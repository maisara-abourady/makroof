// Phase 05h, scope 6 and D-H1 (AX38 4b / 4c / (iv), AX41, Seat 1's clause (d)): the records of the switched
// build. Hidden: CI runs them from the Release build with "[benchmark]". Recorded, not gated, except where
// the plan pins a gate (docs/review/phase-05h/, decisions D-H1 and RG-1): the gated-scene flags, the
// realised-work ratio, the W_pilot / W_final pins, the unit-decay length and synthesis FFT size per gated
// scene, the flutter scene's 14 x worst-of-10 restore <= 30 s and, in a +-5 % flutter window on x64, the
// low-alpha restore's growth bound are asserted in "[diffuse-records]"; everything else is printed.
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "contract/Json.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/DiffuseSolveGate.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Fft.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"
#include "sim/ism/BandRenderer.h"
#include "sim/tail/Decay.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <map>
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

// Register of the AX38 4c restore gate at the pinned W_max 3.05 M (D-H1 (v), file 19; recorded values from
// docs/review/phase-05h/1-orchestrator-cpp-costs.md §4, 96 kHz, worst-of-10 restore + worst solve; the
// baselines are the means of the measured CI runs named in tests/golden/CHANGELOG.md, RG-1). Only the two
// gated builds have entries.
#if defined(_WIN32)
constexpr const char* kOsName = "Windows";
#elif defined(__APPLE__)
constexpr const char* kOsName = "macOS";
#else
constexpr const char* kOsName = "Linux";
#endif
struct GateEntry
{
    const char* scene;
    const char* os;
    double recorded14xS; // 14 x (worst restore + worst solve), s: the register's recorded value (printed)
    // DECISION RG-1 (docs/review/phase-05h/64, 66; interrogator 65, 67): on GitHub-hosted runners the gate
    // asserts what is runner-independent and prints what is not. baselineMedianMs = the mean of the
    // in-window runs on file (Linux 2043/2092, Windows 2000/2056; macOS 1849/1887/1715, print only);
    // baselineRatio = the mean low-alpha / flutter restore-median ratio of the measured runs on file;
    // flutterRefMs = the mean flutter restore median of those runs (the runner-speed reference);
    // absoluteAsserted = the in-window growth bound is a REQUIRE (x64), else a print (macOS until Phase 13).
    // Runs: 42909003931, 42924781618, 42935789745, 42949252041 (Windows also 42942694523; macOS the last
    // three). Re-pinned only when the restore path changes: one run PROVISIONAL, >= 3 runs with a CHANGELOG
    // reason (tests/golden/CHANGELOG.md, not a golden).
    double baselineMedianMs;
    double baselineRatio;
    double flutterRefMs;
    bool absoluteAsserted;
    bool listed;       // in the AX38 4c defect register (plan text); false once closed under (c): print only
    bool strict30s;    // the strict 14 x worst <= 30 s REQUIRE: the flutter scene only (interrogator file 69
                       // item 2: an entry leaving the register under section 5 (c) never re-arms it on the
                       // low-alpha scene)
    double solveRefMs; // phase-05i Q5 (docs/review/phase-05i/9, Seat 5 file 8): the scene's solve-median
                       // baseline, the mean of the in-window runs only (phase-05i 3.3 (v)): Linux and macOS
                       // run 43007183782; Windows runs 42964823518 and 43007183782
    int solveRefRuns;  // runs behind solveRefMs; below 3 the bound prints PROVISIONAL
};
// RG-1 constants (provenance: docs/review/phase-05h/56 table, 64, 66).
constexpr double kGrowth = 1.10;    // median-of-10 restore <= kGrowth x baselineMedianMs, in-window, x64
constexpr double kGuardPct = 5.0;   // the run's flutter median within +-5 % of flutterRefMs (Seat 7 r2)
constexpr double kRatioWarn = 1.20; // low-alpha / flutter ratio above kRatioWarn x baselineRatio: WARNING
// phase-05i Q5: a scene's solve median above kSolveWarn x solveRefMs prints SOLVE in that scene's warnings=;
// one-sided (the work pins are asserted), never asserted on hosted runners, never a (d) trigger; kept apart
// from kRatioWarn so the 07c re-pin re-derives each from >= 3 in-window runs.
constexpr double kSolveWarn = 1.20;
// macOS trigger (RG-1 round 4, Seat 5 file 57 r3): two consecutive macOS runs with the low-alpha median above
// 1.15 x the mean of the four measured macOS medians (2106 / 1849 / 1887 / 1715 -> 1889; 0 of 4 rows over)
// are a (d) defect through /fix-plan; read by the orchestrator from the GATE lines, no state in the test.
// Re-derived at the 07c re-pin.
constexpr double kMacGrowthTriggerMs = 2172.0;
constexpr std::size_t kFftSizeLowAlpha96k =
    2097152; // [probe-restore-split], 2026-11-11: 1152000 + 2 x 15697 -> 2^21
constexpr std::size_t kFftSizeFlutter96k = 524288; // 377517 + 2 x 15697 -> 2^19
constexpr GateEntry kGateRegister[] = {
    // The flutter scene: strict 14 x worst <= 30 s on every OS (headroom >= 2.3x, Seat 5); no growth bound.
    {"cube100_flutter_fallback", "Linux", 10.59, 0.0, 0.0, 0.0, false, false, true, 131.2, 1},
    {"cube100_flutter_fallback", "macOS", 7.59, 0.0, 0.0, 0.0, false, false, true, 102.7, 1},
    {"cube100_flutter_fallback", "Windows", 9.65, 0.0, 0.0, 0.0, false, false, true, 144.4, 2},
    // The gated low-alpha cube. macOS is listed (recorded 33.40 s, local / file 1; remedy phase-07c
    // conditions 9-10). Linux (30.27 s local / file 1) and Windows (36.73 s on CI run 42942694523's slow
    // runner, file 53) closed under AX38 4c (c) on phase 05i's runs (docs/review/phase-05i/9): print only.
    {"cube100_lowalpha0.05_s0.3", "Linux", 30.27, 2068.0, 3.05, 701.0, true, false, false, 80.9, 1},
    {"cube100_lowalpha0.05_s0.3", "macOS", 33.40, 1817.0, 3.75, 484.0, false, true, false, 83.7, 1},
    {"cube100_lowalpha0.05_s0.3", "Windows", 36.73, 2028.0, 2.83, 737.0, true, false, false, 90.4, 2},
};
const GateEntry* gateRegisterEntry(const std::string& scene)
{
    for (const auto& e : kGateRegister)
        if (scene == e.scene && std::string(kOsName) == e.os)
            return &e;
    return nullptr;
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
    return diffuse_test::scene({20.0, 30.0, 10.0}, alpha, s, {10.0, 8.0, 1.7},
                               {{7.0, 20.0, 2.0}, {13.0, 20.0, 2.0}});
}

// Peak resident set (Linux: VmHWM from /proc/self/status, kB; 0 elsewhere).
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

