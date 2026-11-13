# 13 — Interrogator, document mode: `/fix-plan` step 5 on the plan-editor diff

2026-11-13, corpus c1b171f. Saved by the orchestrator from the interrogator's report. The interrogator read the current text of
every changed passage (no shell) against decider file 11 with interrogator file 12's corrections 1–4, RG-1's final 4c (d) text
(`docs/review/phase-05h/71-interrogator-RG-1-r4.md` L19) and CI record files 42, 44.

**Orchestrator's diff check (the part the interrogator could not run):** `git diff 89183bd -- docs/BUILD_PLAN.md docs/phases/
docs/PRD.md` changes BUILD_PLAN only at L160 (the AX38 row), L169–171 (AX47–AX49) and the six new §6 rows after L520; the phase files
changed are exactly 07c-1b, 07c-2, 07d, 08-3, 08-4, 09, 13-1, 13-2, 13-3, 13-5; `docs/PRD.md` untouched. No unlisted row or file
changed.

## Overall
Every replaced 4c passage matches its G-number (G1–G14); sub-items relabelled (row 15); everything on the "Not amended" list present;
4c (d) matches RG-1's final text word for word; AMENDS line exact; arithmetic checks; X-d− run ids and figures match files 42, 44.
Two defects: phase-07c-1b AC 7 / scope 7 contradicts the decided AX47 check (DC-35); the D-B1 re-instrument has no work item in
phase-07c-1b (DC-36 — a gap in file 11's plan text, not the editor's error).

**Ruling on the plan-editor's D1:** implied by the decisions, no new decision: the print-only proviso is re-read at every pin over the
runs that set that pin's r̄ (S2 at 07c-1b; ≥ 3 at 07c-2; ≥ 6 at 07d) — (1) file 12 row 13 / correction 2 renamed G5's reference "the
current pin" and the proviso is a clause of G5 describing r̄'s calibration runs; (2) file 11 Q1's reason ("a detector that fires on
identical code does not serve 'usable'") applies to every r̄; (3) tying it to S2 would keep an OS print-only after a tight re-pin,
contradicting Q2's "armed every Linux / Windows run" (Q2's "Windows only while its S2 max/min ≤ 1.10" was written when S2 was the pin).

## Ledger
| id | kind | item | verdict | evidence | severity | correction |
|---|---|---|---|---|---|---|
| P07C1B-DC-01 | NUMBER | AX38 (i) cond. 12 (c) note | CORRECT; placement IMPRECISE | matches item 1; p99.9 = us[⌈0.999N⌉−1]: N 953 → index 952 (largest), N 1 936 → 1 934 (2nd); the note sits before the 05i line `AMENDS … (AX38 (i): register entry G-1 added, no rule change.)`, which then reads as covering it (D-B1 amends nothing) | minor | add "(amends nothing)" or move it after that AMENDS line |
| P07C1B-DC-02 | DECISION | AX38 (iv) Record FM-10S insert | CORRECT | item 13 verbatim | — | — |
| P07C1B-DC-03 | DECISION | G1 (b) | CORRECT | + G5's print-only proviso (row 13) | — | — |
| P07C1B-DC-04 | DECISION | G2 (c) | CORRECT | + proviso | — | — |
| P07C1B-DC-05 | DECISION | G3 | CORRECT | verbatim | — | — |
| P07C1B-DC-06 | NUMBER | G4a–c | CORRECT | 1.10 × 2 068 = 2 274.8 → 2 275 ms | — | — |
| P07C1B-DC-07 | NUMBER | G5 r̄ "of the current pin"; proviso "S2 ratios" | IMPRECISE | correction 2 renamed r̄; the proviso still names S2 (D1 ruling) | minor | "an OS whose ratios over the current pin's runs have max/min > 1.10 is print-only"; same in G1, G2, §6 row 523 |
| P07C1B-DC-08 | NUMBER | G5 absolute leg 1.083, w ≈ 2 %, no leg if ≥ 1.07 | CORRECT | 1.083/1.062 − 1 = 1.98 %; margin 1.10/1.083 = 1.016; at 1.07, w ≤ 1.2 % | — | — |
| P07C1B-DC-09 | NUMBER | G5 f ≈ ×1.28 | CORRECT | from s_L·k + 1 − s_L > 1.10(s_F·k + 1 − s_F) (needs s_L > 1.10·s_F); 0.459/0.359 = 1.279 | — | — |
| P07C1B-DC-10 | NUMBER | G5 coverage ≈ ×1.21–1.28 at w ≈ 2 % | CORRECT | upper edge: 1.02(0.92k + 0.08) > 1.10(0.51k + 0.49) → 0.377k > 0.457 → k > 1.21; centre 1.28 | — | — |
| P07C1B-DC-11 | NUMBER | G5 "Every GATE line prints in-window yes / no and the flutter deviation" before 07d | IMPRECISE (decision text, faithful copy) | until the 07d re-pin there is no w (07c-1b scope 1 "no ±5 % window"), so "in-window" is undefined on 07c-1b and 07c-2 runs | minor | Q4 |
| P07C1B-DC-12 | DECISION | G5 closing PR sentence | CORRECT | correction 1 applied | — | — |
| P07C1B-DC-13 | DECISION | G6 | CORRECT | — | — | — |
| P07C1B-DC-14 | NUMBER | G7 | CORRECT | 1.20 / `kSolveWarn` wording removed from 4c | — | — |
| P07C1B-DC-15 | DECISION | G8 | CORRECT | — | — | — |
| P07C1B-DC-16 | NUMBER | G9 | CORRECT | — | — | — |
| P07C1B-DC-17 | DECISION | G10 | CORRECT; wording IMPRECISE | "above 1.10 × the current pin" omits what is pinned (the baseline median); the parenthetical omits a print-only OS and a not-added 07d leg | minor | "above 1.10 × the current pin's baseline median where not asserted (macOS or a print-only OS; Linux and Windows out of window, before 07d, or where the 07d leg was not added)" |
| P07C1B-DC-18 | DECISION | G11 | CORRECT | — | — | — |
| P07C1B-DC-19 | DECISION | G12 + G12a | CORRECT | the kept re-pin rule present | — | — |
| P07C1B-DC-20 | DECISION | G13 | CORRECT | — | — | — |
| P07C1B-DC-21 | DECISION | G14 | CORRECT | — | — | — |
| P07C1B-DC-22 | DECISION | 4c (d) and "Not amended" | CORRECT | (d) = 05h file 71 L19; 1.10, Phase 13 re-enforcement, flutter 14 × worst ≤ 30 s present | — | — |
| P07C1B-DC-23 | NUMBER | FM-TRIG paragraph | CORRECT | k > 1 + 0.15/s_L = 1.163 at 0.92; 1 + 0.23/0.92 = 1.25; her "2 172 ms … re-derived at the 07c re-pin" kept | — | — |
| P07C1B-DC-24 | NUMBER | X-d− runs and figures | CORRECT | file 42 L566: 2223, ratio 3.318, L565 +38.4 %; file 44 L593: 2572, 5.048, L592 +5.3 %; flutterRef 484 = fact 5 | — | — |
| P07C1B-DC-25 | DECISION | E1 | CORRECT | — | — | — |
| P07C1B-DC-26 | SOFTWARE | step-summary rule | not rated | matches item 9 (f) | — | — |
| P07C1B-DC-27 | DECISION | amendment block, AMENDS, public reason | CORRECT | — | — | — |
| P07C1B-DC-28 | NUMBER | AX47 Measurement sentence | CORRECT | per sample |o|² ≤ (1−g)|a|² + g|b|² (Jensen); over a window where g moves by N_w/L, energy ≤ (1 + N_w/L)·max ≤ (1 + N_w/L)²·max: conservative and valid; "> 8u·L" from a one-sample gain error |b−a|/L; Eq. 4.15 not reopened | — | — |
| P07C1B-DC-29 | DECISION | AX48 FM-B2 sentence | CORRECT | — | — | — |
| P07C1B-DC-30 | DECISION | AX49 Reversal | CORRECT | — | — | — |
| P07C1B-DC-31 | DECISION | §6 rows 521–526 | CORRECT | row 523 carries DC-07's "S2 ratios" | minor (via DC-07) | — |
| P07C1B-DC-32 | NUMBER | 07c-1b scope 1 / AC 1 "PROVISIONAL, print-only … until AX38 4c's dated exit" | IMPRECISE | G9: after the exit k is "still print-only on hosted runners"; "until" can attach to "print-only" | minor | "PROVISIONAL until its dated exit; print-only on hosted runners throughout (G9)" |
| P07C1B-DC-33 | DECISION | 07c-1b scope 2 / AC 2 (E1) | CORRECT | — | — | — |
| P07C1B-DC-34 | DECISION | 07c-1b scope 6 / AC 6; review focus | CORRECT | — | — | — |
| P07C1B-DC-35 | NUMBER | 07c-1b scope 7 last sentence; AC 7 | **INCONSISTENT** | AC 7 still sets the window "in this phase's loop" and asserts output energy "does not exceed the louder endpoint's"; AX47 now decides 1 ms windows and E_out ≤ (1 + N_w/L)²·max·(1 + 10⁻⁵); a correct equal-gain fade breaks the strict form (a, b in disjoint samples at g = 0, g = x: E = E_a + x²·E_b > max) — AC 7 as written fails on correct code | major | Q1 |
| P07C1B-DC-36 | DECISION | 07c-1b scope 3 / AC 3: D-B1 B1-b instrument | **INCONSISTENT** (missing line; not the editor's error) | the AX38 (i) note says "re-instrumented in 07c-1b"; 08-4 and 13-3 run "07c-1b's instrument"; 07c-1b scope 3 / AC 3 say only that the rise "goes to the board loop"; the D-B1 spec (file 4 L41–54; item 6 corrected in file 8 L38–41) is in no 07c-1b line, and file 11 has no item for it | major | Q2 |
| P07C1B-DC-37 | DECISION | 07c-1b scope 8 "taken in this phase's loop (or the loop moves it to 07d)" | IMPRECISE (stale but true) | D-B4 moved it | minor | "moved to phase-07d by D-B4 (C7′)" |
| P07C1B-DC-38 | DECISION | 07d scope 2 candidates | CORRECT | order and conditions match item 8 | — | — |
| P07C1B-DC-39 | DECISION | 07d scopes 6–8 and ACs | CORRECT; minor | the re-pin AC "asserted on Linux and Windows" omits a print-only OS | minor | Q3 |
| P07C1B-DC-40 | DECISION | phase-07c-2 sentences | CORRECT | unchanged context L48 "k (`kSolveWarn`) re-derived" stale next to G7's k | minor | "k (G7)" |
| P07C1B-DC-41 | DECISION | phase-08-3 | CORRECT | — | — | — |
| P07C1B-DC-42 | DECISION | phase-08-4 | CORRECT | — | — | — |
| P07C1B-DC-43 | DECISION | phase-09 | CORRECT | — | — | — |
| P07C1B-DC-44 | DECISION | phase-13-1, 13-5 R3 | CORRECT | row 17 (a), (b) applied | — | — |
| P07C1B-DC-45 | DECISION | phase-13-2, 13-3, 13-5 scope 3 | CORRECT | — | — | — |
| P07C1B-DC-46 | DECISION | D1: proviso re-read at each pin | implied, no new decision | file 12 row 13 / correction 2; file 11 Q1, Q2; G13 | — | Q3 |

## Questions
1. (DC-35) AC 7 / scope 7 → the AX47 Measurement check as decided (1 ms windows, the (1 + N_w/L)² bound, per-sample bound,
   reconstruction), replacing the strict "does not exceed the louder endpoint" and "window set in this phase's loop" (D-B3 / item 6).
2. (DC-36) Which 07c-1b scope line carries D-B1 B1-b's instrument (file 4 spec items 1–5; item 6 corrected in file 8 L38–41)?
3. (DC-07, DC-39, DC-46) G1, G2, G5, §6 row 523 and the 07d AC: "an OS whose ratios over the current pin's runs have max/min > 1.10 is
   print-only".
4. (DC-11) Before the 07d re-pin there is no w: against which window is "in-window yes / no" printed on 07c-1b and 07c-2 GATE lines,
   and what does §0 count?
5. (DC-32) After the G9 exit, does the solve bound stay print-only on hosted runners (G9) or not?
