# Seat 5 (deadline keeper) — positions on D-T5 and D-T4

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## SEAT 5 POSITION: D-T5 (how the switch interacts with the matching)

**1. Reading.** The switch changes what the builder thread computes before it submits an IR: which energy list sets E_target, which list sets k_real/t_mix,e, what the axis shares are taken from, and what `open_field` gets. My cues: §4.5 (which clock it runs on, and what crosses to the callback), S5 (offline must equal real time), §4.1 (denormals) and §4.4 (tests that only cover the happy path). **No option adds a new crossing to the callback.** The diffuse result is folded into the IR before `submit`, so the callback and the allocation-tracker test do not change. This is from the code: `planEmitter` → `buildRoomIR` → the existing IrSet snapshot.

**2–4. Ranking and tension (now / later)**

| option | label | now | later | reason (my measures) |
|---|---|---|---|---|
| 5.1-A | prefer | 1 | 2 | Builder work is the D-T4 matter. Later: the FP-environment hazard below breaks offline = real-time bit identity. |
| 5.1-C | can live with | 1 | 2 | Saves about 5/8 of the band-dependent builder work, but 100 m still needs ≈ 1.1 TB dense (3 TB × 3/8), so the D-T3 picture is the same. It keeps two level models in production and doubles the test surface. It also carries the same FP hazard. |
| 5.2-A | prefer | 0 | 1 | Zero added cost: `energyEntries` already builds the AX16 list from `set.scattered`, and W1 (20.6 ms) and W2 (28.5 ms) already include it. t_mix,e is fixed before matching (`Engine.cpp` L121–148), so the diffuse horizon is known before the solve and the working set can be sized up front, in a single pass. Later: an AX16 list kept alive only for this test. |
| 5.2-B, 5.2-C | not rated (out of bounds) | – | – | – |
| 5.3-D | prefer | 0 | 0 | Costs nothing, is labelled honestly, and does not depend on the AX16 list's future. |
| 5.3-A | prefer (tie) | 0 | 1 | Free under 5.2-A, but it is a diagnostic from a superseded model, which can mislead triage. |
| 5.3-B | can live with | 1 | 2 | Three accumulators per band in the gather. A formulation that computes only the scalar window functional needs up to 3 extra solves, one per weighting `[Inferred]`. That widens D-T1's output for an ungated diagnostic. |
| 5.3-C | can live with | 2 | 2 | Phase 08's binaural build per rebuild grows (W1/W2 in binaural mode), Phase 08 gains a dependency on 05h, and binaural goldens become coupled to D-T1's output format. |
| 5.4-A | prefer | 1 | 1 | Two tests and one golden are replaced. It is generic, with no new branch. |
| 5.4-B | can live with | 1 | 2 | Adds a special branch that every later formulation and the Phase 10 cache must reproduce. An exact-zero test flips between FTZ-on (offline) and FTZ-off (builder) paths. |

**5. Evidence**
- **FP-environment split** `[from the code]`:
  - The offline synchronous build runs inside `processBlock` under `juce::ScopedNoDenormals`. Path: `PluginProcessor.cpp` L166/L181 → `ScenePipeline::process` L400–402 → `decide(Source::Offline)`.
  - The builder thread (`IrBuilderThread.cpp` L29), the synchronous prepare/restore builds (`ScenePipeline.cpp` L271, L322) and `render_cli` set no FP mode.
  - Today this is latent because the build runs in double and only the output is flushed (`toFloatNoDenormal`, `Engine.cpp` L49).
  - A float32 kernel (as in `ref_hybrid`, phase-05b2 §0.3) with energy shrinking per generation reaches float denormals: (0.01)^20 = 1e-40 < 1.18e-38 after about 20 hits at α 0.99. The offline path flushes those values and the builder does not, so offline ≠ real time `[Inferred]`. Builder slowdown on denormals is `[Hypothesis]`; the researcher could find a base rate.
