// sim::Fft against a direct DFT.
#include "sim/Fft.h"
#include "sim/Rng.h"

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <complex>
#include <numbers>
#include <stdexcept>
#include <vector>

TEST_CASE("Fft matches a direct DFT and inverts", "[sim][fft]")
{
    for (const std::size_t n : {1u, 2u, 8u, 64u, 512u})
    {
        INFO("n = " << n);
        sim::GaussianSource g(sim::Pcg32(n, 0u));
        std::vector<std::complex<double>> x(n);
        for (auto& v : x)
            v = {g.next(), g.next()};
        const sim::Fft fft(n);
        auto y = x;
        fft.forward(y);
        double maxError = 0.0;
        for (std::size_t k = 0; k < n; ++k)
        {
            std::complex<double> sum = 0.0;
            for (std::size_t t = 0; t < n; ++t)
                sum += x[t]
                       * std::polar(1.0, -2.0 * std::numbers::pi * static_cast<double>(k * t)
                                             / static_cast<double>(n));
            maxError = std::max(maxError, std::abs(sum - y[k]));
        }
        CHECK(maxError < 1e-10 * static_cast<double>(n));
        fft.inverse(y);
        for (std::size_t t = 0; t < n; ++t)
            CHECK(std::abs(y[t] / static_cast<double>(n) - x[t]) < 1e-12);
    }
}

TEST_CASE("Fft rejects sizes that aren't powers of two", "[sim][fft]")
{
    CHECK_THROWS_AS(sim::Fft(0), std::invalid_argument);
    CHECK_THROWS_AS(sim::Fft(12), std::invalid_argument);
    CHECK(sim::Fft::nextPowerOfTwo(1) == 1);
    CHECK(sim::Fft::nextPowerOfTwo(5) == 8);
    CHECK(sim::Fft::nextPowerOfTwo(1024) == 1024);
}
