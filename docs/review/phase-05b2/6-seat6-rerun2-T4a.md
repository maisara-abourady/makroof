# Seat 6 (canvas designer) — re-run 2 on 4a-2G (interrogator Q1)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 6 POSITION (re-run 2)

The decider's carried 1/1 for 4a-2G is a misread: I rate it **1 now, 2 later**. The gate stops memory adding up across instances, but under 4b-2 it makes each instance's edit-to-hear delay depend on how many other instances are rebuilding at the same moment. My condition for later 2 → 1 is in the table.

| variant | now / later | reason (measure: how long the user waits between an edit and hearing it) | condition (later 2 → 1) |
|---|---|---|---|
| 4a-2G | **1 / 2** | **Now 1:** with one solve in flight per process and a solve in every rebuild (4b-2), the last instance waits about (k − 1) solves when k instances rebuild together. Prototype scale (builder evidence `7-builder-D-T1-evidence.md` §4, for scale only, not a D-T1 rating) is ≤ ~30 ms per emitter in typical rooms. Eight instances then queue roughly 0.4–0.5 s, inside my tolerance, and a project load loses no work (it agrees with Seat 8's reading) [Inf]. **Later 2:** at that prototype's worst case (≈ 1.5 s per emitter, layout 4 at s = 1), the queue reaches seconds. Instances automated together (position or room size) become a staircase that grows with instance count. The user hears a cheap room lagging behind someone else's expensive one, with nothing on its canvas to say why. Phase 10's automation suite runs one instance, so it would not catch this [Inf]. Undoing it later (priority or fairness in the gate) is a builder rework in Phase 10 or 13. | (1) The gate is FIFO-fair at solve granularity, so an instance under continuous automation cannot starve another instance's edit. (2) The time spent waiting at the gate counts in Phase 10's "IR staleness" metric and drives the UI's "settling" state, so the wait is visible on that instance's canvas. (3) Under 4c-1C, also record two times, with 4 and 8 instances, and escalate them against the same 1 s / 3 s / 10 s marks: the time until the last instance is audible at project load, and the staleness when the instances are automated together (position and room size). |
