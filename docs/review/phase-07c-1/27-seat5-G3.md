# 27 — Seat 5 (deadline keeper), G3 / D1 position (phase 07c-1 session 2)

2026-11-12. No option touches the audio thread; none rated 3. Ranking: O4 prefer; O2 (with fixes), O3, O5 (last) can
live with; O6 can live with only if k > 3.53.

| option | now | later | reason |
|---|---|---|---|
| O4 | 0 | 1 | split fixed by scene, identical on every OS; worst 1.72 % (3.3 points of margin); coverage chosen from results |
| O2 | 1 | 2 | deterministic per OS but the evaluated split is decided at run time near 5 % (5.1/5.3/5.6 % cases) and may differ across OSes; six layout-4 cases stay asserted on a degenerate regression (24–98 s), one at 4.76 % |
| O3 | 1 | 1 | static, cheap fit [Hyp]; margin unknown until measured |
| O5 | 1 | 2 | x unsourced; margin chosen on today's results = O2's brittleness |
| O6 | 2 (k ≤ 3.53) / 0 (k > 3.53) | 1 / 2 | static split from scene JSON; k ≤ 3.53 asserts layout 4 and 48 kHz s2 b4 (−11.54 %) fails on every OS |

Evidence: file 23 (per-case values), file 25 (r/r_c), AX5 / CLAUDE.md determinism; runtime [Hyp].
Conditions: O2 — print the conditioning for every case; assert a guard band (no case's conditioning within 4.5–5.5 %);
do not pin the evaluated count beyond the floor; a domain rule from Seat 2 for layout 4, else later stays 2. O5 — x
sourced before the run, margin ≥ 2× cross-OS spread. O6 — k > 3.53 or a second prior condition (e.g. a direct-fraction
ceiling) that excludes layout 4. Premortem: a later tail change turns a meaningless estimator artifact red on one OS.
