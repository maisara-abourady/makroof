// Phase 05h, scope 4: the AX43 agreement suite, the AX45 regression gate, the AX46 bias check and the tracer
// check of the C++ diffuse estimator against the committed references (tests/golden/phase05h_agreement_reference.json
// and phase05h_tracer_reference.json, written by tools/validation/export_phase05h_references.py). Which case-bands
// are gated is the golden's `gated_<b>` column (decision D-H2, docs/review/phase-05h/); the rest are reported with
// their label (U-a). Pre-registered before any number was seen: N_test = 65 536 histories on [0, N_test) (stage 1),
// stage 2 on the disjoint range [N_test, 5 N_test) decides a stage-1 failure (AX43, no reseed); z_FW = 4.290 (AX43)
// and 3.81 (AX45); tau = 0.25 dB (AX42); the AX46 class check at the same N where 3 SE_class <= 1 % - l_ref.
#include "DiffuseTestUtil.h"

#include "sim/diffuse/DiffuseEstimator.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <cmath>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace sim::diffuse;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

namespace {

constexpr double kTau = 0.25;        // AX42
constexpr double kZfw43 = 4.290;     // AX43
constexpr double kZfw45 = 3.81;      // AX45
constexpr double kFlag45 = 0.68;     // AX45 physics flag
constexpr std::int64_t kNTest = 65536; // pre-registered (1 024 blocks)
constexpr double kBiasLimit = 0.01;  // AX46: 1 %

struct Case
{
    std::string name;
    contract::SceneDescription scene;
    std::size_t refEmitter = 0;
    int suite = 0; // 0 AX43, 1 AX45
    int cls = 0;
    std::array<double, 8> refFine{}, refCoarse{}, lRef{}, pyAx16{}, pySpec{}, pyT60{};
    std::array<bool, 8> certified{}, gated{};
    double pyWindowStart = 0.0, pyMix = 0.0;
    bool pyFallback = false;
};

std::vector<Case> loadCases(const diffuse_test::SmokeReference& ref)
{
    std::vector<Case> cases;
    const char* faces[] = {"xMin", "xMax", "yMin", "yMax", "floor", "ceiling"};
    for (std::size_t i = 0; i < ref.rows.size(); ++i)
    {
        const auto& row = ref.rows[i];
        REQUIRE(row.size() == ref.columns.size());
        const auto c = [&](const std::string& name) {
            const std::size_t idx = ref.col(name);
            REQUIRE(idx < row.size());
            return row[idx];
        };
        Case k;
        k.name = ref.names[i];
        std::array<contract::BandArray, 6> alpha{};
        std::array<double, 6> s{};
        for (std::size_t f = 0; f < 6; ++f)
        {
            for (std::size_t b = 0; b < 8; ++b)
                alpha[f][b] = c("alpha_" + std::string(faces[f]) + "_" + std::to_string(b));
            s[f] = c("s_" + std::string(faces[f]));
        }
        std::vector<contract::Vec3> emitters{{c("src0_x"), c("src0_y"), c("src0_z")}};
        if (c("num_emitters") > 1.5)
            emitters.push_back({c("src1_x"), c("src1_y"), c("src1_z")});
        k.scene = diffuse_test::scene({c("dims_x"), c("dims_y"), c("dims_z")}, alpha, s,
                                      {c("rcv_x"), c("rcv_y"), c("rcv_z")}, emitters);
        k.refEmitter = static_cast<std::size_t>(c("ref_emitter"));
        k.suite = static_cast<int>(c("suite"));
        k.cls = static_cast<int>(c("cls"));
        for (std::size_t b = 0; b < 8; ++b)
        {
            const std::string bs = std::to_string(b);
            k.refFine[b] = c("ref_fine_" + bs);
            k.refCoarse[b] = c("ref_coarse_" + bs);
            k.lRef[b] = c("l_ref_" + bs);
            k.certified[b] = c("certified_" + bs) > 0.5;
            k.gated[b] = c("gated_" + bs) > 0.5;
            k.pyAx16[b] = c("py_target_ax16_" + bs);
            k.pySpec[b] = c("py_target_specular_" + bs);
            k.pyT60[b] = c("py_t60_" + bs);
        }
        k.pyWindowStart = c("py_window_start_s");
        k.pyMix = c("py_mix_s");
        k.pyFallback = c("py_fallback") > 0.5;
        cases.push_back(k);
    }
    return cases;
}

double db(double x)
{
    return 10.0 * std::log10(x);
}

const char* className(int cls)
{
    switch (cls)
    {
    case 0:
        return "reference";
    case 1:
        return "near_wall";
    case 2:
        return "absorbing";
    case 3:
        return "small";
    case 5:
        return "bras";
    default:
        return "other";
    }
}

struct Stat
{
    double sum = 0.0, sum2 = 0.0;
    int n = 0;
    void add(double v)
    {
        sum += v;
        sum2 += v * v;
        ++n;
    }
    double mean() const { return n ? sum / n : 0.0; }
    double se() const // of the mean, from the sample spread
    {
        if (n < 2)
            return 0.0;
        const double var = (sum2 - sum * sum / n) / (n - 1);
        return std::sqrt(std::max(0.0, var) / n);
    }
};

} // namespace

