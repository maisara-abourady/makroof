# 7 — Orchestrator: facts for the interrogator's rebuttal question 5 (Q3 mechanism) and question 3's R + 2P path

**CORRECTION (2026-11-11, after interrogator file 10, P05I-47; verified by the orchestrator):** the first bullet and
the 'Reading' paragraph below are **wrong**. `ScenePipeline::solveAndBuild` (`src/plugin/core/ScenePipeline.cpp`
L115–133) constructs a `DiffuseSolveGate::Scope` before `sim::buildRoomIR(scene, options)` and the Scope's destructor
(`DiffuseSolveGate.h` L92–96) leaves the gate only when that call returns: **the gate is held for the whole room-IR
build** (ISM, unit-decay synthesis and the diffuse solve); only the IR-set build (`makeIrSet`) runs outside it. The
original text is kept below as written, for the record.

From the code at the branch head (no new measurement):

- **What the gate serialises.** `src/plugin/core/DiffuseSolveGate.{h,cpp}`: one process-wide gate whose pool has
  `hardware_concurrency()` threads; a waiter enters it only for the diffuse solve (`sim::diffuse` estimator, the
  only user of `ThreadPool`: `src/sim/diffuse/DiffuseEstimator.cpp` L481). Nothing else in a build takes the gate.
- **What runs outside it, single-threaded per instance and concurrently across instances:** the ISM, the unit-decay
  synthesis (`tail::BandNoiseGenerator`, FFT up to 2^21 points at the low-α 96 kHz cube) and the convolver's IR-set
  build. Each builder is its own thread (`src/plugin/core/IrBuilderThread.cpp` L29); an offline instance builds on
  the thread that calls `process()` and then convolves every block on it (the bounce in record (c) does this back
  to back).
- **No build-time cache in the plugin path.** `BuildOptions::cachedUnitDecays` (`src/sim/Engine.h` L112) is set only
  by tests; every room-size step in the records is a cold build (review question Q5 of the branch review).

**Reading.** With the gate held only around an ≈ 81–91 ms solve, the ≈ +1.76 s excess of record (c) (one real-time
and one offline instance) and the systematic ≈ 2× contended host-thread wait of record (d) cannot come from the
gate's turn-taking. The plausible mechanism is CPU and memory-bandwidth sharing between concurrent builds (and the
offline instance's continuous convolution) on 3–4-core hosted runners: two cold builds at once each take about twice
as long. **Not established**: settling it needs a split timer of the contended call (ISM / synthesis / IR-set /
solve wait / solve), which is phase-07c condition 9's packet ("repeats the file 7 split timer on one named local box
before sizing its interim rules"). Until then the excess is recorded as "about one extra rebuild's time;
mechanism not established (hypothesis: CPU sharing outside the gate)".

**The listener step in the joint record (rebuttal question 3).** In the pipeline at this head, every parameter change
marks the scene dirty and the builder rebuilds the whole scene (`ScenePipeline::setParameter`, `decide`); there is
no position-only path that reaches the output while a room-size rebuild of the same instance is pending (the
position-only tail cache is Phase 10-1). So in the joint step the listener move waits for the full rebuild: its
staleness is the room-size rebuild's, as recorded.
