# Phase 06b — interrogator option check (round 0, 2026-11-07, corpus c1b171f)

Input: `decisions-request.md`, `measurements.md` (before the P06B-15/16 corrections, now applied).

| id | type | claim | verdict | evidence | severity |
|---|---|---|---|---|---|
| P06B-7 | NUMBER | D1/D2 544 samples = 11.3 ms, 288 = 6.0 ms; one partition 10.7 ms (P 512) / 5.3 ms (P 256) at 48 kHz | CORRECT | 544/48000 = 11.33 ms; 288/48000 = 6.00; 512/48000 = 10.67; 256/48000 = 5.33; `RealtimeEngine.h` latencySamples() = P + kAlignPreRollSamples (AX1) | none |
| P06B-8 | NUMBER | D1 CPU at P = 256 vs 512 (run 42397114233) | NOT CHECKABLE (measurements) | P = 512 triple matches §0 row 06; P = 256 matched the CI logs per P06B-1 | none |
| P06B-9 | DECISION | D1(a) keep P = 512, reword AQ10 | PRODUCT MATTER. CONSEQUENCE: 11.3 ms reported latency | Izhaki Ch. 11 (buffer size): monitoring latency matters in recording, less in mixdown; no ms threshold in the corpus | minor |
| P06B-10 | DECISION | D1(b) default P = 256 | PRODUCT MATTER. CONSEQUENCE: 12 s IR, host 64, Linux mean 103.2 % while crossfading | outside AQ10's 3 s budget case but reachable under the 12 s cap; Vorländer §15.1.1: block length optimised against update rate and latency | minor |
| P06B-11 | FACT | D1 × D2 interplay | CONSEQUENCE (P06F-8 not reopened) | if Vorländer §15's 50 ms total applied, W1 Linux: AX31 at P 512: 20.6 + 2·10.67 + 11.33 = 53.2 ms; without the extra partition 42.5 ms; AX31 at P 256: 20.6 + 2·5.33 + 6.0 = 37.3 ms | minor |
| P06B-12 | FACT | D2 isolated update enters one partition later | CORRECT | computeBlock step 4 fadeStart_ = blockStart_ + P → s0 = (⌊r/P⌋ + 2)·P vs (⌊r/P⌋ + 1)·P | none |
| P06B-13 | NUMBER | D2 "host 64, 12 s IR: Linux p99.9 66.6 %, Windows 32.2 %" | IMPRECISE → applied in the request: P = 512 stated; macOS wall 657.4 % / thread-CPU 109.9 % added (phase-13 item 9) | §0 row 06 | minor |
| P06B-14 | DECISION | D2 confirm AX31, or catch-up / whole first block at pickup | PRODUCT MATTER; corpus shows none wrong | Table 15.1 translational row (700 ms) ≫ 10.7 ms; "one state's block work in one callback" correct by the code (lane B: M·N·(K−1) multiply-adds); no measured cost for the alternatives | minor |
| P06B-15 | FACT | D3/M1 "poison threshold 2P·A ≥ FLT_MAX" | IMPRECISE → applied: DC bin = min(R, 2P)·A for a same-sign run of R; 2P·B is the sufficient bound | M1 rows | minor |
| P06B-16 | FACT | M1 "non-finite for the IR length" from a 96 000-sample render | WRONG as evidence → applied: re-measured over 3 × IR length: 189 440 samples per channel (IR + run), finite after | measurements.md M1 "Duration" | major |
| P06B-17 | FACT | FLT_MAX 3.40e38; 2²⁰ ≈ 1.05e6 ≈ +120 dBFS; +24 / +40 dBFS | CORRECT (arithmetic; FLT_MAX outside the corpus) | (2 − 2⁻²³)·2¹²⁷ = 3.4028e38; 20·log10(2²⁰) = 120.4 dB; Izhaki Ch. 11 | none |
| P06B-18 | FACT | output bound |y| ≤ B·ΣΣ|h| | CORRECT for output; IMPRECISE as a finiteness criterion: inverse-FFT partial sums only bounded by 2P·B·ΣΣ|h| → safe form FLT_MAX/(2P·N·Σ|h|max) = 1.83e33 at P 512 (7.3e33 at P 128) | triangle inequality; `IrSet::create` scaling | minor |
| P06B-19 | FACT | "largest Σ|h| 90.9"; "output finiteness also needs bounded IR taps (scope 4)" | IMPRECISE → applied: 90.9 is a 12-scene maximum, not a bound; guarantee needs 2P·N·B·Σ|h| < FLT_MAX (Σ|h| < 1.6e29 at B = 2²⁰) | – | minor |
| P06B-20 | FACT | FDL entries bounded by 2P·B for any IR | CORRECT; PFFFT partial-sum part NOT CHECKABLE | |X_bin| ≤ Σ|x|; M1 run 1024 at 3e35, P 512: 3.07e38 finite | none |
| P06B-21 | FACT | isolated sample up to 1e38 does not overflow | CORRECT as a measurement (this IR), not a guarantee | max|y| 3.1e37 | none |
| P06B-22 | DECISION | D3 bound B: 2²⁰, FLT_MAX-derived, or +24/+40 dBFS | 2²⁰ and derived values ≤ 1.83e33: PRODUCT MATTER (valid); +24 dBFS CONDITIONS VIOLATED; +40 dBFS valid only at the edge | Izhaki Ch. 11 "What is in it for us?": float sums values "much larger" than 1.0 without clipping; no largest legitimate level in the corpus | major |
| P06B-23 | DECISION | D3 treatment: clamp to ±B, or zero | PRODUCT MATTER; neither wrong | Izhaki Ch. 25 "Digital clipping": most float systems trim over-limit signals to the highest value (clamp-like); zero matches the NaN/Inf guard | minor |
| P06B-24 | FACT | D3 test: −120 dB against the render of the treated input | CORRECT under zeroing; CONDITIONS VIOLATED under clamping (clamped burst dominates the reference energy: 64 samples at 2²⁰ vs 1 s σ 0.25 noise → 104 dB, gate would accept ≈ −16 dB in-range error); "after the IR length equals the clean render" valid under both | `residualDb` | major |
| P06B-25 | NUMBER | M2(a) gap 0.7–3.5 dB, ±0.35 dB seed | CORRECT arithmetic; values NOT CHECKABLE | – | none |
| P06B-26 | DECISION | D4 option (a) alone | CONDITIONS VIOLATED vs "pin the order rather than one platform's rounding" | SSE only; smallest gap 0.7–0.8 dB ≈ 2× seed spread; NEON unmeasured | major |
| P06B-27 | NUMBER | M2(b) 0 / 25 / 100 ulp, −110.5 / −98.5 dB | CORRECT | ulp(1) = 2⁻²³; 2⁻²⁵ < half ulp; T·2⁻²⁵ = T/4 ulp; DC-only FDL spectrum, power-of-two scale → exact products | none |
| P06B-28 | DECISION | D4 option (b): threshold in ulp on the exact case | CORRECT (pins the order independent of SIMD path); any threshold in [0, 25) ulp separates; rule is the decider's; NEON NOT CHECKABLE until CI | – | none |
| P06B-29 | FACT | D4 "margin for FMA / compiler differences" | WRONG (for FMA): a·b exact → fma = round(round(a·b) + c); only value-changing reassociation could change it, which is an order change the test should catch | IEEE arithmetic | major |
| P06B-30 | SOFTWARE | M3, scope 4 path, D2 threading | listed, not rated | – | – |

Questions: (1) P06B-16 → answered by the re-measurement. (2) P06B-24: under clamping, which energy
normalises the null? (3) P06B-22: largest legitimate level that must pass exactly (+40 dBFS or higher)?
(4) P06B-19: is the finiteness guarantee for simulator IRs only or any IR submitIrSet accepts? (5) P06B-28:
NEON result in CI.
