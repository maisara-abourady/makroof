Corpus revision: c1b171f (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`). Target: `/tmp/claude-0/-home-user-makroof/05ae2e1f-dec9-587c-bb0d-7484bc818a46/scratchpad/fixplan-diff-05d.patch`. I read `/home/user/makroof/docs/review/phase-04-consult/18-decider-05d-choices.md` only to see what the D5 and D6 rationale claims. It is not used as evidence. Dataset facts (Arni and dEchorate dimensions, panels, RH and temperature, c = 346.98, roll-off near 300 Hz, licences) are labelled external in the changed lines. They are NOT CHECKABLE and not rated below.

## 1. Part A: scope 5, mean |d̄|

| Q | Verdict | Lean and reason |
|---|---|---|
| (a) Expected mean \|d̄\| at d = 0 | **OPEN** | **None of 1–3 works as stated.** The null should mean true d = 0 for every pair, so that only noise remains. **Option 1** is the right formula, but only if σ is a noise-only σ₀. With the observed σ_d it is circular: any zero-mean normal variable gives E\|x\| = σ√(2/π), so it tests normality, not d = 0. **Option 2** cannot work: flipping signs leaves every \|d̄\| unchanged, so the permutation distribution is a single value (the observed one). **Option 3** leaves out the measured-side noise, which dominates. The Phase 04 tail is Eyring and Eyring ΔT = 0 on matched pairs (Vorländer Eq. 4.30, 4.32), so d_T30 ≈ −Δln T30_meas/0.05, and a seed-only floor would be close to 0. **Lean:** E\|d̄\|₀ = σ₀√(2/π), with σ₀² = σ²_seed (from option 3) + σ²_meas,noise. The measured-side term needs a stated noise-only source: repeat measurements if the record has them, otherwise the phase-05 figure of 2–3.5 % per single position, labelled outside the corpus. That gives √2·(2–3.5 %)/5 % = 0.57–0.99 jnd per band, reduced by up to √3 for the D3 band mean if the bands are independent. The corpus gives no figure for the repeatability of a T measurement. |
| (b) Bands and unit of SD(Δln T30_meas) | **OPEN** | **Lean: option 1** (the D3 500 Hz–2 kHz evaluable mean, /0.05, in jnd). It then shares bands, scale and null with mean \|d̄\| and σ_d, and for T30 it is practically σ_d itself. Per-band values are already printed descriptively under D3. **Two points to settle:** (i) is the SD taken about zero (RMS) or about the mean? The D2 a* orientation sets the signs, which changes the SD about the mean but not the RMS. (ii) 5 % for T is the working jnd; Vorländer Table 6.1 lists only EDT at 5 %. |

## 2. Part B: findings that are not CORRECT

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| B1 | FACT | Selector unit test: "every selected pair gives an Eyring ΔT of exactly 0", read together with D5's "render each scene at its own logged values" | INCONSISTENT | Vorländer §4.4.1 Eq. 4.32: T = 0.16V/(−S ln(1−ᾱ) + 4mV). Equal ᾱ gives ΔT = 0 only if m is also equal. Under D5 branch (a), m differs per IR, so ΔT ≠ 0 and the gate either fails or rejects valid pairs. | major | Q1 | open |
| B2 | FACT | Arni match condition: same n plus equal open–open shared-edge length means equal edge effect (Kuttruff §8.7 Eq. 8.56) | CONDITIONS VIOLATED | Kuttruff §8.7: free edges are those "not adjacent to a perpendicular rigid wall", and β "may reach 0.2 m or more". Free-edge length = n·P − 2·L_oo − L_(edge against a perpendicular surface), so the last term must also be equal. Eq. 8.57 (Waterhouse) adds a term on those adjoining edges. | major | Q2 | open |
| B3 | NUMBER | "random-incidence α can misstate a specific-angle reflection by up to 2 dB (Vorländer §11.1.2)" | CONDITIONS VIOLATED | §11.1.2 says the error stays below 2 dB only while the angle-specific loss differs by ≤ 40 %, and is larger at grazing incidence. So 2 dB is not a cap. Working with reflected energy 1−α (Eq. 4.31): a +40 % loss gives 2 dB at α = 0.48, and a −40 % loss gives 2 dB at α = 0.59. The dEchorate absorbing state is likely above both. | major | Q3 | open |
| B4 | NUMBER | D6 isolation: another arrival ≥ 10 dB weaker means leakage ≤ 10·log₁₀(1.1) = 0.41 dB (report 18 rationale; the number is not in the phase text) | CONDITIONS VIOLATED | Energy addition is the geometric-acoustics convention (Vorländer Notation §4, "phases neglected"). Two deterministic, band-filtered pulses in one ±2.5 ms window can add coherently: 20·log₁₀(1 ± √0.1) = +2.39 / −3.30 dB. | major | Q4 | open |
| B5 | FACT | "input bias cancelled to first order" (Goal, §4 05d, scope 4) | IMPRECISE | Exact for Eyring (Eq. 4.32: same ᾱ). For other models, a common error ε leaves a residual ε·(∂lnX_a/∂α − ∂lnX_b/∂α). That is still first order in ε, scaled by the a–b difference in sensitivity, not O(ε²). | minor | – | open |
| B6 | FACT | dEchorate: "the edge problem does not arise (Kuttruff §8.7)" | IMPRECISE | Kuttruff §8.7: covering an entire wall removes free edges, but Eq. 8.57 still applies along a perimeter next to a perpendicular rigid surface. It cancels only for equal adjoining perimeters (two separate 6 × 2.4 m walls, yes; two adjacent walls against two opposite walls, no). The documented panel gaps also create edges. | minor | – | open |
| B7 | FACT | "GA is limited to large rooms (Vorländer §11.5), so dEchorate small-room misses are expected" | IMPRECISE | §11.5 does list large rooms as a limit, but Round-robin III, a "smaller room with expected modal effects", reports 1–2 jnd achievable with a good scattering model. Note the corpus says "expected" modal effects, not "showed", if the main session's wording is used anywhere. | minor | – | open |
| B8 | FACT | The matched-pair spread "directly measures what Eyring cannot see" (B12 row) | IMPRECISE | Eyring ΔT = 0 (Eq. 4.32), so the measured ΔT is non-Eyring effect **plus measurement noise**. By the document's own 2–3.5 % figure, the noise alone is 0.57–0.99 jnd per band. This ties to Part A. | minor | – | open |
| B9 | NUMBER | Arni atmosphere: "19–20 °C, RH 28–50 %" and "19.3–20.3 °C and 28.5–50 %" in the same AX4 bullet, same source | INCONSISTENT (external quoting) | Both cite researcher report 14 V4. 20.3 °C lies outside "19–20 °C". The midpoints 19.8 °C and 39.25 % are correct for the second range. | minor | – | open |
| B10 | DECISION | D4: s = 0.05 wherever a/λ < 0.125 | CONSEQUENCE | Vorländer Annex: s there is "generally smaller than 0.05", so 0.05 is an upper value. The Annex concept assumes a surface large compared with corrugations and wavelength, and does not apply to single objects. That condition is not stated for panel gaps or for sparse panels. | minor | – | open |
| B11 | DECISION | D3: signed band mean | CONSEQUENCE | Per-band errors of opposite sign cancel in d̄. The per-band printout exposes this. Table 6.1 jnds are stated for 500–1000 Hz. | minor | – | open |
| B12 | NUMBER | Arni "below about 250 Hz: transition zone" | NOT CHECKABLE | It needs Arni's T, which is external. Working: Kuttruff Eq. 3.44 gives f_s ≤ 250 Hz when T ≤ 201.9·(250/2000)² = 3.15 s, and Vorländer Eq. 4.13 gives the same when T ≤ 8.8 s. | none | – | – |
| B13 | NUMBER | dEchorate c = 346.98 m/s at 24 °C, and c_sim = 343 | NOT CHECKABLE | External. For reference, Kuttruff Eq. 1.1 gives 345.8 m/s and Vorländer Eq. 1.20 gives 345.5 m/s at 24 °C, both without humidity. Kuttruff fixes 343 m/s. Whether the simulator still uses 343 when the scene is set to 24 °C is a code question. | none | – | – |

Notes on the other items the main session asked about:

- **Main-session humidity recomputation.** This is outside the changed lines. The decider's **0.95 % is right; the ≈ 0.89 % is wrong.** Working: Kuttruff Table 6.1 at 2 kHz gives 2.58 and 2.28 ×10⁻³ m⁻¹, so 4ΔmV = 0.242 m². A = 0.161V/T (Kuttruff Eq. 4.12) taken from a measured T is already the total absorption including 4mV. So ΔT/T = 0.242/25.4 = 0.95 % ≈ 0.19 jnd, and ≈ 0.06 jnd on the band mean. Adding 4mV again (giving 27.2–27.5 m²) counts air twice. Also, D5's real bound spans 28.5–50 %, which goes below the corpus table, so it will be larger.
- **Other D6 numbers.** The "≥ 99 % rule: 1 kHz and up" (AX13) is filter-specific and NOT CHECKABLE.
- **Statistics in report 18.** The family false-positive figures (0.8 % over 3 metrics, 2.4 % over 9 tests) are correct: 1 − 0.9973ⁿ.

Questions, most severe first:

- **Q1.** Is the selector's Eyring ΔT computed with each scene's own 4mV, or at one common atmosphere? If D5(a) applies, is the gate "exactly 0" at a common m, or a tolerance equal to the 4mV term?
- **Q2.** Does "equal open–open shared-edge length" also require equal open-panel edge length against perpendicular walls and the ceiling, so that L′ in Eq. 8.56 and the Eq. 8.57 term are equal?
- **Q3.** For absorbing-state reflections with α above about 0.5, what bound on the specific-angle level error is meant, given that §11.1.2's 40 % → 2 dB relation fails above α ≈ 0.48–0.59?
- **Q4.** Is the 10 dB isolation leakage meant as energy addition (0.41 dB) or as coherent addition inside the band-filtered window (+2.39 / −3.30 dB)?
- **Q5 (Part A).** Is σ in E|d̄|₀ the observed σ_d or a noise-only σ₀, and which source supplies the measured-side noise term?

## 3. CORRECT count

**27 items** in the changed lines are CORRECT:

- **Matched-pair claims.**
  - Eyring depends on α only through ᾱ (Vorländer Eq. 4.30, 4.32).
  - A common α error cancels exactly from the Eyring ΔT when each material has the same area.
  - α_eff = βL′ + α_∞ (Kuttruff Eq. 8.56).
  - Placement changes the effective α at free edges.
  - dT/dn depends on the input α.
  - EDT "varies considerably within a hall" (Kuttruff §8).
- **Low-frequency limits.** Kuttruff Eq. 3.44, 2000√(T/V); Vorländer Eq. 4.13, 1200√(T/V), printed as "≫".
- **D2 unit.**
  - A common (1+b) cancels exactly in ln(X_a/X_b).
  - The jnds: EDT 5 % and C80 1 dB, Table 6.1, stated for 500–1000 Hz; T at a working 5 %, correctly labelled.
- **D3.** A signed mean has zero expectation under the null.
- **D4.**
  - The Annex quote "generally smaller than 0.05" below 0.125.
  - The Fig. A.1 1-D and 2-D classes.
  - log₂ interpolation fits the octave-spaced a/λ columns.
- **D5.** Midpoints 19.8 °C and 39 %.
- **Timing.**
  - 346.98/343 = 1.16 %.
  - ≈ 16.05 samples at 48 kHz over 10 m.
  - c_sim/c_meas is applied to the simulated delay, which is the right direction.
- **Statistics.**
  - K ≥ 9σ_d² gives SE ≤ 1/3.
  - The K′ form.
  - Two-sided false-positive rate of 0.27 %, as an upper value at SE = 1/3.
  - K ≥ 9 at σ_d = 1. Two positions give 0.57–0.99 jnd, so "≈ 1" is the upper end.
- **Vorländer §11.5.**
  - "crucial influence".
  - The rating uses absolute deviations.
  - 1–2 jnd is achievable.
  - Large rooms are listed among the limits.
  - The F2 reading that input data dominate (Round-robin I, harmonised inputs).
- **Coverage arithmetic.** 6 × 6 × 2.4 = 86.4 m³; 202 m³ and 86 m³ are correct roundings.

## 4. WRONG

- **In the changed lines: none.**
- **Outside the changed lines:** the main session's recomputed humidity effect of ≈ 0.89 % is wrong because it counts air absorption twice. The decider's 0.95 % stands (Kuttruff Table 6.1 and Eq. 4.12).

**SOFTWARE (not rated):** fetch scripts, SHA-256 and md5 manifests, tampered-file test, cache paths, licence confirmation in THIRD_PARTY.md, nightly CI and the 24 h rule, exact report reproduction, mapping files committed before results (git history), seeded draws, scene file naming. One remark on the "ΔT exactly 0" check: ᾱ summed over different face assignments may differ at ulp level, which is a floating-point concern, not acoustics.

**DECISIONS (CONSEQUENCE only, none rated):**
- The s/2 sensitivity step is outside the corpus, so "s-limited" is only as good as that step.
- One receiver per pair: position effects cancel only for the part common to both members.
- Sets are never pooled: K is per set.