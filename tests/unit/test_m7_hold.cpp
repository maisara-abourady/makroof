// Phase 07c-2, measurements M7 and M7b of docs/review/phase-07c-2/8-decider-rebuttal-r2.md section 6 (context:
// docs/review/phase-07c-2/6-interrogator-on-file5.md row C-1). RECORDS ONLY: nothing here asserts a bound.
//
// M7: the ISM hold of a position edit (setParameter on kListenerY) that arrives at a seeded random point of a
// running builder solve: the time from the edit to the engine holding (submitIrSet, under stateMutex_) the
// first IrSet built from a snapshot that contains the edit (the interim of the next decision, whose early part
// is the edit's ISM; condition 4). From the code (C-1): the running solve is not abandoned by an edit
// (ScenePipeline::setParameter only bumps dirty_), so the hold is the rest of the solve plus the next
// decision's plan + interim. Baseline: the same edit with the builder idle.
//
// The W multiplier m runs the pipeline at W_scene = 2 x m x kWMaxPerEmitterProvisional through the
// validation-only seam ScenePipeline::setDiffuseLimitsForTest (W_scene = 2 W_max, AX41; n*_max, SE target,
// pilot and the joint rule as shipped). One instance, the process-wide gate pool as shipped
// (hardware_concurrency threads), 48 kHz.
//
// M7b (record only, no cancel-on-edit rule is implemented): from the measured idle-edit timings, the fraction
// of solves that would complete before the next edit if every edit cancelled the running solve, for an edit
// every 5 s (room size stepping 1 m) and every 100 ms (continuous automation): a solve completes iff the time
// from its edit to the end of its solve (C = interim + gate entry + solve) is below the edit interval. C is
// measured on position edits (10 per case) and on 2 room-size edits (kRoomD +-1 m) per case at m = 6, 8.
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/diffuse/DiffuseEstimator.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

namespace {

using Clock = std::chrono::steady_clock;
double msBetween(Clock::time_point a, Clock::time_point b)
{
    return std::chrono::duration<double, std::milli>(b - a).count();
}
std::int64_t nowNs()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now().time_since_epoch()).count();
}
Clock::time_point fromNs(std::int64_t ns)
{
    return Clock::time_point(std::chrono::duration_cast<Clock::duration>(std::chrono::nanoseconds(ns)));
}

#if defined(_WIN32)
constexpr const char* kOsName = "Windows";
#elif defined(__APPLE__)
constexpr const char* kOsName = "macOS";
#else
constexpr const char* kOsName = "Linux";
#endif

constexpr double kRate = 48000.0;
constexpr int kMultipliers[] = {1, 4, 5, 6, 8};
const int kOnlyCase = std::getenv("M7_ONLY") ? std::atoi(std::getenv("M7_ONLY")) : -1; // DEBUG
constexpr int kIdleEdits = 10;
constexpr int kMidEdits = 10;
constexpr int kRoomEdits = 2;   // per case at m = 6, 8 (M7b)
constexpr float kStepM = 0.05f; // listener y step per edit (every edit is a new diffuse problem)

struct Stats
{
    double median = 0.0, p95 = 0.0, worst = 0.0;
};
// p95 by nearest rank (ceil(0.95 n)); with n = 10 it is the worst.
Stats stats(std::vector<double> v)
{
    Stats s;
    if (v.empty())
        return s;
    std::sort(v.begin(), v.end());
    const std::size_t n = v.size();
    s.median = 0.5 * (v[(n - 1) / 2] + v[n / 2]);
    s.p95 = v[static_cast<std::size_t>(std::ceil(0.95 * static_cast<double>(n))) - 1];
    s.worst = v.back();
    return s;
}

// The scenes, as tests/unit/test_diffuse_wsweep.cpp builds them.
contract::SceneDescription layout4Corner()
{
    std::array<contract::BandArray, 6> alpha{};
    for (auto& a : alpha)
        a.fill(0.01);
    alpha[4].fill(1.0); // layout 4: absorbing floor
    std::array<double, 6> s1{};
    s1.fill(1.0);
    return diffuse_test::scene({20.0, 30.0, 10.0}, alpha, s1, {0.1, 0.1, 9.9}, {{7.0, 20.0, 2.0}, {13.0, 20.0, 2.0}});
}
contract::SceneDescription cubeLowAlphaS1()
{
    std::array<contract::BandArray, 6> alpha{};
    alpha.fill(diffuse_test::flat(0.05));
    std::array<double, 6> s{};
    s.fill(1.0);
    auto sc = diffuse_test::scene({100.0, 100.0, 100.0}, alpha, s, {50.0, 30.0, 1.7},
                                  {{45.0, 70.0, 2.0}, {55.0, 70.0, 2.0}});
    sc.render.outputMode = contract::OutputMode::binaural;
    return sc;
}

