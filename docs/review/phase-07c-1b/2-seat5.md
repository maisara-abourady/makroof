# 2 — Seat 5 position (D-B1 … D-B5; lead on D-B1, D-B2, D-B4, D-B5), round 1

2026-11-13, corpus c1b171f (claims from code and arithmetic). Saved by the orchestrator from the seat's report.

## Knowledge answers (from the code)
**K11.** The output is fully wet (direct sound in the IR; no dry path: `ScenePipeline::process` → `engine_.process` → trim).
Before any IR, `CrossfadingConvolver::computeBlock` writes y_A = 0 → **silence** (`RealtimeEngine.h` L18). An inserted
instance never plays it today: realtime `prepare()` runs `decide(Source::Synchronous, load)` before returning (L812–822), so
the IR is in the mailbox and step 1 of `computeBlock` (L281–288) installs it at the first partition boundary, no fade; only
the reported latency (P + pre-roll) is heard, host-compensated. A first IR arriving later (blockStart_ > 0) fades in from
silence over 30 ms (L338–352) — only if the first build is asynchronous (B2-b) or late.
**K13 / K23.** Yes, bit for bit on one platform, given the same prepare (P, FDL capacity), the same input from sample 0, trim
exactly 0 dB (`applyTrim` returns early at gain 1). Both lanes read the one FDL; lane B accumulates over the whole history
(L289–296); `advanceLane` walks units in index order u whatever the callback split; `finishLane` is shared. Output o =
gOut[idx]·a + gIn[idx]·b in float (L323).
**K14.** s0 = (⌊r/P⌋ + 2)·P in output samples from prepare/reset (on the partition grid; `fadeStartSample()`); r is
timing-dependent when the builder submits, so **the test must own the submit point**: drive a `RealtimeEngine`
single-threaded, submit between blocks, use the pipeline-built IrSets (`lastSubmittedIrSet`), align to the reported s0. L =
round(0.030·fs) (1440 @ 48 kHz, 2880 @ 96 kHz). Windows need not divide L: with ΔG = N_w/L the bound holds for every window,
incl. one straddling the fade end.
**Code facts for the board:** record (h) times restores with the insertion prepares excluded (instances prepared, settled,
then restored, L1723–1745); in a prepare-before-setState host every instance pays an insertion solve on top (not in the D-B4
trigger figure; `insertMs` now printed beside it; which hosts [Hyp] until RQ5 / cond. 11 trace). The diffuse pool has
`hardware_concurrency()` threads at default priority (`DiffuseSolveGate.h` L60), plus 8 builder threads, plus per-emitter
syntheses outside the gate; the D-B1 measuring thread runs at normal priority beside them.
**K24.** No reading of MACTRIGGER found; it prints only into `warnings=` in the job log (L602–613); nothing surfaces it — a
process defect (see (vi)).

## D-B1 (lead)
Reading: an unreadable deadline record (cues 4.2 "works at 512, fails at 64", 4.1 average vs worst). `sleep_for(1333 µs)` on
Windows' default timer (≈ 15.6 ms ticks) and loaded macOS run queues paces at ≈ 5–10 ms → p99.9 = 1st–2nd largest sample;
normal priority; wall time includes preemption by ≈ N_hw + 8 + 2·8 default-priority threads: it measures the OS's fair share,
not a host audio thread.
Ranking: B1-b prefer; B1-d can live with (only once B1-b shows a residual); B1-a only under its condition; B1-c last resort, not
recommended.
- **B1-b 1 / 0.** Test-only under `tests/`. Spec: callback thread at THREAD_TIME_CONSTRAINT_POLICY on macOS (period 1 333 µs,
  constraint 1 333 µs); MMCSS "Pro Audio" + a high-resolution waitable timer on Windows; SCHED_FIFO on Linux else "not
  available"; absolute-deadline pacing (`sleep_until` next period, spin the last ≈ 100 µs); per-thread CPU beside wall time
  (QueryThreadCycleTime, not GetThreadTimes at 15.6 ms granularity); print median / p99 / p99.9 / max, overruns > period and >
  period/2 [Hyp headroom rule], callback count vs expected, builders 0/1/2/4/8, hardware threads; print `INSTRUMENT INVALID`
  when count < 0.95 × expected; a record, not a gate (hosted runners are VMs).
- **B1-a 1 / 3.** Records an unreadable number and closes it at Phase 13 with the same instrument; if the Windows 48 ms (36
  periods) is even partly real, criterion 1 is broken and unmeasured; undo = re-instrumentation at Phase 13 under release
  pressure.
- **B1-c 2 / 2.** A class (1) host call waits "at most for the one solve already running" (AX38 (i)); a lower-priority
  builder makes that solve preemptible → unbounded host-thread wait (priority inversion on the gate); macOS background QoS pins
  to efficiency cores [Hyp, RQ3]; amends cond. 12. The audio thread never waits on a builder (lock-free mailbox,
  `is_always_lock_free` asserted), so 2, not 3.
