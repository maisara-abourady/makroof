// Phase 05h, scope 6 and D-H1 (AX38 4b / 4c / (iv), AX41, Seat 1's clause (d)): the records of the switched
// build. Hidden: CI runs them from the Release build with "[benchmark]". Recorded, not gated, except where
// the plan pins a gate (docs/review/phase-05h/, decisions D-H1 and RG-1): the gated-scene flags, the
// realised-work ratio, the W_pilot / W_final pins, the unit-decay length and synthesis FFT size per gated
// scene, the flutter scene's 14 x worst-of-10 restore <= 30 s and, in a +-5 % flutter window on x64, the
// low-alpha restore's growth bound are asserted in "[diffuse-records]"; everything else is printed.
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"
#include "ProcessMemory.h"
#include "RealtimeProbe.h"

#include "contract/Json.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/DiffuseSolveGate.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Fft.h"
#include "sim/RealtimeEngine.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"
#include "sim/ism/BandRenderer.h"
#include "sim/tail/Decay.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <limits>
#include <map>
#include <optional>
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
    // The gated low-alpha cube. macOS and Windows are listed (remedy phase-07c conditions 9-10): macOS
    // recorded 33.40 s (local / file 1); Windows recorded 36.73 s on CI run 42942694523's slow runner
    // (phase-05h file 53) and printed OVER30S on 05i's run of record 43031773338. Linux (30.27 s local /
    // file 1) closed under AX38 4c (c) on phase 05i's runs (docs/review/phase-05i/9, 19): print only.
    {"cube100_lowalpha0.05_s0.3", "Linux", 30.27, 2068.0, 3.05, 701.0, true, false, false, 80.9, 1},
    {"cube100_lowalpha0.05_s0.3", "macOS", 33.40, 1817.0, 3.75, 484.0, false, true, false, 83.7, 1},
    {"cube100_lowalpha0.05_s0.3", "Windows", 36.73, 2028.0, 2.83, 737.0, true, true, false, 90.4, 2},
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
        // Phase-07c-1 condition 7 (AX38 4c re-scoped): the restore as AX48 / AX49 build it, 96 kHz, worst of
        // 10, alone and contended: a project load (the instance's first restore, no IrSet of this scene
        // current) into a fresh instance prepared on the default scene: ISM + matching + the AX49 interim
        // tail + mix, plus the AX48 stage-1 solve (keyless: no saved E_b). The background settling to the
        // exact tail is not in it (the instance is destroyed after the timed restore; its builder is
        // cancelled, condition 10).
        const auto values = module3d::parameterValuesFromScene(sc);
        // Phase-07c-1b D-B5 (vi) item 3 (per-stage split, test-only; Seat 5 Q5): the timed restore's stage
        // hook timestamps, taken on this (host) thread only; the builder's own stages after the restore
        // returns are ignored. stageMs: per keyless restore, Plan, Solve, Assemble, Commit and the return,
        // in ms from its start (-1: the stage did not fire).
        std::vector<std::array<double, 5>> stageMs;
        struct StageStamps
        {
            std::optional<Clock::time_point> plan, solve, assemble, commit;
        };
        const std::thread::id hostThread = std::this_thread::get_id();
        const auto load = [&](const std::optional<plugin::SavedDiffuse>& saved, StageStamps* stamps) {
            plugin::ScenePipeline fresh;
            fresh.prepare(96000.0, 512, false);
            REQUIRE(pipeline_test::waitFor([&] { return !fresh.settling() && fresh.builderIdle(); }));
            if (stamps != nullptr)
                fresh.setStageHook([stamps, hostThread](plugin::ScenePipeline::BuildStage st) {
                    if (std::this_thread::get_id() != hostThread)
                        return;
                    const auto now = Clock::now();
                    using Bs = plugin::ScenePipeline::BuildStage;
                    auto& slot = st == Bs::Plan       ? stamps->plan
                                 : st == Bs::Solve    ? stamps->solve
                                 : st == Bs::Assemble ? stamps->assemble
                                                      : stamps->commit;
                    if (!slot)
                        slot = now; // the first of each stage
                });
            const auto t0 = Clock::now();
            fresh.beginRestore();
            fresh.restore(sc, values, saved);
            const double d = ms(t0, Clock::now());
            if (stamps != nullptr)
            {
                // The split, in ms from the restore's start (t0): Plan, Solve, Assemble, Commit, return.
                const auto at = [&](const std::optional<Clock::time_point>& tp) {
                    return tp ? ms(t0, *tp) : -1.0;
                };
                stageMs.push_back(
                    {at(stamps->plan), at(stamps->solve), at(stamps->assemble), at(stamps->commit), d});
            }
            return d;
        };
        std::vector<double> restore;
        for (int i = 0; i < kRuns; ++i)
        {
            StageStamps stamps;
            restore.push_back(load(std::nullopt, gateRegisterEntry(key) != nullptr ? &stamps : nullptr));
        }
        const auto rs = spread(restore);
        if (gateRegisterEntry(key) != nullptr && !stageMs.empty())
        {
            // Segment medians over the kRuns keyless restores (a segment whose stage did not fire: n/a).
            const auto seg = [&](int from, int to) {
                std::vector<double> v;
                for (const auto& st : stageMs)
                    if (st[static_cast<std::size_t>(from)] >= 0.0 && st[static_cast<std::size_t>(to)] >= 0.0)
                        v.push_back(st[static_cast<std::size_t>(to)] - st[static_cast<std::size_t>(from)]);
                return v.empty() ? Spread{-1.0, -1.0, -1.0} : spread(v);
            };
            std::vector<double> startToPlan;
            for (const auto& st : stageMs)
                if (st[0] >= 0.0)
                    startToPlan.push_back(st[0]);
            const auto sp0 = startToPlan.empty() ? Spread{-1.0, -1.0, -1.0} : spread(startToPlan);
            const auto planSolve = seg(0, 1), solveAsm = seg(1, 2), asmCommit = seg(2, 3),
                       commitRet = seg(3, 4);
            std::printf(
                "07c1b-records stage split os=%s scene=%s 96 kHz keyless restore (stage-hook timestamps on "
                "the "
                "host thread, median [min max] of %zu, ms): start->Plan (quiesce, snapshot) %.1f [%.1f "
                "%.1f]; "
                "Plan->Solve (ISM + matching + gate wait) %.1f [%.1f %.1f]; Solve->Assemble (solve) %.1f "
                "[%.1f "
                "%.1f]; Assemble->Commit (synthesis + assembly + makeIrSet + D7 compare) %.1f [%.1f %.1f]; "
                "Commit->return %.1f [%.1f %.1f]; restore median %.0f\n",
                kOsName, key, stageMs.size(), sp0.median, sp0.min, sp0.max, planSolve.median, planSolve.min,
                planSolve.max, solveAsm.median, solveAsm.min, solveAsm.max, asmCommit.median, asmCommit.min,
                asmCommit.max, commitRet.median, commitRet.min, commitRet.max, rs.median);
            // The replay (public sim::StagedBuild, serial emitter synthesis): the exact build's synthesis
            // separated from its assembly (assemble() fresh vs assemble() over the cached exact unit decays),
            // makeIrSet timed apart. Median of 3. Not the restore's own (provisional) build: labelled replay.
            sim::BuildOptions o;
            o.sampleRate = 96000.0;
            o.kind = sim::BuildOptions::Kind::Omni;
            o.parallelEmitterSynthesis = false;
            sim::RealtimeEngine engine(plugin::ScenePipeline::kPartitionSize);
            engine.prepare(96000.0, 512);
            std::vector<double> planR, solveR, freshR, cachedR, irSetR;
            bool exact = true, irSetOk = true;
            std::size_t emitters = 0;
            for (int r = 0; r < 3; ++r)
            {
                auto t = Clock::now();
                auto first = sim::StagedBuild::plan(sc, o);
                planR.push_back(ms(t, Clock::now()));
                t = Clock::now();
                first.solve();
                solveR.push_back(ms(t, Clock::now()));
                sim::HybridDiagnostics diag;
                t = Clock::now();
                const auto ir = first.assemble(&diag);
                freshR.push_back(ms(t, Clock::now()));
                emitters = diag.emitters.size();
                auto second = sim::StagedBuild::plan(sc, o);
                REQUIRE(first.diffuseLevel().has_value());
                second.useDiffuseLevel(*first.diffuseLevel());
                second.useUnitDecays(first.unitDecays());
                exact = exact && second.unitDecaysExact();
                t = Clock::now();
                (void)second.assemble();
                cachedR.push_back(ms(t, Clock::now()));
                t = Clock::now();
                const auto set = engine.makeIrSet(ir);
                irSetR.push_back(ms(t, Clock::now()));
                irSetOk = irSetOk && set != nullptr;
            }
            const double fresh = spread(freshR).median, cached = spread(cachedR).median;
            std::printf(
                "07c1b-records stage split replay os=%s scene=%s 96 kHz (sim::StagedBuild, "
                "parallelEmitterSynthesis = false, exact tail, median of 3, ms): plan (ISM + matching) "
                "%.1f; solve %.1f; assemble fresh (synthesis + assembly) %.1f; assemble over the cached "
                "exact unit decays (assembly) %.1f%s; synthesis %.1f, per emitter %.1f (mean over %zu, "
                "serial); makeIrSet %.1f%s\n",
                kOsName, key, spread(planR).median, spread(solveR).median, fresh, cached,
                exact ? "" : " [cached units NOT exact]", fresh - cached,
                emitters > 0 ? (fresh - cached) / static_cast<double>(emitters) : 0.0, emitters,
                spread(irSetR).median, irSetOk ? "" : " [IrSet nullptr]");
        }
        {
            auto planned = sim::StagedBuild::plan(sc, [] {
                sim::BuildOptions o;
                o.sampleRate = 96000.0;
                o.kind = sim::BuildOptions::Kind::Omni;
                return o;
            }());
            const auto t = planned.provisionalTiming();
            std::printf(
                "05h-records restore %-26s 96 kHz L_p %.2f s (L_f %.2f s, L %.2f s): %s (AX49 reversal 1 "
                "reads L_p <= 3.82 s)\n",
                key, t.endS, t.fadeStartS, t.exactS,
                t.provisional ? "provisional interim tail" : "L_p >= L: the exact tail in its place (07d)");
        }
        std::printf("05h-records restore %-26s 96 kHz as AX48/AX49 build it (keyless load: stage-1 solve + "
                    "interim tail), "
                    "%d runs: min %.0f median %.0f worst %.0f ms; 14 x worst %.2f s (30 s)\n",
                    key, kRuns, rs.min, rs.median, rs.max, 14.0 * rs.max / 1000.0);
        {
            // The keyed load (saved E_b whose five-part key matches): no synchronous solve. Printed, median
            // of 3.
            plugin::ScenePipeline src;
            src.prepare(96000.0, 512, false);
            src.beginRestore();
            src.restore(sc, values);
            REQUIRE(pipeline_test::waitFor([&] { return !src.settling() && src.builderIdle(); },
                                           std::chrono::minutes(5)));
            const auto saved = src.savedDiffuse();
            REQUIRE(saved.has_value());
            std::vector<double> keyed;
            for (int i = 0; i < 3; ++i)
                keyed.push_back(load(saved, nullptr));
            const auto ks = spread(keyed);
            std::printf(
                "05h-records restore %-26s 96 kHz keyed load (saved E_b, no solve), 3 runs: min %.0f median "
                "%.0f worst %.0f ms\n",
                key, ks.min, ks.median, ks.max);
        }
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
        // Contended: a second instance loads the same 100 m scene on another thread at the same time.
        std::vector<double> contended;
        for (int i = 0; i < 3; ++i)
        {
            plugin::ScenePipeline pipe, other;
            pipe.prepare(96000.0, 512, false);
            other.prepare(96000.0, 512, false);
            REQUIRE(pipeline_test::waitFor([&] { return !pipe.settling() && !other.settling(); }));
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
// with the record, AX38 (iv)). (3), the callback record at host buffer 64 with concurrent builders, is the
// next test case (condition 12 (c), re-instrumented in phase-07c-1b).
TEST_CASE("records: AQ4 intervals and the 3-minute room-size bounce at 100 m",
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
        // Phase-07c-1 O16 (AX38 4c, umbrella section 9): the same record after conditions 6 and 9 (offline
        // waits for the final solve, the unit-decay synthesis in parallel per emitter, the AQ4 cache), the
        // (C) W_max input of phase 07c-2 (D-H1 (iv), AX41). The pre-move figures:
        // docs/review/phase-05h/31-orchestrator-local-records.md.
        std::printf(
            "07c1-records bounce (O16) 100 m cube %6.0f Hz: 3-minute offline room-size automation, %d "
            "rebuilds: %.1f s wall, ratio to real time %.2f x; interim IrSets offline %llu (must be 0)\n",
            fs, steps, wall, wall / seconds, static_cast<unsigned long long>(pipe.stats().interimSubmits));
        REQUIRE(pipe.stats().interimSubmits == 0); // condition 6: offline never plays an interim
    }
}

