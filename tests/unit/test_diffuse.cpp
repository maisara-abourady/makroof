// Phase 05h: the diffuse-energy estimator (AX39-AX44), src/sim/diffuse/.
#include "DiffuseTestUtil.h"

#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/Sampling.h"
#include "sim/diffuse/ThreadPool.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <string>

using namespace sim::diffuse;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

namespace {

contract::SceneDescription smallScene(double s = 0.4)
{
    // 6 x 5 x 3 m, mixed alpha, two emitters (generic test room, not a fixture).
    std::array<contract::BandArray, 6> alpha{diffuse_test::flat(0.1),  diffuse_test::flat(0.2),
                                             diffuse_test::flat(0.15), diffuse_test::flat(0.3),
                                             diffuse_test::flat(0.05), diffuse_test::flat(0.5)};
    alpha[5][7] = 0.7;
    return diffuse_test::scene({6.0, 5.0, 3.0}, alpha, {s, s, s, s, s, s}, {3.0, 1.5, 1.2},
                               {{2.0, 4.0, 1.5}, {4.2, 3.8, 1.6}});
}

bool sameBits(double a, double b)
{
    return std::memcmp(&a, &b, sizeof a) == 0;
}

void requireIdentical(const DiffuseResult& a, const DiffuseResult& b)
{
    REQUIRE(a.nStar == b.nStar);
    REQUIRE(a.count.n == b.count.n);
    REQUIRE(a.wPilot == b.wPilot);
    REQUIRE(a.wFinal == b.wFinal);
    REQUIRE(a.faceHash == b.faceHash);
    REQUIRE(a.emitters.size() == b.emitters.size());
    for (std::size_t e = 0; e < a.emitters.size(); ++e)
        for (std::size_t k = 0; k < 8; ++k)
        {
            REQUIRE(sameBits(a.emitters[e].bandsDiffuse[k], b.emitters[e].bandsDiffuse[k]));
            REQUIRE(sameBits(a.emitters[e].bandsSe[k], b.emitters[e].bandsSe[k]));
        }
}

} // namespace

TEST_CASE("diffuse RNG known-answer vectors (AX39 D3)", "[diffuse]")
{
    // The generator's specification: these values must be equal on every platform (D3). They were
    // produced by this implementation and checked against an independent Python implementation of the
    // same specification (SplitMix64 fold of the key, then SplitMix64 steps); a change of Sampling.h
    // that moves them changes every path.
    struct Kat
    {
        Key key;
        std::uint64_t state;
        std::uint64_t out[3];
    };
    const Kat kats[] = {
        {{0, PathEnd::emitter, 0, 0, 0, 0},
         0x1957a7604e215178ull,
         {0xf255f7ce0e960df8ull, 0xc3a9cc40fe6cc872ull, 0x67146d33ac7a43dbull}},
        {{kDiffuseSeed, PathEnd::emitter, 1, 12345, 3, 2},
         0xcabb2e8649966de3ull,
         {0x820a0626d34ae800ull, 0x3764ef1be8c7b85eull, 0x50b723c399a35d0eull}},
        {{kDiffuseSeed, PathEnd::listener, kSharedEmitter, 8000, 17, 0},
         0x0df62b567fc9bf4cull,
         {0xeb26d6c0ea557777ull, 0x81cbb27f570ba9beull, 0xb50e6985cbbabce2ull}},
        {{0xFFFFFFFFFFFFFFFFull, PathEnd::listener, 0xFFFFFFFFu, 0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFu,
          0xFFFFFFFFu},
         0x4534072e25c610cbull,
         {0x352a61c80c12f59bull, 0xd1409fccac1df122ull, 0x034461d952602287ull}},
    };
    for (const auto& kat : kats)
    {
        Stream s(kat.key);
        const std::uint64_t st = keyState(kat.key);
        const std::uint64_t o0 = s.nextU64(), o1 = s.nextU64(), o2 = s.nextU64();
        std::printf("KAT state 0x%016llxull out 0x%016llxull 0x%016llxull 0x%016llxull\n",
                    static_cast<unsigned long long>(st), static_cast<unsigned long long>(o0),
                    static_cast<unsigned long long>(o1), static_cast<unsigned long long>(o2));
        CHECK(st == kat.state);
        CHECK(o0 == kat.out[0]);
        CHECK(o1 == kat.out[1]);
        CHECK(o2 == kat.out[2]);
    }
    // Uniforms are in [0, 1) with 53 bits.
    Stream s(Key{kDiffuseSeed, PathEnd::emitter, 0, 7, 1, 1});
    for (int i = 0; i < 1000; ++i)
    {
        const double u = s.nextUniform();
        REQUIRE(u >= 0.0);
        REQUIRE(u < 1.0);
    }
}

