

# 33: Decider on M3-H, rebuttal round (answer to interrogator file 31). Phase 07c-2b

Read-only. The orchestrator saves this as `/home/user/makroof/docs/review/phase-07c-2b/33-decider-m3h-rebuttal.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. The PRD digest is unchanged from file 28 L10–21.

**State: REVISED. The decision is still H4+G. It now carries the 07e/07e-b split, the merged scope-4 text and an AC clause with an end date. It goes back to the interrogator.**

**What changed and why the winner did not:**
- Seat 3 moves to 0/0 because C3-a is adopted.
- Seat 7 re-rated the larger 07e at 1/1 under both H4+G and H3+G.
- So H4+G and H3+G both sum to **7** and tie again.
- Reversibility breaks the tie, on a corrected premise. The 07d split and the extra 07e work are common to both options. The one cost only H3+G carries is the hold on 08-1 and 08-2 from day one. Seat 7 says that hold "is spent at the start and cannot be recovered" (32-seat7 §4).
- Seat 2 says 07e is two S sessions, not one, and requires every gate to name 07e-b. The split is therefore planned now.

## 0. Answers to file 31

| item | verdict in file 31 | answer | state |
|---|---|---|---|
| **Q1 / M3H-15**: S7 cell on the larger 07e; Lead's size | TENSION MISREAD; the reversal condition FALLS | **Accepted.** Seat 7 re-rated H4+G at **1/1** and H3+G at **1/1**. It adds that on its measures H3+G is "strictly worse than H4+G, not tied with it" (32-seat7 §3). That statement enters at step 6, not as a re-rating. Seat 2: "two S sessions [Hyp]". The split is planned now as 07e (scopes 1–3, AC1, report) and 07e-b (scopes 4–5, DoD), with every gate on 07e-b (32-seat2 §2). The reversal condition is restated in §4 so that it no longer assumes the prints apply only under H4+G. | corrected |
| **Q2**: S3 with C3-a | TENSION MISREAD | **Accepted.** S3 is 0/0 on every pre-freeze option that carries C3-a (29-seat3 §6). Sums: H4+G 7, H3+G 7 (it carries the same 07e, see Q1), H3 8. **Reversibility decides.** | corrected |
| **Q3 / M3H-14**: premise that the debt is conditional | IMPRECISE | **Accepted.** Item D holds scope 8 on 07e-b `done` whether or not a fix is ruled. The 07d/07d-b split is "near-certain and not conditional on a fix" (32-seat7 §4), and Seat 5 accepts the correction (32-seat5 §4). Both say the split is common to H3+G and H4+G. Only two debts are conditional on a fix, and only H4+G has them: the re-hear of 08-3's provisional verdicts (29-seat4), and the item 15 wait on a long fix. Step 6 is restated (§3). | corrected |
| **Q4**: breach criterion in scope 4 | INCONSISTENT | **Accepted.** "Unexplained by the engine's model" was my own wording, wrongly given to Seat 2. It is replaced by one scope-4 text merged from Seat 2 (32-seat2 §3–4) and Seat 9 (32-seat9 §2). The two seats' differences are reconciled in §5, Item A2, Scope 1 ("Reconciliation notes"). Under the merged text a model feature is a cause, never an explanation. The coherent-radiation question is **answered in the text** ("no"), not left open before the verdicts. | corrected |
| **Q5**: AC board clause | unattributed addition | **Accepted. It was mine; no seat wrote it.** It is replaced by Seat 5's sentence (32-seat5 §1), applied until the end date that Seat 7's condition requires (32-seat7 §6, second branch). After that date the rule is update-with-reason. See §2 for the reconciliation and for what each seat's cell rests on. | corrected |
| (c) "uncertainty stated" | unfaithful | **"Under 0.5 dB" is restored** in Seat 9's exact text (32-seat9 §2). Seat 2's receiver limit is added: the tracer reference is used only where the receiver is ≥ 0.5 m from every face (32-seat2 §2). | corrected |
| S5 and S7 undo cells | IMPRECISE | S5: "not stated by Seat 5 for H4+G" (its "one /fix-plan" belongs to H2-cg). S7: in Seat 7's own words (32-seat7 §4). See §4. | corrected |
| NFR-1 line | IMPRECISE | It now names the provisional re-hear (§4, acceptance check). | corrected |
| Item H | INCONSISTENT | It now also removes "M3-H answer, " from the status cell of §0 row 07c-2b. | corrected |
| Per-distance print relabelled | minor | Seat 1's framing is restored: a jump "the user would meet while dragging a source" (29-seat1 §6). | corrected |
| Seat 6 clamp hand-off softer than the seat | minor | Seat 6's words are restored: "no ruling is ever answered by moving the AX6 clamp" (29-seat6 §6). | corrected |
| "None raises a cell" | IMPRECISE | Withdrawn as a blanket claim. §2 gives the stated basis for each seat's cell. | corrected |

## 1. Knowledge inventory (only changes from file 30 §1; K1–K12 stand)

| K | what must be known | source | status |
|---|---|---|---|
| K13 | Size of the larger 07e: two S sessions. The proposed split is 07e (scopes 1–3, AC1, report) and 07e-b (scopes 4–5, DoD) | 32-seat2 §2 [Hyp, Lead's own cost]; 32-seat7 §3 "about 2 founder sessions [Hyp]" | known (seat own-cost claims) |
| K14 | Tracer: the receiver is a 0.5 m sphere; bins are gated at k ≥ 684, which gives 3σ ≈ 0.5 dB with σ = 4.34/√k; N0 = ceil(254 V) | from the code, re-checked: `tools/acoustics/tracer.py` L21, L28, L43–44. Working: √684 = 26.15, 4.34/26.15 = 0.166 dB, 3σ = 0.498 dB. For layout4, V = 20·30·10 = 6 000 m³, so N0 ≈ 1.52 M | known |
| K15 | `--diagnostics` already prints every scope-3 counter, so the work needs no CLI edit | 32-seat2 §2, from the code (`Cli.cpp` L597–654; not re-opened by me) | known (Seat 2's own-cost claim from the code) |
| K16 | AX44's "GA limit" text names the receiver side: "the GA tail level ignores the near-wall pressure rise" | BUILD_PLAN L167 (re-read) | known |
| K17 | Seat 5's per-run pytest condition: ≥ 1 placement; the full sweep and the tracer are not in the per-run job | 32-seat5 §6 | known |

No load-bearing gap remains. One cell is read from conditions (S5 on the end-dated clause, §2), so confidence stays **medium**.

## 2. Tension map (now / later)

The option rated is the **decided variant**: the home, plus all adopted texts, the 07e/07e-b split, the merged scope 4, and the AC clause with its end date. **That 07e is the same under every home** (32-seat7 §1; 32-seat5 §4; 32-seat9 §3). H3 and H3+G are therefore rated with the same 07e.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| H1 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 2 | 18 |
| H2-c | 0/2 | 1/2 | 0/0 | 0/2 | 1/2 | 0/1 | 1/2 | 0/0 | 0/1 | 2 | 15 |
| H2-cg | 0/1 | 1/1 | 0/0 | 0/2 | 1/1 | 0/0 | 1/1 | 0/0 | 0/0 | 2 | 9 |
| H3 | 0/1 | 1/1 | 0/0 | 1/0 | 1/1 | 0/0 | 1/1 † | 0/0 | 0/0 | 1 | 8 |
| H3+G | 0/1 | 1/1 | 0/0 | 1/0 | 1/0 | 0/0 | **1/1** | 0/0 | 0/0 | 1 | **7** |
| H4 | 0/1 | 1/1 | 0/0 | 0/1 | 0/2 | 0/1 | 1/1 | 0/0 | 0/0 | 2 | 9 |
| **H4+G (decided variant)** | 0/1 | **1/1** | **0/0** | 0/1 | 0/1 ‡ | 0/0 | **1/1** | 0/0 | 0/0 | **1** | **7** |

† Seat 7 did not re-rate H3 with the larger 07e. The cell is its 29-seat7 rating, marked. It is not load-bearing: every other cell of H3 equals H3+G's except S5 (later 1 against 0), so H3 sums at least 8 under any S7 rating of 1 or more.
‡ (read from conditions) for the end-dated clause; see the basis below.

**Basis of each cell on the decided variant, in the seats' words:**
- **S1 0/1:** "a ruled fix fires M3-8 … the fix's cost, not the home's" (29-seat1 §4). It holds on Seat 1's "every gated option" condition: the audibility clause and the per-distance print are both adopted (29-seat1 §6).
- **S2 1/1:** "confirmed" for H4+G and H3+G. "Two sessions stay inside my tolerance." The later cell is **conditional**: "They hold only if the gates name 07e-b … If they do not, my later cell under H4+G goes to 2" (32-seat2 §5). Met: every gate in §5 names 07e-b.
- **S3 0/0:** "C3-a: takes every pre-freeze option from 0/1 to 0/0" (29-seat3 §6). C3-a is adopted verbatim in 07e scope 3 and 07e-b scope 2.
- **S4 0/1 (H4+G) and 1/0 (H3, H3+G):** from the 29-seat4 table. H4+G: "item 15 waits … checklist … may also be heard on the pre-fix engine". H3 and H3+G: they hold 08-1 and 08-2 "for no cue reason". Seat 4's item-7 text is adopted. The only change is "07e" to "07e-b", which Seat 2's gate condition requires. Seat 4 says the text "does not change my cells". *Premise not re-asked:* Seat 4 inferred that 07e "should be done before 08-3 reaches item 15". 07e plus 07e-b is two S sessions, run against 08-1 and 08-2 (M each) and 08-3's items 1–14. Seat 4's later 1 already counts "if 07e rules a long fix phase, item 15 waits". I have not re-rated it.
- **S5 0/1 (H4+G):** "0, confirmed" now and "1, confirmed" later (32-seat5 §3–4). The cell rests on Seat 5's §6 condition: the per-run pytest re-renders ≥ 1 placement only, with no tracer and no full sweep. That is met (Item A1 AC1). **Read from conditions for the end date:** Seat 5 rated with its sentence applying "while 07e's ruling stands". I end it at 07e-b plus fix `done` (Seat 7). Seat 5's stated conditions (§6) do not cover that end date, and they are all met. Seat 5's §1 argument against bare update-with-reason is carried under the strongest objection. **H3+G 1/0:** "1, unchanged" and "0, confirmed".
- **S6 0/0:** G1 is a Depends-on (29-seat6 §4). The medium_room cases are its own hand-off.
- **S7 1/1, both options:** 32-seat7 §3–4. H4+G later "holds at 1 only with the condition in §6". The condition used is §6's second branch: "keep the board clause only until 07e's ruling and any fix phase are `done`, then fall back to update-with-reason". It is met (AC1).
- **S8 0/0:** 29-seat8.
- **S9 0/0:** "my two texts adopted: 0 (confirmed) / 0 (confirmed)"; "H3+G … same as H4+G" (32-seat9 §3). Both texts are adopted. The band-span difference with Seat 2 is reconciled in Item A2 scope 1 without breaking Seat 9's §5 conditions.

**Reconciliation, Seat 5's sentence against Seat 7's end date (task item 3):**
- Seat 7 offers two branches (32-seat7 §6). The first (bare update-with-reason) is the text Seat 5 rejects as the whole rule (32-seat5 §1). The second keeps a board clause until the ruling and any fix are done.
- **Adopted:**
  - Seat 5's sentence **verbatim** from the commit of 07e's JSON until **07e-b `done` and the fix phase it names, if any, `done`**.
  - After that, update-with-reason, in the changing phase's PR, with a §6 row and never regenerated just to pass. These are Seat 5's own mechanics minus the board look, and Seat 5's 29-seat5 §4 wording.
  - One clause of mine, attributed as mine: the stated reason must say whether any discrete field changed. It adds no board loop, so Seat 7's branch is still literally update-with-reason. It makes the discrete-field case that Seat 5 named visible to the contracted engineer, which is Seat 5's own premortem reader.
- **Edit to Seat 5's sentence:** "07e's ruling" becomes "07e's findings and 07e-b's ruling", because the split moves the ruling to 07e-b. This is a split edit, not a change of substance.

## 3. Minimum-tension working (redone)

1. **Bounds.** Unchanged from file 30: none is dropped. The merged scope 4 keeps NFR-8 binding. A model feature is a cause, never an explanation, and no `src/sim` change happens in 07e or 07e-b.
2. **Veto.** No cell is 3. Seat 6's conditional veto (clamp moved after release) is excluded by the Out-of-scope text and Seat 6's restored sentence.
3. **Worst-off seat.**
   - Max 2: H1, H2-c, H2-cg (S4), H4 (S5). These are dropped.
   - Max 1: H3, H3+G, H4+G go forward.
4. **Compose.** No variant brings the max to 0:
   - S1 has no condition that lowers its later 1.
   - S2's 1/1 is "confirmed" with no lower condition.
   - S7's 1/1 has none either.
   - S5's later 1 is the split, which is common and not conditional (Q3).
   - The split, the merged scope 4 and the AC clause are adopted inside the variant because they are **conditions that keep cells where they are**: S2 later 1 (gates on 07e-b), S9 later 0 (both texts), S7 later 1 (end date), S5 now 0 (pytest scope). They are not a composition that lowers the max.
5. **Sum.** H4+G = 1+2+0+1+1+0+2+0+0 = **7**. H3+G = 1+2+0+1+1+0+2+0+0 = **7**. H3 = 8. **Tie: H4+G against H3+G.**
6. **Reversibility (restated, with no premise that the prints apply only under H4+G).**
   - **Common to both:**
     - the larger 07e and 07e-b (32-seat7 §1);
     - the 07d/07d-b split, about 1 session, "not conditional on a fix" (32-seat7 §4; 32-seat5 §4);
     - the JSON-pin board looks up to the end date.
   - **Only H3+G:** 08-1 and 08-2 (two M phases) wait in series from day one, behind 07c-2b's person-dependent ABX dates and a 07e that is now twice as long. Seat 7: "spent at the start and cannot be recovered, which is why H3+G undoes worse" (32-seat7 §4). The cost is certain, and it is S4 now 1 and S5 now 1.
   - **Only H4+G:** two debts, both **conditional on a ruled fix**:
     - the re-hear of 08-3 checklist verdicts recorded provisional (S4 later 1);
     - item 15 waiting on a long fix.
   - **Undo cost of H4+G (Seat 7's words):**
     - "one /fix-plan round, about half a session" before 07e starts;
     - "still under 1 session" after the JSON and pytest are committed.
     - Moving to H3+G after 08-1 and 08-2 have started: "nothing has to be undone … nothing is lost".
   - **H4+G is cheaper to undo.**
7. **Decide: H4+G (decided variant).** The texts are in §5.
   - **Confidence: medium.** No acoustic claim is load-bearing, and every product claim has an id. But one cell is read from conditions (S5, end date), the session counts are [Hyp], and Seat 4's timing premise is [Inferred] and was not re-asked.

## 4. DECISION M3-H (revised): H4+G with a planned split. `phase-07e` measures; `phase-07e-b` rules. Report only. Lead Seat 2

**The phases:**
- 07e (S) runs scopes 1–3, AC1 and the report.
- 07e-b (S) runs the board ruling, any fix-phase file, and the Definition of done.
- **Every gate names 07e-b `done`, and the fix phase it rules, if any:** 08-4 Depends on (G1), 08-3 item 15's stimulus build, 07d scope 8 (G2), and the §0 rows.
- 08-1, 08-2, 08-3's other items and 07d scopes 1–7 run in parallel.

**Load-bearing claims:**
- **D-L1 to D-L4:** as in file 30. All were rated CORRECT in file 31.
- **D-L5 [seats]:** the cells in §2. Sums: H4+G 7, H3+G 7, H3 8 (working in §3 step 5).
- **D-L7 [seat, own cost]:** 07e is two S sessions. The split is 07e (scopes 1–3, AC1, report) and 07e-b (scopes 4–5, DoD). S2's later 1 holds only if the gates name 07e-b (32-seat2 §2, §5).
- **D-L8 [code, re-checked]:** the tracer's receiver is a 0.5 m sphere and its bins are gated at k ≥ 684 (3σ ≈ 0.498 dB). It is valid only where the receiver is ≥ 0.5 m from every face. It is therefore not a reference for (a)'s listener (tracer.py L21, L28, L43–44; 32-seat2 §2).
- **D-L9 [seats]:** the split and the JSON-pin debt are common to H3+G and H4+G. The 08-1/08-2 hold is H3+G's alone and cannot be recovered (32-seat7 §4; 32-seat5 §4).
- **D-L6 [PRD]:** the acceptance check below.

**Future-debt register (decided variant; every later ≥ 1):**

| seat | what it commits later phases to | what undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (L1) | a ruled fix fires M3-8: 07c-2b F1/F2 are void for their scene; omni rerun for the cross-chain comparison | "deleting one file" (29-seat1 §4); now two files (07e, 07e-b) | 07e-b's ruling | "no breach", or the M3-8 rebuild done |
| 2 (L1) | one golden round plus M3-8's rebuild, once, before the freeze; the sweep JSON is re-pinned inside that same round (32-seat2 §5) | "deleting the 07e file" (29-seat2 §4); now the two files | 07e-b's ruling | the fix phase lands before 08-4 |
| 4 (L1) | item 15 waits on a long fix (08-3 may split to 08-3b); checklist verdicts heard before 07e-b `done` are provisional and are re-heard if a fix lands | not stated by Seat 4; the debt is repaid by the re-hear (29-seat4 §4) | 07e-b's ruling | 07e-b `done` with "no breach", or the re-hear |
| 5 (L1) | scope 8 held and a likely 07d/07d-b split, **not conditional on a fix**; one board look per output-changing phase until the end date; a fix after a re-pin carries ≥ 6 runs, a CHANGELOG reason and a §6 row | not stated by Seat 5 for H4+G (its "one /fix-plan" is the H2-cg figure, 29-seat5 §4) | 07e-b's ruling; 07d's start date | the re-pin on the final restore path; the end date passes |
| 7 (L1) | 07d/07d-b split, about 1 session, near-certain; 07e-b, about 1 session (now planned); longer holds on 08-4 and item 15 (a delay, not hours); JSON-pin board loops until the end date | before 07e starts: one /fix-plan, about ½ session, 0 Maisara hours; after the JSON is committed: the same plus a script, the JSON, the test and a CHANGELOG reason, under 1 session (32-seat7 §4) | 07e-b's ruling; 07d's start date | the split closes; the end date passes |

- Seat 3 has no row: it is 0/0. Its C3-a clauses remain as acceptance criteria of any fix phase.

**Strongest objection: Seat 5 on the post-end-date fallback (cell S5 later, read from conditions).**
- Seat 5 argues that bare update-with-reason "would let the JSON be updated without anyone asking whether the ruling still holds". It adds that a discrete-field change "can overturn 07e's ruling" and that "a stated reason does not cover it" (32-seat5 §1).
- After the end date, the adopted text drops the board look. It keeps the reason, the §6 row, and my clause requiring the reason to name any discrete-field change.
- **Why it holds:**
  - Seat 5 bounded its own 1 to "while 07e's ruling stands" (§4).
  - Its stated conditions (§6) are all met.
  - Seat 7's later cell needs an end date ("holds at 1 only with the condition in §6"). Without one, Seat 7's premortem predicts unbounded loops.
- **When it would not hold:** if Seat 5, asked, rates the post-end-date fallback at 2. In that case, re-convene Seats 5 and 7 on one variant: a board look only for a discrete-field change after the end date. This touches H3+G and H4+G alike, so it does not move the home.
- **Second-closest objection: Seat 4's unasked timing premise (§2).** If 07e plus 07e-b runs past 08-3's item 15, item 15 waits. Seat 4's 1 already counts that wait.

**Reversal condition (restated; it no longer assumes that the larger 07e is specific to H4+G):**
- **Now:** a second round in which some seat rates the decided variant at 2 on a cost that H3+G does not carry. Only two costs are specific to H4+G: the provisional-verdict re-hear (Seat 4) and item 15 waiting on a fix (Seats 4, 7). A rating of 2 on a common cost (the larger 07e, the split, the JSON pin, Seat 2's gate condition) moves both options equally. It is answered by fixing the text, not by changing the home.
- **Later:** 07e-b's ruling.
  - "No breach" on (a)–(c) zeroes S4's conditional debt and G1's wait. The split and the larger 07e are spent under either home.
  - If a fix cannot be ordered before item 15, it goes back to the board with Seats 4, 5 and 7.

**Accepted for Maisara (PRD check):** no hard constraint is broken, and no PRD id points to another surviving option.
- **NFR-8 L112** ("Any valid scene renders correctly"):
  - H4+G and H3+G rule in 07e-b before 08-4, 11-2 and 12-2, with any fix ordered (G1, G2). Under the merged scope 4, an engine feature never clears a spread.
  - H3 rules equally early but leaves the re-pin order unrated (S5 later 1).
- **FR-3D-5 L75** ("anywhere in the scene"): (a)'s geometry is reachable (D-L4). All three survivors rule before the canvas; equal.
- **NFR-1 L105** ("pass listening tests"):
  - Under all three, item 15's stimuli are built on the ruled engine.
  - Under H4+G, 08-3's checklist verdicts can be heard earlier, on the pre-ruling engine. They are then recorded provisional and re-heard if a fix lands (Item E; 29-seat4). Under H3 and H3+G they cannot be heard earlier.
  - Either way the final listening test is on the ruled engine, so the id does not separate the options.
- **L49/L101** (accuracy first): all three order the CPU re-pin after the acoustic fix. Under G2 (H4+G, H3+G) a growth red "never trims or reverts the acoustic fix". H3 has no such order.
- **L55/L174** (no deadline): H3 and H3+G hold 08-1 and 08-2. That is a schedule cost the PRD does not bound, so no id points to them.

## 5. FINAL texts for the plan-editor (one `/fix-plan`)

Notation: **(S n)** attributes a clause to Seat n; **(decider)** marks my own words.

### Item A1: new file `docs/phases/phase-07e.md`
> # Phase 07e — NFR-8 placement findings from the 07c-2b ABX scenes: measurement (report only)
>
> Size: **S** · Depends on: [07c-2b](phase-07c-2b.md) `done` (the engine its golden round leaves) · Followed by: [07e-b](phase-07e-b.md) (the ruling; planned split, Seat 2: two S sessions) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; image-source order; … claims of physical accuracy" · Created 2026-11-24 by phase-07c-2b's M3 loop (`docs/review/phase-07c-2b/` decider files 17 §3, 28, 30, 33 (H4+G); all nine seats, files 29-seat1…29-seat9 and 32-seat2, 32-seat5, 32-seat7, 32-seat9; researcher 29-researcher-RH1; interrogator 31; Maisara's hand-back) · Read first, in this order: `CLAUDE.md`; this file; `phase-07e-b.md`; `docs/review/phase-07c-2b/5-builder-tail-spread.md`, `14-seat9.md` §2, `29-seat1.md` … `29-seat9.md`, `29-researcher-RH1.md`, `32-seat2.md`, `32-seat5.md`, `32-seat7.md`, `32-seat9.md`, `33-decider-m3h-rebuttal.md`; `docs/BUILD_PLAN.md` §2 AX5, AX6, AX16, AX21, AX22, AX37, AX39, AX40, AX41, AX43, AX44, AX49; PRD NFR-1, NFR-8, FR-3D-5.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Measure, for each finding below, everything phase-07e-b needs to rule whether NFR-8 ("Any valid scene renders correctly") is breached and why. This phase gives no verdict. No `src/sim` change; nothing is tuned for a scene.
>
> ## Gates
> This phase opens nothing by itself. Phase-08-4, the build of phase-08-3 item 15's stimuli and phase-07d scope 8 wait on **phase-07e-b** `done` (and the fix phase it rules, if any) (Seat 2).
>
> ## Scope
> 1. **Findings** (builder file 5; 14-seat9):
>    - (a) `layout4_s1/both_corner`: emitter L (0.1 m from two walls and the ceiling) has a 1 kHz tail 6.20 / 6.12 dB below R's at equal absolute windows (−6.80 dB from each emitter's own t_mix,e), where Kuttruff Eq. 5.42 expects equal reverberant levels at equal power (indicative, §5.6). Listener at (0.1, 0.1, 0.1) m, 0.1 m from two walls and the α 1 floor; emitter L at (19.9, 29.9, 9.9) m; both within AX44's 0.70 m (both-near branch) (S2).
>    - (b) `layout4_s1/both_wall`: tail onsets t_mix,e 0.165 / 0.380 s; from its own onset L's 1 kHz tail energy is +9.39 dB over R's (−0.05 / −0.03 dB at equal windows). Listener 0.1 m from the y = 0 wall, L 0.1 m from the y = 30 wall (S2).
>    - (c) lower priority: `layout4_s0.7/default`, −1.23 dB (L − R) from the common onset 0.380 s (−0.21 / −0.73 dB in the equal windows), not attributed (the room is not diffuse).
>    - The geometry of (a) is reachable from the canvas: a drag or automation lane past a face lands at exactly 0.1 m (`ParameterMap.cpp` `axisFromNormalized`; S6).
> 2. **Candidate causes:**
>    - (a): the diffuse estimator (AX39/AX41/AX44: the both-near weight w and the capped branch; AX40 fixes only its seed, whose effect is bounded near 0.083–0.33 dB); the image-source set at a corner source. The t_mix,e rule is demoted for (a): L's and R's onsets are 0.376 / 0.379 s (S2).
>    - (b): AX22's realised-k test at a source 0.1 m from a face. From the code, `planEmitter` moves the handover to t_cap,e only when the test fails, and R's 0.380 s matches the fallback time of the other layout4_s1 scenes (S2, [Inferred]). Mechanism to test [Inferred from AX22's formula, not measured]: near-coincident image pairs (about 0.58 ms apart) off a face 0.1 m away enter k_real = S²/Q as separate entries, roughly doubling k_real per such face (×4 for L with two faces against ×2 for R with one), so L can pass the k ≥ 19 test where R falls back. Measured in Python from `--images`: k_real with entries merged within 1 ms (print only). Or the t_mix,e rule (S2).
>    - Confirm with `ismFallback`, `expectedMixS` and `capTimeS` from `--diagnostics`.
> 3. **Measurement** (S2; no `src/sim` or CLI edit; every counter is already printed by `--diagnostics`; deterministic, AX5):
>    - A placement sweep at 0.1, 0.2, 0.5, 0.65, 0.75, 1 and 2 m from 1, 2 and 3 faces; each placement with the listener near and with it far; corners with and without the α 1 face (S2); and `medium_room` (8 × 12 × 4 m) at normalised 0 / 1 on 1, 2 and 3 axes (S6).
>    - For each placement and each emitter: the equal-window level per band, 63 Hz–8 kHz, against Eq. 5.42 (S9); E_target against the `matchTail` energy; `--tail-level ax16` against the default; k_real and the fallback flag; the both-near and capped flags, w, n\*, N and W (S2).
>    - Per band and placement, the reference's uncertainty as used by 07e-b scope 1's band rule: for the tracer, from its gated bins; for Eq. 5.42, stated in the report with its basis (decider; makes S2's band qualifier checkable).
>    - Per sweep, the equal-window 1 kHz deficit at each distance, with any step > 1 dB between neighbouring distances flagged as a jump the user would meet while dragging a source (S1). The flag is a print, not an audibility verdict.
>    - An indicative rigid-boundary column (researcher R-H1: Waterhouse 1958 Eq. 3, image sum; derived octave averages at 0.1 m, 1 kHz about −0.5 / −1.6 / −3.8 dB for 1 / 2 / 3 faces). It is printed and is never used to explain a deficit away (S9).
>    - Per placement and emitter: the handover time (after any AX22 fallback) and the AX21 step and dip at it, per band. L_f and L_p at the AX49 gated geometry and on `ax49_l4_cube` (S3, C3-a).
>    - For (b): window energy from the full IR (not tail-only), to test whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s against R's ISM-only energy (S2).
>    - For (c): a diffuse control (the same room with its absorption spread over all faces to the same ᾱ in every band) and an independent late-level reference at equal times from the seeded tracer (`tools/acoustics/tracer.py`), every compared bin gated at k ≥ 684 (3σ ≈ 0.5 dB), so the reference's uncertainty is under 0.5 dB; 1.2 dB is about 1 JND of G (S9). The tracer reference is formed only where the receiver is at least 0.5 m from every face (its receiver is a 0.5 m sphere); it is never a reference at a near-face listener such as (a)'s (S2). Printed: L − R per band for the engine, the control and the tracer. Attribution: a spread that survives in the control is the engine's; one that only the tracer reproduces is the room's; if the tracer's 3σ band overlaps both readings, (c) is 'not decidable' with that stated (S9).
>    - The restore-work counters on the AX38 4c gate scenes: images per emitter, handover time, W_pilot, n\*, N, W (for a fix's effect on 07d scope 8) (S2).
>    - Nothing is fitted to the compared level (no circularity) (S2).
> 4. **Report:** `docs/review/phase-07e/report.md` prints every scope 3 value for (a), (b), (c) and the sweep, with no verdict. Verdicts belong to phase-07e-b.
>
> ## Out of scope
> Any verdict on NFR-8 (07e-b); any `src/sim` edit; tuning for a scene; preset or canvas changes; moving the AX6 clamp; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] The sweep script and its output JSON committed; the JSON holds every scope 3 print for every placement, and the (c) tracer reference with its seed and gated-bin counts. The output JSON records the producing platform (OS, CPU architecture, CI runner label, preset, commit); values are produced by the `cli` preset on the ubuntu-24.04 x64 CI runner (S5). The full sweep and the tracer reference run only in a manually started job or as a one-off print on that runner, never in the per-run pytest (S2, S5; a new CI job follows CLAUDE.md's `needs: changes` / `ci-ok` rules). A pytest in the `python` job re-runs ≥ 1 placement through `render_cli` and asserts every value bit-identically on that runner; on macOS and Windows, `ismFallback` and k_real equal, times and levels within AX5's cross-architecture bound as converted by the builder and stated in the test (AX5). A disagreement in a discrete field is a finding, never a tolerance. The JSON changes only through `tools/ci/update_goldens.py` (S5). Until phase-07e-b is `done` and the fix phase its ruling names, if any, is `done`: a red caused by another phase's output change (e.g. 07d's C5) is resolved in that phase's PR: it re-runs the sweep on the producing runner, updates the JSON through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, and puts the changed prints to the board for whether 07e's findings and 07e-b's ruling still hold. It is never regenerated just to pass, and the ruling is never carried over unasked (S5, 32-seat5). After that date, such a red is updated in that phase's PR through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, never regenerated just to pass (end date: S7, 32-seat7 §6; wording: S5, 29-seat5 §4); the reason states whether any discrete field (`ismFallback`, k_real across 19, the both-near or capped flag) changed (decider).
> - [ ] §0 row 07e updated.
>
> ## Definition of done
> Scopes 1–4 complete; the JSON, script, pytest and report committed; AC green in CI on Linux, macOS and Windows. The PR lists "Decided for Maisara". CLAUDE.md rules apply. The ruling is phase-07e-b's.

### Item A2: new file `docs/phases/phase-07e-b.md`
> # Phase 07e-b — NFR-8 placement findings: cause ruling (report only)
>
> Size: **S** · Depends on: [07e](phase-07e.md) `done` · Lead subject matter: Seat 2 (Engine architect) · Created 2026-11-24 with phase-07e as its planned split (decider files 30, 33; 32-seat2 §2) · Read first: `CLAUDE.md`; this file; `phase-07e.md` and its report `docs/review/phase-07e/report.md`; the files phase-07e lists.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Rule, per finding (a), (b), (c), whether NFR-8 is breached and why, from phase-07e's prints, before 08-3's item 15 stimuli are built, before 07d's growth re-pin and before Phase 08-4. No `src/sim` change in this phase; nothing is tuned for a scene.
>
> ## Gates (what waits on this phase)
> Phase-08-4 (§0 Depends on), the build of phase-08-3 item 15's stimuli and phase-07d scope 8 (the growth re-pin) wait on this phase `done` and on the fix phase it rules, if any (S2, S5). Nothing else waits: 08-1, 08-2, the rest of 08-3 and 07d scopes 1–7 run in parallel; 08-3's checklist verdicts heard before then are recorded provisional (phase-08-3 item 7) (S4).
>
> ## Scope
> 1. **Board loop** (Lead Seat 2; decider; interrogator SURVIVES):
>    - It rules, per finding and per octave band in which the reference's uncertainty is under 0.5 dB: NFR-8 breached / not breached / not decidable, with the cause. The reference is the GA-internal equal level: the late level that the engine's own geometrical model predicts at equal times for each emitter at the scene's source power (Kuttruff Eq. 5.42 where the field is diffuse; the seeded tracer, uncertainty under 0.5 dB, receiver clear of every face, where it is not). Breached: a spread > 1 dB from that reference. Not breached: every band within 1 dB. Not decidable: no such reference can be formed (S2; reference named as in S9). A spread produced by a feature of the engine (the AX44 weight w, the AX39/AX41 capped branch, the AX22 fallback, the t_mix,e rule, a cap) is its cause, never its explanation (S2, S9).
>    - Before the verdicts it records, as already settled by this text, that the engine does not reproduce coherent near-boundary source radiation (R-H1): it is geometric, and as built its late level follows an energy target (E_target), so the reference above holds (S2, S9). AX44's 'GA limit' text names the receiver side only (S2). Whether it should also name the source side (R-H1 §7) is recorded as a separate AX44 amendment after the per-finding verdicts, not before them and not in their place (S9). The rigid-boundary column (phase-07e scope 3) is therefore never a ground for 'not breached' and cannot reduce a spread (S9, S2). Changing that answer is a separate board decision with a new AX checked against the corpus, outside this phase; it applies at the source to the direct, early and late parts alike, and under it a spread counts as explained only where it matches that model's per-band prediction within 1 dB and arises from that mechanism (S2).
>    - For (a), the band-wise deficit is judged against the falsifiable claim 'flat within ±1 dB from 125 Hz to 4 kHz → an engine effect' (S9, 29-seat9 §5).
>    - Audibility is never a ground for 'not breached' under NFR-8 (S1). If the loop considers deferring a ruled fix, Seat 1's self-ABX for (a) (29-seat1 §4) is run first; its null never makes (a) "not breached" (S1).
>    - Hand-offs it convenes: Seat 1 (audibility, if deferral is weighed); Seat 6 (what the canvas or the AX44 note must say; no ruling is ever answered by moving the AX6 clamp, and a change to AX6 is a separate board decision: it remaps saved automation (S6)); Seat 9 (attribution for (c); which planned 12-2 presets place a source within 0.5 m of a face (S9)); Seat 4 (whether a fix adds `both_corner` and `both_wall` to 08-3 AC6's parity cases); Seats 5 and 7 (any fix's order and cost). Already answered: K8, the drag clamp (29-seat6), and R-H1, the source power near rigid faces (29-researcher-RH1).
> 2. **If a `src/sim` change follows:**
>    - The loop writes it as its own phase file (e.g. `phase-07f.md`), ordered before 08-4 and before 07d scope 8. It is an output change (golden round, §6 row; phase-07e's JSON re-pinned inside that round (S2)), fires phase-07c-2b M3-8 (rebuild and reseal both ABX scenes before 08-3 listening), and adds no scene- or placement-specific logic (NFR-8).
>    - The `/fix-plan` that creates the fix phase also adds its id to the Depends-on text of §0 row 08-4 and `phase-08-4.md` L3, to 08-3 item 15's stimulus sentence, and to phase-07d scope 8's order line (or 07d-b's §0 row) (S5, G1/G2).
>    - If a fix phase lands after 07d scope 8's re-pin is committed, its own automated acceptance criteria include that re-pin on the restore path it leaves: reference and baselines from ≥ 6 green manual runs after its last code change (no pooling of earlier runs), a `tests/golden/CHANGELOG.md` reason and a BUILD_PLAN §6 row, under phase-07d scope 8's rule, its Linux return-to-board clause included. It also prints record (h)'s 8-instance load on its own runs; an exceedance goes to the board (S5). A growth red after the fix goes to 07d's FM-GROWTH board loop; it never trims or reverts the acoustic fix (NFR-8, PRD L49) (S2).
>    - A fix that moves the handover, L_f or L_p carries in its own acceptance criteria: AX49's acceptance re-asserted; L_p at the gated geometry printed against 3.82 s; record (h) re-printed at the rated corner if L_f moved there; and the M3-8 rebuild, which names the L4 stimuli if `ax49_l4_cube`'s IR changes (S3, C3-a).
>    - The fix phase also prints the restore-work counters on the AX38 4c gate scenes before and after the fix; whether equal counters allow pooling under 07d scope 8 is Seat 5's ruling (S2).
>    - If the loop finds the fix cannot land before 08-4 or before item 15's build, that order is its own board ruling with Seats 4, 5 and 7, never a default.
>
> ## Out of scope
> Any `src/sim` edit; re-measuring beyond phase-07e's prints except where the loop asks for a named print; tuning for a scene; preset or canvas changes (any consequence goes to 11-2, 11-3 or 12-2 by ruling); moving the AX6 clamp; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] Phase-07e's pytest green on this branch, its JSON unchanged.
> - [ ] §0 rows 07e-b (and 07d, 08-3 and 08-4, if the ruling adds a fix phase) updated.
>
> ## Definition of done
> The ruling for (a), (b) and (c) is committed under `docs/review/phase-07e-b/`, and the interrogator returns SURVIVES. If a fix is ruled, the fix phase file and its §0 row exist, and its id is in the Depends texts named in scope 2. The PR lists "Decided for Maisara". CLAUDE.md rules apply.

**Reconciliation notes for Item A2 scope 1 (task item 2, for the interrogator):**
- **Band rule.** Seat 9 wrote "in any octave band from 125 Hz to 4 kHz". It handed the span to Seat 2, noting "63 Hz and 8 kHz are excluded only for tracer variance [Inf]" (32-seat9 §6). Seat 2's qualifier "per octave band in which the reference's uncertainty is under 0.5 dB" encodes that reason as a rule, so it is adopted. Seat 9's 125 Hz–4 kHz span is kept where Seat 9 itself uses it: (a)'s flatness claim. Seat 9's later-0 conditions (§5) are both met.
- **Order of the coherent-radiation question.**
  - Seat 2 places a record before the verdicts; Seat 9 places the AX44 amendment after them.
  - Both give the same answer, "no". The text states that answer now, so nothing stays open before the verdicts (Seat 9's concern).
  - The AX44 source-side wording comes after the verdicts (Seat 9).
  - Changing the answer is a separate decision, with Seat 2's "explained only where …" rule attached.
  - Seat 2's "AX44 … receiver side only" is checked against BUILD_PLAN L167 (K16). Seat 9's "GA-true, not room-true" is kept only as the reason the engine is geometric.

### Item B: BUILD_PLAN §0
- **New rows after 07d:**
  > "| 07e | [NFR-8 placement findings: measurement (report only)](phases/phase-07e.md) | S | not started | | | Depends on 07c-2b `done`. Created 2026-11-24 by phase-07c-2b's M3 loop (decider files 17 §3, 28, 30, 33: H4+G; all nine seats, files 29 and 32; Maisara's hand-back). Lead: Seat 2 (Engine architect). Planned split: this phase measures (scopes 1–3, report); 07e-b rules. No `src/sim` change. Opens no gate by itself; runs in parallel with 08-1, 08-2 and 07d scopes 1–7. |"

  > "| 07e-b | [NFR-8 placement findings: cause ruling (report only)](phases/phase-07e-b.md) | S | not started | | | Depends on 07e `done`. Created 2026-11-24 with 07e (decider file 33; 32-seat2). Lead: Seat 2 (Engine architect). A fix, if ruled, is its own phase before 08-4 and 07d scope 8. Gates 08-4 (Depends on), 08-3 item 15's stimulus build and 07d scope 8. |"
- **Row 07d notes, append:**
  > "Scope 8 waits on 07e-b and its fix phase, if any (M3-H); if 07d reaches scope 8 first, it splits to 07d-b."
- **Row 08-3 notes, append:**
  > "Item 15's stimuli (AX47 binaural rerun) are built only after 07e-b `done` (and its fix phase, if any); checklist verdicts heard before then are recorded provisional (item 7; M3-H)."
- **Row 08-4:** replace "Depends on 08-3;" with:
  > "Depends on 08-3 and 07e-b `done` (and the fix phase 07e-b's ruling names, if any, added here by id when its §0 row is created);"

### Item C: `docs/phases/phase-08-4.md` L3
Replace "Depends on: 08-3;" with:
> "Depends on: 08-3 and 07e-b `done` (and the fix phase 07e-b's ruling names, if any, added here by id when its §0 row is created);"

### Item D: `docs/phases/phase-07d.md` scope 8, prepend
> "**Order against phase-07e-b (phase-07c-2b M3-H):** this scope runs only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done` (§0). If this phase reaches scope 8 first, scope 8 splits to `phase-07d-b.md` with that dependency in its §0 row; 07d-b inherits 'lands before 08-4 freezes its goldens' (scope 6) and premise P1. Scopes 6 and 7 are not held."

