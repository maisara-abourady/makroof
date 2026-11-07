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

// Exact comparisons are intended (untouched buffers, exact zeros).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

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
// ramp starting at the block boundary where the swap is picked up. The mailbox is read at the first
// partition boundary after the request and the new state spends one block accumulating (work
// spreading), so its fade starts with the next block: s0 = (floor(r / P) + 2) P for a request after r input
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
    const auto s0 = static_cast<std::int64_t>((requestedAt / pp + 2) * pp);
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
    if (!test_support::trackerActive())
        SKIP("AllocationTracker inactive under AddressSanitizer (ASan keeps its own operator new/delete)");
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

// A first IR that arrives after processing has started fades in from silence (AQ4), so it never
// starts with a step: out = g (x*A) for equal gain, with g the 30 ms ramp from the pickup boundary.
TEST_CASE("CrossfadingConvolver: a first IR arriving mid-stream fades in from silence", "[conv][crossfade]")
{
    const int p = 256;
    const auto h = conv_test::noise(4000, 83u, 0.3);
    const auto x = conv_test::noise(20000, 84u, 0.5);
    const auto ref = conv_test::reference(x, h);
    CrossfadingConvolver c;
    c.prepare(1, 1, 512, p, 20, kFade48k);
    std::vector<float> in(x.size() + h.size() + p, 0.0f), out(in.size(), 0.0f);
    std::copy(x.begin(), x.end(), in.begin());
    std::size_t pos = 0, requestedAt = 0;
    for (int n : conv_test::blockSchedule(in.size(), 0, 9u, 512))
    {
        if (requestedAt == 0 && pos >= 3000)
        {
            REQUIRE(c.requestIr(monoIr(h, p)));
            requestedAt = pos;
        }
        c.process(in.data() + pos, out.data() + pos, n);
        pos += static_cast<std::size_t>(n);
    }
    CHECK(c.fadeCount() == 1);
    const auto pp = static_cast<std::size_t>(p);
    const auto s0 = static_cast<std::int64_t>((requestedAt / pp + 2) * pp);
    CHECK(c.fadeStartSample() == s0);
    std::vector<double> expected(out.size(), 0.0);
    for (std::size_t s = pp; s < out.size(); ++s)
    {
        const double g = std::clamp(static_cast<double>(static_cast<std::int64_t>(s) - s0) / kFade48k, 0.0,
                                    1.0);
        expected[s] = s - pp < ref.size() ? g * ref[s - pp] : 0.0;
    }
    CHECK(conv_test::residualDb(out, expected, 0) <= -100.0);
}

TEST_CASE("CrossfadingConvolver::process before prepare() returns at once", "[conv][crossfade]")
{
    CrossfadingConvolver c;
    std::vector<float> in(64, 0.5f), out(64, 7.0f);
    conv_test::runWithWatchdog([&] { c.process(in.data(), out.data(), 64); },
                               "CrossfadingConvolver::process");
    CHECK(out[0] == 7.0f);
    CHECK_FALSE(c.requestIr(monoIr(std::vector<float>(10, 0.1f), 128)));
}

