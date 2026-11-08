#include "sim/RealtimeEngine.h"

#include "sim/tail/NoiseTail.h"

#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>

namespace sim {

RealtimeEngine::RealtimeEngine(int partitionSize)
    : partitionSize_(partitionSize)
{
    if (!conv::isSupportedPartitionSize(partitionSize))
        throw std::invalid_argument("RealtimeEngine: partition size must be 128, 256 or 512, got "
                                    + std::to_string(partitionSize));
}

std::size_t RealtimeEngine::maxIrLengthSamples(double sampleRate) noexcept
{
    return static_cast<std::size_t>(std::ceil(tail::kMaxIrLengthS * sampleRate)) + kAlignPreRollSamples;
}

void RealtimeEngine::prepare(double sampleRate, int maxBlock)
{
    sampleRate_ = 0.0; // unprepared (silence) until this call succeeds, also when it throws
    if (!isSupportedSampleRate(sampleRate))
        throw std::invalid_argument("RealtimeEngine::prepare: unsupported sample rate");
    if (maxBlock < 1)
        throw std::invalid_argument("RealtimeEngine::prepare: maxBlock must be >= 1");
    const auto fade = static_cast<int>(std::lround(kCrossfadeS * sampleRate)); // AQ4: 30 ms
    convolver_.prepare(kNumChannels, kNumChannels, maxBlock, partitionSize_,
                       conv::partitionCount(maxIrLengthSamples(sampleRate), partitionSize_), fade);
    sampleRate_ = sampleRate;
}

void RealtimeEngine::reset() noexcept
{
    if (sampleRate_ <= 0.0)
        return;
    convolver_.resetAndDropIrs();
}

void RealtimeEngine::process(const float* const in[2], float* const out[2], int n) noexcept
{
    if (sampleRate_ <= 0.0) // not prepared (or prepare() threw)
    {
        for (int c = 0; c < kNumChannels; ++c)
            for (int i = 0; i < n; ++i)
                out[c][i] = 0.0f;
        return;
    }
    convolver_.process(in, out, n);
}

std::shared_ptr<const conv::IrSet> RealtimeEngine::makeIrSet(const RoomIR& ir) const
{
    if (ir.numEmitters != kNumChannels || ir.numOutputs != kNumChannels || ir.sampleRate != sampleRate_
        || ir.length() > maxIrLengthSamples(sampleRate_)
        || ir.taps.size() != static_cast<std::size_t>(kNumChannels * kNumChannels))
        return nullptr;
    try
    {
        // Phase 06b scope 4: non-finite taps are refused like an IR
        // that doesn't fit, so submitRoomIR() returns false and the current IR keeps playing.
        return conv::IrSet::create(ir, partitionSize_);
    }
    catch (const std::invalid_argument&)
    {
        return nullptr;
    }
}

bool RealtimeEngine::submitRoomIR(const RoomIR& ir, conv::CrossfadeLaw law)
{
    return submitIrSet(makeIrSet(ir), law);
}

bool RealtimeEngine::submitIrSet(std::shared_ptr<const conv::IrSet> irSet, conv::CrossfadeLaw law)
{
    releaseRetired();
    if (!irSet || irSet->sampleRate() != sampleRate_)
        return false;
    return convolver_.requestIr(std::move(irSet), law);
}

} // namespace sim
