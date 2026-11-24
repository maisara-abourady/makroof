# Interrogator round 2 on the decider's rebuttal (`docs/review/phase-07c-2b/5-decider-rebuttal-r2.md`)

All seven revised decisions stand: four survive outright and three survive with corrections. The defects left are a misstated speech-chain silence in D-M3b, an outdated robustness sentence in D-M3c and two wording slips in D-M3g.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**What I re-read:**
- The rebuttal in full.
- The working tree of `tools/ci/abx_kit.py`: L104–109 (the spike constants and `SPIKE_FLOOR_DBFS_AT`), L408–450 (`crossfade_residual` and `click_check` with a `channel` argument, `spike_floor_dbfs`, counts on A, B and E) and the speech programme at L736–815.
- `tools/ci/test_abx_kit.py` L130–161: the new `test_click_check_form_b_spike_bracket`, mid-frame and on a frame boundary.
- The seat files, Kuttruff §5.6–5.7, BUILD_PLAN L144, PRD L49, L101 and L105–106, and builder file 22 L24 and L70.

I did not run the tests. Following the rebuttal-round rules, I rate only new or revised items.

## Rulings

| decision | ruling |
|---|---|
| D-M3a | **SURVIVES** |
| D-M3b (revised) | **SURVIVES WITH CORRECTIONS** |
| D-M3c | **SURVIVES WITH CORRECTIONS** |
| D-M3d | **SURVIVES** |
| D-M3e | **SURVIVES** |
| D-M3g | **SURVIVES WITH CORRECTIONS** |
| D-M3h | **SURVIVES** |
| Q3 (K7 additions, V6 trigger, scope of "map stands") | accepted, faithful to my Q3 |
| K7 renamed to K17 | resolves the double use of "K7" |

### D-M3a: SURVIVES
- **The spike floor is CORRECT.** −90 − 10·log10(0.917/96) = −90 + 20.20 = −69.80 dBFS, where 0.917 ≈ 22/24 is the share of energy above 2 kHz and 96 is the 2 ms frame at 48 kHz. The test asserts it to ±0.1 dB (L150).
- **The bracket follows from the same working.**
  - Mid-frame: −68 dBFS gives a frame level of about −88.2, so it is caught; −72 gives about −92.2, so it is missed.
  - On a frame boundary the zero-phase response puts most of its energy (≈ 0.84 of 0.917) in the first frame. That lowers the frame level by only about 0.2–0.5 dB, so −68 is still caught (about −88.5) and −72 is still missed.
  - The constants match: `SPIKE_CAUGHT_DBFS = -68.0`, `SPIKE_MISSED_DBFS = -72.0`.
- **The code now matches the text:** a `channel` argument, `spike_floor_dbfs` printed, and event counts on A, B and E.
- **The E-null reference is sound.** E is a step at sample 0, and the lead-in silence of at least 8 × 512 = 4096 samples is longer than L = 1440. So E's output equals the programme convolved with the stepped IR, and a direct-convolution reference is valid.
- **PRD:** NFR-1 (L105) alone. FR-SIM-6 is dropped.
- **Software follow-up, not a claim:** the old test's docstring (test_abx_kit L133–134) still says "missed at −70".

### D-M3b: SURVIVES WITH CORRECTIONS
**The noise-chain construction is CORRECT.**
- The heard gap is G − Δ, where G = ⌈(T·fs + Δ)/P⌉·P ≥ T·fs + Δ, so the heard gap is at least T·fs.
- Burst 3 starts at N + ⌈T·fs/P⌉·P. The heard silence after N is therefore ⌈T·fs/P⌉·P + min d, which is at least T·fs.
- The burst 2→3 gap as heard is also at least T.
- N stays a partition boundary.

**The numbers are CORRECT.**
- **S-A:** Δ = 0, G = 189 × 512 = 96768 samples, and N moves by +512. The silence after N is 96768 + 32 = 96800 samples, at least T·fs = 96432.
- **both_wall:** Δ = 1407 − 32 = 1375 and ⌈67135/512⌉ = 132, so G = 67584 samples. The heard gap is 66209 samples (1.379 s), at least 1.370 s. N moves by ⌈1407/512⌉ × 512 = 1536. The silence after N is 129 × 512 + 32 = 66080 samples (1.377 s).

