# Orchestrator computations after the D-T1 seat round: NW-4 (reciprocal start), small-room reference ladder, band correlation

2026-11-09. Requested by the seats' D-T1 positions (`18-seat*-T1-T2*.md`): Seat 2 proposed **NW-4**; Seats 2 and 9 asked for the
reference ℓ ladder in small rooms; Seat 1 asked for the cross-band correlation of (f)'s errors. Prototype outside `src/sim`
(`tools/validation/phase05b2_dt1.py`, 4 threads); 1 kHz unless stated.

## 1. NW-4: start the paths at the listener, gather at the emitter's images (reciprocity)

The diffuse transport of the model is reciprocal (Lambert and specular kernels symmetric; air and window depend on total path length),
so the same estimator with emitter and listener swapped estimates the same E_target. Implemented as `paths_run` with `src` and `rcv`
swapped and the plan (window, t_mix,e) of the true positions.

| scene (listener at 0.1 m) | forward (point) SE at 32 k | NW-4 SE at 32 k | NW-4 at 256 k | NW-4 vs the long forward run | largest path share (NW-4, 32 k) |
|---|---|---|---|---|---|
| W1 wall | 0.216 dB | 0.014 dB | 2.1702e-3 (SE 0.005) | +0.026 dB (forward 4 M: SE 0.023) | 0.0008 |
| W1 edge | 0.582 dB | 0.015 dB | 1.7002e-3 (SE 0.005) | +0.018 dB (forward 4 M: SE 0.043) | 0.0009 |
| W1 corner | 0.143 dB | 0.013 dB | 1.6476e-3 (SE 0.005) | +0.036 dB (forward 4 M: SE 0.069) | 0.0009 |
| layout 4, s = 1, wall | 1.657 dB | 0.072 dB | 8.055e-5 (SE 0.025) | – | 0.0016 |
| layout 4, s = 1, edge | 0.554 dB | 0.067 dB | 8.831e-5 (SE 0.024) | −0.69 dB vs forward 4 M (SE 0.28, heavy tail); **+0.04 dB vs ref_hybrid 1.25 m (8.75e-5)** | 0.0013 |
| layout 4, s = 1, corner | 3.184 dB | 0.069 dB | 8.814e-5 (SE 0.024) | – | 0.0015 |

Readings: with the listener at a wall the reciprocal start removes the heavy tail entirely (SE at 32 k equals the reference-position
SE; single-path shares ≤ 0.16 %); it agrees with the long forward runs within their SE in W1 and with ref_hybrid at the layout-4 edge,
where the forward 4 M-path run was still biased by its tail. NW-4 is unbiased and changes no model. Its cost moves the problem to the
start end: an **emitter** at 0.1 m from a wall is cheap under the forward start (C4: SE 0.015 dB) and is the expensive end under NW-4.
A path set started at the listener serves both emitters (one NEE per emitter per hit). Layout-4 timing at 32 k paths: 1.7–3.6 s
(4 threads, prototype).

## 2. Small-room reference ladder (Seats 2, 9: ℓ = 2.5 m ≥ the room's dimensions)

`ref_hybrid` E_target (1 kHz) at ℓ = 2.5 / 1.25 / 0.625 / 0.3125 m (patches) against (f) at 1 M paths:

| room | dims (m) | 2.5 m | 1.25 m | 0.625 m | 0.3125 m | (f), 1 M paths |
|---|---|---|---|---|---|---|
| dead_booth | 2.5 × 2.0 × 2.2 | 0.784218 (6) | 0.785574 (24) | 0.787778 (96) | 0.788423 (352) | 0.788825 (SE 0.0006 dB) |
| living_room | 5.0 × 4.0 × 2.6 | 0.487498 (24) | 0.484897 (80) | 0.484493 (262) | 0.484358 (938) | 0.484706 (SE 0.0008 dB) |

Readings: the reference converges onto (f) as ℓ shrinks (the continuum limit (f) estimates). At ℓ = 2.5 m it is off by −0.58 % in
`dead_booth` and +0.58 % in `living_room`; 2.5 → 1.25 m changes it by 0.17 % / 0.53 % (< 1 %), 1.25 → 0.625 m by 0.28 % / 0.08 %.
(`classroom` and `small_room` at 0.3125 m were cut by an out-of-memory kill; to be rerun to 0.625 m.)

## 3. Cross-band correlation of (f)'s per-path contributions (Seat 1)

Correlation of the 8 band contributions over paths (32 k paths): W1 reference min 0.994; W1 corner min 0.978; CR4 min 0.988; layout 4
reference 1.000. The random error is a broadband level offset, not a tone-colour tilt.
