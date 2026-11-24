# 1-seat9: Seat 9 (room acoustician) on M3, V1–V4 and item-9 labels (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION

The corpus is not in this checkout (`docs/corpus/` is missing), so every acoustic claim below comes from my register or from the citations already on record in files 26, 28 and 41. Those claims are flagged.

**1. Reading.** M3 picks the scene or scenes for the AX47 self-ABX (07c-2b) and the 08-3 binaural rerun. My questions are which of V1–V4 sits nearest a listener at a real seat, what each scene's label must say, and where the 0.43 ceiling binds.
Cues it triggers:
- **W2 (RT right, room wrong):** every s = 1 scene has no early part.
- **S4 / W3:** a reflection under 5 ms is missing at the 0.1 m placements.
- **S2:** layout 5 puts all its absorption on one wall.
- **Late change after commitment:** AX47 is decided on one class and later evidence could reverse it after the W_max pin.

**2. Ranking**
- **V1 with S-B\* = layout4_s0.7: *prefer*.** It is the only option that puts an early part into the decision AX47 actually rests on (07c-2).
- **V3, restricted to layout5_s1/default: *can live with*.** This variant is my addition. Under the S-W rule as written, layout5 emitter_wall (share 0.869) wins and gets V2's rating.
- **V4: *can live with*.**
- **V2: *can live with*.** It is the lowest of the four.
- No option is *cannot live with*.

**3–4. Tension now / later**

| option | now | later | why |
|---|---|---|---|
| V1 | 1 | 1 | **Now:** 07c-2 gets two classes, and S-B\* has an early part (−3.8 dB re direct) with a first image about 24 ms after the direct sound. **Later:** both 08-3 scenes are s = 1 with no early part, and B11 makes them stale. Undo: rebuild the stimuli. |
| V2 | 2 | 1 | **Now:** AX47 rests on a wall placement (both_wall, with the listener 0.1 m from a face) whose sub-millisecond wall reflection AX21 deletes. That is no seat in any room. **Later:** 08-3 guarantees S-B\*. |
| V3 (layout5 default) | 1 | 1 | **Now:** default placement, per-emitter D/R −3.8 / −4.8 dB against a diffuse −13.5 dB. That is the s = 1 scene nearest the diffuse field. **But:** T60 2.6 s with all absorption on one wall is not a room prediction (S2). It also fails the M2 gap check (below). **Undo:** a /fix-plan, minutes. |
| V3 (emitter_wall, as the rule picks) | 2 | 1 | The 0.1 m emitter fault, as in V2. |
| V4 | 1 | 2 | **Now:** S-A under the class-scoped label meets my file-26 conditions. **Later:** the class-(c) admission, the W_max pin and the golden round all happen on direct-dominated evidence only. If S-B\* detects at 08-3, AX47 reverses to 0.5 dB after the pin, which costs a re-pin and a second golden round (about a phase of rework). |

**Brief questions**
- **s = 0.7 or 0.9?** Neither is representative of a measured room. Uniform s on all faces is not a hall surface set: real hall walls are mostly much lower, audience areas higher [Hyp; researcher, Vorländer/ISO 17497 tables].
  - On my measures, **0.7** is less unrepresentative. Heard D/R is +1.7 dB against −10.8 dB diffuse (12.5 dB off); at 0.9 it is +6.6 dB (17.4 dB off). The early part is −3.8 dB re direct, against −9.5 dB at 0.9 (K4).
  - The sensitivity cost is Seat 1's: |ΔC80| is 0.52 dB at 0.7 against 0.86 dB at 0.9.
- **Layout-5 provenance.** Layout 5 comes from the same synthetic AX43 family as layout 4 (`test_diffuse_wsweep.cpp` L72–83). Neither is measured, so neither has better provenance. The "layout-4 only" restriction in AX47 protects nothing on my criteria.
- **S-W.** Among the scenes that qualify, I pick layout5_s1/default (V3) over any 0.1 m placement. In V1, S-W is in practice both_wall (0.667, since K5 found its event a false positive). listener_corner fails the M2 gap check (heard T30 1.288 s against a tail T30 of about 1.27–1.30 s).
- **The 0.43 ceiling, corrected bound** (hold 0.1 s, SNR 46 dB [Hyp], T60_tail 1.30 s for layout 4 and 2.60 s for layout 5) [Inf; M]:
  - S-A: 0.375 s against a ceiling of 0.864 s. Not binding.
  - s0.7: L_drop 3.9 dB gives 0.58 s against 0.787 s. Not binding.
  - s0.9: L_drop 7.5 dB gives 0.50 s against 0.828 s. Not binding.
  - both_wall: L_drop 1.1 dB gives 0.64 s against 0.589 s. Binds.
  - layout5 default: L_drop 2.4 dB gives 1.12 s against 1.10 s. Binds.
  - layout5 emitter_wall: L_drop 0.5 dB gives 1.21 s against 1.10 s. Binds.
  - Rating: 1/1 on every option, as before.

