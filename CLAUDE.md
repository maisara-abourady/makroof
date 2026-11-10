# CLAUDE.md — Spatial Scene VST (repo: makroof)

A commercial VST3/AU plugin that renders a track as if it were played in a 3D space the user
designs. Requirements: `docs/PRD.md`. Plan and status: `docs/BUILD_PLAN.md`. Per-phase
instructions: `docs/phases/phase-XX.md`.

## The one rule for every session

**Each session executes exactly one phase.**

1. Read, in order: this file → `docs/BUILD_PLAN.md` (§0 status, §2 assumptions, §3 flags) → the
   phase file you were asked to execute → the PRD sections the phase file cites.
2. If the phase file has a **"Raise with Maisara"** section, raise every item in it in your first
   message and again in the PR description. Maisara does not track these herself.
3. Check that every phase this one depends on is `done` in the status table. If one isn't, stop and
   report it. Don't build on unfinished phases.
4. Set the phase to `in progress` in `docs/BUILD_PLAN.md` §0 and commit that first.
5. Do the phase's scope and nothing outside it. If you find work that belongs to another phase,
   write it under "Follow-ups" in your PR description. Don't do it.
6. When every **automated** acceptance criterion passes in CI on Linux, macOS and Windows (a run that
   CI skipped because the tree already passed counts; cite the run its `ci ok` summary links):
   - set the status to `done` (or `blocked (reason)`), fill in the PR link, date and short notes;
   - add a row to the change log (§6) if you changed an assumption, a threshold or a golden file;
   - put the phase's **listening checklist** in the PR description for Maisara, with where to
     find the listening-pack artifact;
   - put the phase's **contractor review focus** in the PR description.
7. Validate the session's scope list (next section). Then stop. Don't start the next phase.

If a phase can't be finished in two sessions, split the remainder into `phase-XXb.md`, add it to
the status table, and stop.

## Scope list: open with it, close on it (every build or execution session)

A build or execution session is any session that changes code, tests, tooling, CI or plan status,
a phase session included. Pure questions and reviews are not.

1. **Open with the list.** The first message starts with the session's scope as a numbered list,
   one short line per item: a bold label of two to four words, then the intended outcome as a
   checkable result, not an activity (e.g. `3. **ISM unit tests** — image-source tests pass in
   ctest on all three CI platforms`). In a phase session the items come from the phase file's scope
   and automated acceptance criteria, plus the bookkeeping above (status `in progress`, status
   `done`, PR description). "Raise with Maisara" items come right after the list.
2. **The list is the contract.** It defines "done" for the session. If the scope has to change,
   restate the whole list with the change marked and the reason. Never drop or soften an item quietly.
3. **Validate before reporting.** At the end, go through the list item by item and check each one
   against evidence you can point to (command output, CI run, commit, file), not memory. Mark each
   ✅ with its evidence.
4. **No report until every item is checked.** While any item is unchecked, keep working; don't end
   the session or report back. If an item genuinely cannot be finished in this session (a decision
   only Maisara can make, missing access, the two-session limit), restate the list (rule 2) with it
   replaced by its hand-off (e.g. `phase-XXb.md` written, status `blocked (reason)` committed), check
   that, and say so at the top of the report. The final report starts with the fully checked list.

## Reporting: the steward (every session, not only phases)

The main session is the **orchestrator**. It reports to the `steward` agent, not to Maisara, and
decides itself which agent does what. The steward's memory is the session brief (`docs/sessions/`,
template in its README).

1. At the start, write `docs/sessions/<YYYY-MM-DD>-<slug>.md`, with Maisara's words verbatim, the
   objectives with done-criteria, the scope, the settled decisions and the "Raise with Maisara" items.
   In a build or execution session, the brief's objectives are the items of the opening scope list
   (section above), one for one. Run the steward on it and fix it until it returns BRIEF OK. Commit it.
2. After each substantial step, and always before reporting to Maisara, report to the steward with
   the brief's path and the evidence (files, diffs, CI runs, agent reports). Append its round note to
   the brief's steward log. On CONTINUE, close the gaps it lists by delegating as you judge best.
3. Speak to Maisara only on **READY TO REPORT** (send its draft, edited for accuracy) or **NEEDS
   MAISARA** (ask its questions). Append each new instruction from her to the brief verbatim. The
   "Raise with Maisara" items (step 2 of "The one rule for every session") still go in your first message to her.

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
  The main session runs these steps itself; Maisara doesn't have to ask for them.

## The board (decision loop)

Open choices that the corpus alone does not settle are decided by the **decider** sitting over a board of
nine subject-matter seats (`docs/board/README.md`; personas in `docs/board/`, agents in `.claude/agents/`):

