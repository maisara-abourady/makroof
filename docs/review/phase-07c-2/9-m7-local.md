# Phase 07c-2: M7 and M7b, local records (Linux, 4-thread pool)

Requested by the decider in `8-decider-rebuttal-r2.md` §6 ("Measurements"). Context: `6-interrogator-on-file5.md`,
ledger row C-1. These are **records only**: nothing is asserted, and no shipped behaviour or constant changes.
The CI three-OS print comes from the Release benchmark step. The test is tagged `[.][benchmark][m7-hold]`, and the
job summary picks up the lines `07c2-m7 ` and `07c2-m7b `.

- Box: this session's Linux container, `nproc` = 4. The gate pool is as shipped (`hardware_concurrency`, 4 threads).
  The build is Release (`build/release`, `-DSPATIAL_BUILD_PLUGIN=OFF`).
- Test: `tests/unit/test_m7_hold.cpp`. Run: `build/release/tests/unit/spatial_tests "[m7-hold]"`. It took 2 min 4 s,
  2 min 10 s and 2 min 17 s on the three runs.
- Three local runs, numbered 2, 3 and 4. Run 1 was thrown away: it had a test bug. Its step of 0.05 normalised units clamped the listener at the room's inner edge, so later edits left the scene unchanged and nothing was submitted. The random offsets are seeded (`0x07C20007` + case index), so all three runs use the same offsets.

## Method

**Seam (validation only).** `ScenePipeline::setDiffuseLimitsForTest(const sim::diffuse::DiffuseLimits&)` sits
beside `setPlatformTagForTest`. It stores an optional override under `stateMutex_`. `decide()` copies the override
into its snapshot. `planStage()` passes it on through a new validation-only `sim::BuildOptions::diffuseLimitsOverride`
(a pointer that is `nullptr` in every product path). `Engine.cpp` then uses `*override` instead of
`diffuse::DiffuseLimits{}`, and the existing `diffuseFixedHistories` still applies on top.
- Default: no override, pointer `nullptr`. The shipped code path is unchanged.
- `ScenePipeline::diffuseLimits()` returns the limits the solve uses.
- The test `"ScenePipeline: the M7 diffuse-limits seam defaults to the shipped DiffuseLimits"` (`[pipeline][m7-seam]`)
  asserts that the default equals `DiffuseLimits{}` field by field, with `wScene = 2 kWMaxPerEmitterProvisional`,
  `nStarMax = kNStarMax` and `seTargetDb = kSeTargetDb`.
- `engineKey()` (the AX48 key) still hashes the shipped limits.
- Nothing in `src/plugin` calls the setter.

**Cases.** m ∈ {1, 4, 5, 6, 8} sets `W_scene = 2 × m × kWMaxPerEmitterProvisional`. Everything else of the shipping
rule is unchanged (n\*_max, SE target, pilot, joint rule). The run uses one instance at 48 kHz on two scenes, built
as `test_diffuse_wsweep.cpp` builds them:
- `layout4_s1/listener_corner`: 20 × 30 × 10 m, absorbing floor, s = 1, listener (0.1, 0.1, 9.9).
- `cube100_lowalpha0.05_s1`.

For each case the pipeline is set up with `prepare(48 kHz, 256)` and a restore, and the test waits for it to settle.
While it runs, a host-audio thread calls `process()` with 256-sample blocks at real-time pace, so the engine installs
every submitted IrSet as a host would.

**Edit.** Each edit is `setParameter(kListenerY, …)` and moves the listener by 0.001 normalised units, which is 3 cm
in the layout and 10 cm in the cube. Every edit is therefore a new diffuse problem and is never clamped.

**Hold.** The hold runs from just before `setParameter` to the moment the engine holds the first IrSet built from a
snapshot that contains the edit. That IrSet is the next decision's interim, carrying the new ISM early part (condition 4).
- The test hooks track it. `setAfterSnapshotHook` counts decisions. The stage hook records the Solve start, the end
  of the solve (the first Assemble after Solve), and the next decision's Commit.
