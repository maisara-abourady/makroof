// Phase-07c-1b, decider D-B3 (W-a, signal ruling s1): the AX47 mid-fade check at the engine output.
//
// AX47: no value in the middle of an IR change may exceed the louder of its two endpoints. AQ4: every change
// is a 30 ms crossfade (L = lround(0.030 fs) samples); AX18: equal gain for a same-scene step (interim ->
// final), equal power for an unrelated IR (recorded only here, Vorlaender §4.3 Eq. 4.15).
//
// D-B3 harness (items 1-6):
//   1. The IrSets come from plugin::ScenePipeline (lastSubmittedIr / lastSubmittedIrSet): (a) a project load
//      (club.json restored keyless): the AX49 provisional IrSet, then the exact final after settling; (b) an
//      edit after settling (listener y + 0.5 m): the B1' interim (held E_b over the cached exact unit
//      decays), then the solved final. Each pair is fed to a single-threaded sim::RealtimeEngine: A installed
//      before processing (at once), >= 2 s of input, B submitted (EqualGain) between blocks at a test-chosen
//      block, processing past s0 + L. Each endpoint is rendered alone on a fresh engine with the same P and
//      input from sample 0 (K23: the matching crossfade component, bit for bit). Trim is not involved (engine
//      level).
//   2. W-a: windows of N_w = lround(0.001 fs) samples, non-overlapping, aligned to s0, covering
//      [s0 - 4 N_w, s0 + L + 4 N_w); per output channel E_out <= (1 + N_w/L)^2 max(E_a, E_b) (1 + 1e-5)
//      (D3-L1: holds for any correlation); windows with max(E_a, E_b) below -100 dB re full scale skipped,
//      counted and printed.
//   3. Companions: (i) |o| <= max(|a|, |b|) + 8u(|a| + |b|) per sample (D3-L2); (ii) |o - ((1 - j/L) a +
//      (j/L) b)| <= 8u(|a| + |b|), j = t - s0 in double, and o == 0 where |a| + |b| == 0 (D3-L3: a one-sample
//      offset of g is 1/L >> 8u); (iii) outside [s0, s0 + L) the output equals the endpoint rendered alone
//      exactly (K23).
//   4. Fade from silence: 3 blocks with no IR, then the first submit: o == 0 before s0, |o| <= |b| exactly
//      during the fade, per-window E <= E_b (1 + 1e-12), (ii) and (iii) with a = 0.
//   5. Equal-power fade club -> living_room: recorded, not asserted (per-window 10 log10(E_out / max) and the
//      correlation rho over the fade).
//   6. Signals: seeded pink noise and the s1 seeded speech-like stimulus (glottal pulses at f0 120 Hz +- 5 %
//      seeded jitter, three two-pole resonators at 500 / 1500 / 2500 Hz, a 4 Hz syllabic envelope, pauses
//      >= 200 ms). Board round 2 (Seats 1, 4): a pause boundary inside a fade in EACH direction, so the
//      seeded speech-like stimulus comes in two variants: "release" (a pause starts inside the fade: release
//      into the tail) and "onset" (a pause ends inside the fade: an onset into the fade). Its seeds and
//      parameters are fixed, versioned constants (kSpeechLikeV1). All deterministic (AX5): no download, no
//      committed WAV.
#include "PipelineTestUtil.h"

#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Engine.h"
#include "sim/RealtimeEngine.h"
#include "sim/Rng.h"
#include "sim/conv/CrossfadingConvolver.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <numbers>
#include <string>
#include <thread>
#include <vector>

// Exact comparisons are intended (bit-identical endpoints, exact zeros).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

using IrSetPtr = std::shared_ptr<const sim::conv::IrSet>;
using IrPtr = std::shared_ptr<const sim::RoomIR>;
using Stereo = std::array<std::vector<float>, 2>;

// D-B3 / D3-L3: the unit roundoff of float, u = 2^-24.
constexpr double kU = 1.0 / 16777216.0;
// D-B3 item 2: windows whose louder endpoint is below -100 dB re full scale (mean square) are skipped.
constexpr double kSkipEnergy = 1e-10;
// D-B3 item 2: the relative float allowance on the W-a bound.
constexpr double kEnergyEps = 1e-5;
// D-B3 item 6: at least this much input precedes the submit (both lanes carry a full history).
constexpr double kHistoryS = 2.0;

