# Orchestrator — D-H3: three findings of the first switched runs, for the decision loop (2026-11-10)

Follow-on round of the phase 05h session-2 loop (`/fix-plan` step 3), decided before the golden round and the atomic push
(steward round 8, G1/G5). Settled and not reopened: AX37–AX46 (her recorded decisions of 2026-11-10, "I accept the board's
answer by definition"), D-H1 and D-H2 as decided in file 8. Each item below is a reading or an amendment of one of her
recorded decisions, so the answer is a FOR MAISARA answer with PRD ids and, where a row is amended, the line
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`, checked by the interrogator (no PRD MISREAD).

## D-H3 (a) — AX43's pooled bias check against the references' own rung error (an amendment of the statistical rule)

Evidence: `9-orchestrator-agreement-results.md` §"Finding for the decider (a reading of AX43's pooled bias check)". The rule as
written (|mean z| ≤ 3/√M per band, z = (C++ − ref)/SE_C++) fails at 500 Hz–2 kHz (mean z +0.439 / +0.445 / +0.464 over
M = 53 vs 0.412) while every per-case-band check passes by a wide margin (max 0.046 dB vs τ 0.25 dB) and AX46's bias rule,
which carries ℓ_ref, passes per class (+0.03 %, −0.23 %, +0.11 %). Cause: the pooled SE over 53 case-bands (≈ 0.004 dB)
resolves the references' residual discretisation error (the BRAS pairs' +0.11 % share one room's rung error across 10 pairs
each; ℓ_ref 0.35–0.37 %), which the rule's z does not carry. Options (none changes τ, z_FW, the case list or stage 2):
- (a) z_i = (C++ − ref)_i / √(SE_i² + ℓ_ref,i²) per case-band (the reference's certified uncertainty enters the pooled test
  as it enters the per-case test): an amendment of AX43's formula;
- (b) pool per reference class (so one room's shared rung error does not accumulate across its pairs): an amendment of
  AX43's pooling;
- (c) keep the rule as written and record the failure as a finding at every CI run (the test's CHECK stays red).
The interrogator should check the arithmetic: with ℓ_ref = 0.36 % = 0.0156 dB and SE_i ≈ 0.035 dB, option (a) scales the
BRAS z by 1/√(1 + 0.2) ≈ 0.91 and the (A) z (ℓ_ref ≤ 0.33 %) by ≈ 0.93; whether that alone brings the pooled mean under 0.412
is to be computed from the per-case-band table in the CI log, not assumed.

## D-H3 (b) — U at the default placement of two valid fixtures (AX44 Seat 6 (ii) and AX44's reversal condition)

Evidence: file 9 §"Finding for the decider (AX44 Seat 6 (ii))". At the provisional W_max and n\*_max, U is raised at the default
placement of `edge_values` (n\* 64, N 0, cap hit, floor truncated, pilot floor, the pilot ships; SE 0.76 / 3.98 dB) and
`open_field` (n\* 1 024, N 2 624, cap hit; SE 2.39 / 2.12 dB of a total that is the floor's single scattering alone). Both are
contract-limits fixtures (absorption alternating 0.01 / 1.0 between bands; a 100 × 100 m floor with every other face α = 1),
not rooms or presets. AX44 Seat 6 (ii): "no default placement of a valid fixture or Phase 12 preset may raise U; if one does,
the placement is changed, not the predicate". AX44's reversal: "a default placement raises U and cannot be moved". Here a
placement change cannot silence U (the cause is the work cap at a fixture whose window is extreme, and the open field's
near-zero total), so the reversal condition is formally met. Options: (a) read Seat 6 (ii) as applying to rooms and presets,
and list the two contract-limits fixtures as known, correct U cases in the CI report (U describes them truthfully: the level
there is uncertain), with the reversal recorded as not triggered because the fixtures are not rooms (a FOR MAISARA reading of
AX44); (b) change the fixtures' materials or placement (edge_values is the contract-limits fixture the validation tests use;
open_field's outcome is AX37 (5.4)'s "whatever the generic model gives"); (c) treat the reversal as triggered and reopen NW-4C
/ U (excluded by AX44 (ii) as written unless the board decides it). Nothing here changes the predicate.

## D-H3 (c) — the AX37 (5.1) (i) denormal premise of the FTZ test

AX37 (5.1) (i): "a `[pipeline]` test builds an absorbent room, asserted to produce denormals without FTZ, with the caller's FTZ
on and off, and requires the IRs to be bit-identical". The guard and the bit-identity test exist (`test_diffuse_gate.cpp`).
The premise was probed twice: on the estimator alone (24 scenes, α 0.5–0.999, 3–100 m, s 0.3 / 1: identical hashes and
estimates with FTZ off and on) and on the whole IR path without the guard (`[.][probe-denormals-ir]`: dead_booth at α 0.98 and
0.999, edge_values, open_field, medium_room and two 100 m cubes at α 0.999, at 48 and 96 kHz; result recorded in this file's
addendum once run). If no probed scene produces a denormal that reaches the IR, the test cannot honestly "assert" the premise.
Options: (a) the test asserts what holds (bit-identical IRs with the caller's FTZ off and on, the guard in place) and records the
probe's finding, the "asserted to produce denormals" clause read as satisfied by the probe's negative result (a FOR MAISARA
reading of AX37 (5.1) (i)); (b) keep searching for a scene (which one, and how long); (c) a synthetic denormal injected into
the IR path for the test only (a formulation seam in test code; it would assert the guard, not the premise).
