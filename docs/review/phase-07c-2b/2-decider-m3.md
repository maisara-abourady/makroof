
# 2: Decider on M3, the ABX scene (phase-07c-2b scope 2, round 1 decision)

**Corpus:** revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d, the same as file 31's.

**Seat-flagged facts checked against the corpus now.** Four corpus facts are load-bearing here, and all four read as the seats cited them:
- Vorländer Table 6.1: the jnd is 1 dB for G and for C80, at 500 to 1000 Hz.
- Kuttruff Eq. 5.44: r_c = (A/16π)^½.
- Kuttruff Eq. 5.45: w_d/w_r = r_c²/r², so the diffuse-field D/R is 20·log10(r_c/r).
- Kuttruff Eq. 8.59: s = 1 − I_spec/(I₀(1−α)), so I_spec = 0 at s = 1.

Three flagged citations are not load-bearing here, so I did not re-check them: Begault Ch. 3 (Seat 4), Kuttruff Eq. 2.50 via AX44 (Seat 4), and Eq. 5.43's reliability at ᾱ ≈ 0.28 (Seat 9; the labels below call the diffuse D/R values indicative, as the S-A precedent does).

## PRD digest
- **For whom:** producers and DJs who don't know spatial audio (PRD L17). Validation stimuli are never public copy (item 13).
- **Outcome:** rendering that matches real IRs and passes listening tests, with thresholds from the Expert (NFR-1, L105).
- **Priorities:** "Accuracy is the top priority" (L101); "Accuracy first" (L49).
- **Hard bounds:**
  - NFR-8 (L112): "Any valid scene renders correctly; no environment-specific code paths". Nothing scene-specific goes in `src/sim/`.
  - FR-3D-5 (L75): a listener and sources may be placed "anywhere in the scene".
  - Out of scope (L133): "Audience or crowd presence; all spaces are empty". This is a second reason to drop "occupied".
  - Her AX21 decision of 2026-11-05: the early part should contain scattered energy. The empty early part at s = 1 is her known deficit.
  - The AQ/AX defaults: AX5, AX18, AX41, AX47 and AX49 are board rows and change only through `/fix-plan`.
  - Item 3's thresholds, item 4 and the pre-registered Q5 rule (decider file 40, 2a) are unchanged unless stated below.
- **Not bounds:** listening hours. There is "no fixed deadline" (L55, L174).
- **Verification culture:** every DSP behaviour has an automated check, a gate is never loosened to pass, and a red is a stop.

## Knowledge inventory

| K | what must be known | source | status |
|---|---|---|---|
| K1 | tail share, ΔG, ΔC80, capping, peak, item 6 and heard T30 per candidate | file 29 table, facts 2–9 (code measurement) | known |
| K2 | both K5 events are detector false positives; the companions pass; A−B has no peak in the fade | file 32 (builder measurement) | known |
| K3 | about 2 h per scene (1.3–2.8 h) | file 32 K6 (pace is [Hyp]) | known as a range |
| K4 | jnd 1 dB for G and C80 | Vorländer Table 6.1 | known |
| K5 | s = 1 means no specular component; diffuse D/R from r_c | Kuttruff Eqs. 8.59, 5.44, 5.45 | known |
| K6 | binomial tails 2517, 697 and 137 out of 65536; 190051/2²⁴ | recomputed: Σ C(16,k), k = 12..16 = 2517; Σ C(24,k), k = 18..24 = 190051 | known |
| K7 | the provisional IR already exists in `src/sim`; `render_cli` has no flag for it | from the code: `Engine.h` L146–160, L293–298 (`assembleProvisional`); `Cli.cpp` flag list | known |
| K8 | both_wall tail T30 per placement | Seat 1 [Inferred] 1.25–1.27 s | under-informed. Not load-bearing for the choice: the M2 gap check asserts it at seal, and the fallback rule takes over if it fails |
| K9 | HF-W's commutator is negligible | Seat 3 [Hyp] | under-informed. It is a pre-seal gate the builder measures, not a premise of the choice |
| K10 | Seats 1 and 7 on Seat 6's 24-trial split | not rated | **uninformed, so α is deferred (CONVENE R2)** |
| K11 | V1-W cells for Seats 1, 2, 4, 5, 7 and 9 | read from each seat's conditions | known as readings; R2 confirms them |

---

## M3-1: the scene option

**Restatement.** M3 picks the scene or scenes the AX47 self-ABX decides on in 07c-2b, and the scenes item 15 reruns binaurally at 08-3. The option names used below:
- **V1 to V4:** file 31's options.
- **V1-W:** Seat 3's variant, which Seats 1 and 7 also point to in their conditions. 07c-2b runs S-W and S-B\*, two families. 08-3 runs (i) S-W binaural and (ii) S-B\* binaural.
- **V1′:** Seat 4's variant. 07c-2b runs S-A and S-B\*. 08-3 runs S-A and S-B\*.
- **V3-default:** Seats 2 and 9. V3 with a default-placement filter, so S-W is layout5_s1/default.
- **Gated S-B\*:** Seat 1's. V2, with S-B\* tested only after an S-W detection.

