#include "plugin/core/ScenePipeline.h"

#include "contract/Json.h"
#include "contract/Validate.h"
#include "module3d/SceneModel.h"
#include "plugin/core/DefaultSceneJson.h"
#include "sim/diffuse/DiffuseEstimator.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <utility>

namespace plugin {

namespace {

std::uint64_t platformTag() noexcept; // AX48 Pi (below)

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
    , platformTag_(platformTag())
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
        *clock_,
        [this] {
            watchHostRate(); // condition 6: the render-log watch, on the builder thread
            return hasWork();
        },
        [this] { decide(Source::Builder); });
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

namespace {

std::uint64_t fnv(const void* p, std::size_t n, std::uint64_t h = 0xcbf29ce484222325ull) noexcept
{
    const auto* c = static_cast<const unsigned char*>(p);
    for (std::size_t i = 0; i < n; ++i)
    {
        h ^= c[i];
        h *= 0x100000001b3ull;
    }
    return h;
}

// AX48 Pi: OS family + CPU architecture, a compile-time constant.
constexpr const char* kPlatformName =
#if defined(_WIN32)
    "windows-"
#elif defined(__APPLE__)
    "macos-"
#elif defined(__linux__)
    "linux-"
#else
    "other-"
#endif
#if defined(__aarch64__) || defined(_M_ARM64)
    "arm64";
#elif defined(__x86_64__) || defined(_M_X64)
    "x64";
#else
    "other";
#endif

std::uint64_t platformTag() noexcept
{
    return fnv(kPlatformName, std::strlen(kPlatformName));
}

// The max |level step| in dB over bands and present emitters between two builds' tail amplitudes.
double stepDb(const sim::HybridDiagnostics& from, const sim::HybridDiagnostics& to) noexcept
{
    double worst = 0.0;
    const std::size_t n = std::min(from.emitters.size(), to.emitters.size());
    for (std::size_t e = 0; e < n; ++e)
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            const double a = from.emitters[e].match.bandsAmplitude[b];
            const double c = to.emitters[e].match.bandsAmplitude[b];
            if (a > 0.0 && c > 0.0)
                worst = std::max(worst, std::abs(20.0 * std::log10(c / a)));
        }
    return worst;
}

// AX47 measurement (review M2): the realised tail energy per present emitter and band over emission times
// [t_mix,e, endS), A_b^2 sum w_tail^2 u_b^2 on the unit decays actually played (the construction's band
// split).
std::vector<contract::BandArray> realisedTailEnergy(const std::vector<sim::tail::UnitDecay>& units,
                                                    const sim::HybridDiagnostics& d, double endS)
{
    std::vector<contract::BandArray> out(d.emitters.size());
    const double fs = d.sampleRate;
    const auto offset = static_cast<std::size_t>(std::max(0.0, std::round(d.alignmentShiftS * fs)));
    for (std::size_t e = 0; e < d.emitters.size() && e < units.size(); ++e)
    {
        const auto& u = units[e];
        const double mix = d.emitters[e].match.mixing.mixS;
        const auto from = static_cast<std::size_t>(std::max(0.0, std::ceil(mix * fs)));
        const auto to = std::min(u.length(), static_cast<std::size_t>(std::max(0.0, endS * fs)));
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
        {
            const double a = d.emitters[e].match.bandsAmplitude[b];
            double sum = 0.0;
            for (std::size_t j = std::max(from, offset); j < to; ++j)
            {
                const double w =
                    sim::tail::crossfade(static_cast<double>(j - offset) / fs + d.alignmentShiftS, mix).tail;
                sum += w * w * u.bands[b][j] * u.bands[b][j];
            }
            out[e][b] = a * a * sum;
        }
    }
    return out;
}

double realisedStepDb(const std::vector<contract::BandArray>& from,
                      const std::vector<contract::BandArray>& to) noexcept
{
    double worst = 0.0;
    for (std::size_t e = 0; e < std::min(from.size(), to.size()); ++e)
        for (std::size_t b = 0; b < contract::kNumOctaveBands; ++b)
            if (from[e][b] > 0.0 && to[e][b] > 0.0)
                worst = std::max(worst, std::abs(10.0 * std::log10(to[e][b] / from[e][b])));
    return worst;
}

} // namespace

