// sim::buildRoomIR(Kind::Omni): the Phase 04 hybrid room IR (ISM early part + stochastic tail).
// The acoustic gates (T30 vs Eyring, seed and sample-rate ensembles, the EDC seam test, goldens)
// run in Python: tools/acoustics/tests/test_tail.py.
#include "ContractFixtures.h"
#include "contract/Parse.h"
#include "sim/AirAbsorption.h"
#include "sim/Engine.h"
#include "sim/ism/BandRenderer.h"

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <numbers>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

// Exact floating-point comparisons are intended here (determinism, exact zeros, values copied
// unchanged), so -Wfloat-equal (part of JUCE's recommended warnings, which the tests compile with
// when the plugin is built) is silenced for this file, as in contract/SceneDescription.h.
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

using Catch::Matchers::WithinAbs;

namespace {

contract::SceneDescription loadScene(const std::string& name)
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / name));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

const sim::BuildOptions kOmni48{48000.0, sim::BuildOptions::Kind::Omni};

double energy(const std::vector<float>& x, std::size_t from, std::size_t to)
{
    double s = 0.0;
    for (std::size_t i = from; i < to && i < x.size(); ++i)
        s += static_cast<double>(x[i]) * x[i];
    return s;
}

double energy(const std::vector<float>& x, std::size_t from = 0)
{
    return energy(x, from, x.size());
}

} // namespace

TEST_CASE("omni IRs: no NaN, Inf or denormals in any sample of any valid fixture at 44.1, 48 and 96 kHz",
          "[sim][hybrid]")
{
    for (const auto& path : contract_fixtures::list("valid"))
    {
        INFO(path.filename().string());
        const auto parsed = contract::parseScene(contract_fixtures::read(path));
        REQUIRE(parsed.ok());
        for (const double rate : {44100.0, 48000.0, 96000.0})
            for (const auto kind : {sim::BuildOptions::Kind::Omni, sim::BuildOptions::Kind::OmniEarly})
            {
                INFO(rate << " Hz, kind " << static_cast<int>(kind));
                const auto ir = sim::buildRoomIR(*parsed.scene, {rate, kind});
                std::size_t bad = 0;
                for (const auto& taps : ir.taps)
                    for (const float v : taps)
                        bad += (std::isfinite(v) && (v == 0.0f || std::fpclassify(v) == FP_NORMAL)) ? 0u : 1u;
                CHECK(bad == 0);
                CHECK(energy(ir.ir(0, 0)) > 0.0);
            }
    }
}

TEST_CASE("hybrid IR: the same seed is bit-identical, a different seed changes only the noise",
          "[sim][hybrid]")
{
    auto scene = loadScene("classroom.json");
    const auto a = sim::buildRoomIR(scene, kOmni48);
    const auto b = sim::buildRoomIR(scene, kOmni48);
    CHECK(a.taps == b.taps);
    scene.render.tailSeed += 1;
    const auto c = sim::buildRoomIR(scene, kOmni48);
    REQUIRE(c.length() == a.length());
    CHECK(c.taps != a.taps);
    // Before the crossfade the IR is the deterministic early part: identical for both seeds.
    sim::HybridDiagnostics d;
    (void)sim::buildRoomIR(scene, kOmni48, &d);
    const double fadeStart = d.emitters[0].match.mixing.mixS - sim::tail::kCrossfadeHalfS;
    const auto n = static_cast<std::size_t>((fadeStart - d.alignmentShiftS) * 48000.0);
    for (std::size_t i = 0; i < n; ++i)
        REQUIRE(a.ir(0, 0)[i] == c.ir(0, 0)[i]);
}

TEST_CASE("hybrid IR: both outputs of an emitter are the same; the direct path is at the pre-roll",
          "[sim][hybrid]")
{
    for (const char* name : {"small_room.json", "medium_room.json", "large_hall.json", "dead_booth.json"})
    {
        INFO(name);
        const auto scene = loadScene(name);
        const auto ir = sim::buildRoomIR(scene, kOmni48);
        CHECK(ir.ir(0, 0) == ir.ir(0, 1));
        CHECK(ir.ir(1, 0) == ir.ir(1, 1));
        const auto& taps = ir.ir(0, 0);
        const auto peak = static_cast<std::size_t>(
            std::distance(taps.begin(), std::max_element(taps.begin(), taps.end(), [](float x, float y) {
                              return std::abs(x) < std::abs(y);
                          })));
        CHECK(peak == static_cast<std::size_t>(sim::kAlignPreRollSamples));
    }
}