// Phase-07c-1 condition 12 (c) record (AX38 (i)): callback times of one real-time instance at host buffer 64
// (48 kHz, AQ10 room) while other instances rebuild the 100 m low-alpha cube without pause (a listener move
// on each every 50 ms: ISM, solve at the gate, assembly over the cached unit decays). Two instruments:
// - old instrument (R16), unchanged: a normal-priority test thread paced by sleep_for, wall time only,
//   1 / 4 / 8 builders. Its p99.9 over 953-1 936 callbacks is the 1st-2nd largest sample (R16), on a thread
//   no host would use for audio (R4, R7, R8): kept for comparison only.
// - phase-07c-1b D-B1 (B1-b; docs/review/phase-07c-1b/4-decider-decision-r1.md items 1-5, file 8 item 6):
//   the callback thread at platform audio priority (RealtimeProbe.h: macOS time-constraint policy at the
//   1 333 us period, Windows MMCSS "Pro Audio" with a high-resolution timer, Linux SCHED_FIFO, else "not
//   available" with the error), absolute-deadline pacing (sleep to ~100 us before the deadline, then spin);
//   per callback the wall and thread-CPU time of process() and the convolver's multiply-adds; builders
//   0 / 1 / 2 / 4 / 8, the 0-builder floor first. Per point: callback count vs expected (INSTRUMENT INVALID
//   below 0.95 x), median / p99 / p99.9 / max of wall and CPU, overruns > period and > period / 2,
//   hardware_concurrency() and the priority obtained.
// A record, never asserted. An overrun > period at 8 builders with none at 0 is re-measured in phase-13-3
// scope 4 and on the R5 Windows release machine (a miss opens 13-1b, B1-d first; never an instance cap).
TEST_CASE("records: condition 12 (c) callback record at host buffer 64, B1-b instrument (0/1/2/4/8 "
          "builders) beside the old instrument (R16)",
          "[.][benchmark][diffuse-records-aq4][cond12c]")
{
    constexpr double kFs = 48000.0;
    constexpr int kBlock = 64;
    const auto big = cube("cube100_lowalpha0.05_s0.3");
    const auto bigValues = module3d::parameterValuesFromScene(big);
    const auto room = aq10Room();
    const unsigned hw = std::thread::hardware_concurrency();
    std::map<int, double> oldP999;
    // ---- old instrument (R16), as in phase 05h / 07c-1 ----
    for (const int builders : {1, 4, 8})
    {
        const double fs = kFs;
        plugin::ScenePipeline rt;
        rt.prepare(fs, kBlock, false);
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
        std::vector<float> a(kBlock, 0.1f), b(kBlock, -0.1f);
        const float* const in[2] = {a.data(), b.data()};
        float* const out[2] = {a.data(), b.data()};
        std::vector<double> us;
        const double period = kBlock / fs * 1e6;
        const auto tEnd = Clock::now() + std::chrono::seconds(10);
        while (Clock::now() < tEnd)
        {
            const auto c0 = Clock::now();
            rt.process(in, out, kBlock);
            us.push_back(std::chrono::duration<double, std::micro>(Clock::now() - c0).count());
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long>(period)));
        }
        stop.store(true);
        churn.join();
        std::sort(us.begin(), us.end());
        const double p999 = us[static_cast<std::size_t>(std::ceil(0.999 * us.size())) - 1];
        oldP999[builders] = p999;
        std::printf(
            "05h-records callback p99.9 [old instrument (R16): normal-priority thread, sleep_for "
            "pacing, wall only] at host buffer 64 (%.0f us period), %d concurrent builder%s at 100 m: "
            "p99.9 %.0f us, max %.0f us over %zu callbacks (10 s)\n",
            period, builders, builders == 1 ? "" : "s", p999, us.back(), us.size());
    }

    // ---- B1-b instrument (phase-07c-1b D-B1) ----
    const double periodUs = kBlock / kFs * 1e6;
    constexpr double kSeconds = 10.0;
    const auto expected = static_cast<std::size_t>(kSeconds * 1e6 / periodUs); // 7 500 slots
    const auto quantile = [](const std::vector<double>& sorted, double q) {
        return sorted[static_cast<std::size_t>(std::ceil(q * static_cast<double>(sorted.size()))) - 1];
    };
    struct Point
    {
        int builders = 0;
        std::size_t callbacks = 0, missedSlots = 0, overPeriod = 0, overHalf = 0, cpuOverHalf = 0;
        double wallP999 = 0.0;
    };
    std::vector<Point> points;
    std::vector<std::unique_ptr<plugin::ScenePipeline>> others; // created after the 0-builder floor
    const auto othersIdle = [&] {
        for (const auto& o : others)
            if (!o->builderIdle() || o->settling())
                return false;
        return true;
    };
    for (const int builders : {0, 1, 2, 4, 8})
    {
        if (builders > 0 && others.empty())
        {
            for (int i = 0; i < 8; ++i)
            {
                others.push_back(std::make_unique<plugin::ScenePipeline>());
                others.back()->prepare(kFs, 512, false);
                others.back()->beginRestore();
                others.back()->restore(big, bigValues);
            }
            REQUIRE(pipeline_test::waitFor(othersIdle, std::chrono::minutes(10)));
        }
        plugin::ScenePipeline rt;
        rt.prepare(kFs, kBlock, false);
        rt.beginRestore();
        rt.restore(room, module3d::parameterValuesFromScene(room));
        REQUIRE(pipeline_test::waitFor([&] { return !rt.settling() && rt.builderIdle(); }));
        std::atomic<bool> stop{false};
        std::thread churn([&] {
            float x = 50.0f;
            while (!stop.load())
            {
                x += 0.1f;
                for (int i = 0; i < builders; ++i)
                    others[static_cast<std::size_t>(i)]->setParameter(module3d::kListenerX, x);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
        // The callback thread: priority, timer and CPU clock are set up on it, then the paced loop.
        std::vector<double> wall, cpu;
        std::uint64_t maxMacs = 0;
        std::size_t missed = 0;
        double wakeLateMaxUs = 0.0;
        std::string priority, timer, cpuClock;
        std::thread callback([&] {
            const rt_probe::AudioPriority prio(periodUs);
            const rt_probe::Pacer pacer;
            const rt_probe::ThreadCpuClock cpuClk;
            priority = prio.description();
            timer = pacer.describe();
            cpuClock = cpuClk.describe();
            wall.reserve(expected);
            cpu.reserve(expected);
            std::vector<float> a(kBlock, 0.1f), b(kBlock, -0.1f);
            const float* const in[2] = {a.data(), b.data()};
            float* const out[2] = {a.data(), b.data()};
            const auto start = Clock::now() + std::chrono::milliseconds(5);
            const auto slot = [&](std::size_t k) {
                return start
                       + std::chrono::duration_cast<Clock::duration>(
                           std::chrono::duration<double, std::micro>(static_cast<double>(k) * periodUs));
            };
            std::size_t k = 0;
            while (k < expected)
            {
                const auto deadline = slot(k);
                pacer.waitUntil(deadline);
                const double c0 = cpuClk.nowNs();
                const auto w0 = Clock::now();
                rt.process(in, out, kBlock);
                const auto w1 = Clock::now();
                const double c1 = cpuClk.nowNs();
                maxMacs = std::max(maxMacs, rt.engine().convolver().lastProcessMultiplyAdds());
                wall.push_back(std::chrono::duration<double, std::micro>(w1 - w0).count());
                cpu.push_back((c1 - c0) / 1000.0);
                wakeLateMaxUs = std::max(wakeLateMaxUs,
                                         std::chrono::duration<double, std::micro>(w0 - deadline).count());
                ++k;
                // A slot whose successor's time has also passed is skipped (counted missed), as a driver
                // drops a buffer it could not hand over: a late callback still runs at once.
                const double elapsedUs =
                    std::chrono::duration<double, std::micro>(Clock::now() - start).count();
                const auto latest = static_cast<std::size_t>(elapsedUs / periodUs);
                if (latest > k)
                {
                    const std::size_t skip = std::min(latest, expected) - k;
                    missed += skip;
                    k += skip;
                }
            }
        });
        callback.join();
        stop.store(true);
        churn.join();
        REQUIRE(pipeline_test::waitFor(othersIdle, std::chrono::minutes(5)));
        Point pt;
        pt.builders = builders;
        pt.callbacks = wall.size();
        pt.missedSlots = missed;
        for (const double w : wall)
        {
            if (w > periodUs)
                ++pt.overPeriod;
            if (w > 0.5 * periodUs)
                ++pt.overHalf;
        }
        for (const double c : cpu)
            if (c > 0.5 * periodUs)
                ++pt.cpuOverHalf;
        std::sort(wall.begin(), wall.end());
        std::sort(cpu.begin(), cpu.end());
        pt.wallP999 = quantile(wall, 0.999);
        points.push_back(pt);
        const bool valid = static_cast<double>(pt.callbacks) >= 0.95 * static_cast<double>(expected);
        if (builders == 0)
            std::printf("07c1b-records (c) B1-b instrument: %s; %s\n", timer.c_str(), cpuClock.c_str());
        std::printf(
            "07c1b-records (c) B1-b callback, %d concurrent builder%s at 100 m, buffer %d @ %.0f Hz (period "
            "%.0f us), %.0f s: callbacks %zu / %zu expected (missed slots %zu); wall us median %.1f p99 %.1f "
            "p99.9 %.1f max %.1f; thread CPU us median %.1f p99 %.1f p99.9 %.1f max %.1f; overruns (wall) > "
            "period %zu, > period/2 %zu (CPU > period/2 %zu); wake late max %.0f us; max multiply-adds per "
            "callback %llu; hardware_concurrency %u; priority: %s%s\n",
            builders, builders == 1 ? "" : "s", kBlock, kFs, periodUs, kSeconds, pt.callbacks, expected,
            missed, quantile(wall, 0.5), quantile(wall, 0.99), pt.wallP999, wall.back(), quantile(cpu, 0.5),
            quantile(cpu, 0.99), quantile(cpu, 0.999), cpu.back(), pt.overPeriod, pt.overHalf, pt.cpuOverHalf,
            wakeLateMaxUs, static_cast<unsigned long long>(maxMacs), hw, priority.c_str(),
            valid ? "" : "  INSTRUMENT INVALID (callbacks < 0.95 x expected)");
    }
    // Beside the old instrument (R16), and the residual reading (D-B1 item 6): an overrun > period at 8
    // builders with none at 0. Printed only.
    std::string beside;
    const Point* floor0 = nullptr;
    const Point* top8 = nullptr;
    for (const auto& pt : points)
    {
        char buf[96];
        const auto o = oldP999.find(pt.builders);
        if (o != oldP999.end())
            std::snprintf(buf, sizeof(buf), "%s%d: %.0f (old %.0f)", beside.empty() ? "" : "; ", pt.builders,
                          pt.wallP999, o->second);
        else
            std::snprintf(buf, sizeof(buf), "%s%d: %.0f (old n/a)", beside.empty() ? "" : "; ", pt.builders,
                          pt.wallP999);
        beside += buf;
        if (pt.builders == 0)
            floor0 = &pt;
        if (pt.builders == 8)
            top8 = &pt;
    }
    const bool residual = floor0 != nullptr && top8 != nullptr && top8->overPeriod > 0
                          && floor0->overPeriod == 0;
    std::printf(
        "07c1b-records (c) B1-b beside the old instrument (R16), wall p99.9 us by builders: %s; "
        "overruns > period at 0 / 8 builders %zu / %zu%s\n",
        beside.c_str(), floor0 != nullptr ? floor0->overPeriod : 0, top8 != nullptr ? top8->overPeriod : 0,
        residual ? "  RESIDUAL: overrun at 8 builders with a clean floor (D-B1 item 6: phase-13-3 scope 4 "
                   "and the R5 Windows machine; a miss opens 13-1b)"
                 : "");
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

// Phase-07c-1 condition 10 (D-H3 (e); AX38 (i) register entry): the enter-offline path cancels and never
// waits. Records, never CHECKs: the host call (setNonRealtime(true)), the cancel unwind (from the call until
// the abandoned decision has left its last cancel point), the first offline block (it waits for that unwind,
// then builds) and the AX38 (i) transient-memory record (the PROCESS resident-set delta, sampled every 2 ms,
// while an abandoned build's ISM / synthesis may still overlap the offline build), at the low-alpha 100 m
// cube, 48 and 96 kHz, with the cancel landing at several points of the build (ISM, solve, synthesis,
// assembly).
TEST_CASE("records: condition 10 enter-offline cancel latency and transient memory at the 100 m cube",
          "[.][benchmark][records-07c1-cond10]")
{
    const char* key = "cube100_lowalpha0.05_s0.3";
    const auto sc = cube(key);
    const auto values = module3d::parameterValuesFromScene(sc);
    const float w = static_cast<float>(sc.room.geometry.dimensions.x);
    for (const double fs : {48000.0, 96000.0})
    {
        // The uncancelled rebuild time of a room-size edit sets where the cancels land.
        double rebuildMs = 0.0;
        {
            plugin::ScenePipeline pipe;
            pipe.beginRestore();
            pipe.restore(sc, values);
            pipe.prepare(fs, 512, false);
            const auto t0 = Clock::now();
            pipe.setParameter(module3d::kRoomW, w - 1.0f);
            while (!pipe.builderIdle())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            rebuildMs = ms(t0, Clock::now());
        }
        double worstCall = 0.0, worstUnwind = 0.0, worstFirstBlock = 0.0, worstDeltaMb = 0.0;
        for (const double frac : {0.02, 0.1, 0.3, 0.6, 0.9})
        {
            plugin::ScenePipeline pipe;
            pipe.beginRestore();
            pipe.restore(sc, values);
            pipe.prepare(fs, 512, false);
            const long rssBefore = test_memory::currentRssKb();
            std::atomic<long> rssMax{rssBefore};
            std::atomic<bool> sampling{true};
            std::thread sampler([&] {
                while (sampling.load())
                {
                    const long r = test_memory::currentRssKb();
                    long m = rssMax.load();
                    while (r > m && !rssMax.compare_exchange_weak(m, r))
                    {}
                    std::this_thread::sleep_for(std::chrono::milliseconds(2));
                }
            });
            pipe.setParameter(module3d::kRoomW, w - 2.0f);
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(frac * rebuildMs));
            const bool wasBusy = pipe.builderBusy();
            const auto t0 = Clock::now();
            pipe.setNonRealtime(true);
            const double callMs = ms(t0, Clock::now());
            while (pipe.builderBusy())
                std::this_thread::sleep_for(std::chrono::microseconds(200));
            const double unwindMs = ms(t0, Clock::now());
            // The first offline block (on the next host block: here, right after the unwind was observed).
            std::vector<float> l(512, 0.0f), r(512, 0.0f);
            const float* const in[2] = {l.data(), r.data()};
            float* const out[2] = {l.data(), r.data()};
            const auto tb = Clock::now();
            pipe.process(in, out, 512);
            const double firstBlockMs = ms(tb, Clock::now());
            sampling.store(false);
            sampler.join();
            const double deltaMb = (rssMax.load() - rssBefore) / 1024.0;
            std::printf(
                "07c1-records cond10 %-26s %6.0f Hz, %s: cancel at %.0f %% of a %.0f ms rebuild (builder "
                "%s): setNonRealtime(true) %.2f ms, cancel unwind %.1f ms, first offline block %.0f ms; "
                "transient RSS delta %.0f MB (process, RSS before %ld kB)%s\n",
                key, fs, kOsName, 100.0 * frac, rebuildMs, wasBusy ? "busy" : "idle", callMs, unwindMs,
                firstBlockMs, deltaMb, rssBefore, rssBefore == 0 ? "  [RSS n/a]" : "");
            worstCall = std::max(worstCall, callMs);
            worstUnwind = std::max(worstUnwind, unwindMs);
            worstFirstBlock = std::max(worstFirstBlock, firstBlockMs);
            worstDeltaMb = std::max(worstDeltaMb, deltaMb);
        }
        std::printf(
            "07c1-records cond10 %-26s %6.0f Hz, %s: WORST setNonRealtime(true) %.2f ms (was: the in-flight "
            "build, AX38 (i) entry 2 664 ms), cancel unwind %.1f ms, first offline block %.0f ms, transient "
            "RSS delta %.0f MB\n",
            key, fs, kOsName, worstCall, worstUnwind, worstFirstBlock, worstDeltaMb);
    }
}

// Phase-07c-1 condition 12 (D-G1), records (d) and (f), never CHECKs: with the gate around the solve only,
// several builds (ISM planning and unit-decay synthesis) now run at once. (d) the worst quiesce() wait of one
// pipeline (a restore's beginRestore()) while N - 1 others synthesise, the cancel landing at a random point
// of its own rebuild; (f) the AX38 (i) transient-memory record as the PROCESS peak resident-set delta
// (sampled every 2 ms) with 4 and 8 concurrent builds of the 100 m low-alpha cube, at 48 and 96 kHz. A breach
// of the memory budget goes to Phase 13's memory budget (scope 1), never to an instance cap (PRD FR-3D-5,
// FR-3D-6, FR-SIM-7, A5), a W_max cut or a range change (D-H1 (v)(d)).
TEST_CASE("records: condition 12 (d) quiesce with N concurrent syntheses and (f) process memory with 4 / 8 "
          "concurrent builds at 100 m",
          "[.][benchmark][records-07c1-cond12]")
{
    const char* key = "cube100_lowalpha0.05_s0.3";
    const auto sc = cube(key);
    const auto values = module3d::parameterValuesFromScene(sc);
    const float w = static_cast<float>(sc.room.geometry.dimensions.x);
    std::mt19937_64 rng(0x07C12);
    for (const double fs : {48000.0, 96000.0})
        for (const int n : {1, 4, 8})
        {
            std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
            for (int i = 0; i < n; ++i)
            {
                pipes.push_back(std::make_unique<plugin::ScenePipeline>());
                pipes.back()->beginRestore();
                pipes.back()->restore(sc, values);
                pipes.back()->prepare(fs, 512, false);
            }
            const auto allIdle = [&] {
                for (auto& p : pipes)
                    if (!p->builderIdle())
                        return false;
                return true;
            };
            const long rssBefore = test_memory::currentRssKb();
            std::atomic<long> rssMax{rssBefore};
            std::atomic<bool> sampling{true};
            std::thread sampler([&] {
                while (sampling.load())
                {
                    const long r = test_memory::currentRssKb();
                    long m = rssMax.load();
                    while (r > m && !rssMax.compare_exchange_weak(m, r))
                    {}
                    std::this_thread::sleep_for(std::chrono::milliseconds(2));
                }
            });
            // (f): every instance rebuilds at once (a room-size edit), uncancelled.
            const auto t0 = Clock::now();
            for (auto& p : pipes)
                p->setParameter(module3d::kRoomW, w - 1.0f);
            while (!allIdle())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            const double allMs = ms(t0, Clock::now());
            const double peakMb = (rssMax.load() - rssBefore) / 1024.0;
            // (d): again, and pipeline 0 is quiesced at a random point of its rebuild.
            std::uniform_real_distribution<double> u(0.0, allMs / std::max(1, n) + 1.0);
            double worstWait = 0.0;
            for (int run = 0; run < 3; ++run)
            {
                for (auto& p : pipes)
                    p->setParameter(module3d::kRoomW, w - 2.0f - static_cast<float>(run));
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(u(rng)));
                const auto q0 = Clock::now();
                pipes[0]->beginRestore();
                worstWait = std::max(worstWait, ms(q0, Clock::now()));
                pipes[0]->restore(sc, values);
                while (!allIdle())
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            sampling.store(false);
            sampler.join();
            std::printf(
                "07c1-records cond12 %-26s %6.0f Hz, %s, %d concurrent build%s: all rebuilt in %.0f ms; "
                "(f) process peak RSS delta %.0f MB (RSS before %ld kB)%s; (d) worst quiesce wait %.0f ms "
                "(3 cancels at random points)\n",
                key, fs, kOsName, n, n == 1 ? "" : "s", allMs, peakMb, rssBefore,
                rssBefore == 0 ? " [RSS n/a]" : "", worstWait);
        }
}

// Phase-07c-1 record (h) (AX49; condition 9): restores in sequence on one thread (a host loading a project's
// instances one after another), keyed and keyless, at 1, 4 and 8 instances at T60_max 8 s; a T60_max sweep of
// 2, 8, 12, 20, 35 and 50 s at one instance; 100 m cubes; 48 and 96 kHz. Printed: per-instance time until
// audible (the restore's return: an IrSet with a tail is current) and the time from provisional to exact
// (until the last instance settled); the ISM latency of a T60-changing edit under the AX49 D5 bridge. Any
// 8-instance run over 5 s is flagged in print, never asserted. Its T60 sweep is an input to phase 07d.
// Phase-07c-1b (D-B4 C7', D-B2 B2-a'' / FM-10S; docs/review/phase-07c-1b/8-decider-decision-r2.md): per
// instance its restore time and the other instances' background builds at its start (Solve / Assemble, from
// a stage hook on builder threads), hardware_concurrency(), and at the rated corner (96 kHz, T60 8 s; 1 and 8
// instances) the prepare-first totals without a settle wait, interleaved and batched, beside the
// setState-first total, with the largest of the three named. Printed only.
TEST_CASE("records: phase-07c-1 record (h), project loads keyed and keyless, 1 / 4 / 8 instances, T60 sweep, "
          "D5-bridge ISM latency",
          "[.][benchmark][diffuse-records][record-h]")
{
    const auto cubeT60 = [](double t60) {
        // Uniform alpha for the target Sabine-Eyring T60 of a 100 m cube without air: alpha = 1 - e^(-0.161 V
        // / (S T60)); air absorption shortens the high bands, so T60_max (the 63 Hz band) is close to the
        // target.
        const double a = 1.0 - std::exp(-0.161 * 1.0e6 / (6.0e4 * t60));
        std::array<contract::BandArray, 6> alpha{};
        for (auto& f : alpha)
            f.fill(std::max(0.01, a));
        std::array<double, 6> s{};
        s.fill(0.3);
        auto sc = diffuse_test::scene({100.0, 100.0, 100.0}, alpha, s, {50.0, 30.0, 1.7},
                                      {{45.0, 70.0, 2.0}, {55.0, 70.0, 2.0}});
        return sc;
    };
    const auto settled = [](const plugin::ScenePipeline& p) { return !p.settling() && p.builderIdle(); };
    const auto savedFor = [&](const contract::SceneDescription& sc) {
        plugin::ScenePipeline src;
        src.prepare(48000.0, 512, false);
        src.beginRestore();
        src.restore(sc, module3d::parameterValuesFromScene(sc));
        REQUIRE(pipeline_test::waitFor([&] { return settled(src); }, std::chrono::minutes(5)));
        return src.savedDiffuse();
    };
    // Phase-07c-1b D-B4 (C7') and D-B2 (B2-a''): background builds at each restore's start. Each pipe gets a
    // stage hook storing its last build stage in an atomic, on builder threads only (calls on this host
    // thread, the synchronous prepare / restore, are ignored); at the start of restore i the other pipes
    // whose builderBusy() is true are counted by that stage. Counted as instances, each with up to 2 emitter
    // synthesis threads (AX49 parallel).
    const std::thread::id hostThread = std::this_thread::get_id();
    struct StageProbe
    {
        std::atomic<int> last{-1};
    };
    using Stage = plugin::ScenePipeline::BuildStage;
    const auto attachProbe = [hostThread](plugin::ScenePipeline& p, StageProbe& probe) {
        p.setStageHook([hostThread, &probe](Stage st) {
            if (std::this_thread::get_id() != hostThread)
                probe.last.store(static_cast<int>(st), std::memory_order_relaxed);
        });
    };
    struct Busy
    {
        int solve = 0, assemble = 0, other = 0; // other: Plan, Commit or no stage yet in this decision
        int queued = 0; // not busy but not idle: work waiting for the builder to start its decision
    };
    const auto busyAt = [](const std::vector<std::unique_ptr<plugin::ScenePipeline>>& pipes,
                           const std::vector<std::unique_ptr<StageProbe>>& probes, std::size_t self) {
        Busy b;
        for (std::size_t j = 0; j < pipes.size(); ++j)
        {
            if (j == self)
                continue;
            if (!pipes[j]->builderBusy())
            {
                if (!pipes[j]->builderIdle())
                    ++b.queued;
                continue;
            }
            const int st = probes[j]->last.load(std::memory_order_relaxed);
            if (st == static_cast<int>(Stage::Solve))
                ++b.solve;
            else if (st == static_cast<int>(Stage::Assemble))
                ++b.assemble;
            else
                ++b.other;
        }
        return b;
    };
    const auto joinBusy = [](const std::vector<Busy>& v) {
        std::string out;
        char buf[48];
        for (std::size_t i = 0; i < v.size(); ++i)
        {
            std::snprintf(buf, sizeof(buf), "%s%d(S%d/A%d/o%d)+q%d", i ? " " : "",
                          v[i].solve + v[i].assemble + v[i].other, v[i].solve, v[i].assemble, v[i].other,
                          v[i].queued);
            out += buf;
        }
        return out;
    };
    const unsigned hw = std::thread::hardware_concurrency();
    struct Result
    {
        double audibleMaxMs = 0.0, audibleSumMs = 0.0, exactMs = 0.0;
        // phase-07c-1b scope 6 (review M1): the instances' first prepares (instance insertion, outside the
        // restore window above): their synchronous stage-1 solves (Stats::insertSolves) and their wall time
        double insertMs = 0.0;
        std::uint64_t insertSolves = 0;
        // phase-07c-1b D-B4: per instance its restore time and the background builds at its start
        std::vector<double> restoreMs;
        std::vector<Busy> busy;
    };
    const auto run = [&](const contract::SceneDescription& sc, double fs, int instances,
                         const std::optional<plugin::SavedDiffuse>& saved) {
        Result r;
        std::vector<std::unique_ptr<StageProbe>> probes; // outlive the pipes (destroyed after them)
        std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
        const auto i0 = Clock::now();
        for (int i = 0; i < instances; ++i)
        {
            probes.push_back(std::make_unique<StageProbe>());
            pipes.push_back(std::make_unique<plugin::ScenePipeline>());
            attachProbe(*pipes.back(), *probes.back());
            pipes.back()->prepare(fs, 512, false);
        }
        r.insertMs = ms(i0, Clock::now());
        for (auto& p : pipes)
        {
            REQUIRE(pipeline_test::waitFor([&] { return settled(*p); }));
            r.insertSolves += p->stats().insertSolves;
        }
        const auto values = module3d::parameterValuesFromScene(sc);
        const auto t0 = Clock::now();
        for (std::size_t i = 0; i < pipes.size(); ++i) // in sequence on one thread
        {
            r.busy.push_back(busyAt(pipes, probes, i));
            const auto a = Clock::now();
            pipes[i]->beginRestore();
            pipes[i]->restore(sc, values, saved);
            const double d = ms(a, Clock::now());
            r.restoreMs.push_back(d);
            r.audibleMaxMs = std::max(r.audibleMaxMs, d);
            r.audibleSumMs += d;
        }
        for (auto& p : pipes)
            REQUIRE(pipeline_test::waitFor([&] { return settled(*p); }, std::chrono::minutes(10)));
        r.exactMs = ms(t0, Clock::now());
        return r;
    };
    const auto print = [&](const char* what, double t60, double fs, int n, bool keyed, const Result& r,
                           const sim::ProvisionalTiming& t) {
        std::printf(
            "07c1-records (h) %s T60 %4.0f s %6.0f Hz %d inst %-7s: until audible per instance max %.0f ms "
            "(sum %.0f ms); provisional -> exact (all settled) %.0f ms; L_p %.2f s / L %.2f s%s; insertion "
            "(outside "
            "the window): insertSolves %llu, first prepares %.0f ms%s\n",
            what, t60, fs, n, keyed ? "keyed" : "keyless", r.audibleMaxMs, r.audibleSumMs, r.exactMs, t.endS,
            t.exactS, t.provisional ? "" : " (exact in place)",
            static_cast<unsigned long long>(r.insertSolves), r.insertMs,
            n == 8 && r.audibleSumMs > 5000.0 ? "  FLAG: 8-instance load over 5 s (AX49 reversal input)"
                                              : "");
        std::printf(
            "07c1b-records (h) %s T60 %4.0f s %6.0f Hz %d inst %-7s setState-first order (prepares "
            "settled, then restores): restore per instance ms [%s]; other instances' builders busy at "
            "each restore start [%s] (busy count(Solve/Assemble/other) + q queued, instances, each up to 2 "
            "emitter "
            "threads, AX49); hardware_concurrency %u\n",
            what, t60, fs, n, keyed ? "keyed" : "keyless", joinMs(r.restoreMs).c_str(),
            joinBusy(r.busy).c_str(), hw);
    };
    // FM-10S (D-B2 B2-a''): the prepare-first host order with no settle wait between prepare and restore,
    // interleaved (prepare i, restore i, for each i) or batched (every prepare, then every restore); the
    // total runs from the first prepare to the last restore's return (the last instance audible).
    struct PrepareFirst
    {
        double totalMs = 0.0;
        std::vector<double> prepareMs, restoreMs;
        std::vector<Busy> busy;
    };
    const auto runPrepareFirst = [&](const contract::SceneDescription& sc, double fs, int instances,
                                     const std::optional<plugin::SavedDiffuse>& saved, bool interleaved) {
        PrepareFirst r;
        std::vector<std::unique_ptr<StageProbe>> probes; // outlive the pipes
        std::vector<std::unique_ptr<plugin::ScenePipeline>> pipes;
        const auto values = module3d::parameterValuesFromScene(sc);
        const auto restoreOne = [&](std::size_t i) {
            r.busy.push_back(busyAt(pipes, probes, i));
            const auto a = Clock::now();
            pipes[i]->beginRestore();
            pipes[i]->restore(sc, values, saved);
            r.restoreMs.push_back(ms(a, Clock::now()));
        };
        const auto t0 = Clock::now();
        for (int i = 0; i < instances; ++i)
        {
            probes.push_back(std::make_unique<StageProbe>());
            pipes.push_back(std::make_unique<plugin::ScenePipeline>());
            attachProbe(*pipes.back(), *probes.back());
            const auto a = Clock::now();
            pipes.back()->prepare(fs, 512, false);
            r.prepareMs.push_back(ms(a, Clock::now()));
            if (interleaved)
                restoreOne(pipes.size() - 1);
        }
        if (!interleaved)
            for (std::size_t i = 0; i < pipes.size(); ++i)
                restoreOne(i);
        r.totalMs = ms(t0, Clock::now());
        return r; // the pipes are destroyed here (their builders cancelled; not timed)
    };
    // setState-first totals of the rated corner (T60 8 s, 96 kHz) by (instances, keyed), from the loop below.
    std::map<std::pair<int, bool>, double> setStateFirst;
    std::optional<plugin::SavedDiffuse> savedAt8;
    for (const double t60 : {2.0, 8.0, 12.0, 20.0, 35.0, 50.0})
    {
        const auto sc = cubeT60(t60);
        const auto saved = savedFor(sc);
        REQUIRE(saved.has_value());
        const bool ratedCorner = t60 > 7.5 && t60 < 8.5;
        if (ratedCorner)
            savedAt8 = saved;
        for (const double fs : {48000.0, 96000.0})
        {
            sim::BuildOptions o;
            o.sampleRate = fs;
            o.kind = sim::BuildOptions::Kind::Omni;
            const auto timing = sim::StagedBuild::plan(sc, o).provisionalTiming();
            for (const int n : {1, 4, 8})
            {
                if (n > 1 && !ratedCorner)
                    continue; // instances at the rated corner (T60_max 8 s); the sweep at one instance
                for (const bool keyed : {false, true})
                {
                    const auto r = run(sc, fs, n, keyed ? saved : std::nullopt);
                    print("load", t60, fs, n, keyed, r, timing);
                    if (ratedCorner && fs > 90000.0)
                        setStateFirst[{n, keyed}] = r.audibleSumMs;
                }
            }
        }
    }
    // FM-10S: the three totals at the rated corner (96 kHz, T60 8 s), 1 and 8 instances, keyless and keyed;
    // which is largest is printed (phase-07d's 5 s criterion and AX38 (iv)'s 10 s line read the largest).
    REQUIRE(savedAt8.has_value());
    for (const int n : {1, 8})
        for (const bool keyed : {false, true})
        {
            const auto sc = cubeT60(8.0);
            const auto& saved = keyed ? savedAt8 : std::optional<plugin::SavedDiffuse>{};
            const auto inter = runPrepareFirst(sc, 96000.0, n, saved, true);
            const auto batch = runPrepareFirst(sc, 96000.0, n, saved, false);
            for (const auto* pf : {&inter, &batch})
                std::printf(
                    "07c1b-records (h) prepare-first %-11s T60 8 s 96000 Hz %d inst %-7s (no settle "
                    "wait): total %.0f ms; prepare per instance ms [%s]; restore per instance ms [%s]; "
                    "other instances' builders busy at each restore start [%s] (count(Solve/Assemble/"
                    "other) + q queued); hardware_concurrency %u\n",
                    pf == &inter ? "interleaved" : "batched", n, keyed ? "keyed" : "keyless", pf->totalMs,
                    joinMs(pf->prepareMs).c_str(), joinMs(pf->restoreMs).c_str(), joinBusy(pf->busy).c_str(),
                    hw);
            const double sf = setStateFirst.at({n, keyed});
            const char* largest = "setState-first";
            double largestMs = sf;
            if (inter.totalMs > largestMs)
            {
                largest = "prepare-first interleaved";
                largestMs = inter.totalMs;
            }
            if (batch.totalMs > largestMs)
            {
                largest = "prepare-first batched";
                largestMs = batch.totalMs;
            }
            std::printf(
                "07c1b-records (h) FM-10S T60 8 s 96000 Hz %d inst %-7s: prepare-first interleaved %.0f "
                "ms, prepare-first batched %.0f ms, setState-first %.0f ms (restore sum, prepares settled "
                "first); largest: %s %.0f ms%s%s\n",
                n, keyed ? "keyed" : "keyless", inter.totalMs, batch.totalMs, sf, largest, largestMs,
                n == 8 && largestMs > 5000.0 ? "  FLAG: over 5 s (phase-07d criterion)" : "",
                n == 8 && largestMs > 10000.0 ? "  FLAG: over 10 s (AX38 (iv) line)" : "");
        }
    // The D5 bridge: a T60-changing edit (room width) in a settled 100 m instance at T60 8 s; the ISM update
    // is submitted over the cached unit decays before the solve: its latency, and the time to the exact tail.
    for (const double fs : {48000.0, 96000.0})
    {
        const auto sc = cubeT60(8.0);
        plugin::ScenePipeline p;
        p.prepare(fs, 512, false);
        p.beginRestore();
        p.restore(sc, module3d::parameterValuesFromScene(sc));
        REQUIRE(pipeline_test::waitFor([&] { return settled(p); }, std::chrono::minutes(5)));
        std::vector<double> ism, exact;
        for (int i = 0; i < 3; ++i)
        {
            const auto before = p.stats().interimSubmits;
            const auto t0 = Clock::now();
            p.setParameter(module3d::kRoomW, p.parameter(module3d::kRoomW) - 2.0f);
            REQUIRE(pipeline_test::waitFor([&] { return p.stats().interimSubmits > before; }));
            ism.push_back(ms(t0, Clock::now()));
            REQUIRE(pipeline_test::waitFor([&] { return settled(p); }, std::chrono::minutes(5)));
            exact.push_back(ms(t0, Clock::now()));
        }
        const auto si = spread(ism), se = spread(exact);
        std::printf(
            "07c1-records (h) D5 bridge T60 8 s %6.0f Hz: ISM latency of a T60-changing edit min %.0f median "
            "%.0f max %.0f ms; to the exact tail median %.0f ms (3 edits)\n",
            fs, si.min, si.median, si.max, se.median);
    }
}

namespace {
// FNV-1a 64 over the E_b of the fingerprint fixtures, in fixture order (shared by the pinned test and its
// negative check, phase-07c-1b scope 4).
std::uint64_t ax48FingerprintHash(const std::vector<sim::EmitterBands>& levels)
{
    std::uint64_t h = 0xcbf29ce484222325ull;
    for (const auto& level : levels)
    {
        const auto* c = reinterpret_cast<const unsigned char*>(level.data());
        for (std::size_t i = 0; i < sizeof(sim::EmitterBands); ++i)
        {
            h ^= c[i];
            h *= 0x100000001b3ull;
        }
    }
    return h;
}
} // namespace

// Phase-07c-1 AX48 E_model fingerprint: the E_b of the fingerprint fixtures (the two gated 100 m cubes, the
// flutter cube triggering the AX22 ISM fallback, and the low-alpha s = 1 cube, air-dominated in the upper
// bands) hashed bit for bit, per platform, with DiffuseLimits and kEstimatorModelId. A change of E_b with the
// limits unchanged must bump kEstimatorModelId (and is a step for every saved project: AX48's engine-mismatch
// policy); this test fails otherwise. A platform without a pin prints PROVISIONAL (pinned from its first CI
// run, with a CHANGELOG reason).
TEST_CASE("records: AX48 E_model fingerprint of E_b on the fingerprint fixtures",
          "[.][benchmark][ax48-fingerprint]")
{
    struct Pin
    {
        const char* os;
        std::uint32_t modelId;
        std::uint64_t hash;
    };
    // Pinned in phase-07c-1b (scope 4) from CI: each hash identical on runs 43242209571, 43258505284 and
    // 43291051799 (docs/review/phase-07c-1/41, 42, 44); 0 = not pinned. CHANGELOG: tests/golden/CHANGELOG.md.
    constexpr Pin kPins[] = {
        {"Linux", 1, 0x22f009efe0004e82ull},
        {"macOS", 1, 0x9d4f48216097ae94ull},
        {"Windows", 1, 0xa70a95cd5962863bull},
    };
    std::vector<sim::EmitterBands> levels;
    for (const char* key :
         {"cube100_flutter_fallback", "cube100_lowalpha0.05_s0.3", "cube100_lowalpha0.05_s1"})
    {
        sim::BuildOptions o;
        o.sampleRate = 48000.0;
        o.kind = sim::BuildOptions::Kind::Omni;
        auto build = sim::StagedBuild::plan(cube(key), o);
        build.solve();
        const auto level = build.diffuseLevel();
        REQUIRE(level.has_value());
        levels.push_back(*level);
        std::printf("07c1-records ax48 fingerprint %-26s E_b[0] 1 kHz %.17g\n", key, (*level)[0][4]);
    }
    const std::uint64_t h = ax48FingerprintHash(levels);
    for (const auto& pin : kPins)
        if (std::string(pin.os) == kOsName)
        {
            std::printf("07c1-records ax48 fingerprint os=%s modelId=%u hash=%016llx pinned=%016llx %s\n",
                        kOsName, sim::diffuse::kEstimatorModelId, static_cast<unsigned long long>(h),
                        static_cast<unsigned long long>(pin.hash),
                        pin.hash == 0 ? "PROVISIONAL (no pin yet)" : "");
            if (pin.hash != 0)
            {
                REQUIRE(sim::diffuse::kEstimatorModelId == pin.modelId);
                REQUIRE(
                    h == pin.hash); // E_b changed with DiffuseLimits unchanged: bump kEstimatorModelId (AX48)
            }
        }
}

// Phase-07c-1b scope 4, negative check: the fingerprint sees a change of E_b. One fixture's E_b (the flutter
// cube at 48 kHz, cheap enough for every Debug run) is hashed, then a single band of one emitter is moved by
// one ulp; the hash must differ, so the pinned comparison above fails on any change of E_b, however small.
TEST_CASE("records: AX48 fingerprint hash changes when E_b changes by one ulp", "[ax48-fingerprint-negative]")
{
    sim::BuildOptions o;
    o.sampleRate = 48000.0;
    o.kind = sim::BuildOptions::Kind::Omni;
    auto build = sim::StagedBuild::plan(cube("cube100_flutter_fallback"), o);
    build.solve();
    const auto level = build.diffuseLevel();
    REQUIRE(level.has_value());
    const std::uint64_t pinned = ax48FingerprintHash({*level});
    CHECK(ax48FingerprintHash({*level}) == pinned); // deterministic
    for (std::size_t e = 0; e < level->size(); ++e)
        for (std::size_t b = 0; b < (*level)[e].size(); ++b)
        {
            auto changed = *level;
            changed[e][b] = std::nextafter(changed[e][b], std::numeric_limits<double>::infinity());
            CHECK(ax48FingerprintHash({changed}) != pinned);
        }
}