TEST_CASE("diffuse estimator agrees with ref_hybrid on the AX43 case set (AX42 tau, z_FW 4.290, stage 2); AX45 "
          "regression gate; AX46 bias per class; uncertified references reported (D-H2)",
          "[.][benchmark][diffuse-agree-full]")
{
    const auto ref = diffuse_test::readSmokeReference(std::string(SPATIAL_GOLDEN_DIR)
                                                      + "/phase05h_agreement_reference.json");
    const auto cases = loadCases(ref);
    REQUIRE(cases.size() == 79); // 70 (AX43) + 9 (AX45)
    DiffuseLimits stage1;
    stage1.fixedHistories = kNTest;
    DiffuseLimits stage2;
    stage2.fixedStart = kNTest;
    stage2.fixedHistories = 4 * kNTest;

    int gatedBands = 0, reportedBands = 0, noRefBands = 0, stage2Runs = 0, failures = 0, ax45Gated = 0;
    double worstDb = 0.0;
    std::array<Stat, 8> pooledZ{};                  // AX43 pooled bias per band
    std::map<int, std::array<Stat, 8>> classDev;   // AX46: signed relative deviation per class and band
    std::map<int, std::array<double, 8>> classLRef; // max l_ref per class and band
    for (const Case& k : cases)
    {
        const auto planned = diffuse_test::plan(k.scene);
        const auto& pe = planned.emitters[k.refEmitter];
        INFO(k.name);
        // The C++ plan reproduces the Python plan of the reference emitter (window, fallback, specular target).
        REQUIRE_THAT(pe.emitter.mixS, WithinRel(k.pyMix, 1e-9));
        REQUIRE_THAT(pe.emitter.windowStartS, WithinRel(k.pyWindowStart, 1e-9));
        REQUIRE(pe.fallback == k.pyFallback);
        for (std::size_t b = 0; b < 8; ++b)
        {
            REQUIRE_THAT(pe.emitter.bandsSpecularTarget[b], WithinRel(k.pySpec[b], 1e-6) || WithinAbs(0.0, 1e-300));
            REQUIRE_THAT(pe.bandsAx16Target[b], WithinRel(k.pyAx16[b], 1e-6) || WithinAbs(0.0, 1e-300));
            REQUIRE_THAT(pe.emitter.bandsT60S[b], WithinRel(k.pyT60[b], 1e-9));
        }
        // Stage 1 on [0, N_test), the shipping configuration (both emitters of the scene, one solve).
        auto r = estimateDiffuse(planned.problem, stage1);
        REQUIRE(r.count.n == kNTest);
        bool needStage2 = false;
        std::array<double, 8> dbs{}, ses{};
        const auto evaluate = [&](const DiffuseResult& res, std::array<double, 8>& outDb,
                                  std::array<double, 8>& outSe) {
            const auto& er = res.emitters[k.refEmitter];
            for (std::size_t b = 0; b < 8; ++b)
            {
                const double tot = pe.emitter.bandsSpecularTarget[b] + er.bandsDiffuse[b];
                const double refv = k.gated[b] ? k.refFine[b] : (std::isfinite(k.refFine[b]) ? k.refFine[b] : k.refCoarse[b]);
                outDb[b] = std::isfinite(refv) && refv > 0.0 && tot > 0.0 ? db(tot / refv) : std::nan("");
                outSe[b] = er.bandsSeDb[b];
            }
        };
        evaluate(r, dbs, ses);
        for (std::size_t b = 0; b < 8; ++b)
        {
            const double lRefDb = std::isfinite(k.lRef[b]) ? db(1.0 + k.lRef[b]) : 0.0;
            if (k.gated[b])
            {
                const double zfw = k.suite == 0 ? kZfw43 : kZfw45;
                // The pre-registered N must give z_FW SE <= tau - l_ref (AX43), else the test cannot fail.
                CHECK(zfw * ses[b] <= kTau - lRefDb);
                if (!(std::abs(dbs[b]) <= kTau) || !(zfw * ses[b] <= kTau - lRefDb))
                    needStage2 = true;
            }
        }
        if (needStage2)
        {
            ++stage2Runs;
            const auto r2 = estimateDiffuse(planned.problem, stage2);
            REQUIRE(r2.count.n == 4 * kNTest);
            std::array<double, 8> dbs2{}, ses2{};
            evaluate(r2, dbs2, ses2);
            std::printf("agree-full %-28s stage 2 (4 N on [N, 5N)): ", k.name.c_str());
            for (std::size_t b = 0; b < 8; ++b)
                if (k.gated[b])
                {
                    std::printf("b%zu %+.3f dB (SE %.3f) ", b, dbs2[b], ses2[b]);
                    dbs[b] = dbs2[b];
                    ses[b] = ses2[b];
                }
            std::printf("\n");
        }
        // AX45: dL = 10 log10(E_AX16 / E_target), C++ against the reference (py AX16 / ref_fine).
        for (std::size_t b = 0; b < 8; ++b)
        {
            const double lRefDb = std::isfinite(k.lRef[b]) ? db(1.0 + k.lRef[b]) : 0.0;
            const double z = ses[b] > 0.0 && std::isfinite(dbs[b]) ? dbs[b] / ses[b] : 0.0;
            if (k.gated[b])
            {
                ++gatedBands;
                worstDb = std::max(worstDb, std::abs(dbs[b]));
                if (k.suite == 0)
                {
                    pooledZ[b].add(z);
                    const bool pass = std::abs(dbs[b]) <= kTau;
                    if (!pass)
                        ++failures;
                    CHECK(pass);
                    std::printf("agree-full %-28s band %zu [gated %s] C++ - ref %+.4f dB  SE %.4f  z %+.2f  l_ref %.3f%%\n",
                                k.name.c_str(), b, className(k.cls), dbs[b], ses[b], z, 100.0 * k.lRef[b]);
                    classDev[k.cls][b].add(std::pow(10.0, dbs[b] / 10.0) - 1.0);
                    classLRef[k.cls][b] = std::max(classLRef[k.cls][b], k.lRef[b]);
                }
                else
                {
                    ++ax45Gated;
                    // dL_C++ - dL_ref = (log E_ax16,C++ - log E_C++) - (log E_ax16,py - log E_ref) = -(C++ - ref) in dB
                    // since the AX16 targets agree to 1e-6 (checked above).
                    const double dDelta = -dbs[b];
                    const bool pass = std::abs(dDelta) <= kTau;
                    if (!pass)
                        ++failures;
                    CHECK(pass);
                    const double dLRef = db(k.pyAx16[b] / k.refFine[b]);
                    std::printf("agree-full %-28s band %zu [AX45] dL_C++ - dL_ref %+.4f dB  dL_ref %+.3f dB  SE %.4f%s\n",
                                k.name.c_str(), b, dDelta, dLRef, ses[b],
                                std::abs(dLRef) > kFlag45 ? "  FLAG > 0.68 dB (physics finding)" : "");
                }
            }
            else if (std::isfinite(dbs[b]))
            {
                ++reportedBands;
                std::printf("agree-full %-28s band %zu [REPORTED, uncertified rung, no l_ref, not pass/fail] C++ - ref "
                            "%+.4f dB  SE %.4f\n",
                            k.name.c_str(), b, dbs[b], ses[b]);
            }
            else
            {
                ++noRefBands;
                std::printf("agree-full %-28s band %zu [no reference yet]\n", k.name.c_str(), b);
            }
        }
    }
    // AX43 pooled bias per band: |mean z| <= 3 / sqrt(M).
    for (std::size_t b = 0; b < 8; ++b)
        if (pooledZ[b].n > 0)
        {
            const double limit = 3.0 / std::sqrt(static_cast<double>(pooledZ[b].n));
            std::printf("agree-full pooled bias band %zu: mean z %+.3f over %d case-bands (limit %.3f)\n", b,
                        pooledZ[b].mean(), pooledZ[b].n, limit);
            CHECK(std::abs(pooledZ[b].mean()) <= limit);
        }
    // AX46: mean signed deviation <= 1 % per band and class, evaluated where 3 SE_class <= 1 % - l_ref.
    for (const auto& [cls, stats] : classDev)
        for (std::size_t b = 0; b < 8; ++b)
        {
            const Stat& st = stats[b];
            if (st.n == 0)
                continue;
            const double budget = kBiasLimit - classLRef[cls][b];
            const bool evaluated = budget > 0.0 && st.n >= 2 && 3.0 * st.se() <= budget;
            std::printf("agree-full AX46 class %-10s band %zu: mean deviation %+.3f%% (SE %.3f%%, %d cases, l_ref max %.3f%%) %s\n",
                        className(cls), b, 100.0 * st.mean(), 100.0 * st.se(), st.n, 100.0 * classLRef[cls][b],
                        evaluated ? "evaluated" : "not evaluated (pre-registered N insufficient for 3 SE <= 1 % - l_ref)");
            if (evaluated)
                CHECK(std::abs(st.mean()) <= kBiasLimit);
        }
    std::printf("agree-full summary: %d gated AX43 case-bands, %d gated AX45 case-bands, %d reported (uncertified), %d without "
                "reference; max |C++ - ref| %.4f dB over the gated set; %d stage-2 runs; %d failures (N_test %lld)\n",
                gatedBands - ax45Gated, ax45Gated, reportedBands, noRefBands, worstDb, stage2Runs, failures,
                static_cast<long long>(kNTest));
}