void restoreScene(plugin::ScenePipeline& p, const contract::SceneDescription& s)
{
    p.beginRestore();
    p.restore(s, module3d::parameterValuesFromScene(s));
}

void waitSettled(const plugin::ScenePipeline& p)
{
    REQUIRE(pipeline_test::waitFor([&] { return !p.settling() && p.builderIdle(); }));
}

bool bitIdentical(const sim::RoomIR& a, const sim::RoomIR& b)
{
    if (a.taps.size() != b.taps.size())
        return false;
    for (std::size_t i = 0; i < a.taps.size(); ++i)
        if (a.taps[i].size() != b.taps[i].size()
            || (!a.taps[i].empty()
                && std::memcmp(a.taps[i].data(), b.taps[i].data(), a.taps[i].size() * sizeof(float)) != 0))
            return false;
    return true;
}

// ---- signals (D-B3 item 6, ruling s1) --------------------------------------------------------------------

// Seeded pink noise: white Gaussian (PCG32) through Paul Kellet's refined pink filter (-3 dB/octave within
// about 0.05 dB from 9.2 Hz to fs/2 at 44.1 kHz), in double; scaled to an RMS of 0.1.
std::vector<float> pinkNoise(std::size_t n, std::uint64_t seed)
{
    const std::vector<float> w = conv_test::noise(n, seed, 1.0);
    std::vector<double> y(n);
    double b0 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0;
    for (std::size_t i = 0; i < n; ++i)
    {
        const double x = w[i];
        b0 = 0.99886 * b0 + x * 0.0555179;
        b1 = 0.99332 * b1 + x * 0.0750759;
        b2 = 0.96900 * b2 + x * 0.1538520;
        b3 = 0.86650 * b3 + x * 0.3104856;
        b4 = 0.55000 * b4 + x * 0.5329522;
        b5 = -0.7616 * b5 - x * 0.0168980;
        y[i] = b0 + b1 + b2 + b3 + b4 + b5 + b6 + x * 0.5362;
        b6 = x * 0.115926;
    }
    double ms = 0.0;
    for (const double v : y)
        ms += v * v;
    const double g = 0.1 / std::sqrt(ms / static_cast<double>(n));
    std::vector<float> out(n);
    for (std::size_t i = 0; i < n; ++i)
        out[i] = static_cast<float>(g * y[i]);
    return out;
}

// Ruling s1, version 1: the seeded speech-like stimulus. Its seeds and parameters are fixed constants of this
// version and are never changed: a change is a new version (kSpeechLikeV2 ...) with its own name in the
// printed records. Resonator frequencies and bandwidths are test design parameters, not claims about any
// recorded material (not ITU-T P.50).
struct SpeechLikeParams
{
    std::uint64_t seed[2]; // per input channel (PCG32 stream 11)
    double f0Hz;           // glottal pulse rate
    double jitter;         // +- relative, per period, seeded
    double formantHz[3];   // two-pole resonators, in cascade
    double bandwidthHz[3];
    double syllableHz;           // raised-cosine syllabic envelope
    double runMinS, runMaxS;     // runs between pauses
    double pauseMinS, pauseMaxS; // pauses (>= 200 ms)
    double boundaryPauseS;       // the pause whose boundary lies inside the fade
    double peak;
};
constexpr SpeechLikeParams kSpeechLikeV1{{0x5eed11ce0001ull, 0x5eed11ce0002ull},
                                         120.0,
                                         0.05,
                                         {500.0, 1500.0, 2500.0},
                                         {80.0, 100.0, 120.0},
                                         4.0,
                                         0.5,
                                         1.0,
                                         0.20,
                                         0.35,
                                         0.25,
                                         0.3};

// Which pause boundary lies inside the fade (board round 2, Seats 1, 4).
enum class Boundary
{
    Release, // a pause STARTS at `boundaryAt`: the input stops, the output releases into the tail
    Onset    // a pause ENDS at `boundaryAt`: the input starts again inside the fade
};

