// Phase-07c-1: the diffuse solve and the unit-decay synthesis off the synchronous paths.
//   AX49 (D-C9, condition 9): the provisional tail (timing, the >= 18.7 dB decay, L_p >= L, normalisation,
//     AX47 (b) against the exact tail, the parallel synthesis bit-identical to the serial one).
//   Condition 2 / AX48 (D-C2, D-C3): which restores and prepares solve synchronously (keyless loads with no
//   IrSet
//     current only, FM-3'); keyed loads at the saved E_b; every key part, Pi included; output mode, HRTF and
//     seed never re-solve.
//   Condition 4: the ISM update before the solve, one step per solve, never mid-drag, "settling".
//   Condition 5 / AX47 (a): the interim level is never silence and never the AX16 level (layouts 4/5, an
//     absorbing-floor cube, BRAS CR3).
//   Condition 6: offline waits for the final and never uses an interim; the render-log line.
#include "ContractFixtures.h"
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "contract/Json.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Engine.h"
#include "sim/Fft.h"
#include "sim/ism/BandRenderer.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <thread>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

constexpr double kRate = 48000.0;
// D1 / O8 (phase-07c-1 session 2; decider file 33): EDT is asserted only where the exact band IR's direct
// fraction is below this (Kuttruff Eq. 5.44: w_d = w_r at r = r_c, applied to the measured field;
// section 8.4).
constexpr double kDirectFractionMax = 0.5;

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

sim::BuildOptions omni(double fs)
{
    sim::BuildOptions o;
    o.sampleRate = fs;
    o.kind = sim::BuildOptions::Kind::Omni;
    return o;
}

void restoreScene(plugin::ScenePipeline& p, const contract::SceneDescription& s,
                  const std::optional<plugin::SavedDiffuse>& saved = std::nullopt)
{
    p.beginRestore();
    p.restore(s, module3d::parameterValuesFromScene(s), saved);
}

void waitSettled(const plugin::ScenePipeline& p)
{
    REQUIRE(pipeline_test::waitFor([&] { return !p.settling() && p.builderIdle(); }));
}

// The A4 set (phase-07c-1 A4; Seat 9): Kuttruff Table 5.2 layouts 4 (absorbing floor) and 5 (absorbing wall)
// at s = 1, an absorbing-floor cube, and BRAS CR3 ls1_mp2 (the AX16 -1.18 dB case).
struct A4Scene
{
    const char* name;
    contract::SceneDescription scene;
    bool ax16KnownOff; // AX16 is known to be > 1 dB off (AX16 row, phase 05e X-b; C16 (g))
};

std::vector<A4Scene> a4Set()
{
    const auto layout = [](int which) {
        std::array<contract::BandArray, 6> alpha{};
        for (auto& a : alpha)
            a.fill(0.01);
        alpha[which == 4 ? 4 : 0].fill(1.0); // layout 4: absorbing floor; layout 5: absorbing xMin wall
        return alpha;
    };
    std::array<double, 6> s1{};
    s1.fill(1.0);
    const contract::Vec3 D{20.0, 30.0, 10.0};
    const contract::Vec3 S0{7.0, 20.0, 2.0}, S1{13.0, 20.0, 2.0}, R0{10.0, 8.0, 1.7};
    std::vector<A4Scene> set;
    set.push_back({"layout4_s1", diffuse_test::scene(D, layout(4), s1, R0, {S0, S1}), true});
    set.push_back({"layout5_s1", diffuse_test::scene(D, layout(5), s1, R0, {S0, S1}), false});
    {
        std::array<contract::BandArray, 6> alpha{};
        for (auto& a : alpha)
            a.fill(0.05);
        alpha[4].fill(1.0); // the floor (SurfaceId order: xMin, xMax, yMin, yMax, floor, ceiling)
        std::array<double, 6> s{};
        s.fill(0.3);
        set.push_back({"absorbing_floor_cube20",
                       diffuse_test::scene({20.0, 20.0, 20.0}, alpha, s, {10.0, 6.0, 1.7},
                                           {{8.0, 14.0, 2.0}, {12.0, 14.0, 2.0}}),
                       false});
    }
    {
        auto parsed = contract::fromJson(
            contract_fixtures::read(contract_fixtures::scenesDir() / "validation" / "bras_cr3_ls1_mp2.json"));
        REQUIRE(parsed.ok());
        set.push_back(
            {"bras_cr3_ls1_mp2", *parsed.scene, true}); // AX16 row: −1.18 dB at 2 kHz (review minor 4)
    }
    return set;
}

// The per-band energy of emitter e's tail as built, over emission times [t0, t1): A_b^2 sum w_tail^2 u_b^2
// over the IR samples whose emission time lies there (the band split of the construction itself).
contract::BandArray tailBandEnergy(const std::vector<sim::tail::UnitDecay>& units,
                                   const sim::HybridDiagnostics& d, std::size_t e, double t0, double t1)
{
    contract::BandArray sum{};
    const auto& u = units[e];
    const double fs = d.sampleRate;
    const double mix = d.emitters[e].match.mixing.mixS;
    const auto offset = static_cast<std::size_t>(std::max(0.0, std::round(d.alignmentShiftS * fs)));
    // Only the samples whose emission time lies in [t0, t1), the crossfade weight once per sample.
    const auto first = std::max(offset, static_cast<std::size_t>(std::max(0.0, std::ceil(t0 * fs))));
    const auto last = std::min(u.length(), t1 * fs < static_cast<double>(u.length())
                                               ? static_cast<std::size_t>(std::max(0.0, std::ceil(t1 * fs)))
                                               : u.length());
    for (std::size_t j = first; j < last; ++j)
    {
        const double w =
            sim::tail::crossfade(static_cast<double>(j - offset) / fs + d.alignmentShiftS, mix).tail;
        const double w2 = w * w;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            sum[b] += w2 * u.bands[b][j] * u.bands[b][j];
    }
    contract::BandArray out{};
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const double a = d.emitters[e].match.bandsAmplitude[b];
        out[b] = a * a * sum[b];
    }
    return out;
}

