# Orchestrator computation C4 — (f) with the listener or emitter at the AX6 0.1 m clearance (D-T1, RQ-T1-1)

2026-11-09. Asked by the D-T1 convening round (`9-decider-convene-T1-T2-T6.md`, C4). Data: `tools/validation/data/phase05b2_dt1.json`
section `c4`; tool `tools/validation/phase05b2_dt1.py` (`step_c4`, `near_field_run`). Prototype outside `src/sim`, 4 threads.

## 1. The point estimator near walls (C4 as asked)

Positions: listener at 0.1 m from one wall `(10, 0.1, 1.7)`, an edge `(0.1, 0.1, 1.7)`, a corner `(0.1, 0.1, 9.9)`; emitter at 0.1 m
from a wall; and the reference positions; in the W1 room (AQ10, α 0.15…0.30, s = 0.3) and in Table 5.2 layout 4 at s = 1 (α = 1 floor,
AX22 fallback). Worst AQ9 band. "(f) − ref" = (f) at 32 000 paths against `ref_hybrid` at ℓ = 1.25 m (1 kHz); ref change = its
2.5 → 1.25 m change (max over 500 Hz–2 kHz).

| scene | SE at 8 000 paths (dB) | SE at 32 000 (dB) | largest single-path share | paths for SE 0.083 dB | ms at 32 000 | (f) − ref at 32 000 (dB) | ref change 2.5→1.25 (%) |
|---|---|---|---|---|---|---|---|
| W1_listener_wall | 0.677 | 0.216 | 0.0774 | 217598 | 38 | -0.161 | 0.05 |
| W1_listener_edge | 0.259 | 0.582 | 0.1674 | 1571056 | 41 | +0.208 | 0.31 |
| W1_listener_corner | 0.417 | 0.143 | 0.0536 | 94604 | 47 | -1.060 | 0.65 |
| W1_emitter_wall | 0.029 | 0.015 | 0.0010 | 981 | 42 | -0.013 | 0.05 |
| W1_reference_positions | 0.032 | 0.018 | 0.0013 | 1489 | 33 | +0.002 | 0.05 |
| layout4_s1_listener_wall | 0.228 | 1.657 | 0.3806 | 12746466 | 686 | -0.155 | 0.61 |
| layout4_s1_listener_edge | 0.370 | 0.554 | 0.1124 | 1428006 | 716 | -3.891 | 4.75 |
| layout4_s1_listener_corner | 4.038 | 3.184 | 0.7319 | 47103124 | 779 | +0.160 | 1.18 |
| layout4_s1_emitter_wall | 0.142 | 0.071 | 0.0012 | 23702 | 928 | +0.037 | 0.84 |
| layout4_s1_reference_positions | 0.138 | 0.069 | 0.0012 | 21906 | 839 | -0.088 | 0.09 |

**Readings.** An emitter at 0.1 m costs nothing (scores bounded far from the listener). A **listener** at 0.1 m from walls gives the
heavy-tailed score the researcher derived (dossier F3: bounded by 1/(π d²), tail slope ≈ 5/3): single paths carry 5–73 % of the
estimate at 32 000 paths, and the 32 000-path mean is typically low (MCNP F11 pattern), e.g. −3.9 dB at the layout-4 edge.

## 2. Follow-up runs (orchestrator, same tool; per emitter; 1 kHz)

**Long runs of the point estimator** (unbiased; convergence check):

| scene | 250 k | 1 M | 4 M | SE at 4 M (dB) | time at 4 M |
|---|---|---|---|---|---|
| W1 corner | 1.679e-3 | 1.621e-3 | 1.634e-3 | 0.069 | 5.1 s |
| W1 wall | 2.138e-3 | 2.112e-3 | 2.157e-3 | 0.023 | 4.5 s |
| W1 edge | 1.746e-3 | 1.718e-3 | 1.693e-3 | 0.043 | 4.7 s |
| layout 4 edge | – | 9.17e-5 (SE 0.52) | 1.036e-4 (SE 0.28) | 0.280 | 167 s |