// The seeded speech-like stimulus (kSpeechLikeV1) for input channel `channel`: a glottal pulse train (f0 with
// a seeded +-jitter per period) through the resonator cascade, the syllabic envelope (at its peak at
// `boundaryAt`, so the boundary is an abrupt stop or start), pauses of 200-350 ms, and one pause of 250 ms
// whose start (Release) or end (Onset) is input sample `boundaryAt`. Peak scaled to 0.3.
std::vector<float> seededSpeechLike(std::size_t n, double fs, int channel, std::size_t boundaryAt,
                                    Boundary boundary)
{
    const SpeechLikeParams& v = kSpeechLikeV1;
    sim::Pcg32 rng(v.seed[channel], 11u);
    const auto uniform = [&] { return static_cast<double>(rng.next()) / 4294967296.0; }; // [0, 1)
    std::vector<double> src(n, 0.0);
    double t = 0.0;
    while (t < static_cast<double>(n))
    {
        src[static_cast<std::size_t>(t)] = 1.0;
        t += fs / (v.f0Hz * (1.0 + v.jitter * (2.0 * uniform() - 1.0)));
    }
    for (int m = 0; m < 3; ++m)
    {
        const double f = v.formantHz[m];
        const double bw = v.bandwidthHz[m];
        const double r = std::exp(-std::numbers::pi * bw / fs);
        const double a1 = 2.0 * r * std::cos(2.0 * std::numbers::pi * f / fs);
        const double a2 = -r * r;
        const double g = 1.0 - r; // rough unity-order gain at the peak
        double y1 = 0.0, y2 = 0.0;
        for (auto& x : src)
        {
            const double y = g * x + a1 * y1 + a2 * y2;
            y2 = y1;
            y1 = y;
            x = y;
        }
    }
    // Pause mask: runs of 0.5-1.0 s, pauses of 0.20-0.35 s; the boundary pause, preceded by >= 0.25 s of
    // signal and followed by a run.
    const double pauseAt = static_cast<double>(boundaryAt)
                           - (boundary == Boundary::Onset ? v.boundaryPauseS * fs : 0.0);
    std::vector<char> active(n, 1);
    const auto pause = [&](double from, double len) {
        const auto a = static_cast<std::size_t>(std::max(0.0, from));
        const auto b = std::min(n, static_cast<std::size_t>(from + len));
        for (std::size_t i = a; i < b; ++i)
            active[i] = 0;
    };
    const auto run = [&] { return (v.runMinS + (v.runMaxS - v.runMinS) * uniform()) * fs; };
    const auto pauseLen = [&] { return (v.pauseMinS + (v.pauseMaxS - v.pauseMinS) * uniform()) * fs; };
    const double limit = pauseAt - (v.pauseMaxS + v.boundaryPauseS) * fs;
    t = 0.0;
    for (;;)
    {
        t += run();
        if (t >= limit)
            break;
        const double len = pauseLen();
        pause(t, len);
        t += len;
    }
    pause(pauseAt, v.boundaryPauseS * fs);
    t = pauseAt + v.boundaryPauseS * fs;
    while (t < static_cast<double>(n))
    {
        t += run();
        const double len = pauseLen();
        pause(t, len);
        t += len;
    }
    double peak = 0.0;
    for (std::size_t i = 0; i < n; ++i)
    {
        // The syllabic envelope, at its peak at the boundary.
        const double ph = 2.0 * std::numbers::pi * v.syllableHz
                          * (static_cast<double>(i) - static_cast<double>(boundaryAt)) / fs;
        src[i] *= active[i] ? 0.5 * (1.0 + std::cos(ph)) : 0.0;
        peak = std::max(peak, std::abs(src[i]));
    }
    std::vector<float> out(n);
    for (std::size_t i = 0; i < n; ++i)
        out[i] = static_cast<float>(v.peak * src[i] / peak);
    return out;
}

// ---- the engine harness (D-B3 item 1) ---------------------------------------------------------------------

struct Render
{
    Stereo out;
    std::int64_t s0 = -1;
    std::uint64_t fades = 0;
    int submitsOk = 0;
    const sim::conv::IrSet* currentBeforeSubmit = nullptr;
    const sim::conv::IrSet* currentAtEnd = nullptr;
};

