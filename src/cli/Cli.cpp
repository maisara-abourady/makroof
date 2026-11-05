#include "cli/Cli.h"

#include "cli/WavIO.h"
#include "contract/Parse.h"
#include "contract/Version.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <locale>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace cli {

namespace {

struct Options
{
    std::string scenePath;
    std::string inPath;
    std::string outPath;
    std::string irPath;
    std::string automationPath;
    std::string imagesPath;
    bool noAirAbsorption = false;
    std::optional<double> rate;
    std::optional<sim::BuildOptions::Kind> mode;
    bool help = false;
    bool version = false;
};

std::optional<sim::BuildOptions::Kind> parseMode(const std::string& text)
{
    if (text == "omni")
        return sim::BuildOptions::Kind::Omni;
    if (text == "binaural")
        return sim::BuildOptions::Kind::Binaural;
    if (text == "stereoSpeakers")
        return sim::BuildOptions::Kind::StereoSpeakers;
    return std::nullopt;
}

std::optional<double> parseRate(const std::string& text)
{
    int value = 0;
    const char* end = text.data() + text.size();
    const auto [ptr, ec] = std::from_chars(text.data(), end, value);
    if (ec != std::errc{} || ptr != end || value <= 0)
        return std::nullopt;
    return static_cast<double>(value);
}

// Returns an error message, or an empty string on success.
std::string parseArgs(const std::vector<std::string>& args, Options& options)
{
    for (std::size_t i = 0; i < args.size(); ++i)
    {
        const std::string& arg = args[i];
        if (arg == "--help" || arg == "-h")
        {
            options.help = true;
            continue;
        }
        if (arg == "--version")
        {
            options.version = true;
            continue;
        }
        if (arg == "--no-air-absorption")
        {
            options.noAirAbsorption = true;
            continue;
        }

        std::string* target = nullptr;
        if (arg == "--scene")
            target = &options.scenePath;
        else if (arg == "--in")
            target = &options.inPath;
        else if (arg == "--out")
            target = &options.outPath;
        else if (arg == "--ir")
            target = &options.irPath;
        else if (arg == "--automation")
            target = &options.automationPath;
        else if (arg == "--images")
            target = &options.imagesPath;
        else if (arg != "--rate" && arg != "--mode")
            return "unknown argument '" + arg + "'";

        if (i + 1 >= args.size())
            return "missing value after " + arg;
        const std::string& value = args[++i];

        if (arg == "--rate")
        {
            options.rate = parseRate(value);
            if (!options.rate)
                return "--rate must be a positive integer in Hz, got '" + value + "'";
        }
        else if (arg == "--mode")
        {
            options.mode = parseMode(value);
            if (!options.mode)
                return "--mode must be omni, binaural or stereoSpeakers, got '" + value + "'";
        }
        else
        {
            if (!target->empty())
                return arg + " given twice";
            *target = value;
        }
    }

    if (options.help || options.version)
        return {};
    if (!options.automationPath.empty())
        return "--automation is not implemented until Phase 10";
    if (options.scenePath.empty())
        return "--scene is required";
    if (options.inPath.empty() != options.outPath.empty())
        return "--in and --out must be given together";
    if (options.inPath.empty() && options.irPath.empty() && options.imagesPath.empty())
        return "nothing to do: give --in and --out, --ir or --images";
    if (options.rate && !sim::isSupportedSampleRate(*options.rate))
        return "--rate must be one of 44100, 48000, 88200, 96000 (AX6)";
    return {};
}

bool readTextFile(const std::filesystem::path& path, std::string& text)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
        return false;
    std::ostringstream buffer;
    buffer << in.rdbuf();
    if (in.bad())
        return false;
    text = buffer.str();
    return true;
}

void writeNumber(std::ostream& os, double v)
{
    // 17 significant digits round-trip a double exactly. (Floating-point std::to_chars isn't
    // available on every macOS deployment target.)
    std::ostringstream text;
    text.imbue(std::locale::classic());
    text << std::setprecision(17) << v;
    os << text.str();
}

template <typename Range>
void writeArray(std::ostream& os, const Range& values)
{
    os << '[';
    bool first = true;
    for (const auto v : values)
    {
        if (!first)
            os << ',';
        first = false;
        writeNumber(os, static_cast<double>(v));
    }
    os << ']';
}

