# Phase 06b — decider, round 2: final texts (2026-11-07, corpus c1b171f)

Applies interrogator round 1 (P06B-31…60) and advocate round 1 (D1 REDIRECT; D2 wording). No load-bearing
claim fell. D1 revised (no Linux-runner premise); D2, D3, D4 stand with revised wording.

## D1 — (a), confidence medium; answer to the REDIRECT: yes, (a) follows without the Linux runner

1. For a fixed IR, after latency compensation, P does not change the output (UPOLS nulls ≤ −129.8 dB at
   P = 128/256/512, §0 row 06); under an update s0 = (⌊r/P⌋ + 2)·P depends on P (AX31) [P06B-31]. The extra
   256 samples buy CPU headroom, not accuracy; NFR-2's "latency acceptable when it buys accuracy" favours
   neither; only the 32-sample pre-roll buys accuracy (AX1) and is in both [P06B-40].
2. The latency costs a playback/bounce user nothing extra: automatic PDC (Izhaki Ch. 11); the result reaches
   the track by bounce (PRD A4); Izhaki App. A: PDC can misalign a bounce at any non-zero latency, 288 as
   much as 544 [P06B-35].
3. The benefit of (b) is unsourced and outside the PRD's stated use: Izhaki Ch. 11 says buffer latency is
   "important in recording, less in mixdown"; plugin latency adding to input monitoring is outside the corpus
   (F9, F10, read) [P06B-34]; the PRD is silent on tracking; its use is "hear their track" (product reading).
4. The cost of (b) is measured on all three OSes: 1.5–2.1× convolution CPU per instance (run 42397114233, 3 s,
   host 512; crossfading 2.00/1.51/2.08, steady 2.12/1.67/2.13 Linux/macOS/Windows) [P06B-32], multiplied
   across instances (FR-SIM-7, A5; phase-13 scope 3: 10).
5. Like with like: host 64 / 12 s crossfading has means only at P = 256 (Windows 64.2 %, macOS 48.9 %; Linux
   runner 103.2 %) [P06B-36] and p99.9 only at P = 512 (Windows 32.2 %; macOS thread-CPU 109.9 %, unproven);
   no same-statistic pair, so no host-64 conclusion beyond: per-sample work at P = 256 ≈ 2× (4), and on macOS
   even P = 512 is unproven there [P06B-33, 39]. The Linux 103.2 % stays as a CI-runner fact (NFR-4).
Reversal: tracking or live monitoring through the plugin declared a v1 use; 13b lands.

**AQ10 first sentence (rest unchanged):**
> Convolution partition size **P ≤ 512 samples at 48 kHz** (default P = 512, `conv::kDefaultPartitionSize`); the **reported latency is P + the AX1 pre-roll (32 samples) = 544 samples (11.3 ms at 48 kHz) at the default**. For a fixed IR, after latency compensation, P does not change the output (UPOLS nulls ≤ −129.8 dB at P = 128, 256, 512, §0 row 06; under an update the fade start depends on P, AX31). Halving P costs 1.5–2.1× convolution CPU per instance (3 s IR, host 512, run 42397114233: crossfading Linux 6.3 → 12.6 %, macOS 4.3 → 6.5 %, Windows 2.6 → 5.4 %) and buys no accuracy (NFR-2). Sequencers compensate reported plugin delay automatically (Izhaki Ch. 11); buffer latency is "important in recording, less in mixdown" (Izhaki Ch. 11), and plugin latency adds to input-monitoring latency (host documentation, researcher F9, F10; outside the corpus); PDC misalignment of a bounce applies to any non-zero latency (Izhaki App. A). Lower latency without the CPU cost: non-uniform partitioning, phase-13 scope 1 (13b). Phase-06b D1, 2026-11-07, decider; vetoable by Maisara.

**phase-13.md** [P06B-39]:
- "Assumptions in force", AQ10 latency line: "latency ≤ 512 samples at 48 kHz" → "partition P ≤ 512 samples at
  48 kHz; reported latency P + 32 = 544 samples (11.3 ms) at the default P = 512 (phase-06b D1)".
