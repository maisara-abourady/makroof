// Smoke tests for the three JUCE-free libraries.
#include "contract/Version.h"
#include "module3d/SceneModel.h"
#include "sim/Simulator.h"

#include <catch2/catch_test_macros.hpp>

#include <string_view>

TEST_CASE("contract version string is non-empty", "[contract][smoke]")
{
    const std::string_view version{contract::kContractVersion};
    REQUIRE_FALSE(version.empty());
    REQUIRE(std::string_view{contract::contractVersion()} == version);
}

TEST_CASE("sim and module3d are built against the same contract", "[sim][module3d][smoke]")
{
    REQUIRE(std::string_view{sim::supportedContractVersion()} == contract::kContractVersion);
    REQUIRE(std::string_view{module3d::producedContractVersion()} == contract::kContractVersion);
}
