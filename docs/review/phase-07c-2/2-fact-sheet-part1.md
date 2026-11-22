# 2 — Fact sheet, part 1 (F1, F2, F5, F6, F7, F8, F9, F10, F11, F13), for the decider (phase 07c-2, D-W1)

2026-11-22. Extracted from records on file and from the code at HEAD 5f2fd24 (branch `claude/modest-planck-5xtgzp`).
Nothing measured or built for this sheet. Numbers are copied as printed. A value marked *derived* is arithmetic on printed
values, and the arithmetic is given. "Not on file" means no record in the repository holds the value. The CI logs of
those runs may still hold it, but they were not fetched.

## Read first: the `nsPerEval` denominator counts the work twice

`05h-records GATE … nsPerEval` (and the `05h-records solve` line it comes from) divides the solve median by
**W_pilot + W_final summed over the scene's emitters**. `W_pilot` and `W_final` are scene totals (one solve for both
emitters), and `src/sim/Engine.cpp` L222–223 copies them into each emitter's diagnostics. Summing over the two emitters
therefore counts each one twice:

- code: `tests/unit/test_diffuse_records.cpp` L483–488: `for (const auto& em : diag.emitters) work += em.match.diffuse.wPilot + em.match.diffuse.wFinal;` then `nsPerEval = solveMedianMs * 1e6 / work`;
- record: `05h-records solve cube100_flutter_fallback … 12.97 ns per image evaluation over W_pilot + W_final 11403548`
  (`docs/review/phase-07c-1/44-…43291051799.md` L47). The scene's work is W_pilot 3 154 338 + W_final 2 547 436 = 5 701 774
  (same file L44–45, printed once per emitter with equal values). 11 403 548 = 2 × 5 701 774. For the low-α cube,
  12 089 950 = 2 × (1 696 086 + 4 348 889) (L55–58).

So the printed `nsPerEval` is **half** the cost per scene image evaluation. The 05h cost benchmark
(`tests/unit/test_diffuse_bench.cpp` L136–141) divides by `first.wPilot + first.wFinal`, counted once. Its figures
(16.4 ns at pool 4, 44.3–44.7 ns on one thread on Linux, `docs/review/phase-05h/1-orchestrator-cpp-costs.md` L65–75)
are per scene evaluation. K3 (12.97 / 7.59 ns) and K4 (44.7 ns) are on different bases, a factor of 2 apart. The
"per scene eval" column in F1 below gives solveMedianMs × 10⁶ / scene work (*derived*).

---

## F1 — `nsPerEval` per OS and scene, from every GATE line on file

Scene work (deterministic, D7; pinned in `tests/unit/test_diffuse_records.cpp` L437–444): flutter W_pilot + W_final =
3 154 338 + 2 547 436 = **5 701 774**; low-α s 0.3 = 1 696 086 + 4 348 889 = **6 044 975**. The last column is
*derived*: solveMedianMs × 10⁶ / scene work.

