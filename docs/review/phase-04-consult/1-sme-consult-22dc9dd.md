Corpus revision: 22dc9dd59cf2f4ced36440b3b3f4cc23576e56f0 (`docs/corpus/SOURCE_COMMIT`).

# Phase 04 open items P4-D1, D2, D3, D5 and the sparse-field question: expert consultation

**Bottom line:**
- Items 1, 3, 4 and 5 are really one problem. Scattered energy is never rendered before t_mix, and AX16 makes it follow the specular path's absorption.
- The way out the corpus supports is a ray-traced, Lambert-scattering energy model for the scattered and late part (Vorländer §11.6.1). It can be added in stages without blocking Phase 04.
- For item 2, keep the fixed atmosphere and report how much the high-frequency decay depends on it.
- No change I recommend needs a contract change.

## Requirement checks (from PRD.md, BUILD_PLAN.md and the phase files, used as constraints only)

- **NFR-6 is "Persistence" in the PRD**, not offline/realtime equivalence. Equivalence lives in AQ4 (offline rebuilds run synchronously), AX5 (bit-identical on the same platform) and Phase 10 ("offline/realtime equivalence for static scenes"). I check options against those.
- **Shoebox-only is not a PRD rule.** The PRD says "any environment". The shoebox limit comes from BUILD_PLAN AQ1 and F3. B2 already plans a "new simulation core (ray/beam tracing)" for mesh rooms.
- **What users control:** room W/D/H (automatable host parameters, Phase 07), per-band α and one broadband s per surface (AQ3, AX17), and positions. Atmosphere is excluded (PRD Out of scope, AX4).
- **Other constraints used:**
  - NFR-1: accuracy first.
  - NFR-3 / FR-SIM-6: no artifacts during movement.
  - NFR-8: no scene-specific code paths.
  - AQ10: rebuild ≤ 50 ms.
  - Phase 10 cache: the unit-energy decay depends only on V, S, ᾱ_b, m_b, seed and sample rate, never on positions.
  - Phase 05: BRAS validation, with sim–measurement errors reported but not gated.

## X. Problem shared by items 1, 3, 4 and 5 (read first)

- **Scattered energy is missing from the early part.** Phase 03 renders images with energy (1−α)(1−s) per hit (phase-03 scope 1; Vorländer §3.3.2 Eq. 3.23). The scattered energy goes into a separate list that is used only to set the tail level. Before t_mix the rendered IR is specular-only; after t_mix it is specular plus scattered.
  - For one path the average level jumps by 10·log(1/Π(1−s)^hits) dB: about 2.3 dB for s = 0.1 at 5 hits, and about 11 dB for s = 0.4 at 5 hits (computed from Eq. 3.23).
  - The corpus says this energy is large early on. Kuttruff's example (Vorländer §11.6, Fig. 11.34) puts the diffuse share at about 45 % at order 2 and about ⅔ at order 3.
  - So EDT, C80 and D50 computed on the hybrid IR lack this early energy.
- **The seam gate is not built to see this.** The Schroeder curve is an integral (Vorländer §6.4.1 Eq. 6.4), so a step in the envelope changes its slope, not its value. The "no EDC step > 1 dB" gate measures something else. The listening seam check is the only guard.
- **Under AX16 the tail level does not depend on s.** Specular plus scattered equals E_noScatter for every path (AX16), so E_target is the level of an s = 0 specular ISM. AX16 also gives scattered energy every wall's (1−α) along the specular path. Scattering therefore never sends energy toward an absorbent face. That redistribution is what makes a non-uniform room more diffuse (Vorländer §11.5: Round Robins II and III found a scattering model essential).
- **Any decay or diffuseness estimate built from the current entry list is therefore a pure-specular estimate.** This rules out "fit the late ISM" in items 1 and 5. It also undercuts the "more ISM = more accurate" reasoning in item 4.

## 1. Eyring with uneven absorption (P4-D1)

**(a) Options and evidence**

