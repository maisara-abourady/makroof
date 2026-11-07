# Phase 06b measurements (session 1, 2026-11-07)

Local Linux x86-64, Debug preset (GCC, PFFFT SSE), branch `claude/charming-cannon-s1biw8` on top of
PR #14 head 67c5c4a. Made with a temporary, uncommitted Catch2 harness (hidden tests); the numbers are
inputs to the 06b decisions, not gates.

## M1 — Big finite input (scope 3)

`sim::RealtimeEngine` (2 × 2, 48 kHz, random host blocks ≤ 512), `medium_room.json` omni IR
(188 360 samples, Σ|h| per path 34.8–36.2, peak tap 0.155), seeded noise input (σ = 0.25) with samples
1000 … 1000 + run − 1 of both inputs set to +A. Output: 96 000 samples per channel; "non-finite" counts
NaN/Inf output samples over both channels.

| run (samples) | A | P = 128 | P = 512 |
|---|---|---|---|
| 1 | 1e32 … 1e38 | all finite (max |y| 3.1e37 at A = 1e38) | all finite |
| 64 | ≤ 3e36 | all finite | all finite |
| 64 | 1e37, 1e38 | **189 696 / 189 952 non-finite** (from output sample 1152 / 1024) | **188 928 / 189 952 non-finite** |
| 1024, 4096 | ≤ 3e35 | all finite (max |y| 8.9e36 at 3e35, run 4096) | all finite |
| 1024, 4096 | 1e36 | finite at P = 128 | **188 928 non-finite** |
| 1024, 4096 | ≥ 3e36 | **non-finite** | **non-finite** |

Reading: an isolated sample up to 1e38 does not overflow; a run of large samples does, once the
forward FFT's DC bin, Σ over 2P samples ≈ 2P·A, exceeds FLT_MAX = 3.40e38 (P = 512: 2P·A ≥ 3.4e38 at
A ≥ 3.3e35; observed: 3e35 finite, 1e36 not). Once poisoned, the FDL spectrum stays in the delay line
and the output is non-finite for the IR length (≈ 189 000 samples ≈ the 188 360-sample IR). The
re-review's claim (Minor 2) is confirmed for runs, not for isolated samples.

Analytic bounds (N = 2 inputs, P ≤ 512, so 2P ≤ 1024), with |x| ≤ B after the bound:
- forward FFT of [previous P | newest P]: every bin |X| ≤ Σ|x| ≤ 2P·B ≤ 1024·B (radix-2/4 partial
  sums are bounded the same way);
- output: |y_m| ≤ B · Σ_n Σ|h_{n,m}| (linear convolution);
- largest Σ|h| per path over the 12 valid test scenes at 44.1 and 96 kHz: **90.9** (living_room,
  96 kHz; small_room 88.9, stone_box 73.6); largest |h| 0.49.

## M2 — Summation order (scope 6)

### (a) Realistic case: null against the double-precision reference

`RealtimeEngine` 2 × 2, 48 kHz, random host blocks ≤ 2048, 1 s seeded noise, Phase 04 omni IR,
`residualDb` against `sim::renderOffline` (the AC 2 measure). Descending = the current code (late
partitions first); ascending = the mutant `kk = k`. Both outputs give the same value (the two output
channels of a seed agree to 0.01 dB).

| room | P | descending (dB) | ascending (dB) | gap (dB) |
|---|---|---|---|---|
| medium_room | 128 | −129.58 … −130.20 | −126.70 … −126.79 | 2.79 … 3.48 |
| medium_room | 256 | −131.22 … −131.92 | −128.96 … −129.31 | 2.15 … 2.61 |
| medium_room | 512 | −132.00 … −132.48 | −130.53 … −130.82 | 1.47 … 1.91 |
| concert_hall_box | 128 / 256 / 512 | −130.4 / −131.9 / −132.5 | −128.6 / −130.6 / −131.7 | 1.7 / 1.2–1.4 / 0.7–0.8 |
| large_hall | 128 / 256 / 512 | −129.1 / −130.8 / −131.9 | −127.3 / −129.3 / −130.8 | 1.8–1.9 / 1.5 / 1.0–1.1 |
| living_room | 128 / 256 / 512 | −130.2 / −131.6 / −132.5 | −127.1 / −129.3 / −131.1 | 3.0–3.2 / 2.3 / 1.3 |

(3 seeds each: 61, 161, 261.) The ascending mutant passes the whole `[conv]` suite (8 900 assertions,
34 test cases), as the re-review found. Gap at most 3.5 dB, seed-dependent by ±0.35 dB, measured on one
platform only; the residual mixes the order effect with PFFFT's own rounding, which differs between
SSE (Linux/Windows x86-64) and NEON (macOS arm64).

### (b) Constructed case: exact IEEE-754 arithmetic

`CrossfadingConvolver` 1 × 1, random host blocks ≤ 512, constant input x = 1.0. IR of K = T + 2
partitions: partition 0 zero; partition 1 one tap of 1.0; partitions 2 … K − 1 one tap each of
2⁻²⁵ (below half an ulp of 1.0, which is 2⁻²⁴). Steady-state output (last P samples) against the exact
value 1 + T·2⁻²⁵, in units of ulp(1) = 2⁻²³. Every product is exact (powers of two), so only the order of
the additions decides: summed late-first, the tiny terms add exactly before 1.0 is added; summed
early-first, each tiny term is rounded away against 1.0.

| P | T (tiny partitions) | expected − 1 | descending: max |error| | ascending: max |error| (relative) |
|---|---|---|---|---|
| 128, 256, 512 | 100 | 25 ulp | **0 ulp** (bit-exact) | **25 ulp** (−110.5 dB) |
| 128, 256, 512 | 400 | 100 ulp | **0 ulp** | **100 ulp** (−98.5 dB) |

## M3 — Fail fast after a crash (scope 5)

Probe: a hidden test aborts (SIGABRT) while a detached thread holds the stdout `FILE` lock (`flockfile`),
which Catch2's POSIX fatal-signal reporter needs. A heap-corruption probe (glibc "malloc(): invalid
size", single- and multi-threaded) did not reproduce the re-review's futex hang here (exit after 6 ms);
the stdout-lock probe reproduces it deterministically.

| Catch2 build | probe result | time |
|---|---|---|
| default (POSIX signal handler on) | hung; `timeout 20` killed it (rc 124); under ctest: `crash probe hung: no exit within 30 s`, Test #161 `***Failed 30.01 sec` | ≥ 20 s / 30.01 s |
| `CATCH_CONFIG_NO_POSIX_SIGNALS` | `Subprocess aborted` (rc 134); ctest Test #161 `Passed 0.06 sec`, probe `after 54 ms` | 0.057 s |

A visible test that calls `std::abort()` is reported by ctest by name:
`Test #68: crash probe plain abort ....Subprocess aborted***Exception: 0.00 sec`.
