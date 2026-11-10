# Orchestrator computation C13: N-3W\* under the seats' second-round conditions

2026-11-10 (§2 corrected the same day: the first version's readings quoted errors against the reference under the
long-run heading; the decider found the mismatch). Asked for by the second-round seat positions (`23-seat<n>-round2-T1-T2.md`). Prototype outside `src/sim`:
`tools/validation/phase05b2_dt1.py` steps `c13`, `c13g` and `c13x`; data in `tools/validation/data/phase05b2_dt1.json`, sections
`c13`, `c13g` and `c13x`. Work is counted in image evaluations, so nothing here depends on this machine's speed.

**Rule as implemented (each element traced to the seat that asked for it).**
- **W_max** follows Seat 5's round-2 correction: a 1-thread CI pool; the worst cost over the gated set (the flutter cube,
  42.5 ns per evaluation); the Linux build (1.884 s).
  - That leaves 0.1296 s per emitter, so **W_max = 3.05 M evaluations**.
  - The 2-thread pool figure, 5.9 M, is reported beside it.
- **Pilot defined in work** (Seats 1–9): n\* = min(8 000, ⌊(W_max / 2) / e_cal⌋).
  - e_cal is the mean evaluations per history of a fixed calibration block [0, 256), sized before the pilot is sampled (Seat 4).
  - The pilot-floor flag is raised below 1 000 histories (Seats 1 and 3).
- **Final range** starts at the fixed index 8 000 (Seats 2 and 4) and is disjoint from the pilot (Seat 1).
  - N = max(N_need, n\*), the minimum final N asked for by Seats 1, 2, 3, 5, 6, 7 and 9.
  - N is then capped by the remaining work, and a cap hit is flagged.
- **Replicates** use independent seed pairs: 30 per near-wall case, the shipping rule at the 1-thread W_max, 1 kHz.
  - Against the C12 long runs (256 k histories) they give the spread of the shipped error.
  - The long run is itself heavy-tailed in the both-near cases, so there the comparison bounds the shipped error only loosely.

## 1. Reference positions (the gated and benchmark scenes)

| scene | n\* | N | cap hit | final SE (dB) | pilot VOV | pilot-floor flag | 2-thread W_max: N / cap hit / SE |
|---|---|---|---|---|---|---|---|
| W1_e0 | 8000 | 8000 | no | 0.023 | 0.008 | no | 8000 / no / 0.023 |
| W1_e1 | 8000 | 8000 | no | 0.023 | 0.007 | no | 8000 / no / 0.023 |
| W2_e0 | 273 | 273 | no | 0.011 | 0.078 | yes | 520 / no / 0.010 |
| W2_e1 | 273 | 273 | no | 0.012 | 0.080 | yes | 523 / no / 0.010 |
| bras_cr4_ls1_mp1 | 7663 | 7646 | no | 0.027 | 0.003 | no | 8000 / no / 0.026 |
| bras_cr4_ls1_mp2 | 5085 | 5015 | no | 0.028 | 0.005 | no | 8000 / no / 0.022 |
| bras_cr4_ls1_mp3 | 4469 | 4392 | no | 0.033 | 0.012 | no | 8000 / no / 0.024 |
| bras_cr4_ls1_mp4 | 7199 | 6989 | no | 0.023 | 0.003 | no | 8000 / no / 0.022 |
| bras_cr4_ls1_mp5 | 5466 | 5274 | no | 0.033 | 0.007 | no | 8000 / no / 0.026 |
| bras_cr4_ls2_mp1 | 5961 | 5713 | no | 0.027 | 0.005 | no | 8000 / no / 0.022 |
| bras_cr4_ls2_mp2 | 6332 | 6095 | no | 0.031 | 0.008 | no | 8000 / no / 0.027 |
| bras_cr4_ls2_mp3 | 5526 | 5352 | no | 0.025 | 0.006 | no | 8000 / no / 0.020 |
| bras_cr4_ls2_mp4 | 4858 | 4534 | no | 0.032 | 0.004 | no | 8000 / no / 0.024 |
| bras_cr4_ls2_mp5 | 3017 | 2875 | no | 0.036 | 0.012 | no | 5559 / no / 0.028 |
| cube100_e0 | 1832 | 1830 | **yes** | 0.199 | 0.307 | no | 3562 / yes / 0.116 |
| cube100_e1 | 1827 | 1832 | **yes** | 0.140 | 0.373 | no | 3567 / yes / 0.083 |
| cube100_flutter_e0 | 314 | 313 | no | 0.002 | 0.512 | yes | 606 / no / 0.001 |
| cube100_flutter_e1 | 314 | 313 | no | 0.002 | 0.100 | yes | 605 / no / 0.001 |

