#include "sim/conv/CrossfadingConvolver.h"

#include "sim/conv/Denormals.h"

#include <algorithm>
#include <cassert>
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
    partitionSize_ = 0; // stays 0 (process() a no-op) until every allocation below succeeded
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
    timeScratch_ = allocateAligned(2 * p);
    for (Lane* lane : {&laneA_, &laneB_})
    {
        lane->acc = allocateAligned(static_cast<std::size_t>(numOutputs) * 2 * p);
        lane->done = lane->total = 0;
    }

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
    partitionSize_ = partitionSize;
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
        // Never frees here (phase-07c-1 condition 10: reset() may run on a host's processing thread). A fade
        // is only ever started while retiring_ is empty (process() step 4), and retiring_ is only set when a
        // fade ends, so while next_ is set retiring_ is empty: a full release queue parks `old` there and
        // the next process() or submit hands it on.
        assert(retiring_ == nullptr);
        if (old != nullptr && !pushRetired(old))
            retiring_ = old;
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
    restartLanes();
}

void CrossfadingConvolver::resetAndDropIrs() noexcept
{
    if (partitionSize_ <= 0)
        return;
    clearAll(); // mailbox, current, next, retiring, then the release queue
    reset();
}

void CrossfadingConvolver::startLane(Lane& lane, const Request* r) noexcept
{
    lane.done = 0;
    lane.total = 0;
    if (r == nullptr)
        return;
    const IrSet& ir = *r->ir;
    lane.total = static_cast<std::size_t>(ir.numOutputs()) * static_cast<std::size_t>(ir.numInputs())
                 * (ir.numPartitions() - 1);
    std::fill(lane.acc.get(),
              lane.acc.get()
                  + static_cast<std::size_t>(numOutputs_) * 2 * static_cast<std::size_t>(partitionSize_),
              0.0f);
}

void CrossfadingConvolver::advanceLane(Lane& lane, const IrSet& ir, std::size_t target) noexcept
{
    // Unit u = one 2P-bin multiply-add: output m, input n, partition k >= 1, in that nesting order.
    // Before the boundary's FDL push, X(b + 1 - k) is the spectrum of age k - 1.
    target = std::min(target, lane.total);
    if (lane.done >= target)
        return;
    const auto twoP = static_cast<std::size_t>(2 * partitionSize_);
    const std::size_t k1 = ir.numPartitions() - 1; // > 0 whenever total > 0
    const auto inputs = static_cast<std::size_t>(ir.numInputs());
    const std::size_t capacity = fdl_.capacity();
    const std::size_t head = fdl_.head();
    std::size_t m = lane.done / (inputs * k1);
    std::size_t n = (lane.done / k1) % inputs;
    std::size_t k = 1 + lane.done % k1;
    for (std::size_t u = lane.done; u < target; ++u)
    {
        // Partitions in descending order (the quiet, late ones first): the running sum stays small
        // while most terms are added, which lowers the float rounding error (measured: the
        // render_cli null at P = 128 went from -124.9 to -128.6 dB, ascending vs descending).
        const std::size_t kk = k1 + 1 - k;
        const std::size_t age = kk - 1;
        const std::size_t slot = head >= age ? head - age : head + capacity - age;
        fft_.multiplyAccumulate(fdl_.slotSpectrum(static_cast<int>(n), slot),
                                ir.spectrum(static_cast<int>(n), static_cast<int>(m), kk),
                                lane.acc.get() + m * twoP, 1.0f);
        if (++k > k1)
        {
            k = 1;
            if (++n == inputs)
            {
                n = 0;
                ++m;
            }
        }
    }
    macs_ += target - lane.done;
    lane.done = target;
}

void CrossfadingConvolver::finishLane(Lane& lane, const IrSet& ir, float* const* y) noexcept
{
    // After the FDL push: add the k = 0 term (the new block, age 0) and transform back.
    const auto p = static_cast<std::size_t>(partitionSize_);
    for (int m = 0; m < ir.numOutputs(); ++m)
    {
        float* acc = lane.acc.get() + static_cast<std::size_t>(m) * 2 * p;
        for (int n = 0; n < ir.numInputs(); ++n)
            fft_.multiplyAccumulate(fdl_.spectrum(n, 0), ir.spectrum(n, m, 0), acc, 1.0f);
        macs_ += static_cast<std::uint64_t>(ir.numInputs());
        fft_.inverse(acc, timeScratch_.get());
        // Overlap-save: the last P samples are the linear convolution; the first P wrap around.
        std::memcpy(y[m], timeScratch_.get() + p, p * sizeof(float));
    }
}

