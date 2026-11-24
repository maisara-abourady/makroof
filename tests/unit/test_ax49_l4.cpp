// Phase-07c-2b M3-L4 (decider files 6, 9, 13; Seat 3's P4 / P5, files 4-seat3, 12-seat3): the AX49
// provisional unit decays against the exact ones on the L4 scene S' (the 100 m cube at T60 8 s,
// tools/ci/ax49_l4.py), read through StagedBuild::unitDecays().
//   P4: per emitter and band, on [t_mix,e + 2.5 ms, L_f), provisional = c_b * exact (relative residual
//   printed and
//       asserted against the bound the measurement supports, see below);
//   P5: the provisional's gain over [L_f, L_p) relative to its value before L_f is the raised cosine
//       0.5 (1 + cos(pi (j - lf + 1) / (fadeLen + 1))), monotone, first value >= 1 - 1e-5, 0 from L_p.
// The bound 1e-9 is Seat 3's; the measured residuals on S' are far below it (printed).
// measurement, never fitted to pass (CLAUDE.md "never loosen").

#include "ContractFixtures.h"
#include "PipelineTestUtil.h"

#include "sim/Engine.h"
#include "sim/tail/NoiseTail.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>
#include <numbers>
#include <vector>

namespace {

// S' (decider file 6 M3-L4 "Scene"; alpha per band from the builder's iteration, tools/ci/ax49_l4.py
// L4_ALPHA)
contract::SceneDescription sPrime(std::uint32_t seed = 12345)
{
    auto s = pipeline_test::loadScene("medium_room.json");
    s.room.geometry.dimensions = {.x = 100.0, .y = 100.0, .z = 100.0};
    const contract::BandArray alpha{0.2836145906046942,  0.2801163239249038,  0.2704382479375733,
                                    0.2543793051751666,  0.23188082812760125, 0.23188082812760125,
                                    0.23188082812760125, 0.23188082812760125};
    for (auto& f : s.room.surfaces)
    {
        f.bandsAbsorption = alpha;
        f.scattering = 0.3;
    }
    s.listener.position = {.x = 50.0, .y = 30.0, .z = 1.7};
    s.emitters[0].position = {.x = 45.0, .y = 70.0, .z = 2.0};
    s.emitters[1].position = {.x = 55.0, .y = 70.0, .z = 2.0};
    s.render.tailSeed = seed;
    return s;
}

sim::BuildOptions omni48()
{
    sim::BuildOptions o;
    o.sampleRate = 48000.0;
    o.kind = sim::BuildOptions::Kind::Omni;
    return o;
}

struct P4P5
{
    double worstP4 = 0.0; // max over (e, b) of max_j |pr - c ex| / rms(ex) on the P4 window
    double worstP5 = 0.0; // max over (e, b) of max_j |pr[j] / (c_lin ex_fit) - g(j)| on the fade (see below)
    double worstCb = 0.0; // max |20 log10 c_b|
    bool monotone = true;
    bool zeroAfter = true;
};

struct Built
{
    sim::ProvisionalTiming timing;
    sim::HybridDiagnostics dEx;
    std::shared_ptr<const std::vector<sim::tail::UnitDecay>> uEx, uPr;
};

Built build(const contract::SceneDescription& scene)
{
    auto b = sim::StagedBuild::plan(scene, omni48());
    Built r;
    r.timing = b.provisionalTiming();
    REQUIRE(r.timing.provisional);
    sim::HybridDiagnostics dPr;
    (void)b.assemble(&r.dEx);
    r.uEx = b.unitDecays();
    (void)b.assembleProvisional(&dPr);
    r.uPr = b.unitDecays();
    REQUIRE(r.uEx);
    REQUIRE(r.uPr);
    return r;
}

P4P5 measure(const Built& bt, const std::vector<sim::tail::UnitDecay>& prUnits)
{
    const auto& timing = bt.timing;
    const double fs = 48000.0;
    const std::size_t lp = sim::tail::unitDecayLength(timing.endS, fs);
    const std::size_t lf = std::min(lp, sim::tail::unitDecayLength(timing.fadeStartS, fs));
    const std::size_t fadeLen = lp - lf;
    P4P5 r;
    for (std::size_t e = 0; e < bt.uEx->size() && e < bt.dEx.emitters.size(); ++e)
    {
        const double mix = bt.dEx.emitters[e].match.mixing.mixS;
        const auto from = static_cast<std::size_t>(std::ceil((mix + 0.0025) * fs));
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            const auto& ex = (*bt.uEx)[e].bands[b];
            const auto& pr = prUnits[e].bands[b];
            REQUIRE(pr.size() >= lp);
            REQUIRE(ex.size() > lp);
            // P4: least-squares c_b on [t_mix,e + 2.5 ms, L_f)
            double num = 0.0, den = 0.0;
            for (std::size_t j = from; j < lf; ++j)
            {
                num += pr[j] * ex[j];
                den += ex[j] * ex[j];
            }
            REQUIRE(den > 0.0);
            const double c = num / den;
            const double rms = std::sqrt(den / static_cast<double>(lf - from));
            double worst = 0.0;
            for (std::size_t j = from; j < lf; ++j)
                worst = std::max(worst, std::abs(pr[j] - c * ex[j]) / rms);
            r.worstP4 = std::max(r.worstP4, worst);
            r.worstCb = std::max(r.worstCb, std::abs(20.0 * std::log10(std::abs(c))));
            // P5: the gain over [L_f, L_p) read as pr[j] / (c ex[j]) where |ex[j]| is not small (the
            // provisional's generator sample equals ex[j] to the P4 residual), against the raised cosine
            double prev = 2.0;
            for (std::size_t j = lf; j < lp; ++j)
            {
                const double g = 0.5
                                 * (1.0
                                    + std::cos(std::numbers::pi * static_cast<double>(j - lf + 1)
                                               / static_cast<double>(fadeLen + 1)));
                if (std::abs(ex[j]) > 0.1 * rms)
                    r.worstP5 = std::max(r.worstP5, std::abs(pr[j] / (c * ex[j]) - g));
                if (g > prev)
                    r.monotone = false;
                if (j == lf && g < 1.0 - 1e-5)
                    r.monotone = false;
                prev = g;
            }
            for (std::size_t j = lp; j < pr.size(); ++j)
                if (pr[j] != 0.0)
                    r.zeroAfter = false;
        }
    }
    return r;
}

} // namespace

