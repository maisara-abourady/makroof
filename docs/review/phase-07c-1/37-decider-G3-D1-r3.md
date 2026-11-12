# 37 — Decider: G3 / D1 decision round 3 (answer to interrogator file 36): DECISION O8 stands, debt register revised

2026-11-12, corpus c1b171f. Cells and sums as file 35 (O8 max 1, sum 11; full row with seats 4, 6, 8 at 0/0: S1 1/1, S2
1/1, S3 0/1, S4 0/0, S5 1/1, S6 0/0, S7 1/1, S8 0/0, S9 1/1). Row 44: S1's O7 cell 1/1 is Seat 1's own rating (not rc).
Row 45: S7's O8 cell 1/1 rc from its O4 clause, O5 condition "source x or drop" met.

Q1: Phase 10 has no EDT/BRAS item; the S1/S9 debt is repaid by a **phase-05d item added now via /fix-plan** (text below).
Q5: keep **0.217 with "1.9 rounded"** (K = 0.161: ratio 1.908, d 0.2155; K = 0.16: 1.915, d 0.214); no file-23 case lies
in [0.214, 0.217) (nearest 0.213, 0.221).

Future-debt register (final):
| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S1 | EDT asserted at d < 0.5, not "r ≫ r_c"; K7 closed with no number | one constant: AX47 (b) "d < 0.5" via /fix-plan and test_interim.cpp's 0.5 gate (at 0.217: 5 of 40, layout 5) | every run prints the d < 0.217 subset; phase-05d item 7 (d_dir per measured Arni/dEchorate/BRAS position) | phase-05d's d_dir-binned EDT table and its loop's ruling (0.5 or 0.217) |
| S9 | same; CR3 asserted below ISO 3382-2 d_min ≈ 1.9 r_c | as S1 | as S1 (CR3 positions included) | as S1 |
| S2 | the prefix check never a measured-vs-simulated criterion | remove AX47 (b)'s prefix clause via /fix-plan and the prefix block (−18.27 dB) | phase-05d scopes 3, 6; BRAS nightly | 05d's item says so; 05d/nightly stay metric-only (AQ9); checked when 05d is done |
| S3 | prefix check guards the A4 set only | same clause and block | 07c-2; 08, 09 | 07c-2 keeps AX47 (b) incl. the prefix check green on its stage-1 sources; 08/09 unrepaid (follow-up in this PR) |
| S5 | cube EDT margin 1.47 points | nothing (5 % and 0.5 stay; a red is a regression) | this branch's three-OS CI; later tail changes | three-OS worst EDT and prefix figures in the PR; green after the next tail change |
| S7 | wording "EDT within 5 % on N cases with d < 0.5 of M"; never "within jnd" | AX47 (b)'s record sentence and the summary printf | phase-13-2 accuracy wording (AX43) | 13-2's wording review |

Final texts:
1. AX47 (b) replacement — as file 35 with "for Phase 10" → "for phase-05d's ruling on the d constant" and the d < 0.217
   definition "(1/(1 + 1.9²), ISO 3382-2's d_min ≈ 1.9 r_c in diffuse-field terms, 1.9 rounded)".
2. Evidence append — as file 35 plus "decider files 33, 35, 37; interrogator files 22, 34, 36 … The d constant (0.5 vs
   0.217) is ruled in phase-05d (scope item added by D1)."
3. §6 row — as file 35 plus "phase-05d gains scope item 7 (d_dir per measured position; rules the constant 0.5 vs 0.217)".
4. phase-05d scope item 7 (and AX47 in "Read first"): "**AX47 (b) direct-fraction constant** (D1, phase-07c-1 G3; decider
   files 35, 37). Reported, not gated; tools only. For every measured position used in scope 3 (Arni, dEchorate) and every
   BRAS position in the nightly scenes, at 500 Hz and 1 kHz, print the direct fraction d_dir of the measured IR (energy
   within ±5 ms of the band peak over the band's total, as AX47 (b) defines d; named d_dir here to keep it apart from the
   matched-pair d), the measured EDT and the sim–meas EDT error in jnd (5 %, Vorländer Table 6.1). Table it by bin:
   d_dir < 0.217, 0.217 ≤ d_dir < 0.5, d_dir ≥ 0.5, with the count, mean and SE of the error per bin and room. The session
   raises the AX47 (b) constant (0.5 or 0.217) as a decision-loop item on that table; a change goes through /fix-plan with a
   §6 row and touches AX47 (b) and tests/unit/test_interim.cpp only. The AX47 (b) prefix check is a provisional-against-
   exact test and is never applied to a measured IR here or in the nightly baseline."
5. Test comment l.452: "D1 / O8 (decider files 35, 37): d < 0.217 (1/(1 + 1.9^2), ISO 3382-2's d_min ~ 1.9 r_c in
   diffuse-field terms, 1.9 rounded) is printed for phase-05d's ruling on the AX47 (b) d constant; nothing is asserted on it."
6. Decided for Maisara: D1 — the interim-tail test checks EDT only where the reference IR is not direct-dominated
   (d < 0.5) and adds a check that the interim tail's opening equals the final tail's, up to the allowed 1 dB step, on the
   shipped IR. PRD check: NFR-1 (thresholds unchanged; d decides where a self-comparison applies), NFR-8 and FR-SIM-2 (no
   scene logic; test-side case choice on a measured property of the reference IR); AX5 a plan default, holds. O2 NFR-1
   strained; O3 NFR-1 weaker evidence; O4 NFR-1 narrower, FR-SIM-2 strained in spirit; O5 NFR-1 with an unsourced threshold;
   O7 all hold, one check fewer; O8 all hold plus the shipped-IR check. Who gave most: Seats 1 and 9 (d < 0.5 instead of
   r ≫ r_c), repaid by the printed d < 0.217 subset and phase-05d item 7; Seat 2 accepts the prefix check never used on
   measured IRs. Amends none of her decisions. NEEDS MAISARA: none.
