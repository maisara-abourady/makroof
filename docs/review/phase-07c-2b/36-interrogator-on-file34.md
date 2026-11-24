# Interrogator on decider file 34 (I7, round 3, final)

**Verdict: SURVIVES WITH CORRECTIONS, conditional on Seat 7's answer in file 35.** The decision itself already says which option applies under either answer. The arithmetic, the n = 2 claim and the pair-search logic hold. Two corrections are needed to the pre-registration text, and one citation is wrong.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:**
- File 34.
- My file 31.
- Seat 1: files 29 and 32. Seat 7: file 33. Seats 5 and 6: 1-seat5 and 1-seat6.
- Phase-07c-2 file 13, items 3, 4, 8 and 10.

## Map and ordering
- **The (1)+remedy row is faithful.**
  - S1 1/1: file 32, with conditions 1–5.
  - S7 0/1: file 33, "Now 0, later 1".
  - S5 and S6 1/1. Seat 5: "Unsplit, at most 3 families: prefer", 1/1, with V2–V4 at 3 families and 0.147. Seat 6's table: 3 families, 0.147, unsplit 1/1. So n = 3 is inside their ratings, as R3-L2 says.
- **Seat 1's (3) cell 1/1 is faithful, and an upper bound.**
  - File 29 rated (3) at 1/1 because it "reopens M3-T and repeats the measurement on all 16 scenes" and recovers about 4 dB "only if" the new pair gives earlier boundaries.
  - The variant decided here re-measures only on the scene in use, and accepts a pair only if it satisfies item 7 unrestricted. Both of Seat 1's reasons are smaller under this variant, so carrying 1/1 is conservative.
- **Citation, IMPRECISE.** The "(1) with no feasible remedy, later 2" cell cites file 32. Its source is file 29: "Without condition 4, I rate it later 2." File 32's own "later 2" covers a different case, a remedy designed after E's nulls.
- **Seat 7's (3) cell 0/0 "not required" is not a rating Seat 7 gave. TENSION MISREAD, pending file 35.**
  - The decider rests it on file 25's reasons for not convening Seats 2–9. But file 25 judged those seats on option (1), where the signal is unchanged. It excluded (3) as a signal change and never assessed Seat 7's hours under (3).
  - A new pair changes the speech stimulus length, hence K6 and the sitting plan. Seat 7's row covers that.
- **The cell decides the winner.**
  - Sums: (3) = 2 + 2 + 2 + 0 = 6; (1)+remedy = 2 + 2 + 2 + 1 = 7. CORRECT as computed.
  - If Seat 7 rates (3) at 1 or more in any column, the sums tie at 7.
  - Reversibility is Seat 1's stated reason for (1). It then breaks the tie, and (1)+remedy is chosen.
- **The decision's reversal clause already handles both answers**, so no further board round is needed:
  - **Seat 7 gives 0/0:** (3) with the pair search stands.
  - **Seat 7 gives 1 or more:** apply (1)+remedy, with Seat 1's conditions 1–5 (file 32) and Seat 7's conditions 1–5 (file 33). The union becomes n = 3, ≤ 0.147.
- The sum ordering correctly comes before reversibility (decider §5, steps 5–6).

## M3-T amendment and the pair-search rule
- **Amending M3-T is in bounds.**
  - M3-T is a board decision, not one of Maisara's.
  - Seat 1 accepted the pair on condition that "the pre-registration states the selection grounds". The rule states them: measured assertions only, before any blind result, never chosen by listening.
  - That matches Seat 1's file-32 condition 2 for choosing a pair.
- **The order is defined:** TSP index order, consecutive pairs, every pair tried recorded, the first qualifying pair taken.
- **The logic holds.** The remedy pair's criteria (file 32 condition 2) are the same as the primary pair's:
  - if a qualifying pair exists, it becomes the primary, so a remedy family never runs;
  - if none exists, no remedy can be built.
