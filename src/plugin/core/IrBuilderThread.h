#pragma once

// The background IR builder of the plugin (Phase 07 scope 3). JUCE-free.
//
// One std::thread that runs `decide` (build the scene's IR and submit it, or skip it) whenever `hasWork`
// says the dirty generation differs from the last handled one. It never blocks the audio thread: the
// parameter listener only increments an atomic counter, and the builder notices it by polling while it
// is idle (kIdlePollS); non-audio callers can wake it at once with notify().
//
// AX33 (the AQ4 20 ms cap): a minimum spacing of kMinBuildSpacingS between the STARTS of successive
// builds. A request with no build running and none started in the last 20 ms starts at once (within the
// idle poll); requests during a build or within 20 ms of the last start are coalesced into one build
// starting at max(last start + 20 ms, end of the running build). Because `decide` reads the generation
// before its scene snapshot and `hasWork` compares it with the newest one after every build, the final
// state is always built (no lost wake-up, FR-3D-10).
//
// quiesce() stops accepting work and waits for an in-flight `decide` to return; the owner discards its
// result (ScenePipeline checks accepting() under its own lock before submitting). restart() accepts work
// again. The thread runs from construction to destruction.
#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <thread>

namespace plugin {

// Time source of the builder, injectable for the AX33 test.
class BuilderClock
{
public:
    virtual ~BuilderClock() = default;
    // Seconds on a monotonic clock.
    virtual double now() = 0;
    // Waits on `cv` (with `lock` held on entry and exit) until `stop()` is true or now() >= deadline.
    virtual void waitUntil(std::unique_lock<std::mutex>& lock, std::condition_variable& cv, double deadline,
                           const std::function<bool()>& stop) = 0;
};

// std::chrono::steady_clock.
class SteadyBuilderClock final : public BuilderClock
{
public:
    double now() override;
    void waitUntil(std::unique_lock<std::mutex>& lock, std::condition_variable& cv, double deadline,
                   const std::function<bool()>& stop) override;
};

class IrBuilderThread
{
public:
    static constexpr double kMinBuildSpacingS = 0.020; // AQ4 / AX33
    // How often an idle builder looks at the dirty counter (the audio-thread listener doesn't notify,
    // so it never takes a lock or makes a system call). Well below one partition (10.7 ms at P = 512).
    static constexpr double kIdlePollS = 0.001;

    // `hasWork` and `decide` are called on the builder thread; `hasWork` also under the builder's lock,
    // so it must be cheap and must not call back into this object.
    IrBuilderThread(BuilderClock& clock, std::function<bool()> hasWork, std::function<void()> decide);
    ~IrBuilderThread();
    IrBuilderThread(const IrBuilderThread&) = delete;
    IrBuilderThread& operator=(const IrBuilderThread&) = delete;

    // Non-audio thread. Stops accepting work and waits until no `decide` is running.
    void quiesce();
    // Any thread (phase-07c-1 condition 10): stops accepting work WITHOUT waiting; a running `decide`
    // finishes (or is cancelled by its owner) and no new one starts until restart().
    void stopAccepting();
    // Non-audio thread. Accepts work again.
    void restart();
    // Non-audio thread. Wakes the builder (it would notice the work within kIdlePollS anyway).
    void notify();

    // True while work is accepted. Read it under the owner's lock that quiesce() callers also take.
    bool accepting() const;
    // True while `decide` runs (for tests).
    bool busy() const;
    // True while the builder has nothing to do or waits for its AX33 slot (for tests).
    bool idleOrWaiting() const;

private:
    void run();

    BuilderClock& clock_;
    std::function<bool()> hasWork_;
    std::function<void()> decide_;

    mutable std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
    bool accepting_ = false;
    bool busy_ = false;
    bool waiting_ = true;
    std::optional<double> lastStart_;
    std::thread thread_;
};

} // namespace plugin