- **B1-d 1 / 1.** A process-wide sleeping semaphore around background builds, output-identical; staleness Seats 3, 6.
Conditions: B1-a → 2 if Phase 13's re-check is bound to B1-b's instrument (B1-b deferred by name); B1-c → 1 only if (i) B1-b
shows the rise at real audio priority, (ii) B1-d tried, (iii) the gate holder exempt (keeps default priority); B1-d: class (1)
and offline never take the slot; slot taken before the gate, never holding `stateMutex_`; `quiesce()` wakes slot waiters via the
abandon predicate; TSan `[pipeline]` with 8 pipelines. Premortem: B1-a ships, the rise is real, a Windows dropout while
editing 8 stems, no valid record to compare.

## D-B2 (lead)
Reading: prepare runs on the host's setup thread (VST3 setActive / setupProcessing on the UI thread; AU Initialize); cue 4.3 (a
lifecycle call that builds); 145–430 ms blocks the host's UI thread, not its audio thread (K11).
Ranking: B2-a prefer; B2-d can live with; B2-b only under its condition.
- **B2-a 1 / 1.** One path, tested; exact from the first block after the latency; deterministic after insertion; insertion is
  class (1): waits at most one running solve (≤ 153 ms measured, cond. 12 (b)); later inherits 07c-2's stage-1 rule; overturned
  by RQ5 (host time limit) or the cond. 11 trace showing a stall.
- **B2-b 2 / 2.** Silent 0.15–0.43 s then a fade from silence; as a builder-class waiter it queues behind other instances'
  builder and offline solves (seconds at 100 m); real-time output after insertion timing-dependent (criterion 2); pluginval
  processes straight after prepare, acceptance renders flaky (criterion 3); a third first-IR state for 08, 09, 10 to test.
- **B2-d 1 / 2.** ISM and interim synthesis stay synchronous; only the stage-1 solve saved; a fourth per-platform pinned
  artefact re-pinned at every E_model bump; fails safe (keyless = B2-a); real gain at project load in prepare-first hosts;
  NFR-8 Seat 2's.
Conditions: B2-b → 1 only if RQ5 shows a host/validator time limit below the measured insertion time, insertion stays class (1)
on the builder, and a test pins the fade from silence; B2-d → 1 if the embedded E_b is produced by the CI fingerprint job (no
hand-pinned hex) and the fingerprint test fails on a mismatch. Premortem: B2-b, a producer drops the plugin on a playing stem,
the track vanishes for a second behind seven other instances, KVR post.

## D-B3 (convened)
Reading: determinism and alignment of a self-referential render test; K23 holds.
Ranking: W-a = W-b prefer; W-c, W-d can live with; T-0 only under its condition.
W-a, W-b 0 / 0 (within one platform: identical on three OSes, no cross-OS golden; smaller windows tighter, no statistical
noise); W-c 0 / 1; W-d 1 / 1 (ties a time constant to P ∈ {128, 256, 512}; at 96 kHz 512 = 5.33 ms); T-0 2 / 2 (with g varying
inside a window a speech transient can push E_out above max(E_A, E_B); in the limit E_A + E_B, +3 dB; a false red under "no
re-run" invites an edit).
Arithmetic (K15): W-d's bound is +2.64 dB (ΔG = 512/1440 = 0.3556; 20·log10 1.3556), not +2.88 (that corresponds to T ≈ 11.8
ms); W-a, W-b, W-c check (0.28 / 0.70 / 1.34 dB). Equal-power at ρ = 1, equal-energy components, averaged over 10.67 ms at
mid-fade: 1 + sin(0.559)/0.559 = 1.949 → +2.90 dB; W-d catches the wrong law by ≈ 0.26 dB, W-a/W-b by > 2 dB.
Conditions: T-0 → 1 only with a proof covering a varying g. **Added check:** assert the reconstruction |o − ((1−g)·a + g·b)|
≤ a few ulp per sample, g computed independently from s0 and L, IrSets from the pipeline, deterministic submit (K14), trim 0
dB — tests law, alignment and gain sum exactly against an independent reference. Float ε ≈ 1e-5 relative, energies in double.
Hand-off: at load and insertion no fade from silence happens today (K11); "each fade from silence" needs an engine-level case
with the first submit after k blocks (Seat 3).

## D-B4 (lead)
Reading: cue 4.5 ("which clock, what crosses"); the 1.5–2.6× excess is CPU contention — earlier instances' exact syntheses
run outside the gate at default priority while restore i runs synchronously; architecture, not only the runner (recurs with
fewer cores than syntheses in flight); Windows misses 5 s uncontended (5.07 s), so no single remedy clears every OS.
Ranking: prefer **C6 + C1 together** (own composition), then C1, then C6; can live with C2 (only through the process-wide pool,
only with C6), C7 (fallback if C6 + C1 do not fit an S phase), C8 (residual only), C3, C5; cannot live with C4 as stated.
- **C6 1 / 1** output-identical. Design: a process-wide atomic count of synchronous host calls in flight; background
  syntheses and builders check it at their cancel points (NoiseTail has them) and sleep on a condition variable (no spin) until
  zero or abandon; `quiesce()` wakes them; a thread holding the diffuse gate never pauses (else a class (1) caller waits on a
  paused solver: deadlock); offline (class 2) not paused. Records: pause latency = cancel-point spacing; background starvation
  under repeated restores (pluginval state tests).
