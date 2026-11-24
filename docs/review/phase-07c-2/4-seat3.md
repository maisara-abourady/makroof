<!-- Saved by the orchestrator from seat 3's report, 2026-11-22. -->

SEAT 3 POSITION — Phase 07c-2, round 1 (D-W1 and D-W2)

Corpus is present (c1b171f). I read Vorländer §15.3, Table 15.1 myself. Everything else here comes from the fact sheets (F1–F13, T1–T5), the researcher's dossier, BUILD_PLAN AQ4/AX18/AX47/AX48/AX49, phase-07c-2.md, 05b2 file 47 §4 (iii), my file 48 (S3-c), and `src/plugin/core/ScenePipeline.cpp`.

---

## D-W1 — W_max under (C)

**1. Reading.** Choose the per-emitter work cap under (C). The cues it triggers:
- **cost:** CPU per solve, the pool running beside the callback;
- **state discontinuity:** the interim-to-final step on a keyless load;
- **my own condition (5)**, Table 15.1.

**Table 15.1 read in the corpus** (Vorländer §15.3, after Lentz et al. 2007):
- 700 ms for a translation over 0.25 m (specular part).
- 3 s for a translation over 1 m (specular plus scattering part).
- They are derived from movement at 30–50 cm/s. Check: 0.25/0.7 = 0.36 m/s and 1/3 = 0.33 m/s.
- So the rows are **per-update latencies for one moving scene**. They are not a load budget and not per emitter, and they say nothing about threads.
- My mapping:
  - the 700 ms row bounds the **ISM update latency** after a move;
  - the 3 s row bounds **the time until the moved scene's final diffuse level plays**: solve, then assembly and IrSet, then 2P, then the 30 ms fade.

**A finding from the code that couples W to the 700 ms row.** Condition 4 ("the ISM is never held behind the solve") holds only for the first edit after a quiet spell (L494–524).
- A parameter change only bumps `dirty_` (L315).
- `builderAbandon_` is set only in `quiesceBuilder` and `cancelBuilder` (L114, L849).
- So an edit that arrives while a builder solve runs, or while it waits at the gate, does not cancel that solve.
- The edit's ISM update waits for that solve, `finishExact` and `makeIrSet`. Only then is the result discarded mid-drag (L539–543).
- At 8 instances it also waits for the gate queue of the other solves.
- So the **ISM hold ≈ queue + solve(W)**, and it grows linearly with W in capped classes.

**Measures per option** (derived from T1 and T2):
- CPU per solve ≈ W_scene × ~50 ns single-thread (T2: 43–63 ns in layout 4 and the cubes).
  - At the pin: 0.3 core-s.
  - At ×8: 2.4 core-s.
  - At ×16: 4.9 core-s.
- Pool(4) wall time in capped classes, measured locally: ×8 664–808 ms; ×16 1.13–1.65 s. CI pool times are about 2× faster per evaluation.
- The gated cubes saturate: low-α s0.3 from ×2 (1.25 × the pin's work), flutter from ×4 (3.29 × the pin's work). Only the s = 1 cube and layouts 4/5 keep scaling.

**2–4. Ranking and ratings (now / later):**

| option | label | now / later | reason |
|---|---|---|---|
| W-6 (≈ ×8: U = 0 at every capped class except both-near) | prefer | 1 / 1 with conditions (1 / 2 without) | Repays my level debt (s = 1 SE 0.36 → 0.13 dB; layout 4 listener_edge 0.93 → 0.21 dB). The ISM hold of ≤ ~0.8 s is right at the 700 ms row. |
| W-5, composed with my terms below | prefer | 1 / 1 | This is the same value as W-6 if W-4 is read as an increment. |
| W-1 (≈ ×8 when read on the capped class) | can live with | 1 / 2 | Ill-posed on the "costliest gated scene", which saturates by ×4, so it never binds there. It has to be read on the capped class. |
| W-2 (≈ ×16) | can live with, only with conditions | 2 / 2 | ISM hold 1.1–1.65 s, over 700 ms. 4.9 core-s per settle: about 1 core continuously for one instance automated every 5 s. |
| W-3 (≈ ×17–25) | can live with, only with conditions | 2 / 2 | It spends the whole 3 s row on the solve and leaves nothing for assembly and fade. 10+ core-s per settle. |
| W-4 as the sizing basis | can live with only as a check | 2 / 2 | It already fails at the pin (F6: settled 9.9–13.3 s at 96 kHz, 8 instances), and the failure comes from synthesis (1.1–1.4 s per emitter), not from W. As a basis it would return the pin, which is out of bounds, and freeze my debt. As an increment check (8 × ΔS(W) printed) it is 0 / 0. |

