// Phase 05h, scope 6 and D-H1 (AX38 4b / 4c / (iv), AX41, Seat 1's clause (d)): the records of the switched build.
// Hidden: CI runs them from the Release build with "[benchmark]". Recorded, not gated, except where the plan pins a
// gate (docs/review/phase-05h/, decision D-H1): the gated-scene flags, the realised-work assertion and the restore block
// are asserted in "[diffuse-gate-records]" once D-H1's constants are in the code.
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "contract/Json.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <random>
#include <string>
#include <thread>
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

contract::SceneDescription aq10Room()
{
    std::array<contract::BandArray, 6> alpha{};
    alpha.fill({0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3});
    std::array<double, 6> s{};
    s.fill(0.3);
    return diffuse_test::scene({20.0, 30.0, 10.0}, alpha, s, {10.0, 8.0, 1.7}, {{7.0, 20.0, 2.0}, {13.0, 20.0, 2.0}});
}

// Peak resident set (Linux: VmHWM from /proc/self/status, kB; 0 elsewhere).
long peakRssKb()
{
    std::ifstream in("/proc/self/status");
    std::string line;
    while (std::getline(in, line))
        if (line.rfind("VmHWM:", 0) == 0)
            return std::stol(line.substr(6));
    return 0;
}
long currentRssKb()
{
    std::ifstream in("/proc/self/status");
    std::string line;
    while (std::getline(in, line))
        if (line.rfind("VmRSS:", 0) == 0)
            return std::stol(line.substr(6));
    return 0;
}

} // namespace

// Seat 1's clause (d) (phase-05h §3; AX38 4c Trigger 1): 30 replicates of the shipping rule (pilot + joint rule + final
// range, as built) on disjoint pre-registered streams (replicate r uses histories offset by r × 2^20, pilot and final
// alike) against a long run (2^20 histories on the range [2^26, 2^26 + 2^20)), per gated cube: median and p95 |error| at
// 1 kHz per emitter (C15's rule: |median| ≤ 0.25 dB and p95 ≤ 1 dB), the replicate SD of the achieved SE and of the
// estimate (the starting-state spread Trigger 1's "any further rise" is read against).
TEST_CASE("records: clause (d) replicates of the shipping rule at the gated cubes (30 disjoint streams vs a long run)",
          "[.][benchmark][diffuse-replicates]")
{
    constexpr int kReplicates = 30;
    constexpr std::int64_t kStride = std::int64_t{1} << 20;
    for (const char* key : {"cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1", "cube100_flutter_fallback"})
    {
        const auto planned = diffuse_test::plan(cube(key));
        DiffuseLimits longRun;
        longRun.fixedStart = std::int64_t{1} << 26;
        longRun.fixedHistories = kStride;
        const auto t0 = Clock::now();
        const auto ref = estimateDiffuse(planned.problem, longRun);
        const double tLong = ms(t0, Clock::now());
        for (std::size_t e = 0; e < 2; ++e)
        {
            std::vector<double> errDb, seDb, vov;
            for (int r = 0; r < kReplicates; ++r)
            {
                DiffuseLimits lim;
                lim.historyOffset = static_cast<std::int64_t>(r) * kStride;
                const auto res = estimateDiffuse(planned.problem, lim);
                const double tot = planned.problem.emitters[e].bandsSpecularTarget[4] + res.emitters[e].bandsDiffuse[4];
                const double tref = planned.problem.emitters[e].bandsSpecularTarget[4] + ref.emitters[e].bandsDiffuse[4];
                errDb.push_back(10.0 * std::log10(tot / tref));
                seDb.push_back(res.emitters[e].achievedSeDb);
                vov.push_back(res.emitters[e].vovUnion);
            }
            std::vector<double> absErr(errDb.size());
            std::transform(errDb.begin(), errDb.end(), absErr.begin(), [](double x) { return std::abs(x); });
            std::sort(absErr.begin(), absErr.end());
            const double p95 = absErr[static_cast<std::size_t>(std::ceil(0.95 * absErr.size())) - 1];
            const auto sd = [](const std::vector<double>& v) {
                double m = 0.0;
                for (double x : v)
                    m += x;
                m /= static_cast<double>(v.size());
                double s2 = 0.0;
                for (double x : v)
                    s2 += (x - m) * (x - m);
                return std::sqrt(s2 / static_cast<double>(v.size() - 1));
            };
            const auto es = spread(errDb);
            std::printf("05h-replicates %s e%zu: 30 replicates at 1 kHz vs long run (2^20 histories, SE %.3f dB, %.0f ms): "
                        "median %+.3f dB, p95 |error| %.3f dB, max |error| %.3f dB, SD of error %.3f dB; achieved SE "
                        "median %.3f dB (SD %.4f); VOV_union median %.3f (SD %.3f); clause (d) %s\n",
                        key, e, ref.emitters[e].bandsSeDb[4], tLong, es.median, p95, absErr.back(), sd(errDb),
                        spread(seDb).median, sd(seDb), spread(vov).median, sd(vov),
                        (std::abs(es.median) <= 0.25 && p95 <= 1.0) ? "met" : "NOT met");
        }
    }
}

