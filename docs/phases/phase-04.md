# Phase 04 — Late reverberant tail + hybrid room IR

Size: **M** · Depends on: 03 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ2, AQ3, AX4, AX5), PRD NFR-1, NFR-8

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

## Scope

1. `src/sim/tail/Decay.h/.cpp` — per band b:
   - S = total surface area, ᾱ_b = area-weighted mean absorption, V = W·D·H.
   - m_b = air attenuation coefficient in nepers/m (from `AirAbsorption`, converted).
   - Eyring: `T60_b = 0.161·V / (−S·ln(1−ᾱ_b) + 4·m_b·V)`. Clamp ᾱ_b ≤ 0.999 so ln stays finite.
     For the `open_field` case (five surfaces at α = 1.0) Eyring does not apply (no diffuse field,
     Vorländer §4.4.1) and its nominal T60 need not be near 0. The tail is still absent because its
     **level** comes from energy matching (below): with no ISM or scattered energy around `t_mix`, the
     matched tail is zero. No scene-specific logic is involved (NFR-8).
   - Expose `T60_b` for tests and UI display.
2. `src/sim/tail/MixingTime.h/.cpp` — `t_mix = max(20 ms, √V ms)` with V in m³ (the widely used
   √V-milliseconds estimate of perceptual mixing time; cite the source in a comment). Clamp it to the time covered by the
   ISM order the scene requests. If the requested order ends earlier, use that end time instead and log it.
3. `src/sim/tail/NoiseTail.h/.cpp` — for each emitter:
   - Generate Gaussian white noise (seeded, see AX5), split it into the 8 bands with the **same
     filterbank as Phase 03**, and apply the envelope `e_b(t) = E_b · exp(−6.91·t / T60_b)` per band.
   - **Energy matching:** set E_b so the tail's band energy in a 10 ms window just after `t_mix`
     equals the energy the statistical model predicts at that time. Use the diffuse-field decay
     extrapolated from the ISM's band energy over `[t_mix − 10 ms, t_mix]`, **plus** the scattered
     energy collected by Phase 03 up to that time. This keeps the energy budget consistent.
     - The onset energy is the **specular ISM energy plus the accumulated scattered energy**, taken from
       Phase 03's scattered-energy list as defined in **AX16**: one entry per image path,
       E_noScatter·(1 − Π(1 − s)^hits) per band at the path's specular arrival time (Vorländer Eq. 3.23,
       Fig. 3.10; §11.6: scattered energy dominates after a few orders).
       Matching to specular energy alone would make the tail too quiet (≈9 dB low with s = 0.5 after
       3 hits).
     - With no ISM and no scattered energy around `t_mix`, E_b = 0: the matched tail is zero.
     - The matching windows are part of this phase's spec and must be stated exactly in code and tests
       (they are the ones above); the open-field result depends on them.
   - **Crossfade** ISM → tail over 5 ms around `t_mix` with complementary cos² windows applied to both
     signals. Before `t_mix`, the tail is absent; after it, ISM contributions are dropped.
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

- [ ] For the 6 test rooms, the measured **T30 (metrics.py) is within ±5%** of the Eyring T60_b in bands
      250 Hz–4 kHz, and within ±10% at 125 Hz and 8 kHz.
- [ ] Energy decay curve (Schroeder, per band) is monotonic, and the EDC shows **no step > 1 dB** in a
      5 ms window around `t_mix` (the seam test).
- [ ] Same scene + same seed gives a **bit-identical** IR on the same platform (run twice in one test).
      A different seed gives the same T30 within ±2% (the seed changes the noise, not the room).
- [ ] 44.1 kHz and 96 kHz renders of the same scene give the same T30/EDT/C80 within ±2% (bands up to 8 kHz).
- [ ] `open_field` gives no tail (energy after 50 ms < −60 dB relative to the direct sound).
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

Energy matching at `t_mix` (units, band energies vs amplitudes), Eyring with air absorption, PRNG
portability, filterbank reuse, and IR truncation.

## Risks

- Eyring is known to be inaccurate for strongly non-uniform absorption (e.g. one absorbent ceiling).
  Note it as an input for Phase 05 and the Expert; don't patch it with per-scene factors.
- An audible seam at `t_mix`. Mitigated by the energy-matched crossfade and the seam test.

## Definition of done

All automated criteria green; status row 04 `done`; listening checklist in the PR.
