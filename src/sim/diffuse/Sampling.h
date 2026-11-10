#pragma once

// Path-decision primitives of the diffuse-energy estimator (AX39 D1, D3).
//
// Everything in this header decides a path (a direction, a branch, a rejection), so it uses
// integer arithmetic, + - * / and std::sqrt only: IEEE 754 requires those to be correctly rounded,
// so with fp-contract off (D2, src/sim/CMakeLists.txt) the same key gives the same path on every
// platform. No libm transcendental (sin, cos, exp, log, pow, ...) and no <random> may appear here;
// tools/ci/test_diffuse_sources.py checks both.
//
// Generator (an implementation choice inside AX39 D1, which fixes only the key): a counter-based
// stream. The key (seed, end, emitter, path, hit, attempt) is folded through the SplitMix64
// finaliser (Steele, Lea & Flood 2014) into a 64-bit state; successive outputs of one key are
// SplitMix64 steps from that state. A uniform double is the top 53 bits times 2^-53, in [0, 1).
// Known-answer vectors: tests/unit/test_diffuse.cpp ("diffuse RNG known-answer vectors", D3).
#include <cmath>
#include <cstdint>

namespace sim::diffuse {

// Which end of the path the trace starts from (AX44): the emitter (forward) or the listener.
enum class PathEnd : std::uint32_t
{
    emitter = 0,
    listener = 1,
};

// The key's emitter field for the listener-started set, which serves both emitters (AX44).
inline constexpr std::uint32_t kSharedEmitter = 0xFFu;

inline constexpr std::uint64_t splitMix64(std::uint64_t z) noexcept
{
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}

inline constexpr std::uint64_t kGolden64 = 0x9E3779B97F4A7C15ull;

// The key (AX39 D1). `hit` is 0 for the emission and k for the k-th reflection; `attempt` is 0 for
// the branch draw of a reflection and 1, 2, ... for the successive rejection attempts of a
// direction.
struct Key
{
    std::uint64_t seed = 0;
    PathEnd end = PathEnd::emitter;
    std::uint32_t emitter = 0;
    std::uint64_t path = 0;
    std::uint32_t hit = 0;
    std::uint32_t attempt = 0;
};

inline constexpr std::uint64_t keyState(const Key& k) noexcept
{
    std::uint64_t h = splitMix64(k.seed + kGolden64);
    h = splitMix64(h ^ (static_cast<std::uint64_t>(k.end) << 32 | k.emitter));
    h = splitMix64(h ^ k.path);
    h = splitMix64(h ^ (static_cast<std::uint64_t>(k.hit) << 32 | k.attempt));
    return h;
}

// Outputs of one key.
class Stream
{
public:
    explicit constexpr Stream(const Key& key) noexcept
        : state_(keyState(key))
    {}

    constexpr std::uint64_t nextU64() noexcept
    {
        state_ += kGolden64;
        return splitMix64(state_);
    }

    // Uniform in [0, 1): 53 bits.
    constexpr double nextUniform() noexcept { return static_cast<double>(nextU64() >> 11) * 0x1.0p-53; }

private:
    std::uint64_t state_;
};

struct Direction
{
    double v[3]{};
};

// Uniform direction on the sphere by rejection from the cube [-1, 1]^3 (no trigonometry). Each
// attempt draws three uniforms from its own key (attempt = 1, 2, ...).
inline Direction uniformSphere(Key key) noexcept
{
    for (std::uint32_t attempt = 1;; ++attempt)
    {
        key.attempt = attempt;
        Stream s(key);
        const double x = 2.0 * s.nextUniform() - 1.0;
        const double y = 2.0 * s.nextUniform() - 1.0;
        const double z = 2.0 * s.nextUniform() - 1.0;
        const double r2 = x * x + y * y + z * z;
        if (r2 > 1e-12 && r2 <= 1.0)
        {
            const double inv = 1.0 / std::sqrt(r2);
            return {{x * inv, y * inv, z * inv}};
        }
    }
}

// Lambert (cosine-weighted) direction into the room off face `axis` (Kuttruff Eq. 4.24): Malley's
// method, a uniform point on the unit disk by rejection from the square, lifted to the
// hemisphere. `inward` is +1 for a face at coordinate 0 and -1 for a face at the room's size.
inline Direction lambert(Key key, int axis, double inward) noexcept
{
    for (std::uint32_t attempt = 1;; ++attempt)
    {
        key.attempt = attempt;
        Stream s(key);
        const double u = 2.0 * s.nextUniform() - 1.0;
        const double w = 2.0 * s.nextUniform() - 1.0;
        const double r2 = u * u + w * w;
        if (r2 < 1.0)
        {
            Direction d;
            const int a1 = (axis + 1) % 3;
            const int a2 = (axis + 2) % 3;
            d.v[a1] = u;
            d.v[a2] = w;
            d.v[axis] = inward * std::sqrt(1.0 - r2);
            return d;
        }
    }
}

// The branch draw of a reflection (attempt 0): true = diffuse continuation, with probability s.
inline bool scatterBranch(Key key, double scattering) noexcept
{
    key.attempt = 0;
    Stream s(key);
    return s.nextUniform() < scattering;
}

// FNV-1a step for the D5 face-sequence hash.
inline constexpr std::uint64_t kFnvOffset = 0xCBF29CE484222325ull;
inline constexpr std::uint64_t fnvStep(std::uint64_t h, std::uint64_t v) noexcept
{
    return (h ^ v) * 0x100000001B3ull;
}

} // namespace sim::diffuse
