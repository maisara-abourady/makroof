# Phase 04 — Late reverberant tail + hybrid room IR

Size: **M** · Depends on: 03 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ3, AX4, AX5, AX11, AX16, AX18), PRD NFR-1, NFR-8

## Goal

Complete the omni room IR. Phase 03's image-source early reflections are joined to a **statistical
late tail** whose per-band decay comes from room geometry and materials alone. The result is a full
IR for every valid shoebox scene.

## Assumptions in force

- **AQ2**: stochastic noise tail, per-band decay from **Eyring** with air absorption, energy-matched to
  the ISM at a mixing time.
- **AX4**: fixed standard atmosphere.
- **AX5**: determinism. The tail noise comes from a fixed PRNG (e.g. `std::mt19937` is **not**
  guaranteed identical across standard libraries. Use a self-contained PCG32 or xoshiro128+ in
  `src/sim/Rng.h`) seeded with `render.tailSeed` combined with the emitter index.
- **AX11**: decay times of the noise tail are gated on ensemble-averaged decay curves (see the
  acceptance criteria for R per band).
- **AX16**: scattered energy is one entry per image path, at the path's specular arrival time.
- **AX18**: the ISM→tail crossfade joins uncorrelated signals, so it is equal-power.

## Scope

1. `src/sim/tail/Decay.h/.cpp` — per band b:
   - S = total surface area, ᾱ_b = area-weighted mean absorption, V = W·D·H.
   - m_b = **energy** attenuation coefficient of air in 1/m, I(x) = I₀·e^(−m·x), so
     m_b = D_b / 4.34 with D_b the level loss in dB/m from `AirAbsorption` (ISO 9613-1, AX4)
     (Vorländer §3.6 Eq. 3.33–3.35; it enters Eyring as 4mV, §4.4.1 Eq. 4.32). It is **not** the
     pressure attenuation in Np/m (D/8.686), which would halve the 4·m_b·V term (≈ 8 % too long a T
     at 4 kHz in a 20×30×10 m room). Unit-test the conversion against one ISO 9613-1 value.
   - Eyring: `T60_b = 0.161·V / (−S·ln(1−ᾱ_b) + 4·m_b·V)`. Clamp ᾱ_b ≤ 0.999 so ln stays finite.
     For the `open_field` case (five surfaces at α = 1.0) Eyring does not apply (no diffuse field,
     Vorländer §4.4.1) and its nominal T60 need not be near 0. The tail is still absent because its
     **level** comes from energy matching (below), which only looks at arrivals in the 10 ms before
     `t_mix`: the direct sound and the floor reflection (specular and AX16 scattered part) arrive long
     before that window, and every later image hits an α = 1 face, so the window is empty and E_b = 0
     for any floor scattering s. No scene-specific logic is involved (NFR-8).
   - Expose `T60_b` for tests and UI display.
2. `src/sim/tail/MixingTime.h/.cpp` — `t_mix = max(20 ms, √V ms)` with V in m³ (the widely used
   √V-milliseconds estimate of perceptual mixing time; cite the source in a comment). Clamp it to the time covered by the
   ISM order the scene requests. If the requested order ends earlier, use that end time instead and log it.