TEST_CASE("hybrid IR: emitters get independent tails (PCG32 stream = emitter channel)", "[sim][hybrid]")
{
    // Symmetric fixture: both emitters have the same t_mix and E_b, but different noise.
    const auto scene = loadScene("club.json");
    sim::HybridDiagnostics d;
    const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
    REQUIRE(d.emitters.size() == 2);
    CHECK(d.emitters[0].match.mixing.mixS == d.emitters[1].match.mixing.mixS);
    CHECK(d.emitters[0].match.bandsAmplitude == d.emitters[1].match.bandsAmplitude);
    const std::size_t late = 48000; // 1 s
    double cross = 0.0;
    for (std::size_t n = late; n < late + 48000; ++n)
        cross += static_cast<double>(ir.ir(0, 0)[n]) * ir.ir(1, 0)[n];
    const double norm = std::sqrt(energy(ir.ir(0, 0), late, late + 48000)
                                  * energy(ir.ir(1, 0), late, late + 48000));
    CHECK(std::abs(cross / norm) < 0.1);
}

TEST_CASE("AX20: the image list holds every image of any order arriving before t_mix + 2.5 ms",
          "[sim][hybrid][ax20]")
{
    for (const char* name : {"living_room.json", "medium_room.json", "edge_values.json"})
    {
        INFO(name);
        auto scene = loadScene(name);
        const auto timeBounded = sim::imageSourcesByChannel(scene, kOmni48);
        sim::HybridDiagnostics d;
        (void)sim::buildRoomIR(scene, kOmni48, &d);
        for (std::size_t e = 0; e < 2; ++e)
        {
            const double end = d.emitters[e].match.mixing.mixS + sim::tail::kCrossfadeHalfS;
            CHECK(d.emitters[e].imageCount == timeBounded[e].images.size());
            // Reference: an order-bounded enumeration with an order high enough to reach `end`
            // (an image of order N is at least (N - 3) * min dimension / 2 away... use a safe bound),
            // filtered by arrival time.
            const auto& dims = scene.room.geometry.dimensions;
            const double minDim = std::min({dims.x, dims.y, dims.z});
            const int order = static_cast<int>(std::ceil(2.0 * end * sim::ism::kSpeedOfSoundMps / minDim))
                              + 3;
            if (order > 60)
                continue; // too many images for a unit test (edge_values' 1.5 m width)
            auto deep = scene;
            deep.render.maxReflectionOrder = order;
            const auto all = sim::imageSourcesByChannel(deep, {48000.0, sim::BuildOptions::Kind::OmniEarly});
            std::multiset<std::tuple<double, double, double>> expected, actual;
            for (const auto& image : all[e].images)
                if (image.arrivalTimeS < end)
                    expected.insert({image.position.x, image.position.y, image.position.z});
            for (const auto& image : timeBounded[e].images)
                actual.insert({image.position.x, image.position.y, image.position.z});
            CHECK(actual == expected);
            CHECK(timeBounded[e].images.front().order == 0);
        }
    }
}

TEST_CASE("AX20: maxReflectionOrder has no effect on the hybrid IR", "[sim][hybrid][ax20]")
{
    auto scene = loadScene("medium_room.json");
    scene.render.maxReflectionOrder = 0;
    const auto a = sim::buildRoomIR(scene, kOmni48);
    scene.render.maxReflectionOrder = 60;
    const auto b = sim::buildRoomIR(scene, kOmni48);
    CHECK(a.taps == b.taps);
}

TEST_CASE("hybrid IR: the early part before the fade is the image-source render of the AX20 list",
          "[sim][hybrid]")
{
    const auto scene = loadScene("living_room.json");
    sim::HybridDiagnostics d;
    const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
    const auto sets = sim::imageSourcesByChannel(scene, kOmni48);
    const sim::ism::OctaveFilterbank fb(48000.0);
    const auto early = sim::ism::renderImageSources(sets[0].images, d.alignmentShiftS, fb);
    const double fadeStart = d.emitters[0].match.mixing.mixS - sim::tail::kCrossfadeHalfS;
    const auto n = static_cast<std::size_t>(std::floor((fadeStart - d.alignmentShiftS) * 48000.0));
    for (std::size_t i = 0; i < n; ++i)
        REQUIRE(ir.ir(0, 0)[i] == static_cast<float>(early[i]));
    // With every face at a = 1 only the direct sound is left: k_real = 0, so the AX22 fallback keeps
    // the ISM to the cap and E_b = 0; past the direct sound's filterbank ringing (kernel + 163 ms) the
    // IR is silent.
    auto silent = scene;
    for (auto& s : silent.room.surfaces)
        s.bandsAbsorption.fill(1.0);
    sim::HybridDiagnostics dd;
    const auto dry = sim::buildRoomIR(silent, kOmni48, &dd);
    CHECK(dd.emitters[0].ismFallback);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        CHECK(dd.emitters[0].match.bandsAmplitude[b] == 0.0);
    const std::size_t ringingEnd = static_cast<std::size_t>(sim::kAlignPreRollSamples) + 16
                                   + fb.maxHalfLength() + 2;
    CHECK(energy(dry.ir(0, 0), ringingEnd) == 0.0);
}

