# Review: PR #27 — phase-05h (session 1 of 2) diffuse-energy estimator in src/sim/diffuse, C++ costs for D-H1   (head 5a0be96, base main c821b7b)

## Verdict

**Request changes. Nothing blocks the merge.** The PR adds the AX39–AX44 Monte Carlo diffuse-energy estimator as a
stand-alone unit, `src/sim/diffuse/`. Nothing calls it yet: `git diff origin/main...pr/27 -- src/sim/Engine.cpp src/sim/tail
src/contract src/plugin src/module3d` is empty, so shipped audio is unchanged (phase-05h §8 atomicity holds).
The PR also adds unit tests, a hidden smoke-agreement test against `ref_hybrid`, one new golden made by a script, and
the C++ cost data for D-H1.

I compared the code with the prototype (`phase05b2_dt1.py` `mc5`, `_Prep`, `n3w_joint`, `tally_stats`, `summarise`,
C16b) and with the AX39–AX44 text. The transport model, NEE gather, window, referral, NW-4C blend, joint rule, flags,
statistics and U match. I found no wrong physics, no race and no determinism break.

Every session-1 criterion is green in run 42846229834, which was run on the identical code tree (Linux, macOS,
Windows, ASan + UBSan). The later commits change only fingerprint-excluded prose. The smoke result is
max |C++ − ref| 0.0247 dB, and the printed per-case/band lines are identical on all three OSes.

**Most important finding:** every agreement and determinism test runs **one emitter**. The shipping configuration
is two emitters sharing one listener-started set (AX41, AX44). A mutation that gathers emitter 1's reverse scores at
emitter 0's images passes every test, including the smoke test (Major M-1).

What would flip this to Approve: M-1 (a two-emitter test), M-2 (`[diffuse]` added to the TSan job) and M-3 (one
sentence fixed in the cost write-up). All three are small. They can go in before the merge, or be the first commits
of session 2 if Maisara prefers to merge now. Session 2 is the PR that wires the estimator in.

## Process gate

- **Scope.** Every hunk is phase-05h scope 1 (the estimator part) or the data half of scope 6. Bookkeeping: brief,
  §0 note, cost write-up. No other phase's work is in the diff. The matching switch, `TailMatch.approximate`, the
  FTZ guard and the gate are correctly left out and listed in the brief's hand-off.
- **Dependencies.** 05b (`done (not promoted …)`), 05f `done` and 07 `done` at merge-base c821b7b.
- **Status table / §6.**
  - The first commit (9085aa8) sets `in progress`. The row stays `in progress` with a session-1 note. Its numbers
    match CI (below).
  - There is no §6 row for the new golden (review_context warning). The phase file puts §6 bookkeeping in scope 7
    (session 2). Acceptable if session 2 adds it (m-7).
- **Assumptions used.** AX39 D1–D7, AX40, AX41, AX42, AX44 and AX4 are used as written and cited in code. The
  constants match AX41/AX42/AX44: block 64, final start 8 000, n\*_max 1 024, W_max 3.05 M per emitter, SE target
  0.083 dB, 0.70 m, 0.33 dB, VOV 0.1, union 8 000, pilot floor 1 000.
- **New or changed assumptions.** None.
  - The generator (SplitMix64 counter fold), the samplers (cube rejection, Malley) and the key packing are
    implementation choices inside AX39 D1, recorded in `Sampling.h` comments, as the brief allows.
  - Two small deviations from the prototype, both documented: `kDbPerRelative` is 10/ln 10 instead of 4.343 (a
    2.5e-5 relative change in N_need), and W_scene is exactly 6.10 M instead of 6 098 823.5. Neither is a decision.
- **Boundary and contract.** `check_boundaries.py` OK (run locally). No JUCE in `src/sim`. Contract unchanged. The
  NFR-8 scan hit (`Engine.cpp:418`) is pre-existing and not in this diff.