// The first n samples of two signals split into the eight bands (circular FFT convolution with the centred
// band filters on the prefix alone: outputs below n - halfLength are exact). One forward transform per signal
// and per band filter, one inverse per band and signal (D1 prefix check; Windows Debug time).
std::array<std::array<std::vector<double>, contract::kNumOctaveBands>, 2> prefixBands(
    const std::vector<float>& x0, const std::vector<float>& x1, std::size_t n,
    const sim::ism::OctaveFilterbank& fb, std::size_t bFrom = 0, std::size_t bTo = contract::kNumOctaveBands)
{
    // The band filters are real, so the two signals share one transform: x0 + i x1 in, h * x0 + i h * x1 out.
    std::array<std::array<std::vector<double>, contract::kNumOctaveBands>, 2> out;
    const std::size_t len = 2 * fb.maxHalfLength() + 1;
    const std::size_t m = sim::Fft::nextPowerOfTwo(n + len);
    const sim::Fft fft(m);
    std::vector<std::complex<double>> X(m, {0.0, 0.0});
    for (std::size_t i = 0; i < n; ++i)
        X[i] = {i < x0.size() ? static_cast<double>(x0[i]) : 0.0,
                i < x1.size() ? static_cast<double>(x1[i]) : 0.0};
    fft.forward(X);
    std::vector<std::complex<double>> H(m), Y(m);
    for (std::size_t b = bFrom; b < bTo; ++b)
    {
        const auto h = fb.bandImpulseResponse(b);
        const std::size_t half = (h.size() - 1) / 2;
        std::fill(H.begin(), H.end(), std::complex<double>(0.0, 0.0));
        for (std::size_t i = 0; i < h.size(); ++i)
            H[(i + m - half) % m] = h[i];
        fft.forward(H);
        for (std::size_t i = 0; i < m; ++i)
            Y[i] = X[i] * H[i];
        fft.inverse(Y);
        out[0][b].resize(n);
        out[1][b].resize(n);
        const double scale = 1.0 / static_cast<double>(m);
        for (std::size_t i = 0; i < n; ++i)
        {
            out[0][b][i] = Y[i].real() * scale;
            out[1][b][i] = Y[i].imag() * scale;
        }
    }
    return out;
}

// EDT (s) of a band signal as tools/acoustics/metrics.py takes it (ISO 3382-1 A.2.1): the Schroeder curve
// from the onset (the first sample within 20 dB of the peak), normalised to 0 dB there; a least-squares line
// through every sample of it from 0 dB to the first time it reaches -10 dB; EDT = -60 / slope.
double edtS(const std::vector<double>& y, double fs)
{
    double peak = 0.0;
    for (const double v : y)
        peak = std::max(peak, v * v);
    std::size_t onset = 0;
    while (onset < y.size() && y[onset] * y[onset] < 0.01 * peak)
        ++onset;
    std::vector<double> sch(y.size() + 1, 0.0);
    for (std::size_t i = y.size(); i-- > onset;)
        sch[i] = sch[i + 1] + y[i] * y[i];
    const double total = sch[onset];
    double sx = 0.0, sy = 0.0, sxx = 0.0, sxy = 0.0;
    std::size_t n = 0;
    for (std::size_t i = onset; i < y.size(); ++i)
    {
        const double l = 10.0 * std::log10(sch[i] / total);
        const double x = static_cast<double>(i - onset) / fs;
        sx += x;
        sy += l;
        sxx += x * x;
        sxy += x * l;
        ++n;
        if (l <= -10.0)
            break;
    }
    const double nn = static_cast<double>(n);
    const double slope = (nn * sxy - sx * sy) / (nn * sxx - sx * sx);
    return slope < 0.0 ? -60.0 / slope : 0.0;
}

double tailEnergy(const sim::RoomIR& ir, double fromS)
{
    double e = 0.0;
    const auto& t = ir.taps[0];
    for (std::size_t i = static_cast<std::size_t>(fromS * ir.sampleRate); i < t.size(); ++i)
        e += static_cast<double>(t[i]) * t[i];
    return e;
}

} // namespace

// ---------------------------------------------------------------------------------------------------------------
// AX49: the provisional tail itself (sim)
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE(
    "AX49: L_f = t_mix,e,max + 0.312 T60_max gives >= 18.7 dB of decay in every band; L_p = L_f + 0.1 s",
    "[interim][ax49]")
{
    for (const auto& a4 : a4Set())
        for (const double fs : {48000.0, 96000.0})
        {
            CAPTURE(a4.name, fs);
            auto build = sim::StagedBuild::plan(a4.scene, omni(fs));
            const auto t = build.provisionalTiming();
            REQUIRE(t.t60MaxS > 0.0);
            REQUIRE(t.fadeStartS == t.mixMaxS + sim::kProvisionalT60Fraction * t.t60MaxS);
            REQUIRE(t.endS == t.fadeStartS + sim::kProvisionalFadeS);
            REQUIRE(t.provisional == (t.endS < t.exactS));
            sim::HybridDiagnostics d;
            build.useDiffuseLevel(sim::EmitterBands{});
            (void)build.assemble(&d);
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            {
                // The energy decay from t_mix,e,max to L_f along band b's own T60 (Vorlaender Eq. 6.4).
                const double decayDb = 60.0 * (t.fadeStartS - t.mixMaxS) / d.decay.bandsT60S[b];
                CAPTURE(b, decayDb);
                REQUIRE(decayDb >= 18.7);
            }
            std::printf(
                "07c1-records ax49 timing %-22s %6.0f Hz: t_mix,max %.3f s, T60_max %.2f s, L_f %.3f s, "
                "L_p %.3f s, L %.3f s, provisional %s\n",
                a4.name, fs, t.mixMaxS, t.t60MaxS, t.fadeStartS, t.endS, t.exactS,
                t.provisional ? "yes" : "no (exact tail in its place)");
        }
}

