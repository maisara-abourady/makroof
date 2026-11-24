# 1-seat4: Seat 4 (chain keeper) on M3, V1–V4 and item 15 (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 4 POSITION

Corpus not present (`docs/corpus/` is empty). The acoustic claims below come from my register or the plan text, and each is flagged.

**1. Reading.** M3 chooses the 07c-2 ABX scene or scenes, and with them the scenes item 15 reruns binaurally at 08-3. It triggers three of my cues:
- **Missing room cue:** every s = 1 scene has an empty early part (K4 fact 4).
- **Model violated:** a listener 0.1 m from a face, rendered through a free-field HRTF.
- **Comparability:** a binaural result read against an omni result on the same scene.

**Seat-specific answers.**
- **0.1 m placements in binaural.** In layout 4, every candidate with a tail share above emitter_wall's 0.132 puts the listener 0.1 m from a face (K4: both_wall 0.667, listener_corner 0.256, listener_edge 0.208, both_corner 0.199). So the S-W rule picks a listener-at-wall scene under every K5 outcome, and K5 cleared both events as false positives.
  - Listener positions are the head centre (AX44). With a KU100-sized head (SADIE II D1, THIRD_PARTY L53), the near ear sits about 1 cm from the wall [Hyp: head half-width about 9 cm].
  - The shipped HRTFs are free-field, so none of them represents that head.
  - The wall's specular image is zeroed at s = 1 (AX21). Had it been rendered, it would arrive 0.58 ms after the direct sound (path difference 0.2 m; first comb notch about 860 Hz; my arithmetic).
  - AX44's own GA limit makes no accuracy claim at layout-4/5 edges and corners, and puts the near-wall rise at up to +3 dB (Kuttruff Eq. 2.50, via BUILD_PLAN; not re-checked against the corpus).
  - A binaural rerun there is still a valid omni-vs-binaural comparison on the same stimulus. It is not evidence about what a producer hears at a sensible position.
  - Emitter-only placements (emitter_wall) are harmless binaurally: the listener is at the default position.
- **layout5/default.** The listener is at the default position, so there is no head-position problem. One issue is mine: the absorbing lateral face (xMin) makes the real late field left-right anisotropic, and the 08-3 tail is isotropic by design (AX37 (5.3); directional tail is backlog B18). The binaural render is therefore the plugin's isotropic tail, not that room's. That does not invalidate a detection test (the plugin's output is what ships), but it needs a label.
  - Note for others: layout 5 fails the M2 gap check as it stands (heard T30 2.557–2.575 s against tail 2.58–2.62 s; decider file 34 item 3).
  - Under V3, S-W picks layout5_s1/emitter_wall (0.869) if that scene is added. If only layout5/default (0.579) is added, S-W stays on layout-4 both_wall (0.667).

**2. Ranking.**
1. **V4: prefer.** It is my file-26 S-D. (i) is the same scene in both chains with a representable head position. (ii) is the only binaural run that exercises `Kind::Binaural`'s early part.
2. **V1′ (my variant): prefer.** V1 with 08-3 (ii) = S-B\* instead of S-W. Both binaural scenes then have an omni baseline, at the cost of one more 2 h block (Seat 7's matter).
3. **V3 with layout5_s1/emitter_wall as S-W: can live with.**
4. **V2: can live with,** on conditions.
5. **V1: can live with,** on conditions. It is ranked last: the only scene with an early part never goes binaural, and the binaural S-W has no omni baseline.

**3. Tension now.** 0 for every option. The 07c-2 chain is omni and diotic.

**4. Tension later.**

| option | later | why |
|---|---|---|
| V4 | 1 | Debts left: B14 (no headphone compensation, 08-3 R7); a static, generic head; a B11 promotion breaks (i)'s comparison; S-B\* has no omni baseline. Undo: one session. |
| V1′ | 1 | Same B14 and B11 debts. Every binaural scene has an omni baseline. |
| V3 (emitter_wall) | 1 | Isotropic-tail label; the M2 gap check must pass; AX47 needs a /fix-plan. If S-W lands on layout-4 both_wall instead, rate it as V2. |
| V2 | 2 | (i) is a head at a wall, with an empty early part, that would be read as binaural evidence. Undo: a 2 h session at 08-3. The evidence arrives at 08-3 L4/L5 and on the per-ear prints. |
| V1 | 2 | No binaural run with an early part. S-W binaural has no omni baseline. Both binaural scenes are s = 1. |

**5. Evidence.**
- Empty early part at s = 1, filled at s < 1; tail shares; placements: file 29 table and facts 4–5 (from the code).
- K5 false positives: file 32.
- No tail directions: phase-08-3 L14–16 (AX37 (5.3), B18).
- Near-wall GA limit: AX44 (BUILD_PLAN L167).
- Reverberation aids externalisation: Begault Ch. 3. [Observed; corpus absent now, cited from file 26]
- Head-position validity of free-field HRTFs next to a wall: [Hyp]; my persona has no incident for it. Researcher: are there HRTF-near-boundary data for a head 0–5 cm from a wall?

**6. Conditions.**
- **V2 → 1:** either
  - (a) S-W is drawn from placements with the listener ≥ 0.70 m from every face (AX44's d_L threshold), which gives layout4 emitter_wall; or
  - (b) (i) is labelled "chain comparison only; listener 0.1 m from a face, outside the free-field HRTF's validity" and is never counted as binaural evidence for the class.
  - I prefer (a).
- **V1 → 1:** replace 08-3 (ii) S-W with S-B\*, which makes it V1′.
- **All options, at 08-3:**
  - Run sheet §2 is amended for binaural: the same wired headphone model and level setting as the 07c-2 session, and no virtualiser.
  - On each scene, before any stimulus: per-ear parity within ±1 dB (AC6), item 6 and `[ax47-midfade]` per ear, the M2/Q5 checks, and D/R per ear.
  - The `hrtfId` and the set identity string are recorded.

**Item 15 under V4 (draft wording, not adopted).** "15. 08-3. Before Phase 08's goldens freeze, the AX47 self-ABX is rerun on the binaural chain at the bound in force, in one dated sitting, as two pre-registered families. Each family uses item 3's thresholds with item 4 applied within it, and the record states the union rate.
- (i) layout4_s1/default, with tailSeed 12345, programmes, steps and trials identical to 07c-2's, so the chain is the only variable.
- (ii) S-B\* [s 0.7 or 0.9], guaranteed.

Before any stimulus is built, on each scene: binaural vs omni per-band energy within ±1 dB (AC6); item 6, `[ax47-midfade]`, the M2 gap and Q5 checks per ear; D/R printed per ear. The same headphone model and level as 07c-2, recorded with the `hrtfId` and set identity string.

Results are worded 'static, uncompensated (B14), generic HRTF', and for (i) also 'empty early part (AX21)'. Neither family is cited for externalisation or plausibility, and L4/L5 are not judged on these scenes. If B11 is promoted first, (i)'s omni family is rerun on the promoted IR, or the cross-chain comparison is recorded void."

**7. Hand-offs.**
- Seat 1: α split or unsplit, and S-W's sensitivity.
- Seats 1 and 9: layout 5's M2 gap failure.
- Seat 2: AX47's Reversal under V3.
- Seat 9: labels, including the isotropic-tail note.
- Seat 7: hours for V1′.
- Seat 6: whether both_wall raises the AX44 U note.

**8. Premortem.** Under V1 or an unconditioned V2, 08-3 records "not detected binaurally" from scenes with no early reflections, one with a head against a wall, and Phase 08's goldens freeze on that. The first to notice is Maisara at L4/L5, or a producer on a preset with early reflections.
