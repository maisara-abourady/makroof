// Phase 07 scope 2: host parameters <-> scene. Room-size map (decider D9), listener-emitter push-away
// (decider D1, tests (a)-(c)), the scene as a pure function of the parameters.
#include "ContractFixtures.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "module3d/ParameterMap.h"
#include "module3d/SceneModel.h"

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <numbers>
#include <random>
#include <vector>

// Exact comparisons are intended (exact endpoints, bit-identical scenes, D9/D1).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

using contract::Vec3;

contract::SceneDescription mediumRoom()
{
    auto parsed = contract::fromJson(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / "medium_room.json"));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

double dist(const Vec3& a, const Vec3& b)
{
    const double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

bool inBox(const Vec3& p, const module3d::MarginBox& b, double tol = 1e-12)
{
    return p.x >= b.lo.x - tol && p.x <= b.hi.x + tol && p.y >= b.lo.y - tol && p.y <= b.hi.y + tol
           && p.z >= b.lo.z - tol && p.z <= b.hi.z + tol;
}

} // namespace

TEST_CASE("Room-size map (D9): exact endpoints, exact inverse endpoints, strictly monotone",
          "[module3d][params][room-map]")
{
    REQUIRE(module3d::roomSizeFromNormalized(0.0) == 1.5);
    REQUIRE(module3d::roomSizeFromNormalized(1.0) == 100.0);
    REQUIRE(module3d::roomSizeFromNormalized(-0.5) == 1.5);
    REQUIRE(module3d::roomSizeFromNormalized(1.5) == 100.0);
    REQUIRE(module3d::normalizedFromRoomSize(1.5) == 0.0);
    REQUIRE(module3d::normalizedFromRoomSize(100.0) == 1.0);
    REQUIRE(module3d::normalizedFromRoomSize(1.0) == 0.0);
    REQUIRE(module3d::normalizedFromRoomSize(250.0) == 1.0);

    constexpr int kPoints = 10000;
    double prevL = -1.0;
    double prevX = -1.0;
    for (int i = 0; i < kPoints; ++i)
    {
        const double x = static_cast<double>(i) / (kPoints - 1);
        const double l = module3d::roomSizeFromNormalized(x);
        INFO("x = " << x);
        REQUIRE(l >= 1.5);
        REQUIRE(l <= 100.0);
        REQUIRE(l > prevL);
        prevL = l;
        const double li = 1.5 + (100.0 - 1.5) * x;
        const double xi = module3d::normalizedFromRoomSize(li);
        REQUIRE(xi > prevX);
        prevX = xi;
        // The formula of parameter_ids_v1.json: L = 1.5 (100 / 1.5)^x.
        REQUIRE(std::fabs(l - 1.5 * std::pow(100.0 / 1.5, x)) <= 1e-12 * l);
        REQUIRE(std::fabs(module3d::normalizedFromRoomSize(l) - x) <= 1e-12);
    }
}

TEST_CASE("Push-away (D1) (a): e = l near the corners of 1.5 m rooms always validates",
          "[module3d][params][push-away]")
{
    std::mt19937_64 rng(7001);
    std::uniform_real_distribution<double> jitter(0.0, 0.05);
    std::bernoulli_distribution side(0.5);
    const auto base = mediumRoom();
    module3d::ParameterValues v = module3d::defaultParameterValues();
    v[module3d::kRoomW] = v[module3d::kRoomD] = v[module3d::kRoomH] = 1.5;
    for (int i = 0; i < 100000; ++i)
    {
        // l in a corner region of the margin box (normalised 0 or 1, moved inwards by up to 0.05).
        for (const std::size_t axis : {std::size_t{0}, std::size_t{1}, std::size_t{2}})
        {
            const double n = side(rng) ? jitter(rng) : 1.0 - jitter(rng);
            v[module3d::kListenerX + axis] = n;
            v[module3d::kEmLX + axis] = n; // e = l
            v[module3d::kEmRX + axis] = n;
        }
        const auto scene = module3d::deriveScene(v, base);
        const auto result = contract::validate(scene);
        INFO("case " << i);
        REQUIRE(result.ok());
    }
}