TEST_CASE("hybrid IR length: L_IR = 1.5 T60_max from emission (12 s cap), or the early part", "[sim][hybrid]")
{
    const auto scene = loadScene("club.json");
    sim::HybridDiagnostics d;
    const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
    CHECK(d.tailLengthS == std::min(12.0, 1.5 * d.decay.maxT60S()));
    const auto offset = static_cast<std::size_t>(std::round(d.alignmentShiftS * 48000.0));
    CHECK(ir.length() == static_cast<std::size_t>(std::ceil(d.tailLengthS * 48000.0)) - offset);
    CHECK(d.irLength == ir.length());
}

TEST_CASE("open_field gives no tail: E_b = 0, nothing 50 ms after the direct sound (floor s 0.4 and 0.5)",
          "[sim][hybrid]")
{
    for (const double floorScattering : {0.4, 0.5})
    {
        INFO("floor scattering " << floorScattering);
        auto scene = loadScene("open_field.json");
        REQUIRE(scene.room.surface(contract::SurfaceId::floor).scattering == 0.4);
        scene.room.surface(contract::SurfaceId::floor).scattering = floorScattering;
        sim::HybridDiagnostics d;
        const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
        for (const auto& e : d.emitters)
            for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            {
                CHECK(e.match.bandsAmplitude[b] == 0.0);
                CHECK(e.match.bandsNonZeroEntries[b] == 0);
            }
        for (int e = 0; e < 2; ++e)
        {
            const auto& taps = ir.ir(e, 0);
            const double direct = d.emitters[static_cast<std::size_t>(e)].match.mixing.directS;
            const auto from = static_cast<std::size_t>((direct + 0.050 - d.alignmentShiftS) * 48000.0);
            const double peak = static_cast<double>(*std::max_element(taps.begin(), taps.end()));
            const double late = energy(taps, from);
            CHECK(late < 1e-6 * peak * peak); // < -60 dB re the direct sound's peak energy
        }
    }
}

TEST_CASE("hybrid IR: the tail level is matched (diagnostics) and tail-only renders hold just the tail",
          "[sim][hybrid]")
{
    const auto scene = loadScene("medium_room.json");
    sim::HybridDiagnostics d;
    const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
    for (const auto& e : d.emitters)
    {
        CHECK(e.match.mixing.expectedKeff >= 19.0);
        CHECK(e.match.expectedSigmaDb <= 1.0);
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            CHECK(e.match.bandsAmplitude[b] > 0.0);
            CHECK(e.match.bandsNonZeroEntries[b] > 0);
            CHECK(std::isfinite(e.bandsRealisedOverTargetDb[b]));
        }
    }
    auto options = kOmni48;
    options.tailOnly = true;
    const auto tailOnly = sim::buildRoomIR(scene, options);
    REQUIRE(tailOnly.length() == ir.length());
    // After the fade the hybrid IR is the tail itself.
    const double fadeEnd = d.emitters[0].match.mixing.mixS + sim::tail::kCrossfadeHalfS;
    const auto from = static_cast<std::size_t>(std::ceil((fadeEnd - d.alignmentShiftS) * 48000.0)) + 1;
    for (std::size_t n = from; n < from + 1000; ++n)
        REQUIRE(tailOnly.ir(0, 0)[n] == ir.ir(0, 0)[n]);
    CHECK(std::abs(tailOnly.ir(0, 0)[0]) > 0.0f); // no early part, no fade-in
}

namespace {

// AQ10 workloads (phase-04 acceptance, AX22): the 20 x 30 x 10 m room, 2 emitters, 48 kHz.
contract::SceneDescription aq10Room(bool flutter)
{
    auto scene = loadScene("medium_room.json");
    scene.room.geometry.dimensions = {20.0, 30.0, 10.0};
    scene.listener.position = {10.0, 8.0, 1.7};
    scene.emitters[0].position = {7.0, 20.0, 2.0};
    scene.emitters[1].position = {13.0, 20.0, 2.0};
    for (auto& s : scene.room.surfaces)
    {
        s.bandsAbsorption = {0.15, 0.18, 0.2, 0.22, 0.24, 0.26, 0.28, 0.3};
        s.scattering = 0.3;
    }
    if (flutter)
    {
        // W2: a generic flutter scene (Kuttruff §4.2): hard x-walls, absorbent other faces.
        for (auto& s : scene.room.surfaces)
        {
            s.bandsAbsorption.fill(0.8);
            s.scattering = 0.1;
        }
        for (const auto id : {contract::SurfaceId::xMin, contract::SurfaceId::xMax})
        {
            scene.room.surface(id).bandsAbsorption.fill(0.02);
            scene.room.surface(id).scattering = 0.0;
        }
    }
    return scene;
}

// Position-only rebuild (AQ10): the unit decays come from the cache, as in Phase 10.
double medianRebuildMs(const contract::SceneDescription& scene, sim::BuildOptions options, int runs)
{
    const sim::ism::OctaveFilterbank fb(options.sampleRate);
    const auto decay = sim::tail::eyringDecay(scene.room);
    const sim::tail::BandNoiseGenerator gen(
        fb, sim::tail::unitDecayLength(sim::tail::tailLengthS(decay), options.sampleRate));
    std::vector<sim::tail::UnitDecay> cache;
    for (std::uint32_t e = 0; e < 2; ++e)
        cache.push_back(gen.make(decay, sim::tail::tailSeedForOutput(scene.render.tailSeed, 0), e));
    options.cachedUnitDecays = &cache;
    std::vector<double> ms;
    for (int r = 0; r < runs; ++r)
    {
        const auto start = std::chrono::steady_clock::now();
        const auto ir = sim::buildRoomIR(scene, options);
        const auto stop = std::chrono::steady_clock::now();
        REQUIRE(ir.length() > 0);
        ms.push_back(std::chrono::duration<double, std::milli>(stop - start).count());
    }
    std::sort(ms.begin(), ms.end());
    return ms[ms.size() / 2];
}

} // namespace

