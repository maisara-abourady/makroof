// Phase 07 scope 1: the 3D Module's editable scene. Every setter clamps, so toContract() always
// validates; editor-only data survives in `extensions`.
#include "ContractFixtures.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "module3d/SceneModel.h"

#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <limits>
#include <random>

// Exact comparisons are intended (exact endpoints, bit-identical scenes, D9/D1).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

contract::SceneDescription mediumRoom()
{
    auto parsed = contract::fromJson(
        contract_fixtures::read(contract_fixtures::scenesDir() / "valid" / "medium_room.json"));
    REQUIRE(parsed.ok());
    return *parsed.scene;
}

bool validates(const contract::SceneDescription& s)
{
    return contract::validate(s).ok();
}

} // namespace

TEST_CASE("SceneModel: a valid scene is kept as is", "[module3d][scene-model]")
{
    const auto scene = mediumRoom();
    const module3d::SceneModel model(scene);
    REQUIRE(model.toContract() == scene);
    REQUIRE(validates(model.toContract()));
}

TEST_CASE("SceneModel: setters clamp every input to a valid scene", "[module3d][scene-model]")
{
    std::mt19937_64 rng(20261108);
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();
    const std::vector<double> specials{nan, inf, -inf, -1e9, 1e9, 0.0, -0.0, 0.1, 0.3, 1.5, 100.0, 100.0001};
    std::uniform_real_distribution<double> wide(-20.0, 140.0);
    std::uniform_int_distribution<std::size_t> pick(0, specials.size() - 1);
    std::bernoulli_distribution special(0.2);
    const auto draw = [&] { return special(rng) ? specials[pick(rng)] : wide(rng); };

    module3d::SceneModel model(mediumRoom());
    for (int i = 0; i < 5000; ++i)
    {
        switch (i % 7)
        {
        case 0:
            model.setRoomDimensions({draw(), draw(), draw()});
            break;
        case 1:
            model.setListenerPosition({draw(), draw(), draw()});
            break;
        case 2:
            model.setEmitterPosition(0, {draw(), draw(), draw()});
            break;
        case 3:
            model.setEmitterPosition(1, model.scene().listener.position); // e = l: pushed 0.3 m away
            break;
        case 4:
            model.setEmitterGainDb(i % 2, draw());
            break;
        case 5:
        {
            contract::SurfaceMaterial m;
            for (auto& a : m.bandsAbsorption)
                a = draw() / 100.0;
            m.scattering = draw() / 100.0;
            model.setSurfaceMaterial(contract::kAllSurfaces[static_cast<std::size_t>(i) % 6], m);
            break;
        }
        default:
            model.setMaxReflectionOrder(static_cast<int>(std::lround(std::isfinite(draw()) ? draw() : 0.0)));
            model.setTailSeed(static_cast<std::uint32_t>(rng()));
            break;
        }
        const auto result = contract::validate(model.toContract());
        INFO("step " << i << ": " << (result.issues.empty() ? "" : result.issues.front().message));
        REQUIRE(result.ok());
    }
}

TEST_CASE("SceneModel: sanitize repairs an arbitrary scene", "[module3d][scene-model]")
{
    contract::SceneDescription bad;
    bad.room.geometry.dimensions = {0.2, std::numeric_limits<double>::quiet_NaN(), 1e6};
    bad.listener.position = {-5.0, 7.0, 99.0};
    bad.emitters.clear(); // AX7 emitters added
    bad.render.maxReflectionOrder = 1000;
    bad.render.hrtfId = "other";
    bad.extensionsJson = "[1, 2]";
    const auto fixed = module3d::SceneModel::sanitize(bad);
    REQUIRE(validates(fixed));
    REQUIRE(fixed.emitters.size() == 2);
    REQUIRE(fixed.emitters[0].id == "L");
    REQUIRE(fixed.emitters[0].channel == 0);
    REQUIRE(fixed.emitters[1].id == "R");
    REQUIRE(fixed.emitters[1].channel == 1);
    REQUIRE(fixed.extensionsJson == "{}");
}

TEST_CASE("SceneModel: editor-only data survives in extensions", "[module3d][scene-model]")
{
    module3d::SceneModel model(mediumRoom());
    const std::string ext = R"({"camera":{"yaw":30},"colour":"#ff0000"})";
    model.setExtensionsJson(ext);
    model.setRoomDimensions({5.0, 6.0, 3.0});
    model.setListenerPosition({2.0, 2.0, 1.5});
    model.setEmitterPosition(0, {2.1, 2.0, 1.5});
    REQUIRE(model.toContract().extensionsJson == ext);
    REQUIRE(validates(model.toContract()));

    model.setExtensionsJson("not json");
    REQUIRE(model.toContract().extensionsJson == "{}");
}
