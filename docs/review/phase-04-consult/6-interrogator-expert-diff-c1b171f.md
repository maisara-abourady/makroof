Science check of /tmp/claude-0/-home-user-makroof/05ae2e1f-dec9-587c-bb0d-7484bc818a46/scratchpad/fixplan-diff-expert.patch (corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d), with /home/user/makroof/docs/review/phase-04-consult/5-decider-expert-questions-c1b171f.md as the decider source. Nothing in the changed lines is WRONG. Two DECISIONS NEEDED are VERIFIED (DN3, DN4); DN1, DN2 and DN5 stay OPEN. The main finding is FE-01: with no margin, the "not worse" and "lowers" rules in (B) and D1 (b) can be decided by tail-noise scatter alone.

## 1. Part A

| DN | verdict on the options (evidence) | classification |
|---|---|---|
| DN1 particle count | **How k scales:** in the corpus model, energy-multiplication ray tracing with a constant number of rays, Vorländer Eq. 11.12 gives ⟨k⟩ = N·πr_d²cΔt/V hits per bin, so k grows linearly with N. With unequal energies, (ΣE)²/ΣE² is the Poisson-equivalent count (derived, compound Poisson). For k ≥ 171 in 10 ms bins with r_d = 0.5 m (πr_d²cΔt = 2.69 m³) you need N ≥ 63.6·V. **(a) 10⁵** covers only V ≤ ≈ 1 600 m³. **(b) 10⁶** covers V ≤ ≈ 15 700 m³, and Kuttruff §9.8's 10⁵–10⁶ is a "sufficiently precise" guideline for counters of about 1 m, not a k guarantee. **(c)** meets the gate by construction, with Eq. 11.12 as the starting N. Caveat (FE-02): at k = 171 the tracer's own 3σ already uses the whole ±1 dB. | OPEN, corpus lean (c) with N from Eq. 11.12 and a k target above 171 |
| DN2 uniform α | The corpus has no s < 1 reference for any of these values. **(a)** 0.15 matches Kuttruff Fig. 5.3 (α = 0.15, s = 0.4), but "ᾱ of the AQ10 room" is not a corpus value. **(b)** 1/6 and 3/11 tie to Table 5.2's s = 1 iteration values, which do not apply at s < 1. **(c)** gives more coverage but needs ≥ 3 gated bins in each room. All three are valid. | OPEN, lean ᾱ = 0.15 (Kuttruff Fig. 5.3) |
| DN3 s for layouts 4–6 | **(a) s = 1 only** exercises only the all-Lambert branch (Eq. 4.28), not the mixed split (Eq. 4.35 with §5.2) that B11 adds, so it is circular (C3). **(b)** tests the mixed propagation where X-b matters: uneven α, scattered energy meeting other walls (§4.6, Gilbert). **(c)** adds the s = 1 anchor to Table 5.2 and Fig. 5.10. | VERIFIED (c); (b) also acceptable; (a) rejected |
| DN4 room | Same box. Table 5.2 case 4 calls the 20×30 face the floor, so the height is 10 m, which is 20×30×10 with z up. With uniform α and no orientation-dependent physics, the two options are acoustically identical up to rotation; only the source and receiver coordinates change. | VERIFIED: either; (a) matches Table 5.2's notation |
| DN5 ensemble R | **Pairing does not remove the tail-noise variance.** The tail starts at t_mix,e, and 6.8·V^(1/3) ms is below 80 ms for V ≤ ≈ 1 600 m³. So C80's early integral contains noise, and ΔC80 = 10·log((E_e + ΔE)/E_e) depends on the realisation. EDT regresses over an EDC (Vorländer Eq. 6.4) that integrates the noise. Paired differences are correlated, not exact. **(c)** a single fixed seed leaves σ_Δ unknown. **(a)** n ≥ 51 is AX19's rule for estimating σ₁, not an ensemble size. **(b)** uses σ₁ of one metric, not of the difference, so it over-sizes R. **What R must control:** σ₁ of the paired difference Δ (hybrid − base) of the room-averaged \|error\|/jnd, per metric. Then R ≥ (σ₁,Δ/(δ/3))² for an explicit margin δ (Vorländer §11.2.5: averaging reduces stochastic fluctuations). | OPEN, lean: measure σ₁,Δ on the AX19 runs, then size R by the AX11 tol/3 rule against a stated margin δ |

## 2. Part B findings

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| FE-01 | NUMBER | (B) "not higher" and D1 (b) "lowers", both with no margin | CONDITIONS VIOLATED | The simulated metrics are ensemble estimates with residual paired noise (DN5; Vorländer §11.2.5). A zero-margin "not higher" fails about half the time when the true difference is 0. The decider's "paired, no statistical margin" holds only if both arms are noise-identical, which is not true for EDT, nor for C80 when t_mix,e < 80 ms. | major | open |
| FE-02 | NUMBER | (A) ±1 dB per bin at k ≥ 171 ("3σ ≈ 1 dB") | CONDITIONS VIOLATED | The 3σ arithmetic is right: 3·4.34/√171 = 0.996 dB. But it is the tracer's noise only, and that alone uses the full ±1 dB. Systematic hybrid-vs-tracer differences (1 ms step, patch averaging, Kuttruff §9.8 class width, §4.5) get no budget. For half the band, k ≥ 4·171 = 684. | major | open |
| FE-03 | FACT | (A) gate model: Poisson σ on (ΣE)²/ΣE² | CORRECT with a condition | Vorländer Eqs. 11.7–11.18 assume a constant ray count with independent hits. (ΣE)²/ΣE² is the compound-Poisson equivalent (derived). It needs a seeded tracer run independent of the rendered side. | none | — |
| FE-04 | NUMBER | D1 (a)–(c) and (B) "1 jnd" applied over 500 Hz–2 kHz | IMPRECISE | Vorländer Table 6.1 states the EDT 5 % and C80 1 dB jnds for 500–1000 Hz only. Using them at 2 kHz is an extrapolation; printing the 500–1000 Hz mean helps but should be stated as such. | minor | open |
| FE-05 | NUMBER | ΔL_b and its 1 dB reading | IMPRECISE | The definition is consistent: same window, both referred to t_mix,e. The 1 dB is G's jnd (Table 6.1, 500–1000 Hz) but is read over 500 Hz–2 kHz and "everywhere". The s for Table 5.2 layouts 2, 4–6 is not stated; at s = 0 the hybrid has no diffuse part. | minor | open |
| FE-06 | FACT | "uniform α per face set, so they isolate the hit-count residual" | IMPRECISE | Per-face α that differs between faces is not uniform α. AX16 is exact only for uniform α (Kuttruff §5.2), so rooms with different α per face mix X-b with the hit-count residual. | minor | open |
| FE-07 | CONSEQUENCE (D2) | "no code path or gate needs a diffuseness threshold" | — | True for branching: AX22 uses k_real, a precision criterion, and Kuttruff §8.5 gives no threshold. But every tail uses Eyring, which presumes a diffuse field (Kuttruff §5 intro, §5.1). Table 5.2 shows deviations of −12 % to +29 % when it is not diffuse. | minor | open |

The rest of Part B is CORRECT:
- No transition-time rule exists (Vorländer §11.7).
- Kuttruff §8.5 calls diffuseness an "open question" and gives no threshold.
- Round robins found a scattering model essential (Vorländer §11.5).
- Per-axis shares are a necessary condition only (§8.5, Eqs. 5.1–5.2).
- The `open_field` Lambert estimate (−23 to −43 dB) is unchanged.

## 3. WRONG items

None. FE-01 and FE-02 are the major findings, and both sit on promotion gates.