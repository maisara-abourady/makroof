// sim::tail::eyringDecay: Eyring T60 per band with air absorption (phase-04 scope 1).
#include "ContractFixtures.h"
#include "contract/Parse.h"
#include "sim/AirAbsorption.h"
#include "sim/tail/Decay.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <cmath>

// Exact floating-point comparisons are intended here (determinism, exact zeros, values copied
// unchanged), so -Wfloat-equal (part of JUCE's recommended warnings, which the tests compile with
// when the plugin is built) is silenced for this file, as in contract/SceneDescription.h.
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

using Catch::Matchers::WithinRel;

namespace {

contract::Room uniformRoom(double w, double d, double h, double alpha)
{
    contract::Room room;
    room.geometry.dimensions = {w, d, h};
    for (auto& s : room.surfaces)
    {
        s.bandsAbsorption.fill(alpha);
        s.scattering = 0.0;
    }
    return room;
}

} // namespace

TEST_CASE("m_b is the energy attenuation coefficient D / 4.343, checked against ISO 9613-1", "[sim][tail]")
{
    // ISO 9613-2:1996 Table 2 (computed with ISO 9613-1), 20 degC, 70 % RH: 9.0 dB/km at 2 kHz,
    // rounded to 0.1 dB/km (the table test_air_absorption.cpp checks the formula against).
    const double dbPerMetre = sim::airAttenuationDbPerMetre(2000.0, 20.0, 70.0);
    CHECK(std::abs(dbPerMetre * 1000.0 - 9.0) <= 0.05 + 1e-9);
    const double m = sim::tail::airEnergyAttenuationPerMetre(dbPerMetre);
    // I(x) = I0 e^(-m x) loses 10 log10(e^(-m)) = -4.343 m dB per metre.
    CHECK_THAT(10.0 * std::log10(std::exp(-m)), WithinRel(-dbPerMetre, 1e-12));
    CHECK_THAT(m, WithinRel(dbPerMetre / 4.3429448190325175, 1e-12));
    // Not the pressure coefficient in Np/m (D / 8.686), which is half of it.
    CHECK_THAT(m, WithinRel(2.0 * dbPerMetre / 8.685889638065035, 1e-12));
}

TEST_CASE("Eyring T60 per band: hand-computed value with and without air", "[sim][tail]")
{
    const auto room = uniformRoom(20.0, 30.0, 10.0, 0.2);
    const double v = 6000.0, s = 2.0 * (600.0 + 200.0 + 300.0);
    const auto noAir = sim::tail::eyringDecay(room, false);
    CHECK_THAT(noAir.volumeM3, WithinRel(v, 1e-15));
    CHECK_THAT(noAir.surfaceM2, WithinRel(s, 1e-15));
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        CHECK(noAir.bandsAirEnergyPerMetre[b] == 0.0);
        CHECK_THAT(noAir.bandsT60S[b], WithinRel(0.161 * v / (-s * std::log(0.8)), 1e-12));
    }
    const auto withAir = sim::tail::eyringDecay(room, true);
    const auto airDb = sim::bandsAirAttenuationDbPerMetre();
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const double m = airDb[b] / (10.0 / std::log(10.0));
        CHECK_THAT(withAir.bandsT60S[b], WithinRel(0.161 * v / (-s * std::log(0.8) + 4.0 * m * v), 1e-12));
        CHECK(withAir.bandsT60S[b] < noAir.bandsT60S[b]);
    }
    // Phase-04 spec note: the energy coefficient matters, ~8 % at 4 kHz in this room.
    const double m4k = airDb[6] / (10.0 / std::log(10.0));
    const double tPressure = 0.161 * v / (-s * std::log(0.8) + 2.0 * m4k * v);
    CHECK(tPressure / withAir.bandsT60S[6] > 1.03);
}

TEST_CASE("Eyring: area-weighted mean absorption and the 0.999 clamp", "[sim][tail]")
{
    auto room = uniformRoom(4.0, 5.0, 3.0, 0.1);
    room.surface(contract::SurfaceId::ceiling).bandsAbsorption.fill(0.7); // 20 m^2 of 94 m^2
    const auto d = sim::tail::eyringDecay(room, false);
    CHECK_THAT(d.bandsMeanAbsorption[3], WithinRel((74.0 * 0.1 + 20.0 * 0.7) / 94.0, 1e-12));

    const auto open = sim::tail::eyringDecay(uniformRoom(10.0, 10.0, 10.0, 1.0), false);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        REQUIRE(std::isfinite(open.bandsT60S[b]));
        CHECK_THAT(open.bandsT60S[b], WithinRel(0.161 * 1000.0 / (-600.0 * std::log(0.001)), 1e-12));
    }
}

