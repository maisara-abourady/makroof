# Seat 3 (reverb renderer) — re-run 2 on 4a-2G (interrogator Q1)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 3 POSITION (re-run 2)

I rate 4a-2G at 1/2 as it stands, and at 1/1 if one record and two scheduling rules are added. The decider carried my 4a-2 cell over, so this replaces it.

| variant | rating (now / later) | reason | condition (later 2 → 1) |
|---|---|---|---|
| 4a-2G | **1 / 2** | **Now 1:** the per-process gate caps peak memory at about 1 GB however many instances there are, which serves my cost criterion and removes the out-of-memory stall-then-jump risk I raised under 4c-3. Nothing clicks, because a queued instance keeps its last IR and still crossfades over 30 ms (AQ4). **Later 2:** under 4b-2 every rebuild contains a diffuse solve. With n instances rebuilding together, the last one in the queue waits about (n−1)·R_d first, so its staleness becomes about 2R + 2P + (n−1)·R_d [Hyp], where R_d is the length of one diffuse solve. Each update is then a bigger jump, which raises the AX18 dip risk. Phase 10's staleness and position-fade gates use single-instance scenarios, so nothing measures this. | **Record:** add per-instance staleness, not only callback p99.9, with 1, 4 and 8 instances rebuilding together, in the AQ10 room and at 100 m, at 48 and 96 kHz. **Scheduling rules:** (a) an instance waiting for the gate keeps coalescing and solves its newest scene when its turn comes, never a stale one; (b) the gate serves instances in arrival order, so no instance waits indefinitely. With these the rating is 1/1. |

Two points go to Seat 5:
- **Non-realtime processBlock waiting on the gate:** a track freeze or offline render can run while other instances play in real time. A non-realtime processBlock would then wait on a gate held by another instance's builder thread. Seat 5 should check that this is allowed.
- **Determinism:** gate order must never change any output.
