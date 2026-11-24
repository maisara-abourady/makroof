# 31: Decider round 4 on the D-W2 ABX kit. M1 and M2 are decided; M3 goes back to the seats (CONVENE)

Corpus revision c1b171fe.

**PRD digest (changed from file 27 only here).**
- NFR-8, read in full (PRD L112): "Any valid scene renders correctly; no environment-specific code paths."
- The bounds are AX47's Reversal ("capped layout-4 scene"), item 3's thresholds with α 0.049, item 4's rule, and NFR-8.
- AX47 is a board row, not one of Maisara's recorded decisions. A board DECISION through /fix-plan can change it.

## M1: what item 5's step scales (A, the whole E_target; B, E_diff only)

| seat | status | reason |
|---|---|---|
| 1 | not required | Item 5 already fixes the perceptual quantity (g, the same in every band). M1 is about how the stimulus is built to meet it. |
| 2 | convened | E_target is the representation handed to the renderer (Engine.cpp L183). Rated in file 30. |
| 3 | convened | Tail rendering. Rated in file 26. |
| 4 | not required | Omni, diotic; no delivery quantity is involved. |
| 5 | not required | A validation flag, run offline; src/plugin never reaches it. |
| 6 | not required | No user control. |
| 7 | not required | Both options are the same one-parameter cost. |
| 8 | not required | A validation stimulus. |
| 9 | not required | No room or label question. |

| option | S2 | S3 | max | sum |
|---|---|---|---|---|
| A | 0/0 | 0/0 | 0 | 0 |
| B | 1/2 ("not uniform across all 8 bands") | 1/2 ("step shrinks and stops being uniform") | 2 | 6 |

- **DECISION A.** Confidence high. The future-debt register is empty: no seat rated A later ≥ 1.
- Seat 2's caveat goes on record: the stepped IR is a stimulus, never a room prediction.
- **D5-L1:** E′_target = k·E_target (Cli L788), and the window holds no images after t_mix,e + 2.5 ms (NoiseTail L278–279). File 28 rated this CORRECT.
- **Item-5 sentence:** file 27's sentence, with its last clause replaced by: "The kit refuses (1) a down-step when E_target's specular share exceeds k, i.e. g < 10·log10(share), and (2) any step in a band whose tail target is specular-only (Cli L781–786)."
- The summary's "sum 1" is corrected to 0.

## M2: which T30 Q5 uses

| seat | status | reason |
|---|---|---|
| 1 | convened | The signal and the onset window. |
| 2, 3, 4 | not required | Both options read the same IR, the same IrSets and the same omni chain. |
| 5, 6, 8 | not required | No thread, control or workflow is involved. |
| 7 | not required | T-b's reseed costs minutes. |
| 9 | convened | The ceiling and the T30 label. |

T-a is S1 0/1 and S9 1/1 (sum 3). T-b is S1 1/1 and S9 1/1 (sum 4). Both have a maximum of 1.

**DECISION T-a**, with Seat 9's manifest label. Confidence medium.

**Debt register (restored):**

| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | Any other scene uses its own heard-IR T30. K4 gives 1.288–2.575 s, and Q5 was never run on a candidate. Seat 1's 0 now rested on "gap longer than the tail's own decay". That must be shown again wherever the heard T30 is at or below the tail T30 (e.g. listener_corner, 1.288 s). | Minutes for a Q5 rerun; reseal if it fails | When M3 fixes any second scene, before its seal | Q5's ≥ 20 dB assertion passes there, with the heard and tail T30 both printed |
| 9 | 2.009 s is a fit across the AX21 gap, not a decay rate | Relabel | At seal | The manifest carries the label |

## M3: CONVENE

| seat | status | reason |
|---|---|---|
| 1 | convened | Sensitivity (ΔG, ΔC80) and the α treatment |
| 2 | convened | The early/late split, layout 5, the B11 trigger |
| 3 | convened | The s < 1 stimulus and the click events |
| 4 | convened | Item 15's binaural rerun |
| 5 | convened, narrow | A false "detected" sets 0.5 dB, which raises the admission cost (SE ≤ 0.25 dB). The α choice changes how likely that is. |
| 6 | convened, narrow | The same question, as load time the user sees |
| 7 | convened | Listening hours and sessions (file 28) |
| 8 | not required | A validation stimulus; item 13 forbids public copy |
| 9 | convened | Labels, representativeness, layout-5 provenance |

**Faithful map of the rated options** (now/later; c = read from conditions):

