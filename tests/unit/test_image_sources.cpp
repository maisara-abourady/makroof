// sim::ism::computeImageSources: enumeration, geometry, amplitudes, reciprocity, symmetry, limits.
#include "IsmTestUtil.h"
#include "sim/AirAbsorption.h"
#include "sim/ism/BandRenderer.h"
#include "sim/ism/ImageSources.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <cmath>
#include <map>
#include <tuple>

using contract::SurfaceId;
using contract::surfaceIndex;
using contract::Vec3;
using sim::ism::ImageSource;
using sim::ism::ImageSourceOptions;

namespace {

ImageSourceOptions options(int order, bool air = true)
{
    ImageSourceOptions o;
    o.maxOrder = order;
    o.airAbsorption = air;
    return o;
}

// Independent enumerator: images of order k are the mirror images of the order-(k-1) images in
// each wall plane, except the wall the last reflection was in (that would give back the parent).
// Positions are deduplicated on a 1e-6 m grid. Returns position -> (order, hits).
struct RefImage
{
    int order;
    std::array<int, 6> hits;
};
using Key = std::tuple<long long, long long, long long>;
Key key(const Vec3& p)
{
    return {std::llround(p.x * 1e6), std::llround(p.y * 1e6), std::llround(p.z * 1e6)};
}

std::map<Key, RefImage> mirrorEnumerate(const contract::Room& room, const Vec3& source, int maxOrder)
{
    struct Node
    {
        Vec3 p;
        int lastWall;
        RefImage info;
    };
    const auto& d = room.geometry.dimensions;
    std::map<Key, RefImage> all;
    std::vector<Node> frontier{{source, -1, {0, {}}}};
    all[key(source)] = {0, {}};
    for (int order = 1; order <= maxOrder; ++order)
    {
        std::vector<Node> next;
        for (const auto& node : frontier)
        {
            for (int wall = 0; wall < 6; ++wall)
            {
                if (wall == node.lastWall)
                    continue;
                Vec3 p = node.p;
                switch (static_cast<SurfaceId>(wall))
                {
                case SurfaceId::xMin:
                    p.x = -p.x;
                    break;
                case SurfaceId::xMax:
                    p.x = 2.0 * d.x - p.x;
                    break;
                case SurfaceId::yMin:
                    p.y = -p.y;
                    break;
                case SurfaceId::yMax:
                    p.y = 2.0 * d.y - p.y;
                    break;
                case SurfaceId::floor:
                    p.z = -p.z;
                    break;
                case SurfaceId::ceiling:
                    p.z = 2.0 * d.z - p.z;
                    break;
                }
                RefImage info = node.info;
                info.order = order;
                ++info.hits[static_cast<std::size_t>(wall)];
                if (all.emplace(key(p), info).second)
                    next.push_back({p, wall, info});
            }
        }
        frontier = std::move(next);
    }
    return all;
}

double formulaAmplitude(const contract::Room& room, const ImageSource& image, std::size_t band, double gain)
{
    double a = gain / image.distanceM;
    for (std::size_t s = 0; s < 6; ++s)
    {
        const auto& m = room.surfaces[s];
        a *= std::pow(std::sqrt(1.0 - m.bandsAbsorption[band]) * std::sqrt(1.0 - m.scattering),
                      image.hits[s]);
    }
    return a;
}

} // namespace

TEST_CASE("image count follows (2N+1)(2N^2+2N+3)/3", "[sim][ism]")
{
    std::mt19937_64 rng(1);
    const auto room = ism_test::randomRoom(rng);
    const auto [s, l] = ism_test::randomPair(rng, room);
    for (int order = 0; order <= 12; ++order)
    {
        const auto set = sim::ism::computeImageSources(room, s, l, options(order));
        CHECK(set.images.size() == sim::ism::imageCount(order));
    }
    CHECK(sim::ism::imageCount(0) == 1);
    CHECK(sim::ism::imageCount(1) == 7);
    CHECK(sim::ism::imageCount(2) == 25);
}

