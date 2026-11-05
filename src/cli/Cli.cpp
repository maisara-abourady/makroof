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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <locale>
#include <optional>
#include <ostream>
#include <span>
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
    std::string diagnosticsPath;
    std::optional<std::uint32_t> tailSeed;
    std::optional<std::uint32_t> ensemble;
    std::optional<std::uint32_t> ensembleEmitter;
    bool noAirAbsorption = false;
    bool tailOnly = false;
    std::optional<double> rate;
    std::optional<sim::BuildOptions::Kind> mode;
    bool help = false;
    bool version = false;
};

std::optional<sim::BuildOptions::Kind> parseMode(const std::string& text)
{
    if (text == "omni")
        return sim::BuildOptions::Kind::Omni;
    if (text == "omni-early")
        return sim::BuildOptions::Kind::OmniEarly;
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

std::optional<std::uint32_t> parseSeed(const std::string& text)
{
    std::uint32_t value = 0;
    const char* end = text.data() + text.size();
    const auto [ptr, ec] = std::from_chars(text.data(), end, value);
    if (ec != std::errc{} || ptr != end || text.empty())
        return std::nullopt;
    return value;
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
        if (arg == "--tail-only")
        {
            options.tailOnly = true;
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
        else if (arg == "--diagnostics")
            target = &options.diagnosticsPath;
        else if (arg != "--rate" && arg != "--mode" && arg != "--tail-seed" && arg != "--ensemble"
                 && arg != "--ensemble-emitter")
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
                return "--mode must be omni, omni-early, binaural or stereoSpeakers, got '" + value + "'";
        }
        else if (arg == "--tail-seed")
        {
            options.tailSeed = parseSeed(value);
            if (!options.tailSeed)
                return "--tail-seed must be an integer in [0, 4294967295], got '" + value + "'";
        }
        else if (arg == "--ensemble")
        {
            options.ensemble = parseSeed(value);
            if (!options.ensemble || *options.ensemble == 0 || *options.ensemble > 100000)
                return "--ensemble must be an integer in [1, 100000], got '" + value + "'";
        }
        else if (arg == "--ensemble-emitter")
        {
            options.ensembleEmitter = parseSeed(value);
            if (!options.ensembleEmitter || *options.ensembleEmitter > 1)
                return "--ensemble-emitter must be 0 or 1, got '" + value + "'";
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
    if (options.inPath.empty() && options.irPath.empty() && options.imagesPath.empty()
        && options.diagnosticsPath.empty())
        return "nothing to do: give --in and --out, --ir, --images or --diagnostics";
    if (!options.diagnosticsPath.empty() && options.mode && *options.mode != sim::BuildOptions::Kind::Omni)
        return "--diagnostics needs --mode omni (the hybrid IR)";
    if (options.tailOnly && (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni))
        return "--tail-only needs --mode omni (the hybrid IR)";
    if (options.ensemble
        && (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni || options.irPath.empty()
            || !options.inPath.empty() || !options.imagesPath.empty() || !options.diagnosticsPath.empty()))
        return "--ensemble needs --mode omni and --ir, without --in, --images or --diagnostics";
    if (options.ensembleEmitter && !options.ensemble)
        return "--ensemble-emitter needs --ensemble";
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

// Diagnostics of the hybrid omni build as JSON (format in usage()). NaN becomes null.
bool writeDiagnostics(const std::filesystem::path& path, const contract::SceneDescription& scene,
                      const sim::HybridDiagnostics& d)
{
    std::ofstream os(path, std::ios::binary);
    if (!os)
        return false;
    const auto num = [&](double v) {
        if (std::isfinite(v))
            writeNumber(os, v);
        else
            os << "null";
    };
    const auto arr = [&](const auto& values) {
        os << '[';
        bool first = true;
        for (const auto v : values)
        {
            os << (first ? "" : ",");
            first = false;
            num(static_cast<double>(v));
        }
        os << ']';
    };
    os << "{\"sampleRate\":";
    num(d.sampleRate);
    os << ",\"bandsHz\":";
    arr(contract::kOctaveBandsHz);
    os << ",\"tailSeed\":" << scene.render.tailSeed;
    os << ",\"volume\":";
    num(d.decay.volumeM3);
    os << ",\"surface\":";
    num(d.decay.surfaceM2);
    os << ",\"meanAbsorption\":";
    arr(d.decay.bandsMeanAbsorption);
    os << ",\"airEnergyPerMetre\":";
    arr(d.decay.bandsAirEnergyPerMetre);
    os << ",\"t60\":";
    arr(d.decay.bandsT60S);
    os << ",\"tailLengthS\":";
    num(d.tailLengthS);
    os << ",\"alignmentShiftS\":";
    num(d.alignmentShiftS);
    os << ",\"irLength\":" << d.irLength << ",\"emitters\":[";
    bool first = true;
    for (const auto& e : d.emitters)
    {
        const auto it = std::find_if(scene.emitters.begin(), scene.emitters.end(),
                                     [&](const auto& em) { return em.channel == e.channel; });
        os << (first ? "" : ",") << "{\"channel\":" << e.channel << ",\"id\":\""
           << (it != scene.emitters.end() ? it->id : "") << "\"";
        first = false;
        const auto& m = e.match;
        os << ",\"imageCount\":" << e.imageCount << ",\"scatteredCount\":" << e.scatteredCount;
        os << ",\"directS\":";
        num(m.mixing.directS);
        os << ",\"mixLowerBoundS\":";
        num(m.mixing.lowerBoundS);
        os << ",\"windowStartS\":";
        num(m.mixing.windowStartS);
        os << ",\"mixS\":";
        num(m.mixing.mixS);
        os << ",\"expectedKeff\":";
        num(m.mixing.expectedKeff);
        os << ",\"expectedSigmaDb\":";
        num(m.expectedSigmaDb);
        os << ",\"targetEnergy\":";
        arr(m.bandsTargetEnergy);
        os << ",\"expectedUnitEnergy\":";
        arr(m.bandsExpectedUnitEnergy);
        os << ",\"amplitude\":";
        arr(m.bandsAmplitude);
        os << ",\"nonZeroEntries\":";
        arr(m.bandsNonZeroEntries);
        os << ",\"realisedKeff\":";
        arr(m.bandsRealisedKeff);
        os << ",\"realisedOverTargetDb\":";
        arr(e.bandsRealisedOverTargetDb);
        os << '}';
    }
    os << "]}\n";
    return static_cast<bool>(os);
}

} // namespace

std::string usage()
{
    return "usage:\n"
           "  render_cli --scene <json> --in <wav> --out <wav> [--rate <hz>] "
           "[--mode omni|omni-early|binaural|stereoSpeakers]\n"
           "  render_cli --scene <json> --ir <wav> [--rate <hz>] [--mode ...] [--tail-seed <n>]\n"
           "  render_cli --scene <json> --images <json> [--rate <hz>]\n"
           "  render_cli --scene <json> --mode omni --diagnostics <json> [--rate <hz>]\n"
           "  render_cli --help | --version\n"
           "\n"
           "  --in/--out   render a stereo WAV through the scene (output: float32 WAV, length input + IR - "
           "1)\n"
           "  --ir         write the room IR (float32 WAV, channel = emitter * outputs + output)\n"
           "  --rate       sample rate in Hz; must match the input WAV when --in is given (default: the\n"
           "               input's rate, or 48000 for --ir alone). Supported: 44100, 48000, 88200, 96000\n"
           "  --mode       output kind (default: the scene's render.outputMode). omni = hybrid room IR\n"
           "               (early reflections + late tail, Phase 04); omni-early = early reflections\n"
           "               only, to maxReflectionOrder (Phase 03); binaural/stereoSpeakers are still a\n"
           "               dry stub\n"
           "  --tail-seed  override render.tailSeed (0..4294967295) for this run (ensembles, AX11)\n"
           "  --images     write the image sources of each emitter as JSON: per image order,\n"
           "               position, distance (m), time (s, unaligned), sample (aligned, fractional),\n"
           "               hits per surface (xMin xMax yMin yMax floor ceiling), direction of\n"
           "               arrival, amplitude per band; plus the scattered energy per path. With --mode\n"
           "               omni: the AX20 list (every image before t_mix + 2.5 ms, any order)\n"
           "  --diagnostics  hybrid omni IR only: write T60 per band (Eyring), tail length, and per\n"
           "               emitter t_mix, the matching window, expected k_eff and sigma_dB, E_target,\n"
           "               expected unit-decay energy, tail amplitude E_b, non-zero entry count and\n"
           "               realised k_eff per band\n"
           "  --no-air-absorption  validation only: switch off air absorption (AX4 keeps it on)\n"
           "  --tail-only  validation only, --mode omni: write just the matched late tail (no early part,\n"
           "               no crossfade), for decay-time ensembles\n"
           "  --ensemble   validation only, --mode omni --ir: render N realisations with tail seeds\n"
           "               tailSeed, tailSeed + 1, ...; channel 2k = emitter 0 and 2k + 1 = emitter 1 of\n"
           "               seed tailSeed + k (output 0)\n"
           "  --ensemble-emitter  with --ensemble: build and write only emitter channel 0 or 1 (one\n"
           "               WAV channel per seed)\n"
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
    contract::SceneDescription scene = *parsed.scene;
    if (options.tailSeed)
        scene.render.tailSeed = *options.tailSeed;

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
    build.tailOnly = options.tailOnly;
    if (options.ensembleEmitter)
        build.onlyEmitterChannel = static_cast<int>(*options.ensembleEmitter);

    if (!options.imagesPath.empty())
    {
        if (!writeImages(options.imagesPath, scene, build))
        {
            err << "render_cli: cannot write '" << options.imagesPath << "'\n";
            return kExitIo;
        }
        out << "wrote image sources " << options.imagesPath << "\n";
        if (options.irPath.empty() && options.inPath.empty() && options.diagnosticsPath.empty())
            return kExitOk;
    }

    if (!options.diagnosticsPath.empty() && build.kind != sim::BuildOptions::Kind::Omni)
    {
        err << "render_cli: --diagnostics needs --mode omni (the hybrid IR)\n\n" << usage();
        return kExitUsage;
    }
    sim::HybridDiagnostics diagnostics;
    const sim::RoomIR ir = options.ensemble ? sim::RoomIR{} : sim::buildRoomIR(scene, build, &diagnostics);

    if (!options.diagnosticsPath.empty())
    {
        if (!writeDiagnostics(options.diagnosticsPath, scene, diagnostics))
        {
            err << "render_cli: cannot write '" << options.diagnosticsPath << "'\n";
            return kExitIo;
        }
        out << "wrote diagnostics " << options.diagnosticsPath << "\n";
    }

    // ---- Ensemble of IRs (validation, AX11): seeds tailSeed, tailSeed + 1, ... ----
    if (options.ensemble)
    {
        Audio irAudio;
        irAudio.sampleRate = static_cast<std::uint32_t>(build.sampleRate);
        std::vector<std::uint32_t> seeds(*options.ensemble);
        for (std::uint32_t k = 0; k < *options.ensemble; ++k)
            seeds[k] = scene.render.tailSeed + k; // wraps modulo 2^32
        // In chunks, so a long ensemble doesn't hold every IR twice.
        for (std::size_t first = 0; first < seeds.size(); first += 64)
        {
            const auto count = std::min<std::size_t>(64, seeds.size() - first);
            for (auto& one : sim::buildRoomIREnsemble(scene, build, std::span(seeds).subspan(first, count)))
                for (int e = 0; e < 2; ++e)
                    if (!options.ensembleEmitter || static_cast<int>(*options.ensembleEmitter) == e)
                        irAudio.channels.push_back(std::move(one.taps[one.index(e, 0)]));
        }
        std::string error;
        if (!writeWavFloat32(options.irPath, irAudio, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitIo;
        }
        out << "wrote IR ensemble " << options.irPath << " (" << irAudio.channels.size() << " channels, "
            << (irAudio.channels.empty() ? 0 : irAudio.channels.front().size()) << " samples)\n";
        return kExitOk;
    }

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
