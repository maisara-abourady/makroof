#include "plugin/PluginProcessor.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "module3d/ParameterMap.h"

#include <algorithm>
#include <cstring>
#include <string>

#if SPATIAL_HOST_TRACE
// Phase-07c-1 condition 11: one record per host entry point (diagnostic build only).
#define SPATIAL_TRACE(entry, block, argument)                                                                \
    const trace::Scope traceScope_(trace_.get(), trace::Entry::entry, juce::AudioProcessor::isNonRealtime(), \
                                   transport(), (block), (argument))
#else
#define SPATIAL_TRACE(entry, block, argument) static_cast<void>(0)
#endif

namespace plugin {

namespace {

const juce::Identifier kStateTag{"SpatialSceneState"};
const juce::Identifier kParamsTag{"PARAMS"};
constexpr const char* kSceneTag = "Scene";
constexpr const char* kVersionAttribute = "pluginStateVersion";

juce::String toJuce(std::string_view s)
{
    return juce::String::fromUTF8(s.data(), static_cast<int>(s.size()));
}

juce::AudioProcessorValueTreeState::ParameterLayout makeLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    for (const auto& spec : module3d::parameterSpecs())
    {
        const juce::ParameterID id{toJuce(spec.id), 1};
        if (spec.kind == module3d::ParamKind::Choice)
        {
            juce::StringArray choices;
            for (const auto c : module3d::kOutputModeChoices)
                choices.add(toJuce(c));
            layout.add(std::make_unique<juce::AudioParameterChoice>(id, toJuce(spec.name), choices,
                                                                    static_cast<int>(spec.defaultValue)));
            continue;
        }
        juce::NormalisableRange<float> range(static_cast<float>(spec.min), static_cast<float>(spec.max));
        if (spec.mapping == "room-log")
        {
            // D9: L = 1.5 (100 / 1.5)^x with exact endpoints.
            range = juce::NormalisableRange<float>(
                static_cast<float>(spec.min), static_cast<float>(spec.max),
                [](float, float, float x) { return static_cast<float>(module3d::roomSizeFromNormalized(x)); },
                [](float, float, float l) {
                    return static_cast<float>(module3d::normalizedFromRoomSize(l));
                });
        }
        layout.add(std::make_unique<juce::AudioParameterFloat>(
            id, toJuce(spec.name), range, static_cast<float>(spec.defaultValue),
            juce::AudioParameterFloatAttributes().withLabel(toJuce(spec.unit))));
    }
    return layout;
}

// Brings a state of any known version to the current layout. Version 1 is the current one.
bool migrateState(int version, juce::XmlElement& /*state*/)
{
    const auto& known = SpatialSceneProcessor::knownStateVersions();
    return std::find(known.begin(), known.end(), version) != known.end();
}

} // namespace

// One per parameter: forwards the plain value to the pipeline (atomic store + one fetch_add).
struct SpatialSceneProcessor::ParameterForwarder final : juce::AudioProcessorValueTreeState::Listener
{
    ParameterForwarder(ScenePipeline& p, std::size_t i)
        : pipeline(p)
        , index(i)
    {}
    void parameterChanged(const juce::String&, float newValue) override
    {
        pipeline.setParameter(index, newValue);
    }

    ScenePipeline& pipeline;
    std::size_t index;
};

const std::vector<int>& SpatialSceneProcessor::knownStateVersions()
{
    static const std::vector<int> versions{1};
    return versions;
}

SpatialSceneProcessor::SpatialSceneProcessor()
    : SpatialSceneProcessor(nullptr)
{}

