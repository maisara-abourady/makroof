## Researcher dossier RQ-H3-1 — reference uncertainty in per-item and pooled bias tests (D-H3 (a))

Accessed 2026-11-10. Corpus c1b171f. "Read" = text retrieved and read by me; "tool summary" = retrieved, summarised by the fetch tool; "unverified" = abstract/TOC/citation only.

### 1. Decision served
D-H3 (a), rows K-a2 (corrected), K-a5, K-a6; Seat 2/Seat 9 questions on ℓ_ref's nature and round-robin pooling; decider premise "(a) is the form of a metrological E_n score".

### 2. Findings

| id | question | finding | reference | location | status | conf. | changes |
|---|---|---|---|---|---|---|---|
| F1 | per-item score with reference uncertainty | ζ = (x−x_pt)/√(u(x)²+u(x_pt)²) (standard uncertainties); E_n same with expanded U (≈95 %); z′ = (x−x_pt)/√(σ_pt²+u(x_pt)²), used when u(x_pt) > 0.3 σ_pt | Eurachem PT WG, *Understanding PT performance assessment*, leaflet, 1st Engl. ed. May 2024, https://eurachem.org/images/stories/leaflets/pt/pt_perf_assmnt/PT_Understand_Evaluation_V1_EN.pdf; NIST Dataplot "EN SCORE", https://itl.nist.gov/div898/software/dataplot/refman2/auxillar/enscore.htm | leaflet p. 2 Table 1 (cites ISO 13528:2022 §9.4.2); NIST page (cites ISO 13528:2005 pp. 27–28) | read | high | Option (a)'s per-item form is the ζ-score form, provided ℓ_ref is a *standard uncertainty* (see F5–F6) |
| F2 | ISO 13528 structure | 2015 ed.: 7.2 uncertainty of assigned value; 9.2 "Limiting the uncertainty of the assigned value"; 9.4–9.7 z, z′, ζ, E_n; 9.9 "Combined performance scores"; 10.8 combining over rounds (graphical) | ISO 13528:2015 TOC (DIN), https://www.din.de/de/mitwirken/normenausschuesse/naw/wdc-beuth:din21:240487596/toc-2349403/download | pp. 1–2 | read (TOC only; clause text unverified) | medium | Pooled scores exist in the standard (9.9) but their text was not retrievable |
| F3 | AX43's pooled form | AX43's \|mean z\| ≤ 3/√M ≡ \|Σz/√M\| ≤ 3, the "rescaled sum" RSZ; NIST: same interpretation as z, "but large z-scores of opposite sign can cancel" | NIST Dataplot "RESCALED SUM", https://itl.nist.gov/div898/software/dataplot/refman2/auxillar/rescasum.htm | whole page | read | medium | (c) keeps a recognised form; its known weakness is masking, not over-sensitivity |
| F4 | bias against a certified value | Δ = \|c_m − c_CRM\|; u_Δ = √(u_m²+u_CRM²); U_Δ = 2u_Δ; no significant difference if Δ ≤ U_Δ | Linsinger T. (2010) *ERM Application Note 1*, EC-JRC IRMM, https://crm.jrc.ec.europa.eu/sites/default/files/2025-02/application_notes/ERM%20application%20note%201_english_rev3.pdf | p. 1 "Basic principles" | read | high | Quadrature of reference and measurement *standard* uncertainties is standard for one item vs one reference |
| F5 | is a bound a 1-σ term? | A quantity known only within ±a: rectangular, u = a/√3 (normal 99.73 %: a/3; triangular a/√6). Recognised systematic effects are *corrected*, and the correction's uncertainty is the component (3.2.3–3.2.4) | JCGM 100:2008 (GUM), https://www.bipm.org/documents/20126/2071204/JCGM_100_2008_E.pdf | 3.2.3, 3.2.4 + Note 1, 4.4.5/Eq. (7), F.2.3.3 | read | high | Option (a) enters raw ℓ_ref as 1-σ; GUM gives ℓ/√3 if ℓ is a bound, or a *correction* if its sign is known. AX43's per-case rule (τ − ℓ_ref) treats ℓ_ref as a linear bound: (a) and the per-case rule are not the same reading |
| F6 | discretisation residual → uncertainty (simulation V&V) | E = D − S (Eq. 5); U_V² = U_D² + U_SN² (Eq. 6); δ*_RE = ε_21/(r^p − 1) (Eq. 11); U = F_S\|δ*_RE\|, F_S = 1.25 careful 3-grid study, **3 with two grids / assumed order** (§4.4, Eq. 23); numerical error treated "stochastic" → U_SN, or "deterministic" → corrected, with caution on three grids (§5.1–5.2) | ITTC Rec. Proc. 7.5-03-01-01 Rev. 03 (2017), https://www.ittc.info/media/8153/75-03-01-01.pdf; Stern, Wilson, Coleman, Paterson (2001) J. Fluids Eng. 123(4) 793–802, DOI 10.1115/1.1412235 | ITTC pp. 4–5, 8, 11–12; Stern abstract | ITTC read; Stern abstract only | high | A last-halving change is the input to an *expanded* band with a safety factor, not a 1-σ; with only two rungs (BRAS r1) the convention is F_S = 3. Neither (a) nor AX43's per-case rule carries F_S |
| F7 | GCI form | CI centred on the fine-grid value, U = F_s\|f(h₁)−f(h₂)\|/(r^p−1); "confidence" in a "casual, non-statistical" sense; GCI bands, it does "not actually extrapolate" | Bect, Zio, Perrin, Cannamela, Vazquez (2021) WCCM-ECCOMAS 2020, arXiv:2103.14559, https://arxiv.org/pdf/2103.14559 | §2.1 Eqs (4)–(6) | read | medium | Same as F6; the sign is normally *not* used unless one corrects |
| F8 | items sharing one reference, pooled | Correlated inputs: Eq. (13)/(16); with r = +1 the uncertainties add *linearly*; example: ten resistors calibrated against one standard give u = 10×u(R_s), "not √10"; same reference standard ⇒ correlation (5.2.4; F.1.2.3 Note: r = +1 in comparison calibrations); a shared offset's variance does not fall with n (Eq. E.6, E.3.5) | GUM, as F5 | 5.2.2 Note 1 + Example, 5.2.4, E.3.4–E.3.6, F.1.2.3 Note | read | high | Confirms K-a6 in form: for a *shared* reference error ℓ_s, u²(mean) = SE²/M + ℓ_s²; option (a) with 3/√M gives (SE²+ℓ²)/M and still understates a shared part. Grouping ((b)/(e)) or a covariance term is the GUM way to carry it |
| F9 | key-comparison practice | Weighted mean, χ²_obs = Σ(x_i−y)²/u²(x_i), ν = N−1, fail at Pr < 0.05; d_i = x_i − x_ref, u²(d_i) = u²(x_i) − u²(x_ref) "as a consequence of the mutual dependence"; procedure valid only if measurements are "realised independently"; mutually dependent measurements need "appropriate modification" | Bich, Cox, Estler, Nielsen, Wöger (2002) *Proposed guidelines for the evaluation of key comparison data*, BIPM Advisory Group, CCAUV/02-36, https://bipm.org/documents/20126/28426623/working-document-ID-612/99db2b61-f661-86c9-bd18-e7d7696d06d4; published: Cox (2002) Metrologia 39(6) 589–595, DOI 10.1088/0026-1394/39/6/10 | draft §2 Cond. 2 + Note, §5 Eqs (1)–(5) | draft read; Metrologia abstract only | high | Consistency is a χ² over items, with the reference's uncertainty entered through the covariance; dependence among items is flagged as outside the simple procedure |
| F10 | many points per comparison | For n points, ≤ n/20 exceedances attributable to "statistical variation (i.e. there is no obvious spectral/magnitude pattern…)" do not invoke bias | CCPR-G8 v1.1 (2023), https://www.bipm.org/utils/common/pdf/CC/CCPR/CCPR-G8.pdf | p. 1 | read | medium | A *pattern* across points sharing one comparison is read as bias; practice counts exceedances rather than pooling a mean z |
| F11 | acoustics round robins | RR-I: "relative error" = mean over the 10 S/R combinations of \|sim − meas\|, divided by the jnd; only 3/17 programmes reached "the measurement standard deviation and the jnds"; conclusion: deviations "of the order of the experimental uncertainty or the jnd". BRAS 2019: T20 "averaged across ten source/receiver positions"; no quantified reference uncertainty; JND criterion. BRAS database: four complex scenes "can not be used as a direct reference" (measurement uncertainty), unquantified | corpus `docs/corpus/vorlaender-auralization.md` L3340–3354 (§11.5); Brinkmann et al. (2019) JASA 145(4) 2746–2760, DOI 10.1121/1.5096178; Aspöck et al. (2020) BRAS v3, DOI 10.14279/depositonce-6726.3 (CC BY-SA 4.0) | §11.5; JASA §II.D, III.B.1, Fig. 5; dataset record | corpus read; JASA/BRAS tool summary | medium | Round robins pool per room by averaging over positions against the jnd; none enters a reference uncertainty in a denominator; none supports or rejects (a)–(e) directly |
| F12 | ISO 5725-4 | 2020 ed.: 5.4.3 "Requirements of measurement uncertainty of the accepted reference value"; 6.5.2 "Estimation of the laboratory bias" | ISO 5725-4:2020 TOC (DIN), https://www.din.de/de/mitwirken/normenausschuesse/nqsz/veroeffentlichungen/wdc-beuth:din21:322875554/toc-3159529/download | p. 1 | TOC only | low | Clause exists; formula unverified |

