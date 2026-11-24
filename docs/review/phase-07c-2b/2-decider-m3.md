# 2: Decider on M3 (the AX47 self-ABX scene) and the click_check call

To be saved as `docs/review/phase-07c-2b/2-decider-m3.md`.

**Outcome: partly decided, partly RESEARCH NEEDED.** Nine of the questions are decided (D-M3a to D-M3i). The scene questions are held back: which scene or scenes 07c-2b runs, which 08-3 runs, the family count and union rate, the item-9 scene amendment, and whether V3 needs its AX47 wording change. They wait on one builder measurement, K7. No question goes to Maisara.

Why K7 is needed: in file 31 I wrote that no option can reach a worst cell of 1 on a single scene. That claim was measured only at the layout-4 default placement, so I withdraw it below.

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`). Seats 1, 2, 4 and 9 say their checkouts had no corpus, and Seat 3 did not re-open it. I re-read every corpus fact used here.

## PRD digest
- **For whom:** producers and DJs who do not know spatial audio (PRD L17–20).
- **Outcome:** a designed space rendered accurately. Accuracy is a quality gate, checked by measured match plus listening tests (L26, L50).
- **Hard constraints:**
  - NFR-8 (L112): "Any valid scene renders correctly; no environment-specific code paths."
  - NFR-1 (L105): pass thresholds come from the Expert. The stand-in is D-C1/AX47.
  - FR-SIM-6 and NFR-3: no audible artefacts.
  - File 13's pre-registered thresholds, α, trial counts and item 4.
  - M1 and M2 as decided (file 34), and 2a/2b (file 40).
  - Maisara's AX21 decision of 2026-11-05: the empty early part is a known deficit, and its fix waits for B11.
  - AX47's Reversal wording ("capped layout-4 scene") is a board row. A board DECISION through /fix-plan can change it.
- **Priorities:** "Accuracy first; heavy CPU/latency acceptable" (L49), NFR-2 (L106), and "no fixed deadline" (L55).
- **Verification culture (CLAUDE.md):** every DSP behaviour gets an automated check; independent references are preferred; each gate is shown red once (the N1 precedent); goldens are never regenerated to make a test pass.

## Knowledge inventory
| K | what | source | status |
|---|---|---|---|
| K1 | Share, ΔG, ΔC80, caps, peaks, early part and heard T30 for 19 candidates | file 29 table, facts 1–9 | known (builder, from the code) |
| K2 | Both K5 events are detector false positives. On noise, `click_check` passes S-A only because A's and B's peak frames coincide | file 32 L15–35, L99–123 | known |
| K3 | In the fade, r = (A − B) − m equals o − rec, which companion (ii) bounds by 8u(\|a\|+\|b\|) with u = 2⁻²⁴. Outside the fade, (iii) makes r exactly 0 | from the code: abx_kit L385–396, L400–411, L97 | known |
| K4 | Floor of form (b): a single-sample spike is caught at about −68 dBFS and missed at −70 | from the code: test_abx_kit L130–142; clicks.py L43–47. Working in M3-L2 | known |
| K5 | Binomial tails: 2517/65536 = 0.0384, 697/65536 = 0.0106. Powers 0.63 / 0.405 / 0.197 | file 31 answer 4, redone by Seats 1, 5, 6 | known |
| K6 | About 1.94 h per scene at a typical pace. Stimulus length scales with T30 | file 32 K6 (pace is [Hyp]) | under-informed for other scenes; Seat 7's redo is adopted |
| K7 | In both_wall the far emitter's heard burst ends at N + 1407, 29.3 ms into the 30 ms fade | file 32 L44–62 | known |
| K8 | Kuttruff Table 5.2 case 5 (10 × 20 × 30 m, long side wall 10 × 30 m² at α 1, others at 0): Sabine 3.22, Eyring 2.99, iteration 3.06 s | corpus, kuttruff L2782–2793 | known |
| K9 | r_c = (A/16π)^½ (Eq. 5.44). S-A: Sabine A ≈ 640 m² gives r/r_c 3.47 and −10.8 dB. Layout 5 default: A ≈ 343 m² gives r_c 2.61 m, r/r_c 4.74 and −13.5 dB | corpus L2708; arithmetic in M3-L6 | known (the A values are Seats 2 and 9's Sabine plus air) |
| K10 | On layout 5 the heard T30 (2.557–2.575 s) is below the tail T30 (2.58–2.62 s), so `gap_check` fails | file 29 fact 9; test_abx_kit L96–98 | known |
| K11 | **For an s < 1 scene at a wet placement, or in layout 5: cap at m = 6/7/8, tail share, item 6, Q5, gap** | none. K4 measured s < 1 only at layout4/default | **uninformed, load-bearing** |
| K12 | Phase 06 null: real-time emulation against offline, within −120 dB | phase-06.md L64–65 | known |
| K13 | At s = 1, E_target's specular share is 0 | file 29 fact 7 (0.000 on every s = 1 candidate); AX21, (1−α)(1−s) per hit; Kuttruff Eq. 8.59 defines s | known |
| K14 | The 0.43 ceiling's corrected premise gives 0.375 s on S-A | files 40, 41 (survived) | known on S-A. On the other scenes the inputs are Seat 9's [Hyp]. Not load-bearing, because the ≥ 20 dB assertion governs |
| K15 | Each item-15 family can fire AX47's reversal | file 13 item 15 ("at the bound in force"); file 31 answer 4 | known (plan text) |
| K16 | SE ∝ 1/√W; one-sided-absorber ILD; tail JND after a masker | Seat 5/6 [Inf], Seat 4 [Hyp], Seat 1 (open) | lead only. Not load-bearing for any part decided here |

## Tension maps (now/later, in the seats' words; c = read from the seat's conditions)

**Scene options** (α unsplit; family counts as Seats 5 and 6 counted them: V1 has 4, the others 3).

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| V1 | 2/2 | 2/1 | 1/1 | 0/2 | 1/2 | 1/1 | 2/2 | 1/1 | 2 | 22 |
| V2 | 1/0 | 2/1 | 2/2 | 0/1 | 1/1 | 1/1 | 1/1 | 1/2 | 2 | 18 |
| V3 | 2/1 | 2/1 | 2/2 | 0/2 | 1/1 | 1/1 | 1/1 | 1/2 | 2 | 21 |
| V3′ (Seat 2) | 2/1 c | 1/1 | 2/2 c | 0/2 c | 1/1 | 1/1 | 1/1 c | 1/2 c | 2 | 20 |
| V4 | 2/**3** | 1/1 | 2/2 | 0/1 | 1/1 | 1/1 | 0/2 | 1/2 | 3 | — |
| V1′ (Seat 4) | ≥2/**3** c | — | — | 0/1 | 1/2 | 1/1 | — | — | 3 | — |

Seat 8 is not required in any row (file 31: a validation stimulus, and item 13 forbids public copy), so it scores 0/0. Seat 9's 0.43 ceiling is 1/1 on every option and goes in the register.

The seats' reasons, cell by cell:

**V1**
- S1: the 07c-2 gate rests on the two weakest scenes; if S-W detects first at 08-3, that is "a phase of rework".
- S2: S-B\*'s AX21 jump is unmeasured (1/1 under its C1).
- S3: one more scene, minutes of compute.
- S4: the only scene with an early part never reaches binaural.
- S5: a 4th family, landing after O4 and O10.
- S6: unsplit, "Commits: a false-reversal risk".
- S7: 3.9 h before the pin, two sittings.
- S9: a B11 rebuild.

**V2**
- S1: needs C1–C3; a detection tightens correctly.
- S2: both-near is where "the engine is least faithful", and the burst plays through the fade.
- S3: empty early part, and the evidence arrives after O10, O4 and O6.
- S4: S-B\* has no omni twin.
- S5 and S6: as V1, with 3 families.
- S7: about 2 h; S-B\* reversal is the least likely case.
- S9: O10 is read from an empty-early-part scene only.

**V3**
- S1: `gap_check` fails on layout 5.
- S2: emitter_wall puts about 28 ms of burst into the fade.
- S3: as V2.
- S4: "binaural ABX runs on a tail the room contradicts".
- S7: as V2, plus one board cycle.
- S9: the V2 debt plus the M2 premise.

**V3′**
- Seat 2 rated it 1/1 directly.
- The cells for Seats 1, 3, 4, 7 and 9 are read from their V3 reasons, which all still apply to layout5_s1/default: the T-a premise (K10), the empty early part, binaural layout-5 anisotropy at 08-3 (i), and the board cycle.

**V4**
- S1: "No test ever covers late-dominated scenes before Phase 08 freezes".

**V1′**
- S1 (read from conditions): V1′ never runs a wet scene, which is S1's V4 reason for its 3.

**α treatment**

| treatment | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| unsplit, ≤ 3 families | 0/0 c ("unsplit"; its condition is that the primary family stays at 0.049) | 1/1 | 1/1 | 0/1 | 1 | 5 |
| unsplit, 4 families | 0/0 c | 1/2 | 1/1 | 0/1 | 2 | 6 |
| split, 0.0213 per family | 2 ("rated 2"; no column given, so entered as 2/2) | 0/1 | 2/2 | 0/1 | 2 | 8 |

Seats 2, 3, 4 and 9 handed α to Seats 1, 5, 6 and 7, so they score 0/0.

**click_check form**

| form | S1 | S3 | S5 | max |
|---|---|---|---|---|
| (b) A − B against the crossfade model | 0/0 c (C1: "I prefer A − B against the crossfade model", plus the planted click) | 0/0 c ("my pick") | 0/0 c ("Prefer (b)"; its test spec is met) | 0 c |
| (a) per-frame flags against B's threshold | C1 prefers (b) | "stays blind" | 2/1 | 2 |
| unfixed | "a fix is needed" | "needed before the seal" | 2/2 | 2 |

Seats 2, 4, 6, 7 and 9 handed this call to Seats 3 and 5 and score 0/0.

**S-B\* value**
- s = 0.7: preferred by Seats 2, 3 and 9, and named as a condition on every option by Seat 4. Seat 1 "can live with 0.7".
- s = 0.9: Seat 1's pick. It fails Seat 4's condition (b).
- No seat rated either value 2 or 3.

## Working (scene options)
1. **Bounds.** Every option is inside. V3 and V3′ need a board /fix-plan to AX47. Everything is kit-side, so NFR-8's no-code-paths half is untouched.
2. **Veto.** V4 is dropped on Seat 1's later 3. V1′ is dropped on Seat 1's later 3, read from its conditions.
3. **Worst-off seat.** V1, V2, V3 and V3′ all have a maximum of 2.
4. **Compose.** No variant built from measured scenes reaches 1, because three seats' conditions pull against each other:
   - Seat 7 needs one scene (about 2 h) before the pin.
   - Seat 9 needs an s < 1 family read before O10, and O10 comes before the pin ("That alone leaves the rating at 2" for any trigger-only substitute).
   - Seat 1 needs a wet scene before the pin.

   Only a single scene that is both s < 1 and wet meets all three. Under Seat 2's C2 it would also sit at a default placement (layout5_s<1/default), or it could be a wall-behind layout-4 placement for Seats 1 and 4 to weigh.

   K4 measured s < 1 only at layout4/default, where the share is ≤ 0.040. File 31's "Why no option can reach 1 on a single scene" generalised from that one placement. **I withdraw it.**

   Whether such a scene exists, is capped, and is clean is unmeasured (K11). It could win the ordering, as the s = 0.25 / 0.4 inference did in file 28. The protocol does not let me decide on that gap. PRD L49 and L55 ("no fixed deadline") put no time pressure against waiting one builder round of minutes.

## DECISIONS (fully informed; applied once they survive)

**D-M3a. click_check: form (b), needed before any seal.** The kit-side code already matches this (working tree read 2026-11-24, abx_kit L400–438).
- **Pre-registered criterion.** On every stimulus of every chain and sealed scene (per ear at 08-3), there is no `tools.acoustics clicks` event on channel 0 of r = (A − B) − m over [N − 5 ms, N + L + 5 ms).
  - The model m is (j/L)(E − B) on [N, N + L) and E − B after it, with L = 1440.
  - The detector settings are unchanged: 2 kHz zero-phase high-pass, 2 ms frames, 20 dB over the median, absolute floor −90 dBFS.
- **Red tests** (pytest, shown failing):
  - a hard switch at N (L = 0);
  - a single-sample impulse of −65 dBFS inside [N, N + L).
  - The measured floor (about −68 dBFS caught, −70 missed) is printed in the record.
- **Green before the seal:**
  - S-A's 50 stimuli;
  - the two K5 stimuli;
  - every stimulus of each sealed scene.
  - The check is bit-reproducible.
- **Printed only:**
  - event counts of the detector on A, B and E;
  - the old comparison of A's events against B's peak frames.
- **Seat 3's remaining gap** (a transient common to B and E): per sealed scene, B nulls against the offline render within −120 dB (Phase 06's criterion). E is nulled the same way, against the offline render of the stepped IR; the builder names the offline path.
- **Why Seat 3's version of (b) and not Seat 5's ratio form HP(A − B) ≤ HP(E − B)(1 + tol):**
  - In the fade, A − B = (j/L)(E − B) + r. Under the ratio form, a click below (1 − j/L)·HP(E − B) passes, so its floor scales with the programme, which is K5's blind spot.
  - Seat 3's version has an absolute floor.
  - Seat 5's stated conditions (red, green, reproducible, tolerance fixed before the seal) are all met.
- **What the gate is, stated plainly:** the sample-level guarantee is companions (ii) and (iii) (K3). Form (b) makes item 6's click line independent of the programme, and shows it red. If a real stimulus fails form (b), that is an FR-SIM-6 / NFR-8 report and nothing is tuned.

**D-M3b. Onset at the heard gap start (Seat 1 C3; Seat 3).**
- **Noise chain:** N is the first partition boundary at or after the heard end of burst 2. The heard end is the input end + max over emitters of (directS − alignmentShiftS)·fs.
  - The silence from N to the next burst still meets the gap rule (≥ heard T30, and ≥ every tail T30 under M2).
  - The rest of item 7 holds.
- **Speech chain:** onset boundaries must lie at or after the heard end of sentence 1. Q5 itself (≤ 0.43·T30 after the end of speech, the ≥ 20 dB assertion) is unchanged. The realised window is recomputed and recorded.
- **Manifest:** prints N minus the heard end for each emitter, asserted ≥ 0.
- **On S-A:** the onset moves by one partition.

**D-M3c. α: unsplit.**
- Each sealed scene, and each item-15 rerun, is its own family at item 3's thresholds (≥ 12/16 noise, ≥ 13/16 speech, FWER ≤ 0.049), with item 4 applying in each family.
- A 0.9 dB detection in any family, including an 08-3 family, sets AX47's bound to 0.5 dB. This answers Seat 6's question.
- **The record states:**
  - the triggering family;
  - the union rate, ≤ 0.049·n (and 1 − 0.951ⁿ if the families are independent): n = 3 gives 0.147 (0.140); n = 4 gives 0.196 (0.182).
- **At most 3 families**, unless Seat 5's condition is met: the 08-3 families run before O4, or admission is written as SE ≤ B/1.96 with W_max derived from B.
- **Seat 6's conditions:**
  - A reversal that fires in exactly one family, at exactly its threshold, is flagged for a confirmatory ABX before Phase 13. The flag is not a gate.
  - The cost of a false reversal is measured as wall-clock time at O10/O4: the AX38 (iv) load, and stage-1 time at SE 0.25 against 0.5, on three OSes.

**D-M3d. S-B\* = layout4_s0.7/default.**
- Seats 2, 3, 4 and 9 choose 0.7; Seat 1 can live with it.
- On record: share 0.032 / 0.029 (> 0), so M1's identity assertions are live on this scene. s_w is 6.1e−7 broadband and 2.5e−5 in the worst band, against the 2.3 % limit.
- Wherever S-B\* runs, it carries:
  - Seat 2's C1: per band, the energy in [t_mix,e − 12.5, t_mix,e − 2.5) ms against [t_mix,e + 2.5, t_mix,e + 12.5) ms, and the time at which the early envelope falls 60 dB below direct;
  - Seat 3's prints: per-band share, s_w, the AX21 step and `wet_band_change`, plus Q5, the M2 gap assertion and form (b).

**D-M3e. Item 13 wording** (file 31 answer 5):
> "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states."

The "class" is the Class line of the scene's item-9 label (D-M3g).

**D-M3f. File 34 item 1's clause** becomes (Seat 2):
> "[Scenes with s = 1 on every face:] There E_target's specular share is 0 in every band (AX21; file 29 fact 7), so this equals scaling E_b alone (file 5's wording). On an s < 1 scene (S-B\*: share 0.032 / 0.029) it does not, and M1's reversal condition (file 34 item 2) is live there."

**D-M3g. Item-9 labels.**
- Seat 9's five labels and detail lines (1-seat9 §6) are adopted. None contains "hall" or "occupied". Each sealed scene's manifest carries its own label.
- **Two corrections:**
  - **(i) Layout-5 detail.** "(non-diffuse; physical decay expected shorter)" becomes "Kuttruff Table 5.2 case 5 (long side wall α 1, others 0): iteration 3.06 s against Eyring 2.99 s; the engine's tail follows Eyring". The corpus case that matches this geometry runs the other way from Seat 9's analogy with case 4.
  - **(ii) A basis.** Every D/R expectation names its A basis. For S-A: −10.8 dB with Sabine A ≈ 640 m², and −10.1 dB with Eyring A ≈ 747 m².
- S-B\*'s detail line adds Seat 2's tag "partial-AX21".
- Every manifest prints:
  - ITDG;
  - early part re direct;
  - per-emitter D/R against the expectation;
  - heard and tail T30;
  - "stimulus scene, not a room prediction".
- **Now:** the vetoed string is replaced by Seat 9's S-A label in three places: run sheet §1, `abx_kit.py` (docstring and manifest `label`), and the output of `listening_pack.py` L452.

**D-M3h. Conditions adopted, scene-independent.**
1. **B11 trigger** (Seat 2's three changes):
   - Any change that makes AX21's statement false or moves t_mix,e voids the sealed stimuli. That covers a B11 promotion, an early-diffuse method, or an AX22 rule change.
   - Rebuilt stimuli must pass, before sealing: item 6 (with form (b)), the cap check, the peak check, Q5, s_w ≤ 2.3 % and the M2 gap assertion. If s_w exceeds 2.3 %, the kit refuses and the scene returns to the board.
   - Earlier results are kept as "pre-promotion engine".
   - If no listening session follows the promotion before the 08-4 freeze or the beta, the promotion phase schedules item 15.
   - Homes for the rule: phase-05e scope (b), BUILD_PLAN's deferred B11 entry, and the phase-05b row.
2. **Item 15 general rules** (go into phase-08-3.md, which has no item-15 entry today):
   - (a) listeners at x = 0.1 (listener_edge, listener_corner, both_corner) are barred (Seat 4 (a));
   - (b) per ear: peak ≤ −1 dBFS, item 6 with form (b), and M1's identity assertion on S-B\* (Seat 4 (c));
   - (c) file 26's (a)–(d) carry over (Seat 4 (d));
   - (d) an 08-3 detection is a reversal trigger for O10 and O4. The undo cost is named: a class (c) re-decision, a W_max re-pin and a second golden round. The bound is re-decided before the 08-4 freeze (Seat 3);
   - (e) 08-3 runs in two dated sittings (Seat 7).
3. **Before each seal:**
   - M1's reversal condition, with s_w printed and asserted (file 34 item 2);
   - the M2 checks for each sealed scene (file 34 item 3): minimum gap, heard T30 and tail T30 printed; gap ≥ tail T30 asserted; Q5's ≥ 20 dB assertion; Seat 9's label;
   - K6 redone on each chosen scene, with the AX49 L4 time added and a per-sitting plan in the brief (Seat 7);
   - Seats 3 and 5 read the form-(b) outcome.

**D-M3i. A /fix-plan to AX47 is needed now, for α only.**
- Append to "Self-ABX design":
  > "Each sealed 07c-2b scene and each phase-08-3 rerun (file 13 item 15) is its own family at these thresholds, unsplit; a 0.9 dB detection in any family sets the bound to 0.5 dB; the record states the triggering family and the union rate ≤ 0.049 × families (phase-07c-2b decider file 2)."
- Reversal: "the 07c-2 self-ABX" becomes "the 07c-2 self-ABX (run in 07c-2b) or its phase-08-3 rerun".
- A §6 row is added.
- The wording "layout-4 or layout-5" waits for the scene decision.

## RESEARCH NEEDED (builder K7; the scene questions wait on it)
**K7.** Build each of these scenes the way K4 did (tailSeed 12345, s uniform on all six faces):
- layout5_s{0.7, 0.8, 0.9}/default;
- layout5_s0.7/emitter_wall;
- layout4_s0.7/{listener_wall, emitter_wall, both_wall}.

For each one, report:
- K4's columns: cap at m = 6/7/8, peak, per-emitter and heard D/R at 1 kHz, tail share, ΔG, ΔC80, specular share, s_w, item 6 with M1's identities, heard T30, early part;
- tail T30 per emitter;
- `gap_check` under the heard-T30 rule and under max(heard, tail);
- a 10-stimulus noise chain with D-M3b onsets and form (b);
- the Q5 speech chain (≥ 20 dB assertion, realised window);
- stimulus length;
- Seat 2's C1 and Seat 9's prints.

Run the same new checks (form (b), D-M3b, gap, Q5) on S-A, S-B\*(0.7), layout4_s1/both_wall and layout5_s1/default.

**What changes the winner.** Suppose any s < 1 candidate is:
- capped at m = 6, 7 and 8;
- at a peak of −1 dBFS or below;
- clean on item 6, including form (b);
- passing Q5;
- at gap ≥ tail T30;
- at s_w ≤ 2.3 %;
- above S-A's tail share of 0.046 at 1 kHz.

Then a one-scene option exists (V6: that scene alone in 07c-2b; item 15 per D-M3h). It could meet the max-1 conditions of Seats 1, 3, 7 and 9 together, so it is convened. If no candidate qualifies, the map above stands and the next round decides among V1, V2, V3 and V3′.

**Non-blocking, forwarded to the researcher:**
- Seat 1: level discrimination of a decaying tail after a masker.
- Seat 4 (a)–(c).
- Seat 9: ISO 17497-1 scattering data, and the band basis of the 46 dB SNR.
- Seat 5: the SE law, which belongs to the O10/O4 round.
- Seat 2's Table 5.2 question is answered by K8: case 5 is in the table.

**CONVENE after K7.**
- Seats 1, 2, 3, 4, 7 and 9: rate V6 (each qualifying candidate) and re-state V1–V3′ where K7 changes a fact.
- Seats 5 and 6: narrow, only if the family count moves away from 3.
- Seat 8: not required (validation stimulus; item 13).
- **Brief:** read this file, K7 and files 29 and 32. Rate now/later with your conditions. Seat 4 rates layout 5 in item 15. Seat 1 says whether a share of [K7 value] meets "the hardest signal".

## Load-bearing claims
- **M3-L1** (from the code; K3). r = o − rec in the fade, so |r| ≤ 8u(|a|+|b|) with u = 2⁻²⁴, which is −126 dB re |a|+|b|. Outside the fade r is 0, bit for bit.
- **M3-L2** (derived). A spike of amplitude x leaves about 22/24 of its energy above 2 kHz, inside one 96-sample frame. That gives a frame level of x_dB + 10·log10(0.917/96) = x_dB − 20.2 dB. Against the −90 dBFS floor, the catch threshold is x ≥ −69.8 dBFS. This matches the code's "caught at −68, missed at −70".
- **M3-L3** (K5). Splitting cuts noise power from 0.630 to 0.405 at p = 0.75.
- **M3-L4** (file 32). both_wall's far emitter is heard until N + 1407, while L = 1440.
- **M3-L5** (corpus). Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s.
- **M3-L6** (corpus Eq. 5.44). S-A: √(640/16π) = 3.57 m, 12.37/3.57 = 3.47, giving −10.8 dB. With Eyring A, √(747/16π) = 3.86 m, giving 3.21 and −10.1 dB. Layout 5 default: √(343/16π) = 2.61 m, giving 4.74 and −13.5 dB.
- **M3-L7** (file 29). The share at s = 0.7 is 0.032 / 0.029, and s_w is 2.5e−5 or less.
- **M3-L8** (product). Waiting is consistent with PRD L49 and L55.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 9 | The 0.43 ceiling, 1/1. Corrected premise: t ≤ hold + (SNR − 20 − L_drop)/60·T60_tail. On S-A it gives 0.375 s (files 40, 41). It binds on wet scenes: both_wall by 50 ms, listener_corner, layout 5. At s < 1 it is an upper estimate. Hold 0.1 s and SNR 46 dB are [Hyp] | Re-check the window on each sealed scene | Q5 on each sealed scene; item 15 | The ≥ 20 dB assertion passes and the realised window is recorded on each sealed scene |
| 5 | Unsplit, 1 later: a false reversal (≤ 0.049·n) needs SE ≤ 0.255 dB, about 3.9× the work [Hyp] | A person-ABX (about 2 h) plus a reseal | The sessions; O10/O4 | The record states the triggering family and union; O10/O4 take SE ≤ B/1.96 as an input |
| 6 | Unsplit, 1 later: loads stay slow if the reversal is false | A board round plus a confirmatory ABX | 07c-2b, 08-3, beta load times | Wall-clock false-reversal cost measured at O10/O4; threshold-edge flag before Phase 13 |
| 7 | Unsplit, 1 later: "compute and load time, recoverable as a parameter" | A parameter change | as above | as above |
| 2, 9 | The B11 trigger (D-M3h 1) | Minutes to a reseal | Any B11 promotion | Stimuli rebuilt and passed, or results recorded as "pre-promotion engine" |
| 3, 7 | An 08-3 detection reopens O10, O4 and O6 | A class (c) round, a re-pin and a second golden round | 08-3 | Re-decided before the 08-4 freeze |
| 4 | The item-15 per-ear rules; x = 0.1 listeners barred | One 08-3 scene swap | 08-3 L4/L5 | 08-3 records per ear |
| 3 | Form (b)'s gap: a transient common to B and E | One null run per scene | Before each seal | B and E null within −120 dB |
| 1 | D-M3b; gap ≥ tail T30 | Kit minutes | Before each seal | Manifest assertions pass |

## Strongest objection
- **On the scene deferral.** Seat 7 can object that deferring the scene delays Maisara's session, which is 07c-2b's critical path, and that K7 may find nothing. That holds:
  - K7 costs builder minutes and the PRD sets no deadline (L55);
  - deciding at a maximum of 2 while a maximum of 1 is plausible is what the protocol forbids.
  - The deferral would be wrong if K7 had already been run, or if Seat 1 or Seat 9 were on record rejecting any s < 1 wet scene. Neither is.
- **On α.** Seat 5 rates split lower (0/1 against 1/1). Unsplit still wins, because split carries Seat 1's 2 and Seat 6's 2/2.

## Summary
| id | decision | state | worst-off (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-M3a | form (b), criterion and red tests above | proposed | 0 c | 0 | medium | FR-SIM-6, NFR-1 | — (code) | (b) red on a real stimulus, or a B/E null failure |
| D-M3b | onset at the heard gap start | proposed | 0 c | 0 | medium | NFR-1 | — | Q5 window empty on a scene, then the deviation is pre-registered |
| D-M3c | unsplit, ≤ 3 families, union recorded | proposed | S5/S6 1/1 | 5 | medium | NFR-1, NFR-2 | — | > 3 families without Seat 5's condition |
| D-M3d | S-B\* = s 0.7 | proposed | ≤ 1 c | — | medium | NFR-1, NFR-8 | — | K7 or the pre-seal checks fail at 0.7 (then 0.9) |
| D-M3e | item 13 wording | proposed | 0 | 0 | high | NFR-8 | — | — |
| D-M3f | "[s = 1 scenes]" clause | proposed | 0 | 0 | high | NFR-8 | Eq. 8.59 | a share > 0 at s = 1 |
| D-M3g | Seat 9's labels with corrections (i) and (ii) | proposed | S9 1/1 | — | medium | NFR-1, AX21 | Eq. 5.44, Table 5.2 | Seat 9 rejects |
| D-M3h | B11 trigger, item-15 rules, pre-seal checks | proposed | 1 | — | medium | NFR-1 | — | — |
| D-M3i | AX47 α sentence via /fix-plan | proposed | 0 | 0 | high | NFR-1 | — | — |
| scene(s), families, item 9, item 15 scenes, V3 word | — | research needed (K7) | 2 on every survivor | — | — | NFR-1, NFR-8 | — | K7 |

**Challenges to settled decisions:** none.

## Decided for Maisara
- **click_check (D-M3a).** The click check now compares the stepped render against the exact crossfade model. It is shown to fail when a click is planted, and its threshold was fixed before any listening. Rests on FR-SIM-6 and NFR-1 (an unseen click would be a non-level cue). The other options, form (a) and leaving it unfixed, strain both. Seat 5 gives up its ratio form. Amends nothing.
- **Onset (D-M3b).** The step starts only after every source's sound has actually stopped at the listener. NFR-1. Recording the deviation instead would strain it. Amends nothing.
- **α (D-M3c).** Each scene is tested at full strength. A false "detected" costs CPU and load time, which NFR-2 accepts. A missed real step costs accuracy (NFR-1, L49). Splitting strains NFR-1. Seats 5 and 6 carry the 1/1 and get the wall-clock measurement and the confirmatory flag back. Amends nothing.
- **s = 0.7 (D-M3d).** NFR-1, NFR-8 L112: a second, more room-like class. s = 0.9 is nearly the same class as S-A. Seat 1 gives up its preferred 0.9. Amends nothing.
- **Item 13 and the file-34 clause (D-M3e, D-M3f).** NFR-8 L112: evidence is scoped to the class actually tested. Amends nothing.
- **Labels (D-M3g).** NFR-1, and her AX21 decision of 2026-11-05: the deficit is named, not tuned. Amends nothing.
- **Conditions and AX47 (D-M3h, D-M3i).** NFR-1. Amends nothing.
- **Scene deferral.** L49 and L55: accuracy first, no deadline. The alternative, deciding now at a maximum of 2, strains NFR-1.

**NEEDS MAISARA:** none. The listening session, about 2 h per scene with hours redone after K7, is a person's action (Raise item 2).

Files read: the eight seat files in /home/user/makroof/docs/review/phase-07c-2b/; /home/user/makroof/docs/review/phase-07c-2/{13,28,29,31,32,33,34,40,41}-*.md; /home/user/makroof/docs/phases/phase-07c-2b.md; /home/user/makroof/docs/BUILD_PLAN.md (AX21, AX47, AX49); /home/user/makroof/docs/PRD.md; /home/user/makroof/tools/ci/abx_kit.py; /home/user/makroof/tools/ci/test_abx_kit.py; /home/user/makroof/tools/acoustics/clicks.py; /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md.