SpatialSceneProcessor::SpatialSceneProcessor(BuilderClock* clock)
    : juce::AudioProcessor(BusesProperties()
                               .withInput("Input", juce::AudioChannelSet::stereo(), true)
                               .withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , pipeline_(clock)
    , apvts_(*this, nullptr, kParamsTag, makeLayout())
{
    const auto& specs = module3d::parameterSpecs();
    for (std::size_t i = 0; i < specs.size(); ++i)
    {
        forwarders_.push_back(std::make_unique<ParameterForwarder>(pipeline_, i));
        apvts_.addParameterListener(toJuce(specs[i].id), forwarders_.back().get());
        // Prime JUCE's notification path once (the APVTS adapter's listener list grows its iterator vector
        // on the first call), so host automation applied on the audio thread does not allocate there.
        if (auto* p = apvts_.getParameter(toJuce(specs[i].id)))
            p->sendValueChangedMessageToListeners(p->getValue());
    }
    setLatencySamples(pipeline_.latencySamples());
#if SPATIAL_HOST_TRACE
    // One trace file per instance, in $SPATIAL_HOST_TRACE_DIR or the temporary directory (opened here, off
    // the audio thread).
    auto dir = juce::SystemStats::getEnvironmentVariable("SPATIAL_HOST_TRACE_DIR", {});
    const juce::File folder = dir.isNotEmpty() ? juce::File(dir)
                                               : juce::File::getSpecialLocation(juce::File::tempDirectory);
    const auto name = "SpatialScene-trace-" + juce::String(juce::Time::currentTimeMillis()) + "-"
                      + juce::String::toHexString(
                          static_cast<juce::pointer_sized_int>(reinterpret_cast<std::uintptr_t>(this)))
                      + ".txt";
    trace_ = std::make_unique<trace::Logger>(folder.getChildFile(name).getFullPathName().toStdString());
#endif
}

SpatialSceneProcessor::~SpatialSceneProcessor()
{
    const auto& specs = module3d::parameterSpecs();
    for (std::size_t i = 0; i < specs.size(); ++i)
        apvts_.removeParameterListener(toJuce(specs[i].id), forwarders_[i].get());
}

bool SpatialSceneProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
           && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void SpatialSceneProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
    SPATIAL_TRACE(PrepareToPlay, maximumExpectedSamplesPerBlock, 0);
    const int maxBlock = std::max(1, maximumExpectedSamplesPerBlock);
    for (auto& s : doubleScratch_)
        s.assign(static_cast<std::size_t>(maxBlock), 0.0f);
    pipeline_.prepare(sampleRate, maxBlock, isNonRealtime());
    // P + 32 = 544 samples at P = 512 (phase-06b D1, AX1); the same in the AX34 fallback, at every rate.
    setLatencySamples(pipeline_.latencySamples());
}

void SpatialSceneProcessor::releaseResources()
{
    SPATIAL_TRACE(ReleaseResources, 0, 0);
    pipeline_.release();
}

void SpatialSceneProcessor::reset()
{
    SPATIAL_TRACE(Reset, 0, 0);
    pipeline_.reset();
}

void SpatialSceneProcessor::setNonRealtime(bool isNonRealtime) noexcept
{
    SPATIAL_TRACE(SetNonRealtime, 0, isNonRealtime ? 1 : 0);
    juce::AudioProcessor::setNonRealtime(isNonRealtime);
    try
    {
        pipeline_.setNonRealtime(isNonRealtime);
    }
    catch (...) // std::system_error from the builder's lock; nothing sensible to do but keep going
    {}
}

template <typename SampleType>
void SpatialSceneProcessor::clearExtraChannels(juce::AudioBuffer<SampleType>& buffer) noexcept
{
    for (int channel = 2; channel < buffer.getNumChannels(); ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());
}

void SpatialSceneProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    SPATIAL_TRACE(ProcessBlock, buffer.getNumSamples(), 0);
    juce::ScopedNoDenormals noDenormals;
    clearExtraChannels(buffer);
    if (buffer.getNumChannels() < 2)
    {
        buffer.clear();
        return;
    }
    const float* const in[2] = {buffer.getReadPointer(0), buffer.getReadPointer(1)};
    float* const out[2] = {buffer.getWritePointer(0), buffer.getWritePointer(1)};
    pipeline_.process(in, out, buffer.getNumSamples());
}

void SpatialSceneProcessor::processBlock(juce::AudioBuffer<double>& buffer,
                                         juce::MidiBuffer& /*midiMessages*/)
{
    SPATIAL_TRACE(ProcessBlock, buffer.getNumSamples(), 1);
    juce::ScopedNoDenormals noDenormals;
    clearExtraChannels(buffer);
    if (buffer.getNumChannels() < 2 || doubleScratch_[0].empty())
    {
        buffer.clear();
        return;
    }
    const int chunk = static_cast<int>(doubleScratch_[0].size());
    const int n = buffer.getNumSamples();
    for (int start = 0; start < n; start += chunk)
    {
        const int len = std::min(chunk, n - start);
        for (int c = 0; c < 2; ++c)
        {
            const double* src = buffer.getReadPointer(c, start);
            float* dst = doubleScratch_[static_cast<std::size_t>(c)].data();
            for (int i = 0; i < len; ++i)
                dst[i] = static_cast<float>(src[i]);
        }
        float* const io[2] = {doubleScratch_[0].data(), doubleScratch_[1].data()};
        pipeline_.process(io, io, len);
        for (int c = 0; c < 2; ++c)
        {
            double* dst = buffer.getWritePointer(c, start);
            const float* src = doubleScratch_[static_cast<std::size_t>(c)].data();
            for (int i = 0; i < len; ++i)
                dst[i] = static_cast<double>(src[i]);
        }
    }
}

