// Phase 05h, scope 2: the AX38 diffuse-solve gate (src/plugin/core/DiffuseSolveGate.h), the solve seam
// (ScenePipeline::solveAndBuild) and the cancellation of a builder solve (AX39 D6); plus the AX37 (5.1)
// (i) FTZ/DAZ guard of buildRoomIR.
#include "AllocationTracker.h"
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "module3d/ParameterMap.h"
#include "plugin/core/DiffuseSolveGate.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Engine.h"
#include "sim/conv/Denormals.h"
#include "sim/diffuse/DiffuseEstimator.h"
#include "sim/diffuse/ThreadPool.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using Class = plugin::DiffuseSolveGate::Class;
using namespace std::chrono_literals;

namespace {

constexpr double kRate = 48000.0;

void restoreScene(plugin::ScenePipeline& p, const contract::SceneDescription& scene)
{
    p.beginRestore();
    p.restore(scene, module3d::parameterValuesFromScene(scene));
}

bool bitIdentical(const sim::RoomIR& a, const sim::RoomIR& b)
{
    if (a.taps.size() != b.taps.size() || a.length() != b.length())
        return false;
    for (std::size_t i = 0; i < a.taps.size(); ++i)
        if (std::memcmp(a.taps[i].data(), b.taps[i].data(), a.taps[i].size() * sizeof(float)) != 0)
            return false;
    return true;
}

// A scene whose build is long enough to be waited for (a large room, both emitters).
contract::SceneDescription slowScene()
{
    auto scene = pipeline_test::loadScene("medium_room.json");
    scene.room.geometry.dimensions = {40.0, 30.0, 12.0};
    scene.listener.position = {20.0, 8.0, 1.7};
    scene.emitters[0].position = {14.0, 20.0, 2.0};
    scene.emitters[1].position = {26.0, 20.0, 2.0};
    return scene;
}

void processBlocks(plugin::ScenePipeline& p, int blocks, std::size_t* allocs = nullptr,
                   std::size_t* frees = nullptr)
{
    std::vector<float> a(256, 0.1f), b(256, -0.1f);
    const float* const in[2] = {a.data(), b.data()};
    float* const out[2] = {a.data(), b.data()};
    for (int i = 0; i < blocks; ++i)
    {
        if (allocs != nullptr)
        {
            test_support::ScopedTracking tracking;
            p.process(in, out, 256);
            *allocs += tracking.allocations();
            *frees += tracking.deallocations();
        }
        else
            p.process(in, out, 256);
        std::this_thread::sleep_for(500us);
    }
}

} // namespace

TEST_CASE(
    "Diffuse-solve gate: synchronous first, then offline and builder in turn, FIFO within a class (AX38 (i))",
    "[pipeline][gate]")
{
    plugin::DiffuseSolveGate gate(1);
    REQUIRE(gate.enter(Class::Builder)); // the solve already running
    std::mutex mutex;
    std::vector<std::string> order;
    std::vector<bool> entered;
    std::atomic<bool> never{false};
    std::vector<std::thread> threads;
    const auto queue = [&](Class cls, const char* name, std::size_t expectWaiting) {
        threads.emplace_back([&, cls, name] {
            const bool ok = gate.enter(cls, &never);
            {
                std::lock_guard lock(mutex);
                order.push_back(name);
                entered.push_back(ok);
            }
            std::this_thread::sleep_for(2ms);
            if (ok)
                gate.leave();
        });
        REQUIRE(pipeline_test::waitFor([&] { return gate.waiting(cls) == expectWaiting; }));
    };
    queue(Class::Builder, "B1", 1);
    queue(Class::Offline, "O1", 1);
    queue(Class::Builder, "B2", 2);
    queue(Class::Offline, "O2", 2);
    queue(Class::Synchronous, "S1", 1);
    REQUIRE(gate.held());
    gate.leave();
    for (auto& t : threads)
        t.join();
    REQUIRE(order == std::vector<std::string>{"S1", "O1", "B1", "O2", "B2"});
    for (const bool ok : entered)
        REQUIRE(ok);
    REQUIRE_FALSE(gate.held());
    REQUIRE(gate.solvesCompleted() == 6);
}