// Phase-04 / AQ10 benchmark (recorded, not a pass/fail on time). Hidden: CI runs it from the Release
// build with `spatial_tests "[benchmark]"`; the Linux runner's numbers set N_cap (AX22).
TEST_CASE("benchmark: AQ10 W1/W2 position-only rebuild, 20 x 30 x 10 m, 48 kHz, 2 emitters", "[.][benchmark]")
{
    constexpr int kRuns = 10;
    const auto w1 = aq10Room(false);
    sim::HybridDiagnostics d1;
    (void)sim::buildRoomIR(w1, kOmni48, &d1);
    for (const auto& e : d1.emitters)
        REQUIRE_FALSE(e.ismFallback); // W1: the hybrid IR without the AX22 fallback
    std::cout << "AQ10 W1 (no fallback): " << d1.emitters[0].imageCount + d1.emitters[1].imageCount
              << " images, t_mix " << d1.emitters[0].handoverS * 1000.0 << " ms, IR " << d1.irLength
              << " samples, median of " << kRuns << " position-only rebuilds "
              << medianRebuildMs(w1, kOmni48, kRuns) << " ms (target 50 ms)\n";

    const auto w2 = aq10Room(true);
    int largest = -1;
    for (int i0 = 10; i0 <= 20; ++i0)
    {
        auto options = kOmni48;
        options.imageCountCapOverride = sim::ism::reflectionImageCount(i0);
        sim::HybridDiagnostics d2;
        (void)sim::buildRoomIR(w2, options, &d2);
        for (const auto& e : d2.emitters)
            REQUIRE(e.ismFallback); // otherwise the scene is unsuitable for W2
        const double ms = medianRebuildMs(w2, options, kRuns);
        std::cout << "AQ10 W2 (both emitters in the AX22 fallback) i0 = " << i0
                  << ", N_cap = nu_r(i0) = " << options.imageCountCapOverride << ": t_cap "
                  << d2.emitters[0].capTimeS * 1000.0 << " ms, "
                  << d2.emitters[0].imageCount + d2.emitters[1].imageCount << " non-zero images, median "
                  << ms << " ms" << (i0 == sim::kImageCountCapOrder ? "  <- kImageCountCapOrder" : "")
                  << "\n";
        if (ms <= 50.0)
            largest = i0;
    }
    std::cout << "AQ10 W2: largest i0 >= 10 meeting 50 ms on this machine: "
              << (largest >= 10 ? std::to_string(largest)
                                : std::string("none (N_cap = nu_r(10), miss recorded)"))
              << "; compiled kImageCountCapOrder = " << sim::kImageCountCapOrder << "\n";
    BENCHMARK("W1 rebuild (cached unit decays)")
    {
        return sim::buildRoomIR(w1, kOmni48).length();
    };
}

TEST_CASE("buildRoomIREnsemble: member k equals buildRoomIR with tailSeed = seeds[k]", "[sim][hybrid]")
{
    auto scene = loadScene("dead_booth.json");
    const std::vector<std::uint32_t> seeds{5u, 4294967295u, 0u};
    for (const bool tailOnly : {false, true})
    {
        auto options = kOmni48;
        options.tailOnly = tailOnly;
        const auto irs = sim::buildRoomIREnsemble(scene, options, seeds);
        REQUIRE(irs.size() == seeds.size());
        for (std::size_t k = 0; k < seeds.size(); ++k)
        {
            scene.render.tailSeed = seeds[k];
            CHECK(irs[k].taps == sim::buildRoomIR(scene, options).taps);
        }
    }
    CHECK_THROWS_AS(sim::buildRoomIREnsemble(scene, {48000.0, sim::BuildOptions::Kind::OmniEarly}, seeds),
                    std::invalid_argument);
}

