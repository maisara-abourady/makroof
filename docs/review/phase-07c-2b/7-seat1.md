SEAT 1 POSITION (round 2 of M3, phase 07c-2b, after K7-builder)

The corpus is present this time (c1b171f). I checked the JNDs against Vorländer Table 6.1: G is 1 dB and C80 is 1 dB, both in the 500–1000 Hz range, measured under static concert-hall conditions. So I read 1 kHz as the band that governs. Every value below in "JND units" is that static JND. It is a borrowed threshold and keeps its method.

**1. Reading.** K7-builder measured eleven s < 1 candidates and four re-checks. The questions are:
- which scene carries the self-ABX;
- whether layout 5 is admitted through the gap rule;
- whether α stays unsplit;
- whether the measured shares meet "the hardest signal".

Cues this triggers:
- B2 (the scene is the stimulus; find the one that breaks it);
- "a threshold quoted without its method";
- a new cue from file 4: every s < 1 scene has a filled early part (−1.3 to −10.3 dB re direct, fact 11). So the cue "the gap shows the full g" that I relied on for s = 1 scenes is no longer automatic.

**(e) Does the share meet "the hardest signal"?** Programme cue = ΔG at 1 kHz, from file 4 Table 1.

| scene | share | ΔG at 1 kHz | JND units | verdict |
|---|---|---|---|---|
| layout5_s1/emitter_wall (strongest measured, V3) | 0.869 | 0.792 dB | 0.79 | — |
| layout5_s0.9/emitter_wall | 0.852 | 0.778 dB | 0.78 | meets (0.014 dB below the maximum) |
| layout5_s0.8/emitter_wall | 0.834 | 0.763 dB | 0.76 | meets |
| layout4_s0.7/both_wall | 0.692 | 0.641 dB | 0.64 | the hardest admissible under the kit's heard-T30 rule; 0.15 dB below the maximum |
| layout4_s1/both_wall (V2) | 0.667 | 0.621 dB | 0.62 | — |
| layout5 default, s0.9 / s0.8 | 0.545 / 0.485 | 0.51 / 0.46 dB | 0.51 / 0.46 | does not meet: about 60 % of the best cue; adequate, not hardest |
| layout4_s0.7/listener_wall | 0.126 | 0.124 dB | 0.12 | does not meet |
| S-A | 0.046 | 0.045 dB | 0.045 | does not meet |

- **Gap cue.** On s = 1 scenes it is the full g, because the early part is −67 to −77 dB re direct.
- **On s < 1 scenes it is diluted for up to t_mix,e (77.5–344 ms) after N, by early energy that the step does not scale.** My estimate for s0.7/both_wall is about 0.85 dB against 0.9 [Inferred]: early energy is about −11.6 dB re tail, and it is gone by t_mix. The figure is unmeasured. If the dilution is larger, S-A's gap cue would beat the s < 1 scene's on that one cue.

**2. Ranking**
- **(a) V6**
  - layout5_s0.9/emitter_wall: **prefer**, only under the max gap rule.
  - layout4_s0.7/both_wall: **prefer**.
  - layout5_s0.8/emitter_wall: **can live with**.
  - layout5_s0.9/default and s0.8/default: **can live with**. s0.9 is better than s0.8 (share 0.545 against 0.485; early part −10.3 against −6.9 dB).
  - layout4_s0.7/listener_wall as the sole scene: **cannot live with**.
- **(b) Re-stated**
  - V2: prefer.
  - V3: can live with, rising to prefer under the max rule.
  - V3′: can live with.
  - V1: can live with.
- **(c) Gap rule:** I prefer the max(heard, tail) rule, with Δ added as in revised D-M3b. I can live with the heard-T30 rule.
- **(d) α:** unsplit is prefer. Splitting only the 08-3 families I can live with. Splitting everywhere I cannot live with.

**3–4. Tension now / later**

