
# 31: Interrogator on file 30 (M3-H decision round, H4+G)

For saving as `/home/user/makroof/docs/review/phase-07c-2b/31-interrogator-on-file30.md`. I changed no files.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

## Verdict: the decision does not survive as written. Outcome: TENSION MISREAD

The fix is small and probably leaves H4+G the winner, but the decision cannot stand on its current map. These parts are faithful:
- **Convening:** all nine seats were convened.
- **Map of the seven options as they were briefed:** every cell matches the seat's own words.
- **Sums:** H3+G 8, H4+G 8 and H3 9 are right.
- **Debt register:** has every row it needs.
- **PRD reading:** the acceptance check holds.

The defect is in the option actually decided. It is H4+G **plus the seven adopted seat texts**, and two of its cells are not the seats' words:

1. **Seat 7's cells are carried over to a variant Seat 7 never rated.**
   - Seat 7 rated H4+G as "About 1 session [Hyp]. G1–G3 add only text to the same /fix-plan round" (29-seat7 §3).
   - The adopted prints are scope work, not G1–G3 text. They are Seat 6's medium_room sweep, Seat 9's band-wise, diffuse-control and tracer prints, Seat 1's per-distance print, C3-a, and Seat 2's extra distances, listener-near/far and α-1 variants and counters.
   - Seat 7 ran in parallel and did not see them.
   - The decider admits this (§3 step 7, strongest objection) but still keeps S7 at 1/1. Its own rule (decider.md §4) says to ask the seat in a second round, or to read the cell from conditions and mark it. It did neither.
2. **Seat 3's cell for the adopted variant is wrong.** Seat 3 says C3-a "takes every pre-freeze option from 0/1 to 0/0" (29-seat3 §6). The decider adopts C3-a but keeps S3 at 0/1 and sums H4+G to 8.

The reversal condition also does not follow from the decision (row M3H-15):
- It says that if Seat 7 rates the enlarged 07e at 2, the decision "falls back to H3+G with the same prints".
- But the prints enlarge 07e under H3+G exactly as they do under H4+G.
- So a Seat 7 rating of 2 for the enlarged 07e would also land on H3+G, which would not "hold the lowest maximum alone".

**What the decider must do:**
- Run one short second round. Seat 7 rates the enlarged 07e under H4+G and H3+G. Seat 2, as Lead, confirms "S" for the prints it did not itself propose.
- Correct S3 to 0/0.
- Redo steps 3–7.
- Apply the text corrections below.

