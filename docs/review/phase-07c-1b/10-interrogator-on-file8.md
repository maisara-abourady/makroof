# 10 — Interrogator, decision mode, round 2, on decider file 8

2026-11-13, corpus c1b171f. Saved by the orchestrator from the interrogator's report. Read: files 8, 4, 6; 2-seat1 … 8 (B2-a,
signal, D-B5 lines); 5-seat2/3/6/7-r2; 7-seat1-r2-signal; 7-seat7-r2b-signal; 7-seat4-DB2; 7-seat6-r2b; 7-seat3-r2b;
7-seat5-r2b; README "Who answers Maisara's questions"; PRD L101–112; BUILD_PLAN L160, L169–171; phase-13, 13-3, 13-5;
`ScenePipeline.cpp` L771–939. No new acoustic claim load-bearing (Vorländer §4.3 Eq. 4.15 unchanged, CORRECT in round 1).
(The B-iv+ cells of Seats 5, 6, 7 — files 9 — had not been read by this check.)

## Outcomes
| decision | outcome |
|---|---|
| D-B1 (B1-b) | **SURVIVES** (rows 03, 04, 07 corrected; 13-3 scope 4 and 13-1b exist, phase-13.md L69, L94) |
| D-B2 (B2-a″) | **PRD MISREAD (formal)** — map, ordering, debt faithful; its acceptance check leaves B2-b dry out against the preamble (row 05) |
| FM-B2 | **PRD MISREAD (formal)** — part of round-1 Q1 unanswered (row 05) |
| FM-10S | **PRD MISREAD** — the R3 / release-machine passage left out; no plan line carries the reading there (row 06) |
| D-B3 W-a + companions; s1 | **SURVIVES** (plan item 6 wording, row 22) |
| D-B4 (C7′) | **SURVIVES WITH CORRECTIONS** (rows 09, 10) |
| D-B5 (i) S2 | **SURVIVES** |
| D-B5 (ii) B-iv / FM-GROWTH | **TENSION MISREAD** and **PRD MISREAD** (rows 11–15) |
| D-B5 (iv) (iv″) + exit | **PRD MISREAD (formal)** inside FM-GROWTH; map faithful (rows 16, 17) |
| D-B5 (iii) M-a / FM-TRIG | **SURVIVES WITH CORRECTIONS** (rows 18–20) |
| D-B5 (v) E1 | **SURVIVES** |
| D-B5 (vi) X-d− | **SURVIVES** (row 21) |

