#include "plugin/core/ScenePipeline.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "module3d/SceneModel.h"
#include "plugin/core/DefaultSceneJson.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <utility>

namespace plugin {

namespace {

bool bitIdentical(const sim::RoomIR& a, const sim::RoomIR& b) noexcept
{
    if (a.numEmitters != b.numEmitters || a.numOutputs != b.numOutputs || a.taps.size() != b.taps.size()
        || std::memcmp(&a.sampleRate, &b.sampleRate, sizeof(double)) != 0)
        return false;
    for (std::size_t i = 0; i < a.taps.size(); ++i)
    {
        if (a.taps[i].size() != b.taps[i].size())
            return false;
        if (!a.taps[i].empty()
            && std::memcmp(a.taps[i].data(), b.taps[i].data(), a.taps[i].size() * sizeof(float)) != 0)
            return false;
    }
    return true;
}

float trimDbToGain(float db) noexcept
{
    const auto& spec = module3d::parameterSpecs()[module3d::kOutputTrimDb];
    double d = db;
    if (!(d >= spec.min)) // also NaN
        d = spec.min;
    if (d > spec.max)
        d = spec.max;
    if (d == 0.0)
        return 1.0f; // exactly unity at 0 dB
    return static_cast<float>(std::pow(10.0, d / 20.0));
}

contract::SceneDescription parseDefaultScene()
{
    auto parsed = contract::fromJson(kDefaultSceneJson);
    if (!parsed.ok() || !contract::validate(*parsed.scene).ok())
        throw std::logic_error("the embedded default scene (medium_room.json) does not validate");
    return module3d::SceneModel::sanitize(*parsed.scene);
}

} // namespace

const contract::SceneDescription& defaultScene()
{
    static const contract::SceneDescription scene = parseDefaultScene();
    return scene;
}

sim::RoomIR ScenePipeline::buildIr(const contract::SceneDescription& scene, double sampleRate)
{
    sim::BuildOptions options;
    options.sampleRate = sampleRate;
    // Phase 07: always the omni hybrid IR (mono room preview); outputMode is ignored until 08/09.
    options.kind = sim::BuildOptions::Kind::Omni;
    return sim::buildRoomIR(scene, options);
}

ScenePipeline::ScenePipeline(BuilderClock* clock)
    : base_(defaultScene())
{
    const auto defaults = module3d::defaultParameterValues();
    for (std::size_t i = 0; i < module3d::kNumParams; ++i)
        params_[i].store(static_cast<float>(defaults[i]), std::memory_order_relaxed);
    for (auto& d : delay_)
        d.assign(static_cast<std::size_t>(latencySamples()), 0.0f);
    if (clock == nullptr)
    {
        ownClock_ = std::make_unique<SteadyBuilderClock>();
        clock = ownClock_.get();
    }
    clock_ = clock;
    snapTrim();
    builder_ = std::make_unique<IrBuilderThread>(
        *clock_, [this] { return hasWork(); }, [this] { decide(Source::Builder); });
}

ScenePipeline::~ScenePipeline()
{
    // Stop accepting work and wait for a running decision first (unique_ptr::reset() nulls the pointer
    // before the destructor joins, and a running decision reads builder_), then stop and join. gate_
    // is released after that (member order): with the last pipeline its pool joins its workers here.
    quiesceBuilder();
    builder_.reset();
}

void ScenePipeline::quiesceBuilder()
{
    builderAbandon_.store(true, std::memory_order_release);
    gate_->notifyWaiters(); // a builder waiting at the gate leaves the queue (AX38 (i))
    builder_->quiesce();
}

void ScenePipeline::restartBuilder()
{
    builderAbandon_.store(false, std::memory_order_release);
    builder_->restart();
}

sim::RoomIR ScenePipeline::solveAndBuild(const contract::SceneDescription& scene, Source source)
{
    const bool builder = source == Source::Builder;
    const auto cls = builder ? DiffuseSolveGate::Class::Builder
                             : (source == Source::Offline ? DiffuseSolveGate::Class::Offline
                                                          : DiffuseSolveGate::Class::Synchronous);
    // The offline path takes the gate only after quiesce() has returned (AX38 (i)).
    assert(source != Source::Offline || !builder_->accepting());
    const std::atomic<bool>* abandon = builder ? &builderAbandon_ : nullptr;
    DiffuseSolveGate::Scope gate(*gate_, cls, abandon);
    if (!gate.entered())
        throw sim::BuildCancelled();
    sim::BuildOptions options;
    options.sampleRate = sampleRate_;
    options.kind = sim::BuildOptions::Kind::Omni; // Phase 07: the omni hybrid IR until 08/09
    options.diffusePool = &gate_->pool();
    options.cancel = abandon;
    return sim::buildRoomIR(scene, options);
}

// ---- parameters ----

void ScenePipeline::setParameter(std::size_t index, float plainValue) noexcept
{
    if (index >= module3d::kNumParams)
        return;
    params_[index].store(plainValue, std::memory_order_relaxed);
    dirty_.fetch_add(1, std::memory_order_acq_rel); // the only other thing the listener does
}

float ScenePipeline::parameter(std::size_t index) const noexcept
{
    return index < module3d::kNumParams ? params_[index].load(std::memory_order_relaxed) : 0.0f;
}

module3d::ParameterValues ScenePipeline::parameterValues() const noexcept
{
    module3d::ParameterValues v{};
    for (std::size_t i = 0; i < module3d::kNumParams; ++i)
        v[i] = static_cast<double>(params_[i].load(std::memory_order_relaxed));
    return v;
}

// ---- decisions ----

bool ScenePipeline::hasWork() const noexcept
{
    const auto d = dirty_.load(std::memory_order_acquire);
    return d != handled_.load(std::memory_order_acquire);
}

bool ScenePipeline::decide(Source source)
{
    // The generation is read BEFORE the snapshot: a change after it is a later generation.
    const std::uint64_t gen = dirty_.load(std::memory_order_acquire);
    try
    {
        const module3d::ParameterValues values = parameterValues();
        contract::SceneDescription scene;
        std::function<void()> hook;
        std::shared_ptr<const sim::RoomIR> ir;
        std::shared_ptr<const sim::conv::IrSet> irSet;
        {
            std::lock_guard<std::mutex> lock(stateMutex_);
            scene = module3d::deriveScene(values, base_);
            hook = afterSnapshot_;
            if (builtScene_ && *builtScene_ == scene && builtIrSet_) // AX5: same scene, same IR
            {
                ir = builtIr_;
                irSet = builtIrSet_;
            }
        }
        if (hook)
            hook();
        if (injectedFailures_.load(std::memory_order_acquire) > 0)
        {
            injectedFailures_.fetch_sub(1, std::memory_order_acq_rel);
            throw std::runtime_error("injected build failure (test hook)");
        }
        if (!irSet)
        {
            auto built = std::make_shared<const sim::RoomIR>(solveAndBuild(scene, source));
            irSet = engine_.makeIrSet(*built);
            ir = std::move(built);
        }

        std::lock_guard<std::mutex> lock(stateMutex_);
        if (source == Source::Builder && !builder_->accepting())
            return false; // quiesced while building: the result is discarded, not submitted
        builtIr_ = ir;
        builtIrSet_ = irSet;
        builtScene_ = scene;
        builtGen_ = gen;

        const bool restoreDecision = restoreGen_.has_value() && gen >= *restoreGen_;
        // Skip rule (D7): bit-identical to the last successful submit since prepare()/reset(). Reset
        // step 3 always submits (the engine has just dropped its IRs).
        if (source != Source::ResetStep3 && lastIr_
            && ((lastScene_ && *lastScene_ == scene) || bitIdentical(*ir, *lastIr_)))
        {
            handled_.store(gen, std::memory_order_release);
            if (restoreDecision)
                restoreGen_.reset();
            return true;
        }
        const auto law = restoreDecision ? sim::conv::CrossfadeLaw::EqualPower
                                         : sim::conv::CrossfadeLaw::EqualGain;
        if (!irSet || !engine_.submitIrSet(irSet, law))
        {
            // Records nothing as handled (D7): the generation still differs from the handled one, so it is
            // built again (by the builder after its AX33 slot, or by the next offline block).
            return false;
        }
        lastIr_ = ir;
        lastIrSet_ = irSet;
        lastScene_ = scene;
        handled_.store(gen, std::memory_order_release);
        if (restoreDecision)
            restoreGen_.reset();
        return true;
    }
    catch (const std::exception&)
    {
        // std::bad_alloc, a cancelled builder solve (sim::BuildCancelled: the builder was quiesced and its
        // result would be discarded anyway) or an unexpected build failure: nothing is recorded as handled
        // and the current IR keeps playing; the generation is built again like a failed submit (D7).
        return false;
    }
}

void ScenePipeline::resetSequence(bool restartBuilder)
{
    quiesceBuilder(); // 1. an in-flight build is discarded
    if (fallback_.load(std::memory_order_acquire) || !engine_.isPrepared())
    {
        snapTrim(); // AX34: steps 1-3 and 5 do nothing
        return;
    }
    engine_.reset(); // 2.
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        lastIr_.reset();
        lastIrSet_.reset();
        lastScene_.reset();
        handled_.store(kNone, std::memory_order_release);
    }
    decide(Source::ResetStep3); // 3. reuses the last built IrSet when its scene is current
    snapTrim();                 // 4.
    if (restartBuilder && active_.load(std::memory_order_acquire)) // 5.
        this->restartBuilder();
}

