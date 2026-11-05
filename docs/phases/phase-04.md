# Phase 04 — Late reverberant tail + hybrid room IR

Size: **M** · Depends on: 03 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ3, AX4, AX5, AX11, AX16, AX17, AX18, AX19, AX20, AX21, AX22), PRD NFR-1, NFR-3, NFR-8

## Goal

Complete the omni room IR. Phase 03's image-source early reflections are joined to a **statistical
late tail** whose per-band decay comes from room geometry and materials alone. The result is a full
IR for every valid shoebox scene.

## Assumptions in force

- **AQ2**: stochastic noise tail, per-band decay from **Eyring** with air absorption, energy-matched to
  the ISM at a mixing time.
- **AX4**: fixed standard atmosphere.
- **AX5**: determinism. The tail noise comes from a self-contained PRNG (PCG32 or xoshiro128+) in
  `src/sim/Rng.h` with its own Gaussian transform, seeded with `render.tailSeed` combined with the
  emitter index. The C++ standard fixes the output sequence of its engines (e.g. `std::mt19937`), but
  the standard-library **distributions** (e.g. `std::normal_distribution`) are not portable across
  standard libraries (engineering, from the C++ standard [rand.eng], [rand.dist]; not from the corpus).
- **AX11**: decay times of the noise tail are gated on ensemble-averaged decay curves (see the
  acceptance criteria for R per band).
- **AX16**: scattered energy is one entry per image path, at the path's specular arrival time.
- **AX17**: one broadband scattering coefficient per surface (it overstates low-frequency ground
  scattering in `open_field`, see the acceptance criteria).
- **AX18**: the ISM→tail crossfade joins uncorrelated signals, so it is equal-power.
- **AX19**: σ₁(EDT) and σ₁(C80) of the hybrid IR are measured in this phase and recorded there; they
  set R for the EDT and C80 sample-rate gates.
- **AX20**: the image list used for matching and for the rendered early part is time-bounded (every
  image of any order arriving before t_mix,e + 2.5 ms; later images are represented by the tail), so
  `maxReflectionOrder` has no effect on the hybrid IR. It applies only to the early-reflection-only
  (Omni ISM) IR of Phase 03, kept after Phase 04 as `Kind::OmniEarly` / `render_cli --mode omni-early`.
  Where the realised-k fallback of scope 2 moves the handover to the AX22 cap, the list extends with
  it.
- **AX21**: the hybrid IR is **specular-only before t_mix,e** (Phase 03 renders (1−α)(1−s) per hit; the
  AX16 scattered entries only set the tail level). This is a known deficit; Maisara decided on
  2026-11-05 that the early part should contain scattered energy. The fix is planned on Phase 05
  evidence (BUILD_PLAN §5 B11), not in this phase.
- **AX22**: switch rule. If the **realised** k at the expected-rule t_mix,e is < 19 in any band
  500 Hz–2 kHz (scope 2), the emitter falls back to ISM-only up to a cap on the image count; the cap
  value is measured in this phase against AQ10 and recorded there.

## Scope

