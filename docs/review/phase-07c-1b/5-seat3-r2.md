# 5 — Seat 3 position, round 2 (D-B5 (ii) B-i … B-iv, (iv″))

2026-11-13. Saved by the orchestrator from the seat's report. No acoustic fact (corpus not consulted); records plus own
arithmetic. Read: file 4 (D-B5), file 1 fact 5, 2-seat5 (ii), (iv), 2-seat2 (iv), RG-1 05h/58 (rounds 1–5), 05h/70, BUILD_PLAN
L160.

**Reading.** Which hosted-runner form keeps a working detector for a synthesis or solve regression in the restore until 07d /
Phase 13? Cue: cost (a CPU figure is meaningful only on a named machine). Underneath: a gate never evaluated — Linux flutter
medians 453 / 490 / 706 put none in the ±5 % window, so today RG-1's in-window absolute bound sees nothing; the seat's RG-1 1/1
rested on it ("sees the synthesis from ×1.1 on a nominal runner", 05h/58 r3).

**Ranking.** **B-iv+** (own composition) prefer: B-iv as written **and keeps** RG-1's in-window absolute bound (1.10 × baseline,
asserted on Linux and Windows whenever the flutter median falls inside the ±5 % window re-derived from the S2 mean). B-iv can
live with. (iv″) prefer. B-iii can live with, nominally. B-i, B-ii can live with, lowest. Nothing veto-grade (no option touches
the audio).

| option | now | later | cost and debt |
|---|---|---|---|
| B-iv+ | 1 | 1 | now: the ratio bound from n = 3 (Linux 1.071, Windows 1.096 max/min); an edge run could be red under "no re-run"; later: macOS has only the M-a trigger until Phase 13 (accepted in RG-1); nothing loosened (an assertion added, none removed); undo one constant |
| B-iv | 1 | 2 | ratio asserted every run but detects a synthesis regression only from ≈ ×1.28 (low-α share 0.92, flutter 0.51, RG-1 r3: (0.92k + 0.08)/(0.51k + 0.49) = 1.10 → k ≈ 1.28); the ×1.1 absolute detector drops to a print; an ISM or solve slowdown lowers the ratio (one-sided bound blind); 07d could size its remedy on a synthesis cost 25 % grown unasserted; undo a test edit; overturned by D-B5 (vi) item 3's split |
| B-iii | 1 | 2 | honest width ≈ ±22 %; off-window runs move low-α more than flutter (2 of 3 in RG-1), so 1.10 inside ±22 % produces false defects, each sending 07d after a non-existent regression (X-a later 2), then pressure to loosen |
| B-i | 1 | 2 | no run left in the window (453 / 490 / 706 vs mean 550): no x64 timing assertion, possibly until Phase 13 — RG-1's "no synthesis detector until Phase 13 → 2"; more manual runs (Seat 7) |
| B-ii | 1 | 2 | as B-i: one run (490) in window |
| (iv″) | 0 | 1 | solve ≈ 5 % of the low-α restore, work pinned (W_pilot / W_final): print-only costs nothing now; same-run ns/eval ratio within 1 % over three runs (Seat 2: 0.584–0.588 Linux, 0.585–0.592 Windows), better than the RG-1 worry; debt: PROVISIONAL may never end if "in-window" keeps the flutter ±5 % meaning |

Evidence: ratio steady across x64 runners (Linux 2.433–2.606, Windows 2.439–2.674) while flutter medians move +44 % [Measured,
fact 5]; shares 0.92 / 0.51 [Measured on 05h code, RG-1 r3], on 07c-1b code [Hyp] (cond. 9 / AX49 interim; at flutter L_p < L,
so flutter's synthesis share has probably fallen, making the ratio more sensitive) — the D-B5 (vi) split settles it; macOS
3.32–5.05 a macOS-specific load, print-only right.

Conditions: B-iv → 1/1: AX38 4c states in words the uniform synthesis slowdown at which the ratio crosses 1.10, from the S2
split; if that k > ×1.4, B-iv stays 1/2 and only B-iv+ reaches 1/1; each run prints a WARNING when the ratio falls below mean /
1.10 (ISM / solve regressions), never asserted. B-iv+ → 1/0: at the 07d re-pin the ratio bound re-derived from ≥ 6 runs (S2
plus 07d's). B-iii → 1/1 only with window ≤ ±7 % and bound 1.10 (the spread rules it out: no acceptable form). B-i / B-ii →
1/1 only with B-iv's ratio as the detector every run (= B-iv+). (iv″) → 0/0: exit from PROVISIONAL = ≥ 3 green S2 runs whose
ns/eval ratio is within 1.05 of its mean (not flutter-in-window), or named at Phase 13 on release machines; the same-run ns/eval
ratio becomes an asserted runner-free check at that exit.

Hand-offs: Seat 5 (flake rate of a 1.10 ratio bound at n = 3); decider / interrogator (is B-iv+ a FOR MAISARA amendment of
RG-1 at all — it removes nothing, so "never loosen" holds); Seat 7 (cost of B-i / B-ii runs); Seat 2 (does the ns/eval ratio hold
once 07c-2 changes the work). Premortem: B-iv alone; a `BandNoiseGenerator` change in 07d makes synthesis ×1.25 slower on every
OS, the ratio moves +9 %, green; only a printed WARNING; 07d's 5 s criterion sized on a cost a quarter heavier; first noticed
by the steward reading record (h) in 07d, or Maisara at Phase 13 as slower loads.
