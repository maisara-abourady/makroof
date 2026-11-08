#pragma once

// Counts heap allocations (and frees) made through global operator new / delete on a flagged thread (phase-06
// scope 6). AllocationTracker.cpp replaces every global operator new / delete of the test binary; the
// replacements count an allocation only while the calling thread is inside a ScopedTracking, so
// other threads (Catch2, the OS, worker threads in the test) don't interfere.
//
//   {
//       test_support::ScopedTracking tracking;
//       convolver.process(...);
//       REQUIRE(tracking.allocations() == 0);
//   }
//
// malloc / calloc / realloc called directly are not seen (only operator new). The real-time code
// under test never calls them either (PFFFT allocates only in setup, which prepare() does).
#include <cstddef>

namespace test_support {

// False in AddressSanitizer builds, where operator new / delete are left to ASan (see the .cpp) and
// nothing is counted; tests skip their allocation assertions then.
bool trackerActive() noexcept;
// Allocations by operator new on this thread since the tracker started, while tracking was on.
std::size_t trackedAllocations() noexcept;
// Non-null pointers freed by operator delete on this thread while tracking was on.
std::size_t trackedDeallocations() noexcept;

class ScopedTracking
{
public:
    ScopedTracking() noexcept;
    ~ScopedTracking();
    ScopedTracking(const ScopedTracking&) = delete;
    ScopedTracking& operator=(const ScopedTracking&) = delete;

    // Allocations on this thread since this scope started.
    std::size_t allocations() const noexcept;
    // Frees through operator delete on this thread since this scope started (an IrSet released on
    // the audio thread would show here).
    std::size_t deallocations() const noexcept;

private:
    std::size_t start_ = 0;
    std::size_t startFrees_ = 0;
    bool previous_ = false;
};

} // namespace test_support
