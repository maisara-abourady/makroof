Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. The only new file is `docs/corpus/kuttruff-room-acoustics.md`. I read its Notation and symbol-conflict sections; ρ = 1−α and m = intensity attenuation constant in Ch. 4–6.

# Re-consultation with Kuttruff, *Room Acoustics* (6th ed.)

Kuttruff changes three of my earlier recommendations and corrects two things I got wrong:

- **My proposed item 1 test would have failed.** I suggested a uniform-α, s = 1 shoebox should match Eyring within ±5 %. Kuttruff's own results for such rooms come out 5–10 % longer than Eyring (§5.5, §5.7 Table 5.2).
- **I understated ray-tracing cost.** Kuttruff's guideline is 10⁵–10⁶ particles for counters of about 1 m (§9.8), far more than Vorländer's N for G that I quoted.
- **Changed:**
  - Item 1: use Kuttruff's radiosity decay (a*) as the Phase 05 comparison, not ray tracing.
  - Item 3: the shape of the scattered-energy delay is now defined (radiosity), so there is no need for an invented kernel.
  - Item 5: use Kuttruff's diffuseness measure q_d instead of ψ, and drop the diffusion equation as a fallback.
- **New interaction:** realistic floor scattering in `open_field` would very likely fail its −60 dB acceptance gate.

## 1. Earlier gaps and NOT CHECKABLE rows: does Kuttruff settle them?

| earlier gap | Kuttruff | verdict |
|---|---|---|
| Millington–Sette | §5.4 Eqs. 5.27–5.28. Kuttruff calls the derivation a wrong shortcut: it averages ln(1−α) instead of α, so any portion with α = 1 gives T = 0. | **Settled: rejected** |
| Eyring with uneven α | §5.4 Eqs. 5.15–5.25. In a diffuse field, where successive reflections are independent and wall hits follow area shares, the expected energy goes with the area-weighted ᾱ, so Eyring with ᾱ is the correct diffuse-field result. | **Settled.** My earlier framing was imprecise: the error comes from the loss of diffuseness, not from uneven α as such (§5.2). |
| "Kuttruff's correction" | The text has two corrections: path-length variance (§5.5 Eqs. 5.33–5.35, γ² from Table 5.1) and the radiosity effective absorption exponent a* (§5.7 Eqs. 5.53–5.56). No separate "uneven-absorption correction" formula appears. | **Partly settled.** The specific uneven-absorption formula is still NOT CHECKABLE (earlier Kuttruff editions or his papers would settle it). |
| Fitzroy / Arau-Puchades | Not in Kuttruff. | **Still NOT CHECKABLE** (Toole Box only names them) |
| Per-axis decay | §4.2 Eq. 4.8 gives per-axis crossing rates n_x, n_y, n_z. A smooth rectangular room never mixes directions, so each ray decays at its own rate and the decay curve bends. One totally absorbing wall gives a decay ∝ 1/t (§4.3 Eqs. 4.14–4.16). | **Settled for the physics:** specular shoeboxes have bent decays. No per-axis T formula is given. |
| Kernel shape and length | Lambert scattering (§4.5 Eq. 4.24). Time-dependent radiosity (Eq. 4.28) plus the gather at an interior point (Eq. 4.29) define the delay and weight of scattered energy from each wall element. Mixed specular/diffuse versions: §4.6 Gilbert, Joyce Eq. 4.35, Koutsouris (radiosity + image sources). | **Settled for Lambert scattering.** My "about one mean free time" kernel is superseded. |
| √V perceptual mixing time | Not in Kuttruff. But with Eq. 4.6, any fixed reflection-density threshold ρ* gives t = √(ρ*·V/(4πc³)) ∝ √V. Computed: t = √V ms means a density of 4π·343³·10⁻⁶ ≈ **507 reflections/s**. Kuttruff's synthesis density of 10 000/s (§9.9 step 5) would mean t ≈ 4.44·√V ms. | **Form settled, constant NOT CHECKABLE** (the perceptual study would settle it) |
| Diffuseness criteria | §8.5: directional diffusivity d (Eqs. 8.31–8.32), spatial correlation (Eq. 8.34), intensity measure q_d = 1 − c\|I\|/w (Eq. 8.43). All are "necessary but not sufficient". §9.5: no quantitative guideline for how much diffuseness is needed. | **Settled: indicators only, no threshold** |
| ψ on image sums | Incoherent components add as intensities (Ch. 4 intro; §5.1 Eq. 5.1), so q_d can be computed from an image/patch list as 1 − \|Σ E_i u_i\| / Σ E_i. Zotter's ψ = 1 − \|r\|² uses a different scale. | **Use q_d.** It is a necessary condition only. |
| One trace for all bands | §9.8 steps 2–3(a): the scattering decision uses s, and option (a) multiplies energy by (1−α_i). With a broadband s (AX17), the path does not depend on the band, so one path can carry all 8 band energies. Annihilation (option b) cannot. | **Follows from the §9.8 algorithm** (derived, not stated) |
| Ray count | §9.8: 10⁵–10⁶ particles for counters of about 1 m. | Settled. My earlier cost was too optimistic. |
| Early/late transition | Fig. 4.8: early part up to ≈50–60 ms (schematic). §4.2: later reflections "merge" into reverberation, with no density threshold given. §7.5.2 Eq. 7.12: gradual perceptual early/late weighting, t₁ ≈ 35 ms, t₂ ≈ 100 ms. §7.6: reverberance follows the first 160 ms of decay. | **Still no simulation rule** (Vorländer §11.7 stands) |
| Diffusion equation (§4.6 Eqs. 4.37–4.39) | Valid only for nearly diffuse fields, and there are no clear rules for deciding when that holds. | **Rejected as a sparse-field fallback** |

