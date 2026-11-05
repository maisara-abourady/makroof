Decider report 11: DN-1, FR-01 to FR-05, and the researcher findings F1–F21

Corpus: `docs/corpus/` at c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I made no file edits. Inputs: `/home/user/makroof/docs/review/phase-04-consult/10-interrogator-r8-diff.md`, `/home/user/makroof/docs/review/phase-04-consult/9-researcher-measurements.md`, `/home/user/makroof/docs/phases/phase-05.md`, `phase-05b.md`, `phase-10.md`, `phase-04.md`, and `/home/user/makroof/docs/BUILD_PLAN.md`.

## PRD digest
- **For whom:** producers and DJs. They are assumed to know nothing about spatial audio; they describe a space and the plugin does the acoustics (PRD "Target users").
- **Outcome:** the user hears the space they built. Accuracy is a quality gate, checked by a "measured match against real impulse responses + listening tests" (metrics table, Validation decision, NFR-1).
- **Priority order:** NFR-1 accuracy, then NFR-2 (heavy CPU is acceptable but the plugin must stay usable), then NFR-3 and FR-SIM-6 (smooth movement), then NFR-8 and FR-SIM-2 (generic engine), then NFR-6 and NFR-7.
- **Hard constraints:** AQ10 rebuild ≤ 50 ms (a target; misses are recorded, and the output is never cut to meet it); AX5 determinism; NFR-8 (no scene logic in `src/sim`); NFR-3 / AX18 (the equal-gain premise needs correlated consecutive IRs); the Phase 10 tail cache (only the unit decay is cached); the contract rules; out of scope: user atmosphere, multichannel output, head tracking.
- **Verification culture:** every DSP behaviour has an automated check; independent references are preferred over our own goldens; goldens are never regenerated to make a test pass; stochastic gates use AX11 (3σ, R = (σ₁/(tol/3))²).
- **PRD is silent on:** which reference IRs to use (Q9 is open). It does not say BRAS is enough.

---

## DN-1: how the early diffuse energy is rendered in `src/sim`, plus patches and time step

**Restatement.** Phase 05b scope 1 must decide three things: how the gathered Lambert energy (Kuttruff Eq. 4.29) becomes IR samples, the patch layout, and the time step. These drive gate (A), Phase 08's directions, Phase 10 continuity and the AQ10 W1 time.

**Validity screen.**
- Rendering (c), the envelope only, is out. Vorländer §15.2 says the fine structure "must be created in post-processing".
- Patches (a), converging per scene, are out: the cost is unbounded and the layout can jump.
- Rendering (a), (b), patches (b) and patches (c) remain.

**A defect the options miss.** Eq. 11.51 needs the density n_j per interval Δt to match the actual reflection statistics. The diffuse-field density is 4πc³t²/V (Blauert Ch. 3 §3.3, Cremer; Kuttruff §4.2), and Vorländer §15.2 says the density "increases with t²". Option (b), with one burst per patch per 1 ms step, gives a density of N_p/Δt. With 88 to 2 000 patches that is 0.09 to 2·10⁶ s⁻¹. At t_mix in the 6 000 m³ room the target is ≈ 1 300 s⁻¹ (4π·343³·0.124²/6000). So (b) is as wrong on density as (a).

(b) has two further problems:
- Its seeds are tied to the patch index, so any change in the patch layout (a room-size sweep crossing a patch boundary) re-seeds every patch. That breaks AX18's equal-gain premise.
- Its cost grows with patches × bands.

(a) has no directions for Phase 08. Each option fixes the other's flaw, so I chose a minimal variant that keeps the strong part of each.

**DECISION (rendering, variant (d)): equivalent-reflection pulses under the gathered envelope.** Wording for 05b scope 1:
> Per emitter and per 1 ms step k on the emission time axis, the gathered diffuse energy E_k,b (all patches, Eq. 4.29, each with its own delay R′/c) is rendered as n_k = max(1, ⌈ν(t_k)·Δt⌉) pulses, ν(t) = 4πc³t²/V (Vorländer Eq. 11.51 with Δt = 1 ms; Kuttruff §9.8 class width). Pulse offsets within the step and signs come from a counter-based RNG keyed by (tailSeed, emitter, step, pulse), independent of positions and patch layout (AX5). Each pulse is a broadband equivalent reflection with per-band amplitude √(E_k,b/n_k), rendered through the Phase 03 filterbank path like an image source, so per-band energy per step equals the envelope exactly. Per step, the per-patch contributions are kept so that Phase 08 can assign directions (Kuttruff §4.5; Vorländer Fig. 15.5); how it does so is Phase 08's decision. Diffuse pulses inside the ISM→tail crossfade take the ISM window (AX18).

