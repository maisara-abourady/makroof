# Split map — Phase 10 (Artifact-free movement under automation)

Source: `docs/phases/phase-10.md` (Size M; depends on 06, 07, 08, 09). Drafted per
`docs/review/phase-split/0-drafting-brief.md`. Pure reallocation: no scope item, criterion, threshold, AX/AQ value
or listening item is added, dropped or reworded, except the one clause split of scope 7 named below (CHOICE 10-c2).

Labels used for the original file: **S1–S8** scope items (S1a = `--offline`, S1b = `--realtime-sim`);
**AC1–AC10** automated criteria in file order (AC1 0 click events; AC2 negative control ≥ 18/20; AC3 offline
bit-identical; AC4 static scene offline vs realtime-sim; AC5 tail cache = full rebuild; AC6 AX22 switch point;
AC7 position-fade gate (AX18 amendment); AC8 staleness ≤ 100 ms; AC9 no allocation in `processBlock`;
AC10 pluginval strictness 10); **L0–L5** listening checklist (L0 = the preamble "In Logic and one VST3 host, on a
sustained pad *and* on drums, both output modes"); **CR1–CR4** contractor review focus (scheduling and coalescing;
cache-key completeness; realtime-sim clock; negative-control code path); **R1–R2** risks; **A-AQ4, A-AX18, A-AX22,
A-AX1** assumptions in force; **G** goal; **OOS** out of scope; **DoD1–DoD3** definition of done (all automated
criteria green; staleness numbers in status notes; status row 10 `done`); **H** header (size, depends on, read first).
Phase 10 has **no "Raise with Maisara" section** and no "settled / decisions before implementation" section.

## 1. Sub-phase table

| id | title | lead subject matter (seat, convening-table row words) | size | depends on | ships | automated criteria owned |
|---|---|---|---|---|---|---|
| 10-1 | Position-only tail cache | **Seat 2 Engine architect** — "late-tail statistics; the representation handed to the renderer; simulator compute and recompute time" | S | 06, 07, 08, 09 | A keyed cache of the unmatched unit-energy per-band decay (per output for 08/09) used by every rebuild in the product path, with E_b (diffuse solve included), t_mix,e, the AX20 list, AX16 list and the ISM→tail crossfade recomputed each time | AC5 |
| 10-2 | Automation driver, rebuild scheduling and staleness | **Seat 5 Deadline keeper** — "real-time safety; lock-free hand-off; threading topology; host conformance (pluginval, … automation …); offline equals real-time; CI gates" | M | 06, 07, 08, 09, 10-1 | `render_cli --automation` in `--offline` and `--realtime-sim` (simulated clock), coalescing scheduler with the IR-staleness metric, the AX33 / idle-poll confirmation, the 20 scenarios and the `automation` CI job on 3 OSes with the staleness gate | AC3, AC4, AC8, AC9, AC10 |
| 10-3 | Crossfade law and artefact gates under movement | **Seat 3 Reverb renderer** — "time variance under motion and automation (crossfades, zipper, clicks, metallic tails); coloration" | M | 06, 07, 08, 09, 10-2 (and 10-1 through it) | The AX18 law for position / room-size / large-jump switches set and gated (AX22 switch-point gate, position-fade gate), the `MAKROOF_TEST_HARD_SWITCH` negative control, and `clicks.py` in the `automation` job with 0 events | AC1, AC2, AC6, AC7 |

Why three and not one or five:
- The phase spans three subject matters that each carry their own risk named by the file: cache-key completeness
  (CR2, "a stale tail is a nasty bug"), the scheduler / realtime-sim clock (CR1, CR3, R1, the AQ10-miss `blocked`
  branch of AC8), and the crossfade law (A-AX18 "This phase sets the law", AC6/AC7 and their new-AX branches).
- 10-1 is S. The omni proxy already exists (`sim::BuildOptions::cachedUnitDecays`, `src/sim/Engine.h:94`, used by the
  AQ10 benchmark and `tests/unit/test_hybrid_ir.cpp:581`), so what is left is the key, the store, the per-output
  decays for 08/09, the wiring into the plugin and render_cli rebuild path, and AC5. It is kept separate because the
  subject is distinct (Seat 2, not the thread or the fade) and risky (CR2), it owns its own criterion, and 10-2's
  staleness gate (AC8) is measured on position-only rebuilds that need it. Merging it into 10-2 is CHOICE 10-c3.
