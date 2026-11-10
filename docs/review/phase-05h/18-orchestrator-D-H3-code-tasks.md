# Orchestrator — D-H3 code tasks K-a3, K-a4, K-b3 (and K-c4's status)

Asked for in `16-decider-convene-D-H3.md` ("Orchestrator code tasks"). All numbers from the code: the hidden suite `[diffuse-agree-full]` re-run on the Release build (`build/release/tests/unit/spatial_tests`, Linux, same pre-registered N_test = 65 536, no reseed; log `agree_full.log`, 274 gated case-bands, 3 pooled CHECKs red as in file 9), and `render_cli --diagnostics` (48 kHz, W_max 3.05 M, n*_max 1 024) for K-b3. Scripts and the raw rows: `ka3_rows.json`, `ka3_pooled.json`, `kb3.json` in the session scratchpad (not committed; regenerable from the log and the fixtures).

## K-a3 — the pooled statistic per band under AX43 as written and under options (a), (b), (d), (e)

Definitions: z as written = (C++ − ref) / SE_C++; z_(a) = (C++ − ref) / √(SE² + ℓ_ref²) with ℓ_ref in dB = 10 log10(1 + ℓ_ref); (b) pools per reference class with z as written; (d) per class with z_(a); (e) pools per reference room (one cluster mean per room: each BRAS room's 10 pairs, each Phase 04 room's two emitters, each (A) case its own room) with z_(a) (also shown with z as written). Limit = 3/√M of the pooled set. **Bold** = fails.

| band | M | limit | mean z (as written) | mean z_(a) | mean dev dB | mean SE dB | mean ℓ_ref dB | (b) per class: mean z / limit | (d) per class: mean z_(a) / limit | (e) per room: M, mean z_(a) / mean z / limit |
|---|---|---|---|---|---|---|---|---|---|---|
| 0 | 23 | 0.626 | +0.160 | -0.120 | -0.0046 | 0.0097 | 0.0060 | absorbing -0.417 / 0.866 (M 12); reference +0.789 / 0.905 (M 11) | absorbing -0.375 / 0.866; reference +0.159 / 0.905 | M 19, -0.190 / -0.035 / 0.688 |
| 1 | 23 | 0.626 | +0.183 | -0.106 | -0.0046 | 0.0097 | 0.0059 | absorbing -0.417 / 0.866 (M 12); reference +0.839 / 0.905 (M 11) | absorbing -0.375 / 0.866; reference +0.187 / 0.905 | M 19, -0.182 / -0.021 / 0.688 |
| 2 | 23 | 0.626 | +0.216 | -0.076 | -0.0046 | 0.0097 | 0.0058 | absorbing -0.417 / 0.866 (M 12); reference **+0.906** / 0.905 (M 11) | absorbing -0.375 / 0.866; reference +0.250 / 0.905 | M 19, -0.164 / -0.001 / 0.688 |
| 3 | 53 | 0.412 | **+0.438** | +0.313 | +0.0009 | 0.0077 | 0.0052 | absorbing -0.417 / 0.866 (M 12); bras **+0.576** / 0.548 (M 30); reference **+0.998** / 0.905 (M 11) | absorbing -0.375 / 0.866; bras **+0.598** / 0.548; reference +0.286 / 0.905 | M 22, -0.051 / +0.101 / 0.640 |
| 4 | 53 | 0.412 | **+0.445** | +0.308 | +0.0008 | 0.0076 | 0.0052 | absorbing -0.417 / 0.866 (M 12); bras **+0.557** / 0.548 (M 30); reference **+1.077** / 0.905 (M 11) | absorbing -0.375 / 0.866; bras **+0.588** / 0.548; reference +0.290 / 0.905 | M 22, -0.051 / +0.118 / 0.640 |
| 5 | 53 | 0.412 | **+0.464** | +0.305 | +0.0008 | 0.0076 | 0.0051 | absorbing -0.417 / 0.866 (M 12); bras **+0.576** / 0.548 (M 30); reference **+1.123** / 0.905 (M 11) | absorbing -0.375 / 0.866; bras **+0.595** / 0.548; reference +0.257 / 0.905 | M 22, -0.059 / +0.132 / 0.640 |
| 6 | 23 | 0.626 | +0.344 | -0.069 | -0.0043 | 0.0096 | 0.0056 | absorbing -0.417 / 0.866 (M 12); reference **+1.175** / 0.905 (M 11) | absorbing -0.375 / 0.866; reference +0.265 / 0.905 | M 19, -0.159 / +0.077 / 0.688 |
| 7 | 23 | 0.626 | +0.355 | -0.067 | -0.0042 | 0.0096 | 0.0055 | absorbing -0.417 / 0.866 (M 12); reference **+1.198** / 0.905 (M 11) | absorbing -0.376 / 0.866; reference +0.270 / 0.905 | M 19, -0.158 / +0.083 / 0.688 |

