#include "sim/Engine.h"

#include "contract/Validate.h"
#include "sim/AirAbsorption.h"
#include "sim/conv/Denormals.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/ism/BandRenderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <future>
#include <limits>
#include <numbers>
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
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996) // getenv: read once per build, never on the audio thread
#endif
    const char* bias = std::getenv("MAKROOF_TEST_BIAS_T60");
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    if (bias != nullptr)
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
    tail::TailMatch match;         // on the specular + AX16 scattered entries (Phase 04; AX37 (5.2))
    tail::TailMatch specularMatch; // on the specular entries alone (AX37 (5.1), (5.3))
    double gainSquared = 1.0;
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
    plan.gainSquared = iso.gain * iso.gain;
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
    // AX37 (5.1), (5.3): the specular entries alone (same window, referral and t_mix,e).
    ism::ImageSourceSet specularOnly;
    specularOnly.images = plan.set.images;
    plan.specularMatch = tail::matchTail(tail::energyEntries(specularOnly, bandEnergy), plan.mixing, decay,
                                         lengthS);
    return plan;
}

// Phase 05h (AX37 (5.1)): E_target,b = the specular entries + the propagated diffuse energy (AX39,
// estimated once per scene build for both emitters, AX44), in the matching's units. `match` keeps the
// Phase 04 (AX16) statistics the AX22 decision and the diagnostics use (5.2); only the level, the
// axis shares (5.3) and the new diffuse fields change.
// The level part of the switch, shared by the solve and by a held or saved level (phase-07c-1, AX48): the
// same arithmetic on the same doubles, so a saved level equal to the solve's gives the same IR bit for bit.
void applyDiffuseLevel(tail::TailMatch& match, const EmitterPlan& plan,
                       const contract::BandArray& bandsDiffuse, const contract::BandArray& bandEnergy)
{
    auto& d = match.diffuse;
    d.computed = true;
    d.bandsAx16Energy = plan.match.bandsTargetEnergy;
    d.bandsSpecularEnergy = plan.specularMatch.bandsTargetEnergy;
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        d.bandsDiffuseEnergy[b] = bandsDiffuse[b] * bandEnergy[b];
        d.bandsDiffuseReference[b] = bandsDiffuse[b];
        match.bandsTargetEnergy[b] = d.bandsSpecularEnergy[b] + d.bandsDiffuseEnergy[b];
        match.bandsAmplitude[b] = match.bandsTargetEnergy[b] > 0.0 && match.bandsExpectedUnitEnergy[b] > 0.0
                                      ? std::sqrt(match.bandsTargetEnergy[b]
                                                  / match.bandsExpectedUnitEnergy[b])
                                      : 0.0;
    }
    match.bandsAxisShares = plan.specularMatch.bandsAxisShares; // (5.3): specular entries only
}

void switchTailLevel(tail::TailMatch& match, const EmitterPlan& plan, const diffuse::DiffuseEmitterResult& er,
                     const diffuse::DiffuseResult& result, const contract::BandArray& bandEnergy)
{
    applyDiffuseLevel(match, plan, er.bandsDiffuse, bandEnergy);
    auto& d = match.diffuse;
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        d.bandsSeDb[b] = er.bandsSeDb[b];
        d.bandsPilotSeDb[b] = er.bandsPilotSeDb[b];
        d.bandsR[b] = er.bandsR[b];
        d.bandsVov[b] = er.bandsVov[b];
        d.bandsPilotVov[b] = er.bandsPilotVov[b];
        d.bandsVovUnion[b] = er.bandsVovUnion[b];
        d.bandsSlope[b] = er.bandsSlope[b];
    }
    d.nStar = result.nStar;
    d.nNeed = result.nNeed;
    d.n = result.count.n;
    d.nCap = result.count.nCap;
    d.capHit = result.count.capHit;
    d.floorTruncated = result.count.floorTruncated;
    d.pilotFloor = result.count.pilotFloor;
    d.pilotShipped = result.count.pilotShipped;
    d.achievedSeDb = er.achievedSeDb;
    d.vovUnion = er.vovUnion;
    d.weight = er.weight;
    d.listenerDistanceM = er.listenerDistanceM;
    d.emitterDistanceM = er.emitterDistanceM;
    d.bothNear = er.bothNear;
    d.realisedWorkRatio = result.realisedWorkRatio();
    d.wPilot = result.wPilot;
    d.wFinal = result.wFinal;
    d.wScene = result.wScene;
    d.faceHash = result.faceHash;
    d.latticeImages = result.latticeImages;
    match.approximate = er.approximate;
}

