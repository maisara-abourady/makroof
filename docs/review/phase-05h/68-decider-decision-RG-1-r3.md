# 68 — Decider: DECISION RG-1, round 3 (answers interrogator file 67): the macOS trigger GROWTH-only; Seats 5 and 6 read; phase-05i scope 3 text

phase-05h (session 2). Verbatim decider output (the orchestrator saved it).

# Decider — DECISION RG-1, round 3 (answers to interrogator file 67). **State: revised; stands** (max 1, sum 7).

## Corrections: all accepted
- **Q1 / F1 (TENSION MISREAD) — accepted.** The macOS entry is listed at 33.40 s, so OVER30S is its recorded state until 07c; on identical code (37.37 / 31.23 / 31.71 / 27.33 s) the trigger as I worded it would have fired twice and then printed PASSES30S: weather read as (d) defects, and its entry would restate 07c 9–10. **Narrowed to GROWTH-only:** two consecutive macOS runs with the low-α median > 1.10 × 1 817 = 1 999 ms. On the rows on file (2 106, then 1 849 / 1 887 / 1 715) it fires 0 times.
- **Q3 — Seat 3 (file 58 r4): "(x‴) holds at 1 / 1"** with c2 = GROWTH-only and the ±5 % window; "no new condition". Its cell marked "(±5 % read from Seat 7 r2: same four rows, 1.10 unchanged; c2 GROWTH-only in its own words)".
- **Q2 — Seat 5's rating source.** My "plan edit per entry (later 1)" was a misquote: file 57 §4 rates "each creep a plan edit" 2 under (c) and "'no re-run' turns runner speed into register 'defects'" 2 under (a). Withdrawn. **Reading now:** with the trigger narrowed to a form that fires 0 times on the four identical-code runs, Seat 5's objection to both (its §4 (a) and (c) reasons) does not arise; its own form (file 57 r2, 0 / 1) already carried the register entries and the §0 count; Seat 5 is **read from its conditions: 0 / 1 (read)**. Seat 6 likewise: criterion 6 ("a gate red when nothing changed says 'defect' falsely") is not triggered by a rule that fires 0 times on identical code; its line + §0 condition is met (test L514–524): **0 / 0 (read)**. The interrogator checks both readings; if it holds that Seat 5 must see the narrowed clause, CONVENE Seat 5 on this one line: "Does the GROWTH-only macOS trigger (two consecutive medians > 1 999 ms; 0 fires on file) keep your 0 / 1?"
- **Seat 2's debt row** gains "or an added pass" (an extra filterbank pass changes neither length nor n).
- **K3 restated:** at k = 1.20 the per-OS one-sided level is ≈ 97–98 % (t ≈ 3.37 at df 3, 3.02 at df 4): a RATIO warning ≈ 2 % per OS-run, not 0.2 %. Print only. File 63 marked read.
- **Q4 — phase-05i scope 3 named among the amended texts**, replacement below.
- Test nits (status "+N %", the dead ternary at L524) are the orchestrator's; ci.yml L427/L437 already `if: always()`.

## Final form (x‴), item 3 only changed
"Printed with WARNING, never asserted on hosted runners: the low-α/flutter restore ratio above 1.20 × its pinned ratio; the per-scene solve median and its ns per evaluation; 14 × worst above 30 s; the absolute median above 1.10 × baseline where not asserted (macOS until Phase 13); the §5 (c) line. **On macOS, two consecutive runs with the low-α growth warning (median > 1.10 × 1 817 ms) are a defect under (d), remedy named, through `/fix-plan`; the 30 s warning on a listed entry is its recorded state, not a trigger.**" Items 1, 2, 4–7 as file 66 (work pins W / length / FFT n; flutter 30 s strict; low-α 1.10 in a ±5 % flutter window on x64; mean baselines Linux 2 068 / Windows 2 028 / macOS 1 817, flutter 701 / 737 / 484, ratio 3.05 / 2.83 / 3.75, macOS from three runs; PROVISIONAL / ≥ 3-run re-pin; `if: always()`; Phase 13 strict; 07c split-timer packet).

## Tension map (x‴, final)
| seat | now / later | source |
|---|---|---|
| 5 | 0 / 1 (read) | own (x′) cell; ns/eval print per its §2 rule; narrowed trigger fires 0 times on identical code, so its (a)/(c) reasons do not apply |
| 3 | 1 / 1 | r4, own words |
| 2 | 1 / 1 | "(f) 1 with the pin" (pin = length + n via its §7 hand-off to Seat 3) |
| 6 | 0 / 0 (read) | "(f) 0"; "later 1 → 0" on the line + §0 condition, met |
| 7 | 1 / 1 | r2, own words (±5 % in) |
| 1, 4, 8, 9 | 0 / 0 | not required |
Max 1; sum 7 < 10. Ordering unchanged: (d) at bounds; (a) at veto (Seat 5 now 3); worst-off tie with (b)-conditioned; sum; reversibility.

