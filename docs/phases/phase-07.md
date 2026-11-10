# Phase 07 — Plugin integration: parameters, state, scene → IR pipeline

Size: **M** · Depends on: 01, 04, 06 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ5, AX2, AX5, AX6, AX7, AX18, AX33, AX34), PRD FR-3D-5, FR-3D-8, FR-3D-10, FR-LIC-1, NFR-2, NFR-6

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

- **AQ4**: background IR rebuild, at most one per 20 ms (AX33: a minimum spacing between build
  starts); **synchronous rebuild in non-realtime (offline bounce) mode**. **AQ5**: everything runs locally.
- **AX2**: 0 dB at 1 m plus a user output trim. AX2 holds **per emitter path**; the mono preview sums
  both paths (L and R emitters) in each output. The plugin's band-mean gain can exceed 0 dB: up to
  +28.5 dB direct (gainDb +12, both emitters at 0.3 m) and ≈ +44 dB in the 63 Hz band in a 1.5 m
  α = 0.01 booth (Kuttruff Eq. 5.45, a diffuse-field estimate); `output_trim_db` −48…+24 covers
  programme level, and +24 covers the ≈ 19–22 dB mid-band drop at maximum room (4–8 kHz fall further
  by air absorption, AX4, not compensated). Single-mode peaks above the band mean are not bounded by
  any source below the Schroeder frequency; float does not clip before the master (Izhaki Ch. 11).
  **AX5**: determinism. **AX7**: two emitters, L and R.
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
     Resizing the room keeps relative positions. Consequence (documented in the README): resizing
     scales distances and heights with the room (approximately: positions are normalized inside the
     0.1 m margins, so a uniform resize scales them only up to that offset). The default scene
     stretched to 100 × 100 × 100 m puts the listener 52.9 m from L at 42.1 m ear height: direct sound
     −18.8 dB re the default scene (−34.5 dB re 1 m, AX2). DRR is unchanged only for uniform scaling
     without air absorption (Kuttruff Eqs. 5.44/5.45); per-axis resizing or air changes it. With
     absolute positions the in-room share of a 0.1–99.9 m slider would be 1.3 % in a 1.5 m room and
     3.8 % for the default height. A UI resize that keeps absolute positions is a Phase 11 gesture, not
     a mapping change. Document this in `docs/contract/README.md` as a 3D Module
     behaviour, not a contract rule.
   - Frozen parameter IDs (strings, never renamed): `listener_x`, `listener_y`, `listener_z`, `emL_x`,
     `emL_y`, `emL_z`, `emR_x`, `emR_y`, `emR_z`, `room_w`, `room_d`, `room_h` (in metres, range
     1.5–100, mapping below), `output_trim_db` (−48…+24 dB, linear in dB, default 0; AX2 note under
     "Assumptions in force"), `output_mode` (choice: binaural, stereoSpeakers;
     wired in 08/09), `dry_wet` is **not** included (the PRD wants the space, not a reverb send; note it
     as a possible follow-up).
   - room_w/d/h: L = 1.5·(100/1.5)^x with explicit endpoints (x ≤ 0 → 1.5, x ≥ 1 → 100), interior
     clamped to [1.5, 100]; the inverse likewise; formula recorded in parameter_ids_v1.json. One per
     cent of travel = ×1.0429 in L, the smallest possible largest relative step for any map onto
     [1.5, 100]; per axis it changes T by 0 … +4.3 % under Sabine (Kuttruff Eq. 5.26 with 4mV), at
     most ≈ one T jnd (4 %, §7.6); Eyring (Eq. 5.24, AQ2) can differ slightly, ≈ −1.1 % … +4.9 % in
     extreme absorption layouts. Test (ctest, all three OSes): x = 0 and x = 1 give exactly 1.5 and
     100.0, the inverse of 1.5 and 100 gives exactly 0 and 1, and the map is strictly monotone on 10⁴
     points.
   - Listener–emitter distances below 0.3 m: each emitter e is replaced by the point p of the margin
     box B with |p − l| ≥ 0.3 m that is nearest to e; the listener never moves; the two emitters are
     treated independently. If |e − l| ≥ 0.3 m, p = e. Otherwise p = l + 0.3·u, where u maximises u·d
     over unit vectors with l + 0.3·u ∈ B, d = (e − l)/|e − l|, or d = +y (AQ1 forward) if e = l
     exactly; exact ties are broken by the largest u·ŷ, then u·x̂, then u·ẑ. When l + 0.3·d lies in B
     this is the push along the listener→emitter direction. p moves the least possible distance; it
     jumps only where two nearest points tie (up to 0.6 m, the sphere diameter; 0.52 m in example (c);
     e.g. across the line through l normal to a wall). Tests: (a) 10⁵ seeded cases (1.5 m rooms, l in
     corners, e = l): toContract() validates; (b) independent reference: |p − e| ≤ bruteMin + 1e−9 m,
     bruteMin over 10⁵ Fibonacci points of the 0.3 m sphere inside B plus 10⁴ points on each circle
     where a face plane of B cuts the sphere (with (a) this bounds p between the true minimum and the
     sampled one); (c) 1.5 m cube, l = (0.25, 0.75, 0.75), e = (0.1, 0.75, 0.75) →
     p = (0.1, 0.75 + 0.15√3, 0.75) within 1e−12 m. Reversal: Phase 10 traversal scenarios or Phase 08
     listening find the tie jumps objectionable → Phase 10 proposes an AX. The phase session mirrors
     this rule in `docs/contract/README.md` (as a 3D Module behaviour). The engine never sees an
     invalid scene.
   - The scene is a **pure function** of (current parameter values, non-parameter scene fields). The
     push-away is recomputed on every change; it is never stored and never written back to a host
     parameter.
