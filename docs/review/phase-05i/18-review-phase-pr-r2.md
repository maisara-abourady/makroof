# Review (round 2): branch claude/charming-franklin-pyvvw3, phase-05i (head ee25421, base main d606b10)

**Scope of this round.**
- **Delta reviewed.** Mainly `b83345c..ee25421`. I also covered the two fix commits before it (`8199f86`, `b83345c`), because they answer round 1's minors.
- **Round 1.** See `review-claude-charming-franklin-pyvvw3-phase-05i.md`; its findings that are not listed here stand as written.
- **Review type.** This is a branch review: no PR exists. The verdict can only be "Request changes" or "Not ready (no CI)".

## Verdict

**Not ready (no CI). There is no blocker or major finding in the code.**

What the delta adds, all print-only:
- **D-Q5.** The restore gate prints a solve-median bound: `kSolveWarn` = 1.20, `solveRefMs`, and PROVISIONAL while fewer than 3 runs back it.
- **Q1.** The restore gate prints the closed-register text for the Linux and Windows low-α entries (`listed=false`).
- **D-G1.** Record (d) gets a gate-wait split: `measureGateWait` and `printGateSplit`.
- **Bookkeeping.** CHANGELOG entries for the new constants, plus board-driven plan text.

What I checked against CI run 43007183782 (on b94e14f) and locally:
- **CI numbers match the constants.** The run is green on all three build jobs; the GATE and K-e12 lines in its logs match the new constants and the plan text.
- **The delta compiles.** It builds cleanly with GCC and Clang at `-Wall -Wextra -Wpedantic -Wshadow -Werror` (syntax-only).
- **Formatting is clean.** clang-format 18 reports no changes.

