
# 6: Decider on M3, rebuttal round (phase-07c-2b scope 2, round 2)

Read-only. To be saved as `/home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`).

**Re-checked this round:**
- Kuttruff §5.6: Eq. 5.42 (w_r = 4P/cA), Eqs. 5.44–5.45, and the caveat after Eq. 5.48 ("questionable if ᾱ is not small compared with 1").

**Files read:**
- Seat files 4-seat1 to 4-seat9, including Seat 3's addendum.
- Builder file 5.
- Interrogator file 3.
- My file 2.
- AX47 and AX49 rows (BUILD_PLAN L170, L172).
- Run sheet L135–147.
- phase-07c-2b.md L36 and L118–131.
- `src/cli/Cli.cpp` (flag guards L341–372) and `src/sim/OfflineRender.h` (L5–7, L20–33).

## PRD digest (unchanged from file 2, with corrections)

- **For whom:** producers and DJs (L17). Validation stimuli are never public copy.
- **Outcome:** NFR-1 (L105): rendering "must match impulse responses measured in real spaces and pass listening tests".
- **Accuracy ranking:** L49 and L101 rank accuracy against **CPU and latency**, not against listening hours. (Correction: file 2 read them more broadly.)
- **Hard bounds:**
  - NFR-8 (L112) is a rendering requirement, with no environment-specific code paths. It says nothing about the order in which evidence arrives. (Correction.)
  - FR-3D-5 (L75): placements anywhere.
  - L54 and L133: spaces are empty.
  - Her AX21 decision of 2026-11-05.
  - The AQ/AX rows, except AX47's Reversal and design (M3-2) and AX49's `render_cli` sentence (M3-7).
- **Not bounded:** hours (L55, L174: no deadline).
- **Verification:** every DSP behaviour is checked automatically, nothing is loosened to pass, and a red is a stop.

---

## Answers to the interrogator's five questions

**Q1. Seat 7's now cell.**
- Seat 7 gives **1/1**: "I confirm 1/1. The reason for the now cell is corrected" (4-seat7).
- Its likely bill is about 2.5 h, inside its tolerance.
- So V1-W's highest cell is 1. The contingency in file 2 does not arise, and I **withdraw** the contingent FOR MAISARA reasoning.
- I concede the interrogator's reading: L49 and L101 rank accuracy against CPU and latency, NFR-8 does not order evidence, and L55 leaves hours unbounded rather than ranked. No PRD id separates V1-W from V2 or gated S-B\* on hours. Had Seat 7 rated 2, the V2-versus-gated tie would have gone to reversibility, and the acceptance check would have found no PRD id pointing away from the ordering's winner.

**Q2.**
- M3-1's acceptance check now shows all six surviving options (see M3-1 below).
- M3-3 shows its four options against **NFR-1 only**. FR-SIM-6 and NFR-3 are about movement, and the AX47 step is an IR update, so I drop FR-SIM-6.

**Q3. Seat 3 on HF-W:** **1/1**, provided condition (a) is met, plus (b) (4-seat3 addendum).
- (a) asks that the per-scene worst ratio, margin and skipped-frame count be cited. File 5 L61–71 now cites them (both_wall 1.0002 / 0.560 dB / 0 skipped; s0.7 1.0003 / 0.559 dB / 0 skipped; 2100 frames each). Seat 3 could not find them when it wrote. The session brief must cite them.

**Q4. Render flag, AX49 exception and pre-seal build.** Conceded as UNDERCONVENED in file 2. These three are decided below (M3-7), on the round-2 ratings of Seats 3, 5 and 7, plus Seats 1, 2, 8 and 9.

**Q5. Seat 4 accepts the narrowing**, 0/1 confirmed: "The (i) label limits what a non-detection means. It does not limit what a detection means" (4-seat4 (2)). Seats 1, 5 and 6 also confirm F1–F4, including (i).

**Corrections accepted from file 3:**
- Seat 6's cells on the V2, V3 and V4 rows are 0/0, and the "higher of the two α cells" header is withdrawn.
- V1′ is excluded at step 3. Seat 1's later 3 on it is marked as an unconfirmed reading.
- "V2 would win on sum" becomes "V2 and gated tie on sum; reversibility decides". It is now moot.
- s0.9: only Seat 3 said "can live with". Seat 1 named it first choice. Seat 2's "Any S-B\*" conditions cover it, and Seat 9 supplied its label values. Seats 2 and 9 did not rate it.
- "V2 strains NFR-8" is withdrawn.
- "Same or next day" becomes "the same day" (Seat 1: "Same day: yes").
- Labels get "indicative" and Eqs. 5.44–5.45 (see M3-4).

---

## Knowledge inventory (round 2)

