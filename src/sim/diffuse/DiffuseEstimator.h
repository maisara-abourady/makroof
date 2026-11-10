#pragma once

// Propagated diffuse energy in the Phase 04 matching window (AX37 (5.1)), estimated by a seeded Monte
// Carlo with next-event estimation: the ℓ -> 0 form of tools/acoustics/ref_hybrid.py (AX39).
//
// Model (Kuttruff §5.2, §2.7; Eqs. 4.24, 4.29, 4.35; AX4 air). A path leaves its start point
// uniformly over the sphere with weight 4π (unit intensity per steradian, AX2). At every wall hit
// the incident energy E is split: s(1 - a) is emitted diffusely (Lambert) and gathered at the other
// end directly and over every specular route, i.e. at that end's lattice images in front of the
// face, each with prod((1 - a)(1 - s))^hits and air exp(-m r): cos θ / (π r²) per unit diffusely
// emitted energy, weighted by the matching window (Hann over [t_dir,e + 2.5 ms, t_mix,e], referred
// to t_mix,e with the Eyring rate, per 10 ms; src/sim/tail/NoiseTail.cpp matchTail). The path then
// continues with weight E (1 - a), diffusely (Lambert) with probability s and specularly otherwise
// (unweighted branching: s is broadband per surface, AX17). Only the diffuse energy is estimated;
// the specular entries stay exact (ISM).
//
// History h (AX41): the emitter-started path h of every emitter plus the listener-started path h,
// which gathers at each emitter's images (one set for both emitters, AX44). Per emitter the score
// is w·fwd + (1 - w)·rev, w = d_L² / (d_L² + d_E²) (NW-4C, AX44). Work = image evaluations.
//
// Determinism (AX39): D1 key (seed, end, emitter, path, hit, attempt) and libm-free path decisions
// (Sampling.h); D2 fp-contract off / precise (CMake); D4 64-history blocks, reduced in history order,
// independent of the thread count; D5 face-sequence hash; D6 stop flag between blocks; D7 N from
// 64-bit integer work counts. The key is fixed (AX40): nothing here depends on tailSeed.
//
// Units: E_target in the reference's units (squared pressure re 1 m, per 10 ms; no band-filter
// energy); the caller scales by bandImpulseEnergies (NoiseTail.h) where the matching needs it.
// Runs on the builder thread only (it allocates); never on the audio thread.
#include "contract/SceneDescription.h"

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