Added automated checks, all deterministic:
- (i) Rendered tap energy per step and band equals E_k,b within 1e-9 relative.
- (ii) Continuity: per band from 500 Hz to 2 kHz, the normalised cross-energy of the diffuse parts is ≥ 0.79 for a 1.5 cm source move and for a 1 cm room-dimension change that crosses a patch boundary. At 0.79 the equal-gain mid-fade dip of that part alone is ≤ 10·log10((1+0.79)/2) = 1 dB, the Phase 10 bound. The 1.5 cm is 50 cm/s (Vorländer §15.3) × 30 ms (AQ4).

Why this scores best:
- **NFR-1:** energy is exact at 1 ms, and the density is Eq. 11.51's.
- **NFR-3:** amplitudes vary smoothly, and the fine structure never re-seeds on position or layout changes.
- **Cost:** about 120 pulses per emitter in the AQ10 room, against patches × bands for (b).
- **Phase 08:** directions are kept.

The density floor of one pulse per step is above ν(t) only while ν·Δt < 1. That is t < √(V/(4πc³Δt)): ≈ 109 ms at 6 000 m³ and ≈ 17 ms at 145 m³, which is the sparse part. This is the smallest departure that keeps Eq. 11.51's 1 ms envelope. The corpus does not give the true early density of scattered sound, so this part has the lowest confidence.

**DECISION (patches and step): patches (b), frozen, defined as one absolute edge length ℓ in metres.**
- Each face is split into ⌈L/ℓ⌉ equal strips per edge. ℓ is a constant in `src/sim`, changed only as an intended output change, like N_cap.
- The time step Δt is 1 ms, also frozen.
- ℓ is set in a new 05b "scope 0", before any gate result is seen. It is the coarsest ℓ at which, in every selected BRAS room and every (A) case, halving ℓ changes all of these by < 1 %: a*, the window energy E_target per band from 500 Hz to 2 kHz, and each bin that (A) gates.
- Halving stops at ℓ = c·Δt = 0.343 m, because a finer patch is not resolved by the 1 ms step. If that floor is reached, the residual is recorded.
- It must be absolute, not relative to room size: with a relative split, a 100 m room's patches would smear delays by tens of ms.
- I chose it over (c) because (c) lets CPU decide accuracy.
- The Table 15.1 option (the scattering part updated every 3 s or 1 m) is not adopted. If W1 with the diffuse part goes above 700 ms, it is the first remedy Phase 10 may propose as an AX. A coarser ℓ is not a remedy.

**Confidence:** medium for the rendering principle, the patches and the step (Vorländer Eq. 11.51, §15.2 and Fig. 15.5; Kuttruff §4.5 and §9.8; PRD NFR-1 and NFR-3). Low for the density floor. Variant (d) is new acoustic wording, so it needs an interrogator check before the plan-editor applies it.

**Reversal condition (Phase 05b):**
- Maisara's 05b listening item "no new graininess" fails.
- Gate (A) fails only in early bins where the floor applies.
- Phase 08 finds that per-step direction data is not enough. Then it moves to the Fig. 15.5 directional groups (an AX).

---

## FR-01: how the Phase 10 switch-point dip gate is stated and measured

**Restatement.** The ≤ 1 dB gate stays, as Maisara decided. What is missing is the window, the worst-case formula and the bound.

**Derivation** (Vorländer Eq. 4.14 and §1.7: the cross term vanishes for incoherent signals).
- Take a linear ramp g, segment powers P₁ and P₂, ρ = P₂/P₁ ≥ 1, and the power-linear reference.
- The segment's ratio to the reference is r(g) = ((1−g)²P₁ + g²P₂)/((1−g)P₁ + gP₂).
- Setting dr/dg = 0 gives (ρ−1)g² + 2g − 1 = 0, so g* = 1/(1+√ρ).
- The minimum is r_min = 2√ρ/(1+√ρ)². Check: ρ = 1 gives 0.5; ρ = 10 gives g* = 0.240 and r_min = 0.365, which matches the interrogator.
- The total dip is 10·log10(1 − f·(1+ρ)/(1+√ρ)²).
- The gate holds when f ≤ 0.2057·(1+√ρ)²/(1+ρ): f ≤ 0.411 at ρ = 1, f ≤ 0.324 at ρ = 10, and f ≤ 0.206 for any ρ.