Reading (orchestrator's arithmetic, for the decider and the interrogator to redo):

- **As written** fails only at bands 3–5 (M 53), as in file 9. **(a)** passes every band (bands 3–5: 0.31 against 0.412; the others ≤ 0.12 against 0.626). **(b)** fails: the BRAS class at bands 3–5 (0.56–0.58 against 0.548) and the reference-position class at bands 3–7 (1.00–1.20 against 0.905). **(d)** fails in the BRAS class at bands 3–5 (0.59–0.60 against 0.548; ℓ_ref barely moves the BRAS z because their SE is of the order of ℓ_ref), passes elsewhere. **(e)** passes every band in both forms (|mean| ≤ 0.19 against 0.64–0.69).
- File 11's and file 16's working assumed SE_C++ ≈ 0.035 dB per case-band. **That premise is wrong:** the mean SE over the 53 case-bands at 500 Hz–2 kHz is 0.0077 dB (range 0.0021–0.034 dB), the mean ℓ_ref 0.0052 dB. File 16's scaling estimates for (a) (≈ 0.91–0.985) therefore do not hold: for the small-SE cases ℓ_ref dominates the denominator and (a) scales their z by 3–4×.
- **K-a4 (reconciliation with AX46's class means):** the mean signed deviation at bands 3–5 is **+0.0009 dB (+0.02 %)**, not 0.015 dB; it agrees with AX46's class means (+0.03 / −0.23 / +0.11 %). The mean z of +0.44 is not a shared 0.015 dB deviation: the pooled mean of z weights each case-band by 1/SE, and three contributors with SE far below their reference's ℓ_ref carry it (table below). The per-case-band |C++ − ref| passes τ everywhere by ≥ 5× (max 0.046 dB).

### Contributors at 1 kHz (band 4), per reference room

| room (cluster) | class | n | mean C++ − ref dB | mean SE dB | mean z (as written) | mean ℓ_ref % (dB) | mean z_(a) |
|---|---|---|---|---|---|---|---|
| s_case_s0.1 | reference | 1 | +0.0014 | 0.0027 | +0.50 | 0.019 (0.0008) | +0.50 |
| s_case_s0.25 | reference | 1 | -0.0009 | 0.0069 | -0.13 | 0.054 (0.0023) | -0.12 |
| s_case_s0.4 | reference | 1 | -0.0040 | 0.0111 | -0.36 | 0.096 (0.0042) | -0.34 |
| t52_layout4_s0.1 | absorbing | 1 | +0.0049 | 0.0052 | +0.94 | 0.002 (0.0001) | +0.94 |
| t52_layout4_s0.25 | absorbing | 1 | +0.0130 | 0.0122 | +1.06 | 0.009 (0.0004) | +1.07 |
| t52_layout4_s0.4 | absorbing | 1 | +0.0084 | 0.0182 | +0.46 | 0.021 (0.0009) | +0.46 |
| t52_layout4_s1.0 | absorbing | 1 | -0.0208 | 0.0344 | -0.60 | 0.087 (0.0038) | -0.60 |
| t52_layout5_s0.1 | absorbing | 1 | -0.0024 | 0.0061 | -0.40 | 0.010 (0.0004) | -0.39 |
| t52_layout5_s0.25 | absorbing | 1 | -0.0090 | 0.0094 | -0.96 | 0.040 (0.0017) | -0.94 |
| t52_layout5_s0.4 | absorbing | 1 | -0.0142 | 0.0150 | -0.95 | 0.060 (0.0026) | -0.93 |
| t52_layout5_s1.0 | absorbing | 1 | -0.0460 | 0.0240 | -1.92 | 0.325 (0.0141) | -1.65 |
| t52_layout6_s0.1 | absorbing | 1 | +0.0018 | 0.0036 | +0.49 | 0.007 (0.0003) | +0.50 |
| t52_layout6_s0.25 | absorbing | 1 | -0.0033 | 0.0088 | -0.37 | 0.029 (0.0013) | -0.37 |
| t52_layout6_s0.4 | absorbing | 1 | -0.0074 | 0.0137 | -0.54 | 0.065 (0.0028) | -0.53 |
| t52_layout6_s1.0 | absorbing | 1 | -0.0436 | 0.0197 | -2.22 | 0.185 (0.0080) | -2.05 |
| dead_booth | reference | 2 | +0.0169 | 0.0021 | +8.07 | 0.173 (0.0075) | +2.16 |
| living_room | reference | 2 | -0.0032 | 0.0027 | -1.18 | 0.534 (0.0231) | -0.14 |
| classroom | reference | 2 | -0.0042 | 0.0039 | -1.10 | 0.155 (0.0067) | -0.55 |
| club | reference | 2 | +0.0009 | 0.0067 | +0.14 | 0.140 (0.0061) | +0.10 |
| cr2 | bras | 10 | -0.0001 | 0.0023 | -0.16 | 0.164 (0.0071) | +0.14 |
| cr3 | bras | 10 | +0.0045 | 0.0086 | +0.49 | 0.102 (0.0044) | +0.38 |
| cr4 | bras | 10 | +0.0099 | 0.0073 | +1.34 | 0.062 (0.0027) | +1.24 |

The three that carry the sign: `dead_booth` (two emitters: C++ − ref +0.017 dB = +0.39 % at SE 0.002 dB, z +8.1, against an ℓ_ref of 0.17 %: the C++ sits 2.3 ℓ_ref from a reference whose own last halving moved it 0.17 %), `cr4` (ten pairs, +0.010 dB, z +1.3, ℓ_ref 0.06 %) and `cr3` (+0.005 dB, z +0.5). The absorbing-face layouts pull the other way (−0.42 per class). Per case-band at bands 3–5 the largest |z| as written are dead_booth (8.0–8.2), t52_layout6_s1.0 (−2.2), t52_layout5_s1.0 (−1.9) and the cr4 pairs (≤ +2.4). The full 274-row table is in `agree_full.log` (scratchpad) and is reproduced by the hidden suite on every CI Release run.

## K-b3 — U and the flags at moved placements of the two fixtures (48 kHz, W_max 3.05 M, n*_max 1 024)

Every placement raises U on both emitters; the cause is the cap at every one (edge_values additionally the pilot floor and the floor truncation; the pilot ships only at the default). Moving the ends off the walls (both-near 0) does not silence U: the capped branch alone raises it (achieved SE > 0.33 dB everywhere). "Cannot be moved" is shown, not asserted.

| fixture | placement | emitter | n* | N | N_cap | N_need | cap | floor trunc. | pilot floor | pilot ships | achieved SE dB | VOV_union | both-near (d_L, d_E m) | U |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| edge_values | default | 0 | 64 | 0 | 0 | 147242 | 1 | 1 | 1 | 1 | 0.764 | 0.137 | 1 (0.1, 0.1) | 1 |
| edge_values | default | 1 | 64 | 0 | 0 | 147242 | 1 | 1 | 1 | 1 | 3.981 | 0.949 | 1 (0.1, 0.1) | 1 |
| edge_values | centre line: L (0.75,50,2) E0 (0.75,52,2) E1 (0.75,48,2) | 0 | 256 | 128 | 128 | 104068 | 1 | 1 | 1 | 0 | 0.926 | 0.484 | 0 (0.75, 0.75) | 1 |
| edge_values | centre line: L (0.75,50,2) E0 (0.75,52,2) E1 (0.75,48,2) | 1 | 256 | 128 | 128 | 104068 | 1 | 1 | 1 | 0 | 1.171 | 0.521 | 0 (0.75, 0.75) | 1 |
| edge_values | centre line, 0.3 m apart: L (0.75,50,2) E0 (0.75,50.3,2) E1 (0.75,49.7,2) | 0 | 256 | 128 | 128 | 29551 | 1 | 1 | 1 | 0 | 0.929 | 0.482 | 0 (0.75, 0.75) | 1 |
| edge_values | centre line, 0.3 m apart: L (0.75,50,2) E0 (0.75,50.3,2) E1 (0.75,49.7,2) | 1 | 256 | 128 | 128 | 29551 | 1 | 1 | 1 | 0 | 0.946 | 0.430 | 0 (0.75, 0.75) | 1 |
| edge_values | mid-room, wall side: L (0.3,50,1) E0 (1.2,55,3) E1 (0.3,45,1) | 0 | 192 | 128 | 128 | 483261 | 1 | 1 | 1 | 0 | 2.382 | 0.919 | 1 (0.3, 0.3) | 1 |
| edge_values | mid-room, wall side: L (0.3,50,1) E0 (1.2,55,3) E1 (0.3,45,1) | 1 | 192 | 128 | 128 | 483261 | 1 | 1 | 1 | 0 | 3.287 | 0.693 | 1 (0.3, 0.3) | 1 |
| open_field | default | 0 | 1024 | 2624 | 2624 | 1423887 | 1 | 0 | 0 | 0 | 2.390 | 0.468 | 0 (1.7, 3) | 1 |
| open_field | default | 1 | 1024 | 2624 | 2624 | 1423887 | 1 | 0 | 0 | 0 | 2.122 | 0.306 | 0 (1.7, 3) | 1 |
| open_field | listener 0.3 m above floor: L (50,40,0.3) | 0 | 1024 | 2560 | 2560 | 2356485 | 1 | 0 | 0 | 0 | 3.915 | 0.988 | 0 (0.3, 3) | 1 |
| open_field | listener 0.3 m above floor: L (50,40,0.3) | 1 | 1024 | 2560 | 2560 | 2356485 | 1 | 0 | 0 | 0 | 4.110 | 0.996 | 0 (0.3, 3) | 1 |
| open_field | listener 5 m above floor: L (50,40,5) | 0 | 1024 | 2752 | 2752 | 596546 | 1 | 0 | 0 | 0 | 1.959 | 0.377 | 0 (5, 3) | 1 |
| open_field | listener 5 m above floor: L (50,40,5) | 1 | 1024 | 2752 | 2752 | 596546 | 1 | 0 | 0 | 0 | 1.557 | 0.179 | 0 (5, 3) | 1 |
| open_field | all at 0.3 m: L (50,40,0.3) E (45|55,60,0.3) | 0 | 1024 | 2432 | 2432 | 2068876 | 1 | 0 | 0 | 0 | 2.858 | 0.527 | 1 (0.3, 0.3) | 1 |
| open_field | all at 0.3 m: L (50,40,0.3) E (45|55,60,0.3) | 1 | 1024 | 2432 | 2432 | 2068876 | 1 | 0 | 0 | 0 | 3.820 | 0.985 | 1 (0.3, 0.3) | 1 |

## K-c4 — the IR-path denormal probe on macOS and Windows

Not run here (Linux box). The hidden test `[.][probe-denormals-ir]` exists in `tests/unit/test_diffuse_gate.cpp`; it is added to the next manual CI run's Release step on the three OSes if D-H3 (c) chooses (b) or (d) (a one-line change in `.github/workflows/ci.yml`'s hidden-tag list, no golden). Status: pending the decision.

## Item (e) (T5T4-61) — no code task was asked; the facts are in file 12 and the ledger row.


## K-e6 — the worst `quiesce()` wait after a cancel at a random point of the 100 m / 96 kHz builder rebuild (item (e))

Hidden record `[.][benchmark][diffuse-quiesce]` added to `tests/unit/test_diffuse_records.cpp` (the AX38 (iv) "worst `quiesce()` latency" record brought forward; runs in the CI Release benchmark step on the three OSes from the next manual run). Method: one pipeline, prepared realtime at 96 kHz with the gated cube restored; `setParameter(kListenerX)` starts a builder rebuild; after a delay drawn uniformly over the uncancelled rebuild time the test calls `beginRestore()`, which is `quiesceBuilder()` alone (the abandon flag, the gate notify and the wait for the in-flight build), and times it. Linux Release, this box (4 cores), 10 runs per scene, seed fixed.

**Cancel points on the build path (from the code):** `BuildOptions::cancel` is passed only to the diffuse solve (`Engine.cpp` L324 `run.stop = options.cancel`), which checks it between 64-history blocks of the pilot and the final range (`DiffuseEstimator.cpp` L335, L497, L518, L552; AX39 D6) and throws `BuildCancelled` (`Engine.cpp` L326–327). The image-source planning before the solve, the unit-decay synthesis after it (`tail::BandNoiseGenerator` constructor and `make`, 95 % of the non-diffuse build at 100 m / 96 kHz, file 7) and the convolver's IR-set build check nothing. A cancel that lands before the solve waits until the solve's first block; one that lands after it waits for the whole remainder.

| scene (96 kHz) | builder rebuild, uncancelled | wait after cancel, 10 runs: min / median / worst |
|---|---|---|
| cube100_flutter_fallback | 1260 ms | 7 / 188 / **491 ms** |
| cube100_lowalpha0.05_s0.3 | 3645 ms | 74 / 461 / **2664 ms** |

Per run (cancel instant within the rebuild → wait):

| scene | run | cancel at ms | of ms | waited ms |
|---|---|---|---|---|
| cube100_flutter_fallback | 0 | 256 | 1260 | 286 |
| cube100_flutter_fallback | 1 | 283 | 1260 | 247 |
| cube100_flutter_fallback | 2 | 1130 | 1260 | 19 |
| cube100_flutter_fallback | 3 | 496 | 1260 | 96 |
| cube100_flutter_fallback | 4 | 361 | 1260 | 119 |
| cube100_flutter_fallback | 5 | 223 | 1260 | 280 |
| cube100_flutter_fallback | 6 | 347 | 1260 | 129 |
| cube100_flutter_fallback | 7 | 716 | 1260 | 491 |
| cube100_flutter_fallback | 8 | 511 | 1260 | 7 |
| cube100_flutter_fallback | 9 | 805 | 1260 | 346 |
| cube100_lowalpha0.05_s0.3 | 0 | 2825 | 3645 | 1070 |
| cube100_lowalpha0.05_s0.3 | 1 | 3597 | 3645 | 97 |
| cube100_lowalpha0.05_s0.3 | 2 | 3209 | 3645 | 832 |
| cube100_lowalpha0.05_s0.3 | 3 | 2316 | 3645 | 1277 |
| cube100_lowalpha0.05_s0.3 | 4 | 3503 | 3645 | 180 |
| cube100_lowalpha0.05_s0.3 | 5 | 1113 | 3645 | 82 |
| cube100_lowalpha0.05_s0.3 | 6 | 1010 | 3645 | 74 |
| cube100_lowalpha0.05_s0.3 | 7 | 416 | 3645 | 743 |
| cube100_lowalpha0.05_s0.3 | 8 | 3625 | 3645 | 110 |
| cube100_lowalpha0.05_s0.3 | 9 | 1340 | 3645 | 2664 |

Reading: the three regimes are visible. A cancel during the solve is observed within one block (74–97 ms, runs 5, 6 and 1 of the low-α cube; 7–19 ms at the flutter scene whose solve is longer and whose synthesis is shorter). A cancel before the solve waits for the image-source planning to reach it (run 7: 416 → 743 ms). A cancel after the solve waits for the remainder of the synthesis and the IR-set build with no cancel point: up to **2 664 ms** at the low-α cube (run 9) and 491 ms at the flutter scene. So (e-c)'s wait is bounded by the build's remainder, not by the solve's block granularity: seconds, not tens of milliseconds, unless cancel points are added to the synthesis (a phase-07c change). The `reset()` path adds the synchronous `ResetStep3` build on top of this wait when the IR set is stale.


## K-c3 — a direct denormal detector on the IR path (item (c)); Seat 3's candidate scene is positive

Hidden probe `[.][probe-denormals-detector]` added to `tests/unit/test_diffuse_gate.cpp`: the FPU's sticky denormal-operand status flag (x86-64 MXCSR DE bit 1; AArch64 FPSR IDC bit 7) is cleared before and read after an unguarded `buildRoomIR` (`ftzGuard = false`) with the caller's FTZ off, then again with FTZ on; the IRs are compared bit for bit. This sees a denormal that arose and was flushed without changing an output bit, which the bit-difference probe cannot (file 16 K-c2). Probe set: the eight scenes of `[.][probe-denormals-ir]` plus Seat 3's candidate (file 17-seat3 (c): a dead_booth-sized room with α 0.01 at 63 Hz and 0.999 above, s 0.5, whose fast bands' exp(−rate·j) in `BandNoiseGenerator::make` reach the double subnormal range inside the 63 Hz band's long tail). Linux Release, x86-64, this box.

| fs | scene | flag, FTZ off | flag, FTZ on | IRs |
|---|---|---|---|---|
| 48000 | absorbentScene (dead_booth, alpha 0.98, s 1) | clear | clear | bit-identical |
| 48000 | dead_booth.json | clear | clear | bit-identical |
| 48000 | edge_values.json | clear | clear | bit-identical |
| 48000 | open_field.json | clear | clear | bit-identical |
| 48000 | medium_room.json | clear | clear | bit-identical |
| 48000 | dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3) | **SET** | clear | bit-identical |
| 48000 | dead_booth alpha 0.999 s 0.5 | clear | clear | bit-identical |
| 48000 | 100 m cube alpha 0.999 s 0.5 | clear | clear | bit-identical |
| 48000 | 100 m cube alpha 0.01 at 63/125 Hz, 0.999 above | clear | clear | bit-identical |
| 96000 | absorbentScene (dead_booth, alpha 0.98, s 1) | clear | clear | bit-identical |
| 96000 | dead_booth.json | clear | clear | bit-identical |
| 96000 | edge_values.json | clear | clear | bit-identical |
| 96000 | open_field.json | clear | clear | bit-identical |
| 96000 | medium_room.json | clear | clear | bit-identical |
| 96000 | dead_booth alpha 0.01 at 63 Hz, 0.999 above, s 0.5 (Seat 3) | **SET** | clear | bit-identical |
| 96000 | dead_booth alpha 0.999 s 0.5 | clear | clear | bit-identical |
| 96000 | 100 m cube alpha 0.999 s 0.5 | clear | clear | bit-identical |
| 96000 | 100 m cube alpha 0.01 at 63/125 Hz, 0.999 above | clear | clear | bit-identical |