TEST_CASE("AX49: where L_p >= L the provisional build IS the exact build (no handover)", "[interim][ax49]")
{
    // A 30 m cube at alpha 0.02: T60 long enough that L (1.5 T60_max, capped at 12 s) is within L_p (the
    // property the 100 m low-alpha gated cube has; that scene is exercised in the Release records).
    std::array<contract::BandArray, 6> alpha{};
    for (auto& a : alpha)
        a.fill(0.02);
    std::array<double, 6> s{};
    s.fill(0.3);
    auto scene = diffuse_test::scene({30.0, 30.0, 30.0}, alpha, s, {15.0, 9.0, 1.7},
                                     {{13.0, 21.0, 2.0}, {17.0, 21.0, 2.0}});
    auto a = sim::StagedBuild::plan(scene, omni(kRate));
    const auto t = a.provisionalTiming();
    CAPTURE(t.fadeStartS, t.endS, t.exactS);
    if (t.provisional)
    {
        // Lower alpha until L_p >= L (air absorption bounds T60 at high frequencies, the 12 s cap bounds L).
        for (auto& f : alpha)
            f.fill(0.005);
        scene = diffuse_test::scene({30.0, 30.0, 30.0}, alpha, s, {15.0, 9.0, 1.7},
                                    {{13.0, 21.0, 2.0}, {17.0, 21.0, 2.0}});
        a = sim::StagedBuild::plan(scene, omni(kRate));
    }
    REQUIRE_FALSE(a.provisionalTiming().provisional);
    auto b = sim::StagedBuild::plan(scene, omni(kRate));
    a.useDiffuseLevel(sim::EmitterBands{});
    b.useDiffuseLevel(sim::EmitterBands{});
    REQUIRE(bitIdentical(a.assembleProvisional(), b.assemble()));
}

TEST_CASE("AX49: the parallel per-emitter synthesis is bit-identical to the serial build",
          "[interim][ax49][staged]")
{
    for (const char* name : {"club.json", "living_room.json"})
    {
        CAPTURE(name);
        const auto scene = pipeline_test::loadScene(name);
        auto serial = omni(kRate);
        auto parallel = omni(kRate);
        parallel.parallelEmitterSynthesis = true;
        REQUIRE(bitIdentical(sim::buildRoomIR(scene, serial), sim::buildRoomIR(scene, parallel)));
        auto a = sim::StagedBuild::plan(scene, serial);
        auto b = sim::StagedBuild::plan(scene, parallel);
        a.useDiffuseLevel(sim::EmitterBands{});
        b.useDiffuseLevel(sim::EmitterBands{});
        REQUIRE(bitIdentical(a.assembleProvisional(), b.assembleProvisional()));
    }
}

