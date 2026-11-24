# 1: Seat 9 (room acoustician), M3: s = 0.7 / 0.9, layout-5 provenance, S-W label, the 0.43 ceiling, item-9 labels

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE"). Run 2026-11-24 in the
phase-07c-2b session as `seat9-room-acoustician`. Recorded verbatim from the seat's answer.

SEAT 9 POSITION

Corpus not present (`docs/corpus/` is empty in this checkout). Kuttruff Eq. 5.44 and §5.6 are cited as files 26 and 31 cited them against corpus c1b171fe. The new arithmetic below is mine and is tagged.

**1. Reading.** M3 picks the ABX scene or scenes for V1–V4. My brief has four parts: is s = 0.7 or s = 0.9 representative; where layout 5 comes from; a label for S-W; the corrected 0.43 ceiling on each option. I also give item-9 labels for every candidate. Cues from my §4 that this triggers:
- D/R at the seat against the diffuse field.
- Early structure and ITDG.
- Provenance (S8).
- "Decay right, room wrong" (W2).
- A late change after commitment (W1): class (c) admitted before the s < 1 evidence arrives.

**2. Ranking**
- **V1** (S-A plus S-B\* at s = 0.7 in 07c-2; S-A and S-W binaural at 08-3): *prefer*.
- **V2** (S-W now; S-W and S-B\* at 08-3): *can live with*.
- **V4** (S-A now; S-A and S-B\* at 08-3): *can live with*.
- **V3** (V2 plus layout 5 in the pool): *can live with*.

V2 ranks above V4 because S-W is the most exposed corner of the scene space, so a non-detection there bounds more of NFR-8's "any valid scene" than S-A does. S-A is the least exposed corner.

**3. Tension now**

| option | now | why |
|---|---|---|
| V1 | 1 | Neither scene is validated. S-B\* at 0.7 is the least unrepresentative candidate there is (below). |
| V2 | 1 | S-W at 0.1 m from a wall is not a seat, and its early part is empty. Its labelled exposure (heard D/R −5.3 dB, tail share 0.667) is honest. |
| V3 | 1 | Same reasons as V2. |
| V4 | 1 | My file-26 conditions for S-A are met: item 13 names the class, and 08-3 is not run on S-A alone. |

**4. Tension later (the debt)**