Readings:
1. **W1, CR4, W2 and the flutter cube fit, with no cap hit.**
   - W1 and CR4 run the full or nearly full 8 000-history pilot. Their final SE is 0.023–0.036 dB.
   - In W2 and the flutter cube the work-defined pilot shrinks to 273–314 histories, and the final range now exists.
     Conflict 1 of C12 is resolved: the SE is 0.002–0.012 dB.
   - The pilot-floor flag fires there (n\* < 1 000) on a scene whose estimate is excellent. As specified, the floor flags
     these scenes, not only weak estimates.
2. **The gated 100 m cube hits the cap at its reference positions.**
   - The final SE is 0.14 / 0.20 dB, inside Seat 1's 0.33 dB floor.
   - The pilot VOV is 0.31 / 0.37, so Seat 1's rule (VOV < 0.1 wherever the pilot SE > target / 3) is not met.
   - At the 2-thread W_max the SE is 0.08 / 0.12 dB, and the cap still hits.

## 2. Near-wall cases: shipped estimate at the 1-thread W_max, 30 replicates against the C12 long runs (1 kHz)

| case | w | n\* | N | cap hit | final SE (dB) | pilot VOV | replicates vs long run: p5 / median / p95 (dB) | largest |error| vs long (dB) | replicates vs ref 1.25 m: p5 / median / p95 (dB) | 2-thread SE (dB) |
|---|---|---|---|---|---|---|---|---|---|---|
| W1/reference_positions | 0.419 | 8000 | 8000 | no | 0.023 | 0.008 | -0.04 / -0.01 / +0.03 | 0.06 | -0.04 / -0.01 / +0.03 | 0.023 |
| W1/listener_wall | 0.002 | 3907 | 3907 | no | 0.040 | 0.022 | -0.05 / -0.00 / +0.06 | 0.08 | -0.05 / -0.00 / +0.06 | 0.030 |
| W1/listener_edge | 0.002 | 3229 | 3229 | no | 0.054 | 0.029 | -0.06 / -0.01 / +0.07 | 0.08 | -0.07 / -0.03 / +0.05 | 0.037 |
| W1/listener_corner | 0.002 | 2769 | 2769 | no | 0.046 | 0.040 | -0.04 / +0.02 / +0.07 | 0.08 | -0.07 / -0.00 / +0.04 | 0.032 |
| W1/emitter_wall | 0.997 | 3311 | 3311 | no | 0.049 | 0.036 | -0.05 / +0.01 / +0.09 | 0.16 | -0.06 / +0.00 / +0.08 | 0.031 |
| W1/emitter_edge | 0.997 | 2485 | 2485 | no | 0.048 | 0.046 | -0.08 / +0.01 / +0.07 | 0.08 | -0.08 / +0.00 / +0.06 | 0.032 |
| W1/emitter_corner | 0.997 | 2186 | 2141 | no | 0.053 | 0.048 | -0.10 / +0.01 / +0.08 | 0.11 | -0.11 / -0.00 / +0.07 | 0.039 |
| W1/both_wall | 0.500 | 1771 | 1766 | **yes** | 0.082 | 0.876 | -0.60 / -0.35 / +0.50 | 1.35 | -0.64 / -0.39 / +0.46 | 0.187 |
| W1/both_corner | 0.500 | 935 | 914 | **yes** | 0.081 | 0.275 | -1.49 / -1.20 / +4.43 | 6.95 | -1.73 / -1.44 / +4.18 | 0.306 |
| layout4_s1/reference_positions | 0.419 | 432 | 459 | **yes** | 0.387 | 0.028 | -0.76 / -0.07 / +0.44 | 1.06 | -0.76 / -0.06 / +0.45 | 0.282 |
| layout4_s1/listener_wall | 0.002 | 347 | 356 | **yes** | 0.682 | 0.082 | -1.38 / +0.02 / +1.17 | 2.33 | -1.37 / +0.03 / +1.18 | 0.444 |
| layout4_s1/listener_edge | 0.002 | 273 | 274 | **yes** | 0.672 | 0.073 | -0.98 / +0.01 / +0.97 | 1.22 | -0.95 / +0.05 / +1.01 | 0.497 |
| layout4_s1/listener_corner | 0.002 | 256 | 176 | **yes** | 0.862 | 0.101 | -1.35 / -0.06 / +1.28 | 2.18 | -1.52 / -0.23 / +1.11 | 0.563 |
| layout4_s1/emitter_wall | 0.997 | 335 | 341 | **yes** | 0.699 | 0.126 | -1.01 / -0.01 / +0.82 | 1.46 | -1.02 / -0.03 / +0.80 | 0.497 |
| layout4_s1/emitter_edge | 0.997 | 271 | 270 | **yes** | 0.638 | 0.075 | -1.30 / -0.29 / +1.05 | 1.84 | -1.16 / -0.15 / +1.19 | 0.470 |
| layout4_s1/emitter_corner | 0.997 | 256 | 145 | **yes** | 1.113 | 0.079 | -1.44 / +0.34 / +1.70 | 2.46 | -1.60 / +0.18 / +1.54 | 0.753 |
| layout4_s1/both_wall | 0.500 | 2470 | 2554 | **yes** | 0.924 | 0.403 | -2.96 / -2.45 / +1.32 | 5.04 | -2.60 / -2.09 / +1.67 | 0.549 |
| layout4_s1/both_corner | 0.500 | 256 | 90 | **yes** | 1.008 | 0.208 | -9.28 / -6.72 / -0.45 | 10.84 | -8.78 / -6.22 / +0.05 | 0.869 |
| layout4_s1/listener_absorber | 0.002 | 444 | 460 | **yes** | 0.571 | 0.068 | -0.88 / -0.13 / +0.66 | 2.01 | -0.89 / -0.13 / +0.66 | 0.418 |
| layout5_s1/reference_positions | 0.419 | 264 | 262 | **yes** | 0.403 | 0.099 | -0.45 / -0.15 / +0.42 | 0.82 | -0.45 / -0.15 / +0.42 | 0.299 |
| layout5_s1/listener_wall | 0.002 | 4243 | 4434 | **yes** | 0.162 | 0.039 | -0.42 / -0.01 / +0.26 | 0.47 | -0.43 / -0.02 / +0.25 | 0.128 |
| layout5_s1/listener_edge | 0.002 | 4471 | 4596 | **yes** | 0.320 | 0.104 | -0.50 / -0.07 / +0.39 | 0.61 | -0.68 / -0.25 / +0.21 | 0.210 |
| layout5_s1/listener_corner | 0.002 | 3520 | 3571 | **yes** | 0.221 | 0.130 | -0.37 / +0.07 / +0.30 | 0.58 | -0.74 / -0.31 / -0.08 | 0.167 |
| layout5_s1/emitter_wall | 0.997 | 3491 | 3748 | **yes** | 0.224 | 0.111 | -0.38 / +0.04 / +0.31 | 0.44 | -0.35 / +0.07 / +0.34 | 0.163 |
| layout5_s1/emitter_edge | 0.997 | 2272 | 2396 | **yes** | 0.244 | 0.110 | -0.36 / -0.17 / +0.27 | 0.69 | -0.32 / -0.12 / +0.32 | 0.166 |
| layout5_s1/emitter_corner | 0.997 | 1747 | 1785 | **yes** | 0.330 | 0.075 | -0.39 / -0.06 / +0.37 | 0.83 | -0.45 / -0.12 / +0.31 | 0.216 |
| layout5_s1/both_wall | 0.500 | 1819 | 1879 | **yes** | 0.745 | 0.242 | -2.28 / -1.13 / +0.97 | 4.01 | -2.89 / -1.74 / +0.36 | 1.083 |
| layout5_s1/both_corner | 0.500 | 867 | 872 | **yes** | 0.257 | 0.347 | -6.13 / -5.57 / +0.80 | 6.18 | -6.52 / -5.97 / +0.40 | 0.181 |
| layout5_s1/listener_absorber | 0.002 | 319 | 309 | **yes** | 0.603 | 0.237 | -1.21 / -0.22 / +1.30 | 1.63 | -1.18 / -0.19 / +1.33 | 0.420 |

