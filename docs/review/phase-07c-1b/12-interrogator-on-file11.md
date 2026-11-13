# 12 — Interrogator, decision mode, round 3 (last), on decider file 11

2026-11-13, corpus c1b171f (14 books). Saved by the orchestrator from the interrogator's report. Read: file 11, file 10,
9-seat5/6/7, 5-seat3-r2, 5-seat2-r2, file 8 (L226–255, L312–323, L361–365); C7′/C7 lines of 2-seat3, 2-seat6, 2-seat7,
2-seat8; BUILD_PLAN L160 in full, AX47 Measurement; PRD L99–112; README L85–136; `.claude/agents/decider.md` §5; phase-13-1,
13-5 (R3 L17–19; R5), 13-2 scope 1, phase-13.md L54, phase-07c-1b (scope 1, AC 1, review focus), phase-07c-1 L86–92;
`tests/unit/test_diffuse_records.cpp` L102–110. No new acoustic claim load-bearing (Vorländer §4.3 Eq. 4.15 unchanged,
CORRECT in round 1); process, arithmetic and plan-text checks only.

## Outcomes
| decision | outcome |
|---|---|
| D-B1 (B1-b) | **SURVIVES** |
| D-B2 (B2-a″) / FM-B2 | **SURVIVES WITH CORRECTIONS** (row 18); R2-05 answered |
| FM-10S | **SURVIVES WITH CORRECTIONS** (row 17); R2-06 answered, Phase 13 R3 carries the reading |
| D-B3 | **SURVIVES** (item 6 replaces one sentence only) |
| D-B4 (C7′) | **SURVIVES** (rows 09, 10 applied; quotes verified, row 20) |
| D-B5 (i) | **SURVIVES** |
| D-B5 (ii) B-iv/+07d / FM-GROWTH | **SURVIVES WITH CORRECTIONS** (rows 01–16): map complete and faithful, ordering and PRD tie-break hold, AMENDS exact; corrections to claims, wording and plan text, none changes the winner |
| D-B5 (iv) (iv″) + exit | **SURVIVES** (shown against PRD ids inside FM-GROWTH; G7, G9 match Seats 2, 3, row 22) |
| D-B5 (iii) M-a / FM-TRIG | **SURVIVES WITH CORRECTIONS** (rows 15, 19) |
| D-B5 (v) E1, (vi) X-d− | **SURVIVES** |

**NEEDS MAISARA from this check: none.** Every item survives (some with corrections); nothing goes to her as case (a). Her open
item is still FM-D1-S3 only. For FM-GROWTH, rows 13–14 are inconsistencies in the drafted plan text, not in the claims the
decision rests on; rows 09–11 are statements to Maisara that say more than the evidence supports; applying the restatements below
completes the decision without a further round.

