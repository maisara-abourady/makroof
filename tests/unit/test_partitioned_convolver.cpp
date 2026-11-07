// Phase 06: conv::Fft (PFFFT wrapper), conv::IrSet and conv::PartitionedConvolver (UPOLS) against
// the Phase 02 reference convolution (sim::convolve / sim::renderOffline), the denormal guard, and
// zero heap allocations in process().
#include "AllocationTracker.h"
#include "ConvTestUtil.h"
#include "sim/Engine.h"
#include "sim/OfflineRender.h"
#include "sim/conv/CrossfadingConvolver.h"
#include "sim/conv/Denormals.h"
#include "sim/conv/Fft.h"
#include "sim/conv/PartitionedConvolver.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <algorithm>
#include <cmath>
#include <complex>
#include <limits>
#include <numbers>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

// Feeds x (then P + h - 1 zeros, so the whole tail comes out) through a 1 x 1 convolver in the
// given host block schedule and returns everything it produced.
std::vector<float> runMono(const std::vector<float>& x, const std::vector<float>& h, int partitionSize,
                           int blockSize, int maxBlock = 2048)
{
    sim::conv::PartitionedConvolver c;
    c.prepare(1, 1, maxBlock, partitionSize, sim::conv::partitionCount(h.size(), partitionSize));
    c.setIrSet(sim::conv::IrSet::create(1, 1, {h}, partitionSize));
    std::vector<float> in(x.size() + h.size() - 1 + static_cast<std::size_t>(partitionSize), 0.0f);
    std::copy(x.begin(), x.end(), in.begin());
    std::vector<float> out(in.size(), 0.0f);
    std::size_t pos = 0;
    for (const int n : conv_test::blockSchedule(in.size(), blockSize, 11u, maxBlock))
    {
        c.process(in.data() + pos, out.data() + pos, n);
        pos += static_cast<std::size_t>(n);
    }
    return out;
}

std::string blockName(int b)
{
    return b == 0 ? std::string("random") : std::to_string(b);
}

} // namespace

TEST_CASE("conv::Fft forward matches a double-precision DFT and inverts with scale N", "[conv][fft]")
{
    const int n = GENERATE(32, 256, 1024);
    sim::conv::Fft fft(n);
    auto x = sim::conv::allocateAligned(static_cast<std::size_t>(n));
    const auto ref = conv_test::noise(static_cast<std::size_t>(n), 5u, 1.0);
    for (int i = 0; i < n; ++i)
        x[static_cast<std::size_t>(i)] = ref[static_cast<std::size_t>(i)];

    auto ordered = sim::conv::allocateAligned(static_cast<std::size_t>(n));
    fft.forwardOrdered(x.get(), ordered.get());
    double maxErr = 0.0, scale = 0.0;
    for (int k = 0; k <= n / 2; ++k)
    {
        std::complex<double> s{};
        for (int t = 0; t < n; ++t)
            s += static_cast<double>(ref[static_cast<std::size_t>(t)])
                 * std::polar(1.0, -2.0 * std::numbers::pi * k * t / n);
        std::complex<double> got;
        if (k == 0)
            got = {ordered[0], 0.0};
        else if (k == n / 2)
            got = {ordered[1], 0.0};
        else
            got = {ordered[static_cast<std::size_t>(2 * k)], ordered[static_cast<std::size_t>(2 * k + 1)]};
        maxErr = std::max(maxErr, std::abs(got - s));
        scale = std::max(scale, std::abs(s));
    }
    CHECK(maxErr / scale < 1e-5);

    auto spec = sim::conv::allocateAligned(static_cast<std::size_t>(n));
    auto back = sim::conv::allocateAligned(static_cast<std::size_t>(n));
    fft.forward(x.get(), spec.get());
    fft.inverse(spec.get(), back.get());
    for (int i = 0; i < n; ++i)
        CHECK(std::abs(back[static_cast<std::size_t>(i)] / static_cast<float>(n)
                       - ref[static_cast<std::size_t>(i)])
              < 1e-5f);

    CHECK_THROWS_AS(sim::conv::Fft(16), std::invalid_argument);
    CHECK_THROWS_AS(sim::conv::Fft(1000), std::invalid_argument);
}