- 10-2 and 10-3 are not split further: AC3, AC4, AC8, AC9 all need the scenarios (S6) and both timing modes (S1);
  AC1, AC2, AC6, AC7 all exercise the same crossfade path; a further cut would leave a part with no criterion (G2).

Each sub-phase leaves `main` green: 10-1 adds a cache that a test proves equal to a full rebuild; 10-2 replaces the
"not implemented until Phase 10" rejection of `--automation` (AX12; `src/cli/Cli.cpp:259`, `tests/unit/test_cli.cpp:220`,
`tools/acoustics/tests/test_render_cli.py:57` change in the same sub-phase) and adds the job with its staleness gate;
10-3 adds the click gate and the law. Movement before 10-3 runs with the existing AX18 placeholder (equal-gain,
Phase 06/07), so no sub-phase ships a hard switch.

## 2. Order and rationale

Order: **10-1 → 10-2 → 10-3.**
- 10-1 first: it depends only on 06–09 and is the input AC8 is measured on (AQ10 defines the rebuild as position-only
  with "the Phase 10 tail cache hits", BUILD_PLAN AQ10).
- 10-2 next: AC3, AC4, AC8, AC9 need the automation driver (S1), the scenarios (S6) and the job (S7); 10-3's gates
  need the same scenarios in both timing modes. AC7 asks every movement scenario for "its measured update interval",
  which in the product path is the realtime-sim interval max(20 ms cap, 30 ms crossfade, rebuild time) (A-AQ4), so
  the position-fade gate cannot be complete before S1b and S3 exist.
- 10-3 last: it sets the law on the scenarios and intervals 10-2 produces, and puts `clicks.py` into the job.
- S3's split update (AX38 (v)) is "designed together with phase-07c condition 4"; it stays in 10-2 unchanged.
  Phase 10 records no dependency on 07c and none is added; the coupling is carried as written.

Decisions (G1):

- **CHOICE 10-c1 (order: which risk is retired first).** Options: (A) scheduling first, law last, as above (10-2
  before 10-3): retires the staleness / AQ10-miss risk (AC8, R1) before the law risk (AC6/AC7 may require a new AX);
  every criterion stays whole. (B) law first: an "offline automation and crossfade law" sub-phase (S1a, S4, S5, S6,
  S7 offline leg, AC1 offline clause, AC2, AC3, AC6, AC7) before a "realtime-sim scheduling" sub-phase (S1b, S3, S8,
  S7 realtime-sim leg, AC1 realtime-sim clause, AC4, AC8–AC10): retires the law risk first, but needs AC1 split by
  timing mode (its "× 2 timing modes" is a factor, not a clause, so the G2 verbatim rule is strained) and runs AC7
  on offline update intervals only, before the realtime-sim intervals (larger steps, lower ρ) exist.
  **Recommended (A)**: no criterion reworded, AC7 measured on the intervals the product uses, and the phase file's
  own scope order (1 driver, 2 cache, 3 scheduling, then 5–7 control and suite). Whether retiring the law risk first
  is worth (B)'s costs is the decider's call.
- **CHOICE 10-c2 (clause split of scope 7).** S7 reads "CI job `automation` (…) runs all scenarios × 2 modes ×
  {offline, realtime-sim} through `render_cli` with the sustained-tone input | and runs `clicks.py`." AC8 says
  "recorded in the CI log; failing it fails the job", so the job must exist in 10-2. Options: (a) split S7 at its
  existing clause: 10-2 gets the job and the renders (verbatim first clause), 10-3 gets "and runs `clicks.py`";
  (b) S7 whole in 10-2, with `clicks.py` running but AC1 gated only from 10-3 (a job behaviour the file does not
  describe); (c) S7 and AC8 both in 10-3 (10-2 then loses its staleness gate and its CI-log record). **Recommended (a)**.
- **CHOICE 10-c3 (keep 10-1 standalone or merge into 10-2).** Options: (a) 10-1 standalone S (as above); (b) merge
  S2 / AC5 / CR2 into 10-2 (one M–L sub-phase with two lead subjects, Seat 2 and Seat 5). **Recommended (a)**: one
  lead subject each; the cache key is the bug the contractor focus names; the two-session limit is less likely to be
  crossed by 10-2. Not a size change across the two-session limit either way for the phase as a whole (the original
  is M); flagged because the brief asks for S sub-phases to be justified.

No other element is a decision: the lead seats are read from the convening table; no item crosses a recorded
dependency (06–09 are inherited by every sub-phase; 07c is not a recorded dependency of phase 10 and is not added).

## 3. Coverage table