1. `src/sim/tail/Decay.h/.cpp` — per band b:
   - S = total surface area, ᾱ_b = area-weighted mean absorption, V = W·D·H.
   - m_b = **energy** attenuation coefficient of air in 1/m, I(x) = I₀·e^(−m·x), so
     m_b = D_b / 4.34 with D_b the level loss in dB/m from `AirAbsorption` (ISO 9613-1, AX4)
     (Vorländer §3.6 Eq. 3.33–3.35; it enters Eyring as 4mV, §4.4.1 Eq. 4.32). It is **not** the
     pressure attenuation in Np/m (D/8.686), which would halve the 4·m_b·V term (≈ 8 % too long a T
     at 4 kHz in a 20×30×10 m room with ᾱ_4k ≈ 0.35; in general the error is (1+x)/(1+x/2) − 1 with
     x = 4mV/(−S·ln(1−ᾱ)), up to 2× where air absorption dominates, Vorländer Eq. 4.32). Unit-test the
     conversion against one ISO 9613-1 value. Next to it, unit-test `AirAbsorption` at 20 °C against
     Kuttruff Table 6.1 at 40 / 50 / 70 % RH and 0.5–8 kHz, within **±1 %** (e.g. 50 % RH, m in
     10⁻³ m⁻¹: 2.28 / 6.84 / 24.29 at 2 / 4 / 8 kHz). This checks the code against Kuttruff Table 6.1
     (Bass 1995); the Vorländer Annex gives only humidity bins, with 50 % on a bin boundary, so it is not
     a point reference. On failure, fix the code. (The current ISO 9613-1 code agrees within 0.7 %,
     e.g. 6.83 against 6.84·10⁻³ m⁻¹ at 4 kHz / 50 % RH; main-session check, 2026-11-05.)
   - Eyring: `T60_b = 0.161·V / (−S·ln(1−ᾱ_b) + 4·m_b·V)`. Clamp ᾱ_b ≤ 0.999 so ln stays finite.
     For the `open_field` case (five surfaces at α = 1.0) Eyring does not apply (no diffuse field,
     Vorländer §4.4.1) and its nominal T60 need not be near 0. The tail is still absent because its
     **level** comes from energy matching (below), which only looks at entries in the matching window
     before `t_mix,e`. In `open_field` the only non-zero entries are the direct sound and the floor
     reflection (specular and AX16 scattered part); in the fixture the floor reflection arrives 1.4 ms
     after the direct sound, before the window's start t_dir,e + 2.5 ms, and every later image
     hits an α = 1 face, so every entry in the window is zero and E_b = 0 for any floor scattering s.
     No scene-specific logic is involved (NFR-8). E_b = 0 is the physical criterion: single-surface
     ground scattering is a deterministic early component, not a diffuse field (Kuttruff §4.5, §5.1).
   - Expose `T60_b` for tests and UI display.