Reading: **Seat 3's scene produces denormals without FTZ at 48 and 96 kHz** (the flag is set after the unguarded build and clear with FTZ on), and its IRs are bit-identical with FTZ off and on, as the build path's double sums and the final `toFloatNoDenormal` conversion predict (file 17-seat3). So AX37 (5.1) (i)'s clause "an absorbent room asserted to produce denormals without FTZ" is satisfiable literally: the `[pipeline]` FTZ test can build this scene, assert the flag set without the guard (where the platform exposes it) and assert bit-identity with the caller's FTZ off and on. None of the eight earlier probe scenes sets the flag at either rate. macOS (AArch64 FPSR IDC) and Windows (MSVC `_mm_getcsr`) are covered by the same probe in the next manual CI run (K-c4).


## K-a4 (ii) — the ladder's direction: sign(C++ − ref_1.25) against sign(ref_1.25 − ref_2.5) per case-band (Seat 2's and Seat 9's request)

From the committed golden (`ref_fine`, `ref_coarse` per case-band) and the agreement run of K-a3. step = 10 log10(ref_1.25 / ref_2.5) (the signed last halving change); dev = C++ − ref_1.25. If the reference is still converging monotonically, the next halving would move ref by about +step·(convergence ratio) and "same sign" means the C++ sits where the ladder is heading (residual explanation); "opposite" means the C++ sits behind the ladder (an estimator-bias candidate, or an oscillating ladder). ratio = dev / step.

