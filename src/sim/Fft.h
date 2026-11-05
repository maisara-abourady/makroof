#pragma once

// A plain radix-2 complex FFT in double precision for the offline IR builder (late tail, Phase 04).
// Twiddles are computed once per size with std::cos / std::sin per index (no recurrence), so the
// result is deterministic and accurate to ~1e-15 relative. Not real-time code: the real-time
// convolver (Phase 06) uses PFFFT.
#include <complex>
#include <cstddef>
#include <vector>

namespace sim {

class Fft
{
public:
    // size must be a power of two >= 1.
    explicit Fft(std::size_t size);

    std::size_t size() const noexcept { return size_; }

    // In place. forward: X[k] = sum x[n] e^{-2 pi i k n / N}; inverse is the unscaled
    // conjugate transform (divide by size() to invert).
    void forward(std::vector<std::complex<double>>& data) const { transform(data, false); }
    void inverse(std::vector<std::complex<double>>& data) const { transform(data, true); }

    // Smallest power of two >= n (n >= 1).
    static std::size_t nextPowerOfTwo(std::size_t n) noexcept;

private:
    void transform(std::vector<std::complex<double>>& data, bool inverse) const;

    std::size_t size_;
    std::vector<std::complex<double>> twiddle_; // e^{-2 pi i k / N}, k < N / 2
};

} // namespace sim