DiffuseKey ScenePipeline::engineKey() noexcept
{
    DiffuseKey k;
    const sim::diffuse::DiffuseLimits limits; // the shipping limits (W_max, n*_max, SE_target)
    std::uint64_t h = fnv(&limits.wScene, sizeof limits.wScene);
    h = fnv(&limits.nStarMax, sizeof limits.nStarMax, h);
    h = fnv(&limits.seTargetDb, sizeof limits.seTargetDb, h);
    k.ePrec = h;
    k.eModel = sim::diffuse::kEstimatorModelId;
    k.platform = platformTag();
    return k;
}

std::uint64_t ScenePipeline::sceneKey(const contract::SceneDescription& scene)
{
    // AX48 S: the effective scene without outputMode, hrtfId and tailSeed (AX40, AX44), canonical JSON.
    contract::SceneDescription s = scene;
    s.render.outputMode = contract::OutputMode::binaural;
    s.render.hrtfId = contract::kHrtfIdGenericV1;
    s.render.tailSeed = 0;
    const std::string json = contract::toJson(s);
    return fnv(json.data(), json.size());
}

void ScenePipeline::setPlatformTagForTest(std::uint64_t tag)
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    platformTag_ = tag;
}

sim::StagedBuild ScenePipeline::planStage(const contract::SceneDescription& scene, Source source,
                                          const std::function<void(BuildStage)>& hook)
{
    // The offline path takes the gate only after quiesce() has returned (AX38 (i)).
    assert(source != Source::Offline || !builder_->accepting());
    sim::BuildOptions options;
    options.sampleRate = sampleRate_;
    options.kind = sim::BuildOptions::Kind::Omni; // Phase 07: the omni hybrid IR until 08/09
    options.cancel = source == Source::Builder ? &builderAbandon_ : nullptr;
    options.parallelEmitterSynthesis = true; // AX49: the two emitters in parallel (bit-identical to serial)
    if (hook)
        hook(BuildStage::Plan);
    return sim::StagedBuild::plan(scene, options);
}

ScenePipeline::Level ScenePipeline::solveStage(sim::StagedBuild& build, Source source,
                                               const std::function<void(BuildStage)>& hook, std::uint64_t p,
                                               std::uint64_t s)
{
    const bool builder = source == Source::Builder;
    const auto cls = builder ? DiffuseSolveGate::Class::Builder
                             : (source == Source::Offline ? DiffuseSolveGate::Class::Offline
                                                          : DiffuseSolveGate::Class::Synchronous);
    const std::atomic<bool>* abandon = builder ? &builderAbandon_ : nullptr;
    // Condition 12 (D-G1; AX38 (i): the gate is "held only around the solve"): the solve pool is passed only
    // while the gate is held; the RAII Scope releases it on every exit, a BuildCancelled thrown inside the
    // solve included. Nothing under the gate takes stateMutex_ (the hook was copied before).
    if (build.needsSolve())
    {
        DiffuseSolveGate::Scope gate(*gate_, cls, abandon);
        if (!gate.entered())
            throw sim::BuildCancelled();
        if (hook)
            hook(BuildStage::Solve);
        build.solve(&gate_->pool());
    }
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        ++stats_.solves;
        if (source == Source::Synchronous)
            ++stats_.syncSolves;
    }
    Level level;
    level.bands = build.diffuseLevel().value_or(sim::EmitterBands{});
    level.p = p;
    level.s = s;
    level.solved = true;
    return level;
}

void ScenePipeline::setStageHook(std::function<void(BuildStage)> hook)
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    stageHook_ = std::move(hook);
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