| room (cluster) | class | case-bands | same sign | opposite | mean dev dB | mean step dB | mean ratio dev/step |
|---|---|---|---|---|---|---|---|
| s_case_s0.1 | reference | 8 | 0 | 8 | +0.0014 | -0.0008 | -1.72 |
| s_case_s0.25 | reference | 8 | 8 | 0 | -0.0009 | -0.0023 | +0.39 |
| s_case_s0.4 | reference | 8 | 8 | 0 | -0.0040 | -0.0041 | +0.97 |
| t52_layout4_s0.1 | absorbing | 8 | 0 | 8 | +0.0049 | -0.0001 | -63.99 |
| t52_layout4_s0.25 | absorbing | 8 | 0 | 8 | +0.0130 | -0.0004 | -32.00 |
| t52_layout4_s0.4 | absorbing | 8 | 0 | 8 | +0.0084 | -0.0009 | -8.91 |
| t52_layout4_s1.0 | absorbing | 8 | 8 | 0 | -0.0208 | -0.0038 | +5.48 |
| t52_layout5_s0.1 | absorbing | 8 | 0 | 8 | -0.0024 | +0.0004 | -5.71 |
| t52_layout5_s0.25 | absorbing | 8 | 8 | 0 | -0.0090 | -0.0017 | +5.28 |
| t52_layout5_s0.4 | absorbing | 8 | 8 | 0 | -0.0142 | -0.0026 | +5.47 |
| t52_layout5_s1.0 | absorbing | 8 | 0 | 8 | -0.0460 | +0.0141 | -3.26 |
| t52_layout6_s0.1 | absorbing | 8 | 0 | 8 | +0.0018 | -0.0003 | -6.34 |
| t52_layout6_s0.25 | absorbing | 8 | 8 | 0 | -0.0033 | -0.0013 | +2.60 |
| t52_layout6_s0.4 | absorbing | 8 | 8 | 0 | -0.0074 | -0.0028 | +2.62 |
| t52_layout6_s1.0 | absorbing | 8 | 0 | 8 | -0.0436 | +0.0080 | -5.45 |
| dead_booth | reference | 16 | 16 | 0 | +0.0163 | +0.0086 | +1.94 |
| living_room | reference | 16 | 16 | 0 | -0.0037 | -0.0232 | +0.16 |
| classroom | reference | 16 | 10 | 6 | -0.0037 | -0.0061 | +0.60 |
| club | reference | 16 | 8 | 8 | +0.0010 | +0.0063 | +0.17 |
| cr2 | bras | 30 | 24 | 6 | -0.0001 | -0.0046 | -0.12 |
| cr3 | bras | 30 | 18 | 12 | +0.0044 | +0.0035 | -9.05 |
| cr4 | bras | 30 | 27 | 3 | +0.0103 | +0.0029 | +15.27 |

