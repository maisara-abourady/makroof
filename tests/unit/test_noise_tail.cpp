// sim::tail::NoiseTail (phase-04 scope 3): the unit decay, the energy matching and the crossfade.
#include "sim/ism/BandRenderer.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>

// Exact floating-point comparisons are intended here (determinism, exact zeros, values copied
// unchanged), so -Wfloat-equal (part of JUCE's recommended warnings, which the tests compile with
// when the plugin is built) is silenced for this file, as in contract/SceneDescription.h.
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

namespace {

sim::tail::RoomDecay decayWith(contract::BandArray t60)
{
    sim::tail::RoomDecay d;
    d.volumeM3 = 400.0;
    d.surfaceM2 = 340.0;
    d.bandsT60S = t60;
    return d;
}

double sumSquares(const std::vector<double>& x, std::size_t from, std::size_t to)
{
    double s = 0.0;
    for (std::size_t i = from; i < to && i < x.size(); ++i)
        s += x[i] * x[i];
    return s;
}

double sumSquares(const std::vector<double>& x)
{
    return sumSquares(x, 0, x.size());
}

} // namespace

TEST_CASE("tail length: 1.5 T60 of the slowest band (90 dB), capped at 12 s", "[sim][tail]")
{
    CHECK_THAT(sim::tail::tailLengthS(decayWith({1.0, 2.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5})),
               WithinRel(3.0, 1e-15));
    CHECK(sim::tail::tailLengthS(decayWith({20.0, 2.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5})) == 12.0);
}

TEST_CASE("unit decay: unit energy per band, exp(-6.91 t / T60) envelope, deterministic", "[sim][tail]")
{
    const double fs = 48000.0;
    const sim::ism::OctaveFilterbank fb(fs);
    const auto decay = decayWith({0.9, 0.8, 0.7, 0.6, 0.5, 0.45, 0.4, 0.3});
    const auto unit = sim::tail::makeUnitDecay(decay, 12345u, 0u, fb);
    REQUIRE(unit.length() == static_cast<std::size_t>(std::ceil(1.35 * fs)));
    CHECK(unit.lengthS == 1.5 * 0.9);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        INFO("band " << b);
        CHECK_THAT(sumSquares(unit.bands[b]), WithinRel(1.0, 1e-12));
        // Energy in [0.1, 0.2) s vs [0.3, 0.4) s: 60 dB per T60 (a noise estimate, so loose).
        const auto e1 = sumSquares(unit.bands[b], 4800, 9600);
        const auto e2 = sumSquares(unit.bands[b], 14400, 19200);
        const double measuredDb = 10.0 * std::log10(e1 / e2);
        const double expectedDb = 60.0 * 0.2 / decay.bandsT60S[b];
        CHECK_THAT(measuredDb, WithinAbs(expectedDb, b == 0 ? 6.0 : 3.0));
    }
    const auto again = sim::tail::makeUnitDecay(decay, 12345u, 0u, fb);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        CHECK(again.bands[b] == unit.bands[b]);
    // A different seed or stream gives different noise.
    const auto otherSeed = sim::tail::makeUnitDecay(decay, 12346u, 0u, fb);
    const auto otherStream = sim::tail::makeUnitDecay(decay, 12345u, 1u, fb);
    CHECK(otherSeed.bands[4] != unit.bands[4]);
    CHECK(otherStream.bands[4] != unit.bands[4]);
}