TEST_CASE("Eyring T60 of the six Phase 04 test rooms spans about 0.2 s to about 6 s", "[sim][tail]")
{
    double shortest = 1e9, longest = 0.0;
    for (const char* name :
         {"dead_booth", "living_room", "classroom", "club", "concert_hall_box", "stone_box"})
    {
        const auto parsed = contract::parseScene(contract_fixtures::read(
            contract_fixtures::scenesDir() / "valid" / (std::string(name) + ".json")));
        REQUIRE(parsed.ok());
        const auto d = sim::tail::eyringDecay(parsed.scene->room);
        const double mid = 0.5 * (d.bandsT60S[3] + d.bandsT60S[4]); // 500 Hz / 1 kHz
        shortest = std::min(shortest, mid);
        longest = std::max(longest, mid);
    }
    CHECK(shortest < 0.25);
    CHECK(longest > 5.0);
}

TEST_CASE("AirAbsorption matches Kuttruff Table 6.1 (Bass 1995) at 20 degC within 1 %", "[sim][tail][air]")
{
    // Phase-04 scope 1: Kuttruff, Room Acoustics, Table 6.1, intensity attenuation constant m in
    // 10^-3 1/m at 20 degC, normal pressure (adapted from Bass et al., JASA 97, 680, 1995). The table
    // prints two decimals (rounding up to ~0.8 % at 0.5 kHz); the tolerance stays +-1 %.
    struct Row
    {
        double humidityPercent;
        std::array<double, 7> m1e3;
    };
    constexpr std::array<double, 7> kHz{500.0, 1000.0, 2000.0, 3000.0, 4000.0, 6000.0, 8000.0};
    constexpr std::array<Row, 3> table{{
        {40.0, {0.60, 1.07, 2.58, 5.03, 8.40, 17.71, 30.00}},
        {50.0, {0.63, 1.08, 2.28, 4.20, 6.84, 14.26, 24.29}},
        {70.0, {0.64, 1.15, 2.08, 3.45, 5.32, 10.62, 17.91}},
    }};
    for (const auto& row : table)
        for (std::size_t i = 0; i < kHz.size(); ++i)
        {
            const double m = sim::tail::airEnergyAttenuationPerMetre(
                sim::airAttenuationDbPerMetre(kHz[i], 20.0, row.humidityPercent));
            INFO(row.humidityPercent << " % RH, " << kHz[i] << " Hz: m = " << m * 1e3 << "e-3 1/m, table "
                                     << row.m1e3[i]);
            CHECK_THAT(m * 1e3, WithinRel(row.m1e3[i], 0.01));
        }
}

TEST_CASE("Atmosphere override (AX4 validation only): the AX4 values reproduce the default exactly",
          "[sim][tail][air]")
{
    const auto room = uniformRoom(20.0, 30.0, 10.0, 0.2);
    const auto ax4 = sim::tail::eyringDecay(room, true);
    const auto same = sim::tail::eyringDecay(
        room, sim::bandsAirAttenuationDbPerMetre(sim::kAirTemperatureC, sim::kAirRelativeHumidityPercent));
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        CHECK(same.bandsT60S[b] == ax4.bandsT60S[b]);
    // Drier air absorbs more at 8 kHz at 20 degC (Kuttruff Table 6.1: 40 % > 50 % > 70 % RH there).
    const auto dry = sim::tail::eyringDecay(room, sim::bandsAirAttenuationDbPerMetre(20.0, 40.0));
    const auto humid = sim::tail::eyringDecay(room, sim::bandsAirAttenuationDbPerMetre(20.0, 70.0));
    const std::size_t b8k = contract::kNumOctaveBands - 1;
    CHECK(dry.bandsT60S[b8k] < ax4.bandsT60S[b8k]);
    CHECK(humid.bandsT60S[b8k] > ax4.bandsT60S[b8k]);
}