TEST_CASE("Diffuse-solve gate: a builder waiter leaves the queue when its pipeline is quiesced",
          "[pipeline][gate]")
{
    plugin::DiffuseSolveGate gate(1);
    REQUIRE(gate.enter(Class::Synchronous));
    std::atomic<bool> abandon{false};
    std::atomic<int> result{-1};
    std::thread t([&] { result.store(gate.enter(Class::Builder, &abandon) ? 1 : 0); });
    REQUIRE(pipeline_test::waitFor([&] { return gate.waiting(Class::Builder) == 1; }));
    std::this_thread::sleep_for(20ms);
    REQUIRE(result.load() == -1); // still waiting: the gate is held
    abandon.store(true);
    gate.notifyWaiters();
    t.join();
    REQUIRE(result.load() == 0);
    REQUIRE(gate.waiting(Class::Builder) == 0);
    gate.leave();
    REQUIRE(gate.solvesCompleted() == 1); // the abandoned waiter never solved
}

TEST_CASE("buildRoomIR throws BuildCancelled when the cancel flag is set (AX39 D6)", "[sim][hybrid][diffuse]")
{
    const auto scene = pipeline_test::loadScene("living_room.json");
    sim::BuildOptions options;
    options.sampleRate = kRate;
    options.kind = sim::BuildOptions::Kind::Omni;
    std::atomic<bool> cancel{true};
    options.cancel = &cancel;
    REQUIRE_THROWS_AS(sim::buildRoomIR(scene, options), sim::BuildCancelled);
    cancel.store(false);
    REQUIRE(sim::buildRoomIR(scene, options).length() > 0);
}

TEST_CASE(
    "Pipeline: every pipeline shares one gate; gate order never changes the output (two pipelines in either "
    "order, one offline)",
    "[pipeline][gate]")
{
    const auto x = pipeline_test::loadScene("living_room.json");
    const auto y = pipeline_test::loadScene("club.json");
    // The pipeline builds the scene derived from the host parameters (module3d quantisation), so the
    // reference is that derived scene, built with the process pool and no gate (D4: pool-independent).
    sim::RoomIR refX, refY;
    {
        plugin::ScenePipeline p;
        restoreScene(p, x);
        refX = plugin::ScenePipeline::buildIr(p.currentScene(), kRate);
        restoreScene(p, y);
        refY = plugin::ScenePipeline::buildIr(p.currentScene(), kRate);
    }
    for (const bool xFirst : {true, false})
    {
        plugin::ScenePipeline a, b;
        REQUIRE(&a.gate() == &b.gate());
        a.prepare(kRate, 256, false);
        b.prepare(kRate, 256, false);
        if (xFirst)
        {
            restoreScene(a, x);
            restoreScene(b, y);
        }
        else
        {
            restoreScene(b, y);
            restoreScene(a, x);
        }
        REQUIRE(bitIdentical(*a.lastSubmittedIr(), refX));
        REQUIRE(bitIdentical(*b.lastSubmittedIr(), refY));
    }
    // One of them offline, the two solving at the same time.
    plugin::ScenePipeline rt, off;
    rt.prepare(kRate, 256, false);
    off.prepare(kRate, 256, true); // offline: stores the restore, solves in process()
    restoreScene(off, y);
    std::thread t([&] { restoreScene(rt, x); });
    processBlocks(off, 2);
    t.join();
    REQUIRE(bitIdentical(*rt.lastSubmittedIr(), refX));
    REQUIRE(bitIdentical(*off.lastSubmittedIr(), refY));
}