// Seat 1's clause (d) (phase-05h §3; AX38 4c Trigger 1): 30 replicates of the shipping rule (pilot + joint
// rule + final range, as built) on disjoint pre-registered streams (replicate r uses histories offset by r ×
// 2^20, pilot and final alike) against a long run (2^20 histories on the range [2^26, 2^26 + 2^20)), per
// gated cube: median and p95 |error| at 1 kHz per emitter (C15's rule: |median| ≤ 0.25 dB and p95 ≤ 1 dB),
// the replicate SD of the achieved SE and of the estimate (the starting-state spread Trigger 1's "any further
// rise" is read against).
TEST_CASE("records: clause (d) replicates of the shipping rule at the gated cubes (30 disjoint streams vs a "
          "long run)",
          "[.][benchmark][diffuse-replicates]")
{
    constexpr int kReplicates = 30;
    constexpr std::int64_t kStride = std::int64_t{1} << 20;
    for (const char* key :
         {"cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1", "cube100_flutter_fallback"})
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
                const double tot = planned.problem.emitters[e].bandsSpecularTarget[4]
                                   + res.emitters[e].bandsDiffuse[4];
                const double tref = planned.problem.emitters[e].bandsSpecularTarget[4]
                                    + ref.emitters[e].bandsDiffuse[4];
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
            // Trigger 1 starting state (D-H1 (ii), file 19; the record of
            // docs/review/phase-05h/10-orchestrator- clause-d-replicates.md, C++ shipping rule, 30 disjoint
            // streams, 1 kHz, Linux Release): the fixed-key achieved SE and the replicate p95 per gated scene
            // and emitter. A record, not a golden: a rise of the achieved SE >= 0.05 dB or of the p95 >= 0.10
            // dB above it is RECORDED here (a flagged line), never a CHECK; the escalations (SE crossing 0.33
            // dB, p95 crossing 1 dB) go to Maisara via phase-05h §2 item 1. Re-pinned with a CHANGELOG reason
            // whenever W_max or n*_max is re-derived (Seat 5, file 17).
            struct Start
            {
                const char* scene;
                double seDb[2];
                double p95Db[2];
            };
            constexpr Start kStart[] = {{"cube100_lowalpha0.05_s0.3", {0.117, 0.115}, {0.250, 0.178}},
                                        {"cube100_lowalpha0.05_s1", {0.381, 0.384}, {0.701, 0.810}},
                                        {"cube100_flutter_fallback", {0.002, 0.002}, {0.003, 0.005}}};
            for (const auto& s : kStart)
                if (std::string(key) == s.scene)
                {
                    const double seNow = spread(seDb).median;
                    const bool riseSe = seNow >= s.seDb[e] + 0.05, riseP95 = p95 >= s.p95Db[e] + 0.10;
                    std::printf("05h-replicates trigger-1 %s e%zu: starting state SE %.3f p95 %.3f dB; now "
                                "SE %.3f p95 %.3f dB%s%s\n",
                                key, e, s.seDb[e], s.p95Db[e], seNow, p95,
                                (riseSe || riseP95) ? "  RECORDED RISE (Trigger 1 record, not a failure)"
                                                    : "",
                                (seNow > 0.33 || p95 > 1.0) ? "  ESCALATE (phase-05h §2 item 1)" : "");
                }
            std::printf(
                "05h-replicates %s e%zu: 30 replicates at 1 kHz vs long run (2^20 histories, SE %.3f dB, "
                "%.0f ms): "
                "median %+.3f dB, p95 |error| %.3f dB, max |error| %.3f dB, SD of error %.3f dB; achieved SE "
                "median %.3f dB (SD %.4f); VOV_union median %.3f (SD %.3f); clause (d) %s\n",
                key, e, ref.emitters[e].bandsSeDb[4], tLong, es.median, p95, absErr.back(), sd(errDb),
                spread(seDb).median, sd(seDb), spread(vov).median, sd(vov),
                (std::abs(es.median) <= 0.25 && p95 <= 1.0) ? "met" : "NOT met");
        }
    }
}