3. `src/plugin/`:
   - `PluginProcessor` creates `juce::AudioProcessorValueTreeState` from `ParameterMap`. A parameter
     listener marks the scene dirty by incrementing an atomic dirty generation counter (an atomic
     increment (lock-free fetch_add) only: no allocation, no lock).
   - `IrBuilderThread` (a JUCE `Thread`, or a `std::thread` with a condition variable) coalesces dirty
     notifications, builds `contract::SceneDescription` → `sim::buildRoomIR` → `IrSet`, and submits it
     to `RealtimeEngine` (Phase 06 mailbox). It rebuilds while the generation counter differs from the
     last handled generation (recorded by its own last successful submit or bit-identical skip, by
     reset step 3, or by the restore's decision; see the switch rule below), so the final state is
     always built (no lost wake-up; FR-3D-10) and a scene already handled is not rebuilt.
     It applies AX33. Test (injected clock): an isolated request starts at 0 ms; requests 5 ms apart
     start ≥ 20 ms apart; the final state is built. The audio thread never waits.
   - The plugin talks to the convolution engine **only through `sim::RealtimeEngine`**, never the bare
     `conv::CrossfadingConvolver` (whose `process()` leaves the output untouched when it isn't prepared)
     (PR #14 follow-up).
   - The IR builder thread is **stopped or joined (no `submitRoomIR` in flight) before
     `RealtimeEngine::prepare()` is called again or the engine is destroyed**: `prepare` drops the IRs
     and reallocates, so a concurrent submit would race it (PR #14 follow-up).
   - Non-finite host input samples and finite samples with |x| > 2²⁰ are already zeroed inside the
     engine (Phase 06, AX32).
   - **Reset sequence.** `AudioProcessor::reset()` and the entry into non-realtime mode run the same
     sequence:
     1. Quiesce the builder: it stops accepting work, and any in-flight build is joined and drained;
        its result is discarded, not submitted.
     2. `RealtimeEngine::reset()` (new): a no-op if the engine is unprepared; otherwise it returns the
        engine to the state right after `prepare()` at the same sample rate and block size: no current,
        next or retiring IR and an empty mailbox (the dropped IRs are freed on the calling thread;
        `reset()` is not concurrent with `process()`); input history, pending output and sample counter
        cleared; buffers reused, not reallocated. `CrossfadingConvolver::reset()` keeps the current IR
        today, so this phase adds the drop (code change in this phase).
     3. Submit the current scene's IR (reuse the last built `IrSet` through `submitIrSet` when its
        parameter generation is current, otherwise build it) and, only if the submit returned true,
        record that generation as handled, so neither `processBlock`'s dirty check nor the builder
        submits the same scene again. Every `RealtimeEngine::prepare()` (it drops the IRs) clears the
        record.
     4. Snap the output-trim smoother to its target.
     5. In realtime mode, restart the builder; in non-realtime mode, keep it quiesced.

     The IR is installed at once (`CrossfadingConvolver::computeBlock` step 1: no current, next or
     retiring IR and `blockStart_ == 0`) when it is in the mailbox before the first P samples are
     processed; otherwise it fades in from silence. So playback after a host reset is not silent and
     every bounce starts identically. A reset that kept the current IR would break offline
     determinism: the next bounce's first IR would fade in from s0 = 2P (`computeBlock` step 4) instead of being
     installed at once, so it could not equal a fresh instance.

     Threading: the reset sequence, resubmit included, runs on the thread the host calls
     `AudioProcessor::reset()` on (or the thread that enters non-realtime mode), which **may be the VST3
     processing thread** (AX38 (i), D-H3 (e), 2026-11-10: VST3 permits `setProcessing` there and the pinned
     JUCE wrapper maps `setProcessing(false)` to `reset()`; AU leaves the thread unspecified). It is not
     concurrent with `processBlock` (one processing thread, F4, F21), but it is not a thread that tolerates a wait or a
     build: phase-07c condition 10 removes both from `reset()`. Assumed from the JUCE/host contract:
     `setStateInformation`, `prepareToPlay` and `reset()` are not called concurrently with each other. These
     assumptions are **not checkable** by an automated test here; pluginval exercises `reset()`, not on an
     audio thread (researcher dossier `docs/review/phase-05h/12-researcher-T5T4-61.md`). The resubmit may allocate
     (`buildRoomIR`/`makeIrSet`) or free; it is a transport event outside `processBlock`, so the
     no-allocation rule for `processBlock` is unaffected.
   - **Non-realtime mode** (`isNonRealtime()`): entering it runs the reset sequence, which leaves the
     builder quiesced. When a parameter changes during an offline bounce, `processBlock` builds the IR
     and calls `submitRoomIR` itself before processing that block (or skips it as bit-identical; either
     way it records the generation as handled, switch rule below); it is the only submitter during a bounce: `setStateInformation`
     and `prepareToPlay` do not submit mid-bounce (if a host calls them, their submit is deferred to the
     next `processBlock`), so bounces are deterministic. "Synchronous" means the IR is submitted before
     the block; under AX31 it enters the output up to 2P later for an isolated update (no fade
     running); a change during a running fade is taken after that fade ends (AX31); identical across
     runs for the same block partitioning. Leaving non-realtime mode restarts the builder thread. Widen
     the `submitRoomIR`/`submitIrSet` thread comments in `RealtimeEngine.h` from "any non-audio thread"
     to "any non-audio thread, or the processing thread when nothing else submits (offline bounce,
     reset sequence with the builder quiesced)" (code change in this phase).
   - `prepareToPlay` builds the initial IR synchronously and calls `setLatencySamples(engine.latencySamples())`.
     Latency stays constant for the life of the instance at a given sample rate.
   - **Unsupported host sample rate (AX34):** if `prepareToPlay` gets a rate outside AX6, the plugin
     catches the engine's refusal and enters AX34's fallback (output = input delayed by the reported
     latency, 544 samples at every rate, no output trim, no AX32 guard; warning flag set; no IR built
     anywhere; the builder stopped before prepare and not restarted). A later `prepareToPlay` at a
     supported rate runs the normal path. Test (Catch2, three OSes): at 11025, 22050, 176400,
     192000 Hz with output_trim_db = −12 and one NaN input sample: no throw; every output sample
     bit-equals the input delayed by getLatencySamples() (= 544), NaN at the delayed index (isnan);
     flag set; prepareToPlay(48000) then renders the room (output differs from the delayed input) and
     clears the flag; also 48 → 96 → 44.1 → 192 → 48 kHz without re-instantiation.
   - **Switch rule and crossfade law** (Phase 07 decision loop 2026-11-08, decider D7 (rounds 1–3),
     interrogator SURVIVES WITH CORRECTIONS, advocate round 2 REDIRECT (narrow), cleared on interrogator
     confirmation; final advocate screen of the applied text PASS; accepted by Maisara 2026-11-08 (no vetoes)).

     *Skip rule.* A submit is skipped when the built RoomIR is bit-identical (length and taps) to the IR
     of the last successful submit since the last `prepare()` or reset. Step 3 of the reset sequence
     always submits. If the derived scene equals the last submitted one in every field, the build may be
     skipped as well (AX5: the same scene gives the same IR). A decision skipped as bit-identical records
     its generation as handled, the same record a successful submit writes, in the builder and in the
     offline `processBlock` dirty check; a failed submit records nothing, and every
     `RealtimeEngine::prepare()` clears the record (R3-2).

     *Restore flag.* `setStateInformation` advances the dirty generation and records it as the restore
     generation g_R, which sets the flag. The flag applies only to the restore's own submit decision: the
     first build decision whose scene generation is ≥ g_R. That decision either submits or skips as
     bit-identical, and in both cases it clears the flag. A build that merges the restore with parameter
     changes made after it is still that decision. The synchronous builds in `setStateInformation`
     (realtime, engine prepared), `prepareToPlay` and reset step 3 are build decisions at a generation
     ≥ g_R, and each consumes the flag; a build discarded in reset step 1 is not a decision. The
     generation a decision records (as handled, and for the ≥ g_R comparison) is the one read before
     its scene snapshot, so a change after the snapshot is a later generation.
     - Realtime (engine prepared): `setStateInformation` runs like the reset sequence's steps 1, 3 and 5
       on its own thread: it quiesces the builder (discarding any in-flight build), makes the restore's
       decision itself (build; submit with EqualPower, or skip if bit-identical; record the generation
       as handled; consume the flag), and restarts the builder. So it is never concurrent with a
       builder submit. Before `prepareToPlay` (or in the AX34 fallback), the decision is `prepareToPlay`'s
       synchronous build.
     - Offline: the deferred submit in `processBlock` makes it at the next block boundary and clears the
       flag there. Host call order fixes which block that is, so bounces stay deterministic (AX5).
     - The rule is generic: no scene fields or values are inspected beyond the IR comparison (NFR-8).

     *Law.* The submit made by the restore's decision uses EqualPower. Every other submit uses EqualGain
     (the AX18 placeholder for position and room-size updates; Phase 10 sets the law).

     *Tests* (realtime and offline each; the law is checked by a −100 dB null of the output against the
     analytic crossfade of the two IRs, the Phase 06 technique). Null-test conditions: `output_trim_db`
     at 0 dB with the smoother snapped (gain exactly 1.0f), or the reference applies the same gain; the
     reference fade starts at s0 = (⌊r/P⌋+2)·P, read from `fadeStartSample()` (AX31); the reference IRs
     are built from the same two scenes at the same rate (AX5); the reference allows for the mono
     preview (same signal on both outputs).
     (a) Restoring the current state during playback starts no fade: the engine's fade counter is
     unchanged, the output is unchanged, and the flag is cleared.
     (b) After (a), the next listener_y change crosses to the new IR as an EqualGain fade.
     (c) Restoring a different state crosses as an EqualPower fade, and the next listener_y change after
     it is EqualGain.
     (d) Offline: a restore and a parameter change in the same block make one EqualPower fade, and the
     next change is EqualGain. Realtime: a parameter change injected after the restore's scene snapshot
     (through a test hook) is a later generation, built by the builder after the restore, with
     EqualGain.
     (e) Offline (c) is bit-identical across two bounces, and a fresh instance that restores before
     `prepareToPlay` bounces bit-identical to the reset-instance bounce.
     (f) `setStateInformation` → `prepareToPlay` or reset → a listener_y change crosses as EqualGain,
     realtime and offline.
   - Output trim is applied with a smoothed gain (20 ms).
   - Bus layout: stereo in → stereo out only.
4. **State (FR-LIC-1, NFR-6):** `getStateInformation` writes XML (or JSON in a `MemoryBlock`) with
   `pluginStateVersion` (int, starts at 1), the **full scene contract JSON**, and the APVTS parameter state.
   `setStateInformation` reads any known `pluginStateVersion`, migrates it, validates the scene and
   rebuilds the IR synchronously (the restore's decision, scope 3 switch rule). If it arrives before `prepareToPlay`, it validates and stores the
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
      The saved state differs from the default in at least one parameter (e.g. `listener_y`) and at least
      one non-parameter field (e.g. `tailSeed` and one α), and the test asserts that the restored output differs
      from a default instance's output.
- [ ] **Offline determinism:** an offline render with a parameter change at 2.0 s is bit-identical
      across two bounces in **one** instance with a reset between them, and a third bounce in a fresh
      instance (same block partitioning). The test also asserts that the output after 2.0 s differs
      from a run without the change.
- [ ] **No lost update (FR-3D-10):** a unit test fires N parameter changes and asserts that, after
      them, the last handled generation equals the final one, and the engine's current IR is
      bit-identical to the IR built from the final parameter values.
- [ ] **Latency:** an impulse through the plugin (emitter placed at the listener's minimum distance, all
      α = 1) produces its first peak at exactly `getLatencySamples()` samples (±0).
- [ ] **No allocation / lock** in `processBlock` in realtime mode, including while 50 parameter changes
      per second arrive: no allocation is tested (AllocationTracker through the processor); no lock holds
      by construction (the parameter listener only does an atomic increment (lock-free fetch_add); reviewed), and the TSan
      criterion below covers the cross-thread part.
- [ ] Corrupt-state fuzz test (1 000 random byte blobs) never crashes and always ends in a valid scene.
- [ ] TSan passes on a test where one thread fires parameter changes, the builder runs, and the audio
      thread processes.
- [ ] Boundary check still passes (`module3d` and `sim` don't include each other).
- [ ] The tests named in scope 2 and 3 pass on 3 OSes: room-size map (D9), push-away (a)–(c) (D1),
      AX33 injected-clock test (D6), AX34 unsupported-rate test (D8), switch-rule tests (a)–(f) (D7).

## Listening / manual checklist (Maisara)

In **Logic (AU)** and **one VST3 host**, put a drum loop or vocal on a stereo track:
- [ ] Insert the plugin. You hear the default room (mono preview for now, so both speakers are the same).
- [ ] Move `listener_y` from near the emitters to the far wall: the sound gets more distant and roomier.
- [ ] Move `listener_x` off-centre: the sound becomes coloured (comb filtering, because the L and R
      paths have different lengths and the mono preview sums them in one output). This is expected with
      the mono preview for coherent L/R material; in Phase 08's binaural render it is less audible or
      inaudible (binaural timbre compensation, Blauert Ch. 4). Don't report it as a defect.
- [ ] Shrink `room_w/d/h` to minimum, then maximum: small booth vs very large hall. At maximum size the
      IR is cut at 12 s (AX6): every band with T60 > 8 s is cut; with the default materials the 63 Hz
      band is only ≈ 12 dB below its start when it stops. Expected in 07; describe what you hear.
      Positions scale with the room, so at maximum size everything is ≈ 19–22 dB quieter; restore it
      with `output_trim_db`.
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
  rate without re-instantiating. Handle both. pluginval's default rates are 44.1/48/96 kHz only
  (research dossier F1); unsupported rates are covered by the AX34 test and auval (M1).
- Room-size changes make IR length vary, so memory gets allocated on the builder thread, never the audio thread.
- In the 1.5 m minimum room the field is modal below ≈ 520–1040 Hz (Schroeder frequency, Kuttruff §3.6
  Eq. 3.44, default materials); the diffuse tail model does not describe it there. A known model
  limit; raising the minimum would not remove it (f_s ≤ 125 Hz needs ≳ 10.5 m).

## Definition of done

All automated criteria green; status row 07 `done`; checklist in the PR. The PR records the peak memory
(RSS) per instance at 96 kHz with the maximum room (recorded, not gated). It also records (not gated):
- the full-rebuild time at the default and the maximum room, entered in BUILD_PLAN §0 with the status
  update (D6);
- the extreme scene (1.5 m cube, α = 0.01, gainDb +12 on both emitters, L and R at the same point,
  0.3 m from the listener, identical L = R input): the maximum octave-band gain of the summed omni IR
  (AX14 bands); if it exceeds 48 dB, widen before release (D4).
