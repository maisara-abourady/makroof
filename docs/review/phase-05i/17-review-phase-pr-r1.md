# Review: branch claude/charming-franklin-pyvvw3 — phase-05i Tail-level switch: remainder of 05h   (head f1d372a, base main d606b10)

Branch review: there is no PR yet, so the verdict can only be "Request changes" or "Not ready (no CI)".

## Verdict
**Not ready (no CI).** The branch does phase-05i's code and data work. It adds an offline generator for the 30 BRAS pairs'
outer-band references (63, 125, 250 Hz, 4 and 8 kHz, at the 2.5 and 1.25 m rungs) with a provenance file. It joins those
references into the agreement golden through the export script, which gates 150 more case-bands (AX43 560 of 560,
AX45 72 of 72), and it re-pins `kGatedAx43`. It adds three hidden record tests (`[diffuse-records-05i]`): AX38 (iv), the
offline wait and K-e12. It also adds a CI step that copies the record and GATE lines into the job summary. I checked the
data myself:
- I recomputed six units and the chunked CR4 path, and the generator reproduces the committed values bit for bit.
- Against main, the golden diff only extends the gating: no gated value, `l_ref` or flag changed, and exactly 150
  case-bands moved. Their `ref_fine`/`ref_coarse` equal the JSONL values.

The code has no blocker. The verdict comes from CI: run 43007183782 (on b94e14f) is still running for every build,
ASan, TSan and tail-gate job, and nightly run 43007188366 is mid-way. The head also differs from b94e14f in two
non-inert paths, so that run will not count as the head's run. The most important open item is the evidence itself:
- the agreement suite green on three OSes;
- the K-e12 record against 2.143 s;
- the restore gate in RG-1 form;
- pluginval and auval.

The most important code-side finding is minor. The 150 case-bands were gated by
`export_phase05h_references.py`, not by `update_goldens.py --extend` as phase-05i §3.1 / §4 criterion 1 and CLAUDE.md
word it. The deviation is documented, and it needs a recorded reading in the PR.

## Process gate
- **Scope.** Every hunk belongs to phase-05i §3 items 1, 2, 4 and 5, or to the session's bookkeeping:
  - the generator and data: §3.1;
  - the export join and golden: §3.1;
  - `test_diffuse_records.cpp`: §3.2 and §3.4;
  - `ci.yml`: §4 criterion 2;
  - the AX41 record: §3.5;
  - the brief and the review records.

  Nothing touches `src/`. No out-of-phase work.
- **Dependencies.** 05h is `done` at d606b10 (§0 row 27). OK.
- **Status table and §6.** a7cbad1 sets 05i `in progress` first. OK. These are **pending** (planned by the orchestrator,
  not defects):
  - the `done` row with the counts and records;
  - a §6 change-log row for the golden extension;
  - the AX43/AX45 'at the time of writing' counts;
  - the AX43 §0 catch record;
  - the ledger links (all through `/fix-plan`).
- **Assumptions used.** AX36 rung rule (`l_ref < 1 %`), AX43 (c) / D-H2 (a)(c) order and G-a gating, AX38 4c / (iv),
  D-H3 (e), the AX41/AX44 lists. They are cited in code and comments. No new AX. No threshold, τ, N or case changed.
- **Boundary and contract.** Boundary check clean on the head tree. Contract untouched. NFR-8: nothing in `src/sim`
  changed. The one scan hit, `Engine.cpp:550` (the emitter id "L"/"R"), is pre-existing and not in this diff.
- **Goldens, tolerances and skips.**
  - `phase05h_agreement_reference.json` is extended only, which I verified (see below). There is a CHANGELOG entry.
  - Not written by `update_goldens.py` (Minor 1).
  - No tolerance changed and no skip added.
  - The pinned count moves 410 → 560, which matches the golden (560 / 72 recomputed from the head golden).
- **PR description sections.** No PR: not available. Pending: the six sections, "Decided for Maisara", and the Raise
  items.
- **CI.** Run 43007183782 (workflow_dispatch, b94e14f), read at review time:
  - Green: `changes`, `clang-format`, `contract tools` ×3, `python tools (linux)` (571 passed, 16 skipped, including
    `tools/ci/test_ci_workflow.py`; `listening-pack` artifact 13849760524 uploaded).
  - `build (linux/macos/windows)` were inside `Test (debug)`. So the debug build, the new tests and `SPATIAL_WERROR=ON`
    compiled on all three OSes. Release, Benchmark, Records, pluginval and auval had not run.
  - Still running or queued: `python tools (macos/windows)`, `open-field` ×3, ASan, TSan and the tail gates.

  Nightly run 43007188366: "Nightly gate and validation tests" passed; the a* recomputation, the report and the upload
  were still running. Head f1d372a differs from b94e14f in `tests/golden/CHANGELOG.md` and
  `tools/validation/export_phase05h_references.py`, which are not inert under `ci_fingerprint.py`. So the run that
  counts is the one the PR opening starts. Everything CI-dependent below is **unproven**.

