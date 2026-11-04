// Contract versioning: same major and any minor is read; a newer minor warns; a different major or
// a malformed version is rejected.
#include "ContractFixtures.h"

#include "contract/Parse.h"
#include "contract/Validate.h"
#include "contract/Version.h"

#include <catch2/catch_test_macros.hpp>

#include <string>

namespace {

std::string mediumRoomWithVersion(const std::string& version)
{
    std::string json = contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json");
    const std::string from = "\"contractVersion\": \"1.0\"";
    json.replace(json.find(from), from.size(), "\"contractVersion\": \"" + version + "\"");
    return json;
}

} // namespace

TEST_CASE("the current version is 1.0", "[contract][version]")
{
    CHECK(contract::kContractVersionMajor == 1);
    CHECK(contract::kContractVersionMinor == 0);
    CHECK(contract::toString(contract::kCurrentContractVersion) == contract::kContractVersion);
}

TEST_CASE("parseContractVersion accepts MAJOR.MINOR only", "[contract][version]")
{
    CHECK(contract::parseContractVersion("1.0") == contract::ContractVersion{1, 0});
    CHECK(contract::parseContractVersion("1.7") == contract::ContractVersion{1, 7});
    CHECK(contract::parseContractVersion("12.345") == contract::ContractVersion{12, 345});
    for (const char* bad : {"", "1", "x", "1.", ".1", "1.0.0", "01.0", "1.01", "-1.0", "1.-1", " 1.0", "1.0 ",
                            "+1.0", "1,0", "1.1234567890", "v1.0"})
    {
        INFO("version: \"" << bad << "\"");
        CHECK_FALSE(contract::parseContractVersion(bad).has_value());
    }
}

TEST_CASE("version 1.0 loads without issues", "[contract][version]")
{
    const auto result = contract::parseScene(mediumRoomWithVersion("1.0"));
    REQUIRE(result.ok());
    CHECK(result.issues.empty());
    CHECK(result.scene->contractVersion == contract::kCurrentContractVersion);
}

TEST_CASE("version 1.7 loads with a warning and ignores unknown fields", "[contract][version]")
{
    std::string json = mediumRoomWithVersion("1.7");
    // Fields a future 1.7 might add, at the root and nested.
    const std::string units = "\"units\": \"meters\"";
    json.replace(json.find(units), units.size(), units + ", \"speakerLayouts\": []");
    const std::string gain = "\"gainDb\": 0.0";
    json.replace(json.find(gain), gain.size(), gain + ", \"directivity\": \"cardioid\"");

    const auto result = contract::parseScene(json);
    REQUIRE(result.ok());
    REQUIRE(result.issues.size() == 1);
    CHECK(result.issues[0].code == contract::IssueCode::W_VERSION_MINOR_NEWER);
    CHECK(result.issues[0].severity() == contract::Severity::warning);
    CHECK(result.issues[0].path == "contractVersion");
    // The loaded value is a 1.0 scene: the unknown fields are gone.
    CHECK(result.scene->contractVersion == contract::kCurrentContractVersion);
    CHECK(contract::toJson(*result.scene).find("directivity") == std::string::npos);
}

TEST_CASE("version 1.7 still rejects semantic errors", "[contract][version]")
{
    std::string json = mediumRoomWithVersion("1.7");
    const std::string gain = "\"gainDb\": 0.0";
    json.replace(json.find(gain), gain.size(), "\"gainDb\": 40.0");
    const auto result = contract::parseScene(json);
    CHECK_FALSE(result.ok());
    REQUIRE(result.issues.size() == 2);
    CHECK(result.issues[0].code == contract::IssueCode::W_VERSION_MINOR_NEWER);
    CHECK(result.issues[1].code == contract::IssueCode::E_GAIN_RANGE);
}

TEST_CASE("versions 2.0 and 0.9 are rejected as another major version", "[contract][version]")
{
    for (const char* version : {"2.0", "0.9"})
    {
        INFO("version: " << version);
        const auto result = contract::parseScene(mediumRoomWithVersion(version));
        CHECK_FALSE(result.ok());
        REQUIRE(result.issues.size() == 1);
        CHECK(result.issues[0].code == contract::IssueCode::E_VERSION_MAJOR);
    }
}

TEST_CASE("versions 1 and x are rejected as malformed", "[contract][version]")
{
    for (const char* version : {"1", "x"})
    {
        INFO("version: " << version);
        const auto result = contract::parseScene(mediumRoomWithVersion(version));
        CHECK_FALSE(result.ok());
        REQUIRE(result.issues.size() == 1);
        CHECK(result.issues[0].code == contract::IssueCode::E_VERSION_FORMAT);
    }
}

TEST_CASE("a numeric contractVersion is a type error", "[contract][version]")
{
    std::string json = contract_fixtures::read(contract_fixtures::scenesDir() / "valid/medium_room.json");
    const std::string from = "\"contractVersion\": \"1.0\"";
    json.replace(json.find(from), from.size(), "\"contractVersion\": 1.0");
    const auto result = contract::parseScene(json);
    REQUIRE(result.issues.size() == 1);
    CHECK(result.issues[0].code == contract::IssueCode::E_TYPE);
}

TEST_CASE("validate() checks the version of an in-memory scene", "[contract][version]")
{
    const auto parsed = contract::parseScene(mediumRoomWithVersion("1.0"));
    REQUIRE(parsed.ok());
    auto scene = *parsed.scene;
    scene.contractVersion = {2, 0};
    REQUIRE(contract::validate(scene).issues.size() == 1);
    CHECK(contract::validate(scene).issues[0].code == contract::IssueCode::E_VERSION_MAJOR);
}