TEST_CASE("conv::Fft multiplyAccumulate is circular convolution", "[conv][fft]")
{
    constexpr int n = 64;
    sim::conv::Fft fft(n);
    const auto a = conv_test::noise(n, 1u, 1.0), b = conv_test::noise(n, 2u, 1.0);
    auto ta = sim::conv::allocateAligned(n), tb = sim::conv::allocateAligned(n);
    for (int i = 0; i < n; ++i)
    {
        ta[static_cast<std::size_t>(i)] = a[static_cast<std::size_t>(i)];
        tb[static_cast<std::size_t>(i)] = b[static_cast<std::size_t>(i)];
    }
    auto sa = sim::conv::allocateAligned(n), sb = sim::conv::allocateAligned(n),
         acc = sim::conv::allocateAligned(n);
    fft.forward(ta.get(), sa.get());
    fft.forward(tb.get(), sb.get());
    fft.multiplyAccumulate(sa.get(), sb.get(), acc.get(), 1.0f / n);
    fft.multiplyAccumulate(sa.get(), sb.get(), acc.get(), 1.0f / n); // accumulates: 2x
    auto y = sim::conv::allocateAligned(n);
    fft.inverse(acc.get(), y.get());
    for (int t = 0; t < n; ++t)
    {
        double s = 0.0;
        for (int k = 0; k < n; ++k)
            s += static_cast<double>(a[static_cast<std::size_t>(k)])
                 * b[static_cast<std::size_t>((t - k + n) % n)];
        CHECK(std::abs(y[static_cast<std::size_t>(t)] - 2.0 * s) < 1e-4);
    }
}

TEST_CASE("IrSet geometry and validation", "[conv]")
{
    CHECK(sim::conv::partitionCount(0, 512) == 1);
    CHECK(sim::conv::partitionCount(1, 512) == 1);
    CHECK(sim::conv::partitionCount(512, 512) == 1);
    CHECK(sim::conv::partitionCount(513, 512) == 2);
    const auto set = sim::conv::IrSet::create(2, 2,
                                              {std::vector<float>(1000, 0.1f), std::vector<float>(1000),
                                               std::vector<float>(1000), std::vector<float>(1000)},
                                              256, 48000.0);
    CHECK(set->numPartitions() == 4);
    CHECK(set->length() == 1000);
    CHECK(set->sampleRate() == 48000.0);
    CHECK_THROWS_AS(sim::conv::IrSet::create(1, 1, {std::vector<float>(10)}, 1024), std::invalid_argument);
    CHECK_THROWS_AS(sim::conv::IrSet::create(1, 2, {std::vector<float>(10)}, 512), std::invalid_argument);
    CHECK_THROWS_AS(sim::conv::IrSet::create(1, 2, {std::vector<float>(10), std::vector<float>(11)}, 512),
                    std::invalid_argument);
    sim::conv::PartitionedConvolver c;
    c.prepare(2, 2, 64, 256, 3);
    CHECK_THROWS_AS(c.setIrSet(set), std::invalid_argument); // 4 partitions > 3
}

// Acceptance (phase-06): output = sim::convolve (Phase 02 direct / double FFT reference) delayed by
// P, within -120 dB residual/signal energy, for random IRs of lengths 1, P-1, P, P+1, 48 000 and
// 144 000 and random inputs, at host blocks 1, 37, 64, 512, 2048 and random sizes.
TEST_CASE("PartitionedConvolver equals the reference convolution delayed by P (-120 dB)", "[conv]")
{
    const int p = GENERATE(128, 256, 512);
    const std::size_t len = GENERATE_COPY(std::size_t{1}, static_cast<std::size_t>(p - 1),
                                          static_cast<std::size_t>(p), static_cast<std::size_t>(p + 1),
                                          std::size_t{48000}, std::size_t{144000});
    // Input: long enough to fill every partition and to cross many block boundaries.
    const std::size_t inputLength = len < 10000 ? 9 * static_cast<std::size_t>(p) + 77 : 30000;
    const auto h = conv_test::noise(len, 1000u + len, 0.3);
    const auto x = conv_test::noise(inputLength, 2000u + len, 0.5);
    const auto ref = conv_test::reference(x, h);
    for (const int block : {1, 37, 64, 512, 2048, 0})
    {
        // Block size 1 over a 144 000-tap IR is slow in Debug and adds nothing over 37; run it on
        // the shorter IRs.
        if (block == 1 && len > 50000)
            continue;
        const auto y = runMono(x, h, p, block);
        const double db = conv_test::residualDb(y, ref, static_cast<std::size_t>(p));
        INFO("P = " << p << ", IR length " << len << ", host block " << blockName(block) << ": " << db
                    << " dB");
        CHECK(db <= -120.0);
    }
}

