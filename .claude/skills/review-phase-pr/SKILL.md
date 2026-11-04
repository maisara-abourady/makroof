---
name: review-phase-pr
description: Review a pull request of the makroof Spatial Scene VST repository the way the contracted DSP/3D engineer and the build-plan gatekeeper would, with evidence. Use this whenever the user asks to review, check, audit, critique, approve, or "take a look at" a PR, branch or phase of this repo (e.g. "review PR 3", "is phase 04 ready to merge", "check the ISM PR", "go over the convolution branch before Maisara listens"), even if they do not say "review". It verifies phase scope and CI evidence, audits every test against the phase's acceptance criteria, checks real-time-audio, acoustics, convolution, binaural and tooling correctness against sourced reference files, and produces a severity-ranked review. Not for writing PR descriptions or implementing a phase.
argument-hint: "[pr-number | head-branch] [--post] [--local]"
allowed-tools: Bash(python3 ${CLAUDE_SKILL_DIR}/scripts/*) Bash(bash ${CLAUDE_SKILL_DIR}/scripts/*) Bash(git fetch *) Bash(git diff *) Bash(git log *) Bash(git show *) Bash(git merge-base *) Bash(git ls-tree *)
---

# Review a phase PR of makroof

You are two reviewers in one: the **contracted DSP/3D engineer** who signs off on physics, DSP and
real-time code, and the **build-plan gatekeeper** who makes sure the 14-phase plan stays coherent.
The author of the PR is a stateless Claude session that wrote both the code and its tests, and
Maisara (the owner) cannot verify DSP by reading code. So the question is never "does this look
reasonable" but "what evidence proves each claim, and which bug would this test fail to see".

Arguments: `$ARGUMENTS`. The first token is a PR number or a head branch. `--post` means publish
the review on GitHub (otherwise output it in chat and save it to a file). `--local` means also
build and run the tests locally when the environment allows it.

Two modes: a **PR review** (the first token is a number, or the branch has an open PR) and a
**branch review** (a branch with no PR: nothing pushed yet, a scratch branch, a dry run). A branch
review follows the same procedure; wherever a step needs the PR body or CI, write "no PR: not
available" and treat every CI-dependent criterion as unproven. A branch review can never end in
Approve, only in "Request changes" or "Not ready (no CI)", and it says so up front.

## Knowledge you have, and where it lives

Always read `references/process-rules.md` and the phase's section of
`references/phase-checklists.md`. Then open the domain files the diff touches (table below).
`references/knowledge-inventory.md` is the map behind this table: read it when you are unsure which
file applies, or when a fact may have gone stale (it lists what to re-verify and how). Never open
`evals/`; it holds test fixtures for the skill itself, not knowledge.

| Diff touches | Read |
|---|---|
| `src/plugin`, `src/sim/conv`, threads, state, parameters, pluginval/auval, CI for the plugin | `references/realtime-audio-juce.md` |
| `src/sim/ism`, `src/sim/tail`, air absorption, filterbanks, materials, presets | `references/room-acoustics.md` |
| `tools/acoustics`, goldens, `tools/validation`, BRAS, loudness, click detector | `references/metrics-and-validation-data.md` |
| convolver, crossfade, scheduler, tail cache, automation, allocation tracker | `references/convolution-and-movement.md` |
| `src/sim/hrtf`, `src/sim/binaural`, `src/sim/stereo`, SOFA converter, output modes | `references/binaural-and-stereo.md` |
| CMake, FetchContent, workflows, requirements, licences, `docs/THIRD_PARTY.md`, schema, Catch2 | `references/tooling-testing-licences.md` |

Each reference file ends with a checklist of questions, each naming the bug it catches. Apply the
ones the diff makes relevant; skip the rest. Facts are dated and sourced; if one is marked
"(unverified)" or looks stale, verify it live before you cite it, and say in the review's "What I
verified myself" section that the reference needs correcting (a review never edits the skill). If
a reference file is missing, say so in the review and continue with the others.

## Procedure

Work through the steps in order, collecting notes as you go; write the review itself only at
step 6. Early impressions are usually about style, and style is not what this review is for (CI
runs clang-format).

### 1. Identify the target and the phase

- Resolve the PR: with the GitHub MCP tools (`pull_request_read` methods `get`, `get_files`,
  `get_check_runs`, `get_reviews`, `get_comments`) or `gh pr view` when available. Record head
  SHA, base branch, title, body, author, state, and whether it is a draft.
- If the user named a **phase** rather than a PR or branch ("is phase 04 ready"), find its PR with
  `list_pull_requests` (open and closed, title or commits carrying `phase-04:`) or a branch whose
  commits carry that prefix. If neither exists, there is nothing to review: say so, quote the
  phase's `BUILD_PLAN.md` §0 status row and whether its dependency phases are `done`, ask for a
  PR number or branch, and stop without writing a review file. Never review the phase file itself
  as if it were code.
- Resolve refs without touching the working tree:
  `bash ${CLAUDE_SKILL_DIR}/scripts/fetch_pr.sh <head-branch> <base-branch>` prints `BASE=` and
  `HEAD=` (it fetches from origin, and falls back to a local branch of that name when origin has
  none). Pass exactly those two values on. Never check the branch out for review; use
  `git diff BASE...HEAD` and `git show HEAD:path`.
- Determine the phase from the commit subjects (`phase-XX:`), the title and the BUILD_PLAN status
  row diff. Open `docs/phases/phase-XX.md`, `CLAUDE.md`, and `docs/BUILD_PLAN.md` §0, §2 and §6 at
  the **head** revision, plus the PRD sections the phase file cites. Read §3 (PRD flags F1–F9) only
  when the diff touches one of the flagged requirements (scan the flag titles). Note every
  assumption ID the phase lists as "in force".
- Check the dependency phases are `done` in §0 at the merge base. If not, that is the first blocker.

### 2. Gather the mechanical context

Run:

```bash
python3 ${CLAUDE_SKILL_DIR}/scripts/review_context.py --base <BASE> --head <HEAD>
```

It reports the phase detection, files by area, process signals with warnings (goldens without a
changelog, pins without a THIRD_PARTY row, contract touched without a version bump, parameter
freeze file touched, WAVs or large binaries added), a boundary check of the head tree, an NFR-8
scan of `src/sim` for preset/scene/material names, and heuristic scans for audio-thread,
determinism, test-hygiene and pin red flags on the added lines. Every scan hit is a line to read,
not a verdict: open the file at HEAD and decide. The audio-thread scan marks hits inside functions
that look like audio callbacks; hits in `prepareToPlay`, constructors or editor code are normal.

### 3. Process gate (references/process-rules.md)

Decide each of these and keep the evidence for the review:

1. Scope: every diff hunk belongs to this phase's scope or is an explicitly justified fix. Work
   belonging to another phase is a blocker even when it is good work.
2. Status table: row moved to `in progress` first, then to `done`/`blocked` with PR link, date and
   the numbers the phase file asks for. `done` with any criterion not proven is a blocker.
3. Assumptions: the phase's assumptions are used as written and cited in code; any new decision
   has an `AX` row; any changed assumption or threshold has a §6 row.
4. Contract boundary and contract versioning rules.
5. Goldens, tolerances, skips.
6. PR description contract: the six sections, with each automated criterion linked to CI evidence.
7. CI evidence: with `get_check_runs` on the head SHA, confirm every job is green (format, build on
   linux/macos/windows, ASan, and any phase-specific jobs such as python, automation, nightly).
   Confirm the linked run is for the head SHA, not an earlier commit. Confirm artifacts the
   description promises exist (plugin bundles, pluginval logs, listening pack). A red or missing
   job makes the PR "not ready", whatever the code looks like.

### 4. Read the whole diff, tests first

Read every changed file at HEAD, not only the hunks. Order:

1. **Tests and fixtures.** For each automated acceptance criterion in the phase file, find the
   test that proves it and record: file and test name; what reference it compares against
   (analytic, pyroomacoustics, direct convolution, golden, self); the tolerance and whether it
   equals the phase file's number; the inputs (random seeded? how many cases? edge values?). Then
   ask the mutation question: *name one plausible bug in the implementation that this test would
   not catch.* If the answer is a bug the phase file specifically warns about, the test is
   inadequate and that is a finding on its own. A criterion with no test at all gets the row
   "Test: none; Bug it would miss: any; Verdict: not proven".
2. **Implementation.** Read with the domain reference open. Re-derive formulas on paper or with a
   short Python check (allowed: compute Eyring T60 for a fixture, count image sources for an
   order, compute an ITD from geometry) and compare with what the code and the tests expect.
3. **Threading and lifetime** for anything near the audio thread: who allocates, who frees, which
   thread reads which field, which operations are atomic and with which memory order, what
   happens when the builder is slower than the audio callback, what happens in non-realtime mode.
4. **Docs, schema, THIRD_PARTY, CI changes, CLAUDE.md edits.**

### 5. Verify what you can

- Build and run the tests when `--local` was given, or when `build/debug/_deps` already exists
  (a cold JUCE fetch and build takes 10–20 minutes and is not worth it for a review; CI already
  did it). In that case configure and build the `debug` preset, run `ctest --preset debug` (under
  `xvfb-run -a` on headless Linux) and `pytest tools/acoustics` when it exists. Report exactly what
  you ran and the result. Never skip or weaken a test to get a pass.
- Otherwise do partial verification and say so: compile a single changed translation unit with
  the project's warning flags when a build break is suspected, run quick independent calculations
  in Python for numeric claims, and read CI logs through `get_job_logs` for benchmark numbers,
  pluginval output and pytest summaries.
- Anything you could not verify is reported as a **Question** with what evidence would settle it,
  never as a pass.

### 6. Write the review

Use exactly this structure. Keep every finding specific: file, line, what is wrong, why it matters
here (cite the phase file, the assumption ID, or the reference file), and what resolves it.

```
# Review: PR #<n> — phase-XX <title>   (head <sha7>, base <branch>)
  (branch review: "Review: branch <name> — phase-XX <title>")

## Verdict
<Approve | Request changes | Not ready (CI)> — one paragraph: what the PR does, the state of the
automated criteria, and the single most important finding.

## Process gate
- Scope: ...            - Dependencies: ...        - Status table / §6: ...
- Assumptions used: ... - New/changed assumptions: ...
- Boundary & contract: ...                          - Goldens/tolerances/skips: ...
- PR description sections: (what is missing)        - CI: (jobs, head SHA match, artifacts)

## Acceptance criteria audit
| # | Criterion (phase file) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |

## Findings (by severity)
### Blockers
1. `path:line` — ...
### Major
### Minor
### Questions (unverified, evidence requested)

## What I verified myself
(commands run and results, calculations re-derived, logs read; or "nothing built: no toolchain")

## For Maisara
Listening checklist: untouched; it is yours. Where the listening-pack / plugin artifacts are.
Anything the Expert should see (accuracy shortfalls reported, not tuned).

## Contractor review focus (from the phase file), with pointers into the diff
(if a focus item has no counterpart in the diff, say so and name the file where it will live)
```

Severity definitions are in `process-rules.md` §9. A review with no blocker and no major finding
whose acceptance-criteria audit has every row at "Verdict: proven" may Approve. Otherwise Request
changes, and say in one sentence what would flip it.

### 7. Deliver

- Save the review to `review-PR<n>-phase-XX.md` (branch review: `review-<branch-slug>-phase-XX.md`)
  in the working directory (or the scratchpad in a cloud session) and print it in chat.
- Post to GitHub only when `--post` was given or the user asked for it: create a pending review
  with `pull_request_review_write` (`create`), add line comments for blockers and majors with
  `add_comment_to_pending_review`, and submit with `submit_pending` as **COMMENT** (never
  APPROVE or REQUEST_CHANGES on the author's behalf unless the user said so). End every GitHub
  post with the attribution footer required by the session.
- Never merge. Never tick the listening checklist. Never propose preset-specific tuning in `src/sim`;
  when accuracy falls short, say what the report should tell the Expert.

## Conduct

- Verified over plausible. If you did not run it, read it, or compute it, you do not know it; say
  so.
- Judge tests by the bugs they can see, not by their count or their green colour.
- Cite IDs (`AQ4`, `AX5`, `NFR-8`, `phase-06 §acceptance`) so Maisara and the contractor can follow
  without the reference files.
- No style findings beyond what blocks (CI formats); no re-litigating settled assumptions; a
  disagreement with an assumption is a note "for the Expert", not a finding against the PR.
- The author is a future session that will read your review cold: make each finding actionable in
  one pass, and separate "must change" from "would be nice".