2. `src/sim/tail/MixingTime.h/.cpp` — per emitter e, t_mix,e is the **smallest t ≥ t_dir,e +
   max(20 ms, √V ms)** such that the expected energy-weighted k_eff of the Hann window
   [t_dir,e + 2.5 ms, t] is **≥ 19**, with
   k_eff = (4πc³/V) · (∫w dt)² / ∫ w(t)²/t² dt,
   w the Hann taper over [t_dir,e + 2.5 ms, t], t measured from emission, c = 343 m/s, V in m³, and
   t_dir,e the emitter's own direct-arrival time from emission (distance / c, before the AX1 shift).
   (Sources: Blauert Ch. 3 §3.3, Cremer's reflection density; Vorländer Eqs. 11.8, 11.20, 11.50 and
   11.9/11.17.) The corpus gives no rule for the transition time (Vorländer §11.7). This rule is
   chosen for accuracy (PRD NFR-1: more of the response is deterministic ISM) and for **1 dB expected
   level precision**: σ = 4.34/√19 ≈ 1.0 dB (Vorländer Eqs. 11.9/11.17), against the 1 dB jnd of G
   (Vorländer Table 6.1, stated for 500–1000 Hz). The earlier √V-milliseconds term (the widely used estimate of perceptual
   mixing time, cite the source in a comment) and the 20 ms are kept as a lower bound, counted from the
   emitter's direct sound, not from emission. The Expert may revise the rule. For t_dir,e → 0 the k_eff
   criterion alone gives roughly 6.8·V^(1/3) ms (≈ 53 expected arrivals) (approximate, from
   N(t) = (4π/3)(ct)³/V). Each emitter gets its own t_mix,e, as it gets its own tail; the matching window
   and the crossfade use t_mix,e. There is no clamp to the requested ISM order: the image list is
   time-bounded instead (AX20, scope 3).
   **Realised-k switch (AX22):** t_mix,e comes from the expected-k_eff rule above, which is continuous
   in source position. At that t_mix,e, compute per band the realised
   k_real = (Σ w_i E'_i)² / Σ (w_i E'_i)², the sums running over the specular and scattered entries in
   the window of scope 3, w_i = w(t_i), and E'_i entry i referred to t_mix,e (scope 3, step 3). If
   k_real < 19 in **any** of the bands 500 Hz, 1 kHz and 2 kHz (AQ9's bands), the emitter falls back to
   **ISM-only up to the AX22 cap**: the cap is an image count N_cap, measured in this phase against
   AQ10 and recorded in AX22 (for scale: the order-30 budget is ν_r(30) = 37 880 images, Kuttruff
   Eq. 9.23). The handover then moves to t_cap,e, the arrival time of the N_cap-th image in arrival
   order, and the tail is matched there (scope 3, window [t_dir,e + 2.5 ms, t_cap,e]) only if the
   window holds non-zero energy (else E_b = 0). N_cap counts every enumerated lattice image,
   pruned or not (as Kuttruff Eq. 9.23 does), so the cap bounds the enumeration cost; if
   t_cap,e < t_mix,e the handover stays at max(t_mix,e, t_cap,e) = t_mix,e (Maisara, 2026-11-05). k_real is not monotonic in t: entries never leave the window
   (its left edge is fixed), but the Hann re-weighting as t grows changes their weights (derived, not
   from the corpus); so k_real is tested only at the expected-rule t_mix,e. The switch is a single jump
   point in source position (see Risks). Images with exactly zero energy (any hit on a face with α = 1)
   are pruned, generically (NFR-8).
3. `src/sim/tail/NoiseTail.h/.cpp` — for each emitter:
   - **Image list (AX20):** matching and the rendered early part use every image of any order that
     arrives before t_mix,e + 2.5 ms (the end of the crossfade); later images are represented by the
     tail. The early part is time-bounded, so `maxReflectionOrder` has no effect on the hybrid IR
     (accuracy first, PRD NFR-1); it applies only to the early-reflection-only (Omni ISM) IR of Phase 03 /
     `render_cli --mode omni-early`. The list is complete up to the end of the fade.
   - Generate Gaussian white noise (seeded, see AX5), split it into the 8 bands with the **same
     filterbank as Phase 03**, and apply the envelope `exp(−6.91·t / T60_b)` per band. Normalise each
     band to unit total energy. This **unmatched, unit-energy per-band decay** depends only on V, S,
     ᾱ_b, m_b, `tailSeed` (with the AX5 emitter/output offsets) and the sample rate. It is the object
     Phase 10 caches, so keep it as a separate value computed **before** E_b scaling, `t_mix,e` gating
     and the crossfade; those three are recomputed from the current image list on every rebuild
     (`t_mix,e` depends on positions through t_dir,e, and so does the AX20 time-bounded image list).
     The band signal is then `E_b · unitDecay_b(t)`, E_b an amplitude factor.
   - **Energy matching** (all quantities are band **energies**, i.e. squared pressure summed over
     samples, per band b):
     1. **Entries.** Every image path of the AX20 list gives two entries per band: its **specular**
        energy and its **AX16 scattered-energy entry** E_noScatter·(1 − Π(1 − s)^hits), both at the
        path's specular arrival time t_i. The scattered entries are what keeps the tail from being too
        quiet: matching to specular energy alone would put it ≈ 9 dB low with s = 0.5 after 3 hits
        (Vorländer Eq. 3.23, Fig. 3.10; §11.6: scattered energy dominates after a few orders).
     2. **Window.** The window is [t_dir,e + 2.5 ms, t_mix,e], the one scope 2 uses to choose t_mix,e.
        Its taper w is a Hann window over that interval, zero at both ends. By scope 2 its expected
        energy-weighted k_eff is ≥ 19, and so is its realised k_real at 500 Hz–2 kHz unless the AX22
        fallback applies (then the window ends at t_cap,e).
        **Report**, per emitter and band, σ_dB = 4.34/√k_eff (Vorländer Eqs. 11.9/11.17) as the
        **expected** precision under Poisson-like arrivals, together with the realised count of
        non-zero entries in the window, k_real, the realised σ = 4.34/√k_real, and the per-axis energy
        shares Σ E_i u_{i,k}² / Σ E_i (k = x, y, z; u_i the unit arrival direction of entry i), each 1/3
        in an isotropic field (Kuttruff Eqs. 5.1–5.2). The shares are a necessary condition only (three
        equal axial flutter pairs also read 1/3 each); there is no threshold and they are not gated. Do
        not use q_d (Kuttruff Eq. 8.43 reads a 1-D flat-room field as ≈ 0.85 "diffuse", for r = 5 m,
        h = 3 m at 100 ms; ledger rebuttal Q2). Shoebox image
        arrivals are deterministic, so in sparse or non-diffuse fields the actual error is not bounded
        by these σ values (see Risks).
     3. **Estimate.** Refer each entry to t_mix,e along the diffuse decay (energy falls 60 dB per
        T60_b) and weight it by the taper, normalised to a 10 ms window:
        E_target,b = (0.010 s / ∫w dt) · Σ_i w(t_i) · E_i,b · exp(−13.82 · (t_mix,e − t_i) / T60_b).
        This is the band energy per 10 ms at t_mix,e.
     4. **Match.** Set E_b so that E_b² · ē_b = E_target,b, where ē_b is the **expected** energy of the
        unit-energy decay per 10 ms at t_mix,e (the same 10 ms normalisation), computed analytically,
        **not** the realisation's own Σ unitDecay_b²:
        ē_b = 0.010 s · (13.82/T60_b) · exp(−13.82·t_m/T60_b) / (1 − exp(−13.82·L_IR/T60_b)),
        with t_m = t_mix,e measured from emission on the unit decay's time axis (the unit decay starts at
        emission time 0 and is independent of positions, which Phase 10's cache relies on) and L_IR the
        rendered IR length (12 s cap, below). ē_b does not depend on the matching window. Band-filter
        ringing is not included in ē_b; it is a measured, reported check. E_b is then
        seed-independent, and so is the tail's total energy E_b² (Vorländer §11.7 Eq. 11.51: the
        envelope is deterministic, the noise carries the fine structure). Match on the un-faded tail
        (before the crossfade below). Nothing is accumulated from t = 0.
     - Entries outside the window (for example the direct sound, and the `open_field` floor
       reflection in the fixture, specular or scattered) do **not** set the tail level. If every entry
       in the window is zero, E_b = 0: the matched tail is zero.
     - The mixing-time rule (scope 2), the matching window and its taper are part of this phase's spec
       and must be stated exactly in code and tests (they are the ones above); the open-field result
       depends on them.
   - **Crossfade** ISM → tail over 5 ms centred on `t_mix,e` (`[t_mix,e − 2.5 ms, t_mix,e + 2.5 ms]`). ISM
     and tail are uncorrelated, so the crossfade is **equal-power** (AX18; uncorrelated broadband
     signals add in power, Vorländer §4.3 Eq. 4.14–4.16; cf. §9.2.1): with τ running from 0 to 1
     across the 5 ms, the **amplitude** windows are w_ISM = cos(πτ/2) on the ISM and w_tail = sin(πτ/2) on the tail, so
     w_ISM² + w_tail² = 1. (Equal-gain windows, whose amplitudes sum to 1, dip by up to 3 dB mid-fade
     on uncorrelated signals.) Before the fade the tail is absent; after it, ISM contributions are
     dropped. The direct arrival always lies before the fade (t_mix,e ≥ t_dir,e + 20 ms), so it is never
     faded or dropped; but band-filter ringing of the direct sound and of early images that extends past
     t_mix,e − 2.5 ms is crossfaded like other ISM content. The corpus does not cover analysis-filterbank
     ringing (Vorländer §11.7 concerns ringing from coarse interpolation of reflection-factor spectra),
     so its effect is a measured, reported check.
   - IR length: until the slowest band decays 90 dB below its start level, capped at **12 s**. The cap
     is the only bound (AX6 room limits allow T of order 160–265 s: 100 m cube, α = 0.01: ≈ 265 s
     without air absorption (Vorländer Eq. 4.32); with air absorption ≈ 225 s at 63 Hz and ≈ 160 s at
     125 Hz); longer decays are **truncated** at 12 s, and T30 is
     measurable on a 12 s IR only for T ≤ ≈20 s (it needs ≥ 35 dB of decay).
