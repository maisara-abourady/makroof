#include "sim/conv/PartitionedConvolver.h"

#include "sim/Cancel.h"

#include "sim/conv/Denormals.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>

namespace sim::conv {

bool isSupportedPartitionSize(int partitionSize) noexcept
{
    return std::find(std::begin(kSupportedPartitionSizes), std::end(kSupportedPartitionSizes), partitionSize)
           != std::end(kSupportedPartitionSizes);
}

std::size_t partitionCount(std::size_t length, int partitionSize) noexcept
{
    const auto p = static_cast<std::size_t>(partitionSize);
    return std::max<std::size_t>(1, (length + p - 1) / p);
}

// ---- IrSet ----

std::shared_ptr<const IrSet> IrSet::create(const RoomIR& ir, int partitionSize,
                                           const std::atomic<bool>* cancel)
{
    if (ir.taps.size() != static_cast<std::size_t>(ir.numEmitters) * static_cast<std::size_t>(ir.numOutputs))
        throw std::invalid_argument("IrSet::create: RoomIR has " + std::to_string(ir.taps.size())
                                    + " taps for " + std::to_string(ir.numEmitters) + " x "
                                    + std::to_string(ir.numOutputs) + " paths");
    return create(ir.numEmitters, ir.numOutputs, ir.taps, partitionSize, ir.sampleRate, cancel);
}

std::shared_ptr<const IrSet> IrSet::create(int numInputs, int numOutputs,
                                           const std::vector<std::vector<float>>& taps, int partitionSize,
                                           double sampleRate, const std::atomic<bool>* cancel)
{
    if (!isSupportedPartitionSize(partitionSize))
        throw std::invalid_argument("IrSet::create: partition size must be 128, 256 or 512, got "
                                    + std::to_string(partitionSize));
    if (numInputs <= 0 || numOutputs <= 0)
        throw std::invalid_argument("IrSet::create: needs at least one input and one output");
    const auto paths = static_cast<std::size_t>(numInputs) * static_cast<std::size_t>(numOutputs);
    if (taps.size() != paths)
        throw std::invalid_argument("IrSet::create: expected " + std::to_string(paths) + " paths, got "
                                    + std::to_string(taps.size()));
    const std::size_t length = taps.front().size();
    for (const auto& t : taps)
        if (t.size() != length)
            throw std::invalid_argument("IrSet::create: all paths must have the same length");
    // Phase 06b scope 4: a NaN or +-Inf tap would make every output sample it touches non-finite for
    // as long as the IR plays. Rejected here, off the audio thread; the engine keeps its current IR.
    // (Finite taps cannot overflow the spectrum: they are scaled by 1 / 2P first and a partition has P
    // of them, so every bin is at most max|h| / 2.)
    for (const auto& t : taps)
        if (!std::all_of(t.begin(), t.end(), [](float v) { return std::isfinite(v); }))
            throw std::invalid_argument("IrSet::create: the IR has a non-finite (NaN or Inf) tap");

    std::shared_ptr<IrSet> set(new IrSet());
    set->numInputs_ = numInputs;
    set->numOutputs_ = numOutputs;
    set->partitionSize_ = partitionSize;
    set->numPartitions_ = partitionCount(length, partitionSize);
    set->length_ = length;
    set->sampleRate_ = sampleRate;

    const auto p = static_cast<std::size_t>(partitionSize);
    const std::size_t twoP = 2 * p;
    set->spectra_ = allocateAligned(paths * set->numPartitions_ * twoP);
    Fft fft(static_cast<int>(twoP));
    AlignedFloats block = allocateAligned(twoP);
    // The 1 / 2P of the inverse transform is folded into H, so the audio thread needn't scale.
    const float scale = 1.0f / static_cast<float>(twoP);
    for (std::size_t path = 0; path < paths; ++path)
    {
        const auto& h = taps[path];
        for (std::size_t k = 0; k < set->numPartitions_; ++k)
        {
            if ((k & 127) == 0)
                throwIfCancelled(cancel); // phase-07c-1 condition 10: the IR-set build
            std::fill(block.get(), block.get() + twoP, 0.0f);
            const std::size_t begin = k * p;
            const std::size_t end = std::min(length, begin + p);
            for (std::size_t i = begin; i < end; ++i)
                block[i - begin] = h[i] * scale;
            float* dest = set->spectra_.get() + (path * set->numPartitions_ + k) * twoP;
            fft.forward(block.get(), dest);
        }
    }
    return set;
}

// ---- FrequencyDelayLine ----

void FrequencyDelayLine::prepare(int numInputs, int partitionSize, std::size_t capacity)
{
    if (numInputs <= 0 || !isSupportedPartitionSize(partitionSize) || capacity == 0)
        throw std::invalid_argument("FrequencyDelayLine::prepare: bad arguments");
    numInputs_ = numInputs;
    partitionSize_ = 0; // set once both buffers are allocated
    capacity_ = capacity;
    head_ = 0;
    const auto twoP = static_cast<std::size_t>(2 * partitionSize);
    time_ = allocateAligned(static_cast<std::size_t>(numInputs) * twoP);
    ring_ = allocateAligned(static_cast<std::size_t>(numInputs) * capacity * twoP);
    partitionSize_ = partitionSize;
}

void FrequencyDelayLine::reset() noexcept
{
    const auto twoP = static_cast<std::size_t>(2 * partitionSize_);
    if (time_)
        std::fill(time_.get(), time_.get() + static_cast<std::size_t>(numInputs_) * twoP, 0.0f);
    if (ring_)
        std::fill(ring_.get(), ring_.get() + static_cast<std::size_t>(numInputs_) * capacity_ * twoP, 0.0f);
    head_ = 0;
}

void FrequencyDelayLine::push(const float* const* blocks, Fft& fft) noexcept
{
    const auto p = static_cast<std::size_t>(partitionSize_);
    head_ = head_ + 1 == capacity_ ? 0 : head_ + 1;
    for (int n = 0; n < numInputs_; ++n)
    {
        float* time = time_.get() + static_cast<std::size_t>(n) * 2 * p;
        // [previous P | newest P]: the old newest half becomes the previous half.
        std::memcpy(time, time + p, p * sizeof(float));
        std::memcpy(time + p, blocks[n], p * sizeof(float));
        fft.forward(time, ring_.get() + (static_cast<std::size_t>(n) * capacity_ + head_) * 2 * p);
    }
}

// ---- renderPartition ----

void renderPartition(const IrSet& ir, const FrequencyDelayLine& fdl, Fft& fft, float* accumulator,
                     float* timeScratch, float* const* out) noexcept
{
    const auto p = static_cast<std::size_t>(fdl.partitionSize());
    const std::size_t twoP = 2 * p;
    const std::size_t partitions = ir.numPartitions();
    const std::size_t capacity = fdl.capacity();
    for (int m = 0; m < ir.numOutputs(); ++m)
    {
        std::fill(accumulator, accumulator + twoP, 0.0f);
        for (int n = 0; n < ir.numInputs(); ++n)
        {
            const float* h = ir.spectrum(n, m, 0);
            std::size_t slot = fdl.head(); // age 0 pairs with partition 0
            for (std::size_t k = 0; k < partitions; ++k)
            {
                fft.multiplyAccumulate(fdl.slotSpectrum(n, slot), h, accumulator, 1.0f);
                h += twoP;
                slot = slot == 0 ? capacity - 1 : slot - 1;
            }
        }
        fft.inverse(accumulator, timeScratch);
        // Overlap-save: the last P samples are the linear convolution; the first P wrap around.
        std::memcpy(out[m], timeScratch + p, p * sizeof(float));
    }
}

// ---- PartitionedConvolver ----

void PartitionedConvolver::prepare(int numInputs, int numOutputs, int maxBlock, int partitionSize,
                                   std::size_t maxPartitions)
{
    if (numInputs <= 0 || numOutputs <= 0 || maxBlock <= 0 || !isSupportedPartitionSize(partitionSize)
        || maxPartitions == 0)
        throw std::invalid_argument("PartitionedConvolver::prepare: bad arguments");
    numInputs_ = numInputs;
    numOutputs_ = numOutputs;
    maxBlock_ = maxBlock;
    partitionSize_ = 0; // stays 0 (process() a no-op) until every allocation below succeeded
    position_ = 0;
    ir_.reset();
    const auto p = static_cast<std::size_t>(partitionSize);
    fft_ = Fft(2 * partitionSize);
    fdl_.prepare(numInputs, partitionSize, maxPartitions);
    inBlock_ = allocateAligned(static_cast<std::size_t>(numInputs) * p);
    outBlock_ = allocateAligned(static_cast<std::size_t>(numOutputs) * p);
    accumulator_ = allocateAligned(2 * p);
    timeScratch_ = allocateAligned(2 * p);
    inPtrs_.assign(static_cast<std::size_t>(numInputs), nullptr);
    outPtrs_.assign(static_cast<std::size_t>(numOutputs), nullptr);
    for (int n = 0; n < numInputs; ++n)
        inPtrs_[static_cast<std::size_t>(n)] = inBlock_.get() + static_cast<std::size_t>(n) * p;
    for (int m = 0; m < numOutputs; ++m)
        outPtrs_[static_cast<std::size_t>(m)] = outBlock_.get() + static_cast<std::size_t>(m) * p;
    partitionSize_ = partitionSize;
}

void PartitionedConvolver::setIrSet(std::shared_ptr<const IrSet> ir)
{
    if (ir
        && (ir->numInputs() != numInputs_ || ir->numOutputs() != numOutputs_
            || ir->partitionSize() != partitionSize_ || ir->numPartitions() > fdl_.capacity()))
        throw std::invalid_argument("PartitionedConvolver::setIrSet: IrSet does not fit prepare()");
    ir_ = std::move(ir);
}

void PartitionedConvolver::reset() noexcept
{
    fdl_.reset();
    const auto p = static_cast<std::size_t>(partitionSize_);
    if (inBlock_)
        std::fill(inBlock_.get(), inBlock_.get() + static_cast<std::size_t>(numInputs_) * p, 0.0f);
    if (outBlock_)
        std::fill(outBlock_.get(), outBlock_.get() + static_cast<std::size_t>(numOutputs_) * p, 0.0f);
    position_ = 0;
}

void PartitionedConvolver::computeBlock() noexcept
{
    fdl_.push(inPtrs_.data(), fft_);
    if (ir_)
        renderPartition(*ir_, fdl_, fft_, accumulator_.get(), timeScratch_.get(), outPtrs_.data());
    else
        std::fill(outBlock_.get(), outBlock_.get() + static_cast<std::size_t>(numOutputs_ * partitionSize_),
                  0.0f);
}

void PartitionedConvolver::process(const float* const* in, float* const* out, int n) noexcept
{
    if (partitionSize_ == 0) // not prepared: nothing to do, never spin
        return;
    const ScopedFlushDenormals noDenormals;
    int done = 0;
    while (done < n)
    {
        const int chunk = std::min(n - done, partitionSize_ - position_);
        const auto bytes = static_cast<std::size_t>(chunk) * sizeof(float);
        // Inputs first, so that in-place processing reads every input sample before it is overwritten.
        for (int c = 0; c < numInputs_; ++c)
            std::memcpy(inPtrs_[static_cast<std::size_t>(c)] + position_, in[c] + done, bytes);
        for (int c = 0; c < numOutputs_; ++c)
            std::memcpy(out[c] + done, outPtrs_[static_cast<std::size_t>(c)] + position_, bytes);
        position_ += chunk;
        done += chunk;
        if (position_ == partitionSize_)
        {
            computeBlock();
            position_ = 0;
        }
    }
}

void PartitionedConvolver::process(const float* in, float* out, int n) noexcept
{
    const float* const ins[1] = {in};
    float* const outs[1] = {out};
    process(ins, outs, n);
}

} // namespace sim::conv
