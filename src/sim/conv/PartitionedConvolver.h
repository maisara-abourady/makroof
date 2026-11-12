#pragma once

// Uniformly partitioned overlap-save convolution (UPOLS) with a frequency-domain delay line (FDL),
// for N inputs x M outputs (2 x 2 in v1, AX7). Phase 06.
//
// Algorithm (partition size P, FFT size 2P, an IR of K = ceil(L / P) partitions h_0 .. h_{K-1}):
//   - H_{n,m,k} = FFT_2P([h_{n,m}[kP .. kP + P), 0 x P]) / 2P, computed once off the audio thread (IrSet).
//   - every P input samples, per input n: the time buffer [previous P | newest P] is transformed,
//     X_n = FFT_2P(...), and pushed into the FDL (a ring of the last K_max spectra);
//   - per output m: Y_m = sum_n sum_k X_n(age k) . H_{n,m,k}; y_m = IFFT_2P(Y_m); the LAST P
//     samples of y_m are the next P output samples (the first P are circular wrap-around, discarded:
//     overlap-save).
//   - process() accepts any block size and buffers internally into P-sized blocks: input sample t
//     contributes to output sample t + P at the earliest, so the latency is exactly P samples.
//
// Real-time rules (CLAUDE.md): prepare() and IrSet::create() allocate; process() never allocates,
// locks, logs or throws.
#include "sim/Engine.h"
#include "sim/conv/Fft.h"

#include <atomic>
#include <cstddef>
#include <memory>
#include <vector>

namespace sim::conv {

// Partition sizes the real-time engine supports (phase-06 scope 2). AQ10: P <= 512 at 48 kHz.
inline constexpr int kSupportedPartitionSizes[] = {128, 256, 512};
inline constexpr int kDefaultPartitionSize = 512;
bool isSupportedPartitionSize(int partitionSize) noexcept;

// Number of partitions of an IR of `length` samples: ceil(length / P), at least 1.
std::size_t partitionCount(std::size_t length, int partitionSize) noexcept;

// Pre-transformed IR partitions of an N x M matrix (immutable once built; shared between threads by
// std::shared_ptr<const IrSet>). Path (input n, output m) is RoomIR::taps[n * M + m].
class IrSet
{
public:
    // Built OFF the audio thread. Throws std::invalid_argument for an unsupported partition size, a
    // matrix with no inputs or outputs, taps of different lengths, or a non-finite (NaN, +-Inf) tap
    // (phase 06b scope 4). `cancel` (phase-07c-1 condition 10): checked every 128 partitions; when set,
    // throws sim::BuildCancelled. nullptr = never cancelled.
    static std::shared_ptr<const IrSet> create(const RoomIR& ir, int partitionSize,
                                               const std::atomic<bool>* cancel = nullptr);
    static std::shared_ptr<const IrSet> create(int numInputs, int numOutputs,
                                               const std::vector<std::vector<float>>& taps, int partitionSize,
                                               double sampleRate = 0.0,
                                               const std::atomic<bool>* cancel = nullptr);

    int numInputs() const noexcept { return numInputs_; }
    int numOutputs() const noexcept { return numOutputs_; }
    int partitionSize() const noexcept { return partitionSize_; }
    std::size_t numPartitions() const noexcept { return numPartitions_; }
    std::size_t length() const noexcept { return length_; }    // IR length in samples
    double sampleRate() const noexcept { return sampleRate_; } // 0 when unknown

    // 2P floats, z-domain layout (conv::Fft), already scaled by 1 / 2P.
    const float* spectrum(int input, int output, std::size_t partition) const noexcept
    {
        const std::size_t path = static_cast<std::size_t>(input) * static_cast<std::size_t>(numOutputs_)
                                 + static_cast<std::size_t>(output);
        return spectra_.get()
               + (path * numPartitions_ + partition) * static_cast<std::size_t>(2 * partitionSize_);
    }

private:
    IrSet() = default;

