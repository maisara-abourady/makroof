// sim::buildRoomIR: the omni early-reflection IR (Kind::OmniEarly, Phase 03, unchanged in Phase 04),
// the binaural/stereo stub (Phase 02) and the RoomIR layout. The hybrid IR (Kind::Omni, Phase 04)
// is tested in test_hybrid_ir.cpp.
#include "ContractFixtures.h"
#include "contract/Parse.h"
#include "sim/Engine.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "sim/ism/BandRenderer.h"

#include <catch2/benchmark/catch_benchmark.hpp>

#include <chrono>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

contract::SceneDescription loadScene(const std::string& name)
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / name));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

} // namespace

TEST_CASE("binaural/stereo stub IR is a 2x2 pass-through: L -> output 0, R -> output 1", "[sim][engine]")
{
    const auto scene = loadScene("medium_room.json");
    for (const auto kind : {sim::BuildOptions::Kind::Binaural, sim::BuildOptions::Kind::StereoSpeakers})
    {
        for (const double rate : sim::kSupportedSampleRatesHz)
        {
            const sim::RoomIR ir = sim::buildRoomIR(scene, {rate, kind});
            CHECK_THAT(ir.sampleRate, Catch::Matchers::WithinAbs(rate, 0.0));
            REQUIRE(ir.numEmitters == 2);
            REQUIRE(ir.numOutputs == 2);
            REQUIRE(ir.taps.size() == 4);
            CHECK(ir.length() == 1);
            // medium_room: L is channel 0, R is channel 1.
            CHECK(ir.ir(0, 0) == std::vector<float>{1.0f});
            CHECK(ir.ir(0, 1) == std::vector<float>{0.0f});
            CHECK(ir.ir(1, 0) == std::vector<float>{0.0f});
            CHECK(ir.ir(1, 1) == std::vector<float>{1.0f});
        }
    }
}

TEST_CASE("stub IR follows the emitter ids when channels are swapped (AX10)", "[sim][engine]")
{
    auto scene = loadScene("medium_room.json");
    for (auto& emitter : scene.emitters)
        emitter.channel = 1 - emitter.channel;
    const sim::RoomIR ir = sim::buildRoomIR(scene, {48000.0, sim::BuildOptions::Kind::Binaural});
    // Input channel 0 now feeds R, which goes to output 1.
    CHECK(ir.ir(0, 0) == std::vector<float>{0.0f});
    CHECK(ir.ir(0, 1) == std::vector<float>{1.0f});
    CHECK(ir.ir(1, 0) == std::vector<float>{1.0f});
    CHECK(ir.ir(1, 1) == std::vector<float>{0.0f});
}

TEST_CASE("buildRoomIR rejects unsupported sample rates (AX6)", "[sim][engine]")
{
    const auto scene = loadScene("small_room.json");
    for (const double rate : {0.0, 22050.0, 32000.0, 47999.0, 192000.0})
        CHECK_THROWS_AS(sim::buildRoomIR(scene, {rate, sim::BuildOptions::Kind::OmniEarly}),
                        std::invalid_argument);
}

TEST_CASE("output modes map to build kinds", "[sim][engine]")
{
    CHECK(sim::kindForOutputMode(contract::OutputMode::binaural) == sim::BuildOptions::Kind::Binaural);
    CHECK(sim::kindForOutputMode(contract::OutputMode::stereoSpeakers)
          == sim::BuildOptions::Kind::StereoSpeakers);
}

namespace {

double energy(const std::vector<float>& x)
{
    double e = 0.0;
    for (const float v : x)
        e += static_cast<double>(v) * v;
    return e;
}

std::size_t peakIndex(const std::vector<float>& x)
{
    std::size_t peak = 0;
    for (std::size_t n = 0; n < x.size(); ++n)
        if (std::abs(x[n]) > std::abs(x[peak]))
            peak = n;
    return peak;
}

} // namespace

