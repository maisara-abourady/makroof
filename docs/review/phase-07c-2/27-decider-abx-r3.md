# 27 — Decider round 3 on the ABX kit (M1, M2, M3)

I've decided all three matters: M1 is option A, M2 is T-a, and M3 keeps the current scene with conditions (S-A′). This changes the pre-registered D-W2 text: items 6, 9, 13 and 15 must be amended through /fix-plan before sealing. Corpus c1b171fe.

# Decider round 3, phase 07c-2: M1, M2, M3. All three proposed; none is NEEDS MAISARA.

## Bounds
- **AX47 Reversal and item 9** require a "capped layout-4 scene".
- **S-B is out.** K3 found s = 0.3 uncapped at m = 6/7/8 and s = 0.6 uncapped at m = 8. I treat Seat 2's s = 0.4 and Seat 9's s = 0.25 as out on the same evidence. That rests on Seat 2's inference that the paths needed fall with s; it is not measured.
- **`concert_hall_box` (Seat 9's variant) is out.** It is not layout 4 and its cap status is unknown.
- **Code fact, confirmed independently by Seats 2 and 3 and by K3:** the tail window holds no specular energy, and item 6's identity holds at any share of E_target.
  - The claim in file 23 Q2 and in file 24's item-5 sentence is **WRONG**, so I withdraw it.
  - Under option B, the step would really be smaller than g whenever the target share is above 0 (Seat 3).

## Tension maps (now / later)

**M1** (Seats 1, 2, 4 and 9 were not asked to rate M1; their cells are 0/0)

| option | Seat 3 |
|---|---|
| A | 0/0 |
| B | 1/2: "step shrinks… stops being uniform" |

- **Decision: A.** Maximum 0.

**M2** (Seats 2, 3 and 4 were not asked to rate M2)

| option | Seat 1 | Seat 9 |
|---|---|---|
| T-a | 0/1 | 1/1 |
| T-b | 1/1 | 1/1 |

- Both have maximum 1. T-a wins on the sum, 3 against 4.
- **Decision: T-a.** Seat 9's condition applies: the manifest labels 2.009 s "heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate", with the tail T30 of 1.25–1.27 s beside it.

**M3** (c = read from that seat's conditions of acceptance)

| option | S1 | S2 | S3 | S4 | S9 | max | sum |
|---|---|---|---|---|---|---|---|
| S-A bare | 2/2 | 1/1 | 2/2 | 0/2 | 2/2 | 2 | 16 |
| S-C | 0/0 (condition met by K3: capped, and 4.8 dB wetter heard) | 2/1 | 2/2 | 0/2 | 2/2 | 2 | 13 |
| S-D (Seat 1's) | 1/0–1 | 2/1 c | 2/2 c | 0/2 c | 2/2 c (no condition lowers an s = 1 scene) | 2 | ≤13 |
| **S-A′** (S-A with every seat's conditions, composed below) | 1/1 c | 0/0 c | 1/1 c | 0/1 c | 1/1 c | **1** | **7** |

- **No 3s.** Seat 9's 3/3 was on the old label only, and the label is replaced.
- **S-B fails Seat 1's condition** even ignoring the cap. On K3's numbers, unscaled early energy (+4.2 dB at s = 0.3, −0.1 dB at s = 0.6) against a tail at −9 to −10 dB re direct gives a smaller tail share than S-A. So both ΔG and ΔC80 fall.
- **Decision: S-A′.** It has the lowest maximum (1) and the lowest sum (7). Confidence medium, because every S-A′ cell is read from conditions.

## Decided wording

**Item 5 sentence (run sheet and PR):**
"Item 5 scales the whole tail target E_target = E_spec + E_diff by 10^(g/10) (E′_diff = k·E_diff + (k−1)·E_spec). The rendered tail window holds no specular energy, so the whole window waveform scales by 10^(g/20) and item 6's identity is exact at any specular share of E_target (test_cli.cpp L350–358 asserts it at share ≈ 0.74). The only unscaled energy in [t_mix,e, L) is the 2.5 ms ISM fade-out, which lies inside the 0.1 dB window tolerance. The kit refuses a down-step when the specular share of E_target exceeds k, i.e. g < 10·log10(share). On layout4_s1/default that share is 0, so this equals scaling E_b alone (file 5's wording)."

**Scene label (item 9, kit `label` string, manifest):**
"layout4_s1/default: 20 × 30 × 10 m, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Direct-dominated: D/R at 1 kHz +10.7 / +9.7 dB per emitter, +13.1 dB heard, against −10 dB in a diffuse field at r/r_c 3.2. Early part empty under AX21: energy between the direct sound and 0.38 s is −29 dB re direct at 1 kHz (filter ringing), and broadband it is numerically empty. Tail target is the Eyring T60, 1.29 s at 1 kHz: a diffuse target, not a room prediction. Kuttruff Table 5.2 case 4 (other faces α 0) gives the iteration 1.21 s against Eyring 1.38 s. Tail measured T30 1.25–1.27 s. Not a validated preset."
- "Hall" and "occupied" are removed everywhere.

**`specular_share` print: fix before sealing.** It is a print-only change, so the stimulus hashes do not move.
- Replace the inferred print with K3's exact split, N = (a·u − s)/(a − 1), as `window_unscaled_share` per band and broadband.
- Print render_cli's `target_specular_share` beside it under its own name.
- Add per band the tail-window share of the heard energy, and ΔG and ΔC80 measured on the IR pair at each g (Seat 1's condition).

**8 kHz follow-up** (NFR-8: reported, nothing tuned; does not block sealing).
- Render synthetic exponential noise with T60 0.74 s through the AX13 band filter.
- Measure the tail's band-7 noise alone, without the neighbouring bands.
- This settles whether the analysis filter or the tail causes the +18 %. It must be done before Phase 08's goldens freeze.
- Seat 3 rates it 0 for the ABX and 1 later.

**Item 15: it gets a condition.** The full text is in amendment 4 below.

## Changes to the pre-registered D-W2 text (file 13), through /fix-plan before sealing
1. **Item 6.** The last bullet becomes: "The per-band wet-output change, the window's unscaled energy share (exact split) and E_target's specular share are printed, each under its own name."
2. **Item 9.** The label is replaced by the text above. Add: "The record names the scene class: direct-dominated, D/R ≥ +10 dB at 1 kHz, early part empty. A non-detection is never generalised beyond that class."
3. **Item 13.** The non-detection wording gains "on layout4_s1/default (direct-dominated, early part empty under AX21; tail share X dB per band)". The record adds "AX47's bound rests on an AX21-extreme stimulus, pending item 15(ii)". Thresholds, α, trial counts and the decision rule (item 4) are unchanged.
4. **Item 15** becomes:
   "Rerun on the binaural chain at the bound in force, before Phase 08's goldens freeze:
   - (i) on layout4_s1/default with tailSeed 12345;
   - (ii) on one second scene, with its own Bonferroni split.
   The second scene is chosen by a rule committed before any 08-3 stimulus is heard. Candidates: S-A at uniform s ∈ {0.7, 0.8, 0.9} (decider's grid), and the layout-4 s = 1 placements whose listener is not 0.1 m from a face. Pick the one with the largest 1 kHz tail share of the heard energy, among candidates that are capped at the pins in force and meet all of these:
   - ΔG and ΔC80 at 0.9 dB ≥ S-A's;
   - E_target specular share ≤ 0.40 in every band;
   - window unscaled share ≤ 2.3 %;
   - AX21 step at t_mix printed;
   - peak ≤ −1 dBFS.
   If none qualifies, (ii) is omitted and the record says so. Per ear, the per-band parity (±1 dB) and item 6 are asserted, and D/R is printed. The wording is 'dry scene, empty early part (AX21), static, uncompensated, generic HRTF', never cited for externalisation; L4/L5 are not judged on it. If B11 is promoted before 08-3, the omni ABX is rerun on the promoted IR, or the cross-chain comparison is marked void."
- The run sheet also takes the new item-5 sentence, the new label, and T-a's manifest label.
- AX47 itself is unchanged.

## Load-bearing claims
- **D4-L1:** S-B is uncapped at s = 0.3 and at s = 0.6, m = 8. Source: K3, from the code.
- **D4-L2:** the tail window has no specular energy. Source: Engine.cpp L536–551, NoiseTail.cpp L278–279, Cli.cpp L742–796, test_cli.cpp L350–358.
- **D4-L3:** S-B's tail share is below S-A's. Derived from K3 rows "early energy" and "tail energy".
- **D4-L4:** Table 5.2 case 4 gives 1.38 s Eyring and 1.21 s iteration, with the other faces at α 0. Source: corpus.

## Future-debt register

| seat | commitment | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | The 1 dB bound stands on a scene where G moves 0.05 dB | Reseal, rerun, one listener session | 08-3 item 15(ii) | (ii) runs, or the bound is re-tested on a wet scene |
| 3 | The bound rests on an AX21-extreme stimulus | One person-session | 08-3 (ii), or a B11 promotion | (ii) runs on an s < 1 scene |
| 4 | The binaural rerun inherits an empty early part; extra listening time | One more 08-3 session | 08-3 L4/L5, B11 | (i) and (ii) both recorded under the scoped wording |
| 9 | Stimulus unrepresentative once B11 fills the early part | Rebuild the stimuli | B11 promotion, 08-3 | Rebuilt on the promoted engine |
| 3 | 8 kHz tail T30 at +18 % | Analysis or tail fix | The 8 kHz follow-up | Before Phase 08's goldens freeze |

## Strongest objection
- Seat 1's 2 later (Seat 1 also rated S-A 2 now): a null result keeps 1 dB for late-dominated scenes.
- The scoped wording and item 15(ii) are its own conditions. Its cell is read from conditions, though: my selection rule for (ii) differs from its S-D (it adds s < 1 candidates and drops the wall placements).
- If Seat 1 holds 2, S-A′ and S-C tie at maximum 2, and S-A′ still wins on the sum.

**Reversal condition:** a capped s < 1 layout-4 scene that passes item 15's filters is found before sealing. The ABX then moves to it.

## Decided for Maisara (PRD check: NFR-1, NFR-8; no hard constraint broken; amends nothing)
- M1 A: serves NFR-1, because the step is exactly g in every band. M1 B: strains NFR-1, because the step shrinks at share > 0.
- M2 T-a: serves NFR-1 and keeps the pre-registered realisations. T-b: neutral on NFR-1, but reseeds every stimulus for no gain.
- M3 S-A′: serves NFR-1 (an honest scope and a wetter follow-up) and NFR-8 (nothing tuned). S-C strains NFR-1: it is still empty and the listener is not at a seat. S-B strains NFR-1 (lower cue) and breaks AX47's "capped". `concert_hall_box` breaks AX47's "layout-4". Seat 1's S-D strains NFR-1, because the scene is still s = 1.
- Seat 1 gave the most. It gets back item 15(ii) and the scoped non-detection wording.

## Summary

| id | decision | state | worst cell | sum | confidence |
|---|---|---|---|---|---|
| M1 | A | proposed | 0 | 1 | high |
| M2 | T-a, with Seat 9's manifest label | proposed | 1 | 3 | medium |
| M3 | S-A′, with amendments 1–4 | proposed | 1 | 7 | medium |

**NEEDS MAISARA:** none.

Files:
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md
- /home/user/makroof/docs/review/phase-07c-2/25-k3-alt-scenes.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat1.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat2.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat3.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat4.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat9.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/tools/ci/abx_kit.py
