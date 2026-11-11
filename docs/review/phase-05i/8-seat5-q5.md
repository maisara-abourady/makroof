# 8 — Seat 5 (deadline keeper): Q5, the solve-median bound k (interrogator P05I-37)

Phase 05i, 2026-11-11. Seat 5's output, saved verbatim by the orchestrator (the seat only reads).
Files read: file 4 Q5; file 5 Q5 and its summary; file 6 P05I-28…P05I-38; phase-05h §5 L366–406; phase-05i §3 L77–94; phase-05h file 57 (rounds 1–3); `tests/unit/test_diffuse_records.cpp` L64–116 and L506–549 (from the code). There is no acoustic claim, so the corpus is not needed.

SEAT 5 POSITION

**1. Reading.** Q5 asks which factor k and which baseline define a new print-only `SOLVE` WARNING on the RG-1 GATE line, and what that costs in false warnings, each of which must be named in a PR. It touches three of my cues:
- WI-3: calibrate the instrument against reality. A warning that fires on weather trains reviewers to type "runner".
- My own file 57 r2 (v): never a red or out-of-window run as a baseline. That rule is now settled as phase-05i §3.3 (v).
- My §17 blind spot: a record nobody reads.

The solve runs on the builder or host thread, never the audio callback (AX38 (i)), so criterion 1 is not at stake. Criteria 3–5 are: the CI gate's signal and the PR's cost.

**2. Ranking.** The in-window runs are those within ±5 % of the flutter reference (`kGuardPct = 5.0`, test L89): Linux 43007183782 only; macOS 43007183782 only; Windows 42964823518 and 43007183782.
- **A. Prefer.** k = 1.20 on the in-window baseline, PROVISIONAL. Baselines Linux 80.9 / 131.2, macOS 83.7 / 102.7, Windows 90.40 / 144.40 ms (low-α / flutter). Thresholds 97.1 / 157.4, 100.4 / 123.2, 108.5 / 173.3 ms.
- **B. Can live with.** k = 1.30 on the same baseline. Thresholds 105.2 / 170.6, 108.8 / 133.5, 117.5 / 187.7 ms.
- **C. Can live with.** k = 1.15 on the same baseline. Thresholds 93.0 / 150.9, 96.3 / 118.1, 104.0 / 166.1 ms.
- **D. Can live with.** No token until the 07c re-pin; values printed only.
- **E. Barred by settled text, not by my veto.** k = 1.20 on the 3-run mean (file 5). This was my own (c) objection in file 57.

**3. Tension now.**
- **A: 0.** Against the in-window baseline, 0 of the 18 cell-runs on file are over at k = 1.20, 1.15 or 1.30. The largest observed/baseline ratio is 1.036 (Windows flutter, 149.6 / 144.40). macOS flutter, predictive with σ from n = 3 (SD 12.41, mean 96.77): t(2) = (123.2 − 96.77) / (12.41·√(4/3)) = 1.84, P ≈ 0.10, about 1 warning in 10 runs (about 1 in 60 with σ known and a normal spread). The other five cells have CV ≤ 2.1 %, so 1.20 sits 10 or more SD above the mean; their rate is about 0.
- **B: 0.** macOS flutter t = 2.56, P ≈ 0.06 (1 in 16). On x64 a solve regression must exceed about +30 % before it prints, about +14 × 27 ms ≈ 0.4 s on Windows low-α's 14 × worst; that line is already printed, so nothing is lost now.
- **C: 1.** macOS flutter t = 1.49, P ≈ 0.14 (1 in 7). 1.15 is the defect-trigger family (`kMacGrowthTriggerMs`); a reader of the GATE line can mistake a print for a (d) trigger.
- **D: 1.** Leaves §3.3 (iv) undone, which needs a `/fix-plan` amendment; without a printed bound every PR reviewer compares `solveMedianMs` with file 4 by eye.
- **E: 2.** Its baseline includes runs that §3.3 (v) bars. The macOS flutter threshold drops to 116.1, about 1 in 6.5 warnings (P05I-33).

**4. Tension later (the debt).**
- **A: 1.** A one-run baseline (two runs on Windows) holds until the 07c re-pin; undoing it costs a constant plus a CHANGELOG line. The risk is a baseline that was a low draw. macOS flutter's in-window run is the high draw (102.7 against 82.5), so there the threshold is effectively 1.27 × the 3-run mean, erring towards missing a regression rather than warning falsely. Evidence arrives from every 05i/06/07 PR's GATE lines and is overturned at the 07c re-pin from ≥ 3 in-window runs.
- **B: 1.** Same debt as A; weaker on x64 if 07c's synthesis move shifts the solve.
- **C: 1.** Same debt as A, plus a recurring PR line on macOS at about 1 in 7.
- **D: 1.** Nothing lost (07c derives k from the same printed values), but each PR's §0 count has no SOLVE column until then.
- **E: 2.** The creeping-baseline pattern (file 57 (c)): each slow-runner run that enters the mean moves the bound.

**5. Evidence.** Per-cell values and flutter deviations: file 4 L69–77 [Observed]; means, SDs, CVs redone, agree with P05I-29, P05I-33, P05I-34. In-window membership from `kGuardPct` = 5 (test L89, from the code) and the flutter deviation (file 4 L77). The flutter deviation does not predict the solve time (P05I-35; file 57 r2 (iii) found the same for macOS) [Observed], so SOLVE prints regardless of the window: not suppressed as `NOT EVALUATED`, no runner attribution. The flutter GATE line has no `warnings=` field today (test L534–538, from the code). t(2) tails assume roughly normal per-run noise [Hyp].

**6. Conditions of acceptance.**
- **For A (keeps it at 0 / 1):** a named constant `kSolveWarn = 1.20`, separate from `kRatioWarn` so 07c can re-derive each on its own; a field `solveRefMs` in `GateEntry` on all six rows; print `solveWarnAt=%.1f` and `solveBasis=PROVISIONAL(n=1|2)` on both scene lines; `SOLVE` in the scene's own `warnings=` (this adds a `warnings=` field at the end of the flutter line, additive); one-sided (the work pins already guard against a fast solve); SOLVE never enters (d) and is never a trigger; counted in §0 apart from the in-window/out-of-window status; one cell printing SOLVE in-window on 2 runs with `nsPerEval`'s work and the pins unchanged is an instrument-calibration finding (WI-3), not a defect.
- **C, 1 → 0:** use 1.20; if the board takes 1.15, only on x64, macOS at 1.20.
- **D, 1 → 0:** not reachable without amending §3.3 (iv).
- **E, 2 → 1:** restrict to in-window runs, which turns it into A.

**7. Hand-offs.** Decider: whether the flutter-line `warnings=` field fits Q5's `/fix-plan` slot or is separate test scope in 05i. Seats 2 and 3: whether `nsPerEval` stays invariant across 07c's synthesis move (re-pin the solve baseline or only re-derive k). Interrogator: the t(2) arithmetic above.

**8. Premortem.** If E or C is adopted and fails: macOS prints SOLVE on about 1 in 7 runs, PR authors write "runner" by reflex, and a real solve regression in 07c is waved through. The contractor notices first, when Linux low-α's printed 14 × worst crosses 30 s again.
