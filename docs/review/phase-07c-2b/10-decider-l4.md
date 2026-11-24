# 10: Decider on AX49 L4 (with Seat 6), and rebuttal to interrogator file 11

To be saved as `docs/review/phase-07c-2b/10-decider-l4.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**This file does two things.**

Part A decides L4. Seat 6's answer is now in.
- **L-a is decided:** a validation-only `render_cli --provisional-ir` flag, with a second flag that sets a handover sample.
- **The scene** is the stone_box variant tuned to T60_max 8 s.
- **A and B** are static: A is the provisional IR, B the exact IR, both rendered on the real-time path.
- **Seat 1's design** and **Seat 3's assertions** are adopted.
- **AX49's wording** is amended through /fix-plan.

Part B answers interrogator file 11.
- M3-S, M3-G, M3-C and M3-F are corrected. **Two of the corrections change what the kit does; they are marked ⚙.**
- **M3-T is decided again**, now that Seat 1 has rated it.

NEEDS MAISARA: none.

---

# Part A: AX49 L4

## Convening
- **Convened:** Seats 1, 2, 3, 5, 6, 7, and 9 (narrow). All have answered. Seat 6 was added because file 11 found the round UNDERCONVENED without it: L4 tests what every user hears when a project loads.
- **Not required:**
  - Seat 4: the chain is omni and diotic.
  - Seat 8: this is a validation stimulus.
- **K23 restated:** `assembleProvisional` is called from `src/plugin/core/ScenePipeline.cpp` L656 and L704, and from `tests/unit/test_interim.cpp`. The test call is a precedent for L-b. It does not change the guard, which must name the CLI option field (Seat 5).

## Knowledge inventory (new rows; K1–K24 from files 2, 5 and 8)
| K | what | source | status |
|---|---|---|---|
| K25 | A guard that greps for "provisional" would fail on `src/plugin` | Seat 5, from the code | known |
| K26 | The gating pattern for validation flags (`--abx-step-db`, Cli.cpp L274–282, L350–375) and its guard test (`test_abx_kit.py` L188–197) | Seat 5, from the code | known |
| K27 | Stone variant: 0.161·2400/(1120·0.0431) = 8.0 s; t_mix,e ≥ 64.7 ms; L_f ≥ 2.561 s; L_p ≥ 2.661 s; L = min(1.5·T60_max, 12) = 12 s | Seat 2; Kuttruff Eq. 4.12 and 5.24; Engine.h L240 (from the code) | known as bounds; each value is measured and asserted |
| K28 | The 100 m "low-α" cube has T60_max 50.5 s and L_p ≥ L, so it cannot host L4. At T60 8 s the cube's ᾱ would be 0.23–0.29 | Seat 9; AX49 K22; Kuttruff Table 6.1 | known |
| K29 | After an interrupted steady excitation, the decay equals the backward-integrated IR | Kuttruff §8.4 Eq. 8.29; Vorländer §6.4.1 Eq. 6.3 (Seat 3) | known |
| K30 | At equal T60, a smaller volume cuts earlier and louder (t_mix,e grows with √V; K20) | Seats 2 and 9 [Inf] | the direction is known; the depth is measured per band |
| K31 | Is a −19 dB cut, or a re-onset after silence, audible? | Seats 1 and 3 [Hyp] | uninformed. Not load-bearing: L4 is the test |
| K32 | Phase 11 requires "settling" while crossfading, but `settling()` leaves out a running crossfade | Seat 6: BUILD_PLAN L365; phase-07c-1b L124 | known (plan) |

## Tension map (now/later, in the seats' words)
| option | S1 | S2 | S3 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|
| **L-a** | 0/1 (0/0 under L-a1) | 1/0 | 1/1 | 1/1 | 0/1 | 1/1 | 0/1 | **1** | 10 (9 with L-a1) |
| L-b | 1/1 | 1/1 | 1/**2** | 1/**2** | 1/1 | 1/1 | 0/0 | 2 | 14 |
| L-c | 1/**2** | 1/**2** | 1/**2** | 0/**2** | 1/**2** | 1/**2** | 0/1 | 2 | 18 |

The seats' reasons, as they gave them:

**L-a**
- S1: "if the flag is off by default". Later, the risk that a flagged render ends up in a golden or a BRAS comparison.
- S2: "no engine change". Later, "Removal is one flag".
- S3: "condition 6 erodes".
- S5: "every later flag change" must keep the guard green.
- S6: "Producers hear no difference". Later, the ghost and the "indicator-clears-before-handover" issue go unheard.
- S7: one /fix-plan, in orchestrator time.
- S9: "a provenance risk".

**L-b**
- S3: a second renderer to maintain.
- S5: a binary that is "neither the shipped one nor the CLI".

**L-c**
- S6: 07d would trade load time against a gated tail "by rationale".
- S7: rises to 3 if L4 slips past 08-4.

## Working
1. **Bounds.** L-a changes AX49's wording. AX49 is a board row (D-C9), so this is allowed. None of Maisara's recorded decisions is touched, and `src/sim` is not touched.
2. **Veto.** No seat gives a 3.
3. **Worst-off seat.** L-a has a maximum of 1. L-b and L-c have 2. **L-a.**

Steps 4–6 are not reached.

## DECISION L4-P: the flags (`src/cli` only)
**`--provisional-ir`** (validation-only, off by default)
- render_cli builds on the same plan, at the solve's level, then calls `assembleProvisional()` in place of `assemble()`.
- Every output of that run uses the provisional IR: `--ir`, and `--out` with `--in`, both offline and with `--realtime-emulation`.

**`--provisional-timing <json>`** (allowed only with `--provisional-ir`)
- Writes `provisionalTiming()`: provisional, mixMaxS, t60MaxS, fadeStartS (L_f), endS (L_p), exactS (L) and the per-band T60.

**`--provisional-handover-sample N`** (Seat 6, condition 2)
- Requires `--provisional-ir`, `--realtime-emulation`, `--in`/`--out` and a fixed `--block`. N must be a multiple of the partition.
- Output: the provisional IR until N, then the shipped AQ4 30 ms equal-gain crossfade to the exact IR (AX49 "Handover"; AX18), through the IR swap of the real-time engine.
- Used only for one **unscored, labelled** listening-pack render. It is never sealed and never scored.

**Refusals** (exit 1, with the conflict named):
- (r1) `provisionalTiming().provisional` is false, i.e. L_p ≥ L.
- (r2) `--mode` is anything other than `omni`.
- (r3) Combined with any of: `--diagnostics`, `--ensemble`, `--tail-only`, `--ensemble-emitter`, `--tail-level ax16`, `--switch-scene`, `--switch-every`, `--abx-step-db`, `--abx-stepped-ir`, `--image-cap`, `--automation` (where present).
- (r4) `--provisional-timing` or `--provisional-handover-sample` without `--provisional-ir`.
- (r5) A handover sample that is not a multiple of the partition, lies beyond the input, or comes without `--realtime-emulation` and a fixed block.

**Tests** (CI with `SPATIAL_REQUIRE_RENDER_CLI=1`, three OSes, before any L4 seal):
1. **Guard.** `src/plugin` never names `provisionalIr`, `provisionalHandoverSample`, `--provisional-ir` or `--provisional-handover-sample`. Only `src/cli/Cli.cpp` reads the option fields.
2. **No golden path.** A `tools/ci` pytest checks that the flag strings appear nowhere in golden-generating or BRAS code. They may appear only in Cli.cpp, its tests, `tools/ci/abx_kit.py`, `tools/ci/listening_pack.py`, `tools/ci/test_*.py` and `docs/`.
3. **Default output unchanged.**
   - Every existing golden and render test passes unchanged.
   - A pinned SHA-256 of the default `render_cli --mode omni --ir` output on `medium_room.json`, built from the same binary.
4. **Determinism.** Flagged output is bit-identical from run to run (AX5).
5. **Offline against real-time.** The flagged offline output and the `--realtime-emulation --block 512` output null within −120 dB (Phase 06).
6. **Refusals.** r1–r5 each exit with code 1. r1 is checked on AX49's L_p ≥ L cube.
7. **Plugin parity** (a JUCE-free `[pipeline]` test). On the L4 scene, the keyless-load interim IR (ScenePipeline L652–656) is bit-identical to the IR written by `--provisional-ir --ir`.
8. **Handover.**
   - Before N, the output is bit-identical to the `--provisional-ir` render.
   - From N + 1440 on (48 kHz), it is bit-identical to the default exact render.
   - Inside the fade, it reconstructs to 8u (`midfade_checks`).

**Comment.** Engine.h L295–298 changes to "render_cli calls it only under `--provisional-ir`".

## DECISION L4-W: AX49 wording (/fix-plan, §6 row)
**The render_cli sentence.**
- Replace: "Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6)."
- With: "Offline renders and bounces in hosts that signal offline never use the provisional, and neither does `render_cli`, except under the validation-only `--provisional-ir` flag (off by default; omni only; refused with `--diagnostics`, the ensemble, switch, step and image-cap flags and where L_p ≥ L; an optional handover sample for unscored listening-pack renders only; never reached by `src/plugin`, never used for goldens; tests in phase-07c-2b decider file 10). AX5, condition 6."

**Additions to AX49.**
- **Listening item L4** gains: "scene, stimuli and assertions: phase-07c-2b decider file 10".
- **07d's reversal inputs** gain the ghost print (L4-D 13).
- **The D-C9 debt register** gains Seat 6's line: "settling must stay lit through the handover crossfade". Its home is Phase 11's settling item (BUILD_PLAN L365), together with the follow-up at phase-07c-1b L124.

## DECISION L4-S: the scene
**What it is.**
- `tests/scenes/valid/stone_box.json`: 20 × 12 × 10 m; listener (10, 8, 1.7); emitters (8, 3, 1.7) and (12, 3, 1.7); s 0.1; tailSeed 106.
- Every band's α is multiplied by one common factor k, starting at 0.844. The builder adjusts k until `--provisional-timing` reports T60_max = 8.0 ± 0.1 s. k is recorded.
- The scene JSON and its SHA-256 are committed with the kit.

**Asserted before the seal:** provisional is true, L_p < L, and L_f, L_p, L and the per-band T60 are printed.

**Why not the cube.** The cube cannot host L4 (K28). At T60 8 s a smaller volume cuts shallower, so it is easier to hear (K30). Seat 6 adds that it is "more like a producer's large hard-room preset".

**Label** (Seat 9's template with Seat 2's wording; Seat 9 confirms it before the seal):
- `label`: "Long-decay test room, hard stone box with uniform absorption, T60_max 8 s; provisional-vs-exact tail test (provisional tail, validation-only flag); not a validated preset"
- Detail lines:
  1. Geometry; α = k × stone_box per band; s 0.1 (early part specular only, AX21); tailSeed 106; 48 kHz; emitters 5.39 m away.
  2. T60 per band; T60_max [8.0] s in band [b].
  3. D/R at 1 kHz [measured] against [ ] dB at r/r_c [ ] (Kuttruff Eq. 5.44, Sabine A [ ] m²). ᾱ ≈ [0.04–0.07] is small, so §5.6's ᾱ caveat does not apply.
  4. t_mix,e,max, L_f, L_p and L [12.0] s.
  5. Cut depth per band: 10·log10(E_B[L_f, L)/E_B[0, L)), printed beside the chord's band energy.
  6. The early reflections are identical in A and B.
  7. "Stimulus scene, not a room prediction."
- Class line: "long-decay, [Seat 9's D/R class] (heard D/R [ ] dB), cut [ ] dB in the T60_max band"

**Record wording** (Seats 9 and 6):
- On non-detection: "not detected in 16 trials by one listener (power 0.63 at p = 0.75); covers a cut ≥ [measured] dB below the full-IR energy in the T60_max band at T60_max 8 s".
- Never "inaudible", and never "at T60 8 s" alone.

## DECISION L4-D: design and assertions
**A and B** (Seat 3)
- A is the provisional IR (`--provisional-ir`). B is the exact IR from the same plan.
- Both are rendered with `--realtime-emulation --block 512 --partition 512`.
- Both are static: the handover is not part of the scored stimulus.

**Chord** (Seat 1)
- Deterministic additive synthesis, versioned in the kit. Open voicing C2–G2–C3–E3–G3–C4, equal-tempered.
- Harmonic partials up to 8 kHz, tilted −3 dB/octave; no vibrato.
- 50 ms onset; 10 ms raised-cosine release.
- Band energies printed.

**Timing**
- Hold H = max(L_p, 0.5·T60_max), which is 4 s.
- One release per file, then at least L + 0.5 s of silent input.
- The whole exact decay must fit in the file (asserted). A and B are the same length.

**Fully wet**
- The whole room IR: direct, early and tail.
- No dry path, no tail-only render.
- Diotic.
- No normalisation: one fixed, recorded gain for all files.
- Peak ≤ −3 dBFS.

**Trials**
- 16 scored trials. Detection at ≥ 12/16. This is its own family.
- 6 anchor trials (3 up, 3 down) at seeded positions, pass mark ≥ 5/6. The anchor is B against B with the tail stepped ±3 dB (`--abx-step-db ±3 --abx-step-sample 0`), on the L4 scene and chord.
- Blocks of 22 trials, with a break after trial 11.
- Familiarisation includes a labelled A/B pair.
- No 0.5 dB block.

**Assertions on every stimulus** (Seats 3, 1, 9; print-only items say so)
1. The provisional flag is recorded, with "provisional tail, validation-only flag" in the manifest.
2. A and B agree bit for bit before the earliest tail crossfade starts.
3. Prefix (AX47 (b)): 10·log10(E(A − B)/E(B)) ≤ −18.27 dB over [t_mix,e, L_f − h), per emitter and band.
4. Over [t_mix,e,max + 2.5 ms, L_f), the A/B energy matches AX47 (b)'s predicted step within 0.05 dB.
5. A is zero from L_p on.
6. B is L long.
7. Decay from t_mix,e,max to L_f is at least 18.7 dB in every band.
8. B's share past L_f is at most 0.0134 per band.
9. Print: the A/B level difference over the held part, per band.
10. Silence after the release is at least L.
11. Peak ≤ −3 dBFS.
12. Two builds are bit-identical.
13. **Ghost print** (print only; Seat 3 item 9 and Seat 6 condition 1): per band, the re-onset level from B's backward-integrated curve at release + L_p + {0, 1, 2, 5} s.
14. **Listening pack** (Seat 6): one unscored render, "L4 handover demo (unscored; interim then handover, as at project load)". It uses the L4 chord, releases at t_r and hands over at the first partition boundary at or after t_r + L_p + 1 s. It is built with `--provisional-handover-sample` and is added to `listening_pack.py` under phase-07c-2b.

**Not adopted:** Seat 1's optional fade and L_f-fraction parameters. They go to 07d as a follow-up, to be used only if L4 detects. Whether the ghost needs its own ABX is put to Seat 1 in 07d, after Maisara has heard the demo.

## DECISION L4-T: sittings (Seat 7)
- K6 is redone on the sealed L4 stimuli.
- L4 runs as its own block, with its own anchor, in E's second sitting if that sitting stays within 2 h. Otherwise a third dated sitting goes into the brief before any seal.
- L4 is sealed with E, before the session.

## Load-bearing claims (L4)
- **L4-L1:** L-a has a maximum of 1. L-b and L-c have a maximum of 2 (the map above).
- **L4-L2:** K27's bounds. The realised values are measured and asserted.
- **L4-L3:** K28, the cube is excluded.
- **L4-L4:** K25 and K26, the guard pattern.
- **L4-L5:** e^(−4.312) = 0.0134 (AX49 K17′).

## Future-debt register (L4-a)
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | Later 0 under L-a1 | — | — | — |
| 3 | Validation flags call `assembleProvisional` from render_cli; condition 6 could erode | Delete the flags | Tests 1–3 | Green on three OSes |
| 3, 6 | The handover ghost is untested; "settling" clears before the crossfade (K32) | A 07d remedy round; the `settling()` fix in Phase 11 | Ghost print, the demo render, a researcher finding on re-onset audibility, the Phase 11 checklist | 07d rules on the ghost; Phase 11 keeps settling lit through the crossfade |
| 5 | Every later flag change keeps the guard green | Delete the options | Default hash (test 3) | Each CI run |
| 7 | render_cli carries the path; a possible third sitting | Flag deletion; one sitting | K6 on L4 | Per-sitting plan in the brief |
| 9 | render_cli produces a non-room IR | A label line | Manifest | The validation-only line is printed |

## Strongest objection
- **Seats 7 and 9 prefer L-b.** It still leaves Seats 3 and 5 at a later 2.
- **Seat 5's condition (iv)** asked for output "bit-identical to the default" on the L_p ≥ L scene. This decision refuses there instead (r1, Seats 2 and 3).
  - If Seat 5 holds that refusal fails its condition, L-a becomes 1/2. That ties L-b's maximum, but L-a still wins on sum.
- **The handover flag is Seat 6's addition.** Seat 5 has not rated it. It follows Seat 5's own gating pattern and its tests (1, 6, 8).

**Confidence:** medium.

**Reversal:** any of the following.
- Seat 5 rejects r1 or the handover flag.
- A pre-seal assertion fails on the stone variant.
- Test 7 fails (then L4 goes back to the board).

---

# Part B: rebuttal to interrogator file 11

All corrections in file 11 are accepted. The kit-behaviour changes (⚙) are for the builder, who is already implementing M3-S, M3-G and M3-C.

## M3-S (corrected)

**⚙ Label, E** (adds one detail line to `label_detail`). It replaces the ITDG line:
> "ITDG 0.6 ms (S0's wall image, notch ≈ 860 Hz), 0.89 ms (S0's floor image, notch ≈ 560 Hz) and 1.6 ms (S1's floor image, notch ≈ 320 Hz), all inside the ±2.5 ms direct window and counted as direct; specular amplitude √(0.99 × 0.1) = 0.315 (+2.4 / −3.3 dB at the wall image)."

The other label lines and the Class line are unchanged from file 8.

**D-M3d is dormant.** S-B\* is not run under M3-S. The value s = 0.7 holds for any later use.

**Strongest objection** (restated):
- Seats 2 and 9 prefer B.
- If E rose by 1 in any cell, **D** (sum 14) would tie or lead.
- B leads only if both emitter_wall scenes fail C4.

**Decided for Maisara: one line per surviving option.** The PRD tests are NFR-1 (sensitivity and fidelity), NFR-8 L112 (scope of a non-detection by class) and L101 (accuracy first, the plugin stays usable).
- **E, layout5_s0.9/emitter_wall (chosen):**
  - NFR-1: the hardest s < 1 scene that qualifies (ΔG 0.778 dB, 0.014 dB under V3's s = 1 scene), with specular-only early reflections.
  - NFR-8: a tail-dominated class.
  - L101: about 2.5 h in two sittings.
- **D, layout5_s0.8/emitter_wall:**
  - NFR-1: slightly less sensitive (0.763 dB), with a fuller early part.
  - NFR-8: the same class.
  - L101: the same hours.
  - Strains NFR-1 only through Seat 1's 1 now.
- **B, layout5_s0.8/default:**
  - NFR-1: less sensitive (0.46 dB).
  - NFR-8: a near-balanced class, so the far-listener class goes untested (strains it).
  - L101: the same hours.
- **layout5_s0.9/default:**
  - NFR-1: near-empty early structure (Seat 3 later 2), which strains it.
  - NFR-8: near-balanced.
- **layout4_s0.7/both_wall:**
  - NFR-1: wet, with a full early part.
  - It puts the listener 0.1 m from a wall, which is not a real seat (Seat 2's 2). That strains NFR-1's real-space fidelity.
  - L101: 1.76 h.
- **V3′, layout5_s1/default:**
  - NFR-1: the early part is empty, which strains it.
  - NFR-8: near-balanced.
- **V1, V2, V3:** as in file 8. Each has a seat at 2 later, which strains NFR-1.

## M3-G (corrected)
- **M3S-L4, restated:**
  - Sentence 2 starts at s1_end + ⌈(0.43·T_h + T)·fs⌉ + Δ.
  - Its earliest heard start adds min d.
  - The onset is at most eos + 0.43·T_h·fs, with eos ≤ s1_end.
  - So the silence after the onset is ≥ T·fs + Δ + min d ≥ T·fs.
- **Cost on E:** "about +1.2 s per speech stimulus" (3.729 s against 2.560 s). **⚙ K6's redo includes the longer pause, about +0.08 h.**
- **Plain-language line:** "every gap and pause, and the silence after the step, is at least the longer of the measured reverberation times, as heard". The lead-in silence is excluded.
- **Unchanged:** the construction and the assertions. The noise check on E (G = 126464, heard 2.606 s ≥ 2.600 s) is confirmed.

## M3-C (corrected)
- **Item 8:** "Seat 7's 'rises to 2' trigger is **avoided**". Its trigger is the confirmatory ABX falling after the 08-4 freeze.
- **Item 9:** "The engine's Eyring tail on floor-absorbing layouts is inferred to run about 14 % long. That comes from Kuttruff Table 5.2 case 4 (1.38/1.21, with the other faces at α 0 and diffusely reflecting walls), carried over to layout 4 (α 0.01 plus air) as an inference [Inf; Seat 9]." It is a report only, and nothing is tuned.
- No kit change.

## M3-F (corrected): the full apply list for /fix-plan
1. **AX47.** In the Reversal, "capped layout-4 scene" becomes "capped layout-4 or layout-5 scene". Add D-M3i's α sentence. One §6 row.
2. **The held file-13 amendments.**
   - **Item 9** becomes scene E, with its label, r/r_c 8.46 / 4.74 and D/R −18.6 / −13.5 dB. It replaces file 31's S-A numbers.
   - **Item 13** is D-M3e.
   - **Item 15** is M3-S's text.
   - Homes:
     - `docs/validation/abx-07c-2-run-sheet.md` §1 "Scene";
     - the run sheet's item-15 entry under §7;
     - `docs/phases/phase-07c-2b.md` scope 2, "Amendments held for M3", marked applied with this file.
3. **M2 re-decision (M3-G).**
   - The run sheet's construction text for gaps and pauses (L50–55, L61–64).
   - The "M2 debt checks" bullet in phase-07c-2b scope 2.
   - A note in both that M3-G (file 8) replaces file 34 item 3's construction premise. Review files are not edited.
4. **phase-08-3.md:** the item-15 entry with Seat 4's L5 label, its prints and its scope.
5. **phase-07c-2b item 8:** D-M3h 2(d)'s exception to the one-golden-round rule, with its §6 row.
6. **B11 homes** for D-M3h 1 plus C-b: phase-05e scope (b), BUILD_PLAN's deferred B11 entry, and the phase-05b row.
7. **Follow-ups:**
   - the 14 % report (M3-C 9), next to file 40's 8 kHz item in phase-08-4 "Notes from the split", and in the PR Follow-ups;
   - Seat 1's optional remedy parameters, in 07d.
8. **AX49:** L4-W, and Seat 6's settling line in Phase 11's settling item.

## M3-T (decided again)
**Convening.**
- **Seat 1, convened.** The speech pair is item 8's blind-test signal, which falls under Seat 1. Its answer is file 9-seat1-l4 §"M3-T".
- **Seats 2–9, not required:**
  - The pair does not change the scene, the engine, the chain or any user control. That covers Seats 2, 4, 5 and 6.
  - It does not change the hours, because the speech stimulus length is set by the pause rule. That covers Seat 7.
  - It does not change a label (Seat 9) or any producer workflow (Seat 8).
  - Seat 3's interest, the nulls, is a pre-seal condition already listed in M3-C 7.

**Options**
- (a) MA01_01 + MA01_02.
- (b) Another pair, which would need re-measuring.

**Map.** Seat 1 on (a): "I accept", on condition that "the pre-registration states the selection grounds". Entered as 0/0 c. Its condition is adopted. (b) is unrated; no seat asked for it.

**Corrected claim.** On the speech stimuli, the ≥ 20 dB assertion and form (b) pass on all 16 scenes (file 4, facts 4 and 9). **E is nulled on speech; B is nulled on noise only** (fact 5).

**⚙ Open before the seal (Seat 3, M3-C 7).** B must be nulled within −120 dB on every speech stimulus.

**DECISION M3-T:**
- Speaker MA (an adult; TSP's documentation records it, and the children CA and CB are excluded, abx_kit L737).
- Files MA01_01 and MA01_02, at 48 kHz.
- The pre-registration states the selection grounds: the pair was fixed for its measured Q5, form-(b) and E-null results, before any blind result.
- Our SHA-256 of `48k.zip` and of each excerpt is recorded (item 12).

Confidence: high. Reversal: Seat 1 objects, or B fails the speech null.

---

## Summary
| id | decision | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| L4-P | `--provisional-ir`, `--provisional-timing`, `--provisional-handover-sample`; refusals r1–r5; tests 1–8 | proposed | 1 | 9 | medium | NFR-1, NFR-8 | — (code) | Seat 5 rejects r1 or the handover flag; parity fails |
| L4-W | AX49 wording, plus the Phase 11 settling line | proposed | 1 | — | high | NFR-1 | — | — |
| L4-S | stone_box with α × k, T60_max 8.0 ± 0.1 s; label; cut-depth scope | proposed | — (Seat 9 confirms the label) | — | medium | NFR-1, NFR-8 | Eq. 4.12, 5.24, 5.44 | pre-seal failure |
| L4-D | static A/B; chord; anchor; assertions 1–14 | proposed | 0 | — | medium | NFR-1 | Eq. 8.29, 6.3, 6.4 | — |
| L4-T | own block in E's sitting 2, else a third dated sitting | proposed | 1 | — | high | L101 | — | K6 on L4 |
| M3-S | E; item 15; n = 2; ⚙ label line; D-M3d dormant | revised | 1 | 13 | medium | NFR-1, NFR-8 | Eq. 5.44, Table 5.2 | pre-seal failure, then D, then B |
| M3-G | max rule; pause +1.2 s; ⚙ K6 | revised | 0 | 0 | high | NFR-1 | — | — |
| M3-C | items 8 and 9 reworded | revised | 1 | — | medium | NFR-1, NFR-8 | Eq. 2.50, Table 5.2 | — |
| M3-F | full apply list (1–8) | revised | 0 | — | high | NFR-1 | — | — |
| M3-T | MA01_01 + MA01_02, grounds pre-registered; ⚙ B speech null open | decided again | 0 c | 0 | high | NFR-1 | — | Seat 1 objects; null fails |

**Challenges to settled decisions:** AX49's render_cli clause is a board row (D-C9). M2's gap construction is a board decision. Neither is one of Maisara's recorded decisions.

## Decided for Maisara
- **L4.** The test of the shortened "provisional" reverb, which plays while a large room loads, is built with the main test's own tool. It uses a switch that is off by default, which the plugin can never reach and no reference file uses.
  - A small, very reverberant stone room is used, where a cut is easiest to hear. A held chord is released into 12 s of decay.
  - An unscored demo of the real load-time handover goes into the listening pack, so that you can hear the "tail comes back" effect.
  - PRD: NFR-1 (L4 is the test AX49's reversal reads) and NFR-8 (no engine change).
  - L-b, a separate harness, strains NFR-1's evidence chain, because the stimuli would come from a binary that is not the shipped one. L-c, running L4 later, strains NFR-1, because class (c) and the W pin would be decided without it.
  - Seats 7 and 9 give up their preferred option, L-b.
  - Amends nothing of yours.
- **Scene and gaps (M3-S, M3-G, corrected).** The test room is the hardest qualifying one among those with scattering below 1, and its early reflections are specular only. Every gap and pause, and the silence after the step, is at least one reverberation time as heard. NFR-1, NFR-8, L101. Amends nothing.
- **Speech pair (M3-T).** Speaker MA, two sentences. It was chosen for its measured checks before any listening, and is accepted by the seat responsible for perception. NFR-1. Amends nothing.

**NEEDS MAISARA:** none. Raise item 2 remains a person's action: two sittings of about 1.25 h each for E, plus about 20 minutes for L4. The L4 block either joins the second sitting or becomes a third, short sitting.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/9-seat{1,2,3,5,6,7,9}-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/11-interrogator-on-file8.md
