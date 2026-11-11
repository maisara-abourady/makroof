# 40 — Orchestrator: questions from review file 39 for the decider (phase 05h, session 2)

Review file 39 (`/review-phase-pr` on head a9d8313; verdict Request changes; CI green on the head's
fingerprint: run 42924781618, nightly 42924784861) raises one blocker and two majors that are readings of
AX37 (5.4) and AX46, not code slips. They go to the decider (for Maisara where the PRD settles them) under
`docs/board/README.md` "Who answers Maisara's questions"; the interrogator checks the answer; the plan-editor
and the tests follow. Nothing here touches `src/sim`, W_max or a range.

## Q-A — AX37 (5.4): the open_field finite-floor check where the estimator's own SE exceeds τ (blocker 1)

**Plan text.** AX37 (5.4): the double diffuse E_target of `open_field` is checked against the independent
finite-floor single-scatter window integral "compared in the log domain on double values … to D-T1's
tolerance (AX42)", τ = 0.25 dB; phase-05h §5: "the AX37 (5.4) finite-floor check and the −60 dB check (PR CI,
three OSes)". Review file 32 B3 asked for the check at a validation N "where 3·SE ≤ τ" or the form recorded;
d51dde0 added the 2^20-history form (`--diffuse-histories`, validation only) but kept `τ + 3·SE` as the
tolerance in both forms (`tools/acoustics/tests/test_tail.py`, `OPEN_FIELD_TAU_DB`), with no AX / §6 row.

**Evidence (file 39, re-derived by the reviewer at N = 2^20, both s).** 63 Hz–2 kHz: SE 0.020–0.043 dB,
deviation −0.028…+0.005 dB (inside τ). 4 kHz and 8 kHz: SE 0.217 / 0.231 dB (bound τ + 3·SE = 0.90 / 0.94 dB),
deviation +0.366 / +0.285 dB: above τ on their own, z 1.7 / 1.2. The open_field solve at 2^20 histories caps
nothing (`capHit` false). A 2^23-history run (SE ≈ 0.08 dB at 4–8 kHz) is being produced by the orchestrator
(`scratchpad/open_field_2e23.log`; appended below when it lands) to tell noise from an offset.

**Question.** How is AX37 (5.4)'s check to be read and asserted at the bands where the finite-N estimator's SE
is not small against τ? Options the orchestrator sees (the decider ranks and may add): (a) a validation N
large enough that 3·SE ≤ τ in every band (≈ 2^23 at 4–8 kHz; the cap is 2^24; cost ≈ 8× the 2^20 run per s in
the python CI job) and the assertion |dev| ≤ τ; (b) keep N = 2^20 and the additive form |dev| ≤ τ + 3·SE,
recorded as a §6 row / AX37 (5.4) note with the per-band catch printed, consistent with D-H3 (a)'s reading of
a finite-N comparison (a bound of unknown-sign systematic plus 3 SE), the τ-only bands named; (c) (a) for the
bands where it is affordable and (b) above; (d) the shipping-N form stays a smoke test labelled as such
(d51dde0 already does this). Whatever the form, the 4–8 kHz offset, if the 2^23 run keeps it above τ, is a
finding reported for the Expert (NFR-8: not tuned), with its reading: the single-scatter floor integral is
itself a model (one bounce, Lambert, Hann window) and the generic estimator's higher-order floor paths are
real energy; which of the two is "right" is the Expert's, not a gate's. AX42 (τ 0.25 dB) and AX46 (bias 1 %)
are the plan's own numbers; NFR-1 ranks accuracy; D-H1 (v)(d) bars cuts and seams.

## Q-B — AX46: the BRAS pairs' class (major 1)

**Plan text.** AX46 (D-H2 (d)): the bias check "per band and per case class (reference positions, one-end
near-wall, absorbing face, small rooms, 100 m)", on every class with ≥ 1 certified case; "pooled over <n> of
5 classes". AX43's case set lists the 30 BRAS pairs beside the 15 (A) cases, the six Phase 04 rooms, W1/W2 and
the CS-NW+ placements. The export script assigns `CLASSES["bras"] = 5`; the test's per-class loop runs
`cls = 0 … 4`, so the 30 BRAS pairs (90 gated case-bands at 500 Hz–2 kHz, the largest certified group, the
only class whose α comes from measured rooms) enter the pooled additive check and the per-room watch but no
per-class bias line (CI runs 42909003931 and 42924781618 print no bras line); `classDev[5]` is filled and
never read.