- **Goldens / tolerances / skips.**
  - One new golden, `tests/golden/phase05h_dt1_smoke_reference.json`, written by
    `tools/validation/export_phase05h_smoke.py`, with a CHANGELOG entry. Phase-05h scope 5 allows new goldens "created
    by script with its reason in the CHANGELOG".
  - I checked the golden against `tools/validation/data/phase05b.json`: relative difference 0. Max ref change
    2.5 → 1.25 m is 0.325 % = 0.0141 dB, which equals the test's `kEllRefDb` of 0.014.
  - No existing golden changed. τ = 0.25 dB and z = 4.290 match AX42/AX43 and the brief's pre-registration. No skips.
- **PR description sections.**
  - Present: what was done, acceptance evidence with the run link, listening checklist ("none this session"),
    contractor focus, follow-ups.
  - Missing: a separately headed "Assumption / golden changes" section. The content is in "What was done" (m-7).
- **CI.**
  - Head 5a0be96 has **no check runs**; its run was cancelled on purpose.
  - Evidence run 42846229834 (head f3e3603, attempt 2): all 32 latest-attempt jobs succeeded, including build
    linux/macos/windows, ASan + UBSan, TSan, python ×3, contract ×3, tail gates ×18 and `ci ok`. The macOS
    concert_hall_box job was cancelled in attempt 1 and succeeded in attempt 2.
  - `git diff --stat f3e3603 pr/27` touches only `docs/BUILD_PLAN.md`, `docs/review/…` and `docs/sessions/…`, all in
    the `ci_fingerprint.py` exclusions (lines 33, 34, 44).
  - Run 42853505511 (head 721e8d7): `ci ok` succeeded with every other job skipped. I did not read its summary text,
    only the job conclusions.
  - Logs read (downloaded and grepped): build linux / macos / windows and ASan jobs of 42846229834.
  - Re-trigger CI on the final head before merging, so the merge commit carries its own `ci ok` (m-8).

## Acceptance criteria audit

The session-1 rows come from the brief's O3–O7, which map to phase-05h §5. The §5 rows the brief hands to session 2
are marked "not in this PR", and that is not a finding by itself.

