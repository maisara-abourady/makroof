// sim::buildRoomIR(Kind::Omni): the Phase 04 hybrid room IR (ISM early part + stochastic tail).
// The acoustic gates (T30 vs Eyring, seed and sample-rate ensembles, the EDC seam test, goldens)
// run in Python: tools/acoustics/tests/test_tail.py.
#include "ContractFixtures.h"
#include "contract/Parse.h"
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
#include <set>
#include <stdexcept>
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
    // After the fade nothing of the early part is left: with E_b = 0 the IR would be silent there.
    auto silent = scene;
    for (auto& s : silent.room.surfaces)
        s.bandsAbsorption.fill(1.0);
    const auto dry = sim::buildRoomIR(silent, kOmni48);
    CHECK(energy(dry.ir(0, 0), static_cast<std::size_t>(0.1 * 48000.0)) == 0.0);
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

// Phase-04 benchmark (AQ10: IR rebuild <= 50 ms for order <= 30 in a 20 x 30 x 10 m room; with AX20
// the hybrid list is time-bounded, so the order no longer applies). Recorded, not optimized.
TEST_CASE("benchmark: hybrid omni IR, 20 x 30 x 10 m, 48 kHz, 2 emitters", "[.][benchmark]")
{
    auto scene = loadScene("medium_room.json");
    scene.room.geometry.dimensions = {20.0, 30.0, 10.0};
    scene.listener.position = {10.0, 8.0, 1.7};
    scene.emitters[0].position = {7.0, 20.0, 2.0};
    scene.emitters[1].position = {13.0, 20.0, 2.0};
    sim::HybridDiagnostics d;
    const auto start = std::chrono::steady_clock::now();
    const auto ir = sim::buildRoomIR(scene, kOmni48, &d);
    const auto stop = std::chrono::steady_clock::now();
    std::cout << "phase-04 benchmark: " << d.emitters[0].imageCount + d.emitters[1].imageCount
              << " images (AX20), t_mix " << d.emitters[0].match.mixing.mixS * 1000.0 << " ms, IR "
              << ir.length() << " samples (" << static_cast<double>(ir.length()) / 48000.0
              << " s), one build " << std::chrono::duration<double, std::milli>(stop - start).count()
              << " ms (AQ10 target 50 ms)\n";
    BENCHMARK("buildRoomIR omni (hybrid)")
    {
        return sim::buildRoomIR(scene, kOmni48);
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
