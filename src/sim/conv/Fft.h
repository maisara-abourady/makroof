#pragma once

// Thin wrapper over PFFFT (single precision, real transforms) for the real-time convolver
// (Phase 06). Not to be confused with sim::Fft (sim/Fft.h), the double-precision complex FFT of the
// offline IR builder and the reference renderer, which must stay independent of this one.
//
// Spectra are kept in PFFFT's internal ("z-domain", unordered) layout: that is the layout
// pffft_zconvolve_accumulate expects, and it saves the reordering on every block. A spectrum of a
// size-N transform is N floats. Only multiplyAccumulate() and inverse() may consume it; use
// forwardOrdered() when the bins are needed in the usual order (tests).
//
// All buffers handed to Fft must be SIMD-aligned: allocate them with allocateAligned().
#include <cstddef>
#include <memory>

struct PFFFT_Setup;

namespace sim::conv {

struct AlignedFree
{
    void operator()(float* p) const noexcept;
};
using AlignedFloats = std::unique_ptr<float[], AlignedFree>;

// `count` zero-initialised floats, 64-byte aligned. Throws std::bad_alloc. Not for the audio thread.
AlignedFloats allocateAligned(std::size_t count);

class Fft
{
public:
    // size: the real transform length N, a power of two >= 32 (PFFFT's minimum for real
    // transforms). All allocation happens here (setup and work buffer). Throws
    // std::invalid_argument for an unsupported size.
    explicit Fft(int size);
    ~Fft();
    Fft(Fft&& other) noexcept;
    Fft& operator=(Fft&& other) noexcept;
    Fft(const Fft&) = delete;
    Fft& operator=(const Fft&) = delete;

    int size() const noexcept { return size_; }

    // The methods below are real-time safe (no allocation, no locks) but not reentrant: each uses
    // this object's work buffer, so one Fft must not be used by two threads at once.

    // N real samples -> N floats of spectrum in the z-domain layout. in and out may alias.
    void forward(const float* in, float* spectrum) noexcept;
    // Unscaled inverse: inverse(forward(x)) = N * x. spectrum and out may alias.
    void inverse(const float* spectrum, float* out) noexcept;
    // ab += a * b * scale, bin by bin (complex products; DC and Nyquist real), z-domain layout.
    void multiplyAccumulate(const float* a, const float* b, float* ab, float scale) noexcept;
    // Forward transform with ordered output: out[0] = DC, out[1] = Nyquist, then (re, im) of bins
    // 1 .. N/2 - 1. For tests.
    void forwardOrdered(const float* in, float* out) noexcept;

    // PFFFT's SIMD backend name ("SSE1", "NEON", "scalar", ...), for the benchmark log.
    static const char* simdArch() noexcept;

private:
    void release() noexcept;

    int size_ = 0;
    PFFFT_Setup* setup_ = nullptr;
    AlignedFloats work_;
};

} // namespace sim::conv
