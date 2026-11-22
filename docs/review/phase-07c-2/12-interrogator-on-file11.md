<!-- Saved by the orchestrator from the interrogator's report, 2026-11-22. -->

Interrogator on `docs/review/phase-07c-2/11-decider-decision-r3.md` (decision mode, round 3). Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

# Interrogator on file 11: D-W3, FM-W3a, D-W2 final, D-W1 waiting list

## Outcome per item

FM-W3a fails, and D-W3 cannot stand without it. D-W2 and the D-W1 waiting list survive with corrections.

| item | outcome | why, in one line |
|---|---|---|
| **FM-W3a** | **FAILS: PRD MISREAD (two readings)**; it goes to Maisara | FR-SIM-6's "follow" and its "without audible artifacts" point opposite ways on tail steps during motion. NFR-3 sends exactly this tension to the Expert. AQ4 does not rank the two clauses: it is a plan default, and it already stood beside condition 4 when she accepted condition 4. The deciding premise, that small in-motion steps are less audible than one end step, has no evidence (NOT CHECKABLE). |
| **D-W3** | **FAILS as applied (step 1, bounds)** while FM-W3a does not survive | Item 4's exception, and possibly item 3, break her standing condition 4 ("exactly one step per solve and never mid-drag"). Apart from that the map, composition, veto drop and code facts hold, with corrections 1–7. If she accepts the amendment, D-W3 survives with those corrections. |
| **D-W2 final** | **SURVIVES WITH CORRECTIONS** (2) | The map is faithful, the pre-fixed outcome is applied correctly, and the speech choice matches the dossier. |
| **D-W1 waiting list** | **SURVIVES WITH CORRECTIONS** (2) | — |

### FM-W3a: why it is not within the decider's remit as answered

- **What the README allows.** The decider may amend her recorded decisions only "when the PRD calls for it" (README item 1). It is not case (b) (no PRD edit) or case (c) (no 3 is overridden).
- **What the PRD says.** FR-SIM-6: "Follow automated listener and source movement without audible artifacts." The FM's own veto reading ("no tail-level change while moving") is a faithful reading of the second clause. Recency adoption is the first clause.
  - NFR-3 (PRD L107) ends "This tension goes to the Expert". Q4 is owned by the Expert, and AQ4 is only its default.
  - AQ4 ("rebuild the IR on a background thread … crossfading … over 30 ms") was in force when she accepted condition 4, which carved the diffuse level out of it. So AQ4 does not newly call for undoing that carve-out.
- **What the premise lacks.** Choosing between the two readings needs to know whether recency steps (recorded, not bounded; AX47 Scope excludes B1′ steps) are audible artifacts.
  - No corpus passage addresses this. M7b records only step sizes, and Seat 1 has not answered the hand-offs from Seats 6 and 8 on in-motion audibility.
  - This is a research or listening gap, not a fact.
- **Board support is misread.** "Seats 1, 6, 8 now ask for recency adoption" misreads Seat 8: "an anti-starvation rule … (not required)". The README also says an answer must not rest on the board alone.
- **Routing.** Her own decision settles the point the other way, and the PRD does not rank the clauses. So the decider cannot apply the amendment.
  - Either it goes to her (NEEDS MAISARA, nearest case (a): the PRD supports two readings on this point), or the decider keeps condition 4 and redoes the D-W3 ordering with the exception out of bounds.
  - Which of the two is the decider's choice, not mine.

### D-W3 corrections (they apply if the amendment is accepted)

1. **Mark every H-2\* cell "(read from conditions)", not only S3's.** H-2\* is a composed variant (decider.md §4).
   - The readings hold for S1 (H-2 recency / H-1 progress conditions), S2 (rule 1 plus bit-identity), S4 ("completion guarantee … so the stale level is bounded", so 1/0), S5 (all six H-2 conditions and H-1 (i)–(iii) adopted), S6 (its H-1 condition "at least one solve completes every ~3 s" plus decoupling), S7 ("first work of 07c-2b … TSan … gates", so 1/0), S8 (0/1) and S9 (0/0).
2. **The S3 cell does not follow from Seat 3's stated conditions.** Seat 3's (b) is "A doomed solve stops at its next `run.stop` once its generation is stale". The 3 s exception lets one doomed solve run on, so put the cell to Seat 3.
   - The winner does not change even if Seat 3 says 1/2. Every option then has a maximum of 2, and on sums H-2\* has 13, H-2 as stated 19, H-1 21 and H-0 29.
3. **H-3's S9 cell is 0/0 (NOT MY MATTER), not "—".** The H-3 veto drop on Seat 3's "2 / 3" is correctly applied.
4. **Code line reference.** The single-committer comment is at L582 at HEAD; L566 is the `catch`.
   - There are two mid-drag discards: L542 (before the solve starts) and L555 (after it).
   - "No solve is ever adopted" holds under the condition that edits arrive faster than the ISM build plus the solve.
