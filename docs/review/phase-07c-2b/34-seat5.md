# 34: Seat 5 on the end-dated red clause (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (follow-up on M3-H: the end-dated AC clause. Read-only; for the orchestrator to save as /home/user/makroof/docs/review/phase-07c-2b/34-seat5.md)

**1. Reading.** My 32-seat5 sentence now applies only until 07e-b is `done` and any fix phase it names is `done`. After that, the rule is update-with-reason plus a §6 row. The reason must say whether any discrete field changed (`ismFallback`, k_real crossing 19, the both-near or capped flag), and there is no board look. Cues: §4.5 (who owns the baseline at each crossing) and criteria 2 and 4 (determinism; one person can check the gate mechanically).

**2. Ranking.** H4+G with the end-dated clause: **prefer. I accept it.** H3+G is unchanged (can live with). The clause is common to both, so it does not separate them.

**3. Tension now.** H4+G: **0**. Nothing changes on the audio thread or in the per-run pytest, and my 32-seat5 §6 pytest-scope condition is still met (Item A1 AC1).

**4. Tension later (the debt).** H4+G: **1**.
- Why the end date does not raise it: in 32-seat5 §1 I objected that bare update-with-reason lets the JSON move "without anyone asking whether the ruling still holds". That applies while a ruling is pending or a fix is in flight. That is the window the clause now covers verbatim, with the split edit ("07e's findings and 07e-b's ruling"), which I accept.
- After 07e-b and its fix are `done`, the JSON is an ordinary golden. CLAUDE.md's golden rules already govern it (update_goldens.py, a reason, a §6 row, never regenerated just to pass).
- The decider's clause keeps the one thing I said a stated reason misses: a discrete-field flip now has to be named in the reason. That puts it in front of the contracted engineer, who is my 32-seat5 §8 premortem reader.
- What stays as debt: after the end date, a discrete-field flip is recorded but no gate stops it. If one happens, it reopens NFR-8 (L112) on the code path 07e-b judged. Undoing that costs one board look plus possibly a fix phase. The evidence would arrive in the first output-changing PR after the end date whose reason names a flip.
- That is inside 1: the flip is visible, attributable to one PR, and reproducible (AX5, same runner).

**5. Evidence.**
- Item A1 AC (file 33 L215): the end date, the post-date wording and the discrete-field clause.
- File 33 §2 L75–81 (the reconciliation) and §4 L142–149 (the strongest objection).
- My earlier positions: 32-seat5 §1, §4 and §6; 29-seat5 §4 (my update-with-reason wording).
- AX5: bit-identity holds only on the same OS and architecture, so a flip on the producing runner is a real change, not noise.
- [Hyp] Discrete-field flips after the ruling are rare. Not measured.

**6. Conditions of acceptance.** None required: no cell is rated 2 or 3. One refinement, not a condition, that would make the clause mechanical rather than remembered:
- The 07e pytest's failure output should list by name which discrete fields differ from the JSON. The PR's reason then comes from tool output.
- Where one does differ, the PR should list it under Follow-ups as an NFR-8 candidate for the board, without blocking the merge.
- This keeps Seat 7's "no board loop" and adds nothing to a PR in which no discrete field changed. If the decider prefers not to adopt it, my 1 stands as rated.

**7. Hand-offs.**
- Builder: printing the names of the changed discrete fields in the pytest failure message.
- Seat 7: whether a non-blocking Follow-ups entry counts as a "board loop" for its later cell.
- Seat 2 (Lead): whether a post-ruling flip of k_real across 19 is enough on its own to reopen (b).

**8. Premortem.** Suppose a later phase flips `ismFallback` for a near-face emitter after the end date. The reason names it, but no one routes it. The rule is still met and NFR-8 regresses quietly on the geometry 07e-b judged. The contracted engineer would notice first, comparing the reason in the PR against 07e-b's ruling.

Files read: /home/user/makroof/docs/review/phase-07c-2b/33-decider-m3h-rebuttal.md (L60–219), /home/user/makroof/docs/review/phase-07c-2b/32-seat5.md.