4. Update `sim::buildRoomIR(Kind::Omni)` to return ISM + tail. Keep the Phase 03 early-reflection-only
   IR available as its own path (`Kind::OmniEarly`, `render_cli --mode omni-early`), unchanged, so the
   Phase 03 pyroomacoustics cross-check and its goldens keep testing the ISM; `maxReflectionOrder`
   applies to that path (AX20). Phase 08 will need decorrelated tails per ear; leave the hook as a
   per-output seed offset (`seed ^ (outputIndex · 0x9E3779B9)`).
5. Update golden metrics for all valid fixtures (this is an **intended** change; use
   `update_goldens.py --reason "phase 04 adds tail"`).
6. Add 6 test rooms to `tests/scenes/valid/` covering T60 from about 0.2 s to about 6 s
   (`dead_booth`, `living_room`, `classroom`, `club`, `concert_hall_box`, `stone_box`).
7. Follow-up from the plan review (AX20): `docs/contract/README.md` must document in this phase that
   `maxReflectionOrder` has no effect on the hybrid IR (its early part holds every image of any order
   arriving before t_mix,e + 2.5 ms, later images are represented by the tail) and applies only to the
   early-reflection-only (Omni ISM) IR of Phase 03, kept after Phase 04 as `Kind::OmniEarly` / `render_cli --mode omni-early`. This changes the field's
   meaning, so this phase bumps `contractVersion` (minor) and updates the field's description in
   `docs/contract/scene-v1.schema.json` and `docs/contract/README.md`, per CLAUDE.md's contract rule.

