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
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>

// Exact comparisons are intended (untouched buffers, exact zeros).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

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

// This thread's CPU time in microseconds (POSIX CLOCK_THREAD_CPUTIME_ID: Linux, macOS), or -1 where it
// isn't available (Windows: GetThreadTimes counts in scheduler quanta, too coarse for a 1.3 ms callback).
double threadCpuMicros() noexcept
{
#if defined(CLOCK_THREAD_CPUTIME_ID)
    timespec ts{};
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) == 0)
        return static_cast<double>(ts.tv_sec) * 1e6 + static_cast<double>(ts.tv_nsec) * 1e-3;
#endif
    return -1.0;
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

// Phase 06b scope 3 (AX32): input samples with |x| > 2^20, and NaN / +-Inf, are taken in as 0, before the
// forward FFT, so a huge finite burst cannot overflow the FDL. (a) With bursts that overflow the FDL
// without the bound (an isolated +1e38, an isolated -FLT_MAX, a same-sign run of 2P samples at +1e38:
// 2P * 1e38 > FLT_MAX), every output sample is finite and the output nulls (-120 dB, phase-06 AC 2 gate)
// against renderOffline of the input with exactly those samples zeroed. (b) From output sample
// s_last + L + 4P on, the output nulls against the render of the burst-free input (recovery; valid under
// any treatment). (c) A sample of exactly +-B is kept and one of nextafter(B, +inf) /
// nextafter(-B, -inf) is zeroed, each against the matching reference.
TEST_CASE("RealtimeEngine bounds input samples at 2^20 (AX32)", "[conv][engine]")
{
    const int p = GENERATE(128, 256, 512);
    constexpr float kB = sim::conv::CrossfadingConvolver::kInputBound;
    STATIC_REQUIRE(kB == 1048576.0f);
    constexpr std::size_t kTaps = 5000;
    auto ir = emptyIr(48000.0, kTaps);
    for (std::size_t path = 0; path < 4; ++path)
        ir.taps[path] = conv_test::noise(kTaps, 90u + path, 0.2);
    const auto pp = static_cast<std::size_t>(p);
    const auto runOne = [&](const sim::MultiChannel& in, std::size_t frames) {
        sim::RealtimeEngine engine(p);
        engine.prepare(48000.0, 512);
        REQUIRE(engine.submitRoomIR(ir));
        return runEngine(engine, in, frames, 0, 512);
    };
    const auto nullDb = [&](const std::vector<float>& y, const std::vector<float>& ref, std::size_t from) {
        const std::vector<float> yw(y.begin() + static_cast<std::ptrdiff_t>(from + pp), y.end());
        const std::vector<double> rw(ref.begin() + static_cast<std::ptrdiff_t>(from), ref.end());
        return conv_test::residualDb(yw, rw, 0);
    };

    SECTION("(a) overflowing bursts: finite output, null against the zeroed input; (b) recovery")
    {
        const sim::MultiChannel clean = {conv_test::noise(20000, 95u, 0.2),
                                         conv_test::noise(20000, 96u, 0.2)};
        sim::MultiChannel x = clean, zeroed = clean;
        const auto put = [&](std::size_t c, std::size_t i, float v) {
            x[c][i] = v;
            zeroed[c][i] = 0.0f;
        };
        put(0, 1000, 1e38f);
        put(1, 1500, -std::numeric_limits<float>::max());
        const std::size_t runStart = 2000;
        for (std::size_t i = 0; i < 2 * pp; ++i)
        {
            put(0, runStart + i, 1e38f);
            put(1, runStart + i, 1e38f);
        }
        const std::size_t sLast = runStart + 2 * pp - 1;
        const auto refZeroed = sim::renderOffline(ir, zeroed);
        const auto refClean = sim::renderOffline(ir, clean);
        const auto out = runOne(x, refZeroed[0].size() + pp);
        const std::size_t recoveryFrom = sLast + kTaps + 4 * pp;
        REQUIRE(refClean[0].size() >= recoveryFrom + 4096);
        for (std::size_t m = 0; m < 2; ++m)
        {
            INFO("P " << p << ", output " << m);
            CHECK(std::all_of(out[m].begin(), out[m].end(), [](float v) { return std::isfinite(v); }));
            CHECK(nullDb(out[m], refZeroed[m], 0) <= -120.0);
            CHECK(nullDb(out[m], refClean[m], recoveryFrom) <= -120.0);
        }
    }

    SECTION("(c) +-B is kept, the next float beyond it is zeroed")
    {
        for (const float v : {kB, -kB, std::nextafter(kB, std::numeric_limits<float>::infinity()),
                              std::nextafter(-kB, -std::numeric_limits<float>::infinity())})
        {
            const bool kept = std::fabs(v) <= kB;
            sim::MultiChannel x = {conv_test::noise(12000, 97u, 0.2), conv_test::noise(12000, 98u, 0.2)};
            x[0][3000] = v;
            sim::MultiChannel expected = x;
            if (!kept)
                expected[0][3000] = 0.0f;
            const auto ref = sim::renderOffline(ir, expected);
            const auto out = runOne(x, ref[0].size() + pp);
            for (std::size_t m = 0; m < 2; ++m)
            {
                INFO("P " << p << ", sample " << v << (kept ? " (kept)" : " (zeroed)") << ", output " << m);
                CHECK(nullDb(out[m], ref[m], 0) <= -120.0);
            }
        }
    }
}

