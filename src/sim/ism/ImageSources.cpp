#include "sim/ism/ImageSources.h"

#include "sim/AirAbsorption.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <numbers>

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

// Time-bounded variant (AX20): every axis image within `radius` of the listener coordinate, of any
// order, sorted by distance along the axis so the combining loops can stop early.
std::vector<AxisImage> axisImagesWithin(double size, double source, double listener, double radius)
{
    std::vector<AxisImage> out;
    // |2 n L +- s - l| <= radius needs |n| <= (radius + 2 L) / (2 L).
    const auto nMax = static_cast<int>(std::ceil((radius + 2.0 * size) / (2.0 * size)));
    for (int n = -nMax; n <= nMax; ++n)
    {
        for (int p = 0; p <= 1; ++p)
        {
            AxisImage image;
            image.coordinate = 2.0 * n * size + (p == 0 ? source : -source);
            image.emissionSign = p == 0 ? 1.0 : -1.0;
            image.hitsMin = std::abs(n - p);
            image.hitsMax = std::abs(n);
            if (std::abs(image.coordinate - listener) <= radius)
                out.push_back(image);
        }
    }
    std::stable_sort(out.begin(), out.end(), [&](const AxisImage& a, const AxisImage& b) {
        return std::abs(a.coordinate - listener) < std::abs(b.coordinate - listener);
    });
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

std::size_t reflectionImageCount(int maxOrder) noexcept
{
    return maxOrder < 0 ? 0 : imageCount(maxOrder) - 1;
}

double nthReflectionArrivalTimeS(const contract::Room& room, const Vec3& source, const Vec3& listener,
                                 std::size_t n)
{
    if (n == 0)
        return 0.0;
    const Vec3& size = room.geometry.dimensions;
    const double volume = size.x * size.y * size.z;
    // Expected radius holding n images, N(r) = 4 pi r^3 / (3 V) (Kuttruff Eq. 4.6), with margin.
    double radius = std::cbrt(3.0 * static_cast<double>(n + 1) * volume / (4.0 * std::numbers::pi)) * 1.2
                    + 2.0 * std::max({size.x, size.y, size.z});
    for (int attempt = 0; attempt < 64; ++attempt, radius *= 1.5)
    {
        const auto xs = axisImagesWithin(size.x, source.x, listener.x, radius);
        const auto ys = axisImagesWithin(size.y, source.y, listener.y, radius);
        const auto zs = axisImagesWithin(size.z, source.z, listener.z, radius);
        const double r2 = radius * radius;
        std::vector<double> d2;
        for (const auto& ix : xs)
        {
            const double dx = ix.coordinate - listener.x;
            if (dx * dx > r2)
                break;
            for (const auto& iy : ys)
            {
                const double dy = iy.coordinate - listener.y;
                if (dx * dx + dy * dy > r2)
                    break;
                for (const auto& iz : zs)
                {
                    const double dz = iz.coordinate - listener.z;
                    const double dd = dx * dx + dy * dy + dz * dz;
                    if (dd > r2)
                        break;
                    if (ix.order() + iy.order() + iz.order() > 0) // reflections only
                        d2.push_back(dd);
                }
            }
        }
        if (d2.size() < n)
            continue;
        std::nth_element(d2.begin(), d2.begin() + static_cast<std::ptrdiff_t>(n - 1), d2.end());
        return std::sqrt(d2[n - 1]) / kSpeedOfSoundMps;
    }
    return 0.0; // unreachable for valid rooms
}

ImageSourceSet computeImageSources(const contract::Room& room, const Vec3& source, const Vec3& listener,
                                   const ImageSourceOptions& options)
{
    const bool timeBounded = options.maxArrivalTimeS > 0.0;
    const int maxOrder = timeBounded ? std::numeric_limits<int>::max() : std::max(options.maxOrder, 0);
    const double radius = timeBounded ? options.maxArrivalTimeS * kSpeedOfSoundMps : 0.0;
    const Vec3& size = room.geometry.dimensions;
    const auto xs = timeBounded ? axisImagesWithin(size.x, source.x, listener.x, radius)
                                : axisImages(size.x, source.x, maxOrder);
    const auto ys = timeBounded ? axisImagesWithin(size.y, source.y, listener.y, radius)
                                : axisImages(size.y, source.y, maxOrder);
    const auto zs = timeBounded ? axisImagesWithin(size.z, source.z, listener.z, radius)
                                : axisImages(size.z, source.z, maxOrder);
    const auto axisDistanceSquared = [](const AxisImage& image, double l) {
        const double d = image.coordinate - l;
        return d * d;
    };
    const double radiusSquared = radius * radius;

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
        airDbPerMetre = options.airDbPerMetreOverride ? *options.airDbPerMetreOverride
                                                      : bandsAirAttenuationDbPerMetre();

    ImageSourceSet set;
    if (!timeBounded)
        set.images.reserve(imageCount(maxOrder));

    for (const auto& ix : xs)
    {
        const double dx2 = axisDistanceSquared(ix, listener.x);
        if (timeBounded ? dx2 > radiusSquared : ix.order() > maxOrder)
            break;
        for (const auto& iy : ys)
        {
            const double dxy2 = dx2 + axisDistanceSquared(iy, listener.y);
            if (timeBounded ? dxy2 > radiusSquared : ix.order() + iy.order() > maxOrder)
                break;
            for (const auto& iz : zs)
            {
                const int order = ix.order() + iy.order() + iz.order();
                if (timeBounded ? dxy2 + axisDistanceSquared(iz, listener.z) > radiusSquared
                                : order > maxOrder)
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
                if (timeBounded && !(image.arrivalTimeS < options.maxArrivalTimeS))
                    continue; // AX20: strictly before the end of the crossfade
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
                scattered.arrivalDirection = image.arrivalDirection;
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
                    // AX16: per path, at the specular arrival time, after all of its (1 - a).
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
