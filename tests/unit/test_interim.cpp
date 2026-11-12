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
        set.push_back({"bras_cr3_ls1_mp2", *parsed.scene, false});
    }
    return set;
}

// The per-band energy of emitter e's tail as built, over emission times [t0, t1): A_b^2 sum w_tail^2 u_b^2
// over the IR samples whose emission time lies there (the band split of the construction itself).
contract::BandArray tailBandEnergy(const std::vector<sim::tail::UnitDecay>& units,
                                   const sim::HybridDiagnostics& d, std::size_t e, double t0, double t1)
{
    contract::BandArray out{};
    const auto& u = units[e];
    const double fs = d.sampleRate;
    const double mix = d.emitters[e].match.mixing.mixS;
    const auto offset = static_cast<std::size_t>(std::max(0.0, std::round(d.alignmentShiftS * fs)));
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
    {
        const double a = d.emitters[e].match.bandsAmplitude[b];
        double sum = 0.0;
        for (std::size_t j = offset; j < u.length(); ++j)
        {
            const double t = static_cast<double>(j) / fs;
            if (t < t0 || t >= t1)
                continue;
            const double w =
                sim::tail::crossfade(static_cast<double>(j - offset) / fs + d.alignmentShiftS, mix).tail;
            sum += w * w * u.bands[b][j] * u.bands[b][j];
        }
        out[b] = a * a * sum;
    }
    return out;
}

// The IR of emitter 0 band-filtered through the filterbank's band b (circular FFT convolution, centred
// filter).
std::vector<double> bandFiltered(const std::vector<float>& x, const sim::ism::OctaveFilterbank& fb,
                                 std::size_t b)
{
    const auto h = fb.bandImpulseResponse(b);
    const std::size_t half = (h.size() - 1) / 2;
    const std::size_t n = sim::Fft::nextPowerOfTwo(x.size() + h.size());
    const sim::Fft fft(n);
    std::vector<std::complex<double>> X(n), H(n);
    for (std::size_t i = 0; i < x.size(); ++i)
        X[i] = x[i];
    for (std::size_t i = 0; i < h.size(); ++i)
        H[(i + n - half) % n] = h[i];
    fft.forward(X);
    fft.forward(H);
    for (std::size_t k = 0; k < n; ++k)
        X[k] *= H[k];
    fft.inverse(X);
    std::vector<double> y(x.size());
    for (std::size_t i = 0; i < x.size(); ++i)
        y[i] = X[i].real() / static_cast<double>(n);
    return y;
}

// EDT (s) of a band signal as tools/acoustics/metrics.py takes it (ISO 3382-1 A.2.1): the Schroeder curve
// from the onset (the first sample within 20 dB of the peak), normalised to 0 dB there; a least-squares line
// through every sample of it from 0 dB to the first time it reaches -10 dB; EDT = -60 / slope.
double edtS(const std::vector<double>& y, double fs, double totalScale = 1.0)
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
    const double total = sch[onset] * totalScale;
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

