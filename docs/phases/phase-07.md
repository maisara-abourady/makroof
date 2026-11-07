# Phase 07 — Plugin integration: parameters, state, scene → IR pipeline

Size: **M** · Depends on: 01, 04, 06 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ5, AX2, AX5, AX7), PRD FR-3D-5, FR-3D-8, FR-3D-10, FR-LIC-1, NFR-2, NFR-6

## Goal

The plugin renders the room in a DAW. Listener, emitter positions and room size are **host-automatable
parameters**. The scene is saved in the DAW project and restored with an identical render. This is the
first phase where the 3D Module (`src/module3d`) and the Simulator (`src/sim`) meet, and they do so
only through `contract::SceneDescription`.

## Assumptions in force

- **AQ4**: background IR rebuild, at most one per 20 ms; **synchronous rebuild in non-realtime
  (offline bounce) mode**. **AQ5**: everything runs locally.
- **AX2**: 0 dB at 1 m plus a user output trim. **AX5**: determinism. **AX7**: two emitters, L and R.
- Output is still the **omni** IR (mono room preview, same signal on both outputs). Binaural is Phase 08.

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
3. `src/plugin/`:
   - `PluginProcessor` creates `juce::AudioProcessorValueTreeState` from `ParameterMap`. A parameter
     listener marks the scene dirty.
   - `IrBuilderThread` (a JUCE `Thread`, or a `std::thread` with a condition variable) coalesces dirty
     notifications, builds `contract::SceneDescription` → `sim::buildRoomIR` → `IrSet`, and submits it
     to `RealtimeEngine` (Phase 06 mailbox). It runs at most every 20 ms. The audio thread never waits.
   - The plugin talks to the convolution engine **only through `sim::RealtimeEngine`**, never the bare
     `conv::CrossfadingConvolver` (whose `process()` leaves the output untouched when it isn't prepared)
     (PR #14 follow-up).
   - The IR builder thread is **stopped or joined (no `submitRoomIR` in flight) before
     `RealtimeEngine::prepare()` is called again or the engine is destroyed**: `prepare` drops the IRs
     and reallocates, so a concurrent submit would race it (PR #14 follow-up).
   - Non-finite host input samples are already zeroed inside the engine (Phase 06).
   - **Non-realtime mode** (`isNonRealtime()`): when a parameter changes during an offline bounce,
     `processBlock` builds the IR synchronously before processing that block, so bounces are deterministic.
   - `prepareToPlay` builds the initial IR synchronously and calls `setLatencySamples(engine.latencySamples())`.
     Latency stays constant for the life of the instance at a given sample rate.
   - Output trim is applied with a smoothed gain (20 ms).
   - Bus layout: stereo in → stereo out only.
4. **State (FR-LIC-1, NFR-6):** `getStateInformation` writes XML (or JSON in a `MemoryBlock`) with
   `pluginStateVersion` (int, starts at 1), the **full scene contract JSON**, and the APVTS parameter state.
   `setStateInformation` reads any known `pluginStateVersion`, migrates it, validates the scene and
   rebuilds the IR synchronously. Invalid or corrupt state falls back to the default scene and records
   a visible warning flag (shown by the UI in Phase 11), and never crashes.
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
- [ ] **Offline determinism:** an offline render with a parameter change at 2.0 s is bit-identical
      across two runs.
- [ ] **Latency:** an impulse through the plugin (emitter placed at the listener's minimum distance, all
      α = 1) produces its first peak at exactly `getLatencySamples()` samples (±0).
- [ ] **No allocation / lock** in `processBlock` in realtime mode (AllocationTracker test through the
      processor), including while 50 parameter changes per second arrive.
- [ ] Corrupt-state fuzz test (1 000 random byte blobs) never crashes and always ends in a valid scene.
- [ ] TSan passes on a test where one thread fires parameter changes, the builder runs, and the audio
      thread processes.
- [ ] Boundary check still passes (`module3d` and `sim` don't include each other).

## Listening / manual checklist (Maisara)

In **Logic (AU)** and **one VST3 host**, put a drum loop or vocal on a stereo track:
- [ ] Insert the plugin. You hear the default room (mono preview for now, so both speakers are the same).
- [ ] Move `listener_y` from near the emitters to the far wall: the sound gets more distant and roomier.
- [ ] Shrink `room_w/d/h` to minimum, then maximum: small booth vs large hall.
- [ ] Draw automation on `listener_y` and play it. The change follows the automation. Some stepping or
      zipper noise is acceptable here; Phase 10 removes it. Report anything harsher than that.
- [ ] Save, close and reopen the project: it sounds the same.
- [ ] With delay compensation on, the plugin's track stays in time with an unprocessed duplicate track
      (play both and solo-switch; the drum hits must line up).
- [ ] Bounce/export offline twice: the files null in the DAW (invert one), or at least sound identical.

## Contractor review focus

Threading model (who owns the scene, what crosses threads and how), non-realtime path, state
versioning and migration, and parameter normalization choices (these get frozen).

## Risks

- Host quirks: Logic calls `setStateInformation` before `prepareToPlay`, and some hosts change sample
  rate without re-instantiating. Handle both, and test the second with pluginval's sample-rate test.
- Room-size changes make IR length vary, so memory gets allocated on the builder thread, never the audio thread.

## Definition of done

All automated criteria green; status row 07 `done`; checklist in the PR.
