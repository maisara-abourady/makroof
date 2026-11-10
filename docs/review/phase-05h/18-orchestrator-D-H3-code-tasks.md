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

