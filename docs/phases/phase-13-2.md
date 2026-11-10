# Phase 13-2 — Engine limits after optimisation

Size: **M** (remainder, if needed: `13-2b`) · Depends on: 13-1; and on 07c `done` or S13's versioning fallback recorded (header H) (D-PS4 Addendum, Seat 2 hand-off 1; S13 = phase-13 scope 13, below). Header H in full: 00–12, including 05b, 05h, 07c (`done`, or the versioning fallback of scope 13 recorded), 05d, 05e and 05f (05f `done` or Maisara's recorded acceptance of the two-room label; 05d `done` or `blocked (reason)`, decider report 15, accepted by Maisara, 2026-11-05; with 05c, if it exists, `blocked` only on Maisara's recorded decision) · Part of: [phase-13](phase-13.md) · Lead subject matter: Seat 2 (Engine architect), "simulator compute and recompute time" · Read first: [`phase-13.md`](phase-13.md) (umbrella), `CLAUDE.md`, `docs/BUILD_PLAN.md` (all of §2–§3), PRD NFR-2, NFR-4, NFR-6

## Goal

This sub-phase's share of the umbrella goal ("Turn the vertical slice into a **private-beta build**"): meet the
performance budget where it bounds the simulator (rebuild and diffuse-solve limits, the image-count cap), re-checked
on the code 13-1 optimised.

## Assumptions in force

- **AQ10** budget (partition P ≤ 512 samples at 48 kHz; reported latency P + 32 = 544 samples (11.3 ms)
  at the default P = 512 (phase-06b D1); ≤ 15% of one core per instance for a 3 s tail;
  IR rebuild ≤ 50 ms for the AQ10 workloads W1 and W2 (position-only), in every output mode
  (decider report 8, accepted by Maisara, 2026-11-05)). **AX5**: the definition of "exactly as saved" across machines.
  (phase-13 assumptions, shared)

## Scope

1. **Diffuse-estimator work limits and the restore (AX41, AQ10 amended 2026-11-10, phase 05b):**
   re-check W_max (provisional 3.05 M image evaluations per emitter, sized to pluginval's restore
   watchdog less D-H1's margin; re-derived once under phase-07c; board answer, decider files 43, 47, 51) and n\*_max (1 024, sized to 25 ms of the W1 target) on the release machines; any change is
   an output change (golden round, §6 row) and must be fixed before the first release. Q2a (C), moving the
   diffuse solve off the synchronous restore, prepare and `reset()`, is its own phase,
   [`phase-07c.md`](phase-07c.md) (board answer, decider files 47 §4 (iii), 51 §4 items 4 and 8): **it is a
   prerequisite for the beta**; if it has not landed, the estimator parameters are versioned in saved
   state before release. (phase-13 scope 13)

## Out of scope

Licensing/trial (B1), auto-update, anything listed in BUILD_PLAN §5. (phase-13 out of scope, shared)
Every item the umbrella's table assigns to 13-1 or 13-3 … 13-5.

## Acceptance criteria — automated

- [ ] Full CI matrix green; nightly validation green (no regression). (phase-13 C1, umbrella shared: for this
      sub-phase's PR)
- [ ] Raising N_cap with time freed by optimisation is an intended output change, proposed through /fix-plan
      (decider report 8, accepted by Maisara, 2026-11-05). Re-derive the
      AX22 i₀ after optimisation if AX22 records 'cap limits accuracy'. (phase-13 C2, sentences 2 and 3;
      sentence 1 in 13-1)

## Listening / manual checklist (Maisara)

None. (All of phase-13's listening and manual items are in 13-5.)

## Contractor review focus

None of phase-13's contractor review focus clauses is assigned here (umbrella coverage table).

## Risks

The umbrella's risks (phase-13 K1–K3) apply.

## Notes from the split

- 13-2 depends on 13-1 (D-PS4 Q1). Header H already carries the 07c dependency; made explicit, nothing added.
  (D-PS4 Addendum, Seat 2 hand-off 1)
- If `13-1b` changes rebuild time or diffuse-solve time, 13-2's i₀ sentence, its N_cap rule and S13's W_max / n*_max
  re-check re-run before 13-3's records are taken. (D-PS4 instruction 3, final wording, Addendum)
- S13's 'release machines', in 13-2, and S9, in 13-3, need Apple-silicon hardware; Maisara provides it (follow-up).
  (D-PS4 instruction 6, final wording, Addendum)

## Definition of done

All automated criteria green (phase-13 definition of done, clause 1, shared: this sub-phase's criteria); status
row 13-2 `done` (CLAUDE.md rule 6; status row 13 stays on the umbrella). CLAUDE.md rules apply: one sub-phase per
session; if it can't be finished in two sessions, split the remainder into `phase-13-2b.md`.