| option | S1 | S2 | S3 | S4 | S7 | S9 | max |
|---|---|---|---|---|---|---|---|
| S-A, no (ii) | 2/2 | 1/1 | 2/2 | 0/2 | 0/2 | 2/2 | 2 (sum 18) |
| S-A′ (file 27) | 2/2 | 1/1 (trigger narrowed) | 2/2 | 0/1 | 0/2 | 2/2 | 2 (sum 17) |
| S-C | 0/0 | 2/1 | 2/2 | 0/2 | 1/2 | 2/2 | 2 (sum 16) |
| S-B, capped (s 0.7–0.9) | 2/2 (its condition "ΔG, ΔC80 ≥ S-A's" is unmet, K4) | 1/1 c | 1/1 | 0/1 | unrated | unrated | 2 |
| S-D (Seat 1's) | 1/0–1 | unrated | unrated | unrated | unrated | unrated | — |

- Seat 9 rated the 0.43 ceiling 1/1 on every option. It goes in the register.
- **Why no option can reach 1 on a single scene:**
  - Seat 1 needs at least S-A's sensitivity. Only the s = 1 scenes give it.
  - Seats 3 and 9 need an early part that is not empty. Only the s < 1 scenes give it, and all of them are less sensitive (K4 facts 2, 4, 5).
  - Any option with a maximum of 1 therefore uses two scenes, and no seat has rated one.

**Answers to file 28.**
1. Neither is in amendment 4. The S-A′ cells for Seats 1, 3 and 9 are 2/2 (map above). I withdraw file 27's M3.
2. None. Under Vorländer Eq. 6.7, the images from 59.7 ms onward sit unscaled in both C80 windows. K4 gives |ΔC80| of 0.076–0.860 dB, against 0.900 dB. I withdraw the ΔC80 filter and file 27's reversal condition.
3. No. s = 0.25, 0.3 and 0.4 are uncapped at every m, and s = 0.6 is capped at m = 6 and 7 only. Under "capped", S-B at s ≤ 0.6 is out.
4. **Bonferroni arithmetic** (Binomial(16, ½); powers at p = 0.75):
   - P(≥12) = 2517/65536 = 0.0384, power 0.630.
   - P(≥13) = 697/65536 = 0.0106, power 0.405.
   - P(≥14) = 137/65536 = 0.0021, power 0.197.
   - One scene's family is 0.049. Two unsplit families give ≤ 0.098. The only split that fits 0.0245 per scene is noise ≥ 13 with speech ≥ 13 (0.0213), which cuts noise power from 0.63 to 0.405.
   - **For rating:** no split. Each scene is its own family at item 3's thresholds, and item 4 applies in each family. The record states a union rate ≤ 0.049 × families.
   - Item 15(i) is already an undeclared unsplit second family; the amendment declares it.
5. **Reconciliation with AX47.** The 1 dB bound rests on D-C1 (Vorländer Table 6.1) for every valid scene. The ABX can only tighten it, and running it is the procedural gate on statistical sources. So a non-detection supports nothing elsewhere.
   - **Item 13 wording:** "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states."
   - AX47 needs no change for this.

**Click events: K5, builder, before any seal.**
- Two candidates failed item 6 at the click detector, one stimulus each:
  - listener_corner, at 3.537 s;
  - both_wall, at 3.491 s.
- The builder should:
  - place each event against the step onset, the AQ4 fade, the pulse edges and the partition boundaries;
  - run the detector on the unstepped render and on A−B;
  - print the W-a margins.
- This must come before sealing, even on S-A, for two reasons:
  - If the clicks are real and lie in the step or fade path, they are a non-level cue that could confound any scene's ABX (FR-SIM-6, NFR-3). They would also be an NFR-8 L112 report.
  - If they are false, both scenes re-enter Seat 1's pool, and both_wall (share 0.667) would top layout 4.
- Nothing is tuned. Seat 3 reads the outcome.

**K6:** stimulus durations from manifest.json, to put Seat 7's session hours on a number.

**New options to rate.**
- Every scene in them must be: capped at m = 6, 7 and 8; clean on item 6 including K5; rerun through Q5; at a peak of −1 dBFS or below.
- **S-B\*** is layout4_s0.7 (early part −3.8 dB re direct) or layout4_s0.9 (|ΔC80| 0.86). The seats pick.
- **S-W** is Seat 1's rule: among the qualifying scenes, the one with the largest tail share.

The four options:
- **V1:** 07c-2 runs S-A and S-B\* as two families. At 08-3, (i) S-A binaural and (ii) S-W binaural.
- **V2:** 07c-2 runs S-W (layout-4 placements, so AX47 is unchanged; all of them have a listener or emitter 0.1 m from a face). At 08-3, (i) the same scene and (ii) S-B\*, guaranteed.
- **V3:** V2, with layout5_s1/default (default placement, share 0.579) or layout5_s1/emitter_wall (0.869) added to the S-W pool.
  - **V3 needs a /fix-plan to AX47's Reversal:** "capped layout-4 scene" becomes "capped layout-4 or layout-5 scene".
- **V4:** 07c-2 runs S-A. At 08-3, (i) S-A and (ii) S-B\*, guaranteed and held in the same sitting (Seat 7's rank 2).

**Briefs.** Every seat reads files 28 and 29 and this file, and rates V1–V4 now and later, with its conditions. Seat-specific questions:
- **S1:** your S-W pick under each K5 outcome. Is S-B\* worth a family at all? Split or unsplit α. Does the T-a premise hold on your pick?
- **S2:** layout 5's provenance as an AX47 scene. The AX21 jump at s = 0.7 and 0.9. The trigger wording "on any B11 promotion, stimuli rebuilt before the next listening session".
- **S3:** does a 07c-2 or an 08-3 s < 1 run meet your "before 08-3"? s = 0.7 or 0.9? How do you read K5?
- **S4:** the 0.1 m placements in binaural, and layout5/default.
- **S5, S6:** split or unsplit only: the cost of a false-reversal rate of up to 0.098, or 0.147 with three families.
- **S7:** V1–V4 against K6's hours, and split or unsplit.
- **S9:** whether s = 0.7 or 0.9 is representative, layout-5 provenance, an S-W label, and the 0.43 ceiling on each option.

## Amendments to file 13 (now; thresholds, α, trial counts and item 4 unchanged)
- **Item 5:** the sentence above.
- **Item 6:** file 27's amendment 1, which file 28 rated faithful.
- **Run sheet:** T-a's manifest label.
- **Held for M3:** items 9, 13 and 15. That includes the item-9 label, with r/r_c 3.47 and diffuse-field D/R −10.8 dB (Kuttruff Eq. 5.44, A ≈ 640 m²).

## Decided for Maisara
Acceptance check for M1 and M2: NFR-1 and NFR-8. No hard constraint is broken, and no PRD goal points to another option. Nothing amends one of her recorded decisions.

- **M1 A:** serves NFR-1 (the step is exactly g in every band) and NFR-8 (no scene-specific path). **B** strains NFR-1: it under-steps toward non-detection. Seats 2 and 3 gave nothing up.
- **M2 T-a:** neutral on NFR-1 (the ≥ 20 dB assertion governs) and keeps the realisations. **T-b** is neutral on NFR-1 but reseeds every stimulus. Neither touches NFR-8. Seat 1 gives the most and gets back the Q5 rerun on any second scene.
- **M3, provisional (the seats are still rating):**
  - **S-A and S-A′** strain NFR-1 (ΔG is only 0.045 dB) and NFR-8 L112 (one class of evidence for a bound that covers every valid scene).
  - **S-C:** a stronger G cue, but the early part is still empty, which strains NFR-1. Same one-class strain on NFR-8.
  - **S-B\*:** serves NFR-1's representativeness and strains its sensitivity. It adds a second class for NFR-8.
  - **V1–V4** each serve NFR-8 L112 with two classes. V3 also changes AX47 through the board, not the PRD.
  - **The click events** need an NFR-8 report if they are real.

**NEEDS MAISARA:** none. Whether she can sit for about 3 h at 08-3 is a person's action (item 16).

## Summary

| id | decision | state | worst cell | sum | confidence | reversal condition |
|---|---|---|---|---|---|---|
| M1 | A, with the two-refusal sentence | proposed | 0 | 0 | high | an item-6 failure on any scene |
| M2 | T-a, with the label | proposed | 1 | 3 | medium | Q5 fails on a second scene |
| M3 | V1–V4 and the α treatment | convening | — | — | — | — |

Files:
- /home/user/makroof/docs/review/phase-07c-2/28-interrogator-on-file27.md
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/30-seat2.md
- /home/user/makroof/docs/review/phase-07c-2/30-seat7.md
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md

**CONVENE** Seats 1, 2, 3, 4, 5, 6, 7 and 9, plus the builder for K5 and K6.