If Seat 7 keeps 1/1 and the corrections are applied, I expect SURVIVES WITH CORRECTIONS. With C3-a counted, H4+G is 7 and H3 is 8. H3+G is 7 if it carries the same prints and 8 if it does not. So H4+G wins either outright on sum or on the same reversibility tie-break.

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-H | convening | nine rows; all nine seats convened, none NOT MY MATTER | faithful | 28-decider-m3h convening table; 29-seat1…9 all give positions | — | — |
| M3-H | map | 63 cells, 7 options × 9 seats, as briefed in file 28 | faithful, every cell | S1 29-seat1 §3–4; S2 22-seat2 §3–4 + 29-seat2 §3–4; S3 29-seat3 §3–4; S4 29-seat4 table; S5 22-seat5 §3–4 + 29-seat5 §2–4; S6 29-seat6 §3–4; S7 29-seat7 §3–4; S8 29-seat8 §3–4; S9 29-seat9 §3–4 | — | — |
| M3-H | map / sums | H1 18, H2-c 16, H2-cg 10, H3 9, H3+G 8, H4 10, H4+G 8 | CORRECT (redone) | H4+G: 1+2+1+1+1+0+2+0+0 = 8. H3+G: same digits, with S4 and S5 at 1/0. H3: S5 1/1, so 9 | — | — |
| M3-H | map (decided variant) | S7 1/1 on H4+G **with** the adopted prints | TENSION MISREAD (cell invented for an unrated variant) | 29-seat7 §3: "About 1 session [Hyp]. G1–G3 add only text…". It priced the file 17 skeleton + G1–G3, not the sweep's added placements, the tracer reference or C3-a | TENSION MISREAD | Q1 |
| M3-H | map (decided variant) | S3 0/1 on H4+G with C3-a adopted | TENSION MISREAD (cell not the seat's) | 29-seat3 §6: C3-a "takes every pre-freeze option from 0/1 to 0/0". So S3 is 0/0, and H4+G sums to 7 | TENSION MISREAD (the winner does not change) | Q2 |
| M3-H | map / composition | "none raises a cell" (§3 step 4, §4) | IMPRECISE | Seats 1, 4, 7 and 9 say this only of their own cells. Seat 3's text lowers a cell. Seat 6's medium_room is a §7 hand-off with no statement about cells. Seat 2 gave no such statement for its amendments. No seat stated the effect of the combined texts on S7 | correction | Q1 |
| M3-H | ordering: bounds / veto | none dropped; Seat 6's veto is conditional (clamp moved after release) | correct | 29-seat6 §4. The 07e text puts the clamp out of scope and makes any AX6 change a separate board decision, so Seat 6 sits at that decision | — | — |
| M3-H | ordering: worst-off | survivors with max 1: H3, H3+G, H4+G | correct | H2-cg max 2 at S4 ("2 as worded", 29-seat4); H4 max 2 at S5 (22-seat5 §4) | — | — |
| M3-H | ordering: compose | no variant brings the max to 0 | correct | no seat states a condition that takes its last 1 to 0 except S3 (C3-a) and S5 ("no breach", which is an outcome) | — | — |
| M3-H | ordering: reversibility | "Under H4+G the debt is conditional: S5 says it 'arises only if a fix is ruled'" | IMPRECISE (hidden premise, see row M3H-14) | Item D holds scope 8 on "phase-07e is `done`" whether or not a fix is ruled. Seat 7 calls the split "near-certain" (29-seat7 §4). The split is common to H3+G and H4+G (29-seat7: H3+G "Same split cost"). What is conditional is only S4's re-hear and S5's re-pin-after-fix | SURVIVES WITH CORRECTIONS (winner unchanged: the certain extra cost that H3+G alone carries is still the 08-1/08-2 hold, S4 1/0 and S5 1/0) | Q3 |
| M3-H | debt | rows S1, S2, S3, S4, S5, S7 (every later ≥ 1) | present | register §4 | — | — |
| M3-H | debt | S5 row "undoing costs: one /fix-plan" | IMPRECISE (attribution) | 29-seat5 §4 says "Undoing it costs one /fix-plan" in its **H2-cg** paragraph. For H4+G Seat 5 gives no undo cost; Seats 1 and 2 give "delete one file" | correction | — |
| M3-H | debt | S7 row "what undoing costs: —" | IMPRECISE | Seat 7 gives no undo cost for H4+G. The row should say so ("not stated by Seat 7"), not leave a blank | correction | — |
| M3-H | debt | S2 "repaid when: the fix phase lands before 08-4"; S3 "the fix phase's AC green" | acceptable (conditional) | No fix phase exists yet. Applied 07e scope 5 obliges its creation and §0 entry if one is ruled | — | — |
| M3-H (M3H-14) | inference | hidden premise: H4+G's later debt is conditional on a fix | IMPRECISE | see the reversibility row; Item D and 29-seat7 §4 | correction | Q3 |
| M3-H (M3H-15) | inference | reversal condition: "if Seat 7 … rates the enlarged 07e at 2 … falls back to H3+G with the same prints. H3+G then holds the lowest maximum alone" | FALLS as stated (does not follow) | The adopted prints are 07e's scope under any home. A Seat 7 rating of 2 for the enlarged 07e would apply to H3+G's 07e too. Under H3+G it blocks all of 08, so it is no cheaper. This invalidates the stated fallback, not the choice | must be redone with Q1's answer | Q1 |
| M3-H | claim D-L1 | 08-3 depends on 08-2, 04, 05b, 05h, 07, not on 07d | CORRECT | phase-08-3 L3; §0 L42 | — | — |
| M3-H | claim D-L2 | scope 8 pools only if "07d leaves the restore path unchanged"; an AX22 fix changes restore work | CORRECT (plan); restore work is Seat 2's own claim from the code | phase-07d L94–96; 29-seat2 K7 | — | — |
| M3-H | claim D-L3 | 07d is `not started` and depends on 07c-1 and 07c-1b; 07c-2b is `blocked` | CORRECT | BUILD_PLAN §0 L37–38 | — | — |
| M3-H | claim D-L4 | `axisFromNormalized` = 0.1 + clamp01(n)·(side − 0.2); a drag past a face lands at 0.1 m | CORRECT (from the code) | ParameterMap.cpp L25–36; Validate.h L28. "Exactly" means to floating-point precision (29-seat6) | — | — |
| M3-H | claim D-L5 | sums 8 / 8 / 9 | CORRECT for the briefed options; **7** for H4+G with C3-a | see the map rows | correction | Q2 |
| M3-H | K11 / record correction | at 1 kHz and 0.1 m, rigid faces give less power than free field; octave averages −0.5 / −1.6 / −3.8 dB; corner pure tone −10.7 dB; the d → 0 limit is in Toole §12.1 | CORRECT as derived; not load-bearing | Toole §12.1, Fig. 12.1 table (+3/+6/+9 dB power) and the validity line (long wavelengths only). Redone from R-H1 D3 at u = 2kd = 3.664: 1 − 0.4086 − 0.5163 + 0.0099 = 0.085, which is −10.7 dB. My trapezoid over u ∈ [2.59, 5.18] gives a mean of 0.44, about −3.6 dB, inside R-H1's ±0.5 dB. Rigid faces only (R-H1 §3) | — | — |
| M3-H | K-row (07e 1(a)) | Kuttruff Eq. 5.42 "expects equal reverberant levels at equal power (indicative, §5.6)" | CORRECT (rated in file 20, unchanged) | Kuttruff §5.6 Eq. 5.42, w_r = 4P/(cA); caveat when ᾱ is not small (§5.6, L2724) | — | — |
| M3-H | PRD proxy | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 | the ids say what is claimed; no PRD id points to H3+G | PRD L49 ranks accuracy against CPU/latency, not schedule; L55/L174 say "no fixed deadline"; all three survivors are shown against each id | no PRD MISREAD | — |
| M3-H | PRD proxy | NFR-1 line, "all three build item 15 on the ruled engine; equal" | IMPRECISE | Under H4+G, 08-3's checklist verdicts can be heard on the pre-ruling engine and marked provisional (29-seat4 H4/H4+G row); under H3+G they cannot. They are re-heard, so NFR-1's final listening test is still on the ruled engine and the id does not separate the options | correction (add the provisional re-hear to the line) | — |
| §5 Item A, scope 3 | text fidelity | (c): "independent late-level reference … with its uncertainty stated (Seat 9)" | unfaithful (softened) | 29-seat9 §5: "with an uncertainty under 0.5 dB, since 1.2 dB is about 1 JND of G". The tracer already gates bins at 3σ ≈ 0.5 dB (`tools/acoustics/tracer.py` docstring, k ≥ 684) | correction: "with an uncertainty under 0.5 dB (Seat 9)" | — |
| §5 Item A, scope 4 | text fidelity | "breached / not breached (a level spread > 1 dB at equal times unexplained by the engine's model, Seat 2's test)" | INCONSISTENT (misattributed, and it has two readings) | Seat 2's test in the file 17 skeleton reads "unexplained by physics". Seat 2 did not amend scope 4 (29-seat2). Read literally, a deficit produced by a model feature (e.g. AX44's weight w) is "explained by the engine's model" and so "not breached", which defeats NFR-8. Seat 9's clause, "The verdict for (a) is judged against the GA-internal equal level" (29-seat9 §6), is left out | correction required | Q4 |
| §5 Item A, scope 4 | text fidelity | "It first rules whether the engine is meant to reproduce coherent near-boundary radiation (R-H1; AX44 'GA limit')" | decider's own text (sourced to R-H1 §7), not a seat's; it leaves open what Seat 9's verdict clause closes | AX44's GA limit is receiver-side only (BUILD_PLAN L167). R-H1 §7 flags the source side as a conditions question. Seat 9 says the rigid column is "never used to explain a deficit away" | must be reconciled with Seat 9's clause | Q4 |
| §5 Item A, scope 3 | text fidelity | the > 1 dB step print, labelled "a print threshold, not an audibility claim; Seat 1" | IMPRECISE (relabelled) | Seat 1 framed it as a jump that "shows up as a cue the user hears while dragging" (29-seat1 §6). The relabel matches the run sheet's convention, and the print is unchanged | minor; acceptable | — |
| §5 Item A, scope 4 | text fidelity | Seat 6 hand-off: "the AX6 clamp is not a remedy within this ruling … a separate board decision" | faithful in substance, softer than the seat | Seat 6: "no ruling is ever answered by moving the AX6 clamp", given as an H1 condition; veto only if moved after release (29-seat6 §4, §6) | minor | — |
| §5 Item A, AC | text fidelity | G3 text, plus "a red caused by another phase's output change … goes to the board …" | unattributed addition | Seat 5's G3 ends at "…only through `tools/ci/update_goldens.py`". Its §4 says such a red is "updated with a stated reason, never regenerated just to pass". The board clause follows Seat 7's §7 hand-off, but neither Seat 5 nor Seat 7 wrote or rated this text | attribute it, or have Seat 5 confirm it in the Q1 round | Q5 |
| §5 Items A scope 1–2, B, C, D, E, F, G, I | text fidelity | Seat 2's amendments; G1 and G2 (Seat 5); 07d-b inheritance (Seat 7); Seat 4 item-7 text; R1 | faithful | 29-seat2 "Skeleton"; 29-seat5 §6; 29-seat7 §6; 29-seat4 §5; file 20 R1. Anchors exist: 08-3 L74–75 and L144; 08-4 L3; 07d scope 8; run sheet L130–131; 07c-2b L192–193 | — | — |
| §5 Item H | text fidelity | replaces only the "Waiting: M3-H (case (a), file 24)" note in row 07c-2b | INCONSISTENT (row left contradictory) | The status column of §0 L37 still says "blocked (awaiting Maisara: M3-H answer, the ABX listener …)". Item H does not touch it | correction: Item H also removes "M3-H answer, " from the status cell | — |
| M3-H | strongest objection | Seat 7's sizing | correctly named; "holds anyway" is not shown | Its three reasons (existing tools, the 07e-b bound, Seat 7's later 1 counting a long fix) are the decider's, not Seat 7's. Only Seat 7 rates its session cost (decider.md §3, "Never re-rate a seat") | TENSION MISREAD (row above) | Q1 |

