# 27 — /review-phase-pr branch review (before PR open)

2026-11-13. Saved by the orchestrator. Fixes applied after it: minors 1 (RealtimeProbe.h double 'priority:' prefix), 2 (stale register comments), 5 (AX47 law pointer comment). Minors 3, 4 and questions 1–3 go to the PR description (follow-ups / notes). Blocker 1 is closed by the PR-open CI run.

# Review: branch claude/peaceful-bohr-o0g8ct — phase-07c-1b Diffuse solve off the synchronous paths: remainder of 07c-1   (head f63b98d, base main @ merge-base 85557e3)

Branch review (no PR yet): the PR body and PR-level check runs are "no PR: not available". A branch review can only end
in "Request changes" or "Not ready (no CI)".

## Verdict
**Not ready (no CI).** The branch is test-, tool- and plan-only (no `src/` change): the condition 7 S2 re-pin
(`kGateRegister` S2 pins, macOS trigger 2 172 → 1 703 ms, by `tools/ci/repin_gate.py`), the AX38 4c macOS/Windows
low-α entries closed (E1), the B1-b callback instrument (`tests/unit/RealtimeProbe.h`), record (h) prepare-first
totals and busy counts, the AX48 fingerprint pins plus a negative check, `[fm-b2]` insertion tests, the D-B3
`[ax47-midfade]` render test, the ci.yml GATE-warnings step, and the board's plan edits. Every automated criterion is
evidenced in CI on code 9717a58 (three forced runs, all jobs green, I re-read run 43412038058's three build logs)
except the part that only exists after 9717a58: the S2 pin constants and `solveExitMet` (9cc0e32, 5753896). Those
arm, for the first time, an **asserted** check — Windows `REQUIRE(ratio <= 1.10 × 2.5297 = 2.783)` — that has never
executed in CI. The single most important item: open the PR and get its CI run green on all three OSes, and read the
Windows GATE line of that run (`ratioCheck=ASSERTED`, `status=asserted(ratio)`). I found no code defect that blocks;
the findings below are minors and questions.

## Process gate
- Scope: every code hunk maps to scope 1–8 (records, tests, CI summary step, repin tool). Plan edits to phase-07c-2,
  07d, 08-3, 08-4, 09, 13-1/2/3/5 are the board's decisions applied through `/fix-plan` (FM-D1-S3 (i), D-B1, D-B4,
  FM-10S, FM-B2, FM-GROWTH), ledger rows in `docs/review/ledger.md`; not scope creep. `src/` untouched
  (`git diff --stat main...head -- src` empty).
- Dependencies: 07c-1 `done` (PR #32) at the base. OK.
- Status table / §6: §0 07c-1b `in progress` (first commit c100512) — correct pre-PR; `done` + PR link + 07c-1 row note
  still owed (O11). §6 rows present for AX38 (i), (iv), 4c, AX47, AX48, AX49, FM-D1-S3, condition 7 re-pin and the
  fingerprint pins (rows 520–529); `tests/golden/CHANGELOG.md` reasons for scope 4 and the re-pin; no golden file changed.
- Assumptions used: AX38 4c (FM-GROWTH G1–G14, FM-TRIG, E1, X-d−), AX38 (i)/(iv), AX47 (D-B3), AX48 (FM-B2), AX49
  (D-B4), AQ4 (L = lround(0.030 fs)), AX18 laws. Cited in code comments.
- New/changed assumptions: the phase file's own AC 1/AC 2 were rewritten (review_context flags "a phase file
  changed"). Justified: board decisions D-B5/FM-GROWTH (files 4, 8, 11; interrogator 12 SURVIVES), scope list restated
  under rule 2 in the brief. Note it removes the RG-1 in-window absolute `REQUIRE(la.restore.median <= growthBound)`
  on x64 (Linux now has no asserted growth check before 07d) — decided, `AMENDS her decision of 2026-11-10`, on the
  brief's "Decided for Maisara"; the PR must say so in "Assumption / golden changes".
- Boundary & contract: boundary check clean; no contract change. NFR-8 scan hit `src/sim/Engine.cpp:850`
  (`emitter.id == "L"`) is pre-existing, not in this diff.
- Goldens/tolerances/skips: no golden; records-test constants with CHANGELOG reasons. No per-OS skipped TEST_CASE
  (the `#if defined(_WIN32)` hits are inside `RealtimeProbe.h` helpers). The new thresholds equal the plan's
  (1.10, (1 + N_w/L)²(1 + 10⁻⁵), 8u, 1 + 10⁻¹²).
- THIRD_PARTY warning: false positive — ci.yml changes a run script only; `avrt`/`winmm` are Windows system libraries.
- PR description sections: no PR: not available. When written it needs the six sections, the Raise items with
  Maisara's answer (FM-D1-S3 (i)), "Decided for Maisara" (FM-B2, FM-10S, FM-GROWTH with its AMENDS line, D-B1 residual,
  G9, FM-TRIG, D-B1/3/4/5), and "Seat 3's later 2: not triggered" (f ×1.207 / ×1.228 / ×1.222 ≤ ×1.4; s_L > 1.10 s_F
  on every OS).
