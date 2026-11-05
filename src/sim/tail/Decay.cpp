#include "sim/tail/Decay.h"

#include "sim/AirAbsorption.h"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace sim::tail {

double airEnergyAttenuationPerMetre(double dbPerMetre) noexcept
{
    // 10 log10(e) = 10 / ln 10 = 4.3429 dB per neper of energy.
    return dbPerMetre * std::numbers::ln10 / 10.0;
}

double RoomDecay::maxT60S() const noexcept
{
    return *std::max_element(bandsT60S.begin(), bandsT60S.end());
}

RoomDecay eyringDecay(const contract::Room& room, bool airAbsorption)
{
    const auto& d = room.geometry.dimensions;
    // Surface areas by contract::surfaceIndex: xMin, xMax (D x H), yMin, yMax (W x H), floor,
    // ceiling (W x D).
    const std::array<double, contract::kNumSurfaces> areas{d.y * d.z, d.y * d.z, d.x * d.z,
                                                           d.x * d.z, d.x * d.y, d.x * d.y};
    RoomDecay decay;
    decay.volumeM3 = d.x * d.y * d.z;
    decay.surfaceM2 = 0.0;
    for (const double a : areas)
        decay.surfaceM2 += a;

    contract::BandArray airDb{};
    if (airAbsorption)
        airDb = bandsAirAttenuationDbPerMetre();

    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        double weighted = 0.0;
        for (std::size_t s = 0; s < contract::kNumSurfaces; ++s)
            weighted += areas[s] * room.surfaces[s].bandsAbsorption[b];
        const double mean = weighted / decay.surfaceM2;
        decay.bandsMeanAbsorption[b] = mean;
        const double m = airEnergyAttenuationPerMetre(airDb[b]);
        decay.bandsAirEnergyPerMetre[b] = m;
        const double clamped = std::min(mean, kMaxMeanAbsorption);
        decay.bandsT60S[b] = kEyringConstant * decay.volumeM3
                             / (-decay.surfaceM2 * std::log(1.0 - clamped) + 4.0 * m * decay.volumeM3);
    }
    return decay;
}

} // namespace sim::tail
