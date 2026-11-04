// Contract v1 round trips: parse -> toJson -> parse gives an equal struct, and the second
// serialization is byte-identical to the first.
#include "ContractFixtures.h"

#include "contract/Json.h"
#include "contract/Parse.h"

#include <catch2/catch_test_macros.hpp>

#include <string>

namespace {

std::string issuesText(const contract::ParseResult& result)
{
    std::string text;
    for (const auto& issue : result.issues)
        text += contract::toString(issue) + "\n";
    return text;
}

} // namespace

TEST_CASE("there are at least 5 valid fixtures", "[contract][roundtrip]")
{
    REQUIRE(contract_fixtures::list("valid").size() >= 5);
}

TEST_CASE("every valid fixture parses without issues and round-trips", "[contract][roundtrip]")
{
    for (const auto& path : contract_fixtures::list("valid"))
    {
        INFO("fixture: " << path.filename().string());
        const auto first = contract::parseScene(contract_fixtures::read(path));
        INFO(issuesText(first));
        REQUIRE(first.ok());
        REQUIRE(first.issues.empty());

        const std::string json1 = contract::toJson(*first.scene);
        const auto second = contract::parseScene(json1);
        INFO(issuesText(second));
        REQUIRE(second.ok());
        CHECK(*second.scene == *first.scene);

        // serialize -> parse -> serialize gives the same bytes.
        const std::string json2 = contract::toJson(*second.scene);
        CHECK(json2 == json1);
    }
}

TEST_CASE("unknown extensions content is preserved", "[contract][roundtrip]")
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid/asymmetric_materials.json"));
    REQUIRE(parsed.ok());
    const std::string expected =
        R"({"module3d":{"ui":{"emitterColours":{"L":"#3b82f6","R":"#ef4444"},)"
        R"("cameraYawDeg":37.5},"notes":"asymmetric test room","tags":["test",1,true,null]}})";
    CHECK(parsed.scene->extensionsJson == expected);

    const auto again = contract::parseScene(contract::toJson(*parsed.scene));
    REQUIRE(again.ok());
    CHECK(again.scene->extensionsJson == expected);
}

TEST_CASE("doubles survive a round trip exactly", "[contract][roundtrip]")
{
    auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json"));
    REQUIRE(parsed.ok());
    contract::SceneDescription scene = *parsed.scene;
    // Values with no short decimal form need all 17 significant digits.
    scene.listener.position = {4.0 / 3.0, 3.0 + 1e-15, 1.7000000000000002};
    scene.emitters[0].gainDb = -0.1 * 3.0;
    scene.room.surface(contract::SurfaceId::yMax).bandsAbsorption[5] = 0.1 + 0.2;

    const auto reparsed = contract::parseScene(contract::toJson(scene));
    REQUIRE(reparsed.ok());
    CHECK(*reparsed.scene == scene);
}

TEST_CASE("a float with no fractional part is accepted where an integer is required", "[contract][roundtrip]")
{
    std::string json = contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json");
    const std::string from = "\"maxReflectionOrder\": 20";
    json.replace(json.find(from), from.size(), "\"maxReflectionOrder\": 20.0");
    const auto parsed = contract::parseScene(json);
    REQUIRE(parsed.ok());
    CHECK(parsed.scene->render.maxReflectionOrder == 20);
    CHECK(contract::toJson(*parsed.scene).find("\"maxReflectionOrder\": 20,") != std::string::npos);
}
