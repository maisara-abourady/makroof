## Decider report 16: the seven open choices in phase-05d (plus the SD-4 wording fix)

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

**What I read:** PRD, CLAUDE.md, BUILD_PLAN (§1 row, §2 AQ9/AX4/AX11/AX17/AX19/AX21, §3 F2, §4 05/05b/05d), phase-05, phase-05d, phase-13 (beta wording), decider report 15, and researcher reports 13, 14 and 17.

**Where the facts come from:**
- **Dataset facts** come from those researcher reports. They are external, not corpus evidence.
- **Code facts:**
  - `src/sim/AirAbsorption.h/.cpp` takes temperature and RH as parameters (ISO 9613-1 form, outside the corpus).
  - The tail decay is Eyring + air (AQ2). So for a matched pair, the simulated T30 difference is about 0 by construction.

### PRD digest
- **For whom:** producers and DJs who do not know spatial audio.
- **Outcome:** the user hears the space they described. Accuracy is a quality gate: measured match plus listening tests (NFR-1).
- **Priority:** NFR-1 accuracy first, then NFR-3/FR-SIM-6, NFR-2. FR-3D-3 sets the categories that coverage is reported against.
- **Hard constraints:**
  - NFR-8/FR-SIM-2: no scene-specific logic. Phase 05 adds generic reduction rules and no per-room tweaks.
  - Selections and pair lists are committed before any sim–meas number, and nothing is dropped after results.
  - AX4 override is validation-only. AQ1: one broadband s (AX17). AQ8: omni only.
  - Datasets are never committed.
  - phase-05 24 h rule. "K unchanged" (SD-3 reversal).
- **Verification culture:** every behaviour has an automated check. Statistics follow AX11 (SE ≤ threshold/3). Checks must be neither vacuous nor flaky. Labels are "evidence, not validation" (SD-2).
- **PRD is silent on:** what counts as a matched-pair result. That is product policy from F2 and decider report 15.

---

### D1. Configuration subset and pair list
**Restatement.** This chooses which Arni configurations and receivers become scenes, and how the committed pair list is drawn. The pilot, K, the report size and the nightly runtime all depend on it.

**Validity screen.**
- **(c) is out.** Letting runtime set the sample size contradicts the settled rule "K unchanged; too long → outside CI under the 24 h rule" (SD-3, phase-05d scope 6).
- (a) and (b) survive.

**Scoring.**
- **NFR-1:** coverage of the full absorption range matters. Arni's room-average α is linear in n (researcher report 14 V3, external), so stratifying on n spreads the evidence evenly over the absorption range.
- **Option (b):** a fixed count per bin has no link to K and is arbitrary.
- **Option (a):** sized by the statistics. It is also cheapest, which serves AQ10 indirectly through nightly time.
- **Disjointness:** pairs that share a configuration share that configuration's model error, so SE would be understated. Disjointness must therefore be defined at configuration level.

**DECISION: (a), as follows.** Exact wording for the phase-05d Data bullet:

> **Configuration subset (Arni).**
> - **AQ9 sample:** for every n = 0…55 present in `combinations_setup.csv`, one configuration is drawn uniformly by a fixed integer seed. The seed is written in `arni_mapping.md` before the draw. All 5 receivers are used.
> - **Pair list:** take all matched candidates (same n, equal open–open shared-edge length). Draw an ordered list of configuration-disjoint pairs: cycle through the n values in increasing order and, at each n that still has candidates, draw one unused pair per cycle with the same seed, until no candidates remain. No configuration appears in two pairs. Each pair gets one receiver, assigned cyclically 1–5 in list order. The ordered list is committed.
> - **Pilot and K:** the pilot is the first 51 pairs. The reported set is the first K′ = max(51, ⌈9·σ_d²⌉) pairs, with σ_d in jnd taken as the largest over T30, EDT and C80. Pilot pairs count towards K′. If after the run σ_d/√K′ > 1/3 jnd for any metric, the set is extended in list order.
> - **dEchorate:** all 11 configurations, all IRs of the omni source positions, no sampling. A pair's unit d is the mean over all its omni-source/receiver combinations.

**Confidence:** medium. This is product and statistics; there is no acoustic claim beyond the external V3.

**Reversal:** the 05d session finds that matched candidates exist at only a few n. Then the cycle simply covers those n, and the report states which n were covered.

---

### D2. Unit (and sign) of d
**Restatement.** This sets how a pair's T30/EDT differential becomes jnd units. The pilot σ_d, K and the 1-jnd reading in F2 all depend on it.

