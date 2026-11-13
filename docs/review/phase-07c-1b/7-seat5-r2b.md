# 7 — Seat 5 position, round 2b (Q1, Q3, Q5)

2026-11-13. Saved by the orchestrator from the seat's report (re-run after the container restart; the first run was lost).

## Q1 — FM-B2 under prepare-first hosts
1. **Reading (code).** Yes: in a host calling `setActive` before `setState`, each instance runs the insertion before its restore.
   JUCE runs `prepareToPlay` inside `setActive` on the UI thread (R19). `ScenePipeline::prepare` (L812–822) sees no `restoreGen_` →
   `decide(Synchronous, load=false)`; with no `held_` / `pending_` it takes `solveStage` (L443–451, `++insertSolves`), then ISM and
   the AX49 provisional interim (L457–476), then `restartBuilder()`. The interim is provisional for `medium_room` unless L_p =
   t_mix + 0.312·T60 + 0.1 s ≥ 1.5·T60 (T60 ≲ 0.13 s) [Inferred], so the builder then starts the default scene's exact synthesis.
   `setState` → `beginRestore`/`restore` → `quiesceBuilder()` (L908, L914) abandons it at the next cancel point; `restore` then runs
   the full synchronous load (`!loadedState_`, L923–937) at record (h)'s cost. Nothing paid at insertion is reused (scene, p, s
   differ). Cues 4.3 (a lifecycle call that builds), 4.5 (an uncounted crossing: default-scene builds contend with the restores).
2. **Added serial time.** Per instance 145–430 ms (05i (iv)) on the host UI thread plus one quiesce latency (cancel-point spacing,
   [Hyp] small); 8 instances 1.16–3.44 s → run 42 macOS keyed 10 206 ms → ≈ 11.4–13.6 s vs AX38 (iv)'s 10 s. `setState`-first hosts
   (the Logic order, L815) unaffected (10 206 ms). Which hosts prepare first [Hyp] until the cond. 11 `HostTrace` read. Record (h)
   under-reports this order: it waits for every instance to settle before restoring (L1730–1734), excluding the in-flight default
   syntheses and the quiesce cost.
3. **Can a restore cancel the insertion build?** Not without silence: the insertion is synchronous and done before `setState`;
   the background part is already cancelled by the restore's quiesce. Async insertion = B2-b (Seat 6: 3); an early-only first IrSet
   is ruled out by AX47.
4. **Variant B2-a′ (C9).** A process-wide, single-flight cache of the default-scene insertion result, output-identical: shares the
   `Built` (IR, IrSet, level, and the exact units once the builder finishes); key = canonical scene incl. `tailSeed`, fs, partition
   size, `engineKey()`, platform; `shared_ptr<const>` behind a weak cache. Safe: IrSets already freed off the audio thread
   (`releaseRetired`, `RealtimeEngine.h` L21, L80–89 "switch between cached IRs"); a second instance waits at most for the first's
   running build; no lock held under the gate. Gain: 8 insertions ≈ 1 × 145–430 ms + 7 lookups; first IrSet at the first boundary,
   no fade, in each case. Test: `[pipeline]` asserts `insertSolves + insertCacheHits == 1` and bit-identity with an uncached build.
5. **Ratings.**

| option | now | later | label |
|---|---|---|---|
| B2-a + C9 named as a 07d candidate (no code now) | 1 | 1 | prefer |
| B2-a′ = C9 implemented in this phase | 2 | 0 | can live with |
| B2-a as decided | 1 | 2 | can live with |
| B2-d | 1 | 2 | can live with |
| B2-b (silent) | 2 | 2 | (Seat 6 vetoes it at 3) |

   B2-a′ now 2: a `src/` change on the prepare/decide path in a phase whose D-B4 commits no code, plus TSan work. B2-a as decided
   later 2: the prepare-first cost counted in no criterion. B2-d unchanged; C9 dominates it (same solve saved for 7 of 8, plus ISM
   and synthesis, no pinned artefact).
