# 29-seat6: Seat 6 on M3-H (brief B6)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 6 POSITION (brief B6, M3-H re-run; for `docs/review/phase-07c-2b/29-seat6.md`; read-only, the orchestrator saves it)

**1. Reading.** The question is where and when the cause of findings (a), (b) and (c) is ruled. My row is touched in one place: whether the canvas and parameter map deliver users to the finding's geometry, and whether 11-2's canvas, 11-3's note and 12-2's presets are designed before or after the ruling. Cues from my §4: "positions that recompute heavily"; "a default that is not the most realistic state"; and, from §2 criterion 1, "trust before range". The edge of the range must still be reality.

**K8 answered, from the code.**
- `ParameterMap.cpp` L32–36: `axisFromNormalized` gives lo + clamp01(n)·(side − 2·lo), with lo = `kSurfaceClearanceM` = 0.1 (`Validate.h` L28). L25–30: `clamp01` sends every value ≤ 0 (and NaN) to 0, and every value ≥ 1 to 1.
- `SceneModel.cpp` L98–102 (`clampToMarginBox`) and L202: the D1 push-away also ends in that clamp.
- Phase-11-2 scope 2: a drag is clamped "with the same rules as `module3d::SceneModel`".
- **So a drag or an automation lane past a face lands exactly at 0.1 m, to floating-point precision. It does not land merely near it.** In the 20 × 30 × 10 m room, emL = (1, 1, 1) is (19.9, 29.9, 9.9) m, which is both_corner's emitter L exactly (`abx_kit.py` L143).
- On the canvas: a top-view drag into a corner, plus a side-view drag to the floor or ceiling, reaches three faces. Lanes drawn to 0 or 1, and `room_*` automation (normalised 1 stays on the wall at every room size), reach the same points.
- The clamp acts as a magnet: every overshoot collapses onto the finding's geometry `[Inf]`. How often producers do this belongs to Seat 8.
- Defaults are untouched. The plugin's default sources L (3, 9, 2) and R (5, 9, 2) are ≥ 2 m from every face (`ParameterMap.cpp` L14–15).
- AX44's note U does not cover this case. Its both-near branch needs the listener within 0.70 m of a face too, so a corner source with a distant listener gets no user note (BUILD_PLAN AX44).

**2. Ranking**
- **H4+G, H2-cg, H3+G: prefer** (tied on my row).
- **H4, H3, H2-c: can live with.**
- **H1: can live with, at a major later cost.**

**3. Tension now.** 0 for all seven options. No control, name, range or default changes now.

**4. Tension later**
- **H1: 2.** 11-2 (canvas and clamp), 11-3 (note) and 12-2 (presets; Seat 6 supporting) are all built before a 13-2 ruling.
  - If the ruling is "breach" or "GA limit", the honest UI response is a note branch for a one-end corner. That means touching AX44's predicate, which is pinned in the D5 golden (a golden round), and re-checking the note text and preset placements.
  - Undo: rework of 11-3, plus a golden round, plus a 12-2 re-check. That is roughly a phase.
  - The evidence arrives at 13-2, one phase before the 13-5 beta.
  - There is also a hazard. Late and under pressure, "move the clamp inward" will look cheap. Raising `kSurfaceClearanceM` changes the metres that every position value maps to. That remaps saved automation, and the parameters are frozen once released. Done as a substitute for a `src/sim` fix, it would break FR-3D-5 L75 and NFR-8 L112. If done after release, I rate it veto-grade.
- **H2-c: 1.** The ruling precedes 08-4 (phase-07d L79–80), so it precedes 09 → 11 → 12-2. The residual is that the order lives only in 07d prose, not in a §0 Depends-on. If that is missed, the canvas could be designed blind.
- **H4: 1.** Same reason: the gate sits in Notes and prose only.
- **H3: 0.** The block of all of 08 is a phase-level dependency.
- **H2-cg, H3+G, H4+G: 0.** The gate is on a committed artifact or in Depends-on (G1), so the ruling lands before any canvas or preset session reads it.

What each later cell commits later phases to: 11-2 and 11-3 start with the ruling in hand. For every option except H1, the evidence arrives at the ruling, which is before 11-1.

**5. Evidence**
- Clamp and margin behaviour: [Obs, code] at the lines cited above.
- The 11-2 clamp rule: [Obs, plan] phase-11-2 L22–24.
- Order 11-2 ← 11-1 ← 09 ← 08: [Obs] BUILD_PLAN §0 L50–51 and file 20 "Phase order".
- U is silent for one-end placements, and U is golden-pinned: [Obs, plan] AX44.
- Parameter freeze: CLAUDE.md, and `ParameterMap.h` L5.
- "Trust before range": W1 (Indoor's limits keep every setting inside reality) [SRi; ASFX16].
- Frequency of corner placement: [Hyp]. Corpus not opened; I make no acoustic claim.

**6. Conditions of acceptance**
- **H1 (2→1):** the ruling must land before 11-1 starts. In substance that is H4. Separately, the plan should state that no ruling is ever answered by moving the AX6 clamp.
- **H4 and H2-c (1→0):** G1, or H2-cg's artifact gate, written as a Depends-on.

**7. Hand-offs**
- **Seat 2:** the 07e sweep should include a room a user can reach (`medium_room` 8 × 12 × 4 m) at normalised 0/1 on 1, 2 and 3 axes. layout4 (floor α 1, s 1) is not one. Whether (a) generalises sets what the canvas must say.
- **Seat 8:** how often producers put sources in corners and against walls.
- **Seat 1:** whether a ~6 dB tail deficit is audible.
- **Seat 9:** placements in 12-2's presets.
- **Seat 5:** the G1 wording.
- **Decider:** record the 07e skeleton's Seat 6 hand-off as answered (K8, above). Its "Out of scope: preset or canvas changes" is correct. Any canvas or note consequence goes to 11-2 or 11-3 by ruling.

**8. Premortem.** H1 is chosen and 11-2 ships its exact 0.1 m clamp. A producer drags a sub into a corner and the room goes dry while U stays silent. The first to notice is a beta user, and the fix offered under deadline is the clamp move that remaps every saved automation.

Files read: /home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md, 5-builder-tail-spread.md (L1–40), 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md; /home/user/makroof/docs/PRD.md L45–112; /home/user/makroof/docs/BUILD_PLAN.md (§0 rows 11, 11-1, 11-2, 12-2; AX9; AX44); /home/user/makroof/docs/phases/phase-07d.md L75–103, phase-08-3.md L58–87, phase-08-4.md L20–27, phase-11-2.md, phase-12-2.md L40–64; /home/user/makroof/src/module3d/ParameterMap.cpp L1–60, ParameterMap.h, SceneModel.cpp L80–209; /home/user/makroof/src/contract/Validate.h (L28–29); /home/user/makroof/tools/ci/abx_kit.py (L138–160).
