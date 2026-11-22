# 2 (part 2) — Fact sheet: the diffuse solve at W_max × {1, 2, 4, 8, 16} (F3, F4, F12)

Orchestrator measurement for the decider's convening (`1-decider-convening.md`, facts F3, F4, F12). Records only;
nothing here is a decision. **Local, one machine, Linux only** (not the three CI OSes F3 asks for; macOS and
Windows are under-informed until a CI run of the same test, which needs a manual `[wmax-sweep]` step or the
`[benchmark]` step, see "CI note").

## Method

- **Test:** `tests/unit/test_diffuse_wsweep.cpp` (new, registered in `tests/unit/CMakeLists.txt`), two hidden
  Catch2 cases tagged `[.][benchmark][wmax-sweep]`:
  - `wmax-sweep: the diffuse solve at W_max x {1, 2, 4, 8, 16} (F3 time and memory, F4 accuracy)`
  - `wmax-sweep: 30-replicate p95 at the gated cubes at W_max x {1, 4, 16}`
- **Seam: none.** The override is the existing field `DiffuseLimits::wScene` (`src/sim/diffuse/DiffuseEstimator.h`),
  set to `2 × kWMaxPerEmitterProvisional × m` (W_scene = 2 W_max, AX41). Every other limit (n\*_max 1 024, SE
  target 0.083 dB, pilot stop rule, joint rule) is the shipped default. No shipped file or constant changed.
- **Scenes:** the 100 m cubes exactly as `test_diffuse_records.cpp` `cube()` builds them
  (`cube100_lowalpha0.05_s0.3`, `cube100_flutter_fallback`, `cube100_lowalpha0.05_s1`; listener (50, 30, 1.7),
  emitters (45, 70, 2) / (55, 70, 2)); layouts 4 / 5 at s = 1 exactly as the AX43 reported set in
  `test_diffuse_records.cpp` builds them (20 × 30 × 10 m, faces α = 0.01, layout 4 floor α = 1, layout 5 xMin α = 1,
  two emitters; placements listener_wall / listener_edge / listener_corner / emitter_wall / both_wall /
  both_corner) plus `default` (listener R0 (10, 8, 1.7), emitters S0 (7, 20, 2) / S1 (13, 20, 2)), which the
  reported set does not list. Problems built with `diffuse_test::plan` (the planEmitter mirror). **The diffuse
  problem has no sample rate input** (plan builds it from the scene alone), so these are the solves of the
  48 kHz and the 96 kHz builds alike.
- **Timing:** per scene × multiplier, one warm-up solve at ×1, then 3 solves on the process pool (min / median /
  worst) and 1 solve on a 1-thread `ThreadPool` (single-thread). `REQUIRE`d: face hash and N identical between
  the two pools (D4) — held in all 85 cells. **Thread count:** the estimator runs on `ThreadPool::process()`,
  `hardware_concurrency()` = **4 threads** here (the caller plus 3 workers); the "single-thread" column is the
  same solve on a 1-thread pool.
- **Peak RSS delta:** Linux `/proc/self/clear_refs` ← "5" resets VmHWM; delta = VmHWM after the 3 pool solves −
  VmRSS before. This counts only pages newly faulted in (glibc reuses freed heap from earlier cells), so it is a
  lower bound per cell; the estimator's own score storage is analytically 3 × (n\* + N) × emitters × 8 bands × 8 B
  (= 384 B per history for two emitters) plus the lattice, which matches the one large cell (s = 1 cube ×16:
  N = 58 624 → 22.5 MB analytic, 21.3 MB measured).
- **Replicates (F4):** the "records: clause (d) replicates" form: 30 replicates of the shipping rule with
  `historyOffset = r × stride` against one fixed long run of 2^20 histories, |error| at 1 kHz (band 4) of the total
  (specular + diffuse). Stride 2^20 (N + 8 000 < 2^20 at every multiplier); the long run starts at 2^25 (beyond all
  replicate streams; the records test uses 2^26, so the ×1 numbers differ from the 05h record by the long run's
  own noise only: SE 0.117 / 0.115 dB and p95 0.254 / 0.179 dB here vs 0.117 / 0.115 and 0.250 / 0.178 on file).
  Multipliers 1, 4, 16, gated cubes only. Took 3 min 34 s.
- **Machine:** `nproc` = 4; CPU `Intel(R) Xeon(R) Processor @ 2.10GHz` (/proc/cpuinfo); 15 GB RAM; Linux
  6.18.44 (cloud container); GCC 13.3.0; Release preset (`-DSPATIAL_BUILD_PLUGIN=OFF`); repo HEAD 4488d2c plus
  the test as then uncommitted (the same test file is now in commit 656fae5, byte-identical). Load average 0.5–2.6 during the runs (other jobs may have run). This container is about
  2× slower per evaluation than the CI runners (pool ns/eval 6–31 here vs 4.6–14 in the S2 GATE lines), so
  **absolute times here are not CI times**; the F12 projection therefore scales CI pin values by measured work
  ratios, not by local milliseconds.
- **Build checks:** `cmake --build --preset release --target spatial_tests` clean; the new TU compiled
  separately with the project flags plus `-Werror` (`-Wall -Wextra -Wpedantic -Wshadow`) at -O3 and at -O0 -g:
  both clean (GCC only; MSVC /W4 /WX and Apple Clang not checked). `tools/ci/check_format.sh`: 114 files clean.
- **Runtime:** sweep 3 min 47 s; replicates 3 min 34 s. ×16 ran everywhere; no extrapolation needed.

## Key findings

1. **Time is linear in realised work, and realised work stops growing once N_need ≤ N_cap.** Single-thread
   ns per image evaluation is flat across ×1…×16 per scene (max/min 1.02–1.37, no trend; table T2). The pool
   (4 threads) gets cheaper per evaluation at larger W (max/min up to 2.05, falling): the pilot runs a pool's
   worth of blocks at a time and is a smaller share of a larger solve. So time(W) ≤ linear in W, = linear in
   realised work.
2. **The two gated cubes saturate early.** `cube100_lowalpha0.05_s0.3` is capped only at ×1 (N_need 3 574 vs
   N_cap 2 624); from ×2 N = 3 584 and realised work is fixed at 1.26 × the pin's (7.65 M evaluations).
   `cube100_flutter_fallback` is work-stopped in the pilot at ×1 and ×2 (n\* 320 / 640, floor truncated); from
   ×4 n\* = n\*_max = 1 024, N = 1 024 (N_need 1) and work is fixed at 3.29 × the pin's W_scene (20.1 M).
3. **The s = 1 cube and the layouts keep scaling.** `cube100_lowalpha0.05_s1` (N_need 58 612) is capped up to
   ×8 and uncapped first at ×16 (N_cap 58 944): work 15.9 × the pin's, single-thread 4.4 s, pool 1.2 s here.
   Layout 4 placements stay capped at ×16 except `default` (N_need 11 714); layout 4 both_corner needs N ≈ 571 k
   (≈ 105 × its ×16 N_cap). Layout 5: listener_wall / listener_edge / listener_corner uncap at ×8, default /
   both_wall / both_corner at ×16, emitter_wall is still capped at ×16.
4. **Memory is small against AX38 (i)'s 1 GB:** the largest measured delta is 21.3 MB (s = 1 cube ×16);
   analytic estimator storage at the largest N seen (58 624) is 22.5 MB.
5. **Accuracy (F4):** where capped, achieved SE falls about as 1/√W (s = 1 cube 0.36 → 0.29 → 0.19 → 0.13 →
   0.095 dB; layout 4 default 0.47 → 0.08 dB; layout 4 listener_edge 0.93 → 0.14 dB). The gated s = 0.3 cube's
   replicate p95 falls from 0.254 / 0.179 dB (×1) to 0.157 / 0.158 dB (×4 = ×16, saturated); the flutter
   cube's p95 is 0.003–0.005 dB at every W. **The both-near emitter-0 cases do not improve with W**
   (layout 4 both_wall / both_corner, layout 5 both_wall): VOV_union 0.31–0.91 across W and 0.41–0.55 at ×16
   (≥ 0.1), achieved SE 0.5–1.2 dB at ×16 and U = 1 at every W — heavy-tailed scores, a variance-estimate problem that more
   histories at these W do not fix.
6. **F12:** at the gated cubes the solve-at-W term is bounded by saturation, so the projection rises by at most
   0.37 s (low-α s = 0.3, any W ≥ ×2) and 5.6 s (flutter, Linux, W ≥ ×4) over the pin, under 30 s on every OS's
   S2 worst; only the macOS PR #33 outlier (30.50 s at the pin) is over 30 s, at the pin already. The s = 1 cube
   (not a gated build) would cross 30 s at about ×8 on Linux / macOS and ×16 on Windows.

## T1. Time against W (F3)

Pool(4) and single-thread wall time of one solve (ms, this machine), realised work relative to the ×1 W_scene
(6.10 M), peak RSS delta at ×16.

| scene | pool(4) median ms x1 / x2 / x4 / x8 / x16 | worst x16 | single-thread ms x1 / x2 / x4 / x8 / x16 | single x16 / x1 | realised work x1 → x16 (W_pilot+W_final)/W_scene(x1) | peak RSS delta x16 |
|---|---|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | 91 / 117 / 88 / 97 / 89 | 129 | 309 / 332 / 326 / 330 / 328 | 1.1 | 0.99 / 1.25 / 1.25 / 1.25 / 1.25 | 2.4 MB |
| cube100_flutter_fallback | 129 / 250 / 412 / 446 / 347 | 359 | 322 / 634 / 1072 / 1048 / 1047 | 3.2 | 0.93 / 1.98 / 3.29 / 3.29 / 3.29 | 3.3 MB |
| cube100_lowalpha0.05_s1 | 95 / 174 / 343 / 791 / 1198 | 1210 | 259 / 534 / 1204 / 2433 / 4432 | 17.1 | 0.99 / 1.99 / 3.99 / 7.97 / 15.87 | 21.3 MB |
| layout4_s1/default | 123 / 270 / 448 / 778 / 1527 | 1641 | 351 / 750 / 1454 / 2891 / 5079 | 14.5 | 1.01 / 2.02 / 4.06 / 8.17 / 14.56 | 0.2 MB |
| layout4_s1/listener_wall | 155 / 209 / 385 / 692 / 1395 | 1411 | 386 / 621 / 1360 / 2512 / 5247 | 13.6 | 1.00 / 2.03 / 4.03 / 8.11 / 16.34 | 0.0 MB |
| layout4_s1/listener_edge | 151 / 251 / 424 / 673 / 1326 | 1451 | 285 / 672 / 1325 / 2363 / 5044 | 17.7 | 0.91 / 1.97 / 3.93 / 7.84 / 15.84 | 0.0 MB |
| layout4_s1/listener_corner | 125 / 292 / 482 / 758 / 1436 | 1462 | 280 / 781 / 1189 / 2471 / 4829 | 17.2 | 0.93 / 1.97 / 3.85 / 7.88 / 15.75 | 0.0 MB |
| layout4_s1/emitter_wall | 133 / 256 / 444 / 778 / 1434 | 1438 | 384 / 661 / 1522 / 2763 / 5263 | 13.7 | 1.01 / 2.02 / 4.03 / 8.17 / 16.33 | 0.4 MB |
| layout4_s1/both_wall | 86 / 169 / 331 / 718 / 1361 | 1381 | 276 / 692 / 1224 / 2432 / 5026 | 18.2 | 0.97 / 2.00 / 4.08 / 8.24 / 16.50 | 1.4 MB |
| layout4_s1/both_corner | 102 / 208 / 330 / 664 / 1159 | 1197 | 243 / 489 / 1048 / 2060 / 4228 | 17.4 | 0.92 / 1.87 / 3.93 / 7.86 / 15.84 | 0.0 MB |
| layout5_s1/default | 184 / 276 / 455 / 790 / 1134 | 1259 | 318 / 631 / 1426 / 2775 / 4328 | 13.6 | 0.96 / 1.93 / 4.00 / 8.05 / 12.22 | 0.0 MB |
| layout5_s1/listener_wall | 44 / 97 / 166 / 167 / 177 | 189 | 157 / 269 / 623 / 624 / 620 | 3.9 | 0.99 / 1.98 / 3.96 / 4.06 / 4.06 | 0.0 MB |
| layout5_s1/listener_edge | 52 / 105 / 174 / 388 / 334 | 369 | 156 / 351 / 679 / 1199 / 1074 | 6.9 | 0.99 / 1.98 / 3.96 / 7.20 / 7.20 | 17.9 MB |
| layout5_s1/listener_corner | 49 / 84 / 191 / 245 / 229 | 268 | 139 / 370 / 563 / 900 / 755 | 5.4 | 0.99 / 1.99 / 4.00 / 5.58 / 5.57 | 0.0 MB |
| layout5_s1/emitter_wall | 121 / 244 / 385 / 808 / 1632 | 1646 | 325 / 676 / 1306 / 2661 / 5240 | 16.1 | 1.00 / 1.95 / 4.01 / 8.08 / 16.16 | 0.0 MB |
| layout5_s1/both_wall | 43 / 81 / 185 / 301 / 365 | 385 | 133 / 267 / 534 / 1079 / 1192 | 8.9 | 0.98 / 1.98 / 3.96 / 7.95 / 8.44 | 0.8 MB |
| layout5_s1/both_corner | 43 / 88 / 151 / 304 / 520 | 572 | 121 / 304 / 535 / 1178 / 1813 | 15.0 | 0.99 / 1.98 / 3.97 / 7.93 / 14.25 | 0.0 MB |

## T2. ns per image evaluation against W (linearity)

Wall time / realised work (W_pilot + W_final). Flat single-thread columns = time linear in realised work.

| scene | single-thread ns/eval ×1 / ×2 / ×4 / ×8 / ×16 | max/min | pool(4) ns/eval ×1 / ×2 / ×4 / ×8 / ×16 | max/min |
|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | 51.1 / 43.4 / 42.6 / 43.2 / 42.9 | 1.20 | 15.1 / 15.2 / 11.5 / 12.7 / 11.6 | 1.33 |
| cube100_flutter_fallback | 56.5 / 52.5 / 53.4 / 52.2 / 52.1 | 1.08 | 22.6 / 20.7 / 20.5 / 22.2 / 17.3 | 1.31 |
| cube100_lowalpha0.05_s1 | 43.0 / 44.0 / 49.5 / 50.0 / 45.8 | 1.16 | 15.7 / 14.3 / 14.1 / 16.3 / 12.4 | 1.32 |
| layout4_s1/default | 56.8 / 60.8 / 58.8 / 58.0 / 57.2 | 1.07 | 19.9 / 21.9 / 18.1 / 15.6 / 17.2 | 1.40 |
| layout4_s1/listener_wall | 63.1 / 50.3 / 55.4 / 50.7 / 52.6 | 1.26 | 25.4 / 16.9 / 15.7 / 14.0 / 14.0 | 1.81 |
| layout4_s1/listener_edge | 51.1 / 56.0 / 55.3 / 49.4 / 52.2 | 1.13 | 27.1 / 20.9 / 17.7 / 14.1 / 13.7 | 1.97 |
| layout4_s1/listener_corner | 49.4 / 65.0 / 50.7 / 51.4 / 50.3 | 1.31 | 22.1 / 24.2 / 20.5 / 15.8 / 14.9 | 1.62 |
| layout4_s1/emitter_wall | 62.5 / 53.7 / 62.0 / 55.5 / 52.9 | 1.18 | 21.6 / 20.8 / 18.1 / 15.6 / 14.4 | 1.50 |
| layout4_s1/both_wall | 46.5 / 56.7 / 49.2 / 48.4 / 50.0 | 1.22 | 14.4 / 13.8 / 13.3 / 14.3 / 13.5 | 1.08 |
| layout4_s1/both_corner | 43.4 / 42.8 / 43.7 / 43.0 / 43.8 | 1.02 | 18.2 / 18.2 / 13.8 / 13.9 / 12.0 | 1.52 |
| layout5_s1/default | 54.0 / 53.6 / 58.4 / 56.5 / 58.0 | 1.09 | 31.2 / 23.5 / 18.6 / 16.1 / 15.2 | 2.05 |
| layout5_s1/listener_wall | 26.0 / 22.4 / 25.8 / 25.2 / 25.1 | 1.16 | 7.3 / 8.0 / 6.9 / 6.8 / 7.2 | 1.19 |
| layout5_s1/listener_edge | 25.8 / 29.0 / 28.1 / 27.3 / 24.4 | 1.19 | 8.6 / 8.7 / 7.2 / 8.8 / 7.6 | 1.22 |
| layout5_s1/listener_corner | 23.1 / 30.4 / 23.1 / 26.5 / 22.2 | 1.37 | 8.1 / 6.9 / 7.8 / 7.2 / 6.7 | 1.20 |
| layout5_s1/emitter_wall | 53.4 / 56.7 / 53.5 / 54.0 / 53.2 | 1.07 | 19.9 / 20.5 / 15.7 / 16.4 / 16.6 | 1.30 |
| layout5_s1/both_wall | 22.3 / 22.1 / 22.1 / 22.2 / 23.2 | 1.05 | 7.2 / 6.7 / 7.7 / 6.2 / 7.1 | 1.23 |
| layout5_s1/both_corner | 20.1 / 25.2 / 22.1 / 24.4 / 20.9 | 1.25 | 7.2 / 7.3 / 6.2 / 6.3 / 6.0 | 1.22 |

## T3. Accuracy against W (F4), per scene × multiplier

Per emitter: achieved SE (max over bands, dB of the total), VOV_union, max per-band VOV of the shipped range,
U (TailMatch.approximate). The last column is the largest |total(×m) − total(×16)| over the 8 bands, dB — not
an error against truth (×16 has its own SE, and the final ranges share histories from 8 000, so a smaller N is
a prefix of a larger one); per-band SE and VOV are in the raw lines.

