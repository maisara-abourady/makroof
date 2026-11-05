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
  The main session runs these steps itself (see "Who works on this project" below); Maisara doesn't have to ask for them.
- Never add preset-specific or scene-specific logic to `src/sim/` (PRD NFR-8). If accuracy falls
  short for a scene, report it. Don't tune for it.

## Who works on this project

Two different things help a session: **people** (humans and subagents), who each own a part of the
process, and **tools** (skills and commands), which are procedures any of them can run. Know who owns
a step before reaching for a tool.

### The team

Each subagent is a team member with a role, not a utility. Bring them in at their point in the process
without being asked, and never ask Maisara which one to involve. Subagents cannot call each other, so
the lead builder carries work between them.

- **Maisara — owner.** Owns what the product is and the final call on anything the corpus and the PRD
  don't settle. Listens to the listening packs. Is asked briefly, with evidence, never for routine steps.
- **The contracted engineer — reviewer.** Owns sign-off on physics, DSP and real-time code in every
  phase PR. A session stands in for them before handover with `/review-phase-pr`.
- **The lead builder — the main session.** Owns the phase end to end: scope, code, tests, CI evidence,
  the PR. Runs the process below, hands work to the others, and is the only one who commits.
- **The interrogator — the scientific prosecutor.** Owns the truth of every acoustic, psychoacoustic
  and signal-processing claim and number, with `docs/corpus/` as its only authority. Comes in before a
  phase starts, whenever someone proposes an acoustic value or method, and after plan text is written.
  Judges; never edits, never rules on product choices, never proposes implementations.
- **The advocate — defence for the product.** Owns proportionality: that what the interrogator finds is
  weighed against what the PRD needs (evidence, applicability, audibility, cost, scope). Comes in after
  the interrogator has found something that would change the plan, before it is adopted. Uses the same
  corpus and concedes when it is against the plan; never overrides a WRONG result that a gate, golden
  or shipped behaviour rests on. Argues; never edits.
- **The plan editor — the scribe.** Owns the wording of `docs/PRD.md`, `docs/BUILD_PLAN.md` and
  `docs/phases/`. Comes in once fixes are settled, writes them, and hands back every acoustic or numeric
  choice it would have had to make instead of making it. Never touches code, tests, goldens or the
  ledger; never commits.

**How they work together:**

1. *Before a phase:* the interrogator audits the phase file; the advocate cross-examines what it found;
   the interrogator answers the advocate once. What is settled goes to the scribe; what isn't goes to Maisara.
2. *When the plan changes:* the scribe writes; the interrogator verifies each choice the scribe handed
   back and then the finished text. Every verdict lands in `docs/review/ledger.md`.
3. *During a phase:* a new or changed AX/AQ value goes to the interrogator, and to the advocate if the
   verdict is not CORRECT, before it is committed. The PR links the ledger rows.
4. *At the end of a phase:* CI green → review in the contracted engineer's place → fix in-scope findings
   → listening checklist to Maisara.

Anything that uses the corpus first makes sure `docs/corpus/SOURCE_COMMIT` exists
(`tools/ci/fetch_corpus.sh`; in a cloud session attach `maisara-abourady/audio-resources` first). If it
can't be fetched, stop and report it; nobody falls back to recollection.

**Who decides.** The corpus decides acoustics, the PRD decides product questions, Maisara decides the
rest. Adopt a finding without asking when the interrogator rates it WRONG or CONDITIONS VIOLATED and the
advocate concedes, or when exactly one option is CORRECT. Ask Maisara when the advocate challenges,
narrows or offers an alternative and the rebuttal doesn't settle it, when several options are valid or
none is, or when the choice is a product matter.

### Skills and commands

Procedures the team runs. They carry out steps of the process above; they don't own any of it.

| Skill / command | What it does | Use it when |
|---|---|---|
| `/interrogate <file>` | Runs the interrogator on a document, appends its ledger to `docs/review/ledger.md`, answers it as the builder (≤ 3 rounds) | Auditing the PRD, BUILD_PLAN or a phase file (step 1) |
| `/fix-plan <fixes \| ledger ids>` | Editor → interrogator on handed-back choices → editor applies → interrogator on the diff → ledger, commit `plan: …` | Any change to the PRD, BUILD_PLAN or phase files (step 2) |
| `/review-phase-pr <pr \| branch>` | Severity-ranked review of a phase PR against its phase file, assumptions and sourced references | Every phase PR before the listening checklist; any "review / is it ready" request (step 4) |
| `/code-review`, `/simplify`, `/security-review` | Generic diff review for bugs, cleanups, security | Optional extra passes on code; never a substitute for `/review-phase-pr` |
| `Explore`, `Plan` (built-in agents) | Wide read-only search; implementation planning | Searching many files or planning a large step inside a phase; they hold no role and decide nothing acoustic |

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
