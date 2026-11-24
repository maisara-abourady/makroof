
# 35: Interrogator on file 33 (M3-H rebuttal, H4+G with the 07e/07e-b split)

To be saved as `/home/user/makroof/docs/review/phase-07c-2b/35-interrogator-on-file33.md`. I changed no files.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

## Verdict: the decision does not survive as written. Outcome: PRD MISREAD + FALLS (07e-b scope-1 text only)

**What survives.** The home (H4+G), the ordering and the tie-break all hold. All five of file 31's questions and every listed correction were answered faithfully:
- Seat 7 re-rated at 1/1.
- Seat 3 is at 0/0.
- The split is common to both options.
- The scope-4 text is merged.
- The board clause is attributed and end-dated.
- "Under 0.5 dB" is restored.
- The undo cells, the NFR-1 line and Item H are fixed.

The sums are right: H4+G 7, H3+G 7, H3 8. Reversibility decides, and Seat 4 (34 §3) and Seat 7 (32 §4) both say it favours H4+G.

**Two defects, both in what file 33 newly adds:**

1. **PRD MISREAD: her recorded decision AX44 / B15 is left out.**
   - Finding (a) is `layout4_s1/both_corner`: both ends are within 0.70 m of a face, the cap is hit, and it is a layout-4 corner.
   - AX44 is a §2 row that cites her: "Accepted by Maisara 2026-11-10 (ledger P05B2-M-02)" (BUILD_PLAN L167). It already says three things about this geometry:
     - "No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners";
     - it pins `layout4_s1/both_corner` as asserting the cap flag;
     - it accepts as debt that "both-near reads low, flagged, not bounded" (C13 §2: capped medians −0.35 to −6.72 dB). That debt is repaid by §5 B15, which is "none scheduled" (L408).
   - (a)'s −6.2 dB lies inside that accepted range.
   - File 33's text contradicts this without showing it. The merged 07e-b rule says "the AX44 weight w, the AX39/AX41 capped branch … is its cause, never its explanation". "Decided for Maisara" says a fix "is never excused because the engine's own model produced the deficit" and "Amends nothing".
   - Together these turn her accepted, flagged and unscheduled debt into an NFR-8 breach that must be fixed before 08-4. Neither AX44 nor B15 is shown, and there is no `AMENDS her decision of 2026-11-10` line.
   - decider.md §5 forbids changing her decision inside a board decision; that needs a separate `FOR MAISARA` answer.
   - **Correcting my own file 31.** Row 70 there said "AX44's GA limit is receiver-side only". That was imprecise for the same reason, and I withdraw the wording. File 33's K16 and the 07e-b text ("names the receiver side only (S2)") carry the same error.

2. **FALLS (INCONSISTENT): the 07e-b scope-1 text leaves (a) with no admissible reference.**
   - The merged text allows two references:
     - Eq. 5.42 only "where the field is diffuse";
     - the tracer only with the "receiver clear of every face".
   - Layout 4 (20 × 30 × 10 m, α 1 floor, s 1) is the corpus's own example of a non-diffuse room. Kuttruff §5.7 calls the 1:2:3 room with an absorbing floor a "severe deviation from diffuse conditions" (Table 5.2 case 4; Fig. 5.11(a); Fig. 5.10 shows element levels about 3.5 dB apart at 9 MFP). Working: ᾱ = (600·1 + 1600·0.01)/2200 = 0.28, so the §5.6 caveat "ᾱ … not small compared with 1" also applies.
   - (a)'s listener is at (0.1, 0.1, 0.1) m. The tracer's receiver has radius 0.5 m (tracer.py L21, L42), so the tracer is barred there.
   - So under the text's own rule, (a) can only come out "not decidable". The text gives that outcome no consequence for the gates, so they would open with no fix, which is the failure both Seat 2's and Seat 9's premortems describe.
   - Seat 9's text would use the tracer "where it is not" diffuse. Seat 2 bars it at (a)'s listener. Seat 2's hand-off to Seat 9 ("confirm the tracer is used only where the receiver is clear of every face", 32-seat2 §7) was never answered, and the reconciliation notes do not mention it.

## Follow-ups after file 33: what the final texts must carry

