# 31 — Interrogator on decider file 28b (P07C1B-R1 round 2)

2026-11-13, corpus c1b171f (no acoustic claim load-bearing). Saved by the orchestrator from the interrogator's report.

## Outcome
- **Decision (1)** (re-list macOS low-α; text and flag in one carrier push): SURVIVES WITH CORRECTIONS (C-1 … C-13).
- **Decision (2)** (one MACTRIGGER is a print; a pair joins X-d−): SURVIVES WITH CORRECTIONS (C-8, C-10).
- **For Maisara:** PRD MISREAD (8a-1, 8a-2); the decider re-answers.
- The winners 1b′ and 2a are unchanged. Nothing FALLS or is UNDERCONVENED.

## Checked and correct
- Map cells match file 30. Sums: Q1 7 / 1–3 / 3; Q2 4 / 7.
- 1b′ S5 0/1 read from Seat 5's condition (faithful).
- L1/K2: `listed` is used only at L112, L687, L690, L693; no REQUIRE reads it.
- L2: the RG-1 sentence is verbatim.
- L3: 30.50 / 24.08 = 1.2666; 14 × 2.179 = 30.51 (macos.log L3056).
- L5: budget per defect.
- L6/K4: code L788–789 appends OVER30S unconditionally; ci.yml L434 greps it; macos.log L4129–4138.
- K7: macos.log L3049–3050, L3055.
- K8: macos.log L3053 "1673.8 [1467.8 1948.5] … restore median 1851" (90.4 %).
- Push clause: ci_fingerprint.py L35, L44 exclude `docs/phases/` and `docs/BUILD_PLAN.md`; `tests/` is not excluded.
- Anchors T1, T2, T5, T4 row 07d and scope 1, T3 scope 7: verbatim and unique.
- T5 figures correct.
- AMENDS form as in phase-05i file 9 Q1 and AX38 G-1.

## Findings
- **Seat 2 reason:** imprecise. It should read "no compute or recompute time set; records only".
- **S6 on 1b′:** holds only with C-7. T3 lands "re-listed" now, ahead of the flag.
- **S3 and S7 on 1b′:** not rated by those seats; mark "(read from 1b/1c)" (C-4).
- **T1's standing any-run re-list rule:** unrated (Seat 5 "Accepts that only the re-pin's own runs count"; Seat 6's any-run ask was a 1a condition). The H1 note cites "Seat 5 (i)", which is the 2a fingerprint clause (C-1).
- **Bounds slip:** 1b (flag at the review push) is inside bounds. 1b′ = 1b + Seat 5's fallback (C-3).
- **Hidden premise "the carrier adds no CI run":** if the review asks only for prose, the `tests/` flip forces a full run (C-5).
- **L4 "05i precedent":** clause (2) covers changes the review asks for. The 05i carrier was decided but **never fired**: PR #30 merged first, and the flag landed in follow-up PR #31 (ledger P05I-120; BUILD_PLAN L160; brief 2026-11-12-05i-windows-listed.md L20) (C-6).
- **T1 gloss "(a) reads … the E1 values":** (a) lists an entry whose recorded value is > 29.1 s; the E1 values are ≤ 24.08 s; the code prints 33.40 s as "recorded"; the value after re-listing is unstated (Q4).
- **Q4 naming:** the 'otherwise' branch is phase-05i §3.3 (ii)'s, not E1's (C-2).
- **Carrier item 5:** the label is on the "restore gate" line, not the GATE line; at or below 30 s it reads "WARNING PASSES30S … remove it through /fix-plan" (C-9).
- **T3 vs T4:** inconsistent in the interval (C-7).
- **Seat 3 C1:** not met in T2 (L and emitters), T4 scope 1, T8, the carrier comment or the CHANGELOG line (C-8).
- **Anchor T4 scope 5:** spans a hard wrap (phase-07d L69–70); unique.
- **T7:** phase-07c-2.md has no carry section; T7 names no insertion point (C-11).
- **T8:** §6 has three columns (`Date | Change | By`, L416) (C-13).
- **T5 counts:** still not given (minor).
- **Strongest objection:** "holds on the 05i precedent" does not hold. The 05i review carrier failed (P05I-120). The 07c-2 fallback lag is open-ended (07c-2 is "not started" and depends on 07c-1b `done`, BUILD_PLAN L36).
- **8a-1 PRD MISREAD:** "no rule changes" is untrue while T1 adds a standing rule, and the Decided line hides that rule from her veto.
- **8a-2 PRD MISREAD:** her recorded decision is left out. Brief 2026-11-12-05i-windows-listed.md L10–12: her words ("do that") on a flag owed after PR #30 merged before its review push; the vehicle was a dedicated follow-up PR, #31. 1b′'s fallback (07c-2's first code commit) is not shown against it.
- **8a-3:** every option is shown. Two overreads: "NFR-4 ranks" (NFR-4 lists platforms) and the preamble not quoted whole ("CPU load and latency may be high…"). The plain line misstates 30.50 s: it is 14 × the slowest restore (2.18 s).
- **R2 / T2:** Seat 5 (ii)'s otherwise branch is implicit (C-10).

