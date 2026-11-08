// Phase 07: the JUCE processor. Bus layout, the parameter ID freeze (tests/state/parameter_ids_v1.json),
// the AX34 unsupported-rate fallback (decider D8), the latency peak and the no-allocation check through
// processBlock while host parameters change.
#include "AllocationTracker.h"
#include "ConvTestUtil.h"

#include "plugin/PluginProcessor.h"

#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <limits>

#include <atomic>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>

// Exact comparisons are intended (frozen endpoints, bit-identical delayed samples).
#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wfloat-equal"
#endif

namespace {

constexpr int kLatency = 544;

void setParam(plugin::SpatialSceneProcessor& p, const char* id, float plain)
{
    auto* param = p.parameters().getParameter(id);
    REQUIRE(param != nullptr);
    param->setValueNotifyingHost(param->convertTo0to1(plain));
}

// Processes `in` (2 channels, same length) in blocks of `block`; returns the output.
std::vector<std::vector<float>> render(plugin::SpatialSceneProcessor& p,
                                       const std::vector<std::vector<float>>& in, int block)
{
    std::vector<std::vector<float>> out = in;
    juce::MidiBuffer midi;
    const int n = static_cast<int>(in[0].size());
    for (int pos = 0; pos < n; pos += block)
    {
        const int len = std::min(block, n - pos);
        float* chans[2] = {out[0].data() + pos, out[1].data() + pos};
        juce::AudioBuffer<float> buffer(chans, 2, len);
        p.processBlock(buffer, midi);
    }
    return out;
}

bool bitEqual(float a, float b)
{
    return std::memcmp(&a, &b, sizeof(float)) == 0;
}

} // namespace

TEST_CASE("SpatialScene accepts only stereo in and stereo out", "[plugin][layout]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor processor;

    auto layout = processor.getBusesLayout();
    REQUIRE(processor.checkBusesLayoutSupported(layout));

    // getMainInputChannelSet() returns a copy, so edit the bus arrays directly.
    layout.inputBuses.getReference(0) = juce::AudioChannelSet::mono();
    REQUIRE_FALSE(processor.checkBusesLayoutSupported(layout));

    layout.inputBuses.getReference(0) = juce::AudioChannelSet::stereo();
    layout.outputBuses.getReference(0) = juce::AudioChannelSet::quadraphonic();
    REQUIRE_FALSE(processor.checkBusesLayoutSupported(layout));

    layout.outputBuses.getReference(0) = juce::AudioChannelSet::stereo();
    REQUIRE(processor.checkBusesLayoutSupported(layout));
}

TEST_CASE("Parameter ID freeze: the plugin's parameters equal tests/state/parameter_ids_v1.json",
          "[plugin][params][freeze]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    const juce::File file(juce::String(SPATIAL_STATE_DIR) + "/parameter_ids_v1.json");
    REQUIRE(file.existsAsFile());
    const juce::var doc = juce::JSON::parse(file);
    const auto* frozen = doc["parameters"].getArray();
    REQUIRE(frozen != nullptr);

    plugin::SpatialSceneProcessor processor;
    const auto& params = processor.getParameters();
    REQUIRE(params.size() == frozen->size());
    for (int i = 0; i < params.size(); ++i)
    {
        const auto& f = frozen->getReference(i);
        auto* ranged = dynamic_cast<juce::RangedAudioParameter*>(params[i]);
        REQUIRE(ranged != nullptr);
        INFO("parameter " << i << ": " << ranged->getParameterID());
        REQUIRE(ranged->getParameterID() == f["id"].toString());
        REQUIRE(ranged->getName(100) == f["name"].toString());
        if (f["type"].toString() == "choice")
        {
            auto* choice = dynamic_cast<juce::AudioParameterChoice*>(ranged);
            REQUIRE(choice != nullptr);
            const auto* choices = f["choices"].getArray();
            REQUIRE(choices != nullptr);
            REQUIRE(choice->choices.size() == choices->size());
            for (int c = 0; c < choices->size(); ++c)
                REQUIRE(choice->choices[c] == choices->getReference(c).toString());
            REQUIRE(choice->choices[choice->getIndex()] == f["default"].toString());
            continue;
        }
        REQUIRE(f["type"].toString() == "float");
        const auto& range = ranged->getNormalisableRange();
        REQUIRE(range.start == static_cast<float>(static_cast<double>(f["min"])));
        REQUIRE(range.end == static_cast<float>(static_cast<double>(f["max"])));
        REQUIRE(ranged->convertFrom0to1(0.0f) == range.start);
        REQUIRE(ranged->convertFrom0to1(1.0f) == range.end);
        const float def = ranged->convertFrom0to1(ranged->getDefaultValue());
        REQUIRE(std::fabs(def - static_cast<float>(static_cast<double>(f["default"]))) <= 1e-6f);
        REQUIRE(ranged->getLabel() == f["unit"].toString());
        const auto mapping = f["mapping"].toString();
        if (mapping == "room-log")
        {
            for (const float x : {0.25f, 0.5f, 0.75f})
                REQUIRE(std::fabs(ranged->convertFrom0to1(x) - 1.5 * std::pow(100.0 / 1.5, x)) <= 1e-4);
            REQUIRE(ranged->convertTo0to1(1.5f) == 0.0f);
            REQUIRE(ranged->convertTo0to1(100.0f) == 1.0f);
        }
        else
        {
            REQUIRE(mapping == "linear");
            REQUIRE(std::fabs(ranged->convertFrom0to1(0.5f) - (range.start + range.end) / 2.0f) <= 1e-5f);
        }
    }
}

