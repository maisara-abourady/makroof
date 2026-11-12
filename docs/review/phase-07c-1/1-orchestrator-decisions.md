# 1 — Orchestrator: decisions before implementation (phase 07c-1)

Phase 07c-1, 2026-11-12. Input to the decider's convening round (`/fix-plan` step 3, decision loop). Source of the
items: `docs/phases/phase-07c-1.md` "Decisions before implementation" (umbrella §4) and condition 9 ("the interim tail
while the synthesis is pending is decided in this phase's loop beside D-C2"). Decider file 51 §4 item 4: these are
decided through the board loop and recorded as AX rows before any code; not by the implementer alone.

## Decisions

- **D-C1, the provisional-to-final step.** Seat 1's ruling on the size of the level step from the interim level to the
  final solve (condition 5 last sentence; Seat 6 (d)). Needed: a number (dB, per band or broadband) or a rule, and
  what happens when the step would exceed it (e.g. the interim level is not used and the previous level kept, or the
  step is taken anyway as an AQ4 crossfade and recorded).
- **D-C2, the interim level and saved E_b.** Condition 5's preference order: (1) the E_b saved in the project state
  when the scene and W_max match; (2) otherwise the (A)-budget estimate or the previous level. Never silence, never the
  AX16 level where AX16 is known to be > 1 dB off (layouts 4/5, absorbing-floor cube). Open: which of (2)'s two
  alternatives and when; whether E_b is stored in the project state (then a state-version AX:
  `pluginStateVersion` bump, new fixtures, old fixtures load, Phase 07 rules).
- **D-C3, the solved result in saved state.** Seat 8's question whether the solved result can travel in the saved
  state; a feasibility call for Seat 5. The facts below bear on it.
- **D-C9, the interim tail while the unit-decay synthesis is pending** (condition 9; "beside D-C2"; "never silence
  where a tail existed in the saved state"; "the same interim / settling rules as the diffuse solve"). Open: what
  plays while `tail::BandNoiseGenerator` has not yet produced the unit decays for the restored scene: e.g. the
  restored scene's early part (ISM) alone with the tail added later as an AQ4 step; or the previous IrSet held
  (realtime reset keeps it, condition 10) until the full IR is ready; or a shorter / cheaper provisional tail.

## Researcher questions (decider file 51 §4 item 9)

- **R1** how long hosts tolerate a blocked `setStateInformation` (Seat 5).
- **R2** which hosts do not signal offline rendering reliably (Seat 5).
- **R3** host hang dialogs and their timeouts in Logic, Live, Cubase and Bitwig (Seat 7).
Note: `docs/review/phase-05h/12-researcher-T5T4-61.md` already holds related research (situations (a)–(e)); the
researcher should start there and add only what it lacks.

## Facts from the code (2026-11-12, branch `claude/clever-newton-ovvzcv` at b4dd092)

- The solve seam: `plugin::ScenePipeline::solveAndBuild` (`src/plugin/core/ScenePipeline.cpp` ≈ L109–129) is the one
  call from restore, prepare, `reset()` step 3 and the offline `process()`. It holds `DiffuseSolveGate::Scope` across
  the whole `sim::buildRoomIR` (ISM planning, the diffuse solve, the unit-decay synthesis and assembly) — the D-G1
  defect condition 12 fixes.
- In `sim::buildRoomIR` (`src/sim/Engine.cpp` ≈ L284–331), the order is: ISM plans per emitter → one diffuse solve
  (`diffuse::estimateDiffuse`) for all emitters → `switchTailLevel` sets per-band amplitudes `bandsAmplitude[b]` (the
  E_b-derived level) → per seed, per emitter: `generator->make(decay, seed, e)` (unit decays, the 3.14 s of 3.29 s at
  100 m / 96 kHz) → sample loop `taps[n] = w.ism·early[n] + w.tail·Σ_b bandsAmplitude[b]·unit.bands[b][n+offset]`.
  So the tail **level** (from the solve) and the tail **waveform** (unit decays) are separable: the final IR is
  linear in the per-band amplitudes once the unit decays exist. `BuildOptions::cachedUnitDecays` already lets a
  caller reuse unit decays.
- The unit decays depend on (fs, tailSeed, emitter channel, the decay T60s and tail length) but not on E_b; E_b
  depends on geometry, materials, positions and W_max (AX41) but not on tailSeed.
- Saved state today (Phase 07): `pluginStateVersion` with fixtures `tests/state/v<N>_*.bin`; holds the base scene JSON
  and parameter values; no IR or E_b.
- An E_b per emitter is 8 doubles (`kOctaveBandsHz`); a full IR at 100 m / 96 kHz is 12 s × 96 000 × 2 emitters × 2
  outputs floats ≈ 18 MB.
- The realtime engine adopts IrSets through a latest-wins mailbox with a 30 ms crossfade (AQ4, AX18); the restore's
  submit uses EqualPower (AX18), others EqualGain.