TEST_CASE("PartitionedConvolver 2 x 2 equals renderOffline delayed by P (-120 dB)", "[conv]")
{
    const int p = GENERATE(256, 512);
    sim::RoomIR ir;
    ir.sampleRate = 48000.0;
    ir.numEmitters = 2;
    ir.numOutputs = 2;
    for (int path = 0; path < 4; ++path)
        ir.taps.push_back(conv_test::noise(20000, 300u + static_cast<std::uint64_t>(path), 0.2));
    const sim::MultiChannel x = {conv_test::noise(25000, 41u), conv_test::noise(25000, 42u)};
    const auto ref = sim::renderOffline(ir, x, sim::ConvolutionMethod::Fft);

    sim::conv::PartitionedConvolver c;
    c.prepare(2, 2, 2048, p, sim::conv::partitionCount(ir.length(), p));
    c.setIrSet(sim::conv::IrSet::create(ir, p));
    const std::size_t total = ref[0].size() + static_cast<std::size_t>(p);
    std::vector<std::vector<float>> in(2, std::vector<float>(total, 0.0f)),
        out(2, std::vector<float>(total, 0.0f));
    for (int ch = 0; ch < 2; ++ch)
        std::copy(x[static_cast<std::size_t>(ch)].begin(), x[static_cast<std::size_t>(ch)].end(),
                  in[static_cast<std::size_t>(ch)].begin());
    std::size_t pos = 0;
    for (const int n : conv_test::blockSchedule(total, 0))
    {
        const float* ins[2] = {in[0].data() + pos, in[1].data() + pos};
        float* outs[2] = {out[0].data() + pos, out[1].data() + pos};
        c.process(ins, outs, n);
        pos += static_cast<std::size_t>(n);
    }
    for (int m = 0; m < 2; ++m)
    {
        std::vector<double> r(ref[static_cast<std::size_t>(m)].begin(),
                              ref[static_cast<std::size_t>(m)].end());
        const double db = conv_test::residualDb(out[static_cast<std::size_t>(m)], r,
                                                static_cast<std::size_t>(p));
        INFO("P = " << p << ", output " << m << ": " << db << " dB");
        CHECK(db <= -120.0);
    }
}

TEST_CASE("PartitionedConvolver latency is exactly P and in-place processing works", "[conv]")
{
    const int p = GENERATE(128, 256, 512);
    std::vector<float> h(static_cast<std::size_t>(p) * 3, 0.0f);
    h[0] = 1.0f; // delta IR
    sim::conv::PartitionedConvolver c;
    c.prepare(1, 1, 100, p, 3);
    c.setIrSet(sim::conv::IrSet::create(1, 1, {h}, p));
    CHECK(c.latencySamples() == p);
    std::vector<float> buf(static_cast<std::size_t>(4 * p), 0.0f);
    buf[5] = 1.0f;
    std::size_t pos = 0;
    for (const int n : conv_test::blockSchedule(buf.size(), 0, 3u, 100))
    {
        c.process(buf.data() + pos, buf.data() + pos, n); // in place
        pos += static_cast<std::size_t>(n);
    }
    std::size_t peak = 0;
    for (std::size_t i = 1; i < buf.size(); ++i)
        if (std::abs(buf[i]) > std::abs(buf[peak]))
            peak = i;
    CHECK(peak == static_cast<std::size_t>(p) + 5);
    CHECK(std::abs(buf[peak] - 1.0f) < 1e-6f);
}

