# 15 — Seat 4 position on the FM-D1-S3 (i) lines (Maisara chose (i), 2026-11-13)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the seat's report. Convened per phase-07c-1b Raise item 1 / interrogator
file 40 observation 98 (the 08-3 / 09 lines fall in Seat 4's row).

**Reading.** How the (i) lines read in 08-3 and 09 so the provisional tail is checked on the exact tail's noise stream. Cues: level
and tone parity (a stream mismatch at the AQ4 equal-gain handover dips up to 3 dB mid-fade, AX18); model violated (the draft assumed
independent outputs; the 2×2 mix makes them dependent); measurement doubt (an empty window passes without testing); write the chain.
**Chain (code, phase files):** n1 at `tailSeedForOutput(seed,0)`, n2 at `(seed,1)`, both on the emitter's PCG stream (NoiseTail.cpp
`seed ^ (k·0x9E3779B9)`); per-band envelopes; per-band mix L = a·n1 + b·n2, R = a·n1 − b·n2, a² + b² = 1; in 08-3 only, a per-ear
diffuse-field HRTF magnitude (and any DF-EQ) filter; the shipped IR.

**Ranking.** (i) corrected as below: prefer. (i) as drafted (file 39): cannot live with — at high frequencies (γ_b ≈ 0) its "other
output's seed" control on L is green by construction; a control asserted red that is green fails CI and invites silent weakening.

**Proposed text (08-3; 09 the same with "feed (L, R)").**
- Compared: per emitter, output and band, the provisional IR against the exact IR, both as shipped (after the mix and the per-ear
  filter), between two renders of one scene and seed.
- Expected: prefix samples equal up to per-stream band gains g₁, g₂ → E(diff)/E(exact) ≈ a²(g₁−1)² + b²(g₂−1)² ≤ max(g−1)² (a² + b² =
  1): the AX47 (b) bound carries over per output and band.
- Bound: 10·log10(E/E) ≤ 20·log10(10^(B/20) − 1), B the AX47 bound in force (−18.27 dB at 1 dB; −24.55 dB after a 0.5 dB reversal).
- Window: [t_mix,e, L_f − h), L_f the AX49 global fade start (the same in every mode); h the backward reach in samples, at each fs, of
  every filter between the noise and the shipped IR — the generator's band filters; any band split used by the coherence mix; in 08-3
  the per-ear DF-HRTF magnitude and DF-EQ filters (half-length if linear-phase with latency compensated, 0 if causal); plus the
  analysis filterbank. Window length printed per case and band; an empty window, or L_p ≥ L (no provisional), prints "not evaluated"
  and never counts as a pass; ≥ 1 evaluated case per band, output and fs on the A4 set (non-vacuity, not a quota).
- **Negative control N1 (different base seed, red by construction):** provisional built with tailSeed′ = tailSeed + 1, asserting
  neither output seed of tailSeed′ equals either output seed of tailSeed; both streams independent of the exact tail's; expected
  10·log10(2) = +3.01 dB per emitter, output and band whatever γ_b (incoherent energies add; Vorländer §4.3 Eq. 4.15, file 40 row 87);
  asserted red per output and band.
- **Negative control N2 (seeds swapped — the likeliest per-output bug):** per output the measured value printed beside its closed
  form, L 10·log10(2(1 − √(1−γ_b²))), R 10·log10(2(1 + √(1−γ_b²))); asserted red on the two-output aggregate per band, (E_L,diff +
  E_R,diff)/(E_L + E_R), where the γ terms cancel: expected +3.01 dB (± a small ear imbalance after DF-EQ); L alone not asserted where
  |γ_b| ≤ 0.122.
- Rejected as a control: comparison against the other output's signal (not red where γ_b ≥ 0.9926 — low bands on a head).
- **Direct assertion:** the mix coefficients (a_b, b_b) and the per-ear filter coefficients bit-identical between the provisional and
  exact builder paths (a coherence error of 0.1 at γ ≈ 0 — a = b ≈ 0.707 vs γ = 0.1, a′ = 0.742, b′ = 0.671 — gives a prefix
  difference ≈ −26 dB, invisible to the prefix check).

**Tension.** Corrected (i): now 0 (two small tests on a path the phases already build), later 1 (commits 08-3 and 09 to a few tests;
undo = drop lines; evidence 08-3 / 09 CI on three OSes, and 07c-2's ABX if B becomes 0.5 dB). Draft (i): now 1, later 2 (the control
fails by construction at high frequencies in 08-3, and in 09 as spacing lowers coherence; an unplanned rewrite in 08-3 and silent
weakening).

**Evidence.** Mix, seeds, per-ear filter from the code and phase files (Engine.cpp / NoiseTail.cpp; 08-3 scope 5, l. 25–31; 09 scope
3); closed forms own arithmetic, agreeing with file 40 row 88; +3.01 dB Vorländer §4.3 Eq. 4.15; convexity own derivation [Inferred];
ORTF diffuse-field coherence at low frequencies ≈ 0.66 (two coincident cardioids 110° apart) own first-order arithmetic [Hyp] until
phase 09 scope 3 documents the formula (if it holds, N2's L term is red at low frequencies in 09 but not at high) — researcher to
verify.

**Conditions (draft → corrected):** N1 asserted per output and band plus N2 asserted on the aggregate (later 2 → 1); the per-mode h and
the non-vacuity rule (else 63 Hz on small rooms can pass with an empty window); B written, not a fixed −18.27 dB.
**Hand-offs:** 07c-2's window for full-length interims (correction 91) — Seats 3, 5; CI / test cost in 08-3, 09 — Seat 5;
audibility of a coherence-only mismatch — Seat 1.
**Premortem:** the draft ships; 08-3 CI fails on the left-ear swap control at ≥ 1 kHz; the control is loosened or removed; a later
ear-ordering bug reaches users as a mid-fade dip of up to 3 dB at every restore; Maisara hears it first on headphones.