5. **D3-L3 is a local Linux projection, not a fact,** until M7 on CI is in.
6. **The PRD acceptance check leaves out a survivor.** H-2 as stated has no 3 and must be shown against FR-SIM-6 and NFR-3.
7. **Scope and plain wording.**
   - Adding H-2\* to 07c-2 or 07c-2b is a phase-file scope change, so it goes through `/fix-plan`, not only the BUILD_PLAN §0 line.
   - The "Decided for Maisara" line "catches up about every 3 s" should read "at most one held-level step per ≥ 3 s, plus up to one solve".
   - The register's S1 undo ("change the rule") understates Seat 1's "a phase of rework if M7b shows starvation".

### D-W2 corrections

1. **Noise floor.** Write "SNR about 46 dB re the average active speech level (R35 App. A)", not "the 46 dB noise floor".
2. **Step placement.**
   - "First half of the pause" does not guarantee "≥ 20 dB above the floor". At 60 dB per T the tail is 30 dB down at 0.5 T. That leaves only 16 dB above a floor 46 dB below the speech level (taking the tail onset at the speech level).
   - The condition holds for an onset within 26/60 ≈ 0.43 T of the speech end. Pre-register the measured criterion itself (tail level minus floor at the onset ≥ 20 dB), or the 0.43 T bound (Seat 9's arithmetic, ledger row W2-3).

### D-W1 waiting-list corrections

1. **U2 attribution.** Only Seats 2 and 8 ask for print-only.
   - Seat 5 rates "U2 as a term … 1/1" as "a check at derivation time … never an asserted CI gate".
   - Seat 7 accepts it as a non-binding ceiling on the condition "U2 may bind only above m\*".
   - Record their own terms, not "agreed print-only (2, 5, 7, 8)".
2. **The W-C2 win is conditional.** "W-C2 at m = 6 (or 7) wins" holds only on Seat 5's condition that D-W3 makes the hold independent of W. If FM-W3a fails, D-W3 has to be re-ordered first.

---

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question |
|---|---|---|---|---|---|---|
| D-W3 | convening | nine rows | faithful | file 8 §5 table; S9 declined only H-3 | — | — |
| D-W3 | map | H-0, H-1, H-2 as stated, H-3 rows | faithful | 10-seat1…9 tables match cell for cell | — | — |
| D-W3 | map | H-3 / S9 "—" | minor slip | seat 9: "NOT MY MATTER", so 0/0 | correction 3 | — |
| D-W3 | map | H-2\* cells other than S3 unmarked | procedural slip; readings hold | decider.md §4 "(read from conditions)" | correction 1 | — |
| D-W3 | map | H-2\* / S3 1/1 | TENSION MISREAD (not from stated conditions) | 10-seat3 §3 (b) "stops at its next `run.stop`"; the exception contradicts it | put to Seat 3; winner unchanged | Q3 |
| D-W3 | map | "progress and recency rule asked for by Seats 1, 4, 6 and 8" | IMPRECISE | 10-seat8: anti-starvation "(not required)" | correction | — |
| D-W3 | ordering | one composed variant | correct | file 11 §Working step 4 | — | — |
| D-W3 | ordering | H-3 dropped on Seat 3's 3 | correct | 10-seat3 "2 / 3 … trades a sourced yardstick for convenience" | — | — |
| D-W3 | ordering | "H-1 with progress re-holds the ISM" | CORRECT (from the code) | one builder thread runs the solve inline (`IrBuilderThread.h` L5; `ScenePipeline.cpp` L552–553) | — | — |
| D-W3 | ordering | bounds: H-2\* item 4 against condition 4 | out of bounds unless FM-W3a survives | phase-05b2 file 47 L119 "exactly one step per solve and never mid-drag" | FAILS as applied | Q1 |
| D-W3 | debt | six later-1 rows (S1, S2, S3, S5, S6, S8) | complete; S1 undo understated | 10-seat1 "a phase of rework" | correction 7 | — |
| D-W3 | D3-L1 | ISM waits behind the solve; mid-drag discards | CORRECT | from the code: L538–540 commit; L542 and L555 discards; L552–553 inline solve | — | — |
| D-W3 | D3-L1 | single committer "L566" | IMPRECISE (line) | comment at L582; L566 is the `catch` | correction 4 | — |
| D-W3 | D3-L2 | Table 15.1 700 ms specular / 3 s specular + scattering | CORRECT (conditions: VR filter update, by extension) | Vorländer §15.3, Table 15.1 | — | — |
| D-W3 | D3-L3 | hold 590 / 810 / 813 ms; H-0 caps W at 5 | IMPRECISE (local projection) | fact sheet part 3, local Linux, pool 4; M7 pending | correction 5 | — |
| D-W3 | hidden premise | problem-key final adoption during a drag that leaves the `DiffuseProblem` unchanged | adopts a final mid-drag; inside FM-W3a's wording but not reasoned | FM-W3a text "(problem key)" | — | Q2 |
| D-W3 | PRD proxy | acceptance check omits H-2 as stated | PRD MISREAD (survivor not shown) | README "each surviving option is shown against the check's ids" | correction 6 | Q4 |
| FM-W3a | PRD proxy | FR-SIM-6 read as calling for recency adoption | PRD MISREAD (two readings) | PRD L89; FM's own veto line gives the second reading | goes to Maisara | Q1 |
| FM-W3a | PRD proxy | NFR-3 and AQ4 as the tie-breaker | PRD MISREAD | PRD L107 "This tension goes to the Expert"; AQ4 (BUILD_PLAN L111) cites no date of hers and coexisted with condition 4 | goes to Maisara | Q1 |
| FM-W3a | hidden premise | in-motion AQ4 tail steps less audible than one end step | NOT CHECKABLE (load-bearing) | no corpus passage; M7b records sizes only; Seat 1 has not answered | UNDERINFORMED | Q1 |
| FM-W3a | form | AMENDS line | present and correct in form | `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` | — | — |
| FM-W3a | form | "Seats 1, 6, 8 now ask for recency" | IMPRECISE (S8) | 10-seat8 "(not required)" | correction | — |
| D-W2 | map | X-5 row; X-3 (Seat 6's form) S1 2/2 | faithful | 10-seat6 "can live with, 1 / 1"; 10-seat1 "2 now / 2 later" | X-5 wins at step 3 | — |
| D-W2 | conditions | Seat 6's three conditions, Seat 1's anchor rule, Seat 7 local-only, Seat 9's residuals | adopted | 10-seat6 §(a); 10-seat7 (c); 10-seat9 (b) | — | — |
| D-W2 | claim | TSP anechoic, 15 cm, Simplified BSD, no consent, 46 dB SNR | CORRECT (dossier, read) | 7-researcher R35 | — | — |
| D-W2 | W2-1 | "46 dB noise floor" | IMPRECISE | R35 App. A: SNR about 46 dB re active speech level | correction 1 | — |
| D-W2 | W2-2 | "first half of the pause" taken as "≥ 20 dB above the floor" | INCONSISTENT | 60 dB per T: 0.5 T gives 30 dB down, 16 dB above the floor; the bound is 0.43 T | correction 2 | Q5 |
| D-W2 | W2-3 | Seat 9: tail falls 46 dB in 0.77 T | CORRECT (computed) | 46/60 = 0.767 | — | — |
| D-W1 | list | U2 "print-only (2, 5, 7, 8)" | IMPRECISE | 10-seat5 "a check at derivation time"; 10-seat7 "may bind only above m\*" | correction 1 | — |
| D-W1 | list | "W-C2 at m = 6 (or 7) wins" | conditional | 10-seat5: W-C2 1/1 only if D-W3 makes the hold independent of W | correction 2 | Q4 |
| D-W1 | list | K-b veto cells, K-a cells, M1/M3–M6/M8/M9, three-OS SE print | carried correctly | file 8 corrections 6, 7, 10 | — | — |

## Questions for the decider's rebuttal round

1. **FM-W3a.** Which PRD passage ranks FR-SIM-6's "follow" above its "without audible artifacts" for tail-level steps during motion, given that NFR-3 sends this tension to the Expert and that AQ4 already stood when she accepted condition 4? What evidence shows small in-motion AQ4 steps to be less audible than the single end step? If there is none, will you send it to her, or keep condition 4 and redo D-W3's ordering with the item 4 exception out of bounds?
2. **Problem-key final adoption.** When a drag changes a parameter that leaves the `DiffuseProblem` unchanged, H-2\* item 3 adopts a final mid-drag. Is that inside the amendment, and where is it reasoned against FR-SIM-6?
3. **Seat 3's cell.** Put the 3 s exception to Seat 3's condition (b) to Seat 3, and record its rating of H-2\*.
4. **Acceptance and the re-order.** Show H-2 as stated against FR-SIM-6 and NFR-3. If FM-W3a does not survive, what is the D-W3 ordering, and does Seat 5's W-C2 condition still hold for D-W1?
5. **TSP step placement.** State the pre-registered onset rule as the measured "tail ≥ floor + 20 dB at onset" condition or its 0.43 T bound, so that it does not conflict with "first half of the pause".

Files examined:
- `/home/user/makroof/docs/review/phase-07c-2/11-decider-decision-r3.md`
- `/home/user/makroof/docs/review/phase-07c-2/8-decider-rebuttal-r2.md`
- `/home/user/makroof/docs/review/phase-07c-2/10-seat1.md` … `10-seat9.md`
- `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part3-m2.md`
- `/home/user/makroof/docs/review/phase-07c-2/7-researcher-RQ-W2-6-7-9.md`
- `/home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` (L114–125)
- `/home/user/makroof/docs/BUILD_PLAN.md` (AQ4, L111)
- `/home/user/makroof/docs/PRD.md` (L89, L101–107)
- `/home/user/makroof/docs/board/README.md` (L76–147)
- `/home/user/makroof/src/plugin/core/ScenePipeline.cpp` (L486–582)
- `/home/user/makroof/src/plugin/core/IrBuilderThread.h`
- `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (Table 15.1, L3959–3966)
