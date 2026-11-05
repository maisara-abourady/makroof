#include "sim/tail/NoiseTail.h"

#include "sim/Fft.h"
#include "sim/Rng.h"

#include <algorithm>
#include <cmath>
#include <complex>
#include <numbers>

namespace sim::tail {

namespace {

using Complex = std::complex<double>;

// Real spectrum of a centred (zero-phase, symmetric) low-pass placed circularly in a buffer of
// size n: the imaginary part vanishes in exact arithmetic and is dropped.
void lowpassSpectra(const ism::OctaveFilterbank& filterbank, std::size_t a, std::size_t b, const Fft& fft,
                    std::vector<Complex>& work, std::vector<double>& specA, std::vector<double>& specB)
{
    const std::size_t n = fft.size();
    std::fill(work.begin(), work.end(), Complex(0.0, 0.0));
    const auto load = [&](std::size_t k, bool imaginary) {
        const auto& h = filterbank.lowpass(k);
        const std::size_t half = filterbank.halfLength(k);
        for (std::size_t i = 0; i < h.size(); ++i)
            work[(i + n - half) % n] += imaginary ? Complex(0.0, h[i]) : Complex(h[i], 0.0);
    };
    const bool pair = b != a;
    load(a, false);
    if (pair)
        load(b, true);
    fft.forward(work);
    specA.resize(n);
    specB.resize(n);
    for (std::size_t k = 0; k < n; ++k)
    {
        const Complex zk = work[k];
        const Complex zc = std::conj(work[(n - k) % n]);
        specA[k] = (0.5 * (zk + zc)).real();
        specB[k] = pair ? (Complex(0.0, -0.5) * (zk - zc)).real() : 0.0;
    }
}

} // namespace

double tailLengthS(const RoomDecay& decay) noexcept
{
    return std::min(kMaxIrLengthS, kTailDecayRangeDb / 60.0 * decay.maxT60S());
}

std::uint32_t tailSeedForOutput(std::uint32_t tailSeed, int outputIndex) noexcept
{
    return tailSeed ^ (static_cast<std::uint32_t>(outputIndex) * 0x9E3779B9u);
}

contract::BandArray bandImpulseEnergies(const ism::OctaveFilterbank& filterbank)
{
    contract::BandArray energies{};
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const auto h = filterbank.bandImpulseResponse(b);
        double sum = 0.0;
        for (const double v : h)
            sum += v * v;
        energies[b] = sum;
    }
    return energies;
}

std::size_t unitDecayLength(double lengthS, double sampleRate) noexcept
{
    return std::max<std::size_t>(1, static_cast<std::size_t>(std::ceil(lengthS * sampleRate)));
}

BandNoiseGenerator::BandNoiseGenerator(const ism::OctaveFilterbank& filterbank, std::size_t length)
    : sampleRate_(filterbank.sampleRate())
    , length_(length)
    , half_(filterbank.maxHalfLength())
    // Noise long enough that every kept output sample is filtered by the full (centred) band filter:
    // outputs [H, H + length) of a circular convolution of size >= length + 2H don't wrap.
    , fft_(Fft::nextPowerOfTwo(length + 2 * filterbank.maxHalfLength()))
{
    const std::size_t n = fft_.size();
    // Band spectra B_0 = P_0, B_k = P_k - P_(k-1), B_7 = 1 - P_6, as in ism::OctaveFilterbank, from
    // the low-pass spectra computed two at a time.
    std::vector<Complex> work(n);
    std::vector<double> pPrev, pA, pB;
    for (std::size_t bandA = 0; bandA < contract::kNumOctaveBands; bandA += 2)
    {
        const std::size_t k1 = bandA + 1; // upper edge of band bandA + 1 (7 = none)
        const bool pair = k1 < ism::OctaveFilterbank::kNumCrossovers;
        lowpassSpectra(filterbank, bandA, pair ? k1 : bandA, fft_, work, pA, pB);
        std::vector<double> lower(n), upper(n);
        for (std::size_t k = 0; k < n; ++k)
        {
            lower[k] = pA[k] - (bandA == 0 ? 0.0 : pPrev[k]);
            upper[k] = (pair ? pB[k] : 1.0) - pA[k];
        }
        bandSpectrum_[bandA] = std::move(lower);
        bandSpectrum_[bandA + 1] = std::move(upper);
        if (pair)
            pPrev = pB;
    }
}

UnitDecay BandNoiseGenerator::make(const RoomDecay& decay, std::uint32_t seed,
                                   std::uint32_t emitterStream) const
{
    UnitDecay unit;
    unit.sampleRate = sampleRate_;
    unit.lengthS = tailLengthS(decay);
    unit.bandsT60S = decay.bandsT60S;
    const double fs = sampleRate_;
    const std::size_t length = length_;
    const std::size_t h = half_;
    const std::size_t n = fft_.size();

    std::vector<Complex> spectrum(n, Complex(0.0, 0.0));
    GaussianSource gauss(Pcg32(seed, emitterStream));
    for (std::size_t i = 0; i < length + 2 * h; ++i)
        spectrum[i] = Complex(gauss.next(), 0.0);
    fft_.forward(spectrum);

    std::vector<Complex> work(n);
    for (std::size_t bandA = 0; bandA < contract::kNumOctaveBands; bandA += 2)
    {
        // Two real band signals from one inverse transform: IFFT(X B_a + i X B_b) = y_a + i y_b.
        for (std::size_t k = 0; k < n; ++k)
            work[k] = spectrum[k] * Complex(bandSpectrum_[bandA][k], bandSpectrum_[bandA + 1][k]);
        fft_.inverse(work);
        const double scale = 1.0 / static_cast<double>(n);
        for (std::size_t pair = 0; pair < 2; ++pair)
        {
            const std::size_t b = bandA + pair;
            auto& out = unit.bands[b];
            out.resize(length);
            const double rate = kAmplitudeDecayPerT60 / (decay.bandsT60S[b] * fs);
            double energy = 0.0;
            for (std::size_t j = 0; j < length; ++j)
            {
                const Complex v = work[h + j] * scale;
                const double sample = (pair == 0 ? v.real() : v.imag())
                                      * std::exp(-rate * static_cast<double>(j));
                out[j] = sample;
                energy += sample * sample;
            }
            const double norm = energy > 0.0 ? 1.0 / std::sqrt(energy) : 0.0;
            for (double& v : out)
                v *= norm;
        }
    }
    return unit;
}