TEST_CASE("hybrid IR: the rendered tail's band energy at t_mix equals E_target (end-to-end level)",
          "[sim][hybrid]")
{
    // Seed-averaged band energy of the tail-only IR in the 10 ms centred on t_mix,e, measured with
    // the filterbank's band filter, against the matching target E_target,b (band energy per 10 ms):
    // this ties the entries, E_b, the unit decay and its placement on the IR's time axis together.
    const auto scene = loadScene("classroom.json");
    auto options = kOmni48;
    options.tailOnly = true;
    options.onlyEmitterChannel = 0;
    sim::HybridDiagnostics d;
    (void)sim::buildRoomIR(scene, kOmni48, &d);
    std::vector<std::uint32_t> seeds(48);
    for (std::uint32_t k = 0; k < seeds.size(); ++k)
        seeds[k] = 500u + k;
    const auto irs = sim::buildRoomIREnsemble(scene, options, seeds);
    const sim::ism::OctaveFilterbank fb(48000.0);
    const double centre = (d.emitters[0].match.mixing.mixS - d.alignmentShiftS) * 48000.0;
    const auto from = static_cast<std::size_t>(std::llround(centre - 240.0));
    const auto to = static_cast<std::size_t>(std::llround(centre + 240.0));
    for (const std::size_t b : {2u, 4u, 6u}) // 250 Hz, 1 kHz, 4 kHz
    {
        const auto h = fb.bandImpulseResponse(b);
        const std::size_t half = h.size() / 2;
        double mean = 0.0;
        for (const auto& ir : irs)
        {
            const auto& x = ir.ir(0, 0);
            for (std::size_t n = from; n < to; ++n)
            {
                double s = 0.0;
                for (std::size_t k = 0; k < h.size(); ++k)
                {
                    const auto i = static_cast<std::ptrdiff_t>(n + half) - static_cast<std::ptrdiff_t>(k);
                    if (i >= 0 && i < static_cast<std::ptrdiff_t>(x.size()))
                        s += h[k] * static_cast<double>(x[static_cast<std::size_t>(i)]);
                }
                mean += s * s;
            }
        }
        mean /= static_cast<double>(irs.size());
        const double target = d.emitters[0].match.bandsTargetEnergy[b];
        INFO("band " << b << ": realised " << mean << ", E_target " << target);
        // 48 realisations of a 10 ms band excerpt: ~10 % scatter at 250 Hz, less above.
        CHECK(std::abs(10.0 * std::log10(mean / target)) < 1.0);
    }
}

TEST_CASE("AX22: nu_r and the arrival time of the N-th lattice reflection", "[sim][hybrid][ax22]")
{
    // Kuttruff Eq. 9.23 as quoted in AX22 / AQ10: nu_r(10) = 1 560, nu_r(30) = 37 880.
    CHECK(sim::ism::reflectionImageCount(10) == 1560);
    CHECK(sim::ism::reflectionImageCount(30) == 37880);
    CHECK(sim::ism::reflectionImageCount(14) == 4088);
    CHECK(sim::imageCountCap() == sim::ism::reflectionImageCount(sim::kImageCountCapOrder));
    // Reference: every lattice image of order <= 40 (no a = 1 face, so none is pruned), sorted by
    // arrival; the n-th reflection must match for n well inside that order's coverage.
    auto scene = loadScene("medium_room.json");
    const auto& e = scene.emitters[0];
    sim::ism::ImageSourceOptions iso;
    iso.maxOrder = 40;
    const auto all = sim::ism::computeImageSources(scene.room, e.position, scene.listener.position, iso);
    std::vector<double> times;
    for (const auto& image : all.images)
        if (image.order > 0)
            times.push_back(image.arrivalTimeS);
    std::sort(times.begin(), times.end());
    for (const std::size_t n : {1u, 10u, 1560u, 4088u})
    {
        INFO("n = " << n);
        CHECK_THAT(sim::ism::nthReflectionArrivalTimeS(scene.room, e.position, scene.listener.position, n),
                   WithinAbs(times[n - 1], 1e-12));
    }
    // Materials don't matter: the count includes pruned (a = 1) images.
    auto open = scene;
    for (auto& s : open.room.surfaces)
        s.bandsAbsorption.fill(1.0);
    CHECK(sim::ism::nthReflectionArrivalTimeS(open.room, e.position, scene.listener.position, 1560)
          == sim::ism::nthReflectionArrivalTimeS(scene.room, e.position, scene.listener.position, 1560));
}

