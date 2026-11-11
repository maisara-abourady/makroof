# 71 — Interrogator: DECISION RG-1 round 4 (file 70) — SURVIVES WITH CORRECTIONS (two wording fixes: Seat 6's cell marked as read; rule (d)'s remedy clause split for timing and work-pin entries)

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). The fixes go into the plan-editor brief and the ledger row.

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (not load-bearing).

**Outcome: SURVIVES WITH CORRECTIONS (two wording fixes, no cell or winner changes).**

**Cells against the seats' words.**
- Seat 5 0 / 1 on T2: own. File 57 r3: "Alternative if the decider wants it armed now: bound 1.15 × … 2 172 ms: 0 of 4 rows over … Then 0 / 1 holds." Faithful. Note Seat 5 wrote "mean of in-window medians (1 889)"; 1 889 is the mean of all four rows (the in-window mean is 1 817); the decider's provenance ("the mean of the four measured macOS medians") corrects it rightly — keep that wording in the constant's comment.
- Seat 6 0 / 1 on T2: faithful in number, but not "own". File 61 r2 priced "later 1, not 2" on the 1 999 ms form with ≈ 39 % exposure; it did not rate 2 172 ms. Its reason ("it buys nothing: the entry is already in the register with that same remedy") holds equally at 2 172, and the exposure is lower, so later 1 is an upper bound. **Fix:** mark the cell "(read from r2: later 1 on the 1 999 form, same 'buys nothing' reason; T2 has lower exposure)".
- Seat 3 1 / 1: now own — file 58 Round 5: "1 / 1 holds at 2 172 ms … No new condition." Its arithmetic agrees with mine: relative to the 1 817 print baseline, 1 + 0.92d = 2 172/1 817 = 1.195 → d = 0.21 (≈ ×1.21); relative to 1 889, ≈ ×1.16. Drop the "(read)" marking and the CONVENE offer.
- Seats 2, 7 unchanged and faithful.

**Arithmetic.** (2 106 + 1 849 + 1 887 + 1 715)/4 = 1 889.25; × 1.15 = 2 172.6 → 2 172 (truncated; state "rounded down"). Max row 2 106 < 2 172: 0 of 4 over. 2 172/1 817 = 1.195 ≈ ×1.20, as stated. Sum: 5 (0+1) + 6 (0+1) + 3 (1+1) + 2 (1+1) + 7 (1+1) = 9 < (b)-conditioned 10; max 1 vs T1's 2 (Seat 3 r3: "my later rating returns to 2"). Ordering correct; one composition this round.

**Sentences.**
- macOS sentence and (c): consistent with the form; the test carries (c) (`strict30s` L81, used at L454) and the trigger (`kMacGrowthTriggerMs = 2172` L93; `MACTRIGGER` only where `!absoluteAsserted`, L533–540; `trigger=` printed). Fit.
- **(d) as reworded contradicts item 1's pin rule.** "A broken assertion, or the macOS trigger, is a defect: … remedy phase-07c conditions 9–10 through `/fix-plan`" assigns the synthesis remedy to every broken assertion, including a broken work pin (W_pilot / W_final, unit-decay length, FFT n), whose own rule (test L332–336 comment; form item 5) is "re-pinned only with a CHANGELOG reason naming the code change". File 66's (d) had no remedy clause and the original (d) said "it enters the register with its remedy". **Fix (exact):** "(d) A broken assertion, or the macOS trigger, is a defect: no re-run, no W_max cut, no range change, no seam; it enters the register with its remedy through `/fix-plan` — a timing entry: phase-07c conditions 9–10; a work-pin entry: the code change named, re-pinned only with a CHANGELOG reason."

**Debt register.** Rows for Seats 5, 6, 3, 2, 7 cover every later 1; Seat 6's row ("one constant (disarm)", repaid at the 07c re-pin) matches its r2 words; 07c condition 9 and Phase 13 exist (phase-07c.md L95/L126/L140, phase-13.md L123). Complete.

**Against files 66/68's unchanged parts.** No contradiction found: the GROWTH print stays at 1.10 × 1 817 (= 1 999) and the trigger at 2 172 are two distinct lines, both named; phase-05i scope 3 (iii) updated to 2 172 per the text; baselines, window, pins, `if: always()`, PRD ids and the AMENDS line as rated in files 65/67/69.

Files: /home/user/makroof/docs/review/phase-05h/70-decider-decision-RG-1-r4.md, /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md (Round 3), /home/user/makroof/docs/review/phase-05h/61-seat6-restore-gate-runner-variance.md (Round 2), /home/user/makroof/docs/review/phase-05h/58-seat3-restore-gate-runner-variance.md (Round 5), /home/user/makroof/tests/unit/test_diffuse_records.cpp L81, L93, L332–336, L454, L533–540.