- **Correction 1: the criteria list in the exact text is incomplete. INCONSISTENT.**
  - The outcome says the pair must pass "every pre-seal check on E".
  - The exact run-sheet text lists only: the earliest boundary meets (c) under (a) and (b); at least 34 passing; form (b); B and E nulls; the M3-G silences.
  - It omits checks that also depend on the programme:
    - item 10's peak ≤ −1 dBFS;
    - item 6's mid-fade companions (i)–(iii) and the W-a windows;
    - Q5's realised window and replacement rate, recorded;
    - the per-stimulus item-7 assertion on every drawn onset.
  - Pre-registration text must be exact. Add these, or write "every pre-seal assertion of §1 and §3 item 3" and keep the named criteria as a subset.
- **Correction 2: the criteria depend on the scene in use.** A new pair is measured only on the scene in use, so a switch to fallback D or B needs the search or the re-measure repeated there. The debt row says this; the exact text should say it too ("on the scene in use; re-run on a fallback").

## Fallback branch and debt
- **Fallback branch: CORRECT.**
  - It uses MA01_01 + MA01_02 with restriction (c).
  - The figures are those I checked in file 31: floor 2.685 s, first candidate boundary 2.688 s, window about [0.134, 0.380]·T_heard, about 60 passing.
  - The floor is pinned only in this branch.
  - The record wording follows Seat 1's condition 3.
- **Seat 1's debt is recorded honestly.**
  - With no remedy, Seat 1's later 2 stands. That is not a veto, and it is recorded.
  - "Repaid when" now includes a detection by either chain, which was my file 31 correction.
- "No remedy speech family is pre-registered: a non-detection is never a reason to run another speech block (file 13 item 4)" is consistent with items 3 and 4.

## n = 2
- In either branch of the decided rule, the families are E omni at 07c-2b and E binaural at 08-3.
- Union ≤ 2 × 0.049 = 0.098. AX47's α sentence (D-M3i) is unchanged. **CORRECT.**
- R3-L1: if a null-triggered rerun were pooled into E's family, its error rate would be about 0.0384 + 2 × 0.0106 ≈ 0.060. CORRECT, as in file 31.
- If file 35 returns 1 or more, the reversal gives n = 3 (≤ 0.147). That is inside Seats 5 and 6's ratings, confirmed above.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| I7 r3 | map | (1)+remedy: S1 1/1, S5 1/1, S6 1/1, S7 0/1 | faithful | files 32, 33; 1-seat5, 1-seat6 | — | — |
| I7 r3 | map | S1 on (3): 1/1 | faithful (upper bound for the narrower variant) | file 29 | — | — |
| I7 r3 | map | S7 on (3): 0/0 "not required" | TENSION MISREAD: file 25's reasons do not cover (3)'s hours | file 25; Seat 7's row | pending file 35 | apply the reversal per Seat 7's answer |
| I7 r3 | ordering | sums 6 vs 7; reversibility only after the sum | CORRECT as computed; the winner depends on Seat 7's (3) cell | decider §5 | conditional | — |
| I7 r3 | citation | fallback "later 2" attributed to file 32 | IMPRECISE (source is file 29) | files 29, 32 | SWC | — |
| I7 r3 | M3-T | amended by board decision; selection grounds stated | in bounds, faithful | 9-seat1-l4; file 32 condition 2 | — | — |
| I7 r3 | pre-reg text | pair criteria omit peak, mid-fade companions, Q5 record, per-onset item 7 | INCONSISTENT with "every pre-seal check" | file 13 items 6, 10; run sheet §1, §3 | SWC | complete the list in the exact text |
| I7 r3 | pre-reg text | criteria only on the scene in use | IMPRECISE: a fallback scene needs the search or re-measure again | debt row | SWC | state it in the text |
| I7 r3 | fallback | restriction, floor, window, about 60, record wording; Seat 1 later 2 as debt | CORRECT | files 29, 30, 31 | — | — |
| I7 r3 | n = 2 | union ≤ 0.098; no third family | CORRECT | D-M3i; file 13 items 3, 4 | — | — |

## Orchestrator note (2026-11-24)

Seat 7 answered in file 35: option (3) 0/0 (prefer). The TENSION MISREAD row is therefore resolved in the decided direction: (3) with the pre-registered pair search stands (sum 6 < 7), n = 2. The corrections above (complete criteria list, scene-in-use clause, file-29 citation) are applied in the run sheet by the plan-editor.
