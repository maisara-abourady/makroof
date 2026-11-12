# 25 — Orchestrator: M1 (decider file 24), r and r_c per A4 case

2026-11-12. r_c = (A/16π)^½ (Kuttruff Eq. 5.44), A = Σ S_i α_i,b from the scene JSON (no air term: at 500 Hz / 1 kHz 4mV adds < 1 % here). r = |listener − emitter|. Finding: every A4 case has r > r_c (r/r_c 1.6 … 4.9); layout 4 is direct-dominated in the band IRs (d 0.83 … 0.90, file 23) at r/r_c = 3.53, because its absorbing floor makes the field non-diffuse (Eq. 5.44 assumes a diffuse field). A prior r ≥ k·r_c gate (O6) would assert layout 4 for any k ≤ 3.5.

```
layout4_s1                 500 Hz emitter 0: A   616.0 m2 (no air), r_c  3.50 m, r 12.37 m, r/r_c  3.53
layout4_s1                 500 Hz emitter 1: A   616.0 m2 (no air), r_c  3.50 m, r 12.37 m, r/r_c  3.53
layout4_s1                1000 Hz emitter 0: A   616.0 m2 (no air), r_c  3.50 m, r 12.37 m, r/r_c  3.53
layout4_s1                1000 Hz emitter 1: A   616.0 m2 (no air), r_c  3.50 m, r 12.37 m, r/r_c  3.53
layout5_s1                 500 Hz emitter 0: A   319.0 m2 (no air), r_c  2.52 m, r 12.37 m, r/r_c  4.91
layout5_s1                 500 Hz emitter 1: A   319.0 m2 (no air), r_c  2.52 m, r 12.37 m, r/r_c  4.91
layout5_s1                1000 Hz emitter 0: A   319.0 m2 (no air), r_c  2.52 m, r 12.37 m, r/r_c  4.91
layout5_s1                1000 Hz emitter 1: A   319.0 m2 (no air), r_c  2.52 m, r 12.37 m, r/r_c  4.91
absorbing_floor_cube20     500 Hz emitter 0: A   500.0 m2 (no air), r_c  3.15 m, r  8.25 m, r/r_c  2.62
absorbing_floor_cube20     500 Hz emitter 1: A   500.0 m2 (no air), r_c  3.15 m, r  8.25 m, r/r_c  2.62
absorbing_floor_cube20    1000 Hz emitter 0: A   500.0 m2 (no air), r_c  3.15 m, r  8.25 m, r/r_c  2.62
absorbing_floor_cube20    1000 Hz emitter 1: A   500.0 m2 (no air), r_c  3.15 m, r  8.25 m, r/r_c  2.62
bras_cr3_ls1_mp2           500 Hz emitters 0/1: A   321.3 m2 (no air), r_c  2.53 m, r  4.57 m, r/r_c  1.81
bras_cr3_ls1_mp2          1000 Hz emitters 0/1: A   397.5 m2 (no air), r_c  2.81 m, r  4.57 m, r/r_c  1.63
```
