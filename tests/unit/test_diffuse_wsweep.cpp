// Phase 07c-2, facts F3 / F4 / F12 of docs/review/phase-07c-2/1-decider-convening.md: the diffuse solve at
// W_max x {1, 2, 4, 5, 6, 7, 8, 16}. VALIDATION ONLY: no shipped code path or constant changes. The override
// is the existing DiffuseLimits::wScene field (W_scene = 2 W_max, AX41), set here to 2 x
// kWMaxPerEmitterProvisional x the multiplier; nothing else of the shipping rule (n*_max, SE target, pilot,
// joint rule) is touched. Hidden; prints records only, asserts nothing but D4 (the result is independent of
// the thread count). The diffuse problem has no sample rate: diffuse_test::plan (the planEmitter mirror)
// builds it from the scene alone, so these solves are the ones the 48 and 96 kHz builds run.
#include "DiffuseTestUtil.h"

#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace sim::diffuse;

namespace {

using Clock = std::chrono::steady_clock;
double ms(Clock::time_point a, Clock::time_point b)
{
    return std::chrono::duration<double, std::milli>(b - a).count();
}

constexpr int kMultipliers[] = {1, 2, 4, 5, 6, 7, 8, 16}; // 5-7: M2 (decider file 5)

DiffuseLimits limitsAt(int mult)
{
    DiffuseLimits lim;
    lim.wScene = 2 * kWMaxPerEmitterProvisional * static_cast<std::int64_t>(mult);
    return lim;
}

// The 100 m cubes, as tests/unit/test_diffuse_records.cpp cube() builds them.
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

struct Named
{
    std::string name;
    contract::SceneDescription scene;
};

// Layouts 4 / 5 at s = 1, as the AX43 reported set of test_diffuse_records.cpp builds them (20 x 30 x 10 m,
// faces 0.01, layout 4: absorbing floor, layout 5: absorbing xMin wall; two emitters), plus the default
// placement (listener R0, emitters S0 / S1) the reported set does not list.
std::vector<Named> layoutScenes()
{
    const auto layout = [](int which) {
        std::array<contract::BandArray, 6> alpha{};
        for (auto& a : alpha)
            a.fill(0.01);
        alpha[which == 4 ? 4 : 0].fill(1.0);
        return alpha;
    };
    std::array<double, 6> s1{};
    s1.fill(1.0);
    const contract::Vec3 D{20.0, 30.0, 10.0};
    const contract::Vec3 S0{7.0, 20.0, 2.0}, S1{13.0, 20.0, 2.0}, R0{10.0, 8.0, 1.7};
    std::vector<Named> out;
    for (const int L : {4, 5})
    {
        const std::string pre = "layout" + std::to_string(L) + "_s1/";
        out.push_back({pre + "default", diffuse_test::scene(D, layout(L), s1, R0, {S0, S1})});
        out.push_back(
            {pre + "listener_wall", diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {S0, S1})});
        out.push_back(
            {pre + "listener_edge", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 1.7}, {S0, S1})});
        out.push_back(
            {pre + "listener_corner", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 9.9}, {S0, S1})});
        out.push_back(
            {pre + "emitter_wall", diffuse_test::scene(D, layout(L), s1, R0, {{7.0, 29.9, 2.0}, S1})});
        out.push_back({pre + "both_wall",
                       diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {{7.0, 29.9, 2.0}, S1})});
        out.push_back({pre + "both_corner",
                       diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 0.1}, {{19.9, 29.9, 9.9}, S1})});
    }
    return out;
}

// Linux: VmRSS / VmHWM (kB) from /proc/self/status; writing "5" to /proc/self/clear_refs resets VmHWM to the
// current RSS (Linux >= 4.0). -1 where not readable.
long statusKb(const char* field)
{
    std::ifstream in("/proc/self/status");
    std::string line;
    const std::string key = std::string(field) + ":";
    while (std::getline(in, line))
        if (line.rfind(key, 0) == 0)
            return std::stol(line.substr(key.size()));
    return -1;
}
bool resetPeak()
{
    std::ofstream out("/proc/self/clear_refs");
    if (!out)
        return false;
    out << "5";
    out.flush();
    return static_cast<bool>(out);
}

