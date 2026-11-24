
# 45: Interrogator diff check of the M3-H /fix-plan application (phase 07c-2b)

To be saved by the caller as `/home/user/makroof/docs/review/phase-07c-2b/45-interrogator-diff-m3h.md`. I changed no files.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. No acoustic fact or number is newly asserted in this diff, so no corpus check was needed. C1–C4 add no new value: 0.75 / 1.74 dB and 3σ were rated CORRECT in file 44 (K31) and are not reopened.

**Limit on this check:** I have no shell in this run, so I could not run `git show HEAD`. Instead I compared the current contents of every file the task names, verbatim, against file 43 §6 (A1, A2, B–I) as amended by file 44's C1–C4. So this check confirms what is now in each file. It cannot see an unrequested edit made elsewhere in those files, away from the anchors. The orchestrator should look at `git show HEAD --stat` for unexpected hunks.

## Verdict: NOT CLEAN. One correction is required (R1). One attribution fix is recommended (R2).

## Ledger

| id | kind | item | verdict | evidence | severity | question | status |
|---|---|---|---|---|---|---|---|
| 45-01 | SOFTWARE/plan text | A1 `phase-07e.md`, full text | applied verbatim | Header, Goal, Gates, Scopes 1–4, Out of scope, AC and DoD match file 43 L268–329 word for word, apart from C1 and C2 | none | — | ok |
| 45-02 | plan text | C1 bullet 1 (07e Run record) | applied | 07e L45: "uses the smaller of the two figures for the two-radius agreement test, and the larger of the two for σ_d of L − R". C1 bullet 2 targets file 43 §2.4 and is in the errata, correctly not in plan text | none | — | ok |
| 45-03 | plan text | C2, both replacements (07e top-up) | applied | 07e L42: "N × the largest gate_b / k_realised,b over the bands below their gate"; "no engine-to-(a0) comparison is read before the top-up completes (S5, 42-seat5 §6: …)" | none | — | ok (see R2 note) |
| 45-04 | plan text | A2 `phase-07e-b.md`, full text | applied verbatim, apart from C3 and C4 | Compared against file 43 L332–392 | none | — | ok, except R1 |
| 45-05 | plan text | C3, three replacements | applied | 07e-b L26 "(0.75 dB at k 684, lower above it; 1.74 dB at k 76)"; L28 "(reference 3σ = x dB)"; L29 "A per-emitter breach that holds at both radii with the same sign also fires the reversal;" | none | — | ok |
| 45-06 | plan text | C4 | applied | 07e-b L21 "two-radius check resolves only 3 × the two-radius SE used (phase-07e run record) dB" | none | — | ok |
| 45-07 | INCONSISTENT (cross-reference) | 07e-b BUILD_PLAN line anchors: L165 (AX42), L167 (AX44), L404 (B11), L408 (B15) | stale after this same commit | Item B adds two §0 rows (07e, 07e-b at BUILD_PLAN L39–40), which moves everything below them down by 2 lines. AX42 is now at **L167**, AX43 at L168, AX44 at **L169** ("…contradicts NW-4C by more than τ" found at L169), B11 at **L406** ("…never changed after results are seen"), B15 at **L410**. So 07e-b's "AX44 (BUILD_PLAN L167)" now points at AX42 | major (the ruling phase quotes these rows as the text it must apply) | Do the anchors refer to the rows by id? If so, the line numbers must match the file as committed | **R1** |
| 45-08 | plan text | Item B: §0 rows 07e and 07e-b, plus appends to 07d and 08-3 and the 08-4 Depends text | applied verbatim | BUILD_PLAN L39, L40, L38 (end), L44 (end), L45 | none | — | ok |
| 45-09 | plan text | Item C: phase-08-4 L3 | applied | "Depends on: 08-3 and 07e-b `done` (and the fix phase …)" | none | — | ok |
| 45-10 | plan text | Item D: phase-07d scope 8 prepend | applied | phase-07d L94 | none | — | ok |
| 45-11 | plan text | Item E: phase-08-3 item 15, item 7 and the checklist line | applied | L78–79 (the file-24 sentence is gone), L57–61, L149–150 | none | — | ok |
| 45-12 | plan text | Item F: run sheet C-b | applied | run sheet L130–131 | none | — | ok |
| 45-13 | plan text | Item G: phase-07c-2b Out of scope | applied | L192–193 | none | — | ok |
| 45-14 | plan text | Item H: 07c-2b status and notes | applied | L37: "blocked (awaiting Maisara: the ABX listener and sitting dates, then the ABX itself)"; "Waiting: nothing on M3-H (decided for Maisara, …)" | none | — | ok |
| 45-15 | plan text | Item I: §6 row | applied verbatim | BUILD_PLAN L538 | none | — | ok |
| 45-16 | self-consistency | Gates and dependencies | consistent | 07e depends on 07c-2b; 07e-b depends on 07e. 08-4, 08-3 item 15 and 07d scope 8 wait on 07e-b plus any fix phase. This agrees across 07e Gates, 07e-b Gates, the §0 rows 07d/08-3/08-4/07e/07e-b, phase-07d L94, phase-08-3 L78 and phase-08-4 L3. The parallel lists (08-1, 08-2, 07d scopes 1–7) agree. Every cross-reference resolves: 07e-b scope 1 verdict (iv), 08-3 item 7, 08-3 AC6, decider file 43 §2.2 and §4a. "phase-07c-2b M3-8" resolves to the run sheet L23 ("M3-8: the rebuild trigger") | none | — | ok |
| 45-17 | attribution | 07e header, §0 row 07e and §6 row L538 list "interrogator files 31, 35, 41" | IMPRECISE (attribution) | The applied texts contain file 44's C1–C4, but no plan text cites file 44. The 07e top-up paragraph is quoted as S5's own words "(S5, 42-seat5 §6)", yet it now includes C2's wording, which is not S5's. The inline citation in C2 marks only the second change | minor | — | **R2** (recommended) |
| 45-18 | stale-reference grep | "24-m3h", "file 24", M3-H pending or awaiting Maisara, "home pending" across docs/ (review/ excluded) | none live | BUILD_PLAN L163 and L531 cite "interrogator file 24" of **phase-07c-1b**, which is unrelated. L536 is the dated §6 change-log row from earlier in the day ("M3-H, is with Maisara, case (a), file 24"). It is history, and the §6 change log is not rewritten. L538 records the change. `docs/sessions/…-phase-07c-2b.md` L118 says "previously case (a), file 24", which is accurate. No phase file, the run sheet or a §0 row still says M3-H is pending with Maisara | none | — | ok |
| 45-19 | drift | Any acoustic or numeric choice added by the plan-editor | none found in the compared text | Every number in 07e and 07e-b is in file 43 §6 or in C1–C4 | none | — | ok |

