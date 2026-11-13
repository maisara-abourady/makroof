#pragma once

// Phase-07c-1b D-B1 (B1-b; docs/review/phase-07c-1b/4-decider-decision-r1.md items 1-3,
// 8-decider-decision-r2.md): the callback instrument of the condition 12 (c) record. A test thread standing
// in for a host audio thread:
//   - platform audio priority: macOS THREAD_TIME_CONSTRAINT_POLICY (period = constraint = the callback period
//     in mach absolute units, computation half of it); Windows MMCSS "Pro Audio"; Linux SCHED_FIFO (else the
//     error is printed: GitHub-hosted runners have RLIMIT_RTPRIO 0);
//   - absolute-deadline pacing: sleep until ~100 us before the deadline, then spin (Windows: a
//     high-resolution waitable timer where available, and timeBeginPeriod(1); the resolution in force is
//     printed);
//   - the calling thread's CPU time (Windows: QueryThreadCycleTime at a cycle rate measured on this thread;
//     POSIX / macOS: CLOCK_THREAD_CPUTIME_ID, macOS thread_info where that clock is missing).
// Test code only; records, never asserted. Nothing here touches src/.
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <string>
#include <thread>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
// windows.h first: avrt.h and mmsystem.h need its types.
#include <avrt.h>
#include <mmsystem.h>
#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION // Windows 10 1803 SDK and later
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif
#elif defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <mach/thread_policy.h>
#include <pthread.h>
#include <time.h>
#else
#include <cerrno>
#include <cstring>
#include <pthread.h>
#include <sched.h>
#include <sys/resource.h>
#include <time.h>
#endif

namespace rt_probe {

using Clock = std::chrono::steady_clock;

// Raises the CALLING thread to the platform's audio priority for callbacks of `periodUs`; returns what was
// obtained, in words (printed by the record). Undone by AudioPriority's destructor where the platform needs
// it.
class AudioPriority
{
public:
    explicit AudioPriority(double periodUs)
    {
        (void)periodUs; // macOS only (the time-constraint period)
        char buf[256];
#if defined(_WIN32)
        DWORD taskIndex = 0;
        task_ = AvSetMmThreadCharacteristicsW(L"Pro Audio", &taskIndex);
        if (task_ != nullptr)
        {
            obtained_ = true;
            std::snprintf(buf, sizeof(buf),
                          "MMCSS \"Pro Audio\" (task index %lu, thread priority %d after the call)",
                          static_cast<unsigned long>(taskIndex), GetThreadPriority(GetCurrentThread()));
        }
        else
            std::snprintf(buf, sizeof(buf),
                          "priority: not available (MMCSS \"Pro Audio\" failed, GetLastError %lu)",
                          static_cast<unsigned long>(GetLastError()));
#elif defined(__APPLE__)
        mach_timebase_info_data_t tb{};
        mach_timebase_info(&tb);
        // ns -> mach absolute units: abs = ns * denom / numer.
        const double absPerNs = static_cast<double>(tb.denom) / static_cast<double>(tb.numer);
        thread_time_constraint_policy_data_t pol{};
        pol.period = static_cast<uint32_t>(periodUs * 1000.0 * absPerNs);
        pol.computation = pol.period / 2;
        pol.constraint = pol.period;
        pol.preemptible = 1;
        const thread_port_t self = pthread_mach_thread_np(pthread_self());
        const kern_return_t kr = thread_policy_set(self, THREAD_TIME_CONSTRAINT_POLICY,
                                                   reinterpret_cast<thread_policy_t>(&pol),
                                                   THREAD_TIME_CONSTRAINT_POLICY_COUNT);
        if (kr == KERN_SUCCESS)
        {
            thread_time_constraint_policy_data_t got{};
            mach_msg_type_number_t count = THREAD_TIME_CONSTRAINT_POLICY_COUNT;
            boolean_t getDefault = FALSE;
            const kern_return_t kg = thread_policy_get(self, THREAD_TIME_CONSTRAINT_POLICY,
                                                       reinterpret_cast<thread_policy_t>(&got), &count,
                                                       &getDefault);
            obtained_ = kg == KERN_SUCCESS && getDefault == FALSE;
            std::snprintf(buf, sizeof(buf),
                          "THREAD_TIME_CONSTRAINT_POLICY %s (period %u, computation %u, constraint %u mach "
                          "units; timebase %u/%u)",
                          obtained_ ? "in force" : "set but not read back", got.period, got.computation,
                          got.constraint, tb.numer, tb.denom);
        }
        else
            std::snprintf(buf, sizeof(buf),
                          "priority: not available (THREAD_TIME_CONSTRAINT_POLICY kern_return %d)", kr);
#else
        sched_param sp{};
        const int maxPrio = sched_get_priority_max(SCHED_FIFO);
        // A typical audio-server priority (below the kernel's own real-time threads).
        sp.sched_priority = maxPrio > 80 ? 80 : maxPrio;
        const int rc = pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp);
        rlimit rl{};
        const long long rtLimit = getrlimit(RLIMIT_RTPRIO, &rl) == 0 ? static_cast<long long>(rl.rlim_cur)
                                                                     : -1LL;
        if (rc == 0)
        {
            int policy = 0;
            sched_param got{};
            pthread_getschedparam(pthread_self(), &policy, &got);
            obtained_ = policy == SCHED_FIFO;
            std::snprintf(buf, sizeof(buf), "SCHED_FIFO priority %d (%s; RLIMIT_RTPRIO %lld)",
                          got.sched_priority, obtained_ ? "in force" : "not read back", rtLimit);
        }
        else
            std::snprintf(buf, sizeof(buf), "priority: not available (errno %d: %s; RLIMIT_RTPRIO %lld)", rc,
                          std::strerror(rc), rtLimit);
#endif
        description_ = buf;
    }
    ~AudioPriority()
    {
#if defined(_WIN32)
        if (task_ != nullptr)
            AvRevertMmThreadCharacteristics(task_);
#endif
    }
    AudioPriority(const AudioPriority&) = delete;
    AudioPriority& operator=(const AudioPriority&) = delete;
    bool obtained() const noexcept { return obtained_; }
    const std::string& description() const noexcept { return description_; }

private:
    bool obtained_ = false;
    std::string description_;
#if defined(_WIN32)
    HANDLE task_ = nullptr;
#endif
};