double totalDb(const DiffuseProblem& pr, const DiffuseResult& r, std::size_t e, std::size_t b)
{
    return 10.0 * std::log10(pr.emitters[e].bandsSpecularTarget[b] + r.emitters[e].bandsDiffuse[b]);
}

} // namespace

TEST_CASE(
    "wmax-sweep: the diffuse solve at W_max x {1, 2, 4, 5, 6, 7, 8, 16} (F3 time and memory, F4 accuracy)",
    "[.][wmax-sweep]")
{
    ThreadPool& pool = ThreadPool::process();
    ThreadPool single(1);
    std::printf("wsweep machine: process pool %u threads (hardware_concurrency); single-thread pool %u\n",
                pool.size(), single.size());
    std::vector<Named> scenes;
    for (const char* key :
         {"cube100_lowalpha0.05_s0.3", "cube100_flutter_fallback", "cube100_lowalpha0.05_s1"})
        scenes.push_back({key, cube(key)});
    for (auto& n : layoutScenes())
        scenes.push_back(std::move(n));
    constexpr int kTimedRuns = 3;
    for (const auto& sn : scenes)
    {
        const auto planned = diffuse_test::plan(sn.scene);
        const auto& pr = planned.problem;
        (void)estimateDiffuse(pr, limitsAt(1)); // warm-up (lattice, pool threads, page faults)
        std::map<int, DiffuseResult> byMult;
        for (const int mult : kMultipliers)
        {
            const auto lim = limitsAt(mult);
            // Peak RSS delta of one pool solve (Linux).
            const long rss0 = statusKb("VmRSS");
            const bool peakOk = resetPeak();
            DiffuseResult res;
            std::vector<double> tPool;
            for (int i = 0; i < kTimedRuns; ++i)
            {
                const auto t0 = Clock::now();
                res = estimateDiffuse(pr, lim);
                tPool.push_back(ms(t0, Clock::now()));
            }
            const long hwm = statusKb("VmHWM");
            const auto t0 = Clock::now();
            DiffuseRunOptions one;
            one.pool = &single;
            const auto res1 = estimateDiffuse(pr, lim, one);
            const double tSingle = ms(t0, Clock::now());
            REQUIRE(res1.faceHash == res.faceHash); // D4: independent of the thread count
            REQUIRE(res1.count.n == res.count.n);
            std::sort(tPool.begin(), tPool.end());
            const double work = static_cast<double>(res.wPilot + res.wFinal);
            char rssBuf[64];
            if (peakOk && rss0 >= 0 && hwm >= 0)
                std::snprintf(rssBuf, sizeof rssBuf, "%.1f MB", static_cast<double>(hwm - rss0) / 1024.0);
            else
                std::snprintf(rssBuf, sizeof rssBuf, "not measured");
            std::printf(
                "wsweep %-28s x%-2d W_max %lld W_scene %lld | pool(%u) min %.1f median %.1f worst %.1f ms "
                "(%d runs); single-thread %.1f ms; ns/eval pool %.2f single %.2f | peak RSS delta %s | "
                "n* %lld W_pilot %lld N_need %lld N_cap %lld N %lld cap hit %d floor truncated %d pilot "
                "shipped %d | W_final %lld realised/W_scene %.4f\n",
                sn.name.c_str(), mult, static_cast<long long>(lim.wScene / 2),
                static_cast<long long>(lim.wScene), pool.size(), tPool.front(), tPool[tPool.size() / 2],
                tPool.back(), kTimedRuns, tSingle, 1e6 * tPool[tPool.size() / 2] / work, 1e6 * tSingle / work,
                rssBuf, static_cast<long long>(res.nStar), static_cast<long long>(res.wPilot),
                static_cast<long long>(res.nNeed), static_cast<long long>(res.count.nCap),
                static_cast<long long>(res.count.n), res.count.capHit ? 1 : 0,
                res.count.floorTruncated ? 1 : 0, res.count.pilotShipped ? 1 : 0,
                static_cast<long long>(res.wFinal), res.realisedWorkRatio());
            for (std::size_t e = 0; e < res.emitters.size(); ++e)
            {
                const auto& er = res.emitters[e];
                std::printf(
                    "wsweep %-28s x%-2d e%zu achieved SE %.3f dB VOV_union %.3f U %d | SE dB per band",
                    sn.name.c_str(), mult, e, er.achievedSeDb, er.vovUnion, er.approximate ? 1 : 0);
                for (std::size_t b = 0; b < 8; ++b)
                    std::printf(" %.3f", er.bandsSeDb[b]);
                std::printf(" | VOV per band");
                for (std::size_t b = 0; b < 8; ++b)
                    std::printf(" %.3f", er.bandsVov[b]);
                std::printf("\n");
            }
            byMult[mult] = std::move(res);
        }
        // Estimate drift against the x16 solve (total = specular + diffuse, dB, per band), per emitter.
        const auto& top = byMult[16];
        for (const int mult : kMultipliers)
            for (std::size_t e = 0; e < top.emitters.size(); ++e)
            {
                std::printf("wsweep %-28s x%-2d e%zu total minus x16 total, dB per band", sn.name.c_str(),
                            mult, e);
                for (std::size_t b = 0; b < 8; ++b)
                    std::printf(" %+.3f", totalDb(pr, byMult[mult], e, b) - totalDb(pr, top, e, b));
                std::printf("\n");
            }
    }
}

