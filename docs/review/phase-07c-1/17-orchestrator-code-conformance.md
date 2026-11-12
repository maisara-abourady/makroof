# 17 — Orchestrator: conformance of the condition 10/11/12 code (ee15c56) to the final decision texts (steward G4)

Phase 07c-1, 2026-11-12. The condition 10/11/12 code was written in the working tree while the decision loop ran
(file 8 header) and committed only after the plan commits d23b59d / 4ea9234 (A1's commit order). This note checks,
clause by clause, that ee15c56 conforms to the FINAL texts (BUILD_PLAN §2 after 4ea9234), so the code follows the
decisions. Where a final clause asks for behaviour that ee15c56 does not yet implement, it is listed as session 2
work, not as a conflict.

| final text | clause | ee15c56 | verdict |
|---|---|---|---|
| AX38 (i) | the gate is held only around the diffuse solve; the solve pool passed only while held | `ScenePipeline::solveAndBuild`: `StagedBuild::plan` outside, `DiffuseSolveGate::Scope` + `build.solve(&gate_->pool())` inside, `assemble()` outside; test "Condition 12 (a)" | conforms |
| AX38 (i) | class order Synchronous > Offline/Builder; "the AX48 stage-1 solve is served in class (1)" | the gate's classes unchanged (`DiffuseSolveGate.h` L46–51); restore/prepare solves enter as `Class::Synchronous`, the offline `process()` as `Offline`, the builder as `Builder`. The AX48 stage-1 solve does not exist yet (session 2, O8/O10); when it lands it is a Synchronous-source call through the same seam, i.e. class (1) | conforms; stage-1 solve = session 2 |
| AX38 (i) / condition 10 | `reset()` and `setNonRealtime(true)` never wait on the builder and never build; realtime reset keeps the IrSet; offline: drop, next `process()` builds | `ScenePipeline::reset`, `cancelBuilder`, `dropForOffline`, `setNonRealtime`; `RealtimeEngine::resetKeepIr`; tests "Condition 10: …" (both) | conforms |
| AQ10 (amended 2026-11-12) / FM-2′ / FM-3′ | restore and prepare run neither the solve nor the unit-decay synthesis synchronously, except the keyless stage-1 solve and the AX49 interim tail where no valid IrSet is current | NOT YET: ee15c56 still builds the whole IR synchronously at restore and prepare (the pre-07c-1 behaviour; only the gate's scope narrowed). This is condition 9 / 2 (O6), scheduled after condition 12's records (b), (g) by the phase's order ("records (b) and (g) are taken between the two") | no conflict; session 2 (O6) |
| AX18 (amended, FM-1) | same-scene interim → final steps equal-gain; restore over another scene's IrSet equal-power | ee15c56 creates no interim IrSet (no AX48/AX49 yet). Its only new switch: after a realtime `reset()`, a restore's request still in the mailbox crosses from the kept IrSet as an ordinary fade with the law it was submitted with (EqualPower: the restore of a DIFFERENT scene over the current IrSet, which AX18 keeps equal-power); test "Switch rule (D7), realtime … (f)" asserts that law | conforms |
| AX47 | every interim step measured on the builder thread, recorded | no interim steps exist in ee15c56 | n/a until session 2 (O8) |
| AX48 / AX49 | state v2, five-part key; provisional tail; D5 bridge; parallel emitters | not in ee15c56 | session 2 (O6, O8, O10) |
| condition 11 | "a preallocated SPSC ring written from the host entry points and drained off-thread" | `HostTrace.h`: a preallocated bounded lock-free ring with ONE consumer (the drain thread) and several producers (D. Vyukov's queue, one CAS per push), because host entry points arrive on several threads (processing, UI/message, a host's state thread), so a single-producer ring would race; nothing allocates, locks or logs on the real-time path (tracker test) | deviation in form, not in intent (steward G6): recorded here and in the PR's contractor focus |
| AX5 | offline bit-identical; `buildRoomIR` = its stages | test "Condition 12: buildRoomIR is bit-identical to its stages…"; `render_cli` outputs bit-identical to b4dd092 (file 8 / brief) | conforms |

No clause of the final texts conflicts with ee15c56; nothing in ee15c56 pre-empts a decision the loop made (the code
contains no interim level, no saved E_b, no provisional tail and no law change).

## Addendum (interrogator file 18, rows F-23, F-25, F-29, F-30)

- F-23: the condition 12 test hook is now copied once, before the gate, so nothing under the gate takes
  `stateMutex_` (`ScenePipeline::solveAndBuild`).
- F-25: `CrossfadingConvolver::reset()` no longer contains a `delete`: while a fade runs, `retiring_` is empty by
  construction (a fade starts only when it is empty; it is set only when a fade ends), so a full release queue parks
  the retired request there (asserted). Stale comments in `ScenePipeline.h` and `DiffuseSolveGate.h` corrected.
- F-29: the plan's "SPSC ring" wording (condition 11, AX38 (i) half (2)) is amended through `/fix-plan` to the
  multi-producer / single-consumer ring the code uses (reason above).
- F-30: the bit-identity evidence is local: `render_cli` built from b4dd092 (a git worktree, preset `cli`) and from
  the working tree that became ee15c56; `--mode omni` and `--mode omni-early --ir` for medium_room, club,
  concert_hall_box, large_hall, dead_booth and stone_box, the default-mode stub, a 3-seed `--ensemble` (club,
  `--tail-seed 1000`) and `--diagnostics` (club): every pair identical under `cmp` (this session, 2026-11-12). In
  CI, the existing golden and render tests run on three OSes on ee15c56 and later (run 43213141559).
