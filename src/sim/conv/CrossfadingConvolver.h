#pragma once

// Two UPOLS convolver states, A (current) and B (next), over ONE shared input history (FDL), with a
// click-free IR swap (AQ4, AX18). Phase 06; Phase 10 builds movement on it.
//
// Threads:
//   - requestIr() and releaseRetired(): any non-audio thread (thread-safe among themselves);
//   - process(): the audio thread only. Never allocates, locks, frees or throws.
//
// Handover (lock-free single-slot mailbox, "latest wins"): requestIr() heap-allocates a request
// (the shared_ptr and the crossfade law) and atomically exchanges it into the mailbox; a request
// that was still there (never seen by the audio thread) comes back from the exchange and is freed by
// the requester. The audio thread takes the mailbox (exchange with nullptr) only when it can start a
// fade, so a request that arrives during a fade waits there, and only the newest one survives.
//
// Work spreading (worst-case callback): the output of block b + 1 is Y = sum_k X(b + 1 - k) H_k. Only
// the k = 0 term needs the block's own input; the k >= 1 terms use spectra that are already in the
// FDL. So while process() takes in the samples of block b + 1, it accumulates the k >= 1 products in
// steps proportional to the samples taken in (a fraction position / P of the M * N * (K - 1)
// complex multiply-adds per state), and the partition boundary does only the remainder, the N
// forward FFTs, the k = 0 products and the M inverse FFTs. A small host buffer then sees about 1/(P/n)
// of the block's work per callback instead of all of it in one. The result is the same convolution
// (only the summation order differs from PartitionedConvolver).
//
// Timing: the mailbox is read at a PARTITION boundary, i.e. when process() has taken in the P input
// samples of block b and computes that block's output. A request taken there first spends one block
// accumulating (see above) and enters the output with the NEXT block: with output samples counted
// from 0 since prepare() (or reset()), a request made after r input samples is taken at the boundary
// of block floor(r / P) and its fade starts at output sample s0 = (floor(r / P) + 2) P;
// fadeStartSample() reports s0. For s0 <= s < s0 + L, g = (s - s0) / L, g = 1 from s0 + L on:
//   EqualGain:  out = (1 - g) y_A + g y_B        (position updates: correlated IRs)
//   EqualPower: out = cos(g pi/2) y_A + sin(g pi/2) y_B   (unrelated IRs: mode switch, large jumps)
// where y_A, y_B are the exact convolutions x * A and x * B (both states read the full history), so
// with the latency P: out(t) = (1 - g(t)) (x*A)(t - P) + g(t) (x*B)(t - P) for equal gain.
// After the fade, B becomes the current state and A's request is retired. An IR taken at the first
// partition boundary after prepare() / reset() is installed at once and rendered in full there (the
// output so far is the latency's silence, and an offline render then starts exact); one taken later
// with no current IR fades in from silence (y_A = 0) like any other change, so a late first IR never
// starts with a step.
//
// Input guard: non-finite input samples (NaN, +-Inf) are replaced by 0 as they are taken in, so a
// bad host sample cannot poison the FDL (and with it the output for a whole IR length).
//
// Memory reclamation: the audio thread never frees. A retired request goes into a fixed-size
// lock-free single-producer (audio) / single-consumer queue; releaseRetired() pops and frees them
// (the consumer side is serialised by a mutex, which only non-audio threads take). If the queue is
// full, the audio thread holds the retired request and starts no new fade until it fits, so nothing
// is ever dropped or freed on the audio thread.
#include "sim/conv/PartitionedConvolver.h"

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

namespace sim::conv {

// AX18: equal-gain for correlated IRs (position updates), equal-power for unrelated ones.
enum class CrossfadeLaw
{
    EqualGain,
    EqualPower
};

class CrossfadingConvolver
{
public:
    CrossfadingConvolver() = default;
    ~CrossfadingConvolver();
    CrossfadingConvolver(const CrossfadingConvolver&) = delete;
    CrossfadingConvolver& operator=(const CrossfadingConvolver&) = delete;

    // Not real-time, not concurrent with anything else. Allocates everything. fadeLengthSamples
    // L >= 1 (AQ4: 30 ms, see RealtimeEngine). Drops any IR and request held before.
    void prepare(int numInputs, int numOutputs, int maxBlock, int partitionSize, std::size_t maxPartitions,
                 int fadeLengthSamples);

    // Any non-audio thread. Returns false (and changes nothing) if `ir` is null or doesn't fit
    // prepare() (shape, partition size, more than maxPartitions partitions).
    bool requestIr(std::shared_ptr<const IrSet> ir, CrossfadeLaw law = CrossfadeLaw::EqualGain);