## X. Shared problem: scattered energy (confirmed and strengthened)

- **AX16's energy split is exactly Kuttruff's for uniform α.** Per reflection, s(1−α) is scattered and (1−s)(1−α) stays specular. After n reflections the scattered part is [1−(1−s)ⁿ](1−α)ⁿ (§5.2, Fig. 5.3). With α = 0.15 and s = 0.4 the scattered share is about 40 % after 1 reflection and dominant from 2. So the missing early scattered energy in the rendered IR is confirmed.
- **AX16's inheritance of the specular path's absorption is not Kuttruff's model.**
  - A diffusely reflected ray "forgets its history" (§4.5).
  - Gilbert (§4.6): after scattering, energy is reduced by the coefficients of the walls it actually meets next.
  - In a diffuse field those hits follow area shares, giving (1−ᾱ) per reflection (Eq. 5.18).
  - Under AX16, scattered energy decays like the specular lattice. In a shoebox with uneven α that decay is non-exponential (§4.2; §4.3 Eq. 4.16 for one absorbing wall), while a Lambert room decays in a straight line (§5.7, Fig. 5.10).
  - So E_target comes from the unmixed field. Whether it is high or low depends on the case (Table 5.2: case 4 decays faster than Eyring, case 6 slower). The bias cannot be bounded without solving the radiosity.
- **This affects how the matching window is read.** Referring entries along a single exponential is wrong where the specular energy decays like 1/t.

## Item 1: Eyring with uneven absorption (CHANGED)

**Evidence**

- Kuttruff Table 5.2 compares Eyring with the radiosity iteration (Lambert walls, Eqs. 5.55–5.56):

  | case | Eyring | radiosity | difference |
  |---|---|---|---|
  | uniform cube | 1.47 s | 1.55 s | +5 % |
  | uniform 10×20×30 | 1.38 s | 1.52 s | +10 % |
  | 10×20×30, floor α = 1 | 1.38 s | 1.21 s | −12 % |
  | 10×20×30, short wall α = 1 | 4.61 s | 5.93 s | +29 % |

