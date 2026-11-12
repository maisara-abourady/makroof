// Phase 07 scope 3: the plugin's scene -> IR -> engine pipeline (JUCE-free): RealtimeEngine::reset(),
// the reset sequence, the synchronous and offline paths, the switch rule and crossfade law (decider D7,
// tests (a)-(f), realtime and offline, -100 dB nulls against the analytic crossfade), no lost update
// (FR-3D-10), the latency peak, the output trim smoother, and a TSan stress test. Phase-07c-1 condition 10:
// reset() / setNonRealtime(true) never wait or build, the realtime reset keeps the IrSet, the two orders.
#include "PipelineTestUtil.h"

#include "AllocationTracker.h"
#include "contract/Validate.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/RealtimeEngine.h"

#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <cstdio>
#include <memory>

#include <array>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <mutex>
#include <random>
#include <thread>

// Exact comparisons are intended (bit-identical outputs, unity gains).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

using pipeline_test::Recorder;
using pipeline_test::Segment;
using Law = sim::conv::CrossfadeLaw;

constexpr double kRate = 48000.0;
constexpr int kP = plugin::ScenePipeline::kPartitionSize;

module3d::ParameterValues valuesOf(const contract::SceneDescription& s)
{
    return module3d::parameterValuesFromScene(s);
}

void restoreScene(plugin::ScenePipeline& p, const contract::SceneDescription& s)
{
    p.beginRestore();
    p.restore(s, valuesOf(s));
}

sim::RoomIR irOf(const module3d::ParameterValues& v, const contract::SceneDescription& base)
{
    return plugin::ScenePipeline::buildIr(module3d::deriveScene(v, base), kRate);
}

bool sameSpectra(const sim::conv::IrSet& a, const sim::conv::IrSet& b)
{
    if (a.numInputs() != b.numInputs() || a.numOutputs() != b.numOutputs()
        || a.numPartitions() != b.numPartitions() || a.length() != b.length())
        return false;
    for (int i = 0; i < a.numInputs(); ++i)
        for (int o = 0; o < a.numOutputs(); ++o)
            for (std::size_t k = 0; k < a.numPartitions(); ++k)
                if (std::memcmp(a.spectrum(i, o, k), b.spectrum(i, o, k),
                                static_cast<std::size_t>(2 * a.partitionSize()) * sizeof(float))
                    != 0)
                    return false;
    return true;
}

// Waits until the builder has handled every change.
void waitBuilt(const plugin::ScenePipeline& p)
{
    REQUIRE(pipeline_test::waitFor(
        [&] { return p.handledGeneration() == p.dirtyGeneration() && p.builderIdle(); }));
}

double residual(const Recorder& rec, const std::vector<Segment>& chain, int channel = 0)
{
    return pipeline_test::chainResidualDb(rec.in, rec.out[channel], chain, channel, kP,
                                          static_cast<int>(std::lround(0.030 * kRate)));
}

// The fade length L plus a margin, so that a fade has ended.
constexpr std::size_t kSettle = 1440 + 3 * kP;

} // namespace

TEST_CASE("RealtimeEngine::reset drops every IR and returns to the state after prepare()",
          "[pipeline][engine]")
{
    const auto scene = pipeline_test::loadScene("dead_booth.json");
    const auto ir = plugin::ScenePipeline::buildIr(scene, kRate);
    const auto x0 = conv_test::noise(4000, 11, 0.2);
    const auto x1 = conv_test::noise(4000, 12, 0.2);

    const auto run = [&](sim::RealtimeEngine& e) {
        std::vector<float> a = x0, b = x1;
        const float* const in[2] = {a.data(), b.data()};
        float* const out[2] = {a.data(), b.data()};
        e.process(in, out, 4000);
        return a;
    };

    sim::RealtimeEngine fresh;
    fresh.prepare(kRate, 4000);
    REQUIRE(fresh.submitRoomIR(ir));
    const auto expected = run(fresh);

    sim::RealtimeEngine engine;
    engine.reset(); // unprepared: a no-op
    engine.prepare(kRate, 4000);
    REQUIRE(engine.submitRoomIR(ir));
    run(engine);
    REQUIRE(engine.submitRoomIR(ir, Law::EqualPower)); // a fade pending in the mailbox
    run(engine);
    REQUIRE(engine.submitRoomIR(ir)); // a request left in the mailbox
    const auto fades = engine.convolver().fadeCount();
    engine.reset();
    REQUIRE(engine.convolver().currentIr() == nullptr);
    REQUIRE_FALSE(engine.convolver().isFading());
    REQUIRE(engine.convolver().fadeStartSample() == -1);
    REQUIRE(engine.convolver().fadeCount() == fades);
    // Silence until an IR arrives, then exactly a fresh engine's output.
    {
        std::vector<float> z(512, 1.0f), w(512, 1.0f);
        const float* const in[2] = {z.data(), w.data()};
        float* const out[2] = {z.data(), w.data()};
        sim::RealtimeEngine probe;
        probe.prepare(kRate, 4000);
        probe.process(in, out, 512);
        REQUIRE(z == std::vector<float>(512, 0.0f));
    }
    REQUIRE(engine.submitRoomIR(ir));
    REQUIRE(run(engine) == expected);
}