// If the non-audio side never drains the release queue, the audio thread holds the next retired
// request and starts no new fade: nothing is dropped and nothing is freed on the audio thread. Once
// drained, fades resume.
TEST_CASE("CrossfadingConvolver: a full release queue pauses swaps, nothing is freed on the audio thread",
          "[conv][crossfade][alloc]")
{
    constexpr int p = 128;
    CrossfadingConvolver c;
    c.prepare(1, 1, p, p, 2, 8); // 8-sample fades: one swap per partition
    const auto ir = monoIr(std::vector<float>(100, 0.1f), p);
    std::vector<float> in(p, 0.1f), out(p);
    REQUIRE(c.requestIr(ir));
    c.process(in.data(), out.data(), p); // installs
    std::size_t frees = 0;
    for (int i = 0; i < 3 * static_cast<int>(CrossfadingConvolver::kReleaseQueueSize); ++i)
    {
        REQUIRE(c.requestIr(ir)); // allocates the request here, on the "message" thread
        test_support::ScopedTracking tracking;
        c.process(in.data(), out.data(), p);
        frees += tracking.deallocations();
    }
    if (test_support::trackerActive()) // under ASan the tracker counts nothing
        CHECK(frees == 0);
    // kReleaseQueueSize retired requests are queued, one more is held, then swaps stop.
    CHECK(c.fadeCount() == CrossfadingConvolver::kReleaseQueueSize + 1);
    CHECK(c.releaseRetired() == CrossfadingConvolver::kReleaseQueueSize);
    for (int i = 0; i < 4; ++i)
        c.process(in.data(), out.data(), p);
    CHECK(c.fadeCount() > CrossfadingConvolver::kReleaseQueueSize + 1);
    c.releaseRetired();
}

TEST_CASE("CrossfadingConvolver::reset during a fade ends it on the target and clears the history",
          "[conv][crossfade]")
{
    const int p = 128;
    const auto hA = conv_test::noise(500, 85u), hB = conv_test::noise(500, 86u);
    CrossfadingConvolver c;
    c.prepare(1, 1, p, p, 4, kFade48k);
    std::vector<float> in(p, 0.2f), out(p);
    REQUIRE(c.requestIr(monoIr(hA, p)));
    c.process(in.data(), out.data(), p);
    REQUIRE(c.requestIr(monoIr(hB, p)));
    c.process(in.data(), out.data(), p);
    REQUIRE(c.isFading());
    c.reset();
    CHECK_FALSE(c.isFading());
    CHECK(c.fadeStartSample() == -1);
    CHECK(c.releaseRetired() == 1); // A retired by reset(), freed here
    // After reset the output is x * B from scratch (latency P), with no trace of the old input.
    const auto x = conv_test::noise(3000, 87u);
    std::vector<float> xin(x.size() + hB.size() + p, 0.0f), y(xin.size());
    std::copy(x.begin(), x.end(), xin.begin());
    for (std::size_t pos = 0; pos < xin.size(); pos += p)
        c.process(xin.data() + pos, y.data() + pos,
                  static_cast<int>(std::min<std::size_t>(p, xin.size() - pos)));
    CHECK(conv_test::residualDb(y, conv_test::reference(x, hB), p) <= -120.0);
}

// Work spreading: no process() call does much more than its share of the block's k >= 1 work. With
// host buffer n and U = M N (K - 1) multiply-adds per state and block, a call does at most
// ceil(U n / P) + 1 per active state, plus at a partition boundary the k = 0 terms (N M per state).
// Without spreading, the boundary call would do all U per state at once.
TEST_CASE("CrossfadingConvolver spreads the partition work across small host buffers", "[conv][crossfade]")
{
    constexpr int p = 512, host = 64;
    constexpr std::size_t partitions = 60;
    CrossfadingConvolver c;
    c.prepare(2, 2, host, p, partitions, kFade48k);
    const auto taps = [](std::uint64_t seed) {
        return std::vector<std::vector<float>>(4, conv_test::noise(partitions * p, seed, 0.01));
    };
    const auto a = IrSet::create(2, 2, taps(1), p), b = IrSet::create(2, 2, taps(2), p);
    const std::uint64_t units = 2 * 2 * (partitions - 1);
    const std::uint64_t share = (units * host + p - 1) / p + 1;
    std::vector<float> l = conv_test::noise(host, 3u), r = conv_test::noise(host, 4u), o0(host), o1(host);
    const float* ins[2] = {l.data(), r.data()};
    float* outs[2] = {o0.data(), o1.data()};
    REQUIRE(c.requestIr(a));
    std::uint64_t worst = 0, worstFading = 0;
    for (int call = 0; call < 2000; ++call)
    {
        if (call % 300 == 150)
            REQUIRE(c.requestIr(call % 600 == 150 ? b : a, CrossfadeLaw::EqualPower));
        const bool fadingBefore = c.isFading();
        c.process(ins, outs, host);
        if (call < p / host) // the first boundary installs the first IR and renders it in full
            continue;
        const std::uint64_t macs = c.lastProcessMultiplyAdds();
        // Two states while a fade is pending or running (also in the call where it ends).
        const std::uint64_t states = fadingBefore || c.isFading() ? 2 : 1;
        CHECK(macs <= states * (share + 2 * 2));
        worst = std::max(worst, macs);
        if (c.isFading())
            worstFading = std::max(worstFading, macs);
    }
    INFO("worst call " << worst << " multiply-adds (fading " << worstFading << "), unspread block " << units
                       << " per state");
    CHECK(c.fadeCount() >= 4);
    CHECK(worstFading > 0);
    CHECK(worst < units); // far below one whole block of one state
}