// A fresh single-threaded engine (P, fs), host blocks of P. `first` (if any) is installed before processing
// (at once, at the first boundary); `second` (if any) is submitted with `law` between blocks, before block
// `submitBlock`. Processes `n` samples of `x` (n a multiple of P).
Render render(int P, double fs, const Stereo& x, std::size_t n, const IrSetPtr& first, const IrSetPtr& second,
              std::size_t submitBlock, sim::conv::CrossfadeLaw law)
{
    Render r;
    sim::RealtimeEngine engine(P);
    engine.prepare(fs, P);
    if (first && engine.submitIrSet(first))
        ++r.submitsOk;
    for (auto& o : r.out)
        o.assign(n, 0.0f);
    const auto p = static_cast<std::size_t>(P);
    for (std::size_t blk = 0; blk * p < n; ++blk)
    {
        if (second && blk == submitBlock)
        {
            r.currentBeforeSubmit = engine.convolver().currentIr();
            if (engine.submitIrSet(second, law))
                ++r.submitsOk;
        }
        const float* const in[2] = {x[0].data() + blk * p, x[1].data() + blk * p};
        float* const out[2] = {r.out[0].data() + blk * p, r.out[1].data() + blk * p};
        engine.process(in, out, P);
    }
    r.s0 = engine.convolver().fadeStartSample();
    r.fades = engine.convolver().fadeCount();
    r.currentAtEnd = engine.convolver().currentIr();
    return r;
}

// Runs the jobs on worker threads (each its own engine, single-threaded) and joins them. No Catch2 macro is
// used on the workers.
void runParallel(std::vector<std::function<void()>>& jobs)
{
    std::vector<std::thread> threads;
    threads.reserve(jobs.size());
    for (auto& j : jobs)
        threads.emplace_back(j);
    for (auto& t : threads)
        t.join();
}

// ---- the checks (D-B3 items 2-4) --------------------------------------------------------------------------

struct CheckResult
{
    double worstRatioDb = -1e300;  // max over checked windows and channels of 10 log10(E_out / max(E_a, E_b))
    double worstInFadeDb = -1e300; // the same over the windows that overlap [s0, s0 + L) only
    int windows = 0;
    int skipped = 0;
    std::size_t windowFails = 0, perSampleFails = 0, reconFails = 0, zeroFails = 0, outsideFails = 0;
    std::size_t silenceFails = 0;
};

double meanSquare(const std::vector<float>& v, std::size_t from, std::size_t len)
{
    double e = 0.0;
    for (std::size_t i = from; i < from + len; ++i)
        e += static_cast<double>(v[i]) * static_cast<double>(v[i]);
    return e / static_cast<double>(len);
}

// o: the faded render; a, b: the endpoints alone (a == nullptr: fade from silence, a = 0).
CheckResult check(const Stereo& o, const Stereo* a, const Stereo& b, std::int64_t s0, int L, int Nw)
{
    CheckResult r;
    const auto n = o[0].size();
    const auto us0 = static_cast<std::size_t>(s0);
    const auto uL = static_cast<std::size_t>(L);
    const auto uNw = static_cast<std::size_t>(Nw);
    const bool fromSilence = a == nullptr;
    // W-a tolerance from the sample counts (D3-L1); the fade from silence: factor 1 (D-B3 item 4).
    const double dRamp = static_cast<double>(Nw) / static_cast<double>(L);
    const double bound = fromSilence ? 1.0 + 1e-12 : (1.0 + dRamp) * (1.0 + dRamp) * (1.0 + kEnergyEps);
    const auto av = [&](int c, std::size_t t) { return fromSilence ? 0.0f : (*a)[c][t]; };
    for (int c = 0; c < 2; ++c)
    {
        // Windows aligned to s0, covering [s0 - 4 N_w, s0 + L + 4 N_w).
        for (std::size_t w = us0 - 4 * uNw; w < us0 + uL + 4 * uNw; w += uNw)
        {
            const double eo = meanSquare(o[c], w, uNw);
            const double ea = fromSilence ? 0.0 : meanSquare((*a)[c], w, uNw);
            const double eb = meanSquare(b[c], w, uNw);
            const double m = std::max(ea, eb);
            if (m < kSkipEnergy)
            {
                ++r.skipped;
                continue;
            }
            ++r.windows;
            if (eo > bound * m)
                ++r.windowFails;
            if (eo > 0.0)
            {
                const double db = 10.0 * std::log10(eo / m);
                r.worstRatioDb = std::max(r.worstRatioDb, db);
                if (w + uNw > us0 && w < us0 + uL)
                    r.worstInFadeDb = std::max(r.worstInFadeDb, db);
            }
        }
        for (std::size_t t = 0; t < n; ++t)
        {
            const double ot = o[c][t];
            const double at = av(c, t);
            const double bt = b[c][t];
            const double abs = std::abs(at) + std::abs(bt);
            if (t < us0 || t >= us0 + uL)
            {
                // (iii) outside the fade: the endpoint rendered alone, exactly (K23). Compared by value (==),
                // not memcmp: in the block where the fade ends the engine computes o = 0 a + 1 b (gOut[L] =
                // 0, gIn[L] = 1), which gives +0 where b = -0 (and 0 a may be -0); == treats +-0 as equal and
                // still catches any other difference (no NaN can occur: finite IRs and inputs, AX32).
                if (o[c][t] != (t < us0 ? av(c, t) : b[c][t]))
                    ++r.outsideFails;
                if (fromSilence && t < us0 && o[c][t] != 0.0f)
                    ++r.silenceFails;
                continue;
            }
            // (i) per sample (D3-L2); from silence |o| <= |b| with no epsilon (D-B3 item 4).
            if (fromSilence ? std::abs(o[c][t]) > std::abs(b[c][t])
                            : std::abs(ot) > std::max(std::abs(at), std::abs(bt)) + 8.0 * kU * abs)
                ++r.perSampleFails;
            // (ii) reconstruction, g computed independently in double (D3-L3).
            const double g = static_cast<double>(t - us0) / static_cast<double>(L);
            const double ref = (1.0 - g) * at + g * bt;
            if (std::abs(ot - ref) > 8.0 * kU * abs)
                ++r.reconFails;
            if (abs == 0.0 && ot != 0.0)
                ++r.zeroFails;
        }
    }
    return r;
}

