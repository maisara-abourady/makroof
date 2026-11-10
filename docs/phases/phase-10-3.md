# Phase 10-3 — Crossfade law and artefact gates under movement

Size: **M** (remainder, if needed: `10-3b`) · Depends on: 06, 07, 08, 09, 10-2 (and 10-1 through it) · Part of: [phase-10](phase-10.md) · Lead subject matter: Seat 3 (Reverb renderer), "time variance under motion and automation (crossfades, zipper, clicks, metallic tails); coloration" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AX1, AX18, AX22), PRD FR-SIM-6, NFR-3, Q4, the umbrella [`phase-10.md`](phase-10.md)

## Goal

Automated listener and emitter movement never produces clicks, zipper noise or dropouts, in either
output mode, while staying deterministic in offline bounces (PRD FR-SIM-6, NFR-3). (phase-10 goal, shared)

This sub-phase's share: the AX18 law for position / room-size / large-jump switches set and gated (AX22 switch-point
gate, position-fade gate), the `MAKROOF_TEST_HARD_SWITCH` negative control, and `clicks.py` in the `automation` job
with 0 events (map-10 §1).

## Assumptions in force

All of the umbrella's ([phase-10](phase-10.md)); those bearing on this sub-phase:

- **AQ4**: rebuilds at most once per 20 ms, coalesced; 30 ms crossfade; tail cached when only
  positions change; synchronous rebuild in non-realtime mode. Since a crossfade runs uninterrupted, the
  effective update interval is max(20 ms cap, 30 ms crossfade, rebuild time): at most one new IR per
  30 ms while rebuilds stay under 30 ms, one per rebuild time otherwise (reference: Vorländer Table 15.1).
  (phase-10 assumption AQ4, shared)
- **AX18**: equal-gain for position and room-size updates (placeholder until Phase 10, AX18);
  **equal-power** for large jumps (e.g. the corner-to-corner step scenarios) and output-mode toggles,
  where the IRs are unrelated. This phase sets the law. (phase-10 assumption AX18, shared)
- **AX22**: Phase 04's realised-k switch. t_mix,e is continuous in position, but the fallback to
  ISM-only up to the image-count cap is a single jump point in source position. Across it the IR segment
  between t_mix,e and t_cap,e is ISM in one IR and noise in the other, so AX18's equal-gain premise
  (correlated consecutive IRs) does not hold there, and the 30 ms position crossfade dips in that segment: 3 dB at mid-fade for any power ratio of the two
  uncorrelated segments; the largest dip relative to the power-linear interpolation of the two segments
  grows with their power ratio, ≈ 4.4 dB at 10:1, at g ≈ 0.24 of the fade (Vorländer Eq. 4.14). The total output dip is gated in this
  phase (acceptance criteria) (decider report 8, accepted by Maisara, 2026-11-05). (phase-10 assumption AX22)
- **AX1**: no Doppler. Movement is a sequence of crossfaded static IRs. Fast moves sound slightly
  smeared rather than pitch-shifted. That's intended, and the PR must describe it. (phase-10 assumption AX1, shared)

## Scope

5. **Negative control:** a build flag `MAKROOF_TEST_HARD_SWITCH` (test builds only) replaces the crossfade
   with an instantaneous IR switch. The click detector **must** flag that build. This proves the detector
   catches the problem this phase solves. (phase-10 scope 5)
7. CI job `automation` (set up in [10-2](phase-10-2.md)) … and
   runs `clicks.py`. (phase-10 scope 7, clause 2; clause 1 in 10-2)

## Out of scope

The umbrella's out-of-scope list ([phase-10](phase-10.md)); phase-10 scope 2 (in [10-1](phase-10-1.md)); scope 1,
3, 4, 6, 7 clause 1 and 8 (in [10-2](phase-10-2.md)).

## Acceptance criteria — automated

- [ ] All 20 scenarios × 2 modes × 2 timing modes: **0 click events** (Phase 02 detector, default threshold). (phase-10 AC1)
- [ ] Negative control (`MAKROOF_TEST_HARD_SWITCH`) is flagged in ≥ 18 of 20 scenarios. (Scenarios with
      no effective IR change may legitimately pass.) (phase-10 AC2)
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
      2026-11-05). (phase-10 AC6)
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
      2026-11-08, decider round 2 §4, advocate round 2). (phase-10 AC7)

## Listening / manual checklist (Maisara)

In Logic and one VST3 host, on a sustained pad *and* on drums, both output modes: (phase-10 listening preamble, shared)
- [ ] Automate the L and R emitters from 1 m to 15 m away and back over 8 bars: smooth change in distance,
      no clicks, zipper noise or level pumping. (phase-10 L1)
- [ ] Jump the listener between two corners every beat: the room snaps cleanly, with no clicks. (phase-10 L2)
- [ ] Sweep the room size over 4 bars: smooth. (phase-10 L3)
- [ ] Fast moves sound slightly "washy" but not pitch-wobbly. That's the intended no-Doppler design.
      Say if you'd prefer audible Doppler; that's a product decision. (phase-10 L4)

## Contractor review focus

- whether the negative control really exercises the same code path. (phase-10 CR4)

## Risks

- The click detector's blind spots for very low-frequency artifacts (thumps below 2 kHz). Add one scenario
  with a 40 Hz tone and a low-band detector variant if cheap. (phase-10 R2)

## Notes from the split

- Order 10-1 → 10-2 → 10-3: "(A) follows the data dependencies (AQ10: AC8 rebuild hits the tail cache; AC7 needs
  the realtime-sim intervals)" (convening round, 10-c1 (A), `docs/review/phase-split/1-decider-convening.md`).
  AC7's "measured update interval" is measured on the realtime-sim intervals that 10-2 produces.
- Scope 7 is "split at S7's existing clause, verbatim" (convening round, 10-c2 (a)): the job and its renders are in
  [10-2](phase-10-2.md); this sub-phase adds `clicks.py` to it.
- AX1's "the PR must describe it" goes in 10-3's PR, the sub-phase that sets the movement crossfade (map-10 §3).

## Definition of done

- All automated criteria green (phase-10 DoD1, for the criteria this sub-phase owns: AC1, AC2, AC6, AC7).
- Status row 10-3 `done` (phase-10 DoD3; the umbrella row 10 is `done` when 10-1…10-3 are).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder
  into `phase-10-3b.md`.