All gated case-bands: 274; same sign 175; opposite 99.

Per case-band at 500 Hz–2 kHz for the three contributors and the two s = 1 layouts:

| case | band | dev dB | step dB | same | ratio |
|---|---|---|---|---|---|
| t52_layout5_s1.0 | 3 | -0.0460 | +0.0141 | no | -3.26 |
| t52_layout5_s1.0 | 4 | -0.0460 | +0.0141 | no | -3.26 |
| t52_layout5_s1.0 | 5 | -0.0460 | +0.0141 | no | -3.26 |
| t52_layout6_s1.0 | 3 | -0.0436 | +0.0080 | no | -5.44 |
| t52_layout6_s1.0 | 4 | -0.0436 | +0.0080 | no | -5.44 |
| t52_layout6_s1.0 | 5 | -0.0436 | +0.0080 | no | -5.44 |
| dead_booth_e0 | 3 | +0.0173 | +0.0073 | yes | +2.35 |
| dead_booth_e0 | 4 | +0.0178 | +0.0075 | yes | +2.37 |
| dead_booth_e0 | 5 | +0.0183 | +0.0084 | yes | +2.17 |
| dead_booth_e1 | 3 | +0.0156 | +0.0073 | yes | +2.12 |
| dead_booth_e1 | 4 | +0.0159 | +0.0075 | yes | +2.12 |
| dead_booth_e1 | 5 | +0.0160 | +0.0084 | yes | +1.90 |
| bras_cr3_ls1_mp1 | 3 | -0.0083 | +0.0022 | no | -3.84 |
| bras_cr3_ls1_mp1 | 4 | -0.0079 | +0.0023 | no | -3.37 |
| bras_cr3_ls1_mp1 | 5 | -0.0075 | +0.0024 | no | -3.15 |
| bras_cr3_ls1_mp2 | 3 | +0.0138 | +0.0159 | yes | +0.87 |
| bras_cr3_ls1_mp2 | 4 | +0.0136 | +0.0156 | yes | +0.87 |
| bras_cr3_ls1_mp2 | 5 | +0.0130 | +0.0150 | yes | +0.87 |
| bras_cr3_ls1_mp3 | 3 | +0.0146 | +0.0051 | yes | +2.89 |
| bras_cr3_ls1_mp3 | 4 | +0.0145 | +0.0054 | yes | +2.66 |
| bras_cr3_ls1_mp3 | 5 | +0.0143 | +0.0058 | yes | +2.47 |
| bras_cr3_ls1_mp4 | 3 | +0.0011 | +0.0018 | yes | +0.61 |
| bras_cr3_ls1_mp4 | 4 | +0.0010 | +0.0019 | yes | +0.53 |
| bras_cr3_ls1_mp4 | 5 | +0.0006 | +0.0018 | yes | +0.33 |
| bras_cr3_ls1_mp5 | 3 | -0.0014 | -0.0029 | yes | +0.49 |
| bras_cr3_ls1_mp5 | 4 | -0.0010 | -0.0022 | yes | +0.46 |
| bras_cr3_ls1_mp5 | 5 | -0.0006 | -0.0015 | yes | +0.41 |
| bras_cr3_ls2_mp1 | 3 | +0.0099 | -0.0003 | no | -29.00 |
| bras_cr3_ls2_mp1 | 4 | +0.0095 | -0.0001 | no | -71.00 |
| bras_cr3_ls2_mp1 | 5 | +0.0088 | -0.0000 | no | -180.17 |
| bras_cr3_ls2_mp2 | 3 | +0.0070 | +0.0073 | yes | +0.96 |
| bras_cr3_ls2_mp2 | 4 | +0.0070 | +0.0071 | yes | +0.99 |
| bras_cr3_ls2_mp2 | 5 | +0.0068 | +0.0067 | yes | +1.01 |
| bras_cr3_ls2_mp3 | 3 | +0.0041 | -0.0027 | no | -1.53 |
| bras_cr3_ls2_mp3 | 4 | +0.0041 | -0.0022 | no | -1.90 |
| bras_cr3_ls2_mp3 | 5 | +0.0039 | -0.0017 | no | -2.36 |
| bras_cr3_ls2_mp4 | 3 | -0.0026 | +0.0053 | no | -0.49 |
| bras_cr3_ls2_mp4 | 4 | -0.0026 | +0.0054 | no | -0.48 |
| bras_cr3_ls2_mp4 | 5 | -0.0028 | +0.0053 | no | -0.53 |
| bras_cr3_ls2_mp5 | 3 | +0.0064 | +0.0016 | yes | +4.06 |
| bras_cr3_ls2_mp5 | 4 | +0.0065 | +0.0020 | yes | +3.23 |
| bras_cr3_ls2_mp5 | 5 | +0.0063 | +0.0024 | yes | +2.60 |
| bras_cr4_ls1_mp1 | 3 | +0.0157 | +0.0051 | yes | +3.09 |
| bras_cr4_ls1_mp1 | 4 | +0.0149 | +0.0048 | yes | +3.10 |
| bras_cr4_ls1_mp1 | 5 | +0.0138 | +0.0045 | yes | +3.10 |
| bras_cr4_ls1_mp2 | 3 | +0.0048 | +0.0025 | yes | +1.90 |
| bras_cr4_ls1_mp2 | 4 | +0.0048 | +0.0023 | yes | +2.09 |
| bras_cr4_ls1_mp2 | 5 | +0.0052 | +0.0024 | yes | +2.13 |
| bras_cr4_ls1_mp3 | 3 | +0.0099 | +0.0020 | yes | +4.86 |
| bras_cr4_ls1_mp3 | 4 | +0.0092 | +0.0018 | yes | +5.20 |
| bras_cr4_ls1_mp3 | 5 | +0.0089 | +0.0018 | yes | +4.97 |
| bras_cr4_ls1_mp4 | 3 | +0.0151 | +0.0055 | yes | +2.77 |
| bras_cr4_ls1_mp4 | 4 | +0.0132 | +0.0049 | yes | +2.71 |
| bras_cr4_ls1_mp4 | 5 | +0.0138 | +0.0049 | yes | +2.81 |
| bras_cr4_ls1_mp5 | 3 | +0.0109 | +0.0023 | yes | +4.70 |
| bras_cr4_ls1_mp5 | 4 | +0.0086 | +0.0018 | yes | +4.77 |
| bras_cr4_ls1_mp5 | 5 | +0.0107 | +0.0022 | yes | +4.93 |
| bras_cr4_ls2_mp1 | 3 | +0.0166 | +0.0028 | yes | +5.95 |
| bras_cr4_ls2_mp1 | 4 | +0.0157 | +0.0026 | yes | +6.07 |
| bras_cr4_ls2_mp1 | 5 | +0.0154 | +0.0026 | yes | +5.85 |
| bras_cr4_ls2_mp2 | 3 | +0.0052 | +0.0061 | yes | +0.85 |
| bras_cr4_ls2_mp2 | 4 | +0.0055 | +0.0051 | yes | +1.08 |
| bras_cr4_ls2_mp2 | 5 | +0.0049 | +0.0053 | yes | +0.92 |
| bras_cr4_ls2_mp3 | 3 | -0.0001 | +0.0014 | no | -0.07 |
| bras_cr4_ls2_mp3 | 4 | -0.0004 | +0.0009 | no | -0.42 |
| bras_cr4_ls2_mp3 | 5 | -0.0001 | +0.0015 | no | -0.07 |
| bras_cr4_ls2_mp4 | 3 | +0.0137 | +0.0029 | yes | +4.78 |
| bras_cr4_ls2_mp4 | 4 | +0.0130 | +0.0027 | yes | +4.82 |
| bras_cr4_ls2_mp4 | 5 | +0.0126 | +0.0028 | yes | +4.52 |
| bras_cr4_ls2_mp5 | 3 | +0.0168 | +0.0004 | yes | +47.45 |
| bras_cr4_ls2_mp5 | 4 | +0.0148 | +0.0000 | yes | +296.49 |
| bras_cr4_ls2_mp5 | 5 | +0.0154 | +0.0006 | yes | +26.76 |

