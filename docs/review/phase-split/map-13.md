# Split map — Phase 13 (v1 hardening: performance, DAW matrix, signing)

Source: `docs/phases/phase-13.md` (as of main 8583ba1). Drafted under `0-drafting-brief.md` and the session brief
`docs/sessions/2026-11-10-phase-split.md` (G1–G4). Pure reallocation: no threshold, number, AX/AQ value, criterion
wording or decision is changed. Item labels used below: **H** header (size, depends, read first), **R1–R4** Raise
items (**R0** the Raise preamble), **G** goal, **A** assumptions in force, **S1–S13** scope items (S3 bullets
S3.1–S3.6, S4 bullets S4.1–S4.3), **O** out of scope, **C1–C5** automated criteria (in file order), **L1–L5**
listening/manual items, **F1–F4** contractor review focus clauses, **K1–K3** risks, **D1–D4** definition-of-done
clauses.

## 1. Sub-phase table

| id | title | lead subject matter (seat — convening-table row words) | size | depends on | ships | automated criteria owned |
|---|---|---|---|---|---|---|
| 13-1 | Performance, memory and diffuse limits to AQ10 | Seat 2 Engine architect — "simulator compute and recompute time"; "the representation handed to the renderer" (S10's IR cap). Hand-offs: per-instance CPU and SIMD in the accumulation loops (3), audibility of the cut (S10 Q1/Q2, 1) | L (remainder `13-1b`, see §2) | H in full (00–12, 05b, 05h, 07c or S13's versioning fallback recorded, 05d, 05e, 05f, 05c clause) | `docs/perf/v1.md` (profiles on macOS arm64 and Windows x64, memory per instance on 3 OSes, the memory-budget decision); output-preserving optimisations; AQ10 benchmark result or quantified miss with proposal; AX22 i₀ re-derived; W_max / n\*_max re-checked on the release machines; the S10 end-treatment answer (Q1–Q3) and choice | C2 (all clauses: "Benchmarks: AQ10 met … Re-derive the AX22 i₀ after optimisation if AX22 records 'cap limits accuracy'.") |
| 13-2 | Platforms: universal macOS binary, cross-architecture determinism, ARM64 flush-to-zero, Apple-silicon callback timing | Seat 5 Deadline keeper — "platform transitions"; "worst-case callback time"; "CI gates" | M | 13-1; H in full | universal binary (arm64 + x86_64) with both slices tested in CI (Rosetta); cross-architecture residual job; MSVC ARM64 FTZ guard with an ARM64 Windows runner; S9 measurement on Apple-silicon hardware | C3 clause "including cross-architecture ≤ −100 dBFS residual", stated alone as: "Robustness test: cross-architecture ≤ −100 dBFS residual." |
| 13-3 | Host robustness and conformance | Seat 5 Deadline keeper — "host conformance (pluginval, auval, state, automation, undo, buses, latency)"; "anything on or beside the audio thread"; "CI gates" | M | 13-2 (both macOS slices for C4); H in full. S12 may be pulled forward on its own (as S12 already allows) | Catch2/pluginval robustness suite (S3.1–S3.5), multi-instance CPU and RSS records incl. Bitwig's sandbox; the AX34 resampling decision (and implementation if chosen); pluginval release cached in CI; pluginval 10 + auval on the release build | C3 clause "Robustness tests above pass" (S3.1–S3.5); C4 ("pluginval strictness 10 on the **release** build, 3 OSes (both macOS slices). auval passes.") |
| 13-4 | Release packaging, licences, identity and the beta decision | Seat 5 Deadline keeper — "CI gates"; "framework and plugin-format choice" (release workflow, signing, installers). Hand-offs: JUCE tier, signing cost, AX8 identity, public compatibility wording (7) | M (remainder `13-4b` if notarization fights back) | 13-1, 13-2, 13-3; H in full | `release.yml` (signed/notarized/stapled pkg or `signing pending secrets`, Inno Setup installer, version from tag shown in UI); complete `docs/THIRD_PARTY.md` and `THIRD_PARTY_NOTICES.txt`; JUCE tier in §6; AX8 confirmed; `docs/compat/v1.md`; Maisara's install checks, final listening pass and the v1 beta decision in §6 | C5 |

C1 ("Full CI matrix green; nightly validation green (no regression).") is **umbrella, shared**: every sub-phase
owns it for its own PR.

## 2. Order and rationale

