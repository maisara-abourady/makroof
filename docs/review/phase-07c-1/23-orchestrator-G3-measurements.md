# 23 — Orchestrator: answers to interrogator file 22 Q1/Q2 (G3, AX47 (b) EDT clause)

2026-11-12, local Debug build of the branch (test "[ax47]", tests/unit/test_interim.cpp with the per-case print added).
Per EDT case: eps = 1 − E_prov/E_exact of the band-filtered whole IR (emitter 0); d = energy within ±5 ms of the band
peak / total (the direct fraction); EDT per the test's edtS (Schroeder from the onset, least squares 0 … −10 dB, ×6).

**Q1.** The 0.013 % figure was broadband (emitter 0 taps). Per band at 500 Hz / 1 kHz: eps 8e-6 … 1e-4 (CR3),
6e-4 … 1.4e-3 (layout 4, absorbing-floor cube), 5.5e-3 … 8.3e-3 (layout 5). The evaluated worst (1.81 %) is at
layout 5 or layout 4 seed 2 band 3; it is not a contradiction of Eq. 6.4 once per-band eps is used.

**Q2.** The 7 ill-conditioned cases: layout4_s1 (d = 0.833 … 0.900 in every layout-4 case) and the absorbing-floor cube
at 1 kHz (d = 0.27 … 0.33). In layout 4 the raw regression also returns physically meaningless EDTs (24 … 98 s for a
T60_max of 1.34 s) in most cases, ill-conditioned or not: the EDC steps to about −8 … −9 dB at the direct sound and the
0 … −10 dB least-squares line over a step plus a slow tail is degenerate. So in layout 4 the EDT estimator is outside its
domain (Kuttruff §8.4, r < r_c), not only ill-conditioned; in the absorbing-floor cube (d ≈ 0.3) the 1 kHz cases are near
the edge (5.1 %, 5.6 % conditioning).

Full per-case lines (scene, rate, seed, band, eps, d, EDT exact, EDT provisional, deviation):

