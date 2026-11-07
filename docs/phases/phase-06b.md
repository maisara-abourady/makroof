# Phase 06b — Phase 06 decisions and follow-ups

Size: **S** · Depends on: 06 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §0 (row 06 notes) and §2 (AQ4, AQ10, AX1, AX18, AX31), `docs/phases/phase-06.md`, the PR #14 description sections "Raise with Maisara" and "Follow-ups (not done here)" (GitHub), `docs/sessions/2026-11-07-phase-06.md`, `docs/sessions/2026-11-07-phase-06-followups.md`, `docs/review/phase-06/review-PR14-followups-at-31894b6.md`, `docs/review/ledger.md` rows P06F-1 … P06F-14

Created on 2026-11-07 at Maisara's request ("Create a phase for the two pending decisions and what is
left for later") for the two decisions Phase 06 put to her and the PR #14 follow-ups that no other
phase file plans, as a fresh session. **Phase 07 waits only for decision 1** (`docs/phases/phase-07.md`
"Raise with Maisara"), not for the rest of this phase.

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**. Both
decisions are hers; this phase records her answer and applies it.

**Status (2026-11-07):** both decided by the phase-06b decision loop (decider, interrogator, advocate;
`docs/review/phase-06b/decider-round2.md`, ledger P06B-7 … P06B-73) on Maisara's instruction ("I have
created an entire workflow described in claude.md so you don't ask me these" / "Same answer"): decision 1
**(a)** (D1), decision 2 **AX31 confirmed** (D2). Both remain proposals Maisara can veto; the session
still raises them so that she can.

