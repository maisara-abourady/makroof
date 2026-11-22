# 20 — Independent concurrency review of H-2c (steward G18)

Reviewer: an independent general-purpose agent. It read the code (`git diff c4037aa..853a586 -- src`) without the
implementer's write-up as evidence. It did not build or run anything.

**Verdict: no serious defect found.** Checked and ruled out:
- use-after-free on `owner` (`settleJobs()` runs in `quiesceBuilder()` before `builder_.reset()`; `orphanOrWait()`
  waits for `State::Done`, which is set after `execute()` returns);
- the executor outliving the gate (the destructor joins the executors before `pool_` is destroyed);
- the gate held while taking `stateMutex_` (`stateMutex_` is taken only after the gate `Scope` closes);
- a quiesce/builder wait cycle;
- a lost wake-up (`ready` is stored before `mailbox_`, and the builder clears `mailbox_` before reading `ready`;
  a missed notify costs at most one `kIdlePollS` poll);
- a final adopted after an edit (dirty == gen is checked in the task and again at reap);
- a cancelled partial result leaking into a level;
- new audio-thread locks or allocations (`process()` gains one atomic load in `hasWork()`);
- offline or synchronous output drift (share limit 0 for those classes);
- share-limit non-determinism (the pilot's stop test runs per block in index order);
- static destruction order (nothing is static).

## Findings and their disposition
| # | severity | finding | disposition |
|---|---|---|---|
| 1 | low | If `post()` throws (thread start or allocation), `job_` and `inflightGen_` stay set with no task behind them. `hasWork()` then stays false for that generation, so the builder stalls until the next edit. A failed second thread was never retried. | **Fixed:** `post` is wrapped. On throw, `job_` and `inflightGen_` are reset under `jobMutex_` and the exception is rethrown, so the next decision retries. `DiffuseSolveGate::post` starts executors while `size() < kExecutorThreads`, so a failed start is retried. |
| 2 | low | `erase_if(retired_, …)` freed the last reference to finished jobs (IR, IrSet) while holding `jobMutex_`. An offline `reset()` / `setNonRealtime(true)` through `cancelBuilder()` could then wait on those frees, a small breach of condition 10. | **Fixed:** finished jobs are moved to a local vector under the lock and destroyed after it is released. |
| 3 | info | A cancelled job stays in `retired_` until the next `decide()` or quiesce. | **Answered:** memory only, bounded by one job per superseded generation between decisions. `jobsIdle()` is correct. No change. |

Fix verification: a TSan run of `[pipeline],[diffuse]` locally, then the next manual three-OS CI run (cited in the brief).