- The test then polls `lastSubmittedIrSet()` until it changes. That pointer is set right after
  `engine_.submitIrSet`, under `stateMutex_`.
- The audio thread swaps the IrSet in at its next block, which adds at most one block (5.3 ms). This is not counted.

**Idle baseline (10 edits per case).** Each edit is made with the builder idle and the scene settled. Each of these
edits runs one undisturbed solve, and that solve gives the solve duration D (stage hook: Solve to the next Assemble).

**Mid-solve (10 edits per case).** The edit lands at `u × D_median` after the Solve start of the running solve, with
u ~ U[0, 1) seeded. The running solve belongs to the previous edit, so each trial's edit starts the next trial's
running solve. If the solve had already ended when the edit landed, the edit is counted as "landed after the solve
ended" (D varies around D_median). It is kept: it is a real edit during the running decision (after the L539 check).

**Statistics.** Median, p95 by nearest rank (with n = 10 it is the worst) and worst, per case. The table below takes
the worst over the 3 runs.

**M7b (hypothetical cancel-on-edit, not implemented).** Under the rule, an edit cancels the running solve. A solve
therefore completes only if no edit arrives between its edit and the end of its solve. With periodic edits at
interval T, the fraction of solves that complete is the fraction of measured C < T. C is the time from the edit to
the end of its solve, so C = plan + interim (ISM update) + gate entry + solve, measured on the 10 idle position edits
of each case. After the solve, finishExact and makeIrSet still run. The rule as stated cancels only the solve, so they
are left out of C.
- T = 5 s is the room size stepping 1 m every 5 s.
- T = 100 ms is continuous automation, an edit every 100 ms.
- For the room-size pattern, 2 room-size edits (`kRoomD` ± 1 m: grown in the layout, shrunk in the cube) are also
  measured per case at m = 6 and 8.
- The 05i joint step pattern (AX38 (iv)) is **not** covered here.
- The scenes are W-capped. The solve cost is therefore set mainly by W_scene, and the position-edit C is a fair stand-in
  for other edits. The room-size samples confirm this.

## Results: M7, worst over 3 local runs (ms)

| scene | m | solve D median (runs 2/3/4) | worst solve | idle-edit hold median (2/3/4) | idle worst | mid-solve hold median (2/3/4) | mid-solve p95 = worst, worst of 3 runs | landed after the solve ended (2/3/4) |
|---|---|---|---|---|---|---|---|---|
| layout4_s1/listener_corner | 1 | 105 / 113 / 123 | 143 | 30 / 32 / 31 | 37 | 90 / 73 / 84 | **177** | 0 / 0 / 0 |
| layout4_s1/listener_corner | 4 | 347 / 420 / 472 | 583 | 30 / 34 / 41 | 52 | 302 / 331 / 400 | **517** | 0 / 0 / 0 |
| layout4_s1/listener_corner | 5 | 426 / 505 / 555 | 637 | 30 / 30 / 38 | 81 | 230 / 236 / 327 | **559** | 0 / 1 / 0 |
| layout4_s1/listener_corner | 6 | 514 / 589 / 757 | 858 | 30 / 32 / 48 | 52 | 221 / 311 / 312 | **705** | 0 / 0 / 0 |
| layout4_s1/listener_corner | 8 | 721 / 758 / 814 | 910 | 32 / 31 / 32 | 51 | 379 / 447 / 417 | **768** | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 1 | 98 / 105 / 103 | 114 | 74 / 79 / 80 | 113 | 121 / 154 / 137 | **215** | 0 / 0 / 1 |
| cube100_lowalpha0.05_s1 | 4 | 320 / 334 / 337 | 412 | 73 / 73 / 77 | 107 | 273 / 218 / 247 | **377** | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 5 | 404 / 438 / 416 | 535 | 68 / 74 / 74 | 106 | 351 / 358 / 356 | **540** | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 6 | 497 / 538 / 503 | 650 | 77 / 82 / 83 | 108 | 406 / 345 / 343 | **605** | 2 / 2 / 1 |
| cube100_lowalpha0.05_s1 | 8 | 787 / 714 / 646 | 907 | 79 / 85 / 74 | 115 | 262 / 284 / 356 | **730** | 1 / 1 / 0 |

