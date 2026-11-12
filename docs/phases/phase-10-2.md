# Phase 10-2 — Automation driver, rebuild scheduling and staleness

Size: **M** (remainder, if needed: `10-2b`) · Depends on: 06, 07, 08, 09, 10-1 · Part of: [phase-10](phase-10.md) · Lead subject matter: Seat 5 (Deadline keeper), "real-time safety; lock-free hand-off; threading topology; host conformance (pluginval, … automation …); offline equals real-time; CI gates" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ10, AX20, AX22, AX33), PRD FR-SIM-6, NFR-3, Q4, the umbrella [`phase-10.md`](phase-10.md)

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3). (phase-10 goal, shared)

This sub-phase's share: `render_cli --automation` in `--offline` and `--realtime-sim` (simulated clock), coalescing
scheduler with the IR-staleness metric, the AX33 / idle-poll confirmation, the 20 scenarios and the `automation` CI
job on 3 OSes with the staleness gate (map-10 §1).

## Assumptions in force

All of the umbrella's ([phase-10](phase-10.md)); the one bearing most on this sub-phase:

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
  (phase-10 assumption AQ4, shared)

## Scope

1. **Automation in `render_cli`:** implement `--automation <json>`: a list of `{paramId, points:
   [[timeSec, normalizedValue], ...]}` with linear interpolation. render_cli drives the same
   `module3d::ParameterMap` and builder logic as the plugin, in **both** modes:
   - `--offline` (default): synchronous rebuild per block whenever parameters changed (the plugin's
     non-realtime path).
   - `--realtime-sim`: the builder runs on a real background thread with the 20 ms cadence. The audio loop
     runs as fast as possible, but the *simulated* clock decides when the builder's results are picked up,
     so behaviour is reproducible for tests. Document the mechanism. (phase-10 scope 1)
