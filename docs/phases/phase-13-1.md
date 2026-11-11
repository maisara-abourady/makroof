# Phase 13-1 — Performance and per-instance CPU

Size: **L** (remainder, if needed: `13-1b`) · Depends on: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) (phase-13 header, in full) · Part of: [phase-13](phase-13.md) · Lead subject matter: Seat 3 (Reverb renderer), "per-instance CPU" · Read first: [`phase-13.md`](phase-13.md) (umbrella), `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again before the beta decision. (phase-13 R0; in this
split the first message is 13-1's and "again before the beta decision" is 13-5's, which carries the same five items:
D-PS4 instruction 5.)

1. **Commissioning decision (BUILD_PLAN §3 F2).** Check BUILD_PLAN §6 for Maisara's answer, recorded by
   phase 05d. If it is missing or "deferred", put the question to her again with the Phase 05/05d
   numbers before the beta decision. (phase-13 R1)
2. **DELTA panel report.** Check whether `docs/phases/phase-05d.md`'s PR recorded an answer. If not,
   remind her that the request (`docs/review/drafts/delta-report-request.md`) is still outstanding, and
   keep the Arni provenance label as is in the beta wording. (phase-13 R2)
3. **Load time with 8 instances (AX38 (iv), phase 05b).** If the recorded time until the last of 8
   instances is audible at project load at 100 m exceeds 10 s, it goes to Maisara before the first
   release. (phase-13 R3)
4. **Phase 07c not landed (conditional).** If the asynchronous diffuse solve (phase-07c) would land after
   the first release without the estimator parameters versioned in saved state, Seat 7's condition fails
   and the item returns to Maisara (decider file 47 §4, strongest objection). (phase-13 R4)
5. **Release machines for the AX38 4c strict re-check (RG-1).** Release machines bought once, no standing
   runner (Seat 7, file 60 round 1: larger hosted runners ≈ €100–130/month, a standing cost before any
   revenue, and the macOS larger runner still a shared VM; decider files 64 item 7 and 66 §7: a person's
   purchase); on them the strict 30 s and the 1.10 growth bound are asserted on all three OSes (AX41) and the
   register entries close or the absolute CHECK returns on named hardware. (phase-13 R5, added 2026-11-11 by DECISION RG-1)

## Goal

This sub-phase's share of the umbrella goal ("Turn the vertical slice into a **private-beta build**"): meet the
performance budget, per instance (CPU and memory), on the optimised code that every later sub-phase measures.

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.
  (phase-13 assumptions, shared)

## Scope

1. **Profiling and optimization** against AQ10 on macOS arm64 and Windows x64 (profile with Instruments /
   VTune or Superluminal; record findings in `docs/perf/v1.md`). Allowed optimizations: SIMD in
   accumulation loops, image-source grouping parameters, tail-cache hit rate, partition size choice. Not
   allowed without a new AX entry: anything that changes the acoustic output beyond −100 dB, and
   non-uniform partitioning (if needed, make it 13b). Measured motivation (Phase 06, PR #14, CI run
   42355829013; 2×2, 48 kHz, host buffer 512, mean % of the real-time budget, steady / crossfading):
   12 s IR at P = 512: macOS 7.3 / 14.0, Linux 11.7 / 26.0, Windows 9.1 / 26.2; 12 s IR at P = 256: up
   to 59 % while crossfading (Linux/Windows). AQ10 budgets only a 3 s IR (P = 512: 1.6–2.1 % steady,
   3.3–4.1 % crossfading), so no current criterion needs it; Maisara chose to plan it, not build it
   (2026-11-07). Further inputs (Phase 07 follow-up, PR #23, CI run 42465826545, release build, best of
   3): full rebuild (scene → `buildRoomIR` → `IrSet`, tail noise generation included), default / maximum
   room (100 × 100 × 100 m), at 48 kHz: Linux 183.6 / 752.1 ms, macOS 132.7 / 801.9 ms, Windows
   141.8 / 603.0 ms; at 96 kHz: Linux 392.4 / 1883.7 ms, macOS 278.6 / 1832.1 ms, Windows
   295.2 / 1509.1 ms. RSS per instance at 96 kHz, maximum room: +122.6 MB (Linux only; the pipeline
   keeps the last built and the last submitted `RoomIR`/`IrSet`). Measure memory per instance on all
   three OSes and report it in `docs/perf/v1.md`; any memory budget is a decision for this phase (no
   number is set here). Phase-07c-1 condition 12 (f) records the process transient peak with 4 and 8
   concurrent builds at 100 m, 48 and 96 kHz once the gate is narrowed; a breach of the budget is remedied by
   a limit on concurrently running builds sized from that record, never an instance cap (PRD FR-3D-5,
   FR-3D-6, FR-SIM-7, A5), a W_max cut or a range change (D-H1 (v)(d)) (D-G1,
   `docs/review/phase-05i/13-decider-DG1.md`). Input since phase 05b: AX38's working ceiling for the diffuse computation (≤ 1 GB
   transient per solve, one solve per process; ≤ 128 MB additional resident per instance) and its records.
   (phase-13 scope 1; "13b" is `13-1b` in this split)
2. **End treatment at the 12 s cap** (Phase 07 D3). Answer first: (Q1) audibility threshold of a
   rectangular cut at a given remaining decay depth, per band, for music; (Q2) fade length that removes
   cut artefacts without shortening the perceived decay; (Q3) CPU and memory of a 20–30 s cap at
   96 kHz. Then choose: keep the cut; an end fade (new AX, goldens via update_goldens.py, §6 row); or a
   longer cap. (phase-13 scope 10; Q1/Q2 handed to Seat 1, D-PS4 Q1)

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5. (phase-13 out of scope, shared)
Every item the umbrella's table assigns to 13-2 … 13-5; non-uniform partitioning, if needed, is `13-1b`.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression). (phase-13 C1, umbrella shared: for this
      sub-phase's PR)
- [ ] Benchmarks: AQ10 met on the macOS runner and Windows runner, or the miss is quantified in the status
      notes, with the effective update interval max(30 ms, rebuild) and the worst staleness, together
      with a proposal that does not change the output beyond −100 dB. (phase-13 C2, sentence 1; sentences 2
      and 3 in 13-2)

## Listening / manual checklist (Maisara)

None. (All of phase-13's listening and manual items are in 13-5.)

## Contractor review focus

Optimization diffs (no acoustic changes beyond −100 dB) (phase-13 contractor review focus, clause 1; the other
clauses in 13-4 and 13-5).

## Risks

Apple developer account and notarization logistics; JUCE licence tier cost at launch; Windows signing cost.
(phase-13 K1–K3, umbrella shared; read by 13-1: D-PS4 instruction 4)

## Notes from the split

- Remainder (G3): `13-1b` (optimisation, non-uniform partitioning, S9 remedy). (D-PS4 Q1)
- 13-3 runs S9 first, before C3's residual and S8 are recorded. A miss opens `13-1b`; 13-3's records are taken after
  `13-1b` lands. (D-PS4 instruction 2; S9 = phase-13 scope 9, in 13-3)
- If `13-1b` changes rebuild time or diffuse-solve time, 13-2's i₀ sentence, its N_cap rule and S13's W_max / n*_max
  re-check re-run before 13-3's records are taken. (D-PS4 instruction 3, final wording, Addendum)
- K1, K2, K3 "umbrella (shared)", read by 13-1; risk text verbatim. (D-PS4 instruction 4) The lead time decides when
  Maisara starts enrolment (a person's action), a follow-up for 13-1's session. (`3-decider-decision.md`, K1–K3
  paragraph)
- Raise items: all four carried by 13-1 (first message) and by 13-5 ("before the beta decision"). (Five since R5, 2026-11-11.) (D-PS4 instruction
  5; final corrections list item 3)
- S10 in 13-1 (13-c2, NOT A DECISION, resolution (a): convening round).

## Definition of done

All automated criteria green (phase-13 definition of done, clause 1, shared: this sub-phase's criteria); status
row 13-1 `done` (CLAUDE.md rule 6; status row 13 stays on the umbrella). CLAUDE.md rules apply: one sub-phase per
session; if it can't be finished in two sessions, split the remainder into `phase-13-1b.md`.
