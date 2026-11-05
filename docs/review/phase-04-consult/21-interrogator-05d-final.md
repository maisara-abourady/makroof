I checked the changed lines in the final 05d patch. B1–B9 are all fixed, and the arithmetic you asked about is correct. Nothing in the changed lines is WRONG. Two new defects are major and one is minor. Both majors sit on rules that a unit test is built on.

Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`). Patch checked: `/tmp/claude-0/-home-user-makroof/05ae2e1f-dec9-587c-bb0d-7484bc818a46/scratchpad/fixplan-diff-05d-final.patch`, against `/home/user/makroof/docs/review/phase-04-consult/19-interrogator-05d-check.md`.

## 1. B1–B9

| B | fixed? | note |
|---|---|---|
| B1 | yes | Vorländer §4.4.1 Eq. 4.32. The selector is evaluated at one atmosphere (AX4, 20 °C/50 %), so equal ᾱ and equal m give ΔT = 0 exactly. Summing in a fixed material order removes the ulp-level differences. Under the per-IR branch, Δln T_Eyring is subtracted in r_k and printed, which is consistent. |
| B2 | yes | Kuttruff §8.7, Eq. 8.56/8.57. The Arni pair now also needs equal open-panel edge length against perpendicular walls and the ceiling. Free-edge length is fixed once n, the open–open length and the adjoining length are all equal. |
| B3 | yes | Vorländer §11.1.2 says a loss may differ by up to 40 % before the level error exceeds 2 dB. With reflected energy 1−α (Eq. 4.31), a 40 % higher loss gives (1−1.4α)/(1−α) = 10^−0.2 = 0.631, so 0.369 = 0.769α and α = **0.480**. A 40 % lower loss gives (1−0.6α)/(1−α) = 10^0.2 = 1.585, so 0.585 = 0.985α and α = **0.594**. At α = 0.48 the lower-loss case gives 20·log10(0.712/0.52) = 1.37 dB < 2. So "holds only for α ≤ 0.48" is the correct two-sided limit, and the label wording is fine. |
| B4 | yes, with one new condition (N1) | **Per level:** 20·log10(1.1) = **+0.828** and 20·log10(0.9) = **−0.915**, which round to +0.83 / −0.92 dB. **On ΔL:** worst case 0.828 + 0.915 = 1.743 dB. With the √0.99 allowance it is 20·log10(1.1005) + \|20·log10(0.8995)\| = 0.832 + 0.920 = **1.752 dB**, so ±1.75 dB is a correct upper value. **Single neighbour:** √(E₁/E₀) ≤ 0.1 means E₁/E₀ ≤ 0.01, i.e. 20 dB below, correct. **Test (i):** 0.10 passes (≤), 0.11 fails, and 0.06 + 0.06 = 0.12 > 0.1 fails; all correct. One software remark: 0.10 sits exactly on the limit, so its comparison can flip at the last floating-point digit. **Test (ii):** by the triangle inequality, ‖w(h₀+h₁)‖ ≤ ‖wh₀‖ + √E₁. Since √E₁ = 0.1√E₀ ≤ 0.1‖wh₀‖/√0.99 when ‖wh₀‖² ≥ 0.99·E₀ (AX13), the band 20·log10(1 ± 0.1/√0.99) is correctly derived. Coherent addition is the right worst case, since Vorländer §11.5 justifies energy addition only because "phases neglected". |
| B5 | yes | Wording matches check 19. Small residual: see N3. |
| B6 | yes, but the new wording has a defect (N2) | Kuttruff §8.7: covering a whole wall removes free edges, and Eq. 8.57 adds L″λ/8. |
| B7 | yes | Vorländer §11.5 lists "large rooms" under Limits. Round-robin III is a "smaller room with expected modal effects" and reports 1–2 jnd. Both are quoted correctly. |
| B8 | yes | "plus measurement noise" is added, and the noise reference is printed beside it. |
| B9 | yes | 19.3–20.3 °C and 28.5–50 % are now used throughout. Midpoints: 19.8 °C, and 39.25 % rounds to 39 %. |

## 2. Other checks requested (all CORRECT)

- **E\|d̄\|₀ = √(2/π)·(1/K)·Σσ₀,ₖ:** each d̄ₖ ~ N(0, σ₀,ₖ²) has E\|x\| = σ√(2/π). This is consistent with check 19 Part A.
- **Sampling range ±3·√((1−2/π)Σσ₀,ₖ²)/K:** Var\|x\| = (1−2/π)σ², so the mean of K independent terms has SD √((1−2/π)Σσ²)/K.
- **Mean \|x\| test:** 1 − 2/π = 0.3634, √0.3634 = 0.6028, divided by √10 000 = 100 gives 0.006028, times 3 gives **0.0181**, so 0.018 is right. √(2/π) = 0.7979 rounds to 0.798.
- **σ₀² = σ²_seed + σ²(a) + σ²(b):** correct for independent terms.
- **RMS reference √(meanₖ σ²_meas,noise,ₖ):** under no placement effect E[rₖ²] = σ²_meas,noise,ₖ, so it is right. Taking it about zero makes it independent of the D2 sign. Leaving out σ_seed is right, because the Eyring Δln T is analytic.
- **"0 at a common atmosphere by selection":** follows from Eq. 4.32.
- **Not checkable against the corpus:** the AX11 noise model, the "probably an upper value for EDT and C80" label, "repeat SD is a lower value", and the dataset facts.

## 3. New findings that are not CORRECT

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| N1 | NUMBER | Isolation bound +0.83/−0.92 dB per level and ±1.75 dB on ΔL, with unit test (ii) sweeping delay over ±2.5 ms | CONDITIONS VIOLATED | Working (triangle inequality): the bound holds only if every arrival with energy inside the level window is counted. The level window is ±2.5 ms centred on the IR's detected peak, but the rule counts only arrivals within ±2.5 ms of the predicted arrival. A band-filtered neighbour just outside 2.5 ms, or one inside the window because the detected peak is offset, leaks in uncounted. Test (ii) never places a neighbour beyond 2.5 ms, so it cannot catch this. The corpus gives no filter-length figure. | major | Q1 | open |
| N2 | FACT | dEchorate rule "equal absorbing-face perimeter adjoining perpendicular surfaces", with the example "adjacent walls against opposite walls do not [pass]" | INCONSISTENT | Kuttruff §8.7 says the Waterhouse term applies near a "perpendicularly adjacent rigid wall"; Eq. 8.57 is S_eff = S_s + L″λ/8, where L″ is the sample perimeter. In a 6 × 6 × 2.4 m room, two 6 × 2.4 m walls have 2 × 16.8 = 33.6 m of perimeter against perpendicular surfaces whether they are adjacent or opposite. Against rigid surfaces only, adjacent walls give 33.6 − 2 × 2.4 = 28.8 m. So the rule as written passes the adjacent pair that the example says fails, and the selector test is built on this rule. | major | Q2 | open |
| N3 | FACT | "input bias cancelled exactly for Eyring (equal ᾱ, Eq. 4.32)", under the Arni per-IR atmosphere branch | IMPRECISE | Vorländer Eq. 4.32: ∂lnT/∂ᾱ = −[S/(1−ᾱ)]/(−S ln(1−ᾱ) + 4mV). With unequal m, the two members' sensitivities differ by about Δ(4mV)/A, roughly 1 % (check 19: 0.242/25.4 m²). So the cancellation is exact only at a common m, and the residual is about 0.01·ε·sensitivity. | minor | – | open |

**Questions**
- **Q1.** Does the isolation rule count every arrival whose band-filtered energy falls inside the peak-centred ±2.5 ms level window (so the window around the arrival is widened by the filter length and the peak offset)? Or is the ±0.83/−0.92 dB bound meant only for neighbours within ±2.5 ms of the predicted arrival?
- **Q2.** In the dEchorate perimeter rule, does "perpendicular surfaces" mean perpendicular *rigid* (reflective-state) surfaces, as Kuttruff §8.7 states, so that the adjacent-walls example fails?

## 4. WRONG
None in the changed lines.