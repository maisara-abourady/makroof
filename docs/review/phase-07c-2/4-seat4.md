<!-- Saved by the orchestrator from seat 4's report, 2026-11-22. -->

SEAT 4 POSITION (phase 07c-2, round 1). Corpus present (SOURCE_COMMIT c1b171f per the dossier). I did not re-read any corpus section myself. My corpus citations come through the researcher's dossier `docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md` and are marked that way.

# D-W1: W_max under (C)

**1. Reading.** This sets one per-emitter work count, and it decides how much restore time and background CPU every output mode inherits. Cues it triggers: *level and tone parity*; *over-resolved periphery* (CPU); the Phase 08-4 heaviest-mode restore gate (scope 10).

Load-bearing code facts:
- **The diffuse problem is mode-independent.** `DiffuseProblem` has no sample rate (F7 (2); wsweep Method). There is one solve per scene, shared across modes, and E_b is shared by both ears (AX39). So "one constant for all modes" holds by construction. W does not multiply by ears or modes. It adds to the binaural build; it does not scale with it.
- **Only Kind::Omni has a seeded tail today.** Binaural and stereoSpeakers are direct-only stubs (from the code: `Engine.cpp` L747–748, L824–834; `Cli.cpp` L656). The binaural cost on top of the solve is a Phase 08 unknown.

**2–4. Ranking, with tension now / later.**

| option | label | now | later | reason |
|---|---|---|---|---|
| W-6 bounded by W-5 | prefer | 1 | 1 | Smallest W that buys accuracy, so the least binaural restore and contention time and the least golden churn. Caveat: F4 shows both-near emitter-0 cases at SE 0.5–1.2 dB with U = 1 at ×16. No W meets the floor there (estimator change, out of scope §9). W-6 must name that class as excluded, or it never terminates. |
| W-1 | can live with | 1 | 1 | ≈ ×11 [derived: 3 s / 44.7 ns per scene eval ≈ 67 M; 05h single-thread figure, F2, on c309589]. The gated cubes saturate: low-α from ×2, +0.37 s on 14 × restore; flutter from ×4, +5.6 s Linux (T5). So the 08-4 gate is insensitive to W above ×4. |
| W-2 | can live with | 1 | 2 | ≈ 2 × W-1. The gated cubes are no worse, but ungated capped rooms (s = 1 cube, layouts 4/5) grow linearly under K-a. In binaural mode the user's large-room load is then synthesis(binaural) + a solve that is 2 × larger. T5: the s = 1 cube passes 30 s at ×4–×8 in omni already. |
| W-3 | can live with | 1 | 2 | Pool basis (≈ ×30). A user with 4–6 performance cores (R22) running a heavier binaural callback gets longer contention windows (F8 Linux overruns already rise with builders). |
| W-4 | cannot use as stated | 2 | 2 | At the pin, 8 × 100 m / 96 kHz final-settled is already 9.9–13.3 s (F6 (b)), which is above 10 s. Synthesis dominates, and binaural (two ears) makes it worse. A literal W-4 admits no raise, which conflicts with condition 3. Re-measured in the heaviest mode at 08-4, it would demand a W cut, which AX38 4c forbids. |
| W-5 | can live with | 1 | 1 | Only if its W-4 term is reformed (condition below). |

Keyless path:
- **K-a: now 1, later 2.** At 08-4 the heaviest-mode gate holds the binaural build plus the stage-1 solve. The macOS low-α margin at the S2 worst is 30 − 24.4 = 5.6 s in omni (T5). The binaural increment is unknown. The PR #33 macOS outlier is already at 30.50 s at the pin.
- **K-b: now 0, later 1.** The interim step is a per-band level step applied identically to both ears, because E_b is shared. It is a level change, not a spatial or interaural one [Inferred from AX39]. Its audibility is Seat 1's call.
- **K-c: unrated.** No candidate is on the table.

I accept the sequencing: value now, keyless path after the ABX, one golden round after both. The condition is that the golden round lands before the 08-4 golden freeze, which it does: 08-x are not started.

**6. Conditions.**
- **W-4** drops to 1/1 if it becomes "the solve-attributable share of the (iv) settle time ≤ its budget". Measure it in omni now and print it in binaural at 08-4. Never make it a gate that can force a W cut.
- **W-2 and W-3** drop to 1 if 08-4 scope 9 also prints the binaural restore and settle times at the s = 1 cube and at one layout-4 room at the chosen W. These are print only, not gated. Then the ungated user case is known before the freeze.
- **K-a** drops to 1 if the class (c) round sees an omni projection of the heaviest-mode margin (14 × restore at the chosen W) before choosing K-a.