TEST_CASE("unit decay: each band's energy lies in its own octave (same filterbank as Phase 03)",
          "[sim][tail]")
{
    const double fs = 48000.0;
    const sim::ism::OctaveFilterbank fb(fs);
    const auto unit = sim::tail::makeUnitDecay(decayWith({2, 2, 2, 2, 2, 2, 2, 2}), 7u, 0u, fb);
    // Band 4 (1 kHz) filtered again by its own band filter keeps its energy; band filters of
    // two octaves away keep almost nothing (stop band 80 dB).
    const auto apply = [&](const std::vector<double>& x, std::size_t band) {
        const auto h = fb.bandImpulseResponse(band);
        const std::size_t half = h.size() / 2;
        std::vector<double> y(x.size(), 0.0);
        for (std::size_t n = 0; n < x.size(); n += 1) // direct convolution on a short excerpt
        {
            if (n < 20000 || n >= 22000)
                continue;
            double s = 0.0;
            for (std::size_t k = 0; k < h.size(); ++k)
            {
                const std::ptrdiff_t i = static_cast<std::ptrdiff_t>(n + half)
                                         - static_cast<std::ptrdiff_t>(k);
                if (i >= 0 && i < static_cast<std::ptrdiff_t>(x.size()))
                    s += h[k] * x[static_cast<std::size_t>(i)];
            }
            y[n] = s;
        }
        return sumSquares(y, 20000, 22000) / sumSquares(x, 20000, 22000);
    };
    CHECK(apply(unit.bands[4], 4) > 0.95);
    CHECK(apply(unit.bands[4], 2) < 1e-6);
    CHECK(apply(unit.bands[4], 6) < 1e-6);
}

TEST_CASE("band impulse energies: the band filters' energies, which sum to about 1", "[sim][tail]")
{
    for (const double fs : {44100.0, 96000.0})
    {
        const sim::ism::OctaveFilterbank fb(fs);
        const auto g = sim::tail::bandImpulseEnergies(fb);
        double sum = 0.0;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            CHECK(g[b] > 0.0);
            sum += g[b];
        }
        // The band filters sum to a delta, but in each +-1/8-octave crossover |B_k|^2 + |B_k+1|^2 < 1,
        // so the energies sum to a little less than 1 (measured 0.983).
        CHECK(sum < 1.0);
        CHECK(sum > 0.97);
        // An octave band holds about its share of the spectrum, 1 kHz band [707, 1414] Hz of
        // [0, fs / 2], less the crossover losses (measured 5 % below).
        CHECK(g[4] < 707.1 / (fs / 2.0));
        CHECK_THAT(g[4], WithinRel(707.1 / (fs / 2.0), 0.08));
    }
}

TEST_CASE("expected unit energy per 10 ms matches the realisations on average", "[sim][tail]")
{
    const double fs = 48000.0;
    const sim::ism::OctaveFilterbank fb(fs);
    const auto decay = decayWith({1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0});
    const double t = 0.08;
    double mean = 0.0;
    constexpr int kRealisations = 40;
    for (std::uint32_t seed = 0; seed < kRealisations; ++seed)
    {
        const auto unit = sim::tail::makeUnitDecay(decay, seed, 0u, fb);
        mean += sumSquares(unit.bands[5], static_cast<std::size_t>((t - 0.005) * fs),
                           static_cast<std::size_t>((t + 0.005) * fs));
    }
    mean /= kRealisations;
    const double expected = sim::tail::expectedUnitEnergyPer10ms(1.0, t, 1.5);
    CHECK_THAT(mean, WithinRel(expected, 0.05));
    // Closed form: 0.01 (13.82 / T) e^(-13.82 t / T) / (1 - e^(-13.82 L / T)).
    const double r = 6.0 * std::log(10.0);
    CHECK_THAT(expected, WithinRel(0.01 * r * std::exp(-r * t) / (1.0 - std::exp(-r * 1.5)), 1e-12));
}

TEST_CASE("matchWindow is the Hann taper over [start, end], zero outside", "[sim][tail]")
{
    CHECK(sim::tail::matchWindow(0.010, 0.010, 0.030) == 0.0);
    CHECK(sim::tail::matchWindow(0.030, 0.010, 0.030) == 0.0);
    CHECK(sim::tail::matchWindow(0.005, 0.010, 0.030) == 0.0);
    CHECK_THAT(sim::tail::matchWindow(0.020, 0.010, 0.030), WithinAbs(1.0, 1e-15));
    CHECK_THAT(sim::tail::matchWindow(0.015, 0.010, 0.030), WithinAbs(0.5, 1e-15));
}

