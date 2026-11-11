# 45 — Interrogator: decider file 44, round 2 — SURVIVES WITH CORRECTIONS (wording A, B, C; applied by the plan-editor)

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). Correction B's quadrature-grid halving is recorded in file 40 (the integral's ℓ_ref ≤ 0.11 %, 0.009 dB over the ladder).

**Interrogator — round 2 on `/home/user/makroof/docs/review/phase-05h/44-decider-review-39-readings-r2.md`** (corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d; no acoustic claim new this round).

## Outcome: **SURVIVES WITH CORRECTIONS** (QA, QB, QC all stand; three wording fixes, none changes an answer)

## File 43 fixes 1–6 and questions 1–3

| item | verdict | evidence |
|---|---|---|
| Fix 1 (nightly clause → board return, Seat 5; marker form dropped) | applied, faithful | file 44 L11, L23 last sentence |
| Fix 2 (AMENDS names no moved phrase) | applied | L25; but see correction A |
| Fix 3 ("plan's N-rule form with AX46's constant 3, no ℓ_ref"; "8–9 %") | applied | L23 |
| Fix 4 (BRAS in the enumeration; "as quoted in AX46") | applied | L31 |
| Fix 5 ("0.76–0.84 %"; c4 record; watch label) | applied | L19, L31, L33 |
| Fix 6 (seat cells struck) | applied | L44 |
| Q1 | answered, checkable | no python-job budget on file; board return (README L120–123 route) |
| Q2 | CORRECT | file 6 L649–670: table filled 2026-11-11, four 0.1 m cases + `W1_e0`, max \|rel. diff\| 3.41e-6 (L661) |
| Q3 | substance right, **quantity misnamed** | see correction B |

## Numbers (re-checked)

- AX37 record: −0.020…+0.005 dB, 3·SE ≤ 0.229, 213 s vs ≈ 27 s, z ≤ 1.7, "1/12 of τ" (0.020/0.25 = 1/12.5): CORRECT (file 40 L113–154). Cap 2^24: CORRECT (file 39 blocker 1). AX42 reversal "ℓ_ref > τ/2": CORRECT (BUILD_PLAN L143).
- AX46 record: near-wall SE_prop 0.072–0.078 %, means −0.136…−0.217 %, 8/8 evaluated; BRAS +0.110…+0.117 %, SE_prop 0.028–0.029 %, 30 cases; "pooled over 4 of 6"; no heterogeneity label (worst 0.217 + 3·0.160 = 0.70 %): CORRECT (file 31 L488–511).
- Test-form statement vs working tree: `test_tail.py` L204, L226, L237, L247, L249–250 and `test_diffuse_agreement.cpp` L378–436 match line for line: faithful.
- phase-05h §5 criterion 9 (L325 "PR CI, three OSes"): unchanged and consistent with the withdrawn move.

## Corrections (exact wording)

**A. AX37 AMENDS line (README L99–100 format requires her words).** Replace L25 with:
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX37 (5.4), ledger P05B2-M-01: the validation-N sentence, the smoke-test sentence and the 2^23 record added; no other clause changed.)

**B. AX37 (5.4) text, the residual sentence — INCONSISTENT with the code.** `tools/acoustics/ground_scatter.py` L58–97: `window_target` is a continuous quadrature over the floor (n_r = 4000 log-spaced shells, L74–76; n_phi = 720 azimuths, L77), each element weighted by the Hann window at its exact arrival time (L86, L93) and Eyring-referred (L96–97); "10 ms" is only the normalisation `norm = 0.010 / (0.5 (b − a))` (L95). There is no 10 ms bin. Replace "The integral's 10 ms-bin discretisation residual is bounded only by that measurement (|dev| ≤ 0.020 dB); a 5 ms-bin halving is recorded as its ℓ_ref in 05h or 05i." with:
"The integral's quadrature residual (its (n_r, n_phi) = (4000, 720) floor grid; the arrival times are exact, the 10 ms is a normalisation) is bounded only by that measurement (|dev| ≤ 0.020 dB) until the grid halving (n_r 8000, n_phi 1440) is recorded as the integral's ℓ_ref (AX36's ladder form) in 05h or 05i: a record, not a gate; it reopens the clause only by AX42's reversal (ℓ_ref > τ/2)."
Make the same substitution in file 44 Q3 and in the §6 row if it names the residual. When the orchestrator's halving lands in file 40, quote its value in the record sentence.

**C. phase-05h §5 criterion 3 (L298).** The parenthetical "at the pre-registered test N (3·SE ≤ 1 % − ℓ_ref)" would contradict the amended AX46 sentence; change it to "(3·SE_class ≤ 1 % − mean ℓ_ref, SE_class estimator-propagated, AX46)". The decider's criterion-3 text (L31) names only the enumeration and the label; add this.

Nothing else moves: the convening position (readings; Seat 5 convened only on the > 10 min return), the PRD readings (NFR-1 L105, NFR-8 L112), the two AX46 AMENDS lines and both §6 rows are faithful to the rows they amend (BUILD_PLAN L138, L147) and to D-H2 (d) (file 19 L235) and D-H3 (a) (file 27 L61, L76).

No questions for a further round.
