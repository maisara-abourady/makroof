# 42 — Decider: review file 39's blocker 1 and majors 1–2 (file 40 Q-A, Q-B, Q-C), answered for Maisara

phase-05h (session 2). Verbatim decider output (the orchestrator saved it). Orchestrator note: the decider finished before the 2^23 result reached file 40; the result (s 0.4 and 0.5, both emitters: every band inside τ on its own, 3·SE 0.22–0.23 dB ≤ τ at 4–8 kHz, 213 s per s value on the Linux box) is Q-A's outcome 1, so no seat is convened; the decider's addendum on it, if any, is appended below.

# Decider — file 39 blocker 1, majors 1–2 (Q-A, Q-B, Q-C), phase-05h session 2

Corpus revision c1b171fe (no acoustic fact is load-bearing in these three: they are readings of a test's statistics against recorded plan rows). The 2^23 result was **not** in file 40 when I finished (file ends at L111), so Q-A is answered conditionally.

**PRD digest.** For whom: producers who design a room and expect it to sound like a real one. Outcome: the render matches measured IRs and passes listening (NFR-1, "Pass thresholds come from the Expert"); NFR-6/AX5 bit-identical offline; NFR-8 "no environment-specific code paths". Bounds here: τ = 0.25 dB (AX42, hers, P05B2-M-02); the 1 % bias rule (AX46, hers, P05B2-M-04); AX37 (5.4) "to D-T1's tolerance (AX42), in PR CI on three OSes" (hers, P05B2-M-01); D-H1 (v)(d) no cut/seam; D-H2 (d) and D-H3 (a) decided for her. Verification culture (CLAUDE.md, D-H3 (a)): tolerances follow from the requirement and the statistics; nothing loosened or regenerated to pass; a red-by-design check is a defect, not a result.

## Procedure

All three are **readings of recorded decisions / plan rows** → `FOR MAISARA` (README: "the scope or the reading of one of her earlier answers … and an amendment of one when the PRD calls for it"). **No seat convened now**: each answer is additive (a line printed, an N raised to the plan's own rule, a formula read as its sibling clause already reads it); nothing is widened, no τ/1 %/N/case changes, no audio-thread or user-control touch; the seats whose mandates D-H3 (a) heard (1, 2, 5, 7, 9) gave conditions there (catch printed, restated per golden round, a test edit) that these forms meet. **One conditional CONVENE** (Q-A outcome 2, below). **NEEDS MAISARA: none** (PRD not silent: NFR-1/NFR-8 plus the AX numbers settle direction; no PRD change; no veto overridden).

## FOR MAISARA P05H-QA — AX37 (5.4): form and N of the open_field finite-floor check

**Question.** How is "compared … to D-T1's tolerance (AX42)" asserted where the finite-N estimator's SE is not small against τ?

**Answer.** "AX37 (5.4)'s check is the validation-N form only: `render_cli --diffuse-histories 2^23` (validation-only option, 0 in every product path), both s values, asserting per band (i) the N rule 3·SE_b ≤ τ wherever the integral is non-zero (else the check cannot fail at τ and is not a check) and (ii) |10 log10(E_target,b / integral_b)| ≤ τ, τ alone; the per-band deviation, SE and z are printed. The shipping-N render is a labelled smoke test of the form (finite, ≥ 0, zero where the integral is zero, |dev| ≤ τ + 3·SE as a gross-error detector), never AX37 (5.4)'s check and never quoted. A band outside τ at 3·SE ≤ τ is a finding: reported with its numbers for the Expert and the board, never a loosened bound, an excluded band or an xfail (NFR-8, NFR-1)."

**Rests on.** AX37 (5.4) (its own words name τ); AX42; AX43's N rule (z_FW·SE ≤ τ − ℓ_ref: the plan sizes N so the stated tolerance is the operative one); NFR-1; NFR-8; CLAUDE.md verification culture.

**Reasoning.** (1) The row names τ; a bound of τ + 3·SE at SE 0.22 dB is 0.90–0.94 dB (file 39's measurement at 2^20, 4–8 kHz), 3.6× τ: not the recorded decision. (2) Everywhere else the plan makes a tolerance operative by sizing N (AX43), not by adding SE to it; SE ∝ 1/√N, so 2^23 gives ≈ 0.08 dB at 4–8 kHz, 3·SE ≈ 0.23 ≤ τ, and ≤ 0.015 dB below 2 kHz. (3) Cost: file 39 reports "a few seconds" at 2^20; 8× over two s values is minutes, not Seat 5's agreement-suite budget (≤ 10 min per OS, AX43), the only CI budget on file; the orchestrator records the measured wall time. (4) Outcome 1 (2^23 inside τ at every band): the check passes at τ and the 2^20 figures (+0.29/+0.37 dB, z ≤ 1.7) are recorded as noise. (5) Outcome 2 (4–8 kHz stays above τ at 3·SE ≤ τ): the check is red, stays red, and the clause goes to the board — **CONVENE Seat 2** (validation, claims of physical accuracy: which of the two single-scatter implementations is in error, or whether the models differ), **Seat 9** (the floor integral as a reference and its provenance), **Seat 1** (keep/cut: open_field's tail sits −85 dB re the direct peak, AX44 measurement), **Seat 5** (a red PR gate; nightly vs PR); brief: the per-band table at 2^20 and 2^23, `ground_scatter.window_target`'s assumptions (Hann, Eyring referral, 10 ms bins, finite floor), the estimator's AX37 (5.1) transport; rate "keep red and fix the defect found" vs "report at 4–8 kHz, check below" vs "nightly". The branch is not PR-ready on criterion 9 until that round lands (D-H3 (a)'s precedent: "never made green by an edit"). I state no physics: whether higher-order floor energy exists here is Seat 2's and the Expert's.

- (a) 2^23 at τ — serves AX37 (5.4) as written, NFR-1 (a check that can fail at τ), NFR-8 (nothing per scene); cost minutes of python CI. **Chosen.**
- (b) 2^20 at τ + 3·SE recorded — strains AX37 (5.4) (admits +0.6 dB at 4–8 kHz) and the culture (a tolerance widened after the data).
- (c) mixed — (a) already covers every band at 2^23; (c) adds a second form for no gain.
- (d) smoke only — abandons the check; strains NFR-1.

**What would make her veto it:** reading NFR-1's "thresholds come from the Expert" as making the integral's τ-level disagreement a question that must wait for the Expert before any gate. The answer stands because τ is her accepted number (AX42, AX37 (5.4)) and the form only makes it operative; a disagreement is reported, not gated away.

`AMENDS her decision of 2026-11-10 (AX37, ledger P05B2-M-01, "Accepted by Maisara"; plan-editor: quote her ledger words verbatim)`: adds the N sentence and the smoke-test sentence to (5.4).

**Plan text (AX37 (5.4), after "in PR CI on three OSes"):** "The check runs at a validation N of 2^23 histories (`--diffuse-histories`, validation only; 0 in every product path), both s values, with the N rule 3·SE_b ≤ τ asserted per band; the shipping-N render is a labelled smoke test (finite, ≥ 0, zero where the integral is zero, |dev| ≤ τ + 3·SE as a gross-error detector), never this check. A band outside τ at 3·SE ≤ τ is reported with its numbers (the Expert, the board), never loosened or excluded (NFR-8). If the two 2^23 renders add more than 10 min to the python job on any OS, the validation-N form moves to the nightly and the smoke form stays in PR CI." §6 row: "AX37 (5.4) check at N = 2^23, τ alone; the τ + 3·SE form confined to the labelled smoke test; 2^20 record +0.37/+0.29 dB at 4–8 kHz (SE 0.22/0.23)".

**Test form (`test_tail.py`):** `OPEN_FIELD_VALIDATION_HISTORIES = 1 << 23`; `histories is not None` branch: `assert n == histories and not capHit`; for each band with `ref[b] ≥ 1e-300`: `assert 3.0 * se_db[b] <= OPEN_FIELD_TAU_DB`, `assert abs(dev_b) <= OPEN_FIELD_TAU_DB`; print `band, dev, se, z` under "AX37 (5.4) validation N". `None` branch: the existing finite/≥0/zero-pattern asserts, `abs(dev_b) <= OPEN_FIELD_TAU_DB + 3*se_db[b]`, docstring and print labelled "smoke (shipping N, capped): not AX37 (5.4)'s check"; delete the `nanmax(se) ≤ 0.5` guard.

**Debt.** Seat 5 | 2 × 2^23 solves per OS in PR CI | one line (→ nightly) | this run's python-job wall time | repaid by the 10 min clause. Seat 2 / Expert | Phase 12 branch (a) rests on this integral | a board round | the 2^23 run; Phase 12 | repaid when outcome 1 is recorded, or outcome 2's round closes.

## FOR MAISARA P05H-QB — AX46: the BRAS pairs' class

**Question.** Are the 30 BRAS pairs "reference positions", a sixth class, or outside AX46?

**Answer.** "The BRAS pairs are AX46's sixth class, `bras`, printed and checked on its own line per band; the pooled label reads 'pooled over <n> of 6 classes'. Bands without a gated BRAS case-band print 'not evaluated (reference pending)'. No class is folded, none excluded."

**Rests on.** NFR-1 ("match impulse responses measured in real spaces": the BRAS pairs are the only class whose α comes from measured rooms); AX46's purpose (bias per case class so a class-confined bias is seen); D-H2 (d) ("every class with ≥ 1 certified case"); AX43's case set (lists the 30 pairs beside the 15 (A) cases, i.e. as their own group); CLAUDE.md (nothing hidden).

**Reasoning.** AX43 lists the BRAS pairs as a group of their own; AX46's class list predates their certification and omitted them; the code's `CLASSES["bras"] = 5` already records the export's intent. Folding them into "reference positions" would dilute a BRAS-confined bias (30 of 49 cases) and a designed-room bias alike, and remove the one line that speaks to NFR-1's "measured in real spaces". Excluding them leaves the largest certified group (90 case-bands) outside the only per-class check. A sixth line costs one loop bound and one word in the label; nothing else moves. Their record figures (mean z′ +0.59–0.60 over 30; no room |mean z′| > 3) suggest the line will read inside 1 %, but the test says, not this answer.

- sixth class — serves NFR-1 and D-H2 (d); nothing hidden. **Chosen.**
- fold into reference positions — serves D-H2 (d) formally; strains NFR-1 (visibility lost).
- outside AX46 — strains NFR-1 directly; no PRD text supports excluding the measured rooms.

**What would make her veto it:** that D-T2 fixed "five classes" by design and the BRAS pairs were meant as reference positions. The row's own case list and the export's class code say otherwise.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX46's class list: six classes; D-H2 (d)'s "pooled over <n> of 5 classes" → 6.)

**Plan text (AX46):** "(reference positions, one-end near-wall, absorbing face, small rooms, 100 m, BRAS pairs)"; every "of 5 classes" → "of 6 classes" in AX46, D-H2 (d)'s quoted text and phase-05h §5 criterion 3 ("six classes labelled, 'pooled over n of 6'"). §6 row: "AX46: BRAS pairs the sixth class (file 39 major 1)".

**Test form (`test_diffuse_agreement.cpp` L363–408):** iterate `cls` over `{0, 1, 2, 3, 5, 4}` (bras before the 100 m tracer line); `className(5) == "bras"`; for a class in `classDev` whose `st.n == 0` at band b print `agree-full AX46 class bras band b: not evaluated (reference pending)`; the pooled print "pooled over %d of 6 classes".

**Debt.** Seat 9 / 2 | the bras line exists at 500 Hz–2 kHz only until 05i certifies the outer bands (AX43 (c) order 5) | nil | 05i golden rounds | repaid as bands certify.

## FOR MAISARA P05H-QC — AX46: the class SE and the ℓ_ref budget

**Question.** Which SE does "3·SE ≤ 1 % − ℓ_ref" mean for a class, and which ℓ_ref?

**Answer.** "SE_class is the estimator-propagated standard error of the class mean, SE_class = √(mean SE_i² / n) with SE_i the per-case estimator SE in relative units; ℓ_ref is the class mean ℓ_ref: a class-band is evaluated when n ≥ 1 and 3·SE_class ≤ 1 % − mean ℓ_ref, and then CHECK |mean deviation| ≤ 1 %. The empirical SE of the per-case deviations (`Stat::se`, n ≥ 2) and the class max ℓ_ref are printed as records; a class-band whose |mean| + 3·SE_emp exceeds 1 % with the CHECK green is labelled (the heterogeneity watch) and returns the clause to the board. The 1 % limit, τ, N and the case list are unchanged."

**Rests on.** AX46's sentence ("The test N is pre-registered so that 3·SE ≤ …": N controls only the estimator's SE); D-H3 (a) / H3-F1 ("one reading of ℓ_ref throughout": a bounded systematic residual of unknown sign added linearly; per case its own ℓ_ref, pooled the mean); D-H2 (d) ("≥ 1 certified case"); NFR-1; CLAUDE.md (a check that cannot be met by the quantity it sizes is a defect).

**Reasoning.** The empirical spread contains each reference's own ℓ_ref (file 40: 0.15 % empirical vs 0.07 % propagated at nine cases), so under the present code N cannot satisfy the sentence: the sentence is false as coded, not the class. Working: each case's reference residual r_i satisfies |r_i| ≤ ℓ_ref,i, so |mean r_i| ≤ mean ℓ_ref,i — the mean is the bound the row's reading implies; the max over-bounds and, with the spread, counts ℓ_ref twice (the second reading D-H3 (a) rejected). On file 40's data: 3·0.078 % + 0.24 % = 0.47 % ≤ 1 %: every near-wall band evaluable, means −0.14…−0.22 % (4.6× inside). The propagated SE is blind to between-case heterogeneity; the per-case τ checks bound it per case, and the printed empirical SE plus the label keep the watch, as D-H3 (a) keeps the per-room watch.

- propagated SE + mean ℓ_ref — serves AX46's sentence, D-H3 (a)'s one reading, D-H2 (d)'s "≥ 1 case"; nothing widened. **Chosen.**
- empirical SE + max ℓ_ref (present) — strains AX46 (6 of 8 near-wall bands unevaluable by construction) and the culture.
- empirical SE + mean ℓ_ref — evaluable on today's data (3·0.15 ≤ 0.81 %) but ℓ_ref counted twice; a tighter set later makes it unevaluable again for no estimator reason.

**What would make her veto it:** reading AX46's 1 % as a bound on every class's observed scatter, not on the shared bias. The row's own words ("bias", "mean signed deviation") and its sizing sentence point to the mean.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX46's N sentence made explicit; D-H2 (d)'s "(3·SE ≤ 1 % − ℓ_ref)".)

**Plan text (AX46, replacing "The test N is pre-registered so that 3·SE ≤ 1 % − ℓ_ref (near-wall class: …)"):** "The test N is pre-registered so that 3·SE_class ≤ 1 % − mean ℓ_ref per class-band, SE_class = √(mean SE_i²/n) from the per-case estimator SEs (the quantity N controls), mean ℓ_ref over the class (the D-H3 (a) reading: a bounded residual added once); evaluated at n ≥ 1, then |mean deviation| ≤ 1 %. The empirical SE (n ≥ 2) and max ℓ_ref are printed as records; |mean| + 3·SE_emp > 1 % with the CHECK green is labelled and returns the clause to the board. At the 05h round the near-wall class (nine cases) is evaluable in all eight bands (3·0.078 % + 0.24 % = 0.47 %)." §6 row accordingly.

**Test form (L169–170, 266–267, 383–392):** add `classSe2[cls][b].add(seRel*seRel)` with `seRel = pow(10, ses[b]/10) − 1`, and `classLRefMean[cls][b].add(k.lRef[b])`; keep `classLRef` as the max record; `seProp = sqrt(classSe2.mean()/n)`; `budget = kBiasLimit − classLRefMean.mean()`; `evaluated = st.n ≥ 1 && budget > 0 && 3*seProp ≤ budget`; `CHECK(|st.mean()| ≤ kBiasLimit)` when evaluated; print `mean, SE_prop, SE_emp (n ≥ 2 else "n/a"), n, l_ref mean, l_ref max, status`; label `"  |mean| + 3 SE_emp > 1 % (heterogeneity watch)"` when it holds.

**Debt.** Seat 1 | the CHECK is blind to between-case heterogeneity | a test edit (empirical form) | each golden round; 05i's near-wall and small classes | repaid by the printed SE_emp and the label.

## Summary

| id | decision | state | worst-off | PRD bound | reversal |
|---|---|---|---|---|---|
| P05H-QA | AX37 (5.4) check at 2^23, τ alone, N rule asserted; shipping N a labelled smoke | for Maisara (conditional on the 2^23 result; outcome 2 → CONVENE 2, 9, 1, 5) | Seat 5 (python-job time) | AX37 (5.4), AX42, NFR-1, NFR-8 | 2^23 offset above τ; python job > 10 min |
| P05H-QB | BRAS pairs = sixth AX46 class, "of 6 classes" | for Maisara | none above 0 (additive) | NFR-1, D-H2 (d) | the bras line outside 1 % (a finding, a board round) |
| P05H-QC | SE_class propagated, budget 1 % − mean ℓ_ref, n ≥ 1; SE_emp and max printed; heterogeneity label | for Maisara | Seat 1 (later 1) | AX46, D-H3 (a), NFR-1 | a labelled class-band |

**Decided for Maisara.** QA: AX37 (5.4)'s τ made operative by N = 2^23 (AX37 (5.4), AX42, NFR-1, NFR-8); Seat 5 gives CI minutes, gets the nightly clause. QB: the measured-room pairs get their own bias line (NFR-1, D-H2 (d)); nobody gives. QC: AX46's class SE read as the estimator's, ℓ_ref once as a mean (AX46, D-H3 (a)); Seat 1 gives heterogeneity blindness in the CHECK, gets the printed SE_emp and the label. AMENDS lines as above. Confidence: QB high; QC high; QA medium until the 2^23 result and its wall time are on file. **NEEDS MAISARA: none.**

Files read: /home/user/makroof/docs/review/phase-05h/40-orchestrator-review-39-questions.md, /home/user/makroof/docs/review/phase-05h/39-review-branch-session2-r2.md, /home/user/makroof/docs/BUILD_PLAN.md (AX37, AX42, AX43, AX44, AX46), /home/user/makroof/docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md (D-H2 (d)), /home/user/makroof/docs/review/phase-05h/27-decider-decision-D-H3-r3.md (D-H3 (a)), /home/user/makroof/tools/acoustics/tests/test_tail.py (L195–241), /home/user/makroof/tests/unit/test_diffuse_agreement.cpp (L107–144, 150–419), /home/user/makroof/tools/validation/export_phase05h_references.py (L75), /home/user/makroof/docs/PRD.md (NFR-1/6/8), /home/user/makroof/docs/board/README.md.


---

# Addendum to P05H-QA — the 2^23 result is in (file 40 L113–154, both s values, both emitters)

**Outcome 1 holds.** At N = 2^23 every band is inside τ on its own: 4–8 kHz deviation −0.020 / +0.005 dB (L / R), SE 0.073–0.076 dB, 3·SE 0.220–0.229 dB ≤ τ 0.25 dB; bands 0–5 deviation |≤ 0.002| dB with 3·SE 0.022–0.100 dB; `capHit` false; s 0.4 and s 0.5 identical to the printed precision (the single-scatter ratio cancels s, as file 39 measured). The 2^20 run's +0.29 / +0.37 dB was noise (z ≤ 1.7), not an offset. **The conditional CONVENE (Seats 2, 9, 1, 5) lapses**; no finding goes to the Expert beyond the record line below. Q-A's state: **for Maisara, confidence high** (every load-bearing number measured on the head; product ids as before). The answer, AMENDS line, plan text and test form stand as delivered, with these three precisions:

1. **Record for the Expert / §0 / PR (not a finding):** "open_field at 2^23 histories: C++ diffuse E_target against the independent finite-floor integral within −0.020…+0.005 dB in every band (3·SE ≤ 0.229 dB ≤ τ); the 2^20 figures +0.29 / +0.37 dB at 4–8 kHz were noise (z ≤ 1.7)." Add it to the §6 row text given in the report.

2. **Cost and the budget clause (Seat 5's debt row, now with numbers):** 213 s per s value on the Linux dev box (≈ 27 s at 2^20), so the validation-N form costs ≈ 7 min per OS for both s values plus the smoke renders; CI runners may be slower. The 10 min clause in the plan text stands, applied in two steps so nothing is lost before anything is moved: the orchestrator records the python job's added wall time per OS from the first CI run; if it exceeds 10 min on any OS, the **s 0.5 validation-N case moves to `nightly.yml` first** (the deviation is s-independent by construction and by measurement, so s 0.4 alone carries the check), and only if s 0.4 alone still exceeds 10 min does the whole validation-N form move to the nightly with the smoke form staying in PR CI. Plan text for AX37 (5.4), replacing the last sentence I gave: "If the 2^23 renders add more than 10 min to the python job on any OS, the s 0.5 case moves to the nightly first (the ratio is s-independent: measured identical at both s), then the whole validation-N form; the smoke form stays in PR CI." Test form: keep `@pytest.mark.parametrize("s", [0.4, 0.5])`; if the clause fires, mark the (0.5, 2^23) case with the nightly marker the repo already uses for BRAS-class work rather than deleting it.

3. **The N-rule margin:** 3·SE = 0.229 dB against τ 0.25 dB at 8 kHz (R emitter) is a 9 % margin. The SE is a deterministic function of the seeded stream on one platform (AX5) and the cross-OS E_target check holds to 1e-7 relative, so the margin is expected to hold on macOS and Windows; if any OS prints 3·SE > τ at 2^23, N goes to 2^24 (the option's cap) with a §6 row, never τ + SE. That is the only reversal left on Q-A; it is a test-N change, not a tolerance change.

Summary row update: `P05H-QA | AX37 (5.4) check at 2^23, τ alone, N rule asserted per band; shipping N a labelled smoke | for Maisara | Seat 5 (python-job ≈ 7 min per OS; two-step nightly clause) | AX37 (5.4), AX42, NFR-1, NFR-8 | an OS with 3·SE > τ at 2^23 (→ 2^24); python job > 10 min (→ nightly, s 0.5 first)`. Decided-for-Maisara line unchanged except: "the 2^23 run shows every band inside τ; the 2^20 4–8 kHz figures were noise, recorded, not tuned (NFR-8)". NEEDS MAISARA: none. Q-B and Q-C unchanged.

File read for this addendum: /home/user/makroof/docs/review/phase-05h/40-orchestrator-review-39-questions.md (L112–155).