TEST_CASE(
    "geometry: 200 random scenes, arrival time = |image - listener| / c, images match mirror enumeration",
    "[sim][ism]")
{
    std::mt19937_64 rng(2026);
    for (int scene = 0; scene < 200; ++scene)
    {
        const auto room = ism_test::randomRoom(rng);
        const auto [s, l] = ism_test::randomPair(rng, room);
        const int order = scene % 6; // 0..5, so the mirror enumeration stays cheap
        const auto set = sim::ism::computeImageSources(room, s, l, options(order));
        REQUIRE(!set.images.empty());
        CHECK(set.images.front().order == 0);
        CHECK(set.images.front().position == s);

        const auto reference = mirrorEnumerate(room, s, order);
        REQUIRE(set.images.size() == reference.size());
        double previous = 0.0;
        for (const auto& image : set.images)
        {
            const double expected = ism_test::distance(image.position, l) / sim::ism::kSpeedOfSoundMps;
            CHECK(std::abs(image.arrivalTimeS - expected) <= 1e-9);
            CHECK(image.arrivalTimeS >= previous); // sorted
            previous = image.arrivalTimeS;

            const auto it = reference.find(key(image.position));
            REQUIRE(it != reference.end());
            CHECK(it->second.order == image.order);
            CHECK(it->second.hits == image.hits);

            // Direction of arrival: unit vector towards the image.
            const auto& u = image.arrivalDirection;
            CHECK_THAT(u.x * u.x + u.y * u.y + u.z * u.z, Catch::Matchers::WithinAbs(1.0, 1e-12));
            CHECK_THAT(l.x + u.x * image.distanceM, Catch::Matchers::WithinAbs(image.position.x, 1e-9));
            CHECK_THAT(l.y + u.y * image.distanceM, Catch::Matchers::WithinAbs(image.position.y, 1e-9));
            CHECK_THAT(l.z + u.z * image.distanceM, Catch::Matchers::WithinAbs(image.position.z, 1e-9));
        }
    }
}

TEST_CASE("amplitude = gain / r * prod (sqrt(1-a) sqrt(1-s))^hits, without air absorption", "[sim][ism]")
{
    std::mt19937_64 rng(7);
    for (int scene = 0; scene < 20; ++scene)
    {
        const auto room = ism_test::randomRoom(rng);
        const auto [s, l] = ism_test::randomPair(rng, room);
        auto o = options(6, false);
        o.gain = ism_test::uniform(rng, 0.1, 2.0);
        const auto set = sim::ism::computeImageSources(room, s, l, o);
        for (const auto& image : set.images)
            for (std::size_t b = 0; b < 8; ++b)
                CHECK_THAT(image.bandsAmplitude[b],
                           Catch::Matchers::WithinRel(formulaAmplitude(room, image, b, o.gain), 1e-12));
        // Direct path at 1 m = gain (AX2): amplitude * r == gain.
        CHECK_THAT(set.images[0].bandsAmplitude[3] * set.images[0].distanceM,
                   Catch::Matchers::WithinRel(o.gain, 1e-12));
    }
}

TEST_CASE("air absorption multiplies each band by 10^(-a_b r / 20)", "[sim][ism][air]")
{
    std::mt19937_64 rng(8);
    const auto room = ism_test::randomRoom(rng, 20.0, 80.0);
    const auto [s, l] = ism_test::randomPair(rng, room);
    const auto with = sim::ism::computeImageSources(room, s, l, options(3, true));
    const auto without = sim::ism::computeImageSources(room, s, l, options(3, false));
    REQUIRE(with.images.size() == without.images.size());
    const auto db = sim::bandsAirAttenuationDbPerMetre();
    for (std::size_t i = 0; i < with.images.size(); ++i)
        for (std::size_t b = 0; b < 8; ++b)
            CHECK_THAT(
                with.images[i].bandsAmplitude[b] / without.images[i].bandsAmplitude[b],
                Catch::Matchers::WithinRel(std::pow(10.0, -db[b] * with.images[i].distanceM / 20.0), 1e-12));
}

