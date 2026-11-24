SEAT 9 POSITION (phase 07c-2b, AX49 L4 stimuli; narrow brief: the label, and whether the scene needs a caveat about how representative it is; corpus c1b171f present)

**1. Reading**

The question: what item-9-style label should the L4 scene carry (T60_max ≈ 8 s, fully wet, probably the gated 100 m cube), and does the result need a caveat about which real rooms it stands for? Cues from my §4/§9 that apply: provenance (S8), D/R at the seat against the diffuse field, the "noise I ignore" rule (an RT quoted without position), and my §18 gap (no measured reference at this volume).

**Two corrections before any label is written:**

- **Do not call the L4 scene "low-α".** AX49's "100 m low-α cube" is the gated scene with T60_max 50.5 s (K22), where L_p ≥ L, so it has no provisional. That scene cannot host L4.
  - At V = 10⁶ m³ and S = 6×10⁴ m², a T60 of 8 s needs Sabine A_total = 0.161·10⁶/8 = 20,125 m².
  - Band with negligible air absorption (likely the T60_max band): Eyring ᾱ = 1 − e^(−20125/60000) = 0.285.
  - At 1 kHz (m = 1.08×10⁻³ m⁻¹, Kuttruff Table 6.1, 50 % RH, so 4mV = 4,320 m²): ᾱ ≈ 0.23.
  - Kuttruff's case 3 uses uniform α = 3/11 = 0.27, so this is moderate absorption, not low. Recommended wording: "the gated geometry (t_dir 0.118 s) with α raised to give T60_max 8 s".
- **The one-face clause does not carry over.** If Seat 2 names a uniform-α cube, the "one face at α 1, severe deviation from diffuse conditions" part of the item-9 qualifier does not apply. The closest corpus case is Table 5.2 case 1 (a cube with uniform α = 1/6): iteration 1.55 s against Eyring 1.47 s, +5.4 %, about 1 JND. The ᾱ clause of §5.6 still applies, because 0.23–0.29 is not small compared with 1.

**Label proposal** (Seat 2 fills the brackets with measured values)

- `label`: "Long-decay stress scene, 100 m cube with uniform absorption, T60_max 8 s; provisional-vs-exact tail test; stimulus scene, not a validated preset"
- Detail lines:
  1. 100 × 100 × 100 m (V 1.0×10⁶ m³, S 6.0×10⁴ m², mean free path 66.7 m). α [per band] on every face; s [value], AX21 if s < 1; tailSeed [ ]; fs [ ]; source–listener distance 40.5 m (t_dir 0.118 s).
  2. T60 per band (the engine's Eyring with air absorption). T60_max 8.0 s in band [b]; T60 at 1 kHz [ ] s.
  3. D/R at 1 kHz [measured] dB, against [−6.1] dB diffuse at r/r_c [2.02] (Eq. 5.44, Sabine A ≈ [20,100] m², r_c ≈ 20.0 m in the T60_max band; recompute at 1 kHz). Indicative only: Kuttruff §5.6 says these relations are questionable when ᾱ (≈ [0.23–0.29]) is not small.
  4. Kuttruff Table 5.2 case 1 (cube, uniform α): iteration +5.4 % against Eyring. The engine's tail follows Eyring.
  5. t_mix,e,max [1.118] s; L_f [3.61] s; L_p [3.71] s; L [ ] s.
  6. **Cut depth at release:** 60·L_p/T60_b below steady state, printed per band. In the T60_max band it is 60 × 3.714/8 = 27.9 dB.
  7. The early reflections are specular and sparse (mean free path 66.7 m). They are identical in A and B (the ISM is shared), so they are not the variable under test.
  8. Stimulus scene, not a room prediction. No measured reference room of this volume.
- Class line: "long-decay, [tail-dominated | near-balanced] (heard D/R [ ] dB), cut [27.9] dB below steady state in the T60_max band". The class follows my file-7 bands, applied to the measured heard D/R.

**Is a representativeness caveat needed? Yes, on two counts.**

1. **Volume.** 10⁶ m³ is outside every incident and reference I hold, so this point is `[Hyp]`. A T60 of 8 s is itself within what real rooms do: Toole puts cathedrals at "5 s or more" (toole-sound-reproduction L715). But those rooms are smaller and often coupled volumes with multi-slope decays (roginska-geluso L1098), and the engine does not render that. Label line 8 covers this.
2. **Scope of a non-detection.** L_f = t_mix,e + 0.312·T60, and t_mix,e grows with √V (K20). So at the same T60 a smaller room cuts earlier and louder. Example (`[Inf]`, my arithmetic): V = 5×10⁴ m³ with a listener at 20 m gives t_mix ≈ 0.058 + 0.224 = 0.282 s, L_p ≈ 2.88 s and a cut 21.6 dB below steady state. That is about 6 dB less deep than the cube's 27.9 dB. A non-detection on the cube should therefore be scoped as "cut depth ≥ 27.9 dB below steady state at T60_max", not as "T60 8 s".

**2–4. Ratings** (labelling only; anything else is NOT MY MATTER)

| option | rank | now | later | reason |
|---|---|---|---|---|
| L-b (harness) | prefer | 0 | 0 | The scene JSON and its SHA travel with the kit, and the stimulus never passes through a product binary. |
| L-a (render_cli flag) | can live with | 0 | 1 | A render_cli path that produces something other than the room's IR is a provenance risk. Condition: the manifest and the label record "provisional tail, validation-only flag". |
| L-c (later phase) | can live with | 0 | 1 | The label written now has to be redone if the scene or the AX49 constants change before it runs. |

**5. Evidence**

- Kuttruff Eq. 5.44 and §5.6 (corpus L2708, L2724).
- Kuttruff Table 5.2 cases 1 and 3 (L2786, L2788).
- Kuttruff Table 6.1 (L2832).
- Toole L715; Roginska L1098.
- AX49 K20, K22 and K15′ (L_p 3.71 s; I get 3.714 s).
- The arithmetic above is mine, redone from scratch. The air-absorption humidity the engine uses is not confirmed: Seat 2 should state it.

**6. Conditions**

- L-a: the "provisional tail, validation-only" line goes in the manifest and the label.
- Every option: the record states the cut-depth scope and leaves "low-α" out of the label.

**7. Hand-offs**

- **Seat 2:** name the per-band α and s; measure the D/R, ITDG, T60 per band and L.
- **Seat 1:** is a smaller-volume variant at T60 8 s (cut about 6 dB shallower) the more sensitive test under NFR-1?
- **Seat 7:** nothing from me.

**8. Premortem**

The non-detection gets read as "the provisional is inaudible at T60 8 s". A later scene with the same T60 and a smaller volume then puts the cut about 6 dB higher, and a producer hears it first, in a church-sized preset.
