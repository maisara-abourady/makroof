#pragma once

// The diffuse-solve gate (phase 05h, AX38 (i)): at most one diffuse solve runs at a time per process,
// through a sleeping wait (mutex + condition variable, no spin), with a three-class service order:
//   (1) synchronous host calls (prepare, restore, setNonRealtime, and reset() through its step 3) are
//       served first, FIFO among themselves, waiting at most for the one solve already running;
//   (2) offline-render waiters and (3) builder-thread waiters take turns, one solve each, FIFO within
//       the class (a real-time instance's builder waits about two solves while another instance
//       renders offline, and an offline waiter about two solves).
// A builder waiting at the gate leaves the queue when its pipeline is quiesced (the predicate checks
// the abandon flag). The gate is never held while a pipeline holds stateMutex_ or the builder mutex:
// ScenePipeline enters it only inside the build step of decide(), outside both. It is never reachable
// from a real-time process(): a debug assert on the thread-local flag realtimeProcessDepth checks that.
// Gate order never changes any output (a solve is a pure function of its scene, AX39/AX40), so the
// classes only trade latency.
//
// The gate also owns the diffuse estimator's worker pool (AX39 "process-wide, owned with the AX38
// gate"). The process-wide gate is reference-counted: created with the first ScenePipeline, destroyed
// (its workers joined) with the last one, on the host thread that deletes that instance, never in a
// static destructor at library unload (a loader-lock deadlock on Windows, PR #27 review Q-1).
// JUCE-free.
#include "sim/diffuse/ThreadPool.h"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>

namespace plugin {

namespace detail {
// > 0 while the calling thread is inside a real-time ScenePipeline::process() (debug builds only).
extern thread_local int realtimeProcessDepth;
} // namespace detail

class DiffuseSolveGate
{
public:
    enum class Class
    {
        Synchronous,
        Offline,
        Builder
    };

    // threads = total pool threads including the caller (>= 1).
    explicit DiffuseSolveGate(unsigned threads);
    ~DiffuseSolveGate();
    DiffuseSolveGate(const DiffuseSolveGate&) = delete;
    DiffuseSolveGate& operator=(const DiffuseSolveGate&) = delete;

    // The process-wide gate (hardware_concurrency() threads): one instance shared by every pipeline
    // alive, destroyed with the last holder.
    static std::shared_ptr<DiffuseSolveGate> shared();

    sim::diffuse::ThreadPool& pool() noexcept { return pool_; }

    // Blocks until this waiter may solve (the class order above). Returns false without entering when
    // `abandon` became true while waiting (builder class: the pipeline was quiesced); synchronous and
    // offline waiters never abandon. Pair every true return with leave().
    bool enter(Class cls, const std::atomic<bool>* abandon = nullptr);
    void leave();
    // Wakes the waiters so that one whose abandon flag is set can leave the queue.
    void notifyWaiters();

    // Inspection (tests).
    bool held() const;
    std::size_t waiting(Class cls) const;
    std::uint64_t solvesCompleted() const;

    // RAII entry: entered() tells whether the gate was taken (false = abandoned).
    class Scope
    {
    public:
        Scope(DiffuseSolveGate& gate, Class cls, const std::atomic<bool>* abandon = nullptr)
            : gate_(gate), entered_(gate.enter(cls, abandon))
        {}
        ~Scope()
        {
            if (entered_)
                gate_.leave();
        }
        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;
        bool entered() const noexcept { return entered_; }

    private:
        DiffuseSolveGate& gate_;
        bool entered_;
    };

private:
    struct Waiter
    {
        Class cls;
        std::uint64_t ticket;
    };
    // The waiter served next, or nullptr. Called with mutex_ held.
    const Waiter* next() const noexcept;
    void remove(std::uint64_t ticket);

    sim::diffuse::ThreadPool pool_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool held_ = false;
    std::uint64_t nextTicket_ = 1;
    std::uint64_t completed_ = 0;
    Class lastTurn_ = Class::Builder; // of the offline / builder alternation
    std::deque<Waiter> synchronous_;
    std::deque<Waiter> offline_;
    std::deque<Waiter> builder_;
};

} // namespace plugin