// AX38 4b / 4c records: full rebuilds (noise generated) and position-only rebuilds (cached unit decays), both
// with the diffuse solve, at 48 and 96 kHz: the six Phase 04 rooms, the AQ10 room, both 100 m cases; W1/W2
// with the diffuse share; the peak working-set delta of the gated 100 m, 96 kHz builds (Linux); the
// synchronous restore at 100 m and 96 kHz with the solve (14 × t_restore against 30 s, worst of 10) and
// contended (a second pipeline solving the 100 m room at the same time).
TEST_CASE("records: AX38 4b/4c rebuilds, memory and the 100 m / 96 kHz restore with the diffuse solve",
          "[.][benchmark][diffuse-records]")
{
    constexpr int kRuns = 10;
    // RG-1 (decider files 64/66): per-scene figures of this run, read after the scene loop (the flutter scene
    // is the runner-speed reference of the low-alpha entry's guarded growth bound).
    struct SceneRecord
    {
        Spread restore{};
        double fullRebuildMedianMs = 0.0;
        double solveMedianMs = 0.0;
        double nsPerEval = 0.0;
    };
    std::map<std::string, SceneRecord> records;
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
    for (const char* name : {"dead_booth.json", "living_room.json", "classroom.json", "club.json",
                             "concert_hall_box.json", "stone_box.json"})
        for (const double fs : {48000.0, 96000.0})
        {
            const auto sp = full(pipeline_test::loadScene(name), fs, 3);
            std::printf(
                "05h-records full rebuild %-22s %6.0f Hz: min %.0f median %.0f max %.0f ms (3 runs)\n", name,
                fs, sp.min, sp.median, sp.max);
        }
    for (const double fs : {48000.0, 96000.0})
    {
        const auto sp = full(aq10Room(), fs, 3);
        std::printf(
            "05h-records full rebuild AQ10 room          %6.0f Hz: min %.0f median %.0f max %.0f ms\n", fs,
            sp.min, sp.median, sp.max);
    }
    for (const char* key :
         {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1"})
    {
        const auto sc = cube(key);
        for (const double fs : {48000.0, 96000.0})
        {
            // AX38 (i)/4c transient peak: RSS sampled every 2 ms by a sampler thread during the builds
            // (steward round 10 G2: VmHWM is a process high-water mark that an earlier test in the same
            // process sets, so its delta read 0 MB); delta = max sampled RSS - RSS before. Gated on Linux (<=
            // 1 GB), recorded on macOS / Windows (currentRssKb() reads /proc and returns 0 elsewhere: the
            // line then says "n/a").
            const long rssBefore = currentRssKb();
            std::atomic<bool> sampling{true};
            std::atomic<long> rssMax{rssBefore};
            std::thread sampler([&] {
                while (sampling.load())
                {
                    const long r = currentRssKb();
                    long m = rssMax.load();
                    while (r > m && !rssMax.compare_exchange_weak(m, r))
                    {}
                    std::this_thread::sleep_for(std::chrono::milliseconds(2));
                }
            });
            const auto sp = full(sc, fs, 3);
            sampling.store(false);
            sampler.join();
            const double deltaMb = (rssMax.load() - rssBefore) / 1024.0;
            std::printf(
                "05h-records full rebuild %-26s %6.0f Hz: min %.0f median %.0f max %.0f ms; transient RSS "
                "delta %.0f MB (sampled max %ld kB, RSS before %ld kB)%s\n",
                key, fs, sp.min, sp.median, sp.max, deltaMb, rssMax.load(), rssBefore,
                rssBefore == 0 ? "  [RSS n/a on this OS: recorded, not gated]" : "");
            if (fs > 90000.0)
                records[key].fullRebuildMedianMs = sp.median;
            const bool gatedBuild = std::string(key) != "cube100_lowalpha0.05_s1" && fs > 90000.0;
#if defined(__linux__)
            if (gatedBuild && rssBefore > 0)
                REQUIRE(deltaMb
                        <= 1024.0); // AX38 (i): at most 1 GB transient per diffuse solve, gated on Linux
#else
            (void)gatedBuild;
#endif
        }
        // AX41 realised-work ratio, pre-registered 1.02 at each gated scene (D-H1 (iii), file 19); the
        // reported s = 1 cube prints it only.
        {
            sim::BuildOptions o;
            o.sampleRate = 96000.0;
            o.kind = sim::BuildOptions::Kind::Omni;
            sim::HybridDiagnostics diag;
            (void)sim::buildRoomIR(sc, o, &diag);
            for (std::size_t e = 0; e < diag.emitters.size(); ++e)
            {
                const auto& d = diag.emitters[e].match.diffuse;
                std::printf("05h-records work ratio %-26s e%zu: realised work / W_scene %.4f (W_pilot %lld, "
                            "W_final %lld, "
                            "W_scene %lld); achieved SE %.3f dB; fallback %s\n",
                            key, e, d.realisedWorkRatio, static_cast<long long>(d.wPilot),
                            static_cast<long long>(d.wFinal), static_cast<long long>(d.wScene),
                            d.achievedSeDb, diag.emitters[e].ismFallback ? "yes" : "no");
                if (gateRegisterEntry(key) != nullptr)
                {
                    REQUIRE(d.realisedWorkRatio <= 1.02);
                    // D-H1 (iii): W_pilot and W_final per gated scene pinned exactly (deterministic, D7), as
                    // constants with their provenance (this test's Release run, 2026-11-10, W_max 3.05 M,
                    // n*_max 1 024), re-pinned with a CHANGELOG reason at each W_max / n*_max change (steward
                    // round 10 G5: the constants form, as H3-F4 pins W1 both_corner; the D5 golden holds the
                    // valid fixtures).
                    const std::int64_t wPilotPinned = std::string(key) == "cube100_flutter_fallback"
                                                          ? 3154338
                                                          : 1696086;
                    const std::int64_t wFinalPinned = std::string(key) == "cube100_flutter_fallback"
                                                          ? 2547436
                                                          : 4348889;
                    REQUIRE(d.wPilot == wPilotPinned);
                    REQUIRE(d.wFinal == wFinalPinned);
                }
            }
            if (gateRegisterEntry(key) != nullptr)
            {
                // RG-1 work pins (runner-independent; Seats 2 and 3): the unit-decay length and the synthesis
                // FFT size n = nextPowerOfTwo(length + 2 maxHalfLength) of the 96 kHz build, exact, pinned
                // from the probe [probe-restore-split] (2026-11-11; re-pinned with a CHANGELOG reason). The
                // IFFT count itself is 4 per make() by construction (band count only).
                const auto decay = sim::tail::eyringDecay(sc.room);
                const sim::ism::OctaveFilterbank fb(96000.0);
                const std::size_t len = sim::tail::unitDecayLength(sim::tail::tailLengthS(decay), 96000.0);
                const std::size_t n = sim::Fft::nextPowerOfTwo(len + 2 * fb.maxHalfLength());
                // The generator's own transform size, not only the formula's value (review r3 major 1): a
                // change to how the synthesis pads or sizes its FFT breaks the pin.
                const sim::tail::BandNoiseGenerator generator(fb, len);
                const std::size_t nGenerator = generator.fftSize();
                const bool flutter = std::string(key) == "cube100_flutter_fallback";
                const std::size_t lenPinned = flutter ? 377517u : 1152000u;
                const std::size_t nPinned = flutter ? kFftSizeFlutter96k : kFftSizeLowAlpha96k;
                std::printf(
                    "05h-records work pin %-26s unit decay %zu samples (pinned %zu); synthesis FFT size "
                    "%zu, generator %zu (pinned %zu)\n",
                    key, len, lenPinned, n, nGenerator, nPinned);
                REQUIRE(len == lenPinned);
                REQUIRE(n == nPinned);
                REQUIRE(nGenerator == nPinned);
                // RG-1 solve print (no bound until >= 3 runs give its spread, through /fix-plan): the diffuse
                // solve alone at the shipping rule, median of 5, and its ns per image evaluation over
                // W_pilot + W_final of both emitters.
                const auto planned = diffuse_test::plan(sc);
                std::vector<double> solve;
                for (int i = 0; i < 5; ++i)
                {
                    const auto t0 = Clock::now();
                    (void)estimateDiffuse(planned.problem);
                    solve.push_back(ms(t0, Clock::now()));
                }
                std::int64_t work = 0;
                for (const auto& em : diag.emitters)
                    work += em.match.diffuse.wPilot + em.match.diffuse.wFinal;
                records[key].solveMedianMs = spread(solve).median;
                records[key].nsPerEval = work > 0
                                             ? records[key].solveMedianMs * 1e6 / static_cast<double>(work)
                                             : 0.0;
                std::printf("05h-records solve %-26s shipping rule, median of 5: %.1f ms; %.2f ns per image "
                            "evaluation over W_pilot + W_final %lld (print, RG-1)\n",
                            key, records[key].solveMedianMs, records[key].nsPerEval,
                            static_cast<long long>(work));
            }
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
        std::printf(
            "05h-records restore %-26s 96 kHz with the solve, %d runs: min %.0f median %.0f worst %.0f ms; "
            "14 x worst %.2f s (30 s)\n",
            key, kRuns, rs.min, rs.median, rs.max, 14.0 * rs.max / 1000.0);
        records[key].restore = rs;
        // AX38 4c blocking restore gate in the RG-1 form (decider files 64/66, interrogator 65/67; D-H1 (v)
        // amended for Maisara): on hosted runners the flutter scene's 14 x worst <= 30 s is asserted on every
        // OS; the low-alpha entry's growth bound is asserted in a +-5 % flutter window on x64 after the scene
        // loop (the GATE block runs after both scenes, whatever their order), everything else is printed with
        // WARNING. A broken assertion is a defect under (d): no re-run, no cut, no range change, no seam.
        if (const auto* entry = gateRegisterEntry(key))
        {
            const double fourteen = 14.0 * rs.max / 1000.0;
            if (entry->strict30s)
            {
                std::printf("05h-records restore gate %-26s %s: strict (recorded %.2f s <= 29.1 s): 14 x "
                            "worst %.2f s <= 30 s\n",
                            key, kOsName, entry->recorded14xS, fourteen);
                REQUIRE(fourteen <= 30.0);
            }
            else
                std::printf(
                    "05h-records restore gate %-26s %s: %s (recorded 14 x worst %.2f s); 14 "
                    "x worst now %.2f s%s; growth bound %s after the scene loop (RG-1)\n",
                    key, kOsName,
                    entry->listed ? "LISTED defect" : "register entry closed, hosted-runner form",
                    entry->recorded14xS, fourteen,
                    fourteen <= 30.0
                        ? (entry->listed ? "; WARNING PASSES30S: this entry now passes 30 s, remove it "
                                           "through /fix-plan"
                                         : "; passes 30 s (register entry closed under AX38 4c (c))")
                        : (entry->listed ? "; WARNING OVER30S (printed, not asserted on hosted runners)"
                                         : "; WARNING OVER30S on a closed register entry (printed, not "
                                           "asserted on hosted runners; name the run in the PR)"),
                    entry->absoluteAsserted ? "asserted in-window" : "reported only");
        }
        else
            std::printf("05h-records restore gate %-26s %s: reported set, not gated\n", key, kOsName);
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
        std::printf("05h-records restore %-26s 96 kHz contended (another pipeline solving the same room): "
                    "min %.0f median "
                    "%.0f worst %.0f ms (3 runs)\n",
                    key, cs.min, cs.median, cs.max);
    }
    // RG-1: the machine-readable GATE line per gated scene and the low-alpha entry's guarded growth bound.
    {
        const auto& fl = records["cube100_flutter_fallback"];
        const auto& la = records["cube100_lowalpha0.05_s0.3"];
        const auto* entry = gateRegisterEntry("cube100_lowalpha0.05_s0.3");
        REQUIRE(entry != nullptr);
        REQUIRE(fl.restore.median > 0.0);
        const double ratio = la.restore.median / fl.restore.median;
        const double flutterDevPct = 100.0 * (fl.restore.median / entry->flutterRefMs - 1.0);
        const bool inWindow = std::abs(flutterDevPct) <= kGuardPct;
        const double growthBound = kGrowth * entry->baselineMedianMs;
        const double fourteen = 14.0 * la.restore.max / 1000.0;
        const auto* flEntry = gateRegisterEntry("cube100_flutter_fallback");
        REQUIRE(flEntry != nullptr);
        const double flSolveWarnAt = kSolveWarn * flEntry->solveRefMs;
        const double laSolveWarnAt = kSolveWarn * entry->solveRefMs;
        const auto solveBasis = [](const GateEntry& e) {
            return e.solveRefRuns < 3 ? "PROVISIONAL" : "PINNED";
        };
        const std::string flWarnings = fl.solveMedianMs > flSolveWarnAt ? "SOLVE " : "";
        std::string warnings;
        if (ratio > kRatioWarn * entry->baselineRatio)
            warnings += "RATIO ";
        if (la.restore.median > growthBound)
            warnings += "GROWTH ";
        if (fourteen > 30.0)
            warnings += "OVER30S ";
        else
            warnings += "PASSES30S ";
        char status[64];
        if (!entry->absoluteAsserted)
            std::snprintf(status, sizeof(status), "reported-only");
        else if (inWindow)
            std::snprintf(status, sizeof(status), "asserted");
        else
            std::snprintf(status, sizeof(status), "not-evaluated(runner,flutter%+.1f%%)", flutterDevPct);
        std::printf("05h-records GATE os=%s scene=cube100_flutter_fallback x14worst=%.2f median=%.0f "
                    "fullRebuildMedian=%.0f solveMedianMs=%.1f solveWarnAt=%.1f solveBasis=%s(n=%d) "
                    "nsPerEval=%.2f status=asserted(30s) flutterRef=%.0f flutterDev=%+.1f%% warnings=%s\n",
                    kOsName, 14.0 * fl.restore.max / 1000.0, fl.restore.median, fl.fullRebuildMedianMs,
                    fl.solveMedianMs, flSolveWarnAt, solveBasis(*flEntry), flEntry->solveRefRuns,
                    fl.nsPerEval, entry->flutterRefMs, flutterDevPct, flWarnings.c_str());
        if (!entry->absoluteAsserted && la.restore.median > kMacGrowthTriggerMs)
            warnings += "MACTRIGGER ";
        if (la.solveMedianMs > laSolveWarnAt)
            warnings += "SOLVE ";
        std::printf(
            "05h-records GATE os=%s scene=cube100_lowalpha0.05_s0.3 ratio=%.3f ratioWarnAt=%.3f "
            "solveMedianMs=%.1f solveWarnAt=%.1f solveBasis=%s(n=%d) nsPerEval=%.2f x14worst=%.2f "
            "median=%.0f growthBound=%.0f fullRebuildMedian=%.0f status=%s trigger=%.0f warnings=%s\n",
            kOsName, ratio, kRatioWarn * entry->baselineRatio, la.solveMedianMs, laSolveWarnAt,
            solveBasis(*entry), entry->solveRefRuns, la.nsPerEval, fourteen, la.restore.median, growthBound,
            la.fullRebuildMedianMs, status, entry->absoluteAsserted ? 0.0 : kMacGrowthTriggerMs,
            warnings.c_str());
        if (entry->absoluteAsserted && inWindow)
            REQUIRE(la.restore.median <= growthBound);
    }
}

// AX38 (iv) record brought forward (D-H3 (e), K-e6): the worst quiesce() latency after a cancel issued at a
// random point during a builder rebuild of the gated 100 m cubes at 96 kHz. From the code, the cancel flag
// (BuildOptions::cancel) is checked only inside the diffuse solve, between 64-history blocks
// (DiffuseEstimator.cpp; AX39 D6); the ISM, the unit-decay synthesis (tail::BandNoiseGenerator) and the
// convolver's IR-set build have no cancel point, so a cancel that lands after the solve waits for the rest of
// the build. beginRestore() is quiesceBuilder() alone (the wait the host thread sees in reset(),
// setNonRealtime(true), prepare(), release() and restore()).
TEST_CASE(
    "records: worst quiesce() latency after a cancel at random points of the 100 m / 96 kHz builder rebuild",
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
            pipe.setParameter(module3d::kListenerX,
                              static_cast<float>(sc.listener.position.x + 0.5 + 0.01 * (i + 1)));
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(d));
            const auto t0 = Clock::now();
            pipe.beginRestore(); // = quiesceBuilder(): abandon flag, gate notify, wait for the in-flight
                                 // build
            waits.push_back(ms(t0, Clock::now()));
            delays.push_back(d);
            pipe.restore(sc, values);
        }
        const auto ws = spread(waits);
        std::printf("05h-records quiesce %-26s 96 kHz: builder rebuild %.0f ms; cancel at a random point, %d "
                    "runs: wait min "
                    "%.0f median %.0f worst %.0f ms\n",
                    key, rebuild, kRuns, ws.min, ws.median, ws.max);
        for (int i = 0; i < kRuns; ++i)
            std::printf("05h-records quiesce %-26s run %2d: cancel at %.0f ms of %.0f -> waited %.0f ms\n",
                        key, i, delays[static_cast<std::size_t>(i)], rebuild,
                        waits[static_cast<std::size_t>(i)]);
    }
}

