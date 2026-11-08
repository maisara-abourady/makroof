// Phase 07 scope 4 (FR-LIC-1, NFR-6): the plugin state. Round trip (bit-identical render), offline
// determinism, restore before prepareToPlay (the Logic order), the parameters win over the scene JSON,
// committed state fixtures (tests/state/v1_*.bin), known versions, and the corrupt-state fuzz.
#include "ConvTestUtil.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "plugin/PluginProcessor.h"

#include <catch2/catch_test_macros.hpp>

#include <cstring>
#include <random>
#include <string>
#include <vector>

// Exact comparisons are intended (bit-identical renders, stored values).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

constexpr double kRate = 48000.0;
constexpr int kBlock = 480; // 2.0 s = block 200

using Audio = std::vector<std::vector<float>>;

void setParam(plugin::SpatialSceneProcessor& p, const char* id, float plain)
{
    auto* param = p.parameters().getParameter(id);
    REQUIRE(param != nullptr);
    param->setValueNotifyingHost(param->convertTo0to1(plain));
}

float getParam(plugin::SpatialSceneProcessor& p, const char* id)
{
    return p.parameters().getRawParameterValue(id)->load();
}

Audio noise(double seconds, std::uint64_t seed)
{
    const auto n = static_cast<std::size_t>(seconds * kRate);
    return {conv_test::noise(n, seed, 0.2), conv_test::noise(n, seed + 1, 0.2)};
}

// Renders `in` in blocks of kBlock; calls atBlock(block index) before each block.
Audio render(plugin::SpatialSceneProcessor& p, const Audio& in, const std::function<void(int)>& atBlock = {})
{
    Audio out = in;
    juce::MidiBuffer midi;
    const int n = static_cast<int>(in[0].size());
    int block = 0;
    for (int pos = 0; pos < n; pos += kBlock, ++block)
    {
        if (atBlock)
            atBlock(block);
        const int len = std::min(kBlock, n - pos);
        float* chans[2] = {out[0].data() + pos, out[1].data() + pos};
        juce::AudioBuffer<float> buffer(chans, 2, len);
        p.processBlock(buffer, midi);
    }
    return out;
}

void prepare(plugin::SpatialSceneProcessor& p, bool offline)
{
    p.setNonRealtime(offline);
    p.setPlayConfigDetails(2, 2, kRate, kBlock);
    p.prepareToPlay(kRate, kBlock);
}

juce::MemoryBlock stateOf(plugin::SpatialSceneProcessor& p)
{
    juce::MemoryBlock block;
    p.getStateInformation(block);
    return block;
}

void restore(plugin::SpatialSceneProcessor& p, const juce::MemoryBlock& block)
{
    p.setStateInformation(block.getData(), static_cast<int>(block.getSize()));
}

// A state whose scene JSON is `edit`ed (non-parameter fields; parameter fields are overridden by PARAMS).
juce::MemoryBlock editedState(plugin::SpatialSceneProcessor& p,
                              const std::function<void(contract::SceneDescription&)>& edit)
{
    const auto block = stateOf(p);
    auto xml = juce::AudioProcessor::getXmlFromBinary(block.getData(), static_cast<int>(block.getSize()));
    REQUIRE(xml != nullptr);
    auto* sceneEl = xml->getChildByName("Scene");
    REQUIRE(sceneEl != nullptr);
    auto parsed = contract::fromJson(sceneEl->getAllSubText().toStdString());
    REQUIRE(parsed.ok());
    auto scene = *parsed.scene;
    edit(scene);
    sceneEl->deleteAllTextElements();
    const auto json = contract::toJson(scene);
    sceneEl->addTextElement(juce::String::fromUTF8(json.data(), static_cast<int>(json.size())));
    juce::MemoryBlock out;
    juce::AudioProcessor::copyXmlToBinary(*xml, out);
    return out;
}

// The modified state of the AC: listener_y and two non-parameter fields (tailSeed, one alpha).
void applyModifiedState(plugin::SpatialSceneProcessor& p)
{
    setParam(p, "listener_y", 0.6f);
    restore(p, editedState(p, [](contract::SceneDescription& s) {
                s.render.tailSeed = 777;
                s.room.surface(contract::SurfaceId::floor).bandsAbsorption[4] = 0.35;
            }));
    REQUIRE_FALSE(p.stateWarning());
}

juce::File stateDir()
{
    return juce::File(juce::String(SPATIAL_STATE_DIR));
}

} // namespace

