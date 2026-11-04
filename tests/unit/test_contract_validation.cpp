// Contract v1 validation: every invalid fixture yields exactly its expected code (the file name),
// and the inclusive edge values are valid.
#include "ContractFixtures.h"

#include "contract/Diagnostics.h"
#include "contract/Parse.h"
#include "contract/Validate.h"

#include <catch2/catch_test_macros.hpp>

#include <limits>
#include <set>
#include <string>

namespace {

contract::SceneDescription mediumRoom()
{
    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json"));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

std::string issuesText(const std::vector<contract::Issue>& issues)
{
    std::string text;
    for (const auto& issue : issues)
        text += contract::toString(issue) + "\n";
    return text;
}

std::vector<contract::Issue> errorsOf(const contract::SceneDescription& scene)
{
    return contract::validate(scene).issues;
}

} // namespace

TEST_CASE("there are at least 15 invalid fixtures", "[contract][validation]")
{
    REQUIRE(contract_fixtures::list("invalid").size() >= 15);
}

TEST_CASE("every invalid fixture yields exactly its expected code", "[contract][validation]")
{
    for (const auto& path : contract_fixtures::list("invalid"))
    {
        const std::string name = path.stem().string();
        INFO("fixture: " << path.filename().string());
        const auto expected = contract::codeFromName(name);
        REQUIRE(expected.has_value()); // the file name must be an error code
        REQUIRE(contract::severityOf(*expected) == contract::Severity::error);

        const auto result = contract::parseScene(contract_fixtures::read(path));
        INFO(issuesText(result.issues));
        CHECK_FALSE(result.ok());
        CHECK_FALSE(result.scene.has_value());
        REQUIRE(result.issues.size() == 1);
        CHECK(result.issues[0].code == *expected);
        CHECK_FALSE(result.issues[0].message.empty());
    }
}

TEST_CASE("every error code that a document can trigger has an invalid fixture", "[contract][validation]")
{
    std::set<std::string> fixtures;
    for (const auto& path : contract_fixtures::list("invalid"))
        fixtures.insert(path.stem().string());
    for (const auto code : contract::allIssueCodes())
    {
        // Not reachable from a JSON document: a warning, an internal failure, and a check that only
        // applies to in-memory scenes.
        if (code == contract::IssueCode::W_VERSION_MINOR_NEWER || code == contract::IssueCode::E_INTERNAL
            || code == contract::IssueCode::E_EXTENSIONS)
            continue;
        INFO("code: " << contract::codeName(code));
        CHECK(fixtures.count(std::string{contract::codeName(code)}) == 1);
    }
}

TEST_CASE("issue codes have unique names that round-trip", "[contract][validation]")
{
    std::set<std::string_view> names;
    for (const auto code : contract::allIssueCodes())
    {
        const auto name = contract::codeName(code);
        REQUIRE_FALSE(name.empty());
        REQUIRE_FALSE(contract::codeMeaning(code).empty());
        CHECK(names.insert(name).second);
        CHECK(contract::codeFromName(name) == code);
    }
    CHECK_FALSE(contract::codeFromName("E_NOT_A_CODE").has_value());
}

TEST_CASE("errors carry the JSON path of the offending value", "[contract][validation]")
{
    auto scene = mediumRoom();
    scene.room.surface(contract::SurfaceId::floor).bandsAbsorption[3] = 1.2;
    const auto issues = errorsOf(scene);
    REQUIRE(issues.size() == 1);
    CHECK(issues[0].code == contract::IssueCode::E_ABSORPTION_RANGE);
    CHECK(issues[0].path == "room.surfaces.floor.absorption[3]");

    const auto parsed = contract::parseScene(
        contract_fixtures::read(contract_fixtures::scenesDir() / "invalid/E_UNKNOWN_FIELD.json"));
    REQUIRE(parsed.issues.size() == 1);
    CHECK(parsed.issues[0].path == "emitters[0].gainDB");
}

TEST_CASE("edge values are valid", "[contract][validation]")
{
    SECTION("absorption 0.01 and 1.0, scattering 0 and 1")
    {
        auto scene = mediumRoom();
        scene.room.surface(contract::SurfaceId::floor).bandsAbsorption.fill(0.01);
        scene.room.surface(contract::SurfaceId::ceiling).bandsAbsorption.fill(1.0);
        scene.room.surface(contract::SurfaceId::floor).scattering = 0.0;
        scene.room.surface(contract::SurfaceId::ceiling).scattering = 1.0;
        CHECK(errorsOf(scene).empty());
    }
    SECTION("emitter exactly 0.3 m from the listener")
    {
        auto scene = mediumRoom(); // listener at (4, 3, 1.7)
        scene.emitters[0].position = {4.0, 3.3, 1.7};
        scene.emitters[1].position = {4.3, 3.0, 1.7};
        INFO(issuesText(errorsOf(scene)));
        CHECK(errorsOf(scene).empty());
    }
    SECTION("listener and emitters exactly 0.1 m from surfaces")
    {
        auto scene = mediumRoom(); // 8 x 12 x 4
        scene.listener.position = {0.1, 0.1, 0.1};
        scene.emitters[0].position = {7.9, 11.9, 3.9};
        scene.emitters[1].position = {0.1, 11.9, 0.1};
        INFO(issuesText(errorsOf(scene)));
        CHECK(errorsOf(scene).empty());
    }
    SECTION("gain, reflection order and room size limits")
    {
        auto scene = mediumRoom();
        scene.emitters[0].gainDb = -60.0;
        scene.emitters[1].gainDb = 12.0;
        scene.render.maxReflectionOrder = 60;
        scene.room.geometry.dimensions = {100.0, 12.0, 4.0};
        CHECK(errorsOf(scene).empty());
        scene.render.maxReflectionOrder = 0;
        scene.room.geometry.dimensions = {8.0, 12.0, 4.0};
        CHECK(errorsOf(scene).empty());
    }
}

TEST_CASE("values just past the limits are rejected", "[contract][validation]")
{
    using contract::IssueCode;
    const auto onlyCode = [](const contract::SceneDescription& scene) {
        const auto issues = errorsOf(scene);
        INFO(issuesText(issues));
        REQUIRE(issues.size() == 1);
        return issues[0].code;
    };
    auto scene = mediumRoom();
    scene.room.surface(contract::SurfaceId::xMin).bandsAbsorption[0] = 0.0099;
    CHECK(onlyCode(scene) == IssueCode::E_ABSORPTION_RANGE);

    scene = mediumRoom();
    scene.room.surface(contract::SurfaceId::xMin).scattering = -0.01;
    CHECK(onlyCode(scene) == IssueCode::E_SCATTERING_RANGE);

    scene = mediumRoom();
    scene.emitters[0].position = {4.0, 3.299, 1.7};
    CHECK(onlyCode(scene) == IssueCode::E_EMITTER_TOO_CLOSE_TO_LISTENER);

    scene = mediumRoom();
    scene.listener.position = {4.0, 3.0, 3.91};
    CHECK(onlyCode(scene) == IssueCode::E_LISTENER_SURFACE_CLEARANCE);

    scene = mediumRoom();
    scene.emitters[1].gainDb = -60.5;
    CHECK(onlyCode(scene) == IssueCode::E_GAIN_RANGE);

    scene = mediumRoom();
    scene.render.maxReflectionOrder = -1;
    CHECK(onlyCode(scene) == IssueCode::E_REFLECTION_ORDER_RANGE);

    scene = mediumRoom();
    scene.room.geometry.dimensions.x = 1.49;
    CHECK(onlyCode(scene) == IssueCode::E_ROOM_DIMENSION_RANGE);
}

TEST_CASE("NaN values are rejected", "[contract][validation]")
{
    auto scene = mediumRoom();
    scene.emitters[0].gainDb = std::numeric_limits<double>::quiet_NaN();
    scene.room.surface(contract::SurfaceId::floor).scattering = std::numeric_limits<double>::quiet_NaN();
    scene.listener.position.x = std::numeric_limits<double>::quiet_NaN();
    CHECK(errorsOf(scene).size() == 3);
}

TEST_CASE("in-memory extensions text must be a JSON object", "[contract][validation]")
{
    auto scene = mediumRoom();
    scene.extensionsJson = "[1, 2]";
    const auto issues = errorsOf(scene);
    REQUIRE(issues.size() == 1);
    CHECK(issues[0].code == contract::IssueCode::E_EXTENSIONS);
}

TEST_CASE("the L/R channel assignment may be swapped", "[contract][validation]")
{
    // AX7 only asks that ids L, R and channels 0, 1 are each used once.
    auto scene = mediumRoom();
    scene.emitters[0].channel = 1;
    scene.emitters[1].channel = 0;
    CHECK(errorsOf(scene).empty());
}

TEST_CASE("several mistakes in one document are all reported", "[contract][validation]")
{
    std::string json = contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json");
    const auto replace = [&json](const std::string& from, const std::string& to) {
        json.replace(json.find(from), from.size(), to);
    };
    replace("\"units\": \"meters\"", "\"units\": \"meters\", \"colour\": 1");
    replace("\"hrtfId\": \"generic-v1\"", "\"hrtfId\": 7");
    const auto result = contract::parseScene(json);
    REQUIRE(result.issues.size() == 2);
    CHECK(result.issues[0].code == contract::IssueCode::E_UNKNOWN_FIELD);
    CHECK(result.issues[1].code == contract::IssueCode::E_TYPE);
    CHECK(result.issues[1].path == "render.hrtfId");
}

TEST_CASE("parseScene never throws on hostile input", "[contract][validation]")
{
    for (const char* text : {"", "null", "[]", "42", "\"scene\"", "{", "{\"contractVersion\": 1.0}",
                             "{\"contractVersion\": \"1.0\"}", "{\"a\": 1e999}", "\xff\xfe"})
    {
        INFO("input: " << text);
        const auto result = contract::parseScene(text);
        CHECK_FALSE(result.ok());
        CHECK_FALSE(result.issues.empty());
    }
}