- **Tests that break** `[from the code]`:
  - `test_hybrid_ir.cpp` L234–261: `bandsAmplitude == 0` and `bandsNonZeroEntries == 0`. Its −60 dB late check probably still holds `[Hypothesis]`.
  - `test_tail.py::test_open_field_has_no_tail` L194–203.
  - Golden `phase04_open_field_omni`:
    - The IR is 86 549 samples (1.80 s) and the tail would fill about 1.40–1.80 s.
    - The Lundeby noise estimate would then see the tail, so the T20/T30/EDT pins (1 % rel) can move `[Hypothesis]`.
    - The "no late energy (> 60 dB)" sentinels flip by platform if the tail sits near 60 dB; the comment at `test_tail.py` L446 records that flakiness.
  - Unchanged under 5.2-A, and they should stay as gates: `test_tail.py` L147 (k_real from the image list, the fallback, t_cap) and `test_cli.cpp` L159 (`--images`).
- **`open_field` window** `[Inferred, arithmetic]`:
  - Floor arrivals end at about 0.42 s: the farthest corner path is ≈ 145 m from the fixture coordinates.
  - The referral weight is exp(+rate·t) (`NoiseTail.cpp` L230); at 1 kHz the rate is 13.8/0.636 ≈ 21.7 s⁻¹.
  - `ground_scatter.py` defaults to an infinite plane (docstring L14–15). An infinite-plane reference would put arrivals up to 1.4 s at up to ≈ +93 dB of weight, so it is **not** an independent reference for the window value. It must use the finite floor (`half_width`).
  - My rough level for E_b per 10 ms at t_mix is ≈ −150 dB re the direct sound at 1 kHz and ≈ −100 dB at 63 Hz `[Hypothesis]`; C1 decides.
- Corpus present (c1b171f). These are engineering claims; the corpus does not cover them.

**6. Conditions of acceptance**
- **5.1-A / 5.1-C, later 2 → 1:**
  - `buildRoomIR` sets FTZ/DAZ itself on entry and restores the caller's mode on exit. `sim/conv/Denormals.h` already provides this without JUCE.
  - Window sums accumulate in double.
  - A `[pipeline]` test builds the same scene with the caller's FTZ on and off, including an absorbent room, and requires bit-identical IRs on all three OSes.
- **5.1-C, later 2 → 1:** the switched band set is one constant (like `kRealisedKBands`), so that going to 8 bands is a parameter change.
- **5.3-B, later 2 → 1:** the direction tallies are computed only on the `render_cli --diagnostics` path, never in the plugin builder.
- **5.3-C, 2/2 → 1/1:**
  - RQ6 gives a perceptual basis (Seats 1 and 4).
  - The direction data are fixed-size arrays inside the IR snapshot.
  - Phase 08 records binaural W1/W2 with them.
  - The 08 → 05h dependency is written down.
- **5.4-B, later 2 → 1:** the rule tests only structural zeros (α = 1, pruned images, as AX20/AX22 already do), never a float threshold. The FP condition above also applies.

**Test replacement and gating (5.4-A).** All of these are deterministic, run in seconds, and belong in **PR CI on three OSes**, not nightly.
- **C++:** check E_b finite and ≥ 0. Replace the "== 0" checks with "energy after 50 ms ≤ the ledger OF bound per band", for s ∈ {0.4, 0.5}.
- **Python:** compare the diffuse E_target from `--diagnostics` with a new finite-floor window integral (Hann weight, Eyring referral) that does not import `ref_hybrid`. Compare in the log domain, at D-T1's tolerance.
- **Golden:** update only through `update_goldens.py`. First confirm that every sentinel band sits ≥ 10 dB from 60 dB on every OS.
- **Unchanged:** keep `test_tail.py` L147 and `test_cli.cpp` L159 as they are. They are the proof that AX22 did not move.

**Phase 10 continuity.** Under 5.2-A the AX22 jump point and the Phase 10 gate formula stay as they are; only E₁ and E₂ at the jump change, and Phase 10 measures those. The cache key must include the window horizon.