| original item | → sub-phase | note |
|---|---|---|
| H: title, size M, depends on 06, 07, 08, 09, read first (AQ4, AQ10, AX1, AX18, AX20, AX22, AX33, FR-SIM-6, NFR-3, Q4) | umbrella | each sub-phase inherits 06–09; its own read-first subset (10-1: AQ10, AX20, PRD NFR-3; 10-2: AQ4, AQ10, AX20, AX22, AX33; 10-3: AQ4, AX1, AX18, AX22) — shared |
| G (goal: no clicks, zipper or dropouts, both modes, deterministic offline; FR-SIM-6, NFR-3) | umbrella | shared by all three |
| A-AQ4 | umbrella | shared: 10-2 (cadence, coalescing, synchronous offline), 10-3 (30 ms crossfade); 10-1 (tail cached when only positions change) |
| A-AX18 ("This phase sets the law") | 10-3 | also umbrella (shared) |
| A-AX22 (switch-point dip gated in this phase) | 10-3 | |
| A-AX1 (no Doppler; "the PR must describe it") | 10-3 | also umbrella (shared); the description goes in 10-3's PR, the sub-phase that sets the movement crossfade |
| S1 automation in render_cli (`--automation`, ParameterMap, both modes) incl. S1a `--offline`, S1b `--realtime-sim` and "Document the mechanism" | 10-2 | |
| S2 tail cache (object, key, recompute list, equality test incl. t_mix,e / AX20 change, diffuse solve with no cache credit, kernel cache only through a new AX) | 10-1 | |
| S3 rebuild scheduling (coalescing, never block, staleness metric incl. diffuse-gate wait AX38 (iii), split update with phase-07c condition 4) | 10-2 | |
| S4 parameter smoothing (20 ms trim, positions unsmoothed, room size same path, document stepwise room-size automation, AX38 4c hand-off) | 10-2 | |
| S5 negative control `MAKROOF_TEST_HARD_SWITCH` | 10-3 | |
| S6 automation scenario suite (20 scenarios) | 10-2 | |
| S7 CI job `automation` … "runs all scenarios × 2 modes × {offline, realtime-sim} through `render_cli` with the sustained-tone input" | 10-2 | clause split, CHOICE 10-c2 |
| S7 … "and runs `clicks.py`" | 10-3 | clause split, CHOICE 10-c2 |
| S8 isolated-update cap (AX33 confirm/replace; idle poll `kIdlePollS` confirm/replace; worst-case extra delay) | 10-2 | |
| OOS (Doppler; dynamic reduction of the image list) | umbrella | shared |
| AC1 0 click events, 20 × 2 × 2 | 10-3 | |
| AC2 negative control flagged ≥ 18 of 20 | 10-3 | |
| AC3 offline bit-identical across two runs | 10-2 | |
| AC4 static scene offline vs realtime-sim within −120 dB | 10-2 | |
| AC5 tail cache equals full rebuild within −120 dB | 10-1 | |
| AC6 AX22 switch point gate (incl. instrument self-test, transient-input report, time-segment-split AX branch) | 10-3 | |
| AC7 position-fade gate (AX18 amendment) incl. speed / update interval / largest band step per scenario, new-law branch, known limit | 10-3 | |
| AC8 worst-case staleness ≤ 100 ms incl. phase-13 scope 1 optimisation branch and `blocked (AQ10 miss)` with Maisara's (a)/(b) | 10-2 | |
| AC9 no allocation in `processBlock` during the automation scenarios | 10-2 | |
| AC10 pluginval strictness 10 | 10-2 | |
| L0 preamble (Logic + one VST3 host, pad and drums, both modes) | umbrella | shared by 10-2 (L5) and 10-3 (L1–L4) |
| L1 emitters 1 m → 15 m and back over 8 bars | 10-3 | |
| L2 listener jumps between corners every beat | 10-3 | |
| L3 room-size sweep over 4 bars | 10-3 | |
| L4 fast moves washy, not pitch-wobbly; Doppler preference is a product decision | 10-3 | |
| L5 offline bounce sounds like realtime playback | 10-2 | |
| CR1 scheduling and coalescing logic | 10-2 | |
| CR2 cache-key completeness | 10-1 | |
| CR3 realtime-sim clock mechanism | 10-2 | |
| CR4 negative control exercises the same code path | 10-3 | |
| R1 IR rebuild cost in large rooms; propose (not implement) an image-list reduction AX | 10-2 | |
| R2 detector blind spot below 2 kHz; 40 Hz scenario and low-band detector variant if cheap | 10-3 | |
| DoD1 all automated criteria green | umbrella | shared: each sub-phase for the criteria it owns |
| DoD2 staleness numbers in the status notes | 10-2 | |
| DoD3 status row 10 `done` | umbrella | set when 10-1…10-3 are `done` (G3); each sub-phase sets its own row |
| Raise with Maisara | — | none in phase-10.md |
| settled / decisions before implementation | — | none in phase-10.md |