- CI: no PR checks. Manual `force` runs 43389296112, 43402114873, 43412038058 on 9717a58 (heads 9717a58, ccd6f2d,
  3dd196b). For 43412038058 I listed all 36 jobs (`actions_list list_workflow_jobs`): every job `success`, head 3dd196b;
  `git diff 9717a58 3dd196b` touches only docs/sessions and docs/review. Code after 9717a58:
  `tests/unit/test_diffuse_records.cpp`, `tools/ci/repin_gate.py`, `tools/ci/test_repin_gate.py`,
  `tests/golden/CHANGELOG.md` — **not run in CI**. Artifacts: not checked (no listening-pack change in this phase).

## Acceptance criteria audit
| # | Criterion (phase file) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | Condition 7 re-pin (r̄, F̄, baselines, solveRefMs, k; ratio asserted 1.10 × r̄ on Linux/Windows unless max/min > 1.10; macOS trigger by script; split and f printed; CHANGELOG, §6) | `records: AX38 4b/4c …` GATE block (`test_diffuse_records.cpp:738–867`); `tools/ci/repin_gate.py` + `test_repin_gate.py` (35 passed locally with test_ci_workflow) | mean of 3 green S2 runs (file 22); I re-derived r̄ Linux/Windows, max/min 1.3681, trigger ⌊1.15 × 1 481⌋ = 1 703, f (Linux 1.207) by hand | 1.10 / 1.10 | Inputs: runs 43389296112, 43402114873, 43412038058 green. **The pinned code (9cc0e32, 5753896) never ran in CI.** | a transcription slip between repin_gate output and `S2Pin{…}` (only a manual `diff` in file 22's addendum) | **not proven in CI** (pending PR-open run) |
| 2 | AX38 4c macOS/Windows entries close under (c) or name 07d, on the scope-1 runs | `kGateRegister` `listed` false; GATE x14worst | E1: 14 × worst ≤ 30 s on every S2 run (macOS 23.46/22.44/24.08, Windows 20.24/15.96/19.59 s; Windows run 3 log 19.59 confirmed) | 30 s / 30 s | the three S2 runs; plan text via /fix-plan (§6 row 528) | — (print-only by design) | proven (data); the `listed` constant change itself unproven in CI (print only) |
| 3 | Condition 12 (c): board decision recorded; B1-b record printed on 3 OSes in one run, priority obtained, INSTRUMENT INVALID | `records: condition 12 (c) callback record …` (`[cond12c]`), `RealtimeProbe.h` | — (record) | none (record) | run 43412038058: Linux "not available (errno 1, RLIMIT_RTPRIO 0)", RESIDUAL 0/9; macOS time-constraint in force (32000 mach units), floor 10 overruns; Windows MMCSS "Pro Audio" (priority 18), 7 500/7 500 callbacks, 0/0 overruns; no INSTRUMENT INVALID | n/a (a record) | proven |
| 4 | E_model fingerprint asserted on 3 OSes, fails on a changed E_b | `records: AX48 E_model fingerprint` (`[.][benchmark][ax48-fingerprint]`, REQUIRE `h == pin.hash`); `[ax48-fingerprint-negative]` | per-platform pins from 07c-1 runs | exact | run 43412038058: Linux `22f009efe0004e82`, macOS `9d4f48216097ae94`, Windows `a70a95cd5962863b` = pinned; negative test in ctest (Windows #216) and locally | the negative check covers one fixture at 48 kHz, not the three-fixture concatenation — adequate (FNV over bytes) | proven |
| 5 | FM-D1-S3 answer in §6; (i) lines in 07c-2, 08-3, 09 | plan text | Maisara 2026-11-13 "Write the stream checks now" | — | not CI (prose) | — | proven (files 15–21, §6 row) |
| 6 | Instance insertion reading recorded; a test asserting it | `[fm-b2]` two TEST_CASEs (`test_interim.cpp` +185) | stage-1 solve outside the pipeline, bit-identical IR and E_b | exact | ctest #60, #61 green on Windows run 3; Linux/macOS 253/253; local Debug 57 assertions passed | prepare that solves on a builder thread but blocks — caught by `syncSolves == 1` | proven |
| 7 | AX47 mid-fade check (W-a 1 ms, per channel; (i), (ii), (iii); fade from silence; equal-power recorded), 3 OSes | `[ax47-midfade]` (`test_ax47_midfade.cpp`) | each endpoint rendered alone (K23), reconstruction g in double | (1 + N_w/L)²(1 + 10⁻⁵), 8u, 1 + 10⁻¹² / same | ctest #13 green in run 43412038058 on 3 OSes; local Debug: 490 assertions passed, 64.5 s | the test injects `EqualGain` itself, so a pipeline using the wrong law for a step is not seen here — covered by `test_scene_pipeline.cpp:328`, `:1046` | proven |
| 8 | AX49 reversal decided (moved to 07d, D-B4); record (h) prints per-instance restore, busy builds, hw concurrency, prepare-first totals | record (h) (`[record-h]`) | — (record) | none | Windows run 3: FM-10S 8 inst keyless 8 301 / 9 314 / 6 442 ms, largest batched, FLAG > 5 s | n/a | proven |

## Findings (by severity)
### Blockers
1. `tests/unit/test_diffuse_records.cpp:138, 157–169, 866` — the S2 pin and the newly armed Windows assertion
   `REQUIRE(ratio <= ratioWarnAt)` (2.783) have no CI execution; the three green runs are on 9717a58, before the
   constants existed (CLAUDE.md rule 6; process-rules §8; the caller's own note). Resolve: open the PR (its one CI
   run), require every job green on Linux/macOS/Windows, and cite in the PR from that run's build logs: the Windows
   GATE line with `ratioRefBasis=S2(n=3) ratioCheck=ASSERTED status=asserted(ratio) solveBasis=S2-PINNED`, Linux
   `ratioCheck=PRINT-ONLY … S2-PINNED`, macOS `PRINT-ONLY … S2-PROVISIONAL trigger=1703 triggerBasis=S2`, and
   `pytest tools/ci` (repin_gate tests) green. Headroom on Windows over the S2 runs is 7.6 % (max r 2.585); a red there
   is a 4c (d) defect with no re-run, so read that line before claiming AC 1.

### Major
None.

### Minor
1. `tests/unit/RealtimeProbe.h:73, 106, 126` with `tests/unit/test_diffuse_records.cpp:1238` — the "not available"
   descriptions start with `priority: ` and the record prints `priority: %s`, so the Linux CI log reads
   `priority: priority: not available (errno 1 …)`. Drop the prefix from the three descriptions (test-only, print only;
   any parser keyed on `priority: not available` should be checked first).
2. `tests/unit/test_diffuse_records.cpp:74–75` ("All zero with runs = 0 until then …") and `:156` ("macOS and Windows
   are listed (remedy …)") are stale now that the pins are in and the entries are closed; the next re-pin session reads
   these comments cold. Reword to the current state (the closure comment below them already says it).
3. No automated tie between `repin_gate.py`'s printed initializers and the `S2Pin{…}` literals (file 22's addendum is a
   manual sorted `diff`). The rule "never by hand" is only as good as the paste. Suggested follow-up for 07c-2 / 07d
   re-pins (not this PR): a `tools/ci` test that parses `kGateRegister` and compares it with a committed
   `repin_gate.py --json` output. Put it under "Follow-ups".
4. Commit subjects `plan: …` (e.g. 924701d, ebf18bb, 8a2ac7d, 92514aa, 6ba16a5, d311e2a, b42457c, a28c14c) and
   several "WIP … not yet verified" subjects do not follow `phase-XX: <imperative summary>` (CLAUDE.md "Git and PRs").
   Either reword when squashing at merge, or say in the PR that the history is kept as the decision trail.
5. `tests/unit/test_ax47_midfade.cpp:526` — the header says AX18 decides the law, but the test supplies `EqualGain`
   itself; add one line naming where the pipeline's own law per step is asserted (`test_scene_pipeline.cpp:328`,
   `:1046`) so a reader does not take this test as the law check.