TEST_CASE("AX47 (b) / AX49: provisional against exact on the A4 set: steps <= 1 dB, prefix identity, EDT "
          "within 5 % where d < 0.5",
          "[interim][ax49][ax47]")
{
    double worstTail = 0.0, worstCommon = 0.0, worstEdt = 0.0, worstPrefix = -300.0;
    int edtCases = 0, outOfDomain = 0;
    std::array<int, contract::kNumOctaveBands> evaluated{};
    for (const auto& a4 : a4Set())
    {
        // One solve per scene (the level is rate- and seed-independent: AX40); reused bit for bit below.
        auto solved = sim::StagedBuild::plan(a4.scene, omni(kRate));
        solved.solve();
        const auto level = solved.diffuseLevel();
        REQUIRE(level.has_value());
        for (const double fs : {48000.0, 96000.0})
            for (const std::uint32_t seed : {1u, 2u, 3u})
            {
                if (fs > 50000.0 && seed > 2)
                    continue; // 96 kHz on two seeds (Debug time)
                CAPTURE(a4.name, fs, seed);
                auto sc = a4.scene;
                sc.render.tailSeed = seed;
                // The two emitters synthesised in parallel (bit-identical to serial: test "AX49: the parallel
                // …").
                auto opts = omni(fs);
                opts.parallelEmitterSynthesis = true;
                // One plan serves both builds (assemble() and assembleProvisional() read the same plan; the
                // exact unit decays are taken before the provisional replaces them).
                auto build = sim::StagedBuild::plan(sc, opts);
                const auto timing = build.provisionalTiming();
                if (!timing.provisional)
                    continue; // L_p >= L: the exact tail itself (previous test)
                build.useDiffuseLevel(*level);
                sim::HybridDiagnostics dEx, dPr;
                const auto irEx = build.assemble(&dEx);
                const auto uEx = build.unitDecays();
                const auto irPr = build.assembleProvisional(&dPr);
                const auto uPr = build.unitDecays();
                REQUIRE(uEx);
                REQUIRE(uPr);
                // The step <= 1 dB per emitter in every band, both windows (kept per (e, b) for the
                // out-of-domain prints).
                std::array<std::array<double, contract::kNumOctaveBands>, 2> stepT{}, stepC{};
                for (std::size_t e = 0; e < dEx.emitters.size() && e < 2; ++e)
                {
                    const double mix = dEx.emitters[e].match.mixing.mixS;
                    const auto tailEx = tailBandEnergy(*uEx, dEx, e, mix, 1e9);
                    const auto tailPr = tailBandEnergy(*uPr, dPr, e, mix, 1e9);
                    const auto comEx = tailBandEnergy(*uEx, dEx, e, mix, timing.fadeStartS);
                    const auto comPr = tailBandEnergy(*uPr, dPr, e, mix, timing.fadeStartS);
                    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                    {
                        if (tailEx[b] <= 0.0)
                            continue;
                        const double stepTail = 10.0 * std::log10(tailEx[b] / tailPr[b]);
                        const double stepCommon = 10.0 * std::log10(comEx[b] / comPr[b]);
                        stepT[e][b] = stepTail;
                        stepC[e][b] = stepCommon;
                        CAPTURE(e, b, stepTail, stepCommon);
                        REQUIRE(std::abs(stepTail) <= 1.0);
                        REQUIRE(std::abs(stepCommon) <= 1.0);
                        worstTail = std::max(worstTail, std::abs(stepTail));
                        worstCommon = std::max(worstCommon, std::abs(stepCommon));
                    }
                }
                const sim::ism::OctaveFilterbank fb(fs);
                // The prefix identity on the shipped IRs (D1 / O8, Seat 3's O5'): per emitter and band, over
                // emission times [t_mix,e, L_f - h), h = the generator's filter half-length + the analysis
                // filterbank's (both fb.maxHalfLength()), E(provisional - exact) / E(exact) <= 20
                // log10(10^(1/20) - 1) = -18.27 dB, the difference a pure 1 dB gain step gives (AX47's
                // bound).
                const double prefixBound = 20.0 * std::log10(std::pow(10.0, 0.05) - 1.0);
                for (std::size_t e = 0; e < dEx.emitters.size(); ++e)
                {
                    const std::size_t tap = irEx.index(static_cast<int>(e), 0);
                    const double mix = dEx.emitters[e].match.mixing.mixS;
                    const auto from = static_cast<std::ptrdiff_t>(
                        std::llround((mix - dEx.alignmentShiftS) * fs));
                    const auto to = static_cast<std::ptrdiff_t>(
                                        std::llround((timing.fadeStartS - dEx.alignmentShiftS) * fs))
                                    - 2 * static_cast<std::ptrdiff_t>(fb.maxHalfLength());
                    REQUIRE(to > from);
                    // Band-split the prefix only (up to L_f - h + the filter's half length: exact below
                    // `to`).
                    const auto bands = prefixBands(irPr.taps[tap], irEx.taps[tap],
                                                   static_cast<std::size_t>(to) + fb.maxHalfLength(), fb);
                    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
                    {
                        const auto& yP = bands[0][b];
                        const auto& yE = bands[1][b];
                        double diff = 0.0, ref = 0.0;
                        for (auto i = std::max<std::ptrdiff_t>(0, from); i < to; ++i)
                        {
                            const auto k = static_cast<std::size_t>(i);
                            if (k >= yE.size() || k >= yP.size())
                                break;
                            diff += (yP[k] - yE[k]) * (yP[k] - yE[k]);
                            ref += yE[k] * yE[k];
                        }
                        if (ref <= 0.0)
                            continue;
                        const double rel = diff > 0.0 ? 10.0 * std::log10(diff / ref) : -300.0;
                        CAPTURE(e, b, rel);
                        REQUIRE(rel <= prefixBound);
                        worstPrefix = std::max(worstPrefix, rel);
                    }
                }
                // EDT on the whole IR (emitter 0) at 500 Hz and 1 kHz, against the exact IR (5 %, Vorlaender
                // Table 6.1), in every case whose exact band IR has a direct fraction d < 0.5 (D1 / O8:
                // Kuttruff Eq. 5.44's w_d = w_r on the measured field; section 8.4). d is judged on the exact
                // IR alone, before comparing.
                // The whole IRs (emitter 0) split into bands in one pass (the EDT bands 3 and 4 are read).
                const auto edtBands = prefixBands(
                    irPr.taps[0], irEx.taps[0], std::max(irPr.taps[0].size(), irEx.taps[0].size()), fb, 3, 5);
                for (const std::size_t b : {std::size_t{3}, std::size_t{4}})
                {
                    const auto& yEx = edtBands[1][b];
                    const auto& yPr = edtBands[0][b];
                    double eEx = 0.0, peak = 0.0;
                    std::size_t at = 0;
                    for (std::size_t i = 0; i < yEx.size(); ++i)
                    {
                        eEx += yEx[i] * yEx[i];
                        if (yEx[i] * yEx[i] > peak)
                        {
                            peak = yEx[i] * yEx[i];
                            at = i;
                        }
                    }
                    double direct = 0.0;
                    const auto w = static_cast<std::size_t>(0.005 * fs);
                    for (std::size_t i = at > w ? at - w : 0; i < std::min(yEx.size(), at + w); ++i)
                        direct += yEx[i] * yEx[i];
                    const double d = direct / eEx;
                    const double edtEx = edtS(yEx, fs);
                    const double edtPr = edtS(yPr, fs);
                    ++edtCases;
                    if (d >= kDirectFractionMax)
                    {
                        ++outOfDomain;
                        std::printf(
                            "07c1-records ax47(b) EDT %s %.0f Hz seed %u band %zu: not evaluated (outside "
                            "EDT "
                            "domain: direct-dominated, d %.3f, direct step %.2f dB); EDT exact %.1f ms, "
                            "provisional %.1f ms (T60_b %.2f s); steps tail/common e0 %+.3f/%+.3f e1 "
                            "%+.3f/%+.3f "
                            "dB\n",
                            a4.name, fs, seed, b, d, -10.0 * std::log10(1.0 - d), 1e3 * edtEx, 1e3 * edtPr,
                            dEx.decay.bandsT60S[b], stepT[0][b], stepC[0][b], stepT[1][b], stepC[1][b]);
                        continue;
                    }
                    const double rel = std::abs(edtPr / edtEx - 1.0);
                    CAPTURE(b, d, edtEx, edtPr, rel);
                    REQUIRE(edtEx > 0.0);
                    // D1 / O8 (decider files 35, 37): d < 0.217 (1/(1 + 1.9^2), ISO 3382-2's d_min ~ 1.9 r_c
                    // in diffuse-field terms, 1.9 rounded) is printed for phase-05d's ruling on the AX47 (b)
                    // d constant; nothing is asserted on it.
                    std::printf(
                        "07c1-records ax47(b) EDT %s %.0f Hz seed %u band %zu: d %.3f (d < 0.217: %s), EDT "
                        "exact %.1f ms, provisional %.1f ms (T60_b %.2f s): %+.2f %%\n",
                        a4.name, fs, seed, b, d, d < 0.217 ? "yes" : "no", 1e3 * edtEx, 1e3 * edtPr,
                        dEx.decay.bandsT60S[b], 100.0 * (edtPr / edtEx - 1.0));
                    REQUIRE(rel <= 0.05);
                    worstEdt = std::max(worstEdt, rel);
                    ++evaluated[b];
                }
            }
    }
    std::printf(
        "07c1-records ax47(b) provisional vs exact on the A4 set: worst |step| tail window %.3f dB, common "
        "window %.3f dB; EDT within 5 %% on %d cases with d < 0.5 of %d (worst %.2f %%; %d outside EDT "
        "domain, "
        "d >= 0.5); worst prefix difference %.1f dB (bound %.2f dB). A provisional-against-exact "
        "self-comparison, not a perceptual claim.\n",
        worstTail, worstCommon, evaluated[3] + evaluated[4], edtCases, 100.0 * worstEdt, outOfDomain,
        worstPrefix, 20.0 * std::log10(std::pow(10.0, 0.05) - 1.0));
    REQUIRE(evaluated[3] >= 1); // non-vacuity, not a quota (D1 / O8)
    REQUIRE(evaluated[4] >= 1);
}

