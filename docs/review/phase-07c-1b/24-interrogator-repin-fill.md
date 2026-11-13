# 24 — Interrogator, `/fix-plan` step 5 on the re-pin fill (commit b42457c)

2026-11-13, corpus c1b171f (no acoustic FACT in the fill; arithmetic against records and decided rules). Saved by the orchestrator
(summary; ledger in substance). Every placed value recomputes CORRECT (r̄, max/min, F̄, baselines, solveRefMs, k, f, G9, 1703 ms,
X-d− +30.5 / +51.0 %, E1, B1-b figures; no point INSTRUMENT INVALID, lowest count 7355 > 7125). Step 5 **not complete**: two
INCONSISTENT (major) items, several minor.

| id | item | verdict | note |
|---|---|---|---|
| P07C1B-RP-01 | AX38 (i) note B1-b figures | CORRECT | file 23 |
| P07C1B-RP-02 | note: Linux RESIDUAL on all three runs, generic D-B1 item 6 sentence | IMPRECISE (minor) | does not say Linux's residual is now the 13-3 scope 4 / R5 item, nor that D-B1's reversal ("an overrun at 8 builders with a clean floor") is met on Linux |
| P07C1B-RP-03 | Linux measurement condition | IMPRECISE (minor) | Linux "priority: not available (errno 1 … RLIMIT_RTPRIO 0)": taken on a default-priority thread (D1-L2: not a host audio thread); unstated |
| P07C1B-RP-04 | r̄, max/min, Linux print-only, Windows asserted | CORRECT | proviso applied as corrected (DC-07, DC2-02…05); code L744 |
| P07C1B-RP-05 | f, s_L, s_F, branch A | CORRECT | |
| P07C1B-RP-06 | "the stage split's max/min ≤ 1.10 holds only on Windows" | IMPRECISE (minor) | `repin_gate.py` L216 `domainMaxMinOk` uses the ratios' max/min, not a stage-split quantity → "the ratios' max/min ≤ 1.10 (the print-only proviso) holds only on Windows" |
| P07C1B-RP-07 | solveRefMs, k | CORRECT | |
| P07C1B-RP-08 | G9 met Linux, Windows; not macOS | CORRECT values; IMPRECISE consequence | file 11: once met, "k and solveRefMs then pinned … with a CHANGELOG reason"; else "re-derived at the 07d re-pin"; 4c, CHANGELOG and the code label ("S2-PROVISIONAL") do not state it per OS |
| P07C1B-RP-09 | FM-TRIG 1703, ×1.167, no S2 run over | CORRECT | |
| P07C1B-RP-10 | X-d− | CORRECT | |
| P07C1B-RP-11 | E1 closures, `listed` false | CORRECT | |
| P07C1B-RP-12 | baselines | CORRECT | |
| P07C1B-RP-13 | G5 "(today w ≈ 2 %)" stale | IMPRECISE (minor) | on S2: Windows (1+w)·1.0219 ≤ 1.083 → w ≤ 5.98 %; Linux max r/r̄ 1.1230 ≥ 1.07 → leg not added there if 07d looks like S2 |
| P07C1B-RP-14 | FM-GROWTH public reason ("the same-run ratio measures the code") and Q2's premise (Linux max/min 1.071) | **INCONSISTENT (major)** | on identical code Linux's ratio spans 1.967–2.691 (max/min 1.3681, r/r̄ up to 1.1230); hosted Linux has no asserted growth check before 07d; the Decided-for-Maisara line "judged on Linux and Windows by the within-run ratio" is untrue for Linux as pinned |
| P07C1B-RP-15 | phase-07d title / Goal ("Close the AX38 4c … entries"), §0 row 07d, Depends line | **INCONSISTENT (major)** | contradict 07d scope 1, 5, AC notes and 4c E1; 07d still owns scopes 2, 6–8 (D-B4 C7′, X-d−, FM-GROWTH re-pin), all decided — wording, not a DECISION, unless size, dependencies or P1 change |
| P07C1B-RP-16 | §6 row 521 "phase-phase-07c-1b" | typo | fix |
| P07C1B-RP-17 | 4c Records sentence (1 178 / 4 245 / 1 137 µs "carried to phase-07c-1b") | IMPRECISE (minor) | add "(re-instrumented: AX38 (i) cond. 12 (c) note)" |

Questions: Q1 (RP-14) restate the FM-GROWTH Maisara line and public reason for Linux; does Linux run 1 (r/r̄ 1.1230 > 1.10) meet
FM-GROWTH's reversal ("a ratio red on identical code shown to be noise") in substance? Q2 (RP-02/03) state the Linux residual as the
D-B1 item 6 item with its reversal met, measured without RT priority? Q3 (RP-08) G9 consequence per OS (Linux, Windows out of
PROVISIONAL with a CHANGELOG reason and plan line; macOS re-derived at 07d)? Q4 (RP-13) restate or drop "w ≈ 2 %"? Q5 (RP-15)
restate 07d's goal, §0 row, Depends to scopes 2, 6–8 — wording only?
