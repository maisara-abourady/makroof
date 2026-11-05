# Phase 10 — Artifact-free movement under automation

Size: **M** · Depends on: 06, 07, 08, 09 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ10, AX1), PRD FR-SIM-6, NFR-3, Q4

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3).

## Assumptions in force

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
- **AX15**: equal-gain crossfade for position updates; **equal-power** for large jumps (e.g. the
  corner-to-corner step scenarios) and output-mode toggles, where the IRs are unrelated.
- **AX1**: no Doppler. Movement is a sequence of crossfaded static IRs. Fast moves sound slightly
  smeared rather than pitch-shifted. That's intended, and the PR must describe it.

## Scope

1. **Automation in `render_cli`:** implement `--automation <json>`: a list of `{paramId, points:
   [[timeSec, normalizedValue], ...]}` with linear interpolation. render_cli drives the same
   `module3d::ParameterMap` and builder logic as the plugin, in **both** modes:
   - `--offline` (default): synchronous rebuild per block whenever parameters changed (the plugin's
     non-realtime path).
   - `--realtime-sim`: the builder runs on a real background thread with the 20 ms cadence. The audio loop
     runs as fast as possible, but the *simulated* clock decides when the builder's results are picked up,
     so behaviour is reproducible for tests. Document the mechanism.
2. **Tail cache:** cache the Phase 04/08/09 tail keyed by (room dimensions, materials, mode, seed, sample
   rate). Position-only changes rebuild just the early part and re-run energy matching. Prove the result
   equals a full rebuild (test).
3. **Rebuild scheduling:** the builder always works on the newest scene (coalescing). If a build takes
   longer than 20 ms, the next build starts immediately with the latest scene. The audio thread keeps
   using the last IR and never blocks. Track and expose "IR staleness" (time between the parameter
   change and the IR going live) as a debug metric.
4. **Parameter smoothing:** the 20 ms output-trim smoothing stays. Positions aren't smoothed per sample
   (they only drive IR rebuilds). Room-size changes go through the same path.
5. **Negative control:** a build flag `MAKROOF_TEST_HARD_SWITCH` (test builds only) replaces the crossfade
   with an instantaneous IR switch. The click detector **must** flag that build. This proves the detector
   catches the problem this phase solves.
6. **Automation scenario suite** `tests/automation/*.json` (20 scenarios): slow and fast linear sweeps of
   the listener and each emitter across the room; step jumps (corner to corner) every 250 ms; sinusoidal
   oscillation at 0.1, 1, 2 and 5 Hz; room size sweeps from min to max; output-mode toggles mixed with
   movement; all parameters at once.
7. CI job `automation` (Linux in every PR; macOS/Windows too, since it's fast with short renders) runs all
   scenarios × 2 modes × {offline, realtime-sim} through `render_cli` with the sustained-tone input and
   runs `clicks.py`.

## Out of scope

Doppler / interpolated delay lines (would need a new AX entry and Expert input), dynamic reflection-order
reduction while moving (needs an AX entry if introduced).

## Acceptance criteria — automated

- [ ] All 20 scenarios × 2 modes × 2 timing modes: **0 click events** (Phase 02 detector, default threshold).
- [ ] Negative control (`MAKROOF_TEST_HARD_SWITCH`) is flagged in ≥ 18 of 20 scenarios. (Scenarios with
      no effective IR change may legitimately pass.)
- [ ] Offline render of every scenario is **bit-identical** across two runs.
- [ ] A static scene renders identically (within −120 dB) in offline and realtime-sim modes.
- [ ] Tail-cache result equals a full rebuild within −120 dB.
- [ ] Worst-case IR staleness in realtime-sim ≤ **100 ms** in all scenarios at order 20 (recorded in the
      CI log; failing it fails the job).
- [ ] No allocation in `processBlock` during the automation scenarios (AllocationTracker through the plugin processor).
- [ ] pluginval strictness 10 passes (its automation test exercises this path too).

## Listening / manual checklist (Maisara)

In Logic and one VST3 host, on a sustained pad *and* on drums, both output modes:
- [ ] Automate the L and R emitters from 1 m to 15 m away and back over 8 bars: smooth change in distance,
      no clicks, zipper noise or level pumping.
- [ ] Jump the listener between two corners every beat: the room snaps cleanly, with no clicks.
- [ ] Sweep the room size over 4 bars: smooth.
- [ ] Fast moves sound slightly "washy" but not pitch-wobbly. That's the intended no-Doppler design.
      Say if you'd prefer audible Doppler; that's a product decision.
- [ ] Bounce offline: the bounce sounds like the realtime playback.

## Contractor review focus

Scheduling and coalescing logic, cache-key completeness (a stale tail is a nasty bug), the realtime-sim
clock mechanism, and whether the negative control really exercises the same code path.

## Risks

- IR rebuild cost at high orders in large rooms could exceed the 20 ms cadence and cause visible
  staleness. Measure it. If it's too slow, propose (don't implement) a moving-order reduction as an AX entry.
- The click detector's blind spots for very low-frequency artifacts (thumps below 2 kHz). Add one scenario
  with a 40 Hz tone and a low-band detector variant if cheap.

## Definition of done

All automated criteria green; staleness numbers in the status notes; status row 10 `done`.
