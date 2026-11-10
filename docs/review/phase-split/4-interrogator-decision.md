# Interrogator, decision mode, round 1 — phase split (2026-11-10)

Saved by the orchestrator from the interrogator's report. Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d
(consulted only for D-PS2's audibility premise; plan-structure choices).

**Across all four decisions:**
- **No acceptance check (PRD MISREAD).** No "Decided for Maisara" lines showing each surviving option against the
  check's PRD ids (decider §1a line 112; README item 1). D-PS1 cites no PRD id; D-PS2 (FR-SIM-3) and D-PS4 (NFR-4)
  show no surviving option against them.
- **"Repaid when" names sub-phases not yet in §0** (08-4, 11-2, 13-1b, 13-2): valid only if the plan-editor lands
  exactly those names.

## Ledger
| decision | check | item | verdict | evidence | outcome |
|---|---|---|---|---|---|
| all | convening | Seat 8 not required | faithful | README row 8, persona §18; nothing reaches a producer before 13-4 | — |
| all | convening | Seat 9 not required | faithful, note | grouping is a rendering approximation; audibility with Seat 1; phase-08 L6 is labelled "(Seat 9)", Seat 1 rates L6 unaffected | — |
| D-PS1 | D1-L1 (code) | 08-2 reads t_mix,e and AX22 fallback, not E_b | CORRECT | `Engine.cpp` 124, 134–148, 246; early part (211) uses only `set.images`; `bandsAmplitude` only in the tail (252) | — |
| D-PS1 | D1-L2 | 05h leaves them unchanged | CORRECT | BUILD_PLAN line 137 AX37 (5.2); phase-05h line 41 | — |
| D-PS1 | map, ordering | cells, sums 8 vs 4 | faithful | — | — |
| D-PS1 | map (rc) | Seat 5's condition | partly met | Seat 5 asked "08-4 and the umbrella"; step 6 adds it to 08-4 only | correction |
| D-PS1 | claim | "(iv)'s re-listen (phase-05h line 286)" | IMPRECISE | line 286 is "an addition, not part of AX37 (5.3)"; (iv) only marks provisional (phase-05b2 line 403) | correction |
| D-PS1 | inference | step 4 rewords (i) on 08-2 | IMPRECISE | adds "same result as the omni build", not in (i) (phase-05b2 line 401): a change in substance | correction |
| D-PS2 | map, ordering | cells, (b+) | faithful | — | — |
| D-PS2 | D2-L1 | grouping only above order 3 | CORRECT (plan) | phase-08 line 157 | — |
| D-PS2 | claim | unsplit phase heard L-items after grouping decision | CORRECT (plan) | checklist answered at the PR, after AC12 | — |
| D-PS2 | claim | movement covered by Phase 10 AC1 | CORRECT | phase-10 line 88 | — |
| D-PS2 | claim | grouping's colour/envelopment effect | NOT CHECKABLE, not load-bearing | Zotter & Frank §7.1.2 (direction ↔ direct sound and first reflections, compact arrays; silent on colour); re-listen guards it | — |
| D-PS3 | map | cells, sums | faithful | — | — |
| D-PS3 | claim | "each deserve an M session (Seat 5…; Seat 6…)" | IMPRECISE | sizes come from map-11, not the seats; Seat 6 preferred (c) | correction |
| D-PS3 | bounds | (b) excluded because halves mix subjects | holds only with its test stated | (b) with A5 moved ties (a) at max 1, sum 4; exclusion holds only on a criterion-ownership test ((b)'s first half owns A1 (Seat 6) and A4/A6/A7 (Seat 5); (a)'s 11-1 owns only Seat 5 criteria); not stated | correction (Q5) |
| D-PS3 | inference | rests on FM-1 | re-answer FM-1 | — | Q2 |
| D-PS4 | map | Seat 1's "S10 in 13-1" 1/— missing | TENSION MISREAD, minor | applies to every option: (a+) S1 1/0; sums (a+) 6, (b)+K 9; winner unchanged | correction |
| D-PS4 | map, ordering | other cells; (c) out (Seat 5 later 3) | faithful | — | — |
| D-PS4 | claim | K1–K3 lead time not load-bearing | CORRECT | marking is a reallocation; moves no cell between (a+) and (b)+K | — |
| D-PS4 | step 4 | "not split further (S13, S10 own no criterion except C2)" | FALLS | Seat 3: C2 splits into "AQ10 met" (Seat 3) and the AX22 i₀ re-derivation (Seat 2); G2 allows clause splits; C2 has two sentences (phase-13 129–133); contradicts FM-1's split-where-possible | re-answer (Q1) |
| FM-1 | PRD proxy | "Answer: No." | INCONSISTENT | conclusion "split, not whole" answers the question as posed "Yes" | PRD MISREAD |
| FM-1 | PRD proxy | NFR-4 reading | PRD MISREAD | PRD line 108 lists platforms, says nothing on order | PRD MISREAD |
| FM-1 | PRD proxy | options vs cited ids | PRD MISREAD | FR-3D-8 and line 174 not shown against any option; (b) only against her words; (a)'s line omits 11-1's one-subject strain | PRD MISREAD |
| FM-1 | PRD proxy | Overview, FR-3D-5 quotes | CORRECT | PRD lines 9, 75 | — |

## Corrections from the convening round
1. 07c Raise in both sub-phases: **SURVIVES** (phase-07c §2 "first message and PR"; CLAUDE.md rule 2).
2. 12 AC2 share in 12-1: **SURVIVES WITH CORRECTIONS — drop 12-1's AC2 share** (a list of objects, not clauses: a
   split "along a factor", as rejected for 10-c1 (B)); 12-1 keeps AC5 alone.
