<!-- Saved by the orchestrator from the interrogator's report, 2026-11-22. -->

Interrogator on `docs/review/phase-07c-2/15-decider-rebuttal-r5.md` (decision mode, round 5). Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

# Interrogator on file 15: D-W3 (H-2c with the generation check), D-W4 homed in phase-10-3

## Outcome per item

Both revised items survive with small corrections: three on D-W3, one on D-W4. Nothing fails this round.

| item | outcome | in one line |
|---|---|---|
| **D-W3 (H-2c)** | **SURVIVES WITH CORRECTIONS** (3) | The file 14 failure is repaired: the (P, S) key is withdrawn and today's generation discard is kept. The cells are the seats' own words, and the ordering stands at max 2 with sum 16. Corrections: one wording slip in item 3, stale line references, one overstatement in the strongest objection. |
| **D-W4** | **SURVIVES WITH CORRECTIONS** (1) | The home exists: `docs/phases/phase-10-3.md`, "Crossfade law and artefact gates under movement", lead Seat 3, ahead of 13. RQ-W4-1 is well posed. The repayment rows name items that phase-10-3 will hold only once the `/fix-plan` edit lands. |
| FM-W3a (withdrawn), D-W2 final, D-W1 waiting list | **SURVIVE** (unchanged since file 14) | — |

### D-W3 corrections

1. **Item 3 is weaker than today's check as worded.** It says "`dirty_` is unchanged since the solve started (today's generation check, L555)".
   - Today the reference generation is read before the scene snapshot: L355–356, "The generation is read BEFORE the snapshot". So the check covers edits made during the B1′ ISM build too, and those already stop the solve before it starts (L543).
   - A generation read at solve start would miss an edit that lands between the snapshot and the solve start. A stale-scene solve could then be adopted as the final mid-drag, which is not what the code does today.
   - Restate item 3 as "unchanged since the generation read before the scene snapshot (L356)". Item 4's token must compare against that same generation.
   - With that wording the claim "exactly what the code does today" holds.
2. **Line references at HEAD have shifted.**

   | what | file 15 cites | at HEAD |
   |---|---|---|
   | `dirty_` bump in `setParameter` | L315 | L329 |
   | mid-drag check before the solve | L542 | L543 |
   | mid-drag check after the solve | L555 | L556 |
   | single-committer comment | L582 | L583 |
   | trim ramp | L977–998 | around L978–999 (`trimTarget_ = target` at L989) |

   `IrBuilderThread.h` L5 ("One std::thread that runs `decide`") is unchanged. The file is moving between rounds, so cite by function and comment as well as by line.
3. **The strongest objection overstates.** "They need condition 4 changed, and only she can change it" is correct for Seats 1 and 6, whose conditions need adoption during motion. It is IMPRECISE for Seat 2.
   - Seat 2's rule 1 (problem-key adoption) differs from the generation check only on edits that leave the `DiffuseProblem` unchanged. Output trim is the continuous case.
   - Whether a trim drag is a "drag" in condition 4's sense is a scope reading, which decider.md §1a lets the decider answer as FOR MAISARA if the PRD settles it. You chose not to attempt it, which is legitimate.
   - So write "no in-bounds option removes it without a scope reading of condition 4", not "only she can change it".
   - The ordering does not change: one composed variant has already been used this round, and H-0 keeps Seat 2's 2 regardless.

### D-W4 correction

1. **Make the `/fix-plan` edit a tracked deliverable.** The debt rows for S1, S2, S4, S6 and S8 are repaid at "D-W4 in 10-3", and S3's at "the 10-3 gate". Phase-10-3 exists, but its automated record (M7b plus the validation-only alternative) and its listening item do not exist until the `/fix-plan` edit lands.
   - Until then the rows point to items that are not yet in the plan.
   - The edit has to land in this session, with the steward checking it, or the deferral drops the debt in effect.

