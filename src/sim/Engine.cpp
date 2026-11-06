#include "sim/Engine.h"

#include "contract/Validate.h"
#include "sim/AirAbsorption.h"
#include "sim/ism/BandRenderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>

namespace sim {

bool isSupportedSampleRate(double sampleRateHz) noexcept
{
    for (const double rate : kSupportedSampleRatesHz)
        if (sampleRateHz == rate) // exact on purpose: the rates are integers
            return true;
    return false;
}

BuildOptions::Kind kindForOutputMode(contract::OutputMode mode) noexcept
{
    switch (mode)
    {
    case contract::OutputMode::binaural:
        return BuildOptions::Kind::Binaural;
    case contract::OutputMode::stereoSpeakers:
        return BuildOptions::Kind::StereoSpeakers;
    }
    return BuildOptions::Kind::Binaural;
}

namespace {

double distance(const contract::Vec3& a, const contract::Vec3& b) noexcept
{
    const double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Float conversion that flushes values below the smallest normal float to zero (no denormals in
// an IR; |v| < 1.2e-38 is ~760 dB below full scale).
float toFloatNoDenormal(double v) noexcept
{
    return std::abs(v) < static_cast<double>(std::numeric_limits<float>::min()) ? 0.0f
                                                                                : static_cast<float>(v);
}

ism::ImageSourceOptions imageOptions(const contract::Emitter& emitter, const BuildOptions& options)
{
    ism::ImageSourceOptions iso;
    iso.gain = std::pow(10.0, emitter.gainDb / 20.0);
    iso.airAbsorption = options.airAbsorption;
    if (options.atmosphere)
        iso.airDbPerMetreOverride = bandsAirAttenuationDbPerMetre(
            options.atmosphere->temperatureC, options.atmosphere->relativeHumidityPercent);
    return iso;
}

// The Eyring decay the hybrid IR uses: AX4 atmosphere, or the validation-only override.
tail::RoomDecay roomDecay(const contract::SceneDescription& scene, const BuildOptions& options)
{
    tail::RoomDecay decay =
        options.atmosphere && options.airAbsorption
            ? tail::eyringDecay(scene.room,
                                bandsAirAttenuationDbPerMetre(options.atmosphere->temperatureC,
                                                              options.atmosphere->relativeHumidityPercent))
            : tail::eyringDecay(scene.room, options.airAbsorption);
#ifndef NDEBUG
    // Phase-05 nightly-gate self-test (scope 4): MAKROOF_TEST_BIAS_T60=<factor> scales the tail's
    // per-band T60. Debug builds only; never compiled into a release build or the plugin.
    if (const char* bias = std::getenv("MAKROOF_TEST_BIAS_T60"))
    {
        const double factor = std::strtod(bias, nullptr);
        if (factor > 0.0)
            for (auto& t : decay.bandsT60S)
                t *= factor;
    }
#endif
    return decay;
}

double directArrivalS(const contract::SceneDescription& scene, const contract::Emitter& emitter) noexcept
{
    return distance(emitter.position, scene.listener.position) / ism::kSpeedOfSoundMps;
}

// Scope 2/3 and AX22 for one emitter: t_mix,e, the AX20 image list, the matching, and the
// realised-k fallback. Shared by the build and imageSourcesByChannel (render_cli --images).
struct EmitterPlan
{
    tail::MixingTime mixing; // mixS = the handover actually used
    ism::ImageSourceSet set;
    tail::TailMatch match;
    contract::BandArray bandsRealisedKeffAtMix{};
    bool ismFallback = false;
    double expectedMixS = 0.0;
    double capTimeS = 0.0;
};

EmitterPlan planEmitter(const contract::SceneDescription& scene, const contract::Emitter& emitter,
                        const BuildOptions& options, const tail::RoomDecay& decay, double lengthS,
                        const contract::BandArray& bandEnergy, std::size_t cap)
{
    EmitterPlan plan;
    // Scope 2: t_mix,e from the emitter's own direct arrival. Scope 3: the AX20 image list.
    plan.mixing = tail::mixingTime(directArrivalS(scene, emitter), decay.volumeM3,
                                   options.mixingFloorAfterDirectS);
    ism::ImageSourceOptions iso = imageOptions(emitter, options);
    iso.maxArrivalTimeS = plan.mixing.mixS + tail::kCrossfadeHalfS;
    plan.set = ism::computeImageSources(scene.room, emitter.position, scene.listener.position, iso);
    plan.match = tail::matchTail(tail::energyEntries(plan.set, bandEnergy), plan.mixing, decay, lengthS);
    plan.bandsRealisedKeffAtMix = plan.match.bandsRealisedKeff;
    plan.expectedMixS = plan.mixing.mixS;

    // AX22: k_real < 19 in any of 500 Hz-2 kHz at the expected-rule t_mix,e -> ISM-only up to the
    // N_cap-th lattice image; the handover moves to max(t_mix,e, t_cap,e), the list extends with it
    // (AX20) and the tail is matched there (E_b = 0 if the window holds no energy). k_real is not
    // monotonic in t, so it is tested only at the expected-rule t_mix,e.
    if (tail::needsIsmFallback(plan.match))
    {
        plan.ismFallback = true;
        plan.capTimeS = ism::nthReflectionArrivalTimeS(scene.room, emitter.position, scene.listener.position,
                                                       cap);
        if (plan.capTimeS > plan.mixing.mixS)
        {
            plan.mixing.mixS = plan.capTimeS;
            plan.mixing.expectedKeff = tail::expectedKeff(plan.mixing.windowStartS, plan.mixing.mixS,
                                                          decay.volumeM3);
            iso.maxArrivalTimeS = plan.mixing.mixS + tail::kCrossfadeHalfS;
            plan.set = ism::computeImageSources(scene.room, emitter.position, scene.listener.position, iso);
            plan.match = tail::matchTail(tail::energyEntries(plan.set, bandEnergy), plan.mixing, decay,
                                         lengthS);
        }
    }
    return plan;
}

// The hybrid omni IR for each tail seed in `seeds` (one RoomIR per seed). Everything that doesn't
// depend on the seed (mixing times, image lists, matching, the early part, the band filters'
// spectra) is computed once. Diagnostics describe the first seed.
std::vector<RoomIR> buildHybridOmni(const contract::SceneDescription& scene, const BuildOptions& options,
                                    std::span<const std::uint32_t> seeds, HybridDiagnostics* diagnostics)
{
    const double fs = options.sampleRate;
    const int numEmitters = static_cast<int>(contract::limits::kEmitterCount);
    const ism::OctaveFilterbank filterbank(fs);
    const contract::BandArray bandEnergy = tail::bandImpulseEnergies(filterbank);
    const double shift = alignmentShiftS(scene, fs);
    // Sample n of the IR is emission time n / fs + shift; sample j of the unit decay is emission
    // time j / fs. The tail is placed at j = n + offset, i.e. within half a sample of its emission
    // time (a level error < 0.01 dB), so the unit decay stays independent of positions (Phase 10).
    const auto offset = static_cast<std::size_t>(std::max(0.0, std::round(shift * fs)));
    const tail::RoomDecay decay = roomDecay(scene, options);
    const double lengthS = tail::tailLengthS(decay);
    const std::size_t unitLength = tail::unitDecayLength(lengthS, fs);
    const std::size_t tailEnd = unitLength > offset ? unitLength - offset : 0;
    const std::size_t cap = options.imageCountCapOverride > 0 ? options.imageCountCapOverride
                                                              : imageCountCap();
    // The band filters' spectra are only needed when noise is generated (not for a cached rebuild).
    const bool cached = options.cachedUnitDecays != nullptr
                        && options.cachedUnitDecays->size() == static_cast<std::size_t>(numEmitters)
                        && options.cachedUnitDecays->front().length() == unitLength;
    std::optional<tail::BandNoiseGenerator> generator;
    if (!cached)
        generator.emplace(filterbank, unitLength);

    struct PerEmitter
    {
        bool present = false;
        tail::MixingTime mixing;
        tail::TailMatch match;
        std::vector<double> early;
        HybridEmitterDiagnostics diag;
    };
    std::vector<PerEmitter> perChannel(static_cast<std::size_t>(numEmitters));
    std::size_t length = 1;
    for (const auto& emitter : scene.emitters)
    {
        if (emitter.channel < 0 || emitter.channel >= numEmitters)
            continue; // impossible for a validated scene
        if (options.onlyEmitterChannel >= 0 && emitter.channel != options.onlyEmitterChannel)
            continue; // validation: one emitter only
        auto& pe = perChannel[static_cast<std::size_t>(emitter.channel)];
        pe.present = true;
        EmitterPlan plan = planEmitter(scene, emitter, options, decay, lengthS, bandEnergy, cap);
        pe.mixing = plan.mixing;
        pe.match = plan.match;
        pe.diag.bandsRealisedKeffAtMix = plan.bandsRealisedKeffAtMix;
        pe.diag.imageCountCap = cap;
        pe.diag.ismFallback = plan.ismFallback;
        pe.diag.expectedMixS = plan.expectedMixS;
        pe.diag.capTimeS = plan.capTimeS;
        const ism::ImageSourceSet& set = plan.set;
        pe.diag.handoverS = pe.mixing.mixS;
        if (!options.tailOnly)
            pe.early = ism::renderImageSources(set.images, shift, filterbank);
        length = std::max({length, pe.early.size(), tailEnd});
        pe.diag.channel = emitter.channel;
        pe.diag.imageCount = set.images.size();
        pe.diag.scatteredCount = set.scattered.size();
        pe.diag.match = pe.match;
    }

    std::vector<RoomIR> irs;
    irs.reserve(seeds.size());
    for (std::size_t s = 0; s < seeds.size(); ++s)
    {
        RoomIR ir;
        ir.sampleRate = fs;
        ir.numEmitters = numEmitters;
        ir.numOutputs = 2;
        ir.taps.assign(static_cast<std::size_t>(ir.numEmitters * ir.numOutputs),
                       std::vector<float>(length, 0.0f));
        for (std::size_t e = 0; e < perChannel.size(); ++e)
        {
            auto& pe = perChannel[e];
            if (!pe.present)
                continue;
            // AX5: tailSeed (output index 0, both outputs the same) with the emitter channel as the
            // PCG32 stream.
            tail::UnitDecay generated;
            if (!cached)
                generated = generator->make(decay, tail::tailSeedForOutput(seeds[s], 0),
                                            static_cast<std::uint32_t>(e));
            const tail::UnitDecay& unit = cached ? (*options.cachedUnitDecays)[e] : generated;
            auto& taps = ir.taps[ir.index(static_cast<int>(e), 0)];
            for (std::size_t n = 0; n < length; ++n)
            {
                const double t = static_cast<double>(n) / fs + shift;
                const tail::CrossfadeWeights w = options.tailOnly ? tail::CrossfadeWeights{0.0, 1.0}
                                                                  : tail::crossfade(t, pe.mixing.mixS);
                double v = n < pe.early.size() ? w.ism * pe.early[n] : 0.0;
                if (w.tail > 0.0 && n < tailEnd)
                {
                    double sum = 0.0;
                    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                        sum += pe.match.bandsAmplitude[b] * unit.bands[b][n + offset];
                    v += w.tail * sum;
                }
                taps[n] = toFloatNoDenormal(v);
            }
            for (int o = 1; o < ir.numOutputs; ++o)
                ir.taps[ir.index(static_cast<int>(e), o)] = taps;

            if (s == 0)
            {
                // Measured check: the realisation's energy in the 10 ms centred on t_mix,e vs E_target.
                const auto centre = static_cast<std::ptrdiff_t>(std::llround(pe.mixing.mixS * fs));
                const auto half = static_cast<std::ptrdiff_t>(
                    std::llround(0.5 * tail::kMatchNormalisationS * fs));
                for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                {
                    double en = 0.0;
                    for (std::ptrdiff_t j = centre - half; j < centre + half; ++j)
                        if (j >= 0 && j < static_cast<std::ptrdiff_t>(unit.length()))
                            en += unit.bands[b][static_cast<std::size_t>(j)]
                                  * unit.bands[b][static_cast<std::size_t>(j)];
                    const double realised = pe.match.bandsAmplitude[b] * pe.match.bandsAmplitude[b] * en;
                    pe.diag.bandsRealisedOverTargetDb[b] =
                        realised > 0.0 && pe.match.bandsTargetEnergy[b] > 0.0
                            ? 10.0 * std::log10(realised / pe.match.bandsTargetEnergy[b])
                            : std::numeric_limits<double>::quiet_NaN();
                }
            }
        }
        irs.push_back(std::move(ir));
    }

    if (diagnostics != nullptr)
    {
        diagnostics->sampleRate = fs;
        diagnostics->decay = decay;
        diagnostics->tailLengthS = lengthS;
        diagnostics->alignmentShiftS = shift;
        diagnostics->irLength = length;
        diagnostics->emitters.clear();
        for (auto& pe : perChannel)
            diagnostics->emitters.push_back(pe.diag);
    }
    return irs;
}

RoomIR buildOmni(const contract::SceneDescription& scene, const BuildOptions& options)
{
    RoomIR ir;
    ir.sampleRate = options.sampleRate;
    ir.numEmitters = static_cast<int>(contract::limits::kEmitterCount);
    ir.numOutputs = 2;

    const ism::OctaveFilterbank filterbank(options.sampleRate);
    const double shift = alignmentShiftS(scene, options.sampleRate);
    const auto sets = imageSourcesByChannel(scene, options);

    std::vector<std::vector<double>> perChannel;
    std::size_t length = 1;
    for (const auto& set : sets)
    {
        perChannel.push_back(ism::renderImageSources(set.images, shift, filterbank));
        length = std::max(length, perChannel.back().size());
    }
    ir.taps.assign(static_cast<std::size_t>(ir.numEmitters * ir.numOutputs),
                   std::vector<float>(length, 0.0f));
    for (std::size_t e = 0; e < perChannel.size() && e < static_cast<std::size_t>(ir.numEmitters); ++e)
        for (int o = 0; o < ir.numOutputs; ++o)
        {
            auto& taps = ir.taps[ir.index(static_cast<int>(e), o)];
            std::transform(perChannel[e].begin(), perChannel[e].end(), taps.begin(),
                           [](double v) { return static_cast<float>(v); });
        }
    return ir;
}

} // namespace

std::vector<RoomIR> buildRoomIREnsemble(const contract::SceneDescription& scene, const BuildOptions& options,
                                        std::span<const std::uint32_t> tailSeeds)
{
    if (!isSupportedSampleRate(options.sampleRate))
        throw std::invalid_argument("unsupported sample rate " + std::to_string(options.sampleRate)
                                    + " Hz (supported: 44100, 48000, 88200, 96000)");
    if (options.kind != BuildOptions::Kind::Omni)
        throw std::invalid_argument("buildRoomIREnsemble: only Kind::Omni has a seeded tail");
    return buildHybridOmni(scene, options, tailSeeds, nullptr);
}

std::size_t imageCountCap() noexcept
{
    return ism::reflectionImageCount(kImageCountCapOrder);
}

double earliestDirectArrivalS(const contract::SceneDescription& scene) noexcept
{
    double earliest = std::numeric_limits<double>::infinity();
    for (const auto& emitter : scene.emitters)
        earliest = std::min(earliest,
                            distance(emitter.position, scene.listener.position) / ism::kSpeedOfSoundMps);
    return scene.emitters.empty() ? 0.0 : earliest;
}

double alignmentShiftS(const contract::SceneDescription& scene, double sampleRate) noexcept
{
    return earliestDirectArrivalS(scene) - static_cast<double>(kAlignPreRollSamples) / sampleRate;
}

std::vector<ism::ImageSourceSet> imageSourcesByChannel(const contract::SceneDescription& scene,
                                                       const BuildOptions& options)
{
    std::vector<ism::ImageSourceSet> sets(contract::limits::kEmitterCount);
    for (const auto& emitter : scene.emitters)
    {
        if (emitter.channel < 0 || static_cast<std::size_t>(emitter.channel) >= sets.size())
            continue; // impossible for a validated scene
        if (options.kind == BuildOptions::Kind::Omni)
        {
            // AX20/AX22: the time-bounded list of the hybrid IR, after the realised-k decision.
            // k_real is scale-free per band, so the band energies only need the right ratios.
            const tail::RoomDecay decay = roomDecay(scene, options);
            const ism::OctaveFilterbank filterbank(options.sampleRate);
            const std::size_t cap = options.imageCountCapOverride > 0 ? options.imageCountCapOverride
                                                                      : imageCountCap();
            sets[static_cast<std::size_t>(emitter.channel)] =
                planEmitter(scene, emitter, options, decay, tail::tailLengthS(decay),
                            tail::bandImpulseEnergies(filterbank), cap)
                    .set;
            continue;
        }
        ism::ImageSourceOptions iso = imageOptions(emitter, options);
        iso.maxOrder = scene.render.maxReflectionOrder;
        sets[static_cast<std::size_t>(emitter.channel)] = ism::computeImageSources(
            scene.room, emitter.position, scene.listener.position, iso);
    }
    return sets;
}

RoomIR buildRoomIR(const contract::SceneDescription& scene, const BuildOptions& options,
                   HybridDiagnostics* diagnostics)
{
    if (!isSupportedSampleRate(options.sampleRate))
        throw std::invalid_argument("unsupported sample rate " + std::to_string(options.sampleRate)
                                    + " Hz (supported: 44100, 48000, 88200, 96000)");

    if (options.kind == BuildOptions::Kind::Omni)
    {
        const std::uint32_t seed = scene.render.tailSeed;
        return std::move(
            buildHybridOmni(scene, options, std::span<const std::uint32_t>(&seed, 1), diagnostics).front());
    }
    if (options.kind == BuildOptions::Kind::OmniEarly)
        return buildOmni(scene, options);

    RoomIR ir;
    ir.sampleRate = options.sampleRate;
    ir.numEmitters = static_cast<int>(contract::limits::kEmitterCount);
    ir.numOutputs = 2;
    ir.taps.assign(static_cast<std::size_t>(ir.numEmitters * ir.numOutputs), std::vector<float>(1, 0.0f));

    // PHASE 02 STUB (Binaural, StereoSpeakers): dry pass-through, "L" -> output 0, "R" -> output 1 (see
    // Engine.h).
    for (const auto& emitter : scene.emitters)
    {
        if (emitter.channel < 0 || emitter.channel >= ir.numEmitters)
            continue; // impossible for a validated scene
        const int output = emitter.id == "L" ? 0 : (emitter.id == "R" ? 1 : -1);
        if (output < 0)
            continue; // impossible for a validated scene
        ir.taps[ir.index(emitter.channel, output)][0] = 1.0f;
    }
    return ir;
}

} // namespace sim
