Corpus revision: c1b171f (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`).

**PRD digest (3 lines)**
- **Users and outcome.** The users are producers and DJs who are not acoustics specialists. They must hear their track in the space they designed. Accuracy is a quality gate: "measured match against real impulse responses + listening tests" (PRD metrics table, NFR-1, Q9).
- **Priority.** NFR-1 accuracy comes first. Then NFR-8 / FR-SIM-2 (generic engine, nothing tuned per scene), then NFR-3 / FR-SIM-6 (movement without artefacts, not touched here), then NFR-2 cost.
- **Hard constraints.** No change to `src/sim` or the contract in 05d. AX5 / CLAUDE.md: everything is deterministic and seeded. CLAUDE.md requires an automated, non-vacuous check for every behaviour. Atmosphere is not user-facing (PRD out-of-scope list; the AX4 override is for validation only). The PRD says nothing on what a measured-noise null should be.

---

## 1. Part A (a), (b) and Q5: the reference printed beside mean |d̄|, and SD(Δln T30_meas)

**Restatement.** Two descriptive figures go next to the B12 "spread" in the scope 5 report:
- the value mean |d̄| should have if d = 0;
- the measured-only placement spread of T30.

Both feed Maisara's F2 reading. Neither gates CI.

**Validity screen**
- The observed σ_d is out, because it is circular (interrogator §1).
- The sign-flip permutation is out, because it is degenerate.
- A floor from the seed alone is out, because it leaves out the measured-side noise.
- The interrogator's lean survives: σ₀² = σ²_seed + σ²_meas,noise, with E|x| = σ√(2/π) for a zero-mean normal variable. That is maths, not acoustics.
- That leaves the question of where the measured-side noise term comes from. There are three candidates:
  - **(i) Repeated measurements in the record.** This is not valid as σ₀. A repeated deterministic IR measurement at one point captures only additive and electrical noise. It does not capture the realisation scatter: the part of one measured decay that no model can predict, and which Phase 04's seeded tail cannot match. Repeats would therefore underestimate σ₀ (a signal-processing argument, not from the corpus). Keep them only as a lower value.
  - **(ii) Phase 05's 2–3.5 % per position.** This is valid but crude. It is an ISO 3382-2 estimate for T = 0.8 s, outside the corpus, and covers T30 only (phase-05 line 20). It does not scale with T or band, and Arni's T changes with the number of open panels, n. It gives no figure for EDT or C80, although the accepted Challenge 1 asks for the reference "per metric".
  - **(iii) The AX11 single-realisation scatter model** (BUILD_PLAN AX11, a project fact outside the corpus). Treat each measured IR's decay as one noise realisation at its own measured band T30, and compute the scatter of the metric with the project's seeded tooling. It scales with T and band, covers all three metrics, and is the same noise model the project already uses for the simulated side.

**Scoring.**
- **NFR-1:** (iii) gives a reference that fits each IR and is computed the same way on both sides. (ii) gives a fixed range: two reference values, and none for EDT or C80.
- **Testability:** (iii) is deterministic because it is seeded. It needs no "is a repeat present" branch.
- **Cost:** K′ pairs × 2 members × 51 short noise realisations, with no renders. This is small.
- **Reversibility:** this is analysis-only code.
- **Weakness of (iii):** for EDT and C80 it probably overstates the noise. A measured IR's early reflections are deterministic, and the ISM is meant to predict them. The label must say so.

**For (b).** I take the interrogator's option 1: the D3 band mean, divided by 0.05, in jnd. I take the figure **about zero (RMS)**, for two reasons:
- The D2 orientation (a* T at 1 kHz) is a simulator choice. A figure about the mean would make a "measured-only" figure depend on it. The RMS does not.
- B12 asks how much of the measured placement effect Eyring cannot see. Eyring predicts ΔT = 0 at a common atmosphere (Vorländer Eq. 4.30, 4.32), so the whole RMS is what Eyring misses. That includes the mean part. Its value with no placement effect is the noise RMS.

Under D5's per-IR atmosphere branch, the Eyring atmosphere term must be subtracted first, so that air is not counted as placement (see decision 2).

**DECISION.** Replace the *(open)* sentence in scope 5, and "SD(Δln T30_meas)" in the B12 row, with:

> **Expected value at d = 0** (decider report 17, accepted by Maisara, <date>): E|d̄|₀ = √(2/π)·(1/K)·Σₖ σ₀,ₖ, with σ₀,ₖ² = σ²_seed,ₖ + σ²_meas,noise,ₖ, per metric, in jnd on the D3 band mean. The observed σ_d is never used for σ₀.
> - σ_seed: the SD of the simulated term over ≥ 51 seed-paired renders (AX19 sampling rule). It may be estimated on the 51 pilot pairs, with their mean square applied to all pairs.
> - σ_meas,noise,ₖ² = σ²(a) + σ²(b). Each member's σ comes from the AX11 single-realisation model (outside the corpus): R ≥ 51 seeded white-noise sequences, split by the `tools/acoustics` octave filters, each band given an exponential decay at that member's measured band T30. The metric is computed per band, then the D3 band mean is taken.
> - The report prints E|d̄|₀ with its sampling range ±3·√((1−2/π)·Σₖσ₀,ₖ²)/K, descriptive only, labelled "noise-model reference (AX11 model, outside the corpus); for EDT and C80 probably an upper value, since a measured IR's early reflections are deterministic".
> - If the record holds repeated measurements of one configuration and receiver, their SD is printed as a lower value (additive noise only). It is not used for σ₀.
> - Unit test: over 10 000 seeded N(0, 1) draws, mean |x| lies within 3·√(1−2/π)/100 = 0.018 of √(2/π) = 0.798.
>
> **RMS(Δln T30_meas)**: rₖ = [Δln T30_meas,ₖ − Δln T_Eyring,ₖ]/0.05 on the D3 band mean. Δln T_Eyring,ₖ is the pair's Eyring Δln T at the rendered atmospheres; it is 0 at a common atmosphere by selection. The figure is √(meanₖ rₖ²), taken about zero so that it does not depend on the D2 orientation, in jnd (T at the working 5 %, AQ9). It is printed beside its value with no placement effect, √(meanₖ σ²_meas,noise,ₖ), from the same noise model.

**Confidence: medium.** The formula and the RMS choice are mathematical. The noise model is outside the corpus, and the corpus gives no figure for how repeatable a T measurement is (interrogator §1).

**Reversal condition.** Arni has 5 receivers. If their T30 scatter within one configuration is clearly below the model's σ (beyond 3·SE), the model overstates the noise and should be revisited. The 05d session can see this from its first data. A corpus or standards source on how repeatable a single-position T measurement is would also reverse it.

---

## 2. B1 / Q1: "Eyring ΔT exactly 0" against per-IR atmospheres

**Restatement.** Should the selector's gate compare at one common atmosphere or with a tolerance? And how does the per-IR difference in 4mV then enter d?

**Validity screen.** Vorländer Eq. 4.32 gives T = 0.16V/(−S ln(1−ᾱ) + 4mV), so equal ᾱ gives ΔT = 0 only when m is equal (interrogator B1).
- A tolerance set to the 4mV term would mix two separate questions in one gate: is the pair matched, and does the air differ? It also adds a number that has no requirement behind it.
- A common atmosphere is valid. The selector's job is to match geometry and materials.

**Scoring.**
- **Testability:** a common atmosphere keeps the test exact and non-vacuous. The interrogator's ulp remark (floating-point rounding) goes away if ᾱ is summed from per-material area totals in a fixed order. Two matched pairs then produce bit-identical sums.
- **How the atmosphere enters d.** Under D5 branch (a), each member is rendered at its own logged atmosphere. The simulated ln-ratio then contains the same 4mV difference the measured ratio contains, so it cancels in d to the accuracy of the air-absorption model. This is a correction, not an uncorrected systematic term, so no label is needed.
- **The residual** on the input-bias cancellation is first order in a common α error ε, scaled by about 4ΔmV/A. The derivation comes from Eq. 4.32: ∂lnT/∂ᾱ = −(S/(1−ᾱ))/A, differenced between A_a and A_b. The interrogator puts 4ΔmV/A at about 1 % at 2 kHz over the Kuttruff Table 6.1 RH span, and probably more down to 28.5 % RH. So the cancellation stays at about 99 %.
- **Branch (b)** keeps D5's "atmosphere-limited" label exactly as written. Both members are rendered at the same m there, so the real difference goes uncorrected.

**DECISION.** Replace the selector criterion with:

> Matched-pair selector unit test: every selected pair has equal per-material area totals and equal edge lengths (scope 4). At one common atmosphere (AX4 standard, 20 °C/50 % RH), with ᾱ summed from the per-material area totals in a fixed material order, it gives an Eyring ΔT of exactly 0. A deliberately unmatched pair is rejected; this is the negative control, so the test is not vacuous.

Add to the D5 atmosphere rule:

> Under the per-IR branch, the atmosphere difference within a pair is corrected in the render: each member's simulated IR carries its own 4mV, so it cancels in d to the accuracy of the air-absorption model, and no label applies. The report prints per set and band the mean and largest |Eyring Δln T at the rendered atmospheres|/0.05, as the size of that correction. Under the mid-range branch, the "atmosphere-limited" rule applies as written.

**Confidence: high** (Vorländer Eq. 4.32; NFR-1; CLAUDE.md test rule).

**Reversal condition.** Phase 05's BRAS high-band results might show the air-absorption model in error by more than the printed correction sizes. In that case the per-IR correction needs its own label.

---

## 3. B3 / Q3: the per-face ΔL label

**Restatement.** How to state the uncertainty of the dEchorate per-face ΔL (absorbing state minus reflective state), simulated against measured.

**Validity screen.** Vorländer §11.1.2 says the specific-angle loss "may differ from the random-incidence loss by up to 40 % before the reflection-level error exceeds 2 dB". Working with reflected energy 1−α (my check):
- +40 % loss: 10·log10((1−1.4α)/(1−α)) = −2 dB at α = 0.48.
- −40 % loss: +2 dB at α = 0.59.
- At α = 0.9 the −40 % case gives +6.6 dB, and the +40 % case has no lower bound at all.

So "up to 2 dB" as a cap is CONDITIONS VIOLATED for the absorbing state. Reporting the reflective state only would throw away the one measured quantity that bears on the table α of the absorbing panels. That α is the F2 question of whether input data dominate (§11.5).

**Scoring.**
- **NFR-1:** keeping ΔL with an honest label preserves real evidence on the α inputs.
- **Testability:** the label is computed from the committed α, so a unit test on the label rule is trivial.
- **Cost:** nil. Printing an interval derived from "40 %" would treat 40 % as a known spread of real deviations, which the corpus does not say. Labelling only is the honest minimum.

**DECISION.** Replace the dEchorate "Early reflection level" table cell, and add the same sentence to scope 3's Level bullet:

> Reported, descriptive. It depends on the table α. Vorländer §11.1.2: random-incidence α keeps a reflection's level error below 2 dB while the specific-angle loss is within 40 % of the random-incidence loss; as a level bound (reflected energy 1 − α) this holds only for α ≤ 0.48. Per face and band where either state's committed α exceeds 0.48, ΔL is labelled "α-limited: no corpus bound"; elsewhere it carries "≤ 2 dB per level if the angle loss is within 40 % (§11.1.2)". The measured ΔL is evidence on the absorbing panels' table α, not a method test.

**Confidence: high** (Vorländer §11.1.2 and Eq. 4.31 arithmetic; NFR-1).

**Reversal condition.** The dEchorate documentation might give impedance or angle-dependent α. Vorländer Eqs. 3.3–3.6 would then allow angle-dependent values. The 05d session finds this out when it reads the record.

---

## 4. B4 / Q4: the isolation threshold

**Restatement.** Which rule admits a reflection to the timing and level checks, so that leakage from other arrivals is bounded?

**Validity screen.**
- Two band-filtered pulses inside one window can add coherently. Vorländer's "phases neglected" convention (Notation §4) is a geometrical-acoustics modelling choice, not a fact about the measured IR. So the 0.41 dB figure is invalid.
- Keeping 10 dB with the correct bound is valid. But the bound is +2.39 / −3.30 dB per level, which is ±5.7 dB worst case on a ΔL made of two levels. That swamps the effect being read.
- A threshold on the single strongest neighbour does not bound the case of several neighbours.
- The rule as worded ("within 10 dB of its own") also fails to exclude a much stronger neighbour, such as the direct sound.

**Scoring: how many reflections survive.**
- Kuttruff Eq. 4.6 gives a reflection rate dN/dt = 4πc³t²/V. With V = 86.4 m³ and c = 343 m/s, the mean number of arrivals in a 5 ms window is ≈ 29 300·t²:
  - 0.73 at t = 5 ms;
  - 2.9 at t = 10 ms;
  - 6.6 at t = 15 ms.
- Eq. 4.6 is a mean over the image lattice, so it gives an expected count, not a guarantee.
- In the reflective state, a neighbour with a similar path length and low α is only a few dB weaker. It fails a 10 dB rule and a 20 dB rule alike.
- So survival is set by the ±2.5 ms window, not by the threshold. Only early reflections near the direct sound survive either way, and 20 dB costs little more.
- In return, the worst-case error on ΔL falls from ±5.7 dB to ±1.75 dB. That is below the effect being read: 10·log10(1−α) is −3 dB at α = 0.5 and −10 dB at α = 0.9.
- An amplitude-sum rule bounds several neighbours at once and covers the direct sound automatically.
- Applying the rule per reported band and in both states is needed. The absorbing state lowers the reflection itself, so a neighbour that is 20 dB down in the reflective state can be close in the absorbing one.

**DECISION.** Replace D6's isolation bullet with:

> A reflection is evaluated only if, by the simulated image list, in each reported band and in both the reflective and the absorbing scene, the other arrivals within ±2.5 ms of it satisfy Σᵢ √(Eᵢ/E₀) ≤ 0.1, where E₀ is the reflection's own predicted energy. Stronger arrivals, including the direct sound, count. Coherent addition then bounds the leakage to 20·log10(1 ± 0.1) = +0.83 / −0.92 dB per level, and ±1.75 dB worst case on ΔL. A single neighbour meets it at ≥ 20 dB below. The report prints the number of evaluable reflections per face; a face with none is "not evaluable".
>
> Unit tests:
> - (i) The rule accepts one neighbour at amplitude ratio 0.10 and rejects 0.11, and rejects two neighbours at 0.06 each.
> - (ii) Two band-filtered pulses at amplitude ratio 0.1, with the delay swept over ±2.5 ms, give a windowed band level within 20·log10(1 ± 0.1/√0.99) of the single pulse's windowed level. The √0.99 allows for AX13's ≥ 99 % window rule.

**Confidence: high** for the bound (maths, plus Vorländer Notation §4) and **medium** for the survivor estimate (Kuttruff Eq. 4.6 is a mean).

**Reversal condition.** Test (ii) may show that the band-filtered cross term falls well below the worst case for delays beyond about 1/B. A delay-dependent rule could then admit more reflections. This is visible in the 05d session's unit test. Separately, if the count printed per face is zero for every face, the check is reported "not evaluable"; the threshold is not loosened.

---

## Summary

| id | decision (exact value/wording) | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| A / Q5 | E\|d̄\|₀ = √(2/π)·mean σ₀,ₖ, with σ₀² = σ²_seed + σ²_meas,noise. The measured term comes from the AX11 noise model at each member's band T30, run through the D3 band mean; σ_d is never used. RMS(Δln T30_meas − Eyring Δln T)/0.05 is taken about zero, beside the noise RMS | medium | NFR-1, Q9, CLAUDE.md tests | maths; Vorländer Eq. 4.30, 4.32 (Eyring ΔT = 0). The noise model is outside the corpus | Arni's within-configuration receiver scatter falls below the model σ (05d session) |
| B1 / Q1 | Selector: equal per-material areas; Eyring ΔT exactly 0 at the AX4 common atmosphere, with ᾱ summed in a fixed order. Per-IR atmosphere is corrected in the render and its size printed; the "atmosphere-limited" label applies only under the mid-range branch | high | NFR-1, CLAUDE.md tests | Vorländer Eq. 4.32 | BRAS shows an air-model error larger than the correction (Phase 05) |
| B3 / Q3 | ΔL is descriptive. It is labelled "α-limited: no corpus bound" where the committed α > 0.48; otherwise it carries the conditional "≤ 2 dB per level" note. It is evidence on the table α | high | NFR-1 | Vorländer §11.1.2, Eq. 4.31 | angle-dependent α or impedance is found in the dEchorate record |
| B4 / Q4 | Σ√(Eᵢ/E₀) ≤ 0.1, per band, in both states, counting stronger arrivals. Bound +0.83/−0.92 dB per level, ±1.75 dB on ΔL. Count printed. Two unit tests | high / medium | NFR-1, CLAUDE.md tests | Vorländer Notation §4; Kuttruff Eq. 4.6 | test (ii) shows a smaller cross term at longer delays (05d session) |

## Challenges to settled decisions

None. Two small points:
- Decision 4 changes D6's "broadband" isolation to a per-band rule. That falls within the "another rule" scope Q4 opened, but Maisara should see that it touches D6's wording.
- Decision 1 renames "SD(Δln T30_meas)" to "RMS(…)" in the accepted Challenge 1 text.

## For Maisara

- **A / Q5:** Beside the "mean |d̄|" figure, the report prints what pure measurement noise alone would give. That noise level is estimated from each measured decay by the project's own noise model, never from the result itself. The T30 spread is taken as an RMS about zero, so it does not depend on how pairs were oriented.
- **B1:** The pair selector matches rooms on geometry and materials at one fixed atmosphere, so its "exactly 0" test stays exact. When each recording has its own logged temperature and humidity, the simulation already accounts for them, and the report shows how big that correction was.
- **B3:** For absorbing panels, the book's "2 dB" limit does not apply, because it only holds up to absorption 0.48. Those level changes are therefore printed as "α-limited: no corpus bound": evidence about the material table, not a test of the method.
- **B4:** A reflection is only measured if everything else arriving within ±2.5 ms is at least 10 times weaker in amplitude (20 dB) in every band and in both panel states. That keeps the error below 1 dB per level. At the old 10 dB rule it could reach 3 dB, and in this small room almost no extra reflections are lost by the stricter rule.

Files read: `/home/user/makroof/docs/review/phase-04-consult/19-interrogator-05d-check.md`, `/home/user/makroof/docs/phases/phase-05d.md`, `/home/user/makroof/docs/phases/phase-05.md`, `/home/user/makroof/docs/PRD.md`, `/home/user/makroof/docs/BUILD_PLAN.md` (AX4–AX15), `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (§11.1.2, Notation), `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` (Eq. 4.6).