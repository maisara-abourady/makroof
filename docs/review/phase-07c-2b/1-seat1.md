# 1-seat1: Seat 1 (perceptual gatekeeper) on M3, V1–V4, α, speech material, AX49 L4 (phase-07c-2b, round 1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION

**1. Reading.** M3 asks which scene or scenes the AX47 self-ABX decides on (V1 to V4), how α is treated across scene families, what speech material is fixed, and where the AX49 L4 ABX sits. Cues it triggers:
- **Hardest signal (B2, W4).** The scenes differ by about 14× in ΔG.
- **Threshold quoted without its method.** A null result on a scene with ΔG 0.045 dB would be recorded against a 1 dB jnd.
- **Pre-registration before anyone listens (O1, W1).**

What changed since file 26:
- K4 measured a qualifying wet layout-4 scene.
- K5 cleared both click events as detector false positives.
- File 34 made the gap ≥ tail-T30 check a seal gate, and it fails on layout 5.

**2. Ranking.**
- **V2: prefer.**
- **V3: can live with.** Its layout-5 additions fail the M2 gap check as decided (file 34 item 3: heard T30 2.557–2.575 s against tail 2.58–2.62 s). So the S-W rule still picks a layout-4 scene, and V3 equals V2 plus a /fix-plan.
- **V1: can live with, only under the conditions below.**
- **V4: cannot live with.**

**My S-W pick.** The S-W rule picks **layout4_s1/both_wall** (tail share 0.667; ΔG 0.621 dB at 1 kHz and 0.471 broadband; ΔC80 −0.900), on two conditions:
- `click_check` is made robust, which is already a pre-seal item in 07c-2b scope 2.
- both_wall passes the robust check.

Otherwise the rule falls to **layout4_s1/listener_edge** (share 0.208, ΔG 0.204 dB, item 6 passes, heard T30 1.752 s). listener_corner (0.256) would rank above it if it re-enters, but its T-a margin is about 18 ms (heard T30 1.288 s against a tail T30 of about 1.27 s). Once the robust check exists, the rule is rerun over the whole layout-4 pool and committed before any listening.

**3. Tension now.**
- **V2: 0 on both_wall, 1 on the listener_edge fallback.** Gives the most sensitive scene that qualifies.
- **V3: 1.** Nothing gained over V2. The only extra gain would be layout5_s1/emitter_wall (ΔG 0.79 against 0.62 dB), and that scene fails the gap check.
- **V1: 2.** The 07c-2 result, which feeds class (c) and W_max now, rests on the two least sensitive scenes: S-A (ΔG 0.045 dB) and S-B\* (0.032–0.040 dB).
- **V4: 2.** The same, with one family.

**4. Tension later.**
- **V2: 1.** S-W is ranked as most sensitive on ΔG and ΔC80 only; no listener has confirmed that. Evidence arrives at the 08-3 binaural rerun. If Seat 4 rejects the 0.1 m placements, 08-3 (i) changes scene: a reseal, a matter of hours.
- **V3: 1.** Same as V2.
- **V1: 2.** S-W first meets a listener at 08-3, after O10, the W_max pin and the golden round. A detection there sets 0.5 dB (SE ≤ 0.25 dB). Undoing that means a class (c) re-decision, a W_max re-derivation and another golden round: about a phase of rework.
- **V4: 3.**
  - No phase ever tests a measured, qualifying scene whose programme-level step is about 14× S-A's.
  - The all-scene bound would meet only the scenes most likely to hide the step. That trades the hardest condition for the easiest one, which my §2 never trades.
  - File 26 rated S-A alone 2/2 because the wet alternative was then unmeasured. K4 and K5 have now measured it and cleared it.

**5. Evidence.**
- **ΔG ≈ 10·log10(1 + share·(a² − 1)), with a² = 1.2303 at g = 0.9 dB** (K4 fact 5; arithmetic redone):
  - both_wall: 0.620 dB.
  - listener_edge: 0.203 dB.
  - S-A: 0.046 dB.
  - s = 0.9: 0.040 dB.
  - s = 0.7: 0.032 dB.
- **ΔC80** is −0.900 dB on every layout-4 s = 1 scene, 0.86 dB at s = 0.9 and 0.52 dB at s = 0.7 (file 29). The jnd for G and C80 is 1 dB (Vorländer Table 6.1; paradigm not stated, medium confidence).
- **The gap cue** is the same g in every scene [Hyp, unchanged from file 26; still with the researcher]. On S-A, though, the gap tail starts about 13 dB below the burst, so forward masking is greater there [Inferred].
- **T-a premise on both_wall:**
  - The gap is at least the heard T30 of 1.370 s. That is 1.341 s as heard for the far emitter, whose burst ends 29 ms late (K5).
  - The tail T30 is about 1.25–1.27 s. Same room and the same Eyring 1.291 s target [Inferred; not measured per placement].
  - So the premise holds by roughly 0.07–0.1 s, which is narrow. It must be printed and asserted.
