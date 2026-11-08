#include "plugin/core/IrBuilderThread.h"

#include <chrono>
#include <utility>

namespace plugin {

double SteadyBuilderClock::now()
{
    using namespace std::chrono;
    return duration<double>(steady_clock::now().time_since_epoch()).count();
}

void SteadyBuilderClock::waitUntil(std::unique_lock<std::mutex>& lock, std::condition_variable& cv,
                                   double deadline, const std::function<bool()>& stop)
{
    using namespace std::chrono;
    const auto until = steady_clock::time_point(
        duration_cast<steady_clock::duration>(duration<double>(deadline)));
    cv.wait_until(lock, until, stop);
}

IrBuilderThread::IrBuilderThread(BuilderClock& clock, std::function<bool()> hasWork,
                                 std::function<void()> decide)
    : clock_(clock)
    , hasWork_(std::move(hasWork))
    , decide_(std::move(decide))
{
    thread_ = std::thread([this] { run(); });
}

IrBuilderThread::~IrBuilderThread()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
        accepting_ = false;
    }
    cv_.notify_all();
    if (thread_.joinable())
        thread_.join();
}

void IrBuilderThread::quiesce()
{
    std::unique_lock<std::mutex> lock(mutex_);
    accepting_ = false;
    cv_.notify_all();
    cv_.wait(lock, [this] { return !busy_; });
}

void IrBuilderThread::restart()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        accepting_ = true;
    }
    cv_.notify_all();
}

void IrBuilderThread::notify()
{
    cv_.notify_all();
}

bool IrBuilderThread::accepting() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return accepting_;
}

bool IrBuilderThread::busy() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return busy_;
}

bool IrBuilderThread::idleOrWaiting() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return waiting_ && !busy_;
}

void IrBuilderThread::run()
{
    std::unique_lock<std::mutex> lock(mutex_);
    const auto interrupted = [this] { return stop_ || !accepting_; };
    while (!stop_)
    {
        if (!accepting_ || !hasWork_())
        {
            waiting_ = true;
            const std::function<bool()> wake = [this] { return stop_ || (accepting_ && hasWork_()); };
            clock_.waitUntil(lock, cv_, clock_.now() + kIdlePollS, wake);
            continue;
        }
        // AX33: a minimum spacing between build starts.
        if (lastStart_)
        {
            const double slot = *lastStart_ + kMinBuildSpacingS;
            if (clock_.now() < slot)
            {
                waiting_ = true;
                clock_.waitUntil(lock, cv_, slot, interrupted);
                continue; // re-check stop, acceptance, work and the slot
            }
        }
        waiting_ = false;
        busy_ = true;
        lastStart_ = clock_.now();
        lock.unlock();
        decide_();
        lock.lock();
        busy_ = false;
        cv_.notify_all(); // quiesce() waits for this
    }
}

} // namespace plugin
