# 12-seat8: Seat 8 on the L4 band-coverage red

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 8 POSITION (M3-L4 narrow: the chord's spectrum after the band-coverage fail). For docs/review/phase-07c-2b/12-seat8.md. Read-only; I edited no files.

**Whose ears:** the producer on the first play after load, judging the last pad chord as it rings into an 8 s tail (4-seat8). No audience hears the provisional tail.

1. **Reading.** Choose between brightening the chord so it passes the 4 kHz coverage check, or changing the check so it fits the chord. The cues this triggers are 10 ("where was it judged": the material has to be what producers actually play) and 6/7 (a surface that doesn't fit the frame).

2. **Ranking.**
- **C: prefer.** Keep the chord and assert coverage over 63 Hz–2 kHz, with 4 kHz printed.
- **A: can live with.** Extend the 1/k partials to 10 kHz. But it probably does not fix the fail (section 5).
- **B: cannot live with as the primary.** I can live with it only as a secondary variant (section 6).

**Which is closest to what producers put through an 8 s reverb:** the current chord (C). My 4-seat8 material was detuned saws, *gently low-passed*. A 1/k series cut off at 5 kHz is that pad. An unfiltered saw (A) is brighter than producers usually send into a long hall. A flat 1/√k series (B) is a buzz with pink-noise spectrum. Producers do not voice a pad like that for an 8 s tail. `[Inf]`, no incident covers pad voicing.

3. **Tension now.**
- **C: 0.** The material stays representative. The 4 kHz band of a low-passed pad after an 8 s room (T60 3.73 s at 4 kHz) really is about 20 dB or more below the low-mids. The coverage limit is the outlier here, not the chord.
- **A: 1.** It is a little brighter than typical, which is within my tolerance.
- **B: 2.** It moves the test off the real material (criterion 5). It may also make the test more lenient: at a matched steady-state level (−28.4 dBFS), energy moves out of 63 Hz–1 kHz. Those are the bands where T60_max sits and where the cut is exposed. `[Inf]`, Seat 1 to verify.

4. **Tension later (the debt).**
- **C: 1.** If a bright-pad producer reports in beta (Phase 13) that the tail is cut short, the 4 kHz exposure was untested. But at L_f the 4 kHz band is already 40.1 dB down (builder table), so it is unlikely to carry the cut. Seat 1 owns that claim. Undoing it costs one extra variant sitting.
- **A: 1.** If it still fails, it costs a rebuild and another board round.
- **B: 2.** A "not detected" on bright material lets the record say the cut was cleared when the realistic material was never tested. Undoing it means a re-sitting with the pad, about a day of Maisara's listening.

5. **Evidence.**
- **A probably does not pass.** This is my own rough arithmetic `[Inf]`; Seat 1 or the builder should verify it.
  - With 1/k amplitudes, power per octave falls about 3 dB per octave. From 125 Hz to 4 kHz is 5 octaves, which predicts about −15 dB dry. The kit measured −14.8 dB.
  - The 5 kHz cutoff removes only about 13% of the 2.83–5.66 kHz band's power, about −0.6 dB.
  - So extending to 10 kHz recovers about 0.6 dB. Add the room's 8.1 dB loss and the 4 kHz band ends near −22.3 dB, which still fails the 20 dB limit.
- **B would pass.** A 1/√k series gives about constant power per octave, about 0 dB dry, so about −8 dB after the room `[Inf]`.
- The builder's figures (−14.8 dB dry, 8.1 dB taken by the room, 40.14 dB depth at L_f in the 4 kHz band) come from 11-builder-l4-kit.
- No incident in my record covers spectral tilt of pads. Everything above about material is `[Inf]` from producer practice.

6. **Conditions of acceptance.**
- **B (2):** use it only as a second, labelled "bright" variant run after the pad arm, never in place of the pad. That lowers it to 1 now and 1 later.
- **C:** no condition from me. Whether 4 kHz must be asserted for the test to be valid is Seat 1's call. If Seat 1 says it must, my fallback is B as the secondary variant, not A.

7. **Hand-offs.**
- Seat 1: the coverage criterion itself; whether the cut can be heard in the 4 kHz band 40 dB down; whether B's level-matched spectrum makes the test more lenient.
- Seat 3: the per-stimulus checks if the criterion changes.
- Builder: the dry input peaks at +3.05 dBFS. This is not mine, but noted.
- Human: genres built on wash may use brighter pads. Producers' own reports outrank me there.

8. **Premortem.** If B replaces the pad and the result is "not detected", an ambient producer reports in beta that a dark pad's tail cuts short on first play, and the record shows no test ever ran on that material.

**Workflow requirement most affected:** the translation view. Judge the tool on the material producers actually play, through the same condition they hear it in.