TEST_CASE("Pipeline: prepare builds synchronously; latency 544 at every supported rate", "[pipeline]")
{
    plugin::ScenePipeline p;
    REQUIRE(p.latencySamples() == 544);
    for (const double rate : {44100.0, 48000.0, 88200.0, 96000.0, 48000.0})
    {
        CAPTURE(rate);
        p.prepare(rate, 512, false);
        REQUIRE(p.latencySamples() == 544);
        REQUIRE_FALSE(p.unsupportedRateFallback());
        REQUIRE(p.handledGeneration() == p.dirtyGeneration()); // built before prepare() returned
        Recorder rec{p};
        rec.run(2 * kP);
        REQUIRE(p.engine().convolver().currentIr() != nullptr); // installed at once
        REQUIRE(p.engine().convolver().fadeCount() == 0);
    }
}

TEST_CASE("Pipeline: no lost update (FR-3D-10)", "[pipeline][lost-update]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    Recorder rec{p};
    rec.run(4 * kP);

    std::mt19937 rng(42);
    std::uniform_real_distribution<float> u(0.0f, 1.0f);
    std::thread fire([&] {
        for (int i = 0; i < 60; ++i)
        {
            p.setParameter(module3d::kListenerY, u(rng));
            p.setParameter(module3d::kEmRX, u(rng));
            std::this_thread::sleep_for(std::chrono::microseconds(700));
        }
    });
    while (!(fire.joinable() && p.dirtyGeneration() >= 120))
        rec.run(kP);
    fire.join();
    // Keep the audio running until the final state has been built and has become the current IR.
    REQUIRE(pipeline_test::waitFor([&] {
        rec.run(kP);
        return p.handledGeneration() == p.dirtyGeneration() && p.builderIdle();
    }));
    rec.run(4 * kSettle);
    REQUIRE(p.handledGeneration() == p.dirtyGeneration());
    const auto expected = p.engine().makeIrSet(irOf(p.parameterValues(), p.baseScene()));
    REQUIRE(expected != nullptr);
    const auto* current = p.engine().convolver().currentIr();
    REQUIRE(current != nullptr);
    REQUIRE(sameSpectra(*current, *expected));
}

TEST_CASE("Pipeline: a failed build records nothing and is built again (D7)", "[pipeline][lost-update]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    const auto before = p.handledGeneration();

    // Realtime: the builder fails three times on the same generation, then builds it.
    p.injectBuildFailures(3);
    p.setParameter(module3d::kListenerY, 0.6f);
    waitBuilt(p);
    REQUIRE(p.handledGeneration() != before);
    REQUIRE(pipeline_test::sameIr(*p.lastSubmittedIr(), irOf(p.parameterValues(), p.baseScene())));

    // A failure at generation g followed by a change to g + 1: g + 1 is built.
    p.injectBuildFailures(1);
    p.setParameter(module3d::kListenerY, 0.3f);
    p.setParameter(module3d::kListenerY, 0.35f);
    waitBuilt(p);
    REQUIRE(pipeline_test::sameIr(*p.lastSubmittedIr(), irOf(p.parameterValues(), p.baseScene())));

    // Offline: the failed block records nothing; the next block builds.
    p.setNonRealtime(true);
    Recorder rec{p};
    p.injectBuildFailures(1);
    p.setParameter(module3d::kListenerY, 0.5f);
    rec.run(256, 256);
    REQUIRE(p.handledGeneration() != p.dirtyGeneration());
    rec.run(256, 256);
    REQUIRE(p.handledGeneration() == p.dirtyGeneration());
}

TEST_CASE("Pipeline: the default scene is medium_room; the tail covers the longest IR", "[pipeline]")
{
    plugin::ScenePipeline p;
    const auto medium = pipeline_test::loadScene("medium_room.json");
    const auto s = p.currentScene();
    REQUIRE(contract::validate(s).ok());
    REQUIRE(s.room.geometry.dimensions == medium.room.geometry.dimensions);
    REQUIRE(s.room.surfaces == medium.room.surfaces);
    REQUIRE(s.render == medium.render);
    REQUIRE(s.emitters.size() == 2);
    const auto near = [](const contract::Vec3& a, const contract::Vec3& b) {
        return std::fabs(a.x - b.x) < 1e-5 && std::fabs(a.y - b.y) < 1e-5 && std::fabs(a.z - b.z) < 1e-5;
    };
    REQUIRE(near(s.listener.position, medium.listener.position));
    REQUIRE(near(s.emitters[0].position, medium.emitters[0].position));
    REQUIRE(near(s.emitters[1].position, medium.emitters[1].position));
    REQUIRE(s.emitters[0].gainDb == medium.emitters[0].gainDb);

    for (const double rate : {44100.0, 48000.0, 96000.0})
    {
        p.prepare(rate, 256, false);
        REQUIRE(p.tailLengthSeconds() * rate
                >= static_cast<double>(sim::RealtimeEngine::maxIrLengthSamples(rate)) - 1e-6);
        REQUIRE(p.tailLengthSeconds() >= 12.0);
    }
}