TEST_CASE("omni IR: both outputs of an emitter are the same; the earliest direct path is at the pre-roll",
          "[sim][engine][omni]")
{
    for (const char* name : {"small_room.json", "medium_room.json", "open_field.json", "large_hall.json"})
    {
        INFO(name);
        const auto scene = loadScene(name);
        for (const double rate : sim::kSupportedSampleRatesHz)
        {
            const sim::RoomIR ir = sim::buildRoomIR(scene, {rate, sim::BuildOptions::Kind::OmniEarly});
            REQUIRE(ir.numEmitters == 2);
            REQUIRE(ir.numOutputs == 2);
            CHECK(ir.ir(0, 0) == ir.ir(0, 1));
            CHECK(ir.ir(1, 0) == ir.ir(1, 1));
            // Both emitters of these fixtures are equidistant from the listener: both direct paths at 32.
            CHECK(peakIndex(ir.ir(0, 0)) == static_cast<std::size_t>(sim::kAlignPreRollSamples));
            CHECK(peakIndex(ir.ir(1, 0)) == static_cast<std::size_t>(sim::kAlignPreRollSamples));
            // Before the first arrival's kernel there is only the filterbank's linear-phase
            // pre-ringing of later reflections whose per-band gains differ. Measured worst case over
            // the fixtures at their own orders (48 kHz): -46.7 dB (large_hall), -49.1 dB
            // (open_field). The cut at sample 0 leaves a step of at most -52 dB. Bound for both,
            // on both emitters: 40 dB below the direct peak.
            for (int e = 0; e < 2; ++e)
            {
                const auto& taps = ir.ir(e, 0);
                const float peak = std::abs(taps[peakIndex(taps)]);
                for (std::size_t n = 0; n + 16 < static_cast<std::size_t>(sim::kAlignPreRollSamples); ++n)
                    CHECK(std::abs(taps[n]) < 1e-2f * peak);
            }
        }
    }
}

TEST_CASE("omni IR keeps relative delays and 1/r level (AX1, AX2)", "[sim][engine][omni]")
{
    auto scene = loadScene("medium_room.json");
    scene.render.maxReflectionOrder = 0;
    scene.emitters[0].position = {4.0, 5.0, 1.7};  // 2 m in front of the listener at (4, 3, 1.7)
    scene.emitters[1].position = {4.0, 7.43, 1.7}; // 4.43 m
    const double fs = 48000.0;
    auto options = sim::BuildOptions{fs, sim::BuildOptions::Kind::OmniEarly};
    options.airAbsorption = false;
    const sim::RoomIR ir = sim::buildRoomIR(scene, options);
    CHECK(peakIndex(ir.ir(0, 0)) == 32);
    const double expected = 32.0 + 2.43 / sim::ism::kSpeedOfSoundMps * fs; // 372.03...
    CHECK(peakIndex(ir.ir(1, 0)) == static_cast<std::size_t>(std::lround(expected)));
    // Without air absorption all bands are equal, so a direct path is the bare kernel: integer
    // delay -> exact delta of height 1/r.
    CHECK_THAT(ir.ir(0, 0)[32], Catch::Matchers::WithinRel(0.5, 1e-6));
    // Gain: +6.0206 dB doubles the IR.
    scene.emitters[0].gainDb = 20.0 * std::log10(2.0);
    const sim::RoomIR louder = sim::buildRoomIR(scene, options);
    CHECK_THAT(louder.ir(0, 0)[32], Catch::Matchers::WithinRel(1.0, 1e-6));
}

TEST_CASE("omni IR follows the channels when they are swapped (AX10)", "[sim][engine][omni]")
{
    auto scene = loadScene("medium_room.json");
    scene.emitters[0].position.x = 2.0; // make L and R differ
    const sim::BuildOptions options{48000.0, sim::BuildOptions::Kind::OmniEarly};
    const auto a = sim::buildRoomIR(scene, options);
    for (auto& emitter : scene.emitters)
        emitter.channel = 1 - emitter.channel;
    const auto b = sim::buildRoomIR(scene, options);
    CHECK(a.ir(0, 0) == b.ir(1, 0));
    CHECK(a.ir(1, 0) == b.ir(0, 0));
}

TEST_CASE("omni IR is deterministic", "[sim][engine][omni]")
{
    const auto scene = loadScene("asymmetric_materials.json");
    const sim::BuildOptions options{44100.0, sim::BuildOptions::Kind::OmniEarly};
    const auto a = sim::buildRoomIR(scene, options);
    const auto b = sim::buildRoomIR(scene, options);
    CHECK(a.taps == b.taps);
}