TEST_CASE(
    "Pipeline: a real-time pipeline beside one solving at the gate allocates nothing and never touches the "
    "gate (AX38 (i)); reset() goes through the synchronous class",
    "[pipeline][gate][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("allocation tracking is off in this build (ASan)");
    plugin::ScenePipeline rt, solver;
    restoreScene(rt, pipeline_test::loadScene("dead_booth.json"));
    rt.prepare(kRate, 256, false);
    REQUIRE(pipeline_test::waitFor([&] { return rt.builderIdle(); }));
    solver.prepare(kRate, 256, false);
    const auto before = rt.gate().solvesCompleted();
    std::atomic<bool> done{false};
    std::thread t([&] {
        const auto big = slowScene();
        restoreScene(solver, big);
        restoreScene(solver, plugin::defaultScene());
        restoreScene(solver, big);
        solver.reset(); // synchronous class, through the same seam (ResetStep3 rebuilds nothing new)
        done.store(true);
    });
    std::size_t allocs = 0, frees = 0;
    while (!done.load())
        processBlocks(rt, 4, &allocs, &frees);
    t.join();
    REQUIRE(allocs == 0);
    REQUIRE(frees == 0);
    // Only the solver's builds entered the gate (3 restores; reset() reused its last build).
    REQUIRE(rt.gate().solvesCompleted() == before + 3);
    REQUIRE(pipeline_test::waitFor([&] { return rt.builderIdle(); }));
    // D-H3 (e) (AX38 (i) register entry): Synchronous-class entries from a thread that had run a real-time
    // process() are counted (debug builds), never asserted; here none is expected (the solver's thread never
    // processed), so the count is a record of this harness, printed for the job summary. A host delivering
    // reset() on its processing thread would raise it; the remedy is phase-07c's reset() half.
    std::printf("gate: synchronous entries from a thread that ran a real-time process(): %llu (debug count; "
                "0 in release)\n",
                static_cast<unsigned long long>(rt.gate().synchronousEntriesFromRealtimeThreads()));
    // A reset() delivered on the real-time thread itself (what VST3 permits, file 12 F1/F6) is counted, not
    // asserted.
    {
        plugin::ScenePipeline host;
        restoreScene(host, pipeline_test::loadScene("dead_booth.json"));
        host.prepare(kRate, 256, false);
        REQUIRE(pipeline_test::waitFor([&] { return host.builderIdle(); }));
        const auto n0 = host.gate().synchronousEntriesFromRealtimeThreads();
        std::size_t a = 0, f = 0;
        processBlocks(host, 2, &a, &f); // this thread is now a "real-time" thread in the gate's eyes
        host.setParameter(module3d::kListenerX, 0.7f);
        REQUIRE(pipeline_test::waitFor([&] { return host.builderIdle(); }));
        host.reset(); // ResetStep3 reuses the last build: no gate entry expected
        const auto n1 = host.gate().synchronousEntriesFromRealtimeThreads();
        std::printf("gate: reset() on the thread that processed: %llu new synchronous entries from it (a "
                    "stale IR set "
                    "would make it 1; the register's growth print)\n",
                    static_cast<unsigned long long>(n1 - n0));
    }
}

TEST_CASE("Pipeline: two pipelines, one switching to offline in the middle of the other's solve (TSan)",
          "[pipeline][gate][tsan]")
{
    plugin::ScenePipeline a, b;
    a.prepare(kRate, 256, false);
    b.prepare(kRate, 256, false);
    std::atomic<bool> stop{false};
    std::thread params([&] {
        float w = 6.0f;
        while (!stop.load())
        {
            a.setParameter(module3d::kRoomW, w); // the builder of a solves after each change
            w = w > 30.0f ? 6.0f : w + 4.0f;
            std::this_thread::sleep_for(15ms);
        }
    });
    std::thread host([&] {
        for (int round = 0; round < 3 && !stop.load(); ++round)
        {
            restoreScene(b, slowScene());
            b.setNonRealtime(true); // while a's builder may be solving
            processBlocks(b, 3);
            b.setNonRealtime(false);
            std::this_thread::sleep_for(10ms);
        }
    });
    const auto end = std::chrono::steady_clock::now() + 800ms;
    while (std::chrono::steady_clock::now() < end)
        processBlocks(a, 4);
    host.join();
    stop.store(true);
    params.join();
    REQUIRE(pipeline_test::waitFor([&] { return a.builderIdle(); }));
    REQUIRE(b.lastSubmittedIr() != nullptr);
}