// ---------------------------------------------------------------------------------------------------------------
// Condition 2 / 9 and AX48 in the pipeline
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE("Condition 9 / AX49: a project load plays a tail at once and settles to the exact IR in one step",
          "[pipeline][interim]")
{
    const auto club = pipeline_test::loadScene("club.json");
    plugin::ScenePipeline p;
    p.prepare(kRate, 256, false);
    waitSettled(p);
    const auto before = p.stats();
    restoreScene(p, club); // the first restore: a project load (AX48: keyless, no saved E_b)
    const auto first = p.lastSubmittedIr();
    REQUIRE(first != nullptr);
    const auto after = p.stats();
    REQUIRE(after.syncSolves == before.syncSolves + 1); // FM-3': the stage-1 solve, synchronously
    REQUIRE(after.keylessLoads == before.keylessLoads + 1);
    auto build = sim::StagedBuild::plan(p.currentScene(), omni(kRate));
    const auto timing = build.provisionalTiming();
    REQUIRE(timing.provisional);
    REQUIRE(after.provisionalSubmits == before.provisionalSubmits + 1);
    // The first IrSet carries a tail (never early-only, never silence): energy past the latest mixing time.
    REQUIRE(tailEnergy(*first, timing.mixMaxS) > 0.0);
    REQUIRE(first->length() < plugin::ScenePipeline::buildIr(p.currentScene(), kRate).length()); // the prefix
    waitSettled(p);
    const auto done = p.stats();
    REQUIRE(done.steps == before.steps + 1);               // one step
    REQUIRE(done.finalSubmits == before.finalSubmits + 1); // to the final
    REQUIRE(done.solves == after.solves);                  // the stage-1 solve was the final (07c-1)
    // AX47 (a): the level is the stage-1 solve's (the final in 07c-1); AX47 (b): the realised provisional ->
    // exact step over [t_mix,e, L_f) on the decays played (review M2) stays within 1 dB (expected <= ~0.06
    // dB).
    REQUIRE(done.lastStepDb > 0.0);
    REQUIRE(done.lastStepDb <= 1.0);
    std::printf("07c1-records cond9 club load: realised provisional -> exact step %.4f dB\n",
                done.lastStepDb);
    REQUIRE(bitIdentical(*p.lastSubmittedIr(), plugin::ScenePipeline::buildIr(p.currentScene(), kRate)));
}