## Out of scope

Binaural tail coherence (08); validation against real rooms (05); any per-scene tuning (forbidden by NFR-8).

## Acceptance criteria — automated

- [ ] For the 6 test rooms, the measured **T30 is within ±5%** of the Eyring T60_b in bands
      250 Hz–4 kHz, and within ±10% at 125 Hz and 8 kHz, measured on an **AX11 ensemble-averaged
      decay curve** (`metrics.room_metrics_ensemble`) over R realisations with different `tailSeed`s.
      R per band follows AX11's rule R ≥ (σ₁ / (tol/3))², with σ₁ from AX11's table taken at the band's
      Eyring T60_b (see "Ensemble sizes" below). Single-realisation T30s are reported, not gated.
- [ ] Energy decay curve (Schroeder, per band) is monotonic, and the EDC shows **no step > 1 dB** in a
      5 ms window around each emitter's `t_mix,e` (the seam test).
- [ ] **Envelope step, reported only (not gated):** per emitter and band, the ensemble-averaged band
      energy in the 10 ms bins [t_mix,e − 10 ms, t_mix,e) and [t_mix,e, t_mix,e + 10 ms), on the AX11
      Eyring-gate ensemble (its R), with the level step in dB between the two bins after removing the
      expected decay between them, 60·0.010/T60_b dB (Vorländer Eq. 11.13; raw differences would exceed
      the expected step, e.g. 3 dB at T = 0.2 s). The EDC gate above cannot see an envelope step,
      because the Schroeder EDC is a backward integral (Vorländer Eq. 6.4): a step changes its slope,
      not its value. Expected step from the missing early scattered energy (AX21), as **upper
      estimates**: ≈ 0.9 / 1.8 / 4.9 / 8.7 dB for s = 0.05 / 0.1 / 0.25 / 0.4 in the AQ10 room, from
      (1−s)^(n̄t) with n̄t ≈ 3.9 hits at t_mix,e (Kuttruff §5.2). They replace each image's order by the
      mean n̄t, the shortcut Kuttruff §5.5 corrects; by convexity the true energy-weighted step is
      smaller.