| # | Criterion | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | RNG known-answer test, no `<random>` (AX39 D1, D3) | `diffuse RNG known-answer vectors (AX39 D3)`; `tools/ci/test_diffuse_sources.py` | 4 KAT vectors. I re-derived all 4 in an independent Python implementation: equal | exact | Passed on all three OSes and ASan (42846229834) | A bias in the samplers that passes the first-moment checks (only E[z] and E[cos] are checked) | proven |
| 2 | D2 flags, no fast-math | `test_fp_contract_flags`, `test_no_fast_math_anywhere` | source grep | — | python tools ×3 green; local 5/5 pass | Path-deciding inputs computed outside the flagged files (`MixingTime.cpp` etc., m-3) | proven for the unit |
| 3 | D4: estimate independent of pool size, repeatable | `…independent of the pool size…` (pools 1/2/4); hidden bench `REQUIRE(r.faceHash == first.faceHash)` (pool 1 vs process pool) | self (bit equality) | exact | Unit test on all three OSes; the bench ran pool 4 (Linux, Windows) and pool 3 (macOS) | **Unit test:** the pilot stop applied per batch instead of per block. My mutation M2 passed `[diffuse]`, because the small room stops on n\*_max, which pool sizes 1/2/4 divide. The hidden bench at the flutter scene (pilot stopped by work, n\* 320) would catch it on a runner with more than one thread (m-1) | proven (via the bench) |
| 4 | D5 face hash, n\* and N equal on three OSes | bench prints the hash, n\*, N and W | cross-OS printout | exact | Identical on gcc, Apple clang arm64, MSVC (I diffed the logs) | Nothing asserts it yet; the golden is session 2 | partly (hand-off says so) |
| 5 | D6 stop flag between blocks | `diffuse solve stops between blocks when asked` | self | ≤ k + pool − 1 blocks | all OSes | A missing stop check in the final range (only the pilot is cancelled in the test) | proven for the pilot |
| 6 | D7 / AX41 joint rule, integer arithmetic, flags | `diffuse joint path-count rule and its flags` | hand-computed integers | exact | all OSes | Small: every flag and the rounding have a case. No overflow case (m-5) | proven |
| 7 | NW-4C weight, both-near at 0.70 m, U truth table (AX44) | `diffuse NW-4C weight…` | hand-computed values, 16-row truth table | 1e-15 | all OSes | — | proven |
| 8 | R, VOV, slope, union VOV (AX41/AX44) | `diffuse tally statistics…` | hand-computed; Pareto slope | 1e-15 / 0.15 | all OSes | The union-VOV assembly (pilot then final, capped at 8 000) is not unit-tested; checked by reading against C16b | proven (statistics), reading (union) |
| 9 | AX40: no tailSeed dependence | `diffuse estimate does not depend on tailSeed` | self | exact | all OSes | Trivial by construction (`kDiffuseSeed`) | proven |
| 10 | Smoke agreement with `ref_hybrid`, 15 (A) cases × 8 bands, N 131 072, z 4.290, τ 0.25 dB (O5) | `[.][benchmark][diffuse-agree]` | **independent:** `ref_hybrid` at ℓ 1.25 m, committed data | 0.25 dB and z·SE ≤ 0.236 dB / AX42 τ 0.25 | Linux, macOS, Windows Release benchmark step: max 0.0247 dB, \|z\| 1.77, SE 0.0244 dB; 120 lines identical across OSes | **Anything specific to two emitters** (M-1); per-face scattering indexing (every case has uniform s); per-band α mapping (α broadband in every case) (m-10) | proven for one emitter |
| 11 | Finite, ≥ 0, no denormals at the estimator level | pool-size test asserts | — | — | all OSes | Denormals inside intermediate weights (only outputs are checked) | proven (outputs) |
| 12 | Not wired into `matchTail` / `planEmitter` (O3 l) | `git diff` | — | — | empty diff (verified) | — | proven |
| 13 | C++ cost data for D-H1 (O6) | hidden `[diffuse-cost]` | measurement | — | numbers in the write-up match the logs on three OSes | The flutter scene's "ns per evaluation" includes discarded speculative pilot blocks (m-2); one sentence mis-states Seat 1's rule (M-3) | recorded |
| 14 | pluginval 10 / auval unchanged | CI | — | — | build jobs green on all three OSes; pluginval 1.0.4 log present (macOS) | — | proven |
| §5 | D-H1 AX change; the 70-case / 560-case-band agreement; AX46; tracer ±1 dB; AX45 + M-2; D5 golden + cross-OS E_target comparison; U at defaults + W1 both_corner cap flag; realised-work assertion; `open_field`; `--diagnostics`; FTZ `[pipeline]`; gate + TSan two pipelines; W1/W2 + memory; blocking restore gate; solve seam; clause (d) replicates; goldens / BRAS nightly | — | — | — | — | — | **not in this PR (session 2)**; the brief's hand-off lists every one with its state |

## Findings (by severity)

### Blockers

None.

### Major

