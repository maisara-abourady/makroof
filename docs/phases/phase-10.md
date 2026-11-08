# Phase 10 — Artifact-free movement under automation

Size: **M** · Depends on: 06, 07, 08, 09 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ10, AX1, AX18, AX20, AX22, AX33), PRD FR-SIM-6, NFR-3, Q4

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3).

## Assumptions in force

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
- **AX18**: equal-gain crossfade for position updates; **equal-power** for large jumps (e.g. the
  corner-to-corner step scenarios) and output-mode toggles, where the IRs are unrelated. Equal-gain
  for position updates is a placeholder (AX18 amendment); this phase sets the law.
- **AX22**: Phase 04's realised-k switch. t_mix,e is continuous in position, but the fallback to
  ISM-only up to the image-count cap is a single jump point in source position. Across it the IR segment
  between t_mix,e and t_cap,e is ISM in one IR and noise in the other, so AX18's equal-gain premise
  (correlated consecutive IRs) does not hold there, and the 30 ms position crossfade dips in that segment: 3 dB at mid-fade for any power ratio of the two
  uncorrelated segments; the largest dip relative to the power-linear interpolation of the two segments
  grows with their power ratio, ≈ 4.4 dB at 10:1, at g ≈ 0.24 of the fade (Vorländer Eq. 4.14). The total output dip is gated in this
  phase (acceptance criteria) (decider report 8, accepted by Maisara, 2026-11-05).
- **AX1**: no Doppler. Movement is a sequence of crossfaded static IRs. Fast moves sound slightly
  smeared rather than pitch-shifted. That's intended, and the PR must describe it.

## Scope

1. **Automation in `render_cli`:** implement `--automation <json>`: a list of `{paramId, points:
   [[timeSec, normalizedValue], ...]}` with linear interpolation. render_cli drives the same
   `module3d::ParameterMap` and builder logic as the plugin, in **both** modes:
   - `--offline` (default): synchronous rebuild per block whenever parameters changed (the plugin's
     non-realtime path).
   - `--realtime-sim`: the builder runs on a real background thread with the 20 ms cadence. The audio loop
     runs as fast as possible, but the *simulated* clock decides when the builder's results are picked up,
     so behaviour is reproducible for tests. Document the mechanism.
2. **Tail cache:** cache the Phase 04/08/09 **unmatched, unit-energy per-band noise decay** (Phase 04
   scope 3: it depends only on V, S, ᾱ_b, m_b, `tailSeed` and the sample rate, per output for 08/09),
   stored **before** E_b scaling, `t_mix,e` gating and the ISM→tail crossfade. Key it by (room
   dimensions, materials, mode, seed, sample rate). Every rebuild, including a position-only one,
   recomputes the early part, the AX16 scattered-energy list, each emitter's `t_mix,e` (it follows the
   emitter's direct-arrival time, so it depends on positions), the AX20 time-bounded image list (every
   image of any order arriving before t_mix,e + 2.5 ms; `maxReflectionOrder` has no effect on it), E_b
   (against ē_b, which depends only on T60_b, t_mix,e on the cached decay's emission-referenced time
   axis and the IR length) and the crossfade from the new image list. Prove the
   result equals a full rebuild (test), including a move that changes t_mix,e and the time-bounded
   image list.
3. **Rebuild scheduling:** the builder always works on the newest scene (coalescing). If a build takes
   longer than 20 ms, the next build starts immediately with the latest scene. The audio thread keeps
   using the last IR and never blocks. Track and expose "IR staleness" (time between the parameter
   change and the IR going live) as a debug metric.
4. **Parameter smoothing:** the 20 ms output-trim smoothing stays. Positions aren't smoothed per sample
   (they only drive IR rebuilds). Room-size changes go through the same path.
5. **Negative control:** a build flag `MAKROOF_TEST_HARD_SWITCH` (test builds only) replaces the crossfade
   with an instantaneous IR switch. The click detector **must** flag that build. This proves the detector
   catches the problem this phase solves.