Why it is not ready: the new test code (the SOLVE print, the closed-register branch, the gate-wait split, K-e12's per-run in-flight flag) has **never run in CI**. The commits after b94e14f change `tests/unit/test_diffuse_records.cpp`, so the PR's run is the first evidence for this code.

**Most important item:** the code already treats the Linux and Windows low-α register entries as closed. The plan text still says they "stand" or "stay listed": AX38 4c and phase-05i §3.3 (ii). The plan editor deferred that closure to the PR's CI run of record (file 15, line 69). The two must be reconciled before `done`.

## Round-1 minors: status

| # | Round-1 finding | Status | Evidence |
|---|---|---|---|
| 1 | Golden gated by the export script, not `update_goldens.py`; stale comment | **Comment fixed** (`test_diffuse_agreement.cpp:438-441`). The deviation itself is unchanged and documented (file 2, G11). | It still has to be named in the PR as "met in substance", with its follow-up (pending). |
| 2 | Provenance not the script's own output | **Mostly resolved.** The script now writes the full commit, a dirty flag, `l_ref_max_by_room_band` (ℓ_ref, as §3.1 asks) and `recipe_checks`. | Residue: see new Minor 3. |
| 3 | `--check` did not cover the chunked solver | **Resolved.** `--check-chunked` (CR4 1.25 m) was added, and its result is recorded in the provenance (`worst_rel_diff` 0.0, script commit 8199f86). | My own round-1 recomputation agrees. |
| 4 | K-e12 may count restores with nothing in flight | **Partly resolved.** Each run now prints `build in flight: yes/no` (`test_diffuse_records.cpp:1408, 1427-1431`). | Residue: see new Minor 2. |
| 5 | (iv) wording: the default-scene build in the load time; "0 other rebuild" | **Resolved** (`:1080-1082`; "0: uncontended baseline"). The duplicate 05h (iv) test (`:829`) still runs. | That remains a CI-time note, not a defect. |
| 6 | Redundant `set -o pipefail` | Note only, unchanged. | — |

## Process gate (delta)

- **Scope.** The delta is all phase-05i: §3.2 records, §3.3 register rules (ii)/(iv), and the D-G1 test-side split that the board added to §3.2 and §4 criterion 2. There is no `src/` change: `git diff --stat d606b10..ee25421 -- src/` is empty.
- **CHANGELOG.** There are two new entries: "05i, Q1" and "05i, D-Q5". Both are test constants, not golden files, and they are labelled that way.
  - The D-Q5 baselines match run 43007183782's GATE lines: Linux 131.2 / 80.9 ms, macOS 102.7 / 83.7 ms.
  - Windows 144.4 / 90.4 ms is the mean of 145.0 / 90.6 from this run and a second run, 42964823518, which I did not read.
  - Every run named is in-window: flutterDev is −3.7 %, +2.4 % and +1.3 %.
- **§6 rows.** Four rows were added by the plan editor (D-Q5, Q3, D-G1 + G1-C1, the AX43 outer bands). The round-1 gap "§6 row for the golden extension" is now closed.
- **Still pending:**
  - the §0 05i `done` row, with the SOLVE counts per OS;
  - the AX38 4c Q1 closure text, waiting for the PR run;
  - the PR description, with "Decided for Maisara".
- **Plan text compared with the code.** Everything matches except the Q1 ordering (Minor 1):
  - D-Q5 in the BUILD_PLAN RG-1 paragraph: 1.20 ×, PROVISIONAL at n = 1–2, print only, re-derived at the 07c re-pin.
  - D-G1 in phase-05i §3.2: the poll interval, `waiting(Synchronous/Offline)`, `solvesCompleted()`, the remainder definition, max poll gap as the resolution, never asserted.
  - The K-e12 record in AX38 4c (3 276 / 2 648 / 3 231 ms) equals the CI logs.
  - The strict 30 s check stays on the flutter scene only.
- **CI.** 43007183782 is green on b94e14f, which I confirmed from the logs.
  - Benchmark: `All tests passed` on Linux, macOS and Windows.
  - The agreement suite prints `560 of 560`, `72 of 72`, max 0.0460 dB and 0 failures on all three OSes.
  - GATE lines: Linux low-α 14 × worst 27.61 s and Windows 28.74 s (both in-window, growth bound asserted), macOS 43.54 s (OVER30S, reported only).
  - K-e12 low-α worst: 3 276, 2 648 and 3 231 ms, so FINDING on every OS.
  - This run does not cover the delta's code.

## Findings (by severity)

### Blockers
1. **The delta's test code has not run in CI (process).** File: `tests/unit/test_diffuse_records.cpp`. Run 43007183782 is on b94e14f and predates the D-Q5, Q1, D-G1 and in-flight code. This resolves when the PR's CI run of record is green on three OSes and its job summary shows the new lines:
   - `solveWarnAt` / `solveBasis` in the GATE lines;
   - the `gate-wait` lines;
   - `build in flight` per K-e12 run.

### Major
None.

### Minor
1. **The code marks two register entries closed before the plan does.**
   - Code: `test_diffuse_records.cpp:115-117` sets `listed=false` for the Linux and Windows low-α entries.
   - Plan: AX38 4c still reads "register entries (Linux 30.27 s, macOS 33.40 s, Windows 36.73 s …) stand", and phase-05i §3.3 (ii) (lines 95-96) still says they "stay listed".
   - The plan editor deferred the closure to the PR's CI run of record. The CHANGELOG says "else the entry stays listed".
   - The effect is print-only, but for the length of the PR run the code and the plan disagree. If the PR run puts either entry over 30 s, the code has to go back to `listed=true`. Windows' margin is 28.74 s against 30 s, about 4 %.
   - **To resolve:** land the AX38 4c Q1 closure text in the same push that records the PR run (atomicity, phase-05h §8). Or keep `listed=true` until then; the existing `PASSES30S` warning already prints the evidence.
2. **K-e12's summary line ignores the in-flight flag** (`test_diffuse_records.cpp:1414-1431`).
   - The summary's min, median and worst still pool all 10 runs, including any printed `build in flight: no`.
   - `builderIdle() == false` also holds while an edit is pending but its build has not started (≤ 1 build / 20 ms coalescing). "In flight" therefore means "the builder has work", not "a solve is running".
   - **To resolve:** print the number of in-flight runs in the summary line, and the worst among them. Name the flag "builder busy" (or say pending-or-building) so H1-F1's condition is not read either way.
3. **Provenance residue** (`tools/validation/compute_phase05i_bras_references.py:122-140`).
   - `write_provenance` merges `{**old, …}`, so the hand-written `tool_commit_note` and `machine` keys survive every rewrite. Nothing marks them as written by hand, so they read as script output.
   - `tool_dirty_at_write`:
     - it checks only the script file, not `hybrid_fast.py`, `ref_hybrid.py` or `phase05b.py`;
     - with `--provenance` (keep_commit) it describes the tree at rewrite time, not at the run;
     - it currently reads `false` for a rewrite done at 8199f86, which says nothing about the 2c11610 run.
   - **To resolve:** either rename the field to `tool_dirty_at_provenance_write` and extend it to the recipe's three modules, or move the hand notes under a `notes_by_hand` key.
   - `--check --check-chunked` together silently runs only the chunked check. That is a nit.
4. **The gate-wait split's attribution rule and robustness** (`test_diffuse_records.cpp:1001-1060`).
   - **Attribution.** queue(Synchronous) counts every interval in which *any* Synchronous waiter exists anywhere in the process. In record (d) that is only the measured pipeline, because the churn instances rebuild in the Builder class. phase-07c-1 condition 12 re-runs this "unchanged", though, and a scenario with other synchronous callers would book their waits as this call's queue. Say "process-wide waiter count" in the printed line, or record (d)'s premise in a comment.
   - **Exceptions.** If `call()` throws, `prepare` and `restore` are not `noexcept`. The `std::thread poller` would then be destroyed while joinable, which ends in `std::terminate` instead of a Catch2 failure. A small RAII guard (set `running=false` and join in a destructor) fixes it.
   - **Thread safety: no problem found.**
     - Only the poller writes to `samples`, which is read only after `join()`.
     - `started` and `running` use acquire/release.
     - `waiting()` and `solvesCompleted()` each lock the gate's mutex.
     - The two `waiting()` reads per sample are not one snapshot, which is negligible at 1 ms.
     - The pipeline's gate is `DiffuseSolveGate::shared()` (`ScenePipeline.h:204`), so the test inspects the same gate the pipelines use.
     - The poller's ~1 kHz mutex traffic is an observer effect the record states.

### Questions (evidence requested)
1. **New record lines in the PR run.** Does the PR run print the D-Q5 `warnings=` (any SOLVE?), the closed-register lines on Linux and Windows (`passes 30 s (register entry closed …)` or `OVER30S on a closed register entry`), and the gate-wait lines, with polls > 0 and a sane max poll gap on Windows (timer quantum)?
2. **Second Windows run.** Was run 42964823518, the second Windows solve baseline, in-window on Windows under the RG-1 ±5 % rule? I did not read that run.

## What I verified myself
- **Diffs read in full:**
  - `git diff f1d372a..b83345c` (script, agreement comment, records wording, provenance);
  - `git diff b83345c..ee25421 -- tests/unit/test_diffuse_records.cpp tests/golden/CHANGELOG.md`;
  - the plan-text deltas, scanned for the AX38 4c, D-Q5, D-G1 and K-e12 entries and phase-05i §3.2 / §3.3.
- **Compiled the head records test** (`git show ee25421:tests/unit/test_diffuse_records.cpp`) with `g++ -std=c++20 -fsyntax-only -Wall -Wextra -Wpedantic -Wshadow -Werror` and with `clang++` using the same flags, against the repo headers and the local Catch2 (`build/release/_deps`). Both are clean. MSVC /W4 was not checked.
- **Formatting:** `clang-format` 18.1.3 makes no changes to that file.
- **CI run 43007183782 logs read** (build linux 130477545194, windows 130477545065, macos 130477545158): the lines above, which match the CHANGELOG constants and the BUILD_PLAN K-e12 record.
- **Gate source read:** `src/plugin/core/DiffuseSolveGate.{h,cpp}`. `waiting()` and `solvesCompleted()` lock `mutex_`, `shared()` returns the weak-held singleton, and the pipeline holds the same instance.
- **Working tree:** unchanged.

## Contractor review focus (delta)
- **Record conditions stated beside each number.** These are the gate-wait lines (`:1069-1086`), K-e12 per run (`:1427`) and the GATE SOLVE fields (`:555-575`). Gaps: Minor 2 and Minor 4.
- **CHANGELOG reasons for the new constants.** The two 05i entries; the constants trace to runs 43007183782 and 42964823518.
- **No per-scene logic.** There is no `src/` change.
