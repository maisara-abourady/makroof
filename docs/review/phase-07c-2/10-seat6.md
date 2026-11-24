<!-- Saved by the orchestrator from seat 6's report, 2026-11-22. -->

SEAT 6 POSITION — round 2 (phase 07c-2): (a) X-5 as decided; (b) D-W3

Read: file 8 (§4–§6), file 6 (rows on D-W2 / S6, L116 anchor check), fact sheet part 3 (m* = 6).

# (a) X-5 as decided: **can live with, 1 / 1**

X-5 as decided: noise 0.9 → 0.5 dB at 12/16; speech 0.9 → 0.5 dB at 13/16; Bonferroni split, family-wise error ≤ 0.049; 3 dB anchor at ≥ 5/6.

**Why this is not my round-1 X-2 cell (2 / 2).** I gave X-2 a 2 because a design that detects only at 13–14/16 misses a real step 60–80 % of the time at p = 0.75. The failure that costs my seat is an audible step that passes as "not detected" and then plays as a jump when "settling" clears (W4).

In X-5, detection doesn't rest on the 13/16 chain:
- The noise chain, the most sensitive stimulus, keeps 12/16 (power 0.63 at p = 0.75).
- AX47's reversal fires on a detected step below 1 dB in either chain. A noise detection at 0.9 dB is enough.
- The weaker speech chain (power 0.405) can only add a detection. It cannot block one.

**What X-5 adds over X-3:** speech evidence in every outcome. 08-3 and the class (c) round need it, and the producer's moment is program material, not noise.

**Step placement.** The step falls in a pause of at least T30 between two sentences, which leaves the tail alone in the ear. That is stricter than the L1 moment, where the step usually lands under program. I accept it as the conservative case.

**Conditions I hold for the 1** (none is needed to lower a 2):
1. The script fires AX47's reversal on a detection at 0.9 dB in **either** chain. A speech non-detection never cancels a noise detection.
2. A speech "not detected" at 13/16 is recorded with its power (0.405 at p = 0.75). It is never worded as inaudible on speech or program, in the plan, the UI or copy (Seat 7's wording, my constraint). An anchor that fails (< 5/6) invalidates that chain. It is not a "not detected".
3. No "settling" or other visual cue during trials. The step is the shipped AQ4 crossfade, in both directions, as in file 5.

**Debt.** If speech goes undetected and is wrongly read as "inaudible in program", the class (c) round could admit K-b on weak evidence. The jump would then show first at the 07c-2 L1 checklist, then at 08-3 binaural. Undoing it costs one class (c) re-decision. Condition 2 is what prevents it.

# (b) D-W3: the ISM update held behind a running solve

**Reading.** During a drag or automation in a capped large room, the icon moves and the specular part (the position cues) follows only after the running solve. That is about 590 / 810 / 813 ms at ×5 / ×6 / ×8 on the pool, and more on a busy machine. Cues:
- positions that recompute heavily (S3);
- the picture must never lie about the engine (criterion 6);
- motion is first-class (criterion 4);
- an automatic level step after the user stops (W4).

| option | rating | now / later | reason |
|---|---|---|---|
| **H-2** (decouple), with my adoption condition | **prefer** | 1 / 1 | Position cues follow the drag at once. Only the diffuse level lags, and "settling" then means exactly that. |
| **H-2** as written (adopt only if the scene is still current) | prefer, conditionally | 1 / **2** | Under continuous automation every finished solve is stale, so nothing is ever adopted. The held level then plays until the automation stops, followed by one step of the whole move's level change (W4). |
| **H-1** (cancel-on-edit) | can live with | 1 / **2** | It has the same starvation and the same end-of-move step. "Settling" stays lit for the whole automation, which tells the user nothing (S9: unmeasured). M7b is the evidence. |
| **H-0** (no change, W ≤ ×5) | can live with | 1 / **2** | Now: the hold stays under 700 ms, and U is raised only at a synthetic layout-4 corner placement, where it is true. Later: following stays tied to the solve time. Every later W or a slower user machine lengthens the hold, with no ceiling (×5 single thread ≈ 1.8 s locally). Phase 10-1 inherits it. |
| **H-3** (relax 700 ms) | can live with | 1 / **2** | 0.8 s against 0.7 s is a small difference to the ear now. But it changes the yardstick to fit the engine (rationale over measurement), and the hold then grows with W and machine load without any limit. |

**Conditions of acceptance:**
- **H-2 to 1 / 1:** adopt the **newest completed** solve whenever it is newer than the E_b now playing, even if the scene has since moved on. Then solve the newest scene. The diffuse level lags by at most about one solve, in small AQ4 equal-gain steps that motion masks, instead of one large step at the end.
  - Real-time path only. Offline and `render_cli` stay exact per block (AX5; Seat 2 and Seat 5 to confirm determinism and topology).
  - Record the per-step level change against AX47's bound.
- **H-1 to 1 / 1:** a staleness bound. A solve that has passed a set fraction of its work is not cancelled, or at least one solve completes every ~3 s (my settle anchor, by extension) under the AX38 (iv) automation patterns, as shown by M7b. The adoption step is recorded against AX47.
- **H-0 to 1 / 1:** name the owner of the hold. Phase 10-1's position path does H-2, with this hold as its acceptance test (M7 on three OSes). Record the ×5 U cell at layout-4 listener_corner as a finding.
- **H-3 to 1 / 1:** a stated ceiling (hold ≤ 1 s at the pool size on the worst shipping OS, measured by M7, not projected), "settling" visible during the hold, and H-2 named for Phase 10-1.

**Future debt:**
- **07c-2:** H-2 is a threading change, so a 07c-2b split is likely (Seat 7's schedule).
- **07d:** unaffected, apart from restore-path re-pins if the builder changes.
- **10-1:** H-2 now repays the position path Phase 10-1 would otherwise build. H-0 and H-3 move that cost there.
- **11-3:** the drawing of "settling" depends on which option wins. Under H-1 it is lit through the whole automation; under H-2 it covers only the diffuse lag.
- **13:** beta testers dragging sources in large rooms are where a wrong choice shows first.

**Hand-offs:**
- Seat 3: whether H-2 with adopt-newest meets C-a under time variance.
- Seat 5: the topology and TSan coverage.
- Seat 2: purity and determinism of the adopted result.
- Seat 8: long automated moves in practice.
- Seat 1: the audibility of the small in-motion steps.

**Premortem.** If H-0 or H-3 wins, the first producer who drags a vocal across a 60 m hall hears the position arrive about a second after the icon, more on a loaded laptop, and stops trusting the canvas. The beta tester notices first.