## Questions for the decider's rebuttal round (most consequential first)

1. **Seat 7 and Seat 2 on the enlarged 07e.** Ask Seat 7 to rate H4+G and H3+G **with** the seven adopted texts (now and later, one value each). Ask Seat 2, as Lead, whether 07e stays size S with Seat 9's tracer reference and diffuse control, Seat 6's medium_room cases and C3-a's prints. Falsifiable from their reports. Then redo steps 3–7, and restate the reversal condition so that it does not assume the prints apply only under H4+G.
2. **Seat 3's cell.** Do you accept S3 = 0/0 for every option that carries C3-a (29-seat3 §6)? What sums result: H4+G 7, H3+G 7 or 8 depending on whether it carries the prints, H3 8? Which step then decides, sum or reversibility?
3. **Reversibility premise.** Item D holds scope 8 on 07e `done` whether or not a fix is ruled. Do you agree that the 07d/07d-b split is not conditional on a fix (29-seat7 §4, "near-certain") and that it is common to H3+G and H4+G? Restate step 6 accordingly. The winner is unchanged by my working.
4. **Breach criterion in 07e scope 4.** Restore Seat 2's test as written, or adopt Seat 9's clause ("the verdict for (a) is judged against the GA-internal equal level"). Then say how "It first rules whether the engine is meant to reproduce coherent near-boundary radiation" stands beside that clause. As written, "unexplained by the engine's model" lets a deficit caused by a model feature count as "not breached".
5. **The AC's board clause** for a red caused by another phase's output change. Which seat wrote it? If none did, will you put it to Seat 5 in the Q1 round? Seat 5's §4 sends such a red to an update with a stated reason.