// Observes the builder's decisions through the test hooks (all called on the deciding thread).
struct Probe
{
    plugin::ScenePipeline& p;
    std::atomic<std::uint64_t> decisions{0}; // decision snapshots so far
    std::atomic<std::uint64_t> solveSeq{0};  // solves started so far
    std::atomic<std::uint64_t> solveDecision{0};
    std::atomic<std::int64_t> solveStartNs{0};
    std::atomic<std::uint64_t> endSeq{0}; // the solve whose end was seen last
    std::atomic<std::int64_t> solveEndNs{0};
    std::atomic<bool> inSolve{false};
    // The hold: the first commit of decision armDecision records the IrSet current before it.
    std::atomic<std::uint64_t> armDecision{0};
    std::atomic<bool> armed{false};
    std::shared_ptr<const sim::conv::IrSet> armPtr;
    std::mutex dbgM; std::string dbg;

    explicit Probe(plugin::ScenePipeline& pipe)
        : p(pipe)
    {
        p.setAfterSnapshotHook([this] {
            decisions.fetch_add(1);
            { std::lock_guard<std::mutex> l(dbgM); dbg += " |D" + std::to_string(decisions.load()) + " y=" + std::to_string(p.parameter(module3d::kListenerY)) + " st=" + std::to_string(p.stats().interimSubmits) + "/" + std::to_string(p.stats().finalSubmits) + "/" + std::to_string(p.stats().discardedMidDrag); }
            inSolve.store(false);
        });
        p.setStageHook([this](plugin::ScenePipeline::BuildStage stage) {
            using S = plugin::ScenePipeline::BuildStage;
            { std::lock_guard<std::mutex> l(dbgM); dbg += " " + std::to_string(static_cast<int>(stage)); }
            if (stage == S::Solve)
            {
                solveDecision.store(decisions.load());
                solveStartNs.store(nowNs());
                inSolve.store(true);
                solveSeq.fetch_add(1);
            }
            else if (stage == S::Assemble && inSolve.exchange(false))
            {
                solveEndNs.store(nowNs()); // the first stage after the solve (finishExact)
                endSeq.store(solveSeq.load());
            }
            else if (stage == S::Commit && !armed.load() && armDecision.load() != 0
                     && decisions.load() == armDecision.load())
            {
                armPtr = p.lastSubmittedIrSet(); // stateMutex_ is not held here
                armed.store(true);
            }
        });
    }
    ~Probe()
    {
        p.setStageHook({});
        p.setAfterSnapshotHook({});
    }

    // Arms the hold for the decision after the current one; returns the edit time.
    Clock::time_point editAndArm(float listenerY)
    {
        armed.store(false);
        armDecision.store(decisions.load() + 1);
        const auto t0 = Clock::now();
        p.setParameter(module3d::kListenerY, listenerY);
        return t0;
    }
    // Waits until the armed decision's first IrSet is in the engine; returns that time.
    Clock::time_point waitHold()
    {
        REQUIRE(pipeline_test::waitFor([&] { return armed.load(); }, std::chrono::seconds(120)));
        const auto before = armPtr;
        Clock::time_point t;
        const auto end = Clock::now() + std::chrono::seconds(120);
        while (p.lastSubmittedIrSet() == before)
        {
            REQUIRE(Clock::now() < end);
            std::this_thread::sleep_for(std::chrono::microseconds(50));
        }
        t = Clock::now();
        armDecision.store(0);
        return t;
    }
};

// The host's audio thread: process() in blocks of 256 at the real-time pace, so the engine installs each
// submitted IrSet (the convolver's request queue is drained only by process(); with nothing draining it,
// submits start to fail).
class AudioThread
{
public:
    explicit AudioThread(plugin::ScenePipeline& p)
        : thread_([this, &p] {
            constexpr int kBlock = 256;
            std::vector<float> l(kBlock, 0.0f), r(kBlock, 0.0f);
            const auto period = std::chrono::duration_cast<Clock::duration>(
                std::chrono::duration<double>(kBlock / kRate));
            auto next = Clock::now();
            while (!stop_.load())
            {
                std::fill(l.begin(), l.end(), 0.0f);
                std::fill(r.begin(), r.end(), 0.0f);
                const float* const in[2] = {l.data(), r.data()};
                float* const out[2] = {l.data(), r.data()};
                p.process(in, out, kBlock);
                next += period;
                std::this_thread::sleep_until(next);
            }
        })
    {}
    ~AudioThread()
    {
        stop_.store(true);
        thread_.join();
    }
    AudioThread(const AudioThread&) = delete;
    AudioThread& operator=(const AudioThread&) = delete;

private:
    std::atomic<bool> stop_{false};
    std::thread thread_;
};

void waitSettled(const plugin::ScenePipeline& p)
{
    REQUIRE(pipeline_test::waitFor([&] { return !p.settling() && p.builderIdle(); }, std::chrono::seconds(300)));
}

