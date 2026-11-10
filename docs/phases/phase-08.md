# Phase 08 — Binaural output with a generic HRTF

Size: **split into 08-1…08-4** · Depends on: 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the D1 decision (`docs/review/board-smoke/hrtf-head/`, accepted by Maisara 2026-11-09) behind scope 1–3

## Goal

Headphone rendering (`outputMode = binaural`). Every early reflection reaches the listener's ears from
its true direction through a measured **generic HRTF**, and the late tail has the interaural coherence
of a diffuse field. The result is a 2-emitter × 2-ear binaural room impulse response (BRIR) applied by
the Phase 06 convolver.

## Assumptions in force

- **AQ6**: one generic HRTF, with the contract `hrtfId = "generic-v1"`. No personalization (deferred, B4).
- **AX3**: the head is upright, and yaw points toward the horizontal centroid of the emitters. If the
  centroid is within 0.1 m horizontally of the listener, the previous yaw is held (initial yaw = +y).
- **AX5**: deterministic; tail noise per ear is seeded from `tailSeed` with the per-output offset from Phase 04.
- **AX37 (5.3)** (phase 05b): this phase receives E_b and t_mix,e per emitter through `TailMatch` and no
  tail directions; `bandsAxisShares` is a labelled specular-only diagnostic. A directional late tail is
  backlog (§5 B18), behind Seat 1's blind test. **AX39**: one diffuse solve per scene, shared across
  output modes. **AX38**: the diffuse solve runs through the process-wide gate; W1/W2 include it.
- **AX35**: the data behind a released `hrtfId` is never replaced; a different head, campaign or re-converted
  set is `generic-v2` with the old data retained. Before this phase's goldens are frozen a converter re-run
  is a parameter change.

## Sub-phases

| id | title | lead seat | size | depends on | ships | owns |
|---|---|---|---|---|---|---|
| [08-1](phase-08-1.md) | HRTF data, converter and lookup | Seat 4 (Chain keeper), "HRTF dataset choice and licence; binaural architecture" | M | the header's line | licensed, pinned, converted `resources/hrtf/generic-v1.bin` with its dataset-agnostic header and Voronoi-weighted DF-EQ / coherence target, embedded in `sim`, and `HrtfSet::query` with interpolated HRIRs + ITD | AC1, AC2, AC4, AC9 |
| [08-2](phase-08-2.md) | Head-relative early binaural part | Seat 4 (Chain keeper), "binaural architecture" | M | 08-1; the header's line | `ListenerFrame` (AX3), BRIR early part through the HRTF, `buildRoomIR(Kind::Binaural)` 2×2, `render_cli --mode binaural`, the `--hrtf` validation override, anechoic listening-pack renders incl. `anechoic_azimuth_sweep.wav` | AC3, AC7, AC10 |
| [08-3](phase-08-3.md) | Binaural late tail, level parity and plugin mode | Seat 4 (Chain keeper), "binaural architecture; … cross-format loudness and timbre parity" | M | 08-2; the header's line | two seeded ear tails mixed to the HRTF-derived interaural coherence, diffuse-field magnitude per ear, omni/binaural energy and T30 parity, E_b via `TailMatch` (AX39 one solve), plugin `output_mode = binaural` wired, room listening-pack renders incl. the both-near render | AC5, AC6, AC8, AC11, AC12 "pluginval passes." |
| [08-4](phase-08-4.md) | Binaural timing records, restore gate and golden freeze | Seat 5 (Deadline keeper), "worst-case callback time; … host conformance (pluginval, auval, state …); … CI gates" | M (S-to-M in the 08-first order, where scope 9/10 move to phase-05h scope 10) | 08-3; the header's line | plugin CPU / BRIR-build benchmark in binaural, the 2° grouping decision taken on it, item 8's update-time record, W1/W2 per mode with the diffuse share and the binaural AX38 (iv) records, the heaviest-mode restore gate, the goldens for 3 scenes frozen | AC12 "Plugin CPU benchmark is recorded." and "If 05h is `done`: … records them."; AC13 |