void writeVec(std::ostream& os, const contract::Vec3& v)
{
    writeArray(os, std::array<double, 3>{v.x, v.y, v.z});
}

// The image-source list of every emitter as JSON (format in usage()).
bool writeImages(const std::filesystem::path& path, const contract::SceneDescription& scene,
                 const sim::BuildOptions& build)
{
    std::ofstream os(path, std::ios::binary);
    if (!os)
        return false;
    const auto sets = sim::imageSourcesByChannel(scene, build);
    const double shift = sim::alignmentShiftS(scene, build.sampleRate);
    os << "{\"sampleRate\":";
    writeNumber(os, build.sampleRate);
    os << ",\"speedOfSound\":";
    writeNumber(os, sim::ism::kSpeedOfSoundMps);
    os << ",\"alignPreRollSamples\":" << sim::kAlignPreRollSamples << ",\"alignmentShiftS\":";
    writeNumber(os, shift);
    os << ",\"airAbsorption\":" << (build.airAbsorption ? "true" : "false");
    os << ",\"bandsHz\":";
    writeArray(os, contract::kOctaveBandsHz);
    os << ",\"emitters\":[";
    for (std::size_t ch = 0; ch < sets.size(); ++ch)
    {
        const auto it = std::find_if(scene.emitters.begin(), scene.emitters.end(),
                                     [&](const auto& e) { return e.channel == static_cast<int>(ch); });
        os << (ch ? "," : "") << "{\"channel\":" << ch << ",\"id\":\""
           << (it != scene.emitters.end() ? it->id : "") << "\",\"images\":[";
        bool first = true;
        for (const auto& image : sets[ch].images)
        {
            os << (first ? "" : ",") << "{\"order\":" << image.order << ",\"position\":";
            first = false;
            writeVec(os, image.position);
            os << ",\"distance\":";
            writeNumber(os, image.distanceM);
            os << ",\"time\":";
            writeNumber(os, image.arrivalTimeS);
            os << ",\"sample\":";
            writeNumber(os, (image.arrivalTimeS - shift) * build.sampleRate);
            os << ",\"hits\":";
            writeArray(os, image.hits);
            os << ",\"direction\":";
            writeVec(os, image.arrivalDirection);
            os << ",\"amplitude\":";
            writeArray(os, image.bandsAmplitude);
            os << '}';
        }
        os << "],\"scattered\":[";
        first = true;
        for (const auto& s : sets[ch].scattered)
        {
            os << (first ? "" : ",") << "{\"order\":" << s.order << ",\"time\":";
            first = false;
            writeNumber(os, s.arrivalTimeS);
            os << ",\"energy\":";
            writeArray(os, s.bandsEnergy);
            os << '}';
        }
        os << "]}";
    }
    os << "]}\n";
    return static_cast<bool>(os);
}

} // namespace

std::string usage()
{
    return "usage:\n"
           "  render_cli --scene <json> --in <wav> --out <wav> [--rate <hz>] "
           "[--mode omni|binaural|stereoSpeakers]\n"
           "  render_cli --scene <json> --ir <wav> [--rate <hz>] [--mode ...]\n"
           "  render_cli --scene <json> --images <json> [--rate <hz>]\n"
           "  render_cli --help | --version\n"
           "\n"
           "  --in/--out   render a stereo WAV through the scene (output: float32 WAV, length input + IR - "
           "1)\n"
           "  --ir         write the room IR (float32 WAV, channel = emitter * outputs + output)\n"
           "  --rate       sample rate in Hz; must match the input WAV when --in is given (default: the\n"
           "               input's rate, or 48000 for --ir alone). Supported: 44100, 48000, 88200, 96000\n"
           "  --mode       output kind (default: the scene's render.outputMode). omni = early\n"
           "               reflections (Phase 03); binaural/stereoSpeakers are still a dry stub\n"
           "  --images     write the image sources of each emitter as JSON: per image order,\n"
           "               position, distance (m), time (s, unaligned), sample (aligned, fractional),\n"
           "               hits per surface (xMin xMax yMin yMax floor ceiling), direction of\n"
           "               arrival, amplitude per band; plus the scattered energy per path\n"
           "  --no-air-absorption  validation only: switch off air absorption (AX4 keeps it on)\n"
           "  --automation not implemented until Phase 10\n"
           "\n"
           "exit codes: 0 ok, 1 usage error, 2 invalid scene, 3 I/O error, 4 internal error\n";
}