struct CaseResult
{
    std::string scene;
    int m = 0;
    std::vector<double> solveMs, idleHoldMs, midHoldMs, editToSolveEndMs, roomEditToSolveEndMs;
};

CaseResult runCase(const std::string& name, const contract::SceneDescription& sc, int m, std::uint64_t seed)
{
    CaseResult r;
    r.scene = name;
    r.m = m;
    plugin::ScenePipeline p;
    sim::diffuse::DiffuseLimits lim;
    lim.wScene = 2 * sim::diffuse::kWMaxPerEmitterProvisional * static_cast<std::int64_t>(m);
    p.setDiffuseLimitsForTest(lim);
    p.prepare(kRate, 256, false);
    p.beginRestore();
    p.restore(sc, module3d::parameterValuesFromScene(sc));
    waitSettled(p);
    AudioThread audio(p);
    Probe probe(p);
    const float y0 = p.parameter(module3d::kListenerY);
    int k = 0;
    const auto nextY = [&] { return y0 + kStepM * static_cast<float>(++k); };

    // Baseline: an edit with the builder idle; each runs one undisturbed solve (the solve durations).
    for (int i = 0; i < kIdleEdits; ++i)
    {
        const auto seq0 = probe.solveSeq.load();
        const auto t0 = probe.editAndArm(nextY());
        r.idleHoldMs.push_back(msBetween(t0, probe.waitHold()));
        waitSettled(p);
        REQUIRE(probe.endSeq.load() == seq0 + 1); // exactly one solve, run to its end
        r.solveMs.push_back(msBetween(fromNs(probe.solveStartNs.load()), fromNs(probe.solveEndNs.load())));
        r.editToSolveEndMs.push_back(msBetween(t0, fromNs(probe.solveEndNs.load())));
    }
    const double dMed = stats(r.solveMs).median;

    // Mid-solve: each edit lands at u x D_median after the start of the running solve (the previous edit's);
    // the next decision's solve is then the next trial's running solve.
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> uni(0.0, 1.0);
    (void)probe.editAndArm(nextY()); // the first running solve
    (void)probe.waitHold();
    int late = 0;
    for (int i = 0; i < kMidEdits; ++i)
    {
        const std::uint64_t want = probe.decisions.load(); // the decision of the latest edit
        REQUIRE(pipeline_test::waitFor([&] { return probe.solveDecision.load() == want; },
                                       std::chrono::seconds(120)));
        const auto seq = probe.solveSeq.load();
        const auto start = fromNs(probe.solveStartNs.load());
        const double u = uni(rng);
        std::this_thread::sleep_until(start + std::chrono::duration_cast<Clock::duration>(
                                                  std::chrono::duration<double, std::milli>(u * dMed)));
        const bool ended = probe.endSeq.load() == seq;
        late += ended ? 1 : 0;
        const auto st0 = p.stats();
        const auto dec0 = probe.decisions.load();
        const auto t0 = probe.editAndArm(nextY());
        const double hold = msBetween(t0, probe.waitHold());
        const auto st1 = p.stats();
        { std::lock_guard<std::mutex> l(probe.dbgM); std::printf("DBG %s\n", probe.dbg.c_str()); probe.dbg.clear(); }
        r.midHoldMs.push_back(hold);
        std::printf("07c2-m7trial os=%s scene=%s m=%d edit %d at %.1f ms into the solve (u=%.3f of D_med %.1f ms%s): "
                    "hold %.1f ms [decisions +%llu, interim +%llu, final +%llu, discarded +%llu]\n",
                    kOsName, name.c_str(), m, i, msBetween(start, t0), u, dMed,
                    ended ? ", solve already ended" : "", hold,
                    static_cast<unsigned long long>(probe.decisions.load() - dec0),
                    static_cast<unsigned long long>(st1.interimSubmits - st0.interimSubmits),
                    static_cast<unsigned long long>(st1.finalSubmits - st0.finalSubmits),
                    static_cast<unsigned long long>(st1.discardedMidDrag - st0.discardedMidDrag));
    }
    waitSettled(p);

    // M7b: room-size edits (kRoomD by 1 m: grown in the 20 x 30 x 10 m layout, whose listener sits in a
    // corner; shrunk in the 100 m cube), m = 6 and 8 only.
    if (m == 6 || m == 8)
    {
        const float d0 = p.parameter(module3d::kRoomD);
        const float dir = d0 > 50.0f ? -1.0f : 1.0f;
        for (int i = 0; i < kRoomEdits; ++i)
        {
            const auto seq0 = probe.solveSeq.load();
            probe.armDecision.store(0);
            const auto t0 = Clock::now();
            p.setParameter(module3d::kRoomD, d0 + dir * static_cast<float>(i + 1));
            waitSettled(p);
            REQUIRE(probe.endSeq.load() == seq0 + 1);
            r.roomEditToSolveEndMs.push_back(msBetween(t0, fromNs(probe.solveEndNs.load())));
        }
    }
    const auto sd = stats(r.solveMs), ih = stats(r.idleHoldMs), mh = stats(r.midHoldMs);
    std::printf("07c2-m7 os=%s scene=%s m=%d W_max/emitter=%lld pool=%u fs=48k | solve n=%zu median %.1f p95 %.1f "
                "worst %.1f ms | idle-edit hold n=%zu median %.1f p95 %.1f worst %.1f ms | mid-solve hold n=%zu "
                "median %.1f p95 %.1f worst %.1f ms (%d landed after the solve ended)\n",
                kOsName, name.c_str(), m,
                static_cast<long long>(sim::diffuse::kWMaxPerEmitterProvisional * static_cast<std::int64_t>(m)),
                p.gate().pool().size(), r.solveMs.size(), sd.median, sd.p95, sd.worst, r.idleHoldMs.size(),
                ih.median, ih.p95, ih.worst, r.midHoldMs.size(), mh.median, mh.p95, mh.worst, late);
    return r;
}