1. **M-1: two-emitter behaviour is untested.**
   - Where: `src/sim/diffuse/DiffuseEstimator.cpp:187-205` (`runHistory`) and `:244-264` (`prepare`, per-emitter
     gathers); tests in `tests/unit/test_diffuse.cpp:331-389` (smoke, one emitter) and `:245-327`.
   - The problem: the smoke agreement builds one emitter per case. The unit tests that do use two emitters
     (`smallScene`) check only self-consistency: pool size, tailSeed, finite, > 0. In shipping there are always two
     emitters, sharing one listener-started set that runs to max_e t_mix,e and gathers at each emitter's images with
     that emitter's window (AX41 "History", AX44 "one listener-started set serves both emitters").
   - The evidence: I changed `:261` to `rev.lists = &p.emitterLists[0];` (emitter 1's reverse scores gathered at
     emitter 0's images), rebuilt, and **`[diffuse]` still passed**. The smoke test cannot see it either, because it
     has one emitter. Other bugs it would miss: a wrong `norm` or window for e = 1, a `sc.rev` index mix-up, a wrong
     `reverseEndS`.
   - Why it matters: it is a correctness risk that no test covers, in exactly the configuration session 2 switches
     on. It is also the contractor focus "equivalence of `tracePath` to `mc5`".
   - The fix is cheap and exact. The listener-started trajectory is keyed by `kSharedEmitter` and does not depend on
     the gather. So in a fixed-N run, the per-emitter reverse scores of a two-emitter problem must be **bit-identical**
     to those of the one-emitter problems {listener, emitter e} (the prototype says the same in its `n3w_joint`
     comment).
     - Expose the per-end tallies (or the scores, under a test hook) and assert that.
     - For the forward set of emitter 1, assert statistical agreement with the one-emitter run at that source (same
       z·SE rule), or run the smoke cases with a second, distinct emitter.

2. **M-2: the new thread pool has no race-detector evidence.**
   - Where: `src/sim/diffuse/ThreadPool.cpp` (whole file); `.github/workflows/ci.yml:474`.
   - The TSan job runs `"[conv],[pipeline]"` only. The `[diffuse]` tests, which drive the pool at sizes 2 and 4 and
     exercise the stop path, never run under TSan.
   - My reading found no race and no deadlock:
     - `epoch_` / `active_` / `next_` are all under `mutex_`.
     - Late wakers find `next_ >= count_` and leave.
     - Results are published to the caller through the mutex release in `--active_`.
     - Concurrent callers are serialised by `runMutex_`.
   - The contractor focus names "`ThreadPool` correctness" and process-rules §9 asks for TSan on new threading code.
   - Resolve: add `[diffuse]` to the TSan filter. It runs in under 1 s in Release, more under TSan but small.

3. **M-3: the cost write-up mis-states Seat 1's floor rule.**
   - Where: `docs/review/phase-05h/1-orchestrator-cpp-costs.md:47`.
   - The write-up says the floor "is **not met** at `cube100_lowalpha0.05_s1` … **unless clause (d)'s replicates
     pass**".
   - Phase-05h §3 (decider file 53 §1) says the floor is met only when the achieved SE is ≤ 0.33 dB **and** one of
     (a)–(d) holds. With SE 0.36 dB, clause (d) cannot rescue it.
   - This document is the board's input for D-H1 and for "Raise with Maisara" item 1. Wrong evidence wording there can
     change the decision.
   - Resolve: replace that clause with "not met (SE 0.36 dB > 0.33 dB, from one realisation; the joint-rule
     replicates of the reported set, session 2, establish the starting state)".

### Minor

1. **m-1: the unit test for D4 misses the branch where pool size matters.**
   - Where: `tests/unit/test_diffuse.cpp:245-278`.
   - The branch that depends on pool size (pilot stopped by **work** in the middle of a batch, later blocks
     discarded) is covered only by the hidden benchmark (`test_diffuse_bench.cpp:135,151`). Debug, ASan and local
     runs never see it.
   - My mutation M2 (stop test applied once per batch: `used = to`) passed `[diffuse]`.
   - Add a `[diffuse]` case with `DiffuseLimits::wScene` small enough to stop the pilot on work, for pools 1, 3 and 4.

2. **m-2: discarded speculative pilot work is not counted.**
   - Where: `src/sim/diffuse/DiffuseEstimator.cpp:491-506` and the cost write-up §3.
   - Blocks past the pilot stop are computed in pool-sized batches and discarded. `realisedWorkRatio()` excludes
     them, which is correct for AX41's "work", but the cost write-up's "ns per image evaluation (median solve /
     realised work)" then includes their time.
   - At the flutter scene (e_hist ≈ 9 857, n\* 320 = 5 blocks), pool 4 computes 8 blocks: 3 discarded ≈ 1.89 M
     evaluations, +33 % over the 5.70 M counted. That explains part of the 28.3 vs 16.4 ns figure.
   - On a 16-thread user machine the whole 16-block pilot runs in one batch: about 1.6 × W_scene of CPU at that scene.
     Wall time is roughly unchanged, but CPU load matters for AX38 (iv)'s 8 instances.
   - Session 2's W_max re-derivation "from the C++ cost at the CI runner's pool size" should take the per-evaluation
     cost from the n\*_max-stopped scenes, or the diagnostics should report the speculative work.