TEST_CASE("AX22: the realised-k switch decides on 500 Hz-2 kHz only", "[sim][hybrid][ax22]")
{
    sim::tail::TailMatch m;
    m.bandsRealisedKeff.fill(100.0);
    CHECK_FALSE(sim::tail::needsIsmFallback(m));
    m.bandsRealisedKeff[0] = 1.0; // 63 Hz: not a deciding band
    m.bandsRealisedKeff[7] = 1.0; // 8 kHz: not a deciding band
    CHECK_FALSE(sim::tail::needsIsmFallback(m));
    for (const std::size_t b : {3u, 4u, 5u})
    {
        auto one = m;
        one.bandsRealisedKeff[b] = 18.999;
        CHECK(sim::tail::needsIsmFallback(one));
        one.bandsRealisedKeff[b] = 19.0;
        CHECK_FALSE(sim::tail::needsIsmFallback(one));
    }
}

TEST_CASE("AX22: fallback to ISM-only up to the cap, handover at max(t_mix, t_cap)", "[sim][hybrid][ax22]")
{
    // medium_room falls back (k_real 16 / 13.5 / 12.5 at 500 Hz / 1 kHz / 2 kHz at t_mix); classroom
    // does not. Both are generic fixtures: no scene-specific logic (NFR-8).
    {
        const auto scene = loadScene("medium_room.json");
        sim::HybridDiagnostics d;
        const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
        const auto sets = sim::imageSourcesByChannel(scene, kOmni48);
        for (std::size_t e = 0; e < 2; ++e)
        {
            const auto& em = d.emitters[e];
            REQUIRE(em.ismFallback);
            CHECK(em.imageCountCap == sim::imageCountCap());
            const auto& emitter = scene.emitters[e];
            const double cap = sim::ism::nthReflectionArrivalTimeS(
                scene.room, emitter.position, scene.listener.position, sim::imageCountCap());
            CHECK(em.capTimeS == cap);
            const auto expected = sim::tail::mixingTime(em.match.mixing.directS, d.decay.volumeM3);
            CHECK(em.handoverS == std::max(expected.mixS, cap));
            CHECK(em.match.mixing.mixS == em.handoverS);
            // The decision was taken at the expected-rule t_mix: k_real < 19 in 500 Hz-2 kHz there.
            bool below = false;
            for (const std::size_t b : sim::tail::kRealisedKBands)
                below = below || em.bandsRealisedKeffAtMix[b] < 19.0;
            CHECK(below);
            // The list holds every image before the new handover + 2.5 ms (AX20 extended).
            CHECK(sets[e].images.back().arrivalTimeS < em.handoverS + sim::tail::kCrossfadeHalfS);
            CHECK(sets[e].images.back().arrivalTimeS > em.handoverS - 0.010);
        }
        // Before the (moved) fade the IR is the ISM render of the extended list.
        const sim::ism::OctaveFilterbank fb(48000.0);
        const auto early = sim::ism::renderImageSources(sets[0].images, d.alignmentShiftS, fb);
        const auto n = static_cast<std::size_t>(
            std::floor((d.emitters[0].handoverS - sim::tail::kCrossfadeHalfS - d.alignmentShiftS) * 48000.0));
        for (std::size_t i = 0; i < n; ++i)
            REQUIRE(ir.ir(0, 0)[i] == static_cast<float>(early[i]));
        // The tail is matched at the handover (the window holds energy there).
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            CHECK(d.emitters[0].match.bandsAmplitude[b] > 0.0);
    }
    {
        const auto scene = loadScene("classroom.json");
        sim::HybridDiagnostics d;
        (void)sim::buildRoomIR(scene, kOmni48, &d);
        for (const auto& em : d.emitters)
        {
            CHECK_FALSE(em.ismFallback);
            CHECK(em.handoverS == sim::tail::mixingTime(em.match.mixing.directS, d.decay.volumeM3).mixS);
            CHECK(em.bandsRealisedKeffAtMix == em.match.bandsRealisedKeff);
        }
    }
}

TEST_CASE("AX22: the image-cap override and the cached unit decays (validation only)", "[sim][hybrid][ax22]")
{
    const auto scene = loadScene("medium_room.json");
    auto options = kOmni48;
    sim::HybridDiagnostics base, doubled;
    const auto a = sim::buildRoomIR(scene, options, &base);
    options.imageCountCapOverride = sim::ism::reflectionImageCount(2 * sim::kImageCountCapOrder);
    (void)sim::buildRoomIR(scene, options, &doubled);
    CHECK(doubled.emitters[0].capTimeS > base.emitters[0].capTimeS);
    CHECK(doubled.emitters[0].handoverS == doubled.emitters[0].capTimeS);

    // A rebuild from cached unit decays (the Phase 10 proxy AQ10 times) gives the same IR.
    const sim::ism::OctaveFilterbank fb(48000.0);
    const auto decay = sim::tail::eyringDecay(scene.room);
    const sim::tail::BandNoiseGenerator gen(
        fb, sim::tail::unitDecayLength(sim::tail::tailLengthS(decay), 48000.0));
    std::vector<sim::tail::UnitDecay> cache;
    for (std::uint32_t e = 0; e < 2; ++e)
        cache.push_back(gen.make(decay, sim::tail::tailSeedForOutput(scene.render.tailSeed, 0), e));
    auto cachedOptions = kOmni48;
    cachedOptions.cachedUnitDecays = &cache;
    CHECK(sim::buildRoomIR(scene, cachedOptions).taps == a.taps);
}

