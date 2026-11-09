# D1 (dry run) — interrogator, decision mode, round 1 (2026-11-09)

Method: the registered `interrogator` agent, told to re-read `.claude/agents/interrogator.md` (rewritten this session), given the convening round, the nine seat reports, the dossier and the decision. Verbatim.

---

# Interrogation of D1 (dry run) — decision mode

Corpus revision: `docs/corpus/SOURCE_COMMIT` = `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (14 files, all ten books, no extra files).

Target: `docs/review/board-smoke/hrtf-head/4-decider-decision.md` (D1, (a′) SADIE II D1 / KU100, bounded embed, dataset-agnostic header). Authorities used: the nine seat reports `2-seat1…9-*.md`, the dossier `3-researcher-dossier.md`, `docs/board/README.md` "Convening table", `.claude/agents/decider.md` §5, `docs/BUILD_PLAN.md` §0/§4/§5, `docs/phases/phase-08.md`, `docs/THIRD_PARTY.md`, and the corpus in `docs/corpus/`.

## 1. Convening check — PASS

Nine rows, all nine **convened** (three "narrowly"); none answered `NOT MY MATTER`; no row is marked *not required*, so there is nothing to test against the README table. Seat 4 is the README owner ("HRTF dataset choice and licence; headphone compensation"); Seats 1, 5, 6, 7 (PRD-priority seats) are convened with the reason stated. Nothing wrongly marked.

## 2. Tension-map check — faithful, one misattributed cell in a non-option row

Rebuilt every cell from the seats' own §3/§4:

| Option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum (my recount) |
|---|---|---|---|---|---|---|---|---|---|---|---|
| (a) | 1/1 | 1/1 | 1/1 | 1/2 | 2/2 | 0/1 | 1/2 | 0/1 | 1/1 | 2 | 20 ✓ |
| (b) | 2/2 | 1/1 | 1/1 | 1/2 | 2/2 | 1/1 | 1/2 | 1/2 | 1/1 | 2 | 25 ✓ |
| (c) | 2/2 | 2/2 | 2/2 | 2/2 | 1/1 | 1/1 | 1*/2 | 1/2 | 2/2 | 2 (3*) | 30 ✓ |
| (d) | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/1 | 1†/2 | 0/1 | 1/1 | 2 (3†) | 17 ✓ |
| (a′) | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/1 | 1/1 | 0/1 | 1/1 | 1 | 16 ✓ |

All option cells and one-line reasons match the seats' words. Footnotes (Seat 4 near-field 1 for all; Seat 5 round-trip 1 for all; Seat 7 naming 2 for any option) are the seats' own and are correctly carried. The `(rfc)` cells of (a′) follow from the stated conditions: Seat 3 §3(i) and §6(vi); Seat 4 §6 "(a) 2→1 … otherwise record in `THIRD_PARTY.md`"; Seat 5 §6 "(a)/(b) 2→1: either the grid is ≤ ~3000 directions, or … float16 … and the embed is a build-step object"; Seat 7 §6 "later 2→1 … an AX row" and "Naming 2→0". Seat 7's conditional 3 on (c) ("1 if its terms are clear, 3 if …") is undetermined rather than 1; recording it as 1* changes nothing because (c) loses at steps 3–5 regardless.

**One defect.** In the row "Any option without the condition (later)" the S6 cell "–/1" is not Seat 6's rating of an option without the condition: Seat 6's "1" is "Condition without my clause: 1 (an About box hard-codes a head)" — Seat 6 gave no number for options without the condition (only "without it, `src/sim` rework"). Seat 5 likewise gave no number there (the "–/0" is a reading). The row's conclusion — the condition is part of every survivor — rests on Seats 1 and 9, who did say 3 ("not met: 3 for every option"; "Any head without the condition: 3"), so no option cell or ordering step moves. Correction, not a misread of a rated cell.

## 3. Future-debt check — all nine rows present; three rows need restating

Every `later ≥ 1` on (a′) (all nine seats) has a register row with commitment, undo cost and evidence timing. Defects:

- **S4 row**: "evidence arrives: … the compensation phase"; "repaid when: … a compensation listening check passes". No headphone-compensation phase or test exists in `BUILD_PLAN.md` §0 (table ends at 13), §4 (Phases 00–13), §5 (only B4, B9) or any phase file (`phase-08.md` "Out of scope" names only near-field correction); the PRD is silent on headphone EQ (the decider's own digest). By the letter of step 3 this row names a phase that does not exist (INCONSISTENT with the plan). By substance the debt is owned, faithful to Seat 4 §6 ("compensation, when added, will be cross-campaign and must pass a colouration listening check") and flagged "when added" — an open debt with no repayment slot, like S7's "never fully". I treat it as a restatement, not a dropped debt.
- **S5 row**: undo = "parameter change". That holds only until the Phase 08 goldens are frozen (Seat 3 §4: a swap re-creates three goldens) and before first paid release; after release the decision's own item 7 ("data behind a released `hrtfId` is never replaced … new id … old data retained, with the contract bump") makes the undo a second embedded set (Seat 7 §4: "binary size doubles"). Hidden premise H1; the row must state its window.
- **S1/S3/S6/S8/S9 rows** cite "B9 (alongside 15)" and "B4 (18)". B4 and B9 exist in §5; "15" and "18" are the backlog's own phase labels and do not exist in §0/§4. Cite by backlog id.
- Seat 9's half of its 3→0 condition, "record the head id in every preset's validation log", is in the register ("B9 logs carry the head id") but not in the decision's wording items 1–9 or the attached-conditions paragraph.

## 4. Ordering check — correct; winner unchanged

- **Step 1 bounds.** (d) dropped: `phase-08.md` scope 1 reads verbatim "Don't ship data under an unclear licence"; CLAUDE.md "The converted embedded HRTF is the one exception, once its licence is confirmed"; the dossier itself leaves the TH Köln licence unresolved (F6 BY-SA 3.0 vs F7 CC BY 3.0 vs F8 none; N1). decider.md §1 counts CLAUDE.md rules among hard constraints (its own example is "the contract rules"), so the bound is real even though scope 1 is plan text. (c) kept: both MIT texts permit commercial use (F5); the two wordings differ on proviso vs request, not on permission — the asymmetry with (d) is justified.
- **Step 2 veto.** No survivor carries an unconditional 3 ✓; the condition is in every survivor (S1, S9 = 3 without it) ✓.
- **Step 3 worst-off.** (a), (b), (c) all max 2 ✓ (both columns counted).
- **Step 4 compose.** (a′) max 1: each lowering follows a seat's stated condition (above); decimation keeps the −81° row (Seat 2's concern) and stays under Seat 3's ≤10° bound; (b) cannot be composed (Seat 1 §6 needs an ABX result; Seat 4 §6 needs R8 evidence, N3); (c) cannot (Seat 7's later 2 has no lowering condition; five seats at 2/2) ✓. One composed variant ✓.
- **Step 5 sum.** 16 < 20 < 25 < 30 ✓. **Step 6** consistent with Seats 1, 3, 4, 6, 8, 9's undo statements ✓.

## 5. Load-bearing claims — all CORRECT or NOT CHECKABLE-and-not-load-bearing, one IMPRECISE citation

Computations redone (details in the ledger): D1-L5 103.7 / 31.8 / 8.4 MB ✓; D1-L7 −50.2° / −38.7° / −82.9°, 17.9 %, 0.6 % ✓; D1-L8 0.656 / 0.637 ms ✓ against Blauert Ch. 2 lines 222, 233, 237; D1-L13 8.9 µs/° ✓ from Zotter & Frank Eq. (4.51) with R = 0.0875 m, c = 343 m/s. D1-L9's "Vorländer §16.1.2" is a wrong section: the dummy-head front–back passage is §6.3.2 "Artificial heads" (line 1967); §16.1.2 is "Individual filters" (line 4010) and says individual filters cut errors "particularly above 6 kHz". Substance right, reference wrong (the brief, the dossier F32 and Seats 6, 8, 9 carry the same slip; Seat 1 cited §6.3.2 correctly).

## 6. Inference and hidden premises

The choice follows from the map and the bound. Three unstated premises sit in the composed variant's wording, none of which changes the winner:

- **H1** (S5 undo = parameter change) — see §3.
- **H2** (item 5, C-2): "for this already-equalised set the computed curve is expected near flat … so the EQ is applied exactly once". True only if the converter's diffuse-field average is the same kind of average York used; F18 gives neither York's weighting nor its bands, and whether the shipped SOFA is the DF-equalised variant is N2. NOT CHECKABLE in the corpus; a pin-time measurement with a stated flatness tolerance and a stated rule (apply vs record only) is what makes Seat 1's condition "applies DF-EQ exactly once" checkable.
- **H3** (items 4 + 5): an unweighted average over the stored ≤ ~3000 directions, which by item 4 keeps the full 360-point 0°-elevation ring of a grid that is already non-uniform (F11), is not a *diffuse-field* average. The corpus defines diffuse-field equalisation as the average over all directions = 1 (Blauert Ch. 4 "Theile's solution", line 525; Begault Ch. 4 "Equalization of HRTFs", line 1489, "random incidence"). The condition (solid-angle weighting) is unstated for (a′); Seat 2 §6 named exactly this cure (Voronoi weighting) but only for (c), and the decider carried it only into reversal 1. This also touches the tail-coherence target (phase-08 scope 5 "diffuse-field average of the interaural cross-spectrum") and therefore the ±0.1 AC. Not load-bearing for choosing among (a)–(d) — every option's converter faces it — so it is a wording correction, not a fall.

## 7. Knowledge inventory

- **K7 "known"** overstates: F18's last sentence says whether the shipped SOFA is the DF-EQ'd version "is not stated" (N2). Under-informed; the decision survives because item 1 reads `GLOBAL_Comment` at pin time and item 5 computes from the set, but only under H2/H3.
- **Missing fact** the composition depends on: York's diffuse-field averaging method (weighting, bands) and the resulting flatness of the converter's weighted average on the pinned file. Research gap for the researcher / pin-time measurement; not filled here.
- K5 known with C3 (8802 vs 9201 points) and K1 with a lawyer's call pending are honestly flagged. K8, K10 correctly declared not load-bearing.
- Seat 4's HpTF question (does SADIE II publish KU100 HpTFs) was not answered by the dossier; the decider's "as far as read" is honest and both branches of Seat 4's condition give 1.

## 8. Strongest objection

The decider's (Seat 5, size) holds as stated: two independent mechanisms named by the seat, Seat 3's grid bound, and reversal 3 declared. A **stronger** one, supported by Seat 1 §3/§6 and the dossier: Seat 1 rated (a) 1 on the explicit risk "a second DF-EQ on already-equalised data is a tone-colour fault" and conditioned acceptance on DF-EQ "exactly once"; F18 now establishes the set *is* already DF-equalised, and H3 shows the composed variant's own decimation makes a non-flat computed curve likely unless weighted. It is on the PRD-priority seat for what the user hears. It is answerable from the seats' words (Seat 2's weighting; Seat 1's header-records-state) and so does not overturn the decision, but it must be answered in the wording.

The decider's C-1 premise (a low-frequency/cross-correlation ITD exceeds an onset ITD) is supported by corpus the decider did not cite: Roginska & Geluso Ch. 1, line 959: maximum ITD ≈ 650 µs, "750 µs for low-frequency sounds" (Kuhn 1977).

## 9. Outcome: **SURVIVES WITH CORRECTIONS**

No seat unheard; every option cell faithful; every debt row present; ordering correct; every load-bearing claim CORRECT or NOT CHECKABLE-and-not-load-bearing. With the restatements below the decision still follows: (d) out at bounds, (a′) max 1 / sum 16 against (a) 20, (b) 25, (c) 30; no cell changes.

Exact restatements required:
1. D1-L9 and the summary table: "Vorländer §6.3.2 (line 1967)" in place of "§16.1.2".
2. Map row "Any option without the condition (later)": S6 and S5 cells → "–" (unrated); the row stands on S1 = 3 and S9 = 3.
3. Register S4: replace "the compensation phase" / "a compensation listening check" with "no headphone-compensation phase or test exists in the plan (PRD silent); open debt without a repayment slot until one is added" — the decider does not add it.
4. Register S5: "parameter change *before the Phase 08 goldens are frozen and before first release*; after release, item 7 applies (generic-v2, old data retained, contract bump)".
5. Register rows: cite "B4 (§5)" and "B9 (§5)"; drop the phase numbers 15/18, which are not in §0/§4.
6. Items 4–5: state that the DF-EQ curve and the tail-coherence target are solid-angle (Voronoi) weighted over the stored subset, and state the flatness tolerance on the computed curve and what the converter does when it is exceeded, so Seat 1's "exactly once" and the ±0.1 coherence AC are checkable.
7. K7 → under-informed (N2), resolved at pin time by item 1.
8. Add Seat 9's "record the head id in every preset's validation log" to the plan wording.
9. Attached Seat 9 protocol: "'thin' is never the head" → "head shadow is not a low-frequency effect; low-frequency loss can still come from the HRIR window or LF extension" (Begault Ch. 4 "Methods for Data Reduction", line 1539; F18).

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| D1 | convening | nine rows, all convened, none `NOT MY MATTER`, none *not required* | PASS | `1-decider-convene.md` §2 vs README "Convening table" (Seat 4 row "HRTF dataset choice and licence") | — | — |
| D1 | map | (a)–(d) × S1–S9 ratings and reasons | FAITHFUL | recounted from `2-seat1…9`: sums 20/25/30/17, max 2/2/2(3*)/2(3†) | — | — |
| D1 | map | row "Any option without the condition", S6 "–/1", S5 "–/0" | IMPRECISE (misattributed) | Seat 6 §4: "Condition without my clause: 1"; neither seat rated options without the condition; conclusion holds on S1/S9 = 3 | corrections | Q4 |
| D1 | map | (a′) rfc cells S3, S4, S5, S7 | FAITHFUL | Seat 3 §3(i), §6(vi); Seat 4 §6 "(a) 2→1 … otherwise record"; Seat 5 §6 "≤ ~3000 … build-step object"; Seat 7 §6 "AX row", "Naming 2→0" | — | — |
| D1 | map | S7 (c) "1*" with conditional 3 recorded, not applied | ACCEPTABLE | Seat 7 §3 "1 if clear, 3 if unclear"; (c) loses at steps 3–5 regardless | — | — |
| D1 | debt | nine rows for nine `later ≥ 1` cells on (a′) | PASS | register vs (a′) row | — | — |
| D1 | debt | S4 "the compensation phase" / "compensation listening check" | INCONSISTENT with plan (no such phase/test); debt itself owned | BUILD_PLAN §0 ends at 13, §4 Phases 00–13, §5 B4/B9 only; phase-08 "Out of scope"; PRD silent | corrections (restate as open debt) | Q2 |
| D1 | debt | S5 undo "parameter change" (hidden premise H1) | IMPRECISE | decision item 7; Seat 7 §4 "binary size doubles"; Seat 3 §4 "re-created goldens" | corrections | Q3 |
| D1 | debt | "B9 (alongside 15)", "B4 (18)" | IMPRECISE | BUILD_PLAN §5 rows B4 "18 (SOFA)", B9 "alongside 15"; no Phase 14–18 in §0/§4 | corrections | — |
| D1 | debt | Seat 9 "head id in every preset's validation log" absent from wording items 1–9 | IMPRECISE (omission) | Seat 9 §6 "Any head 3→0 later: … record the head id" | corrections | — |
| D1 | ordering 1 | (d) dropped on unclear licence | CORRECT bound | `phase-08.md` scope 1 "Don't ship data under an unclear licence"; CLAUDE.md "once its licence is confirmed"; dossier N1/C1 | — | — |
| D1 | ordering 2–6 | veto, worst-off, compose, sum, reversibility | CORRECT | tie at max 2; (a′) max 1 sum 16; (b)/(c) not composable per Seat 1 §6, Seat 4 §6, Seat 7 §6 | — | — |
| D1 | D1-L5 | 104 / 31.8 / 8.4 MB | CORRECT (derived) | taps 235+256+470+512 = 1473; ×2 ears ×4 B = 11 784 B; ×8802 = 103.7 MB; ×2702 = 31.8 MB; ×710 = 8.4 MB (phase-08 scope 2) | — | — |
| D1 | D1-L6 | HRTF distance-independent > 1 m; all sets > 1 m | CORRECT | Vorländer §9.5 (line 2648), Fig. 9.7; F17 | — | — |
| D1 | D1-L7 | −atan(2h/d_h); caps 17.9 %, 0.6 % | CORRECT | Begault Ch. 4 "HRTF Measurements" (line 2137): 1.4 m, 44.1 kHz, 710, −40…+90°; atan 1.2 = 50.2°, atan 0.8 = 38.7°, atan 8 = 82.9°; (1−sin 40°)/2 = 0.179; (1−sin 81°)/2 = 0.006 | — | — |
| D1 | D1-L8 | 650 µs; 0.656 / 0.637 ms | CORRECT | Blauert Ch. 2 line 233 ΔS = (D/2)(φ+sin φ), line 237 Fig. 2.30 ≈ 650 µs, line 222 sphere 17.5 cm; 0.0875×2.5708/343 = 0.656 ms; 0.085×2.5708/343 = 0.637 ms; c = 343 (Zotter & Frank notation) | — | — |
| D1 | D1-L9 | corpus citations for torso/shoulders/dummy-head confusion | IMPRECISE (wrong section) | Rumsey §3.2.4 line 952 ✓; Roginska Ch. 4 line 1551 ✓; Vorländer passage is §6.3.2 line 1967, not §16.1.2 (line 4010, "Individual filters") | corrections | Q4 |
| D1 | D1-L11 | IEM BinauralDecoder uses Cologne KU100 | CORRECT | Zotter & Frank §4.12.3 line 1654 | — | — |
| D1 | D1-L13 | ITD slope 8.9 µs/°; minimum-phase interpolation | CORRECT | Zotter & Frank Eq. (4.51), R = 0.0875 m: ITD(θ) = (R/c)(θ+sin θ), slope at 0 = 2R/c = 0.510 ms/rad = 8.9 µs/°; Begault Ch. 4 "Problems with Interpolation Algorithms" lines 1593–1597. The 1 dB half of AC 4 has no corpus bound: measured, not claimed | — | — |
| D1 | K13 / item 5 basis | DF-EQ rationale | CORRECT | Blauert Ch. 4 "Theile's solution" line 525 (average over all directions = 1); Begault line 1489; Rumsey §3.2.4 lines 954, 957 | — | — |
| D1 | hidden premise H2 (item 5, C-2) | computed DF curve near flat on already-equalised set → "applied exactly once" | NOT CHECKABLE (York's method not in dossier; N2) | F18 states no weighting/bands; holds only if the same kind of average | research gap (pin time); not load-bearing for the head choice | Q1, Q5 |
| D1 | hidden premise H3 (items 4+5) | average over stored non-uniform subset = diffuse-field average | CONDITIONS VIOLATED unless solid-angle weighted (condition unstated) | Blauert line 525 "all directions"; Begault line 1489 "random incidence"; F11 non-uniform grid; item 4 keeps the 360-point 0° ring; Seat 2 §6 Voronoi cure given for (c) only | not load-bearing for the choice; wording correction required | Q1 |
| D1 | K7 | "known" | IMPRECISE (under-informed) | F18: shipped SOFA variant "not stated"; N2 | corrections | Q5 |
| D1 | C-1 premise | LF/cross-correlation ITD > onset ITD | CORRECT (uncited by decider) | Roginska Ch. 1 line 959: ≈ 650 µs, "750 µs for low-frequency sounds" (Kuhn 1977); Blauert Ch. 2 line 226 | — | — |
| D1 | register S1 | "30–50 % expected reversals" | CORRECT (Seat 1's words, corpus-consistent) | Begault Table 2.3 (lines 958–959): Wenzel 1993 31 %, Begault & Wenzel 1993 37 %; Fig. 2.32 mean 47 % | — | — |
| D1 | attached Seat 9 protocol | "'thin' is never the head" | IMPRECISE | Rumsey line 664 head "not [a barrier] at LF", Vorländer Fig. 6.6 support the shadow part; Begault line 1539 windowing "may lose low-frequency information"; F18 LF < 200 Hz modelled | corrections | — |
| D1 | seat claim (Seat 3 §5) | KU100 onset ITD ≈ 0.75–0.85 ms from Fig. 4.25b | NOT CHECKABLE; conflicts with F23 (0.625 ms) | Zotter & Frank line 1564: earliest value not printed (Seat 4 §5 agrees); not relied on (K8 under-informed) | — | — |
| D1 | strongest objection | Seat 5 size | HOLDS; stronger: Seat 1 "exactly once" × F18 × H3 | Seat 1 §3 "a second DF-EQ on already-equalised data is a tone-colour fault"; answerable from Seat 2 §6 and Seat 1 §6 | — | Q1 |

## Questions for the decider (rebuttal round)

1. **Items 4–5 (H2/H3).** Is the converter's diffuse-field average — for the DF-EQ curve and for the tail-coherence target — solid-angle (Voronoi) weighted over the stored ≤ ~3000-direction subset that keeps the full 0°-elevation ring? And what flatness tolerance on the computed curve decides whether it is applied to the already-DF-equalised SADIE II data or only recorded in the header? Falsifiable against Blauert Ch. 4 line 525 (average over all directions = 1) and F11/F18.
2. **Register S4.** Which phase or §5 item is "the compensation phase" in which the cross-campaign compensation debt is repaid? If none exists in `BUILD_PLAN.md` §0/§4/§5 or the phase files, restate the row as an open debt without a repayment slot.
3. **Register S5.** After the Phase 08 goldens are frozen, and after first paid release under item 7's AX row, is re-running the converter with a different subset or storage still "a parameter change"? State the window in which the undo cost holds.
4. **D1-L9 and the map.** Confirm the dummy-head front–back passage is Vorländer §6.3.2 (line 1967), not §16.1.2; and confirm Seat 6 never rated "options without the condition" (its "1" is "Condition without my clause"), so that cell becomes "–".
5. **K7.** Given F18's last sentence and N2, is K7 "known" or "under-informed", and does any item of the decision change if the pinned `D1_HRIR_SOFA.zip` turns out to hold raw rather than diffuse-field-equalised HRIRs?