| Seat | Agent | Subject matter |
|---|---|---|
| 1 | `seat1-perceptual-gatekeeper` | what the listener can hear or prefers; JNDs, blind tests, keep/cut/test, realism claims |
| 2 | `seat2-engine-architect` | geometry and materials → room response; GA/wave/hybrid, scattering, diffraction, validation |
| 3 | `seat3-reverb-renderer` | response → audio; FDN/convolution, time variance, coloration, CPU per instance |
| 4 | `seat4-chain-keeper` | delivery to the ear; HRTF, headphone compensation, decoding, formats, loudness parity |
| 5 | `seat5-deadline-keeper` | the audio thread and hosts; real-time safety, threading, pluginval, formats, CI gates |
| 6 | `seat6-canvas-designer` | the user's controls and canvas; names, ranges, defaults, presets, automation, workflow |
| 7 | `seat7-founder` | price, free tier, protection, channels, licensing, cadence, runway, public wording |
| 8 | `seat8-storyteller` | what producers do with it; whose ears, point of view, anchor, contrast, translation |
| 9 | `seat9-room-acoustician` | real rooms as references; audible geometry and materials, library provenance, presets |

- The decider **convenes**: for every subject matter it fills a nine-row table (each seat convened or
  recorded not required with the reason) and returns CONVENE; the main session runs the convened seats in
  parallel (and the **researcher**, the decider's assistant for external evidence: papers, standards,
  dataset and licence documentation, statistics and base rates). Each seat is its own advocate: it
  ranks the options and rates its own tension **now** and **later** (0–3; 3 is veto-grade).
- The decider decides at the **point of minimum tension among all nine, now and in the future**: inside
  the PRD's hard constraints and Maisara's settled decisions, drop any option a seat rated veto-grade
  (only Maisara overrides a veto), then minimise the worst-off seat over both columns, then the sum, then
  prefer the cheaper-to-undo option; every decision carries a future-debt register. No decision borrows
  from later phases silently.
- The **interrogator** pushes back: convening (UNDERCONVENED), the tension map against the seats' words
  (TENSION MISREAD), the debt register, the ordering, and every load-bearing fact against `docs/corpus/`.
  A decision stands only if it SURVIVES. There is no advocate agent.
- `/fix-plan` runs the loop (step 3); outputs of every round are saved under `docs/review/<target>/`.
- Agent files for the seats are **generated**: `python3 .claude/board/build_agents.py` (`--check` to
  verify) from the persona's sections 0–18 plus `docs/board/seat-protocol.md`. Never edit a persona or a
  generated seat file by hand. An agent type added in a session may not be listed by the Agent tool at
  once (it was picked up mid-session on 2026-11-09, but not immediately); try the type first, and if it is
  not found run the seat as a `general-purpose` worker given its agent file verbatim, saying so in the
  transcript.
- Never add preset-specific or scene-specific logic to `src/sim/` (PRD NFR-8). If accuracy falls
  short for a scene, report it. Don't tune for it.

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
docs/           PRD, BUILD_PLAN, phases/, contract/, validation/, board/ (the nine personas, protocol)
.claude/        agents/ (decider, interrogator, researcher, plan-editor, steward, seat1–9), commands/, board/ (agent generator)
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
python tools/ci/listening_pack.py --phase phase-04

# golden files: the ONLY way to update them (appends the reason to tests/golden/CHANGELOG.md)
python tools/ci/update_goldens.py --reason "<why>" -- <pytest args selecting the tests>
# --extend also pins keys the golden lacks (e.g. a BRAS room added to validation_baseline); never drops one

# pluginval strictness 10 (downloads the pinned release by checksum on first run; xvfb on Linux)
tools/ci/run_pluginval.sh build/release/SpatialScene_artefacts/Release/VST3/SpatialScene.vst3

# macOS only: AU validation (component must be copied to ~/Library/Audio/Plug-Ins/Components)
auval -v aufx Spsc Mkrf

# offline render (Phase 02+); exit codes 0 ok, 1 usage, 2 invalid scene, 3 I/O, 4 internal (AX12)
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --in in.wav --out out.wav
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --ir ir.wav
# Phase 04+: --mode omni = hybrid room IR (ISM + late tail), --mode omni-early = the Phase 03
# early-reflection-only IR to maxReflectionOrder (binaural/stereoSpeakers stay a dry stub until 08/09);
# --images writes the image-source list as JSON (omni: the AX20 time-bounded list); --diagnostics writes
# T60/t_mix/matching per emitter; --no-air-absorption is for validation only (AX4)
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --mode omni --ir ir.wav --diagnostics diag.json
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --mode omni-early --ir ir.wav --images images.json
# validation ensembles (AX11): N tail seeds from --tail-seed in one WAV, optionally the tail alone / one emitter
build/cli/render_cli --scene tests/scenes/valid/club.json --mode omni --tail-seed 1000 --ensemble 64 --tail-only --ensemble-emitter 0 --ir ens.wav
# AX22 sensitivity: override the image-count cap N_cap (validation only), e.g. nu_r(20) = 11520
build/cli/render_cli --scene tests/scenes/valid/medium_room.json --mode omni --image-cap 11520 --ir ir.wav
# Phase 04: sigma1(EDT), sigma1(C80) of the hybrid IR (AX19) -> tools/acoustics/data/phase04_sigma1.json
python -m tools.acoustics.measure_sigma1

