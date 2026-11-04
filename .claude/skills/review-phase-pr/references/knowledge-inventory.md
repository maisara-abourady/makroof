# Knowledge inventory: what this reviewer must know, and why

This file is the map. It lists the domains of knowledge a pull request in this repository can
demand, why each one matters here, which phases exercise it, and which reference file holds the
facts. It was built on 2026-11-04 by reading every repo document (`CLAUDE.md`, `docs/PRD.md`,
`docs/BUILD_PLAN.md`, `docs/phases/phase-00..13.md`, the CMake files and CI workflow) and then
researching each domain live. Dates on facts in the reference files say when they were verified.

Why a map: Maisara cannot verify DSP by reading code (BUILD_PLAN §4, Phase 02), so the reviewer is
the only line of defence between a plausible-looking diff and a wrong plugin. A reviewer who only
knows C++ will approve an image-source model that applies absorption to pressure instead of
energy, or a tail whose envelope decays twice as fast as its T60 claims. The CI gates catch many of
these, but the tests are written by the same session that writes the code, so the reviewer must
also judge whether the tests can see the bug at all.

## Domains

| # | Domain | Why it matters in this repo | Phases | Reference file |
|---|---|---|---|---|
| K1 | **Project process rules**: one phase per PR, status table, assumptions `AQ`/`AX`, flags, golden policy, PR description contract, contract boundary | Every PR. The rules are what make a 14-phase build by stateless sessions coherent. A PR that quietly changes an assumption or widens scope damages later phases. | all | `process-rules.md` |
| K2 | **Per-phase scope and acceptance criteria**: what each phase must and must not deliver, its review focus, its traps | A PR is reviewed against its phase file, not against general taste. | all | `phase-checklists.md` |
| K3 | **Real-time audio C++ and JUCE plugin engineering**: audio-thread rules, lock-free handover, memory reclamation, denormals, FP determinism, `AudioProcessor` lifecycle, latency reporting, parameter IDs, state versioning, pluginval/auval | The product is a plugin. Bugs here are crashes, glitches and broken projects in users' DAWs, and most are invisible to listening tests. | 00, 06, 07, 10, 11, 13 | `realtime-audio-juce.md` |
| K4 | **Room acoustics theory**: image-source method, pressure vs energy coefficients, scattering, air absorption (ISO 9613-1), Sabine/Eyring, mixing time, hybrid IR construction, filterbanks, fractional delay | This is the physics the engine claims to implement. The classic bugs (α on pressure, wrong decay constant, double air absorption) produce IRs that look fine and measure wrong. | 03, 04, 05, 08, 09, 12 | `room-acoustics.md` |
| K5 | **Acoustic metrics and validation data**: ISO 3382-1 definitions and JNDs, Schroeder/Lundeby, octave filters, pyroomacoustics as reference, BRAS dataset, loudness (BS.1770), click detection | The measuring instruments are built in Phase 02 and gate every later phase. A wrong metric makes every gate meaningless. | 02, 03, 04, 05, 09, 10, 12 | `metrics-and-validation-data.md` |
| K6 | **Convolution and movement**: UPOLS/FDL algorithm, PFFFT contract, crossfades, update scheduling, tail caching, allocation tracking | The engine applies multi-second IRs in real time and swaps them under automation. Off-by-one partition indexing or a bad cache key are silent. | 06, 07, 10, 13 | `convolution-and-movement.md` |
| K7 | **Binaural and stereo rendering**: SOFA/AES69, HRTF datasets and licences, ITD/ILD reference values, interpolation, diffuse-field EQ, interaural coherence, virtual ORTF, loudness matching | Sign and coordinate conventions are where these phases fail. Licence errors here would block shipping. | 08, 09, 11, 12 | `binaural-and-stereo.md` |
| K8 | **Tooling, testing and licences**: CMake/FetchContent pinning, GitHub Actions hygiene, sanitizers, Catch2, golden-file discipline, JSON Schema, Python pinning, MSVC/macOS specifics, every third-party licence | Every PR touches the build or CI. Licence mistakes are the most expensive to undo. | all, esp. 00, 01, 02, 08, 12, 13 | `tooling-testing-licences.md` |
| K9 | **Review craft**: how to read a diff for a correctness bug, how to judge a test, severity, what evidence to demand, how to write a review the contractor and Maisara can act on | Without it the knowledge above becomes a lecture instead of a verdict. | all | `SKILL.md` (procedure) |

## What is deliberately *not* in the reviewer's knowledge

- Preset- or scene-specific tuning heuristics. PRD NFR-8 forbids them in the engine; the reviewer's
  job is to spot them, not to suggest them.
- Answers to the PRD's open questions Q1–Q10. They are unresolved; the reviewer checks that a PR
  uses the `BUILD_PLAN.md` §2 default and does not quietly answer a question.
- Licensing/subscription logic (post-v1 backlog B1).

## Freshness: facts that go stale and must be re-verified

Re-run the live checks below when a PR touches the item, or at least every phase.

| Item | Where used | How to re-verify |
|---|---|---|
| Latest JUCE tag; JUCE licence tiers and revenue caps. State on 2026-11-04: JUCE 9 (9.0.5) is the mainline, JUCE 8 is a security-patch branch whose newest tag is the pinned `8.0.17-security`; tiers Starter ≤ $20k / Indie ≤ $300k / Pro; JUCE 8 removed the splash-screen rule, so the "splash screen" note in `docs/THIRD_PARTY.md` is stale | `cmake/SpatialDependencies.cmake`, `docs/THIRD_PARTY.md`, Phase 13 | github.com/juce-framework/JUCE/releases, juce.com/legal/juce-9-licence (see `tooling-testing-licences.md` §0–§1) |
| pluginval latest release and CLI flags | `tools/ci/run_pluginval.sh` | github.com/Tracktion/pluginval/releases |
| Catch2, nlohmann/json, PFFFT, dr_wav latest tags | `cmake/SpatialDependencies.cmake` | GitHub releases/tags of each |
| GitHub Actions major versions | `.github/workflows/*.yml` | each action's releases page |
| Python package versions and wheel availability (pyroomacoustics, numpy, scipy) | `tools/acoustics/requirements.txt` | PyPI |
| HRTF dataset licence (SADIE II, MIT KEMAR) | Phase 08, `resources/hrtf/LICENSE-*.txt` | the dataset's official page, read the licence text |
| BRAS dataset location, licence and manifest checksums | Phase 05, `tools/validation/bras_manifest.json` | DepositOnce record |
| ITU-R BS.1770 current revision | Phase 09 tests | itu.int |

## How the reviewer uses this map

1. Read `process-rules.md` for every PR.
2. Read the phase's section in `phase-checklists.md`.
3. From the "Domains" table, open only the reference files whose phases match. Each reference file
   ends with a checklist of questions; apply the ones the diff touches.
4. When a fact in a reference file looks outdated or is marked "(unverified)", verify it live
   before citing it in a review, and fix the reference file in the same PR if the skill is editable.
