# Phase 06b — decider, round 1 (2026-11-07, corpus c1b171f)

Inputs: decisions-request.md, measurements.md, interrogator-option-check.md (P06B-7..30),
researcher-dossier.md (F1–F20; D1, D3 NOT READY, gaps not fillable). All four proposed; none RESEARCH NEEDED.
Premises that are product judgement (not sourced fact) are labelled.

PRD digest: users = producers and DJs hearing their track in a designed space (PRD "Target users");
NFR-1 accuracy first ("heavy CPU/latency acceptable" when it buys accuracy, NFR-2: latency reported,
usable in a session); NFR-3 / FR-SIM-6 artifact-free movement; NFR-8 any valid scene; FR-3D-3 halls and
churches (long IRs to the 12 s cap valid); FR-SIM-7 several instances. PRD silent on the largest legitimate
host level and on whether input monitoring through the plugin is a v1 use.

## D1 — (a) keep P = 512, reword AQ10

Load-bearing claims:
- **D1-L1** P does not change the output: UPOLS nulls ≤ −129.8 dB at P = 128/256/512 (§0 row 06); M2(a)
  residuals −129 … −132.5 dB at all P.
- **D1-L2** CPU roughly doubles from P = 512 to 256: AQ10 case crossfading Linux 12.6/6.3 = 2.0, macOS
  6.5/4.3 = 1.5, Windows 5.4/2.6 = 2.1 (run 42397114233).
- **D1-L3** 12 s IR, host 64, crossfading: over budget at P = 256 on Linux (103.2 % mean), within at P = 512
  (p99.9 66.6 %); reachable by valid scenes (AX6: only the 12 s cap bounds the IR).
- **D1-L4 (product judgement)** v1 use is playback and mixing, where hosts compensate reported latency
  (Izhaki Ch. 11 PDC; F9, F10: hosts bypass compensation or the plugin for input-monitored tracks); input
  monitoring is not the primary use, so no monitoring threshold (unsourced, dossier) is needed for (a).
- **D1-L5** not a loosened gate: AQ10 is an unsourced default; its parenthesis names the partition size;
  AX1 already puts the pre-roll in the reported latency; phase-06 AC 7 asserts P + 32.
Strongest objection: 11.3 ms > Wessel & Wright's 10 ms (F1) — conditions differ (gesture instruments).
Breaks if live monitoring/performance through the plugin is declared a v1 use. Confidence medium.
Reversal: tracking/live use in v1; Phase 13 real-hardware P = 256 within budget at host 64 / 12 s; 13b.
Veto → (b): kDefaultPartitionSize = 256, CLI help, AQ10 CPU check at the shipped P = 256 (12.6 % ≤ 15 %),
phase-13 scope 1 adds P = 256 numbers, item 9 restated at P = 256, phase-06 ACs, benchmark, listening pack re-run.

Proposed AQ10 first sentence (rest unchanged):
> Convolution partition size **P ≤ 512 samples at 48 kHz** (default P = 512, `conv::kDefaultPartitionSize`);
> the **reported latency is P + the AX1 pre-roll (32 samples) = 544 samples (11.3 ms at 48 kHz) at the
> default**. P does not change the output (UPOLS nulls ≤ −129.8 dB at P = 128, 256, 512, §0 row 06); halving
> P roughly doubles convolution CPU (3 s IR, host 512, crossfading: Linux 6.3 → 12.6 %, macOS 4.3 → 6.5 %,
> Windows 2.6 → 5.4 %, run 42397114233) and puts the 12 s IR at host 64 over budget on the Linux runner
> (103.2 % mean). Hosts compensate reported plugin delay on playback and bounce; latency matters mainly for
> input monitoring (Izhaki Ch. 11). Lower latency without the CPU cost is a phase-13 scope 1 option
> (non-uniform partitioning, 13b). Phase-06b D1, 2026-11-07, decider; vetoable by Maisara.
Also: the phase-13 "Assumptions in force" line "latency ≤ 512 samples" updated to this wording; phase-13
scope 1 / item 9 unchanged.

## D2 — confirm AX31 unchanged

