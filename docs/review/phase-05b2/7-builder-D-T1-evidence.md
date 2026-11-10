# D-T1 evidence (builder): candidate formulations measured on prototypes outside `src/sim`

2026-11-09. Orchestrator (builder) evidence for the D-T1 convening round, produced after D-T4 and D-T5 were convened and
**before** the D-T1 decision and before any `src/sim` code. Tool: `tools/validation/phase05b2_dt1.py` (numba, offline;
commands `agree`, `bench`, `dense`, `openfield`); data: `tools/validation/data/phase05b2_dt1.json`. Machine: the session
container (4 cores, 15 GB; prototypes single-threaded). Times are for scale; the C++ numbers belong to O15.

## 1. Candidates (phase-05b2 §3 D-T1 (a)–(f)) at a glance

| candidate | what it stores | memory: AQ10 / CR4 / 100 m (8 bands) | time per position-only rebuild | status |
|---|---|---|---|---|
| (a) dense kernel (`ref_hybrid` port) | K[k, l, τ], N²T | 0.47 (1.53 fallback) / 2.53 / 3 052–6 193 GB | W1 measured: kernel build 9.9 s (room part, cacheable), injection + gather 0.36 s, solve 5.4 s (numpy, 10 generations); peak RSS 1.17 GB | measured on W1 |
| (b) matrix-free | per-patch history N·T per band | 100 m: 40–81 MB per band and emitter | per generation N²·images·16 sample pairs: 4.6·10⁸ (AQ10) … 4·10¹² (100 m fallback) pair-image evaluations | arithmetic only |
| (c) shoebox structure (Toeplitz/Hankel over patch offsets) | offset kernels per face pair and parity | 0.17 (0.54) / 0.35 / 211–428 GB | FFT over patch offsets × time per generation; build ∝ offsets × images | arithmetic only |
| (d) adjoint (listener-side) | as (a)/(b), one backward solve per emitter | as (a)/(b) | as (a)/(b): the windows are per emitter, so it saves nothing over a forward solve | reasoning only |
| (e) transform domain | N×N complex per frequency | 100 m: 0.74 GB per frequency | exact needs ≈ T frequencies (as `ref_hybrid.solve`); an approximation with a few frequencies has no error bound yet | reasoning only |
| (f) seeded Monte Carlo with next-event estimation ("MC-NEE") | the listener's lattice images per face (≤ ~3 000), no patches | < 2 MB in every room measured | below (§3) | measured on all rooms |

Dense memory table (2.5 m patches, 1 ms bins, float32, 8 bands; `dense.memory_table`):

| room | patches | bins | kernel (GB) |
|---|---|---|---|
| AQ10 non-fallback | 352 | 118 | 0.47 |
| AQ10 fallback | 352 | 385 | 1.53 |
| CR4 | 714 | 155 | 2.53 |
| 100 m non-fallback | 9600 | 1035 | 3052.34 |
| 100 m fallback | 9600 | 2100 | 6193.15 |

## 2. What (f) computes (equivalence to the validated model)

Particles leave the emitter uniformly (4π/N each: unit intensity per steradian, AX2), are traced in the shoebox with air exp(−m_b R)
along the path, and lose (1 − α_b) at every hit. At **every** hit the diffuse emission s(1 − α_b) of the incident energy
(Kuttruff Eq. 4.24, §5.2 split) is gathered at the point listener directly and over every specular route, i.e. the listener's lattice
images with Π((1 − α)(1 − s))^hits and air (Eq. 4.29 with Joyce/Gilbert transport, Eq. 4.35): next-event estimation with
cos θ/(π r²), weighted by the matching window exactly as `matchTail` (Hann, Eyring referral, 10 ms normalisation). The particle then
continues diffusely (cosine-weighted) with probability s and specularly otherwise (broadband s, AQ3: unbiased with no weights).
This is the continuous (ℓ → 0) form of `ref_hybrid`'s patch model; it has no patch size, so its resolution parameter is the
path count N (standard error ∝ 1/√N). Specular entries stay exact (ISM).

## 3. Measurements

