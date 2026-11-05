#pragma once

// The stochastic late tail of the hybrid omni IR (AQ2; phase-04 spec, scope 3).
//
// 1. Unit decay (the object Phase 10 caches; independent of positions): seeded Gaussian white noise
//    (AX5, sim/Rng.h) split into the 8 octave bands with the Phase 03 filterbank
//    (ism::OctaveFilterbank), each band multiplied by exp(-6.91 t / T60_b) with t from emission
//    (sample 0 of the unit decay = emission time 0) and normalised to unit total energy.
// 2. Energy matching per emitter and band at t_mix,e (matchTail): band energies of the AX20 image
//    list (specular + AX16 scattered entries) in the Hann-weighted window [t_dir,e + 2.5 ms, t_mix,e],
//    referred to t_mix,e along the decay and normalised to 10 ms, against the EXPECTED (analytic)
//    energy of the unit decay per 10 ms at t_mix,e. The band amplitude E_b is then seed-independent.
// 3. Equal-power crossfade ISM -> tail over [t_mix,e - 2.5 ms, t_mix,e + 2.5 ms] (AX18).
#include "contract/SceneDescription.h"
#include "sim/ism/BandRenderer.h"
#include "sim/ism/ImageSources.h"
#include "sim/tail/Decay.h"
#include "sim/tail/MixingTime.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace sim::tail {

// IR length cap (phase-04 spec, AX6): decays longer than this are truncated.
inline constexpr double kMaxIrLengthS = 12.0;
// The tail runs until the slowest band has decayed by this much from emission.
inline constexpr double kTailDecayRangeDb = 90.0;
// The level-matching normalisation window: energies are "per 10 ms".
inline constexpr double kMatchNormalisationS = 0.010;
// ln(10^6) = 13.8155: energy decays by 60 dB per T60 (exp(-13.82 t / T60)); the amplitude
// envelope is exp(-6.91 t / T60) with 6.91 = ln(10^3).
inline constexpr double kEnergyDecayPerT60 = 13.815510557964274;
inline constexpr double kAmplitudeDecayPerT60 = 0.5 * kEnergyDecayPerT60;

// Length of the unit decay in seconds from emission: until the slowest band has decayed 90 dB
// (1.5 T60_max), capped at 12 s.
double tailLengthS(const RoomDecay& decay) noexcept;

// Phase 08 hook: per-output seed offset for decorrelated tails, seed ^ (outputIndex * 0x9E3779B9)
// (32-bit). The omni IR uses outputIndex 0 for both outputs (mono preview). The emitter index
// selects the PCG32 stream (AX5: "tailSeed combined with the emitter index").
std::uint32_t tailSeedForOutput(std::uint32_t tailSeed, int outputIndex) noexcept;

// The unmatched, unit-energy per-band decay. Depends only on V, S, abar_b, m_b (through T60_b),
// the seed, the emitter stream and the sample rate. bands[b][j] is the value at emission time
// j / sampleRate; sum_j bands[b][j]^2 = 1 for every band.
struct UnitDecay
{
    double sampleRate = 48000.0;
    double lengthS = 0.0; // L_IR (s from emission)
    contract::BandArray bandsT60S{};
    std::array<std::vector<double>, contract::kNumOctaveBands> bands;

    std::size_t length() const noexcept { return bands[0].size(); }
};

UnitDecay makeUnitDecay(const RoomDecay& decay, std::uint32_t seed, std::uint32_t emitterStream,
                        const ism::OctaveFilterbank& filterbank);

// Band energy of a unit impulse: sum_n B_b[n]^2 of the filterbank's band filter. The band energy of
// an image of per-band pressure amplitude a_b is a_b^2 * bandImpulseEnergy[b] (squared pressure of
// the band-filtered image summed over samples), the same quantity the unit decay is normalised in.
contract::BandArray bandImpulseEnergies(const ism::OctaveFilterbank& filterbank);

// One energy entry of the matching (phase-04 scope 3.1): the specular or the AX16 scattered energy
// of an image path, as band energies, at the path's specular arrival time (from emission).
struct EnergyEntry
{
    double timeS = 0.0;
    contract::BandArray bandsEnergy{};
};

// Entries of an image set: specular a_b^2 g_b for every image and scattered E_b g_b for every
// scattered-energy record, g = bandImpulseEnergies.
std::vector<EnergyEntry> energyEntries(const ism::ImageSourceSet& set, const contract::BandArray& bandEnergy);

// Hann taper of the matching window [startS, endS]: sin^2(pi (t - start) / (end - start)) inside,
// 0 outside (and at both ends).
double matchWindow(double t, double startS, double endS) noexcept;

// Expected energy per 10 ms of the unit decay at emission time tS (the realisation's own energy is
// not used): 0.010 (13.82 / T60) e^(-13.82 t / T60) / (1 - e^(-13.82 L / T60)).
double expectedUnitEnergyPer10ms(double t60S, double tS, double lengthS) noexcept;

struct TailMatch
{
    MixingTime mixing;
    double expectedSigmaDb = 0.0;                  // 4.34 / sqrt(expected k_eff), every band
    contract::BandArray bandsTargetEnergy{};       // E_target,b: band energy per 10 ms at t_mix,e
    contract::BandArray bandsExpectedUnitEnergy{}; // ebar_b
    contract::BandArray bandsAmplitude{};          // E_b, with E_b^2 ebar_b = E_target,b
    std::array<int, contract::kNumOctaveBands> bandsNonZeroEntries{}; // realised, in the window
    contract::BandArray bandsRealisedKeff{}; // (sum x)^2 / sum x^2 of the weighted entries
};

// Energy matching of one emitter (phase-04 scope 3, steps 1-4). Entries outside the window (the
// direct sound, early reflections before t_dir,e + 2.5 ms) don't set the level; if every entry in
// the window is zero, E_b = 0.
TailMatch matchTail(std::span<const EnergyEntry> entries, const MixingTime& mixing, const RoomDecay& decay,
                    double lengthS);

// Equal-power crossfade weights at emission time tS around mixS (AX18): tau = (t - (mix - 2.5 ms))
// / 5 ms clamped to [0, 1], ism = cos(pi tau / 2), tail = sin(pi tau / 2).
struct CrossfadeWeights
{
    double ism = 1.0;
    double tail = 0.0;
};
CrossfadeWeights crossfade(double tS, double mixS) noexcept;

} // namespace sim::tail
