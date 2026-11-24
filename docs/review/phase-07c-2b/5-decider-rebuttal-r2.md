# 5: Decider rebuttal, round 2, on interrogator file 3 (everything except the scene choice)

To be saved as `docs/review/phase-07c-2b/5-decider-rebuttal-r2.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Where things stand:**
- **D-M3b falls and is revised below.** The interrogator showed from the code that my gap claim was wrong: moving the onset later shortened the silence after it below T30 on every scene.
- **D-M3a, c, d, e, g and h are accepted with the interrogator's corrections.** Their corrected texts are below.
- **D-M3f and D-M3i stand unchanged.**
- **The scene choice waits for the builder's K7 report** (file 4). It is not ruled on here.
- **One rename:** inventory row K7 in file 2 (both_wall's far-emitter burst ending at N + 1407) becomes **K17**. "K7" now means only the builder measurement.

## Answers to the interrogator's questions

**Q1 (D-M3b): the silence after N must be at least the heard T30 and at least every tail T30, measured as heard.**
- Every quantity is now taken as heard. For each emitter e, d_e = (directS − alignmentShiftS)·fs, the direct delay in the aligned IR. Δ = max d_e − min d_e.
- `gap_check` now reads these heard quantities, not the programme gap.
- The full rule is in D-M3b below.

**Q2 (D-M3c): Seat 1's "split only the 08-3 families" variant keeps a maximum of 2.** Its cells, all read from conditions:
- **Seat 1: 1/1 c.** It said "I can live with" this, without a number.
- **Seat 5: 0/1 c.** Its split reason applies.
- **Seat 6: 2/2 c.** Its split reason applies: under D-M3h 2(d), a miss at 08-3 leaves an admitted source in place.
- **Seat 7: 0/1 c.**

That gives a maximum of 2 and a sum of 8. Unsplit stays the winner at a maximum of 1.

**Q3 (K7): yes.** The coordinator has passed the four additions to the builder:
- layout5_s1/emitter_wall run under the new checks;
- s = 0.8 and 0.9 as fallbacks wherever s = 0.7 is uncapped, for every placement listed;
- the silence after N and every heard gap, per D-M3b;
- the difference in direct path between emitters (Δ, in ms).

The trigger for the one-scene option V6 now also names:
- Seat 2's C2: no placement within 0.1 m of a face, and Δ ≤ 2.5 ms. A candidate that fails C2 is still convened, with Seat 2's 2 carried.
- Seat 4's layout-5 condition: either layout 5 is left out of item 15, or its record is labelled "isotropic tail, anisotropic room" with per-ear tail energy printed.

"If no candidate qualifies, the map stands" is limited to the set K7 measures.

**Q4 (D-M3a): I withdraw "already matches".** The residual criterion and the red tests match the code. Three things are added:
1. **A pytest that asserts the bracket.** A single-sample spike is caught at −68 dBFS and missed at −72 dBFS. It is placed both mid-frame and on a frame boundary. The existing −65 dBFS red test stays.
2. **Printed in the record:** `spike_floor_dbfs`, computed as −90 − 10·log10(0.917/n_frame), which is −69.8 dBFS at 48 kHz, plus the asserted bracket.
3. **Printed only:** the detector event counts on A, B and E.

**Q5 (D-M3c register): the undo cost becomes a re-pin plus a golden round.**
- W_max is a pinned constant, `kWMaxPerEmitter`. Undoing a false reversal therefore means:
  - a board round;
  - a confirmatory person-ABX (about 2 h);
  - a W_max re-pin;
  - a second golden round, which needs a /fix-plan to the one-golden-round rule (07c-2b item 8).
- I do not adopt Seat 5's condition (W_max derived from B) for 3 or fewer families. It is O10/O4's design question, and it goes to that round as an input.
- Seat 7's own words ("recoverable as a parameter") put its later rating of 1 on a premise the plan does not support. The rating stands as given. Seat 7 is asked in the scene round whether it still holds.

## Corrected texts (to apply once they survive)

**D-M3a (corrected). click_check form (b).**
- **Criterion:** on every stimulus there is no `tools.acoustics clicks` event on r = (A − B) − m over [N − 5 ms, N + L + 5 ms).
  - The model m is (j/L)(E − B) on [N, N + L) and E − B after it, with L = 1440.
  - The detector is unchanged: 2 kHz zero-phase high-pass, 2 ms frames, 20 dB over the median, absolute floor −90 dBFS.
  - It runs on channel 0 in omni, where the two outputs are asserted identical, and on each ear at 08-3. `crossfade_residual` takes a channel argument.
- **Red tests:**
  - a hard switch at N (L = 0);
  - a −65 dBFS single-sample impulse inside [N, N + L);
  - the bracket from Q4 (caught at −68, missed at −72; mid-frame and on a frame boundary).
- **Green:** S-A's 50 stimuli, the two K5 stimuli, and every stimulus of each sealed scene. Bit-reproducible.
- **Printed:**
  - `spike_floor_dbfs` and the bracket;
  - the detector event counts on A, B and E;
  - the legacy comparison of A's events against B.
- **The null for a transient common to B and E.** Per sealed scene, B nulls against the offline render of the same programme within −120 dB (phase-06 L64–65).
  - E nulls the same way against the offline render of the stepped IR.
  - If `render_cli` has no offline path for E, E's reference is direct convolution of the programme with the IR that `--abx-stepped-ir` writes.
  - A null failure goes back to Seats 3 and 5. The tolerance is not loosened.
- **Plain statement:** the sample-level guarantee comes from companions (ii) and (iii). Form (b) makes the click line independent of the programme and proves it can fail.
- **PRD:** NFR-1 (L105) only. FR-SIM-6 is dropped, because it is scoped to movement.

**D-M3b (revised). Onset and gaps, as heard.**
- **Noise chain.**
  - Let T = the heard-IR T30, which M2 T-a keeps as the construction quantity.
  - **Gaps.** Each gap between bursts is built as ⌈(T·fs + Δ)/P⌉·P. So every heard gap, from the latest heard end of one burst (input end + max d) to the earliest heard start of the next (input start + min d), is at least T.
  - **Onset.** N is the first partition boundary at or after the heard end of burst 2 (input end + max d).
  - **Burst 3.** It starts at the input sample N + ⌈T·fs/P⌉·P. The heard silence after N, from N to burst 3's earliest heard start, is then at least T.
- **Speech chain.**
  - The input pause is at least T·fs + Δ, so the heard pause is at least T.
  - Onset boundaries must lie at or after the heard end of sentence 1.
  - Q5 is unchanged: onset no later than 0.43·T after the input end of speech, and the ≥ 20 dB onset assertion. The realised window is recomputed and recorded.
- **The manifest asserts, per stimulus:**
  1. N − (input end of the burst before N + d_e) ≥ 0 for every emitter;
  2. heard silence after N ≥ T;
  3. every heard gap or pause ≥ T;
  4. M2 (`gap_check` on heard quantities): the minimum heard gap and the heard silence after N are each ≥ every tail T30;
  5. item 7: at least one T of programme before N, and at least 2 s after it.
- **What this does to the numbers.**
  - Gaps only grow, by at most one partition plus Δ. No threshold changes.
  - S-A: Δ = 0, gap 96768, and N moves by +512. The silence after N is ≥ 96768 samples, against T = 96432.
  - both_wall: Δ = 1375. The gap is 67584 samples (heard 66209 = 1.379 s ≥ 1.370 s), N moves by +1536, and the silence after N is 66080 samples (1.377 s).
  - both_wall's tail T30 is still unmeasured; K7 measures it.
- **Layout 5:** the M2 assertion is expected to fail there (K10). Any layout-5 choice needs an M2 re-decision in the scene round.
- **Seat cells:** Seat 1 C3 and Seat 3 §6, both 0/0 c.
- **PRD:** NFR-1.
- **Reversal:** the realised Q5 window is empty on a scene. Then the deviation is pre-registered.

**D-M3c (corrected). α unsplit.** The decision text is unchanged.

| treatment | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| unsplit, 3 or fewer families | prefer, no number (0/0 c) | 1/1 | 1/1 | 0/1 | 1 | 5 |
| unsplit, 4 families | 0/0 c | 1/2 | 1/1 | 0/1 | 2 | 6 |
| split only the 08-3 families | 1/1 c | 0/1 c | 2/2 c | 0/1 c | 2 | 8 |
| split everywhere | 2/2 ("rated 2", no column given) | 0/1 | 2/2 | 0/1 | 2 | 10 |

- Even if Seat 1's unsplit cell were 2/2, unsplit wins on sum: 9 against 10.
- **Seat 7's register row:** the undo cost is restated as in Q5.
- **PRD:** L101 "Accuracy is the top priority" and L49. A split strains NFR-1 through lost power. L101's "must stay usable" is met, because Seat 6 records that a false reversal "does not make today's load worse". NFR-2 is withdrawn: it accepts CPU only "when they buy accuracy", and a false reversal buys none.

**D-M3d (corrected).** "Worst-off" now reads: no seat rated an s value. Seats 2, 3 and 9 prefer 0.7; Seat 4 makes 0.7 a condition; Seat 1 prefers 0.9 and can live with 0.7. The decision is unchanged.

**D-M3e (corrected).** "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states." The class is the Class line of the scene's item-9 label. Every sealed scene's label must carry a Class line; the kit refuses to build a manifest without one.

**D-M3g (corrected). Item-9 labels.**

*S-A, applied now in three places:*
- the run sheet §1 "Scene" bullet;
- `abx_kit.py`, in the `scene_layout4_s1_default` docstring and the manifest `label` / `label_detail`;
- through the kit, `listening_pack.py` L452.

The old string is removed from all three.
- **`label`:** `Direct-dominated test room, early reflections absent (AX21); not a validated preset`
- **`label_detail`** (the run sheet uses the same lines as bullets):
  - "20 × 30 × 10 m; floor α 1, other faces α 0.01; scattering s = 1 on every face; tailSeed 12345; emitters 12.4 m from the listener."
  - "D/R at 1 kHz +10.7 / +9.7 dB per emitter (heard L + R: +13.1 dB), against −10.8 dB at r/r_c 3.47 (Kuttruff Eq. 5.44, Sabine A ≈ 640 m²: 600 + 16 m² of surfaces, 24 m² of air). Indicative only: with ᾱ ≈ 0.28 and one face at α 1 the field is far from diffuse, where Kuttruff (§5.6) calls these relations questionable."
  - "Early part −76.7 dB re direct: empty (AX21; Maisara 2026-11-05: 'the early part should contain scattered energy', a known deficit, not rendered here)."
  - "Heard-IR T30 2.009 s (ISO fit spanning the AX21 gap, not a decay rate); tail T30 1.254 / 1.274 s; Eyring target 1.291 s."
  - "Class: direct-dominated, early part empty."
  - "Stimulus scene, not a room prediction."

*The other labels:*
- **Eyring-A figures** (−10.1 dB) are removed from every label. Eq. 5.44 rests on Sabine's T, so they are not a corpus expectation.
- **The ᾱ qualifier** goes on every D/R expectation line.
- **Seat 9's labels for S-B\*(0.7) and both_wall** keep their Class lines.
- **Layout-5 labels** get proposed Class lines. They are mine, and Seat 9 confirms them in the scene round:
  - default: "reverberant-dominated, early part empty";
  - emitter_wall: "tail-dominated, early part empty".
- **Layout-5 detail line:** Kuttruff Table 5.2 case 5 (long side wall α 1, others 0, diffusely reflecting walls) gives iteration 3.06 s against Eyring 2.99 s. The engine's tail follows Eyring.

*PRD:* NFR-1. The labels state the absence that her AX21 decision ("the early part should contain scattered energy", BUILD_PLAN L144) leaves to B11.

**D-M3h (corrected), items 2(c) and 2(d).**
- **2(c).** File 26-seat4 (a), "same scene and tailSeed … the chain is the only variable", applies to each 08-3 scene that was sealed in omni at 07c-2b. An 08-3 scene with no omni twin is recorded as "binaural only, no omni twin; its result stands alone" (Seat 4, V2). File 26-seat4 (b)–(d) apply to every 08-3 scene, with (c)'s wording fitted to the scene's Class line.
- **2(d).** An 08-3 detection is a reversal trigger for O10 and O4. The undo is:
  - a class (c) board round;
  - a W_max re-pin;
  - a second golden round. It needs a /fix-plan to the one-golden-round rule (07c-2b item 8) with a §6 row, decided before the 08-4 freeze. Until then no golden is regenerated.

  Items 1, 2(a), 2(b), 2(e) and 3 are unchanged. Item 3's M2 check now runs on the heard quantities of D-M3b.

## State
| id | state |
|---|---|
| D-M3a | revised (corrections applied) |
| D-M3b | revised (replaces the failed text) |
| D-M3c, d, e, g, h | revised (corrections applied) |
| D-M3f, i | stand |
| scene(s), family count, item 9 scene, item 15 scenes, V3 wording | research needed (K7, file 4) |

## Decided for Maisara (changes from file 2)
- **D-M3b:** the step starts after every source has actually fallen silent at the listener. Every silence the listener hears, before and after the step, is at least one reverberation time, and the stimulus file asserts that. Rests on NFR-1. Gaps get slightly longer; no threshold changes. Amends nothing.
- **D-M3c:** the reasoning now rests on PRD L101 and L49 (accuracy first, and the plugin stays usable), not NFR-2. Seat 7's undo cost is stated honestly: a re-pin plus a golden round. Amends nothing.
- **D-M3g:** the S-A label shown above replaces the vetoed "hall" label now, in the run sheet, the kit and the listening pack. Rests on NFR-1 and her AX21 decision of 2026-11-05. Amends nothing.

**NEEDS MAISARA:** none.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/3-interrogator-on-file2.md
- /home/user/makroof/tools/ci/abx_kit.py (L493–508, L548–559, L400–438)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (§1, L50–64)
- /home/user/makroof/docs/review/phase-07c-2/26-seat4.md (L32–35)
