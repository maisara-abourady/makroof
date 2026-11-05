// sim::buildRoomIR (Phase 02 stub) and the RoomIR layout.
#include "ContractFixtures.h"
#include "contract/Parse.h"
#include "sim/Engine.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

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

TEST_CASE("stub IR is a 2x2 pass-through: L -> output 0, R -> output 1", "[sim][engine]")
{
    const auto scene = loadScene("medium_room.json");
    for (const auto kind : {sim::BuildOptions::Kind::Omni, sim::BuildOptions::Kind::Binaural,
                            sim::BuildOptions::Kind::StereoSpeakers})
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
        CHECK_THROWS_AS(sim::buildRoomIR(scene, {rate, sim::BuildOptions::Kind::Omni}),
                        std::invalid_argument);
}

TEST_CASE("output modes map to build kinds", "[sim][engine]")
{
    CHECK(sim::kindForOutputMode(contract::OutputMode::binaural) == sim::BuildOptions::Kind::Binaural);
    CHECK(sim::kindForOutputMode(contract::OutputMode::stereoSpeakers)
          == sim::BuildOptions::Kind::StereoSpeakers);
}