Order: 08-1 → 08-2 → 08-3 → 08-4. Every sub-phase carries the header's dependency line verbatim; AX37 (5.3)
condition (i) binds 08-2 and 08-3, (ii) and (iv) bind 08-3, (iii) binds 08-4 (D-PS1,
`docs/review/phase-split/5-decider-decision-r2.md`). AC12's first sentence, "All earlier tests still pass.",
is owned by every sub-phase.

## Shared items (verbatim; each also in the sub-phase files named)

- No UI code or string table knows which head shipped: any About/credits text reads the header's attribution
  string; the main window and the mode switch never show a dataset name. (phase-08 scope 2, Dataset-agnostic
  header, last sentence; 08-1, and binding on 08-3's plugin wiring)
- Every preset validation log (the Phase 12 preset listening checklist and its PR listening notes, the Phase
  13 final listening pass through all presets, and the B9 (§5) protocol logs) records the `hrtfId` and the
  header's set identity string of the build it was listened through; this phase's checklist does the same.
  (phase-08 scope 7, last sentence; 08-2, 08-3)
- All earlier tests still pass. (phase-08 AC12, sentence 1; every sub-phase)
- Listening / manual checklist preamble (phase-08 L0; 08-2, 08-3): Listening pack (`binaural/`) and the
  plugin in a DAW with `output_mode = binaural`. The pack never names the head (the dataset is named only in
  the licence file, `docs/THIRD_PARTY.md` and the public testing record). Fixed acceptance set, rendered for
  every item: an **a cappella voice, pink-noise pulses and speech**. Every room render comes with an
  **anechoic direct-only render** (α = 1, direct path only) of the same emitter and listener positions
  beside it, and with the omni preview. Answer in the **forced-choice form**: location **front / back /
  above / inside / outside**; colour against the omni preview **none / boxy / thin / harsh**. Record the
  `hrtfId` and the header's set identity string of the build you listened through (scope 7).
- Contractor review focus: head named nowhere in UI (phase-08 CF1, clause; 08-1).
- Generic HRTFs cause front/back confusion and weak externalization for some listeners. This is an
  expected limitation, recorded as evidence for B4. (phase-08 R1; 08-2, 08-3)

## Out of scope

Personalized HRTF / SOFA import (B4), head tracking and head orientation control (PRD out of scope),
near-field HRTF correction (sources < 1 m; note it as a follow-up).

## Where the original items went

Labels as in `docs/review/phase-split/map-08.md`: scope items 1–10 (5a Early part, 5b Late tail, 5c Energy,
5d E_b and t_mix,e); AC1…AC13 = the automated criteria in file order (AC1 licence, AC2 converter round-trip,
AC3 ITD/ILD sanity, AC4 interpolation continuity, AC5 tail coherence, AC6 energy, AC7 orientation (AX3),
AC8 T30, AC9 DF-EQ identity, AC10 validation-only override, AC11 E_b parity (AX44), AC12 "All earlier tests
…", AC13 restore gate); L0 = the checklist preamble, L1…L7 the listening items in order; CF1…CF9 = the
contractor review focus clauses in order; R1…R7 = the risks in order; DoD1…DoD5 = the definition-of-done
clauses.

| original item | → |
|---|---|
| Header: size L, "split into 08 and 08b if needed" | umbrella (now per sub-phase; remainders `08-<n>b`) |
| Header: dependency line, incl. AX37 (5.3) conditions (i)–(iv) | umbrella and every sub-phase (verbatim); (i) binds 08-2 and 08-3, (ii) and (iv) 08-3, (iii) 08-4 |
| Header: Read first | umbrella and every sub-phase; the D1 decision (behind scope 1–3) in 08-1 |
| Goal | umbrella; each sub-phase states its share |
| Assumptions AQ6, AX3, AX5, AX37 (5.3) / AX39 / AX38, AX35 | umbrella (all); AQ6, AX35 also 08-1; AX3 also 08-2; AX5, AX37 bullet also 08-3; AX37 bullet, AX35 also 08-4 |
| Scope 1 (Licence first) | 08-1 |
| Scope 2 (converter), Embed bound | 08-1 |
| Scope 2, Dataset-agnostic header | 08-1; its last sentence ("No UI code …") shared: umbrella, 08-3 |
| Scope 3 (`HrtfSet`), `query`, Diffuse-field equalization | 08-1; the "`[alloc]` … on the BRIR build" part 08-2 (shared with 08-3) |
| Scope 4 (`ListenerFrame`) | 08-2 |
| Scope 5 lead-in | 08-2, 08-3 |
| Scope 5a, first and last sentences | 08-2 |
| Scope 5a, "No 2° grouping until … document the approximation." | 08-4 (D-PS2) |
| Scope 5b, 5c, 5d | 08-3 |
| Scope 6, sentence 1 (`Kind::Binaural`) | 08-2 |
| Scope 6, sentences 2–3 (plugin `outputMode`; `stereoSpeakers`) | 08-3 |
| Scope 7, `render_cli --mode binaural` | 08-2 |
| Scope 7, listening-pack entries | 08-2 (anechoic renders) and 08-3 (room renders, omni previews) |
| Scope 7, both-near binaural render | 08-3 |
| Scope 7, goldens for 3 scenes | 08-4 (convening round, 08-c2) |
| Scope 7, `render_cli --hrtf <file>` | 08-2 |
| Scope 7, preset validation log sentence | shared: umbrella, 08-2, 08-3 |
| Scope 8 (update-time check, "item 8") | 08-4 |
| Scope 9 (records from 05b) | 08-4 (otherwise phase-05h scope 10) |
| Scope 10 (restore gate, heaviest mode) | 08-4 (otherwise phase-05h scope 10) |
| Out of scope | umbrella |
| AC1, AC2, AC4, AC9 | 08-1 |
| AC3, AC7, AC10 | 08-2 (AC3's onset criterion named at the start of 08-1, convening round 08-c4) |
| AC5, AC6, AC8, AC11 | 08-3 |
| AC12 sentence 1 "All earlier tests still pass." | shared: umbrella, every sub-phase |
| AC12 sentence 2 "pluginval passes." | 08-3 |
| AC12 sentences 3–4 (CPU benchmark; W1/W2 records) | 08-4 |
| AC13 | 08-4 |
| L0 | shared: umbrella, 08-2, 08-3 |
| L2 | 08-2 |
| L1, L3, L4, L5, L6, L7 | 08-3 (L1, L3, L4, L5 provisional if 08-4 introduces grouping, D-PS2) |
| CF1, CF2, CF4, CF5 | 08-1 (CF1's "head named nowhere in UI" shared: umbrella) |
| CF3, CF9 | 08-2 |
| CF6 | 08-4 |
| CF7, CF8 | 08-3 |
| R1 | shared: umbrella, 08-2, 08-3 |
| R2, R5 | 08-2 |
| R3 | 08-4 |
| R4, R6 | 08-1 |
| R7 | 08-3 |
| DoD1 | shared: umbrella; each sub-phase for its own criteria |
| DoD2 | 08-1 |
| DoD3 | shared: umbrella, 08-1 |
| DoD4 | umbrella |
| DoD5 | shared: umbrella, 08-2, 08-3 |

## Notes from the split

- In this split, 'Phase 08 went first' in phase-05h scope 10 (goldens, W1/W2, item 8) means 08-4 ran before
  05h was `done`. (D-PS1, `docs/review/phase-split/5-decider-decision-r2.md`, instruction 6)
- phase-05h line 286's addition (outside AX37 (5.3)) applies if 08-3 ran before 05h was `done`. (D-PS1,
  instruction 6)
- The binaural goldens that (iii) re-renders include 08-2's early part; 08-2 freezes none. (D-PS1,
  instruction 6)

## Definition of done

All automated criteria green (phase-08 DoD1); the head named only in `LICENSE-generic-v1.txt`,
`docs/THIRD_PARTY.md` and the public testing record (phase-08 DoD3); status row 08 `done` (or 08b added)
(phase-08 DoD4); checklist in the PR with the `hrtfId` and set identity string (phase-08 DoD5).

Status: the umbrella is `done` when every sub-phase is. A dependency on phase 08 means all of its
sub-phases unless a sub-phase is named.
