#pragma once

// Helpers shared by the ISM / band-renderer / engine tests: random valid rooms and positions.
#include "contract/SceneDescription.h"

#include <algorithm>
#include <cmath>
#include <random>
#include <utility>

namespace ism_test {

inline double uniform(std::mt19937_64& rng, double lo, double hi)
{
    return std::uniform_real_distribution<double>(lo, hi)(rng);
}

// A random shoebox (AX6 limits) with random per-band absorption and scattering.
inline contract::Room randomRoom(std::mt19937_64& rng, double minSize = 1.5, double maxSize = 40.0)
{
    contract::Room room;
    room.geometry.dimensions = {uniform(rng, minSize, maxSize), uniform(rng, minSize, maxSize),
                                uniform(rng, minSize, std::min(maxSize, 20.0))};
    for (auto& surface : room.surfaces)
    {
        for (double& a : surface.bandsAbsorption)
            a = uniform(rng, 0.01, 0.99);
        surface.scattering = uniform(rng, 0.0, 0.9);
    }
    return room;
}

// A point at least `clearance` from every wall.
inline contract::Vec3 randomPoint(std::mt19937_64& rng, const contract::Room& room, double clearance = 0.1)
{
    const auto& d = room.geometry.dimensions;
    return {uniform(rng, clearance, d.x - clearance), uniform(rng, clearance, d.y - clearance),
            uniform(rng, clearance, d.z - clearance)};
}

inline double distance(const contract::Vec3& a, const contract::Vec3& b)
{
    const double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Source and listener at least 0.3 m apart (AX6).
inline std::pair<contract::Vec3, contract::Vec3> randomPair(std::mt19937_64& rng, const contract::Room& room)
{
    for (;;)
    {
        const auto s = randomPoint(rng, room);
        const auto l = randomPoint(rng, room);
        if (distance(s, l) >= 0.3)
            return {s, l};
    }
}

} // namespace ism_test