TEST_CASE("Pipeline: the latency peak lands at exactly latencySamples()", "[pipeline][latency]")
{
    // Emitters at the listener's minimum distance (pushed to 0.3 m), all alpha = 1.
    auto scene = pipeline_test::loadScene("medium_room.json");
    for (auto& s : scene.room.surfaces)
        s.bandsAbsorption.fill(1.0);
    auto v = valuesOf(scene);
    for (std::size_t a = 0; a < 3; ++a)
    {
        v[module3d::kEmLX + a] = v[module3d::kListenerX + a];
        v[module3d::kEmRX + a] = v[module3d::kListenerX + a];
    }
    for (const double rate : {44100.0, 48000.0, 96000.0})
    {
        CAPTURE(rate);
        plugin::ScenePipeline p;
        p.beginRestore();
        p.restore(scene, v);
        p.prepare(rate, 128, false);
        std::vector<float> a(4096, 0.0f), b(4096, 0.0f);
        a[0] = 1.0f;
        b[0] = 1.0f;
        for (int pos = 0; pos < 4096; pos += 128)
        {
            const float* const in[2] = {a.data() + pos, b.data() + pos};
            float* const out[2] = {a.data() + pos, b.data() + pos};
            p.process(in, out, 128);
        }
        std::size_t peak = 0;
        for (std::size_t i = 1; i < a.size(); ++i)
            if (std::fabs(a[i]) > std::fabs(a[peak]))
                peak = i;
        REQUIRE(peak == static_cast<std::size_t>(p.latencySamples()));
        REQUIRE(a == b); // mono preview: the same signal on both outputs
    }
}

TEST_CASE("Pipeline: the output trim follows a 20 ms linear ramp and snaps on reset", "[pipeline][trim]")
{
    plugin::ScenePipeline ref, p;
    restoreScene(ref, pipeline_test::loadScene("dead_booth.json"));
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    ref.prepare(kRate, 256, false);
    p.prepare(kRate, 256, false);
    Recorder r0{ref}, r1{p};
    r0.run(8 * kP);
    r1.run(8 * kP);
    REQUIRE(r0.out[0] == r1.out[0]);
    const std::size_t start = r1.samples();
    p.setParameter(module3d::kOutputTrimDb, -6.0f);
    r0.run(4 * kP);
    r1.run(4 * kP);
    const double target = std::pow(10.0, -6.0 / 20.0);
    const std::size_t ramp = 960; // 20 ms at 48 kHz
    for (std::size_t i = 0; i < 4 * kP; ++i)
    {
        const float a = r0.out[0][start + i];
        if (std::fabs(a) < 1e-3f)
            continue;
        const double g = r1.out[0][start + i] / a;
        const double expected = i + 1 >= ramp ? target
                                              : 1.0 + (target - 1.0) * static_cast<double>(i + 1) / ramp;
        INFO("sample " << i);
        REQUIRE(std::fabs(g - expected) < 1e-4);
    }
    REQUIRE(p.trimGain() == static_cast<float>(target));
    p.setParameter(module3d::kOutputTrimDb, 0.0f);
    p.reset(); // step 4: snapped to the target
    REQUIRE(p.trimGain() == 1.0f);
}