## Corrections

**R1 (required).** In `docs/phases/phase-07e-b.md`, the BUILD_PLAN line anchors were moved by 2 when the 07e and 07e-b rows were inserted. Make these replacements:
- L25: "AX44 (BUILD_PLAN L167)" → "AX44 (BUILD_PLAN L169)"; "AX42 (L165)" → "AX42 (L167)".
- L31: "B11's clause, L404" → "B11's clause, L406".
- L38: "AX44 (BUILD_PLAN L167: …)" → "L169"; "AX42's τ (L165)" → "L167"; "B15 (L408)" → "B15 (L410)".
- L42: "AX44's GA-limit paragraph (L167)" → "(L169)".

Re-grep after any later BUILD_PLAN insertion above L167, or cite the rows by id alone. The PRD line numbers (L49 and others) are unaffected, because the PRD was not touched.

**R2 (recommended, bookkeeping only; no cell, value or rule changes).** Add "44 (corrections C1–C4)" to the interrogator lists in three places:
- the 07e header ("interrogator files 31, 35, 41");
- the §0 row 07e;
- the §6 row L538.

In 07e L42, after "(S5, 42-seat5 §6)" on the top-up paragraph, add "; formula and trigger wording per interrogator file 44 C2". This makes clear that the quoted paragraph is no longer entirely S5's words.

Once R1 is applied (and optionally R2), the application is CLEAN: every item A1, A2 and B–I and every correction C1–C4 is in place exactly as decided, with no added acoustic or numeric choice.

## Files read
- `/home/user/makroof/docs/review/phase-07c-2b/43-decider-m3h-rebuttal3.md` L260–501
- `/home/user/makroof/docs/review/phase-07c-2b/44-interrogator-on-file43.md`
- `/home/user/makroof/docs/phases/phase-07e.md`, `/home/user/makroof/docs/phases/phase-07e-b.md` (full)
- `/home/user/makroof/docs/BUILD_PLAN.md` L30–49, L535–538; grep for AX42–AX44 (L167–169), B11 (L406), B15 (L410)
- `/home/user/makroof/docs/phases/phase-07d.md` L88–99; `/home/user/makroof/docs/phases/phase-08-3.md` L50–84, L145–151; `/home/user/makroof/docs/phases/phase-08-4.md` L1–3; `/home/user/makroof/docs/phases/phase-07c-2b.md` L186–194; `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` L20–24, L124–133
- `/home/user/makroof/docs/corpus/SOURCE_COMMIT`
- Greps across `/home/user/makroof/docs/` (review/ excluded) for "24-m3h", "file 24", "M3-H", "pending"/"awaiting Maisara", "07e", "M3-8"