## Ledger
| id | decision | check | item | verdict | evidence | outcome | correction |
|---|---|---|---|---|---|---|---|
| P07C1B-R3-01 | D-B5 (ii) | map | B-iv+ now: S3 1/1, S5 2/2, S6 1/1 (1/0 with a′, e, f), S7 1/1 | faithful | 5-seat3-r2 L19 "1 \| 1"; 9-seat5 L9 "adopted now … 2/2", L12, L19; 9-seat6 L13, L17; 9-seat7 L18, L23 | — | — |
| P07C1B-R3-02 | D-B5 (ii) | map (fc) | B-iv/+07d S5 1/1 | faithful | 9-seat5 L36–41 conditions (1)–(4): ≥ 6 runs at 07d; 1.10 kept, w narrowed with (1+w)·max ≤ 1.083 (L38); every in-window evaluation printed; coverage stated; "≥ 1.07 → no leg" — all in G5 | — | see row 10 |
| P07C1B-R3-03 | D-B5 (ii) | map (fc) | S6 1/1, not 1/0 | faithful (conservative) | Seat 6's B-iv later-1 reason, "07d's remedy could grow synthesis ≈ 25 % unasserted" (9-seat6 L21–22), holds through 07d; (a′) in G5's "what it detects", (e) in G5 and §0, (f) in G13 and item 8 | — | — |
| P07C1B-R3-04 | D-B5 (ii) | map (fc) | S7 1/1 | faithful | 9-seat7 L31–33: (1) X-d− path in G5; (2) `::warning::` in G10 and (f); (3) ≥ 6-run re-pin in item 8 | — | — |
| P07C1B-R3-05 | D-B5 (ii) | map (fc) | S3 = B-iv's cell until 07d (1/1 A, 1/2 B) | faithful | Seat 3's "→ 1/0" is conditional on B-iv+, whose leg asserts during 07d (5-seat3-r2 L33); the variant adds no leg before 07d; reading 1/0 makes the variant win outright (sum 9) — the winner does not depend on it | — | — |
| P07C1B-R3-06 | D-B5 (ii) | map (fc) | S2 1/1 | faithful | 5-seat2-r2 L27–30: C1 in G13; C2 in G6; C3 in G5 | — | — |
| P07C1B-R3-07 | D-B5 (ii) | ordering | steps 1–6 | correct, one slip, winner unchanged | redone: no bound broken, no 3; A: B-iv 1/10, variant 1/10, B-iv+ now max 2; B: all max 2, sums 11, 11, 12 (11 with S6's conditions). Slip: step 6 calls B-iv+ now "the dearest" to undo, but Seats 5, 6, 7 each give its undo as "one constant"; Seat 5's "real cost is each false red's investigation" (9-seat5 L23) is a running cost, not an undo cost; step 6 ties; the PRD check decides either way | SWC | step 6: "tie (one constant each); decided by the PRD check" |
| P07C1B-R3-08 | D-B5 (ii) | PRD proxy | tie-break (README L108–112); why not B-iv+ now | sound; one figure IMPRECISE | the variant = B-iv until 07d then only adds detection, no seat higher, so no PRD id points to B-iv; every option shown against preamble, NFR-6, RG-F1; R2-15 answered. IMPRECISE: "observed max/mean up to 1.062" is an endpoint bound — Windows 2.439–2.674 gives max/mean between 2.674/2.5957 = 1.030 and 2.674/2.5173 = 1.062; the red threshold 1.10/1.05 = 1.0476 falls inside the bracket | SWC | "can overlap (bounds 1.030–1.062 bracket the 1.048 red threshold; individual ratios not printed)" |
| P07C1B-R3-09 | D-B5 (ii) | debt / objection | S3 row "the per-stage split printed every run limits this"; "repaid when: 07d re-pin adds the absolute leg"; "prints on every OS every run (vi item 3)" | **INCONSISTENT** (not load-bearing) | D-B5 (vi) item 3 (file 8 L317) and plan 9(d): "printed on every OS **on the S2 runs**, test-only", not every run; item 8 and G13 re-derive reference and baselines from runs "after 07d's last code change", so a synthesis growth 07d itself introduces becomes part of the new baseline and the absolute leg cannot assert it — what reads it is 07d's closure evidence (the macOS per-stage split after the remedy), then Phase 13; no effect on the winner (S3 read at B-iv's cell; the tie-break does not use this premise) | SWC | restate the S3 row's mitigation and "repaid when" (and G5's closing PR sentence "until the 07d re-pin") to name what actually reads 07d-introduced growth; correct "every run" |
| P07C1B-R3-10 | D-B5 (ii) | G5 coverage | "(≈ ×1.12–1.28 on upper-edge runs at ±5 %)" | IMPRECISE | the variant never runs ±5 %; at the re-pin w ≈ 2 %. Seat 5's reduction with 05h shares 0.92 / 0.51: the leg fires on an in-window run iff (1+w)(0.92k+0.08)/(0.51k+0.49) > 1.10; at w = 0.02, 0.370k > 0.448 → k > 1.21; coverage ≈ ×1.21–1.28 (beyond, the ratio catches it), only on runs ≈ 10 % faster than F̄ (at ±5 % → k > 1.12, Seat 5's figure) | SWC | give the figure for the window used, labelled 05h shares, or keep only "[computed at the re-pin]" (Seat 5's condition (4) asks for the true coverage) |
| P07C1B-R3-11 | FM-GROWTH | wording for Maisara | "sized from ≥ 6 runs so it cannot fire on unchanged code"; "returns where it can measure without false alarms" | IMPRECISE | Seat 5's condition is "a stated margin" (9-seat5 L37–38): 1.10/1.083 ≈ 1.6 % above the largest r/r̄ of ≥ 6 runs — a sample margin, not a guarantee; the public sentence extends Seat 7's "measured runner speed … measures the code" (5-seat7-r2 L27) | SWC | "sized with a stated margin over the largest of ≥ 6 runs"; drop "cannot" and "without false alarms" |
| P07C1B-R3-12 | FM-GROWTH | AMENDS | 17 superseded passages | CORRECT | each verbatim at L160; the SOLVE passage's "…" elides only "in the scene's `warnings=`"; every in-window rule passage listed; untouched in-window mentions are historical ("in-window, flutter −3.7 %", "28.74 s, in-window") or still true ("counted in §0 apart from the in-window status"); the "Not amended" list matches L160 | — | — |
| P07C1B-R3-13 | FM-GROWTH | G1–G14 vs unamended 4c | G10 under "Printed with WARNING, never asserted on hosted runners"; "S2 mean" in G5, G10, G11, G12 | INCONSISTENT / IMPRECISE | header conflict: from the 07d re-pin the in-window absolute leg is asserted on Linux and Windows (G5), yet G10 lists "the absolute low-α median above 1.10 × its S2 mean on every OS" under "never asserted"; stale name: G13 and item 8 mandate re-pins at 07c-2 and 07d, after which "S2 mean" no longer names the baseline; G1, G2 omit G5's print-only proviso for max/min > 1.10 | SWC | G10: "where not asserted (macOS; Linux and Windows out of window or before 07d)"; name the reference "the current pin (S2 at 07c-1b; re-pinned at 07c-2 and 07d)" |
| P07C1B-R3-14 | FM-GROWTH | plan backing | phase-07c-1b scope 1, AC 1, review focus | INCONSISTENT (missing line) | phase-07c-1b L44–46, L96–98 still require baselines, ±5 % window and `kSolveWarn` "from ≥ 3 in-window CI runs … never a red or out-of-window run"; review focus "in-window, none red"; G12 says "out-of-window runs count" and Q2 says no OS has 3 in-window runs — AC 1 as written cannot be checked; phase files are not her recorded decisions (no AMENDS), but a plan line is needed | SWC | add an item rewriting scope 1, AC 1, the review focus to the G12 / G7 / G9 form |
| P07C1B-R3-15 | plan item 9 | exactness | sub-labels "(c)", "(d)", "(e)", "(f)" | IMPRECISE | collide with 4c's own (a)–(d); "(d) X-d−" could be applied to 4c (d), which "Not amended" keeps word for word | SWC | relabel (e.g. 9-iii, 9-vi, 9-v, 9-out) and name where each is inserted |
| P07C1B-R3-16 | FM-GROWTH | rests on | "CLAUDE.md 'tolerances never loosened'" | IMPRECISE | CLAUDE.md has no "loosen"; the rule is decider.md §5 ("loosening a tolerance so a test passes"); not a PRD id | SWC | cite decider.md §5 |
| P07C1B-R3-17 | FM-10S | PRD proxy / claims | R3 at Phase 13; item 13 | faithful; two IMPRECISE | AX38 (iv) Record verbatim (L160), 13-1, 13-5 L17–19, phase-13.md L54; "up to 3.44 s" = 8 × 430 ms. (a) "13-2 scope 1 runs the records there" not yet true (13-2 scope 1 re-checks W_max, n*_max, 4c; record (h) on release machines comes from item 13's addition); (b) "'the former' … is held to 10 s": her line is an escalation ("goes to Maisara before the first release"), and AX38 (iv) labels the marks "not audibility limits" | SWC | (a) "13-2 scope 1 will run record (h) there (item 13)"; (b) "the former is read against her 10 s line" |
| P07C1B-R3-18 | FM-B2 / D-B2 | PRD proxy, objection | lines for B2-a″, B2-b dry, B2-d, B2-b silent | CORRECT; one IMPRECISE | B2-b dry removes 1.16–3.44 s but 10 206 ms > 10 s; B2-d strains NFR-8; B2-b silent 3/3 veto; R2-05 answered. IMPRECISE: "stands on step 3" — if Seat 8's later cell rose to 2 every option sits at max 2; B2-a″ then wins on sum (9 vs B2-d 19, B2-b dry ≥ 19, S5 unrated): step 5 | SWC | "stands on step 5" |
| P07C1B-R3-19 | FM-TRIG / D-B5 (iii) | AMENDS / map / debt | reading amends nothing; S7 cell; undo | faithful; citation IMPRECISE | "1.15 × the mean … rounded down; re-derived at the 07c re-pin" verbatim at L160; M-a applies it as written; S7 M-a 1/1, Seat 7's (1)–(4) (9-seat7 L33–36), "undo" column present; sum comparison dropped; 1 + 0.15/0.92 = 1.163, 1 + 0.23/0.92 = 1.25. IMPRECISE: "README L102–104" is the definition of her recorded decisions, the text is BUILD_PLAN L160 | SWC | cite L160 |
| P07C1B-R3-20 | D-B4 | rows 09, 10 | debt figure; C7′ composition | faithful | quotes verified: 2-seat3 L88, 2-seat6 L48, 2-seat7 L52, 2-seat8 L40; none tied to the restore-only total | — | — |
| P07C1B-R3-21 | plan text | backing | items 1–13 | all backed | 1–3 D-B1, FM-10S; 4, 5, 11, 12 FM-B2, D-B2; 5, 6 D-B3; 7, 8 D-B4, FM-10S, D-B5 (vi), FM-GROWTH; 9 FM-GROWTH, FM-TRIG, D-B5 (iii)–(vi); 10 the ledger; 13 FM-10S; gaps row 14 (missing line), rows 13, 15 (wording) | — | — |
| P07C1B-R3-22 | D-B5 (iv) | PRD proxy | (iv″) with / without exit; "Confirm the 05i rule" | faithful | each option against preamble and NFR-6; G9 = Seat 3's exit (5-seat3-r2 L35–37) + Seat 2's C4 second branch (5-seat2-r2 L36–37); print-only, S3 stays 0/1 (R2-17) | — | — |

## Corrections to apply (last round, no rebuttal)
1. S3 debt row, strongest objection and G5's closing PR sentence (row 09): the split prints on the S2 runs and in 07d's closure
   evidence, not every run; the 07d re-pin re-baselines on post-remedy runs, so the absolute leg does not repay Seat 3's 07d debt.
2. Add a plan item rewriting phase-07c-1b scope 1, AC 1 and the review focus to the S2-mean form (row 14); fix G10 and the "S2
   mean" naming in G5, G10, G11, G12 (row 13); relabel plan item 9's sub-items (row 15).
3. G5's coverage figure for the window used, ≈ ×1.21–1.28 at w ≈ 2 % (row 10); for Maisara and the public sentence "a stated
   margin", not "cannot fire" or "without false alarms" (row 11).
4. FM-10S: item 13 adds record (h) to 13-2; "held to" → "read against" (row 17). FM-B2: "step 5" (row 18). FM-TRIG: cite L160
   (row 19). FM-GROWTH: cite decider.md §5 for "never loosen" (row 16). Ordering step 6: a tie settled by the PRD check (row 07).
   The 1.062 figure is an endpoint bound (row 08).