    // Any non-audio thread: frees the requests the audio thread has retired. Returns how many.
    std::size_t releaseRetired();

    // Audio thread. n in 1 .. maxBlock. in and out may be the same buffers when N == M. Before a
    // successful prepare() it does nothing (out is left untouched).
    void process(const float* const* in, float* const* out, int n) noexcept;
    // 1 x 1 convenience.
    void process(const float* in, float* out, int n) noexcept;

    // Clears the input history, the pending output and the sample counter; keeps the current IR,
    // ends a running fade on its target. Not concurrent with process().
    void reset() noexcept;

    int latencySamples() const noexcept { return partitionSize_; }
    int partitionSize() const noexcept { return partitionSize_; }
    int fadeLengthSamples() const noexcept { return fadeLength_; }
    std::size_t maxPartitions() const noexcept { return fdl_.capacity(); }

    // Inspection for tests and diagnostics. Read them from the audio thread, or while process() is
    // not running.
    const IrSet* currentIr() const noexcept;
    // True from the boundary where a request is taken until its fade has ended.
    bool isFading() const noexcept { return next_ != nullptr; }
    // Output sample at which the latest fade started (see Timing), or -1 if none has.
    std::int64_t fadeStartSample() const noexcept { return fadeStart_; }
    // Number of fades started since prepare().
    std::uint64_t fadeCount() const noexcept { return fades_; }
    // 2P-bin complex multiply-adds done by the latest process() call (work-spreading tests).
    std::uint64_t lastProcessMultiplyAdds() const noexcept { return macs_; }

    // Capacity of the deferred-release queue.
    static constexpr std::size_t kReleaseQueueSize = 64;

private:
    struct Request
    {
        std::shared_ptr<const IrSet> ir;
        CrossfadeLaw law = CrossfadeLaw::EqualGain;
    };

    // One state's k >= 1 accumulation for the block being taken in (see "Work spreading").
    struct Lane
    {
        AlignedFloats acc;     // M x 2P spectra
        std::size_t done = 0;  // multiply-adds done this block
        std::size_t total = 0; // M * N * (K - 1)
    };

    void computeBlock() noexcept;
    void startLane(Lane& lane, const Request* r) noexcept;
    void advanceLane(Lane& lane, const IrSet& ir, std::size_t target) noexcept;
    void finishLane(Lane& lane, const IrSet& ir, float* const* y) noexcept;
    void advanceLanes() noexcept;
    void restartLanes() noexcept;
    bool pushRetired(Request* r) noexcept;
    void clearAll() noexcept;

    int numInputs_ = 0;
    int numOutputs_ = 0;
    int maxBlock_ = 0;
    int partitionSize_ = 0;
    int fadeLength_ = 1;
    int position_ = 0;

    // Audio-thread state.
    Request* current_ = nullptr;
    Request* next_ = nullptr;
    Request* retiring_ = nullptr; // retired but not yet in the queue (queue was full)
    std::int64_t blockStart_ = 0; // output sample index of outBlock_[0]
    std::int64_t fadeStart_ = -1;
    std::uint64_t fades_ = 0;
    std::uint64_t macs_ = 0; // multiply-adds in the current / latest process() call

    std::atomic<Request*> mailbox_{nullptr};
    static_assert(std::atomic<Request*>::is_always_lock_free, "the IR mailbox must be lock-free");
    static_assert(std::atomic<std::size_t>::is_always_lock_free, "the release queue must be lock-free");

    // SPSC queue: audio thread pushes (writeIndex_), releaseRetired() pops (readIndex_).
    std::array<Request*, kReleaseQueueSize> releaseQueue_{};
    std::atomic<std::size_t> writeIndex_{0};
    std::atomic<std::size_t> readIndex_{0};
    std::mutex consumerMutex_;

    Fft fft_{32};
    FrequencyDelayLine fdl_;
    AlignedFloats inBlock_;  // N x P
    AlignedFloats outBlock_; // M x P, being played out
    AlignedFloats yA_;       // M x P
    AlignedFloats yB_;       // M x P
    AlignedFloats timeScratch_;
    Lane laneA_; // serves current_
    Lane laneB_; // serves next_
    // Gain ramps for both laws, index j = s - s0 in 0 .. L (j = L: 1 / 0).
    std::vector<float> rampIn_[2];
    std::vector<float> rampOut_[2];
    std::vector<float*> inPtrs_;
    std::vector<float*> outPtrs_;
    std::vector<float*> yAPtrs_;
    std::vector<float*> yBPtrs_;
};

} // namespace sim::conv
