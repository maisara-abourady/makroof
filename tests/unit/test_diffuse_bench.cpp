// Phase 05h session 1, O6 (docs/sessions/2026-11-10-phase-05h.md): the C++ measurements D-H1 is decided
// from (phase-05h §3): cost per image evaluation at the runner's pool size, realised against planned work
// under the joint rule at block 64, the diffuse solve time and today's synchronous restore time over 10
// runs at the gated 100 m, 96 kHz scenes, and W1's diffuse share. Recorded, not gated: no W_max, n*_max,
// ratio or margin is chosen here. Hidden: CI runs it from the Release build with "[benchmark]".
#include "DiffuseTestUtil.h"

#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <string>
#include <vector>

using namespace sim::diffuse;

namespace {

using Clock = std::chrono::steady_clock;

double ms(Clock::time_point a, Clock::time_point b)
{
    return std::chrono::duration<double, std::milli>(b - a).count();
}

struct Spread
{
    double min = 0.0, median = 0.0, max = 0.0;
};

Spread spread(std::vector<double> v)
{
    std::sort(v.begin(), v.end());
    return {v.front(), 0.5 * (v[(v.size() - 1) / 2] + v[v.size() / 2]), v.back()};
}

// The gated 100 m scenes (prototype keys of tools/validation/phase05b2_dt1.py _joint_cases()).
contract::SceneDescription cube(const std::string& key)
{
    std::array<contract::BandArray, 6> alpha{};
    std::array<double, 6> s{};
    if (key == "cube100_flutter_fallback")
    {
        alpha = {diffuse_test::flat(0.02), diffuse_test::flat(0.02), diffuse_test::flat(0.95),
                 diffuse_test::flat(0.95), diffuse_test::flat(0.95), diffuse_test::flat(0.95)};
        s = {0.0, 0.0, 0.05, 0.05, 0.05, 0.05};
    }
    else
    {
        alpha.fill(diffuse_test::flat(0.05));
        s.fill(key == "cube100_lowalpha0.05_s1" ? 1.0 : 0.3);
    }
    auto sc = diffuse_test::scene({100.0, 100.0, 100.0}, alpha, s, {50.0, 30.0, 1.7},
                                  {{45.0, 70.0, 2.0}, {55.0, 70.0, 2.0}});
    sc.render.outputMode = contract::OutputMode::binaural;
    return sc;
}

contract::SceneDescription w1Scene()
{
    std::array<contract::BandArray, 6> alpha{};
    alpha.fill({0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3});
    std::array<double, 6> s{};
    s.fill(0.3);
    return diffuse_test::scene({20.0, 30.0, 10.0}, alpha, s, {10.0, 8.0, 1.7},
                               {{7.0, 20.0, 2.0}, {13.0, 20.0, 2.0}});
}

void printResult(const char* key, const DiffuseResult& r, const diffuse_test::Planned& p)
{
    std::printf("05h-cost %s: fallback e0 %d e1 %d, t_mix %.4f / %.4f s, lattice %zu, n* %lld, N_need %lld, "
                "N_cap %lld, N %lld, W_pilot %lld, W_final %lld, realised/W_scene %.4f, cap hit %d, floor "
                "truncated %d, pilot floor %d, pilot shipped %d, hash 0x%016llx\n",
                key, p.emitters[0].fallback ? 1 : 0, p.emitters[1].fallback ? 1 : 0,
                p.problem.emitters[0].mixS, p.problem.emitters[1].mixS, r.latticeImages,
                static_cast<long long>(r.nStar), static_cast<long long>(r.nNeed),
                static_cast<long long>(r.count.nCap), static_cast<long long>(r.count.n),
                static_cast<long long>(r.wPilot), static_cast<long long>(r.wFinal), r.realisedWorkRatio(),
                r.count.capHit ? 1 : 0, r.count.floorTruncated ? 1 : 0, r.count.pilotFloor ? 1 : 0,
                r.count.pilotShipped ? 1 : 0, static_cast<unsigned long long>(r.faceHash));
    for (std::size_t e = 0; e < r.emitters.size(); ++e)
    {
        const auto& er = r.emitters[e];
        double pilotSe = 0.0, pilotVov = 0.0, vov = 0.0;
        for (std::size_t k = 0; k < 8; ++k)
        {
            pilotSe = std::max(pilotSe, er.bandsPilotSeDb[k]);
            pilotVov = std::max(pilotVov, er.bandsPilotVov[k]);
            vov = std::max(vov, er.bandsVov[k]);
        }
        const double ax16 = p.emitters[e].bandsAx16Target[4];
        const double hyb = p.problem.emitters[e].bandsSpecularTarget[4] + er.bandsDiffuse[4];
        std::printf(
            "05h-cost %s e%zu: achieved SE %.3f dB (max band), pilot SE %.3f dB, pilot VOV %.3f, final VOV "
            "%.3f, VOV_union %.3f, both-near %d, U %d, AX16 - switched at 1 kHz %+.2f dB\n",
            key, e, er.achievedSeDb, pilotSe, pilotVov, vov, er.vovUnion, er.bothNear ? 1 : 0,
            er.approximate ? 1 : 0, hyb > 0.0 ? 10.0 * std::log10(ax16 / hyb) : 0.0);
    }
}

} // namespace

