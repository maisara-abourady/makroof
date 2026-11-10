# Phase 13 — v1 hardening: performance, DAW matrix, signing

Size: **split into 13-1…13-5** · Depends on: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

Status: the umbrella is `done` when every sub-phase is. A dependency on phase 13 means all of its sub-phases unless
a sub-phase is named.

## Raise with Maisara (she does not track these herself)

The four items (phase-13 R0–R4) are carried verbatim by [13-1](phase-13-1.md) (first message) and
[13-5](phase-13-5.md) ("before the beta decision") (D-PS4 instruction 5).

## Goal

Turn the vertical slice into a **private-beta build**: meet the performance budget, survive real-world
host behaviour, install cleanly on macOS and Windows, and get every licence in order. (Licensing and
subscriptions are deliberately not in v1; see BUILD_PLAN F9 and B1.)

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.

## Sub-phases

Order 13-1 → 13-2 → 13-3 → 13-4 → 13-5; each carries the header's dependency line in full; C1 is shared via the
umbrella (D-PS4 Q1).

| id | title | lead seat | size | depends on | ships | owns |
|---|---|---|---|---|---|---|
| [13-1](phase-13-1.md) | Performance and per-instance CPU | Seat 3, "per-instance CPU" | L (`13-1b`) | header | `docs/perf/v1.md` (profiles on macOS arm64 and Windows x64, memory per instance on 3 OSes, the memory-budget decision); output-preserving optimisations; AQ10 benchmark result or quantified miss with proposal; the end-treatment answer (Q1–Q3) and choice | C1 (shared); C2 sentence 1 |
| [13-2](phase-13-2.md) | Engine limits after optimisation | Seat 2, "simulator compute and recompute time" | M | 13-1; header | W_max / n\*_max re-checked on the release machines; AX22 i₀ re-derived; any N_cap raise proposed through /fix-plan | C1 (shared); C2 sentences 2 and 3 |
| [13-3](phase-13-3.md) | Platforms | Seat 5, "platform transitions"; "worst-case callback time"; "CI gates" | M | 13-2; header | real-hardware callback timing on Apple silicon (first); universal binary with both slices tested in CI; cross-architecture residual job; MSVC ARM64 flush-to-zero guard with an ARM64 Windows runner | C1 (shared); C3 cross-architecture clause |
| [13-4](phase-13-4.md) | Host robustness and conformance | Seat 5, "host conformance (pluginval, auval, state, automation, undo, buses, latency)"; "anything on or beside the audio thread" | M | 13-3; header | robustness suite (multi-instance CPU and RSS incl. Bitwig's sandbox, rate/buffer changes, 0/1-sample buffers, bypass, state fixtures); the AX34 decision; pluginval release cached in CI; pluginval 10 and auval on the release build | C1 (shared); C3 "Robustness tests above pass"; C4 |
| [13-5](phase-13-5.md) | Release, licences, identity, beta | Seat 5, "CI gates"; "framework and plugin-format choice" | M (`13-5b`) | 13-1 to 13-4; header | `release.yml` (signed/notarized/stapled pkg or `signing pending secrets`, Windows installer, version from tag); complete `docs/THIRD_PARTY.md` and `THIRD_PARTY_NOTICES.txt`; JUCE tier in §6; AX8 confirmed; `docs/compat/v1.md`; the v1 beta decision in §6 | C1 (shared); C5 |

## Where the original items went

Labels: **H** header, **R0–R4** Raise preamble and items, **G** goal, **A** assumptions, **S1–S13** scope items
(S3 bullets S3.1–S3.6, S4 bullets S4.1–S4.3), **O** out of scope, **C1–C5** automated criteria in file order,
**L1–L5** listening/manual items, **F1–F4** contractor review focus clauses, **K1–K3** risks, **D1–D4**
definition-of-done clauses. "phase-13 scope n" = Sn.

| original item | → sub-phase | note |
|---|---|---|
| H size line "M (L if notarization or optimization fights back; split into 13b)" | umbrella (shared) | per sub-phase: optimisation → 13-1 (L, `13-1b`); notarization → 13-5 (`13-5b`); "13b" in the original text means `13-1b` |
| H depends on | umbrella (shared) | carried unchanged to every sub-phase |
| H read first | umbrella (shared) | each sub-phase reads all of it |
| R0 preamble | 13-1 and 13-5 | first message: 13-1; "again before the beta decision": 13-5 |
| R1 Commissioning decision (F2) | 13-1 and 13-5 | D-PS4 instruction 5 |
| R2 DELTA panel report | 13-1 and 13-5 | D-PS4 instruction 5 |
| R3 Load time with 8 instances (AX38 (iv)) | 13-1 and 13-5 | D-PS4 instruction 5 |
| R4 Phase 07c not landed (conditional) | 13-1 and 13-5 | D-PS4 instruction 5 |
| G Goal | umbrella (shared) | each sub-phase states its share |
| A AQ10, AX5 | umbrella (shared) | carried to every sub-phase |
| S1 Profiling and optimization (incl. memory per instance and the memory-budget decision) | 13-1 (scope 1) | non-uniform partitioning → `13-1b` |
| S2 macOS universal binary | 13-3 (scope 1) | |
| S3 preamble "Robustness tests (Catch2 + pluginval options)" | 13-4 (scope 1) | |
| S3.1–S3.5 (10 instances and RSS; rate/buffer change; 0/1-sample buffers and silence; bypass; state fixtures) | 13-4 (scope 1) | |
| S3.6 Cross-architecture determinism (AX5) | 13-3 (scope 2) | |
| S4 Release packaging, S4.1–S4.3 | 13-5 (scope 1) | |
| S5 Licences and attribution | 13-5 (scope 2) | |
| S6 DAW compatibility matrix | 13-5 (scope 3) | uses 13-4's S3.1 result |
| S7 AX8 placeholder identity | 13-5 (scope 4) | |
| S8 MSVC ARM64 flush-to-zero guard | 13-3 (scope 3) | |
| S9 Small-buffer callback timing on real macOS hardware | 13-3 (scope 4) | runs first in 13-3; a miss opens `13-1b` (D-PS4 instruction 2) |
| S10 End treatment at the 12 s cap | 13-1 (scope 2) | Q1/Q2 handed to Seat 1 |
| S11 AX34 internal resampling decision | 13-4 (scope 2) | |
| S12 Cache the pinned pluginval release in CI | 13-4 (scope 3) | may still be pulled forward standalone |
| S13 Diffuse-estimator work limits and the restore (AX41) | 13-2 (scope 1) | |
| O Out of scope | umbrella (shared) | carried to every sub-phase |
| C1 Full CI matrix green; nightly validation green | umbrella (shared) | every sub-phase for its own PR |
| C2 sentence 1 "Benchmarks: AQ10 met … beyond −100 dB." | 13-1 | |
| C2 sentence 2 (N_cap) and sentence 3 (AX22 i₀) | 13-2 | |
| C3 clause "Robustness tests above pass" | 13-4 | covers S3.1–S3.5 |
| C3 clause "including cross-architecture ≤ −100 dBFS residual" | 13-3 | stated as "Robustness test: cross-architecture ≤ −100 dBFS residual." |
| C4 pluginval strictness 10, release build; auval | 13-4 | needs 13-3's both slices |
| C5 Release workflow on a test tag | 13-5 | |
| L1–L5 | 13-5 | |
| F1 Optimization diffs | 13-1 | |
| F2 Threading under multi-instance load | 13-4 | |
| F3 Release pipeline's secret handling, F4 Licence compliance | 13-5 | |
| K1–K3 | umbrella (shared), read by 13-1 | D-PS4 instruction 4 |
| D1 All automated criteria green (or signing explicitly pending secrets) | umbrella (shared) | each sub-phase its own criteria; signing clause 13-5 |
| D2 Compat matrix filled in, D4 v1 beta decision recorded | 13-5 | |
| D3 Status row 13 `done` | umbrella | set when 13-1…13-5 are `done` |

## Notes from the split (D-PS4, `docs/review/phase-split/5-decider-decision-r2.md`, with its Addendum)

1. The five sub-phases and order as in Q1. (instruction 1)
2. 13-3 runs S9 first, before C3's residual and S8 are recorded. A miss opens `13-1b`; 13-3's records are taken after
   `13-1b` lands. (instruction 2)
3. If `13-1b` changes rebuild time or diffuse-solve time, 13-2's i₀ sentence, its N_cap rule and S13's W_max / n*_max
   re-check re-run before 13-3's records are taken. (instruction 3, final)
4. K1, K2, K3 "umbrella (shared)", read by 13-1; risk text verbatim. (instruction 4)
5. Raise items: all four carried by 13-1 (first message) and by 13-5 ("before the beta decision"). (instruction 5)
6. S13's 'release machines', in 13-2, and S9, in 13-3, need Apple-silicon hardware; Maisara provides it (follow-up).
   (instruction 6, final)
7. Remainders (G3): `13-1b` (optimisation, non-uniform partitioning, S9 remedy); `13-5b` (notarization). (Q1)

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5.

## Acceptance criteria — automated (shared)

- [ ] Full CI matrix green; nightly validation green (no regression).

Every other criterion is owned by a sub-phase (table above).

## Risks

Apple developer account and notarization logistics; JUCE licence tier cost at launch; Windows signing cost.

## Definition of done

All automated criteria green (or signing explicitly pending secrets); status row
13 `done`. (The compat matrix and the v1 beta decision are 13-5's.)