TEST_CASE("scattering removes (1 - s) of the specular energy per reflection and reports it", "[sim][ism]")
{
    std::mt19937_64 rng(9);
    auto room = ism_test::randomRoom(rng);
    const auto [s, l] = ism_test::randomPair(rng, room);
    for (auto& surface : room.surfaces)
        surface.scattering = 0.0;
    const auto clean = sim::ism::computeImageSources(room, s, l, options(4, false));
    CHECK(clean.scattered.empty());
    for (auto& surface : room.surfaces)
        surface.scattering = 0.5;
    const auto scattering = sim::ism::computeImageSources(room, s, l, options(4, false));
    REQUIRE(clean.images.size() == scattering.images.size());
    REQUIRE(scattering.scattered.size() == scattering.images.size() - 1); // every reflected path
    for (std::size_t i = 0; i < clean.images.size(); ++i)
    {
        const int n = clean.images[i].order;
        for (std::size_t b = 0; b < 8; ++b)
        {
            const double e0 = clean.images[i].bandsAmplitude[b] * clean.images[i].bandsAmplitude[b];
            const double e1 = scattering.images[i].bandsAmplitude[b] * scattering.images[i].bandsAmplitude[b];
            CHECK_THAT(e1, Catch::Matchers::WithinRel(e0 * std::pow(0.5, n), 1e-12));
        }
    }
    // Specular + scattered energy = energy of the path without scattering (energy is conserved).
    for (std::size_t i = 1; i < scattering.images.size(); ++i)
    {
        const auto& sc = scattering.scattered[i - 1];
        CHECK_THAT(sc.arrivalTimeS, Catch::Matchers::WithinULP(scattering.images[i].arrivalTimeS, 0));
        for (std::size_t b = 0; b < 8; ++b)
        {
            const double specular = scattering.images[i].bandsAmplitude[b]
                                    * scattering.images[i].bandsAmplitude[b];
            const double e0 = clean.images[i].bandsAmplitude[b] * clean.images[i].bandsAmplitude[b];
            CHECK_THAT(specular + sc.bandsEnergy[b], Catch::Matchers::WithinRel(e0, 1e-12));
        }
    }
}

TEST_CASE("reciprocity: swapping source and listener gives the same images and IR (-120 dB)", "[sim][ism]")
{
    std::mt19937_64 rng(11);
    for (int scene = 0; scene < 5; ++scene)
    {
        const auto room = ism_test::randomRoom(rng, 2.0, 12.0);
        const auto [s, l] = ism_test::randomPair(rng, room);
        const auto forward = sim::ism::computeImageSources(room, s, l, options(8));
        const auto backward = sim::ism::computeImageSources(room, l, s, options(8));
        REQUIRE(forward.images.size() == backward.images.size());

        const sim::ism::OctaveFilterbank fb(48000.0);
        const double shift = forward.images[0].arrivalTimeS - 32.0 / 48000.0;
        const auto a = sim::ism::renderImageSources(forward.images, shift, fb);
        const auto b = sim::ism::renderImageSources(backward.images, shift, fb);
        REQUIRE(a.size() == b.size());
        double energy = 0.0, residual = 0.0;
        for (std::size_t n = 0; n < a.size(); ++n)
        {
            energy += a[n] * a[n];
            residual += (a[n] - b[n]) * (a[n] - b[n]);
        }
        INFO("residual " << 10.0 * std::log10(residual / energy + 1e-300) << " dB");
        CHECK(residual <= energy * 1e-12);
    }
}

