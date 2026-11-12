# 3 — Seat 9 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 9 POSITION (phase 07c-1, Matters A–D; corpus present, revision as in file 2)

**1. Reading.** The question is what tail level plays between a restore or edit and the final solve, and whether the solved E_b is saved. The brief asks me which real rooms fall where AX16 is more than 1 dB off, whether interim errors of these sizes are audible at a seat, and whether a saved E_b is a provenance risk for Phase 12. Cues it triggers: coefficient and estimator provenance (§4); occupancy ("people are a material by area"); and an RT or level that is right on average but wrong at the seat (S2).

**Main finding (B3).** The cases where AX16 is more than 1 dB off are not edge cases. They are the occupied-room case.
- Kuttruff §5.7 calls Table 5.2 case 4 (absorbing floor, diffusely reflecting walls) "practically most important". It is a crude model of most auditoria, especially occupied ones, because the audience absorbs strongly and the absorption is lopsided.
- Kuttruff §6.7: medium and large halls (churches, theatres, entertainment halls) matter in the occupied state, and their absorption is largely the audience's.
- AX16's measured worst cases are that very class: layout 4 +3.83 dB, the absorbing-floor cube +2.38 dB. Even the measured BRAS CR3 room is −1.18 dB at 2 kHz (AX16 row).
- FR-3D-3 classes that sit there, from my reading [Inf, M]: occupied halls, chapels and churches; clubs and warehouses with a crowd on a hard-walled floor; a living room with carpet and sofa and bare walls (layout-4-like); rooms with one absorbing long side, such as a curtained wall or one open side (layout-5-like, sign reversed, −1.17 dB). In outdoor scenes almost all the surface absorbs; their capped or pilot-ships class is already handled by AX41's D-H3 (b) clause.
- So a predictor of AX16's error from scene data alone would have to work exactly in the most common presets, and its sign flips between layouts 4 and 5. I know of no such predictor [Hyp; Seat 2 to confirm, researcher K14]. Condition 5 ("never AX16 where > 1 dB off") therefore rules B3 out in practice.

**2. Ranking**
- **Matter A:** A1 *prefer* = A2 *prefer* > A0 *can live with* > A3 *can live with* (A3 is mostly not my matter).
- **Matter B:** B4 *prefer* > B2 *prefer* > B1 *can live with* > B3 *cannot live with*.
- **Matter C:** C2 *prefer* > C1 *can live with* > C3 *can live with* > C4 *can live with* (rated 2).
- **Matter D:** mostly Seats 1 and 3. One acoustic point: D1 at load removes all late energy. Beyond the critical distance that is many dB of G, far beyond the 1 dB jnd (Vorländer Table 6.1), so it is a different room, not a settling step. D3 is preferred to D5 (D5 plays a wrong-T60 decay; the EDT jnd is 5 %).

**3–4. Tension, now / later**

Matter A:

| option | now | later | reason |
|---|---|---|---|
| A0 | 1 | 1 | Load always goes to B, which is exact in 07c-1. |
| A1 | 0 | 1 | Keyed by the exact effective scene, so material values are included as numbers (12 CF3); interim only. |
| A2 | 1 | 2 | A saved number becomes the final level. If the key misses one dependency (fs, AX4 air, estimator D1–D7), a stale E_b ships silently into bounces and validation. Evidence arrives at 07c-2's W_max raise and the Phase 13 re-check. Undoing costs a state-version bump. |
| A3 | 0 | 1 | No acoustic issue for my seat. |

Matter B:

| option | now | later | reason |
|---|---|---|---|
| B1 | 1 | 1 | On edits the step is the edit's own change, delayed by the solve. That is fine at 81–131 ms; under 07c-2's longer solves it reads as the room changing by itself (Seat 6). |
| B2 | 0 | 2 | Exact in 07c-1. Under 07c-2 the stage-1 error is SE 0.13–1.33 dB in layouts 4/5 at s = 1 (AX41), so p95 ≈ 1.96 × SE ≈ 2.6 dB, more than 1 jnd, in exactly the occupied class above. |
| B3 | 3 | 3 | Fails condition 5 in the common occupied presets (above). |
| B4 | 0 | 2 | Same later cost as B2 at load. |

Matter C:

| option | now | later | reason |
|---|---|---|---|
| C1 | 1 | 2 | Steps above 1 jnd are allowed and only counted. |
| C2 | 0 | 1 | Matches condition 5's logic. |
| C3 | 0 | 2 | Below 1 jnd; it would fail B2 under 07c-2 even in the low-α s = 1 cube (p95 ≤ 0.89 dB). |
| C4 | 2 | 2 | No audibility guard at all. |

**5. Evidence**
- jnd for G and C80 is 1 dB, at 500–1000 Hz (Vorländer Table 6.1). It comes from paired-comparison and real-room tests; whether it holds for a step inside a running stream is Seat 1's question (R4).
- A step in tail level alone moves G and C80 by no more than the step [Inf, H; arithmetic]. G = 10·log10(E_d+e + k·E_l), so ΔG < 10·log10 k whenever the direct and early energy is above zero. C80 changes by at most the step, reached when the tail starts after 80 ms. A per-band E_b bound of 1 dB therefore bounds ΔG and ΔC80 by ≤ 1 dB. The bound is conservative near the source and tight beyond the critical distance.
- AX16 error values are from the AX16 row; B2's 07c-2 SE values are from AX41.
- Kuttruff §5.7 (Table 5.2 commentary) and §6.7 for why case 4 is the occupied-room model.

**6. Conditions of acceptance**
- **A2 → 1/1:** the key includes an estimator-version id that changes whenever D1–D7, W_max, n\*_max, AX4 or fs handling changes. Phase 12 presets never carry E_b (12 CF3), and preset validation always runs the solve, never a cached value.
- **B2/B4 → 1:** at 07c-2, a stage-1 estimate whose per-band p95 can exceed 1 dB at 500 Hz–2 kHz is not used as the interim level (C2 applies). Hold the previous level, or extend stage 1.
- **C1 → 1:** steps above 1 dB are refused (that is, C2).
- **C3 → 1:** apply 0.5 dB only if R4 finds a within-stream threshold below 1 dB.
- **C4 → 1:** add a numeric bound.
- **A4 test:** besides layouts 4/5 and the absorbing-floor cube, add one measured BRAS room (CR3, the AX16 −1.18 dB case) and one occupied-hall preset once 12-2 exists.

**7. Hand-offs**
- Seat 1: the within-stream step threshold (R4), and whether D1's gap counts as silence.
- Seat 2: whether any predictor of AX16's error exists; the completeness of the key.
- Seat 3: D3 and D5 cost and coloration.
- Seat 6: the delayed step under B1 in 07c-2.
- A human: any preference claim, and running the blind A4 check.

**8. Premortem.** B3, or an unbounded stage-1 interim under 07c-2, ships, and occupied hall and club presets open 2–4 dB too wet, then settle. The first to notice are producers A/B-ing a church or club preset right after load. Some of their bounces from hosts that do not signal offline carry the wrong level.