3. **m-3: some values that decide paths are not deterministic by construction.**
   - D1 says no libm may enter "any value that decides a path", and D2 applies only to the three unit files.
   - N_need is computed from pilot variances of scores that contain `std::exp` / `std::sin`
     (`DiffuseEstimator.cpp:114,132,153,157`). So N, which decides the shipped path set, is equal across OSes with
     very high probability, not by construction.
   - t_mix,e and the window start (`t < endS` decisions) come from `MixingTime.cpp`, which is built without
     `-ffp-contract=off` (Apple clang defaults to `on`). It looks contraction-free today (sqrt and add only).
   - CI shows equal hashes and N on four scenes, so this is not a defect. When wiring, say so in the AX5 note, or
     extend D2 to the plan inputs.

4. **m-4: constants are duplicated.**
   - Where: `DiffuseEstimator.cpp:17-19`.
   - c = 343, 13.8155… and 10 ms are copied from `ism::kSpeedOfSoundMps` / `tail::` instead of being referenced. A
     later change to one side would desynchronise the specular target and the diffuse part.
   - Use the originals, or add a `static_assert` that they are equal.

5. **m-5: `DiffuseLimits` is not validated.**
   - Where: `DiffuseEstimator.h:81-88` and `DiffuseEstimator.cpp:361`.
   - Nothing stops `nStarMax > 8000`. That would make the pilot overlap the "fresh" final range
     [8 000, 8 000 + N) (AX41).
   - `(wScene − wPilot) * nStar` is unchecked for arbitrary limits.
   - Fine at the pinned constants; add an assert / clamp before these become configurable.

6. **m-6: a missing column reads out of bounds.**
   - Where: `tests/unit/DiffuseTestUtil.h:152`.
   - `col()` returns `size_t(-1)`. A missing or renamed golden column then reads out of bounds (undefined behaviour)
     instead of failing.
   - `REQUIRE` the column exists.