Reading:
- **The hold of an edit during a running solve is the rest of that solve plus the next decision's plan and interim.**
  This agrees with C-1. In every trial the previous decision was discarded at the L539 check ("discarded +1" in the
  trial lines).
- **The worst hold is the solve duration plus the idle hold**, reached when an edit lands just after the Solve
  starts:
  - m = 1: 177 ms (layout) and 215 ms (cube).
  - m = 6: 705 ms and 605 ms.
  - m = 8: 768 ms and 730 ms.
- **The baseline hold with the builder idle does not depend on m.** It is about 30–50 ms in the layout and about
  70–115 ms in the cube (the interim of a long 100 m IR).
- **The solve duration grows about linearly with m.** On this box the median at m = 8 is 646–814 ms, and the worst
  single solve is 907–910 ms.
- So on this box the window is not empty at any m. Even at m = 1, a position edit that arrives during a solve waits
  up to about 100–150 ms more than one made with the builder idle.

## Results: M7b (hypothetical cancel-on-edit)

| scene | m | C = edit → solve end, median / worst (position edits, runs 3 and 4) | room-size C, median / worst (runs 3 and 4) | complete at T = 5 s | complete at T = 100 ms |
|---|---|---|---|---|---|
| layout4_s1/listener_corner | 6 | 626 / 711; 800 / 906 | 563 / 589; 759 / 832 | 100 % | **0 %** |
| layout4_s1/listener_corner | 8 | 788 / 863; 853 / 944 | 764 / 765; 922 / 961 | 100 % | **0 %** |
| cube100_lowalpha0.05_s1 | 6 | 622 / 716; 580 / 676 | 575 / 604; 553 / 565 | 100 % | **0 %** |
| cube100_lowalpha0.05_s1 | 8 | 807 / 929; 724 / 863 | 566 / 572; 627 / 653 | 100 % | **0 %** |

**The fractions are the same in every run (run 2 too) and at every m printed, m = 1 included.** At m = 1, C is
144–186 ms, more than 100 ms.
- Room size stepping every 5 s: every solve completes.
- Continuous automation every 100 ms: no solve completes under cancel-on-edit, at any m.
- Without the rule, the shipped "never mid-drag" discard has the same outcome. A solve is adopted only once the
  parameters hold still, so continuous automation never adopts one either. Cancel-on-edit would change the hold
  (M7), not the starvation.

## Raw lines

Summary lines, runs 2, 3 and 4:

