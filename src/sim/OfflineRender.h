#pragma once

// The REFERENCE renderer: convolves an input with a RoomIR offline, favouring correctness over
// speed. The real-time partitioned convolver (Phase 06) is tested against this, so it must stay
// independent of the real-time path: no PFFFT, no partitioning, no float accumulation. It uses a
// plain direct (time-domain) sum, or for long dense IRs a one-shot full-length FFT convolution with
// this file's own double-precision radix-2 FFT.
#include "sim/Engine.h"

#include <cstddef>
#include <vector>

namespace sim {

// Audio as one vector per channel; every channel has the same length.
using MultiChannel = std::vector<std::vector<float>>;

enum class ConvolutionMethod
{
    // Direct when the work is small (see chooseMethod()), FFT otherwise.
    Auto,
    // y[n] = sum_k h[k] x[n-k], summed in double. Exact zeros in h are skipped, which leaves the
    // result unchanged (except that it never turns a -0 or a NaN in x into something else through
    // a 0 tap), and makes sparse IRs cheap.
    Direct,
    // Full-length linear convolution by one FFT of size >= len(x) + len(h) - 1 (double precision,
    // no partitioning). Agrees with Direct to rounding error (~1e-12 relative).
    Fft
};

// The method Auto picks for one input channel of `inputLength` samples and an IR with
// `nonZeroTaps` non-zero taps out of `irLength`: Direct when nonZeroTaps * inputLength <= 2^26
// multiply-adds, or the IR has at most 64 non-zero taps; FFT otherwise. A pure function of
// the sizes, so a render is deterministic.
ConvolutionMethod chooseMethod(std::size_t inputLength, std::size_t irLength,
                               std::size_t nonZeroTaps) noexcept;

// Renders `input` (input.size() == ir.numEmitters channels) through `ir`:
//   out[o][n] = sum_e (input[e] * ir.taps[e * numOutputs + o])[n]
// Output: ir.numOutputs channels of length input_length + ir.length() - 1 (the full tail; for an
// IR of length 1 the output is as long as the input). An empty input gives empty channels.
// Throws std::invalid_argument when the channel counts or lengths don't match. Deterministic.
MultiChannel renderOffline(const RoomIR& ir, const MultiChannel& input,
                           ConvolutionMethod method = ConvolutionMethod::Auto);

// One linear convolution, exposed for tests: result length x.size() + h.size() - 1 (empty if
// either is empty), accumulated in double.
std::vector<double> convolve(const std::vector<float>& x, const std::vector<float>& h,
                             ConvolutionMethod method);

} // namespace sim
