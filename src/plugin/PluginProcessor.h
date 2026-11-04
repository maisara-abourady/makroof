#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

namespace plugin {

// Phase 00: a stereo pass-through. processBlock leaves the audio untouched; later phases replace the
// body with the scene -> IR -> convolution pipeline.
class SpatialSceneProcessor final : public juce::AudioProcessor
{
public:
    SpatialSceneProcessor();
    ~SpatialSceneProcessor() override = default;

    // Only stereo in -> stereo out is supported (PRD AX7: one stereo track drives two emitters).
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    void processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override;
    bool supportsDoublePrecisionProcessing() const override { return true; }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return "Default"; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    template <typename SampleType>
    void passThrough(juce::AudioBuffer<SampleType>& buffer) noexcept;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpatialSceneProcessor)
};

} // namespace plugin
