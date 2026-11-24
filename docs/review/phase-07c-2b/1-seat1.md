# 1: Seat 1 (perceptual gatekeeper), M3: the ABX scene, S-W pick, α, click_check

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE"). Run 2026-11-24 in the
phase-07c-2b session as `seat1-perceptual-gatekeeper`. Recorded verbatim from the seat's answer.

SEAT 1 POSITION

The corpus is not present (`docs/corpus/` is missing), so every acoustic claim below is flagged as resting on my register or on the builder's measurements.

**1. Reading.** M3 asks which scene or scenes carry the AX47 self-ABX. K5 removed the only objection to the wet layout-4 placements, so the question is now whether 07c-2b runs the most sensitive admissible scene first. Cues it triggers:
- "Find the signal that breaks it" (B2): the scene is the stimulus.
- "A threshold quoted without its method": a non-detection on a dry scene would be read as cover for wet scenes.
- "Measure the floor first" (T1): `click_check` has no measured floor on this programme.

**My S-W pick under K5 (both events are false positives): `layout4_s1/both_wall`.**
- **Tail share 0.667.** ΔG at +0.9 dB is 0.621 dB at 1 kHz and 0.471 dB broadband, against S-A's 0.045 / 0.011 (file 29 L38 vs L33). That is about 14 times S-A's programme-level cue.
- **The other cues match S-A or better:**
  - ΔC80 is the full −0.900 dB.
  - The gap cue is the full g, as in every scene.
  - It is capped at m = 6, 7 and 8 (yes/yes/yes).
  - Peaks are −15.7 to −12.9 dBFS, inside item 10's −1 dBFS.
- **Heard D/R is −5.3 dB.** This is the tail-dominated, far-listener class my premortem named (26-seat1 L56).
- **It qualifies only once item 6 can pass it** (condition C1 below). As `click_check` stands, it still fails.

**Does the T-a premise (minimum gap ≥ tail T30) hold on both_wall?** It probably does, but this is unmeasured.
- The gap is ceil(1.370 s) to a partition boundary (abx_kit L470, L613).
- K4 printed no tail T30 for this scene. Layout 4's Eyring value is 1.291 s and S-A's tail T30 is 1.25–1.27 s (file 29 L86; file 34 L26).
- That leaves a margin of about 0.08–0.12 s [Inferred].
- On listener_corner (heard T30 1.288 s) the margin is about 0 and could fail. That is another reason not to pick it.
- `gap_check` (L519–529) already asserts the premise, so the check costs minutes.

**Is S-B\* worth a family?** It is not worth one as a detection gate.
- It is the least sensitive scene on both cues: ΔG 0.032 / 0.040 dB and |ΔC80| 0.52 / 0.86, against S-A's 0.045 / 0.90 (file 29 L30, L32).
- A non-detection there adds nothing that S-W does not already cover. A detection there with no detection on S-W would be an anomaly, pointing to an early/late balance cue, and that is when I would re-diagnose.
- I can live with it as an 08-3 family, where it serves Seats 3 and 9.
- If it runs, I pick s = 0.9 (C80 cue 0.86 against 0.52). I can live with 0.7 if Seat 9 needs it. On G the difference is 0.008 dB.

**Split or unsplit α: unsplit.**
- Splitting cuts noise power on the primary scene from 0.630 to 0.405, and speech from 0.405 to 0.197 (file 31 answer 4). That spends detection power where the gate matters.
- A false detection costs the 0.5 dB bound. That is the conservative error, and its cost falls on compute (Seats 5, 6 and 7), not on the listener.
- A miss keeps 1 dB where a step may be audible, which is the listener-facing error.
- This is consistent with my 4-seat1 position: within one scene's family the chains test one claim; across scenes, item 13 already confines each non-detection to its own class.
- I can live with splitting only the 08-3 families. I cannot accept any split that lowers the 07c-2 primary family below 0.049 (rated 2).

**2. Ranking.**
- **V2, prefer.** It runs S-W = both_wall at 07c-2.
- **V3, can live with.** S-W becomes layout5/emitter_wall (share 0.869, ΔG 0.792), but the T-a premise fails on layout 5.
- **V1, can live with.** The 07c-2 gate rests on the two weakest scenes.
- **V4, cannot live with.** The wet class is never tested.

