# Phase 07c-2 scope 11: D-W3 (H-2c) implemented — the ISM never waits behind the solve

Spec: `docs/phases/phase-07c-2.md` scope 11 and its automated acceptance criterion. Background: decider files 13
(H-2c items 1–8), 15 (item 3 replaced, item 4 aligned), interrogator file 16 (the orchestrator's application:
adoption iff `dirty_` is unchanged since the generation read before the snapshot; the per-generation token compares
against that same value) and Seat 5's six H-2 conditions (file 10-seat5 §6). Local box: Linux container, `nproc` = 4.

## Design

**Item 1, the solve off the builder thread.** `DiffuseSolveGate` (the process-wide AX38 (i) gate, which already owned
the AX39 pool) now also owns the process-wide **solve executor**: `kExecutorThreads` = 2 threads, started with the
first task, joined with the last pipeline (the gate's existing lifetime: never in a static destructor). It runs
`DiffuseSolveGate::Task`s FIFO. There is no thread per instance: any number of pipelines share the two threads. Two
threads, not one, so that a superseded solve unwinding to its stop point (or one pipeline's post-solve assembly) does
not delay the next solve's gate entry.

- The realtime builder's solve becomes a `ScenePipeline::SolveJob` task. Its input is immutable: the planned
  `sim::StagedBuild` (the `DiffuseProblem` after image-source planning; E_prec in its limits, E_model in the
  estimator), the generation read before the snapshot, the scene, the unit-decay cache pointer and a copy of the stage
  hook. The task enters the gate in the **Builder** class exactly as before (AX38 (i): the gate is held around the
  solve only, the RAII `Scope` releases it on every exit), solves, and then, outside the gate, assembles the exact
  final (`finishExact`, now a static helper shared with the inline paths) and builds its IrSet.
- Its result goes into the task itself (`std::optional<Built> result`), which is shared-owned by the pipeline and
  the executor queue: that is the mailbox. The task sets `ready` (release) after writing it, then raises the
  pipeline's `mailbox_` flag and wakes the builder.
- **The builder is the only committer.** At the start of each builder decision it reaps a ready task and calls the
  unchanged `ScenePipeline::commit` ("The deciding thread is the only committer"). The task touches no committed
  state: it reads `dirty_` and the engine's constant IrSet parameters, and counts its solve under `stateMutex_`.
- **Pool `hardware_concurrency − 1` while the builder works alongside.** `sim::diffuse::ThreadPool::setShareLimit`
  (new, output-neutral) sets how many threads take shares. The gate sets it on every entry: `size() − 1` (at least 1)
  for a Builder-class solve, and the full pool for Synchronous and Offline solves, which do not run beside a builder.
  The estimator's pilot batch now uses `pool.shareThreads()` instead of `pool.size()`. D4 makes the result
  independent of both (the stop test is per block). The test "diffuse estimate is independent of the pool's share
  limit" covers it, including a pilot that stops mid-batch. So the change is not invasive and changes no shipped
  number. Its cost: a builder-class solve runs on 3 of 4 threads here, about 4/3 of its H-0 duration (M7 table
  below).

**Item 2, the builder never waits.** In `ScenePipeline::decide` (Builder source) the condition 4 B1′ branch is
unchanged: the edit's interim is built and committed at once, and the first mid-drag check (L543 in file 16's
numbering) still discards when `dirty_` moved during the ISM build. Then, where a solve is needed, the builder posts the
task and returns instead of solving. `hasWork()` no longer counts a generation whose task is in flight
(`inflightGen_`). The builder wakes on a new generation or on the mailbox. `settling()` and `builderIdle()` include an
in-flight task.

**Item 3, final adoption.** A ready task is adopted only if its token was never set, it has a result, and `dirty_`
equals the generation its decision read before the scene snapshot. Otherwise it is discarded and counted in
`discardedMidDrag`, once per task. Edits that do not bump `dirty_` today still do not. The second mid-drag check (after
the solve) now runs inside the task before the assembly, and the reap re-checks the same value. Adoption is the
ordinary commit, one AQ4 step. Finals are bit-identical to an uncancelled one-shot solve: the task runs the same
staged build (the stages-on-different-threads bit-identity is condition 12's existing test), and D4 covers the share
limit.

**Item 4, the per-generation cancel token.** `SolveJob::cancel` is an `std::atomic<bool>` per task, separate from
`builderAbandon_`, which is still the builder's own quiesce/restart flag. A builder decision that reads a generation
other than the in-flight task's sets the token first, before it plans (lock-free store, then `gate.notifyWaiters()`).
The token is the planned build's cancel flag for every stage after the hand-off (`StagedBuild::setCancel`, new,
output-neutral), the gate's abandon flag for the task's wait, and the IrSet build's cancel. The stop points are the
estimator's existing ones: between 64-history blocks (AX39 D6). That is a fixed work count, never time (AX41). After
the solve come the assembly's existing cancel points. A cancelled solve throws `BuildCancelled` inside the estimator
and yields no level, so it never yields an E_b, and `stats().solves` does not count it. **No held-level adoption during
motion:** nothing but a final from an unchanged generation is ever committed from a task.

The token is set by the builder when it sees `dirty_` ≠ the task's generation, not by `setParameter`. The audio-thread
listener stays one `fetch_add` (Phase 07). The builder sees the change within its 1 ms idle poll (AX33 spacing applies
only if the previous decision started less than 20 ms earlier). Seat 5's (i) allows either form.

**Item 5, offline unchanged.** The Synchronous (prepare, restore) and Offline (`process()` during a bounce) paths solve
inline as before, through the same `solveStage`, with the full pool. `render_cli` and `sim::buildRoomIR` do not touch
the plugin. Shipped outputs: `setCancel` and `setShareLimit` default to the previous behaviour.

**Item 6 (lifetime), quiesce / release / restore / destructor.** `quiesceBuilder()` quiesces the builder as before.
Then `settleJobs()` sets every task's token, wakes the gate waiters, and calls `Task::orphanOrWait()`: a task not yet
started is **orphaned** (it never runs, and its `execute()` never touches the pipeline); a running one is **waited
for**. The wait is bounded by the next cancel point, as the builder's own quiesce always was. After it no task touches
the pipeline. Reaped tasks stay in `retired_` until done, so the tail of a task's `execute()` (mailbox flag, notify) can
never outlive the pipeline. `cancelBuilder()` (the offline entry, offline `reset()`) sets the token without waiting,
as condition 10 requires: no allocation, a pointer-only `jobMutex_` section. A task never holds the gate's
`shared_ptr` (the executor's join would otherwise run on its own thread).

Locks: `jobMutex_` is taken only for pointer operations and never nested with `stateMutex_`, the gate's mutex or the
builder's mutex. Nothing on the real-time path changed. `process()` takes no new lock and allocates nothing.

## Files changed

- `src/plugin/core/DiffuseSolveGate.{h,cpp}`: the executor (`Task`, `post`, `kExecutorThreads`), the builder-class
  share limit (`builderShareThreads`).
- `src/plugin/core/ScenePipeline.{h,cpp}`: `SolveJob`, `runSolveJob`, `settleJobs`, `jobsIdle`, the reap and
  supersede blocks at the top of `decide`, the hand-off in the builder branch, `finishExact` as a static helper,
  `hasWork` / `settling` / `builderIdle`, `quiesceBuilder` / `cancelBuilder`. Comments cite scope 11 items.
- `src/plugin/core/IrBuilderThread.h`: comment only.
- `src/sim/Engine.{h,cpp}`: `StagedBuild::setCancel` (the hand-off's only need in `src/sim/`).
- `src/sim/diffuse/ThreadPool.{h,cpp}`: `setShareLimit`, `shareThreads`. Workers outside the limit sit a job out.
- `src/sim/diffuse/DiffuseEstimator.cpp`: the pilot batch is `pool.shareThreads()` (one line; D4).
- Tests: `tests/unit/test_interim.cpp`, `test_diffuse_gate.cpp`, `test_diffuse.cpp`, `test_m7_hold.cpp`.

No scene-specific logic. No golden touched or regenerated. No contract change.

## Tests (new)

| test | tags | checks |
|---|---|---|
| Scope 11 (H-2c): an edit during a running solve gets its B1′ ISM update at once; the superseded solve yields no final; no adoption during motion | `[pipeline][interim][cond4][h2c]` | first solve parked inside the gate; a second edit's interim lands while it is parked; no final in motion; the parked solve discarded once; never on the builder thread; afterwards 1 solve, 1 final, 1 step, final bit-identical to `buildIr` |
| Scope 11 (H-2c): a final is bit-identical with and without cancelled predecessors (D7) | `[pipeline][interim][h2c]` | 0 vs 3 predecessors each superseded mid-solve; the finals are bit-identical to each other and to `buildIr`; the cancelled ones yield no E_b (`solves` + 1) |
| Scope 11 (H-2c) stress: edits at random solve points, quiesce and restore mid-solve, the offline switch, destroyed mid-solve (TSan) | `[pipeline][h2c][stress]` | 8 seeded iterations, an audio thread running, 4–8 edits per iteration at random points of the running solve (position and T60 edits), random release + prepare, restore, realtime reset, offline switch with offline blocks; even iterations destroy the pipeline mid-solve, odd ones settle and check the final against `buildIr` |
| Scope 11 (H-2c): a pipeline destroyed or quiesced with its solve task waiting at the gate or still queued on the executor neither hangs nor leaves the task behind | `[pipeline][gate][h2c]` | the task at the gate behind a synchronous holder; the task queued behind two blocking executor tasks (orphaned, never run); destroy and release + prepare variants |
| Gate executor: a task orphaned before it starts never runs; a running one is waited for | `[pipeline][gate][h2c]` | the `Task` state machine |
| Gate: a builder-class solve takes shares on size() − 1 threads, the other classes on all | `[pipeline][gate][h2c]` | n = 1, 2, 4 |
| diffuse estimate is independent of the pool's share limit (D4) | `[diffuse]` | limits 3, 1, 0, 9 (clamped); the pilot stopping mid-batch |

CI coverage: all are `[pipeline]` or `[diffuse]`, so the TSan job (`"[conv],[pipeline],[diffuse]"`) and the ordinary
ctest runs pick them up.

## Local results

**Release** (`build/release`, `-DSPATIAL_BUILD_PLUGIN=OFF`), the full non-hidden `spatial_tests`: **All tests passed (1 834 951 assertions in 244 test cases)**, 2 min 38 s (before the new tests: 237 cases, also green).

**TSan** (`cmake --preset tsan -DSPATIAL_BUILD_PLUGIN=OFF`, `build/tsan/tests/unit/spatial_tests
"[conv],[pipeline],[diffuse]"`): **All tests passed (76 800 assertions in 101 test cases), 0 ThreadSanitizer warnings**, 14 min 5 s. The `[h2c]` tests were also repeated 3 times under TSan: 0 warnings. The first TSan run found 94 races, all in the new stress test, which called `reset()` concurrently with the audio thread's `process()`. The host contract forbids that. The test now serialises `reset()` with `process()` like the other host calls, and nothing in the product changed.

**Debug, `SPATIAL_WERROR=ON`**: `SPATIAL_WERROR=ON cmake --preset debug -DSPATIAL_BUILD_PLUGIN=OFF`: `spatial_tests` builds with no warning (GCC, `-Wsign-conversion` included). `[h2c],[gate],[cond4],[reset-nowait]` in Debug (the gate's real-time assert active): all passed (271 assertions in 16 test cases).

`tools/ci/check_format.sh --fix` (clang-format 18): applied. `python3 tools/ci/check_boundaries.py`: OK.

Existing `[reset-nowait]` (3 cases), every `[pipeline]` test, the offline bounce bit-identity (condition 10's
"bounce == reference"), condition 12's stage and gate-scope tests and every golden-backed test pass unchanged.

### M7 under H-2c (local, Linux, 4 threads; builder-class shares 3), three runs (seeded offsets `0x07C20007` + case index, as file 9)

`build/release/tests/unit/spatial_tests "[m7-hold]"`. Times in ms; mid-solve = an edit at u × D_median into the running
solve (seeded u). The H-0 column is file 9's worst of 3 runs.

| scene | m | solve D median (runs 1/2/3) | worst solve | idle-edit hold median (1/2/3) | idle worst | mid-solve hold median (1/2/3) | **mid-solve worst, worst of 3 runs** | H-0 mid-solve worst (file 9) | landed after the solve ended (1/2/3) |
|---|---|---|---|---|---|---|---|---|---|
| layout4_s1/listener_corner | 1 | 175 / 218 / 206 | 240 | 51 / 57 / 51 | 80 | 32 / 36 / 34 | **50** | 177 | 1 / 1 / 2 |
| layout4_s1/listener_corner | 4 | 490 / 554 / 518 | 606 | 50 / 51 / 52 | 69 | 41 / 35 / 44 | **68** | 517 | 0 / 0 / 0 |
| layout4_s1/listener_corner | 5 | 654 / 634 / 734 | 884 | 52 / 51 / 51 | 71 | 44 / 45 / 36 | **58** | 559 | 1 / 0 / 0 |
| layout4_s1/listener_corner | 6 | 822 / 795 / 737 | 902 | 53 / 63 / 55 | 74 | 41 / 36 / 32 | **54** | 705 | 0 / 0 / 0 |
| layout4_s1/listener_corner | 8 | 998 / 980 / 965 | 1185 | 51 / 55 / 50 | 82 | 35 / 36 / 37 | **54** | 768 | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 1 | 116 / 123 / 111 | 141 | 94 / 97 / 94 | 140 | 88 / 77 / 80 | **138** | 215 | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 4 | 400 / 482 / 425 | 570 | 89 / 112 / 96 | 132 | 83 / 83 / 79 | **134** | 377 | 0 / 4 / 3 |
| cube100_lowalpha0.05_s1 | 5 | 519 / 498 / 500 | 762 | 95 / 92 / 89 | 143 | 76 / 70 / 91 | **104** | 540 | 0 / 0 / 0 |
| cube100_lowalpha0.05_s1 | 6 | 614 / 623 / 628 | 700 | 95 / 88 / 96 | 136 | 102 / 80 / 75 | **140** | 605 | 0 / 0 / 1 |
| cube100_lowalpha0.05_s1 | 8 | 948 / 856 / 791 | 1039 | 111 / 93 / 96 | 152 | 104 / 82 / 77 | **169** | 730 | 0 / 2 / 0 |

Reading:
- **The mid-solve hold now equals the idle hold, and it is flat in m.** Layout: medians 32–45 ms, worst 50–68 ms.
  Cube: medians 70–104 ms, worst 104–169 ms. The mid-solve median is even slightly below the idle median in the layout.
  Both are the plan plus the interim. Why the idle median is the higher of the two is not investigated. Under H-0 the worst was the solve plus the idle hold (705 / 768 ms at
  m = 6 / 8). Locally the 700 ms bound holds with a wide margin at every m. The acceptance reading is on CI's three OSes
  (Release benchmark step, lines `07c2-m7 `).
- The solve itself is slower than in file 9 (layout m = 1: 175–218 vs 105–123 ms; m = 8: 965–998 vs 721–814 ms). That is the
  `hardware_concurrency − 1` share (3 of 4 threads here) plus box noise. The time to the final at rest grows with it
  (M7b below). It only trades speed, never a result (D4).

### M7b (record), continuous automation measured under H-2c

`07c2-m7b-auto` lines, 20 position edits one every 100 ms, then rest (runs 1/2/3):

| scene | m | finals adopted during the motion | solves discarded (of 20 edits) | last edit → final, ms | end step, dB |
|---|---|---|---|---|---|
| layout4_s1/listener_corner | 1 | 0 / 0 / 0 | 19 / 19 / 19 | 262 / 228 / 231 | 1.152 (all runs) |
| layout4_s1/listener_corner | 4 | 0 / 0 / 0 | 19 / 19 / 19 | 507 / 637 / 598 | 0.146 |
| layout4_s1/listener_corner | 5 | 0 / 0 / 0 | 19 / 19 / 19 | 681 / 847 / 742 | 0.111 |
| layout4_s1/listener_corner | 6 | 0 / 0 / 0 | 19 / 19 / 19 | 777 / 976 / 841 | 0.148 |
| layout4_s1/listener_corner | 8 | 0 / 0 / 0 | 19 / 19 / 19 | 1112 / 1238 / 1035 | 0.098 |
| cube100_lowalpha0.05_s1 | 1 | 0 / 0 / 0 | 19 / 19 / 19 | 238 / 215 / 191 | 0.820 |
| cube100_lowalpha0.05_s1 | 4 | 0 / 0 / 0 | 19 / 19 / 19 | 477 / 635 / 542 | 0.304 |
| cube100_lowalpha0.05_s1 | 5 | 0 / 0 / 0 | 19 / 19 / 19 | 586 / 676 / 643 | 0.324 |
| cube100_lowalpha0.05_s1 | 6 | 0 / 0 / 0 | 19 / 19 / 19 | 779 / 907 / 696 | 0.372 |
| cube100_lowalpha0.05_s1 | 8 | 0 / 0 / 0 | 19 / 19 / 19 | 886 / 891 / 871 | 0.395 |

The derived `07c2-m7b` fractions are as in file 9: every 5 s, 100 % of solves complete; every 100 ms, 0 %, at every m.
The end step is the same in every run (the final is deterministic). The step is the AX47 held-level step after the
motion, recorded and not bounded.

Against H-0's `discardedMidDrag` (file 9): under H-0, continuous automation also never adopted a solve (the "never
mid-drag" discard); under H-2c the same 19 of 20 are discarded, now each **stopped** at its next block instead of run
to the end. The level settles once, after the motion, in about one solve time. M7b's other patterns (AX38 (iv)) are not
yet covered (below).

## Not done / follow-ups

- **B1-b re-run with the solve duration printed** (scope 11 item 6, last bullet): not done in this session. The B1-b
  instrument (`test_diffuse_records.cpp`, `[.][benchmark][diffuse-records-aq4][cond12c]`) runs unchanged under H-2c.
  Adding the solve-duration print needs a stage-hook timer per background pipeline. That instrument is a hidden
  benchmark for CI's Release step.
- **M7 on the three CI OSes** and the worst over ≥ 3 runs: CI's Release benchmark step (three local Linux runs here).
- **M7b under the AX38 (iv) patterns**: only continuous automation (100 ms) and the 5 s derived fraction are
  recorded. The 05i joint step pattern is not.
- The `[m7-hold]` probe's "solve end" marker is still the first Assemble after a Solve, now on the executor thread.
  The H-2c trial lines print "discarded +1" for every superseded solve.
