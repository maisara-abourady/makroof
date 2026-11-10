# Orchestrator computation C16c: U at n\*_max 8 000 with the union VOV (decider addendum)

2026-11-10. Asked for in `37-decider-round4-addendum.md` (reported, not blocking). The question is whether the note's VOV leg,
computed over pilot ∪ final range up to the first 8 000 histories, changes U at n\*_max 8 000 for any of C16 (f)'s cases.
Code: step `c16c`; data: JSON section `c16c`.

**Result: no case changes.** For every C16 (f) case at n\*_max 8 000, U is the same under the union VOV as under the
pilot-only VOV. Three kinds of case cannot change at all:
- cases where the pilot ran the full 8 000 histories (the union is the pilot itself);
- cases decided by a cap hit;
- cases decided by the SE > 0.33 dB leg.

The rest kept their outcome. In particular:
- U stays silent at every Phase 04 default and one-end placement, in the D-T6 small room and in the closed 100 m cubes at s = 0.3;
- U still fires on `living_room` both_wall_0.1 and W1 both_wall_0.3.

Seat 6's condition (ii) is unaffected, so Seat 6 does not need to re-confirm.
