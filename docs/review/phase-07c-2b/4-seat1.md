# 4-seat1: Seat 1, round 2 on M3 (α, V1-W cell, F1–F4) and M3-L4

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (round 2: M3 R2 (a), (b), (c) and the new matter M3-L4). Read-only; for saving as /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md.

Corpus is present (c1b171f). The binomial figures below are my own arithmetic (summed pmf).

**1. Reading.**
- **R2** asks how α is handled across F1–F4 under V1-W.
- **M3-L4** asks how the AX49 L4 stimulus is built.
- Cues triggered: per-listener power (T1); the hardest condition (B2, W4); pre-registration before any scored trial (O1).

---

## R2 (a): the 24-trial split against unsplit + C1

**What changed since round 1.** I preferred unsplit because the 13/13 split cut noise power from 0.630 to 0.405. The 24-trial split removes that reason.

| | noise criterion | α noise | power at p = 0.70 / 0.75 / 0.80 | speech | α per scene | at 07c-2b (F1+F2) | F1–F4 |
|---|---|---|---|---|---|---|---|
| Unsplit + C1 | ≥ 12/16 | 0.0384 | 0.450 / **0.630** / 0.798 | ≥ 13/16, 0.0106, power 0.405 | 0.049 | ≤ 0.098 | ≤ 0.196 |
| 24-trial split | ≥ 18/24 | 0.0113 | 0.389 / **0.607** / 0.811 | ≥ 13/16, unchanged | 0.0219 | ≤ 0.0438 | ≤ 0.0876 |

- The power loss at the design point is 0.023. It is 0.061 at p = 0.70, and the split gains 0.013 at p = 0.80 (the two curves cross near p ≈ 0.77).
- The false-reversal rate falls by more than half, so a recorded "detected" is worth more as evidence. My §2 criterion 3 counts that.

**Ranking and tension:**
- **24-trial split: prefer.** Now **1** (−0.023 power at p = 0.75; a 30-presentation block carries a fatigue risk [Hyp]). Later **0** (the trial count is one parameter, applied the same way at 08-3).
- **Unsplit + C1: can live with.** Now **1** (a union of 0.098 at admission). Later **1** (0.196 over four families: about one in five chances that a recorded reversal is false under the null).

**Trial-count change after K6:**
- Noise blocks go from 22 to 30 presentations (24 scored + 6 anchors).
- Per scene, presentations go from 44 to 52 with no 0.9 detection, and from 88 to 104 with every block run: +18 %.
- Scaled linearly, K6's 1.3–2.8 h per scene becomes about 1.5–3.3 h [Inferred; K6's pace is Hyp]. The hours are Seat 7's.
- The change is admissible only if no scored trial of any family has been run, and it is committed in the same pre-registration commit.

**Conditions on the split:**
- 3 anchors in each half of the block, on each side of the break after trial 15, so that fatigue in the second half voids the block instead of passing as a null. Pass stays at ≥ 5/6.
- Null wording: "not detected in 24 trials by one listener (power 0.61 at p = 0.75)".

