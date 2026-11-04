// render_cli, run in-process through cli::runCli() so it is covered on every OS. The Linux python
// job also runs the real binary end to end (tools/acoustics/tests/test_render_cli.py).
#include "ContractFixtures.h"
#include "cli/Cli.h"
#include "cli/WavIO.h"

#include <catch2/catch_test_macros.hpp>

#include <atomic>
#include <chrono>
#include <cstring>
#include <filesystem>
#include <random>
#include <sstream>

namespace fs = std::filesystem;

namespace {

// A fresh directory under the system temp dir, removed when the object goes away.
struct TempDir
{
    fs::path path;
    TempDir()
    {
        static std::atomic<int> counter{0};
        const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
        path = fs::temp_directory_path()
               / ("spatial_cli_test_" + std::to_string(stamp) + "_" + std::to_string(counter++));
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

struct Run
{
    int exitCode = -1;
    std::string out;
    std::string err;
};

Run run(const std::vector<std::string>& args)
{
    std::ostringstream out, err;
    Run result;
    result.exitCode = cli::runCli(args, out, err);
    result.out = out.str();
    result.err = err.str();
    return result;
}

std::string scene(const std::string& name)
{
    return (contract_fixtures::scenesDir() / "valid" / name).string();
}

cli::Audio randomStereo(std::uint32_t rate, std::size_t frames, std::uint32_t seed)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    cli::Audio audio;
    audio.sampleRate = rate;
    audio.channels.assign(2, std::vector<float>(frames));
    for (auto& channel : audio.channels)
        for (auto& v : channel)
            v = dist(rng);
    return audio;
}

bool bitIdentical(const std::vector<float>& a, const std::vector<float>& b)
{
    return a.size() == b.size() && std::memcmp(a.data(), b.data(), a.size() * sizeof(float)) == 0;
}

} // namespace

TEST_CASE("render_cli stub render is bit-identical to the input", "[cli]")
{
    TempDir dir;
    for (const std::uint32_t rate : {44100u, 48000u, 96000u})
    {
        const auto input = randomStereo(rate, rate + 123, rate);
        std::string error;
        REQUIRE(cli::writeWavFloat32(dir.path / "in.wav", input, error));

        for (const std::string sceneName : {"medium_room.json", "large_hall.json", "open_field.json"})
        {
            const Run r = run({"--scene", scene(sceneName), "--in", (dir.path / "in.wav").string(), "--out",
                               (dir.path / "out.wav").string()});
            INFO(r.err);
            REQUIRE(r.exitCode == cli::kExitOk);

            cli::Audio output;
            REQUIRE(cli::readWav(dir.path / "out.wav", output, error));
            CHECK(output.sampleRate == rate);
            REQUIRE(output.channels.size() == 2);
            CHECK(bitIdentical(output.channels[0], input.channels[0]));
            CHECK(bitIdentical(output.channels[1], input.channels[1]));
        }
    }
}

TEST_CASE("render_cli --ir writes emitter x output channels", "[cli]")
{
    TempDir dir;
    const Run r = run(
        {"--scene", scene("small_room.json"), "--ir", (dir.path / "ir.wav").string(), "--mode", "omni"});
    INFO(r.err);
    REQUIRE(r.exitCode == cli::kExitOk);

    cli::Audio ir;
    std::string error;
    REQUIRE(cli::readWav(dir.path / "ir.wav", ir, error));
    CHECK(ir.sampleRate == 48000u);
    REQUIRE(ir.channels.size() == 4);
    CHECK(ir.channels[0] == std::vector<float>{1.0f}); // L -> out 0
    CHECK(ir.channels[1] == std::vector<float>{0.0f});
    CHECK(ir.channels[2] == std::vector<float>{0.0f});
    CHECK(ir.channels[3] == std::vector<float>{1.0f}); // R -> out 1

    const Run r96 = run(
        {"--scene", scene("small_room.json"), "--ir", (dir.path / "ir96.wav").string(), "--rate", "96000"});
    REQUIRE(r96.exitCode == cli::kExitOk);
    REQUIRE(cli::readWav(dir.path / "ir96.wav", ir, error));
    CHECK(ir.sampleRate == 96000u);
}

TEST_CASE("render_cli returns exit code 2 with readable errors for every invalid fixture", "[cli]")
{
    TempDir dir;
    const auto fixtures = contract_fixtures::list("invalid");
    REQUIRE(fixtures.size() >= 15);
    for (const auto& path : fixtures)
    {
        const Run r = run({"--scene", path.string(), "--ir", (dir.path / "ir.wav").string()});
        INFO(path.filename().string() << "\n" << r.err);
        CHECK(r.exitCode == cli::kExitInvalidScene);
        // The expected code, its JSON path context and a sentence are printed.
        CHECK(r.err.find("error: " + contract_fixtures::expectedCodeName(path)) != std::string::npos);
        CHECK(r.err.find("invalid scene") != std::string::npos);
        CHECK_FALSE(fs::exists(dir.path / "ir.wav"));
    }
}

TEST_CASE("render_cli exit codes are distinct (AX12)", "[cli]")
{
    const std::vector<int> codes{cli::kExitOk, cli::kExitUsage, cli::kExitInvalidScene, cli::kExitIo,
                                 cli::kExitInternal};
    for (std::size_t i = 0; i < codes.size(); ++i)
    {
        CHECK(codes[i] == static_cast<int>(i)); // 0 ok, 1 usage, 2 invalid scene, 3 I/O, 4 internal
        for (std::size_t j = i + 1; j < codes.size(); ++j)
            CHECK(codes[i] != codes[j]);
    }
    CHECK(cli::usage().find("4 internal error") != std::string::npos);
}

TEST_CASE("render_cli usage and I/O errors", "[cli]")
{
    TempDir dir;
    const std::string ir = (dir.path / "ir.wav").string();

    CHECK(run({"--help"}).exitCode == cli::kExitOk);
    CHECK(run({}).exitCode == cli::kExitUsage);
    CHECK(run({"--scene", scene("small_room.json")}).exitCode == cli::kExitUsage);
    CHECK(run({"--scene", scene("small_room.json"), "--ir", ir, "--bogus"}).exitCode == cli::kExitUsage);
    CHECK(run({"--scene", scene("small_room.json"), "--ir", ir, "--rate", "22050"}).exitCode
          == cli::kExitUsage);
    CHECK(run({"--scene", scene("small_room.json"), "--ir", ir, "--mode", "mono"}).exitCode
          == cli::kExitUsage);
    CHECK(run({"--scene", scene("small_room.json"), "--in", ir}).exitCode == cli::kExitUsage);

    const Run automation = run({"--scene", scene("small_room.json"), "--ir", ir, "--automation", "a.json"});
    CHECK(automation.exitCode == cli::kExitUsage);
    CHECK(automation.err.find("not implemented until Phase 10") != std::string::npos);

    CHECK(run({"--scene", (dir.path / "missing.json").string(), "--ir", ir}).exitCode == cli::kExitIo);
    CHECK(run({"--scene", scene("small_room.json"), "--in", (dir.path / "missing.wav").string(), "--out",
               (dir.path / "out.wav").string()})
              .exitCode
          == cli::kExitIo);
    CHECK(run({"--scene", scene("small_room.json"), "--ir", (dir.path / "no_such_dir" / "ir.wav").string()})
              .exitCode
          == cli::kExitIo);

    // Mono input: v1 needs stereo.
    cli::Audio mono;
    mono.channels.assign(1, std::vector<float>(100, 0.5f));
    std::string error;
    REQUIRE(cli::writeWavFloat32(dir.path / "mono.wav", mono, error));
    CHECK(run({"--scene", scene("small_room.json"), "--in", (dir.path / "mono.wav").string(), "--out",
               (dir.path / "out.wav").string()})
              .exitCode
          == cli::kExitIo);

    // --rate that contradicts the input: no resampling.
    REQUIRE(cli::writeWavFloat32(dir.path / "in.wav", randomStereo(48000, 100, 1), error));
    CHECK(run({"--scene", scene("small_room.json"), "--in", (dir.path / "in.wav").string(), "--out",
               (dir.path / "out.wav").string(), "--rate", "44100"})
              .exitCode
          == cli::kExitUsage);
}