TEST_CASE("State round trip: a restored instance renders bit-identically", "[plugin][state][roundtrip]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const auto in = noise(5.0, 31);

    plugin::SpatialSceneProcessor a;
    applyModifiedState(a);
    prepare(a, true);
    const auto outA = render(a, in);
    const auto saved = stateOf(a);
    const auto sceneA = a.pipeline().currentScene();
    REQUIRE(sceneA.render.tailSeed == 777);
    REQUIRE(sceneA.room.surface(contract::SurfaceId::floor).bandsAbsorption[4] == 0.35);
    REQUIRE(sceneA.render.outputMode == contract::OutputMode::binaural); // stored, not applied (omni)

    plugin::SpatialSceneProcessor b;
    restore(b, saved);
    REQUIRE_FALSE(b.stateWarning());
    REQUIRE(b.pipeline().currentScene() == sceneA);
    REQUIRE(getParam(b, "listener_y") == 0.6f);
    prepare(b, true);
    const auto outB = render(b, in);
    REQUIRE(outB == outA);

    plugin::SpatialSceneProcessor d; // default instance
    prepare(d, true);
    const auto outD = render(d, in);
    REQUIRE(outD[0] != outA[0]);
}

TEST_CASE("State: outputMode is stored unchanged and the render stays omni", "[plugin][state]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const auto in = noise(1.0, 41);
    plugin::SpatialSceneProcessor a;
    prepare(a, true);
    const auto outBinaural = render(a, in);

    plugin::SpatialSceneProcessor b;
    restore(b, editedState(b, [](contract::SceneDescription& s) {
                s.render.outputMode = contract::OutputMode::stereoSpeakers;
            }));
    REQUIRE_FALSE(b.stateWarning());
    REQUIRE(b.pipeline().currentScene().render.outputMode == contract::OutputMode::stereoSpeakers);
    prepare(b, true);
    REQUIRE(render(b, in) == outBinaural); // Phase 07 always renders Kind::Omni
    plugin::SpatialSceneProcessor c;
    restore(c, stateOf(b));
    REQUIRE(c.pipeline().currentScene().render.outputMode == contract::OutputMode::stereoSpeakers);
}

TEST_CASE("Offline determinism: two bounces with a reset and a fresh instance are bit-identical",
          "[plugin][state][offline]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const auto in = noise(3.0, 51);
    const auto bounce = [&](plugin::SpatialSceneProcessor& p, bool change) {
        return render(p, in, [&](int block) {
            if (change && block == 200) // 2.0 s
                setParam(p, "listener_y", 0.7f);
        });
    };

    plugin::SpatialSceneProcessor a;
    prepare(a, true);
    const auto first = bounce(a, true);
    setParam(a, "listener_y", static_cast<float>(module3d::defaultParameterValues()[module3d::kListenerY]));
    a.reset();
    const auto second = bounce(a, true);
    REQUIRE(second == first);

    plugin::SpatialSceneProcessor fresh;
    prepare(fresh, true);
    const auto third = bounce(fresh, true);
    REQUIRE(third == first);

    plugin::SpatialSceneProcessor still;
    prepare(still, true);
    const auto unchanged = bounce(still, false);
    const std::size_t at = 96000;
    REQUIRE(std::equal(unchanged[0].begin(), unchanged[0].begin() + static_cast<std::ptrdiff_t>(at),
                       first[0].begin()));
    REQUIRE(!std::equal(unchanged[0].begin() + static_cast<std::ptrdiff_t>(at), unchanged[0].end(),
                        first[0].begin() + static_cast<std::ptrdiff_t>(at)));
}

TEST_CASE("State restored before prepareToPlay (the Logic order) is built in prepareToPlay",
          "[plugin][state][logic-order]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const auto in = noise(2.0, 61);
    plugin::SpatialSceneProcessor a;
    applyModifiedState(a);
    const auto saved = stateOf(a);
    prepare(a, true);
    const auto expected = render(a, in);

    plugin::SpatialSceneProcessor b;
    restore(b, saved);
    REQUIRE_FALSE(b.stateWarning());
    REQUIRE_FALSE(b.pipeline().engine().isPrepared()); // validated and stored only
    REQUIRE(b.pipeline().engine().convolver().currentIr() == nullptr);
    REQUIRE(b.pipeline().restorePending());
    prepare(b, false); // realtime: the synchronous build consumes the restore
    REQUIRE_FALSE(b.pipeline().restorePending());
    REQUIRE(render(b, in) == expected);
}

TEST_CASE("State: the parameters win over the scene JSON; other fields come from the JSON", "[plugin][state]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor a;
    setParam(a, "listener_y", 0.5f);
    const auto state = editedState(a, [](contract::SceneDescription& s) {
        s.listener.position.y = 9.0;         // disagrees with listener_y
        s.room.geometry.dimensions.x = 20.0; // disagrees with room_w
        s.emitters[0].gainDb = -6.0;         // no parameter: taken from the JSON
    });
    plugin::SpatialSceneProcessor b;
    restore(b, state);
    REQUIRE_FALSE(b.stateWarning());
    const auto scene = b.pipeline().currentScene();
    REQUIRE(std::fabs(scene.listener.position.y - (0.1 + 0.5 * 11.8)) < 1e-6);
    REQUIRE(scene.room.geometry.dimensions.x == 8.0);
    REQUIRE(scene.emitters[0].gainDb == -6.0);
}