**DECISION.** Replace "Total dip = 10·log10(1 − 0.5·f) … f ≤ 0.41" in phase-10, AX22, phase-04 Risks and §4 Phase 04 with:
> Measured per output channel and octave band (500 Hz, 1 kHz, 2 kHz; AX14 rule if adjacent bands differ > 15 dB) as the expected instantaneous output power for a stationary input, computed from the two IRs: P(g) = (1−g)²E₁ + g²E₂ + 2g(1−g)C₁₂ (E full-IR band energies, C₁₂ their band cross-energy), against R(g) = (1−g)E₁ + gE₂, at every sample of the 30 ms ramp (instantaneous, no averaging window; valid because Phase 06 gates the crossfade to the analytic one within −100 dB). Gate: max_g of −10·log10(P/R) ≤ 1 dB. Reported: the dip at each g, the fade-averaged dip, ρ, f (the segment's share of R(g*)), and the predicted worst case 10·log10(1 − f(1+ρ)/(1+√ρ)²) at g* = 1/(1+√ρ). The predicted worst case is ≤ 1 dB when f ≤ 0.2057(1+√ρ)²/(1+ρ): 0.41 at ρ = 1, 0.32 at ρ = 10, 0.21 for any ρ. Instrument self-test: two independent seeded noise IRs at ρ = 10, f = 1 give 4.37 ± 0.1 dB at g = 0.24 ± 0.01. With a transient input the segment's own dip (up to 4.4 dB at 10:1) is reported, not gated.

**Testability.** The gate is computed directly from the IRs, so it is not flaky. The self-test stops it from being vacuous.

**Confidence:** high for the maths (Eq. 4.14 and the derivation). The "instantaneous" window is conservative.

**Reversal condition (Phase 10):** a corpus source on temporal integration for short level dips would justify a fade-averaged window.

---

## FR-02 to FR-05 (wording)

**FR-02 (AQ10 rationale).** Replace the last sentence with:
> A miss does not create clicks (every update still crossfades, AQ4); it lowers the update rate. That stays within Vorländer Table 15.1's proposal (700 ms for moves > 0.25 m: specular part; 3 s for moves > 1 m: specular and scattering part) only while the measured W1/W2 rebuild is ≤ 700 ms; a longer rebuild exceeds it and §0 says so. Table 15.1 would let the phase-05b scattering part update on the 3 s / 1 m interval; that is a Phase 10 cache option, adopted only through an AX.

Confidence high (Table 15.1, re-read).

**FR-03 (B12).** Replace "(deterministic, so no seed noise)" with:
> (deterministic, so no seed noise, but not error-free: a* is converged to < 1 % per patch halving and the γ² choice moves γ²-Eyring by ≈ 0.4–3.6 % (Kuttruff Eqs. 5.33–5.34), both the size of the 1.25-point margin)

Add these conditions:
- (i) A predictor counts as lowering the error only if it does so with a* converged to < 0.4 % per halving (margin/3, by analogy with AX11).
- (ii) A predictor with a free modelling input (γ²) must meet the rule at every admissible value: the Table 5.1 row and 0.4.
- (iii) The 5 % T jnd is a working value from outside the corpus. Vorländer Table 6.1 gives 5 % for EDT, not for T.
- (iv) Only the initial-estimate α set counts. See F6 below.

Confidence medium.

**FR-04 (05b ΔL_b,tr switch).** Add:
> The switch is valid only with SE(ΔL_b,tr) = 4.34/√k_tr ≤ 1/3 dB (threshold/3, AX11); k ≥ 684 gives ≤ 0.17 dB. Realised k and SE are printed. The tracer seed is fixed, so the decision reproduces on re-run. Near 1 dB either branch leaves the level error within about 1 dB + 3·SE.

Whether the trigger should use the absolute value is under "Challenges" (C1). Confidence high (Vorländer Eqs. 11.15–11.18).

**FR-05 (scale note in AX22).** Replace "Phase 03's rate suggests i₀ ≈ 13–15" with:
> Phase 03's rate (4.5–6.9 µs per image) puts the 25 ms per-emitter budget at ≈ 3 600–5 500 images, so the largest i₀ within budget is expected to be 13–15 (ν_r(13) = 3 302, ν_r(14) = 4 088, ν_r(15) = 4 990, ν_r(16) = 6 016; Kuttruff Eq. 9.23), assuming rebuild time ∝ image count (engineering assumption, not corpus).

Checked: 3 623 lies between ν_r(13) and ν_r(14), and 5 556 between ν_r(15) and ν_r(16). Confidence high.

---

## Researcher findings

**F1–F3 (BRAS has CR1–CR4 only; CR1 is coupled; the CRs "cannot serve as a direct reference"; α and s are estimated; every CR RIR carries a 6 dB level correction).**

- **Phase 05 claim and AQ9 wording.** Keep comparing: BRAS is the only measured data we have. Change the claim:
  - In the AQ9 measured row, add: "BRAS CR rooms (CR1 excluded as coupled, F3) with the dataset's estimated α and s (F6, F7); the dataset authors state the CRs 'cannot serve as a direct reference' (F2), so these errors measure method plus input data, not a validation of NFR-1."
  - In the §1 BRAS row, replace "exactly what NFR-1 needs" with "the only open dataset with geometry, (estimated) materials and measured IRs together; see F2".
  - In the Phase 05 report, put the RR19 round-robin errors for the same rooms and input set next to ours, where published, as context. This is the use the authors endorse (F2: comparing simulations on identical input).
- **"AQ9 met in x/y".** Report x/y per room (the room mean over pairs) and per pair, and give the α set for each. RR19 found per-position structure mostly not reproduced (F13), so a per-pair pass/fail mostly reflects noise in the position-specific details. On the fitted set, T30 is circular: the fitted α were scaled so that Eyring matches the measured T (F6). Label it that way.
- **B11 (B).** No rule change. Both arms share the same estimated input, so (B) stays valid as a "not worse" safety check. Add one line: "(B) is a safety check on estimated input data (F2, F6, F7), not a validation; n_rooms ≤ 3, so m ≤ 8 comparisons, false-failure ≈ 1.1 %."
- **B12.** Use the initial-estimate set only. The fitted set is circular in Eyring's favour by construction (F6), so it is reported only. See also C2.
- **G and level.** No G errors from the BRAS CRs: "G not evaluable: levels manually corrected by 6 dB (F3)". T30, EDT and C80 do not depend on absolute level, so they are unaffected. Position-to-position level differences inside a room may be shown for information, but only if the documentation confirms that the correction is uniform.
- **PRD Q9 and a second source.** Needed for the PRD outcome. Three rooms (145 / 2 350 / 8 650 m³) with estimated inputs cover none of the domestic, car-sized, club or warehouse presets (FR-3D-3) and cannot support "measured match" in general. The target is measured RIRs with geometry and in-situ measured α, and s where possible, that are shoebox-like, include small rooms under 100 m³, and have a licence that allows commercial use.
  - **Owner:** Maisara decides, since Q9 is her decision to accept. The researcher agent searches. RR-III (the PTB studio, F14) is a lead, not a fact.
  - **Timing:** it does not block Phase 05, but it is needed before Phase 13's beta decision. If none is found, the beta decision says so.

**F7 (BRAS s rises as √f).** The B10 trigger and priority stay the same. Update the phase-05 report line: for unclamped BRAS materials the AX17 mean is (1 + √2 + 2)/3 = 1.471 × s(500). That overstates s by +47 % at 500 Hz and +4 % at 1 kHz, and understates it by −26 % at 2 kHz, whatever d_char is. Every material is affected, so the per-band-s run always tests something real. The prior from F15 (the full s swing moved EDT and C80 by ≈ 0.6 jnd) suggests the change will stay below δ at low s. That is a lead, not a reason to change the trigger.

**F13 (mature hybrids missed T by 58 % / 35 % at 125 / 250 Hz and stayed above 1 jnd at 500 Hz–2 kHz).** Add to phase-05 Risks:
> On BRAS initial data, blind mature hybrids stayed above 1 jnd at 500 Hz–2 kHz in most cases, driven by the input data (RR19); the corpus reports 1–2 jnd achievable with carefully chosen coefficients (Vorländer §11.5, RR-III). An AQ9 miss on initial data is therefore expected and is read against the RR19 spread before it is escalated.

No threshold changes.

**F20 (Lindau et al. 2012 perceptual mixing time).**
- **Citation.** The phase-04 comment should cite: "√V ms, the popular estimate attributed to Cremer & Müller (1978), reported in Lindau, Kosanke & Weinzierl 2012, JAES 60(11), §1.1 (F20); their Eq. 1 at 400 s⁻¹ gives 0.89·√V ms."
- **t_mp95 as a floor: no.** Worked comparison:

| V (m³) | t_mp95 (ms) | Phase 04 k_eff rule (ms) | already covered? |
|---|---|---|---|
| 145 | 51.8 | ≈ 36 | yes, the 80 ms floor is above it |
| 6 000 | 120 | ≈ 124 | yes |
| 8 650 | 151 | ≈ 140 | not by the 140 ms floor, but it is only 11 ms above it |

  A separate t_mp95 arm would add ensembles for almost no information.
- **Instead:** report t_mp50 and t_mp95 per room next to t_mix,e in Phase 05, as context (scope: binaural, near-shoebox rooms, V up to about 10 000 m³).
- **k_eff rule:** no challenge. The rule is above t_mp50 for these BRAS rooms, so the √V lower bound rarely binds.

**F21 (ISO 9613-1 and Bass 1995).** The plan makes no such claim. I searched `docs/` (outside the corpus), `src/`, `tools/` and `tests/`. Phase-04 line 56 says "Kuttruff Table 6.1 (Bass 1995)", which is right: Kuttruff's caption says the table is "adapted from Bass et al., J Acoust Soc Am 1995". No change needed. An optional clarification: "(Kuttruff's caption: adapted from Bass et al. 1995)".