3. `src/sim/tail/NoiseTail.h/.cpp` — for each emitter:
   - Generate Gaussian white noise (seeded, see AX5), split it into the 8 bands with the **same
     filterbank as Phase 03**, and apply the envelope `exp(−6.91·t / T60_b)` per band. Normalise each
     band to unit total energy. This **unmatched, unit-energy per-band decay** depends only on V, S,
     ᾱ_b, m_b, `tailSeed` (with the AX5 emitter/output offsets) and the sample rate. It is the object
     Phase 10 caches, so keep it as a separate value computed **before** E_b scaling, `t_mix` gating
     and the crossfade; those three are recomputed from the current image list on every rebuild
     (`t_mix` including its clamp to the ISM order's coverage, which depends on positions and
     `maxReflectionOrder`). The band signal is then `E_b · unitDecay_b(t)`, E_b an amplitude factor.
   - **Energy matching** (all quantities are band **energies**, i.e. squared pressure summed over
     samples, per band b):
     1. Build **one** time-binned energy envelope per band from Phase 03's image list: every image
        path's **specular** energy and its **AX16 scattered-energy entry**
        E_noScatter·(1 − Π(1 − s)^hits), both placed at the path's specular arrival time. Bins are
        10 ms wide and end at `t_mix` (bin 0 = `[t_mix − 10 ms, t_mix)`). The scattered entries are
        what keeps the tail from being too quiet: matching to specular energy alone would put it ≈ 9 dB
        low with s = 0.5 after 3 hits (Vorländer Eq. 3.23, Fig. 3.10; §11.6: scattered energy dominates
        after a few orders).
     2. Extrapolate the diffuse-field decay from bin 0 into `[t_mix, t_mix + 10 ms)`:
        E_target,b = E_bin0,b · exp(−13.82 · 0.010 s / T60_b) (energy falls 60 dB per T60_b).
     3. Set E_b so that the tail's energy in `[t_mix, t_mix + 10 ms)`,
        E_b² · Σ_window unitDecay_b², equals E_target,b. Match on the un-faded tail (before the
        crossfade below). This is a per-interval envelope match (cf. Vorländer §11.7 Eq. 11.51): both
        sides are energies per 10 ms at `t_mix`; nothing is accumulated from t = 0.
     - Arrivals earlier than `t_mix − 10 ms` (for example the direct sound and the `open_field` floor
       reflection, specular or scattered) do **not** set the tail level. With no specular or
       scattered arrival in bin 0, E_b = 0: the matched tail is zero.
     - The matching windows are part of this phase's spec and must be stated exactly in code and tests
       (they are the ones above); the open-field result depends on them.
   - **Crossfade** ISM → tail over 5 ms centred on `t_mix` (`[t_mix − 2.5 ms, t_mix + 2.5 ms]`). ISM
     and tail are uncorrelated, so the crossfade is **equal-power** (AX18; Vorländer §9.2.1: signal
     power in the overlap stays constant): with τ running from 0 to 1 across the 5 ms, the
     **amplitude** windows are w_ISM = cos(πτ/2) on the ISM and w_tail = sin(πτ/2) on the tail, so
     w_ISM² + w_tail² = 1. (Equal-gain windows, whose amplitudes sum to 1, dip by up to 3 dB mid-fade
     on uncorrelated signals.) Before the fade the tail is absent; after it, ISM contributions are
     dropped.
   - IR length: until the slowest band decays 90 dB below its start level, capped at **12 s**. The cap
     is the only bound (AX6 room limits allow T of order 160 s, e.g. α = 0.01 in a 100 m room); longer
     decays are **truncated** at 12 s, and T30 is measurable on a 12 s IR only for T ≤ ≈20 s (it needs
     ≥ 35 dB of decay).
4. Update `sim::buildRoomIR(Kind::Omni)` to return ISM + tail. Phase 08 will need decorrelated tails
   per ear; leave the hook as a per-output seed offset (`seed ^ (outputIndex · 0x9E3779B9)`).
5. Update golden metrics for all valid fixtures (this is an **intended** change; use
   `update_goldens.py --reason "phase 04 adds tail"`).
6. Add 6 test rooms to `tests/scenes/valid/` covering T60 from about 0.2 s to about 6 s
   (`dead_booth`, `living_room`, `classroom`, `club`, `concert_hall_box`, `stone_box`).

## Out of scope

Binaural tail coherence (08); validation against real rooms (05); any per-scene tuning (forbidden by NFR-8).

## Acceptance criteria — automated

- [ ] For the 6 test rooms, the measured **T30 is within ±5%** of the Eyring T60_b in bands
      250 Hz–4 kHz, and within ±10% at 125 Hz and 8 kHz, measured on an **AX11 ensemble-averaged
      decay curve** (`metrics.room_metrics_ensemble`) over R realisations with different `tailSeed`s.
      R per band follows AX11's rule R ≥ (σ₁ / (tol/3))², with σ₁ from AX11's table taken at the band's
      Eyring T60_b (see "Ensemble sizes" below). Single-realisation T30s are reported, not gated.
