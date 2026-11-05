#pragma once

// The Simulator's stable offline API: scene in, room impulse response out. Later phases replace the
// body of buildRoomIR() (ISM in Phase 03, tail in Phase 04, binaural in Phase 08, stereo speakers in
// Phase 09); the types and the signature stay.
//
// Phase 04: Kind::Omni renders the hybrid room IR (image-source early part + stochastic late tail);
// Kind::OmniEarly is the Phase 03 early-reflection-only IR, kept unchanged. Binaural and
// StereoSpeakers are still the Phase 02 dry pass-through stub (Phases 08 and 09).
#include "contract/SceneDescription.h"
#include "sim/ism/ImageSources.h"
#include "sim/tail/Decay.h"
#include "sim/tail/NoiseTail.h"

#include <array>

#include <cstddef>
#include <cstdint>
#include <span>
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
    // Omni: the hybrid IR (ISM + tail) at one omnidirectional receiver per output (validation,
    // Phases 04-05). OmniEarly: the Phase 03 early-reflection-only (ISM) IR to maxReflectionOrder.
    // Binaural and StereoSpeakers correspond to contract::OutputMode.
    enum class Kind
    {
        Omni,
        OmniEarly,
        Binaural,
        StereoSpeakers
    } kind = Kind::Binaural;
    // AX4: air absorption is always on in the product. false only for validation against
    // references that don't model it (render_cli --no-air-absorption).
    bool airAbsorption = true;
    // Kind::Omni, validation only (render_cli --tail-only): the IR holds only the matched tail
    // sum_b E_b u_b, from emission time 0 on the IR's time axis, without the early part and without
    // the crossfade. The T30 ensembles of Phase 04 measure the tail generator's decay on these
    // ("tail-only renders", phase-04.md, "Ensemble sizes").
    bool tailOnly = false;
    // Kind::Omni, validation only (render_cli --ensemble-emitter): when >= 0, only this emitter
    // channel is built; the other emitter's taps stay zero. Ensembles that analyse one emitter
    // don't pay for the other.
    int onlyEmitterChannel = -1;
    // Kind::Omni, validation only (render_cli --image-cap): overrides the AX22 image-count cap N_cap
    // (0 = kImageCountCap). For the AX22 sensitivity report at nu_r(2 i0).
    std::size_t imageCountCapOverride = 0;
    // Kind::Omni, benchmark / Phase 10 proxy only: precomputed unit decays by emitter channel
    // (tail::BandNoiseGenerator::make with the scene's seed and stream). When set and of the right
    // length, the build uses them instead of generating noise, i.e. it times a position-only rebuild
    // as AQ10 defines it. nullptr in every product path.
    const std::vector<tail::UnitDecay>* cachedUnitDecays = nullptr;
};

// AX22: the image-count cap N_cap = nu_r(i0) (Kuttruff Eq. 9.23) of the realised-k fallback, i0 the
// largest integer >= 10 at which the AQ10 workload W2 meets 50 ms on the Linux CI runner (Phase 04
// benchmark, "benchmark: AQ10 W1/W2" in test_hybrid_ir.cpp). Frozen once recorded in AX22; changing
// it is an intended output change (AX22, goldens via update_goldens.py, a BUILD_PLAN section 6 row).
inline constexpr int kImageCountCapOrder = 10;
std::size_t imageCountCap() noexcept; // nu_r(kImageCountCapOrder)

// AX1: the earliest direct arrival (over all emitters) lands at this sample, so the
// fractional-delay kernel (16 samples either side) isn't truncated. Part of the reported latency
// from Phase 06/07.
inline constexpr int kAlignPreRollSamples = 32;

// Time of the earliest direct arrival over all emitters, |emitter - listener| / c (seconds).
double earliestDirectArrivalS(const contract::SceneDescription& scene) noexcept;

// The time that maps to sample 0 of the omni IR: earliestDirectArrivalS - kAlignPreRollSamples / fs.
double alignmentShiftS(const contract::SceneDescription& scene, double sampleRate) noexcept;

// The image sources of each emitter as the omni builds use them, indexed by emitter channel
// (AX10), with the emitter's gainDb applied. For tests and render_cli --images. Kind::Omni: the
// AX20 time-bounded list (every image arriving before t_mix,e + 2.5 ms, any order); any other kind:
// orders 0..maxReflectionOrder (the Phase 03 list).
std::vector<ism::ImageSourceSet> imageSourcesByChannel(const contract::SceneDescription& scene,
                                                       const BuildOptions& options);

