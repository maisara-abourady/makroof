// Phase 06: conv::CrossfadingConvolver: the analytic crossfade (AQ4 30 ms, AX18 laws), pickup timing,
// latest-wins handover, back-to-back requests, zero allocations in process() (also during fades) and
// a TSan hammer test (requestIr from two threads while the audio thread processes).
#include "AllocationTracker.h"
#include "ConvTestUtil.h"
#include "sim/conv/CrossfadingConvolver.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <numbers>
#include <thread>
#include <vector>

namespace {

using sim::conv::CrossfadeLaw;
using sim::conv::CrossfadingConvolver;
using sim::conv::IrSet;

constexpr int kFade48k = 1440; // AQ4: 30 ms at 48 kHz

std::shared_ptr<const IrSet> monoIr(const std::vector<float>& h, int p)
{
    return IrSet::create(1, 1, {h}, p);
}

} // namespace

// Acceptance: switching A -> B mid-signal equals (1 - g) (x*A) + g (x*B) within -100 dB, g a 30 ms
// ramp starting at the block boundary where the swap is picked up (the first output sample of the
// partition computed after the request: s0 = (floor(r / P) + 1) P for a request after r input
// samples). Equal gain (linear g) and equal power (cos / sin of g pi/2, AX18).
TEST_CASE("CrossfadingConvolver A -> B equals the analytic crossfade (-100 dB)", "[conv][crossfade]")
{
    const int p = GENERATE(128, 256, 512);
    const auto law = GENERATE(CrossfadeLaw::EqualGain, CrossfadeLaw::EqualPower);
    const int block = GENERATE(1, 37, 512, 2048, 0);
    const auto hA = conv_test::noise(6000, 71u, 0.3);
    const auto hB = conv_test::noise(9000, 72u, 0.3);
    const auto x = conv_test::noise(30000, 73u, 0.5);
    const auto refA = conv_test::reference(x, hA);
    const auto refB = conv_test::reference(x, hB);

    CrossfadingConvolver c;
    c.prepare(1, 1, 2048, p, sim::conv::partitionCount(9000, p), kFade48k);
    REQUIRE(c.requestIr(monoIr(hA, p), law));
    const std::size_t total = x.size() + 9000 + static_cast<std::size_t>(p);
    std::vector<float> in(total, 0.0f), out(total, 0.0f);
    std::copy(x.begin(), x.end(), in.begin());

    // Request B before the first block that starts at or after sample 10 001 (mid-signal, not on a
    // partition boundary for any P).
    const std::size_t requestAfter = 10001;
    std::size_t pos = 0;
    std::size_t requestedAt = 0;
    bool requested = false;
    for (int n : conv_test::blockSchedule(total, block, 21u))
    {
        if (!requested && pos >= requestAfter)
        {
            REQUIRE(c.requestIr(monoIr(hB, p), law));
            requested = true;
            requestedAt = pos;
        }
        c.process(in.data() + pos, out.data() + pos, n);
        pos += static_cast<std::size_t>(n);
    }
    REQUIRE(requested);
    REQUIRE(c.fadeCount() == 1);
    const auto pp = static_cast<std::size_t>(p);
    const auto s0 = static_cast<std::int64_t>((requestedAt / pp + 1) * pp);
    CHECK(c.fadeStartSample() == s0);
    CHECK_FALSE(c.isFading());

    // Analytic expectation in output time s (latency P: input time s - P).
    std::vector<double> expected(total, 0.0);
    for (std::size_t s = pp; s < total; ++s)
    {
        const std::size_t t = s - pp;
        const double a = t < refA.size() ? refA[t] : 0.0;
        const double b = t < refB.size() ? refB[t] : 0.0;
        const double g = std::clamp(static_cast<double>(static_cast<std::int64_t>(s) - s0) / kFade48k, 0.0,
                                    1.0);
        const double wA = law == CrossfadeLaw::EqualGain ? 1.0 - g : std::cos(g * std::numbers::pi / 2.0);
        const double wB = law == CrossfadeLaw::EqualGain ? g : std::sin(g * std::numbers::pi / 2.0);
        expected[s] = wA * a + wB * b;
    }
    const double db = conv_test::residualDb(out, expected, 0);
    INFO("P = " << p << ", law " << (law == CrossfadeLaw::EqualGain ? "equal gain" : "equal power")
                << ", block " << block << ", request at " << requestedAt << ", s0 " << s0 << ": " << db
                << " dB");
    CHECK(db <= -100.0);
}

