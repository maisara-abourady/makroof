# Phase 10-1 — Position-only tail cache

Size: **S** (remainder, if needed: `10-1b`) · Depends on: 06, 07, 08, 09 · Part of: [phase-10](phase-10.md) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; the representation handed to the renderer; simulator compute and recompute time" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ10, AX20), PRD FR-SIM-6, NFR-3, Q4, the umbrella [`phase-10.md`](phase-10.md)

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3). (phase-10 goal, shared)

This sub-phase's share: a keyed cache of the unmatched unit-energy per-band decay (per output for 08/09) used by
every rebuild in the product path, with E_b (diffuse solve included), t_mix,e, the AX20 list, AX16 list and the
ISM→tail crossfade recomputed each time (map-10 §1).

## Assumptions in force

All of the umbrella's ([phase-10](phase-10.md)); the one bearing on this sub-phase:

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
  (phase-10 assumption AQ4, shared)

## Scope

2. **Tail cache:** cache the Phase 04/08/09 **unmatched, unit-energy per-band noise decay** (Phase 04
   scope 3: it depends only on V, S, ᾱ_b, m_b, `tailSeed` and the sample rate, per output for 08/09),
   stored **before** E_b scaling, `t_mix,e` gating and the ISM→tail crossfade. Key it by (room
   dimensions, materials, mode, seed, sample rate). Every rebuild, including a position-only one,
   recomputes the early part, the AX16 scattered-energy list, each emitter's `t_mix,e` (it follows the
   emitter's direct-arrival time, so it depends on positions), the AX20 time-bounded image list (every
   image of any order arriving before t_mix,e + 2.5 ms; `maxReflectionOrder` has no effect on it), E_b
   (against ē_b, which depends only on T60_b, t_mix,e on the cached decay's emission-referenced time
   axis and the IR length) and the crossfade from the new image list. Prove the
   result equals a full rebuild (test), including a move that changes t_mix,e and the time-bounded
   image list. Since phase 05b, E_b includes the diffuse solve (AX37, AX39), recomputed every rebuild with
   no cache credit (AX38 4b). A cache of the diffuse computation (a room kernel) comes only through a new
   AX, which reopens AX38 (ii) (128 MB additional resident) and AX38 4b together. (phase-10 scope 2)

## Out of scope

The umbrella's out-of-scope list ([phase-10](phase-10.md)), and every other phase-10 scope item (scope 1, 3, 4, 6,
7 clause 1 and 8 in [10-2](phase-10-2.md); scope 5 and 7 clause 2 in [10-3](phase-10-3.md)).

## Acceptance criteria — automated

- [ ] Tail-cache result equals a full rebuild within −120 dB. (phase-10 AC5)

## Listening / manual checklist (Maisara)

None. The phase-10 listening items are in [10-2](phase-10-2.md) and [10-3](phase-10-3.md).

## Contractor review focus

- cache-key completeness (a stale tail is a nasty bug) (phase-10 CR2)

## Risks

None of the phase-10 risks falls to this sub-phase (R1 in [10-2](phase-10-2.md), R2 in [10-3](phase-10-3.md)).

## Notes from the split

- Order 10-1 → 10-2 → 10-3: "(A) follows the data dependencies (AQ10: AC8 rebuild hits the tail cache; AC7 needs
  the realtime-sim intervals)" (convening round, 10-c1 (A), `docs/review/phase-split/1-decider-convening.md`).
- 10-1 standalone: "owns AC5, one subject, carries risk CR2" (convening round, 10-c3 (a)).
- 10-1 leaves `main` green: it "adds a cache that a test proves equal to a full rebuild" (map-10 §1).

## Definition of done

- All automated criteria green (phase-10 DoD1, for the criterion this sub-phase owns: AC5).
- Status row 10-1 `done` (phase-10 DoD3; the umbrella row 10 is `done` when 10-1…10-3 are).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder
  into `phase-10-1b.md`.