TEST_CASE("Condition 2 / AX48: the solve runs synchronously only at a keyless load with no IrSet current",
          "[pipeline][interim][ax48]")
{
    const auto club = pipeline_test::loadScene("club.json");
    auto other = club;
    other.room.surface(contract::SurfaceId::floor).bandsAbsorption.fill(0.4);
    plugin::ScenePipeline p;
    p.prepare(kRate, 256, false);
    waitSettled(p);
    restoreScene(p, club); // project load: keyless, synchronous stage-1 solve
    waitSettled(p);
    auto s0 = p.stats();
    // A later restore with an IrSet current (preset recall, undo): everything in the background.
    restoreScene(p, other);
    REQUIRE(p.stats().syncSolves == s0.syncSolves);
    waitSettled(p);
    REQUIRE(p.stats().solves == s0.solves + 1);
    REQUIRE(p.stats().syncSolves == s0.syncSolves);
    // prepare() at the same rate: the held level is this scene's, the unit decays are cached: final at once.
    s0 = p.stats();
    p.prepare(kRate, 256, false);
    REQUIRE(p.stats().solves == s0.solves);
    REQUIRE(p.stats().finalSubmits == s0.finalSubmits + 1);
    REQUIRE_FALSE(p.settling());
    // prepare() at another rate (an fs change): no synchronous solve. The previous E_b is held (B1') under
    // the AX49 interim tail built synchronously; the builder then solves for this rate's problem (P carries
    // the rate through the specular target's band-filter energies) and settles.
    s0 = p.stats();
    p.prepare(96000.0, 256, false);
    REQUIRE(p.stats().solves == s0.solves);
    REQUIRE(p.stats().syncSolves == s0.syncSolves);
    REQUIRE(p.stats().provisionalSubmits == s0.provisionalSubmits + 1);
    waitSettled(p);
    REQUIRE(p.stats().syncSolves == s0.syncSolves);
    REQUIRE(p.stats().solves <= s0.solves + 1);
    REQUIRE(p.stats().heldSteps == s0.heldSteps + 1); // B1': recorded, not bounded (AX47 scope)
    // reset() never builds (condition 10).
    s0 = p.stats();
    p.reset();
    REQUIRE(p.stats().solves == s0.solves);
    REQUIRE(p.stats().interimSubmits == s0.interimSubmits);
    REQUIRE(p.stats().finalSubmits == s0.finalSubmits);
}

TEST_CASE("AX48: a keyed load plays the saved E_b; the confirming solve is bit-identical (step 0, no switch)",
          "[pipeline][interim][ax48]")
{
    const auto club = pipeline_test::loadScene("club.json");
    plugin::ScenePipeline a;
    a.prepare(kRate, 256, false);
    restoreScene(a, club);
    waitSettled(a);
    const auto saved = a.savedDiffuse(); // the key-match state built in-process
    REQUIRE(saved.has_value());
    REQUIRE(saved->key.p != 0);
    REQUIRE(saved->key.s == plugin::ScenePipeline::sceneKey(a.currentScene()));

    plugin::ScenePipeline b;
    b.prepare(kRate, 256, false);
    waitSettled(b);
    const auto s0 = b.stats();
    restoreScene(b, club, saved);
    REQUIRE(b.stats().keyedLoads == s0.keyedLoads + 1);
    REQUIRE(b.stats().syncSolves == s0.syncSolves); // no synchronous solve
    waitSettled(b);
    const auto s1 = b.stats();
    REQUIRE(s1.solves == s0.solves + 1); // the background solve always runs
    REQUIRE(s1.steps == s0.steps + 1);
    // AX47 (a): the keyed level is the final's bit for bit (the IR and E_b checks below); the realised step
    // is the AX49 provisional's against its exact tail, AX47 (b) (review M2).
    REQUIRE(s1.lastStepDb <= 1.0);
    REQUIRE(bitIdentical(*b.lastSubmittedIr(), *a.lastSubmittedIr()));
    REQUIRE(b.savedDiffuse()->bands == saved->bands);
}

TEST_CASE("AX48: any key-part mismatch (P, S, E_prec, E_model, Pi) is keyless: a synchronous stage-1 solve",
          "[pipeline][interim][ax48]")
{
    const auto club = pipeline_test::loadScene("club.json");
    plugin::ScenePipeline a;
    a.prepare(kRate, 256, false);
    restoreScene(a, club);
    waitSettled(a);
    const auto saved = a.savedDiffuse();
    REQUIRE(saved.has_value());
    for (int part = 0; part < 6; ++part)
    {
        CAPTURE(part);
        auto s = *saved;
        plugin::ScenePipeline b;
        if (part == 0)
            s.key.p ^= 1;
        else if (part == 1)
            s.key.s ^= 1;
        else if (part == 2)
            s.key.ePrec ^= 1;
        else if (part == 3)
            s.key.eModel += 1;
        else if (part == 4)
            s.key.platform ^= 1;
        else
            b.setPlatformTagForTest(saved->key.platform ^ 0x5a5a); // a state saved on another platform
        b.prepare(kRate, 256, false);
        waitSettled(b);
        const auto s0 = b.stats();
        restoreScene(b, club, s);
        REQUIRE(b.stats().keylessLoads == s0.keylessLoads + 1);
        REQUIRE(b.stats().keyedLoads == s0.keyedLoads);
        REQUIRE(b.stats().syncSolves == s0.syncSolves + 1);
        // A keyless restore's first IrSet carries a tail.
        REQUIRE(tailEnergy(*b.lastSubmittedIr(),
                           sim::StagedBuild::plan(b.currentScene(), omni(kRate)).provisionalTiming().mixMaxS)
                > 0.0);
        waitSettled(b);
    }
}

TEST_CASE(
    "AX48: a state restored in the other outputMode uses the saved E_b bit-identically; output mode, HRTF "
    "and seed never re-solve",
    "[pipeline][interim][ax48]")
{
    auto club = pipeline_test::loadScene("club.json");
    club.render.outputMode = contract::OutputMode::binaural;
    plugin::ScenePipeline a;
    a.prepare(kRate, 256, false);
    restoreScene(a, club);
    waitSettled(a);
    const auto saved = a.savedDiffuse();
    REQUIRE(saved.has_value());

    auto speakers = club;
    speakers.render.outputMode = contract::OutputMode::stereoSpeakers;
    plugin::ScenePipeline b;
    b.prepare(kRate, 256, false);
    waitSettled(b);
    const auto s0 = b.stats();
    restoreScene(b, speakers, saved);
    REQUIRE(b.stats().keyedLoads == s0.keyedLoads + 1);
    waitSettled(b);
    REQUIRE(b.savedDiffuse()->bands == saved->bands); // bit-identical E_b (AX44)

    // Seed, output mode and HRTF changes in the running instance: never a solve.
    const auto s1 = b.stats();
    auto seed = b.currentScene();
    seed.render.tailSeed += 11;
    restoreScene(b, seed);
    waitSettled(b);
    auto mode = b.currentScene();
    mode.render.outputMode = contract::OutputMode::binaural;
    restoreScene(b, mode);
    waitSettled(b);
    REQUIRE(b.stats().solves == s1.solves);
    REQUIRE(b.savedDiffuse()->bands == saved->bands);
}

