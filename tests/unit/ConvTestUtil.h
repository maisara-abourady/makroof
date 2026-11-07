#pragma once

// Helpers for the Phase 06 real-time convolution tests: seeded signals, the independent reference
// (sim::convolve, Phase 02: direct or one full-length double-precision FFT, no PFFFT, no
// partitioning) and the residual-energy measure of the acceptance criteria.
#include "sim/OfflineRender.h"
#include "sim/Rng.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

namespace conv_test {

// White Gaussian samples, deterministic (PCG32 + Box-Muller, sim/Rng.h).
inline std::vector<float> noise(std::size_t n, std::uint64_t seed, double scale = 0.25)
{
    sim::GaussianSource g(sim::Pcg32(seed, 54u));
    std::vector<float> x(n);
    for (auto& v : x)
        v = static_cast<float>(scale * g.next());
    return x;
}

// Reference linear convolution in double (length x + h - 1), Phase 02's renderer.
inline std::vector<double> reference(const std::vector<float>& x, const std::vector<float>& h)
{
    return sim::convolve(x, h, sim::ConvolutionMethod::Auto);
}

// 10 log10( sum (y[t + delay] - ref[t])^2 / sum ref[t]^2 ) over t in [0, ref.size()), with y[t] = 0
// beyond its end. -inf when the residual is exactly zero.
inline double residualDb(const std::vector<float>& y, const std::vector<double>& ref, std::size_t delay)
{
    long double err = 0.0L, sig = 0.0L;
    for (std::size_t t = 0; t < ref.size(); ++t)
    {
        const double v = t + delay < y.size() ? static_cast<double>(y[t + delay]) : 0.0;
        const long double d = static_cast<long double>(v) - static_cast<long double>(ref[t]);
        err += d * d;
        sig += static_cast<long double>(ref[t]) * static_cast<long double>(ref[t]);
    }
    // Samples of y before the delay must be silent (they would be energy the reference doesn't have).
    for (std::size_t t = 0; t < delay && t < y.size(); ++t)
        err += static_cast<long double>(y[t]) * static_cast<long double>(y[t]);
    if (!(err > 0.0L))
        return -std::numeric_limits<double>::infinity();
    return 10.0 * std::log10(static_cast<double>(err / sig));
}

// Host block sizes for a run of `total` samples: a fixed size, or (blockSize == 0) seeded random
// sizes in 1 .. maxRandom.
inline std::vector<int> blockSchedule(std::size_t total, int blockSize, std::uint64_t seed = 7u,
                                      int maxRandom = 2048)
{
    std::vector<int> sizes;
    sim::Pcg32 rng(seed, 3u);
    std::size_t done = 0;
    while (done < total)
    {
        int n = blockSize > 0 ? blockSize
                              : 1 + static_cast<int>(rng.next() % static_cast<std::uint32_t>(maxRandom));
        n = static_cast<int>(std::min<std::size_t>(static_cast<std::size_t>(n), total - done));
        sizes.push_back(n);
        done += static_cast<std::size_t>(n);
    }
    return sizes;
}

} // namespace conv_test
