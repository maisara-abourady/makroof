Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I re-did every computation the advocate asked for, from the corpus and `/home/user/makroof/tests/scenes/valid/open_field.json`.

# Rebuttal round: reply to the advocate

The advocate is right on nearly every point, and its arithmetic checks out. I withdraw three things from my earlier reports:
- Taking the tail decay from a* (item 3).
- Moving t_mix to where the specular share is "small" (item 4).
- q_d as a diffuseness indicator (item 5).

I also accept that my check C3 was circular.

## 1. Answers to the five questions

**Q1. What supports taking the post-t_mix decay from a* when s ≤ 0.3?**
- No corpus passage supports it quantitatively.
- The only support is qualitative: nearly all energy becomes diffuse after a few reflections, and the conversion is irreversible (Kuttruff §5.2, Fig. 5.3, which uses s = 0.4). Totally diffuse reflection is often closer to real walls over many reflections (§4.5).
- Computed, for uniform α in the AQ10 room with T = 2 s and s = 0.1:
  - The T30 range (−5 to −35 dB) spans about t = 0.17–1.17 s, i.e. n = n̄t ≈ 5–37 reflections.
  - Over that range the specular share (1−s)ⁿ falls from 0.59 to 0.02.
  - So the T30 range is a mixed regime: neither the Lambert decay of §5.7 nor the lattice decay of §4.2 alone describes it.
- With uneven α and low s, surviving specular paths can lengthen T (§9.4, Göttingen).
- I withdraw the commitment. The source of the tail decay is decided by the Phase 05 evidence (item 1).

**Q2. q_d for the Eq. 4.3 flat room (r = 5 m, h = 3 m, A and B midway).**
- Images come in ±n pairs at r_n = √(25 + 9n²). Their vertical components cancel, and the horizontal component is r/r_n.
- Incoherent intensities add (Eq. 5.1), so c|I|/w = Σ I_n·(r/r_n) / Σ I_n.
- **At 100 ms:** the pair arriving there is n = ±11 (r_n = 33.38 m, 97.3 ms). That gives q_d = 1 − 5/33.38 = **0.85**. ✓ the advocate's figure.
  - The actual field at that time is two nearly vertical arrivals: elevation arctan(33/5) ≈ 81°, up and down.
- **Steady state, α = 0, direct sound included:**
  - Σ 1/r_n² = (π/(rh))·coth(πr/h) = 0.2094.
  - Σ r/r_n³ ≈ 0.133, summed term by term to n = 10 plus a tail estimate.
  - So q_d ≈ 1 − 0.637 = 0.36.
- q_d therefore swings with the time window, and it reads a two-direction (1-D) field as near-diffuse.
- What remains of q_d is only what Kuttruff §8.5 grants: a necessary condition. It has no diagnostic value for item 5, so I drop it.

**Q3. γ²-Eyring on all six Table 5.2 cases.**
- Formula: T_γ = T_E / (1 − γ²a/2), with a = −ln(1−ᾱ) (Eq. 5.34). γ² = 0.342 for the cube (Table 5.1). For 1:2:3 I used 0.38, my interpolation between Table 5.1's 1:2:2 and 1:2:5 rows (0.363, 0.403), not a tabulated value.

| case | ᾱ | Eyring | γ²-Eyring | iteration | γ² moves T |
|---|---|---|---|---|---|
| 1 cube, uniform | 1/6 | 1.47 s | 1.47/0.9688 = **1.52 s** | 1.55 s | toward |
| 2 cube, floor α = 1 | 1/6 | 1.47 s | **1.52 s** | 1.35 s | **away** |
| 3 10×20×30, uniform | 3/11 | 1.38 s | 1.38/0.9395 = **1.47 s** | 1.52 s | toward |
| 4 10×20×30, floor α = 1 | 3/11 | 1.38 s | **1.47 s** | 1.21 s | **away** |
| 5 long side wall α = 1 | 300/2200 = 0.1364 | 2.995 s | 2.995/0.9722 = **3.08 s** | 3.06 s | toward (slight overshoot) |
| 6 short side wall α = 1 | 200/2200 = 0.0909 | 4.607 s | 4.607/0.9819 = **4.69 s** | 5.93 s | toward (small) |

