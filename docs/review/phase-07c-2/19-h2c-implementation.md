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
to the end. The level settles once, after the motion, in about one solve time. M7b under the AX38 (iv) patterns: next
section.

### M7b under the AX38 (iv) patterns (local)

`build/release/tests/unit/spatial_tests "records: M7b under*"` (`tests/unit/test_m7_hold.cpp`, hidden, tagged
`[.][benchmark][m7-hold]`, so CI's Release benchmark step runs it; lines `07c2-m7b ... pattern=`). Local Linux, 4 threads
(builder-class shares 3), 48 kHz, two runs. The patterns are those of the AX38 (iv) records test
(`test_diffuse_records.cpp`, "records: AX38 (iv) multi-instance load and staleness"), on the M7 scenes and the M7 W_max
seam (`setDiffuseLimitsForTest`, W_scene = 2 × m × `kWMaxPerEmitterProvisional`, set before `prepare()`):

- **(L) project load:** N fresh instances, `prepare` + `beginRestore` + `restore` one after another on one host thread
  (keyless: no saved level). The pattern ends when the last `restore()` returns.
- **(J) joint step:** with every instance settled after (L), one listener-Y change (0.001 normalised) on every instance at
  once. The pattern ends when the last `setParameter()` returns.

Per pattern: the `Stats` deltas summed over the N instances, taken once all are settled; "completed" = finalSubmits /
(finalSubmits + discardedMidDrag). The time from the end of the pattern to each instance's next final
(`finalSubmits` + 1) is 0 for an instance whose final was already in when the pattern ended. The end step is
`lastStepDb` after that final over the instances. `maxStepDb` is the largest since construction, worst instance. No audio
thread runs (as in the AX38 (iv) records test): the convolver's mailbox is latest-wins and a submit never waits for
`process()`. Run 1 is on the committed product code. Run 2 was built with another agent's uncommitted robustness edits
in `src/plugin/core/` (a failed executor post is retried, finished jobs are freed outside `jobMutex_`), which change no
timing path. The counts and steps are identical in both runs.

**H-0 reference (not measured):** under H-0 a single load or a single joint step has no mid-solve edit, so its
`discardedMidDrag` was 0 by construction. Every line states this.

| scene | m | pattern | N | pattern length, ms (runs 1/2) | solves (of them sync) | finalSubmits | discardedMidDrag | **completed** | final in before the end (run 2) | end → final median, ms (1/2) | **end → final worst, ms (1/2)** | end step lastStepDb median / worst, dB | maxStepDb, dB |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| layout4_s1/listener_corner | 1 | L (load) | 1 | 450 / 529 | 2 (2) | 1 | 0 | **100 %** | 0/1 | 88 / 128 | **88 / 128** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 1 | J (joint step) | 1 | 0 / 0 | 1 (0) | 1 | 0 | **100 %** | 0/1 | 214 / 315 | **214 / 315** | 1.010 / 1.010 | 1.010 |
| layout4_s1/listener_corner | 1 | L (load) | 4 | 1805 / 2031 | 8 (8) | 4 | 0 | **100 %** | 3/4 | 0 / 0 | **118 / 85** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 1 | J (joint step) | 4 | 0 / 0 | 4 (0) | 4 | 0 | **100 %** | 0/4 | 420 / 647 | **653 / 951** | 1.010 / 1.010 | 1.010 |
| layout4_s1/listener_corner | 1 | L (load) | 8 | 3402 / 3887 | 16 (16) | 8 | 0 | **100 %** | 7/8 | 0 / 0 | **84 / 90** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 1 | J (joint step) | 8 | 0 / 0 | 8 (0) | 8 | 0 | **100 %** | 0/8 | 895 / 994 | **1548 / 1809** | 1.010 / 1.010 | 1.010 |
| layout4_s1/listener_corner | 6 | L (load) | 1 | 1128 / 1679 | 2 (2) | 1 | 0 | **100 %** | 0/1 | 82 / 84 | **82 / 84** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 6 | J (joint step) | 1 | 0 / 0 | 1 (0) | 1 | 0 | **100 %** | 0/1 | 717 / 752 | **717 / 752** | 0.119 / 0.119 | 0.119 |
| layout4_s1/listener_corner | 6 | L (load) | 4 | 4856 / 6754 | 8 (8) | 4 | 0 | **100 %** | 3/4 | 0 / 0 | **84 / 95** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 6 | J (joint step) | 4 | 0 / 0 | 4 (0) | 4 | 0 | **100 %** | 0/4 | 1979 / 1946 | **3156 / 3143** | 0.119 / 0.119 | 0.119 |
| layout4_s1/listener_corner | 6 | L (load) | 8 | 10461 / 13006 | 16 (16) | 8 | 0 | **100 %** | 7/8 | 0 / 0 | **102 / 140** | 0.000 / 0.000 | 0.000 |
| layout4_s1/listener_corner | 6 | J (joint step) | 8 | 0 / 0 | 8 (0) | 8 | 0 | **100 %** | 0/8 | 3478 / 3502 | **5946 / 6012** | 0.119 / 0.119 | 0.119 |
| cube100_lowalpha0.05_s1 | 1 | L (load) | 1 | 1113 / 1060 | 2 (2) | 1 | 0 | **100 %** | 1/1 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 1 | J (joint step) | 1 | 0 / 0 | 1 (0) | 1 | 0 | **100 %** | 0/1 | 240 / 244 | **240 / 244** | 0.127 / 0.127 | 0.127 |
| cube100_lowalpha0.05_s1 | 1 | L (load) | 4 | 4888 / 4496 | 8 (8) | 4 | 0 | **100 %** | 4/4 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 1 | J (joint step) | 4 | 0 / 0 | 4 (0) | 4 | 0 | **100 %** | 0/4 | 675 / 486 | **921 / 683** | 0.127 / 0.127 | 0.127 |
| cube100_lowalpha0.05_s1 | 1 | L (load) | 8 | 10506 / 10007 | 16 (16) | 8 | 0 | **100 %** | 8/8 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 1 | J (joint step) | 8 | 0 / 0 | 8 (0) | 8 | 0 | **100 %** | 0/8 | 1023 / 1167 | **1520 / 1675** | 0.127 / 0.127 | 0.127 |
| cube100_lowalpha0.05_s1 | 6 | L (load) | 1 | 2861 / 2694 | 2 (2) | 1 | 0 | **100 %** | 1/1 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 6 | J (joint step) | 1 | 0 / 0 | 1 (0) | 1 | 0 | **100 %** | 0/1 | 959 / 789 | **959 / 789** | 0.027 / 0.027 | 0.027 |
| cube100_lowalpha0.05_s1 | 6 | L (load) | 4 | 9833 / 9905 | 8 (8) | 4 | 0 | **100 %** | 4/4 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 6 | J (joint step) | 4 | 0 / 0 | 4 (0) | 4 | 0 | **100 %** | 0/4 | 1632 / 2100 | **2648 / 3333** | 0.027 / 0.027 | 0.027 |
| cube100_lowalpha0.05_s1 | 6 | L (load) | 8 | 17736 / 18488 | 16 (16) | 8 | 0 | **100 %** | 8/8 | 0 / 0 | **0 / 0** | 0.000 / 0.000 | 0.000 |
| cube100_lowalpha0.05_s1 | 6 | J (joint step) | 8 | 0 / 0 | 8 (0) | 8 | 0 | **100 %** | 0/8 | 3405 / 3252 | **5987 / 5651** | 0.027 / 0.027 | 0.027 |

Reading:
- **Every solve completes under both patterns** (discardedMidDrag 0, completed 100 %), as under H-0. Neither pattern
  edits mid-solve, so H-2c's cancel never fires.
- **(L)** "sync" is 2 per instance: a fresh instance's first `prepare()` solves synchronously (`insertSolves`), then
  the keyless restore solves again (FM-3'). The load is audible when each `restore()` returns (the pattern length is the
  time until the last one is). In the cube, every final is in before the load ends (the restore's synchronous build is
  final). In the layout, the last instance's final follows within 82–140 ms, all earlier ones being already in. The end
  step is 0.000 dB: the final confirms the synchronously solved level.
- **(J)** The N background solves queue at the gate, so the time to the final grows about linearly with N. Worst over
  both runs: 315 / 951 / 1 809 ms (layout, m = 1, N = 1 / 4 / 8), 752 / 3 156 / 6 012 ms (layout, m = 6),
  244 / 921 / 1 675 ms (cube, m = 1), 959 / 3 333 / 5 987 ms (cube, m = 6). The end step is the same for every instance
  and run (deterministic): 1.010 dB (layout, m = 1), 0.119 dB (layout, m = 6), 0.127 dB (cube, m = 1), 0.027 dB (cube,
  m = 6). This is the AX47 held-level step after a B1′ hold, recorded and not bounded.
- **CI cost:** the case takes 94 s and 101 s locally (wall), against about 3 minutes allowed per OS, so N = 1, 4, 8 and
  both scenes are kept. Most of it is (L) at N = 8 (3.4–18.5 s) and (J) at N = 8, m = 6 (up to 6 s).

## Not done / follow-ups

- **B1-b re-run with the solve duration printed** (scope 11 item 6, last bullet): the print was added in commit
  `853a586` (`07c2-b1b` lines, from `Stats::totalSolveMs` / `totalGateWaitMs` over each 10 s window). Local values at
  0 / 1 / 2 / 4 / 8 builders: 0 / 1 / 1 / 2 / 4 solves completed per 10 s window, mean solve 0 / 120 / 96 / 103 / 117 ms,
  mean gate wait 0 / 0 / 0 / 45 / 68 ms. CI pending on run 45020888832.
- **M7 on the three CI OSes** and the worst over ≥ 3 runs: CI's Release benchmark step (three local Linux runs here).
- **M7b under the AX38 (iv) patterns**: (L) project load and (J) joint step recorded locally (section above). The
  three CI OSes come from CI's Release benchmark step (`07c2-m7b ... pattern=` lines).
- The `[m7-hold]` probe's "solve end" marker is still the first Assemble after a Solve, now on the executor thread.
  The H-2c trial lines print "discarded +1" for every superseded solve.