6. **Automation scenario suite** `tests/automation/*.json` (20 scenarios): slow and fast linear sweeps of
   the listener and each emitter across the room; step jumps (corner to corner) every 250 ms; sinusoidal
   oscillation at 0.1, 1, 2 and 5 Hz; room size sweeps from min to max; output-mode toggles mixed with
   movement; all parameters at once.
7. CI job `automation` (Linux in every PR; macOS/Windows too, since it's fast with short renders) runs all
   scenarios × 2 modes × {offline, realtime-sim} through `render_cli` with the sustained-tone input and
   runs `clicks.py`.
8. **Isolated-update cap:** confirm or replace AX33 (Phase 07: minimum 20 ms spacing between build
   starts; an isolated request starts at once) and state the resulting isolated-update delay (at most
   rebuild + 2P, AX31).

## Out of scope

Doppler / interpolated delay lines (would need a new AX entry and Expert input), dynamic reduction of the
image list while moving (it would change AX20; needs an AX entry if introduced).

## Acceptance criteria — automated

- [ ] All 20 scenarios × 2 modes × 2 timing modes: **0 click events** (Phase 02 detector, default threshold).
- [ ] Negative control (`MAKROOF_TEST_HARD_SWITCH`) is flagged in ≥ 18 of 20 scenarios. (Scenarios with
      no effective IR change may legitimately pass.)
- [ ] Offline render of every scenario is **bit-identical** across two runs.
- [ ] A static scene renders identically (within −120 dB) in offline and realtime-sim modes.
- [ ] Tail-cache result equals a full rebuild within −120 dB.
- [ ] **AX22 switch point:** a test scene and a position move that cross a realised-k switch point
      (ISM-only fallback on one side, tail from t_mix,e on the other). Measured per output channel and
      octave band (500 Hz, 1 kHz, 2 kHz; AX14 rule if adjacent bands differ > 15 dB) as the expected
      instantaneous output power for a stationary input, computed from the two IRs:
      P(g) = (1−g)²E₁ + g²E₂ + 2g(1−g)C₁₂ (E full-IR band energies, C₁₂ their band cross-energy),
      against R(g) = (1−g)E₁ + gE₂, at every sample of the 30 ms ramp (instantaneous, no averaging
      window; valid because Phase 06 gates the crossfade to the analytic one within −100 dB).
      **Gate:** max_g of −10·log10(P/R) ≤ 1 dB. Reported: the dip at each g, the fade-averaged dip, ρ,
      f (the segment's share of R(g*)), and the predicted worst case 10·log10(1 − f(1+ρ)/(1+√ρ)²) at
      g* = 1/(1+√ρ). That prediction is for the segment only; the equal-gain dip of the correlated rest
      when E₁ ≠ E₂ comes on top, and the gate, computed from P(g) with C₁₂, includes it. The predicted
      worst case is ≤ 1 dB when f ≤ 0.2057(1+√ρ)²/(1+ρ): 0.41 at ρ = 1, 0.32 at ρ = 10, 0.21 for any ρ.
      Instrument self-test: two independent seeded noise IRs at ρ = 10, f = 1 give 4.37 ± 0.1 dB at
      g = 0.24 ± 0.01. This holds only with residual normalised cross-energy |ρ_c| ≤ 0.023 at 3σ, so use
      noise IRs with 2BT ≥ 1.7·10⁴ per band (≈ 24 s at 500 Hz), or set the tolerance from 3/√(2BT) for
      the chosen length (derived, not corpus). With a transient input the segment's own dip (up to
      4.4 dB at 10:1) is reported, not gated (Vorländer Eq. 4.14, §1.7). The 1 dB is G's jnd (Table 6.1,
      stated for 500–1000 Hz), applied to a 30 ms dip by extension. If the gate fails, this phase
      proposes a time-segment-split crossfade as a new AX (decider report 8; measurement and formula:
      decider report 11, FR-01, with the interrogator's corrections, report 12; accepted by Maisara,
      2026-11-05).
