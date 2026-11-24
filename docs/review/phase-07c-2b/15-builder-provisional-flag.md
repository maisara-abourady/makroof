# 15: Builder, L4-P (`render_cli --provisional-ir`): implementation and measurements

Implements decider file 10 Part A **DECISION L4-P** as corrected by interrogator file 13 (r5, tests 3 and 8) and
with Seat 5's conditions (file 14). Computation only; no decision is taken here. Code commit: **e4c34ac**.
Nothing in `src/sim` changed except the `assembleProvisional()` comment (Engine.h L295–298). No scene-specific
logic (NFR-8). Not contradictory or impossible in the code.

## What changed
| file | change |
|---|---|
| `src/cli/Cli.cpp` | three options, refusals r1–r5, `buildProvisional()`, `writeProvisionalTiming()`, help text; `renderRealtime()` takes its step sample from `--provisional-handover-sample` when given (the `--abx-step-db` request path, unchanged otherwise) |
| `src/sim/Engine.h` L295–298 | comment: "Offline renders never call it, and render_cli calls it only under `--provisional-ir`" |
| `tests/unit/test_cli_provisional.cpp` (+ `tests/unit/CMakeLists.txt`) | test 7 (`[pipeline]`), test 3 (C++ half), r1 in-process |
| `tools/ci/test_provisional_flag.py` | tests 1, 2, 3, 4, 5, 6, 8 and the L4 scene's timing check |

## Flag semantics
- **`--provisional-ir`** (validation only; off by default). render_cli plans the scene once
  (`StagedBuild::plan`), then follows ScenePipeline's keyless-load sequence:
  1. `solve()`;
  2. `useUnitDecays(nullptr)`;
  3. `useDiffuseLevel(the solve's level)`;
  4. `assembleProvisional()`.

  Every output of the run uses that IR: `--ir`, and `--out` with `--in`, both offline and under
  `--realtime-emulation`. stdout prints "provisional tail, validation-only flag" together with t_mix,e,max,
  T60_max, L_f, L_p and L.
- **`--provisional-timing <json>`** (needs `--provisional-ir`). It writes:
  - `validationOnly`, `provisional`, `mixMaxS`, `t60MaxS`, `fadeStartS` (L_f), `endS` (L_p), `exactS` (L);
  - `bandsHz`, `bandsT60S` (the T60 per band that the exact tail is built with), `t60MaxBandHz`, `sampleRate`.
- **`--provisional-handover-sample N`** (needs `--provisional-ir`). The run needs `--in`/`--out`,
  `--realtime-emulation` and an explicit fixed `--block`.
  - Both IRs come from the one plan at one level and are built before the first block: the provisional IR, then
    `useUnitDecays(nullptr)` and `assemble()` for the exact IR.
  - The render starts on the provisional IrSet and requests the exact IrSet once with `CrossfadeLaw::EqualGain`
    through `RealtimeEngine::submitIrSet`. This is the IR-publication path that `--abx-step-db` and
    `--switch-scene` already use; there is no CLI-local crossfade.
  - The request goes in at r = N − P, so the fade starts at output sample N (AX31 timing, the same as
    `--abx-step-sample`).
  - The help text says: "this shows the DSP of the handover, not its timing".
- **Refusals** (all exit 1, each naming the conflict):
  - **r1:** L_p ≥ L. This is decided from `provisionalTiming()` on the plan, before any output file
    (`--images`, `--ir`, `--out`, `--provisional-timing`) is opened. The message says that the scene is valid
    and that this is a usage error (exit 1).
  - **r2:** `--mode` absent or not `omni`.
  - **r3:** any of `--diagnostics`, `--ensemble`, `--tail-only`, `--ensemble-emitter`, `--tail-level ax16`,
    `--switch-scene`, `--switch-every`, `--abx-step-db`, `--abx-step-sample`, `--abx-stepped-ir`, `--image-cap`
    or `--automation`.
  - **r4:** `--provisional-timing` or `--provisional-handover-sample` without `--provisional-ir`.
  - **r5:** this mirrors `--abx-step-sample`. N must be a multiple of the partition and of the block, at least
    one partition, and strictly inside the input (checked once the input has been read, before any output). The
    run also needs `--realtime-emulation` and an explicit, non-random `--block`.

## The L4 scene: k and measured `provisionalTiming()`
- **Scene:** `tests/scenes/valid/stone_box.json` with every band's absorption multiplied by k, at 48 kHz.
- **Not committed as a fixture.** A new file in `tests/scenes/valid/` would join two per-fixture sets:
  - `test_tail.py::test_golden_metrics_hybrid` (`ALL_FIXTURES`), which would need a new golden;
  - every phase's listening pack.

  The tests therefore build the scene from stone_box.json and k: `K_L4` in the Python test, `kL4` in the C++
  test.
