#pragma once

// Helpers for the Phase 06 real-time convolution tests: seeded signals, the independent reference
// (sim::convolve, Phase 02: direct or one full-length double-precision FFT, no PFFFT, no
// partitioning) and the residual-energy measure of the acceptance criteria.
#include "sim/OfflineRender.h"
#include "sim/Rng.h"

#include <atomic>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <thread>
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
    if (std::isnan(err)) // a NaN anywhere in y is never a null (phase-06b review: it read as -inf)
        return std::numeric_limits<double>::infinity();
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

// Runs f() on a worker thread and waits at most `limit`. A call that hangs (e.g. a process() that
// spins) aborts the test binary with a message after `limit`, so the test fails in seconds instead
// of at the 600 s ctest timeout. (The hung thread can't be cancelled, so aborting is the only clean
// exit.)
template <typename F>
void runWithWatchdog(F&& f, const char* what, std::chrono::milliseconds limit = std::chrono::seconds(5))
{
    std::atomic<bool> finished{false};
    std::thread worker([&] {
        f();
        finished.store(true, std::memory_order_release);
    });
    const auto until = std::chrono::steady_clock::now() + limit;
    while (!finished.load(std::memory_order_acquire) && std::chrono::steady_clock::now() < until)
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    if (!finished.load(std::memory_order_acquire))
    {
        std::fprintf(stderr, "WATCHDOG: %s did not return within %lld ms (hang); aborting\n", what,
                     static_cast<long long>(limit.count()));
        std::fflush(stderr);
        std::abort();
    }
    worker.join();
}

} // namespace conv_test
