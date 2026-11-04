#include "plugin/PluginProcessor.h"

namespace plugin {

SpatialSceneProcessor::SpatialSceneProcessor()
    : juce::AudioProcessor(BusesProperties()
                               .withInput("Input", juce::AudioChannelSet::stereo(), true)
                               .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{}

bool SpatialSceneProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
           && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void SpatialSceneProcessor::prepareToPlay(double /*sampleRate*/, int /*maximumExpectedSamplesPerBlock*/)
{
    // Phase 00: nothing to allocate. Later phases size the convolver here (never in processBlock).
    setLatencySamples(0);
}

void SpatialSceneProcessor::releaseResources() {}

template <typename SampleType>
void SpatialSceneProcessor::passThrough(juce::AudioBuffer<SampleType>& buffer) noexcept
{
    // Hosts process in place: the input channels arrive in `buffer` and the output is read back from
    // the same channels. A pass-through therefore leaves the main channels untouched and only has to
    // silence output channels that have no input counterpart (none for the stereo->stereo layout,
    // but the host may still hand us a wider buffer).
    juce::ScopedNoDenormals noDenormals;

    const auto numInputChannels = getTotalNumInputChannels();
    const auto numOutputChannels = getTotalNumOutputChannels();

    for (int channel = numInputChannels; channel < numOutputChannels; ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());
}

void SpatialSceneProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    passThrough(buffer);
}

void SpatialSceneProcessor::processBlock(juce::AudioBuffer<double>& buffer,
                                         juce::MidiBuffer& /*midiMessages*/)
{
    passThrough(buffer);
}

juce::AudioProcessorEditor* SpatialSceneProcessor::createEditor()
{
    // The generic editor is enough until Phase 11.
    return new juce::GenericAudioProcessorEditor(*this);
}

void SpatialSceneProcessor::getStateInformation(juce::MemoryBlock& /*destData*/)
{
    // Phase 00 has no state. Phase 07 defines the versioned plugin state wrapping the scene JSON.
}

void SpatialSceneProcessor::setStateInformation(const void* /*data*/, int /*sizeInBytes*/) {}

} // namespace plugin

// Called by the JUCE plugin wrappers (VST3, AU, Standalone) to create the processor instance.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new plugin::SpatialSceneProcessor();
}