namespace {

contract::SceneDescription absorbentScene()
{
    auto scene = pipeline_test::loadScene("dead_booth.json");
    for (auto& s : scene.room.surfaces)
    {
        s.bandsAbsorption.fill(0.98);
        s.scattering = 1.0;
    }
    return scene;
}

// The absorbent room AX37 (5.1) (i) names (D-H3 (c), docs/review/phase-05h/20-decider-decision-D-H3.md; Seat
// 3's scene, positive on the direct detector at 48 and 96 kHz, file 18 K-c3): dead_booth geometry, alpha 0.01
// at 63 Hz and 0.999 above, s 0.5. The fast bands' exp(-rate j) in BandNoiseGenerator::make reach the double
// subnormal range inside the 63 Hz band's long tail; the IR stays bit-identical because the whole path is
// double and the final conversion flushes (Engine.cpp toFloatNoDenormal). The denormal needs the
// long/short-band ratio (a near-rigid 63 Hz band, T60 about 5.9 s, against fast bands decaying in about 8.6
// ms), not absorbency as such: alpha 0.999 on every band reads clear (file 18 K-c3), so absorbentScene()
// reading clear is not a regression (D-H3 (c), P05H-60).
contract::SceneDescription denormalScene()
{
    auto scene = pipeline_test::loadScene("dead_booth.json");
    for (auto& s : scene.room.surfaces)
    {
        s.bandsAbsorption = {0.01, 0.999, 0.999, 0.999, 0.999, 0.999, 0.999, 0.999};
        s.scattering = 0.5;
    }
    return scene;
}

} // namespace

namespace {
// Sticky FPU exception flags, read as (denormal-operand, underflow). x86-64 MXCSR: DE bit 1 (a denormal
// operand was consumed; not set under DAZ), UE bit 4 (a tiny inexact result; set when FTZ flushes one).
// AArch64 FPSR: IDC bit 7 (an input denormal was flushed because FZ = 1; never set with FZ off), UFC bit 3
// (underflow). So a denormal shows as DE or UE without the guard on x86, and as UFC without the guard / IDC
// or UFC with it on AArch64 (Seat 5, file 17-seat5 addendum): the probe prints both bits and both arms per
// architecture.
struct DenormalFlags
{
    bool operand = false;
    bool underflow = false;
};
DenormalFlags denormalFlags() noexcept
{
    DenormalFlags f;
#if defined(SPATIAL_DENORMALS_SSE)
    const unsigned csr = _mm_getcsr();
    f.operand = (csr & 0x2u) != 0;
    f.underflow = (csr & 0x10u) != 0;
#elif defined(SPATIAL_DENORMALS_AARCH64)
    std::uint64_t fpsr = 0;
    asm volatile("mrs %0, fpsr" : "=r"(fpsr) : : "memory");
    f.operand = (fpsr & 0x80u) != 0;
    f.underflow = (fpsr & 0x8u) != 0;
#endif
    return f;
}
void clearDenormalFlags() noexcept
{
#if defined(SPATIAL_DENORMALS_SSE)
    _mm_setcsr(_mm_getcsr() & ~0x3Fu); // the six sticky exception flags
#elif defined(SPATIAL_DENORMALS_AARCH64)
    std::uint64_t fpsr = 0;
    asm volatile("mrs %0, fpsr" : "=r"(fpsr) : : "memory");
    fpsr &= ~0xFFull;
    asm volatile("msr fpsr, %0" : : "r"(fpsr) : "memory");
#endif
}
const char* flagText(DenormalFlags f) noexcept
{
    return f.operand && f.underflow ? "operand+underflow"
           : f.operand              ? "operand"
           : f.underflow            ? "underflow"
                                    : "clear";
}
// Calibration (Seat 5): the detector must see a known denormal operand and a known underflow, else it SKIPs.
// Calibration, per architecture. x86-64: a denormal operand sets DE and an underflowing product sets UE with
// FTZ/DAZ off. AArch64 (K-c4, the macOS run of 2026-11-10: with FZ off neither a denormal operand nor an
// underflowing product raised a cumulative flag on Apple silicon), so there the observable is IDC under FZ =
// 1, the guard's own mode: a denormal operand consumed while flushing sets IDC. The arms the [pipeline] test
// asserts follow: x86-64 asserts the flags in the unguarded arm; AArch64 asserts IDC in the guarded arm.
bool calibrateDetector(bool& operandSeenWithoutGuard)
{
    volatile double tiny = 1e-310, one = 1.0, small = 1e-300, smaller = 1e-20;
    clearDenormalFlags();
    volatile double a = tiny * one; // a denormal operand
    const auto f1 = denormalFlags();
    clearDenormalFlags();
    volatile double b = small * smaller; // an underflowing result
    const auto f2 = denormalFlags();
    (void)a;
    (void)b;
    operandSeenWithoutGuard = f1.operand;
#if defined(SPATIAL_DENORMALS_AARCH64)
    DenormalFlags f3;
    {
        const sim::conv::ScopedFlushDenormals fz;
        clearDenormalFlags();
        volatile double c = tiny * one; // a denormal operand flushed under FZ = 1 -> IDC
        f3 = denormalFlags();
        (void)c;
    }
    return f3.operand || ((f1.operand || f1.underflow) && f2.underflow);
#else
    return (f1.operand || f1.underflow) && f2.underflow;
#endif
}
} // namespace