| option | now | later | reason |
|---|---|---|---|
| V6 layout5_s0.9/emitter_wall, max rule | 0 | 0 | Strongest qualifying cue. The heard gap 1→2 was 26 ms short only because K7-builder did not add Δ; revised D-M3b with T = max(heard, tail) closes it. Under the heard rule: 2/1, because M2 fails by 8–72 ms. |
| V6 layout5_s0.8/emitter_wall | 1 | 0 | Early part −5.2 dB, so more gap dilution. |
| V6 layout4_s0.7/both_wall | 1 | 0 | The gap-cue dilution is unmeasured. Heard D/R is −8.2 dB, more tail-dominated than V2's −5.3. Broadband ΔG is 0.296 against V2's 0.471. |
| V6 layout5 default, s0.9 / s0.8 | 1 | 1 | The far-listener, tail-dominated class (D/R ≤ −5 dB) stays untested. Item 13 confines a non-detection to its own class. |
| V6 listener_wall | 2 | 3 | Heard D/R +0.4 dB. No late-dominated scene would be tested before the Phase 08 freeze, which is my V4 reason. |
| V1 | 2 | 2 | Unchanged. File 4 confirms shares 0.046 and 0.032. |
| V2 | 0 | 0 | Was 1/0. My C1–C3 are now met: form (b) residual −162/−170 dBFS, 64 dB or more under the floor; tail T30 1.313/1.274 s measured, programme gap 1.376 s, margin 63 ms (my estimate of 0.08–0.12 s was high); D-M3b revised. |
| V3 / V3′ | 0/0 and 1/0 under the max rule | 2/1 under the heard rule | Under the heard rule `gap_check` fails on every layout-5 scene (fact 8). |
| Max gap rule | 0 | 0 | On layout 4 it changes nothing, because heard T30 ≥ tail T30 on every layout-4 scene (Table 1). Heard T30 is an ISO fit across the AX21 gap, not a decay rate (D-M3g label), so taking the max with the tail T30 is the robust construction. |
| Heard-T30 rule | 1 | 0 | Perceptually the shortfall is harmless: 8–72 ms against a 2.6 s T30 leaves the residual at about −58.3 dB or less at the next onset, which is masked [Inferred]. Its cost is that it excludes the two strongest qualifying candidates. |
| α unsplit | 0 | 0 | |
| α split only the 08-3 families | 1 | 1 | Power at p = 0.75 on the 08-3 noise family falls from 0.630 to 0.405. |
| α split everywhere | 2 | 2 | |

**(d) Confirmed:** my unsplit cell is 0/0, so unsplit's maximum stays 1.

**5. Evidence**
- G and C80 JNDs: Vorländer Table 6.1 (corpus).
- Shares, ΔG, early part, T30, gaps and Q5: file 4, Tables 1, 2 and 4, facts 7, 8 and 11 [Observed, builder].
- Residual arithmetic: 60 × 0.072 / 2.6 = 1.66 dB.
- Gap-dilution estimate [Inferred].
- Researcher (still open): level discrimination of a decaying tail just after a masker ends.

**6. Conditions of acceptance**
- **both_wall s0.7 (1 → 0):** per stimulus, print the 1 kHz level of E − B relative to B in [N, N + 100 ms) and [N, N + 300 ms), plus the per-band maximum of ΔG. If the gap cue is within about 0.1 dB of S-A's, I go to 0.
- **layout5 emitter_wall (2 → 0):** adopt the max rule, with Δ in the gap.
- **layout5 default (1 → 0):** run a late-dominated scene with share ≥ 0.6 at 08-3.
- **listener_wall (3 → 2):** add a tail-dominated scene at 08-3. To reach 1, run that scene at 07c-2b.
- **Fact file 4 leaves unmeasured, on every wet scene.** In the speech chain, the silence after the onset is about T(1 − window) plus TSP's trailing silence. By construction that is shorter than the tail T30 on wet scenes:
  - both_wall: about 0.97 s against 1.313 s;
  - layout5 emitter_wall: about 1.63 s against 2.60 s.

  This is [Inferred] and comes before adding TSP's trailing silence. Perceptually it is close to indifferent: the cue sits in the first few hundred ms. But interrogator file 6's speech-chain M2 assertion would fail. Either lengthen the pause or restate that rule; the decider rules on which.

**7. Hand-offs**
- Seat 2: C2 fails on every wall placement.
- Seat 4: the layout-5 binaural label, and the 0.1 m y-wall listener at 08-3.
- Seat 9: the Class lines for layout5 s0.9.
- Seat 7: the time cost, 2.39 h against 1.76 h.
- Decider and interrogator: the speech-chain M2 form.

**8. Premortem.** Suppose listener_wall or layout5/default is chosen and gives a non-detection. Then a 0.9 dB jump at handover ships in tail-dominated far-listener scenes. The first to hear it is a mixer automating a distant source in the beta.

Files: /home/user/makroof/docs/review/phase-07c-2b/4-k7-candidates.md, /home/user/makroof/docs/review/phase-07c-2b/5-decider-rebuttal-r2.md, /home/user/makroof/docs/review/phase-07c-2b/6-interrogator-on-file5.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1, L2056–2066)
