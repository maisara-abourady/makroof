// sim::ism band reconstruction: fractional-delay kernel, octave filterbank (perfect reconstruction,
// selectivity, flatness), group-delay removal.
#include "IsmTestUtil.h"
#include "sim/Engine.h"
#include "sim/ism/BandRenderer.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <complex>
#include <numbers>

namespace {

// Test-local radix-2 FFT (power spectrum of a real signal, zero-padded to a power of two >= minSize).
std::vector<double> powerSpectrum(const std::vector<double>& x, std::size_t minSize)
{
    std::size_t n = 1;
    while (n < std::max(minSize, x.size()))
        n <<= 1;
    std::vector<std::complex<double>> a(n);
    for (std::size_t i = 0; i < x.size(); ++i)
        a[i] = x[i];
    for (std::size_t i = 1, j = 0; i < n; ++i)
    {
        std::size_t bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            std::swap(a[i], a[j]);
    }
    for (std::size_t len = 2; len <= n; len <<= 1)
    {
        const double ang = -2.0 * std::numbers::pi / static_cast<double>(len);
        for (std::size_t s = 0; s < n; s += len)
            for (std::size_t k = 0; k < len / 2; ++k)
            {
                const auto w = std::polar(1.0, ang * static_cast<double>(k));
                const auto t = w * a[s + k + len / 2];
                a[s + k + len / 2] = a[s + k] - t;
                a[s + k] += t;
            }
    }
    std::vector<double> p(n / 2 + 1);
    for (std::size_t k = 0; k < p.size(); ++k)
        p[k] = std::norm(a[k]);
    return p;
}

// Energy of a power spectrum between lo and hi Hz.
double bandEnergy(const std::vector<double>& p, double fs, double lo, double hi)
{
    const double df = fs / (2.0 * static_cast<double>(p.size() - 1));
    double e = 0.0;
    for (std::size_t k = 0; k < p.size(); ++k)
    {
        const double f = static_cast<double>(k) * df;
        if (f >= lo && f < hi)
            e += p[k];
    }
    return e;
}

double octaveEnergy(const std::vector<double>& p, double fs, std::size_t band, double halfWidthOctaves = 0.5)
{
    const double fc = sim::ism::OctaveFilterbank::bandCentreHz(band);
    return bandEnergy(p, fs, fc * std::pow(2.0, -halfWidthOctaves), fc * std::pow(2.0, halfWidthOctaves));
}

} // namespace

TEST_CASE("fractional-delay kernel: exact delta at integer delay, unit DC gain, mirror symmetry",
          "[sim][bands]")
{
    const auto delta = sim::ism::fractionalDelayKernel(0.0);
    for (std::size_t j = 0; j < delta.size(); ++j)
        CHECK_THAT(delta[j], Catch::Matchers::WithinULP(j == 16 ? 1.0 : 0.0, 0));
    for (const double frac : {-0.5, -0.31, 0.1, 0.25, 0.4999})
    {
        const auto k = sim::ism::fractionalDelayKernel(frac);
        const auto m = sim::ism::fractionalDelayKernel(-frac);
        double sum = 0.0;
        for (std::size_t j = 0; j < k.size(); ++j)
        {
            sum += k[j];
            CHECK_THAT(k[j], Catch::Matchers::WithinAbs(m[k.size() - 1 - j], 1e-15));
        }
        CHECK_THAT(sum, Catch::Matchers::WithinAbs(1.0, 1e-14));
        // The kernel's centre of mass is at the fractional position (linear phase).
        double moment = 0.0;
        for (std::size_t j = 0; j < k.size(); ++j)
            moment += (static_cast<double>(j) - 16.0) * k[j];
        CHECK_THAT(moment, Catch::Matchers::WithinAbs(frac, 2e-3));
    }
    CHECK_THAT(sim::ism::besselI0(0.0), Catch::Matchers::WithinAbs(1.0, 0.0));
    CHECK_THAT(sim::ism::besselI0(8.0), Catch::Matchers::WithinRel(427.56411572180474, 1e-12));
}

TEST_CASE("filterbank: the band filters sum to a delta within -100 dB", "[sim][bands]")
{
    for (const double fs : sim::kSupportedSampleRatesHz)
    {
        const sim::ism::OctaveFilterbank fb(fs);
        std::vector<double> sum(2 * fb.maxHalfLength() + 1, 0.0);
        for (std::size_t b = 0; b < 8; ++b)
        {
            const auto h = fb.bandImpulseResponse(b);
            for (std::size_t i = 0; i < h.size(); ++i)
                sum[i] += h[i];
        }
        sum[fb.maxHalfLength()] -= 1.0;
        double err = 0.0;
        for (const double v : sum)
            err += v * v;
        INFO(fs << " Hz: residual " << 10.0 * std::log10(err + 1e-300) << " dB");
        CHECK(err <= 1e-10);
    }
}