// D-B3 item 5: the equal-power record (no assertion): per-window 10 log10(E_out / max) and rho over the fade.
struct PowerRecord
{
    double maxExcessDb = -1e300;
    double rho[2] = {0.0, 0.0};
};

PowerRecord recordPower(const Stereo& o, const Stereo& a, const Stereo& b, std::int64_t s0, int L, int Nw)
{
    PowerRecord r;
    const auto us0 = static_cast<std::size_t>(s0);
    const auto uL = static_cast<std::size_t>(L);
    const auto uNw = static_cast<std::size_t>(Nw);
    for (int c = 0; c < 2; ++c)
    {
        for (std::size_t w = us0 - 4 * uNw; w < us0 + uL + 4 * uNw; w += uNw)
        {
            const double m = std::max(meanSquare(a[c], w, uNw), meanSquare(b[c], w, uNw));
            const double eo = meanSquare(o[c], w, uNw);
            if (m >= kSkipEnergy && eo > 0.0)
                r.maxExcessDb = std::max(r.maxExcessDb, 10.0 * std::log10(eo / m));
        }
        double ab = 0.0, aa = 0.0, bb = 0.0;
        for (std::size_t t = us0; t < us0 + uL; ++t)
        {
            ab += static_cast<double>(a[c][t]) * b[c][t];
            aa += static_cast<double>(a[c][t]) * a[c][t];
            bb += static_cast<double>(b[c][t]) * b[c][t];
        }
        r.rho[c] = aa > 0.0 && bb > 0.0 ? ab / std::sqrt(aa * bb) : 0.0;
    }
    return r;
}

// ---- the IrSet pairs from the pipeline (D-B3 item 1) ------------------------------------------------------

struct Pairs
{
    IrPtr loadA, loadB, editA, editB, other;
    IrSetPtr loadASet, loadBSet, editASet, editBSet; // the pipeline's own IrSets (P = 512)
};