- **Q5 on both_wall.** Seat 9's corrected bound gives L_drop = 1.12 dB at heard D/R −5.3 dB. That makes t ≤ 0.1 + (46 − 20 − 1.12)/60 · 1.29 ≈ 0.635 s, above the 0.43·T30 ceiling of 0.589 s. So the window should widen against S-A's 0.375 s [Inferred; the 46 dB SNR is Seat 9's Hyp]. The rerun decides.
- **Fatigue** across long attentive listening is reported only qualitatively in the corpus (Izhaki, ear-fatigue passage). Researcher: does BS.1116-3 give a maximum session length?

**Seat-specific answers.**
- **Is S-B\* worth a family?**
  - For detection, no.
    - Every cue it carries is weaker than on any s = 1 scene. Its early images are unscaled in both C80 windows, and no cue exists that s < 1 has and s = 1 lacks [Inferred].
    - Its non-detection supports nothing (file 31, answer 5).
    - Its detection is unlikely when S-W did not detect.
  - Its value is representativeness, which is the ground of Seats 3 and 9.
  - If it runs, I prefer **s = 0.9** on detectability (ΔC80 0.86 against 0.52; share 0.040 against 0.032). I would accept 0.7 if Seats 3 and 9 need an early part at −3.8 dB.
  - A gated variant that costs my seat nothing: S-B\* is tested only after an S-W detection at 0.9 dB. The bound is then already 0.5 dB, so the decision-relevant error rate stays at 0.049. That bears on Seat 5's cost.
- **Split or unsplit α:** **unsplit.** Each scene is its own family at item 3's thresholds, and the union rate is stated. A false detection is the conservative error for the listener: a tighter bound, no audible harm. Splitting cuts noise power from 0.63 to 0.405, which raises the chance of a missed detection, the error that reaches the listener as an audible step. Its cost in admissions belongs to Seats 5 and 6.
- **(a) Speech material:** **speaker MA, files MA01_01 and MA01_02.** The rule:
  1. Take the corpus's own first adult speaker and first two files.
  2. These were fixed as the kit's smoke default before anyone listened, and nobody has heard them through the kit, since speech is never in the listening pack.
  3. The pair must pass Q5 on the chosen scene. If it fails, the next pair in corpus order (MA01_03 and MA01_04) is used, then the next adult speaker.
  4. Never choose by ear.
  5. The record names the speaker. Whether another voice would be more sensitive is [Hyp]; a pretest by a non-decision listener (T1) is the upgrade if one is ever wanted.
- **(b) AX49 L4.**
  - **Same day: yes.** AX49 already places it with the AX47 ABX.
  - **Same sitting: no.**
    - Run it in a separate sitting, after a rest, never interleaved, in an order fixed in the pre-registration.
    - AX47 noise 0.9 dB goes first, while the listener is fresh: it carries the higher-stakes decision.
    - At a slow pace, about 2.8 h (K6) plus about 30 min for L4 [Hyp] is too long for one sitting.
  - **Stimuli: yes, before the first scored AX47 trial.** L4's stimuli are built, sealed and hash-committed before that trial, ideally in the same pre-registration commit. If L4 were designed after the AX47 scores, its open choices could be bent by them.
  - **Design gap:** item 14 does not fix the chord material, the scene, the level, or how `render_cli` produces a provisional (AX49 says `render_cli` never uses one). All of these must be pre-registered.

**6. Conditions of acceptance.**
- **V1, to 1/1:** S-W runs in 07c-2 as well, ahead of S-A, rather than only at 08-3.
- **V4, to 2/2:** S-W replaces S-B\* at 08-3. **To 1/1:** S-W runs in 07c-2, which makes it V2.
- **V2 and V3, to 0/0:** all of the following:
  - both_wall qualifies under the robust `click_check`;
  - the manifest prints the minimum gap, the heard T30 and the tail T30, and both the gap check and Q5 pass;
  - the overlap of the far emitter's burst with the fade (29.3 of 30 ms) is recorded against item 7, and the speech onset window is counted from the latest heard end of speech;
  - a null is worded "not detected … on a scene with tail share 0.667".

**7. Hand-offs.**
- **Seat 4:** the 0.1 m placements in binaural, for 08-3 (i).
- **Seats 3 and 5:** which `click_check` repair to use; the provisional render path for L4.
- **Seat 9:** S-W's label; the representativeness of S-B\*.
- **Seats 5 and 6:** the cost of the union false-detection rate.
- **Seat 7:** the hours.
- **Researcher:** BS.1116-3 session length; level discrimination of a decaying tail just after a masker ends.

**8. Premortem.** Under V4, the step goes undetected on S-A, and 1 dB stands for far-listener scenes where the same step moves the programme level 0.62 dB. The first to notice is a mixer automating a distant preset, who hears the reverb settle in a jump.

Files read:
- /home/user/makroof/docs/review/phase-07c-2/31-decider-abx-r4.md
- /home/user/makroof/docs/review/phase-07c-2/28-interrogator-on-file27.md
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/34-decider-m1-m2-final.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat1.md
- /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- /home/user/makroof/docs/review/phase-07c-2/40-decider-2a-2b-final.md
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md (items 1–16)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/phases/phase-07c-2b.md
- /home/user/makroof/docs/BUILD_PLAN.md (AX47 and AX49 rows, L170 and L172)