**An option of my own (I added it).** Speech also runs ≥ 18/24:
- α per scene 0.0226; 0.0453 at 07c-2b and 0.0905 over F1–F4, all within the family limits.
- Speech power rises from 0.405 to 0.607.
- Tension 0/0 for my seat. Cost: +36 % presentations per scene (Seat 7's hours).
- I prefer it but do not require it.

**F3 and F4.** I want the same design as F1 and F2: the same trial counts, criteria, anchors and seeds. Item 15 requires identical trials, and chain comparability needs the same power. Each family's α and the union rate are stated in the record.

---

## R2 (b): my V1-W cell

I re-rate it **0/1** (lower than the 1/1 read). The decider adopted every one of my V2 → 0/0 conditions:
- HF-W asserted;
- the gap, heard T30 and tail T30 printed and asserted;
- the 29.3 ms overlap recorded against item 7;
- Q5 counted from the heard end of speech;
- the null worded with the tail share (item 13).

S-W is heard first, while the listener is fresh. The later 1 stands: S-W's rank rests on ΔG and ΔC80 alone, and 08-3 (i) is a near-wall binaural scene.

---

## R2 (c): F1–F4 and Seat 4's label

**Confirmed.** Each of F1–F4 can reverse AX47, with Seat 4's (i) rule: a non-detection on (i) never counts as binaural evidence, and a detection reverses AX47.

This is my asymmetry rule.
- **Why a detection counts:** a detection on (i) is the shipped binaural output of a valid scene (FR-3D-5), with item 6 and HF-W per ear excluding artefacts.
- **Why a null does not:** a null at 0.1 m from a wall, through a free-field HRTF, says nothing about the class.

---

## M3-L4

**Reading.** From the code, K23 holds: both crossfade states read one input history. So after the handover the output equals the exact render.

Consequences:
- The cut is heard only over [release + L_f, handover).
- L4-B (handover ≤ L_f) therefore cannot contain the cut, which is the defect named in AX49's reversal trigger. What it tests is the ≤ 0.06 dB normalisation step plus the AQ4 fade. AX47 (b)'s asserted bound and the AX47 ABX already cover both, more sensitively.

| option | rank | now | later |
|---|---|---|---|
| L4-A | prefer | 0 | 1: it is the worst-case exposure; how often a user meets it comes from record (h)'s time-to-exact, not from L4 |
| L4-B | cannot live with, as the L4 test | 2 | **3**: AX49's "the L4 ABX detects the cut" can never fire, so the cut ships untested (my §2: the hardest condition is never traded) |

**My prediction, pre-registered so it can embarrass me: detection** [Inferred]:
- The energy past L_f is e^(−13.82·0.312) = 0.0134, so the cut comes when the decay is about 18.7 dB (+10·log10 of the tail share) below steady state. That is from AX49 K17′, arithmetic redone.
- After the cut, the exact decay has about 41 dB still to run.

**Condition for L4-B, from 3 to 1:**
- either it runs only as an unscored record after L4-A;
- or (L4-B′) the handover is seeded in [release + L_p, release + L), which gives the realistic dropout-and-return seen on slow loads (9.5 s, AX49).

**Chord spec** (the voicing and timbre are open to Seat 8; band coverage and timing are my constraints):
- **Notes:** a generated, deterministic open C voicing: C2, G2, C3, E3, G3 (65.4, 98.0, 130.8, 164.8, 196.0 Hz).
- **Partials:** each note is a band-limited harmonic series with amplitudes 1/k up to 5 kHz, phases from a fixed seed, versioned like D-B3. No sampled instrument.
- **Band coverage:** the exact render's steady state has every band from 63 Hz to 4 kHz within 20 dB of its strongest band. This is printed and asserted, and the T60_max band (expected to be low, because of air absorption) is printed.
- **Envelope:**
  - 0.5 s of silence;
  - a 20 ms raised-cosine attack;
  - a 4 s hold. A hold of 0.273·T60 = 2.2 s reaches within 0.1 dB of steady state, so 4 s leaves margin;
  - a 10 ms raised-cosine release, so the chord adds no decay of its own;
  - at least L (12 s) of free decay.
- **Level:**
  - the exact render's steady-state RMS equals the AX47 noise stimuli's heard RMS within ±1 dB [kit choice];
  - peak ≤ −1 dBFS;
  - no normalisation;
  - the same headphones and level setting as the AX47 sittings.
- **Seeds:** tailSeed fixed and shared by A and B (AX49 by definition), plus the trial-plan seed. Both are committed with `prereg_hashes`.
- **Asserted before the seal:**
  - the prefix check on A−B ≤ −18.27 dB over [0, release + L_f − h);
  - the cut's energy, printed per band in dB relative to B's steady state.

**Pass rule.** Its own family, not part of AX47's union:
- **Detection:** ≥ 12/16 (α 2517/65536 = 0.0384; power 0.630 at p = 0.75).
- **Anchors:** 6 interleaved trials pairing exact with exact at tail −3 dB (item 5's method) on the same chord. Pass ≥ 5/6; otherwise the block is void and gets one rerun.
- **Familiarisation:** labelled, no scored feedback.
- **Detection result:** AX49's Reversal fires, and the board takes it up with 07d's candidates first. The result is worded "worst case: provisional current through the whole free decay".
- **Null result:** worded "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic". Never "inaudible".

---

**5. Evidence.**
- Binomial tails and powers: derived (K6 sums re-checked: 2517, 697, 190051).
- Energy past L_f: AX49 K17′ (Vorländer §6.4.1 Eq. 6.4), arithmetic redone (13.8155 × 0.312 = 4.310, giving −18.72 dB).
- Crossfade states share one input history: AX49 K23 (from the code).
- The fatigue effect of 30-presentation blocks: [Hyp]. Researcher: RQ-M3-1 (BS.1116-3 session length) bears on it.

**7. Hand-offs.**
- **Seat 2:** the T60 8 s scene with L_p < L.
- **Seat 3:** the shape of the fade and the per-stimulus checks.
- **Seat 5:** the flag and its isolation test.
- **Seat 8:** the voicing.
- **Seat 7:** the hours (+18 % or +36 %).
- **Seat 9:** the L4 label.

**8. Premortem.** If L4-B is adopted, the L4 test returns a predicted null, AX49 never reverses, and a producer reopening a long-reverb project on a slow 8-instance load hears the pad's reverb drop out 3.7 s after a release and then come back.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat1.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat4.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat5.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat6.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat7.md
- /home/user/makroof/docs/BUILD_PLAN.md (L170 AX47, L172 AX49)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md (item 14)
- /home/user/makroof/src/sim/Engine.h (L146–160, L293–309)
