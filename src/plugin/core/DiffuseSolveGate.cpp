#include "plugin/core/DiffuseSolveGate.h"

#include <algorithm>
#include <cassert>
#include <thread>

namespace plugin {

namespace detail {
thread_local int realtimeProcessDepth = 0;
thread_local bool ranRealtimeProcess = false;
} // namespace detail

DiffuseSolveGate::DiffuseSolveGate(unsigned threads)
    : pool_(std::max(1u, threads))
{}

DiffuseSolveGate::~DiffuseSolveGate()
{
    // Every task still queued was orphaned by its pipeline (each pipeline orphans or waits for its tasks
    // before it lets go of the gate): the executor drops them unrun.
    {
        std::lock_guard lock(execMutex_);
        execStop_ = true;
    }
    execCv_.notify_all();
    for (auto& t : executors_)
        t.join();
    tasks_.clear();
    // No solve can be running (every holder's pipeline is gone) and no waiter can be queued: the pool
    // joins its workers here, on the thread that released the last holder.
    assert(!held_ && synchronous_.empty() && offline_.empty() && builder_.empty());
}

std::shared_ptr<DiffuseSolveGate> DiffuseSolveGate::shared()
{
    // Only a weak reference lives in static storage: the gate and its threads die with the last
    // pipeline, never at library unload.
    static std::mutex mutex;
    static std::weak_ptr<DiffuseSolveGate> weak;
    std::lock_guard lock(mutex);
    if (auto existing = weak.lock())
        return existing;
    auto fresh = std::make_shared<DiffuseSolveGate>(std::max(1u, std::thread::hardware_concurrency()));
    weak = fresh;
    return fresh;
}

const DiffuseSolveGate::Waiter* DiffuseSolveGate::next() const noexcept
{
    if (!synchronous_.empty())
        return &synchronous_.front();
    const bool o = !offline_.empty();
    const bool b = !builder_.empty();
    if (o && b)
        return lastTurn_ == Class::Offline ? &builder_.front() : &offline_.front();
    if (o)
        return &offline_.front();
    if (b)
        return &builder_.front();
    return nullptr;
}

void DiffuseSolveGate::remove(std::uint64_t ticket)
{
    for (auto* q : {&synchronous_, &offline_, &builder_})
    {
        const auto it = std::find_if(q->begin(), q->end(),
                                     [&](const Waiter& w) { return w.ticket == ticket; });
        if (it != q->end())
        {
            q->erase(it);
            return;
        }
    }
}

bool DiffuseSolveGate::enter(Class cls, const std::atomic<bool>* abandon)
{
    assert(detail::realtimeProcessDepth == 0
           && "the diffuse-solve gate is unreachable from a real-time process()");
#ifndef NDEBUG
    if (cls == Class::Synchronous && detail::ranRealtimeProcess)
        synchronousFromRealtime_.fetch_add(1, std::memory_order_relaxed);
#endif
    std::unique_lock lock(mutex_);
    const std::uint64_t ticket = nextTicket_++;
    auto& queue = cls == Class::Synchronous ? synchronous_ : (cls == Class::Offline ? offline_ : builder_);
    queue.push_back({cls, ticket});
    const auto abandoned = [&] { return abandon != nullptr && abandon->load(std::memory_order_acquire); };
    cv_.wait(lock, [&] {
        if (abandoned())
            return true;
        const Waiter* w = next();
        return !held_ && w != nullptr && w->ticket == ticket;
    });
    if (abandoned())
    {
        remove(ticket);
        lock.unlock();
        cv_.notify_all(); // the order may have changed for the others
        return false;
    }
    queue.pop_front();
    held_ = true;
    // Phase-07c-2 scope 11 (Seat 5): a builder-class solve runs beside the IR builder on size() - 1 threads.
    pool_.setShareLimit(cls == Class::Builder ? builderShareThreads() : 0);
    if (cls != Class::Synchronous)
        lastTurn_ = cls;
    return true;
}

void DiffuseSolveGate::leave()
{
    {
        std::lock_guard lock(mutex_);
        assert(held_);
        held_ = false;
        ++completed_;
    }
    cv_.notify_all();
}

void DiffuseSolveGate::notifyWaiters()
{
    cv_.notify_all();
}

bool DiffuseSolveGate::held() const
{
    std::lock_guard lock(mutex_);
    return held_;
}

std::size_t DiffuseSolveGate::waiting(Class cls) const
{
    std::lock_guard lock(mutex_);
    return (cls == Class::Synchronous ? synchronous_ : (cls == Class::Offline ? offline_ : builder_)).size();
}

unsigned DiffuseSolveGate::builderShareThreads() const noexcept
{
    return std::max(1u, pool_.size() - 1);
}

void DiffuseSolveGate::post(std::shared_ptr<Task> task)
{
    {
        std::lock_guard lock(execMutex_);
        if (executors_.empty())
            for (unsigned i = 0; i < kExecutorThreads; ++i)
                executors_.emplace_back([this] { executorLoop(); });
        tasks_.push_back(std::move(task));
    }
    execCv_.notify_one();
}

void DiffuseSolveGate::executorLoop()
{
    for (;;)
    {
        std::shared_ptr<Task> task;
        {
            std::unique_lock lock(execMutex_);
            execCv_.wait(lock, [this] { return execStop_ || !tasks_.empty(); });
            if (execStop_)
                return;
            task = std::move(tasks_.front());
            tasks_.pop_front();
        }
        task->runOnExecutor();
        task.reset(); // outside execMutex_ (a task's results are released here when its owner dropped them)
    }
}

void DiffuseSolveGate::Task::runOnExecutor() noexcept
{
    {
        std::lock_guard lock(mutex_);
        if (state_ == State::Orphaned)
            return;
        state_ = State::Running;
    }
    execute();
    {
        std::lock_guard lock(mutex_);
        state_ = State::Done;
        done_.store(true, std::memory_order_release);
    }
    cv_.notify_all();
}

bool DiffuseSolveGate::Task::orphanOrWait()
{
    std::unique_lock lock(mutex_);
    if (state_ == State::Queued)
    {
        state_ = State::Orphaned;
        done_.store(true, std::memory_order_release);
        return false;
    }
    cv_.wait(lock, [this] { return state_ == State::Done || state_ == State::Orphaned; });
    return true;
}

std::uint64_t DiffuseSolveGate::solvesCompleted() const
{
    std::lock_guard lock(mutex_);
    return completed_;
}

} // namespace plugin
