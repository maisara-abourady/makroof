# 4-seat8: Seat 8, M3-L4 (chord material, L4-A/L4-B)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 8 POSITION (M3-L4, narrow: the chord material, plus ratings for L4-A and L4-B). For docs/review/phase-07c-2b/4-seat8.md. I edited no files.

**Whose ears:** a producer who opens a session and presses play on an ambient or cinematic track whose last chord rings into an 8 s tail. No audience ever hears the provisional, because offline renders and bounces never use it (AX49, AX5). So the only person at risk is the producer, while judging a tail during the provisional window.

1. **Reading.** Which stimulus makes the L4 ABX test what a producer would really run through a long reverb on first play after load. The cues it triggers: "Where was it judged?" (cue 10) and "the maker's detector" (cue 9). Here the maker is the only listener, so their detector is the one that matters.

2. **Ranking.**
- **L4-A: prefer.** The first play after load is the realistic case. Record (h) printed 9.51 s for an 8-instance Windows load (CI 43242209571). A producer who presses play straight after load can therefore hear a whole provisional tail, including the fade over [L_f, L_p). L4-A is that experience. It is also the event AX49's Reversal names: "the L4 ABX detects the cut".
- **L4-B: can live with, only as an addition.** The handover is at or before L_f. So by the time the cut would play, the exact tail is already playing. Before L_f the provisional and the exact come from the same generator, seed and stream, so they differ only by the normalisation step (AX49 text). L4-B therefore tests the handover crossfade, not the cut. Run alone, it cannot trigger the Reversal it is meant to feed.

3. **Tension now.**
- L4-A: **1**. It is stricter than the median session, which is inside my tolerance.
- L4-B: **2**. It misses the event a producer hears on first play, and it moves my criterion 5 (judge on the chain and in the condition the listener actually has) off the real case.

4. **Tension later (the debt).**
- **L4-A: 1.** If it detects the cut, the Reversal goes to 07d, which is already planned, so there is no new debt. If it does not detect, the residual risk is a wash-genre producer judging a tail at load. The evidence that could overturn it is producer reports in beta (Phase 13).
- **L4-B: 2.** A pass would probably be read as clearing the cut, which it never tested. Undoing that means another ABX sitting plus a re-read of AX49 (about a day of Maisara's listening). The evidence would arrive as beta reports that the tail sounds shorter on first play.

5. **Evidence.**
- None of my incidents covers how producers voice chords into long reverbs. Everything below on the chord is `[Inf]` from producer practice, or `[Hyp]` where marked. I give no numbers; level, durations and seeds belong to Seats 1 and 3.
- The material I would put in front of the test, and why:
  - **Timbre: a synthetic pad as the primary material.** Detuned saw-type oscillators, gently low-passed, steady through the hold. This is what ambient and cinematic producers most often send to an 8 s-class reverb. It holds level, so the tail is fully built at release. It can be generated from code with a seed, so it needs no sample licence and its sealed hash can be reproduced. `[Inf]`
  - **Piano as a variant only.** A sampled piano with the pedal down is equally idiomatic. But it decays during the hold, so its free-decay onset depends on the sample. It also brings licence and provenance work (Seat 9). `[Inf]`
  - **Voicing: open and spread, no low clusters.** For example, root and fifth in the low-mid with upper voices an octave or two above, consonant (triad or add9). Producers avoid muddy low clusters under long reverbs. `[Inf]`
  - **Register: put energy in the band where T60_max sits.** L_f is set by T60_max, so the cut is exposed highest in that band; the other bands have decayed further by L_f. The chord's register must put energy in that band, whichever band the scene puts it in (Seat 2). `[Inf]`, from the AX49 text.
  - **Release: a musical release, not a gate click.** The fade at L_f should be the only abrupt event in the stimulus; otherwise listeners may cue on an artefact producers never make. The release time goes to Seat 3. `[Inf]`
  - **Voicing matters less than it seems.** The tail is octave-band noise (K2), so after the release the chord matters mainly through its octave-band spectrum; the harmony is smeared. Seat 1 owns whether that makes the spec reducible to a band spectrum. `[Hyp]`
- **Fully wet is realistic, not just strict.** It is the last chord of an ambient piece or a breakdown with the dry signal muted. `[Inf]`

6. **Conditions of acceptance.**
- **L4-B (2):** run it only after L4-A, and label it as a handover test, not the AX49 cut test. That lowers it to **1** now and **1** later.

7. **Hand-offs.**
- Seat 1: level, pass rule, and whether the pad-versus-piano choice changes detectability.
- Seat 2: the scene, and which band carries T60_max.
- Seat 3: the release envelope and the per-stimulus checks.
- Seat 9: provenance if a sampled piano is used.
- Human: genres built on wash are the main users of 8 s T60, and I default to subtraction. Producers' own reports outrank me there.

8. **Premortem.** If L4-B is chosen and passes, an ambient producer on an 8-instance Windows session reports in beta that the tail cuts short on the first play after load, while the record shows "not detected".

**Workflow requirement most affected:** the translation view. The tool should warn when a judgement was made under the interim tail.