TEST_CASE("diffuse samplers: unit sphere and Lambert hemisphere without trigonometry", "[diffuse]")
{
    double meanCos = 0.0;
    double meanZ = 0.0;
    const int n = 20000;
    for (int i = 0; i < n; ++i)
    {
        const Key key{kDiffuseSeed, PathEnd::emitter, 0, static_cast<std::uint64_t>(i), 0, 0};
        const Direction d = uniformSphere(key);
        const double len = std::sqrt(d.v[0] * d.v[0] + d.v[1] * d.v[1] + d.v[2] * d.v[2]);
        REQUIRE_THAT(len, WithinAbs(1.0, 1e-12));
        meanZ += d.v[2];
        const Direction l = lambert(key, 1, -1.0); // the y = D face: into the room is -y
        REQUIRE(l.v[1] <= 0.0);
        REQUIRE_THAT(std::sqrt(l.v[0] * l.v[0] + l.v[1] * l.v[1] + l.v[2] * l.v[2]), WithinAbs(1.0, 1e-12));
        meanCos += -l.v[1];
    }
    // Uniform sphere: E[z] = 0 (SE 1/sqrt(3n) = 0.004). Lambert: E[cos] = 2/3 (SE ~0.0017).
    CHECK(std::abs(meanZ / n) < 0.02);
    CHECK_THAT(meanCos / n, WithinAbs(2.0 / 3.0, 0.01));
    // The branch draw is P(diffuse) = s exactly at the ends.
    for (int i = 0; i < 100; ++i)
    {
        const Key key{kDiffuseSeed, PathEnd::emitter, 0, static_cast<std::uint64_t>(i), 1, 0};
        REQUIRE_FALSE(scatterBranch(key, 0.0));
        REQUIRE(scatterBranch(key, 1.0));
    }
}

