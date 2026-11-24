# 25: Builder, decider file 21 builder items: null wording, median print, 16-seed ensemble of (b)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

## Decider file 21 builder items: all three applied; the sealed seed passes, but (b) reds on 3 of 16 other seeds

I applied the three items to `tools/ci/ax49_l4.py` and `tools/ci/test_ax49_l4_kit.py` only, and committed nothing.
- The sealed build (tailSeed 12345) still passes every check, with SHA-256s identical to the previous build.
- In the seed ensemble, the asserted strongest-band form of (b) reds on **3 of the 16 seeds**.
- The ensemble median margin is +1.59 dB, so file 21's reversal condition (median margin < 0) does not fire.
- Nothing is asserted on the ensemble; the reference band of the assert is unchanged.

### 1. Null wording
`WORDING_NULL` is now exactly the decider's text, and the pinning test in `test_pinned_numbers` checks it verbatim.

### 2. Median print of (b)
A new field, `b_cut_window_vs_median`, is printed only, beside the asserted form. On the sealed build:
- **Asserted form (unchanged):** 63 −14.73, 125 0.00, 250 −5.65, 500 −6.57, 1k −5.91, 2k −17.71 dB relative to the strongest band. The weakest is 2 kHz, a **margin of 2.29 dB**.
- **Against the median of 63 Hz–1 kHz (print only):** 63 −8.82, 125 +5.91, 250 +0.27, 500 −0.66, 1k 0.00, 2k −11.80 dB. The weakest is 2 kHz, a **margin of 8.20 dB**.
- Coverage (a) is unchanged: margin 4.17 dB.

### 3. Ensemble
`python tools/ci/ax49_l4.py ensemble --out build/abx-07c-2b --seeds 16` renders the exact arm for tailSeeds 12346–12361.
- **What stays fixed:** the scene is otherwise S′, and the chord and gain come from the sealed manifest. The command checks that its chord input hashes to the sealed `chord_dry.wav`. It uses the same real-time path and the same 2^−1 pre-scale.
- **Output:** `build/abx-07c-2b/l4/ensemble.json`. It is print only, never asserted, and not a CI step.
- **Runtime:** 80.6 s.

In every seed the weakest band is 2 kHz, for both (a) and (b).

| tailSeed | (a) margin (dB) | (b) margin (dB) | (b) vs median (dB) |
|---|---|---|---|
| 12346 | 5.09 | 1.24 | 10.06 |
| 12347 | 7.22 | 2.04 | 3.79 |
| 12348 | 3.50 | 3.92 | 6.51 |
| 12349 | 5.40 | 1.61 | 5.18 |
| 12350 | 5.35 | 3.29 | 5.78 |
| 12351 | 5.93 | 1.01 | 2.74 |
| 12352 | 4.72 | 0.21 | 3.32 |
| 12353 | 4.97 | 1.60 | 4.35 |
| 12354 | 4.16 | **−0.95** | 7.89 |
| 12355 | 5.00 | 3.93 | 6.28 |
| 12356 | 5.28 | **−3.98** | 6.90 |
| 12357 | 4.96 | 1.58 | 4.40 |
| 12358 | 4.25 | 1.92 | 6.98 |
| 12359 | 5.86 | 1.21 | 8.61 |
| 12360 | 4.00 | 1.68 | 5.37 |
| 12361 | 4.09 | **−0.34** | 4.29 |

| Measure | min | median | max |
|---|---|---|---|
| (a) margin | 3.50 dB | 4.98 dB | 7.22 dB |
| (b) margin, asserted form | **−3.98 dB** | 1.59 dB | 3.93 dB |
| (b) margin, against the median | 2.74 dB | 5.57 dB | 10.06 dB |

- (a) and the median form of (b) hold on all 16 seeds.
- The strongest-band form of (b) would red on seeds 12354, 12356 and 12361. Its 2.29 dB margin on the sealed seed is close to the ensemble median of 1.59 dB.
- These figures are for the board's record; I changed nothing in response to them.

### Notes
- `build` replaces `<out>/l4`, so any rebuild deletes `ensemble.json`. Run the ensemble again after the final build if its output is to go into the pre-registration commit.
- **Sealed build rerun:** exit 0, every check passed, 28.8 s. All 8 SHA-256s match the previous build.
- **Pytest:** `SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci/test_ax49_l4_kit.py tools/ci/test_ax49_l4.py` gives **18 passed in 40.5 s**. `test_full_build` also checks that the median print is present and marked print only.

## Source of the "2.5 s Release" figure (interrogator file 23, Q5)

Orchestrator's local run, this session, 2026-11-24: `build/release/tests/unit/spatial_tests "[ax49-l4]" --durations yes`
on the session's Linux container (Release preset, `-DSPATIAL_BUILD_PLUGIN=OFF`, branch `claude/trusting-hypatia-j2rt6d`
at the commit that made `[ax49-l4]` non-hidden): "2.528 s: AX49 L4: the provisional unit decays are c_b times the
exact ones, faded by the raised cosine (S')", 216 assertions passed; wall time 3.97 s for the process. Not a CI
figure; the CI figure comes from the 'AX49 L4 gate (release)' step's `--durations` output on the first manual run.

## [ax49-l4] durations and peak RSS, local (decider file 21 §5, R5 condition; Seat 5 file 16 §6)

Session's Linux container, 2026-11-24, unit tests built without the plugin (`-DSPATIAL_BUILD_PLUGIN=OFF`), whole case
(all sections) per run, Catch2 `--durations yes`; peak RSS from `getrusage(RUSAGE_CHILDREN)`:
- Release: 2.53 s (budget 60 s).
- Debug: 15.87 s (budget 300 s); peak RSS 287 MB.
- ASan: 14.57 s for the whole case (Catch2 also printed 7.15 s for one section) (budget 300 s); peak RSS 643 MB; no sanitizer report.
All within half the 600 s ctest limit; the SECTION re-entry fix is not needed. CI's own figures come from the first
manual run's ctest and 'AX49 L4 gate (release)' logs.
