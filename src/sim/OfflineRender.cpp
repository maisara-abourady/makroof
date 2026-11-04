#include "sim/OfflineRender.h"

#include <cmath>
#include <complex>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>

namespace sim {

namespace {

using Complex = std::complex<double>;

std::size_t countNonZero(const std::vector<float>& h) noexcept
{
    std::size_t n = 0;
    for (const float v : h)
        if (v != 0.0f)
            ++n;
    return n;
}

std::vector<double> convolveDirect(const std::vector<float>& x, const std::vector<float>& h)
{
    // -0.0 is the exact additive identity in IEEE 754 (-0 + v == v for every v, including -0), so
    // an output sample that receives a single contribution is bit-identical to that contribution.
    std::vector<double> y(x.size() + h.size() - 1, -0.0);
    for (std::size_t k = 0; k < h.size(); ++k)
    {
        const double hk = h[k];
        if (hk == 0.0)
            continue;
        double* out = y.data() + k;
        for (std::size_t n = 0; n < x.size(); ++n)
            out[n] += hk * static_cast<double>(x[n]);
    }
    return y;
}

// In-place iterative radix-2 FFT (Cooley-Tukey, decimation in time). data.size() must be a power
// of two. Twiddles are computed directly with cos/sin for each index (no recurrence), so the error
// stays near machine precision for large sizes. inverse = true computes the unscaled inverse.
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
        {
            for (std::size_t k = 0; k < half; ++k)
            {
                const Complex t = twiddle[k * step] * data[start + k + half];
                data[start + k + half] = data[start + k] - t;
                data[start + k] += t;
            }
        }
    }
}

std::vector<double> convolveFft(const std::vector<float>& x, const std::vector<float>& h)
{
    const std::size_t outLength = x.size() + h.size() - 1;
    std::size_t n = 1;
    while (n < outLength)
        n <<= 1;

    std::vector<Complex> a(n), b(n);
    for (std::size_t i = 0; i < x.size(); ++i)
        a[i] = Complex(static_cast<double>(x[i]), 0.0);
    for (std::size_t i = 0; i < h.size(); ++i)
        b[i] = Complex(static_cast<double>(h[i]), 0.0);

    fft(a, false);
    fft(b, false);
    for (std::size_t i = 0; i < n; ++i)
        a[i] *= b[i];
    fft(a, true);

    std::vector<double> y(outLength);
    const double scale = 1.0 / static_cast<double>(n);
    for (std::size_t i = 0; i < outLength; ++i)
        y[i] = a[i].real() * scale;
    return y;
}

} // namespace

ConvolutionMethod chooseMethod(std::size_t inputLength, std::size_t irLength,
                               std::size_t nonZeroTaps) noexcept
{
    (void)irLength;
    constexpr std::size_t kDirectWorkLimit = std::size_t{1} << 26;
    constexpr std::size_t kSparseTapLimit = 64;
    if (nonZeroTaps <= kSparseTapLimit)
        return ConvolutionMethod::Direct;
    if (inputLength == 0 || nonZeroTaps <= kDirectWorkLimit / inputLength)
        return ConvolutionMethod::Direct;
    return ConvolutionMethod::Fft;
}

std::vector<double> convolve(const std::vector<float>& x, const std::vector<float>& h,
                             ConvolutionMethod method)
{
    if (x.empty() || h.empty())
        return {};
    if (method == ConvolutionMethod::Auto)
        method = chooseMethod(x.size(), h.size(), countNonZero(h));
    return method == ConvolutionMethod::Fft ? convolveFft(x, h) : convolveDirect(x, h);
}

MultiChannel renderOffline(const RoomIR& ir, const MultiChannel& input, ConvolutionMethod method)
{
    if (ir.numEmitters <= 0 || ir.numOutputs <= 0
        || ir.taps.size()
               != static_cast<std::size_t>(ir.numEmitters) * static_cast<std::size_t>(ir.numOutputs))
        throw std::invalid_argument("renderOffline: malformed RoomIR");
    const std::size_t irLength = ir.length();
    for (const auto& taps : ir.taps)
        if (taps.size() != irLength || irLength == 0)
            throw std::invalid_argument("renderOffline: RoomIR taps must be non-empty and of equal length");
    if (input.size() != static_cast<std::size_t>(ir.numEmitters))
        throw std::invalid_argument("renderOffline: input has " + std::to_string(input.size())
                                    + " channels, the IR expects " + std::to_string(ir.numEmitters));
    const std::size_t inLength = input.front().size();
    for (const auto& channel : input)
        if (channel.size() != inLength)
            throw std::invalid_argument("renderOffline: input channels differ in length");

    MultiChannel out(static_cast<std::size_t>(ir.numOutputs));
    if (inLength == 0)
        return out;

    const std::size_t outLength = inLength + irLength - 1;
    for (int o = 0; o < ir.numOutputs; ++o)
    {
        std::vector<double> sum(outLength, -0.0); // -0.0: exact additive identity (see convolveDirect)
        for (int e = 0; e < ir.numEmitters; ++e)
        {
            const auto part = convolve(input[static_cast<std::size_t>(e)], ir.ir(e, o), method);
            for (std::size_t n = 0; n < outLength; ++n)
                sum[n] += part[n];
        }
        auto& channel = out[static_cast<std::size_t>(o)];
        channel.resize(outLength);
        for (std::size_t n = 0; n < outLength; ++n)
            channel[n] = static_cast<float>(sum[n]);
    }
    return out;
}

} // namespace sim
