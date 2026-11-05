#pragma once

// The Simulator's stable offline API: scene in, room impulse response out. Later phases replace the
// body of buildRoomIR() (ISM in Phase 03, tail in Phase 04, binaural in Phase 08, stereo speakers in
// Phase 09); the types and the signature stay.
//
// Phase 03: Kind::Omni renders the early reflections (image-source method). Binaural and
// StereoSpeakers are still the Phase 02 dry pass-through stub (Phases 08 and 09).
#include "contract/SceneDescription.h"
#include "sim/ism/ImageSources.h"

#include <cstddef>
#include <vector>

namespace sim {

// Supported sample rates (AX6). buildRoomIR() rejects anything else.
inline constexpr double kSupportedSampleRatesHz[] = {44100.0, 48000.0, 88200.0, 96000.0};
bool isSupportedSampleRate(double sampleRateHz) noexcept;

// A matrix of impulse responses: one per (emitter, output) pair.
//
// Emitter index e is the emitter fed by input channel e (contract Emitter::channel), so a render
// convolves input channel e with taps[e * numOutputs + out] and sums over e into output `out`.
// The pairing of ids and channels is free (AX10); the engine maps ids to outputs, not channels.
// v1: 2 emitters x 2 outputs (AX7).
struct RoomIR
{
    double sampleRate = 48000.0;
    int numEmitters = 0;
    int numOutputs = 0;
    std::vector<std::vector<float>> taps; // [emitter * numOutputs + out], all the same length

    std::size_t index(int emitter, int output) const noexcept
    {
        return static_cast<std::size_t>(emitter) * static_cast<std::size_t>(numOutputs)
               + static_cast<std::size_t>(output);
    }
    const std::vector<float>& ir(int emitter, int output) const { return taps.at(index(emitter, output)); }
    // Length in samples (0 when there are no taps).
    std::size_t length() const noexcept { return taps.empty() ? 0 : taps.front().size(); }
};

struct BuildOptions
{
    double sampleRate = 48000.0;
    // Omni: one omnidirectional receiver per output (validation, Phases 03-05). Binaural and
    // StereoSpeakers correspond to contract::OutputMode.
    enum class Kind
    {
        Omni,
        Binaural,
        StereoSpeakers
    } kind = Kind::Binaural;
    // AX4: air absorption is always on in the product. false only for validation against
    // references that don't model it (render_cli --no-air-absorption).
    bool airAbsorption = true;
};

// AX1: the earliest direct arrival (over all emitters) lands at this sample, so the
// fractional-delay kernel (16 samples either side) isn't truncated. Part of the reported latency
// from Phase 06/07.
inline constexpr int kAlignPreRollSamples = 32;

// Time of the earliest direct arrival over all emitters, |emitter - listener| / c (seconds).
double earliestDirectArrivalS(const contract::SceneDescription& scene) noexcept;

// The time that maps to sample 0 of the omni IR: earliestDirectArrivalS - kAlignPreRollSamples / fs.
double alignmentShiftS(const contract::SceneDescription& scene, double sampleRate) noexcept;

// The image sources of each emitter as the omni build uses them, indexed by emitter channel
// (AX10), with the emitter's gainDb applied. For tests and render_cli --images.
std::vector<ism::ImageSourceSet> imageSourcesByChannel(const contract::SceneDescription& scene,
                                                       const BuildOptions& options);

// The kind that corresponds to the scene's render.outputMode.
BuildOptions::Kind kindForOutputMode(contract::OutputMode mode) noexcept;

// Builds the room IR of a scene. The scene must have passed contract::validate(); the result for
// an invalid scene is unspecified (but never undefined behaviour). Throws std::invalid_argument
// for an unsupported sample rate. Deterministic: the same scene and options give the same taps.
//
// Kind::Omni (Phase 03): for each emitter, the image-source IR (orders 0..maxReflectionOrder) at
// an omnidirectional receiver at the listener, built per octave band and summed through the
// linear-phase filterbank (ism/BandRenderer.h). Both outputs of an emitter get the same IR (mono
// room preview). Time-aligned per AX1, level per AX2 (direct path at 1 m = emitter gain), air
// absorption per AX4. All taps have the length of the longest emitter IR: last arrival + kernel +
// filterbank ringing. No late tail yet (Phase 04).
//
// PHASE 02 STUB (Binaural, StereoSpeakers): a dry pass-through. The emitter with id "L" goes to
// output 0 and the emitter with id "R" to output 1, each as a unit delta at t = 0 (length 1
// sample); the other two pairs are a single 0. Positions, materials and gains are ignored.
RoomIR buildRoomIR(const contract::SceneDescription& scene, const BuildOptions& options);

} // namespace sim