// ---------------------------------------------------------------------------------------------------------------
// Condition 4: the ISM update first, one step per solve, never mid-drag, settling
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE("Condition 4: an edit submits the ISM update before the solve; one step per solve; settling while "
          "pending",
          "[pipeline][interim][cond4]")
{
    plugin::ScenePipeline p;
    p.prepare(kRate, 256, false);
    restoreScene(p, pipeline_test::loadScene("club.json"));
    waitSettled(p);
    for (const bool t60Edit : {false, true})
    {
        CAPTURE(t60Edit);
        const auto s0 = p.stats();
        std::atomic<bool> release{false}, sawInterimFirst{false}, sawSettling{false}, entered{false};
        p.setStageHook([&](plugin::ScenePipeline::BuildStage stage) {
            if (stage != plugin::ScenePipeline::BuildStage::Solve || entered.exchange(true))
                return;
            // Inside the AX38 gate, before the solve: the ISM update is already submitted.
            sawInterimFirst.store(p.stats().interimSubmits == s0.interimSubmits + 1);
            sawSettling.store(p.settling());
            while (!release.load())
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
        });
        if (t60Edit)
            p.setParameter(module3d::kRoomW, p.parameter(module3d::kRoomW) + 2.0f); // the D5 bridge
        else
            p.setParameter(module3d::kListenerY, p.parameter(module3d::kListenerY) + 0.5f);
        REQUIRE(pipeline_test::waitFor([&] { return entered.load(); }));
        REQUIRE(p.settling());
        release.store(true);
        waitSettled(p);
        p.setStageHook({});
        REQUIRE(sawInterimFirst.load()); // the ISM update is never held behind the solve
        REQUIRE(sawSettling.load());     // "settling" while the update is pending (AX38 (iii))
        const auto s1 = p.stats();
        REQUIRE(s1.solves == s0.solves + 1);
        REQUIRE(s1.finalSubmits == s0.finalSubmits + 1); // exactly one step per solve
        REQUIRE(s1.steps == s0.steps + 1);
        REQUIRE(s1.heldSteps == s0.heldSteps + 1); // after a B1' hold / the bridge: recorded, not bounded
        REQUIRE_FALSE(p.settling());
        REQUIRE(bitIdentical(*p.lastSubmittedIr(), plugin::ScenePipeline::buildIr(p.currentScene(), kRate)));
        std::printf("07c1-records cond4 %s edit: interim then final; step %.2f dB (held level, recorded)\n",
                    t60Edit ? "T60-changing (D5 bridge)" : "position", s1.lastStepDb);
    }
}

TEST_CASE("Condition 4: never mid-drag: a solve is not adopted when the parameters moved while it ran",
          "[pipeline][interim][cond4]")
{
    plugin::ScenePipeline p;
    p.prepare(kRate, 256, false);
    restoreScene(p, pipeline_test::loadScene("club.json"));
    waitSettled(p);
    const auto s0 = p.stats();
    std::atomic<int> solvesSeen{0};
    p.setStageHook([&](plugin::ScenePipeline::BuildStage stage) {
        if (stage == plugin::ScenePipeline::BuildStage::Solve && solvesSeen.fetch_add(1) == 0)
            p.setParameter(module3d::kListenerY,
                           p.parameter(module3d::kListenerY) + 0.25f); // the drag goes on
    });
    p.setParameter(module3d::kListenerY, p.parameter(module3d::kListenerY) + 0.5f);
    waitSettled(p);
    p.setStageHook({});
    const auto s1 = p.stats();
    REQUIRE(s1.discardedMidDrag >= s0.discardedMidDrag + 1);
    REQUIRE(s1.finalSubmits == s0.finalSubmits + 1); // one adoption, after the drag
    REQUIRE(bitIdentical(*p.lastSubmittedIr(), plugin::ScenePipeline::buildIr(p.currentScene(), kRate)));
}

// ---------------------------------------------------------------------------------------------------------------
// Condition 5: the interim level is never silence and never the AX16 level
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE(
    "Condition 5: on the A4 set the interim level is the stage-1 solve (step 0), never silence, never AX16",
    "[pipeline][interim][cond5]")
{
    for (const auto& a4 : a4Set())
    {
        CAPTURE(a4.name);
        plugin::ScenePipeline p;
        p.prepare(kRate, 256, false);
        waitSettled(p);
        const auto s0 = p.stats();
        restoreScene(p, a4.scene); // keyless project load: the stage-1 solve is the interim level
        const auto interim = p.lastSubmittedIr();
        REQUIRE(interim != nullptr);
        auto build = sim::StagedBuild::plan(p.currentScene(), omni(kRate));
        REQUIRE(tailEnergy(*interim, build.provisionalTiming().mixMaxS) > 0.0); // never silence
        waitSettled(p);
        REQUIRE(p.stats().steps == s0.steps + 1);
        REQUIRE(p.stats().lastStepDb
                <= 1.0); // AX47 (a) level = final; (b) the realised provisional step (M2)
        // Never the AX16 level: the level played is the diffuse solve's, and where AX16 is known to be > 1 dB
        // off it differs from AX16's by more than 1 dB in some band.
        sim::HybridDiagnostics dSolve, dAx16;
        (void)sim::buildRoomIR(p.currentScene(), omni(kRate), &dSolve);
        auto ax16 = omni(kRate);
        ax16.tailLevelAx16 = true;
        (void)sim::buildRoomIR(p.currentScene(), ax16, &dAx16);
        double worst = 0.0;
        for (std::size_t e = 0; e < dSolve.emitters.size(); ++e)
        {
            REQUIRE(dSolve.emitters[e].match.diffuse.computed);
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            {
                const double s = dSolve.emitters[e].match.bandsTargetEnergy[b];
                const double x = dAx16.emitters[e].match.bandsTargetEnergy[b];
                if (s > 0.0 && x > 0.0)
                    worst = std::max(worst, std::abs(10.0 * std::log10(x / s)));
            }
        }
        std::printf(
            "07c1-records cond5 %-22s interim level = the stage-1 solve; AX16 level would be off by up to "
            "%.2f dB\n",
            a4.name, worst);
        if (a4.ax16KnownOff)
            REQUIRE(worst > 1.0);
    }
}

