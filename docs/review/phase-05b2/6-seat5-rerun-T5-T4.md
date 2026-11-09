# Seat 5 (deadline keeper) — re-run on the decider's composed variants (5.1-A*, 4a-2G, 4c-1C)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## SEAT 5 POSITION (re-run)

I confirm all three cells as the decider read them: 5.1-A* at 1/1, 4a-2G at 1/1, 4c-1C at 1/2. The reason for each is in the table; two of them carry an implementation note that does not change the rating.

| variant | decider's reading | my cell | one-line reason |
|---|---|---|---|
| **5.1-A*** | 1/1 | **1/1, confirmed** | The condition covers `render_cli` too, which answers the decider's strongest objection. Because `buildRoomIR` sets its own FTZ/DAZ, every path gets the same FP mode: the builder thread, the synchronous prepare/restore, the offline `process()` and `render_cli`. The bit-identity gate in 4c-1C covers the outputs. Implementation note: the mode must be restored by a scoped guard (RAII), so that the caller's mode also comes back when `buildRoomIR` throws (AX34 rates). The test room must be absorbent enough that denormals actually occur without FTZ. |
| **4a-2G** | 1/1 | **1/1, confirmed** | It meets all three of my terms: one diffuse solve in flight per process, ≤ 128 MB resident per instance, and callback p99.9 recorded under concurrent builders. The Bitwig gap is accepted at 1. Implementation note: hold the gate only around the solve itself, never while holding `stateMutex_` or the builder's mutex, so that `quiesce()` and the offline path cannot deadlock. A TSan `[pipeline]` test with two pipelines should cover this. |
| **4c-1C** | 1/2 | **1/2, confirmed** | Later stays 2 because the synchronous restore and prepare at 100 m, 96 kHz are still not gated. Today's 1.51–1.88 s already sits close to the ≈ 2.1 s per restore that pluginval's 30 s watchdog allows. It drops to 1 only if Maisara accepts Challenge 1. I am adding one item to the records: under 4a-2G, a synchronous restore can wait behind another instance's solve, so the restore time should also be recorded in that contended case (a second pipeline solving the 100 m room at the same time). |
