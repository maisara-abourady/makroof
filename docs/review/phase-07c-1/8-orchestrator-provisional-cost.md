# 8 — Orchestrator: measured provisional-tail cost (K15) and condition 10/12 local records (phase 07c-1)

2026-11-12, this session's container (Linux x86-64, 4 cores, Release build), code at the working tree on top of
da45b05 (uncommitted condition 10/11/12 work). Records, not CHECKs; the CI runs re-take them on three OSes.

## K15 — the unit-decay synthesis at a prefix L_p = 0.31 T60_max + 0.1 s (one emitter: constructor + make)

Test `records: provisional-tail synthesis cost …` (`tests/unit/test_noise_tail.cpp`, tag `[provisional-cost]`).
L_p = 0.31 T60 is the EDT-within-5 % bound for a truncated exponential (Seats 1, 3, 9; interrogator row 25), plus
a 0.1 s fade.

```
07c1-records provisional cost  48000 Hz, T60  2.0 s: full tail 3.00 s -> 132 ms; prefix L_p 0.72 s -> 18 ms
07c1-records provisional cost  48000 Hz, T60  8.0 s: full tail 12.00 s -> 774 ms; prefix L_p 2.58 s -> 121 ms
07c1-records provisional cost  48000 Hz, T60 12.0 s: full tail 12.00 s -> 747 ms; prefix L_p 3.82 s -> 129 ms
07c1-records provisional cost  96000 Hz, T60  2.0 s: full tail 3.00 s -> 320 ms; prefix L_p 0.72 s -> 47 ms
07c1-records provisional cost  96000 Hz, T60  8.0 s: full tail 12.00 s -> 1596 ms; prefix L_p 2.58 s -> 325 ms
07c1-records provisional cost  96000 Hz, T60 12.0 s: full tail 12.00 s -> 1629 ms; prefix L_p 3.82 s -> 334 ms
```

Per instance with two emitters (the plugin's case) the prefix cost is ≈ constructor + 2 × make, i.e. somewhat
under 2 × the figure above: at 96 kHz / T60 ≥ 8 s about 0.5–0.65 s [Inf from the one-emitter figure; the
constructor is shared]. On this box the full synthesis is ≈ 1.6 s per emitter at 96 kHz (the CI-runner figure in
AX38 4c is 3.14 s for both emitters).

## Condition 10 record (enter-offline cancel), 100 m low-α cube, Linux, this box

setNonRealtime(true) worst 1.34 ms (48 kHz) / 2.57 ms (96 kHz) against AX38 (i)'s 2 664 ms; cancelled build unwinds
in ≤ 84.6 / 188.4 ms; first offline block 1.27 / 3.34 s (it waits for the unwind, then builds); process RSS delta
≤ 182 / 395 MB.

## Condition 12 records (d), (f), 100 m low-α cube, Linux, this box

| fs | builds | all rebuilt | (f) process peak RSS delta | (d) worst quiesce wait |
|---|---|---|---|---|
| 48 kHz | 1 / 4 / 8 | 1 228 / 1 682 / 3 656 ms | 156 / 552 / 1 108 MB | 51 / 38 / 6 ms |
| 96 kHz | 1 / 4 / 8 | 3 064 / 3 909 / 8 287 ms | 311 / 1 147 / 2 250 MB | 154 / 153 / 296 ms |

(f) at 8 × 96 kHz exceeds AX38 (i)'s "1 GB transient per diffuse solve" figure as a PROCESS figure (it is the
concurrent ISM + synthesis of eight builds, now outside the gate): a finding for Phase 13's memory budget
(scope 1) per condition 12 (f), never an instance cap.

## TSan

Local TSan build (`cmake --preset tsan -DSPATIAL_BUILD_PLUGIN=OFF`): `[conv],[pipeline],[diffuse]` 79 test cases,
76 153 assertions, no ThreadSanitizer warning (includes the condition 10 tests, the condition 12 (a)/(e) tests
and the host-trace ring tests).
