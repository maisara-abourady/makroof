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
        ism::ImageSourceOptions iso;
        iso.maxOrder = scene.render.maxReflectionOrder;
        iso.gain = std::pow(10.0, emitter.gainDb / 20.0);
        iso.airAbsorption = options.airAbsorption;
        sets[static_cast<std::size_t>(emitter.channel)] = ism::computeImageSources(
            scene.room, emitter.position, scene.listener.position, iso);
    }
    return sets;
}

RoomIR buildRoomIR(const contract::SceneDescription& scene, const BuildOptions& options)
{
    if (!isSupportedSampleRate(options.sampleRate))
        throw std::invalid_argument("unsupported sample rate " + std::to_string(options.sampleRate)
                                    + " Hz (supported: 44100, 48000, 88200, 96000)");

    if (options.kind == BuildOptions::Kind::Omni)
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