TEST_CASE("matchTail: hand-computed E_target, E_b from the expected unit energy", "[sim][tail]")
{
    const auto decay = decayWith({1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0});
    sim::tail::MixingTime mt;
    mt.directS = 0.010;
    mt.windowStartS = 0.0125;
    mt.mixS = 0.0325;
    mt.expectedKeff = 25.0;
    std::vector<sim::tail::EnergyEntry> entries;
    const auto entry = [&](double t, double e) {
        sim::tail::EnergyEntry x;
        x.timeS = t;
        x.bandsEnergy.fill(e);
        entries.push_back(x);
    };
    entry(0.010, 100.0); // the direct sound: outside the window
    entry(0.0115, 50.0); // an early reflection before the window start
    entry(0.0225, 2.0);  // window centre, w = 1
    entry(0.0175, 1.0);  // w = 0.5
    entry(0.0400, 9.0);  // after t_mix (in the AX20 list until t_mix + 2.5 ms): outside
    const auto m = sim::tail::matchTail(entries, mt, decay, 1.5);
    const double r = 6.0 * std::log(10.0);
    const double sum = 1.0 * 2.0 * std::exp(-r * 0.010) + 0.5 * 1.0 * std::exp(-r * 0.015);
    const double target = 0.010 / (0.5 * 0.020) * sum;
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        CHECK_THAT(m.bandsTargetEnergy[b], WithinRel(target, 1e-12));
        CHECK(m.bandsNonZeroEntries[b] == 2);
        const double ebar = sim::tail::expectedUnitEnergyPer10ms(1.0, 0.0325, 1.5);
        CHECK_THAT(m.bandsExpectedUnitEnergy[b], WithinRel(ebar, 1e-12));
        CHECK_THAT(m.bandsAmplitude[b] * m.bandsAmplitude[b] * ebar, WithinRel(target, 1e-12));
        const double x1 = 2.0 * std::exp(-r * 0.010), x2 = 0.5 * std::exp(-r * 0.015);
        CHECK_THAT(m.bandsRealisedKeff[b], WithinRel((x1 + x2) * (x1 + x2) / (x1 * x1 + x2 * x2), 1e-12));
    }
    CHECK_THAT(m.expectedSigmaDb, WithinRel(10.0 / std::log(10.0) / 5.0, 1e-12));
}

TEST_CASE("matchTail: no entry in the window gives E_b = 0", "[sim][tail]")
{
    const auto decay = decayWith({0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2});
    const auto mt = sim::tail::mixingTime(0.1, 300000.0);
    std::vector<sim::tail::EnergyEntry> entries(2);
    entries[0].timeS = 0.1;
    entries[0].bandsEnergy.fill(1.0);
    entries[1].timeS = 0.1014; // 1.4 ms after the direct sound (the open_field floor reflection)
    entries[1].bandsEnergy.fill(0.3);
    const auto m = sim::tail::matchTail(entries, mt, decay, 0.3);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        CHECK(m.bandsAmplitude[b] == 0.0);
        CHECK(m.bandsNonZeroEntries[b] == 0);
    }
}

TEST_CASE("crossfade is equal-power over [t_mix - 2.5 ms, t_mix + 2.5 ms] (AX18)", "[sim][tail]")
{
    const double mix = 0.05;
    const auto before = sim::tail::crossfade(mix - 0.0026, mix);
    CHECK(before.ism == 1.0);
    CHECK(before.tail == 0.0);
    const auto after = sim::tail::crossfade(mix + 0.0025, mix);
    CHECK(after.ism == 0.0);
    CHECK(after.tail == 1.0);
    for (double t = mix - 0.0025; t <= mix + 0.0025; t += 0.0001)
    {
        const auto w = sim::tail::crossfade(t, mix);
        CHECK_THAT(w.ism * w.ism + w.tail * w.tail, WithinAbs(1.0, 1e-12));
    }
    const auto middle = sim::tail::crossfade(mix, mix);
    CHECK_THAT(middle.ism, WithinAbs(std::sqrt(0.5), 1e-12));
    CHECK_THAT(middle.tail, WithinAbs(std::sqrt(0.5), 1e-12));
}

TEST_CASE("per-output seed offset for Phase 08", "[sim][tail]")
{
    CHECK(sim::tail::tailSeedForOutput(12345u, 0) == 12345u);
    CHECK(sim::tail::tailSeedForOutput(12345u, 1) == (12345u ^ 0x9E3779B9u));
}