// Phase 06b scope 4: an IR with a NaN, +Inf or -Inf tap is refused (makeIrSet gives nullptr,
// submitRoomIR returns false) and the engine keeps playing its current IR: the output still nulls
// against the offline render of that IR (-120 dB) and no fade starts.
TEST_CASE("RealtimeEngine refuses an IR with a non-finite tap and keeps the current IR", "[conv][engine]")
{
    const float bad = GENERATE(std::numeric_limits<float>::quiet_NaN(),
                               std::numeric_limits<float>::infinity(),
                               -std::numeric_limits<float>::infinity());
    sim::RealtimeEngine engine(256);
    engine.prepare(48000.0, 512);
    auto ir = emptyIr(48000.0, 5000);
    for (std::size_t path = 0; path < 4; ++path)
        ir.taps[path] = conv_test::noise(5000, 80u + path, 0.2);
    REQUIRE(engine.submitRoomIR(ir));
    auto poisoned = ir;
    poisoned.taps[2][4321] = bad;
    INFO("bad tap " << bad);
    CHECK(engine.makeIrSet(poisoned) == nullptr);

    const sim::MultiChannel x = {conv_test::noise(20000, 85u), conv_test::noise(20000, 86u)};
    const auto ref = sim::renderOffline(ir, x);
    const std::size_t total = ref[0].size() + 256;
    std::vector<std::vector<float>> in(2, std::vector<float>(total, 0.0f)),
        out(2, std::vector<float>(total, 0.0f));
    for (std::size_t c = 0; c < 2; ++c)
        std::copy(x[c].begin(), x[c].end(), in[c].begin());
    std::size_t pos = 0;
    bool refused = false;
    for (const int n : conv_test::blockSchedule(total, 0, 19u, 512))
    {
        if (!refused && pos >= 6000) // mid-stream, with the first IR playing
        {
            CHECK_FALSE(engine.submitRoomIR(poisoned));
            refused = true;
        }
        const float* ins[2] = {in[0].data() + pos, in[1].data() + pos};
        float* outs[2] = {out[0].data() + pos, out[1].data() + pos};
        engine.process(ins, outs, n);
        pos += static_cast<std::size_t>(n);
    }
    REQUIRE(refused);
    CHECK(engine.convolver().fadeCount() == 0); // the first IR was installed at once; nothing faded
    for (std::size_t m = 0; m < 2; ++m)
    {
        CHECK(std::all_of(out[m].begin(), out[m].end(), [](float v) { return std::isfinite(v); }));
        const std::vector<double> r(ref[m].begin(), ref[m].end());
        CHECK(conv_test::residualDb(out[m], r, 256) <= -120.0);
    }
}

