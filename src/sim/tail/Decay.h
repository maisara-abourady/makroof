#pragma once

// Per-band reverberation time of a shoebox room from the Eyring formula with air absorption
// (AQ2, AX4; Vorlaender §4.4.1 Eq. 4.32):
//
//     T60_b = 0.161 V / (-S ln(1 - abar_b) + 4 m_b V)
//
// V = W D H, S = total surface area, abar_b = area-weighted mean absorption of band b (clamped to
// <= 0.999 so ln stays finite), m_b = ENERGY attenuation coefficient of air in 1/m (I = I0 e^(-m x)).
#include "contract/SceneDescription.h"

namespace sim::tail {

// Largest mean absorption the Eyring formula is evaluated at (phase-04 spec): ln(1 - 0.999) = -6.9.
inline constexpr double kMaxMeanAbsorption = 0.999;
// Eyring / Sabine constant in s/m, as in the phase-04 spec (24 ln 10 / c = 0.1611 for c = 343 m/s).
inline constexpr double kEyringConstant = 0.161;

// m = D / (10 log10 e) = D / 4.343: the energy attenuation coefficient (1/m) from a level loss D in
// dB/m (Vorlaender §3.6 Eqs. 3.33-3.35). NOT the pressure coefficient in Np/m (D / 8.686), which
// would halve the 4 m V term of Eyring.
double airEnergyAttenuationPerMetre(double dbPerMetre) noexcept;

struct RoomDecay
{
    double volumeM3 = 0.0;
    double surfaceM2 = 0.0;
    contract::BandArray bandsMeanAbsorption{};    // abar_b, area-weighted, before the clamp
    contract::BandArray bandsAirEnergyPerMetre{}; // m_b (1/m); 0 without air absorption
    contract::BandArray bandsT60S{};              // Eyring T60_b (s)

    // Largest T60_b (the slowest band).
    double maxT60S() const noexcept;
};

// Eyring decay of a shoebox room. airAbsorption = false (validation only, AX4) sets m_b = 0.
// Expose for tests and UI display.
RoomDecay eyringDecay(const contract::Room& room, bool airAbsorption = true);

} // namespace sim::tail