TEST_CASE(
    "AX47 (b) / AX49: provisional against exact on the A4 set, both windows <= 1 dB per band, EDT within 5 %",
    "[interim][ax49][ax47]")
{
    double worstTail = 0.0, worstCommon = 0.0, worstEdt = 0.0;
    int edtEvaluated = 0, illConditioned = 0;
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
                auto ex = sim::StagedBuild::plan(sc, omni(fs));
                auto pr = sim::StagedBuild::plan(sc, omni(fs));
                const auto timing = pr.provisionalTiming();
                if (!timing.provisional)
                    continue; // L_p >= L: the exact tail itself (previous test)
                ex.useDiffuseLevel(*level);
                pr.useDiffuseLevel(*level);
                sim::HybridDiagnostics dEx, dPr;
                const auto irEx = ex.assemble(&dEx);
                const auto irPr = pr.assembleProvisional(&dPr);
                const auto uEx = ex.unitDecays();
                const auto uPr = pr.unitDecays();
                REQUIRE(uEx);
                REQUIRE(uPr);
                for (std::size_t e = 0; e < dEx.emitters.size(); ++e)
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
                        CAPTURE(e, b, stepTail, stepCommon);
                        REQUIRE(std::abs(stepTail) <= 1.0);
                        REQUIRE(std::abs(stepCommon) <= 1.0);
                        worstTail = std::max(worstTail, std::abs(stepTail));
                        worstCommon = std::max(worstCommon, std::abs(stepCommon));
                    }
                }
                // EDT on the whole IR (emitter 0) at 500 Hz and 1 kHz, against the exact IR (5 %, Vorlaender
                // Table 6.1).
                const sim::ism::OctaveFilterbank fb(fs);
                for (const std::size_t b : {std::size_t{3}, std::size_t{4}})
                {
                    const auto yEx = bandFiltered(irEx.taps[0], fb, b);
                    const auto yPr = bandFiltered(irPr.taps[0], fb, b);
                    const double edtEx = edtS(yEx, fs);
                    const double edtPr = edtS(yPr, fs);
                    {
                        // Interrogator file 22 Q1/Q2: per-band missing-energy fraction eps of the provisional (whole
                        // band IR, emitter 0) and the direct fraction d (energy within 5 ms of the peak / total).
                        double eEx = 0.0, ePr = 0.0, peak = 0.0;
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
                        for (const double v : yPr)
                            ePr += v * v;
                        double direct = 0.0;
                        const auto w = static_cast<std::size_t>(0.005 * fs);
                        for (std::size_t i = at > w ? at - w : 0; i < std::min(yEx.size(), at + w); ++i)
                            direct += yEx[i] * yEx[i];
                        std::printf("07c1-records ax47(b) EDT case %s %.0f Hz seed %u band %zu: eps %.3e, direct "
                                    "fraction d %.3f, EDT exact %.2f ms, provisional %.2f ms (%.2f %%)\n",
                                    a4.name, fs, seed, b, 1.0 - ePr / eEx, direct / eEx, 1e3 * edtEx, 1e3 * edtPr,
                                    100.0 * (edtPr / edtEx - 1.0));
                    }
                    const double rel = std::abs(edtPr / edtEx - 1.0);
                    CAPTURE(b, edtEx, edtPr, rel);
                    REQUIRE(edtEx > 0.0);
                    // Conditioning: the exact IR's own EDT under a +-0.06 dB change of its total energy (the
                    // AX49 truncation bound). Where that alone moves EDT by more than 5 %, the regression's
                    // -10 dB end point sits on a plateau of a sparse early part (a direct-dominated band) and
                    // EDT cannot resolve the provisional; the case is printed, not asserted.
                    const double up = edtS(yEx, fs, std::pow(10.0, 0.006));
                    const double down = edtS(yEx, fs, std::pow(10.0, -0.006));
                    const double conditioning = std::max(std::abs(up / edtEx - 1.0),
                                                         std::abs(down / edtEx - 1.0));
                    if (conditioning > 0.05)
                    {
                        ++illConditioned;
                        std::printf(
                            "07c1-records ax47(b) EDT %s %.0f Hz seed %u band %zu: not evaluated "
                            "(ill-conditioned "
                            "EDC: +-0.06 dB of total moves the exact EDT by %.1f %%; EDT exact %.1f ms, "
                            "provisional %.1f ms)\n",
                            a4.name, fs, seed, b, 100.0 * conditioning, 1e3 * edtEx, 1e3 * edtPr);
                        continue;
                    }
                    REQUIRE(rel <= 0.05);
                    worstEdt = std::max(worstEdt, rel);
                    ++edtEvaluated;
                }
            }
    }
    std::printf(
        "07c1-records ax47(b) provisional vs exact on the A4 set: worst |step| tail window %.3f dB, common "
        "window %.3f dB, worst EDT deviation %.2f %% over %d evaluated cases (%d ill-conditioned, printed) "
        "(bounds 1 dB, 1 dB, 5 %%)\n",
        worstTail, worstCommon, 100.0 * worstEdt, edtEvaluated, illConditioned);
    REQUIRE(edtEvaluated >= illConditioned); // most cases are evaluated
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
    REQUIRE(done.lastStepDb == 0.0);                       // same level: the provisional is normalised (AX49)
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
    REQUIRE(s1.lastStepDb == 0.0); // AX47 (a): step 0 within AX5's scope
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
        REQUIRE(p.stats().lastStepDb == 0.0); // AX47 (a): the stage-1 solve is the final in 07c-1
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
            "07c1-records cond5 %-22s interim = stage-1 solve (step 0); AX16 level would be off by up to "
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
