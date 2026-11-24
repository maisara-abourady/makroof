
# 7: Interrogator on file 6 (decider M3, rebuttal round 2, phase-07c-2b)

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. This review is read-only. I wrote no file; it is to be saved as `/home/user/makroof/docs/review/phase-07c-2b/7-interrogator-on-file6.md`.

## Verdict in brief

| matter | outcome |
|---|---|
| **M3-1** (V1-W) | **TENSION MISREAD.** Seat 9's V1-W cell rests on a condition the decider has re-measured. Read as Seat 9 wrote it, the condition fires on both_wall (+9.39 dB). If the cell goes to 2, V1-W ties V2 and gated on max and sum, so the winner can change. Everything else in M3-1 survives with corrections. |
| **M3-2** (α) | The unsplit-out ruling and the noise design **SURVIVE WITH CORRECTIONS**. The acceptance check is **PRD MISREAD (omission, mechanical)**. The speech criterion is **UNDERINFORMED**; the decider says so and has deferred it to R3. |
| **M3-3** (HF-W) | **SURVIVES WITH CORRECTIONS**, plus **PRD MISREAD (omission, mechanical)**. |
| **M3-4** (texts) | **SURVIVES WITH CORRECTIONS**, except the S-W label's spread sentence, which waits on M3-1. |
| **M3-L4 design, scene S′** | **SURVIVES WITH CORRECTIONS.** |
| **M3-L4 flag (F2 as composed)** | Faithful as read. Can stand pending R3 confirmation. |
| **M3-L4 timing** | Pending R3; one wording correction. |
| **M3-L4 acceptance check** | **PRD MISREAD (omission, mechanical).** |
| **Hours** | **SURVIVES WITH CORRECTIONS.** |
| **Corner routing** | Items (1), (3) and (4) **SURVIVE**. Item (2) **FALLS (INCONSISTENT)**. |

**Answers to my file-3 questions (Q1–Q5): all faithful.**
- Q1: Seat 7 gives "I confirm 1/1".
- Q2: the six M3-1 options are shown, and FR-SIM-6 is dropped.
- Q3: Seat 3's addendum gives 1/1 on condition (a), which file 5 L61–71 meets.
- Q4: the flag, the AX49 exception and the pre-seal build are now rated by Seats 3, 5 and 7.
- Q5: Seat 4 confirms with "The (i) label limits what a non-detection means…".
- The file-3 corrections are all applied: Seat 6's 0/0 cells, V1′ out at step 3, "tie, not V2", the s0.9 attribution, "same day", and "indicative".

