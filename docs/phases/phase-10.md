# Phase 10 — Artifact-free movement under automation

Size: **M**, split into 10-1…10-3 · Depends on: 06, 07, 08, 09 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ10, AX1, AX18, AX20, AX22, AX33), PRD FR-SIM-6, NFR-3, Q4

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3).

## Assumptions in force

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
- **AX18**: equal-gain for position and room-size updates (placeholder until Phase 10, AX18);
  **equal-power** for large jumps (e.g. the corner-to-corner step scenarios) and output-mode toggles,
  where the IRs are unrelated. This phase sets the law.
- **AX22**: Phase 04's realised-k switch. t_mix,e is continuous in position, but the fallback to
  ISM-only up to the image-count cap is a single jump point in source position. Across it the IR segment
  between t_mix,e and t_cap,e is ISM in one IR and noise in the other, so AX18's equal-gain premise
  (correlated consecutive IRs) does not hold there, and the 30 ms position crossfade dips in that segment: 3 dB at mid-fade for any power ratio of the two
  uncorrelated segments; the largest dip relative to the power-linear interpolation of the two segments
  grows with their power ratio, ≈ 4.4 dB at 10:1, at g ≈ 0.24 of the fade (Vorländer Eq. 4.14). The total output dip is gated in this
  phase (acceptance criteria) (decider report 8, accepted by Maisara, 2026-11-05).
- **AX1**: no Doppler. Movement is a sequence of crossfaded static IRs. Fast moves sound slightly
  smeared rather than pitch-shifted. That's intended, and the PR must describe it.

## Sub-phases

| id | title | lead seat | size | depends on | ships | owns |
|---|---|---|---|---|---|---|
| [10-1](phase-10-1.md) | Position-only tail cache | Seat 2 (Engine architect) | S | 06, 07, 08, 09 | A keyed cache of the unmatched unit-energy per-band decay (per output for 08/09) used by every rebuild in the product path, with E_b (diffuse solve included), t_mix,e, the AX20 list, AX16 list and the ISM→tail crossfade recomputed each time | AC5 |
| [10-2](phase-10-2.md) | Automation driver, rebuild scheduling and staleness | Seat 5 (Deadline keeper) | M | 06, 07, 08, 09, 10-1 | `render_cli --automation` in `--offline` and `--realtime-sim` (simulated clock), coalescing scheduler with the IR-staleness metric, the AX33 / idle-poll confirmation, the 20 scenarios and the `automation` CI job on 3 OSes with the staleness gate | AC3, AC4, AC8, AC9, AC10 |
| [10-3](phase-10-3.md) | Crossfade law and artefact gates under movement | Seat 3 (Reverb renderer) | M | 06, 07, 08, 09, 10-2 (and 10-1 through it) | The AX18 law for position / room-size / large-jump switches set and gated (AX22 switch-point gate, position-fade gate), the `MAKROOF_TEST_HARD_SWITCH` negative control, and `clicks.py` in the `automation` job with 0 events | AC1, AC2, AC6, AC7 |

Order: 10-1 → 10-2 → 10-3. Status: the umbrella is `done` when every sub-phase is. A dependency on phase 10 means
all of its sub-phases unless a sub-phase is named.

## Out of scope

Doppler / interpolated delay lines (would need a new AX entry and Expert input), dynamic reduction of the
image list while moving (it would change AX20; needs an AX entry if introduced).

## Where the original items went

Labels: acceptance criteria AC1–AC10 in the original file order (AC1 0 click events; AC2 negative control; AC3
offline bit-identical; AC4 static scene offline vs realtime-sim; AC5 tail cache; AC6 AX22 switch point; AC7
position-fade gate; AC8 staleness; AC9 no allocation; AC10 pluginval); listening items L1–L5 in file order (the
preamble "In Logic and one VST3 host, …" is shared); contractor review focus CR1–CR4 in sentence order; risks R1–R2.

| original item | → |
|---|---|
| Goal; assumptions AQ4, AX18, AX1 | umbrella (shared; repeated in the sub-phases they bear on) |
| Assumption AX22 | umbrella and [10-3](phase-10-3.md) |
| Scope 1 (automation in `render_cli`, `--offline`, `--realtime-sim`) | [10-2](phase-10-2.md) |
| Scope 2 (tail cache) | [10-1](phase-10-1.md) |
| Scope 3 (rebuild scheduling, staleness metric, split update with phase-07c condition 4) | [10-2](phase-10-2.md) |
| Scope 4 (parameter smoothing) | [10-2](phase-10-2.md) |
| Scope 5 (negative control `MAKROOF_TEST_HARD_SWITCH`) | [10-3](phase-10-3.md) |
| Scope 6 (automation scenario suite) | [10-2](phase-10-2.md) |
| Scope 7, clause 1 (CI job `automation` … with the sustained-tone input) | [10-2](phase-10-2.md) |
| Scope 7, clause 2 ("and runs `clicks.py`") | [10-3](phase-10-3.md) |
| Scope 8 (isolated-update cap, AX33, `kIdlePollS`) | [10-2](phase-10-2.md) |
| Out of scope | umbrella (shared) |
| AC1, AC2, AC6, AC7 | [10-3](phase-10-3.md) |
| AC3, AC4, AC8, AC9, AC10 | [10-2](phase-10-2.md) |
| AC5 | [10-1](phase-10-1.md) |
| Listening preamble | umbrella (shared by 10-2 and 10-3) |
| L1–L4 | [10-3](phase-10-3.md) |
| L5 | [10-2](phase-10-2.md) |
| CR1 (scheduling and coalescing), CR3 (realtime-sim clock) | [10-2](phase-10-2.md) |
| CR2 (cache-key completeness) | [10-1](phase-10-1.md) |
| CR4 (negative control code path) | [10-3](phase-10-3.md) |
| R1 (rebuild cost in large rooms) | [10-2](phase-10-2.md) |
| R2 (detector blind spot below 2 kHz) | [10-3](phase-10-3.md) |
| Definition of done: "All automated criteria green" | umbrella (shared: each sub-phase for the criteria it owns) |
| Definition of done: "staleness numbers in the status notes" | [10-2](phase-10-2.md) |
| Definition of done: "status row 10 `done`" | umbrella (set when 10-1…10-3 are `done`; each sub-phase sets its own row) |

## Listening / manual checklist (Maisara)

In Logic and one VST3 host, on a sustained pad *and* on drums, both output modes: (items L1–L4 in
[10-3](phase-10-3.md), L5 in [10-2](phase-10-2.md))

## Notes from the split

- 10-c1 NOT A DECISION: (A). (A) follows the data dependencies (AQ10: AC8 rebuild hits the tail cache; AC7 needs
  the realtime-sim intervals). 10-c2 NOT A DECISION: (a), split at S7's existing clause, verbatim. 10-c3 NOT A
  DECISION: (a), 10-1 standalone (owns AC5, one subject, carries risk CR2). (convening round,
  `docs/review/phase-split/1-decider-convening.md`)
- Map and coverage: `docs/review/phase-split/map-10.md`.

## Definition of done

All automated criteria green (shared; each sub-phase for the criteria it owns); status row 10 `done` (when
10-1…10-3 are `done`).
