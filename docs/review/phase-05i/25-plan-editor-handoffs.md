# 25 — Plan-editor: phase 05i hand-offs given owners (Maisara 2026-11-11, "fix gaps then merge to main")

All five edits were SPECIFIED by the brief (values settled in AX38 4c, phase-05i §3.3 (v), decider files 9 and 13,
Seat 6 file 12). No acoustic or numeric choice made. Uncommitted.

## Applied

1. `docs/phases/phase-07c-1.md` condition 7: new paragraph "**The 07c re-pin**" (after conditions 9 and 12 land;
   growth-bound baselines, ±5 % flutter window, `kSolveWarn` and `solveRefMs` baselines, macOS trigger 2 172 ms
   re-derived from ≥ 3 in-window runs; one run PROVISIONAL, printed not asserted; never a red or out-of-window run as a
   baseline; a CHANGELOG reason). Acceptance criteria: new line "Condition 7, the 07c re-pin" (AX38 4c; D-Q5).
   `docs/phases/phase-07c-2.md` condition 3: sentence "The W_max raise changes the work: the solve bound's baselines
   (`solveRefMs`) are re-pinned with the new work and k (`kSolveWarn`) re-derived (D-Q5)." (decider file 9's D-Q5
   debt row states the raise changes the work, so the conditional applied.)
2. `docs/phases/phase-07c-1.md` condition 9: "Closes the AX38 4c register entries: Linux cube (also closed by the
   diffuse move, 28.9 s) and macOS cube (33.40 s …)" → macOS entry (33.40 s; three closing routes) and Windows entry
   (36.73 s; same routes; listed since run 42942694523, OVER30S on 05i's run of record on a slow runner); Linux
   already closed in phase 05i under (c). Rest unchanged.
3. `docs/phases/phase-13-1.md` scope 1, after "any memory budget is a decision for this phase (no number is set
   here).": condition 12 (f) process-peak hand-in and its remedy (concurrent-build limit; never an instance cap, a
   W_max cut or a range change) (D-G1, decider file 13).
4. `docs/phases/phase-07c-2.md` condition 3 (with item 1's sentence): `nsPerEval` invariance check across 07c's
   moves; if it moves, D-Q5 baselines re-pinned and Seats 2 and 3 convened (decider file 9 future-debt register).
5. `docs/phases/phase-11-3.md` scope 3: how "settling" is drawn (delay, hysteresis, scene-level aggregate) decided
   here (AX38 (iii) as amended by G1-C1; Seat 6, file 12).
6. `docs/BUILD_PLAN.md` §6: one change-log row (no value, threshold or golden changed).

## Held

None.

## DECISIONS NEEDED

None.

## Interpretations

- Item 1 paragraph placed as an indented continuation paragraph inside list item 7; the acceptance line placed
  after the condition 12 line (end of the list) and labelled "(AX38 4c; D-Q5)" since condition 7 has no umbrella A-id
  of its own.
- `solveRefMs` named beside `kSolveWarn` as the field holding the baselines (decider file 9 test-code spec).
- Item 2: "Linux cube … 28.9 s" parenthetical dropped with the Linux entry, per the brief's replacement text.
- §6 row added following the file's convention for wording-only plan edits.
