# 12 — Seat 2 (Scene-to-Response Architect) on D-G1

Phase 05i, 2026-11-11. Convened by decider file 11 (Brief 2). Saved verbatim by the orchestrator (the seat only reads). Corpus c1b171f present; no acoustic fact here rests on it; everything comes from the code and the records.

SEAT 2 POSITION

**1. Reading.** The gate is held for the whole `buildRoomIR`, not only around the solve (G-1). The question is who narrows it, and when, or whether her AX38 (i) is amended to match the code. Cues: cue 7 (cost growth: flat per build but serialised, so linear in N); §8 P5 (precompute what does not move, budget the edit cycle); §8 P4 (the representation and API between sim and plugin).

**2. Ranking.** (1) **A′** prefer. (2) **A** prefer, a close second (no before-remedy baseline). (3) **D** can live with. (4) **E** can live with, under condition. (5) **B** can live with, under condition. No option breaks a criterion I never trade (validation, frequency-dependent absorption, scattering, stated edge).

**3. Tension now.** A 0: no code, no output change (AX5). A′ 0: the poller is test-only and touches no `src/` (whether it is inside scope 2 is Seat 5's call). B 1: nothing changes today; it writes into her decision a 2 s serialisation the memory rationale does not need (the solve is ≈ 81–91 ms of a ≈ 1.8–2.0 s build, about 4–5 %). D 1: an S-size phase that changes the sim API before 07c-1 restructures the same function. E 0: no code.

**4. Tension later (the debt).**
- **A, 1.** Commits 07c-1 to a stage split of `buildHybridOmni` (plan/ISM → solve → synthesis → assembly), which 07c-1 needs anyway: condition 9 has to take the synthesis off the synchronous path; condition 4 ("the ISM update is never held behind the diffuse solve") cannot hold across instances while the gate encloses the ISM (today the ISM waits behind other instances' whole builds). Narrowing falls out of planned work. Undo: one line (widen the scope). Evidence: 07c-1's gate-wait and transient-memory records, and condition 7.
- **A′, 0–1.** As A, plus a before/after pair on the same instrument — the non-circular comparison P3 asks for.
- **B, 2.** After 07c-1 moves synthesis to the background, the gate would still serialise ≈ 2 s of synthesis per instance; following stays linear in N (8 × 100 m / 96 kHz about 16 s today). Undo: a second amendment of her decision plus the same code change. Evidence: 07c condition 7's re-measure.
- **D, 2.** A `BuildOptions` hook in 05j will be torn up when 07c-1 splits the stages for conditions 4 and 9 (the sim API changes twice); concurrent syntheses (memory, below) arrive one phase earlier, before 07c-1's cancel points (condition 10) exist.
- **E, 2.** No test pins the gate's scope; 07c-1 can satisfy F1 and still leave the gate around the whole build; the departure goes untracked, nothing records it before or after.

**5. Evidence.**
- **The gate encloses the ISM, the synthesis and the solve; `makeIrSet` is outside:** from the code, `ScenePipeline.cpp` L124–132.
- **The synthesis buffers are allocated before the solve:** `BandNoiseGenerator` is emplaced *before* planning and the solve and lives across it (`Engine.cpp` L240–242).
- **Memory split, derived from the code** (100 m, 96 kHz, 12 s tail cap; L = 1 152 000 samples; n = 2²¹, assuming 2H < 945 152): band spectra 8 × n × 8 B ≈ 134 MB, resident across the solve; `make()` spectrum + work 2 × n × 16 B ≈ 67 MB; unit bands 8 × L × 8 B ≈ 74 MB per emitter (≈ 147 MB for two, if both are held); IR taps ≈ 18 MB. These outside-solve buffers alone reach the recorded 293–297 MB delta (05h row; `NoiseTail.cpp` L77–155) [Inferred]; the solve's own share is not recorded.
- **Concurrent memory once narrowed:** N builders each hold about 0.3 GB at once, so 8 instances ≈ 2.4 GB of process transient at 100 m / 96 kHz [Hyp: the peaks overlap]. Not against the letter of AX38 (i) (≤ 1 GB per solve, one solve per process), but unbounded in N; less at 48 kHz (n = 2²⁰) and in the AQ10 room.
- **API form, preferred:** the stage split `planRoomIR` / `solveDiffuse` / `assembleRoomIR`; `buildRoomIR` stays as their composition for `render_cli`, with a test that the result is bit-identical; the pool and cancel already pass through `BuildOptions` (`Engine.cpp` L325–327); the gate's abandon maps onto the existing `BuildCancelled`. Minimal form: a `solveScope` callable in `BuildOptions` wrapping `estimateDiffuse`.
- **Contract-boundary cost: none.** `BuildOptions` is sim API, not `contract::SceneDescription`: no `contractVersion` bump, no schema change, `check_boundaries.py` unaffected; sim stays JUCE-free.
- **Output unchanged.** The solve is a pure function of its scene (AX39/AX40); oversubscription of the gate's pool by concurrent syntheses changes timing, not output.

**6. Conditions of acceptance.** B → 1: add a memory reason the records support (a synthesis that is ≈ 95 % of the build is serialised; that reason has to be measured, not assumed). D → 1: 05j delivers the stage split that 07c-1 conditions 4 and 9 will use, not a throwaway hook. E → 1: a `[pipeline]` assertion that the gate is not held during the ISM or synthesis, added to 07c-1's acceptance criteria. All narrowing options: the AX38 (i) transient-memory record measures the *process* peak with 4 and 8 concurrent builds at 100 m / 96 kHz; a breach goes to Phase 13's memory budget, never fixed by an instance cap (D-H1 (v)(d)); a concurrency limit on syntheses, sized from that record, stays open.

**7. Hand-offs.** Seat 5: whether A′'s poller is inside scope 2; TSan and the order of abandon and quiesce under narrowing. Seat 3: following and CPU under concurrent syntheses on 4-core machines (RQ-G1). Seat 7: the cost of D. Phase 13 / Seat 5: the process memory budget.

**8. Premortem.** If B is chosen and fails: after 07c, 8 instances at 100 m still settle one after another in about 16 s, because the synthesis waits behind a gate it never needed; Seat 3 sees it first, at 07c condition 7's re-measure.
