# Phase 08 — Binaural output with a generic HRTF

Size: **L** (plan for two sessions; split into 08 and 08b if needed) · Depends on: 04, 07 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1

## Goal

Headphone rendering (`outputMode = binaural`). Every early reflection reaches the listener's ears from
its true direction through a measured **generic HRTF**, and the late tail has the interaural coherence
of a diffuse field. The result is a 2-emitter × 2-ear binaural room impulse response (BRIR) applied by
the Phase 06 convolver.

## Assumptions in force

- **AQ6**: one generic HRTF, with the contract `hrtfId = "generic-v1"`. No personalization (deferred, B4).
- **AX3**: the head is upright, and yaw points toward the horizontal centroid of the emitters. If the
  centroid is within 0.1 m horizontally of the listener, the previous yaw is held (initial yaw = +y).
- **AX5**: deterministic; tail noise per ear is seeded from `tailSeed` with the per-output offset from Phase 04.

## Scope

### Session 1: HRTF data and lookup

1. **Licence first.** Pick the dataset: preferred is **SADIE II** (University of York), KU100 or KEMAR
   subject, 48 kHz, in SOFA format. Read its licence on the official site and record the licence text
   and attribution in `resources/hrtf/LICENSE-generic-v1.txt` and `docs/THIRD_PARTY.md`. If the licence
   doesn't allow commercial redistribution of derived data, fall back to **MIT KEMAR**, and check that
   licence the same way. If neither is clearly allowed, mark the phase `blocked` and escalate. Don't ship
   data under an unclear licence.
2. `tools/hrtf/convert_sofa.py` (uses `sofar` or `netCDF4`/`h5py`, pinned) — reads the SOFA file,
   resamples to 44.1/48/88.2/96 kHz (high-quality polyphase), trims to a common length (e.g. 256 taps
   at 48 kHz, scaled for other rates), removes the common onset delay while keeping the ITD as a
   separate per-direction value (`onset_left`, `onset_right` in fractional samples), and writes
   `resources/hrtf/generic-v1.bin` (a simple versioned binary: header, direction grid, minimum-phase or
   raw HRIRs, ITDs). The original SOFA is downloaded by checksum, **never committed**.
3. `src/sim/hrtf/HrtfSet.h/.cpp` — loads the embedded binary (via a generated C++ byte array or
   CMake `add_custom_command` resource step; `sim` stays JUCE-free). Lookup:
   - `query(azimuth, elevation) → {hrirL, hrirR, itd}` with interpolation: triangulate the measurement
     grid (spherical Delaunay computed offline in the converter and stored), then barycentric
     interpolation of magnitude-aligned (onset-removed) HRIRs. ITD is interpolated separately and
     re-applied as a fractional delay.
   - **Diffuse-field equalization** of the set (computed in the converter, stored as an EQ filter), so the
     generic HRTF doesn't add a strong overall colouration. Keep the EQ switchable in code for tests.

### Session 2: BRIR assembly and tail

4. `src/sim/binaural/ListenerFrame.h/.cpp` — AX3 orientation; converts world-space directions of
   arrival (from Phase 03 image sources) into head-relative azimuth/elevation.
5. `src/sim/binaural/BrirBuilder.h/.cpp` — for each emitter:
   - **Early part:** for each image source (from Phase 03, using its per-band amplitude, delay and
     direction), add `band-filtered(amplitudes) * HRIR(direction)` into the left and right ear buffers at
     the arrival time plus the per-ear ITD. For efficiency, group image sources by direction cell (e.g. 2°
     bins) above reflection order 3 and render each group once. Document the approximation and make sure the
     direct path and orders 1–3 are never grouped.
   - **Late tail:** two noise tails (left/right seeds) with the Phase 04 per-band envelopes, then mixed per
     band so the **interaural coherence** follows the diffuse-field model for a head: compute the target
     coherence per band from the HRTF set itself (diffuse-field average of the interaural cross-spectrum,
     done in the converter), and apply it with the standard 2×2 mixing
     (`L = a·n1 + b·n2, R = a·n1 − b·n2` with a and b set from the target coherence), then apply the
     diffuse-field HRTF magnitude per ear.
   - Energy: the binaural BRIR's per-band energy (average of the two ears, diffuse-field equalized)
     equals the omni IR's per-band energy within ±1 dB. This keeps levels consistent between modes.
