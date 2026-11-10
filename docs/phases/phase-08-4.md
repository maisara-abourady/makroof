# Phase 08-4 — Binaural timing records, restore gate and golden freeze

Size: **M** (remainder, if needed: `08-4b`) · Depends on: 08-3; and 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Part of: [phase-08](phase-08.md) · Lead subject matter: Seat 5 (Deadline keeper), "worst-case callback time; … host conformance (pluginval, auval, state …); … CI gates" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the umbrella [phase-08](phase-08.md) (shared items); [phase-08-1](phase-08-1.md) (pin-time results to settle before the freeze), [phase-08-2](phase-08-2.md), [phase-08-3](phase-08-3.md) (the BRIR, its checks and listening verdicts)

## Goal

This sub-phase's share of the [phase-08](phase-08.md) goal: the binaural room impulse response (BRIR)
built in 08-2 and 08-3 is benchmarked, checked against the update-time limit and the heaviest-mode restore
gate, and its goldens are frozen (phase-08 scope 5 grouping rule, scope 7 goldens clause, scope 8–10).

## Assumptions in force

- **AX37 (5.3)** (phase 05b): this phase receives E_b and t_mix,e per emitter through `TailMatch` and no
  tail directions; `bandsAxisShares` is a labelled specular-only diagnostic. A directional late tail is
  backlog (§5 B18), behind Seat 1's blind test. **AX39**: one diffuse solve per scene, shared across
  output modes. **AX38**: the diffuse solve runs through the process-wide gate; W1/W2 include it.
- **AX35**: the data behind a released `hrtfId` is never replaced; a different head, campaign or re-converted
  set is `generic-v2` with the old data retained. Before this phase's goldens are frozen a converter re-run
  is a parameter change.
- And all of the umbrella's ([phase-08](phase-08.md), "Assumptions in force").

## Scope

Order inside 08-4, written in the file: benchmark on the full BRIR → grouping decision → S8, S9, S10 →
golden freeze; timing recorded on the post-grouping build only. (D-PS2, `3-decider-decision.md`, step 3;
S8, S9, S10 = phase-08 scope 8, 9, 10)

5. **No 2° grouping until the Phase 08 benchmark shows it is
   needed; measure first.** Only if the measured BRIR build time calls for it, group image sources by
   direction cell (e.g. 2° bins) above reflection order 3 and render each group once, and document the
   approximation. (phase-08 scope 5, Early part, sentences 2–3; the rest in 08-2, D-PS2)
8. **Update-time check (ledger P06F-4):** once the head yaw follows the emitter centroid (AX3), emitter
   moves change the HRTF set; check whether Vorländer Table 15.1's head-rotation row (35 ms; filter
   content 'new HRTF') applies and, if so, whether the AQ4/AX31 isolated-update delay (slot wait +
   rebuild + 2P) meets it; record the result (an AX through /fix-plan if a change is needed).
   Before measuring, state which limit is applied (Table 15.1's 35 ms or the 20 ms printed in Vorländer
   §15 prose) and whether the 30 ms fade counts toward it (ledger P06B-66, phase-06b advocate). Under the
   35 ms limit with the fade not counted, W1 (20.6 ms on the Linux runner) lies in (35 − 2P, 35 − P] =
   (13.7, 24.3] ms at P = 512, where AX31's extra partition decides the row (31.3 vs 41.9 ms); so if the
   row applies, AX31's reversal clause applies (AX31 note, phase-06b D2). Under the 20 ms limit neither
   pickup variant meets it for W1 (20.6 > 20 ms) (ledger P06B-76).
   **Since phase 05b (AX38 (v)):** item 8 measures the delay of one isolated update with the wait at the
   diffuse-solve gate included, and records that the diffuse solve inside every rebuild, not the gate,
   is what breaks Table 15.1's 35 ms head-rotation row. If that row applies, the remedy is a Phase 10 AX
   that updates the specular and directional part without waiting for the diffuse solve, not a change to
   the gate. Seat 1 reads AX3's centroid-following yaw under the source-movement rows, not the
   head-rotation row [Inferred]; item 8 still measures. (phase-08 scope 8)
9. **Records from phase 05b (AX38)** (only if 05h is `done` when this phase runs; if this phase goes first
   under AX37 (5.3), phase-05h scope 10 carries them):** W1/W2 per output mode with the diffuse share shown separately
   (AX38 4b); the AX38 (iv) multi-instance records repeated in binaural mode, with the gate wait shown
   separately. (phase-08 scope 9)
