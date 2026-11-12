#pragma once

// Phase-07c-1 condition 11 (D-H3 (e); AX38 (i), half (2)): the host-trace instrument. A diagnostic build
// (CMake option SPATIAL_HOST_TRACE, default OFF, never in a release artefact: tools/ci/test_host_trace.py)
// records every host entry point of the plugin (prepareToPlay, releaseResources, reset, setNonRealtime,
// processBlock, get/setStateInformation): entry id, native thread id, isNonRealtime(), transport state,
// block size, start time and duration. Records go into a preallocated, bounded, lock-free ring and a
// drain thread writes them off-thread as text lines; nothing on the real-time path allocates, locks, logs
// or makes a system call (tests/unit/test_host_trace.cpp, the allocation-tracker test).
//
// The ring is the plan's "preallocated SPSC ring" generalised to several producers: host entry points
// arrive on several threads (the processing thread, the UI / message thread, a host's state thread), so
// a single-producer ring would race. It is D. Vyukov's bounded queue (one sequence number per slot, one
// CAS per push): lock-free for the producers, single consumer (the drain thread). A full ring drops the
// record and counts it (never blocks, never allocates).
//
// The per-host measurement itself (Live, Logic, Cubase, Bitwig, REAPER, FL Studio, Studio One on macOS
// arm64 and Windows x64) is a person's action and does not gate the phase (condition 11).
// JUCE-free: the plugin adapter supplies the transport state.
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

namespace plugin::trace {

enum class Entry : std::uint8_t
{
    PrepareToPlay,
    ReleaseResources,
    Reset,
    SetNonRealtime,
    ProcessBlock,
    GetState,
    SetState
};
const char* entryName(Entry e) noexcept;

// Transport as the host reports it (JUCE AudioPlayHead): unknown when the host gives no position.
enum class Transport : std::int8_t
{
    Unknown = -1,
    Stopped = 0,
    Playing = 1
};

struct Record
{
    Entry entry = Entry::ProcessBlock;
    bool nonRealtime = false;
    Transport transport = Transport::Unknown;
    std::int32_t blockSize = 0; // processBlock: samples; prepareToPlay: the maximum block; else 0
    std::uint64_t threadId = 0; // native id (pthread / GetCurrentThreadId)
    std::uint64_t startNs = 0;  // steady clock, from the ring's construction
    std::uint64_t durationNs = 0;
    std::int64_t argument = 0; // setNonRealtime: the flag; setState: bytes; else 0
};

// The native id of the calling thread. No allocation, no lock, no system call on Linux and macOS
// (pthread_self / pthread_threadid_np read thread-local data); GetCurrentThreadId on Windows reads the TEB.
std::uint64_t nativeThreadId() noexcept;

class Ring
{
public:
    // capacity: a power of two >= 2. Allocates here, never afterwards.
    explicit Ring(std::size_t capacity);
    Ring(const Ring&) = delete;
    Ring& operator=(const Ring&) = delete;

    // Any thread, real-time safe: lock-free, no allocation. False (and counted) when the ring is full.
    bool push(const Record& r) noexcept;
    // The single consumer.
    bool pop(Record& r) noexcept;
    std::uint64_t dropped() const noexcept { return dropped_.load(std::memory_order_relaxed); }
    std::size_t capacity() const noexcept { return mask_ + 1; }

private:
    struct Slot
    {
        std::atomic<std::size_t> sequence{0};
        Record record;
    };
    std::unique_ptr<Slot[]> slots_;
    std::size_t mask_;
    alignas(64) std::atomic<std::size_t> enqueue_{0};
    alignas(64) std::atomic<std::size_t> dequeue_{0};
    std::atomic<std::uint64_t> dropped_{0};
};

// The ring plus its drain thread, which writes one text line per record to `path` (opened here, off the
// audio thread) every kDrainPeriodMs and at destruction.
class Logger
{
public:
    static constexpr std::size_t kCapacity = std::size_t{1} << 16;
    static constexpr int kDrainPeriodMs = 50;

    explicit Logger(const std::string& path, std::size_t capacity = kCapacity);
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::uint64_t nowNs() const noexcept;
    bool push(const Record& r) noexcept { return ring_.push(r); }
    std::uint64_t written() const noexcept { return written_.load(std::memory_order_relaxed); }
    std::uint64_t dropped() const noexcept { return ring_.dropped(); }
    bool isOpen() const noexcept { return file_ != nullptr; }

private:
    void drain();

    Ring ring_;
    std::chrono::steady_clock::time_point origin_;
    std::FILE* file_ = nullptr;
    std::atomic<std::uint64_t> written_{0};
    std::mutex mutex_; // the drain thread's sleep only; never taken by a producer
    std::condition_variable cv_;
    bool stop_ = false;
    std::thread thread_;
};

// Times one host entry point and pushes its record on scope exit (real-time safe).
class Scope
{
public:
    Scope(Logger* logger, Entry entry, bool nonRealtime, Transport transport, std::int32_t blockSize,
          std::int64_t argument = 0) noexcept;
    ~Scope();
    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

private:
    Logger* logger_;
    Record record_;
};

} // namespace plugin::trace
