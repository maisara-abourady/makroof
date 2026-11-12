# Session brief: 05i follow-up — Windows low-α restore-gate entry listed again

- Branch: `claude/clever-ride-j355sg` (from `origin/main` at 3c444a8, PR #30's merge)   Started: 2026-11-12
- Governing: CLAUDE.md (scope list, steward, "When to open a PR", golden-file rules); `docs/review/phase-05i/9-decider-r2.md`
  (Q1, answer 4), `10-*` (interrogator: SURVIVES), `19-orchestrator-ci-run-of-record.md`, interrogator file 22 (P05I-120);
  `docs/BUILD_PLAN.md` AX38 4c register and RG-1 paragraph; `docs/phases/phase-05i.md` §3.3 (ii);
  `docs/phases/phase-07c-1.md` condition 9. Not a phase: no §0 status changes.

## Maisara's words
> 2026-11-12: "do we have a session for this small follow up to run whether before or after 07c-1 it won't matter?"

The session request that came with her message (the same user turn, 2026-11-12), verbatim from "## What is wrong" on:

> ## What is wrong
> Phase 05i decided (decider file `docs/review/phase-05i/9-decider-r2.md`, Q1 and answer 4; interrogator file 10: SURVIVES) that an AX38 4c restore-gate register entry closes under rule (c) only if it passed 30 s on every 05i run, and that if any 05i run printed OVER30S the entry stays listed and its records-test `listed` flag goes back to `true` in the next permitted push.
> - Outcome on the run of record, CI run 43031773338 (records in `docs/review/phase-05i/19-orchestrator-ci-run-of-record.md`): Linux low-α passed both runs (27.61 / 27.40 s) and is closed; **Windows printed OVER30S (46.63 s, slow runner, flutterDev +48.9 %), so it stays listed**; macOS stays listed.
> - The plan text already says this (`docs/BUILD_PLAN.md` AX38 4c register and RG-1 paragraph; `docs/phases/phase-05i.md` §3.3 (ii); `docs/phases/phase-07c-1.md` condition 9).
> - But the code still has Windows `listed = false`, so every CI run prints the Windows low-α entry as "register entry closed, hosted-runner form". The PR named this as owed to the contractor's review push, which never happened because the PR was merged first (interrogator file 22, P05I-120).
>
> ## The change
> 1. Branch from main (e.g. `git checkout -B <your session branch> origin/main`).
> 2. `tests/unit/test_diffuse_records.cpp`, in `kGateRegister`: the row `{"cube100_lowalpha0.05_s0.3", "Windows", 36.73, 2028.0, 2.83, 737.0, true, false, false, 90.4, 2}` → change the 8th field (`listed`) from `false` to `true`. Update the comment above the low-α rows: macOS and Windows are listed (Windows: OVER30S on 05i's run of record 43031773338; recorded 36.73 s on CI run 42942694523's slow runner, phase-05h file 53); Linux closed under AX38 4c (c) on phase 05i's runs (docs/review/phase-05i/9, 19). Change nothing else: `strict30s`, `absoluteAsserted`, baselines and `solveRefMs` stay as they are. The flag is print-only (it selects the "LISTED defect" vs "register entry closed" text; no REQUIRE reads it).
> 3. `tests/golden/CHANGELOG.md`: append an entry in the RG-1 form, e.g. "## <date> (05i follow-up, Q1)" with Reason: the 05i Q1 entry of 2026-11-11 said Linux and Windows close; on the run of record 43031773338 Windows printed OVER30S (46.63 s), so under decider file 9's rule it stays listed; `listed` true for Windows, print only; no golden file changed. Bullet: "- `(records-test constants)`: the Windows low-alpha entry listed again (AX38 4c (c) 'otherwise' branch, phase-05i §3.3 (ii)); print only (no golden file changed)".
> 4. Run `tools/ci/check_format.sh` and build the Release test binary (`cmake --preset release` then `cmake --build --preset release --target spatial_tests`; plugin not needed: `-DSPATIAL_BUILD_PLUGIN=OFF`) to check it compiles cleanly with warnings as errors (`SPATIAL_WERROR=ON`).
> 5. Commit with a message such as `phase-05i: Windows restore-gate register entry listed again (Q1 outcome on the run of record)`, push, and open a PR only when finished (CLAUDE.md "When to open a PR"). Opening the PR starts CI. The test file is in the CI fingerprint, so it is a full run of about 75 minutes. Six Linux jobs failed once during an Azure apt-mirror outage; if that recurs, use "re-run failed jobs", never empty commits.
> 6. Done when CI is green on Linux, macOS and Windows and the Windows build job's GATE output for `cube100_lowalpha0.05_s0.3` prints "LISTED defect" (Linux still "register entry closed"). Record the run id in the brief and the PR. Have the steward clear the session, then report to Maisara; she decides on the merge.
>
> ## Out of scope
> No plan-text change (the plan is already right), no board loop (this applies a decided rule), no other test or code change, no phase status change. Order relative to phase 07c-1 does not matter. If 07c-1 has already landed and rewritten `kGateRegister`, apply the same intent to its version: the Windows low-α entry is listed until 07c-1's conditions 9–10 close it.

## Objectives
The items of the session's opening scope list, one for one.

| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | **Session brief**: this file, steward BRIEF OK | CLAUDE.md "Reporting" 1 | BRIEF OK in the log below; the brief committed |
| O2 | **Windows entry listed**: `kGateRegister` Windows `cube100_lowalpha0.05_s0.3` has `listed = true`; the comment above the low-α rows says macOS and Windows are listed (Windows: OVER30S on 43031773338; 36.73 s on 42942694523, phase-05h file 53), Linux closed under AX38 4c (c) (05i files 9, 19); nothing else changed (`strict30s`, `absoluteAsserted`, baselines, `solveRefMs`) | request step 2; decider file 9 Q1; phase-05i §3.3 (ii) | `git diff origin/main -- tests/unit/test_diffuse_records.cpp` shows the comment and that one field only |
| O3 | **Golden changelog entry**: `tests/golden/CHANGELOG.md` entry in the RG-1 form "2026-11-12 (05i follow-up, Q1)" with the reason and the bullet; no golden file changed | request step 3; CLAUDE.md "Tests and golden files" | the diff; `git diff --stat origin/main` lists no file under `tests/golden/` but CHANGELOG.md |
| O4 | **Format and build clean**: `tools/ci/check_format.sh` clean; Release `spatial_tests` builds with `SPATIAL_WERROR=ON`, `SPATIAL_BUILD_PLUGIN=OFF` | request step 4 | command output (exit 0) |
| O5 | **Plan status untouched**: no change to `docs/BUILD_PLAN.md` (no §0 status, no plan text) | request "Out of scope" | `git diff --stat origin/main` does not list `docs/BUILD_PLAN.md` |
| O6 | **Pre-PR review**: `/review-phase-pr` run on the branch diff, fixes in | CLAUDE.md "When to open a PR" | the review's verdict quoted in the log |
| O7 | **Pushed, PR opened**: commit (`phase-05i: …`, request step 5) pushed to `claude/clever-ride-j355sg`; PR open with what was done, criteria checklist with CI evidence, listening note (none: print-only change), contractor focus, follow-ups, golden changes, "Decided for Maisara" (none new); follow-up named: BUILD_PLAN L28/L158 wording "contractor's review push" → this follow-up PR, via /fix-plan | request step 5; CLAUDE.md "Git and PRs" | the PR link |
| O8 | **CI green, GATE text right**: CI green on Linux, macOS, Windows; the Windows job's GATE line for `cube100_lowalpha0.05_s0.3` prints "LISTED defect"; Linux prints "register entry closed"; macOS still prints "LISTED defect" | request step 6 | the run id and the three quoted low-α GATE lines, here and in the PR |
| O9 | **Steward clearance**: READY TO REPORT, then the report to Maisara (she decides on the merge) | request step 6; CLAUDE.md "Reporting" 3 | READY TO REPORT in the log |

## Scope
- In: the one `listed` field and its comment, the CHANGELOG entry, the brief, the PR.
- Out: any plan text (already right), any board loop (this applies a decided rule), any other test or code change, any
  phase status. Order relative to 07c-1 does not matter; if 07c-1 lands first and rewrites `kGateRegister`, the same
  intent applies to its version (Windows low-α listed until 07c-1 conditions 9–10 close it).
- Out, follow-up for the PR: BUILD_PLAN L28/L158 say the Windows flag returns to true "in the contractor's review push"
  of PR #30; that wording should name this follow-up PR instead, via `/fix-plan` (plan text is out of scope here).

## Constraints and settled decisions
- Decider file 9 Q1 (answer 4), interrogator file 10 SURVIVES: an entry closes under (c) only if it passed 30 s on every
  05i run; otherwise it stays listed and `listed` goes back to `true` in the next permitted push.
- The flag is print-only: it selects "LISTED defect" vs "register entry closed, hosted-runner form" (and the
  PASSES30S/OVER30S warning wording); no REQUIRE reads it.
- CLAUDE.md, Maisara 2026-11-08: PR opened only when finished; it starts CI (full run, the test file is in the
  fingerprint). Transient apt-mirror failures: "re-run failed jobs", never empty commits.

## Decided for Maisara
- None new. This applies Q1 as already decided for her in phase 05i (listed in PR #30 and the 05i brief).

## Raise with Maisara
- none (not a phase; no phase file)

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
| 1 | 2026-11-12 | BRIEF GAPS | G1 session request not quoted verbatim (blocking); G2 stale BUILD_PLAN "contractor's review push" wording as a /fix-plan follow-up; G3 commit prefix; G4 macOS GATE line in O8 | none |
| 2 | 2026-11-12 | BRIEF OK | none | G1, G2, G3, G4 |
| 3 | 2026-11-12 | CONTINUE (pre-PR clearance given: O1–O6 MET on e6fc12b) | G5 PR + CI run of record with the three low-α GATE lines (O7, O8) | none |

## Evidence log
- O4 (2026-11-12, local): `tools/ci/check_format.sh` → "clang-format: 105 files clean", exit 0. `SPATIAL_WERROR=ON cmake --preset release -DSPATIAL_BUILD_PLUGIN=OFF` + `cmake --build --preset release --target spatial_tests` → "[180/180] Linking CXX executable tests/unit/spatial_tests", exit 0; CMakeCache `SPATIAL_WERROR:BOOL=ON`.
- Local Linux run of the restore-gate case (slow container, not O8 evidence): "restore gate cube100_lowalpha0.05_s0.3  Linux: register entry closed, hosted-runner form …"; "All tests passed (36 assertions in 1 test case)".
- O2/O3: commit 6d38d4e.
- O6: `/review-phase-pr` branch review (head 6d38d4e): "Not ready (no CI)", no blocker/major/minor finding; the script's §6 warning is a false positive (only CHANGELOG.md changed; §6 L504 already says Windows stays listed). File: scratchpad `review-claude-clever-ride-j355sg-phase-05i.md`, summarised in the PR.
- O7: PR https://github.com/maisara-abourady/makroof/pull/31 opened 2026-11-12 07:12 UTC (head 38d4ba5).
- O8: CI run 43173536470 (pull_request, head 38d4ba5): every job success (35 jobs incl. build linux/macos/windows, ASan+UBSan, TSan, tail gates, open-field validation, python/contract tools, `ci ok`). Low-α restore-gate lines from the three build jobs:
  - Windows (job 131032359471): "restore gate cube100_lowalpha0.05_s0.3  Windows: LISTED defect (recorded 14 x worst 36.73 s); 14 x worst now 26.23 s; WARNING PASSES30S: this entry now passes 30 s, remove it through /fix-plan; growth bound asserted in-window after the scene loop (RG-1)"; GATE `x14worst=26.23 median=1807 growthBound=2231 status=not-evaluated(runner,flutter-16.1%) warnings=PASSES30S`
  - macOS (job 131032359529): "… macOS: LISTED defect (recorded 14 x worst 33.40 s); 14 x worst now 26.44 s; WARNING PASSES30S …; growth bound reported only"; GATE `x14worst=26.44 median=1554 status=reported-only trigger=2172 warnings=PASSES30S`
  - Linux (job 131032359536): "… Linux: register entry closed, hosted-runner form (recorded 14 x worst 30.27 s); 14 x worst now 21.47 s; passes 30 s (register entry closed under AX38 4c (c))"; GATE `x14worst=21.47 median=1434 status=not-evaluated(runner,flutter-34.8%)`
  - Note (not acted on, out of scope): on this post-05i run Windows and macOS low-α passed 30 s and print PASSES30S ("remove it through /fix-plan"). Removal is not this session's: decider file 9 reads (c) "on 05i's runs", and the listed entries close under phase-07c-1 conditions 9–10 (or a /fix-plan reading the latest runs). Recorded here for 07c-1 as a data point; both runners were fast (flutterDev −16.1 % / −34.8 % on Windows / Linux), so the growth bound was not evaluated.