// AX38 4c records (steward round 10 G3): (1) the AQ4 intervals derived from the measured rebuilds (R = the
// builder's position-only rebuild, which reuses the cached unit decays; "full" = a material / size rebuild)
// with P = 512 samples (ScenePipeline::kPartitionSize): R + 2P, about 2R + 2P, full + 2P against AQ4's 100 ms
// / 700 ms / 3 s; (2) the offline bounce of a 3-minute room-size automation at 100 m, 48 and 96 kHz, with its
// ratio to real time, taken at a rebuild step of one size change every 5 s of audio (36 steps; each stated
// with the record, AX38 (iv)); (3) callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders
// (other instances rebuilding the 100 m cube without pause while one real-time instance processes 64-sample
// blocks).
TEST_CASE(
    "records: AQ4 intervals, the 3-minute room-size bounce at 100 m, callback p99.9 with 1/4/8 builders",
    "[.][benchmark][diffuse-records-aq4]")
{
    const auto positionRebuildMs = [](const contract::SceneDescription& sc, double fs) {
        plugin::ScenePipeline pipe;
        pipe.prepare(fs, 512, false);
        pipe.beginRestore();
        pipe.restore(sc, module3d::parameterValuesFromScene(sc));
        std::vector<double> t;
        for (int i = 0; i < 3; ++i)
        {
            const auto t0 = Clock::now();
            pipe.setParameter(module3d::kListenerX,
                              static_cast<float>(sc.listener.position.x + 0.3 + 0.1 * i));
            while (!pipe.builderIdle())
                std::this_thread::sleep_for(std::chrono::microseconds(200));
            t.push_back(ms(t0, Clock::now()));
        }
        return spread(t).median;
    };
    const auto fullRebuildMs = [](const contract::SceneDescription& sc, double fs) {
        sim::BuildOptions o;
        o.sampleRate = fs;
        o.kind = sim::BuildOptions::Kind::Omni;
        std::vector<double> t;
        for (int i = 0; i < 3; ++i)
        {
            const auto t0 = Clock::now();
            (void)sim::buildRoomIR(sc, o);
            t.push_back(ms(t0, Clock::now()));
        }
        return spread(t).median;
    };
    for (const auto& [label, sc] : std::vector<std::pair<std::string, contract::SceneDescription>>{
             {"AQ10 room", aq10Room()}, {"cube100_lowalpha0.05_s0.3", cube("cube100_lowalpha0.05_s0.3")}})
        for (const double fs : {48000.0, 96000.0})
        {
            const double twoP = 2.0 * 512.0 / fs * 1000.0;
            const double R = positionRebuildMs(sc, fs), F = fullRebuildMs(sc, fs);
            std::printf("05h-records AQ4 %-26s %6.0f Hz: R (position-only, builder) %.0f ms, full rebuild "
                        "%.0f ms, 2P %.1f ms; "
                        "R + 2P %.0f ms (100 ms), 2R + 2P %.0f ms (700 ms), full + 2P %.0f ms (3 s)\n",
                        label.c_str(), fs, R, F, twoP, R + twoP, 2 * R + twoP, F + twoP);
        }
    // (2) the stepped 3-minute bounce at 100 m: offline pipeline, room width/depth/height stepping down 1 m
    // every 5 s of audio (36 rebuilds; the offline branch builds before the block whose scene changed, AX5 /
    // X11).
    for (const double fs : {48000.0, 96000.0})
    {
        const auto sc = cube("cube100_lowalpha0.05_s0.3");
        auto values = module3d::parameterValuesFromScene(sc);
        plugin::ScenePipeline pipe;
        pipe.prepare(fs, 512, true);
        pipe.beginRestore();
        pipe.restore(sc, values);
        std::vector<float> a(512, 0.1f), b(512, -0.1f);
        const float* const in[2] = {a.data(), b.data()};
        float* const out[2] = {a.data(), b.data()};
        const double seconds = 180.0;
        const std::int64_t blocks = static_cast<std::int64_t>(seconds * fs / 512.0);
        const std::int64_t stepEvery = static_cast<std::int64_t>(5.0 * fs / 512.0);
        int steps = 0;
        const auto t0 = Clock::now();
        for (std::int64_t k = 0; k < blocks; ++k)
        {
            if (k % stepEvery == 0 && k > 0)
            {
                ++steps;
                const float size = static_cast<float>(100.0 - steps);
                pipe.setParameter(module3d::kRoomW, size);
                pipe.setParameter(module3d::kRoomD, size);
                pipe.setParameter(module3d::kRoomH, size);
            }
            pipe.process(in, out, 512);
        }
        const double wall = ms(t0, Clock::now()) / 1000.0;
        std::printf("05h-records bounce 100 m cube %6.0f Hz: 3-minute offline bounce with the room size "
                    "stepping 1 m every 5 s "
                    "(%d rebuilds): %.1f s wall, ratio to real time %.2f x\n",
                    fs, steps, wall, wall / seconds);
    }
    // (3) callback p99.9 at host buffer 64 with 1 / 4 / 8 concurrent builders rebuilding the 100 m cube.
    for (const int builders : {1, 4, 8})
    {
        const double fs = 48000.0;
        const auto big = cube("cube100_lowalpha0.05_s0.3");
        const auto bigValues = module3d::parameterValuesFromScene(big);
        plugin::ScenePipeline rt;
        const auto room = aq10Room();
        rt.prepare(fs, 64, false);
        rt.beginRestore();
        rt.restore(room, module3d::parameterValuesFromScene(room));
        std::vector<std::unique_ptr<plugin::ScenePipeline>> others;
        for (int i = 0; i < builders; ++i)
        {
            others.push_back(std::make_unique<plugin::ScenePipeline>());
            others.back()->prepare(fs, 512, false);
            others.back()->beginRestore();
            others.back()->restore(big, bigValues);
        }
        std::atomic<bool> stop{false};
        std::thread churn([&] {
            float x = 50.0f;
            while (!stop.load())
            {
                x += 0.1f;
                for (auto& o : others)
                    o->setParameter(module3d::kListenerX,
                                    x); // a builder rebuild each time (position-only, cached decays)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
        std::vector<float> a(64, 0.1f), b(64, -0.1f);
        const float* const in[2] = {a.data(), b.data()};
        float* const out[2] = {a.data(), b.data()};
        std::vector<double> us;
        const double period = 64.0 / fs * 1e6;
        const auto tEnd = Clock::now() + std::chrono::seconds(10);
        while (Clock::now() < tEnd)
        {
            const auto c0 = Clock::now();
            rt.process(in, out, 64);
            us.push_back(std::chrono::duration<double, std::micro>(Clock::now() - c0).count());
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long>(period)));
        }
        stop.store(true);
        churn.join();
        std::sort(us.begin(), us.end());
        const double p999 = us[static_cast<std::size_t>(std::ceil(0.999 * us.size())) - 1];
        std::printf("05h-records callback p99.9 at host buffer 64 (%.0f us period), %d concurrent builder%s "
                    "at 100 m: p99.9 %.0f us, "
                    "max %.0f us over %zu callbacks (10 s)\n",
                    period, builders, builders == 1 ? "" : "s", p999, us.back(), us.size());
    }
}

// AX38 (iv) records (subset): 1, 4 and 8 instances at the AQ10 room and at 100 m, 48 and 96 kHz: the time
// until the last instance is audible at project load (instances restored one after another on one host
// thread, as a host loads a project; the gate serialises their solves), and per-instance staleness when they
// rebuild together (one parameter change on every instance at once, the time from the change to each
// instance's submit; builders contend at the gate).
TEST_CASE("records: AX38 (iv) multi-instance load and staleness (1, 4, 8 instances)",
          "[.][benchmark][diffuse-records]")
{
    for (const auto& [label, sc] : std::vector<std::pair<std::string, contract::SceneDescription>>{
             {"AQ10 room", aq10Room()}, {"cube100_lowalpha0.05_s0.3", cube("cube100_lowalpha0.05_s0.3")}})
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
                std::printf("05h-records (iv) %-26s %6.0f Hz, %d instances: load until the last is audible "
                            "%.0f ms; staleness "
                            "when rebuilding together min %.0f median %.0f max %.0f ms\n",
                            label.c_str(), fs, instances, load, ss.min, ss.median, ss.max);
            }
}

