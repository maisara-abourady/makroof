# Seat 7 (founder) — re-run on 4a-2G++

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 7 POSITION (re-run), D-T4a

| option | now | later | one line, in my measures | condition |
|---|---|---|---|---|
| 4a-2G++ | 1 | 1 | Better than 4a-2 for my seat. The gate means at most one 1 GB solve per process, so the "project won't open" case I rated 3 under 4a-3 is gone. What remains is extra contractor work now (the gate plus its TSan and order tests) and, later, slower project loads and memory that grows with instance count. With 8 instances the per-instance additions come to at most about 1.0 GB resident in the worst case (8 × 128 MB) plus about 0.98 GB of Phase 07 baseline (8 × 122.6 MB) `[Inferred]`; whether that fits customer machines is `[Hyp]`, open until RQ1 and RQ3. Serialised solves also mean some stems may be silent at load until their turn: a support ticket and a lost trial if nothing explains it, not lost work. | These conditions keep the cell at 1/1; none of them lowers it further. (1) The "settling" state from (iii) appears on every instance waiting at the gate, project load included, so a silent stem reads as busy, not broken (support load: R1, R3). (2) If the 8-instance, 100 m record of time until the last instance is audible at load is over 10 s, it goes to Maisara before the first release, so it is never found by customers after release (V4). (3) The Bitwig per-plugin sandbox gap stays in the public compatibility notes until Phase 13 measures it. |

Evidence:
- The design comes from `docs/review/phase-05b2/11-decider-round3-T4a-T54.md` (D-T4a (i) to (iv)) and the Phase 07 baseline in BUILD_PLAN §0 row 07.
- Support and OS work are the real load: R1 `[Peer-report]`. Abrasive support loses customers: R3. Retroactive fixes draw backlash: V4 `[Self-report: incident]`.
- Customer RAM and instances per session are still unknown (RQ1, RQ3).
