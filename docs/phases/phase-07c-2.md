# Phase 07c-2 — W_max re-derived under (C), one golden round

Size: **S** (remainder, if needed: `07c-2b`) · Depends on: 07c-1 `done` (and, through it, 05h, 07 `done`) · Part
of: [phase-07c](phase-07c.md) · Lead subject matter: Seat 2 (Engine architect), "simulator compute and recompute
time" · Read first, in this order: `CLAUDE.md`; this file in full [and the umbrella, `docs/phases/phase-07c.md`, and
`docs/phases/phase-07c-1.md`]; `docs/BUILD_PLAN.md` §2 **AQ4, AQ10 (amended 2026-11-10), AX5, AX18, AX33, AX38,
AX41, AX44**; `docs/phases/phase-05h.md` (§3 D-H1, §4 scope 2, the solve seam); `docs/phases/phase-07.md` (state
restore, reset sequence, offline path); `docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 and
`51-decider-addendum-J1.md`; `49-interrogator-board-answers-C1-Q2.md`; ledger P05B2-C1Q2-01…14; PRD NFR-2, NFR-3,
NFR-6, FR-SIM-6.

The umbrella is a beta prerequisite: **Must be `done` before Phase 13's beta** (or phase-13 scope 13's versioning
fallback recorded) applies to this sub-phase as part of phase 07c (umbrella header).

---

## Raise with Maisara (first message and PR)

(phase-07c §2.1)
1. **Only if** this phase would land after the first public release without the estimator parameters
   versioned in saved state: Seat 7's condition fails and the item returns to Maisara (decider file 47 §4,
   strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.

## Goal

This is Seat 1's "now" 2, repaid when this phase lands with W_max re-derived from the background budget.
(phase-07c §0; the move off the synchronous paths is 07c-1's.)

## Assumptions in force

All of the umbrella's: §1 "Settled — do not reopen" (AX37–AX46 and the AQ10 amendment; the board's J1 answer; D-H1
as decided in phase 05h) and §3 Timing. D-C1–D-C3 as recorded by 07c-1 (AX rows).

## Scope

- **Timing** (phase-07c §3, first bullet; shared with the umbrella): Lands **before the first public release (the
  Phase 13 beta)**, with its W_max raise in one golden round. If it lands after release, the estimator parameters
  are versioned in saved state (Seats 5, 7; condition 1). (phase-07c §3 T1)

1. **Timing** (section 3): before the first public release, with its W_max raise in one golden round;
   after release only with the estimator parameters versioned in saved state. (phase-07c condition 1; shared
   with the umbrella)
3. **W_max re-derived under (C)** from the background budget: Seat 6's 3 s per emitter, the AX38 (iv)
   load mark, and Table 15.1's 700 ms / 3 s rows (Seats 1 (i), 3 (5), 5). It is not kept at (A). It stays a
   pinned work count, the same on every platform (AX41), re-derived from the C++ cost, never a time cap;
   AX41 and the AQ10 amendment are updated through `/fix-plan`. (phase-07c condition 3)
8. **Follow-on checks.** The Phase 12 (ii) preset check (no preset default raises U) is re-run under this
   phase's W_max (Seat 6 (e)). Phase 08 goldens in capped rooms carry a tolerance derived from the
   achieved SE, unless this phase lands before they are frozen (Seat 4). (phase-07c condition 8)

## Out of scope

- The umbrella's §9 (phase-07c §9): Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel
  cache (AX38 (ii), phase-10 AX only); n\*_max (Q2b (i) stays unless the C++ W1 measurement moves it, AX41).
- Conditions 2, 4–7 and the decisions D-C1–D-C3: [phase-07c-1](phase-07c-1.md).

## Acceptance criteria — automated

- [ ] W_max re-derived under (C) from the background budget (condition 3), pinned, equal on the three OSes;
      goldens updated once through `update_goldens.py` with the reason; §6 row. (phase-07c A6)
- [ ] The Phase 12 (ii) preset check re-run under the new W_max and reported, if Phase 12 has run;
      otherwise Phase 12 runs it at 07c's W_max. (phase-07c A9)

## Listening / manual checklist

- [ ] Load a project with a large room: the room is heard at once at the interim level, shows "settling",
      and moves to the final level without a click or an obvious jump. (phase-07c L1)

## Contractor review focus

- the W_max re-derivation from the background budget (phase-07c F6)

## Risks

The original phase file has no risks section; the umbrella's §0 gives the rationale.

## Definition of done

- Section 6 all checked with CI evidence (phase-07c §10, clause 1; here: this file's automated criteria).
- PR with the listening checklist, contractor focus, AX/ledger links and the "Raise with Maisara" item if it applies
  (phase-07c §10, clause 3; this sub-phase's share).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-2b.md`.

## Notes from the split

- Convening-round correction (`docs/review/phase-split/1-decider-convening.md`, Map 07c; confirmed in
  `3-decider-decision.md` and `5-decider-decision-r2.md` corrections item 1): "§2.1 Raise goes into both sub-phase
  files (the phase's first message is 07c-1's)." Each raises it in its first message.
- 07c-c1 (convening round, NOT A DECISION): "(a). The umbrella is the beta prerequisite (G3 default; matches §3 T1)."
- 07c-c2 (convening round, NOT A DECISION): "(a). The umbrella is brought forward (phase-08 scope 10: "W_max is then
  re-derived once, under phase-07c, with one golden round")."
