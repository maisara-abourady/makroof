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

std::uint64_t DiffuseSolveGate::solvesCompleted() const
{
    std::lock_guard lock(mutex_);
    return completed_;
}

} // namespace plugin