```
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 1 band 3: eps 1.297e-03, direct fraction d 0.848, EDT exact 39997.22 ms, provisional 40546.13 ms (1.37 %)
07c1-records ax47(b) EDT layout4_s1 48000 Hz seed 1 band 3: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 6.1 %; EDT exact 39997.2 ms, provisional 40546.1 ms)
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 1 band 4: eps 7.910e-04, direct fraction d 0.890, EDT exact 97640.27 ms, provisional 98021.72 ms (0.39 %)
07c1-records ax47(b) EDT layout4_s1 48000 Hz seed 1 band 4: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 5.3 %; EDT exact 97640.3 ms, provisional 98021.7 ms)
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 2 band 3: eps 8.397e-04, direct fraction d 0.880, EDT exact 55383.63 ms, provisional 56383.31 ms (1.81 %)
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 2 band 4: eps 7.366e-04, direct fraction d 0.900, EDT exact 40.80 ms, provisional 36.09 ms (-11.54 %)
07c1-records ax47(b) EDT layout4_s1 48000 Hz seed 2 band 4: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 98.2 %; EDT exact 40.8 ms, provisional 36.1 ms)
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 3 band 3: eps 1.021e-03, direct fraction d 0.845, EDT exact 38417.83 ms, provisional 39021.50 ms (1.57 %)
07c1-records ax47(b) EDT case layout4_s1 48000 Hz seed 3 band 4: eps 9.048e-04, direct fraction d 0.885, EDT exact 93411.74 ms, provisional 93995.52 ms (0.62 %)
07c1-records ax47(b) EDT case layout4_s1 96000 Hz seed 1 band 3: eps 8.663e-04, direct fraction d 0.873, EDT exact 63538.24 ms, provisional 63423.87 ms (-0.18 %)
07c1-records ax47(b) EDT case layout4_s1 96000 Hz seed 1 band 4: eps 9.104e-04, direct fraction d 0.858, EDT exact 51144.91 ms, provisional 51929.86 ms (1.53 %)
07c1-records ax47(b) EDT case layout4_s1 96000 Hz seed 2 band 3: eps 1.385e-03, direct fraction d 0.833, EDT exact 24272.30 ms, provisional 25428.24 ms (4.76 %)
07c1-records ax47(b) EDT layout4_s1 96000 Hz seed 2 band 3: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 6.2 %; EDT exact 24272.3 ms, provisional 25428.2 ms)
07c1-records ax47(b) EDT case layout4_s1 96000 Hz seed 2 band 4: eps 9.128e-04, direct fraction d 0.879, EDT exact 76338.30 ms, provisional 77258.58 ms (1.21 %)
07c1-records ax47(b) EDT layout4_s1 96000 Hz seed 2 band 4: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 11.3 %; EDT exact 76338.3 ms, provisional 77258.6 ms)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 1 band 3: eps 6.757e-03, direct fraction d 0.195, EDT exact 4855.43 ms, provisional 4847.79 ms (-0.16 %)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 1 band 4: eps 6.531e-03, direct fraction d 0.256, EDT exact 4888.84 ms, provisional 4874.77 ms (-0.29 %)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 2 band 3: eps 8.267e-03, direct fraction d 0.222, EDT exact 4923.09 ms, provisional 4838.29 ms (-1.72 %)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 2 band 4: eps 5.544e-03, direct fraction d 0.274, EDT exact 5045.26 ms, provisional 5019.93 ms (-0.50 %)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 3 band 3: eps 7.474e-03, direct fraction d 0.191, EDT exact 4673.25 ms, provisional 4700.23 ms (0.58 %)
07c1-records ax47(b) EDT case layout5_s1 48000 Hz seed 3 band 4: eps 5.791e-03, direct fraction d 0.247, EDT exact 4713.49 ms, provisional 4703.11 ms (-0.22 %)
07c1-records ax47(b) EDT case layout5_s1 96000 Hz seed 1 band 3: eps 7.962e-03, direct fraction d 0.221, EDT exact 4643.82 ms, provisional 4721.27 ms (1.67 %)
07c1-records ax47(b) EDT case layout5_s1 96000 Hz seed 1 band 4: eps 5.698e-03, direct fraction d 0.207, EDT exact 4546.19 ms, provisional 4534.11 ms (-0.27 %)
07c1-records ax47(b) EDT case layout5_s1 96000 Hz seed 2 band 3: eps 8.001e-03, direct fraction d 0.183, EDT exact 4700.20 ms, provisional 4708.08 ms (0.17 %)
07c1-records ax47(b) EDT case layout5_s1 96000 Hz seed 2 band 4: eps 7.164e-03, direct fraction d 0.213, EDT exact 4935.97 ms, provisional 4964.66 ms (0.58 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 1 band 3: eps 9.913e-04, direct fraction d 0.296, EDT exact 3060.87 ms, provisional 3034.51 ms (-0.86 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 1 band 4: eps 8.252e-04, direct fraction d 0.329, EDT exact 1849.76 ms, provisional 1825.74 ms (-1.30 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 2 band 3: eps 1.042e-03, direct fraction d 0.300, EDT exact 2874.51 ms, provisional 2850.39 ms (-0.84 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 2 band 4: eps 6.248e-04, direct fraction d 0.331, EDT exact 1763.73 ms, provisional 1757.98 ms (-0.33 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 3 band 3: eps 1.064e-03, direct fraction d 0.296, EDT exact 3074.36 ms, provisional 3056.14 ms (-0.59 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 48000 Hz seed 3 band 4: eps 6.907e-04, direct fraction d 0.327, EDT exact 2119.61 ms, provisional 2072.14 ms (-2.24 %)
07c1-records ax47(b) EDT absorbing_floor_cube20 48000 Hz seed 3 band 4: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 5.6 %; EDT exact 2119.6 ms, provisional 2072.1 ms)
07c1-records ax47(b) EDT case absorbing_floor_cube20 96000 Hz seed 1 band 3: eps 9.428e-04, direct fraction d 0.296, EDT exact 2532.56 ms, provisional 2490.62 ms (-1.66 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 96000 Hz seed 1 band 4: eps 6.928e-04, direct fraction d 0.273, EDT exact 2024.91 ms, provisional 1953.34 ms (-3.53 %)
07c1-records ax47(b) EDT absorbing_floor_cube20 96000 Hz seed 1 band 4: not evaluated (ill-conditioned EDC: +-0.06 dB of total moves the exact EDT by 5.1 %; EDT exact 2024.9 ms, provisional 1953.3 ms)
07c1-records ax47(b) EDT case absorbing_floor_cube20 96000 Hz seed 2 band 3: eps 1.360e-03, direct fraction d 0.285, EDT exact 3303.70 ms, provisional 3283.74 ms (-0.60 %)
07c1-records ax47(b) EDT case absorbing_floor_cube20 96000 Hz seed 2 band 4: eps 8.063e-04, direct fraction d 0.270, EDT exact 2772.36 ms, provisional 2731.59 ms (-1.47 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 1 band 3: eps 1.281e-04, direct fraction d 0.276, EDT exact 1561.56 ms, provisional 1561.46 ms (-0.01 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 1 band 4: eps 9.949e-06, direct fraction d 0.379, EDT exact 1509.88 ms, provisional 1509.82 ms (-0.00 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 2 band 3: eps 1.306e-04, direct fraction d 0.313, EDT exact 1802.79 ms, provisional 1801.85 ms (-0.05 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 2 band 4: eps 8.347e-06, direct fraction d 0.359, EDT exact 1410.64 ms, provisional 1410.60 ms (-0.00 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 3 band 3: eps 1.275e-04, direct fraction d 0.288, EDT exact 1617.47 ms, provisional 1616.71 ms (-0.05 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 48000 Hz seed 3 band 4: eps 9.465e-06, direct fraction d 0.364, EDT exact 1331.64 ms, provisional 1331.59 ms (-0.00 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 96000 Hz seed 1 band 3: eps 1.276e-04, direct fraction d 0.302, EDT exact 1714.93 ms, provisional 1714.45 ms (-0.03 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 96000 Hz seed 1 band 4: eps 8.907e-06, direct fraction d 0.339, EDT exact 1263.92 ms, provisional 1263.87 ms (-0.00 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 96000 Hz seed 2 band 3: eps 1.338e-04, direct fraction d 0.262, EDT exact 1843.28 ms, provisional 1842.42 ms (-0.05 %)
07c1-records ax47(b) EDT case bras_cr3_ls1_mp2 96000 Hz seed 2 band 4: eps 9.717e-06, direct fraction d 0.361, EDT exact 1498.25 ms, provisional 1498.19 ms (-0.00 %)
07c1-records ax47(b) provisional vs exact on the A4 set: worst |step| tail window 0.072 dB, common window 0.015 dB, worst EDT deviation 1.81 % over 33 evaluated cases (7 ill-conditioned, printed) (bounds 1 dB, 1 dB, 5 %)
```