- **D2-L1** cost = one partition, 10.67 ms at P = 512 (P06B-12, code).
- **D2-L2** isolated update W2 Linux 28.5 + 2·10.67 = 49.8 ms + 30 ms fade ≪ Vorländer Table 15.1
  translational 700 ms; the 35 ms / 50 ms rows (head tracking / interactive VR) are out of v1 scope (PRD
  out of scope; AQ8).
- **D2-L3 (derived, not measured)** an alternative concentrates lane B's k ≥ 1 work in one callback: at
  host 64 / P 512 (8 callbacks per block), if lane B ≈ half of the measured 66.6 % p99.9, ≈ 8 × 33 % ≈ 270 %
  > 100 %; holds unless off by > 2.7×.
- **D2-L4 (settled product decision)** Maisara 2026-11-07 "Spread only, plan later"
  (`docs/sessions/2026-11-07-phase-06-followups.md`).
Append to the AX31 row: "Confirmed by the phase-06b decision loop (D2, 2026-11-07); vetoable by Maisara."
Confidence high. Reversal: a measured alternative < 100 % worst callback at host 64 / 12 s on 3 OSes, or an
Expert limit broken by rebuild + 2P but met by rebuild + P. Veto → replacement loop between the two
alternatives; CrossfadingConvolver, AC 3 (s0 = (⌊r/P⌋ + 1)·P) and the per-call tests change.

## D3 — new AX32

- **D3-L1 (arithmetic)** 2²⁰ = 1 048 576, 20·log10 = 120.41 dB; 2P·B ≤ 1024·2²⁰ = 2³⁰ ≪ FLT_MAX; output
  finiteness needs Σ|h| < 3.4028e38/(1024·2·2²⁰) = 1.58e29; emitted |y| ≤ 2²⁰·181.8 ≈ 1.9e8 at Σ|h| = 90.9.
- **D3-L2 (product judgement)** no working level reaches +120 dB re 1.0; the corpus shows "much larger"
  than 808 is fine (Izhaki Ch. 11) but gives no maximum (dossier). B = 2²⁰ is 80 dB above a +40 dB hot bus.
- **D3-L3** placed in the intake loop before computeBlock() (forward FFT), so the FDL never sees |x| > B
  or a non-finite value; depends on no finite-math-only flags (the NaN test would catch them).
- **D3-L4 (product judgement)** zero rather than clamp: one rule for samples that are not audio; one
  comparison `!(std::fabs(x) <= B)` (true for NaN), merging the guards; keeps the −120 dB precedent valid
  (P06B-24); a clamped garbage burst would emit up to ≈ 1.9e8 of reverb for the IR length (up to 12 s),
  trimmed at the master into seconds of hard clipping (Izhaki Ch. 25 "Digital clipping").
- **D3-L5 (derived)** a sample at s affects output only before s + L + 3P; checking from s_last + L + 4P
  on leaves ≥ P margin; M1: 2023 + 188 360 + 4·512 = 192 431 > last poisoned 190 975 (P 512); P 128 limit
  190 895 > 190 591.
Strongest objection: why not a larger B (2⁶⁴)? Free product choice in [≈ 2²⁰, ≈ 2⁶⁴]; the smaller keeps
the finiteness margin and the emitted maximum robust. Confidence medium. Reversal: a documented legitimate
level > 2²⁰, or a clamp convention. Veto of B → another B < 1.83e33 (constant and boundary values change);
veto of zero → clamp with a separate NaN check first, whole-render null dropped, checks (b)–(d) remain.

