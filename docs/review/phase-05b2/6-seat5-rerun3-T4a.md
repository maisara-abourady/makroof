# Seat 5 (deadline keeper) — re-run 3 on the three-class gate

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## SEAT 5 POSITION (re-run 3)

| variant | now | later | reason |
|---|---|---|---|
| **4a-2G++ with the three-class rule and my (b)** | 1 | **1** | Confirmed, and it supersedes my two-class rule (a). A synchronous host call (prepare, restore, `setNonRealtime`) still waits at most one running solve. Offline and builder waiters taking turns bounds an offline wait at about two solves, and offline has no deadline. Seats 3 and 6 are right that my two-class rule would have starved real-time instances for the length of a bounce. Because each solve is a pure function of its scene and offline never coalesces, the turn order cannot change any output. No real-time thread ever reaches the gate. |

The rating holds with the following, which I'd like stated in the AX text rather than added as new terms:
- **Several offline renders at once.** If a host renders several tracks offline in parallel, M offline waiters queue among themselves, so the offline bound is about 2M solves, not 2. Offline has no deadline, so this is acceptable, but put it in the records next to the "staleness of real-time instances during an offline render" row.
- **My earlier conditions stay part of the rule.** These are:
  - builder waits can be cancelled (b);
  - the offline path takes the gate only after `quiesce()` has returned;
  - the gate is a sleeping wait (mutex plus condition variable), with no spin lock;
  - TSan `[pipeline]` runs with two pipelines, one of them switching to offline in the middle of a solve;
  - the records include the worst `quiesce()` latency and the worst host-thread wait with 1, 4 and 8 pipelines.
