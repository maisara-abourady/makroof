# 25 — Decider: rulings on the re-pin fill (interrogator file 24, Q1–Q5)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing; arithmetic on files 22, 23). Saved by the orchestrator from the decider's
report. **Verdict:** no new board decision, nothing to Maisara. Q1 a reading of decided text plus a routing line for 07d; Q2–Q4
restatements; Q5 wording only. PRD digest: NFR preamble (L101) "must stay usable in a DAW session"; NFR-4 (L108) shipping platforms
macOS and Windows, Linux a CI OS only; NFR-6. Bounds: RG-F1 / AX38 4c as amended by FM-GROWTH; 4c (d) "no re-run"; 1.10 never
loosened (decider.md §5); D-B1 item 6; G9 as decided.

## Q1 — FM-GROWTH on Linux (RP-14)
**Ruling.** FM-GROWTH's reversal is met in substance on Linux, as a counterfactual: three S2 runs on the same code 9717a58; run
43389296112's ratio 2.691 / 2.3963 = 1.1230 × the r̄ it helped set — a 1.10 assertion would have gone red on unchanged code; no real
red (ratioCheck was PROVISIONAL). The consequence is already decided text: G5's proviso (DC-07, DC2-02…05) — "an OS whose ratios over
the current pin's runs have max/min > 1.10 is print-only, as macOS"; Linux 1.3681 → print-only. No new decision.
**Not a CONVENE now:** on the S2 Linux data no rated option gives Linux an asserted check — ratio form (B-iv, B-iv/+07d) fails the
proviso; in-window absolute forms (B-i, B-ii, B-iv+ now) never evaluate (Linux flutter 411 / 515 / 731 ms vs F̄ 552.3: −25.6 / −6.8 /
+32.4 %); B-iii (the only one sometimes evaluating) already rated 2/2 by Seats 5, 6, 7 (false defects); widening 1.10 breaks
decider.md §5. Re-rating the same options on the same data cannot change the winner. PRD check: Linux is not a NFR-4 shipping
platform; Windows (shipping) stays asserted (1.0530); macOS was print-only before. **Routing:** to the 07d re-pin (scope 8, ≥ 6 runs);
to 07d's board loop only if Linux is again print-only there. Nothing to Maisara.

**Texts.**
- Decided for Maisara, FM-GROWTH (replaces file 11's line): "FM-GROWTH — restore growth on hosted runners is judged by the
  within-run low-α / flutter ratio at 1.10 × its pin, asserted on an OS only where its pin runs agree within 1.10 (max/min). On the
  07c-1b S2 runs that is Windows (1.053). Linux (1.368 on unchanged code) and macOS (1.162) are printed, not asserted. So before 07d,
  hosted Linux has no asserted growth check; its GROWTH prints fired on unchanged code in the S2 runs and are leads, not defects. The
  absolute 1.10 bound returns at 07d, in-window, sized with a stated margin over the largest of ≥ 6 runs (on an OS only if those runs
  agree within 1.07), and on all three OSes on the Phase 13 release machines. If 07d's runs leave Linux print-only again, Linux's
  form goes to 07d's board loop. Solve baselines are provisional until a dated exit (met at S2 on Linux and Windows). Rests on:
  preamble, NFR-4, NFR-6, RG-F1. Seat 3 gave most (no asserted check on Linux, weaker uniform detection everywhere until 07d) and gets
  the absolute leg back at 07d where the runs allow, and on the release machines. `AMENDS her decision of 2026-11-10: "I accept the
  board's answer by definition."` (G1–G14 of AX38 4c, verbatim; unchanged)."
- 4c public reason (replaces the current sentence): "The absolute bound measured runner speed. The same-run ratio cancels most of it,
  not all: on unchanged code it held within 5.3 % on Windows and is enforced there; it moved 37 % on Linux and 16 % on macOS, so there
  it is printed, not enforced. The absolute bound returns at 07d where ≥ 6 runs leave a stated margin, and on all three systems on the
  Phase 13 release machines."
- 4c "Amended 2026-11-13" summary: replace "the growth check on Linux and Windows hosted runners is the same-run low-α / flutter ratio
  at 1.10 × its current pin, every run" with "the growth check on hosted runners is the same-run low-α / flutter ratio at 1.10 × its
  current pin, every run, asserted on an OS whose pin runs' ratios have max/min ≤ 1.10 (at 07c-1b Windows only; Linux 1.3681 and macOS
  1.1618 print-only)".
- 4c, new sentence after the public reason: "FM-GROWTH reversal ('a ratio red on identical code shown to be noise'): met in substance
  on Linux at the S2 re-pin (run 43389296112 at 1.1230 × r̄ on code 9717a58; low-α median 1 438 ms on run 43412038058 above 1.10 ×
  1 282.7 = 1 411 ms). Handled by the print-only proviso, no new decision; Linux's form is re-read at the 07d re-pin (phase-07d scope
  8)."