**Question.** Where do the BRAS pairs sit in AX46's class table: folded into "reference positions" (they are
the Phase 05 reference positions of real rooms), or a sixth class printed on its own line (then "pooled over
<n> of 6 classes" and AX46's class list amended), or outside AX46 (recorded as excluded with the reason)?
Their per-band means from `agree_full7.log` / the CI logs (the per-class record lines print bras as class 5)
are the evidence; the per-room watch shows no BRAS room with |mean z′| > 3.

## Q-C — AX46: the class SE form and the near-wall class (major 2)

**Plan text.** AX46: "The test N is pre-registered so that 3·SE ≤ 1 % − ℓ_ref (near-wall class: ℓ_ref 0.65 %,
so SE ≈ 0.12 % ≈ 0.005 dB; CI time only)"; the test evaluates a class-band only when 3·SE_class ≤ 1 % −
max ℓ_ref over the class, with SE_class = the empirical standard error of the per-case deviations (`Stat::se`).

**Evidence (file 39).** With the nine near-wall cases certified (410 gated), the near_wall class SE is
0.148–0.160 % (nine cases; 3·SE 0.44–0.48 %) against a budget 1 % − max ℓ_ref = 0.31–0.43 % in bands 2–7, so
those bands print "not evaluated (pre-registered N insufficient)"; bands 0–1 (max ℓ_ref 0.47 / 0.53 %) are
evaluated (means −0.136 / −0.157 %). The empirical class SE is the spread of per-case deviations, which
carries each reference's own ℓ_ref (0.47–0.69 %) as well as the estimator's ≈ 0.2 % per case; raising N
cannot drive it under the budget if the reference scatter dominates (reviewer's reading; Q1 of file 39 asks
for a 4·N run of the nine cases to confirm). D-H3 (a) read the same situation for the pooled check and chose
the additive bound: |mean dev| ≤ 3·SE_pool + mean ℓ_ref with SE_pool from the estimator SEs
(sqrt(mean SE²/M)), the reference uncertainty entering as a mean, not through the spread.

**Question.** Which SE does AX46's "3·SE ≤ 1 % − ℓ_ref" mean for a class: the estimator-propagated class SE
(sqrt(mean SE_i²)/√n, the quantity the sentence sized N for, ≈ 0.07 % at nine cases) with ℓ_ref entering as
the class mean (the D-H3 (a) form), or the empirical spread (the present code), or the empirical spread with
the budget against the mean ℓ_ref rather than the max? The near-wall class then is evaluated or not in bands
2–7 accordingly; nothing is widened: the 1 % limit and τ stand.

## Constraints