TEST_CASE("symmetry: mirrored placement in a symmetric room gives mirror-identical image sets", "[sim][ism]")
{
    std::mt19937_64 rng(12);
    for (int axis = 0; axis < 3; ++axis)
    {
        auto room = ism_test::randomRoom(rng, 2.0, 15.0);
        const auto lo = static_cast<std::size_t>(2 * axis),
                   hi = lo + 1; // xMin/xMax, yMin/yMax, floor/ceiling
        room.surfaces[hi] = room.surfaces[lo];
        const auto [s, l] = ism_test::randomPair(rng, room);
        const auto& d = room.geometry.dimensions;
        const auto mirror = [&](Vec3 p) {
            if (axis == 0)
                p.x = d.x - p.x;
            else if (axis == 1)
                p.y = d.y - p.y;
            else
                p.z = d.z - p.z;
            return p;
        };
        const auto a = sim::ism::computeImageSources(room, s, l, options(6));
        const auto b = sim::ism::computeImageSources(room, mirror(s), mirror(l), options(6));
        REQUIRE(a.images.size() == b.images.size());

        std::map<Key, const ImageSource*> byPosition;
        for (const auto& image : b.images)
            byPosition[key(image.position)] = &image;
        for (const auto& image : a.images)
        {
            const auto it = byPosition.find(key(mirror(image.position)));
            REQUIRE(it != byPosition.end());
            const ImageSource& m = *it->second;
            CHECK_THAT(m.arrivalTimeS, Catch::Matchers::WithinAbs(image.arrivalTimeS, 1e-12));
            auto hits = image.hits;
            std::swap(hits[lo], hits[hi]);
            CHECK(m.hits == hits);
            for (std::size_t band = 0; band < 8; ++band)
                CHECK_THAT(m.bandsAmplitude[band],
                           Catch::Matchers::WithinRel(image.bandsAmplitude[band], 1e-12));
        }
    }
}

TEST_CASE("limits: all a = 1 or order 0 leaves the direct path only", "[sim][ism]")
{
    std::mt19937_64 rng(13);
    auto room = ism_test::randomRoom(rng);
    const auto [s, l] = ism_test::randomPair(rng, room);
    CHECK(sim::ism::computeImageSources(room, s, l, options(0)).images.size() == 1);
    CHECK(sim::ism::computeImageSources(room, s, l, options(0)).scattered.empty());

    for (auto& surface : room.surfaces)
        surface.bandsAbsorption.fill(1.0);
    const auto set = sim::ism::computeImageSources(room, s, l, options(10));
    REQUIRE(set.images.size() == 1);
    CHECK(set.images[0].order == 0);
    CHECK(set.scattered.empty());

    // One reflecting surface (the floor) at order 10: the direct path and one floor reflection.
    room.surface(SurfaceId::floor).bandsAbsorption.fill(0.5);
    const auto floorOnly = sim::ism::computeImageSources(room, s, l, options(10));
    REQUIRE(floorOnly.images.size() == 2);
    CHECK(floorOnly.images[1].hits[surfaceIndex(SurfaceId::floor)] == 1);
    CHECK(floorOnly.images[1].position == Vec3{s.x, s.y, -s.z});
}

TEST_CASE("emission direction is the arrival path mirrored back into the source frame", "[sim][ism]")
{
    contract::Room room;
    room.geometry.dimensions = {10.0, 10.0, 5.0};
    const Vec3 s{5.0, 2.0, 1.0}, l{5.0, 8.0, 1.0};
    const auto set = sim::ism::computeImageSources(room, s, l, options(1));
    // Direct path: leaves the source towards +y.
    CHECK_THAT(set.images[0].emissionDirection.y, Catch::Matchers::WithinAbs(1.0, 1e-12));
    for (const auto& image : set.images)
    {
        if (image.hits[surfaceIndex(SurfaceId::floor)] != 1)
            continue;
        // Floor bounce: leaves the real source downwards and forwards; the arrival comes from below
        // too (z mirrored once), while x and y are reversed.
        CHECK(image.emissionDirection.z < 0.0);
        CHECK(image.emissionDirection.y > 0.0);
        CHECK_THAT(image.emissionDirection.z, Catch::Matchers::WithinAbs(image.arrivalDirection.z, 1e-12));
    }
}
