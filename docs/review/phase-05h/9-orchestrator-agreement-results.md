# Orchestrator — first run of the AX43 / AX45 / AX46 / tracer tests on the switched C++ (2026-11-10, local Release, 4 cores)

Data, not a decision. Test: `tests/unit/test_diffuse_agreement.cpp` (`[.][benchmark][diffuse-agree-full]`, `[diffuse][tracer]`),
golden `tests/golden/phase05h_agreement_reference.json` at the K20 state of this moment (274 of 560 AX43 case-bands and 40 of
72 AX45 case-bands certified at two rungs; the rest single-rung). Pre-registered before the run: N_test = 65 536 histories on
[0, N_test), stage 2 on [N_test, 5 N_test), z_FW 4.290 / 3.81, τ 0.25 dB, the AX46 class check at the same N where
3 SE_class ≤ 1 % − ℓ_ref. Wall time 87 s (the whole suite, both stages available; one build of the pool 4).

## Results

- **AX43 per case-band:** 274 gated case-bands, max |C++ − ref| **0.046 dB**, every z_FW·SE ≤ τ − ℓ_ref, **0 stage-2 runs, 0 failures**.
- **AX45:** 40 gated case-bands, |ΔL_C++ − ΔL_ref| ≤ 0.046 dB (gate 0.25 dB at z_FW 3.81), no physics flag (> 0.68 dB).
- **AX46 per class (evaluated where 3 SE_class ≤ 1 % − ℓ_ref):** reference positions +0.03 % (SE 0.05–0.06 %, 11 cases, 8 bands);
  absorbing face −0.23 % (SE 0.125 %, 12 cases); BRAS +0.11–0.12 % (SE 0.03 %, 30 cases, 500 Hz–2 kHz). All ≤ 1 %. Classes
  small rooms and 100 m: not in the gated set (small room: single rung so far; 100 m: no `ref_hybrid`, decision D-H2 (d)).
- **Tracer (15 (A) cases, deterministic, N 4 096):** max |C++ − tracer| **0.231 dB** at 500 Hz–2 kHz (gated, ±1 dB);
  **outer bands** (125 Hz, 4 kHz, 8 kHz; layouts 4/5 at s = 1): +0.113 dB (layout 4) and −0.056 dB (layout 5), reported before
  any golden (AX37 (5.1) (ii)): no band fails, nothing goes to D-T2.
- **Reported, uncertified (U-a):** 318 case-bands printed with the label; none above τ in the AQ9 bands of the Phase 04 rooms
  (the per-band values are in the CI log).

## Finding for the decider (a reading of AX43's pooled bias check)

AX43's pooled bias check per band, |mean z| ≤ 3/√M with z = (C++ − ref)/SE_C++, **fails in the 500 Hz–2 kHz bands**:
mean z +0.439 / +0.445 / +0.464 over M = 53 case-bands against the limit 0.412 (the other five bands, M = 23: +0.16 to +0.36
against 0.626, pass). The deviations themselves are tiny (the BRAS class's mean +0.11 % = 0.005 dB; the (A) cases' +0.03 %),
far inside τ and inside the references' own rung error ℓ_ref (0.35–0.37 % for the BRAS pairs). The pooled z uses the C++ SE
only (0.03–0.05 dB per case-band → 0.004 dB pooled over 53), so it resolves the reference's residual discretisation error
(the 1.25 m rung is certified to < 1 % per halving, i.e. a remaining error of the order of ℓ_ref is expected, same sign across
a room's pairs) as a "bias" of the estimator. AX46's bias rule, which takes ℓ_ref into account (3 SE ≤ 1 % − ℓ_ref, bound 1 %),
passes on every evaluated class. The AX43 rule as written cannot pass once M is large enough that SE/√M < ℓ_ref, whatever the
estimator does. Options for the decider: (a) read AX43's z as (C++ − ref)/√(SE² + ℓ_ref²) per case-band (the reference's
certified uncertainty enters the pooled test as it enters the per-case test); (b) pool per reference class (so a room's shared
rung error does not accumulate across its 10 pairs); (c) keep the rule and record the fail as a finding. AX43 cites her
acceptance of 2026-11-10, so (a) or (b) is a FOR MAISARA reading with the interrogator's check. Until decided, the test keeps
the rule as written (the CHECK fails) and prints the per-class table.

## Finding for the decider (AX44 Seat 6 (ii): U at the default placement of two valid fixtures)

The D5 / CI-reports test (`tests/unit/test_diffuse_reports.cpp`, every valid fixture at 48 kHz, provisional W_max 3.05 M,
n\*_max 1 024) prints, per fixture, the D5 hash, n\*, N, the flags, U and the achieved SE. U is **raised at the default
placement of two valid fixtures**, both contract-limits scenes, not rooms (n\* / N / flags / SE e0, e1):
- `edge_values` (absorption alternating 0.01 / 1.0 between bands; the contract-limits fixture): n\* 64, N 0, cap hit, floor
  truncated, pilot floor, **the pilot estimate ships**, U on both emitters (SE 0.76 / 3.98 dB). The cause is the work cap at a
  scene whose near-rigid bands give a very long window; no placement change can silence it (AX44 (ii)'s remedy is a placement
  change, not the predicate).
- `open_field` (100 × 100 m floor, every other face α = 1): n\* 1 024, N 2 624, cap hit, U on both emitters (SE 2.39 / 2.12 dB
  of a total E_target that is the floor's single scattering alone; AX37 (5.4): "`open_field` gets whatever the generic model
  gives").
Every other fixture is silent (U 0), the pilot never ships, SE ≤ 0.19 dB; `medium_room` (the plugin's default scene, in the AX22
fallback) and `asymmetric_materials` carry the pilot-floor and floor-truncated flags with U silent. The test asserts Seat 6 (ii)
as written and therefore fails on these two fixtures until the board reads it: options are (a) the rule applies to rooms and
presets, and the two contract-limits fixtures are listed as known exceptions in the CI report (U correctly describes them);
(b) the fixtures' placements or materials change (edge_values is a contract-limits fixture used by the validation tests;
open_field's outcome is AX37 (5.4)'s); (c) the predicate changes (excluded by AX44 (ii)).