## Corrections (exact text)
- **C-1:** T1 either becomes instance-only ("under RG-1's re-listing provision the macOS entry below is re-listed under (a) on run 43427854710, recorded value `<per Q4>` (> 29.1 s at the pinned W_max)", striking the H1 note), or keeps the standing rule, rated by Seat 5 and named in the AMENDS parenthesis and the Decided line.
- **C-2:** "E1's 'otherwise' branch" → "phase-05i §3.3 (ii)'s 'otherwise' branch". After "Same carrier (next permitted push)" add "(in 05i that push never came: PR #30 merged first; the flag landed in follow-up PR #31, ledger P05I-120)".
- **C-3:** the bounds line → "1b (flag at the review-round push) is inside bounds; with a review push 1b and 1b′ tie (max 1, sum 1); without one Seat 5 rates 1b 2. 1b′ = 1b + Seat 5's fallback carrier."
- **C-4:** S3 and S7 1b′ cells: add "(read from 1b/1c)".
- **C-5:** "if the review asks for no change before merge" → "if the review asks for no change outside fingerprint-excluded prose before merge".
- **C-6:** push clause → "It rides the review round's push only as a change the review takes up (T6 puts it before the reviewer); otherwise it moves to 07c-2's first code commit (T7). 05i decided the same carrier (file 9 item 4); it never fired (P05I-120)."
- **C-7:** T3 "(OVER30S; the entry re-listed, scope 1)" → "(OVER30S; the entry's re-list decided, P07C1B-R1, lands with its flag in the carrier push, scope 1)".
- **C-8:** wherever 30.50 s appears (T4 scope 1, T8, carrier comment, CHANGELOG line) add "(hosted macOS runner; 100 m / 96 kHz, exact tail L = 12 s, 2 emitters)". In T2, after "100 m / 96 kHz" add ", L = 12 s, 2 emitters".
- **C-9:** carrier item 5 → "the macOS restore-gate line (not the GATE line) reads 'LISTED defect (recorded 14 x worst 33.40 s)'; above 30 s it adds 'WARNING OVER30S (printed, not asserted …)', at or below 30 s 'WARNING PASSES30S: … remove it through /fix-plan' (code L690–693), which T4 reads as closing only in 07d; the GATE line's warnings= is unchanged; no REQUIRE changes."
- **C-10:** T2, after "put the excess in Assemble→Commit" add "(otherwise the pair is a new (d) defect)".
- **C-11:** T7 names its section in docs/phases/phase-07c-2.md.
- **C-12:** Decided line: "after one CI run took 30.50 s" → "after one CI run's restore check read 30.50 s (14 × its slowest restore, 2.18 s; the limit is 30 s)"; "a short lag" → "a lag until the review push, or 07c-2's first code commit".
- **C-13:** T8 → "| 2026-11-13 | **Phase 07c-1b: AX38 4c:** macOS low-α entry re-listed under (a) after closure (run 43427854710, hosted macOS runner, 100 m / 96 kHz, L = 12 s, 2 emitters: 14 × worst 30.50 s); `listed` true, print only | /fix-plan (plan-editor), decider files 28/28b, interrogator files 29/<next> |".

## Questions for the decider
1. Is T1 an instance or a standing rule? If a standing rule, where is Seat 5's rating, and how is "no rule changes" true?
2. Her 2026-11-12 decision and P05I-120: show 1b′'s fallback against it, and give the length of the lag.
3. A prose-only review: does the carrier then force a CI run? How does it differ from the excluded plain flip?
4. After re-listing, which recorded value does (a) read (24.08, 33.40 or 30.50 s)?
5. Are Seat 6's same-push condition and Seat 3's C1 met as written?
