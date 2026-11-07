#pragma once

// Scoped flush-to-zero / denormals-are-zero for the real-time convolver (phase-06 scope 5). sim is
// JUCE-free, so juce::ScopedNoDenormals isn't available; this is the equivalent:
//   - x86 / x86-64 (SSE): MXCSR bits FTZ (15) and DAZ (6);
//   - AArch64: FPCR bit FZ (24), which flushes both denormal inputs and results of single and double
//     precision arithmetic (Arm ARM, "Flush-to-zero").
// The previous state is restored on destruction. Elsewhere (no SSE, 32-bit ARM, MSVC on ARM64) the
// guard does nothing and isSupported() is false. Real-time safe: a register read and write.
#include <cstdint>

#if defined(_M_X64) || defined(__x86_64__) || defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#include <xmmintrin.h>
#define SPATIAL_DENORMALS_SSE 1
#elif defined(__aarch64__) && (defined(__GNUC__) || defined(__clang__))
#define SPATIAL_DENORMALS_AARCH64 1
#endif

namespace sim::conv {

class ScopedFlushDenormals
{
public:
    ScopedFlushDenormals() noexcept
    {
#if defined(SPATIAL_DENORMALS_SSE)
        previous_ = _mm_getcsr();
        _mm_setcsr(static_cast<unsigned int>(previous_) | kSseFtz | kSseDaz);
#elif defined(SPATIAL_DENORMALS_AARCH64)
        std::uint64_t fpcr = 0;
        asm volatile("mrs %0, fpcr" : "=r"(fpcr));
        previous_ = fpcr;
        asm volatile("msr fpcr, %0" : : "r"(fpcr | kArmFz));
#endif
    }

    ~ScopedFlushDenormals() noexcept
    {
#if defined(SPATIAL_DENORMALS_SSE)
        _mm_setcsr(static_cast<unsigned int>(previous_));
#elif defined(SPATIAL_DENORMALS_AARCH64)
        asm volatile("msr fpcr, %0" : : "r"(previous_));
#endif
    }

    ScopedFlushDenormals(const ScopedFlushDenormals&) = delete;
    ScopedFlushDenormals& operator=(const ScopedFlushDenormals&) = delete;

    static constexpr bool isSupported() noexcept
    {
#if defined(SPATIAL_DENORMALS_SSE) || defined(SPATIAL_DENORMALS_AARCH64)
        return true;
#else
        return false;
#endif
    }

private:
    [[maybe_unused]] static constexpr unsigned int kSseFtz = 0x8000u;                // MXCSR bit 15
    [[maybe_unused]] static constexpr unsigned int kSseDaz = 0x0040u;                // MXCSR bit 6
    [[maybe_unused]] static constexpr std::uint64_t kArmFz = std::uint64_t{1} << 24; // FPCR.FZ
    [[maybe_unused]] std::uint64_t previous_ = 0;
};

} // namespace sim::conv