**Tension map** (now/later; c = read from the seat's conditions, to be confirmed in R2; Seat 8 is not required, 0/0; Seats 5 and 6 are rated under unsplit α with C1, the higher of the two α cells for them):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| **V1-W** | 1/1 c | 1/1 c | 1/1 | 0/1 c | 1/1 c | 1/1 | 1/1 c | 1/1 c | **1** | **15** |
| V2 (seat conditions met) | 0/1 | 1/1 c | 2/2 | 0/1 c | 0/1 c | 1/1 | 1/1 | 1/1 c | 2 | 15 |
| V2 (raw) | 0/1 | 2/1 | 2/2 | 0/2 | 0/1 c | 1/1 | 1/1 | 2/1 | 2 | 18 |
| V3-default | 1/1 c | 1/1 | 2/2 | 0/1 c | 0/1 c | 1/1 | 1/1 | 1/1 | 2 | 16 |
| V3, rule as written (emitter_wall) | 1/1 | 2/1 | 2/2 | 0/1 | 0/1 c | 1/1 | 1/1 | 2/1 | 2 | 18 |
| V1 | 2/2 | 1/1 | 1/1 | 0/2 | 1/1 c | 1/1 | 2/2 | 1/1 | 2 | 20 |
| Gated S-B\* (on V2) | 0/1 | 1/1 c | 2/2 c | 0/1 c | 0/1 c | 1/1 | 1/1 | 1/1 c | 2 | 15 |
| V4 | 2/**3** | 1/1 | 2/2 | 0/1 | 0/1 c | 1/1 | 0/2 | 1/2 | veto | — |
| V1′ | 2/**3** c | 1/1 c | 1/1 c | 0/1 | 1/1 c | 1/1 | 2/2 c | 1/1 c | veto | — |

**Each seat's reason, in its own words** (seat files 1-seat1 to 1-seat9):
- **S1:**
  - V2 is "0 on both_wall … 1 later": S-W's sensitivity is ranked on ΔG and ΔC80 alone, and no listener has confirmed it yet.
  - V1 is 2/2: the "two least sensitive scenes".
  - V4 is 2/3: "No phase ever tests a measured, qualifying scene whose programme-level step is about 14× S-A's". V1′ never tests S-W either, so the same later 3 is read for it.
  - V1-W comes from Seat 1's V1 condition, "S-W runs in 07c-2 as well, ahead of S-A", which gives 1/1.
- **S2:**
  - V2 is 2: the stimulus departs from the room class twice, through the wall reflection zeroed at 0.1 m and through the empty early part.
  - Seat 2's label condition takes V2 to 1. The S-B\* label and dip-print condition carry over to V1-W.
- **S3:**
  - V1-W is rated explicitly, "the same" as V1, 1/1: "the only option with s < 1 evidence before O4".
  - V2, V3 and V4 are "2 each" later: the first s < 1 result would arrive at 08-3, after O4–O6.
- **S4:**
  - Now is 0 on every option: the 07c-2b chain is omni.
  - V2 later is 2: "a head at a wall".
  - Under condition (b), the "chain comparison only" label, it is 1. V1′ is 1.
  - V1-W's 08-3 (ii) is S-B\*, and (i) carries the (b) label, which gives 1.
- **S5:**
  - With two 07c-2b families, P(false reversal at admission) is 0.098, so now is 1. With one family it is 0.
  - Later is 2, falling to 1 under C1.
- **S6:** unsplit is 1/1, because "nothing gets worse; a possible gain is lost".
- **S7:**
  - V1 is 2/2.
  - Its condition reads "V1, to 1: the 07c-2b pair becomes S-W plus S-B\*". I read that as 1/1 (see the strongest objection).
- **S9:**
  - V2 is 2 now: "no seat in any room".
  - The condition "the label states 'no seat represented'" takes it to 1/1. V1 (s = 0.7) is 1/1.

**Minimum-tension working:**
1. **Bounds:** none of the options breaks one.
2. **Veto:**
   - V4 is out on Seat 1's later 3.
   - V1′ is out on the same reason, as a reading.
3. **Worst-off seat:**
   - V1-W is the only survivor whose highest cell is 1.
   - Every other survivor holds a 2. For V2, V3 and the gated variant the 2 is Seat 3's ("the first s < 1 result arrives at 08-3, after O4 to O6"). V1 holds 2s for Seats 1, 4 and 7.
4. **Compose:**
   - V1-W is also exactly the variant that Seat 3's condition composes from V2 (S-B\* moved into 07c-2b).
   - No other composition lowers the maximum below 1.
5. **Sum:** not needed.
6. **Reversibility:** not needed.

**DECISION M3-1: V1-W.**
- **07c-2b runs two families, in this order:**
  - **S-W = `layout4_s1/both_wall`.** It is the S-W rule's pick (largest tail share among the qualifying scenes, 0.667), now that K5 has cleared it.
  - **S-B\* = `layout4_s0.7/default`.** Seats 2, 3 and 9 pick 0.7. Seat 1 accepts 0.7 "if Seats 3 and 9 need an early part at −3.8 dB", and they do.
- **08-3 (item 15) runs (i) the sealed S-W binaural and (ii) the sealed S-B\* binaural.**
- **Seal gates on each scene:**
  - capped at m = 6, 7 and 8 (yes on both, file 29);
  - peak ≤ −1 dBFS (both_wall −15.7 to −12.9 dBFS; s0.7 −7.6 to −6.3 dBFS);
  - item 6 clean, using the new HF-W check (M3-3);
  - s_w printed and asserted ≤ 2.3 % (4.1e−13 and 6.1e−7 broadband);
  - M2: minimum gap, heard T30 and tail T30 printed, with gap ≥ tail T30 asserted;
  - Q5 rerun with the ≥ 20 dB onset assertion.
- **Prints:**
  - On S-B\*: the AX21 step and dip at t_mix,e, per band and per emitter, as energy over [t_mix,e − 20 ms, t_mix,e − 2.5 ms) against [t_mix,e + 2.5 ms, t_mix,e + 20 ms) (Seats 2 and 3).
  - On both_wall: the far emitter's burst overlapping the fade (29.3 of 30 ms) is recorded against item 7 (Seat 1).
- **Kit choice on both_wall:** Q5's onset window is counted from the latest *heard* end of speech, that is, the input end plus the largest emitter direct delay in the aligned IR (Seat 1's condition). On s0.7 the two direct delays are equal, so nothing changes there.
- **S-W fallback:** the S-W rule is rerun over the layout-4 s = 1 pool once HF-W exists, and its result is committed before any listening. The order is by tail share:
  1. listener_corner (0.256)
  2. listener_edge (0.208)
  3. both_corner (0.199)
  4. emitter_wall (0.132)
  5. listener_wall (0.129)

  The first scene that passes every gate is used. Its label follows the both_wall template with its own values, and Seat 9 confirms the filled text before the seal. If no placement with share ≥ 0.129 passes, M3 returns to the board, because V1-W would then collapse into V1.
- **S-B\* fallback:** if s0.7 fails a gate, use `layout4_s0.9/default` (Seat 1's first choice; Seats 2, 3 and 9 can live with it), labelled from the same template.

---

## M3-2: the α treatment. Families are decided now; split or unsplit is deferred to R2

**Decided now (α-independent; this answers Seat 5's C1, "the board declares which families can reverse AX47"):**
- Four families are declared, each at its own pre-registered thresholds, with item 4 applied within each:
  - F1: 07c-2b S-W, omni.
  - F2: 07c-2b S-B\*, omni.
  - F3: 08-3 (i), binaural.
  - F4: 08-3 (ii), binaural.
- A 0.9 dB detection in any of the four sets AX47 to 0.5 dB for all scenes (item 4).
- A 0.5 dB detection is a finding for the class (c) round. At 08-3 that round is already closed, so the finding reopens it at the board.
- A non-detection is scoped by item 13 (M3-4).
- The record states each family's α, the union rate, and which family detected at what count (Seat 6 (i)).

**Map** (unsplit is rated under V1-W's two 07c-2b families):

| α option | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| Unsplit + C1 | prefers; no number given | 1/1 c (2 → 1 under C1) | 1/1 | 0/1 | 1 | 5 + S1 |
| Split 13/13 | prefers unsplit; no number given | 0/1 | 1/2 | 0/1 | 2 | 5 + S1 |
| Seat 6's 24-trial split (noise ≥ 18/24 = 0.0113, plus speech ≥ 13/16 = 0.0106, gives 0.0219 per scene) | **not rated** | 0/1 (split rating) | 1/1 c | **not rated** | ≥ 1 | 3 + S1 + S7 |

**Why it is deferred:** the 13/13 split is out on Seat 6's later 2. The 24-trial split could tie unsplit at maximum 1 and win on the sum if Seats 1 and 7 rate it low, and neither has rated it. Deciding without those cells would be deciding on a gap (K10). This blocks nothing yet: the seal waits on α, but the builder work below does not.

**Union rate, as it would stand:**
- Unsplit: ≤ 0.098 at the 07c-2b admission point (F1, F2), and ≤ 0.196 over F1–F4.
- 24-trial split: ≤ 0.0438 at 07c-2b; F3 and F4 to be set in R2.

**If unsplit stands, these conditions attach to it:**
- Seat 5's C1, first branch: if O10 admits a statistical stage-1 source, it carries SE_target as one named constant citing AX47, and 07c-2b prints the AX38 4c restore record with the 0.25 dB branch at the gated builds.
- Seat 6's (ii): the AX38 (iv) records print the keyless time-to-audible under the bound in force.
- Seat 6's (iii): "settling" shows through any keyless load.
- Seat 6's (iv): already item 4.

## M3-3: the `click_check` replacement

| option | S3 | S5 | max |
|---|---|---|---|
| keep as is (peak-frame) | 2/2 | 1/2 | 2 |
| Seat 5's (a), per-frame flags against B's threshold | 1/2 (rated as builder option (1); Seat 5's "or E" not rated by Seat 3) | 1/0 | 2 |
| A−B, literal | 2/2 | 1/1 (as (b)) | 2 |
| **HF-W + N1–N3**, with Seat 5's asserted-form rules | its own proposal (≤ its best) | 1/1 c (meets every "any asserted form" condition) | **1** |

**DECISION M3-3: HF-W is asserted.** It is a kit change in `tools/ci/abx_kit.py` plus pytest in `tools/ci`. Nothing changes in `src/`.
- **What it computes:**
  - h is `clicks.highpass` (2 kHz, order 8, zero-phase).
  - Frames are n_f = round(2 ms·fs) long, aligned to N, over [N − 5 ms, N + L + 5 ms), on every output channel.
  - Per frame: E_o, E_a (unstepped B) and E_b (the stepped IR rendered alone).
  - A frame where max(E_a, E_b) < n_f·10⁻⁹ is skipped and counted.
- **What it asserts:**
  - E_o ≤ β·max(E_a, E_b), with β = (1 + n_f/L)²(1 + 10⁻⁵).
  - At 48 kHz, β = 1.1378, which is 0.561 dB.
  - The worst ratio and the margin are printed per stimulus.
  - The detector's events, and Seat 5's (a) subset result, are printed as a record only.
- **Rules:**
  - It is a pure function of the sealed WAVs, with each SHA-256 checked against `manifest.json`, float64, no RNG and no clock.
  - It runs on the platform that built the kit.
  - A red is a stop: never a rerun, and β is never fitted.
- **Negative controls (`pytest tools/ci`):**
  - **N1:** a single-sample spike at N + L/2, sized 3 dB over β·max. HF-W must fail.
  - **N2:** a hard switch at N + L/2. Companion (ii) must fail.
  - **N3:** the fade quantised in 32-sample steps. Companion (ii) must fail.
  - The unmodified stimulus must pass (Seat 5's non-vacuity pair).
- **Before any seal:**
  - The builder confirms Seat 3's commutator [Hyp] by running HF-W green on the 50 S-A stimuli, the two K5 stimuli and every stimulus of the chosen scenes.
  - If a clean stimulus fails, it is reported and the check returns to Seats 3 and 5. It is not loosened.
- **Assertion of record for the fade path:** companions (i) to (iii).

## M3-4: amendments held for M3

**Item 9.** It is replaced by the two labels below, in the run sheet §1, in `abx_kit.py` (the docstring and the manifest `label`), and therefore in `listening_pack.py` L452. Each label is built from Seat 9's draft plus Seat 2's phrase. Neither contains "hall" or "occupied".

- **S-W:** "layout4_s1/both_wall: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall; those wall reflections are absent at s = 1 (AX21), so the direct sound's tone colour is not room-like and the scene represents no seat. D/R at 1 kHz −7.7 / +5.2 dB per emitter (diffuse field −18.5 / −15.0 dB at r/r_c 8.4 / 5.6; Kuttruff Eq. 5.44, A ≈ 640 m²), −5.3 dB heard. Early part empty (AX21). Heard-IR T30 1.370 s. Not a validated preset."
- **S-B\*:** "layout4_s0.7/default: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 0.7 on every face. D/R at 1 kHz +1.5 / +1.3 dB per emitter, +1.7 dB heard, against −10.8 dB in a diffuse field at r/r_c 3.47 (Kuttruff Eq. 5.44, A ≈ 640 m²). Early part present but specular-only (partial AX21): first image (ceiling) about 23.6 ms after the direct sound; broadband early energy −3.8 dB re direct; the step at t_mix,e is printed. Tail target Eyring 1.29 s at 1 kHz, a diffuse target, not a room prediction; heard-IR T30 1.831 s spans early part and tail. Not a validated preset."
- **Both manifests** keep T-a's label on the heard T30 (file 34), with the tail T30 beside it.

**Item 13.** Add this sentence: "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states." Each record line also names the scene and its tail share. For example: "not detected in 16 trials by one listener (power 0.63 / 0.41 at p = 0.75) on layout4_s1/both_wall (tail share 0.667 at 1 kHz; listener and emitter 0.1 m from a face)". The family α and the union rate are filled in from R2.

**Item 15 (08-3), replacing file 13's item 15:**

"15. 08-3. Before Phase 08's goldens freeze, the AX47 self-ABX is rerun on the binaural chain at the bound in force, as two pre-registered families (F3, F4), each at its pre-registered thresholds with item 4 applied within it; the record states the union rate.
- (i) The S-W scene sealed in 07c-2b, with tailSeed, programmes, steps and trials identical to 07c-2b's. Where its listener is < 0.70 m from a face (AX44 d_L), it is labelled 'chain comparison only; listener 0.1 m from a face, outside the free-field HRTF's validity'. A non-detection there is never counted as binaural evidence for the class; a detection reverses AX47 per item 4.
- (ii) The S-B\* scene sealed in 07c-2b, likewise identical.

Before any stimulus, per scene:
- binaural vs omni per-band energy within ±1 dB (AC6);
- item 6 (HF-W included) and `[ax47-midfade]` per ear;
- the M2 gap and Q5 checks per ear;
- D/R printed per ear;
- `hrtfId` and the set identity string recorded;
- the same wired headphone model and level as 07c-2b, and no virtualiser.

Two sittings of ≤ 2 h each, on the same or consecutive days, with dates in the 08-3 brief before 08-3 starts. Results are worded 'static, uncompensated (B14), generic HRTF', and for (i) also 'empty early part (AX21)'. If the trigger (M3-8) fired after 07c-2b, the stimuli are rebuilt, and the cross-chain comparison is recorded void unless the omni family is rerun on the current engine."

Home: a `/fix-plan` adds this to `docs/phases/phase-08-3.md` (scope and manual checklist), which has no rerun item yet.

**File 34 item 1's "[S-A only …]" clause** is replaced, as Seat 2 proposed, by the physical condition plus the s0.7 extension. Nothing is dropped. The new text:

"[every ABX scene with s = 1 on all faces (layout4_s1/both_wall or its sealed fallback): E_spec = 0 in every band (AX21; Kuttruff Eq. 8.59), so this equals scaling E_b alone.] [layout4_s0.7/default: the target specular share is up to 0.032 (max over bands and emitters, file 29), so scaling E_b alone would give 0.87 dB, not 0.9 (10·log10(0.032 + 1.2303 × 0.968) = 0.874 dB). Item 6's identity is asserted there, and M1's reversal condition is live on this scene.]"

Seat 2 wrote "0.873 dB". The arithmetic gives 0.874 dB; the rounded 0.87 is unaffected.

## M3-5: is V3's /fix-plan needed?

**No.** V3 is not chosen, and both scenes are capped layout-4 scenes.

A separate `/fix-plan` to AX47's Reversal is needed for the families in M3-2. It replaces "If the 07c-2 self-ABX (16 trials, capped layout-4 scene, …)" with: "If the 07c-2b self-ABX (two capped layout-4 scenes, each its own family) or its 08-3 binaural rerun (two families, item 15) detects …". It also carries the thresholds R2 settles, and a §6 row. It is applied after R2, in one edit.

## M3-6: speech material

**DECISION.** Speaker MA, files MA01_01 and MA01_02. This is the kit's documented smoke pair (`abx_kit.py` L12), fixed before anyone listened.
- **Fallback order:**
  1. MA01_03 and MA01_04.
  2. The first two files of the next adult speaker in the archive's alphabetical directory order, excluding CA and CB.
- **Selection rule:** use the first pair in that order that passes Q5 on **every** sealed scene, and use that same pair in all four families.
- **Constraints:** never chosen by ear. The record names the speaker.
- **Not relied on:** Seat 1's "first adult speaker" premise. The rule stands without it.

## M3-7: AX49 L4

**Decided now:**
- **What item 14 and AX49 already fix:**
  - provisional against exact, T60 8 s, fully wet, 16 trials, ≥ 12/16, its own family;
  - the 3 dB anchor, pass at ≥ 5/6;
  - the chord released into ≥ L of free decay;
  - the same omni diotic chain, the same fixed recorded level setting, and the same tool.
- **Sitting order, pre-registered:**
  1. S-W (noise 0.9 first, while the listener is fresh, then speech).
  2. S-B\*.
  3. L4, alone, after a rest, never interleaved.
- **Sitting length:**
  - Each sitting aims at ≤ 2 h (K6).
  - A sitting may split only at a chain boundary.
  - L4 runs on the same day as sitting 2, or the next day.
  - The dates go in the session brief before the seal.
- **Before the first scored AX47 trial:** L4's stimuli are built and sealed, and their `prereg_hashes` are committed in the same pre-registration commit (Seat 1).
- **Render path:**
  - A validation-only `render_cli` flag writes the AX49 provisional IR through the existing `Engine::assembleProvisional` (from the code).
  - It is off by default, with item 5's guards: a test that `src/plugin` never reaches it, and default renders bit-identical without it.
  - There is no `src/sim` change. If the builder finds that one is needed, it stops and returns to Seats 3 and 5.
  - Routing: a `/fix-plan` to AX49's sentence "`render_cli` never use the provisional", adding this validation-only exception. Shipped and offline behaviour are unchanged (AX5, condition 6). The edit touches no part of the row that cites her by date.

**Not decided:** the chord material, the scene (which geometry gives T60 8 s with L_p < L), the level, the seeds, and how A and B are built. These go to **CONVENE M3-L4**.

## M3-8: trigger wording

**DECISION.** Seat 2's widened trigger, plus Seat 4's clause. It goes into the run sheet and item 15:

"On any `src/sim` change that alters a sealed scene's rendered IR (B11 promotion, the t_mix,e rule, estimator constants), the stimuli are rebuilt, pass every seal gate again, and their hashes are re-registered before the next listening session. Earlier results stand, each recorded with the engine it was obtained on."

O4's W_max raise is expected to fire this trigger before 08-3, because both scenes are capped at the candidate pins. That debt is recorded below.

---

## Load-bearing claims
- **D-L1 (code measurement, file 29):** both_wall has tail share 0.667, ΔG 0.621 dB at 1 kHz, is capped at 6/7/8, peaks at −15.7 to −12.9 dBFS, and has heard T30 1.370 s. s0.7 has share 0.032, is capped at 6/7/8, peaks at −7.6 to −6.3 dBFS, has early part −3.8 dB re direct, |ΔC80| 0.519, and heard T30 1.831 s. S-A has ΔG 0.045 dB.
- **D-L2 (file 32):** both K5 events are false positives in unstepped direct-burst frames. Companions (i) to (iii) pass. Nothing is reported under NFR-8.
- **D-L3 (Vorländer Table 6.1):** the jnd is 1 dB for G and C80 at 500 to 1000 Hz. The step moves the programme level about 14× more on both_wall than on S-A (0.62 against 0.045 dB; Seat 1's arithmetic, re-checked: 10·log10(1 + 0.667·0.2303) = 0.620).
- **D-L4 (Kuttruff Eq. 8.59):** I_spec = I₀(1−α)(1−s), which is zero at s = 1. This is the basis of the new clause.
- **D-L5 (Kuttruff Eqs. 5.44, 5.45):** r_c = (640/16π)^½ = 3.57 m. Distances to the listener and the resulting diffuse D/R:
  - 12.37 m: r/r_c 3.47, −10.8 dB;
  - 29.95 m: r/r_c 8.39, −18.5 dB;
  - 20.13 m: r/r_c 5.64, −15.0 dB.
- **D-L6 (derived):** the first image on s0.7 is the ceiling image, 20.46 m against 12.37 m, which is 59.7 ms from emission (file 29 fact 2) and about 23.6 ms after the direct sound. The floor is α 1, and every wall image is longer (20.8 m or more).
- **D-L7 (derived):** P(≥ 12 of 16) = 2517/65536 and P(≥ 13 of 16) = 697/65536, so one family is ≤ 0.049, two are ≤ 0.098 and four are ≤ 0.196. P(≥ 18 of 24) = 190051/16777216 = 0.0113.
- **D-L8 (derived):** HF-W's β = (1 + 96/1440)²(1 + 10⁻⁵) = 1.1378, which is 0.561 dB.
- **D-L9 (Seat 9's corrected bound, re-computed):**
  - both_wall: L_drop 1.12 dB gives 0.1 + 24.88/60·1.30 = 0.639 s, against 0.43·1.370 = 0.589 s. The ceiling binds.
  - s0.7: L_drop 3.94 dB gives 0.578 s, against 0.787 s. It does not bind.
- **D-L10 (from the code):** `assembleProvisional` exists in `Engine.h` L293–298. `Cli.cpp` has no provisional flag.
- **D-L11 (product):** NFR-1 L105, NFR-8 L112, L101, L49, FR-3D-5 L75, out of scope L133, L55.

## Future-debt register (V1-W)

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | S-W ranked most sensitive on ΔG and ΔC80 only | reseal hours if 08-3 (i) changes scene | the 07c-2b sittings; 08-3 | results recorded per family |
| 2 | 08-3 (i) is binaural at a near-face position with its wall reflection missing | rerun one scene, about 2 h | 08-3 | (i) labelled and scoped |
| 3 | 08-3's S-W is empty-early; the s < 1 omni result exists before O4 | none extra | 08-3 | F2 recorded before O4 |
| 4 | B14, a static generic head, (i) as chain comparison only; the trigger voids the cross-chain comparison (O4 is expected to fire it) | one session, or the omni rerun | 08-3 | per-ear prints, label, omni rerun or void recorded |
| 5 | four families can reverse AX47; a late flip after admission | a constant change under C1 | 08-3 | C1's record exists at O10, or no source is admitted |
| 6 | a false reversal costs keyless load time | `/fix-plan` plus new ABX evidence | the AX38 (iv) records under the bound in force | the records print it |
| 7 | about 4 h in 07c-2b plus L4; about 4 h at 08-3 in two sittings of ≤ 2 h | listening hours | each sitting | dates in the briefs |
| 9 | **the 0.43 ceiling, rated 1/1 on every option, premise corrected** (t ≤ hold + (SNR − 20 − L_drop)/60·T60_tail; 46 dB SNR [Hyp]) | re-check the window | at each seal, at 08-3 | Q5 passes; the window is printed per scene |
| 9 | both_wall "represents no seat"; both 08-3 scenes go stale when the trigger fires | rebuild | 08-3 | the trigger is applied |

On the ceiling row: it binds on both_wall (0.639 s against 0.589 s), where the pre-registered 0.43 rule is the tighter limit and is not amended. It does not bind on s0.7.

## Strongest objection
**Seat 7's now cell.**
- **The reading:** V1-W puts about 4 h (2.6 to 5.6 h) plus L4 on 07c-2b's critical path, against about 2.3 h under V2. Seat 7's condition "V1, to 1" names no column, so I read it as 1/1.
- **If R2 gives 2 now:** V1-W has maximum 2 and sum 16 against V2's 15, and V2 would win on sum.
- **Why the decision would still be V1-W:** the acceptance check below then points to V1-W, because the PRD ranks accuracy first (L101, L49), puts no deadline on hours (L55), and NFR-8 L112 is served by two classes before the pin. I would rule that as a `FOR MAISARA` answer naming both options.

**Seats 2, 4 and 9 on "no seat":** this objection holds because FR-3D-5 makes a 0.1 m placement a valid scene, S-B\* supplies the seat-like class, and item 13 scopes any null.

**Confidence:** medium. Six seats' V1-W cells are read from conditions, and α is deferred.

**Reversal conditions:**
- R2 lifts a V1-W cell to 2 or 3.
- No S-W placement passes the gates.
- HF-W fails on clean stimuli, which sends it back to Seats 3 and 5.
- s0.7 fails Q5 for every pair, which moves S-B\* to s0.9.

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-1 | V1-W: both_wall (fallback by share) plus s0.7 (fallback s0.9) in 07c-2b; both binaural at 08-3 | proposed | all 1 | 15 | medium | NFR-1, NFR-8 L112, FR-3D-5 | Vorländer T6.1; Kuttruff 5.44, 8.59 | R2 cell ≥ 2; gates fail |
| M3-2 | F1–F4 declared; split or unsplit | families proposed; α **deferred (R2)** | — | — | — | NFR-1 | — | R2 ratings |
| M3-3 | HF-W asserted, N1–N3 | proposed | S5 1/1 c | ≤ 2 | medium | NFR-1, FR-SIM-6 | — (code) | a clean stimulus fails HF-W |
| M3-4 | item 9 labels, item 13, item 15, clause text above | proposed | — | — | medium | NFR-1, NFR-8, L133 | Kuttruff 5.44, 8.59 | Seat 9 rejects a filled label |
| M3-5 | no V3 `/fix-plan`; AX47 Reversal `/fix-plan` after R2 | proposed | — | — | high | — | — | — |
| M3-6 | MA01_01 and MA01_02; fallback order | proposed | — | — | high | NFR-1 | — | Q5 fails for every pair |
| M3-7 | order, pre-seal L4, `render_cli` flag plus AX49 `/fix-plan`; design → M3-L4 | partly proposed; rest convening | — | — | medium | NFR-1, AX5 | — | the flag needs a `src/sim` change |
| M3-8 | widened trigger | proposed | — | — | high | NFR-1 | — | — |

**Challenges to settled decisions:** none.

## Decided for Maisara
Acceptance check for M3-1: no hard constraint is broken, nothing amends one of her recorded decisions, and AX21 is applied, not changed. The PRD ids that bear are NFR-1 (L105, with L101 and L49), NFR-8 L112, FR-3D-5 L75 and L133.

**How each option serves or strains those ids:**
- **V1-W:** serves NFR-1, because the most sensitive qualifying scene is heard before the W_max pin. Serves NFR-8 L112, with two scene classes before the pin and nothing tuned. Uses a placement FR-3D-5 allows. Costs hours, which no PRD id bounds (L55).
- **V2:** serves NFR-1's sensitivity. Strains NFR-8 L112: a single empty-early class before the pin, with s < 1 evidence only after it.
- **V3-default:** a less sensitive scene, one class before the pin, and an AX47 change.
- **V1:** strains NFR-1. The two least sensitive scenes come before the pin, and S-W comes after the golden round.
- **V4 and V1′:** strain NFR-1 most, and are vetoed (Seat 1, 3 later).

**Plain-language lines:**
- **M3-1:** the self-ABX runs on two test rooms: a far, wet placement and a room with early reflections. Both come back binaurally at 08-3 (NFR-1, NFR-8 L112). Seat 7 gives the most, about 4 h of listening before the pin, and gets back the most sensitive test heard before the golden round. Amends nothing.
- **M3-3:** the click gate becomes a derived energy bound with built-in failing tests (NFR-1, FR-SIM-6). Amends nothing.
- **M3-4:** labels say what each room is, with no "hall" and no "occupied" (L133: spaces are empty), and a null counts only for its room class (NFR-1, NFR-8). Amends nothing.
- **M3-6 to M3-8:** the speech pair is fixed by rule. L4 is fixed and sealed before the first scored trial. Rebuilds follow engine changes (NFR-1, AX5). Amends nothing.
- **Person's action, not a question:** about 4 h in 07c-2b plus L4 (about 15–30 min, [Hyp]), then about 4 h at 08-3. Raise item 2 and scope 3's "about 2 h per scene" text get updated (`/fix-plan`).

**NEEDS MAISARA:** none.

---

## CONVENE

**R2 (a second round on M3; the convening table and reasons are those of file 31).**
- **Seats 1, 5, 6 and 7:** rate, now and later, Seat 6's 24-trial split against unsplit + C1 under V1-W.
  - The 24-trial split, applied to F1 and F2: noise blocks of 24 scored trials plus 6 anchors, with a break after trial 15, ≥ 18/24 (0.0113, power ≈ 0.607); speech ≥ 13/16; 0.0219 per scene, ≤ 0.0438 at 07c-2b.
  - Unsplit + C1: as in M3-2 above.
  - Say what you want for F3 and F4.
  - Seat 7: hours. Seat 1: power, and a trial-count change after K6.
- **Seats 1, 2, 4, 5, 7 and 9:** confirm or re-rate your V1-W cell as read from your conditions in the M3-1 table. Seat 7: the now column in particular.
- **Seats 1, 4, 5 and 6:** confirm the declaration that F1–F4 can each reverse AX47, including Seat 4's "(i) chain comparison only".
- **Files:** this decision; `1-seat*.md`; file 31 answer 4; the AX47 row (BUILD_PLAN L170).

**M3-L4 (new matter: the L4 stimulus design).** Options to rate:
- **L4-A:** the held chord through the provisional IR, faded over [L_f, L_p), against the exact IR.
- **L4-B:** provisional, then an AQ4 handover to exact at a seeded time ≤ L_f, against exact.

What still has to be fixed: the chord material, the scene at T60 8 s with L_p < L, the level, and the seeds.

| seat | status | reason / brief |
|---|---|---|
| 1 | convened | Detection design, the chord, the level and L4-A vs L4-B. Rate both options; give the chord spec and the pass rule. |
| 2 | convened | The scene: which geometry yields T60 8 s with L_p < L (AX49's gated geometry, L_p ≈ 3.7 s). Rate both options. |
| 3 | convened | Provisional synthesis, the fade at L_f, handover artefacts. Rate both options; give the checks per stimulus. |
| 4 | not required | Omni and diotic, the same chain as item 14. No delivery quantity. |
| 5 | convened | The validation-only `render_cli` flag, the `src/plugin` isolation test, CI. Rate both options and the flag. |
| 6 | not required | No control, name or default. L4's load consequence is AX49's Reversal, which is already set. |
| 7 | convened, narrow | Hours, and the pre-seal build on the critical path. |
| 8 | convened, narrow | The chord material as producers voice it (register, timbre). Rate both options. |
| 9 | convened, narrow | The scene's label (no "hall") and its provenance. |

Files for M3-L4: BUILD_PLAN L172 (AX49); file 13 item 14; run sheet §7; `src/sim/Engine.h` L146–160 and L293–307; `src/cli/Cli.cpp` (the abx flag precedent); this decision.

**Researcher (none of these blocks a decision):**
- RQ-M3-1: BS.1116-3 guidance on maximum session or sitting length. It bears on the sitting rule.
- RQ-M3-2: HRTF data near a boundary, head 0–5 cm from a wall. It bears on the 08-3 (i) label.
- RQ-M3-3: measured scattering coefficients for hall surfaces. It bears on Seat 9's label.
- RQ-M3-4: the band basis of the 46 dB SNR. It bears on the debt row.

**Builder (can start now, before R2):**
- HF-W with N1–N3 in the kit.
- Scene selection and the item-9 labels in the kit.
- Q5 counted from the heard end of speech.
- The S-B\* dip and step print.
- The M2 and Q5 runs on both_wall and s0.7.
- The S-W rule rerun over the pool, committed.
- HF-W green on the 50 S-A and two K5 stimuli.

**Plan edits through `/fix-plan` after the interrogator:**
- the run sheet §1 and the M2 lines;
- the item-15 home in `phase-08-3.md`;
- AX47's Reversal (after R2);
- AX49's `render_cli` exception;
- the phase-07c-2b Raise item 2 and scope 3 hours.

Files cited:
- /home/user/makroof/docs/review/phase-07c-2b/1-seat1.md … 1-seat9.md
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/review/phase-07c-2/31-decider-abx-r4.md
- /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md
- /home/user/makroof/docs/review/phase-07c-2/34-decider-m1-m2-final.md
- /home/user/makroof/docs/review/phase-07c-2/40-decider-2a-2b-final.md
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/src/sim/Engine.h
- /home/user/makroof/src/cli/Cli.cpp
- /home/user/makroof/docs/BUILD_PLAN.md (L170, L172)
- /home/user/makroof/docs/PRD.md
