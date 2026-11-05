// sim::Pcg32 / sim::GaussianSource (AX5: a portable PRNG for the tail noise).
#include "sim/Rng.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <cmath>
#include <cstdint>

// Exact floating-point comparisons are intended here (determinism, exact zeros, values copied
// unchanged), so -Wfloat-equal (part of JUCE's recommended warnings, which the tests compile with
// when the plugin is built) is silenced for this file, as in contract/SceneDescription.h.
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

TEST_CASE("Pcg32 reproduces the reference implementation's pcg32 sequence", "[sim][rng]")
{
    // pcg-c-basic pcg32-demo: pcg32_srandom_r(&rng, 42u, 54u), first six pcg32_random_r values.
    sim::Pcg32 rng(42u, 54u);
    const std::array<std::uint32_t, 6> expected{0xa15c02b7u, 0x7b47f409u, 0xba1d3330u,
                                                0x83d2f293u, 0xbfa4784bu, 0xcbed606eu};
    for (const auto value : expected)
        CHECK(rng.next() == value);
}

TEST_CASE("Pcg32 streams and seeds give different sequences", "[sim][rng]")
{
    sim::Pcg32 a(12345u, 0u), b(12345u, 1u), c(12346u, 0u);
    int sameAb = 0, sameAc = 0;
    for (int i = 0; i < 1000; ++i)
    {
        const auto va = a.next();
        sameAb += va == b.next() ? 1 : 0;
        sameAc += va == c.next() ? 1 : 0;
    }
    CHECK(sameAb < 3);
    CHECK(sameAc < 3);
}

TEST_CASE("uniformOpen stays inside (0, 1)", "[sim][rng]")
{
    sim::Pcg32 rng(1u, 2u);
    for (int i = 0; i < 100000; ++i)
    {
        const double u = rng.uniformOpen();
        REQUIRE(u > 0.0);
        REQUIRE(u < 1.0);
    }
}

TEST_CASE("GaussianSource has zero mean and unit variance", "[sim][rng]")
{
    sim::GaussianSource gauss(sim::Pcg32(7u, 3u));
    constexpr int n = 400000;
    double sum = 0.0, sumSquares = 0.0, sumFourth = 0.0;
    for (int i = 0; i < n; ++i)
    {
        const double x = gauss.next();
        REQUIRE(std::isfinite(x));
        sum += x;
        sumSquares += x * x;
        sumFourth += x * x * x * x;
    }
    const double mean = sum / n;
    const double variance = sumSquares / n - mean * mean;
    CHECK(std::abs(mean) < 5.0 / std::sqrt(static_cast<double>(n))); // 5 standard errors
    CHECK_THAT(variance, Catch::Matchers::WithinAbs(1.0, 0.01));
    CHECK_THAT(sumFourth / n, Catch::Matchers::WithinAbs(3.0, 0.05)); // Gaussian kurtosis
}

TEST_CASE("GaussianSource is deterministic", "[sim][rng]")
{
    sim::GaussianSource a(sim::Pcg32(99u, 1u)), b(sim::Pcg32(99u, 1u));
    for (int i = 0; i < 1000; ++i)
        CHECK(a.next() == b.next());
}
