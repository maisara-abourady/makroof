# 2 — Seat 4 position (D-B1 narrow, D-B3 narrow, D-B4), round 1

2026-11-13, corpus c1b171f (not re-read; arithmetic only for D-B3). Saved by the orchestrator from the seat's report.

**Code facts.** F1: `process()` runs the same 2×2 partitioned convolution in every mode (`src/sim/RealtimeEngine.cpp` L33,
L67: numEmitters == numOutputs == 2); omni copies the same taps to both outputs (`src/sim/Engine.cpp` L552–553); phase 09
stays stereo (phase-09 L47). F2: omni synthesises one unit decay per emitter at `tailSeedForOutput(seed, 0)` (Engine.cpp
L465); binaural needs two seeded ear noises per emitter (phase-08-3 scope 5), so output 1 is a second `make()` omni never
builds; the unit-decay synthesis is 95.5 % of the non-diffuse restore (AX38 4c, split timer file 7).

## D-B1 (narrow: Phase 08 callback load)
Ranking: B1-b prefer > B1-d > B1-c > B1-a (can live with).
B1-b 0 / 0 (a valid instrument for 08-4's AX38 (iv) binaural repeat); B1-d 1 / 1 (time until audible longer equally in every
mode); B1-c 1 / 1 (mode-neutral; inversion Seat 5's); B1-a 1 / 2 (08-4 repeats the records in binaural; a "p99.9" that is the
1st–2nd largest of 953–1 936 callbacks cannot tell a mode effect from runner noise; undo = one re-instrumentation in 08-4).
Narrow point: by F1 Phase 08 adds no `process()` work (same path count, IR ≤ 12 s); it raises builder work (F2 plus the HRIR
early part), the contention axis this record measures [Inferred; 08-4's W1/W2 per mode will confirm]. Condition (B1-a → 1):
08-4's binaural repeat runs both modes in the same CI run with the same instrument, prints the callback count, labelled "not
a host audio thread".

## D-B3 (narrow: per ear / channel in 08-3, 09)
Tolerance (1 + T/30)²: W-a 1 ms +0.28 dB; W-b 2.5 ms +0.70 dB; W-c 5 ms +1.34 dB; W-d 10.67 ms **+2.64 dB, not +2.88 dB**
((1.3557)² = 1.838). A sin/cos equal-power fade at ρ = 0.993 in a window centred on mid-fade gives E = 1 + ρ·(window average
of sin 2θ) ≈ +2.88 dB for W-d — the brief's figure may be that quantity. Equal-power margins over the tolerance: W-a ≈ +2.7
dB, W-b +2.29, W-c +1.63, W-d +0.24 dB [Inferred: AX18 equal-power is sin/cos; Seat 3 or 5 to confirm from code].
Ranking: W-b prefer > W-a > W-c > T-0 > W-d (can live with). Parity tolerance ±1 dB (phase-08 AC6; phase-09 LUFS ≤ 1 dB): a
fade-only gain error on one output passes whenever below the tolerance.
W-b 0 / 0; W-a 0 / 1 (tight, valid for any signal; debt Seat 5's determinism margins); W-c 1 / 1 (admits 1.34 dB fade-only
error in one ear, above 1 dB parity); T-0 1 / 2 (not proven; false per-ear failures in 08-3, 09); W-d 2 / 2 (admits 2.64 dB in
one ear; separates the laws by 0.24 dB).
Conditions: **(P) for every option** — asserted per output channel, as the maximum over channels, never on the L+R sum or
mean (a sum hides opposite-sign ear errors); in 08-3 and 09 extended to each ear and speaker feed; mode switches
(omni↔binaural↔stereoSpeakers, AX18 equal-power) recorded per channel, not asserted (phase-09 L36–37). W-d → 1/1: replace by
W-b, or keep W-d and add a per-channel endpoint-gain sum check (a + b = 1 to ε). T-0: needs Seat 3's or the interrogator's
per-window proof. Evidence: ILD JND vs a 1.34 dB fade-only error [Hyp], Seat 1.

## D-B4 (C4 and the mode switch)
**Shared debt (load-bearing).** AX49: "an output-mode switch reuses the cached unit decays and never waits for a synthesis"
(Seat 4 M). By F2 a project loaded in omni has no output-1 decays, so at 08-3 either (a) every load synthesises output-1
decays in every mode (≈ 2× the unit-decay share of the trigger figure [Inferred]) or (b) M breaks. 08-4's heaviest-mode gate
(scope 10) and binaural (iv) records will read the 5 s trigger at ≈ 2× today's 7.7–10.2 s [Inferred]. Whatever is chosen
must scale with the number of outputs.
Ranking: C2 = C1 prefer > C6 > C3 > C4 > C5 > C7 > C8 (can live with).
C1 0 / 0 (bit-identical; constructor spectra depend on the decay, not the seed, so shared across ears and the gain grows in
binaural [Inferred]; Seat 2 or 5 to confirm); C2 0 / 0 (per-ear syntheses independent, parallelise alike); C6 0 / 1 (a mode
switch's background rebuild can pause behind another instance's load); C3 1 / 1 (07c-1 condition R: the interim carries each
mode's target coherence); C4 1 / 2 (07c-1 A3 in unit-decay form; binaural needs both output indices → ≈ 2 × 147 MB
[Inferred]; memory Seat 5's); C5 1 / 2 (must keep the two ear seeds' noises uncorrelated per band or 08-3's coherence
criterion ±0.1 (AC5) fails; golden round); C7 1 / 2 (08-4 measures the binaural load before any remedy exists); C8 1 / 2
(binaural ships without its trigger read until Phase 13).
Conditions: C4 → 1/1 stores mode-independent unit decays per (emitter, outputIndex) the modes need, never an assembled IR;
key includes `tailSeed` and fs, excludes `outputMode`, `hrtfId`. C5 → 1/1 per-band cross-correlation between seeds verified
before 08-3 relies on it. C7 → 1/1 07d lands before 08-4 freezes its goldens. C8 → 1/1 08-4 re-reads the 5 s trigger in the
heaviest mode and returns it to the board if it fires.

Hand-offs: Seat 5 (C4 vs AX38 (ii) 128 MB; C6; whether output-1 decays are built at load); Seat 3 (equal-power law form;
per-ear decay cache vs M); Seat 1 (1.34 dB fade-only interaural step audible?); interrogator (W-d 2.64 vs 2.88 dB); decider
(register output-count scaling as D-B4 debt). Premortem: D-B4 fixed on omni figures; at 08-3 meeting M doubles per-load
synthesis; 08-4's heaviest-mode gate reads ≈ 18 s at 8 Windows instances [Inferred], above AX38 (iv)'s 10 s line.
Files: `src/sim/Engine.cpp` (L465, L514–553), `src/sim/RealtimeEngine.cpp` (L33, L67), `src/sim/tail/NoiseTail.h` (L45–48),
`docs/phases/phase-08-3.md` (scope 5), `docs/phases/phase-09.md` (L36–47), `docs/review/phase-07c-1/3-seat4.md`.
