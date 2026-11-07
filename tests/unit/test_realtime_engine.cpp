// Phase 06: sim::RealtimeEngine (the façade Phase 07 calls): reported latency (P + AX1 pre-roll),
// the null against the offline render of a Phase 04 room IR, argument checks, zero allocations, and
// the AQ10 CPU benchmark (hidden, run from the Release build in CI).
#include "AllocationTracker.h"
#include "ContractFixtures.h"
#include "ConvTestUtil.h"
#include "contract/Parse.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"
#include "sim/RealtimeEngine.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

contract::SceneDescription loadScene(const std::string& name)
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / name));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

sim::RoomIR emptyIr(double fs, std::size_t length)
{
    sim::RoomIR ir;
    ir.sampleRate = fs;
    ir.numEmitters = 2;
    ir.numOutputs = 2;
    ir.taps.assign(4, std::vector<float>(length, 0.0f));
    return ir;
}

// Renders a stereo input through the engine in the given block schedule (0 = random sizes) and
// returns `total` output frames per channel.
std::vector<std::vector<float>> runEngine(sim::RealtimeEngine& engine, const sim::MultiChannel& x,
                                          std::size_t total, int block, int maxBlock)
{
    std::vector<std::vector<float>> in(2, std::vector<float>(total, 0.0f)),
        out(2, std::vector<float>(total, 0.0f));
    for (std::size_t c = 0; c < 2; ++c)
        std::copy(x[c].begin(), x[c].end(), in[c].begin());
    std::size_t pos = 0;
    for (const int n : conv_test::blockSchedule(total, block, 17u, maxBlock))
    {
        const float* ins[2] = {in[0].data() + pos, in[1].data() + pos};
        float* outs[2] = {out[0].data() + pos, out[1].data() + pos};
        engine.process(ins, outs, n);
        pos += static_cast<std::size_t>(n);
    }
    return out;
}

} // namespace

// Acceptance: latencySamples() equals the measured offset of an impulse through a delta IR (exactly
// P + pre-roll). The delta sits where buildRoomIR puts the earliest direct arrival (AX1).
TEST_CASE("RealtimeEngine latency = P + pre-roll, measured on an impulse", "[conv][engine]")
{
    const int p = GENERATE(128, 256, 512);
    const double fs = GENERATE(44100.0, 48000.0, 96000.0);
    sim::RealtimeEngine engine(p);
    engine.prepare(fs, 256);
    CHECK(engine.latencySamples() == p + sim::kAlignPreRollSamples);
    CHECK(engine.crossfadeSamples() == static_cast<int>(std::lround(0.030 * fs)));
    auto ir = emptyIr(fs, 100);
    ir.taps[ir.index(0, 0)][sim::kAlignPreRollSamples] = 1.0f;
    ir.taps[ir.index(1, 1)][sim::kAlignPreRollSamples] = 1.0f;
    REQUIRE(engine.submitRoomIR(ir));
    sim::MultiChannel x(2, std::vector<float>(1, 0.0f));
    x[0][0] = 1.0f;
    x[1][0] = 1.0f;
    const auto out = runEngine(engine, x, 3000, 0, 256);
    for (const auto& ch : out)
    {
        const auto first = std::find_if(ch.begin(), ch.end(), [](float v) { return std::abs(v) > 1e-3f; });
        REQUIRE(first != ch.end());
        CHECK(first - ch.begin() == engine.latencySamples());
        CHECK(std::abs(*first - 1.0f) < 1e-5f);
    }
}

TEST_CASE("RealtimeEngine latency on a real scene: the direct sound peaks at latencySamples()",
          "[conv][engine]")
{
    const auto scene = loadScene("open_field.json");
    sim::BuildOptions options;
    options.sampleRate = 48000.0;
    options.kind = sim::BuildOptions::Kind::Omni;
    const auto ir = sim::buildRoomIR(scene, options);
    sim::RealtimeEngine engine;
    engine.prepare(48000.0, 512);
    REQUIRE(engine.submitRoomIR(ir));
    sim::MultiChannel x(2, std::vector<float>(1, 0.0f));
    x[0][0] = 1.0f; // emitter L only
    const auto out = runEngine(engine, x, ir.length() + 2000, 512, 512);
    const auto& ch = out[0];
    const auto peak = std::max_element(ch.begin(), ch.end(),
                                       [](float a, float b) { return std::abs(a) < std::abs(b); });
    CHECK(peak - ch.begin() == engine.latencySamples());
}

