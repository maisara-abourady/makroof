# 10 — Seat 5, round 3 (phase 07c-1, on decider file 9 §6)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-3 questions: file 9 §6.

SEAT 5, round 3. Neither cell is a 3, so nothing goes to Maisara.

- **D3\*′: I correct my cell from 1/1 to 2/2 (major, not veto-grade).**
  - Criterion 1, the audio deadline, is untouched. The synchronous build runs on the host thread only where no IrSet is current, and the realtime `process()` takes no lock. My rating comes from criterion 3, host conformance.
  - The measured cost is about 0.65–0.8 s per instance. With 8 instances restored in sequence that is about 5–6.5 s [Inf]. That passes Windows' 5 s not-responding criterion (F13) if a host restores on its UI thread outside a progress dialog. Whether any host does is [Hyp] until the condition 11 trace.
  - The debt lands at the Phase 13 host matrix. If a dialog shows up there, the fallback is the early-only gap, which three seats vetoed. Undoing this is therefore a re-convened board decision, not a parameter change.
  - **Condition that lowers it to 1/1:**
    - run the two emitters' provisional syntheses in parallel, outside the gate. This would roughly halve the per-instance time [Hyp]; it must be shown bit-identical to the serial build;
    - record (h) prints the wall time of 8 instances restored in sequence on all three OSes, plus the keyless variant, and flags any run over 5 s. The flag is printed, not asserted;
    - reversal 2 stays as written.

- **K2: 1/1 confirmed (now 1 / later 1).**
  - The synchronous stage-1 solve adds about 81–131 ms per instance, and only at keyless loads.
  - Restores done in sequence on one thread do not queue on each other. The roughly 1 s gate-queue figure applies only if they run concurrently with the background solves of instances already loaded. AX38 (i) should give the synchronous class priority at the gate; if it does not, I would rate 1/2.
  - The added solve brings the D3\*′ worst corner to about 0.75–0.93 s per instance and about 6–7.5 s for 8 [Inf]. That falls under D3\*′'s 2 above, not K2's.
  - Every cross-OS or cross-fs reopen is now keyless, so record (h) must time the keyless variant as well. That is already in my D3\*′ condition.