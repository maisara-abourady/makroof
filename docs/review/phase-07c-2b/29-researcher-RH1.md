# 29-researcher-RH1: Researcher, R-H1 (source power near rigid faces at 1 kHz)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

## R-H1 researcher dossier
The caller asked for this to be saved as `/home/user/makroof/docs/review/phase-07c-2b/29-researcher-RH1.md`. I have no write tool and this task was read-only, so **the main session needs to save it**.

**Main finding:** a point source 0.1 m from rigid faces radiates **less** power than in free field at 1 kHz. The lift of +3/+6/+9 dB holds only far below 1 kHz. The engine's −6.2 dB is a deficit, which is the direction the physics predicts. Its size matches neither the pure-tone value nor my rough octave-band estimate. Details follow.

### 1. Decision served and question examined
- File 28 (decider, M3H), RESEARCH NEEDED **R-H1**, inventory row **K11**: the radiated power of a point source at 0.1 m from 1, 2 and 3 rigid faces, at 1 kHz. Three parts:
  - the factor relative to free field;
  - the frequency range where that factor holds;
  - the condition on distance relative to wavelength.
- It serves Seat 2's [Hyp] (as quoted in file 28): "a boundary source radiating more power makes a 6.2 dB deficit point the wrong way".
- Context: `/home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md`, lines 22 and 34–35.
  - Emitter L is at (19.9, 29.9, 9.9), 0.1 m from two walls and the ceiling.
  - In the 1 kHz octave its diffuse tail is 6.1–6.2 dB below emitter R's.

### 2. Findings table
Conditions used in every derivation below: c = 343 m/s, f = 1 kHz, λ = 0.343 m, d = 0.1 m, so d/λ = 0.29 and 2kd = 3.664.