## phase-05i scope 3 — replacement text (L77–85)
"3. **Restore-gate register (AX38 4c, D-H1 (v), RG-F1):** the gate runs in the RG-F1 form (phase-05h §5 'Blocking'): work pins and the flutter 30 s asserted; the low-α absolute median ≤ 1.10 × baseline asserted on Linux and Windows only, inside a ±5 % flutter window; everything else printed with WARNING. Baselines are means, not one-run values: flutter reference 701 / 737 / 484 ms, ratio 3.05 / 2.83 / 3.75, in-window median 2 068 / 2 028 / 1 817 ms (Linux / Windows / macOS; runs named in AX38 4c and the CHANGELOG). What 05i carries: (i) the §0 counts per OS (asserted / not evaluated / WARNING runs) and the GATE lines of every run; (ii) a listed entry whose printed 14 × worst passes 30 s on 05i's runs leaves the register through `/fix-plan` before 05i is `done` (§5 (c)); otherwise it stays listed and the run is recorded; the Linux (30.27 s), macOS (33.40 s) and Windows (36.73 s) entries stay listed with the remedy phase-07c conditions 9–10; (iii) two consecutive macOS runs with the low-α growth warning are a (d) defect, remedy named, through `/fix-plan`; (iv) the per-scene solve median accrues per run; after ≥ 3 runs the orchestrator proposes its bound k from the spread through `/fix-plan`; (v) the baselines, the ±5 % window and k are re-derived from ≥ 3 in-window runs at the 07c re-pin (one run PROVISIONAL, printed not asserted); never a red or out-of-window run as a baseline. The runner's speed remains the recorded likely cause of the listed entries, to be shown at Phase 13 (AX41)."

## FOR MAISARA RG-F1 (final plan text; phase-05h §5 "Blocking" (a)–(b) and AX38 4c's register paragraph)
As file 66, with one sentence replaced: "On macOS two consecutive runs with the low-α growth warning (median above 1.10 × the pinned baseline) are a defect under (d), remedy named, through `/fix-plan`; the 30 s warning on a listed entry is its recorded state until phase-07c, not a trigger." Amended texts: AQ10 amended (1), AX38 4c, phase-05h §5 "Blocking" ((c)–(d): "growth bound" → "the asserted figures above"), **phase-05i scope 3 (above)**, phase-07c condition 9 packet (the split timer on one named local box), phase-13 (release-machine strict re-check; machines bought once), AX41 cross-reference. PRD ids, reasoning, the option lines ((x‴), (a), (b), (c), (e), (g), (d)) and the veto line: as file 66, with NFR-4 read as "VST3 and AU on macOS and Windows" and the three-OS `ci ok` as CLAUDE.md step 6.
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

## Test form and CI (final)
Unchanged from file 66 and already in the tree (test L83–88 constants, L376–392 pins, L393–414 solve timer, L514–526 GATE lines and guarded REQUIRE; ci.yml L427/L437). The macOS two-consecutive rule is read by the orchestrator from the §0 count **on the GROWTH flag only**; OVER30S and PASSES30S remain informational. Nits: print "+N %" in the not-evaluated status; remove the dead ternary at L524.

## Future-debt register (x‴)
| seat | commits later phases to | undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 5 (later 1, read) | a record that must be read; strict re-enforcement on release machines; a (d) edit per macOS double growth warning (0 on file) | flag flip per entry | Phase 13 run; §0 counts | Phase 13 |
| 3 (later 1) | a uniform synthesis slowdown < ≈ ×1.65 reaches hosted CI as a warning; solve bound only after ≥ 3 runs; 07c sizes on the split-timer packet | — | 07c condition 9 packet; 3 runs | 07c |
| 2 (later 1) | a per-op slowdown **or an added pass** at unchanged length / n invisible until Phase 13; re-pin at 07c | one constant + CHANGELOG | 07c; Phase 13 | 07c / Phase 13 |
| 7 (later 1) | the in-window 1.10 at n = 2 until the 07c re-derivation; one §0 explanation; release machines bought once | — | 07c re-pin; Phase 13 | Phase 13 |

**Strongest objection** unchanged (the in-window 1.10 at n = 2 on x64; file 63 G4/G6); holds as in file 66; falls if an in-window x64 run goes red by runner before 07c, in which case x64 takes macOS's form through `/fix-plan`. **Confidence:** medium (Seat 5 and Seat 6 cells read; n = 2). **Reversal:** Phase 13's release-machine run; the 07c re-pin; an in-window x64 red; ≥ 3 solve-median runs.

**Summary:** `RG-1 | (x‴) with GROWTH-only macOS trigger | revised, stands | Seats 2, 3, 7 (1 / 1) | 7 | medium | L101/NFR-2, NFR-4, NFR-1, (v)(d) | none needed | Phase 13 run; 07c re-pin; §0 count`

**Decided for Maisara.** RG-F1: on shared CI machines the gate judges the work exactly and the restore's growth only when the machine is at normal speed; the rest is printed with a warning and counted; on macOS two growth warnings in a row count as a defect; the strict 30 s is judged on the release machines at Phase 13 (L101, NFR-2, NFR-4, NFR-1). Seat 3 gave the most and gets the macOS growth trigger, 07c's split-timer packet and the Phase 13 strict check back. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` **NEEDS MAISARA:** none.

Files: /home/user/makroof/docs/review/phase-05h/67-interrogator-RG-1-r2.md, /home/user/makroof/docs/review/phase-05h/58-seat3-restore-gate-runner-variance.md (round 4), /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md §4, /home/user/makroof/docs/phases/phase-05i.md L77–85.