Readings:
1. **W1: every one-end case meets Seat 1's floor, with no cap hit.**
   - The final SE is 0.040–0.054 dB, and the pilot VOV is ≤ 0.048.
   - Over 30 replicates the shipped error against the long runs stays within −0.10 / +0.09 dB (p5 / p95). The largest error
     is 0.16 dB. Against the reference it is −0.11 / +0.08 dB.
2. **Layouts 4 and 5 at s = 1 fail Seat 1's floor, at their reference positions as well.**
   - The cause is the window, not the walls: t_mix,e is 0.380 s in these rooms, against 0.114 s in W1.
     - The calibration block costs 3 400–8 800 evaluations per history in layout 4 (all cases but both_wall, 620) and
       340–5 800 in layout 5, against 180 in W1.
     - W_max therefore buys 256–460 histories in layout 4 (all but both_wall) and 260–4 600 in layout 5. Every layout-4
       case but both_wall sits below the 1 000-history pilot floor.
   - Final SE:

     | room | reference positions | near-wall cases |
     |---|---|---|
     | layout 4 | 0.39 dB | 0.57–1.11 dB |
     | layout 5 | 0.40 dB | 0.16–0.60 dB |

   - The replicate spread (p5 / p95) reaches about ±1.0–1.6 dB in layout 4.
   - At the 2-thread W_max, layout 4 is 0.28 dB at its reference positions and 0.42–0.75 dB near walls. That is still above
     the floor near walls.
   - These two rooms are the C4 cases Seat 1 named, and they have the longest t_mix,e in the case set.