7. **m-7: bookkeeping for the new golden.** There is no BUILD_PLAN §6 row for the new golden (CLAUDE.md "Tests and
   golden files"), and the PR body has no headed "Assumption / golden changes" section. Add both in session 2's
   scope 7 bookkeeping.

8. **m-8: the merge head has no CI run.**
   - Head 5a0be96 has no check runs, because its CI was cancelled on purpose.
   - The skip-evidence chain is valid (42853505511 → 42846229834), but the commit that merges should carry its own
     `ci ok`. It will skip in seconds.

9. **m-9: `parallelFor` is not exception-safe.**
   - Where: `ThreadPool.cpp:75-95`.
   - If `fn` throws on the caller thread, workers still hold `&fn` (a dangling pointer to the caller's stack). If it
     throws on a worker, `std::terminate` is called.
   - Nothing throws today (`runBlock` does not allocate). Document that the job must not throw, or catch and rethrow
     after the join.

10. **m-10: the smoke cases leave per-face scattering and per-band absorption unexercised.**
    - In the smoke cases, s is uniform per case and α is broadband per face. A per-face scattering index bug
      (`p.scattering[axis]` instead of `[f]`) or a per-band α mapping bug would not be seen.
    - Make sure session 2's 70-case suite contains mixed-s rooms; the Phase 04 rooms and flutter-like rooms qualify.

### Questions (unverified, evidence requested)

1. **Q-1: lifetime of the process-wide pool in a plugin.**
   - `ThreadPool::process()` (`ThreadPool.cpp:26-30`) is a function-local static whose destructor joins its workers.
   - Inside a VST3/AU binary that is unloaded (Windows `FreeLibrary` runs static destructors under the loader lock;
     threads exiting then need that lock), this is a known deadlock pattern.
   - It is also unowned, while AX39 says "owned with the AX38 gate", and it sizes itself to `hardware_concurrency()`,
     competing with host threads.
   - Not reachable from the plugin today. How will session 2 own, size and shut it down? pluginval's repeated
     load/unload once wired would be the evidence.

2. **Q-2: is the s = 1 SE from one realisation representative?**
   - The C++ achieved SE at `cube100_lowalpha0.05_s1` is 0.36 dB, against the prototype's 0.44 / 0.50 dB (C16
     nmax1024, same n\* 1 024 and N_cap 2 688). Both come from single realisations of a heavy-tailed estimator (pilot
     VOV 0.39 / 0.75).
   - The write-up already names this as a finding for the board. The Seat 1 starting state should come from the
     reported-set replicates (session 2), not from this single run.

3. **Q-3: the definition of "work" differs from the prototype's.**
   - C++ face lists keep images within c·t_mix + |dims| of the gather point (`FaceLists.cpp:43`). The prototype's
     lattice keeps cells with gap ≤ c·b + 1 m.
   - So C++ can count extra non-contributing "evaluations": images that pass the `dist − d_lr ≤ rem` prune but lie
     further than the prototype's lattice reached. Contributions are unaffected; both sets contain every image that
     can contribute.
   - The measured e_hist is close (1 627 vs 1 636 at s = 1). Confirm that W_max is re-derived on C++ counts, which the
     plan already requires.

## What I verified myself

- **Diff and context.** Fetched the refs with `fetch_pr.sh 27` (BASE origin/main c821b7b, HEAD 5a0be96) and ran
  `review_context.py`. Read every changed source, test, tool and doc file at HEAD.
- **Prototype comparison.** Compared `tracePath` / `runHistory` / `prepare` line by line with `mc5`, `_Prep`,
  `n3w_joint`, `summarise`, `tally_stats` and `step_c16b`, and the joint rule with AX41. All of these are identical
  in model:
  - Lambert gather cos θ/(π r²) with s(1−α) at the hit;
  - image factor ((1−α)(1−s))^hits;
  - air exp(−m r) on each leg, and referral exp(−rate (t_mix − t_a)) through γ = m − rate/c;
  - Hann² window with norm 10 ms / ((b−a)/2);
  - unweighted branching;
  - stop test `2·W_pilot ≥ W_scene`;
  - N_cap = ⌊(W − W_p)·n\*/W_p⌋ rounded down to whole blocks;
  - `capHit = N_need > N_cap`, `floorTruncated = N_cap < n*`, `pilotShipped = N_cap < 64`;
  - union VOV over the pilot then the final range, up to 8 000;
  - U as in AX44.
- **Surface order.** The face order 2·axis + high matches `contract::SurfaceId` (xMin, xMax, yMin, yMax, floor,
  ceiling).
- **Golden.** Recomputed `tests/golden/phase05h_dt1_smoke_reference.json` against `phase05b.json`: exact.
- **RNG.** Re-derived the 4 KAT vectors in an independent Python SplitMix64: all match.
- **Local build** (`cmake --build --preset release --target spatial_tests`):
  - `[diffuse]`: All tests passed (62 567 assertions, 9 test cases).
  - `[diffuse-agree]`: max 0.0247 dB, \|z\| 1.77, SE 0.0244 dB, 557 assertions passed. Same as CI.
  - `pytest tools/ci/test_diffuse_sources.py`: 5 passed. `check_boundaries.py`: OK.
- **Mutations.** Both were reverted, with the file restored from a copy; `git status` is clean for `src/` and
  `tests/`, and the binary was rebuilt from the original.
  - M1 (`rev.lists = &p.emitterLists[0]`): `[diffuse]` passes. This is the M-1 evidence.
  - M2 (pilot stop applied once per batch): `[diffuse]` passes. This is the m-1 evidence; the hidden bench's
    pool-1-vs-pool-N hash `REQUIRE` would catch it.
- **CI.**
  - `actions_get` 42846229834: success, attempt 2, head f3e3603. `list_workflow_jobs` latest: 32/32 success.
  - Downloaded the logs of build linux, macos and windows and of ASan. Grepped: the 9 `[diffuse]` ctest cases passed
    on all four; the 120 smoke lines are identical across the three OSes; the `05h-cost` lines (hash, n\*, N, W,
    flags, per-emitter SE and VOV) are identical across the three OSes; the timing numbers match the write-up's
    tables and the PR body.
  - 42853505511: `ci ok` success, other jobs skipped. PR head 5a0be96: no check runs.
- **Gaps in the skill's references.** `references/phase-checklists.md` has no Phase 05b or 05h section, so I applied
  the phase file directly. The skill's references should gain a 05h entry.
- **Not run.** TSan on `[diffuse]` (no tsan build here), Debug/ASan locally, and the macOS auval output, which I did
  not grep (the job is green).

## For Maisara

- **Listening checklist:** untouched; it is yours. Nothing audible changed in this PR (the estimator is not wired
  in), so there is no `phase-05h` listening pack yet. It comes with the switch in session 2. Plugin artifacts from
  run 42846229834 are unchanged-behaviour builds.
- **For the Expert / board (D-H1).** On the C++ data, the closed low-α 100 m cube's synchronous restore at 96 kHz is
  already 2.06–2.07 s worst-of-10 on Linux and 2.33–2.59 s on macOS before any diffuse solve, against a 2.143 s
  per-restore budget. 14 × (restore + solve) comes to 30.3–37.4 s against 30 s. Per AX38 4c the remedy is phase-07c
  forward, never a cap.
- **Seat 1's floor.** At s = 1 it is not met (SE 0.36 dB > 0.33 dB, one realisation). Clause (d) cannot rescue it
  (M-3). This is the trigger for "Raise with Maisara" item 1 once session 2 has the replicates.
- **Plan-text conflict** (process-rules §8): CLAUDE.md sets `done` on the automated criteria, while the BUILD_PLAN
  preamble waits for your listening checklist. It does not matter here: the phase stays `in progress`.

## Contractor review focus (from the phase file), with pointers into the diff

- **Equivalence to the validated model.** `DiffuseEstimator.cpp:63-184` (`tracePath`) against `mc5`: same model.
  Verified at one emitter by the smoke test, 15 cases × 8 bands, 0.025 dB. Not verified at two emitters (M-1).
- **Independence of the tracer comparison.** Not in this PR (session 2, `tools/acoustics/tracer.py` committed
  windows).
- **AX22 interaction (AX37 (5.2)).** The estimator takes the post-fallback t_mix,e as input (`DiffuseEmitter::mixS`).
  The test mirror `DiffuseTestUtil.h:53-65` reproduces the fallback, and the smoke test asserts the C++ plan equals
  the Python plan (window, fallback, specular target to 1e-6). The real wiring is session 2's (`Engine.cpp`).
- **Memory at 100 m (AX38).** Not measured here. Lattice sizes are printed: 708 images at the low-α cube, 2 953 at
  the flutter scene. Score arrays are n × E × 8 doubles, under 1 MB. The memory gate is session 2's.
- **Determinism D1–D7.** `Sampling.h` (D1/D3), `src/sim/CMakeLists.txt:50-60` (D2),
  `DiffuseEstimator.cpp:280-336, 484-549` (D4–D6), `:352-389` (D7). Correct by reading. The caveats are m-1 and m-3.
- **AX38 gate (threading, three-class order, `reset()`).** Not in this PR. The pool it will own is
  `ThreadPool.cpp` (M-2, Q-1).
- **Cap-hit and floor-truncated flags (AX41).** `DiffuseEstimator.cpp:352-372`, tests `test_diffuse.cpp:137-202`.
  Correct and covered.
- **D-H1's margin.** Data only, `docs/review/phase-05h/1-orchestrator-cpp-costs.md`. Decision in session 2.
- **No per-scene logic.** None in `src/sim/diffuse/`. Scene keys appear only in the benchmark test.
