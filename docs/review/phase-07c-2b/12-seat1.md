# 12-seat1: Seat 1 on the L4 band-coverage red

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (M3-L4 band-coverage red, phase 07c-2b). Read-only; for saving as /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md.

I read /home/user/makroof/docs/review/phase-07c-2b/11-builder-l4-kit.md, 4-seat1.md and 9-decider-m3-r3.md. The corpus was not needed: every figure below is spectral arithmetic I did myself or the builder's measurement.

**1. Reading.** My chord spec requires every band from 63 Hz to 4 kHz to be within 20 dB of the strongest band. On the clean stimulus 4 kHz is at −22.94 dB, so the check is red. Cues: the hardest signal (B2, W4); a threshold that carries its method (S4); not loosening after a red (O1).

**What the builder's diagnosis gets wrong (my arithmetic, [Inferred]).** Partials at 1/k have energy 1/k². That gives each note about f0·(1/f_lo − 1/f_hi) per octave band, so the band energy falls about 3 dB per octave.
- **Dry chord, 4 kHz band, cut at 5 kHz:** 655 Hz (the sum of the five f0) × (1/2830 − 1/5000) = 0.100.
- **Dry chord, 125 Hz band:** G2 + C3 + E3 fundamentals + C2 k=2 = 3.25.
- **Ratio:** −15.1 dB, which matches the builder's −14.8 dB.
- **The 5 kHz stop is not the cause.** Filling the octave to 5.66 kHz raises the 0.100 to 0.116, which is **+0.6 dB**. The cause is the 1/k slope (−15 dB over five octaves) plus the room's −8.1 dB.
- **So option A should still fail, at about −22.3 dB.**

**Where the cut is audible.** I measured B in the 100 ms after release + L_f, re the hold:

| Band (Hz) | 63 | 125 | 250 | 500 | 1k | 2k | 4k |
|---|---|---|---|---|---|---|---|
| B (dB re hold) | −39.9 | −34.9 | −31.3 | −29.9 | −27.5 | −36.8 | −48.5 |

- At L_f the tail is 40.1 dB down at 4 kHz, against 18.7 dB at 63 Hz–1 kHz.
- So the 4 kHz part of the cut sits 21 dB below the 1 kHz part. Neither chord option changes that: the 40 dB depth comes from the scene (T60 3.73 s, air absorption), not from the chord.
- **Answer to (C):** whether the cut is heard does not depend on 4 kHz. It depends on 63 Hz–2 kHz, and most of all on 0.5–1 kHz.
- The 4 kHz clause in my spec was my own error: I did not combine the 1/k slope with the room's loss at high frequencies.

**2–4. Ranking and tension (now / later)**

| Option | Rank | Now | Later |
|---|---|---|---|
| **B: 1/√k to 10 kHz (or to 5.66 kHz), criterion unchanged** | prefer | **0**. With 1/k energy the dry chord is about flat per octave: 4k ≈ 3.47 against 125 ≈ 3.5. Predicted 4 kHz ≈ −8 to −13 dB after the room, which passes. It also raises the cut's exposure at 1–2 kHz by about 9–12 dB re 125 Hz at matched RMS, so the stimulus gets harder, which is my criterion 1. Timbre is Seat 8's call. | **0**. The chord becomes "l4-chord-v2"; nothing is sealed and no trial has been scored. |
| **E (added by me): C plus a cut-coverage assert.** In 63 Hz–2 kHz, B's energy in the 100 ms after release + L_f is within 20 dB of its strongest band (today 12.4 dB spread, passes); the steady-state coverage check runs on 63 Hz–2 kHz; 4k and 8k printed with their depths | can live with | **1**. It is a loosening after a red, justified only by the depth argument above. It keeps the 1/k chord, which is 9–12 dB weaker at 1–2 kHz than B. | **1**. The null must say "cut exposed at 63 Hz–2 kHz; at 4 kHz the tail is 40 dB down at L_f". |
| C as worded | can live with | 1 | 1 (the same, but with no assert on where the cut is actually exposed) |
| D (A + C) | can live with | 1. The A half adds only 0.6 dB. | 1 |
| A alone | cannot live with **as a fix**. This is not a veto: it simply does not work. | **2**. Predicted to red again at about −22.3 dB, which costs a build cycle and leaves the wrong cause in the record. | 1 |

**5. Evidence**
- The 1/k and 1/√k band sums and the +0.6 dB figure: my own arithmetic [Inferred]. They match the builder's −14.8 dB.
- Per-band T60, the depths at L_f and B's cut-window levels: measured by the builder (file 11).
- That the 4 kHz part adds nothing to detection when it sits 21 dB below 1 kHz: [Hyp]. It is a plausible masking and loudness argument with no corpus citation. Researcher: optional.
- The B prediction (−8 to −13 dB) is [Inferred]. The room's per-band effect is known only at 4k and 125. The builder confirms it in the rebuild, and a red stops again.

**6. Conditions**
- **A, from 2 to 1:** only as part of D.
- **C and E, from 1 to 0:** none available. A loosened criterion stays at 1 by my own §2.
- **For B:**
  - Seat 8 accepts the brighter timbre.
  - The level, peak and S1–S5 checks are rerun.
  - The chord version is bumped before the seal.
- **Fallback:** I ask the decider to pre-decide **B, then E if Seat 8 rejects B or B reds**, so that a second red does not need another round.

**7. Hand-offs**
- **Seat 8:** timbre and harshness of 1/√k, and the upper limit (5.66 kHz or 10 kHz).
- **Seat 3:** confirm the cut-window measure in E is computable on the partition grid.
- **Seat 9:** whether the null wording needs the 4 kHz depth sentence.
- **Builder:** correct the cause stated in file 11 (it is the slope, not the 5 kHz stop).

**8. Premortem.** If C passes without E's assert and L4 returns a null, nobody can show the 1/k chord put enough energy at 1–2 kHz to expose the cut. A critic of AX49 then reads the null as a dull-chord artefact, and the AX49 reviewer at 07d is the first to notice.