**Validity screen.** All three options are arithmetically valid, but only one keeps the SD-2 claim ("input bias cancelled to first order"). Let a common input error scale both simulated T of a pair by (1 + b):
- **(a)** d/(0.05·T̄) leaves b·ΔT_meas in d, so the bias leaks in at first order.
- **(c)** e_a − e_b = (1 + b)(m_a − m_b) scales the model error by (1 + b). With Arni's pre-calibration T errors of 6–40 % (researcher report 14 V3, external), the jnd count would shift by that much.
- **(b)** ln(T_a,sim/T_b,sim) − ln(T_a,meas/T_b,meas): ln(1 + b) cancels exactly.

**Corpus support for (b).** Vorländer Table 6.1 gives the EDT jnd as a relative 5 %, and a relative jnd is a fixed step in ln T. C80 is already a level (dB), so (b) makes T and C80 the same kind of quantity: a difference of logarithms.

**Missing sign convention.** The definition needs an orientation that does not depend on results. If a/b is arbitrary, a model that misses the distribution effect gives a mean d ≈ 0. The test would then be vacuous. This matters most for T30, where the simulated ΔT ≈ 0 by construction (Eyring tail).
- Orient by an input-only predictor: phase 05's a* radiosity solver (Kuttruff §5.7). Kuttruff Table 5.2 shows that distribution alone moves T both ways at equal A (cases 4 and 6 against Eyring).
- An orientation taken from inputs never biases the null: E[d] = 0 when the simulation is right, whatever the sign rule. It only sets power.

**DECISION: (b) plus a committed orientation.** Exact wording for scope 3 / scope 4:

> d_X = [ln(X_a/X_b)]_sim − [ln(X_a/X_b)]_meas, divided by 0.05, for X = T30 and EDT (T at the working 5 %, AQ9; EDT 5 %, Vorländer Table 6.1). For C80, d = [(C80_a − C80_b)_sim − (C80_a − C80_b)_meas]/1 dB.
> Orientation: a is the configuration with the longer a* T at 1 kHz (phase-05 solver, same committed α and s, converged < 0.4 %). Where |ΔT_a*| is below 0.4 %, a is the lower CSV combination number. The orientation is committed with the pair list.

**Notes.**
- Dividing by 0.05 rather than ln 1.05 = 0.0488 keeps first-order equality with the AQ9 e/0.05 metric, a 2.4 % difference.
- For T30, d is essentially −Δln T30_meas/0.05: the distribution effect that Eyring cannot see (SD-2 B12 row).

**Confidence:** high for the unit (Table 6.1 relative jnd; algebra shown). Medium for the a* orientation.

**Reversal:** none expected for the unit. The orientation is revisited if Phase 05 finds a* unconverged on panel layouts.

---

### D3. Bands of d
**Restatement.** This sets which bands the pair statistic averages over.

**Validity screen.** All three options are valid.
- **(b)** means 9 tests per set (3 metrics × 3 bands), so a family false-positive rate of about 2.4 % at a true d = 0, and K driven by the noisiest band.
- **(c)** departs from the AQ9 convention.

**Scoring.**
- **(a)** reuses the settled AQ9/B11(B)/handover convention: mean over 500 Hz, 1 kHz and 2 kHz, with the 500–1000 Hz mean printed as the in-range figure (phase-05 scope 6).
- Averaging bands before the test lowers σ_d, and so K.
- The mean must be signed. A mean of |d| has a positive mean under the null.
- Cancellation across bands is exposed by printing the per-band values.

**DECISION: (a).** Exact wording:

> Per pair, d̄ = mean of the signed per-band d over the evaluable bands among 500 Hz, 1 kHz and 2 kHz (Phase 05 evaluability rules; a pair with no evaluable band is "not evaluable"). σ_d, K and the 1-jnd check use d̄. The report also prints the 500–1000 Hz mean as the in-range figure (Table 6.1 jnds are stated for 500–1000 Hz; 2 kHz by extension, AQ9), and the per-band means with SE, descriptive only.

**False-positive rate:** two-sided, 0.27 % per metric, ≈ 0.8 % across T30, EDT and C80 per set.

**Confidence:** medium-high.

**Reversal:** per-band means of opposite sign that each exceed 1 jnd. This is visible in the 05d report and goes to the Expert.

---

### D4. Scattering input, and the dEchorate α rule
**Restatement.** Neither set documents s, and phase-05 forbids running without scattering. This fixes which s goes into the scenes, how much the result depends on it, and how the dEchorate α table is chosen.

