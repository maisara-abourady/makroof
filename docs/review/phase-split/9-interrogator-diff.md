# Interrogator, finished-diff check (/fix-plan step 5) — phase split (2026-11-10)

Saved by the orchestrator from the interrogator's report. Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (plan
text only; no corpus passage load-bearing). The interrogator had no shell in this run: it read the 19 relevant
sub-phase files, the phase-13 umbrella and BUILD_PLAN §0/§6 at HEAD and compared against the originals' passages it had
read in round 1; full sentence coverage rests on `8-coverage-check.md` (run by the orchestrator with a shell).

| item | verdict | evidence |
|---|---|---|
| 1 Coverage script | CORRECT as reported (not re-run) | residuals are deliberate; spot checks verbatim: phase-08 AC3, AC6–AC8, AC10–AC13, scope 5a, 8–10, L0–L7; phase-13 R0–R4, C2–C5 |
| 1 Duplication | CORRECT | only decided or shared duplicates (13 Raise in 13-1/13-5; 07c §2.1 in both; C1; AC12 sentence 1); AC2 only in 12-2 |
| 2 Numbers, AX/AQ | CORRECT | sampled values unchanged; AQ10 gained only the "[now `13-1b` …]" cross-reference, recorded in §6 |
| 2 C2 split (13-1 / 13-2) | CORRECT | verbatim vs phase-13 lines 129–133 |
| 2 C3 split (13-4 / 13-3) | CORRECT | "Robustness test: cross-architecture ≤ −100 dBFS residual." adds only the needed subject (G2) |
| 2 AC12 split (08-2/08-3/08-4) | CORRECT | sentence 1 shared, 2 in 08-3, 3–4 in 08-4, verbatim |
| 2 Scope 5a split (08-2/08-4) | CORRECT | matches D-PS2 steps 1–2 |
| 3 D-PS1 | CORRECT | instructions 1–6 at 08-1 l.199, 08-2 l.107–113, 08-3 l.113–115, 08-4 l.94, 97–102, umbrella l.132–136 |
| 3 D-PS2 | CORRECT | 08-4 l.24, 103–108; 08-3 l.116; CF6, R3 in 08-4 |
| 3 D-PS3, FM-1 | CORRECT | order 11-1→11-3; Seat 6 (i) at 11-1 l.68–70, (ii) at l.21–25; Q5 note l.72 |
| 3 D-PS4 + Addendum | CORRECT | five sub-phases; instructions 2–6 in final wording; Seat 2 hand-off 1 in 13-2 header |
| 3 Convening resolutions | CORRECT | 08-c2, 08-c4, 13-c2, 13-c4, corrections 1–3 applied; 11-c3 a follow-up |
| 3 Debt-register ids | CORRECT | §0 rows 08-4, 11-2, 13-2, 13-3; `13-1b` defined as the G3 remainder |
| 4a 13-1 L, 13-2 M | CORRECT (harmless) | 13-1 L from map-13 (13-c3 NOT A DECISION); no criterion or order depends on a size label |
| 4b 12-1 note "'Phase 12 is done' reads as 12-1 `done`" | WRONG (minor) | no decision sets it; contradicts G3's default → **delete 12-1 lines 71–72** |
| 4c BUILD_PLAN §0 row 13-2 "(… scope 13, below)" | WRONG (trivial) | "below" points at nothing → **"in phase-13-2.md"** |
| 4d 12-2 "supporting: Seat 6" | CORRECT (harmless) | descriptive, owns no criterion |
| 4e 07c-2 beta-prerequisite sentence | CORRECT | restates the umbrella header |

**Verdict:** CORRECT with two fixes (4b, 4c), neither touching a criterion, threshold or decision.

**Fixes applied** (plan-editor, 2026-11-10): 4b — the 2-line bullet deleted from phase-12-1.md "Notes from the split";
4c — BUILD_PLAN §0 row 13-2 now reads "S13 = phase-13 scope 13, in phase-13-2.md)". Diff passes step 5.
