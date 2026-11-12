# 43 — Interrogator: diff check of plan commits d41700c, 8790106, f780c37 (steward round-5 gap G4)

2026-11-12, corpus c1b171f. Read the current text of BUILD_PLAN §0 (07c, 07c-1, 07c-1b, 07d), AX18, AX47, AX48, AX49, AQ10,
§6 rows; phase-07c-1 A2 and Definition of done; phase-07c-1b; phase-07c sub-phase table; against file 41, the review
(scratchpad) and the code (ScenePipeline.cpp l.436–451, test_diffuse_records.cpp l.1683–1750, test_scene_pipeline.cpp
l.1042–1088). **Outcome: SURVIVES WITH CORRECTIONS** (applied in a6fbf2e).

| id | kind | item | verdict | severity |
|---|---|---|---|---|
| P07C1-S5-DC-01 | NUMBER | Windows 8-instance 96 kHz T60 8 s load 9 511 / 9 448 ms (AX49 Reversal 9.51 / 9.45 s; §6; 07c-1b scope 8; §0 "9.5 s") | CORRECT (file 41 l.681–682) | none |
| P07C1-S5-DC-02 | NUMBER | macOS 7 846 / 8 780; Linux 4 995 / 5 083 ms | CORRECT (l.486–487, 158–159; the trigger names Windows only) | none |
| P07C1-S5-DC-03 | NUMBER | restore 14 × worst low-α 16.33 / 23.68 / 31.97 s, flutter 6.57 / 8.39 / 12.56 s | CORRECT (l.63, 412, 734; 52, 401, 723) | none |
| P07C1-S5-DC-04 | NUMBER | rated corner (96 kHz, T60_max ≲ 8.3 s, L_p ≤ 3.82 s) vs record (h) (T60 8 s, L_p 3.70 s) | CORRECT: T60_max ≤ (3.82 − 0.1 − 1.118)/0.312 = 8.34 s; record (h) ≈ 7.95 s | none |
| P07C1-S5-DC-05 | NUMBER | the 5 s line | NOT CHECKABLE (a product line); record (h) times sequential restores as AX49 Acceptance specifies | none |
| P07C1-S5-DC-06 | DECISION | scope 8 to the board, 07d's candidates first, no instance cap | CONSEQUENCE | none |
| P07C1-S5-DC-07 | FACT | instance-insertion note faithful to AQ10 / AX48 / A2, except "record (h) prints them apart" (it does not) | CORRECT except the phrase → corrected | minor |
| P07C1-S5-DC-08 | FACT | 07c-1b scope 7 "each fade" includes the restore's EqualPower fade over another scene, where the louder-endpoint bound is not guaranteed (Vorländer §4.3 Eq. 4.15 cross term) | CONDITIONS VIOLATED → restricted to AX47 equal-gain steps and fades from silence | major |
| P07C1-S5-DC-09 | NUMBER | analysis window left to 07c-1b's loop | NOT CHECKABLE (no number chosen); note: state it relative to the 30 ms AQ4 ramp | none |
| P07C1-S5-DC-10 | INCONSISTENT | 07c-1's split note omitted the M2 move | IMPRECISE → corrected | minor |
| P07C1-S5-DC-11 | INCONSISTENT | umbrella 07c-1b "owns" cell | IMPRECISE → corrected | minor |
| P07C1-S5-DC-12 | SOFTWARE | `Stats::insertSolves` exists | listed | — |