TEST_CASE("Switch rule (D7), realtime: (a) restore of the current state, (b) EqualGain, (c) EqualPower, "
          "(d) a change after the restore's snapshot, (f) after prepare / reset",
          "[pipeline][switch-rule]")
{
    const auto booth = pipeline_test::loadScene("dead_booth.json");
    plugin::ScenePipeline p;
    restoreScene(p, booth);
    p.prepare(kRate, 256, false);
    Recorder rec{p};
    rec.run(4 * kP);
    std::vector<Segment> chain{{irOf(p.parameterValues(), p.baseScene()), -1, Law::EqualGain}};
    const auto& conv = p.engine().convolver();

    // (a) Restoring the current state starts no fade, leaves the output unchanged, clears the flag.
    const auto fades0 = conv.fadeCount();
    restoreScene(p, p.currentScene());
    REQUIRE_FALSE(p.restorePending());
    REQUIRE(p.handledGeneration() == p.dirtyGeneration());
    rec.run(kSettle);
    REQUIRE(conv.fadeCount() == fades0);
    REQUIRE(residual(rec, chain) <= -100.0);

    // (b) The next listener_y change crosses as an EqualGain fade.
    p.setParameter(module3d::kListenerY, 0.6f);
    waitBuilt(p);
    rec.run(kSettle);
    REQUIRE(conv.fadeCount() == fades0 + 1);
    chain.push_back({irOf(p.parameterValues(), p.baseScene()), conv.fadeStartSample(), Law::EqualGain});
    REQUIRE(pipeline_test::sameIr(*p.lastSubmittedIr(),
                                  chain.back().ir)); // AX5: the reference IR is the submitted one
    REQUIRE(residual(rec, chain) <= -100.0);
    {
        auto wrong = chain;
        wrong.back().law = Law::EqualPower;
        REQUIRE(residual(rec, wrong) > -60.0); // the null tells the laws apart
    }

    // (c) Restoring a different state crosses as an EqualPower fade; the next change is EqualGain.
    auto other = p.currentScene();
    other.render.tailSeed += 1;
    other.room.surface(contract::SurfaceId::floor).bandsAbsorption.fill(0.3);
    restoreScene(p, other);
    REQUIRE_FALSE(p.restorePending());
    rec.run(kSettle);
    REQUIRE(conv.fadeCount() == fades0 + 2);
    chain.push_back({irOf(p.parameterValues(), p.baseScene()), conv.fadeStartSample(), Law::EqualPower});
    REQUIRE(residual(rec, chain) <= -100.0);
    p.setParameter(module3d::kListenerY, 0.4f);
    waitBuilt(p);
    rec.run(kSettle);
    chain.push_back({irOf(p.parameterValues(), p.baseScene()), conv.fadeStartSample(), Law::EqualGain});
    REQUIRE(conv.fadeCount() == fades0 + 3);
    REQUIRE(residual(rec, chain) <= -100.0);

    // (d) A change injected after the restore's scene snapshot is a later generation, built by the
    // builder after the restore, with EqualGain.
    auto third = p.currentScene();
    third.render.tailSeed += 7;
    std::atomic<bool> injected{false};
    p.setAfterSnapshotHook([&] {
        if (!injected.exchange(true))
            p.setParameter(module3d::kListenerY, 0.5f);
    });
    p.beginRestore();
    p.restore(third, valuesOf(third));
    p.setAfterSnapshotHook({});
    REQUIRE(injected.load());
    const auto restoredValues = valuesOf(third);
    rec.run(kSettle); // the restore's EqualPower fade (taken before the builder's later request)
    chain.push_back({irOf(restoredValues, third), conv.fadeStartSample(), Law::EqualPower});
    waitBuilt(p);
    rec.run(kSettle);
    chain.push_back({irOf(p.parameterValues(), p.baseScene()), conv.fadeStartSample(), Law::EqualGain});
    REQUIRE(conv.fadeCount() == fades0 + 5);
    REQUIRE(residual(rec, chain) <= -100.0);

    // (f) setStateInformation -> prepareToPlay or reset -> a listener_y change crosses as EqualGain.
    // Phase-07c-1 condition 10: a realtime reset keeps the current IrSet (never silent), so the restore's
    // request, still in the mailbox when reset() arrives, crosses as an ordinary EqualPower fade from the
    // previous IR instead of being installed at once (prepare() still drops and installs at once).
    for (const bool viaPrepare : {true, false})
    {
        CAPTURE(viaPrepare);
        const auto before = irOf(p.parameterValues(), p.baseScene());
        auto fourth = p.currentScene();
        fourth.render.tailSeed += 3;
        restoreScene(p, fourth);
        const auto fadesBefore = p.engine().convolver().fadeCount();
        if (viaPrepare)
            p.prepare(kRate, 256, false);
        else
            p.reset();
        REQUIRE_FALSE(p.restorePending());
        rec.clear();
        rec.run(4 * kP);
        std::vector<Segment> c;
        if (viaPrepare)
            c.push_back({irOf(p.parameterValues(), p.baseScene()), -1, Law::EqualGain});
        else
        {
            REQUIRE(p.engine().convolver().fadeCount() == fadesBefore + 1); // kept IR, then one fade
            c.push_back({before, -1, Law::EqualGain});
            c.push_back({irOf(p.parameterValues(), p.baseScene()), p.engine().convolver().fadeStartSample(),
                         Law::EqualPower});
        }
        p.setParameter(module3d::kListenerY, viaPrepare ? 0.3f : 0.7f);
        waitBuilt(p);
        rec.run(kSettle);
        c.push_back({irOf(p.parameterValues(), p.baseScene()), p.engine().convolver().fadeStartSample(),
                     Law::EqualGain});
        REQUIRE(residual(rec, c) <= -100.0);
    }
}

namespace {

// An offline bounce script: state0 at the start; at block 10 a restore of state1 together with a
// listener_y change (one EqualPower fade, D7 (d) offline); at block 30 another listener_y change
// (EqualGain).
struct Bounce
{
    Recorder rec;
    std::vector<Segment> chain;
};

void runScript(plugin::ScenePipeline& p, Bounce& b, const contract::SceneDescription& state1)
{
    constexpr int kBlock = 256;
    b.rec.seed = 100; // the same input in every bounce
    for (int block = 0; block < 50; ++block)
    {
        if (block == 10)
        {
            restoreScene(p, state1);
            p.setParameter(module3d::kListenerY, 0.55f);
        }
        if (block == 30)
            p.setParameter(module3d::kListenerY, 0.35f);
        const auto fades = p.engine().convolver().fadeCount();
        b.rec.run(kBlock, kBlock);
        if (block == 0)
            b.chain.push_back({irOf(p.parameterValues(), p.baseScene()), -1, Law::EqualGain});
        if (p.engine().convolver().fadeCount() != fades)
            b.chain.push_back({irOf(p.parameterValues(), p.baseScene()),
                               p.engine().convolver().fadeStartSample(),
                               b.chain.size() == 1 ? Law::EqualPower : Law::EqualGain});
    }
    b.rec.run(kSettle, kBlock);
}

} // namespace