## K-a4 (iii) — the 0.625 m rung at the small rooms (Seat 9's and Seat 2's decisive test)

`hybrid_fast` references at 0.625 m for dead_booth, living_room and the D-T6 small room (classroom and club queued), computed with the same script as the committed references (`compute_refs.py`, lean solver; patches and seconds per case below). The signed ladder per band at 500 Hz–2 kHz, with the C++ deviation against the 1.25 m reference (the committed golden) and against the new 0.625 m one. ratio = (1.25 → 0.625 step) / (2.5 → 1.25 step): below 1 the ladder is converging, above 1 it is still accelerating and the last-halving change under-states the residual.

| case | band | ref 2.5 → 1.25 dB | ref 1.25 → 0.625 dB | ratio | C++ − ref_1.25 dB | C++ − ref_0.625 dB | SE dB |
|---|---|---|---|---|---|---|---|
| dead_booth_e0 | 3 | +0.0073 | +0.0116 | +1.58 | +0.0173 | +0.0057 | 0.0021 |
| dead_booth_e0 | 4 | +0.0075 | +0.0122 | +1.62 | +0.0178 | +0.0056 | 0.0021 |
| dead_booth_e0 | 5 | +0.0084 | +0.0126 | +1.50 | +0.0183 | +0.0057 | 0.0021 |
| dead_booth_e1 | 3 | +0.0073 | +0.0116 | +1.58 | +0.0156 | +0.0040 | 0.0021 |
| dead_booth_e1 | 4 | +0.0075 | +0.0122 | +1.62 | +0.0159 | +0.0037 | 0.0021 |
| dead_booth_e1 | 5 | +0.0084 | +0.0126 | +1.50 | +0.0160 | +0.0034 | 0.0021 |
| living_room_e0 | 3 | -0.0239 | -0.0039 | +0.16 | -0.0056 | -0.0017 | 0.0028 |
| living_room_e0 | 4 | -0.0232 | -0.0036 | +0.16 | -0.0048 | -0.0012 | 0.0027 |
| living_room_e0 | 5 | -0.0226 | -0.0034 | +0.15 | -0.0042 | -0.0008 | 0.0027 |
| living_room_e1 | 3 | -0.0239 | -0.0039 | +0.16 | -0.0025 | +0.0014 | 0.0027 |
| living_room_e1 | 4 | -0.0232 | -0.0036 | +0.16 | -0.0017 | +0.0019 | 0.0027 |
| living_room_e1 | 5 | -0.0226 | -0.0034 | +0.15 | -0.0011 | +0.0023 | 0.0027 |
| dt6_small_room_e0 | 3 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |
| dt6_small_room_e0 | 4 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |
| dt6_small_room_e0 | 5 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |
| dt6_small_room_e1 | 3 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |
| dt6_small_room_e1 | 4 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |
| dt6_small_room_e1 | 5 | -0.0039 | -0.0005 | +0.14 | not gated (no C++ run) | — | — |