### Questions (unverified, evidence requested)
1. Windows B1-b, run 43412038058: "wake late max" 935–1 065 µs at every point despite "high-resolution waitable timer,
   500 us sleep overshoot mean 48 us" — is that one slow wake per 10 s or systematic? It does not invalidate the
   record (7 500/7 500 callbacks, 0 missed) but the design says "spin the last ≈ 100 µs". A wake-late p99 in the print
   would settle it (07d or 13-3, not this PR).
2. macOS B1-b: the 0-builder floor itself shows 10 overruns > period (p99.9 1 488 µs, max 6 382 µs, thread CPU equal to
   wall), so D-B1 item 6's residual test ("overrun at 8 with none at 0") cannot fire on hosted macOS. Presumably VM CPU
   steal on the 3-vCPU runner; the decided owner (13-3 scope 4, real hardware) already covers it. Confirm the PR says
   so rather than reading 10 / 15 as "no residual".
3. AC 2's "at both gated builds on three OSes": which two builds are meant (keyless/keyed, or Debug/Release)? The E1
   numbers come from the Release benchmark only. State the reading in the PR.

## What I verified myself
- `fetch_pr.sh` → BASE=origin/main, HEAD=origin/claude/peaceful-bohr-o0g8ct (f63b98d); `review_context.py` run
  (phase regex does not match `07c-1b`: tooling limitation, phase identified from the status-row diff).