namespace {

contract::Room boxRoom(double w, double d, double h, double alpha)
{
    contract::Room room;
    room.geometry.dimensions = {w, d, h};
    for (auto& s : room.surfaces)
    {
        s.bandsAbsorption.fill(alpha);
        s.scattering = 0.0;
    }
    return room;
}

double toDb(double ratio)
{
    return 10.0 * std::log10(ratio);
}

} // namespace

TEST_CASE("flat room (Kuttruff Eq. 4.3 / 9.24): per-image energies and their sum within 0.5 dB",
          "[sim][hybrid][analytic]")
{
    // Four walls a = 1, floor and ceiling with the same a and s = 0, source and listener at mid-height
    // (Kuttruff §4.1 example 1). The hybrid IR's image list runs to the handover (t_mix,e here; the
    // AX22 fallback, if it triggered, would move it to the cap); every image of it must match (1/r_n^2)(1 - a)^|n| e^(-m r_n),
    // r_n = sqrt(r^2 + n^2 h^2), per band, and the sum must match Eq. 4.3 truncated to the same images.
    const double h = 4.0, alpha = 0.3;
    auto scene = loadScene("medium_room.json");
    scene.room = boxRoom(200.0, 200.0, h, 1.0);
    scene.room.surface(contract::SurfaceId::floor).bandsAbsorption.fill(alpha);
    scene.room.surface(contract::SurfaceId::ceiling).bandsAbsorption.fill(alpha);
    scene.listener.position = {100.0, 100.0, h / 2.0};
    scene.emitters[0].position = {103.0, 104.0, h / 2.0}; // r = 5 m
    scene.emitters[1].position = {97.0, 96.0, h / 2.0};
    const double r = 5.0;
    sim::HybridDiagnostics d;
    (void)sim::buildRoomIR(scene, kOmni48, &d);
    const auto sets = sim::imageSourcesByChannel(scene, kOmni48);
    const auto& images = sets[0].images;
    const double end = d.emitters[0].handoverS + sim::tail::kCrossfadeHalfS;
    const auto airDb = sim::bandsAirAttenuationDbPerMetre();

    std::size_t expectedCount = 0;
    contract::BandArray sumRef{}, sumList{};
    for (int n = -1000; n <= 1000; ++n)
    {
        const double rn = std::sqrt(r * r + n * n * h * h);
        if (rn / sim::ism::kSpeedOfSoundMps >= end)
            continue;
        ++expectedCount;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            sumRef[b] += std::pow(1.0 - alpha, std::abs(n)) / (rn * rn)
                         * std::pow(10.0, -airDb[b] * rn / 10.0);
    }
    REQUIRE(images.size() == expectedCount);
    CHECK(expectedCount > 20);
    double worst = 0.0;
    for (const auto& image : images)
    {
        const int n = image.order;
        const double rn = std::sqrt(r * r + n * n * h * h);
        REQUIRE_THAT(image.distanceM, WithinAbs(rn, 1e-9));
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            const double ref = std::pow(1.0 - alpha, n) / (rn * rn) * std::pow(10.0, -airDb[b] * rn / 10.0);
            const double e = image.bandsAmplitude[b] * image.bandsAmplitude[b];
            sumList[b] += e;
            worst = std::max(worst, std::abs(toDb(e / ref)));
        }
    }
    CHECK(worst <= 0.5);
    for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        CHECK(std::abs(toDb(sumList[b] / sumRef[b])) <= 0.5);

    // The rendered IR itself: without air absorption all bands are equal, the filterbank is the
    // identity, and each arrival is the fractional-delay kernel; its energy within +-16 samples
    // must match the per-image reference.
    auto options = kOmni48;
    options.airAbsorption = false;
    const auto ir = sim::buildRoomIR(scene, options, &d);
    const double fs = 48000.0;
    const double fadeStart = d.emitters[0].handoverS - sim::tail::kCrossfadeHalfS;
    double worstRendered = 0.0;
    int checked = 0;
    for (int n = 0; n <= 200; ++n)
    {
        const double rn = std::sqrt(r * r + n * n * h * h);
        const double t = rn / sim::ism::kSpeedOfSoundMps;
        if (t + 0.001 >= fadeStart)
            break;
        const auto centre = static_cast<std::ptrdiff_t>(std::llround((t - d.alignmentShiftS) * fs));
        double e = 0.0;
        for (std::ptrdiff_t k = centre - 16; k <= centre + 16; ++k)
            e += static_cast<double>(ir.ir(0, 0)[static_cast<std::size_t>(k)])
                 * ir.ir(0, 0)[static_cast<std::size_t>(k)];
        // At mid-height the images +n and -n arrive at the same instant, so the pressure IR adds them
        // coherently: (2 a)^2 = 4 a^2 (Eq. 4.3, an energy sum, is the list check above).
        const double ref = (n == 0 ? 1.0 : 4.0) * std::pow(1.0 - alpha, n) / (rn * rn);
        worstRendered = std::max(worstRendered, std::abs(toDb(e / ref)));
        ++checked;
    }
    INFO("worst per-image error " << worst << " dB (list), " << worstRendered << " dB (rendered, " << checked
                                  << " arrivals)");
    CHECK(checked > 20);
    CHECK(worstRendered <= 0.5);
}