---

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question |
|---|---|---|---|---|---|---|
| D-W3 | map | S2 1/2 | faithful (seat's own words) | 10-seat2: "Without rule 1 (generation check only): 1/2" | — | — |
| D-W3 | map | S3 1/1 | faithful | 10-seat3 §3: "(b) A doomed solve stops at its next `run.stop` once its generation is stale"; (a) is M7 | — | — |
| D-W3 | map | S1 0/2, S4 1/1, S5 1/1 (token as "an atomic comparison of `dirty_` against `gen`"), S6 1/2, S7 1/0, S8 0/1, S9 0/0 | faithful | 10-seat1, 4, 5 (H-1 (i)), 6, 7, 8, 9 | max 2, sum 6 + 10 = 16 | — | — |
| D-W3 | ordering | survivors and sums: H-2c 16 < H-2 as stated 19 < H-1 21 < H-0 29; H-3 dropped on S3's 3 | correct | recounted | — | — |
| D-W3 | claim | item 3 "since the solve started" | IMPRECISE (weaker than today) | from the code: `gen` read at L356 before the snapshot; L543 stops the solve on edits during the B1′ build | correction 1 | Q1 |
| D-W3 | claim | item 4 token stops at the next stop point once `dirty_` ≠ generation | CORRECT, if the generation is L356's | Seat 5 H-1 (i); Seat 3 (b) | — | Q1 |
| D-W3 | claim | trim facts: `output_trim_db` continuous, not in `SceneDescription`, bumps `dirty_` | CORRECT (lines stale) | `ParameterMap.cpp` L65; `ScenePipeline.cpp` L329, L989 | correction 2 | — |
| D-W3 | claim | discards at L542 / L555; committer comment L582 | CORRECT in substance; lines stale | HEAD: L543, L556, L583 | correction 2 | — |
| D-W3 | claim | condition 4 "holds literally" under H-2c | CORRECT, with correction 1 | phase-05b2 file 47 L119 | — | — |
| D-W3 | strongest objection | "only she can change it" (Seat 2) | IMPRECISE | decider.md §1a scope readings; README item 1 | correction 3 | — |
| D-W3 | debt | seven rows; repayment phases 07d, 08, 10-1, 10-3, 11-3 | exist | phase files present | — | — |
| D-W4 | debt | "D-W4 in 10-3", "the 10-3 gate" | conditional on the `/fix-plan` edit | phase-10-3.md L1, L3 (lead Seat 3); the items are not yet in its scope | D-W4 correction 1 | Q2 |
| D-W4 | deadline | before Phase 13's beta; Raise item in phase-13 if 10-3 slips | consistent | phase-10-3 is part of phase 10, which precedes 13 | — | — |
| D-W4 | inventory | RQ-W4-1 | well posed and falsifiable; anchored on the Lentz et al. (2007) source the corpus names | Vorländer §15.3, Table 15.1 | — | — |
| D-W3 | Decided for Maisara | "cancels it, exactly as the plugin already does today" | IMPRECISE in mechanism (today discards at the end); same outcome | L543, L556 | wording | — |

## Questions for the decider

1. Is item 3's reference generation the one read before the scene snapshot (L356), so that an edit during the B1′ build still discards, as at L543? Does item 4's token compare against the same value?
2. Will the `/fix-plan` edit adding D-W4's automated record and listening item to phase-10-3 land in this session as a tracked item, so that the five debt rows name items that exist?

Files examined:
- `/home/user/makroof/docs/review/phase-07c-2/15-decider-rebuttal-r5.md`
- `/home/user/makroof/docs/review/phase-07c-2/10-seat2.md`, `/home/user/makroof/docs/review/phase-07c-2/10-seat3.md`, `/home/user/makroof/docs/review/phase-07c-2/10-seat5.md`
- `/home/user/makroof/src/plugin/core/ScenePipeline.cpp` (L324–359, L500–587, L989)
- `/home/user/makroof/src/plugin/core/IrBuilderThread.h`
- `/home/user/makroof/src/module3d/ParameterMap.cpp` (L65)
- `/home/user/makroof/docs/phases/phase-10-3.md`

---

**Orchestrator's application (2026-11-22, no new decision).** D-W3 (H-2c, file 15) and D-W4 (file 15 Q2) stand with this
file's corrections applied as follows:
- D-W3 item 3 reads: "A finished solve is adopted as the final only if `dirty_` is unchanged since the generation read
  before the scene snapshot (`ScenePipeline::decide`, 'The generation is read BEFORE the snapshot', L356 at HEAD); any
  parameter edit after that read discards it, as today (the two mid-drag checks before and after the solve, L543 / L556);
  edits that do not bump `dirty_` today do not." Item 4's per-generation cancel token compares against that same value.
- Line references are cited by function and comment as well as line (correction 2).
- Strongest objection, Seat 2: "no in-bounds option removes it without a scope reading of condition 4" (correction 3).
- "Decided for Maisara" wording: "Any edit made while that calculation runs stops it early and it is not used, as today".
- D-W4: the `/fix-plan` edit adding the automated record and the listening item to `docs/phases/phase-10-3.md` lands in
  this session as a tracked deliverable (correction D-W4 1).