| case | patches at 0.625 m | seconds |
|---|---|---|
| dead_booth_e0 | 96 | 26 |
| dead_booth_e1 | 96 | 26 |
| living_room_e0 | 262 | 59 |
| living_room_e1 | 262 | 45 |
| dt6_small_room_e0 | 112 | 41 |
| dt6_small_room_e1 | 112 | 20 |

Reading: **dead_booth's reference moves toward the C++ at the next halving, and by more than at the previous one** (ratio ≈ 1.5–1.6: +0.012 dB after +0.007 dB). Against the 0.625 m reference the C++ sits at +0.004 to +0.006 dB (+0.1 %), inside the 1.25 → 0.625 step, so the z ≈ 8 of K-a3 is the reference's discretisation residual, not an estimator bias: the residual explanation holds for dead_booth, in the direction Seats 2 and 9 named. A second finding for AX36: the 1.25 m rung is "certified" at dead_booth by the < 1 % per-halving rule (0.17 %), yet the ladder there is not in its asymptotic regime (the steps grow), so the per-halving criterion can pass a reference whose true residual is larger than its last change; at a 2.5 × 2.0 × 2.2 m room the 2.5 m rung is coarser than two of the three dimensions (Seat 9). living_room converges (ratio 0.16) and the C++ is within ±0.002 dB of the 0.625 m reference on both emitters. The D-T6 small room converges (ratio 0.14) and is not gated this session. classroom and club follow in the same file when their run completes.