TEST_CASE("Switch rule (D7), offline: (d) restore + change in one block = one EqualPower fade, then "
          "EqualGain; (e) bit-identical bounces; (f) after reset; processBlock is the only submitter",
          "[pipeline][switch-rule][offline]")
{
    const auto state0 = pipeline_test::loadScene("dead_booth.json");
    auto state1 = state0;
    state1.render.tailSeed += 5;
    state1.room.surface(contract::SurfaceId::ceiling).bandsAbsorption.fill(0.2);

    // Instance A, first bounce.
    plugin::ScenePipeline a;
    restoreScene(a, state0);
    a.prepare(kRate, 256, true);
    REQUIRE(a.engine().convolver().fadeCount() == 0);
    REQUIRE_FALSE(a.handledGeneration().has_value()); // offline prepare leaves the build to process()
    Bounce b1{Recorder{a}, {}};
    runScript(a, b1, state1);
    REQUIRE(b1.chain.size() == 3); // installed at once, one EqualPower fade, one EqualGain fade
    REQUIRE(residual(b1.rec, b1.chain) <= -100.0);

    // Offline, setStateInformation and prepareToPlay do not submit: the next process() does.
    {
        const auto fades = a.engine().convolver().fadeCount();
        const auto handled = a.handledGeneration();
        auto s = state0;
        s.render.tailSeed += 11;
        restoreScene(a, s);
        REQUIRE(a.engine().convolver().fadeCount() == fades);
        REQUIRE(a.handledGeneration() == handled);
        REQUIRE(a.restorePending());
    }

    // Second bounce on A after a reset (state0 restored first).
    restoreScene(a, state0);
    a.reset(); // (f) condition 10: an offline reset only drops; the next process() makes the decision
    REQUIRE(a.restorePending());
    REQUIRE_FALSE(a.handledGeneration().has_value());
    Bounce b2{Recorder{a}, {}};
    runScript(a, b2, state1);
    REQUIRE(b2.rec.out[0] == b1.rec.out[0]);
    REQUIRE(b2.rec.out[1] == b1.rec.out[1]);

    // A fresh instance that restores before prepare bounces bit-identically.
    plugin::ScenePipeline fresh;
    restoreScene(fresh, state0);
    fresh.prepare(kRate, 256, true);
    Bounce b3{Recorder{fresh}, {}};
    runScript(fresh, b3, state1);
    REQUIRE(b3.rec.out[0] == b1.rec.out[0]);
    REQUIRE(b3.rec.out[1] == b1.rec.out[1]);
}

TEST_CASE("Pipeline: leaving non-realtime mode restarts the builder", "[pipeline][offline]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    p.setNonRealtime(true);
    // Condition 10: entering cancels and drops (no wait, no build); the next process() builds.
    REQUIRE_FALSE(p.handledGeneration().has_value());
    p.setParameter(module3d::kListenerY, 0.6f);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    REQUIRE(p.handledGeneration() != p.dirtyGeneration()); // quiesced: nothing built without process()
    p.setNonRealtime(false);
    waitBuilt(p); // the builder took over, no process() call
}

