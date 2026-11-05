Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`).

## PRD digest (unchanged from report 5)
- **For whom:** producers and DJs who don't need to understand spatial audio (PRD "Target users").
- **Outcome:** the user describes a space and hears the track as if played there. Accuracy is gated by "measured match against real impulse responses + listening tests" (PRD metrics, "Validation").
- **Priority order:** NFR-1 accuracy first, then NFR-3/FR-SIM-6 artifact-free movement, then NFR-2 (CPU may be spent on accuracy), NFR-6, NFR-8. FR-SIM-2: no preset-specific logic.
- **Hard constraints:** NFR-8 (generic `src/sim`), AX5 determinism, AQ10 (rebuild time is recorded, not a blocker), the Phase 10 cache, the contract rules, and the PRD's out-of-scope list.
- **Verification culture:** every DSP behaviour has an automated check; independent references are preferred; goldens are never regenerated to pass; AX11 gates sit at 3σ with R ≥ (σ₁/(tol/3))².
- **PRD silent on:** what size of change in the averaged error counts as "not worse". This is a product choice (FE-01).

---

## FE-01. Margin δ and decision rule for "not higher" (D4 (B)) and "lowers" (D1 (b))

**Restatement.** Both rules compare room-averaged AQ9 errors (in jnd units) between two seed-paired arms. The interrogator showed that residual tail noise survives the pairing. A zero-margin rule therefore fails about half the time when the true difference is zero.

**Validity screen.**
- I withdraw my premise "paired, no statistical margin". I re-read Vorländer §11.2.5: it says stochastic fluctuations "can be reduced by more rays or by averaging repeated runs". Reduced, not removed.
- The zero-margin rule is CONDITIONS VIOLATED and out.
- Two valid rule forms remain:
  - (i) AX11 form: the threshold is δ, and the standard error of the estimate is ≤ δ/3.
  - (ii) Non-inferiority form: the upper confidence bound is ≤ δ. This needs SE ≤ δ/6, i.e. 4× the R, for the same false-failure rate at Δ = 0.

**Scoring.**
- Testability:
  - Form (i) follows the project convention (AX11).
  - Its error rates are symmetric. True Δ = 0 fails with P(Z > 3) = 0.135 % per comparison. A true worsening of 2δ passes with 0.135 %.
  - Form (ii) gives the same protection only at 4× the cost, so I choose (i).
- Value of δ: the corpus has no "fraction of a jnd" rule. Table 6.1 gives only the jnds (EDT 5 %, C80 1 dB, 500–1000 Hz). So δ is a product choice.
  - δ = 0.25 jnd on a room average: a quarter of the smallest audible step, averaged over bands, pairs and rooms.
  - It keeps Maisara's "not worse" intent. It still tolerates a sub-audible average shift that input-data errors can cause (Vorländer §11.5).
  - The per-room 1 jnd rule already catches an audible worsening in any single room.
  - Cost: R = 144·σ₁,Δ² (σ₁,Δ in jnd). It is cheap for plausible σ₁,Δ ≤ 0.5 jnd: R ≤ 36.
  - δ = 0.1 jnd would cost 6.25× the R and make "not worse" nearly the rejected "not higher".
- NFR-8: the rule is generic, with no room-specific terms.

**DECISION.**
- Let Δ̂_X = (room-averaged AQ9 error of metric X with the change) − (same, base), for X ∈ {EDT, C80}, on seed-paired ensembles.
- **δ = 0.25 jnd.**
- **Rule:**
  - "not worse" means Δ̂_X ≤ +δ.
  - "lowers" means Δ̂_X ≤ −δ.
  - "no room worse by more than 1 jnd" means Δ̂_room,X ≤ +1 jnd.
  - "moves by more than 1 jnd" (D1 (a)) means |Δ̂_pair,X| > 1 jnd.
  - Each is valid only if its standard error is ≤ (its threshold)/3: SE(Δ̂_X) ≤ δ/3 = 0.083 jnd, and SE(Δ̂_room,X), SE(Δ̂_pair,X) ≤ 1/3 jnd. R is sized for this (DN5).
- **False-failure rate:** 0.135 % per one-sided comparison at a true Δ on the wrong side of zero. For the (B) family of m = 2 + 2·n_rooms comparisons, about m·0.135 %. For example, 4 rooms give 10 comparisons and ≈ 1.3 %.
- The Phase 05 report prints Δ̂, SE, R and the pass/fail for each comparison.
- The wording for D1 and D4 (B) is under "Challenges".

**Confidence:** medium. The statistics are standard and follow Vorländer §11.2.5. δ is a product choice.
**Reversal condition:** Maisara picks another δ; or the Phase 05 pilot σ₁,Δ makes R impractical (more than about 2 000 per arm), and then δ goes back to her.

---

## DN5. Ensemble size R for the paired comparisons

**Restatement.** R per arm for D1 and D4 (B), in Phase 05 and in any re-run in the B11 phase.

**Validity screen.**
- Ruled out, as the interrogator found:
  - (c) a single seed: σ_Δ stays unknown;
  - (a) n ≥ 51 used as R: that is a rule for estimating σ₁, not an ensemble size;
  - (b) σ₁ of one metric: wrong quantity.
- What survives: σ₁ of the paired difference.

**Scoring.** The interrogator leans towards measuring σ₁,Δ on the AX19 runs. I keep the AX19 *method* but not those *runs*:
- The AX19 runs are the six Phase 04 test rooms, with one arm and no hybrid. σ₁,Δ needs both arms, on the BRAS pairs and with the actual handover or hybrid change.
- In Phase 05 both arms are cheap to compute on the same seeds. The hybrid adds a deterministic envelope; the handover changes t_mix,e.

**DECISION.**
- **Pilot.** Per comparison, run n ≥ 51 seeds through both arms (AX19's sampling rule: relative standard error of σ₁ ≤ 10 %). From the single-realisation metrics, take the SD of the paired difference:
  - σ₁,Δ for the room-averaged error;
  - σ₁,Δ,room per room;
  - σ₁,Δ,pair per pair (for D1 (a) only).
- **Then** R ≥ max(144·σ₁,Δ², 9·σ₁,Δ,room², 9·σ₁,Δ,pair²), with σ in jnd, rounded up. This is (σ₁/(tol/3))² with tol = δ or 1 jnd.
- Pilot seeds may count towards R.
- One R per comparison, used in both arms with the same seeds.
- After the run, check that σ₁,Δ/√R meets the bound. If it does not, increase R.

**Confidence:** medium-high (AX11 convention; Vorländer §11.2.5).
**Reversal condition:** the Phase 05 pilot values. If they are huge, δ goes back to Maisara (FE-01).

---

## FE-02. Budget in the (A) gate: tracer noise against systematic difference

**Restatement.** At k ≥ 171 the tracer's own 3σ is 0.996 dB, so the ±1 dB gate leaves nothing for real hybrid-vs-tracer differences: the 1 ms step, patch averaging, class width (Kuttruff §9.8) and detector size.

**Validity screen.**
- Keep k = 171 unchanged: CONDITIONS VIOLATED, out.
- Looser tolerance: this loosens the gate so it passes, which the rules forbid unless a stated requirement justifies it. None does.
- Wider bins (the FQ-12 precedent) do not fit here:
  - FQ-12 widened bins because the lattice count scatter was structural and could not be reduced. Tracer scatter can be reduced by raising N (Eq. 11.18).
  - In the 20×30×10 m room, t_mix,e ≈ 6.8·6000^(1/3) ≈ 124 ms. With 40 ms bins that leaves about 3 bins, before the low-k early bins are excluded, so the ≥ 3-bin rule fails.
  - Wider bins also average away the build-up of scattered energy that the gate exists to check (Kuttruff Fig. 5.3).
- What survives: a higher k.

**Scoring.**
- k ≥ 684 makes the tracer's 3σ = 3·4.34/√684 = 0.498 dB (Eqs. 11.9/11.17), which leaves an explicit **0.5 dB systematic budget** (linear sum, bias plus 3σ ≤ 1 dB).
- Expected false failures over M ≈ 15 cases × 8 bands × ~8 gated bins ≈ 960 bins. The bands are correlated, so these figures are conservative. σ = 0.166 dB.
  - True bias 0: per bin P(|Z| > 6) ≈ 2·10⁻⁹. Negligible.
  - Bias 0.25 dB: P(Z > 4.5) ≈ 3.4·10⁻⁶ per bin, ≈ 0.3 % in total.
  - Bias 0.5 dB: about 0.135 % per bin, so the gate will probably fail. That is intended, because this is the edge of the budget.
  - True bias 1 dB: fails with near certainty. The gate is not vacuous.
- It is seeded (AX5), so it is deterministic, not flaky. The seed must not be changed to pass.
- Cost: N grows 4× (DN1). That is still seconds to minutes in CI, because rays are traced only to t_mix,e (about 4 reflections at a mean free path 4V/S ≈ 10.9 m).

**DECISION.**
- **Keep ±1 dB per 10 ms bin up to t_mix,e, all 8 bands. Gate only bins with k = (ΣE)²/ΣE² ≥ 684.** Tracer 3σ = 0.50 dB; the stated systematic budget is 0.5 dB, so bias + 3σ ≤ 1 dB (AX11 convention).
- At least 3 gated bins per case. With fewer, the case **fails**; it is not skipped.
- The tracer uses energy multiplication (Kuttruff §9.8 step 3a; the Vorländer Eq. 11.14–11.18 model), so its σ follows those equations. Its seed is independent of the rendered side (FE-03).
- Engineering note, not from the corpus: time-stamp each detection at the ray's closest approach to the receiver point. That removes the ±r_d/c entry-time smear (±1.5 ms) from the systematic budget.

**Confidence:** medium. The arithmetic follows the corpus. The 0.5/0.5 split is a design choice.
**Reversal condition:** in the promotion phase, an N-doubling run shows that the per-bin difference converges to a bias above 0.3 dB. In that case, find the systematic source (time step, patches) before touching the budget.

---

## DN1. Ray-tracer particle count

**Restatement.** N for the (A) tracer.

**Validity screen.**
- (a) 10⁵ covers V ≤ about 1 600 m³ only. It fails for V = 6 000 m³, so it is out.
- (b) 10⁶ is a Kuttruff §9.8 "sufficiently precise" guideline for counters of about 1 m, not a k guarantee. At k = 684 it falls short for 6 000 m³.
- (c) survives.

**DECISION: (c), scaled to k = 684.**
- r_d = 0.5 m and Δt = 10 ms, so πr_d²cΔt = π·0.25·343·0.01 = 2.694 m³.
- Vorländer Eq. 11.12 gives N₀ = ⌈684·V / 2.694⌉ = ⌈254·V⌉. For every case here (V = 6 000 m³) that is N₀ ≈ 1.52·10⁶.
- If any case has fewer than 3 bins with k ≥ 684, double N, up to a cap of 16·N₀. If the cap is reached, the case fails (FE-02).
- N, the seed and the doubling count are logged.

**Confidence:** high for the arithmetic (Eq. 11.12); medium for the cap (an engineering bound for CI).
**Reversal condition:** the promotion-phase CI time exceeds its budget (shrink the cap or vectorise). Or k_eff at N₀ is far below Eq. 11.12, which would show strong energy-weight spread.

---

## DN2. Uniform α for the s-cases

**Restatement.** The absorption of the s = 0.1 / 0.25 / 0.4 uniform-α cases in (A).

**Validity screen.** All three options are valid (interrogator).

**Scoring.**
- With uniform α, the (1−α)ⁿ factor is shared by the specular and scattered parts (Kuttruff §5.2). A second α value therefore mostly rescales the same test.
- Uneven α is already covered by Table 5.2 layouts 4–6.
- α = 0.15 has the only corpus anchor in the mixed regime: Kuttruff §5.2, Fig. 5.3 (α = 0.15, s = 0.4, scattered share dominant from n = 2).
- Option (b) ties the values to s = 1 iteration results that do not apply at s < 1.

**DECISION.**
- α = 0.15 on all six faces and all 8 bands.
- Room 20×30×10 m (AQ10's room; the same box as DN4).
- Air absorption per AX4, on both sides.

**Confidence:** medium.
**Reversal condition:** if Phase 05's BRAS rooms have mean α far from 0.15, for example above 0.3, add that value as a second case (option (c)).

---

## Minor items

**FE-04: wording change needed.** Add to D1, D4 (B) and phase-05 scope 6, wherever the AQ9 metric is defined:
> "Vorländer Table 6.1 states these jnds for 500–1000 Hz only; at 2 kHz they are applied by extension (AQ9). The 500–1000 Hz mean is printed as the in-range figure."

**FE-05: wording change needed.** In the phase-05 X-b bound:
> "Table 5.2 layouts 2, 4, 5 and 6 are run at s = 0.1, 0.25, 0.4 and 1 on all faces (as DN3). 'Everywhere' means every case in bands 500 Hz–2 kHz; the 1 dB is G's jnd (Table 6.1, stated for 500–1000 Hz, applied by extension to 2 kHz); other bands are reported. Both E_target values are deterministic, so ΔL_b needs no statistical margin."

The last sentence comes from the plan: the AX16 list and the patch hybrid are both noise-free.

**FE-06: wording change needed.** Replace "uniform α per face set, so they isolate the hit-count residual" with:
> "the six Phase 04 test rooms (per-face α differs between faces, so their ΔL_b mixes X-b with the hit-count residual); the hit-count residual alone is isolated by also computing ΔL_b in the three uniform-α (A) s-cases (α = 0.15, 20×30×10 m), where AX16 is exact (Kuttruff §5.2)."

**FE-07: wording change needed (one clause).** Append to D2's replacement sentence:
> "Every tail's T60_b still uses Eyring, which presumes a diffuse field (Kuttruff §5.1); the size of that error is measured by the Phase 05 decay-predictor comparison (B12), not by a threshold."

---

## Summary

| id | decision (exact value/wording) | confidence | PRD basis | corpus basis | reversal condition |
|---|---|---|---|---|---|
| FE-01 | δ = 0.25 jnd. "Not worse": Δ̂ ≤ +δ. "Lowers": Δ̂ ≤ −δ. Per room ≤ +1 jnd, per pair \|Δ̂\| > 1 jnd. Each valid only with SE ≤ threshold/3 (0.135 % false failure per comparison). | medium | NFR-1, AX11 | Vorländer §11.2.5, Table 6.1, §11.5 | Maisara's δ; Phase 05 R impractical |
| DN5 | Pilot n ≥ 51 seed-paired runs per comparison (Phase 05, BRAS pairs, both arms). R ≥ max(144·σ₁,Δ², 9·σ₁,Δ,room², 9·σ₁,Δ,pair²), σ in jnd. Check σ₁,Δ/√R afterwards. | medium-high | AX11, AX19 | Vorländer §11.2.5 | Phase 05 pilot values |
| FE-02 | ±1 dB per 10 ms bin; gate bins with k ≥ 684 (tracer 3σ 0.50 dB, systematic budget 0.5 dB); ≥ 3 gated bins per case or fail; energy-multiplication tracer, independent seed. | medium | NFR-1, AX11, AX5 | Vorländer Eqs. 11.9, 11.12–11.18; Kuttruff §9.8, Fig. 5.3 | N-doubling shows bias > 0.3 dB (promotion phase) |
| DN1 | r_d = 0.5 m. N₀ = ⌈254·V⌉ (≈ 1.52·10⁶ at 6 000 m³). Double until ≥ 3 bins reach k ≥ 684; cap 16·N₀, then fail. | high / medium (cap) | NFR-1 | Vorländer Eq. 11.12; Kuttruff §9.8 | CI time; k_eff ≪ Eq. 11.12 |
| DN2 | α = 0.15 uniform, all faces and bands, 20×30×10 m, AX4 air on both sides. | medium | NFR-1 | Kuttruff §5.2, Fig. 5.3 | BRAS mean α far from 0.15 (Phase 05) |
| FE-04 | Add the "500–1000 Hz only, applied by extension" sentence. | high | AQ9 | Vorländer Table 6.1 | none |
| FE-05 | Layouts 2/4/5/6 at s = 0.1/0.25/0.4/1; "everywhere" = all cases, 500 Hz–2 kHz; deterministic, so no margin. | high | NFR-1 | Kuttruff Table 5.2; Vorländer Table 6.1 | none |
| FE-06 | Test rooms mix X-b with the residual; isolate the residual on the uniform-α s-cases. | high | NFR-1 | Kuttruff §5.2 | none |
| FE-07 | Add the Eyring-presumes-diffuseness clause to D2. | high | NFR-1 | Kuttruff §5.1 | B12 evidence |

## Challenges to settled decisions

1. **D1 (b)/(c)/(a), Phase 05 scope 6 "Mixing-time handover".** My "paired, no statistical margin" premise was false (FE-01). Proposed wording, which keeps the arbiter and the intent:
   > "…only if, on the reference-hybrid IR, all three hold, with seed-paired ensembles sized per DN5: (a) |Δ̂| > 1 jnd for EDT or C80 in at least one evaluable pair; (b) the room-averaged mean |error|/jnd falls by at least δ = 0.25 jnd for both EDT and C80 (Δ̂ ≤ −δ); (c) no room's Δ̂ exceeds +1 jnd on either. Each comparison requires SE ≤ threshold/3 (AX11)."

2. **D4 (B) (BUILD_PLAN §5 B11, phase-05 "Promotion evidence").** This keeps Maisara's "not worse". Replace "is not higher for either metric" with:
   > "is not higher by more than δ = 0.25 jnd for either metric (Δ̂ ≤ +δ), and no room's Δ̂ exceeds +1 jnd on either, each with SE ≤ threshold/3 from seed-paired ensembles sized per DN5."

   Change "k ≥ 171 (3σ ≈ 1 dB)" in (A) to "k ≥ 684 (tracer 3σ ≈ 0.5 dB, systematic budget 0.5 dB)", per FE-02.

## For Maisara
- **FE-01:** "Not worse" now means the hybrid may not raise the average error by more than a quarter of the smallest audible step, and no room may get worse by a whole step. Random noise in the simulation can't decide it on its own (about a 1-in-700 chance per comparison).
- **DN5:** Phase 05 first runs about 51 trial renders to measure how noisy the comparison is, then renders enough copies to make the noise three times smaller than the margin.
- **FE-02:** The ray-tracer check stays at ±1 dB, but the tracer must be precise enough to use only half of it. The other half is the allowed real difference between the two methods.
- **DN1:** The tracer starts with about 1.5 million particles for these rooms and doubles until the check has enough data. If it never does, the check fails, not skips.
- **DN2:** The scattering test rooms use absorption 0.15 everywhere, the value the textbook uses for its scattering illustration.
- **FE-04 to FE-07:** Wording only. Say that the "audible step" values were measured for 500–1000 Hz, name the scattering values of the textbook rooms, correct the "uniform absorption" claim, and note that the reverberation formula assumes a well-mixed room.

Files read: /home/user/makroof/docs/review/phase-04-consult/6-interrogator-expert-diff-c1b171f.md, /home/user/makroof/docs/review/phase-04-consult/5-decider-expert-questions-c1b171f.md, /home/user/makroof/docs/phases/phase-04.md, /home/user/makroof/docs/phases/phase-05.md, /home/user/makroof/docs/BUILD_PLAN.md (AQ10, AX11–AX21, B11). Corpus re-read: Vorländer §11.2.5 (Eqs. 11.7–11.21) and Table 6.1; Kuttruff §5.1, §5.2 (Fig. 5.3), Table 5.2, §9.8.