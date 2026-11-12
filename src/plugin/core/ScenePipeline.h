#pragma once

// The plugin's scene -> IR -> convolution pipeline (Phase 07 scope 3), JUCE-free so that it can be
// tested headless and under TSan. The JUCE AudioProcessor (src/plugin/PluginProcessor) is a thin
// adapter: it forwards host parameters (setParameter), the host lifecycle (prepare, reset, release,
// setNonRealtime), state restores (beginRestore / restore) and audio (process).
//
// Ownership and threads
//   - Parameters: an array of atomics, written by setParameter() on any thread (the APVTS listener;
//     often the audio thread) together with ONE lock-free fetch_add on the dirty generation. Nothing else.
//   - Non-parameter scene fields (materials, gains, seed, ...): the base scene, owned under stateMutex_,
//     replaced only by restore() with the builder quiesced.
//   - The scene is a pure function of (parameters, base scene): module3d::deriveScene().
//   - The engine (sim::RealtimeEngine, the only way to the convolver): process() on the audio thread;
//     submits from the builder thread (realtime) or, with the builder quiesced, from the host thread
//     (prepare, restore) or the processing thread during an offline bounce; prepare() only with the
//     builder quiesced (no submit in flight); the realtime reset's resetKeepIr() may overlap a builder
//     submit; the offline drop (setNonRealtime(true), offline reset()) runs under stateMutex_ after the
//     builder stopped accepting, so no submit reaches the engine during it (phase-07c-1 condition 10).
//     None of them concurrently with process().
//   - The decision state (last handled generation, last submitted IR, restore flag): under stateMutex_,
//     taken by the builder, the host-thread calls and the offline process(). The realtime process()
//     never takes a lock or allocates.
//
// Switch rule (decider D7, accepted by Maisara 2026-11-08): a submit is skipped when the built IR is
// bit-identical to the last successful submit's since the last prepare()/reset() (the build itself is
// skipped when the derived scene equals that submit's scene: AX5). A skip records its generation as
// handled, as a successful submit does; a failed submit records nothing; every engine prepare() clears
// the record. restore() advances the dirty generation to g_R and sets the restore flag; the first
// decision at a generation >= g_R submits with EqualPower (AX18) or skips, and clears the flag either
// way. Every other submit uses EqualGain (AX18 placeholder until Phase 10).
#include "contract/SceneDescription.h"
#include "module3d/ParameterMap.h"
#include "plugin/core/DiffuseSolveGate.h"
#include "plugin/core/IrBuilderThread.h"
#include "sim/Engine.h"
#include "sim/RealtimeEngine.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <vector>

namespace plugin {

// The default scene, embedded from tests/scenes/valid/medium_room.json (scope 5; not a preset).
const contract::SceneDescription& defaultScene();

class ScenePipeline
{
public:
    // AQ10 / phase-06b D1: P = 512, reported latency P + 32 = 544 samples (AX1).
    static constexpr int kPartitionSize = 512;
    // Output trim smoothing (scope 3): a linear gain ramp over 20 ms.
    static constexpr double kTrimRampS = 0.020;

    // clock: nullptr = the steady clock (tests inject one for AX33).
    explicit ScenePipeline(BuilderClock* clock = nullptr);
    ~ScenePipeline();
    ScenePipeline(const ScenePipeline&) = delete;
    ScenePipeline& operator=(const ScenePipeline&) = delete;

    // ---- parameters (any thread, lock-free) ----
    // Stores the plain value and increments the dirty generation (one fetch_add). No lock, no allocation.
    void setParameter(std::size_t index, float plainValue) noexcept;
    float parameter(std::size_t index) const noexcept;
    module3d::ParameterValues parameterValues() const noexcept;