bool ScenePipeline::decide(Source source, bool load)
{
    // The generation is read BEFORE the snapshot: a change after it is a later generation.
    const std::uint64_t gen = dirty_.load(std::memory_order_acquire);
    try
    {
        const module3d::ParameterValues values = parameterValues();
        contract::SceneDescription scene;
        std::function<void()> hook;
        std::function<void(BuildStage)> stageHook;
        Built b;
        std::optional<Level> held;
        std::optional<SavedDiffuse> saved;
        std::optional<Pending> pending;
        std::shared_ptr<const std::vector<sim::tail::UnitDecay>> units;
        bool restoreBg = false;
        std::uint64_t platform = 0;
        {
            std::lock_guard<std::mutex> lock(stateMutex_);
            scene = module3d::deriveScene(values, base_);
            hook = afterSnapshot_;
            stageHook = stageHook_; // copied once, before the gate: nothing under the gate takes stateMutex_
            if (builtScene_ && *builtScene_ == scene && builtIrSet_) // AX5: same scene, same (final) IR
            {
                b.ir = builtIr_;
                b.irSet = builtIrSet_;
                b.final = true;
                if (held_)
                    b.level = *held_;
            }
            held = held_;
            if (source == Source::Synchronous)
                saved = saved_;
            pending = pending_;
            if (units_ && unitsSeed_ == scene.render.tailSeed && unitsRate_ == sampleRate_)
                units = units_;
            restoreBg = restoreGen_.has_value() && gen >= *restoreGen_;
            platform = platformTag_;
        }
        if (hook)
            hook();
        if (injectedFailures_.load(std::memory_order_acquire) > 0)
        {
            injectedFailures_.fetch_sub(1, std::memory_order_acq_rel);
            throw std::runtime_error("injected build failure (test hook)");
        }
        if (b.irSet)
            return commit(source, gen, scene, b);

        const auto* abandon = source == Source::Builder ? &builderAbandon_ : nullptr;
        sim::StagedBuild build = planStage(scene, source, stageHook);
        const std::uint64_t p = build.problemHash();
        const std::uint64_t s = sceneKey(scene);
        // A level solved in this process for this very problem is final: a change of seed, output mode or
        // HRTF never re-solves (AX48).
        std::optional<Level> level;
        if (held && held->solved && held->p == p && held->s == s)
            level = held;
        else if (pending && pending->level.solved && pending->level.p == p && pending->level.s == s)
            level = pending->level;

        // Builds the tail over the cached unit decays when they are this scene's (exact, AQ4), else
        // synthesises the exact tail (in parallel per emitter, AX49). Final builds only.
        const auto finishExact = [&](Level lv) {
            build.useDiffuseLevel(
                lv.bands); // the solve's own result, or the held / saved one: same arithmetic
            if (stageHook)
                stageHook(BuildStage::Assemble);
            if (units)
                build.useUnitDecays(units);
            const bool cachedExact = units && build.unitDecaysExact();
            if (units && !cachedExact)
                build.useUnitDecays(
                    nullptr); // not this scene's decays: synthesise (never a bridge in a final)
            b.ir = std::make_shared<const sim::RoomIR>(build.assemble(&b.diag));
            b.units = build.unitDecays();
            b.level = lv;
            b.final = lv.solved;
        };

        if (source == Source::Synchronous)
        {
            // Condition 9 / AX49 / AX48: ISM + matching + the interim tail + mix, synchronously, where no
            // IrSet valid at the current rate is current (prepare, project load). Keyed: the saved level;
            // keyless: the stage-1 (A) solve inside the AX38 gate (FM-3'), the final in 07c-1.
            if (!level)
            {
                DiffuseKey key = engineKey();
                key.p = p;
                key.s = s;
                key.platform = platform;
                if (load && saved && saved->key == key)
                {
                    level = Level{saved->bands, p, s, false};
                    std::lock_guard<std::mutex> lock(stateMutex_);
                    ++stats_.keyedLoads;
                }
                else if (!load && (held || pending))
                {
                    // prepare(): hold the previous E_b with the specular part recomputed (B1'); the builder
                    // solves.
                    level = held ? Level{held->bands, p, s, false} : Level{pending->level.bands, p, s, false};
                    b.heldLevel = true;
                }
                else
                {
                    level = solveStage(build, source, stageHook, p, s);
                    std::lock_guard<std::mutex> lock(stateMutex_);
                    if (load)
                        ++stats_.keylessLoads;
                    else
                        ++stats_.insertSolves; // a fresh instance's first prepare (review M1; phase-07c-1b)
                }
            }
            if (units)
                build.useUnitDecays(units);
            if (units && build.unitDecaysExact())
                finishExact(*level); // this scene's exact unit decays are cached (AQ4): no provisional
            else
            {
                build.useUnitDecays(nullptr);
                build.useDiffuseLevel(level->bands);
                if (stageHook)
                    stageHook(BuildStage::Assemble);
                const bool provisional = build.provisionalTiming().provisional;
                b.ir = std::make_shared<const sim::RoomIR>(build.assembleProvisional(&b.diag));
                b.provisional = provisional;
                if (provisional && build.unitDecays())
                {
                    b.windowEndS = build.provisionalTiming().fadeStartS;
                    b.realised = realisedTailEnergy(*build.unitDecays(), b.diag, b.windowEndS);
                }
                b.level = *level;
                // Where L_p >= L the exact tail was built in its place (no handover, AX49).
                b.final = level->solved && !provisional;
                if (!provisional)
                    b.units = build.unitDecays();
            }
        }
        else if (source == Source::Offline)
        {
            // Condition 6: offline renders wait for the final solve and never use an interim (AX5, AX49).
            if (!level)
                level = solveStage(build, source, stageHook, p, s);
            finishExact(*level);
        }
        else
        {
            const bool continuation = pending && pending->scene == scene;
            // B1': hold the previous E_b, the last final's, or before the first final the interim's that
            // plays.
            if (!held && pending)
                held = pending->level;
            if (!level && !continuation && !restoreBg && held)
            {
                // Condition 4: an edit. The ISM update is never held behind the diffuse solve: submit the new
                // early part at once over the held level (B1', AX48) and the cached unit decays (AQ4; on a
                // T60-changing edit the AX49 D5 bridge, the old decays at the ebar of the decay played), then
                // solve. Without a cache (the exact tail not built yet), the AX49 provisional tail.
                build.useDiffuseLevel(held->bands);
                if (stageHook)
                    stageHook(BuildStage::Assemble);
                Built interim;
                interim.level = Level{held->bands, p, s, false};
                if (units)
                {
                    build.useUnitDecays(units);
                    interim.ir = std::make_shared<const sim::RoomIR>(build.assemble(&interim.diag));
                }
                else
                {
                    interim.provisional = build.provisionalTiming().provisional;
                    interim.ir = std::make_shared<const sim::RoomIR>(
                        build.assembleProvisional(&interim.diag));
                    if (interim.provisional && build.unitDecays())
                    {
                        interim.windowEndS = build.provisionalTiming().fadeStartS;
                        interim.realised = realisedTailEnergy(*build.unitDecays(), interim.diag,
                                                              interim.windowEndS);
                    }
                }
                interim.final = false;
                interim.heldLevel = true;
                interim.irSet = engine_.makeIrSet(*interim.ir, abandon);
                (void)commit(source, gen, scene,
                             interim); // an interim never records the generation as handled
                // Never mid-drag: a solve starts only once the parameters held still through the ISM update.
                if (dirty_.load(std::memory_order_acquire) != gen)
                {
                    std::lock_guard<std::mutex> lock(stateMutex_);
                    ++stats_.discardedMidDrag;
                    return false;
                }
                build.useUnitDecays(nullptr);
            }
            // The solve: a continuation of a keyed load (the confirming solve, AX48), of a provisional load,
            // an edit after its ISM update, or a background restore with an IrSet current.
            if (!level)
                level = solveStage(build, source, stageHook, p, s);
            // Never mid-drag: a solved snapshot is adopted only if no change arrived while it was solved.
            if (dirty_.load(std::memory_order_acquire) != gen)
            {
                std::lock_guard<std::mutex> lock(stateMutex_);
                ++stats_.discardedMidDrag;
                return false;
            }
            finishExact(*level);
        }
        b.irSet = engine_.makeIrSet(*b.ir, abandon); // condition 10: a cancel point of builder decisions
        return commit(source, gen, scene, b);
    }
    catch (const std::exception&)
    {
        // std::bad_alloc, a cancelled builder build (sim::BuildCancelled: the builder was quiesced and its
        // result would be discarded anyway) or an unexpected build failure: nothing is recorded as handled
        // and the current IR keeps playing; the generation is built again like a failed submit (D7).
        return false;
    }
}