**Agreement with the reference hybrid** (15 (A) cases, 500 Hz–2 kHz, reference = session 1's hybrid E_target at ℓ = 1.25 m;
32000 paths, seed 0x5EED): largest |difference| **0.087 dB**, largest |difference|/SE **1.67** (no bias detected).
The difference contains the hybrid's own ℓ error (≤ 0.37 % per halving, AX36) and the MC standard error.

| case | t_mix,e (ms) | (f) − hybrid, worst band (dB) | SE at 32k paths (dB) | paths for SE 0.083 dB | ms per emitter at that N |
|---|---|---|---|---|---|
| s_case_s0.1 | 113.5 | -0.004 | 0.006 | 153 | 1 |
| s_case_s0.25 | 113.5 | -0.006 | 0.015 | 993 | 1 |
| s_case_s0.4 | 113.5 | -0.004 | 0.024 | 2640 | 4 |
| t52_layout4_s0.1 | 380.4 | +0.001 | 0.010 | 490 | 64 |
| t52_layout4_s0.25 | 380.4 | +0.004 | 0.024 | 2733 | 344 |
| t52_layout4_s0.4 | 380.4 | -0.004 | 0.036 | 6174 | 851 |
| t52_layout4_s1.0 | 380.4 | -0.027 | 0.069 | 21984 | 1539 |
| t52_layout5_s0.1 | 380.4 | -0.005 | 0.013 | 804 | 205 |
| t52_layout5_s0.25 | 113.5 | +0.002 | 0.021 | 2106 | 3 |
| t52_layout5_s0.4 | 113.5 | +0.009 | 0.034 | 5497 | 9 |
| t52_layout5_s1.0 | 380.4 | -0.087 | 0.052 | 12694 | 1373 |
| t52_layout6_s0.1 | 113.5 | -0.004 | 0.007 | 255 | 0 |
| t52_layout6_s0.25 | 113.5 | -0.006 | 0.018 | 1571 | 3 |
| t52_layout6_s0.4 | 113.5 | +0.001 | 0.029 | 4003 | 7 |
| t52_layout6_s1.0 | 380.4 | +0.025 | 0.038 | 6676 | 900 |

**Cost per emitter** (8 000 paths measured; paths and time for a standard error of 0.083 dB and 0.033 dB in the worst AQ9 band,
SE ∝ 1/√N; W1/W2 = AQ10 scenes of `test_hybrid_ir.cpp`; CR4 = its 10 BRAS pairs; cube100 = 100 m cube, α 0.10–0.22, s 0.3;
cube100_flutter = 100 m, hard x-walls, α 0.95 elsewhere, s 0.05: AX22 fallback, t_cap ≈ 2.1 s):