**3. Tension now.**
- **V2: 1.** It needs the click fix, the gap check and the heard-onset point (C1–C3).
- **V3: 2.** On layout 5 the heard T30 is 2.557–2.575 s against a tail T30 of 2.58–2.62 s (K4 fact 9), so `gap_check` fails as built. That reopens M2.
- **V1: 2.** The class (c) and W_max decisions rest on scenes with ΔG ≤ 0.045 dB, and S-B\* adds a family without adding sensitivity.
- **V4: 2.**

**4. Tension later.**
- **V2: 0.** A detection tightens correctly. A non-detection is the strongest evidence available.
- **V3: 1.** An AX47 /fix-plan, and the layout-5 gaps have to be redefined.
- **V1: 2.** If S-W binaural detects at 08-3, the bound moves to 0.5 dB after the W pin and the golden round. That is a phase of rework.
- **V4: 3.** No test ever covers late-dominated scenes before Phase 08 freezes. The first evidence would be users hearing a 0.9 dB tail jump at handover. This breaks "the hardest signal, never the demo signal" (§2).

**5. Evidence.**
- Share, ΔG, ΔC80, caps and peaks: file 29 L28–46 [Observed, builder].
- K5: file 32 L17–35 and L115–122 [Observed]. S-A also passes only because its peak frames coincide: the step region sits 23.8–30.1 dB above the detector threshold.
- Powers: file 31 L91–94; I redid 2517/65536 = 0.0384.
- JNDs (G 1 dB, C80 1 dB) from Vorländer Table 6.1 via AX47, corpus not checked [Medium].
- Gap rule: abx_kit L470, L613, L519–529 (from the code).

**6. Conditions of acceptance.**
- **C1 (V2, V3): `click_check` must be fixed. My answer is yes, a fix is needed.**
  - On this noise programme the detector cannot discriminate in the step region (file 32 L115–116), so item 6's click gate has no measured floor. A real fade transient would be a non-level cue, a false detection.
  - I prefer A − B against the crossfade model. Per-frame flags still judge against the direct bursts, which sit 24–30 dB above threshold, and that masking is what hid the fault.
  - Pre-state the criterion. File 32's "high-passed A − B peak in the fade ≤ the peak in the 100 ms after" passes both_wall by only 0.6 dB, so measure it across all 50 stimuli.
  - Plant a synthetic click to show the check's floor.
- **C2 (V2):** the M2 debt holds: print the tail T30 and assert gap ≥ tail T30 on both_wall before the seal.
- **C3 (V2): put the step at the heard gap start.**
  - In both_wall the far emitter's heard burst runs to N + 1407, through 29.3 of the fade's 30 ms (file 32 L52, L62). Item 7's "step at a gap start" holds on the input only.
  - Either place N at or after every emitter's heard burst end (a kit change, minutes), or pre-register the deviation. I prefer the first.
- **V3 → 1:** build gaps from max(heard T30, tail T30). That is a kit parameter and needs an M2 re-decision.
- **V1 → 1:** run S-W omni diotic at 07c-2, which is V2 with S-A added.
- **V4 → 2:** add S-W to 08-3. → 1: run S-W at 07c-2.

**7. Hand-offs.**
- Seat 4: both_wall's 0.1 m placements in binaural for item 15(i).
- Seat 9: the item-9 label for a 0.1 m wall-to-wall placement, and the s = 0.7 versus 0.9 representativeness.
- Seats 3 and 5: which click fix to implement.
- Seats 5, 6 and 7: the false-detection union rate of 0.098 or 0.147.
- Seat 7: hours. Under V2, 07c-2 is one scene of about 2 h (K6), noise length scaled by T30 1.37 against 2.01 s.
- Researcher: level-discrimination thresholds for a decaying tail just after a masker ends (still open).

**8. Premortem.** If V4 or V1 is chosen and S-A is not detected, class (c) admits statistical sources and ships a 0.9 dB tail jump at handover in a far-listener scene. The first to notice is a mixer automating a distant source in the beta, not the ABX.

Files: docs/review/phase-07c-2/29-k4-candidates.md, docs/review/phase-07c-2/32-k5-k6-clicks-session.md, docs/review/phase-07c-2/31-decider-abx-r4.md, docs/review/phase-07c-2/34-decider-m1-m2-final.md, docs/review/phase-07c-2/13-decider-rebuttal-r4.md (L144–206), tools/ci/abx_kit.py (L399, L464–476, L519–529, L613).