TEST_CASE("diffuse joint path-count rule and its flags (AX41, D7)", "[diffuse]")
{
    // Pilot stop test: n >= n*_max or 2 W_pilot >= W_scene, integers only.
    CHECK(pilotStops(1024, 10, 6'100'000, 1024));
    CHECK_FALSE(pilotStops(960, 3'049'999, 6'100'000, 1024));
    CHECK(pilotStops(960, 3'050'000, 6'100'000, 1024));

    SECTION("uncapped: N = N_need rounded up to blocks")
    {
        const auto c = pathCount({1024, 100'000, 6'100'000, 5000});
        CHECK(c.nCap == (6'100'000LL - 100'000) * 1024 / 100'000 / 64 * 64); // 61 440
        CHECK(c.n == 5056);
        CHECK_FALSE(c.capHit);
        CHECK_FALSE(c.floorTruncated);
        CHECK_FALSE(c.pilotFloor);
        CHECK_FALSE(c.pilotShipped);
    }
    SECTION("N_need below n*: N = n*")
    {
        const auto c = pathCount({1024, 100'000, 6'100'000, 10});
        CHECK(c.n == 1024);
    }
    SECTION("cap hit := N_need > N_cap")
    {
        const auto c = pathCount({1024, 1'000'000, 6'100'000, 9000});
        CHECK(c.nCap == 5184); // floor(5.1e6 * 1024 / 1e6) = 5222 -> 81 blocks
        CHECK(c.n == 5184);
        CHECK(c.capHit);
        CHECK_FALSE(c.floorTruncated);
    }
    SECTION("floor truncated: N_cap below n*, reported apart from the cap hit")
    {
        const auto c = pathCount({1024, 3'000'000, 6'100'000, 100});
        CHECK(c.nCap == 1024LL * 3'100'000 / 3'000'000 / 64 * 64); // 1 058 -> 1 024
        CHECK_FALSE(c.floorTruncated);
        const auto d = pathCount({1024, 3'100'000, 6'100'000, 100});
        CHECK(d.nCap == 960);
        CHECK(d.n == 960);
        CHECK(d.floorTruncated);
        CHECK_FALSE(d.capHit);
    }
    SECTION("pilot floor and pilot shipped")
    {
        const auto c = pathCount({576, 3'050'000, 6'100'000, 40'000});
        CHECK(c.pilotFloor);
        CHECK(c.nCap == 576);
        const auto d = pathCount({576, 6'050'000, 6'100'000, 40'000});
        CHECK(d.nCap == 0);
        CHECK(d.pilotShipped);
        CHECK(d.n == 0);
        CHECK(d.capHit);
    }
    SECTION("no work at all (no scattering): no cap")
    {
        const auto c = pathCount({1024, 0, 6'100'000, 1});
        CHECK(c.n == 1024);
        CHECK_FALSE(c.capHit);
    }
    // N_need = ceil(k^2 var / (tot^2 target^2)).
    const double k = kDbPerRelative;
    const double var = 2.0e-6, tot = 0.01;
    CHECK(pathsNeeded(1024, var, tot, 0.083)
          == static_cast<std::int64_t>(std::ceil(k * k * var / (tot * tot * 0.083 * 0.083))));
    CHECK(pathsNeeded(1024, 0.0, tot, 0.083) == 1);
    CHECK(pathsNeeded(1024, var, 0.0, 0.083) == 1);
}

TEST_CASE("diffuse tally statistics R, VOV, slope (AX41)", "[diffuse]")
{
    const double x[] = {1.0, 2.0, 3.0, 4.0};
    const auto s = tallyStats(x, 4, 1);
    CHECK_THAT(s.mean, WithinRel(2.5, 1e-15));
    CHECK_THAT(s.variance, WithinRel(1.25, 1e-15));
    CHECK_THAT(s.se, WithinRel(std::sqrt(1.25 / 4.0), 1e-15));
    CHECK_THAT(s.r, WithinRel(std::sqrt(1.25 / 4.0) / 2.5, 1e-15));
    // d = -1.5, -0.5, 0.5, 1.5: sum d^2 = 5, sum d^4 = 10.25; VOV = 10.25 / 25 - 1/4.
    CHECK_THAT(s.vov, WithinRel(10.25 / 25.0 - 0.25, 1e-14));
    // Strided read (second column of two).
    const double y[] = {9.0, 1.0, 9.0, 2.0, 9.0, 3.0, 9.0, 4.0};
    CHECK(sameBits(tallyStats(y + 1, 4, 2).vov, s.vov));
    // Slope: Pareto-like scores x_i = (i + 1)^(-1/a) have Hill index ~ 1/a, slope ~ 1 + a.
    std::vector<double> p(10000);
    for (std::size_t i = 0; i < p.size(); ++i)
        p[i] = std::pow((static_cast<double>(i) + 1.0) / static_cast<double>(p.size()), -1.0 / 2.0);
    CHECK_THAT(tallyStats(p.data(), p.size(), 1).slope, WithinAbs(3.0, 0.15));
}

TEST_CASE("diffuse NW-4C weight, both-near at 0.70 m and the note U (AX44)", "[diffuse]")
{
    const contract::Vec3 dims{10.0, 8.0, 4.0};
    CHECK(sameBits(nearestSurfaceDistance(dims, {5.0, 4.0, 0.3}), 0.3));
    CHECK(sameBits(nearestSurfaceDistance(dims, {9.6, 4.0, 2.0}), 10.0 - 9.6));
    CHECK_THAT(blendWeight(1.0, 2.0), WithinRel(0.2, 1e-15));
    CHECK_THAT(blendWeight(0.1, 0.1), WithinRel(0.5, 1e-15));
    CHECK(bothNear(0.69, 0.69));
    CHECK_FALSE(bothNear(0.70, 0.69));
    CHECK_FALSE(bothNear(0.69, 0.70));
    // U = (both-near AND (cap hit OR VOV_union >= 0.1)) OR (cap hit AND SE > 0.33 dB).
    for (int near = 0; near < 2; ++near)
        for (int cap = 0; cap < 2; ++cap)
            for (const double vov : {0.05, 0.1})
                for (const double se : {0.2, 0.34})
                {
                    const bool expected = (near && (cap || vov >= 0.1)) || (cap && se > 0.33);
                    CHECK(approximateNote(near != 0, cap != 0, vov, se) == expected);
                }
}

TEST_CASE("diffuse estimate is independent of the pool size, repeatable and finite (AX39 D4)", "[diffuse]")
{
    const auto planned = diffuse_test::plan(smallScene());
    ThreadPool one(1), two(2), four(4);
    DiffuseRunOptions o1, o2, o4;
    o1.pool = &one;
    o2.pool = &two;
    o4.pool = &four;
    const auto a = estimateDiffuse(planned.problem, {}, o1);
    const auto b = estimateDiffuse(planned.problem, {}, o2);
    const auto c = estimateDiffuse(planned.problem, {}, o4);
    const auto d = estimateDiffuse(planned.problem, {}, o4);
    requireIdentical(a, b);
    requireIdentical(a, c);
    requireIdentical(c, d);
    REQUIRE_FALSE(a.cancelled);
    REQUIRE(a.nStar == kNStarMax); // a small room never reaches half of W_scene in the pilot
    REQUIRE(a.count.n >= a.nStar);
    REQUIRE(a.count.n % kBlockHistories == 0);
    std::printf("small room: n* %lld N %lld W_pilot %lld W_final %lld hash 0x%016llx\n",
                static_cast<long long>(a.nStar), static_cast<long long>(a.count.n),
                static_cast<long long>(a.wPilot), static_cast<long long>(a.wFinal),
                static_cast<unsigned long long>(a.faceHash));
    for (const auto& e : a.emitters)
        for (std::size_t k = 0; k < 8; ++k)
        {
            REQUIRE(std::isfinite(e.bandsDiffuse[k]));
            REQUIRE(e.bandsDiffuse[k] > 0.0);
            REQUIRE(e.bandsDiffuse[k] >= std::numeric_limits<double>::min()); // no denormal
            REQUIRE(std::isfinite(e.bandsSe[k]));
            REQUIRE(e.achievedSeDb <= 0.0831); // uncapped: N reaches the target
        }
    REQUIRE_FALSE(a.count.capHit);
}

TEST_CASE("diffuse two-emitter problem: each emitter gathers at its own images (AX44)", "[diffuse]")
{
    // The listener-started set is keyed by the shared emitter field and its trace does not depend on
    // the gather targets, so in a fixed-N run each emitter's reverse part in the two-emitter problem
    // is bit-identical to a one-emitter run of that emitter; emitter 0's forward part is too (same
    // key). Emitter 1's forward set has its own key: checked statistically against a one-emitter run.
    const auto planned = diffuse_test::plan(smallScene());
    REQUIRE(planned.problem.emitters.size() == 2);
    ThreadPool pool(3);
    DiffuseRunOptions o;
    o.pool = &pool;
    DiffuseLimits fixed;
    fixed.fixedHistories = 4096;
    const auto both = estimateDiffuse(planned.problem, fixed, o);
    for (std::size_t e = 0; e < 2; ++e)
    {
        auto single = planned.problem;
        single.emitters.clear();
        single.emitters.push_back(planned.problem.emitters[e]);
        const auto one = estimateDiffuse(single, fixed, o);
        const auto& b = both.emitters[e];
        const auto& s1 = one.emitters[0];
        for (std::size_t k = 0; k < 8; ++k)
        {
            REQUIRE(b.bandsReverse[k] > 0.0);
            REQUIRE(sameBits(b.bandsReverse[k], s1.bandsReverse[k]));
            if (e == 0)
                REQUIRE(sameBits(b.bandsForward[k], s1.bandsForward[k]));
            // Blend identity: the estimate is w fwd + (1 - w) rev of the same histories.
            REQUIRE_THAT(
                b.bandsDiffuse[k],
                WithinRel(b.weight * b.bandsForward[k] + (1.0 - b.weight) * b.bandsReverse[k], 1e-12));
        }
        if (e == 1)
            for (std::size_t k = 0; k < 8; ++k)
            {
                // Independent streams of the same estimator: |difference| within 5 combined SE,
                // the SE taken conservatively from the blended estimate's SE scaled up by 4.
                const double se = 4.0
                                  * std::sqrt(b.bandsSe[k] * b.bandsSe[k] + s1.bandsSe[k] * s1.bandsSe[k]);
                CHECK(std::abs(b.bandsForward[k] - s1.bandsForward[k]) <= 5.0 * se);
            }
    }
    // The two emitters really differ (a bug gathering both at one emitter's images would make them equal).
    CHECK_FALSE(sameBits(both.emitters[0].bandsReverse[4], both.emitters[1].bandsReverse[4]));
}

TEST_CASE("diffuse pilot stopped by work mid-batch is independent of the pool size (AX41, D4)", "[diffuse]")
{
    const auto planned = diffuse_test::plan(smallScene());
    ThreadPool p1(1), p3(3), p4(4);
    DiffuseRunOptions o1, o3, o4;
    o1.pool = &p1;
    o3.pool = &p3;
    o4.pool = &p4;
    const auto free = estimateDiffuse(planned.problem, {}, o1);
    REQUIRE(free.nStar == kNStarMax);
    // W_scene so that 2 W_pilot >= W_scene after about 5.5 of the 16 pilot blocks: the stop falls
    // inside a batch of 3 or 4 blocks.
    DiffuseLimits tight;
    tight.wScene = 2 * free.wPilot * 11 / 32;
    const auto a = estimateDiffuse(planned.problem, tight, o1);
    const auto b = estimateDiffuse(planned.problem, tight, o3);
    const auto c = estimateDiffuse(planned.problem, tight, o4);
    REQUIRE(a.nStar < kNStarMax);
    REQUIRE(a.nStar % kBlockHistories == 0);
    REQUIRE(2 * a.wPilot >= tight.wScene);
    requireIdentical(a, b);
    requireIdentical(a, c);
}

TEST_CASE("diffuse estimate does not depend on tailSeed (AX40)", "[diffuse]")
{
    auto s1 = smallScene();
    auto s2 = s1;
    s1.render.tailSeed = 1;
    s2.render.tailSeed = 0xDEADBEEF;
    ThreadPool pool(2);
    DiffuseRunOptions o;
    o.pool = &pool;
    requireIdentical(estimateDiffuse(diffuse_test::plan(s1).problem, {}, o),
                     estimateDiffuse(diffuse_test::plan(s2).problem, {}, o));
}

TEST_CASE("diffuse solve stops between blocks when asked (AX39 D6)", "[diffuse]")
{
    const auto planned = diffuse_test::plan(smallScene());
    ThreadPool pool(2);
    std::atomic<bool> stop{false};
    std::atomic<int> blocks{0};
    DiffuseRunOptions o;
    o.pool = &pool;
    o.stop = &stop;
    o.onBlock = [&](std::int64_t) {
        if (blocks.fetch_add(1) + 1 == 3)
            stop.store(true);
    };
    const auto r = estimateDiffuse(planned.problem, {}, o);
    CHECK(r.cancelled);
    // At most the blocks already started when the flag was set: 3 + one per other thread.
    CHECK(blocks.load() <= 3 + static_cast<int>(pool.size()) - 1);
    stop.store(true);
    blocks = 0;
    CHECK(estimateDiffuse(planned.problem, {}, o).cancelled);
    CHECK(blocks.load() == 0);
}

TEST_CASE("diffuse estimate is zero without scattering and positive with it", "[diffuse]")
{
    const auto planned = diffuse_test::plan(smallScene(0.0));
    ThreadPool pool(2);
    DiffuseRunOptions o;
    o.pool = &pool;
    const auto r = estimateDiffuse(planned.problem, {}, o);
    CHECK(r.wPilot == 0);
    for (const auto& e : r.emitters)
        for (const double v : e.bandsDiffuse)
            CHECK(sameBits(v, 0.0));
}

// O5 (docs/sessions/2026-11-10-phase-05h.md): smoke agreement with ref_hybrid on the 15 (A) cases,
// all 8 bands, pre-registered N = 131 072, z = 4.290 (AX43's family value), tau = 0.25 dB (AX42).
TEST_CASE("diffuse estimator agrees with ref_hybrid on the 15 (A) cases (smoke, AX42)",
          "[.][benchmark][diffuse-agree]")
{
    const auto ref = diffuse_test::readSmokeReference(std::string(SPATIAL_GOLDEN_DIR)
                                                      + "/phase05h_dt1_smoke_reference.json");
    REQUIRE(ref.rows.size() == 15);
    REQUIRE(ref.names.size() == 15);
    constexpr double kTau = 0.25;
    constexpr double kZ = 4.290;
    constexpr double kEllRefDb = 0.014; // 2.5 -> 1.25 m change <= 0.33 % (phase05b2_dt1.json c3)
    DiffuseLimits fixed;
    fixed.fixedHistories = 131072;
    double worstDb = 0.0, worstZ = 0.0, worstSe = 0.0;
    for (std::size_t i = 0; i < ref.rows.size(); ++i)
    {
        const auto& row = ref.rows[i];
        REQUIRE(row.size() == ref.columns.size());
        const auto c = [&](const char* name) {
            const std::size_t idx = ref.col(name);
            REQUIRE(idx < row.size());
            return row[idx];
        };
        std::array<contract::BandArray, 6> alpha{};
        const char* faces[] = {"alpha_xMin", "alpha_xMax",  "alpha_yMin",
                               "alpha_yMax", "alpha_floor", "alpha_ceiling"};
        for (std::size_t f = 0; f < 6; ++f)
            alpha[f] = diffuse_test::flat(c(faces[f]));
        const double s = c("s");
        const auto sc = diffuse_test::scene({c("dims_x"), c("dims_y"), c("dims_z")}, alpha,
                                            {s, s, s, s, s, s}, {c("rcv_x"), c("rcv_y"), c("rcv_z")},
                                            {{c("src_x"), c("src_y"), c("src_z")}});
        const auto planned = diffuse_test::plan(sc);
        const auto& pe = planned.emitters[0];
        // The C++ plan reproduces the Python plan (window, fallback, specular target).
        REQUIRE_THAT(pe.emitter.mixS, WithinRel(c("py_mix_s"), 1e-9));
        REQUIRE_THAT(pe.emitter.windowStartS, WithinRel(c("py_window_start_s"), 1e-9));
        REQUIRE(pe.fallback == (c("py_fallback") > 0.5));
        const auto r = estimateDiffuse(planned.problem, fixed);
        REQUIRE(r.count.n == 131072);
        const auto& er = r.emitters[0];
        for (std::size_t k = 0; k < 8; ++k)
        {
            const std::string bk = std::to_string(k);
            REQUIRE_THAT(pe.emitter.bandsSpecularTarget[k],
                         WithinRel(c(("py_target_specular_" + bk).c_str()), 1e-6) || WithinAbs(0.0, 1e-300));
            REQUIRE_THAT(pe.emitter.bandsT60S[k], WithinRel(c(("py_t60_" + bk).c_str()), 1e-9));
            const double tot = pe.emitter.bandsSpecularTarget[k] + er.bandsDiffuse[k];
            const double target = c(("target_" + bk).c_str());
            const double db = 10.0 * std::log10(tot / target);
            const double seDb = er.bandsSeDb[k];
            const double z = seDb > 0.0 ? db / seDb : 0.0;
            std::printf("agree %-18s band %zu  C++ - ref %+.4f dB  SE %.4f dB  z %+.2f\n",
                        ref.names[i].c_str(), k, db, seDb, z);
            worstDb = std::max(worstDb, std::abs(db));
            worstZ = std::max(worstZ, std::abs(z));
            worstSe = std::max(worstSe, seDb);
            CHECK(std::abs(db) <= kTau);
            CHECK(kZ * seDb <= kTau - kEllRefDb);
        }
    }
    std::printf("agree summary: max |C++ - ref| %.4f dB, max |z| %.2f, max SE %.4f dB (N = 131072)\n",
                worstDb, worstZ, worstSe);
}
