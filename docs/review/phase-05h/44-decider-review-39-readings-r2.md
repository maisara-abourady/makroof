# 44 — Decider: round 2 on file 42 (answers interrogator file 43): all corrections accepted, the nightly-move clause withdrawn; the final plan texts and test forms

phase-05h (session 2). Verbatim decider output (the orchestrator saved it).

# Decider round 2 on file 42 (interrogator file 43) — QA, QB, QC: all corrections accepted; nothing argued

**State.** QA **revised** (nightly-move clause withdrawn; check form stands). QB, QC **stand with corrections**. No seat convened; NEEDS MAISARA none.

## Answers to the interrogator's questions

**Q1.** No seat report and no recorded decision states a wall-time budget for the python job or pre-authorises a move out of "PR CI on three OSes". The ≤ 10 min figure is AX43's agreement-suite budget in the Release build job (Seat 5 heard in file 19); I borrowed it. Accepted: the > 10 min case is a **board return with Seat 5 convened**, not a move; the two-step marker form is dropped (unregistered marker; `nightly.yml` is Linux-only and does not run `test_tail.py`). The 10 min stays only as the reporting trigger for that return.

**Q2.** The c4 cross-check pass is recorded in `docs/review/phase-05h/6-orchestrator-K20-certified-listing.md` L647–665 (table filled from the golden at HEAD, 2026-11-11): |rel. diff| ≤ 3.4e-6 on the four 0.1 m cases and W1_e0. D-H2 (d)'s condition for the near-wall line is met and is cited in the AX46 text below.

**Q3.** No. The integral's 10 ms-bin (Hann, Eyring-referral) discretisation residual has no bound on file other than the 2^23 measurement: |dev| ≤ 0.020 dB in every band, which contains the residual plus Monte Carlo noise, 1/12 of τ. The proper independent bound is the plan's own ladder form (AX36): rerun `window_target` at 5 ms bins and record the change as the integral's ℓ_ref. That is a python-only record the orchestrator may run now; if it is not run, it is a 05i follow-up. It is a record, not a gate (no new tolerance); it would reopen the clause only by AX42's reversal form (a change > τ/2).

## Corrections accepted (file 43 items 1–6)

(1) nightly clause struck, board-return sentence adopted, item 3 kept; (2) the AMENDS line does not name "in PR CI on three OSes" (no move kept); (3) "AX43's N rule" → "the plan's N-rule form with AX46's constant 3, no ℓ_ref term (the integral's residual bounded by |dev| ≤ 0.020 dB at 2^23)", "9 %" → "8–9 %"; (4) BRAS pairs added to the enumeration of classes evaluated now; "as quoted in AX46"; (5) "0.81 %" → "0.76–0.84 %"; the c4 record cited; the watch labelled "n ≥ 2, 1 d.o.f. at n = 2"; (6) summary seat cells struck: "decider's own debt, no seat rated".

## Final plan texts (verbatim for the plan-editor)

**AX37 (5.4), appended after "in PR CI on three OSes":** "The check runs at a validation N of 2^23 histories (`render_cli --diffuse-histories`, validation only; 0 in every product path), both s values, both emitters, asserting per band the plan's N-rule form with AX46's constant 3 and no ℓ_ref term, 3·SE_b ≤ τ, wherever the integral is non-zero, then |10 log10(E_target,b / integral_b)| ≤ τ, τ alone; deviation, SE and z printed per band. The shipping-N render is a labelled smoke test of the form (finite, ≥ 0, zero where the integral is zero, |dev| ≤ τ + 3·SE as a gross-error detector), never this check and never quoted. Record (2026-11-11, Linux, Release, 213 s per s value against ≈ 27 s at 2^20): every band inside τ, −0.020…+0.005 dB, 3·SE ≤ 0.229 dB (8–9 % margin at 4–8 kHz); the 2^20 run's +0.29 / +0.37 dB at 4–8 kHz was noise (z ≤ 1.7), recorded, not tuned (NFR-8). The integral's 10 ms-bin discretisation residual is bounded only by that measurement (|dev| ≤ 0.020 dB); a 5 ms-bin halving is recorded as its ℓ_ref in 05h or 05i. If an OS prints 3·SE > τ at 2^23, N goes to 2^24 (the option's cap) with a §6 row, never τ + SE. If the two 2^23 renders add more than 10 min to the python job on any OS, the clause returns to the board (Seat 5 convened; the nightly is Linux-only and does not run `test_tail.py`), never a loosened τ."

`AMENDS her decision of 2026-11-10 (AX37, ledger P05B2-M-01; plan-editor: quote her ledger words verbatim)` (AX37 (5.4): the validation-N sentence, the smoke-test sentence and the 2^23 record added; no other clause changed.)