TEST_CASE("RealtimeEngine::process allocates nothing, including IR swaps", "[conv][engine][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("AllocationTracker inactive under AddressSanitizer (ASan keeps its own operator new/delete)");
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
TEST_CASE("benchmark: real-time convolution 2 x 2, 48 kHz, host buffers 512 and 64", "[.][benchmark]")
{
    // Per host callback, as % of that callback's real-time budget (host / fs): mean, 99.9th percentile
    // and max, steady and while crossfading continuously. The p99.9 / max at host buffer 64 show the
    // work spreading (a whole partition is no longer computed in one callback). The max includes
    // runner preemption, which is not the convolver: recorded, never a pass/fail (phase-06 AC 8).
    constexpr double fs = 48000.0;
    constexpr std::size_t audioSamples = 1500 * 512; // 16 s of audio per measurement
    std::cout << "Phase 06 real-time convolution benchmark (PFFFT backend " << sim::conv::Fft::simdArch()
              << "), 2 x 2, 48 kHz; % of the callback budget (512: 10667 us, 64: 1333 us)\n";
    for (const int host : {512, 64})
        for (const int p : {256, 512})
            for (const double seconds : {1.0, 3.0, 6.0, 12.0})
            {
                const double budgetUs = host / fs * 1e6;
                const std::size_t callbacks = audioSamples / static_cast<std::size_t>(host);
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
                std::vector<float> l = conv_test::noise(static_cast<std::size_t>(host), 1u),
                                   r = conv_test::noise(static_cast<std::size_t>(host), 2u),
                                   o0(static_cast<std::size_t>(host)), o1(static_cast<std::size_t>(host));
                const float* ins[2] = {l.data(), r.data()};
                float* outs[2] = {o0.data(), o1.data()};
                // Per callback: wall-clock time, and (POSIX) this thread's CPU time, which excludes
                // time the runner's scheduler took the thread off the CPU (preemption). Returns mean,
                // p99.9 and max of the wall time, then p99.9 and max of the CPU time (-1 if unavailable),
                // all as % of the callback budget.
                const auto measure = [&](bool fading) {
                    std::vector<double> us, cpu;
                    us.reserve(callbacks);
                    cpu.reserve(callbacks);
                    for (std::size_t i = 0; i < callbacks; ++i)
                    {
                        if (fading && !engine.convolver().isFading())
                            engine.submitIrSet(i % 2 ? setA : setB);
                        const double c0 = threadCpuMicros();
                        const auto t0 = std::chrono::steady_clock::now();
                        engine.process(ins, outs, host);
                        const auto t1 = std::chrono::steady_clock::now();
                        const double c1 = threadCpuMicros();
                        us.push_back(std::chrono::duration<double, std::micro>(t1 - t0).count());
                        cpu.push_back(c0 >= 0.0 ? c1 - c0 : -1.0);
                    }
                    double mean = 0.0;
                    for (const double v : us)
                        mean += v;
                    mean /= static_cast<double>(us.size());
                    std::sort(us.begin(), us.end());
                    std::sort(cpu.begin(), cpu.end());
                    const std::size_t i999 = std::min(us.size() - 1, us.size() * 999 / 1000);
                    const bool haveCpu = cpu.front() >= 0.0;
                    return std::array<double, 5>{100.0 * mean / budgetUs, 100.0 * us[i999] / budgetUs,
                                                 100.0 * us.back() / budgetUs,
                                                 haveCpu ? 100.0 * cpu[i999] / budgetUs : -1.0,
                                                 haveCpu ? 100.0 * cpu.back() / budgetUs : -1.0};
                };
                for (int i = 0; i < 4 * p / host + 50; ++i) // warm-up
                    engine.process(ins, outs, host);
                const auto steady = measure(false);
                const auto fade = measure(true);
                const auto cpuText = [](const std::array<double, 5>& m) {
                    std::ostringstream t;
                    t << std::fixed << std::setprecision(1);
                    if (m[3] >= 0.0)
                        t << "; thread-CPU p99.9 " << m[3] << " %, max " << m[4] << " %";
                    return t.str();
                };
                std::cout << std::fixed << std::setprecision(1) << "  host " << host << ", P = " << p
                          << ", IR " << seconds << " s (" << sim::conv::partitionCount(len, p)
                          << " partitions/path): steady mean " << steady[0] << " % (p99.9 " << steady[1]
                          << " %, max " << steady[2] << " %" << cpuText(steady) << "); crossfading mean "
                          << fade[0] << " % (p99.9 " << fade[1] << " %, max " << fade[2] << " %"
                          << cpuText(fade) << ")";
                if (host == 512 && p == 512 && seconds > 2.5 && seconds < 3.5)
                    std::cout << "  <- AQ10 budget 15 % (mean): "
                              << (steady[0] <= 15.0 && fade[0] <= 15.0 ? "met" : "MISSED");
                if (host == 64 && p == 512 && seconds > 11.5)
                {
                    std::cout << "  <- worst-case callback, target p99.9 < 100 % while crossfading: wall "
                              << (fade[1] < 100.0 ? "met" : "MISSED");
                    if (fade[3] >= 0.0)
                        std::cout << ", thread-CPU " << (fade[3] < 100.0 ? "met" : "MISSED");
                }
                std::cout << "\n";
                engine.releaseRetired();
            }
    std::cout.unsetf(std::ios::fixed);
}

TEST_CASE("RealtimeEngine::process before a successful prepare() writes silence", "[conv][engine]")
{
    sim::RealtimeEngine engine;
    std::vector<float> l(64, 0.5f), r(64, 0.5f), o0(64, 7.0f), o1(64, 7.0f);
    const float* ins[2] = {l.data(), r.data()};
    float* outs[2] = {o0.data(), o1.data()};
    conv_test::runWithWatchdog([&] { engine.process(ins, outs, 64); },
                               "RealtimeEngine::process (unprepared)");
    CHECK(std::all_of(o0.begin(), o0.end(), [](float v) { return v == 0.0f; }));
    CHECK_THROWS_AS(engine.prepare(22050.0, 64), std::invalid_argument);
    std::fill(o1.begin(), o1.end(), 7.0f);
    conv_test::runWithWatchdog([&] { engine.process(ins, outs, 64); },
                               "RealtimeEngine::process (failed prepare)");
    CHECK(std::all_of(o1.begin(), o1.end(), [](float v) { return v == 0.0f; }));
}

// Input guard: NaN and +-Inf host samples are taken in as 0, so they cannot poison the FDL: the
// output is finite everywhere and equals the render of the input with those samples zeroed.
TEST_CASE("RealtimeEngine replaces non-finite input samples by zero", "[conv][engine]")
{
    sim::RealtimeEngine engine(256);
    engine.prepare(48000.0, 512);
    auto ir = emptyIr(48000.0, 5000);
    for (std::size_t path = 0; path < 4; ++path)
        ir.taps[path] = conv_test::noise(5000, 70u + path, 0.2);
    REQUIRE(engine.submitRoomIR(ir));
    sim::MultiChannel x = {conv_test::noise(20000, 75u), conv_test::noise(20000, 76u)};
    sim::MultiChannel clean = x;
    x[0][1000] = std::numeric_limits<float>::quiet_NaN();
    x[1][3001] = std::numeric_limits<float>::infinity();
    x[0][7777] = -std::numeric_limits<float>::infinity();
    clean[0][1000] = clean[1][3001] = clean[0][7777] = 0.0f;
    const auto ref = sim::renderOffline(ir, clean);
    const auto out = runEngine(engine, x, ref[0].size() + 256, 0, 512);
    for (std::size_t m = 0; m < 2; ++m)
    {
        CHECK(std::all_of(out[m].begin(), out[m].end(), [](float v) { return std::isfinite(v); }));
        const std::vector<double> r(ref[m].begin(), ref[m].end());
        CHECK(conv_test::residualDb(out[m], r, 256) <= -120.0);
    }
}
