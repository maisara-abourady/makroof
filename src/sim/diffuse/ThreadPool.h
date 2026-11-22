#pragma once

// The diffuse estimator's worker pool (AX39: process-wide, owned with the AX38 gate). A blocking
// parallel-for over block indices; which thread runs a block never changes a result (D4: blocks are
// reduced in index order by the caller). One caller at a time: the AX38 gate holder (the host, offline or
// builder thread, or since phase-07c-2 scope 11 the gate executor running a builder-class solve task).
#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace sim::diffuse {

// Convention (AX37 (5.1) (i), D-H3 (c)): every share that runs on this pool, on a worker or on the caller,
// runs under ScopedFlushDenormals (FTZ/DAZ), so a build never depends on the FP mode a thread inherited; a
// later pool job is written for that.
class ThreadPool
{
public:
    // threads = total threads including the caller (>= 1).
    explicit ThreadPool(unsigned threads);
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    unsigned size() const noexcept { return static_cast<unsigned>(workers_.size()) + 1; }

    // Phase-07c-2 scope 11 (D-W3 H-2c, Seat 5): the number of threads (the caller included, 1..size()) that
    // take shares in the following parallelFor() calls; 0 or >= size() = all. The plugin's gate sets size() -
    // 1 for a solve that runs beside the IR builder. Which thread runs a block never changes a result (D4),
    // so the limit only trades speed. Set it only between parallelFor() calls (the plugin does under the AX38
    // gate).
    void setShareLimit(unsigned threads) noexcept;
    // The threads that take shares: min(limit, size()), at least 1.
    unsigned shareThreads() const noexcept;

    // Runs fn(i) for i in [0, count) on the pool and the calling thread; returns when all have run.
    // A false return from fn stops the remaining indices from being started.
    // fn must not throw (the estimator's blocks do not allocate or throw): an exception would leave
    // the workers holding a pointer to fn.
    void parallelFor(std::int64_t count, const std::function<bool(std::int64_t)>& fn);

    // The process-wide pool (std::thread::hardware_concurrency() threads, at least 1). Ownership,
    // sizing and shutdown inside the plugin (AX39: owned with the AX38 gate; no join in a static
    // destructor at library unload) are phase-05h session 2's.
    static ThreadPool& process();

private:
    void workerLoop(unsigned id);
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
    std::atomic<unsigned> limit_{0}; // setShareLimit(); 0 = all
    unsigned participants_ = 1;      // of the running parallelFor (under mutex_): workers 1..participants_-1
};

} // namespace sim::diffuse
