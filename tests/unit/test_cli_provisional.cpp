// Phase-07c-2b L4-P (decider file 10 Part A; interrogator file 13; Seat 5 file 14): render_cli's
// validation-only
// --provisional-ir, in-process through cli::runCli().
//   Test 7 (plugin parity, JUCE-free [pipeline]): on the L4 scene (stone_box.json with every absorption
//     coefficient times kL4), the IR a ScenePipeline submits at a keyless project load (the AX49 interim,
//     built synchronously by ScenePipeline's Source::Synchronous decision) is bit-identical to the IR that
//     `--provisional-ir --ir` writes.
//   Test 3 (default output unchanged, same runner): the default `--mode omni --ir` output is bit-identical to
//     sim::buildRoomIR, which no option code reaches.
//   r1: refused (exit 1) where L_p >= L, with no output file written.
// The end-to-end flag tests (determinism, the -120 dB null, r1-r5, the handover) are
// tools/ci/test_provisional_flag.py.
#include "ContractFixtures.h"
#include "DiffuseTestUtil.h"
#include "PipelineTestUtil.h"

#include "cli/Cli.h"
#include "cli/WavIO.h"
#include "contract/Json.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/ScenePipeline.h"
#include "sim/Engine.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace {

constexpr double kRate = 48000.0;
// L4-S: the factor on stone_box's absorption that makes T60_max 8.0 +/- 0.1 s (7.9955 s at 63 Hz, measured
// with
// --provisional-timing; builder file 15). The same constant as tools/ci/test_provisional_flag.py K_L4.
constexpr double kL4 = 0.84;

struct TempDir
{
    fs::path path;
    TempDir()
    {
        static std::atomic<int> counter{0};
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        path = fs::temp_directory_path()
               / ("spatial_cli_provisional_" + std::to_string(stamp) + "_" + std::to_string(counter++));
        fs::create_directories(path);
    }
    ~TempDir()
    {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;
};

int runCli(const std::vector<std::string>& args, std::string* err = nullptr)
{
    std::ostringstream out, e;
    const int code = cli::runCli(args, out, e);
    if (err != nullptr)
        *err = e.str();
    return code;
}

void writeScene(const fs::path& path, const contract::SceneDescription& scene)
{
    std::ofstream os(path, std::ios::binary);
    os << contract::toJson(scene);
    REQUIRE(os.good());
}

contract::SceneDescription l4Scene()
{
    auto scene = pipeline_test::loadScene("stone_box.json");
    for (auto& surface : scene.room.surfaces)
        for (auto& a : surface.bandsAbsorption)
            a *= kL4;
    return scene;
}

// The IR as render_cli wrote it (float32 WAV, channel = emitter * outputs + output).
bool sameTaps(const sim::RoomIR& ir, const cli::Audio& wav)
{
    if (ir.taps.size() != wav.channels.size())
        return false;
    for (std::size_t c = 0; c < ir.taps.size(); ++c)
        if (ir.taps[c].size() != wav.channels[c].size()
            || (!ir.taps[c].empty()
                && std::memcmp(ir.taps[c].data(), wav.channels[c].data(), ir.taps[c].size() * sizeof(float))
                       != 0))
            return false;
    return true;
}

} // namespace

