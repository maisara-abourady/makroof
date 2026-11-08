#include "cli/Cli.h"

#include "cli/WavIO.h"
#include "contract/Parse.h"
#include "contract/Version.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"
#include "sim/RealtimeEngine.h"
#include "sim/Rng.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstdlib>
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

// Largest fixed --block, and the upper end of --block random (1 .. 2048, the largest host buffer
// in the phase-06 acceptance list).
constexpr int kMaxEmulationBlock = 8192;
constexpr int kMaxRandomBlock = 2048;
// Seed of the --block random schedule (PCG32 state, stream): fixed, so the emulation is deterministic.
constexpr std::uint64_t kRandomBlockSeed = 20261107u;
constexpr std::uint64_t kRandomBlockStream = 6u;

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
    std::optional<std::uint32_t> imageCap;
    std::optional<sim::BuildOptions::Atmosphere> atmosphere;
    std::optional<double> mixFloorMs;
    // Phase 06: render --in through sim::RealtimeEngine in host blocks (realtime emulation).
    bool realtimeEmulation = false;
    std::optional<int> block;     // fixed host block size; 0 = seeded random sizes 1..2048
    std::optional<int> partition; // P (128, 256, 512)
    std::string switchScenePath;  // listening demo: alternate with this scene's IR
    std::optional<double> switchEveryS;
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
        if (arg == "--realtime-emulation")
        {
            options.realtimeEmulation = true;
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
        else if (arg == "--switch-scene")
            target = &options.switchScenePath;
        else if (arg != "--rate" && arg != "--mode" && arg != "--tail-seed" && arg != "--ensemble"
                 && arg != "--ensemble-emitter" && arg != "--image-cap" && arg != "--atmosphere"
                 && arg != "--mix-floor-ms" && arg != "--block" && arg != "--partition"
                 && arg != "--switch-every")
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
        else if (arg == "--image-cap")
        {
            options.imageCap = parseSeed(value);
            if (!options.imageCap || *options.imageCap == 0)
                return "--image-cap must be a positive integer, got '" + value + "'";
        }
        else if (arg == "--atmosphere")
        {
            // T,RH: degC and % relative humidity (AX4 validation override).
            const auto comma = value.find(',');
            char* end = nullptr;
            const double t = comma == std::string::npos ? 0.0 : std::strtod(value.c_str(), &end);
            const bool tOk = comma != std::string::npos && end == value.c_str() + comma;
            const std::string rhText = comma == std::string::npos ? std::string{} : value.substr(comma + 1);
            const double rh = rhText.empty() ? 0.0 : std::strtod(rhText.c_str(), &end);
            const bool rhOk = !rhText.empty() && end == rhText.c_str() + rhText.size();
            if (!tOk || !rhOk || !std::isfinite(t) || !std::isfinite(rh) || t < -20.0 || t > 50.0 || rh < 10.0
                || rh > 100.0)
                return "--atmosphere must be T,RH with -20 <= T <= 50 degC and 10 <= RH <= 100 %, got '"
                       + value + "'";
            options.atmosphere = sim::BuildOptions::Atmosphere{t, rh};
        }
        else if (arg == "--mix-floor-ms")
        {
            char* end = nullptr;
            const double ms = std::strtod(value.c_str(), &end);
            if (end != value.c_str() + value.size() || !std::isfinite(ms) || ms < 0.0 || ms > 1000.0)
                return "--mix-floor-ms must be a number of milliseconds in [0, 1000], got '" + value + "'";
            options.mixFloorMs = ms;
        }
        else if (arg == "--block")
        {
            if (value == "random")
                options.block = 0;
            else
            {
                const auto b = parseSeed(value);
                if (!b || *b == 0 || *b > static_cast<std::uint32_t>(kMaxEmulationBlock))
                    return "--block must be 'random' or an integer in [1, "
                           + std::to_string(kMaxEmulationBlock) + "], got '" + value + "'";
                options.block = static_cast<int>(*b);
            }
        }
        else if (arg == "--partition")
        {
            const auto p = parseSeed(value);
            if (!p || !sim::conv::isSupportedPartitionSize(static_cast<int>(*p)))
                return "--partition must be 128, 256 or 512, got '" + value + "'";
            options.partition = static_cast<int>(*p);
        }
        else if (arg == "--switch-every")
        {
            char* end = nullptr;
            const double sec = std::strtod(value.c_str(), &end);
            if (end != value.c_str() + value.size() || !std::isfinite(sec) || sec < 0.05 || sec > 60.0)
                return "--switch-every must be a number of seconds in [0.05, 60], got '" + value + "'";
            options.switchEveryS = sec;
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
    if (options.imageCap && (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni))
        return "--image-cap needs --mode omni (the hybrid IR)";
    if (options.mixFloorMs && (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni))
        return "--mix-floor-ms needs --mode omni (the hybrid IR)";
    if (options.atmosphere && options.noAirAbsorption)
        return "--atmosphere and --no-air-absorption exclude each other";
    if (options.ensembleEmitter && !options.ensemble)
        return "--ensemble-emitter needs --ensemble";
    if (options.realtimeEmulation && options.inPath.empty())
        return "--realtime-emulation needs --in and --out";
    if ((options.block || options.partition || !options.switchScenePath.empty() || options.switchEveryS)
        && !options.realtimeEmulation)
        return "--block, --partition, --switch-scene and --switch-every need --realtime-emulation";
    if (options.switchScenePath.empty() != !options.switchEveryS)
        return "--switch-scene and --switch-every must be given together";
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
        os << ",\"realisedSigmaDb\":";
        arr(m.bandsRealisedSigmaDb);
        os << ",\"axisShares\":[";
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            os << (b ? "," : "");
            arr(m.bandsAxisShares[b]);
        }
        os << "],\"realisedKeffAtMix\":";
        arr(e.bandsRealisedKeffAtMix);
        os << ",\"ismFallback\":" << (e.ismFallback ? "true" : "false")
           << ",\"imageCountCap\":" << e.imageCountCap << ",\"capTimeS\":";
        num(e.capTimeS);
        os << ",\"handoverS\":";
        num(e.handoverS);
        os << ",\"expectedMixS\":";
        num(e.expectedMixS);
        os << '}';
    }
    os << "]}\n";
    return static_cast<bool>(os);
}