UnitDecay makeUnitDecay(const RoomDecay& decay, std::uint32_t seed, std::uint32_t emitterStream,
                        const ism::OctaveFilterbank& filterbank)
{
    const BandNoiseGenerator generator(filterbank,
                                       unitDecayLength(tailLengthS(decay), filterbank.sampleRate()));
    return generator.make(decay, seed, emitterStream);
}

std::vector<EnergyEntry> energyEntries(const ism::ImageSourceSet& set, const contract::BandArray& bandEnergy)
{
    std::vector<EnergyEntry> entries;
    entries.reserve(set.images.size() + set.scattered.size());
    for (const auto& image : set.images)
    {
        EnergyEntry e;
        e.timeS = image.arrivalTimeS;
        e.arrivalDirection = image.arrivalDirection;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            e.bandsEnergy[b] = image.bandsAmplitude[b] * image.bandsAmplitude[b] * bandEnergy[b];
        entries.push_back(e);
    }
    for (const auto& scattered : set.scattered)
    {
        EnergyEntry e;
        e.timeS = scattered.arrivalTimeS;
        e.arrivalDirection = scattered.arrivalDirection;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            e.bandsEnergy[b] = scattered.bandsEnergy[b] * bandEnergy[b];
        entries.push_back(e);
    }
    return entries;
}

double matchWindow(double t, double startS, double endS) noexcept
{
    if (!(t > startS) || !(t < endS))
        return 0.0;
    const double s = std::sin(std::numbers::pi * (t - startS) / (endS - startS));
    return s * s;
}

double expectedUnitEnergyPer10ms(double t60S, double tS, double lengthS) noexcept
{
    const double rate = kEnergyDecayPerT60 / t60S;
    const double total = 1.0 - std::exp(-rate * lengthS);
    if (!(total > 0.0))
        return 0.0;
    return kMatchNormalisationS * rate * std::exp(-rate * tS) / total;
}

TailMatch matchTail(std::span<const EnergyEntry> entries, const MixingTime& mixing, const RoomDecay& decay,
                    double lengthS)
{
    TailMatch match;
    match.mixing = mixing;
    match.expectedSigmaDb = expectedSigmaDb(mixing.expectedKeff);
    const double start = mixing.windowStartS;
    const double end = mixing.mixS;
    const double integralW = 0.5 * (end - start);

    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const double rate = kEnergyDecayPerT60 / decay.bandsT60S[b];
        double sum = 0.0;
        double sumSquares = 0.0;
        double sumEnergy = 0.0;
        std::array<double, 3> axisEnergy{};
        int nonZero = 0;
        for (const auto& entry : entries)
        {
            const double w = matchWindow(entry.timeS, start, end);
            if (w == 0.0 || entry.bandsEnergy[b] == 0.0)
                continue;
            const double x = w * entry.bandsEnergy[b] * std::exp(-rate * (end - entry.timeS));
            sum += x;
            sumSquares += x * x;
            ++nonZero;
            const auto& u = entry.arrivalDirection;
            sumEnergy += entry.bandsEnergy[b];
            axisEnergy[0] += entry.bandsEnergy[b] * u.x * u.x;
            axisEnergy[1] += entry.bandsEnergy[b] * u.y * u.y;
            axisEnergy[2] += entry.bandsEnergy[b] * u.z * u.z;
        }
        match.bandsNonZeroEntries[b] = nonZero;
        match.bandsRealisedKeff[b] = sumSquares > 0.0 ? sum * sum / sumSquares : 0.0;
        match.bandsRealisedSigmaDb[b] = expectedSigmaDb(match.bandsRealisedKeff[b]);
        for (std::size_t k = 0; k < 3; ++k)
            match.bandsAxisShares[b][k] = sumEnergy > 0.0 ? axisEnergy[k] / sumEnergy : 0.0;
        match.bandsTargetEnergy[b] = integralW > 0.0 ? kMatchNormalisationS / integralW * sum : 0.0;
        match.bandsExpectedUnitEnergy[b] = expectedUnitEnergyPer10ms(decay.bandsT60S[b], end, lengthS);
        const double ebar = match.bandsExpectedUnitEnergy[b];
        match.bandsAmplitude[b] = ebar > 0.0 ? std::sqrt(match.bandsTargetEnergy[b] / ebar) : 0.0;
    }
    return match;
}

bool needsIsmFallback(const TailMatch& match) noexcept
{
    for (const std::size_t b : kRealisedKBands)
        if (match.bandsRealisedKeff[b] < kRealisedKMin)
            return true;
    return false;
}

CrossfadeWeights crossfade(double tS, double mixS) noexcept
{
    const double tau = (tS - (mixS - kCrossfadeHalfS)) / (2.0 * kCrossfadeHalfS);
    if (!(tau > 0.0))
        return {1.0, 0.0}; // before the fade: ISM only
    if (!(tau < 1.0))
        return {0.0, 1.0}; // after it: the ISM contributions are dropped
    return {std::cos(0.5 * std::numbers::pi * tau), std::sin(0.5 * std::numbers::pi * tau)};
}

} // namespace sim::tail
