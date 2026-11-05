#pragma once

// Atmospheric absorption of sound, ISO 9613-1:1993 (pure-tone attenuation coefficient, eq. (3)-(5)
// with the saturation vapour pressure of its Annex B). AX4: the Simulator always uses the fixed
// standard atmosphere below; users can't change it.
#include "contract/SceneDescription.h"

namespace sim {

// AX4: 20 degC, 50 % relative humidity, 101.325 kPa.
inline constexpr double kAirTemperatureC = 20.0;
inline constexpr double kAirRelativeHumidityPercent = 50.0;
inline constexpr double kAirPressureKPa = 101.325;

// Attenuation coefficient in dB per metre of a pure tone at `frequencyHz`. Valid (per the
// standard) for 50 Hz - 10 kHz, -20 to +50 degC, 10 - 100 % RH, pressures below 200 kPa; it
// returns the formula's value outside that range too.
double airAttenuationDbPerMetre(double frequencyHz, double temperatureC = kAirTemperatureC,
                                double relativeHumidityPercent = kAirRelativeHumidityPercent,
                                double pressureKPa = kAirPressureKPa) noexcept;

// AX4 atmosphere, evaluated at the nominal band centres contract::kOctaveBandsHz.
contract::BandArray bandsAirAttenuationDbPerMetre() noexcept;

// Pressure-amplitude factor of air absorption over `distanceM` metres per band:
// 10^(-a_b * r / 20).
contract::BandArray bandsAirAmplitude(const contract::BandArray& bandsDbPerMetre, double distanceM) noexcept;

} // namespace sim
