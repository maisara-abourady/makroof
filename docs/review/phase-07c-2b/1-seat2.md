# 1-seat2: Seat 2 (engine architect) on M3, V1–V4 (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION (phase 07c-2b scope 2, M3: the ABX scene for the AX47 self-ABX). The corpus is not present in this checkout (`docs/corpus/` missing). Corpus facts below come from the corpus citations in files 26, 28 and 31, and each one is flagged.

**1. Reading**
- The question: which scene(s) carry the AX47 self-ABX at 07c-2 and at 08-3 (V1–V4), given the K4 table (file 29) and K5's finding that both click events are detector false positives (file 32).
- Cues it triggers:
  - §4 cue 3, geometry class: the absorber is concentrated on the floor (layout 4) or on one wall (layout 5).
  - §6 S4: every S-W pool scene in layout 4 has a listener or emitter 0.1 m from a face.
  - §4 cue 5: the early/late split.
  - §2 criterion 5: the stimulus label must match the render.

**2. Ranking** (none veto-grade)
1. **V3, prefer, only with layout5_s1/default.** I would not take emitter_wall.
2. **V4, can live with.**
3. **V1, can live with.**
4. **V2, can live with, only under the condition in §6.**

**3. Tension now**
- **V3, default: 1.**
  - The early part is empty (AX21), as on S-A.
  - It uses the default placements, has a tail share of 0.579, and a heard D/R of −1.4 dB.
  - Its per-emitter D/R of −3.8 / −4.8 dB is about 9–10 dB above the diffuse-field value: r = 12.37 m, A ≈ 319–370 m², r_c ≈ 2.5–2.7 m, D/R about −13.2 to −13.8 dB [Inferred, Kuttruff Eq. 5.44 via file 31]. S-A is about 21 dB above (file 31). V3 halves the dryness shortfall.
- **V3, emitter_wall: 2.** Same reason as V2.
- **V2: 2.**
  - Whatever S-W picks in layout 4 (both_wall 0.667 once K5 is cleared, or listener_corner 0.256) puts a position 0.1 m from a face at s = 1.
  - In the render, the wall reflection is zeroed by (1−α)(1−s) = 0 (Kuttruff Eq. 8.59 via file 26).
  - A real wall at that distance gives a reflection about 0.6 ms after the direct sound and comb notches from about 860 Hz up [Inferred]. That is a tone-colour departure, my largest perceptual weight (2019 regression, β 0.29).
  - So the stimulus has two departures from the room class, not one.
- **V1: 1.**
  - S-A carries its known AX21 deficit.
  - S-B\* meets my file-26 conditions: it is capped at m = 6, 7 and 8, its specular share is 0.032 or less (the limit was 0.40), and it is clean on item 6. It still needs the jump printed and the label (§6).
- **V4: 1.** This is my file-26 position (S-A with its label and the B11 trigger), plus a guaranteed S-B\*.

**4. Tension later**
- **V1: 1.**
  - At 08-3, S-W is rendered binaurally at a near-face position, where the missing wall reflection becomes part of what Seat 4 judges.
  - Undo: rerun one scene, about 2 h (K6).
- **V2: 1.**
  - S-B\* at 08-3 adds a second class.
  - Undo: rerun.
  - Evidence: 08-3.
