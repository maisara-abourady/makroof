# Review: PR #14 — phase-06 real-time partitioned convolution + latency   (head 1340b62, base main)

## Verdict
**Request changes.** It is also **Not ready (CI)**: the PR is a draft and the Windows build is still running.

The PR adds a PFFFT wrapper, a UPOLS `PartitionedConvolver` with a shared frequency-domain delay line (FDL), and a `CrossfadingConvolver` that swaps IRs through a single-slot atomic mailbox and a deferred-release SPSC queue. It also adds the `RealtimeEngine` façade, a JUCE-free FTZ/DAZ guard, an operator-new `AllocationTracker`, `render_cli --realtime-emulation`, the benchmark, a TSan CI job and the phase-06 listening pack.

The DSP core is correct. I re-read the UPOLS indexing, the overlap-save layout, the 1/2P scaling, the FDL wrap and the shared-history crossfade, and found no defect. Every automated criterion I could run passes with about 10 dB to spare in C++. CI on the head SHA is green for TSan, ASan+UBSan, python (all three OSes), clang-format, and ctest plus the benchmark on Linux and macOS. On the macOS runner (NEON), the 3 s / P = 512 case uses 2.1 % of the budget steady and 4.2 % while crossfading, against AQ10's 15 %.

What stops approval:
- The PR description is a placeholder and status row 06 is still `in progress`.
- Windows CI is unfinished.
- Two real-time-path behaviours have no AX row and no guard:
  1. The first IR is switched in hard, with no fade. I measured an onset step of about 25x the signal's normal per-sample slope.
  2. `process()` before a successful `prepare()` loops forever on the audio thread (confirmed by experiment).

To flip it: finish CI on Windows, write the six-section description, set row 06 to `done` with the numbers, and either add a guard or an AX row for each of the two behaviours (M1, M2).