// AX43 "reported, not gated" set (phase-05h scope 4, before the goldens): the layout 4/5 near-wall cases
// (listener at a wall, an edge and a corner at 0.1 m; emitter at a wall), W1, club and living_room both-near
// at 0.1, 0.3 and 0.5 m (listener dd from its nearest wall, emitter 0 dd from the opposite wall along y),
// each with the shipping rule as built: n*, N, flags, achieved SE, VOV_union, U per emitter;
// layout4_s1/both_corner asserts the cap flag and W1 both_corner asserts U with its flags pinned (Seat 5,
// AX44, as read by D-H3 (d)).
TEST_CASE("records: the AX43 reported set (near-wall and both-near placements), the cap benchmark and W1 "
          "both_corner's flags",
          "[.][benchmark][diffuse-reported-set]")
{
    struct Row
    {
        std::string name;
        contract::SceneDescription scene;
        bool assertCapHit = false; // D-H3 (d): the cap benchmark, where the cap is a property of the rule
        bool assertU =
            false; // D-H3 (d): W1 both_corner asserts U (through the VOV leg) with its flags pinned
    };
    // W1 both_corner's flags at the pinned W_max 3.05 M / n*_max 1 024 (file 13; D-H3 (d) (e5)): pinned
    // exactly, like the gated scenes' pre-registered flags (AX41), so a change of the pilot's draw is
    // visible. The prototype's expectation (cap hit, N_cap 2 624) is not met by the C++ joint rule: the Q-3
    // work-count difference (the C++ counts every attempted image evaluation; N_cap 1 088), recorded once in
    // the 05h PR.
    struct PinnedFlags
    {
        std::int64_t nStar = 1024, n = 1024, nCap = 1088;
        bool capHit = false, floorTruncated = false;
    } const kW1BothCornerFlags;
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
        rows.push_back(
            {pre + "listener_wall", diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {S0, S1})});
        rows.push_back(
            {pre + "listener_edge", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 1.7}, {S0, S1})});
        rows.push_back(
            {pre + "listener_corner", diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 9.9}, {S0, S1})});
        rows.push_back(
            {pre + "emitter_wall", diffuse_test::scene(D, layout(L), s1, R0, {{7.0, 29.9, 2.0}, S1})});
        rows.push_back({pre + "both_wall",
                        diffuse_test::scene(D, layout(L), s1, {10.0, 0.1, 1.7}, {{7.0, 29.9, 2.0}, S1})});
        rows.push_back({pre + "both_corner",
                        diffuse_test::scene(D, layout(L), s1, {0.1, 0.1, 0.1}, {{19.9, 29.9, 9.9}, S1}),
                        L == 4}); // layout4_s1/both_corner asserts the cap flag (N_need >> N_cap; D-H3 (d))
    }
    std::array<contract::BandArray, 6> aq{};
    aq.fill({0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3});
    std::array<double, 6> s03{};
    s03.fill(0.3);
    rows.push_back({"W1/both_corner",
                    diffuse_test::scene(D, aq, s03, {0.1, 0.1, 0.1}, {{19.9, 29.9, 9.9}, S1}), false, true});
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
            rows.push_back({std::string(room).substr(0, std::string(room).find('.')) + "/both_wall_"
                                + std::to_string(dd).substr(0, 3),
                            wall});
            auto edge = wall;
            edge.listener.position.x = dd;
            edge.emitters[0].position.x = dx - dd;
            rows.push_back({std::string(room).substr(0, std::string(room).find('.')) + "/both_edge_"
                                + std::to_string(dd).substr(0, 3),
                            edge});
        }
    for (const auto& row : rows)
    {
        const auto planned = diffuse_test::plan(row.scene);
        const auto r = estimateDiffuse(planned.problem);
        std::printf("05h-reported %-28s n* %lld N %lld N_cap %lld cap hit %d floor truncated %d pilot floor "
                    "%d pilot shipped %d",
                    row.name.c_str(), static_cast<long long>(r.nStar), static_cast<long long>(r.count.n),
                    static_cast<long long>(r.count.nCap), r.count.capHit ? 1 : 0,
                    r.count.floorTruncated ? 1 : 0, r.count.pilotFloor ? 1 : 0, r.count.pilotShipped ? 1 : 0);
        for (std::size_t e = 0; e < r.emitters.size(); ++e)
            std::printf(" | e%zu SE %.3f dB VOV_union %.3f both-near %d U %d", e, r.emitters[e].achievedSeDb,
                        r.emitters[e].vovUnion, r.emitters[e].bothNear ? 1 : 0,
                        r.emitters[e].approximate ? 1 : 0);
        std::printf("\n");
        if (row.assertCapHit)
            REQUIRE(r.count.capHit); // Seat 5 (AX44, as read by D-H3 (d)): the cap benchmark at
                                     // layout4_s1/both_corner
        if (row.assertU)
        {
            REQUIRE(r.emitters[0]
                        .approximate); // W1 both_corner: U through the VOV leg (both-near, VOV_union >= 0.1)
            REQUIRE(r.nStar == kW1BothCornerFlags.nStar);
            REQUIRE(r.count.n == kW1BothCornerFlags.n);
            REQUIRE(r.count.nCap == kW1BothCornerFlags.nCap);
            REQUIRE(r.count.capHit == kW1BothCornerFlags.capHit);
            REQUIRE(r.count.floorTruncated == kW1BothCornerFlags.floorTruncated);
        }
    }
}