**Validity screen.**
- **(b) is weak on NFR-1.** One generic s ignores documented geometry. The Annex shows that s depends on a/λ and on shape (Vorländer Annex, scattering tables, Fig. A.1).
- (a) and (c) survive.
- **s = 1 is rejected as a sensitivity value.** With AX21 (specular-only early part), s → 1 empties the early part. EDT and C80 would then measure the AX21 deficit, not s.

**Scoring.**
- Round-robin III names the chosen scattering coefficients as decisive and says a good scattering model is essential in a smaller room (Vorländer §11.5). With s undocumented, NFR-1 evidence needs a measured sensitivity, so (c).
- For Arni, a panel's geometry does not change with its state. So s errors are largely common to both members of a pair, and they cancel to first order in d as well.
- **Sensitivity direction:** halving s lowers the AX21 contamination. The step is a product choice; the Annex gives no uncertainty and says its values are rounded.

**DECISION: (c).** Exact wording for the mapping-file bullet:

> **Scattering (both sets)**, committed before results:
> 1. Per surface, read the structural depth h and length a from the documented geometry (Arni panel drawing; dEchorate panel layout, gaps included).
> 2. At each band where a/λ < 0.125, set s = 0.05. Vorländer Annex: below 0.125, s is "generally smaller than 0.05".
> 3. Otherwise, take the Annex scattering row of the same class (1-D or 2-D, Fig. A.1) with the nearest h/a, then the closest shape description. If rows tie, use their mean. Interpolate linearly in log₂(a/λ) between columns, and hold the end column beyond the table.
> 4. Map to faces by Phase 05's reflected-energy weighting, then reduce to broadband by AX17.
>
> **Sensitivity run:** every face at s/2 (a chosen step, outside the corpus), same scenes, same pairs and K. The report prints the change in the AQ9 metrics and in d̄. Any room, configuration or d conclusion that differs between the two runs is labelled "s-limited".

**dEchorate α rule.** Its form is fixed here. The 05d session applies it and writes it in `dechorate_mapping.md` before results, and the interrogator checks the chosen rows against `docs/corpus/` (CLAUDE.md):

> For each material named in the dEchorate documentation (Formica 20 mm, perforated panels with rock or glass wool, carpet), take the Vorländer Annex random-incidence α row that matches by, in order: material family; construction (porous backing or cavity, mounting); nearest thickness. If rows tie, use their per-band mean. Record the row(s) and the reason.

The Arni α rule stays as written.

**Shared gap rule for both sets.** Bands below the lowest tabulated band take that band's value and are flagged. The Annex starts at 125 Hz; Arni's table starts at 250 Hz (researcher report 14 V1). These bands are method-validity evidence (Arni) or not evaluable (dEchorate), so AQ9 is unaffected.

**Confidence:** medium. The rule is corpus-backed; the s/2 step is a product choice.

**Reversal:** if the s/2 run moves no conclusion in Phase 05d, the sensitivity can be dropped from the nightly run (via /fix-plan). If it moves many conclusions, the result is "s-limited" and goes to the Expert.

---

### D5. Arni atmosphere for the AX4 override
**Restatement.** This sets which T and RH the Arni scenes are rendered at. It affects the absolute AQ9 numbers and, through atmosphere differences between the two measurement times of a pair, d.

**Validity screen.**
- All three options are valid.
- **(c) adds cost without information.** The simulated tail is Eyring + air (AQ2), so rendering at both ends reproduces the deterministic Eyring humidity bound that phase-05 already computes.
- Only per-IR conditions (a) remove the atmosphere difference between the two members of a pair.

