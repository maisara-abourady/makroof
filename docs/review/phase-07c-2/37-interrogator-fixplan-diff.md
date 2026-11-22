# 37 — Interrogator: diff check of the split-marking /fix-plan edit (ff1f414)

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Document mode, on `docs/phases/phase-07c-2.md` and
`docs/phases/phase-07c-2b.md` (branch review findings M1, m4). All checked content is software or bookkeeping; no
corpus rating needed.

**Verdict: CLEAN on (1)–(4), two minor findings (wording, nothing acoustic).**

1. Every moved note resolves to the 07c-2b item it names: scope 3 → 2b scopes 6, 7; scope 8 → 2b scope 9; scope 9
   (M3, seal, ABX run → 2b scopes 2, 3; class (c), load fallback, FM-B2 → 2b scope 4; interim stream check incl.
   "No shared prefix" → 2b scope 5; E_prec and Seat 2's prefix check → 2b scope 10); criteria 1–3 → 2b criteria 1–3;
   criterion 4's M7/M7b/TSan part → 2b criterion 4; listening items 1–2 → 2b listening items.
2. No item 07c-2b takes over is left unmarked (2b's O5 and O12 come from text now marked). Timing and Raise item 1
   are shared, correctly unmarked.
3. Nothing ticked or softened; every number byte-unchanged; 1–34 → 1–36 is correct (files 35, 36 exist).
4. The conditional criterion-4 note agrees in 07c-2 (L166–167, L201–203), 2b (scope 1, criterion 4) and
   BUILD_PLAN §0.

Minor findings, both applied by the plan-editor in the follow-up commit:

- M1: the contractor focus "the W_max re-derivation from the background budget (phase-07c F6)" (07c-2 L215) had
  no moved note though scope 3 moved. Applied: moved note added.
- M2: scope 9's "The ABX runs first" still said the ABXs "are run in this phase". Applied: "are run in
  phase-07c-2b (its scopes 2 and 3)", per the 07c-1 precedent.