// The per-emitter working state of the hybrid omni build (Phase 04/05h).
struct PerEmitter
{
    bool present = false;
    tail::MixingTime mixing;
    tail::TailMatch match;
    std::vector<double> early;
    HybridEmitterDiagnostics diag;
};

} // namespace

// Phase-07c-1 condition 12 (D-G1): the hybrid omni build as three stages over one state. Everything that
// doesn't depend on the seed (mixing times, image lists, matching, the early part, the band filters'
// spectra) is computed once for all seeds; diagnostics describe the first seed.
struct StagedBuild::State
{
    contract::SceneDescription scene;
    BuildOptions options;
    std::vector<std::uint32_t> seeds;
    bool hybrid = false; // Kind::Omni; otherwise `direct` is the whole IR
    RoomIR direct;
    bool solveDone = false;

    double fs = 0.0;
    int numEmitters = 0;
    std::optional<ism::OctaveFilterbank> filterbank;
    contract::BandArray bandEnergy{};
    double shift = 0.0;
    std::size_t offset = 0;
    tail::RoomDecay decay;
    double lengthS = 0.0;
    std::size_t unitLength = 0;
    std::size_t tailEnd = 0;
    std::size_t cap = 0;
    bool cached = false;
    std::vector<PerEmitter> perChannel;
    std::vector<EmitterPlan> plans;
    std::size_t length = 1;
    std::size_t maxEarly = 1; // max(1, the longest early part)
    std::vector<char> planned;
    // Phase-07c-1 (AX48, AX49).
    std::optional<EmitterBands> level;                              // the solve's or the given level
    std::shared_ptr<const std::vector<tail::UnitDecay>> givenUnits; // useUnitDecays()
    std::shared_ptr<const std::vector<tail::UnitDecay>> usedUnits;  // what the last assemble() played
};

