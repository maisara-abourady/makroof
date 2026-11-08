# Phase 07 — Plugin integration: parameters, state, scene → IR pipeline

Size: **M** · Depends on: 01, 04, 06 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ5, AX2, AX5, AX7), PRD FR-3D-5, FR-3D-8, FR-3D-10, FR-LIC-1, NFR-2, NFR-6

## Goal

The plugin renders the room in a DAW. Listener, emitter positions and room size are **host-automatable
parameters**. The scene is saved in the DAW project and restored with an identical render. This is the
first phase where the 3D Module (`src/module3d`) and the Simulator (`src/sim`) meet, and they do so
only through `contract::SceneDescription`.

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**.

1. **Latency decision gate.** Before `prepareToPlay` reports latency (`setLatencySamples`), phase-06b
   decision 1 (the AQ10 latency reading, `docs/phases/phase-06b.md`) must be recorded; until then 07
   may build everything else. Recorded 2026-11-07: phase-06b D1 (a), P = 512, reported latency 544
   samples, accepted by Maisara 2026-11-08 (no vetoes). Phase 07 reports latencySamples() = 544 at
   the default P = 512.

## Assumptions in force

- **AQ4**: background IR rebuild, at most one per 20 ms; **synchronous rebuild in non-realtime
  (offline bounce) mode**. **AQ5**: everything runs locally.
- **AX2**: 0 dB at 1 m plus a user output trim. AX2 holds **per emitter path**; the mono preview sums
  both paths (L and R emitters) in each output. **AX5**: determinism. **AX7**: two emitters, L and R.
- Output is still the **omni** IR (mono room preview, same signal on both outputs). Binaural is Phase 08.
  07 ignores `outputMode` / `output_mode` and always renders omni (`Kind::Omni`); the stored
  `outputMode` is kept unchanged. Phase 08 changes the render of 07-era states by design (nothing has
  been released yet, so NFR-6 is not at stake).

## Scope

1. `src/module3d/SceneModel.h/.cpp` — the 3D Module's editable scene. It holds a
   `contract::SceneDescription` plus editor-only data (in `extensions`), offers typed setters that
   **clamp to valid values** (AX6 margins) so the result always validates, and has
   `toContract() const`. Pure C++, no JUCE.
2. `src/module3d/ParameterMap.h/.cpp` — the mapping between normalized host parameters and the scene:
   - Positions are normalized 0–1 **within the room** per axis, so the 0.1 m wall margin maps to 0 and 1.
     Resizing the room keeps relative positions. Document this in `docs/contract/README.md` as a 3D Module
     behaviour, not a contract rule.
   - Frozen parameter IDs (strings, never renamed): `listener_x`, `listener_y`, `listener_z`, `emL_x`,
     `emL_y`, `emL_z`, `emR_x`, `emR_y`, `emR_z`, `room_w`, `room_d`, `room_h` (in metres, range
     1.5–100, skewed), `output_trim_db` (−24…+24), `output_mode` (choice: binaural, stereoSpeakers;
     wired in 08/09), `dry_wet` is **not** included (the PRD wants the space, not a reverb send; note it
     as a possible follow-up).
   - Listener-to-emitter distances below 0.3 m are resolved by pushing the emitter away along the
     listener→emitter direction (and documented). The engine never sees an invalid scene.
   - The scene is a **pure function** of (current parameter values, non-parameter scene fields). The
     push-away is recomputed on every change; it is never stored and never written back to a host
     parameter.