// reset() mid-block during a fade, from a long A to a short B, then odd host blocks: the lanes must
// restart for the new current IR (a stale lane would run past B's partitions / accumulator).
TEST_CASE("CrossfadingConvolver::reset mid-block during a fade restarts the lanes", "[conv][crossfade]")
{
    const int p = 128;
    const auto hA = conv_test::noise(2000, 88u), hB = conv_test::noise(300, 89u);
    CrossfadingConvolver c;
    c.prepare(1, 1, 512, p, sim::conv::partitionCount(2000, p), kFade48k);
    std::vector<float> in(512, 0.2f), out(512);
    REQUIRE(c.requestIr(monoIr(hA, p)));
    c.process(in.data(), out.data(), p); // installs A
    REQUIRE(c.requestIr(monoIr(hB, p)));
    c.process(in.data(), out.data(), p + 50); // B taken, its lane running; 50 samples into a block
    REQUIRE(c.isFading());
    c.reset();
    CHECK(c.currentIr()->length() == 300);
    CHECK(c.releaseRetired() == 1);
    const auto x = conv_test::noise(3000, 90u);
    std::vector<float> xin(x.size() + hB.size() + p, 0.0f), y(xin.size());
    std::copy(x.begin(), x.end(), xin.begin());
    for (std::size_t pos = 0; pos < xin.size(); pos += 37)
        c.process(xin.data() + pos, y.data() + pos,
                  static_cast<int>(std::min<std::size_t>(37, xin.size() - pos)));
    CHECK(conv_test::residualDb(y, conv_test::reference(x, hB), p) <= -120.0);
}

// The per-call bound for host blocks that straddle partition boundaries (37, 100, random <= P): a
// call does at most ceil(U n / P) + 2 multiply-adds per active state (its share, split over at most
// two blocks) plus the boundary's k = 0 terms (N M per state).
TEST_CASE("CrossfadingConvolver work spreading holds for odd and random host blocks", "[conv][crossfade]")
{
    constexpr int p = 256;
    constexpr std::size_t partitions = 40;
    const int host = GENERATE(37, 100, 0);
    CrossfadingConvolver c;
    c.prepare(2, 2, p, p, partitions, kFade48k);
    const auto taps = [](std::uint64_t seed) {
        return std::vector<std::vector<float>>(4, conv_test::noise(partitions * p, seed, 0.01));
    };
    const auto a = IrSet::create(2, 2, taps(5), p), b = IrSet::create(2, 2, taps(6), p);
    const std::uint64_t units = 2 * 2 * (partitions - 1);
    std::vector<float> l = conv_test::noise(p, 7u), r = conv_test::noise(p, 8u), o0(p), o1(p);
    const float* ins[2] = {l.data(), r.data()};
    float* outs[2] = {o0.data(), o1.data()};
    REQUIRE(c.requestIr(a));
    std::size_t samples = 0;
    int call = 0;
    for (const int n : conv_test::blockSchedule(static_cast<std::size_t>(p) * 400, host, 13u, p))
    {
        if (call % 97 == 50)
            REQUIRE(c.requestIr(call % 194 == 50 ? b : a));
        const bool fadingBefore = c.isFading();
        const std::size_t before = samples;
        c.process(ins, outs, n);
        samples += static_cast<std::size_t>(n);
        ++call;
        if (before < static_cast<std::size_t>(p)) // contains the first boundary: first IR rendered in full
            continue;
        const std::uint64_t states = fadingBefore || c.isFading() ? 2 : 1;
        const std::uint64_t share = (units * static_cast<std::uint64_t>(n) + p - 1) / p + 2;
        INFO("host " << n << " (schedule " << host << "), call " << call);
        CHECK(c.lastProcessMultiplyAdds() <= states * (share + 2 * 2));
    }
    CHECK(c.fadeCount() >= 3);
}

