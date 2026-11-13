# 5 — Seat 2 position, round 2 (D-B5 (ii) B-iv; (iv″) delta)

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic fact load-bearing.

**Reading.** B-iv replaces RG-1's low-α growth assertion (absolute median ≤ 1.10 × baseline, only inside the ±5 % flutter
window) with a same-run ratio bound (low-α / flutter median ≤ 1.10 × the S2 mean ratio), asserted on Linux and Windows,
printed on macOS. Cue 7: does the instrument see an engine cost change at pinned work? The ratio removes runner speed only for
the share of cost the two scenes have in common.

**Ranking.** B-iv prefer (as conditioned). Under the current form the low-α assertion fires almost never: 1 of 9 OS-runs in
window on the old refs (fact 5) — it detects nothing; B-iv detects something.

**Now: B-iv 1.** Ratio steady (Linux max/min 1.071, Windows 1.096): ≈ 4–6 % headroom to 1.10 × mean at n = 3; flake risk under
"no re-run" Seats 5, 7's.

**Later: B-iv 1 with C1 and C2, else 2.** Blind spots [Inferred]:
- A uniform synthesis slowdown is barely seen: the low-α restore ≈ 95.5 % synthesis (AX38 4c, file 7); RG-1's debt row (×1.65
  moves the ratio by 1.20) implies a flutter synthesis share ≈ 0.54; (0.955f + 0.045)/(0.54f + 0.46) = 1.10 → f ≈ 1.28: a
  common per-op slowdown up to ≈ +28 % passes (printed only, absolute WARNING) — RG-1's debt carried forward, not new.
- A flutter-only slowdown lowers the ratio; a one-sided bound misses it; the flutter backstop (14 × worst ≤ 30 s vs 7.6–10.6 s
  on file) lets that path grow ≈ ×2.8 before red.
- The ratio ties the two scenes: a legitimate change in either forces a ratio re-pin; 07d (L_p ≥ L corner, full synthesis) and
  07c-2 (W_max under (C)) are certain re-pin points; unnamed, a stale ratio goes red as a false (d) defect or gets loosened —
  either scores 2.
- Undo: one constant + CHANGELOG reason. Evidence: S2 runs, 07c-2, 07d, Phase 13 release machines.

**Conditions.** C1: name 07c-2 (W_max change) and 07d (corner synthesis) in the plan as mandatory ratio re-pins, each from ≥ 3
green runs with a CHANGELOG reason. C2: WARNING on both sides (below 1/1.10 × mean as well as above), assert only the upper
side. C3 (keeps 1): use D-B5 (vi) item 3's per-stage split on the S2 runs to state in the plan text the uniform synthesis
slowdown the ratio cannot see (measured, replacing 0.54 / ×1.28).

**(iv″) vs round 1's (iv′).** Unchanged in substance (mean baselines, k = largest max/mean, PROVISIONAL print-only, never a
(d) trigger, same-run ns/eval ratio printed): 1 / 1; S2 runs instead of 41/42/44 an improvement. New gap: "until ≥ 3 in-window
runs exist" has no meaning if B-iv retires the flutter window as the gate (kept only as a printed S2 mean) — the solve
baselines would stay PROVISIONAL forever, no calibrated solve detector until Phase 13. **C4** (keeps later 1): define the exit
from PROVISIONAL under B-iv — ≥ 3 S2-or-later runs within ±5 % of the re-derived flutter mean, or ≥ 3 green runs on unchanged
work pins with k from those runs; without C4, (iv″) later 2.

Evidence: ratios, in-window counts (fact 5) [Observed]; 95.5 % (AX38 4c file 7) [Observed]; ×1.65 / 1.20 (RG-1 debt row, Seat
3, file 70) [Peer-report]; 0.54 and f ≈ 1.28 own arithmetic [Inferred] (C3 replaces); flutter 7.6–10.6 s (AX38 4c) [Observed].
Hand-offs: Seat 5 (flake probability at n = 3); Seat 7 (re-pin runs at 07c-2, 07d); Seat 3 (two-sided print noise); decider
(B-iv a FOR MAISARA amendment via RG-1). Premortem: B-iv without C1 — 07d lowers the low-α restore, the stale ratio sits far
under its mean unread, a later +25 % common synthesis regression passes every run, surfacing only at Phase 13 (Seat 5 first).
Files read: file 4 (D-B5), file 1 (fact 5), 2-seat5 (ii), 2-seat2 (iv), `docs/review/phase-05h/70-…`, BUILD_PLAN L160.