Pairs buildPairs(double fs)
{
    Pairs out;
    const auto club = pipeline_test::loadScene("club.json");
    plugin::ScenePipeline p;
    p.prepare(fs, 512, false);
    waitSettled(p);

    // (a) A project load: club.json restored keyless (AX48 FM-3'): the AX49 provisional, then the exact
    // final.
    const auto s0 = p.stats();
    restoreScene(p, club);
    REQUIRE(p.stats().keylessLoads == s0.keylessLoads + 1);
    REQUIRE(p.stats().provisionalSubmits == s0.provisionalSubmits + 1);
    out.loadA = p.lastSubmittedIr();
    out.loadASet = p.lastSubmittedIrSet();
    REQUIRE(out.loadA != nullptr);
    waitSettled(p);
    const auto s1 = p.stats();
    out.loadB = p.lastSubmittedIr();
    out.loadBSet = p.lastSubmittedIrSet();
    if (s1.finalSubmits != s0.finalSubmits + 1 || out.loadB == out.loadA
        || bitIdentical(*out.loadA, *out.loadB))
    {
        std::printf("ax47-midfade %6.0f Hz load pair: no fade (step 0)\n", fs);
        FAIL("load pair: no fade (step 0): never counts as a pass (D-B3 item 1)");
    }
    REQUIRE(bitIdentical(*out.loadB, plugin::ScenePipeline::buildIr(p.currentScene(), fs)));

    // (b) An edit after settling: listener y + 0.5 m. The builder submits the B1' interim (the held E_b over
    // the cached exact unit decays: condition 4) before the solve, then the solved final. The builder is
    // parked inside the gate (Solve stage) to read the interim.
    std::atomic<bool> release{false}, entered{false};
    p.setStageHook([&](plugin::ScenePipeline::BuildStage stage) {
        if (stage != plugin::ScenePipeline::BuildStage::Solve || entered.exchange(true))
            return;
        while (!release.load())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    });
    p.setParameter(module3d::kListenerY, p.parameter(module3d::kListenerY) + 0.5f);
    REQUIRE(pipeline_test::waitFor([&] { return entered.load(); }));
    const auto s2 = p.stats();
    REQUIRE(s2.interimSubmits == s1.interimSubmits + 1);
    out.editA = p.lastSubmittedIr();
    out.editASet = p.lastSubmittedIrSet();
    release.store(true);
    waitSettled(p);
    p.setStageHook({});
    const auto s3 = p.stats();
    out.editB = p.lastSubmittedIr();
    out.editBSet = p.lastSubmittedIrSet();
    if (s3.finalSubmits != s2.finalSubmits + 1 || out.editB == out.editA
        || bitIdentical(*out.editA, *out.editB))
    {
        std::printf("ax47-midfade %6.0f Hz edit pair: no fade (step 0)\n", fs);
        FAIL("edit pair: no fade (step 0): never counts as a pass (D-B3 item 1)");
    }
    REQUIRE(s3.heldSteps == s2.heldSteps + 1); // the interim was the B1' held level (recorded, AX47 scope)
    std::printf("ax47-midfade %6.0f Hz pairs: load = AX49 provisional (%zu samples) -> exact final (%zu); "
                "edit = listener y +0.5 m: B1' interim (held E_b, cached unit decays, %zu) -> solved final "
                "(%zu), pipeline step %.3f dB\n",
                fs, out.loadA->length(), out.loadB->length(), out.editA->length(), out.editB->length(),
                s3.lastStepDb);

    // D-B3 item 5: another scene's IR (living_room) for the equal-power record, built as the pipeline builds.
    out.other = std::make_shared<const sim::RoomIR>(
        plugin::ScenePipeline::buildIr(pipeline_test::loadScene("living_room.json"), fs));
    return out;
}

const char* lawName(sim::conv::CrossfadeLaw law)
{
    return law == sim::conv::CrossfadeLaw::EqualGain ? "equal-gain" : "equal-power";
}

} // namespace