```
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 104.9 p95 126.3 worst 126.3 ms | idle-edit hold n=10 median 29.9 p95 30.9 worst 30.9 ms | mid-solve hold n=10 median 89.8 p95 131.6 worst 131.6 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 346.8 p95 394.4 worst 394.4 ms | idle-edit hold n=10 median 30.4 p95 32.6 worst 32.6 ms | mid-solve hold n=10 median 301.7 p95 472.8 worst 472.8 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 426.1 p95 482.2 worst 482.2 ms | idle-edit hold n=10 median 30.1 p95 81.3 worst 81.3 ms | mid-solve hold n=10 median 230.1 p95 434.6 worst 434.6 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 513.7 p95 543.3 worst 543.3 ms | idle-edit hold n=10 median 30.4 p95 36.0 worst 36.0 ms | mid-solve hold n=10 median 221.3 p95 572.0 worst 572.0 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 721.2 p95 764.3 worst 764.3 ms | idle-edit hold n=10 median 31.7 p95 50.9 worst 50.9 ms | mid-solve hold n=10 median 378.9 p95 679.5 worst 679.5 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 98.1 p95 114.4 worst 114.4 ms | idle-edit hold n=10 median 73.8 p95 84.7 worst 84.7 ms | mid-solve hold n=10 median 120.8 p95 170.8 worst 170.8 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 320.3 p95 406.6 worst 406.6 ms | idle-edit hold n=10 median 73.2 p95 106.9 worst 106.9 ms | mid-solve hold n=10 median 273.1 p95 371.6 worst 371.6 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 403.6 p95 478.3 worst 478.3 ms | idle-edit hold n=10 median 68.2 p95 97.7 worst 97.7 ms | mid-solve hold n=10 median 350.6 p95 419.2 worst 419.2 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 496.9 p95 609.2 worst 609.2 ms | idle-edit hold n=10 median 76.9 p95 95.1 worst 95.1 ms | mid-solve hold n=10 median 406.0 p95 559.0 worst 559.0 ms (2 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 786.9 p95 906.9 worst 906.9 ms | idle-edit hold n=10 median 79.0 p95 103.2 worst 103.2 ms | mid-solve hold n=10 median 262.1 p95 730.2 worst 730.2 ms (1 landed after the solve ended)

07c2-m7 os=Linux scene=layout4_s1/listener_corner m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 112.8 p95 141.7 worst 141.7 ms | idle-edit hold n=10 median 32.5 p95 36.7 worst 36.7 ms | mid-solve hold n=10 median 73.0 p95 156.6 worst 156.6 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 419.7 p95 481.4 worst 481.4 ms | idle-edit hold n=10 median 33.6 p95 36.5 worst 36.5 ms | mid-solve hold n=10 median 330.8 p95 452.7 worst 452.7 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 505.3 p95 540.4 worst 540.4 ms | idle-edit hold n=10 median 30.4 p95 53.6 worst 53.6 ms | mid-solve hold n=10 median 236.4 p95 475.0 worst 475.0 ms (1 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 589.0 p95 679.0 worst 679.0 ms | idle-edit hold n=10 median 32.2 p95 52.0 worst 52.0 ms | mid-solve hold n=10 median 310.9 p95 537.1 worst 537.1 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 758.2 p95 833.6 worst 833.6 ms | idle-edit hold n=10 median 31.1 p95 41.9 worst 41.9 ms | mid-solve hold n=10 median 447.2 p95 715.3 worst 715.3 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 104.9 p95 109.1 worst 109.1 ms | idle-edit hold n=10 median 78.6 p95 111.2 worst 111.2 ms | mid-solve hold n=10 median 154.3 p95 203.1 worst 203.1 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 333.8 p95 412.4 worst 412.4 ms | idle-edit hold n=10 median 73.0 p95 99.7 worst 99.7 ms | mid-solve hold n=10 median 218.2 p95 370.0 worst 370.0 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 437.6 p95 457.9 worst 457.9 ms | idle-edit hold n=10 median 74.1 p95 105.7 worst 105.7 ms | mid-solve hold n=10 median 357.5 p95 539.5 worst 539.5 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 537.5 p95 649.9 worst 649.9 ms | idle-edit hold n=10 median 82.1 p95 107.8 worst 107.8 ms | mid-solve hold n=10 median 344.7 p95 604.8 worst 604.8 ms (2 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 714.2 p95 855.5 worst 855.5 ms | idle-edit hold n=10 median 84.8 p95 113.0 worst 113.0 ms | mid-solve hold n=10 median 283.9 p95 714.3 worst 714.3 ms (1 landed after the solve ended)

07c2-m7 os=Linux scene=layout4_s1/listener_corner m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 122.8 p95 143.0 worst 143.0 ms | idle-edit hold n=10 median 31.1 p95 35.6 worst 35.6 ms | mid-solve hold n=10 median 84.0 p95 176.6 worst 176.6 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 471.9 p95 583.4 worst 583.4 ms | idle-edit hold n=10 median 41.3 p95 52.5 worst 52.5 ms | mid-solve hold n=10 median 399.6 p95 517.3 worst 517.3 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 555.0 p95 637.2 worst 637.2 ms | idle-edit hold n=10 median 37.5 p95 48.2 worst 48.2 ms | mid-solve hold n=10 median 326.6 p95 559.0 worst 559.0 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 757.1 p95 857.7 worst 857.7 ms | idle-edit hold n=10 median 48.4 p95 50.8 worst 50.8 ms | mid-solve hold n=10 median 311.9 p95 705.1 worst 705.1 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=layout4_s1/listener_corner m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 814.3 p95 910.5 worst 910.5 ms | idle-edit hold n=10 median 32.0 p95 48.4 worst 48.4 ms | mid-solve hold n=10 median 417.3 p95 767.8 worst 767.8 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=1 W_max/emitter=3050000 pool=4 fs=48k | solve n=10 median 102.6 p95 111.9 worst 111.9 ms | idle-edit hold n=10 median 79.6 p95 113.4 worst 113.4 ms | mid-solve hold n=10 median 137.3 p95 215.2 worst 215.2 ms (1 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=4 W_max/emitter=12200000 pool=4 fs=48k | solve n=10 median 337.3 p95 358.7 worst 358.7 ms | idle-edit hold n=10 median 76.7 p95 95.4 worst 95.4 ms | mid-solve hold n=10 median 247.1 p95 377.0 worst 377.0 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=5 W_max/emitter=15250000 pool=4 fs=48k | solve n=10 median 415.6 p95 534.7 worst 534.7 ms | idle-edit hold n=10 median 74.1 p95 100.9 worst 100.9 ms | mid-solve hold n=10 median 356.4 p95 492.2 worst 492.2 ms (0 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=6 W_max/emitter=18300000 pool=4 fs=48k | solve n=10 median 503.4 p95 569.6 worst 569.6 ms | idle-edit hold n=10 median 83.2 p95 106.9 worst 106.9 ms | mid-solve hold n=10 median 343.1 p95 554.0 worst 554.0 ms (1 landed after the solve ended)
07c2-m7 os=Linux scene=cube100_lowalpha0.05_s1 m=8 W_max/emitter=24400000 pool=4 fs=48k | solve n=10 median 645.8 p95 792.3 worst 792.3 ms | idle-edit hold n=10 median 74.4 p95 114.7 worst 114.7 ms | mid-solve hold n=10 median 355.9 p95 661.2 worst 661.2 ms (0 landed after the solve ended)
```