| id | question | finding (value + conditions) | reference | location | read/unverified | confidence | what it changes |
|---|---|---|---|---|---|---|---|
| F1 | corpus: factor relative to free field | **Power** into the solid angle is P, 2P, 4P, 8P (0, +3, +6, +9 dB) for 0, 1, 2, 3 perpendicular surfaces. **SPL** at a fixed radius is +0, +6, +12, +18 dB. Point monopole "closely adjacent" to large flat surfaces. | Toole, *Sound Reproduction*, corpus digest `docs/corpus/toole-sound-reproduction.md` (corpus rev c1b171f) | §12.1, Fig. 12.1 table (digest lines 1609–1620) | read (corpus) | high | This is the source of the "more power" intuition. |
| F2 | corpus: when F1 holds | F1 holds only at wavelengths long compared with source size and separation distance, with no other reflecting surfaces nearby. Boundary effects arise when the source is less than a wavelength from boundaries, where interference makes the radiated power fluctuate. | same | ch. 12 intro and §12.1 (digest lines 1601, 1621) | read (corpus) | high | At 0.1 m, 1 kHz is not in F1's range (d/λ = 0.29). |
| F3 | corpus: measured behaviour | The predicted ≈6 dB steps were seen only at the lowest frequencies (≈30 Hz). Above that, the curves converged near 200 Hz, and the π/2 and π cases showed interference dips and peaks up to ≈1 kHz. Loudspeaker on/near a building, 2 m distance, NRC mid-1980s. | same | §12.1, Figs 12.2–12.3 (digest lines 1622–1631) | read (corpus) | medium: a real loudspeaker, not a point source | The textbook factors fail well below 1 kHz at practical spacings. |
| F4 | primary source: general formula | Power of N coherent simple sources (images): W/W_f = N + 2Σ j0(4π r_mn/λ). Divide by N when only one source is real. j0(x) = sin x / x; r_mn is the source spacing. Reflectors rigid and 100 % reflecting. | Waterhouse, R. V. (1958). "Output of a Sound Source in a Reverberation Chamber and Other Reflecting Environments." *J. Acoust. Soc. Am.* 30(1), 4–13. DOI [10.1121/1.1909380](https://doi.org/10.1121/1.1909380); it resolves to pubs.aip.org JASA 30/1/4. Read from a scan of the journal pages hosted at [trueaudio.com](https://trueaudio.com/array/downloads/Waterhouse-Output%20of%20a%20sound%20source%201958.pdf), accessed 2026-11-24. | p. 5, Eqs (3)–(4) | read (pp. 4–5 only) | high | The governing equation. |
| F5 | primary source: one plane | W/W_f = 1 + j0(2kx), where x is the distance to the plane. The value is 2 at x = 0 and tends to 1 when the source is many wavelengths away. | Waterhouse 1958 | p. 5, Eqs (6)–(8); Fig. 3(a) | read | high | One face at 1 kHz: **0.864, −0.64 dB** (derived; arithmetic below). |
| F6 | primary source: edge and corner geometry | Images: 1, 3 and 7 for one, two and three walls (Fig. 2). Fig. 3(b) and (c) plot W/W_f for two and three planes at right angles; asymptotes 4 and 8 at zero distance. The plot axes are ρ and r, distances along the symmetry lines, **not** the perpendicular distance to each face. | Waterhouse 1958 | p. 5, Fig. 2(a)–(c), Fig. 3(a)–(c) and caption | read | high | The explicit edge and corner formulas are in Waterhouse's Table II, which I did not see. Rows D1–D3 rebuild them from Eq. (3). |
| F7 | primary source: distance condition | Power output differs significantly from the free-field value when the source is less than a wavelength from the reflector. The paper also treats the effect of source bandwidth. | Waterhouse 1958 | p. 4, abstract and introduction | read | high | The condition the decider asked for. |
| F8 | corpus: Kuttruff, receiver side | Mean-square pressure at distance x from a rigid wall in a diffuse field: 2p̂0²[1 + sin(2kx)/(2kx)]. For octave-band noise the standing-wave ripple disappears beyond x ≈ 0.5λ. | Kuttruff, *Room Acoustics*, corpus digest | §2.5, Eq. (2.50), Fig. 2.11 (digest lines 1544–1552) | read (corpus) | high | Same function as Waterhouse Eq. (7). Linking source power to it by reciprocity is my inference; the digest does not say so. |

**Derived values (my arithmetic from Waterhouse Eq. 3, not stated in the source).**
- Image-source spacings:
  - Edge: 4 sources on a square of side 2d. Pair distances are 2d (4 pairs) and 2√2·d (2 pairs).
  - Corner: 8 sources on a cube of side 2d. Pair distances are 2d (12 pairs), 2√2·d (12 pairs) and 2√3·d (4 pairs).
- With u = 2kd:
  - **D1, one face:** W/W_f = 1 + j0(u).
  - **D2, edge:** W/W_f = 1 + 2 j0(u) + j0(√2·u).
  - **D3, corner:** W/W_f = 1 + 3 j0(u) + 3 j0(√2·u) + j0(√3·u).
  - At u → 0 these give 2, 4 and 8, which matches F1 and Waterhouse's asymptotes.
- At u = 3.664 (1 kHz pure tone, d = 0.1 m):
  - j0(3.664) = −0.1361
  - j0(5.181) = −0.1722
  - j0(6.346) = +0.0098

| faces | pure tone at 1 kHz | octave 707–1414 Hz, flat-spectrum average (coarse trapezoid, 10 points, my estimate ±0.5 dB) |
|---|---|---|
| 1 | 0.864, **−0.6 dB** | ≈0.89, **≈−0.5 dB** |
| 2 | 0.556, **−2.6 dB** | ≈0.70, **≈−1.6 dB** |
| 3 | 0.085, **−10.7 dB** | ≈0.42, **≈−3.8 dB** |

- **Crossovers at d = 0.1 m** (frequency where W/W_f = 1): about 860 Hz for one face (j0 = 0 at u = π), about 780 Hz for an edge, about 700 Hz for a corner.
  - Below these frequencies the source radiates more than in free field; above them, less, up to the 1 kHz octave's upper edge.
- **Corner within 1 dB of its +9 dB limit:** small-u series F ≈ 8 − 2u², so u ≲ 0.9, i.e. d/λ ≲ 0.07. At 0.1 m that means below roughly 250 Hz. This is a rough estimate.

### 3. Not found / unresolved
- **Waterhouse Table II** (explicit edge and corner expressions), the Appendix II impedance derivation, and the bandwidth section. Only pp. 4–5 were retrievable; the publisher page is paywalled. The full JASA article would settle this. My D2 and D3 follow directly from Eq. (3) and Fig. 2, so the risk is low, but they are derivations.
- **Kuttruff or Vorländer stating source power near boundaries.** I searched the corpus for "power output", "near the wall", "corner", "half-space", "Waterhouse", "quadruple" and similar. Neither digest states it. Kuttruff gives only the receiver-side Eq. (2.50), and his Waterhouse reference (R8.25, 1955) concerns interference patterns, not source output.
- **Absorbing (non-rigid) faces.** Every value above assumes rigid, 100 % reflecting planes. No verified formula was found for finite-impedance walls at d/λ ≈ 0.3. A source on spherical-wave reflection from impedance planes would settle it.
- **Whether a geometrical-acoustics engine should show this effect at all.** This is a conditions question, not a fact I could find (see §7, the ill-informed row).

### 4. Conflicts between sources
- These are a difference of conditions, not a conflict:
  - Toole Fig. 12.1 (F1) gives +3/+6/+9 dB in the limit d ≪ λ.
  - Waterhouse Eqs (3) and (6) (F4, F5) give the full distance dependence; F1 is their limit at zero distance.
  - Toole himself bounds F1's validity (F2).
- **Citation error in the corpus digest.** The Toole digest's bibliography (line 4456) titles the paper "…in a **Reflecting** Chamber…". The journal page and the DOI landing page say "…in a **Reverberation** Chamber…". I have not checked whether the error is Toole's or the digest's.

### 5. Seat claims screened
| seat | claim | status | reference |
|---|---|---|---|
| Seat 2 | [Hyp] a boundary source radiates more power, so a 6.2 dB deficit "points the wrong way" | **Corrected (conditions differ).** More power holds only for d ≪ λ (corner within 1 dB of +9 dB only below about 250 Hz at 0.1 m). At 1 kHz and 0.1 m, rigid-wall theory predicts **less** power: corner −10.7 dB pure tone, about −3.8 dB octave average. The sign of the engine's deficit agrees with the physics; its size matches neither value. | F2, F4–F7, D1–D3 |
| Seat 9 (lead, per file 28 K11) | the corner factor | The corpus value +9 dB is confirmed only as the low-frequency limit. | F1, F2 |

### 6. Corpus candidates
- Waterhouse 1958, JASA 30:4–13, DOI 10.1121/1.1909380. It is the primary source for this question and is not in the corpus; the copyright holder is ASA/AIP.

### 7. Readiness for the decider
| row | status | facts it can rely on |
|---|---|---|
| Factor relative to free field, d → 0 | known | F1, F6 (2, 4, 8 = +3/+6/+9 dB) |
| Factor at 0.1 m, 1 kHz, rigid | known as derived | D1–D3 from F4/F5. Pure tone −0.6/−2.6/−10.7 dB; octave about −0.5/−1.6/−3.8 dB. Derivation, not a printed value. |
| Frequency range and distance condition | known | F2, F7 (significant when d < λ); the 1 dB limit at d/λ ≲ 0.07 and the crossovers at 700–860 Hz are derived |
| Ill-informed risk: conditions differ from the engine | flagged | All three sources assume coherent wave interference with rigid faces. The engine's scene has absorbing surfaces, and whether its ISM and tail model coherent near-boundary interference is a fact about `src/sim`, not a literature fact. The physics value applies to the engine only if the engine is meant to reproduce this wave effect. |
| Absorbing faces | uninformed | not found (§3) |

**Verdict for R-H1: READY**, with these limits:
- The rigid-wall factor, its range and its distance condition are known.
- The edge and corner values at 1 kHz are my derivation from a verified equation; Table II was not seen.
- The non-rigid case is still uninformed.
- The physics does not by itself say whether the engine's −6.2 dB is right or wrong. That requires knowing whether `src/sim` is meant to model coherent near-boundary radiation (Seat 2's ground, for 07e).

### Sources
- [Waterhouse 1958, scanned journal pp. 4–5 (trueaudio.com)](https://trueaudio.com/array/downloads/Waterhouse-Output%20of%20a%20sound%20source%201958.pdf)
- [DOI 10.1121/1.1909380](https://doi.org/10.1121/1.1909380), which redirects to pubs.aip.org/jasa/article/30/1/4/655630
- Corpus (rev c1b171f): `/home/user/makroof/docs/corpus/toole-sound-reproduction.md` §12.1; `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` §2.5, Eq. (2.50)