6. **Conditions.** B2-a → 1/1 when: record (h) prints a prepare-first total in two orders with no settle wait — interleaved (prepare
   i, restore i) and batched (all prepares, then all restores); 07d's 5 s criterion and the AX38 (iv) 10 s reading use the
   prepare-first total, with the `setState`-first total beside it; C9 named in 07d's candidate list ahead of C1. B2-a′ → 1/0 if TSan
   `[pipeline]` with 8 pipelines inserting concurrently is green and a test shows the audio thread never drops the last reference.
7. **Seat 4's condition (i) (unit decays for both outputs at insertion).** Synchronously on the host thread: 0 now / 2 later —
   unit-decay synthesis is 95.5 % of the non-diffuse restore (AX38 4c), nearly doubling the synthesis share of every insertion (up
   to +1.1–3.3 s at 8 instances in prepare-first hosts [Inferred; insertion's solve/synthesis split unmeasured]). By the builder
   after the first IrSet (output-0 first IrSet unchanged; output-1 exact decays cached when settled): 0/1; under C9 once per
   process. Condition: output-1 decays only in the background, unless the current mode needs two outputs; whether a mode switch
   inside the settling window may play an interim is Seats 4 and 3's.

## Q3 — D-B5 (iii)
On Seat 3's proxy (runs 41, 42, 44; mean 2 107.7 ms; max 2 572 ms): **M-a** ⌊1.15 × 2 107.7⌋ = 2 423 ms; run 44 over by itself (one
of three calibration runs fires); a signal firing on its own calibration data trains the reader to ignore it (how K24's warning
went unread) → re-rated **1/2, can live with** (later back to 1 with Seat 3's closure path). **S6-k prefer 1/1**, conditions: k =
max(1.15, max/mean) rounded up to 0.01 so ⌊k × mean⌋ ≥ every S2 median — on the proxy 1.22 gives 2 571 < 2 572, so k = 1.23,
trigger 2 592 ms (Seat 3's 2 571 does not meet its own rounding-up condition); k capped at 1.25 (2 634 ms), and if the spread
exceeds the cap the trigger fires and that is printed; the detection factor written in 4c: (k − 0.08)/0.92 = ×1.25 at k = 1.23,
×1.27 at 1.25; k computed by the test or a script from the GATE lines, never by hand; all figures recomputed on the real S2 runs.
The `AMENDS` reading of RG-1's "1.15 ×" is the decider's and Seat 7's.

## Q5 — do the new records need `src/`? No (test code, public stage hook, builder queries)
- **Background syntheses at each restore's start:** before the restores give each pipe a stage hook storing its last stage in an
  atomic, on builder threads only (compare the test thread's id); at the start of restore i count pipes j < i with `builderBusy()`,
  split into Solve and Assemble; label as instances, each with up to 2 emitter threads (AX49 parallel).
- **Per-stage split:** hook timestamps on the timed restore — Plan→Solve = ISM, matching, gate wait; Solve→Assemble = the solve;
  Assemble→Commit = synthesis, assembly, `makeIrSet`. Synthesis vs assembly separated by a replay through public
  `sim::StagedBuild`: `assemble()` fresh, then again with `useUnitDecays` on the cached exact units (`unitDecaysExact()`), plus
  `makeIrSet` timed separately; per-emitter figures with `parallelEmitterSynthesis = false`; labelled "replay".
- `src/` alternative (not recommended): a callback in `sim::BuildOptions` after unit-decay synthesis and a new `BuildStage`;
  deciding thread only (audio-thread-free) but it touches the restore/builder path under D-B5 (i) — S2 still wins, but it breaks
  "C7′ commits no code".

Evidence: code lines as cited; R17, R19, R21; 05i (iv); AX38 4c 95.5 %; Seat 3's GATE medians [Measured, CI]; exceedance
arithmetic own. Hand-offs: decider — plan text for the two record (h) orders and C9 in phase-07d; `insertMs` per mode in 08-4 and
an insertion read in the Phase 13 host matrix (closes P07C1B-R1-11); Seats 4, 3 — interim on a mode switch while settling; Seat
7 — the S6-k amendment. Premortem: B2-a ships uncounted; a Cubase user opening an 8-stem project waits ≈ 13 s while CI reports
10.2 s; the Phase 13 host-matrix trace notices first, after the plan is frozen.