TEST_CASE(
    "L4-P test 7: the keyless-load interim IR of ScenePipeline is bit-identical to --provisional-ir --ir",
    "[pipeline][cli][provisional]")
{
    const auto l4 = l4Scene();
    plugin::ScenePipeline p;
    p.prepare(kRate, 256, false);
    REQUIRE(pipeline_test::waitFor([&] { return !p.settling() && p.builderIdle(); }));
    const auto before = p.stats();
    p.beginRestore();
    p.restore(l4, module3d::parameterValuesFromScene(l4), std::nullopt); // a project load: keyless (AX48)
    const auto interim = p.lastSubmittedIr();
    REQUIRE(interim != nullptr);
    const auto after = p.stats();
    REQUIRE(after.keylessLoads == before.keylessLoads + 1);
    REQUIRE(after.provisionalSubmits == before.provisionalSubmits + 1);

    // The CLI on the scene the pipeline actually built (the parameter round trip may quantise the scene).
    const auto loaded = p.currentScene();
    for (std::size_t f = 0; f < 6; ++f)
        CHECK(loaded.room.surfaces[f].bandsAbsorption == l4.room.surfaces[f].bandsAbsorption);
    auto timing = sim::StagedBuild::plan(loaded,
                                         [] {
                                             sim::BuildOptions o;
                                             o.sampleRate = kRate;
                                             o.kind = sim::BuildOptions::Kind::Omni;
                                             return o;
                                         }())
                      .provisionalTiming();
    REQUIRE(timing.provisional);
    REQUIRE(timing.t60MaxS >= 7.9);
    REQUIRE(timing.t60MaxS <= 8.1);

    TempDir dir;
    writeScene(dir.path / "l4.json", loaded);
    const auto irPath = (dir.path / "provisional.wav").string();
    REQUIRE(runCli({"--scene", (dir.path / "l4.json").string(), "--mode", "omni", "--provisional-ir", "--ir",
                    irPath})
            == cli::kExitOk);
    cli::Audio wav;
    std::string error;
    REQUIRE(cli::readWav(irPath, wav, error));
    REQUIRE(wav.sampleRate == static_cast<std::uint32_t>(kRate));
    REQUIRE(sameTaps(*interim, wav));
    // ... and it is the provisional, not the exact IR (shorter: it ends at L_p).
    REQUIRE(interim->length() < plugin::ScenePipeline::buildIr(loaded, kRate).length());
    REQUIRE(pipeline_test::waitFor([&] { return !p.settling() && p.builderIdle(); }));
}

TEST_CASE("L4-P test 3: the default --mode omni --ir output is bit-identical to sim::buildRoomIR",
          "[cli][provisional]")
{
    TempDir dir;
    const auto medium = (contract_fixtures::scenesDir() / "valid" / "medium_room.json").string();
    const auto irPath = (dir.path / "default.wav").string();
    REQUIRE(runCli({"--scene", medium, "--mode", "omni", "--ir", irPath}) == cli::kExitOk);
    cli::Audio wav;
    std::string error;
    REQUIRE(cli::readWav(irPath, wav, error));
    sim::BuildOptions o;
    o.sampleRate = kRate;
    o.kind = sim::BuildOptions::Kind::Omni;
    REQUIRE(sameTaps(sim::buildRoomIR(pipeline_test::loadScene("medium_room.json"), o), wav));
}

TEST_CASE("L4-P r1: --provisional-ir is refused where L_p >= L, before any output file is opened",
          "[cli][provisional]")
{
    // AX49's L_p >= L scene: the 100 m low-alpha cube of the records (alpha 0.05, s 0.3).
    std::array<contract::BandArray, 6> alpha{};
    alpha.fill(diffuse_test::flat(0.05));
    std::array<double, 6> s{};
    s.fill(0.3);
    auto cube = diffuse_test::scene({100.0, 100.0, 100.0}, alpha, s, {50.0, 30.0, 1.7},
                                    {{45.0, 70.0, 2.0}, {55.0, 70.0, 2.0}});
    TempDir dir;
    writeScene(dir.path / "cube.json", cube);
    std::string err;
    const auto out = dir.path / "out";
    fs::create_directories(out);
    REQUIRE(runCli({"--scene", (dir.path / "cube.json").string(), "--mode", "omni", "--provisional-ir",
                    "--ir", (out / "ir.wav").string(), "--images", (out / "images.json").string(),
                    "--provisional-timing", (out / "timing.json").string()},
                   &err)
            == cli::kExitUsage);
    CHECK(err.find("does not apply to this scene") != std::string::npos);
    CHECK(fs::is_empty(out));
    CHECK(cli::usage().find("--provisional-ir") != std::string::npos);
    CHECK(cli::usage().find("not its timing") != std::string::npos);
}