double fractionBelow(const std::vector<double>& v, double limitMs)
{
    if (v.empty())
        return 0.0;
    return static_cast<double>(std::count_if(v.begin(), v.end(), [&](double x) { return x < limitMs; }))
           / static_cast<double>(v.size());
}

} // namespace

TEST_CASE("ScenePipeline: the M7 diffuse-limits seam defaults to the shipped DiffuseLimits",
          "[pipeline][m7-seam]")
{
    plugin::ScenePipeline p;
    const sim::diffuse::DiffuseLimits shipped;
    const auto check = [](const sim::diffuse::DiffuseLimits& a, const sim::diffuse::DiffuseLimits& b) {
        CHECK(a.wScene == b.wScene);
        CHECK(a.nStarMax == b.nStarMax);
        CHECK(a.seTargetDb == b.seTargetDb);
        CHECK(a.fixedHistories == b.fixedHistories);
        CHECK(a.fixedStart == b.fixedStart);
        CHECK(a.historyOffset == b.historyOffset);
    };
    check(p.diffuseLimits(), shipped);
    CHECK(shipped.wScene == 2 * sim::diffuse::kWMaxPerEmitterProvisional);
    CHECK(shipped.nStarMax == sim::diffuse::kNStarMax);
    CHECK(shipped.seTargetDb == sim::diffuse::kSeTargetDb);
    sim::diffuse::DiffuseLimits x6 = shipped;
    x6.wScene *= 6;
    p.setDiffuseLimitsForTest(x6);
    check(p.diffuseLimits(), x6);
}

TEST_CASE("records: M7 ISM hold of a position edit during a running builder solve, m = 1, 4, 5, 6, 8; M7b",
          "[.][benchmark][m7-hold]")
{
    const struct
    {
        const char* name;
        contract::SceneDescription scene;
    } scenes[] = {{"layout4_s1/listener_corner", layout4Corner()}, {"cube100_lowalpha0.05_s1", cubeLowAlphaS1()}};
    std::vector<CaseResult> all;
    std::uint64_t seed = 0x07C20007;
    for (const auto& s : scenes)
        for (const int m : kMultipliers)
            if (kOnlyCase < 0 || kOnlyCase == m)
                all.push_back(runCase(s.name, s.scene, m, seed++));
    // M7b: cancel-on-edit, from the measured edit-to-solve-end times (not implemented in shipped code).
    for (const auto& r : all)
    {
        if (r.m != 6 && r.m != 8)
            continue;
        const auto c = stats(r.editToSolveEndMs);
        std::printf("07c2-m7b os=%s scene=%s m=%d cancel-on-edit (hypothetical): edit->solve end median %.1f worst "
                    "%.1f ms (n=%zu position edits); solves completing before the next edit: every 5 s %.0f%%, "
                    "every 100 ms %.0f%%",
                    kOsName, r.scene.c_str(), r.m, c.median, c.worst, r.editToSolveEndMs.size(),
                    100.0 * fractionBelow(r.editToSolveEndMs, 5000.0),
                    100.0 * fractionBelow(r.editToSolveEndMs, 100.0));
        const auto rc = stats(r.roomEditToSolveEndMs);
        std::printf(" | room size +-1 m (n=%zu): edit->solve end median %.1f worst %.1f ms; every 5 s %.0f%%, every "
                    "100 ms %.0f%%\n",
                    r.roomEditToSolveEndMs.size(), rc.median, rc.worst,
                    100.0 * fractionBelow(r.roomEditToSolveEndMs, 5000.0),
                    100.0 * fractionBelow(r.roomEditToSolveEndMs, 100.0));
    }
}