10. **Restore gate in the heaviest mode (AX38 4c, AQ10; board answer, decider files 47 §4 (i), 51 §4
    item 5; only if 05h is `done` when this phase runs; if this phase goes first under AX37 (5.3),
    phase-05h scope 10 carries it):** from this phase on, the blocking 100 m, 96 kHz restore gate measures
    the heaviest output mode, and W_max stays one constant for all modes. If the heaviest-mode build makes
    the pinned W_max fail the gate, phase-07c (which depends on 05h) is brought forward, once 05h is
    `done`, to land before this phase's goldens are frozen (W_max is then re-derived once, under
    phase-07c, with one golden round); W_max is never cut to pass. Goldens in
    capped rooms carry a tolerance derived from the achieved SE, unless phase-07c has landed before they
    are frozen. (phase-08 scope 10)
7. goldens for 3 scenes. (phase-08 scope 7, clause; placed after the restore gate, convening round 08-c2 (b))

## Out of scope

The umbrella's out-of-scope list ([phase-08](phase-08.md)) applies.

## Acceptance criteria — automated

- [ ] All earlier tests still pass. (phase-08 AC12, sentence 1; shared, umbrella) Plugin CPU benchmark is
      recorded. (phase-08 AC12, sentence 3) If 05h is `done`:
      W1/W2 per output mode with the diffuse share and the binaural AX38 (iv) records are recorded
      (scope 9); otherwise phase-05h scope 10 records them. (phase-08 AC12, sentence 4)
- [ ] **Restore gate, heaviest mode (scope 10; if 05h is `done`, otherwise carried by phase-05h scope
      10):** 14 × t_restore ≤ 30 s at the AX38 4c scenes in the
      heaviest output mode, with the one W_max constant; capped-room goldens with the SE-derived
      tolerance unless phase-07c has landed. (phase-08 AC13)

## Listening / manual checklist (Maisara, headphones)

None from the phase-08 list. If grouping is introduced, the re-listen in "Notes from the split" (D-PS2
step 5) applies, with the umbrella's checklist preamble (phase-08 L0).

## Contractor review focus

- the image-source grouping approximation (if the benchmark introduced it) (phase-08 CF6)

## Risks

- BRIR build time with many image sources. Measure it against AQ4's 20 ms cadence (AX33) first; grouping
  (scope 5) is introduced only if the benchmark shows it is needed. (phase-08 R3)

## Notes from the split

- AX37 (5.3) condition binding this sub-phase: (iii) 05h re-renders the binaural goldens, re-measures
  binaural W1/W2 and re-runs item 8. (D-PS1, `docs/review/phase-split/5-decider-decision-r2.md`,
  instruction 5)
- In this split, 'Phase 08 went first' in phase-05h scope 10 (goldens, W1/W2, item 8) means 08-4 ran before
  05h was `done`. (D-PS1, instruction 6)
- phase-05h line 286's addition (outside AX37 (5.3)) applies if 08-3 ran before 05h was `done`. (D-PS1,
  instruction 6)
- The binaural goldens that (iii) re-renders include 08-2's early part; 08-2 freezes none. (D-PS1,
  instruction 6)
- If grouping is introduced: AC3, AC5, AC6, AC8 re-run on grouped output, and L1, L3, L4, L5 (wording
  unchanged) re-listened on grouped output before the goldens freeze (same fixed set, same forced-choice
  form, 08-3 renders beside the new ones); the PR states whether grouping was introduced; the provisional
  mark lapses if it was not. (D-PS2, `docs/review/phase-split/3-decider-decision.md`, step 5)
- Not an added item: in the unsplit phase these items were heard after the grouping decision; this
  restores that. (D-PS2, step 6)
- The goldens for 3 scenes (phase-08 scope 7) are frozen here, after the restore gate, because scope 10 and
  AC13 require the gate result before "this phase's goldens are frozen" (convening round, 08-c2 (b),
  `1-decider-convening.md`). The freeze-point conditions set in 08-1 apply to it: phase-08 scope 1 (TH Köln
  re-entry "before the Phase 08 goldens are frozen"), scope 3 and R6 (a "not confirmed" source state raised
  "before any golden is frozen"), and AX35 (a converter re-run before the freeze is a parameter change).

## Definition of done

- All automated criteria green (phase-08 DoD1; this sub-phase's own).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the
  remainder into `phase-08-4b.md`.