bool ScenePipeline::commit(Source source, std::uint64_t gen, const contract::SceneDescription& scene,
                           Built& b)
{
    // Phase-07c-1 condition 10 (steward round 6): stateMutex_ is held for pointer swaps and counters only.
    // The D7 bit-identity comparison, the AX47 step measurement and every release of a previous IR, IrSet,
    // unit-decay cache or interim record run outside it, so a host call that takes the lock
    // (setNonRealtime(true), an offline reset(), restore(), the queries) never waits for builder work. The
    // deciding thread is the only committer; a drop in between (offline entry) is detected by the lastIr_
    // pointer changing.
    std::shared_ptr<const sim::RoomIR> last;
    std::optional<Pending> pend;
    std::function<void(BuildStage)> hook;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        last = lastIr_;
        if (pending_ && pending_->scene == scene)
            pend = pending_;
        hook = stageHook_;
    }
    const bool identical = last && bitIdentical(*b.ir, *last);
    double step =
        -1.0; // AX47: the step from the interim to this final (measured here, never in the callback)
    if (b.final && pend)
        // A provisional interim: the realised step over [t_mix,e, L_f) on the decays played (review M2);
        // otherwise (held level, bridge) the amplitude step on the same decays.
        step = !pend->realised.empty() && b.units
                   ? realisedStepDb(pend->realised, realisedTailEnergy(*b.units, b.diag, pend->windowEndS))
                   : stepDb(pend->diag, b.diag);
    pend.reset();
    if (hook)
        hook(BuildStage::Commit); // test hook: outside stateMutex_

    // Released after the lock (declared before it, so destroyed after it).
    std::shared_ptr<const sim::RoomIR> oldIr, oldBuiltIr;
    std::shared_ptr<const sim::conv::IrSet> oldIrSet, oldBuiltIrSet;
    std::shared_ptr<const std::vector<sim::tail::UnitDecay>> oldUnits;
    std::optional<Pending> oldPending;
    std::lock_guard<std::mutex> lock(stateMutex_);
    if (source == Source::Builder && !builder_->accepting())
        return false; // quiesced while building: the result is discarded, not submitted
    const bool sameLast = lastIr_ == last;
    if (b.final)
    {
        oldBuiltIr = std::exchange(builtIr_, b.ir);
        oldBuiltIrSet = std::exchange(builtIrSet_, b.irSet);
        builtScene_ = scene;
        builtGen_ = gen;
        if (b.units)
        {
            oldUnits = std::exchange(units_, b.units);
            unitsSeed_ = scene.render.tailSeed;
            unitsRate_ = sampleRate_;
        }
    }
    const bool restoreDecision = restoreGen_.has_value() && gen >= *restoreGen_;
    const auto finishRecord = [&] {
        if (b.final)
        {
            handled_.store(gen, std::memory_order_release);
            held_ = b.level;
            oldPending = std::move(pending_);
            pending_.reset();
            interimPlaying_.store(false, std::memory_order_release);
        }
        if (restoreDecision)
            restoreGen_.reset();
    };
    const bool settling = b.final && pending_ && pending_->scene == scene;
    // Skip rule (D7): the same scene already plays at least as final as this, or the IR is bit-identical to
    // the last successful submit since prepare() or the last drop (offline entry / offline reset).
    if (lastIr_
        && ((lastScene_ && *lastScene_ == scene && (lastFinal_ || !b.final)) || (sameLast && identical)))
    {
        if (settling)
        {
            ++stats_.steps; // the settling step was 0 (AX47 (a): a keyed level confirmed bit for bit)
            stats_.lastStepDb = 0.0;
        }
        if (b.final)
        {
            lastFinal_ = true;
            lastScene_ = scene;
        }
        finishRecord();
        return b.final;
    }
    // AX18 / FM-1: the restore's first submit is equal-power; every other step, a same-scene settling step
    // included, is equal-gain.
    const auto law = restoreDecision ? sim::conv::CrossfadeLaw::EqualPower
                                     : sim::conv::CrossfadeLaw::EqualGain;
    if (!b.irSet || !engine_.submitIrSet(b.irSet, law))
    {
        // Records nothing as handled (D7): the generation still differs from the handled one, so it is built
        // again (by the builder after its AX33 slot, or by the next offline block).
        return false;
    }
    if (settling && step >= 0.0)
    {
        ++stats_.steps;
        stats_.lastStepDb = step;
        stats_.maxStepDb = std::max(stats_.maxStepDb, step);
        if (pending_->held)
            ++stats_.heldSteps;
    }
    oldIr = std::exchange(lastIr_, b.ir);
    oldIrSet = std::exchange(lastIrSet_, b.irSet);
    lastScene_ = scene;
    lastFinal_ = b.final;
    if (b.final)
        ++stats_.finalSubmits;
    else
    {
        ++stats_.interimSubmits;
        if (b.provisional)
            ++stats_.provisionalSubmits;
        oldPending = std::move(pending_);
        pending_ = Pending{scene,       b.level, std::move(b.diag), b.heldLevel, std::move(b.realised),
                           b.windowEndS};
        interimPlaying_.store(true, std::memory_order_release);
    }
    finishRecord();
    return b.final;
}