TEST_CASE("CrossfadingConvolver: first IR is installed at once, output = x * A delayed by P",
          "[conv][crossfade]")
{
    const int p = 256;
    const auto h = conv_test::noise(5000, 81u, 0.3);
    const auto x = conv_test::noise(12000, 82u, 0.5);
    CrossfadingConvolver c;
    c.prepare(1, 1, 512, p, 40, kFade48k);
    CHECK(c.currentIr() == nullptr);
    REQUIRE(c.requestIr(monoIr(h, p)));
    std::vector<float> in(x.size() + h.size() + p, 0.0f), out(in.size(), 0.0f);
    std::copy(x.begin(), x.end(), in.begin());
    std::size_t pos = 0;
    for (int n : conv_test::blockSchedule(in.size(), 0, 5u, 512))
    {
        const float* ins[1] = {in.data() + pos};
        float* outs[1] = {out.data() + pos};
        c.process(ins, outs, n);
        pos += static_cast<std::size_t>(n);
    }
    CHECK(c.fadeCount() == 0);
    CHECK(c.currentIr() != nullptr);
    CHECK(conv_test::residualDb(out, conv_test::reference(x, h), p) <= -120.0);
}

TEST_CASE("CrossfadingConvolver rejects IrSets that don't fit prepare()", "[conv][crossfade]")
{
    CrossfadingConvolver c;
    c.prepare(2, 2, 512, 256, 10, kFade48k);
    std::vector<std::vector<float>> four(4, std::vector<float>(100, 0.0f));
    CHECK_FALSE(c.requestIr(nullptr));
    CHECK_FALSE(c.requestIr(IrSet::create(1, 1, {std::vector<float>(100)}, 256))); // shape
    CHECK_FALSE(c.requestIr(IrSet::create(2, 2, four, 512)));                      // partition size
    CHECK_FALSE(c.requestIr(IrSet::create(2, 2, std::vector<std::vector<float>>(4, std::vector<float>(2561)),
                                          256))); // > 10 partitions
    CHECK(c.requestIr(IrSet::create(2, 2, four, 256)));
}

TEST_CASE("CrossfadingConvolver: a request during a fade waits, and the latest one wins", "[conv][crossfade]")
{
    const int p = 128;
    CrossfadingConvolver c;
    c.prepare(1, 1, 64, p, 4, kFade48k);
    std::vector<std::shared_ptr<const IrSet>> irs;
    for (int i = 0; i < 4; ++i)
        irs.push_back(monoIr(conv_test::noise(300, 90u + static_cast<std::uint64_t>(i)), p));
    std::vector<float> in(64, 0.1f), out(64);
    const auto run = [&](int blocks) {
        for (int b = 0; b < blocks; ++b)
            c.process(in.data(), out.data(), 64);
    };
    REQUIRE(c.requestIr(irs[0]));
    run(2); // one partition computed: irs[0] installed
    CHECK(c.currentIr() == irs[0].get());
    REQUIRE(c.requestIr(irs[1]));
    run(2);
    CHECK(c.isFading());
    const auto firstFade = c.fadeStartSample();
    // Two requests during the fade: irs[2] is superseded by irs[3] before the audio thread sees it.
    REQUIRE(c.requestIr(irs[2]));
    REQUIRE(c.requestIr(irs[3]));
    run(2);
    CHECK(c.isFading());
    CHECK(c.fadeStartSample() == firstFade); // the running fade isn't interrupted
    run(2 * (kFade48k / 64 + 4));
    CHECK(c.fadeCount() == 2);
    CHECK(c.currentIr() == irs[3].get());
    CHECK(c.fadeStartSample() >= firstFade + kFade48k); // the second fade starts after the first ends
    CHECK(c.releaseRetired() == 2);                     // irs[0] and irs[1]; irs[2] was freed by requestIr
    CHECK(irs[0].use_count() == 1);
    CHECK(irs[1].use_count() == 1);
    CHECK(irs[2].use_count() == 1);
    CHECK(irs[3].use_count() == 2);
}

// Acceptance: back-to-back requestIr calls (100 in 1 s) neither crash nor leak (ASan) and the last
// IR wins.
TEST_CASE("CrossfadingConvolver: 100 requests in 1 s, the last one wins", "[conv][crossfade]")
{
    constexpr int fs = 48000, p = 512, block = 480; // a request every 10 ms of audio
    const auto x = conv_test::noise(fs * 2, 99u, 0.5);
    std::vector<std::vector<float>> taps;
    for (int i = 0; i < 100; ++i)
        taps.push_back(conv_test::noise(2000, 500u + static_cast<std::uint64_t>(i), 0.3));
    std::weak_ptr<const IrSet> firstIr;
    CrossfadingConvolver c;
    c.prepare(1, 1, block, p, sim::conv::partitionCount(2000, p), kFade48k);
    std::vector<float> out(x.size(), 0.0f);
    for (std::size_t pos = 0, i = 0; pos < x.size(); pos += block)
    {
        if (i < taps.size())
        {
            auto ir = monoIr(taps[i], p);
            if (i == 0)
                firstIr = ir;
            REQUIRE(c.requestIr(std::move(ir), i % 2 ? CrossfadeLaw::EqualPower : CrossfadeLaw::EqualGain));
            ++i;
        }
        const float* ins[1] = {x.data() + pos};
        float* outs[1] = {out.data() + pos};
        c.process(ins, outs, block);
        c.releaseRetired();
    }
    REQUIRE(c.currentIr() != nullptr);
    CHECK_FALSE(c.isFading());
    CHECK(firstIr.expired()); // retired and freed on this (non-audio) thread
    // The last IR is the current one: the output's last second is x * taps.back().
    const auto ref = conv_test::reference(x, taps.back());
    const std::size_t from = static_cast<std::size_t>(fs) + 10000;
    long double err = 0.0L, sig = 0.0L;
    for (std::size_t s = from; s < out.size(); ++s)
    {
        const long double d = static_cast<long double>(out[s]) - ref[s - p];
        err += d * d;
        sig += static_cast<long double>(ref[s - p]) * ref[s - p];
    }
    CHECK(10.0 * std::log10(static_cast<double>(err / sig)) <= -120.0);
}