// AX37 (5.1) (i): buildRoomIR sets FTZ/DAZ through a scoped guard, so the IR does not depend on the
// caller's mode. Built with the caller's FTZ off (the test thread's default) and on.
TEST_CASE(
    "buildRoomIR: the IR is bit-identical with the caller's FTZ/DAZ off and on (AX37 (5.1) (i)); the named "
    "room (near-rigid 63 Hz band, absorbent above) produces denormals without FTZ (direct detector, per "
    "architecture)",
    "[pipeline][ftz]")
{
    if (!sim::conv::ScopedFlushDenormals::isSupported())
        SKIP("no FTZ/DAZ control on this platform");
    sim::BuildOptions options;
    options.sampleRate = kRate;
    options.kind = sim::BuildOptions::Kind::Omni;
    for (const auto& scene :
         {denormalScene(), absorbentScene(), pipeline_test::loadScene("medium_room.json")})
    {
        const sim::RoomIR off = sim::buildRoomIR(scene, options);
        sim::RoomIR on;
        {
            const sim::conv::ScopedFlushDenormals ftz;
            on = sim::buildRoomIR(scene, options);
        }
        REQUIRE(bitIdentical(off, on));
    }
    // The premise, asserted on the named scene (D-H3 (c)): an unguarded build (validation-only ftzGuard =
    // false), every solve block on this thread, sets the FPU's sticky denormal flags with FTZ off; with
    // FTZ/DAZ on the operand flag stays clear on x86-64 (DAZ suppresses DE; the flushed results still raise
    // UE) and on AArch64 the input-denormal flag IDC is raised only under FZ = 1 (Seat 5's reading, decided
    // by the three-OS run).
    bool operandWithoutGuard = false;
    if (!calibrateDetector(operandWithoutGuard))
        SKIP("the FPU status-flag detector did not see a known denormal / underflow on this platform");
    sim::diffuse::ThreadPool oneThread(1);
    sim::BuildOptions unguarded = options;
    unguarded.ftzGuard = false;
    unguarded.diffusePool = &oneThread;
    clearDenormalFlags();
    const sim::RoomIR off = sim::buildRoomIR(denormalScene(), unguarded);
    const auto flagsOff = denormalFlags();
    sim::RoomIR on;
    DenormalFlags flagsOn;
    {
        const sim::conv::ScopedFlushDenormals ftz;
        clearDenormalFlags();
        on = sim::buildRoomIR(denormalScene(), unguarded);
        flagsOn = denormalFlags();
    }
    std::printf(
        "ftz: the absorbent room without the guard: flags FTZ off [%s], FTZ on [%s]; IRs %s (operand flag "
        "without the guard on this architecture: %s)\n",
        flagText(flagsOff), flagText(flagsOn), bitIdentical(off, on) ? "bit-identical" : "DIFFERENT",
        operandWithoutGuard ? "yes" : "no");
    REQUIRE(bitIdentical(off, on));
#if defined(SPATIAL_DENORMALS_SSE)
    REQUIRE((flagsOff.operand || flagsOff.underflow)); // DE | UE set: denormals arose
    REQUIRE_FALSE(flagsOn.operand);                    // DAZ: no denormal operand reaches an instruction
#elif defined(SPATIAL_DENORMALS_AARCH64)
    // K-c4 (the macOS run): with FZ off no cumulative flag is raised on Apple silicon, so the premise is read
    // in the guarded arm: a denormal operand was consumed and flushed under FZ = 1 (IDC), which is what the
    // guard is for.
    REQUIRE(flagsOn.operand);
#endif
}

