# Seat 5 (deadline keeper) — positions on D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 5 POSITION: D-T1 (sub-questions 1.1 to 1.6), D-T2 and D-T6

Corpus present (c1b171f). The corpus does not cover the claims below: they are engineering claims, sourced from the code, the C4/C5/C8 data, builder evidence §3 and dossier F15–F20. Prototype times are numba and single-threaded unless I say otherwise. Treating them as C++ times is [Hyp] (O15).

## D-T1 / D-T2

**1. Reading.** The question is how the builder computes the diffuse E_target, and what that does to my clocks. These are the clocks:
- the builder thread;
- the synchronous host calls (prepare, restore, setNonRealtime), which take the gate first (D-T4a 4a-2G3C);
- the offline `processBlock`;
- `quiesce()`.

My cues: §4.1 (unbounded work), §10.2 (worst case first), S5 (offline equals real-time; AX5) and §4.4. No option adds a crossing to the callback.

The yardstick throughout is Challenge 1, still pending with Maisara: about 2.1 s per synchronous restore at 100 m and 96 kHz (14 × t_restore against pluginval's 30 s watchdog). Today a restore takes 1.51–1.88 s. If Maisara answers yes, the overruns below become blocking CI failures. If she answers no, they stay recorded debt, and my ratings do not change.

**D-T1.1, formulation**

| option | label | now / later | reason |
|---|---|---|---|
| T1-F | prefer | 1 / 2 | **Now:** at Tol-2, a 100 m restore gains 2 × (144–183) ms = 0.29–0.37 s, giving 1.80–2.25 s against about 2.1 s. With 4 threads it is about 1.6–2.0 s. **Later:** the prototype samples directions with libm `cos` and `sin` (`phase05b2_dt1.py` L93–94, L139–141). That sampling decides the path, and libm differs across MSVC, glibc and Apple (F19). FMA defaults also differ by compiler (F20), and CMake sets no `fp-contract` policy today (from the code). One branch flip on a path holding 0.13 % of the estimate (W1, 32k paths) is about 0.0056 dB. For a tail at −30 dBFS that leaves a residual of about −94 dBFS. Near walls, single paths hold 5–73 % of the estimate, which gives about −40 dBFS. Either way AX5's −100 dBFS across architectures is broken [Inferred]. |
| T1-B | **cannot live with** | 3 / 3 | C8 puts a generation at about 1 454 s at 100 m, and about 9 s per rebuild in the AQ10 room (2 ns per evaluation, [Hyp]). That time runs on the host's thread during restore and prepare, and `quiesce()` waits for one whole solve. |
| T1-A | **cannot live with** | 2 / 3 | **Now:** W1 measured 9.9 s for the kernel plus 5.4 s for the solve, with a peak of 1.17 GB. **Later:** it forces D-T3. The edge of the supported range would be set by (c)'s memory figures, which are arithmetic only. If that edge turns out wrong after release, the fix is a second contract major bump. A cached kernel would also break the 128 MB resident cap. |

**D-T1.2, seed**
- **S-1: prefer, 0/0.** The diffuse solve does not depend on tailSeed. A seed edit only regenerates noise, so Phase 10's cache key can leave the seed out. The agreement test has no seed knob to turn.
- **S-2: can live with, 0/1.** A tailSeed edit forces a new diffuse solve. The seed also becomes a knob that could be turned until a test passes.
- **Cross-machine note, as written: 1/2.** It does not exclude libm or FMA from the path state. The flip rate it calls "unquantified" is costed above.

**D-T1.3, path count** (my ratings are the same under either seed)
- **N-1: 2/2.** At 22 000 paths, W2 costs about 2.3 s per emitter: 848 ms per 8 000 paths, where W2 needs 12 paths. W2 would go from 28.5 ms to about 4.7 s. The 100 m fallback costs about 2.0 s per emitter. Near walls the standard error is unbounded and nothing flags it.
- **N-2: can live with, 1/2.** A cap counted in paths spreads the worst case about 90× across scenes: about 1.2 µs per path in W1 near a wall against about 106 µs in W2. The prototype's stratification uses `nsq = √N` (L86), which breaks the prefix property.
- **N-3: prefer, 1/2.** The cap has the same problem. The pilot paths are extra cost, which I accept.
- **N-3W (my own option): 1/1.** This is N-3 with a deterministic **work cap** W_max, counted in image evaluations rather than in paths or wall time.
  - W_max is derived, not invented: two emitters solved with the pool at W_max must fit within the restore bound minus that scene's existing build time, measured at the gated scene below.
- **Diagnostics cost.** Each path adds 4 power sums per band and an insertion into a fixed top-201 buffer, against hundreds of image evaluations per path. That is under 1 % [Inferred], and about 13 KB per emitter. The generalized-Pareto fit must use a fixed iteration count.
- **Cap hits.** In a user's DAW a cap hit is a deterministic flag in TailMatch and diagnostics. It cannot be escalated to anyone from there. Escalation happens in CI and render_cli only.
- **Gated worst-case scenes for T1-F.** Memory is not the issue (< 2 MB), so D-T4c's two 100 m builds stay as they are. For time:
  - Table 5.2 layout 4, s = 1, listener at the 0.1 m corner (C4: 47 M paths needed). The benchmark asserts the cap flag, the way W2 asserts the fallback.
  - The 100 m non-fallback cube.
  - Recorded beside W1/W2: "W1-NW", W1 with the listener at the 0.1 m edge.
  - If Challenge 1 becomes a block, the restore gate takes the maximum over this set.
- **Near-wall times against Challenge 1.**
  - W1 edge at SE 0.083 dB: about 2 s per emitter even with 4 threads, so about 4 s per restore.
  - Layout 4: about 40 s per emitter, so about 80 s per restore. 14 × 80 s is about 19 min against a 30 s watchdog.
  - D-T4c's "record and escalate" protects nothing on the host's thread. Only the work cap does.

**D-T1.4, tolerance τ** (my ratings collapse to L2-F2's cost if L2-F2 wins)
- **Tol-1: prefer, 0/1.**
- **Tol-2: can live with, 1/1.**
- **Tol-3: 2/2.**
  - 100 m restore gains 1.8–2.3 s, giving 3.3–4.2 s.
  - W1 gains 23–32 ms, giving 44–53 ms against the 50 ms target.
  - Layout 4 takes 9.7 s per emitter.

**D-T1.5, case set**
- **CS-1: can live with, 0/1.** It misses W1/W2 and the golden fixtures.
- **CS-2: prefer, 0/0.**
- **CS-3: prefer, 0/0.** The 30 pairs add about 0.3 s in Release.
- **CS-NW: add it.** It is the only case that runs the heavy-tail and cap path in CI. The W1 edge costs about 2 s with 4 threads.
- **Condition on every set:** CS-1 alone is about 5.3 s single-threaded at Tol-2. In Debug ctest, ASan or TSan that becomes minutes, and at L2-F2 it would take more than 29 min per OS [Hyp].

**D-T1.6, near-listener handling**
- **NW-3: prefer, 0/1.** The largest single score drops to 1/(πρ²) = 1.27 m⁻², from 31.8 m⁻², a 25× lower cap. Variance falls 4–7×. The clamp uses only min and max, which give the same result on every platform.
- **NW-2: can live with, 1/1.** Variance falls 2–4×, at walls only.
- **NW-1: can live with, 1/2.** Near walls it is served only by the cap.

**D-T2**
- **L2-P: 1/1 for the rule itself.** It is reachable only through T1-A or T1-B, which I rate 3.
- **L2-F1: prefer, 0/1.** A deterministic run at N and at 2N cannot flake. It runs once, in Release.
- **L2-F2: cannot live with, 2/3.**
  - A 100 m restore gains 2.4–3.0 s even with 4 threads, giving 3.9–4.9 s; 14 × that is 55–69 s against 30 s.
  - Layout 4 takes about 51 s per emitter.
  - A W1 wall takes 7.1 M paths.
  - Under a deadline cap, the "certified" standard error would be false in exactly the costly scenes.

**5. Evidence**
- C5 (data file): no face sequence changed at 1e-9 m perturbation or with float32 state; results were bit-identical with 1, 2 and 4 threads. This was on one platform.
- F15–F18: the counter-based integer stream is identical everywhere, and the integer-to-float conversion can be made exact.
- F19–F20: the floating-point path is what varies across machines.
- `ci.yml` L318–327: Debug ctest on all three OSes. L341–346: benchmarks run from the Release build. L441, L474: ASan and TSan jobs.
- C4 and C8; builder evidence §3.

**6. Conditions of acceptance**

*T1-F, 1/2 → 1/1 (the determinism package):*
- **D1.** No libm call in any value that decides a branch or a path. Direction sampling uses only +, ×, ÷, sqrt and comparisons, for example disc rejection plus Malley's method. The RNG counter is keyed by (seed, emitter, path, hit, attempt). libm stays in the scores only (Hann, exp), where it changes results at ulp level.
- **D2.** `-ffp-contract=off` on gcc and clang for `src/sim`, `/fp:precise` on MSVC, and no fast-math.
- **D3.** A known-answer test of the RNG on all three CI platforms (F17).
- **D4.** Fixed path blocks whose boundaries do not depend on the thread count, reduced in block order. Stratification does not depend on N.
- **D5.** A committed golden **integer hash of every path's face sequence**, required to be equal on all three CI platforms. This is cross-architecture evidence that needs no artifact exchange.
- **D6.** The solve checks the stop flag between batches, so `quiesce()` waits at most one batch. A cancelled solve is discarded.

*Threads inside the solve:*
- one process-wide pool, owned with the gate, created at prepare rather than per solve;
- at most hardware_concurrency − 2 threads [Hyp], normal priority;
- D-T4c's callback p99.9 record at buffer 64 runs with the pool busy.

*Other options:*
- **N-1 / N-2 / N-3:** adopt N-3W, giving 1/1.
- **NW-1:** the work cap brings it to 1/1.
- **Tol-3:** the work cap plus the pool bring it to 1/1; Tol-3 then simply means more cap hits.
- **Case sets:** the agreement suite runs under a hidden tag from the Release build on three OSes. Debug, ASan and TSan run one smoke case.
- **L2-F2, to 2/2:** the work cap, plus taking the diffuse solve out of the synchronous restore and prepare. Restore would return after the specular build, the builder thread would solve, and the offline path would wait. That is roughly a phase of Phase 07 rework.
- **T1-A, to 2/2:** measure (c)'s memory and the C++ restore time at the proposed range edge before D-T3 goes to Maisara.
- **T1-B:** async restore plus D-T3 brings it to 2/2. Nothing smaller does.

## D-T6

**Reading.** This is a CI gate on three OSes, the golden process and paired renders.

**Ratings**
- **RS-2: prefer, 0/0.** It includes W1, the AQ10 benchmark scene.
- **RS-1: can live with, 0/1.** With one case, a regression at a middle s value passes.
- **B6-1: prefer, 0/1.**
  - One `--diagnostics` run carries both E_targets, because AX16 is kept (D-T5.1). ΔL_C++ is therefore paired inside one build.
  - It needs the small ΔL_ref golden (C11), exported by a script with its reason in the CHANGELOG.
  - It must be regenerated whenever `ref_hybrid` changes.
- **B6-2: can live with, 1/1.** No golden is needed. But the 0.43 dB rests on one room class (K16). If it fails in `stone_box`, the only remedy is to reopen the decision, because changing the bound after seeing the result is tuning.
- **M-1 and M-2: 0/0 each,** provided tracer data are committed with their seed and statistics.

**Gate design**
- The gate reads `render_cli --diagnostics` from the cli build and runs in PR CI on all three OSes.
- It lands in the same push as the switch (§8 atomicity) and before any golden update.
- Paired renders use a validation-only `render_cli` flag that renders the AX16 tail level with the same binary and the same tailSeed, like `--no-air-absorption`. Before and after then differ only in E_b.
- The renders feed a report job, not a gate, with `--ensemble` where Seat 1 asks for it.

**Multiple comparisons [Inferred].** RS-2 has 7 emitter cases × 8 bands = 56 case-bands. At τ ≈ 3 SE, 1 − 0.9973⁵⁶ ≈ 14 % if the case-bands are independent. The seed is fixed, so the result never flakes. But a fail on the first draw has no legitimate fix.

## Hand-offs
- **Seat 1:** the decision rule for multiple comparisons; whether estimates that hit the cap and read 1–4 dB low are audible.
- **Seats 2 and 9:** whether NW-3 is still the same model.
- **Seat 6:** showing cap hits to the user; edit-to-hear delay near walls.
- **Seat 7:** the cost of async restore.
- **Researcher:**
  - whether glibc's runtime dispatch changes exp or cos results across x86-64 microarchitectures (AX5 on the same architecture, true today too);
  - how long hosts tolerate a blocked `setStateInformation`.
- **Orchestrator:** the existing restore time at the layout-4-sized room, and the C++ cost per image evaluation, so that W_max can be derived.

## Premortem
T1-F ships with libm sampling and a path cap. A user opens a Windows-saved project on an M-series Mac with the listener in a corner, a path flips, and the bounce differs by about 0.5 dB. Or a corner listener in an absorbent room blocks project load for about 80 s per instance. A beta tester notices first, because CI only restores the 100 m cube at reference positions.

Files: /home/user/makroof/docs/review/phase-05b2/9-decider-convene-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/17-decider-convene-T1-addendum.md, /home/user/makroof/docs/review/phase-05b2/16-orchestrator-C4-near-wall.md, /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md, /home/user/makroof/tools/validation/phase05b2_dt1.py, /home/user/makroof/tools/validation/data/phase05b2_dt1.json, /home/user/makroof/.github/workflows/ci.yml
