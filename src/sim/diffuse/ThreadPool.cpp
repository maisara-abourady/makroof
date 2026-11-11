#include "sim/diffuse/ThreadPool.h"

#include "sim/conv/Denormals.h"

#include <algorithm>

namespace sim::diffuse {

ThreadPool::ThreadPool(unsigned threads)
{
    const unsigned n = std::max(1u, threads);
    workers_.reserve(n - 1);
    for (unsigned i = 0; i + 1 < n; ++i)
        workers_.emplace_back([this] { workerLoop(); });
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard lock(mutex_);
        halt_ = true;
    }
    wake_.notify_all();
    for (auto& t : workers_)
        t.join();
}

ThreadPool& ThreadPool::process()
{
    static ThreadPool pool(std::max(1u, std::thread::hardware_concurrency()));
    return pool;
}

void ThreadPool::runShare()
{
    // AX37 (5.1) (i), D-H3 (c): the build's FTZ/DAZ guard covers only the thread that constructs it, so every
    // share (worker or caller) runs under its own guard; the IR then never depends on any thread's inherited
    // FP mode.
    const sim::conv::ScopedFlushDenormals flushDenormals;
    for (;;)
    {
        std::int64_t i = 0;
        const std::function<bool(std::int64_t)>* job = nullptr;
        {
            std::lock_guard lock(mutex_);
            if (stopFlag_ || next_ >= count_)
                return;
            i = next_++;
            job = job_;
        }
        if (!(*job)(i))
        {
            std::lock_guard lock(mutex_);
            stopFlag_ = true;
        }
    }
}

void ThreadPool::workerLoop()
{
    std::uint64_t seen = 0;
    for (;;)
    {
        {
            std::unique_lock lock(mutex_);
            wake_.wait(lock, [&] { return halt_ || epoch_ != seen; });
            if (halt_)
                return;
            seen = epoch_;
            ++active_;
        }
        runShare();
        {
            std::lock_guard lock(mutex_);
            --active_;
        }
        done_.notify_all();
    }
}

void ThreadPool::parallelFor(std::int64_t count, const std::function<bool(std::int64_t)>& fn)
{
    if (count <= 0)
        return;
    std::lock_guard run(runMutex_);
    {
        std::lock_guard lock(mutex_);
        job_ = &fn;
        count_ = count;
        next_ = 0;
        stopFlag_ = false;
        ++epoch_;
    }
    wake_.notify_all();
    runShare();
    std::unique_lock lock(mutex_);
    // Every index has been handed out (or stopping); wait for the ones still running.
    done_.wait(lock, [&] { return active_ == 0 && (stopFlag_ || next_ >= count_); });
    job_ = nullptr;
    count_ = 0;
}

} // namespace sim::diffuse