| scene | t_mix,e (ms) | fallback | listener images | ms at 8 000 paths | SE (dB) | paths / ms for SE 0.083 | paths / ms for SE 0.033 | image table (MB) | ΔL (AX16 vs (f)), 1 kHz (dB) |
|---|---|---|---|---|---|---|---|---|---|
| W1_e0 | 113.5 | no | 197 | 12.1 | 0.032 | 1223 / 1.8 | 7734 / 11.7 | 0.11 | +0.32 |
| W1_e1 | 113.5 | no | 197 | 12.0 | 0.038 | 1689 / 2.5 | 10682 / 16.0 | 0.11 | +0.27 |
| W2_e0 | 380.4 | yes | 2798 | 848.3 | 0.003 | 12 / 1.3 | 74 / 7.8 | 1.61 | +0.21 |
| W2_e1 | 380.4 | yes | 2798 | 863.4 | 0.003 | 12 / 1.3 | 76 / 8.2 | 1.61 | +0.21 |
| bras_cr4_ls1_mp1 | 122.2 | no | 243 | 17.5 | 0.036 | 1474 / 3.2 | 9323 / 20.3 | 0.14 | -0.69 |
| bras_cr4_ls1_mp2 | 130.7 | no | 293 | 23.7 | 0.035 | 1444 / 4.3 | 9132 / 27.1 | 0.17 | -0.33 |
| bras_cr4_ls1_mp3 | 136.1 | no | 321 | 23.5 | 0.034 | 1316 / 3.9 | 8322 / 24.4 | 0.18 | -0.28 |
| bras_cr4_ls1_mp4 | 125.6 | no | 253 | 26.4 | 0.030 | 1043 / 3.4 | 6592 / 21.8 | 0.15 | -0.55 |
| bras_cr4_ls1_mp5 | 129.4 | no | 279 | 25.0 | 0.029 | 993 / 3.1 | 6280 / 19.6 | 0.16 | -0.24 |
| bras_cr4_ls2_mp1 | 128.5 | no | 297 | 26.6 | 0.028 | 918 / 3.0 | 5803 / 19.3 | 0.17 | -0.36 |
| bras_cr4_ls2_mp2 | 124.6 | no | 231 | 35.3 | 0.052 | 3087 / 13.6 | 19528 / 86.1 | 0.13 | -0.37 |
| bras_cr4_ls2_mp3 | 129.1 | no | 291 | 30.6 | 0.024 | 653 / 2.5 | 4125 / 15.8 | 0.17 | -0.11 |
| bras_cr4_ls2_mp4 | 133.6 | no | 321 | 27.5 | 0.030 | 1062 / 3.6 | 6716 / 23.1 | 0.18 | -0.35 |
| bras_cr4_ls2_mp5 | 150.0 | no | 387 | 36.3 | 0.028 | 888 / 4.0 | 5616 / 25.5 | 0.22 | +0.08 |
| cube100_e0 | 1117.5 | no | 577 | 105.3 | 0.097 | 10961 / 144.3 | 69339 / 913.1 | 0.33 | +0.09 |
| cube100_e1 | 1117.5 | no | 577 | 100.8 | 0.112 | 14522 / 182.9 | 91864 / 1157.0 | 0.33 | -0.06 |
| cube100_flutter_e0 | 2097.8 | yes | 2639 | 738.8 | 0.001 | 2 / 0.2 | 9 / 0.8 | 1.52 | +0.03 |
| cube100_flutter_e1 | 2097.8 | yes | 2639 | 714.8 | 0.000 | 1 / 0.1 | 2 / 0.2 | 1.52 | +0.03 |

**Cross-check on an exact reference** (C1, `open_field`): (f) equals the exact single-scatter floor integral within its standard error
(1.242·10⁻²⁰ vs 1.240·10⁻²⁰ at 1 kHz).

## 4. Properties the decision must weigh (builder's reading; for the seats to rate)

- **Scaling.** (f)'s cost per path is (hits before t_mix,e) × (listener images within the remaining time). By the mixing-time rule
  and AX22 the image count within t_mix,e is bounded (hundreds without the fallback, ≈ N_cap … 3 000 with it), so cost does not grow with
  room size the way N² does. Memory is the image tables only.
- **Precision is a choice.** SE ∝ 1/√N; a target SE gives N per scene. A fixed N (simple, smooth under automation) or an N chosen to meet a
  target SE (cost adapts: W2 needs ~12 paths, layout 4 at s = 1 ~22 000) are both deterministic.
- **Worst case.** Kuttruff Table 5.2 layout 4 at s = 1 (an α = 1 floor, every wall Lambert, AX22 fallback): ≈ 1.5 s per emitter at SE 0.083 dB
  single-threaded. Typical rooms: ≤ ~30 ms.
- **Determinism (AX5).** A counter-based RNG keyed by (seed, emitter, path) gives bit-identical results run to run. The seed choice
  (fixed constant vs `tailSeed`) decides whether E_target varies across `tailSeed` ensembles (AX11).
- **Continuity under automation (FR-SIM-6).** With fixed directions per path index, hit points move continuously with the source;
  a path whose hit face changes near an edge jumps (O(1/N) each). No patch boundaries (DN-1 (ii)'s room-size crossing concern does not arise).
- **Agreement test.** (f) is a different estimator of the same model (phase-05b2 §3 (f)): it must be validated against `ref_hybrid`
  with a tolerance that covers SE and the hybrid's ℓ error.
- **D-T2.** Under (f) the resolution parameter is N (or the SE target), not ℓ; R1 for CR4 at the reference's ℓ = 2.5 m is now certified
  (0.140 %), so `ref_hybrid` at 2.5 m is a valid agreement reference in all three BRAS rooms.
- **Dense (a) is feasible only in small rooms** and needs a resident 0.5–2.5 GB kernel there; (b), (c), (e) do not reach 100 m within any
  of D-T4's ceilings in time or memory on this arithmetic.
