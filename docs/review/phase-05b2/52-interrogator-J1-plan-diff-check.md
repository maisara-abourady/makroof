# Interrogator — document mode, diff check of the J1 plan edits (3a28f1b..bf3f5bd)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, document mode: diff check of the J1 plan edits (`git diff 3a28f1b HEAD -- docs/BUILD_PLAN.md docs/phases/`)

The plan edits carry J1 faithfully: every condition in 47 §4 (i)–(iii) and every item in 51 §4 1–9 is present, the numbers from 51 §2/§3 are copied correctly, and phase-07c is self-contained. Two problems must be settled before the restore gate is implemented, and both come from the decision text itself, not from the plan-editor:

- **The "W_max below Seat 1's floor → Maisara" trigger is already met today at the gated 100 m cubes**, so as written it fires on day one.
- **Phase 12's reopening trigger** ("a hall preset in the capped class reopens the board answer") now covers every preset near 100 m, which file 51 §2 does not intend.

There are also five smaller fixes the plan-editor can make through /fix-plan.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Checked:** the changed passages only, against 47 §4 (i)–(iii), 51 §2–§4, my file 49, and the `c16` data.

### Verdicts per passage

| passage | verdict |
|---|---|
| AQ10 amendment (board-answer citations, G1 closed, the J1 gate conditions) | CORRECT: all 47 §4 (i) / 51 §4 item 1 conditions present, plus correction 8 (a)/(b). The trigger wording inherits correction 1. Stray ".;" after "frozen)" (correction 7). |
| AX38 4c (same conditions; board-answer citation) | CORRECT; inherits correction 1 |
| AX41 W_max basis ((A) = restore budget less D-H1's margin, pinned, re-derived once under (C), never a time cap) and n\*_max (Q2b (i)) as board answers | CORRECT: 47 §4 (ii), 51 §4 item 2 |
| §0 row 07c (M, deps 05h and 07, before Phase 13's beta, ahead of Phase 08's golden freeze, forward on any gate failure) | CORRECT |
| §4 entry 07c | CORRECT |
| §4 entries 05h and 13 | CORRECT |
| §6 row | CORRECT |
| phase-05h §1 (citations; Q2a (C) moved to phase-07c) | CORRECT |
| phase-05h §2 item 1 | IMPRECISE: correction 3 |
| phase-05h §3 D-H1 (margin rule, ≥ 10 runs, 20 % trigger, expected ≈ 27 %, SE +17 %) | CORRECT: 51 §3 arithmetic, e.g. 1/√0.73 = 1.17, 1.33 → 1.56, 0.50 → 0.58 dB |
| phase-05h §4 scope 2, solve seam | CORRECT |
| phase-05h §5 (gate wording; seam criterion) | CORRECT |
| phase-05h §9 | CORRECT |
| phase-08 scope 10 and its AC (heaviest mode, one W_max, 07c brought forward, never cut, SE-derived golden tolerance) | CORRECT: 51 §4 item 5 |
| phase-11 (U's note reaches the editor, Seat 8's later 1) | CORRECT: 51 §4 item 6 |
| phase-12 scope 7, re-run under 07c's W_max once landed | CORRECT |
| phase-12 capped-class check | INCONSISTENT: correction 2 |
| phase-13 dependencies (07c), raise item 4, scope 13 | CORRECT, one INCONSISTENT: correction 4 |
| phase-07c §0, §1, §3, §5 (conditions 1–8, the phase-10 / AX38 (v) cross-reference), §8, §9, §10 | CORRECT: faithful to 47 §4 (iii) and 51 §2 L3/L5; numbers at n\*_max 1 024 |
| phase-07c §2 (raise only if it slips past release unversioned) | CORRECT |
| phase-07c §4 (D-C1 Seat 1's step ruling; D-C2 interim level / saved E_b with a state-version AX; D-C3 Seat 8's saved-state question; researcher questions) | CORRECT; the labels are acceptable. "Researcher questions before D-C1–D-C3" is the plan-editor's ordering, not in 51 (correction 6). |
| phase-07c §6 acceptance criteria | CORRECT translations of conditions 1–8, except the last item (correction 5). The added standard gates (allocation tracker, TSan, pluginval, auval; old state fixtures load) are consistent with AX38 and the Phase 07 rules. |
| phase-07c §7 listening items | CORRECT: they follow conditions (iii) 4, 5 and 6. "No obvious jump" stays subordinate to D-C1. |
| phase-07c size M (one phase of Phase 07 rework; Phase 07 is M) | CORRECT, not an overreach |

### Corrections

1. **Settle before the gate is implemented; this goes to the decider, because it is a definition in the board answer.**
   - The condition "if the non-diffuse build alone leaves W_max below Seat 1's floor (SE ≤ 0.33 dB with VOV < 0.1) at a gated scene, the result goes to Maisara" comes from 47 §4 (i) and Seat 6 (a). Its 51 §3 variant reads "a margin that leaves W_max below Seat 1's floor at a gated scene".
   - Both are already true at the provisional W_max (A). At the gated 100 m cubes, C16 (n\*_max 1 024) gives a pilot VOV of 0.47–0.59:
     - closed low-α cube at s = 0.3: SE 0.14 / 0.09 dB, VOV 0.47 / 0.48;
     - α 0.10–0.22 cube: VOV 0.55 / 0.59.
   - The VOV part of the floor therefore fails today; 34 D-T1.3 already records "the VOV part in the closed cubes" as failing Seat 1's floor.
   - As written, the escalation fires on day one. The decider must define the trigger by one of:
     - the SE part only;
     - Seat 1's floor as measured at the provisional W_max (A), i.e. "further below than at (A)";
     - an explicit list of what counts as "below the floor".

   Then AQ10, AX38 4c and phase-05h §2/§3 need to be aligned.
2. **phase-12 capped-class trigger (INCONSISTENT between 47 and 51 as composed; settle before Phase 12).**
   - The text "a hall preset in it [the capped class] reopens the board answer" takes 47's strongest-objection trigger. File 51 §2 L5 has since widened the capped class to include rooms near 100 m, which are capped at SE ≤ 0.15 dB with U silent.
   - So any hall or arena preset near 100 m would reopen J1. That contradicts 51 §2: "Only the former [long-window s = 1 layouts], and the low-α s = 1 cube, carry errors above 0.33 dB".
   - Restate the reopening trigger as "a hall preset in the capped class with achieved SE > 0.33 dB (U fires)". Capped presets near 100 m at SE ≤ 0.15 dB are reported only.
   - The decider should confirm this reading, since it narrows 47's text.
3. **phase-05h §2 item 1 against §3 (IMPRECISE).** §2 gives only the non-diffuse-build trigger. §3, following 51 §3, gives "the margin leaves W_max below Seat 1's floor". List both triggers in §2, subject to correction 1.
4. **phase-13's dependency against its fallback (INCONSISTENT).** phase-13 now depends hard on 07c, but scope 13 and raise item 4 keep the branch "if it has not landed, the estimator parameters are versioned in saved state before release". With a hard dependency that branch can never be reached. 47 §4 (iii) 1 gives both: a beta prerequisite, otherwise versioning. Make the dependency "07c `done`, or the versioning fallback of scope 13 recorded", or drop the fallback.
5. **phase-07c §6, last criterion (conditions violated).** "The Phase 12 (ii) preset check re-run under the new W_max and reported" is unconditional. 07c depends only on 05h and 07, so it can land before Phase 12 exists. Make it conditional: "if Phase 12 has run; otherwise Phase 12 runs it at 07c's W_max". phase-12 scope 7 already says this.
6. **phase-07c §4 (plan-editor ordering).** "Researcher questions (before D-C1–D-C3)" is not in 51 §4 item 9. Mark it as the plan-editor's ordering, or drop "before".
7. **Small edits.**
   - **phase-10 has no cross-reference.** 51 §4 item 4 asks for a cross-reference between (iii) 4 and phase-10's split update / AX38 (v). Only the 07c side has it; add a pointer from phase-10 to phase-07c so the split update is not designed twice.
   - **AQ10 punctuation.** Remove the stray ".;" in AQ10.

Corrections 1 and 2 need the decider; 3–7 can be applied by /fix-plan.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-J1FX-01 | AQ10 / AX38 4c J1 conditions (47 §4 (i), 51 §4 item 1, correction 8 (a)/(b)) | CORRECT | closed |
| P05B2-J1FX-02 | AX41 W_max basis and n\*_max as board answers; G1 closed | CORRECT | closed |
| P05B2-J1FX-03 | phase-05h §1, §3 D-H1 (margin rule, 20 % trigger, ≈ 27 %, +17 % SE), §4 seam, §5, §9 | CORRECT | closed |
| P05B2-J1FX-04 | phase-08 scope 10 / AC; phase-11 note to editor; phase-12 re-run under 07c's W_max | CORRECT | closed |
| P05B2-J1FX-05 | phase-07c faithful to 47 §4 (iii) 1–8 and 51 §4 items 4, 9; size M; labels D-C1–D-C3 | CORRECT | closed |
| P05B2-J1FX-06 | "W_max below Seat 1's floor at a gated scene → Maisara" already true at (A) (gated cubes VOV 0.47–0.59, C16) | INCONSISTENT: decider defines the trigger before the gate is implemented | open |
| P05B2-J1FX-07 | phase-12 "hall preset in the capped class reopens J1" against 51 §2 (100 m rooms capped at SE ≤ 0.15 dB) | INCONSISTENT: decider confirms the restatement | open |
| P05B2-J1FX-08 | phase-05h §2 item 1 lists one trigger, §3 another | IMPRECISE (/fix-plan) | open |
| P05B2-J1FX-09 | phase-13 hard dependency on 07c against its versioning fallback | INCONSISTENT (/fix-plan) | open |
| P05B2-J1FX-10 | phase-07c §6 unconditional Phase 12 re-run | CONDITIONS VIOLATED (/fix-plan) | open |
| P05B2-J1FX-11 | phase-07c §4 "researcher questions before D-C1–D-C3" (plan-editor ordering) | IMPRECISE (/fix-plan) | open |
| P05B2-J1FX-12 | phase-10 lacks the pointer to 07c; AQ10 stray punctuation | IMPRECISE (/fix-plan) | open |

Files:
- /home/user/makroof/docs/BUILD_PLAN.md (AQ10, AX38 4c, AX41, §0 row 07c, §4, §6)
- /home/user/makroof/docs/phases/phase-07c.md
- /home/user/makroof/docs/phases/phase-05h.md
- /home/user/makroof/docs/phases/phase-12.md
- /home/user/makroof/docs/phases/phase-13.md
- /home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md
- /home/user/makroof/docs/review/phase-05b2/51-decider-addendum-J1.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json (section `c16`)