### Item E: `docs/phases/phase-08-3.md`
- **Item 15:** replace L74–75 ("Whether item 15's stimulus build waits … `24-m3h-for-maisara.md`).") with:
  > "Stimuli are built only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done` (phase-07c-2b M3-H, decider files 30, 33; the fix phase's id is added here when its §0 row is created)."
- **Item 7, append** (S4; the only change is "07e" to "07e-b", per S2's gate condition):
  > "If heard before phase-07e-b is `done` (and the fix phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine before the 07e-b ruling'. A level or dryness remark on a near-face render goes to 07e/07e-b (or, once 07e-b is `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones."
- **Listening checklist:** after "Record the `hrtfId` … (scope 7).", add:
  > "Verdicts heard before phase-07e-b is `done` are marked 'provisional: engine before the 07e-b ruling' (item 7)."

### Item F: `docs/validation/abx-07c-2-run-sheet.md`, C-b bullet (L130–131)
Replace "goes to the board (home pending Maisara's answer on M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`) as an NFR-8 candidate." with:
> "goes to phases 07e/07e-b, or, once 07e-b is `done`, to the board as an NFR-8 candidate (M3-H, decider files 30, 33; R1)."

### Item G: `docs/phases/phase-07c-2b.md`, Out of scope (L192–193)
Replace the line with:
> "- The NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): measured in phase-07e, ruled in phase-07e-b (M3-H, decider files 30, 33, H4+G); this phase's PR lists them under Follow-ups."

### Item H: BUILD_PLAN §0 row 07c-2b (two edits, bookkeeping)
- **Status cell:** replace "blocked (awaiting Maisara: M3-H answer, the ABX listener and sitting dates, then the ABX itself)" with:
  > "blocked (awaiting Maisara: the ABX listener and sitting dates, then the ABX itself)"
- **Notes:** in "Waiting: M3-H (case (a), file 24);", replace "M3-H (case (a), file 24)" with:
  > "nothing on M3-H (decided for Maisara, decider files 30, 33: H4+G, phases 07e/07e-b)"

### Item I: BUILD_PLAN §6, new row
> "| 2026-11-24 | Phase 07c-2b M3-H re-run after Maisara's hand-back (decider files 28, 30, 33; seats files 29-seat1…9, 32-seat2/5/7/9; researcher 29-researcher-RH1; interrogator 31; corpus c1b171f): phases 07e (report-only measurement: findings, causes, sweep with Seats 1/2/3/6/9 prints, (c) diffuse control and tracer reference under 0.5 dB; G3 producer-platform pytest on ≥ 1 placement, full sweep and tracer by manual run; red clause Seat 5 until 07e-b and any fix `done`, then update-with-reason) and 07e-b (ruling against the GA-internal equal level; an engine feature is a cause, never an explanation; fix-phase ordering G1/G2, C3-a) created, Lead Seat 2; §0 rows 07e, 07e-b (new), 07c-2b (status and notes), 07d, 08-3 and 08-4 (Depends on 07e-b, G1); phase-07d scope 8 ordered after 07e-b and its fix phase (G2; 07d-b split if reached first); phase-08-3 item 15 gate, item 7 provisional-verdict clause and checklist line; phase-08-4 L3; run sheet C-b bullet (R1); phase-07c-2b Out of scope. Decided for Maisara; amends nothing. | phase-07c-2b session (Claude), board loop; /fix-plan (plan-editor); `docs/review/phase-07c-2b/` |"

## 6. Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-H | H4+G with the 07e (measure) / 07e-b (rule) split, Lead Seat 2; gates on 07e-b `done` plus its fix phase: 08-4 Depends on, 08-3 item 15 stimuli, 07d scope 8; merged scope-4 breach rule; G3 pytest on ≥ 1 placement; Seat 5's red clause until the end date, then update-with-reason; texts §5 A1–I | revised (to the interrogator) | 1 (S1, S2, S4, S5 ‡, S7) | 7 (ties H3+G at 7; reversibility decides) | medium | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 | none load-bearing. Kuttruff Eq. 5.42 (indicative) is the reference named in 07e-b; Toole §12.1 and Waterhouse via R-H1 feed the ruling only | now: a seat rates an H4+G-specific cost (provisional re-hear, item 15 wait) at 2 → H3+G. Seat 5 rating the post-end-date fallback at 2 → re-convene Seats 5 and 7 on a discrete-field-only board look (no change of home). Later: 07e-b's ruling ("no breach" zeroes S4's conditional debt) |

**Challenges to settled decisions:** none.

## 7. Decided for Maisara
- **M3-H (revised):** we find out whether a source pushed into a corner loses its reverb, and whether one source's reverb starts early by a wall. The check is two small report-only phases: 07e measures and 07e-b rules.
  - **When:** before the binaural listening stimuli are built, before 07d's CPU re-pin and before Phase 08-4. Any fix lands before all three. A fix to the engine is never excused because the engine's own model produced the deficit, and never because it might be inaudible.
  - **Accepted on:** NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101 and L55/L174. H3+G serves the same ids. It also holds 08-1 and 08-2 from day one, which no PRD id asks for, and that hold cannot be recovered.
  - **Who gave most:** Seat 7 (07e is now about two sessions, plus a likely 07d split) and Seat 2 (it leads the investigation and the ruling). They get back a single golden round and a single re-pin, once, before anything freezes, and an end date on the JSON's board checks.
  - Amends nothing.

**NEEDS MAISARA:** none.

**Files read:**
- `/home/user/makroof/docs/review/phase-07c-2b/`: 30-decider-m3h-decision.md, 31-interrogator-on-file30.md, 32-seat2.md, 32-seat5.md, 32-seat7.md, 32-seat9.md, 29-seat1.md, 29-seat2.md, 29-seat3.md, 29-seat4.md, 29-seat5.md, 29-seat6.md, 29-seat7.md, 29-seat9.md
- `/home/user/makroof/docs/BUILD_PLAN.md` (§0 L37–38, L42–43; AX44 L167 "GA limit")
- `/home/user/makroof/tools/acoustics/tracer.py` (L21–28, L41–44, L243–244)