// ---------------------------------------------------------------------------------------------------------------
// Condition 6: offline
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE(
    "Condition 6: offline waits for the final solve, never uses an interim, and bounces bit-identically",
    "[pipeline][interim][cond6][offline]")
{
    const auto club = pipeline_test::loadScene("club.json");
    std::vector<float> outs[2];
    for (int run = 0; run < 2; ++run)
    {
        plugin::ScenePipeline p;
        p.prepare(kRate, 256, true);
        restoreScene(p, club); // offline: stored; process() builds the final before its block
        pipeline_test::Recorder rec{p};
        rec.seed = 5;
        rec.run(20 * 256, 256);
        const auto st = p.stats();
        REQUIRE(st.interimSubmits == 0);
        REQUIRE(st.provisionalSubmits == 0);
        REQUIRE(st.finalSubmits >= 1);
        REQUIRE(bitIdentical(*p.lastSubmittedIr(), plugin::ScenePipeline::buildIr(p.currentScene(), kRate)));
        // An edit mid-bounce: the offline block waits for its final too.
        p.setParameter(module3d::kListenerY, p.parameter(module3d::kListenerY) + 0.5f);
        rec.run(20 * 256, 256);
        REQUIRE(p.stats().interimSubmits == 0);
        REQUIRE(bitIdentical(*p.lastSubmittedIr(), plugin::ScenePipeline::buildIr(p.currentScene(), kRate)));
        outs[run] = rec.out[0];
    }
    REQUIRE(outs[0] == outs[1]);
}

TEST_CASE("Condition 6: the render log records a host that renders faster than real time without the offline "
          "signal while the reverb settles",
          "[pipeline][interim][cond6]")
{
    pipeline_test::ManualClock clock;
    plugin::ScenePipeline p(&clock);
    p.prepare(kRate, 256, false);
    REQUIRE(pipeline_test::waitFor([&] { return p.builderIdle() || p.settling(); }));
    // Keep an interim playing: a project load, then the builder's settling attempts fail (test hook).
    restoreScene(p, pipeline_test::loadScene("club.json"));
    p.injectBuildFailures(1 << 30);
    REQUIRE(p.settling());
    std::vector<float> a(512, 0.0f), b(512, 0.0f);
    const float* const in[2] = {a.data(), b.data()};
    float* const out[2] = {a.data(), b.data()};
    double t = clock.now();
    // 2 s of audio in 0.2 s of wall clock (10 x real time), not signalled offline.
    for (int i = 0; i < 188 && p.renderLog().empty(); ++i)
    {
        p.process(in, out, 512);
        t += 0.001;
        clock.set(t);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    REQUIRE(pipeline_test::waitFor([&] { return !p.renderLog().empty(); }, std::chrono::seconds(10)));
    const auto log = p.renderLog();
    std::printf("07c1-records cond6 render log: %s\n", log.front().c_str());
    REQUIRE(log.front().find("offline signal unreliable") != std::string::npos);
    p.injectBuildFailures(0);
}

// ---------------------------------------------------------------------------------------------------------------
// A8 / AX44: E_b is shared across output modes, HRTFs and seeds (the AX48 key part S excludes them)
// ---------------------------------------------------------------------------------------------------------------

TEST_CASE("A8 / AX44: E_b is bit-identical between output modes, HRTF ids and seeds", "[interim][ax48][ax44]")
{
    auto base = pipeline_test::loadScene("club.json");
    base.render.outputMode = contract::OutputMode::binaural;
    auto build = sim::StagedBuild::plan(base, omni(kRate));
    build.solve();
    const auto ref = build.diffuseLevel();
    REQUIRE(ref.has_value());
    const auto refP = build.problemHash();
    for (int variant = 0; variant < 3; ++variant)
    {
        CAPTURE(variant);
        auto sc = base;
        if (variant == 0)
            sc.render.outputMode = contract::OutputMode::stereoSpeakers;
        else if (variant == 1)
            sc.render.hrtfId = "another-hrtf";
        else
            sc.render.tailSeed += 99;
        auto b = sim::StagedBuild::plan(sc, omni(kRate));
        REQUIRE(b.problemHash() == refP);
        REQUIRE(plugin::ScenePipeline::sceneKey(sc) == plugin::ScenePipeline::sceneKey(base));
        b.solve();
        REQUIRE(b.diffuseLevel().has_value());
        REQUIRE(std::memcmp(b.diffuseLevel()->data(), ref->data(), sizeof(sim::EmitterBands)) == 0);
    }
}