- **V3: 1.**
  - AX47's Reversal changes to "layout-4 or layout-5" (one /fix-plan; undo is the same).
  - Layout 5 breaks T-a's premise: heard T30 is 2.557 s against a tail T30 of 2.58–2.62 s (K4 fact 9, file 34). The gap must come from max(heard, tail) T30, and Q5 must be rerun. Cost: minutes plus a reseal.
  - Stimuli get about 20 % longer [Inferred, from K6's formula].
  - The layout 5 tail sits at Eyring (2.608 s), so it is an Eyring-trap check (researcher item below).
- **V4: 1.**
  - The only 07c-2 verdict rests on the most extreme AX21 scene.
  - Undo: rerun.
  - Evidence: 08-3's S-B\*.

**Seat-specific answers**
- **Layout 5's provenance.**
  - It is Kuttruff Table 5.2 layout 5 (absorbing xMin wall), built like layout 4 (test_diffuse_records.cpp L1398–1399).
  - It is already in AX47's own A4 assertion set (test_interim.cpp L83, L107) and in AX43's reported set (05b2 file 24).
  - Its provenance therefore equals layout 4's. "Layout-4" in the Reversal is file 13's pre-registration choice, not an engine limit.
- **The AX21 jump at s = 0.7 and 0.9.** All figures are [Inferred], by AX21's method:
  - t_mix,e is 380 ms (the AX22 fallback). The mean free path is 4V/S = 10.9 m, so n̄ ≈ 12 hits.
  - The upper-estimate jump, −10·n̄·log10(1−s), is about 63 dB at s = 0.7 and about 120 dB at s = 0.9. In other words, the specular field is gone well before t_mix,e.
  - The early part decays at about −5.2 or −10 dB per hit, giving an effective T60 of about 0.36 s or 0.19 s, against a heard T30 of 1.83 or 1.93 s. So the stimulus has a short early part, then a dip, then the tail onset.
  - **I pick s = 0.7.** Its early part is 5.7 dB stronger (−3.8 against −9.5 dB re direct), it is the less extreme case of AX21, and it differs most from S-A (|ΔC80| 0.52 against 0.86).
  - At s = 0.9 the stimulus is close to S-A.
- **Trigger wording.** I accept it if it is widened to: "On any `src/sim` change that alters a sealed scene's rendered IR (B11 promotion, the t_mix,e rule, estimator constants), the stimuli are rebuilt and their hashes re-registered before the next listening session. Earlier results stand, each recorded with the engine it was obtained on."
  - Reason: the 08-3 rerun comes after this phase's own W_max raise (O4).
  - An empty early part leaves the tail less masked, so a result on the AX21 engine points the conservative way [Hyp, Seat 1].
- **File 34 item 1's clause.** Under every option, replace the scene-name tag with the physical condition: "[every ABX scene with s = 1 on all faces: E_spec = 0 in every band (AX21; Kuttruff Eq. 8.59)]". Then:
  - **V2 and V3:** that is all, since every candidate is s = 1 (K4 gives a share of 0.000).
  - **V1, and 08-3 under V2 and V4:** extend it with "On layout4_s0.7 the share is up to 0.032, so scaling E_b alone would give 0.87 dB, not 0.9. Item 6's identity is asserted there, and this is where M1's reversal condition can bite." Arithmetic: 0.032 + 1.230 × 0.968 = 1.223, which is 0.873 dB.
  - Do not drop the clause outright.

**5. Evidence**
- From the code: test_interim.cpp L83–107; test_diffuse_wsweep.cpp L75–107.
- Files: K4 table (file 29); K5 and K6 (file 32); file 34 item 3; AX21 and AX47 (BUILD_PLAN L144, L170).
- Kuttruff Eqs. 5.44 and 8.59: corpus not present, cited through files 26, 28 and 31.
- Researcher: Kuttruff Table 5.2 layout 5. Do its iteration and Eyring T60 differ, the way layout 4's do (1.21 against 1.38 s)?

**6. Conditions of acceptance**
- **V2 (2 → 1):** the label states "position 0.1 m from a face, its wall reflection absent at s = 1, tone colour of the direct sound not room-like", and the non-detection is scoped to that class (item 13).
- **V3 (default only):** the S-W rule gets a default-placement filter. Without it, S-W picks both_wall (0.667) or emitter_wall (0.869) over default (0.579), and V3 collapses into V2.
- **Any S-B\*:**
  - the measured dip per band and per emitter is printed: energy over [t_mix,e − 20 ms, t_mix,e − 2.5 ms) against [t_mix,e + 2.5 ms, t_mix,e + 20 ms);
  - it is labelled "partial-AX21, specular-only early part".

**7. Hand-offs**
- Split or unsplit α, and the sensitivity of s = 0.7: Seat 1, Seat 5.
- Whether the dip before the tail onset adds a temporal cue: Seat 1, Seat 3.
- Near-face positions in binaural: Seat 4.
- Hours: Seat 7.
- Label: Seat 9.
- The far emitter's direct burst runs through the fade on both_wall: Seat 3.

**8. Premortem.** If V2 seals both_wall, a non-detection is set on a corner case the engine renders least like a room. When a near-face placement is heard binaurally at 08-3, its missing wall reflection would be noticed before anything else, by Seat 4 or Maisara.
