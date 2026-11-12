#pragma once

// The JUCE AudioProcessor (Phase 07): a thin adapter around plugin::ScenePipeline (src/plugin/core/),
// which owns the scene -> IR -> convolution pipeline and its threading rules.
//
//   - Host parameters: an AudioProcessorValueTreeState built from module3d::parameterSpecs() (frozen IDs,
//     tests/state/parameter_ids_v1.json). One listener per parameter forwards the plain value to
//     ScenePipeline::setParameter (an atomic store and one lock-free fetch_add; no lock, no allocation).
//     JUCE's own notification path around it (AudioProcessorParameter::sendValueChangedMessageToListeners)
//     takes JUCE's uncontended listenerLock on whatever thread the host automates from, with or without
//     our listener; the constructor primes it once so it does not allocate later.
//   - State (FR-LIC-1, NFR-6): XML with pluginStateVersion, the full scene contract JSON and the APVTS
//     state. On restore the APVTS values win for every field that has a parameter; the scene JSON gives
//     every other field. Invalid or corrupt state falls back to the default scene and sets a warning flag.
//     State v2 (phase-07c-1, AX48) adds the solved diffuse level per emitter and its five-part key (DIFFUSE);
//     a load whose key matches plays it at once, any mismatch or a v1 state loads keyless.
//   - Output: the omni room IR (mono preview, the same signal on both outputs) until Phase 08.
#if SPATIAL_HOST_TRACE
#include "plugin/core/HostTrace.h"
#endif
#include "plugin/core/ScenePipeline.h"

#include <juce_audio_processors/juce_audio_processors.h>

#include <array>
#include <atomic>
#include <memory>
#include <vector>

namespace plugin {

class SpatialSceneProcessor final : public juce::AudioProcessor
{
public:
    // The plugin state format version. Every phase that bumps it adds a fixture tests/state/v<N>_*.bin,
    // and the old fixtures must keep loading (migrateState()).
    static constexpr int kPluginStateVersion = 2; // 2: AX48 saved diffuse level (phase-07c-1)

    SpatialSceneProcessor();
    // Tests only: an injected builder clock.
    explicit SpatialSceneProcessor(BuilderClock* clock);
    ~SpatialSceneProcessor() override;

    // Only stereo in -> stereo out is supported (AX7: one stereo track drives two emitters).
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void releaseResources() override;
    void reset() override;
    void setNonRealtime(bool isNonRealtime) noexcept override;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;
    void processBlock(juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override;
    bool supportsDoublePrecisionProcessing() const override { return true; }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    // The longest room IR (12 s cap + AX1 pre-roll), so hosts render the reverb tail.
    double getTailLengthSeconds() const override { return pipeline_.tailLengthSeconds(); }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return "Default"; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Warning flags (shown by the UI from Phase 11): the last restored state was invalid or corrupt (the
    // default scene was loaded); the host rate is outside AX6 (AX34 fallback).
    bool stateWarning() const noexcept { return stateWarning_.load(std::memory_order_acquire); }
    bool unsupportedRateWarning() const noexcept { return pipeline_.unsupportedRateFallback(); }

    juce::AudioProcessorValueTreeState& parameters() noexcept { return apvts_; }
    ScenePipeline& pipeline() noexcept { return pipeline_; }
    const ScenePipeline& pipeline() const noexcept { return pipeline_; }

    // The known plugin state versions, oldest first.
    static const std::vector<int>& knownStateVersions();

private:
    struct ParameterForwarder;

    template <typename SampleType>
    void clearExtraChannels(juce::AudioBuffer<SampleType>& buffer) noexcept;
    void setAllParameters(const module3d::ParameterValues& values);
    module3d::ParameterValues readParameters() const;

    ScenePipeline pipeline_;
    juce::AudioProcessorValueTreeState apvts_;
    std::vector<std::unique_ptr<ParameterForwarder>> forwarders_;
    std::atomic<bool> stateWarning_{false};
    std::vector<float> doubleScratch_[2]; // the double-precision path's float buffers (maxBlock)
#if SPATIAL_HOST_TRACE
    // Phase-07c-1 condition 11: the diagnostic host trace (never in a release artefact).
    std::unique_ptr<trace::Logger> trace_;
    trace::Transport transport() const noexcept;
#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpatialSceneProcessor)
};

} // namespace plugin
