# 5 — Seat 6 position, round 2 (D-B5 (ii) B-i … B-iv, (iv″))

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic claim. Read: file 4 §D-B5; file 1 fact 5; 2-seat5 (ii),
(iv); 2-seat2 (iv); 2-seat6; RG-1 files 60, 70; BUILD_PLAN L160, L503; phase-07c-1b scope 1.

**Reading.** How the 07c re-pin arms the low-α growth check now that the ±5 % in-window rule keeps fewer than 3 runs on every
OS ("never a red or out-of-window run as a baseline" applies to every OS). The gate is the only CI detector of project-open time
(NFR-6, the preamble's "usable"), felt on every load. Cues: W3 (an instrument that never arms is silence), K24 (a fired trigger
unread), E5 (say plainly where the instrument stops). Also the "repaid when" of the seat's RG-1 debt row (file 70: "repaid when
07c re-pin").

**Ranking.** B-iv prefer, on conditions; (iv″) prefer; B-i, B-ii can live with; B-iii can live with at 2; nothing veto-grade (a
CI gate, not a user control).

- **B-i 1 / 2:** Linux 453 / 490 / 706 around 550 leaves none inside ±5 %: no OS armed, RG-1 debt not repaid; later 07d changes
  the restore path (C1, C6) — exactly when a growth detector matters — and it reaches 07d unarmed, likely still at Phase 13;
  undo one `/fix-plan` edit; evidence 07d's runs.
- **B-ii 1 / 2:** one run (490), not 3; same outcome and debt.
- **B-iii 2 / 2:** honest window ≈ ±22 % on Linux (Seat 5); a fixed 1.10 bound inside it reds a 20 % slow runner on identical
  code; under "no re-run" each red is a (d) round, ≈ half a session (file 60); repeated reds teach readers to explain triggers
  away (K24 again); later the same flakiness through 07d and 08.
- **B-iv 1 / 1 on conditions:** a within-run ratio cancels runner speed; S2 spreads so far Linux 2.606 / 2.433 = 1.071, Windows
  2.674 / 2.439 = 1.096: armed and readable. Cost now: the hosted assertion stops seeing a slowdown hitting both scenes equally
  (e.g. the shared noise synthesis — the one most likely to lengthen every load); only the flutter 14 × worst ≤ 30 s backstop
  (today 6.57 / 8.39 / 12.56 s: catches only ≈ ×2.4–×4.6) and the absolute WARNING catch it. Later: 07d's C1 may speed the scenes
  unequally and shift the ratio: a 07d re-pin is owed; undoing B-iv costs a FOR MAISARA `/fix-plan` round. Without (a), (b): 1 / 2.
- **(iv″) 0 / 1:** S2-mean baselines honest, PROVISIONAL, never a trigger; later 1: "until ≥ 3 in-window runs exist" can stay true
  forever on macOS and Windows — a record nobody reads (W3).

Evidence: ratios, in-window shortfall (fact 5) [Obs]; Linux medians, ±22 % (2-seat5 (ii)) [Obs]; ns/eval steady to 1 % (2-seat2
(iv)) [Obs]; flutter figures (phase-07c-1b scope 2) [Obs]; cost of a false red (file 60) [Inf]; the ratio's blind spot (RG-1
hand-off to Seats 2, 3, file 60 §7) [Inf]; silence is not approval {Obs; FF-forum-float} W3. **Margin arithmetic:** the mean ≥
the minimum, so the largest run's ratio to the mean ≤ max/min; worst case the 1.10 × mean bound sits only 1.10 / 1.096 = +0.4 %
above the largest Windows run so far (Linux +2.7 %); how often a 4th run crosses it [Hyp] — Seat 5 to print each S2 run's ratio
and margin.

Conditions: **B-iv → 1/1:** (a) AX38 4c states plainly "the hosted growth assertion detects a scene-specific slowdown; a uniform
slowdown is printed (GROWTH) and asserted only at 30 s and at Phase 13"; (b) the absolute GROWTH WARNING to
`$GITHUB_STEP_SUMMARY` on every OS (D-B5 (vi) item 5) and counted per run in §0; (c) the ratio re-derived from S2 runs in 07d
after its remedy lands; (d) the GATE line prints each S2 run's ratio and its margin to the bound. B-i / B-ii → 1/1 only with
B-iv's ratio as the armed detector (they become the print window rule). B-iii → 1/1 print-only, never asserted (Seat 5's
fallback, not B-iii as stated). (iv″) → 0/0: PROVISIONAL has an end — "in-window" takes (ii)'s adopted rule, or baselines
re-derived on Phase 13 release machines, date named.

Hand-offs: Seat 5 (false-red rate at 1.10 with n = 3; step-summary format); Seats 2, 3 (shared synthesis hiding a real
regression); Seat 7 (amendment round cost; does B-iv loosen under "never loosen"); decider (FOR MAISARA wording for the RG-1
amendment). Premortem: B-i or B-ii — 07d's C1 / C6 lengthens every restore by 15 %, nothing armed, GROWTH scrolls past; Seat 8's
beta tester opening an 8-stem project notices first.
