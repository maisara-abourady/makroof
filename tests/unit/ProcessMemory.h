#pragma once

// Resident set of this process in kB, on the three CI platforms (phase-07c-1: the AX38 (i) transient-memory
// records, condition 10 and condition 12 (f), are taken as the PROCESS figure on Linux, macOS and Windows).
// Linux: VmRSS from /proc/self/status; macOS: mach task_basic_info resident_size; Windows: the working set
// (GetProcessMemoryInfo). 0 when it cannot be read.
#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
// windows.h first: psapi.h needs its types.
#include <psapi.h>
#elif defined(__APPLE__)
#include <mach/mach.h>
#else
#include <fstream>
#include <string>
#endif

namespace test_memory {

inline long currentRssKb()
{
#if defined(_WIN32)
    PROCESS_MEMORY_COUNTERS pmc{};
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
        return static_cast<long>(pmc.WorkingSetSize / 1024);
    return 0;
#elif defined(__APPLE__)
    mach_task_basic_info info{};
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, reinterpret_cast<task_info_t>(&info), &count)
        == KERN_SUCCESS)
        return static_cast<long>(info.resident_size / 1024);
    return 0;
#else
    std::ifstream in("/proc/self/status");
    std::string line;
    while (std::getline(in, line))
        if (line.rfind("VmRSS:", 0) == 0)
            return std::stol(line.substr(6));
    return 0;
#endif
}

} // namespace test_memory
