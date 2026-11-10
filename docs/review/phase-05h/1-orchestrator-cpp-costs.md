# Phase 05h, session 1: C++ costs for D-H1 (orchestrator measurement, O6)

Recorded, not decided. No W_max, n\*_max, realised-work ratio or margin is chosen here: D-H1 and the ratio's
pre-registration are board decisions (phase-05h §3, AX41), taken in session 2 from these numbers.

- **Source:** hidden Catch2 test `benchmark: phase 05h C++ costs for D-H1 …` (`tests/unit/test_diffuse_bench.cpp`,
  tags `[.][benchmark][diffuse-cost]`), run by the Release "Benchmark (release)" step of `ci.yml`.
- **Run:** all three OSes from run [42846229834](https://github.com/maisara-abourady/makroof/actions/runs/42846229834)
  (head f3e3603). Spread check: the earlier run [42841138286](https://github.com/maisara-abourady/makroof/actions/runs/42841138286)
  (head c309589; same `src/` and benchmark, only test assertions differ) gave on Windows restore worst 525.2 /
  1 954.9 / 2 023.7 ms and solve medians 115.4 / 71.1 / 70.8 ms (flutter / s 0.3 / s 1), against 574.3 / 2 003.5 /
  1 999.1 ms and 114.7 / 71.0 / 71.1 ms below: run-to-run spread of the worst restore up to 49 ms (9 %) on Windows.
- **Basis (provisional, AX41):** joint rule, block 64, n\*_max 1 024, W_scene = 6.10 M image evaluations
  (W_max 3.05 M per emitter), SE target 0.083 dB; estimator commit c309589.
- **Scenes:** prototype keys of `tools/validation/phase05b2_dt1.py` `_joint_cases()`: 100 × 100 × 100 m,
  listener (50, 30, 1.7), emitters (45, 70, 2) and (55, 70, 2); `cube100_flutter_fallback` (α 0.02 on the x
  faces, 0.95 elsewhere; s 0, 0, 0.05 × 4), `cube100_lowalpha0.05_s0.3`, `cube100_lowalpha0.05_s1` (the two
  candidates for the closed low-α cube, whose α and s D-H1 still pins). Restores at 96 kHz.

## 1. Determinism across platforms (AX39 D5, first evidence)

D5 face-sequence hashes, n\*, N_need, N_cap, N, W_pilot and W_final are **identical on Linux (gcc), macOS
(Apple clang, arm64) and Windows (MSVC)**, and identical to a local gcc build:

| scene | hash | n\* | N_need | N_cap | N | W_pilot | W_final |
|---|---|---|---|---|---|---|---|
| cube100_flutter_fallback | 0x6cfba7181536751b | 320 | 1 | 256 | 256 | 3 154 338 | 2 547 436 |
| cube100_lowalpha0.05_s0.3 | 0x7d5ca4b6b120c09e | 1 024 | 3 574 | 2 624 | 2 624 | 1 696 086 | 4 348 889 |
| cube100_lowalpha0.05_s1 | 0xf4e59aa02150725e | 1 024 | 58 612 | 2 688 | 2 688 | 1 666 253 | 4 347 497 |
| W1 (AQ10 room) | 0x5cfeac895afc2053 | 1 024 | 515 | 15 744 | 1 024 | 371 272 | 370 767 |

The smoke agreement (O5) prints the same summary on all three: max \|C++ − ref\| 0.0247 dB, max \|z\| 1.77, max SE
0.0244 dB.

## 2. Flags and precision at the gated scenes (pre-registration input, AX41)

| scene | fallback (e0, e1) | cap hit | floor truncated | pilot floor | pilot shipped | realised / W_scene | achieved SE e0 / e1 (dB, max band) | VOV_union e0 / e1 | U e0 / e1 |
|---|---|---|---|---|---|---|---|---|---|
| flutter fallback | 1, 1 | 0 | 1 | 1 | 0 | 0.9347 | 0.002 / 0.001 | 0.152 / 0.238 | 0 / 0 |
| low-α 0.05, s 0.3 | 0, 0 | 1 | 0 | 0 | 0 | 0.9910 | 0.092 / 0.075 | 0.084 / 0.122 | 0 / 0 |
| low-α 0.05, s 1 | 0, 0 | 1 | 0 | 0 | 0 | 0.9859 | 0.360 / 0.359 | 0.126 / 0.154 | 1 / 1 |
| W1 | 0, 0 | 0 | 0 | 0 | 0 | 0.1216 | 0.082 / 0.063 | 0.025 / 0.019 | 0 / 0 |

- Realised work / W_scene ≤ 0.991 at every gated scene (prototype C16: ≤ 1.009). The pilot's speculative blocks past
  the stop (one pool's worth) are computed and discarded; they cost time, not work in this count.
- At s = 1 the achieved SE (0.36 dB) is above Seat 1's 0.33 dB floor, so the floor is **not met** at
  `cube100_lowalpha0.05_s1` under the provisional W_max unless clause (d)'s replicates pass; with s = 0.3 it is met
  (SE ≤ 0.092 dB). This matches the expectation in phase-05h §3 ("at s = 1 … the starting-state clause would fire
  once"); prototype C14/C16: 0.44–0.50 dB, the C++ joint rule gives 0.36 dB.
- AX16 − switched E_target at 1 kHz: +0.03 / +0.03 dB (flutter), +0.07 / +0.17 dB (s 0.3), +0.03 / +0.26 dB (s 1),
  +0.15 / +0.26 dB (W1).

## 3. Cost per image evaluation and solve time

| OS (pool) | scene | solve min / median / max (ms), 10 runs | ns / evaluation at pool size | one thread (ms; ns / evaluation) |
|---|---|---|---|---|
| Linux (4) | flutter | 160.1 / 161.5 / 171.1 | 28.3 | 321.7; 56.4 |
| Linux (4) | low-α s 0.3 | 98.5 / 98.9 / 99.6 | 16.4 | 268.0; 44.3 |
| Linux (4) | low-α s 1 | 98.0 / 98.5 / 100.1 | 16.4 | 268.7; 44.7 |
| macOS (3) | flutter | 78.5 / 95.9 / 116.0 | 16.8 | 163.9; 28.7 |
| macOS (3) | low-α s 0.3 | 51.5 / 57.7 / 67.4 | 9.6 | 134.5; 22.3 |
| macOS (3) | low-α s 1 | 75.9 / 82.6 / 88.3 | 13.7 | 155.6; 25.9 |
| Windows (4) | flutter | 113.9 / 114.7 / 116.1 | 20.1 | 218.7; 38.4 |
| Windows (4) | low-α s 0.3 | 70.7 / 71.0 / 71.5 | 11.7 | 185.3; 30.7 |
| Windows (4) | low-α s 1 | 70.8 / 71.1 / 72.2 | 11.8 | 189.2; 31.5 |

**W1 diffuse share** (two emitters, n\*_max 1 024, median of 10): Linux 7.65 ms, macOS 9.03 ms (max 13.98),
Windows 6.35 ms, against AX41's ≤ 25 ms. On this evidence n\*_max is not pushed below 1 000 by the W1 share
(re-derivation is session 2's, AX41).

## 4. Synchronous restore today (no diffuse solve yet), 96 kHz, 10 runs

Through the JUCE-free `ScenePipeline` (`beginRestore` + `restore`, prepared realtime), alternating with an untimed
restore of the default scene so every timed restore builds. After the switch, t_restore ≈ this + the solve above.

| OS | scene | restore min / median / **worst** (ms) | worst + median solve (ms) | 14 × that (s), watchdog 30 s |
|---|---|---|---|---|
| Linux | flutter | 581.2 / 590.6 / **594.6** | 756.1 | 10.59 |
| Linux | low-α s 0.3 | 1 969.4 / 2 032.5 / **2 063.0** | 2 161.9 | **30.27** |
| Linux | low-α s 1 | 1 933.4 / 1 983.7 / **2 074.5** | 2 173.0 | **30.42** |
| macOS | flutter | 351.7 / 401.3 / **446.5** | 542.4 | 7.59 |
| macOS | low-α s 0.3 | 1 500.7 / 1 882.0 / **2 327.7** | 2 385.4 | **33.40** |
| macOS | low-α s 1 | 1 717.4 / 2 078.9 / **2 591.2** | 2 673.8 | **37.43** |
| Windows | flutter | 532.1 / 542.2 / **574.3** | 689.0 | 9.65 |
| Windows | low-α s 0.3 | 1 889.9 / 1 935.8 / **2 003.5** | 2 074.5 | 29.04 |
| Windows | low-α s 1 | 1 860.2 / 1 953.4 / **1 999.1** | 2 070.3 | 28.98 |

The Phase 07 full-rebuild record in the same runs (default materials, maximum room, best of 3, 96 kHz): Linux
2 028.2 ms, macOS 2 172.8 ms (BUILD_PLAN §0 row 07: 1.884 s best of 3).

## 5. Finding for D-H1 (not a decision)

- AX41's W_max basis under Q2a (A) is (30 s / 14 − worst OS build) / 2 per emitter, i.e. (2.143 s − build) for the
  whole diffuse solve. With the worst of 10 restores (D-H1's rule, not a best of 3), the **non-diffuse** restore of
  the closed low-α 100 m cube is 2.06–2.07 s on Linux (0.07–0.08 s left for the diffuse solve and the margin) and
  **2.33–2.59 s on macOS, already above 2.143 s with no diffuse solve at all.** The restore spread on macOS is
  wide (min 1.50 s, worst 2.59 s; shared runner).
- So the blocking restore gate (AX38 4c, AQ10 amended) would fail at that scene on macOS whatever W_max is, and on
  Linux at the provisional W_max (30.3–30.4 s). This is the case phase-05h §3 names: "any growth of the non-diffuse
  build" and a margin that would take far more than about 20 % of W_max (here more than 100 % on macOS).
- Per AX38 4c the remedy for a gate failure is bringing (C) (phase-07c) forward, never a time cap, a narrower room
  range or a formulation seam; a margin above about 20 % returns to the seats, whose options are a smaller W_max or
  (C) forward. Seat 1's floor at `cube100_lowalpha0.05_s1` is not met at the provisional W_max (SE 0.36 dB), so a
  smaller W_max there goes to Maisara (phase-05h §2 item 1) before any range change.
- Open for the board (session 2): pin the gated cube's α and s; define "any further rise"; decide D-H1 on these
  numbers; pre-register the realised-work ratio (measured here ≤ 0.991 at the gated scenes).