namespace {

// AX37 (5.1) (i): FTZ/DAZ on for each stage, through a scoped guard that restores the caller's mode on every
// exit, including a throw, so the IR never depends on the host's mode (every stage runs in the same mode, so
// the composed stages equal the one-shot build bit for bit).
#define SPATIAL_STAGE_GUARD(options)                                                                         \
    std::optional<conv::ScopedFlushDenormals> stageGuard_;                                                   \
    if ((options).ftzGuard)                                                                                  \
    stageGuard_.emplace()

// Stage 1 of the hybrid build: decay, image-source planning, matching, the early parts.
void planHybrid(StagedBuild::State& st)
{
    const auto& scene = st.scene;
    const auto& options = st.options;
    st.fs = options.sampleRate;
    const double fs = st.fs;
    st.numEmitters = static_cast<int>(contract::limits::kEmitterCount);
    const int numEmitters = st.numEmitters;
    st.filterbank.emplace(fs);
    const ism::OctaveFilterbank& filterbank = *st.filterbank;
    st.bandEnergy = tail::bandImpulseEnergies(filterbank);
    const contract::BandArray& bandEnergy = st.bandEnergy;
    st.shift = alignmentShiftS(scene, fs);
    const double shift = st.shift;
    // Sample n of the IR is emission time n / fs + shift; sample j of the unit decay is emission
    // time j / fs. The tail is placed at j = n + offset, i.e. within half a sample of its emission
    // time (a level error < 0.01 dB), so the unit decay stays independent of positions (Phase 10).
    st.offset = static_cast<std::size_t>(std::max(0.0, std::round(shift * fs)));
    st.decay = roomDecay(scene, options);
    const tail::RoomDecay& decay = st.decay;
    st.lengthS = tail::tailLengthS(decay);
    const double lengthS = st.lengthS;
    st.unitLength = tail::unitDecayLength(lengthS, fs);
    st.tailEnd = st.unitLength > st.offset ? st.unitLength - st.offset : 0;
    const std::size_t tailEnd = st.tailEnd;
    st.cap = options.imageCountCapOverride > 0 ? options.imageCountCapOverride : imageCountCap();
    const std::size_t cap = st.cap;
    // The band filters' spectra are only needed when noise is generated (not for a cached rebuild).
    st.cached = options.cachedUnitDecays != nullptr
                && options.cachedUnitDecays->size() == static_cast<std::size_t>(numEmitters)
                && options.cachedUnitDecays->front().length() == st.unitLength;

    st.perChannel.assign(static_cast<std::size_t>(numEmitters), PerEmitter{});
    st.plans.assign(static_cast<std::size_t>(numEmitters), EmitterPlan{});
    auto& perChannel = st.perChannel;
    auto& plans = st.plans;
    std::size_t& length = st.length;
    length = 1;
    // Phase 05h: every emitter is planned (the diffuse solve is one per scene for both emitters, AX39 /
    // AX41, so a validation build of one channel matches the full build bit for bit); only the
    // present ones are rendered.
    st.planned.assign(static_cast<std::size_t>(numEmitters), 0);
    auto& planned = st.planned;
    for (const auto& emitter : scene.emitters)
    {
        if (emitter.channel < 0 || emitter.channel >= numEmitters)
            continue; // impossible for a validated scene
        auto& pe = perChannel[static_cast<std::size_t>(emitter.channel)];
        pe.present = options.onlyEmitterChannel < 0 || emitter.channel == options.onlyEmitterChannel;
        planned[static_cast<std::size_t>(emitter.channel)] = 1;
        throwIfCancelled(options.cancel); // condition 10: image-source planning, per emitter
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
        if (!options.tailOnly && pe.present)
            pe.early = ism::renderImageSources(set.images, shift, filterbank);
        length = std::max({length, pe.early.size(), tailEnd});
        st.maxEarly = std::max(st.maxEarly, pe.early.size());
        pe.diag.channel = emitter.channel;
        pe.diag.imageCount = set.images.size();
        pe.diag.scatteredCount = set.scattered.size();
        plans[static_cast<std::size_t>(emitter.channel)] = std::move(plan);
    }
}

// Stage 2 of the hybrid build: the diffuse solve (the only stage the plugin runs under the AX38 gate).
diffuse::DiffuseProblem diffuseProblem(const StagedBuild::State& st, std::vector<std::size_t>& channels);

void solveHybrid(StagedBuild::State& st)
{
    const auto& options = st.options;
    const contract::BandArray& bandEnergy = st.bandEnergy;
    auto& perChannel = st.perChannel;
    auto& plans = st.plans;
    // Phase 05h (AX37 (5.1)): the tail level from the propagated diffuse energy. One diffuse solve per
    // scene build, for the present emitters together (AX39: shared across output modes; AX44: one
    // listener-started set serves both emitters). Validation only: --tail-level ax16 keeps Phase 04's.
    if (!options.tailLevelAx16)
    {
        std::vector<std::size_t> channels;
        const diffuse::DiffuseProblem problem = diffuseProblem(st, channels);
        if (!channels.empty())
        {
            diffuse::DiffuseRunOptions run;
            run.pool = options.diffusePool;
            run.stop = options.cancel;
            diffuse::DiffuseLimits limits;
            if (options.diffuseFixedHistories > 0)
                limits.fixedHistories = options.diffuseFixedHistories; // validation only
            const diffuse::DiffuseResult result = diffuse::estimateDiffuse(problem, limits, run);
            if (result.cancelled)
                throw BuildCancelled();
            EmitterBands level{};
            for (std::size_t i = 0; i < channels.size(); ++i)
            {
                switchTailLevel(perChannel[channels[i]].match, plans[channels[i]], result.emitters[i], result,
                                bandEnergy);
                if (channels[i] < level.size())
                    level[channels[i]] = result.emitters[i].bandsDiffuse;
            }
            st.level = level;
        }
    }
}

// The diffuse problem of the planned emitters (the solve's input; AX48's key part P hashes it). `channels`
// receives the emitter channel of each problem emitter.
diffuse::DiffuseProblem diffuseProblem(const StagedBuild::State& st, std::vector<std::size_t>& channels)
{
    const auto& scene = st.scene;
    const tail::RoomDecay& decay = st.decay;
    const contract::BandArray& bandEnergy = st.bandEnergy;
    const auto& perChannel = st.perChannel;
    const auto& plans = st.plans;
    const auto& planned = st.planned;
    channels.clear();
    {
        diffuse::DiffuseProblem problem;
        problem.room.dimensions = scene.room.geometry.dimensions;
        for (std::size_t f = 0; f < contract::kNumSurfaces; ++f)
        {
            problem.room.bandsAbsorption[f] = scene.room.surfaces[f].bandsAbsorption;
            problem.room.scattering[f] = scene.room.surfaces[f].scattering;
        }
        problem.room.bandsAirEnergyPerMetre =
            decay.bandsAirEnergyPerMetre; // AX4 (or the validation override)
        problem.listener = scene.listener.position;
        for (std::size_t e = 0; e < perChannel.size(); ++e)
        {
            if (!planned[e])
                continue;
            const EmitterPlan& plan = plans[e];
            const auto it = std::find_if(scene.emitters.begin(), scene.emitters.end(), [&](const auto& em) {
                return static_cast<std::size_t>(em.channel) == e;
            });
            diffuse::DiffuseEmitter d;
            d.position = it->position;
            d.windowStartS = plan.mixing.windowStartS;
            d.mixS = plan.mixing.mixS; // after the AX22 fallback (5.2)
            d.bandsT60S = decay.bandsT60S;
            d.gainSquared = plan.gainSquared;
            // The specular window target in the reference's units: the matching's value per g_b.
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                d.bandsSpecularTarget[b] = bandEnergy[b] > 0.0
                                               ? plan.specularMatch.bandsTargetEnergy[b] / bandEnergy[b]
                                               : 0.0;
            problem.emitters.push_back(d);
            channels.push_back(e);
        }
        return problem;
    }
}

// Phase-07c-1 (AX49): the unit decays of the present emitters for one seed, by channel (absent: empty), from
// one generator; the two emitters in parallel when options.parallelEmitterSynthesis (bit-identical: make() is
// a const, pure function of its seed and stream). `post` (may be empty) runs on each emitter's decay on the
// thread that made it.
template <typename Post>
std::vector<tail::UnitDecay> synthesiseUnits(const StagedBuild::State& st,
                                             const tail::BandNoiseGenerator& generator,
                                             const tail::RoomDecay& decay, std::uint32_t seed,
                                             const Post& post)
{
    const auto& options = st.options;
    std::vector<tail::UnitDecay> units(st.perChannel.size());
    std::vector<std::size_t> present;
    for (std::size_t e = 0; e < st.perChannel.size(); ++e)
        if (st.perChannel[e].present)
            present.push_back(e);
    const auto makeOne = [&](std::size_t e) {
        tail::UnitDecay u = generator.make(decay, tail::tailSeedForOutput(seed, 0),
                                           static_cast<std::uint32_t>(e), options.cancel);
        post(u);
        return u;
    };
    if (options.parallelEmitterSynthesis && present.size() >= 2)
    {
        // One extra thread for the second emitter; its exception (BuildCancelled, bad_alloc) reaches get().
        // If the first throws, the future's destructor waits for the second (which stops at its next cancel
        // point when the build was cancelled).
        auto second = std::async(std::launch::async, [&] { return makeOne(present[1]); });
        units[present[0]] = makeOne(present[0]);
        units[present[1]] = second.get();
        for (std::size_t i = 2; i < present.size(); ++i)
            units[present[i]] = makeOne(present[i]);
    }
    else
        for (const std::size_t e : present)
            units[e] = makeOne(e);
    return units;
}

bool sameDecay(const tail::UnitDecay& u, std::size_t length, const tail::RoomDecay& decay, double fs) noexcept
{
    if (u.length() != length || std::memcmp(&u.sampleRate, &fs, sizeof(double)) != 0)
        return false;
    return std::memcmp(u.bandsT60S.data(), decay.bandsT60S.data(), sizeof(double) * contract::kNumOctaveBands)
           == 0;
}

// Stage 3 of the hybrid build: the IR assembly over given unit decays (by channel), one RoomIR. `exact` = the
// decays are this scene's own (the amplitudes of the matching apply); otherwise (the AX49 D5 bridge, a
// provisional tail normalised to the exact distribution is exact too) each band's amplitude uses the ebar of
// the decay actually played (AX48). The tail ends where each decay ends.
RoomIR mixHybrid(StagedBuild::State& st, const std::vector<tail::UnitDecay>& units, bool exact, bool measured)
{
    const auto& options = st.options;
    const double fs = st.fs;
    const double shift = st.shift;
    const std::size_t offset = st.offset;
    auto& perChannel = st.perChannel;
    std::size_t length = std::max<std::size_t>(1, st.maxEarly);
    for (std::size_t e = 0; e < perChannel.size(); ++e)
        if (perChannel[e].present && e < units.size() && units[e].length() > offset)
            length = std::max(length, units[e].length() - offset);

    RoomIR ir;
    ir.sampleRate = fs;
    ir.numEmitters = st.numEmitters;
    ir.numOutputs = 2;
    ir.taps.assign(static_cast<std::size_t>(ir.numEmitters * ir.numOutputs),
                   std::vector<float>(length, 0.0f));
    for (std::size_t e = 0; e < perChannel.size(); ++e)
    {
        auto& pe = perChannel[e];
        if (!pe.present)
            continue;
        const tail::UnitDecay& unit = units[e];
        const std::size_t tailEnd = unit.length() > offset ? unit.length() - offset : 0;
        contract::BandArray amplitude = pe.match.bandsAmplitude;
        if (!exact)
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            {
                const double ebar = tail::expectedUnitEnergyPer10ms(unit.bandsT60S[b], pe.mixing.mixS,
                                                                    unit.lengthS);
                amplitude[b] = ebar > 0.0 && pe.match.bandsTargetEnergy[b] > 0.0
                                   ? std::sqrt(pe.match.bandsTargetEnergy[b] / ebar)
                                   : 0.0;
            }
        auto& taps = ir.taps[ir.index(static_cast<int>(e), 0)];
        for (std::size_t n = 0; n < length; ++n)
        {
            if ((n & (kCancelCheckSamples - 1)) == 0)
                throwIfCancelled(options.cancel); // condition 10: the IR assembly
            const double t = static_cast<double>(n) / fs + shift;
            const tail::CrossfadeWeights w = options.tailOnly ? tail::CrossfadeWeights{0.0, 1.0}
                                                              : tail::crossfade(t, pe.mixing.mixS);
            double v = n < pe.early.size() ? w.ism * pe.early[n] : 0.0;
            if (w.tail > 0.0 && n < tailEnd)
            {
                double sum = 0.0;
                for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                    sum += amplitude[b] * unit.bands[b][n + offset];
                v += w.tail * sum;
            }
            taps[n] = toFloatNoDenormal(v);
        }
        for (int o = 1; o < ir.numOutputs; ++o)
            ir.taps[ir.index(static_cast<int>(e), o)] = taps;

        if (measured)
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
                const double realised = amplitude[b] * amplitude[b] * en;
                pe.diag.bandsRealisedOverTargetDb[b] =
                    realised > 0.0 && pe.match.bandsTargetEnergy[b] > 0.0
                        ? 10.0 * std::log10(realised / pe.match.bandsTargetEnergy[b])
                        : std::numeric_limits<double>::quiet_NaN();
            }
        }
    }
    return ir;
}

