# Room acoustics theory (K4)

Reference file of the `review-phase-pr` skill. Scope: image-source method for shoeboxes, pressure vs energy coefficients, scattering, pyroomacoustics ISM internals, ISO 9613-1 air absorption, Sabine/Eyring and alternatives, mixing time, hybrid IR construction, filterbanks and fractional delay, flutter echo. Phases 03, 04, 05, 08, 09, 12.

How to use it: read the "Reviewer's checklist" section first and apply the questions the diff makes
relevant; use the earlier sections to settle a disagreement with the author or to re-derive a number.
Every fact carries its source URL and the date it was verified (researched live on 2026-11-04).
Facts marked "(unverified, from memory)" must be verified before they are cited in a review; when
you verify one, fix it here. See `knowledge-inventory.md` for which facts go stale and how to
re-check them.

## Contents

- 1. Image-source method (ISM) for shoebox rooms
  - 1.1 Image positions (indices + parity)
  - 1.2 Path length, delay, spreading
  - 1.3 Allen–Berkley sampling issues, the "−1 sample" and the low-pass artefact
- 2. Pressure vs energy coefficients, scattering, angle dependence
- 3. pyroomacoustics ISM specifics (read from source, master branch, 2026-11-04)
- 4. Air absorption (ISO 9613-1:1993)
- 5. Reverberation-time theory
- 6. Mixing time and echo density
- 7. Hybrid IR construction, energy matching, seams, Schroeder frequency
- 8. Filterbanks and fractional-delay kernels
- 9. Diffuse-field assumptions and flutter echo
- 10. Reviewer's checklist (ISM / tail / filterbank diffs)
- Source list (accessed 2026-11-04)

---

Compiled 2026-11-04. Every fact carries its source and access date (all accessed 2026-11-04 unless
noted). Items marked **(unverified, from memory)** were not confirmed against a live source today.
Items marked **(computed)** were evaluated numerically today with the cited formula; the script is
reproducible from the formulas given. Project context: `docs/phases/phase-03.md`, `phase-04.md`,
`docs/BUILD_PLAN.md` §2 (AQ2, AQ3, AQ9, AX1, AX2, AX4, AX6).

Conventions used below: α = energy absorption coefficient, s = scattering coefficient, r = path
length [m], c = speed of sound [m/s], T60 in s, V in m³, S in m², m = energy air-attenuation
coefficient [1/m] (intensity ∝ exp(−m r)), a = air attenuation in dB/m.

---

## 1. Image-source method (ISM) for shoebox rooms

