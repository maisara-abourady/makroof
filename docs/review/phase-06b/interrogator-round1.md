# Phase 06b — interrogator, decision mode, round 1 (2026-11-07, corpus c1b171f)

Target: `decider-round1.md`. **All four SURVIVE WITH CORRECTIONS**; no load-bearing claim WRONG.

| decision | outcome | corrections |
|---|---|---|
| D1 keep P = 512, reword AQ10 | SURVIVES WITH CORRECTIONS | P06B-31, 32, 34, 35, 36; "phase-13 item 9 unchanged" INCONSISTENT (P06B-39, major: plan text, not choice (a)) |
| D2 confirm AX31 | SURVIVES WITH CORRECTIONS | P06B-43, 45 |
| D3 AX32 B = 2²⁰, zero | SURVIVES WITH CORRECTIONS | P06B-46, 47 (major), 50, 53, 54, 55 (major) |
| D4 50 ulp rule | SURVIVES WITH CORRECTIONS | P06B-58 (rationale only) |

| id | type | claim | verdict | evidence | severity |
|---|---|---|---|---|---|
| P06B-31 | FACT | "P does not change the output" | IMPRECISE: static-IR nulls; under an update s0 = (⌊r/P⌋+2)·P depends on P → "for a fixed IR, after latency compensation" | §0 row 06; AX31 | minor |
| P06B-32 | NUMBER | "CPU roughly doubles" | arithmetic CORRECT (crossfading 2.00/1.51/2.08; steady 2.12/1.67/2.13); say "1.5–2.1×" | run 42397114233 | minor |
| P06B-33 | NUMBER | 12 s / host 64 over budget at P 256, within at P 512 | NOT CHECKABLE; Linux runner only (P 256: Windows 64.2 %, macOS 48.9 %; P 512 macOS thread-CPU p99.9 109.9 %) | phase-06b item 1; §0 row 06 | minor |
| P06B-34 | FACT | latency matters mainly for input monitoring (Izhaki Ch. 11) | IMPRECISE citation: Ch. 11 supports automatic PDC and buffer latency "important in recording, less in mixdown"; plugin latency adding to monitoring is outside the corpus (dossier F9, F10) | Izhaki Ch. 11 | minor |
| P06B-35 | FACT | "compensate … on playback and bounce" | IMPRECISE: Izhaki Appendix A "Time range": PDC issues can put a bounced track out of sync (applies to 288 too) | Izhaki App. A | minor |
| P06B-36 | NUMBER | "12 s IR at host 64 over budget on Linux (103.2 % mean)" | IMPRECISE: "while crossfading" missing | phase-06b item 1 | minor |
| P06B-37 | NUMBER | 544 = 11.3 ms; CPU triples | CORRECT | – | none |
| P06B-38 | FACT | pre-roll in reported latency; AC 7 P + 32 | CORRECT | RealtimeEngine.h:45 | none |
| P06B-39 | FACT | "phase-13 scope 1 / item 9 unchanged" (item 9 remedy "P = 256") | INCONSISTENT with D1-L2/L3 (per-callback work at P 256 ≈ 2× P 512; Linux 103.2 % mean) | phase-13 item 9 | major |
| P06B-40 | DECISION | NFR-2 "latency when it buys accuracy" | CONSEQUENCE: the extra 256 samples buy CPU headroom, not accuracy (advocate) | PRD | minor |
| P06B-41 | FACT | 11.3 ms > Wessel & Wright 10 ms | NOT CHECKABLE (outside corpus) | – | none |
| P06B-42 | NUMBER | one partition 10.67 ms | CORRECT | – | none |
| P06B-43 | FACT | 49.8 + 30 ms ≪ 700 ms; "35 ms / 50 ms rows" | arithmetic CORRECT; IMPRECISE: two 35 ms rows (source rotation/directivity; head rotation/new HRTF); 50 ms is §15 text, not a row | Vorländer Table 15.1, §15 | minor |
| P06B-44 | NUMBER | 8 × 33 % ≈ 270 % | arithmetic CORRECT; premise NOT CHECKABLE (labelled derived) | – | none |
| P06B-45 | DECISION | "Spread only" settles AX31 | IMPRECISE: that question was non-uniform now vs spreading; it did not choose among pickup variants | 06-followups brief l.8 | minor |
| P06B-46 | NUMBER | 2²⁰, 120.41 dB, 2³⁰, 1.58e29, 1.9e8 | CORRECT; "needs" → "is sufficient" | arithmetic | minor |
| P06B-47 | NUMBER | AX32 "2P·N·B·max_m Σ_n Σ|h| < FLT_MAX, i.e. < 1.58e29" | INCONSISTENT: N counted twice; correct sufficient bound 2P·B·max_m Σ_n Σ|h_{n,m}| < FLT_MAX → 1.58e29 per path at P 512, N 2 | PartitionedConvolver.cpp:75–86; advanceLane/finishLane | major |
| P06B-48 | FACT | no working level reaches +120 dB | NOT CHECKABLE (product); 80.4 dB arithmetic CORRECT | Izhaki Ch. 11 | none |
| P06B-49 | FACT | bound before the forward FFT; `!(fabs(x) <= B)` true for NaN | CORRECT | code; IEEE | none |
| P06B-50 | FACT | clamped burst → seconds of hard clipping | CORRECT conditional; IMPRECISE: primary support Ch. 11 (trim at float-to-int on the master); +104 dB falls below 1.0 after ≈ 1.7 T: seconds only for T ≳ 0.6 s | Izhaki Ch. 11, 25; Kuttruff §3.8 | minor |
| P06B-51 | NUMBER | no influence at or after s + L + 3P; check from s_last + L + 4P | CORRECT | overlap-save; M1 | none |
| P06B-52 | FACT | test (a) | CORRECT; the unbounded mutant fails (a) | P06B-24 | none |
| P06B-53 | FACT | test (b) "(FDL not poisoned)" | IMPRECISE: (b) starts after any poison has cleared, so the unbounded mutant passes (b); (b) shows recovery, (a) carries "not poisoned" | P06B-51 | minor |
| P06B-54 | FACT | test (c) "alternative ≈ 0 dB" | IMPRECISE: zeroing a kept ±B ≈ 0 dB; keeping a zeroed sample ≈ +87 dB; both fail; negative side must be nextafter(−B, −∞) | arithmetic | minor |
| P06B-55 | NUMBER | "free product choice in [≈ 2²⁰, ≈ 2⁶⁴]" | INCONSISTENT with the AX32 window +40 dB … 1.83e33 ≈ 2^110.5 | P06B-22 | major |
| P06B-56 | FACT | "+120.4 dB re 1.0"; guards merged | CORRECT | Izhaki Ch. 11 | none |
| P06B-57 | NUMBER | D4 ascending 100 ulp, descending 0 | CORRECT | arithmetic; code l.207 | none |
| P06B-58 | FACT | "bit-exact would pin PFFFT rounding" | IMPRECISE: every operation in this case is exact, so 0 would not pin platform rounding; 50 ulp is a free maximin margin; any θ in [0, 100) separates | P06B-27/29 | minor |
| P06B-59 | NUMBER | partial reorder ≤ 200 terms passes | CORRECT | j/4 ulp | none |
| P06B-60 | SOFTWARE | D4 test setup | listed | – | – |

Questions: (1) P06B-47 which finiteness condition; (2) P06B-39 item 9 remedy given D1-L2/L3; (3) P06B-53/54;
(4) P06B-58 any operation differing SSE vs NEON in the exact case; (5) P06B-34/35 corpus support for
"bounce" and "mainly input monitoring".
