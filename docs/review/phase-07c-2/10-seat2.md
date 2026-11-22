<!-- Saved by the orchestrator from seat 2's report, 2026-11-22. -->

SEAT 2 POSITION, round 2 (phase 07c-2): (a) U2 as a term in W-C1′ and W-C2; (b) D-W3, options H-0 to H-3

**Bottom line:** U2 never binds inside the W range the other terms allow, so it can be kept as a print-only check; its 48 kHz total-bounce clause must not set W. On D-W3, I prefer H-1 (cancel on edit), then H-2 with its adoption keyed on the diffuse problem rather than the scene generation.

The fact sheets and my reading of `src/plugin/core/ScenePipeline.cpp` L252–316 and L486–557 are the sources. "Local" means the M2 and T1 runs; on corrected costs (counted once) these are inside CI Linux's range.

# (a) U2, Seat 8's bounce cap

U2 has two clauses, and they behave differently.

**Clause 1: the bounce time W adds, at layout 4 s=1, ≤ 0.25 × real time.**
- The added time is 36 × (pool solve at m − pool solve at ×1) at a capped scene. Local medians at layout4_s1/default are 118 ms at ×1, 550 ms at ×6, 748 ms at ×8 and 1397 ms at ×16. The worst capped scene at ×6 and ×8 is about 810 ms.
- Added time over the 180 s bounce:
  - ×6: 36 × (0.81 − 0.12) s ≈ 25 s, about 0.14 ×;
  - ×8: 36 × (0.75 − 0.12) s = 22.7 s, 0.13 ×;
  - ×16: 36 × 1.28 s = 46 s, 0.26 ×. Clause 1 binds only here.
- On macOS (pool of 3), scaling by 4/3 [Inferred]: ×8 gives about 0.17 ×, and clause 1 binds near ×12.
- The window U1 and U3 allow is m ≤ 10. **Clause 1 never binds inside it.**
- The bounce actually on record is the 100 m s 0.3 cube, which stops getting costlier at ×2. Its added time is at most 36 × 0.26 × 0.09 s ≈ 0.9 s. The layout-4 figure is a projection for a bounce nobody has run.

**Clause 2: the 48 kHz bounce ≤ 1 × real time on every OS.**
- Today it is 0.22–0.42 ×. The solve is only 6–8 % of it (F7); unit-decay synthesis dominates. Adding clause 1's 0.13 × at ×8 gives at most about 0.55 ×.
- **The debt:** clause 2 caps the whole bounce, not the part W adds. If Phase 08 binaural, or 10, raises per-rebuild synthesis past 1 ×, clause 2 would demand a smaller W. W would then pay for synthesis it does not cause. AX38 4c forbids that outright: "no W_max cut once pinned".

**Ratings, the same in W-C1′ and W-C2:**

| term | now / later | why |
|---|---|---|
| Clause 1 | 0 / 1 | Measures W alone and does not bind below about ×12–16. The 1 later is because the layout-4 bounce is projected, not measured. |
| Clause 2 as a W term | 1 / 2 | Makes W the shock absorber for synthesis growth in 08 or 10, which collides with AX38 4c. |
| Clause 2 as a recorded check | 0 / 1 | |

**Condition for clause 2 → 0/1:** it becomes a print-only record per OS, and a breach goes to Seats 3 and 8, never to W. My round-1 reason still stands: R14–R20 say an offline render slower than real time is a wait, not a break.

**Condition for clause 1:** state it as 36 × (S(m) − S(1)) at the worst capped scene on the worst OS, measured in the M7 or sweep CI run.

# (b) D-W3: the ISM update held behind a running solve

**Reading.** The diffuse solve is a pure function of the scene's `DiffuseProblem`: deterministic and independent of the pool (D4/D7, F2). What D-W3 decides is when its result is used, and that ties W to edit latency. Cues: cost growth (the hold rises linearly with realised work), and "precompute what does not move".