M7b lines, run 3 (all m; room-size part at m = 6, 8):

```
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=1 cancel-on-edit (hypothetical): edit->solve end median 143.8 worst 177.6 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=4 cancel-on-edit (hypothetical): edit->solve end median 452.6 worst 516.8 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=5 cancel-on-edit (hypothetical): edit->solve end median 535.4 worst 593.4 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=6 cancel-on-edit (hypothetical): edit->solve end median 626.2 worst 710.6 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 563.4 worst 588.8 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=8 cancel-on-edit (hypothetical): edit->solve end median 788.2 worst 863.0 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 763.7 worst 765.1 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=1 cancel-on-edit (hypothetical): edit->solve end median 184.6 worst 207.7 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=4 cancel-on-edit (hypothetical): edit->solve end median 409.4 worst 511.8 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=5 cancel-on-edit (hypothetical): edit->solve end median 511.4 worst 562.9 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=6 cancel-on-edit (hypothetical): edit->solve end median 622.0 worst 716.0 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 575.4 worst 604.0 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=8 cancel-on-edit (hypothetical): edit->solve end median 806.6 worst 928.5 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 565.8 worst 572.1 ms; every 5 s 100%, every 100 ms 0%
```

M7b lines, run 4:

```
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=1 cancel-on-edit (hypothetical): edit->solve end median 152.6 worst 177.8 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=4 cancel-on-edit (hypothetical): edit->solve end median 512.7 worst 613.0 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=5 cancel-on-edit (hypothetical): edit->solve end median 590.9 worst 673.7 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=6 cancel-on-edit (hypothetical): edit->solve end median 800.1 worst 905.7 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 759.4 worst 832.2 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=layout4_s1/listener_corner m=8 cancel-on-edit (hypothetical): edit->solve end median 853.4 worst 944.1 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 922.0 worst 961.1 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=1 cancel-on-edit (hypothetical): edit->solve end median 186.0 worst 214.1 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=4 cancel-on-edit (hypothetical): edit->solve end median 411.9 worst 434.0 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=5 cancel-on-edit (hypothetical): edit->solve end median 486.9 worst 635.6 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=6 cancel-on-edit (hypothetical): edit->solve end median 580.1 worst 675.9 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 552.9 worst 565.2 ms; every 5 s 100%, every 100 ms 0%
07c2-m7b os=Linux scene=cube100_lowalpha0.05_s1 m=8 cancel-on-edit (hypothetical): edit->solve end median 723.5 worst 863.1 ms (n=10 position edits); solves completing before the next edit: every 5 s 100%, every 100 ms 0% | room size +-1 m (n=2): edit->solve end median 626.7 worst 652.8 ms; every 5 s 100%, every 100 ms 0%
```