- Read at HEAD: `phase-07c-1b.md`, the session brief, the diffs of ci.yml, CMakeLists, CHANGELOG, test_ci_workflow.py,
  test_diffuse_records.cpp (all hunks), test_interim.cpp (+185), test_ax47_midfade.cpp (whole), RealtimeProbe.h (whole),
  repin_gate.py (whole), file 22; AX38 4c / §6 passages for the S2 values (match the code constants: r̄, max/min, F̄,
  baselines, solveRefMs, k, 1 703 ms, G9 exit Linux/Windows).
- Re-derived: r̄ Windows (2.585 + 2.455 + 2.549)/3 = 2.5297, Linux 2.3963, max/min 2.691/1.967 = 1.3681; trigger
  ⌊1.15 × 1 481⌋ = 1 703; f Linux = [1.1·0.6493 − 0.1312]/(0.8688 − 0.3858) = 1.207; mid-fade bound
  10·log10((1 + 1/30)²) = 0.2848 dB (matches the printed bound); fingerprint refactor hashes the same bytes in the same
  order as the 07c-1 code (`EmitterBands` = `std::array<BandArray, 2>`).
- CI (GitHub MCP): job list of 43412038058 (36 jobs, all success, head 3dd196b); build-job logs of linux, macos, windows
  persisted and grepped (fingerprint lines = pins on all three; B1-b lines on all three; ctest 253/253; benchmark
  "All tests passed (… 22 test cases)"; FM-10S lines; GATE lines with `ratioRefBasis=RG-1(n=0)` confirming the pins
  were not yet in that code). Did not re-read runs 43389296112 / 43402114873 logs (relied on file 22 for them).
- Local (working tree already at f63b98d; `build/debug` existed, incremental build: no work): `[ax48-fingerprint-negative]`
  18 assertions passed; `[fm-b2]` 57 assertions in 2 test cases passed; `[ax47-midfade]` 490 assertions passed (64.5 s);
  `.venv` pytest `tools/ci/test_repin_gate.py tools/ci/test_ci_workflow.py` 35 passed. Did not run the full ctest suite
  or the Release benchmark (the GATE assertion needs the Release `[benchmark]` run, 30+ min).

## For Maisara
Listening checklist: none new; phase-07c-1's applies and is yours — never ticked by a reviewer. The listening-pack
artifact will be on the PR-open CI run.
For the Expert: on hosted runners the growth check is now asserted on Windows only (Linux's ratio spread 1.368 on
unchanged code, macOS print-only) until the 07d re-pin — the board's FM-GROWTH, which amends your 2026-11-10 decision
and is listed for your veto. The 8-instance Windows load at the rated corner is still 6.4–9.3 s (FM-10S largest:
prepare-first batched 9 314 ms) against AX49's 5 s; moved to 07d, reported, not tuned. Note the plan-text wording
conflict (CLAUDE.md "done on automated criteria" vs BUILD_PLAN preamble "done after the listening checklist") still
stands.

## Contractor review focus (from the phase file), with pointers into the diff
- Run selection: three green S2 runs, none red, out-of-window runs counted — `repin_gate.py:load_runs` refuses `red=`
  and green logs holding a Catch2 failure; file 22 lists the nine logs. Ratio reference and baselines as means —
  `propose()`; constants `test_diffuse_records.cpp:157–169`.
- Solve bound k × solveRefMs PROVISIONAL / print-only with its dated exit — `solveWarnAt`/`solveBasis` lambdas
  (`:758–772`), G9 in `propose()` (`ns_exit`); never asserted (no REQUIRE on SOLVE).
- Register closures (E1) — `listed` false on macOS/Windows low-α entries, `passes30sEveryRun` in repin_gate.
- Fingerprint pins per platform — `kPins` (`:2471–2475`), negative check `:2506`.
