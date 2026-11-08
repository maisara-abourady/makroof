# Review: PR #14 — phase-06 real-time partitioned convolution + latency, follow-ups since 71d58b0   (head 31894b6, base main)

Scope of this review: `git diff 71d58b0 HEAD -- src tests tools .github docs/phases docs/BUILD_PLAN.md`, i.e. commits 163393d..31894b6. Everything up to 71d58b0 was covered by `docs/review/phase-06/review-PR14-at-1340b62.md` and is not re-reviewed here. The `.github/workflows/nightly.yml`, `tools/validation/requirements-extract.txt` and `docs/phases/phase-05.md` hunks come from the main merges (#16, #17; `git diff 6326c28 HEAD` shows nothing there beyond the PR's own ci.yml) and are out of scope.

## Verdict
**Not ready (CI)**, and Request changes on the description.

The follow-ups do three things:
- They spread each state's k ≥ 1 multiply-adds across the host callbacks of the block being taken in (lanes A and B in `CrossfadingConvolver`). As a result, the IR pickup moves one partition later (AX31: s0 = (⌊r/P⌋ + 2)·P).
- They zero non-finite input samples and sum the partitions late-first.
- They make the AllocationTracker step aside under ASan, add a watchdog to the before-`prepare()` tests, add a per-call multiply-add test, extend the benchmark to host buffer 64, and edit the plan (AQ4, AX31, phase-06 AC 3, phase-07, phase-13).

The lane bookkeeping is correct. I re-derived the age mapping (before the push, partition k reads age k−1; after the push, k = 0 reads age 0), the m/n/k resume decode, the install-at-once path, retire-then-pickup and `reset()`. I found no defect, and 13 mutants confirm it: the tests kill every non-equivalent mutant except one. An age off-by-one (k instead of k−1) fails 44 assertions; reading the new block at age 1 fails 63.

What blocks:
- CI is unfinished on the code commit 66419a5: build (windows), python tools (macos) and two macOS tail gates are still running.
- No CI run exists yet on head 31894b6.
- GitHub reports the PR as `dirty`: `docs/BUILD_PLAN.md` conflicts with main 8cd20dd (#18).
- The PR description still describes the pre-follow-up behaviour.

The most important code-level finding: the `reset()` test cannot see a missing `restartLanes()`. That mutant passes the whole `[conv]` suite. In my probe, the same mutant corrupts the heap (SIGABRT) when the fade target is shorter than the current IR (Major 1).

## Process gate
- **Scope:** the follow-ups are within phase-06 scope 3 (crossfading convolver) and the acceptance tests. The plan edits went through `/fix-plan` (decider D1, interrogator, advocate; ledger P06F-*), per the §6 row. Two things should be named in the PR description:
  - The `.claude/skills/review-phase-pr/references/*` edits (PFFFT tags, commit 89770db). They are a factual correction of the reviewer's knowledge base and the previous review asked for it, but they sit outside the phase's scope.
  - The phase-07 and phase-13 text additions. These are plan edits, not phase-07/13 work, so they are OK.
- **Dependencies:** unchanged (02 and 04 are `done`).
- **Status table / §6:** row 06 is back to `in progress` (163393d), which is correct while the follow-ups run. The §6 row for AQ4/AX31 is present (`docs/BUILD_PLAN.md:379`). **The table conflicts with main #18** (`git merge-tree HEAD origin/main` → CONFLICT in docs/BUILD_PLAN.md).
- **Assumptions used:** AX31 is cited at `CrossfadingConvolver.h:25` and AQ4 at `.cpp:325-328`. The new decision (later pickup) has an AX row, so it is not silent.
- **New/changed assumptions:**
  - AQ4 restated, AX31 added.
  - AQ4's "32 ms at P = 256 or 512" is only true at 48/96 kHz (Minor 4).
  - phase-06 AC 3 now ties the ramp start to `fadeStartSample()`. The test still computes s0 independently from r and asserts it (`test_crossfading_convolver.cpp:82-83`), so it is not circular.
- **Boundary & contract:** no change. `src/sim` is still JUCE-free and the contract is untouched.
- **Goldens/tolerances/skips:**
  - No goldens touched; tolerances unchanged (−120 / −100 dB).
  - New `SKIP`s for the `[alloc]` tests under ASan only (`test_crossfading_convolver.cpp:228`, `test_partitioned_convolver.cpp:247, 266`, `test_realtime_engine.cpp:169`). They carry a stated reason, the counting still runs in debug/release on 3 OSes and under TSan, and this is what the convolution reference §8 item 5 recommends. Acceptable.
- **PR description sections:** all six exist but are **stale** (Major 2).
- **CI** (`list_workflow_jobs` on run 42390056623 for 66419a5; `list_workflow_runs` on the branch):
  - Green: clang-format, ASan+UBSan, TSan, build (linux) (ctest 160/160), build (macos) (ctest 160/160), contract tools ×3, python tools linux/windows, most tail gates.
  - **In progress:** build (windows), python tools (macos), tail gates (macos, living_room / club).
  - The nightly run 42390056535 is in progress.
  - **No run on 31894b6.** It is docs-only, but ci.yml has no paths filter, so one is expected.
  - I did not check artifacts for this run because it is unfinished.

## Acceptance criteria audit (criteria touched by the follow-ups)
| # | Criterion (phase file) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | UPOLS = reference delayed by P, −120 dB, all IR lengths and blocks | Unchanged `PartitionedConvolver` tests. The crossfading path is covered by `test_realtime_engine.cpp:122` (2×2 `medium_room`, blocks random/64/2048) and `test_crossfading_convolver.cpp:106` | `renderOffline` / double direct convolution | −120 / −120 | build linux/macos green on 66419a5; Windows pending | Nothing about the lane decode: m/n decode mutants abort or fail at `test_realtime_engine.cpp:142` | Proven on linux/macos; Windows unproven |
| 2 | `render_cli --realtime-emulation` null, −120 dB | `tools/acoustics/tests/test_realtime_emulation.py` | offline render | −120 / −120 | python linux, windows green; macos pending | — | Unproven on macOS until the job finishes |
| 3 | A→B = analytic crossfade, −100 dB, ramp from where the new IR enters the output (AX31) | `test_crossfading_convolver.cpp:44` (s0 = (⌊r/P⌋+2)P asserted against `fadeStartSample()` and used in the analytic reference), `:326` (fade-in from silence) | analytic, double | −100 / −100 | linux/macos green | The old s0 (`fadeStart_ = blockStart_`) fails 63 assertions, and dropping lane B's remainder or not restarting lane B fails 31, so timing and lane-B bookkeeping are covered. Missing: a reset mid-block with A ≠ B lengths (Major 1) | Proven (linux/macos) |
| 4 | 100 requests / s, no leak, last wins | `:183` | −120 dB last second | — | ASan green | — | Proven |
| 5 | Zero heap allocations in `process`, also during crossfades | `:226`, `test_realtime_engine.cpp:167`, `test_partitioned_convolver.cpp:244` (skipped under ASan only) | AllocationTracker; the self-test at `test_partitioned_convolver.cpp:264` guards against a dead tracker | `== 0` | build linux/macos (tracker active); TSan (tracker active) | The lanes allocate nothing (`acc` comes from `prepare()`), and blocks 1/37/64 exercise `advanceLanes` | Proven (linux/macos) |
| 6 | TSan with 2 threads hammering `requestIr` | `:267` | TSan | — | TSan green on 66419a5 | — | Proven |
| 7 | Latency = P + pre-roll on an impulse | `test_realtime_engine.cpp:75` | measured | exact | green | Unchanged by AX31 (pickup ≠ latency): the install-at-once path keeps the first IR exact | Proven |
| 8 | Benchmark prints in CI (3 s, P = 512, 48 kHz ≤ 15 % on macOS) | `test_realtime_engine.cpp:204` (now host 512 and 64, mean/p99.9/max) | — | recorded | Linux log read: 3 s/P512/host 512 steady 1.9 %, crossfading 3.2 %. macOS log read: 3.1 % / 4.5 % (NEON), i.e. within 15 %. Windows pending | Numbers are printed, never asserted (by design, AC 8) | Proven for linux/macos |
| — | Work spreading (new behaviour, AX31 rationale) | `test_crossfading_convolver.cpp:434` (per-call MAC bound, host 64, P 512, 2×2, fades) | analytic work count | `≤ states·(⌈U·n/P⌉+1+NM)` | linux/macos green | Disabling spreading fails 250 assertions. Host sizes that don't divide P (37, random) are not checked against the bound (Minor 3) | Proven for n \| P |
| — | Non-finite input guard (new) | `test_realtime_engine.cpp:296` | `renderOffline` of the input with those samples zeroed | −120 dB + all finite | linux/macos green | Removing the guard fails it. Finite overflow (≈1e38) is out of scope (Minor 2) | Proven |

## Findings (by severity)
### Blockers
1. **CI unfinished on the code commit, none on head, and a merge conflict with main.**
   - On 66419a5 (run 42390056623), build (windows), python tools (macos) and the macOS tail gates `living_room` and `club` are still `in_progress`. Windows is the only OS that has not yet run the new lane code, the tracker `#if` and the watchdog (MSVC, `_aligned_malloc`).
   - Head 31894b6 has no run.
   - The PR is `mergeable_state: dirty`: `docs/BUILD_PLAN.md` conflicts with main 8cd20dd (PR #18, phase-05g row).
   - Resolve: merge main, keep both the 05g row and the 06/AX31 edits, then get a green run on the new head on all three OSes.

### Major
1. **`reset()` × lanes is untested: deleting `restartLanes()` from `reset()` passes every test, and the mutant corrupts the heap.**
   - Where: `src/sim/conv/CrossfadingConvolver.cpp:169`. The only reset test is `tests/unit/test_crossfading_convolver.cpp:403-428`, and it resets exactly at a partition boundary with hA and hB of equal length (500 taps). There, the lanes are already zero and `laneA_.total` happens to fit B.
   - Without the call, after a reset that ends a fade, lane A keeps A's `total` while `current_` is now B.
   - When A has more partitions than B, `advanceLane` decodes `m = done / (inputs·k1_B)` past `numOutputs` and writes beyond `lane.acc` (`.cpp:199, 211`; there is no bound on m).
   - When the reset falls mid-block, partial sums over the old, now-cleared history survive into the first block.
   - My probe confirmed both halves (scratch copy, not committed): fade from a 2000-tap A to a 300-tap B, `process(50)` mid-block, `reset()`, then blocks of 37. It passes at HEAD (−120 dB vs x*B), and the `restartLanes()`-less mutant dies with SIGABRT.
   - Why it matters: Phase 07 will call `reset()` from the host's `reset()` / transport paths at arbitrary positions, and Phase 10 keeps a fade running almost continuously, so this is the path that will run.
   - Resolve:
     - Add a reset test with mid-block position, a running fade, A longer than B, and an odd block size afterwards.
     - Optionally add a debug assertion in `advanceLane` that `lane.total == M·N·(K−1)` of the IR passed in.
2. **The PR description is stale against the follow-ups** (process-rules §7: the description is how Maisara and the contractor verify the phase).
   - AC 3 still says "s0 = (⌊r/P⌋+1)·P, which the test asserts". The test now asserts +2.
   - "Contractor review focus" says "s0 = first output sample of that block". That is no longer true; pickup and entry are one block apart, and the lanes are the new thing to review.
   - "Assumptions, thresholds, goldens" says "No AQ/AX value was changed or added … no §6 row". AQ4 was restated, AX31 added, and a §6 row exists.
   - The benchmark is described as host buffer 512 with mean/median/max; it is now 512 and 64 with mean/p99.9/max.
   - Follow-ups still list "NaN/Inf input … not guarded" and "AllocationTracker … applies in the ASan build". Both are now done here.
   - The CI links point to ed1ec95 / 459069e.
   - Resolve: rewrite the affected sections once CI on the new head is green. Add the host-64 benchmark lines, the AX31 user-visible cost (one extra partition, 10.7 ms at P = 512, for an isolated update) and the skill-reference edit.

### Minor
1. **Dead guard in `renderB`** (`src/sim/conv/CrossfadingConvolver.cpp:277`). `fadeStart_ <= newStart` is always true when `next_ != nullptr`: `next_` is set only in step 4 with `fadeStart_ = blockStart_ + P`, which is the next `newStart`, and `reset()`/`prepare()` clear `next_`. If it were ever false, `advanceLanes()` (`:249-250`) would still accumulate lane B while the boundary skips its remainder and output. Either drop the clause or make it an assertion, so a later change to the pickup rule cannot silently desynchronise the two.
2. **Input guard scope** (`.cpp:360-362`). It zeroes NaN/±Inf only. A finite but huge sample (|x| ≈ 1e38) overflows to Inf inside the forward FFT and poisons the FDL for the IR length all the same. `IrSet::create` still does not check that the taps are finite (prior m6, second half). Neither is a phase-06 criterion. Name both in the Phase 07 follow-ups (the builder asserts finiteness; optionally clamp the input to a sane bound) rather than claiming in `phase-07.md` scope 3 that non-finite input is "already" fully handled.
3. **The per-call multiply-add test covers only host sizes that divide P** (`tests/unit/test_crossfading_convolver.cpp:434-472`: host 64, P 512). The header's claim "at most ⌈U·n/P⌉+1 per state" (`.cpp`/test comment at `:430-433`) is not exercised for a call that straddles a boundary (n = 37, 100, random), where one call does the old block's remainder plus the new block's first share. A GENERATE over n ∈ {37, 64, 100} with the same bound (plus one share) would cover it.
4. **AQ4 wording: "32 ms at P = 256 or 512" holds only at 48 and 96 kHz** (`docs/BUILD_PLAN.md:85`).
   - Derived from `computeBlock()`: back-to-back fades are spaced ⌈L/P⌉·P samples apart.
   - 48 kHz: L = 1440, giving 1536 samples = 32.0 ms for P = 128, 256 and 512. So P = 128 also gives 32 ms.
   - 96 kHz: L = 2880, giving 3072 samples = 32.0 ms.
   - 44.1 kHz: L = 1323, giving 1536 samples = **34.8 ms**.
   - Add "at 48 kHz" (or the general ⌈L/P⌉·P form) via `/fix-plan`.
5. **Comment cites "the PR, O9"** (`src/sim/conv/CrossfadingConvolver.cpp:205`). O9 is a session-brief objective ID that a reader of the source can't resolve. Also, the claimed benefit of descending order (CLI null at P = 128 from −124.9 to −128.6 dB, commit 89770db) is not pinned by any C++ test: the ascending-order mutant passes `[conv]`. That is fine for a numeric improvement, but cite the measurement (or AX/ledger row) in the comment instead of "the PR".

### Questions (unverified, evidence requested)
1. **Windows:** do build (windows) ctest, including the 2×2 `[conv]` lane paths, the `[alloc]` tests with the tracker active and the watchdog tests, and the extended benchmark pass and print on the new head? Evidence: the green job log, linked from the updated description.
2. **CLI null margin after reordering:** the commit message says the P = 128 CLI null improved to −128.6 dB. Please quote the python job's numbers for all three P on the new head. I did not run the Python suite.
3. **Catch2 hang after a fatal signal (information, not this PR's code).** In two of my mutants, a SIGABRT inside a test left `spatial_tests` blocked in a futex with one thread, apparently Catch2's fatal-condition reporter deadlocking after heap corruption. A real crash in CI would then sit until the 600 s ctest timeout instead of failing fast. Consider `CATCH_CONFIG_NO_POSIX_SIGNALS`, or rely on ctest's timeout knowingly.

## What I verified myself
- Read at HEAD: `src/sim/conv/CrossfadingConvolver.{h,cpp}` (whole), `PartitionedConvolver.h` (FDL `head()`/`spectrum()` semantics) and `.cpp` (`push`). Read the whole diff of every test file, `ConvTestUtil.h`, `AllocationTracker.{h,cpp}`, and the plan diffs (AQ4, AX31, §6, phase-06/07/13).
- Re-derived by hand:
  - age mapping: before the push, partition kk uses slot head−(kk−1), i.e. X(b+1−kk); after the push, age 0 is the new block;
  - unit decode (m, n, k) against the loop nesting;
  - `renderB` reachability;
  - install-at-once: the k ≥ 1 terms are zero on an empty history, so the redundant `startLane` at `:274` is an equivalent mutant;
  - fade spacing ⌈L/P⌉·P at 44.1/48/96 kHz;
  - the AQ4 isolated-update delay s0 − r ∈ (P, 2P].
- Built `build/dev` (Release, no plugin) and ran `spatial_tests "[conv]"`: all passed (4260 assertions, 32 test cases).
- Built `build/asan-local` (ASan+UBSan, RelWithDebInfo): 28 passed and 4 skipped (the `[alloc]` SKIPs, as intended), 4213 assertions, no sanitizer report.
- Mutation testing on a scratch copy (`git archive HEAD`, own build dir, `[conv]` filter):
  - **Killed:**
    - age +1 (44 failures);
    - new block read at age 1 (63);
    - no spreading (250, in the MAC test);
    - n-decode wrong (abort);
    - m-decode wrong (segfault);
    - no lane-B remainder (31);
    - lane B not restarted (31);
    - NaN guard removed (2);
    - old pickup timing s0 = blockStart_ (63).
  - **Survived, equivalent:** ceil instead of floor share; no `startLane` at install-at-once.
  - **Survived, not a correctness bug:** ascending partition order.
  - **Survived, real gap:** no `restartLanes()` in `reset()` (Major 1), confirmed by a probe test that passes at HEAD and aborts on the mutant.
- CI: `list_workflow_runs` on the branch and `list_workflow_jobs` for run 42390056623. I grepped the logs of build (linux) (job 128455669946) and build (macos) (128455670055) for ctest and benchmark lines; job statuses are as listed above. `get_check_runs` for the PR returned 0 entries (no run on 31894b6). PR metadata came from `pull_request_read get`; the conflict was checked with `git merge-tree` against `origin/main` 8cd20dd.

## For Maisara
- Listening checklist: untouched; it is yours. The phase-06 `listening-pack` artifact for the new head will be in the CI run on the merged head once it is green (the current run on 66419a5 is unfinished). The follow-ups change the switch timing by one partition, so `ir_switch_demo.wav` is worth re-hearing from the new run.
- For the Expert (measured, not tuned): the host-64 benchmark shows what work spreading buys.
  - Linux, 12 s IR, P = 512, crossfading: p99.9 is 41 % of a 64-sample callback, max 46 %. The previous review estimated about 259 % for the unspread step.
  - **At P = 256 the 12 s IR still exceeds the budget while crossfading:** Linux p99.9 127 % (host 64) and 124 % (host 512). That is the non-uniform-partitioning item now planned in phase-13 scope 1.
  - macOS maxima (up to 458 % steady at host 512) are runner preemption; the means are low.
- AX31's user-visible cost: an isolated update reaches the output one partition (10.7 ms at P = 512) later than before. That is vetoable by you per the AX31 row.
- Wording conflict still open (CLAUDE.md "done when automated criteria pass" vs BUILD_PLAN preamble "after the listening checklist"): expect "listening pending Maisara" in the row 06 notes.

## Contractor review focus (from the phase file), with pointers into the diff
- **UPOLS indexing / overlap-save:** unchanged in `PartitionedConvolver.cpp`. The crossfading path no longer calls `renderPartition` and re-implements the sum in `advanceLane`/`finishLane` (`CrossfadingConvolver.cpp:187-240`). Review the slot formula at `:208` and the post-push age-0 term at `:234`.
- **Lock-free handover and reclamation:** pickup moved to step 4 (`:325-339`), after the retire at `:313-321`. `retiring_` retries are at `:267-268` and `:329-330`. The install-at-once special case is at `:269-276`.
- **Denormals:** unchanged (`Denormals.h`). The MSVC/ARM64 gap is now phase-13 scope 8.
- **Crossfade timing:** AX31, header `CrossfadingConvolver.h:16-39`, `fadeStart_ = blockStart_ + P` at `.cpp:336`, the ramp at `:301-312`.