**Engine facts:**
- **The solve is thrown away under continuous automation today.** At L539 a finished solve is discarded if any edit arrived during it (`discardedMidDrag`), so the B1′ held level already plays until the automation stops. That staleness exists in H-0 and is not new to H-1.
- **The hold is the remaining time of the running solve.** That averages half a solve for an edit at a random moment and is a full solve at worst. So the hold scales with W, and every later raise of W meets the 700 ms again.
- **With cancel-on-edit the hold shrinks to one batch of blocks.** That is about 25 ms at layout 4 ×8 [Inferred]: per history ≈ W_pilot/n\* = 6.9 M / 1024 ≈ 6 750 evaluations; 64 histories ≈ 0.43 M evaluations ≈ 25 ms single-thread at 58 ns per evaluation. The hold then no longer depends on W, and U3 drops out of the W derivation.

**Ranking:**

| option | label | now / later | why |
|---|---|---|---|
| H-1 cancel-on-edit | prefer | 1 / 1 | Smallest change. Takes W out of the latency question. Its starvation is the one that exists today, not a new one. |
| H-2 decouple | prefer, with my adoption rule | 1 / 1 | Meets condition 4 literally. It is a bigger threading change (Seat 5's call). |
| H-3 relax U3 | can live with | 1 / 2 | Hold still linear in W, so every later raise reopens AQ4's rationale (an Expert question, NFR-3). |
| H-0 no change | can live with | 2 / 2 | ×5 leaves listener_corner e1 at 0.375 dB with U raised, which W ≤ ×5 cannot fix. My criterion 2 is not met in that class. |

**H-2 adoption rule (engine):**
1. **A solve becomes the final only if its problem key equals the current scene's.** The key is a hash of the `DiffuseProblem` plus E_prec and E_model, not the scene generation or a whole-scene compare. An edit that leaves the problem unchanged then does not throw the solve away. This keeps AX48's step 0 and AX5's determinism: the final always equals the solve of the current scene.
2. **A stale solve, one for a scene that has since been edited, is never a final.**
   - It may only replace the B1′ held level, as a newer held E_b. That puts it in B1′'s class: outside AX47's scope, with the step recorded.
   - This is the only rule that lets the diffuse level follow continuous automation at all.
   - Whether to use it belongs to Seats 1 and 3 (audibility of B1′ steps) and Seat 5 (threading). I offer it; I do not require it.
3. Adoption is one AQ4 step, as the decider wrote.

**Conditions:**
- **H-1:**
  - Cancellation happens only at block boundaries.
  - A cancelled solve never gives an E_b: no partial final range or pilot estimate is shipped.
  - A test asserts that a solve run to completion after an earlier cancel is bit-identical to an uncancelled one.
  - M7b records the share of solves that complete.
- **H-2 → 1/1:** rule 1 above, plus the same bit-identity test. Without rule 1 (generation check only): 1/2.
- **H-3 → 1/1:** none from my seat. Only a change that makes the hold independent of W (H-1 or H-2) removes the debt.
- **H-0 → 1/1:** record listener_corner as a known limitation with U shown. That is honesty, not a fix; it stays at 2 until the estimator is revisited (§9, out of scope).

**Debt:**
- **H-1:** one cancel path in `ScenePipeline` plus tests, built in 07c-2 (or 07d). Afterwards W can be re-derived without reference to the 700 ms. Undoing it costs one function. Evidence: M7 and M7b in 07c-2 CI, and 13 on the release machines.
- **H-2:** a threading topology that Seat 5 owns, plus TSan in 07d or 10-1. Undoing it is a phase of rework.
- **H-3:** each raise of W reopens AQ4 (13, and any later re-derivation). Undoing it costs a plan-text change.
- **H-0:** a raise later costs a golden round. Before release that is one round; after release it needs a state-version bump. The capped layout-4 class stays above 0.33 dB until then.

**Evidence tags:**
- Code facts: from the code (L486–557; L539 discard; L260 cancel pointer).
- Determinism: D4/D7 (F2, F11).
- Costs: local M2/T1 sweeps.
- Block-latency figure: [Inferred].
- macOS 4/3 scaling: [Hyp]; M7 settles it.

**Hand-offs:**
- Seat 5: H-2 topology, the gate, and TSan.
- Seats 1 and 3: whether stale-solve B1′ updates are audible, and the crossfade law.
- Seat 8: what staleness during automation means for producers.
- Seat 6: what "settling" shows during drags.

**Premortem.** Under H-0 or H-3, the next raise of W (13, or a later re-derivation) makes edit latency in large capped rooms worse again. Seat 3 notices first, in the M7 records: the ISM hold crosses 700 ms.
