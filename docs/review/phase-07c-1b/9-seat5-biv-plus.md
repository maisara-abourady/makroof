# 9 — Seat 5 position (B-iv+)

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic fact; corpus not consulted.

**Reading.** Should RG-1's in-window absolute bound (low-α median ≤ 1.10 × baseline on Linux and Windows whenever the run's
flutter median is within ±5 % of the S2-mean flutter) stay on top of B-iv's same-run ratio? Cues: a gate that can go red on
identical code under "no re-run" (criteria 2, 4); a detector whose firing range overlaps its false-red range.

**Ranking (ii) only.** B-iv prefer; B-iv+ as written can live with, only at the 07d re-pin under the conditions; B-iv+ adopted now
on the n = 3 S2 runs 2/2 (not veto-grade: no audio path touched).

**Now: B-iv+ as written 2.** In the window the absolute check reduces to (f/F̄)·(r/r̄) > 1.10 (f run flutter median, F̄ the S2
mean, r the low-α/flutter ratio, r̄ its mean); at the window's upper edge (f/F̄ = 1.05) it goes red once r/r̄ > 1.048. Observed
ratio noise already reaches that (individual ratios not in the files; endpoint bounds): Windows 2.439–2.674 → max/mean 1.030 to
1.062; Linux 2.433–2.606 → 1.023 to 1.046. On Windows a false red on unchanged code lies inside the measured spread at n = 3; on
Linux the margin is 0.2 %–2.5 %. Under "no re-run" every such red is a defect and a `/fix-plan` entry, pushing toward loosening;
it is file 8's own reversal trigger ("a false red on identical code").

**Later: 2.** Narrow detection (RG-1 r3 shares 0.92 / 0.51): a uniform synthesis slowdown k moves flutter by 0.51k + 0.49, so the
run stays in the window only while k ≤ ≈ 1.10 (unless the runner is fast); the in-window check fires only when the ratio rises ≥
1.048, needing k ≳ 1.12 (0.3855k = 0.4335), and only on upper-edge runs; at the lower edge ≈ the ratio's ×1.28. Its added detection
(k ≈ 1.12–1.28 on lucky-edge runs, ≈ 1 in 9 OS-runs in window per fact 5) lives on exactly the runs where its false reds live —
detection gained and flake added are the same mechanism. Undo: one constant + a CHANGELOG row; the real cost is each false red's
investigation and the precedent of loosening. Overturned by the 07d re-pin (≥ 6 runs) and the D-B5 (vi) S2 split (measured k).
B-iv stays 1/1.

**Flake risk under "no re-run".** P(red | identical code) = P(in window) × P((f/F̄)(r/r̄) > 1.10 | in window); P(in window) ≈ 1/6 per
x64 OS-run (fact 5: 1 of 6 Linux and Windows runs); the second factor not estimable at n = 3 — Windows' range reaches the red
region, "not negligible" [Hyp], of order several percent per in-window Windows run. B-iv's ratio bound alone: margin ≥ 3.6 % on
both OSes (1.10 vs max r/r̄ ≤ 1.062).

Evidence: ratio ranges, in-window counts (fact 5) [Observed]; shares 0.92 / 0.51 and k ≈ 1.28 (Seat 3 r2, RG-1 r3) [Peer-report];
edge arithmetic own (the six individual x64 ratios of runs 41, 42, 44 needed to replace the endpoint bounds — orchestrator or
researcher to print them).

**Conditions (B-iv+ 2/2 → 1/1), all four:** (1) adopt only at the 07d re-pin from ≥ 6 green runs (Seat 3's condition); (2) keep
1.10 unchanged and narrow the window: w such that (1 + w) × max(r/r̄) over those ≥ 6 runs leaves a stated margin below 1.10 (today
w ≈ ±2 %: 1.02 × 1.062 = 1.083) — evaluates fewer runs, does not loosen the bound ("never loosen" holds); (3) each in-window
evaluation prints (f/F̄), (r/r̄), their product and the margin as `::warning::` or in the step summary; (4) AX38 4c states the
in-window check covers only k ≈ 1.12–1.28 on upper-edge runs. If 07d's ≥ 6 runs show max(r/r̄) ≥ 1.07, B-iv+ stays 2/2 and the 07d
re-pin should keep B-iv plus the printed absolute growth.

Hand-offs: Seat 3 (does a narrower window still serve its 1/0); Seat 2 (measured k from the S2 split); decider / interrogator (is
narrowing w a change of form under RG-F1). Premortem: B-iv+ now at ±5 % — the first Windows run with flutter near +5 % and a high
ratio goes red on unchanged code; the steward sees an unreproducible GROWTH defect; the next re-pin is pressed to widen 1.10.
