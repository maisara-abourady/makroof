# Phase 13-4 — Host robustness and conformance

Size: **M** (remainder, if needed: `13-4b`) · Depends on: 13-3 (both macOS slices for C4); and the phase-13 header in full: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Part of: [phase-13](phase-13.md) · Lead subject matter: Seat 5 (Deadline keeper), "host conformance (pluginval, auval, state, automation, undo, buses, latency)"; "anything on or beside the audio thread"; "CI gates" · Read first: [`phase-13.md`](phase-13.md) (umbrella), `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Goal

This sub-phase's share of the umbrella goal ("Turn the vertical slice into a **private-beta build**"): survive
real-world host behaviour.

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.
  (phase-13 assumptions, shared)

## Scope

1. **Robustness tests** (Catch2 + pluginval options): (phase-13 scope 3; its last bullet, cross-architecture
   determinism, in 13-3)
   - 10 instances in one process, all processing; the CPU sum is recorded. Multi-instance RSS is recorded
     on three OSes, including Bitwig's per-plugin sandbox, where the AX38 transient counts per instance.
   - Sample-rate change at runtime (44.1 ↔ 96 kHz) and buffer-size change without re-instantiation.
   - `processBlock` with 0-sample and 1-sample buffers, and with silence for 60 s (CPU must not spike;
     denormals off).
   - Bypass (`processBlockBypassed`) keeps the latency constant and outputs a delayed dry signal.
   - Load every state fixture from Phases 07–12 (`tests/state/`).
2. **AX34:** decide whether to add internal resampling for unsupported rates (quality verifiable),
   replacing the bypass-like fallback (Phase 07 D8). (phase-13 scope 11)
3. **Cache the pinned pluginval release in CI** (`actions/cache`, keyed on the pinned version and its
   checksum) so that a GitHub Releases outage cannot fail CI (Phase 07 follow-up: CI run 42465826545
   attempt 1 failed only at the pluginval download, HTTP 504 on all three runners). May be pulled
   forward as a standalone tooling change before Phase 13. (phase-13 scope 12)

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5. (phase-13 out of scope, shared)
Every item the umbrella's table assigns to 13-1, 13-2, 13-3 or 13-5.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression). (phase-13 C1, umbrella shared: for this
      sub-phase's PR)
- [ ] Robustness tests above pass (phase-13 C3, clause 1; the cross-architecture clause in 13-3)
- [ ] pluginval strictness 10 on the **release** build, 3 OSes (both macOS slices). auval passes. (phase-13 C4)

## Listening / manual checklist (Maisara)

None. (All of phase-13's listening and manual items are in 13-5.)

## Contractor review focus

threading under multi-instance load (phase-13 contractor review focus, clause 2; the other clauses in 13-1 and 13-5).

## Risks

The umbrella's risks (phase-13 K1–K3) apply.

## Notes from the split

- C4 needs both macOS slices, i.e. 13-3's universal binary. Scope 3 (phase-13 scope 12) may still be pulled forward
  on its own, as the original scope item allows. (map-13 §2, order rationale)
- S11 in 13-4 (13-c2, NOT A DECISION, resolution (a): convening round).
- 13-5's compatibility matrix and the public Bitwig note use this sub-phase's scope 1 multi-instance result
  (phase-13 scope 6, in 13-5).

## Definition of done

All automated criteria green (phase-13 definition of done, clause 1, shared: this sub-phase's criteria); status
row 13-4 `done` (CLAUDE.md rule 6; status row 13 stays on the umbrella). CLAUDE.md rules apply: one sub-phase per
session; if it can't be finished in two sessions, split the remainder into `phase-13-4b.md`.
