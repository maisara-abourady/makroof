# Phase 03 — Early reflections: shoebox image-source model (omni)

Size: **M** · Depends on: 01, 02 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ1, AQ2, AQ3, AQ8, AX1, AX2, AX4, AX6), PRD FR-SIM-2, NFR-1, NFR-8

## Goal

A correct, **per-octave-band image-source method (ISM)** for shoebox rooms. It produces the early
part of the room IR for an omnidirectional receiver at the listener position, for each emitter. This is
the first real acoustics in the project, so it's checked against analytic geometry and against an
independent implementation (pyroomacoustics).

## Assumptions in force

- **AQ2**: hybrid method; ISM is the early part. **AQ3**: specular reflection uses α per band;
  scattering removes energy from the specular path. **AQ8**: emitters are omni (keep a directivity hook).
- **AX1**: time alignment. Shift the whole multi-emitter IR so the earliest direct arrival is at
  t = `kAlignPreRollSamples` (a small constant, e.g. 32 samples, so fractional-delay kernels aren't
  truncated; it becomes part of the reported latency later). Relative delays are kept.
- **AX2**: level. The direct path at 1 m is gain 1.0 and amplitude scales with 1/r.
- **AX4**: air absorption from ISO 9613-1 at 20 °C, 50% RH, 101.325 kPa, evaluated at band centres,
  applied per path length.

## Scope

1. `src/sim/ism/ImageSources.h/.cpp`
   - Enumerate image sources of a shoebox for reflection order ≤ `maxReflectionOrder` (standard
     lattice enumeration: indices `(nx, ny, nz)` and parity bits `(px, py, pz)`; reflection counts
     per surface derived from them; all images in a shoebox are valid, so no visibility test is needed).
   - For each image: path length r, arrival time r/c (c = 343.0 m/s at 20 °C, a named constant), and
     per-band amplitude
     `A_b = (1/r) · Π_surfaces (√(1−α_{s,b}) · √(1−scat_s))^{hits_s} · air_b(r) · directivity_b(dir)`.
     `directivity_b` returns 1.0 (omni) in v1. It's an interface stub for B7 (dispersion).
   - Also output the **direction of arrival** at the listener (unit vector from listener to image).
     Phase 08 needs it, and stereo-speaker mode needs it in Phase 09.
   - Output the **scattered energy** removed at each reflection (per band, with arrival time) as a
     separate energy list. Phase 04 feeds it into the tail.
2. `src/sim/ism/BandRenderer.h/.cpp` — build a broadband pressure IR from per-band image amplitudes:
   - For each band, accumulate a sparse train of fractional-delay impulses (windowed-sinc kernel,
     length 33, Kaiser β = 8) into a per-band buffer.
   - Filter each band buffer with that band's filter from a **linear-phase, perfect-reconstruction
     octave filterbank** (FIR, designed once per sample rate; the sum of all 8 band filters = a delayed
     delta within −100 dB). Above 8 kHz, extend the top band to Nyquist and below 63 Hz extend the
     bottom band to DC.
   - Sum the bands. Remove the filterbank's constant group delay so peaks land at their true times.
3. `src/sim/AirAbsorption.h/.cpp` — ISO 9613-1 attenuation coefficient per band (dB/m), with a unit
   test against the standard's published table values at 20 °C/50% RH.
4. Wire into `sim::buildRoomIR` for `Kind::Omni`. For each emitter, output 0 and output 1 receive the
   same omni IR (mono room preview). Truncate after the last image arrival plus the kernel length.
   The tail comes in Phase 04.
5. `render_cli --mode omni` uses this.
6. Benchmark (Catch2 `BENCHMARK`): order 30, 20×30×10 m room, 48 kHz, 2 emitters. Record the time in
   the CI log. AQ10 targets ≤ 50 ms; don't optimize prematurely, just measure.

## Out of scope

Late tail (04), binaural directions applied as HRTFs (08), real-time convolution (06), source directivity models (B7).

## Deliverables

`src/sim/ism/*`, `src/sim/AirAbsorption.*`, updated `Engine.cpp`, unit tests, pytest cross-checks,
golden metrics for 3 fixtures (`small_room`, `medium_room`, `large_hall`) at order 10, listening pack entries.

## Acceptance criteria — automated

- [ ] **Geometry:** for 200 random valid scenes, every image arrival time equals ‖image − listener‖/c to
      within 1e-9 s (unit test on the enumerator). In rendered IRs, the first 50 peaks match those times
      to ±1 sample (`compare.py`).
- [ ] **Independent cross-check (pytest):** for 10 random rooms with frequency-independent absorption
      (same α in all bands, scattering 0, no air absorption), the first 50 reflections' amplitudes,
      relative to the direct sound, match `pyroomacoustics.ShoeBox(..., max_order=N,
      materials=pra.Material(energy_absorption=α))` within **±0.5 dB**, and arrival times within ±1 sample.
- [ ] **Reciprocity:** swapping emitter and listener positions gives the same omni IR within −120 dB
      (residual energy relative to IR energy).
- [ ] **Symmetry:** a source and listener placed symmetrically in a room with symmetric materials give
      mirror-identical image sets.
- [ ] **Limits:** all α = 1.0 gives the direct path only. `maxReflectionOrder = 0` gives the direct path only.
- [ ] **Filterbank:** flat band gains (all 1.0) reproduce a delta within −100 dB. A single band at gain 1
      and the others at 0 gives a response whose octave-band energy is ≥ 20 dB above the neighbouring bands.
- [ ] **Per-band check:** a room with α = 0.9 above 1 kHz and α = 0.1 below gives reflections whose
      measured per-band levels (via `bands.py`) match the expected Π√(1−α) within ±1 dB for orders 1–3
      (scattering 0; air absorption off, or its 4.34·m·r dB per band included in the expected value).
- [ ] Air-absorption table test passes (within ±5% of ISO 9613-1 table values at band centres).
- [ ] Golden metrics committed. Benchmark result printed in CI.

## Listening / manual checklist (Maisara)

Listening-pack artifact, headphones or monitors (mono room preview, so both channels are identical):
- [ ] **Clicks** in `small_room`, `medium_room`, `large_hall`: a dense cluster of echoes that spreads
      out and gets later as the room gets larger. No tail yet, so they stop abruptly. That's expected.
- [ ] `asymmetric_materials` sounds duller than `medium_room` on the clicks.
- [ ] **Pink bursts:** no pitched "ringing" except a flutter-echo between hard parallel walls,
      which is physically correct.
- [ ] `open_field`: dry click plus one ground reflection right after.

## Contractor review focus

Image enumeration and reflection counts per surface; amplitude formula (pressure vs energy
coefficients: √(1−α) on pressure); filterbank design (perfect reconstruction, group-delay removal);
fractional-delay kernel; that scattering is applied as (1−s) on energy.

## Risks

- Band filtering smearing transients. The filterbank is linear-phase, so check peak sharpness in `compare.py`.
- Image count grows as O(N³). Order 60 is the contract maximum; measure it, cap it later if needed
  (that would need an AX entry).

## Definition of done

All automated criteria green; status row 03 `done`; listening checklist and benchmark number in the PR.
