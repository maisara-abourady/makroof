#pragma once

// Builds a broadband pressure IR from per-octave-band image amplitudes (Phase 03).
//
// 1. Each band gets a sparse train of fractional-delay impulses (Kaiser-windowed sinc, 33 taps,
//    beta = 8, unit DC gain) scaled by that band's image amplitude.
// 2. The bands are filtered by a linear-phase, perfect-reconstruction octave filterbank and summed.
//
// The filterbank is complementary: 7 linear-phase low-pass FIRs P_0..P_6 (Kaiser-windowed sinc,
// cut-off at the crossovers fc_k * sqrt(2) between adjacent base-2 octave bands, all centred on the
// same sample) give the band filters
//     B_0 = P_0,   B_k = P_k - P_(k-1) (k = 1..6),   B_7 = delta - P_6,
// which sum to a delta by construction whatever the low-passes look like (perfect
// reconstruction). B_0 extends to DC and B_7 to Nyquist. The sum over bands is evaluated as
//     y = x_7 + sum_k P_k * (x_k - x_(k+1)),
// so when all bands are equal the result is exactly the impulse train (no filtering error at all).
// The filters are zero-phase (centred): the filterbank's constant group delay is removed and peaks
// land at their true times. Their pre-ringing before sample 0 is cut off (AX1 pre-roll).
#include "sim/ism/ImageSources.h"

#include <array>
#include <cstddef>
#include <span>
#include <vector>

namespace sim::ism {

// Fractional-delay kernel (phase-03 spec): 2 * kKernelHalfLength + 1 = 33 taps, Kaiser beta 8.
inline constexpr int kKernelHalfLength = 16;
inline constexpr double kKernelKaiserBeta = 8.0;

// Crossover design: each low-pass has a transition band of +-kCrossoverTransitionOctaves around
// its crossover and kCrossoverStopbandDb stopband attenuation (Kaiser design formulas). Chosen so
// that one band's response is >= 20 dB above its neighbours' octaves (measured: ~21 dB) while
// each band's central half octave stays flat (ripple ~1e-4).
inline constexpr double kCrossoverTransitionOctaves = 0.125;
inline constexpr double kCrossoverStopbandDb = 80.0;

// Modified Bessel function of the first kind, order 0 (power series).
double besselI0(double x) noexcept;

// Taps of the fractional-delay kernel for an impulse at fractional offset `frac` in [-0.5, 0.5]
// from its nearest sample: taps[j + kKernelHalfLength] is the value at that sample + j.
// Normalised to unit sum; frac = 0 gives an exact unit delta.
std::array<double, 2 * kKernelHalfLength + 1> fractionalDelayKernel(double frac) noexcept;

class OctaveFilterbank
{
public:
    static constexpr std::size_t kNumCrossovers = contract::kNumOctaveBands - 1;

    explicit OctaveFilterbank(double sampleRate);

    double sampleRate() const noexcept { return sampleRate_; }
    // Crossover between band k and k + 1: 1000 * 2^(k - 4) * sqrt(2) Hz (88.4 Hz ... 5657 Hz).
    static double crossoverHz(std::size_t k) noexcept;
    // Exact base-2 centre of band b (62.5, 125, ..., 8000 Hz; "63" is the nominal label).
    static double bandCentreHz(std::size_t b) noexcept;

    // Low-pass k, centred: length 2 * halfLength(k) + 1, centre tap at index halfLength(k).
    const std::vector<double>& lowpass(std::size_t k) const { return lowpass_.at(k); }
    std::size_t halfLength(std::size_t k) const { return (lowpass_.at(k).size() - 1) / 2; }
    // Largest half length: the filterbank's group delay before it is removed, and how far the
    // filters ring on either side of an impulse.
    std::size_t maxHalfLength() const noexcept { return maxHalf_; }

    // Explicit band filter B_b, centred, length 2 * maxHalfLength() + 1 (for tests).
    std::vector<double> bandImpulseResponse(std::size_t b) const;

private:
    double sampleRate_;
    std::vector<std::vector<double>> lowpass_;
    std::size_t maxHalf_ = 0;
};

// Renders images into a broadband IR. An image arriving at time t lands at the (fractional)
// sample (t - timeShiftS) * sampleRate; it must be >= kKernelHalfLength (the caller's pre-roll,
// AX1). The output is long enough for the last arrival, its kernel and the filterbank ringing:
// ceil(last sample) + kKernelHalfLength + filterbank.maxHalfLength() + 1 samples. Accumulated in
// double. Deterministic.
std::vector<double> renderImageSources(std::span<const ImageSource> images, double timeShiftS,
                                       const OctaveFilterbank& filterbank);

// The per-band sparse trains of step 1 (before the filterbank), each `length` samples (for tests).
std::vector<std::vector<double>> accumulateBandTrains(std::span<const ImageSource> images, double timeShiftS,
                                                      double sampleRate, std::size_t length);

// Applies the filterbank to per-band signals (all the same length) and sums the bands; output has
// the same length (zero-phase, so nothing is shifted).
std::vector<double> synthesizeBands(const std::vector<std::vector<double>>& bandSignals,
                                    const OctaveFilterbank& filterbank);

} // namespace sim::ism
