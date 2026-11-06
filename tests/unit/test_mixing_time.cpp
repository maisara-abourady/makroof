// sim::tail::mixingTime (phase-04 scope 2): the smallest t >= t_dir + max(20 ms, sqrt(V) ms) with an
// expected energy-weighted k_eff >= 19 for the Hann window [t_dir + 2.5 ms, t].
#include "sim/tail/MixingTime.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <numbers>

// Exact floating-point comparisons are intended here (determinism, exact zeros, values copied
// unchanged), so -Wfloat-equal (part of JUCE's recommended warnings, which the tests compile with
// when the plugin is built) is silenced for this file, as in contract/SceneDescription.h.
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

namespace {

// Independent reference: midpoint rule with many points.
double keffReference(double a, double b, double volume)
{
    constexpr int n = 200000;
    const double h = (b - a) / n;
    double sw = 0.0, sw2 = 0.0;
    for (int i = 0; i < n; ++i)
    {
        const double t = a + (i + 0.5) * h;
        const double s = std::sin(std::numbers::pi * (t - a) / (b - a));
        const double w = s * s;
        sw += w * h;
        sw2 += w * w / (t * t) * h;
    }
    const double c = 343.0;
    return 4.0 * std::numbers::pi * c * c * c / volume * sw * sw / sw2;
}

} // namespace

TEST_CASE("expectedKeff agrees with an independent quadrature", "[sim][tail][mixing]")
{
    for (const auto& [a, b, v] : {std::tuple{0.0025, 0.02, 10.0}, std::tuple{0.0203, 0.0427, 384.0},
                                  std::tuple{0.035, 0.2, 16000.0}, std::tuple{0.3, 0.32, 600.0}})
        CHECK_THAT(sim::tail::expectedKeff(a, b, v), WithinRel(keffReference(a, b, v), 1e-6));
    CHECK(sim::tail::expectedKeff(0.1, 0.1, 100.0) == 0.0);
}

TEST_CASE("expectedKeff grows with the window end (the bisection relies on it)", "[sim][tail][mixing]")
{
    for (const double v : {10.0, 400.0, 16000.0, 300000.0})
    {
        double last = 0.0;
        for (double t = 0.0101; t < 1.5; t *= 1.05)
        {
            const double k = sim::tail::expectedKeff(0.01, t, v);
            CHECK(k > last);
            last = k;
        }
    }
}

TEST_CASE("mixingTime: the lower bound, k_eff >= 19, and the smallest such t", "[sim][tail][mixing]")
{
    for (const double direct : {0.00087, 0.0178, 0.05, 0.29})
        for (const double v : {11.0, 52.0, 384.0, 2400.0, 16000.0, 300000.0})
        {
            INFO("t_dir = " << direct << " s, V = " << v << " m^3");
            const auto mt = sim::tail::mixingTime(direct, v);
            CHECK(mt.directS == direct);
            CHECK_THAT(mt.windowStartS, WithinAbs(direct + 0.0025, 1e-15));
            CHECK_THAT(mt.lowerBoundS, WithinAbs(direct + std::max(0.020, std::sqrt(v) * 1e-3), 1e-15));
            CHECK(mt.mixS >= mt.lowerBoundS);
            CHECK(mt.expectedKeff >= 19.0);
            CHECK(mt.mixS >= direct + 0.020); // the direct sound is never in the fade
            if (mt.mixS > mt.lowerBoundS)
            {
                CHECK(sim::tail::expectedKeff(mt.windowStartS, mt.mixS - 1e-9, v) < 19.0);
                CHECK_THAT(mt.expectedKeff, WithinRel(19.0, 1e-6));
            }
            CHECK_THAT(sim::tail::expectedSigmaDb(mt.expectedKeff),
                       WithinRel(10.0 / std::log(10.0) / std::sqrt(mt.expectedKeff), 1e-12));
            CHECK(sim::tail::expectedSigmaDb(mt.expectedKeff) <= 0.9964 + 1e-9);
        }
}

TEST_CASE("mixingTime for t_dir -> 0 is roughly 6.8 V^(1/3) ms (phase-04 note)", "[sim][tail][mixing]")
{
    // Large rooms, where the k_eff criterion (not the lower bound) decides.
    for (const double v : {500.0, 2000.0, 16000.0})
    {
        const auto mt = sim::tail::mixingTime(1e-4, v);
        const double estimate = 6.8e-3 * std::cbrt(v);
        INFO("V = " << v << ": t_mix = " << mt.mixS << " s, 6.8 V^(1/3) ms = " << estimate);
        CHECK_THAT(mt.mixS, WithinRel(estimate, 0.25));
    }
}

TEST_CASE("mixingTime is deterministic", "[sim][tail][mixing]")
{
    const auto a = sim::tail::mixingTime(0.0177, 384.0);
    const auto b = sim::tail::mixingTime(0.0177, 384.0);
    CHECK(a.mixS == b.mixS);
}

TEST_CASE("mixingTime floor raises only the lower bound (phase-05 scope 6, validation only)",
          "[sim][tail][mixing]")
{
    const double direct = 0.0177, v = 384.0;
    const auto base = sim::tail::mixingTime(direct, v);
    // A floor below the rule's own bound changes nothing.
    const auto low = sim::tail::mixingTime(direct, v, 0.005);
    CHECK(low.mixS == base.mixS);
    CHECK(low.lowerBoundS == base.lowerBoundS);
    // A later floor moves the lower bound to t_dir + floor; the k_eff rule still applies above it.
    for (const double floor : {0.080, 0.140})
    {
        const auto mt = sim::tail::mixingTime(direct, v, floor);
        CHECK_THAT(mt.lowerBoundS, WithinRel(direct + floor, 1e-12));
        CHECK(mt.mixS >= mt.lowerBoundS);
        CHECK(mt.mixS >= base.mixS);
        CHECK(mt.expectedKeff >= sim::tail::kMixingMinKeff);
    }
}