// Absolute-deadline pacing: waitUntil(deadline) sleeps until kSpin before the deadline, then spins.
class Pacer
{
public:
    static constexpr std::chrono::microseconds kSpin{100};
    Pacer()
    {
#if defined(_WIN32)
        periodSet_ = timeBeginPeriod(1) == TIMERR_NOERROR;
        timer_ = CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                                        TIMER_ALL_ACCESS);
        highRes_ = timer_ != nullptr;
        if (timer_ == nullptr)
            timer_ = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
#endif
    }
    ~Pacer()
    {
#if defined(_WIN32)
        if (timer_ != nullptr)
            CloseHandle(timer_);
        if (periodSet_)
            timeEndPeriod(1);
#endif
    }
    Pacer(const Pacer&) = delete;
    Pacer& operator=(const Pacer&) = delete;

    void waitUntil(Clock::time_point deadline) const
    {
        const auto wake = deadline - kSpin;
        const auto now = Clock::now();
        if (now < wake)
        {
#if defined(_WIN32)
            if (timer_ != nullptr)
            {
                LARGE_INTEGER due{};
                // Relative due time in 100 ns units (negative = relative).
                due.QuadPart = -static_cast<LONGLONG>(
                    std::chrono::duration_cast<std::chrono::nanoseconds>(wake - now).count() / 100);
                if (SetWaitableTimer(timer_, &due, 0, nullptr, nullptr, FALSE))
                    WaitForSingleObject(timer_, INFINITE);
            }
            else
                std::this_thread::sleep_until(wake);
#else
            std::this_thread::sleep_until(wake);
#endif
        }
        while (Clock::now() < deadline)
        {}
    }

    // The timer mechanism and the resolution in force, in words, with the mean and worst overshoot of 20
    // sleeps of 500 us through the same sleep, measured on the calling thread.
    std::string describe() const
    {
        double worst = 0.0, sum = 0.0;
        for (int i = 0; i < 20; ++i)
        {
            const auto t0 = Clock::now();
            const auto target = t0 + std::chrono::microseconds(500);
#if defined(_WIN32)
            if (timer_ != nullptr)
            {
                LARGE_INTEGER due{};
                due.QuadPart = -5000; // 500 us
                if (SetWaitableTimer(timer_, &due, 0, nullptr, nullptr, FALSE))
                    WaitForSingleObject(timer_, INFINITE);
            }
            else
                std::this_thread::sleep_until(target);
#else
            std::this_thread::sleep_until(target);
#endif
            const double over = std::chrono::duration<double, std::micro>(Clock::now() - target).count();
            worst = over > worst ? over : worst;
            sum += over;
        }
        char buf[256];
#if defined(_WIN32)
        // The system timer resolution in force (ntdll NtQueryTimerResolution, 100 ns units), if reachable.
        double currentMs = -1.0;
        if (HMODULE nt = GetModuleHandleW(L"ntdll.dll"))
        {
            using QueryFn = LONG(WINAPI*)(PULONG, PULONG, PULONG);
            const auto fn = reinterpret_cast<QueryFn>(
                reinterpret_cast<void*>(GetProcAddress(nt, "NtQueryTimerResolution")));
            ULONG coarsest = 0, finest = 0, current = 0;
            if (fn != nullptr && fn(&coarsest, &finest, &current) == 0)
                currentMs = current / 10000.0;
        }
        std::snprintf(buf, sizeof(buf),
                      "timer: %s waitable timer, timeBeginPeriod(1) %s, system resolution in force %.3f ms; "
                      "500 us sleep overshoot mean %.0f us, worst %.0f us",
                      highRes_ ? "high-resolution" : "standard", periodSet_ ? "ok" : "failed", currentMs,
                      sum / 20.0, worst);
#else
        std::snprintf(
            buf, sizeof(buf),
            "timer: std::this_thread::sleep_until; 500 us sleep overshoot mean %.0f us, worst %.0f us",
            sum / 20.0, worst);
#endif
        return buf;
    }