// The C++ side of the render_cli --realtime-emulation null (the Python test runs the binary): a
// Phase 04 hybrid room IR through the engine in random blocks equals renderOffline within -120 dB.
TEST_CASE("RealtimeEngine nulls against renderOffline of a Phase 04 room IR (-120 dB)", "[conv][engine]")
{
    const int block = GENERATE(0, 64, 2048);
    const auto scene = loadScene("medium_room.json");
    sim::BuildOptions options;
    options.sampleRate = 48000.0;
    options.kind = sim::BuildOptions::Kind::Omni;
    const auto ir = sim::buildRoomIR(scene, options);
    const sim::MultiChannel x = {conv_test::noise(48000, 61u), conv_test::noise(48000, 62u)};
    const auto ref = sim::renderOffline(ir, x);
    sim::RealtimeEngine engine;
    engine.prepare(48000.0, 2048);
    REQUIRE(engine.submitRoomIR(ir));
    const int p = engine.partitionSize();
    const auto out = runEngine(engine, x, ref[0].size() + static_cast<std::size_t>(p), block, 2048);
    for (std::size_t m = 0; m < 2; ++m)
    {
        const std::vector<double> r(ref[m].begin(), ref[m].end());
        const double db = conv_test::residualDb(out[m], r, static_cast<std::size_t>(p));
        INFO("block " << block << ", output " << m << ": " << db << " dB");
        CHECK(db <= -120.0);
    }
}

TEST_CASE("RealtimeEngine refuses IRs that don't fit", "[conv][engine]")
{
    CHECK_THROWS_AS(sim::RealtimeEngine(1024), std::invalid_argument);
    sim::RealtimeEngine engine(256);
    CHECK_THROWS_AS(engine.prepare(32000.0, 512), std::invalid_argument);
    CHECK_THROWS_AS(engine.prepare(48000.0, 0), std::invalid_argument);
    engine.prepare(48000.0, 512);
    CHECK(sim::RealtimeEngine::maxIrLengthSamples(48000.0)
          == static_cast<std::size_t>(std::ceil(sim::tail::kMaxIrLengthS * 48000.0))
                 + sim::kAlignPreRollSamples);
    CHECK_FALSE(engine.submitRoomIR(emptyIr(44100.0, 10))); // rate
    CHECK_FALSE(engine.submitRoomIR(
        emptyIr(48000.0, sim::RealtimeEngine::maxIrLengthSamples(48000.0) + 1))); // length
    auto mono = emptyIr(48000.0, 10);
    mono.numEmitters = 1;
    mono.numOutputs = 1;
    mono.taps.resize(1);
    CHECK_FALSE(engine.submitRoomIR(mono)); // shape
    CHECK(engine.submitRoomIR(emptyIr(48000.0, sim::RealtimeEngine::maxIrLengthSamples(48000.0))));
}

TEST_CASE("RealtimeEngine::process allocates nothing, including IR swaps", "[conv][engine][alloc]")
{
    sim::RealtimeEngine engine(256);
    engine.prepare(48000.0, 1024);
    auto a = emptyIr(48000.0, 4000), b = emptyIr(48000.0, 6000);
    for (auto& t : a.taps)
        t = conv_test::noise(4000, 3u);
    for (auto& t : b.taps)
        t = conv_test::noise(6000, 4u);
    std::vector<float> l(1024, 0.1f), r(1024, 0.2f);
    const float* ins[2] = {l.data(), r.data()};
    float* outs[2] = {l.data(), r.data()}; // in place
    std::size_t allocations = 0, frees = 0;
    for (int i = 0; i < 6; ++i)
    {
        REQUIRE(engine.submitRoomIR(i % 2 ? a : b, i % 3 ? sim::conv::CrossfadeLaw::EqualGain
                                                         : sim::conv::CrossfadeLaw::EqualPower));
        for (const int n : {1, 37, 64, 512, 1024})
        {
            test_support::ScopedTracking tracking;
            engine.process(ins, outs, n);
            allocations += tracking.allocations();
            frees += tracking.deallocations();
        }
    }
    CHECK(allocations == 0);
    CHECK(frees == 0);
    CHECK(engine.convolver().fadeCount() > 0);
}