void CrossfadingConvolver::advanceLanes() noexcept
{
    // Keep each state's k >= 1 work in step with the samples taken in: a fraction position / P.
    const auto pos = static_cast<std::size_t>(position_);
    const auto p = static_cast<std::size_t>(partitionSize_);
    if (current_ != nullptr)
        advanceLane(laneA_, *current_->ir, laneA_.total * pos / p);
    if (next_ != nullptr)
        advanceLane(laneB_, *next_->ir, laneB_.total * pos / p);
}

void CrossfadingConvolver::restartLanes() noexcept
{
    startLane(laneA_, current_);
    startLane(laneB_, next_);
}

void CrossfadingConvolver::computeBlock() noexcept
{
    const auto p = static_cast<std::size_t>(partitionSize_);
    const std::int64_t newStart = blockStart_ + partitionSize_; // first output sample of this block

    // 1. The very first IR after prepare() / reset() is installed here and rendered in full this
    //    block (the output so far is the latency's silence: offline renders start exact, no fade).
    //    Every other hand-over happens at the end of the boundary, see 4.
    if (retiring_ != nullptr && pushRetired(retiring_))
        retiring_ = nullptr;
    if (current_ == nullptr && next_ == nullptr && retiring_ == nullptr && blockStart_ == 0)
    {
        if (Request* r = mailbox_.exchange(nullptr, std::memory_order_acq_rel))
        {
            current_ = r;
            startLane(laneA_, current_); // its lane did not run during this block: whole sum below
        }
    }
    // B is taken at the end of a boundary (step 4), so a set next_ always had its lane run this block.
    const bool renderB = next_ != nullptr;

    // 2. The k >= 1 remainder (before the push), the push, then k = 0 and the inverse transforms.
    if (current_ != nullptr)
        advanceLane(laneA_, *current_->ir, laneA_.total);
    if (renderB)
        advanceLane(laneB_, *next_->ir, laneB_.total);
    fdl_.push(inPtrs_.data(), fft_);
    if (current_ != nullptr)
        finishLane(laneA_, *current_->ir, yAPtrs_.data());
    else
        std::fill(yA_.get(), yA_.get() + static_cast<std::size_t>(numOutputs_) * p, 0.0f);

    if (!renderB)
    {
        std::memcpy(outBlock_.get(), yA_.get(), static_cast<std::size_t>(numOutputs_) * p * sizeof(float));
    }
    else
    {
        finishLane(laneB_, *next_->ir, yBPtrs_.data());
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

    // 4. Hand-over, after a finished fade has retired (so back-to-back requests keep the AQ4 pace:
    //    one fade per 30 ms plus at most a block). A request taken now accumulates during the next
    //    block and enters the output with it: s0 = blockStart_ + P. AQ4: every change crossfades, from
    //    silence too (y_A = 0 when current_ is null).
    if (retiring_ != nullptr && pushRetired(retiring_))
        retiring_ = nullptr;
    if (next_ == nullptr && retiring_ == nullptr)
    {
        if (Request* r = mailbox_.exchange(nullptr, std::memory_order_acq_rel))
        {
            next_ = r;
            fadeStart_ = blockStart_ + partitionSize_;
            ++fades_;
        }
    }

    // 5. The next block's accumulation starts from zero (lane A for current_, lane B for next_).
    restartLanes();
}

void CrossfadingConvolver::process(const float* const* in, float* const* out, int n) noexcept
{
    if (partitionSize_ == 0) // not prepared (or prepare() threw): nothing to do, never spin
        return;
    const ScopedFlushDenormals noDenormals;
    macs_ = 0;
    int done = 0;
    while (done < n)
    {
        const int chunk = std::min(n - done, partitionSize_ - position_);
        const auto bytes = static_cast<std::size_t>(chunk) * sizeof(float);
        for (int c = 0; c < numInputs_; ++c)
        {
            float* dst = inPtrs_[static_cast<std::size_t>(c)] + position_;
            std::memcpy(dst, in[c] + done, bytes);
            // AX32 input bound: a sample is taken in unchanged iff |x| <= kInputBound; NaN, +-Inf and
            // |x| > kInputBound become 0 (one comparison: it is false for NaN). Every FDL bin then stays
            // <= 2P * kInputBound, so neither the forward FFT nor the delay line can overflow.
            for (int i = 0; i < chunk; ++i)
                if (!(std::fabs(dst[i]) <= kInputBound))
                    dst[i] = 0.0f;
        }
        for (int c = 0; c < numOutputs_; ++c)
            std::memcpy(out[c] + done, outPtrs_[static_cast<std::size_t>(c)] + position_, bytes);
        position_ += chunk;
        done += chunk;
        if (position_ == partitionSize_)
        {
            computeBlock();
            position_ = 0;
        }
        else
        {
            advanceLanes();
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