private:
#if defined(_WIN32)
    HANDLE timer_ = nullptr;
    bool highRes_ = false;
    bool periodSet_ = false;
#endif
};

// The calling thread's CPU time in ns. Construct on the thread that is measured (Windows measures the
// cycle rate there: QueryThreadCycleTime against the steady clock over a ~50 ms spin).
class ThreadCpuClock
{
public:
    ThreadCpuClock()
    {
#if defined(_WIN32)
        ULONG64 c0 = 0, c1 = 0;
        const auto t0 = Clock::now();
        QueryThreadCycleTime(GetCurrentThread(), &c0);
        while (Clock::now() - t0 < std::chrono::milliseconds(50))
        {}
        QueryThreadCycleTime(GetCurrentThread(), &c1);
        const double ns = std::chrono::duration<double, std::nano>(Clock::now() - t0).count();
        cyclesPerNs_ = ns > 0.0 ? static_cast<double>(c1 - c0) / ns : 0.0;
#endif
    }
    double nowNs() const
    {
#if defined(_WIN32)
        ULONG64 c = 0;
        QueryThreadCycleTime(GetCurrentThread(), &c);
        return cyclesPerNs_ > 0.0 ? static_cast<double>(c) / cyclesPerNs_ : 0.0;
#elif defined(CLOCK_THREAD_CPUTIME_ID)
        timespec ts{};
        clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
        return static_cast<double>(ts.tv_sec) * 1e9 + static_cast<double>(ts.tv_nsec);
#elif defined(__APPLE__)
        thread_basic_info_data_t info{};
        mach_msg_type_number_t count = THREAD_BASIC_INFO_COUNT;
        const thread_port_t self = pthread_mach_thread_np(pthread_self());
        if (thread_info(self, THREAD_BASIC_INFO, reinterpret_cast<thread_info_t>(&info), &count)
            != KERN_SUCCESS)
            return 0.0;
        return (static_cast<double>(info.user_time.seconds + info.system_time.seconds) * 1e9)
               + static_cast<double>(info.user_time.microseconds + info.system_time.microseconds) * 1e3;
#else
        return 0.0;
#endif
    }
    std::string describe() const
    {
        char buf[160];
#if defined(_WIN32)
        std::snprintf(buf, sizeof(buf), "thread CPU: QueryThreadCycleTime at a measured %.3f cycles/ns",
                      cyclesPerNs_);
#elif defined(CLOCK_THREAD_CPUTIME_ID)
        std::snprintf(buf, sizeof(buf), "thread CPU: clock_gettime(CLOCK_THREAD_CPUTIME_ID)");
#elif defined(__APPLE__)
        std::snprintf(buf, sizeof(buf), "thread CPU: thread_info(THREAD_BASIC_INFO), us resolution");
#else
        std::snprintf(buf, sizeof(buf), "thread CPU: not available");
#endif
        return buf;
    }

private:
#if defined(_WIN32)
    double cyclesPerNs_ = 0.0;
#endif
};

} // namespace rt_probe
