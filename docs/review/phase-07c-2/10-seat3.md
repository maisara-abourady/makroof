<!-- Saved by the orchestrator from seat 3's report, 2026-11-22. -->

SEAT 3 POSITION — D-W3, round 2 (lead seat)

**My answer.** H-2 meets my C-a, on one condition: M7 must be re-measured under H-2 itself and show the latency of an edit made mid-solve at ≤ 700 ms. I still prefer H-1. From the code, H-1 gives exactly the same diffuse-level behaviour as today and as H-2, and it is the cheaper change. I can live with H-2, which is your variant.

**1. Reading.** The ISM update of an edit made during a solve waits behind that solve. The cues are: state discontinuity and time variance under automation, plus cost, because the pool keeps spending its cores beside the callback.
- I accept the interrogator's correction (file 6, row C-1). An edit made during a solve waits for the solve only. The discard check at L539 runs before `finishExact` (L545) and `makeIrSet` (L547). So the hold is about one pool solve, not solve plus synthesis.
- Local hold at the capped set: ×5 590 ms, ×6 810 ms, ×8 813 ms.

**A fact from the code that changes the starvation reading of H-1.** Today, a solve that finishes after a newer edit is already thrown away: L539–543 discards it, and `discardedMidDrag` counts it.
- So under automation that moves faster than one solve, no final is adopted today either. The B1′ held level already plays until the movement stops.
- H-1 cancels at `run.stop` a solve that would have been thrown away anyway.
- So H-1 adds no starvation of the final level that does not exist now. What it removes is the ISM hold and the wasted pool time.
- H-2 keeps the same generation-checked adoption, so its level behaviour is the same as well.
- The stale level during a long drag is therefore not a property of any of these options. It follows from "never mid-drag" (condition 4, AX38 (iii)). If that rule should change, it is Seat 1's and Seat 6's matter, not D-W3's.

**2. Ranking**

| option | label | now / later | reason |
|---|---|---|---|
| **H-1, cancel-on-edit** | prefer | 1 / 1 | ISM latency becomes independent of W, so m ≥ 6 opens. Adoption is the same as today. Fewer core-seconds beside the callback (2.4 core-s per abandoned solve at ×8). The change is small: one store to `builderAbandon_` on a P- or S-changing edit, then coalescing. |
| **H-2, decouple** | can live with | 1 / 2 | It meets condition 4 as written. But every solve runs to the end even when it is doomed, which keeps all cores busy beside the callback for longer (the F8 exposure). The new threading surface (a second worker, the gate, quiesce, TSan) is debt for 07d and 10-1. |
| **H-0, no change** | can live with | 1 / 2 | At m ≤ 5 the hold stays at ≤ 590 ms, under 700 ms. But `layout4_s1/listener_corner` e1 keeps SE 0.375 dB with U = 1, which is my level debt. Condition 4's text stays false. Any later growth in ISM cost, or W, eats the 110 ms margin. |
| **H-3, relax U3** | cannot live with as stated | 2 / 3 | Table 15.1 (Vorländer §15.3) is the only sourced latency anchor: 0.25 m ÷ 0.7 s = 0.36 m/s, which sits inside the 30–50 cm/s the table assumes. It is my condition (5) from 05b2. Relaxing it to fit a ~0.8–1.4 s hold, without new evidence, trades a sourced yardstick for convenience. |

**3. Conditions of acceptance**
- **H-1, to keep it at 1 / 1:**
  - (a) Cancel only on edits that change P or S. Gain, output mode and seed edits never cancel.
  - (b) Coalesce to the newest generation, with no queue of stale scenes.
  - (c) Run M7b (the starvation record) at m = 6 and 8 and compare it with today's `discardedMidDrag` on the same patterns. If H-1 adopts fewer finals than the current code, I re-rate it to 2.
  - (d) Add `[pipeline]` and TSan coverage of cancellation while a solve holds the gate.
- **H-2, to move from 1 / 2 to 1 / 1:**
  - (a) Re-measure M7 under H-2 with the solve occupying the pool. The B1′ build then competes with the solve for cores, so the ISM latency of a mid-solve edit has to be shown at ≤ 700 ms on the worst OS.
  - (b) A doomed solve stops at its next `run.stop` once its generation is stale. That is H-1's cancel added to H-2, and it removes the wasted cores.
  - With (a) and (b), H-2 meets C-a fully.
- **H-0, to reach 1 / 1:** pin m ≤ 5, and have Seat 1 rule that U = 1 at listener_corner e1 is acceptable. That ruling is Seat 1's, not mine.
- **H-3, to drop to 2 / 2:** replace 700 ms only with a sourced or measured figure for how far early reflections can lag a source movement in a DAW. I have no incident covering it [Hyp]. Researcher route, Phase 10.

**4. Future debt**
- **07c-2:** H-1 or H-2 lands here. A fix is a code change in `src/plugin/core`, not `src/sim`; Seat 7 rules whether it is a 07c-1 defect sent on to 07d. Without H-1 or H-2, W is capped at ×5 and the floor stays unmet.
- **07d:** H-2 adds a worker topology that has to survive 07d's synthesis moves. H-1 adds one cancel path.
- **10-1:** Phase 10 sets the motion law and its gate. Under H-0 or H-3 the hold is baked into that gate. Under H-1 or H-2 the gate measures ISM latency independent of W.
- **13:** public wording on "settling" during drags is the same under every option (Seat 6, Seat 7).
- **Evidence:** M7 on CI on three OSes settles whether H-0's window exists beyond the local box. M7b settles the H-1 condition (c).

**5. Evidence**
- From the code:
  - `ScenePipeline.cpp` L315 (an edit bumps only `dirty_`);
  - L114 and L849 (the only places that set abandon);
  - L525–531 and L539–543 (mid-drag discard before L545 and L547);
  - interrogator file 6, row C-1.
- From the corpus: Vorländer §15.3, Table 15.1, and the 30–50 cm/s movement speed.
- Hold times: decider file 8 §5 (local, Linux, 4 threads) [Observed locally; CI pending, M7].
- The claim that the stale level is the same today as under H-1 and H-2 is [Inferred] from the code. M7b verifies it.

**6. Hand-offs**
- Seat 5: the H-2 topology, quiesce and cancel races, TSan.
- Seat 1: whether "never mid-drag" should give way on long automation.
- Seat 7: which phase owns the fix.
- Seat 4: the binaural ISM cost under 700 ms in Phase 08.

**7. Premortem.** If H-0 is adopted and later work pushes the ISM build or W up, the 110 ms margin disappears. Early reflections then visibly lag automated moves in capped large rooms, and Seat 6's users notice first.