## 4. References

Grep of the repo (excluding `docs/corpus`, `docs/review`, `docs/sessions`) for Phase 10 references. "umbrella" =
refers to the phase as a whole and still resolves to the umbrella file.

| file:line | reference | → |
|---|---|---|
| `CLAUDE.md` (render_cli section: `--automation`, no explicit phase-10 item) | — | none |
| `docs/BUILD_PLAN.md:35` | §0 row 10 | umbrella (`split (10-1…10-3)`) + rows 10-1, 10-2, 10-3 |
| `docs/BUILD_PLAN.md:89` | AQ4: "Phase 10 confirms or replaces it" (AX33); breaks 10 | 10-2 (S8); AQ4 breaks: umbrella |
| `docs/BUILD_PLAN.md:95` | AQ10: "the Phase 10 tail cache hits"; Table 15.1 scattering-part "Phase 10 cache option, only through an AX" | 10-1 |
| `docs/BUILD_PLAN.md:112` | AX12: `--automation` usage error "until Phase 10" | 10-2 (S1) |
| `docs/BUILD_PLAN.md:118` | AX18: "placeholder until Phase 10 sets the law and its gate"; large jumps (Phase 10); breaks 10 | 10-3 (A-AX18, AC7) |
| `docs/BUILD_PLAN.md:122` | AX22: Phase 10 reports and gates the switch-point dip; time-segment-split AX | 10-3 (AC6) |
| `docs/BUILD_PLAN.md:131` | AX31: "Phase 10 swaps about every 30 ms" | umbrella (informational) |
| `docs/BUILD_PLAN.md:133` | AX33: "Phase 10 confirms or replaces it" | 10-2 (S8) |
| `docs/BUILD_PLAN.md:138` | AX38 (iii) staleness metric; (v) Phase 10 AX split update; kernel cache (Phase 10) reopens (ii) and 4b; 4c hand-off stepwise room-size automation | (iii), (v), 4c → 10-2 (S3, S4); kernel cache → 10-1 (S2) |
| `docs/BUILD_PLAN.md:216` | §4 Phase 04 risks: Phase 10 gates the switch-point dip | 10-3 (AC6) |
| `docs/BUILD_PLAN.md:291` | §4 Phase 07c: cross-reference AX38 (v) and phase-10's update scheduling | 10-2 (S3) |
| `docs/BUILD_PLAN.md:315–321` | §4 Phase 10 summary (goal, scope, dependencies, acceptance, listening, from 05b, risks) | umbrella (needs a sub-phase pointer per item: scope smoothing/scheduling/wake-up → 10-2; law → 10-3; tail cache → 10-1; negative control → 10-3; acceptance per §3 above) |
| `docs/BUILD_PLAN.md:392, 394, 395, 398, 399, 402, 403, 427, 429, 434, 435, 446, 447` | §6 change-log rows naming phase-10 items (cache wording; staleness gate; switch-point gate; AX18 placeholder; scope 8; scope 3 → 07c) | historical record, not edited; resolve through the umbrella's old-item mapping (cache → 10-1; scope 3, scope 8, staleness → 10-2; switch-point gate, AX18 law, position-fade gate → 10-3) |
| `docs/phases/phase-02.md:38` | `--automation` "not implemented until Phase 10" | 10-2 (S1) |
| `docs/phases/phase-04.md:120, 154` | unit decay is "the object Phase 10 caches"; cache relies on position independence | 10-1 (S2) |
| `docs/phases/phase-04.md:374` | Phase 10 gates the switch-point dip | 10-3 (AC6) |
| `docs/phases/phase-05b.md:27` | early diffuse energy not part of the Phase 10 tail cache | 10-1 (S2) |
| `docs/phases/phase-05b.md:40` | Table 15.1 scattering-part option: first remedy Phase 10 may propose as an AX if W1 > 700 ms | 10-2 (R1 / AC8 branch) |
| `docs/phases/phase-05b.md:125` | equal-gain mid-fade dip −1.0 dB, "the Phase 10 bound" | 10-3 (AC7) |
| `docs/phases/phase-05b2.md:192` | room kernel cached "as in the Phase 10 tail cache" | 10-1 (S2) |
| `docs/phases/phase-05b2.md:215` | Table 15.1 option is a Phase 10 remedy only if W1 > 700 ms | 10-2 (R1 / AC8 branch) |
| `docs/phases/phase-05b2.md:228–230` | Phase 10's mid-fade gate; "phase-10 puts its limit at ≳ 8.5 dB" | 10-3 (AC7) |
| `docs/phases/phase-05b2.md:372`, `docs/phases/phase-05h.md:283` | "no level jumps (Phase 10 will gate this; listen now)" | 10-3 (AC7, L1, L3) |
| `docs/phases/phase-05b2.md:408`, `docs/phases/phase-05h.md:314` | Phase 10 caching beyond D-T1 / AX39 (kernel cache only through an AX) | 10-1 (S2) |
| `docs/phases/phase-06.md:9` | "Phase 10 builds movement on top of that swap" | umbrella |
| `docs/phases/phase-06.md:18` | equal-power for "Phase 10 large jumps" | 10-3 (A-AX18) |
| `docs/phases/phase-06b.md:151` | "`docs/phases/phase-10.md` scope item 8" | 10-2 |
| `docs/phases/phase-07.md:83–84` | tie jumps: "Phase 10 traversal scenarios … → Phase 10 proposes an AX" | scenarios → 10-2 (S6); judging the jumps and any AX → 10-3 (AC1, AC7, L2) |
| `docs/phases/phase-07.md:197` | EqualGain "AX18 placeholder …; Phase 10 sets the law" | 10-3 |
| `docs/phases/phase-07.md:287` | "zipper noise is acceptable here; Phase 10 removes it" | 10-3 (L1) |
| `docs/phases/phase-07c.md:88–90` | split update, a Phase 10 AX, "designed together with phase-10's update scheduling" | 10-2 (S3) |
| `docs/phases/phase-07c.md:146` | kernel cache "(AX38 (ii), phase-10 AX only)" | 10-1 (S2) |
| `docs/phases/phase-08.md:193` | remedy for Table 15.1's head-rotation row "is a Phase 10 AX" (split update) | 10-2 (S3) |
| `src/sim/Engine.h:94`, `src/sim/Engine.cpp:166`, `src/sim/tail/NoiseTail.h:5` | "Phase 10 proxy" / "the object Phase 10 caches" | 10-1 |
| `src/sim/conv/CrossfadingConvolver.h:4` | "Phase 10 builds movement on it" | umbrella |
| `src/plugin/core/ScenePipeline.h:28` | "EqualGain (AX18 placeholder until Phase 10)" | 10-3 |
| `src/cli/Cli.cpp:259, 623`, `tests/unit/test_cli.cpp:220`, `tools/acoustics/tests/test_render_cli.py:57` | `--automation` "not implemented until Phase 10" | 10-2 (S1; these change in 10-2) |
| `tests/unit/test_hybrid_ir.cpp:325, 581` | position-only rebuild from cached unit decays "as in Phase 10" | 10-1 |
| `.claude/skills/review-phase-pr/references/phase-checklists.md:291` | "## Phase 10" checklist (must contain / verify / traps) | umbrella; items: automation, scheduler, staleness, allocation, pluginval, bit-identical, static equivalence → 10-2; tail cache key → 10-1; negative control, 0 clicks, 40 Hz scenario, comb colouration on corner jumps → 10-3 |
| `.claude/skills/review-phase-pr/references/convolution-and-movement.md:32, 42, 48, 56, 448–496` | §5 "Update scheduling for moving sources (phase 10)": coalescing, rate limiting, staleness metric, realtime-sim clock, synchronous offline → 10-2; tail cache key (482), energy matching (491) → 10-1; 56 (staleness budget 100 ms) → 10-2 | as listed |
| `.claude/skills/review-phase-pr/references/convolution-and-movement.md:410` | hard-switch negative control (phase 10) | 10-3 |
| `.claude/skills/review-phase-pr/references/convolution-and-movement.md:770–805` | checklist "Scheduler and automation (phase 10)": items 26–30, 34–39 → 10-2; 31–33 → 10-1; 40 → 10-3 | as listed |

Note: `phase-checklists.md:291` says "worst staleness ≤ 100 ms at order 20", which the phase file no longer ties to
order 20 (change log 2026-11-05, R3). Pre-existing skill drift, not created by the split; a follow-up for the skill,
not changed here.