void fillDiagnostics(StagedBuild::State& st, std::size_t length, HybridDiagnostics* diagnostics)
{
    if (diagnostics == nullptr)
        return;
    diagnostics->sampleRate = st.fs;
    diagnostics->decay = st.decay;
    diagnostics->tailLengthS = st.lengthS;
    diagnostics->alignmentShiftS = st.shift;
    diagnostics->irLength = length;
    diagnostics->emitters.clear();
    for (auto& pe : st.perChannel)
        diagnostics->emitters.push_back(pe.diag);
}

// Stage 3 of the hybrid build: the unit-decay synthesis and the IR assembly, one RoomIR per seed.
std::vector<RoomIR> assembleHybrid(StagedBuild::State& st, HybridDiagnostics* diagnostics)
{
    const auto& options = st.options;
    const std::span<const std::uint32_t> seeds(st.seeds);
    for (std::size_t e = 0; e < st.perChannel.size(); ++e)
        if (st.planned[e])
            st.perChannel[e].diag.match = st.perChannel[e].match;

    // The decays to play: the phase-07c-1 given ones (cache or D5 bridge), the BuildOptions benchmark cache,
    // or a fresh synthesis per seed.
    std::shared_ptr<const std::vector<tail::UnitDecay>> given = st.givenUnits;
    if (!given && st.cached)
        given = std::shared_ptr<const std::vector<tail::UnitDecay>>(std::shared_ptr<void>{},
                                                                    options.cachedUnitDecays);
    std::optional<tail::BandNoiseGenerator> generator;
    throwIfCancelled(options.cancel); // condition 10: before the synthesis constructor
    if (!given)
        generator.emplace(*st.filterbank, st.unitLength, options.cancel);

    const auto noPost = [](tail::UnitDecay&) {};
    std::vector<RoomIR> irs;
    irs.reserve(seeds.size());
    for (std::size_t s = 0; s < seeds.size(); ++s)
    {
        std::shared_ptr<const std::vector<tail::UnitDecay>> units = given;
        bool exact = true;
        if (!units)
            units = std::make_shared<const std::vector<tail::UnitDecay>>(
                synthesiseUnits(st, *generator, st.decay, seeds[s], noPost));
        else
            for (std::size_t e = 0; e < st.perChannel.size(); ++e)
                if (st.perChannel[e].present
                    && (e >= units->size() || !sameDecay((*units)[e], st.unitLength, st.decay, st.fs)))
                    exact = false;
        if (!exact && units->size() < st.perChannel.size())
            throw std::invalid_argument("useUnitDecays: one decay per emitter channel is needed");
        irs.push_back(mixHybrid(st, *units, exact, s == 0));
        if (s == 0)
            st.usedUnits = units;
    }
    fillDiagnostics(st, irs.empty() ? 0 : irs.front().length(), diagnostics);
    return irs;
}

