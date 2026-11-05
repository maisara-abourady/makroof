#pragma once

// Portable pseudo-random numbers for the Simulator (AX5: determinism). std::mt19937 and the
// std:: distributions are not guaranteed to give the same values on every standard library, so the
// Simulator uses its own generator: PCG32 (O'Neill 2014, "PCG: A Family of Simple Fast
// Space-Efficient Statistically Good Algorithms for Random Number Generation", pcg32 = XSH RR 64/32,
// the reference implementation's pcg32_srandom_r / pcg32_random_r).
#include <cmath>
#include <cstdint>
#include <numbers>

namespace sim {

class Pcg32
{
public:
    // Seeds the generator like pcg32_srandom_r(initState, streamId): different streams give
    // independent sequences for the same state seed.
    Pcg32(std::uint64_t initState, std::uint64_t streamId) noexcept
        : inc_((streamId << 1u) | 1u)
    {
        next();
        state_ += initState;
        next();
    }

    std::uint32_t next() noexcept
    {
        const std::uint64_t old = state_;
        state_ = old * 6364136223846793005ULL + inc_;
        const auto xorShifted = static_cast<std::uint32_t>(((old >> 18u) ^ old) >> 27u);
        const auto rot = static_cast<std::uint32_t>(old >> 59u);
        return (xorShifted >> rot) | (xorShifted << ((32u - rot) & 31u));
    }

    // Uniform in the open interval (0, 1): (k + 0.5) / 2^32.
    double uniformOpen() noexcept { return (static_cast<double>(next()) + 0.5) * (1.0 / 4294967296.0); }

private:
    std::uint64_t state_ = 0;
    std::uint64_t inc_ = 0;
};

// Standard normal deviates by the Box-Muller transform, two per pair of uniforms. Deterministic for
// a given generator state; the values can differ across platforms only by the last bits of
// std::log / std::cos / std::sin (AX5 allows this across architectures).
class GaussianSource
{
public:
    explicit GaussianSource(Pcg32 rng) noexcept
        : rng_(rng)
    {}

    double next() noexcept
    {
        if (hasSpare_)
        {
            hasSpare_ = false;
            return spare_;
        }
        const double u1 = rng_.uniformOpen();
        const double u2 = rng_.uniformOpen();
        const double radius = std::sqrt(-2.0 * std::log(u1));
        const double angle = 2.0 * std::numbers::pi * u2;
        spare_ = radius * std::sin(angle);
        hasSpare_ = true;
        return radius * std::cos(angle);
    }

private:
    Pcg32 rng_;
    double spare_ = 0.0;
    bool hasSpare_ = false;
};

} // namespace sim