6. `sim::buildRoomIR(Kind::Binaural)` returns the 2×2 BRIR matrix: emitter L → ear L/R and emitter R →
   ear L/R. The plugin sends `outputMode` through, so `binaural` now uses this path. `stereoSpeakers`
   keeps using omni until Phase 09.
7. `render_cli --mode binaural`, listening-pack entries, goldens for 3 scenes.

## Out of scope

Personalized HRTF / SOFA import (B4), head tracking and head orientation control (PRD out of scope),
near-field HRTF correction (sources < 1 m; note it as a follow-up).

## Acceptance criteria — automated

- [ ] Licence file present and `docs/THIRD_PARTY.md` updated (a CI script fails if `resources/hrtf/*.bin`
      exists without the matching `LICENSE-*.txt`).
- [ ] Converter round-trip: HRIRs decoded from `generic-v1.bin` match the SOFA source (resampled) within
      −60 dB at measured directions.
- [ ] **ITD/ILD sanity** (anechoic scene: α = 1 everywhere, direct path only): an emitter at +90°
      azimuth (left; define the azimuth sign convention in the code and docs) gives ITD between **0.6 and
      0.75 ms** with the left ear leading, and ILD > 6 dB averaged over 2–8 kHz. The mirror holds at −90°.
      An emitter straight ahead gives |ITD| < 20 µs and |ILD| < 1 dB.
- [ ] **Interpolation continuity:** sweeping azimuth in 1° steps never changes broadband level by more than
      1 dB or ITD by more than 30 µs per step.
- [ ] **Tail coherence:** measured interaural coherence of the late tail per band is within ±0.1 of the
      target curve (125 Hz–4 kHz).
- [ ] **Energy:** binaural vs omni per-band energy within ±1 dB for all valid fixtures.
- [ ] **Orientation (AX3):** a unit test with emitters ahead, behind and on top of the listener gives
      the documented yaw, and the hold rule triggers at < 0.1 m.
- [ ] T30 of each ear's BRIR within ±5% of the omni IR's T30 (250 Hz–4 kHz).
- [ ] All earlier tests still pass. pluginval passes. Plugin CPU benchmark is recorded.

## Listening / manual checklist (Maisara, headphones)

Listening pack (`binaural/`) and the plugin in a DAW with `output_mode = binaural`:
- [ ] Default scene with emitters at about ±30° ahead: the stereo image sits **in front** and outside your head.
      (Generic HRTFs often sound slightly "inside" or "above" for some people. Note what you hear; that's
      what B4 is for.)
- [ ] `anechoic_azimuth_sweep.wav`: a sound circling the head. It should be clearly left, right and
      front. Front/back confusion is common with generic HRTFs, so note it.
- [ ] Move the listener close to the L emitter: the image pulls left and the room recedes.
- [ ] Large hall: the reverb surrounds you rather than sitting between the ears like a normal stereo reverb.
- [ ] Note any colouration (boxy, harsh, thin) compared with the omni preview.

## Contractor review focus

Licence review, HRIR interpolation (triangulation, ITD handling), coordinate and sign conventions, the
image-source grouping approximation, the diffuse-coherence mixing, and energy normalization between modes.

## Risks

- Generic HRTFs cause front/back confusion and weak externalization for some listeners. This is an
  expected limitation, recorded as evidence for B4.
- F8: the head always faces the emitters, so sources can't be put behind the listener. Report it if it
  sounds odd in practice.
- BRIR build time with many image sources. The grouping keeps it within budget; measure it against AQ4's 20 ms cadence.

## Definition of done

All automated criteria green; licence verified; status row 08 `done` (or 08b added); checklist in the PR.
