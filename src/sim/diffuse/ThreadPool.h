#pragma once

// The diffuse estimator's worker pool (AX39: process-wide, owned with the AX38 gate). A blocking
// parallel-for over block indices; which thread runs a block never changes a result (D4: blocks are
// reduced in index order by the caller). Builder thread only.
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace sim::diffuse {

class ThreadPool
{
public:
    // threads = total threads including the caller (>= 1).
    explicit ThreadPool(unsigned threads);
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    unsigned size() const noexcept { return static_cast<unsigned>(workers_.size()) + 1; }

    // Runs fn(i) for i in [0, count) on the pool and the calling thread; returns when all have run.
    // A false return from fn stops the remaining indices from being started.
    void parallelFor(std::int64_t count, const std::function<bool(std::int64_t)>& fn);

    // The process-wide pool (std::thread::hardware_concurrency() threads, at least 1).
    static ThreadPool& process();

private:
    void workerLoop();
    void runShare();

    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::condition_variable wake_;
    std::condition_variable done_;
    std::mutex runMutex_; // one parallelFor at a time
    const std::function<bool(std::int64_t)>* job_ = nullptr;
    std::int64_t count_ = 0;
    std::int64_t next_ = 0;
    bool stopFlag_ = false;
    bool halt_ = false;
    unsigned active_ = 0;
    std::uint64_t epoch_ = 0;
};

} // namespace sim::diffuse