// Phase-06 benchmark (recorded; not a pass/fail on time, runner noise). Hidden: CI runs it from the
// Release build with `spatial_tests "[benchmark]"`. 2 x 2, IR 1 / 3 / 6 / 12 s, P = 256 / 512,
// 48 kHz, host buffer 512: the mean (and median, max) time per host buffer as % of its real-time
// budget (512 / 48 000 s = 10.67 ms), steady and while crossfading continuously. AQ10: <= 15 % for
// the 3 s IR at P = 512.
TEST_CASE("benchmark: real-time convolution 2 x 2, 48 kHz, host buffer 512", "[.][benchmark]")
{
    constexpr double fs = 48000.0;
    constexpr int host = 512;
    constexpr int blocks = 1500;
    const double budgetUs = host / fs * 1e6;
    std::cout << "Phase 06 real-time convolution benchmark (PFFFT backend " << sim::conv::Fft::simdArch()
              << "), 2 x 2, 48 kHz, host buffer " << host << " (budget " << budgetUs << " us)\n";
    for (const int p : {256, 512})
        for (const double seconds : {1.0, 3.0, 6.0, 12.0})
        {
            const auto len = static_cast<std::size_t>(seconds * fs);
            auto irA = emptyIr(fs, len), irB = emptyIr(fs, len);
            for (std::size_t path = 0; path < 4; ++path)
            {
                irA.taps[path] = conv_test::noise(len, 10u + path, 0.01);
                irB.taps[path] = conv_test::noise(len, 20u + path, 0.01);
            }
            sim::RealtimeEngine engine(p);
            engine.prepare(fs, host);
            const auto setA = engine.makeIrSet(irA), setB = engine.makeIrSet(irB);
            REQUIRE(engine.submitIrSet(setA));
            std::vector<float> l = conv_test::noise(host, 1u), r = conv_test::noise(host, 2u), o0(host),
                               o1(host);
            const float* ins[2] = {l.data(), r.data()};
            float* outs[2] = {o0.data(), o1.data()};
            const auto measure = [&](bool fading) {
                std::vector<double> us;
                us.reserve(blocks);
                for (int i = 0; i < blocks; ++i)
                {
                    if (fading && !engine.convolver().isFading())
                        engine.submitIrSet(i % 2 ? setA : setB);
                    const auto t0 = std::chrono::steady_clock::now();
                    engine.process(ins, outs, host);
                    const auto t1 = std::chrono::steady_clock::now();
                    us.push_back(std::chrono::duration<double, std::micro>(t1 - t0).count());
                }
                double mean = 0.0;
                for (const double v : us)
                    mean += v;
                mean /= static_cast<double>(us.size());
                std::sort(us.begin(), us.end());
                return std::array<double, 3>{mean, us[us.size() / 2], us.back()};
            };
            for (int i = 0; i < 50; ++i) // warm-up
                engine.process(ins, outs, host);
            const auto steady = measure(false);
            const auto fade = measure(true);
            std::cout << std::fixed << std::setprecision(1) << "  P = " << p << ", IR " << seconds << " s ("
                      << sim::conv::partitionCount(len, p) << " partitions/path): steady mean "
                      << 100.0 * steady[0] / budgetUs << " % (median " << 100.0 * steady[1] / budgetUs
                      << " %, max " << 100.0 * steady[2] / budgetUs << " %); crossfading mean "
                      << 100.0 * fade[0] / budgetUs << " % (max " << 100.0 * fade[2] / budgetUs << " %)"
                      << (p == 512 && seconds > 2.5 && seconds < 3.5 ? "  <- AQ10 budget 15 %" : "") << "\n";
            engine.releaseRetired();
        }
    std::cout.unsetf(std::ios::fixed);
}
