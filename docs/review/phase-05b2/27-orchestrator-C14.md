# Orchestrator computation C14: the interrogator's requested computations (a)–(e)

2026-11-10. Asked for by `26-interrogator-T1-T2-T6.md` ("For the orchestrator to compute or fix"). Prototype outside `src/sim`:
`tools/validation/phase05b2_dt1.py` step `c14`; data in `tools/validation/data/phase05b2_dt1.json` section `c14`. The rule is
C13's (N-3W\*\* as decided in round 2), computed per emitter with W_max = 3.05 M evaluations per emitter. Q2 (B) is
11.4 × that. Restore times assume 1 thread at 42.5 ns per evaluation and the 1.884 s Linux build (Seat 5's basis).

## (a) Calibration-block cost at the gated and worst 100 m scenes

| scene (100 m cube, both emitters) | AX22 fallback | t_mix,e (s) | e_cal | calibration block / W_max |
|---|---|---|---|---|
| cube100_alpha0.10-0.22_s0.3_e0 | no | 1.118 | 832 | 0.07 |
| cube100_alpha0.10-0.22_s0.3_e1 | no | 1.118 | 834 | 0.07 |
| cube100_lowalpha0.05_s0.3_e0 | no | 1.118 | 832 | 0.07 |
| cube100_lowalpha0.05_s0.3_e1 | no | 1.118 | 834 | 0.07 |
| cube100_lowalpha0.05_s1_e0 | no | 1.118 | 827 | 0.07 |
| cube100_lowalpha0.05_s1_e1 | no | 1.118 | 836 | 0.07 |
| cube100_flutter_fallback_e0 | yes | 2.098 | 4850 | 0.41 |
| cube100_flutter_fallback_e1 | yes | 2.098 | 4846 | 0.41 |
| cube100_absorbing_floor_s1_e0 | no | 1.118 | 827 | 0.07 |
| cube100_absorbing_floor_s1_e1 | no | 1.118 | 836 | 0.07 |

- **No gated 100 m scene breaks the calibration bound.** The block costs 0.07 of W_max in the closed cubes and 0.41 in the
  flutter (fallback) cube, both below ½.
- The interrogator's failure (block > W_max/2 once e_cal > ≈ 5 960) occurs only in the layout-4 rooms of C13, at e_cal
  7 000–8 800. Their t_mix,e is 0.38 s, against 0.11 s in W1 of the same size.
- The closed low-α cube (α 0.05) has the same t_mix,e (1.118 s) and e_cal as the α 0.10–0.22 cube. In these cubes α does not
  change the window.
- The low-α cube at s = 1 and the absorbing-floor cube do not fall back either. The only fallback scene is the flutter cube.

Shipped estimate per gated scene, (n\*, N, cap hit, final SE in dB):

| scene | (A), n\*_max 8 000 | (A), n\*_max 1 020 | (B), n\*_max 8 000 | (B), n\*_max 1 020 |
|---|---|---|---|---|
| cube100_alpha0.10-0.22_s0.3_e0 | 1832, 1830, cap, 0.199 | 1020, 2648, cap, 0.151 | 8000, 8000, –, 0.072 | 1020, 4650, –, 0.106 |
| cube100_alpha0.10-0.22_s0.3_e1 | 1827, 1832, cap, 0.140 | 1020, 2636, cap, 0.101 | 8000, 8000, –, 0.079 | 1020, 9403, –, 0.071 |
| cube100_lowalpha0.05_s0.3_e0 | 1832, 1830, cap, 0.183 | 1020, 2648, cap, 0.142 | 8000, 8000, –, 0.075 | 1020, 4610, –, 0.110 |
| cube100_lowalpha0.05_s0.3_e1 | 1827, 1832, cap, 0.126 | 1020, 2636, cap, 0.092 | 8000, 8000, –, 0.080 | 1020, 8558, –, 0.076 |
| cube100_lowalpha0.05_s1_e0 | 1842, 1905, cap, 0.483 | 1020, 2717, cap, 0.439 | 8000, 34777, cap, 0.122 | 1020, 41585, cap, 0.110 |
| cube100_lowalpha0.05_s1_e1 | 1824, 1915, cap, 0.637 | 1020, 2705, cap, 0.502 | 8000, 34696, cap, 0.117 | 1020, 41450, cap, 0.105 |
| cube100_flutter_fallback_e0 | 314, 313, –, 0.002 | 314, 313, –, 0.002 | 3584, 3507, –, 0.001 | 1020, 1020, –, 0.001 |
| cube100_flutter_fallback_e1 | 314, 313, –, 0.002 | 314, 313, –, 0.002 | 3586, 3505, –, 0.001 | 1020, 1020, –, 0.001 |
| cube100_absorbing_floor_s1_e0 | 1842, 1905, cap, 0.116 | 1020, 2717, cap, 0.098 | 8000, 8000, –, 0.062 | 1020, 2937, –, 0.105 |
| cube100_absorbing_floor_s1_e1 | 1824, 1915, cap, 0.111 | 1020, 2705, cap, 0.090 | 8000, 8000, –, 0.052 | 1020, 2976, –, 0.085 |

- **The closed low-α cube at s = 1 misses Seat 1's floor under (A):** final SE 0.48 / 0.64 dB. Under (A) every closed 100 m
  cube hits the cap.
- **Under (B)**, the cubes with s = 0.3 and the absorbing-floor cube no longer hit the cap. The low-α s = 1 cube still does,
  at SE 0.11–0.12 dB.

## (c) Restore under Q2 (A) and (B), per gated scene (both emitters' realised work, 1 thread)

| scene | (A) restore (s) | (B), n\*_max 8 000: restore / 14 restores (s) | (B), n\*_max 1 020: restore / 14 restores (s) |
|---|---|---|---|
| cube100_alpha0.10-0.22_s0.3 | 2.14 | 3.01 / 42.2 | 2.45 / 34.3 |
| cube100_lowalpha0.05_s0.3 | 2.14 | 3.01 / 42.2 | 2.42 / 33.9 |
| cube100_lowalpha0.05_s1 | 2.14 | 4.82 / 67.5 | 4.81 / 67.3 |
| cube100_flutter_fallback | 2.14 | 4.83 / 67.6 | 2.73 / 38.2 |
| cube100_absorbing_floor_s1 | 2.14 | 2.99 / 41.8 | 2.16 / 30.2 |

- Under (A) every gated scene uses its full cap: the restore sits at the bound (2.14 s), and 14 restores take 30.0 s, at
  pluginval's watchdog.
- **Under (B) every gated scene exceeds the bound.**
  - With n\*_max = 8 000: 2.99–4.83 s per restore, and 41.8–67.6 s for 14.
  - With n\*_max = 1 020: 2.16–4.81 s per restore, and 30.2–67.3 s for 14.
  - The worst cases are the low-α s = 1 cube (≈ 4.8 s) and, at n\*_max = 8 000, the flutter cube (4.83 s). That matches the
    interrogator's estimate of 4.8 s.

## (b) Six Phase 04 rooms, listener then emitter at 0.1 m from its nearest surface, both emitters, W_max (A)

| room | cap hits (of 4) | final SE (dB), n\*_max 8 000 | final SE (dB), n\*_max 1 020 | largest pilot VOV | n\* range |
|---|---|---|---|---|---|
| dead_booth | 0 | 0.013–0.025 | 0.020–0.035 | 0.003 | 2059–2298 |
| living_room | 0 | 0.010–0.020 | 0.026–0.046 | 0.001 | 4887–7142 |
| classroom | 0 | 0.014–0.019 | 0.040–0.054 | 0.002 | 8000–8000 |
| club | 0 | 0.023–0.032 | 0.065–0.082 | 0.002 | 8000–8000 |
| concert_hall_box | 0 | 0.054–0.082 | 0.076–0.124 | 0.106 | 8000–8000 |
| stone_box | 0 | 0.007–0.008 | 0.021–0.022 | 0.004 | 8000–8000 |

- **No cap hits at W_max (A)** in 24 cases (6 rooms × 2 emitters × listener or emitter at the wall). The pilot floor never
  binds (n\* ≥ 2 059). The final SE is ≤ 0.082 dB at n\*_max 8 000 and ≤ 0.124 dB at 1 020. This closes ledger
  P05B2-T1T2T6-24 with a measurement.
- **The VOV trigger of the "approximate" note fires once on an ordinary placement.** `concert_hall_box`, emitter 1 at
  0.1 m from its wall, has pilot VOV 0.106 with pilot SE ≈ the final SE of 0.054 dB (N = n\* = 8 000), which is above
  target / 3 (0.028 dB). Under round 2's trigger the note would show for a final SE of 0.054 dB, 0.05 jnd.

## (d) The D-T6 small room (3 × 2.5 × 2.5 m, α 0.03, s 0.1; listener (1.5, 0.667, 0.425), emitters at z = 0.5 m)

- **e0:** d_L 0.425 m, d_E 0.500 m. **Both-near flag (< 0.70 m): raised.** t_mix,e 23.2 ms, e_cal 355.
  - n\*_max 8 000: n\* 4292, N 4292, no cap hit, final SE 0.0062 dB, pilot VOV 0.0017.
  - n\*_max 1 020: SE 0.0134 dB.
  - Reference ladder (1 kHz): 0.625 m 1.943988, 0.3125 m 1.944054, 0.15625 m 1.944059. The last halving changes it by 0.0003 %.
  - 30 replicates of the shipping rule against the finest rung: p5 / median / p95 -0.009 / +0.000 / +0.008 dB, largest 0.012 dB. The 256 k run against the finest rung: -0.0003 dB (SE 0.0008 dB).
- **e1:** d_L 0.425 m, d_E 0.500 m. **Both-near flag (< 0.70 m): raised.** t_mix,e 23.2 ms, e_cal 356.
  - n\*_max 8 000: n\* 4285, N 4285, no cap hit, final SE 0.0063 dB, pilot VOV 0.0016.
  - n\*_max 1 020: SE 0.0134 dB.
  - Reference ladder (1 kHz): 0.625 m 1.943988, 0.3125 m 1.944054, 0.15625 m 1.944059. The last halving changes it by 0.0003 %.
  - 30 replicates of the shipping rule against the finest rung: p5 / median / p95 -0.011 / -0.001 / +0.009 dB, largest 0.015 dB. The 256 k run against the finest rung: -0.0008 dB (SE 0.0008 dB).

**Reading.** In this room the both-near flag is raised by geometry, yet the estimate is excellent: SE 0.006 dB, VOV 0.002,
replicates within ±0.015 dB of a reference converged to 0.0003 %. D-T1.6's 0.70 m criterion came from one W1 sweep with a
long window (C13 §4: 28–30 m apart, t_mix,e 0.16 s). Here the window is 23 ms, and the scores stay bounded. The geometric
criterion therefore does not carry over between rooms. The heavy tail depends on d relative to the path lengths in the window,
not on d alone [Inferred]. The D-T6 gate itself (|ΔL_C++ − ΔL_ref| ≤ 0.25 dB) is unaffected: the estimate meets it at shipping N
with a margin of about 15×.

## (e) Gated case count of CS-3 + CS-NW+ and z_FW

| component | cases |
|---|---|
| (A) cases | 15 |
| six Phase 04 rooms, both emitters | 12 |
| W1 and W2, both emitters | 4 |
| BRAS pairs | 30 |
| CS-NW+ as listed in D-T1.5 (five placements, one emitter) | 5 |
| CS-NW+ with both emitters at each listener placement | 9 |

| reading | cases M | case-bands | z_FW (family α 1 %, two-sided, Bonferroni) | family false-fail at p ≥ 0.999 per case |
|---|---|---|---|---|
| as listed | 66 | 528 | 4.277 | 6.4 % |
| both emitters | 70 | 560 | 4.290 | 6.8 % |

Neither 50 nor 64 is the count. The pre-registration must fix one reading: 66 or 70 cases, 528 or 560 case-bands.

