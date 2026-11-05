#include "sim/Engine.h"

#include "contract/Validate.h"
#include "sim/ism/BandRenderer.h"

#include <algorithm>
#include <cmath>
#include <limits>
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
    return iso;
}

double directArrivalS(const contract::SceneDescription& scene, const contract::Emitter& emitter) noexcept
{
    return distance(emitter.position, scene.listener.position) / ism::kSpeedOfSoundMps;
}

RoomIR buildHybridOmni(const contract::SceneDescription& scene, const BuildOptions& options,
                       HybridDiagnostics* diagnostics)
{
    RoomIR ir;
    ir.sampleRate = options.sampleRate;
    ir.numEmitters = static_cast<int>(contract::limits::kEmitterCount);
    ir.numOutputs = 2;

    const double fs = options.sampleRate;
    const ism::OctaveFilterbank filterbank(fs);
    const contract::BandArray bandEnergy = tail::bandImpulseEnergies(filterbank);
    const double shift = alignmentShiftS(scene, fs);
    // Sample n of the IR is emission time n / fs + shift; sample j of the unit decay is emission
    // time j / fs. The tail is placed at j = n + offset, i.e. within half a sample of its emission
    // time (a level error < 0.01 dB, the unit decay stays independent of positions for Phase 10).
    const auto offset = static_cast<std::size_t>(std::max(0.0, std::round(shift * fs)));
    const tail::RoomDecay decay = tail::eyringDecay(scene.room, options.airAbsorption);
    const double lengthS = tail::tailLengthS(decay);

    struct PerEmitter
    {
        std::vector<double> samples;
        HybridEmitterDiagnostics diag;
    };
    std::vector<PerEmitter> perChannel(static_cast<std::size_t>(ir.numEmitters));
    std::size_t length = 1;
    for (const auto& emitter : scene.emitters)
    {
        if (emitter.channel < 0 || emitter.channel >= ir.numEmitters)
            continue; // impossible for a validated scene
        auto& out = perChannel[static_cast<std::size_t>(emitter.channel)];

        // Scope 2: t_mix,e from the emitter's own direct arrival. Scope 3: the AX20 image list.
        const tail::MixingTime mixing = tail::mixingTime(directArrivalS(scene, emitter), decay.volumeM3);
        ism::ImageSourceOptions iso = imageOptions(emitter, options);
        iso.maxArrivalTimeS = mixing.mixS + tail::kCrossfadeHalfS;
        const ism::ImageSourceSet set = ism::computeImageSources(scene.room, emitter.position,
                                                                 scene.listener.position, iso);

        const auto entries = tail::energyEntries(set, bandEnergy);
        const tail::TailMatch match = tail::matchTail(entries, mixing, decay, lengthS);
        const tail::UnitDecay unit = tail::makeUnitDecay(
            decay, tail::tailSeedForOutput(scene.render.tailSeed, 0),
            static_cast<std::uint32_t>(emitter.channel), filterbank);

        std::vector<double> early = ism::renderImageSources(set.images, shift, filterbank);
        const std::size_t tailEnd = unit.length() > offset ? unit.length() - offset : 0;
        out.samples.assign(std::max(early.size(), tailEnd), 0.0);
        for (std::size_t n = 0; n < out.samples.size(); ++n)
        {
            const double t = static_cast<double>(n) / fs + shift;
            const tail::CrossfadeWeights w = options.tailOnly ? tail::CrossfadeWeights{0.0, 1.0}
                                                              : tail::crossfade(t, mixing.mixS);
            double v = n < early.size() ? w.ism * early[n] : 0.0;
            if (w.tail > 0.0 && n < tailEnd)
            {
                double sum = 0.0;
                for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                    sum += match.bandsAmplitude[b] * unit.bands[b][n + offset];
                v += w.tail * sum;
            }
            out.samples[n] = v;
        }
        length = std::max(length, out.samples.size());

        out.diag.channel = emitter.channel;
        out.diag.imageCount = set.images.size();
        out.diag.scatteredCount = set.scattered.size();
        out.diag.match = match;
        // Measured check: the realisation's energy in the 10 ms centred on t_mix,e vs E_target.
        const auto centre = static_cast<std::ptrdiff_t>(std::llround(mixing.mixS * fs));
        const auto half = static_cast<std::ptrdiff_t>(std::llround(0.5 * tail::kMatchNormalisationS * fs));
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            double e = 0.0;
            for (std::ptrdiff_t j = centre - half; j < centre + half; ++j)
                if (j >= 0 && j < static_cast<std::ptrdiff_t>(unit.length()))
                    e += unit.bands[b][static_cast<std::size_t>(j)]
                         * unit.bands[b][static_cast<std::size_t>(j)];
            const double realised = match.bandsAmplitude[b] * match.bandsAmplitude[b] * e;
            out.diag.bandsRealisedOverTargetDb[b] =
                realised > 0.0 && match.bandsTargetEnergy[b] > 0.0
                    ? 10.0 * std::log10(realised / match.bandsTargetEnergy[b])
                    : std::numeric_limits<double>::quiet_NaN();
        }
    }

    ir.taps.assign(static_cast<std::size_t>(ir.numEmitters * ir.numOutputs),
                   std::vector<float>(length, 0.0f));
    for (std::size_t e = 0; e < perChannel.size(); ++e)
        for (int o = 0; o < ir.numOutputs; ++o)
        {
            auto& taps = ir.taps[ir.index(static_cast<int>(e), o)];
            std::transform(perChannel[e].samples.begin(), perChannel[e].samples.end(), taps.begin(),
                           toFloatNoDenormal);
        }

    if (diagnostics != nullptr)
    {
        diagnostics->sampleRate = fs;
        diagnostics->decay = decay;
        diagnostics->tailLengthS = lengthS;
        diagnostics->alignmentShiftS = shift;
        diagnostics->irLength = length;
        diagnostics->emitters.clear();
        for (auto& p : perChannel)
            diagnostics->emitters.push_back(p.diag);
    }
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
        ism::ImageSourceOptions iso = imageOptions(emitter, options);
        if (options.kind == BuildOptions::Kind::Omni)
        {
            // AX20: the time-bounded list of the hybrid IR.
            const tail::MixingTime mixing = tail::mixingTime(
                directArrivalS(scene, emitter),
                tail::eyringDecay(scene.room, options.airAbsorption).volumeM3);
            iso.maxArrivalTimeS = mixing.mixS + tail::kCrossfadeHalfS;
        }
        else
        {
            iso.maxOrder = scene.render.maxReflectionOrder;
        }
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
        return buildHybridOmni(scene, options, diagnostics);
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