// AX37 (5.1) (ii) and phase-05h scope 4: the C++ E_target against the tracer's committed window energies (the 15
// (A) cases at 500 Hz-2 kHz; the outer bands 125 Hz, 4 kHz, 8 kHz on layouts 4/5 at s = 1), within the B11 window
// tolerance +-1 dB, independently of ref_hybrid. Deterministic (fixed key); cheap enough for Debug, ASan and TSan.
TEST_CASE("diffuse estimator: C++ E_target vs the tracer's window energies within 1 dB on the 15 (A) cases (B11 window "
          "tolerance); outer bands reported",
          "[diffuse][tracer]")
{
    const auto ref = diffuse_test::readSmokeReference(std::string(SPATIAL_GOLDEN_DIR) + "/phase05h_tracer_reference.json");
    REQUIRE(ref.rows.size() == 15);
    DiffuseLimits fixed;
    fixed.fixedHistories = 4096; // SE ~0.15 dB against a 1 dB tolerance
    const char* faces[] = {"alpha_xMin", "alpha_xMax", "alpha_yMin", "alpha_yMax", "alpha_floor", "alpha_ceiling"};
    double worstAq9 = 0.0, worstOuter = 0.0;
    for (std::size_t i = 0; i < ref.rows.size(); ++i)
    {
        const auto& row = ref.rows[i];
        const auto c = [&](const std::string& name) {
            const std::size_t idx = ref.col(name);
            REQUIRE(idx < row.size());
            return row[idx];
        };
        std::array<contract::BandArray, 6> alpha{};
        for (std::size_t f = 0; f < 6; ++f)
            alpha[f] = diffuse_test::flat(c(faces[f]));
        const double s = c("s");
        const auto sc = diffuse_test::scene({c("dims_x"), c("dims_y"), c("dims_z")}, alpha, {s, s, s, s, s, s},
                                            {c("rcv_x"), c("rcv_y"), c("rcv_z")}, {{c("src_x"), c("src_y"), c("src_z")}});
        const auto planned = diffuse_test::plan(sc);
        const auto& pe = planned.emitters[0];
        REQUIRE_THAT(pe.emitter.mixS, WithinRel(c("py_mix_s"), 1e-9));
        const auto r = estimateDiffuse(planned.problem, fixed);
        for (std::size_t b = 0; b < 8; ++b)
        {
            const double eTr = c("e_tr_" + std::to_string(b));
            if (!std::isfinite(eTr))
                continue;
            const double tot = pe.emitter.bandsSpecularTarget[b] + r.emitters[0].bandsDiffuse[b];
            const double d = db(tot / eTr);
            const bool aq9 = b >= 3 && b <= 5;
            std::printf("tracer %-18s band %zu %s C++ - tracer %+.3f dB (tracer SE %.3f dB, C++ SE %.3f dB)\n",
                        ref.names[i].c_str(), b, aq9 ? "[gated]" : "[outer band, reported]", d,
                        c("se_tr_db_" + std::to_string(b)), r.emitters[0].bandsSeDb[b]);
            if (aq9)
            {
                worstAq9 = std::max(worstAq9, std::abs(d));
                CHECK(std::abs(d) <= 1.0);
            }
            else
                worstOuter = std::max(worstOuter, std::abs(d));
        }
    }
    std::printf("tracer summary: max |C++ - tracer| %.3f dB at 500 Hz-2 kHz (gated, 1 dB); %.3f dB in the outer bands (reported)\n",
                worstAq9, worstOuter);
}