- Item 9, replacement for the sentence that names P = 256:
  > Measure it on an Apple-silicon Mac with the `[benchmark]` test (it prints wall and thread-CPU p99.9 per case); if it misses, the remedy is non-uniform partitioning (new AX entry, 13b, per scope 1) or another scope 1 optimisation that leaves the output unchanged within −100 dB (e.g. SIMD in the accumulation loops), not P = 256 (it raises convolution work per sample 1.5–2.1×, run 42397114233, host 512) and not a change to the target.
- Scope 1 unchanged.

## D2 — AX31 confirmed, confidence high

Note appended to AX31:
> Confirmed by the phase-06b decision loop (D2, 2026-11-07; vetoable by Maisara): the alternatives would restore one state's block work in one callback on every swap, the spike the Phase 06 spreading fix was shipped to remove (Maisara 2026-11-07, "Spread only", which chose spreading over non-uniform partitioning, not among pickup variants). Table 15.1's 35 ms rows: source rotation / directivity does not apply in v1 (omni, AQ8); head rotation ('new HRTF') is deferred to phase-08 item 8 (AX3 yaw follows the emitter centroid), not out of scope; the extra partition decides that row only for rebuilds in (35 − 2P, 35 − P] = (13.7, 24.3] ms at P = 512, which includes W1 on the Linux runner (20.6 ms: 31.3 vs 41.9 ms), so phase 08 applies this row's reversal clause if the row applies. The 50 ms total delay is §15 text for interactive virtual environments with head tracking (out of scope).
[P06B-43, 45, advocate]

## D3 — AX32, confidence medium

> **AX32 — Bound on finite input samples (Phase 06b scope 3):** an input sample is taken into the convolver unchanged iff |x| ≤ **B = 2²⁰ (1 048 576, +120.4 dB re 1.0)**; otherwise (|x| > B, ±Inf, NaN) it is **replaced by 0**, in one comparison (`!(std::fabs(x) <= B)`, true for NaN) in the intake loop of `CrossfadingConvolver::process`, before the forward FFT; this replaces the Phase 06 NaN/Inf guard (same behaviour for non-finite samples; the existing non-finite test stays). **Guaranteed:** every FDL bin ≤ 2P·B ≤ 2³⁰ for any IR, so the FDL never holds a non-finite value. **Sufficient for finite output:** 2P·B·max_m Σ_n Σ|h_{n,m}| < FLT_MAX (3.40e38), i.e. Σ|h| per path < 1.58e29 at P = 512, N = 2 (largest over the 12 test scenes: 90.9; not a bound over all valid scenes; IrSet::create rejects only non-finite taps). **Not guaranteed:** that samples above B are preserved (they are discarded). **Test** (`[conv][engine]`, P = 128, 256, 512, seeded random host blocks, the 5 000-tap noise IR of the Phase 06 non-finite test, input σ 0.2 noise): (a) bursts of an isolated +1e38, an isolated −FLT_MAX and a same-sign run of 2P samples at +1e38 (overflows without the bound: 2P·1e38 > FLT_MAX) → every output sample finite, and −120 dB null (`residualDb`, the phase-06 AC 2 gate) against `renderOffline` of the input with exactly the |x| > B samples zeroed: shows the FDL is not poisoned (fails without the bound); (b) from output sample s_last + L + 4P on (no influence of a sample s at or after s + L + 3P; render length ≥ s_last + L + 4P + 4 096), −120 dB null against `renderOffline` of the burst-free original input: shows recovery, valid under any treatment; (c) single samples +B and −B are kept, single samples nextafter(+B, +∞) and nextafter(−B, −∞) are zeroed, each −120 dB against the matching reference (zeroing a kept ±B reads ≈ 0 dB, keeping a zeroed sample ≈ +87 dB, so both errors fail; says nothing about in-range accuracy, which (a) and the phase-06 nulls cover); (d) the phase-06 nulls at unchanged gates and zero allocations in `process` (AC 5). Rationale: float hosts pass values far above 1.0, up to "a million tracks at integer full scale" as the theoretical extreme (Izhaki Ch. 11; 10⁶ < 2²⁰), so B sits 80.4 dB above a +40 dB hot bus; no source gives a largest legitimate level (researcher F17–F20), so B is a product choice inside the window +40 dB … 1.83e33 (≈ 2^110.5, P06B-22, P06B-55), taken low for a large finiteness margin and a small emitted maximum (|y| ≤ 1.9e8 at Σ|h| = 90.9). Zero rather than clamp: float audio is trimmed at the float-to-integer conversion on the master (Izhaki Ch. 11), so a clamped +120 dB burst would be heard as full-scale output until its reverb falls 104 dB, ≈ 1.7 T (seconds in halls and churches, FR-3D-3; in headphones in binaural mode, FR-SIM-3), while zeroing leaves a gap; the zero treatment also keeps the precedent null valid (P06B-24). Decider 2026-11-07 (phase-06b D3; interrogator P06B-46…56; advocate PASS); vetoable by Maisara. Reversal: a documented legitimate level above 2²⁰. | 06b, 07 (host input), 13 |