// AX37 (5.1) (i), second half: the absorbent room is asserted to produce denormals without FTZ. The build
// runs WITHOUT the guard (BuildOptions::ftzGuard = false, validation only) in the caller's mode, FTZ off and
// on; the IRs differing proves a denormal was flushed somewhere on the IR path. Where no probed scene
// differs, that is a finding for the decider (docs/review/phase-05h/11-orchestrator-D-H3-question.md), never
// a silent drop.
TEST_CASE("probe: denormals on the IR path (buildRoomIR without the guard, FTZ off vs on)",
          "[.][probe-denormals-ir]")
{
    if (!sim::conv::ScopedFlushDenormals::isSupported())
        SKIP("no FTZ/DAZ control on this platform");
    struct Probe
    {
        const char* label;
        contract::SceneDescription scene;
    };
    std::vector<Probe> probes;
    probes.push_back({"absorbentScene (dead_booth, alpha 0.98, s 1)", absorbentScene()});
    for (const char* name : {"dead_booth.json", "edge_values.json", "open_field.json", "medium_room.json"})
        probes.push_back({name, pipeline_test::loadScene(name)});
    {
        auto sc = pipeline_test::loadScene("dead_booth.json");
        for (auto& s : sc.room.surfaces)
        {
            s.bandsAbsorption.fill(0.999);
            s.scattering = 0.5;
        }
        probes.push_back({"dead_booth alpha 0.999 s 0.5", sc});
        sc.room.geometry.dimensions = {100.0, 100.0, 100.0};
        sc.listener.position = {50.0, 30.0, 1.7};
        sc.emitters[0].position = {45.0, 70.0, 2.0};
        sc.emitters[1].position = {55.0, 70.0, 2.0};
        probes.push_back({"100 m cube alpha 0.999 s 0.5", sc});
        for (auto& s : sc.room.surfaces)
            s.bandsAbsorption = {0.01, 0.01, 0.5, 0.999, 0.999, 0.999, 0.999, 0.999};
        probes.push_back({"100 m cube alpha 0.01 at 63/125 Hz, 0.999 above", sc});
    }
    for (const double fs : {48000.0, 96000.0})
        for (const auto& pr : probes)
        {
            sim::BuildOptions o;
            o.sampleRate = fs;
            o.kind = sim::BuildOptions::Kind::Omni;
            o.ftzGuard = false;
            const sim::RoomIR off = sim::buildRoomIR(pr.scene, o);
            sim::RoomIR on;
            {
                const sim::conv::ScopedFlushDenormals ftz;
                on = sim::buildRoomIR(pr.scene, o);
            }
            std::printf("probe-ir fs %.0f %-45s: IR without the guard, FTZ off vs on -> %s\n", fs, pr.label,
                        bitIdentical(off, on) ? "identical (no denormal reached the IR)"
                                              : "DIFFERENT (denormals matter)");
        }
}

// Direct detector (hidden; D-H3 (c), docs/review/phase-05h/16-decider-convene-D-H3.md K-c3): the sticky
// denormal-operand status flag of the FPU, read after an unguarded build with FTZ/DAZ off. x86-64: MXCSR DE
// (bit 1); AArch64: FPSR IDC (bit 7). Unlike the bit-difference probe above, this sees a denormal that arose
// and was flushed without changing an output bit (the whole build path is double; the IR is float only at the
// end, Engine.cpp toFloatNoDenormal). Seat 3's candidate (file 17-seat3): a dead_booth-sized room with alpha
// 0.01 at 63 Hz and 0.999 above, whose fast bands' exp(-rate j) in BandNoiseGenerator::make reach the double
// subnormal range (708 < rate j < 745) inside the 63 Hz band's long tail.