Variance-of-variance at 4 M: 0.010–0.014 (W1; MCNP's limit 0.1). In layout 4 near walls the point estimator does not settle within
minutes: the late window energy comes from rare long-surviving paths (α = 1 floor) passing close to the listener.

**Remedy NW-2: near-field cells** (`near_field_run`: within r_near = 1 m of a near listener image, a hit is gathered through the exact
solid angle of its wall cell of edge h, Ω/(π A), instead of cos θ/(π r²)):

| scene | h | 1 M paths E (1 kHz) | SE at 1 M (dB) | vs point at 4 M |
|---|---|---|---|---|
| W1 wall | 1.0 m | 2.092e-3 | 0.011 | −3.0 % |
| W1 wall | 0.5 m | 2.160e-3 | 0.021 | +0.1 % |
| W1 wall | 0.25 m | 2.130e-3 | 0.030 | −1.2 % |
| W1 edge | 0.5 m | 1.738e-3 | 0.052 | +2.6 % |
| W1 corner | 0.5 m | 1.593e-3 (4 M: 1.619e-3, SE 0.046) | 0.094 | −0.9 % (4 M) |
| layout 4 wall | 0.5 m | 7.92e-5 | 0.136 | – |
| layout 4 edge | 0.5 m | 8.24e-5 | 0.297 | – |

Variance falls by 2–4× at a single wall, little at edges and corners; bias ≲ 1–3 % at h = 0.5–1 m.

**Remedy NW-3: diffuse gather point clamped to ≥ 0.5 m from every surface** (the specular entries and the window keep the true
position; only the point at which the diffuse energy is gathered moves):

| scene | diffuse at 0.1 m (4 M paths) | diffuse at 0.5 m (1 M paths) | E_target change |
|---|---|---|---|
| W1 wall | 1.213e-3 (SE 0.9 %) | 1.227e-3 (SE 0.4 %) | +0.029 dB |
| W1 edge | 9.640e-4 (SE 1.8 %) | 1.001e-3 (SE 0.8 %) | +0.093 dB |
| W1 corner | 8.894e-4 (SE 2.9 %) | 9.118e-4 (SE 1.1 %) | +0.059 dB |
| layout 4 edge | – | 8.34e-5 (SE 0.125 dB at 1 M; 0.51 dB at 32 k) | – |
| layout 4 wall | – | 7.86e-5 (SE 0.068 dB at 1 M; 0.38 dB at 32 k) | – |

In W1 the clamp moves E_target by ≤ 0.09 dB (within ≈ 1–2 SE of the 0.1 m estimate) and cuts the variance by ≈ 4–7× at equal
path count. In layout 4 (α = 1 floor, s = 1, fallback) near walls stay expensive under every remedy (≈ 1 M paths, ≈ 40 s per emitter
in the single-thread-per-core prototype for ≈ 0.1 dB).

## 3. What this means for D-T1 (builder's reading, for the seats to rate)

- Near-listener handling is a sub-decision of D-T1 (call it D-T1.6): NW-1 point estimator with an SE target, MCNP-style diagnostics
  (VOV, tail slope; dossier F8–F11) and a path cap N_max (cap hits recorded and escalated); NW-2 near-field cells (h, r_near);
  NW-3 clamp of the diffuse gather point (ρ). Each changes cost near walls by the factors above; NW-2 and NW-3 add a small, measured bias.
- The reference itself (`ref_hybrid` at 1.25 m) is coarse next to a listener at 0.1 m (its patches are 1.25 m): the "(f) − ref" column
  near walls mixes the reference's ℓ error with (f)'s sampling.


**Reference against the long runs** (1 kHz; the long-run totals include the exact specular part; `ref_hybrid` at 2.5 and 1.25 m):

| scene | ref 2.5 m | ref 1.25 m | point (f) at 4 M paths | (f, 4 M) − ref 1.25 (dB) |
|---|---|---|---|---|
| W1_listener_corner | 1.6674e-03 | 1.6569e-03 | 1.6340e-03 | -0.061 |
| W1_listener_wall | 2.1737e-03 | 2.1726e-03 | 2.1570e-03 | -0.031 |
| W1_listener_edge | 1.7123e-03 | 1.7071e-03 | 1.6930e-03 | -0.036 |
| layout4_s1_listener_edge | 8.3542e-05 | 8.7508e-05 | 1.0360e-04 | +0.733 |