**7. Hand-offs**
- Seat 2: whether the patch discretisation near the floor edge meets D-T1's tolerance against an exact finite-floor integral under exp(+rate·t) weighting.
- Seat 1: whether C1's `open_field` level is audible.
- Seat 3: discretisation steps under position automation.
- Seat 4: whether Phase 08 needs 5.3-C.

**8. Premortem.** The switch ships without a fixed FP mode, an absorbent-room bounce flushes denormals that the builder kept, and the offline render ≠ the real-time render. The first to notice is the acceptance-render diff, or the contractor's determinism check.

---

## SEAT 5 POSITION: D-T4 (cost budget)

**1. Reading.** How much the diffuse computation may use per instance, and what blocks. My cues: §4.2 ("crashes only after N instances"), §10.3 (what the host can do to me: state load, bounce, validators) and §4.5. The clocks involved, from the code:
- **Builder:** one `std::thread` per instance (`IrBuilderThread.cpp` L29, owned by `ScenePipeline.cpp` L88). No priority is set and nothing coordinates across instances, so K concurrent rebuilds give K × the transient peak.
- **Caller's thread:** synchronous builds on prepare (L271) and restore/setState (L322).
- **Host offline thread:** a synchronous build on every block whose scene changed (L400–402; AX33 sets no cap offline).

**Does a ceiling rule out every class at 100 m?** No, by arithmetic `[Inferred; Seat 2 decides]`.
- The dense kernel (3–6 TB) is out under all three ceilings.
- A per-band patch history N·T in float32 needs 9 600 × 1 035 × 4 B ≈ 40 MB, and ≈ 81 MB at T ≈ 2 100 (fallback). Solved band by band and emitter by emitter, that fits even 4a-1.
- A particle estimator holds about O(bins).
- One N² float32 matrix needs ≈ 369 MB: out under 4a-1, in under 4a-2 and 4a-3.
- So memory alone does not force D-T3; time may.

**2–4. Ranking and tension (now / later)**

| option | label | now | later | reason |
|---|---|---|---|---|
| 4a-1 ≤ 128 MB | prefer | 1 | 1 | 8 concurrent builders × 128 MB ≈ 1 GB. It excludes the N²-storage classes at 100 m. |
| 4a-2 ≤ 1 GB | can live with | 2 | 2 | 8 concurrent room-automation rebuilds ≈ 8 GB transient. Memory pressure leads to swapping or compression, then page faults on the audio thread, and the callback deadline is no longer bounded `[Hypothesis]`. |
| 4a-3 ≤ 4 GB | **cannot live with** | 3 | 3 | Four instances ≈ 16 GB transient. One instance alone takes a quarter of a 16 GB machine (RQ1). |
| 4b-2 (no cache credit) | prefer | 0 | 1 | Measures the worst position-only rebuild. It may trigger the Table 15.1 remedy early; reversible through an AX. |
| 4b-1 (cache credit) | can live with | 1 | 2 | A cache is a classic offline ≠ real-time source: the bounce and state load start cold, playback runs warm. Resident memory × N instances. |
| 4c-1 | prefer | 1 | 2 | Nothing gates the synchronous paths at the largest room: state load and prepare on the host's thread, pluginval's repeated state restores. |
| 4c-2 | can live with | 1 | 1 | The usability anchor belongs to Seats 6 and 8. It would subsume my timeout bound if its limit is lower. |
| 4c-3 | **cannot live with** | 2 | 3 | Transient memory is unbounded once D-T1 ships. |

No memory-adaptive fallback at runtime: a builder that picks a cheaper path when RAM is low makes the IR depend on the machine, which breaks AX5 and offline = real time. The ceiling has to be met by design.