namespace {

int runUnchecked(const std::vector<std::string>& args, std::ostream& out, std::ostream& err)
{
    Options options;
    if (const std::string problem = parseArgs(args, options); !problem.empty())
    {
        err << "render_cli: " << problem << "\n\n" << usage();
        return kExitUsage;
    }
    if (options.help)
    {
        out << usage();
        return kExitOk;
    }
    if (options.version)
    {
        out << "render_cli (SpatialScene), scene contract " << contract::contractVersion() << "\n";
        return kExitOk;
    }

    // ---- Scene ----
    std::string sceneText;
    if (!readTextFile(options.scenePath, sceneText))
    {
        err << "render_cli: cannot read scene file '" << options.scenePath << "'\n";
        return kExitIo;
    }
    const contract::ParseResult parsed = contract::parseScene(sceneText);
    for (const auto& issue : parsed.issues)
        err << (issue.severity() == contract::Severity::error ? "error: " : "warning: ")
            << contract::toString(issue) << "\n";
    if (!parsed.ok())
    {
        err << "render_cli: invalid scene '" << options.scenePath << "'\n";
        return kExitInvalidScene;
    }
    const contract::SceneDescription& scene = *parsed.scene;

    // ---- Input ----
    Audio input;
    if (!options.inPath.empty())
    {
        std::string error;
        if (!readWav(options.inPath, input, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitIo;
        }
        if (input.channels.size() != 2)
        {
            err << "render_cli: input '" << options.inPath << "' has " << input.channels.size()
                << " channels; v1 needs a stereo input (AX7)\n";
            return kExitIo;
        }
        if (!sim::isSupportedSampleRate(input.sampleRate))
        {
            err << "render_cli: input '" << options.inPath << "' has sample rate " << input.sampleRate
                << " Hz; supported: 44100, 48000, 88200, 96000 (AX6)\n";
            return kExitIo;
        }
        if (options.rate && *options.rate != static_cast<double>(input.sampleRate))
        {
            err << "render_cli: --rate " << *options.rate << " does not match the input's "
                << input.sampleRate << " Hz (render_cli does not resample)\n";
            return kExitUsage;
        }
    }

    sim::BuildOptions build;
    build.sampleRate = options.rate.value_or(options.inPath.empty() ? kDefaultIrSampleRateHz
                                                                    : static_cast<double>(input.sampleRate));
    build.kind = options.mode.value_or(sim::kindForOutputMode(scene.render.outputMode));
    build.airAbsorption = !options.noAirAbsorption;

    if (!options.imagesPath.empty())
    {
        if (!writeImages(options.imagesPath, scene, build))
        {
            err << "render_cli: cannot write '" << options.imagesPath << "'\n";
            return kExitIo;
        }
        out << "wrote image sources " << options.imagesPath << "\n";
        if (options.irPath.empty() && options.inPath.empty())
            return kExitOk;
    }

    const sim::RoomIR ir = sim::buildRoomIR(scene, build);

    // ---- IR ----
    if (!options.irPath.empty())
    {
        Audio irAudio;
        irAudio.sampleRate = static_cast<std::uint32_t>(ir.sampleRate);
        irAudio.channels = ir.taps;
        std::string error;
        if (!writeWavFloat32(options.irPath, irAudio, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitIo;
        }
        out << "wrote IR " << options.irPath << " (" << ir.taps.size() << " channels, " << ir.length()
            << " samples)\n";
    }

    // ---- Render ----
    if (!options.inPath.empty())
    {
        Audio rendered;
        rendered.sampleRate = input.sampleRate;
        rendered.channels = sim::renderOffline(ir, input.channels);
        std::string error;
        if (!writeWavFloat32(options.outPath, rendered, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitIo;
        }
        out << "wrote " << options.outPath << " (" << rendered.channels.size() << " channels, "
            << rendered.numFrames() << " samples)\n";
    }
    return kExitOk;
}

} // namespace

int runCli(const std::vector<std::string>& args, std::ostream& out, std::ostream& err)
{
    try
    {
        return runUnchecked(args, out, err);
    }
    catch (const std::exception& e)
    {
        err << "render_cli: internal error: " << e.what() << "\n";
        return kExitInternal;
    }
}

} // namespace cli
