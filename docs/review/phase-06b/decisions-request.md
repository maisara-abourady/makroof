# Phase 06b — open decisions (request to the decision loop)

Session brief: `docs/sessions/2026-11-07-phase-06b.md`. Phase file: `docs/phases/phase-06b.md`.
Measurements: `docs/review/phase-06b/measurements.md` (M1–M3). Corpus c1b171f.

Maisara, 2026-11-07, asked to choose D1 and D2 herself: "I have created an entire workflow described in
claude.md so you don't ask me these" / "Same answer". The loop decides; surviving decisions are recorded
as proposals she can veto.

## D1 — Latency reading (AQ10)

Facts: phase-06b.md "Raise with Maisara" item 1 (options, CPU at P = 256 and 512 from CI run 42397114233),
BUILD_PLAN §2 AQ10 ("Reported latency ≤ 512 samples at 48 kHz (convolution partition size)"), AX1
(32-sample pre-roll is part of the reported latency), AX31, §0 row 06, phase-13.md scope 1 and item 9
(measured at P = 512; non-uniform partitioning planned), phase-07.md "Raise with Maisara" item 1 (Phase 07
waits for this decision only).
- **(a)** keep P = 512; reword AQ10 so the partition size is the budgeted quantity and the reported
  latency is P + the AX1 pre-roll (544 samples, 11.3 ms at 48 kHz).
- **(b)** default P = 256; reported latency 288 samples (6.0 ms). CPU (mean % of budget, steady /
  crossfading, AQ10 case 3 s IR, host 512): Linux 7.0 / 12.6, macOS 3.5 / 6.5, Windows 3.2 / 5.4 (vs
  P = 512: 3.3 / 6.3, 2.1 / 4.3, 1.5 / 2.6). 12 s IR at P = 256 while crossfading: Linux host 64 mean
  103.2 % (over budget), Windows 64.2 %, macOS 48.9 %.
Product questions: who is the user (PRD), does 544 vs 288 samples matter to them (tracking, monitoring
while recording, mixing), what does the PRD rank higher, CPU headroom per instance (AQ10 15 %, multi-
instance in Phase 13), the 12 s case.

## D2 — AX31: confirm or replace

Facts: BUILD_PLAN §2 AX31 (and the alternatives it records), ledger P06F-1 (decider D1, interrogator
SURVIVES WITH CORRECTIONS, advocate PASS), AQ4, phase-06 AC 3. An isolated update reaches the output one
partition later (10.7 ms at P = 512, 5.3 ms at P = 256) in exchange for spreading the k ≥ 1 work over the
host callbacks (worst-callback cost at host 64, 12 s IR, P = 512, crossfading: Linux p99.9 66.6 %, Windows 32.2 %; macOS wall 657.4 % / thread-CPU 109.9 %, not provable on the shared runner, phase-13 item 9; no measured cost for the alternatives). Options:
**confirm** AX31; **replace** it with one of its recorded alternatives (catch-up at pickup, or computing
the whole first block at pickup).

## D3 — Bound on finite input samples (scope 3; new AX row)

Facts: M1 (a same-sign run of R samples at A overflows the forward FFT's DC bin once min(R, 2P)·A ≥ FLT_MAX =
3.40e38 and poisons the FDL for the IR length, measured 189 440 samples per channel; |x| ≤ B bounds every
FDL bin by 2P·B for any IR); the existing guard zeroes
NaN/±Inf (CrossfadingConvolver input guard, phase-06 non-finite test: −120 dB against the render of the
input with those samples zeroed); output growth |y| ≤ B·Σ_n Σ|h_{n,m}|, largest Σ|h| per path over the
12 test scenes 90.9 (not a bound over all valid scenes or IRs given to submitIrSet; output finiteness needs
2P·N·B·Σ|h| < FLT_MAX, i.e. Σ|h| < 1.6e29 at B = 2²⁰); FLT_MAX 3.40e38. Phase-06b risk: "A bound set too low would change in-range audio; the
phase-06 null tests at their unchanged gates are the guard." The AX row must fix:
1. **the bound B** (a magnitude on |x|; options to weigh, not limited to: a level far above any audio,
   e.g. 2²⁰ ≈ 1.05e6 ≈ +120 dBFS, or larger values derived from FLT_MAX / (2P·N·Σ|h|_max) with margin, or
   smaller ones such as +24/+40 dBFS);
2. **the treatment** of |x| > B (clamp to ±B, keeping the sign; or replace by 0 as for NaN/Inf);
3. **the test reference and tolerance** (precedent: −120 dB against the reference render of the input with
   the out-of-bound samples treated per 2; the output must also stay finite and the FDL unpoisoned: e.g.
   the output after the IR length has elapsed equals the clean render);
4. what is guaranteed and what is not (FDL entries bounded by 2P·B for any IR; output finiteness also needs
   bounded IR taps, scope 4).
Product questions: floating-point hosts pass samples above 0 dBFS legitimately; the plugin must not change
them; a hot bus at, say, +40 dBFS must convolve exactly; only pathological values are affected.

## D4 — Rule from measurement to the summation-order test's threshold (scope 6)

Facts: M2. (a) the realistic null against the double reference separates the orders by only 0.7–3.5 dB on
one platform, mixed with PFFFT rounding (SSE vs NEON); (b) the constructed exact-arithmetic case gives
descending 0 ulp, ascending 25 ulp (T = 100) / 100 ulp (T = 400), at P = 128, 256, 512. The test must fail
on the ascending mutant and pass on the descending order, and "pin the order rather than one platform's
rounding" (contractor review focus). Options to weigh: test on (a) with a threshold between the two
measured distributions (which rule: midpoint, a margin from the descending side, …); test on (b) with a
threshold in ulp (which rule: e.g. ≤ some fraction of the mutant's error, or bit-exact, or a stated
margin for FMA / compiler differences); or both.

## Interrogator option check (round 0, 2026-11-07): ledger P06B-7 … P06B-30

D1, D2: product matters (several valid). D3: product matter inside the window fixed by arithmetic
(lower edge: at least the largest level that must pass exactly, ≥ +40 dBFS by this request; upper edges
3.32e35 (FDL, P = 512) and 1.83e33 (output, Σ|h| ≤ 90.9)); +24 dBFS CONDITIONS VIOLATED; clamp vs zero
product matter; the −120 dB null against the treated-input render is valid under zeroing but not under
clamping (P06B-24: the clamped burst dominates the reference energy), while "output after the IR length
equals the clean render" is valid under both. D4: option family (b) verified (exact products, any
threshold in [0, 25) ulp separates; no FMA margin needed, P06B-29); (a) alone CONDITIONS VIOLATED;
the exact rule is the decider's.