// AX38 4b / 4c records: full rebuilds (noise generated) and position-only rebuilds (cached unit decays), both with the
// diffuse solve, at 48 and 96 kHz: the six Phase 04 rooms, the AQ10 room, both 100 m cases; W1/W2 with the diffuse
// share; the peak working-set delta of the gated 100 m, 96 kHz builds (Linux); the synchronous restore at 100 m and
// 96 kHz with the solve (14 × t_restore against 30 s, worst of 10) and contended (a second pipeline solving the 100 m
// room at the same time).
TEST_CASE("records: AX38 4b/4c rebuilds, memory and the 100 m / 96 kHz restore with the diffuse solve",
          "[.][benchmark][diffuse-records]")
{
    constexpr int kRuns = 10;
    const auto full = [](const contract::SceneDescription& sc, double fs, int runs) {
        sim::BuildOptions o;
        o.sampleRate = fs;
        o.kind = sim::BuildOptions::Kind::Omni;
        std::vector<double> t;
        for (int i = 0; i < runs; ++i)
        {
            const auto t0 = Clock::now();
            (void)sim::buildRoomIR(sc, o);
            t.push_back(ms(t0, Clock::now()));
        }
        return spread(t);
    };
    std::printf("05h-records pool size %u\n", ThreadPool::process().size());
    for (const char* name : {"dead_booth.json", "living_room.json", "classroom.json", "club.json", "concert_hall_box.json",
                             "stone_box.json"})
        for (const double fs : {48000.0, 96000.0})
        {
            const auto sp = full(pipeline_test::loadScene(name), fs, 3);
            std::printf("05h-records full rebuild %-22s %6.0f Hz: min %.0f median %.0f max %.0f ms (3 runs)\n", name, fs,
                        sp.min, sp.median, sp.max);
        }
    for (const double fs : {48000.0, 96000.0})
    {
        const auto sp = full(aq10Room(), fs, 3);
        std::printf("05h-records full rebuild AQ10 room          %6.0f Hz: min %.0f median %.0f max %.0f ms\n", fs, sp.min,
                    sp.median, sp.max);
    }
    for (const char* key : {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1"})
    {
        const auto sc = cube(key);
        for (const double fs : {48000.0, 96000.0})
        {
            const long before = peakRssKb();
            const long rssBefore = currentRssKb();
            const auto sp = full(sc, fs, 3);
            const long after = peakRssKb();
            std::printf("05h-records full rebuild %-26s %6.0f Hz: min %.0f median %.0f max %.0f ms; peak RSS delta %.0f MB "
                        "(VmHWM %ld -> %ld kB, RSS before %ld kB)\n",
                        key, fs, sp.min, sp.median, sp.max, (after - before) / 1024.0, before, after, rssBefore);
        }
        // Synchronous restore with the solve, 96 kHz, worst of 10 (AX38 4c), alone and contended.
        const auto values = module3d::parameterValuesFromScene(sc);
        const auto smallValues = module3d::defaultParameterValues();
        plugin::ScenePipeline pipe;
        pipe.prepare(96000.0, 512, false);
        std::vector<double> restore;
        for (int i = 0; i < kRuns; ++i)
        {
            pipe.beginRestore();
            pipe.restore(plugin::defaultScene(), smallValues);
            const auto t0 = Clock::now();
            pipe.beginRestore();
            pipe.restore(sc, values);
            restore.push_back(ms(t0, Clock::now()));
        }
        const auto rs = spread(restore);
        std::printf("05h-records restore %-26s 96 kHz with the solve, %d runs: min %.0f median %.0f worst %.0f ms; "
                    "14 x worst %.2f s (30 s)\n",
                    key, kRuns, rs.min, rs.median, rs.max, 14.0 * rs.max / 1000.0);
        // Contended: a second pipeline restores the same 100 m scene on another thread at the same time.
        plugin::ScenePipeline other;
        other.prepare(96000.0, 512, false);
        std::vector<double> contended;
        for (int i = 0; i < 3; ++i)
        {
            pipe.beginRestore();
            pipe.restore(plugin::defaultScene(), smallValues);
            other.beginRestore();
            other.restore(plugin::defaultScene(), smallValues);
            std::thread t([&] {
                other.beginRestore();
                other.restore(sc, values);
            });
            const auto t0 = Clock::now();
            pipe.beginRestore();
            pipe.restore(sc, values);
            contended.push_back(ms(t0, Clock::now()));
            t.join();
        }
        const auto cs = spread(contended);
        std::printf("05h-records restore %-26s 96 kHz contended (another pipeline solving the same room): min %.0f median "
                    "%.0f worst %.0f ms (3 runs)\n",
                    key, cs.min, cs.median, cs.max);
    }
}

// AX38 (iv) record brought forward (D-H3 (e), K-e6): the worst quiesce() latency after a cancel issued at a random
// point during a builder rebuild of the gated 100 m cubes at 96 kHz. From the code, the cancel flag (BuildOptions::cancel)
// is checked only inside the diffuse solve, between 64-history blocks (DiffuseEstimator.cpp; AX39 D6); the ISM, the
// unit-decay synthesis (tail::BandNoiseGenerator) and the convolver's IR-set build have no cancel point, so a cancel that
// lands after the solve waits for the rest of the build. beginRestore() is quiesceBuilder() alone (the wait the host
// thread sees in reset(), setNonRealtime(true), prepare(), release() and restore()).
TEST_CASE("records: worst quiesce() latency after a cancel at random points of the 100 m / 96 kHz builder rebuild",
          "[.][benchmark][diffuse-quiesce]")
{
    constexpr int kRuns = 10;
    std::mt19937_64 rng(0x05E6);
    for (const char* key : {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3"})
    {
        const auto sc = cube(key);
        const auto values = module3d::parameterValuesFromScene(sc);
        plugin::ScenePipeline pipe;
        pipe.prepare(96000.0, 512, false);
        pipe.beginRestore();
        pipe.restore(sc, values);
        // The builder rebuild time, uncancelled (the range the cancel points are drawn from).
        const auto tb = Clock::now();
        pipe.setParameter(module3d::kListenerX, static_cast<float>(sc.listener.position.x + 0.5));
        while (!pipe.builderIdle())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        const double rebuild = ms(tb, Clock::now());
        std::vector<double> waits, delays;
        std::uniform_real_distribution<double> u(0.0, rebuild);
        for (int i = 0; i < kRuns; ++i)
        {
            pipe.beginRestore();
            pipe.restore(sc, values); // builder idle, IR current
            const double d = u(rng);
            pipe.setParameter(module3d::kListenerX, static_cast<float>(sc.listener.position.x + 0.5 + 0.01 * (i + 1)));
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(d));
            const auto t0 = Clock::now();
            pipe.beginRestore(); // = quiesceBuilder(): abandon flag, gate notify, wait for the in-flight build
            waits.push_back(ms(t0, Clock::now()));
            delays.push_back(d);
            pipe.restore(sc, values);
        }
        const auto ws = spread(waits);
        std::printf("05h-records quiesce %-26s 96 kHz: builder rebuild %.0f ms; cancel at a random point, %d runs: wait min "
                    "%.0f median %.0f worst %.0f ms\n",
                    key, rebuild, kRuns, ws.min, ws.median, ws.max);
        for (int i = 0; i < kRuns; ++i)
            std::printf("05h-records quiesce %-26s run %2d: cancel at %.0f ms of %.0f -> waited %.0f ms\n", key, i,
                        delays[static_cast<std::size_t>(i)], rebuild, waits[static_cast<std::size_t>(i)]);
    }
}

// AX38 (iv) records (subset): 1, 4 and 8 instances at the AQ10 room and at 100 m, 48 and 96 kHz: the time until the last
// instance is audible at project load (instances restored one after another on one host thread, as a host loads a
// project; the gate serialises their solves), and per-instance staleness when they rebuild together (one parameter change
// on every instance at once, the time from the change to each instance's submit; builders contend at the gate).
TEST_CASE("records: AX38 (iv) multi-instance load and staleness (1, 4, 8 instances)", "[.][benchmark][diffuse-records]")
{
    for (const auto& [label, sc] :
         std::vector<std::pair<std::string, contract::SceneDescription>>{{"AQ10 room", aq10Room()},
                                                                          {"cube100_lowalpha0.05_s0.3", cube("cube100_lowalpha0.05_s0.3")}})
        for (const double fs : {48000.0, 96000.0})
            for (const int instances : {1, 4, 8})
            {
                std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
                for (int i = 0; i < instances; ++i)
                    pipes.push_back(std::make_unique<plugin::ScenePipeline>());
                const auto values = module3d::parameterValuesFromScene(sc);
                const auto t0 = Clock::now();
                for (auto& p : pipes)
                {
                    p->prepare(fs, 512, false);
                    p->beginRestore();
                    p->restore(sc, values); // synchronous: audible when restore() returns
                }
                const double load = ms(t0, Clock::now());
                // Staleness: every instance changes one parameter at once; wait until all builders are idle.
                const auto t1 = Clock::now();
                for (auto& p : pipes)
                    p->setParameter(module3d::kListenerX, static_cast<float>(sc.listener.position.x + 0.5));
                std::vector<double> stale(static_cast<std::size_t>(instances), 0.0);
                std::vector<bool> done(static_cast<std::size_t>(instances), false);
                for (;;)
                {
                    bool all = true;
                    for (std::size_t i = 0; i < pipes.size(); ++i)
                    {
                        if (!done[i] && pipes[i]->builderIdle())
                        {
                            done[i] = true;
                            stale[i] = ms(t1, Clock::now());
                        }
                        all = all && done[i];
                    }
                    if (all)
                        break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                const auto ss = spread(stale);
                std::printf("05h-records (iv) %-26s %6.0f Hz, %d instances: load until the last is audible %.0f ms; staleness "
                            "when rebuilding together min %.0f median %.0f max %.0f ms\n",
                            label.c_str(), fs, instances, load, ss.min, ss.median, ss.max);
            }
}

// AX43 "reported, not gated" set (phase-05h scope 4, before the goldens): the layout 4/5 near-wall cases (listener at
// a wall, an edge and a corner at 0.1 m; emitter at a wall), W1, club and living_room both-near at 0.1, 0.3 and 0.5 m
// (listener dd from its nearest wall, emitter 0 dd from the opposite wall along y), each with the shipping rule as
// built: n*, N, flags, achieved SE, VOV_union, U per emitter; W1 both_corner asserts the cap flag (Seat 5, AX44).
TEST_CASE("records: the AX43 reported set (near-wall and both-near placements) and W1 both_corner's cap flag",
          "[.][benchmark][diffuse-reported-set]")
{
    struct Row
    {
        std::string name;
        contract::SceneDescription scene;
        bool assertCapHit = false;
    };
    std::vector<Row> rows;
    const auto layout = [](int which) {
        std::array<contract::BandArray, 6> alpha{};
        for (auto& a : alpha)
            a.fill(0.01); // Table 5.2's rigid faces at the contract minimum (the (A) references use 0)
        alpha[which == 4 ? 4 : 0].fill(1.0); // layout 4: absorbing floor; layout 5: absorbing xMin wall
        return alpha;
    };
    std::array<double, 6> s1{};
    s1.fill(1.0);
    const contract::Vec3 D{20.0, 30.0, 10.0};
    const contract::Vec3 S0{7.0, 20.0, 2.0}, S1{13.0, 20.0, 2.0}, R0{10.0, 8.0, 1.7};
    for (const int L : {4, 5})
    {
        const std::string pre = "layout" + std::to_string(L) + "_s1/";
        rows.push_back({pre + "listener_wall", diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {S0, S1})});
        rows.push_back({pre + "listener_edge", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 1.7}, {S0, S1})});
        rows.push_back({pre + "listener_corner", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 9.9}, {S0, S1})});
        rows.push_back({pre + "emitter_wall", diffuse_test::scene(D, layout(L), s1, R0, {{7.0, 29.9, 2.0}, S1})});
        rows.push_back({pre + "both_wall", diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {{7.0, 29.9, 2.0}, S1})});
        rows.push_back({pre + "both_corner", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 0.1}, {{19.9, 29.9, 9.9}, S1})});
    }
    std::array<contract::BandArray, 6> aq{};
    aq.fill({0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3});
    std::array<double, 6> s03{};
    s03.fill(0.3);
    rows.push_back({"W1/both_corner", diffuse_test::scene(D, aq, s03, {0.1, 0.1, 0.1}, {{19.9, 29.9, 9.9}, S1}), true});
    for (const double dd : {0.1, 0.3, 0.5})
        rows.push_back({"W1/both_wall_" + std::to_string(dd).substr(0, 3),
                        diffuse_test::scene(D, aq, s03, {10.0, dd, 1.7}, {{7.0, 30.0 - dd, 2.0}, S1})});
    for (const char* room : {"club.json", "living_room.json"})
        for (const double dd : {0.1, 0.3, 0.5})
        {
            auto sc = pipeline_test::loadScene(room);
            const double dy = sc.room.geometry.dimensions.y, dx = sc.room.geometry.dimensions.x;
            auto wall = sc;
            wall.listener.position.y = dd;
            wall.emitters[0].position.y = dy - dd;
            rows.push_back({std::string(room).substr(0, std::string(room).find('.')) + "/both_wall_" + std::to_string(dd).substr(0, 3), wall});
            auto edge = wall;
            edge.listener.position.x = dd;
            edge.emitters[0].position.x = dx - dd;
            rows.push_back({std::string(room).substr(0, std::string(room).find('.')) + "/both_edge_" + std::to_string(dd).substr(0, 3), edge});
        }
    for (const auto& row : rows)
    {
        const auto planned = diffuse_test::plan(row.scene);
        const auto r = estimateDiffuse(planned.problem);
        std::printf("05h-reported %-28s n* %lld N %lld N_cap %lld cap hit %d floor truncated %d pilot floor %d pilot shipped %d",
                    row.name.c_str(), static_cast<long long>(r.nStar), static_cast<long long>(r.count.n),
                    static_cast<long long>(r.count.nCap), r.count.capHit ? 1 : 0, r.count.floorTruncated ? 1 : 0,
                    r.count.pilotFloor ? 1 : 0, r.count.pilotShipped ? 1 : 0);
        for (std::size_t e = 0; e < r.emitters.size(); ++e)
            std::printf(" | e%zu SE %.3f dB VOV_union %.3f both-near %d U %d", e, r.emitters[e].achievedSeDb,
                        r.emitters[e].vovUnion, r.emitters[e].bothNear ? 1 : 0, r.emitters[e].approximate ? 1 : 0);
        std::printf("\n");
        if (row.assertCapHit)
            REQUIRE(r.count.capHit); // Seat 5 (AX44): W1 both_corner asserts the cap flag
    }
}