| scene | x | n* | W_pilot | N_need | N_cap | N | cap hit | floor trunc | realised/W_scene | e0 SE dB | e0 VOV_union | e0 max band VOV | e0 U | e1 SE dB | e1 VOV_union | e1 max band VOV | e1 U | max abs band drift vs x16 dB e0/e1 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | 1 | 1024 | 1696086 | 3574 | 2624 | 2624 | 1 | 0 | 0.991 | 0.092 | 0.084 | 0.131 | 0 | 0.075 | 0.122 | 0.155 | 0 | 0.007 / 0.041 |
| cube100_lowalpha0.05_s0.3 | 2 | 1024 | 1696086 | 3574 | 6336 | 3584 | 0 | 0 | 0.627 | 0.088 | 0.125 | 0.183 | 0 | 0.075 | 0.137 | 0.192 | 0 | 0.000 / 0.000 |
| cube100_lowalpha0.05_s0.3 | 4 | 1024 | 1696086 | 3574 | 13696 | 3584 | 0 | 0 | 0.313 | 0.088 | 0.125 | 0.183 | 0 | 0.075 | 0.137 | 0.192 | 0 | 0.000 / 0.000 |
| cube100_lowalpha0.05_s0.3 | 8 | 1024 | 1696086 | 3574 | 28416 | 3584 | 0 | 0 | 0.157 | 0.088 | 0.125 | 0.183 | 0 | 0.075 | 0.137 | 0.192 | 0 | 0.000 / 0.000 |
| cube100_lowalpha0.05_s0.3 | 16 | 1024 | 1696086 | 3574 | 57856 | 3584 | 0 | 0 | 0.078 | 0.088 | 0.125 | 0.183 | 0 | 0.075 | 0.137 | 0.192 | 0 | 0.000 / 0.000 |
| cube100_flutter_fallback | 1 | 320 | 3154338 | 1 | 256 | 256 | 0 | 1 | 0.935 | 0.002 | 0.152 | 0.232 | 0 | 0.001 | 0.238 | 0.105 | 0 | 0.000 / 0.003 |
| cube100_flutter_fallback | 2 | 640 | 6364347 | 1 | 576 | 576 | 0 | 1 | 0.990 | 0.001 | 0.087 | 0.103 | 0 | 0.001 | 0.125 | 0.045 | 0 | 0.002 / 0.003 |
| cube100_flutter_fallback | 4 | 1024 | 10101864 | 1 | 1408 | 1024 | 0 | 0 | 0.823 | 0.001 | 0.037 | 0.053 | 0 | 0.001 | 0.048 | 0.063 | 0 | 0.000 / 0.000 |
| cube100_flutter_fallback | 8 | 1024 | 10101864 | 1 | 3904 | 1024 | 0 | 0 | 0.411 | 0.001 | 0.037 | 0.053 | 0 | 0.001 | 0.048 | 0.063 | 0 | 0.000 / 0.000 |
| cube100_flutter_fallback | 16 | 1024 | 10101864 | 1 | 8832 | 1024 | 0 | 0 | 0.206 | 0.001 | 0.037 | 0.053 | 0 | 0.001 | 0.048 | 0.063 | 0 | 0.000 / 0.000 |
| cube100_lowalpha0.05_s1 | 1 | 1024 | 1666253 | 58612 | 2688 | 2688 | 1 | 0 | 0.986 | 0.360 | 0.126 | 0.153 | 1 | 0.359 | 0.154 | 0.185 | 1 | 0.060 / 0.291 |
| cube100_lowalpha0.05_s1 | 2 | 1024 | 1666253 | 58612 | 6464 | 6464 | 1 | 0 | 0.996 | 0.287 | 0.110 | 0.117 | 0 | 0.251 | 0.088 | 0.099 | 0 | 0.134 / 0.322 |
| cube100_lowalpha0.05_s1 | 4 | 1024 | 1666253 | 58612 | 13952 | 13952 | 1 | 0 | 0.997 | 0.186 | 0.100 | 0.093 | 0 | 0.183 | 0.080 | 0.050 | 0 | 0.228 / 0.169 |
| cube100_lowalpha0.05_s1 | 8 | 1024 | 1666253 | 58612 | 28928 | 28928 | 1 | 0 | 0.996 | 0.134 | 0.100 | 0.030 | 0 | 0.123 | 0.080 | 0.023 | 0 | 0.044 / 0.161 |
| cube100_lowalpha0.05_s1 | 16 | 1024 | 1666253 | 58612 | 58944 | 58624 | 0 | 0 | 0.992 | 0.095 | 0.100 | 0.015 | 0 | 0.094 | 0.080 | 0.013 | 0 | 0.000 / 0.000 |
| layout4_s1/default | 1 | 512 | 3446895 | 12294 | 384 | 384 | 1 | 1 | 1.012 | 0.474 | 0.021 | 0.052 | 1 | 0.429 | 0.016 | 0.028 | 1 | 0.383 / 0.496 |
| layout4_s1/default | 2 | 960 | 6474282 | 11910 | 832 | 832 | 1 | 1 | 1.012 | 0.302 | 0.009 | 0.019 | 0 | 0.298 | 0.008 | 0.014 | 0 | 0.437 / 0.314 |
| layout4_s1/default | 4 | 1024 | 6913401 | 11714 | 2560 | 2560 | 1 | 0 | 1.014 | 0.171 | 0.004 | 0.007 | 0 | 0.169 | 0.004 | 0.005 | 0 | 0.102 / 0.108 |
| layout4_s1/default | 8 | 1024 | 6913401 | 11714 | 6144 | 6144 | 1 | 0 | 1.022 | 0.110 | 0.002 | 0.003 | 0 | 0.108 | 0.002 | 0.002 | 0 | 0.028 / 0.090 |
| layout4_s1/default | 16 | 1024 | 6913401 | 11714 | 13376 | 11776 | 0 | 0 | 0.910 | 0.080 | 0.002 | 0.001 | 0 | 0.080 | 0.002 | 0.001 | 0 | 0.000 / 0.000 |
| layout4_s1/listener_wall | 1 | 384 | 3267852 | 25642 | 320 | 320 | 1 | 1 | 1.003 | 0.657 | 0.030 | 0.057 | 1 | 0.690 | 0.038 | 0.073 | 1 | 0.591 / 0.628 |
| layout4_s1/listener_wall | 2 | 768 | 6596124 | 23610 | 640 | 640 | 1 | 1 | 1.013 | 0.469 | 0.019 | 0.033 | 1 | 0.473 | 0.016 | 0.033 | 1 | 0.590 / 0.660 |
| layout4_s1/listener_wall | 4 | 1024 | 8796474 | 23764 | 1792 | 1792 | 1 | 0 | 1.006 | 0.319 | 0.014 | 0.022 | 0 | 0.311 | 0.012 | 0.020 | 0 | 0.142 / 0.183 |
| layout4_s1/listener_wall | 8 | 1024 | 8796474 | 23764 | 4608 | 4608 | 1 | 0 | 1.014 | 0.187 | 0.006 | 0.007 | 0 | 0.184 | 0.005 | 0.006 | 0 | 0.068 / 0.094 |
| layout4_s1/listener_wall | 16 | 1024 | 8796474 | 23764 | 10304 | 10304 | 1 | 0 | 1.021 | 0.124 | 0.004 | 0.003 | 0 | 0.121 | 0.003 | 0.003 | 0 | 0.000 / 0.000 |
| layout4_s1/listener_edge | 1 | 320 | 3398464 | 20409 | 192 | 192 | 1 | 1 | 0.914 | 0.925 | 0.040 | 0.128 | 1 | 0.968 | 0.038 | 0.117 | 1 | 1.145 / 1.253 |
| layout4_s1/listener_edge | 2 | 576 | 6284253 | 19954 | 512 | 512 | 1 | 1 | 0.984 | 0.555 | 0.020 | 0.052 | 1 | 0.597 | 0.020 | 0.054 | 1 | 0.940 / 0.912 |
| layout4_s1/listener_edge | 4 | 1024 | 11334854 | 21829 | 1152 | 1152 | 1 | 0 | 0.982 | 0.378 | 0.015 | 0.037 | 1 | 0.380 | 0.013 | 0.022 | 1 | 0.758 / 0.789 |
| layout4_s1/listener_edge | 8 | 1024 | 11334854 | 21829 | 3328 | 3328 | 1 | 0 | 0.981 | 0.212 | 0.006 | 0.008 | 0 | 0.214 | 0.006 | 0.007 | 0 | 0.187 / 0.270 |
| layout4_s1/listener_edge | 16 | 1024 | 11334854 | 21829 | 7744 | 7744 | 1 | 0 | 0.990 | 0.137 | 0.003 | 0.004 | 0 | 0.139 | 0.003 | 0.003 | 0 | 0.000 / 0.000 |
| layout4_s1/listener_corner | 1 | 256 | 3809660 | 26185 | 128 | 128 | 1 | 1 | 0.929 | 0.919 | 0.082 | 0.085 | 1 | 1.015 | 0.147 | 0.131 | 1 | 0.247 / 0.499 |
| layout4_s1/listener_corner | 2 | 448 | 6512538 | 23487 | 384 | 384 | 1 | 1 | 0.986 | 0.571 | 0.030 | 0.051 | 1 | 0.569 | 0.051 | 0.044 | 1 | 0.273 / 0.109 |
| layout4_s1/listener_corner | 4 | 832 | 12358081 | 23069 | 768 | 768 | 1 | 1 | 0.962 | 0.426 | 0.015 | 0.031 | 1 | 0.433 | 0.021 | 0.025 | 1 | 0.037 / 0.095 |
| layout4_s1/listener_corner | 8 | 1024 | 15206241 | 24858 | 2240 | 2240 | 1 | 0 | 0.985 | 0.254 | 0.009 | 0.013 | 0 | 0.256 | 0.009 | 0.010 | 0 | 0.329 / 0.293 |
| layout4_s1/listener_corner | 16 | 1024 | 15206241 | 24858 | 5504 | 5504 | 1 | 0 | 0.984 | 0.164 | 0.004 | 0.005 | 0 | 0.171 | 0.005 | 0.005 | 0 | 0.000 / 0.000 |
| layout4_s1/emitter_wall | 1 | 448 | 3485513 | 20471 | 320 | 320 | 1 | 1 | 1.008 | 0.708 | 0.034 | 0.086 | 1 | 0.476 | 0.019 | 0.034 | 1 | 0.424 / 0.572 |
| layout4_s1/emitter_wall | 2 | 832 | 6518623 | 20130 | 704 | 704 | 1 | 1 | 1.009 | 0.459 | 0.018 | 0.041 | 1 | 0.324 | 0.009 | 0.017 | 0 | 0.011 / 0.416 |
| layout4_s1/emitter_wall | 4 | 1024 | 8017748 | 20833 | 2048 | 2048 | 1 | 0 | 1.007 | 0.276 | 0.010 | 0.014 | 0 | 0.190 | 0.005 | 0.006 | 0 | 0.419 / 0.173 |
| layout4_s1/emitter_wall | 8 | 1024 | 8017748 | 20833 | 5184 | 5184 | 1 | 0 | 1.021 | 0.176 | 0.005 | 0.006 | 0 | 0.118 | 0.002 | 0.003 | 0 | 0.167 / 0.009 |
| layout4_s1/emitter_wall | 16 | 1024 | 8017748 | 20833 | 11392 | 11392 | 1 | 0 | 1.020 | 0.120 | 0.004 | 0.003 | 0 | 0.081 | 0.002 | 0.001 | 0 | 0.000 / 0.000 |
| layout4_s1/both_wall | 1 | 640 | 3211330 | 22346 | 512 | 512 | 1 | 1 | 0.975 | 0.842 | 0.476 | 0.611 | 1 | 0.538 | 0.021 | 0.047 | 1 | 0.855 / 0.284 |
| layout4_s1/both_wall | 2 | 1024 | 5152042 | 105005 | 1344 | 1344 | 1 | 0 | 1.001 | 0.572 | 0.314 | 0.389 | 1 | 0.362 | 0.014 | 0.028 | 1 | 1.129 / 0.133 |
| layout4_s1/both_wall | 4 | 1024 | 5152042 | 105005 | 3776 | 3776 | 1 | 0 | 1.021 | 1.032 | 0.786 | 0.829 | 1 | 0.201 | 0.006 | 0.008 | 0 | 0.134 / 0.048 |
| layout4_s1/both_wall | 8 | 1024 | 5152042 | 105005 | 8640 | 8640 | 1 | 0 | 1.030 | 0.832 | 0.549 | 0.528 | 1 | 0.133 | 0.003 | 0.003 | 0 | 0.165 / 0.003 |
| layout4_s1/both_wall | 16 | 1024 | 5152042 | 105005 | 18368 | 18368 | 1 | 0 | 1.031 | 0.496 | 0.549 | 0.260 | 1 | 0.092 | 0.003 | 0.001 | 0 | 0.000 / 0.000 |
| layout4_s1/both_corner | 1 | 256 | 3751605 | 112522 | 128 | 128 | 1 | 1 | 0.918 | 1.283 | 0.798 | 0.267 | 1 | 1.239 | 0.056 | 0.124 | 1 | 3.720 / 0.190 |
| layout4_s1/both_corner | 2 | 448 | 6618293 | 93881 | 320 | 320 | 1 | 1 | 0.936 | 0.797 | 0.643 | 0.249 | 1 | 0.938 | 0.044 | 0.151 | 1 | 3.150 / 0.288 |
| layout4_s1/both_corner | 4 | 832 | 12536018 | 552623 | 768 | 768 | 1 | 1 | 0.982 | 0.443 | 0.914 | 0.071 | 1 | 0.609 | 0.023 | 0.077 | 1 | 2.812 / 1.104 |
| layout4_s1/both_corner | 8 | 1024 | 15446007 | 570970 | 2176 | 2176 | 1 | 0 | 0.982 | 0.605 | 0.645 | 0.193 | 1 | 0.324 | 0.011 | 0.019 | 0 | 1.461 / 0.422 |
| layout4_s1/both_corner | 16 | 1024 | 15446007 | 570970 | 5440 | 5440 | 1 | 0 | 0.990 | 1.225 | 0.443 | 0.526 | 1 | 0.198 | 0.005 | 0.006 | 0 | 0.000 / 0.000 |
| layout5_s1/default | 1 | 320 | 3726315 | 6042 | 192 | 192 | 1 | 1 | 0.964 | 0.484 | 0.048 | 0.136 | 1 | 0.441 | 0.033 | 0.129 | 1 | 0.080 / 0.685 |
| layout5_s1/default | 2 | 576 | 6610361 | 5610 | 448 | 448 | 1 | 1 | 0.963 | 0.294 | 0.024 | 0.062 | 0 | 0.266 | 0.017 | 0.035 | 0 | 0.336 / 0.409 |
| layout5_s1/default | 4 | 1024 | 11772695 | 5350 | 1088 | 1088 | 1 | 0 | 1.001 | 0.173 | 0.010 | 0.021 | 0 | 0.174 | 0.008 | 0.015 | 0 | 0.363 / 0.157 |
| layout5_s1/default | 8 | 1024 | 11772695 | 5350 | 3200 | 3200 | 1 | 0 | 1.007 | 0.103 | 0.006 | 0.008 | 0 | 0.102 | 0.004 | 0.006 | 0 | 0.001 / 0.013 |
| layout5_s1/default | 16 | 1024 | 11772695 | 5350 | 7424 | 5376 | 0 | 0 | 0.764 | 0.081 | 0.004 | 0.004 | 0 | 0.081 | 0.003 | 0.004 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_wall | 1 | 1024 | 776372 | 31855 | 6976 | 6976 | 1 | 0 | 0.989 | 0.141 | 0.023 | 0.027 | 0 | 0.142 | 0.015 | 0.019 | 0 | 0.140 / 0.029 |
| layout5_s1/listener_wall | 2 | 1024 | 776372 | 31855 | 15040 | 15040 | 1 | 0 | 0.988 | 0.099 | 0.023 | 0.012 | 0 | 0.094 | 0.015 | 0.009 | 0 | 0.093 / 0.056 |
| layout5_s1/listener_wall | 4 | 1024 | 776372 | 31855 | 31104 | 31104 | 1 | 0 | 0.990 | 0.070 | 0.023 | 0.006 | 0 | 0.066 | 0.015 | 0.004 | 0 | 0.025 / 0.007 |
| layout5_s1/listener_wall | 8 | 1024 | 776372 | 31855 | 63296 | 31872 | 0 | 0 | 0.507 | 0.070 | 0.023 | 0.006 | 0 | 0.066 | 0.015 | 0.004 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_wall | 16 | 1024 | 776372 | 31855 | 127680 | 31872 | 0 | 0 | 0.254 | 0.070 | 0.023 | 0.006 | 0 | 0.066 | 0.015 | 0.004 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_edge | 1 | 1024 | 890484 | 49891 | 5952 | 5952 | 1 | 0 | 0.988 | 0.248 | 0.043 | 0.050 | 0 | 0.215 | 0.040 | 0.048 | 0 | 0.184 / 0.017 |
| layout5_s1/listener_edge | 2 | 1024 | 890484 | 49891 | 12992 | 12992 | 1 | 0 | 0.991 | 0.168 | 0.043 | 0.032 | 0 | 0.145 | 0.035 | 0.017 | 0 | 0.116 / 0.036 |
| layout5_s1/listener_edge | 4 | 1024 | 890484 | 49891 | 27008 | 27008 | 1 | 0 | 0.991 | 0.120 | 0.043 | 0.015 | 0 | 0.105 | 0.035 | 0.008 | 0 | 0.026 / 0.127 |
| layout5_s1/listener_edge | 8 | 1024 | 890484 | 49891 | 55040 | 49920 | 0 | 0 | 0.900 | 0.090 | 0.043 | 0.008 | 0 | 0.081 | 0.035 | 0.005 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_edge | 16 | 1024 | 890484 | 49891 | 111168 | 49920 | 0 | 0 | 0.450 | 0.090 | 0.043 | 0.008 | 0 | 0.081 | 0.035 | 0.005 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_corner | 1 | 1024 | 1098099 | 30642 | 4608 | 4608 | 1 | 0 | 0.990 | 0.225 | 0.060 | 0.074 | 0 | 0.200 | 0.022 | 0.026 | 0 | 0.283 / 0.227 |
| layout5_s1/listener_corner | 2 | 1024 | 1098099 | 30642 | 10304 | 10304 | 1 | 0 | 0.997 | 0.153 | 0.041 | 0.039 | 0 | 0.147 | 0.026 | 0.021 | 0 | 0.046 / 0.076 |
| layout5_s1/listener_corner | 4 | 1024 | 1098099 | 30642 | 21696 | 21696 | 1 | 0 | 1.000 | 0.109 | 0.041 | 0.021 | 0 | 0.113 | 0.026 | 0.017 | 0 | 0.038 / 0.030 |
| layout5_s1/listener_corner | 8 | 1024 | 1098099 | 30642 | 44480 | 30656 | 0 | 0 | 0.697 | 0.090 | 0.041 | 0.014 | 0 | 0.095 | 0.026 | 0.013 | 0 | 0.000 / 0.000 |
| layout5_s1/listener_corner | 16 | 1024 | 1098099 | 30642 | 89984 | 30656 | 0 | 0 | 0.348 | 0.090 | 0.041 | 0.014 | 0 | 0.095 | 0.026 | 0.013 | 0 | 0.000 / 0.000 |
| layout5_s1/emitter_wall | 1 | 512 | 3245332 | 47657 | 448 | 448 | 1 | 1 | 0.998 | 0.438 | 0.268 | 0.269 | 1 | 0.266 | 0.016 | 0.035 | 0 | 1.323 / 0.367 |
| layout5_s1/emitter_wall | 2 | 960 | 6102423 | 50813 | 896 | 896 | 1 | 1 | 0.977 | 0.485 | 0.119 | 0.194 | 1 | 0.186 | 0.009 | 0.016 | 0 | 0.244 / 0.083 |
| layout5_s1/emitter_wall | 4 | 1024 | 6508198 | 48525 | 2752 | 2752 | 1 | 0 | 1.001 | 0.329 | 0.059 | 0.085 | 0 | 0.109 | 0.005 | 0.007 | 0 | 0.421 / 0.069 |
| layout5_s1/emitter_wall | 8 | 1024 | 6508198 | 48525 | 6592 | 6592 | 1 | 0 | 1.010 | 0.193 | 0.034 | 0.042 | 0 | 0.074 | 0.003 | 0.003 | 0 | 0.087 / 0.037 |
| layout5_s1/emitter_wall | 16 | 1024 | 6508198 | 48525 | 14272 | 14272 | 1 | 0 | 1.010 | 0.127 | 0.032 | 0.020 | 0 | 0.050 | 0.003 | 0.001 | 0 | 0.000 / 0.000 |
| layout5_s1/both_wall | 1 | 1024 | 1461656 | 35190 | 3200 | 3200 | 1 | 0 | 0.983 | 0.428 | 0.141 | 0.167 | 1 | 0.215 | 0.024 | 0.034 | 0 | 2.215 / 0.175 |
| layout5_s1/both_wall | 2 | 1024 | 1461656 | 35190 | 7488 | 7488 | 1 | 0 | 0.990 | 0.763 | 0.412 | 0.411 | 1 | 0.137 | 0.015 | 0.018 | 0 | 0.847 / 0.030 |
| layout5_s1/both_wall | 4 | 1024 | 1461656 | 35190 | 16064 | 16064 | 1 | 0 | 0.990 | 0.427 | 0.412 | 0.299 | 1 | 0.092 | 0.015 | 0.009 | 0 | 1.288 / 0.083 |
| layout5_s1/both_wall | 8 | 1024 | 1461656 | 35190 | 33152 | 33152 | 1 | 0 | 0.994 | 1.121 | 0.412 | 0.563 | 1 | 0.065 | 0.015 | 0.004 | 0 | 0.090 / 0.020 |
| layout5_s1/both_wall | 16 | 1024 | 1461656 | 35190 | 67328 | 35200 | 0 | 0 | 0.527 | 1.080 | 0.412 | 0.560 | 1 | 0.064 | 0.015 | 0.004 | 0 | 0.000 / 0.000 |
| layout5_s1/both_corner | 1 | 1024 | 3035309 | 28428 | 1024 | 1024 | 1 | 0 | 0.989 | 0.208 | 0.067 | 0.037 | 1 | 0.488 | 0.049 | 0.090 | 1 | 0.744 / 0.119 |
| layout5_s1/both_corner | 2 | 1024 | 3035309 | 28428 | 3072 | 3072 | 1 | 0 | 0.990 | 0.192 | 0.093 | 0.132 | 1 | 0.283 | 0.046 | 0.063 | 0 | 0.477 / 0.036 |
| layout5_s1/both_corner | 4 | 1024 | 3035309 | 28428 | 7168 | 7168 | 1 | 0 | 0.992 | 0.145 | 0.069 | 0.077 | 1 | 0.215 | 0.031 | 0.044 | 0 | 0.296 / 0.077 |
| layout5_s1/both_corner | 8 | 1024 | 3035309 | 28428 | 15424 | 15424 | 1 | 0 | 0.991 | 0.223 | 0.069 | 0.640 | 1 | 0.141 | 0.031 | 0.020 | 0 | 0.161 / 0.170 |
| layout5_s1/both_corner | 16 | 1024 | 3035309 | 28428 | 31872 | 28480 | 0 | 0 | 0.891 | 0.156 | 0.069 | 0.227 | 0 | 0.107 | 0.031 | 0.009 | 0 | 0.000 / 0.000 |