- [ ] Same scene + same seed gives a **bit-identical** IR on the same platform (run twice in one test).
      A different seed gives the same T30 within ±2% (the seed changes the noise, not the room), in
      bands 125 Hz–8 kHz: compared between **two independent AX11 ensembles** (disjoint `tailSeed`
      sets), each of R realisations from the rule with tol/√2 (see below). Single-realisation
      differences are reported, not gated.
- [ ] 44.1 kHz and 96 kHz renders of the same scene agree, compared between **two per-rate AX11
      ensembles** (one at 44.1 kHz, one at 96 kHz, disjoint `tailSeed` sets). Single-render
      T30/EDT/C80 differences are reported, not gated.
      - **T30** within ±2 %, bands 63 Hz–8 kHz, R per band from the seed-gate row below
        (R ≥ 4.5·σ₁², tol/√2); at 63 Hz R = 1458 / 288 / 41 (see "Ensemble sizes").
      - **EDT** within ±2 %, on the ensemble-averaged decay curves, R ≥ 9·(σ₁,44² + σ₁,96²)/(2 %)² per
        band (= 4.5·σ₁(EDT)² when the two are equal), with σ₁(EDT) measured per band and rate on this
        phase's hybrid IRs (not on noise × exp) and recorded in AX19. Until σ₁(EDT) is measured, EDT is
        reported only. Bands 63 Hz–8 kHz, as T30.
      - **C80** within ±0.5 dB, computed per rate from the ensemble-averaged early and late band
        energies, R ≥ 9·(σ₁,44² + σ₁,96²)/(0.5 dB)² (= 72·σ₁(C80, dB)² = (σ₁ / (0.5 dB / (3·√2)))² when
        the two are equal), with σ₁(C80) measured per band and rate on this phase's hybrid IRs and
        recorded in AX19; bands 125 Hz–8 kHz. The 1 dB jnd of C80 is stated only for 500–1000 Hz
        (Vorländer Table 6.1).
      - **Measuring σ₁(EDT) and σ₁(C80) (AX19):** on the six test rooms at both 44.1 kHz and 96 kHz
        (σ₁,44 and σ₁,96 per band), with n ≥ 51 realisations per room and rate, so the relative
        standard error of each σ₁ estimate, ≈ 1/√(2(n−1)), is ≤ 10 % (standard sampling statistics,
        not from the corpus).
