// Phase 06b scope 5: the crash probe behind the ctest entry `fail_fast_crash_probe`
// (tests/unit/CMakeLists.txt). Hidden ([.]): it never runs in the normal suite. The ctest entry runs it
// through run_crash_probe.cmake, which passes only if the probe ends by abort() within 30 s; a hang, a
// normal exit or any other exit code (e.g. no test matched) fails the entry.
//
// The probe aborts while another thread holds the stdout lock. With Catch2's POSIX fatal-signal
// handler (removed in 06b: CATCH_CONFIG_NO_POSIX_SIGNALS, cmake/SpatialDependencies.cmake; see
// tests/support/FailFast.cpp) the handler blocked on that lock and the binary
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