TEST_CASE("PartitionedConvolver::process allocates nothing on the heap", "[conv][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("AllocationTracker inactive under AddressSanitizer (ASan keeps its own operator new/delete)");
    const int p = GENERATE(128, 512);
    sim::conv::PartitionedConvolver c;
    c.prepare(2, 2, 2048, p, 100);
    std::vector<std::vector<float>> taps(4, conv_test::noise(10000, 9u));
    c.setIrSet(sim::conv::IrSet::create(2, 2, taps, p));
    std::vector<float> a(2048, 0.1f), b(2048, -0.1f), o0(2048), o1(2048);
    const float* ins[2] = {a.data(), b.data()};
    float* outs[2] = {o0.data(), o1.data()};
    test_support::ScopedTracking tracking;
    for (const int n : {1, 37, 64, 512, 2048, 5, 1000})
        for (int rep = 0; rep < 8; ++rep)
            c.process(ins, outs, n);
    CHECK(tracking.allocations() == 0);
}

TEST_CASE("AllocationTracker sees operator new on the tracking thread", "[conv][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("AllocationTracker inactive under AddressSanitizer (ASan keeps its own operator new/delete)");
    test_support::ScopedTracking tracking;
    auto* v = new std::vector<int>(100);
    delete v;
    CHECK(tracking.allocations() >= 2);
    CHECK(tracking.deallocations() >= 2);
}

TEST_CASE("ScopedFlushDenormals flushes subnormal results and restores the previous mode",
          "[conv][denormals]")
{
    if (!sim::conv::ScopedFlushDenormals::isSupported())
        SKIP("no FTZ control on this target");
    volatile float tiny = 1e-30f;
    volatile float factor = 1e-10f;
    const float before = tiny * factor;
    CHECK(before != 0.0f); // 1e-40 is subnormal, kept without the guard
    {
        const sim::conv::ScopedFlushDenormals guard;
        const float inside = tiny * factor;
        CHECK(inside == 0.0f);
        volatile float subnormal = std::numeric_limits<float>::denorm_min();
        const float sum = subnormal + 0.0f; // DAZ (x86) / FZ (AArch64): subnormal inputs read as 0
        CHECK(sum == 0.0f);
    }
    const float after = tiny * factor;
    CHECK(after != 0.0f);
}

// The guard is active inside process() (phase-06 scope 5): products that would be subnormal come
// out as exact zeros. Without it the output here would be ~3e-40 (subnormal).
TEST_CASE("process() flushes subnormal results to zero", "[conv][denormals]")
{
    if (!sim::conv::ScopedFlushDenormals::isSupported())
        SKIP("no FTZ control on this target");
    const int p = 128;
    std::vector<float> h(300, 1e-12f), x(2000, 1e-30f), y(x.size(), 1.0f); // exact x*h = 3e-40
    sim::conv::PartitionedConvolver c;
    c.prepare(1, 1, 2000, p, 3);
    c.setIrSet(sim::conv::IrSet::create(1, 1, {h}, p));
    c.process(x.data(), y.data(), static_cast<int>(x.size()));
    CHECK(std::all_of(y.begin(), y.end(), [](float v) { return v == 0.0f; }));

    sim::conv::CrossfadingConvolver xc;
    xc.prepare(1, 1, 2000, p, 3, 64);
    REQUIRE(xc.requestIr(sim::conv::IrSet::create(1, 1, {h}, p)));
    std::fill(y.begin(), y.end(), 1.0f);
    xc.process(x.data(), y.data(), static_cast<int>(x.size()));
    CHECK(std::all_of(y.begin(), y.end(), [](float v) { return v == 0.0f; }));
}

TEST_CASE("PartitionedConvolver::process before prepare() returns at once", "[conv]")
{
    sim::conv::PartitionedConvolver c;
    std::vector<float> in(64, 0.5f), out(64, 7.0f);
    conv_test::runWithWatchdog([&] { c.process(in.data(), out.data(), 64); },
                               "PartitionedConvolver::process");
    CHECK(out[0] == 7.0f);
}