- **Eyring as is (Eq. 4.32).** Vorländer §4.4.1 derives it assuming uniform absorption and a diffuse field. §4.4 says the diffuse field is a good approximation only when absorption is well distributed; concentrated absorption is not diffuse. It costs almost nothing.
  - Side note: Vorländer uses 0.16 with c = 340 m/s. The spec's 0.161 equals 24·ln10/343 = 0.1611 (Eq. 4.28), so it is consistent.
- **Millington–Sette and Kuttruff's correction:** NOT CHECKABLE. The corpus does not contain them. Kuttruff, *Room Acoustics*, would settle it.
- **Fitzroy and Arau-Puchades:** the corpus names them but gives no formulas (Toole, Box "Calculating reverberation time"). Toole also cites Dalenbäck (2000): such formulas beat Sabine and Eyring only in some cases, and no formula works universally. Their accuracy is NOT CHECKABLE (the original papers, cited there, would settle it).
- **Per-axis or directional decay:** no formula in the corpus. For flat rooms, Vorländer Table 4.1 gives only propagation curves (level against distance), not decay times.
- **Fit the decay to the late ISM energy:** rejected (see X). In a shoebox with s = 0 this is pure specular. The corpus calls pure image-source modelling too rough (§11.5, §11.6) and says scattered energy dominates after order 3–4.
- **Stochastic ray tracing with Lambert scattering** (§11.2, Eqs. 11.2–11.4): this models the scattering-driven mixing directly.
  - It can be used to estimate integral room parameters and then tune the "early reflections + exponential tail" processor (§11.2.6; §15.2.3).
  - Cost (Tables 11.3–11.5, 2 GHz PC, per band and receiver):
    - 1 dB per 10 ms bin, energy multiplication: 0.02–29 s with BSP.
    - Strength G to 1 dB, annihilation: 0.04–8.6 ms with BSP.
  - For the AQ10 room (20×30×10 m: V = 6000, S = 2200), n̄ = cS/4V = 31.4 s⁻¹ (Eq. 4.22).
  - Annihilation's error grows along the tail (Eq. 11.27), so decay curves need energy multiplication (§11.2.6 Case 1).
  - Running one trace for all bands is possible "under special circumstances" (§11.2, fn. 42). My inference that a broadband s (AX17) meets that condition is NOT CHECKABLE.
- **Full hybrid ISM + ray tracing with diffuse rain** (CAESAR/EASE, §11.6.1, Fig. 11.38) or radiosity (Eq. 10.26). The corpus says these hybrids give IRs very near measurements (§11 chapter thesis). The ray-traced envelope M²(Δt, f) plus noise fine structure (§11.7 Eq. 11.51) also reproduces curved, non-Sabine decays (§4.4.2; §15.2.3).

**(b) Fit against constraints**

- Eyring: meets NFR-8, AX5, AQ10 and the Phase 10 cache. It falls short of NFR-1 in rooms with uneven absorption.
- Ray-traced decay rate:
  - NFR-8: generic, no scene logic.
  - AX5: deterministic if seeded from tailSeed and summed in a fixed order.
  - Phase 10 cache: kept, if the trace runs only when W/D/H or materials change and gives a single T per band that does not depend on positions. A receiver-specific estimate would add positions to the cache key; which is more accurate is NOT CHECKABLE.
  - AQ10: risky, because W/D/H are automatable (Phase 07).
  - B2: reuses the ray tracer that B2 needs anyway.
- Full envelope: replaces the single exponential and the analytic ē_b, so it breaks the Phase 10 cache design and most of the Phase 04 gates. It belongs after v1 or with B2.

**(c) RECOMMENDATION (confidence: medium)**

- Keep Eyring in Phase 04. The gates are built on it and it is the textbook diffuse limit.
- In Phase 05, add a Lambert-scattering stochastic ray tracer (energy multiplication, seeded) as a second decay predictor, first as a reference in `tools/acoustics`. Report both against BRAS.
- Promote it to the per-band T60_b source only if Phase 05 shows it reduces T30/EDT error in the less uniform rooms.
- Corpus-backed: the limits of Eyring, the need for scattering, ray-tracing cost scaling.
- NOT CHECKABLE: the size of the gain in shoeboxes, the ray count needed for a T fit, the single-pass-for-all-bands claim.

