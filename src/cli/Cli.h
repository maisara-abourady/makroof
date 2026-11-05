#pragma once

// render_cli's command-line logic, in a library so tests can run it in-process (tests/unit/test_cli.cpp).
//
//   render_cli --scene <json> --in <wav> --out <wav> [--rate <hz>] [--mode omni|binaural|stereoSpeakers]
//   render_cli --scene <json> --ir <wav> [--rate <hz>] [--mode ...]
//   (--in/--out and --ir can be combined in one call)
//
// Exit codes (kExit*, BUILD_PLAN AX12): 0 ok, 1 usage error, 2 invalid scene (validation errors
// printed), 3 I/O error, 4 internal error (an unexpected exception, e.g. out of memory).
#include <iosfwd>
#include <string>
#include <vector>

namespace cli {

inline constexpr int kExitOk = 0;
inline constexpr int kExitUsage = 1;
inline constexpr int kExitInvalidScene = 2;
inline constexpr int kExitIo = 3;
inline constexpr int kExitInternal = 4;

// Default sample rate of an IR-only render (--ir without --in or --rate).
inline constexpr double kDefaultIrSampleRateHz = 48000.0;

// args excludes the program name. Messages go to `out` (normal output) and `err` (errors, warnings).
// Never throws: an unexpected exception is reported on `err` and returns kExitInternal.
int runCli(const std::vector<std::string>& args, std::ostream& out, std::ostream& err);

// Usage text printed by --help and after a usage error.
std::string usage();

} // namespace cli
