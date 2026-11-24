# Interrogator on decider file 2 (phase 07c-2b: M3 and the click_check call)

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`; 14 files present).

**Target:** `/home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md`.

**Read:**
- Seat answers 1-seat{1,2,3,4,5,6,7,9}.
- Convening in `docs/review/phase-07c-2/31-decider-abx-r4.md`, "M3: CONVENE".
- Files 13 (items 7, 8, 15), 29 and 32, and 26-seat4.
- `docs/phases/phase-07c-2b.md`, phase-06 L60–65, phase-05e scope, phase-08-3 and phase-08-4.
- BUILD_PLAN AX21 (L144) and AX47 (L170); PRD L10–112.
- `tools/ci/abx_kit.py` L60–101 and L355–604; `tools/ci/test_abx_kit.py` L95–149; `tools/acoustics/clicks.py`.
- Kuttruff §5.6–5.7 (Eqs. 5.42–5.45, Table 5.2), Eqs. 4.10–4.12 and 5.24, §8.8 Eq. 8.59.
- `.claude/agents/decider.md` §1a and §3–6; `docs/board/README.md` convening table.

## Rulings

| decision | ruling |
|---|---|
| D-M3a click_check form (b) | **SURVIVES WITH CORRECTIONS** |
| D-M3b onset at the heard gap start | **FAILS** (a load-bearing claim is WRONG, shown from the code's own arithmetic) |
| D-M3c α unsplit | **SURVIVES WITH CORRECTIONS** (map misreads that do not change the winner; one debt row; the PRD line) |
| D-M3d S-B\* = s 0.7 | **SURVIVES WITH CORRECTIONS** (wording of the worst-off cell) |
| D-M3e item 13 wording | **SURVIVES WITH CORRECTIONS** (Class line) |
| D-M3f file-34 clause | **SURVIVES** |
| D-M3g item-9 labels | **SURVIVES WITH CORRECTIONS** |
| D-M3h scene-independent conditions | **SURVIVES WITH CORRECTIONS** |
| D-M3i AX47 α sentence | **SURVIVES** |
| Scene deferral to builder K7 | **The deferral is sound. K7's spec is incomplete.** The four additions are listed below. |

### Convening (step 1)
File 31's table has nine rows. The only seat recorded not required is Seat 8: "a validation stimulus; item 13 forbids public copy". That matches the README row for Seat 8 (what producers do with the product, workflow, translation): nothing here is producer-facing. D-M3g's label strings reach only the run sheet, the kit manifest and the internal listening pack. **Not UNDERCONVENED.**

### Scene tension map (step 2)
- Every V1–V4 cell matches the seats' §3/§4 word for word. The recomputed sums are 22, 18, 21 and 20 (V3′).
- The V3′ cells marked "c" follow from those seats' V3 reasons, which all apply to layout5_s1/default: K10, the empty early part, Seat 4's anisotropy and the board cycle.
- V1′'s Seat 1 later 3 (c) follows from Seat 1's V4 veto reason, "No test ever covers late-dominated scenes…". V1′ never runs S-W.
- Faithful.
- Note for the next round: D-M3h 2(d) adopts Seat 3's §6 condition ("V2, V3, V4 drop to 1 if 08-3's S-B\* result is written as a reversal trigger…"). Seat 3's cells must be read down from that condition when the map is redone.

### Scene ordering and deferral (steps 4, 7)
- I redid the ordering:
  - V4 and V1′ are dropped on a 3.
  - V1, V2, V3 and V3′ all have a maximum of 2. V2 is lowest on sum (18).
- The compose step holds against the seats' words:
  - Seat 7 is at 2 now for any option with two scenes before the pin (V1: "3.9 h … two sittings").
  - Seat 9 is at 2 later unless S-B\* is read before O10 ("That alone leaves the rating at 2").
  - Seat 1 is at 2 unless a wet scene runs before the pin (its V1 → 1 condition).
  - So only a single scene that is both s < 1 and wet could bring the maximum down to 1.
- K11 is load-bearing and uninformed. Under decider §3 the decider must therefore return RESEARCH NEEDED, not decide. Withdrawing file 31 L81–84 is correct: it generalised from layout4/default only (file 29, rows 28–32).
- PRD L55 ("no fixed deadline") is quoted correctly. **The deferral is sound.**

**K7 spec: incomplete.**
1. **No measure of the post-onset silence or the heard gap** (see D-M3b). `gap_check` (abx_kit L548–559) reads the programme's minimum gap, so it cannot see what D-M3b changes.
2. **layout5_s1/emitter_wall is not rerun under the new checks**, although V3 stays on the map ("the next round decides among V1, V2, V3 and V3′"), and that is V3's S-W (share 0.869, file 29 L44).
3. **The candidate set is not exhaustive.** Capping improves as s rises (file 29 fact 1), and K7 tests the layout-4 wall placements and layout5 emitter_wall only at s = 0.7. So "If no candidate qualifies, the map above stands" holds only for the listed set.
4. **The V6 trigger names the conditions of Seats 1, 3, 7 and 9 only.** Every layout-4 candidate in K7 is a 0.1 m placement, which fails Seat 2's C2 ("no placement within 0.1 m of a face, and direct-path difference ≤ 2.5 ms"). The layout-5 candidates meet Seat 4's 2 later unless its label condition is met. K7 does not report the difference in direct path between emitters.

Also, "K7" names two different things: inventory row K7 (both_wall at N + 1407) and the builder measurement. One of them needs renaming for traceability.

### D-M3a
- **M3-L1 / K3: CORRECT (from the code).**
  - r = (o − a) − (j/L)(b − a) = o − rec in the fade, which companion (ii) bounds (abx_kit L389–392). Before N and after the fade, r = 0 exactly (L395–396, L407–411).
  - 8u = 2⁻²¹, which is −126.4 dB.
- **M3-L2 / K4: IMPRECISE.**
  - "Caught at −68, missed at −70" is a docstring (test_abx_kit L133–134). Only −65 dBFS is asserted.
  - The planted impulse sits at s0 + 480 = 24480 = 255 × 96, a frame boundary. The zero-phase high-pass spreads its energy over two frames, which moves the derived −69.8 dBFS threshold by about 0.2 dB. That is still inside the bracket.
- **"The kit-side code already matches this": INCONSISTENT with the code.**
  - `click_check` records `floor_dbfs` (the detector's −90), not the −68 dBFS spike floor.
  - It prints only the legacy A-against-B count (L434–436). It prints no event counts on E.
  - The B/E null against the offline render is not implemented.
- The criterion says "per ear at 08-3" but specifies "channel 0". `crossfade_residual` reads channel 0 only.
- The ratio-form slack is (1 − j/L + tol)·HP(E − B); the decider's version omits tol. The inference stands.
- **PRD line: FR-SIM-6 (L89) is scoped to movement.** The AX47 step is interim-to-final, so NFR-1 (L105) alone carries the check. Minor PRD MISREAD (cited id).
- **Corrections:**
  - Restate "already matches" as "the residual criterion and the red tests match; the printed spike floor, the A/B/E counts and the B/E null are to be added".
  - State whether the −68/−70 bracket will be asserted.
  - Write "channel 0 (each ear at 08-3)".
  - Drop FR-SIM-6 or scope it.
- The decision still follows.

### D-M3b: FAILS
**The claim is WRONG** (code arithmetic). It reads: "The silence from N to the next burst still meets the gap rule (≥ heard T30, and ≥ every tail T30 under M2)".
- `noise_programme` sets gap = ceil(T30·fs/P)·P, which is less than T30·fs + P (abx_kit L499). The next burst starts at the input onset + gap (L505).
- The nearer emitter's heard end is always N + 32 (file 32 L56), so D-M3b moves N by at least one partition. The silence after N is then at most gap − P, which is less than T30·fs. **This holds on every scene.**
- S-A: 96768 − 512 = 96256 samples, i.e. 2.0053 s against 2.009 s.
- both_wall: shift 1536, so 66048 − 1536 = 64512 samples, i.e. 1.344 s against 1.370 s. Against the tail T30 it is unmeasured: Seat 1's [Inf] estimate is 1.25–1.29 s.

**INCONSISTENT.** D-M3b places the onset "as heard" but leaves the gap rule on the input.
- On both_wall the heard silence between bursts is already 66048 − (1407 − 32) = 64673 samples, i.e. 1.347 s, which is less than 1.370 s.
- M2's premise ("gap longer than the tail's own decay", file 34 item 3) is asserted on a quantity that D-M3b no longer controls.

The choice of onset itself is not contested (Seat 1 C3, Seat 3 §6). The decider must restate what the silence after N must satisfy and what the manifest asserts.

### D-M3c
- **Claims CORRECT.**
  - Under Binomial(16, ½): P(≥12) = 2517/65536 = 0.0384 and P(≥13) = 697/65536 = 0.0106.
  - Powers at p = 0.75: 0.630, 0.405 and 0.197 (recomputed from the binomial terms).
  - Union rates: 0.147/0.140 for n = 3 and 0.196/0.182 for n = 4.
- **TENSION MISREAD, outcome-neutral (three cells and one sum).**
  - (a) Seat 1's split cell is "rated 2" with no column (1-seat1 §1). The decider enters it as 2/2 but sums the row to 8; with 2/2 the sum is 10.
  - (b) The Seat 1 unsplit cell "0/0 c" is read from conditions for an option that was in file 31's brief. Seat 1 gave "prefer" and no number. Even at 2/2, unsplit wins on sum (9 against 10).
  - (c) Seat 1's own variant, "I can live with splitting only the 08-3 families", is missing from the map. Read from Seat 6's conditions, its split reason still applies there: under D-M3h 2(d) a miss at 08-3 leaves an admitted source standing. That gives 2/2 c and a maximum of 2, so unsplit still wins.
- **Debt register: hidden premise.** Seat 7's row gives the undo cost as "A parameter change".
  - W_max is a pinned constant (`kWMaxPerEmitter`, phase-07c-2b item 6), and item 8 allows one golden round.
  - The decider's own Seat 3/7 row names a re-pin plus a second golden round.
  - Seat 5's "SE ≤ B/1.96, W_max derived from B" is adopted only for more than 3 families.
  - Restate the undo cost.
- **PRD line: PRD MISREAD (cited id).** "A false 'detected' costs CPU and load time, which NFR-2 accepts". But NFR-2 (L106) accepts CPU "when they buy accuracy", and a false reversal buys none.
  - The supported reading rests on L101/L49 (accuracy is the top priority) and on L101's "must stay usable", met because Seat 6 records that a false reversal "does not make today's load worse".
  - Split still strains NFR-1, so the acceptance stands.

### D-M3d
- M3-L7 is CORRECT (file 29 L30: share 0.032/0.029; s_w 6.1e−7, 2.5e−5 in the worst band).
- The worst-off cell "≤ 1 c" is not any seat's number. No seat rated an s value.
- Restate it as "no ratings. 0.7 is preferred by Seats 2, 3, 4 and 9 (Seat 4 makes it a condition); Seat 1 prefers 0.9 and can live with 0.7".

### D-M3e
- The definition "class = the Class line of the item-9 label" is INCONSISTENT with the labels it adopts. Seat 9's layout5_s1/default and emitter_wall labels (1-seat9 §6) have no Class line.
- Every sealed scene's label needs a Class line.

### D-M3f
- K13 is CORRECT. Kuttruff §8.8 Eq. 8.59 gives s = 1 − I_spec/(I₀(1−α)), so at s = 1 the specular part is 0. File 29 fact 7 agrees.
- The clause is accurate. **SURVIVES.**

### D-M3g
- **M3-L5 is CORRECT.** Kuttruff §5.7 Table 5.2 case 5 gives 3.22 / 2.99 / 3.06 s. The table is for diffusely reflecting walls, others at α 0, and correction (i) states "others 0".
- **M3-L6: the arithmetic is CORRECT.**
  - √(640/16π) = 3.568 m, 3.467, −10.80 dB.
  - √(747/16π) = 3.855 m, 3.209, −10.13 dB.
  - √(343/16π) = 2.612 m, 4.735, −13.51 dB.
  - Sabine A = 600 + 16 + 24 = 640 m².
- **M3-L6 conditions are IMPRECISE.**
  - Eq. 5.44 is stated "using Sabine's T". The Eyring-A figure (−10.1 dB) is not a corpus expectation.
  - Kuttruff (§5.6, after Eq. 5.48) says Eq. 5.43 and related equations "become questionable if ᾱ is not small compared with 1". For S-A, ᾱ = 616/2200 = 0.28, with one face at α 1 (§5.7: "severe deviation from diffuse conditions").
  - The label should carry that qualifier, not a bare "diffuse expectation".
- **PRD line is IMPRECISE.** Her AX21 decision of 2026-11-05 is "the early part should contain scattered energy" (BUILD_PLAN L144). "Named, not tuned" is the plan's framing.

### D-M3h
- Faithful to Seats 2, 3, 4 and 7.
- 2(c) carries file 26-seat4 (a), "same scene and tailSeed … chain is the only variable", to every option. That is INCONSISTENT where 08-3 (ii) has no omni twin, which Seat 4 itself notes under V2.
- 2(d) names "a second golden round" as the undo cost. It does not say this needs a /fix-plan to the one-golden-round rule (07c-2b item 8). Seat 3 says the rule "forbids the last of these". Both points need restating.

### D-M3i
- The text is consistent with AX47's design sentence (L170) and with D-M3c. The corrections to D-M3c leave the wording unchanged. **SURVIVES.**

## Ledger rows
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| all | convening | Seat 8 not required | faithful | README Seat 8 row; validation stimulus, item 13 | — | — |
| scenes | map | V1–V4 and V3′ cells, sums | faithful | 1-seat{1..9} §3–4; 22/18/21/20 | — | — |
| scenes | ordering | all at max 2, compose, K11 → RESEARCH NEEDED | correct | Seat 7 §3, Seat 9 §6, Seat 1 §6; decider §3 | deferral sound | — |
| K7 | spec | no measure of the silence after N or the heard gap | incomplete | abx_kit L499–505, L548–559 | correct K7 | Q1, Q3 |
| K7 | spec | layout5_s1/emitter_wall not rerun | incomplete | file 29 L44; V3 kept on the map | correct K7 | Q3 |
| K7 | spec | no s 0.8/0.9 fallback; the "map stands" conclusion covers the listed set only | IMPRECISE | file 29 fact 1 | correct K7 | Q3 |
| K7 | spec | V6 trigger omits Seat 2 C2 and Seat 4's layout-5 condition | incomplete | 1-seat2 §6; 1-seat4 §6 | correct K7 | Q3 |
| K rows | inventory | "K7" used twice | INCONSISTENT (labels) | inventory K7 against the builder K7 | rename | — |
| D-M3a | claim L1 | r = o − rec, −126.4 dB, 0 outside the fade | CORRECT (code) | abx_kit L389–396, L400–411 | — | — |
| D-M3a | claim L2/K4 | −68/−70 floor | IMPRECISE | docstring only; frame-boundary impulse | SWC | Q4 |
| D-M3a | claim | "already matches"; floor, A/B/E counts, null | INCONSISTENT (code) | abx_kit L429–436 | SWC | Q4 |
| D-M3a | criterion | per ear against channel 0 | IMPRECISE | abx_kit L406 | SWC | — |
| D-M3a | PRD proxy | FR-SIM-6 | PRD MISREAD (minor) | PRD L89 scoped to movement; NFR-1 L105 | SWC | — |
| D-M3b | claim | silence after N ≥ heard T30 | WRONG (code arithmetic) | gap < T30·fs + P, shift ≥ P; S-A 2.0053 < 2.009 s; both_wall 1.344 < 1.370 s | FAILS | Q1 |
| D-M3b | inference | onset as heard, gap on input | INCONSISTENT | both_wall heard gap 1.347 s < 1.370 s | FAILS | Q1 |
| D-M3c | claims | tails, powers, union rates | CORRECT | binomial recomputed | — | — |
| D-M3c | map | S1 split 2/2 but sum 8; S1 unsplit 0/0 c | TENSION MISREAD (neutral) | 1-seat1 §1 | SWC | — |
| D-M3c | map | Seat 1's "split only the 08-3 families" omitted | TENSION MISREAD (neutral) | 1-seat1 §1; Seat 6 split reason under D-M3h 2(d) | SWC | Q2 |
| D-M3c | debt | Seat 7 "a parameter change" | hidden premise / INCONSISTENT | 07c-2b items 6 and 8; the decider's S3/S7 row | SWC | Q5 |
| D-M3c | PRD proxy | "NFR-2 accepts" | PRD MISREAD (cited id) | PRD L106 "when they buy accuracy"; L101 | SWC | — |
| D-M3d | claim L7 | share, s_w | CORRECT | file 29 L30 | — | — |
| D-M3d | map | "≤ 1 c" | IMPRECISE | no seat rated an s value | SWC | — |
| D-M3e | inference | Class line | INCONSISTENT | 1-seat9 §6 layout-5 labels | SWC | — |
| D-M3f | claim K13 | specular share 0 at s = 1 | CORRECT | Kuttruff §8.8 Eq. 8.59 | SURVIVES | — |
| D-M3g | claim L5 | Table 5.2 case 5 | CORRECT | Kuttruff §5.7 Table 5.2 | — | — |
| D-M3g | claim L6 | r_c and D/R arithmetic | CORRECT | Kuttruff §5.6 Eq. 5.44 | — | — |
| D-M3g | claim L6 | Eyring A; ᾱ 0.28 non-diffuse | IMPRECISE (conditions) | Kuttruff §5.6 Eq. 5.44 ("Sabine's T"), the ᾱ caveat after Eq. 5.48; §5.7 | SWC | — |
| D-M3g | PRD proxy | AX21 paraphrase | IMPRECISE | BUILD_PLAN L144 | SWC | — |
| D-M3h | consistency | 2(c) "same scene" for every option | INCONSISTENT | 26-seat4 L32; 1-seat4 §4 V2 | SWC | — |
| D-M3h | debt | 2(d) second golden round against the one-round rule | INCONSISTENT unless stated | 07c-2b item 8; 1-seat3 §4 | SWC | — |
| D-M3i | text | α sentence, Reversal wording | faithful | BUILD_PLAN L170 | SURVIVES | — |

## Questions for the decider's rebuttal
1. **D-M3b.** The gap is less than T30 + P and the onset moves by at least one partition. Must the silence after N be ≥ the heard T30, ≥ every tail T30, or neither? Which quantity does the manifest assert, given that `gap_check` reads the programme gap?
2. **D-M3c.** What are the cells for Seat 1's "split only the 08-3 families" (Seats 1, 5, 6 and 7, read from conditions)? Does its maximum stay at 2?
3. **K7.** Will K7 add the following?
   - layout5_s1/emitter_wall under the new checks;
   - s = 0.8/0.9 fallbacks where s = 0.7 is uncapped;
   - the silence after N and the heard gap;
   - the difference in direct path between emitters;
   - Seats 2 and 4's conditions in the V6 trigger.
4. **D-M3a.** Will the −68/−70 bracket be asserted by a test, and the spike floor and the A/B/E counts printed? If not, is "already matches" withdrawn?
5. **D-M3c register.** Is Seat 7's "a parameter change" restated as a re-pin plus a golden round? Or is Seat 5's condition (W_max derived from B) adopted for 3 or fewer families?