TEST_CASE("filterbank: flat band gains reproduce the impulse train exactly", "[sim][bands]")
{
    const sim::ism::OctaveFilterbank fb(48000.0);
    std::mt19937_64 rng(5);
    std::vector<double> x(5000);
    for (auto& v : x)
        v = ism_test::uniform(rng, -1.0, 1.0);
    const std::vector<std::vector<double>> bands(8, x);
    const auto y = sim::ism::synthesizeBands(bands, fb);
    REQUIRE(y == x); // bit-exact: every difference x_k - x_(k+1) is zero
}

TEST_CASE("filterbank: one band at gain 1 is >= 20 dB above its neighbouring octaves", "[sim][bands]")
{
    for (const double fs : sim::kSupportedSampleRatesHz)
    {
        const sim::ism::OctaveFilterbank fb(fs);
        for (std::size_t b = 0; b < 8; ++b)
        {
            // Render it through synthesizeBands (the code path the IR uses): an impulse in band b only.
            const std::size_t length = 2 * fb.maxHalfLength() + 1;
            std::vector<std::vector<double>> bands(8, std::vector<double>(length, 0.0));
            bands[b][fb.maxHalfLength()] = 1.0;
            const auto y = sim::ism::synthesizeBands(bands, fb);
            const auto ref = fb.bandImpulseResponse(b);
            for (std::size_t i = 0; i < y.size(); ++i)
                REQUIRE_THAT(y[i], Catch::Matchers::WithinAbs(ref[i], 1e-12));

            const auto p = powerSpectrum(y, 1 << 16);
            const double own = octaveEnergy(p, fs, b);
            for (const std::size_t n : {b - 1, b + 1})
            {
                if (n >= 8) // b - 1 wraps for b = 0
                    continue;
                const double ratioDb = 10.0 * std::log10(own / octaveEnergy(p, fs, n));
                INFO(fs << " Hz, band " << b << " vs " << n << ": " << ratioDb << " dB");
                CHECK(ratioDb >= 20.0);
            }
            // The central half octave is flat: |B_b| = 1 within 0.01 dB there.
            const double fc = sim::ism::OctaveFilterbank::bandCentreHz(b);
            const double df = fs / (2.0 * static_cast<double>(p.size() - 1));
            for (std::size_t k = 0; k < p.size(); ++k)
            {
                const double f = static_cast<double>(k) * df;
                if (f >= fc * std::pow(2.0, -0.25) && f <= fc * std::pow(2.0, 0.25))
                    REQUIRE_THAT(10.0 * std::log10(p[k]), Catch::Matchers::WithinAbs(0.0, 0.01));
            }
        }
    }
}

TEST_CASE("band rendering removes the group delay: peaks land at their arrival sample", "[sim][bands]")
{
    const sim::ism::OctaveFilterbank fb(48000.0);
    sim::ism::ImageSource a, b;
    a.arrivalTimeS = 100.0 / 48000.0;
    a.bandsAmplitude = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3};
    b.arrivalTimeS = 2345.0 / 48000.0;
    b.bandsAmplitude = {0.2, 0.2, 0.2, 0.2, 0.1, 0.1, 0.1, 0.1};
    const std::vector<sim::ism::ImageSource> images{a, b};
    const auto y = sim::ism::renderImageSources(images, 0.0, fb);
    CHECK(y.size() == 2345 + 16 + fb.maxHalfLength() + 1);
    std::size_t peak = 0;
    for (std::size_t n = 0; n < 1000; ++n)
        if (std::abs(y[n]) > std::abs(y[peak]))
            peak = n;
    CHECK(peak == 100);
    peak = 2000;
    for (std::size_t n = 2000; n < 3000; ++n)
        if (std::abs(y[n]) > std::abs(y[peak]))
            peak = n;
    CHECK(peak == 2345);
}

TEST_CASE("band rendering is linear in the images", "[sim][bands]")
{
    const sim::ism::OctaveFilterbank fb(44100.0);
    std::mt19937_64 rng(3);
    std::vector<sim::ism::ImageSource> images(20);
    for (auto& image : images)
    {
        image.arrivalTimeS = ism_test::uniform(rng, 0.001, 0.05);
        for (auto& v : image.bandsAmplitude)
            v = ism_test::uniform(rng, -1.0, 1.0);
    }
    const auto all = sim::ism::renderImageSources(images, 0.0, fb);
    std::vector<double> sum(all.size(), 0.0);
    for (const auto& image : images)
    {
        const std::vector<sim::ism::ImageSource> one{image};
        auto part = sim::ism::synthesizeBands(sim::ism::accumulateBandTrains(one, 0.0, 44100.0, all.size()),
                                              fb);
        for (std::size_t n = 0; n < sum.size(); ++n)
            sum[n] += part[n];
    }
    for (std::size_t n = 0; n < sum.size(); ++n)
        REQUIRE_THAT(all[n], Catch::Matchers::WithinAbs(sum[n], 1e-12));
}