| K | what must be known | source | status |
|---|---|---|---|
| K1 | V1-W cells, all seats | 4-seat1 to 4-seat9 (own words) | known |
| K2 | both_wall per-emitter tail level at equal times | file 5 table: −0.05 / −0.03 dB; t_mix,e 0.165 / 0.380 s | known (builder measurement, scratchpad method; the kit must print it at seal, see M3-1) |
| K3 | both_corner spread 6.2 dB | file 5 fact 2 | known (measurement); the "should be equal" expectation is Kuttruff Eq. 5.42, **indicative** at ᾱ ≈ 0.28 (§5.6 caveat) |
| K4 | HF-W on both scenes: worst ratio 1.0002 / 1.0003, margin 0.560 / 0.559 dB, 0 skipped of 2100 frames | file 5 L61–71 | known (two scenes only) |
| K5 | M2 gaps: both_wall 1.376 ≥ 1.313 s; s0.7 1.835 ≥ 1.274 s; tail T30s | file 5 | known |
| K6 | binomial tails | Σ C(24,k), k = 18..24 = 190051 (134596 + 42504 + 10626 + 2024 + 276 + 24 + 1); /2²⁴ = 0.011328; 697/65536 = 0.010635 | known (recomputed) |
| K7 | α cells under the 24-trial split | Seats 1, 5, 6, 7 (4-seat\*) | known |
| K8 | **Seat 1's speech-also-18/24 option, Seat 7's cell** | not rated | **uninformed, so the speech criterion is deferred (R3)** |
| K9 | K23: both crossfade states read one input history | AX49 row (code fact) | known |
| K10 | offline `render_cli` uses one full-length double-precision FFT for long IRs; the partitioned path is `--realtime-emulation` | from the code: `OfflineRender.h` L5–7, L20–33; `Cli.cpp` L341–372 | known |
| K11 | energy past L_f = e^(−13.82·0.312) = 0.0134 (−18.7 dB) | AX49 K17′ (Vorländer §6.4.1 Eq. 6.4), arithmetic redone | known |
| K12 | S′ per-band T60 starting values | Seat 2 [Inferred], Kuttruff Table 6.1 | under-informed. Not load-bearing: S′ is defined by an asserted engine print (8.0 ± 0.1 s), not by the table |
| K13 | Seat 1's frozen-spec cell | not rated | uninformed. Not load-bearing for the chosen option (see M3-7) |
| K14 | L4 stimulus length | ≥ 0.5 + 0.02 + 4 + 0.01 + 12 = 16.53 s (Seat 1's envelope, L = 1.5·8) | known (derived); the pace is Seat 7's [Hyp] |

---

## M3-1: the scene, final

**Tension map** (round-2 words; Seat 8 not required, 0/0; Seats 5 and 6 rated under the 24-trial split, which M3-2 decides):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| **V1-W** | **0/1** | 1/1 | 1/1 | 0/1 | 0/1 | 0/1 | 1/1 | 1/1 | **1** | **12** |
| V2 (conditions met) | 0/1 | 1/1 c | 2/2 | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 c | 2 | 13 |
| Gated S-B\* | 0/1 | 1/1 c | 2/2 c | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 c | 2 | 13 |
| V3-default | 1/1 c | 1/1 | 2/2 | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 | 2 | 14 |
| V3 as written | 1/1 | 2/1 | 2/2 | 0/1 | 0/1 c | 0/0 | 1/1 | 2/1 | 2 | 16 |
| V1 | 2/2 | 1/1 | 1/1 | 0/2 | — | — | ·/2 | 1/1 | 2 | not needed |
| V1′ | 2/3 c (unconfirmed) | — | — | 0/1 | — | — | 2/2 c | — | ≥ 2 | out at step 3 |
| V4 | 2/**3** | 1/1 | 2/2 | 0/1 | — | 0/0 | 0/2 | 1/2 | veto | — |

**The V1-W cells, in each seat's words:**
- **S1, 0/1:** "I re-rate it 0/1 … The decider adopted every one of my V2 → 0/0 conditions"; later, "S-W's rank rests on ΔG and ΔC80 alone, and 08-3 (i) is a near-wall binaural scene".
- **S2, 1/1:** "confirmed at 1/1". The labels meet its conditions. New condition: every absent face is named in a fallback label.
- **S3, 1/1:** round 1, unchanged.
- **S4, 0/1:** "confirmed at 0/1". B14, the static generic head, and the trigger keep it at 1.
- **S5, 0/1:** "Under the 24-trial split it becomes 0/1".
- **S6, 0/1:** "My round-1 cell '1/1 c' becomes 0/1".
- **S7, 1/1:** "about 2.5 h on the critical path … now 1"; "Later: 1, as before".
- **S9, 1/1:** confirmed with the tail-spread condition. "Without this condition, later is 2."

**Seat 9's condition is met (file 5):**
- At the same absolute windows the two tails agree within 0.05 dB at 1 kHz, so the SPREAD clause does not fire.
- The share 0.667 comes from emitter L's earlier t_mix,e (0.165 s against 0.380 s): "0.215 s of a 1.29 s decay is 10.0 dB of energy".
- To keep the condition met, it is made a kit print at every seal (below), and the onset is stated in the label and in item 13.

**Working:**
1. **Bounds:** none of the options breaks one.
2. **Veto:** V4 is out (Seat 1, later 3).
3. **Worst-off seat:** V1-W is the only option whose highest cell is 1. Every other survivor holds a 2: Seat 3's on V2, gated, V3-default and V3 as written; Seats 1, 4 and 7 on V1; Seat 1's now 2 on V1′.
4. **Compose:** not needed.
5. **Sum:** not needed. (V1-W's 12 is also the lowest.)
6. **Reversibility:** not needed.

**DECISION M3-1 (stands, with corrections): V1-W, as in file 2**, plus these changes:
- **(a) Tail-spread print at every seal.** For each scene sealed as S-W, and every fallback, the kit prints per-emitter t_mix,e and the L − R octave level at 1 kHz over the absolute windows [0.45, 0.65) s and [0.8, 1.0) s (file 5's windows, after every layout-4 t_mix,e).
  - If either window exceeds 1 dB (Vorländer Table 6.1 jnd for G), the label's SPREAD clause fires and an NFR-8 report goes to Seat 2.
  - The item-13 record names the onset and the spread.
- **(b) Fallback labels** name every face whose reflection is absent (Seat 2) and use Seat 9's template (M3-4). Seat 9 confirms the filled text before the seal.
- **(c) Item 15 / 08-3 rebuild gap.** If the M3-8 trigger rebuilds a scene and the rebuild fails a seal gate, item 15 returns to the board before any 08-3 listening. This is Seat 4's hand-off to Seats 1 and 5. I do not decide it unrated.

**Load-bearing claims:**
- **R2-L1 (file 5, builder measurement):** both_wall L − R is −0.05 dB and −0.03 dB at equal windows; t_mix,e is 0.165 / 0.380 s.
  - Check from the code rule (K20, AX49 row): t_mix,e ≥ t_dir,e + max(20 ms, √V ms).
  - Working: 29.95/343 = 87.3 ms, plus √6000 = 77.5 ms, gives 164.8 ms, matching 0.165 s.
- **R2-L2:** file 2's D-L1 to D-L9 stand (interrogator: CORRECT).
- **R2-L3 (product):** FR-3D-5 L75 makes the 0.1 m placements valid; L133 keeps "occupied" out.

**Future-debt register (V1-W):**

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | S-W ranked on ΔG and ΔC80 only; (i) is near-wall binaural | reseal hours | 07c-2b sittings; 08-3 | results recorded per family |
| 2 | 08-3 (i) is binaural with the wall reflection missing; fallback labels must name every face | about 2 h rerun | 08-3 | (i) labelled; Seat 9 confirms filled labels |
| 3 | s < 1 evidence (F2) before O4; 08-3 S-W empty-early | none extra | 07c-2b, 08-3 | F2 recorded before O4 |
| 4 | B14, a static generic head, (i) as chain comparison only. The trigger (expected at O4) voids the cross-chain comparison unless the omni family is rerun; the rerun branch adds about 2.3–4.5 h | one session | 08-3 | per-ear prints, label, rerun or void recorded |
| 5 | a correct or false flip can land at 08-3, after admission | a constant change under C1 | 08-3 | C1 in place (M3-2) |
| 6 | 2.3-point noise power loss per family (W4) | class (c) re-decision | 08-3; Phase 13 beta | AX38 (iv) prints |
| 7 | about 3 h (up to about 5 h) in 07c-2b and about 2.3 h (up to about 4.5 h) at 08-3 (M3-6 below) | listening hours | each sitting | dates in the briefs |
| 9 | the 0.43 ceiling (binds on both_wall, 0.639 against 0.589 s); "represents no seat"; S-W's share rests on L's t_mix,e onset, so a t_mix,e rule change halves ΔG (Seat 9: about 0.28 dB) and fires M3-8 | rebuild and reseal | each seal; O4; 08-3 | trigger applied; onset printed and in label |

**Strongest objection:** Seat 9's premortem, that S-W's sensitivity rests on the current t_mix,e rule.
- **Why it holds anyway:** that onset is the engine's shipped behaviour, so it is what a user hears. The trigger names "the t_mix,e rule", and the label and item 13 now state the onset. A null is scoped to that scene.
- **When it would fail:** if a `src/sim` change moves L's onset before 08-3. Then (i) is rebuilt and its share is re-printed.

**Confidence:** high on the choice. No cell is read for V1-W, and every acoustic number is corpus-derived or measured.

**Reversal conditions:**
- a seal gate fails and the fallback order is exhausted;
- a clean stimulus fails HF-W;
- the tail-spread print exceeds 1 dB at a rebuild.

**Acceptance check for Maisara (PRD ids: NFR-1 L105, FR-3D-5 L75, L133/L54, AX21 decision, L55):**
- **V1-W:** NFR-1, with the most sensitive measured scene plus an early-part scene before the pin. FR-3D-5 placement. L133 labels. AX21 applied. Hours unbounded (L55).
- **V2 (conditions met):** NFR-1, with the same sensitive scene. FR-3D-5 and L133 met. One class only. No PRD id ranks it above V1-W.
- **Gated S-B\*:** as V2, with S-B\* conditional. No PRD id ranks it above V1-W.
- **V3-default:** NFR-1, with a less sensitive scene. Needs an AX47 change. No PRD id ranks it above.
- **V3 as written:** NFR-1, with a less sensitive scene (emitter_wall). No PRD id ranks it above.
- **V1:** NFR-1 strained, because the two least sensitive scenes come before the pin. Points away from itself.

No PRD goal or ranked requirement points to another survivor over V1-W, so the check passes. The choice among the survivors is the board's, on cost.

---

## M3-2: α

**Map** (round 2):

| option | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| Unsplit + C1 | 1/1 | 1/1 | 1/1 | 0/1 | 1 | 7 |
| **24-trial split** (noise ≥ 18/24, speech ≥ 13/16) | 1/0 | 0/1 | 0/1 | 1/1 | 1 | **5** |
| Speech also ≥ 18/24 (Seat 1's) | 0/0 | 0/1 c | 0/1 c | **not rated** | ≥ 1 | 2 + S7 |
| 13/13 split | — | — | 1/2 | — | 2 | out |

**The cells, in each seat's words:**
- **S1:**
  - Split: "Now 1 (−0.023 power…). Later 0".
  - Unsplit: "Now 1 … Later 1 (0.196 …)".
  - Speech-also: "Tension 0/0 for my seat … I prefer it but do not require it".
- **S5:** split "0/1"; unsplit "1/1 (confirmed)".
  - Speech-also is read from Seat 5's own split reason (≤ 0.0453 is still "below the single-family 0.049"; a later flip can still land at 08-3).
- **S6:** split "0", later "1" (noise power); unsplit 1/1.
  - Speech-also is read from Seat 6's split reasons (the same noise design, nothing changes at load).
- **S7:** split "now 1 … later 1 (speech power 0.41)"; unsplit "now 0, later 1".

**Seat 7's later reason on the split.** I do not re-rate it, but it rests on a misread premise. Speech passes at ≥ 13/16 under both unsplit and the 24-trial split (run sheet L136; Seat 1's table), so speech power is 0.405 under both. Seat 7 is asked to re-check this (R3). Whatever it answers, the split's sum is ≤ 5 < 7.

**Working:**
1. **Bounds:** none of the options breaks one.
2. **Veto:** none.
3. **Worst-off seat:** unsplit and the split both have max 1. Speech-also is undetermined: Seat 7's cell is missing, and its hours rise by about +36 % per scene (Seat 1).
4. **Compose:** none.
5. **Sum:** the split (5) beats unsplit (7).
   - Speech-also beats the split if Seat 7 rates it at most 1 in each column (sum ≤ 4).
   - It loses if Seat 7 rates now 2.
   - That one cell decides it, and it is a gap (K8).

**DECISION M3-2 (noise and families now; speech criterion deferred to R3):**
- **Unsplit is out** (sum 7 against ≤ 5).
- **Noise chain, in all four families F1–F4:**
  - 24 scored trials plus 6 anchors (30 presentations);
  - a break after presentation 15;
  - **3 anchors in each half** (Seat 1);
  - detection at **≥ 18/24**; anchor pass at ≥ 5/6 over the block, otherwise void with one rerun (run sheet L146).
  - The same design applies to the 0.5 dB block and at 08-3 (Seats 1, 5, 6, 7: F3 and F4 the same as F1 and F2).
- **Speech chain:** ≥ 13/16 or ≥ 18/24, decided after R3.
- **The numbers:**
  - **Speech ≥ 13/16:** per family 0.011328 + 0.010635 = **0.021963**; at 07c-2b (F1, F2) **≤ 0.0439** (Seat 5's correction of my 0.0438 is right); over F1–F4 **≤ 0.0879**. Noise power at p = 0.75: **0.607**.
  - **Speech ≥ 18/24:** per family 0.022656; at 07c-2b **≤ 0.0453**; over F1–F4 **≤ 0.0906** (Seat 1's 0.0905 is a rounding slip). Speech power 0.607.
- **C1 attaches under either option** (Seat 5: "C1, first branch, should attach under either α option … it is cheap, and I still ask for it"). Seat 6's (i) and (iv) also apply under the split, and no seat rated against them.
- **Fallback (Seat 6):** if the trial count is cut after K6, all four families revert to unsplit + C1, never 13/13. Such a change is admissible only before any scored trial, in the pre-registration commit (Seat 1).
- **F1–F4 declaration:** confirmed by Seats 1, 4, 5 and 6, plus Seat 6's (b) and (c).
- **Item-13 null wording:**
  - noise: "not detected in 24 trials by one listener (power 0.61 at p = 0.75)";
  - speech: "16 trials (power 0.41)", or "24 trials (power 0.61)" after R3.
- **AX47 `/fix-plan`** (one edit, after R3):
  - The Reversal reads: "If the 07c-2b self-ABX (two capped layout-4 scenes, F1 S-W and F2 S-B\*, each its own family) or its 08-3 binaural rerun (F3, F4; item 15) detects a step below 1 dB, the bound becomes 0.5 dB."
  - The design sentence carries the thresholds and rates above, plus a §6 row.

**Not adopted, unrated:** Seat 7's skip of S-B\*'s 0.9 dB blocks after an S-W detection. It changes the pre-registered design and Seats 1, 5 and 6 have not rated it (R3).

**Debt (split):**
- S1, later 0.
- S5: a flip at 08-3. Repaid by C1.
- S6: power loss. Repaid by the AX38 (iv) prints.
- S7: +17–34 min at each of 07c-2b and 08-3.

**Confidence:** high on "unsplit out" and on the noise design; the speech criterion is pending.

**Acceptance check (NFR-1 L105, L55):**
- **Split:** serves NFR-1, halving the false-reversal rate for −0.023 noise power.
- **Speech-also:** serves NFR-1 most (speech power 0.607); costs hours, which L55 leaves unbounded.
- **Unsplit:** serves NFR-1 with higher power at p ≤ 0.77 and twice the false-reversal rate.
- The PRD ranks none of these against the others.

---

## M3-3: HF-W, final

| option | S3 | S5 | max | sum |
|---|---|---|---|---|
| keep the peak-frame check | 2/2 | 1/2 | 2 | 7 |
| Seat 5's (a) | 1/2 | 1/0 | 2 | 4 |
| A−B, literal | 2/2 | 1/1 | 2 | 6 |
| HF-W without D | — | 1/2 | 2 | — |
| **HF-W + condition D** | **1/1** (addendum) | **1/1** (4-seat5: "1/1 with condition D") | **1** | **4** |

**DECISION M3-3 (stands, revised):** HF-W as in file 2, plus:
- **Seat 5's D:**
  - in a skipped frame, assert E_o ≤ β·n_f·10⁻⁹;
  - print the skip count;
  - if any scene skips a frame inside [N, N+L), add an N1 variant with the spike in a skipped frame.
- **Seat 3's (a):** the brief cites file 5 L61–71 per scene. **Seat 3's (b):** every M3-8 rebuild prints the worst ratio, margin and skip count.

**Status of the commutator assumption:** measured on two scenes, not general. Worst ratio 1.0002 / 1.0003 against β = 1.1378 (margin 0.560 / 0.559 dB).

**Debt:**
- S3 later 1: the commutator is unmeasured beyond these scenes. Repaid at each rebuild print.
- S5 later 1: the CI plumbing.

**Strongest objection:** a defect that stays under 0.56 dB per frame. Companion (ii) catches it exactly (Seat 3's premortem).

**Confidence:** high.

**Acceptance check (NFR-1 L105, "pass listening tests"; the stimulus gate is what makes a detection a detection of the step):**
- **Keep peak-frame:** its K5 false positives block clean scenes. Strains NFR-1.
- **(a):** serves NFR-1, but is not derived per frame.
- **A−B, literal:** serves NFR-1, but has no bound in the fade.
- **HF-W + D:** serves NFR-1, with a derived bound and no blind frames.

FR-SIM-6 is dropped (it is about movement).

---

## M3-4: texts, final

**S-W label (both_wall).** Seat 9's changes 1–8, with change 8 not triggered, and the interrogator's "indicative":

> "layout4_s1/both_wall: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall; listener–emitter 29.95 / 20.13 m (L / R). The reflections off those faces (delay about 0.58 ms; first interference notch near 0.86 kHz) are absent at s = 1 (AX21; Kuttruff Eq. 8.59), so the direct sound's tone colour is not room-like and the scene represents no seat. D/R at 1 kHz −7.7 / +5.2 dB per emitter, −5.3 dB heard (emitter L's direct arrives 28.6 ms after R's and counts as reflected); diffuse field −18.5 / −15.0 dB at r/r_c 8.39 / 5.64 (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Tail onsets t_mix,e 0.165 / 0.380 s; at equal times the two tails agree within 0.05 dB at 1 kHz, and the tail share 0.667 at 1 kHz rests on L's earlier onset. Early part empty (AX21). Heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s. Not a validated preset."

Working for the derived figures:
- 2 × 0.1/343 = 0.583 ms; 1/(2 × 0.583 ms) = 857 Hz (the first null of a direct sound plus one equal-sign delayed copy, which is arithmetic, not a corpus value).
- (29.95 − 20.13)/343 = 28.6 ms.

**S-B\* label (s0.7).** Seat 9's change 9, plus "indicative", plus the tail T30 from file 5:

> "layout4_s0.7/default: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1 (no floor reflection, unlike a real floor), scattering 0.7 on every face. D/R at 1 kHz +1.5 / +1.3 dB per emitter, +1.7 dB heard, against −10.8 dB in a diffuse field at r/r_c 3.47 (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Early part present but specular-only (partial AX21): first image (ceiling) about 23.6 ms after the direct sound; broadband early energy −3.8 dB re direct; the step at t_mix,e is printed. Tail target Eyring 1.29 s at 1 kHz, a diffuse target, not a room prediction; heard-IR T30 1.831 s spans early part and tail; tail T30 1.254 / 1.274 s. Not a validated preset."

**S-W fallback template.** Seat 9's text, verbatim, with two changes:
- NEAR-FACE names each face ("off the {faces} at the listener"), per Seat 2's condition.
- "Tail onsets t_mix,e {a} / {b} s" is added before {SPREAD}.

The prefilled table is Seat 9's [Inf]. The kit's printed values replace it at the seal.

**S-B\* fallback (s0.9).** Seat 9's values: D/R +6.0 / +5.6 dB, +6.6 dB heard; −10.8 dB at 3.47; early part −9.5 dB; 23.6 ms; Eyring 1.29 s; heard T30 1.925 s; the floor clause; "indicative". Seat 9 confirms the filled text before the seal.

**The kit's r_c.** The kit also prints r_c 3.89 m. That is Eq. 5.44's approximate form with Eyring T. The labels use the decided 3.57 m (A form). The manifest names both forms so that the two values are not read as a conflict.

**Item 13.** File 2's sentence, plus the α wording (M3-2), plus "tail onsets t_mix,e" and "tail spread" in each record line. Example:

> "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s1/both_wall (tail share 0.667 at 1 kHz, resting on emitter L's t_mix,e 0.165 s against 0.380 s; tail spread −0.05 dB; listener and emitter 0.1 m from a face)".

Family α and union rates as in M3-2.

**Item 15.** File 2's text, with these changes:
- **"Two sittings of ≤ 2 h each"** becomes "sittings of ≤ 2 h each (two if nothing is detected at 0.9 dB, three if something is), split only at a chain boundary, on the same or consecutive days".
- **F3 and F4** carry F1 and F2's trial design (M3-2).
- **Seat 4's (a):** add "Neither family is cited for externalisation or plausibility, and L4/L5 are not judged on these scenes."
- **Seat 4's (b):** "the same wired headphone model and level setting, recorded in the 07c-2b and 08-3 records, and no virtualiser."
- **AC6** stays as written. Per-ear, per-band energy is a print only (Seat 4 (c)).
- **Add:** "If a rebuilt scene fails a seal gate, item 15 returns to the board before any 08-3 listening."

**File 34 clause:** file 2's text stands (0.874 dB is CORRECT).

**Confidence:** high.

**Acceptance check:** NFR-1, L133/L54 and FR-3D-5 are served. Labels are validation-only. Amends nothing.

---

## M3-7 / M3-L4: AX49 L4

### Design

| option | S1 | S2 | S3 | S5 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|
| **L4-A** | 0/1 | 1/1 (on S′) | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | **1** | **8** |
| L4-B | 2/**3** | 2/2 | 2/**3** | 1/**3** | 1/0 | 2/2 | 0/1 | veto | — |
| L4-B′ (handover in (release + L_p, L)) | 2/1 c | 2/2 c | 1/1 | 1/1 c | 1/0 c | 2/2 c | 0/1 c | 2 | 19 |

Seats 4 and 6 are not required (file 2 table), 0/0.

**The L4-A and L4-B cells, in each seat's words:**
- **S1:** L4-A "0 | 1: it is the worst-case exposure"; L4-B "2 | 3: AX49's 'the L4 ABX detects the cut' can never fire".
- **S2:** L4-A "1 / 1"; L4-B "2 / 2".
- **S3:** L4-A now "1", later "1"; L4-B "2", "3"; L4-B′ "1", "1" (stated).
- **S5:** L4-A "0/0"; L4-B "1/3".
- **S7:** L4-A "Now 0 … Later 1"; L4-B "Now 1 … Later 0".
- **S8:** L4-A "1", "1"; L4-B "2", "2".
- **S9:** L4-A "0/0"; L4-B "0/1".

**Reading the B′ cells (c = read from conditions; B′ appeared in this round):**
- **S1:** the condition takes the later 3 to 1; the now 2 is not addressed.
- **S2:** its only condition ("only as a record next to L4-A") is not met, so 2/2 stands.
- **S5:** "L4-B (3 → 1)", and now 1 ("new two-IR switch plumbing").
- **S7:** its now-to-0 condition needs the switch path confirmed, and Seat 5 says it is new plumbing, so 1/0.
- **S8:** "run only after L4-A" is not met, so 2/2.
- **S9:** no condition, so its L4-B cell 0/1.

**The B′ readings are not decisive.** Even if every read B′ cell equalled that seat's L4-A cell, B′'s sum would be:

| S1 later 1 | S2 2 | S3 2 | S5 2 | S7 1 | S8 2 | S9 0 | total |
|---|---|---|---|---|---|---|---|
| ≥ 1 | 2 | 2 | 2 | ≥ 1 | 2 | ≥ 0 | ≥ 10 |

That is more than 8, so L4-A wins at step 3 or step 5 under any reading.

**Working:**
1. **Bounds:** none of the options breaks one.
2. **Veto:** L4-B is out (Seats 1, 3 and 5, later 3).
3. **Worst-off seat:** L4-A has max 1. B′ has max 2 as read.
4. **Compose:** "L4-A plus B′ as an unscored record" does not lower the maximum, and it adds Seat 5's plumbing and Seat 7's hours. Not built.
5. **Sum and reversibility:** not needed.

### Scene (Seat 2)

- **S (the verbatim box):** 1/2. It is 1/1 only if a null is scoped to "cut at 63 Hz depth only".
- **S′:** 1/1, with no scope limit. Seat 2 prefers it.
- Both are max 1 with conditions met. The sum ties (2), and both are equally cheap to undo. The tie-break is the seat's own ranking: S′ avoids a scope limit that weakens the record.

### Flag (Seats 5 and 3)

- 1/1 as stated; 1/0 with F1–F6.
- **Conflict found:** Seat 3's S1/S2 (both arms on the partitioned real-time path, prefix bit-identical "floored to a partition") against Seat 5's F2 (excludes `--realtime-emulation`).
  - The offline path uses one full-length FFT for long IRs (K10), so its prefix cannot be bit-identical, and S2 would fail on a clean stimulus.
  - **My composition:** F2 is kept except that `--realtime-emulation` with a fixed `--block` is allowed, with both arms always on it.
  - **Seat 5's flag cell is read as 1/1** (its "as stated" rating; F2 partly met; marked c), which is still max 1. Seat 3's S1–S3 hold as written.
  - Seats 3 and 5 confirm in R3.

### Pre-seal timing

- **Built and sealed before the first scored AX47 trial:**
  - Seat 7: 1/0.
  - Seat 1: met. This is its round-1 condition: "If L4 were designed after the AX47 scores, its open choices could be bent by them".
- **Frozen spec only:**
  - Seat 7: 0/0.
  - **Seat 1: not rated** (K13). Seat 7 itself says "Seat 1 decides".
  - The frozen spec leaves open exactly Seat 7's stall case: a spec forced to change after scores.
- I choose the fully rated option. Its cell (1) does not raise M3-L4's maximum.

### DECISION M3-7 / M3-L4

**1. Design: L4-A**, its own family:
- **A:** the chord through the AX49 provisional IR, faded over [L_f, L_p).
- **B:** the same chord through the exact IR.
- One tailSeed, shared by A and B and fixed (the kit's), committed with the trial-plan seed. Seat 3's varied seeds are [Hyp], and its own default is the fixed seed.

**2. Scene: S′.**
- 100 × 100 × 100 m; scattering 0.3 on all faces.
- Listener (50, 30, 1.7). Emitters (45, 70, 2) and (55, 70, 2).
- α set per band so that the engine prints T60 8.0 ± 0.1 s from 63 Hz to 1 kHz. Above 1 kHz, α stays at the 1 kHz value.
- The iteration is on scene data only. Nothing goes in `src/sim` (NFR-8).
- **Seal asserts (Seat 2):**
  - `provisional == true`;
  - L_p < L, with L = 12 s;
  - L_p ≤ 3.82 s;
  - decay ≥ 18.7 dB from t_mix,e,max to L_f in every band.
- **Prints:** per-band T60, the depth at L_f and at L_p, and t_mix,e,max.
- **If S′ cannot meet these:** use S, with Seat 2's per-band depth print and the null scoped to "cut at 63 Hz depth only".

**3. Chord: Seat 1's spec, verbatim.**
- C2, G2, C3, E3, G3; 1/k harmonic series to 5 kHz; seeded phases, versioned.
- Envelope: 0.5 s silence, 20 ms attack, 4 s hold, 10 ms raised-cosine release, ≥ 12 s of free decay.
- Band-coverage assert: 63 Hz–4 kHz within 20 dB.
- Level: steady-state RMS equal to the AX47 noise stimuli's within ±1 dB; peak ≤ −1 dBFS; no normalisation; the same headphones and level setting, recorded.
- **How this meets Seat 8:** the 1/k series is a saw-type spectrum; the voicing is open root-fifth (Seat 8's "open and spread"); energy reaches the T60_max bands; the release is musical.
- **Not adopted:** Seat 8's detune and low-pass. Seat 8 gave no numbers, and it hands "level, durations and seeds" to Seats 1 and 3.
- "Fully wet" means the whole rendered IR (direct, early part and tail) with no dry path (answering Seat 9).

**4. Checks.**
- **Seat 3's P1–P6, S1–S7 and N-L1–N-L3**, as written, plus Seat 2's asserts.
- **Seat 1's prefix check** (A−B ≤ −18.27 dB over [0, release + L_f − h)) is asserted as written.
  - **My note, not a change:** the window includes the post-release interval, where by construction A lacks the lags ≥ L_f, so the margin may be thin.
  - The builder computes the value before the seal. A red is a stop and returns to Seats 1 and 3. It is never loosened.

**5. Pass rule: Seat 1's.**
- ≥ 12/16 (α 0.0384, power 0.630).
- 6 interleaved exact-versus-exact anchors with the tail at −3 dB; pass ≥ 5/6; otherwise void with one rerun (run sheet L146).
- Familiarisation is labelled, with no scored feedback.
- A detection fires AX49's Reversal, worded "worst case: provisional current through the whole free decay".
- A null is worded "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic". Never "inaudible".

**6. Flag: `render_cli --ax49-provisional`** (validation only).
- With `--mode omni`, it assembles the IR through `Engine::assembleProvisional` for `--ir` and for `--in/--out`.
- **F1:** non-zero exit unless `--mode omni` and `provisional` is true; prints L_f, L_p and L.
- **F2 (as composed):** excludes `--ensemble`, `--abx-step-db`, `--switch-scene`/`--switch-every`, `--tail-level ax16` and `--block random`. `--realtime-emulation` with a fixed `--block` is allowed.
- **F3:** both arms go through `render_cli --realtime-emulation --block <fixed>`, one tool.
- **F4:** `src/plugin` never names the flag; the plugin never links `src/cli`.
- **F5:** default renders are bit-identical with and without the code; two flagged runs are bit-identical; `[pipeline]` offline-bypass is unchanged.
- **F6:** the CI test uses a small scene with L_p < L.
- There is no `src/sim` change. If one turns out to be needed, the builder stops and returns to Seats 3 and 5.

**7. The AX49 `/fix-plan`.** Seat 5 rates it 0/0. The sentence keeps its words and gains a clause:

> "Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6), except the validation-only flag `render_cli --ax49-provisional` for listening item L4 (phase-07c-2b M3-L4: omni only; refuses unless a provisional exists; excluded with `--ensemble`, `--abx-step-db`, `--switch-scene`, `--tail-level ax16` and random blocks; never named by `src/plugin`, tested)."

- In the L4 sentence, "run with the AX47 ABX in 07c-2" becomes "in 07c-2b".
- Add a §6 row.
- The FM-2′ text that cites her by date is untouched.

**8. Timing and order.**
- L4's stimuli are built, pass every check, are sealed, and their hashes go in the same pre-registration commit as F1 and F2, **before the first scored AX47 trial**.
- The commit also carries the full spec (Seat 7's frozen spec, at no extra cost).
- Order: S-W (noise 0.9 first), then S-B\*, then L4 in its own sitting after a rest, **the same day** as the S-B\* sitting.

**Load-bearing claims:**
- **L4-L1 (K23, AX49 code fact):** after a handover the output equals the exact render. So any handover ≤ L_f never presents the cut (Seats 1, 2, 3, 5 and 8 agree).
- **L4-L2 (K11):** the energy past L_f is −18.7 dB.
- **L4-L3 (from the code):** offline long-IR rendering is one full-length FFT. Hence the F2 composition.
- **L4-L4 (derived):** the stimulus is ≥ 16.53 s.

**Future-debt register (L4-A, S′, flag, timing):**

| seat | commits to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | a worst-case exposure; frequency of exposure comes from record (h) | — | record (h); 07d | the time-to-exact print |
| 2 | the gap-and-return (handover between L_p and L) is not presented | a third stimulus | 07d (AX49 Reversal with 07d's candidates) | S7's would-be handover print in the record |
| 3 | the resurrection is not heard by ear | a provisional redesign (AX49's debt) | L4 result | S7 printed |
| 5 | flag maintenance; F2 partly relaxed | remove the flag | CI | F4 and F5 tests green |
| 7 | the handover is never heard in a test; the L4 build gates the AX47 seal | hours if it stalls | at the build | seal before the first trial |
| 8 | a residual wash-genre risk if null | another sitting | Phase 13 beta | null scoped as worded |

**Strongest objection:** Seat 2's gap-and-return, which "may be more audible than the cut itself".
- **Why L4-A holds anyway:** B′ would present it, but every seat except Seat 3 rates B′ at or above L4-A, and Seats 1 and 5 call L4-A simpler.
- **What answers it in the record:** S7 prints the step per band. A detection on L4-A already sends AX49 to the board with 07d's candidates.

**Confidence:** medium. Two cells are read (Seat 5's flag, and the B′ cells, which are not decisive), and the F2 composition awaits R3.

**Reversal conditions:**
- S′ cannot be built (then S applies, scoped);
- the flag needs a `src/sim` change;
- Seat 1's prefix check reds on a clean stimulus;
- Seat 1 rates the frozen-spec-only variant 0/0 in R3 (it then wins on sum and replaces the timing rule);
- Seat 3 or 5 rejects the F2 composition.

**Acceptance check (NFR-1 L105, NFR-8 L112, AX5):**
- **L4-A:** serves NFR-1 (the listening test AX49's Reversal names). No `src/sim` path (NFR-8). Offline and shipped behaviour unchanged (AX5).
- **L4-B:** a listening test that cannot reach the cut. Strains NFR-1.
- **L4-B′:** serves NFR-1, but mixes cut and return in one test. No PRD id ranks it above L4-A.

---

## M3-6 (hours): wording for Raise item 2 and scope 3 (Seat 7's condition, both branches)

**Arithmetic** (Seat 7's K6-based figures, [Hyp] pace):
- No detection: 2.0 h, plus the split's 0.28 h, plus L4 scaled to the 16.5 s stimulus (Seat 7: "scales the time linearly"; 30 min × 16.5/11 ≈ 45 min) = **about 3 h** (range 1.9–4.5 h).
- Detection: 2 × 1.94 h + 0.57 h + 0.75 h = **about 5 h**.
- If R3 adopts speech ≥ 18/24, add +17 min and +34 min: about 3.5 h and about 6 h.
- 08-3: about 2.3 h, up to about 4.5 h (about 2.6 h and 5 h with speech-also).

**Raise item 2 (text):**

> "2. The ABX listening (two test rooms plus the L4 held-chord test) needs you or a named listener: about 3 h if nothing is detected at 0.9 dB, up to about 5 h if something is [speech-also: about 3.5 h / up to about 6 h], in sittings of at most 2 h; the dates go in the session brief before the seal. The 08-3 binaural rerun adds about 2.3 h, up to about 4.5 h [2.6 / 5 h]."

**Scope 3:** replace "About 2 h of listening per scene (builder file 32, K6: range 1.3 to 2.8 h by pace)" with:

> "About 3 h of listening if nothing is detected at 0.9 dB, up to about 5 h if something is [3.5 / 6 h with speech at 18/24], L4 included (builder file 32 K6 pace; L4 timed by the builder), in sittings of ≤ 2 h split only at a chain boundary."

Applied after R3 with the speech branch chosen.

---

## The both_corner 6.2 dB spread: routing

**ROUTING.** This is report only. No tuning and no `src/sim` change in 07c-2b (NFR-8; CLAUDE.md "report it. Don't tune for it").
- **(1)** It goes in the 07c-2b PR under "Follow-ups" as an NFR-8 report. Text: "layout4_s1/both_corner: emitter L (0.1 m from two walls and the ceiling) diffuse tail −6.20 / −6.12 dB below emitter R at equal absolute windows, 1 kHz (file 5); Kuttruff Eq. 5.42 expects equal reverberant levels at equal power, indicatively (§5.6: ᾱ ≈ 0.28 is not small)."
- **(2)** A `/fix-plan` adds a §5 backlog row. Owner: **Seat 2** (geometry to room response). The question: is it the AX40 estimator or the image-source set at a corner source?
  - The phase and any acceptance threshold are left to that row's board decision. I set no threshold unconvened.
- **(3)** both_corner stays third in the S-W fallback order. If it is ever reached, the tail-spread print fires Seat 9's SPREAD clause and the null is scoped to it.
- **(4)** A later `src/sim` fix that alters a sealed scene's IR fires M3-8.

---

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-1 | V1-W (both_wall, fallback by share; s0.7, fallback s0.9) plus tail-spread print, face-naming fallback labels, item-15 rebuild gap to the board | stands (revised) | 1 (S2, S3, S7, S9) | 12 | high | NFR-1, FR-3D-5, L133 | Vorländer T6.1; Kuttruff 5.42, 5.44–5.45, 8.59 | gates fail; spread > 1 dB at a rebuild |
| M3-2 | unsplit out; noise ≥ 18/24 (24 + 6, 3 anchors per half) in F1–F4; C1 under either; fallback unsplit + C1 | proposed; **speech criterion research needed (R3)** | 1 | 5 | high (noise) | NFR-1 | — (binomial) | Seat 7's speech-also cell |
| M3-3 | HF-W + D, N1–N3, Seat 3 (a)/(b) | stands (revised) | 1 (S3, S5) | 4 | high | NFR-1 | — (derived β) | a clean stimulus fails |
| M3-4 | the label texts above, the template, item 13, item 15 (Seat 4 (a), (b)), file 34 clause | stands (revised) | — | — | high | NFR-1, L133 | Kuttruff §5.6, 5.44–5.45, 8.59 | Seat 9 rejects a filled label |
| M3-7/L4 | L4-A on S′, Seat 1's chord and pass rule, P/S/N-L checks, `--ax49-provisional` F1–F6 (F2 composed), AX49 clause, built and sealed before the first trial | proposed | 1 | 8 | medium | NFR-1, NFR-8, AX5 | AX49 K17′ (Vorländer Eq. 6.4) | S′ fails; flag needs `src/sim`; R3 |
| hours | Raise 2 / scope 3 texts, both branches | proposed (speech branch after R3) | — | — | medium ([Hyp] pace) | L55 | — | builder timing of L4 |
| corner | NFR-8 report; backlog row, Seat 2 | proposed | — | — | high | NFR-8 | Kuttruff 5.42 (indicative) | — |

**Challenges to settled decisions:** none.

## Decided for Maisara

- **M3-1:** the self-ABX runs on a far, wet placement and on a room with early reflections, both heard again binaurally at 08-3 (NFR-1, FR-3D-5, L133).
  - No PRD id ranks another survivor (V2, gated, V3-default, V3 as written, V1) above it.
  - Seat 7 gives the most, about 3 h of listening before the pin, and gets the most sensitive test before the golden round.
  - Amends nothing.
- **M3-2:** each test room gets its own family, with 24 noise trials. This halves the false-alarm rate for a 2-point power cost (NFR-1; hours unbounded, L55). Seat 7 gives about 17–34 min. Amends nothing.
- **M3-3:** the click gate is a derived energy bound with tests built to fail (NFR-1). Amends nothing.
- **M3-4:** labels say what each room is, indicatively, with no "hall" and no "occupied" (L133); a null counts only for its room (NFR-1). Amends nothing.
- **M3-L4:** the held-chord test plays the real worst case, the cut (NFR-1). A validation-only CLI flag; shipped and offline renders are unchanged (NFR-8, AX5). Seat 7 gives about 45 min plus the pre-seal build. Amends nothing (AX49's FM-2′ text is untouched).
- **Corner spread:** reported, not tuned (NFR-8). Amends nothing.
- **Person's action:** the sitting dates, before the seal.

**NEEDS MAISARA:** none.

---

## Still missing: CONVENE R3 (narrow; blocks only the speech criterion, the hours text's branch, and confirmations)

| seat | status | brief |
|---|---|---|
| 1 | convened | (a) Rate Seat 7's option (skip S-B\*'s 0.9 dB blocks after an S-W 0.9 detection). (b) Rate the L4 frozen-spec-only variant (spec in the pre-registration commit; stimuli built deterministically before L4's own first trial), now and later. |
| 3 | convened | Confirm or re-rate L4-A under the F2 composition: both arms on `--realtime-emulation` with a fixed block. |
| 5 | convened | (a) Confirm the F2 composition, i.e. your flag cell (read 1/1). (b) Confirm speech-also as read (0/1). (c) Rate Seat 7's skip option. |
| 6 | convened | Confirm speech-also as read (0/1); rate Seat 7's skip option. |
| 7 | convened | (a) Rate Seat 1's speech-also-18/24 option, now and later: +17 min with no detection and +34 min with detection, at each of 07c-2b and 08-3. (b) Re-check your split later reason: speech is ≥ 13/16 under both unsplit and the split (run sheet L136), so speech power is 0.405 under both. |
| 2, 4, 8, 9 | not required | no change touches them |

Files: this file; 4-seat1, 4-seat3, 4-seat5, 4-seat6 and 4-seat7; run sheet L135–147; `src/sim/OfflineRender.h`; `src/cli/Cli.cpp` L341–372.

**Builder, now, with no listening:**
- build L4 (S′, the flag, P/S/N-L);
- add the tail-spread print;
- cite file 5 L61–71 in the brief.

**Plan edits** (one `/fix-plan` after R3 and the interrogator): the run sheet §1, item 13, item 15 in `phase-08-3.md`, the AX47 Reversal and design, the AX49 clause, Raise 2 and scope 3, and the §5 corner row.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2b/3-interrogator-on-file2.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md … 4-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
- /home/user/makroof/docs/BUILD_PLAN.md (L170, L172)
- /home/user/makroof/docs/phases/phase-07c-2b.md (L36, L125–131)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (L135–147)
- /home/user/makroof/src/sim/OfflineRender.h
- /home/user/makroof/src/cli/Cli.cpp
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (§5.6, L2696–2724)
- /home/user/makroof/docs/PRD.md