3. `src/plugin/`:
   - `PluginProcessor` creates `juce::AudioProcessorValueTreeState` from `ParameterMap`. A parameter
     listener marks the scene dirty by incrementing an atomic dirty generation counter (an atomic store
     only: no allocation, no lock).
   - `IrBuilderThread` (a JUCE `Thread`, or a `std::thread` with a condition variable) coalesces dirty
     notifications, builds `contract::SceneDescription` → `sim::buildRoomIR` → `IrSet`, and submits it
     to `RealtimeEngine` (Phase 06 mailbox). It rebuilds while the generation counter has changed since
     its last build start, so the final state is always built (no lost wake-up; FR-3D-10). It runs at
     most every 20 ms. The audio thread never waits.
   - The plugin talks to the convolution engine **only through `sim::RealtimeEngine`**, never the bare
     `conv::CrossfadingConvolver` (whose `process()` leaves the output untouched when it isn't prepared)
     (PR #14 follow-up).
   - The IR builder thread is **stopped or joined (no `submitRoomIR` in flight) before
     `RealtimeEngine::prepare()` is called again or the engine is destroyed**: `prepare` drops the IRs
     and reallocates, so a concurrent submit would race it (PR #14 follow-up).
   - Non-finite host input samples and finite samples with |x| > 2²⁰ are already zeroed inside the
     engine (Phase 06, AX32).
   - Add `RealtimeEngine::reset()`: it forwards to `CrossfadingConvolver::reset()` (clears the input
     history and the sample counter, keeps the current IR). Call it from `AudioProcessor::reset()` and on
     entering non-realtime mode.
   - **Non-realtime mode** (`isNonRealtime()`): the builder thread is quiesced: it takes no new work,
     and any in-flight build is joined and drained before the first offline block. When a parameter
     changes during an offline bounce, `processBlock` builds the IR and calls `submitRoomIR` itself
     before processing that block; it is the only submitter then, so bounces are deterministic.
     "Synchronous" means the IR is submitted before the block; under AX31 it enters the output up to
     2P later, identically in every run. Leaving non-realtime mode restarts the builder thread. Widen
     the `submitRoomIR` thread comment in `RealtimeEngine.h` from "any non-audio thread" to "any
     non-audio thread, or the processing thread when nothing else submits" (code change in this phase).
   - `prepareToPlay` builds the initial IR synchronously and calls `setLatencySamples(engine.latencySamples())`.
     Latency stays constant for the life of the instance at a given sample rate.
   - Output trim is applied with a smoothed gain (20 ms).
   - Bus layout: stereo in → stereo out only.
4. **State (FR-LIC-1, NFR-6):** `getStateInformation` writes XML (or JSON in a `MemoryBlock`) with
   `pluginStateVersion` (int, starts at 1), the **full scene contract JSON**, and the APVTS parameter state.
   `setStateInformation` reads any known `pluginStateVersion`, migrates it, validates the scene and
   rebuilds the IR synchronously. If it arrives before `prepareToPlay`, it validates and stores the
   scene, and the synchronous build happens in the next `prepareToPlay`. Invalid or corrupt state falls
   back to the default scene and records a visible warning flag (shown by the UI in Phase 11), and
   never crashes.
   - On restore, the APVTS values are authoritative for every field that has a parameter, and the
     scene JSON for every other field. The scene is re-derived by the same pure function as scope 2.
     If the two disagree, the parameter wins and the JSON value is ignored.
   - Commit **state fixtures** `tests/state/v1_*.bin` and a test loading each. Every future phase that
     bumps `pluginStateVersion` adds a fixture, and old ones must keep loading.
5. Default scene: `medium_room` from `tests/scenes/valid/`, embedded as a resource. It's not a preset;
   it's just the initial state.
6. Generic editor (`juce::GenericAudioProcessorEditor`) is fine for this phase.

## Out of scope

Binaural/stereo-speaker output (08/09), automation smoothing beyond basic rebuild + crossfade (10),
custom UI (11), presets (12).

## Acceptance criteria — automated

- [ ] pluginval **strictness 10** passes on 3 OSes (VST3) and macOS (AU), including its parameter
      fuzzing, state and automation tests. auval passes.
- [ ] **Parameter ID freeze test:** the list of parameter IDs and ranges equals
      `tests/state/parameter_ids_v1.json`. Changing it fails CI.
- [ ] **State round trip:** headless test processes 5 s of noise offline, saves state, creates a new
      instance, restores state, and processes again. The outputs are **bit-identical** (same platform).
      The saved state differs from the default in at least one parameter (e.g. `listener_y`) and one
      non-parameter field (`tailSeed` and one α), and the test asserts that the restored output differs
      from a default instance's output.
- [ ] **Offline determinism:** an offline render with a parameter change at 2.0 s is bit-identical
      across two bounces in **one** instance with a reset between them, and a third bounce in a fresh
      instance (same block partitioning). The test also asserts that the output after 2.0 s differs
      from a run without the change.
- [ ] **No lost update (FR-3D-10):** a unit test fires N parameter changes and asserts that the last
      submitted scene equals the final parameter values.
- [ ] **Latency:** an impulse through the plugin (emitter placed at the listener's minimum distance, all
      α = 1) produces its first peak at exactly `getLatencySamples()` samples (±0).
- [ ] **No allocation / lock** in `processBlock` in realtime mode, including while 50 parameter changes
      per second arrive: no allocation is tested (AllocationTracker through the processor); no lock holds
      by construction (the parameter listener only does an atomic store; reviewed), and the TSan
      criterion below covers the cross-thread part.
- [ ] Corrupt-state fuzz test (1 000 random byte blobs) never crashes and always ends in a valid scene.
- [ ] TSan passes on a test where one thread fires parameter changes, the builder runs, and the audio
      thread processes.
- [ ] Boundary check still passes (`module3d` and `sim` don't include each other).

## Listening / manual checklist (Maisara)

In **Logic (AU)** and **one VST3 host**, put a drum loop or vocal on a stereo track:
- [ ] Insert the plugin. You hear the default room (mono preview for now, so both speakers are the same).
- [ ] Move `listener_y` from near the emitters to the far wall: the sound gets more distant and roomier.
- [ ] Move `listener_x` off-centre: the sound becomes coloured (comb filtering, because the L and R
      paths have different lengths and the mono preview sums them in one output). This is expected and
      goes away in Phase 08; don't report it as a defect.
- [ ] Shrink `room_w/d/h` to minimum, then maximum: small booth vs large hall.
- [ ] Draw automation on `listener_y` and play it. The change follows the automation. Some stepping or
      zipper noise is acceptable here; Phase 10 removes it. Report anything harsher than that.
- [ ] Save, close and reopen the project: it sounds the same.
- [ ] With delay compensation on, the plugin's track stays in time with an unprocessed duplicate track
      (play both and solo-switch; the drum hits must line up). Use the default symmetric L/R positions
      for this check: under AX1 only the nearest emitter's direct sound is on the grid.
- [ ] Bounce/export offline twice: the files null in the DAW (invert one), or at least sound identical.

## Contractor review focus

Threading model (who owns the scene, what crosses threads and how), non-realtime path, state
versioning and migration, and parameter normalization choices (these get frozen).

## Risks

- Host quirks: Logic calls `setStateInformation` before `prepareToPlay`, and some hosts change sample
  rate without re-instantiating. Handle both, and test the second with pluginval's sample-rate test.
- Room-size changes make IR length vary, so memory gets allocated on the builder thread, never the audio thread.

## Definition of done

All automated criteria green; status row 07 `done`; checklist in the PR. The PR records the peak memory
(RSS) per instance at 96 kHz with the maximum room (recorded, not gated).
