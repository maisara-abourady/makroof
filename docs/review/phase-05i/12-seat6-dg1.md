# 12 — Seat 6 (Canvas Designer): D-G1, gate scope (G-1)

Phase 05i, 2026-11-11. Convened by decider file 11 (Brief 6). Saved verbatim by the orchestrator (the seat only reads).

SEAT 6 POSITION

**1. Reading.** The code holds the diffuse-solve gate for the whole room-IR build; AX38 (i) says around the solve only. D-G1 decides who fixes this and when. For my seat it decides what the "settling" readout means (AX38 (iii), phase-11-3 scope 3) and how automated motion behaves with several instances, most when instances share one scene (FR-SIM-7). Cues (§4): positions that recompute heavily — motion is an architecture decision (Strategy D); a picture that must not lie about the engine (Strategy B4).

**2. Ranking.** (1) A′ prefer. (2) A prefer. (3) D can live with. (4) E can live with only under conditions. (5) B cannot live with.

**3. Tension now.** A′ 0: no user-facing change; a baseline before the fix means the gain in following can be measured, not argued (Strategy F, W3). A 1: no change now; without a baseline any later "following improved" rests on reasoning, not a record. D 1: same as A now; the extra phase costs nothing at my seat. E 2: a known defect in motion left without an owner or a register entry, against criterion 4 (motion is first-class). B 2: writes into her decision that an instance's ISM update waits behind other instances' whole builds (from the code, `ScenePipeline.cpp` L124–132, the gate encloses ISM, synthesis and solve).

**4. Tension later (the debt).**
- **A′ and A, 1.** Commits a new condition in 07c-1, next to condition 4 ("the ISM update is never held behind the diffuse solve"); one design, one phase; undo is a condition edit. Debt: the "settling" trigger has to be reworded (C1). Evidence: 07c-1's gate-wait record and the re-measure under 07c condition 7.
- **D, 1.** Commits the gate narrowed in a pipeline that 07c-1 then rebuilds (moves the solve off the synchronous paths and splits off the ISM update); the settling semantics risk being reworked twice. Benefit: narrowing lands earlier.
- **E, 2.** Condition 10 lifts the release rule at 07c-1; if G-1 has no register entry by then it can reach producers with no owner and no record. Undoing later costs a phase.
- **B, 3 (veto-grade).** Serialised builds per process become the decided design; following degrades linearly in N, and the stems of a shared scene arrive at a new position one after another. Records (file 3, Linux): room-size step on 8 instances, staleness min 163 to max 1 280 ms in the AQ10 room at 48 kHz, 361 to 2 776 ms at 96 kHz, 1 963 to 16 304 ms at 100 m / 96 kHz; the joint step with a listener move 155–1 221, 346–2 634 and 2 015–15 705 ms. Veto-grade because criterion 1 (§0(b)) is "what they placed is what they hear": a listener move that sounds as N staggered arrivals breaks that in the common case for FR-SIM-7, not at an edge. It also contradicts 07c-1 condition 4 across instances: either condition 4 bypasses the gate (B's wording stale at once) or condition 4 cannot be met. Undoing costs a second amendment plus the A remedy.

**5. Evidence.** Gate scope encloses `buildRoomIR` (ISM, synthesis, solve): from the code, `ScenePipeline.cpp` L115–133. The solve is a small share of a 100 m / 96 kHz build: `solveMedianMs=80.9` against `fullRebuildMedian=1870` on Linux (file 3 L9), so whole-build gating serialises about 23× the work AX38 (i) intends to gate (my arithmetic; what narrowing buys is unmeasured, K-g5, Seats 3 and 5). That the staggered arrival is audible is [Hyp] (Seat 1 rules; Table 15.1's 700 ms row by extension, corpus not re-read here). "Silence is not approval; measure": incident W3 (FF-forum-float). A helper that misreports engine state destroys trust: W4, Strategy B4 (FST21).

**6. Conditions of acceptance.**
- **C1 (for A, A′ and D):** "settling" must be keyed to an update that is pending and not yet audible (queued at the gate, building, or awaiting the AQ4 crossfade, i.e. Phase 10's staleness above zero), not to "waiting at the gate": once the gate is narrowed, an instance computing its ISM or synthesis outside the gate is stale but would show nothing, so the readout would lie. Wording to align: AX38 (iii), phase-11-3 scope 3 and 07c-1 A3.
- **C2 (for A, A′ and D):** 07c-1's remedy record prints the spread of staleness across instances (min to max) for the joint listener step, before and after the fix; in a shared scene that spread is what the user hears.
- **E (2):** to 1 by adding the register entry and release-rule coverage (that makes it A).
- **B (3):** to 2 only if the amendment ends at 07c-1 ("until 07c-1 narrows the gate"), which is A under another name.

**7. Hand-offs.** Seat 1: whether a 0.2–2.8 s stagger across stems after a listener step is audible. Seat 5: whether A′'s poller fits inside 05i scope 2; safety of narrowing before 07c-1. Seat 2: the form of the solve hook in `BuildOptions`. Seat 3: CPU sharing once builds run concurrently. Seat 7: the cost of D. Seat 8: multi-stem workflows. Phase 11-3 (mine, later): a scene-level "settling" aggregate when instances share a scene, so the user is not reading eight per-instance indicators.

**8. Premortem.** If B is chosen, the first beta producer automates a listener walk across eight stems and hears the drums arrive a second or more after the vocal; the bug report reads "the scene smears when I move"; 07c-1's condition 4 test catches it first.