// --realtime-emulation: renders `input` through sim::RealtimeEngine in host blocks, as a plugin
// would, so the real-time path can be nulled against renderOffline. The output has the offline
// render's length and alignment: the convolver latency P is removed (the AX1 pre-roll is part of the
// IR in both paths). With `other`, the engine switches between ir and *other every switchEvery
// samples of the render (equal-power, AX18: unrelated IRs), starting with ir; a host block boundary
// is placed at every switch.
bool renderRealtime(const sim::RoomIR& ir, const sim::RoomIR* other, const Options& options,
                    const sim::MultiChannel& input, sim::MultiChannel& output, std::string& error)
{
    const int partition = options.partition.value_or(sim::conv::kDefaultPartitionSize);
    const int block = options.block.value_or(512);
    const int maxBlock = block == 0 ? kMaxRandomBlock : block;
    sim::RealtimeEngine engine(partition);
    engine.prepare(ir.sampleRate, maxBlock);
    const auto setA = engine.makeIrSet(ir);
    const auto setB = other != nullptr ? engine.makeIrSet(*other) : nullptr;
    if (!setA || (other != nullptr && !setB))
    {
        error = "the room IR does not fit the real-time engine (longer than "
                + std::to_string(sim::RealtimeEngine::maxIrLengthSamples(ir.sampleRate))
                + " samples, or a non-finite tap)";
        return false;
    }
    const std::size_t irLength = std::max(ir.length(), other != nullptr ? other->length() : std::size_t{0});
    const std::size_t frames = input.empty() ? 0 : input.front().size();
    const std::size_t outLength = frames == 0 ? 0 : frames + std::max<std::size_t>(irLength, 1) - 1;
    const auto latency = static_cast<std::size_t>(partition);
    const std::size_t total = outLength + latency;

    std::vector<std::vector<float>> in(2, std::vector<float>(total, 0.0f)),
        out(2, std::vector<float>(total, 0.0f));
    for (std::size_t c = 0; c < 2 && c < input.size(); ++c)
        std::copy(input[c].begin(), input[c].end(), in[c].begin());

    const std::size_t interval = options.switchEveryS
                                     ? std::max<std::size_t>(1, static_cast<std::size_t>(std::llround(
                                                                    *options.switchEveryS * ir.sampleRate)))
                                     : 0;
    engine.submitIrSet(setA);
    sim::Pcg32 rng(kRandomBlockSeed, kRandomBlockStream);
    std::size_t nextSwitch = interval;
    bool onA = true;
    for (std::size_t pos = 0; pos < total;)
    {
        if (interval != 0 && pos == nextSwitch)
        {
            onA = !onA;
            engine.submitIrSet(onA ? setA : setB, sim::conv::CrossfadeLaw::EqualPower);
            nextSwitch += interval;
        }
        std::size_t n = block == 0 ? 1 + rng.next() % static_cast<std::uint32_t>(kMaxRandomBlock)
                                   : static_cast<std::size_t>(block);
        n = std::min(n, total - pos);
        if (interval != 0)
            n = std::min(n, nextSwitch - pos);
        const float* ins[2] = {in[0].data() + pos, in[1].data() + pos};
        float* outs[2] = {out[0].data() + pos, out[1].data() + pos};
        engine.process(ins, outs, static_cast<int>(n));
        engine.releaseRetired();
        pos += n;
    }
    output.assign(2, {});
    for (std::size_t c = 0; c < 2; ++c)
        output[c].assign(out[c].begin() + static_cast<std::ptrdiff_t>(latency), out[c].end());
    return true;
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
           "               realised k_eff per band; realised sigma, per-axis energy shares, k_real at\n"
           "               the expected-rule t_mix, the AX22 fallback, its cap time and the handover time\n"
           "  --no-air-absorption  validation only: switch off air absorption (AX4 keeps it on)\n"
           "  --tail-only  validation only, --mode omni: write just the matched late tail (no early part,\n"
           "               no crossfade), for decay-time ensembles\n"
           "  --ensemble   validation only, --mode omni --ir: render N realisations with tail seeds\n"
           "               tailSeed, tailSeed + 1, ...; channel 2k = emitter 0 and 2k + 1 = emitter 1 of\n"
           "               seed tailSeed + k (output 0)\n"
           "  --atmosphere T,RH  validation only: air absorption at T degC and RH % instead of the AX4\n"
           "               atmosphere (20 degC, 50 %), in the image sources and the tail (phase-05 scope 6)\n"
           "  --mix-floor-ms X  validation only, --mode omni: raise the mixing-time lower bound to\n"
           "               t_dir,e + X ms (phase-05 scope 6, handover)\n"
           "  --image-cap  validation only, --mode omni: override the AX22 image-count cap N_cap (the\n"
           "               sensitivity report at nu_r(2 i0))\n"
           "  --ensemble-emitter  with --ensemble: build and write only emitter channel 0 or 1 (one\n"
           "               WAV channel per seed)\n"
           "  --realtime-emulation  with --in/--out: render through the real-time engine (Phase 06:\n"
           "               partitioned convolution, as the plugin will) instead of the offline reference;\n"
           "               same length and alignment as the offline render (the convolver latency P is\n"
           "               removed; the AX1 pre-roll stays in the IR as offline)\n"
           "  --block N|random  realtime emulation: host block size (default 512), or seeded random sizes\n"
           "               in 1..2048\n"
           "  --partition P  realtime emulation: partition size 128, 256 or 512 (default 512)\n"
           "  --switch-scene <json> --switch-every S  realtime emulation, listening demo: switch the IR\n"
           "               between --scene and this scene every S seconds (30 ms equal-power crossfade)\n"
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

    std::optional<contract::SceneDescription> switchScene;
    if (!options.switchScenePath.empty())
    {
        std::string switchText;
        if (!readTextFile(options.switchScenePath, switchText))
        {
            err << "render_cli: cannot read scene file '" << options.switchScenePath << "'\n";
            return kExitIo;
        }
        const contract::ParseResult other = contract::parseScene(switchText);
        for (const auto& issue : other.issues)
            err << (issue.severity() == contract::Severity::error ? "error: " : "warning: ")
                << contract::toString(issue) << "\n";
        if (!other.ok())
        {
            err << "render_cli: invalid scene '" << options.switchScenePath << "'\n";
            return kExitInvalidScene;
        }
        switchScene = *other.scene;
        if (options.tailSeed)
            switchScene->render.tailSeed = *options.tailSeed;
    }

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
    if (options.imageCap)
        build.imageCountCapOverride = *options.imageCap;
    build.atmosphere = options.atmosphere;
    if (options.mixFloorMs)
        build.mixingFloorAfterDirectS = *options.mixFloorMs * 1e-3;
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
        std::string error;
        if (options.realtimeEmulation)
        {
            const sim::RoomIR other = switchScene ? sim::buildRoomIR(*switchScene, build) : sim::RoomIR{};
            if (!renderRealtime(ir, switchScene ? &other : nullptr, options, input.channels,
                                rendered.channels, error))
            {
                err << "render_cli: " << error << "\n";
                return kExitInternal;
            }
        }
        else
            rendered.channels = sim::renderOffline(ir, input.channels);
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
