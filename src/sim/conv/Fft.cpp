#include "sim/conv/Fft.h"

#include <pffft.h>

#include <new>
#include <stdexcept>
#include <string>
#include <utility>

namespace sim::conv {

void AlignedFree::operator()(float* p) const noexcept
{
    pffft_aligned_free(p);
}

AlignedFloats allocateAligned(std::size_t count)
{
    const std::size_t n = count == 0 ? 1 : count;
    auto* p = static_cast<float*>(pffft_aligned_malloc(n * sizeof(float)));
    if (p == nullptr)
        throw std::bad_alloc();
    for (std::size_t i = 0; i < n; ++i)
        p[i] = 0.0f;
    return AlignedFloats(p);
}

Fft::Fft(int size)
{
    if (size < 32 || (size & (size - 1)) != 0)
        throw std::invalid_argument("conv::Fft: size must be a power of two >= 32, got "
                                    + std::to_string(size));
    setup_ = pffft_new_setup(size, PFFFT_REAL);
    if (setup_ == nullptr)
        throw std::invalid_argument("conv::Fft: PFFFT rejected size " + std::to_string(size));
    size_ = size;
    try
    {
        work_ = allocateAligned(static_cast<std::size_t>(size));
    }
    catch (...)
    {
        release();
        throw;
    }
}

Fft::~Fft()
{
    release();
}

Fft::Fft(Fft&& other) noexcept
    : size_(std::exchange(other.size_, 0))
    , setup_(std::exchange(other.setup_, nullptr))
    , work_(std::move(other.work_))
{}

Fft& Fft::operator=(Fft&& other) noexcept
{
    if (this != &other)
    {
        release();
        size_ = std::exchange(other.size_, 0);
        setup_ = std::exchange(other.setup_, nullptr);
        work_ = std::move(other.work_);
    }
    return *this;
}

void Fft::release() noexcept
{
    if (setup_ != nullptr)
        pffft_destroy_setup(setup_);
    setup_ = nullptr;
}

void Fft::forward(const float* in, float* spectrum) noexcept
{
    pffft_transform(setup_, in, spectrum, work_.get(), PFFFT_FORWARD);
}

void Fft::inverse(const float* spectrum, float* out) noexcept
{
    pffft_transform(setup_, spectrum, out, work_.get(), PFFFT_BACKWARD);
}

void Fft::multiplyAccumulate(const float* a, const float* b, float* ab, float scale) noexcept
{
    pffft_zconvolve_accumulate(setup_, a, b, ab, scale);
}

void Fft::forwardOrdered(const float* in, float* out) noexcept
{
    pffft_transform_ordered(setup_, in, out, work_.get(), PFFFT_FORWARD);
}

const char* Fft::simdArch() noexcept
{
    return pffft_simd_arch();
}

} // namespace sim::conv