## T4. 30-replicate p95 at the gated cubes (F4), 1 kHz

| scene | × | e | median error dB | p95 \|error\| dB | max \|error\| dB | achieved SE median dB | 30 replicates took (ms, pool 4) |
|---|---|---|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | 1 | 0 | +0.003 | 0.254 | 0.406 | 0.117 | 2291 |
| cube100_lowalpha0.05_s0.3 | 1 | 1 | +0.026 | 0.179 | 0.261 | 0.115 | 2291 |
| cube100_lowalpha0.05_s0.3 | 4 | 0 | -0.007 | 0.157 | 0.189 | 0.071 | 5206 |
| cube100_lowalpha0.05_s0.3 | 4 | 1 | +0.007 | 0.158 | 0.232 | 0.073 | 5206 |
| cube100_lowalpha0.05_s0.3 | 16 | 0 | -0.003 | 0.157 | 0.189 | 0.071 | 5813 |
| cube100_lowalpha0.05_s0.3 | 16 | 1 | +0.007 | 0.158 | 0.232 | 0.073 | 5813 |
| cube100_flutter_fallback | 1 | 0 | +0.000 | 0.003 | 0.005 | 0.002 | 4826 |
| cube100_flutter_fallback | 1 | 1 | -0.000 | 0.005 | 0.015 | 0.002 | 4826 |
| cube100_flutter_fallback | 4 | 0 | -0.000 | 0.002 | 0.003 | 0.001 | 10655 |
| cube100_flutter_fallback | 4 | 1 | +0.000 | 0.003 | 0.003 | 0.001 | 10655 |
| cube100_flutter_fallback | 16 | 0 | -0.000 | 0.002 | 0.003 | 0.001 | 11419 |
| cube100_flutter_fallback | 16 | 1 | +0.000 | 0.003 | 0.003 | 0.001 | 11419 |

Long runs: low-α s = 0.3 2^20 histories SE 0.006 dB (20.5 s); flutter SE 0.000 dB (152.8 s). The ×4 and ×16
rows of the low-α cube are identical draws except the median: N = 3 584 at both (saturated, finding 2).

## T5. F12 projection: 14 × (worst restore + worst solve at W), per OS