**Debt.**
- Every option commits 07c-2 to a single golden round.
- Undoing the value costs a parameter change plus another golden round before release; after release it costs an AX48 versioning decision.
- Evidence that could overturn the value:
  - 07c-2 CI: the cross-OS W sweep, B1-b at the new W;
  - 08-4: the heaviest mode (W does not depend on mode, since the `DiffuseProblem` has no fs);
  - 12-2: preset capped-class membership.

**Keyless path.**
- **K-a:** 0 / 1. Step 0 (class a). The extra synchronous time falls only on capped or work-stopped scenes, because uncapped n*_max-stopped scenes realise identical work at any W (F11). On the gated cubes F12 stays ≤ 25.6 s; the macOS outlier is already at 30.50 s at the pin.
- **K-b:** 1 now / **3 later** as a general source. T3's drift column shows (A)-to-×16 E_b differences that would play as steps:
  - 3.72 dB (layout 4 both_corner, e0);
  - 2.2 dB (layout 5 both_wall);
  - 1.32 dB (layout 5 emitter_wall);
  - 1.15 / 1.25 dB (layout 4 listener_edge).

  These exceed AX47's 1 dB before any reversal.
- **K-c (mine):** run stage-1 at (A) and accept it as final only where it is uncapped and n*_max-stopped. There the final range is identical by F11, so the step is 0. Everywhere else, K-a. Rating 0 / 1.
- **Sequencing:** I accept deciding the value now and the path after the ABX, with goldens after both. But K-a needs no ABX, and F4 already shows that K-b breaks the 1 dB bound in the capped layouts.

**5. Evidence.**
- Table 15.1, the 30–50 cm/s speeds and the 140 ms statistical-decay result: corpus, Vorländer §15.3.
- ISM hold: from the code (ScenePipeline L315, L114, L849, L494–543).
- CPU, saturation and drift: T1–T3 [Observed, local Linux, 4 threads; macOS and Windows still under-informed].
- 1 dB jnd: Vorländer Table 6.1, via researcher R5.
- Hold ≤ 0.8 s at ×8 on user machines: [Inferred]. It needs measuring.

**6. Conditions of acceptance** (they bring W-2, W-1 or W-6 to 1 / 1):
- **(C-a)** One of two:
  - a builder solve is cancelled by a newer edit, at its existing stop points (`run.stop`), which turns the 700 ms term off; or
  - a measured ISM latency for an edit that arrives mid-solve is ≤ 700 ms at 1 instance on the worst OS at the chosen W.
- **(C-b)** Re-run B1-b at the chosen W with a **capped** builder scene (s = 1 cube or layout 4) and print the solve duration. Today's builder scene, the low-α s0.3 cube, saturates at ×2 and cannot show W's effect.
- **(C-c)** The re-pinned solve bound also guards one capped scene. Above ×4, the gated cubes no longer exercise W.
- **(C-d)** The 8-instance queue is printed, not used for sizing. An instance-count basis conflicts with "no instance cap" (FR-SIM-7).

**Companion items.**
- **(b) `nsPerEval`, D-Q5:**
  - No resolvable move. Linux flutter as printed spans 8.72–13.95 ns over 10 runs, with no trend from 05i to S2; the S2 runs alone span 8.99–13.95. Resolution is about ±25 %.
  - Single-thread ns/eval is flat in W (T2: max/min 1.02–1.37), so Seats 2 and 3 need not be convened.
  - Caveats:
    - The printed figure is half the per-scene cost (double count). Any 3 s projection must use the per-scene basis.
    - Pool ns/eval falls with W by up to 2.05×, so re-pin by measurement; scaling from the pin overstates.
- **(c)** The S2 form is fine with me, plus C-c.
- **(d)** Seat 2's. From my side, flutter E_b drift across W is ≤ 0.003 dB, which does not matter for the tail.
- **(e)** Keep v2. It loads keyless at the new W, which is step 0 under K-a.
- **(f), (g):** NOT MY MATTER.

**7. Hand-offs.**
- Seat 5: the cancel-on-edit fix (C-a); a pool of `hardware_concurrency` occupies every core beside the callback (pool = hw − 1 [Hyp]).
- Seat 1: the floor excludes both-near cases, which no W fixes (U = 1 at every W, SE 0.5–1.2 dB at ×16).
- Seat 8: the bounce rooms (99 → 64 m, α 0.05, s 0.3) probably saturate like the gated cube [Inferred], so F7's linear projection overstates the bounce.

