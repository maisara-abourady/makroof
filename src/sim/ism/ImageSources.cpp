#include "sim/ism/ImageSources.h"

#include "sim/AirAbsorption.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

namespace sim::ism {

namespace {

using contract::BandArray;
using contract::kNumOctaveBands;
using contract::kNumSurfaces;
using contract::SurfaceId;
using contract::surfaceIndex;
using contract::Vec3;

// One image coordinate along one axis.
struct AxisImage
{
    double coordinate = 0.0;
    double emissionSign = 1.0; // -1 when the axis is mirrored an odd number of times (p = 1)
    int hitsMin = 0;
    int hitsMax = 0;
    int order() const noexcept { return hitsMin + hitsMax; }
};

std::vector<AxisImage> axisImages(double size, double source, int maxOrder)
{
    std::vector<AxisImage> out;
    // The order of (n, p) is |n - p| + |n|, so |n| <= (maxOrder + 1) / 2 covers every image.
    const int nMax = (maxOrder + 1) / 2;
    for (int n = -nMax; n <= nMax; ++n)
    {
        for (int p = 0; p <= 1; ++p)
        {
            AxisImage image;
            image.coordinate = 2.0 * n * size + (p == 0 ? source : -source);
            image.emissionSign = p == 0 ? 1.0 : -1.0;
            image.hitsMin = std::abs(n - p);
            image.hitsMax = std::abs(n);
            if (image.order() <= maxOrder)
                out.push_back(image);
        }
    }
    // Lowest order first, so the combining loops can stop early.
    std::stable_sort(out.begin(), out.end(),
                     [](const AxisImage& a, const AxisImage& b) { return a.order() < b.order(); });
    return out;
}

Vec3 normalized(const Vec3& v) noexcept
{
    const double length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length <= 0.0)
        return {0.0, 0.0, 0.0};
    return {v.x / length, v.y / length, v.z / length};
}

} // namespace

BandArray omniDirectivity(const Vec3& emissionDirection) noexcept
{
    (void)emissionDirection;
    BandArray gains{};
    gains.fill(1.0);
    return gains;
}

std::size_t imageCount(int maxOrder) noexcept
{
    if (maxOrder < 0)
        return 0;
    const auto n = static_cast<std::size_t>(maxOrder);
    return (2 * n + 1) * (2 * n * n + 2 * n + 3) / 3;
}

ImageSourceSet computeImageSources(const contract::Room& room, const Vec3& source, const Vec3& listener,
                                   const ImageSourceOptions& options)
{
    const int maxOrder = std::max(options.maxOrder, 0);
    const Vec3& size = room.geometry.dimensions;
    const auto xs = axisImages(size.x, source.x, maxOrder);
    const auto ys = axisImages(size.y, source.y, maxOrder);
    const auto zs = axisImages(size.z, source.z, maxOrder);

    // Per surface and band: specular pressure factor sqrt(1 - a) * sqrt(1 - s), the energy factor
    // (1 - a) without scattering, and the energy factor (1 - s) of scattering.
    std::array<BandArray, kNumSurfaces> specular{};
    std::array<BandArray, kNumSurfaces> reflectedEnergy{};
    std::array<double, kNumSurfaces> specularEnergyShare{};
    for (std::size_t s = 0; s < kNumSurfaces; ++s)
    {
        const auto& material = room.surfaces[s];
        specularEnergyShare[s] = 1.0 - material.scattering;
        for (std::size_t b = 0; b < kNumOctaveBands; ++b)
        {
            reflectedEnergy[s][b] = 1.0 - material.bandsAbsorption[b];
            specular[s][b] = std::sqrt(reflectedEnergy[s][b]) * std::sqrt(specularEnergyShare[s]);
        }
    }

    BandArray airDbPerMetre{};
    if (options.airAbsorption)
        airDbPerMetre = bandsAirAttenuationDbPerMetre();

    ImageSourceSet set;
    set.images.reserve(imageCount(maxOrder));

    for (const auto& ix : xs)
    {
        if (ix.order() > maxOrder)
            break;
        for (const auto& iy : ys)
        {
            if (ix.order() + iy.order() > maxOrder)
                break;
            for (const auto& iz : zs)
            {
                const int order = ix.order() + iy.order() + iz.order();
                if (order > maxOrder)
                    break;

                ImageSource image;
                image.position = {ix.coordinate, iy.coordinate, iz.coordinate};
                image.order = order;
                image.hits[surfaceIndex(SurfaceId::xMin)] = ix.hitsMin;
                image.hits[surfaceIndex(SurfaceId::xMax)] = ix.hitsMax;
                image.hits[surfaceIndex(SurfaceId::yMin)] = iy.hitsMin;
                image.hits[surfaceIndex(SurfaceId::yMax)] = iy.hitsMax;
                image.hits[surfaceIndex(SurfaceId::floor)] = iz.hitsMin;
                image.hits[surfaceIndex(SurfaceId::ceiling)] = iz.hitsMax;

                const Vec3 toImage{image.position.x - listener.x, image.position.y - listener.y,
                                   image.position.z - listener.z};
                image.distanceM = std::sqrt(toImage.x * toImage.x + toImage.y * toImage.y
                                            + toImage.z * toImage.z);
                image.arrivalTimeS = image.distanceM / kSpeedOfSoundMps;
                image.arrivalDirection = normalized(toImage);
                // The path leaves the image towards the listener; mirrored back into the real
                // source's frame on every axis reflected an odd number of times.
                image.emissionDirection = normalized({-toImage.x * ix.emissionSign,
                                                      -toImage.y * iy.emissionSign,
                                                      -toImage.z * iz.emissionSign});

                const BandArray air = bandsAirAmplitude(airDbPerMetre, image.distanceM);
                const BandArray directivity = options.directivity(image.emissionDirection);
                double specularShare = 1.0;
                for (std::size_t s = 0; s < kNumSurfaces; ++s)
                    specularShare *= std::pow(specularEnergyShare[s], image.hits[s]);

                ScatteredEnergy scattered;
                scattered.arrivalTimeS = image.arrivalTimeS;
                scattered.order = order;
                bool audible = order == 0;
                bool scatters = false;
                for (std::size_t b = 0; b < kNumOctaveBands; ++b)
                {
                    double pressure = options.gain / image.distanceM * air[b] * directivity[b];
                    double energy = pressure * pressure; // energy of the path without scattering
                    for (std::size_t s = 0; s < kNumSurfaces; ++s)
                    {
                        if (image.hits[s] == 0)
                            continue;
                        pressure *= std::pow(specular[s][b], image.hits[s]);
                        energy *= std::pow(reflectedEnergy[s][b], image.hits[s]);
                    }
                    image.bandsAmplitude[b] = pressure;
                    scattered.bandsEnergy[b] = energy * (1.0 - specularShare);
                    audible = audible || pressure != 0.0;
                    scatters = scatters || scattered.bandsEnergy[b] > 0.0;
                }
                if (audible || scatters)
                    set.images.push_back(image);
                if (scatters)
                    set.scattered.push_back(scattered);
            }
        }
    }

    // The direct path is the only order-0 image and the nearest one, so it sorts first.
    const auto byTime = [](const auto& a, const auto& b) { return a.arrivalTimeS < b.arrivalTimeS; };
    std::stable_sort(set.images.begin(), set.images.end(), byTime);
    std::stable_sort(set.scattered.begin(), set.scattered.end(), byTime);
    return set;
}

} // namespace sim::ism