**5. Evidence**
- From the code: the thread ownership and synchronous paths above.
- From the code: CI runs pluginval with `--timeout-ms 120000` (`run_pluginval.sh` L19). I believe pluginval's own default is 30 s `[Hypothesis]`, so CI is about 4× more lenient than a user's run (RQ4 to verify).
- From the code, offline bounce: the rebuild count is the number of changed blocks. With continuous automation at 512 samples and 48 kHz that is ≈ 94 builds per audio second, so an added diffuse time t_d adds ≈ 94·t_d seconds of bounce per audio second `[Inferred]`. Please measure rather than take my word.
- §0 row 07: +122.6 MB resident (last built and last submitted IR/IrSet), Linux only. Full rebuild 603–1 884 ms.
- §0 row 06: callback p99.9 at host buffer 64 is already 66.6 % on Linux, above my half-buffer headroom rule. Memory-bandwidth contention from concurrent builders is an unmeasured stressor `[Hypothesis]`.
- Vorländer Table 15.1 (corpus L3959–3964), as AQ10 cites it.

**6. Conditions of acceptance**
- **4a-2, 2/2 → 1/1:**
  - A process-wide gate allows one diffuse solve in flight per process, so the transient counts once per process.
  - Resident memory between rebuilds is ≤ 128 MB per instance.
  - The callback-histogram record below runs under concurrent solves.
  - Caveat: Bitwig's per-plugin sandboxing defeats a per-process gate.
- **4a-3, 3/3 → 2/2:** the same gate and resident limit. A single 4 GB transient stays risky on 8–16 GB machines.
- **4b-1, later 2 → 1:**
  - The cache is keyed by a content hash of (room, materials, rate, window horizon), not by change notifications.
  - A cold build and a warm build are bit-identical in CI on three OSes.
  - Resident memory is counted in (a), × instances.
- **4c-1, later 2 → 1:**
  - Extend the existing criterion "pluginval strictness 10 and auval still pass" (phase-05b2 §5) to the largest room.
  - Concretely: a Catch2 `[pipeline]` test runs the synchronous restore/prepare at 100 m, 96 kHz, both emitters.
  - It fails above a bound derived from pluginval's **default** per-test timeout divided by the number of restores a strictness-10 test performs. RQ4 supplies both numbers; record only until then.
  - This is a host-conformance gate, not a usability budget. The decider should rule whether it amends AQ10.
- **4c-3, later 3 → 1:** memory over the ceiling blocks, as in 4c-1.

**CI gates.**
- **Block:**
  - Allocation-free callback (existing tracker).
  - TSan `[conv],[pipeline]` with the diffuse builder running.
  - pluginval strictness 10 (3 OSes) and auval.
  - The largest-room synchronous-restore test, once RQ4 answers.
  - Peak working-set delta of a 100 m, 96 kHz, 2-emitter build ≤ the ceiling. Gated on Linux; recorded on macOS and Windows until Phase 13.
  - Builder, offline and `render_cli` IRs bit-identical (the D-T5 FP condition).
  - No NaN, Inf or denormals.
- **Record:**
  - W1/W2.
  - Full rebuild at the AQ10 room, CR4 and 100 m, at 48 and 96 kHz.
  - Synchronous state-load time per instance.
  - Offline-bounce factor for 10 s position and room-size automation sweeps.
  - Callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders running the 100 m build (Linux and Windows CI; macOS on hardware under phase-13 item 9).

**7. Hand-offs.**
- Seat 2: whether any class fits each ceiling in time.
- Seats 6 and 8: the usability and bounce-time limit (4c-2).
- Seat 7: customer RAM and the cost of D-T3.
- Phase 07 follow-up (not D-T4): synchronous builds on the message thread during session load scale with instances × full rebuild.
- Researcher:
  - pluginval v1.0.4's default `--timeout-ms`, and how many restore and fuzz iterations strictness 10 runs (from the source).
  - Host behaviour on a slow `setStateInformation` or `prepareToPlay` on the main thread (Logic AU, Ableton, Cubase).
  - Whether any host aborts a slow offline render.
  - Audio-thread page faults under memory pressure (macOS compression, Windows paging): incidents.
  - The denormal slowdown factor on x86 and ARM.
  - RQ1 and RQ3.

**8. Premortem.** A 1–4 GB ceiling is chosen without a process-wide gate. A beta user on a 16 GB laptop automates room size in six instances, the machine pages, and the first reports are dropouts and a frozen DAW while builds run. A beta tester notices before CI does, because CI only ever runs one instance.
