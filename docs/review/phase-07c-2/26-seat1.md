<!-- Saved by the orchestrator from seat 1's report, 2026-11-22. -->

SEAT 1 POSITION

**1. Reading.** The question is whether a 0.9/0.5 dB tail step on `layout4_s1/default` still tests AX47's "all scenes" bound, and which T30 Q5 uses. The scene's heard D/R is +13.1 dB and nothing arrives between the direct sound and t_mix,e = 0.380 s. Cues triggered:
- "A threshold quoted without its method": the decision rule turns a null result into a looser bound for every scene.
- "Find the signal or condition that breaks it" (B2).
- "Borrowed vocabulary": the "mid-size hall" label.

The decider's premise needs splitting. The dry scene does not bias every cue toward non-detection. The emptiness makes one cue as strong as it can be and another nearly as weak as it can be.

**2. Ranking.**
- M2: **T-a** prefer. **T-b** can live with.
- M3: **S-D (my variant below)** prefer. **S-C** can live with. **S-A** can live with, if the conditions below are met. **S-B** can live with only if K3 shows it is no less sensitive than S-A; otherwise it ranks last.
- **S-D (added by me):** a pre-stated rule picks the s = 1 candidate that is capped at m = 6–8 and has the largest tail-window share of the heard 1 kHz energy. Candidates are the `test_diffuse_wsweep` placements of layouts 4 and 5. The builder measures them with the file 22 method (K3), and the choice is committed before sealing and before anyone listens. If nothing beats `listener_wall`, S-D becomes S-C.

**3. Tension now.**
- **T-a: 0.** The gap of 2.009 s is longer than the tail's own decay, so the tail fades out completely in every gap. The onset window is the same under both options.
- **T-b: 1.** Every realisation changes for no gain to detection.
- **S-A: 2.** The tail-level cue during programme is close to its weakest (arithmetic in §5).
- **S-B: 2.** Rendered early energy is never stepped, so it lowers both the G and the C80 cue. A more plausible room is not a criterion for a detection test.
- **S-C: 1.** About 4 dB wetter [Inferred], and s = 1 keeps the specular share at 0.
- **S-D: 1.** Costs builder minutes, and the selection rule must be logged before listening.

**4. Tension later.**
- **T-a: 1.** On a scene with an AX21 gap, the heard-IR T30 is an artefact of the decay fit (file 22: the whole-IR EDT runs from 0.001 to 141 s). Another scene could give an unstable value. Evidence would come from K3 or the 08-3 binaural rerun.
- **T-b: 1.**
- **S-A: 2.** A null result keeps 1 dB for every scene, including late-dominated scenes where the same step moves the programme level about 10 times more. Item 15 would carry the same bias into 08-3. Undoing it means reseal, rerun and re-record, plus a listener session. Evidence that could overturn it: the first wet-scene complaint, or the 08-3 rerun.
- **S-B: 2.** On top of the sensitivity loss, Seat 3's specular-share refusal may block it.
- **S-C: 1.**
- **S-D: 0–1.**

**5. Evidence.**
- **Two cues, pulling opposite ways** [Inferred; Vorländer Table 6.1 and Eqs. 6.4–6.7, cited in AX47; file 22 energy budget]:
  - **C80 cue.** Between 80 ms and t_mix the IR holds only about 1.8e−7, which is −29 dB re direct. So C80's late energy is almost all tail, and C80 moves by the full g: 0.9 dB, against a 1 dB jnd. On this cue the scene is at the sensitive extreme. Caveat: C80's jnd was measured in halls with the method not stated, and my register has about 3 dB under live switching.
  - **G cue.** I redid the arithmetic. At heard D/R +13.1 dB, the tail is 0.049 of the direct energy. A 0.9 dB step (k = 1.2303) changes the total by 10·log10((1 + 0.049k)/1.049) = 0.046 dB. Per emitter (+10.4 dB) the change is 0.083 dB. At a tail-dominated D/R of −3 dB it would be about 0.62 dB. Against the 1 dB level jnd, this scene is near the weakest end for programme-level cues.
- **Gap cue** [Hyp]. In the noise gaps the tail plays alone and shifts by the full g in every scene. Post-masking from the ending burst is real (Vorländer §6.2.2), but the corpus gives no time constant for it. That is for the researcher.
- **Most of the dryness is the early part, not the tail.** In diffuse theory a tail starting at 0.380 s sits at about +7.5 dB re direct. The measured value is +9.5 to +10.4 dB (file 22; Kuttruff Eqs. 5.43–5.45). The late t_mix,e drives the bias more than the label does: ismFallback gave 0.380 s where AX20 expects 0.114 s.
- **Item 13 does not admit this.** Its stated power (0.63 / 0.41 at p = 0.75) assumes a p that is not tied to any scene. On the programme cue, p for this scene is plausibly lower [Hyp].

**6. Conditions of acceptance.**
- **S-A, to 1:**
  - The record and manifest print, per band, the tail-window share of the heard energy and the implied ΔG and ΔC80 at each g.
  - A null result is worded "not detected … on a scene with tail share X dB".
  - The 08-3 rerun (item 15) uses the S-D scene.
- **S-B, to 1:** only if K3 shows ΔG and ΔC80 at or above S-A's, and Seat 3 confirms the kit does not refuse it.
- **S-C, to 0:** K3 confirms it is capped at m = 6–8 and wetter than S-A.

**7. Hand-offs.**
- Seat 2: does ismFallback (t_mix,e 0.380 s against 0.114 s) push the start of the tail later in every capped s = 1 scene? If B11 is ever promoted, would early scattered energy fall inside the stepped E_b?
- Seat 3: under S-B, does a specular share above 0 make the kit refuse? And the 8 kHz +18 %.
- Seat 9: the label.
- Seat 4: whether the scene suits the 08-3 binaural rerun.
- Researcher: level-discrimination thresholds for a decaying noise tail just after a masker ends.

**8. Premortem.** If S-A is sealed and the listener does not detect the step, AX47 keeps 1 dB for late-dominated scenes on evidence from a scene where the step moved the programme level 0.05 dB. The first to notice is a mixer automating a far-listener preset, who hears the reverb settle in a jump.

Files read: /home/user/makroof/docs/review/phase-07c-2/24-decider-abx-r2-convene.md, /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md, /home/user/makroof/docs/review/phase-07c-2/21-decider-abx-kit.md, /home/user/makroof/docs/review/phase-07c-2/22-drr-t30-check.md, /home/user/makroof/docs/review/phase-07c-2/23-interrogator-on-file21.md, /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md, /home/user/makroof/docs/BUILD_PLAN.md (AX21 line 143, AX47 line 169, B11 line 403), /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1, §6.2.2), /home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (listener_wall at (10, 0.1, 1.7), lines 88–100).