TEST_CASE("probe: denormals on the IR path, direct FPU status-flag detector (unguarded build, FTZ off)",
          "[.][probe-denormals-detector]")
{
    if (!sim::conv::ScopedFlushDenormals::isSupported())
        SKIP("no FTZ/DAZ control on this platform");
    struct Probe
    {
        const char* label;
        contract::SceneDescription scene;
    };
    std::vector<Probe> probes;
    probes.push_back({"absorbentScene (dead_booth, alpha 0.98, s 1)", absorbentScene()});
    for (const char* name : {"dead_booth.json", "edge_values.json", "open_field.json", "medium_room.json"})
        probes.push_back({name, pipeline_test::loadScene(name)});
    {
        auto sc = pipeline_test::loadScene("dead_booth.json");
        for (auto& s : sc.room.surfaces)
        {
            s.bandsAbsorption = {0.01, 0.999, 0.999, 0.999, 0.999, 0.999, 0.999, 0.999};
            s.scattering = 0.5;
        }
        probes.push_back({"dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3)", sc});
        for (auto& s : sc.room.surfaces)
            s.bandsAbsorption.fill(0.999);
        probes.push_back({"dead_booth alpha 0.999 s 0.5", sc});
        sc.room.geometry.dimensions = {100.0, 100.0, 100.0};
        sc.listener.position = {50.0, 30.0, 1.7};
        sc.emitters[0].position = {45.0, 70.0, 2.0};
        sc.emitters[1].position = {55.0, 70.0, 2.0};
        probes.push_back({"100 m cube alpha 0.999 s 0.5", sc});
        for (auto& s : sc.room.surfaces)
            s.bandsAbsorption = {0.01, 0.01, 0.5, 0.999, 0.999, 0.999, 0.999, 0.999};
        probes.push_back({"100 m cube alpha 0.01 at 63/125 Hz, 0.999 above", sc});
    }
    bool operandWithoutGuard = false;
    if (!calibrateDetector(operandWithoutGuard))
        SKIP("the FPU status-flag detector did not see a known denormal / underflow on this platform");
    std::printf(
        "probe-detector calibration: a denormal operand without the guard reads as %s on this architecture\n",
        operandWithoutGuard ? "operand" : "underflow only (AArch64 form)");
    sim::diffuse::ThreadPool oneThread(
        1); // every solve block runs on the instrumented thread (D4: same result)
    for (const double fs : {48000.0, 96000.0})
        for (const auto& pr : probes)
        {
            sim::BuildOptions o;
            o.sampleRate = fs;
            o.kind = sim::BuildOptions::Kind::Omni;
            o.ftzGuard = false;
            o.diffusePool = &oneThread;
            clearDenormalFlags();
            const sim::RoomIR off = sim::buildRoomIR(pr.scene, o);
            const auto flagsOff = denormalFlags();
            sim::RoomIR on;
            DenormalFlags flagsOn;
            {
                const sim::conv::ScopedFlushDenormals ftz;
                clearDenormalFlags();
                on = sim::buildRoomIR(pr.scene, o);
                flagsOn = denormalFlags();
            }
            std::printf("probe-detector fs %.0f %-55s: flags FTZ off [%s], FTZ on [%s]; IRs %s\n", fs,
                        pr.label, flagText(flagsOff), flagText(flagsOn),
                        bitIdentical(off, on) ? "bit-identical" : "DIFFERENT");
        }
}

// Probe (hidden): does any diffuse solve produce denormals without FTZ? Compares the unguarded
// estimator (estimateDiffuse directly, no buildRoomIR guard) between the caller's FTZ off and on: a
// different D5 hash or estimate means a denormal was flushed somewhere on a path.
TEST_CASE("probe: denormals in the diffuse estimator without the guard", "[.][probe-denormals]")
{
    for (const double alpha : {0.5, 0.9, 0.98, 0.999})
        for (const double dim : {3.0, 20.0, 100.0})
            for (const double s : {0.3, 1.0})
            {
                std::array<contract::BandArray, 6> a{};
                a.fill(diffuse_test::flat(alpha));
                const auto scene = diffuse_test::scene(
                    {dim, dim, dim * 0.4}, a, {s, s, s, s, s, s}, {dim * 0.5, dim * 0.3, dim * 0.1},
                    {{dim * 0.45, dim * 0.7, dim * 0.1}, {dim * 0.55, dim * 0.7, dim * 0.1}});
                const auto planned = diffuse_test::plan(scene);
                const auto off = sim::diffuse::estimateDiffuse(planned.problem);
                sim::diffuse::DiffuseResult on;
                {
                    const sim::conv::ScopedFlushDenormals ftz;
                    on = sim::diffuse::estimateDiffuse(planned.problem);
                }
                bool same = off.faceHash == on.faceHash && off.count.n == on.count.n;
                for (std::size_t e = 0; e < off.emitters.size() && same; ++e)
                    for (std::size_t k = 0; k < 8; ++k)
                        if (std::memcmp(&off.emitters[e].bandsDiffuse[k], &on.emitters[e].bandsDiffuse[k],
                                        sizeof(double))
                            != 0)
                            same = false;
                std::printf("probe alpha %.3f dim %.0f s %.1f: n* %lld N %lld hash off 0x%016llx on "
                            "0x%016llx -> %s\n",
                            alpha, dim, s, static_cast<long long>(off.nStar),
                            static_cast<long long>(off.count.n),
                            static_cast<unsigned long long>(off.faceHash),
                            static_cast<unsigned long long>(on.faceHash),
                            same ? "identical" : "DIFFERENT (denormals matter)");
            }
}