ScenePipeline::Stats ScenePipeline::stats() const
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    return stats_;
}

std::vector<std::string> ScenePipeline::renderLog() const
{
    std::vector<std::string> out;
    const auto events = rateEvents_.load(std::memory_order_acquire);
    if (events > 0)
    {
        char line[320];
        std::snprintf(
            line, sizeof line,
            "render log: offline signal unreliable: the host processed %.2f s of audio in %.2f s of wall "
            "clock without setNonRealtime(true) while the reverb was settling (condition 6; %llu "
            "episode(s))",
            rateAudioS_.load(std::memory_order_relaxed), rateWallS_.load(std::memory_order_relaxed),
            static_cast<unsigned long long>(events));
        out.emplace_back(line);
    }
    return out;
}

std::optional<SavedDiffuse> ScenePipeline::savedDiffuse() const
{
    const auto values = parameterValues();
    std::lock_guard<std::mutex> lock(stateMutex_);
    if (!held_ || !held_->solved)
        return std::nullopt;
    if (held_->s != sceneKey(module3d::deriveScene(values, base_)))
        return std::nullopt; // the current scene is not solved yet
    SavedDiffuse out;
    out.bands = held_->bands;
    out.key = engineKey();
    out.key.p = held_->p;
    out.key.s = held_->s;
    out.key.platform = platformTag_;
    return out;
}