## Process gate
- **Scope:** every hunk belongs to phase-06 scope items 1–8, plus the CI wiring, CLAUDE.md commands and THIRD_PARTY row the phase needs. The session brief `docs/sessions/2026-11-07-phase-06.md` follows the existing convention (`docs/sessions/` exists on main). Nothing from phases 07 or 10. OK.
- **Dependencies:** 02 is `done` (#5) and 04 is `done` (#8) in §0 at merge base e583f87. OK.
- **Status table / §6:** first commit 045d2d9 sets row 06 to `in progress`. That is correct. The row must still move to `done` with the PR link and benchmark numbers (DoD: "benchmark numbers in the status notes"). No §6 row is needed: no assumption, threshold or golden was changed.
- **Assumptions used:** cited where they apply:
  - AQ4 30 ms: `RealtimeEngine.h:28-29`, `RealtimeEngine.cpp:32`
  - AX18 laws: `CrossfadingConvolver.h:46`, `.cpp:65-80`
  - AX1 pre-roll in latency: `RealtimeEngine.h:8-10, :42`
  - AQ10 P ≤ 512: `PartitionedConvolver.h:27`
  - AX7 2×2 and AX6 rates: `RealtimeEngine.h:27, :34`
- **New/changed assumptions:** none were added. Two silent decisions need rows or code changes (M1, M2). The PR body correctly raises the AQ10 wording conflict (544 vs ≤ 512 samples) for Maisara without deciding it.
- **Boundary & contract:** `review_context.py` boundary scan is clean (48 files). `src/sim` is still JUCE-free and the contract is untouched. The one NFR-8 scan hit, `src/sim/Engine.cpp:418` (`emitter.id == "L"`), is old code and not in this diff.
- **Goldens/tolerances/skips:** no goldens touched. All tolerances equal the phase file's numbers (−120 / −100 dB). There is one `SKIP` (`test_partitioned_convolver.cpp:273`), for targets without FTZ control. All CI targets support FTZ, so it never fires in CI.
- **PR description sections:** all six are missing. The body says "Draft until CI is green… the full description replaces this text then". It has only "Raise with Maisara" and the session-brief link.
- **CI:** run 42354122535, every job on head 1340b62 (checked with `list_workflow_jobs`).
  - Green: clang-format; contract tools ×3; python tools ×3; ASan+UBSan; TSan; build (linux) and build (macos), both with ctest 151/151 and the benchmark printed (logs read); tail gates on most matrix cells.
  - **Still running at review time:** build (windows) (in the "Test (debug)" step), and most macOS/Windows tail-gate cells.
  - Artifacts on the head SHA (`list_workflow_run_artifacts`): `listening-pack` (id 13567023129, 92 MB), `SpatialScene-linux`, `SpatialScene-macos`, `pluginval-linux`, `pluginval-macos`. Nothing for Windows yet.

## Acceptance criteria audit
| # | Criterion (phase file) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | UPOLS = OfflineRender delayed by P, −120 dB, IR 1, P−1, P, P+1, 48 000, 144 000; blocks 1, 37, 64, 512, 2048, random | `test_partitioned_convolver.cpp:153` (P ∈ {128, 256, 512}), `:178` (2×2 vs `renderOffline`, Fft method) | `sim::convolve` / `renderOffline` (Phase 02, double, no PFFFT, no partitioning): independent | energy ratio −120 / −120 | ctest 151/151 on linux and macos (logs read); Windows pending | The input is only 30 000 samples, so at most about 235 FDL slots hold non-zero spectra and the full 1 125-partition float accumulation (P = 128, 144 000 taps) is never stressed. Block = 1 is skipped for L > 50 000 (fine: 37 covers it). | Proven on Linux/macOS. Local margins −129.8 to −137.7 dB. |
| 2 | `render_cli --realtime-emulation --block random` nulls against the offline render of a Phase 04 room IR, −120 dB | `tools/acoustics/tests/test_realtime_emulation.py:28` (random×3 P, 37, 2048, 1), plus `test_cli.cpp` and `test_realtime_engine.cpp:116` | Offline render of `medium_room` (Phase 02 path) | −120 / −120 | python tools linux, macos, windows green (macOS log read: same numbers as local) | Little. **Margin is only 4.5 dB at P = 128** (−124.5 dB, drum loop through `medium_room`) | Proven |
| 3 | A→B crossfade = (1−g)(x*A) + g(x*B), −100 dB, g a 30 ms linear ramp from the pickup block boundary | `test_crossfading_convolver.cpp:38` (P ×3, both laws, blocks 1, 37, 512, 2048, random) | Analytic, from double reference convolutions. The test computes s0 from the request position, not from `fadeStartSample()`, so it is independent. | −100 / −100 | ctest linux/macos | The retire-queue-full stall path (`CrossfadingConvolver.cpp:172-174, 225-226`); swaps to a *shorter* IR. Off-by-one in s0 or a per-callback ramp restart would fail (residual ≈ −78 dB estimated), so the test is adequate. | Proven (measured −132.8 to −133.2 dB) |
| 4 | 100 back-to-back `requestIr` in 1 s: no crash, no leak (ASan), last wins | `test_crossfading_convolver.cpp:177`, plus `:138` (latest-wins and use_count accounting) | Last-second null against x * IR₁₀₀ (−120 dB); `weak_ptr` expiry | −120 | ASan+UBSan job green, test #15 "Passed" in the log | The queue-full path again: `releaseRetired()` runs after every block, so `retiring_` is never used | Proven |
| 5 | Zero heap allocations in `process` for all block sizes, including during crossfades | `test_partitioned_convolver.cpp:243`, `test_crossfading_convolver.cpp:220` (also counts frees), `test_realtime_engine.cpp:161`; self-test at `test_partitioned_convolver.cpp:260` | AllocationTracker (operator new family, aligned and nothrow overloads included) | `== 0` | ctest linux/macos | Direct `malloc` (e.g. a future `pffft_new_setup` in `process`) is not seen. That is documented in `AllocationTracker.h:14`. | Proven |
| 6 | TSan (Linux) passes a test that hammers `requestIr` from 2 threads while processing | `test_crossfading_convolver.cpp:259` (700 ms, 2 producers that also call `releaseRetired`, fade length 96) | TSan happens-before | halt_on_error=1 | TSan (linux) green; log read: "All tests passed (2035 assertions in 23 test cases)" | Races only on paths not reached in 700 ms (queue full, `reset()`) | Proven |
| 7 | `latencySamples()` = measured impulse offset through a delta IR = P + pre-roll | `test_realtime_engine.cpp:69` (P ×3 × 44.1/48/96 kHz, random blocks ≤ 256), `:94` (`open_field` direct peak) | Measured first non-zero sample | exact | ctest linux/macos | Little: block-size independence is already covered by #1 | Proven |
| 8 | Benchmark prints in CI; 3 s, P = 512, 48 kHz ≤ 15 % on the macOS runner | `test_realtime_engine.cpp:196` (hidden `[benchmark]`, run from Release) | — | recorded | macOS (NEON): steady 2.1 %, crossfading 4.2 %. Linux (SSE1): 2.1 % / 4.3 %. Windows pending | Measures host buffer 512 only. The worst single callback at 64 or 128 samples is not reported (see m3). | Proven for macOS and Linux. **Status-note entry missing** |

## Findings (by severity)
### Blockers
1. **PR is not done.** `docs/BUILD_PLAN.md` §0 row 06 is still `in progress`. The PR body is a placeholder with none of the six required sections (process-rules §7): what was done, acceptance checklist with CI links, listening checklist with artifact location, contractor focus, follow-ups, assumption/golden changes. build (windows) has not finished, so the "3 OSes" criteria are unproven on Windows. The author has declared this a draft. Resolve by finishing CI, then filling in the description and the row 06 notes (benchmark numbers per OS, including macOS 2.1 % / 4.2 %).

### Major
1. **M1 — First IR is switched in hard, with no fade and no AX row.**
   - Where: `src/sim/conv/CrossfadingConvolver.cpp:178-181` (`current_ = r; // first IR: no fade from silence`), documented at `CrossfadingConvolver.h:27` and `RealtimeEngine.h:13-14`.
   - The phase file (scope 3) only says "a pending IR starts a 30 ms crossfade from the current to the new state". "No current IR means hard install" is a new decision.
   - It is audible. The new state convolves the *full* input history, so if audio is already playing when the first IR lands, the output steps from 0 to mid-tail. My probe (2 × 2, 220 Hz sine at 0.5, decaying noise IR, first `submitRoomIR` after 1 s) measured a largest sample-to-sample step of 0.0435 against an output peak of 0.0616. That is about 25x the sine's normal per-sample slope, i.e. a click.
   - Phase 07 builds the first IR on a builder thread after `prepareToPlay`, so this will happen on every plugin load or scene load that occurs during playback.
   - Fix (either): fade in from silence with the requested law (`yA = 0` when `current_ == nullptr` already exists at `:193-194`, so just start a fade), or add an AX row with rationale and the phases it breaks (07, 10) and the click-detector expectation.
2. **M2 — Unbounded loop on the audio thread when `process()` runs before a successful `prepare()`.**
   - Where: `src/sim/conv/CrossfadingConvolver.cpp:236-238` and `src/sim/conv/PartitionedConvolver.cpp:217-219`. With `partitionSize_ == 0` the chunk is 0, `done` never advances and `while (done < n)` never exits.
   - Confirmed: a probe calling `RealtimeEngine::process` before `prepare` was still running when `timeout 5` killed it (exit 124).
   - A plausible way to reach it in Phase 07: `RealtimeEngine::prepare` throws for an unsupported rate (e.g. 192 kHz, `RealtimeEngine.cpp:27-28`) *before* `convolver_.prepare` runs. A plugin that catches the throw and keeps processing then hangs the host's audio thread (realtime-audio-juce §10 Q9 and Q25).
   - Fix: an early `if (partitionSize_ == 0) { zero out; return; }` (or a `prepared_` flag) in both `process` overloads, plus a test that calls `process` on a default-constructed engine and checks for silence.

### Minor
1. **m1 — Denormal guard is never shown to be active inside `process()`.**
   - `tests/unit/test_partitioned_convolver.cpp:269-288` tests `ScopedFlushDenormals` on its own.
   - Deleting `const ScopedFlushDenormals noDenormals;` from `CrossfadingConvolver.cpp:234` or `PartitionedConvolver.cpp:215` would fail no test.
   - Suggest: an input of about 1e-20 through an IR of about 1e-20. Every product is about 1e-40 (subnormal), so the output must be exactly 0 with the guard on. Run it on x86 and on arm64 CI.
2. **m2 — Denormal inline asm has no `"memory"` clobber** (`src/sim/conv/Denormals.h:31, :33, :42`). Without it the compiler may move loads and stores (e.g. the ramp loop in `computeBlock`) across the FPCR write. JUCE uses the same pattern, so this is low risk, but adding `: "memory"` is free. Also, MSVC/ARM64 compiles to a no-op (`:12-17`). That is acceptable while no CI target needs it, but name it in the follow-ups for Phase 13 (Windows on ARM).
3. **m3 — Benchmark measures host buffer 512 only** (`tests/unit/test_realtime_engine.cpp:196-254`).
   - The phase file asks for exactly this, so it is not a defect against the phase.
   - The UPOLS step runs whole inside one callback, though. At a 64-sample host buffer (budget 1.33 ms) and P = 512, the worst callback is the full step:
     - 12 s IR while fading: ≈ 2.1 ms on macOS (20.1 % × 10.67 ms), i.e. 161 % of a 64-sample callback; ≈ 3.5 ms on Linux, 259 %.
     - 3 s IR while fading: about 34 %.
   - convolution-and-movement §1.2. Report it to the Expert and add a follow-up (07 or 13): print the worst callback at n = 64 and 128, or spread the MAC across sub-blocks.
4. **m4 — Release-queue-full fallback is untested** (`CrossfadingConvolver.cpp:172-174, 225-226`; `kReleaseQueueSize = 64` at `.h:97`). Every test drains after each block. Add a test with more than 64 fades and no `releaseRetired()`: it should show no lost or freed request, fades pausing, then resuming after a drain. The fallback ("start no new fade until it fits") is itself an undocumented policy. Mention it in the PR follow-ups or in the M1 AX row.
5. **m5 — No `static_assert(std::atomic<Request*>::is_always_lock_free)`** at `CrossfadingConvolver.h:125`, nor for the `std::atomic<std::size_t>` indices at `:129-130` (realtime-audio-juce §2.2).
6. **m6 — NaN/Inf handling is absent.**
   - `FrequencyDelayLine::push` (`PartitionedConvolver.cpp:111-123`) transforms whatever arrives. One NaN input sample poisons every output for the full IR length (up to 12 s) through the FDL.
   - `IrSet::create` (`:69-82`) does not check that the taps are finite.
   - The phase file does not require either, so this is a follow-up for Phase 07, where the host feeds the input (convolution-and-movement §7.2, checklist Q17).
7. **m7 — `AllocationTracker` replaces operator new/delete in the whole test binary** (`tests/support/AllocationTracker.cpp:117-237`), including the ASan build. It forwards to `malloc`/`free`, so ASan still catches leaks and use-after-free. It loses `alloc-dealloc-mismatch` and `new-delete-type-mismatch` detection for *every* test in `spatial_tests`. Consider compiling the replacement out under `__SANITIZE_ADDRESS__` / `__has_feature(address_sanitizer)` and SKIP-ing the `[alloc]` tests there, the way WebRTC does (convolution-and-movement §8).
8. **m8 — PFFFT is pinned by tag `v1.1.0`, not by commit** (`cmake/SpatialDependencies.cmake:16-19`). CLAUDE.md allows tags, and the commit is recorded in the comment and in THIRD_PARTY. A tag can be moved, though, and the hash is already known: `GIT_TAG 1fdcb508e5082052ab406d560b7c4622b8b4b0dd` without `GIT_SHALLOW` would make the pin immutable. Optional.
9. **m9 — Thin margin on the CLI null at P = 128**: −124.5 dB against −120 dB (`tools/acoustics/tests/test_realtime_emulation.py:30`). It passes on Linux and macOS with identical numbers. Note it in the PR so a later FFT backend change (e.g. AVX) is not tuned to fit.

### Questions (unverified, evidence requested)
1. **Windows:** do `build (windows)` ctest (all `[conv]` tests, `[alloc]` with `_aligned_malloc`) and the benchmark pass and print? Evidence: the green job log and the benchmark lines, linked from the PR.
2. **AQ10 latency (for Maisara and the Expert, not a finding):** `latencySamples()` = P + 32 = 544 at the default P = 512 (`RealtimeEngine.h:42`). The PR raises options (a) and (b) correctly. It needs a `/fix-plan` decision before Phase 07 reports latency to hosts.
3. **Thread-safety contract for Phase 07:** `prepare()` and the destructor (`CrossfadingConvolver.cpp:23-44`) must not run concurrently with a builder thread's `requestIr()`. The header says so (`.h:61`). Please list "Phase 07 joins or stops the builder before `prepareToPlay`/destruction" under follow-ups.

## What I verified myself
- `review_context.py --base origin/main --head origin/pr/14`: phase 06 detected; boundary clean; NFR-8 hit is pre-existing; audio-thread hits are all in constructors, `prepare` or `requestIr`/`releaseRetired` (non-audio).
- Read every changed file at HEAD:
  - `src/sim/conv/*`, `src/sim/RealtimeEngine.*`, the three new test files, `ConvTestUtil.h`, `AllocationTracker.*`, the CLI diff, `test_realtime_emulation.py`, the `listening_pack.py` phase-06 builder, CMake, CI, THIRD_PARTY and the CLAUDE.md diff.
  - UPOLS checks:
    - IR partitions are P coefficients followed by P zeros, scaled once by 1/2P (`PartitionedConvolver.cpp:66-81`).
    - The input window is [previous P | newest P] (`:118-120`) and the last P samples are kept (`:150`).
    - The newest spectrum pairs with partition 0, and the slot wraps on FDL *capacity*, not Np (`:140-145`).
    - The accumulator is cleared per output (`:136`).
    - Only the unordered `pffft_transform` and `pffft_zconvolve_accumulate` are used.
    - Buffers come from `pffft_aligned_malloc` (64-byte alignment, checked in `pffft_common.c`), including the work buffer.
  - Crossfade timing: s0 = (b+1)P in output time, the ramp is indexed by the absolute output sample (sample-accurate across callbacks), and it is applied after the overlap-save discard. That matches the phase file. A request that arrives mid-fade starts at the first P-boundary after the fade ends.
  - Mailbox and queue: the mailbox is a single `exchange` with `acq_rel` on both sides, and the displaced request is freed on the requester's thread. The SPSC queue uses relaxed own-index plus acquire other-index loads and release stores, monotonic indices, and a mutex on the consumer side only.
- **Builds and tests run locally** (all builds at 1340b62, rebuilt incrementally):
  - `build/dev/tests/unit/spatial_tests "[conv]" -s` (Release): 23 cases / 2035 assertions pass. Margins: UPOLS −129.8 to −137.7 dB; 2×2 −131.1 to −132.1 dB; crossfade −132.8 to −133.2 dB; engine vs `renderOffline` −130.2 dB.
  - TSan (`build/tsan-local`, `TSAN_OPTIONS=halt_on_error=1`) and ASan (`build/asan-local`) runs of `"[conv]"`: all pass.
  - `xvfb-run -a ctest --preset debug -j4`: 151/151 pass.
  - `RENDER_CLI=build/dev/render_cli SPATIAL_REQUIRE_RENDER_CLI=1 pytest tools/acoustics/tests/test_realtime_emulation.py test_listening_pack.py -k "realtime or phase_06"`: 9 pass. Residuals −124.5 (P = 128) to −127.9 dB. Listening-pack builder: −127.3 dB and 11 click-detector events, max −76.8 dBFS.
  - Local benchmark (4-core container, noisy): 3 s / P = 512 at 3.2 % steady and 6.4 % fading.
- **Probes** (scratchpad, linked against `build/dev` libs, no repo edits):
  - `process()` before `prepare()` hangs (M2).
  - First-IR hard onset is a step of 0.0435 against a 0.0616 peak (M1).
- **Calculation:** the README explains the 11 click events on `ir_switch_demo.wav` as slope-corner splatter of the 30 ms ramp. I re-derived it: kink amplitude Δw' = (π/2)/0.03 s. The energy above 2 kHz in a 2 ms frame is A²Δw'²/(3(2π)⁴f³)/0.002, which gives rms ≈ 1.9e-4·A ≈ −74 dB re the tone. That matches the README's "about 74 dB below the tone". One event per switch (11 switches in 6 s) is consistent with that explanation, so these are not clicks.
- **CI logs read:** TSan (whole test step), ASan (per-test lines), python tools macOS (realtime tests and pack line), build linux and build macos (ctest summary, benchmark, start of pluginval). PFFFT tag and commit checked in the fetched clone (`build/debug/_deps/pffft-src`: HEAD 1fdcb508, 2026-02-27, tag v1.1.0; LICENSE.txt present).
- **Reference correction for the skill:** `references/convolution-and-movement.md` §3.2 says the marton78 fork has "No GitHub Releases… pin by commit hash", and `phase-checklists.md` (Phase 06) says "The marton78 fork has no release tags". Both are stale. Tag `v1.1.0` exists (commit 1fdcb508, 2026-02-27). The PR is not at fault; the reference files need updating.

## For Maisara
- **Listening checklist:** untouched; it is yours. The `listening-pack` artifact of CI run 42354122535 (id 13567023129, head 1340b62) holds `phase-06/drums_medium_room_offline.wav`, `drums_medium_room_realtime.wav`, `ir_switch_demo.wav` and a README.
- **About `ir_switch_demo.wav`:**
  - `concert_hall_box` is about 29 dB quieter than `living_room` (AX2: its emitters are farther away), so you will hear a big level change every 0.5 s. That is by design.
  - The automatic click detector flags each switch at about −77 dBFS. My calculation puts that at the expected ramp-corner splatter, about 74 dB below the tone, not a click. Your ears decide.
- **For the Expert:**
  - The AQ10 latency wording (544 vs 512 samples, PR body).
  - Small-buffer worst-case CPU for 12 s IRs during fades (m3).
  - No accuracy shortfall was found or tuned.
- **Plan wording conflict (still open):** CLAUDE.md sets `done` when the automated criteria pass, but the BUILD_PLAN preamble requires your listening checklist too. Expect the row's notes to say "listening checklist pending Maisara".

## Contractor review focus (from the phase file), with pointers into the diff
- **UPOLS indexing and overlap-save correctness:** `src/sim/conv/PartitionedConvolver.cpp:62-83` (IrSet padding and scaling), `:111-123` (FDL push, head advanced before write), `:127-152` (`renderPartition`: slot pairing, wrap on capacity, last-P discard), `:213-234` (block accumulation, in-place order). Tests: `test_partitioned_convolver.cpp:153, :178, :218`.
- **Lock-free handover and memory reclamation:**
  - Mailbox: `CrossfadingConvolver.cpp:97-106` (producer) and `:176` (consumer).
  - Release queue: `:108-135`. Retirement: `:219-227`.
  - Queue-full fallback: `:172-174` (untested, m4).
  - Teardown: `clearAll` at `:28-36`.
  - Tests: `test_crossfading_convolver.cpp:138, :177, :220, :259`.
- **Denormal handling on ARM and x86:** `src/sim/conv/Denormals.h` (MXCSR 0x8040; FPCR bit 24; no-op on MSVC/ARM64; no `"memory"` clobber, m2). Guard sites: `CrossfadingConvolver.cpp:234`, `PartitionedConvolver.cpp:215`, neither tested in place (m1). The macOS CI runner is arm64 (benchmark backend "NEON"), so the AArch64 branch is compiled and its unit test ran there.
- **Crossfade timing semantics:** header contract at `CrossfadingConvolver.h:16-27`; `computeBlock` at `.cpp:166-230` (`newStart`, `fadeStart_`, ramp index `min(s − s0, L)`, end-of-fade test at `:219`); ramps built from L = lround(0.030·fs) at `RealtimeEngine.cpp:32`. Test: `test_crossfading_convolver.cpp:38` with independently computed s0. The first-IR exception is M1.
