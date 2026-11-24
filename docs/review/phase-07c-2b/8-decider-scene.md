# 8: Decider on M3, round 3: the scene decision, the gap rule, the adopted conditions, the TSP pair and AX49 L4

To be saved as `docs/review/phase-07c-2b/8-decider-scene.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **Scene.** The AX47 self-ABX runs on **one scene, `layout5_s0.9/emitter_wall` (V6-E)**, in omni at 07c-2b. Item 15 reruns the same scene in binaural at 08-3.
- **Families.** That makes 2 families, with a union false-reversal rate of 0.098 or less.
- **Gap rule.** It becomes T = max(heard T30, every tail T30). This changes M2. In the speech chain the pause is lengthened, so that the silence after the step is at least T.
- **AX47.** Its Reversal wording is widened to "layout-4 or layout-5" through /fix-plan.
- **Conditions.** Every condition in point 3 of the brief is adopted.
- **TSP pair.** Fixed as MA01_01 + MA01_02.
- **AX49 L4.** Goes back to the seats (**CONVENE**). Its stimuli need a code change in `src/cli` and a change to AX49's wording, and no seat has rated either.
- **Seats 5 and 6** are not re-convened. The family count falls from 3 to 2, which is inside the range they rated ("at most 3").
- NEEDS MAISARA: none.

## PRD digest (unchanged from file 2, two additions)
- NFR-1 (L105), NFR-8 (L112), L49 and L101 ("Accuracy is the top priority … must stay usable"), and L55 ("no fixed deadline").
- Her decision of 2026-11-05 under AX21 (BUILD_PLAN L144), reported speech: the early part should contain scattered energy. The plan's AX21 row defers the fix to the B11 rule.
- Bounds:
  - file 13's thresholds, α, trial counts and item 4;
  - Q5 as recorded in file 40, 2a;
  - AX47's Reversal wording, which is a board row;
  - AX49's "render_cli never use the provisional", also a board row.
- Verification culture (CLAUDE.md): every DSP behaviour is checked automatically, and each gate is shown red once.

## Knowledge inventory (new rows; K1–K17 as in files 2 and 5)
| K | what | source | status |
|---|---|---|---|
| K18 | Caps, peaks, share, ΔG, ΔC80, early part, T30 heard and tail, s_w, item 6 and M1, form (b), nulls, Q5, gaps, C2, hours for 16 scenes | file 4, Tables 1–4 and facts 1–13 | known (builder, from the code) |
| K19 | E: capped at m = 6, 7, 8; peak −8.0 to −4.8 dBFS; heard D/R −9.5 dB; share 0.852; ΔG 0.778 dB at 1 kHz; early part −8.6 dB; specular share 0.022/0.001; heard T30 2.560 s; tail T30 2.582/2.600 s; Q5 window [0.013, 0.380]·T; 2.39 h | file 4 L53, L101, L180, fact 13 | known |
| K20 | Kuttruff Table 5.2: case 5 gives iteration/Eyring 3.06/2.99 (+2.3 %); case 4 gives 1.21/1.38 (−12 %) | corpus L2782–2793 | known |
| K21 | The near-wall rise of Eq. 2.50 is not rendered in either chain | Seat 4 (Kuttruff §2, corpus) | known (Seat 4's arithmetic) |
| K22 | With the builder's programme, E's heard gap between bursts 1 and 2 is 26 ms short of its tail T30. The programme left out Δ | file 4 fact 7 | known. The revised construction closes it; re-measuring is condition C4 |
| K23 | `StagedBuild::assembleProvisional` exists in `src/sim` (Engine.h L298) and is called only from `src/plugin/core` | from the code | known |
| K24 | L4 scene with T60 8 s and L_p < L: L_f, L_p and L for a concrete scene | AX49 gives "L_p ≈ 3.7 s … at T60 8 s / 100 m" only for the gated geometry | under-informed, and so is the L4 cost (Seat 7) → CONVENE |

## Tension map, scenes (now/later; c = cell the seat stated conditionally, its condition adopted below)
Seats 5 and 6 are at 1/1 on every row with 3 or fewer families (unsplit). V1 has 4 families, so Seat 5's later cell is 2. Seat 8 is not required (file 31).

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| **V6-E L5 s0.9/emitter_wall** | 0/0 (under max+Δ) | 1/1 (C2′+C4) | 1/1 c (M2 max) | 0/1 (L5) | 1/1 | 1/1 | 1/1 c (gap T=max+Δ, re-measured) | 1/1 c (C-a) | **1** | **13** |
| V6-D L5 s0.8/emitter_wall | 1/0 | 1/1 | 1/1 c | 0/1 | 1/1 | 1/1 | 1/1 c | 1/1 c | 1 | 14 |
| V6-B L5 s0.8/default | 1/1 | 1/1 | 1/1 c | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1 | 15 |
| V6 L5 s0.9/default | 1/1 | 1/1 | 1/2 c | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 2 | — |
| V6 L4 s0.7/both_wall | 1/0 | **2**/1 | 1/1 | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 2 | 15 |
| V6 L4 s0.7/listener_wall | 2/**3** | 2/1 | 1/2 | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 3 | — |
| V1 | 2/2 | 1/1 | 1/1 | 0/2 | 1/2 | 1/1 | 2/2 | 1/1 | 2 | — |
| V2 | 0/0 | 2/1 | 1/1 | 0/1 | 1/1 | 1/1 | 1/1 | 1/2 | 2 | — |
| V3 | 0/0 | 1/1 | 1/1 c | 0/2 | 1/1 | 1/1 | 1/1 | 1/2 | 2 | — |
| V3′ | 1/0 | 1/1 | 1/1 c | 0/2 | 1/1 | 1/1 | 1/1 | 1/2 | 2 | — |

Reasons, in the seats' own words:
- **E:**
  - S1: "Strongest qualifying cue" under the max rule with Δ.
  - S2: the 0.1 m emitter is "a realistic placement"; its LF-image error is "identical in A and B … affects the label only".
  - S3: "Same M2 condition".
  - S4: L5 lowers later from 2 to 1 ("Lopsided early part, then a symmetric tail").
  - S7: "1" now; "2 as measured" later, lowered to 1 by the gap fix and re-measure.
  - S9: "Only with condition C-a".
- **D:** S1: "Early part −5.2 dB, so more gap dilution".
- **B:**
  - S1: "far-listener, tail-dominated class … stays untested".
  - S2: prefer (Note A).
  - S9: prefer.
- **L5 s0.9/default:** S3: "close to S-A's empty structure".
- **both_wall:** S2: "no change lowers them below 2 while the listener stays at 0.1 m".
- **listener_wall:** S1 later 3: "No late-dominated scene would be tested before the Phase 08 freeze".
- **V1:** S7: 3.83 h before the pin.
- **V2, V3, V3′:** S9 later 2: "O10 would be read only from a scene with an empty early part"; S4 later 2 on V3 and V3′.

## Working (minimum tension)
1. **Bounds.** E, D and B are layout 5. They need AX47's Reversal widened by a board /fix-plan, which is allowed. Every option is kit-side, so NFR-8 is not touched.
2. **Veto.** listener_wall is dropped on Seat 1's later 3.
3. **Worst-off seat.** E, D and B have a maximum of 1. Every other survivor has a maximum of 2.
4. **Compose.** Not needed: a maximum of 1 is reached.
5. **Sum.** E has 13, D 14, B 15. **E.**
6. **Reversibility.** Not reached. Fallback order if E fails a pre-seal check: D, then B. Each has its own check before its seal.

**Item 15 (my composition).** Item 15 is one scene: E in binaural, at the bound in force, under Seat 4's L5 condition.
- S-B\* is dropped from 08-3:
  - Seat 1 called it "not worth a family as a detection gate".
  - K18 shows it is the driest scene (share 0.032).
  - Its purpose, s < 1 evidence before O10 for Seats 3 and 9, is now met by E itself.
- With this choice:
  - Seat 4's later 1 (twin kept, L5 met) is the cell Seat 4 gave. Leaving layout 5 out of item 15 would have been 0/2.
  - Seats 5, 6 and 7 rated fewer families as cheaper.
- Family count: **2**. Union ≤ 2 × 0.049 = 0.098; 1 − 0.951² = 0.0956 if the families are independent. This lies inside Seats 5 and 6's rated range (at most 3 families, unsplit, 1/1), so they are not re-convened.

## DECISION M3-S: the scene and item 15
**Plan text.**
- **Item 9 (file 13, run sheet §1):**
  - `layout5_s0.9/emitter_wall`: 20 × 30 × 10 m; x = 0 wall (30 × 10 m) at α 1; other faces at α 0.01; s = 0.9 on every face in every band; tailSeed 12345; 48 kHz.
  - Listener (10, 8, 1.7); S0 (7, 29.9, 2) at 22.1 m; S1 (13, 20, 2) at 12.4 m.
  - Asserted capped at m = 6, 7 and 8. r/r_c is 8.46 / 4.74; diffuse D/R −18.6 / −13.5 dB (Kuttruff Eq. 5.44, Sabine A ≈ 343 m², ᾱ ≈ 0.145).
  - The scene JSON is committed with the kit, and its SHA-256 goes in the manifest.
  - Fallbacks, in order, if any pre-seal check fails: `layout5_s0.8/emitter_wall`, then `layout5_s0.8/default`.
- **Item 15:** "The AX47 self-ABX is rerun on the binaural chain at the bound in force, before Phase 08's goldens freeze, on the sealed 07c-2b scene and tailSeed (its omni twin), under Seat 4's L5 condition. It is its own family."
- **Item 13:** D-M3e. The class is E's Class line.
- **Label** (Seat 9's file 7, with s 0.9 values, and Seat 2's and Seat 4's lines added):
  - `label`: "Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall, specular-only early reflections (s 0.9, AX21); not a validated preset"
  - Detail lines:
    - S0 22.1 m away; direct-path difference 28.4 ms.
    - D/R −12.7 / −5.0 dB, heard −9.5 dB, against −18.6 / −13.5 dB at r/r_c 8.46 / 4.74 (Sabine A ≈ 343 m²). Indicative only: ᾱ ≈ 0.145 and one face at α 1; Kuttruff §5.6–5.7 says these relations are questionable when ᾱ is not small, and one fully absorbing face is a severe deviation from diffuse conditions.
    - ITDG 0.6 / 1.6 ms, counted as direct: combs at about 860 / 320 Hz, +2.4 / −3.3 and +2.3 / −3.1 dB.
    - Near-wall emitter; its LF image is under-represented (one broadband s).
    - Early part −8.6 dB re direct; the scattered early energy is absent (AX21; the fix is deferred to the B11 rule).
    - Tail share 0.852 at 1 kHz.
    - Heard-IR T30 2.560 s, labelled "ISO fit spanning the early part, not a decay rate"; tail T30 2.582 / 2.600 s; Eyring 2.61 s.
    - Kuttruff Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s; the engine's tail follows Eyring.
    - Gaps are built from max(heard, tail) T30.
    - Stimulus scene, not a room prediction.
  - Class line: "tail-dominated (heard −9.5 dB, tail share 0.85), partial early part"
- **File 34's clause:** the "[s = 1 scenes]" wording from D-M3f stands. On E the specular share is 0.022 / 0.001, so M1's reversal condition is live.
- **Record:** the union rate ≤ 0.098 with n = 2, and the family that triggers any reversal (D-M3c).

## DECISION M3-G: the gap rule (an M2 re-decision) and the speech chain
- **Construction quantity.** T = max(heard-IR T30, every tail T30) at 1 kHz is used for every gap, pause and item-7 lead.
- **What stays.** Q5's ceiling stays 0.43 × the heard-IR T30. That is T-a, unchanged, so file 40's 2a stands. The heard-T30 label stays.
- **Seat cells:**
  - max rule: Seat 1 0/0; Seat 2 0/0; Seat 3 required for layout 5; Seat 9 its C-a.
  - heard rule: Seat 1 1/0; Seat 2 2/1 on layout 5.
  - On layout 4 the max rule changes nothing (heard ≥ tail, file 4 Table 2).
- **Noise chain** (revised D-M3b with interrogator file 6's corrections):
  - Gaps are ⌈(T·fs + Δ)/P⌉·P.
  - N is the first partition boundary at or after the heard end of burst 2.
  - Burst 3 starts at N + ⌈T·fs/P⌉·P.
  - Each gap grows by less than one partition plus max d.
  - Asserted per noise stimulus:
    1. N ≥ the heard end, per emitter;
    2. heard silence after N ≥ T;
    3. every heard gap ≥ T;
    4. M2, on the heard quantities: ≥ every tail T30;
    5. item 7.
- **Speech chain** (Seat 1's finding: **lengthen the pause, do not restate the rule**):
  - Sentence 2 starts at the input end of sentence 1 + ⌈(0.43·T_heard + T)·fs⌉ + Δ.
  - Onsets are at or after the heard end of sentence 1, and no later than 0.43·T_heard after the end of speech (Q5).
  - Asserted per speech stimulus: heard pause ≥ T; heard silence after the onset ≥ T (and so ≥ every tail T30); Q5's ≥ 20 dB margin.
  - Cost on E: about +1.1 s per speech stimulus. The pre-registered "pause ≥ T30" still holds.
  - This keeps M2's premise true on wet scenes. Restating the rule would have left it true only on S-A (file 6 D-M3b 1).
- **Re-measure before the seal (Seat 2's C4, Seat 7):** E's heard gaps under this construction.

## DECISION M3-C: conditions adopted (point 3 of the brief)
1. **C2′ (Seat 2)** replaces C2 for every sealed or item-15 scene:
   - no **listener** within 0.1 m of a face;
   - emitters at 0.1 m are allowed, with the label line above;
   - the Δ clause is dropped, because D-M3b's assertions cover what it stood for.
2. **D-M3h 2(a)** is extended to every listener within 0.1 m of a face, including y = 0.1 (Seats 2 and 9; Kuttruff Eq. 2.50 per Seat 4). Seat 4's "wall-behind label" line is therefore moot for item 15.
3. **Seat 4's L5**, at 08-3 on E:
   - Label: "isotropic tail, anisotropic room: absorber at xMin, 10 m to the listener's left; tail ILD 0 by construction (AX44)".
   - Print per ear and per octave the energy of [direct + 2.5 ms, t_mix,e) and of [t_mix,e, end), each with its ILD. The tail ILD = 0 is asserted; the early-part ILD is recorded.
   - L4 and L5 are not judged on this scene. It is never cited for lateralisation or envelopment.
   - It is voided if an anisotropic tail lands.
4. **Seat 9's C-b.** D-M3h 1's void list gains "any change to the tail's decay target (e.g. non-Eyring for non-diffuse rooms)".
5. **Seat 9's C-c.** The S-A and S-B\* labels gain "Kuttruff Table 5.2 case 4 (floor α 1, others 0): iteration 1.21 s against Eyring 1.38 s; the engine's tail follows Eyring." Applied now to the S-A label in the run sheet and kit.
6. **Seat 1's gap-cue print**, per stimulus (print only):
   - the 1 kHz level of E − B relative to B over [N, N + 100 ms) and [N, N + 300 ms);
   - the per-band maximum of ΔG.
7. **Seat 3's pre-seal conditions:**
   - revised D-M3b and M3-G green on every stimulus;
   - form (b) green on every stimulus;
   - B and E nulled within −120 dB on every **noise and speech** stimulus;
   - M1's per-band step identity asserted at **≤ 0.05 dB** (Seat 3's value). It lies inside the 0.1 dB window tolerance of file 34 item 1. Measured on E: ≤ 8.8e−4 dB.
8. **Seat 7:**
   - K6 redone on E, with the AX49 L4 time added once it is known;
   - E's session (2.39 h) split at a block boundary into two dated sittings;
   - D-M3c's threshold-edge confirmatory ABX is held **before the 08-4 freeze**. This replaces "before Phase 13", and Seat 7's "rises to 2" trigger is met.
9. **Follow-up, report only (NFR-8; Seats 2, 3 and 9).** On layouts with an absorbing floor, the engine's Eyring tail runs about 14 % long against Kuttruff case 4. It goes in the PR's Follow-ups. /fix-plan gives it a home beside file 40's 8 kHz item. Nothing is tuned.

## DECISION M3-F: /fix-plan on AX47
- Reversal: "capped layout-4 scene" becomes "capped layout-4 or layout-5 scene", plus D-M3i's α sentence.
- One edit, with a §6 row.
- The same /fix-plan also adds:
  - the item-15 entry and L5 to phase-08-3.md;
  - D-M3h 2(d)'s one-golden-round exception to 07c-2b item 8;
  - C-b to the B11 homes.

## DECISION M3-T: the TSP speech material (session brief P7; file 13 item 8)
- Speaker MA, files MA01_01 and MA01_02, at 48 kHz.
- This is the kit's documented example, and it is the only pair on which the speech chain's checks have been measured. It passes the ≥ 20 dB assertion, form (b) and the nulls on all 16 scenes (files 32 and 4).
- Before the seal, the run sheet records:
  - the speaker category from TSP's documentation (item 8 requires an adult; the seal is refused otherwise);
  - our SHA-256 of `48k.zip` and of each excerpt (item 12).
- Any other pair would need the same measurement again, for no gain.
- Seat 1 owns item 8. It is asked to object or accept in the L4 round below; its silence is not taken as acceptance.

## AX49 L4 (session brief P6b): CONVENE, not decided
**Restated.**
- The L4 stimuli need the provisional tail, built by `StagedBuild::assembleProvisional` (K23), from `render_cli`.
- That takes a validation-only `src/cli` flag, like `--abx-step-db`, plus a change to AX49's "render_cli never use the provisional".
- It also needs a scene with T60_max = 8 s and L_p < L (K24).

**Options:**
- **L-a:** a validation-only flag `--provisional-ir`, off by default. A test shows `src/plugin` never reaches it. AX49 is amended to "except under a validation-only flag".
- **L-b:** stimuli built by a JUCE-free test harness in `tests/` that calls `StagedBuild` directly. `render_cli` and AX49's wording are unchanged.
- **L-c:** L4 handed to a later phase, by a named date, before 07d or Phase 10. It is not run with AX47 in this phase.

**Convening table.**

| seat | status | reason |
|---|---|---|
| 1 | convened | The held-chord design, release into L, the scene, and the TSP check (M3-T) |
| 2 | convened | Which scene gives T60_max 8 s with L_p < L; L_f, L_p and L printed |
| 3 | convened | The provisional tail and its AX49 handover; D-C9's owner |
| 4 | not required | Omni, diotic; the same chain as AX47 |
| 5 | convened | A src/cli flag, AX5 determinism, `src/plugin` never reaching it, CI gates |
| 6 | not required | No user control |
| 7 | convened | Hours (L4 is about one block) and the sitting plan |
| 8 | not required | A validation stimulus |
| 9 | convened, narrow | The L4 scene's label (no "hall") |

**Brief** (for every convened seat). Read AX49 and file 13 item 14, run sheet §7, `src/sim/Engine.h` L298 and `src/plugin/core/ScenePipeline.cpp` L656 and L704. Rate L-a, L-b and L-c now/later, with your conditions.
- Seat 2: name the scene and its L_p and L, or ask the builder to measure them.
- Seat 1: accept or object to M3-T.

The AX47 seal does not wait on L4. L4 has its own family (AX49).

## Load-bearing claims
- **M3S-L1** (file 4): E is capped at 6, 7 and 8; peak ≤ −4.8 dBFS; share 0.852; ΔG 0.778 dB at 1 kHz; early part −8.6 dB; Q5 passes; s_w ≤ 5.2e−5 at the worst band.
- **M3S-L2** (arithmetic): √(343/16π) = 2.612 m; 22.11/2.612 = 8.46, giving −18.6 dB; 12.37/2.612 = 4.74, giving −13.5 dB; Δ = (22.11 − 12.37)/343 = 28.4 ms.
- **M3S-L3** (K20, corpus): case 5 is +2.3 %; case 4 is −12 %.
- **M3S-L4** (derived): with sentence 2 at t_end + ⌈(0.43·T_heard + T)·fs⌉ + Δ and the onset ≤ t_end + 0.43·T_heard·fs, the heard silence after the onset is ≥ T·fs + Δ + min d − max d... ≥ T·fs.
- **M3S-L5** (arithmetic): union for n = 2 is 0.098, or 0.0956 if independent.
- **M3S-L6** (map): E has a maximum of 1 and a sum of 13, against D's 14 and B's 15.

## Future-debt register (V6-E)
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 9 | The 0.43 ceiling at 1/1, premise corrected (file 40). On E the ≥ 20 dB assertion binds (realised end 0.973 s, below 1.101 s). The formula over-predicts on wet scenes, so it is not a predictor. Hold and SNR are [Hyp] | Re-check the window | E's Q5 at seal; item 15 | Window recorded, assertion green |
| 9 | Not a measured room; s 0.9 is furthest from the fixtures (0.02–0.6) | Relabel | Phase 05d/BRAS | Label carries it |
| 2, 3, 9 | B11 or decay-target void (D-M3h 1, C-b) | Minutes to a reseal | Any promotion | Rebuilt and passed, or recorded "pre-promotion engine" |
| 2 | LF image of the near-wall emitter under-represented | Label only | Per-band s work | Label line present |
| 4 | Isotropic tail in a one-sided room at 08-3 (L5) | One 08-3 session, about 2.4 h | 08-3 L4, or an anisotropic tail | L5 prints and label in the 08-3 record |
| 3, 7 | An 08-3 detection reopens O10, O4 and O6 | Board round, about 2 h ABX, re-pin, second golden round (/fix-plan) | 08-3 | Re-decided before the 08-4 freeze |
| 5, 6, 7 | False reversal, probability ≤ 0.098 | As above | 07c-2b, 08-3 | Triggering family recorded; confirmatory ABX before 08-4; wall-clock cost measured at O10/O4 |
| 7 | 2.39 h in two sittings | — | Session brief | Per-sitting plan committed |
| 1 | M3-G and M3-C 6 | Kit minutes | Before the seal | Assertions green, prints present |

## Strongest objection
- **Seats 2 and 9 prefer B** (layout5_s0.8/default): both ends of the path are seats, and C2′ passes with no emitter-label debt.
  - E still wins. It is lower by 2 on the sum, entirely in Seat 1's cells: B leaves the far-listener tail-dominated class untested (1/1); E is 0/0.
  - B would win if Seat 1 re-rated E above 0/0, or if C4's re-measure fails on both emitter_wall scenes.
- **Seat 3 notes** that emitter_wall at s < 1 "adds little information over V3". It still rated E 1/1, the same as B.

**Confidence: medium.** The cells of Seats 3, 7 and 9 are conditional, with their conditions adopted.

**Reversal:** E fails C4 or any pre-seal check, giving D, then B; or Seat 1 re-rates E.

## Summary
| id | decision | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| M3-S | layout5_s0.9/emitter_wall; item 15 = the same scene binaural with L5; n = 2, union ≤ 0.098 | proposed | 1 (S2, S3, S4, S5, S6, S7, S9) | 13 | medium | NFR-1, NFR-8 | Eq. 5.44, Table 5.2 | pre-seal fail, giving D then B |
| M3-G | T = max(heard, every tail T30); speech pause lengthened | proposed | 0 | 0 | high | NFR-1 | — | — |
| M3-C | C2′; 2(a) extended to all 0.1 m listeners; L5; C-b; C-c; gap-cue print; M1 ≤ 0.05 dB; sittings; confirmatory ABX before 08-4 | proposed | 1 | — | medium | NFR-1, NFR-8 | Eq. 2.50, Table 5.2 | — |
| M3-F | AX47 /fix-plan (layout 5, α), plus homes in phase-08-3 and item 8 | proposed | 0 | — | high | NFR-1 | — | — |
| M3-T | TSP MA01_01 + MA01_02 | proposed | — | — | medium | NFR-1 | — | Seat 1 objects, or the speaker is not an adult |
| L4 | L-a / L-b / L-c | convening | — | — | — | NFR-1 | — | — |

**Challenges to settled decisions:** M2 (T-a) is changed for gap construction by M3-G, a board re-decision. It is not one of Maisara's recorded decisions.

## Decided for Maisara
- **Scene (M3-S):** the listening test uses one wet test room (one absorbing side wall, the source near a wall), with real early reflections. That is the hardest scene that qualifies, and it is heard before the W pin. The same scene is rerun binaurally at 08-3, labelled as a room whose tail is drawn symmetric.
  - PRD ids: NFR-1 (the most sensitive valid test), NFR-8 L112 (a non-detection is scoped to its class), L101.
  - Other options:
    - V2 and V3: their early parts are empty, which strains NFR-1.
    - B: a less sensitive class, which strains NFR-1.
    - V1: the two weakest scenes.
  - Seat 2 gives up its preferred scene and gets the emitter label line. Seat 7 gets the two-sitting plan.
  - Amends nothing.
- **Gaps (M3-G):** every silence is at least the longer of the measured reverberation times, as heard, in both chains. NFR-1. Amends nothing.
- **Conditions (M3-C):** listeners never sit 0.1 m from a wall; the binaural record names its limits. NFR-1 and NFR-8. Her AX21 deficit is stated in every label. Amends nothing.
- **AX47 wording (M3-F):** NFR-1. Amends nothing.
- **TSP (M3-T):** NFR-1. Amends nothing.

**NEEDS MAISARA:** none. The person's action stands: two sittings of about 1.2 h each for E, plus L4 once it is decided (Raise item 2).

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/4-k7-candidates.md
- /home/user/makroof/docs/review/phase-07c-2b/6-interrogator-on-file5.md
- /home/user/makroof/docs/review/phase-07c-2b/7-seat{1,2,3,4,7,9}.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md (§7)
- /home/user/makroof/src/sim/Engine.h (L298)
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp (L656, L704)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md