// ---- host lifecycle ----

void ScenePipeline::prepare(double sampleRate, int maxBlock, bool nonRealtime)
{
    quiesceBuilder(); // no submit in flight while prepare() drops the IRs and reallocates
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        lastIr_.reset();
        lastIrSet_.reset();
        lastScene_.reset();
        builtIr_.reset();
        builtIrSet_.reset();
        builtScene_.reset();
        builtGen_ = kNone;
        handled_.store(kNone, std::memory_order_release);
    }
    nonRealtime_.store(nonRealtime, std::memory_order_release);
    maxBlock_ = std::max(1, maxBlock);
    sampleRate_ = sampleRate;
    for (auto& d : delay_)
        std::fill(d.begin(), d.end(), 0.0f);
    delayPos_ = 0;
    try
    {
        engine_.prepare(sampleRate, maxBlock_);
    }
    catch (const std::invalid_argument&)
    {
        // AX34: unsupported host rate. Input delayed by latencySamples(), no IR built anywhere, the
        // builder stays stopped until a prepare() at a supported rate.
        fallback_.store(true, std::memory_order_release);
        active_.store(false, std::memory_order_release);
        return;
    }
    fallback_.store(false, std::memory_order_release);
    active_.store(true, std::memory_order_release);
    trimRampSamples_ = std::max(1, static_cast<int>(std::lround(kTrimRampS * sampleRate)));
    snapTrim();
    if (!nonRealtime)
    {
        decide(Source::Synchronous); // the initial IR, installed at once at the first partition
        restartBuilder();
    }
    // Offline: the next process() builds and submits (the only submitter during a bounce).
}