## Acceptance criteria audit
| # | Criterion (phase-05i §4) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | Newly certified case-bands gated by extension with a CHANGELOG reason; agreement suite green on 3 OSes; AX43 additive pooled check 'within' per band, catch printed; '<gated> of 560 / 72' printed; no value hand-edited; unfinished items listed with owner | `test_diffuse_agreement.cpp` `[diffuse-agree-full]` (pinned `kGatedAx43 = 560`, `kGatedAx45 = 72`); golden from `export_phase05h_references.py` | independent: Python `ref_hybrid.target_hybrid` (radiosity hybrid) at 1.25 m, `l_ref` = 2.5 → 1.25 m | τ 0.25 dB and the f9 additive check, unchanged / same | none yet (Benchmark step not run). The local run is quoted in docs/review/phase-05i/2 | The pinned count catches un-gating but not a changed gated value. No CI test regenerates the golden from the committed data and diffs it, so a hand edit of a reference value would pass CI. I did that diff by hand for this branch (see "What I verified myself") | not proven (CI) |
| 2 | AX38 (iv) records and K-e12 record printed in the job summary on 3 OSes, each with its condition, none asserted | `test_diffuse_records.cpp:984`, `:1141`, `:1215` `[diffuse-records-05i]`; `ci.yml:418-432` | n/a (records) | no CHECK/REQUIRE: verified | none yet | K-e12 does not print whether a build was actually in flight at each restore (Minor 4); the (d) 1-instance row is labelled as contended (Minor 5) | not proven (CI) |
| 3 | Restore gate in register form, baselines pinned, green on 3 OSes; register entries unchanged | `[diffuse-records]` (05h, unchanged in this diff) | n/a | unchanged | none yet | n/a | not proven (CI); rules (ii)–(iv) evaluation from the GATE lines **pending** (orchestrator) |
| 4 | AX41 lists match the D5 golden and the reports test | `[diffuse][d5][reports]` (unchanged); table in docs/review/phase-05i/1 | D5 golden | exact | debug ctest still running | A new fixture added without re-reading the list. None was added (12 fixtures, unchanged) | proven on reading; CI ctest pending |
| 5 | Nightly BRAS green; report regenerated if a BRAS reference was gated | nightly.yml | measured BRAS | unchanged | 43007188366 in progress (gate tests step green) | The claim that the report does not read the agreement golden: checked, only `export_phase05h_references.py` and `listening_pack.py` read it | not proven (CI) |
| 6 | pluginval 10 and auval pass | ci.yml | n/a | n/a | not reached | n/a | not proven (CI) |

## Findings (by severity)

### Blockers
1. **(process) CI not green on the head.**
   - `ci.yml` run 43007183782: build (all OSes), ASan, TSan, tail gates and the python macos/windows jobs are unfinished.
   - Nightly run 43007188366 is unfinished.
   - Both runs are on b94e14f, not on f1d372a, and the later commits touch non-inert paths.

   This resolves when the PR opens and its CI run is green on three OSes, with the summary's record lines quoted. This is
   the "Not ready (no CI)" verdict, not a code defect.

### Major
None found in the diff.

### Minor
1. **Golden gated by the export script, not `update_goldens.py --extend`.**
   - Where: `tools/validation/export_phase05h_references.py:72-82, 318-321`.
   - The golden is rewritten by the export script and the CHANGELOG is appended by it. phase-05i §3.1 / §4 criterion 1
     and CLAUDE.md ("the ONLY way to update them") name `update_goldens.py --extend`.
   - Mitigation: documented in docs/review/phase-05i/2 (G11), as in 05h's three golden rounds. The script is idempotent
     and its reason text matches the CHANGELOG entry exactly (checked).
   - Resolve: a decider or `/fix-plan` reading recorded in the PR ("met in substance"), plus the follow-up to wire the
     export into `update_goldens.py`. Also fix the stale comment at `tests/unit/test_diffuse_agreement.cpp:439`
     ("re-pinned through update_goldens.py --extend"), which now describes a command that was not used.
2. **Provenance file is not the script's output.**
   - Where: `tools/validation/data/phase05i_bras_references.provenance.json` and
     `compute_phase05i_bras_references.py:111-126`.
   - The committed file carries `tool_commit: "2c11610"`. `write_provenance()` writes the full `git rev-parse HEAD`.
     The file also has `tool_commit_note`, `recipe_check` and `machine`, none of which the script writes. So it was
     edited by hand after the run, and a rerun (or a resume) silently drops those fields.
   - The script records no dirty-tree flag, and no ℓ_ref. phase-05i §3.1 lists ℓ_ref among the provenance fields, and
     the brief's G4 asked for it. Today ℓ_ref lives only in the golden's `l_ref_*` columns and in record 2.
   - Resolve: have the script write the commit with a `git status --porcelain` dirty flag, the check result, the
     machine and the per-unit ℓ_ref (or a max per room and band), and regenerate the file (no reference value changes).
     Or state in the PR that these fields were added by hand.

   The numba 0.68.1, numpy 2.5.4 and scipy 1.18.1 recorded there match the hash-pinned requirements (checked).
