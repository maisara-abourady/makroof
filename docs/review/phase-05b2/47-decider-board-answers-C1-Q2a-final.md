# Decider — board answers to Challenge 1 and Q2a (J1: yes + (A) now + (C) scheduled)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: board answers to Challenge 1 and Q2a (2026-11-10)

## Summary
- **Decision.** Challenge 1 = yes. Q2a = (A) now. (C) is scheduled now as its own phase, which must land before the first public release. Each element carries the seats' conditions, listed below.
- **Match with what was applied.** In outline this is what was applied (Challenge 1 yes; Q2a (A) now, (C) later). It is now the board's answer.
- **What the plan must still change.** As applied, the plan lacks the conditions that hold the seats' cells at 1, and D-H1's margin rule. The changes are listed in §5.
- **Q2b** stays decided at (i), n\*_max = 1 024 (file 43).
- **No veto** stands on the chosen combination. Q2a (B) "now" is dropped on Seat 5's veto (2/3).

Corpus revision: `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Bounds: the PRD and Maisara's settled decisions. AQ10 and AX36 are lifted for these questions on her delegated authority.

Inputs:
- `45-seat1…9-R1-R3.md`;
- C17 (`44-orchestrator-C17.md`);
- C18 (`46-orchestrator-C18.md`);
- C14 (c), C16 (f) and (g);
- phase-05h §3 (D-H1);
- `43-decider-board-answers-C1-Q2.md`.

## 1. Options
Challenge 1, Q2a and the scheduling of (C) depend on each other, so I decide over the combined options:

| option | Challenge 1 | Q2a | (C) |
|---|---|---|---|
| J1 | yes | (A) | scheduled now |
| J2 | no | (A) | scheduled now |
| J3 | yes | (A) | not scheduled |
| J4 | no | (A) | not scheduled |
| J5 | no | (B) now | – |

- J5 is the only form (B) can take now, because (B) fails the restore bound in every gated scene (C14 (c)).
- **Seat 5's offline-only (B), user-chosen, is not composed.** Seat 5 rates it 1/2. Seats 1, 6 and 8, who carry its costs (bounce and playback would differ), have not rated it. It cannot lower the maximum, because Seat 1's 2 is a real-time cell.

## 2. Tension maps

### Per question (each seat's own cells)

| seat | Challenge 1: yes | Challenge 1: no | Q2a (A) | Q2a (B) now | (C) scheduled | (C) not scheduled |
|---|---|---|---|---|---|---|
| S1 | 1/1 with (C); 1/2 without | 1/1 | 2/2; **2/1 with (C)** ("the 'now' 2 stands until that phase ships") | 1/1 | 0/1 | 1/2 |
| S2 | 1/2; **1/1** if W_max is never cut to pass the gate | 1/1 | 1/1 (raised from 0/1, on C16 (g)) | 0/1 | 0/1 | 1/2 |
| S3 | 1/1 with (C); 1/2 without | 1/1 with (C); 1/2 without | **1/2** (corrected from 1/1†) | 2/2 | 1/1 | 1/2 |
| S4 | 0/2; **0/1** under its conditions (gate measures the heaviest mode; one W_max; one re-derivation) | 0/1 | 1/1 (D-T1.3 at n\*_max 1 024) | 2/1 | 0/1 (0/0 under its conditions) | 1/1 |
| S5 | **1/1** (D-H1 margin taken from W_max) | 1/2 | 1/1 | **2/3** | 1/1 (under its conditions 1–5) | 1/2 |
| S6 | 1/1 under (a); 1/2 without | 1/1 | 1/1† | 2/2 | 1/1 (under (b)–(e)) | 1/2 |
| S7 | 1/1 (under its conditions) | 1/2; 1/1 under its conditions | 1/1† | 2/2 | 1/1 (before the first release, or versioned) | 0/2 |
| S8 | 1/1 with (C); 2 later without | 1/1 | 1/1† | 1/2 | 0/1 | 1/2 |
| S9 | 1/1 with (C); 1/2 without | 0/1 | **1/2 unless (C) is scheduled** | 1/1 | 0/1 | 1/2 under (A) |

### Combined map
For each seat and option I use the seat's composite rating where it gave one. Otherwise the cell is the worst of its component cells in each column, and the source is stated.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **J1** | 2/1 | 1/1† | 1/2 | 1/1† | 1/1 | 1/1† | 1/1† | 1/1 | 1/1 | **2** | **20** |
| J2 | 2/1 | 1/1 | 1/2 | 1/1 | 1/2 | 1/1 | 1/1† | 1/1 | 1/1 | 2 | 21 |
| J3 | 2/2 | 1/2 | 1/2 | 1/1† | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 2 | 27 |
| J4 | 2/2 | 1/2 | 1/2 | 1/1 | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 2 | 27 |
| J5 | 1/1 | 0/1 | 2/2 | 2/1 | 2/**3** | 2/2 | 2/2 | 1/2 | 1/1 | 3 | – |

Where the J1–J4 cells come from:
- **S1 in J1/J2:** 2/1 from its Q2a (A) cell with (C) scheduled. Its J1 composite (1/1) and its (C) cell (0/1) are lower.
- **J1, read from conditions (†):**
  - S2: condition "W_max never cut to pass the gate". Its (A) cell is 1/1, its (C) cell 0/1.
  - S4: conditions on "yes", folded in below; component cells 0/1, 1/1, 0/1.
  - S6: condition (a) on "yes"; conditions (b)–(e) on (C).
  - S7: conditions on "yes" and on (C).
- **S3 in J1/J2:** 1/2, its corrected (A) cell, taken as stated. Its "yes" and "no" with (C) are each 1/1, and its R3 text calls (C) "the only route that repays (A)'s level debt". Whether the (A) cell becomes 1/1 once (C) is scheduled is not stated, so I ask (S3-c).
- **S5 in J2:** its "no" cell 1/2. The (C) conditions do not restate it.
- **S7 in J2:** its "no" cell read at 1/1 from its conditions.
- **J3 and J4:** each seat's "not scheduled" cell, or its "yes"/"no" without (C), whichever is worse.

## 3. Working
1. **Bounds.**
   - J5 needs Challenge 1 "no" and breaks the restore bound in every gated scene (C14 (c): 2.16–4.83 s per restore, 30.2–67.6 s for 14).
   - It also carries Seat 5's veto (Q2a (B) later 3: "commits the synchronous host calls to multi-second blocks at large rooms, with nothing to bound them").
   - **J5 is dropped.**
   - A (B)-class W_max stays reachable through (C): it is re-derived after the move.
2. **Vetoes.** None in J1–J4.
3. **Worst-off seat.** J1–J4 all have max 2, and in each case it is Seat 1's Q2a (A) "now". That 2 stays until (C) ships, because only the move off the restore path frees W_max. No composition lowers it now:
   - (B) "now" is vetoed;
   - offline-only (B) is unrated by the seats it costs, and is a different product behaviour.
4. **Composition.** J1 already folds in the conditions that hold S2, S4, S6 and S7 at 1 (§4). No condition lowers S1 or S3 below their cells.
5. **Sum.** J1 20, J2 21, J3 and J4 27. **J1 wins.**
   - J1 beats J2 on Seat 5 ("no" 1/2 against "yes" 1/1).
   - J1 beats J3 and J4 because scheduling (C) lowers eight seats' later cells.
6. **Reversibility.**
   - The gate's form and W_max are parameters until the first release (Seat 7).
   - (C) is scheduled, not built. Its cost is one phase of Phase 07-class rework (Seat 5), and nothing is built yet on (A)'s restore path (phase-05h §3).

## 4. DECISION
**Challenge 1 = yes, Q2a = (A) now, and (C) scheduled now.** The text for the plan:

**(i) Challenge 1: the blocking restore gate.** At 100 m and 96 kHz, 14 × t_restore ≤ 30 s, on the Release build.
- **D-H1's margin comes out of W_max, not the gate (Seat 5).** It is set from C++ data before the gate exists (Seats 5, 7; phase-05h §3), from:
  - the pre-registered realised-work ratio (AX41: about 1.05);
  - the restore spread, taken from the worst of at least 10 runs, not a best of 3 (Seat 5).
- **The margin is reported with what it costs:** the SE at each gated scene and in layouts 4/5 (Seat 1).
- **If the margin would take more than about 20 % of W_max** [Hyp, Seat 3], it comes back to the seats.
- **A gate failure is a defect.** It is never fixed by re-running the job (Seat 7), never by cutting W_max once W_max is pinned (Seat 2), and never by narrowing the room-size range or adding a formulation seam (Seat 6 (a)). The remedy is to move work off the restore path, i.e. bring (C) forward. If the non-diffuse build alone leaves W_max below Seat 1's floor at a gated scene, the result goes to Maisara before any range change (Seat 6 (a)).
- **From Phase 08 on, the gate measures the heaviest output mode, and W_max stays one constant for all modes (Seat 4).**
  - If Phase 08's heaviest-mode build makes the pinned W_max fail the gate, (C) is brought forward to land before Phase 08's goldens are frozen.
  - W_max is then re-derived once, under (C), with one golden round. That is Seat 4's "single re-derivation" taken together with Seat 2's no-cut rule. S4's cell is read from conditions here, because Seat 4 wrote "planned in Phase 08" (S4-c).

**(ii) Q2a (A), now.**
- W_max is sized to the restore budget (30 s / 14 minus the worst OS build), less D-H1's margin.
- It is a pinned work count, the same on every platform (AX41).
- It is re-derived from the C++ cost, never a time cap (Seat 2).

**(iii) (C), scheduled now as its own phase.** The diffuse solve moves off the synchronous restore, prepare and `reset()`. Conditions:
1. **Timing.** It lands before the first public release (the Phase 13 beta), with its W_max raise in one golden round. If it lands after release, the estimator parameters are versioned in saved state (Seats 5, 7).
2. **Seam now.** Phase 05h invokes the solve through one function from restore, prepare and reset (Seat 5).
3. **W_max is re-derived under (C)** from the background budget: Seat 6's 3 s per emitter, the AX38 (iv) load mark, and Table 15.1's 700 ms / 3 s rows (Seats 1 (i), 3 (5), 5). It is not kept at (A). It stays a pinned work count.
4. **No real-time waiting.**
   - The real-time path adopts the solved snapshot by atomic swap with an AQ4 crossfade, exactly one step per solve and never mid-drag. The UI shows "settling" (AX38 (iii)) (Seats 1 (iii), 3 (2), 5, 6 (c), 8 (ii)).
   - The ISM update is never held behind the diffuse solve (Seat 3 (4)).
5. **Interim level, in order of preference:**
   1. the E_b saved in the project state, when the scene and W_max match, so that restore level equals final level (Seats 3 (1), 4, 8 (iii); feasibility is Seat 5's to judge in that phase);
   2. otherwise the (A)-budget estimate or the previous level (Seat 6 (b)).
   
   It is never silence and never the AX16 level where AX16 is known to be more than 1 dB off, such as layouts 4/5 and the absorbing-floor cube (Seats 1, 4, 9). The provisional-to-final step must stay within Seat 1's ruling (Seat 6 (d)).
6. **Offline.** Offline renders, bounces and `render_cli` always wait for the final solve and stay bit-identical. Where the host's offline signal is unreliable, the render log records it (Seats 1 (ii), 2, 4, 5, 6 (e), 8 (i), 9).
7. **Gates re-scoped after the move.** The restore gate measures restore without the solve; the solve time moves to the staleness records (Seat 5 (5)). E_b stays shared across modes and ears (Seat 4).
8. **Follow-on checks.** The Phase 12 (ii) preset check is re-run under (C)'s W_max (Seat 6 (e)). Phase 08 goldens in capped rooms carry a tolerance derived from the achieved SE, unless (C) lands before they are frozen (Seat 4).

### Load-bearing claims
- **L1 (C14 (c)).** Under (A), every gated scene restores in 2.14 s (14 restores = 30.0 s). Under (B), 2.16–4.83 s per restore, 30.2–67.6 s for 14.
- **L2 (D-H1).** Without a margin, "yes" + (A) gives 29.98 s, and about 30.2 s at a realised-work ratio of 1.05. Hence the margin rule in (i).
- **L3 (C16 (f), (g)).**
  - Under (A), layouts 4/5 at s = 1 are capped at SE 0.29–1.33 dB, and the low-α s = 1 cube at 0.44–0.67 dB. In that cube AX16 was only +0.06 / +0.10 dB off.
  - The absorbing-floor cube is corrected by 2.4 dB.
  - This is Seat 1's 2, carried until (C).
- **L4 (C17).** Under (B), layout 4's one-end cases meet Seat 1's floor (SE 0.09–0.22 dB). Layout 5 fails it on the pilot's VOV, not on SE. Both-near cases still fail. So (B)-class precision is worth reaching, by way of (C).
- **L5 (C18).** Halls with an absorbing audience floor (α 0.6–0.8, s ≤ 0.5) keep the short window. They are never capped under (A), have SE ≤ 0.083 dB, and U stays silent. This is measured on four rooms only. The capped class is the synthetic s = 1 long-window layouts, so (A)'s interim cost mostly falls outside realistic presets [Inferred beyond those four].
- **L6 (seats' words).** Seat 5's veto on (B) "now". Scheduling (C) lowers the later cells of S1, S2, S3, S5, S6, S7, S8 and S9 (§2).

### Future-debt register

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1 (2 now) | (A)'s random level error in capped long-window rooms until (C) ships | (C) | the C++ D-H1 SE report; the (C) phase | (C) lands with W_max re-derived |
| S3 (1/2 as stated) | (A)'s level debt | (C) | S3-c | (C) lands |
| S2 | no W_max cut to pass the gate; a gate failure brings (C) forward | schedule change | the Phase 08 heaviest-mode gate | (C) lands |
| S4 | the gate in the heaviest mode from Phase 08; one W_max for all modes; capped-room goldens with an SE tolerance | Phase 08 work | Phase 08 records | Phase 08 / (C) |
| S5 | one phase of rework; the seam in 05h; the margin rule | about one phase | C++ restore spread; the (C) phase | (C) done |
| S6 | provisional step and "settling"; the Phase 12 re-check | UI and preset re-check | (C) phase; Phase 12 | Phase 12 under (C)'s W_max |
| S7 | (C) before the first release, or versioned parameters | schedule | Phase 13 planning | first release |
| S8, S9 | the interim level never AX16 where it is wrong; bounces wait | – | the (C) phase tests | (C) done |

**Strongest objection.** Seat 1 sits at 2 now in every surviving option. It holds because the 2 is repaid by (C) with a date (before the first release), and C18 indicates that realistic hall presets are not in the capped class meanwhile.

It would fall in two cases:
- the (C) phase slips past the first release without versioning (then Seat 7's condition fails, and the item returns to Maisara);
- a Phase 12 hall preset turns out to be in the capped class (Seat 9's check).

**Confidence:** medium. Four cells are read from conditions, and S3 and S4 still need a one-line confirmation each.

**Reversal:**
- the C++ restore spread makes the margin exceed about 20 % of W_max (back to the seats);
- Phase 08's heaviest mode fails the gate (bring (C) forward);
- S3-c or S4-c rated 3.

## 5. Changes the plan needs (/fix-plan)
1. **AQ10 amendment and AX38 4c** (Challenge 1 yes): keep, with (i)'s conditions:
   - the margin is taken from W_max;
   - margin inputs: worst of ≥ 10 runs, plus the pre-registered ratio;
   - the margin's SE cost is reported;
   - a margin above about 20 % of W_max goes back to the seats;
   - Release build;
   - a failure is a defect: no re-run, no W_max cut, no range narrowing;
   - the heaviest mode is gated from Phase 08;
   - (C) is brought forward on a Phase 08 gate failure.
2. **AX41, W_max basis:** "(A): restore budget less D-H1's margin, pinned; re-derived once under (C) from the background budget". Record Q2a and Challenge 1 as **board answers (decider file 47 / this record)**, replacing the orchestrator's statement. That closes the steward's G1.
3. **phase-05h §3 D-H1:** add the margin rule from (i). **§4:** add the single-function solve seam (Seat 5).
4. **A new phase file for (C)** (suggested name `phase-07c.md`, "asynchronous diffuse solve"):
   - conditions (iii) 1–8;
   - status-table row: depends on 05h; must be done before Phase 13's beta; brought ahead of Phase 08's golden freeze if Phase 08's heaviest mode fails the gate;
   - its own decision loop for the interim-level and saved-E_b design (a state-version AX if E_b goes into the state).
5. **phase-08:** the gate measures the heaviest output mode; W_max is one constant; capped-room goldens carry an SE-derived tolerance, unless (C) has landed.
6. **phase-12:** the (ii) preset check is re-run under (C)'s W_max. Seat 9: hall presets are checked for capped-class membership at the final W_max.
7. **phase-13:** (C) is a beta prerequisite; otherwise, versioned estimator parameters in saved state (Seat 7).
8. **Ledger:** R1–R3 rows; this decision; Seat 5's offline-only (B) recorded as not adopted (unrated by Seats 1, 6, 8).

## 6. Seats still to confirm (one line each; only a 3 changes anything)
- **S3-c (Seat 3).**
  > With (C) scheduled under conditions (iii) 1–8, including your (1)–(5), is your Q2a (A) cell still 1/2, or 1/1?
- **S4-c (Seat 4).**
  > Your "single W_max re-derivation, planned in Phase 08" is composed as: if Phase 08's heaviest mode fails the gate, (C) is brought forward and W_max is re-derived once, under (C), with one golden round, never cut to pass the gate (Seat 2). Does "yes" stay at 0/1 for you?

## For Maisara
The board's answers are now on record:
- The 100 m restore gate becomes a CI block.
- The big-room work limit is sized to it for now.
- A dedicated phase, before the first public release, moves that work off the project-load path, so the limit can grow without slowing loads.

This matches what the orchestrator told you. What is new is the conditions: the margin comes out of the work limit, a failing gate is never "fixed" by cutting accuracy or room sizes, and bounces always wait for the final level. Seat 1 gave the most (some extreme synthetic rooms keep about ±0.3–1.3 dB until that phase). Realistic halls with audience floors are not affected (C18). No veto override is needed.

Files:
- /home/user/makroof/docs/review/phase-05b2/45-seat1-R1-R3.md … 45-seat9-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/44-orchestrator-C17.md
- /home/user/makroof/docs/review/phase-05b2/46-orchestrator-C18.md
- /home/user/makroof/docs/review/phase-05b2/43-decider-board-answers-C1-Q2.md
- /home/user/makroof/docs/phases/phase-05h.md