Order **13-1 → 13-2 → 13-3 → 13-4**.

- 13-1 first: it is the only sub-phase that may change code in `src/sim/` hot paths and, through S13 and S10, the
  shipped output (golden round, §6 row). Everything measured later (cross-architecture residual, pluginval on the
  release build, 10-instance CPU, installers) should run on the final, optimised code. The phase-13 review traps
  name the reason: "an optimization that changes summation order and silently breaks AX5 determinism".
- 13-2 after 13-1: the cross-architecture residual (AX5) and the Apple-silicon S9 measurement are only meaningful
  on post-optimisation code; the universal binary must exist before 13-3 can run pluginval on both macOS slices.
- 13-3 after 13-2: C4 requires "both macOS slices". S12 (pluginval cache) is independent and may go first on its
  own, as the original file already says.
- 13-4 last: the installer packages both slices, the beta decision lists every recorded deficit (AQ10 misses from
  13-1, robustness results from 13-3), and the compat matrix note on Bitwig depends on 13-3's measurement.
- The two-session remainder: the size line's "split into 13b" becomes per sub-phase — the optimisation branch
  (S1 "non-uniform partitioning (if needed, make it 13b)", S9's "13b, per scope 1", the size line's "optimization
  fights back") is `13-1b`; the size line's "notarization fights back" is `13-4b`.
- Dependencies: the header's full dependency list (H) is carried to every sub-phase unchanged; no sub-phase is
  allowed to start earlier than the original phase could. (No dependency is moved.)

Elements the session brief may count as decisions:

- **CHOICE 13-c1 (order; which risk is retired first; S9's placement).** Options: (a) S9 in 13-2, order
  13-1 → 13-2 (the real-hardware timing is measured on the optimised code; a miss reopens the optimisation as
  `13-1b`); (b) S9 in 13-1 (measurement and its remedy in one session, but 13-1 then leads two seats' subjects);
  (c) 13-2 before 13-1 (retires the platform/notarization-adjacent risks first, but the AX5 residual and S9 would
  have to be re-run after optimisation). Recommended (a): S9's remedy is a scope 1 optimisation, but its pass
  condition (p99.9 < 100 % on real Apple silicon) is a platform measurement under Seat 5's "worst-case callback
  time", and measuring once on final code avoids a re-run.
- **CHOICE 13-c2 (G2: S10 end treatment and S11 AX34 own no automated criterion).** Options: (a) merge S10 into
  13-1 (its Q3 is CPU and memory of a longer cap; the cap is part of the response representation) and S11 into
  13-3 (AX34's fallback exists because hosts cannot refuse a rate and auval renders at 11.025/22.05/192 kHz, which
  is C4's auval clause); (b) a separate sub-phase "tail end and rate fallback" (lead Seat 1 or 3) owning only C1's
  "nightly validation green (no regression)" clause. Recommended (a): (b) would own a clause every `src/sim/`
  change already owns, which G2 does not count as value of its own.
- **CHOICE 13-c3 (size across the two-session limit).** Phase 13 was M (L with one 13b); the split totals about
  L + 3 M (≈ 5 sessions). Options: (a) the four sub-phases above; (b) keep phase 13 whole with 13b. Recommended
  (a): the original items span four seats' subject matters (Seat 2 rebuild/diffuse, Seat 5 platforms, Seat 5 host
  conformance, Seat 5/7 release and licences), which one session cannot keep in focus; no scope is added, so the
  extra sessions are the original work's true size made explicit.
- **CHOICE 13-c4 (Raise items: first message vs. before the beta decision).** The original preamble R0 ("raises
  each item in its first message and again before the beta decision") is split: each item is raised in the first
  message of the sub-phase that holds its subject (below); the "again before the beta decision" clause goes to
  13-4 for all four. Options: (a) as stated; (b) all four raised in 13-1's first message (the phase's first
  session) and again in 13-4. Recommended (a) for R3/R4 (their subject is in 13-1, so (a) and (b) coincide) and
  (a) for R1/R2 (they concern the beta wording and decision, which only 13-4 makes); the decider rules whether
  R1/R2 must also appear in 13-1's first message.

## 3. Coverage table

| original item | → sub-phase | note |
|---|---|---|
| H size line "M (L if notarization or optimization fights back; split into 13b)" | umbrella (shared) | per sub-phase: optimisation → 13-1 (L, `13-1b`); notarization → 13-4 (`13-4b`); naming per G3 |
| H depends on (00–12, 05b, 05h, 07c or S13 fallback, 05d, 05e, 05f, 05c clause) | umbrella (shared) | carried unchanged to every sub-phase |
| H read first (`CLAUDE.md`, BUILD_PLAN §2–§3, NFR-2, NFR-4, NFR-6) | umbrella (shared) | each sub-phase reads all of it |
| R0 preamble: "raises each item in its first message" | per item below | |
| R0 preamble: "and again before the beta decision" | 13-4 | for all four items |
| R1 Commissioning decision (F2) | 13-4 | first message; re-put "before the beta decision" |
| R2 DELTA panel report | 13-4 | first message; Arni label in the beta wording |
| R3 Load time with 8 instances (AX38 (iv)) | 13-1 | first message; "before the first release" (13-1 precedes 13-4) |
| R4 Phase 07c not landed (conditional) | 13-1 | first message; tied to S13's versioning fallback |
| G Goal (private-beta build …; licensing not in v1) | umbrella (shared) | each sub-phase states its share |
| A AQ10 budget | umbrella (shared) + 13-1 | 13-1 measures it; 13-3 records multi-instance CPU against it |
| A AX5 "exactly as saved" | umbrella (shared) + 13-2 | 13-2 owns the cross-architecture residual |
| S1 Profiling and optimization (incl. allowed/not-allowed optimisations, Phase 06/07 measured inputs, memory per instance on 3 OSes and the memory-budget decision, AX38 inputs) | 13-1 | non-uniform partitioning → `13-1b` |
| S2 macOS universal binary, both slices tested in CI | 13-2 | |
| S3 preamble "Robustness tests (Catch2 + pluginval options)" | 13-3 | |
| S3.1 10 instances, CPU sum; multi-instance RSS on 3 OSes incl. Bitwig sandbox | 13-3 | |
| S3.2 Sample-rate change (44.1 ↔ 96 kHz), buffer-size change | 13-3 | |
| S3.3 0-/1-sample buffers, 60 s silence (denormals off) | 13-3 | |
| S3.4 Bypass keeps latency, delayed dry | 13-3 | |
| S3.5 Load every state fixture 07–12 | 13-3 | |
| S3.6 Cross-architecture determinism (AX5) ≤ −100 dBFS, final CI job | 13-2 | |
| S4 preamble release workflow on tags `v*` | 13-4 | |
| S4.1 macOS codesign, pkg, notarize, staple; secrets; skip message | 13-4 | |
| S4.2 Windows Inno Setup; optional signing; SmartScreen note | 13-4 | |
| S4.3 Version from tag, embedded and shown in UI | 13-4 | |
| S5 Licences and attribution; notices file; JUCE tier in §6 | 13-4 | |
| S6 DAW compatibility matrix `docs/compat/v1.md`; Bitwig gap in public notes until S3 measured | 13-4 | uses 13-3's S3.1 result |
| S7 AX8 placeholder identity confirmed before first beta | 13-4 | |
| S8 MSVC ARM64 flush-to-zero guard + ARM64 Windows runner | 13-2 | |
| S9 Small-buffer callback timing on real macOS hardware | 13-2 | CHOICE 13-c1; remedy (if missed) → `13-1b` per S1 |
| S10 End treatment at the 12 s cap (Q1–Q3, then choose) | 13-1 | CHOICE 13-c2 |
| S11 AX34 internal resampling decision | 13-3 | CHOICE 13-c2 |
| S12 Cache the pinned pluginval release in CI | 13-3 | may still be pulled forward standalone |
| S13 Diffuse-estimator work limits and the restore (AX41; W_max, n\*_max; 07c prerequisite or versioning fallback) | 13-1 | |
| O Out of scope (B1, auto-update, §5) | umbrella (shared) | applies to all |
| C1 Full CI matrix green; nightly validation green (no regression) | umbrella (shared) | each sub-phase for its own PR |
| C2 Benchmarks: AQ10 … AX22 i₀ | 13-1 | whole criterion |
| C3 clause "Robustness tests above pass" | 13-3 | covers S3.1–S3.5 |
| C3 clause "including cross-architecture ≤ −100 dBFS residual" | 13-2 | |
| C4 pluginval strictness 10, release build, 3 OSes (both slices); auval | 13-3 | depends on 13-2 |
| C5 Release workflow on a test tag (pkg accepted by `spctl`, Windows installer, notices; else `signing pending secrets`) | 13-4 | |
| L1 Install from macOS pkg; Logic finds AU | 13-4 | |
| L2 Install on Windows; DAW finds VST3 | 13-4 | |
| L3 Fill in `docs/compat/v1.md` | 13-4 | |
| L4 Final listening pass, all presets, both modes; 10 instances on stems | 13-4 | |
| L5 Beta decision (AQ9 x/y, known deficits, F2 sentence, decider report 16 correction; §6) | 13-4 | |
| F1 Optimization diffs (no acoustic changes beyond −100 dB) | 13-1 | |
| F2 Threading under multi-instance load | 13-3 | |
| F3 Release pipeline's secret handling | 13-4 | |
| F4 Licence compliance | 13-4 | |
| K1 Apple developer account and notarization logistics | 13-4 | |
| K2 JUCE licence tier cost at launch | 13-4 | |
| K3 Windows signing cost | 13-4 | |
| D1 All automated criteria green (or signing explicitly pending secrets) | umbrella (shared) | each sub-phase its own criteria; signing clause 13-4 |
| D2 Compat matrix filled in | 13-4 | |
| D3 Status row 13 `done` | umbrella | set when 13-1…13-4 are `done` (G3) |
| D4 The v1 beta decision is recorded | 13-4 | |
| Settled / "decisions before implementation" section | — | phase-13 has none; the in-phase decisions (memory budget S1, end treatment S10, AX34 S11) stay with 13-1, 13-1, 13-3 |

## 4. References (repo grep, `docs/corpus`, `docs/review`, `docs/sessions` excluded)

| file:line | reference | → new sub-phase |
|---|---|---|
| `docs/BUILD_PLAN.md:29` | §0 row 06: "handed off to phase-13 scope item 9 (real hardware)"; "non-uniform partitioning planned for Phase 13" | 13-2 (item 9); 13-1 / `13-1b` (non-uniform partitioning) |
| `docs/BUILD_PLAN.md:30` | §0 row 06b: "phase-13 item 9 remedy no longer P = 256" | 13-2 (remedy in 13-1 / `13-1b`) |
| `docs/BUILD_PLAN.md:32` | §0 row 07c: "before Phase 13's beta, or phase-13 scope 13's versioning fallback recorded" | 13-1 (S13 fallback); beta → 13-4; dependency umbrella (all) |
| `docs/BUILD_PLAN.md:38` | §0 row 13 | umbrella row `split (13-1…13-4)` + rows 13-1…13-4 |
| `docs/BUILD_PLAN.md:50` | §1 JUCE: "Check the current JUCE licence tiers … (Phase 13 checklist)" | 13-4 |
| `docs/BUILD_PLAN.md:95` | AQ10: "non-uniform partitioning, phase-13 scope 1 (13b)"; "macOS arm64 and Windows x64 recorded in Phase 13"; "not optimised before Phase 13"; "re-checked in phase-13" (W_max, n\*_max) | 13-1 (`13-1b` for "(13b)") |
| `docs/BUILD_PLAN.md:108` | AX8: "Must be confirmed before the first beta (Phase 13)"; phases "00, 13" | 13-4 |
| `docs/BUILD_PLAN.md:122` | AX22: "Phase 13 then re-derives i₀ after optimisation" (twice) | 13-1 |
| `docs/BUILD_PLAN.md:134` | AX34: "No resampling in v1 (Phase 13 decides)" | 13-3 |
| `docs/BUILD_PLAN.md:138` | AX38: "phase-13 scope 1 owns the memory budget"; "recorded on macOS and Windows until Phase 13"; "no memory budget (phase-13 scope 1)"; "Reversal: Phase 13 RSS" | 13-1 |
| `docs/BUILD_PLAN.md:138` | AX38 (i): "Bitwig's per-plugin sandbox … stated in the public compatibility notes until Phase 13 measures it" | 13-3 (measurement S3.1); public notes 13-4 (S6) |
| `docs/BUILD_PLAN.md:141` | AX41: "phase-13 re-checks them on the release machines" | 13-1 |
| `docs/BUILD_PLAN.md:155` | §3 F2: second dataset "required before the Phase 13 beta decision" | 13-4 |
| `docs/BUILD_PLAN.md:293` | §4 Phase 07c: "Before Phase 13's beta" | 13-4 (beta); dependency umbrella |
| `docs/BUILD_PLAN.md:343`–`351` | §4 Phase 13 summary (goal, scope, deps, acceptance, from 05b, risks) | umbrella; clauses map as in §3 above |
| `docs/BUILD_PLAN.md:371` | "User-audible fact for Phase 13's beta list" | 13-4 |
| `docs/BUILD_PLAN.md:402`–`447` | §6 change-log rows naming phase-13 (scope 1, items 9–13, beta decision, Raise item 4, deps) | historical rows, not rewritten; their items map as in §3 |
| `docs/THIRD_PARTY.md:11` | JUCE "licence tier and revenue cap … (Phase 13)" | 13-4 |
| `docs/THIRD_PARTY.md:12`, `:13` | notices "before release (Phase 13)" | 13-4 |
| `docs/phases/phase-00.md:26` | splash screen "(licence check happens in Phase 13)" | 13-4 |
| `docs/phases/phase-05.md:155` | "Phase 13 may start with 05c blocked only on Maisara's recorded decision" | umbrella dependency (all) |
| `docs/phases/phase-05.md:585` | "Phase 13's beta decision lists 'AQ9 met in x/y' …" | 13-4 |
| `docs/phases/phase-05.md:620` | second dataset "before the Phase 13 beta decision" | 13-4 |
| `docs/phases/phase-05b2.md:234`, `:236` | memory budget deferred "to Phase 13 (scope 1)"; "cross-referenced to Phase 13" | 13-1 |
| `docs/phases/phase-05b2.md:409`, `:411` | "phase-13 scope 13" (historical note, now phase-07c) | 13-1 (S13 remainder) |
| `docs/phases/phase-05d.md:7` | "Phase 13 depends on 05d being `done` or `blocked (reason)`" | umbrella dependency (all) |
| `docs/phases/phase-05d.md:41` | F2 deferred: "Phase 13 raises it again" | 13-4 (R1) |
| `docs/phases/phase-05d.md:356` | "Phase 13 may start" | umbrella dependency (all) |
| `docs/phases/phase-05h.md:95` | AX38 (iv) load time "(also phase-13 'Raise with Maisara' item 3)" | 13-1 (R3) |
| `docs/phases/phase-06b.md:35` | non-uniform partitioning "`docs/phases/phase-13.md` scope 1" | 13-1 (`13-1b`) |
| `docs/phases/phase-06b.md:52` | "`phase-13.md` scope 1 and item 9" | 13-1 (scope 1); 13-2 (item 9) |
| `docs/phases/phase-06b.md:145` | non-uniform partitioning: phase-13 scope 1 | 13-1 (`13-1b`) |
| `docs/phases/phase-06b.md:146` | MSVC/ARM64 FTZ: phase-13 scope item 8 | 13-2 |
| `docs/phases/phase-06b.md:147` | real-hardware macOS timing: phase-13 scope item 9 | 13-2 |
| `docs/phases/phase-07c.md:4`–`5` | "Must be `done` before Phase 13's beta (or phase-13 scope 13's versioning fallback recorded)" | 13-1 (S13 fallback); beta 13-4; dependency umbrella |
| `docs/phases/phase-07c.md:41` | "phase-13 'Raise with Maisara' item 4" | 13-1 (R4) |
| `docs/phases/phase-07c.md:45` | "the Phase 13 beta" | 13-4 |
| `docs/phases/phase-07c.md:151` | "§0 row 07c `done` before Phase 13's beta" | 13-4 |
| `docs/phases/phase-08.md:178` | "the Phase 13 final listening pass through all presets" | 13-4 (L4) |
| `docs/phases/phase-10.md:130` | "phase-13 scope 1 optimisations" | 13-1 |
| `src/plugin/CMakeLists.txt:39` | splash screen "(licence check in Phase 13)" | 13-4 (code comment; not edited in this session) |
| `.claude/skills/review-phase-pr/references/phase-checklists.md:348`–`362` | review checklist "Phase 13" (perf notes, universal binary, robustness, release.yml, THIRD_PARTY, compat skeleton, AX8; traps) | umbrella; per clause: perf/−100 dB null/fast-math trap → 13-1; universal binary, both slices, cross-arch, summation-order trap → 13-2; robustness, pluginval release → 13-3; release.yml, notices, JUCE tier, compat skeleton, AX8, secrets/splash/identity traps → 13-4 |
| `.claude/skills/review-phase-pr/references/knowledge-inventory.md:44` | JUCE splash-screen note, "Phase 13" | 13-4 |
