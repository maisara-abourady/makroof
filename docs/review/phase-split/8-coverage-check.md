# Orchestrator's independent coverage check (2026-11-10)

Script: every line-level sentence (≥ 30 chars, list markers stripped) of each original phase file at b4b58a8 is
searched, normalised, in the union of the umbrella and its sub-phase files; a sentence not found whole counts as
covered if all its clause fragments (split at , ; : ( ) — and/or) are found.

| phase | original units | not found whole or by clauses |
|---|---|---|
| 07c | 123 | 2 |
| 08 | 355 | 4 |
| 10 | 159 | 1 |
| 11 | 88 | 0 |
| 12 | 85 | 0 |
| 13 | 162 | 1 |

The 8 residuals, checked by hand:
- size lines (07c "split into phase-07d.md …", 08 "Size: L (plan for two sessions; …"): intentionally replaced by
  "split into …" per the apply brief; the old size line is quoted in each umbrella's coverage table;
- 08 "Session 1: HRTF data and lookup", "Session 2: BRIR assembly and tail": headings of the original's session plan,
  superseded by the sub-phase table;
- 07c "the W_max re-derivation from the background budget.": present in phase-07c-2.md line 71 (line-wrap split);
- 08 "checklist in the PR with the hrtfId and set identity string.": present in 08-2/08-3 DoD and umbrella line 143;
- 10 scope 7 "… with the sustained-tone input and": split at its own clause per 10-c2 (10-2 line 50; clause 2 in 10-3);
- 13 C3 "Robustness tests above pass, including cross-architecture ≤ −100 dBFS residual.": split into its clauses per
  map-13 / D-PS4 (13-4 line 45, 13-3 line 54).

No content lost.