TEST_CASE("Push-away (D1) (b): within 1e-9 m of a brute-force minimum", "[module3d][params][push-away]")
{
    constexpr double r = 0.3;
    constexpr int kFib = 100000;   // Fibonacci points on the 0.3 m sphere
    constexpr int kCircle = 10000; // points on each circle where a face plane of B cuts the sphere
    std::mt19937_64 rng(7002);
    std::uniform_real_distribution<double> side(1.5, 3.0);
    std::uniform_real_distribution<double> u01(0.0, 1.0);
    std::normal_distribution<double> gauss(0.0, 1.0);

    // Unit Fibonacci directions, computed once.
    std::vector<Vec3> fib(kFib);
    const double golden = std::numbers::pi * (3.0 - std::sqrt(5.0));
    for (int k = 0; k < kFib; ++k)
    {
        const double z = 1.0 - 2.0 * (k + 0.5) / kFib;
        const double rho = std::sqrt(1.0 - z * z);
        fib[static_cast<std::size_t>(k)] = {rho * std::cos(golden * k), rho * std::sin(golden * k), z};
    }

    for (int c = 0; c < 200; ++c)
    {
        const Vec3 dims{side(rng), side(rng), side(rng)};
        const auto box = module3d::marginBox(dims);
        // l biased to the box's edges and corners: each axis within 0.3 m of a margin half of the time.
        Vec3 l{};
        double* lp[3] = {&l.x, &l.y, &l.z};
        const double lo[3] = {box.lo.x, box.lo.y, box.lo.z};
        const double hi[3] = {box.hi.x, box.hi.y, box.hi.z};
        for (int a = 0; a < 3; ++a)
        {
            const double t = u01(rng);
            if (t < 0.25)
                *lp[a] = lo[a] + 0.3 * u01(rng);
            else if (t < 0.5)
                *lp[a] = hi[a] - 0.3 * u01(rng);
            else
                *lp[a] = lo[a] + (hi[a] - lo[a]) * u01(rng);
        }
        // e inside the 0.3 m ball around l and inside B (rejection), or e = l now and then.
        Vec3 e = l;
        if (c % 10 != 0)
        {
            do
            {
                Vec3 g{gauss(rng), gauss(rng), gauss(rng)};
                const double n = std::sqrt(g.x * g.x + g.y * g.y + g.z * g.z);
                const double rad = r * std::cbrt(u01(rng)) * 0.999;
                e = {l.x + g.x / n * rad, l.y + g.y / n * rad, l.z + g.z / n * rad};
            } while (!inBox(e, box, 0.0));
        }

        const Vec3 p = module3d::pushAwayFromListener(e, l, box);
        INFO("case " << c);
        REQUIRE(inBox(p, box));
        REQUIRE(dist(p, l) >= r - 1e-12);

        double bruteMin = std::numeric_limits<double>::infinity();
        const auto consider = [&](const Vec3& q) {
            if (inBox(q, box, 1e-12))
                bruteMin = std::min(bruteMin, dist(q, e));
        };
        for (const auto& u : fib)
            consider({l.x + r * u.x, l.y + r * u.y, l.z + r * u.z});
        for (int a = 0; a < 3; ++a)
        {
            for (const double plane : {lo[a], hi[a]})
            {
                const double h = plane - *lp[a];
                if (std::fabs(h) > r)
                    continue;
                const double rho = std::sqrt(r * r - h * h);
                for (int k = 0; k < kCircle; ++k)
                {
                    const double phi = 2.0 * std::numbers::pi * k / kCircle;
                    double q[3]{};
                    q[a] = plane;
                    q[(a + 1) % 3] = *lp[(a + 1) % 3] + rho * std::cos(phi);
                    q[(a + 2) % 3] = *lp[(a + 2) % 3] + rho * std::sin(phi);
                    consider({q[0], q[1], q[2]});
                }
            }
        }
        REQUIRE(std::isfinite(bruteMin));
        REQUIRE(dist(p, e) <= bruteMin + 1e-9);
    }
}

TEST_CASE("Push-away (D1) (c): the analytic case in a 1.5 m cube", "[module3d][params][push-away]")
{
    const auto box = module3d::marginBox({1.5, 1.5, 1.5});
    const Vec3 p = module3d::pushAwayFromListener({0.1, 0.75, 0.75}, {0.25, 0.75, 0.75}, box);
    REQUIRE(std::fabs(p.x - 0.1) <= 1e-12);
    REQUIRE(std::fabs(p.y - (0.75 + 0.15 * std::sqrt(3.0))) <= 1e-12);
    REQUIRE(std::fabs(p.z - 0.75) <= 1e-12);
}