3. 13-c4 Raise in 13-1 and 13-4: **SURVIVES** (phase-13 line 7).

## NOT A DECISION classifications
| item | verdict |
|---|---|
| size ruling (08-c5, 11-c2, 13-c3) | SURVIVES |
| 07c-c1, c2, c3 | SURVIVES |
| 08-c2 | SURVIVES (phase-08 lines 205–207) |
| 08-c4 | SURVIVES |
| 09-c1, 10-c2, 10-c3, 13-c2 | SURVIVES |
| 10-c1 | SURVIVES |
| 11-c3 | SURVIVES (follow-up) |

## Outcomes
- D-PS1: PRD MISREAD (acceptance check only); otherwise survives with corrections: (1) the "08-4 ran before 05h was
  `done`" note also in the umbrella; (2) step 6 says "phase-05h line 286's addition (outside AX37 (5.3))";
  (3) on 08-2 carry (i) verbatim with Seat 4's restatement beside it as a note.
- D-PS2: PRD MISREAD (acceptance check only); rest SURVIVES.
- D-PS3: PRD MISREAD (via FM-1 and acceptance check); corrections: state the criterion-ownership test; sizes from
  map-11.
- D-PS4: steps 1–3 SURVIVE WITH CORRECTIONS (S1 cell 1/0; sums 6 vs 9); step 4 FALLS; acceptance check PRD MISREAD.
- FM-1: PRD MISREAD (conclusion may stand once re-answered).

## Questions for the decider
1. Phase-13 C2 second sentence: is the AX22 i₀ re-derivation conditional ("if AX22 records 'cap limits accuracy'")?
   If so, is a Seat 2 sub-phase of S13 plus that sentence "too small to carry its own check"? Answer Seat 3's split.
2. FM-1: is the answer as posed "Yes"? Show (a), (b), (c) one line each against Overview, FR-3D-5, FR-3D-8, NFR-4 and
   line 174. Which words of NFR-4 does an order serve?
3. "Decided for Maisara" line for each of D-PS1..4, PRD ids, every surviving option shown against them.
4. D-PS1: (i) on 08-2 verbatim from phase-05b2 line 401, and the umbrella carries Seat 5's note?
5. D-PS3: what one-subject test excludes (b) but admits (a)'s 11-1, and does it admit 13-1 as decided?