3. **`--check` does not cover the chunked solver.**
   - Where: `compute_phase05i_bras_references.py:129-142`.
   - It covers CR2/CR3 (lean solver) only. The 5 CR4 1.25 m units, the 15 GB class, come from the chunked path.
   - I recomputed CR4 at 1.25 m and 500 Hz through `compute_unit` (chunked, 197 s): worst relative difference to
     `phase05b.json` r1 = 0.0. So the path is correct, but the committed check does not show it.
   - Resolve: add CR4 to `--check` (optionally behind a flag) or cite this result.

   Related nit: `phase05b.py r1 --all-bands --chunked` already implements the same recipe. The new script duplicates it
   for resumability, which is fine, but say so in its docstring.
4. **K-e12 may count restores with nothing in flight.**
   - Where: `tests/unit/test_diffuse_records.cpp:1262-1276`.
   - The restore lands after a uniform delay in [0, rebuild]. A delay near 0 can come before the builder has picked up
     the edit; the builder coalesces at ≤ 1 build per 20 ms. A delay near `rebuild` can come after the solve (cancel
     points are only in the solve, AX39 D6).
   - So some of the 10 runs may measure "restore with nothing in flight" while the record is labelled "a room edit in
     flight". This matters because phase-05i §3.2 says H1-F1's builder-idle convention "is not read as met for this
     case".
   - Resolve: sample `!pipe.builderIdle()` right before `beginRestore()` and print it per run, along with the count of
     in-flight runs in the summary line. Printing is enough; no assertion.
5. **(iv) records state their conditions incompletely.**
   - (a) at `test_diffuse_records.cpp:1010`: `prepare()` runs before `restore()`. In realtime, `prepare` synchronously
     builds the default scene (`medium_room`) first, so "load until the last is audible" includes one extra build per
     instance. The record should say so, or the order should be stated as the host-call order it models.
   - (d) at `:1128`: with 1 instance the line prints "while the other 0 rebuild without pause". That row is an
     uncontended baseline and should say so.
   - The 05h `[diffuse-records]` (iv) test (`:758`) still runs beside the new (a)/(b). That adds CI time for duplicate
     load numbers; name which one is the record of reference.
6. **Redundant `set -o pipefail`.**
   - Where: `.github/workflows/ci.yml:407`.
   - Harmless: the Actions `shell: bash` already runs `bash -eo pipefail`. I checked the failure semantics, and they are
     preserved: the pipeline's status is `spatial_tests`' status (`xvfb-run` passes it through), and `-e` stops the
     step.
   - The Records step works under Git Bash on Windows (`tee` and `grep -E` exist; CRLF line ends still match `^`) and
     on macOS. Its `if: always()` with the file guard behaves correctly when Build fails. No change needed; note only.

### Questions (unverified, evidence requested)
1. **Agreement on three OSes.** Is the agreement suite green on Linux, macOS and Windows with the 150 new case-bands?
   Is the f9 additive check 'within' in all 8 bands on each? The local run gives max |C++ − ref| 0.046 dB and a catch of
   about 0.008 dB. Evidence: the Benchmark step logs or the job summary of the PR's run.
2. **K-e12 against the budget.** What is the K-e12 worst per OS for both cubes against 2.143 s? The idle restore median
   is already about 2 s (the 05h baselines are 2 068 / 2 028 / 1 817 ms), so a FINDING is likely. That triggers the
   decider record (pending) and possibly Raise item 1.
3. **Wall time.** How long does the Benchmark step take now? The new tests add many 100 m / 96 kHz full builds: 8
   instances × (load + 2 steps + contention + 3 waits) per scene and rate, plus 8 parallel offline instances × 5
   builds. The `build` job has no `timeout-minutes`. Evidence: the step durations in the PR run.
4. **Restore-gate register.** Are the restore gate's GATE lines in RG-1 form, green on three OSes, with register
   entries unchanged? The rules (ii)–(iv) evaluation is pending (orchestrator).
5. **Rebuild-time caching.** Is there any IR or unit-decay cache in the rebuild path that makes repeated −1/−2 m edits
   cheaper than a cold build? If so, the K-e12 "rebuild" window and the (iv) staleness are low.

