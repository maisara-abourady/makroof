# Process rules every PR is checked against

Derived from `CLAUDE.md`, `docs/BUILD_PLAN.md` and the phase files on 2026-11-04. If those documents
change, this file must change with them (the reviewer re-reads them anyway; this file says what to
look for and why).

## 1. One phase per PR, nothing outside it

- The PR title and commits are `phase-XX: <imperative summary>`. The branch executes exactly one
  `docs/phases/phase-XX.md`. Mixed phases, or "while I was here" work in another phase's scope, is
  a **blocker**: later sessions assume each phase's deliverables appear in that phase's PR, and the
  status table would lie.
- Out-of-scope work found necessary belongs under "Follow-ups" in the PR description, not in the
  diff. Exception: a tiny fix needed to make the phase's own acceptance criteria pass, called out
  explicitly in the description.
- Dependencies: every phase this one depends on (the "Depends on" line) must be `done` in
  `BUILD_PLAN.md` §0 at the base commit. Building on an unfinished phase is a blocker.
- If the phase was split (`phase-XXb.md`), the new file must be added to the §0 status table.

## 2. The status table and change log (BUILD_PLAN.md §0 and §6)

- The PR's first commit sets the row to `in progress`; the final state sets it to `done` or
  `blocked (reason)` with the PR link, date and short notes. `done` with any automated criterion
  not green in CI is a blocker.
- Notes must carry the numbers the phase file asks for (benchmark results, "AQ9 met in x/y scenes",
  staleness, signing pending secrets).
- A §6 change-log row is required when the PR changes an assumption, a threshold, a tolerance or a
  golden file. Missing row = request changes.

## 3. Assumptions AQ1–AQ10, AX1–AX8 and new AX entries

- The PRD's Q1–Q10 are unresolved. Code must follow the §2 defaults and cite the ID in a comment
  where a default shapes the code (`// AQ4: 30 ms equal-gain crossfade`). Uncited magic numbers
  that correspond to an assumption are a minor finding; a *different* value than the assumption
  without an AX/§2 edit is a blocker ("never invent an answer quietly").
- A decision not covered by any assumption needs a new `AX<n>` row (assumption, one-line rationale,
  phases that break), mentioned in the PR. Look for silent decisions: clamps, caps, fallbacks,
  default values, coordinate conventions, ordering rules.
- The "Breaks if changed" column tells you which earlier phases a changed assumption invalidates.
  If a PR changes one, the description must say what it re-ran.

## 4. The contract boundary (hard rule)

- `src/sim` and `src/module3d` never include each other, and `src/contract`/`src/sim` never include
  a `juce_*` header. Only `contract::SceneDescription` crosses. `tools/ci/check_boundaries.py`
  enforces it from Phase 01; before that, the reviewer greps. Violation = blocker.
- Any change to the contract (types, JSON fields, semantics, validation limits) requires, in the
  same PR: `contractVersion` bump (minor additive, major breaking), updated
  `docs/contract/scene-v1.schema.json` and `docs/contract/README.md`, new fixtures, and a migration
  test when anything breaks. Partial = blocker. Also check the schema and the C++ validator still
  agree (the Python agreement test).
- `extensions` is for the 3D Module only. The Simulator reading `extensions` is a blocker.
- No preset-, scene- or material-ID-specific logic in `src/sim` (PRD NFR-8). Any string compare on a
  scene name, any lookup keyed by preset, any "if large room then" tuning constant is a blocker.
  Accuracy shortfalls are reported, not tuned.

## 5. Tests and golden files

- Every DSP behaviour has an automated check, preferably against an **independent reference**
  (analytic solution, pyroomacoustics, direct convolution) rather than a self-generated golden.
  A new DSP behaviour with only a "doesn't crash" or "output non-empty" test is a blocker.
- Goldens (`tests/golden/`) store metrics with tolerances; small WAVs only where needed. A golden
  changed in the diff must come with: the phase file saying it is intended, use of
  `tools/ci/update_goldens.py --reason`, an entry in `tests/golden/CHANGELOG.md`, and a §6 row.
  A golden regenerated to make a failing test pass is a blocker.
- Tolerances must match the phase file's numbers. A tolerance loosened relative to the phase file
  without an AX/§6 row is a blocker; look for `Approx(...).margin(...)`, `WithinAbs`, `WithinRel`,
  `atol`, `rtol`, `pytest.approx` with suspiciously round or large values.
- Tests must not be skipped per OS without a stated reason (`SKIP`, `#if !defined(_WIN32)`,
  `pytest.mark.skipif`). Phase criteria say "on 3 OSes".
