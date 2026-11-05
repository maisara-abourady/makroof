# CLAUDE.md — Spatial Scene VST (repo: makroof)

A commercial VST3/AU plugin that renders a track as if it were played in a 3D space the user
designs. Requirements: `docs/PRD.md`. Plan and status: `docs/BUILD_PLAN.md`. Per-phase
instructions: `docs/phases/phase-XX.md`.

## The one rule for every session

**Each session executes exactly one phase.**

1. Read, in order: this file → `docs/BUILD_PLAN.md` (§0 status, §2 assumptions, §3 flags) → the
   phase file you were asked to execute → the PRD sections the phase file cites.
2. Check that every phase this one depends on is `done` in the status table. If one isn't, stop and
   report it. Don't build on unfinished phases.
3. Set the phase to `in progress` in `docs/BUILD_PLAN.md` §0 and commit that first.
4. Do the phase's scope and nothing outside it. If you find work that belongs to another phase,
   write it under "Follow-ups" in your PR description. Don't do it.
5. When every **automated** acceptance criterion passes in CI on Linux, macOS and Windows:
   - set the status to `done` (or `blocked (reason)`), fill in the PR link, date and short notes;
   - add a row to the change log (§6) if you changed an assumption, a threshold or a golden file;
   - put the phase's **listening checklist** in the PR description for Maisara, with where to
     find the listening-pack artifact;
   - put the phase's **contractor review focus** in the PR description.
6. Stop. Don't start the next phase.

If a phase can't be finished in two sessions, split the remainder into `phase-XXb.md`, add it to
the status table, and stop.

## Assumptions and decisions

- Q1–Q10 from the PRD are **unresolved**. The plan runs on the defaults in `BUILD_PLAN.md` §2
  (IDs `AQ1`–`AQ10`, `AX1`–`AX8` and any added later). Cite the ID in code comments where a default shapes the code
  (e.g. `// AQ4: 30 ms equal-gain crossfade`).
- Never invent an answer quietly. If you need a decision that isn't covered, add a new `AX<n>` row
  (assumption, one-line rationale, phases that break), mention it in the PR, and keep the change small.
- **Acoustic decisions are verified, not invented.** Changes to the PRD, BUILD_PLAN or phase files go
  through `/fix-plan` (the `plan-editor` subagent applies them; any acoustic or numeric choice it would
  have to make goes to the `interrogator` first). In a phase session, a new or changed AX/AQ value gets
  an interrogator check against `docs/corpus/` before it is committed, and the PR links the ledger rows.
  The main session runs these steps itself (see "Subagents and skills" below); Maisara doesn't have to ask for them.
- Never add preset-specific or scene-specific logic to `src/sim/` (PRD NFR-8). If accuracy falls
  short for a scene, report it. Don't tune for it.

## Subagents and skills: who does what

The main session is always the orchestrator. Subagents cannot start other subagents, so the main session
calls each one itself, passes outputs between them, and does this without being asked. Never ask Maisara
which agent to use: the trigger column below decides it. Ask Maisara only for the cases in "Who decides".