The advocate's numbers are all correct. In cases 2 and 4, γ²-Eyring moves away from the iteration result.

**Q4. Which corpus reference tests the hybrid at 0 < s < 1?**
- None gives numerical results at an intermediate s on one surface.
- The closest are:
  - Vorländer Table 4.1, flat room with a scattering ceiling *or* floor. That is mixed specular/diffuse per surface; it gives steady-state level against distance, read off a plot only (±1–2 dB).
  - The partial-s ray-tracing algorithm (Kuttruff §9.8 step 2; Vorländer Eqs. 11.2–11.4), implemented independently as a reference.
- Koutsouris (§4.6) is cited only.

**Q5. open_field with the fixture's geometry.**
- Geometry from the fixture: emitter L at (45, 60, 3), listener at (50, 40, 1.7).
  - Direct path r_d = √(426.69) = 20.66 m.
  - Floor image path 21.14 m, so 1.42 ms later ✓.
  - Delay condition: r₁ + r₂ ≥ 20.66 + 17.15 = 37.81 m.
- Exact integral, in place of the advocate's r₁ ≈ r₂ shortcut:
  - Per element, from Eqs. 4.24, 4.27, 4.29 and 5.43, energy relative to the direct sound is dE/E_d = ρ_s·h_s·h_r·r_d²/(π r₁³ r₂³) dS.
  - Neglecting the heights inside r₁ and r₂, elliptic coordinates (foci 20.62 m apart, c = 10.31 m, cosh μ₀ = 18.905/10.31 = 1.834) give ∫dS/(r₁³r₂³) = 2π/(c⁴ sinh²2μ₀) = 2π/(11 289 × 31.80) = 1.75·10⁻⁵ m⁻⁴.
  - Ratio = ρ_s × 692.7 × 1.75·10⁻⁵ = ρ_s × 0.0121, i.e. −19.2 dB + 10·log ρ_s.
  - This is 1.5 dB above the advocate's ρ_s × 0.0085, so its "underestimates" note is right. Keeping the heights would lower the value slightly (about 1 dB near the focus).
- With ρ_s = 0.4(1−α_b), per band:

| band | 63 | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|---|
| ratio (dB) | −23.4 | −23.6 | −24.4 | −27.1 | −28.2 | −34.1 | −43.1 | −43.1 |

  - Air absorption over the extra ≥17 m of path removes about 0.5 dB more at 4 kHz and 1.8 dB at 8 kHz (Kuttruff Table 6.1).
  - **No band gets near −60 dB.** Emitter R is the mirror case.
- **Does E_b have to represent it?** No. Under §4.5 each floor element is a secondary source with its own 1/R′² spreading. This is single-surface, half-space scattering: not isotropic, so not a diffuse field (§5.1), and not an exponential decay. It is a deterministic early-response component, separate from E_b, and E_b = 0 stays correct.

## 2. Ledger rows

- **X-a: ACCEPT.** Kuttruff §5.2 and Vorländer Eq. 6.4 support it. The advocate's step sizes are right: 3.89 hits gives 0.87 / 1.78 / 4.87 / 8.65 dB. I also accept the reported-only 10 ms envelope-step metric.
- **X-b: ACCEPT IN PART.**
  - The narrowing is right. Per path, specular plus scattered equals (1−α)ⁿ for any s (§5.2), so with uniform α, AX16's energy accounting is exact.
  - Residual I keep: even with uniform α, each AX16 entry uses its own path's hit count, not the mixed-field n̄ (§4.2 Eq. 4.8, §5.5). Within the matching window this is a small effect and not quantified.
