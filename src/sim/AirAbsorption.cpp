#include "sim/AirAbsorption.h"

#include <cmath>

namespace sim {

double airAttenuationDbPerMetre(double frequencyHz, double temperatureC, double relativeHumidityPercent,
                                double pressureKPa) noexcept
{
    constexpr double kReferencePressureKPa = 101.325; // p_r
    constexpr double kReferenceTemperatureK = 293.15; // T_0 (20 degC)
    constexpr double kTriplePointK = 273.16;          // T_01

    const double t = temperatureC + 273.15;
    const double pRel = pressureKPa / kReferencePressureKPa;
    const double tRel = t / kReferenceTemperatureK;

    // Molar concentration of water vapour h in percent (ISO 9613-1 Annex B).
    const double c = -6.8346 * std::pow(kTriplePointK / t, 1.261) + 4.6151;
    const double h = relativeHumidityPercent * std::pow(10.0, c) / pRel;

    // Relaxation frequencies of oxygen and nitrogen (eq. (3), (4)).
    const double frO = pRel * (24.0 + 4.04e4 * h * (0.02 + h) / (0.391 + h));
    const double frN = pRel * std::pow(tRel, -0.5)
                       * (9.0 + 280.0 * h * std::exp(-4.170 * (std::pow(tRel, -1.0 / 3.0) - 1.0)));

    const double f2 = frequencyHz * frequencyHz;
    const double classical = 1.84e-11 / pRel * std::sqrt(tRel);
    const double relaxation = std::pow(tRel, -2.5)
                              * (0.01275 * std::exp(-2239.1 / t) / (frO + f2 / frO)
                                 + 0.1068 * std::exp(-3352.0 / t) / (frN + f2 / frN));
    return 8.686 * f2 * (classical + relaxation); // eq. (5), dB/m
}

contract::BandArray bandsAirAttenuationDbPerMetre() noexcept
{
    contract::BandArray bands{};
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        bands[b] = airAttenuationDbPerMetre(contract::kOctaveBandsHz[b]);
    return bands;
}

contract::BandArray bandsAirAttenuationDbPerMetre(double temperatureC,
                                                  double relativeHumidityPercent) noexcept
{
    contract::BandArray bands{};
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        bands[b] = airAttenuationDbPerMetre(contract::kOctaveBandsHz[b], temperatureC,
                                            relativeHumidityPercent);
    return bands;
}

contract::BandArray bandsAirAmplitude(const contract::BandArray& bandsDbPerMetre, double distanceM) noexcept
{
    contract::BandArray amplitude{};
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        amplitude[b] = std::pow(10.0, -bandsDbPerMetre[b] * distanceM / 20.0);
    return amplitude;
}

} // namespace sim
