#include "cli/Cli.h"

#include "cli/WavIO.h"
#include "contract/Parse.h"
#include "contract/Version.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"
#include "sim/RealtimeEngine.h"
#include "sim/Rng.h"
#include "sim/diffuse/DiffuseEstimator.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    bool tailLevelAx16 = false; // phase 05h, validation only: the Phase 04 (AX16) tail level
    std::optional<std::uint64_t> diffuseHistories; // phase 05h, validation only: a fixed solve size
    // Phase-07c-2 D-W2 (AX47 self-ABX), validation only, like --no-air-absorption (AX4): a uniform g dB step
    // of the tail energy, from a second IrSet of the same StagedBuild through useDiffuseLevel, crossfaded in
    // at output sample abxStepSample with the shipped AQ4 30 ms equal-gain fade (AX18). Off unless given; the
    // plugin never links src/cli (tools/ci/test_abx_kit.py checks that src/plugin never names it).
    std::optional<double> abxStepDb;
    std::optional<std::uint64_t> abxStepSample;
    std::string abxSteppedIrPath;
    std::optional<double>
        wMultiplier; // validation only: W_scene = 2 m W_max (the D-W2 cap check at m = 6, 7, 8)
    // Phase-07c-2b L4-P (decider file 10; interrogator file 13; Seat 5 file 14), validation only, off unless
    // given: every output of the run uses the AX49 provisional IR (StagedBuild::assembleProvisional, the
    // plugin's keyless-load interim) instead of the exact one. --provisional-timing writes
    // provisionalTiming();
    // --provisional-handover-sample N starts the shipped AQ4 equal-gain fade (AX18) to the exact IR of the
    // same plan at output sample N, through the RealtimeEngine IR swap. src/plugin never names these
    // (tools/ci/test_provisional_flag.py), and no golden or BRAS path uses them.
    bool provisionalIr = false;
    std::string provisionalTimingPath;
    std::optional<std::uint64_t> provisionalHandoverSample;
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
        if (arg == "--provisional-ir")
        {
            options.provisionalIr = true;
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
        else if (arg == "--abx-stepped-ir")
            target = &options.abxSteppedIrPath;
        else if (arg == "--provisional-timing")
            target = &options.provisionalTimingPath;
        else if (arg != "--rate" && arg != "--mode" && arg != "--tail-seed" && arg != "--ensemble"
                 && arg != "--ensemble-emitter" && arg != "--image-cap" && arg != "--atmosphere"
                 && arg != "--mix-floor-ms" && arg != "--block" && arg != "--partition"
                 && arg != "--switch-every" && arg != "--tail-level" && arg != "--diffuse-histories"
                 && arg != "--abx-step-db" && arg != "--abx-step-sample" && arg != "--w-multiplier"
                 && arg != "--provisional-handover-sample")
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
        else if (arg == "--tail-level")
        {
            if (value != "diffuse" && value != "ax16")
                return "--tail-level must be diffuse (the product) or ax16 (validation), got '" + value + "'";
            options.tailLevelAx16 = value == "ax16";
        }
        else if (arg == "--diffuse-histories")
        {
            options.diffuseHistories = parseSeed(value);
            if (!options.diffuseHistories || *options.diffuseHistories == 0
                || *options.diffuseHistories % 64 != 0
                || *options.diffuseHistories > (std::uint64_t{1} << 24))
                return "--diffuse-histories must be a positive multiple of 64 up to 16777216, got '" + value
                       + "'";
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
        else if (arg == "--abx-step-db")
        {
            char* end = nullptr;
            const double g = std::strtod(value.c_str(), &end);
            if (value.empty() || end != value.c_str() + value.size() || !std::isfinite(g) || g < -12.0
                || g > 12.0)
                return "--abx-step-db must be a number of dB in [-12, 12], got '" + value + "'";
            options.abxStepDb = g;
        }
        else if (arg == "--abx-step-sample")
        {
            const auto n = parseSeed(value);
            if (!n)
                return "--abx-step-sample must be an output sample index in [0, 4294967295], got '" + value
                       + "'";
            options.abxStepSample = *n;
        }
        else if (arg == "--provisional-handover-sample")
        {
            const auto n = parseSeed(value);
            if (!n)
                return "--provisional-handover-sample must be an output sample index in [0, 4294967295], got "
                       "'"
                       + value + "'";
            options.provisionalHandoverSample = *n;
        }
        else if (arg == "--w-multiplier")
        {
            char* end = nullptr;
            const double m = std::strtod(value.c_str(), &end);
            if (value.empty() || end != value.c_str() + value.size() || !std::isfinite(m) || m <= 0.0
                || m > 64.0)
                return "--w-multiplier must be a number in (0, 64], got '" + value + "'";
            options.wMultiplier = m;
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
    // L4-P refusals r2-r5 (r1, L_p >= L, needs the scene: runUnchecked, before any output file is opened).
    if ((!options.provisionalTimingPath.empty() || options.provisionalHandoverSample)
        && !options.provisionalIr)
        return "--provisional-timing and --provisional-handover-sample need --provisional-ir"; // r4
    if (options.provisionalIr)
    {
        if (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni) // r2
            return "--provisional-ir needs --mode omni (the AX49 provisional tail of the hybrid IR)";
        if (!options.diagnosticsPath.empty() || options.ensemble || options.tailOnly
            || options.ensembleEmitter || options.tailLevelAx16 || !options.switchScenePath.empty()
            || options.switchEveryS || options.abxStepDb || options.abxStepSample
            || !options.abxSteppedIrPath.empty() || options.imageCap || !options.automationPath.empty()) // r3
            return "--provisional-ir excludes --diagnostics, --ensemble, --tail-only, --ensemble-emitter, "
                   "--tail-level ax16, --switch-scene, --switch-every, --abx-step-db, --abx-step-sample, "
                   "--abx-stepped-ir, --image-cap and --automation";
        if (options.provisionalHandoverSample) // r5 (the input bound is checked once the input is read)
        {
            if (options.inPath.empty() || !options.realtimeEmulation || !options.block || *options.block == 0)
                return "--provisional-handover-sample needs --in/--out, --realtime-emulation and a fixed "
                       "--block";
            const auto p = static_cast<std::uint64_t>(
                options.partition.value_or(sim::conv::kDefaultPartitionSize));
            const auto b = static_cast<std::uint64_t>(*options.block);
            const std::uint64_t n = *options.provisionalHandoverSample;
            if (n < p || n % p != 0 || n % b != 0)
                return "--provisional-handover-sample must be a multiple of the partition ("
                       + std::to_string(p) + ") and of the block (" + std::to_string(b)
                       + "), at least one partition, got " + std::to_string(n);
        }
    }
    if (!options.automationPath.empty())
        return "--automation is not implemented until Phase 10";
    if (options.scenePath.empty())
        return "--scene is required";
    if (options.inPath.empty() != options.outPath.empty())
        return "--in and --out must be given together";
    if (options.inPath.empty() && options.irPath.empty() && options.imagesPath.empty()
        && options.diagnosticsPath.empty() && options.abxSteppedIrPath.empty()
        && options.provisionalTimingPath.empty())
        return "nothing to do: give --in and --out, --ir, --images, --diagnostics, --abx-stepped-ir or "
               "--provisional-timing";
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
    if (options.wMultiplier && (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni))
        return "--w-multiplier needs --mode omni (the hybrid IR)";
    if ((options.abxStepSample || !options.abxSteppedIrPath.empty()) && !options.abxStepDb)
        return "--abx-step-sample and --abx-stepped-ir need --abx-step-db";
    if (options.abxStepDb)
    {
        if (!options.mode || *options.mode != sim::BuildOptions::Kind::Omni)
            return "--abx-step-db needs --mode omni (the hybrid IR)";
        if (options.ensemble || options.tailLevelAx16 || !options.switchScenePath.empty())
            return "--abx-step-db excludes --ensemble, --tail-level ax16 and --switch-scene";
        if (!options.inPath.empty()
            && (!options.realtimeEmulation || !options.abxStepSample
                || (options.block && *options.block == 0)))
            return "--abx-step-db with --in/--out needs --realtime-emulation, a fixed --block and "
                   "--abx-step-sample";
        if (options.inPath.empty() && options.abxSteppedIrPath.empty())
            return "--abx-step-db needs --in/--out or --abx-stepped-ir";
        if (options.abxStepSample && *options.abxStepSample != 0)
        {
            const auto p = static_cast<std::uint64_t>(
                options.partition.value_or(sim::conv::kDefaultPartitionSize));
            const auto b = static_cast<std::uint64_t>(options.block.value_or(512));
            if (*options.abxStepSample < p || *options.abxStepSample % p != 0
                || *options.abxStepSample % b != 0)
                return "--abx-step-sample must be 0 or a multiple of the partition and of the block, "
                       "at least one partition";
        }
    }
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
        // Phase 05h (AX37, AX41, AX44): the diffuse part of the matching beside the AX16 E_target.
        const auto& dm = m.diffuse;
        os << ",\"axisSharesBasis\":\"specular entries only\"";
        os << ",\"approximate\":" << (m.approximate ? "true" : "false");
        os << ",\"diffuse\":{\"computed\":" << (dm.computed ? "true" : "false");
        os << ",\"targetEnergyAx16\":";
        arr(dm.bandsAx16Energy);
        os << ",\"targetEnergySpecular\":";
        arr(dm.bandsSpecularEnergy);
        os << ",\"targetEnergyDiffuse\":";
        arr(dm.bandsDiffuseEnergy);
        os << ",\"targetEnergyDiffuseReferenceUnits\":";
        arr(dm.bandsDiffuseReference);
        os << ",\"nStar\":" << dm.nStar << ",\"nNeed\":" << dm.nNeed << ",\"n\":" << dm.n
           << ",\"nCap\":" << dm.nCap << ",\"capHit\":" << (dm.capHit ? "true" : "false")
           << ",\"floorTruncated\":" << (dm.floorTruncated ? "true" : "false")
           << ",\"pilotFloor\":" << (dm.pilotFloor ? "true" : "false")
           << ",\"pilotShipped\":" << (dm.pilotShipped ? "true" : "false") << ",\"achievedSeDb\":";
        num(dm.achievedSeDb);
        os << ",\"seDb\":";
        arr(dm.bandsSeDb);
        os << ",\"pilotSeDb\":";
        arr(dm.bandsPilotSeDb);
        os << ",\"r\":";
        arr(dm.bandsR);
        os << ",\"vov\":";
        arr(dm.bandsVov);
        os << ",\"pilotVov\":";
        arr(dm.bandsPilotVov);
        os << ",\"vovUnion\":";
        arr(dm.bandsVovUnion);
        os << ",\"vovUnionMax\":";
        num(dm.vovUnion);
        os << ",\"slope\":";
        arr(dm.bandsSlope);
        os << ",\"weight\":";
        num(dm.weight);
        os << ",\"listenerDistanceM\":";
        num(dm.listenerDistanceM);
        os << ",\"emitterDistanceM\":";
        num(dm.emitterDistanceM);
        os << ",\"bothNear\":" << (dm.bothNear ? "true" : "false") << ",\"realisedWorkRatio\":";
        num(dm.realisedWorkRatio);
        os << ",\"wPilot\":" << dm.wPilot << ",\"wFinal\":" << dm.wFinal << ",\"wScene\":" << dm.wScene
           << ",\"faceHash\":\"0x";
        {
            char buf[32];
            std::snprintf(buf, sizeof buf, "%016llx", static_cast<unsigned long long>(dm.faceHash));
            os << buf;
        }
        os << "\",\"latticeImages\":" << dm.latticeImages << '}';
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
//
// With `stepped` (--abx-step-db, validation only): the engine starts on `ir` and requests `stepped` once,
// with the shipped equal-gain law (AQ4, AX18: the plugin's interim -> final adoption), so that its fade
// starts at output sample options.abxStepSample (a multiple of P and of the block). By CrossfadingConvolver's
// timing (AX31) a request made after r input samples, r a multiple of P, starts its fade at engine output
// sample r + 2P, i.e. at r + P once the latency is removed: the request goes in at r = abxStepSample - P.
// abxStepSample 0 renders `stepped` alone from sample 0 (the fade's end point for the AX47 mid-fade checks).
//
// --provisional-handover-sample N (phase-07c-2b L4-P, validation only) uses the same request: `ir` is the
// AX49 provisional IR and `stepped` the exact IR of the same StagedBuild plan at the same level, both built
// before the first block, so the fade to the exact IR starts at output sample N (the plugin's interim ->
// exact adoption at project load, AX49 "Handover"; its DSP, not its timing).
bool renderRealtime(const sim::RoomIR& ir, const sim::RoomIR* other, const sim::RoomIR* stepped,
                    const Options& options, const sim::MultiChannel& input, sim::MultiChannel& output,
                    std::string& error)
{
    const int partition = options.partition.value_or(sim::conv::kDefaultPartitionSize);
    const int block = options.block.value_or(512);
    const int maxBlock = block == 0 ? kMaxRandomBlock : block;
    sim::RealtimeEngine engine(partition);
    engine.prepare(ir.sampleRate, maxBlock);
    const auto setA = engine.makeIrSet(ir);
    const auto setB = other != nullptr ? engine.makeIrSet(*other) : nullptr;
    const auto setStep = stepped != nullptr ? engine.makeIrSet(*stepped) : nullptr;
    if (!setA || (other != nullptr && !setB) || (stepped != nullptr && !setStep))
    {
        error = "the room IR does not fit the real-time engine (longer than "
                + std::to_string(sim::RealtimeEngine::maxIrLengthSamples(ir.sampleRate))
                + " samples, or a non-finite tap)";
        return false;
    }
    const std::size_t irLength = std::max({ir.length(), other != nullptr ? other->length() : std::size_t{0},
                                           stepped != nullptr ? stepped->length() : std::size_t{0}});
    const std::size_t frames = input.empty() ? 0 : input.front().size();
    const std::size_t outLength = frames == 0 ? 0 : frames + std::max<std::size_t>(irLength, 1) - 1;
    const auto latency = static_cast<std::size_t>(partition);
    const std::size_t total = outLength + latency;
    // --abx-step-db: the input position of the request (see above); never reached when stepped is nullptr.
    std::size_t stepAt = total;
    const std::uint64_t stepSample = options.provisionalHandoverSample ? *options.provisionalHandoverSample
                                                                       : options.abxStepSample.value_or(0);
    const char* stepFlag = options.provisionalHandoverSample ? "--provisional-handover-sample"
                                                             : "--abx-step-sample";
    const bool steppedAlone = stepped != nullptr && stepSample == 0;
    if (stepped != nullptr && !steppedAlone)
    {
        const std::uint64_t onset = stepSample;
        if (onset < latency || onset % latency != 0 || onset % static_cast<std::uint64_t>(block) != 0
            || onset >= outLength)
        {
            error = std::string(stepFlag) + " " + std::to_string(onset)
                    + " must be 0 or a multiple of the partition (" + std::to_string(partition)
                    + ") and of the block (" + std::to_string(block)
                    + "), at least one partition, and inside the render (" + std::to_string(outLength)
                    + " samples)";
            return false;
        }
        stepAt = static_cast<std::size_t>(onset) - latency;
    }

    std::vector<std::vector<float>> in(2, std::vector<float>(total, 0.0f)),
        out(2, std::vector<float>(total, 0.0f));
    for (std::size_t c = 0; c < 2 && c < input.size(); ++c)
        std::copy(input[c].begin(), input[c].end(), in[c].begin());

    const std::size_t interval = options.switchEveryS
                                     ? std::max<std::size_t>(1, static_cast<std::size_t>(std::llround(
                                                                    *options.switchEveryS * ir.sampleRate)))
                                     : 0;
    engine.submitIrSet(steppedAlone ? setStep : setA);
    sim::Pcg32 rng(kRandomBlockSeed, kRandomBlockStream);
    std::size_t nextSwitch = interval;
    bool onA = true;
    for (std::size_t pos = 0; pos < total;)
    {
        if (pos == stepAt)
            engine.submitIrSet(setStep, sim::conv::CrossfadeLaw::EqualGain);
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
        if (pos < stepAt)
            n = std::min(n, stepAt - pos);
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

// --abx-step-db (phase-07c-2 D-W2 item 5; validation only, AX4 style): the unstepped IR `ir` and the stepped
// IR `stepped`, two IrSets from ONE StagedBuild. `ir` is plan(); solve(); assemble() (bit-identical to
// buildRoomIR, AX5 "[staged]"). `stepped` reuses the plan and its unit decays and sets, through
// useDiffuseLevel, the diffuse level that makes the tail energy E_target,b = E_spec,b + E_diff,b of every
// emitter change by g dB in every band (D-W2 item 5: "a change of g dB in tail energy, uniform across all 8
// bands"):  E'_diff,b = k E_diff,b + (k - 1) E_spec,b,  k = 10^(g/10). Where the specular share of the
// tail target is 0 this is file 5's E_b 10^(g/10). The tail amplitude is sqrt(E_target / E_unit), so the
// whole tail scales by 10^(g/20) and the early part (images, direct path) is unchanged. g = 0 passes the
// solve's level unchanged; the two IRs must then be bit-identical (checked here). Prints, per emitter and
// band, the specular share of E_target and the tail-energy change set.
bool buildAbxStep(const contract::SceneDescription& scene, const sim::BuildOptions& build, double g,
                  sim::RoomIR& ir, sim::RoomIR& stepped, sim::HybridDiagnostics& diagnostics,
                  std::ostream& out, std::string& error)
{
    auto staged = sim::StagedBuild::plan(scene, build);
    staged.solve();
    ir = staged.assemble(&diagnostics);
    const std::optional<sim::EmitterBands> level = staged.diffuseLevel();
    if (!level)
    {
        error = "--abx-step-db: the scene has no diffuse tail level to step";
        return false;
    }
    const double k = std::pow(10.0, g / 10.0);
    sim::EmitterBands steppedLevel = *level;
    if (g != 0.0)
        for (const auto& e : diagnostics.emitters)
        {
            if (e.channel < 0 || static_cast<std::size_t>(e.channel) >= steppedLevel.size())
                continue;
            const auto& d = e.match.diffuse;
            auto& bands = steppedLevel[static_cast<std::size_t>(e.channel)];
            out << "abx step: emitter " << e.channel << " g " << g
                << " dB; specular share of E_target per band:";
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            {
                const double spec = d.bandsSpecularEnergy[b], diff = d.bandsDiffuseEnergy[b];
                const double ref = d.bandsDiffuseReference[b];
                out << ' ' << (spec + diff > 0.0 ? spec / (spec + diff) : 0.0);
                if (spec == 0.0)
                {
                    bands[b] = k * ref;
                    continue;
                }
                if (diff <= 0.0 || ref <= 0.0)
                {
                    error = "--abx-step-db: emitter " + std::to_string(e.channel) + " band "
                            + std::to_string(b)
                            + " has a specular-only tail, which useDiffuseLevel cannot step";
                    return false;
                }
                const double steppedRef = k * ref + (k - 1.0) * spec * (ref / diff); // reference units
                if (!(steppedRef >= 0.0))
                {
                    error = "--abx-step-db: a " + std::to_string(g) + " dB step of emitter "
                            + std::to_string(e.channel) + " band " + std::to_string(b)
                            + " would need a negative diffuse energy (specular share too high)";
                    return false;
                }
                bands[b] = steppedRef;
            }
            out << "\n";
        }
    staged.useUnitDecays(staged.unitDecays());
    staged.useDiffuseLevel(steppedLevel);
    sim::HybridDiagnostics steppedDiagnostics;
    stepped = staged.assemble(&steppedDiagnostics);
    for (const auto& e : steppedDiagnostics.emitters)
        for (const auto& u : diagnostics.emitters)
            if (u.channel == e.channel)
            {
                out << "abx step: emitter " << e.channel << " tail-energy change set per band (dB):";
                for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                {
                    const double before = u.match.bandsTargetEnergy[b], after = e.match.bandsTargetEnergy[b];
                    out << ' ' << (before > 0.0 && after > 0.0 ? 10.0 * std::log10(after / before) : 0.0);
                }
                out << "\n";
            }
    const auto bitIdentical = [](const sim::RoomIR& a, const sim::RoomIR& b) {
        if (a.taps.size() != b.taps.size())
            return false;
        for (std::size_t c = 0; c < a.taps.size(); ++c)
            if (a.taps[c].size() != b.taps[c].size()
                || (!a.taps[c].empty()
                    && std::memcmp(a.taps[c].data(), b.taps[c].data(), a.taps[c].size() * sizeof(float))
                           != 0))
                return false;
        return true;
    };
    if (g == 0.0 && !bitIdentical(stepped, ir))
    {
        error = "--abx-step-db 0: the stepped IR is not bit-identical to the unstepped one";
        return false;
    }
    return true;
}

// --provisional-ir (phase-07c-2b L4-P, validation only): the AX49 provisional IR as the plugin builds it at a
// keyless project load (ScenePipeline's synchronous decision: plan; the stage-1 solve;
// useUnitDecays(nullptr); useDiffuseLevel(the solve's level); assembleProvisional), on the plan `staged` that
// runUnchecked already checked for provisionalTiming().provisional (r1). With `exact`, the exact IR from the
// same plan at the same level (assemble(); bit-identical to buildRoomIR, AX5 "[staged]"), the end point of
// the handover.
bool buildProvisional(sim::StagedBuild& staged, sim::RoomIR& provisional, std::optional<sim::RoomIR>* exact,
                      sim::HybridDiagnostics& diagnostics, std::string& error)
{
    staged.solve();
    const std::optional<sim::EmitterBands> level = staged.diffuseLevel();
    if (!level)
    {
        error = "--provisional-ir: the scene has no diffuse tail level";
        return false;
    }
    staged.useUnitDecays(nullptr);
    staged.useDiffuseLevel(*level);
    provisional = staged.assembleProvisional(&diagnostics);
    if (exact != nullptr)
    {
        staged.useUnitDecays(nullptr);
        exact->emplace(staged.assemble());
    }
    return true;
}

// --provisional-timing: StagedBuild::provisionalTiming() and the per-band T60 the exact tail is built with.
bool writeProvisionalTiming(const std::filesystem::path& path, const sim::ProvisionalTiming& t,
                            const sim::HybridDiagnostics& diagnostics)
{
    std::ofstream os(path, std::ios::binary);
    if (!os)
        return false;
    const auto& t60 = diagnostics.decay.bandsT60S;
    const auto maxBand = static_cast<std::size_t>(std::max_element(t60.begin(), t60.end()) - t60.begin());
    os << "{\"validationOnly\":\"provisional tail, validation-only flag\",\"provisional\":"
       << (t.provisional ? "true" : "false") << ",\"mixMaxS\":";
    writeNumber(os, t.mixMaxS);
    os << ",\"t60MaxS\":";
    writeNumber(os, t.t60MaxS);
    os << ",\"fadeStartS\":";
    writeNumber(os, t.fadeStartS);
    os << ",\"endS\":";
    writeNumber(os, t.endS);
    os << ",\"exactS\":";
    writeNumber(os, t.exactS);
    os << ",\"bandsHz\":";
    writeArray(os, contract::kOctaveBandsHz);
    os << ",\"bandsT60S\":";
    writeArray(os, t60);
    os << ",\"t60MaxBandHz\":";
    writeNumber(os, contract::kOctaveBandsHz[maxBand]);
    os << ",\"sampleRate\":";
    writeNumber(os, diagnostics.sampleRate);
    os << "}\n";
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
           "               realised k_eff per band; realised sigma, per-axis energy shares, k_real at\n"
           "               the expected-rule t_mix, the AX22 fallback, its cap time and the handover time\n"
           "  --no-air-absorption  validation only: switch off air absorption (AX4 keeps it on)\n"
           "  --tail-only  validation only, --mode omni: write just the matched late tail (no early part,\n"
           "               no crossfade), for decay-time ensembles\n"
           "  --tail-level diffuse|ax16  validation only, --mode omni: ax16 matches the tail level on the\n"
           "               specular + AX16 scattered entries as Phase 04 did (no diffuse solve); the\n"
           "               product and the default use the propagated diffuse energy (AX37, phase 05h)\n"
           "  --diffuse-histories N   validation only, --mode omni: run the diffuse solve with a fixed N "
           "histories\n"
           "                            (a multiple of 64; no pilot, no cap) instead of the AX41 joint rule\n"
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
           "  --abx-step-db g  validation only (phase-07c-2 D-W2, the AX47 self-ABX), --mode omni: a "
           "uniform\n"
           "               g dB step of the tail energy in all 8 bands (a second IrSet of the same build "
           "through\n"
           "               the diffuse level; the early part unchanged). With --in/--out (needs\n"
           "               --realtime-emulation, a fixed --block and --abx-step-sample N): the render starts "
           "on\n"
           "               the unstepped IR and fades to the stepped one from output sample N (a multiple "
           "of\n"
           "               P and of the block) with the shipped 30 ms equal-gain crossfade (AQ4). g = 0 is\n"
           "               bit-identical to no flag; N = 0 renders the stepped IR alone. --ir writes the\n"
           "               unstepped IR, --abx-stepped-ir <wav> the stepped one\n"
           "  --w-multiplier m  validation only, --mode omni: the diffuse solve at W_scene = 2 m W_max\n"
           "               (AX41; the D-W2 cap check at the candidate pins)\n"
           "  --provisional-ir  validation only (phase-07c-2b L4), --mode omni: every output uses the AX49\n"
           "               provisional IR (the plugin's interim tail at a keyless project load, faded out "
           "at\n"
           "               L_p) instead of the exact one. Refused where L_p >= L (no provisional there), "
           "and\n"
           "               with --diagnostics, --ensemble, --tail-only, --ensemble-emitter, --tail-level "
           "ax16,\n"
           "               --switch-scene/--switch-every, the --abx-* flags and --image-cap. Never for "
           "goldens\n"
           "  --provisional-timing <json>  with --provisional-ir: write provisionalTiming() (provisional,\n"
           "               mixMaxS, t60MaxS, fadeStartS = L_f, endS = L_p, exactS = L) and the per-band T60\n"
           "  --provisional-handover-sample N  with --provisional-ir, --in/--out, --realtime-emulation and\n"
           "               a fixed --block: the render starts on the provisional IR and fades to the exact "
           "IR\n"
           "               of the same build from output sample N (a multiple of P and of the block, at "
           "least\n"
           "               P, inside the input) with the shipped 30 ms equal-gain crossfade (AQ4), through "
           "the\n"
           "               real-time engine's IR swap. Both IRs are built before the first block: this "
           "shows\n"
           "               the DSP of the handover, not its timing. Unscored listening-pack renders only\n"
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
    build.tailLevelAx16 = options.tailLevelAx16;
    if (options.diffuseHistories)
        build.diffuseFixedHistories = static_cast<std::int64_t>(*options.diffuseHistories);
    if (options.imageCap)
        build.imageCountCapOverride = *options.imageCap;
    build.atmosphere = options.atmosphere;
    if (options.mixFloorMs)
        build.mixingFloorAfterDirectS = *options.mixFloorMs * 1e-3;
    if (options.ensembleEmitter)
        build.onlyEmitterChannel = static_cast<int>(*options.ensembleEmitter);
    // --w-multiplier (validation only): W_scene = 2 m W_max in place of the shipped 2 W_max (AX41).
    sim::diffuse::DiffuseLimits wLimits;
    if (options.wMultiplier)
    {
        wLimits.wScene = static_cast<std::int64_t>(std::llround(
            *options.wMultiplier * 2.0 * static_cast<double>(sim::diffuse::kWMaxPerEmitterProvisional)));
        build.diffuseLimitsOverride = &wLimits;
    }

    // --provisional-ir (L4-P): r5's input bound and r1 are decided here, from the plan's provisionalTiming(),
    // before any output file is opened, so a refused run leaves no file behind (Seat 5 file 14, condition
    // (a)).
    std::optional<sim::StagedBuild> provisionalPlan;
    if (options.provisionalIr)
    {
        if (options.provisionalHandoverSample && *options.provisionalHandoverSample >= input.numFrames())
        {
            err << "render_cli: --provisional-handover-sample " << *options.provisionalHandoverSample
                << " lies beyond the input (" << input.numFrames() << " samples)\n\n"
                << usage();
            return kExitUsage;
        }
        provisionalPlan.emplace(sim::StagedBuild::plan(scene, build));
        const sim::ProvisionalTiming t = provisionalPlan->provisionalTiming();
        if (!t.provisional)
        {
            err << "render_cli: --provisional-ir does not apply to this scene: L_p " << t.endS << " s >= L "
                << t.exactS << " s, so the exact tail is built in the provisional's place (AX49) and there "
                << "is no provisional IR to render (usage error, exit 1: the scene itself is valid)\n";
            return kExitUsage;
        }
        out << "provisional tail, validation-only flag: t_mix,e,max " << t.mixMaxS << " s, T60_max "
            << t.t60MaxS << " s, L_f " << t.fadeStartS << " s, L_p " << t.endS << " s, L " << t.exactS
            << " s\n";
    }

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
    sim::RoomIR ir;
    std::optional<sim::RoomIR> steppedIr;
    std::optional<sim::RoomIR> exactIr; // --provisional-handover-sample: the handover's end point
    if (options.abxStepDb)
    {
        std::string error;
        steppedIr.emplace();
        if (!buildAbxStep(scene, build, *options.abxStepDb, ir, *steppedIr, diagnostics, out, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitUsage;
        }
        if (!options.abxSteppedIrPath.empty())
        {
            Audio steppedAudio;
            steppedAudio.sampleRate = static_cast<std::uint32_t>(steppedIr->sampleRate);
            steppedAudio.channels = steppedIr->taps;
            if (!writeWavFloat32(options.abxSteppedIrPath, steppedAudio, error))
            {
                err << "render_cli: " << error << "\n";
                return kExitIo;
            }
            out << "wrote stepped IR " << options.abxSteppedIrPath << "\n";
        }
    }
    else if (provisionalPlan)
    {
        std::string error;
        if (!buildProvisional(*provisionalPlan, ir, options.provisionalHandoverSample ? &exactIr : nullptr,
                              diagnostics, error))
        {
            err << "render_cli: " << error << "\n";
            return kExitUsage;
        }
        if (!options.provisionalTimingPath.empty())
        {
            if (!writeProvisionalTiming(options.provisionalTimingPath, provisionalPlan->provisionalTiming(),
                                        diagnostics))
            {
                err << "render_cli: cannot write '" << options.provisionalTimingPath << "'\n";
                return kExitIo;
            }
            out << "wrote provisional timing " << options.provisionalTimingPath << "\n";
        }
    }
    else if (!options.ensemble)
        ir = sim::buildRoomIR(scene, build, &diagnostics);

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
            // g = 0 requests no second IrSet: the stepped IrSet is then bit-identical to the first (asserted
            // by buildAbxStep), and an equal-gain fade between two equal IrSets need not round to them.
            const bool step = steppedIr && *options.abxStepDb != 0.0;
            const sim::RoomIR* const target = step ? &*steppedIr : (exactIr ? &*exactIr : nullptr);
            if (!renderRealtime(ir, switchScene ? &other : nullptr, target, options, input.channels,
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
