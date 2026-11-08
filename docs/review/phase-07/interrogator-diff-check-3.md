# Phase-07 round-3 fixes (commit 38bbbfe): interrogator diff check, round 3 (final; 2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

No WRONG or INCONSISTENT item left. Closed: P07-15b, d, e, f, g, h, i (host-threading assumption declared NOT
CHECKABLE), j, P07-4. Offline-determinism AC achievable (builder quiesced and in-flight build discarded before
reset(); one current-scene IR into an empty mailbox; computeBlock step 1 installs it at once).

| id | passage | verdict | evidence | fix | severity |
|---|---|---|---|---|---|
| BP-389 | §6 row "next IR installed at once" | IMPRECISE | omits the condition at phase-07 l. 86–88 | add "if in the mailbox before the first P samples" | minor |
| R3-1 | builder rule ("rebuild while the counter changed since its last build start") vs reset step 3 | IMPRECISE | after a discarded stale build the builder would rebuild the current scene → redundant G→G fade (realtime only) | compare against the recorded submitted generation | minor |
| R3-2 | step 3 records the generation even if the submit failed (unprepared) | IMPRECISE (premise) | a later prepare() drops IRs; a gated deferred submit could leave the fresh-instance bounce silent | record only when submit returned true; prepare() clears the record | minor |

Main session: R3-1, R3-2 and the BP-389 clause are specified fixes with no acoustic choice; they go to the
plan-editor with the decision application and are covered by the decisions' diff check.