**Companion items.**
- (b) Seats 2 and 3. Note only: the printed `nsPerEval` is half the per-scene cost (F-sheet), so any time budget built on it is low by a factor of 2.
- (c) Seat 5. The solve is mode-independent, so `solveRefMs` needs no per-mode re-pin at 08-4.
- (d) Seat 2.
- (e) Seat 5. Keeping v2 is fine from delivery: a keyless reload settles in one AQ4 step in every mode (F9, F10).
- (f) **Confirm.** 07c-2 lands before the Phase 08 goldens freeze, so no SE-derived tolerance is needed. Two conditions:
  - the 08-4 CHANGELOG records the achieved SE and U for any golden room still capped at the new W (print only);
  - any later W change is a binaural golden round.

  Phase 12 (ii) belongs to Seat 6. The AX41 n*_max-per-mode clause should not move, because W1's diffuse share is mode-independent [Inferred].
- (g) Not my matter.

**Debt.** Evidence arrives at 08-4 (heaviest-mode gate and binaural (iv) prints) and at 13 (strict register). Undoing W costs a golden round in omni, and in binaural too if it comes after 08-4.

# D-W2: AX47 self-ABX and L4 design

**1. Reading.** This fixes the playback chain for a tail-level-step ABX before binaural exists. Cues: *level and tone parity*, *measurement doubt*, and "judging in one's own room".

**2–4. X-1 to X-5.** The criterion and the family are Seat 1's ground. I rate all five 0 now and 1 later, for the same reason in each case: whatever criterion is chosen, its result holds only for the omni, diotic chain below. It must be re-read in binaural at 08-3.

**Sub-items (my mandate).**
- **Output mode: omni only.** The stereo and binaural stubs carry no tail (from the code), so a tail-level step cannot be rendered in them. The mono IR is presented diotically.
- **Headphones, not speakers.** A wired headphone with its model recorded. On speakers the listening room adds its own reverberation to the tail under test, which makes the result depend on the room. The producer also judges on headphones. No headphone compensation is needed: it weights A, B and X identically.
- **No per-stimulus loudness normalisation.** All stimuli are rendered at one fixed gain, with global headroom only. The step is the cue, so normalising A, B and X would remove it. Toole §17.3.1 says loudness must be matched closely in comparisons; here only the presentation level is held equal, never the step [corpus via dossier R7].
- **Fixed, recorded playback level, at or above a producer's monitoring level.** Increment thresholds fall with level: 0.93 dB at 35 dB SPL and 0.38 dB at 75 dB SPL for tone increments (R11; the condition differs: tones, transient). A quiet session biases toward "not detected". Record the digital pink-noise reference and the volume setting.
- **Chain hygiene.** 48 kHz with no OS resampling. Off: OS headphone virtualisers (macOS Spatialize Stereo, Windows Sonic or Atmos for headphones), loudness and EQ enhancers, player ReplayGain. No Bluetooth lossy codec. Record the SHA-256 of every stimulus file in the sealed answer file.
- **L4** uses the same chain: omni, diotic, headphones.
- Step direction, timing and material belong to Seats 1, 3 and 8. The speech licence belongs to Seat 7.

**Debt.** Binaural decorrelates the two ears' tails. Whether a diotic level-step threshold transfers to a decorrelated binaural tail is [Hyp], and the researcher should verify it. Evidence arrives at 08-3 listening. If binaural detects a step that omni did not, the AX47 reversal goes to 0.5 dB: the interim-check bound moves from −18.27 to −24.55 dB and class (c) is re-decided. That is a parameter change plus one board round, not a rewrite.

**Condition.** The AX47 and L4 result is recorded as "omni, diotic, headphones [model], level [x]". 08-3 adds one confirmatory 16-trial binaural ABX at the bound in force, if class (c) relies on it.

**7. Hand-offs.**
- Statistics, family and power: Seat 1.
- Step rendering: Seat 3.
- Determinism of the stimuli: Seat 5.
- Speech licence: Seat 7 and a human.
- Running the listening test: Maisara (a person's action).

**8. Premortem.** The ABX passes at 1 dB in omni, diotic. At 08-3 the binaural interim step is heard as a tail "bloom" on headphones. Maisara notices first, and class (c) is reopened after the goldens are frozen.

Files read:
- /home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md
- /home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md
- /home/user/makroof/docs/phases/phase-07c-2.md
- /home/user/makroof/docs/phases/phase-08-4.md
- /home/user/makroof/src/sim/Engine.cpp