void ScenePipeline::watchHostRate() noexcept
{
    // Condition 6 (builder thread): the host processes audio much faster than real time while an interim
    // plays and offline was not signalled: a bounce would capture the interim. Recorded once per episode.
    if (sampleRate_ <= 0.0)
        return;
    const double now = clock_->now();
    const std::uint64_t samples = processedSamples_.load(std::memory_order_relaxed);
    if (rateWindowStart_ < 0.0 || samples < rateWindowSamples_)
    {
        rateWindowStart_ = now;
        rateWindowSamples_ = samples;
        return;
    }
    const double wall = now - rateWindowStart_;
    const double audio = static_cast<double>(samples - rateWindowSamples_) / sampleRate_;
    if (audio < kHostRateWindowS)
    {
        if (wall > 4.0 * kHostRateWindowS)
        {
            rateWindowStart_ = now; // real time or slower: restart the window
            rateWindowSamples_ = samples;
            rateLogged_ = false;
        }
        return;
    }
    const bool fast = audio > kHostRateFactor * wall;
    const bool offline = nonRealtime_.load(std::memory_order_acquire);
    const bool interim = interimPlaying_.load(std::memory_order_acquire);
    if (fast && !offline && interim && !rateLogged_)
    {
        // Called under the builder's mutex (hasWork()): no other lock here. The figures go to atomics and
        // renderLog() writes the line.
        rateAudioS_.store(audio, std::memory_order_relaxed);
        rateWallS_.store(wall, std::memory_order_relaxed);
        rateEvents_.fetch_add(1, std::memory_order_release);
        rateLogged_ = true;
    }
    if (!fast)
        rateLogged_ = false;
    rateWindowStart_ = now;
    rateWindowSamples_ = samples;
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
        // The IRs are dropped: no interim plays. The held level and the unit-decay cache stay (the cache is
        // keyed on the rate: at another rate it is not used and AX49's synchronous interim is built).
        pending_.reset();
        lastFinal_ = false;
        interimPlaying_.store(false, std::memory_order_release);
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
        // The initial IR, installed at once at the first partition. A restore stored before this prepare (the
        // Logic order: setStateInformation, then prepareToPlay) makes it a project load (AX48's keyed rule).
        bool load = false;
        {
            std::lock_guard<std::mutex> lock(stateMutex_);
            load = restoreGen_.has_value();
        }
        decide(Source::Synchronous, load);
        restartBuilder();
    }
    // Offline: the next process() builds and submits (the only submitter during a bounce).
}

void ScenePipeline::reset()
{
    // Phase-07c-1 condition 10 (D-H3 (e): Seat 3's (e-k) + Seat 2's (e-e)): reset() never waits on the
    // builder and never builds.
    if (nonRealtime_.load(std::memory_order_acquire))
    {
        dropForOffline(); // offline branch unchanged: drop; the next process() builds before its block
        return;
    }
    // Realtime: clear the convolver's history, pending output and counter but KEEP the current IrSet
    // (a running fade ends on its target), so the output is never silent. Nothing is stale: the scene did
    // not change, so an in-flight build (if any) is of the current generation and its result arrives as
    // an ordinary AQ4 / AX31 update; the D7 record (last submit) still describes what plays. The engine
    // reset may overlap a builder submit (RealtimeEngine::resetKeepIr touches neither the mailbox nor the
    // release queue's consumer side); it is never concurrent with process() (host contract).
    if (!fallback_.load(std::memory_order_acquire))
        engine_.resetKeepIr();
    snapTrim();
}