**Derived from committed data (not from a source):**
- **D1** file 6 (`/home/user/makroof/docs/review/phase-05h/6-orchestrator-K20-certified-listing.md`): BRAS per-pair ℓ_ref at 500 Hz ranges 0.001–0.367 %, mean 0.113 %; 1 kHz 0.001–0.360 %, mean 0.109 %; 2 kHz 0.001–0.351 %, mean 0.109 %.
- **D2** `/home/user/makroof/tools/validation/data/phase05b.json` L10586–10588: CR2 `"e_target_change": 0.00354` = the worst pair-band in CR2 (ls1_mp1, 1 kHz, 0.353 %). So **0.354 / 0.366 / 0.140 % are per room CR2 / CR3 / CR4** (file 6 maxima 0.367 % CR3, 0.141 % CR4), not per band.
- **D3** CR2 500 Hz signed change 2.5→1.25 m (r1 e_target, L10472–10582): −0.349, −0.012, +0.180, −0.244, −0.041, +0.103, −0.138, −0.139, −0.138, −0.284 %: 8 negative, 2 positive; mean −0.106 %, SD 0.167 %. The change is **not** one sign across a room's pairs; the shared part (≈ −0.11 %) is smaller than the pair-to-pair spread.
- **D4** Under f(h) = f₀ + Ah^p (F6 Eq. 11, F7 Eq. 1), the residual at 1.25 m is −c/(2^p − 1), *opposite* in sign to the change c. For the 8 CR2 pairs with c < 0 the 1.25 m reference sits *above* f₀, so an ℓ→0 estimator (AX39) would read *below* the reference there, while the BRAS class mean is +0.11 % (file 9). K-a3 must tabulate sign(C++ − ref)_i against −sign(c_i) before "the pooled z resolves the rung error" is relied on.
- **D5** Option (a) per-item scale 1/√(1+(0.0432·ℓ%/SE)²) at SE 0.035 dB: ℓ 0.11 % → 0.991; 0.35 % → 0.917; 0.55 % (living_room) → 0.83. Mean over the 30 BRAS pairs ≈ 0.98, not the 0.91–0.92 the packet assumed; on these figures (a) leaves mean z ≈ 0.43 in all three bands against 0.412.