3. **Both ends near a surface: the shipped estimate reads low.**
   - The median replicate is below both comparisons:

     | case | median vs long run | median vs ref 1.25 m |
     |---|---|---|
     | W1 both_wall | −0.35 dB | −0.39 dB |
     | W1 both_corner | −1.20 dB | −1.44 dB |
     | layout 5 both_wall | −1.13 dB | −1.74 dB |
     | layout 4 both_wall | −2.45 dB | −2.09 dB |
     | layout 5 both_corner | −5.57 dB | −5.97 dB |
     | layout 4 both_corner | −6.72 dB | −6.22 dB |

   - The upper tail reaches +4.4 dB against the long run (W1 both_corner p95).
   - This is the heavy tail's skew: the typical capped draw misses the rare large scores. It is the "tail too weak" case
     Seats 1, 4 and 8 described.
   - Seat 1's condition (shipped error ≤ 1 dB at the 95th percentile) is met only in W1 both_wall (p5 / p95 against the long run
     −0.60 / +0.50 dB).
     It is not met in W1 both_corner or in any both-near case of layouts 4 and 5.

## 3. Both ends near walls in Phase 04 rooms and in W1 at 0.3 and 0.5 m (Seats 3 and 8)

Error spread of 30 replicates about their own mean (no long run exists for these cases, so this measures spread only; any
bias from the skew described above is not visible in it).