// Probe (hidden, orchestrator's split timer for D-H1, Seat 2's hand-off): where the non-diffuse 100 m,
// 96 kHz restore spends its time. Full build without the diffuse solve (tailLevelAx16) against the
// position-only build (cached unit decays): the difference is the unit-decay synthesis
// (tail::BandNoiseGenerator); the generator's constructor (the band spectra) is timed alone.
TEST_CASE("probe: split timer of the non-diffuse 100 m / 96 kHz build", "[.][probe-restore-split]")
{
    auto scene = pipeline_test::loadScene("medium_room.json");
    scene.room.geometry.dimensions = {100.0, 100.0, 100.0};
    scene.listener.position = {50.0, 30.0, 1.7};
    scene.emitters[0].position = {45.0, 70.0, 2.0};
    scene.emitters[1].position = {55.0, 70.0, 2.0};
    for (auto& s : scene.room.surfaces)
    {
        s.bandsAbsorption.fill(0.05);
        s.scattering = 0.3;
    }
    using Clock = std::chrono::steady_clock;
    const auto ms = [](Clock::time_point a, Clock::time_point b) {
        return std::chrono::duration<double, std::milli>(b - a).count();
    };
    for (const double fs : {96000.0, 48000.0})
    {
        sim::BuildOptions full;
        full.sampleRate = fs;
        full.kind = sim::BuildOptions::Kind::Omni;
        full.tailLevelAx16 = true; // no diffuse solve: today's restore
        std::vector<double> tFull, tCached, tGen, tMake;
        const auto decay = sim::tail::eyringDecay(scene.room);
        const sim::ism::OctaveFilterbank fb(fs);
        const std::size_t len = sim::tail::unitDecayLength(sim::tail::tailLengthS(decay), fs);
        for (int i = 0; i < 5; ++i)
        {
            auto t0 = Clock::now();
            (void)sim::buildRoomIR(scene, full);
            tFull.push_back(ms(t0, Clock::now()));
            t0 = Clock::now();
            const sim::tail::BandNoiseGenerator gen(fb, len);
            tGen.push_back(ms(t0, Clock::now()));
            std::vector<sim::tail::UnitDecay> cache;
            t0 = Clock::now();
            for (std::uint32_t e = 0; e < 2; ++e)
                cache.push_back(gen.make(decay, sim::tail::tailSeedForOutput(scene.render.tailSeed, 0), e));
            tMake.push_back(ms(t0, Clock::now()));
            auto cached = full;
            cached.cachedUnitDecays = &cache;
            t0 = Clock::now();
            (void)sim::buildRoomIR(scene, cached);
            tCached.push_back(ms(t0, Clock::now()));
        }
        const auto med = [](std::vector<double> v) {
            std::sort(v.begin(), v.end());
            return v[v.size() / 2];
        };
        std::printf("probe-split fs %.0f: T60max %.1f s, unit decay %zu samples; full build (no diffuse) "
                    "median %.0f ms; "
                    "generator ctor %.0f ms; make x2 %.0f ms; position-only build (cached decays) %.0f ms\n",
                    fs, *std::max_element(decay.bandsT60S.begin(), decay.bandsT60S.end()), len, med(tFull),
                    med(tGen), med(tMake), med(tCached));
    }
}
