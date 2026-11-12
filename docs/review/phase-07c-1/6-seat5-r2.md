# 6 — Seat 5, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 5, round 2: changed cells only.

- **C5′ (AX47): 1/1, confirmed.** The decision meets my conditions: the step is measured and recorded on the builder thread, never in the callback, and the admissible sources are bounds known at design time rather than a runtime check, which addresses my C2 objection.

- **D3\* (AX49): I correct this to 2/2 as written. It drops to 1/1 when the gap below is closed.**
  - **Conditions met.** The provisional runs outside the gate, its cost is in records (c), (d) and (f), there is an offline-bypass test, and the submit rules are there: an interim submit does not mark its generation handled, and every submit passes a monotonic (generation, stage) check under `stateMutex_`.
  - **The gap.** Building the provisional synchronously needs an interim level.
    - For a v1 project, or a P/S/E key mismatch, AX48 B4 gives that level as the (A) solve.
    - Done synchronously, that solve is 81–131 ms per instance with the gate held. At 8 instances it queues to about 1 s (8 × 131 ms) on the host thread. That breaks A2, which says restore never runs the diffuse solve synchronously.
    - If instead it is not done synchronously, the first IrSet has no tail, which breaks condition 9 for v1 states that had one.
  - **Two ways to close it.** Either works for me.
    - (a) For these cases the first IrSet is early-only, and the provisional follows from the background solve. The tail-less window must be stated as the background solve plus the gate queue (about 0.1–1 s at 1–8 instances [Hyp]), and the interrogator rules whether condition 9 tolerates it for keyless states.
    - (b) AX49 names an explicitly synchronous solve for keyless loads only, and A2 and the restore gate are amended to measure it.
  - **The synchronous time is per instance and adds up at load.** The 0.5 s reversal should be read on 8 instances restored in sequence on one host thread, not on 1 instance. That waits for R1 and R3; until then it is [Hyp].

- **Seat 7's split key policy** (a saved E_b stays authoritative on an engine-part mismatch):
  - **As AX48 composes it** (the format now, the policy decided before the first post-release change to E): 0/1.
  - **Adopted as the policy:** 1/2. The later 2 is my undo issue. Edit, then undo back to the saved scene: the edit invalidates the saved E_b, the scene re-solves with the new engine, and one scene renders two levels in one session. A plugin bounce and `render_cli` of the same project would also differ.
  - **Condition that brings the adopted policy to 1/1:**
    - the saved E_b is held as a cache keyed by S that survives edit and undo within the session;
    - offline uses the same rule as playback;
    - the render log records that the level came from a saved E_b at engine id E_old;
    - the CI fingerprint test stays in place.