| case | n\* | N | cap hit | final SE (dB) | pilot VOV | replicate SD (dB) | p95 |error| (dB) | largest |error| (dB) |
|---|---|---|---|---|---|---|---|---|
| W1/reference_positions | 8000 | 8000 | no | 0.023 | 0.008 | 0.021 | 0.043 | 0.050 |
| W1/listener_wall | 3907 | 3907 | no | 0.040 | 0.022 | 0.035 | 0.069 | 0.081 |
| W1/listener_edge | 3229 | 3229 | no | 0.054 | 0.029 | 0.043 | 0.076 | 0.080 |
| W1/listener_corner | 2769 | 2769 | no | 0.046 | 0.040 | 0.032 | 0.067 | 0.076 |
| W1/emitter_wall | 3311 | 3311 | no | 0.049 | 0.036 | 0.048 | 0.079 | 0.153 |
| W1/emitter_edge | 2485 | 2485 | no | 0.048 | 0.046 | 0.044 | 0.081 | 0.085 |
| W1/emitter_corner | 2186 | 2141 | no | 0.053 | 0.048 | 0.058 | 0.108 | 0.111 |
| W1/both_wall | 1771 | 1766 | **yes** | 0.082 | 0.876 | 0.432 | 0.652 | 1.505 |
| W1/both_corner | 935 | 914 | **yes** | 0.081 | 0.275 | 2.037 | 4.076 | 6.601 |
| layout4_s1/reference_positions | 432 | 459 | **yes** | 0.387 | 0.028 | 0.392 | 0.694 | 0.976 |
| layout4_s1/listener_wall | 347 | 356 | **yes** | 0.682 | 0.082 | 0.887 | 1.520 | 2.352 |
| layout4_s1/listener_edge | 273 | 274 | **yes** | 0.672 | 0.073 | 0.660 | 1.097 | 1.263 |
| layout4_s1/listener_corner | 256 | 176 | **yes** | 0.862 | 0.101 | 0.897 | 1.408 | 2.222 |
| layout4_s1/emitter_wall | 335 | 341 | **yes** | 0.699 | 0.126 | 0.654 | 1.156 | 1.486 |
| layout4_s1/emitter_edge | 271 | 270 | **yes** | 0.638 | 0.075 | 0.789 | 1.533 | 1.771 |
| layout4_s1/emitter_corner | 256 | 145 | **yes** | 1.113 | 0.079 | 1.001 | 2.006 | 2.719 |
| layout4_s1/both_wall | 2470 | 2554 | **yes** | 0.924 | 0.403 | 1.753 | 2.450 | 6.175 |
| layout4_s1/both_corner | 256 | 90 | **yes** | 1.008 | 0.208 | 2.793 | 6.599 | 7.764 |
| layout4_s1/listener_absorber | 444 | 460 | **yes** | 0.571 | 0.068 | 0.601 | 1.020 | 1.924 |
| layout5_s1/reference_positions | 264 | 262 | **yes** | 0.403 | 0.099 | 0.309 | 0.527 | 0.885 |
| layout5_s1/listener_wall | 4243 | 4434 | **yes** | 0.162 | 0.039 | 0.222 | 0.417 | 0.459 |
| layout5_s1/listener_edge | 4471 | 4596 | **yes** | 0.320 | 0.104 | 0.291 | 0.523 | 0.648 |
| layout5_s1/listener_corner | 3520 | 3571 | **yes** | 0.221 | 0.130 | 0.212 | 0.402 | 0.615 |
| layout5_s1/emitter_wall | 3491 | 3748 | **yes** | 0.224 | 0.111 | 0.209 | 0.396 | 0.445 |
| layout5_s1/emitter_edge | 2272 | 2396 | **yes** | 0.244 | 0.110 | 0.223 | 0.411 | 0.582 |
| layout5_s1/emitter_corner | 1747 | 1785 | **yes** | 0.330 | 0.075 | 0.290 | 0.428 | 0.856 |
| layout5_s1/both_wall | 1819 | 1879 | **yes** | 0.745 | 0.242 | 1.290 | 1.798 | 4.606 |
| layout5_s1/both_corner | 867 | 872 | **yes** | 0.257 | 0.347 | 2.318 | 4.426 | 5.962 |
| layout5_s1/listener_absorber | 319 | 309 | **yes** | 0.603 | 0.237 | 0.713 | 1.545 | 1.742 |
| W1/both_wall_0.3 | 1807 | 1813 | **yes** | 0.106 | 0.420 | 0.242 | 0.494 | 0.659 |
| W1/both_wall_0.5 | 1860 | 1869 | **yes** | 0.173 | 0.154 | 0.154 | 0.277 | 0.332 |
| club/both_wall_0.1 | 4838 | 4727 | **yes** | 0.404 | 0.331 | 0.239 | 0.380 | 0.563 |
| club/both_edge_0.1 | 1329 | 1265 | **yes** | 0.098 | 0.607 | 0.635 | 1.384 | 1.758 |
| club/both_wall_0.3 | 5290 | 5238 | **yes** | 0.071 | 0.123 | 0.055 | 0.095 | 0.104 |
| club/both_edge_0.3 | 1413 | 1354 | **yes** | 0.145 | 0.126 | 0.260 | 0.539 | 0.709 |
| club/both_wall_0.5 | 5998 | 5963 | no | 0.047 | 0.025 | 0.041 | 0.084 | 0.106 |
| club/both_edge_0.5 | 1532 | 1464 | **yes** | 0.155 | 0.075 | 0.157 | 0.269 | 0.481 |
| living_room/both_wall_0.1 | 3203 | 3203 | no | 0.092 | 0.281 | 0.073 | 0.148 | 0.160 |
| living_room/both_edge_0.1 | 1311 | 1261 | **yes** | 0.350 | 0.287 | 0.263 | 0.385 | 0.875 |
| living_room/both_wall_0.3 | 3861 | 3861 | no | 0.028 | 0.015 | 0.027 | 0.051 | 0.076 |
| living_room/both_edge_0.3 | 1584 | 1554 | **yes** | 0.132 | 0.067 | 0.072 | 0.123 | 0.137 |
| living_room/both_wall_0.5 | 4696 | 4696 | no | 0.018 | 0.003 | 0.019 | 0.034 | 0.039 |
| living_room/both_edge_0.5 | 1988 | 1988 | no | 0.054 | 0.007 | 0.042 | 0.093 | 0.103 |