3. **Rebuild scheduling:** the builder always works on the newest scene (coalescing). If a build takes
   longer than 20 ms, the next build starts immediately with the latest scene. The audio thread keeps
   using the last IR and never blocks. Track and expose "IR staleness" (time between the parameter
   change and the IR going live) as a debug metric. Time spent waiting at the diffuse-solve gate counts in
   it (AX38 (iii)); the staleness (gate wait included) drives Phase 11's "settling" state. Whether "the IR going
   live" is the submit or the end of the AQ4 crossfade, and how the crossfade state (`CrossfadingConvolver::isFading()`,
   the audio thread's) is exposed to the UI, is defined here (AX38 (iii), G1-C1). The split update (AX38 (v): a
   Phase 10 AX that updates the specular and directional part without waiting for the diffuse solve) is
   designed together with [`phase-07c.md`](phase-07c.md) condition 4 (atomic swap with an AQ4 crossfade;
   the ISM update never held behind the diffuse solve), so it is not designed twice. (phase-10 scope 3)
   **From phase-07c-1's loop** (2026-11-12; decider file `docs/review/phase-07c-1/12-decider-decision-r3.md` §8;
   AX47, AX49): phase-07c-1's record (g) feeds the AX38 (v) split update; D5 restricted to edits within 5 %
   (Seat 9) and D6 are recorded alternatives for T60-changing edits (AX49 "Recorded for Phase 10"; AX49 ships
   Seat 3's D5 bridge on every T60 edit); Seat 1 rules whether automation-driven interim-to-final steps count
   under AX47.
4. **Parameter smoothing:** the 20 ms output-trim smoothing stays. Positions aren't smoothed per sample
   (they only drive IR rebuilds). Room-size changes go through the same path. Document that room-size
   automation at large rooms is stepwise (each step a full rebuild, AQ10; AX38 4c hand-off). (phase-10 scope 4)
6. **Automation scenario suite** `tests/automation/*.json` (20 scenarios): slow and fast linear sweeps of
   the listener and each emitter across the room; step jumps (corner to corner) every 250 ms; sinusoidal
   oscillation at 0.1, 1, 2 and 5 Hz; room size sweeps from min to max; output-mode toggles mixed with
   movement; all parameters at once. (phase-10 scope 6)
7. CI job `automation` (Linux in every PR; macOS/Windows too, since it's fast with short renders) runs all
   scenarios × 2 modes × {offline, realtime-sim} through `render_cli` with the sustained-tone input
   (phase-10 scope 7, clause 1; rest in 10-3)
8. **Isolated-update cap:** confirm or replace AX33 (Phase 07: minimum 20 ms spacing between build
   starts; an isolated request starts at once) and state the resulting isolated-update delay (at most
   rebuild + 2P, AX31). Phase 07's `IrBuilderThread` (`src/plugin/core/IrBuilderThread.h`, `kIdlePollS`)
   notices a parameter change by polling the dirty generation every 1 ms while idle: the audio-thread
   parameter listener only does a lock-free `fetch_add`, so it never makes a system call or takes a lock
   (Phase 07 follow-up, PR #23). Confirm this, or replace it with a wake-up that keeps the audio thread
   free of locks and system calls, and state the resulting worst-case extra delay for an isolated update.
   (phase-10 scope 8)

## Out of scope

The umbrella's out-of-scope list ([phase-10](phase-10.md)); phase-10 scope 2 (in [10-1](phase-10-1.md)); scope 5
and scope 7 clause 2 (in [10-3](phase-10-3.md)).

## Acceptance criteria — automated

- [ ] Offline render of every scenario is **bit-identical** across two runs. (phase-10 AC3)
- [ ] A static scene renders identically (within −120 dB) in offline and realtime-sim modes. (phase-10 AC4)
- [ ] Worst-case IR staleness in realtime-sim ≤ **100 ms** in all scenarios (recorded in the CI log;
      failing it fails the job). The hybrid IR's image list is time-bounded (AX20), so its size follows
      t_mix,e and the room, not `maxReflectionOrder`. If the ≤ 100 ms staleness gate fails only because
      of a recorded AQ10 miss, this phase may apply the phase-13 scope 1 optimisations (output unchanged
      beyond −100 dB). If it still fails, the phase is `blocked (AQ10 miss)` and Maisara chooses between
      (a) a smaller N_cap (an output change; the AX22 sensitivity report shows the accuracy cost) and
      (b) for fallback scenes only, a staleness bound taken from Vorländer Table 15.1 (700 ms,
      translation > 0.25 m). The gate is not loosened otherwise (decider report 8, accepted by Maisara, 2026-11-05).
      (phase-10 AC8)
- [ ] No allocation in `processBlock` during the automation scenarios (AllocationTracker through the plugin processor). (phase-10 AC9)
- [ ] pluginval strictness 10 passes (its automation test exercises this path too). (phase-10 AC10)

## Listening / manual checklist (Maisara)

In Logic and one VST3 host, on a sustained pad *and* on drums, both output modes: (phase-10 listening preamble, shared)
- [ ] Bounce offline: the bounce sounds like the realtime playback. (phase-10 L5)

## Contractor review focus

- Scheduling and coalescing logic (phase-10 CR1)
- the realtime-sim clock mechanism (phase-10 CR3)

## Risks

- IR rebuild cost in large rooms (the AX20 image list grows with t_mix,e, whatever `maxReflectionOrder`
  is) could exceed the 20 ms cadence and cause visible staleness. Measure it. If it's too slow, propose
  (don't implement) a reduction of the image list while moving as an AX entry (it would change AX20). (phase-10 R1)

## Notes from the split

- Order 10-1 → 10-2 → 10-3: "(A) follows the data dependencies (AQ10: AC8 rebuild hits the tail cache; AC7 needs
  the realtime-sim intervals)" (convening round, 10-c1 (A), `docs/review/phase-split/1-decider-convening.md`).
- Scope 7 is "split at S7's existing clause, verbatim" (convening round, 10-c2 (a)): the job and its renders are
  here, `clicks.py` in the job is in [10-3](phase-10-3.md). AC8's "failing it fails the job" needs the job in this
  sub-phase.
- 10-2 replaces the "not implemented until Phase 10" rejection of `--automation` (AX12; `src/cli/Cli.cpp:259`,
  `tests/unit/test_cli.cpp:220`, `tools/acoustics/tests/test_render_cli.py:57` change in the same sub-phase)
  (map-10 §1).
- Movement before 10-3 runs with the existing AX18 placeholder (equal-gain, Phase 06/07), so no sub-phase ships a
  hard switch (map-10 §1).
- S3's split update (AX38 (v)) is "designed together with phase-07c condition 4"; it stays in 10-2 unchanged.
  Phase 10 records no dependency on 07c and none is added; the coupling is carried as written (map-10 §2).

## Definition of done

- All automated criteria green (phase-10 DoD1, for the criteria this sub-phase owns: AC3, AC4, AC8, AC9, AC10).
- staleness numbers in the status notes (phase-10 DoD2)
- Status row 10-2 `done` (phase-10 DoD3; the umbrella row 10 is `done` when 10-1…10-3 are).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder
  into `phase-10-2b.md`.