#if SPATIAL_HOST_TRACE
trace::Transport SpatialSceneProcessor::transport() const noexcept
{
    // AudioPlayHead::getPosition() fills a value object: no allocation, no lock (JUCE 8).
    if (auto* head = getPlayHead())
        if (const auto pos = head->getPosition())
            return pos->getIsPlaying() ? trace::Transport::Playing : trace::Transport::Stopped;
    return trace::Transport::Unknown;
}
#endif

juce::AudioProcessorEditor* SpatialSceneProcessor::createEditor()
{
    // The generic editor is enough until Phase 11.
    return new juce::GenericAudioProcessorEditor(*this);
}

module3d::ParameterValues SpatialSceneProcessor::readParameters() const
{
    module3d::ParameterValues v{};
    const auto& specs = module3d::parameterSpecs();
    for (std::size_t i = 0; i < specs.size(); ++i)
        if (const auto* raw = apvts_.getRawParameterValue(toJuce(specs[i].id)))
            v[i] = static_cast<double>(raw->load());
    return v;
}

void SpatialSceneProcessor::setAllParameters(const module3d::ParameterValues& values)
{
    const auto& specs = module3d::parameterSpecs();
    for (std::size_t i = 0; i < specs.size(); ++i)
        if (auto* p = apvts_.getParameter(toJuce(specs[i].id)))
            p->setValueNotifyingHost(p->convertTo0to1(static_cast<float>(values[i])));
}

void SpatialSceneProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    SPATIAL_TRACE(GetState, 0, 0);
    juce::XmlElement root(kStateTag);
    root.setAttribute(kVersionAttribute, kPluginStateVersion);
    const std::string json = contract::toJson(pipeline_.currentScene()); // the full scene contract JSON
    root.createNewChildElement(kSceneTag)->addTextElement(
        juce::String::fromUTF8(json.data(), static_cast<int>(json.size())));
    if (auto params = apvts_.copyState().createXml())
        root.addChildElement(params.release());
    copyXmlToBinary(root, destData);
}

void SpatialSceneProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    SPATIAL_TRACE(SetState, 0, sizeInBytes);
    pipeline_.beginRestore(); // no half-restored scene is built while the parameters change

    bool ok = false;
    contract::SceneDescription base = defaultScene();
    module3d::ParameterValues values = module3d::defaultParameterValues();
    std::unique_ptr<juce::XmlElement> xml;
    if (data != nullptr && sizeInBytes > 0)
        xml = getXmlFromBinary(data, sizeInBytes);
    if (xml != nullptr && xml->hasTagName(kStateTag.toString())
        && migrateState(xml->getIntAttribute(kVersionAttribute, -1), *xml))
    {
        const auto* sceneEl = xml->getChildByName(kSceneTag);
        const auto* paramsEl = xml->getChildByName(kParamsTag);
        if (sceneEl != nullptr && paramsEl != nullptr)
        {
            const std::string json = sceneEl->getAllSubText().toStdString();
            const auto parsed = contract::fromJson(json);
            if (parsed.ok() && contract::validate(*parsed.scene).ok())
            {
                const auto tree = juce::ValueTree::fromXml(*paramsEl);
                if (tree.isValid() && tree.hasType(kParamsTag))
                {
                    base = *parsed.scene;
                    apvts_.replaceState(tree);
                    values = readParameters(); // the parameters win over the scene JSON
                    ok = true;
                }
            }
        }
    }
    if (!ok)
        setAllParameters(values); // the defaults
    stateWarning_.store(!ok, std::memory_order_release);
    values = readParameters();
    pipeline_.restore(base, values);
}

} // namespace plugin

// Called by the JUCE plugin wrappers (VST3, AU, Standalone) to create the processor instance.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new plugin::SpatialSceneProcessor();
}