TEST_CASE("AX34: an unsupported host rate delays the input by the reported latency; a supported rate "
          "renders the room again",
          "[plugin][ax34]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor p;
    setParam(p, "output_trim_db", -12.0f);

    const auto checkFallback = [&](double rate) {
        CAPTURE(rate);
        p.setPlayConfigDetails(2, 2, rate, 512);
        REQUIRE_NOTHROW(p.prepareToPlay(rate, 512));
        REQUIRE(p.unsupportedRateWarning());
        REQUIRE(p.getLatencySamples() == kLatency);
        std::vector<std::vector<float>> in{conv_test::noise(3000, 5, 0.3), conv_test::noise(3000, 6, 0.3)};
        in[0][100] = std::numeric_limits<float>::quiet_NaN();
        const auto out = render(p, in, 512);
        for (int c = 0; c < 2; ++c)
            for (std::size_t i = 0; i < out[0].size(); ++i)
            {
                const float expected = i < kLatency ? 0.0f : in[static_cast<std::size_t>(c)][i - kLatency];
                INFO("channel " << c << " sample " << i);
                REQUIRE(bitEqual(out[static_cast<std::size_t>(c)][i], expected));
            }
        REQUIRE(std::isnan(out[0][100 + kLatency]));
    };
    const auto checkRoom = [&](double rate) {
        CAPTURE(rate);
        p.setPlayConfigDetails(2, 2, rate, 512);
        p.prepareToPlay(rate, 512);
        REQUIRE_FALSE(p.unsupportedRateWarning());
        REQUIRE(p.getLatencySamples() == kLatency);
        std::vector<std::vector<float>> in{conv_test::noise(3000, 7, 0.3), conv_test::noise(3000, 8, 0.3)};
        const auto out = render(p, in, 512);
        bool differs = false;
        for (std::size_t i = kLatency; i < out[0].size() && !differs; ++i)
            differs = !bitEqual(out[0][i], in[0][i - kLatency]);
        REQUIRE(differs);
        REQUIRE(p.pipeline().engine().convolver().currentIr() != nullptr);
    };

    for (const double rate : {11025.0, 22050.0, 176400.0, 192000.0})
    {
        checkFallback(rate);
        checkRoom(48000.0);
    }
    // Rate changes without re-instantiation.
    checkRoom(48000.0);
    checkRoom(96000.0);
    checkRoom(44100.0);
    checkFallback(192000.0);
    checkRoom(48000.0);
}

TEST_CASE("Latency: an impulse peaks at exactly getLatencySamples()", "[plugin][latency]")
{
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor p;
    // Emitters at the listener (pushed to the 0.3 m minimum distance) and all alpha = 1.
    auto scene = p.pipeline().baseScene();
    for (auto& s : scene.room.surfaces)
        s.bandsAbsorption.fill(1.0);
    auto values = p.pipeline().parameterValues();
    for (std::size_t a = 0; a < 3; ++a)
    {
        values[module3d::kEmLX + a] = values[module3d::kListenerX + a];
        values[module3d::kEmRX + a] = values[module3d::kListenerX + a];
    }
    p.pipeline().beginRestore();
    p.pipeline().restore(scene, values);

    p.setPlayConfigDetails(2, 2, 48000.0, 256);
    p.prepareToPlay(48000.0, 256);
    std::vector<std::vector<float>> in{std::vector<float>(4096, 0.0f), std::vector<float>(4096, 0.0f)};
    in[0][0] = 1.0f;
    in[1][0] = 1.0f;
    const auto out = render(p, in, 256);
    std::size_t peak = 0;
    for (std::size_t i = 1; i < out[0].size(); ++i)
        if (std::fabs(out[0][i]) > std::fabs(out[0][peak]))
            peak = i;
    REQUIRE(peak == static_cast<std::size_t>(p.getLatencySamples()));
    REQUIRE(p.getLatencySamples() == kLatency);
}

TEST_CASE("No allocation in processBlock while 50 parameter changes per second arrive", "[plugin][alloc]")
{
    if (!test_support::trackerActive())
        SKIP("allocation tracking is off in this build (ASan)");
    juce::ScopedJuceInitialiser_GUI juceInitialiser;
    plugin::SpatialSceneProcessor p;
    setParam(p, "room_w", 3.0f); // a smaller room keeps the debug rebuilds short
    setParam(p, "room_d", 4.0f);
    setParam(p, "room_h", 2.5f);
    p.setPlayConfigDetails(2, 2, 48000.0, 256);
    p.prepareToPlay(48000.0, 256);

    std::atomic<bool> done{false};
    std::thread host([&] {
        float y = 0.2f;
        while (!done.load())
        {
            setParam(p, "listener_y", y);
            y = y > 0.7f ? 0.2f : y + 0.05f;
            std::this_thread::sleep_for(std::chrono::milliseconds(20)); // 50 per second
        }
    });
    juce::AudioBuffer<float> buffer(2, 256);
    juce::MidiBuffer midi;
    std::size_t allocs = 0, frees = 0;
    const auto fades0 = p.pipeline().engine().convolver().fadeCount();
    const auto end = std::chrono::steady_clock::now() + std::chrono::milliseconds(2000);
    while (std::chrono::steady_clock::now() < end)
    {
        for (int c = 0; c < 2; ++c)
            juce::FloatVectorOperations::fill(buffer.getWritePointer(c), 0.1f, 256);
        {
            test_support::ScopedTracking tracking;
            p.processBlock(buffer, midi);
            allocs += tracking.allocations();
            frees += tracking.deallocations();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
    done.store(true);
    host.join();
    REQUIRE(p.pipeline().engine().convolver().fadeCount() > fades0);
    REQUIRE(allocs == 0);
    REQUIRE(frees == 0);
}