- **C1 1 / 1** bit-identical; shared immutable cache built once per key (call_once), off the audio thread; resident size
  counted under AX38 (ii) 128 MB, [Hyp] until measured (K18).
- **C2 1 / 2** parallelism under saturated cores adds contention, feeds D-B1.
- **C7 0 / 2** 07d grows past S–M with the same remedy deferred.
- **C8 1 / 2** ignores the contention, which follows users to their machines.
- **C3 1 / 1**, **C5 1 / 2** (golden round, E_model and fingerprint re-pin): Seats 1, 3, 9 to rate.
- **C4 2 / 2** ≈ 147 MB resident per instance > AX38 (ii) 128 MB; ×8 ≈ 1.2 GB; K20 under-informed (resident or transient,
  per instance or shared).
Conditions: C4 → 1 if transient and counted under (i)'s 1 GB, or shared process-wide (Seat 2 or 3 to state); C2 → 1 if on the
gate's pool, no added threads, with C6; C8 → 1 for the residual after C6 + C1; C7 → 1 if 07d's scope gains the trigger with
C6 + C1 named. **Records for any option:** record (h) prints per instance its restore time, the number of background syntheses
running at its start, hardware threads (answers K17), and a prepare-first total (insertion + restore) beside the trigger.
Premortem: C8 alone, an 8-stem project on a 4-core laptop opens 2× slower than eight single loads; a Windows user notices.

## D-B5 (lead)
**(i)** S2 prefer 0 / 0 (S3 reduces to S2: C1 or C6 change the gated restore path); S3 0 / 1; S1 1 / 2 if any restore-path
change lands (→ 1 only if nothing in D-B1/2/4 touches the restore or builder path). Matches steward G1.
**(ii)** **B-iv** prefer 1 / 1: a within-run ratio cancels runner speed (Linux 2.433–2.606, max/min 1.071; Windows
2.439–2.674, 1.096; macOS 3.318–5.048 stays print-only). Condition: flutter 14 × worst ≤ 30 s stays asserted as the absolute
backstop; absolute medians printed with WARNING; the ratio bound set against the mean of ≥ 3 S2 runs. B-iii 2 / 2 (honest
width ≈ ±22 % on Linux makes the 1.10 growth bound flake under "no re-run"). B-i, B-ii 2 / 1 (B-i keeps none of 453 / 490 / 706
within ±5 % of 550; B-ii keeps one (490): neither yields ≥ 3). If B-iv is refused (FOR MAISARA): print-only absolute growth on
all hosted runners until Phase 13, ratio asserted.
**(iii)** M-a prefer on S2 runs only, 1 / 1; M-b undefined (no in-window macOS run).
**(iv)** Confirm the 05i rule with "in-window" defined by (ii); if an OS lacks ≥ 3 such runs, baselines from ≥ 3 green S2 runs
labelled PROVISIONAL: 0 / 1; print-only, never a (d) trigger.
**(v)** E1 on the S2 runs (worst ≤ 30 s, the 05i Linux precedent) prefer 0 / 0 (today: both stay listed = E3's outcome); E3 can
live with 0 / 1; E2 2 / 2 (closes Windows while one run reads 31.97 s); E4 1 / 1 once runner causation is shown (not shown).
**(vi)** X-a prefer 1 / 0 (the named remedy — 07d: at the low-α cube L_p ≥ L, the restore holds the full synthesis — is
already the macOS entry's 'closes at'; paperwork only). X-b 1 / 2 (a fired trigger read away sets a precedent; → 1 if the
trigger re-derived from S2 runs is applied to 42 and 44 retroactively and the ledger records the reading). **Either way:** a
fired MACTRIGGER (and OVER30S, GROWTH) is emitted as a `::warning::` annotation or written to `$GITHUB_STEP_SUMMARY`, so a
printed defect cannot go unread for two runs again. Seat 7 may rule on the cost of the manual runs.

Hand-offs: Seat 1 (dropout audibility, B2-b silence); Seats 3, 6 (staleness under B1-d, C6); Seat 2 (C1, C4 memory; B2-d
NFR-8); Seat 3 (window power; fade-from-silence cases); Seat 7 and the decider (cost of S2 runs; FOR MAISARA readings of B-iv
and X-b). Researcher: RQ1, RQ2 (does a time-constraint / MMCSS thread preempt the default pool), RQ4, RQ5.
Files read: file 1, phase file, BUILD_PLAN AX38, AX47–AX49, `tests/unit/test_diffuse_records.cpp` (L560–616, L774–826,
L1684–1763), `src/plugin/core/ScenePipeline.cpp` (L380–500, L771–1060), `src/plugin/core/DiffuseSolveGate.h`,
`src/sim/conv/CrossfadingConvolver.{h,cpp}`, `src/sim/RealtimeEngine.h`.