- **1: ACCEPT.** Q3 confirms that γ²-Eyring moves T the wrong way in cases 2 and 4. Keeping a* in `tools/acoustics` until it is promoted avoids a patch-size AX and leaves the cache and goldens alone.
- **2: ACCEPT.** The corpus has nothing to say about showing the bound in the UI; dropping it is a product call I don't contest. The advocate's T values match mine.
- **3: ACCEPT.** The corpus supports injecting early scattered energy (Eq. 4.24, Gilbert §4.6, Kuttruff §9.8 hybrids). It does not support an a*-only tail at typical s (Q1). Promote on evidence, as in item 1.
- **4: ACCEPT.** Checked: n = 22 / 45, t = 0.70 / 1.43 s, N(t) ≈ 9.7·10³ / 8.2·10⁴ images, Eq. 9.23 at order 30 = 37 880. Vorländer §11.6.1 and §15.3 give no perceptual case for this cost.
- **5: ACCEPT IN PART.**
  - q_d is out (Q2).
  - Per-axis energy shares follow from isotropy (Eqs. 5.1–5.2: ⟨u_k²⟩ = 1/3), and I confirm u_z² = (33/33.38)² = 0.977 for the flat room.
  - But they are also only a necessary condition. Three equal axial flutter pairs read 1/3, 1/3, 1/3 while being plainly non-diffuse. No threshold is checkable.
- **OF: ACCEPT.** The numbers are confirmed and slightly higher with the exact integral. The AX17 low-frequency point is valid: the Vorländer Annex gives s < 0.05 below a/λ = 0.125. How large it is depends on ground roughness, which is NOT CHECKABLE.
- **C1: ACCEPT.** The Table 5.2 cases use α = 0, which AQ3 (α ≥ 0.01) forbids in scenes, so the test must call the solver directly.
- **C3: ACCEPT.** With s = 1 the test compares radiosity with itself. The closest corpus references for mixed fields are the Q4 ones (plot-read Vorländer Table 4.1, and an independently implemented §9.8 ray tracer).
- **C5: ACCEPT.** Eq. 4.3 already carries (1−α)^|n|. Air absorption needs exp(−m r_n) (§4.2, §4.5). Eq. 4.16's 1/t law needs rigid walls, so with α ≥ 0.01 the test must include (1−α)ⁿ.

**The advocate's arithmetic and citations:**
- Checked and correct: all numbers, Eq. 9.23, Vorländer Eq. 6.4, the Annex a/λ statement, and `large_hall` s = 0.7.
- One imprecision: the open_field shortcut underestimates by about 1.5 dB. It flags this itself.
- Not verified by me: the Izhaki "Early reflections" claim, and Phase 12's courtyard "slap echoes". Neither changes a verdict.
- Minor: calling `courtyard` "the Eq. 4.16 case" holds only with rigid other walls (see C5).

## 3. Final positions

| id | final interrogator position | agrees with advocate? | what remains disputed |
|---|---|---|---|
| X-a | No scattered energy before t_mix; the EDC gate can't see the step; add a reported 10 ms envelope-step metric | yes | nothing |
| X-b | AX16 energy bias only with uneven α; size and sign unbounded; Phase 05 groups errors by absorption contrast | partly | a small per-path hit-count residual even with uniform α (unquantified) |
| 1 | Eyring in 04; a* as a Phase 05 reference in tools/acoustics; γ²-Eyring for information only | yes | nothing |
| 2 | keep AX4; report the bound in Phase 05; validation-only override; AirAbsorption test against Kuttruff Table 6.1 | yes | nothing (UI display is a product call) |
| 3 | early Lambert injection as a Phase 05 reference hybrid; tail decay source decided by evidence | yes | nothing |
| 4 | keep the k_eff rule plus realised k; no specular-share re-derivation; 80/140 ms comparison in Phase 05 | yes | nothing |
| 5 | realised k plus capped ISM extension; per-axis shares reported, not q_d | partly | per-axis shares are also only a necessary condition (they miss three-axis flutter); no threshold |
| OF | E_b = 0 kept; the −60 dB gate recast as an AX16 consistency check; Lambert estimate −23 to −43 dB per band | yes | nothing (exact integral is 1.5 dB above the shortcut) |
| C1 | a* test calls the solver directly with α = 0 cases | yes | nothing |
| C3 | the s = 1 test is circular; mixed reference = §9.8 ray tracer plus plot-read Vorländer Table 4.1 | yes | nothing |
| C5 | flat-room and 1/t tests with α ≥ 0.01, air absorption and the ISM cap | yes | nothing |