PRD NFR-1 (accuracy), NFR-6 / AX5 (determinism), NFR-8 (no scene-specific logic); AX36/AX42/AX46 as written;
D-H1 (v)(d) (no W_max cut, no range change, no seam); D-H2 (d) and D-H3 (a) as decided; the one-phase rule
(any larger reference work is phase-05i's). Each answer needs: the reading, the PRD / AX ids, the options with
the seats' likely cells only where a seat must be convened (the decider says which, if any), the AMENDS line
where a recorded decision is amended, and the exact plan text and test form for the plan-editor and the
orchestrator.

## Evidence appended by the orchestrator (from `agree_full7.log`, the final local run of the extended set; the CI runs print the same lines)

**Q-B, the BRAS class (class 5, 30 pairs, bands 3–5 certified):** per-class record lines "bras: mean z +0.576 /
+0.558 / +0.576, mean z′ +0.598 / +0.587 / +0.595 over 30 (3/√M 0.548)" at 500 Hz / 1 kHz / 2 kHz: inside
3/√M as a record; no BRAS room with |mean z′| > 3 in the per-room watch. No AX46 class line is printed for it.

**Q-C, the near-wall class in both SE forms (nine certified cases):**

| band | mean dev | empirical class SE (present code) | estimator-propagated class SE (√(mean SE²)/√n) | ℓ_ref max | ℓ_ref mean | evaluated now? |
|---|---|---|---|---|---|---|
| 0 | −0.136 % | 0.139 % | 0.078 % | 0.474 % | 0.162 % | yes |
| 1 | −0.158 % | 0.145 % | 0.077 % | 0.532 % | 0.181 % | yes |
| 2 | −0.170 % | 0.149 % | 0.076 % | 0.567 % | 0.192 % | no |
| 3 | −0.182 % | 0.152 % | 0.075 % | 0.599 % | 0.203 % | no |
| 4 | −0.192 % | 0.155 % | 0.074 % | 0.628 % | 0.213 % | no |
| 5 | −0.202 % | 0.157 % | 0.074 % | 0.653 % | 0.221 % | no |
| 6 | −0.210 % | 0.159 % | 0.073 % | 0.675 % | 0.229 % | no |
| 7 | −0.218 % | 0.161 % | 0.072 % | 0.694 % | 0.236 % | no |

The empirical spread is about twice the estimator-propagated SE (the per-case deviations carry each
reference's own ℓ_ref, 0.47–0.69 % at the 0.1 m placements), so a larger N cannot close bands 2–7 under the
present form (file 39 Q1 answered from the data: the estimator part is 0.07 %, the rest is reference
scatter). In the D-H3 (a) form (3 · propagated SE + mean ℓ_ref ≤ 1 %: 0.23 % + 0.24 % = 0.47 %) every band
is evaluable and the class means (−0.14…−0.22 %) are inside 1 % by 4.6×. The other classes: reference 19
cases (SE 0.027–0.032 %, ℓ_ref max ≤ 0.29 %, evaluated, means −0.03 %), absorbing 12 cases (SE 0.125 %, ℓ_ref
max 0.325 %, evaluated, mean −0.227 %), small 'reference pending' (AX45's two small-room cases are in the AX45
suite), 100 m the tracer line.

## 2^23 result (open_field, `render_cli --diffuse-histories 8388608`, Release, Linux; the independent floor integral as in the pytest; 213 s per s value on this box, against ≈ 27 s at 2^20)

```
s 0.4 emitter L n 8388608 capHit False (213 s)
  band 0: dev -0.002 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 1: dev -0.002 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 2: dev -0.002 dB  SE 0.008 dB  3SE 0.025  |dev|<=tau True  |dev|<=tau+3SE True
  band 3: dev -0.000 dB  SE 0.012 dB  3SE 0.037  |dev|<=tau True  |dev|<=tau+3SE True
  band 4: dev +0.000 dB  SE 0.015 dB  3SE 0.044  |dev|<=tau True  |dev|<=tau+3SE True
  band 5: dev +0.001 dB  SE 0.033 dB  3SE 0.099  |dev|<=tau True  |dev|<=tau+3SE True
  band 6: dev -0.019 dB  SE 0.073 dB  3SE 0.220  |dev|<=tau True  |dev|<=tau+3SE True
  band 7: dev -0.020 dB  SE 0.073 dB  3SE 0.220  |dev|<=tau True  |dev|<=tau+3SE True
s 0.4 emitter R n 8388608 capHit False (213 s)
  band 0: dev +0.001 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 1: dev +0.001 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 2: dev +0.000 dB  SE 0.008 dB  3SE 0.025  |dev|<=tau True  |dev|<=tau+3SE True
  band 3: dev -0.000 dB  SE 0.012 dB  3SE 0.037  |dev|<=tau True  |dev|<=tau+3SE True
  band 4: dev -0.000 dB  SE 0.015 dB  3SE 0.044  |dev|<=tau True  |dev|<=tau+3SE True
  band 5: dev -0.000 dB  SE 0.033 dB  3SE 0.100  |dev|<=tau True  |dev|<=tau+3SE True
  band 6: dev +0.005 dB  SE 0.076 dB  3SE 0.229  |dev|<=tau True  |dev|<=tau+3SE True
  band 7: dev +0.005 dB  SE 0.076 dB  3SE 0.229  |dev|<=tau True  |dev|<=tau+3SE True
s 0.5 emitter L n 8388608 capHit False (212 s)
  band 0: dev -0.002 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 1: dev -0.002 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 2: dev -0.002 dB  SE 0.008 dB  3SE 0.025  |dev|<=tau True  |dev|<=tau+3SE True
  band 3: dev -0.000 dB  SE 0.012 dB  3SE 0.037  |dev|<=tau True  |dev|<=tau+3SE True
  band 4: dev +0.000 dB  SE 0.015 dB  3SE 0.044  |dev|<=tau True  |dev|<=tau+3SE True
  band 5: dev +0.001 dB  SE 0.033 dB  3SE 0.099  |dev|<=tau True  |dev|<=tau+3SE True
  band 6: dev -0.019 dB  SE 0.073 dB  3SE 0.220  |dev|<=tau True  |dev|<=tau+3SE True
  band 7: dev -0.020 dB  SE 0.073 dB  3SE 0.220  |dev|<=tau True  |dev|<=tau+3SE True
s 0.5 emitter R n 8388608 capHit False (213 s)
  band 0: dev +0.001 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 1: dev +0.001 dB  SE 0.007 dB  3SE 0.022  |dev|<=tau True  |dev|<=tau+3SE True
  band 2: dev +0.000 dB  SE 0.008 dB  3SE 0.025  |dev|<=tau True  |dev|<=tau+3SE True
  band 3: dev -0.000 dB  SE 0.012 dB  3SE 0.037  |dev|<=tau True  |dev|<=tau+3SE True
  band 4: dev -0.000 dB  SE 0.015 dB  3SE 0.044  |dev|<=tau True  |dev|<=tau+3SE True
  band 5: dev -0.000 dB  SE 0.033 dB  3SE 0.100  |dev|<=tau True  |dev|<=tau+3SE True
  band 6: dev +0.005 dB  SE 0.076 dB  3SE 0.229  |dev|<=tau True  |dev|<=tau+3SE True
  band 7: dev +0.005 dB  SE 0.076 dB  3SE 0.229  |dev|<=tau True  |dev|<=tau+3SE True
```

At 2^23 histories the 4–8 kHz deviation is −0.020 / +0.005 dB (SE 0.073–0.076 dB, 3·SE 0.22–0.23 dB ≤ τ 0.25 dB in every band): the +0.29 / +0.37 dB of the 2^20 run was noise (z ≤ 1.7), not an offset; every band is inside τ on its own at this N. s 0.5 (both emitters) reads the same: every band inside τ, 3·SE ≤ τ at 4–8 kHz.

## The floor integral's quadrature ladder (the integral's ℓ_ref; decider file 44 Q3, the record the decider asked for; 2026-11-11)

`ground_scatter.window_target` is a continuous quadrature (r log-spaced over n_r shells to the floor's edge, n_phi azimuths; each element at its exact arrival time; "per 10 ms" is the normalisation only), so its discretisation residual is the (n_r, n_phi) grid, not a time bin. Halving the grid twice on `open_field` (s 0.4, both emitters identical):

```
emitter L (11 s): per band  (4000x720 -> 8000x1440) %  |  (8000x1440 -> 16000x2880) %  | dB(4000->16000)
  band 0: -0.00533 %   +0.00341 %   -0.000083 dB
  band 1: -0.00575 %   +0.00375 %   -0.000087 dB
  band 2: -0.00703 %   +0.00489 %   -0.000093 dB
  band 3: -0.01172 %   +0.01069 %   -0.000045 dB
  band 4: -0.01341 %   +0.01413 %   +0.000031 dB
  band 5: -0.00827 %   +0.04273 %   +0.001496 dB
  band 6: +0.08975 %   +0.11217 %   +0.008764 dB
  band 7: +0.08978 %   +0.11218 %   +0.008767 dB
emitter R (12 s): per band  (4000x720 -> 8000x1440) %  |  (8000x1440 -> 16000x2880) %  | dB(4000->16000)
```

The integral's ℓ_ref (the finer halving, 8000×1440 → 16000×2880) is ≤ 0.014 % at 63 Hz–1 kHz, 0.043 % at 2 kHz and 0.11 % (0.0049 dB) at 4–8 kHz; the whole ladder moves the integral by ≤ 0.0015 dB at 63 Hz–2 kHz and ≤ 0.009 dB at 4–8 kHz (orchestrator's transcription corrected 2026-11-11 on the plan-editor's D1: the earlier '≤ 0.0004 %' read the dB column as %): 1/28 of τ and below the 2^23 run's |dev| ≤ 0.020 dB, which therefore bounds Monte Carlo noise plus a quadrature residual of at most 0.009 dB. A record, not a gate (AX42's reversal form, a change > τ/2, is nowhere near).