TEST_CASE("Push-away: an emitter at >= 0.3 m is not moved; e = l goes forward (+y)",
          "[module3d][params][push-away]")
{
    const auto box = module3d::marginBox({8.0, 12.0, 4.0});
    const Vec3 l{4.0, 3.0, 1.7};
    const Vec3 far{4.0, 3.3, 1.7};
    REQUIRE(module3d::pushAwayFromListener(far, l, box) == far);
    const Vec3 p = module3d::pushAwayFromListener(l, l, box);
    REQUIRE(std::fabs(p.x - 4.0) <= 1e-15);
    REQUIRE(std::fabs(p.y - 3.3) <= 1e-15);
    REQUIRE(std::fabs(p.z - 1.7) <= 1e-15);
}

TEST_CASE("deriveScene: a pure function of the parameters and the non-parameter fields", "[module3d][params]")
{
    const auto base = mediumRoom();
    const auto defaults = module3d::defaultParameterValues();

    SECTION("the defaults are the default scene")
    {
        const auto s = module3d::deriveScene(defaults, base);
        REQUIRE(contract::validate(s).ok());
        REQUIRE(s.room.geometry.dimensions == base.room.geometry.dimensions);
        REQUIRE(dist(s.listener.position, base.listener.position) <= 1e-12);
        REQUIRE(dist(s.emitters[0].position, base.emitters[0].position) <= 1e-12);
        REQUIRE(dist(s.emitters[1].position, base.emitters[1].position) <= 1e-12);
    }

    SECTION("same inputs, same scene; the push-away is never written back")
    {
        auto v = defaults;
        v[module3d::kEmLX] = v[module3d::kListenerX];
        v[module3d::kEmLY] = v[module3d::kListenerY];
        v[module3d::kEmLZ] = v[module3d::kListenerZ];
        const auto before = v;
        const auto a = module3d::deriveScene(v, base);
        const auto b = module3d::deriveScene(v, base);
        REQUIRE(a == b);
        REQUIRE(v == before);
        REQUIRE(dist(a.emitters[0].position, a.listener.position) >= 0.3 - 1e-12);
        // The parameters still describe the pre-push position.
        const auto back = module3d::parameterValuesFromScene(a);
        REQUIRE(back[module3d::kEmLY] != v[module3d::kEmLY]);
    }

    SECTION("non-parameter fields come from the base; output_mode is not applied in Phase 07")
    {
        auto changed = base;
        changed.render.tailSeed = 99;
        changed.room.surface(contract::SurfaceId::floor).bandsAbsorption[3] = 0.5;
        changed.render.outputMode = contract::OutputMode::stereoSpeakers;
        auto v = defaults;
        v[module3d::kOutputMode] = 0.0; // binaural
        const auto s = module3d::deriveScene(v, changed);
        REQUIRE(s.render.tailSeed == 99);
        REQUIRE(s.room.surface(contract::SurfaceId::floor).bandsAbsorption[3] == 0.5);
        REQUIRE(s.render.outputMode == contract::OutputMode::stereoSpeakers);
    }

    SECTION("resizing keeps normalised positions")
    {
        auto v = defaults;
        v[module3d::kRoomW] = 100.0;
        v[module3d::kRoomD] = 100.0;
        v[module3d::kRoomH] = 100.0;
        const auto s = module3d::deriveScene(v, base);
        REQUIRE(contract::validate(s).ok());
        const auto back = module3d::parameterValuesFromScene(s);
        for (std::size_t i = module3d::kListenerX; i <= module3d::kEmRZ; ++i)
            REQUIRE(std::fabs(back[i] - v[i]) <= 1e-12);
        // phase-07 scope 2: the default scene stretched to 100 m puts the listener 52.9 m from L at
        // 42.1 m ear height.
        REQUIRE(std::fabs(dist(s.listener.position, s.emitters[0].position) - 52.9) < 0.05);
        REQUIRE(std::fabs(s.listener.position.z - 42.1) < 0.05);
    }
}
