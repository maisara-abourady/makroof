#pragma once

// The real-time façade the plugin calls from Phase 07: a 2-in x 2-out CrossfadingConvolver with the
// AQ4 swap and the reported latency. Phase 06.
//
//   prepare(sampleRate, maxBlock)   non-real-time; allocates for the longest room IR
//   process(in[2], out[2], n)       audio thread; n in 1 .. maxBlock; no allocation, locks or I/O
//   latencySamples()                P + kAlignPreRollSamples (AX1: the IR puts the earliest direct
//                                   arrival at sample kAlignPreRollSamples, so a host that
//                                   compensates this latency hears the direct sound on the grid)
//   submitRoomIR(RoomIR)            any non-audio thread; builds the IrSet there and hands it over
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

    // Non-audio thread. Builds the IrSet of `ir` and requests it. Returns false (nothing changes) if
    // the IR is not 2 x 2, has another sample rate than prepare(), is longer than
    // maxIrLengthSamples(), or has a non-finite tap (phase 06b). Frees retired IRs first.
    bool submitRoomIR(const RoomIR& ir, conv::CrossfadeLaw law = conv::CrossfadeLaw::EqualGain);
    // The same with a prebuilt IrSet (makeIrSet()), e.g. to switch between cached IRs.
    bool submitIrSet(std::shared_ptr<const conv::IrSet> irSet,
                     conv::CrossfadeLaw law = conv::CrossfadeLaw::EqualGain);
    // Non-audio thread. nullptr when the IR doesn't fit (as submitRoomIR).
    std::shared_ptr<const conv::IrSet> makeIrSet(const RoomIR& ir) const;

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