**Required for SURVIVES. Leaving any of these out is TENSION MISREAD, because the debt or the seat's words would be dropped:**
- **Seat 4 (34-seat4 §3).** Restate the "Second-closest objection" so that what breaks the premise is 07c-2b's ABX dates slipping (07e depends on 07c-2b `done`), not the split. Also:
  - change §2's "Premise not re-asked" to cite 34-seat4;
  - in §3 step 6, replace "both conditional on a ruled fix" with: the item-15 wait also arises if the ABX dates slip. The same slip holds 08-1/08-2 under H3+G, so the winner does not change;
  - in the S4 register row, add the slip path. Its "repaid when" and the "Later" reversal should read "07e-b rules no fix phase", not "no breach". Seat 4: "the re-hear happens only if 07e-b rules a fix".
- **Seat 5 (34-seat5 §3–4).** S5 0/1 is now the seat's own rating, so remove ‡ / "(read from conditions)" and cite 34-seat5. The strongest objection as named is answered (Seat 5 rates 1, not 2); restate it.
  - Add the residual debt to the S5 row. After the end date, a discrete-field flip is "recorded but no gate stops it". Undo: "one board look plus possibly a fix phase". Evidence: "the first output-changing PR after the end date whose reason names a flip".
  - The row's current "repaid when … the end date passes" contradicts this.