§6 row: "AX37 (5.4) check at N = 2^23, τ alone, N rule 3·SE ≤ τ per band; τ + 3·SE confined to the labelled shipping-N smoke test; 2^23 record −0.020…+0.005 dB, 3·SE ≤ 0.229 dB; the 2^20 +0.37 / +0.29 dB at 4–8 kHz noise. Review file 39 blocker 1; decider files 42/44; interrogator file 43."

**AX46, class list:** "(reference positions, one-end near-wall, absorbing face, small rooms, 100 m, BRAS pairs)".

**AX46, enumeration of classes evaluated now (and phase-05h §5 criterion 3):** "reference positions, absorbing face, small rooms, one-end near-wall (the c4 cross-check recorded passing: `docs/review/phase-05h/6-orchestrator-K20-certified-listing.md`, 2026-11-11, |rel. diff| ≤ 3.4e-6), and BRAS pairs (500 Hz–2 kHz, outer bands as 05i certifies)"; every "of 5 classes" → "of 6 classes" (D-H2 (d)'s text as quoted in AX46; phase-05h §5 criterion 3: "six classes labelled; 'pooled over n of 6'").

**AX46, N sentence (replacing "The test N is pre-registered so that 3·SE ≤ 1 % − ℓ_ref (near-wall class: … CI time only)"):** "The test N is pre-registered so that 3·SE_class ≤ 1 % − mean ℓ_ref per class-band, SE_class = √(mean SE_i² / n) from the per-case estimator SEs in relative units (the quantity N controls), mean ℓ_ref over the class (the D-H3 (a) reading: a bounded residual added once); evaluated at n ≥ 1, then |mean deviation| ≤ 1 %. The empirical SE (n ≥ 2; 1 d.o.f. at n = 2) and the class max ℓ_ref are printed as records; a class-band with |mean| + 3·SE_emp > 1 % and the CHECK green is labelled (heterogeneity watch) and returns the clause to the board. Record (05h round): near-wall evaluated in all eight bands (SE_prop 0.072–0.078 %, means −0.14…−0.22 %); BRAS +0.110…+0.117 % at 500 Hz–2 kHz (SE_prop 0.028–0.029 %); 'pooled over 4 of 6 classes'."

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX46's class list: six classes, BRAS pairs the sixth; D-H2 (d)'s "of 5 classes" as quoted in AX46 → 6.)
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX46's N sentence made explicit: estimator-propagated SE_class, mean ℓ_ref, n ≥ 1; D-H2 (d)'s "(3·SE ≤ 1 % − ℓ_ref)" as quoted in AX46.)

§6 rows: "AX46: BRAS pairs the sixth class, 'of 6 classes' (file 39 major 1; decider 42/44, interrogator 43)." "AX46: class SE = estimator-propagated, budget 1 % − mean ℓ_ref, n ≥ 1; SE_emp and max ℓ_ref printed; heterogeneity watch (file 39 major 2; decider 42/44, interrogator 43)."

## Final test-form statement

`test_tail.py`: `OPEN_FIELD_VALIDATION_HISTORIES = 1 << 23`; validation branch asserts `n == histories`, `not capHit`, per non-zero band `3*se_db[b] <= 0.25` then `abs(dev) <= 0.25`, prints dev/SE/z; shipping branch keeps finite/≥ 0/zero-pattern and `abs(dev) <= 0.25 + 3*se_db[b]` labelled "smoke (shipping N, capped): not AX37 (5.4)'s check"; the `nanmax(se) ≤ 0.5` guard deleted. `test_diffuse_agreement.cpp`: loop `cls ∈ {0,1,2,3,5,4}`, `className(5) == "bras"`, per-band "not evaluated (reference pending)" where a present class has `n == 0`, "pooled over %d of 6 classes"; per class-band `seProp = sqrt(mean((10^(SE_dB/10) − 1)²)/n)`, `budget = 0.01 − mean l_ref`, `evaluated = n ≥ 1 && budget > 0 && 3·seProp ≤ budget`, `CHECK(|mean| ≤ 0.01)` when evaluated; print mean, SE_prop, SE_emp (n ≥ 2, else "n/a"), n, l_ref mean, l_ref max, status; label "|mean| + 3 SE_emp > 1 % (heterogeneity watch)" when it holds. The orchestrator's local runs of these forms are green as reported (near-wall 8/8 bands; BRAS line printed; open_field at τ).

**Summary.** QA | 2^23 at τ, N rule, labelled smoke; > 10 min → board return | revised, for Maisara | decider's own debt, no seat rated | AX37 (5.4), AX42, NFR-1, NFR-8 | an OS with 3·SE > τ (→ 2^24); python job > 10 min (→ board, Seat 5). QB | sixth class | stands | no seat rated | NFR-1, D-H2 (d) | bras line outside 1 %. QC | SE_prop, mean ℓ_ref, n ≥ 1, watch | stands | no seat rated | AX46, D-H3 (a), NFR-1 | a labelled class-band. Confidence: all three high.