void ScenePipeline::cancelBuilder() noexcept
{
    builderAbandon_.store(
        true, std::memory_order_release); // a running builder build stops at its next cancel point
    gate_->notifyWaiters();               // a builder waiting at the gate leaves the queue
    builder_->stopAccepting();            // no new decision; no wait (condition 10)
}

void ScenePipeline::dropForOffline()
{
    cancelBuilder();
    if (fallback_.load(std::memory_order_acquire) || !engine_.isPrepared())
    {
        snapTrim(); // AX34: nothing to drop
        return;
    }
    // The previous IR and IrSet (and the interim record) are released after the lock (steward round 6).
    std::shared_ptr<const sim::RoomIR> oldIr;
    std::shared_ptr<const sim::conv::IrSet> oldIrSet;
    std::optional<Pending> oldPending;
    {
        // A builder submit runs under stateMutex_ and checks accepting() first, so after stopAccepting()
        // no builder submit can reach the engine once this lock is taken: the drop never races a submit
        // (it waits at most for one commit's pointer swaps, never for a build or a comparison).
        std::lock_guard<std::mutex> lock(stateMutex_);
        engine_.reset(); // drop every IR (the offline render starts exact from the first block)
        oldIr = std::move(lastIr_);
        oldIrSet = std::move(lastIrSet_);
        lastIr_.reset();
        lastIrSet_.reset();
        lastScene_.reset();
        lastFinal_ = false;
        oldPending = std::move(pending_);
        pending_.reset();
        interimPlaying_.store(false, std::memory_order_release);
        handled_.store(kNone, std::memory_order_release);
    }
    snapTrim();
}

void ScenePipeline::setNonRealtime(bool nonRealtime)
{
    const bool was = nonRealtime_.exchange(nonRealtime, std::memory_order_acq_rel);
    if (was == nonRealtime)
        return;
    if (nonRealtime)
        dropForOffline(); // enter (condition 10): cancel, drop, no wait and no build; process() builds
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

void ScenePipeline::restore(const contract::SceneDescription& base, const module3d::ParameterValues& values,
                            const std::optional<SavedDiffuse>& saved)
{
    quiesceBuilder(); // also when the caller skipped beginRestore()
    bool synchronous = false;
    {
        std::lock_guard<std::mutex> lock(stateMutex_);
        base_ = module3d::SceneModel::sanitize(base);
        saved_ = saved;
        // AX48 / AX49: synchronous where no IrSet valid at the current rate is current (the engine keeps none
        // across prepare) or at the instance's first restore (project load); otherwise (undo, preset recall
        // during playback) everything runs in the background and the current IrSet plays.
        synchronous = !loadedState_ || !lastIrSet_;
        loadedState_ = true;
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
        if (synchronous)
            decide(Source::Synchronous,
                   true); // the restore's decision (interim or final): EqualPower, or a skip
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
    {
        // Condition 10: setNonRealtime(true) / reset() only cancelled the builder; a cancelled decision may
        // still be unwinding to its next cancel point. The offline thread may wait (AQ4, NFR-6): it waits
        // for that before it becomes the only submitter.
        builder_->quiesce();
        decide(Source::Offline);
    }
#ifndef NDEBUG
    // AX38 (i): the diffuse-solve gate asserts it is never entered from a real-time process(). Debug builds
    // only: two thread_local stores on the real-time path (no allocation, no lock, no syscall); nothing in
    // release.
    struct RealtimeMark
    {
        bool on;
        explicit RealtimeMark(bool realtime) noexcept
            : on(realtime)
        {
            if (on)
            {
                ++detail::realtimeProcessDepth;
                detail::ranRealtimeProcess =
                    true; // D-H3 (e): the gate counts later Synchronous entries from here
            }
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
    processedSamples_.fetch_add(static_cast<std::uint64_t>(n),
                                std::memory_order_relaxed); // condition 6 watch
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

bool ScenePipeline::builderBusy() const
{
    return builder_->busy();
}

} // namespace plugin
