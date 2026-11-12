#include "plugin/core/HostTrace.h"

#include <cinttypes>
#include <stdexcept>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace plugin::trace {

const char* entryName(Entry e) noexcept
{
    switch (e)
    {
    case Entry::PrepareToPlay:
        return "prepareToPlay";
    case Entry::ReleaseResources:
        return "releaseResources";
    case Entry::Reset:
        return "reset";
    case Entry::SetNonRealtime:
        return "setNonRealtime";
    case Entry::ProcessBlock:
        return "processBlock";
    case Entry::GetState:
        return "getStateInformation";
    case Entry::SetState:
        return "setStateInformation";
    }
    return "?";
}

std::uint64_t nativeThreadId() noexcept
{
#if defined(_WIN32)
    return static_cast<std::uint64_t>(GetCurrentThreadId());
#elif defined(__APPLE__)
    std::uint64_t id = 0;
    pthread_threadid_np(nullptr, &id);
    return id;
#else
    return static_cast<std::uint64_t>(pthread_self());
#endif
}

Ring::Ring(std::size_t capacity)
    : mask_(capacity - 1)
{
    if (capacity < 2 || (capacity & (capacity - 1)) != 0)
        throw std::invalid_argument("trace::Ring: capacity must be a power of two >= 2");
    slots_ = std::make_unique<Slot[]>(capacity);
    for (std::size_t i = 0; i < capacity; ++i)
        slots_[i].sequence.store(i, std::memory_order_relaxed);
}

bool Ring::push(const Record& r) noexcept
{
    std::size_t pos = enqueue_.load(std::memory_order_relaxed);
    for (;;)
    {
        Slot& slot = slots_[pos & mask_];
        const std::size_t seq = slot.sequence.load(std::memory_order_acquire);
        const auto diff = static_cast<std::ptrdiff_t>(seq) - static_cast<std::ptrdiff_t>(pos);
        if (diff == 0)
        {
            if (enqueue_.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed))
            {
                slot.record = r;
                slot.sequence.store(pos + 1, std::memory_order_release);
                return true;
            }
        }
        else if (diff < 0)
        {
            dropped_.fetch_add(1, std::memory_order_relaxed); // full: drop, never block
            return false;
        }
        else
            pos = enqueue_.load(std::memory_order_relaxed);
    }
}

bool Ring::pop(Record& r) noexcept
{
    const std::size_t pos = dequeue_.load(std::memory_order_relaxed);
    Slot& slot = slots_[pos & mask_];
    const std::size_t seq = slot.sequence.load(std::memory_order_acquire);
    if (static_cast<std::ptrdiff_t>(seq) - static_cast<std::ptrdiff_t>(pos + 1) < 0)
        return false; // empty
    r = slot.record;
    slot.sequence.store(pos + mask_ + 1, std::memory_order_release);
    dequeue_.store(pos + 1, std::memory_order_relaxed);
    return true;
}

Logger::Logger(const std::string& path, std::size_t capacity)
    : ring_(capacity)
    , origin_(std::chrono::steady_clock::now())
{
    file_ = std::fopen(path.c_str(), "w");
    if (file_ != nullptr)
        std::fprintf(file_, "# SpatialScene host trace (phase-07c-1 condition 11): entry thread nonRealtime "
                            "transport block start_us duration_us argument\n");
    thread_ = std::thread([this] { drain(); });
}

Logger::~Logger()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    if (thread_.joinable())
        thread_.join();
    if (file_ != nullptr)
    {
        std::fprintf(file_, "# dropped %" PRIu64 "\n", ring_.dropped());
        std::fclose(file_);
    }
}

std::uint64_t Logger::nowNs() const noexcept
{
    return static_cast<std::uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - origin_)
            .count());
}

void Logger::drain()
{
    const auto flush = [this] {
        Record r;
        while (ring_.pop(r))
        {
            if (file_ != nullptr)
                std::fprintf(file_, "%s %" PRIu64 " %d %d %d %.1f %.1f %" PRId64 "\n", entryName(r.entry),
                             r.threadId, r.nonRealtime ? 1 : 0, static_cast<int>(r.transport),
                             static_cast<int>(r.blockSize), static_cast<double>(r.startNs) * 1e-3,
                             static_cast<double>(r.durationNs) * 1e-3, r.argument);
            written_.fetch_add(1, std::memory_order_relaxed);
        }
        if (file_ != nullptr)
            std::fflush(file_);
    };
    std::unique_lock<std::mutex> lock(mutex_);
    while (!stop_)
    {
        cv_.wait_for(lock, std::chrono::milliseconds(kDrainPeriodMs), [this] { return stop_; });
        lock.unlock();
        flush();
        lock.lock();
    }
    lock.unlock();
    flush();
}

Scope::Scope(Logger* logger, Entry entry, bool nonRealtime, Transport transport, std::int32_t blockSize,
             std::int64_t argument) noexcept
    : logger_(logger)
{
    if (logger_ == nullptr)
        return;
    record_.entry = entry;
    record_.nonRealtime = nonRealtime;
    record_.transport = transport;
    record_.blockSize = blockSize;
    record_.argument = argument;
    record_.threadId = nativeThreadId();
    record_.startNs = logger_->nowNs();
}

Scope::~Scope()
{
    if (logger_ == nullptr)
        return;
    record_.durationNs = logger_->nowNs() - record_.startNs;
    logger_->push(record_);
}

} // namespace plugin::trace