// Acceptance: zero heap allocations in process() for all block sizes, including during crossfades.
TEST_CASE("CrossfadingConvolver::process allocates nothing, also while fading", "[conv][crossfade][alloc]")
{
    const int p = GENERATE(128, 256, 512);
    CrossfadingConvolver c;
    c.prepare(2, 2, 2048, p, 30, kFade48k);
    std::vector<std::shared_ptr<const IrSet>> irs;
    for (int i = 0; i < 3; ++i)
        irs.push_back(IrSet::create(
            2, 2,
            std::vector<std::vector<float>>(4, conv_test::noise(3000, 7u + static_cast<std::uint64_t>(i))),
            p));
    std::vector<float> a(2048, 0.1f), b(2048, -0.2f), o0(2048), o1(2048);
    const float* ins[2] = {a.data(), b.data()};
    float* outs[2] = {o0.data(), o1.data()};
    std::size_t allocations = 0, frees = 0;
    int k = 0;
    for (const int n : {1, 37, 64, 512, 2048})
    {
        const auto law = k % 2 ? CrossfadeLaw::EqualPower : CrossfadeLaw::EqualGain;
        REQUIRE(c.requestIr(irs[static_cast<std::size_t>(k % 3)], law));
        ++k;
        const auto fadesBefore = c.fadeCount();
        for (int done = 0; done < 6000; done += n)
        {
            test_support::ScopedTracking tracking;
            c.process(ins, outs, n);
            allocations += tracking.allocations();
            frees += tracking.deallocations(); // retired IrSets are freed by releaseRetired(), not here
        }
        if (k > 1) // the first request installs at once; every later one fades
            CHECK(c.fadeCount() == fadesBefore + 1);
        c.releaseRetired();
    }
    CHECK(allocations == 0);
    CHECK(frees == 0);
}

// Acceptance: TSan job (Linux) passes on a test that hammers requestIr from 2 threads while the
// audio thread processes. (Also runs, as a plain stress test, in every other build.)
TEST_CASE("CrossfadingConvolver: requestIr from two threads while processing (TSan)",
          "[conv][crossfade][tsan]")
{
    constexpr int p = 128, block = 64;
    CrossfadingConvolver c;
    c.prepare(2, 2, block, p, 8, 96);
    std::vector<std::shared_ptr<const IrSet>> irs;
    for (int i = 0; i < 6; ++i)
        irs.push_back(IrSet::create(
            2, 2,
            std::vector<std::vector<float>>(4, conv_test::noise(900, 40u + static_cast<std::uint64_t>(i))),
            p));
    REQUIRE(c.requestIr(irs[0]));

    std::atomic<bool> stop{false};
    std::atomic<std::size_t> requests{0};
    std::atomic<std::size_t> refused{0};
    const auto requester = [&](std::size_t offset) {
        std::size_t i = offset;
        while (!stop.load(std::memory_order_relaxed))
        {
            // Fresh copies too, so IrSets are created and destroyed on these threads.
            auto ir = i % 3 == 0
                          ? IrSet::create(
                                2, 2, std::vector<std::vector<float>>(4, std::vector<float>(300, 0.01f)), p)
                          : irs[i % irs.size()];
            // No Catch2 assertions off the main thread (they aren't thread-safe): count instead.
            if (!c.requestIr(std::move(ir), i % 2 ? CrossfadeLaw::EqualGain : CrossfadeLaw::EqualPower))
                refused.fetch_add(1, std::memory_order_relaxed);
            c.releaseRetired();
            requests.fetch_add(1, std::memory_order_relaxed);
            ++i;
            std::this_thread::yield();
        }
    };
    std::thread t1(requester, 0), t2(requester, 1);

    std::vector<float> a(block, 0.1f), b(block, -0.1f), o0(block), o1(block);
    const float* ins[2] = {a.data(), b.data()};
    float* outs[2] = {o0.data(), o1.data()};
    const auto until = std::chrono::steady_clock::now() + std::chrono::milliseconds(700);
    std::uint64_t blocks = 0;
    while (std::chrono::steady_clock::now() < until)
    {
        c.process(ins, outs, block);
        ++blocks;
    }
    stop = true;
    t1.join();
    t2.join();
    c.releaseRetired();
    INFO(requests.load() << " requests, " << blocks << " blocks, " << c.fadeCount() << " fades");
    CHECK(refused.load() == 0);
    CHECK(requests.load() > 10);
    CHECK(c.fadeCount() > 0);
}
