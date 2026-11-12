# 29 — Seat 2 (engine architect), G3 / D1 position (phase 07c-1 session 2)

2026-11-12. Proposed **O7′** (prefer): one fixed rule on the exact (reference) band IR only, before any comparison: EDT
asserted where the direct-sound step of the EDC, S = −10·log10(1 − d), is ≤ 5 dB (half the 0 … −10 dB fit range; d ≤ 0.68),
d = energy within ±5 ms of the band peak / total (file 23). Others print "not evaluated (outside EDT domain: direct step
S dB)" with their level steps (asserted ≤ 1 dB). No "half" floor.

| option | now | later | reason |
|---|---|---|---|
| O7′ | 0 | 0 | asserts 30 of 40 (layout 5, cube, CR3), worst 3.53 %; same rule carries to Phase 10 non-circularly (d on the measured IR) |
| O2 | 2 | 2 | a sensitivity probe, not a domain test; asserts 24–98 s "EDTs"; asserted set changes with seed |
| O3 | 1 | 2 | not circular, but a window from onset keeps layout 4's step; one after it is no longer EDT |
| O6 | 2 | 2 | wrong gate: diffuse-field d = 1/(1 + (r/r_c)²) predicts 0.074 / 0.040 / 0.127 / 0.23–0.27 vs measured 0.83–0.90 / 0.18–0.27 / 0.27–0.33 / 0.26–0.38 (layout 4 / 5 / cube / CR3); no k reproduces the order |
| O4 | 2 | 2 | scope chosen from results; drops the cube; "drop the scene that fails" precedent (vs NFR-8) |
| O5 | 2 | 2 | invented x; duplicates AX47's level bound; meaningless measured vs simulated |

Evidence: Kuttruff §5.6 Eqs. 5.44–5.45 (arithmetic redone), §5 case 4 (absorbing floor non-diffuse), §8.4 (the direct
share of the decay curve is what the criterion protects); file 23: steps 7.8–10.0 dB in layout 4, ≤ 2.07 dB elsewhere, so
any S_max in 2.1–7.7 dB (d_max 0.38–0.83) gives the same partition — not fitted to the results; 5 dB = half the fit range
[Inferred]; ISO minimum distance ≈ 2√(V/(cT)) ≈ 1.9 r_c [Hyp, researcher R1]. O2's probe overstates the actual
perturbation ~20× in the cube (eps ≈ 7e-4 → 0.003 dB).
Conditions: C2 O2 behind O7's domain check, probe sized to per-band eps → 1/1; C3 O3 print-only companion → 1/1; C6 O6 with
d instead of r/r_c (= O7) → 0/0; C4 O4 stated as O7's rule, cube kept → 0/0; C5 O5 sourced or print-only → 1/1.
Premortem: Phase 10 reports "EDT within jnd" at a BRAS position whose EDC is a fitted step.
