SEAT 2 POSITION (narrow: A-iii, the L4 anchor only)

**1. Reading.** A-iii is a validation-only scalar gain on the whole rendered tail (specular and diffuse) from t_mix,e + 2.5 ms on. It exists so that a −3 dB anchor can be built on the L4 scene. That scene's specular share is 0.828, so `--abx-step-db`, which scales E_target (M1 = A), can go down by at most 10·log10(0.828) = −0.82 dB (file 38). Cues from my §4: cue 5 (which parameter deviates: the late level at a fixed decay) and my criterion 5 (honest about what a number measures).

**2. Ranking.** A-iii: **can live with.**

**3. Tension now: 1.**
- **M1 is not overturned.** M1 = A decides what the AX47 interim-to-final step is: a change in diffuse level, because that is what the engine changes between interim and final. A-iii adds a second, separate quantity: the level of the whole late tail.
- **What it is physically.** It is a uniform change in late-energy level at an unchanged T60 per band. To a listener that is a change in reverberant-to-early balance, so about 3 dB in C80 and D50 terms, about 3 times the C80 JND of 1 dB. Changing materials or geometry would not produce it: lowering the level by adding absorption would also shorten T60.
- **So it is a "tail step" in the parametric sense, not a room edit.** For an anchor whose purpose (Seat 1, file 38) is to check the chain and the listener's attention, not envelope sensitivity, that is enough. [Inferred]
- **On a fully diffuse scene (share 0) the two coincide.** A-iii equals `--abx-step-db -3` there, so it is a natural extension of the existing step rather than a different kind of stimulus. [Inferred, from the code's description in file 38: E′ = k·E_target, and the window holds no images.]

**4. Tension later: 1.**
- **The debt.** Two "3 dB tail step" quantities now exist. Someone could read an L4 anchor result as evidence about M1's E_target step, or use the flag for AX47, W-pin or 08-3 measurements. Either would quietly redefine M1.
- **Cost to undo.** Removing a flag is cheap. Re-running any measurement it contaminated costs a sitting.
- **Where the evidence arrives.** The first time a later phase cites an anchor result.

**5. Evidence.**
- −0.82 dB ceiling: file 38, 10·log10(0.828), redone.
- C80 JND 1 dB: ISO 3382 (my register; not re-checked against the corpus).
- A uniform late gain at a fixed decay leaves T60 unchanged: Kuttruff Eq. 5.24. The gain changes neither V, S nor α. [Inferred]

**6. Conditions** (each keeps the rating at 1/1; together they would lower "later" to 0):
- (a) **Name it as its own quantity.** Call it "anchor tail gain, total late level" in the flag name, the kit and the run sheet, and say there that it is not M1's step.
- (b) **Refuse it outside L4 anchor trials.** The kit refuses the flag outside the L4 anchor trials, and refuses it together with `--abx-step-db`. It never feeds the AX47 tolerance, the W pin or any 08-x record.
- (c) **Assert a uniform step.** It is a single broadband scalar applied after the band sum, from each emitter's own t_mix,e + 2.5 ms. The kit asserts that the realised step is uniform: within 0.05 dB per octave band and per emitter on the anchor IR, measured over [t_mix,e + 2.5 ms, L).
- (d) **Leave everything else untouched.** Everything before t_mix,e + 2.5 ms stays bit-identical to the unstepped IR (asserted), so only the late level moves.

**7. Hand-offs.**
- **Seat 5:** the flag's guard, AX5 determinism and the CI test.
- **Seat 1:** whether a −3 dB late-level step serves the anchor's purpose as well as +3 dB.
- **Seat 3:** condition 8 (the anchor stays on the L4 scene and chord, which A-iii keeps).

**8. Premortem.** If the gain is not kept separate, a later phase quotes "L4 anchor passed at −3 dB" as evidence for E_target steps. M1's meaning then drifts silently, and Seat 3 notices first, at 08-3.

Files read: /home/user/makroof/docs/review/phase-07c-2b/38-decider-l4-anchor.md
