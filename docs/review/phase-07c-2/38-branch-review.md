# Review: branch claude/modest-planck-5xtgzp — phase-07c-2 W_max re-derived under (C), one golden round (session 1 of 2; remainder split to 07c-2b)   (head 79564bb, base main @ 976659c)

Branch review: no PR is open. This review cannot end in Approve.

## Verdict
**Not ready (no CI).** The branch lands four things. (1) Scope 10's carrier commit (5b65864). (2) Scope 11, H-2c: the realtime diffuse solve runs as a task on the gate's process-wide executor, the builder never waits, a per-generation cancel token is added, and the pool takes shares on `size() - 1`. (3) The D-W2 ABX kit: render_cli `--abx-step-db/--abx-step-sample/--w-multiplier`, `tools/ci/abx_kit.py`, the run sheet, and a THIRD_PARTY row for McGill TSP. (4) The board files 1–36, plus a two-session split into `phase-07c-2b.md` that carries W_max, the ABX run, class (c), the interim check, the re-pin, the golden round, O7 and O12.

The H-2c code reads correctly. I found no race, lifetime or determinism defect, and the share-limit D4 test and the six `[h2c]` tests pass locally. The only run of record so far, 45023654411, covers Windows only. Run 45040709474 on the head 79564bb is still running (queued or in progress at review time), so M7 on Linux and macOS and the TSan stress are unproven.

The most important finding is a blinding leak in the ABX kit. `seal()` commits the SHA-256 of X next to A and B, and X is a byte copy of one of them. The committed record therefore reveals every answer (B1). 07c-2b puts the kit out of its scope, so this must be fixed here.

**What would flip it:** fix B1 and M1, and get run 45040709474 (or a later run on the final tree) green on all three OSes with the 07c2-m7 lines present. That would leave a PR that can be opened.