Proposed AX32:
> **AX32 — Bound on finite input samples (Phase 06b scope 3):** an input sample is taken into the convolver
> unchanged iff |x| ≤ **B = 2²⁰ (1 048 576, +120.4 dB re 1.0)**; otherwise (|x| > B, ±Inf, NaN) it is
> **replaced by 0**, in one comparison (`!(std::fabs(x) <= B)`) in the intake loop of
> `CrossfadingConvolver::process`, before the forward FFT; this replaces the Phase 06 NaN/Inf guard (same
> behaviour for non-finite samples). **Guaranteed:** every FDL bin ≤ 2P·B ≤ 2³⁰ for any IR, so the FDL never
> holds a non-finite value; the output is finite whenever 2P·N·B·max_m Σ_n Σ|h_{n,m}| < FLT_MAX, i.e. Σ|h|
> per path < 1.58e29 at P = 512, N = 2 (largest over the 12 test scenes: 90.9; not a bound over all valid
> scenes; IrSet::create rejects only non-finite taps). **Not guaranteed:** that samples above B are
> preserved (they are discarded). **Test** (`[conv][engine]`, P = 128, 256, 512, seeded random host blocks,
> the 5 000-tap noise IR of the Phase 06 non-finite test, input σ 0.2 noise): (a) bursts of an isolated
> +1e38, an isolated −FLT_MAX and a same-sign run of 2P samples at +1e38 (overflows without the bound:
> 2P·1e38 > FLT_MAX) → every output sample finite, and −120 dB null (`residualDb`, the phase-06 AC 2 gate)
> against `renderOffline` of the input with exactly the |x| > B samples zeroed; (b) from output sample
> s_last + L + 4P on (render length ≥ s_last + L + 4P + 4 096), −120 dB null against `renderOffline` of the
> burst-free original input (FDL not poisoned; valid under any treatment); (c) a single ±B sample is kept
> and a single ±nextafter(B, ∞) sample is zeroed, each −120 dB against the matching reference (the
> alternative would read ≈ 0 dB, so the check discriminates); (d) the phase-06 nulls at unchanged gates and
> zero allocations in `process` (AC 5). Mutation evidence: with the bound removed, (a) fails. Rationale:
> float hosts pass values far above 1.0 (Izhaki Ch. 11), so B sits 80 dB above a +40 dB hot bus; no source
> gives a largest legitimate level (researcher dossier, F17–F20), so B is a product choice inside the window
> +40 dB … 1.83e33 (P06B-22); zero rather than clamp keeps one rule for samples that are not audio, keeps
> the precedent null valid (P06B-24) and does not turn a garbage burst into seconds of full-scale reverb.
> Decider 2026-11-07 (phase-06b D3); vetoable by Maisara. Reversal: a documented legitimate level above
> 2²⁰. | Breaks: 06b, 07 (host input), 13 |
Follow-up (not decided): rejecting in IrSet::create an IR with Σ|h| per path ≥ FLT_MAX/(2P·N·B) would make
output finiteness unconditional.

## D4 — test rule (no AX row)

- **D4-L1** ascending error exactly T/4 = 100 ulp, descending exactly 0 (IEEE round-to-nearest; 1/2P a
  power of two), matching M2(b).
- **D4-L2 (rule)** midpoint θ = T/8 = 50 ulp: maximin threshold for two point values with unknown
  non-order rounding; bit-exact (0) would pin PFFFT's rounding on every SIMD path.
- **D4-L3** T = 400 measured at all three P.
Rule: `CrossfadingConvolver` 1 × 1, P = 128, 256, 512, seeded random host blocks ≤ 512, x ≡ 1.0, K = T + 2
partitions, **T = 400** (partition 0 zero; 1: one tap 1.0; 2 … K−1: one tap 2⁻²⁵), render ≥ (K + 4)·P; over the
last P samples **max |y − (1 + 400·2⁻²⁵)| ≤ 50 ulp(1) = 50·2⁻²³** (midpoint of 0 and 100 ulp); measured
error printed; no FMA margin (P06B-29); M2(a) not a gate (stays as evidence); mutation `kk = k` fails
(100 ulp). A non-zero descending error on a platform is reported; > 50 ulp → redesign, never re-threshold.
Goes into phase-06b scope 6 text, the test comment and the ledger. Strongest objection: a partial reorder
(≤ 200 tiny terms after 1.0) passes — the AC names the ascending mutant; catching every partial reorder
means bit-exactness. Confidence high. Reversal: macOS (NEON) CI result. Veto → bit-exact θ = 0.

## For Maisara (plain)
- D1: keep 544 samples (11.3 ms): no change to the sound, the DAW compensates it on playback and bounce;
  halving it doubles CPU and makes long church/hall rooms drop out on small buffers. Veto if you want to
  monitor live through the plugin while recording.
- D2: keep AX31: a single move reaches the output ≈ 11 ms later, in exchange for no CPU spikes ("Spread only").
- D3: samples above ≈ +120 dB over full scale (no music reaches it) are treated like broken samples (silence).
- D4: the order test uses an exactly-known case; its pass line is halfway between right and wrong order.
