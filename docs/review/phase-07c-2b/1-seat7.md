# 1: Seat 7 (founder), M3: V1–V4 against K6's hours; split or unsplit α

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE"). Run 2026-11-24 in the
phase-07c-2b session as `seat7-founder`. Recorded verbatim from the seat's answer.

SEAT 7 POSITION

**1. Reading.** M3 decides how many ABX scenes Maisara must listen to, whether they fall before the W pin (07c-2b) or at 08-3, and where a late reversal of the 1 dB bound would land. My §4 and §11 cues apply: "the founder's hour is the scarcest input"; "cheap now, borrowed from later phases". No price, licence or public wording is touched, because item 13 forbids public copy. So nothing here is veto-grade for me.

**Correction to my file 30.** I estimated 1 to 1.5 h per scene `[Hyp]`. K6 (file 32) replaces that: about 1.94 h per scene at a typical pace, 1.31 h brisk and 2.79 h slow. I withdraw my "both scenes in the same sitting" condition on V4. Two scenes take 3.9 h at a typical pace (5.6 h slow), which does not fit one sitting (K6: "does not fit one sitting of 2 h").

**Maisara's listening hours** (typical pace, brisk to slow, from K6 × number of scenes). These exclude the AX49 L4 ABX, which K6 did not time.

| option | before the W pin (07c-2b) | at 08-3 | total |
|---|---|---|---|
| V1 | 3.9 h (2.6–5.6) | 3.9 h | 7.8 h (5.2–11.2) |
| V2 | 1.9 h (1.3–2.8) | 3.9 h | 5.8 h (3.9–8.4) |
| V3 | 1.9 h | 3.9 h | 5.8 h |
| V4 | 1.9 h, or about 1.0 h if 0.9 dB goes undetected (1 block per chain) | 3.9 h | 4.9–5.8 h |

**2. Ranking.**
1. **V2: prefer.** It costs the fewest founder hours on 07c-2b's critical path, the same as V4. The most sensitive scene, S-W, is heard before the pin and the golden round. The scene heard after the pin is S-B\*, and every S-B\* candidate is less sensitive than S-A (ΔG 0.032–0.040 dB against 0.045, file 29). So a reversal after the pin is the least likely of the four options.
2. **V3: can live with.** It costs the same hours as V2, plus one /fix-plan cycle on AX47. These are orchestrator hours, not Maisara's. If Seat 4 rejects the 0.1 m placements in binaural, V3 moves to first: layout5/default spares 08-3 a scene swap.
3. **V4: can live with.** It is cheapest now. But the bound rests on S-A, the weakest stimulus, and the S-B\* result at 08-3 lands after the pin.
4. **V1: can live with, ranked last.** It has the most hours, and it doubles the hours before the pin. Its most sensitive scene, S-W, is heard only at 08-3, after the pin.

**3. Tension now.**
- **V1: 2.** It needs 3.9 h before the pin, which means two sittings. 07c-2b, and with it O4–O8 and the 08-x freeze, waits on both. With unsplit α there are two families before the pin, so the chance of a false 0.5 dB bound is ≤ 0.098.
- **V2: 1.** About 2 h, the floor for every option. K6 must be redone on S-W, because stimulus length scales with T30, which ranges 1.288–2.575 s (K4).
- **V3: 1.** The same as V2, plus one board cycle.
- **V4: 0.** About 1–2 h.

**4. Tension later (the debt).**
- **V1: 2.** 08-3 needs about 3.9 h again. If S-W first detects at 08-3, the bound drops to 0.5 dB after the pin. That means redoing 07c-2b's O4–O8 (the W pin, the solveRefMs re-pin, the golden round) during Phase 08: a phase of rework. The evidence arrives at 08-3 (ii).
- **V2: 1.** 08-3 needs two sittings. If S-B\* reverses, it costs the same rework, but that is the least likely case. The evidence arrives at 08-3 (ii).
- **V3: 1.** The same as V2. The AX47 widening is cheap to undo: a one-line row change.
- **V4: 2.** The same post-pin reversal path as V1, on a weaker scene. The bound is never tested on a sensitive scene, which is Seat 1's 2/2. If it is loose, it surfaces after release as "reverb jumps on automation" (my file 30 premortem). Evidence arrives at 08-3 (ii), or from users.

**Split or unsplit α.** Trial counts do not change, so Maisara's hours are the same either way. Split: 0 now, 1 later. It cuts noise power from 0.63 to 0.405, so a looser bound is more likely to slip through to users, which is a trust withdrawal after release. Unsplit: 0 now, 1 later. A false "detected" costs compute and load time, which is recoverable as a parameter (Seats 5 and 6 own that). On my seat I mildly prefer **unsplit**, with the union rate stated in the record. Under V1 it is the weaker choice: 0.098 before the pin.

**5. Evidence.**
- Hours, the T30 scaling and the one-sitting limit: file 32, K6 `[Observed]`.
- Sensitivity: ΔG for S-A against the s < 1 scenes, and S-W's larger share: file 29, fact 5 `[Observed]`.
- Bonferroni powers: file 31, answer 4 `[Observed]`.
- Rework scope: phase-07c-2b items 6–8; BUILD_PLAN row 08 (freeze after 07c-2b) `[Observed]`.
- Mapping hours to runway and trust: `[Inferred]`. My persona has no incident on scheduling validation sessions, so that part is `[Hyp]`.

**6. Conditions of acceptance.**
- **V1, to 1:** run S-W in 07c-2b instead of S-B\*, and S-B\* at 08-3. That is V2.
- **V4, to 1:** write two things into BUILD_PLAN row 08-3 and the 08-3 brief. First, if (ii) detects, 07c-2b's pin and golden round are rerun before 08-4's freeze. Second, 08-3 runs in two dated sittings.
- **Every option:** the builder redoes K6 on each chosen scene, adds the time of the AX49 L4 ABX, and puts the per-sitting plan in the session brief before sealing.

**7. Hand-offs.**
- Which scene S-W is, s = 0.7 or 0.9, and whether S-B\* is worth a family at all: Seats 1 and 9.
- The 0.1 m placements in binaural: Seat 4.
- The cost of a false 0.5 dB bound: Seats 5 and 6.
- The click_check fix: Seats 3 and 5.
- Whether Maisara can hold two sittings of about 2 h at 08-3: Maisara (a person's action, item 16).

**8. Premortem.** The board picks V1, or V4 with "same sitting". Maisara then faces about 4 h sittings at 07c-2b or 08-3, voids a block, and in the worst case reruns it (3.8 h per scene typical, K6). 07c-2b then sits `blocked (awaiting ABX results)` while Phase 08's freeze and the beta wait. The steward notices first, at the 07c-2b status row.

Files read:
- docs/review/phase-07c-2/31-decider-abx-r4.md
- docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- docs/review/phase-07c-2/30-seat7.md
- docs/review/phase-07c-2/28-interrogator-on-file27.md (Seat 7 row)
- docs/review/phase-07c-2/29-k4-candidates.md (table and facts)
- docs/phases/phase-07c-2b.md
- docs/BUILD_PLAN.md (§0 rows 07c-2b, 08, 08-1 to 08-4, 13, 13-1 to 13-5)