**8. Premortem.** W goes to ×16 without C-a. A producer automating a source in a capped large room hears the early reflections lag the move by 1–2 s, and about 10 s across 8 instances. Seat 6's users notice first.

---

## D-W2 — the AX47 self-ABX and L4 design

**1. Reading.** The stimulus has to be the shipped transition. Cue: a state discontinuity, rendered faithfully.

**2–3. Ranking and ratings (now / later):**
- X-1, X-2, X-3, X-5: 0 / 0. They render identically.
- X-4: 1 / 2 if the staircase tool makes steps with a gain ramp outside the engine.
- I prefer X-3 or X-5 with one size above the bound (for example 2 dB) placed first as a sensitivity anchor (BS.1116-3 §6, R4). The statistics are Seat 1's ground.

**Sub-items (my ground):**
- **Rendering of the step.**
  - Build two IrSets from one StagedBuild of the capped layout-4 scene: same tailSeed, streams and fs.
  - Set the tail level through `useDiffuseLevel`, the same override B1′ uses (L498), to E_b and to E_b + g dB.
  - Use a **uniform g in all 8 bands**. That is the worst case AX47's per-band bound admits [Inferred].
  - Join them by the shipped **30 ms equal-gain** fade (AX18 same-scene, ρ = 1, mid-fade 0 dB by Eq. 4.15).
  - Render through `sim::RealtimeEngine` (`--realtime-emulation`), so both convolvers read one input history and the whole reverberant level steps at once.
  - Use a fixed block size, the plugin's default P, and a fade start at a pinned partition boundary.
- **Assertions on the stimulus:**
  - early parts bit-identical;
  - 10·log10(E(diff)/E(final)) = 20·log10(10^(g/20) − 1) to rounding;
  - the `[ax47-midfade]` checks applied to the stimulus itself.
- **No loudness matching of A against B.** The level is the variable. The absolute playback level is fixed and recorded (Seat 4).
- **Output mode: omni.** The stereo and binaural stubs are dry until 08/09 (CLAUDE.md), so they carry no tail.
- **Timing.** At least one T30 of programme material before the step [Inferred], and at least 2 s after it.
- **Print** the tail-window specular share and the measured wet-output level change per band. The record should state the effective step, not only g.
- **L4.**
  - Use the shipped provisional IR (`assembleProvisional`) and the exact IR through the real-time convolver.
  - The held chord **must be released**, followed by ≥ L = 11.93 s of free decay.
  - While the chord is sustained, the difference is ≤ 0.06 dB (energy past L_f ≤ 1.34 %), so the test would be vacuous.
  - On a free decay the cut falls at about −18.7 dB, so expect a detection [Hyp]. That triggers AX49's reversal, which goes to 07d.
- **What is recorded:** law, length in samples, P, g per band, direction, onset sample, scene hash, tailSeed, commit.

**4. Debt.**
- Phase 10 sets the final crossfade law (AX18 is a placeholder until then). A shorter or different law means re-running the ABX, about an hour of a person's time.
- If the stimulus is not the shipped path, the class (c) admission rests on invalid evidence: a phase of rework in 07c-2 or 07d.
- 08-3 and 09: whether the omni result carries over to binaural with per-ear seeds is [Hyp] (Seat 4).

**6. Condition for X-4.** Pre-render a fine grid of step sizes (0.1 dB) through the shipped path. That brings it to 1 / 1.

**7. Hand-offs.**
- Seat 1: the anchor and the family.
- Seat 4: the chain and level.
- Seat 5: the test-only render flag and determinism.
- Seat 7: the speech licence. LibriSpeech is not anechoic; that is acceptable for detecting a step [Hyp].

**8. Premortem.** The steps are made with a Python gain ramp or an equal-power switch, and the result says "not detected". The class (c) source ships, and the first person to hear the jump is a producer loading a large room.

---

Files used:
- /home/user/makroof/docs/review/phase-07c-2/1-decider-convening.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part1.md
- /home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part2-wsweep.md
- /home/user/makroof/docs/review/phase-07c-2/3-researcher-RQ-W1-W2.md
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp
- /home/user/makroof/docs/corpus/vorlaender-auralization.md
- /home/user/makroof/docs/BUILD_PLAN.md
- /home/user/makroof/docs/phases/phase-07c-2.md
- /home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md
- /home/user/makroof/docs/review/phase-05b2/48-seat3-confirm-S3c.md