    // ---- host lifecycle (never concurrent with process() or each other; reset() and setNonRealtime() may
    // arrive on the processing thread and never wait or build: phase-07c-1 condition 10) ----
    // Quiesces the builder, prepares the engine (drops its IRs, clears the handled record). At a rate
    // outside AX6 it enters the AX34 fallback (input delayed by latencySamples(), warning flag). Otherwise
    // realtime: builds and submits the current scene synchronously, then restarts the builder; offline:
    // leaves the build to the next process() (the only submitter during a bounce).
    void prepare(double sampleRate, int maxBlock, bool nonRealtime);
    // Phase-07c-1 condition 10: never waits on the builder and never builds (it may arrive on the VST3
    // processing thread). Realtime: clears the convolver's history, pending output and counter, keeps the
    // current IrSet (the output is never silent) and snaps the trim. Offline: as setNonRealtime(true).
    void reset();
    // Entering non-realtime mode (condition 10): cancels the builder (no wait), drops the IRs; the next
    // process() waits for the cancelled build to unwind and builds before its block (X11, NFR-6). Leaving
    // it restarts the builder.
    void setNonRealtime(bool nonRealtime);
    // Quiesces the builder (host releaseResources()); it stays stopped until the next prepare().
    void release();

    // ---- state (non-audio thread) ----
    // Quiesces the builder before the host's parameter values are replaced (so no half-restored
    // scene is built). Must be followed by restore().
    void beginRestore();
    // Installs `base` (sanitised) and `values`, advances the dirty generation to g_R and sets the restore
    // flag. Realtime with the engine prepared: makes the restore's decision now (EqualPower or a skip) and
    // restarts the builder. Before prepare(), offline or in the AX34 fallback: only stores; the decision
    // is the next prepare()'s (realtime) or process()'s (offline).
    void restore(const contract::SceneDescription& base, const module3d::ParameterValues& values);
    // The base scene (non-parameter fields) and the current derived scene.
    contract::SceneDescription baseScene() const;
    contract::SceneDescription currentScene() const;

    // ---- audio thread ----
    // in[c], out[c]: n samples, c = 0, 1; in may equal out. n <= maxBlock of prepare(). Realtime: no
    // allocation, lock or I/O. Offline: first builds and submits the scene if it changed (synchronous,
    // AQ4), then processes.
    void process(const float* const in[2], float* const out[2], int n) noexcept;

    // ---- queries ----
    int latencySamples() const noexcept { return kPartitionSize + sim::kAlignPreRollSamples; }
    bool unsupportedRateFallback() const noexcept { return fallback_.load(std::memory_order_acquire); }
    bool isNonRealtime() const noexcept { return nonRealtime_.load(std::memory_order_acquire); }

    // The reverb tail hosts must keep rendering after the input stops (AudioProcessor::
    // getTailLengthSeconds): the longest IR the builder can produce at the prepared rate.
    double tailLengthSeconds() const noexcept;

    // For tests and diagnostics.
    const sim::RealtimeEngine& engine() const noexcept { return engine_; }
    std::uint64_t dirtyGeneration() const noexcept { return dirty_.load(std::memory_order_acquire); }
    // The last handled generation, or nullopt when none is recorded since the last prepare().
    std::optional<std::uint64_t> handledGeneration() const;
    bool restorePending() const;
    // The IR of the last successful submit since the last prepare()/reset() (nullptr if none).
    std::shared_ptr<const sim::RoomIR> lastSubmittedIr() const;
    std::shared_ptr<const sim::conv::IrSet> lastSubmittedIrSet() const;
    // Called on the deciding thread right after a decision's scene snapshot (test hook for D7 (d)).
    void setAfterSnapshotHook(std::function<void()> hook);
    // Condition 12 test hook: called on the deciding thread at the start of each build stage (Plan: before
    // image-source planning; Solve: inside the AX38 gate, before the diffuse solve; Assemble: after the gate,
    // before the unit-decay synthesis and the assembly). Nothing on the real-time path.
    enum class BuildStage
    {
        Plan,
        Solve,
        Assemble
    };
    void setStageHook(std::function<void(BuildStage)> hook);
    // Test hook: the next `count` decisions fail as a build failure would (nothing recorded).
    void injectBuildFailures(int count) noexcept;
    // True when the builder has nothing to do (for tests that wait for it).
    bool builderIdle() const;
    // True while a builder decision runs (tests and records: the condition 10 cancel latency).
    bool builderBusy() const;
    // The builder's current trim gain target and value (tests).
    float trimGain() const noexcept { return trimGain_; }