TEST_CASE("Generate the state fixtures (run by hand when pluginStateVersion is bumped)",
          "[.generate-state-fixtures]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    {
        plugin::SpatialSceneProcessor p;
        REQUIRE(stateDir()
                    .getChildFile("v1_default.bin")
                    .replaceWithData(stateOf(p).getData(), stateOf(p).getSize()));
    }
    {
        plugin::SpatialSceneProcessor p;
        applyModifiedState(p);
        const auto s = stateOf(p);
        REQUIRE(stateDir().getChildFile("v1_modified.bin").replaceWithData(s.getData(), s.getSize()));
    }
}

TEST_CASE("State fixtures: every committed tests/state/v*_*.bin loads", "[plugin][state][fixtures]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const auto files = stateDir().findChildFiles(juce::File::findFiles, false, "v*_*.bin");
    REQUIRE(files.size() >= 2);
    for (const auto& f : files)
    {
        INFO(f.getFileName());
        juce::MemoryBlock block;
        REQUIRE(f.loadFileAsData(block));
        plugin::SpatialSceneProcessor p;
        restore(p, block);
        REQUIRE_FALSE(p.stateWarning());
        REQUIRE(contract::validate(p.pipeline().currentScene()).ok());
    }
    // Every known version has a fixture.
    for (const int v : plugin::SpatialSceneProcessor::knownStateVersions())
        REQUIRE(stateDir().getChildFile("v" + juce::String(v) + "_default.bin").existsAsFile());

    // The modified fixture keeps its values.
    juce::MemoryBlock block;
    REQUIRE(stateDir().getChildFile("v1_modified.bin").loadFileAsData(block));
    plugin::SpatialSceneProcessor p;
    restore(p, block);
    REQUIRE(getParam(p, "listener_y") == 0.6f);
    REQUIRE(p.pipeline().currentScene().render.tailSeed == 777);
    REQUIRE(p.pipeline().currentScene().room.surface(contract::SurfaceId::floor).bandsAbsorption[4] == 0.35);
}

TEST_CASE("State: an unknown version falls back to the default scene with the warning flag",
          "[plugin][state]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor a;
    applyModifiedState(a);
    const auto block = stateOf(a);
    for (const char* version : {"99", "0", "", "x"})
    {
        CAPTURE(version);
        auto xml = juce::AudioProcessor::getXmlFromBinary(block.getData(), static_cast<int>(block.getSize()));
        if (std::strlen(version) == 0)
            xml->removeAttribute("pluginStateVersion");
        else
            xml->setAttribute("pluginStateVersion", version);
        juce::MemoryBlock out;
        juce::AudioProcessor::copyXmlToBinary(*xml, out);
        plugin::SpatialSceneProcessor b;
        restore(b, out);
        REQUIRE(b.stateWarning());
        REQUIRE(b.pipeline().currentScene() == plugin::SpatialSceneProcessor().pipeline().currentScene());
    }
}

TEST_CASE("Corrupt-state fuzz: 1 000 random blobs never crash and always end in a valid scene",
          "[plugin][state][fuzz]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor source;
    applyModifiedState(source);
    const auto valid = stateOf(source);
    std::mt19937_64 rng(1000);
    std::uniform_int_distribution<int> byte(0, 255);

    plugin::SpatialSceneProcessor p;
    int warnings = 0;
    for (int i = 0; i < 1000; ++i)
    {
        juce::MemoryBlock blob;
        if (i % 2 == 0)
        {
            // Random bytes, 0 .. 4 000 long; every fourth one starts with the copyXmlToBinary magic.
            const auto len = static_cast<std::size_t>(rng() % 4001);
            blob.setSize(len);
            for (std::size_t k = 0; k < len; ++k)
                static_cast<std::uint8_t*>(blob.getData())[k] = static_cast<std::uint8_t>(byte(rng));
            if (i % 8 == 0 && len >= 8)
                std::memcpy(blob.getData(), valid.getData(), 8);
        }
        else
        {
            // A valid state with 1 .. 16 bytes overwritten, and sometimes truncated.
            blob = valid;
            auto* data = static_cast<std::uint8_t*>(blob.getData());
            const int edits = 1 + static_cast<int>(rng() % 16);
            for (int k = 0; k < edits; ++k)
                data[rng() % blob.getSize()] = static_cast<std::uint8_t>(byte(rng));
            if (i % 5 == 1)
                blob.setSize(rng() % blob.getSize());
        }
        INFO("blob " << i);
        REQUIRE_NOTHROW(p.setStateInformation(blob.getData(), static_cast<int>(blob.getSize())));
        if (p.stateWarning())
            ++warnings;
        REQUIRE(contract::validate(p.pipeline().currentScene()).ok());
    }
    REQUIRE(warnings >= 500); // every random blob is rejected
    // And the instance still renders.
    prepare(p, false);
    const auto out = render(p, noise(0.5, 71));
    for (const auto& c : out)
        for (const float s : c)
            REQUIRE(std::isfinite(s));
}
