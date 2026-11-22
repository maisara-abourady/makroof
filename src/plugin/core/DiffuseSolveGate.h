#pragma once

// The diffuse-solve gate (phase 05h, AX38 (i)): at most one diffuse solve runs at a time per process,
// through a sleeping wait (mutex + condition variable, no spin), with a three-class service order:
//   (1) synchronous host calls (prepare, restore; reset() and setNonRealtime() never build since
//       phase-07c-1 condition 10) are
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
//
// Phase-07c-2 scope 11 (D-W3 H-2c, Seat 5): the gate also owns the process-wide solve EXECUTOR, on which
// every realtime pipeline runs its builder-class diffuse solves as tasks (never a thread per instance), so
// the IR builder never waits for a solve. kExecutorThreads threads, started with the first task; a task is
// owned through shared_ptr by its pipeline and the executor queue, and its owner either orphans it before it
// starts (it then never runs) or waits for it to finish (Task::orphanOrWait), so a task never outlives the
// pipeline it reports to. While a builder-class solve holds the gate the pool takes shares on size() - 1
// threads (the builder works alongside it; D4: never a different result). JUCE-free.
#include "sim/diffuse/ThreadPool.h"

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace plugin {

namespace detail {
// > 0 while the calling thread is inside a real-time ScenePipeline::process() (debug builds only).
extern thread_local int realtimeProcessDepth;
// Set once a thread has run a real-time process() (debug builds only; D-H3 (e), AX38 (i) register entry): a
// Synchronous-class gate entry from such a thread (a host delivering reset() or the offline switch on its
// processing thread, which VST3 permits) is counted, never asserted, and printed by the tests. A thread-local
// store; nothing on the real-time path allocates, locks or logs.
extern thread_local bool ranRealtimeProcess;
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

    // ---- the solve executor (phase-07c-2 scope 11) ----
    static constexpr unsigned kExecutorThreads =
        2; // one solving, one unwinding a superseded solve or assembling
    // A unit of work on the executor. Its state is Queued until an executor thread starts it (Running, then
    // Done) or its owner orphans it (Orphaned: it never runs and its execute() never touches the owner).
    class Task
    {
    public:
        virtual ~Task() = default;
        // Called by the executor: runs execute() unless orphaned.
        void runOnExecutor() noexcept;
        // Owner: a task not started yet is orphaned (returns false); a running one is waited for (true).
        // After the return the task never touches its owner again.
        bool orphanOrWait();
        // True once execute() has returned (or the task was orphaned).
        bool done() const noexcept { return done_.load(std::memory_order_acquire); }

    protected:
        // Must not throw. Everything it does to its owner happens before it returns.
        virtual void execute() noexcept = 0;

    private:
        enum class State
        {
            Queued,
            Running,
            Done,
            Orphaned
        };
        std::mutex mutex_;
        std::condition_variable cv_;
        State state_ = State::Queued;
        std::atomic<bool> done_{false};
    };
    // Queues `task` on the executor (FIFO). Any non-audio thread.
    void post(std::shared_ptr<Task> task);
    // The pool's share count for a builder-class solve: size() - 1 (at least 1).
    unsigned builderShareThreads() const noexcept;

    // Blocks until this waiter may solve (the class order above). Returns false without entering when
    // `abandon` became true while waiting (builder class: the pipeline was quiesced); synchronous and
    // offline waiters never abandon. Pair every true return with leave().
    bool enter(Class cls, const std::atomic<bool>* abandon = nullptr);
    // D-H3 (e): Synchronous-class entries made from a thread that had run a real-time process() (debug builds
    // count; release builds return 0). A record for the AX38 (i) register, not a gate.
    std::uint64_t synchronousEntriesFromRealtimeThreads() const noexcept
    {
        return synchronousFromRealtime_.load(std::memory_order_relaxed);
    }
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
            : gate_(gate)
            , entered_(gate.enter(cls, abandon))
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

    void executorLoop();

    sim::diffuse::ThreadPool pool_;
    std::atomic<std::uint64_t> synchronousFromRealtime_{0};
    // The executor (its own mutex: never taken with mutex_ held, nor mutex_ with it).
    std::mutex execMutex_;
    std::condition_variable execCv_;
    std::deque<std::shared_ptr<Task>> tasks_;
    std::vector<std::thread> executors_;
    bool execStop_ = false;
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
