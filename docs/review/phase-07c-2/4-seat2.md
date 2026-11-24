<!-- Saved by the orchestrator from seat 2's report, 2026-11-22. -->

SEAT 2 POSITION (phase 07c-2, round 1). Two matters: D-W1 and D-W2.

I read the corpus through the researcher's dossier (c1b171f; R5, R29), not first-hand. Every claim below is from the code or the records unless it is tagged otherwise.

# D-W1: W_max under (C)

**Reading.** Re-pin the per-emitter work cap. Cues: cost growth (linear, cubic or flat; §4 cue 7); validation not circular (S6); measuring at scenes that never reach the cap.

**Engine facts the options must respect (fact sheets F3/T1–T3, F11):**
1. **Solve time is linear in the work actually done**, not in W. Single-thread ns per evaluation is flat from ×1 to ×16 (max/min 1.02–1.37, T2). Memory is at most 21.3 MB, against a 1 GB limit.
2. **Both gated cubes stop getting costlier.** The s 0.3 cube is uncapped from ×2 (fixed at 1.26 × the pin's work). The flutter cube reaches n\*_max at ×4 (fixed at 3.29 ×). From ×4, no W makes them cost more.
   - So **W-1 read literally ("costliest gated scene") puts no bound on W.** The 3 s must be read on a scene that spends the whole W_scene.
   - The layouts spend up to 1.031 × W_scene (T3, layout4 both_wall ×16), so the derivation must use 1.03, not AX41's 1.02.
3. **Single-thread cost at a scene that spends its full W_scene** is 43–63 ns per evaluation locally, and 44–56 ns on Linux CI (05h, F2). At ×8 (W_scene 48.8 M) that is 48.8 M × 1.03 × 60 ns ≈ 3.0 s. The T1 worst at ×8 is 2.89 s. So **W-1 ≈ ×8 ≈ 24.4 M per emitter.**
4. **W-6, accuracy, also lands at ×8.** At ×8 every capped case that is not both-near has achieved SE ≤ 0.33 dB: s=1 cube 0.13, layout 4 0.11–0.25, layout 5 0.07–0.19 dB. At ×4 they do not: layout4 listener_edge 0.378, listener_corner 0.426.
   - The both-near cases do not improve with W (VOV 0.41–0.55, SE 0.5–1.2 dB at ×16). That is an estimator problem (§9, out of scope).
   - **W-6 must exclude both-near cases, or it has no bound.**
5. **W-4 is the wrong instrument for W.** At the pin, 8 instances at 96 kHz already settle in 9.7–13.3 s (F6 b): over 10 s on Linux and macOS. Unit-decay synthesis dominates that time (1.1–1.4 s per emitter at 96 kHz). The 8 serialised solves add about 0.8 s.
   - Whether the (h) T60-8 s scene is capped is not on file, so how W-4 responds to W is unknown.
6. **Note: the fact sheet's "this container is about 2× slower than CI" comes from the nsPerEval double count.** Local pool cost per scene evaluation (15.1 ns, low-α ×1) is within the CI per-scene range (10.3–16.3 ns, Linux). F12 scaled by work ratios, so its results stand.

**Ranking**
- **W-5′ (my composite of W-1 and W-6): prefer.**
  - W_max = the largest block-aligned value at which a scene spending its full W_scene (× 1.03) costs ≤ 3 s single-threaded on the worst CI OS.
  - Accept it only if W-6 (non-both-near capped classes ≤ 0.33 dB) is met at that value.
  - W-4 and the bounce are recorded beside it; they do not set W.
  - Expected value: about ×8.
- W-1 (read as above): prefer.
- W-6 (both-near excluded): prefer, as the acceptance test.
- W-5: prefer, if W-4 becomes a recorded check.
- W-2: can live with.
- W-3: can live with, with conditions.
- W-4 as a basis: can live with only as a recorded check.

**Tension, now / later**

| option | now / later | why |
|---|---|---|
| W-5′ | 1 / 1 | Single-thread CI cost not yet measured on all three OSes |
| W-1 | 1 / 1 | |
| W-6 | 1 / 1 | |
| W-2 (×16) | 1 / 2 | 4.2–5.3 s single-thread. Under K-a a capped s=1 restore projects to 46–49 s (T5). Contradicts Seat 6's per-scene correction. |
| W-3 | 2 / 2 | At pool 4, 3 s means about ×32, beyond the measured range. Its meaning depends on hardware. Table 15.1 is a VR filter-update interval, not a solve budget (R29). Builders already cause Linux overruns (F8). |
| W-4 | 2 / 2 | Fails at (A) already. Driven by synthesis, so it cannot produce a W. |

**Keyless path (F9: the code already does K-a).**
- **K-a: 1 / 2.** The gated scenes rise by at most +0.37 s (s 0.3) and +5.6 s (flutter, 14×). But a capped scene's restore grows linearly: the s=1 cube passes 30 s at ×4–×8 (T5). The gate measures scenes that never reach the cap, so it would pass while a capped restore fails.
- **K-b: 2 / 2.**
  - It needs a second `DiffuseLimits` for stage 1.
  - Its step is the difference between two nested estimates, with σ = √(SE_A² − SE_W²). The p95 step is 1.96σ: layout4 default 0.90 dB; listener_edge 1.77 dB (0.925² − 0.212² = 0.811). **That breaks AX47's 1 dB at layout 4 whatever the ABX shows.** [Inferred, arithmetic]
  - It is not even a prefix where (A) stopped the pilot on work (F11).
- **K-c:** no position yet.

**Sequencing.** I accept deciding the value now, the keyless path after the ABX, and the golden round after both, on one condition: the constant is not committed to `src/` until the keyless path is decided. Otherwise K-a becomes the shipped path by default.

**Conditions (W-2, W-3, W-4, K-a, K-b)**
- **Any option:**
  - Measure single-thread solve medians on all three OSes (the `[wmax-sweep]` case in CI) before pinning.
  - Keep one gated scene that is still capped at the new W: the s=1 cube, capped up to ×8. This keeps the cap-hit flag and the realised-work guard ≤ 1.02 exercised.
  - Re-register the expected flags: s 0.3 cap hit 1 → 0; flutter floor-truncated 1 → 0.
- **K-a → 1/1** if the restore-gate projection includes a scene that spends its full W_scene. That is Seat 5's call.
- **W-3 → 1/1** only within the measured range (≤ ×16) and with the pool reading justified by Seat 6.
- **W-4 → 1/1** as a print-only record.

**Debt**
- **What it commits later phases to:** all capped fixtures move once, in one golden round. 07d, 08-4, 12-2 and 13 run at the new W.
- **Cost to undo:** one constant plus a golden round before release; after release, a state-version bump.
- **Where the evidence arrives:** 07c-2 CI (per-OS sweep) and 13 (release machines).
- **A gain:** at ×8 every reported layout and gated cube reaches n\*_max (T3), so any later raise keeps exact prefixes (F11).

**Companion items**
- **(b)** The timed region is `estimateDiffuse` alone (F1, from the code). The printed nsPerEval is half the true cost per scene evaluation. Across 05i → 07c-1b it shows no trend beyond run-to-run noise of about ±30 %, so it is invariant across 07c's moves. **Seat 3 does not need convening.** Pool ns per evaluation does fall with W (max/min up to 2.05, T2). So:
  - count the work once in the denominator;
  - print the single-thread figure as the invariant.
- **(c)** The S2 form is acceptable: ≥ 3 green runs on unchanged pins, k re-derived, CHANGELOG reason. Re-pin the gated scenes' exact W_pilot / W_final in D5 (flutter 10 101 864 at ≥ ×4).
- **(d)** My 07c-1 prefix claim [Inferred] was wrong as stated for pilots stopped by work: F11 holds. The golden round can test this:
  - the D5 diff must touch only open_field, asymmetric_materials, medium_room and edge_values;
  - the other 8 fixtures must stay byte-identical. Assert it.
- **(e)** Keep `pluginStateVersion` 2. The changed E_prec already makes old states load keyless (F9, F10). Either keep modelId 1 or bump it, but make the `DiffuseEstimator.h` L51–53 rule and the fingerprint comment at L2455 consistent: that comment misstates what the hash covers.
- **(f)** Confirmed: one constant holds across output modes. `DiffuseProblem` has no sample-rate or mode input (F7), so the mode affects synthesis, not W.
- **(g)** `listed` is false on `main` and true on HEAD (5b65864, F13). Fact only.

**Hand-offs**
- Seat 5: whether the restore gate covers capped scenes.
- Seat 6: per-scene reading, single thread or pool.
- Seat 8: the bounce. The F7 projection (1.21 × at ×8, 96 kHz) is an upper bound, because the bounce rooms are probably uncapped from ×2 [Hyp].
- Seat 1: whether 0.33 dB is the floor.
- Seat 3: W-4's synthesis term.

**Premortem.** If W is set by W-1 read on the gated scenes, the cap disappears in effect, and the first user to restore a 100 m low-α s=1 hall waits more than 30 s. The restore gate stays green, because no gated scene reaches the cap. Seat 5 sees it first, in Phase 13.

# D-W2: ABX design

**Reading.** The step sizes must be ones the engine actually produces, and the scene must be pinned. Cues: which parameter deviates (tone colour / level); claims must have a path to measurement.

**Engine step distribution.**
- The interim estimate is unbiased; T4 median error is about 0 dB. So steps go both ways equally often.
- Their size depends on the class:
  - gated cubes: p95 ≤ 0.25 dB;
  - capped layout 4 at (A) against the final: σ 0.46–0.90 dB, so the median |step| is about 0.3–0.6 dB and the p95 is 0.90–1.77 dB;
  - both-near: single draws of up to 3.7 dB (T3 drift column).
- **0.5 dB is the engine's typical step at layout 4, not an edge case.**

**Ranking**

| option | label | now / later | reason |
|---|---|---|---|
| X-5 over X-3, sizes 0.75 → 0.5 (→ 0.25), largest first | prefer | 0 / 1 | Tests the sizes the engine produces. Family error 0.038 (R1). |
| X-3 | prefer | 0 / 1 | |
| X-1 at 0.75 only | can live with | 1 / 2 | Leaves 0.5 dB, the median layout-4 step, unprobed. The class (c) round would then admit at layout 4 without data. |
| X-2 | can live with | 1 / 1 | Statistics are Seat 1's. Power is 0.405 at p 0.75 (R2a). |
| X-4 | can live with | 1 / 1 | A threshold maps straight onto an SE target. |

**Condition for X-1 → 1/1:** add 0.5 dB as a second step in a fixed sequence.

**Sub-items (engine side)**
- **Scene.** Commit a fixture: layout4_s1 with a named placement. It must not be both-near, since those are heavy-tailed and outside §9; I suggest default or listener_wall. Also fix tailSeed and 48 kHz, and assert that the cap is hit at the *new* W. layout4 default uncaps at ×16.
- **Step shape.** Use the same sign and size in all 8 bands. This is the conservative case: the engine's per-band signs are random and partly cancel [Hyp]. Also record the engine's realised per-band step vector at that scene.
- **How the step is applied.** Through a validation-only override of E_b, so matching and decay follow the shipped path. Seat 5 owns the flag.
- **Direction.** The engine is symmetric, so either test both directions or record why one covers the other (Seat 1).
- **Output mode: omni.** The solve does not depend on the mode. CLAUDE.md's render_cli note says stereo and binaural stay a dry stub until 08/09; Seat 4 confirms.

**Debt.** If the ABX tests only steps the engine does not produce, the class (c) round admits or rejects on the wrong evidence. The cost is a second ABX (a person's time) and rework in 08-3 and 09. Whatever the ABX shows, K-b at layout 4 already fails 1 dB on arithmetic. The evidence arrives at the 07c-2 ABX and the class (c) round.

**Evidence tags**
- Jnd 1 dB: corpus, Vorländer Table 6.1, via researcher R5.
- Step σ: [Inferred], nested-mean variance, from T3.
- Both-near behaviour: [Observed], T3.

**Hand-offs**
- Seat 1: paradigm, family and direction.
- Seat 3: crossfade law and window.
- Seat 4: chain and mode.
- Seat 5: the override flag and determinism.
- Seat 9: whether layout 4 is a plausible room.

**Premortem.** If the ABX tests only 0.75 dB and finds nothing, class (c) is admitted at layout 4. The engine's 1.77 dB p95 steps then reach users as audible jumps at settling, and Seat 6 hears of it first, from the L1 listening item.

Files: /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md, /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md, /home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md, /home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md