TEST_CASE("energy entries: an image's band energy is a_b^2 times the band filter's energy", "[sim][tail]")
{
    // The units of the matching (phase-04 scope 3): render one image with per-band amplitudes,
    // band-filter the result with the filterbank's own band filter, and compare its energy with the
    // specular entry of energyEntries().
    const double fs = 48000.0;
    const sim::ism::OctaveFilterbank fb(fs);
    const auto g = sim::tail::bandImpulseEnergies(fb);
    sim::ism::ImageSourceSet set;
    sim::ism::ImageSource image;
    image.arrivalTimeS = 0.05 + 0.3 / fs; // a fractional delay
    image.bandsAmplitude = {0.1, 0.2, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05};
    set.images.push_back(image);
    sim::ism::ScatteredEnergy scattered;
    scattered.arrivalTimeS = image.arrivalTimeS;
    scattered.bandsEnergy.fill(0.01);
    set.scattered.push_back(scattered);
    const auto entries = sim::tail::energyEntries(set, g);
    REQUIRE(entries.size() == 2);
    const auto ir = sim::ism::renderImageSources(set.images, 0.0, fb);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const auto h = fb.bandImpulseResponse(b);
        const std::size_t half = h.size() / 2;
        double e = 0.0;
        for (std::size_t n = 0; n < ir.size(); ++n)
        {
            double s = 0.0;
            for (std::size_t k = 0; k < h.size(); ++k)
            {
                const auto i = static_cast<std::ptrdiff_t>(n + half) - static_cast<std::ptrdiff_t>(k);
                if (i >= 0 && i < static_cast<std::ptrdiff_t>(ir.size()))
                    s += h[k] * ir[static_cast<std::size_t>(i)];
            }
            e += s * s;
        }
        INFO("band " << b);
        // Neighbouring bands' amplitudes leak a little through the crossovers.
        CHECK_THAT(e, WithinRel(entries[0].bandsEnergy[b], 0.05));
        CHECK_THAT(entries[0].bandsEnergy[b],
                   WithinRel(image.bandsAmplitude[b] * image.bandsAmplitude[b] * g[b], 1e-12));
        CHECK_THAT(entries[1].bandsEnergy[b], WithinRel(0.01 * g[b], 1e-12));
        CHECK(entries[1].timeS == image.arrivalTimeS);
    }
}

// Phase-07c-1 decision loop (K15; Seats 1, 3, 9: the AX49 provisional tail): the cost of the unit-decay
// synthesis (constructor + make, one emitter) at a prefix length L_p = 0.31 T60_max + 0.1 s (the EDT-within-5
// % bound for a truncated exponential, plus the fade) against the full length, for T60_max = 2, 8 and 12 s at
// 48 and 96 kHz. A record (printed, never asserted).
TEST_CASE("records: provisional-tail synthesis cost at L_p = 0.31 T60 + 0.1 s vs the full tail",
          "[.][benchmark][provisional-cost]")
{
    using Clock = std::chrono::steady_clock;
    for (const double fs : {48000.0, 96000.0})
    {
        const sim::ism::OctaveFilterbank filterbank(fs);
        for (const double t60 : {2.0, 8.0, 12.0})
        {
            sim::tail::RoomDecay decay;
            decay.bandsT60S.fill(t60);
            const double full = sim::tail::tailLengthS(decay);
            const double prefix = std::min(full, 0.31 * t60 + 0.1);
            double msFull = 0.0, msPrefix = 0.0;
            for (const double len : {full, prefix})
            {
                const auto t0 = Clock::now();
                const sim::tail::BandNoiseGenerator gen(filterbank, sim::tail::unitDecayLength(len, fs));
                const auto unit = gen.make(decay, 1u, 0u);
                const double msTaken = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
                (len == full ? msFull : msPrefix) = msTaken;
                REQUIRE(unit.length() > 0);
            }
            std::printf(
                "07c1-records provisional cost %6.0f Hz, T60 %4.1f s: full tail %.2f s -> %.0f ms; prefix "
                "L_p %.2f s -> %.0f ms (one emitter: constructor + make)\n",
                fs, t60, full, msFull, prefix, msPrefix);
        }
    }
}