// Phase-07c-1 (AX49): the timing of the provisional tail.
ProvisionalTiming provisionalTimingOf(const StagedBuild::State& st) noexcept
{
    ProvisionalTiming t;
    for (const auto& pe : st.perChannel)
        if (pe.present)
            t.mixMaxS = std::max(t.mixMaxS, pe.mixing.mixS);
    t.t60MaxS = st.decay.maxT60S();
    t.fadeStartS = t.mixMaxS + kProvisionalT60Fraction * t.t60MaxS;
    t.endS = t.fadeStartS + kProvisionalFadeS;
    t.exactS = st.lengthS;
    t.provisional = t.endS < t.exactS;
    return t;
}

// Phase-07c-1 (AX49): the provisional tail's unit decays and their IR. Same generator kind, seed and emitter
// stream as the exact tail, length L_p; each band divided by sqrt(E_p,b / f_b) (E_p,b its realised energy
// over [0, L_f), f_b the exact unit decay's expected energy fraction over [0, L_f)), never scaled up for the
// energy past L_p, then faded to zero over [L_f, L_p) (raised cosine). Its energy distribution over [0, L_f)
// is then the exact one's, so the matching's amplitudes (ebar of the exact decay) apply unchanged.
RoomIR assembleProvisionalHybrid(StagedBuild::State& st, HybridDiagnostics* diagnostics)
{
    const auto& options = st.options;
    const ProvisionalTiming timing = provisionalTimingOf(st);
    const double fs = st.fs;
    const std::size_t lp = tail::unitDecayLength(timing.endS, fs);
    const std::size_t lf = std::min(lp, tail::unitDecayLength(timing.fadeStartS, fs));
    for (std::size_t e = 0; e < st.perChannel.size(); ++e)
        if (st.planned[e])
            st.perChannel[e].diag.match = st.perChannel[e].match;
    throwIfCancelled(options.cancel);
    const tail::BandNoiseGenerator generator(*st.filterbank, lp, options.cancel);
    const tail::RoomDecay& decay = st.decay;
    const double lengthS = st.lengthS;
    const auto post = [&](tail::UnitDecay& u) {
        u.lengthS = lengthS; // the exact decay's L: its ebar is the one the amplitudes use
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            auto& band = u.bands[b];
            double ep = 0.0;
            for (std::size_t j = 0; j < lf; ++j)
                ep += band[j] * band[j];
            const double k = tail::kEnergyDecayPerT60 / decay.bandsT60S[b];
            const double fb = (1.0 - std::exp(-k * timing.fadeStartS)) / (1.0 - std::exp(-k * lengthS));
            const double scale = ep > 0.0 && fb > 0.0 ? 1.0 / std::sqrt(ep / fb) : 0.0;
            const std::size_t fadeLen = lp > lf ? lp - lf : 0;
            for (std::size_t j = 0; j < lp; ++j)
            {
                double g = scale;
                if (j >= lf)
                    g *= 0.5
                         * (1.0
                            + std::cos(std::numbers::pi * static_cast<double>(j - lf + 1)
                                       / static_cast<double>(fadeLen + 1)));
                band[j] *= g;
            }
        }
    };
    auto units = std::make_shared<const std::vector<tail::UnitDecay>>(
        synthesiseUnits(st, generator, decay, st.seeds.front(), post));
    // exact = true: the provisional is normalised to the exact distribution, so the matching's amplitudes
    // hold.
    RoomIR ir = mixHybrid(st, *units, true, true);
    st.usedUnits = std::move(units); // the provisional decays (tests); never cached as exact by the plugin
    fillDiagnostics(st, ir.length(), diagnostics);
    return ir;
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
    std::optional<conv::ScopedFlushDenormals> flushDenormals; // AX37 (5.1) (i), as buildRoomIR
    if (options.ftzGuard)
        flushDenormals.emplace();
    if (!isSupportedSampleRate(options.sampleRate))
        throw std::invalid_argument("unsupported sample rate " + std::to_string(options.sampleRate)
                                    + " Hz (supported: 44100, 48000, 88200, 96000)");
    if (options.kind != BuildOptions::Kind::Omni)
        throw std::invalid_argument("buildRoomIREnsemble: only Kind::Omni has a seeded tail");
    auto st = std::make_unique<StagedBuild::State>();
    st->scene = scene;
    st->options = options;
    st->seeds.assign(tailSeeds.begin(), tailSeeds.end());
    planHybrid(*st);
    if (!options.tailLevelAx16)
        solveHybrid(*st);
    return assembleHybrid(*st, nullptr);
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