| run | OS | scene | solveMedianMs | nsPerEval (as printed) | ns per scene eval (*derived*) | source |
|---|---|---|---|---|---|---|
| 43007183782 | Linux | flutter | 131.2 | 11.51 | 23.01 | `phase-05i/3` L8 |
| 43007183782 | Linux | low-α s0.3 | 80.9 | 6.69 | 13.38 | `phase-05i/3` L9 |
| 43007183782 | macOS | flutter | 102.7 | 9.00 | 18.01 | `phase-05i/3` L206 |
| 43007183782 | macOS | low-α s0.3 | 83.7 | 6.92 | 13.85 | `phase-05i/3` L207 |
| 43007183782 | Windows | flutter | 145.0 | 12.72 | 25.43 | `phase-05i/3` L360 |
| 43007183782 | Windows | low-α s0.3 | 90.6 | 7.50 | 14.99 | `phase-05i/3` L361 |
| 43031773338 | Linux | flutter | 130.9 | 11.48 | 22.96 | `phase-05i/19` L97 |
| 43031773338 | Linux | low-α s0.3 | 81.3 | 6.73 | 13.45 | `phase-05i/19` L98 |
| 43031773338 | macOS | flutter | 99.4 | 8.72 | 17.43 | `phase-05i/19` L464 |
| 43031773338 | macOS | low-α s0.3 | 76.9 | 6.36 | 12.72 | `phase-05i/19` L465 |
| 43031773338 | Windows | flutter | 150.2 | 13.17 | 26.34 | `phase-05i/19` L606 |
| 43031773338 | Windows | low-α s0.3 | 93.5 | 7.74 | 15.47 | `phase-05i/19` L607 |
| 43215018040 | Linux | flutter | 131.3 | 11.52 | 23.03 | `phase-07c-1/19` L82 |
| 43215018040 | Linux | low-α s0.3 | 82.5 | 6.83 | 13.65 | `phase-07c-1/19` L83 |
| 43215018040 | macOS | flutter | 87.2 | 7.64 | 15.29 | `phase-07c-1/19` L460 |
| 43215018040 | macOS | low-α s0.3 | 113.9 | 9.42 | 18.84 | `phase-07c-1/19` L461 |
| 43215018040 | Windows | — | not on file (build (windows) failed on a test bug; file 19 L3) | | | |
| 43227272415 | Linux, macOS | — | not on file (file 20 holds the Windows job only) | | | |
| 43227272415 | Windows | flutter | 143.2 | 12.56 | 25.11 | `phase-07c-1/20` L236 |
| 43227272415 | Windows | low-α s0.3 | 90.0 | 7.44 | 14.89 | `phase-07c-1/20` L237 |
| 43242209571 | Linux | flutter | 99.4 | 8.72 | 17.43 | `phase-07c-1/41` L76 |
| 43242209571 | Linux | low-α s0.3 | 62.1 | 5.13 | 10.27 | `phase-07c-1/41` L77 |
| 43242209571 | macOS | flutter | 105.6 | 9.26 | 18.52 | `phase-07c-1/41` L425 |
| 43242209571 | macOS | low-α s0.3 | 80.3 | 6.64 | 13.28 | `phase-07c-1/41` L426 |
| 43242209571 | Windows | flutter | 145.7 | 12.78 | 25.55 | `phase-07c-1/41` L747 |
| 43242209571 | Windows | low-α s0.3 | 90.3 | 7.47 | 14.94 | `phase-07c-1/41` L748 |
| 43258505284 | Linux | flutter | 130.4 | 11.43 | 22.87 | `phase-07c-1/42` L204 |
| 43258505284 | Linux | low-α s0.3 | 80.7 | 6.68 | 13.35 | `phase-07c-1/42` L205 |
| 43258505284 | macOS | flutter | 221.9 | 19.46 | 38.92 | `phase-07c-1/42` L565 (warnings=SOLVE) |
| 43258505284 | macOS | low-α s0.3 | 92.3 | 7.63 | 15.27 | `phase-07c-1/42` L566 |
| 43258505284 | Windows | flutter | 112.8 | 9.90 | 19.78 | `phase-07c-1/42` L809 |
| 43258505284 | Windows | low-α s0.3 | 70.7 | 5.85 | 11.70 | `phase-07c-1/42` L810 |
| 43291051799 | Linux | flutter | 147.9 | 12.97 | 25.94 | `phase-07c-1/44` L73 |
| 43291051799 | Linux | low-α s0.3 | 91.7 | 7.59 | 15.17 | `phase-07c-1/44` L74 |
| 43291051799 | macOS | flutter | 117.1 | 10.27 | 20.54 | `phase-07c-1/44` L592 |
| 43291051799 | macOS | low-α s0.3 | 90.8 | 7.51 | 15.02 | `phase-07c-1/44` L593 |
| 43291051799 | Windows | flutter | 143.5 | 12.58 | 25.17 | `phase-07c-1/44` L772 |
| 43291051799 | Windows | low-α s0.3 | 90.1 | 7.45 | 14.90 | `phase-07c-1/44` L773 |
| 43389296112 (S2) | Linux | flutter | 102.5 | 8.99 | 17.98 | `phase-07c-1b/23` L7 |
| 43389296112 (S2) | Linux | low-α s0.3 | 62.7 | 5.19 | 10.37 | `phase-07c-1b/23` L8 |
| 43389296112 (S2) | macOS | flutter | 118.5 | 10.40 | 20.78 | `phase-07c-1b/23` L20 |
| 43389296112 (S2) | macOS | low-α s0.3 | 63.3 | 5.24 | 10.47 | `phase-07c-1b/23` L21 |
| 43389296112 (S2) | Windows | flutter | 113.4 | 9.95 | 19.89 | `phase-07c-1b/23` L41 |
| 43389296112 (S2) | Windows | low-α s0.3 | 70.7 | 5.85 | 11.70 | `phase-07c-1b/23` L42 |
| 43402114873 (S2) | Linux | flutter | 131.0 | 11.49 | 22.98 | `phase-07c-1b/23` L54 |
| 43402114873 (S2) | Linux | low-α s0.3 | 80.8 | 6.68 | 13.37 | `phase-07c-1b/23` L55 |
| 43402114873 (S2) | macOS | flutter | 109.5 | 9.60 | 19.20 | `phase-07c-1b/23` L60 |
| 43402114873 (S2) | macOS | low-α s0.3 | 84.1 | 6.96 | 13.91 | `phase-07c-1b/23` L61 |
| 43402114873 (S2) | Windows | flutter | 90.2 | 7.91 | 15.82 | `phase-07c-1b/23` L81 |
| 43402114873 (S2) | Windows | low-α s0.3 | 56.1 | 4.64 | 9.28 | `phase-07c-1b/23` L82 |
| 43412038058 (S2) | Linux | flutter | 159.0 | 13.95 | 27.89 | `phase-07c-1b/23` L94 (SOLVE) |
| 43412038058 (S2) | Linux | low-α s0.3 | 98.7 | 8.16 | 16.33 | `phase-07c-1b/23` L95 (SOLVE) |
| 43412038058 (S2) | macOS | flutter | 103.9 | 9.11 | 18.22 | `phase-07c-1b/23` L107 |
| 43412038058 (S2) | macOS | low-α s0.3 | 86.9 | 7.19 | 14.38 | `phase-07c-1b/23` L108 |
| 43412038058 (S2) | Windows | flutter | 114.5 | 10.04 | 20.08 | `phase-07c-1b/23` L121 |
| 43412038058 (S2) | Windows | low-α s0.3 | 71.8 | 5.94 | 11.88 | `phase-07c-1b/23` L122 |
| 43427854710 (PR #33) | all | — | **not on file**: the files that quote it (`phase-07c-1b/28` L8–12, 28b, 29–33) give the ratio, 14 × worst, the medians and flutterDev, but no solveMedianMs or nsPerEval | | | |

Per-OS ranges over the 10 runs on file, as printed (*derived* min–max):

| OS | flutter nsPerEval | low-α nsPerEval |
|---|---|---|
| Linux | 8.72–13.95 (10 runs) | 5.13–8.16 (10 runs) |
| macOS | 7.64–19.46 (10 runs; 19.46 is the SOLVE outlier of 43258505284; without it 7.64–10.40) | 5.24–9.42 (10 runs) |
| Windows | 7.91–13.17 (10 runs) | 4.64–7.74 (10 runs) |

The S2 re-pin means (`docs/review/phase-07c-1b/22-repin-gate-output.md`, the printed `S2Pin` constants, equal to
`tests/unit/test_diffuse_records.cpp` L150–172) give solveRefMs flutter / low-α: Linux 130.8 / 80.7, macOS 110.6 / 78.1,
Windows 106.0 / 66.2 ms.

**Timed region (D-Q5 K18), from the code.** `tests/unit/test_diffuse_records.cpp` L475–481: `t0 = Clock::now();
(void)estimateDiffuse(planned.problem); solve.push_back(ms(t0, Clock::now()));`, five times, median. Default limits and
default options apply, so the pool is `ThreadPool::process()` (`src/sim/diffuse/DiffuseEstimator.cpp` L481). **Yes:
the timed region covers `estimateDiffuse` alone.** `diffuse_test::plan(sc)` runs outside it. The work counted in the
denominator comes from `diag` (an earlier build of the same scene), not from the timed result. The two are the same by
D7 and pinned (L437–444). The time includes the pilot's speculative blocks past the stop (see F2, flutter); the work
count excludes them.

## F2 — pool size and solve medians

**Code.**
- `src/sim/diffuse/ThreadPool.cpp` L28–31: the process-wide pool has `std::max(1u, std::thread::hardware_concurrency())`
  threads, the caller included (`ThreadPool.h` L21).
- Plugin path: `src/plugin/core/DiffuseSolveGate.cpp` L34 creates the process-wide gate with
  `std::max(1u, std::thread::hardware_concurrency())` pool threads, and `ScenePipeline::solveStage` passes
  `&gate_->pool()` (`src/plugin/core/ScenePipeline.cpp` L267–296). These are two pool objects of the same size.
- render_cli and tests use `ThreadPool::process()` unless a pool is passed (`src/sim/Engine.h` L107–110).
- The pilot runs `pool.size()` blocks per batch and scans them in order. Blocks past the stop are discarded
  (`DiffuseEstimator.cpp` L505–526), so a result never depends on the pool size, but the time does.

**CI runners** (`05h-records pool size` = `ThreadPool::process().size()`, `test_diffuse_records.cpp` L351; B1-b lines
print `hardware_concurrency`):

| OS | pool size | sources |
|---|---|---|
| Linux | 4 | `phase-05i/19` L57; `phase-07c-1/19` L42, `/41` L30, `/42` L158, `/44` L27; B1-b `hardware_concurrency 4`, `phase-07c-1b/23` L10–14, 48–52, 88–92 |
| macOS | 3 | `phase-05i/19` L424; `phase-07c-1/19` L420, `/41` L379, `/42` L519, `/44` L546; B1-b `hardware_concurrency 3`, `phase-07c-1b/23` L24–28, 64–68, 101–105 |
| Windows | 4 | `phase-05i/19` L566; `phase-07c-1/20` L196, `/41` L701, `/42` L763, `/44` L726; B1-b `hardware_concurrency 4`, `phase-07c-1b/23` L35–39, 75–79, 115–119 |

**Solve medians at the pool size**: the solveMedianMs column of F1 (Release, median of 5, per run).

**Solve at 1 thread**: **not on file for any 07c-era run.** The GATE lines time only the pool solve. The 05h cost
benchmark prints a one-thread solve (`test_diffuse_bench.cpp` L143–154) and runs in CI's `[benchmark]` step, but the
job-summary grep keeps only `^(05h|05i|07c1|07c1b)-records` lines (`.github/workflows/ci.yml` L431), and no orchestrator
file after phase 05h copied the `05h-cost` lines. The only one-thread figures on file are from run 42846229834
(estimator commit c309589, `docs/review/phase-05h/1-orchestrator-cpp-costs.md` L65–75, solve median of 10 at the pool
size; one thread a single run):

| OS (pool) | scene | pool solve min / median / max (ms) | ns per scene eval at pool | one thread ms; ns per scene eval |
|---|---|---|---|---|
| Linux (4) | flutter | 160.1 / 161.5 / 171.1 | 28.3 | 321.7; 56.4 |
| Linux (4) | low-α s 0.3 | 98.5 / 98.9 / 99.6 | 16.4 | 268.0; 44.3 |
| Linux (4) | low-α s 1 | 98.0 / 98.5 / 100.1 | 16.4 | 268.7; 44.7 |
| macOS (3) | flutter | 78.5 / 95.9 / 116.0 | 16.8 | 163.9; 28.7 |
| macOS (3) | low-α s 0.3 | 51.5 / 57.7 / 67.4 | 9.6 | 134.5; 22.3 |
| macOS (3) | low-α s 1 | 75.9 / 82.6 / 88.3 | 13.7 | 155.6; 25.9 |
| Windows (4) | flutter | 113.9 / 114.7 / 116.1 | 20.1 | 218.7; 38.4 |
| Windows (4) | low-α s 0.3 | 70.7 / 71.0 / 71.5 | 11.7 | 185.3; 30.7 |
| Windows (4) | low-α s 1 | 70.8 / 71.1 / 72.2 | 11.8 | 189.2; 31.5 |

Same file L44–48: at the flutter scene the pilot stops at 5 of 16 blocks, and "about 1.89 M extra evaluations were
computed with 4 threads, 33 % over the counted work, so that scene's 'ns per evaluation' below is inflated". Whether
the estimator's per-evaluation cost changed between c309589 and today is not on file. The W_pilot / W_final pins are
unchanged (05h file 1 L27–28 = `test_diffuse_records.cpp` L437–444).

## F5 — cap and pilot status of every fixture at the current pin (D5 golden)

Source: `tests/golden/phase05h_d5_hashes.json`, generated at W_max 3.05 M per emitter (W_scene 6 100 000) and n*_max
1 024, 48 kHz (`tests/golden/CHANGELOG.md` L113). Fields on file: `nStar, nNeed, n, nCap, wPilot, wFinal, capHit,
floorTruncated, pilotFloor, pilotShipped`.

**Missing from the golden:** the pilot stop reason and W_scene. The stop reason here is *derived* from the code's stop
test `n >= n*_max || 2 W_pilot >= W_scene` (`DiffuseEstimator.cpp` L390–393) with W_scene = 6 100 000:
"n*_max" if n* = 1 024 and 2·W_pilot < W_scene, "work" if 2·W_pilot ≥ W_scene. No fixture meets both.

| fixture | n* | N_need | N | N_cap | W_pilot | W_final | cap hit | floor trunc. | pilot floor | pilot shipped | 2·W_pilot ≥ W_scene | stop (*derived*) | (W_pilot+W_final)/W_scene (*derived*) |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| asymmetric_materials | 256 | 703 | 128 | 128 | 4009269 | 2013428 | 1 | 1 | 1 | 0 | yes | work | 0.9873 |
| classroom | 1024 | 186 | 1024 | 24832 | 241415 | 239253 | 0 | 0 | 0 | 0 | no | n*_max | 0.0788 |
| club | 1024 | 531 | 1024 | 23168 | 257535 | 254834 | 0 | 0 | 0 | 0 | no | n*_max | 0.0840 |
| concert_hall_box | 1024 | 3407 | 3456 | 20416 | 290713 | 976955 | 0 | 0 | 0 | 0 | no | n*_max | 0.2078 |
| dead_booth | 1024 | 49 | 1024 | 4800 | 1071449 | 1073646 | 0 | 0 | 0 | 0 | no | n*_max | 0.3517 |
| edge_values | 64 | 147242 | 0 | 0 | 17125012 | 0 | 1 | 1 | 1 | 1 | yes | work (one block exceeds W_scene) | 2.8074 |
| large_hall | 1024 | 2150 | 2176 | 8256 | 669205 | 1408225 | 0 | 0 | 0 | 0 | no | n*_max | 0.3406 |
| living_room | 1024 | 86 | 1024 | 16640 | 353336 | 355165 | 0 | 0 | 0 | 0 | no | n*_max | 0.1161 |
| medium_room | 256 | 65 | 128 | 128 | 3967675 | 2022235 | 0 | 1 | 1 | 0 | yes | work | 0.9820 |
| open_field | 1024 | 1423887 | 2624 | 2624 | 1688473 | 4201933 | 1 | 0 | 0 | 0 | no | n*_max | 0.9656 |
| small_room | 1024 | 29 | 1024 | 8064 | 684164 | 684611 | 0 | 0 | 0 | 0 | no | n*_max | 0.2244 |
| stone_box | 1024 | 60 | 1024 | 25920 | 231561 | 231532 | 0 | 0 | 0 | 0 | no | n*_max | 0.0759 |

**W_uncap** (*derived*). The formula given is W_pilot + N_need·W_pilot/n*. The second column uses the code's form
`pathCount` (`DiffuseEstimator.cpp` L359–388): N_cap ≥ ceil₆₄(max(N_need, n*)), i.e.
W ≥ W_pilot + ceil₆₄(max(N_need, n*))·W_pilot/n*. This differs from the first column when N_need < n* or N_need is not a
multiple of 64. Values are W_scene; W per emitter = half.

| fixture (capped or floor-truncated) | W_uncap, formula as given (W_scene) | per emitter | W_uncap, block form (W_scene) | per emitter | × current W_scene (formula) |
|---|---|---|---|---|---|
| asymmetric_materials (cap hit; work-stopped) | 15019097.54296875 | 7509548.77 | 15034758.75 (ceil₆₄ 704) | 7517379.38 | 2.4621 |
| edge_values (cap hit; pilot shipped; work-stopped) | 39415890901.125 | 19707945450.56 | 39421777624.0 (147264) | 19710888812.0 | 6461.6215 |
| open_field (cap hit; n*_max-stopped) | 2349534912.991211 | 1174767456.50 | 2349615709.0625 (1423936) | 1174807854.53 | 385.1697 |
| medium_room (no cap hit; floor truncated N 128 < n* 256; work-stopped) | 4975092.48046875 (N_need 65 < n*) | 2487546.24 | 7935350.0 (max(N_need, n*) = 256) | 3967675.0 | 0.8156 (block form 1.3009) |

For the work-stopped fixtures (asymmetric_materials, edge_values, medium_room), W_uncap is computed from **today's**
pilot. At a larger W_scene their pilot runs further (up to n*_max), so W_pilot, n* and N_need change (F11). The value is
an estimate from the current pilot, not a fixed point.

**Gated and reported cubes and W1** (not in the D5 golden; `docs/review/phase-05h/1-orchestrator-cpp-costs.md` L27–30,
run 42846229834, identical on three OSes; W_pilot / W_final equal today's pins, `test_diffuse_records.cpp` L437–444):

| scene | n* | N_need | N_cap | N | W_pilot | W_final | cap hit | stop (*derived*) | W_uncap formula (W_scene) | block form | × W_scene |
|---|---|---|---|---|---|---|---|---|---|---|---|
| cube100_flutter_fallback | 320 | 1 | 256 | 256 | 3154338 | 2547436 | 0 (floor truncated 1, pilot floor 1) | work (2 × 3154338 = 6308676 ≥ 6100000) | not capped | N_cap ≥ ceil₆₄(320) = 320 needs W ≥ 6308676.0 | — |
| cube100_lowalpha0.05_s0.3 | 1024 | 3574 | 2624 | 2624 | 1696086 | 4348889 | 1 | n*_max | 7615823.66015625 (per emitter 3807911.83) | 7632387.0 (3584) | 1.2485 |
| cube100_lowalpha0.05_s1 | 1024 | 58612 | 2688 | 2688 | 1666253 | 4347497 | 1 | n*_max | 97039710.84765625 (per emitter 48519855.42) | 97059237.25 (58624) | 15.9082 |
| W1 (AQ10 room) | 1024 | 515 | 15744 | 1024 | 371272 | 370767 | 0 | n*_max | not capped | — | — |

Reported set (`docs/review/phase-05h/13-orchestrator-reported-set.md` L10–22, local Release, W_max 3.05 M): every
layout4_s1 row is capped with n* 256–640 (work-stopped: n* < 1 024). layout5_s1 rows are capped, with n* 1 024 except
emitter_wall (n* 512). W1/both_corner: n* 1 024, N 1 024, N_cap 1 088, no cap hit.

**AQ10 W1 / W2.** BUILD_PLAN AQ10 (`docs/BUILD_PLAN.md` L117) defines W2 as "both emitters in the AX22 fallback at
N_cap". That N_cap is the **AX22 image-count cap** ν_r(i₀), not AX41's diffuse N_cap. The benchmark
(`tests/unit/test_hybrid_ir.cpp` L371–413) times `buildRoomIR` with default options, which include the diffuse solve
(`tailLevelAx16` false), and prints images, t_cap and the median. It prints no diffuse n*, N_need, N_cap or cap hit for
W2. **Whether W2 binds AX41's diffuse cap: not on file.** The AQ10 W1/W2 benchmark lines (`AQ10 W1 …`, `AQ10 W2 …`) are
also not in any orchestrator record file after phase 05h (the job-summary grep does not keep them). W1 does not bind
the diffuse cap at the current pin (N_need 515, N_cap 15 744, above).

## F6 — AX38 (iv) load totals (latest on file: run 43291051799)

**07c-1b S2 runs (43389296112, 43402114873, 43412038058): their (iv) and (h) lines are not on file.**
`docs/review/phase-07c-1b/23-s2-records-excerpt.md` holds only the (c) B1-b and GATE lines. Run 43291051799 is the
latest run with these lines on file (`phase-07c-1/44`).

**(a) Time until the last instance is audible (interim)**. Instances are prepared and restored one after another on one
host thread. The time runs from the first prepare to the last restore's return (`test_diffuse_records.cpp` L1280–1331).
Final-settled time is not measured by this test.

| room | fs | instances | Linux (ms) | macOS (ms) | Windows (ms) |
|---|---|---|---|---|---|
| AQ10 room | 48000 | 1 | 285 | 266 | 304 |
| AQ10 room | 48000 | 4 | 1301 | 1216 | 1454 |
| AQ10 room | 48000 | 8 | 2656 | 2592 | 3003 |
| AQ10 room | 96000 | 1 | 496 | 393 | 492 |
| AQ10 room | 96000 | 4 | 2181 | 2154 | 2310 |
| AQ10 room | 96000 | 8 | 4670 | 3827 | 4789 |
| cube100_lowalpha0.05_s0.3 (100 m) | 48000 | 1 | 965 | 923 | 1005 |
| cube100_lowalpha0.05_s0.3 | 48000 | 4 | 3910 | 3497 | 3872 |
| cube100_lowalpha0.05_s0.3 | 48000 | 8 | 8424 | 7342 | 8218 |
| cube100_lowalpha0.05_s0.3 | 96000 | 1 | 2207 | 2009 | 1876 |
| cube100_lowalpha0.05_s0.3 | 96000 | 4 | 8956 | 8825 | 7719 |
| cube100_lowalpha0.05_s0.3 | 96000 | 8 | 19185 | 18276 | 17610 |

Sources: `phase-07c-1/44` Linux L125–136, macOS L534–545, Windows L814–825 (`05h-records (iv) … load until the last is
audible`). The same file's `05i-records (iv)` lines split each instance's time into prepare and restore (e.g. Linux AQ10
96 kHz 8 inst: prepare [312 396 423 395 428 409 404 407] ms, restore [161 172 173 176 181 174 190 177] ms, L222). That is
a prepare/restore split, not a synthesis/solve split.

**(b) Time until audible and time until the final tail settled, 100 m** (`07c1-records (h) load`, the 100 m cube with
uniform α for a target T60 and s 0.3, `test_diffuse_records.cpp` L2144–2157, L2235–2292). 1/4/8 instances exist only
at T60 8 s (the rated corner). "Audible" = per-instance max (sum). "Settled" = provisional → exact, all instances.

| fs | inst | key | Linux audible max (sum) / settled ms | macOS | Windows |
|---|---|---|---|---|---|
| 48000 | 1 | keyless | 248 (248) / 954 | 262 (262) / 1003 | 256 (256) / 856 |
| 48000 | 1 | keyed | 169 (169) / 912 | 141 (141) / 831 | 176 (176) / 903 |
| 48000 | 4 | keyless | 598 (1659) / 2707 | 542 (1418) / 2525 | 526 (1652) / 2573 |
| 48000 | 4 | keyed | 356 (1051) / 2622 | 347 (862) / 2613 | 621 (1568) / 2496 |
| 48000 | 8 | keyless | 636 (4115) / 5183 | 665 (3922) / 5131 | 642 (3894) / 4821 |
| 48000 | 8 | keyed | 727 (3786) / 5325 | 704 (3282) / 5986 | 790 (3656) / 4946 |
| 96000 | 1 | keyless | 472 (472) / 2076 | 390 (390) / 2198 | 454 (454) / 1846 |
| 96000 | 1 | keyed | 470 (470) / 1991 | 372 (372) / 2475 | 457 (457) / 1853 |
| 96000 | 4 | keyless | 1476 (3378) / 5935 | 955 (2470) / 7253 | 1094 (3253) / 5229 |
| 96000 | 4 | keyed | 1155 (3186) / 5958 | 944 (2449) / 6964 | 1252 (3116) / 5114 |
| 96000 | 8 | keyless | 1524 (8996) / 12009 | 1930 (8394) / 12813 | 1357 (7703) / 9945 |
| 96000 | 8 | keyed | 1764 (8965) / 12087 | 1730 (9019) / 13323 | 1244 (7729) / 9726 |

Sources: `phase-07c-1/44` Linux L282–293, macOS L504–515, Windows L830–841. L_p 3.70 s / L 11.93 s on every row. The
96 kHz 8-instance rows print "FLAG: 8-instance load over 5 s".

**AQ10 room, time until the final tail settled: not on file.** The (h) test runs only the 100 m cube. The (iv) test
measures "audible" only.

**Synthesis vs solve split: not printed for any load.** The nearest components on file for run 43291051799:
- synthesis, one emitter (`07c1-records provisional cost`, constructor + make), T60 8 s full tail 12.00 s: 48 kHz
  Linux 634 / macOS 490 / Windows 494 ms; 96 kHz 1431 / 1203 / 1144 ms (`phase-07c-1/44` L120, L123; L473, L476;
  L894, L897);
- solve: low-α GATE solveMedianMs 91.7 / 90.8 / 90.1 ms (F1). The 100 m T60-8 s cube's solve is not printed;
- restore at 96 kHz, keyless (stage-1 solve + interim) vs keyed (no solve), medians (`phase-07c-1/44` L49–50, 60–61,
  568–569, 579–580, 748–749, 759–760):

| scene | Linux keyless / keyed median | macOS | Windows |
|---|---|---|---|
| flutter | 706 / 593 | 510 / 380 | 644 / 518 |
| low-α s0.3 | 1718 / 1814 | 2572 / 2292 | 1570 / 1562 |

## F7 — bounce decomposition (36 rebuilds, 3 minutes)

**Not printed.** The bounce prints only wall time and the ratio (`test_diffuse_records.cpp` L974–1027). Scene:
`cube100_lowalpha0.05_s0.3`, offline pipeline, room W/D/H stepping 100 → 64 m (1 m every 5 s, 36 steps). The offline
branch solves and then synthesises in series per rebuild (`ScenePipeline.cpp` L478–484: `solveStage` then `finishExact`).

Records, run 43291051799 (`phase-07c-1/44` L141–144, L598–601, L864–867):

| OS | 48 kHz wall / ratio | 96 kHz wall / ratio |
|---|---|---|
| Linux | 53.8 s / 0.30 × | 194.6 s / 1.08 × |
| macOS | 43.3 s / 0.24 × | 148.1 s / 0.82 × |
| Windows | 50.3 s / 0.28 × | 197.3 s / 1.10 × |

Other runs on file, 48 / 96 kHz ratio: 43031773338 Linux 0.32 / 1.30, macOS 0.29 / 0.84, Windows 0.42 / 1.36
(`phase-05i/19` L245–246, 407–408, 549–550); 43215018040 Linux 0.31 / 1.33, macOS 0.27 / 0.85 (`phase-07c-1/19`
L25–26, 472–473); 43227272415 Windows 0.30 / 1.09 (`/20` L191–192); 43242209571 0.22 / 1.12, 0.23 / 0.76, 0.33 / 1.24
(`/41` L182–185, 441–444, 622–625); 43258505284 0.29 / 1.17, 0.28 / 0.83, 0.33 / 1.13 (`/42` L27–30, 484–487,
867–870). **The range over these runs is 0.22–0.42 × at 48 kHz and 0.76–1.36 × at 96 kHz.**

**Solve share (*derived*).** Assumptions: (1) each rebuild's solve costs that run's low-α GATE solveMedianMs. Every
rebuild is a 99–64 m cube with α 0.05, s 0.3. Whether each is capped, i.e. realised work ≈ W_scene, is not on file.
(2) The solve does not depend on fs: `DiffuseProblem` carries no sample rate (`DiffuseEstimator.h` L62–86).
Per-rebuild wall = wall / 36. Solve share = 36 × solve / wall (with the initial restore's solve: 37 ×).

| OS | solve ms | 48 kHz per-rebuild wall | 48 kHz share (36 / 37) | 96 kHz per-rebuild wall | 96 kHz share (36 / 37) |
|---|---|---|---|---|---|
| Linux | 91.7 | 1.4944 s | 6.1361 % / 6.3065 % | 5.4056 s | 1.6964 % / 1.7435 % |
| macOS | 90.8 | 1.2028 s | 7.5492 % / 7.7589 % | 4.1139 s | 2.2072 % / 2.2685 % |
| Windows | 90.1 | 1.3972 s | 6.4485 % / 6.6276 % | 5.4806 s | 1.6440 % / 1.6897 % |

Projection per W (*derived*, assuming the solve is linear in W, which is F3's question and unmeasured):
wall(W) = wall + 36 × solve × (W/W₀ − 1).

| OS | fs | ×1 | ×2 | ×4 | ×8 | ×16 |
|---|---|---|---|---|---|---|
| Linux | 48 k | 53.8 s (0.299 ×) | 57.1 s (0.317 ×) | 63.7 s (0.354 ×) | 76.9 s (0.427 ×) | 103.3 s (0.574 ×) |
| Linux | 96 k | 194.6 s (1.081 ×) | 197.9 s (1.099 ×) | 204.5 s (1.136 ×) | 217.7 s (1.209 ×) | 244.1 s (1.356 ×) |
| macOS | 48 k | 43.3 s (0.241 ×) | 46.6 s (0.259 ×) | 53.1 s (0.295 ×) | 66.2 s (0.368 ×) | 92.3 s (0.513 ×) |
| macOS | 96 k | 148.1 s (0.823 ×) | 151.4 s (0.841 ×) | 157.9 s (0.877 ×) | 171.0 s (0.950 ×) | 197.1 s (1.095 ×) |
| Windows | 48 k | 50.3 s (0.279 ×) | 53.5 s (0.297 ×) | 60.0 s (0.334 ×) | 73.0 s (0.406 ×) | 99.0 s (0.550 ×) |
| Windows | 96 k | 197.3 s (1.096 ×) | 200.5 s (1.114 ×) | 207.0 s (1.150 ×) | 220.0 s (1.222 ×) | 246.0 s (1.366 ×) |

For comparison, the low-α full rebuild median (`05h-records full rebuild`, `phase-07c-1/44` L53–54, 572–573, 752–753)
is 48 kHz 1111 / 1171 / 964 ms and 96 kHz 2857 / 2715 / 2135 ms (Linux / macOS / Windows).

## F8 — callback p99.9 and overruns with concurrent builders (cond. 12 (c), B1-b)

Source: `docs/review/phase-07c-1b/23-s2-records-excerpt.md` (S2 runs, code 9717a58). Host buffer 64 at 48 kHz (period
1 333 µs), 10 s, real-time instance on the AQ10 room. Builders rebuild the 100 m low-α cube without pause: a listener
move on each every 50 ms means ISM, a solve at the gate and assembly over cached unit decays
(`test_diffuse_records.cpp` L1028–1043). Priority obtained: Linux "not available (errno 1 … RLIMIT_RTPRIO 0)", macOS
THREAD_TIME_CONSTRAINT_POLICY, Windows MMCSS "Pro Audio" (L10, L24, L35).

| run | OS | builders | wall p99.9 µs | wall max µs | CPU p99.9 µs | overruns > period | > period/2 | missed slots | line |
|---|---|---|---|---|---|---|---|---|---|
| 43389296112 | Linux | 0 | 493.7 | 887.0 | 494.4 | 0 | 2 | 0 | L10 |
| 43389296112 | Linux | 1 | 1204.5 | 3125.3 | 241.9 | 3 | 45 | 30 | L11 |
| 43389296112 | Linux | 2 | 1202.9 | 2834.5 | 398.6 | 1 | 47 | 14 | L12 |
| 43389296112 | Linux | 4 | 1408.5 | 2853.1 | 409.9 | 8 | 101 | 90 | L13 |
| 43389296112 | Linux | 8 | 2169.5 | 3131.0 | 382.3 | 13 | 96 | 145 | L14 |
| 43389296112 | macOS | 0 | 771.9 | 3155.1 | 774.5 | 3 | 11 | 1 | L24 |
| 43389296112 | macOS | 1 | 1690.0 | 7095.7 | 1692.8 | 10 | 26 | 13 | L25 |
| 43389296112 | macOS | 2 | 513.6 | 2204.5 | 515.0 | 2 | 5 | 2 | L26 |
| 43389296112 | macOS | 4 | 1972.2 | 3794.8 | 2048.8 | 18 | 47 | 21 | L27 |
| 43389296112 | macOS | 8 | 1943.6 | 3906.8 | 1946.7 | 19 | 48 | 13 | L28 |
| 43389296112 | Windows | 0 | 281.5 | 726.2 | 283.2 | 0 | 1 | 0 | L35 |
| 43389296112 | Windows | 1 | 158.1 | 818.2 | 159.1 | 0 | 1 | 0 | L36 |
| 43389296112 | Windows | 2 | 142.1 | 767.9 | 143.2 | 0 | 1 | 0 | L37 |
| 43389296112 | Windows | 4 | 170.1 | 771.9 | 170.4 | 0 | 1 | 0 | L38 |
| 43389296112 | Windows | 8 | 161.4 | 1037.0 | 163.2 | 0 | 1 | 0 | L39 |
| 43402114873 | Linux | 0 | 140.3 | 851.9 | 141.8 | 0 | 1 | 0 | L48 |
| 43402114873 | Linux | 1 | 1216.5 | 2545.1 | 172.6 | 3 | 55 | 11 | L49 |
| 43402114873 | Linux | 2 | 1220.6 | 2777.0 | 198.9 | 2 | 42 | 25 | L50 |
| 43402114873 | Linux | 4 | 1941.9 | 3109.4 | 206.8 | 8 | 104 | 117 | L51 |
| 43402114873 | Linux | 8 | 1479.4 | 3034.3 | 290.5 | 9 | 76 | 136 | L52 |
| 43402114873 | macOS | 0 | 1073.5 | 3789.5 | 1076.6 | 5 | 10 | 8 | L64 |
| 43402114873 | macOS | 1 | 862.0 | 1952.9 | 867.0 | 3 | 11 | 8 | L65 |
| 43402114873 | macOS | 2 | 846.7 | 2657.4 | 849.0 | 5 | 12 | 4 | L66 |
| 43402114873 | macOS | 4 | 773.3 | 1570.3 | 776.1 | 3 | 8 | 1 | L67 |
| 43402114873 | macOS | 8 | 288.0 | 887.8 | 291.4 | 0 | 1 | 0 | L68 |
| 43402114873 | Windows | 0 | 190.4 | 673.6 | 190.7 | 0 | 1 | 0 | L75 |
| 43402114873 | Windows | 1 | 149.6 | 711.8 | 149.8 | 0 | 1 | 0 | L76 |
| 43402114873 | Windows | 2 | 162.4 | 940.3 | 162.2 | 0 | 1 | 0 | L77 |
| 43402114873 | Windows | 4 | 266.1 | 919.7 | 269.1 | 0 | 1 | 0 | L78 |
| 43402114873 | Windows | 8 | 392.4 | 867.6 | 392.9 | 0 | 1 | 0 | L79 |
| 43412038058 | Linux | 0 | 129.5 | 762.3 | 130.6 | 0 | 1 | 0 | L88 |
| 43412038058 | Linux | 1 | 193.6 | 1057.0 | 168.1 | 0 | 4 | 11 | L89 |
| 43412038058 | Linux | 2 | 1097.0 | 3138.6 | 191.7 | 1 | 13 | 25 | L90 |
| 43412038058 | Linux | 4 | 1380.8 | 3057.8 | 195.4 | 11 | 63 | 103 | L91 |
| 43412038058 | Linux | 8 | 1524.1 | 3234.1 | 213.0 | 9 | 32 | 112 | L92 |
| 43412038058 | macOS | 0 | 1487.7 | 6381.5 | 1490.3 | 10 | 18 | 14 | L101 |
| 43412038058 | macOS | 1 | 662.1 | 2129.8 | 663.4 | 2 | 7 | 2 | L102 |
| 43412038058 | macOS | 2 | 345.0 | 1138.8 | 360.1 | 0 | 1 | 1 | L103 |
| 43412038058 | macOS | 4 | 970.9 | 2660.3 | 973.0 | 4 | 13 | 1 | L104 |
| 43412038058 | macOS | 8 | 1839.6 | 12899.9 | 1842.6 | 15 | 39 | 66 | L105 |
| 43412038058 | Windows | 0 | 119.2 | 799.0 | 119.7 | 0 | 1 | 0 | L115 |
| 43412038058 | Windows | 1 | 166.7 | 785.1 | 167.1 | 0 | 1 | 0 | L116 |
| 43412038058 | Windows | 2 | 164.3 | 791.0 | 163.7 | 0 | 1 | 0 | L117 |
| 43412038058 | Windows | 4 | 162.7 | 1179.9 | 161.8 | 0 | 1 | 0 | L118 |
| 43412038058 | Windows | 8 | 180.6 | 1205.1 | 181.2 | 0 | 1 | 0 | L119 |

Linux printed "RESIDUAL: overrun at 8 builders with a clean floor" on all three S2 runs (L15, L53, L93). On Linux the
wall p99.9 rises with builders while the thread-CPU p99.9 stays at 168–410 µs. On macOS the 0-builder floor itself
overruns (3, 5 and 10 overruns > period).

**Solve duration during these runs: not printed.** The B1-b lines carry no solve time. The nearest record is the same
job's low-α GATE solveMedianMs (measured separately, not during the callback run): 43389296112 Linux 62.7, macOS 63.3,
Windows 70.7 ms; 43402114873 80.8 / 84.1 / 56.1; 43412038058 98.7 / 86.9 / 71.8 (F1). The gate serialises solves
(`DiffuseSolveGate`), so at most one builder solves at a time, on the pool of `hardware_concurrency` threads.

The old instrument (`05h-records callback p99.9`), run 43291051799 Linux: 1 / 4 / 8 builders p99.9 276 / 1124 /
1145 µs (`phase-07c-1/44` L145–147). Run 43227272415 Windows: 131 / 162 / 1137 µs (`/20` L193–195).

## F9 — keyless stage-1 solve vs background final: one `DiffuseLimits`?

**Yes, one.** Every product solve path reaches `solveHybrid` (`src/sim/Engine.cpp` L364–398), which builds
`diffuse::DiffuseLimits limits;` default-constructed. Only `fixedHistories` is overridden, and only when
`options.diffuseFixedHistories > 0`, a validation option. `StagedBuild::solve(pool)` (L863–885) swaps only the pool.
`ScenePipeline::solveStage` (`src/plugin/core/ScenePipeline.cpp` L267–296) serves the synchronous keyless load and
first prepare (L445), the offline wait (L482) and the background builder's final (L537). It differs between them only in
the gate class and the abandon flag. The default is `wScene = 2 * kWMaxPerEmitterProvisional`
(`src/sim/diffuse/DiffuseEstimator.h` L90). **After a raise of `kWMaxPerEmitterProvisional`, a keyless load's stage-1
solve runs at the raised W** (W_scene = 2 × the new value), on the gate's pool, inside the synchronous restore that the
restore gate times. No separate stage-1 limit exists in the code.

**Consequence in the key** (`ScenePipeline::engineKey`, L221–233): E_prec = FNV over `limits.wScene`,
`limits.nStarMax` and `limits.seTargetDb` of the default `DiffuseLimits`. A raise changes E_prec. Every state saved
before the raise then mismatches the key (`saved->key == key`, L433). Its next load is keyless, a stage-1 solve at the
new W, and settles to the new E_b in one AQ4 step.

## F10 — state fixtures

`tests/state/`: `parameter_ids_v1.json`, `v1_default.bin` (3 290 B), `v1_modified.bin` (3 287 B), **`v2_default.bin`
(3 776 B), `v2_modified.bin` (3 773 B)**.

**Do they load keyless after an E_prec or E_model change?** Yes, and the test allows it.
`tests/unit/test_plugin_state.cpp` L341–369 loads `v1_modified.bin`, `v2_modified.bin` and `v2_default.bin`. A load
counts as keyed only if `keyedLoads` rose. Otherwise it is keyless, and `v2_modified.bin` must then show exactly one
synchronous solve (`syncSolves == s0 + 1`); `v2_default.bin` may show 0 or 1. Neither outcome fails. The test requires
only `REQUIRE_FALSE(b.stateWarning())` and that the load settles. The key compare is all five parts
(`ScenePipeline.cpp` L429–433). A change of E_prec (W_max, n*_max or SE target) or of E_model (`kEstimatorModelId`)
makes every v2 fixture load keyless, a stage-1 solve at the then-current limits, with no warning. The fixtures need no
regeneration (CLAUDE.md: regenerate only on a `pluginStateVersion` bump). The second test (L374–400) only requires
each `v*_*.bin` to load without warning and validate.

**Does a D5 regeneration force an E_model bump?**
- **Not mechanically.** Nothing links `phase05h_d5_hashes.json` to `kEstimatorModelId`: no test, no
  `tools/ci/update_goldens.py` check, and no grep hit outside the estimator header and the fingerprint test. The link
  is a rule in a comment: `DiffuseEstimator.h` L51–53, "Bump it with every D5-golden regeneration and whenever the E_b
  of a fingerprint fixture changes with DiffuseLimits unchanged".
- **The fingerprint test bites on a W raise even though the limits change.** `records: AX48 E_model fingerprint`
  (`test_diffuse_records.cpp` L2459–2507, `[.][benchmark][ax48-fingerprint]`, run in CI's benchmark step) hashes only
  the E_b of the three cubes (`ax48FingerprintHash`, L2437–2450: the levels alone; the comment "with DiffuseLimits and
  kEstimatorModelId" at L2455 is not what the hash covers). Each E_b is solved at the default `DiffuseLimits`. The test
  then requires `kEstimatorModelId == pin.modelId` (1) and `h == pin.hash`. The pins are Linux 0x22f009efe0004e82,
  macOS 0x9d4f48216097ae94, Windows 0xa70a95cd5962863b (L2471–2475). Raising W changes E_b at the capped low-α cubes
  and at the work-stopped flutter cube (F11), so this test fails until the three hashes are re-pinned. A re-pin may keep
  modelId 1 (the test compares modelId to the pin, not to the limits). The comment's convention would bump it with the
  D5 regeneration the raise also forces (AX41 per `test_diffuse_reports.cpp` L1–6). The key already changes through
  E_prec either way (F9).

## F11 — Seat 2's prefix claim, from the code

**Code facts.**
- `pilotStops(n, W_pilot, W_scene, n*_max) = n >= n*_max || 2 W_pilot >= W_scene` (`DiffuseEstimator.cpp` L390–393).
- The pilot is histories [offset, offset + n*), scanned block by block in order (L505–526).
- `pathCount`: N_cap = floor₆₄((W_scene − W_pilot) n* / W_pilot), N = min(ceil₆₄(max(N_need, n*)), N_cap)
  (L359–388). N_cap is non-decreasing in W_scene.
- The final range is `[offset + kFinalRangeStart, … + N)` with `kFinalRangeStart` = 8 000 (L547–554; `.h` L45).
- The shipped estimate is the final range's mean (or the pilot's, if `pilotShipped`; L574–580).
- History h's scores depend only on (fixed seed, end, emitter, path index, hit, attempt) (D1, `.h` L21–24), not on N or
  W.

**n*_max-stopped fixtures** (n* = 1 024, 2·W_pilot < W_scene at the current pin): classroom, club, concert_hall_box,
dead_booth, large_hall, living_room, open_field, small_room, stone_box; cube100_lowalpha0.05_s0.3,
cube100_lowalpha0.05_s1, W1. At any larger W_scene, 2·W_pilot < W_scene still holds, so the pilot stops at the same
block with the same n*, W_pilot and N_need. Only N_cap grows. N(W') ≥ N(W), and the final range at the current W is
**an exact prefix** of the larger-W final range (same start 8 000, same per-history scores). For uncapped fixtures
(N = ceil₆₄(max(N_need, n*)) < N_cap) the range is **identical** (N unchanged). Only capped fixtures (open_field, the
two low-α cubes) get a longer range. The D5 hash changes for capped fixtures through the final blocks and `count.n`
(L562–572), not through the pilot.

**Work-stopped fixtures** (2·W_pilot ≥ W_scene at the current pin): asymmetric_materials (n* 256), medium_room
(n* 256), edge_values (n* 64, pilot shipped), cube100_flutter_fallback (n* 320); in the reported set every layout4_s1
row (n* 256–640) and layout5_s1/emitter_wall (n* 512) (`phase-05h/13` L10–19). At a larger W_scene the stop test
passes later: n* and W_pilot grow (up to n*_max) and N_need is re-estimated from a longer pilot. The final range still
starts at 8 000, so one range is an index prefix of the other. But N' = min(ceil₆₄(max(N_need', n*')), N_cap') is not
guaranteed ≥ N. With a different N_need', a capped fixture can come out shorter as well as longer. For edge_values the
current estimate is the **pilot** ([0, 64)). Once N_cap ≥ 64 the final range ships instead, so the current estimate is
**not** a prefix of the larger-W one. The VOV_union (first 8 000 of pilot then final, L582–599) changes with n*.

**Answer.** The prefix claim holds exactly where the pilot stopped at n*_max (identical when uncapped, prefix when
capped). It does not hold as stated for the work-stopped fixtures, which include the gated flutter cube, three D5
fixtures and most of the layout 4/5 reported set.

## F13 — `listed` on the macOS `cube100_lowalpha0.05_s0.3` row of `kGateRegister`

Field order (`test_diffuse_records.cpp` L93–120): scene, os, recorded14xS, baselineMedianMs, baselineRatio,
flutterRefMs, ratioAssertable, **listed**, strict30s, solveRefMs, solveRefRuns, s2.

| ref | line | row | `listed` |
|---|---|---|---|
| `origin/main` (976659c, 2026-11-13) | L166 | `{"cube100_lowalpha0.05_s0.3", "macOS", 33.40, 1817.0, 3.75, 484.0, false, false, false, 83.7, 1,` | **false** |
| HEAD (5f2fd24; carrier commit 5b65864) | L169 | `{"cube100_lowalpha0.05_s0.3", "macOS", 33.40, 1817.0, 3.75, 484.0, false, true, false, 83.7, 1,` | **true** |

5b65864 changes only that field (false → true) and adds the three-line comment L164–166 (PR #33 run 43427854710,
14 × worst 30.50 s; recorded 33.40 s kept; print only).

---

## Missing (not on file)

- F1: nsPerEval and solveMedianMs of run 43427854710; Windows of 43215018040; Linux and macOS of 43227272415.
- F2: one-thread solve medians for any 07c-era run (only 05h run 42846229834, estimator c309589).
- F5: the pilot stop reason (derived here from the stop test); W2's diffuse n*, N_need, N_cap and cap hit (whether W2
  binds AX41's cap); the AQ10 W1/W2 benchmark lines of any run after phase 05h.
- F6: the (iv) and (h) lines of the S2 runs; final-settled time for the AQ10 room; any synthesis/solve split of a load.
- F7: any per-rebuild solve time in the bounce; whether the 99–64 m bounce rooms are capped.
- F8: solve durations during the B1-b runs.
