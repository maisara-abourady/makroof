# Phase 06b — interrogator, decision mode, round 2 (2026-11-07, corpus c1b171f)

Target: `decider-round2.md`. Nothing falls; round-1 majors P06B-39, 47, 55 fixed; all other round-1 rows
applied (P06B-35 not carried into the plain D1 line, P06B-63).

| decision | outcome | remaining corrections (wording, applied with the texts) |
|---|---|---|
| D1 | SURVIVES WITH CORRECTIONS | P06B-62 ("the risk exists at any non-zero latency"), P06B-63 (plain line: qualify "and bounce") |
| D2 | SURVIVES | P06B-66 is a consequence for phase 08 (which limit: Table 15.1 35 ms or §15's printed 20 ms; does the 30 ms fade count) |
| D3 | SURVIVES WITH CORRECTIONS | P06B-68 (state both Izhaki theoretical extremes), P06B-69 (104 dB / 1.7 T for medium_room's peak tap; 1.7–1.9 T over the test scenes) |
| D4 | SURVIVES WITH CORRECTIONS | P06B-71 ("every operation that reaches the output is exact") |

| id | type | claim | verdict | evidence | severity |
|---|---|---|---|---|---|
| P06B-61 | NUMBER | halving P costs 1.5–2.1× CPU (3 s, host 512) | CORRECT (arithmetic) | 2.00/1.51/2.08; steady 2.12/1.67/2.13 | none |
| P06B-62 | FACT | bounce misaligned "288 as much as 544" | IMPRECISE: the offset is the uncompensated delay; "the risk exists at any non-zero latency" | Izhaki App. A "Time range" | minor |
| P06B-63 | FACT | plain line "DAW compensates it on playback and bounce" | IMPRECISE (P06B-35 not carried over) | Izhaki Ch. 11, App. A | minor |
| P06B-64 | FACT | item 9 remedy "not P = 256 (1.5–2.1×, host 512)" | CORRECT (derived; condition stated) | P06B-39 | none |
| P06B-65 | NUMBER | (13.7, 24.3] ms; W1 31.3 vs 41.9 ms | CORRECT | P = 10.67 ms; Vorländer Table 15.1 | none |
| P06B-66 | NUMBER | 35 ms as the head-rotation limit | CONSEQUENCE: §15 prose prints 20 ms (Table 15.1: 35 ms); phase 08 should name which it applies; fade inclusion NOT CHECKABLE | Vorländer §15 | minor |
| P06B-67 | NUMBER | AX32 sufficient condition, 1.58e29 per path | CORRECT | 3.4028e38/2³¹ = 1.585e29 | none |
| P06B-68 | FACT | "a million tracks … the theoretical extreme" | IMPRECISE: Izhaki also gives ≈ 764 dB boost; state both, neither is a working level | Izhaki Ch. 11 | minor |
| P06B-69 | NUMBER | clamped burst full scale "until its reverb falls 104 dB, ≈ 1.7 T" | IMPRECISE: 104 dB uses medium_room's peak tap 0.155; largest test tap 0.49 → 114 dB ≈ 1.9 T | M1; Kuttruff §3.8 | minor |
| P06B-70 | FACT | test (c) readings, boundary values | CORRECT (+87 dB illustrative; ≈ +91 dB at n ≈ 2e4) | arithmetic | none |
| P06B-71 | FACT | D4 "every operation in this case is exact" | IMPRECISE: non-DC bins of H are rounded but only meet exact zeros of X; "every operation that reaches the output is exact" | arithmetic | minor |
| P06B-72 | FACT | only the pre-roll buys accuracy | NOT CHECKABLE (plan/code) | AX1; RealtimeEngine.h:45 | none |
| P06B-73 | FACT | 50 ms is §15 text for interactive VR | CORRECT | Vorländer §15 | none |
