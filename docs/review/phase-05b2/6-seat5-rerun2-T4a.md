# Seat 5 (deadline keeper) — re-run 2 on 4a-2G++ (incl. the offline-path hand-off)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## SEAT 5 POSITION (re-run 2)

The FIFO term makes host-thread waits grow with the number of instances, so 4a-2G++ costs me a 2 later as written. My two conditions below bring it back to 1/1.

| variant | now | later | reason | conditions (later 2 → 1) |
|---|---|---|---|---|
| **4a-2G++** | 1 | **2 as written, 1 with conditions** | Plain FIFO lets a wait on a host thread grow with the queue. That wait can be in `prepare()` or `restore()` on the message thread, in `setNonRealtime()` through `quiesce()`, or in an offline `processBlock`. With K instances queued it is up to K−1 solves plus the one in flight, and at 100 m each solve is seconds long. That pushes the synchronous stretch past pluginval's 30 s watchdog and freezes the host UI. Under 4a-2G I had not considered queue order. | (a) **Two-class FIFO.** Synchronous and offline waiters go ahead of builder-thread waiters, so a host-thread wait is bounded by one solve already running. Output does not depend on order, because each solve is a pure function of its scene. (b) **Wait can be cancelled.** A builder waiting at the gate leaves the queue when `quiesce()` is called; the condition variable's predicate checks the stop/accepting flag. So `quiesce()` waits at most for the instance's own solve if one is running, never for the queue. |

The other new terms cost my seat nothing. A waiting builder that keeps coalescing makes no difference to determinism, because real-time builds are not deterministic anyway (AQ4). Counting the gate wait as staleness and driving "settling" from it is correct. The multi-instance records are what I asked for. I would add three items to the (iv) records:
- the worst `quiesce()` latency;
- the worst wait on a host thread (prepare, restore, offline) with 1, 4 and 8 pipelines contending;
- callback p99.9 for the instances that keep playing during an offline render.

## Hand-off answer (Seat 3): an offline render waiting on the gate

**Yes, this is allowed.** A non-realtime `processBlock` has no deadline, so blocking there is legitimate (persona S5: blocking is allowed off the real-time clock). The instances playing in real time are unaffected as long as the conditions below hold:

1. **Never on a real-time thread.** In real-time mode the gate is unreachable from `process()`. From the code, the only build in `process()` is the `nonRealtime_` branch at `ScenePipeline.cpp` L400–402, and it must stay the only one. Add a test: run two pipelines, one real-time and one solving at the gate. The real-time pipeline's `process()` must make zero allocations and never touch the gate (allocation tracker, plus a debug assert on the gate that it is called only when `nonRealtime_` is set or off the audio path).
2. **Bounded wait.** Condition (a) bounds an offline or synchronous wait by one solve already running. Without (a) the bound is K solves.
3. **Offline builds never coalesce.** The offline waiter builds exactly the scene of the block it was called for. Coalescing applies to builder threads only. This keeps the bounce deterministic (AQ4, AX5), and the gate order never reaches the output. This is the decider's two-order test, run also with one pipeline offline.
4. **No deadlock.**
   - The gate is held only around the solve, never with `stateMutex_` or the builder mutex held (already in (i)).
   - The offline path takes the gate only after `quiesce()` has returned, so an instance never waits on its own builder while that builder waits at the gate.
   - Builder waits can be cancelled (condition (b)).
   - TSan `[pipeline]` with two pipelines, one of them switching to offline in the middle of a solve.
5. **Priority inversion.**
   - The gate holder is a builder thread at normal priority. A higher-priority offline or host thread waiting on it can be delayed by medium-priority work. That costs time but never a deadline, because no real-time thread ever waits.
   - Implement the gate as a mutex plus condition variable with a sleeping wait. No spin lock (Rowland: spin locks starve and invert priority).
   - Do not raise the builder's priority to compensate.
6. **Memory.** Offline solves count against the same one-solve-per-process gate, so the 1 GB transient bound holds during a bounce.

**Researcher check:** do hosts run a freeze or offline render (`isNonRealtime`) on a thread that also serves the real-time graph while other tracks play (Reaper's anticipative FX workers, Live's freeze, Logic's bounce-in-place)? If any host does, an offline wait of seconds would stall that host's real-time graph, and condition 2 would need a tighter bound. Until that is answered, this is `[Hypothesis]`.