namespace sim::diffuse {

class ThreadPool;

inline constexpr std::uint64_t kDiffuseSeed = 0x5EED;    // AX40: fixed, independent of tailSeed
inline constexpr std::int64_t kBlockHistories = 64;      // AX39 D4
inline constexpr std::int64_t kFinalRangeStart = 8000;   // AX41: the final range is [8 000, 8 000 + N)
inline constexpr std::int64_t kUnionVovHistories = 8000; // AX44: VOV_union over the first 8 000
inline constexpr std::int64_t kPilotFloor = 1000;        // AX41: pilot-floor flag below this n*
inline constexpr std::int64_t kNStarMax = 1024; // AX41 n*_max (provisional until the C++ re-derivation)
inline constexpr std::int64_t kWMaxPerEmitterProvisional = 3'050'000; // AX41 provisional W_max
inline constexpr double kSeTargetDb = 0.083;                          // AX42 target SE
inline constexpr double kBothNearM = 0.70;                            // AX44
inline constexpr double kApproximateSeDb = 0.33;                      // AX44 U, capped branch
inline constexpr double kVovLimit = 0.1;                              // AX41 / AX44
// 10 / ln 10: dB per unit relative energy (the prototype rounded it to 4.343).
inline constexpr double kDbPerRelative = 4.342944819032518;

struct DiffuseRoom
{
    contract::Vec3 dimensions;
    std::array<contract::BandArray, contract::kNumSurfaces> bandsAbsorption{};
    std::array<double, contract::kNumSurfaces> scattering{};
    contract::BandArray bandsAirEnergyPerMetre{}; // m_b (1/m), AX4
};

struct DiffuseEmitter
{
    contract::Vec3 position;
    double windowStartS = 0.0; // t_dir,e + 2.5 ms
    double mixS = 0.0;         // t_mix,e (after the AX22 fallback, if any)
    contract::BandArray bandsT60S{};
    double gainSquared = 1.0;
    // The exact specular window target (same units), used only for the SE in dB of the total.
    contract::BandArray bandsSpecularTarget{};
};

struct DiffuseProblem
{
    DiffuseRoom room;
    contract::Vec3 listener;
    std::vector<DiffuseEmitter> emitters; // 1 or 2
};

struct DiffuseLimits
{
    std::int64_t wScene = 2 * kWMaxPerEmitterProvisional; // W_scene = 2 W_max (AX41)
    std::int64_t nStarMax = kNStarMax; // clamped to [64, 8 000]: the pilot stays below the final range
    double seTargetDb = kSeTargetDb;
    // Validation only: a fixed number of histories from history `fixedStart` (a multiple of 64), no
    // pilot and no cap (the AX43 agreement tests: stage 1 on [0, N), stage 2 on the disjoint range
    // [N, 5 N)).
    std::int64_t fixedHistories = 0;
    std::int64_t fixedStart = 0;
    // Validation only (Seat 1's clause (d) replicates, phase-05h §3): shifts every history index of the
    // shipping rule (pilot and final range alike) by this offset, so replicate r on a disjoint
    // pre-registered stream is the rule as built on histories [r 2^20, ...). 0 in every product path.
    std::int64_t historyOffset = 0;
};

// AX41 joint path-count rule as a pure function of integer counts (D7).
struct PathCountInput
{
    std::int64_t nStar = 0;  // pilot histories (a multiple of 64)
    std::int64_t wPilot = 0; // image evaluations of the pilot
    std::int64_t wScene = 0;
    std::int64_t nNeed = 0; // max over emitters and bands of ceil(n* (SE_pilot / SE_target)^2)
};
struct PathCount
{
    std::int64_t nCap = 0;       // floor((W_scene - W_pilot) n* / W_pilot), whole blocks
    std::int64_t n = 0;          // final histories: min(ceil_blocks(max(N_need, n*)), N_cap)
    bool capHit = false;         // N_need > N_cap
    bool floorTruncated = false; // N_cap < n*: N falls below n* (or the pilot ships)
    bool pilotFloor = false;     // n* < 1 000
    bool pilotShipped = false;   // N_cap < one block: the pilot estimate ships
};
PathCount pathCount(const PathCountInput& in) noexcept;
// The pilot's stop test after a block: n >= n*_max or 2 W_pilot >= W_scene.
bool pilotStops(std::int64_t n, std::int64_t wPilot, std::int64_t wScene, std::int64_t nStarMax) noexcept;
// ceil(n* (SE_db / SE_target)^2) from the pilot's per-history scores of one band without sqrt or
// log: SE_db^2 = k^2 var / (n* tot^2). Returns 1 when tot <= 0 or var <= 0.
std::int64_t pathsNeeded(std::int64_t nStar, double variance, double total, double seTargetDb) noexcept;

// Tally statistics of per-history scores x_h (the estimate is their mean), per band.
struct TallyStats
{
    double mean = 0.0;
    double variance = 0.0; // population variance of x_h
    double se = 0.0;       // sqrt(variance / n)
    double r = 0.0;        // se / mean (0 when mean = 0)
    double vov = 0.0;      // sum d^4 / (sum d^2)^2 - 1 / n
    double slope = 0.0;    // 1 + 1 / Hill index over the largest min(200, max(10, 5 %)) scores, <= 10
};
TallyStats tallyStats(const double* x, std::size_t n, std::size_t stride);

// NW-4C (AX44).
double nearestSurfaceDistance(const contract::Vec3& dims, const contract::Vec3& p) noexcept;
double blendWeight(double listenerDistanceM, double emitterDistanceM) noexcept;
bool bothNear(double listenerDistanceM, double emitterDistanceM) noexcept;
// U = (both-near AND (cap hit OR VOV_union >= 0.1)) OR (cap hit AND achieved SE > 0.33 dB).
bool approximateNote(bool bothNear, bool capHit, double vovUnion, double achievedSeDb) noexcept;

struct DiffuseEmitterResult
{
    contract::BandArray bandsDiffuse{}; // the estimate (window-referred, per 10 ms)
    contract::BandArray bandsForward{}; // its emitter-started part alone (w = 1), same histories
    contract::BandArray bandsReverse{}; // its listener-started part alone (w = 0), same histories
    contract::BandArray bandsSe{};      // its standard error (same units)
    contract::BandArray bandsSeDb{};    // SE in dB of the total (specular + diffuse)
    contract::BandArray bandsPilotSeDb{};
    contract::BandArray bandsR{};
    contract::BandArray bandsVov{}; // final range (or pilot, if it ships)
    contract::BandArray bandsPilotVov{};
    contract::BandArray bandsVovUnion{};
    contract::BandArray bandsSlope{};
    double achievedSeDb = 0.0; // max over bands
    double vovUnion = 0.0;     // max over bands
    double weight = 1.0;       // w of the NW-4C blend
    double listenerDistanceM = 0.0;
    double emitterDistanceM = 0.0;
    bool bothNear = false;
    bool approximate = false; // TailMatch.approximate (U)
};

struct DiffuseResult
{
    bool cancelled = false;
    std::int64_t nStar = 0;
    std::int64_t nNeed = 0;
    PathCount count;
    std::int64_t wPilot = 0;
    std::int64_t wFinal = 0;
    std::int64_t wScene = 0;
    std::uint64_t faceHash = 0; // D5, over the shipped histories (pilot + final) in history order
    std::size_t latticeImages = 0;
    std::vector<DiffuseEmitterResult> emitters;

    // Realised work against W_scene (AX41).
    double realisedWorkRatio() const noexcept
    {
        return wScene > 0 ? static_cast<double>(wPilot + wFinal) / static_cast<double>(wScene) : 0.0;
    }
};

struct DiffuseRunOptions
{
    ThreadPool* pool = nullptr;                // nullptr: the process-wide pool
    const std::atomic<bool>* stop = nullptr;   // D6: checked between blocks
    std::function<void(std::int64_t)> onBlock; // tests: called after each block (any thread)
};

DiffuseResult estimateDiffuse(const DiffuseProblem& problem, const DiffuseLimits& limits = {},
                              const DiffuseRunOptions& options = {});

} // namespace sim::diffuse