## Ledger
| id | decision | check | item | verdict | evidence | outcome | question |
|---|---|---|---|---|---|---|---|
| P07C1B-R2-01 | D-B1 | ordering / debt / K7 | sums 23, 22; residual owner; K7 | faithful, corrected | B1-a 23, B1-c 22, B1-b 5 < B1-d 16; phase-13.md L69 "S9 … 13-3 (scope 4) … a miss opens `13-1b` (D-PS4 instruction 2)"; K7 restated as R1-07 asked | SURVIVES | — |
| P07C1B-R2-02 | D-B2 | D2-L1 | prepare-first: insertion then a full restore, nothing reused | CORRECT (code) | `prepare` L812–822 `decide(Synchronous, load=false)` with no `restoreGen_`; `restore` L914 quiesces; L923 `synchronous = !loadedState_ \|\| !lastIrSet_` makes a second synchronous build | — | — |
| P07C1B-R2-03 | D-B2 | D2-L2 | 1.16–3.44 s; 11 366–13 646 ms | CORRECT arithmetic; an estimate | 10 206 + 1 160 / + 3 440; 145–430 ms a 05i range, 10 206 one macOS run; labelled "est." and now measured (record (h), two orders) | — | — |
| P07C1B-R2-04 | D-B2 | map | B2-a″ cells | faithful, one slip | S4 0/1 (fc) follows Seat 4's fallback "the alternative goes to 07d with D-B4" (7-seat4 L25–27) once Seat 5 rated synchronous output-1 decays 0/2; S5 1/1 on its conditions (7-seat5 L41–44; "larger total" at least as strict); S6 silent 3/3 right (7-seat6-r2b L6); fc cells for S1, S2, S3, S6, S7, S8 the seats' B2-a words. Slip: S9 not required → 0/0, not "—", on B2-b dry. Sums B2-a″ 8, B2-a 9, B2-d 19 | SWC | — |
| P07C1B-R2-05 | D-B2 / FM-B2 | PRD proxy | options vs the preamble and AX38 (iv) at project load | **PRD MISREAD (formal)** | B2-b dry shown only against NFR-1; async insertion removes the serial 1.16–3.44 s in prepare-first hosts (the restore's quiesce cancels it, L914) — the preamble's side of B2-b, asked in R1 Q1; B2-d likewise not shown against the prepare-first figure; winner likely unchanged (preamble "Accuracy is the top priority", L101) | PRD MISREAD | Q4 |
| P07C1B-R2-06 | FM-10S | PRD proxy | where the 10 s line is applied | **PRD MISREAD** | AX38 (iv) Record (L160): "phase-13 Raise item 3 applies the 10 s line to the former on the release machines"; phase-13-5 L17–19 R3 (also 13-1); FM-10S reads the line "on 07d's record", does not cite R3; plan items 3, 8 carry the larger-total reading to 07d and 08-4, not to 13-1 or 13-5 R3 where it is applied before release | PRD MISREAD | Q3 |
| P07C1B-R2-07 | FM-10S | reading | includes insertion solves; AMENDS nothing | CORRECT as a reading | README item 1 allows "the scope or the reading of one of her earlier answers"; her line names the user's wait; R17 | — | — |
| P07C1B-R2-08 | FM-B2 | AMENDS / scope | scope reading of AX48 FM-3′; NFR-2 dropped | faithful (R1-13, R1-15 answered) | AX48 L170: keyless load "any mismatch, or a v1 state"; insertion not named → scope reading, no AMENDS | — | — |
| P07C1B-R2-09 | D-B4 | debt | S6, S8 row "5–10 s 8-stem loads until 07d" | IMPRECISE | the decider's own prepare-first estimate ≈ 11.4–13.6 s (D2-L2) | SWC | restate |
| P07C1B-R2-10 | D-B4 | composition | 07d's 5 s criterion moved to the larger (prepare-first) total | not shown | Seats 3, 6, 7, 8 rated C7′ against the restore-only total; Seat 7's later 1 rests on 07d sizing ("07d may split to 07d-b"); only Seat 5 rated the stricter criterion; sums right (C6 = C1 + C6 = 10, C8 = 21, C7′ 13) | SWC | confirm from those seats' conditions that no C7′ cell rises |
| P07C1B-R2-11 | D-B5 (ii) | map / ordering | B-iv+ unranked on missing cells | **TENSION MISREAD** | Seats 5, 6, 7 had no B-iv+ cell; Seat 2's is fc; the decider says if they come in ≤ 1/1 "B-iv+ wins on sum (9 vs 10)"; Seat 3's ≥ 6-run condition is a 07d plan line writable now; deferring a possible winner to the 07d re-pin is R1-35's defect | TM | Q1 |
| P07C1B-R2-12 | D-B5 (ii) | map / debt | S3 1/1* only if f ≤ ×1.4 | INCONSISTENT timing | f comes "from the S2 split" (D-B5 (vi) item 3), produced in this phase; if f > ×1.4 Seat 3's B-iv cell is 1/2 (5-seat3-r2 L31–32), max 2, the ranking changes in 07c-1b; "07d re-pin board on B-iv+" too late | TM | Q1 |
| P07C1B-R2-13 | D-B5 (ii) | other cells | S2 1/1, S3, S5 1/1, S6 1/1, S7 1/1; B-i/ii/iii | faithful | S2 C1–C3 met by plan item 9 (re-pins at 07c-2, 07d; WARNING below mean/1.10; f stated); S6 (a)–(d) met; S7 public reason and `::warning::` present; S5 2-seat5 L118–123; sums B-iv 10, B-i 12, B-iii 15 | — | — |
| P07C1B-R2-14 | D-B5 (ii) | f formula | f = [1.10(1−s_F) − (1−s_L)]/(s_L − 1.10·s_F) ≈ 1.28 | CORRECT; IMPRECISE domain | (s_L·f + 1 − s_L)/(s_F·f + 1 − s_F) = 1.10 → the formula; 0.459/0.359 = 1.279; detection only if s_L > 1.10·s_F (item 9(a) silent); "armed every Linux / Windows run" only if the S2 Windows max/min ≤ 1.10 (proxy 1.096) | minor | state both conditions |
| P07C1B-R2-15 | FM-GROWTH | PRD proxy | B-iv chosen over B-iv+ | **PRD MISREAD** | the FM's own line: "B-iv+ the same plus in-window uniform detection, unrated"; the cited PRD ids (preamble, NFR-6) point to B-iv+, which loosens nothing; the choice rests on the map alone and on missing cells; NFR-4 cited for "macOS print-only" but NFR-4 (L108) names platforms, not CI form (IMPRECISE) | PRD MISREAD | Q1 |
| P07C1B-R2-16 | FM-GROWTH | AMENDS completeness | names "in-window on Linux and Windows, printed on macOS" and "never a red or out-of-window run" | IMPRECISE / incomplete | other passages of her recorded 4c text are changed too: "k and the baselines are re-derived from ≥ 3 in-window runs at the 07c re-pin"; "the ±5 % window and the solve bound re-derived from ≥ 3 in-window runs"; the printed "ratio above 1.20 × its pinned ratio" (now asserted at 1.10); (b) "inside the ±5 % flutter window"; "Asserted every run … else `NOT EVALUATED (runner)`" | PRD MISREAD | Q2 |
| P07C1B-R2-17 | D-B5 (iv) | map / PRD proxy | (iv″) + exit, sum 5 | map faithful; **PRD MISREAD (formal)** | S2 1/1 meets C4's second branch (5-seat2-r2 L36–37); S3 0/1 (assertion not adopted); S6 0/0 fc (Phase 13 date named); S7 0/1 with a dated exit; FM-GROWTH's answer is "plan item 9a" only — 9(b) not in the answer; (iv) options not shown against any PRD id | PRD MISREAD | Q2 |
| P07C1B-R2-18 | D-B5 (iii) | arithmetic | 2 107.7; 2 423; 2 571 vs 2 572; 2 592; ×1.16 | CORRECT | 6 323/3 = 2 107.67; 1.15 × = 2 423.8; 1.22 → 2 571.4; 1.23 → 2 592.4; 1 + 0.15/s_L = 1.163 | — | — |
| P07C1B-R2-19 | D-B5 (iii) | map / ordering | S7 on M-a "not rated" while S6-k fc 1/1; sums over 3 vs 4 seats | slip, winner unchanged | Seat 7's V4 reasoning ("a rule changed after the fact", 2-seat7 L77–81) points no higher on M-a than S6-k; S6-k falls at step 1 (changes "1.15 ×" in her recorded 4c text), so the sum step is moot; M-a's S3, S5 1/1 follow from the closure path (7-seat3-r2b L43–44; 7-seat5-r2b L55); debt row lacks "undo" | SWC | enter S7's M-a cell from conditions; drop the sum comparison |
| P07C1B-R2-20 | FM-TRIG | AMENDS | "only RG-1's '(≥ 3 in-window runs)' parenthesis" | IMPRECISE | her recorded decisions are briefs verbatim or BUILD_PLAN row parts citing her by date (README L102–104); the applied 4c trigger text is "1.15 × the mean of the four measured macOS medians, rounded down; re-derived at the 07c re-pin", no window (R1-37); M-a applies it as written; the parenthesis is in RG-1's file 70, not in her record | SWC | Q5 |
| P07C1B-R2-21 | D-B5 (vi) | map / ordering / PRD | X-d− sum 6; X-d+ out of bounds | faithful | Seat 6 0/1 (7-seat6-r2b L23); S3 fc from Seat 3's closure-evidence condition (7-seat3-r2b L44–47), all three parts in item (4); X-a max 2; lines for X-d−, X-d+, X-a, X-b present; R1-41 answered | SURVIVES | — |
| P07C1B-R2-22 | plan item 6 | backing | "AX47 Measurement: replace with …" | IMPRECISE | AX47's Measurement paragraph also says "Every step is measured on the builder thread and recorded … never in the callback" (L169); replacing the whole paragraph drops it, unbacked | — | replace the renders sentence only |
| P07C1B-R2-23 | plan item 9(a) | backing / consistency | "replaces 'in-window on Linux and Windows, printed on macOS'" | INCONSISTENT risk; not backed until (ii) survives | the phrase occurs twice in 4c; the other in-window passages (row 16) would stay and contradict 9(a); 9(a), 9(b) rest on D-B5 (ii), (iv), which do not survive this round | — | Q2 |
| P07C1B-R2-24 | plan text | missing line | FM-10S at phase-13-1 / 13-5 R3 | missing | row 06 | — | Q3 |
| P07C1B-R2-25 | D-B2 | observation | Seats 6, 8 B2-a cells rated before the prepare-first cost was known | not a misread (the seats' own words) | 2-seat6 L30, 2-seat8 L26 rate only the insertion stall; the new cost bears on their subject; Seat 6 saw file 6 row 14 in r2b and did not revise | — | optional: confirm the cells stand |

Plan items backed by surviving decisions: 1, 2, 3, 4, 5, 6 (with row 22), 7, 8 (with rows 09, 10), 10, 11, 12; 9(c)–(f) by (iii),
(v), (vi); 9(a)–(b) wait on rows 11–17.

## Questions for the decider (most consequential first)
1. **B-iv+ (FM-GROWTH):** Seats 5, 6, 7's B-iv+ cells; is Seat 3's ≥ 6-run 07d condition written now; redo the ordering in this
   phase; read Seat 3's f ≤ ×1.4 at 07c-1b's S2 split, not 07d; if B-iv still wins, the PRD reason (not the map) why B-iv serves
   the preamble and NFR-6 better than B-iv+ (which adds detection, loosens nothing).
2. **FM-GROWTH scope and AMENDS:** list every passage of her recorded AX38 4c text that 9(a), 9(b) supersede (row 16), in the
   AMENDS line and plan item 9; put 9(b) in the answer; show (iv″) with and without the exit against the PRD ids.
3. **FM-10S and Phase 13 R3:** does the larger-total reading apply where her line is applied before release (AX38 (iv) Record, "on
   the release machines", phase-13-1 / 13-5 R3)? If so cite it and add the plan line; if not, say why the CI record replaces it.
4. **FM-B2:** B2-b dry and B2-d against the preamble and AX38 (iv) with the prepare-first figure (B2-b removes the serial 1.16–3.44
   s at project load).
5. **FM-TRIG:** which passage of her recorded decisions (README L102–104) contains "(≥ 3 in-window runs)" for the macOS trigger?
   If none, restate FM-TRIG as a reading that amends nothing; enter Seat 7's M-a cell.

Smaller corrections (no rebuttal round): row 04 Seat 9's B2-b dry → 0/0; row 09 the S6/S8 debt figure; row 10 confirm the
composition from the seats' C7′ conditions; row 14 state the two conditions on f in 9(a); row 19 drop the unequal-set sum, give the
debt row its "undo"; row 22 plan item 6 wording. Round 2 of 3: if round 3 fails on the same items, README item 3(a) sends the ruling
to her.
