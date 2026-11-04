// Null test for the Phase 00 pass-through plugin: output == input, bit for bit, through the same
// AudioProcessor instance the host wrappers use.
#include "plugin/PluginProcessor.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cstring>
#include <random>
#include <vector>

namespace {

constexpr int kNumChannels = 2;
constexpr int kNumBlocks = 10;

// Fills a buffer with deterministic full-scale noise. Seeded so failures are reproducible.
void fillWithNoise(juce::AudioBuffer<float>& buffer, std::mt19937& rng)
{
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* data = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
            data[i] = dist(rng);
    }
}

bool bitIdentical(const juce::AudioBuffer<float>& a, const juce::AudioBuffer<float>& b)
{
    if (a.getNumChannels() != b.getNumChannels() || a.getNumSamples() != b.getNumSamples())
        return false;

    const auto bytes = static_cast<std::size_t>(a.getNumSamples()) * sizeof(float);
    for (int channel = 0; channel < a.getNumChannels(); ++channel)
        if (std::memcmp(a.getReadPointer(channel), b.getReadPointer(channel), bytes) != 0)
            return false;

    return true;
}

} // namespace

TEST_CASE("SpatialScene passes stereo audio through unchanged", "[plugin][passthrough]")
{
    // Headless JUCE runtime: message manager and the bits GenericAudioProcessorEditor would need.
    juce::ScopedJuceInitialiser_GUI juceInitialiser;

    const double sampleRate = GENERATE(44100.0, 48000.0, 96000.0);
    const int blockSize = GENERATE(1, 64, 512, 2048);
    CAPTURE(sampleRate, blockSize);

    plugin::SpatialSceneProcessor processor;
    REQUIRE(processor.getTotalNumInputChannels() == kNumChannels);
    REQUIRE(processor.getTotalNumOutputChannels() == kNumChannels);

    processor.setPlayConfigDetails(kNumChannels, kNumChannels, sampleRate, blockSize);
    processor.prepareToPlay(sampleRate, blockSize);
    REQUIRE(processor.getLatencySamples() == 0);

    std::mt19937 rng(static_cast<std::mt19937::result_type>(sampleRate) ^ static_cast<unsigned>(blockSize));
    juce::AudioBuffer<float> buffer(kNumChannels, blockSize);
    juce::AudioBuffer<float> expected(kNumChannels, blockSize);
    juce::MidiBuffer midi;

    for (int block = 0; block < kNumBlocks; ++block)
    {
        fillWithNoise(buffer, rng);
        expected.makeCopyOf(buffer, true);

        processor.processBlock(buffer, midi);

        INFO("block " << block);
        REQUIRE(bitIdentical(buffer, expected));
    }

    processor.releaseResources();
}

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