**Sources.** R = worst-of-10 keyless restore at the pin (it already contains one stage-1 solve), taken as
max(x14worst)/14 over the three green S2 CI runs 43389296112, 43402114873, 43412038058
(`docs/review/phase-07c-1b/23-s2-records-excerpt.md`, the `05h-records GATE` lines); plus the macOS PR #33 run
43427854710 (14 × worst 30.50 s, `tests/unit/test_diffuse_records.cpp` register comment). For the s = 1 cube
(not a gated build, no GATE line) R = the "as AX48/AX49 build it" worst of run 43291051799
(`docs/review/phase-07c-1/44-orchestrator-ci-records-43291051799.md`: Linux 1 823, macOS 2 171, Windows
1 682 ms; older code than S2). S_pin = the largest S2 `solveMedianMs` of that OS and scene (a median of 10, so
it understates the worst solve by up to the register's solveK 1.08–1.22); for the s = 1 cube the low-α s = 0.3
value is used (same pin work, 6.01 M vs 6.04 M evaluations; local ns/eval within 4 %). **S(W) = S_pin × the
realised-work ratio work(W)/work(×1) measured here** (T1/T2 show time ∝ realised work). I did not run the
`[diffuse-records]` restore test.

Two forms: the literal F12 form 14 × (R + S(W)) (counts the pin's solve twice, conservative), and 14 × (R −
S_pin + S(W)) (the solve inside the restore replaced by the solve at W).

| scene | OS | worst restore R (ms) | worst solve median S_pin (ms) | x | work(W)/work(pin) | S(W) ms | 14x(R+S(W)) s [F12 literal] | 14x(R-S_pin+S(W)) s [solve replaced] |
|---|---|---|---|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | Linux | 1446 | 98.7 | 1 | 1.00 | 99 | 21.62 | 20.24 |
| cube100_lowalpha0.05_s0.3 | Linux | 1446 | 98.7 | 2 | 1.26 | 125 | 21.99 | 20.61 |
| cube100_lowalpha0.05_s0.3 | Linux | 1446 | 98.7 | 4 | 1.26 | 125 | 21.99 | 20.61 |
| cube100_lowalpha0.05_s0.3 | Linux | 1446 | 98.7 | 8 | 1.26 | 125 | 21.99 | 20.61 |
| cube100_lowalpha0.05_s0.3 | Linux | 1446 | 98.7 | 16 | 1.26 | 125 | 21.99 | 20.61 |
| cube100_lowalpha0.05_s0.3 | macOS | 1720 | 86.9 | 1 | 1.00 | 87 | 25.30 | 24.08 |
| cube100_lowalpha0.05_s0.3 | macOS | 1720 | 86.9 | 2 | 1.26 | 110 | 25.62 | 24.40 |
| cube100_lowalpha0.05_s0.3 | macOS | 1720 | 86.9 | 4 | 1.26 | 110 | 25.62 | 24.40 |
| cube100_lowalpha0.05_s0.3 | macOS | 1720 | 86.9 | 8 | 1.26 | 110 | 25.62 | 24.40 |
| cube100_lowalpha0.05_s0.3 | macOS | 1720 | 86.9 | 16 | 1.26 | 110 | 25.62 | 24.40 |
| cube100_lowalpha0.05_s0.3 | Windows | 1446 | 71.8 | 1 | 1.00 | 72 | 21.25 | 20.24 |
| cube100_lowalpha0.05_s0.3 | Windows | 1446 | 71.8 | 2 | 1.26 | 91 | 21.51 | 20.51 |
| cube100_lowalpha0.05_s0.3 | Windows | 1446 | 71.8 | 4 | 1.26 | 91 | 21.51 | 20.51 |
| cube100_lowalpha0.05_s0.3 | Windows | 1446 | 71.8 | 8 | 1.26 | 91 | 21.51 | 20.51 |
| cube100_lowalpha0.05_s0.3 | Windows | 1446 | 71.8 | 16 | 1.26 | 91 | 21.51 | 20.51 |
| cube100_flutter_fallback | Linux | 736 | 159.0 | 1 | 1.00 | 159 | 12.54 | 10.31 |
| cube100_flutter_fallback | Linux | 736 | 159.0 | 2 | 2.12 | 337 | 15.03 | 12.80 |
| cube100_flutter_fallback | Linux | 736 | 159.0 | 4 | 3.52 | 560 | 18.15 | 15.92 |
| cube100_flutter_fallback | Linux | 736 | 159.0 | 8 | 3.52 | 560 | 18.15 | 15.92 |
| cube100_flutter_fallback | Linux | 736 | 159.0 | 16 | 3.52 | 560 | 18.15 | 15.92 |
| cube100_flutter_fallback | macOS | 711 | 118.5 | 1 | 1.00 | 118 | 11.62 | 9.96 |
| cube100_flutter_fallback | macOS | 711 | 118.5 | 2 | 2.12 | 251 | 13.47 | 11.82 |
| cube100_flutter_fallback | macOS | 711 | 118.5 | 4 | 3.52 | 417 | 15.80 | 14.14 |
| cube100_flutter_fallback | macOS | 711 | 118.5 | 8 | 3.52 | 417 | 15.80 | 14.14 |
| cube100_flutter_fallback | macOS | 711 | 118.5 | 16 | 3.52 | 417 | 15.80 | 14.14 |
| cube100_flutter_fallback | Windows | 596 | 114.5 | 1 | 1.00 | 114 | 9.94 | 8.34 |
| cube100_flutter_fallback | Windows | 596 | 114.5 | 2 | 2.12 | 243 | 11.74 | 10.13 |
| cube100_flutter_fallback | Windows | 596 | 114.5 | 4 | 3.52 | 403 | 13.99 | 12.38 |
| cube100_flutter_fallback | Windows | 596 | 114.5 | 8 | 3.52 | 403 | 13.99 | 12.38 |
| cube100_flutter_fallback | Windows | 596 | 114.5 | 16 | 3.52 | 403 | 13.99 | 12.38 |
| cube100_lowalpha0.05_s1 | Linux (run 43291051799) | 1823 | 98.7 | 1 | 1.00 | 99 | 26.90 | 25.52 |
| cube100_lowalpha0.05_s1 | Linux (run 43291051799) | 1823 | 98.7 | 2 | 2.02 | 200 | 28.32 | 26.93 |
| cube100_lowalpha0.05_s1 | Linux (run 43291051799) | 1823 | 98.7 | 4 | 4.04 | 399 | 31.11 | 29.73 |
| cube100_lowalpha0.05_s1 | Linux (run 43291051799) | 1823 | 98.7 | 8 | 8.08 | 798 | 36.69 | 35.31 |
| cube100_lowalpha0.05_s1 | Linux (run 43291051799) | 1823 | 98.7 | 16 | 16.10 | 1589 | 47.77 | 46.39 |
| cube100_lowalpha0.05_s1 | macOS (run 43291051799) | 2171 | 86.9 | 1 | 1.00 | 87 | 31.61 | 30.39 |
| cube100_lowalpha0.05_s1 | macOS (run 43291051799) | 2171 | 86.9 | 2 | 2.02 | 176 | 32.85 | 31.64 |
| cube100_lowalpha0.05_s1 | macOS (run 43291051799) | 2171 | 86.9 | 4 | 4.04 | 351 | 35.31 | 34.10 |
| cube100_lowalpha0.05_s1 | macOS (run 43291051799) | 2171 | 86.9 | 8 | 8.08 | 702 | 40.23 | 39.01 |
| cube100_lowalpha0.05_s1 | macOS (run 43291051799) | 2171 | 86.9 | 16 | 16.10 | 1399 | 49.98 | 48.77 |
| cube100_lowalpha0.05_s1 | Windows (run 43291051799) | 1682 | 71.8 | 1 | 1.00 | 72 | 24.55 | 23.55 |
| cube100_lowalpha0.05_s1 | Windows (run 43291051799) | 1682 | 71.8 | 2 | 2.02 | 145 | 25.58 | 24.57 |
| cube100_lowalpha0.05_s1 | Windows (run 43291051799) | 1682 | 71.8 | 4 | 4.04 | 290 | 27.61 | 26.61 |
| cube100_lowalpha0.05_s1 | Windows (run 43291051799) | 1682 | 71.8 | 8 | 8.08 | 580 | 31.67 | 30.67 |
| cube100_lowalpha0.05_s1 | Windows (run 43291051799) | 1682 | 71.8 | 16 | 16.10 | 1156 | 39.73 | 38.73 |
| cube100_lowalpha0.05_s0.3 | macOS (PR #33 run 43427854710) | 2179 | 86.9 | 1 | 1.00 | 87 | 31.72 | 30.50 |
| cube100_lowalpha0.05_s0.3 | macOS (PR #33 run 43427854710) | 2179 | 86.9 | 2 | 1.26 | 110 | 32.04 | 30.82 |
| cube100_lowalpha0.05_s0.3 | macOS (PR #33 run 43427854710) | 2179 | 86.9 | 4 | 1.26 | 110 | 32.04 | 30.82 |
| cube100_lowalpha0.05_s0.3 | macOS (PR #33 run 43427854710) | 2179 | 86.9 | 8 | 1.26 | 110 | 32.04 | 30.82 |
| cube100_lowalpha0.05_s0.3 | macOS (PR #33 run 43427854710) | 2179 | 86.9 | 16 | 1.26 | 110 | 32.04 | 30.82 |

## CI note

The tag `[benchmark]` was asked for, so the CI "Benchmark (release)" step (`spatial_tests "[benchmark]"`) will
now also run both cases on every OS: about 7.5 min on this machine (the flutter long run is 2.5 min of it), less
on the hosted runners. That is how F3 per OS would be obtained; if the extra CI time is not wanted, drop
`[benchmark]` and run `[wmax-sweep]` by hand.

## Raw printed lines

### Sweep (`spatial_tests "wmax-sweep: the diffuse solve*"`)

```
Filters: "wmax-sweep: the diffuse solve*"
Randomness seeded to: 1694094763
wsweep machine: process pool 4 threads (hardware_concurrency); single-thread pool 1
wsweep cube100_lowalpha0.05_s0.3    x1  W_max 3050000 W_scene 6100000 | pool(4) min 72.5 median 91.4 worst 92.8 ms (3 runs); single-thread 308.7 ms; ns/eval pool 15.13 single 51.06 | peak RSS delta 1.9 MB | n* 1024 W_pilot 1696086 N_need 3574 N_cap 2624 N 2624 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 4348889 realised/W_scene 0.9910
wsweep cube100_lowalpha0.05_s0.3    x1  e0 achieved SE 0.092 dB VOV_union 0.084 U 0 | SE dB per band 0.092 0.092 0.092 0.092 0.092 0.092 0.092 0.092 | VOV per band 0.131 0.131 0.131 0.131 0.131 0.131 0.131 0.131
wsweep cube100_lowalpha0.05_s0.3    x1  e1 achieved SE 0.075 dB VOV_union 0.122 U 0 | SE dB per band 0.075 0.075 0.074 0.074 0.074 0.074 0.074 0.074 | VOV per band 0.155 0.155 0.155 0.155 0.155 0.155 0.155 0.155
wsweep cube100_lowalpha0.05_s0.3    x2  W_max 6100000 W_scene 12200000 | pool(4) min 91.0 median 116.6 worst 145.6 ms (3 runs); single-thread 331.5 ms; ns/eval pool 15.25 single 43.36 | peak RSS delta 2.3 MB | n* 1024 W_pilot 1696086 N_need 3574 N_cap 6336 N 3584 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 5949537 realised/W_scene 0.6267
wsweep cube100_lowalpha0.05_s0.3    x2  e0 achieved SE 0.088 dB VOV_union 0.125 U 0 | SE dB per band 0.088 0.088 0.088 0.088 0.088 0.088 0.088 0.088 | VOV per band 0.183 0.183 0.183 0.183 0.183 0.183 0.183 0.183
wsweep cube100_lowalpha0.05_s0.3    x2  e1 achieved SE 0.075 dB VOV_union 0.137 U 0 | SE dB per band 0.075 0.075 0.075 0.075 0.075 0.075 0.075 0.075 | VOV per band 0.192 0.192 0.192 0.192 0.192 0.192 0.192 0.192
wsweep cube100_lowalpha0.05_s0.3    x4  W_max 12200000 W_scene 24400000 | pool(4) min 87.5 median 87.7 worst 89.2 ms (3 runs); single-thread 325.5 ms; ns/eval pool 11.47 single 42.58 | peak RSS delta 2.4 MB | n* 1024 W_pilot 1696086 N_need 3574 N_cap 13696 N 3584 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 5949537 realised/W_scene 0.3133
wsweep cube100_lowalpha0.05_s0.3    x4  e0 achieved SE 0.088 dB VOV_union 0.125 U 0 | SE dB per band 0.088 0.088 0.088 0.088 0.088 0.088 0.088 0.088 | VOV per band 0.183 0.183 0.183 0.183 0.183 0.183 0.183 0.183
wsweep cube100_lowalpha0.05_s0.3    x4  e1 achieved SE 0.075 dB VOV_union 0.137 U 0 | SE dB per band 0.075 0.075 0.075 0.075 0.075 0.075 0.075 0.075 | VOV per band 0.192 0.192 0.192 0.192 0.192 0.192 0.192 0.192
wsweep cube100_lowalpha0.05_s0.3    x8  W_max 24400000 W_scene 48800000 | pool(4) min 86.6 median 96.8 worst 104.6 ms (3 runs); single-thread 330.1 ms; ns/eval pool 12.67 single 43.17 | peak RSS delta 2.4 MB | n* 1024 W_pilot 1696086 N_need 3574 N_cap 28416 N 3584 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 5949537 realised/W_scene 0.1567
wsweep cube100_lowalpha0.05_s0.3    x8  e0 achieved SE 0.088 dB VOV_union 0.125 U 0 | SE dB per band 0.088 0.088 0.088 0.088 0.088 0.088 0.088 0.088 | VOV per band 0.183 0.183 0.183 0.183 0.183 0.183 0.183 0.183
wsweep cube100_lowalpha0.05_s0.3    x8  e1 achieved SE 0.075 dB VOV_union 0.137 U 0 | SE dB per band 0.075 0.075 0.075 0.075 0.075 0.075 0.075 0.075 | VOV per band 0.192 0.192 0.192 0.192 0.192 0.192 0.192 0.192
wsweep cube100_lowalpha0.05_s0.3    x16 W_max 48800000 W_scene 97600000 | pool(4) min 88.5 median 89.0 worst 129.4 ms (3 runs); single-thread 328.3 ms; ns/eval pool 11.64 single 42.93 | peak RSS delta 2.4 MB | n* 1024 W_pilot 1696086 N_need 3574 N_cap 57856 N 3584 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 5949537 realised/W_scene 0.0783
wsweep cube100_lowalpha0.05_s0.3    x16 e0 achieved SE 0.088 dB VOV_union 0.125 U 0 | SE dB per band 0.088 0.088 0.088 0.088 0.088 0.088 0.088 0.088 | VOV per band 0.183 0.183 0.183 0.183 0.183 0.183 0.183 0.183
wsweep cube100_lowalpha0.05_s0.3    x16 e1 achieved SE 0.075 dB VOV_union 0.137 U 0 | SE dB per band 0.075 0.075 0.075 0.075 0.075 0.075 0.075 0.075 | VOV per band 0.192 0.192 0.192 0.192 0.192 0.192 0.192 0.192
wsweep cube100_lowalpha0.05_s0.3    x1  e0 total minus x16 total, dB per band -0.007 -0.007 -0.007 -0.007 -0.007 -0.007 -0.007 -0.007
wsweep cube100_lowalpha0.05_s0.3    x1  e1 total minus x16 total, dB per band -0.041 -0.041 -0.041 -0.041 -0.041 -0.041 -0.041 -0.041
wsweep cube100_lowalpha0.05_s0.3    x2  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x2  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x4  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x4  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x8  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x8  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s0.3    x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x1  W_max 3050000 W_scene 6100000 | pool(4) min 119.7 median 128.7 worst 137.6 ms (3 runs); single-thread 322.3 ms; ns/eval pool 22.57 single 56.52 | peak RSS delta 3.3 MB | n* 320 W_pilot 3154338 N_need 1 N_cap 256 N 256 cap hit 0 floor truncated 1 pilot shipped 0 | W_final 2547436 realised/W_scene 0.9347
wsweep cube100_flutter_fallback     x1  e0 achieved SE 0.002 dB VOV_union 0.152 U 0 | SE dB per band 0.002 0.002 0.002 0.002 0.002 0.002 0.002 0.002 | VOV per band 0.232 0.232 0.232 0.232 0.232 0.232 0.232 0.232
wsweep cube100_flutter_fallback     x1  e1 achieved SE 0.001 dB VOV_union 0.238 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.105 0.105 0.105 0.105 0.105 0.105 0.105 0.105
wsweep cube100_flutter_fallback     x2  W_max 6100000 W_scene 12200000 | pool(4) min 249.8 median 250.1 worst 256.7 ms (3 runs); single-thread 634.4 ms; ns/eval pool 20.70 single 52.52 | peak RSS delta 3.2 MB | n* 640 W_pilot 6364347 N_need 1 N_cap 576 N 576 cap hit 0 floor truncated 1 pilot shipped 0 | W_final 5714224 realised/W_scene 0.9900
wsweep cube100_flutter_fallback     x2  e0 achieved SE 0.001 dB VOV_union 0.087 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.103 0.103 0.103 0.103 0.103 0.103 0.103 0.103
wsweep cube100_flutter_fallback     x2  e1 achieved SE 0.001 dB VOV_union 0.125 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.045 0.045 0.045 0.045 0.045 0.045 0.045 0.045
wsweep cube100_flutter_fallback     x4  W_max 12200000 W_scene 24400000 | pool(4) min 344.5 median 411.9 worst 435.5 ms (3 runs); single-thread 1072.1 ms; ns/eval pool 20.51 single 53.38 | peak RSS delta 3.4 MB | n* 1024 W_pilot 10101864 N_need 1 N_cap 1408 N 1024 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 9981081 realised/W_scene 0.8231
wsweep cube100_flutter_fallback     x4  e0 achieved SE 0.001 dB VOV_union 0.037 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.053 0.053 0.053 0.053 0.053 0.053 0.053 0.053
wsweep cube100_flutter_fallback     x4  e1 achieved SE 0.001 dB VOV_union 0.048 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.063 0.063 0.063 0.063 0.063 0.063 0.063 0.063
wsweep cube100_flutter_fallback     x8  W_max 24400000 W_scene 48800000 | pool(4) min 430.8 median 445.7 worst 453.9 ms (3 runs); single-thread 1048.3 ms; ns/eval pool 22.19 single 52.20 | peak RSS delta 3.4 MB | n* 1024 W_pilot 10101864 N_need 1 N_cap 3904 N 1024 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 9981081 realised/W_scene 0.4115
wsweep cube100_flutter_fallback     x8  e0 achieved SE 0.001 dB VOV_union 0.037 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.053 0.053 0.053 0.053 0.053 0.053 0.053 0.053
wsweep cube100_flutter_fallback     x8  e1 achieved SE 0.001 dB VOV_union 0.048 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.063 0.063 0.063 0.063 0.063 0.063 0.063 0.063
wsweep cube100_flutter_fallback     x16 W_max 48800000 W_scene 97600000 | pool(4) min 332.1 median 347.0 worst 358.9 ms (3 runs); single-thread 1047.4 ms; ns/eval pool 17.28 single 52.15 | peak RSS delta 3.3 MB | n* 1024 W_pilot 10101864 N_need 1 N_cap 8832 N 1024 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 9981081 realised/W_scene 0.2058
wsweep cube100_flutter_fallback     x16 e0 achieved SE 0.001 dB VOV_union 0.037 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.053 0.053 0.053 0.053 0.053 0.053 0.053 0.053
wsweep cube100_flutter_fallback     x16 e1 achieved SE 0.001 dB VOV_union 0.048 U 0 | SE dB per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001 | VOV per band 0.063 0.063 0.063 0.063 0.063 0.063 0.063 0.063
wsweep cube100_flutter_fallback     x1  e0 total minus x16 total, dB per band -0.000 -0.000 -0.000 -0.000 -0.000 -0.000 -0.000 -0.000
wsweep cube100_flutter_fallback     x1  e1 total minus x16 total, dB per band -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003
wsweep cube100_flutter_fallback     x2  e0 total minus x16 total, dB per band -0.002 -0.002 -0.002 -0.002 -0.002 -0.002 -0.002 -0.002
wsweep cube100_flutter_fallback     x2  e1 total minus x16 total, dB per band -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003
wsweep cube100_flutter_fallback     x4  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x4  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x8  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x8  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_flutter_fallback     x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s1      x1  W_max 3050000 W_scene 6100000 | pool(4) min 92.6 median 94.6 worst 99.1 ms (3 runs); single-thread 258.6 ms; ns/eval pool 15.73 single 42.99 | peak RSS delta 2.0 MB | n* 1024 W_pilot 1666253 N_need 58612 N_cap 2688 N 2688 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 4347497 realised/W_scene 0.9859
wsweep cube100_lowalpha0.05_s1      x1  e0 achieved SE 0.360 dB VOV_union 0.126 U 1 | SE dB per band 0.360 0.360 0.360 0.360 0.360 0.360 0.360 0.360 | VOV per band 0.153 0.153 0.153 0.153 0.153 0.153 0.153 0.153
wsweep cube100_lowalpha0.05_s1      x1  e1 achieved SE 0.359 dB VOV_union 0.154 U 1 | SE dB per band 0.359 0.359 0.359 0.359 0.359 0.359 0.359 0.359 | VOV per band 0.185 0.185 0.185 0.185 0.185 0.185 0.185 0.185
wsweep cube100_lowalpha0.05_s1      x2  W_max 6100000 W_scene 12200000 | pool(4) min 172.4 median 174.0 worst 175.1 ms (3 runs); single-thread 534.4 ms; ns/eval pool 14.31 single 43.96 | peak RSS delta 3.6 MB | n* 1024 W_pilot 1666253 N_need 58612 N_cap 6464 N 6464 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 10490028 realised/W_scene 0.9964
wsweep cube100_lowalpha0.05_s1      x2  e0 achieved SE 0.287 dB VOV_union 0.110 U 0 | SE dB per band 0.287 0.287 0.287 0.287 0.287 0.287 0.287 0.287 | VOV per band 0.117 0.117 0.117 0.117 0.117 0.117 0.117 0.117
wsweep cube100_lowalpha0.05_s1      x2  e1 achieved SE 0.251 dB VOV_union 0.088 U 0 | SE dB per band 0.251 0.251 0.251 0.251 0.251 0.251 0.251 0.251 | VOV per band 0.099 0.099 0.099 0.099 0.099 0.099 0.099 0.099
wsweep cube100_lowalpha0.05_s1      x4  W_max 12200000 W_scene 24400000 | pool(4) min 302.3 median 342.7 worst 417.8 ms (3 runs); single-thread 1203.5 ms; ns/eval pool 14.09 single 49.48 | peak RSS delta 6.3 MB | n* 1024 W_pilot 1666253 N_need 58612 N_cap 13952 N 13952 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 22655048 realised/W_scene 0.9968
wsweep cube100_lowalpha0.05_s1      x4  e0 achieved SE 0.186 dB VOV_union 0.100 U 0 | SE dB per band 0.186 0.186 0.186 0.186 0.186 0.186 0.186 0.186 | VOV per band 0.093 0.093 0.093 0.093 0.093 0.093 0.093 0.093
wsweep cube100_lowalpha0.05_s1      x4  e1 achieved SE 0.183 dB VOV_union 0.080 U 0 | SE dB per band 0.183 0.183 0.183 0.183 0.183 0.183 0.183 0.183 | VOV per band 0.050 0.050 0.050 0.050 0.050 0.050 0.050 0.050
wsweep cube100_lowalpha0.05_s1      x8  W_max 24400000 W_scene 48800000 | pool(4) min 694.9 median 791.4 worst 800.7 ms (3 runs); single-thread 2432.9 ms; ns/eval pool 16.28 single 50.05 | peak RSS delta 10.5 MB | n* 1024 W_pilot 1666253 N_need 58612 N_cap 28928 N 28928 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 46939886 realised/W_scene 0.9960
wsweep cube100_lowalpha0.05_s1      x8  e0 achieved SE 0.134 dB VOV_union 0.100 U 0 | SE dB per band 0.134 0.134 0.134 0.134 0.134 0.134 0.134 0.134 | VOV per band 0.030 0.030 0.030 0.030 0.030 0.030 0.030 0.030
wsweep cube100_lowalpha0.05_s1      x8  e1 achieved SE 0.123 dB VOV_union 0.080 U 0 | SE dB per band 0.123 0.123 0.123 0.123 0.123 0.123 0.123 0.123 | VOV per band 0.023 0.023 0.023 0.023 0.023 0.023 0.023 0.023
wsweep cube100_lowalpha0.05_s1      x16 W_max 48800000 W_scene 97600000 | pool(4) min 1195.2 median 1198.3 worst 1210.1 ms (3 runs); single-thread 4431.8 ms; ns/eval pool 12.38 single 45.77 | peak RSS delta 21.3 MB | n* 1024 W_pilot 1666253 N_need 58612 N_cap 58944 N 58624 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 95160465 realised/W_scene 0.9921
wsweep cube100_lowalpha0.05_s1      x16 e0 achieved SE 0.095 dB VOV_union 0.100 U 0 | SE dB per band 0.095 0.095 0.095 0.095 0.095 0.095 0.095 0.095 | VOV per band 0.015 0.015 0.015 0.015 0.015 0.015 0.015 0.015
wsweep cube100_lowalpha0.05_s1      x16 e1 achieved SE 0.094 dB VOV_union 0.080 U 0 | SE dB per band 0.094 0.094 0.094 0.094 0.094 0.094 0.094 0.094 | VOV per band 0.013 0.013 0.013 0.013 0.013 0.013 0.013 0.013
wsweep cube100_lowalpha0.05_s1      x1  e0 total minus x16 total, dB per band +0.060 +0.060 +0.060 +0.060 +0.060 +0.060 +0.060 +0.060
wsweep cube100_lowalpha0.05_s1      x1  e1 total minus x16 total, dB per band -0.291 -0.291 -0.291 -0.291 -0.291 -0.291 -0.291 -0.291
wsweep cube100_lowalpha0.05_s1      x2  e0 total minus x16 total, dB per band +0.134 +0.134 +0.134 +0.134 +0.134 +0.134 +0.134 +0.134
wsweep cube100_lowalpha0.05_s1      x2  e1 total minus x16 total, dB per band -0.322 -0.322 -0.322 -0.322 -0.322 -0.322 -0.322 -0.322
wsweep cube100_lowalpha0.05_s1      x4  e0 total minus x16 total, dB per band -0.228 -0.228 -0.228 -0.228 -0.228 -0.228 -0.228 -0.228
wsweep cube100_lowalpha0.05_s1      x4  e1 total minus x16 total, dB per band -0.169 -0.169 -0.169 -0.169 -0.169 -0.169 -0.169 -0.169
wsweep cube100_lowalpha0.05_s1      x8  e0 total minus x16 total, dB per band -0.044 -0.044 -0.044 -0.044 -0.044 -0.044 -0.044 -0.044
wsweep cube100_lowalpha0.05_s1      x8  e1 total minus x16 total, dB per band -0.161 -0.161 -0.161 -0.161 -0.161 -0.161 -0.161 -0.161
wsweep cube100_lowalpha0.05_s1      x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep cube100_lowalpha0.05_s1      x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/default           x1  W_max 3050000 W_scene 6100000 | pool(4) min 117.6 median 123.1 worst 130.9 ms (3 runs); single-thread 350.6 ms; ns/eval pool 19.94 single 56.80 | peak RSS delta 0.0 MB | n* 512 W_pilot 3446895 N_need 12294 N_cap 384 N 384 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2725372 realised/W_scene 1.0118
wsweep layout4_s1/default           x1  e0 achieved SE 0.474 dB VOV_union 0.021 U 1 | SE dB per band 0.474 0.474 0.474 0.474 0.474 0.474 0.474 0.474 | VOV per band 0.052 0.052 0.052 0.052 0.052 0.052 0.052 0.052
wsweep layout4_s1/default           x1  e1 achieved SE 0.429 dB VOV_union 0.016 U 1 | SE dB per band 0.428 0.428 0.428 0.428 0.428 0.428 0.428 0.429 | VOV per band 0.028 0.028 0.028 0.028 0.028 0.028 0.028 0.028
wsweep layout4_s1/default           x2  W_max 6100000 W_scene 12200000 | pool(4) min 260.2 median 269.9 worst 289.7 ms (3 runs); single-thread 750.2 ms; ns/eval pool 21.87 single 60.77 | peak RSS delta 0.0 MB | n* 960 W_pilot 6474282 N_need 11910 N_cap 832 N 832 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5871157 realised/W_scene 1.0119
wsweep layout4_s1/default           x2  e0 achieved SE 0.302 dB VOV_union 0.009 U 0 | SE dB per band 0.302 0.302 0.302 0.302 0.302 0.302 0.302 0.302 | VOV per band 0.019 0.019 0.019 0.019 0.019 0.019 0.019 0.019
wsweep layout4_s1/default           x2  e1 achieved SE 0.298 dB VOV_union 0.008 U 0 | SE dB per band 0.298 0.298 0.298 0.298 0.298 0.298 0.298 0.298 | VOV per band 0.014 0.014 0.014 0.014 0.014 0.014 0.014 0.014
wsweep layout4_s1/default           x4  W_max 12200000 W_scene 24400000 | pool(4) min 384.7 median 447.6 worst 458.5 ms (3 runs); single-thread 1453.8 ms; ns/eval pool 18.09 single 58.75 | peak RSS delta 0.0 MB | n* 1024 W_pilot 6913401 N_need 11714 N_cap 2560 N 2560 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 17832688 realised/W_scene 1.0142
wsweep layout4_s1/default           x4  e0 achieved SE 0.171 dB VOV_union 0.004 U 0 | SE dB per band 0.171 0.171 0.171 0.171 0.171 0.171 0.171 0.171 | VOV per band 0.007 0.007 0.007 0.007 0.007 0.007 0.007 0.007
wsweep layout4_s1/default           x4  e1 achieved SE 0.169 dB VOV_union 0.004 U 0 | SE dB per band 0.169 0.169 0.169 0.169 0.169 0.169 0.169 0.169 | VOV per band 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005
wsweep layout4_s1/default           x8  W_max 24400000 W_scene 48800000 | pool(4) min 765.0 median 778.1 worst 965.4 ms (3 runs); single-thread 2891.0 ms; ns/eval pool 15.61 single 58.00 | peak RSS delta 0.0 MB | n* 1024 W_pilot 6913401 N_need 11714 N_cap 6144 N 6144 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 42933770 realised/W_scene 1.0215
wsweep layout4_s1/default           x8  e0 achieved SE 0.110 dB VOV_union 0.002 U 0 | SE dB per band 0.110 0.110 0.110 0.110 0.110 0.110 0.110 0.110 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/default           x8  e1 achieved SE 0.108 dB VOV_union 0.002 U 0 | SE dB per band 0.108 0.108 0.108 0.108 0.108 0.108 0.108 0.108 | VOV per band 0.002 0.002 0.002 0.002 0.002 0.002 0.002 0.002
wsweep layout4_s1/default           x16 W_max 48800000 W_scene 97600000 | pool(4) min 1403.9 median 1527.0 worst 1641.1 ms (3 runs); single-thread 5079.1 ms; ns/eval pool 17.20 single 57.20 | peak RSS delta 0.2 MB | n* 1024 W_pilot 6913401 N_need 11714 N_cap 13376 N 11776 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 81886853 realised/W_scene 0.9098
wsweep layout4_s1/default           x16 e0 achieved SE 0.080 dB VOV_union 0.002 U 0 | SE dB per band 0.080 0.080 0.080 0.080 0.080 0.080 0.080 0.080 | VOV per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001
wsweep layout4_s1/default           x16 e1 achieved SE 0.080 dB VOV_union 0.002 U 0 | SE dB per band 0.080 0.080 0.080 0.080 0.080 0.080 0.080 0.080 | VOV per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001
wsweep layout4_s1/default           x1  e0 total minus x16 total, dB per band +0.383 +0.383 +0.383 +0.383 +0.383 +0.383 +0.383 +0.383
wsweep layout4_s1/default           x1  e1 total minus x16 total, dB per band +0.496 +0.496 +0.496 +0.496 +0.496 +0.496 +0.496 +0.496
wsweep layout4_s1/default           x2  e0 total minus x16 total, dB per band +0.437 +0.437 +0.437 +0.437 +0.437 +0.437 +0.437 +0.437
wsweep layout4_s1/default           x2  e1 total minus x16 total, dB per band +0.314 +0.314 +0.314 +0.314 +0.314 +0.314 +0.314 +0.314
wsweep layout4_s1/default           x4  e0 total minus x16 total, dB per band +0.102 +0.102 +0.102 +0.102 +0.102 +0.102 +0.102 +0.102
wsweep layout4_s1/default           x4  e1 total minus x16 total, dB per band +0.108 +0.108 +0.108 +0.108 +0.108 +0.108 +0.108 +0.108
wsweep layout4_s1/default           x8  e0 total minus x16 total, dB per band +0.028 +0.028 +0.028 +0.028 +0.028 +0.028 +0.028 +0.028
wsweep layout4_s1/default           x8  e1 total minus x16 total, dB per band +0.090 +0.090 +0.090 +0.090 +0.090 +0.090 +0.090 +0.090
wsweep layout4_s1/default           x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/default           x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_wall     x1  W_max 3050000 W_scene 6100000 | pool(4) min 141.8 median 155.1 worst 170.8 ms (3 runs); single-thread 386.5 ms; ns/eval pool 25.35 single 63.15 | peak RSS delta 0.0 MB | n* 384 W_pilot 3267852 N_need 25642 N_cap 320 N 320 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2851937 realised/W_scene 1.0032
wsweep layout4_s1/listener_wall     x1  e0 achieved SE 0.657 dB VOV_union 0.030 U 1 | SE dB per band 0.656 0.656 0.656 0.656 0.656 0.656 0.657 0.657 | VOV per band 0.057 0.057 0.057 0.057 0.057 0.057 0.057 0.057
wsweep layout4_s1/listener_wall     x1  e1 achieved SE 0.690 dB VOV_union 0.038 U 1 | SE dB per band 0.690 0.690 0.690 0.690 0.690 0.690 0.690 0.690 | VOV per band 0.073 0.073 0.073 0.073 0.073 0.073 0.073 0.073
wsweep layout4_s1/listener_wall     x2  W_max 6100000 W_scene 12200000 | pool(4) min 207.5 median 208.8 worst 226.2 ms (3 runs); single-thread 621.1 ms; ns/eval pool 16.90 single 50.27 | peak RSS delta 0.0 MB | n* 768 W_pilot 6596124 N_need 23610 N_cap 640 N 640 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5758303 realised/W_scene 1.0127
wsweep layout4_s1/listener_wall     x2  e0 achieved SE 0.469 dB VOV_union 0.019 U 1 | SE dB per band 0.469 0.469 0.469 0.469 0.469 0.469 0.469 0.469 | VOV per band 0.033 0.033 0.033 0.033 0.033 0.033 0.033 0.033
wsweep layout4_s1/listener_wall     x2  e1 achieved SE 0.473 dB VOV_union 0.016 U 1 | SE dB per band 0.473 0.473 0.473 0.473 0.473 0.473 0.473 0.473 | VOV per band 0.033 0.033 0.033 0.033 0.033 0.033 0.033 0.033
wsweep layout4_s1/listener_wall     x4  W_max 12200000 W_scene 24400000 | pool(4) min 372.1 median 385.0 worst 448.9 ms (3 runs); single-thread 1360.2 ms; ns/eval pool 15.68 single 55.39 | peak RSS delta 0.0 MB | n* 1024 W_pilot 8796474 N_need 23764 N_cap 1792 N 1792 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 15759913 realised/W_scene 1.0064
wsweep layout4_s1/listener_wall     x4  e0 achieved SE 0.319 dB VOV_union 0.014 U 0 | SE dB per band 0.319 0.319 0.319 0.319 0.319 0.319 0.319 0.319 | VOV per band 0.022 0.022 0.022 0.022 0.022 0.022 0.022 0.022
wsweep layout4_s1/listener_wall     x4  e1 achieved SE 0.311 dB VOV_union 0.012 U 0 | SE dB per band 0.311 0.311 0.311 0.311 0.311 0.311 0.311 0.311 | VOV per band 0.020 0.020 0.020 0.020 0.020 0.020 0.020 0.020
wsweep layout4_s1/listener_wall     x8  W_max 24400000 W_scene 48800000 | pool(4) min 669.1 median 692.2 worst 699.1 ms (3 runs); single-thread 2511.6 ms; ns/eval pool 13.98 single 50.74 | peak RSS delta 0.0 MB | n* 1024 W_pilot 8796474 N_need 23764 N_cap 4608 N 4608 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 40700069 realised/W_scene 1.0143
wsweep layout4_s1/listener_wall     x8  e0 achieved SE 0.187 dB VOV_union 0.006 U 0 | SE dB per band 0.187 0.187 0.187 0.187 0.187 0.187 0.187 0.187 | VOV per band 0.007 0.007 0.007 0.007 0.007 0.007 0.007 0.007
wsweep layout4_s1/listener_wall     x8  e1 achieved SE 0.184 dB VOV_union 0.005 U 0 | SE dB per band 0.184 0.184 0.184 0.184 0.184 0.184 0.184 0.184 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout4_s1/listener_wall     x16 W_max 48800000 W_scene 97600000 | pool(4) min 1324.8 median 1394.6 worst 1410.9 ms (3 runs); single-thread 5246.8 ms; ns/eval pool 14.00 single 52.65 | peak RSS delta 0.0 MB | n* 1024 W_pilot 8796474 N_need 23764 N_cap 10304 N 10304 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 90854863 realised/W_scene 1.0210
wsweep layout4_s1/listener_wall     x16 e0 achieved SE 0.124 dB VOV_union 0.004 U 0 | SE dB per band 0.124 0.124 0.124 0.124 0.124 0.124 0.124 0.124 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/listener_wall     x16 e1 achieved SE 0.121 dB VOV_union 0.003 U 0 | SE dB per band 0.121 0.121 0.121 0.121 0.121 0.121 0.121 0.121 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/listener_wall     x1  e0 total minus x16 total, dB per band +0.591 +0.591 +0.591 +0.591 +0.591 +0.591 +0.591 +0.591
wsweep layout4_s1/listener_wall     x1  e1 total minus x16 total, dB per band +0.628 +0.628 +0.628 +0.628 +0.628 +0.628 +0.628 +0.628
wsweep layout4_s1/listener_wall     x2  e0 total minus x16 total, dB per band +0.590 +0.590 +0.590 +0.590 +0.590 +0.590 +0.590 +0.590
wsweep layout4_s1/listener_wall     x2  e1 total minus x16 total, dB per band +0.660 +0.660 +0.660 +0.660 +0.660 +0.660 +0.660 +0.660
wsweep layout4_s1/listener_wall     x4  e0 total minus x16 total, dB per band -0.142 -0.142 -0.142 -0.142 -0.142 -0.142 -0.142 -0.142
wsweep layout4_s1/listener_wall     x4  e1 total minus x16 total, dB per band -0.183 -0.183 -0.183 -0.183 -0.183 -0.183 -0.183 -0.183
wsweep layout4_s1/listener_wall     x8  e0 total minus x16 total, dB per band -0.068 -0.068 -0.068 -0.068 -0.068 -0.068 -0.068 -0.068
wsweep layout4_s1/listener_wall     x8  e1 total minus x16 total, dB per band -0.094 -0.094 -0.094 -0.094 -0.094 -0.094 -0.094 -0.094
wsweep layout4_s1/listener_wall     x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_wall     x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_edge     x1  W_max 3050000 W_scene 6100000 | pool(4) min 126.3 median 150.9 worst 151.2 ms (3 runs); single-thread 285.0 ms; ns/eval pool 27.05 single 51.10 | peak RSS delta 0.0 MB | n* 320 W_pilot 3398464 N_need 20409 N_cap 192 N 192 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2179822 realised/W_scene 0.9145
wsweep layout4_s1/listener_edge     x1  e0 achieved SE 0.925 dB VOV_union 0.040 U 1 | SE dB per band 0.925 0.925 0.925 0.925 0.925 0.925 0.925 0.925 | VOV per band 0.128 0.128 0.128 0.128 0.128 0.128 0.128 0.128
wsweep layout4_s1/listener_edge     x1  e1 achieved SE 0.968 dB VOV_union 0.038 U 1 | SE dB per band 0.968 0.968 0.968 0.968 0.968 0.968 0.968 0.968 | VOV per band 0.117 0.117 0.117 0.117 0.117 0.117 0.117 0.117
wsweep layout4_s1/listener_edge     x2  W_max 6100000 W_scene 12200000 | pool(4) min 227.8 median 251.0 worst 288.6 ms (3 runs); single-thread 672.5 ms; ns/eval pool 20.91 single 56.03 | peak RSS delta 0.0 MB | n* 576 W_pilot 6284253 N_need 19954 N_cap 512 N 512 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5717945 realised/W_scene 0.9838
wsweep layout4_s1/listener_edge     x2  e0 achieved SE 0.555 dB VOV_union 0.020 U 1 | SE dB per band 0.555 0.555 0.555 0.555 0.555 0.555 0.555 0.555 | VOV per band 0.052 0.052 0.052 0.052 0.052 0.052 0.052 0.052
wsweep layout4_s1/listener_edge     x2  e1 achieved SE 0.597 dB VOV_union 0.020 U 1 | SE dB per band 0.597 0.597 0.597 0.597 0.597 0.597 0.597 0.597 | VOV per band 0.054 0.054 0.054 0.054 0.054 0.054 0.054 0.054
wsweep layout4_s1/listener_edge     x4  W_max 12200000 W_scene 24400000 | pool(4) min 407.1 median 423.5 worst 446.1 ms (3 runs); single-thread 1325.3 ms; ns/eval pool 17.68 single 55.34 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11334854 N_need 21829 N_cap 1152 N 1152 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 12614464 realised/W_scene 0.9815
wsweep layout4_s1/listener_edge     x4  e0 achieved SE 0.378 dB VOV_union 0.015 U 1 | SE dB per band 0.378 0.378 0.378 0.378 0.378 0.378 0.378 0.378 | VOV per band 0.037 0.037 0.037 0.037 0.037 0.037 0.037 0.037
wsweep layout4_s1/listener_edge     x4  e1 achieved SE 0.380 dB VOV_union 0.013 U 1 | SE dB per band 0.380 0.380 0.380 0.380 0.380 0.380 0.380 0.380 | VOV per band 0.022 0.022 0.022 0.022 0.022 0.022 0.022 0.022
wsweep layout4_s1/listener_edge     x8  W_max 24400000 W_scene 48800000 | pool(4) min 652.1 median 673.1 worst 731.8 ms (3 runs); single-thread 2363.0 ms; ns/eval pool 14.07 single 49.38 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11334854 N_need 21829 N_cap 3328 N 3328 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 36513610 realised/W_scene 0.9805
wsweep layout4_s1/listener_edge     x8  e0 achieved SE 0.212 dB VOV_union 0.006 U 0 | SE dB per band 0.212 0.212 0.212 0.212 0.212 0.212 0.212 0.212 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout4_s1/listener_edge     x8  e1 achieved SE 0.214 dB VOV_union 0.006 U 0 | SE dB per band 0.214 0.214 0.214 0.214 0.214 0.214 0.214 0.214 | VOV per band 0.007 0.007 0.007 0.007 0.007 0.007 0.007 0.007
wsweep layout4_s1/listener_edge     x16 W_max 48800000 W_scene 97600000 | pool(4) min 1300.2 median 1325.5 worst 1450.8 ms (3 runs); single-thread 5043.8 ms; ns/eval pool 13.72 single 52.20 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11334854 N_need 21829 N_cap 7744 N 7744 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 85289376 realised/W_scene 0.9900
wsweep layout4_s1/listener_edge     x16 e0 achieved SE 0.137 dB VOV_union 0.003 U 0 | SE dB per band 0.137 0.137 0.137 0.137 0.137 0.137 0.137 0.137 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout4_s1/listener_edge     x16 e1 achieved SE 0.139 dB VOV_union 0.003 U 0 | SE dB per band 0.139 0.139 0.139 0.139 0.139 0.139 0.139 0.139 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/listener_edge     x1  e0 total minus x16 total, dB per band -1.145 -1.145 -1.145 -1.145 -1.145 -1.145 -1.145 -1.145
wsweep layout4_s1/listener_edge     x1  e1 total minus x16 total, dB per band -1.253 -1.253 -1.253 -1.253 -1.253 -1.253 -1.253 -1.253
wsweep layout4_s1/listener_edge     x2  e0 total minus x16 total, dB per band -0.939 -0.939 -0.939 -0.939 -0.939 -0.939 -0.939 -0.940
wsweep layout4_s1/listener_edge     x2  e1 total minus x16 total, dB per band -0.911 -0.911 -0.911 -0.911 -0.911 -0.911 -0.911 -0.912
wsweep layout4_s1/listener_edge     x4  e0 total minus x16 total, dB per band -0.758 -0.758 -0.758 -0.758 -0.758 -0.758 -0.758 -0.758
wsweep layout4_s1/listener_edge     x4  e1 total minus x16 total, dB per band -0.789 -0.789 -0.789 -0.789 -0.789 -0.789 -0.789 -0.789
wsweep layout4_s1/listener_edge     x8  e0 total minus x16 total, dB per band -0.187 -0.187 -0.187 -0.187 -0.187 -0.187 -0.187 -0.187
wsweep layout4_s1/listener_edge     x8  e1 total minus x16 total, dB per band -0.270 -0.270 -0.270 -0.270 -0.270 -0.270 -0.270 -0.270
wsweep layout4_s1/listener_edge     x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_edge     x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_corner   x1  W_max 3050000 W_scene 6100000 | pool(4) min 123.9 median 124.9 worst 150.3 ms (3 runs); single-thread 280.0 ms; ns/eval pool 22.05 single 49.42 | peak RSS delta 0.0 MB | n* 256 W_pilot 3809660 N_need 26185 N_cap 128 N 128 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 1855804 realised/W_scene 0.9288
wsweep layout4_s1/listener_corner   x1  e0 achieved SE 0.919 dB VOV_union 0.082 U 1 | SE dB per band 0.919 0.919 0.919 0.919 0.919 0.919 0.919 0.919 | VOV per band 0.085 0.085 0.085 0.085 0.085 0.085 0.085 0.085
wsweep layout4_s1/listener_corner   x1  e1 achieved SE 1.015 dB VOV_union 0.147 U 1 | SE dB per band 1.015 1.015 1.015 1.015 1.015 1.015 1.015 1.015 | VOV per band 0.131 0.131 0.131 0.131 0.131 0.131 0.131 0.131
wsweep layout4_s1/listener_corner   x2  W_max 6100000 W_scene 12200000 | pool(4) min 287.2 median 291.5 worst 296.5 ms (3 runs); single-thread 781.1 ms; ns/eval pool 24.24 single 64.96 | peak RSS delta 0.0 MB | n* 448 W_pilot 6512538 N_need 23487 N_cap 384 N 384 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5510481 realised/W_scene 0.9855
wsweep layout4_s1/listener_corner   x2  e0 achieved SE 0.571 dB VOV_union 0.030 U 1 | SE dB per band 0.571 0.571 0.571 0.571 0.571 0.571 0.571 0.571 | VOV per band 0.051 0.051 0.051 0.051 0.051 0.051 0.051 0.051
wsweep layout4_s1/listener_corner   x2  e1 achieved SE 0.569 dB VOV_union 0.051 U 1 | SE dB per band 0.569 0.569 0.569 0.569 0.569 0.569 0.569 0.569 | VOV per band 0.044 0.044 0.044 0.044 0.044 0.044 0.044 0.044
wsweep layout4_s1/listener_corner   x4  W_max 12200000 W_scene 24400000 | pool(4) min 419.4 median 481.8 worst 568.4 ms (3 runs); single-thread 1189.3 ms; ns/eval pool 20.54 single 50.69 | peak RSS delta 0.0 MB | n* 832 W_pilot 12358081 N_need 23069 N_cap 768 N 768 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 11101389 realised/W_scene 0.9615
wsweep layout4_s1/listener_corner   x4  e0 achieved SE 0.426 dB VOV_union 0.015 U 1 | SE dB per band 0.426 0.426 0.426 0.426 0.426 0.426 0.426 0.426 | VOV per band 0.031 0.031 0.031 0.031 0.031 0.031 0.031 0.031
wsweep layout4_s1/listener_corner   x4  e1 achieved SE 0.433 dB VOV_union 0.021 U 1 | SE dB per band 0.433 0.433 0.433 0.433 0.433 0.433 0.433 0.433 | VOV per band 0.025 0.025 0.025 0.025 0.025 0.025 0.025 0.025
wsweep layout4_s1/listener_corner   x8  W_max 24400000 W_scene 48800000 | pool(4) min 749.3 median 758.2 worst 915.7 ms (3 runs); single-thread 2470.6 ms; ns/eval pool 15.78 single 51.42 | peak RSS delta 0.0 MB | n* 1024 W_pilot 15206241 N_need 24858 N_cap 2240 N 2240 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 32841953 realised/W_scene 0.9846
wsweep layout4_s1/listener_corner   x8  e0 achieved SE 0.254 dB VOV_union 0.009 U 0 | SE dB per band 0.254 0.254 0.254 0.254 0.254 0.254 0.254 0.254 | VOV per band 0.013 0.013 0.013 0.013 0.013 0.013 0.013 0.013
wsweep layout4_s1/listener_corner   x8  e1 achieved SE 0.256 dB VOV_union 0.009 U 0 | SE dB per band 0.256 0.256 0.256 0.256 0.256 0.256 0.256 0.256 | VOV per band 0.010 0.010 0.010 0.010 0.010 0.010 0.010 0.010
wsweep layout4_s1/listener_corner   x16 W_max 48800000 W_scene 97600000 | pool(4) min 1331.0 median 1435.5 worst 1462.3 ms (3 runs); single-thread 4829.1 ms; ns/eval pool 14.94 single 50.27 | peak RSS delta 0.0 MB | n* 1024 W_pilot 15206241 N_need 24858 N_cap 5504 N 5504 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 80856569 realised/W_scene 0.9843
wsweep layout4_s1/listener_corner   x16 e0 achieved SE 0.164 dB VOV_union 0.004 U 0 | SE dB per band 0.164 0.164 0.164 0.164 0.164 0.164 0.164 0.164 | VOV per band 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005
wsweep layout4_s1/listener_corner   x16 e1 achieved SE 0.171 dB VOV_union 0.005 U 0 | SE dB per band 0.171 0.171 0.171 0.171 0.171 0.171 0.171 0.171 | VOV per band 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005
wsweep layout4_s1/listener_corner   x1  e0 total minus x16 total, dB per band -0.247 -0.247 -0.247 -0.247 -0.247 -0.247 -0.247 -0.247
wsweep layout4_s1/listener_corner   x1  e1 total minus x16 total, dB per band -0.499 -0.499 -0.499 -0.499 -0.499 -0.499 -0.499 -0.499
wsweep layout4_s1/listener_corner   x2  e0 total minus x16 total, dB per band +0.273 +0.273 +0.273 +0.273 +0.273 +0.273 +0.273 +0.273
wsweep layout4_s1/listener_corner   x2  e1 total minus x16 total, dB per band -0.109 -0.109 -0.109 -0.109 -0.109 -0.109 -0.109 -0.109
wsweep layout4_s1/listener_corner   x4  e0 total minus x16 total, dB per band +0.037 +0.037 +0.037 +0.037 +0.037 +0.037 +0.037 +0.037
wsweep layout4_s1/listener_corner   x4  e1 total minus x16 total, dB per band -0.095 -0.095 -0.095 -0.095 -0.095 -0.095 -0.095 -0.095
wsweep layout4_s1/listener_corner   x8  e0 total minus x16 total, dB per band +0.329 +0.329 +0.329 +0.329 +0.329 +0.329 +0.329 +0.329
wsweep layout4_s1/listener_corner   x8  e1 total minus x16 total, dB per band +0.293 +0.293 +0.293 +0.293 +0.293 +0.293 +0.293 +0.293
wsweep layout4_s1/listener_corner   x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/listener_corner   x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/emitter_wall      x1  W_max 3050000 W_scene 6100000 | pool(4) min 115.9 median 133.1 worst 139.8 ms (3 runs); single-thread 384.4 ms; ns/eval pool 21.64 single 62.52 | peak RSS delta 0.0 MB | n* 448 W_pilot 3485513 N_need 20471 N_cap 320 N 320 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2663422 realised/W_scene 1.0080
wsweep layout4_s1/emitter_wall      x1  e0 achieved SE 0.708 dB VOV_union 0.034 U 1 | SE dB per band 0.708 0.708 0.708 0.708 0.708 0.708 0.708 0.708 | VOV per band 0.086 0.086 0.086 0.086 0.086 0.086 0.086 0.086
wsweep layout4_s1/emitter_wall      x1  e1 achieved SE 0.476 dB VOV_union 0.019 U 1 | SE dB per band 0.476 0.476 0.476 0.476 0.476 0.476 0.476 0.476 | VOV per band 0.034 0.034 0.034 0.034 0.034 0.034 0.034 0.034
wsweep layout4_s1/emitter_wall      x2  W_max 6100000 W_scene 12200000 | pool(4) min 221.5 median 256.2 worst 271.6 ms (3 runs); single-thread 661.3 ms; ns/eval pool 20.81 single 53.72 | peak RSS delta 0.0 MB | n* 832 W_pilot 6518623 N_need 20130 N_cap 704 N 704 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5792267 realised/W_scene 1.0091
wsweep layout4_s1/emitter_wall      x2  e0 achieved SE 0.459 dB VOV_union 0.018 U 1 | SE dB per band 0.459 0.459 0.459 0.459 0.459 0.459 0.459 0.459 | VOV per band 0.041 0.041 0.041 0.041 0.041 0.041 0.041 0.041
wsweep layout4_s1/emitter_wall      x2  e1 achieved SE 0.324 dB VOV_union 0.009 U 0 | SE dB per band 0.324 0.324 0.324 0.324 0.324 0.324 0.324 0.324 | VOV per band 0.017 0.017 0.017 0.017 0.017 0.017 0.017 0.017
wsweep layout4_s1/emitter_wall      x4  W_max 12200000 W_scene 24400000 | pool(4) min 430.1 median 443.9 worst 468.2 ms (3 runs); single-thread 1522.5 ms; ns/eval pool 18.07 single 61.95 | peak RSS delta 0.0 MB | n* 1024 W_pilot 8017748 N_need 20833 N_cap 2048 N 2048 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 16556744 realised/W_scene 1.0072
wsweep layout4_s1/emitter_wall      x4  e0 achieved SE 0.276 dB VOV_union 0.010 U 0 | SE dB per band 0.276 0.276 0.276 0.276 0.276 0.276 0.276 0.276 | VOV per band 0.014 0.014 0.014 0.014 0.014 0.014 0.014 0.014
wsweep layout4_s1/emitter_wall      x4  e1 achieved SE 0.190 dB VOV_union 0.005 U 0 | SE dB per band 0.189 0.189 0.189 0.189 0.189 0.189 0.189 0.190 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout4_s1/emitter_wall      x8  W_max 24400000 W_scene 48800000 | pool(4) min 756.4 median 778.1 worst 837.9 ms (3 runs); single-thread 2762.8 ms; ns/eval pool 15.62 single 55.47 | peak RSS delta 0.0 MB | n* 1024 W_pilot 8017748 N_need 20833 N_cap 5184 N 5184 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 41793062 realised/W_scene 1.0207
wsweep layout4_s1/emitter_wall      x8  e0 achieved SE 0.176 dB VOV_union 0.005 U 0 | SE dB per band 0.176 0.176 0.176 0.176 0.176 0.176 0.176 0.176 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout4_s1/emitter_wall      x8  e1 achieved SE 0.118 dB VOV_union 0.002 U 0 | SE dB per band 0.118 0.118 0.118 0.118 0.118 0.118 0.118 0.118 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/emitter_wall      x16 W_max 48800000 W_scene 97600000 | pool(4) min 1408.9 median 1434.2 worst 1438.3 ms (3 runs); single-thread 5262.9 ms; ns/eval pool 14.40 single 52.85 | peak RSS delta 0.4 MB | n* 1024 W_pilot 8017748 N_need 20833 N_cap 11392 N 11392 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 91571471 realised/W_scene 1.0204
wsweep layout4_s1/emitter_wall      x16 e0 achieved SE 0.120 dB VOV_union 0.004 U 0 | SE dB per band 0.120 0.120 0.120 0.120 0.120 0.120 0.120 0.120 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/emitter_wall      x16 e1 achieved SE 0.081 dB VOV_union 0.002 U 0 | SE dB per band 0.081 0.081 0.081 0.081 0.081 0.081 0.081 0.081 | VOV per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001
wsweep layout4_s1/emitter_wall      x1  e0 total minus x16 total, dB per band +0.424 +0.424 +0.424 +0.424 +0.424 +0.424 +0.424 +0.424
wsweep layout4_s1/emitter_wall      x1  e1 total minus x16 total, dB per band +0.572 +0.572 +0.572 +0.572 +0.572 +0.572 +0.572 +0.572
wsweep layout4_s1/emitter_wall      x2  e0 total minus x16 total, dB per band -0.011 -0.011 -0.011 -0.011 -0.011 -0.011 -0.011 -0.011
wsweep layout4_s1/emitter_wall      x2  e1 total minus x16 total, dB per band +0.416 +0.416 +0.416 +0.416 +0.416 +0.416 +0.416 +0.416
wsweep layout4_s1/emitter_wall      x4  e0 total minus x16 total, dB per band +0.419 +0.419 +0.419 +0.419 +0.419 +0.419 +0.419 +0.419
wsweep layout4_s1/emitter_wall      x4  e1 total minus x16 total, dB per band +0.173 +0.173 +0.173 +0.173 +0.173 +0.173 +0.173 +0.173
wsweep layout4_s1/emitter_wall      x8  e0 total minus x16 total, dB per band +0.167 +0.167 +0.167 +0.167 +0.167 +0.167 +0.167 +0.167
wsweep layout4_s1/emitter_wall      x8  e1 total minus x16 total, dB per band +0.009 +0.009 +0.009 +0.009 +0.009 +0.009 +0.009 +0.009
wsweep layout4_s1/emitter_wall      x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/emitter_wall      x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/both_wall         x1  W_max 3050000 W_scene 6100000 | pool(4) min 84.9 median 85.5 worst 96.7 ms (3 runs); single-thread 276.3 ms; ns/eval pool 14.38 single 46.45 | peak RSS delta 0.0 MB | n* 640 W_pilot 3211330 N_need 22346 N_cap 512 N 512 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2735781 realised/W_scene 0.9749
wsweep layout4_s1/both_wall         x1  e0 achieved SE 0.842 dB VOV_union 0.476 U 1 | SE dB per band 0.842 0.842 0.842 0.842 0.842 0.842 0.842 0.842 | VOV per band 0.611 0.611 0.611 0.611 0.611 0.611 0.611 0.611
wsweep layout4_s1/both_wall         x1  e1 achieved SE 0.538 dB VOV_union 0.021 U 1 | SE dB per band 0.538 0.538 0.538 0.538 0.538 0.538 0.538 0.538 | VOV per band 0.047 0.047 0.047 0.047 0.047 0.047 0.047 0.047
wsweep layout4_s1/both_wall         x2  W_max 6100000 W_scene 12200000 | pool(4) min 160.3 median 168.8 worst 183.3 ms (3 runs); single-thread 692.3 ms; ns/eval pool 13.82 single 56.68 | peak RSS delta 0.0 MB | n* 1024 W_pilot 5152042 N_need 105005 N_cap 1344 N 1344 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 7061344 realised/W_scene 1.0011
wsweep layout4_s1/both_wall         x2  e0 achieved SE 0.572 dB VOV_union 0.314 U 1 | SE dB per band 0.572 0.572 0.572 0.572 0.572 0.572 0.572 0.572 | VOV per band 0.389 0.389 0.389 0.389 0.389 0.389 0.389 0.389
wsweep layout4_s1/both_wall         x2  e1 achieved SE 0.362 dB VOV_union 0.014 U 1 | SE dB per band 0.362 0.362 0.362 0.362 0.362 0.362 0.362 0.362 | VOV per band 0.028 0.028 0.028 0.028 0.028 0.028 0.028 0.028
wsweep layout4_s1/both_wall         x4  W_max 12200000 W_scene 24400000 | pool(4) min 328.2 median 331.2 worst 339.9 ms (3 runs); single-thread 1224.2 ms; ns/eval pool 13.30 single 49.16 | peak RSS delta 0.0 MB | n* 1024 W_pilot 5152042 N_need 105005 N_cap 3776 N 3776 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 19749962 realised/W_scene 1.0206
wsweep layout4_s1/both_wall         x4  e0 achieved SE 1.032 dB VOV_union 0.786 U 1 | SE dB per band 1.032 1.032 1.032 1.032 1.032 1.032 1.031 1.031 | VOV per band 0.829 0.829 0.829 0.829 0.829 0.829 0.829 0.829
wsweep layout4_s1/both_wall         x4  e1 achieved SE 0.201 dB VOV_union 0.006 U 0 | SE dB per band 0.201 0.201 0.201 0.201 0.201 0.201 0.201 0.201 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout4_s1/both_wall         x8  W_max 24400000 W_scene 48800000 | pool(4) min 665.1 median 718.0 worst 797.7 ms (3 runs); single-thread 2432.0 ms; ns/eval pool 14.28 single 48.36 | peak RSS delta 0.0 MB | n* 1024 W_pilot 5152042 N_need 105005 N_cap 8640 N 8640 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 45135067 realised/W_scene 1.0305
wsweep layout4_s1/both_wall         x8  e0 achieved SE 0.832 dB VOV_union 0.549 U 1 | SE dB per band 0.832 0.832 0.832 0.832 0.832 0.832 0.832 0.832 | VOV per band 0.528 0.528 0.528 0.528 0.528 0.528 0.528 0.528
wsweep layout4_s1/both_wall         x8  e1 achieved SE 0.133 dB VOV_union 0.003 U 0 | SE dB per band 0.133 0.133 0.133 0.133 0.133 0.133 0.133 0.133 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout4_s1/both_wall         x16 W_max 48800000 W_scene 97600000 | pool(4) min 1311.7 median 1360.6 worst 1380.6 ms (3 runs); single-thread 5026.2 ms; ns/eval pool 13.52 single 49.95 | peak RSS delta 1.4 MB | n* 1024 W_pilot 5152042 N_need 105005 N_cap 18368 N 18368 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 95470465 realised/W_scene 1.0310
wsweep layout4_s1/both_wall         x16 e0 achieved SE 0.496 dB VOV_union 0.549 U 1 | SE dB per band 0.496 0.496 0.496 0.496 0.496 0.496 0.496 0.496 | VOV per band 0.260 0.260 0.260 0.260 0.260 0.260 0.260 0.260
wsweep layout4_s1/both_wall         x16 e1 achieved SE 0.092 dB VOV_union 0.003 U 0 | SE dB per band 0.092 0.092 0.092 0.092 0.092 0.092 0.092 0.092 | VOV per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001
wsweep layout4_s1/both_wall         x1  e0 total minus x16 total, dB per band -0.855 -0.855 -0.855 -0.855 -0.855 -0.855 -0.855 -0.854
wsweep layout4_s1/both_wall         x1  e1 total minus x16 total, dB per band +0.284 +0.284 +0.284 +0.284 +0.284 +0.284 +0.284 +0.284
wsweep layout4_s1/both_wall         x2  e0 total minus x16 total, dB per band -1.129 -1.129 -1.129 -1.129 -1.129 -1.129 -1.129 -1.129
wsweep layout4_s1/both_wall         x2  e1 total minus x16 total, dB per band -0.133 -0.133 -0.133 -0.133 -0.133 -0.133 -0.133 -0.133
wsweep layout4_s1/both_wall         x4  e0 total minus x16 total, dB per band -0.134 -0.134 -0.134 -0.134 -0.134 -0.134 -0.134 -0.134
wsweep layout4_s1/both_wall         x4  e1 total minus x16 total, dB per band +0.048 +0.048 +0.048 +0.048 +0.048 +0.048 +0.048 +0.048
wsweep layout4_s1/both_wall         x8  e0 total minus x16 total, dB per band +0.165 +0.165 +0.165 +0.165 +0.165 +0.165 +0.165 +0.165
wsweep layout4_s1/both_wall         x8  e1 total minus x16 total, dB per band -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003 -0.003
wsweep layout4_s1/both_wall         x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/both_wall         x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/both_corner       x1  W_max 3050000 W_scene 6100000 | pool(4) min 88.6 median 102.1 worst 108.5 ms (3 runs); single-thread 243.2 ms; ns/eval pool 18.23 single 43.43 | peak RSS delta 0.0 MB | n* 256 W_pilot 3751605 N_need 112522 N_cap 128 N 128 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 1847989 realised/W_scene 0.9180
wsweep layout4_s1/both_corner       x1  e0 achieved SE 1.283 dB VOV_union 0.798 U 1 | SE dB per band 1.283 1.283 1.283 1.283 1.283 1.283 1.283 1.283 | VOV per band 0.267 0.267 0.267 0.267 0.267 0.267 0.267 0.267
wsweep layout4_s1/both_corner       x1  e1 achieved SE 1.239 dB VOV_union 0.056 U 1 | SE dB per band 1.239 1.239 1.239 1.239 1.239 1.239 1.239 1.239 | VOV per band 0.124 0.124 0.124 0.124 0.124 0.124 0.124 0.124
wsweep layout4_s1/both_corner       x2  W_max 6100000 W_scene 12200000 | pool(4) min 200.9 median 208.0 worst 224.6 ms (3 runs); single-thread 488.6 ms; ns/eval pool 18.22 single 42.80 | peak RSS delta 0.0 MB | n* 448 W_pilot 6618293 N_need 93881 N_cap 320 N 320 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 4798058 realised/W_scene 0.9358
wsweep layout4_s1/both_corner       x2  e0 achieved SE 0.797 dB VOV_union 0.643 U 1 | SE dB per band 0.797 0.797 0.797 0.797 0.797 0.797 0.797 0.797 | VOV per band 0.249 0.249 0.249 0.249 0.249 0.249 0.249 0.249
wsweep layout4_s1/both_corner       x2  e1 achieved SE 0.938 dB VOV_union 0.044 U 1 | SE dB per band 0.938 0.938 0.938 0.938 0.938 0.938 0.938 0.938 | VOV per band 0.151 0.151 0.151 0.151 0.151 0.151 0.151 0.151
wsweep layout4_s1/both_corner       x4  W_max 12200000 W_scene 24400000 | pool(4) min 315.8 median 329.8 worst 343.0 ms (3 runs); single-thread 1047.7 ms; ns/eval pool 13.77 single 43.74 | peak RSS delta 0.0 MB | n* 832 W_pilot 12536018 N_need 552623 N_cap 768 N 768 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 11416976 realised/W_scene 0.9817
wsweep layout4_s1/both_corner       x4  e0 achieved SE 0.443 dB VOV_union 0.914 U 1 | SE dB per band 0.443 0.443 0.443 0.443 0.443 0.443 0.443 0.443 | VOV per band 0.071 0.071 0.071 0.071 0.071 0.071 0.071 0.071
wsweep layout4_s1/both_corner       x4  e1 achieved SE 0.609 dB VOV_union 0.023 U 1 | SE dB per band 0.609 0.609 0.609 0.609 0.609 0.609 0.609 0.609 | VOV per band 0.077 0.077 0.077 0.077 0.077 0.077 0.077 0.077
wsweep layout4_s1/both_corner       x8  W_max 24400000 W_scene 48800000 | pool(4) min 607.5 median 664.5 worst 733.2 ms (3 runs); single-thread 2060.4 ms; ns/eval pool 13.87 single 42.99 | peak RSS delta 0.0 MB | n* 1024 W_pilot 15446007 N_need 570970 N_cap 2176 N 2176 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 32478899 realised/W_scene 0.9821
wsweep layout4_s1/both_corner       x8  e0 achieved SE 0.605 dB VOV_union 0.645 U 1 | SE dB per band 0.605 0.605 0.605 0.605 0.605 0.605 0.605 0.605 | VOV per band 0.193 0.193 0.193 0.193 0.193 0.193 0.193 0.193
wsweep layout4_s1/both_corner       x8  e1 achieved SE 0.324 dB VOV_union 0.011 U 0 | SE dB per band 0.324 0.324 0.324 0.324 0.324 0.324 0.324 0.324 | VOV per band 0.019 0.019 0.019 0.019 0.019 0.019 0.019 0.019
wsweep layout4_s1/both_corner       x16 W_max 48800000 W_scene 97600000 | pool(4) min 1156.7 median 1158.9 worst 1196.9 ms (3 runs); single-thread 4227.8 ms; ns/eval pool 11.99 single 43.75 | peak RSS delta 0.0 MB | n* 1024 W_pilot 15446007 N_need 570970 N_cap 5440 N 5440 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 81198381 realised/W_scene 0.9902
wsweep layout4_s1/both_corner       x16 e0 achieved SE 1.225 dB VOV_union 0.443 U 1 | SE dB per band 1.225 1.225 1.225 1.225 1.225 1.225 1.225 1.225 | VOV per band 0.526 0.526 0.526 0.526 0.526 0.526 0.526 0.526
wsweep layout4_s1/both_corner       x16 e1 achieved SE 0.198 dB VOV_union 0.005 U 0 | SE dB per band 0.198 0.198 0.198 0.198 0.198 0.198 0.198 0.198 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout4_s1/both_corner       x1  e0 total minus x16 total, dB per band -3.720 -3.720 -3.720 -3.720 -3.720 -3.720 -3.720 -3.720
wsweep layout4_s1/both_corner       x1  e1 total minus x16 total, dB per band -0.190 -0.190 -0.190 -0.190 -0.190 -0.190 -0.190 -0.190
wsweep layout4_s1/both_corner       x2  e0 total minus x16 total, dB per band -3.150 -3.150 -3.150 -3.150 -3.150 -3.150 -3.150 -3.150
wsweep layout4_s1/both_corner       x2  e1 total minus x16 total, dB per band -0.288 -0.288 -0.288 -0.288 -0.288 -0.288 -0.288 -0.288
wsweep layout4_s1/both_corner       x4  e0 total minus x16 total, dB per band -2.812 -2.812 -2.812 -2.812 -2.812 -2.812 -2.812 -2.812
wsweep layout4_s1/both_corner       x4  e1 total minus x16 total, dB per band -1.104 -1.104 -1.104 -1.104 -1.104 -1.104 -1.104 -1.104
wsweep layout4_s1/both_corner       x8  e0 total minus x16 total, dB per band -1.461 -1.461 -1.461 -1.461 -1.461 -1.461 -1.461 -1.461
wsweep layout4_s1/both_corner       x8  e1 total minus x16 total, dB per band -0.422 -0.422 -0.422 -0.422 -0.422 -0.422 -0.422 -0.422
wsweep layout4_s1/both_corner       x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout4_s1/both_corner       x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/default           x1  W_max 3050000 W_scene 6100000 | pool(4) min 172.2 median 183.7 worst 190.4 ms (3 runs); single-thread 317.7 ms; ns/eval pool 31.25 single 54.04 | peak RSS delta 0.0 MB | n* 320 W_pilot 3726315 N_need 6042 N_cap 192 N 192 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2153382 realised/W_scene 0.9639
wsweep layout5_s1/default           x1  e0 achieved SE 0.484 dB VOV_union 0.048 U 1 | SE dB per band 0.484 0.484 0.484 0.484 0.484 0.484 0.484 0.484 | VOV per band 0.136 0.136 0.136 0.136 0.136 0.136 0.136 0.136
wsweep layout5_s1/default           x1  e1 achieved SE 0.441 dB VOV_union 0.033 U 1 | SE dB per band 0.440 0.440 0.440 0.440 0.440 0.441 0.441 0.441 | VOV per band 0.129 0.129 0.129 0.129 0.129 0.129 0.129 0.129
wsweep layout5_s1/default           x2  W_max 6100000 W_scene 12200000 | pool(4) min 221.5 median 276.0 worst 303.1 ms (3 runs); single-thread 630.6 ms; ns/eval pool 23.48 single 53.65 | peak RSS delta 0.0 MB | n* 576 W_pilot 6610361 N_need 5610 N_cap 448 N 448 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5143655 realised/W_scene 0.9634
wsweep layout5_s1/default           x2  e0 achieved SE 0.294 dB VOV_union 0.024 U 0 | SE dB per band 0.294 0.294 0.294 0.294 0.294 0.294 0.294 0.294 | VOV per band 0.062 0.062 0.062 0.062 0.062 0.062 0.062 0.062
wsweep layout5_s1/default           x2  e1 achieved SE 0.266 dB VOV_union 0.017 U 0 | SE dB per band 0.266 0.266 0.266 0.266 0.266 0.266 0.266 0.266 | VOV per band 0.035 0.035 0.035 0.035 0.035 0.035 0.035 0.035
wsweep layout5_s1/default           x4  W_max 12200000 W_scene 24400000 | pool(4) min 444.6 median 455.1 worst 491.0 ms (3 runs); single-thread 1426.4 ms; ns/eval pool 18.64 single 58.42 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11772695 N_need 5350 N_cap 1088 N 1088 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 12645700 realised/W_scene 1.0008
wsweep layout5_s1/default           x4  e0 achieved SE 0.173 dB VOV_union 0.010 U 0 | SE dB per band 0.173 0.173 0.173 0.173 0.173 0.173 0.173 0.173 | VOV per band 0.021 0.021 0.021 0.021 0.021 0.021 0.021 0.021
wsweep layout5_s1/default           x4  e1 achieved SE 0.174 dB VOV_union 0.008 U 0 | SE dB per band 0.174 0.174 0.174 0.174 0.174 0.174 0.174 0.174 | VOV per band 0.015 0.015 0.015 0.015 0.015 0.015 0.015 0.015
wsweep layout5_s1/default           x8  W_max 24400000 W_scene 48800000 | pool(4) min 787.1 median 790.4 worst 847.5 ms (3 runs); single-thread 2775.1 ms; ns/eval pool 16.09 single 56.49 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11772695 N_need 5350 N_cap 3200 N 3200 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 37353157 realised/W_scene 1.0067
wsweep layout5_s1/default           x8  e0 achieved SE 0.103 dB VOV_union 0.006 U 0 | SE dB per band 0.103 0.103 0.103 0.103 0.103 0.103 0.103 0.103 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout5_s1/default           x8  e1 achieved SE 0.102 dB VOV_union 0.004 U 0 | SE dB per band 0.102 0.102 0.102 0.102 0.102 0.102 0.102 0.102 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout5_s1/default           x16 W_max 48800000 W_scene 97600000 | pool(4) min 1098.9 median 1134.2 worst 1258.7 ms (3 runs); single-thread 4328.2 ms; ns/eval pool 15.21 single 58.05 | peak RSS delta 0.0 MB | n* 1024 W_pilot 11772695 N_need 5350 N_cap 7424 N 5376 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 62786824 realised/W_scene 0.7639
wsweep layout5_s1/default           x16 e0 achieved SE 0.081 dB VOV_union 0.004 U 0 | SE dB per band 0.081 0.081 0.081 0.081 0.081 0.081 0.081 0.081 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/default           x16 e1 achieved SE 0.081 dB VOV_union 0.003 U 0 | SE dB per band 0.081 0.081 0.081 0.081 0.081 0.081 0.081 0.081 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/default           x1  e0 total minus x16 total, dB per band -0.080 -0.080 -0.080 -0.080 -0.080 -0.080 -0.080 -0.080
wsweep layout5_s1/default           x1  e1 total minus x16 total, dB per band -0.685 -0.685 -0.685 -0.685 -0.685 -0.685 -0.685 -0.685
wsweep layout5_s1/default           x2  e0 total minus x16 total, dB per band -0.336 -0.336 -0.336 -0.336 -0.336 -0.336 -0.336 -0.336
wsweep layout5_s1/default           x2  e1 total minus x16 total, dB per band -0.409 -0.409 -0.409 -0.409 -0.409 -0.409 -0.409 -0.409
wsweep layout5_s1/default           x4  e0 total minus x16 total, dB per band -0.363 -0.363 -0.363 -0.363 -0.363 -0.363 -0.363 -0.363
wsweep layout5_s1/default           x4  e1 total minus x16 total, dB per band -0.157 -0.157 -0.157 -0.157 -0.157 -0.157 -0.157 -0.157
wsweep layout5_s1/default           x8  e0 total minus x16 total, dB per band +0.001 +0.001 +0.001 +0.001 +0.001 +0.001 +0.001 +0.001
wsweep layout5_s1/default           x8  e1 total minus x16 total, dB per band +0.013 +0.013 +0.013 +0.013 +0.013 +0.013 +0.013 +0.013
wsweep layout5_s1/default           x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/default           x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_wall     x1  W_max 3050000 W_scene 6100000 | pool(4) min 43.8 median 44.3 worst 45.5 ms (3 runs); single-thread 157.1 ms; ns/eval pool 7.34 single 26.03 | peak RSS delta 0.0 MB | n* 1024 W_pilot 776372 N_need 31855 N_cap 6976 N 6976 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 5258387 realised/W_scene 0.9893
wsweep layout5_s1/listener_wall     x1  e0 achieved SE 0.141 dB VOV_union 0.023 U 0 | SE dB per band 0.141 0.141 0.141 0.141 0.141 0.141 0.141 0.141 | VOV per band 0.027 0.027 0.027 0.027 0.027 0.027 0.027 0.027
wsweep layout5_s1/listener_wall     x1  e1 achieved SE 0.142 dB VOV_union 0.015 U 0 | SE dB per band 0.142 0.142 0.142 0.142 0.142 0.142 0.142 0.142 | VOV per band 0.019 0.019 0.019 0.019 0.019 0.019 0.019 0.019
wsweep layout5_s1/listener_wall     x2  W_max 6100000 W_scene 12200000 | pool(4) min 91.5 median 96.8 worst 99.6 ms (3 runs); single-thread 269.4 ms; ns/eval pool 8.03 single 22.36 | peak RSS delta 0.0 MB | n* 1024 W_pilot 776372 N_need 31855 N_cap 15040 N 15040 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 11276006 realised/W_scene 0.9879
wsweep layout5_s1/listener_wall     x2  e0 achieved SE 0.099 dB VOV_union 0.023 U 0 | SE dB per band 0.099 0.099 0.099 0.099 0.099 0.099 0.099 0.099 | VOV per band 0.012 0.012 0.012 0.012 0.012 0.012 0.012 0.012
wsweep layout5_s1/listener_wall     x2  e1 achieved SE 0.094 dB VOV_union 0.015 U 0 | SE dB per band 0.094 0.094 0.094 0.094 0.094 0.094 0.094 0.094 | VOV per band 0.009 0.009 0.009 0.009 0.009 0.009 0.009 0.009
wsweep layout5_s1/listener_wall     x4  W_max 12200000 W_scene 24400000 | pool(4) min 162.7 median 166.4 worst 191.7 ms (3 runs); single-thread 623.0 ms; ns/eval pool 6.89 single 25.79 | peak RSS delta 2.9 MB | n* 1024 W_pilot 776372 N_need 31855 N_cap 31104 N 31104 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 23373802 realised/W_scene 0.9898
wsweep layout5_s1/listener_wall     x4  e0 achieved SE 0.070 dB VOV_union 0.023 U 0 | SE dB per band 0.070 0.070 0.070 0.070 0.070 0.070 0.070 0.070 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout5_s1/listener_wall     x4  e1 achieved SE 0.066 dB VOV_union 0.015 U 0 | SE dB per band 0.066 0.066 0.066 0.066 0.066 0.066 0.066 0.066 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/listener_wall     x8  W_max 24400000 W_scene 48800000 | pool(4) min 163.3 median 167.3 worst 167.5 ms (3 runs); single-thread 624.4 ms; ns/eval pool 6.76 single 25.24 | peak RSS delta 0.3 MB | n* 1024 W_pilot 776372 N_need 31855 N_cap 63296 N 31872 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 23963165 realised/W_scene 0.5070
wsweep layout5_s1/listener_wall     x8  e0 achieved SE 0.070 dB VOV_union 0.023 U 0 | SE dB per band 0.070 0.070 0.070 0.070 0.070 0.070 0.070 0.070 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout5_s1/listener_wall     x8  e1 achieved SE 0.066 dB VOV_union 0.015 U 0 | SE dB per band 0.066 0.066 0.066 0.066 0.066 0.066 0.066 0.066 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/listener_wall     x16 W_max 48800000 W_scene 97600000 | pool(4) min 158.8 median 177.4 worst 188.9 ms (3 runs); single-thread 620.0 ms; ns/eval pool 7.17 single 25.06 | peak RSS delta 0.0 MB | n* 1024 W_pilot 776372 N_need 31855 N_cap 127680 N 31872 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 23963165 realised/W_scene 0.2535
wsweep layout5_s1/listener_wall     x16 e0 achieved SE 0.070 dB VOV_union 0.023 U 0 | SE dB per band 0.070 0.070 0.070 0.070 0.070 0.070 0.070 0.070 | VOV per band 0.006 0.006 0.006 0.006 0.006 0.006 0.006 0.006
wsweep layout5_s1/listener_wall     x16 e1 achieved SE 0.066 dB VOV_union 0.015 U 0 | SE dB per band 0.066 0.066 0.066 0.066 0.066 0.066 0.066 0.066 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/listener_wall     x1  e0 total minus x16 total, dB per band -0.140 -0.140 -0.140 -0.140 -0.140 -0.140 -0.140 -0.140
wsweep layout5_s1/listener_wall     x1  e1 total minus x16 total, dB per band +0.029 +0.029 +0.029 +0.029 +0.029 +0.029 +0.029 +0.029
wsweep layout5_s1/listener_wall     x2  e0 total minus x16 total, dB per band -0.093 -0.093 -0.093 -0.093 -0.093 -0.093 -0.093 -0.093
wsweep layout5_s1/listener_wall     x2  e1 total minus x16 total, dB per band -0.056 -0.056 -0.056 -0.056 -0.056 -0.056 -0.056 -0.056
wsweep layout5_s1/listener_wall     x4  e0 total minus x16 total, dB per band -0.025 -0.025 -0.025 -0.025 -0.025 -0.025 -0.025 -0.025
wsweep layout5_s1/listener_wall     x4  e1 total minus x16 total, dB per band -0.007 -0.007 -0.007 -0.007 -0.007 -0.007 -0.007 -0.007
wsweep layout5_s1/listener_wall     x8  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_wall     x8  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_wall     x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_wall     x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_edge     x1  W_max 3050000 W_scene 6100000 | pool(4) min 48.4 median 51.7 worst 52.1 ms (3 runs); single-thread 155.5 ms; ns/eval pool 8.57 single 25.80 | peak RSS delta 0.0 MB | n* 1024 W_pilot 890484 N_need 49891 N_cap 5952 N 5952 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 5138366 realised/W_scene 0.9883
wsweep layout5_s1/listener_edge     x1  e0 achieved SE 0.248 dB VOV_union 0.043 U 0 | SE dB per band 0.248 0.248 0.248 0.248 0.248 0.248 0.248 0.248 | VOV per band 0.050 0.050 0.050 0.050 0.050 0.050 0.050 0.050
wsweep layout5_s1/listener_edge     x1  e1 achieved SE 0.215 dB VOV_union 0.040 U 0 | SE dB per band 0.215 0.215 0.215 0.215 0.215 0.215 0.215 0.215 | VOV per band 0.048 0.048 0.048 0.048 0.048 0.048 0.048 0.048
wsweep layout5_s1/listener_edge     x2  W_max 6100000 W_scene 12200000 | pool(4) min 101.7 median 105.4 worst 122.6 ms (3 runs); single-thread 350.8 ms; ns/eval pool 8.72 single 29.01 | peak RSS delta 0.0 MB | n* 1024 W_pilot 890484 N_need 49891 N_cap 12992 N 12992 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 11204108 realised/W_scene 0.9914
wsweep layout5_s1/listener_edge     x2  e0 achieved SE 0.168 dB VOV_union 0.043 U 0 | SE dB per band 0.168 0.168 0.168 0.168 0.168 0.168 0.168 0.168 | VOV per band 0.032 0.032 0.032 0.032 0.032 0.032 0.032 0.032
wsweep layout5_s1/listener_edge     x2  e1 achieved SE 0.145 dB VOV_union 0.035 U 0 | SE dB per band 0.145 0.145 0.145 0.145 0.145 0.145 0.145 0.145 | VOV per band 0.017 0.017 0.017 0.017 0.017 0.017 0.017 0.017
wsweep layout5_s1/listener_edge     x4  W_max 12200000 W_scene 24400000 | pool(4) min 173.3 median 174.5 worst 188.6 ms (3 runs); single-thread 678.6 ms; ns/eval pool 7.22 single 28.07 | peak RSS delta 0.0 MB | n* 1024 W_pilot 890484 N_need 49891 N_cap 27008 N 27008 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 23282073 realised/W_scene 0.9907
wsweep layout5_s1/listener_edge     x4  e0 achieved SE 0.120 dB VOV_union 0.043 U 0 | SE dB per band 0.120 0.120 0.120 0.120 0.120 0.120 0.120 0.120 | VOV per band 0.015 0.015 0.015 0.015 0.015 0.015 0.015 0.015
wsweep layout5_s1/listener_edge     x4  e1 achieved SE 0.105 dB VOV_union 0.035 U 0 | SE dB per band 0.105 0.105 0.105 0.105 0.105 0.105 0.105 0.105 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout5_s1/listener_edge     x8  W_max 24400000 W_scene 48800000 | pool(4) min 377.4 median 387.9 worst 395.5 ms (3 runs); single-thread 1198.7 ms; ns/eval pool 8.83 single 27.28 | peak RSS delta 6.3 MB | n* 1024 W_pilot 890484 N_need 49891 N_cap 55040 N 49920 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 43047878 realised/W_scene 0.9004
wsweep layout5_s1/listener_edge     x8  e0 achieved SE 0.090 dB VOV_union 0.043 U 0 | SE dB per band 0.090 0.090 0.090 0.090 0.090 0.090 0.090 0.090 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout5_s1/listener_edge     x8  e1 achieved SE 0.081 dB VOV_union 0.035 U 0 | SE dB per band 0.081 0.081 0.081 0.081 0.081 0.081 0.081 0.081 | VOV per band 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005
wsweep layout5_s1/listener_edge     x16 W_max 48800000 W_scene 97600000 | pool(4) min 314.8 median 334.5 worst 368.8 ms (3 runs); single-thread 1074.0 ms; ns/eval pool 7.61 single 24.44 | peak RSS delta 17.9 MB | n* 1024 W_pilot 890484 N_need 49891 N_cap 111168 N 49920 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 43047878 realised/W_scene 0.4502
wsweep layout5_s1/listener_edge     x16 e0 achieved SE 0.090 dB VOV_union 0.043 U 0 | SE dB per band 0.090 0.090 0.090 0.090 0.090 0.090 0.090 0.090 | VOV per band 0.008 0.008 0.008 0.008 0.008 0.008 0.008 0.008
wsweep layout5_s1/listener_edge     x16 e1 achieved SE 0.081 dB VOV_union 0.035 U 0 | SE dB per band 0.081 0.081 0.081 0.081 0.081 0.081 0.081 0.081 | VOV per band 0.005 0.005 0.005 0.005 0.005 0.005 0.005 0.005
wsweep layout5_s1/listener_edge     x1  e0 total minus x16 total, dB per band +0.184 +0.184 +0.184 +0.184 +0.184 +0.184 +0.184 +0.184
wsweep layout5_s1/listener_edge     x1  e1 total minus x16 total, dB per band +0.017 +0.017 +0.017 +0.017 +0.017 +0.017 +0.017 +0.017
wsweep layout5_s1/listener_edge     x2  e0 total minus x16 total, dB per band -0.116 -0.116 -0.116 -0.116 -0.116 -0.116 -0.116 -0.116
wsweep layout5_s1/listener_edge     x2  e1 total minus x16 total, dB per band -0.036 -0.036 -0.036 -0.036 -0.036 -0.036 -0.036 -0.036
wsweep layout5_s1/listener_edge     x4  e0 total minus x16 total, dB per band +0.026 +0.026 +0.026 +0.026 +0.026 +0.026 +0.026 +0.026
wsweep layout5_s1/listener_edge     x4  e1 total minus x16 total, dB per band +0.127 +0.127 +0.127 +0.127 +0.127 +0.127 +0.127 +0.127
wsweep layout5_s1/listener_edge     x8  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_edge     x8  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_edge     x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_edge     x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_corner   x1  W_max 3050000 W_scene 6100000 | pool(4) min 46.9 median 49.0 worst 49.8 ms (3 runs); single-thread 139.3 ms; ns/eval pool 8.11 single 23.05 | peak RSS delta 0.0 MB | n* 1024 W_pilot 1098099 N_need 30642 N_cap 4608 N 4608 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 4942204 realised/W_scene 0.9902
wsweep layout5_s1/listener_corner   x1  e0 achieved SE 0.225 dB VOV_union 0.060 U 0 | SE dB per band 0.225 0.225 0.225 0.225 0.225 0.225 0.225 0.225 | VOV per band 0.074 0.074 0.074 0.074 0.074 0.074 0.074 0.074
wsweep layout5_s1/listener_corner   x1  e1 achieved SE 0.200 dB VOV_union 0.022 U 0 | SE dB per band 0.200 0.200 0.200 0.200 0.200 0.200 0.200 0.200 | VOV per band 0.026 0.026 0.026 0.026 0.026 0.026 0.026 0.026
wsweep layout5_s1/listener_corner   x2  W_max 6100000 W_scene 12200000 | pool(4) min 82.8 median 83.7 worst 85.3 ms (3 runs); single-thread 369.5 ms; ns/eval pool 6.88 single 30.38 | peak RSS delta 2.6 MB | n* 1024 W_pilot 1098099 N_need 30642 N_cap 10304 N 10304 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 11064667 realised/W_scene 0.9969
wsweep layout5_s1/listener_corner   x2  e0 achieved SE 0.153 dB VOV_union 0.041 U 0 | SE dB per band 0.153 0.153 0.153 0.153 0.153 0.153 0.153 0.153 | VOV per band 0.039 0.039 0.039 0.039 0.039 0.039 0.039 0.039
wsweep layout5_s1/listener_corner   x2  e1 achieved SE 0.147 dB VOV_union 0.026 U 0 | SE dB per band 0.147 0.147 0.147 0.147 0.147 0.147 0.147 0.147 | VOV per band 0.021 0.021 0.021 0.021 0.021 0.021 0.021 0.021
wsweep layout5_s1/listener_corner   x4  W_max 12200000 W_scene 24400000 | pool(4) min 190.8 median 191.4 worst 201.1 ms (3 runs); single-thread 562.9 ms; ns/eval pool 7.85 single 23.08 | peak RSS delta 4.2 MB | n* 1024 W_pilot 1098099 N_need 30642 N_cap 21696 N 21696 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 23294298 realised/W_scene 0.9997
wsweep layout5_s1/listener_corner   x4  e0 achieved SE 0.109 dB VOV_union 0.041 U 0 | SE dB per band 0.109 0.109 0.109 0.109 0.109 0.109 0.109 0.109 | VOV per band 0.021 0.021 0.021 0.021 0.021 0.021 0.021 0.021
wsweep layout5_s1/listener_corner   x4  e1 achieved SE 0.113 dB VOV_union 0.026 U 0 | SE dB per band 0.113 0.113 0.113 0.113 0.113 0.113 0.113 0.113 | VOV per band 0.017 0.017 0.017 0.017 0.017 0.017 0.017 0.017
wsweep layout5_s1/listener_corner   x8  W_max 24400000 W_scene 48800000 | pool(4) min 232.5 median 245.4 worst 273.1 ms (3 runs); single-thread 899.9 ms; ns/eval pool 7.22 single 26.46 | peak RSS delta 3.3 MB | n* 1024 W_pilot 1098099 N_need 30642 N_cap 44480 N 30656 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 32908360 realised/W_scene 0.6969
wsweep layout5_s1/listener_corner   x8  e0 achieved SE 0.090 dB VOV_union 0.041 U 0 | SE dB per band 0.090 0.090 0.090 0.090 0.090 0.090 0.090 0.090 | VOV per band 0.014 0.014 0.014 0.014 0.014 0.014 0.014 0.014
wsweep layout5_s1/listener_corner   x8  e1 achieved SE 0.095 dB VOV_union 0.026 U 0 | SE dB per band 0.095 0.095 0.095 0.095 0.095 0.095 0.095 0.095 | VOV per band 0.013 0.013 0.013 0.013 0.013 0.013 0.013 0.013
wsweep layout5_s1/listener_corner   x16 W_max 48800000 W_scene 97600000 | pool(4) min 215.5 median 229.0 worst 268.0 ms (3 runs); single-thread 755.0 ms; ns/eval pool 6.74 single 22.20 | peak RSS delta 0.0 MB | n* 1024 W_pilot 1098099 N_need 30642 N_cap 89984 N 30656 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 32908360 realised/W_scene 0.3484
wsweep layout5_s1/listener_corner   x16 e0 achieved SE 0.090 dB VOV_union 0.041 U 0 | SE dB per band 0.090 0.090 0.090 0.090 0.090 0.090 0.090 0.090 | VOV per band 0.014 0.014 0.014 0.014 0.014 0.014 0.014 0.014
wsweep layout5_s1/listener_corner   x16 e1 achieved SE 0.095 dB VOV_union 0.026 U 0 | SE dB per band 0.095 0.095 0.095 0.095 0.095 0.095 0.095 0.095 | VOV per band 0.013 0.013 0.013 0.013 0.013 0.013 0.013 0.013
wsweep layout5_s1/listener_corner   x1  e0 total minus x16 total, dB per band +0.283 +0.283 +0.283 +0.283 +0.283 +0.283 +0.283 +0.283
wsweep layout5_s1/listener_corner   x1  e1 total minus x16 total, dB per band +0.227 +0.227 +0.227 +0.227 +0.227 +0.227 +0.227 +0.227
wsweep layout5_s1/listener_corner   x2  e0 total minus x16 total, dB per band +0.046 +0.046 +0.046 +0.046 +0.046 +0.046 +0.046 +0.046
wsweep layout5_s1/listener_corner   x2  e1 total minus x16 total, dB per band +0.076 +0.076 +0.076 +0.076 +0.076 +0.076 +0.076 +0.076
wsweep layout5_s1/listener_corner   x4  e0 total minus x16 total, dB per band -0.038 -0.038 -0.038 -0.038 -0.038 -0.038 -0.038 -0.038
wsweep layout5_s1/listener_corner   x4  e1 total minus x16 total, dB per band +0.030 +0.030 +0.030 +0.030 +0.030 +0.030 +0.030 +0.030
wsweep layout5_s1/listener_corner   x8  e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_corner   x8  e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_corner   x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/listener_corner   x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/emitter_wall      x1  W_max 3050000 W_scene 6100000 | pool(4) min 120.6 median 121.1 worst 124.2 ms (3 runs); single-thread 324.8 ms; ns/eval pool 19.89 single 53.35 | peak RSS delta 0.0 MB | n* 512 W_pilot 3245332 N_need 47657 N_cap 448 N 448 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 2842859 realised/W_scene 0.9981
wsweep layout5_s1/emitter_wall      x1  e0 achieved SE 0.438 dB VOV_union 0.268 U 1 | SE dB per band 0.438 0.438 0.438 0.438 0.438 0.438 0.438 0.438 | VOV per band 0.269 0.269 0.269 0.269 0.269 0.269 0.269 0.269
wsweep layout5_s1/emitter_wall      x1  e1 achieved SE 0.266 dB VOV_union 0.016 U 0 | SE dB per band 0.266 0.266 0.266 0.266 0.266 0.266 0.266 0.266 | VOV per band 0.035 0.035 0.035 0.035 0.035 0.035 0.035 0.035
wsweep layout5_s1/emitter_wall      x2  W_max 6100000 W_scene 12200000 | pool(4) min 237.2 median 243.8 worst 248.2 ms (3 runs); single-thread 676.0 ms; ns/eval pool 20.46 single 56.71 | peak RSS delta 0.0 MB | n* 960 W_pilot 6102423 N_need 50813 N_cap 896 N 896 cap hit 1 floor truncated 1 pilot shipped 0 | W_final 5816446 realised/W_scene 0.9770
wsweep layout5_s1/emitter_wall      x2  e0 achieved SE 0.485 dB VOV_union 0.119 U 1 | SE dB per band 0.485 0.485 0.485 0.485 0.485 0.485 0.485 0.485 | VOV per band 0.194 0.194 0.194 0.194 0.194 0.194 0.194 0.194
wsweep layout5_s1/emitter_wall      x2  e1 achieved SE 0.186 dB VOV_union 0.009 U 0 | SE dB per band 0.186 0.186 0.186 0.186 0.186 0.186 0.186 0.186 | VOV per band 0.016 0.016 0.016 0.016 0.016 0.016 0.016 0.016
wsweep layout5_s1/emitter_wall      x4  W_max 12200000 W_scene 24400000 | pool(4) min 383.8 median 384.6 worst 545.6 ms (3 runs); single-thread 1306.1 ms; ns/eval pool 15.74 single 53.46 | peak RSS delta 0.0 MB | n* 1024 W_pilot 6508198 N_need 48525 N_cap 2752 N 2752 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 17922761 realised/W_scene 1.0013
wsweep layout5_s1/emitter_wall      x4  e0 achieved SE 0.329 dB VOV_union 0.059 U 0 | SE dB per band 0.329 0.329 0.329 0.329 0.329 0.329 0.329 0.329 | VOV per band 0.085 0.085 0.085 0.085 0.085 0.085 0.085 0.085
wsweep layout5_s1/emitter_wall      x4  e1 achieved SE 0.109 dB VOV_union 0.005 U 0 | SE dB per band 0.109 0.109 0.109 0.109 0.109 0.109 0.109 0.109 | VOV per band 0.007 0.007 0.007 0.007 0.007 0.007 0.007 0.007
wsweep layout5_s1/emitter_wall      x8  W_max 24400000 W_scene 48800000 | pool(4) min 757.8 median 808.5 worst 888.1 ms (3 runs); single-thread 2661.4 ms; ns/eval pool 16.40 single 53.99 | peak RSS delta 0.0 MB | n* 1024 W_pilot 6508198 N_need 48525 N_cap 6592 N 6592 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 42789539 realised/W_scene 1.0102
wsweep layout5_s1/emitter_wall      x8  e0 achieved SE 0.193 dB VOV_union 0.034 U 0 | SE dB per band 0.193 0.193 0.193 0.193 0.193 0.193 0.193 0.193 | VOV per band 0.042 0.042 0.042 0.042 0.042 0.042 0.042 0.042
wsweep layout5_s1/emitter_wall      x8  e1 achieved SE 0.074 dB VOV_union 0.003 U 0 | SE dB per band 0.074 0.074 0.074 0.074 0.074 0.074 0.074 0.074 | VOV per band 0.003 0.003 0.003 0.003 0.003 0.003 0.003 0.003
wsweep layout5_s1/emitter_wall      x16 W_max 48800000 W_scene 97600000 | pool(4) min 1540.4 median 1632.5 worst 1645.7 ms (3 runs); single-thread 5239.8 ms; ns/eval pool 16.57 single 53.17 | peak RSS delta 0.0 MB | n* 1024 W_pilot 6508198 N_need 48525 N_cap 14272 N 14272 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 92038092 realised/W_scene 1.0097
wsweep layout5_s1/emitter_wall      x16 e0 achieved SE 0.127 dB VOV_union 0.032 U 0 | SE dB per band 0.127 0.127 0.127 0.127 0.127 0.127 0.127 0.127 | VOV per band 0.020 0.020 0.020 0.020 0.020 0.020 0.020 0.020
wsweep layout5_s1/emitter_wall      x16 e1 achieved SE 0.050 dB VOV_union 0.003 U 0 | SE dB per band 0.050 0.050 0.050 0.050 0.050 0.050 0.050 0.050 | VOV per band 0.001 0.001 0.001 0.001 0.001 0.001 0.001 0.001
wsweep layout5_s1/emitter_wall      x1  e0 total minus x16 total, dB per band -1.323 -1.323 -1.323 -1.323 -1.323 -1.323 -1.323 -1.323
wsweep layout5_s1/emitter_wall      x1  e1 total minus x16 total, dB per band -0.367 -0.367 -0.367 -0.367 -0.367 -0.367 -0.367 -0.367
wsweep layout5_s1/emitter_wall      x2  e0 total minus x16 total, dB per band -0.244 -0.244 -0.244 -0.244 -0.244 -0.244 -0.244 -0.244
wsweep layout5_s1/emitter_wall      x2  e1 total minus x16 total, dB per band -0.083 -0.083 -0.083 -0.083 -0.083 -0.083 -0.083 -0.083
wsweep layout5_s1/emitter_wall      x4  e0 total minus x16 total, dB per band +0.421 +0.421 +0.421 +0.421 +0.421 +0.421 +0.421 +0.421
wsweep layout5_s1/emitter_wall      x4  e1 total minus x16 total, dB per band +0.069 +0.069 +0.069 +0.069 +0.069 +0.069 +0.069 +0.069
wsweep layout5_s1/emitter_wall      x8  e0 total minus x16 total, dB per band +0.087 +0.087 +0.087 +0.087 +0.087 +0.087 +0.087 +0.087
wsweep layout5_s1/emitter_wall      x8  e1 total minus x16 total, dB per band +0.037 +0.037 +0.037 +0.037 +0.037 +0.037 +0.037 +0.037
wsweep layout5_s1/emitter_wall      x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/emitter_wall      x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/both_wall         x1  W_max 3050000 W_scene 6100000 | pool(4) min 42.5 median 43.4 worst 48.3 ms (3 runs); single-thread 133.4 ms; ns/eval pool 7.24 single 22.26 | peak RSS delta 0.0 MB | n* 1024 W_pilot 1461656 N_need 35190 N_cap 3200 N 3200 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 4533604 realised/W_scene 0.9828
wsweep layout5_s1/both_wall         x1  e0 achieved SE 0.428 dB VOV_union 0.141 U 1 | SE dB per band 0.428 0.428 0.428 0.428 0.428 0.428 0.428 0.428 | VOV per band 0.167 0.167 0.167 0.167 0.167 0.167 0.167 0.167
wsweep layout5_s1/both_wall         x1  e1 achieved SE 0.215 dB VOV_union 0.024 U 0 | SE dB per band 0.215 0.215 0.215 0.215 0.215 0.215 0.215 0.215 | VOV per band 0.034 0.034 0.034 0.034 0.034 0.034 0.034 0.034
wsweep layout5_s1/both_wall         x2  W_max 6100000 W_scene 12200000 | pool(4) min 73.5 median 81.0 worst 86.4 ms (3 runs); single-thread 266.9 ms; ns/eval pool 6.71 single 22.11 | peak RSS delta 0.0 MB | n* 1024 W_pilot 1461656 N_need 35190 N_cap 7488 N 7488 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 10611144 realised/W_scene 0.9896
wsweep layout5_s1/both_wall         x2  e0 achieved SE 0.763 dB VOV_union 0.412 U 1 | SE dB per band 0.763 0.763 0.763 0.763 0.763 0.763 0.763 0.763 | VOV per band 0.411 0.411 0.411 0.411 0.411 0.411 0.411 0.411
wsweep layout5_s1/both_wall         x2  e1 achieved SE 0.137 dB VOV_union 0.015 U 0 | SE dB per band 0.137 0.137 0.137 0.137 0.137 0.137 0.137 0.137 | VOV per band 0.018 0.018 0.018 0.018 0.018 0.018 0.018 0.018
wsweep layout5_s1/both_wall         x4  W_max 12200000 W_scene 24400000 | pool(4) min 170.6 median 184.8 worst 185.7 ms (3 runs); single-thread 533.7 ms; ns/eval pool 7.65 single 22.10 | peak RSS delta 0.0 MB | n* 1024 W_pilot 1461656 N_need 35190 N_cap 16064 N 16064 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 22685986 realised/W_scene 0.9897
wsweep layout5_s1/both_wall         x4  e0 achieved SE 0.427 dB VOV_union 0.412 U 1 | SE dB per band 0.427 0.427 0.427 0.427 0.427 0.427 0.427 0.427 | VOV per band 0.298 0.298 0.298 0.298 0.298 0.298 0.298 0.299
wsweep layout5_s1/both_wall         x4  e1 achieved SE 0.092 dB VOV_union 0.015 U 0 | SE dB per band 0.092 0.092 0.092 0.092 0.092 0.092 0.092 0.092 | VOV per band 0.009 0.009 0.009 0.009 0.009 0.009 0.009 0.009
wsweep layout5_s1/both_wall         x8  W_max 24400000 W_scene 48800000 | pool(4) min 296.7 median 301.4 worst 308.9 ms (3 runs); single-thread 1078.7 ms; ns/eval pool 6.21 single 22.24 | peak RSS delta 0.9 MB | n* 1024 W_pilot 1461656 N_need 35190 N_cap 33152 N 33152 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 47047386 realised/W_scene 0.9940
wsweep layout5_s1/both_wall         x8  e0 achieved SE 1.121 dB VOV_union 0.412 U 1 | SE dB per band 1.121 1.121 1.121 1.121 1.121 1.121 1.121 1.121 | VOV per band 0.563 0.563 0.563 0.563 0.563 0.563 0.563 0.563
wsweep layout5_s1/both_wall         x8  e1 achieved SE 0.065 dB VOV_union 0.015 U 0 | SE dB per band 0.065 0.065 0.065 0.065 0.065 0.065 0.065 0.065 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/both_wall         x16 W_max 48800000 W_scene 97600000 | pool(4) min 341.8 median 364.8 worst 385.4 ms (3 runs); single-thread 1191.7 ms; ns/eval pool 7.09 single 23.16 | peak RSS delta 0.8 MB | n* 1024 W_pilot 1461656 N_need 35190 N_cap 67328 N 35200 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 49989090 realised/W_scene 0.5272
wsweep layout5_s1/both_wall         x16 e0 achieved SE 1.080 dB VOV_union 0.412 U 1 | SE dB per band 1.080 1.080 1.080 1.080 1.080 1.080 1.080 1.080 | VOV per band 0.560 0.560 0.560 0.560 0.560 0.560 0.560 0.560
wsweep layout5_s1/both_wall         x16 e1 achieved SE 0.064 dB VOV_union 0.015 U 0 | SE dB per band 0.064 0.064 0.064 0.064 0.064 0.064 0.064 0.064 | VOV per band 0.004 0.004 0.004 0.004 0.004 0.004 0.004 0.004
wsweep layout5_s1/both_wall         x1  e0 total minus x16 total, dB per band -2.215 -2.215 -2.215 -2.215 -2.215 -2.215 -2.215 -2.215
wsweep layout5_s1/both_wall         x1  e1 total minus x16 total, dB per band +0.175 +0.175 +0.175 +0.175 +0.175 +0.175 +0.175 +0.175
wsweep layout5_s1/both_wall         x2  e0 total minus x16 total, dB per band -0.847 -0.847 -0.847 -0.847 -0.847 -0.847 -0.847 -0.847
wsweep layout5_s1/both_wall         x2  e1 total minus x16 total, dB per band -0.030 -0.030 -0.030 -0.030 -0.030 -0.030 -0.030 -0.030
wsweep layout5_s1/both_wall         x4  e0 total minus x16 total, dB per band -1.288 -1.288 -1.288 -1.288 -1.288 -1.288 -1.288 -1.288
wsweep layout5_s1/both_wall         x4  e1 total minus x16 total, dB per band -0.083 -0.083 -0.083 -0.083 -0.083 -0.083 -0.083 -0.083
wsweep layout5_s1/both_wall         x8  e0 total minus x16 total, dB per band +0.090 +0.090 +0.090 +0.090 +0.090 +0.090 +0.090 +0.090
wsweep layout5_s1/both_wall         x8  e1 total minus x16 total, dB per band -0.020 -0.020 -0.020 -0.020 -0.020 -0.020 -0.020 -0.020
wsweep layout5_s1/both_wall         x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/both_wall         x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/both_corner       x1  W_max 3050000 W_scene 6100000 | pool(4) min 42.6 median 43.4 worst 47.5 ms (3 runs); single-thread 121.1 ms; ns/eval pool 7.20 single 20.08 | peak RSS delta 0.0 MB | n* 1024 W_pilot 3035309 N_need 28428 N_cap 1024 N 1024 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 2997053 realised/W_scene 0.9889
wsweep layout5_s1/both_corner       x1  e0 achieved SE 0.208 dB VOV_union 0.067 U 1 | SE dB per band 0.208 0.208 0.208 0.208 0.208 0.208 0.208 0.208 | VOV per band 0.037 0.037 0.037 0.037 0.037 0.037 0.037 0.037
wsweep layout5_s1/both_corner       x1  e1 achieved SE 0.488 dB VOV_union 0.049 U 1 | SE dB per band 0.488 0.488 0.488 0.488 0.488 0.488 0.488 0.488 | VOV per band 0.090 0.090 0.090 0.090 0.090 0.090 0.090 0.090
wsweep layout5_s1/both_corner       x2  W_max 6100000 W_scene 12200000 | pool(4) min 86.1 median 88.1 worst 88.9 ms (3 runs); single-thread 304.2 ms; ns/eval pool 7.29 single 25.18 | peak RSS delta 0.0 MB | n* 1024 W_pilot 3035309 N_need 28428 N_cap 3072 N 3072 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 9044719 realised/W_scene 0.9902
wsweep layout5_s1/both_corner       x2  e0 achieved SE 0.192 dB VOV_union 0.093 U 1 | SE dB per band 0.192 0.192 0.192 0.192 0.192 0.192 0.192 0.192 | VOV per band 0.132 0.132 0.132 0.132 0.132 0.132 0.132 0.132
wsweep layout5_s1/both_corner       x2  e1 achieved SE 0.283 dB VOV_union 0.046 U 0 | SE dB per band 0.283 0.283 0.283 0.283 0.283 0.283 0.283 0.283 | VOV per band 0.063 0.063 0.063 0.063 0.063 0.063 0.063 0.063
wsweep layout5_s1/both_corner       x4  W_max 12200000 W_scene 24400000 | pool(4) min 144.4 median 150.7 worst 152.6 ms (3 runs); single-thread 534.6 ms; ns/eval pool 6.23 single 22.10 | peak RSS delta 0.0 MB | n* 1024 W_pilot 3035309 N_need 28428 N_cap 7168 N 7168 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 21160289 realised/W_scene 0.9916
wsweep layout5_s1/both_corner       x4  e0 achieved SE 0.145 dB VOV_union 0.069 U 1 | SE dB per band 0.145 0.145 0.145 0.145 0.145 0.145 0.145 0.145 | VOV per band 0.077 0.077 0.077 0.077 0.077 0.077 0.077 0.077
wsweep layout5_s1/both_corner       x4  e1 achieved SE 0.215 dB VOV_union 0.031 U 0 | SE dB per band 0.215 0.215 0.215 0.215 0.215 0.215 0.215 0.215 | VOV per band 0.044 0.044 0.044 0.044 0.044 0.044 0.044 0.044
wsweep layout5_s1/both_corner       x8  W_max 24400000 W_scene 48800000 | pool(4) min 298.0 median 303.9 worst 336.5 ms (3 runs); single-thread 1178.0 ms; ns/eval pool 6.29 single 24.37 | peak RSS delta 0.0 MB | n* 1024 W_pilot 3035309 N_need 28428 N_cap 15424 N 15424 cap hit 1 floor truncated 0 pilot shipped 0 | W_final 45308553 realised/W_scene 0.9907
wsweep layout5_s1/both_corner       x8  e0 achieved SE 0.223 dB VOV_union 0.069 U 1 | SE dB per band 0.223 0.223 0.223 0.223 0.223 0.223 0.223 0.223 | VOV per band 0.640 0.640 0.640 0.640 0.640 0.640 0.640 0.640
wsweep layout5_s1/both_corner       x8  e1 achieved SE 0.141 dB VOV_union 0.031 U 0 | SE dB per band 0.141 0.141 0.141 0.141 0.141 0.141 0.141 0.141 | VOV per band 0.020 0.020 0.020 0.020 0.020 0.020 0.020 0.020
wsweep layout5_s1/both_corner       x16 W_max 48800000 W_scene 97600000 | pool(4) min 508.4 median 520.1 worst 572.4 ms (3 runs); single-thread 1813.3 ms; ns/eval pool 5.98 single 20.86 | peak RSS delta 0.0 MB | n* 1024 W_pilot 3035309 N_need 28428 N_cap 31872 N 28480 cap hit 0 floor truncated 0 pilot shipped 0 | W_final 83884672 realised/W_scene 0.8906
wsweep layout5_s1/both_corner       x16 e0 achieved SE 0.156 dB VOV_union 0.069 U 0 | SE dB per band 0.156 0.156 0.156 0.156 0.156 0.156 0.156 0.156 | VOV per band 0.227 0.227 0.227 0.227 0.227 0.227 0.227 0.227
wsweep layout5_s1/both_corner       x16 e1 achieved SE 0.107 dB VOV_union 0.031 U 0 | SE dB per band 0.107 0.107 0.107 0.107 0.107 0.107 0.107 0.107 | VOV per band 0.009 0.009 0.009 0.009 0.009 0.009 0.009 0.009
wsweep layout5_s1/both_corner       x1  e0 total minus x16 total, dB per band -0.744 -0.744 -0.744 -0.744 -0.744 -0.744 -0.744 -0.744
wsweep layout5_s1/both_corner       x1  e1 total minus x16 total, dB per band +0.119 +0.119 +0.119 +0.119 +0.119 +0.119 +0.119 +0.119
wsweep layout5_s1/both_corner       x2  e0 total minus x16 total, dB per band -0.477 -0.477 -0.477 -0.477 -0.477 -0.477 -0.477 -0.477
wsweep layout5_s1/both_corner       x2  e1 total minus x16 total, dB per band -0.036 -0.036 -0.036 -0.036 -0.036 -0.036 -0.036 -0.036
wsweep layout5_s1/both_corner       x4  e0 total minus x16 total, dB per band -0.296 -0.296 -0.296 -0.296 -0.296 -0.296 -0.296 -0.296
wsweep layout5_s1/both_corner       x4  e1 total minus x16 total, dB per band +0.077 +0.077 +0.077 +0.077 +0.077 +0.077 +0.077 +0.077
wsweep layout5_s1/both_corner       x8  e0 total minus x16 total, dB per band -0.161 -0.161 -0.161 -0.161 -0.161 -0.161 -0.161 -0.161
wsweep layout5_s1/both_corner       x8  e1 total minus x16 total, dB per band -0.170 -0.170 -0.170 -0.170 -0.170 -0.170 -0.170 -0.170
wsweep layout5_s1/both_corner       x16 e0 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
wsweep layout5_s1/both_corner       x16 e1 total minus x16 total, dB per band +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000 +0.000
===============================================================================
All tests passed (170 assertions in 1 test case)


real	3m46.840s
user	8m21.053s
sys	0m0.778s
```

### Replicates (`spatial_tests "wmax-sweep: 30-replicate*"`)

```
Filters: "wmax-sweep: 30-replicate*"
Randomness seeded to: 3908951137
wsweep-replicates cube100_lowalpha0.05_s0.3  x1  e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median +0.003 dB, p95 |error| 0.254 dB, max |error| 0.406 dB; achieved SE median 0.117 dB; replicates took 2291 ms
wsweep-replicates cube100_lowalpha0.05_s0.3  x1  e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median +0.026 dB, p95 |error| 0.179 dB, max |error| 0.261 dB; achieved SE median 0.115 dB; replicates took 2291 ms
wsweep-replicates cube100_lowalpha0.05_s0.3  x4  e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median -0.007 dB, p95 |error| 0.157 dB, max |error| 0.189 dB; achieved SE median 0.071 dB; replicates took 5206 ms
wsweep-replicates cube100_lowalpha0.05_s0.3  x4  e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median +0.007 dB, p95 |error| 0.158 dB, max |error| 0.232 dB; achieved SE median 0.073 dB; replicates took 5206 ms
wsweep-replicates cube100_lowalpha0.05_s0.3  x16 e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median -0.003 dB, p95 |error| 0.157 dB, max |error| 0.189 dB; achieved SE median 0.071 dB; replicates took 5813 ms
wsweep-replicates cube100_lowalpha0.05_s0.3  x16 e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.006 dB, 20495 ms; stride 1048576): median +0.007 dB, p95 |error| 0.158 dB, max |error| 0.232 dB; achieved SE median 0.073 dB; replicates took 5813 ms
wsweep-replicates cube100_flutter_fallback   x1  e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median +0.000 dB, p95 |error| 0.003 dB, max |error| 0.005 dB; achieved SE median 0.002 dB; replicates took 4826 ms
wsweep-replicates cube100_flutter_fallback   x1  e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median -0.000 dB, p95 |error| 0.005 dB, max |error| 0.015 dB; achieved SE median 0.002 dB; replicates took 4826 ms
wsweep-replicates cube100_flutter_fallback   x4  e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median -0.000 dB, p95 |error| 0.002 dB, max |error| 0.003 dB; achieved SE median 0.001 dB; replicates took 10655 ms
wsweep-replicates cube100_flutter_fallback   x4  e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median +0.000 dB, p95 |error| 0.003 dB, max |error| 0.003 dB; achieved SE median 0.001 dB; replicates took 10655 ms
wsweep-replicates cube100_flutter_fallback   x16 e0: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median -0.000 dB, p95 |error| 0.002 dB, max |error| 0.003 dB; achieved SE median 0.001 dB; replicates took 11419 ms
wsweep-replicates cube100_flutter_fallback   x16 e1: 30 replicates at 1 kHz vs long run (2^20 histories from 33554432, SE 0.000 dB, 152771 ms; stride 1048576): median +0.000 dB, p95 |error| 0.003 dB, max |error| 0.003 dB; achieved SE median 0.001 dB; replicates took 11419 ms
===============================================================================
test cases: 1 | 1 passed
assertions: - none -


real	3m33.924s
user	13m31.076s
sys	0m1.121s
```