TEST_CASE("benchmark: phase 05h C++ costs for D-H1 (gated 100 m scenes, 96 kHz; W1 diffuse share)",
          "[.][benchmark][diffuse-cost]")
{
    constexpr int kRuns = 10;
    ThreadPool& pool = ThreadPool::process();
    std::printf(
        "05h-cost pool size %u (hardware_concurrency), W_scene %lld (provisional W_max %lld per emitter), "
        "n*_max %lld, block %lld\n",
        pool.size(), static_cast<long long>(2 * kWMaxPerEmitterProvisional),
        static_cast<long long>(kWMaxPerEmitterProvisional), static_cast<long long>(kNStarMax),
        static_cast<long long>(kBlockHistories));

    for (const char* key :
         {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1"})
    {
        const auto sc = cube(key);
        const auto planned = diffuse_test::plan(sc);
        DiffuseResult first;
        std::vector<double> solve;
        for (int i = 0; i < kRuns; ++i)
        {
            const auto t0 = Clock::now();
            const auto r = estimateDiffuse(planned.problem);
            solve.push_back(ms(t0, Clock::now()));
            if (i == 0)
                first = r;
            REQUIRE(r.faceHash == first.faceHash);
        }
        printResult(key, first, planned);
        const auto sp = spread(solve);
        const double work = static_cast<double>(first.wPilot + first.wFinal);
        std::printf(
            "05h-cost %s: diffuse solve over %d runs min %.1f median %.1f max %.1f ms; %.2f ns per image "
            "evaluation at pool size %u (median solve / realised work)\n",
            key, kRuns, sp.min, sp.median, sp.max, sp.median * 1e6 / work, pool.size());
        {
            ThreadPool single(1);
            DiffuseRunOptions o;
            o.pool = &single;
            const auto t0 = Clock::now();
            const auto r = estimateDiffuse(planned.problem, {}, o);
            const double t = ms(t0, Clock::now());
            REQUIRE(r.faceHash == first.faceHash);
            std::printf("05h-cost %s: one thread %.1f ms, %.2f ns per image evaluation\n", key, t,
                        t * 1e6 / work);
        }

        // Today's synchronous state restore (no diffuse solve yet) through the JUCE-free pipeline,
        // prepared realtime at 96 kHz: t_restore after the switch ~ this + the solve above.
        const auto values = module3d::parameterValuesFromScene(sc);
        const auto smallValues = module3d::defaultParameterValues();
        plugin::ScenePipeline pipe;
        pipe.prepare(96000.0, 512, false);
        std::vector<double> restore;
        for (int i = 0; i < kRuns; ++i)
        {
            pipe.beginRestore();
            pipe.restore(plugin::defaultScene(), smallValues); // untimed: leave the gated scene
            const auto t0 = Clock::now();
            pipe.beginRestore();
            pipe.restore(sc, values);
            restore.push_back(ms(t0, Clock::now()));
        }
        const auto rs = spread(restore);
        std::printf(
            "05h-cost %s: synchronous restore today (no diffuse) over %d runs min %.1f median %.1f max "
            "%.1f ms; restore + median solve %.1f ms, x14 %.2f s (30 s watchdog)\n",
            key, kRuns, rs.min, rs.median, rs.max, rs.max + sp.median, 14.0 * (rs.max + sp.median) / 1000.0);
    }

    // W1 (AQ10 room, 2 emitters, 48 kHz): the diffuse share at n*_max 1 024, median of 10.
    const auto planned = diffuse_test::plan(w1Scene());
    std::vector<double> w1;
    DiffuseResult r1;
    for (int i = 0; i < kRuns; ++i)
    {
        const auto t0 = Clock::now();
        r1 = estimateDiffuse(planned.problem);
        w1.push_back(ms(t0, Clock::now()));
    }
    printResult("W1", r1, planned);
    const auto s1 = spread(w1);
    std::printf(
        "05h-cost W1: diffuse solve min %.2f median %.2f max %.2f ms at pool size %u (AX41: diffuse share of "
        "W1 for two emitters <= 25 ms)\n",
        s1.min, s1.median, s1.max, pool.size());
}