    int numInputs_ = 0;
    int numOutputs_ = 0;
    int partitionSize_ = 0;
    std::size_t numPartitions_ = 0;
    std::size_t length_ = 0;
    double sampleRate_ = 0.0;
    AlignedFloats spectra_;
};

// The input side shared by every convolver state: per input, the 2P time buffer and a ring of the
// last `capacity` input spectra. CrossfadingConvolver's two states read the same history, so a new
// IR's output is the exact x * h from its first block (no build-up transient).
class FrequencyDelayLine
{
public:
    // Allocates. capacity = the most partitions any IrSet used with it may have.
    void prepare(int numInputs, int partitionSize, std::size_t capacity);
    // Clears the history to silence (not real-time: call when not processing).
    void reset() noexcept;

    // Real-time: blocks[n] points to the newest P samples of input n. Transforms them and makes
    // the result the spectrum of age 0.
    void push(const float* const* blocks, Fft& fft) noexcept;

    // Spectrum of input n, `age` blocks old (0 = newest), age < capacity().
    const float* spectrum(int input, std::size_t age) const noexcept
    {
        return slotSpectrum(input, (head_ + capacity_ - age) % capacity_);
    }
    // The ring itself: slot head() holds age 0, slot head() - 1 (mod capacity) age 1, and so on.
    std::size_t head() const noexcept { return head_; }
    const float* slotSpectrum(int input, std::size_t slot) const noexcept
    {
        return ring_.get()
               + (static_cast<std::size_t>(input) * capacity_ + slot)
                     * static_cast<std::size_t>(2 * partitionSize_);
    }

    int numInputs() const noexcept { return numInputs_; }
    int partitionSize() const noexcept { return partitionSize_; }
    std::size_t capacity() const noexcept { return capacity_; }

private:
    int numInputs_ = 0;
    int partitionSize_ = 0;
    std::size_t capacity_ = 0;
    std::size_t head_ = 0; // slot of the newest spectrum
    AlignedFloats time_;   // numInputs x 2P
    AlignedFloats ring_;   // numInputs x capacity x 2P
};

// Real-time: the next P output samples of every output for `ir` (ir.numPartitions() <=
// fdl.capacity(), matching shape), written to out[m][0 .. P). accumulator and timeScratch are 2P
// aligned floats each.
void renderPartition(const IrSet& ir, const FrequencyDelayLine& fdl, Fft& fft, float* accumulator,
                     float* timeScratch, float* const* out) noexcept;

// One fixed IrSet, N x M, latency P. The building block (and the reference for) CrossfadingConvolver.
class PartitionedConvolver
{
public:
    // Allocates everything process() needs. maxBlock is the largest n process() will be given
    // (any n in 1 .. maxBlock is accepted; the internal block is always P). maxPartitions bounds
    // the IrSets setIrSet() accepts. Throws std::invalid_argument for bad arguments.
    void prepare(int numInputs, int numOutputs, int maxBlock, int partitionSize, std::size_t maxPartitions);

    // Not real-time and not concurrent with process(). nullptr = silence. Throws
    // std::invalid_argument when the IrSet's shape, partition size or length doesn't fit prepare().
    void setIrSet(std::shared_ptr<const IrSet> ir);

    // Clears the input history and the pending output (not concurrent with process()).
    void reset() noexcept;

    // Real-time. in[n] and out[m] hold n samples each; n in 1 .. maxBlock (n <= 0 does nothing).
    // in and out may be the same buffers (in place) when numInputs == numOutputs.
    // Before prepare() it does nothing.
    void process(const float* const* in, float* const* out, int n) noexcept;
    // 1 x 1 convenience.
    void process(const float* in, float* out, int n) noexcept;

    int latencySamples() const noexcept { return partitionSize_; }
    int partitionSize() const noexcept { return partitionSize_; }
    int maxBlock() const noexcept { return maxBlock_; }

private:
    void computeBlock() noexcept;

    int numInputs_ = 0;
    int numOutputs_ = 0;
    int maxBlock_ = 0;
    int partitionSize_ = 0;
    int position_ = 0; // samples of the current partition already taken in
    std::shared_ptr<const IrSet> ir_;
    Fft fft_{32};
    FrequencyDelayLine fdl_;
    AlignedFloats inBlock_;  // numInputs x P
    AlignedFloats outBlock_; // numOutputs x P (the output being played out)
    AlignedFloats accumulator_;
    AlignedFloats timeScratch_;
    std::vector<float*> inPtrs_;
    std::vector<float*> outPtrs_;
};

} // namespace sim::conv