## Note on the researcher's RQ-H3-1 corrections (file 17-researcher-RQ-H3-1, D1–D5) against K-a3

K-a3 and K-a4 above were computed with the **per-case-band** ℓ_ref stored in the committed golden (`l_ref_b` per row), not with the per-room worst values the packet quoted (D1/D2): mean per-pair ℓ_ref at 500 Hz–2 kHz in the BRAS rooms, from the golden: cr2 0.163 %; cr3 0.101 %; cr4 0.066 %. The option (a) means in the K-a3 table are therefore already the recomputation D5 asks for, with the measured per-case SE (0.002–0.034 dB) rather than the assumed 0.035 dB: (a) passes every band (0.31 against 0.412), which D5's arithmetic at SE 0.035 dB could not see. The sign ladder of K-a4 (ii) is per case-band (per pair): step = ref_1.25 − ref_2.5 per pair, so D3's finding (mixed signs within CR2) is in it (cr2: 24 same / 6 opposite; cr3 18 / 12; cr4 27 / 3), and D4's reading (an ℓ → 0 estimator reads on the side the ladder is heading, i.e. dev with the same sign as the step) is the "same sign" column: 175 of 274 case-bands, all 16 of dead_booth, which K-a4 (iii) then confirmed at the 0.625 m rung. What the researcher's F5–F8 add for the decider: ℓ_ref as stored is a last-halving change, neither a 1-σ nor a bound with a safety factor (F6: F_S = 3 with two rungs), and a shared reference error does not shrink with M (F8), so the statistic's reading of ℓ_ref is the decider's to state whichever grouping wins.


### K-c3, corrected detector (Seat 5's three corrections applied)

The probe now reads both sticky bits per architecture (x86-64: DE operand bit 1 and UE underflow bit 4; AArch64: IDC bit 7 and UFC bit 3), calibrates first with a known denormal operand and a known underflowing product (SKIPs if either is unseen), and runs the solve on a one-thread pool so every block executes on the instrumented thread. Linux x86-64 Release, re-run: calibration reads "operand"; Seat 3's scene reads **[operand+underflow]** without the guard and **[underflow]** with FTZ/DAZ on (the flushed results still raise UE, as Seat 5 predicted), IRs bit-identical, at 48 and 96 kHz; the eight other scenes read clear in both arms at both rates. The AArch64 form (IDC only under FZ = 1) is what the next manual CI run on macOS will show; the per-architecture assertion Seat 5 wrote out is the form the `[pipeline]` FTZ test takes if D-H3 (c) adopts it.