# Phase 06: render --in through the real-time engine (sim::RealtimeEngine, partitioned convolution) in
# host blocks of N or random sizes 1..2048; same length/alignment as the offline render, so the two null.
# --switch-scene/--switch-every alternate two rooms' IRs (the listening pack's ir_switch_demo)
build/debug/render_cli --scene tests/scenes/valid/medium_room.json --mode omni --in in.wav --out rt.wav --realtime-emulation --block random [--partition 256]
build/debug/render_cli --scene tests/scenes/valid/living_room.json --switch-scene tests/scenes/valid/concert_hall_box.json --switch-every 0.5 --mode omni --in tone.wav --out sw.wav --realtime-emulation

# ISM, AQ10 W1/W2 and Phase 06 real-time convolution benchmarks (hidden Catch2 tests, CI runs them from
# the release build; the Linux runner's W2 sweep sets N_cap, AX22)
build/release/tests/unit/spatial_tests "[benchmark]" --benchmark-samples 10

# TSan on the real-time convolver and the Phase 07 scene pipeline (CI job `tsan`, Linux; the JUCE
# plugin isn't needed: the pipeline is the JUCE-free spatial_plugin_core in src/plugin/core/)
cmake --preset tsan -DSPATIAL_BUILD_PLUGIN=OFF && cmake --build --preset tsan --target spatial_tests
build/tsan/tests/unit/spatial_tests "[conv],[pipeline]"

# Phase 07: state fixtures tests/state/v<N>_*.bin (regenerate only when pluginStateVersion is bumped,
# adding the new version's files; old fixtures must keep loading)
build/debug/tests/unit/spatial_tests "[.generate-state-fixtures]"
```

**When CI skips.** `ci.yml` starts with a `changes` job that fingerprints every tracked file except
prose no build or test reads (`tools/ci/ci_fingerprint.py`: `docs/sessions/`, `docs/review/`,
`docs/phases/`, `docs/board/`, `docs/PRD.md`, `docs/BUILD_PLAN.md`, `docs/THIRD_PARTY.md`, `CLAUDE.md`,
`README.md`, `.claude/`). If a run on the same fingerprint passed every job, all jobs are skipped and the `ci ok`
check links that run (its jobs and artifacts, listening pack included, are the evidence). A PR's markers
are visible only to that PR (CI no longer runs on `main`). To force a full run: Actions → CI → Run
workflow with `force`. Add a
path to the exclusions only if `pytest tools/ci` (which greps code for reads of them) still passes.
Every new CI job needs `needs: changes`, the `if:` gate and an entry in `ci-ok`'s `needs`
(`tools/ci/test_ci_workflow.py` fails otherwise).

**When CI runs (Maisara, 2026-11-08).** `ci.yml` starts by itself only when a PR is opened, reopened or
marked ready for review; `nightly.yml` (the BRAS validation, no longer scheduled) the same, for PRs that
touch `src/sim/` or the validation files. Pushes to an open PR, `main` and the clock start nothing.
Every other run is started by hand: Actions → CI (or nightly validation) → Run workflow, on the PR's
branch (or the session triggers it with the GitHub tools). `tools/ci/test_ci_workflow.py` pins these
triggers.

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
- **Determinism:** anything random is seeded from scene data (`tailSeed`), except the diffuse tail-level estimator, whose
  key is a fixed constant so that E_target never depends on `tailSeed` (AX40, Maisara 2026-11-10). Offline (non-realtime)
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
- **When to open a PR (Maisara, 2026-11-08).** Open a PR only when the work is finished: no further
  logic changes, no pending decisions, no ongoing conversations. Before opening it, the steward has
  cleared the session and `/review-phase-pr` has run on the branch's diff, with its fixes in. Opening
  the PR runs CI once. After that, push to it only for (1) fixes that a CI failure calls for (e.g. a
  macOS/Windows compile error that can't be reproduced locally) and (2) changes the contracted
  engineer's review asks for; batch each round into one push, then start one manual CI run on the
  branch (pushes don't start CI). Bookkeeping that touches only fingerprint-excluded prose (status row,
  PR link, session brief) may follow without a run.
- Commit messages: `phase-XX: <imperative summary>`.
- The PR description contains: what was done, acceptance-criteria checklist with CI evidence,
  listening checklist for Maisara, contractor review focus, follow-ups, assumption/golden changes.
- Never commit downloaded datasets (BRAS, SOFA originals). Download by checksum in scripts. The
  converted embedded HRTF is the one exception, once its licence is confirmed.