- [ ] Energy decay curve (Schroeder, per band) is monotonic, and the EDC shows **no step > 1 dB** in a
      5 ms window around `t_mix` (the seam test).
- [ ] Same scene + same seed gives a **bit-identical** IR on the same platform (run twice in one test).
      A different seed gives the same T30 within ±2% (the seed changes the noise, not the room), in
      bands 125 Hz–8 kHz: compared between **two independent AX11 ensembles** (disjoint `tailSeed`
      sets), each of R realisations from the rule with tol/√2 (see below). Single-realisation
      differences are reported, not gated.
- [ ] 44.1 kHz and 96 kHz renders of the same scene give the same T30/EDT/C80 within ±2% (bands up to 8 kHz).
- [ ] `open_field` gives no tail: E_b = 0 in every band, and the energy later than 50 ms after the
      direct sound's arrival is < −60 dB relative to the direct sound. Checked on the fixture (floor
      s = 0.4) **and** on a test-local variant with floor scattering s = 0.5: in both, bin 0 holds no
      specular or scattered arrival, so E_b = 0.

**Ensemble sizes (AX11).** R ≥ (σ₁ / (tol/3))² per band, rounded up; one ensemble per room uses the
largest R over its gated bands (more is allowed). σ₁ is AX11's measured single-realisation T30 scatter
(48 kHz); use the column of the tabulated T60 (0.3, 1.0, 6 s) at or just below the band's Eyring
T60_b, since σ₁ shrinks as T grows. For T60_b < 0.3 s scale the 0.3 s value by 0.3 s / T60_b
(σ₁² ∝ 1/T, AX11's 0.5/√(B·T)). The seed gate compares two ensemble means, whose difference has
√2 times the scatter of one, so it uses tol/√2: R ≥ (σ₁ / (2 % / (3·√2)))² = 4.5·σ₁² (σ₁ in %).

| band | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|
| σ₁ at T60 0.3 / 1.0 / 6 s (%) | 10 / 6.7 / 1.8 | 8 / 4.4 / 1.3 | 6 / 2.7 / 1.2 | 3.4 / 1.5 / 0.5 | 2.7 / 1.4 / 0.3 | 1.9 / 1.0 / 0.5 | 1.3 / 1.0 / 0.3 |
| Eyring gate tol | ±10 % | ±5 % | ±5 % | ±5 % | ±5 % | ±5 % | ±10 % |
| R, Eyring gate, T60 0.3 / 1.0 / 6 s | 9 / 5 / 1 | 24 / 7 / 1 | 13 / 3 / 1 | 5 / 1 / 1 | 3 / 1 / 1 | 2 / 1 / 1 | 1 / 1 / 1 |
| R per ensemble, seed gate (±2 %), T60 0.3 / 1.0 / 6 s | 450 / 203 / 15 | 288 / 88 / 8 | 162 / 33 / 7 | 53 / 11 / 2 | 33 / 9 / 1 | 17 / 5 / 2 | 8 / 5 / 1 |

63 Hz is in neither gate (σ₁ up to 18 %). Example: `dead_booth` at T60_b ≈ 0.2 s needs
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

Energy matching at `t_mix` (units, band energies vs amplitudes, the one binned envelope of specular +
AX16 scattered energy), m_b as the energy coefficient D/4.34, the equal-power crossfade, the cached
unit-energy decay being independent of positions, the AX11 ensemble sizes, PRNG portability,
filterbank reuse, and IR truncation.

## Risks

- Eyring is known to be inaccurate for strongly non-uniform absorption (e.g. one absorbent ceiling).
  Note it as an input for Phase 05 and the Expert; don't patch it with per-scene factors.
- An audible seam at `t_mix`. Mitigated by the energy-matched crossfade and the seam test.

## Definition of done

All automated criteria green; status row 04 `done`; listening checklist in the PR.