**5. Evidence**
- D/R, ΔC80, early energy and T30 come from K4 (file 29), as code facts.
- r_c = √(A/16π) (Kuttruff Eq. 5.44, via file 28): A ≈ 640 m² gives r_c 3.57 m. Layout 5 has A ≈ 300 + 19 + about 24 (air) = 343 m², so r_c is 2.61 m [Inf].
- Eq. 5.43 is unreliable at ᾱ ≈ 0.28 (file 41). The diffuse D/R figures are therefore indicative only.
- **M2 gap check on layout 5:** the heard T30 (2.557 s) is below the tail-alone T30 (2.58–2.62 s) (K4 fact 9). With gaps set at about ceil(heard T30) (K6), the assertion gap ≥ tail T30 fails by about 20–60 ms [Inf; H].
- K5's both_wall event: the far emitter's direct burst plays 29.3 ms into the fade (file 32).

**6. Conditions of acceptance**
- **V2, to 1/1:** S-W excludes the 0.1 m listener placements, or the label states "no seat represented".
- **V3:** restrict it to layout5 default. Set its gaps from max(heard, tail) T30 so that the M2 check passes. This keeps 1/1.
- **V4, later 2 → 1:** the class-(c) round and the W_max pin wait for 08-3's S-B\* result, or the record states that a detection on S-B\* re-opens them.

**Item-9 labels** (shared prefix: "20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01")
- **S-A:** file 27's text, with "−10 dB at r/r_c 3.2" replaced by "−10.8 dB in a diffuse field at r/r_c 3.47 (Kuttruff Eq. 5.44, A ≈ 640 m²)".
- **layout4_s0.7:** "…floor α 1, scattering 0.7 on every face. D/R at 1 kHz +1.5 / +1.3 dB per emitter, +1.7 dB heard, against −10.8 dB in a diffuse field at r/r_c 3.47 (A ≈ 640 m²). Early part present: first image (ceiling) 23.6 ms after the direct sound; broadband early energy −3.8 dB re direct. Tail target Eyring 1.29 s at 1 kHz, a diffuse target, not a room prediction; heard-IR T30 1.831 s spans early and tail. Not a validated preset."
- **both_wall:** "…floor α 1, scattering 1. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall; those wall reflections are absent under AX21, so the scene represents no seat. D/R −7.7 / +5.2 dB per emitter (diffuse −18.5 / −15.0 dB at r/r_c 8.4 / 5.6), −5.3 dB heard. Early part empty (AX21). Heard-IR T30 1.370 s. Not a validated preset."
- **layout5 default:** "…xMin wall α 1 (300 m²), all other faces α 0.01, scattering 1. Absorption on one wall: non-diffuse; Eyring 2.61 s at 1 kHz is a target, not a prediction. D/R −3.8 / −4.8 dB per emitter, −1.4 dB heard, against −13.5 dB diffuse at r/r_c 4.74 (A ≈ 343 m²). Early part empty (AX21). Heard-IR T30 2.557 s, tail-alone 2.58–2.62 s. Not a validated preset."

**7. Hand-offs**
- **Seat 1:** whether S-B\* is worth a family, the split, and the sensitivity at 0.7 versus 0.9.
- **Seat 3:** the far-emitter direct burst inside the fade on both_wall.
- **Seat 4:** layout 5's one-sided absorption in binaural.
- **Researcher:** measured scattering coefficients for hall surfaces, and the band basis of the 46 dB SNR.

**8. Premortem.** Under V4 or V2, AX47 is admitted on a scene with no early part or no real seat. At 08-3 the s = 0.7 scene then detects 0.9 dB after W_max and the goldens are pinned, and Maisara hears the step first on her checklist.

Files:
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- /home/user/makroof/docs/review/phase-07c-2/31-decider-abx-r4.md
- /home/user/makroof/tests/unit/test_diffuse_wsweep.cpp
- /home/user/makroof/docs/phases/phase-07c-2b.md