StagedBuild::StagedBuild(std::unique_ptr<State> state)
    : state_(std::move(state))
{}
StagedBuild::StagedBuild(StagedBuild&&) noexcept = default;
StagedBuild& StagedBuild::operator=(StagedBuild&&) noexcept = default;
StagedBuild::~StagedBuild() = default;

StagedBuild StagedBuild::plan(const contract::SceneDescription& scene, const BuildOptions& options)
{
    SPATIAL_STAGE_GUARD(options);
    if (!isSupportedSampleRate(options.sampleRate))
        throw std::invalid_argument("unsupported sample rate " + std::to_string(options.sampleRate)
                                    + " Hz (supported: 44100, 48000, 88200, 96000)");
    auto st = std::make_unique<State>();
    st->scene = scene;
    st->options = options;
    if (options.kind == BuildOptions::Kind::Omni)
    {
        st->hybrid = true;
        st->seeds.assign(1, scene.render.tailSeed);
        planHybrid(*st);
        return StagedBuild(std::move(st));
    }
    st->solveDone = true;
    if (options.kind == BuildOptions::Kind::OmniEarly)
    {
        st->direct = buildOmni(scene, options);
        return StagedBuild(std::move(st));
    }

    RoomIR& ir = st->direct;
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
    return StagedBuild(std::move(st));
}