**Not required (both seats say so):**
- **Seat 4's optional clause** "lifted without re-hearing if 07e-b rules no fix phase". Only the register and reversal wording above is required.
- **Seat 5's refinement** (the pytest names the changed discrete fields; the PR lists any change under Follow-ups as an NFR-8 candidate). Seat 5: "If the decider prefers not to adopt it, my 1 stands as rated." If it is adopted:
  - attribute it to S5;
  - either answer Seat 5's hand-off to Seat 7 (does a non-blocking Follow-ups entry count as a "board loop" under Seat 7's §6 second branch?) or mark S7's later cell read from conditions.

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-H | convening | nine seats, all convened (file 28); follow-ups to S2, S5, S7, S9 (32) and S4, S5 (34) | faithful | session brief L17–18 "hand it back"; 29-seat1…9 | — | — |
| M3-H | Q1 / M3H-15 | S7 1/1 for H4+G and H3+G; split 07e / 07e-b; reversal restated | faithful | 32-seat7 §3–4; 32-seat2 §2; reversal now keys only on H4+G-specific costs, so a 2 there leaves H3+G alone at max 1 | — | — |
| M3-H | Q2 | S3 0/0 with C3-a; sums 7 / 7 / 8 | CORRECT (redone) | 29-seat3 §6. H4+G: 1+2+0+1+1+0+2+0+0 = 7; H3+G the same; H3: S5 1/1, so 8 | — | — |
| M3-H | Q3 / step 6 | "only two debts … both conditional on a ruled fix" | IMPRECISE | 34-seat4 §3: item 15 can wait on 07e-b itself if the ABX dates slip; under H3+G the same slip also holds 08-1/08-2 | SURVIVES WITH CORRECTIONS (winner unchanged) | — |
| M3-H | Q4 / text | merged scope-1 breach rule (07e-b) | faithful to S2 §3–4 and S9 §2 sentence by sentence, except below | 32-seat2 §3–4; 32-seat9 §2 | — | — |
| M3-H | inference / text | (a) has no admissible reference under the merged rule | INCONSISTENT | Kuttruff §5.7: the absorbing-floor 1:2:3 room is a "severe deviation from diffuse conditions" (Table 5.2 case 4, Fig. 5.11(a)); §5.6 caveat at ᾱ = 0.28; tracer R_D 0.5 m (tracer.py L42) vs listener at 0.1 m; "not decidable" has no gate consequence | FALLS (Item A2 scope 1 only; home unaffected) | Q2 |
| M3-H | Q5 | AC board clause attributed; end date; decider's discrete-field clause | faithful; now accepted by S5 | 32-seat5 §1; 32-seat7 §6 branch 2; 34-seat5 §2, §4 | — | — |
| M3-H | map S5 | 0/1 ‡ read from conditions | superseded | 34-seat5 §3–4: "0" now, "1" later, given on the end-dated clause | correction: cite 34-seat5, drop ‡ | — |
| M3-H | map S9 | 0/0 "confirmed" | IMPRECISE (marking) | 32-seat9 §3 confirmed 0/0 for "my two texts adopted". The adopted text changes the band span (handed to S2, acceptable) and adds S2's receiver bar, which S9 never saw. §5 conditions are literally met, so the cell is read from conditions and must be marked | correction; and Q2 | Q2 |
| M3-H | map S4 | 0/1; H3+G 1/0 | faithful | 34-seat4 §2 "Confirmed, unchanged" | — | — |
| M3-H | debt S4 | "repaid when 07e-b done with 'no breach'"; ABX-slip path missing | TENSION MISREAD unless corrected | 34-seat4 §2–3 | required correction | — |
| M3-H | debt S5 | "repaid when … the end date passes" | TENSION MISREAD unless corrected (residual dropped) | 34-seat5 §4: the post-date flip is "recorded but no gate stops it"; undo cost and evidence point given | required correction | — |
| M3-H | ordering | bounds / veto / worst-off (max 1: H3, H3+G, H4+G) / compose / sum / reversibility | correct | redone; reversibility per 32-seat7 §4 and 34-seat4 §3 | — | — |
| M3-H | D-L7 | 07e is two S sessions | NOT CHECKABLE (seat's own-cost [Hyp]); faithful | 32-seat2 §2; 32-seat7 §3 | — | — |
| M3-H | D-L8 / K14 | receiver "0.5 m sphere"; k ≥ 684; 3σ ≈ 0.498 dB; N0 ≈ 1.52 M | CORRECT, but "0.5 m sphere" is IMPRECISE: radius 0.5 m | tracer.py L21, L28, L42–44: √684 = 26.15, 4.34/26.15 = 0.166, ×3 = 0.498 dB; ceil(254 × 6000) = 1,524,000 | correction: "radius 0.5 m" | — |
| M3-H | K15 | `--diagnostics` prints the scope-3 counters | CORRECT (spot-checked) | Cli.cpp L597–647: ismFallback, capTimeS, expectedMixS, nStar, bothNear, wPilot | — | — |
| M3-H | K16 / 07e-b text | "AX44's 'GA limit' … names the receiver side only" | IMPRECISE (also my file 31 row 70) | L167: the mechanism is receiver-side, but the same paragraph disclaims accuracy "where both ends are flagged, nor at layout-4/5-type edges and corners", which covers (a)'s emitter | feeds PRD MISREAD | Q1 |
| M3-H | phase deps | 08-1 → 04/05b/05h/07; 08-2 → 08-1; 08-3 → 08-2; 08-4 "Depends on: 08-3;" | CORRECT | phase-08-1…4 L3; BUILD_PLAN L43 | — | — |
| M3-H | anchors | §0 L37 status "M3-H answer, …"; "Waiting: M3-H (case (a), file 24)"; L43 "Depends on 08-3;" | CORRECT (anchors exist) | BUILD_PLAN L37, L43 | — | — |
| M3-H | text (c) | "1.2 dB is about 1 JND of G" | CORRECT (loose) | Vorländer Table 6.1: G jnd 1 dB, 500–1000 Hz | — | — |
| M3-H | PRD proxy | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 vs H3, H3+G, H4+G | the ids say what is claimed; every survivor is shown | PRD L49, L55, L75, L105, L112, L174 | — | — |
| M3-H | PRD proxy | "never excused because the engine's own model produced the deficit"; "Amends nothing"; scope-1 "cause, never its explanation" | PRD MISREAD (a recorded decision bearing on the point is left out) | BUILD_PLAN L167, AX44 "Accepted by Maisara 2026-11-10 (ledger P05B2-M-02)": no accuracy claim at both-flagged / layout-4 corners; debt "both-near reads low, flagged, not bounded"; L408 B15 "none scheduled". Also not shown: NFR-1 L105's "match impulse responses measured in real spaces" against the GA-internal reference, beside AX44's "GA-true, not room-true" | PRD MISREAD: re-answer | Q1 |
| M3-H | strongest objection | Seat 5 on the post-end-date fallback | answered by the seat (rates 1) | 34-seat5 §4 | must be restated; the stronger objection now is Q1/Q2 | — |
| M3-H | knowledge inventory | AX44 / B15 / C13 §2 both-near capped bias, and the "W1/layout4 both_corner asserts the cap flag" pin | missing (research gap for the board, from the plan) | L167, L408; no match for "C13", "B15" or "cap flag" anywhere in docs/review/phase-07c-2b/ | gap | Q1 |

## Questions for the decider (most consequential first)

1. **AX44 and B15.** Does the merged rule (an AX44 w or capped-branch spread is "its cause, never its explanation"; > 1 dB is breached; any fix lands before 08-4), applied to (a) at a both-near, capped layout-4 corner, amend her accepted AX44 (2026-11-10, P05B2-M-02)? AX44 makes "no accuracy claim" there, accepts "both-near reads low, flagged, not bounded", and leaves B15 "none scheduled".
   - If it does: give the PRD passage that calls for the amendment and the `AMENDS her decision of 2026-11-10` line, in a separate `FOR MAISARA` answer (decider.md §5).
   - If it does not: show why, quoting L167 and L408.
   - Either way, restate K16 and the 07e-b sentence "names the receiver side only" against L167's full GA-limit paragraph.
2. **(a)'s reference.** Under the merged text, which reference is (a) judged against? Layout 4 is non-diffuse in the corpus (Kuttruff §5.7, Table 5.2 case 4, Fig. 5.11(a); ᾱ = 0.28). The tracer is barred at a listener 0.1 m from three faces (radius 0.5 m).
   - If the answer is "none", what does "not decidable" for (a) do to the gates?
   - Put Seat 2's unanswered hand-off to Seat 9 (tracer only where the receiver is clear of every face) to Seat 9, and mark S9's cell as read from conditions until it answers.
3. **Seat 4's correction.** Will you restate the second-closest objection, §3 step 6 and the S4 register row so that 07c-2b's ABX dates are the premise-breaker and the re-hear is lifted when "07e-b rules no fix phase" (34-seat4 §2–3)?
4. **Seat 5's residual.** Will the S5 register row carry the post-end-date residual (an unrouted discrete-field flip; one board look plus possibly a fix phase; evidence in the first PR after the end date whose reason names a flip), and drop "the end date passes" as its repayment (34-seat5 §4)?
5. **Seat 5's refinement.** Do you adopt it? If so, attribute it to S5 and settle Seat 5's hand-off to Seat 7 (is a Follow-ups entry a "board loop"?) before keeping S7's later cell at 1. If not, record that Seat 5's 1 stands as rated.

## Files read
- `/home/user/makroof/docs/review/phase-07c-2b/`: 33-decider-m3h-rebuttal.md, 31-interrogator-on-file30.md, 32-seat2.md, 32-seat5.md, 32-seat7.md, 32-seat9.md, 34-seat4.md, 34-seat5.md, 29-seat1.md, 29-seat2.md, 29-seat3.md, 29-seat4.md, 29-seat5.md, 29-seat7.md, 29-seat9.md (L40–69), 29-seat6.md and 29-seat8.md (via search), 5-builder-tail-spread.md (L1–45)
- `/home/user/makroof/docs/BUILD_PLAN.md`: L37, L43 (via search), L167 (AX44), L408 (B15)
- `/home/user/makroof/docs/PRD.md` L44–113, L174
- `/home/user/makroof/docs/phases/phase-08-1.md` … `phase-08-4.md` L3
- `/home/user/makroof/docs/board/README.md` L85–132
- `/home/user/makroof/.claude/agents/decider.md` L222–257
- `/home/user/makroof/docs/sessions/2026-11-24-phase-07c-2b.md` L14–21
- `/home/user/makroof/tools/acoustics/tracer.py` L1–60
- `/home/user/makroof/src/cli/Cli.cpp` (via search, L597–647)
- `/home/user/makroof/tools/ci/abx_kit.py` (via search, L147–221)
- Corpus: `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` (§4.3 L2250–2270; §5.6 L2695–2725; §5.7 L2727–2801), `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (Table 6.1, L2056–2066)