### 3. Not found / unresolved
- ISO 13528 clause text (9.2's 0.3 σ_pt rule, 9.9 combined scores): iso.org/OBP 403; only TOC + Eurachem/NIST secondary. Settled by the standard itself.
- IUPAC Harmonized Protocol (Thompson, Ellison, Wood 2006, PAC 78(1) 145–196): 403 on three hosts; RSC AMC brief 16 (404) and Anal. Methods 2016 (403).
- ASME V&V 20-2009 body (u_val formula; §5-3 "Case 3: two measured variables share an identical error source" is in the TOC, https://www.asme.org/getmedia/692ee706-d396-49fd-b62c-d8e3de655a27/21356.pdf): paywalled; ITTC (F6) is the retrievable equivalent.
- Brinkmann et al. (2021) Applied Acoustics 176:107867 (measurement-error section): redirect/paywall.
- Any source quantifying BRAS measurement uncertainty in dB.

### 4. Conflicts between sources
- Treatment of a last-halving change: quadrature as a standard uncertainty (F1, F4, F6 "stochastic") versus bound/rectangular (F5 GUM F.2.3.3) versus correction when sign is known (F5 GUM 3.2.3; F6 "deterministic") versus safety-factored band F_S = 1.25–3 (F6, F7). Not contradictions, but different readings of what ℓ_ref *is*; the decider must say which reading AX36/AX42 made.

### 5. Premises and seat leads screened
| source | claim | status | basis |
|---|---|---|---|
| decider K-a2 / file 3 L72 | BRAS ℓ_ref 0.354 / 0.366 / 0.140 % at 500 Hz / 1 kHz / 2 kHz | **corrected**: per room CR2/CR3/CR4, worst pair-band; per-pair values 0.001–0.367 %, mean ≈ 0.11 % in every band | D1, D2 |
| file 9 / decider | rung error "same sign across a room's pairs" | **corrected** for CR2 at 500 Hz (8 −, 2 +); CR3/CR4 not computed | D3 |
| decider | option (a) "is the form of a metrological E_n score" | **partly confirmed**: form matches ζ/E_n (F1, F4) only if ℓ_ref is a standard uncertainty; as a raw last-halving change it is not (F5–F7) | F1, F4–F7 |
| decider K-a6 | pooled SE/√M < ℓ_ref makes the rule unpassable | **confirmed in form** for the *shared* part of ℓ_ref (F8, Eq. E.6); magnitude is the shared part (≈ 0.11 %), not 0.35 % | F8, D3 |
| decider arithmetic (1) | (a) scales BRAS z by ≈ 0.91–0.92 at 500 Hz/1 kHz | **corrected**: ≈ 0.98 mean | D5 |
| Seat 2 lead (file 23 L74, via decider) | pooling per class guards against dilution | not a factual claim; no screening |

### 6. Corpus candidates
JCGM 100:2008 (GUM); ITTC 7.5-03-01-01 (2017); Bich/Cox et al. 2002 BIPM guidelines (and Cox 2002 Metrologia); ISO 13528:2015/2022 (licence permitting); ERM Application Note 1 (2010).

### 7. Readiness
| row | status |
|---|---|
| K-a1 | known (file 9) |
| K-a2 | **misinformed → corrected** (D1, D2) |
| K-a3 | **under-informed** (orchestrator table; add per-pair signed change c_i and sign(C++ − ref)_i, D4) |
| K-a4 | under-informed (same table) |
| K-a5 | **known**: forms F1/F4 (per item), F8/F9 (shared reference), F5–F7 (bound vs 1-σ vs correction, F_S); nature of ℓ_ref: mixed sign within a room (D3) |
| K-a6 | known, qualified (F8, D3) |

**Verdict: NOT READY** for D-H3 (a). RQ-H3-1 is answered, but the choice among (a)–(e) still turns on K-a3, now with two additions: the per-pair signed changes (D3/D4) and the recomputed pooled means using the per-pair ℓ_ref (D5), because the packet's ℓ_ref figures and sign premise were wrong. Items (b)–(d) are unaffected by this dossier.