// F4: the clause (d) replicate form of test_diffuse_records.cpp ("records: clause (d) replicates"): 30
// replicates of the shipping rule on disjoint streams against one long run, at the two gated cubes, at
// multipliers 1, 4 and 16. The stride grows past 2^20 when N + 8 000 would overrun it, and the long run sits
// beyond every replicate's range.
TEST_CASE("wmax-sweep: 30-replicate p95 at the gated cubes at W_max x {1, 4, 16}", "[.][wmax-sweep]")
{
    constexpr int kReplicates = 30;
    for (const char* key : {"cube100_lowalpha0.05_s0.3", "cube100_flutter_fallback"})
    {
        const auto planned = diffuse_test::plan(cube(key));
        const auto& pr = planned.problem;
        const auto top = estimateDiffuse(pr, limitsAt(16));
        std::int64_t stride = std::int64_t{1} << 20;
        while (stride < kFinalRangeStart + top.count.n + kBlockHistories)
            stride *= 2;
        DiffuseLimits longRun;
        longRun.fixedStart = stride * (kReplicates + 2);
        longRun.fixedHistories = std::int64_t{1} << 20;
        const auto t0 = Clock::now();
        const auto ref = estimateDiffuse(pr, longRun);
        const double tLong = ms(t0, Clock::now());
        for (const int mult : {1, 4, 16})
        {
            const auto t1 = Clock::now();
            std::array<std::vector<double>, 2> errDb, seDb;
            for (int r = 0; r < kReplicates; ++r)
            {
                auto lim = limitsAt(mult);
                lim.historyOffset = static_cast<std::int64_t>(r) * stride;
                const auto res = estimateDiffuse(pr, lim);
                for (std::size_t e = 0; e < 2; ++e)
                {
                    errDb[e].push_back(totalDb(pr, res, e, 4) - totalDb(pr, ref, e, 4));
                    seDb[e].push_back(res.emitters[e].achievedSeDb);
                }
            }
            const double tRep = ms(t1, Clock::now());
            for (std::size_t e = 0; e < 2; ++e)
            {
                std::vector<double> a(errDb[e].size());
                std::transform(errDb[e].begin(), errDb[e].end(), a.begin(),
                               [](double x) { return std::abs(x); });
                std::sort(a.begin(), a.end());
                const double p95 =
                    a[static_cast<std::size_t>(std::ceil(0.95 * static_cast<double>(a.size()))) - 1];
                auto sorted = errDb[e];
                std::sort(sorted.begin(), sorted.end());
                const double median = 0.5 * (sorted[(sorted.size() - 1) / 2] + sorted[sorted.size() / 2]);
                auto se = seDb[e];
                std::sort(se.begin(), se.end());
                std::printf(
                    "wsweep-replicates %-26s x%-2d e%zu: 30 replicates at 1 kHz vs long run (2^20 "
                    "histories from %lld, SE %.3f dB, %.0f ms; stride %lld): median %+.3f dB, p95 |error| "
                    "%.3f dB, max |error| %.3f dB; achieved SE median %.3f dB; replicates took %.0f ms\n",
                    key, mult, e, static_cast<long long>(longRun.fixedStart), ref.emitters[e].bandsSeDb[4],
                    tLong, static_cast<long long>(stride), median, p95, a.back(),
                    0.5 * (se[(se.size() - 1) / 2] + se[se.size() / 2]), tRep);
            }
        }
    }
}
