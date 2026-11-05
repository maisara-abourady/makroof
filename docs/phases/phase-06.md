# Phase 06 — Real-time partitioned convolution + latency

Size: **M** · Depends on: 02, 04 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ4, AQ10, AX1), PRD NFR-2, NFR-3

## Goal

A **real-time-safe convolution engine** in `src/sim/` that applies multi-second room IRs
(N inputs × M outputs, 2×2 in v1) with fixed, reportable latency. It must swap IRs with a click-free
crossfade. Phase 10 builds movement on top of that swap.

## Assumptions in force

- **AQ10**: latency ≤ 512 samples at 48 kHz; CPU ≤ 15% of one core per 2×2 instance with a 3 s IR at
  48 kHz/512-sample buffer.
- **AQ4**: IR change = crossfade between two convolver states over **30 ms**.
- **AX15**: the crossfade law is chosen per request: **equal-gain** (linear complementary ramps) for
  position updates, where consecutive IRs are highly correlated; **equal-power** (sin/cos ramps) for
  switches between unrelated IRs (Phase 09 mode switch, Phase 10 large jumps), because equal-gain on
  uncorrelated outputs dips ≈3 dB mid-fade (Vorländer §9.2.1, §15.1.1). The swap API must support both laws.
- **AX1**: pre-roll from Phase 03 (`kAlignPreRollSamples`) is part of the reported latency.

## Scope

1. `src/sim/conv/Fft.h/.cpp` — thin wrapper over **PFFFT** (pinned via FetchContent; add it to
   `docs/THIRD_PARTY.md`). Real FFT, aligned buffers, size fixed at construction.
2. `src/sim/conv/PartitionedConvolver.h/.cpp` — uniformly partitioned overlap-save (UPOLS) with a
   frequency-domain delay line:
   - Partition size P ∈ {128, 256, 512} (default 512), FFT size 2P.
   - `prepare(maxBlock, P)` does all allocation. `process(const float* in, float* out, int n)` accepts
     **any** n (1…maxBlock) and accumulates internally into P-sized blocks. Latency = P samples.
   - `IrSet` = pre-transformed IR partitions for an N×M matrix. Built **off the audio thread** by
     `IrSet::create(const RoomIR&, P)`. `RoomIR` is the struct from Phase 02.
3. `src/sim/conv/CrossfadingConvolver.h/.cpp` — owns two convolver states, A and B, sharing input
   history. `requestIr(std::shared_ptr<const IrSet>)` is called from a non-audio thread and hands
   over through a lock-free single-slot mailbox (atomic pointer exchange). On the audio thread, a
   pending IR starts a 30 ms crossfade from the current to the new state. If another IR arrives during a
   crossfade, it waits in the mailbox (latest wins) and starts when the current fade ends. Old
   `IrSet`s are released on a non-audio thread (deferred-release queue drained by the caller), never
   freed on the audio thread.
4. `sim::RealtimeEngine` façade: `prepare(sampleRate, maxBlock)`, `process(in[2], out[2], n)`,
   `latencySamples()`, `submitRoomIR(RoomIR)`. This is what the plugin will call in Phase 07.
5. Denormals: set flush-to-zero/denormals-are-zero inside `process` (scoped guard; `juce::ScopedNoDenormals`
   isn't available because `sim` is JUCE-free, so write an equivalent for x86 SSE and ARM FPCR).
6. **Allocation guard for tests:** `tests/support/AllocationTracker` overrides global `operator new`
   and `operator delete` in the test binary and counts allocations on a flagged thread. Tests assert zero
   allocations in `process`.
7. `render_cli --realtime-emulation --block <n>` renders through `RealtimeEngine` in blocks of n (with
   random sizes when `--block random`), so offline reference and real-time paths can be nulled.
8. Benchmark: 2×2, IR lengths 1, 3, 6, 12 s, P = 256/512, at 48 kHz. Print the per-block time as % of the
   real-time budget, for each CI OS.

## Out of scope

Plugin parameters/state (07); movement policy, rate limiting and smoothing (10); non-uniform
partitioning (a possible follow-up if 12 s IRs blow the budget).

## Acceptance criteria — automated

- [ ] `PartitionedConvolver` output equals `sim::OfflineRender` (direct convolution reference from
      Phase 02), delayed by P, within **−120 dB** (residual/signal energy) for random IRs (lengths 1,
      P−1, P, P+1, 48 000, 144 000) and random inputs, at host block sizes **1, 37, 64, 512, 2048** and
      random sizes.
- [ ] `render_cli --realtime-emulation --block random` nulls against the offline render of a Phase 04
      room IR within −120 dB.
- [ ] Crossfade test: switching IR A→B mid-signal equals the analytic result
      `(1−g(t))·(x*A) + g(t)·(x*B)` within −100 dB, with g a 30 ms linear ramp starting at the block
      boundary where the swap is picked up.
- [ ] Back-to-back `requestIr` calls (100 in 1 s) neither crash nor leak (ASan) and the last IR wins.
- [ ] **Zero heap allocations** in `process` (AllocationTracker) for all block sizes, including during crossfades.
- [ ] TSan job (Linux) passes on a test that hammers `requestIr` from 2 threads while the audio thread processes.
- [ ] `latencySamples()` equals the measured offset of an impulse through a delta IR (exactly P + pre-roll).
- [ ] Benchmark prints in CI. 3 s IR, P = 512 at 48 kHz: ≤ 15% of the real-time budget on the macOS
      runner (AQ10). If missed, record it in the status notes; don't fail CI on runner noise.

## Listening / manual checklist (Maisara)

- [ ] Listening pack: `drums_medium_room_offline.wav` vs `drums_medium_room_realtime.wav` sound identical
      (CI already proved the null, so this is a sanity listen).
- [ ] `ir_switch_demo.wav`: a tone through a room that switches every 0.5 s between `living_room` and
      `concert_hall_box`. You should hear the room change with **no clicks**.

## Contractor review focus

UPOLS indexing and overlap-save correctness, the lock-free handover and memory-reclamation strategy,
denormal handling on ARM and x86, and crossfade timing semantics.

## Risks

- CPU for long IRs: 12 s × 2×2 at P = 512 is about 1 100 partitions per path. Measure it. Non-uniform
  partitioning is the known fix, kept as a follow-up.
- Memory reclamation bugs in the IR swap. Mitigated by TSan/ASan and the deferred-release queue.

## Definition of done

All automated criteria green; benchmark numbers in the status notes; status row 06 `done`.