1. **Latency reading (AQ10).** At the default partition size P = 512, `latencySamples()` = P + 32
   samples of pre-roll (AX1) = **544 samples**. AQ10 says "≤ 512 samples at 48 kHz (convolution partition
   size)": read as the total reported latency, 544 is over it; read as the partition size, P = 512 meets it.
   - **(a)** Keep P = 512 and reword AQ10 so the partition size is the budgeted quantity and the reported
     latency is P + the AX1 pre-roll (544 samples).
   - **(b)** Make P = 256 the default (reported latency 256 + 32 = 288 samples).
   - CPU at P = 256 (2×2, 48 kHz, mean % of the real-time budget, steady / crossfading; CI run
     42397114233, `[benchmark]` logs of build jobs 128476751836 Linux, 128476751649 macOS,
     128476751804 Windows):
     - 3 s IR, host buffer 512 (the AQ10 case, ≤ 15 %): Linux 7.0 / 12.6 %, macOS 3.5 / 6.5 %,
       Windows 3.2 / 5.4 %. The same case at P = 512 (§0 row 06): Linux 3.3 / 6.3 %, macOS 2.1 / 4.3 %,
       Windows 1.5 / 2.6 %.
     - 12 s IR, P = 256, while crossfading: over budget on Linux (host 64, mean 103.2 %); Windows
       64.2 %, macOS 48.9 % (PR #14 'For the Expert'). Non-uniform partitioning is planned for that
       (`docs/phases/phase-13.md` scope 1, Maisara 2026-11-07).
2. **AX31: confirm or veto.** Decided by decider D1, interrogator SURVIVES WITH CORRECTIONS, advocate
   PASS (ledger P06F-1); vetoable by her. With the work spread over host callbacks, an isolated update
   reaches the output **one partition later** (10.7 ms at P = 512, 48 kHz; 5.3 ms at P = 256, AX31).
   Back-to-back updates keep the AQ4 pace and the reported latency is unchanged. The alternatives
   rejected in AX31 (catch-up at pickup, or computing the whole first block at pickup) restore the old
   timing but put a block of one state's work into one callback on every swap.

## What the session does per answer

- **Latency (a):** AQ10 reworded through `/fix-plan` (interrogator check; ledger row); §6 row. No code
  change.
- **Latency (b):**
  - change `conv::kDefaultPartitionSize` (`src/sim/conv/PartitionedConvolver.h`) to 256; render_cli
    takes its default from it (`src/cli/Cli.cpp`), so update its `--partition` help text "(default 512)";
  - AQ10 text and the phase-06 text that names the default (scope 2 "default 512", AC 8 "P = 512")
    through `/fix-plan` (interrogator check; ledger row). Which P the AQ10 CPU check measures from then
    on, and whether `phase-13.md` scope 1 and item 9 (measured at P = 512) are restated, are decided
    through `/fix-plan` in the 06b session;
  - re-run the phase-06 automated acceptance tests (they already cover P = 128, 256 and 512), the
    `[benchmark]` test and the phase-06 listening pack (`tools/ci/listening_pack.py --phase phase-06`
    uses the default partition);
  - update the `CLAUDE.md` commands if any of them names the default; §0 row 06 notes and §6 row.
- **AX31 confirmed:** ledger row and §6 row "accepted by Maisara <date>"; the AX31 row's "vetoable by
  Maisara" becomes the acceptance. No code change.
- **AX31 vetoed:** a new decision loop (decider → interrogator → advocate, through `/fix-plan`) picks the
  replacement among the alternatives recorded in AX31; the AX31 row is replaced through `/fix-plan`;
  `CrossfadingConvolver`, the crossfade acceptance test (phase-06 AC 3, s0 and `fadeStartSample()`)
  and the per-call multiply-add tests change accordingly; the phase-06 automated acceptance tests and
  the benchmark are re-run; §6 row.

## Goal

Record both decisions and apply them, and close the PR #14 follow-ups that no other phase plans: input
and IR guards, a test binary that fails fast after a crash, and a pinned summation order.

## Assumptions in force

As `docs/BUILD_PLAN.md` §2, unchanged unless a decision above changes them:

- **AQ4**: IR change = 30 ms crossfade between two convolver states; updates capped at one per 20 ms;
  back-to-back fades rounded to whole partitions (32 ms at 48 kHz while the rebuild is ≤ 32 ms);
  isolated-update delay slot wait + rebuild + 2P.
- **AQ10**: partition size P ≤ 512 samples at 48 kHz (default P = 512); reported latency P + the AX1
  pre-roll = 544 samples (11.3 ms) at the default (decision 1, recorded as D1 (a), 2026-11-07; vetoable
  by Maisara); CPU ≤ 15 % of one core per instance, 3 s tail, 48 kHz / 512-sample buffer.
- **AX1**: the Phase 03 pre-roll (`kAlignPreRollSamples`; 32 samples, AX31 and §0 row 06) is part of the
  reported latency.
- **AX18**: equal-gain crossfade for position updates, equal-power between unrelated IRs.
- **AX31**: real-time IR pickup under work spreading, s0 = (⌊r/P⌋ + 2)·P (decision 2: confirmed, D2,
  2026-11-07; vetoable by Maisara).
- **AX32**: input samples with |x| > B = 2²⁰ (+120.4 dB re 1.0), ±Inf or NaN are replaced by 0 before the
  forward FFT (scope 3; D3, 2026-11-07; vetoable by Maisara).

## Start here

Phase 06 is done (PR #14). Commands as `CLAUDE.md` "Build and test", in particular

```bash
ctest --preset debug
build/release/tests/unit/spatial_tests "[benchmark]" --benchmark-samples 10
python tools/ci/listening_pack.py --phase phase-06
```

## Scope

1. **Decision 1 (latency reading)** recorded and applied as "What the session does per answer".
2. **Decision 2 (AX31)** recorded and applied as "What the session does per answer".
3. **Bounded input samples.** The engine zeroes NaN/±Inf input (Phase 06), but a finite sample of huge
   magnitude (about 1e38, re-review `review-PR14-followups-at-31894b6.md` Minor 2; PR #14 follow-ups)
   overflows to Inf inside the forward FFT and poisons the frequency-domain delay line for the IR
   length. Bound finite input samples so that this cannot happen. **The bound and how an out-of-bound
   sample is treated are decided through `/fix-plan` in the 06b session (an AX row)**; no value is
   proposed here. Decided 2026-11-07: **AX32** (`docs/BUILD_PLAN.md` §2; phase-06b D3): bound B = 2²⁰,
   a sample with |x| > B, ±Inf or NaN is replaced by 0; the AX32 row also fixes the test.
   Outcome: the AX row exists (ledger row, §6 row) and a test proves it.
4. **Finite IR taps.** `IrSet::create` / `RealtimeEngine::makeIrSet` reject an IR with any non-finite tap
   (re-review Minor 2, prior m6), so `submitRoomIR` returns false and the engine keeps its current IR,
   as for an IR that doesn't fit.
   Outcome: a test covers NaN, +Inf and −Inf taps.
5. **Fail fast after a crash.** A test that crashes (SIGABRT) must end the test binary promptly instead
   of stalling until the 600 s ctest timeout (`CMakePresets.json`); the re-review saw the binary block
   in a futex after a heap-corrupting mutant (re-review Questions 3). How is a 06b design choice
   (software only; e.g. `CATCH_CONFIG_NO_POSIX_SIGNALS`, as the re-review suggests, or another mechanism).
   Outcome: checkable as in the acceptance criteria.
6. **Pin the summation order.** The phase-06 follow-ups sum the partitions late-first (descending k);
   it raised the render_cli null at P = 128 from −124.9 to −128.6 dB (§0 row 06 notes; commit
   89770db; `CrossfadingConvolver.cpp` comment), but no C++ test pins it: the ascending-order mutant
   passes `[conv]` (re-review Minor 5). Add a C++ test that fails on ascending order. **Its threshold is
   derived from a measurement recorded in the 06b session (ascending and descending residuals, in the
   PR); the rule from measurement to threshold is decided through `/fix-plan` in the 06b session**, not
   invented.
   Decided 2026-11-07 (phase-06b D4): `CrossfadingConvolver` 1 × 1 at P = 128, 256, 512, seeded random
   host blocks ≤ 512, input x ≡ 1.0, IR of K = T + 2 partitions with **T = 400** (partition 0 zero;
   partition 1 one tap 1.0; partitions 2 … K − 1 one tap 2⁻²⁵ each), render length ≥ (K + 4)·P; over the
   last P samples, **max |y − (1 + 400·2⁻²⁵)| ≤ 50 ulp(1) = 50·2⁻²³**. Every operation that reaches the
   output is exact (power-of-two taps and IR scale 1/2P; the input spectrum is DC-only, so H's rounded
   non-DC bins meet exact zeros), so descending gives exactly 0 and ascending exactly T/4 = 100 ulp
   (M2(b); P06B-27, 29, 57); any threshold in [0, 100) separates them, and 50 ulp, the midpoint, is a
   free maximin margin (P06B-58). The measured error (expected 0 on SSE and NEON) is printed for the PR.
   No FMA margin (P06B-29). M2(a) is not a gate; it stays in `measurements.md` (the AC 2 −120 dB gate is
   unchanged). Mutation evidence: `kk = k` fails (100 ulp); a partial reorder with ≤ 200 tiny terms
   after the 1.0 would pass (P06B-59), which the criterion (ascending mutant) accepts. A non-zero
   descending error on any platform means the case is not exact there: report it and redesign the
   case, never re-threshold.
7. **Bookkeeping.** Status row 06b `in progress`, then `done` with the PR link; PR description per
   `CLAUDE.md`; steward brief.

## Out of scope

- Non-uniform partitioning (12 s IR at P = 256): `docs/phases/phase-13.md` scope 1.
- MSVC/ARM64 flush-to-zero guard: `docs/phases/phase-13.md` scope item 8.
- Real-hardware macOS small-buffer timing: `docs/phases/phase-13.md` scope item 9.
- Phase 07 builder-thread lifetime and using `RealtimeEngine`: `docs/phases/phase-07.md` scope 3.
- Vorländer Table 15.1's head-rotation row (35 ms; filter content 'new HRTF') with the AX3 centroid
  yaw (ledger P06F-4): `docs/phases/phase-08.md` scope item 8 (added with this phase).
- Whether the 20 ms cap delays an isolated request (AQ4): `docs/phases/phase-10.md` scope item 8 (added
  with this phase).
- PFFFT v1.2.0: no item. The pin is by commit as policy (`CLAUDE.md`), v1.1.0 meets every phase-06
  criterion, and an upgrade needs a reason, which no follow-up gives.

## Acceptance criteria — automated

- [ ] Both decisions recorded: Maisara's words verbatim in the 06b session brief, and in the ledger and
      a §6 row.
- [ ] If decision 1 is (b): `latencySamples()` = 288 at the default P = 256 (phase-06 AC 7, P + 32
      pre-roll, AX1), and the phase-06 automated acceptance criteria pass again in CI on Linux, macOS
      and Windows, with the benchmark printed.
- [ ] If decision 2 is a veto: the replacement's acceptance tests (changed phase-06 AC 3 and the
      per-call multiply-add tests) pass in CI on 3 OSes.
- [ ] Scope 3: a test feeds finite samples of magnitude about 1e38 (re-review Minor 2) and shows that
      the output stays finite and the delay line is not poisoned; its reference and tolerance are part
      of the scope 3 AX row (precedent: the phase-06 non-finite input test, −120 dB against the render
      of the input with those samples zeroed). The phase-06 nulls still pass at their gates (−120 dB
      for AC 1 and 2, −100 dB for AC 3).
- [ ] Scope 4: an IR with a NaN, +Inf or −Inf tap is rejected (`makeIrSet` gives nullptr,
      `submitRoomIR` returns false) and the output keeps the current IR.
- [ ] Scope 5: a deliberately crashing test (SIGABRT probe, not committed as a failing test) makes ctest
      report that test as failed without reaching its 600 s timeout; the measured time to failure is
      quoted in the PR.
- [ ] Scope 6: the summation-order test passes on the descending order and fails on the ascending-order
      mutant (mutation evidence in the PR); its threshold and the measurement it comes from are in the
      PR and the ledger.
- [ ] TSan and ASan + UBSan jobs green; zero heap allocations in `process` still hold (phase-06 AC 5)
      with the scope 3 bound in place.
- [ ] CI green on Linux, macOS and Windows.

## Listening / manual checklist (Maisara)

None, unless decision 1 is (b). Then, from the head run's `listening-pack` artifact, folder `phase-06/`:

- [ ] `drums_medium_room_offline.wav` vs `drums_medium_room_realtime.wav` still sound identical.
- [ ] `ir_switch_demo.wav` still switches rooms with **no clicks**.

## Contractor review focus

Where the scope 3 bound sits relative to the non-finite guard and the forward FFT (the delay line must
never receive a non-finite spectrum); the finiteness check in `IrSet::create`; the fail-fast mechanism
(does it still report which test crashed?); whether the summation-order test pins the order rather than
one platform's rounding; under (b), every place that assumed P = 512.

## Risks

A bound set too low would change in-range audio; the phase-06 null tests at their unchanged gates are
the guard.

## Definition of done

Automated criteria green; both decisions recorded and applied (ledger, §6, plan files); the scope 3
AX row and the scope 6 threshold recorded through `/fix-plan`; status row 06b `done` with the PR link.