- Kuttruff reports similar results from ray tracing (§5.7, §9.8).
- The final decay slope does not depend on receiver position (Miles, §5.7).
- Check: Eyring for 10×20×30 (V = 6000, S = 2200, ᾱ = 3/11) = 0.161·6000/(2200·0.3185) = 1.379 s ✓.
- **The γ² correction partly closes the gap.**
  - 10×20×30 room (γ² ≈ 0.38 assumed, between Table 5.1's 1:2:2 and 1:2:5 rows): a'' = 0.3185·(1 − 0.19·0.3185) = 0.2992, so T = 1.47 s against 1.52 s by radiosity.
  - Cube (γ² = 0.342): T = 1.52 s against 1.55 s.
- **The limit at low scattering:** a* assumes Lambert walls everywhere. With smooth walls and an absorbing floor, real T can exceed the prediction (§9.4: Göttingen City Hall measured ≈2 s against 1.6–1.7 s predicted, from a 2-D horizontal field; §4.2). So a* can be wrong in the opposite direction when s is small.

**Fit against constraints:** a* depends only on geometry, α_b and air (insert exp(−mR), §4.5), not on positions. So the Phase 10 cache is unchanged. It needs no random numbers (AX5). Its cost is a few N² iterations per band, small against AQ10. It is generic (NFR-8). It needs a new AX for the patch size.

**RECOMMENDATION (confidence: medium)**

- Keep Eyring in Phase 04. Kuttruff confirms it is the correct diffuse-field formula with arithmetic ᾱ.
- In Phase 05, report radiosity a* (§5.7) and γ²-Eyring (Eq. 5.34) beside it against BRAS, instead of a stochastic ray tracer.
- Promote one of them to T60_b only on the Phase 05 evidence.
- What changes: AQ2, a new AX for patches; phases 05, then 04, 10 and 13. No contract change.

**Falsifiable check:** an a* unit test must reproduce Table 5.2's iteration column. I would use ±5 %; that tolerance is my choice, not from the corpus.

## Item 2: Fixed atmosphere (confirmed in direction; my magnitudes revised)

**Kuttruff Table 6.1 (20 °C, from Bass 1995) disagrees with the Vorländer Annex.**

| source | 2 kHz | 4 kHz | 8 kHz |
|---|---|---|---|
| Kuttruff, 50 % RH | 2.28 | 6.84 | 24.29 |
| Vorländer Annex, 20 °C, 30–50 % RH | 1.9 | 5.8 | 20.3 |
| Vorländer Annex, 20 °C, 50–70 % RH | 1.7 | 4.1 | 13.5 |

(m in 10⁻³ m⁻¹.) At 8 kHz and 50 % RH, Kuttruff's m is 1.2–1.8× the Annex value. In the 10000 m³ room that gives T = 0.93 s against 1.02 / 1.23 s. My earlier 8 kHz nominal T values were too long if Kuttruff's table is right.

**Recomputed sensitivity** with Kuttruff Eq. 5.24 (0.161), ᾱ = 0.15, Table 6.1 values, change relative to 50 % RH:

| room | 2 kHz | 4 kHz | 8 kHz |
|---|---|---|---|
| 1000 m³ (S = 906 m²) | −0.8 % / +0.5 % | −3.4 % / +3.6 % | −8.5 % / +11.7 % |
| 10000 m³ (S = 4725 m²) | −1.4 % / +0.9 % | −5.7 % / +6.2 % | −11.6 % / +17.2 % |

- First figure is 40 % RH, second is 70 % RH.
- Example working: 10000 m³ at 8 kHz, 70 % RH: T = 1610 / (767.9 + 716.4) = 1.085 s, against 0.926 s at 50 %.
- Kuttruff gives the T difference limen as about 4 % (Seraphim; §7.6, under somewhat artificial conditions).
- §6.1 does not contradict the recommendation. **RECOMMENDATION unchanged:** keep AX4, report the bound, add a validation-only override. Confidence high.

## Item 3: Scattered energy at the specular time (CHANGED)

**RECOMMENDATION (confidence: medium on direction, low on cost)**

- Drop my improvised kernel.
- In a phase after Phase 05, replace AX16 with an ISM + radiosity hybrid:
  - inject s(1−α) of each specular hit's incident energy into the boundary patch it hits, at the hit time (Eq. 4.24; Gilbert §4.6);
  - step it forward with Eq. 4.32 / 5.51 and gather it at the listener with Eq. 4.29;
  - take the tail decay from the same kernel's a*.
- Kuttruff describes this kind of hybrid in §9.8 (citing radiosity [R9.29]) and §4.6 (Koutsouris).
- It fixes X (energy before t_mix, absorption after scattering, and E_target depending on s), and it gives directions for Phase 08.
- Cost: Miles used 88 patches. 88² × 200 steps × 8 bands ≈ 1.2·10⁷ multiply-adds up to t_mix, which looks small. Whether 88 patches is accurate enough is NOT CHECKABLE.
- What changes: AX16, AQ2, a new AX; phases 04b/06–08, 05, 10 and 13. No contract change.

**New interaction: the open_field gate.** I estimated Lambert floor scattering with Eqs. 4.27 and 4.29 against the direct sound (Eq. 5.43). Energy arriving more than 50 ms after the direct sound, relative to it, is ≈ ρ_s·h²·r₀²/(2R_c⁴).

- I assumed h = 1.5 m, r₀ = 3 m and s(1−α) = 0.4. These are illustrative values, not the fixture's.
- That gives R_c = 10.1 m and a ratio of ≈ −34 dB, so the −60 dB gate fails.
- That gate holds only because of AX16. It must be re-derived if item 3 changes.

**Falsifiable check:** in a Lambert shoebox (s = 1), the hybrid's late decay must match the a* slope, and its energy before t_mix must match radiosity alone within 1 dB per 10 ms bin.

## Item 4: Mixing-time rule (confirmed)

- No numeric merge criterion exists in Kuttruff either.
- The √V floor corresponds to about 507 reflections/s (computed above).
- The k_eff rule hands over at a density of 2.35·10⁴·V^(−1/3) s⁻¹ (computed from Eq. 4.6 at t = 6.8·V^(1/3) ms). That is below Heinz's 10⁴/s synthesis density in all rooms over about 13 m³. Whether that matters perceptually is NOT CHECKABLE.
- In Fig. 5.10, radiosity decays straighten after about 1–3 mean free paths, where l̄ = 4V/S (Eq. 5.12). For the AQ10 room, 3 l̄/c ≈ 95 ms against the rule's ≈124 ms. Same order of magnitude; this corroborates the rule, it does not derive it.

**RECOMMENDATION (confidence: medium)**

- Keep the rule and add the realised-k requirement.
- Under the item 3 hybrid, re-derive t_mix as the time when the radiosity decay has become straight and the specular share of the window is small. The threshold for "small" is NOT CHECKABLE.

## Item 5: Sparse or non-diffuse fields (partly changed)

Interim rule kept: require realised k_eff ≥ 19 and extend the ISM up to a cap.
- Kuttruff supports it: a shoebox image lattice is complete and every image is valid (§4.1).
- Flat rooms have an exact image sum (Eq. 4.3).
- Long rooms with absorbent sides produce flutter echoes that a statistical tail would erase (§4.2).

Changes from my earlier answer:
- Report q_d (Eq. 8.43) instead of ψ, as a necessary condition only.
- Reject the diffusion equation as a fallback (§4.6).
- In the long run the item 3 hybrid covers these rooms with no special rule (§5.7: straight decays even with imperfect diffuseness, for Lambert walls).

Confidence: medium.

**Falsifiable check:** the flat-room energy against Eq. 4.3 within ±1 dB. Reproduce the 1/t decay of Eq. 4.16 in a box with one α = 1 wall and s = 0.

## Updated summary

| item | recommendation | confidence | changes | corpus basis | changed vs 22dc9dd |
|---|---|---|---|---|---|
| 1 Eyring | keep in 04; in Phase 05 report radiosity a* and γ²-Eyring against BRAS; promote on evidence; unit test reproduces Table 5.2 | medium | AQ2, new AX; phases 05, 04, 10, 13 | Kuttruff §5.4–5.5, §5.7 Table 5.2, §4.2, §9.4 | **yes** (radiosity instead of ray tracing; my earlier test corrected) |
| 2 atmosphere | keep AX4; report the humidity bound; validation-only override | high | AX4; phases 04, 05 | Kuttruff §6.1 Table 6.1, Eq. 5.24, §7.6; disagrees with the Vorländer Annex | numbers only |
| 3 AX16 | ISM + radiosity hybrid in a later phase; re-derive the open_field gate | medium / low | AX16, AQ2, new AX; phases 05, 08, 10, 13 | Kuttruff §4.5–4.6, Eqs. 4.24, 4.28, 4.29, 4.32; §5.2; §9.8 | **yes** |
| 4 mixing time | keep, add realised k; re-derive under the hybrid | medium | phase-04 scope 2 | Kuttruff Eq. 4.6, Fig. 4.8, Fig. 5.10, §7.5.2, §7.6, §9.9 | no (reasons refined) |
| 5 sparse fields | realised-k + ISM extension; report q_d; no diffusion-equation fallback | medium | new AX, AX20, AQ10 | Kuttruff §4.1–4.3, Eqs. 4.3, 4.16, §4.6, §8.5 Eq. 8.43 | **partly** |

## Questions, most severe first

1. Is the hybrid IR meant to contain scattered energy before t_mix? Under AX16 plus Phase 03 it contains none. Kuttruff §5.2 puts the scattered share at about 40 % after one reflection for s = 0.4.
2. Is the open_field gate (< −60 dB after 50 ms) meant as a physical expectation? With Lambert floor scattering (Eq. 4.29) and illustrative geometry it comes out at ≈ −34 dB.
3. At 20 °C / 50 % RH, which m does AX4's ISO 9613-1 code give at 4 and 8 kHz: Kuttruff's 6.84 / 24.29, or values near the Vorländer Annex rows (4.1–5.8 / 13.5–20.3, ×10⁻³ m⁻¹)?
4. Is the Phase 04 Eyring gate meant as a self-consistency check, or as a statement about physical T? Kuttruff Table 5.2 puts Lambert rooms with uniform α 5–10 % above Eyring.
5. Must t_mix,e also satisfy realised k_eff ≥ 19, not only the expected value?