void ScenePipeline::reset()
{
    resetSequence(!nonRealtime_.load(std::memory_order_acquire));
}

void ScenePipeline::setNonRealtime(bool nonRealtime)
{
    const bool was = nonRealtime_.exchange(nonRealtime, std::memory_order_acq_rel);
    if (was == nonRealtime)
        return;
    if (nonRealtime)
        resetSequence(false); // enter: the reset sequence, builder kept quiesced
    else if (active_.load(std::memory_order_acquire))
        restartBuilder(); // leave: the builder takes over again
}

void ScenePipeline::release()
{
    active_.store(false, std::memory_order_release); // stays released until the next prepare()
    quiesceBuilder();
}

// ---- state ----

void ScenePipeline::beginRestore()
{
    quiesceBuilder();
}

void ScenePipeline::restore(const contract::SceneDescription& base, const module3d::ParameterValues& values)
{
    quiesceBuilder(); // also when the caller skipped beginRestore()
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        base_ = module3d::SceneModel::sanitize(base);
    }
    for (std::size_t i = 0; i < module3d::kNumParams; ++i)
        params_[i].store(static_cast<float>(values[i]), std::memory_order_relaxed);
    const std::uint64_t gR = dirty_.fetch_add(1, std::memory_order_acq_rel) + 1;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        restoreGen_ = gR; // the restore flag
    }
    if (active_.load(std::memory_order_acquire) && !nonRealtime_.load(std::memory_order_acquire))
    {
        decide(Source::Synchronous); // the restore's decision: EqualPower, or a skip
        restartBuilder();
    }
    // Before prepare(), after release(), offline or in the AX34 fallback: stored only; the next prepare()
    // (realtime) or process() (offline) makes the decision.
}

contract::SceneDescription ScenePipeline::baseScene() const
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    return base_;
}

contract::SceneDescription ScenePipeline::currentScene() const
{
    const auto values = parameterValues();
    std::lock_guard<std::mutex> lock(stateMutex_);
    return module3d::deriveScene(values, base_);
}

// ---- audio ----