- [ ] `open_field` gives no tail: E_b = 0 in every band (the physical criterion). Checked on the
      fixture (floor s = 0.4) **and** on a test-local variant with floor scattering s = 0.5: in both,
      every specular and scattered entry in the matching window is zero (the floor reflection arrives
      1.4 ms after the direct sound, before the window's start t_dir,e + 2.5 ms), so E_b = 0.
      In addition, the energy later than 50 ms after the direct sound's arrival is < −60 dB relative to
      the direct sound. This is a **consistency check of AX16's timing convention**, not a physical
      expectation: under AX16 the only non-zero entries are the direct sound and the floor image.
      Lambert floor scattering with the fixture's geometry is estimated at −23 to −43 dB per band
      (Kuttruff Eqs. 4.24, 4.27, 4.29, 5.43; ledger row OF). The check is to be re-derived in whichever
      phase adds early scattered energy (AX21, BUILD_PLAN §5 B11). AX17's broadband s also overstates
      low-frequency ground scattering (Vorländer Annex: s < 0.05 below a/λ = 0.125; BUILD_PLAN §5 B10).
- [ ] **Flat room:** a test scene with the 4 walls at α = 1, floor and ceiling reflective with
      **equal** α (≥ 0.01, s = 0), and source and listener at mid-height (the conditions of Kuttruff
      Eq. 4.3): per band, the rendered energy of each image arrival matches the per-image reference
      (the Kuttruff Eq. 9.24 form, with (1−α)^|n| and the air factor exp(−m·r_n)) within **±0.5 dB**
      (AQ9's ISM tolerance), up to the end of the ISM part. Eq. 4.3 stays as the steady-state sum
      check: the summed rendered image energies match the reference sum within **±0.5 dB**, as the
      per-image check (Maisara, 2026-11-05).
- [ ] **One absorbing wall:** a box with one wall at α = 1 and the **other walls rigid** (α = 0,
      s = 0), so Kuttruff Eq. 4.16 applies. AQ3 forbids α = 0 in scenes, so the test calls the solver
      directly. The energy decay follows Eq. 4.16 (∝ 1/t, times the air factor exp(−m·c·t)) within
      **±1 dB per 10 ms bin**, from t ≥ L/c to the AX22 cap.

**Ensemble sizes (AX11).** R ≥ (σ₁ / (tol/3))² per band, rounded up; one ensemble per room uses the
largest R over its gated bands and metrics (more is allowed). σ₁ is AX11's measured single-realisation T30 scatter
(48 kHz); use the column of the tabulated T60 (0.3, 1.0, 6 s) at or just below the band's Eyring
T60_b, since σ₁ shrinks as T grows. For T60_b < 0.3 s it is **R** that scales: multiply the 0.3 s
R by 0.3 s / T60_b (equivalently, σ₁ scales by √(0.3 s / T60_b), since σ₁² ∝ 1/T by AX11's
0.5/√(B·T)); do not scale σ₁ itself by 0.3 s / T60_b. The seed gate compares two ensemble means,
whose difference has √2 times the scatter of one, so it uses tol/√2: R ≥ (σ₁ / (2 % / (3·√2)))² = 4.5·σ₁² (σ₁ in %).

| band | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|
| σ₁ at T60 0.3 / 1.0 / 6 s (%) | 10 / 6.7 / 1.8 | 8 / 4.4 / 1.3 | 6 / 2.7 / 1.2 | 3.4 / 1.5 / 0.5 | 2.7 / 1.4 / 0.3 | 1.9 / 1.0 / 0.5 | 1.3 / 1.0 / 0.3 |
| Eyring gate tol | ±10 % | ±5 % | ±5 % | ±5 % | ±5 % | ±5 % | ±10 % |
| R, Eyring gate, T60 0.3 / 1.0 / 6 s | 9 / 5 / 1 | 24 / 7 / 1 | 13 / 3 / 1 | 5 / 1 / 1 | 3 / 1 / 1 | 2 / 1 / 1 | 1 / 1 / 1 |
| R per ensemble, seed gate (±2 %), T60 0.3 / 1.0 / 6 s | 450 / 203 / 15 | 288 / 88 / 8 | 162 / 33 / 7 | 53 / 11 / 2 | 33 / 9 / 1 | 17 / 5 / 2 | 8 / 5 / 1 |

63 Hz is in neither the Eyring nor the seed gate (σ₁ up to 18 %), but it is in the sample-rate T30
gate: with σ₁ = 18 / 8 / 3 % (AX11), R per ensemble = 1458 / 288 / 41 at T60 0.3 / 1.0 / 6 s, × 0.3 s /
T60_b below 0.3 s (`dead_booth` ≈ 2187). The sample-rate T30 gate uses the seed-gate row in the other
bands. Example: `dead_booth` at T60_b ≈ 0.2 s needs
R = 24 · 1.5 = 36 for the Eyring gate and 450 · 1.5 = 675 per ensemble for the seed gate (tail-only
renders of ≈ 0.3 s, so this is cheap).
- [ ] No NaN, Inf or denormals in any IR (check every sample of every fixture).
- [ ] Goldens updated, with the reason recorded in `tests/golden/CHANGELOG.md`.

## Listening / manual checklist (Maisara)

Listening pack (still a mono omni preview): pink bursts, clicks and any WAVs you drop into
`tools/ci/listening_inputs/` before triggering CI (or run `listening_pack.py` locally).
- [ ] Decays sound **smooth**, not grainy, metallic or "fluttery" in the tail.
- [ ] The six rooms sound clearly ordered from dead to very reverberant.
- [ ] No audible "seam" between the early echoes and the tail on clicks.
- [ ] `stone_box` (hard surfaces) sounds brighter in the tail than `concert_hall_box`.

## Contractor review focus

Energy matching at `t_mix,e` (units, band energies vs amplitudes, the Hann-weighted window
[t_dir,e + 2.5 ms, t_mix,e] of specular + AX16 scattered entries referred to t_mix,e, E_b matched to the
expected, not the realised, unit-decay energy ē_b, the reported σ_dB, non-zero entry count, k_real,
realised σ and per-axis shares), t_mix,e per emitter as the smallest t from t_dir,e + max(20 ms, √V ms)
with expected k_eff ≥ 19, the AX22 realised-k switch (500 Hz–2 kHz) to ISM-only up to the image-count
cap, zero-energy image pruning, the reported-only
envelope step (AX21), the flat-room and one-absorbing-wall tests, the `AirAbsorption` test against
Kuttruff Table 6.1, the
AX20 time-bounded image list (`maxReflectionOrder` without effect on the hybrid IR, the contract bump), m_b as the energy coefficient D/4.34, the equal-power crossfade, the cached
unit-energy decay being independent of positions, the AX11 ensemble sizes, PRNG portability,
filterbank reuse, and IR truncation.

## Risks

- Eyring is known to be inaccurate for strongly non-uniform absorption (e.g. one absorbent ceiling).
  Note it as an input for Phase 05 and the Expert; don't patch it with per-scene factors.
- An audible seam at `t_mix,e`. Mitigated by the energy-matched crossfade and the seam test.
- **Known deficit (AX21):** the hybrid IR has no scattered energy before t_mix,e, so its envelope steps
  up at t_mix,e by up to ≈ 0.9–8.7 dB for s = 0.05–0.4 (upper estimates; reported-only envelope-step
  metric); this affects EDT,
  C80 and D50. Maisara decided on 2026-11-05 that the early part should contain scattered energy; the
  fix is planned on Phase 05 evidence (BUILD_PLAN §5 B11), not in this phase.
- **Expert question (mixing time):** the corpus gives no rule for the transition time (Vorländer
  §11.7). Scope 2's k_eff ≥ 19 rule, with t_dir,e + max(20 ms, √V ms) as a lower bound, is chosen for
  accuracy (NFR-1) and a well-conditioned level estimate; the Expert may revise it. t_mix,e stays as in
  scope 2 until the Expert answers.
- **Limitation / Expert question (sparse or non-diffuse fields):** where the window holds far fewer
  non-zero arrivals than expected (non-diffuse or sparse fields, e.g. one floor reflection in a box with
  five α = 1 faces), E_target has no stated accuracy and Eyring T60 does not apply (Vorländer §4.4.1).
  The realised-k switch (scope 2, AX22) falls back to ISM-only up to the AX22 image-count cap in such
  fields; the shoebox image lattice is complete (Kuttruff §4.1, example of the rectangular room), and
  image sources are exact only for rigid walls and approximate otherwise. Beyond the cap the tail is
  matched only if the window holds non-zero energy. The reported k_real, realised σ and per-axis energy shares
  are necessary conditions only; the corpus gives no diffuseness criterion with a threshold (Kuttruff
  §8.5, §9.5), so that stays an Expert question. No diffusion-equation fallback (Kuttruff §4.6: valid
  only for nearly diffuse fields).
- **Switch point (AX22, NFR-3, FR-SIM-6):** t_mix,e stays continuous in position, but the realised-k
  fallback is a single jump point in source position. Across it, the IR segment between t_mix,e and
  t_cap,e is ISM in one IR and noise in the other, so AX18's equal-gain premise (correlated consecutive
  IRs) does not hold there, and the 30 ms position crossfade can dip by up to ≈ 3 dB in that segment
  (Vorländer Eq. 4.14). Phase 10 adds a test that measures the dip at a switch point.
- AX20 makes the image list grow with t_mix,e, not with `maxReflectionOrder` (large rooms need high
  orders to reach t_mix,e), and the realised-k fallback extends it up to the AX22 cap. Measure
  rebuild time against AQ10 and record it; the AX22 cap is the only bound on the list.

## Definition of done

All automated criteria green; status row 04 `done`; listening checklist in the PR.
