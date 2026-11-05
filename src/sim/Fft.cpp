#include "sim/Fft.h"

#include <cmath>
#include <numbers>
#include <stdexcept>
#include <utility>

namespace sim {

std::size_t Fft::nextPowerOfTwo(std::size_t n) noexcept
{
    std::size_t p = 1;
    while (p < n)
        p <<= 1;
    return p;
}

Fft::Fft(std::size_t size)
    : size_(size)
{
    if (size == 0 || (size & (size - 1)) != 0)
        throw std::invalid_argument("Fft: size must be a power of two");
    twiddle_.resize(size / 2);
    for (std::size_t k = 0; k < size / 2; ++k)
    {
        const double angle = -2.0 * std::numbers::pi * static_cast<double>(k) / static_cast<double>(size);
        twiddle_[k] = {std::cos(angle), std::sin(angle)};
    }
}

void Fft::transform(std::vector<std::complex<double>>& data, bool inverse) const
{
    if (data.size() != size_)
        throw std::invalid_argument("Fft: data size differs from the transform size");
    const std::size_t n = size_;
    for (std::size_t i = 1, j = 0; i < n; ++i)
    {
        std::size_t bit = n >> 1;
        for (; (j & bit) != 0; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            std::swap(data[i], data[j]);
    }
    for (std::size_t len = 2; len <= n; len <<= 1)
    {
        const std::size_t half = len / 2;
        const std::size_t step = n / len;
        for (std::size_t start = 0; start < n; start += len)
            for (std::size_t k = 0; k < half; ++k)
            {
                const std::complex<double> w = inverse ? std::conj(twiddle_[k * step]) : twiddle_[k * step];
                const std::complex<double> t = w * data[start + k + half];
                data[start + k + half] = data[start + k] - t;
                data[start + k] += t;
            }
    }
}

} // namespace sim