- **Measurements:**

| k | T60_max (s) | L (s) |
|---|---|---|
| 0.844 (start) | 7.957 | 11.936 |
| **0.84 (chosen)** | **7.9955** | **11.993** |
| 0.8395 | 8.0004 | 12.000 |
| 0.839 | 8.0052 | 12.000 |

  **k = 0.84** is chosen: T60_max = 8.0 ± 0.1 s with a round factor. The interrogator's 8.00 s at 0.844 left out
  air absorption at 63 Hz, which the engine includes.
- **Measured at k = 0.84:**
  - t_mix,e,max = 0.08017 s, for both emitters. K27's bound was ≥ 64.7 ms.
  - **L_f = 2.5748 s** (bound ≥ 2.561 s).
  - **L_p = 2.6748 s** (bound ≥ 2.661 s).
  - **L = 11.9933 s**.
  - provisional = true, and L_p < L.
- **T60 per band (s):**

| 63 Hz | 125 | 250 | 500 | 1 k | 2 k | 4 k | 8 k |
|---|---|---|---|---|---|---|---|
| **7.9955** | 7.8811 | 7.5837 | 7.1441 | 6.6201 | 4.8436 | 2.8955 | 1.2438 |

  **T60_max is in the 63 Hz band.**
- **IR lengths:** the provisional IR is 127 667 samples (2.66 s). The exact IR is 574 956 samples.

## Tests and evidence (Linux, this container)
- **Catch2:** `build/release/tests/unit/spatial_tests "[provisional]"` passes: 3 test cases, 31 assertions. That
  includes test 7, where the IR ScenePipeline submits at a keyless load is bit-identical to the
  `--provisional-ir --ir` WAV, with `keylessLoads` +1 and `provisionalSubmits` +1. The build is
  `cmake --preset release -DSPATIAL_BUILD_PLUGIN=OFF` with `SPATIAL_WERROR=ON`.
- **Catch2 regressions:**
  - `"[cli]"`: 14 test cases, 477 assertions, all pass.
  - `"[interim],[staged]"`: 21 test cases, 1537 assertions, all pass.
- **pytest, new file:** `RENDER_CLI=build/cli/render_cli SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci/test_provisional_flag.py`
  gives **30 passed**:
  - tests 1 and 2;
  - the L4 timing check;
  - test 3: medium_room's default `--mode omni --ir` gives the same SHA-256 run to run and with `--images` added;
    Linux SHA-256 `e3d3421110a76aef1854253cb566ee113f0fa9dde6bc934843dd25114a3b6fca`, printed per OS, not
    pinned;
  - test 4;
  - test 5: the null is −132.3 dB on both channels;
  - test 6: 20 r2/r3/r5 cases, 2 r4 cases, and r1 on the 100 m cube (α 0.05, s 0.3) with no output file left
    behind;
  - test 8: N = 47 616. Before N the output is bit-identical to the `--provisional-ir` real-time render; from
    N + ⌈0.030·fs⌉ = N + 1440 it is bit-identical to the default real-time render (block 512, P 512);
    `abx_kit.midfade_checks` passes on 76 windows, with worst ratio 1.0000005.
- **pytest, all of `tools/ci`:** with `RENDER_CLI` set and `SPATIAL_REQUIRE_RENDER_CLI=1`, 184 tests pass. This
  is after the fingerprint test (`test_ci_fingerprint`) was fixed: the guard no longer names `CLAUDE.md` and
  allows `*.md` prose instead.
- **Default output, goldens unchanged:** `pytest tools/acoustics/tests/test_render_cli.py tools/acoustics/tests/test_tail.py -k "golden or render_cli"`
  gives 77 passed.
- **Repository checks:** `python tools/ci/check_boundaries.py` reports OK, and `tools/ci/check_format.sh` reports
  116 files clean.

## Notes for the orchestrator
- **Test 2's allow-list.** Beyond file 10's list, it allows:
  - Markdown files and `tests/unit/` (the flag's own tests);
  - in `src/sim/Engine.h`, comment lines only. That file names the flag because of file 10's mandated comment.
- **`tools/ci/listening_pack.py` and `tools/ci/abx_kit.py`** were not touched here. They hold the L4 demo render
  and the stimuli. The demo needs `--block` given explicitly when it uses `--provisional-handover-sample`.
- **Not run here:** macOS and Windows. They are covered by CI on the PR. Test 3 is per OS by construction.
