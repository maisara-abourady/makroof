# Phase-07 applied decisions (7871f26, 614a005): interrogator diff check, round 1 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Nothing acoustic or numeric WRONG; all numbers, formulas and citations match the verified texts (DC-9 … DC-23 CORRECT:
D1 example 0.52 m, D2 −34.5 dB re 1 m and 19–22 dB, D3, D4 +28.5 / +43.9 dB (Kuttruff Eq. 5.45), DoD same point, D9
×1.0429 and Sabine/Eyring range, D5 ≥ 10.56 m, D8/AX34, AX33, D7 transcription, AX18 (Eq. 4.15; 0.414; 58.3/f_c m;
−10.7 dB), phase-10 gate known limit (r = 7 → −0.99 dB), phase-11/13 items).

| id | passage | verdict | fix | severity |
|---|---|---|---|---|
| DC-1 | builder rule (R3-1) + reset step 3 (R3-2) vs skip rule | INCONSISTENT (software) | a bit-identical skip never records its generation → builder rebuilds the same IR every 20 ms (e.g. output_mode change); record a skipped decision's generation as handled (builder and offline dirty check) | major |
| DC-2 | AC "No lost update … last submitted scene equals the final parameter values" vs skip rule | INCONSISTENT (software) | restate on the last decided generation / submitted IR equals the IR of the final values | major |
| DC-3 | restore flag consumers vs scope 4 synchronous setStateInformation rebuild; test (d) realtime merge | INCONSISTENT (software) | name which thread makes the restore's decision in realtime; list setStateInformation's synchronous build as a consuming decision or hand off to the builder; align test (d) | major |
| DC-4 | "advocate PASS" for D7 | IMPRECISE | "advocate round 2 REDIRECT, cleared on interrogator confirmation" | minor |
| DC-5 | AC test list omits D7 tests (a)–(f) | IMPRECISE | add | minor |
| DC-6 | AQ4 / phase-10 AX18 line omit room-size and placeholder | IMPRECISE | mirror AX18 | minor |
| DC-7 | AQ4 "recommendation", slot wait | IMPRECISE | "slot wait (0 for an isolated request, AX33)"; drop "recommendation" | minor |
| DC-8 | "fade in from s0 = 2P (step 4)" | IMPRECISE | "(`computeBlock` step 4)" | minor |