Three corrections:
1. **The assertions do not say which chain they apply to.**
   - In the speech chain, Q5 puts the onset up to 0.43·T into a pause of only T·fs + Δ. So assertion 2, "heard silence after N ≥ T", fails by construction there unless the pause is lengthened.
   - The "Decided for Maisara" line "Every silence the listener hears, before and after the step, is at least one reverberation time" is therefore false for speech.
   - Restate assertions 1–2 as noise-chain only, and state the speech-chain rule: heard pause ≥ T, and silence after the onset ≥ every tail T30 (M2).
   - On S-A the M2 form holds. The realised Q5 window is 0.375 s, so the silence after the onset is at least 2.009 − 0.375 = 1.634 s (plus the TSP file's trailing silence), against a tail T30 of 1.274 s. On wet scenes it is unmeasured, and K7 measures it.
   - Correct the Maisara line to match.
2. **"Gaps only grow, by at most one partition plus Δ" is IMPRECISE.** The burst 2→3 input gap grows by ⌈max d/P⌉·P, which is less than P + max d = P + Δ + min d. Example: with Δ = 490, the gap grows by 1024 samples, against P + Δ = 1002. Restate the bound as "less than one partition plus max d".
3. Nothing else changes. The layout-5 M2 note is consistent with K10.

### D-M3c: SURVIVES WITH CORRECTIONS
- **The α table is CORRECT:** sums 5, 6, 8 and 10; maxima 1, 2, 2 and 2.
- **The new row's cells follow from the seats' words.**
  - Seat 6's split reason applies under D-M3h 2(d), so 2/2 c.
  - Seat 1's "can live with" is entered as 1/1 c.
- **The robustness sentence is now WRONG.** "Even if Seat 1's unsplit cell were 2/2, unsplit wins on sum: 9 against 10." With the new row added, unsplit at 2/2 would sum to 9 and lose to "split only the 08-3 families" at 8.
- **The correct support is Seat 1's own ranking.** Seat 1 prefers unsplit and only "can live with" the 08-3-only split (1/1 c). So its unsplit cell is at most 1/1, and unsplit's maximum stays at 1. The winner is unchanged.
- **Correction:** replace the sentence with that reasoning, and confirm the cell with Seat 1 in the scene round, which already convenes it.
- **The register's undo cost is restated faithfully:** a re-pin, a golden round and a /fix-plan to 07c-2b item 8. Seat 7's rating stands as given and is re-asked, which is the correct procedure.
- **The PRD reading is now correct:** L101 "Accuracy is the top priority… must stay usable" and L49. NFR-2 is withdrawn.

### D-M3d: SURVIVES
The worst-off wording now matches the seats: Seats 2, 3 and 9 prefer 0.7; Seat 4 makes 0.7 a condition; Seat 1 prefers 0.9 and can live with 0.7.

### D-M3e: SURVIVES
Every sealed scene must carry a Class line, and the kit refuses to build a manifest without one.

### D-M3g: SURVIVES WITH CORRECTIONS
**I checked the S-A label line by line against the corpus and the code. These parts are correct:**
- Geometry and tailSeed 12345 (abx_kit L87); the emitters are 12.37 m from the listener.
- D/R +10.7 / +9.7 dB per emitter, +13.1 dB heard (file 29 L24).
- −10.8 dB at r/r_c 3.47, with Sabine A = 600 + 16 + 24 = 640 m² (Kuttruff §5.6 Eq. 5.44, which is stated with Sabine's T).
- ᾱ = 616/2200 = 0.28.
- Early part −76.7 dB re direct (file 29 L33).
- Heard T30 2.009 s; tail T30 1.254 / 1.274 s; Eyring 1.291 s (builder file 22 L24 and L70).
- Removing the Eyring-A figures, and the layout-5 detail line (Kuttruff §5.7 Table 5.2 case 5: 3.06 against 2.99 s, diffusely reflecting walls, others at α 0).

Three corrections:
1. **The quote marks around her decision are IMPRECISE.** "Maisara 2026-11-05: 'the early part should contain scattered energy'" quotes text that every source (BUILD_PLAN L144, phase-04 L37, phase-05b L19) gives as reported speech ("decided … that the early part should contain …"). Drop the quote marks.
2. **The PRD line is IMPRECISE.** "the absence that her AX21 decision … leaves to B11": it is the plan's AX21 row that defers the fix to the B11 promotion rule, not her decision. Restate it so.
3. **The citation is IMPRECISE.** "Kuttruff (§5.6) calls these relations questionable" is accurate (§5.6: questionable when ᾱ is not small compared with 1, because the first reflections dominate). But "far from diffuse with one face at α 1" is §5.7 ("severe deviation from diffuse conditions"). Cite §5.6–5.7.

The 24 m² air term (4mV) is NOT CHECKABLE: the corpus gives the 4mV term (Eq. 5.24) but I found no value of m at 1 kHz. It is not load-bearing, since it moves the result by about 0.16 dB.

The proposed layout-5 Class lines are the decider's own and wait for Seat 9's confirmation, which is correctly flagged.

### D-M3h: SURVIVES
- 2(c) is scoped to 08-3 scenes that were sealed in omni. A scene with no omni twin is recorded as standing alone, which matches Seat 4's V2 reason.
- 2(d) names the /fix-plan to 07c-2b item 8 with a §6 row, and no golden is regenerated before it.
- Item 3's M2 check now runs on the heard quantities.

## Ledger rows
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| D-M3a | claim | spike_floor −69.8 dBFS | CORRECT | −90 − 10·log10(0.917/96); abx_kit L108–109; test L150 | SURVIVES | — |
| D-M3a | claim | bracket: caught −68, missed −72, mid-frame and boundary | CORRECT (derived; not executed by me) | frame levels ≈ −88.2/−88.5 and −92.2; test L145–161 | SURVIVES | — |
| D-M3a | code | channel argument, A/B/E counts, floor printed | consistent | abx_kit L408–450 | SURVIVES | (docstring L133–134 outdated, software only) |
| D-M3a | claim | E reference = programme convolved with the stepped IR | CORRECT (code) | lead-in 4096 > L 1440 | SURVIVES | — |
| D-M3b | claim | heard gap = G − Δ ≥ T; silence after N ≥ T (noise) | CORRECT | construction above | — | — |
| D-M3b | claim | S-A 96768/96800 against 96432; both_wall 67584, 66209 (1.379 s), +1536, 66080 (1.377 s) | CORRECT | arithmetic above | — | — |
| D-M3b | scope | assertions 2–3 and the Maisara line applied to speech | INCONSISTENT | Q5 onset ≤ 0.43·T into a pause of T·fs + Δ (abx_kit L759–769) | SWC | restate per chain |
| D-M3b | claim | gap growth ≤ P + Δ | IMPRECISE | growth ⌈max d/P⌉·P < P + max d | SWC | — |
| D-M3c | claim | α table sums and maxima | CORRECT | 5, 6, 8, 10 | — | — |
| D-M3c | ordering | "9 against 10" robustness | WRONG (omits the new row: 9 > 8) | rebuttal table | SWC | restate via Seat 1's ranking; confirm the cell |
| D-M3c | debt / PRD | undo cost; L101/L49 | faithful / correct | 07c-2b item 8; PRD L101 | SURVIVES | — |
| D-M3d | map | worst-off wording | faithful | Seats 1, 2, 3, 4, 9 | SURVIVES | — |
| D-M3e | text | Class line required | consistent | — | SURVIVES | — |
| D-M3g | claim | S-A label numbers | CORRECT | Kuttruff §5.6 Eq. 5.44; file 29 L24, L33; file 22 L24, L70 | — | — |
| D-M3g | claim | §5.6 attribution of "far from diffuse" | IMPRECISE | Kuttruff §5.7 | SWC | — |
| D-M3g | PRD | quote marks; "her decision leaves to B11" | IMPRECISE | BUILD_PLAN L144 | SWC | — |
| D-M3g | claim | air term 24 m² | NOT CHECKABLE (not load-bearing) | Kuttruff Eq. 5.24 gives 4mV, no value of m | — | — |
| D-M3h | consistency | 2(c) scope, 2(d) /fix-plan | faithful | 26-seat4 L32–35; 07c-2b item 8 | SURVIVES | — |
| Q3 / K7 | spec | four additions, V6 trigger, scope of "map stands" | faithful to the request | — | accepted | — |