// Phase 06b scope 6: the k >= 1 partitions are summed late-first (descending k), and this test pins
// that order (test rule: phase-06b decision D4, ledger P06B-27..29, 57..59; measurement in
// docs/review/phase-06b/measurements.md M2(b)).
// Constructed so that only the order of the additions decides, on any SIMD path and with or without
// FMA: constant input x = 1 (the FDL spectrum is DC-only, 2P), partition 1 holds one tap of 1.0 and
// partitions 2 .. K-1 one tap each of 2^-25 (below half an ulp of 1.0); the 1 / 2P scale is a power of
// two, so every product is exact. Summed late-first, the T tiny terms add exactly (T * 2^-25 = T/4 ulp)
// before 1.0 is added: steady-state output 1 + T * 2^-25, bit-exact. Summed early-first (the ascending
// mutant), each tiny term is rounded away against 1.0: output 1.0, an error of T/4 ulp. Measured on
// SSE (descending): 0 ulp at P = 128, 256, 512; the ascending mutant: 100 ulp.
TEST_CASE("CrossfadingConvolver sums the partitions late-first (exact-arithmetic case)", "[conv][crossfade]")
{
    const int p = GENERATE(128, 256, 512);
    const int tiny = 400; // T: the two orders are exactly 0 and T/4 = 100 ulp apart
    const int partitions = tiny + 2;
    std::vector<float> h(static_cast<std::size_t>(partitions * p), 0.0f);
    h[static_cast<std::size_t>(p)] = 1.0f;
    for (int k = 2; k < partitions; ++k)
        h[static_cast<std::size_t>(k * p + 3)] = std::ldexp(1.0f, -25);

    CrossfadingConvolver c;
    c.prepare(1, 1, 512, p, static_cast<std::size_t>(partitions), kFade48k);
    REQUIRE(c.requestIr(monoIr(h, p)));
    const std::size_t total = static_cast<std::size_t>((partitions + 4) * p);
    const std::vector<float> x(total, 1.0f);
    std::vector<float> y(total, 0.0f);
    std::size_t pos = 0;
    for (const int n : conv_test::blockSchedule(total, 0, 9u, 512))
    {
        c.process(x.data() + pos, y.data() + pos, n);
        pos += static_cast<std::size_t>(n);
    }
    const double ulp = std::ldexp(1.0, -23);
    const double expected = 1.0 + tiny * std::ldexp(1.0, -25);
    double worst = 0.0;
    for (std::size_t i = total - static_cast<std::size_t>(p); i < total; ++i) // steady state: last block
        worst = std::max(worst, std::abs(static_cast<double>(y[i]) - expected) / ulp);
    INFO("P " << p << ", T " << tiny << ": worst error " << worst << " ulp (ascending order: " << tiny / 4
              << " ulp)");
    // D4: the pass line is the midpoint of the two exact errors (0 and 100 ulp), a free margin: every
    // operation in this case is exact, so a correct build reads 0 on any SIMD path.
    CHECK(worst <= 50.0);
}