Primary reference: J. B. Allen, D. A. Berkley, "Image method for efficiently simulating small-room
acoustics", JASA 65(4), 943–950 (1979), DOI 10.1121/1.382599. The paper itself is only available as a
scanned PDF (http://users.umiacs.umd.edu/~ramanid/cmsc828d_audio/AllenBerkley79.pdf, no text layer), so
the formulas below are cross-checked against three live implementations of it:
pyroomacoustics `libroom_src/room.cpp` (https://github.com/LCAV/pyroomacoustics), Habets' RIR-Generator
`rir_generator_core.cpp` (https://github.com/ehabets/RIR-Generator), and MathWorks' ISM example
(https://www.mathworks.com/help/audio/ug/room-impulse-response-simulation-with-image-source-method-and-hrtf-interpolation.html).

### 1.1 Image positions (indices + parity)

- Room `[0,Lx]×[0,Ly]×[0,Lz]`, source `s`, receiver `r`. Per axis `d`, images lie on **two interleaved
  lattices of period 2L_d**:

  ```
  x_img,d = 2 n_d L_d + (-1)^{p_d} s_d       n_d ∈ Z,  p_d ∈ {0,1}
  ```
  p_d = 0: "unreflected" lattice (even), p_d = 1: mirrored lattice (odd).
  Allen–Berkley write this as R_p + R_r with R_p = (x ± x', y ± y', z ± z') (8 parity combinations)
  and R_r = 2(n Lx, l Ly, m Lz) **(unverified, from memory for the AB notation; the MathWorks code
  is `xyz = [n*2*Lx; l*2*Ly; m*2*Lz]`, `isourceCoord = xyz - sourceXYZ(:,p)` with 8 sign patterns —
  verified)**. arXiv 2405.03385 (Sec. III-A, https://arxiv.org/html/2405.03385v2) writes the same thing as
  `r_{q,ε} = ε ⊙ v_src + 2 q ⊙ v_L`, ε ∈ {−1,1}³, q ∈ Z³ ("eight distinct translated orthogonal lattices
  of common mesh size 2Lx × 2Ly × 2Lz").
- **Single-integer form (pyroomacoustics):** one index k_d ∈ Z per axis, `loc[d] = k_d·L_d + step`,
  `step = (|k_d| % 2 == 1) ? L_d − s_d : s_d` (room.cpp `image_source_shoebox`, verified). So
  k even → 2nL + s; k odd → (k+1)L − s. Equivalent to the two-lattice form with k = 2n (p=0) or
  k = 2n − 1 (p=1).
- **Reflection order** = Σ_d |k_d| (room.cpp: "source order is just the sum of absolute values of
  reflection", `is.order += abs_point`; verified). pyroomacoustics enumerates the **L1 ball**
  ("Walk on all the points of the discrete L1 ball of radius ism_order": y_max = N − |k_z|,
  x_max = y_max − |k_y|), i.e. exactly the images with Σ|k_d| ≤ N. Enumerating the cube |k_d| ≤ N
  instead gives (2N+1)³ images with orders up to 3N — a different "max_order" semantics.
- **Reflection count per surface** (needed for Π √(1−α_wall)^hits). With wall "0" at x=0 and wall
  "L" at x=L, for index k (**derived, consistent with AB exponents |n−q| and |n|, verified against
  RIR-Generator `pow(beta[0], abs(mx-q)) * pow(beta[1], abs(mx))` and MathWorks
  `BX1.^abs(n-q(p)) .* BX2.^abs(n)`**):

  ```
  k >= 0:  hits_wall0 = floor(k/2),   hits_wallL = ceil(k/2)
  k <  0:  hits_wall0 = ceil(|k|/2),  hits_wallL = floor(|k|/2)
  ```
  Checks: k=−1 → image at −s, 1 hit on wall 0; k=+1 → image at 2L−s, 1 hit on wall L; k=±2 → 1 hit each;
  k=−3 → 2 hits on wall 0, 1 on wall L. The sum is always |k|.
  Common bug: assigning the odd-order extra hit to the wrong wall (sign of k), which is invisible
  with symmetric materials and only shows with `asymmetric_materials` fixtures.
- **Number of images up to order N (L1 ball, 3-D):**

  ```
  count(N) = (4N³ + 6N² + 8N + 3) / 3        shell(n) = 4n² + 2 for n ≥ 1, shell(0) = 1
  N=1: 7   N=2: 25   N=3: 63   N=10: 1561   N=30: 37 881   N=60: 295 361   (computed, brute force)
  ```
  Growth O(N³). The cube enumeration gives (2N+1)³ = 1 771 561 at N=60.
- **Why no visibility test in a shoebox:** every lattice image is the mirror image of the source
  through a sequence of the six planes; the straight segment image→receiver crosses exactly the wall
  planes implied by (k_x,k_y,k_z), and a convex box has nothing to occlude it. pyroomacoustics
  literally sets `is.visible_mics.setOnes();  // everything is visible` (room.cpp, verified). JASA
  review note: "every image source contributes to the total impulse response (unless there are
  obstacles in the room)" (https://pubs.aip.org/asa/jasa/article/158/5/R9/3371770).

### 1.2 Path length, delay, spreading

- r = ‖x_img − r_listener‖, τ = r/c, pressure amplitude ∝ 1/r.
- **4π convention differs between tools:** RIR-Generator uses `/(4*M_PI*dist*cTs)` (verified);
  pyroomacoustics uses `oct_band_amplitude = att / dist` (ism.py, verified, no 4π); AB 1979 uses
  1/(4π|R_p+R_r|) **(unverified, from memory)**. 4π = 22.0 dB absolute offset. The project's AX2
  (gain 1.0 at 1 m) matches pyroomacoustics; **compare amplitudes relative to the direct path**, never
  absolute, when cross-checking (phase-03 criterion already says "relative to the direct sound").
- **Speed of sound:** c = 331.3·√(1 + T_C/273.15) m/s = 20.05·√(T_K) → 343.2 m/s at 20 °C
  (https://www.omnicalculator.com/physics/speed-of-sound; computed: 343.21). Linear approximation
  331.3 + 0.606·T_C. ISO 9613-1 and most texts quote 343.2 at 20 °C; pyroomacoustics' constant is
  `"c": 343.0  # speed of sound at 20 C in dry air` (parameters.py, verified) and its temperature model
  is `331.4 + 0.6*t + 0.0124*h` (parameters.py line 247, verified; → 343.4 at 20 °C, h=0).
  **Pitfall:** 343.0 vs 343.2 is 0.06%; on a 20 m path (2799 samples at 48 kHz) that is 1.6 samples —
  enough to fail a ±1-sample test. Use the same c in both engines (`pra.constants.set("c", 343.0)` or
  rely on the default 343.0; do **not** pass `temperature=20`, which switches to 343.4).

### 1.3 Allen–Berkley sampling issues, the "−1 sample" and the low-pass artefact

- AB 1979 placed each image as a single impulse at the **rounded** integer sample
  (**unverified, from memory**; MathWorks reproduces this: `delay = (fs/c).*dist; ... round(delayV)`,
  verified). Rounding error ≤ 0.5 sample → random phase errors at HF, and coincident delays collide
  (noted for GPU ISM: https://link.springer.com/article/10.1007/s11042-015-2943-4).
- Peterson 1986 (JASA 80(5) 1527–1529) replaced the impulse by a **low-pass impulse** (windowed sinc at
  fractional position). RIR-Generator implements it (rir_generator_core.cpp, verified):

  ```
  Fc = 0.5 (normalized, i.e. Nyquist);  Tw = 2*ROUND(0.004*fs)   // 8 ms Hann-windowed sinc
  t = (n - 0.5*Tw + 1) - (dist - fdist);  LPI[n] = 0.5*(1+cos(2π t/Tw)) * 2Fc * sinc(π 2Fc t)
  startPosition = (int) fdist - (Tw/2) + 1
  ```
  Changelog entry "2.1.20141124 + The window and sinc are now both centered" (verified): earlier
  versions had the window and the sinc offset by one sample — this is the origin of the frequently
  quoted "one-sample" discrepancies between ISM generators. Expect ±1-sample differences between tools
  from (a) `floor` vs `round` of the integer part, (b) window/sinc centring, (c) even-length kernels
  (Tw is even here → the kernel centre sits at a half-sample) and (d) an explicit global offset (see
  pyroomacoustics `fdl2` below).
- **High-pass filter:** AB's original code and RIR-Generator apply a 100 Hz IIR high-pass by default
  (`W = 2π·100/fs; // The cut-off frequency equals 100 Hz`, `hp_filter` default on; verified).
  pyroomacoustics applies a zero-phase 2nd-order Butterworth at 10 Hz by default
  (`rir_hpf_enable: True`, `rir_hpf_fc: 10.0`, `sosfiltfilt`; verified). Both change LF content and
  the 63 Hz band of any comparison; a causal 100 Hz HPF also shifts peak positions slightly.
- **Low-pass artefact:** a Hann-windowed sinc of finite length is not flat up to Nyquist; the response
  droops in the top ~10 % of the band and the shorter the kernel the earlier the droop
  **(unverified, from memory — standard windowed-sinc behaviour, see §8)**. Comparing a 33-tap Kaiser
  kernel against pyroomacoustics' 81-tap Hann kernel band-limits differently above ~20 kHz at 48 kHz;
  irrelevant below 8 kHz, so restrict per-band comparisons to ≤ 8 kHz.

---

## 2. Pressure vs energy coefficients, scattering, angle dependence

- **Reflection factor on pressure** |R| = √(1−α); α = 1 − |R|² is the definition of the (energy)
  absorption coefficient (ETH acoustics slides, https://people.ee.ethz.ch/~isistaff/courses/ak1/acoustics-absorption-reflection.pdf,
  "α = 1 −|R|²"). AB's β is this pressure factor; MathWorks: `B = sqrt(1-A);` "Derive the pressure
  reflection coefficients from the absorption coefficients" (verified). pyroomacoustics wall.hpp:
  `transmission; // computed from absorption as sqrt(1 - a)` and `energy_reflection; // computed from
  absorption as (1 - a)` (verified). arXiv 2405.03385 defines amplitude via α̂ = 1 − â².
- **Classic error:** multiplying pressure by (1−α) per hit. Effect: a wall with α = 0.3 loses 3.1 dB
  per hit instead of 1.55 dB; order-3 reflections are 4.6 dB too quiet; T60 of the early part halves.
  Dual error: applying √ twice (√(1−α) on energy). A ±0.5 dB cross-check against pyroomacoustics at
  α = 0.3 catches both at first order.
- **Scattering coefficient** s (ISO 17497-1:2004): fraction of *reflected* energy sent into
  non-specular directions, s = 1 − E_spec/E_reflected, 0..1, frequency dependent
  (https://acousplan.com/learn/what-is-acoustic-diffusion; https://en.wikipedia.org/wiki/Diffusion_(acoustics)).
  Per hit: specular energy = (1−α)(1−s); scattered energy = (1−α)·s; pressure on the specular path
  = √(1−α)·√(1−s). The scattered part is *not lost*; it feeds the diffuse field and must be re-injected
  into the tail or total energy drops (Wayverb: "energy lost from specular paths is supplied by the
  diffuse ray-tracer output", https://reuk.github.io/wayverb/hybrid.html). Phase-03's "scattered
  energy list" + phase-04 energy matching is exactly this bookkeeping.
- **pyroomacoustics applies √(1−s) to ISM amplitudes only in hybrid mode**:
  `if (shoebox_scattering.maxCoeff() > 0.f && is_hybrid_sim) { transmission_pwr[1] *= (1 - shoebox_scattering).sqrt(); }`
  with `is_hybrid_sim = ism_needed and rt_needed` (room.py line 1016, verified). **Pure-ISM
  pyroomacoustics ignores scattering entirely.** A cross-check with s > 0 must either set s = 0 (what
  phase-03 does) or enable `ray_tracing=True` and compare only the early part.
- Wayverb multiplies "each surface's reflectance" by (1−s) (not √(1−s)); whether its reflectance is a
  pressure or energy quantity is not stated on the page — do not copy that line without checking.
- **Random-incidence vs angle-dependent:** published α tables are random-incidence values from a
  reverberation room (ISO 354). A real locally-reacting surface has a complex, angle-dependent
  pressure reflection factor R(θ) = (Z cosθ − ρc)/(Z cosθ + ρc) **(unverified, from memory; Kuttruff,
  Room Acoustics, ch. 2)**; ISM with a real, angle-independent √(1−α) ignores phase (no sign flips, no
  comb effects from phase shifts) and grazing-incidence behaviour. This is the accepted approximation
  (pyroomacoustics, RIR-Generator, Wayverb all do it); treat per-reflection level errors of a few dB at
  grazing incidence as model error, not a bug (NFR-8: don't tune).
- **Ranges and clamps:** AQ3 fixes α ∈ [0.01, 1.0]. α = 0 is excluded because Eyring's −S ln(1−ᾱ) → 0
  gives T60 → ∞ (and an infinite IR); α = 1 makes √(1−α) = 0 so the image disappears (all-α=1 ⇒ direct
  path only — phase-03 "Limits" test). ISO 354 measurements can report α > 1 (edge effect); any code
  that computes √(1−α) must clamp α ≤ 1 first or it produces NaN. Phase-04 clamps ᾱ_b ≤ 0.999.

---

## 3. pyroomacoustics ISM specifics (read from source, master branch, 2026-11-04)

Sources: https://raw.githubusercontent.com/LCAV/pyroomacoustics/master/pyroomacoustics/{room.py,parameters.py,simulation/ism.py,experimental/rt60.py,acoustics.py,libroom_src/room.cpp,libroom_src/rir_builder.cpp}
and docs https://pyroomacoustics.readthedocs.io/en/latest/pyroomacoustics.room.html.

- **Material → amplitude:** `Material(energy_absorption=α)` stores `{"coeffs": [α]}`; `absorption_coeffs`
  returns these energy values to the C++ engine; per image the engine computes
  `transmission_pwr[1] = (1.f - shoebox_absorption).sqrt();` and `transmission_pwr[i] = transmission_pwr[i-1] * transmission_pwr[1]`,
  then multiplies `is.attenuation *= transmission_pwr[p1].col(2*d)` ("west") and `transmission_pwr[p2].col(2*d+1)` ("east").
  So yes: **√(1−α) per hit, per band**, and the Python side uses `source.damping = room_engine.attenuations.copy()`
  directly (`att / dist`, no further sqrt). Default material when none given: `Material(energy_absorption=0.0)` (rigid).
- **Wall names/order:** `["west","east","south","north","floor","ceiling"]` = x-min, x-max, y-min, y-max,
  z-min, z-max ("W/E is for axis x, S/N for y-axis, F/C for z-axis"). Map the project's six surfaces
  carefully; a swapped pair is invisible with uniform materials.
- **Scattering:** only with `ray_tracing=True` (see §2). `Material(energy_absorption, scattering=None)` → s = 0.
- **air_absorption:** constructor default `air_absorption=False`. When True, `Physics.get_air_absorption()`
  selects a **tabulated** 7-band energy coefficient (1/m), not ISO 9613-1:
  `"20C_50-70%": [0.1, 0.3, 0.6, 1.0, 1.7, 4.1, 13.5] × 1e-3` for centres `[125,250,500,1000,2000,4000,8000]`
  (branches: T<15 → "10C_", else "20C_"; H<50 → "30-50%", 50≤H<70 → "50-70%", else "70-90%"; note the
  `key = "20C_"` assignment instead of `+=`, harmless). Applied as `exp(-0.5 * m * dist)` on amplitude
  (ism.py `apply_air_aborption`, sic). Compared to ISO 9613-1 at 20 °C/50 % (§4: m = 1.07e-3 at 1 kHz,
  6.8e-3 at 4 kHz, 24.2e-3 at 8 kHz) the table is ~40–45 % low at 4–8 kHz. **Do not cross-check air
  absorption against pyroomacoustics**; keep it off in the comparison (phase-03 does).
- **Fractional delay and global offset:** `frac_delay_length = 81` (odd, Hann-windowed sinc, LUT with
  `sinc_lut_granularity = 20`). In `compute_ism_rir` (the normal branch, no impulse-response
  directivities): `fdl2 = fdl // 2` (= 40); `delay = fdl2 / fs; time += delay` ("we add the delay due to
  the fractional delay filter to the arrival times to avoid problems when propagation is shorter than
  the delay of the filter"); buffer `N = ceil(t_max*fs + fdl2 + 1) + 1`. In `rir_builder.cpp` the kernel is
  centred: `fdl2 = (fdl-1)/2`, taps written at `f = int(time_ip) - fdl2 + k`, k = 0..fdl−1, with
  `time_ip = floor(fs*t)`, `time_fp = frac`. Net: **the returned RIR is delayed by exactly 40 samples**
  (docs: `global_delay = pra.constants.get("frac_delay_length") // 2`). For a ±1-sample test, subtract
  40 (at any fs — it is a sample count, not a time) or compare arrival times relative to the direct peak.
- **Octave-band filtering** is applied only when a material has > 1 band (`n_bands > 1`):
  `rir += octave_bands.analysis(ir_loc, band=b)` with `fftconvolve(..., mode="same")` (no extra delay).
  `OctaveBandsFactory(base_frequency=125.0, n_fft=512, keep_dc=...)`, `n_bands = floor(log2(fs/125))`
  (at 48 kHz: 8 bands, 125 Hz … 16 kHz — **not the project's 63 Hz–8 kHz set**), band edges
  `f/√2 … f·√2`. The `rir = rir[n_fft//2:]` trim exists only in the impulse-response-directivity branch.
  Frequency-flat α (phase-03 cross-check) → 1 band → no filtering at all. `min_phase=False` default.
- **Other defaults:** `fs=8000` (!), `max_order=1` ("direct sound and first order reflections"),
  `use_rand_ism=False` (randomised ISM with `max_rand_disp` ≈ 0.08 m — must stay False for exact
  comparisons), `t0=0.0`, `rir_hpf_enable=True` at 10 Hz (zero-phase; set `pra.constants.set("rir_hpf_enable", False)`
  for exact peak amplitudes, otherwise sub-0.1 dB changes and LF pre-ringing).
- **Direct path:** included (order 0, k = (0,0,0)); `max_order=0` gives direct only.
- **Indexing:** `room.rir[mic][src]` — outer list microphones, inner sources ("the outer list is on
  microphones and the inner list over sources"; `room.rir[1][0]` = mic 1, source 0).
- **`pra.experimental.measure_rt60(h, fs=1, decay_db=60, energy_thres=1.0, plot=False, rt60_tgt=None, label=None, linear_domain_fit=False)`:**
  Schroeder backward integration of h², dB relative to the first sample; start = first index below
  −5 dB; end = first index below (start − decay_db); if the available range is < decay_db + 5 dB it
  **silently reduces decay_db** to what is available; least-squares line in dB over that range,
  returns `-60 / slope` (a single float, in seconds if fs is given, **in samples if fs is left at 1**).
  Returns 0.0 if the EDC never drops 5 dB. `plot` only draws (EDC, fit, −5/−60 dB lines, estimate,
  optional `rt60_tgt` line); it does not change the result. `Room.measure_rt60(decay_db=60, plot=False)`
  loops over rir[m][s] and returns an array (n_mics, n_sources). Use `decay_db=30` to get an ISO-style
  T30 (−5…−35 dB); the project's `metrics.py` should be compared with that, not the default.

---

## 4. Air absorption (ISO 9613-1:1993)

Formulas verified against python-acoustics' implementation
(https://github.com/python-acoustics/python-acoustics/blob/master/acoustics/standards/iso_9613_1_1993.py)
and sengpielaudio (https://sengpielaudio.com/AirdampingFormula.htm); constants T0 = 293.15 K,
T01 = 273.16 K (triple point), pr = 101.325 kPa, pa in kPa, T in K, hr = relative humidity in %, f in Hz.

```
psat/pr = 10^( -6.8346·(T01/T)^1.261 + 4.6151 )                      (→ psat = 2.337 kPa at 20 °C, computed)
h       = hr · (psat/pr) / (pa/pr) = hr · psat / pa                   (molar concentration of water vapour, %)
frO     = (pa/pr) · ( 24 + 4.04e4 · h · (0.02 + h)/(0.391 + h) )      (oxygen relaxation frequency, Hz)
frN     = (pa/pr) · (T/T0)^(-1/2) · ( 9 + 280·h·exp(-4.17·((T/T0)^(-1/3) - 1)) )   (nitrogen, Hz)
a [dB/m] = 8.686 · f² · ( 1.84e-11 · (pa/pr)^(-1) · (T/T0)^(1/2)
                        + (T/T0)^(-5/2) · ( 0.01275·exp(-2239.1/T) / (frO + f²/frO)
                                          + 0.1068 ·exp(-3352/T)   / (frN + f²/frN) ) )
```
At 20 °C, 50 % RH, 101.325 kPa: h = 1.153 %, frO = 35 414 Hz, frN = 331.9 Hz (computed).

**Table at 20 °C / 50 % RH / 101.325 kPa (computed with the formula above; cross-checked against the
ISO 9613-1 table reproduced in ScienceDirect "Atmospheric attenuation" overview,
https://www.sciencedirect.com/topics/engineering/atmospheric-attenuation: 63 Hz 0.123, 125 Hz 0.445,
250 Hz 1.32 dB/km — agreement within 1.5 %):**

| f [Hz] | a [dB/km] | a [dB/100 m] | a [dB/m] | amplitude [Np/m] = a/8.686 | energy m [1/m] = a/4.343 |
|---|---|---|---|---|---|
| 63   | 0.122  | 0.0122 | 1.22e-4 | 1.41e-5 | 2.8e-5  |
| 125  | 0.440  | 0.044  | 4.40e-4 | 5.07e-5 | 1.01e-4 |
| 250  | 1.31   | 0.131  | 1.31e-3 | 1.51e-4 | 3.02e-4 |
| 500  | 2.73   | 0.273  | 2.73e-3 | 3.14e-4 | 6.28e-4 |
| 1000 | 4.66   | 0.466  | 4.66e-3 | 5.37e-4 | 1.07e-3 |
| 2000 | 9.89   | 0.989  | 9.89e-3 | 1.14e-3 | 2.28e-3 |
| 4000 | 29.7   | 2.97   | 2.97e-2 | 3.41e-3 | 6.83e-3 |
| 8000 | 105.3  | 10.5   | 1.05e-1 | 1.21e-2 | 2.42e-2 |

- The standard tabulates **pure-tone** values at one-third-octave frequencies; using the band-centre
  value for an octave band is an approximation (Appl. Sci. 2024, https://doi.org/10.3390/app142210139).
  Phase-03's "±5 % of table values at band centres" is a test of the formula, not of band averaging.
- **Unit conversions (exact):** 1 Np = 20·log10(e) dB = 8.6859 dB. Amplitude attenuation
  α_Np/m = a_dB/m / 8.686. **Energy/intensity** coefficient m [1/m] with I(r) = I0·exp(−m r):
  m = a_dB/m / (10·log10 e) = a_dB/m / 4.343 = 2·α_Np/m. Pressure along a path:
  p(r) ∝ 10^(−a·r/20) = exp(−m r/2) (this is pyroomacoustics' `exp(-0.5*m*d)`).
- **Pitfall (phase-04):** Eyring's `4mV` needs the *energy* m (= a/4.343). Converting with 1/8.686
  ("nepers/m") halves the air term; at 8 kHz in a 6000 m³ hall (4mV = 580 m² vs S ≈ 2000 m²·ᾱ) that
  is a visible T60 error in the top band. Phase-04 text says "nepers/m (from AirAbsorption, converted)"
  — review which factor is used.
- **Pitfall:** applying air absorption twice (once per image in the ISM and again as a global
  per-band filter, or in the ISM and again in the tail's T60 *and* on the tail's seed energy).

---

## 5. Reverberation-time theory

- **Sabine:** T60 = (24·ln10 / c) · V / (A + 4mV), A = Σ α_i S_i. 24·ln10/343 = 0.1611 (computed);
  Wikipedia gives "24 ln 10 / c20 ≈ 0.1611 s·m⁻¹" (https://en.wikipedia.org/wiki/Reverberation).
  Texts use 0.16, 0.161, 0.163 (c = 340 → 0.1625) or 0.164 (Sabine's own experimental value)
  (Gdańsk paper, https://sound.eti.pg.gda.pl/papers/prediction_of_reverberation_time.pdf, pdftotext
  of the saved copy). Derivation: diffuse energy density decays as exp(−c A t / 4V) (mean free path
  4V/S, absorption ᾱ per hit); T60 = ln(10⁶)·4V/(cA) = 24 ln10 · V/(cA).
- **Eyring (Eyring–Norris 1930):** T60 = 0.161·V / ( −S·ln(1−ᾱ) + 4mV ), ᾱ = Σ α_i S_i / S
  (area-weighted). Sabine and Eyring "are equal for coefficient values smaller than 0.2"
  (Forum Acusticum 2002 review, http://www.conforg.fr/acoustics2008/cdrom/data/fa2002-sevilla/forumacusticum/archivos/arcgen015.pdf);
  since −ln(1−ᾱ) > ᾱ, Sabine always predicts the longer T60 and "tends to over-predict reverberation
  time for small rooms with high amounts of absorption" (Wikipedia). Eyring → 0 as ᾱ → 1 (correct:
  anechoic), Sabine → 0.161 V/S (wrong). Millington–Sette: −Σ S_i ln(1−α_i) instead (same source).
- **Non-uniform absorption** (one absorbent ceiling, audience floor): both formulas assume a diffuse
  field and misestimate, typically under-predicting T60 (the decay is governed by the "hard" axis).
  Alternatives, all with ᾱ_x, ᾱ_y, ᾱ_z = area-weighted means of each pair of opposite walls,
  S_x, S_y, S_z = their areas (S_x + S_y + S_z = S):

  ```
  Fitzroy (1959):      T = 0.16·V/S² · ( −S_x/ln(1−ᾱ_x) − S_y/ln(1−ᾱ_y) − S_z/ln(1−ᾱ_z) )
                       (= arithmetic mean of three directional Eyring times, weights S_i/S)
  Arau-Puchades (1988): T = Π_i [ 0.16·V / ( −S·ln(1−ᾱ_i) + 4mV ) ]^(S_i/S)
                       (= geometric mean, weights S_i/S)
  ```
  (Gdańsk eq. 10 and 13; FA2002 eqs. with 0.163; both verified by pdftotext.) FA2002 found Arau best
  for tonal shape and values; Fitzroy gives the highest T60s. Phase-04's risk note is correct;
  record deviations as model inputs for phase 05, no per-scene tuning (NFR-8).
- **6.91 and 13.8:** 10^(−60/20) = 10⁻³ → ln(10³) = 3·ln10 = **6.9078** (amplitude);
  10^(−60/10) = 10⁻⁶ → ln(10⁶) = 6·ln10 = **13.8155** (energy). 20·log10(exp(−6.908)) = −60.00 dB (computed).
- **Which envelope for a noise tail — resolved:** let n(t) be stationary noise with E[n²] = 1 and
  the tail be h(t) = g(t)·n(t). Its energy envelope is E[h²] = g²(t). The target is a 60 dB *energy*
  drop at T60: g²(T60)/g²(0) = 10⁻⁶ ⇒ g(t) = exp(−6.908·t/T60) (amplitude) ⇔ g²(t) = exp(−13.816·t/T60).
  So: **multiply the noise amplitude by exp(−6.91 t/T60)** (phase-04's e_b(t) is written correctly as
  an amplitude envelope). Bugs: (a) multiplying amplitude by exp(−13.8 t/T60) → measured T60 = T60/2;
  (b) multiplying amplitude by exp(−6.91 t/(2·T60)) or energy by exp(−6.91 t/T60) → measured 2·T60;
  (c) generating the envelope as 10^(−60 t/(20 T60)) on amplitude is correct and equals (a) — mixing
  10^(−3 t/T60) (amplitude) with a "/10" in the exponent is the same factor-2 bug.
  Quick check: dB(t) = 20·log10 g(t) must be −60·t/T60; with energy measured as 10·log10 of
  Schroeder's ∫h² this gives exactly −60 dB at T60.
- **Per-band T60 and evaluation range:** ISO 3382-1 T30 = fit over −5…−35 dB ×2, T20 = −5…−25 dB ×3,
  EDT = 0…−10 dB ×6 (Wikipedia describes the ×3/×2 rule) — the IR must contain ≥ 45 dB of dynamic
  range above the truncation point in every band for T30; truncation that is too short biases T30
  low. With pyroomacoustics' `decay_db=60` default the fit range is −5…−65 dB (needs 70 dB range)
  and is silently shortened otherwise — the project's `metrics.py` must pin the range explicitly.
- **Initial level of the diffuse tail (energy matching reference, derived, unverified):** with image
  density dN/dt = 4π c³ t²/V and per-image energy (1/r²)·exp(−13.8 t/T60) with r = c t, the expected
  ISM energy per unit time at t is (4π c/V)·exp(−13.8 t/T60) relative to a direct path of 1 at 1 m —
  the "statistical model predicts" curve phase-04 extrapolates from the ISM window.

---

## 6. Mixing time and echo density

Source: Lindau, Kosanke, Weinzierl, "Perceptual evaluation of model- and signal-based predictors of the
mixing time in binaural room impulse responses", JAES 60(11), 887–898, Nov 2012
(https://www2.users.ak.tu-berlin.de/akgroup/ak_pub/2012/Lindau_2012a_Mixing_Time.pdf, text extracted
with pdftotext; equation numbers are the paper's).

- Reflection density from the mirror-source model of a rectangular room (eq. 1):
  `dN/dt = 4π c0³ t² / V`.
- Setting dN/dt = 400 s⁻¹ and solving gives the popular `t_mp ≈ √V` (t in ms, V in m³) (eq. 2) —
  Lindau attributes it to Cremer & Müller [16]; it is also widely cited as Polack (1988/1993)
  **(attribution to Polack: unverified, from memory)**. General form: t = √( n0·V / (4π c³) );
  with n0 = 400, c = 343: 0.888·√V ms (computed) ≈ √V ms. The generic estimator eq. (6):
  `t_mp1 = k_refl · √V`.
- Rubak & Johansen: mean free path l_m = 4V/S (eq. 3); t_mp ≈ 4·l_m·1000/c0 ≈ 47·V/S ms (eq. 4).
- Hidaka et al.: t_m,500Hz = 80·RT_500Hz ms (eq. 5).
- Perceptual results (9 shoebox-like rooms, 182–8500 m³, ᾱ 0.17–0.36, RT 0.39–2.36 s):
  ```
  t_mp50 = 20·V/S + 12   [ms]   R² = 81.5 %   (eq. 12, best model predictor)
  t_mp50 = 0.58·√V + 21.2 [ms]  R² = 78.6 %   (eq. 13)
  t_mp95 = 0.0117·V + 50.1 [ms] R² = 78.7 %   (eq. 14, "perceptively perfect" for 95 % of listeners)
  signal-based: t_mp50 = 0.8·t_mix,AbelI − 8;  t_mp95 = 1.8·t_mix,AbelI − 38 (eqs. 15, 16)
  ```
  Interpretation in the paper: diffuse after "approximately two reflections"; just-audible reflection
  density ≈ 171 s⁻¹ — far below the 400–10 000 s⁻¹ traditionally assumed.
- Project (phase-04) uses t_mix = max(20 ms, √V ms): for V = 72 m³ → 20 ms (clamped), V = 6000 m³ →
  77 ms (Lindau t_mp50 ≈ 66 ms, t_mp95 ≈ 120 ms). √V is a defensible, citable choice (cite Lindau 2012
  eq. 2 / Cremer & Müller); it sits between t_mp50 and t_mp95 for large rooms and above t_mp50 for
  small ones.
- **Coverage check:** ISM of order N covers time ≈ N·(4V/S)/c. For a 6×4×3 m room 4V/S = 2.67 m →
  order 8 reaches 60 ms; a 20×30×10 m room (4V/S = 10.9 m) needs order ≈ 2.5 per 80 ms. Phase-04's
  "clamp t_mix to the time the requested ISM order covers" must use the **minimum** image distance of
  the last complete shell (≈ N·min(L_d)), not the mean, or the seam lands in a region where the ISM is
  incomplete (missing late images of that shell → energy dip before t_mix).
- **Echo density (Abel & Huang 2006, AES 121st, e-lib 13819):** sliding window (Lindau: rectangular,
  210 samples), fraction of samples with |h| > σ_window, normalised by the Gaussian expectation
  erfc(1/√2) = 0.3173 (computed); profile rises to 1; mixing time = first time it reaches 1
  (criterion I) or stays within 1σ of its late value (criterion II). Useful as a seam test
  (a jump in echo density at t_mix is a seam).

---

## 7. Hybrid IR construction, energy matching, seams, Schroeder frequency

- **Energy matching:** match band energy per unit time of ISM and tail at the junction. Wayverb
  equalises direct-sound energy of both models analytically (E_is = E_src/(4πr²)) and then sums with
  no further adjustment; it adds specular ray contributions only above the ISM order and lets the
  "image-source response fade as the diffuse ray-traced reflections grow"
  (https://reuk.github.io/wayverb/hybrid.html). Salvati 2026 (IEEE TASLP) matches decaying-noise tail
  energy to the early part at the transition and then tunes the tail level to the target RT
  (https://signalprocessingsociety.org/publications-resources/ieee-transactions-audio-speech-and-language-processing/2026/09/hybrid-multichannel-room-impulse-response-generation-joint-reverberation-time-and-diffuse).
- **Scattered energy re-injection:** the specular ISM loses (1−α)·s per hit; the diffuse field gains it.
  Standard practice: either (a) run the tail from the *un-scattered* statistical level (Eyring uses α
  only; scattering does not change total energy) — then the ISM window energy used for matching must
  have the scattered energy added back, which is what phase-04 specifies; or (b) ray-trace it
  (Wayverb). Omitting it makes rooms with high s sound too dry at t_mix and produces a step up in the
  EDC after the tail starts if the tail is matched to Eyring instead of to the ISM.
- **Double counting:** ISM contributions after t_mix must be dropped (or faded) when the tail starts,
  otherwise energy after t_mix is counted twice (Wayverb: "specular energy can be counted twice").
  Phase-04 drops ISM after t_mix — the crossfade window must therefore cover the same region on both.
- **Crossfade windows:** ISM and noise tail are uncorrelated, so the energy-preserving crossfade is
  **equal-power**: amplitude gains cos(θ), sin(θ), θ: 0→π/2, cos²+sin² = 1. "Complementary cos²
  windows" applied as amplitude gains cos²(θ) and sin²(θ) (equal-gain, sum = 1) give a power sum of
  cos⁴+sin⁴ = 0.5 at mid-fade → −3 dB dip (computed). Over a 5 ms fade this is a small notch in the
  EDC; phase-04's "no step > 1 dB in a 5 ms window" test may or may not catch it depending on window
  placement. Read the code: cos²/sin² as *power* weights (amplitude cos/sin) is correct.
- **Other common seams:** (1) tail noise starting at t = 0 and merely gated, so its envelope at t_mix
  is already attenuated by exp(−6.91 t_mix/T60) relative to E_b — fine if E_b is defined at t_mix, a
  level error if E_b was defined at t = 0; (2) measuring the ISM energy in a 10 ms window with too few
  images (small rooms at low order: dozens of images → ±3 dB noise) — use a wider window or the
  analytic (4πc/V)·exp(−13.8t/T60) expectation; (3) filterbank group delay not removed identically on
  ISM and tail → tail starts (L−1)/2 samples late; (4) band energies (sum of squares) matched where
  amplitudes (RMS) were meant, or per-sample energy vs per-window energy mismatch (window length
  factor); (5) tail generated at a different sample rate but energy matched in samples instead of
  seconds (phase-04 has a 44.1/96 kHz test for this).
- **Schroeder frequency:** f_s = 2000·√(T/V) (T in s, V in m³) — the modal-overlap threshold (3-fold
  overlap; Schroeder's 1954 criterion with 10-fold overlap gives 4000·√(T/V))
  (https://strutt.arup.com/help/Building_Acoustics/SchroederFreq.htm; derivation with modal density
  4πV f²/c³ and modal bandwidth 2.2/T; https://acoustics.ippt.pan.pl/index.php/aa/article/download/739/649).
  Examples (computed): 50 m³/0.5 s → 200 Hz; 200 m³/0.6 s → 110 Hz; 6000 m³/2 s → 37 Hz. Below f_s the
  field is modal: Gaussian-noise tails and Eyring decay are not physically valid, the ISM's dense
  sum does reproduce modes (it is exact for rigid walls, arXiv 2405.03385) but the real-valued
  √(1−α) makes the modal damping approximate. Hence phase-04's wider tolerance at 125 Hz and no gate
  at 63 Hz; and validation against BRAS (phase 05) should be read per band with f_s in mind.

---

## 8. Filterbanks and fractional-delay kernels

- **Linear-phase FIR:** symmetric h[n] = h[L−1−n], odd L → integer group delay (L−1)/2 samples at
  all frequencies; even L → half-sample delay (avoid for peak-time tests).
- **Perfect reconstruction by construction (complementary design):** for complementary FIR pairs
  δ[n] = h_L[n] + h_H[n] holds with a delayed impulse when the prototype is linear-phase and the
  impulse is added "at the center of symmetry" (https://vhdlwhiz.com/part-6-complementary-fir-filters/;
  https://www.advsolned.com/?p=17540; works for odd-tap linear-phase filters). Octave bank: design
  K−1 lowpass prototypes P_k (all odd length L, same L, crossovers at 63·√2·2^k Hz), then
  band_0 = P_0, band_k = P_k − P_{k−1}, band_top = δ[(L−1)/2] − P_{K−2}. Then Σ_k band_k = δ[n−(L−1)/2]
  exactly (to float rounding, i.e. < −100 dB when done in double) *regardless of the prototype quality*.
  The −100 dB flat-sum test therefore does **not** validate band isolation; the neighbour-band ≥ 20 dB
  test does. Note: amplitude-complementary (sum = 1) is not power-complementary (Σ|H|² = 1); for
  uncorrelated per-band signals (the noise tail!) the band overlap region has energy ≠ sum of band
  energies — matching band energy must use the same filterbank on both sides (phase-04 reuses it).
- **Length/latency reality check (Kaiser estimate, computed):** transition width Δf = 20 Hz at
  48 kHz with 60 dB attenuation needs N ≈ (A−7.95)/(2.285·Δω)+1 ≈ 8700 taps (80 dB: 12 000); group delay
  4350 samples = 91 ms. Removing the delay offline is trivial, but a linear-phase filter **pre-rings
  symmetrically**: energy appears up to (L−1)/2 before each peak (smears clicks, raises EDT, fills the
  gap before the direct sound → AX1 pre-roll of 32 samples is far too short if the group delay is
  removed by shifting without padding). Mitigation: transition width proportional to the crossover
  frequency (constant-Q), which sets the length by the 63/125 Hz crossover only, and check peak
  sharpness in `compare.py` as phase-03 says.
- **Kaiser window:** w[n] = I0(β·√(1−(2n/(L−1))²)) / I0(β) (https://en.wikipedia.org/wiki/Kaiser_window,
  β = π·α). β ↔ attenuation A [dB] (Kaiser; SciPy `kaiser_beta`, https://github.com/scipy/scipy/blob/main/scipy/signal/_fir_filter_design.py):
  ```
  β = 0.1102·(A−8.7)                              A > 50
  β = 0.5842·(A−21)^0.4 + 0.07886·(A−21)          21 ≤ A ≤ 50
  β = 0                                           A < 21
  numtaps = (A − 7.95)/(2.285·Δω) + 1             (SciPy kaiserord, Δω in rad/sample)
  ```
  β = 8 ⇒ A ≈ 81 dB sidelobe/stopband level; β ≈ 8.6 ≈ Blackman, 6 ≈ Hann, 5 ≈ Hamming
  (https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.windows.kaiser.html). First null of
  the window transform at ω0 = 2β/M (https://www.dsprelated.com/freebooks/sasp/Kaiser_Window.html).
- **Windowed-sinc fractional delay:** h[n] = w[n]·sinc(n − D), n = 0..L−1, D = (L−1)/2 + d_frac,
  0 ≤ d_frac < 1 (Laakso, Välimäki, Karjalainen, Laine, "Splitting the unit delay", IEEE SP Mag.
  13(1):30–60, 1996, doi 10.1109/79.482137 — the FIR window-method section; details **unverified,
  from memory**). Integer part placed at floor(t·fs) − (L−1)/2 (pyroomacoustics: `f = int(time_ip) - fdl2`,
  fdl2 = (fdl−1)/2, verified). With L = 33: offset 16 samples each side; a 32-sample pre-roll (AX1)
  leaves 16 samples margin. **Pitfalls:** (a) centring on L/2 instead of (L−1)/2 → 0.5-sample bias;
  (b) even L; (c) window not centred on the *fractional* position (RIR-Generator's pre-2014 bug);
  (d) kernel not re-normalised — a Kaiser-windowed sinc has DC gain slightly ≠ 1 (sum of taps);
  with L = 33, β = 8 the error is small but shows up in ±0.5 dB amplitude tests, especially since the
  gain also varies with d_frac; (e) usable bandwidth: a short windowed sinc under-shoots magnitude
  near Nyquist and its delay error grows there — for L = 33 expect accuracy to ≈ 0.8–0.9·fs/2
  **(unverified, from memory)**; irrelevant ≤ 8 kHz at 44.1 kHz+.
- **Smearing risk:** every per-band image impulse is the kernel (33 taps ≈ 0.7 ms) convolved with
  the band filter; the band-filter length dominates; see pre-ringing above.

---

## 9. Diffuse-field assumptions and flutter echo

- A statistical tail assumes: uniform energy density, isotropic incidence, Gaussian amplitude
  statistics, exponential decay with a single rate per band, and ergodic mixing (Lindau 2012 §1;
  Kuttruff **(from memory)**). Violated by: strongly non-uniform absorption (§5), very flat/long rooms,
  low ᾱ with parallel hard walls, coupled volumes, and any frequency below f_s (§7).
- **Flutter echo is physical:** two parallel reflecting walls ℓ apart give a periodic echo train with
  repetition time t_r = 2ℓ/c (ℓ/c for a listener at the midpoint), perceived as a pitch f0 = 1/Δt
  with harmonics when the rate is above ≈ 20 Hz and as a rhythm below
  (Aalto "Flutter Echo Modeling", https://acris.aalto.fi/ws/portalfiles/portal/88980507/DAFx20in22_paper_27.pdf;
  DAFx-15 submission 39, https://www.dafx.de/paper-archive/2015/DAFx-15_submission_39.pdf; Halmrast,
  https://www.ioa.org.uk/system/files/proceedings/t_halmrast_why_do_flutter_echoes_always_end_up_around_1-2_khz.pdf).
  In the ISM this is the axial image chain k = (n,0,0): positions 2nL ± s, spacing 2L, amplitudes
  (1−α)^{|n|/2}/r — i.e. a decaying comb with period 2L/c. In a shoebox with hard walls these
  peaks persist into high orders and the Schroeder curve shows ripples; a real room's diffusion
  and non-parallelism smooth them. The phase-03 listening note ("a flutter-echo between hard
  parallel walls, which is physically correct") is right; do not "fix" it in `src/sim/` (NFR-8).
  Applying s > 0 reduces the specular comb by (1−s)^{hits} and moves that energy to the tail — the
  only legitimate knob.
- Consequence for the tail: Gaussian noise with Eyring decay has **no** flutter; the seam at t_mix
  therefore changes character for hard parallel rooms (periodic → diffuse). This is expected; a
  t_mix well beyond the perceptual mixing time hides it.

---

## 10. Reviewer's checklist (ISM / tail / filterbank diffs)

Each line: question → bug it catches.

**Geometry and enumeration**
1. Is the image coordinate `2nL + (−1)^p s` (or `kL + (k odd ? L−s : s)`) per axis, with the room
   origin at the floor corner (AQ1)? → images mirrored about the wrong plane (e.g. about L/2).
2. Is "order" Σ|k_d| and the enumeration the L1 ball (not the cube |k_d| ≤ N)? → wrong image count
   (7/25/63/1561 for N = 1/2/3/10) and `maxReflectionOrder` semantics ≠ pyroomacoustics.
3. For odd k, is the extra hit assigned to the wall on the side of the sign of k (k<0 → wall at 0)?
   → wrong wall's α used; invisible with symmetric materials, visible with `asymmetric_materials`.
4. Is the per-surface hit count derived from (|k|, parity) rather than re-counted by ray tracing?
   → off-by-one counts at k = ±1.
5. Does r use the *listener* position and the image position (not source–listener distance plus
   lattice offsets)? → direct-path correct, reflections wrong.
6. Is τ = r/c with c a single named constant (343.0) shared by ISM, tail and tests, and is the
   pyroomacoustics comparison run with the same c (default 343.0, no `temperature=`)? → 0.06 % time
   error = 1–2 samples on long paths.
7. Is the direct path (k = 0) included exactly once, and does order 0 produce only it? → missing or
   doubled direct sound.
8. Are the DOA vectors unit vectors from listener to *image* (not to source), normalised after
   subtraction? → wrong HRTF direction in phase 08.

**Amplitudes**
9. Is √(1−α) applied to pressure per hit (not (1−α), not √ applied to a product that was already
   square-rooted)? → 2× dB error per hit.
10. Is α clamped to [0, 1] before the sqrt (and ≤ 0.999 before ln in Eyring)? → NaN / inf T60.
11. Is scattering applied as √(1−s) on pressure (= (1−s) on energy) and is the removed energy
    (1−α)·s·(previous energy) recorded per band with its arrival time? → energy vanishes.
12. Is the scattered energy recorded in energy units (amplitude²·band) and not in amplitude? →
    tail over/under-fed by the square.
13. Is 1/r applied once (not 1/r², not 1/(4πr) when AX2 says 1 at 1 m)? → 22 dB offset or wrong
    slope vs distance.
14. Air absorption on the ISM path: 10^(−a_dB·r/20) on amplitude (= exp(−m r/2)), once? → applied
    twice (per image + global band filter) or on energy.
15. In the comparison test, is `air_absorption=False`, `scattering=0`, `use_rand_ism=False`,
    `rir_hpf_enable=False` (or peaks compared in a way insensitive to the 10 Hz HPF), and are
    amplitudes normalised to the direct peak? → false failures from pyroomacoustics defaults.
16. Does the test subtract pyroomacoustics' global delay of `frac_delay_length // 2` = 40 samples
    (or align on the direct peak) before the ±1-sample check? → systematic 40-sample offset.
17. Does the pyroomacoustics wall mapping (west/east/south/north/floor/ceiling = x−/x+/y−/y+/z−/z+)
    match the scene's surface order? → swapped surfaces, only visible with asymmetric materials.

**Fractional delay and filterbank**
18. Kernel length odd, centred at (L−1)/2 + frac, integer placement at floor(t·fs) − (L−1)/2? →
    0.5–1 sample bias in every arrival.
19. Is the kernel's DC gain (sum of taps) normalised for every fractional offset? → ±0.1–0.3 dB
    amplitude ripple vs fraction.
20. Is the pre-roll (AX1) ≥ (L−1)/2 + filterbank group delay padding, so no kernel/band tap is
    truncated before t = 0? → clipped direct sound, wrong level.
21. Is the filterbank built once per sample rate, all bands equal odd length, and the top band
    defined as δ_centre − lowpass (so the sum is a delayed delta by construction)? → PR fails or
    passes only approximately.
22. Is the group delay (L−1)/2 removed by the same amount from ISM and tail (and documented in the
    reported latency)? → tail starts late; seam; peak times off.
23. Is pre-ringing before the direct sound bounded and tested (peak sharpness in compare.py)? →
    smeared transients, EDT bias.
24. Band edges: 63 Hz band extended to DC and 8 kHz band to Nyquist (project rule), consistent
    between synthesis filterbank, `bands.py` analysis and the pyroomacoustics bands (125 Hz base,
    different!)? → per-band comparisons off at the ends.
25. Does the filterbank handle 44.1/48/88.2/96 kHz with the same *time-domain* transition behaviour
    (constant-Q design), and do the tests check T30/EDT/C80 across rates (phase-04 ±2 %)? → rate-
    dependent smearing.

**Tail and T60**
26. Eyring written as 0.161·V/(−S·ln(1−ᾱ) + 4mV) with ᾱ area-weighted *per band* and m the
    **energy** coefficient a_dB/4.343 (not a_dB/8.686)? → air term halved; HF T60 too long.
27. Noise amplitude multiplied by exp(−6.908·t/T60_b) (equivalently 10^(−3t/T60)) — not by
    exp(−13.8 t/T60) and not applied to energy? → measured T60 = T60/2 or 2·T60.
28. Does the envelope time origin coincide with the point where E_b was matched (t_mix), and is the
    matched quantity energy-per-time (same window length on both sides, same filterbank)? → level
    step at the seam.
29. Is the matching window after t_mix on the tail and before t_mix on the ISM *plus the scattered
    energy collected up to t_mix* (phase-04)? → dry/wet step at the seam for scattering rooms.
30. Crossfade: amplitude gains cos/sin (power-complementary) for the uncorrelated ISM/tail pair —
    not cos²/sin² amplitude gains? → −3 dB dip at mid-fade.
31. Are ISM contributions after the crossfade dropped (and not also present in the tail's
    statistical level)? → double-counted energy, EDC bump after t_mix.
32. Is t_mix clamped to the time fully covered by the ISM order (last *complete* shell), with the
    clamp logged? → incomplete-shell energy dip before the seam.
33. Noise: per-band from one seeded PRNG stream (PCG32/xoshiro, not std::mt19937 or `rand()`),
    seed = tailSeed ⊕ f(emitter, output)? → non-deterministic or identical tails for L/R.
34. Is the noise split with the same filterbank, and is the band energy of unit-variance noise
    accounted for (band gain·bandwidth) when setting E_b? → band levels wrong by the band's
    noise-gain factor.
35. IR length: until the *slowest* band is 90 dB below start, capped at 12 s; and T30 evaluation
    uses −5…−35 dB with a guard that the range exists in every band? → truncated decays measured as
    short T30; pyroomacoustics-style silent range reduction.
36. Any NaN/denormal source: ln(1−ᾱ) at ᾱ→1, division by T60_b → 0 (open_field), exp underflow
    in long tails (flush-to-zero or clamp)? → open_field crash or CPU spikes.
37. Below the Schroeder frequency (63/125 Hz in small rooms) are tolerances relaxed in tests and
    is nothing "tuned" to pass there? → NFR-8 violation disguised as a fix.
38. Flutter echo peaks in hard shoeboxes left in place, and no per-scene branches in `src/sim/`? →
    NFR-8 violation.
39. Does changing only the seed leave T30 within ±2 % and change the waveform, and does the same
    seed give a bit-identical IR twice in one process? → hidden state (static RNG, time seeding).
40. Units at every interface: metres, seconds, Hz, radians internally; dB only in tests and tables;
    energy vs amplitude named explicitly (`energy`, `amp`, `db`)? → the silent ×2 / ² bugs above.

---

## Source list (accessed 2026-11-04)

- pyroomacoustics sources: https://raw.githubusercontent.com/LCAV/pyroomacoustics/master/pyroomacoustics/room.py ,
  .../parameters.py , .../simulation/ism.py , .../experimental/rt60.py , .../acoustics.py ,
  .../libroom_src/room.cpp , .../libroom_src/rir_builder.cpp , .../libroom_src/wall.hpp ;
  docs https://pyroomacoustics.readthedocs.io/en/latest/pyroomacoustics.room.html
- RIR-Generator: https://raw.githubusercontent.com/ehabets/RIR-Generator/master/rir_generator_core.cpp
- MathWorks ISM example: https://www.mathworks.com/help/audio/ug/room-impulse-response-simulation-with-image-source-method-and-hrtf-interpolation.html
- arXiv 2405.03385v2 (shoebox ISM formalism): https://arxiv.org/html/2405.03385v2
- JASA "The image source method" (2025 reflections piece): https://pubs.aip.org/asa/jasa/article/158/5/R9/3371770
- ISO 9613-1 implementation: https://github.com/python-acoustics/python-acoustics/blob/master/acoustics/standards/iso_9613_1_1993.py ;
  formulas also at https://sengpielaudio.com/AirdampingFormula.htm ; table excerpt
  https://www.sciencedirect.com/topics/engineering/atmospheric-attenuation ; octave-band caveat
  https://doi.org/10.3390/app142210139
- Speed of sound: https://www.omnicalculator.com/physics/speed-of-sound
- Reverberation formulas: https://en.wikipedia.org/wiki/Reverberation ;
  http://www.conforg.fr/acoustics2008/cdrom/data/fa2002-sevilla/forumacusticum/archivos/arcgen015.pdf ;
  https://sound.eti.pg.gda.pl/papers/prediction_of_reverberation_time.pdf
- Mixing time: https://www2.users.ak.tu-berlin.de/akgroup/ak_pub/2012/Lindau_2012a_Mixing_Time.pdf ;
  Abel & Huang 2006 https://www.aes.org/e-lib/browse.cfm?elib=13819
- Hybrid IR: https://reuk.github.io/wayverb/hybrid.html ; https://arxiv.org/pdf/2408.14213 ;
  https://pub.dega-akustik.de/DAGA_2014/data/articles/000467.pdf ; https://dafx2020.mdw.ac.at/Proceedings/papers/DAFx2020_paper_47.pdf
- Schroeder frequency: https://strutt.arup.com/help/Building_Acoustics/SchroederFreq.htm ;
  https://acoustics.ippt.pan.pl/index.php/aa/article/download/739/649
- Scattering: https://acousplan.com/learn/what-is-acoustic-diffusion ; https://en.wikipedia.org/wiki/Diffusion_(acoustics) ;
  α = 1−|R|²: https://people.ee.ethz.ch/~isistaff/courses/ak1/acoustics-absorption-reflection.pdf
- Filters: https://vhdlwhiz.com/part-6-complementary-fir-filters/ ; https://www.advsolned.com/?p=17540 ;
  https://github.com/scipy/scipy/blob/main/scipy/signal/_fir_filter_design.py ;
  https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.windows.kaiser.html ;
  https://www.dsprelated.com/freebooks/sasp/Kaiser_Window.html ; https://en.wikipedia.org/wiki/Kaiser_window ;
  Laakso et al. 1996 doi 10.1109/79.482137
- Flutter echo: https://acris.aalto.fi/ws/portalfiles/portal/88980507/DAFx20in22_paper_27.pdf ;
  https://www.dafx.de/paper-archive/2015/DAFx-15_submission_39.pdf