bool StagedBuild::needsSolve() const noexcept
{
    return state_ && state_->hybrid && !state_->solveDone && !state_->options.tailLevelAx16;
}

void StagedBuild::solve(diffuse::ThreadPool* pool)
{
    if (!needsSolve())
    {
        if (state_)
            state_->solveDone = true;
        return;
    }
    SPATIAL_STAGE_GUARD(state_->options);
    diffuse::ThreadPool* const planned = state_->options.diffusePool;
    if (pool != nullptr)
        state_->options.diffusePool = pool;
    try
    {
        solveHybrid(*state_);
    }
    catch (...)
    {
        state_->options.diffusePool = planned;
        throw;
    }
    state_->options.diffusePool = planned;
    state_->solveDone = true;
}

RoomIR StagedBuild::assemble(HybridDiagnostics* diagnostics)
{
    if (!state_->hybrid)
        return std::move(state_->direct);
    if (!state_->level)
        solve(); // a no-op for a tailLevelAx16 build; skipped when useDiffuseLevel() gave the level
    SPATIAL_STAGE_GUARD(state_->options);
    return std::move(assembleHybrid(*state_, diagnostics).front());
}

namespace {

// FNV-1a 64 over raw bytes (AX48's canonical hashes: bit for bit, so -0.0 != 0.0 and every rounding counts).
struct Fnv1a
{
    std::uint64_t h = 0xcbf29ce484222325ull;
    void bytes(const void* p, std::size_t n) noexcept
    {
        const auto* c = static_cast<const unsigned char*>(p);
        for (std::size_t i = 0; i < n; ++i)
        {
            h ^= c[i];
            h *= 0x100000001b3ull;
        }
    }
    void f64(double v) noexcept
    {
        std::uint64_t bits = 0;
        std::memcpy(&bits, &v, sizeof bits);
        bytes(&bits, sizeof bits);
    }
    void bands(const contract::BandArray& a) noexcept
    {
        for (const double v : a)
            f64(v);
    }
    void vec(const contract::Vec3& v) noexcept
    {
        f64(v.x);
        f64(v.y);
        f64(v.z);
    }
};

} // namespace