**(d) What changes:** AQ2 (decay source), a new AX for the ray-trace parameters, AQ10 measurement. Phases 05, then 04 (the gate would compare against the simulator's own predicted T, plus an Eyring check where Eyring applies), 10 (cache key), 13. No contract change.

**(e) Falsifiable check:** in a shoebox with uniform α and s = 1 on every face (diffuse reflection, homogeneous absorption, the case Eyring is derived for), the ray-traced T must be within ±5 % of Eq. 4.32 at 250 Hz–4 kHz. Then in Phase 05, the mean |T30 error| over 500 Hz–2 kHz (AQ9) must be lower with the ray-traced T than with Eyring in the BRAS rooms with uneven absorption.

## 2. Fixed atmosphere (P4-D2)

**Sensitivity, computed** with Eyring plus air (Eq. 4.32, constant 0.16), ᾱ = 0.15, using Vorländer Table 11.2 rooms 2 (V = 1000 m³, S = 906 m²) and 3 (V = 10000 m³, S = 4725 m²). m comes from the Annex table "Air attenuation coefficient" at 20 °C, rows 30–50 / 50–70 / 70–90 % RH:

| room, band | m (10⁻³ /m) | T (s), 30–50 / 50–70 / 70–90 % | change vs the 50–70 % row |
|---|---|---|---|
| 1000 m³, 2 kHz | 1.9 / 1.7 / 1.7 | 1.033 / 1.039 / 1.039 | −0.5 % / 0 |
| 1000 m³, 4 kHz | 5.8 / 4.1 / 3.5 | 0.939 / 0.978 / 0.992 | −4.0 % / +1.5 % |
| 1000 m³, 8 kHz | 20.3 / 13.5 / 10.6 | 0.700 / 0.795 / 0.844 | −11.9 % / +6.1 % |
| 10000 m³, 2 kHz | as above | 1.896 / 1.914 / 1.914 | −0.9 % / 0 |
| 10000 m³, 4 kHz | as above | 1.600 / 1.717 / 1.762 | −6.8 % / +2.6 % |
| 10000 m³, 8 kHz | as above | 1.013 / 1.223 / 1.342 | −17.2 % / +9.7 % |

- Example working: 10000 m³ at 8 kHz, 30–50 % row: T = 1600 / (4725 × 0.1625 + 4 × 0.0203 × 10000) = 1600 / 1579.9 = 1.013 s.
- A cold hall (10 °C, 30–50 %, m = 29.0) gives 0.830 s at 8 kHz in the large room, −32 %.
- Table 11.2 lists T = 1.2 / 2.3 s for these rooms. That matches Sabine (Eq. 4.29: 0.16·1000 / 135.9 = 1.18 s), not Eyring.
- AX4's 50 % RH sits exactly on the boundary between two Annex rows, which differ 1.4–1.5× at 4–8 kHz. So the nominal value itself carries that uncertainty.
- The corpus does not give ISO 9613-1 values, so whether the Annex agrees with ISO 9613-1 is NOT CHECKABLE.
- The 5 % EDT jnd is stated only for 500–1000 Hz (Table 6.1), so a jnd comparison at 4–8 kHz is NOT CHECKABLE.
- Indoor humidity and temperature drift with HVAC (Begault Ch. 3, "Spectral Changes and Sound Source Distance"; humidity curves in Fig. 3.9).

**(a, b) Options and fit**

- Keep it fixed: meets everything.
- Temperature/RH as scene fields: contradicts PRD Out of scope and AX4, and needs a contract minor bump.
- Preset "venue type" setting the atmosphere: it would be scene data, not code, so NFR-8 holds. But it is hidden user-facing behaviour the PRD excludes, and it needs a contract bump too.
- A validation-only override in render_cli, like the existing `--no-air-absorption` (AX4): not exposed to users, fits NFR-8, AX5 and Phase 05.

**(c) RECOMMENDATION (confidence: high for keeping it fixed, medium for the rest)**

- Keep AX4.
- Add a per-band sensitivity bound to the Phase 05 report and to the T60 display: T at 30 % and 70 % RH, using the same ISO 9613-1 code.
- Add a render_cli atmosphere override for validation only, so Phase 05 can separate model error from atmosphere mismatch when BRAS documents its measurement conditions. Whether BRAS documents them is NOT CHECKABLE.
- Corpus-backed: the numbers above.

**(d) What changes:** AX4 (adds the validation-only override and the reported bound). Phases 04 (display), 05. No contract change.

**(e) Falsifiable check:** a unit test that T60_b at 4 and 8 kHz moves by the Eq. 4.32 prediction when m_b is swapped. In Phase 05, if conditions are known, the 4–8 kHz T30 error must shrink by about the predicted amount when the override is used.

## 3. Scattered energy at the specular time (P4-D3)

**(a) Options and evidence**

- **Leave it as is:** this is the problem in X: no early scattered energy, an envelope step at t_mix, and an E_target that ignores s.
- **Spread each AX16 entry over a causal delay kernel and render it with seeded noise** (Eq. 11.51: an envelope plus reflection density gives the fine structure). The corpus supports the qualitative shape: a specular spike followed by a short decaying train of diffuse arrivals (Fig. 11.35, CATT), with the diffuse part appearing among the early specular arrivals (Fig. 11.42), on longer, delayed paths (Fig. 3.9). The kernel's shape and length (e.g. about the mean free time 4V/(Sc), Eq. 4.23) are NOT CHECKABLE.
- **Lambert-based or diffuse-rain transfer** (Eq. 3.25, Fig. 11.38) or **radiosity** (Eq. 10.26/10.27): physically right for Lambert scattering, including redirection to other walls, which also fixes AX16's absorption inheritance. Cost: the corpus gives none for radiosity. Ray tracing cost is as in item 1.
- **Ray tracing with scattering for the mid/late part:** same as item 1.

**(b) Fit against constraints**

- Kernel plus noise: per-position and short (up to t_mix), so it is rebuilt each time while the Phase 10 cache stays intact. AX5 holds with its own seed offset. NFR-8 holds. For Phase 08, rendering it like the diffuse tail is acceptable: the corpus says the exact directional distribution of scattered sound matters little at first (§11.6).
- Effect on E_target: an energy-preserving causal kernel only moves energy toward the end of the window, where the Hann weight goes to zero. The change is second order; its size is NOT CHECKABLE.
- Effect on C80 and EDT: early energy goes up, so C80 rises and EDT shortens toward real rooms. The direction follows from Eq. 6.7; the size is NOT CHECKABLE.

**(c) RECOMMENDATION (confidence: medium)**

- Render the AX16 scattered entries in the early part as seeded noise bursts on an energy-preserving causal kernel, so that specular plus scattered energy is continuous across t_mix.
- Keep AX16's entry list for matching.
- Treat the ray-traced or diffuse-rain transfer from item 1 as the later, physically complete replacement.

**(d) What changes:** AX16 (rendered, not only reported), a new AX for the kernel. Phases 04 and 08, with Phase 05 measuring the effect. No contract change.

**(e) Falsifiable check:** on the six test rooms, the ensemble-averaged band envelope (10 ms bins) must show no step above 1 dB across [t_mix − 5 ms, t_mix + 5 ms]. This envelope gate is what the EDC gate does not test. In Phase 05, the |C80 error| against BRAS over 500 Hz–2 kHz must not get worse than with AX16 as is.

## 4. Mixing-time rule (P4-D5)

**What the corpus supports**

- **The k_eff ≥ 19 rule follows from corpus equations.**
  - Reflection density is 4πc³t²/V (Blauert §3.3, after Cremer). Referred energies fall as 1/t² (Vorländer Eq. 11.36). Together these give k_eff = (4πc³/V)(∫w)² / ∫w²/t², and with Eq. 11.9/11.17, σ = 4.34/√19 = 0.996 dB. So the rule targets an expected level precision of 1 dB, the level jnd (Table 6.1; §11.2.6 fn. 47).
  - Check of the spec's estimate: N = (4π/3)(ct)³/V = 53 gives t = 6.8·V^(1/3) ms. ✓
  - Computed: the √V-ms floor only binds once √V > 6.8·V^(1/3), i.e. V > 6.8⁶ ≈ 9.9·10⁴ m³ (t_dir → 0). At t = √V ms, N ≈ 0.17·√V.
- **What the corpus says about the transition:**
  - There is no rule (§11.7).
  - Late reverberation above 100 ms does not need deterministic resolution (§11.6.1).
  - After 140 ms the receiver-specific reverberation can be replaced by a statistical decay (§15.3, Meesawat and Hammershøi).
  - Reverberation proper begins at 50–80 ms (§6.4).
  - The 80 ms early/late split is "largely arbitrary"; synthetic early reflections usually run to about 100 ms (Begault Ch. 3 "Physical Aspects of Reverberation"; Ch. 4 "Overview of Auralization").
  - EASE/CAESAR hybrids need no transition order at all (§11.6.1).
  - The √V-ms "perceptual mixing time" is NOT CHECKABLE; the published perceptual study the phase file asks to cite would settle it.
- **What the rule is and is not.** It is an estimator-conditioning rule, not a diffuseness criterion: it uses expected Poisson counts, not realised lattice arrivals, and ignores direction. In small and mid rooms it hands over at about 20–125 ms, before the 100–140 ms the corpus calls safe for statistical replacement. But because of X, a later handover would make the IR more specular and less like a real room, not more accurate.

**(b) Fit against constraints:** meets NFR-8, AX5, AX20 cost (few images) and the Phase 10 cache.

**(c) RECOMMENDATION (confidence: medium)**

- Keep the rule for Phase 04, with the rationale restated as "1 dB expected level precision", which is corpus-derived.
- Do not lengthen t_mix until item 3 renders scattered energy.
- Then use Phase 05 to compare EDT and C80 at the rule's t_mix against a handover floored at t_dir + 80 ms and at t_dir + 140 ms. The 80 ms figure is from Vorländer §6.4 and Begault; 140 ms is from §15.3.
- Add the realised-k test from item 5.

**(d) What changes:** phase-04 scope 2 wording; AX20 cost, if the floor is raised later. Phases 04, 05, 10, 13. No contract change.

**(e) Falsifiable check:** with item 3 in place, Phase 05 BRAS |EDT| and |C80| errors at 500 Hz–2 kHz must change by less than 1 jnd (Table 6.1) between the three handover times. If they change more, the rule matters and must be chosen on that evidence.

## 5. Sparse or non-diffuse fields (Expert question in phase-04 Risks)

**(a) Options and evidence**

- **Report only (current).** Eyring does not apply (§4.4). Flat, long and coupled rooms have curved decays (§4.4.2). Artificial reverberation is not enough for "non-Sabinean" rooms (§15.2.3).
- **Realised effective count** k_real = (Σ w_i E'_i)² / Σ (w_i E'_i)² over the actual window entries, with the realised σ = 4.34/√k_real. This applies Eq. 11.9 to realised weighted counts; for deterministic lattice arrivals it is not a confidence bound (NOT CHECKABLE).
- **Directional diffuseness** ψ = 1 − ‖r_DOA‖², computed from the image directions Phase 03 already outputs (Zotter & Frank §A.6.2 Eq. A.82). It is defined for intensity; applying it to an energy-weighted image sum is NOT CHECKABLE.
- **Extend the ISM.** In a shoebox the image lattice is complete and every lattice source is audible (§11.3.3). For specular flat rooms the image-sum energy density is the analytic answer (Table 4.1). So in sparse fields the time-bounded ISM is the right specular answer and the tail is not needed. Cost grows as t³ (§11.3.3), so a cap is needed (a new AX; its value is NOT CHECKABLE). Images whose energy is exactly 0 (any hit on α = 1) can be pruned generically.
- **Cut-off without extension:** loses real specular energy, so it is not recommended.

**(b) Fit against constraints:** all options are generic (NFR-8) and deterministic (AX5). Extension raises AX20/AQ10 cost and moves t_mix (positions are already recomputed every rebuild, so the Phase 10 cache is unaffected). open_field still gives E_b = 0: k_real stays 0, t_mix reaches the cap, and every window entry is zero.

**(c) RECOMMENDATION (confidence: medium-low)**

- Make t_mix,e the smallest t at or after the scope-2 lower bound where both the expected and the realised k_eff are ≥ 19, up to a cap.
- If the cap is reached first, render ISM-only up to the cap and match the tail only if the window holds energy.
- Report k_real, the realised σ and ψ per emitter and band.
- Without item 3 (and item 1's ray tracing) the extended ISM is still specular-only, so this fixes level conditioning, not the missing scattering.

**(d) What changes:** phase-04 scope 2 and 3, a new AX for the cap and the realised-k rule, AX20, AQ10. Phases 04, 05, 10, 13. No contract change.

**(e) Falsifiable check:** a test-local scene with five α = 1 faces and a reflective floor and ceiling (a flat room, Table 4.1) must have its rendered band energy against time match the Table 4.1 specular sum within ±1 dB. open_field must keep E_b = 0.

## Summary

| item | recommendation | confidence | changes | corpus basis |
|---|---|---|---|---|
| 1 Eyring, uneven α | keep Eyring in 04; add a seeded Lambert ray-tracing decay as a Phase 05 reference; promote it to T60_b only if BRAS errors drop; reject fitting the late ISM | medium | AQ2, new AX, AQ10; phases 05, 04, 10, 13; no contract change | Vorländer §4.4, §4.4.1–4.4.2, §11.2, Tables 11.3–11.5, §11.5–11.6.1, Fig. 11.34; Toole Box (no universal formula); Millington, Kuttruff correction, Fitzroy and Arau formulas NOT CHECKABLE |
| 2 fixed atmosphere | keep AX4; report the per-band T bound at 30/70 % RH; validation-only override in render_cli | high (keep) / medium | AX4; phases 04, 05; no contract change | Eq. 4.32 + Annex air table + Table 11.2 rooms: 8 kHz −12 %/+6 % (1000 m³), −17 %/+10 % (10000 m³); 4 kHz −4 to −7 %; Begault Ch. 3 |
| 3 AX16 timing | render scattered entries before t_mix as seeded noise on an energy-preserving kernel; physical transfer (ray tracing or diffuse rain) later | medium | AX16, new AX; phases 04, 05, 08; no contract change | Eq. 3.23, Figs. 3.9, 11.34, 11.35, 11.42, Eq. 11.51; kernel shape NOT CHECKABLE |
| 4 mixing time | keep the rule (1 dB expected precision); don't lengthen until item 3 is done; compare with 80/140 ms floors in Phase 05 | medium | phase-04 scope 2; phases 04, 05 | Blauert §3.3 density; Vorländer Eqs. 11.9/11.17, Table 6.1, §6.4, §11.6.1, §11.7, §15.3; Begault Ch. 3/4; √V NOT CHECKABLE |
| 5 sparse fields | require realised k_eff ≥ 19 as well, extend the ISM up to a cap, report k_real, σ and ψ | medium-low | new AX, AX20, AQ10; phases 04, 05, 10, 13 | Vorländer §4.4, §4.4.2, Table 4.1, §11.3.3, §15.2.3; Zotter & Frank §A.6.2 Eq. A.82 |

## Questions for Maisara and the Expert, most severe first

1. Is the rendered early part (before t_mix) meant to contain no scattered energy? Under AX16 plus Phase 03 the average level steps by 10·log(1/Π(1−s)^hits) dB at t_mix (about 11 dB for s = 0.4 at 5 hits).
2. Is E_target meant to be independent of s? Under AX16, specular plus scattered = E_noScatter for every path.
3. Does the Annex air table (20 °C rows) agree with the ISO 9613-1 values AX4 uses at 4 and 8 kHz? 50 % RH falls between rows that differ about 1.5×.
4. Should t_mix,e need realised k_eff ≥ 19, not only the expected value, before the tail level is trusted?
5. If a ray-traced decay is adopted, should T60_b be room-averaged (keeping the cache position-independent) or receiver-specific?

Files: /home/user/makroof/docs/phases/phase-04.md, /home/user/makroof/docs/phases/phase-03.md, /home/user/makroof/docs/BUILD_PLAN.md, /home/user/makroof/docs/PRD.md, /home/user/makroof/docs/review/ledger.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md