| option | later | what it commits |
|---|---|---|
| V1 | 1 | Under B11 promotion, the s < 1 stimuli are rebuilt (Seat 2's trigger). The cost is minutes to a reseal. |
| V2 | 2 | O10 (class (c) admission) would be read from an empty-early-part scene only. If S-B\* detects 0.9 dB at 08-3, AX47 drops to 0.5 dB after sources were admitted at 1 dB. Undoing that means re-admission at SE ≤ 0.25 dB, a second W raise and a second golden round, i.e. a phase of rework. The evidence arrives at 08-3. |
| V4 | 2 | Same debt as V2. This is my file-26 premortem. |
| V3 | 2 | The V2 debt, plus the M2 premise failing: heard T30 2.557 s sits below the tail-alone T30 of 2.58–2.62 s (K4 fact 9), so the gap rule has to be re-decided. |

**5. Evidence and answers**

**(a) s = 0.7 or 0.9: pick s = 0.7.**
- Neither represents a measured room. Under AX21 the rendered early part is specular only, (1−s) per hit. So the measure that matters is what is rendered at the seat, not s itself.
- Diffuse-field expectation for the layout-4 default seat is −10.8 dB per emitter (r/r_c 3.47; file 31; Kuttruff Eq. 5.44).

| scene | D/R per emitter | gap to −10.8 dB | early part, broadband re direct | gap to an honest early part (≈ +3 dB) |
|---|---|---|---|---|
| s = 0.7 | +1.5 / +1.3 dB | ≈ 12 dB | −3.8 dB | ≈ 7 dB |
| s = 0.9 | +6.0 / +5.6 dB | ≈ 17 dB | −9.5 dB | ≈ 13 dB |
| S-A | +10.7 / +9.7 dB | ≈ 21 dB | empty | — |

- The ≈ +3 dB honest early part is [Inf; M]: first-order images alone (ceiling, side walls) at −4.4 to −8.3 dB spherical, and +2.7 dB at s = 0.25 (K4).
- s = 0.9 is nearly S-A again, so it adds no real second class. s = 0.7 is the lowest s that is capped at m = 6, 7 and 8 (K4 fact 1).
- Its ITDG is 23.6 ms (ceiling image at 59.7 ms absolute against direct at 36 ms). The first lateral (x = 0 side wall) follows at 24.6 ms [Inf; H; geometry].
- Uniform s = 0.7 on every face is at the high end for real surfaces. Real s also rises with frequency, and this scene has one value across bands [Hyp; researcher].
- On the other side: ΔC80 is 0.519 dB at s = 0.7 against 0.860 dB at s = 0.9. ΔG is 0.032 against 0.040 dB, so the two are equal within a hundredth of a dB. Sensitivity is Seat 1's to weigh.

**(b) Layout-5 provenance.** Same pedigree as layout 4 (from the code: `test_diffuse_wsweep.cpp` L72–107, the AX43 reported set). It is a synthetic stress layout: one face at α 1 (here the x = 0 wall, 300 m²), the others at α 0.01, s = 1 everywhere. It is no worse than layout 4 as an AX47 scene, and no better. Neither is a measured room.
- With one absorbing side wall the field is non-diffuse, so I expect the physical decay to be shorter than Eyring's 2.61 s. The engine's tail follows Eyring [Inf; M, by analogy with Kuttruff Table 5.2 case 4, −12 % on layout 4].
- Sabine A ≈ 300 + 19 + 24 (air) ≈ 343 m², so r_c ≈ 2.61 m [Inf; H].
  - default: r/r_c 4.74, expectation −13.5 dB; measured −3.8 / −4.8 dB.
  - emitter_wall: S0 at 22.1 m, r/r_c 8.46, expectation −18.5 dB; measured −12.4 / −5.0 dB.
  - emitter_wall is the candidate closest to the diffuse field, 6–9 dB off.
- A-basis note: file 31's 640 m² is Sabine plus air. Eyring's A (≈ 747 m²) gives r/r_c 3.21 and −10.1 dB. The label should name its basis; the two differ by 0.7 dB.

**(c) S-W pick and label.**
- Under V2 (layout 4), S-W is both_wall (share 0.667), provided the robust `click_check` (Seat 3/5's call) clears K5's false positives. Otherwise it is listener_edge (0.208), not listener_corner, which has the same K5 issue.
- Under V3 it is layout5 emitter_wall (0.869).
- In both_wall the listener and one source each sit 0.1 m from a wall. With s = 1 the engine does not render that wall's own reflection, so there is no boundary gain and no comb (first null at about 860 Hz in a real room) [Inf; H]. It is not a seat.

**(d) The 0.43 ceiling (corrected premise).**
- Formula: t ≤ hold + (46 − 20 − L_drop)/60 · T60_tail, with L_drop = 10·log10(1 + 10^(D/R/10)). D/R is heard at 1 kHz.
- Inputs: hold 0.1 s and SNR 46 dB carried over from S-A's speech pair [Hyp]. T60_tail 1.30 s for layout 4 (assumed equal at s < 1 [Inf]) and 2.61 s for layout 5.

| scene | L_drop | bound | 0.43·T30 | binds? |
|---|---|---|---|---|
| S-A | 13.3 dB | 0.375 s (measured) | 0.864 s | no |
| s = 0.7 | 3.9 dB | 0.58 s | 0.79 s | no |
| s = 0.9 | 7.5 dB | 0.50 s | 0.83 s | no |
| L4 both_wall | 1.1 dB | 0.64 s | 0.59 s | yes, by 50 ms |
| L4 listener_corner | 2.3 dB | 0.61 s | 0.55 s | yes |
| L5 default | 2.4 dB | 1.13 s | 1.10 s | yes |
| L5 emitter_wall | 0.5 dB | 1.21 s | 1.10 s | yes |

- For s < 1 the bound is an upper estimate: early specular images stop sooner than the tail decays.
- Where the ceiling binds it is doing its pre-registered job, so it is harmless. I keep it at **1/1 on every option**.

**6. Conditions of acceptance**
- **V2, V4 (2 later → 1):** the S-B\* (s = 0.7) family runs and is read before O10 admits any source. Otherwise, O10's record names its admission "empty-early-part class only", with an 08-3 S-B\* detection written in as a reversal trigger, and its undo cost named. That alone leaves the rating at 2.
- **V3 (→ 1):** the V2 condition, plus:
  - the layout-5 gaps set to ≥ max(heard, tail) T30;
  - the M2 gap check passing;
  - the label stating the 0.1 m boundary is not rendered.
- **All options:** the manifest prints ITDG, early-re-direct, per-emitter D/R against expectation, heard and tail T30. Every stimulus is labelled "stimulus scene, not a room prediction".

**Proposed item-9 labels** (short label; detail line in the manifest)

- **S-A, layout4_s1/default.** Label: "Direct-dominated test room, early reflections absent (AX21); not a validated preset." Detail:
  - 20 × 30 × 10 m; floor α 1, other faces 0.01; s = 1 on every face; sources 12.4 m away, r/r_c 3.47.
  - D/R +10.7 / +9.7 dB (heard +13.1) against −10.8 dB diffuse expectation (Kuttruff Eq. 5.44, Sabine A ≈ 640 m²).
  - Early part −77 dB re direct.
  - Heard T30 2.009 s ("heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate"); tail T30 1.25–1.27 s; Eyring target 1.29 s.
  - Class: "direct-dominated, early part empty".
- **S-B\*, layout4_s0.7/default.** Label: "Shoebox test room, specular early reflections only (scattered early energy absent, AX21); not a validated preset." Detail:
  - Geometry as S-A; s = 0.7 on every face, one value for all bands.
  - ITDG 23.6 ms (ceiling); early part −3.8 dB re direct.
  - D/R +1.5 / +1.3 dB (heard +1.7) against −10.8 dB.
  - Heard T30 1.831 s; tail T30 printed.
  - Class: "near-balanced D/R, partial early part".
  - If s = 0.9 is chosen instead: early −9.5 dB, D/R +6.0 / +5.6 dB (heard +6.6), T30 1.925 s.
- **S-W, layout4_s1/both_wall.** Label: "Reverberant-dominated stress placement, listener 0.1 m from a wall; early reflections absent (AX21); not a seat, not a validated preset." Detail:
  - Listener (10, 0.1, 1.7); S0 29.9 m away and 0.1 m from the opposite wall; S1 20.1 m away.
  - D/R −7.7 / +5.2 dB against −18.5 / −15.0 dB expected.
  - Tail share 0.667 at 1 kHz.
  - The wall's own reflection is not rendered (s = 1).
  - Heard T30 1.370 s.
  - Class: "tail-dominated, early part empty".
- **layout5_s1/default.** Label: "Test room with one absorbing side wall, early reflections absent (AX21); not a validated preset." Detail:
  - x = 0 wall α 1, others 0.01; s = 1; Eyring target 2.61 s (non-diffuse; physical decay expected shorter).
  - r/r_c 4.74; D/R −3.8 / −4.8 dB against −13.5 dB.
  - Heard T30 2.557 s, below tail-alone T30 2.58–2.62 s.
- **layout5_s1/emitter_wall.** Label: as layout5_s1/default, with "source 0.1 m from a wall" added. Detail: as layout5_s1/default, but D/R −12.4 / −5.0 dB against −18.5 / −13.5 dB, and the boundary reflection is not rendered.

**7. Hand-offs**
- Seat 1: S-W choice, split α, and whether s = 0.7's ΔC80 of 0.519 dB is worth a family.
- Seat 2: t_mix,e at s = 0.7; the B11 rebuild trigger; the layout-5 Eyring tail against the physical decay.
- Seat 3 and Seat 5: the robust `click_check` that decides both_wall's eligibility.
- Seat 4: 0.1 m placements in binaural.
- Seat 7: hours for two families.
- Researcher: measured scattering coefficients for typical hall surfaces (ISO 17497-1 data), and the band basis of the 46 dB SNR.

**8. Premortem.** Under V2 or V4, class (c) is admitted at 1 dB on an empty-early-part scene. S-B\* then detects 0.9 dB at 08-3, forcing a second W raise and golden round after the Phase 08 work is built on the first. The builder, or Maisara reading the 08-3 result, sees it first.

Files: docs/review/phase-07c-2/29-k4-candidates.md, 31-decider-abx-r4.md, 26-seat9.md, 34-decider-m1-m2-final.md, 40-decider-2a-2b-final.md, 32-k5-k6-clicks-session.md; tests/unit/test_diffuse_wsweep.cpp (L72–107); docs/validation/abx-07c-2-run-sheet.md (§1); docs/BUILD_PLAN.md (AX21 L144, AX47 L170).