TEST_CASE("omni IR: all a = 1 or order 0 gives the direct path only", "[sim][engine][omni]")
{
    auto scene = loadScene("small_room.json");
    auto direct = scene;
    direct.render.maxReflectionOrder = 0;
    const sim::BuildOptions options{48000.0, sim::BuildOptions::Kind::OmniEarly};
    const auto reference = sim::buildRoomIR(direct, options);
    const auto images = sim::imageSourcesByChannel(direct, options);
    REQUIRE(images[0].images.size() == 1);

    for (auto& surface : scene.room.surfaces)
        surface.bandsAbsorption.fill(1.0);
    const auto absorbing = sim::buildRoomIR(scene, options);
    CHECK(absorbing.taps == reference.taps);

    // The reference is the direct path's own render (and nothing else).
    const sim::ism::OctaveFilterbank fb(48000.0);
    const auto own = sim::ism::renderImageSources(images[0].images, sim::alignmentShiftS(direct, 48000.0),
                                                  fb);
    REQUIRE(own.size() <= reference.length());
    for (std::size_t n = 0; n < own.size(); ++n)
        CHECK_THAT(reference.ir(0, 0)[n], Catch::Matchers::WithinULP(static_cast<float>(own[n]), 0));
}

TEST_CASE("omni IR length: last arrival + kernel + filterbank ringing", "[sim][engine][omni]")
{
    const auto scene = loadScene("medium_room.json");
    const double fs = 96000.0;
    const sim::BuildOptions options{fs, sim::BuildOptions::Kind::OmniEarly};
    const auto ir = sim::buildRoomIR(scene, options);
    const auto sets = sim::imageSourcesByChannel(scene, options);
    double last = 0.0;
    for (const auto& set : sets)
        last = std::max(last, set.images.back().arrivalTimeS);
    const sim::ism::OctaveFilterbank fb(fs);
    const double lastSample = (last - sim::alignmentShiftS(scene, fs)) * fs;
    CHECK(ir.length() == static_cast<std::size_t>(std::ceil(lastSample)) + 16 + fb.maxHalfLength() + 1);
    CHECK(energy(ir.ir(0, 0)) > 0.0);
}

// Phase-03 benchmark (AQ10 target: IR rebuild <= 50 ms for order <= 30 in a 20 x 30 x 10 m room).
// Hidden: CI runs it from the Release build with `spatial_tests "[benchmark]"`.
TEST_CASE("benchmark: omni IR, order 30, 20 x 30 x 10 m, 48 kHz, 2 emitters", "[.][benchmark]")
{
    auto scene = loadScene("medium_room.json");
    scene.room.geometry.dimensions = {20.0, 30.0, 10.0};
    scene.listener.position = {10.0, 8.0, 1.7};
    scene.emitters[0].position = {7.0, 20.0, 2.0};
    scene.emitters[1].position = {13.0, 20.0, 2.0};
    scene.render.maxReflectionOrder = 30;
    const sim::BuildOptions options{48000.0, sim::BuildOptions::Kind::OmniEarly};

    const auto start = std::chrono::steady_clock::now();
    const auto ir = sim::buildRoomIR(scene, options);
    const auto stop = std::chrono::steady_clock::now();
    const auto sets = sim::imageSourcesByChannel(scene, options);
    std::cout << "phase-03 benchmark: " << sets[0].images.size() + sets[1].images.size() << " images, IR "
              << ir.length() << " samples, one build "
              << std::chrono::duration<double, std::milli>(stop - start).count()
              << " ms (AQ10 target 50 ms)\n";

    // Contract maximum (phase-03 Risks): one build at order 60, timed once.
    auto order60 = scene;
    order60.render.maxReflectionOrder = 60;
    const auto start60 = std::chrono::steady_clock::now();
    const auto ir60 = sim::buildRoomIR(order60, options);
    const auto stop60 = std::chrono::steady_clock::now();
    std::cout << "phase-03 benchmark, order 60 (contract maximum): " << 2 * sim::ism::imageCount(60)
              << " images, IR " << ir60.length() << " samples, one build "
              << std::chrono::duration<double, std::milli>(stop60 - start60).count() << " ms\n";

    BENCHMARK("image sources only (2 emitters)")
    {
        return sim::imageSourcesByChannel(scene, options);
    };
    BENCHMARK("buildRoomIR omni-early")
    {
        return sim::buildRoomIR(scene, options);
    };
}
