#include "sim/conv/CrossfadingConvolver.h"

#include "sim/conv/Denormals.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <numbers>
#include <stdexcept>
#include <utility>

namespace sim::conv {

namespace {

constexpr std::size_t lawIndex(CrossfadeLaw law) noexcept
{
    return law == CrossfadeLaw::EqualGain ? 0 : 1;
}

} // namespace

CrossfadingConvolver::~CrossfadingConvolver()
{
    clearAll();
}

void CrossfadingConvolver::clearAll() noexcept
{
    delete mailbox_.exchange(nullptr, std::memory_order_acq_rel);
    delete current_;
    delete next_;
    delete retiring_;
    current_ = next_ = retiring_ = nullptr;
    releaseRetired();
}

void CrossfadingConvolver::prepare(int numInputs, int numOutputs, int maxBlock, int partitionSize,
                                   std::size_t maxPartitions, int fadeLengthSamples)
{
    if (numInputs <= 0 || numOutputs <= 0 || maxBlock <= 0 || !isSupportedPartitionSize(partitionSize)
        || maxPartitions == 0 || fadeLengthSamples < 1)
        throw std::invalid_argument("CrossfadingConvolver::prepare: bad arguments");
    clearAll();
    numInputs_ = numInputs;
    numOutputs_ = numOutputs;
    maxBlock_ = maxBlock;
    partitionSize_ = partitionSize;
    fadeLength_ = fadeLengthSamples;
    position_ = 0;
    blockStart_ = 0;
    fadeStart_ = -1;
    fades_ = 0;

    const auto p = static_cast<std::size_t>(partitionSize);
    fft_ = Fft(2 * partitionSize);
    fdl_.prepare(numInputs, partitionSize, maxPartitions);
    inBlock_ = allocateAligned(static_cast<std::size_t>(numInputs) * p);
    outBlock_ = allocateAligned(static_cast<std::size_t>(numOutputs) * p);
    yA_ = allocateAligned(static_cast<std::size_t>(numOutputs) * p);
    yB_ = allocateAligned(static_cast<std::size_t>(numOutputs) * p);
    accumulator_ = allocateAligned(2 * p);
    timeScratch_ = allocateAligned(2 * p);

    // AX18 ramps, j = 0 .. L. Equal gain: g = j / L (linear, complementary). Equal power:
    // sin / cos of g pi/2 (squares sum to 1).
    const auto len = static_cast<std::size_t>(fadeLengthSamples);
    for (auto& r : rampIn_)
        r.assign(len + 1, 0.0f);
    for (auto& r : rampOut_)
        r.assign(len + 1, 0.0f);
    for (std::size_t j = 0; j <= len; ++j)
    {
        const double g = static_cast<double>(j) / static_cast<double>(len);
        rampIn_[0][j] = static_cast<float>(g);
        rampOut_[0][j] = static_cast<float>(1.0 - g);
        rampIn_[1][j] = static_cast<float>(std::sin(g * std::numbers::pi / 2.0));
        rampOut_[1][j] = static_cast<float>(std::cos(g * std::numbers::pi / 2.0));
    }
    rampOut_[1][len] = 0.0f; // cos(pi/2) is 6e-17, not 0

    inPtrs_.assign(static_cast<std::size_t>(numInputs), nullptr);
    outPtrs_.assign(static_cast<std::size_t>(numOutputs), nullptr);
    yAPtrs_.assign(static_cast<std::size_t>(numOutputs), nullptr);
    yBPtrs_.assign(static_cast<std::size_t>(numOutputs), nullptr);
    for (int c = 0; c < numInputs; ++c)
        inPtrs_[static_cast<std::size_t>(c)] = inBlock_.get() + static_cast<std::size_t>(c) * p;
    for (int c = 0; c < numOutputs; ++c)
    {
        const std::size_t offset = static_cast<std::size_t>(c) * p;
        outPtrs_[static_cast<std::size_t>(c)] = outBlock_.get() + offset;
        yAPtrs_[static_cast<std::size_t>(c)] = yA_.get() + offset;
        yBPtrs_[static_cast<std::size_t>(c)] = yB_.get() + offset;
    }
}

bool CrossfadingConvolver::requestIr(std::shared_ptr<const IrSet> ir, CrossfadeLaw law)
{
    if (!ir || ir->numInputs() != numInputs_ || ir->numOutputs() != numOutputs_
        || ir->partitionSize() != partitionSize_ || ir->numPartitions() > fdl_.capacity())
        return false;
    auto* request = new Request{std::move(ir), law};
    // Latest wins: a request the audio thread never took comes back here and is freed here.
    delete mailbox_.exchange(request, std::memory_order_acq_rel);
    return true;
}

std::size_t CrossfadingConvolver::releaseRetired()
{
    const std::lock_guard<std::mutex> lock(consumerMutex_);
    std::size_t read = readIndex_.load(std::memory_order_relaxed);
    const std::size_t write = writeIndex_.load(std::memory_order_acquire);
    std::size_t count = 0;
    while (read != write)
    {
        Request*& slot = releaseQueue_[read % kReleaseQueueSize];
        delete slot;
        slot = nullptr;
        ++read;
        ++count;
    }
    readIndex_.store(read, std::memory_order_release);
    return count;
}

bool CrossfadingConvolver::pushRetired(Request* r) noexcept
{
    const std::size_t write = writeIndex_.load(std::memory_order_relaxed);
    const std::size_t read = readIndex_.load(std::memory_order_acquire);
    if (write - read >= kReleaseQueueSize)
        return false;
    releaseQueue_[write % kReleaseQueueSize] = r;
    writeIndex_.store(write + 1, std::memory_order_release);
    return true;
}

const IrSet* CrossfadingConvolver::currentIr() const noexcept
{
    return current_ != nullptr ? current_->ir.get() : nullptr;
}

void CrossfadingConvolver::reset() noexcept
{
    if (next_ != nullptr)
    {
        Request* old = current_;
        current_ = next_;
        next_ = nullptr;
        if (old != nullptr && !pushRetired(old))
        {
            delete retiring_; // not the audio thread: reset() is not concurrent with process()
            retiring_ = old;
        }
    }
    fdl_.reset();
    const auto p = static_cast<std::size_t>(partitionSize_);
    if (inBlock_)
        std::fill(inBlock_.get(), inBlock_.get() + static_cast<std::size_t>(numInputs_) * p, 0.0f);
    if (outBlock_)
        std::fill(outBlock_.get(), outBlock_.get() + static_cast<std::size_t>(numOutputs_) * p, 0.0f);
    position_ = 0;
    blockStart_ = 0;
    fadeStart_ = -1;
}

void CrossfadingConvolver::computeBlock() noexcept
{
    const auto p = static_cast<std::size_t>(partitionSize_);
    const std::int64_t newStart = blockStart_ + partitionSize_; // first output sample of this block
    fdl_.push(inPtrs_.data(), fft_);

    if (retiring_ != nullptr && pushRetired(retiring_))
        retiring_ = nullptr;
    if (next_ == nullptr && retiring_ == nullptr)
    {
        if (Request* r = mailbox_.exchange(nullptr, std::memory_order_acq_rel))
        {
            if (current_ == nullptr && blockStart_ == 0)
            {
                // The first partition after prepare() / reset(): the output so far is the latency's
                // silence, so the IR is installed at once (offline renders start exact, no fade).
                current_ = r;
            }
            else // AQ4: every other change crossfades, from silence too (y_A = 0 when current_ is null)
            {
                next_ = r;
                fadeStart_ = newStart;
                ++fades_;
            }
        }
    }

    if (current_ != nullptr)
        renderPartition(*current_->ir, fdl_, fft_, accumulator_.get(), timeScratch_.get(), yAPtrs_.data());
    else
        std::fill(yA_.get(), yA_.get() + static_cast<std::size_t>(numOutputs_) * p, 0.0f);

    if (next_ == nullptr)
    {
        std::memcpy(outBlock_.get(), yA_.get(), static_cast<std::size_t>(numOutputs_) * p * sizeof(float));
    }
    else
    {
        renderPartition(*next_->ir, fdl_, fft_, accumulator_.get(), timeScratch_.get(), yBPtrs_.data());
        const std::size_t law = lawIndex(next_->law);
        const float* gIn = rampIn_[law].data();
        const float* gOut = rampOut_[law].data();
        const auto len = static_cast<std::int64_t>(fadeLength_);
        for (int m = 0; m < numOutputs_; ++m)
        {
            const float* a = yAPtrs_[static_cast<std::size_t>(m)];
            const float* b = yBPtrs_[static_cast<std::size_t>(m)];
            float* o = outPtrs_[static_cast<std::size_t>(m)];
            for (std::size_t j = 0; j < p; ++j)
            {
                const std::int64_t s = newStart + static_cast<std::int64_t>(j);
                const auto idx = static_cast<std::size_t>(std::min(s - fadeStart_, len));
                o[j] = gOut[idx] * a[j] + gIn[idx] * b[j];
            }
        }
        if (newStart + partitionSize_ >= fadeStart_ + len)
        {
            // Fade over by the end of this block: B becomes current, A's request is retired.
            Request* old = current_;
            current_ = next_;
            next_ = nullptr;
            if (old != nullptr && !pushRetired(old))
                retiring_ = old;
        }
    }
    blockStart_ = newStart;
}

void CrossfadingConvolver::process(const float* const* in, float* const* out, int n) noexcept
{
    if (partitionSize_ == 0) // not prepared (or prepare() threw): nothing to do, never spin
        return;
    const ScopedFlushDenormals noDenormals;
    int done = 0;
    while (done < n)
    {
        const int chunk = std::min(n - done, partitionSize_ - position_);
        const auto bytes = static_cast<std::size_t>(chunk) * sizeof(float);
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

void CrossfadingConvolver::process(const float* in, float* out, int n) noexcept
{
    const float* const ins[1] = {in};
    float* const outs[1] = {out};
    process(ins, outs, n);
}

} // namespace sim::conv
