# Phase 09 — Stereo-speaker output mode

Size: **S** · Depends on: 07, 08 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ7, AX3), PRD FR-SIM-3, FR-SIM-5, Q7

## Goal

`outputMode = stereoSpeakers`: render the scene for a neutral pair of loudspeakers (PRD FR-SIM-5, no
room calibration) and let the user switch between this mode and binaural.

## Assumptions in force

- **AQ7**: a **virtual ORTF pair** at the listener position: two cardioid capsules aimed ±55° from the
  listener's facing direction (AX3 yaw), spaced 17 cm apart on the interaural axis. No crosstalk
  cancellation. Q7 is still open with the Expert, so keep this behind the `StereoSpeakers` kind so it can
  be swapped out.

## Scope

1. `src/sim/stereo/VirtualMicPair.h/.cpp`:
   - Cardioid gain `g(θ) = 0.5·(1 + cos θ)` for the angle between the arrival direction and each
     capsule's axis (3D: use the full direction, not just azimuth). Frequency-independent in v1 (an ideal
     capsule); note this.
   - Capsule position offset: each arrival is delayed per capsule by the projection of ±8.5 cm onto the
     arrival direction / c (fractional delay, same kernel as Phase 03).
2. **Early part:** for each image source, accumulate its band-filtered amplitude × capsule gain into
   output L/R at the arrival time plus the capsule delay. Reuse the Phase 08 accumulation structure
   (same grouping rule).
3. **Late tail:** two decorrelated tails mixed to the diffuse-field coherence of the ORTF pair (compute
   the target per band analytically for two cardioids at ±55°, 17 cm apart, in a diffuse field; document
   the formula), with the Phase 04 per-band envelopes.
4. **Level match:** normalize so the integrated loudness (ITU-R BS.1770, via `pyloudnorm` in tests,
   pinned) of pink noise through the reference scene matches binaural mode within ±1 dB.
   The normalization is a fixed constant derived once from the diffuse-field gain of the mic pair, not a
   per-scene auto-gain (AX2).
5. Plugin: `output_mode` parameter now switches `Kind`. The switch triggers an IR rebuild and the Phase 06
   crossfade, so it's smooth. The two modes' IRs are unrelated, so this switch uses the **equal-power**
   crossfade (AX15: equal-gain would dip ≈3 dB mid-fade on uncorrelated outputs).
6. `render_cli --mode stereoSpeakers`, listening pack, goldens.

## Out of scope

Crosstalk cancellation, speaker calibration, multichannel output (PRD out of scope).

## Acceptance criteria — automated

- [ ] Anechoic scene, point source at 5 m: the measured L−R level difference equals the value computed
      from exact geometry (each capsule's own angle to the source in the cardioid 0.5(1+cos ϑ) and its
      own distance in 1/r) within ±0.5 dB at φ ∈ {0°, ±30°, ±55°, ±90°}, positive for positive φ
      (toward the left capsule) and mirrored for negative φ. The left channel's level as a function of φ
      peaks within ±3° of the geometric prediction (≈+56.7° at 5 m). Plane-wave sanity values: 9.7 dB at
      55° and 20.1 dB at 90° (±0.5 dB).
- [ ] A centre emitter gives |L−R| < 0.1 dB and inter-channel delay of 0 samples.
- [ ] Inter-channel time difference for an emitter at 90° equals 17 cm / c (±1 sample at 48 kHz).
- [ ] Tail inter-channel coherence per band within ±0.1 of the analytic ORTF diffuse-field target.
- [ ] Loudness: |LUFS(stereoSpeakers) − LUFS(binaural)| ≤ 1 dB for the reference scene and for 3 other fixtures.
- [ ] Mono compatibility: summing L+R of a centre-emitter render shows no comb-filter notch deeper than
      6 dB below 2 kHz.
- [ ] Mode switch during playback: the click detector (Phase 02) reports 0 events across 10 switches.
- [ ] All earlier tests and pluginval still pass.

## Listening / manual checklist (Maisara, Adam monitors via RME, sitting in the sweet spot)

- [ ] Default scene: stable phantom centre, with L/R emitters spread roughly as placed.
- [ ] Rooms are clearly audible and distinguishable on speakers (small vs large hall).
- [ ] Switch `output_mode` between binaural and stereoSpeakers during playback: smooth, roughly equal loudness.
- [ ] On headphones, stereoSpeakers mode should sound like a decent room recording (less 3D than binaural, as expected).
- [ ] Check in mono (RME mono switch or DAW utility): nothing disappears or becomes hollow.

## Contractor review focus

The cardioid and capsule-delay geometry, the diffuse-field coherence formula, and normalization between modes.

## Risks

Users may expect the binaural sense of height or depth on speakers. Set expectations in UI text in Phase 11.

## Definition of done

All automated criteria green; status row 09 `done`; checklist in the PR.