Per-edit lines, run 4, m = 8 (both scenes):

```
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 0 at 461.6 ms into the solve (u=0.567 of D_med 814.3 ms): hold 420.1 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 1 at 576.3 ms into the solve (u=0.707 of D_med 814.3 ms): hold 221.2 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 2 at 286.8 ms into the solve (u=0.348 of D_med 814.3 ms): hold 502.3 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 3 at 390.7 ms into the solve (u=0.477 of D_med 814.3 ms): hold 414.4 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 4 at 517.8 ms into the solve (u=0.633 of D_med 814.3 ms): hold 308.0 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 5 at 233.0 ms into the solve (u=0.286 of D_med 814.3 ms): hold 532.1 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 6 at 143.0 ms into the solve (u=0.175 of D_med 814.3 ms): hold 767.8 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 7 at 564.6 ms into the solve (u=0.693 of D_med 814.3 ms): hold 278.0 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 8 at 112.9 ms into the solve (u=0.139 of D_med 814.3 ms): hold 689.0 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=layout4_s1/listener_corner m=8 edit 9 at 504.4 ms into the solve (u=0.619 of D_med 814.3 ms): hold 278.9 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 0 at 588.3 ms into the solve (u=0.911 of D_med 645.8 ms): hold 252.3 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 1 at 85.5 ms into the solve (u=0.126 of D_med 645.8 ms): hold 661.2 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 2 at 315.7 ms into the solve (u=0.483 of D_med 645.8 ms): hold 409.9 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 3 at 380.6 ms into the solve (u=0.589 of D_med 645.8 ms): hold 337.0 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 4 at 577.2 ms into the solve (u=0.893 of D_med 645.8 ms): hold 75.8 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 5 at 466.5 ms into the solve (u=0.721 of D_med 645.8 ms): hold 137.1 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 6 at 11.5 ms into the solve (u=0.018 of D_med 645.8 ms): hold 572.9 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 7 at 181.3 ms into the solve (u=0.274 of D_med 645.8 ms): hold 506.0 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 8 at 258.2 ms into the solve (u=0.400 of D_med 645.8 ms): hold 363.2 ms [decisions +1, interim +1, final +0, discarded +1]
07c2-m7trial os=Linux scene=cube100_lowalpha0.05_s1 m=8 edit 9 at 301.3 ms into the solve (u=0.466 of D_med 645.8 ms): hold 348.7 ms [decisions +1, interim +1, final +0, discarded +1]
```