| Who | Responsible for | Call it when | Gets from you | Gives back | Never |
|---|---|---|---|---|---|
| `interrogator` (subagent, read-only) | **Scientific correctness** of plan text and AX/AQ values, judged only against `docs/corpus/` | Before starting any phase (on its phase file); on any new or changed AX/AQ value, tolerance, formula or threshold; on `plan-editor` DECISIONS NEEDED; on the finished `/fix-plan` diff | The file or passages, or the decision options | Issue ledger (`id \| kind \| item \| verdict \| evidence \| severity \| question \| status`), verdicts CORRECT / WRONG / CONDITIONS VIOLATED / IMPRECISE / NOT CHECKABLE / INCONSISTENT | Edits files, judges product decisions, proposes implementations |
| `advocate` (subagent, read-only) | **Product counterweight**: cross-examines interrogator findings for evidence, applicability, materiality, proportionality and scope, in favour of the PRD | After every `/interrogate` run or interrogator consultation whose findings would change the plan (any non-CORRECT row above minor), **before** those findings go to `/fix-plan` | The interrogator ledger rows or report, and the target file | Verdict per item (CONCEDED / CHALLENGED / NARROWED / ALTERNATIVE / UNDECIDED), a recommended position for Maisara, rebuttal questions for the interrogator | Edits files, overrides a WRONG result that a gate, golden or shipped behaviour rests on |
| `plan-editor` (subagent, edits docs only) | **Applying** specified corrections to `docs/PRD.md`, `docs/BUILD_PLAN.md`, `docs/phases/*.md` | Only through `/fix-plan`, once the fixes are settled | Exact fixes, ledger row ids, every decision already verified | Applied / Held / DECISIONS NEEDED / Interpretations / `git diff --stat` | Makes acoustic or numeric choices, touches `src/`, `tests/`, `tools/`, `docs/contract/`, goldens or the ledger, commits |
| `/interrogate <file>` (command) | Running the interrogator on a document, appending `docs/review/ledger.md`, answering as the builder (≤ 3 rounds) | Auditing a PRD, BUILD_PLAN or phase file | Path of the file | Ledger section with row statuses | — |
| `/fix-plan <fixes>` (command) | Any change to PRD, BUILD_PLAN or phase files: plan-editor applies, interrogator verifies decisions and the diff, ledger updated, commit `plan: …` | Any time those files must change, in or outside a phase session | Fixes or ledger row ids (after the advocate pass) | Committed, pushed change and a report | — |
| `/review-phase-pr <pr \| branch>` (skill) | **Reviewing a phase PR** as the contracted engineer and plan gatekeeper | Every phase PR, before Maisara goes through a listening checklist; any "review / check / is it ready" request about a PR or branch | PR number or branch | Severity-ranked review with evidence | Writes PR descriptions or implements the phase |
| `Explore` / `Plan` (built-in) | Wide read-only code search / implementation planning inside a phase | A search across many files, or planning a large phase step | A narrow question | Conclusion, not file dumps | Decides acoustics (that is the interrogator's job) |

**Standard pipelines** (run them end to end, in this order):

1. *Plan audit*: `/interrogate <file>` → `advocate` on the open rows → interrogator answers the
   advocate's questions (one rebuttal round) → settled rows go to `/fix-plan`.
2. *Plan change*: `/fix-plan` (plan-editor → interrogator on DECISIONS NEEDED → plan-editor applies →
   interrogator on the diff → ledger, commit).
3. *New or changed AX/AQ value in a phase session*: interrogator on the value → advocate if the verdict
   is not CORRECT → record in the ledger → commit; link the ledger rows in the PR.
4. *Phase PR*: CI green → `/review-phase-pr` → fix what it finds (in scope) → listening checklist for Maisara.

All corpus-based steps first make sure `docs/corpus/SOURCE_COMMIT` exists (`tools/ci/fetch_corpus.sh`;
in a cloud session attach `maisara-abourady/audio-resources` first). If the corpus can't be fetched, stop
and report it; don't fall back to recollection.

**Who decides.** The corpus decides acoustics, the PRD decides product questions, Maisara decides the rest.
Adopt a finding without asking when the interrogator rates it WRONG or CONDITIONS VIOLATED and the
advocate CONCEDES, or when exactly one option is CORRECT. Ask Maisara (briefly, with both sides' evidence)
when the advocate CHALLENGES, NARROWS or proposes an ALTERNATIVE and the rebuttal round doesn't settle it,
when several options are valid or none is, or when the choice is a product matter.

## Repository layout

```
src/contract/   SceneDescription types, JSON I/O, validation, versioning   (no JUCE)
src/sim/        Simulator: ISM, tail, HRTF, IR builder, convolver            (depends on contract only, no JUCE)
src/module3d/   3D Module: editable scene model, params <-> scene, presets   (depends on contract only)
src/plugin/     JUCE AudioProcessor + editor, state, threading glue
src/cli/        render_cli (offline renders for tests and listening packs)
tests/unit/     Catch2 tests (one file per source unit)
tests/scenes/   contract fixtures (valid/ and invalid/)
tests/golden/   golden metric JSON and small reference WAVs
tools/acoustics Python analysis package + pytest (ISO 3382 metrics, click detector, comparisons)
tools/hrtf/     SOFA -> embedded HRTF converter
tools/ci/       CI helper scripts (boundary check, pluginval runner, listening pack)
resources/      HRTF binary, materials.json, presets
docs/           PRD, BUILD_PLAN, phases/, contract/, validation/
```

### The contract boundary (hard rule)

- `src/sim` and `src/module3d` never include each other. Only `contract::SceneDescription` crosses.
  `tools/ci/check_boundaries.py` enforces this in CI.
- A change to the contract always means: bump `contractVersion` (minor for additive changes, major for
  breaking ones), update `docs/contract/scene-v1.schema.json` and `docs/contract/README.md`, add
  fixtures, and add a migration test if the change breaks anything. No exceptions.

## Build and test

(Set up in Phase 00. Keep this section accurate if you change the commands.)

```bash
# configure + build (Debug); presets: debug, release, asan (Linux), tsan (Linux),
# cli (render_cli only: Release, no JUCE, no tests -> build/cli/render_cli; what the python CI job uses)
cmake --preset debug
cmake --build --preset debug

# C++ unit tests (the test presets already enable --output-on-failure)
ctest --preset debug

# warnings as errors, as CI builds: set SPATIAL_WERROR=ON in the environment before configuring
SPATIAL_WERROR=ON cmake --preset debug

# formatting (CI runs the check with clang-format 18)
tools/ci/check_format.sh          # check
tools/ci/check_format.sh --fix    # reformat src/ and tests/

# contract boundary check and the tools/ci Python tests (schema agreement, boundary self-test)
python3 -m venv .venv && . .venv/bin/activate
pip install -r tools/ci/requirements.txt
python tools/ci/check_boundaries.py
pytest tools/ci

# Python analysis tooling (Phase 02+). The render_cli end-to-end tests find the binary through
# RENDER_CLI or build/{cli,release,debug}/; they skip when it is missing unless
# SPATIAL_REQUIRE_RENDER_CLI=1 (set in CI)
python3 -m venv .venv && . .venv/bin/activate
pip install -r tools/ci/requirements.txt -r tools/acoustics/requirements.txt   # hash-pinned; after changing a pin:
                                     # python tools/ci/pin_hashes.py tools/ci/requirements.txt tools/acoustics/requirements.txt
pytest tools                         # tools/ci + tools/acoustics, as the python CI job runs it
python -m tools.acoustics metrics ir.wav          # ISO 3382 metrics as JSON (also: compare a.wav b.wav, clicks out.wav)

# reference corpus for the interrogator subagent / /interrogate (private repo audio-resources -> docs/corpus/,
# git-ignored; never commit it)
tools/ci/fetch_corpus.sh

# listening pack (CI artifact `listening-pack`): build/listening-pack/<phase>/
python tools/ci/listening_pack.py --phase phase-03

# golden files: the ONLY way to update them (appends the reason to tests/golden/CHANGELOG.md)
python tools/ci/update_goldens.py --reason "<why>" -- <pytest args selecting the tests>

# pluginval strictness 10 (downloads the pinned release by checksum on first run; xvfb on Linux)
tools/ci/run_pluginval.sh build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3

# macOS only: AU validation (component must be copied to ~/Library/Audio/Plug-Ins/Components)
auval -v aufx Spsc Mkrf

# offline render (Phase 02+); exit codes 0 ok, 1 usage, 2 invalid scene, 3 I/O, 4 internal (AX12)
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --in in.wav --out out.wav
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --ir ir.wav
# Phase 03+: --mode omni = early-reflection IR (binaural/stereoSpeakers stay a dry stub until 08/09);
# --images writes the image-source list as JSON; --no-air-absorption is for validation only (AX4)
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --mode omni --ir ir.wav --images images.json

# ISM benchmark (hidden Catch2 test, CI runs it from the release build)
build/release/tests/unit/spatial_tests "[benchmark]" --benchmark-samples 10
```

Binary dirs are `build/<preset>/`. Plugin bundles land in
`build/<preset>/SpatialScene_artefacts/<Config>/{VST3,AU,Standalone}/`.

Linux build deps (Ubuntu 24.04): `build-essential cmake ninja-build pkg-config libasound2-dev
libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxext-dev libfreetype-dev
libfontconfig1-dev libgl1-mesa-dev xvfb`. pluginval with an editor on Linux needs `xvfb-run`
(`run_pluginval.sh` adds it when there is no display); run `ctest` under `xvfb-run -a` on a
headless Linux box too, because the pass-through test initialises the JUCE GUI runtime.

Windows: run the CMake commands from an "x64 Native Tools Command Prompt for VS 2022" (CI uses
`ilammy/msvc-dev-cmd`) so that the Ninja presets find MSVC. The scripts in `tools/ci/` run under Git Bash.

## Code conventions

- C++20, `clang-format` (config in repo root) on every changed file. Warnings as errors in CI.
- **Audio thread:** no heap allocation, locks, file I/O, logging or exceptions in `processBlock`
  or anything it calls. Hand data between threads through lock-free single-producer/single-consumer
  structures or atomic pointer swaps. Tests check this where they can (allocation-tracking test from Phase 06).
- **Determinism:** anything random is seeded from scene data (`tailSeed`). Offline (non-realtime)
  rendering must be bit-identical run to run on the same platform.
- Units: SI everywhere (metres, seconds, Hz). Angles in radians internally, degrees in JSON and UI.
  Axes: x right, y forward, z up (AQ1).
- Name per-band arrays `bandsXxx` with the band set fixed in one place: `contract::kOctaveBandsHz`
  (63 Hz–8 kHz, 8 bands).
- Host parameter IDs are frozen once released (a test lists them). Add new IDs; never rename.
- Third-party code comes in through CMake `FetchContent` with a **pinned tag or commit**. Record
  every dependency and its licence in `docs/THIRD_PARTY.md`.

## Tests and golden files

- Every DSP behaviour must have an automated check. Maisara can't verify DSP by reading code, so
  "it sounds right" is never enough on its own.
- Prefer checks against **independent references** (analytic solutions, pyroomacoustics,
  direct convolution) over self-generated goldens.
- Golden files (`tests/golden/`) store metrics with tolerances, and small WAVs only where
  needed. **Never regenerate a golden to make a test pass** unless the change is intended.
  In that case use `tools/ci/update_goldens.py`, explain why in the PR, and add a change-log row
  to `BUILD_PLAN.md` §6.
- Listening packs: phases with audio output add their renders to `tools/ci/listening_pack.py`,
  and CI uploads them as the `listening-pack` artifact.

## Git and PRs

- Work on the branch the session specifies. One phase = one PR, reviewed by the contracted engineer.
- Reviews use the project skill `/review-phase-pr <pr-number | branch>` (`.claude/skills/review-phase-pr/`):
  it checks the PR against the phase file, the assumptions and the sourced domain references, and
  writes a severity-ranked review. Run it before asking Maisara to go through a listening checklist.
- Commit messages: `phase-XX: <imperative summary>`.
- The PR description contains: what was done, acceptance-criteria checklist with CI evidence,
  listening checklist for Maisara, contractor review focus, follow-ups, assumption/golden changes.
- Never commit downloaded datasets (BRAS, SOFA originals). Download by checksum in scripts. The
  converted embedded HRTF is the one exception, once its licence is confirmed.