**Can the rest stand while R3 runs?**
- Yes: M3-3, M3-4 (except the S-W spread sentence), the M3-L4 design, scene and flag (pending Seat 3 and Seat 5's R3 confirmation), the noise half of M3-2, and the builder's no-listening work.
- No: M3-1. R3 as convened (in its "not required" row for Seats 2, 4, 8 and 9) says no change touches Seat 9, yet M3-1 (a) changes how Seat 9's own condition is measured. **R3 is underconvened on Seat 9** for this item.

## Numbers recomputed

All of these are correct unless noted.

**Label figures**
- 2 × 0.1/343 = 0.583 ms.
- From both_wall's coordinates (file 29: listener (10, 0.1, 1.7), S0 (7, 29.9, 2), S1 (13, 20, 2)):
  - the image path differences are 0.199 m (L) and 0.198 m (R), i.e. 0.580 and 0.577 ms;
  - the first null is at 1/(2t₀) = 857 Hz. This follows from Kuttruff §7.4 Eq. 7.6: |G₁|² = 1 + q² + 2q·cos(2πft₀) is smallest at cos = −1. So it is a corpus result, not "arithmetic only".
- (29.95 − 20.13)/343 = 28.6 ms.

**t_mix,e**
- 29.95/343 = 87.3 ms; √6000 = 77.5 ms; sum 164.8 ms. This equals file 5's 0.165 s, so L sits on K20's lower bound.

**Binomial tails** (at p = 0.5 unless stated)
- Σ C(24,k) for k = 18…24 = 190051, and /2²⁴ = 0.011328.
- 697/65536 = 0.010635.
- Speech at ≥ 13/16:
  - per family 0.021963;
  - 2 families: 0.043926 (0.0439);
  - 4 families: 0.087852 (0.0879).
- Speech at ≥ 18/24:
  - per family 2 × 0.011328 = 0.022656;
  - 2 families: 0.045312 (0.0453);
  - 4 families: 0.090624 (0.0906).
- P(≥ 12/16 at p = 0.75) = 0.6302, and P(≥ 13/16) = 0.4050.
- 2517/65536 = 0.0384.

**Energy past L_f**
- e^(−13.8155 × 0.312) = 0.01341, which is −18.72 dB.
- Basis: Vorländer §6.4.1 Eq. 6.4 (Schroeder integral) applied to the decay e^(−13.8t/T) (Vorländer §11, Eq. 11.13; the constant 13.8 is listed among the decibel constants).

**L4 timing**
- Stimulus length: 0.5 + 0.02 + 4 + 0.01 + 12 = 16.53 s. L = min(12 s, 90/60 · T60_max) (`NoiseTail.cpp` L49–52, `kMaxIrLengthS` 12), so L = 12 s at T60 8 s.
- L_p at S′:
  - t_mix,e,max = 0.1175 + 1.000 = 1.1175 s;
  - L_f = 1.1175 + 0.312 × 8 = 3.61 s;
  - L_p = 3.71 s, which is ≤ 3.82 s.

**Hours**
- No detection: 2.0 + 0.28 + 0.75 = 3.03 h. Range: 1.3 + 0.17 + 0.475 = 1.9 h, up to 2.9 + 0.45 + 1.125 = 4.5 h.
- Detection: 2 × 1.94 + 0.57 + 0.75 = 5.2 h.
- 08-3: 2.28 h and 4.45 h.
- With speech also at 18/24:
  - 08-3: 2.56 h and 5.02 h;
  - 07c-2b detection branch: 5.77 h;
  - 07c-2b no-detection branch: **3.31 h**. The decider writes "about 3.5 h" (IMPRECISE).

**M3-1 sums**
- V1-W 12, V2 13, gated 13, V3-default 14, V3 as written 16.

**HF-W margins**
- 10·log₁₀(1.1378/1.0002) = 0.560 dB; 10·log₁₀(1.1378/1.0003) = 0.559 dB.

**Two figures are wrong**
- B′'s sum as read is **17**, not 19: 3 + 4 + 2 + 2 + 1 + 4 + 1.
- Speech-also's presentation cost is +36 % against **unsplit** (44 → 60 presentations), which is Seat 1's baseline. Against the split it is **+15 %** (52 → 60, and 104 → 120).

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-1 | map / claim | S9 V1-W 1/1, "condition is met (file 5)": the SPREAD clause "does not fire" because the tails agree within 0.05 dB in equal absolute windows | **TENSION MISREAD**; the hidden premise is CONDITIONS VIOLATED | Seat 9's condition asks for "each emitter's tail energy at the listener" and says that "if the two differ by more than 1 dB" the SPREAD clause and an NFR-8 report to Seat 2 follow; "Without this condition, later is 2". File 5 measures tail energy from each emitter's own t_mix,e at **+9.39 dB**. Kuttruff Eq. 5.42 is a steady-state energy density, and steady state is the integrated IR (Vorländer §6.4.1 Eq. 6.3). On that measure the two tails differ by about 9.4 dB, not 0.05 dB. Seat 9's premortem (share 0.667 → 0.29 after a `src/sim` change) holds whether the cause is level or onset (file 5 fact 1 says so). | **M3-1 does not survive yet.** If S9 later = 2, V1-W has max 2 and sum 13, the same as V2 and gated, and reversibility would decide. Seat 9 has not agreed to the equal-window measure, and R3 does not convene it. | Q1 |
| M3-1 | claim | M3-1 (a): print L − R in [0.45, 0.65) and [0.8, 1.0) s against the 1 dB jnd for G | CONDITIONS VIOLATED | Vorländer Table 6.1's jnd is for G, a total-energy measure (Eq. 6.5). The fixed late windows cannot see an onset-driven spread, which is the mechanism file 5 found on both_wall. | part of the row above | Q1 |
| M3-1 | map | S1 V2 (conditions met) 0/1 | IMPRECISE (new words) | 4-seat1 R2 (b): "every one of my V2 → 0/0 conditions". V2 would be 0/0 and sum 12. | winner unchanged (S3 2/2 on V2) | — |
| M3-1 | map | S1, S2, S4, S5, S6, S7 V1-W cells; S3 "round 1, unchanged" | faithful | quotes match 4-seat1, 2, 4, 5, 6, 7; file 2 L79 for S3 | — | — |
| M3-1 | debt | eight rows | present; referents exist (O4, 08-3, Phase 13 beta, AX38 (iv)) | `phase-13*.md` mention beta | — | — |
| M3-1 | claim R2-L1 | −0.05 / −0.03 dB; t_mix,e 0.165 / 0.380 s; 164.8 ms | CORRECT (builder measurement; K20 arithmetic) | file 5 table; K20 | — | — |
| M3-1 | PRD proxy | six options shown; "no PRD id ranks another above V1-W" | faithful to the PRD | L49, L55, L75, L101, L105, L133 read | — | — |
| M3-2 | ordering | unsplit out (7 against ≤ 5); noise ≥ 18/24 + 6 anchors, 3 per half | correct | cells match 4-seat1, 5, 6, 7. The result holds under any R3 cell for Seat 7. | SURVIVES WITH CORRECTIONS | — |
| M3-2 | claim | speech-also "+36 % per scene" as the extra cost | IMPRECISE | +36 % is against unsplit; against the split it is +15 % | correction | — |
| M3-2 | inventory | fatigue in 30-presentation blocks | research gap ([Hyp] in Seat 1; RQ-M3-1); missing from the K table | 4-seat1 §5 | add to K; not decisive (the anchors in each half void a fatigued block) | — |
| M3-2 | PRD proxy | 13/13 split (survives steps 1–2, max 2) not shown | PRD MISREAD (omission) | the 4-seat6 cell 1/2 makes it a survivor | re-answer: add one line. No PRD id points to it. | Q4 |
| M3-2 | speech criterion | Seat 7's cell missing | UNDERINFORMED (acknowledged) | K8 | R3 | — |
| M3-3 | map / ordering | HF-W + D 1/1 and 1/1; sums 7 / 4 / 6 / 4 | faithful; correct | 4-seat3 addendum ("1 now, 1 later" on condition (a)); 4-seat5 "1/1 with condition D" | SURVIVES WITH CORRECTIONS | — |
| M3-3 | claim | commutator "measured on two scenes" | IMPRECISE (understated) | file 5 L79–84: four scenes, 200 stimuli, worst 1.0004 | correction | — |
| M3-3 | PRD proxy | "HF-W without D" (in the map, max 2) not shown | PRD MISREAD (omission) | map row 4 | re-answer: add one line | Q4 |
| M3-4 | claim | notch 857 Hz "arithmetic, not a corpus value" | IMPRECISE (citation) | Kuttruff §7.4 Eq. 7.6: minimum at f = 1/(2t₀) | cite Eq. 7.6 | — |
| M3-4 | claim | kit r_c 3.89 m "Eq. 5.44's approximate form with Eyring T" | IMPRECISE | Eq. 5.44 prints 0.1·(V/πT)^½, coefficient 0.0564, with Sabine's T; the kit uses 0.057 and Eyring T | the manifest names the coefficient and the T used | — |
| M3-4 | text | S-W label "agree within 0.05 dB … share rests on L's earlier onset", no SPREAD clause | depends on the M3-1 row above | Seat 9's clause: "this is the engine, not room physics (Kuttruff Eq. 5.42)" | waits on M3-1 | Q1 |
| M3-4 | text | item 13, item 15 (Seat 4 (a), (b), AC6), fallback template, s0.9 values | faithful | 4-seat4 (3); 4-seat9 R2-2 | SURVIVES | — |
| M3-L4 | convening | Seats 4 and 6 not required | correct | README rows 4 (cross-format parity) and 6 (user-facing). L4 changes no shipped behaviour (F4, F5). | — | — |
| M3-L4 | map | L4-A and L4-B cells, all seats | faithful | quotes match 4-seat1, 2, 3, 5, 7, 8, 9. L4-B vetoed by S1, S3 and S5 (later 3). | — | — |
| M3-L4 | map | B′ read cells S2 2/2, S8 2/2, S9 0/1 | TENSION MISREAD (not decisive) | Those seats' L4-B reasons ("the cut is never played", "misses the event … on first play", "does not test the cut") do not apply to B′, which presents the cut | withdraw them as "unrated". The floor below carries the result. | Q3 |
| M3-L4 | ordering | B′ sum "19"; the "not decisive" table is "if every read cell equalled that seat's L4-A cell" | IMPRECISE (arithmetic and premise) | As read, the sum is 17. Under the literal premise S5 = 0 (L4-A 0/0) and the floor is 8, a tie. The table actually uses S5 1/1 and S7 1/0, which are Seat 5's own words ("now 1 … two-IR switch plumbing", "(3 → 1)") and Seat 7's. With S1 ≥ 1 (later 1, its own words), S3 2 (stated), and S2 and S8 ≥ their L4-A cells (their L4-A reasons apply to B′), the floor is 10 > 8. | SURVIVES WITH CORRECTIONS: restate the premise; sum 17 | Q3 |
| M3-L4 | debt | Seat 2 row: "gap-and-return … not presented" | TENSION MISREAD (row content) | Seat 2's own L4-A later reason: "a detection sends AX49 back to the board … a reopening". The gap is a separate paragraph, "Gap neither option covers". | correct the row | — |
| M3-L4 | omission | Seat 9's L4 label ("must contain": V, T60_max, "stress geometry", no "hall"; "exact = full synthesis") | missing from the decision | 4-seat9 M3-L4 | add it; Seat 9 confirms | Q5 |
| M3-L4 | flag / map | F2 as composed; Seat 5's flag cell read 1/1 "as stated" | faithful (an upper reading: the composed flag is a subset of "as stated") | 4-seat5: "1/1 as stated, 1/0 with conditions F1–F6" | stands pending R3 | — |
| M3-L4 | claim L4-L3 | offline long IR is one full-length FFT, so S2's bit-identical prefix fails offline | CORRECT (code) | `OfflineRender.h` L5–7, L26–36. At these sizes taps × input ≫ 2²⁶, so Auto picks FFT. | — | — |
| M3-L4 | claims L4-L1, L4-L2, L4-L4 | K23; −18.7 dB; ≥ 16.53 s | CORRECT | as recomputed above | — | — |
| M3-L4 | timing | sealed-before chosen; reversal "Seat 1 rates frozen-spec 0/0 → it wins on sum" | faithful to 1-seat1 L82 ("built, sealed and hash-committed before that trial"); IMPRECISE wording | at 0/0, frozen-spec has max 0 against 1, so it wins at **step 3**, not on sum | correction; R3 | — |
| M3-L4 | PRD proxy | the check shows only the design options; S/S′ and sealed/frozen are not shown; "No `src/sim` path (NFR-8)" and "shipped and offline renders unchanged (NFR-8, AX5)" | PRD MISREAD (omission); NFR-8 citation IMPRECISE | NFR-8 L112 says "no environment-specific code paths". It does not say renders stay unchanged; AX5 and AX49 do. | re-answer: add the lines; no PRD id points elsewhere | Q4 |
| hours | claim | speech-also no-detection "about 3.5 h" | IMPRECISE | 3.03 + 0.28 = 3.31 h | write "about 3.3 h" | — |
| hours | condition | both branches stated; dates before the seal | meets Seat 7's condition | 4-seat7 R2 (a) | SURVIVES WITH CORRECTIONS | — |
| corner | claim | (2) "a `/fix-plan` adds a §5 backlog row … the phase … left to that row's board decision" | INCONSISTENT | BUILD_PLAN §5 is "Deferred items (post-v1 backlog)": "Phase files for these get written once v1 is done". The placement itself defers an NFR-8 departure past v1. | item (2) FALLS. Items (1), (3) and (4) survive. The 6.2 dB and Eq. 5.42 text is CORRECT (indicative: §5.6). | Q2 |

## Questions for the decider (R3 rebuttal)

1. **Seat 9's spread condition.** Seat 9 wrote "each emitter's tail energy at the listener … differ by more than 1 dB". On that measure file 5 gives +9.39 dB, and Kuttruff Eq. 5.42 is a steady-state, integrated quantity (Vorländer Eq. 6.3). On what reading does the clause "not fire"? Will Seat 9 be convened in R3 to accept the equal-window measure, or will its clause and NFR-8 report be applied as worded? If neither, S9's V1-W later cell is 2, and V1-W, V2 and gated tie at max 2 and sum 13.
2. **Corner routing (2).** §5's header makes its rows post-v1 ("once v1 is done"). How does a §5 row leave the phase "to that row's board decision"?
3. **B′.** Confirm the as-read sum is 17, not 19. Restate the "not decisive" premise: S5 and S7 at their own switch-plumbing words, S2 and S8 at no less than their L4-A cells. Withdraw the S2, S8 and S9 B′ cells read from L4-B reasons that do not apply.
4. **Acceptance checks.** Add the 13/13 split (M3-2), HF-W without D (M3-3), S and S′ and the two timing options (M3-L4) against their PRD ids. Cite AX5 and AX49, not NFR-8, for "offline and shipped renders unchanged".
5. **The L4 label.** Where is Seat 9's required label text (V 10⁶ m³, T60_max 8 s "stress geometry, not a room prediction", no "hall", "exact = full synthesis, not a measurement"), and who confirms it before the seal?

## Files read
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md, 3-interrogator-on-file2.md, 2-decider-m3.md (L55–114, L398–404), 4-seat1.md … 4-seat9.md (Seat 3's addendum included), 5-builder-tail-spread.md, 1-seat1.md (L82)
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md (L12–21, L38)
- /home/user/makroof/docs/PRD.md
- /home/user/makroof/docs/BUILD_PLAN.md (L170, L172, §5 L388–397)
- /home/user/makroof/docs/board/README.md (convening table; recorded decisions)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (L133–147)
- /home/user/makroof/src/sim/OfflineRender.h, /home/user/makroof/src/cli/Cli.cpp (L330–379), /home/user/makroof/src/sim/tail/NoiseTail.cpp (L49–52), /home/user/makroof/src/sim/tail/NoiseTail.h (L31–33)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (§5.6 Eqs. 5.42–5.45 and caveat; §7.4 Eqs. 7.5–7.6)
- /home/user/makroof/docs/corpus/vorlaender-auralization.md (§6.4.1 Eqs. 6.3–6.4; §6.4.2 Eq. 6.5; Eq. 11.13; decibel constants)