void ScenePipeline::snapTrim() noexcept
{
    trimTarget_ = trimDbToGain(params_[module3d::kOutputTrimDb].load(std::memory_order_relaxed));
    trimGain_ = trimTarget_;
    trimStep_ = 0.0f;
    trimRemaining_ = 0;
}

void ScenePipeline::applyTrim(float* const out[2], int n) noexcept
{
    const float target = trimDbToGain(params_[module3d::kOutputTrimDb].load(std::memory_order_relaxed));
    if (target != trimTarget_)
    {
        trimTarget_ = target;
        trimRemaining_ = trimRampSamples_;
        trimStep_ = (target - trimGain_) / static_cast<float>(trimRampSamples_);
    }
    if (trimRemaining_ == 0 && trimGain_ == 1.0f)
        return;
    for (int i = 0; i < n; ++i)
    {
        if (trimRemaining_ > 0)
        {
            trimGain_ += trimStep_;
            if (--trimRemaining_ == 0)
                trimGain_ = trimTarget_;
        }
        out[0][i] *= trimGain_;
        out[1][i] *= trimGain_;
    }
}

void ScenePipeline::processFallback(const float* const in[2], float* const out[2], int n) noexcept
{
    // AX34: output = input delayed by latencySamples(), unchanged (no trim, no AX32 guard).
    const std::size_t len = delay_[0].size();
    for (int i = 0; i < n; ++i)
    {
        for (int c = 0; c < 2; ++c)
        {
            const float x = in[c][i];
            out[c][i] = delay_[static_cast<std::size_t>(c)][delayPos_];
            delay_[static_cast<std::size_t>(c)][delayPos_] = x;
        }
        if (++delayPos_ == len)
            delayPos_ = 0;
    }
}

void ScenePipeline::process(const float* const in[2], float* const out[2], int n) noexcept
{
    if (fallback_.load(std::memory_order_acquire))
    {
        processFallback(in, out, n);
        return;
    }
    // Offline bounce: build and submit the changed scene before this block (AQ4 synchronous rebuild).
    const bool offline = nonRealtime_.load(std::memory_order_acquire);
    if (offline && engine_.isPrepared() && hasWork())
        decide(Source::Offline);
#ifndef NDEBUG
    // AX38 (i): the diffuse-solve gate asserts it is never entered from a real-time process().
    struct RealtimeMark
    {
        bool on;
        explicit RealtimeMark(bool realtime) noexcept
            : on(realtime)
        {
            if (on)
                ++detail::realtimeProcessDepth;
        }
        ~RealtimeMark() noexcept
        {
            if (on)
                --detail::realtimeProcessDepth;
        }
    } mark(!offline);
#endif
    const int maxBlock = std::max(1, maxBlock_);
    for (int start = 0; start < n; start += maxBlock)
    {
        const int len = std::min(maxBlock, n - start);
        const float* const inChunk[2] = {in[0] + start, in[1] + start};
        float* const outChunk[2] = {out[0] + start, out[1] + start};
        engine_.process(inChunk, outChunk, len);
        applyTrim(outChunk, len);
    }
}

// ---- inspection ----

std::optional<std::uint64_t> ScenePipeline::handledGeneration() const
{
    const auto h = handled_.load(std::memory_order_acquire);
    if (h == kNone)
        return std::nullopt;
    return h;
}

bool ScenePipeline::restorePending() const
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    return restoreGen_.has_value();
}

std::shared_ptr<const sim::RoomIR> ScenePipeline::lastSubmittedIr() const
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    return lastIr_;
}

std::shared_ptr<const sim::conv::IrSet> ScenePipeline::lastSubmittedIrSet() const
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    return lastIrSet_;
}

void ScenePipeline::injectBuildFailures(int count) noexcept
{
    injectedFailures_.store(count, std::memory_order_release);
}

void ScenePipeline::setAfterSnapshotHook(std::function<void()> hook)
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    afterSnapshot_ = std::move(hook);
}

double ScenePipeline::tailLengthSeconds() const noexcept
{
    // The longest IR the builder can produce (the 12 s cap of Phase 04 plus the AX1 pre-roll): hosts
    // keep processing (and bounces keep rendering) for this long after the input stops.
    const double rate = sampleRate_ > 0.0 ? sampleRate_ : 48000.0;
    return static_cast<double>(sim::RealtimeEngine::maxIrLengthSamples(rate)) / rate;
}

bool ScenePipeline::builderIdle() const
{
    return !hasWork() && builder_->idleOrWaiting();
}

} // namespace plugin
