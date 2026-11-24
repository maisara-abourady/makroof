# 1: Seat 4 (chain keeper), M3: the 0.1 m placements in binaural, layout5/default, item 15

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE"). Run 2026-11-24 in the
phase-07c-2b session as `seat4-chain-keeper`. Recorded verbatim from the seat's answer.

SEAT 4 POSITION

Corpus not present (`docs/corpus/` missing in this checkout). The acoustic claims below come from my register or are flagged.

**1. Reading.** M3 picks the 07c-2 ABX scene(s) and the scenes for file 13 item 15, the 08-3 binaural rerun (13-decider-rebuttal-r4.md L205). I was asked about the 0.1 m placements in binaural and about layout5/default. The matter triggers three of my cues:
- **Missing or contradicted room cue.** Every s = 1 scene has an empty early part (29-k4 fact 4).
- **Model violated.** The 08-3 tail is isotropic and equal across the ears (08-3 scope 5, L25–36; AX44), and some of these rooms are not.
- **Chain/scene confound.** A binaural run with no omni run on the same scene mixes up the chain with the scene.

**Answer on the 0.1 m placements in binaural.**
- **Near-wall cue missing in both chains.** At s = 1 the boundary image is zeroed (AX21). The reflection that defines the position is absent: delay 2·0.1/343 = 0.58 ms, first comb notch at about 857 Hz (my arithmetic). The binaural render is therefore a free-field position at the same distances. Omni has the same omission, so the comparison across chains stays valid. The result must not be read as binaural evidence for near-wall listening.
- **Wall behind the listener (listener_wall, both_wall): usable.** Under AX3 (BUILD_PLAN L126) the yaw is 0 and the wall is behind, so the error is symmetric between the ears. The isotropic, equal-ear tail is not contradicted interaurally. both_wall's emitters sit at −5.8° and +8.6° (atan(3/29.8), atan(3/19.9)).
- **Wall at the side (listener_edge, listener_corner, both_corner): not usable for binaural.** The listener is at x = 0.1, so the left ear is about 1 cm from a face with α 0.01 (head half-width 8.75 cm assumed `[Hyp]`). A real diffuse field would be louder at low frequencies in that ear only (near-boundary energy rise `[Hyp, register; corpus absent]`). The renderer gives equal ear energies by construction. That is a lateral asymmetry the binaural tail cannot represent, and the head cannot physically occupy the corner placements.
- **Emitter at the wall (emitter_wall): no delivery issue.** Only the source sits at the wall.

**Answer on layout5/default.**
- **Placement:** default, so no near-wall issue.
- **Room cues:** D/R −1.4 dB and tail share 0.579 (29-k4 L40). That would be a better externalisation condition than S-A's +13.1 dB.
- **Problem:** the α = 1 face is xMin, 10 m to the listener's left. A real late field there is strongly anisotropic from left to right. The 08-3 tail is diffuse-field coherence with E_b bit-identical across the ears (AX44). So a binaural render of layout 5 has a symmetric tail in a room whose tail is lopsided: the DirAC lesson (incident 7.5).
- **Layout 4 is different:** its absorber is the floor, on the median plane, so it is symmetric between the ears.
- **Seat 1 and Seat 9 risk:** layout 5's heard T30 (2.557 s) is below its tail-alone T30 (2.58–2.62 s), so the M2 gap assertion is at risk (34-decider L26).
- **Effect on V3 with default only:** adding layout5/default to the S-W pool changes nothing, because both_wall (0.667) outranks it (0.579). It becomes S-W only if both_wall fails to qualify. emitter_wall (0.869) would always win.

**S-B\* choice: s = 0.7.** Its early part is −3.8 dB re direct, against −9.5 dB at s = 0.9 (29-k4 L30, L32). So it puts real load on the binaural early-reflection path (per-image HRTF), which carries externalisation.

**2. Ranking**

| option | label |
|---|---|
| **V1′ (my addition):** 07c-2 runs S-A and S-B\*(0.7); 08-3 runs S-A and S-B\*(0.7) binaural | prefer |
| **V2**, with S-W limited to the default or a wall-behind placement | prefer |
| **V4** | can live with |
| **V3** | can live with, only with layout 5 kept out of the binaural part |
| **V1** | can live with |

V1′ is the only option where every binaural run has an omni twin on the same scene and seed, and the early part is exercised.

**3. Tension now.** 0 for every option. The 07c-2 chain is omni and diotic.

**4. Tension later (debt)**

| option | rating | why | undo cost | evidence arrives |
|---|---|---|---|---|
| V1′ | 1 | S-A binaural is a dry, static, uncompensated render (B14, 08-3 R7) | — | 08-3 L4 and L5 |
| V2 | 1 | (i) is matched on a tail-heavy scene, which is better for externalisation. (ii) S-B\* has no omni twin, so its result stands alone. | — | — |
| V4 | 1 | (i) is the driest scene (+13.1 dB), the most likely to be heard inside the head. (ii) is unmatched. | — | — |
| V3 | 2 | If a layout-5 scene becomes S-W, the binaural ABX runs on a tail the room contradicts | A further 08-3 scene and session, about 2 h (32-k5-k6 K6) | 08-3 L4 (the image sits on one side or not), or any later anisotropic-tail work |
| V1 | 2 | The only scene with an early part never reaches binaural. Both binaural scenes have an empty early part. S-W binaural has no omni twin. | One more 08-3 session | Any B11 promotion (file 26) |

**5. Evidence**
- Empty early part, tail shares, D/R, T30: 29-k4 L28–46, facts 4 and 9. [Observed, from the code]
- Binaural tail with isotropic coherence and equal ear energies: phase-08-3.md L25–36. [Observed, plan]
- Reverberation improves headphone externalisation: Begault Ch. 3, Table 3.2, as cited in file 26. I could not re-check it here because the corpus is absent. Incident 7.1. [Observed]
- Real late fields with a single lateral absorber produce an interaural level difference large enough to matter: `[Hyp]`.
- **Researcher:** (a) late-field ILD or coherence with a one-sided absorber; (b) diffuse-field level rise near a rigid boundary, within 0.1 m and in ear-sized regions; (c) tail-level JNDs, binaural against diotic (still open from file 26).

**6. Conditions of acceptance**
- **V3, 2 → 1:** layout-5 scenes are excluded from item 15. Failing that, the binaural record is labelled "isotropic tail, anisotropic room", with per-ear tail energy printed.
- **V1, 2 → 1:** 08-3's second binaural scene becomes S-B\*(0.7) instead of S-W. That is V1′.
- **All options:**
  - (a) The x = 0.1 listener placements are barred from item 15.
  - (b) S-B\* = s 0.7.
  - (c) At 08-3: per-ear peak ≤ −1 dBFS, per-ear item 6, and M1's identity assertion per ear on S-B\* (share > 0, 34-decider item 2).
  - (d) File 26's (a) to (d) carry over: same scene and tailSeed; parity ±1 dB; the binaural result wording; a B11 void.

**7. Hand-offs**
- Seat 1: S-W's sensitivity, and α across three families (union rate ≤ 0.147).
- Seat 1 and Seat 3: both_wall's far-emitter burst overlaps 29.3 ms of the fade (32-k5-k6 L59–62).
- Seat 2 and Seat 9: layout 5's provenance and whether its Eyring fit holds (heard T30 below tail T30).
- Seat 7: the hours for V1′ against V2.

**8. Premortem.** Suppose layout5/emitter_wall becomes S-W under V3. Then 08-3 reports a binaural threshold on a tail that is symmetric where the room is one-sided. Maisara notices first, on L4, when the reverberation does not lean away from the absorbing wall.