TEST_CASE("AX47 / D-B3: no mid-fade window exceeds the louder endpoint (W-a, 1 ms, per channel); companions "
          "(i)-(iii); fade from silence; equal-power recorded",
          "[ax47-midfade]")
{
    const auto started = std::chrono::steady_clock::now();
    const auto law = sim::conv::CrossfadeLaw::EqualGain; // AX18: a same-scene step is equal-gain
    for (const double fs : {48000.0, 96000.0})
    {
        const auto tBuild = std::chrono::steady_clock::now();
        const Pairs pairs = buildPairs(fs);
        std::printf("ax47-midfade %6.0f Hz pipeline builds %.1f s\n", fs,
                    std::chrono::duration<double>(std::chrono::steady_clock::now() - tBuild).count());
        for (const int P : {128, 512})
        {
            const int L = static_cast<int>(std::lround(sim::RealtimeEngine::kCrossfadeS * fs)); // AQ4
            const int Nw = static_cast<int>(std::lround(0.001 * fs));                           // W-a
            const auto p = static_cast<std::size_t>(P);
            const auto makeSet = [&](const IrPtr& ir, const IrSetPtr& pipelineSet) {
                // P = 512: the pipeline's own IrSet; P = 128: the same RoomIR partitioned for this engine.
                return P == plugin::ScenePipeline::kPartitionSize ? pipelineSet
                                                                  : sim::conv::IrSet::create(*ir, P);
            };
            const IrSetPtr loadA = makeSet(pairs.loadA, pairs.loadASet);
            const IrSetPtr loadB = makeSet(pairs.loadB, pairs.loadBSet);
            const IrSetPtr editA = makeSet(pairs.editA, pairs.editASet);
            const IrSetPtr editB = makeSet(pairs.editB, pairs.editBSet);
            const IrSetPtr other = sim::conv::IrSet::create(*pairs.other, P);
            REQUIRE(loadA->partitionSize() == P);

            // K14: submitted after r = k P input samples (>= 2 s), the fade starts at s0 = (k + 2) P.
            const std::size_t k = (static_cast<std::size_t>(std::ceil(kHistoryS * fs)) + p - 1) / p;
            const auto s0Expected = static_cast<std::int64_t>((k + 2) * p);
            const std::size_t end = static_cast<std::size_t>(s0Expected) + static_cast<std::size_t>(L)
                                    + 4 * static_cast<std::size_t>(Nw) + p;
            const std::size_t n = (end + p - 1) / p * p;
            // The seeded speech-like pause boundaries inside the fade: input sample s0 - P + j reaches the
            // output at s0 + j (latency P). Release: a pause starts at j = L/4; onset: a pause ends at j =
            // 3L/4.
            const auto inFade = [&](int j) {
                return static_cast<std::size_t>(s0Expected) - p + static_cast<std::size_t>(j);
            };
            const std::uint64_t seedBase = static_cast<std::uint64_t>(fs) + static_cast<std::uint64_t>(P);
            constexpr int kSignals = 3;
            const Stereo signals[kSignals] = {
                {pinkNoise(n, seedBase + 1), pinkNoise(n, seedBase + 2)},
                {seededSpeechLike(n, fs, 0, inFade(L / 4), Boundary::Release),
                 seededSpeechLike(n, fs, 1, inFade(L / 4), Boundary::Release)},
                {seededSpeechLike(n, fs, 0, inFade(3 * L / 4), Boundary::Onset),
                 seededSpeechLike(n, fs, 1, inFade(3 * L / 4), Boundary::Onset)}};
            const char* signalNames[kSignals] = {"pink", "seeded-speech-like-v1 release",
                                                 "seeded-speech-like-v1 onset"};

            for (int si = 0; si < kSignals; ++si)
            {
                const Stereo& x = signals[si];
                // Endpoints alone (installed at once) and the faded renders, each on its own fresh engine.
                Render aLoad, bLoad, aEdit, bEdit, bOther, mLoad, mEdit, mPower, mSilence, bSilence;
                std::vector<std::function<void()>> jobs{
                    [&] { aLoad = render(P, fs, x, n, loadA, nullptr, 0, law); },
                    [&] { bLoad = render(P, fs, x, n, loadB, nullptr, 0, law); },
                    [&] { aEdit = render(P, fs, x, n, editA, nullptr, 0, law); },
                    [&] { bEdit = render(P, fs, x, n, editB, nullptr, 0, law); },
                    [&] { mLoad = render(P, fs, x, n, loadA, loadB, k, law); },
                    [&] { mEdit = render(P, fs, x, n, editA, editB, k, law); },
                };
                // D-B3 item 5: club (exact final) -> living_room, equal power (AX18): recorded only, at P =
                // 512 only (Debug runtime: the record needs no P = 128 point; nothing asserted is dropped).
                const bool recordPowerHere = P == plugin::ScenePipeline::kPartitionSize;
                if (recordPowerHere)
                {
                    jobs.emplace_back([&] { bOther = render(P, fs, x, n, other, nullptr, 0, law); });
                    jobs.emplace_back([&] {
                        mPower = render(P, fs, x, n, loadB, other, k, sim::conv::CrossfadeLaw::EqualPower);
                    });
                }
                // D-B3 item 4: fade from silence, 3 blocks with no IR, then the first submit (K11).
                const std::size_t nSilence =
                    (7 * p + static_cast<std::size_t>(L) + 4 * static_cast<std::size_t>(Nw)) / p * p + p;
                const Stereo xs = {
                    std::vector<float>(x[0].begin(), x[0].begin() + static_cast<std::ptrdiff_t>(nSilence)),
                    std::vector<float>(x[1].begin(), x[1].begin() + static_cast<std::ptrdiff_t>(nSilence))};
                jobs.emplace_back([&] { mSilence = render(P, fs, xs, nSilence, nullptr, loadB, 3, law); });
                jobs.emplace_back([&] { bSilence = render(P, fs, xs, nSilence, loadB, nullptr, 0, law); });
                runParallel(jobs);

                struct Case
                {
                    const char* name;
                    const Render& m;
                    const Render& a;
                    const Render& b;
                    const IrSetPtr& aSet;
                    const IrSetPtr& bSet;
                };
                for (const Case& cs : {Case{"load provisional->final", mLoad, aLoad, bLoad, loadA, loadB},
                                       Case{"edit interim->final", mEdit, aEdit, bEdit, editA, editB}})
                {
                    CAPTURE(fs, P, signalNames[si], cs.name);
                    // A fade happened, exactly one, of this pair, where K14 puts it.
                    if (cs.m.fades == 0)
                        std::printf("ax47-midfade %s: no fade (step 0)\n", cs.name);
                    REQUIRE(cs.m.submitsOk == 2);
                    REQUIRE(cs.m.fades == 1);
                    REQUIRE(cs.m.s0 == s0Expected);
                    REQUIRE(cs.m.currentBeforeSubmit == cs.aSet.get());
                    REQUIRE(cs.m.currentAtEnd == cs.bSet.get());
                    REQUIRE(cs.a.fades == 0);
                    REQUIRE(cs.b.fades == 0);
                    const auto r = check(cs.m.out, &cs.a.out, cs.b.out, cs.m.s0, L, Nw);
                    std::printf(
                        "ax47-midfade %6.0f Hz P=%3d %-29s %-24s %s: worst window %+.4f dB (in the fade "
                        "%+.4f dB; bound %+.4f dB), %d windows checked, %d skipped (< -100 dB)\n",
                        fs, P, signalNames[si], cs.name, lawName(law), r.worstRatioDb, r.worstInFadeDb,
                        20.0 * std::log10(1.0 + static_cast<double>(Nw) / L), r.windows, r.skipped);
                    CHECK(r.windows > 0);
                    CHECK(r.windowFails == 0);    // W-a (D3-L1)
                    CHECK(r.perSampleFails == 0); // (i) (D3-L2)
                    CHECK(r.reconFails == 0);     // (ii) (D3-L3)
                    CHECK(r.zeroFails == 0);      // (ii) o == 0 where |a| + |b| == 0
                    CHECK(r.outsideFails == 0);   // (iii) (K23)
                }
                {
                    CAPTURE(fs, P, signalNames[si]);
                    INFO("fade from silence");
                    REQUIRE(mSilence.submitsOk == 1);
                    REQUIRE(mSilence.fades == 1);
                    REQUIRE(mSilence.s0 == static_cast<std::int64_t>(5 * p)); // k = 3: s0 = (3 + 2) P
                    REQUIRE(mSilence.currentBeforeSubmit == nullptr);
                    REQUIRE(mSilence.currentAtEnd == loadB.get());
                    const auto r = check(mSilence.out, nullptr, bSilence.out, mSilence.s0, L, Nw);
                    std::printf(
                        "ax47-midfade %6.0f Hz P=%3d %-29s %-24s %s: worst window %+.4f dB (in the fade "
                        "%+.4f dB; bound 1 + 1e-12), %d windows checked, %d skipped (< -100 dB)\n",
                        fs, P, signalNames[si], "from silence", lawName(law), r.worstRatioDb, r.worstInFadeDb,
                        r.windows, r.skipped);
                    CHECK(r.windows > 0);
                    CHECK(r.silenceFails == 0);   // o == 0 before s0
                    CHECK(r.windowFails == 0);    // E <= E_b (1 + 1e-12)
                    CHECK(r.perSampleFails == 0); // |o| <= |b|, no epsilon
                    CHECK(r.reconFails == 0);     // (ii) with a = 0
                    CHECK(r.zeroFails == 0);
                    CHECK(r.outsideFails == 0); // (iii) with a = 0
                }
                if (recordPowerHere)
                {
                    // Recorded, not asserted (D-B3 item 5; Eq. 4.15: the cross term 2 |p1||p2| cos).
                    REQUIRE(mPower.fades == 1);
                    const auto rec = recordPower(mPower.out, bLoad.out, bOther.out, mPower.s0, L, Nw);
                    std::printf("ax47-midfade %6.0f Hz P=%3d %-29s %-24s %s: max window 10log10(E_out/max) "
                                "%+.4f dB, rho over the fade %.3f / %.3f (record only)\n",
                                fs, P, signalNames[si], "club -> living_room", "equal-power", rec.maxExcessDb,
                                rec.rho[0], rec.rho[1]);
                }
            }
        }
    }
    std::printf("ax47-midfade total %.1f s\n",
                std::chrono::duration<double>(std::chrono::steady_clock::now() - started).count());
}
