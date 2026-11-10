# Interrogator — document mode, diff check of the branch-review fixes (14122cb..5f96d7b)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, document mode: diff check of the branch-review fixes (`git diff 14122cb HEAD`)

The fixes are faithful: majors 1, 2 and 4 and minors 1 and 4 are applied as the review asked, and nothing new is invented.

One gap remains, and it sits in the passage you asked me to check. The plan now lets Phase 08 run before 05h, but the J1 "golden freeze" rule still names only Phase 08's goldens. In the 08-first order the binaural goldens that actually ride on W_max are the ones phase-05h re-renders, and the plan says neither that phase-07c must land before those are frozen nor that this follows from Seat 4's conditions. It can be fixed through /fix-plan with one confirming line from Seat 4 (or the decider). No numbers or thresholds change.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

### Verdicts per passage

| passage | verdict |
|---|---|
| AX16 (major 1): "switch decided … implemented in phase 05h … until 05h is `done` the shipped tail level is still AX16, ΔL_b,tr a known deficit"; 05h added to the breaks column | CORRECT, as the review asked and consistent with phase-05h §1 |
| report-phase05b.md and its generator (major 2): session-1 line kept and marked "session 1"; new session-2 outcome line from one `SESSION2` constant | CORRECT. R1 at 2.5 m in CR2/CR3/CR4 at 500 Hz–2 kHz at the Phase 05 positions (§5b); R2 = D-T1.1 (AX39); switch decided, implemented in 05h; `src/sim` still on AX16 until then. "switched" does not occur, so `test_window_check_follows_ax35` still holds |
| phase-08 scopes 9 and 10 and their two criteria, conditional on 05h `done`, otherwise carried by phase-05h scope 10 (major 4) | CORRECT; the Phase 08 session can meet its criteria in both orders |
| phase-05h scope 10 extension and new §5 criterion (carries phase-08 scopes 9 and 10 when Phase 08 went first) | CORRECT: content taken from phase-08 scopes 9/10, AX38 4c and AX37 (5.3) (iii), not new decisions. One gap: correction 1 |
| phase-07c §3 ("comes forward only after 05h"; in the 08-first case the heaviest-mode gate runs in phase-05h scope 10) | CORRECT, consistent with 07c's dependency on 05h |
| phase-05b2 §9 note (Q2a (C) is phase-07c) (minor 4) | CORRECT |
| §6 row, CLAUDE.md determinism exception (minor 1) | CORRECT: matches AX40 and AX5 |
| §6 row, branch-review fixes | CORRECT ("no value, threshold or golden changed") |

### The 08-first ordering against AX37 (5.3) and J1

- **AX37 (5.3), Seat 4's (i)–(iv):** Phase 08 may go first; 05h then re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8. The new 05h scope 10 does exactly this.
- **What the new 05h scope 10 adds.** It adds the phase-08 scope 9 records and the scope 10 heaviest-mode gate. This is a necessary consequence: the gate and W_max exist only in 05h. It is not an invented condition.
- **phase-07c.** It depends on 05h, so "forward only after 05h" is the only coherent reading.

### Correction

1. **The J1 freeze point in the 08-first order (IMPRECISE; /fix-plan, with one confirming line from Seat 4 or the decider).**
   - **What J1 says.** AQ10 (amended) and AX38 4c still say, unqualified: "if Phase 08's heaviest-mode build makes the pinned W_max fail the gate, (C) lands before Phase 08's goldens are frozen". That comes from 47 §4 (i) and Seat 4's S4-c: "no binaural golden is built on a W_max that later changes".
   - **Why it does not fit the 08-first order.** Phase 08's goldens are frozen before 05h exists (on the AX16 tail, provisional). The binaural goldens that ride on W_max are the ones phase-05h scope 10 re-renders, and 07c can only follow 05h.
   - **What 05h scope 10 says today.** It states only the second branch: capped-room goldens carry the SE-derived tolerance unless 07c has landed. It does not say that a heaviest-mode gate failure in 05h brings 07c forward before those re-rendered goldens are frozen.
   - **Fix.** Qualify the parenthesis in AQ10 and AX38 4c as follows:
     - in the 05h-first order, before Phase 08's goldens are frozen;
     - in the 08-first order, before phase-05h's re-rendered binaural goldens are frozen, or those goldens carry the SE-derived tolerance.

     Then add the same rule to 05h scope 10.
   - **Why a seat should confirm.** This maps Seat 4's S4-c and R3 conditions onto the order AX37 (5.3) allows. Seat 4 rated those conditions with 05h first in view, so a one-line confirmation from Seat 4 (or the decider) is needed.

Major 3 (the JSON sections with no producing step) and minors 2, 3 and 5–7 are not in this diff, so I have not checked them.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-BR-01 | AX16 decided / implemented in 05h / shipped level still AX16 until 05h `done`; breaks column gains 05h (major 1) | CORRECT | closed |
| P05B2-BR-02 | report-phase05b session-2 outcome line and generator `SESSION2`; session-1 line marked (major 2) | CORRECT | closed |
| P05B2-BR-03 | phase-08 scopes 9/10 and criteria conditional on 05h; carried by phase-05h scope 10 and its new §5 criterion (major 4) | CORRECT | closed |
| P05B2-BR-04 | phase-07c §3: comes forward only after 05h; heaviest-mode gate in phase-05h scope 10 if 08 went first | CORRECT | closed |
| P05B2-BR-05 | J1 freeze-point rule (AQ10, AX38 4c) unqualified for the 08-first order; 05h scope 10 states only the SE-tolerance branch | IMPRECISE: /fix-plan, Seat 4 / decider to confirm | open |
| P05B2-BR-06 | phase-05b2 §9 note (minor 4); §6 CLAUDE.md determinism row (minor 1) | CORRECT | closed |

Files:
- /home/user/makroof/docs/BUILD_PLAN.md (AX16, AQ10, AX38 4c, §6 rows)
- /home/user/makroof/docs/phases/phase-05h.md (scope 10, §5)
- /home/user/makroof/docs/phases/phase-08.md (scopes 9, 10)
- /home/user/makroof/docs/phases/phase-07c.md (§3)
- /home/user/makroof/docs/validation/report-phase05b.md
- /home/user/makroof/tools/validation/report_phase05b.py