    // Builds the omni IR of a scene as the pipeline does (Kind::Omni, Phase 07), with the process pool
    // and no gate. For tests and the recorded rebuild times.
    static sim::RoomIR buildIr(const contract::SceneDescription& scene, double sampleRate);
    // The diffuse-solve gate this pipeline holds (AX38 (i); tests).
    DiffuseSolveGate& gate() const noexcept { return *gate_; }

private:
    enum class Source
    {
        Builder,     // the background builder (realtime)
        Synchronous, // prepare / restore on the host thread
        Offline      // process() during a bounce
    };

    // Takes stateMutex_ itself. Returns true when the generation was recorded as handled.
    bool decide(Source source);
    // Phase 05h, the solve seam (AX38, phase-07c condition 2): the ONE function through which restore,
    // prepare, the builder and the offline process() reach the diffuse solve. Condition 12: plans outside
    // the gate, enters it in the source's class around the solve alone (the gate's pool passed only
    // there), then synthesises and assembles outside it. Throws sim::BuildCancelled when a builder
    // was quiesced while waiting or solving (D6). Never called with stateMutex_ or the builder mutex held.
    sim::RoomIR solveAndBuild(const contract::SceneDescription& scene, Source source);
    void quiesceBuilder();
    // Condition 10: abandon flag, gate notify, stop accepting; never waits.
    void cancelBuilder() noexcept;
    // Condition 10: cancelBuilder() then drop the engine's IRs and the D7 record (offline entry / reset).
    void dropForOffline();
    void restartBuilder();
    bool hasWork() const noexcept;
    void snapTrim() noexcept;
    void applyTrim(float* const out[2], int n) noexcept;
    void processFallback(const float* const in[2], float* const out[2], int n) noexcept;

    static constexpr std::uint64_t kNone = ~std::uint64_t{0};

    sim::RealtimeEngine engine_{kPartitionSize};

    std::array<std::atomic<float>, module3d::kNumParams> params_{};
    std::atomic<std::uint64_t> dirty_{0};
    std::atomic<std::uint64_t> handled_{kNone}; // written under stateMutex_; read by hasWork()
    std::atomic<int> injectedFailures_{0};      // test hook: decisions that fail before building
    std::atomic<bool> fallback_{false};
    std::atomic<bool> nonRealtime_{false};
    std::atomic<bool> active_{false}; // prepared at a supported rate and not released

    mutable std::mutex stateMutex_;
    contract::SceneDescription base_;
    std::optional<std::uint64_t> restoreGen_;             // g_R while the restore flag is set
    std::shared_ptr<const sim::RoomIR> lastIr_;           // last successful submit since prepare/reset
    std::shared_ptr<const sim::conv::IrSet> lastIrSet_;   // its IrSet
    std::optional<contract::SceneDescription> lastScene_; // its scene
    // The last built IrSet and its generation (reset step 3 reuses it when its generation is current).
    std::shared_ptr<const sim::RoomIR> builtIr_;
    std::shared_ptr<const sim::conv::IrSet> builtIrSet_;
    std::optional<contract::SceneDescription> builtScene_;
    std::uint64_t builtGen_ = kNone;
    std::function<void()> afterSnapshot_;
    std::function<void(BuildStage)> stageHook_;

    double sampleRate_ = 0.0;
    int maxBlock_ = 0;

    // Output trim (audio thread).
    float trimGain_ = 1.0f;
    float trimTarget_ = 1.0f;
    float trimStep_ = 0.0f;
    int trimRemaining_ = 0;
    int trimRampSamples_ = 1;

    // AX34 fallback delay line (latencySamples() per channel).
    std::array<std::vector<float>, 2> delay_;
    std::size_t delayPos_ = 0;

    std::unique_ptr<BuilderClock> ownClock_;
    BuilderClock* clock_ = nullptr;
    // The process-wide gate and pool (AX38 (i), AX39): shared by every pipeline alive, released after
    // the builder below is joined (member order), so the pool's threads die with the last pipeline.
    std::shared_ptr<DiffuseSolveGate> gate_ = DiffuseSolveGate::shared();
    // Set while the builder is quiesced: a builder waiting at the gate leaves, a builder solve stops
    // between blocks (D6); cleared on restart.
    std::atomic<bool> builderAbandon_{false};
    // Last member: destroyed (stopped and joined) first, before the engine and the state it uses.
    std::unique_ptr<IrBuilderThread> builder_;
};

} // namespace plugin