**Corpus candidates to ask Maisara for, in priority order:**
1. BRAS Documentation.pdf (CC BY-SA 4.0). Phase 05 depends on it.
2. Brinkmann et al. 2019, JASA round robin (CC BY 4.0). It gives the AQ9 priors and the comparison use the authors endorse.
3. Witew 2022 (open access; licence to confirm). It would settle the measurement-uncertainty leads (F19, R2).
4. Lindau et al. 2012. In copyright, so only with permission.

Do not add the Brinkmann 2021 AAM: its NC-ND licence conflicts with a condensed copy for a commercial project. Stephenson 2012 and Shtrepi 2011/2015 are of low value. ISO 3382-1/-2 would settle many "to verify" items, but it is a paid standard: buy it for the engineer, don't put it in the corpus.

---

## Summary

| id | decision | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| DN-1 rendering | Variant (d): seeded equivalent-reflection pulses, n_k = max(1, ⌈4πc³t²/V·1 ms⌉) per 1 ms step, energy exact per step, times independent of position and layout, per-patch contributions kept for 08; continuity check (cross-energy ≥ 0.79) | medium (floor: low) | NFR-1, NFR-3, NFR-8, AX5 | Vorländer Eq. 11.51, §15.2, Fig. 15.5; Kuttruff §4.5, §9.8 | 05b graininess listening item, (A) failing only in early bins, Phase 08 needs |
| DN-1 patches/step | Frozen absolute ℓ: coarsest at which halving changes a*, E_target and the (A)-gated bins by < 1 %; floor c·Δt = 0.343 m; Δt = 1 ms; set in 05b scope 0 before the gates | medium | NFR-1 over NFR-2, NFR-3 | Kuttruff §9.8, §5.7 | 05b convergence or W1 > 700 ms leads to a Table 15.1 cache AX in Phase 10 |
| FR-01 | Expected instantaneous power from the IRs at every ramp sample; gate max dip ≤ 1 dB; worst case 10·log10(1 − f(1+ρ)/(1+√ρ)²); f ≤ 0.41 / 0.32 / 0.21; self-test 4.37 dB at ρ = 10 | high | NFR-3, FR-SIM-6 | Vorländer Eq. 4.14, §1.7, Table 6.1 | a corpus source on temporal integration of short dips (Phase 10) |
| FR-02 | AQ10: "within Table 15.1 only while rebuild ≤ 700 ms; 3 s / 1 m for the scattering part is an AX-only cache option" | high | NFR-2, NFR-3 | Vorländer Table 15.1 | measured W1/W2 (04, 05b) |
| FR-03 | B12: "deterministic, not error-free"; a* converged < 0.4 %; must hold at every admissible γ²; T jnd is a working value; initial α set only | medium | NFR-1, NFR-8 | Kuttruff Eqs. 5.33–5.34; Vorländer Table 6.1 | Phase 05 convergence data |
| FR-04 | Switch valid only with SE = 4.34/√k ≤ 1/3 dB (met at k ≥ 684); k and SE printed | high | NFR-1 | Vorländer Eqs. 11.15–11.18 | — |
| FR-05 | "Expected i₀ = 13–15 from 3 600–5 500 images; ν_r values; ∝ assumption" | high | AQ10 | Kuttruff Eq. 9.23 | Phase 04 benchmark |
| F1–F3 | Reword AQ9 / §1 / Phase 05 claim; x/y per room and per pair, by α set; RR19 context; G not evaluable; (B) and B12 caveats; second measured source needed, Maisara decides, researcher searches, before the Phase 13 beta | high | NFR-1, Q9, FR-3D-3 | Vorländer §11.5 | a second source found |
| F7 | B10 trigger and priority unchanged; report the +47 / +4 / −26 % AX17 error | medium | NFR-1 | — (F7) | Phase 05 per-band-s run |
| F13 | Expectation added to Risks; misses read against the RR19 spread | high | NFR-1 | Vorländer §11.5 | Phase 05 results |
| F20 | Cite LKW12 in phase-04; report t_mp50/t_mp95 per room; no new floor arm | high | NFR-1 | Blauert Ch. 3 §3.3 (density) | Phase 05 handover evidence |
| F21 | No change; the plan makes no such claim | high | — | Kuttruff Table 6.1 caption | — |