Working for the finiteness bound [P06B-47]: per output m, each accumulated bin ≤ Σ_n Σ_k |X_n|·|H_{n,m,k}| with
|X_n| ≤ 2P·B and |H_{n,m,k}| ≤ Σ_partition|h|/2P → ≤ B·Σ_n Σ|h_{n,m}|; the unnormalised inverse sums 2P bins →
≤ 2P·B·Σ_n Σ|h_{n,m}|; P = 512, N = 2, per-path s: s < 3.4028e38/(1024·2²⁰·2) = 1.58e29.

## D4 — test rule, confidence high

> Summation-order test (phase-06b scope 6): `CrossfadingConvolver` 1 × 1 at P = 128, 256, 512, seeded random host blocks ≤ 512, input x ≡ 1.0, IR of K = T + 2 partitions with **T = 400** (partition 0 zero; partition 1 one tap 1.0; partitions 2 … K − 1 one tap 2⁻²⁵ each), render length ≥ (K + 4)·P; over the last P samples, **max |y − (1 + 400·2⁻²⁵)| ≤ 50 ulp(1) = 50·2⁻²³**. Every operation in this case is exact (power-of-two taps and IR scale 1/2P, DC-only input spectrum), so descending gives exactly 0 and ascending exactly T/4 = 100 ulp (M2(b); P06B-27, 29, 57); any threshold in [0, 100) separates them, and 50 ulp, the midpoint, is a free maximin margin (P06B-58). The measured error (expected 0 on SSE and NEON) is printed for the PR. No FMA margin (P06B-29). M2(a) is not a gate; it stays in `measurements.md` (the AC 2 −120 dB gate is unchanged). Mutation evidence: `kk = k` fails (100 ulp); a partial reorder with ≤ 200 tiny terms after the 1.0 would pass (P06B-59), which the criterion (ascending mutant) accepts. A non-zero descending error on any platform means the case is not exact there: report it and redesign the case, never re-threshold.

## For Maisara (plain)
- D1: keep 544 samples (11.3 ms): no change to the sound; the DAW compensates it on playback and bounce; halving it
  costs 1.5–2× CPU per instance on Mac and PC, and helps only when monitoring live through the plugin while
  recording. Veto if that is a v1 use.
- D2: keep AX31: a single move reaches the output ≈ 11 ms later, in exchange for no CPU spike on each IR switch;
  whether that matters once the head turns with the sources is checked in Phase 08.
- D3: samples above ≈ +120 dB over full scale (no music reaches it) are treated like broken samples and set to
  silence, rather than becoming seconds of full-scale noise in a hall or church.
- D4: the order test uses an exactly-known case; its pass line is halfway between right and wrong.
