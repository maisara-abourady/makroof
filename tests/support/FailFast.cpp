// Phase 06b scope 5: a crashing test ends the test binary at once instead of stalling until the
// 600 s ctest timeout.
//   - POSIX: Catch2 is built with CATCH_CONFIG_NO_POSIX_SIGNALS (cmake/SpatialDependencies.cmake), so
//     no fatal-signal handler runs non-async-signal-safe code (stdout, the heap) after a crash.
//   - MSVC: abort() would show the "abort() has been called" message box (Debug CRT) or start Windows
//     Error Reporting, and a failed CRT assertion would open its dialog; on a CI runner nobody clicks
//     them. Here they write to stderr and the process exits.
// ctest runs each test case as its own process (catch_discover_tests), so a crash is reported
// against the test that crashed.
#if defined(_MSC_VER)
#include <crtdbg.h>
#include <stdlib.h>
#include <windows.h>

namespace {

struct FailFastOnWindows
{
    FailFastOnWindows() noexcept
    {
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
        // CRT debug reports (assertion dialogs) exist only in Debug builds; the calls are empty otherwise.
#if defined(_DEBUG)
        const int reportTypes[] = {_CRT_WARN, _CRT_ERROR, _CRT_ASSERT};
        for (const int type : reportTypes)
        {
            _CrtSetReportMode(type, _CRTDBG_MODE_FILE);
            _CrtSetReportFile(type, _CRTDBG_FILE_STDERR);
        }
#endif
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
    }
};

const FailFastOnWindows failFastOnWindows;

} // namespace
#endif