- Listening packs: phases with audio output add renders to `tools/ci/listening_pack.py`; CI uploads
  the `listening-pack` artifact. The PR must say where the artifact is.

## 6. Code conventions that are review criteria

- C++20; `clang-format` clean (CI checks with clang-format 18); warnings as errors on GCC, Clang
  and MSVC. A PR whose CI is red on any OS is not reviewable as done.
- **Audio thread** (`processBlock` and everything it calls): no heap allocation, locks, file I/O,
  logging or exceptions. Data crosses threads via lock-free SPSC structures or atomic pointer swaps.
  See `realtime-audio-juce.md` for how to spot violations in a diff.
- **Determinism:** anything random is seeded from scene data (`tailSeed`). Offline rendering is
  bit-identical run to run on one platform. Unseeded RNGs, `std::random_device`, time-based seeds,
  thread-timing-dependent results, unordered containers iterated into output, are blockers.
- Units: SI; radians internally, degrees in JSON/UI; axes x right, y forward, z up (AQ1). Per-band
  arrays are named `bandsXxx` and use `contract::kOctaveBandsHz` (8 bands, 63 Hz–8 kHz). A second
  definition of the band centres anywhere is a finding.
- Host parameter IDs are frozen once released: new IDs may be added, none renamed or re-ranged.
  `tests/state/parameter_ids_v1.json` (Phase 07+) is the freeze; a diff touching it is a blocker
  unless it only appends.
- Third-party code enters only through CMake `FetchContent` at a pinned tag or commit, with a row in
  `docs/THIRD_PARTY.md` (version, licence, how pulled in). Vendored copies, unpinned `main`, or a
  missing row are blockers. Downloaded datasets are never committed (the converted embedded HRTF is
  the one exception once its licence is confirmed).

## 7. The PR description contract

The description must contain, and the reviewer checks each against the diff and CI:

1. **What was done**, mapped to the phase's scope items (every scope item either done, or listed as
   not done with a reason).
2. **Acceptance-criteria checklist with CI evidence**: each automated criterion of the phase file
   ticked with a link to the run/job/artifact that proves it. "Passes locally" is not evidence.
   Verify the linked run is on the PR's head commit and green on all three OSes.
3. **Listening checklist for Maisara**, copied from the phase file, with where to find the
   listening-pack artifact (or the plugin artifacts for phases without audio).
4. **Contractor review focus**, from the phase file, with pointers into the diff.
5. **Follow-ups**: work found but not done, with the phase it belongs to.
6. **Assumption / golden changes**: every §2, §6, golden and tolerance change, or "None".

Missing sections are "request changes" even when the code is good: the description is how Maisara
and the contractor verify the phase without reading all the code.

## 8. Definition of done, and what the reviewer cannot sign off

- Automated criteria green in CI on Linux, macOS and Windows; status row updated; description
  complete. The reviewer can confirm these. Note a wording conflict in the repo: `CLAUDE.md`
  step 5 sets `done` when the automated criteria pass, while the `BUILD_PLAN.md` preamble says a
  phase counts as done only after Maisara's listening checklist. Follow `CLAUDE.md` (the session
  rule) and expect the status notes to say "listening checklist pending Maisara", as Phase 00 did;
  mention the conflict in the review's "For Maisara" section until the plan text is reconciled.
- The **listening checklist** is Maisara's. The reviewer never ticks it and says so explicitly; a PR
  with the listening checklist pre-ticked by the author is a finding.
- Where a phase file says a failure "does not fail CI but fails the phase review" (Phase 05 AQ9),
  the reviewer is the gate: read the report and state the pass/fail per scene in the review.

## 9. Severity scheme used in reviews

- **Blocker**: wrong physics/DSP with respect to the phase or assumptions; audio-thread violation;
  determinism break; boundary violation; contract change without versioning; golden/tolerance
  changed to pass; scope outside the phase; CI not green; missing licence; unpinned dependency;
  a test that cannot detect the bug it claims to cover; a silent new assumption.
- **Major**: a correctness risk not covered by tests; an acceptance criterion with weak evidence;
  missing description section; a threading design that works but has no TSan test where the phase
  requires one; undocumented behaviour that later phases will build on.
- **Minor**: naming, comments, missing assumption citation, readability, non-blocking CI hygiene.
- **Question**: something the reviewer could not verify and needs the author to prove.

Every finding names the file and line, states what is wrong, why it matters here (cite the phase
file, assumption ID or reference file), and what evidence or change would resolve it.