- phase-07d scope 8, append: "If Linux's ratios over the re-pin runs again have max/min > 1.10 (S2: 1.3681), or max(r/r̄) ≥ 1.07 leaves
  it without the absolute leg, Linux's hosted growth check returns to this phase's board loop (FM-GROWTH reversal, met in substance at
  S2), with the S2 and re-pin spreads; 1.10 unchanged, no re-run."
- phase-07d last AC, append: "; Linux returned to the board under scope 8 if print-only again."
- Debt row S3 / S6 restated: commits — no asserted growth check on hosted Linux before 07d (scene-specific or uniform), GROWTH prints
  only; undo one constant; evidence 07d re-pin runs; repaid at 07d if Linux's re-pin runs agree, otherwise on the Phase 13 release
  machines.

## Q2 — Linux RESIDUAL (RP-02, RP-03)
**Ruling.** D-B1's reversal ("overruns > period at 8 builders with a clean floor (board on B1-d at Phase 13, earlier if 08-4 shows
it)", file 4 L67–68) is met on hosted Linux as a record, under a condition it does not target: B1-b spec item 1 printed Linux priority
"not available (errno)", RLIMIT_RTPRIO 0 on all three runs — a default-priority thread, not a host audio thread (D1-L2); thread-CPU max
at 8 builders 1 158 / 1 138 / 1 161 µs, below the 1 333 µs period — the overruns are wall time (wake late up to 6 474 µs). What
follows is D-B1 item 6 as decided; "earlier if 08-4 shows it" reads as an 08-4 residual measured with RT priority obtained (a reading of
the spec's own priority print, not a new rule).
**Note text** (AX38 (i) cond. 12 (c) note; replaces "(RESIDUAL printed on all three runs)" and the sentence "A residual (overrun > period
at 8 builders, none at 0) is re-measured … never an instance cap."): "Linux: the residual (overrun > period at 8 builders, none at 0)
on all three runs. It is the D-B1 item 6 residual: re-measured in phase-13-3 scope 4 and on the R5 Windows release machine; a miss
there opens 13-1b with B1-d first; never an instance cap. It was measured without real-time priority ('priority: not available (errno
1 …; RLIMIT_RTPRIO 0)': a default-priority thread, not a host audio thread, D1-L2). Thread-CPU max at 8 builders was 1 158 / 1 138 /
1 161 µs, below the 1 333 µs period; the overruns are wall time (wake late up to 6 474 µs). D-B1's reversal ('an overrun at 8 builders
with a clean floor') is therefore met as a record under a condition it does not target. It does not reopen D-B1. Phase-08-4 repeats
the instrument and prints the priority obtained; an 08-4 residual with real-time priority obtained returns D-B1 to the board before
Phase 13. macOS: overruns > period at 0 builders on every run (3 / 5 / 10), no clean floor, not a residual. Windows (MMCSS 'Pro
Audio'): 0 / 0 on all three."

## Q3 — G9 per OS (RP-08)
**Ruling (G9 as written).** Linux and Windows: exit met; k and solveRefMs (Linux 1.2225, 130.8 / 80.7 ms; Windows 1.0846, 106.0 /
66.2 ms) pinned from the S2 runs with a CHANGELOG reason, out of PROVISIONAL, still print-only on hosted runners, never a (d) trigger.
macOS: not met (0.5038 / 0.7250 / 0.7892); PROVISIONAL, re-derived at the 07d re-pin, otherwise named in Phase 13 (13-5 R5). Later
re-pins: 07c-2's W_max change and 07d's remedy change the work pins (G13): Linux and Windows re-pin and re-test the exit then.
**Text** (replaces "on the 07c-1b S2 runs the exit is met on Linux (…) and Windows (…), not on macOS (…)"): "on the 07c-1b S2 runs the
exit is met on Linux (ns-per-eval ratios 0.5773 / 0.5814 / 0.5849) and Windows (0.5879 / 0.5866 / 0.5916): k and solveRefMs pinned from
those runs (CHANGELOG reason, commit [pin commit]); out of PROVISIONAL, still print-only on hosted runners, re-pinned and the exit
re-tested at 07c-2 and 07d (G13). macOS not met (0.5038 / 0.7250 / 0.7892): PROVISIONAL, re-derived at the 07d re-pin, otherwise named
in Phase 13 (13-5 R5)."
**CHANGELOG reason:** "07c-1b S2 re-pin: G9 exit met on Linux and Windows (≥ 3 green runs, ns-per-eval ratio within 1.05 of its mean);
k and solveRefMs pinned from runs 43389296112, 43402114873, 43412038058; macOS not met, PROVISIONAL until 07d."
**Code label: change in this phase** (part of the condition 7 re-pin, test-only): `test_diffuse_records.cpp` L763 prints
"S2-PROVISIONAL" for every OS, contradicting 4c — add a per-entry flag `solveExitMet` that repin_gate emits from its G9 line; print
`S2-PINNED` where set, `S2-PROVISIONAL` where not; update repin_gate's constants line; `pytest tools/ci` green; batched into the same
push and manual CI run as the pinned constants (if that run already happened, one CI-fix-class push).

## Q4 — "(today w ≈ 2 %)" (RP-13)
**Restate:** "(S2 preview, not a pin: Windows max r/r̄ 1.0219 gives w ≤ 5.98 %; Linux max r/r̄ 1.1230 ≥ 1.07, so no leg if the re-pin
runs look alike; w is computed at the 07d re-pin)" (1.083 / 1.0219 = 1.0598). The coverage parenthetical "≈ ×1.21–1.28 at w ≈ 2 %
(05h shares)" stays (a correct, labelled conditional).

## Q5 — phase-07d wording (RP-15)
**Wording only** (size S–M, Depends, P1, scopes and ACs unchanged; only Q1's scope 8 and AC lines added).
- Title: "# Phase 07d — Load at the long-T60 corner, the macOS (d) defect and the growth re-pin (condition 9's split)"
- Header Depends parenthesis: "(07c-1b closed both AX38 4c `cube100_lowalpha0.05_s0.3` entries under E1 and leaves scopes 2, 6–8 here)"
- Goal: "Bring the 8-instance Windows load at the rated corner to ≤ 5 s on record (h) through scope 2's candidates, C9 first (scope 6;
  D-B4 C7′). Close the macOS (d) defect of runs 42 and 44 on measured evidence (scope 7; X-d−). Re-pin the AX38 4c growth check from
  ≥ 6 green runs on the restore path this phase leaves (scope 8; FM-GROWTH). At the long-T60 corner AX49's interim is the full tail (L_p
  ≥ L), so the restore still contains the full unit-decay synthesis (phase-07c-1 decider file 12 §8). The AX38 4c register entries this
  phase was created to close were closed in phase-07c-1b (E1, 2026-11-13; scope 1)."