// ---- Phase 05i, scope 2 (AX38 (iv), the K-e12 finding of AX38 4c, D-H3 (e)) and scope 4 (file 36 Q4) ----
// Records only: printed with their condition, never a CHECK (phase-05i §4 criterion 2). CI copies every
// "05i-records" line into the job summary (ci.yml, "Records to the job summary").
namespace {

// Waits until every pipeline's builder is idle; returns each pipeline's time from t0 to idle (ms).
std::vector<double> waitAllIdle(const std::vector<std::unique_ptr<plugin::ScenePipeline>>& pipes,
                                Clock::time_point t0)
{
    std::vector<double> stale(pipes.size(), 0.0);
    std::vector<bool> done(pipes.size(), false);
    for (;;)
    {
        bool all = true;
        for (std::size_t i = 0; i < pipes.size(); ++i)
        {
            if (!done[i] && pipes[i]->builderIdle())
            {
                done[i] = true;
                stale[i] = ms(t0, Clock::now());
            }
            all = all && done[i];
        }
        if (all)
            return stale;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

std::string joinMs(const std::vector<double>& v)
{
    std::string s;
    char buf[32];
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        std::snprintf(buf, sizeof(buf), "%s%.0f", i ? " " : "", v[i]);
        s += buf;
    }
    return s;
}

// AX38 4c's per-restore budget: 30 s / 14 restores (D-H1; the register's form).
constexpr double kPerRestoreBudgetMs = 30000.0 / 14.0;

// D-G1 (docs/review/phase-05i/13-decider-DG1.md): the gate-wait split of one host call, the before-remedy
// baseline of AX38 (i) register entry G-1 (re-run unchanged by phase-07c-1 condition 12). A test thread polls
// the process-wide gate's inspection calls about every 1 ms while the call runs; queue(class) = the sum of
// the poll intervals whose starting sample had that class's waiter count >= 1; remainder = host call - queues
// (it includes the pipeline's own quiesce and its own build); the maximum poll gap is the resolution
// (sleep_for(1 ms) can last a timer quantum on Windows). Printed, never asserted; test threads only; the
// poller locks the gate mutex about once per ms.
struct GateSplit
{
    double hostMs = 0.0, queueSyncMs = 0.0, queueOfflineMs = 0.0, maxGapMs = 0.0;
    int polls = 0;
    std::uint64_t turns = 0;
    double remainderMs() const { return hostMs - queueSyncMs - queueOfflineMs; }
};

template <typename Call>
GateSplit measureGateWait(plugin::DiffuseSolveGate& gate, Call&& call)
{
    using Cls = plugin::DiffuseSolveGate::Class;
    struct Sample
    {
        Clock::time_point t;
        std::size_t sync, offline;
    };
    std::vector<Sample> samples;
    samples.reserve(1 << 16);
    std::atomic<bool> running{true}, started{false};
    // Premise (printed with the record): queue(class) counts that class's waiters process-wide, so it is this
    // call's wait only while no other pipeline makes Synchronous or Offline entries (true in record (d),
    // where only pipes[0] does; phase-07c-1 condition 12 (b) re-runs it under the same premise).
    struct JoinGuard
    {
        std::atomic<bool>& run;
        std::thread& t;
        ~JoinGuard()
        {
            run.store(false, std::memory_order_release);
            if (t.joinable())
                t.join();
        }
    };
    std::thread poller([&] {
        while (running.load(std::memory_order_acquire))
        {
            samples.push_back({Clock::now(), gate.waiting(Cls::Synchronous), gate.waiting(Cls::Offline)});
            started.store(true, std::memory_order_release);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    Clock::time_point t0, t1;
    std::uint64_t turns0 = 0, turns1 = 0;
    {
        JoinGuard guard{running, poller}; // stops and joins the poller even if call() throws
        while (!started.load(std::memory_order_acquire))
            std::this_thread::yield();
        turns0 = gate.solvesCompleted();
        t0 = Clock::now();
        call();
        t1 = Clock::now();
        turns1 = gate.solvesCompleted();
    }
    GateSplit g;
    g.hostMs = ms(t0, t1);
    g.turns = turns1 - turns0;
    Clock::time_point prev = t0;
    for (std::size_t i = 0; i < samples.size(); ++i)
    {
        const auto& sm = samples[i];
        if (sm.t < t0 || sm.t > t1)
            continue;
        ++g.polls;
        g.maxGapMs = std::max(g.maxGapMs, ms(prev, sm.t));
        prev = sm.t;
        const auto end = (i + 1 < samples.size() && samples[i + 1].t < t1) ? samples[i + 1].t : t1;
        const double dt = ms(sm.t, end);
        if (sm.sync >= 1)
            g.queueSyncMs += dt;
        if (sm.offline >= 1)
            g.queueOfflineMs += dt;
    }
    g.maxGapMs = std::max(g.maxGapMs, ms(prev, t1));
    return g;
}

void printGateSplit(const std::string& room, double fs, int instances, const char* call,
                    const std::vector<GateSplit>& runs)
{
    std::size_t worst = 0;
    double maxQueue = 0.0;
    for (std::size_t i = 0; i < runs.size(); ++i)
    {
        if (runs[i].hostMs > runs[worst].hostMs)
            worst = i;
        maxQueue = std::max(maxQueue, runs[i].queueSyncMs + runs[i].queueOfflineMs);
    }
    const GateSplit& g = runs[worst];
    if (g.polls == 0)
    {
        std::printf("05i-records (iv) gate-wait %-26s %6.0f Hz, %d inst, %s: host call %.0f ms; NOT MEASURED "
                    "(no poll)\n",
                    room.c_str(), fs, instances, call, g.hostMs);
        return;
    }
    std::printf(
        "05i-records (iv) gate-wait %-26s %6.0f Hz, %d inst, %s: host call %.0f ms = queue(Synchronous) "
        "%.0f ms + queue(Offline) %.0f ms + remainder %.0f ms; max queue over %zu runs %.0f ms; gate turns "
        "completed during the call %llu; polls %d, max poll gap %.1f ms (resolution); remainder includes "
        "this pipeline's own quiesce and its own build; queues count waiters process-wide (only this "
        "pipeline makes "
        "Synchronous/Offline entries here); poller locks the gate mutex about once per ms\n",
        room.c_str(), fs, instances, call, g.hostMs, g.queueSyncMs, g.queueOfflineMs, g.remainderMs(),
        runs.size(), maxQueue, static_cast<unsigned long long>(g.turns), g.polls, g.maxGapMs);
}

} // namespace

// AX38 (iv), phase-05i scope 2 and scope 4: 1, 4 and 8 instances at the AQ10 room and at the gated 100 m
// low-alpha cube, 48 and 96 kHz.
// (a) Load: the instances prepared and restored one after another on one host thread (as a host loads a
//     project; prepare() builds the default scene synchronously, restore() then builds the project's scene,
//     and both are in the load time, as in a host); prepare() and restore() timed per instance (scope 4: the
//     per-instance restore times inside the (iv) loop, file 36 Q4; phase-07c condition 7 does not exist yet).
// (b) Staleness when the instances are automated together, at two steps applied to every instance at once:
//     a room-size step (width, depth and height each -1 m) and a joint step (the same room-size step plus the
//     listener +0.5 m in x); from the change to each instance's builder idle (the gate serialises the
//     solves).
// (c) Staleness of the real-time instances while one more instance renders offline under room-size
//     automation (the offline instance steps the room size 1 m per processed block, back to back: the worst
//     rebuild rate a bounce can ask for); the real-time step is a room-size step (to -3 m in w/d/h), a full
//     rebuild that contends at the gate with the offline instance's builds.
// (d) The worst host-thread wait for prepare, restore and the offline switch (setNonRealtime(true) plus the
//     first offline block, after a room-size edit so that block builds) of one instance while the other
//     instances rebuild without pause (room-size steps of 1 m every 50 ms on each of them).
TEST_CASE("records: AX38 (iv) per-instance restore, room-size and joint staleness, offline contention and "
          "host-thread waits (1, 4, 8 instances)",
          "[.][benchmark][diffuse-records-05i]")
{
    std::vector<float> a(512, 0.1f), b(512, -0.1f);
    const float* const in[2] = {a.data(), b.data()};
    float* const out[2] = {a.data(), b.data()};
    for (const auto& [label, sc] : std::vector<std::pair<std::string, contract::SceneDescription>>{
             {"AQ10 room", aq10Room()}, {"cube100_lowalpha0.05_s0.3", cube("cube100_lowalpha0.05_s0.3")}})
        for (const double fs : {48000.0, 96000.0})
            for (const int instances : {1, 4, 8})
            {
                const auto values = module3d::parameterValuesFromScene(sc);
                const float w = static_cast<float>(sc.room.geometry.dimensions.x);
                const float d = static_cast<float>(sc.room.geometry.dimensions.y);
                const float h = static_cast<float>(sc.room.geometry.dimensions.z);
                const float lx = static_cast<float>(sc.listener.position.x);
                std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
                for (int i = 0; i < instances; ++i)
                    pipes.push_back(std::make_unique<plugin::ScenePipeline>());
                // (a)
                std::vector<double> prepMs, restMs;
                const auto t0 = Clock::now();
                for (auto& p : pipes)
                {
                    const auto p0 = Clock::now();
                    p->prepare(fs, 512, false);
                    const auto p1 = Clock::now();
                    p->beginRestore();
                    p->restore(sc, values);
                    prepMs.push_back(ms(p0, p1));
                    restMs.push_back(ms(p1, Clock::now()));
                }
                const double load = ms(t0, Clock::now());
                std::printf(
                    "05i-records (iv) %-26s %6.0f Hz, %d inst: load until the last is audible %.0f ms "
                    "(prepare's default-scene build + restore, per instance); per instance (load order) "
                    "prepare [%s] ms, restore [%s] ms\n",
                    label.c_str(), fs, instances, load, joinMs(prepMs).c_str(), joinMs(restMs).c_str());
                // (b) room-size step, then the joint step, on every instance at once.
                for (const bool joint : {false, true})
                {
                    const float step = joint ? 2.0f : 1.0f;
                    const auto t1 = Clock::now();
                    for (auto& p : pipes)
                    {
                        p->setParameter(module3d::kRoomW, w - step);
                        p->setParameter(module3d::kRoomD, d - step);
                        p->setParameter(module3d::kRoomH, h - step);
                        if (joint)
                            p->setParameter(module3d::kListenerX, lx + 0.5f);
                    }
                    const auto ss = spread(waitAllIdle(pipes, t1));
                    std::printf(
                        "05i-records (iv) %-26s %6.0f Hz, %d inst: staleness when automated together, "
                        "%s step on every instance at once: min %.0f median %.0f max %.0f ms\n",
                        label.c_str(), fs, instances,
                        joint ? "joint (room size -1 m in w/d/h and listener +0.5 m in x)"
                              : "room-size (-1 m in w/d/h)",
                        ss.min, ss.median, ss.max);
                }
                // (c) one more instance renders offline, stepping the room size 1 m per block.
                {
                    plugin::ScenePipeline off;
                    off.prepare(fs, 512, true);
                    off.beginRestore();
                    off.restore(sc, values);
                    off.process(in, out, 512); // the first offline build
                    std::atomic<bool> stop{false};
                    std::atomic<int> offSteps{0};
                    std::thread bounce([&] {
                        int k = 0;
                        while (!stop.load())
                        {
                            ++k;
                            const float s = static_cast<float>(1 + (k % 4));
                            off.setParameter(module3d::kRoomW, w - s);
                            off.setParameter(module3d::kRoomD, d - s);
                            off.setParameter(module3d::kRoomH, h - s);
                            off.process(in, out, 512);
                            offSteps.fetch_add(1);
                        }
                    });
                    while (offSteps.load() < 1)
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    const auto t2 = Clock::now();
                    for (auto& p : pipes)
                    {
                        p->setParameter(module3d::kRoomW, w - 3.0f);
                        p->setParameter(module3d::kRoomD, d - 3.0f);
                        p->setParameter(module3d::kRoomH, h - 3.0f);
                    }
                    const auto ss = spread(waitAllIdle(pipes, t2));
                    stop.store(true);
                    bounce.join();
                    std::printf("05i-records (iv) %-26s %6.0f Hz, %d inst: real-time staleness while 1 more "
                                "instance renders offline (room size stepping 1 m per block, back to back; "
                                "%d offline rebuilds meanwhile), room-size step (to -3 m in w/d/h) on every "
                                "real-time "
                                "instance at once: min %.0f median %.0f "
                                "max %.0f ms\n",
                                label.c_str(), fs, instances, offSteps.load(), ss.min, ss.median, ss.max);
                }
                // (d) one instance's host-thread waits while the others rebuild without pause.
                {
                    std::atomic<bool> stop{false};
                    std::thread churn([&] {
                        int k = 0;
                        while (!stop.load())
                        {
                            ++k;
                            const float s = static_cast<float>(1 + (k % 4));
                            for (int i = 1; i < instances; ++i)
                            {
                                pipes[static_cast<std::size_t>(i)]->setParameter(module3d::kRoomW, w - s);
                                pipes[static_cast<std::size_t>(i)]->setParameter(module3d::kRoomD, d - s);
                                pipes[static_cast<std::size_t>(i)]->setParameter(module3d::kRoomH, h - s);
                            }
                            std::this_thread::sleep_for(std::chrono::milliseconds(50));
                        }
                    });
                    auto& p = *pipes[0];
                    // D-G1: the gate-wait split of each host call (printed below, never asserted).
                    const auto gate = plugin::DiffuseSolveGate::shared();
                    std::vector<double> prep, rest, offl;
                    std::vector<GateSplit> prepSplit, restSplit, offlSplit;
                    for (int r = 0; r < 3; ++r)
                    {
                        prepSplit.push_back(measureGateWait(*gate, [&] { p.prepare(fs, 512, false); }));
                        restSplit.push_back(measureGateWait(*gate, [&] {
                            p.beginRestore();
                            p.restore(sc, values);
                        }));
                        offlSplit.push_back(measureGateWait(*gate, [&] {
                            p.setNonRealtime(true);
                            p.setParameter(module3d::kRoomW, w - static_cast<float>(4 + r));
                            p.setParameter(module3d::kRoomD, d - static_cast<float>(4 + r));
                            p.setParameter(module3d::kRoomH, h - static_cast<float>(4 + r));
                            p.process(in, out, 512); // the offline branch builds before this block
                        }));
                        p.setNonRealtime(false);
                        prep.push_back(prepSplit.back().hostMs);
                        rest.push_back(restSplit.back().hostMs);
                        offl.push_back(offlSplit.back().hostMs);
                    }
                    stop.store(true);
                    churn.join();
                    printGateSplit(label, fs, instances, "prepare", prepSplit);
                    printGateSplit(label, fs, instances, "restore", restSplit);
                    printGateSplit(label, fs, instances, "offline switch + first block", offlSplit);
                    std::printf("05i-records (iv) %-26s %6.0f Hz, %d inst: worst host-thread wait of one "
                                "instance while %d other%s rebuild without pause (0: uncontended baseline; "
                                "room size stepping 1 m "
                                "every 50 ms), 3 runs: prepare %.0f ms, restore %.0f ms, offline switch + "
                                "first block after a room-size edit %.0f ms\n",
                                label.c_str(), fs, instances, instances - 1, instances == 2 ? "" : "s",
                                spread(prep).max, spread(rest).max, spread(offl).max);
                }
            }
}

// AX38 (iv), phase-05i scope 2: the offline wait. M instances render offline in parallel (M = 1, 4, 8; the
// M-parallel case), each stepping the room size 1 m per processed block, 4 steps back to back (the worst
// rebuild rate a bounce can ask for); the wait is the duration of each process() call that builds (the
// offline branch builds before the block whose scene changed, AX5 / X11), and the bounce's wall time.
TEST_CASE("records: AX38 (iv) offline wait per rebuilding block, 1 / 4 / 8 offline instances in parallel",
          "[.][benchmark][diffuse-records-05i]")
{
    for (const auto& [label, sc] : std::vector<std::pair<std::string, contract::SceneDescription>>{
             {"AQ10 room", aq10Room()}, {"cube100_lowalpha0.05_s0.3", cube("cube100_lowalpha0.05_s0.3")}})
        for (const double fs : {48000.0, 96000.0})
            for (const int m : {1, 4, 8})
            {
                const auto values = module3d::parameterValuesFromScene(sc);
                const float w = static_cast<float>(sc.room.geometry.dimensions.x);
                const float d = static_cast<float>(sc.room.geometry.dimensions.y);
                const float h = static_cast<float>(sc.room.geometry.dimensions.z);
                std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
                for (int i = 0; i < m; ++i)
                {
                    pipes.push_back(std::make_unique<plugin::ScenePipeline>());
                    pipes.back()->prepare(fs, 512, true);
                    pipes.back()->beginRestore();
                    pipes.back()->restore(sc, values);
                }
                std::vector<std::vector<double>> waits(static_cast<std::size_t>(m));
                const auto t0 = Clock::now();
                std::vector<std::thread> threads;
                for (int i = 0; i < m; ++i)
                    threads.emplace_back([&, i] {
                        std::vector<float> a(512, 0.1f), b(512, -0.1f);
                        const float* const in[2] = {a.data(), b.data()};
                        float* const out[2] = {a.data(), b.data()};
                        auto& p = *pipes[static_cast<std::size_t>(i)];
                        for (int k = 0; k <= 4; ++k)
                        {
                            if (k > 0)
                            {
                                p.setParameter(module3d::kRoomW, w - static_cast<float>(k));
                                p.setParameter(module3d::kRoomD, d - static_cast<float>(k));
                                p.setParameter(module3d::kRoomH, h - static_cast<float>(k));
                            }
                            const auto c0 = Clock::now();
                            p.process(in, out, 512); // k = 0: the restore's build
                            waits[static_cast<std::size_t>(i)].push_back(ms(c0, Clock::now()));
                        }
                    });
                for (auto& t : threads)
                    t.join();
                const double wall = ms(t0, Clock::now());
                std::vector<double> all;
                for (const auto& v : waits)
                    all.insert(all.end(), v.begin() + 1, v.end()); // the four room-size steps
                const auto ss = spread(all);
                std::printf(
                    "05i-records (iv) offline %-26s %6.0f Hz, %d offline instance%s in parallel: wait "
                    "per rebuilding block (room size -1 m per block, 4 steps back to back) min %.0f "
                    "median %.0f worst %.0f ms; first build (after restore) worst %.0f ms; wall %.0f "
                    "ms\n",
                    label.c_str(), fs, m, m == 1 ? "" : "s", ss.min, ss.median, ss.max,
                    [&] {
                        double x = 0.0;
                        for (const auto& v : waits)
                            x = std::max(x, v.front());
                        return x;
                    }(),
                    wall);
            }
}

// The K-e12 record (AX38 4c finding, D-H3 (e), phase-05i scope 2): a room edit in flight, then a restore, at
// the two gated builds (the 100 m cubes at 96 kHz), worst of 10, printed once as a record, never a CHECK. The
// edit is a room-size step (w/d/h -1 m: a full rebuild with the diffuse solve and new unit decays; a material
// edit reaches the pipeline only through a restore, so the room size is the host-reachable edit); the restore
// lands at a random point of that rebuild; the host-thread wait is beginRestore() + restore(), i.e. the
// quiesce wait (cancel points only in the diffuse solve, AX39 D6) plus the synchronous restore with its
// solve. H1-F1's convention (the gate measures with the builder idle) is not read as met here: a worst above
// the per-restore budget 30 s / 14 = 2.143 s is printed as a FINDING under the register's form (remedy
// phase-07c conditions 9 and 10).
TEST_CASE("records: K-e12 restore with a room edit in flight at the gated 100 m cubes, 96 kHz, worst of 10",
          "[.][benchmark][diffuse-records-05i]")
{
    constexpr int kRuns = 10;
    std::mt19937_64 rng(0x05E12);
    for (const char* key : {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3"})
    {
        const auto sc = cube(key);
        const auto values = module3d::parameterValuesFromScene(sc);
        const float w = static_cast<float>(sc.room.geometry.dimensions.x);
        const float d = static_cast<float>(sc.room.geometry.dimensions.y);
        const float h = static_cast<float>(sc.room.geometry.dimensions.z);
        plugin::ScenePipeline pipe;
        pipe.prepare(96000.0, 512, false);
        const auto edit = [&](float s) {
            pipe.setParameter(module3d::kRoomW, w - s);
            pipe.setParameter(module3d::kRoomD, d - s);
            pipe.setParameter(module3d::kRoomH, h - s);
        };
        // The idle restore (H1-F1's condition) and the room-edit rebuild time, uncancelled.
        // Every timed restore loads a state the pipeline has not built (a distinct room size, as a project or
        // preset load does), so it is a full synchronous build, never the skip of an unchanged state.
        int fresh = 0;
        const auto freshValues = [&] {
            auto v = values;
            const double s = 3.0 + 0.1 * fresh++;
            v[module3d::kRoomW] = w - s;
            v[module3d::kRoomD] = d - s;
            v[module3d::kRoomH] = h - s;
            return v;
        };
        pipe.beginRestore();
        pipe.restore(sc, values);
        std::vector<double> idle;
        for (int i = 0; i < 3; ++i)
        {
            const auto v = freshValues();
            const auto t0 = Clock::now();
            pipe.beginRestore();
            pipe.restore(sc, v);
            idle.push_back(ms(t0, Clock::now()));
        }
        const auto tb = Clock::now();
        edit(1.0f);
        while (!pipe.builderIdle())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        const double rebuild = ms(tb, Clock::now());
        std::uniform_real_distribution<double> u(0.0, rebuild);
        std::vector<double> waits, delays;
        std::vector<int> inFlight;
        for (int i = 0; i < kRuns; ++i)
        {
            pipe.beginRestore();
            pipe.restore(sc, values); // builder idle, IR current
            const double dl = u(rng);
            edit(static_cast<float>(1 + (i % 2)));
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(dl));
            const auto v = freshValues();
            // Whether the builder still had work when the restore landed: the edit queued or building (from
            // the code, builderIdle() is false while a change is pending or being built). Phase-05i §3.2:
            // H1-F1's builder-idle condition is not read as met here; a run where the builder was already
            // idle is printed as such and left out of the busy-run worst.
            inFlight.push_back(pipe.builderIdle() ? 0 : 1);
            const auto t0 = Clock::now();
            pipe.beginRestore();
            pipe.restore(sc, v);
            waits.push_back(ms(t0, Clock::now()));
            delays.push_back(dl);
        }
        const auto ws = spread(waits);
        const auto is = spread(idle);
        std::vector<double> busyWaits;
        for (int i = 0; i < kRuns; ++i)
            if (inFlight[static_cast<std::size_t>(i)])
                busyWaits.push_back(waits[static_cast<std::size_t>(i)]);
        const double busyWorst = busyWaits.empty() ? 0.0 : spread(busyWaits).max;
        std::printf(
            "05i-records K-e12 os=%s %-26s 96 kHz: restore with a room edit in flight (room size -1/-2 m in "
            "w/d/h, restore of a new room size at a random point of the %.0f ms rebuild), %d runs: min %.0f "
            "median %.0f worst "
            "%.0f ms; builder busy at the restore in %zu of %d runs, worst over those %.0f ms (idle restore "
            "of a "
            "new state median %.0f ms, 3 runs); per-restore budget %.0f ms: %s\n",
            kOsName, key, rebuild, kRuns, ws.min, ws.median, ws.max, busyWaits.size(), kRuns, busyWorst,
            is.median, kPerRestoreBudgetMs,
            ws.max > kPerRestoreBudgetMs
                ? "FINDING (worst above the budget; register form, remedy phase-07c conditions 9-10)"
                : "within");
        for (int i = 0; i < kRuns; ++i)
            std::printf("05i-records K-e12 os=%s %-26s run %2d: restore at %.0f ms of %.0f (builder busy: "
                        "%s) -> host thread %.0f ms\n",
                        kOsName, key, i, delays[static_cast<std::size_t>(i)], rebuild,
                        inFlight[static_cast<std::size_t>(i)] ? "yes" : "no",
                        waits[static_cast<std::size_t>(i)]);
    }
}