## What I verified myself
- **Golden diff, main → head.** I wrote a Python comparison of `tests/golden/phase05h_agreement_reference.json`:
  - Columns and names are identical.
  - The only changed fields are `ref_fine`, `ref_coarse`, `l_ref`, `certified` and `gated`, 150 each, all BRAS pairs
    in bands 0, 1, 2, 6 and 7.
  - Gated case-bands lost: 0. Gated case-bands whose value changed: 0. Newly gated: 150, none in 500 Hz–2 kHz and none
    outside the BRAS rows.
  - Max ℓ_ref over the new case-bands is 0.379 %. Gated sums: suite AX43 560, AX45 72.
  - The replaced scope-6 `ref_coarse` values differ from the new rungs by at most 0.333 %, as docs/review/phase-05i/2
    says.
- **Golden equals JSONL.** All 150 `ref_fine` / `ref_coarse` values equal the JSONL's 1.25 m / 2.5 m `e_target`
  exactly (0 mismatches).
- **CHANGELOG reason.** `REASON_05I` in the export script equals the CHANGELOG entry text (so a rerun is a no-op).
- **Reference recomputation.** Using the repo `.venv` (numba 0.68.1, numpy 2.5.4), I recomputed with `compute_unit` at
  the head:
  - CR2 at 2.5 and 1.25 m and CR3 at 2.5 m, bands 63 Hz and 8 kHz: worst relative difference to the committed JSONL
    0.0;
  - CR4 at 1.25 m, 500 Hz, through the chunked solver: worst relative difference to `phase05b.json` r1 0.0.

  The working tree is unchanged.
- **Recipe identity.** I read `phase05b.step_r1` beside the new `compute_unit`: same `t_end`, `var0`, air factor after
  the solve, `FastRoomKernel` per band and `target_hybrid` per band. `target_hybrid` is per band, so zero-filling the
  other bands is exact.
- **Pins.** I checked the recorded numba, numpy and scipy versions against `tools/acoustics/requirements.txt` and
  `tools/validation/requirements-offline.txt`.
- **Report inputs.** Only `export_phase05h_references.py` and `tools/ci/listening_pack.py` read the agreement golden.
  The report's claim is correct.
- **Threading in the new tests.** Each pipeline is driven from exactly one thread at a time:
  - the offline `off` pipeline is handed to the `bounce` thread, which creates a happens-before, and is joined before it
    is destroyed;
  - `churn` touches only `pipes[1..]` while the main thread drives `pipes[0]`;
  - the offline-wait threads each own one pipeline and their own buffers;
  - `waits[i]` is written by thread i only, and the outer vector is never resized;
  - the lambdas do not capture the structured bindings `label` / `sc`.

  No lifetime or two-thread misuse found, and no CHECK or REQUIRE in the three new tests.
- **CI.** I read the job list of runs 43007183782 and 43007188366 and the `python tools (linux)` log (pytest summary,
  listening-pack upload). I did not read any build, benchmark, pluginval or auval log: they had not run.
- **Not done.** No C++ build (no `build/debug/_deps`); compilation is evidenced by CI's debug build reaching
  `Test (debug)` on all three OSes.

## For Maisara
- **Listening checklist.** Untouched; it is yours. Phase-05i adds none new (phase-05h §6 stands).
- **Listening pack.** The `listening-pack` artifact of run 43007183782 (id 13849760524, from `python tools (linux)`) is
  on b94e14f. The README label of `bras_cr3_ls1_mp2` moves from "3/8 bands gated" to "8/8 bands gated", which the PR
  must name (phase-05i §5).
- **For the Expert.** The 63 Hz column is gated as agreement with `ref_hybrid` only, never as a room validation below
  the Schroeder frequency (CHANGELOG). The K-e12 and 8-instance load records are findings, not tuned (NFR-8 respected:
  no `src/` change).
- **Plan wording.** The `CLAUDE.md` (done on automated criteria) vs `BUILD_PLAN` preamble (done after listening)
  wording conflict still stands.

## Contractor review focus (from the phase file), with pointers into the diff
- **Provenance of every committed reference** (tool commit, pins, rungs, ℓ_ref):
  `tools/validation/data/phase05i_bras_references.provenance.json`, `compute_phase05i_bras_references.py:111-126`.
  ℓ_ref is missing there and some fields were added by hand (Minor 2).
- **Gating only extends:** `export_phase05h_references.py:221-240`; the golden diff verified above; the pinned count is
  at `test_diffuse_agreement.cpp:441-448`.
- **Record conditions stated beside each number:** `test_diffuse_records.cpp:984-1280` (format strings); gaps in
  Minor 4 and 5.
- **The baselines' CHANGELOG reasons:** unchanged in this diff (05h RG-1 entry); re-pinning is not due until 07c.
- **No per-scene logic:** no `src/` change; the BRAS rooms are enumerated only in offline tools and the export.
