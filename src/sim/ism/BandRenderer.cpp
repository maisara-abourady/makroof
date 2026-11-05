#include "sim/ism/BandRenderer.h"

#include <algorithm>
#include <cmath>
#include <complex>
#include <numbers>
#include <stdexcept>
#include <utility>

namespace sim::ism {

namespace {

using Complex = std::complex<double>;

double sinc(double x) noexcept
{
    if (x == 0.0)
        return 1.0;
    const double px = std::numbers::pi * x;
    return std::sin(px) / px;
}

// In-place iterative radix-2 FFT, size a power of two; inverse = unscaled inverse transform.
// Twiddles from cos/sin per index (no recurrence), as in OfflineRender.cpp (kept separate so the
// reference renderer stays independent of the IR builder).
void fft(std::vector<Complex>& data, bool inverse)
{
    const std::size_t n = data.size();
    for (std::size_t i = 1, j = 0; i < n; ++i)
    {
        std::size_t bit = n >> 1;
        for (; (j & bit) != 0; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            std::swap(data[i], data[j]);
    }
    const double sign = inverse ? 1.0 : -1.0;
    std::vector<Complex> twiddle(n / 2);
    for (std::size_t k = 0; k < n / 2; ++k)
    {
        const double angle = sign * 2.0 * std::numbers::pi * static_cast<double>(k) / static_cast<double>(n);
        twiddle[k] = Complex(std::cos(angle), std::sin(angle));
    }
    for (std::size_t len = 2; len <= n; len <<= 1)
    {
        const std::size_t half = len / 2;
        const std::size_t step = n / len;
        for (std::size_t start = 0; start < n; start += len)
            for (std::size_t k = 0; k < half; ++k)
            {
                const Complex t = twiddle[k * step] * data[start + k + half];
                data[start + k + half] = data[start + k] - t;
                data[start + k] += t;
            }
    }
}

// Spectra of two real signals a, b from one complex FFT of a + i b.
void splitSpectra(const std::vector<Complex>& z, std::vector<Complex>& a, std::vector<Complex>& b)
{
    const std::size_t n = z.size();
    a.resize(n);
    b.resize(n);
    for (std::size_t k = 0; k < n; ++k)
    {
        const Complex zk = z[k];
        const Complex zc = std::conj(z[(n - k) % n]);
        a[k] = 0.5 * (zk + zc);
        b[k] = Complex(0.0, -0.5) * (zk - zc);
    }
}

} // namespace

double besselI0(double x) noexcept
{
    // sum_k ((x/2)^k / k!)^2; converges quickly for the arguments used here (|x| <= ~20).
    const double half = 0.5 * x;
    double term = 1.0;
    double sum = 1.0;
    for (int k = 1; k < 200; ++k)
    {
        term *= half / k;
        const double t2 = term * term;
        sum += t2;
        if (t2 < sum * 1e-17)
            break;
    }
    return sum;
}

std::array<double, 2 * kKernelHalfLength + 1> fractionalDelayKernel(double frac) noexcept
{
    std::array<double, 2 * kKernelHalfLength + 1> taps{};
    if (frac == 0.0)
    {
        taps[kKernelHalfLength] = 1.0;
        return taps;
    }
    // Window support +-(kKernelHalfLength + 0.5) covers every tap for |frac| <= 0.5.
    const double support = kKernelHalfLength + 0.5;
    const double norm = besselI0(kKernelKaiserBeta);
    double sum = 0.0;
    for (int j = -kKernelHalfLength; j <= kKernelHalfLength; ++j)
    {
        const double x = j - frac;
        const double r = x / support;
        const double window = besselI0(kKernelKaiserBeta * std::sqrt(std::max(0.0, 1.0 - r * r))) / norm;
        const double v = sinc(x) * window;
        taps[static_cast<std::size_t>(j + kKernelHalfLength)] = v;
        sum += v;
    }
    for (double& v : taps)
        v /= sum;
    return taps;
}

double OctaveFilterbank::bandCentreHz(std::size_t b) noexcept
{
    return 1000.0 * std::pow(2.0, static_cast<double>(b) - 4.0);
}

double OctaveFilterbank::crossoverHz(std::size_t k) noexcept
{
    return bandCentreHz(k) * std::numbers::sqrt2;
}

OctaveFilterbank::OctaveFilterbank(double sampleRate)
    : sampleRate_(sampleRate)
{
    if (!(sampleRate > 2.0 * crossoverHz(kNumCrossovers - 1) * std::pow(2.0, kCrossoverTransitionOctaves)))
        throw std::invalid_argument("OctaveFilterbank: sample rate too low");

    const double beta = 0.1102 * (kCrossoverStopbandDb - 8.7); // Kaiser, A > 50 dB
    const double norm = besselI0(beta);
    lowpass_.resize(kNumCrossovers);
    for (std::size_t k = 0; k < kNumCrossovers; ++k)
    {
        const double fx = crossoverHz(k);
        const double transitionHz =
            fx * (std::pow(2.0, kCrossoverTransitionOctaves) - std::pow(2.0, -kCrossoverTransitionOctaves));
        const double deltaOmega = 2.0 * std::numbers::pi * transitionHz / sampleRate;
        const auto taps = static_cast<std::size_t>(
            std::ceil((kCrossoverStopbandDb - 8.0) / (2.285 * deltaOmega)));
        const std::size_t half = (taps + 1) / 2;
        const double wc = 2.0 * fx / sampleRate; // cut-off as a fraction of Nyquist

        std::vector<double> h(2 * half + 1);
        double sum = 0.0;
        for (std::size_t i = 0; i < h.size(); ++i)
        {
            const double m = static_cast<double>(i) - static_cast<double>(half);
            const double r = m / static_cast<double>(half);
            const double window = besselI0(beta * std::sqrt(std::max(0.0, 1.0 - r * r))) / norm;
            h[i] = wc * sinc(wc * m) * window;
            sum += h[i];
        }
        for (double& v : h)
            v /= sum; // unit DC gain, so B_0 passes DC exactly and B_1..B_7 block it
        maxHalf_ = std::max(maxHalf_, half);
        lowpass_[k] = std::move(h);
    }
}

std::vector<double> OctaveFilterbank::bandImpulseResponse(std::size_t b) const
{
    if (b >= contract::kNumOctaveBands)
        throw std::out_of_range("OctaveFilterbank::bandImpulseResponse");
    std::vector<double> out(2 * maxHalf_ + 1, 0.0);
    const auto add = [&](std::size_t k, double sign) {
        const auto& h = lowpass_[k];
        const std::size_t offset = maxHalf_ - halfLength(k);
        for (std::size_t i = 0; i < h.size(); ++i)
            out[offset + i] += sign * h[i];
    };
    if (b < kNumCrossovers)
        add(b, 1.0);
    if (b > 0)
        add(b - 1, -1.0);
    if (b == kNumCrossovers)
        out[maxHalf_] += 1.0;
    return out;
}

std::vector<std::vector<double>> accumulateBandTrains(std::span<const ImageSource> images, double timeShiftS,
                                                      double sampleRate, std::size_t length)
{
    std::vector<std::vector<double>> bands(contract::kNumOctaveBands, std::vector<double>(length, 0.0));
    for (const auto& image : images)
    {
        const double position = (image.arrivalTimeS - timeShiftS) * sampleRate;
        const double nearest = std::round(position);
        const auto kernel = fractionalDelayKernel(position - nearest);
        const auto centre = static_cast<std::ptrdiff_t>(nearest);
        for (int j = -kKernelHalfLength; j <= kKernelHalfLength; ++j)
        {
            const std::ptrdiff_t n = centre + j;
            const double k = kernel[static_cast<std::size_t>(j + kKernelHalfLength)];
            if (k == 0.0 || n < 0 || n >= static_cast<std::ptrdiff_t>(length))
                continue;
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                bands[b][static_cast<std::size_t>(n)] += image.bandsAmplitude[b] * k;
        }
    }
    return bands;
}

std::vector<double> synthesizeBands(const std::vector<std::vector<double>>& bandSignals,
                                    const OctaveFilterbank& filterbank)
{
    if (bandSignals.size() != contract::kNumOctaveBands)
        throw std::invalid_argument("synthesizeBands: need one signal per octave band");
    const std::size_t length = bandSignals.front().size();
    for (const auto& s : bandSignals)
        if (s.size() != length)
            throw std::invalid_argument("synthesizeBands: band signals differ in length");

    // y = x_7 + sum_k P_k * (x_k - x_(k+1)); skip the differences that are exactly zero.
    std::vector<double> y = bandSignals.back();
    std::vector<std::size_t> active;
    std::vector<std::vector<double>> diffs;
    for (std::size_t k = 0; k < OctaveFilterbank::kNumCrossovers; ++k)
    {
        std::vector<double> d(length);
        bool nonZero = false;
        for (std::size_t n = 0; n < length; ++n)
        {
            d[n] = bandSignals[k][n] - bandSignals[k + 1][n];
            nonZero = nonZero || d[n] != 0.0;
        }
        if (nonZero)
        {
            active.push_back(k);
            diffs.push_back(std::move(d));
        }
    }
    if (active.empty() || length == 0)
        return y;

    // Circular convolution of size N >= length + maxHalf: the centred filter's negative taps wrap
    // to the end, and nothing aliases into [0, length).
    std::size_t n = 1;
    while (n < length + filterbank.maxHalfLength() + 1)
        n <<= 1;

    std::vector<Complex> sum(n, Complex(0.0, 0.0));
    std::vector<Complex> z(n), specA, specB, filtA, filtB;
    const auto loadFilter = [&](std::size_t k, std::vector<Complex>& buffer, bool imaginary) {
        const auto& h = filterbank.lowpass(k);
        const std::size_t half = filterbank.halfLength(k);
        for (std::size_t i = 0; i < h.size(); ++i)
        {
            const std::size_t index = (i + n - half) % n;
            buffer[index] += imaginary ? Complex(0.0, h[i]) : Complex(h[i], 0.0);
        }
    };

    // Two (filter, signal) pairs per pair of FFTs: one packs the two filters, one the two signals.
    for (std::size_t i = 0; i < active.size(); i += 2)
    {
        const bool pair = i + 1 < active.size();
        std::fill(z.begin(), z.end(), Complex(0.0, 0.0));
        for (std::size_t t = 0; t < length; ++t)
            z[t] = Complex(diffs[i][t], pair ? diffs[i + 1][t] : 0.0);
        fft(z, false);
        splitSpectra(z, specA, specB);

        std::fill(z.begin(), z.end(), Complex(0.0, 0.0));
        loadFilter(active[i], z, false);
        if (pair)
            loadFilter(active[i + 1], z, true);
        fft(z, false);
        splitSpectra(z, filtA, filtB);

        for (std::size_t k = 0; k < n; ++k)
            sum[k] += filtA[k] * specA[k] + (pair ? filtB[k] * specB[k] : Complex(0.0, 0.0));
    }
    fft(sum, true);
    const double scale = 1.0 / static_cast<double>(n);
    for (std::size_t t = 0; t < length; ++t)
        y[t] += sum[t].real() * scale;
    return y;
}

std::vector<double> renderImageSources(std::span<const ImageSource> images, double timeShiftS,
                                       const OctaveFilterbank& filterbank)
{
    double last = 0.0;
    for (const auto& image : images)
        last = std::max(last, (image.arrivalTimeS - timeShiftS) * filterbank.sampleRate());
    const auto length = static_cast<std::size_t>(std::ceil(last))
                        + static_cast<std::size_t>(kKernelHalfLength) + filterbank.maxHalfLength() + 1;
    return synthesizeBands(accumulateBandTrains(images, timeShiftS, filterbank.sampleRate(), length),
                           filterbank);
}

} // namespace sim::ism