## Challenges to settled decisions

- **C1. The ΔL_b,tr trigger should use the absolute value.** B11 (i)/(iii) and 05b scope 4 say "ΔL_b,tr > 1 dB", which is signed. Phase-05 scope 6 uses |ΔL_b| > 1 dB, and AX16 says the bias "has a case-dependent sign". With the signed trigger, a case where AX16 underestimates the level by 2 dB would never switch. Proposal: |ΔL_b,tr| > 1 dB.
- **C2. B12 on BRAS alone is input-limited evidence.** With at most 3 rooms and estimated α (F2, F6), a predictor can "win" by offsetting a bias in the input absorption. RR19 found blind simulations closer to the Eyring estimate from the supplied data than to measurement (F13). Proposal: an outcome from BRAS alone is labelled "input-limited" in the AQ2 change request, and Maisara decides on that label. I am not proposing a new threshold.

## For Maisara
- **DN-1 rendering:** render the early scattered sound as a sparse, seeded set of "virtual reflections" whose energy follows the computed envelope exactly. It moves smoothly when sources move, and it keeps directions for headphones (Phase 08).
- **DN-1 patches:** one fixed patch size for every room, measured once in Phase 05b before any test result is seen. CPU never decides accuracy.
- **FR-01:** the 1 dB dip gate stays. It is now computed exactly from the two IRs at every point of the fade. The safe share is 41 % at equal powers, 32 % at 10:1, and 21 % at any ratio.
- **FR-02:** the "within Table 15.1" comfort only holds while a rebuild takes ≤ 700 ms. The slower 3 s update for scattering stays an option, not a plan.
- **FR-03:** B12 predictions are repeatable but not exact. A predictor must win by more than its own convergence error and for every reasonable γ².
- **FR-04:** the tail-level switch is valid only when the tracer's noise is under a third of the 1 dB threshold. That is already true at the planned ray counts.
- **FR-05:** the 13–15 is an expected range, not an exact value.
- **BRAS:** we can test against at most 3 rooms, with estimated materials, and the dataset's authors say not to treat them as ground truth. Phase 05 results will be called "evidence", not "validation". A second measured dataset is needed before the beta, and you decide which one.
- **F7:** BRAS scattering rises with frequency, so our single-value scattering is off by +47 % / −26 % at 500 Hz / 2 kHz. The existing B10 check covers this, and nothing changes.
- **F13:** even leading commercial tools miss by 1 jnd or more on this data. Expect misses, and compare them with those tools.
- **F20:** the mixing-time comment gets a real citation, and the perceptual values are shown per room. The rule itself does not change.
- **F21:** nothing to fix.
- **Corpus:** ask to add the BRAS documentation, the 2019 round robin and Witew 2022 (licence to confirm).
- **Before applying:** the plan-editor should send DN-1's variant (d), the FR-01 formula and the B12 "initial α set only" to the interrogator first.