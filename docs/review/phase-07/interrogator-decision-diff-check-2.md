# Phase-07 applied decisions, DC fixes (f6dfc2f): interrogator diff check, round 2 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

DC-1 … DC-8 closed. Nothing WRONG or INCONSISTENT. Logic order setStateInformation → prepareToPlay → reset and the
AX34-fallback restore are consistent.

| id | passage | verdict | fix | severity |
|---|---|---|---|---|
| N1 | realtime setStateInformation quiesce/restart vs "builder stopped before prepare()" | IMPRECISE (threading assumption) | state that setStateInformation, prepareToPlay and reset() are not called concurrently with each other (not checkable, like the reset note) | minor |
| N2 | restore in the AX34 fallback | IMPRECISE | "Before `prepareToPlay` (or in the AX34 fallback)" | minor |
| N3 | test (d) realtime not deterministic as written | IMPRECISE | recorded generation is read before the scene snapshot; inject the change after the snapshot via a test hook | minor |
| N4 | §6 cites interrogator-decision-diff-check-1.md | IMPRECISE (file not found at the time of the check) | main session: false alarm: the file is tracked (`git ls-files docs/review/phase-07/` lists it; committed before f6dfc2f); closed | none |
| N5 | §6 row R3-1/R3-2 wording superseded by "handled" | IMPRECISE | add "(extended to bit-identical skips, DC-1)" | minor |