**Corrections to fold in when re-issuing (none of them changes a winner by itself):**
- Seat 9's "uncertainty under 0.5 dB";
- the S5 and S7 undo-cost cells in the debt register;
- the NFR-1 line, which should name the provisional re-hear;
- Item H, which should also clear "M3-H answer" from row 07c-2b's status cell.

## Files read
- `/home/user/makroof/docs/review/phase-07c-2b/30-decider-m3h-decision.md`, `28-decider-m3h.md`, `29-seat1.md` … `29-seat9.md`, `29-researcher-RH1.md`, `22-seat2.md`, `22-seat5.md`, `14-seat7.md`, `5-builder-tail-spread.md` (L1–42), `17-decider-m3-r4.md` (L215–258), `20-interrogator-on-file17.md` (via search)
- `/home/user/makroof/.claude/agents/decider.md` (L150–309), `/home/user/makroof/docs/board/seat-protocol.md` (L30–69)
- `/home/user/makroof/docs/PRD.md` (L14–180), `/home/user/makroof/docs/BUILD_PLAN.md` (§0 L28–59; AX5, AX6 L128–129; AX22 L145 and AX44 L167 via search)
- `/home/user/makroof/docs/phases/phase-07d.md` (L1–110), `phase-08-3.md` (L1–100, L144), `phase-08-4.md` (L1–30), `phase-07c-2b.md` (L186–194), `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` (L124–133), `/home/user/makroof/docs/sessions/2026-11-24-phase-07c-2b.md` (L15–18)
- `/home/user/makroof/src/module3d/ParameterMap.cpp` (L1–45), `/home/user/makroof/src/contract/Validate.h` (L28), `/home/user/makroof/src/cli/Cli.cpp` (via search: `--tail-level`, `ismFallback`, `capTimeS`, `expectedMixS`), `/home/user/makroof/tools/acoustics/tracer.py` (L1–50, signatures)
- Corpus: `/home/user/makroof/docs/corpus/toole-sound-reproduction.md` (§12, §12.1, L1598–1631), `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` (Eq. 5.42 §5.6 and the caveat, via search)