std::uint64_t StagedBuild::problemHash() const noexcept
{
    if (!state_ || !state_->hybrid)
        return 0;
    std::vector<std::size_t> channels;
    diffuse::DiffuseProblem problem;
    try
    {
        problem = diffuseProblem(*state_, channels);
    }
    catch (...)
    {
        return 0;
    }
    Fnv1a f;
    f.vec(problem.room.dimensions);
    for (const auto& a : problem.room.bandsAbsorption)
        f.bands(a);
    for (const double v : problem.room.scattering)
        f.f64(v);
    f.bands(problem.room.bandsAirEnergyPerMetre);
    f.vec(problem.listener);
    for (std::size_t i = 0; i < problem.emitters.size(); ++i)
    {
        const auto& e = problem.emitters[i];
        const std::uint64_t ch = channels[i];
        f.bytes(&ch, sizeof ch);
        f.vec(e.position);
        f.f64(e.windowStartS);
        f.f64(e.mixS);
        f.bands(e.bandsT60S);
        f.f64(e.gainSquared);
        f.bands(e.bandsSpecularTarget);
    }
    return f.h;
}

void StagedBuild::useDiffuseLevel(const EmitterBands& bandsDiffuse)
{
    if (!state_ || !state_->hybrid || state_->options.tailLevelAx16)
        return;
    auto& st = *state_;
    for (std::size_t e = 0; e < st.perChannel.size() && e < bandsDiffuse.size(); ++e)
        if (st.planned[e])
            applyDiffuseLevel(st.perChannel[e].match, st.plans[e], bandsDiffuse[e], st.bandEnergy);
    st.level = bandsDiffuse; // the solve stays pending: solve() may still run and replace this level
}

std::optional<EmitterBands> StagedBuild::diffuseLevel() const
{
    if (!state_)
        return std::nullopt;
    return state_->level;
}

ProvisionalTiming StagedBuild::provisionalTiming() const noexcept
{
    if (!state_ || !state_->hybrid)
        return {};
    return provisionalTimingOf(*state_);
}

RoomIR StagedBuild::assembleProvisional(HybridDiagnostics* diagnostics)
{
    if (!state_->hybrid || !provisionalTimingOf(*state_).provisional || state_->options.tailOnly)
        return assemble(diagnostics);
    if (!state_->level)
        solve();
    SPATIAL_STAGE_GUARD(state_->options);
    return assembleProvisionalHybrid(*state_, diagnostics);
}

void StagedBuild::useUnitDecays(std::shared_ptr<const std::vector<tail::UnitDecay>> units)
{
    if (state_ && state_->hybrid)
        state_->givenUnits = std::move(units);
}

bool StagedBuild::unitDecaysExact() const noexcept
{
    if (!state_ || !state_->hybrid || !state_->givenUnits)
        return false;
    const auto& units = *state_->givenUnits;
    for (std::size_t e = 0; e < state_->perChannel.size(); ++e)
        if (state_->perChannel[e].present
            && (e >= units.size() || !sameDecay(units[e], state_->unitLength, state_->decay, state_->fs)))
            return false;
    return true;
}

std::shared_ptr<const std::vector<tail::UnitDecay>> StagedBuild::unitDecays() const
{
    return state_ ? state_->usedUnits : nullptr;
}

RoomIR buildRoomIR(const contract::SceneDescription& scene, const BuildOptions& options,
                   HybridDiagnostics* diagnostics)
{
    // Phase-07c-1 condition 12: the composition of the three stages (one-shot callers: render_cli, tests).
    StagedBuild build = StagedBuild::plan(scene, options);
    build.solve();
    return build.assemble(diagnostics);
}

} // namespace sim
