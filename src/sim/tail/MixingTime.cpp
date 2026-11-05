#include "sim/tail/MixingTime.h"

#include "sim/ism/ImageSources.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace sim::tail {

namespace {

// int_a^b w(t)^2 / t^2 dt for the Hann taper w(t) = sin^2(pi (t - a) / (b - a)), composite
// Simpson's rule. The integrand is smooth (a > 0), so 4096 intervals give ~1e-14 relative error.
double hannSquaredOverTSquared(double a, double b) noexcept
{
    constexpr int kIntervals = 4096;
    const double h = (b - a) / kIntervals;
    double sum = 0.0;
    for (int i = 0; i <= kIntervals; ++i)
    {
        const double t = a + h * i;
        const double s = std::sin(std::numbers::pi * static_cast<double>(i) / kIntervals);
        const double w = s * s;
        const double f = w * w / (t * t);
        const double weight = (i == 0 || i == kIntervals) ? 1.0 : (i % 2 == 1 ? 4.0 : 2.0);
        sum += weight * f;
    }
    return sum * h / 3.0;
}

} // namespace

double expectedKeff(double startS, double endS, double volumeM3) noexcept
{
    if (!(endS > startS) || !(startS > 0.0) || !(volumeM3 > 0.0))
        return 0.0;
    constexpr double c = ism::kSpeedOfSoundMps;
    const double integralW = 0.5 * (endS - startS); // int of the Hann taper
    const double denominator = hannSquaredOverTSquared(startS, endS);
    return 4.0 * std::numbers::pi * c * c * c / volumeM3 * integralW * integralW / denominator;
}

double expectedSigmaDb(double keff) noexcept
{
    return keff > 0.0 ? 10.0 / std::numbers::ln10 / std::sqrt(keff) : 0.0;
}

MixingTime mixingTime(double directS, double volumeM3)
{
    MixingTime mt;
    mt.directS = directS;
    // sqrt(V) ms: V in m^3 -> sqrt(V) * 1e-3 s.
    mt.lowerBoundS = directS + std::max(kMixingMinAfterDirectS, std::sqrt(volumeM3) * 1e-3);
    mt.windowStartS = directS + kMatchWindowStartAfterDirectS;

    const auto keff = [&](double t) { return expectedKeff(mt.windowStartS, t, volumeM3); };
    double lo = mt.lowerBoundS;
    if (keff(lo) >= kMixingMinKeff)
    {
        mt.mixS = lo;
    }
    else
    {
        // k_eff grows with the window end (unit-tested); bracket, then bisect.
        double hi = lo + std::max(lo - mt.windowStartS, 0.001);
        for (int i = 0; i < 64 && keff(hi) < kMixingMinKeff; ++i)
            hi = mt.windowStartS + 2.0 * (hi - mt.windowStartS);
        for (int i = 0; i < 60; ++i)
        {
            const double mid = 0.5 * (lo + hi);
            if (keff(mid) >= kMixingMinKeff)
                hi = mid;
            else
                lo = mid;
        }
        mt.mixS = hi;
    }
    mt.expectedKeff = keff(mt.mixS);
    return mt;
}

} // namespace sim::tail