// The kind that corresponds to the scene's render.outputMode.
BuildOptions::Kind kindForOutputMode(contract::OutputMode mode) noexcept;

// Diagnostics of the hybrid omni build, per emitter channel (phase-04 spec: T60_b, t_mix,e, the
// matching results with sigma_dB and the realised non-zero entry count). For tests, render_cli
// --diagnostics and later UI display.
struct HybridEmitterDiagnostics
{
    int channel = 0;
    std::size_t imageCount = 0;     // images in the AX20 list (non-zero ones; the direct path always)
    std::size_t scatteredCount = 0; // AX16 scattered-energy records in it
    tail::TailMatch match;          // at the handover (t_mix,e, or max(t_mix,e, t_cap,e) in the fallback)
    // AX22: k_real per band at the expected-rule t_mix,e (the decision), whether the emitter fell
    // back to ISM-only, the cap's arrival time t_cap,e and the handover time actually used.
    contract::BandArray bandsRealisedKeffAtMix{};
    bool ismFallback = false;
    double expectedMixS = 0.0; // t_mix,e of the expected-k_eff rule (scope 2), where k_real is tested
    std::size_t imageCountCap = 0;
    double capTimeS = 0.0;
    double handoverS = 0.0;
    // Measured check (not used by the matching): the realised tail energy E_b^2 * sum u_b^2 in the
    // 10 ms centred on t_mix,e over E_target,b, in dB (0 dB = the realisation is at its expected
    // level; the band-filter ringing of the ISM is not in it).
    contract::BandArray bandsRealisedOverTargetDb{};
};

struct HybridDiagnostics
{
    double sampleRate = 48000.0;
    tail::RoomDecay decay;
    double tailLengthS = 0.0; // L_IR from emission
    double alignmentShiftS = 0.0;
    std::size_t irLength = 0;                       // samples
    std::vector<HybridEmitterDiagnostics> emitters; // by channel
};

// Builds the room IR of a scene. The scene must have passed contract::validate(); the result for
// an invalid scene is unspecified (but never undefined behaviour). Throws std::invalid_argument
// for an unsupported sample rate. Deterministic: the same scene and options give the same taps.
//
// Kind::OmniEarly (Phase 03, unchanged): for each emitter, the image-source IR (orders
// 0..maxReflectionOrder) at an omnidirectional receiver at the listener, built per octave band and
// summed through the linear-phase filterbank (ism/BandRenderer.h). Both outputs of an emitter get
// the same IR (mono room preview). Time-aligned per AX1, level per AX2 (direct path at 1 m =
// emitter gain), air absorption per AX4. All taps have the length of the longest emitter IR: last
// arrival + kernel + filterbank ringing (AX15).
//
// Kind::Omni (Phase 04): the hybrid IR. Per emitter, the AX20 time-bounded image list (every image
// arriving before t_mix,e + 2.5 ms; maxReflectionOrder has no effect) rendered as above, joined by
// an equal-power crossfade at t_mix,e (AX18) to a seeded stochastic tail (sim/tail/NoiseTail.h)
// whose per-band decay is Eyring with air absorption and whose level is energy-matched to the image
// list at t_mix,e. The tail noise is seeded with render.tailSeed (output index 0, see
// tail::tailSeedForOutput) and the emitter channel as the PCG32 stream; both outputs of an emitter
// get the same IR. Length: the tail's L_IR (1.5 T60_max from emission, capped at 12 s) or the early
// part, whichever is longer. Sub-normal float values are flushed to zero.
//
// Kind::Omni with `diagnostics` != nullptr also fills in the diagnostics.
//
// PHASE 02 STUB (Binaural, StereoSpeakers): a dry pass-through. The emitter with id "L" goes to
// output 0 and the emitter with id "R" to output 1, each as a unit delta at t = 0 (length 1
// sample); the other two pairs are a single 0. Positions, materials and gains are ignored.
RoomIR buildRoomIR(const contract::SceneDescription& scene, const BuildOptions& options,
                   HybridDiagnostics* diagnostics = nullptr);

// Kind::Omni only (validation, AX11 ensembles): the hybrid IR of `scene` for each tail seed in
// tailSeeds, element k equal to buildRoomIR with render.tailSeed = tailSeeds[k]. The seed-independent
// work (images, matching, early part, band filters) is done once. Throws std::invalid_argument for
// another kind or an unsupported sample rate.
std::vector<RoomIR> buildRoomIREnsemble(const contract::SceneDescription& scene, const BuildOptions& options,
                                        std::span<const std::uint32_t> tailSeeds);

} // namespace sim