- [ ] **Position-fade gate (AX18 amendment):** every movement scenario states its speed in m/s and its
      measured update interval. At each IR switch, per output channel and octave band 500 Hz, 1 kHz,
      2 kHz (AX14 rule as above): P(g) = a(g)²E₁ + b(g)²E₂ + 2a(g)b(g)C₁₂ for the law's ramps a, b,
      against R(g) = (1−g)E₁ + gE₂ at every ramp sample. **Gate:** max_g |10·log10(P/R)| ≤ 1 dB (dips
      and bumps; G's jnd, Vorländer Table 6.1, 500–1000 Hz, extended to 2 kHz and a 30 ms fade).
      Report ρ_b = C₁₂/√(E₁E₂) per band. If equal-gain fails, propose a law as a new AX, e.g. a
      per-band or time-segment crossfade, or a correlation-matched law applied per band (Fink, Holters,
      Zölzer 2016, DAFx-16, Eq. 11, ρ from the two IRs; researcher F20). Known limit: at ρ = 1 a band
      step ≳ 8.5 dB between consecutive IRs exceeds 1 dB under any single-gain law (Fink's
      equal-power-assumption law included); this phase either defines the gate's domain or proposes an
      energy-aware law. Each scenario reports its largest band step (Phase 07 decision loop
      2026-11-08, decider round 2 §4, advocate round 2).
- [ ] Worst-case IR staleness in realtime-sim ≤ **100 ms** in all scenarios (recorded in the CI log;
      failing it fails the job). The hybrid IR's image list is time-bounded (AX20), so its size follows
      t_mix,e and the room, not `maxReflectionOrder`. If the ≤ 100 ms staleness gate fails only because
      of a recorded AQ10 miss, this phase may apply the phase-13 scope 1 optimisations (output unchanged
      beyond −100 dB). If it still fails, the phase is `blocked (AQ10 miss)` and Maisara chooses between
      (a) a smaller N_cap (an output change; the AX22 sensitivity report shows the accuracy cost) and
      (b) for fallback scenes only, a staleness bound taken from Vorländer Table 15.1 (700 ms,
      translation > 0.25 m). The gate is not loosened otherwise (decider report 8, accepted by Maisara, 2026-11-05).
- [ ] No allocation in `processBlock` during the automation scenarios (AllocationTracker through the plugin processor).
- [ ] pluginval strictness 10 passes (its automation test exercises this path too).

## Listening / manual checklist (Maisara)

In Logic and one VST3 host, on a sustained pad *and* on drums, both output modes:
- [ ] Automate the L and R emitters from 1 m to 15 m away and back over 8 bars: smooth change in distance,
      no clicks, zipper noise or level pumping.
- [ ] Jump the listener between two corners every beat: the room snaps cleanly, with no clicks.
- [ ] Sweep the room size over 4 bars: smooth.
- [ ] Fast moves sound slightly "washy" but not pitch-wobbly. That's the intended no-Doppler design.
      Say if you'd prefer audible Doppler; that's a product decision.
- [ ] Bounce offline: the bounce sounds like the realtime playback.

## Contractor review focus

Scheduling and coalescing logic, cache-key completeness (a stale tail is a nasty bug), the realtime-sim
clock mechanism, and whether the negative control really exercises the same code path.

## Risks

- IR rebuild cost in large rooms (the AX20 image list grows with t_mix,e, whatever `maxReflectionOrder`
  is) could exceed the 20 ms cadence and cause visible staleness. Measure it. If it's too slow, propose
  (don't implement) a reduction of the image list while moving as an AX entry (it would change AX20).
- The click detector's blind spots for very low-frequency artifacts (thumps below 2 kHz). Add one scenario
  with a 40 Hz tone and a low-band detector variant if cheap.

## Definition of done

All automated criteria green; staleness numbers in the status notes; status row 10 `done`.