Readings:
1. **Both ends at 0.5 m:** the spread is small (p95 ≤ 0.09 dB, pilot VOV ≤ 0.025, no cap hit) in `club` along walls and in
   both `living_room` placements. `club`'s edge placement is capped, with p95 0.27 dB.
2. **Both ends at 0.1 m, edge placement:** the p95 error is 0.39 dB in `living_room` and 1.38 dB in `club`, with pilot VOV
   0.29–0.61.
3. **Wall placements at 0.1 m:** `club` 0.38 dB, `living_room` 0.15 dB.
4. **W1 at 0.3 / 0.5 m:** p95 0.49 / 0.28 dB. W1 runs the long 28–30 m window here, so every point is capped.

## 4. Where the pilot's VOV crosses 0.1 (W1, both ends moved off opposite walls together; Seat 2)

| distance from wall (m) | 1.0 | 0.9 | 0.8 | 0.7 | 0.65 | 0.6 | 0.5 | 0.4 | 0.3 | 0.2 | 0.1 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| pilot VOV | 0.064 | 0.070 | 0.085 | 0.097 | 0.102 | 0.105 | 0.154 | 0.257 | 0.420 | 0.797 | 0.876 |
| pilot SE (dB) | 0.12 | 0.13 | 0.14 | 0.16 | 0.17 | 0.18 | 0.23 | 0.32 | 0.51 | 0.96 | 1.36 |
| final SE (dB) | 0.09 | 0.09 | 0.10 | 0.12 | 0.11 | 0.12 | 0.17 | 0.16 | 0.11 | 0.10 | 0.08 |

- Every point of this sweep hits the cap: the emitter and listener are 28–30 m apart, so the window is long (C12 (b) reading 3).
- **The pilot VOV crosses 0.1 between 0.70 and 0.65 m** (0.097 → 0.102) and rises to 0.88–0.91 at 0.15–0.10 m. Seat 2 asked
  for this crossing to pre-register a geometric both-near criterion. In this room and window it lies near d ≈ 0.65 m for both ends.
