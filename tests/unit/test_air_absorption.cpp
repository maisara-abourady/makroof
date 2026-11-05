// sim::airAttenuationDbPerMetre (ISO 9613-1) against published table values.
#include "sim/AirAbsorption.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <array>
#include <cmath>

namespace {

// Exact (base-10) mid-band frequencies of the octave bands 63 Hz ... 8 kHz, as the ISO tables use.
constexpr std::array<double, 8> kExactMidbandHz{63.0957, 125.893, 251.189, 501.187,
                                                1000.0,  1995.26, 3981.07, 7943.28};

struct TableRow
{
    double temperatureC;
    double humidityPercent;
    std::array<double, 8> dbPerKm;
};

// ISO 9613-2:1996 Table 2, "Atmospheric attenuation coefficient alpha for octave bands of noise",
// dB/km, 101.325 kPa. Those values are computed with ISO 9613-1:1993 (the same equations) and
// rounded to 0.1 dB/km below 10 dB/km. ISO 9613-1 Table 1 itself (which has the 20 degC / 50 %
// row of AX4) is not freely available, so the AX4 row is pinned separately below.
constexpr std::array<TableRow, 6> kIso9613Part2Table2{{
    {10.0, 70.0, {0.1, 0.4, 1.0, 1.9, 3.7, 9.7, 32.8, 117.0}},
    {20.0, 70.0, {0.1, 0.3, 1.1, 2.8, 5.0, 9.0, 22.9, 76.6}},
    {30.0, 70.0, {0.1, 0.3, 1.0, 3.1, 7.4, 12.7, 23.1, 59.3}},
    {15.0, 20.0, {0.3, 0.6, 1.2, 2.7, 8.2, 28.2, 88.8, 202.0}},
    {15.0, 50.0, {0.1, 0.5, 1.2, 2.2, 4.2, 10.8, 36.2, 129.0}},
    {15.0, 80.0, {0.1, 0.3, 1.1, 2.4, 4.1, 8.3, 23.7, 82.8}},
}};

} // namespace

TEST_CASE("air absorption matches the ISO 9613 octave-band table within 5 %", "[sim][air]")
{
    for (const auto& row : kIso9613Part2Table2)
    {
        for (std::size_t b = 0; b < kExactMidbandHz.size(); ++b)
        {
            const double expected = row.dbPerKm[b];
            const double actual = 1000.0
                                  * sim::airAttenuationDbPerMetre(kExactMidbandHz[b], row.temperatureC,
                                                                  row.humidityPercent);
            // 5 % of the value (phase-03 criterion), but never less than the table's rounding
            // (half a unit of the last digit: 0.05 below 10 dB/km, 0.5 above 100 dB/km).
            const double rounding = expected < 10.0 ? 0.05 : (expected < 100.0 ? 0.05 : 0.5);
            const double tolerance = std::max(0.05 * expected, rounding) + 1e-9;
            INFO(row.temperatureC << " degC " << row.humidityPercent << " % RH, " << kExactMidbandHz[b]
                                  << " Hz: table " << expected << ", computed " << actual << " dB/km");
            CHECK(std::abs(actual - expected) <= tolerance);
        }
    }
}

TEST_CASE("AX4 atmosphere: 20 degC, 50 % RH at the nominal band centres", "[sim][air]")
{
    // Computed with an independent implementation of ISO 9613-1 eq. (3)-(5) and Annex B
    // (tools/acoustics/air.py, which tools/acoustics/tests/test_air.py checks against the same
    // table), dB/km at 63, 125, ..., 8000 Hz.
    constexpr std::array<double, 8> expected{0.1225, 0.4398, 1.3097,  2.7281,
                                             4.6647, 9.8870, 29.6655, 105.2909};
    const auto bands = sim::bandsAirAttenuationDbPerMetre();
    for (std::size_t b = 0; b < expected.size(); ++b)
        CHECK_THAT(bands[b] * 1000.0, Catch::Matchers::WithinRel(expected[b], 1e-3));
}

TEST_CASE("air amplitude factor is 10^(-a r / 20)", "[sim][air]")
{
    const auto db = sim::bandsAirAttenuationDbPerMetre();
    const auto zero = sim::bandsAirAmplitude(db, 0.0);
    const auto km = sim::bandsAirAmplitude(db, 1000.0);
    for (std::size_t b = 0; b < db.size(); ++b)
    {
        CHECK_THAT(zero[b], Catch::Matchers::WithinULP(1.0, 0));
        CHECK_THAT(20.0 * std::log10(km[b]), Catch::Matchers::WithinAbs(-1000.0 * db[b], 1e-9));
    }
    // Higher bands lose more.
    for (std::size_t b = 1; b < db.size(); ++b)
        CHECK(db[b] > db[b - 1]);
}