- §0 row title: "[Load at the long-T60 corner, the macOS (d) defect and the growth re-pin (condition 9's split)](phases/phase-07d.md)"
- §0 row notes: "Depends on 07c-1 and 07c-1b `done`. Created 2026-11-12 under phase-07c-1 condition 9's split clause (phase-07c-1
  decision loop, FM-2′; AX49). Owns the 8-instance Windows load ≤ 5 s at the rated corner (scope 6, D-B4 C7′; candidates scope 2, C9
  first), the macOS (d) defect of runs 42 and 44 (scope 7, X-d−) and the AX38 4c growth re-pin from ≥ 6 runs (scope 8, FM-GROWTH;
  Linux's form back to the board if print-only again). The AX38 4c macOS and Windows entries it was created for closed in 07c-1b (E1,
  2026-11-13). Premise P1 (AX38 (iv)): if 07d lands after the first release, phase-13 item 3 fires."

## Summary
| id | ruling | state | confidence | PRD bound | reversal |
|---|---|---|---|---|---|
| Q1 | Linux print-only by the decided proviso; reversal met in substance; re-read at the 07d re-pin, board there if print-only again | reading | high | preamble, NFR-4, NFR-6, RG-F1 | 07d: Linux max/min ≤ 1.10 → asserted |
| Q2 | D-B1 item 6 as decided; reversal met as a record without RT priority; an 08-4 residual with RT priority is the earlier trigger | reading | high | FR-3D-5/6, FR-SIM-7, preamble | 08-4 residual with priority obtained |
| Q3 | Linux, Windows pinned (CHANGELOG), print-only; macOS PROVISIONAL to 07d; label `S2-PINNED` / `S2-PROVISIONAL` now | as decided | high | NFR-6, preamble | 07c-2 / 07d re-pin |
| Q4 | restated as an S2 preview | wording | high | — | 07d |
| Q5 | wording only | wording | high | — | — |

Challenges to settled decisions: none. NEEDS MAISARA: none. Decided for Maisara (open to her veto): FM-GROWTH restated (above;
AMENDS unchanged); D-B1 residual (the Linux CI overruns came from a thread without real-time priority; they follow the decided Phase
13 re-measure; Seat 1 gives most, gets it back at 08-4 with priority shown and at Phase 13; amends nothing); G9 (solve thresholds fixed
on Linux and Windows, provisional on macOS until 07d; amends nothing).
