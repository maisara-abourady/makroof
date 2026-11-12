#pragma once

// The real-time façade the plugin calls from Phase 07: a 2-in x 2-out CrossfadingConvolver with the
// AQ4 swap and the reported latency. Phase 06.
//
//   prepare(sampleRate, maxBlock)   non-real-time; allocates for the longest room IR
//   process(in[2], out[2], n)       audio thread; n in 1 .. maxBlock; no allocation, locks or I/O
//   latencySamples()                P + kAlignPreRollSamples (AX1: the IR puts the earliest direct
//                                   arrival at sample kAlignPreRollSamples, so a host that
//                                   compensates this latency hears the direct sound on the grid)
//   submitRoomIR(RoomIR)            any non-audio thread, or the processing thread when nothing else
//                                   submits (offline bounce, reset sequence with the builder quiesced:
//                                   Phase 07); builds the IrSet there and hands it over
//   reset()                         non-real-time; back to the state right after prepare() (Phase 07)
//   resetKeepIr()                   non-real-time; clears history and pending output, keeps the IR
//                                   (the plugin's realtime reset, phase-07c-1 condition 10)
//
// Until the first IR arrives the output is silence. An IR submitted before processing starts is
// installed at once; every later change, including a first IR that arrives mid-stream, crossfades
// over 30 ms (AQ4) with the requested law (AX18). Retired IRs are freed by the next
// submit*() or by releaseRetired(), always on the calling (non-audio) thread.
#include "sim/Engine.h"
#include "sim/conv/CrossfadingConvolver.h"

#include <cstddef>
#include <memory>

namespace sim {

class RealtimeEngine
{
public:
    static constexpr int kNumChannels = 2; // v1: 2 emitters x 2 outputs (AX7)
    // AQ4: an IR change is a 30 ms crossfade between two convolver states.
    static constexpr double kCrossfadeS = 0.030;

    // partitionSize P in {128, 256, 512} (default 512, AQ10). Throws std::invalid_argument otherwise.
    explicit RealtimeEngine(int partitionSize = conv::kDefaultPartitionSize);

    // Non-real-time. sampleRate must be one of kSupportedSampleRatesHz (AX6). The input history holds
    // maxIrLengthSamples(sampleRate) samples: the longest IR buildRoomIR can produce. Drops any IR.
    // Throws std::invalid_argument for an unsupported rate or maxBlock < 1; after a throw the engine
    // is unprepared (process() writes silence) until a prepare() succeeds.
    void prepare(double sampleRate, int maxBlock);

    // Non-real-time, not concurrent with process() or a submit (Phase 07 reset sequence, step 2). A
    // no-op when unprepared. Otherwise it returns the engine to the state right after prepare() at the
    // same sample rate and block size: no current, next or retiring IR and an empty mailbox (the
    // dropped IRs are freed on the calling thread); input history, pending output and sample counter
    // cleared; buffers reused, not reallocated. (fadeCount() keeps counting since prepare().)
    void reset() noexcept;
    // Phase-07c-1 condition 10 (D-H3 (e), Seat 3's (e-k)): the realtime reset. Not concurrent with
    // process(); MAY run concurrently with a submit from another thread (it never touches the mailbox
    // or frees a retired request a submitter could be freeing). A no-op when unprepared. Clears the
    // input history, the pending output and the sample counter, but KEEPS the current IrSet (a running
    // fade ends on its target, which becomes current), so the output is never silent after a reset and
    // the next submit arrives as an ordinary AQ4 / AX31 crossfade.
    void resetKeepIr() noexcept;
    bool isPrepared() const noexcept { return sampleRate_ > 0.0; }

    // Audio thread. in[c] / out[c] hold n samples, c = 0, 1; in and out may be the same buffers.
    // Before a successful prepare() it writes silence.
    void process(const float* const in[2], float* const out[2], int n) noexcept;

    int latencySamples() const noexcept { return partitionSize_ + kAlignPreRollSamples; }
    int partitionSize() const noexcept { return partitionSize_; }
    double sampleRate() const noexcept { return sampleRate_; }
    // round(kCrossfadeS * sampleRate) samples.
    int crossfadeSamples() const noexcept { return convolver_.fadeLengthSamples(); }

    // The capacity in samples at `sampleRate`: tail::kMaxIrLengthS (12 s, the IR builder's cap)
    // plus the AX1 pre-roll, which the alignment can add in front of a capped tail.
    static std::size_t maxIrLengthSamples(double sampleRate) noexcept;

    // Any non-audio thread, or the processing thread when nothing else submits (offline bounce, reset
    // sequence with the builder quiesced: Phase 07). Builds the IrSet of `ir` and requests it. Returns false
    // (nothing changes) if the IR is not 2 x 2, has another sample rate than prepare(), is longer than
    // maxIrLengthSamples(), or has a non-finite tap (phase 06b). Frees retired IRs first.
    bool submitRoomIR(const RoomIR& ir, conv::CrossfadeLaw law = conv::CrossfadeLaw::EqualGain);
    // The same with a prebuilt IrSet (makeIrSet()), e.g. to switch between cached IRs. Same threads.
    bool submitIrSet(std::shared_ptr<const conv::IrSet> irSet,
                     conv::CrossfadeLaw law = conv::CrossfadeLaw::EqualGain);
    // Non-audio thread. nullptr when the IR doesn't fit or has a non-finite tap (as submitRoomIR).
    // `cancel` (phase-07c-1 condition 10): throws sim::BuildCancelled when set during the build.
    std::shared_ptr<const conv::IrSet> makeIrSet(const RoomIR& ir,
                                                 const std::atomic<bool>* cancel = nullptr) const;

    // Non-audio thread: frees IRs the audio thread has retired; returns how many.
    std::size_t releaseRetired() { return convolver_.releaseRetired(); }

    // For tests and diagnostics (audio thread, or while process() is not running).
    const conv::CrossfadingConvolver& convolver() const noexcept { return convolver_; }

private:
    int partitionSize_;
    double sampleRate_ = 0.0;
    conv::CrossfadingConvolver convolver_;
};

} // namespace sim