TEST_CASE("one absorbing wall (Kuttruff Eqs. 4.14-4.16): 1/t energy decay within 1 dB per 100 ms bin",
          "[sim][hybrid][analytic]")
{
    // 10 x 20 x 30 m box, the 10 x 20 m floor (z = 0) at a = 1, every other face rigid (a = 0, s = 0;
    // AQ3 forbids a = 0 in scenes, so the solver is called directly). Only the two image planes z_s and
    // 2L - z_s survive, each a lattice of areal density sigma = 1 / (W D); the image count grows as
    // dN/dt = 4 pi sigma c^2 t, so the energy per unit time is 4 pi sigma e^(-m c t) / t (Eq. 4.16,
    // no fitted constant). Images are summed incoherently per band (an energy result).
    const double w = 10.0, depth = 20.0, L = 30.0, c = sim::ism::kSpeedOfSoundMps;
    contract::Room room = boxRoom(w, depth, L, 0.0);
    room.surface(contract::SurfaceId::floor).bandsAbsorption.fill(1.0);
    const contract::Vec3 source{3.1, 7.3, 11.2}, receiver{6.4, 13.9, 19.7};
    const double sigma = 1.0 / (w * depth);
    const double t19 = 19.0 / (4.0 * std::numbers::pi * sigma * c * c * 0.010);
    const double tOn = std::max(
        {t19, (2.0 * L - source.z - receiver.z) / c, std::abs(source.z - receiver.z) / c});
    const double tCap = sim::ism::nthReflectionArrivalTimeS(room, source, receiver, sim::imageCountCap());
    // Deviation (phase-04 acceptance, PR): with the measured N_cap the cap can end before three full
    // bins; then the comparison extends to three full bins and says which lie beyond the cap.
    const double tEnd = std::max(tCap, tOn + 0.3 + 1e-9);
    sim::ism::ImageSourceOptions iso;
    iso.maxArrivalTimeS = tEnd;
    const auto set = sim::ism::computeImageSources(room, source, receiver, iso);
    const auto airDb = sim::bandsAirAttenuationDbPerMetre();

    int gated = 0;
    double worst = 0.0;
    for (double t1 = tOn; t1 < tEnd; t1 += 0.100)
    {
        const double t2 = std::min(t1 + 0.100, tEnd);
        const double expectedImages = 2.0 * std::numbers::pi * sigma * c * c * (t2 * t2 - t1 * t1);
        const bool full = t2 - t1 > 0.0999;
        if (!(full ? expectedImages >= 190.0 : expectedImages >= 171.0))
            continue;
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            const double m = sim::tail::airEnergyAttenuationPerMetre(airDb[b]);
            double rendered = 0.0;
            for (const auto& image : set.images)
                if (image.order > 0 && image.arrivalTimeS >= t1 && image.arrivalTimeS < t2)
                    rendered += image.bandsAmplitude[b] * image.bandsAmplitude[b];
            // int_t1^t2 4 pi sigma e^(-m c t) / t dt, by Simpson's rule.
            constexpr int kSteps = 2000;
            double integral = 0.0;
            for (int i = 0; i <= kSteps; ++i)
            {
                const double t = t1 + (t2 - t1) * i / kSteps;
                const double f = std::exp(-m * c * t) / t;
                integral += f * ((i == 0 || i == kSteps) ? 1.0 : (i % 2 == 1 ? 4.0 : 2.0));
            }
            integral *= (t2 - t1) / kSteps / 3.0 * 4.0 * std::numbers::pi * sigma;
            const double err = toDb(rendered / integral);
            worst = std::max(worst, std::abs(err));
            CHECK(std::abs(err) <= 1.0);
        }
        std::cout << "one absorbing wall: bin [" << t1 << ", " << t2 << ") s, " << expectedImages
                  << " expected images" << (t1 >= tCap ? " (beyond the AX22 cap)" : "") << "\n";
        ++gated;
    }
    std::cout << "one absorbing wall: t_on " << tOn << " s, AX22 cap at " << tCap << " s, " << gated
              << " gated bins, worst " << worst << " dB\n";
    CHECK(gated >= 3);
}