TEST_CASE("Pipeline: no allocation or free on the audio thread while 50 changes per second arrive",
          "[pipeline][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("allocation tracking is off in this build (ASan)");
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    std::atomic<bool> done{false};
    std::thread fire([&] {
        float y = 0.2f;
        while (!done.load())
        {
            p.setParameter(module3d::kListenerY, y);
            y = y > 0.7f ? 0.2f : y + 0.05f;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
    std::vector<float> a(256, 0.1f), b(256, -0.1f);
    const float* const in[2] = {a.data(), b.data()};
    float* const out[2] = {a.data(), b.data()};
    std::size_t allocs = 0, frees = 0;
    const auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(1500);
    const auto limit = std::chrono::steady_clock::now() + std::chrono::seconds(60);
    const auto fades0 = p.engine().convolver().fadeCount();
    // At least 1.5 s, and until an IR change has crossed (slow debug builds, e.g. MSVC), at most 60 s.
    while (std::chrono::steady_clock::now() < end
           || (p.engine().convolver().fadeCount() == fades0 && std::chrono::steady_clock::now() < limit))
    {
        {
            test_support::ScopedTracking tracking;
            p.process(in, out, 256);
            allocs += tracking.allocations();
            frees += tracking.deallocations();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
    done.store(true);
    fire.join();
    REQUIRE(p.engine().convolver().fadeCount() > fades0); // IRs did change while we listened
    REQUIRE(allocs == 0);
    REQUIRE(frees == 0);
}

TEST_CASE("Pipeline: parameter thread, builder and audio thread together (TSan)", "[pipeline][tsan]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    std::atomic<bool> stopParams{false};
    std::thread params([&] {
        std::mt19937 rng(9);
        std::uniform_real_distribution<float> u(0.0f, 1.0f);
        while (!stopParams.load())
        {
            p.setParameter(static_cast<std::size_t>(rng() % 9), u(rng));
            p.setParameter(module3d::kOutputTrimDb, -12.0f * u(rng));
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    });
    const auto audio = [&](std::chrono::milliseconds ms) {
        std::atomic<bool> stop{false};
        std::thread t([&] {
            std::vector<float> a(256, 0.1f), b(256, -0.1f);
            const float* const in[2] = {a.data(), b.data()};
            float* const out[2] = {a.data(), b.data()};
            while (!stop.load())
                p.process(in, out, 256);
        });
        std::this_thread::sleep_for(ms);
        stop.store(true);
        t.join();
    };
    for (int round = 0; round < 3; ++round)
    {
        // A state restore while the audio thread runs (allowed by hosts).
        std::thread restorer([&] {
            auto s = p.currentScene();
            s.render.tailSeed += static_cast<std::uint32_t>(round + 1);
            restoreScene(p, s);
        });
        audio(std::chrono::milliseconds(300));
        restorer.join();
        // Host transport events with the audio stopped: reset and prepare (the builder is quiesced first).
        p.reset();
        audio(std::chrono::milliseconds(100));
        p.prepare(round % 2 == 0 ? 44100.0 : kRate, 256, false);
    }
    stopParams.store(true);
    params.join();
    REQUIRE(contract::validate(p.currentScene()).ok());
}

#if defined(__linux__)
#include <fstream>
#include <unistd.h>
#endif

namespace {

// Resident set size of this process in bytes (Linux: /proc/self/statm); 0 where unavailable.
std::size_t residentBytes()
{
#if defined(__linux__)
    std::ifstream statm("/proc/self/statm");
    std::size_t pages = 0, resident = 0;
    statm >> pages >> resident;
    return resident * static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
#else
    return 0;
#endif
}

} // namespace

// Phase 07 Definition of done (recorded, not gated): the full-rebuild time (scene -> buildRoomIR ->
// IrSet) at the default and the maximum room, and the peak memory per instance at 96 kHz with the
// maximum room. Hidden: CI runs it from the Release build with `spatial_tests "[benchmark]"`.
TEST_CASE("benchmark: Phase 07 full rebuild (default and maximum room) and memory per instance",
          "[.][benchmark][pipeline-measure]")
{
    const auto timeBuild = [](const module3d::ParameterValues& v, double rate) {
        sim::RealtimeEngine engine;
        engine.prepare(rate, 512);
        const auto scene = module3d::deriveScene(v, plugin::defaultScene());
        double best = 1e9;
        for (int i = 0; i < 3; ++i)
        {
            const auto t0 = std::chrono::steady_clock::now();
            const auto ir = plugin::ScenePipeline::buildIr(scene, rate);
            const auto set = engine.makeIrSet(ir);
            const auto t1 = std::chrono::steady_clock::now();
            REQUIRE(set != nullptr);
            best = std::min(best, std::chrono::duration<double, std::milli>(t1 - t0).count());
        }
        return best;
    };
    auto maxRoom = module3d::defaultParameterValues();
    maxRoom[module3d::kRoomW] = maxRoom[module3d::kRoomD] = maxRoom[module3d::kRoomH] = 100.0;
    for (const double rate : {48000.0, 96000.0})
    {
        std::printf(
            "phase-07 full rebuild at %.0f Hz (best of 3): default room %.1f ms, maximum room %.1f ms\n",
            rate, timeBuild(module3d::defaultParameterValues(), rate), timeBuild(maxRoom, rate));
    }

    const std::size_t before = residentBytes();
    {
        auto p = std::make_unique<plugin::ScenePipeline>();
        p->beginRestore();
        p->restore(plugin::defaultScene(), maxRoom);
        p->prepare(96000.0, 512, false);
        std::vector<float> a(512, 0.1f), b(512, 0.1f);
        const float* const in[2] = {a.data(), b.data()};
        float* const out[2] = {a.data(), b.data()};
        for (int i = 0; i < 200; ++i)
            p->process(in, out, 512);
        const std::size_t after = residentBytes();
        if (before > 0)
            std::printf("phase-07 memory per instance at 96 kHz, maximum room: RSS +%.1f MB\n",
                        static_cast<double>(after - before) / (1024.0 * 1024.0));
        else
            std::printf("phase-07 memory per instance: RSS not measured on this OS\n");
    }
}

// ---- Phase-07c-1 condition 10 (D-H3 (e): Seat 3's (e-k) + Seat 2's (e-e)) ----

namespace {

// Holds the builder inside a decision (after its scene snapshot) until released, and records whether any
// decision ran on the host thread under test.
struct BlockedBuilder
{
    std::mutex m;
    std::condition_variable cv;
    bool released = false;
    std::atomic<int> builderDecisions{0};
    std::atomic<int> hostDecisions{0};
    std::thread::id host;

    void install(plugin::ScenePipeline& p)
    {
        p.setAfterSnapshotHook([this] {
            if (std::this_thread::get_id() == host)
            {
                ++hostDecisions; // a decision (a build or a skip) on the host thread: condition 10 forbids it
                return;
            }
            ++builderDecisions;
            std::unique_lock<std::mutex> lock(m);
            cv.wait(lock, [this] { return released; });
        });
    }
    void release()
    {
        {
            std::lock_guard<std::mutex> lock(m);
            released = true;
        }
        cv.notify_all();
    }
};

enum class HostCall
{
    RealtimeReset,
    EnterOffline,
    ResetThenEnterOffline,
    EnterOfflineThenReset
};

// Runs `call` on a host thread while the builder is blocked mid-decision. Returns the call's duration in
// seconds, or a negative value if it had not returned 2 s after the builder was blocked (it waited on the
// builder; the builder is released then, so the test fails instead of hanging).
double timedHostCall(plugin::ScenePipeline& p, BlockedBuilder& bb, HostCall call)
{
    std::atomic<bool> done{false};
    double seconds = -1.0;
    std::thread host([&] {
        const auto t0 = std::chrono::steady_clock::now();
        switch (call)
        {
        case HostCall::RealtimeReset:
            p.reset();
            break;
        case HostCall::EnterOffline:
            p.setNonRealtime(true);
            break;
        case HostCall::ResetThenEnterOffline:
            p.reset();
            p.setNonRealtime(true);
            break;
        case HostCall::EnterOfflineThenReset:
            p.setNonRealtime(true);
            p.reset();
            break;
        }
        seconds = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        done.store(true);
    });
    bb.host = host.get_id(); // read by the hook only for decisions that start after this point
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(2);
    while (!done.load() && std::chrono::steady_clock::now() < deadline)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    const bool returned = done.load();
    bb.release();
    host.join();
    return returned ? seconds : -1.0;
}

std::vector<float> offlineBounce(plugin::ScenePipeline& p, int blocks)
{
    Recorder rec{p};
    rec.seed = 77;
    rec.run(static_cast<std::size_t>(blocks) * 256, 256);
    return rec.out[0];
}

} // namespace

TEST_CASE("Condition 10: reset() and setNonRealtime(true) never wait on the builder and never build; the two "
          "orders bounce bit-identically",
          "[pipeline][offline][reset-nowait]")
{
    const auto booth = pipeline_test::loadScene("dead_booth.json");
    // Reference: a fresh offline instance bounces the changed scene.
    std::vector<float> reference;
    {
        plugin::ScenePipeline fresh;
        restoreScene(fresh, booth);
        fresh.setParameter(module3d::kListenerY, 0.6f);
        fresh.prepare(kRate, 256, true);
        reference = offlineBounce(fresh, 40);
    }

    for (const HostCall call : {HostCall::RealtimeReset, HostCall::EnterOffline,
                                HostCall::ResetThenEnterOffline, HostCall::EnterOfflineThenReset})
    {
        CAPTURE(static_cast<int>(call));
        plugin::ScenePipeline p;
        restoreScene(p, booth);
        p.prepare(kRate, 256, false);
        {
            Recorder warm{p};
            warm.run(4 * kP);
        }
        BlockedBuilder bb;
        bb.host = std::thread::id{}; // no host thread yet
        bb.install(p);
        p.setParameter(module3d::kListenerY, 0.6f); // the builder starts a decision and blocks in the hook
        REQUIRE(pipeline_test::waitFor([&] { return bb.builderDecisions.load() >= 1; }));

        const double seconds = timedHostCall(p, bb, call);
        INFO("host call took " << seconds << " s while the builder was blocked mid-decision");
        REQUIRE(seconds >= 0.0); // returned while the builder was still blocked: it never waited on it
        REQUIRE(seconds < 0.5);  // and did no build of its own (a dead_booth build alone is longer on CI)
        REQUIRE(bb.hostDecisions.load() == 0); // never decided (built or skipped) on the host thread
        p.setAfterSnapshotHook({});

        if (call == HostCall::RealtimeReset)
        {
            // The in-flight decision is of the current generation and is not cancelled: it lands as an
            // ordinary AQ4 update.
            waitBuilt(p);
            continue;
        }
        // Offline: nothing was built; the next process() waits for the cancelled decision and builds.
        REQUIRE_FALSE(p.handledGeneration().has_value());
        const auto bounce = offlineBounce(p, 40);
        REQUIRE(p.handledGeneration() == p.dirtyGeneration());
        REQUIRE(bounce == reference); // both orders, bit-identical to a fresh offline bounce (AX5)
    }
}

TEST_CASE("Condition 10: a realtime reset keeps the current IrSet; the output is never silent",
          "[pipeline][reset-nowait]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    p.prepare(kRate, 256, false);
    Recorder rec{p};
    rec.run(4 * kP + kSettle);
    const auto& conv = p.engine().convolver();
    const auto fades = conv.fadeCount();
    const auto* before = conv.currentIr();
    REQUIRE(before != nullptr);

    p.reset();
    REQUIRE(conv.currentIr() == before);        // kept, not dropped
    REQUIRE(p.lastSubmittedIrSet() != nullptr); // the D7 record still describes what plays
    rec.clear();
    rec.run(4 * kP);
    REQUIRE(conv.fadeCount() == fades); // nothing to switch: the same IR plays on
    // Output after the reported latency is the convolution with the kept IR from sample 0 of the cleared
    // history (the -100 dB null), so it is not silence.
    const std::vector<Segment> chain{{irOf(p.parameterValues(), p.baseScene()), -1, Law::EqualGain}};
    REQUIRE(residual(rec, chain) <= -100.0);
    double energy = 0.0;
    for (std::size_t i = static_cast<std::size_t>(p.latencySamples()); i < rec.out[0].size(); ++i)
        energy += static_cast<double>(rec.out[0][i]) * rec.out[0][i];
    REQUIRE(energy > 0.0);

    // A fade running at the reset ends on its target, which keeps playing.
    p.setParameter(module3d::kListenerY, 0.6f);
    waitBuilt(p);
    rec.run(kP + 64); // the request is taken at the next boundary: the fade starts
    REQUIRE(conv.isFading());
    p.reset();
    REQUIRE_FALSE(conv.isFading());
    REQUIRE(conv.currentIr() == p.lastSubmittedIrSet().get());
}

// ---- Phase-07c-1 condition 12 (D-G1): the AX38 gate around the diffuse solve only ----

TEST_CASE("Condition 12 (a): the gate is held during the solve only, not during planning or the synthesis",
          "[pipeline][gate-scope]")
{
    plugin::ScenePipeline p;
    restoreScene(p, pipeline_test::loadScene("dead_booth.json"));
    using Stage = plugin::ScenePipeline::BuildStage;
    std::mutex m;
    std::vector<std::pair<Stage, bool>> seen; // (stage, gate held at its start)
    bool otherEnteredDuringAssembly = false;
    p.setStageHook([&](Stage stage) {
        const bool held = p.gate().held();
        bool entered = false;
        if (stage == Stage::Assemble)
        {
            // Another solve can take the gate while this build synthesises (it is not held here).
            plugin::DiffuseSolveGate::Scope other(p.gate(), plugin::DiffuseSolveGate::Class::Synchronous);
            entered = other.entered();
        }
        std::lock_guard<std::mutex> lock(m);
        seen.emplace_back(stage, held);
        if (stage == Stage::Assemble)
            otherEnteredDuringAssembly = entered;
    });
    p.prepare(kRate, 256, false); // a synchronous build (Synchronous class)
    p.setParameter(module3d::kListenerY, 0.6f);
    waitBuilt(p); // a builder build (Builder class)
    p.setStageHook({});
    std::lock_guard<std::mutex> lock(m);
    REQUIRE(seen.size() == 6);
    for (std::size_t i = 0; i < seen.size(); ++i)
    {
        CAPTURE(i);
        const auto [stage, held] = seen[i];
        REQUIRE(stage == static_cast<Stage>(i % 3)); // Plan, Solve, Assemble, in that order
        REQUIRE(held == (stage == Stage::Solve));
    }
    REQUIRE(otherEnteredDuringAssembly);
    REQUIRE_FALSE(p.gate().held());
}

TEST_CASE(
    "Condition 12: buildRoomIR is bit-identical to its stages, also with the stages on different threads",
    "[pipeline][staged]")
{
    for (const char* file : {"dead_booth.json", "medium_room.json", "club.json"})
    {
        CAPTURE(file);
        const auto scene = pipeline_test::loadScene(file);
        sim::BuildOptions options;
        options.sampleRate = kRate;
        options.kind = sim::BuildOptions::Kind::Omni;
        const sim::RoomIR whole = sim::buildRoomIR(scene, options);
        auto build = sim::StagedBuild::plan(scene, options);
        REQUIRE(build.needsSolve());
        std::thread([&] { build.solve(); }).join(); // the solve on another thread, as the gate's holder
        REQUIRE_FALSE(build.needsSolve());
        sim::RoomIR staged;
        std::thread([&] { staged = build.assemble(); }).join();
        REQUIRE(pipeline_test::sameIr(staged, whole));
    }
    // Kinds without a solve: plan() builds the IR; solve() is a no-op.
    const auto scene = pipeline_test::loadScene("medium_room.json");
    sim::BuildOptions early;
    early.sampleRate = kRate;
    early.kind = sim::BuildOptions::Kind::OmniEarly;
    auto build = sim::StagedBuild::plan(scene, early);
    REQUIRE_FALSE(build.needsSolve());
    build.solve();
    REQUIRE(pipeline_test::sameIr(build.assemble(), sim::buildRoomIR(scene, early)));
}

TEST_CASE("Condition 12 (e): two pipelines plan and synthesise while a third solves (TSan)",
          "[pipeline][gate-scope]")
{
    const auto club = pipeline_test::loadScene("club.json");
    std::array<std::unique_ptr<plugin::ScenePipeline>, 3> pipes;
    for (auto& p : pipes)
    {
        p = std::make_unique<plugin::ScenePipeline>();
        restoreScene(*p, club);
        p->prepare(kRate, 256, false);
    }
    std::atomic<int> concurrentBuilders{0}, maxConcurrent{0};
    for (auto& p : pipes)
        p->setStageHook([&](plugin::ScenePipeline::BuildStage stage) {
            if (stage == plugin::ScenePipeline::BuildStage::Plan)
            {
                const int now = ++concurrentBuilders;
                int m = maxConcurrent.load();
                while (now > m && !maxConcurrent.compare_exchange_weak(m, now))
                {}
                std::this_thread::sleep_for(std::chrono::milliseconds(20)); // widen the overlap
            }
            else if (stage == plugin::ScenePipeline::BuildStage::Assemble)
                --concurrentBuilders;
        });
    for (int round = 0; round < 3; ++round)
    {
        for (std::size_t i = 0; i < pipes.size(); ++i)
            pipes[i]->setParameter(module3d::kListenerY,
                                   0.3f + 0.1f * static_cast<float>(static_cast<std::size_t>(round) + i));
        for (auto& p : pipes)
            waitBuilt(*p);
    }
    for (auto& p : pipes)
        p->setStageHook({});
    // Builds overlapped outside the gate (with the gate around the whole build they never could).
    REQUIRE(maxConcurrent.load() >= 2);
    REQUIRE_FALSE(pipes[0]->gate().held());
}