// Seat 3's P4 / P5 at 1e-9 (files 4-seat3, 12-seat3); measured on S': P4 2.5e-13, P5 3.6e-14 (builder,
// 2026-11-24).
inline constexpr double kP4P5Bound = 1e-9;

TEST_CASE(
    "AX49 L4: the provisional unit decays are c_b times the exact ones, faded by the raised cosine (S')",
    "[ax49-l4]")
{
    const auto bt = build(sPrime());
    const auto r = measure(bt, *bt.uPr);
    std::printf(
        "ax49-l4: P4 worst relative residual %.3e, worst |c_b| %.6f dB, P5 worst gain deviation %.3e\n",
        r.worstP4, r.worstCb, r.worstP5);
    CHECK(r.worstP4 <= kP4P5Bound);
    CHECK(r.worstCb <= 1.0); // AX47 (b)'s bound
    CHECK(r.worstP5 <= kP4P5Bound);
    CHECK(r.monotone);
    CHECK(r.zeroAfter);

    SECTION("N-L1: a hard cut at L_f fails P5")
    {
        auto cut = *bt.uPr;
        const std::size_t lf = sim::tail::unitDecayLength(bt.timing.fadeStartS, 48000.0);
        for (auto& u : cut)
            for (auto& band : u.bands)
                for (std::size_t j = lf; j < band.size(); ++j)
                    band[j] = 0.0;
        CHECK(measure(bt, cut).worstP5 > 0.5);
    }
    SECTION("N-L2: a provisional built with another tailSeed fails P4")
    {
        const auto other = build(sPrime(12346));
        CHECK(measure(bt, *other.uPr).worstP4 > 1e-3);
    }
}