**Size of the effect (Kuttruff Table 6.1, 20 °C).**
- At 2 kHz, m is 2.58 at 40 % RH and 2.28 at 50 % (×10⁻³ m⁻¹).
- With V = 201.85 m³, 4ΔmV = 0.242 m².
- At T = 1.28 s, A ≈ 0.161·V/T = 25.4 m² (Kuttruff Eq. 4.12; illustrative T from Arni's 500 Hz range). That gives ΔT/T ≈ 0.95 % ≈ 0.19 jnd at 2 kHz, and ≈ 0.06 jnd on the band mean.
- At 500 Hz and 1 kHz the change is negligible (Δm ≤ 0.03·10⁻³ m⁻¹).
- The 28.5 % end is below the corpus table. The session computes it with the code's ISO 9613-1 function (outside the corpus).

**DECISION: (a) if logged, else (b).** Exact wording:

> If the record gives temperature and RH per IR or per combination, render each scene at its own logged values. Otherwise render at the campaign mid-range, 19.8 °C and 39 % RH (midpoints of 19.3–20.3 °C and 28.5–50 %, researcher report 14 V4), and print per band Phase 05's Eyring humidity bound between the two ends (19.3 °C/28.5 % and 20.3 °C/50 %). Where that bound on d̄ exceeds 1/3 jnd, d̄ is labelled "atmosphere-limited". It is a systematic term, not reduced by K.

dEchorate stays at 24 °C, 80 % RH.

**Confidence:** medium-high.

**Reversal:** the session finds a per-IR log, in which case (a) applies automatically.

---

### D6. dEchorate reflection timing and level
**Restatement.** This sets how a reflection's arrival is found and over which window its level is measured, for the per-face reflective-vs-absorbing comparison.

**Validity screen.**
- **(c) is out.** Phase 05's t₀ rule (first sample within 20 dB of the broadband peak) finds the direct sound, not a later reflection.
- (a) and (b) survive.

**Scoring.**
- Reuse the settled AX13 convention: a ±2.5 ms window around a broadband |h| peak. Report a band only where the filter keeps ≥ 99 % of an impulse inside the window, which means 1 kHz and up.
- Isolation: allow any other image in the window only if it is at least 10 dB weaker. That limits the leakage to ≤ 10·log₁₀(1.1) = 0.41 dB, against the 2 dB scale of Vorländer §11.1.2.
- Detect the arrival the same way in both IRs, as in Phase 05.

**DECISION: (a) for timing, with an AX13 window for level.** Exact wording:

> - A reflection is evaluated only if, by the simulated image list, no other arrival within ±2.5 ms of it has predicted broadband energy within 10 dB of its own.
> - **Timing:** the largest broadband |h| within ±2.5 ms of the predicted arrival. Delays are taken relative to each IR's t₀ (Phase 05 rule), and the simulated delay is scaled by c_sim/c_meas = 343/346.98 before comparison.
> - **Level:** band energy in a ±2.5 ms window centred on each IR's own detected peak, with bands reported per AX13 (≥ 99 % rule: 1 kHz and up). Reported per face as ΔL = L_absorbing − L_reflective, simulated against measured, in dB.

**Confidence:** medium.

**Reversal:** the isolation rule leaves almost no evaluable reflection in the 6 × 6 × 2.4 m room. The session reports the count; a different window needs an AX through /fix-plan.

---

### D7. Too few qualifying pairs
**Restatement.** This sets what the report says when a set cannot reach the 51-pair pilot or K. It is certain for dEchorate: 11 configurations give at most 5 configuration-disjoint pairs.

**Validity screen.**
- **(c) is out.** Pooling mixes two different matching conditions (edge-matched panels against whole faces) and two different unit definitions, so the label "input-matched" would no longer describe one test. It would also add at most 5 units.
- (a) and (b) survive.

**Scoring.**
- (b) keeps the information (mean, SE, count) at no risk, as long as it is labelled.
- Phase 05's conventions apply: "not evaluable, never a pass" and the "no evaluable pair" branch.

**DECISION: (b), labelled as not evaluable.** Exact wording:

> If a set has fewer than 51 configuration-disjoint pairs, or its committed list ends before K′ is reached, the report prints mean d̄, SE, the number of pairs and per-band values, labelled "descriptive: too few pairs for the 1-jnd test". No 1-jnd conclusion is drawn, and for the F2 commissioning reading the set counts as "no evaluable pair". Sets are never pooled.

**Confidence:** high (reuses Phase 05 conventions).

**Reversal:** none.

---

### SD-4 beta wording, corrected
Replace "mid room 145–454 m³" with:

> "Coverage: domestic small room (one treated empty cuboid, dEchorate 86 m³), mid rooms 145 m³ (BRAS CR2) and 202 m³ (Arni), halls 2 350/8 650 m³ (BRAS); none for outdoor, cars or furnished living rooms."

Where: `docs/phases/phase-13.md` lines 85–87. The figures 145 / 2 350 / 8 650 m³ come from BUILD_PLAN §3 F2.

---

### Summary
| id | decision (exact value/wording) | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| D1 | One seeded configuration per n for AQ9 (5 receivers). Ordered, configuration-disjoint pair list cycling over n, one receiver per pair (cyclic). Pilot = first 51; K′ = max(51, ⌈9σ_d²⌉), extended in list order. dEchorate: all configurations, d averaged over omni-source/receiver combinations | medium | NFR-1, F2, SD-3 "K unchanged" | — (AX11 convention) | matched candidates exist at only a few n |
| D2 | d = Δln X_sim − Δln X_meas, /0.05 (T30, EDT); C80 difference in dB /1 dB. Orientation: a = longer a* T at 1 kHz; ties → lower CSV index | high (unit) / medium (orientation) | NFR-1, SD-2 claim | Vorländer Table 6.1; Kuttruff §5.7, Table 5.2 | a* unconverged on panel layouts (Phase 05) |
| D3 | Signed mean over 500/1k/2k per pair; 500–1000 Hz printed in-range; per-band descriptive | medium-high | NFR-1, AQ9 convention | Vorländer Table 6.1 | opposite-sign per-band means each above 1 jnd |
| D4 | Annex scattering rule (h, a; a/λ < 0.125 → 0.05; nearest same-class row, log₂ interpolation; AX17), plus s/2 sensitivity with an "s-limited" label. dEchorate α: Annex row by family → construction → thickness, ties averaged; session applies, interrogator checks | medium | NFR-1, NFR-8 | Vorländer Annex tables and Fig. A.1, §11.5 RR-III, §11.1.3 | s/2 run moves nothing (drop it) or moves many conclusions (Expert) |
| D5 | Per-IR logged T/RH if available; otherwise 19.8 °C / 39 % RH plus an Eyring bound at both ends; "atmosphere-limited" if the bound exceeds 1/3 jnd | medium-high | NFR-1, AX4 | Kuttruff Table 6.1, Eq. 4.12 | a per-IR log is found |
| D6 | Isolation (no other arrival within 10 dB in ±2.5 ms); timing = broadband peak in ±2.5 ms, relative to t₀, c-scaled; level = AX13 ±2.5 ms window, bands ≥ 1 kHz, ΔL per face | medium | NFR-1 | Vorländer §11.1.2 | too few isolated reflections |
| D7 | Descriptive mean, SE and n, labelled "too few pairs for the 1-jnd test"; counts as "no evaluable pair"; never pooled | high | F2, Phase 05 conventions | — | — |

### Challenges to settled decisions
1. **Report 15 SD-3 / phase-05d scope 5, "mean d … 1-jnd check" (my own earlier wording).**
   - A mean of signed d is vacuous without a sign convention. A model blind to distribution, which is exactly the Eyring T30 case, gives a mean near 0.
   - D2's a* orientation fixes this inside the open item.
   - I also propose printing the round-robin-style mean |d̄| (Vorländer §11.5 rating uses absolute deviations), descriptive only, next to the noise floor it would show at d = 0. SD-2's B12 row speaks of the matched-pair "spread", which mean |d̄| and SD(Δln T30_meas) show and a signed mean does not.
2. **"Phase 05's report generator, unchanged" for EDT/C80 d.**
   - Under AX21 the early part is specular-only. The estimated step reaches 8.7 dB at s = 0.4 (BUILD_PLAN AX21, from Kuttruff §5.2), and Arni's protruding panels may give s in that range.
   - I propose that 05d also prints the EDT/C80 d on Phase 05's reference-hybrid IR (tools only, no simulator change), as phase-05 scope 6 does for BRAS.

### For Maisara
- **D1:** Test one Arni panel setting for each number of open panels, plus a fixed, pre-drawn list of matched pairs, using as many pairs as the statistics need and no more. Use dEchorate in full.
- **D2:** Measure the pair difference as a ratio, so a material-data error that makes every room "too long" cancels out. Fix in advance which room of a pair counts first, so a model that misses the effect cannot hide.
- **D3:** Average over 500 Hz–2 kHz, as everywhere else in the plan. Show each band separately for information.
- **D4:** Guess the scattering values from the textbook tables by a written rule, and run everything once more at half that scattering. Anything that changes gets marked "scattering-limited".
- **D5:** Use Arni's logged temperature and humidity per recording if they exist. Otherwise use the middle of the measured range and print how much the range could matter.
- **D6:** Check dEchorate's wall reflections only where a reflection stands clear of its neighbours, with the short window already used elsewhere (AX13).
- **D7:** If a dataset has too few pairs, show the numbers but draw no conclusion from them, and never mix the two datasets.
- **SD-4 fix:** The mid-room coverage line now names only the rooms actually used: 145 m³ (BRAS) and 202 m³ (Arni).

Files: `/home/user/makroof/docs/phases/phase-05d.md`, `/home/user/makroof/docs/phases/phase-05.md`, `/home/user/makroof/docs/phases/phase-13.md`, `/home/user/makroof/docs/BUILD_PLAN.md`, `/home/user/makroof/docs/review/phase-04-consult/15-decider-second-dataset.md`, `/home/user/makroof/docs/review/phase-04-consult/14-researcher-leads-verified.md`, `/home/user/makroof/docs/review/phase-04-consult/17-researcher-citations-verified.md`, `/home/user/makroof/src/sim/AirAbsorption.h`.