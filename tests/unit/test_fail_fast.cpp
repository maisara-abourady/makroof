// Phase 06b scope 5: the crash probe behind the ctest entry `fail_fast_crash_probe`
// (tests/unit/CMakeLists.txt). Hidden ([.]): it never runs in the normal suite. ctest runs it alone,
// expects it to fail (WILL_FAIL) and gives it 30 s; a probe that hangs instead is a ctest Timeout,
// which WILL_FAIL does not excuse, so the entry then fails.
//
// The probe aborts while another thread holds the stdout lock. With Catch2's POSIX fatal-signal
// handler (removed in 06b, tests/support/FailFast.cpp) the handler blocked on that lock and the binary
// hung until the timeout; without it the process ends with SIGABRT at once.
#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

namespace {

void lockStdout() noexcept
{
#if defined(_WIN32)
    _lock_file(stdout);
#else
    flockfile(stdout);
#endif
}

} // namespace

TEST_CASE("fail-fast probe: abort while another thread holds the stdout lock", "[.][crash-probe]")
{
    std::thread([] {
        lockStdout(); // never released: the process ends with the abort below
        for (;;)
            std::this_thread::sleep_for(std::chrono::seconds(1));
    }).detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::abort();
}