- The capped final SE stays at 0.08–0.22 dB. It is computed from too few histories to see the heavy tail, which §2's
  replicates show.

## 5. Cap-hit rate on a grid of ordinary positions (Seat 2)

Listener on a 3 × 4 × 2 grid (x at 0.2 / 0.5 / 0.8 of the width, y at 0.15 / 0.35 / 0.65 / 0.85 of the length, z 1.2 / 1.7 m),
emitter at the scene's position, 1-thread W_max:

| room | points | cap hits | largest final SE (dB) |
|---|---|---|---|
| W1 | 24 | 0 | 0.033 |
| club | 24 | 0 | 0.023 |
| concert_hall_box | 24 | 0 | 0.086 |

## 6. The layout-4 emitter-edge outlier (Seats 1, 2, 3, 6, 9)

Two more disjoint ranges of NW-4C at the layout-4 emitter edge (1 kHz):

| range | SE (dB) | vs the C12 32 k run | vs the C12 long run (256 k) | vs ref 1.25 m | largest share |
|---|---|---|---|---|---|
| 300 000 – 555 999 | 0.025 | -0.199 dB | +0.074 dB | +0.065 dB | 0.036 % |
| 1 000 000 – 1 999 999 | 0.013 | -0.245 dB | +0.028 dB | +0.111 dB | 0.035 % |

- **The −0.273 dB of C12 does not reproduce.** The long run and the 1 M run agree within 0.03 dB, at a combined SE of about
  0.028 dB.
- The 32 k run reads 0.20–0.25 dB below both, so the 32 k draw was the outlier (about −3.5 SE). The reverse gather at an
  emitter by an edge shows no bias.
- The 1 M run sits 0.11 dB above the 1.25 m reference, which C4 found uncertified for layout 4 near walls.

## 7. Reference ladder at layout 5's edges and corners (Seat 9)

| case | ref 2.5 m (1 kHz) | ref 1.25 m (1 kHz) | change 2.5 → 1.25 m |
|---|---|---|---|
| listener_edge | 1.4126e-03 | 1.3377e-03 | 5.3 % |
| listener_corner | 1.1189e-03 | 1.0213e-03 | 8.7 % |
| emitter_edge | 3.3290e-03 | 3.3024e-03 | 0.8 % |
| emitter_corner | 2.8875e-03 | 2.8290e-03 | 2.0 % |

- The listener edge and corner change by 5.3 % and 8.7 % on the last halving, far above the 1 % rule. The reference is not
  certified there.
- Both moved down as ℓ halved, in the direction of NW-4C's lower values (−0.18 / −0.38 dB in C12 (a)). This supports the
  reading that the disagreements at those seats are reference error, though it does not prove it.
- The emitter edge (0.8 %) is certified. NW-4C's +0.046 dB there (C12 (a)) is within its SE.

## Summary for the decider

1. **With the seats' conditions, conflicts 1 and 2 of C12 are resolved.**
   - A work-defined pilot gives every gated scene a final range.
   - The minimum final N publishes an SE no worse than the pilot's.
2. **A new conflict: Seat 5's corrected W_max (3.05 M) and Seat 1's floor (SE ≤ 0.33 dB with VOV < 0.1) cannot both hold in
   long-window rooms.**
   - **Layouts 4 and 5 at s = 1** (t_mix,e 0.38 s) miss the floor at their reference positions as well as near walls.
     The 2-thread W_max does not close the gap near walls.
   - **The gated 100 m cube** meets the SE part and misses the VOV part.
   - **W1, CR4, the Phase 04 grid and the six Phase 04 rooms' single-end cases** meet it.
3. **Both ends near a surface: NW-4C under the cap reads low**, by a median of −0.35 to −6.72 dB against the long runs. These
   cases need the flag and a decision on what is shipped there; Seat 1 asks for a bounded fallback, designed by Seat 2.
4. **The pilot-floor flag fires on scenes whose estimate is excellent** (W2 and the flutter cube). As specified, it flags
   expensive histories, not weak estimates.
