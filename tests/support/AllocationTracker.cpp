#include "AllocationTracker.h"

#include <cstdlib>
#include <new>

#if defined(_WIN32)
#include <malloc.h>
#endif

namespace {

// Plain (trivially constructible) thread_locals: reading them never allocates.
thread_local bool tTracking = false;
thread_local std::size_t tCount = 0;
thread_local std::size_t tFrees = 0;

void noteFree(void* p) noexcept
{
    if (tTracking && p != nullptr)
        ++tFrees;
}

void noteAllocation() noexcept
{
    if (tTracking)
        ++tCount;
}

void* allocate(std::size_t size)
{
    noteAllocation();
    for (;;)
    {
        if (void* p = std::malloc(size == 0 ? 1 : size))
            return p;
        std::new_handler handler = std::get_new_handler();
        if (handler == nullptr)
            throw std::bad_alloc();
        handler();
    }
}

void* allocateAligned(std::size_t size, std::size_t alignment)
{
    noteAllocation();
    if (alignment < sizeof(void*))
        alignment = sizeof(void*);
    const std::size_t n = size == 0 ? 1 : size;
    for (;;)
    {
#if defined(_WIN32)
        void* p = _aligned_malloc(n, alignment);
#else
        void* p = nullptr;
        if (posix_memalign(&p, alignment, n) != 0)
            p = nullptr;
#endif
        if (p != nullptr)
            return p;
        std::new_handler handler = std::get_new_handler();
        if (handler == nullptr)
            throw std::bad_alloc();
        handler();
    }
}

void freeAligned(void* p) noexcept
{
#if defined(_WIN32)
    _aligned_free(p);
#else
    std::free(p);
#endif
}

} // namespace

namespace test_support {

std::size_t trackedAllocations() noexcept
{
    return tCount;
}

std::size_t trackedDeallocations() noexcept
{
    return tFrees;
}

ScopedTracking::ScopedTracking() noexcept
    : start_(tCount)
    , startFrees_(tFrees)
    , previous_(tTracking)
{
    tTracking = true;
}

ScopedTracking::~ScopedTracking()
{
    tTracking = previous_;
}

std::size_t ScopedTracking::allocations() const noexcept
{
    return tCount - start_;
}

std::size_t ScopedTracking::deallocations() const noexcept
{
    return tFrees - startFrees_;
}

} // namespace test_support

// ---- Replacements of the global allocation functions ([replacement.functions]) ----

void* operator new(std::size_t size)
{
    return allocate(size);
}
void* operator new[](std::size_t size)
{
    return allocate(size);
}
void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    try
    {
        return allocate(size);
    }
    catch (...)
    {
        return nullptr;
    }
}
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    try
    {
        return allocate(size);
    }
    catch (...)
    {
        return nullptr;
    }
}
void* operator new(std::size_t size, std::align_val_t alignment)
{
    return allocateAligned(size, static_cast<std::size_t>(alignment));
}
void* operator new[](std::size_t size, std::align_val_t alignment)
{
    return allocateAligned(size, static_cast<std::size_t>(alignment));
}
void* operator new(std::size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept
{
    try
    {
        return allocateAligned(size, static_cast<std::size_t>(alignment));
    }
    catch (...)
    {
        return nullptr;
    }
}
void* operator new[](std::size_t size, std::align_val_t alignment, const std::nothrow_t&) noexcept
{
    try
    {
        return allocateAligned(size, static_cast<std::size_t>(alignment));
    }
    catch (...)
    {
        return nullptr;
    }
}

void operator delete(void* p) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete[](void* p) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete(void* p, std::size_t) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete[](void* p, std::size_t) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete(void* p, const std::nothrow_t&) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete[](void* p, const std::nothrow_t&) noexcept
{
    noteFree(p);
    std::free(p);
}
void operator delete(void* p, std::align_val_t) noexcept
{
    noteFree(p);
    freeAligned(p);
}
void operator delete[](void* p, std::align_val_t) noexcept
{
    noteFree(p);
    freeAligned(p);
}
void operator delete(void* p, std::size_t, std::align_val_t) noexcept
{
    noteFree(p);
    freeAligned(p);
}
void operator delete[](void* p, std::size_t, std::align_val_t) noexcept
{
    noteFree(p);
    freeAligned(p);
}
void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept
{
    noteFree(p);
    freeAligned(p);
}
void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept
{
    noteFree(p);
    freeAligned(p);
}