## Process gate
- **Scope:** every hunk belongs to 07c-2 scopes 9, 10 or 11, the board record or the split. There is one exception: `test_diffuse_wsweep.cpp` (hidden `[.][wmax-sweep]`, not run in CI) is validation instrumentation for D-W1 (fact sheet part 2). That is acceptable as O4 evidence work.
- **Dependencies:** 07c-1 (PR #32) and 07c-1b (PR #33) are `done` on main 976659c, which the brief records.
- **Status table / §6:** the 07c-2 row is `in progress` (deliberate). A 07c-2b row is added `not started`. The 07c and 08 rows are updated. §6 has two rows: the P07C1B-R1 re-list, and the 07c-2 loop (AX47, AX49, the D-W3 routing, D-W4). AX47 and AX49 in §2 are edited to match.
- **Assumptions used:** AQ4, AX18 (equal-gain step in render_cli), AX38 (i) (gate held around the solve), AX41 (stop points by block count; W pinned), AX5 (offline path unchanged). New uncited constant: `DiffuseSolveGate::kExecutorThreads = 2` (m1).
- **Boundary & contract:** `review_context` finds no boundary violation and no contract change. The NFR-8 hit `Engine.cpp:851` (`emitter.id == "L"`) is pre-existing (main L850), not this diff.
- **Goldens/tolerances/skips:** no golden file changed. The CHANGELOG entry is the records-test flag only. `test_abx_kit.py` skips without numpy in the contract-tools job (reason stated) and without render_cli unless `SPATIAL_REQUIRE_RENDER_CLI=1` (honoured).
- **PR description sections:** no PR, so not available. Brief "Decided for Maisara" still reads "(none yet)", although D-W2, D-W3, M1 and M2 were answered (m3).
- **CI:** run 45040709474 is on head 79564bb (confirmed with `actions_get`). Done so far: changes, clang-format, and contract tools (linux, macos) are green. Everything else is in progress or queued. The earlier run 45023654411 (87a62d5) was red on Linux, macOS and contract-tools. I could not check artifacts (`listening-pack`) because the run has not finished.

## Acceptance criteria audit
| # | Criterion (phase file) | Test(s) | Reference | Tolerance | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | W_max re-derived, golden round (A6) | none | — | — | — | — | moved to 07c-2b scope 6/8 (split); not marked in phase-07c-2.md (M1) |
| 2 | Phase 12 (ii) preset check (A9) | none | — | — | — | — | moved to 07c-2b scope 9; not marked (M1) |
| 3 | Interim stream check (D1) | none | — | — | — | — | moved to 07c-2b scope 5; not marked (M1) |
| 4a | solve off builder; B1′ without waiting; no adoption in motion | `test_interim.cpp` "Scope 11 (H-2c): an edit during a running solve…" | self (stage hook parks the solve in the gate) | exact counts | pending (45040709474) | none found; deterministic | proven locally, CI pending |
| 4b | finals bit-identical with/without cancelled predecessors | "…bit-identical with and without cancelled predecessors (D7)" (0 vs 3) and `buildIr` | independent one-shot build | bit-exact | pending | a predecessor that finishes instead of being cancelled (it asserts `solves == +1`, so this would be caught) | proven locally, CI pending |
| 4c | share limit never changes result | `test_diffuse.cpp` "…independent of the pool's share limit" (1/3/4 threads, stop mid-batch) | 1-thread pool | bit-exact | pending | — | proven (ran locally) |
| 4d | TSan stress: random solve points, destroyed mid-solve | "Scope 11 (H-2c) stress…" `[pipeline]` (TSan job runs it) plus gate tests "waiting at the gate / queued" | TSan | 0 reports | pending | a use-after-free only while a task is **running inside the solve** at destruction: hit only by chance, no assertion that it happened (M2) | weak |
| 4e | offline bit-identical; `[reset-nowait]` | existing tests (offline path unchanged in diff) | — | — | pending | — | pending |
| 4f | B1-b re-run with solve duration printed | `test_diffuse_records.cpp` `07c2-b1b` print; summary grep pinned by `test_ci_workflow.py` | record | — | Windows only (45023654411, file 36) | — | pending (2 OSes) |
| 4g | M7 ≤ 700 ms worst OS, flat in m; M7b recorded | `test_m7_hold.cpp` `[.][benchmark][m7-hold]`, **records only** | print | none asserted | Windows: worst 81.1 ms (file 36); Linux and macOS pending | a regression above 700 ms or a non-flat hold never fails CI (Q1) | not proven (2 OSes missing) |

## Findings (by severity)
### Blockers
1. `tools/ci/abx_kit.py:782-817` (`seal`): `X.wav` is a byte copy of A or B (`shutil.copyfile`). `record["stimuli_sha256"]` stores the SHA-256 of A, B **and** X per trial, and is written to `<session>/prereg_hashes.json`. That file sits in the listener's folder and, per run sheet §3 L111, is committed before the run. `sha(X) == sha(A)` reveals every answer, which defeats D-W2 item 11 (blinding, file 13 L190). AX47's and AX49's reversals read from this ABX. 07c-2b's Out of scope lists the kit as delivered, so no later phase owns the fix.
   - **Resolves it:**
     - Commit only the hashes of A, B and the key, not of X. Alternatively, commit a salted hash of the X set.
     - Keep `prereg_hashes.json` out of the session folder.
     - Add a test: the committed record never contains a digest equal to another entry's digest.
     - Update run sheet §3 to match.

### Major
1. `docs/phases/phase-07c-2.md` (Acceptance criteria, L177-194; Listening checklist): the split is recorded in §0, in `phase-07c-2b.md` and in the brief (G17). This file still lists AC 1–3 and both listening items unchecked, with no "moved to phase-07c-2b" note. The 07c-1 precedent marks each one in the phase file (phase-07c-1.md L245, L278-284). Setting §0 to `done` against this file as it stands would be "`done` with criteria not proven" (process-rules §2).
   - **Resolves it:** a `/fix-plan` edit marking AC 1–3, L1 and the ABX item, and scopes 3, 8 and 9's open parts, as moved to 07c-2b, as 07c-1 did.
2. `tests/unit/test_interim.cpp` (stress test, "destroyed mid-solve" branch, around +L1080-1095): destruction happens after a 0–8 ms sleep and the `HostAudio` join on `dead_booth`. Nothing asserts that a task was Running inside the solve at the moment of destruction. The deterministic gate tests cover only the waiting-at-the-gate and queued states. The criterion "pipeline destroyed mid-solve" therefore rests on chance.
   - **Resolves it:** a deterministic section that parks the solve in the stage hook (as the first `[h2c]` test does) and destroys the pipeline. Alternatively, count and print the stress iterations destroyed with a running task and require at least one.

### Minor
1. `src/plugin/core/DiffuseSolveGate.h` (`kExecutorThreads = 2`): a new process-wide concurrency constant with no AX or decider citation. It sets how many superseded solves can unwind before a new instance's task starts.
   - **Resolves it:** cite D-W3/H-2c file 19 for it, or record it there.
2. `src/plugin/core/ScenePipeline.cpp` (`decide`, superseded branch: `++stats_.discardedMidDrag`): the counter now also counts solves stopped before they finished, while H-0's `discardedMidDrag` counted completed-but-discarded solves. M7b is read "against H-0's `discardedMidDrag`" (scope 11 item 7).
   - **Resolves it:** document the changed meaning in the `Stats` comment and in the M7b record, or split the counter.
3. `docs/sessions/2026-11-22-phase-07c-2.md`: the steward log stops at round 4 (G14–G21 open), and "Decided for Maisara" reads "(none yet)".
   - **Resolves it:** steward rounds through READY TO REPORT, and the decided list (D-W2, D-W3, D-W4 home, M1, M2, with PRD ids).
4. `docs/phases/phase-07c-2b.md` "Dependencies": it cites board files "1–34", but the record runs to 36 (file 36 is scope 1's evidence).

### Questions (unverified, evidence requested)
1. M7's "worst over ≥ 3 runs" and "flat in m" have no numeric test, and the instrument asserts nothing.
   - Does "runs" mean the 10 edits per point, or ≥ 3 CI runs?
   - What flatness rule will the PR apply?
   - Evidence: the per-OS table from 45040709474 with the rule stated. If a numeric flatness rule is wanted, it is a threshold for the decider, not for this branch.
2. Run 45040709474: green on Linux, macOS and Windows (build, TSan, ASan, python with the `listening-pack` artifact holding phase-07c-2's noise chain)?

## What I verified myself
- `fetch_pr.sh` resolved BASE origin/main and HEAD 79564bb. I ran `review_context.py` and read its output.
- I read, at head:
  - the diffs of `src/sim` (ThreadPool, estimator batch, Engine), `src/plugin/core` (gate executor, ScenePipeline) and `src/cli/Cli.cpp`;
  - all new or changed tests;
  - `abx_kit.py`'s `seal`, `fetch_tsp` and the seeds;
  - the `ci.yml` and `test_ci_workflow.py` diffs;
  - the phase file, 07c-2b, the brief, §0, §6, and files 20 and 36.
- Re-derived the stepped diffuse level in `buildAbxStep`: E'_diff = k·E_diff + (k−1)·E_spec, so E'_target = k·E_target. This is correct.
- Checked the estimator pilot: the stop test runs per block in index order, so the batch size (now `shareThreads()`) cannot change n\*, the hash or the result.
- Checked the lost-wake ordering (`ready` before `mailbox_`, cleared before read), owner lifetime (`settleJobs` before `builder_.reset()`), the executor join before `pool_`, and `makeIrSet` against `engine_.reset()` (it reads only `sampleRate_` and `partitionSize_`).
- Confirmed the carrier flips `listed` (field 8) only.
- Ran from the existing `build/release` (built from the head `src`; only 582e485's test-only fix is newer):
  - `spatial_tests "*pool's share limit*"`: passed (196 assertions);
  - `spatial_tests "[h2c]"`: 6 cases, 142 assertions, passed.
- Did not run TSan, pytest or the M7 benchmarks.
- CI: `actions_list` and `actions_get` on 45040709474 (head SHA matches; still running).
- Reference gap: `phase-checklists.md` has no 07c-x section, so I used Phase 07's.

## For Maisara
- **Listening checklist:** untouched. It is yours, and both items moved to 07c-2b.
- **Listening pack:** the `listening-pack` artifact of the green run will hold `phase-07c-2/noise`, the pre-registered ABX stimuli. Do not listen before sealing.
- **Speech chain:** built locally only.
- **Fix B1 before sealing:** until B1 is fixed, the committed hashes would give away the ABX answers.

## Contractor review focus (from the phase file), with pointers into the diff
- The W_max re-derivation from the background budget (phase-07c F6): not in this diff. It will live in `src/sim/diffuse/DiffuseEstimator.h` (`kWMaxPerEmitter…`) under 07c-2b scope 6.
- The instrument it rests on:
  - `ScenePipeline::setDiffuseLimitsForTest` and `BuildOptions::diffuseLimitsOverride` (nullptr in product paths, with a test that the default is the shipped limits: `test_m7_hold.cpp:530`);
  - `render_cli --w-multiplier`.
- Review H-2c in `ScenePipeline::decide`/`runSolveJob`/`settleJobs` and `DiffuseSolveGate::post`/`Task`.

## Dispositions

Added by the orchestrator, 2026-11-22.

| finding | disposition | commit / evidence |
|---|---|---|
| B1 (seal leaked X) | Fixed. Each A, B and X file gets its own secret salt, held in the key. The pre-registration record holds the key's SHA-256 and a salted SHA-256 of every file, and is written beside the key, not in the session folder. `score --session` checks the session folder and the key against it. The suggested "commit A and B hashes only" was not used: X equals A or B byte for byte, so plain A and B hashes would still let anyone holding X find the answer. | 90e4eda (`tools/ci/abx_kit.py`, `tools/ci/test_abx_kit.py`, run sheet §3) |
| M1 (split not marked in the phase file) | Fixed through `/fix-plan`: every moved scope, criterion, listening item and the contractor focus is marked "moved to phase-07c-2b"; interrogator diff check CLEAN, its two wording findings applied. | ff1f414, 1b2f700; file 37 |
| M2 (mid-solve teardown rests on chance) | Fixed: a deterministic "running inside the solve" section in `tests/unit/test_diffuse_gate.cpp` parks the task inside the solve and destroys the pipeline. Release and TSan, 5/5 local runs green. | 90e4eda |
| m1 (`kExecutorThreads = 2` uncited) | Fixed: comment cites D-W3 / H-2c and file 19. | 90e4eda (`src/plugin/core/DiffuseSolveGate.h`) |
| m2 (`discardedMidDrag` meaning changed) | Fixed: the `Stats` comment documents that it now also counts superseded solves stopped before they finished. | 90e4eda (`src/plugin/core/ScenePipeline.h`) |
| m3 (brief: steward log, "Decided for Maisara") | The brief's "Decided for Maisara" section is filled (task G23); the steward log is carried through the remaining steward rounds. | session brief `docs/sessions/2026-11-22-phase-07c-2.md` |
| m4 (07c-2b cites files 1–34) | Fixed: 07c-2b cites 1–36. | ff1f414; file 37 item 3 |
| Q1 (M7 "worst over ≥ 3 runs", "flat in m") | Answered by the final three-OS CI run's per-OS `07c2-m7` table. | run 45045891476 |
| Q2 (three-OS green, TSan, ASan, `listening-pack`) | Answered by the final three-OS CI run. | run 45045891476 |
