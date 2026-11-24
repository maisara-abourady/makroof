# 4: Builder, K7-builder: s < 1 and wet candidates for the AX47 self-ABX, with the new checks

This file is computation only. It makes no decision. Nothing in `src/`, `tools/` or `tests/` was changed or tuned
(PRD NFR-8). It answers decider file 2, "RESEARCH NEEDED (builder K7)", with the additions of interrogator file 3,
"K7 spec: incomplete" (items 1–4, relayed by the coordinator).

**Naming.** This measurement is called **K7-builder** here. Decider file 2's inventory row K7 is a different thing (both_wall's far
emitter heard until N + 1407).
- Binary: `build/cli/render_cli` (`ninja -n render_cli`: no work to do) on this branch at 428c207. `src/` is unchanged
  since 90e4eda; `tools/ci/abx_kit.py` is at dbebb28 (form (b) `click_check`). During the run the working tree's `abx_kit.py` also gained D-M3g's label constants (not by this builder). That change touches only `check_scene`'s `label` fields, and no measured value.
- Method: K4's (file 29), through `abx_kit.py`'s own functions. D-M3b is applied in the scratch script only (not in the
  kit). Scenes are in `build/k7/<layout>__<placement>/scene.json` only, not committed.
- Every check is recorded and the run continues past a failure. No check failed fatally.

## Candidates

Built as K4 built them: from `abx_kit.scene_layout4_s1_default()` (20 × 30 × 10 m, tailSeed 12345), every face α 0.01
except one face at α 1, with s uniform on all six faces.
- **Layout 4:** the floor is at α 1. **Layout 5:** `xMin` is at α 1.
- **Placements** (`tests/unit/test_diffuse_wsweep.cpp` L75–107):

| placement | listener | S0 | S1 |
|---|---|---|---|
| `default` | R0 (10, 8, 1.7) | (7, 20, 2) | (13, 20, 2) |
| `listener_wall` | (10, 0.1, 1.7) | (7, 20, 2) | (13, 20, 2) |
| `emitter_wall` | R0 | (7, 29.9, 2) | (13, 20, 2) |
| `both_wall` | (10, 0.1, 1.7) | (7, 29.9, 2) | (13, 20, 2) |

- **New:** layout5_s{0.7, 0.8, 0.9}/default, layout5_s0.7/emitter_wall, layout4_s0.7/{listener_wall, emitter_wall,
  both_wall}.
- **Added for interrogator file 3:**
  - layout5_s1/emitter_wall (V3's S-W) under the new checks (its item 2);
  - s = 0.8 and 0.9 wherever s = 0.7 is not capped (its item 3). These are layout4/emitter_wall and layout5/emitter_wall;
    layout5/default at 0.8 and 0.9 was already in the list.
- **Re-checks:**
  - S-A (layout4_s1/default);
  - S-B\* (layout4_s0.7/default);
  - layout4_s1/both_wall;
  - layout5_s1/default.

## Table 1: K4's columns, tail T30 and Seat 9's prints

S-A, S-B\* and layout5_s1/emitter_wall reproduce K4's rows to the printed digits: caps, peaks, D/R, share, ΔG, ΔC80, specular share, s_w,
T30 and early part.

| candidate | capped m = 6/7/8 | peak dBFS (10 noise stimuli) | per-emitter D/R 1 kHz, L / R (dB) | heard D/R 1 kHz (dB) | tail share of heard energy, 1 kHz (g = +0.9) | ΔG at +0.9, 1 kHz / broadband (dB) | ΔC80 at +0.9, 1 kHz / broadband (dB) | E_target specular share, max over bands, L / R | s_w broadband (max band), max over g and emitters | item 6 IR level incl. M1 identities (±0.9, ±0.5, ±3) | heard T30 1 kHz (s) | tail T30 1 kHz, L / R (s) | early part (images ≥ 1 non-zero L, R; early re direct, broadband, max over emitters) | ITDG L / R (ms) | D/R 1 kHz vs expectation, Sabine A (Eyring A), L; R (dB) |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| layout5_s0.7/default | **no/no/no** (neither emitter capped) | −3.6 to −1.3 | −3.3 / −9.4 | −4.5 | 0.653 | 0.606 / 0.385 | −0.875 / −0.880 | 0.010 / 0.137 | 1.5e−06 (1.5e−03) | pass (per-band step err ≤ 8.0e−3 dB) | 2.578 | 2.617 / 2.600 | 349/349, 31/31; −4.9 dB | 1.6 / 1.6 | −3.3 vs −13.5 (−13.2); −9.4 vs −13.5 (−13.2) |
| layout5_s0.8/default | yes/yes/yes | −6.1 to −5.2 | −3.6 / −4.4 | −1.4 | 0.485 | 0.460 / 0.156 | −0.897 / −0.888 | 0.004 / 0.004 | 6.5e−12 (8.1e−09) | pass (≤ 4.1e−5 dB) | 2.556 | 2.617 / 2.600 | 349/349, 350/350; −6.9 dB | 1.6 / 1.6 | −3.6 vs −13.5 (−13.2); −4.4 vs −13.5 (−13.2) |
| layout5_s0.9/default | yes/yes/yes | −7.5 to −6.7 | −3.7 / −4.9 | −1.6 | 0.545 | 0.513 / 0.187 | −0.899 / −0.898 | 0.001 / 0.001 | 4.0e−13 (2.3e−10) | pass (≤ 6.0e−6 dB) | 2.556 | 2.617 / 2.600 | 349/349, 350/350; −10.3 dB | 1.6 / 1.6 | −3.7 vs −13.5 (−13.2); −4.9 vs −13.5 (−13.2) |
| layout5_s0.7/emitter_wall | **no/no/no** | −3.2 to **+0.3** | −13.6 / −9.6 | −11.9 | 0.887 | 0.807 / 0.693 | −0.825 / −0.850 | 0.082 / 0.130 | 5.2e−05 (1.4e−03) | pass (≤ 1.4e−2 dB) | 2.583 | 2.582 / 2.600 | 55/55, 31/31; −3.0 dB | 0.6 / 1.6 | −13.6 vs −18.6 (−18.2); −9.6 vs −13.5 (−13.2) |
| layout5_s0.8/emitter_wall | yes/yes/yes | −6.6 to −3.8 | −12.9 / −4.5 | −9.5 | 0.834 | 0.763 / 0.576 | −0.899 / −0.897 | 0.052 / 0.003 | 1.2e−05 (1.2e−04) | pass (≤ 4.5e−3 dB) | 2.561 | 2.582 / 2.600 | 55/55, 350/350; −5.2 dB | 0.6 / 1.6 | −12.9 vs −18.6 (−18.2); −4.5 vs −13.5 (−13.2) |
| layout5_s0.9/emitter_wall | yes/yes/yes | −8.0 to −4.8 | −12.7 / −5.0 | −9.5 | 0.852 | 0.778 / 0.602 | −0.900 / −0.899 | 0.022 / 0.001 | 7.3e−07 (5.2e−05) | pass (≤ 8.8e−4 dB) | 2.560 | 2.582 / 2.600 | 55/55, 350/350; −8.6 dB | 0.6 / 1.6 | −12.7 vs −18.6 (−18.2); −5.0 vs −13.5 (−13.2) |
| layout4_s0.7/listener_wall | yes/yes/yes | −8.8 to −7.0 | −0.4 / −0.7 | +0.4 | 0.126 | 0.124 / 0.019 | −0.743 / −0.558 | 0.022 / 0.023 | 1.5e−05 (2.2e−04) | pass (≤ 1.3e−2 dB) | 1.664 | 1.254 / 1.274 | 181/181, 181/181; −2.1 dB | 0.6 / 0.6 | −0.4 vs −15.0 (−14.4); −0.7 vs −15.0 (−14.4) |
| layout4_s0.7/emitter_wall | **no/no/no** | −8.5 to −6.8 | −9.4 / +1.3 | −4.3 | 0.464 | 0.440 / 0.277 | −0.873 / −0.849 | 0.141 / 0.030 | 5.5e−07 (2.6e−03) | pass (≤ 8.1e−2 dB) | 1.413 | 1.321 / 1.274 | 29/29, 174/174; −1.7 dB | 0.6 / 23.6 | −9.4 vs −15.8 (−15.2); +1.3 vs −10.8 (−10.1) |
| layout4_s0.8/emitter_wall | **no/no/no** | −10.1 to −8.4 | −9.1 / +3.2 | −3.8 | 0.502 | 0.474 / 0.307 | −0.891 / −0.880 | 0.079 / 0.013 | 2.2e−08 (1.0e−03) | pass (≤ 5.1e−2 dB) | 1.405 | 1.321 / 1.274 | 29/29, 174/174; −3.8 dB | 0.6 / 23.6 | −9.1 vs −15.8 (−15.2); +3.2 vs −10.8 (−10.1) |
| layout4_s0.9/emitter_wall | **yes/no/no** | −11.7 to −9.5 | −8.6 / +5.6 | −3.3 | 0.536 | 0.505 / 0.336 | −0.899 / −0.896 | 0.033 / 0.004 | 1.2e−09 (2.1e−04) | pass (≤ 2.2e−2 dB) | 1.397 | 1.321 / 1.274 | 29/29, 174/174; −7.1 dB | 0.6 / 23.6 | −8.6 vs −15.8 (−15.2); +5.6 vs −10.8 (−10.1) |
| layout4_s0.7/both_wall | yes/yes/yes | −9.5 to −7.6 | −10.3 / −0.6 | −8.2 | 0.692 | 0.641 / 0.296 | −0.891 / −0.866 | 0.090 / 0.025 | 1.6e−05 (1.3e−03) | pass (≤ 1.4e−2 dB) | 1.371 | 1.313 / 1.274 | 39/39, 181/181; −1.3 dB | 0.6 / 0.6 | −10.3 vs −18.5 (−17.8); −0.6 vs −15.0 (−14.4) |
| **S-A** layout4_s1/default | yes/yes/yes | −11.7 to −10.3 | +10.7 / +9.7 | +13.1 | 0.046 | 0.045 / 0.011 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (2.4e−12) | pass (≤ 8.0e−8 dB) | 2.009 | 1.254 / 1.274 | 0/174, 0/174; −76.7 dB | — / — (no non-zero image) | +10.7 vs −10.8 (−10.1); +9.7 vs −10.8 (−10.1) |
| **S-B\*** layout4_s0.7/default | yes/yes/yes | −7.6 to −6.3 | +1.5 / +1.3 | +1.7 | 0.032 | 0.032 / 0.008 | −0.519 / −0.329 | 0.032 / 0.029 | 6.1e−07 (2.5e−05) | pass (≤ 3.9e−3 dB) | 1.831 | 1.254 / 1.274 | 174/174, 174/174; −3.8 dB | 23.6 / 23.6 | +1.5 vs −10.8 (−10.1); +1.3 vs −10.8 (−10.1) |
| layout4_s1/both_wall | yes/yes/yes | −15.7 to −12.9 | −7.7 / +5.2 | −5.3 | 0.667 | 0.621 / 0.471 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (1.0e−05) | pass (≤ 7.9e−4 dB) | 1.370 | 1.313 / 1.274 | 0/39, 0/181; −67.9 dB | — / — | −7.7 vs −18.5 (−17.8); +5.2 vs −15.0 (−14.4) |
| layout5_s1/default | yes/yes/yes | −9.6 to −8.1 | −3.8 / −4.8 | −1.4 | 0.579 | 0.543 / 0.208 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (3.1e−12) | pass (≤ 5.3e−8 dB) | 2.557 | 2.617 / 2.600 | 0/349, 0/350; −76.7 dB | — / — | −3.8 vs −13.5 (−13.2); −4.8 vs −13.5 (−13.2) |
| layout5_s1/emitter_wall | yes/yes/yes | −8.3 to −5.8 | −12.4 / −5.0 | −9.5 | 0.869 | 0.792 / 0.633 | −0.900 / −0.900 | 0.000 / 0.000 | 4.3e−13 (2.8e−06) | pass (≤ 4.7e−4 dB) | 2.559 | 2.582 / 2.600 | 0/55, 0/350; −71.0 dB | — / — | −12.4 vs −18.6 (−18.2); −5.0 vs −13.5 (−13.2) |

**Column notes**
- **Capped.** "no/no/no" means at least one emitter is not capped at that m (the per-emitter flags are in `k7.json`).
- **Item 6 IR level** is `ir_assertions` at all six g, which covers:
  - the early part bit-identical;
  - M1's first identity, 10 log10(E(s − u)/E(u)) = 20 log10|a − 1|, over the tail window (0.1 dB) and over the tail
    alone (0.01 dB);
  - the tail-alone step = g;
  - s_w ≤ 2.3 %.
- **Per-band step error.** M1's second identity, "the per-band step equals g", is printed as the maximum |per-band step
  over [t_mix,e, L) − g| across all g, bands and emitters. It was not asserted.
- **D/R expectation** = 20 log10(r_c/r), with r_c = (A/16π)^½ (Kuttruff Eq. 5.44).
  - A is Σ Sα (1 kHz) + 24 m² of air: Seat 9's basis, K9. Layout 4 gives 640 m², layout 5 gives 343 m².
  - The Eyring A is in parentheses: 747 / 387 m².
- **ITDG** is the first image of order ≥ 1 with non-zero amplitude in `--images`, measured from the direct sound.
  - Layout 5 at R0: the floor (α 0.01) at 1.6 ms.
  - Layout 4 at R0: the ceiling at 23.6 ms.
  - Wall placements: the adjacent wall at 0.6 ms.

## Table 2: the new checks (form (b), D-M3b, gap, Q5, nulls, length)

**Noise chain:** 10 stimuli per scene, the K4 pattern:
- the first 2 trials of each block (0.9 dB and 0.5 dB, kit trial plan);
- the 6 familiarisation pairs (±3, ±0.9, ±0.5).

**Speech chain:** McGill TSP v2, speaker MA, MA01_01 and MA01_02. This is the kit docstring's example pair; the run sheet
fixes no pair yet. The chain gives:
- the Q5 window over every boundary;
- 4 rendered stimuli (the first 2 trials of each block) with mid-fade and form (b).

| candidate | gap, heard-T30 rule (kit as is): `gap_check` (gap s) | gap, max(heard, tail) rule (gap s) | D-M3b: onset moved by (partitions); N − heard end, L / R (samples) | noise: form (b) pass; mid-fade (W-a, (i)–(iii)) pass | noise: residual peak in step region, HP sample / max HP frame (dBFS; floor −90) | null B vs offline / E vs offline stepped IR (dB, worst) | Q5: speech onset shift (partitions); passing / boundaries; realised window (T30 after end of speech) | speech: form (b); mid-fade; peak | stimulus length, noise (mean) / speech (s) | K6 typical pace, full design (h) |
|---|---|---|---|---|---|---|---|---|---|---|
| layout5_s0.7/default | **FAIL** (2.581 < 2.617) | pass (2.624) | 1; 480 / 480 | 10/10; 10/10 | −146 / −155 | −133.8 / −132.2 | 0; 86/104; [0.001, 0.352] | 4/4; 4/4; −21.7 | 15.26 / 11.58 | 2.40 |
| layout5_s0.8/default | **FAIL** (2.560 < 2.617) | pass (2.624) | 1; 480 / 480 | 10/10; 10/10 | −150 / −161 | −133.6 / −131.5 | 0; 101/103; [0.001, 0.422] | 4/4; 4/4; −21.9 | 15.26 / 11.58 | 2.40 |
| layout5_s0.9/default | **FAIL** (2.560 < 2.617) | pass (2.624) | 1; 480 / 480 | 10/10; 10/10 | −155 / −163 | −133.4 / −131.4 | 0; 102/103; [0.001, 0.426] | 4/4; 4/4; −21.9 | 15.26 / 11.58 | 2.40 |
| layout5_s0.7/emitter_wall | **FAIL** (2.592 < 2.600) | pass (2.603) | 3; 141 / 1504 | 10/10; 10/10 | −146 / −156 | −132.4 / −130.7 | 3; 83/101; [0.013, 0.352] | 4/4; 4/4; −22.3 | 15.22 / 11.56 | 2.39 |
| layout5_s0.8/emitter_wall | **FAIL** (2.571 < 2.600) | pass (2.603) | 3; 141 / 1504 | 10/10; 10/10 | −152 / −161 | −131.5 / −129.8 | 3; 88/101; [0.013, 0.375] | 4/4; 4/4; −25.9 | 15.22 / 11.56 | 2.39 |
| layout5_s0.9/emitter_wall | **FAIL** (2.560 < 2.600) | pass (2.603) | 3; 141 / 1504 | 10/10; 10/10 | −150 / −162 | −130.9 / −129.9 | 3; 89/101; [0.013, 0.380] | 4/4; 4/4; −26.4 | 15.22 / 11.56 | 2.39 |
| layout4_s0.7/listener_wall | pass (1.675) | pass (1.675) | 1; 480 / 480 | 10/10; 10/10 | −154 / −165 | −135.9 / −133.4 | 0; 43/67; [0.001, 0.270] | 4/4; 4/4; −25.4 | 10.20 / 8.41 | 1.84 |
| layout4_s0.7/emitter_wall | pass (1.419) | pass (1.419) | 3; 141 / 1504 | 10/10; 10/10 | −154 / −163 | −134.3 / −131.0 | 3; 35/54; [0.024, 0.280] | 4/4; 4/4; −26.3 | 9.48 / 8.18 | 1.78 |
| layout4_s0.8/emitter_wall | pass (1.408) | pass (1.408) | 3; 141 / 1504 | 10/10; 10/10 | −156 / −164 | −133.9 / −131.0 | 3; 35/54; [0.024, 0.282] | 4/4; 4/4; −26.8 | 9.44 / 8.17 | 1.77 |
| layout4_s0.9/emitter_wall | pass (1.397) | pass (1.397) | 3; 141 / 1504 | 10/10; 10/10 | −156 / −168 | −133.1 / −130.7 | 3; 35/54; [0.024, 0.283] | 4/4; 4/4; −27.2 | 9.41 / 8.16 | 1.77 |
| layout4_s0.7/both_wall | pass (1.376) | pass (1.376) | 3; 129 / 1504 | 10/10; 10/10 | −156 / −165 | −134.2 / −130.4 | 3; 36/53; [0.024, 0.297] | 4/4; 4/4; −30.6 | 9.32 / 8.11 | 1.76 |
| **S-A** layout4_s1/default | pass (2.016) | pass (2.016) | 1; 480 / 480 | 10/10; 10/10 | −168 / −180 | −135.0 / −134.0 | 0; 35/81; [0.001, 0.187] | 4/4; 4/4; −22.2 | 11.25 / 8.77 | 1.94 |
| **S-B\*** layout4_s0.7/default | pass (1.835) | pass (1.835) | 1; 480 / 480 | 10/10; 10/10 | −154 / −163 | −135.2 / −133.7 | 0; 34/74; [0.001, 0.193] | 4/4; 4/4; −21.7 | 10.70 / 8.60 | 1.89 |
| layout4_s1/both_wall | pass (1.376) | pass (1.376) | 3; 129 / 1504 | 10/10; 10/10 | −162 / −170 | −132.4 / −130.7 | 3; 38/53; [0.024, 0.320] | 4/4; 4/4; −31.6 | 9.32 / 8.11 | 1.76 |
| layout5_s1/default | **FAIL** (2.560 < 2.617) | pass (2.624) | 1; 480 / 480 | 10/10; 10/10 | −154 / −163 | −132.7 / −132.0 | 0; 103/103; [0.001, 0.426] | 4/4; 4/4; −21.8 | 15.26 / 11.58 | 2.40 |
| layout5_s1/emitter_wall | **FAIL** (2.560 < 2.600) | pass (2.603) | 3; 141 / 1504 | 10/10; 10/10 | −152 / −160 | −131.0 / −130.8 | 3; 92/101; [0.013, 0.413] | 4/4; 4/4; −25.9 | 15.22 / 11.56 | 2.39 |

The two gap columns test the **programme** gap, which is what `gap_check` reads. What D-M3b does to the silence after N
and to the heard gaps is in Table 4.

## Table 3: Seat 2's C1

Per emitter IR, L / R:
- **Energy ratio:** E[t_mix,e − 12.5, t_mix,e − 2.5) ms against E[t_mix,e + 2.5, t_mix,e + 12.5) ms, in dB.
- **Early envelope:** the time the early envelope falls 60 dB below direct.

| candidate | t_mix,e after direct, L / R (ms) | broadband ratio (dB) | 1 kHz ratio (dB) | 8 kHz ratio (dB) | early envelope 60 dB below direct, L / R |
|---|---|---|---|---|---|
| layout5_s0.7/default | 344.4 / 77.5 | −70.6 / −11.4 | −29.9 / −17.0 | −60.0 / −10.7 | 291.5 ms / not before t_mix,e − 2.5 ms (last window −27.4 dB) |
| layout5_s0.8/default | 344.4 / 344.4 | −93.5 / −94.0 | −29.9 / −26.1 | −60.2 / −61.6 | 286.5 / 283.5 ms |
| layout5_s0.9/default | 344.4 / 344.4 | −130.7 / −131.8 | −29.9 / −26.1 | −60.2 / −61.6 | 232.5 / 232.5 ms |
| layout5_s0.7/emitter_wall | 77.5 / 77.5 | −16.7 / −11.6 | −20.8 / −17.2 | −18.5 / −10.9 | not before t_mix,e − 2.5 ms (−29.5 / −27.4 dB) |
| layout5_s0.8/emitter_wall | 77.5 / 344.4 | −21.6 / −94.1 | −24.7 / −26.1 | −23.9 / −61.6 | not before t_mix,e − 2.5 ms (−36.6 dB) / 283.5 ms |
| layout5_s0.9/emitter_wall | 77.5 / 344.4 | −30.7 / −131.9 | −29.2 / −26.1 | −33.4 / −61.6 | not before t_mix,e − 2.5 ms (−48.6 dB) / 232.5 ms |
| layout4_s0.7/listener_wall | 321.2 / 321.2 | −32.8 / −32.3 | −31.2 / −25.7 | −33.3 / −32.5 | not before t_mix,e − 2.5 ms (−58.7 / −58.7 dB) |
| layout4_s0.7/emitter_wall | 77.5 / 344.4 | −13.2 / −33.8 | −14.1 / −24.9 | −12.7 / −33.5 | not before t_mix,e − 2.5 ms (−29.5 dB) / 324.5 ms |
| layout4_s0.8/emitter_wall | 77.5 / 344.4 | −18.7 / −46.9 | −18.4 / −25.9 | −18.2 / −46.4 | not before t_mix,e − 2.5 ms (−36.6 dB) / 286.5 ms |
| layout4_s0.9/emitter_wall | 77.5 / 344.4 | −27.9 / −68.9 | −24.7 / −26.0 | −27.4 / −60.7 | not before t_mix,e − 2.5 ms (−48.6 dB) / 232.5 ms |
| layout4_s0.7/both_wall | 77.5 / 321.2 | −9.5 / −31.9 | −17.5 / −25.6 | −9.1 / −32.2 | not before t_mix,e − 2.5 ms (−59.5 / −58.7 dB) |
| S-A layout4_s1/default | 344.4 / 344.4 | −320.6 / −320.4 | −29.5 / −26.0 | −60.0 / −61.5 | early part never within 60 dB of direct (max −77.9 dB) |
| **S-B\*** layout4_s0.7/default | 344.4 / 344.4 | −33.9 / −34.0 | −27.4 / −24.9 | −33.9 / −33.6 | 324.5 / 324.5 ms |
| layout4_s1/both_wall | 77.5 / 321.2 | −115.1 / −324.3 | −35.5 / −28.1 | −58.9 / −63.2 | never within 60 dB (max −69.1 / −73.2 dB) |
| layout5_s1/default | 344.4 / 344.4 | −331.8 / −332.0 | −29.9 / −26.1 | −60.2 / −61.6 | never within 60 dB (max −77.9 dB) |
| layout5_s1/emitter_wall | 77.5 / 344.4 | −120.3 / −332.3 | −31.9 / −26.1 | −55.6 / −61.6 | never within 60 dB (max −72.2 / −77.9 dB) |

All eight bands per emitter are in `k7.json` (`emitters[].C1`).

**Filter floor.** On s = 1 scenes the early part is empty (broadband −320 dB), yet the band ratios read −26 to −30 dB
at 1 kHz and −3 to −6 dB at 63 Hz. That is the zero-phase octave filter's acausal skirt carrying tail energy into the
"before" window (`filter_band_with_lead`). Band ratios at or near the S-A row are that floor, not early energy. The
broadband column has no such floor.

**Envelope method.** 1 ms windows from direct + 2.5 ms to t_mix,e − 2.5 ms, against the 1 ms window around the direct
peak. The time given is the end of the last window at or above −60 dB, measured from the direct sound.

## Table 4: the silence after N, heard gaps, and Seat 2's C2 (interrogator file 3, items 1 and 4)

Each cell gives seconds, then in parentheses the difference in ms against the heard T30 and against the largest tail
T30 (negative means shorter). Samples are seconds × 48 000; they are in `build/k7/k7_gaps_c2.json`, together with the
booleans "≥ heard T30" and "≥ every tail T30".

- **Heard onset** of a burst = its input onset + the smaller direct delay. **Heard end** = its input end + the larger.
- **"Kit as is + D-M3b"** is D-M3b as written: the kit's programme is unchanged (gap = ⌈T30_heard·fs/P⌉·P), and only the
  onset moves to N. Burst 3 stays at input end + gap, so the silence after N shrinks by N − input end.
- **"K7-builder"** is the programme the K7-builder chains actually rendered: gap built from max(heard, tail) T30, with
  burst 3 moved with N.

These are measured facts. No fix is proposed. D-M3b failed interrogation on this point (file 3).

| candidate | direct-path difference between emitters (ms) | nearest face: listener / S0 / S1 (m) | C2 (no face ≤ 0.1 m and difference ≤ 2.5 ms) | kit as is + D-M3b: N → next burst, input onset | same: N → next burst, heard onset | same: heard gap between bursts | K7-builder: N → next burst, input onset | K7-builder: N → next burst, heard onset | K7-builder: heard gap, burst 1 → 2 | K7-builder: heard gap, burst 2 → 3 |
|---|---|---|---|---|---|---|---|---|---|---|
| layout5_s0.7/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 2.571 (-8 / -47) | 2.571 (-7 / -46) | 2.581 (+3 / -36) | 2.624 (+46 / +7) | 2.625 (+46 / +7) | 2.624 (+46 / +7) | 2.635 (+56 / +17) |
| layout5_s0.8/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 2.549 (-6 / -68) | 2.550 (-6 / -67) | 2.560 (+4 / -57) | 2.624 (+68 / +7) | 2.625 (+69 / +7) | 2.624 (+68 / +7) | 2.635 (+79 / +17) |
| layout5_s0.9/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 2.549 (-6 / -68) | 2.550 (-6 / -67) | 2.560 (+4 / -57) | 2.624 (+68 / +7) | 2.625 (+69 / +7) | 2.624 (+68 / +7) | 2.635 (+79 / +17) |
| layout5_s0.7/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 2.560 (-23 / -40) | 2.561 (-22 / -40) | 2.564 (-19 / -37) | 2.603 (+20 / +2) | 2.603 (+21 / +3) | 2.574 (-8 / -26) | 2.606 (+24 / +6) |
| layout4_s0.7/listener_wall | 0.00 | 0.1 / 2.0 / 2.0 | **fail** | 1.664 (-0 / +390) | 1.665 (+0 / +391) | 1.675 (+10 / +401) | 1.675 (+10 / +401) | 1.675 (+11 / +401) | 1.675 (+10 / +401) | 1.685 (+21 / +411) |
| layout4_s0.7/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 1.387 (-26 / +66) | 1.387 (-26 / +67) | 1.390 (-23 / +70) | 1.419 (+6 / +98) | 1.419 (+6 / +99) | 1.390 (-23 / +70) | 1.422 (+9 / +102) |
| layout4_s0.7/both_wall | 28.65 | 0.1 / 0.1 / 2.0 | **fail** | 1.344 (-27 / +31) | 1.345 (-26 / +32) | 1.347 (-24 / +35) | 1.376 (+5 / +63) | 1.377 (+6 / +64) | 1.347 (-24 / +35) | 1.379 (+8 / +67) |
| layout4_s1/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 2.005 (-3 / +732) | 2.006 (-3 / +732) | 2.016 (+7 / +742) | 2.016 (+7 / +742) | 2.017 (+8 / +743) | 2.016 (+7 / +742) | 2.027 (+18 / +753) |
| layout4_s0.7/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 1.824 (-7 / +550) | 1.825 (-6 / +551) | 1.835 (+4 / +561) | 1.835 (+4 / +561) | 1.835 (+5 / +562) | 1.835 (+4 / +561) | 1.845 (+15 / +572) |
| layout4_s1/both_wall | 28.65 | 0.1 / 0.1 / 2.0 | **fail** | 1.344 (-26 / +31) | 1.345 (-25 / +32) | 1.347 (-22 / +35) | 1.376 (+6 / +63) | 1.377 (+7 / +64) | 1.347 (-22 / +35) | 1.379 (+10 / +67) |
| layout5_s1/default | 0.00 | 1.7 / 2.0 / 2.0 | pass | 2.549 (-7 / -68) | 2.550 (-7 / -67) | 2.560 (+3 / -57) | 2.624 (+67 / +7) | 2.625 (+68 / +7) | 2.624 (+67 / +7) | 2.635 (+78 / +17) |
| layout5_s1/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 2.528 (-31 / -72) | 2.529 (-31 / -71) | 2.532 (-28 / -69) | 2.603 (+43 / +3) | 2.603 (+44 / +3) | 2.574 (+15 / -26) | 2.606 (+47 / +6) |
| layout5_s0.8/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 2.539 (-22 / -61) | 2.539 (-21 / -61) | 2.542 (-18 / -58) | 2.603 (+42 / +3) | 2.603 (+43 / +3) | 2.574 (+14 / -26) | 2.606 (+46 / +6) |
| layout5_s0.9/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 2.528 (-32 / -72) | 2.529 (-31 / -71) | 2.532 (-28 / -69) | 2.603 (+43 / +3) | 2.603 (+44 / +3) | 2.574 (+14 / -26) | 2.606 (+46 / +6) |
| layout4_s0.8/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 1.376 (-29 / +55) | 1.377 (-28 / +56) | 1.380 (-25 / +59) | 1.408 (+3 / +87) | 1.409 (+4 / +88) | 1.380 (-25 / +59) | 1.412 (+7 / +91) |
| layout4_s0.9/emitter_wall | 28.40 | 1.7 / 0.1 / 2.0 | **fail** | 1.365 (-32 / +45) | 1.366 (-31 / +45) | 1.369 (-28 / +48) | 1.397 (+0 / +77) | 1.398 (+1 / +77) | 1.369 (-28 / +48) | 1.401 (+4 / +80) |

## Facts for the decider

1. **Caps.** Five of the eleven s < 1 candidates are not capped at all of m = 6, 7 and 8:
   - layout5_s0.7/default: neither emitter at any m. R's ISM handover is at 77.5 ms with `ismFallback` false.
   - layout5_s0.7/emitter_wall: neither emitter at any m.
   - layout4_s0.7/emitter_wall and layout4_s0.8/emitter_wall: neither emitter at any m.
   - layout4_s0.9/emitter_wall: both emitters at m = 6, neither at 7 or 8.

   The s = 0.8 and 0.9 runs required by interrogator file 3, item 3, give:
   - **layout5/emitter_wall:** capped at all three m at s = 0.8 and 0.9.
   - **layout4/emitter_wall:** not capped at s = 0.8 or 0.9. At s = 1 it is capped (K4).
   - **layout5/default:** capped at s = 0.8 and 0.9.

   Every other candidate and all five re-checks are capped at all three m.

2. **Peak (item 10, ≤ −1 dBFS).** layout5_s0.7/emitter_wall reaches **+0.3 dBFS** and fails. layout5_s0.7/default
   reaches −1.28 dBFS, which passes with 0.28 dB of margin over 10 stimuli. Every other scene peaks at −3.8 dBFS or
   below; the highest of these is layout5_s0.8/emitter_wall.

3. **Item 6, IR level, and M1's identities.** These pass on every scene at all six g. M1's identity is therefore live and
   passing on every s < 1 scene; their E_target specular share is 0.001 to 0.141, against 0 on every s = 1 scene.
   - s_w is at most 5.2e−5 broadband and 2.6e−3 in the worst band, against the 2.3 % limit.
   - The per-band step error over [t_mix,e, L) is at most 0.081 dB, on layout4_s0.7/emitter_wall (uncapped).
   - It is at most 0.014 dB on every capped s < 1 scene and ≤ 8e−4 dB at s = 1.

4. **Form (b) and mid-fade.** These pass on all 160 noise stimuli and all 64 speech stimuli (16 scenes). In the step
   region the high-passed residual r = (A − B) − m peaks at −146 dBFS or below (single sample), and its loudest 2 ms
   frame is at −154 dBFS or below. That is at least 64 dB under the −90 dBFS floor and consistent with M3-L1's 8u
   bound.
   - Detector events on A, B and E are printed per stimulus in `k7.json` (`events_A_B_E`).
   - On S-A they are 13 / 13 / 13 on the first stimulus.

5. **Nulls (D-M3a, Seat 3's gap).** All 160 noise stimuli pass the −120 dB criterion:
   - B against `render_cli`'s offline render: −130.9 dB at worst.
   - E against the offline render of the stepped IR: −129.8 dB at worst (layout5_s0.8/emitter_wall), and −130.0 dB or
     better on the speech stimuli.

   The offline path for E is `sim::renderOffline` emulated in double: out_o = Σ_e x_e ∗ ir(e, o), with the stepped IR
   from `--abx-stepped-ir`. That emulation nulls against `render_cli`'s own offline render of B at −219 dB or better on
   every stimulus, so it is the same computation. `render_cli` refuses `--abx-step-db` with `--in/--out` and no
   `--realtime-emulation` (Cli.cpp L361), so there is no direct CLI path for an offline E. All lengths match:
   A = B = E = offline.

6. **D-M3b: the onset.**
   - **Default and listener-wall placements** (both direct sounds at tap 32): the noise onset moves by **1 partition**
     on every scene, S-A included. N − heard end is 480 samples for both emitters.
   - **Emitter-wall placements** (direct-path difference 28.4–28.65 ms; the far emitter's direct at tap 1395 or 1407):
     the onset moves by **3 partitions**, with N − heard end ≥ 129 samples. N − heard end is ≥ 0 everywhere.
   - **Speech:** the first Q5 boundary is unchanged on default placements, because the kit's first boundary already lies
     ≥ 32 samples after the end of speech. It moves by 3 partitions on emitter-wall placements, which shifts the realised
     window start from about 0.001 T30 to 0.013–0.024 T30.

7. **D-M3b: the silence after N (Table 4; interrogator file 3, item 1).**
   - **Kit as is + D-M3b (as written).** On every scene, the silence from N to the next burst's input onset is shorter
     than the heard T30:
     - by 0.45 ms (listener_wall), 3.4 ms (S-A) and 7 ms (S-B\*) on layout 4;
     - by 6 to 8 ms on layout 5 at default;
     - by 22 to 32 ms on emitter-wall and both-wall placements. This confirms the interrogator's
     gap < T30·fs + P. Against every tail T30:
     - every layout-5 scene fails, by 40 to 72 ms;
     - every layout-4 scene passes, by 31 ms (both_wall) to 732 ms (S-A).

     The heard gap between bursts is gap + d_min − d_max. It falls below the heard T30 by 18 to 28 ms on every
     emitter-wall and both-wall placement, and below every tail T30 on every layout-5 scene.
   - **K7-builder programme.** The silence from N to the next burst's input onset and heard onset is ≥ heard T30 and
     ≥ every tail T30 on every scene, with margins of +0.1 ms (layout4_s0.9/emitter_wall, input onset) to +79 ms.

     The heard gap between bursts 1 and 2 (before the onset) is gap − 28.4 ms on emitter-wall and both-wall
     placements, and the max rule does not cover it:
     - it is below the heard T30 on layout4_s0.7/both_wall, layout4_s1/both_wall and layout4_s0.{7,8,9}/emitter_wall,
       by 22 to 28 ms; these still pass every tail T30, by ≥ 35 ms;
     - it is below every tail T30 on **layout5_s{0.7, 0.8, 0.9, 1}/emitter_wall**: 2.574 s against 2.600 s, 26 ms short;
     - it is below the heard T30 on layout5_s0.7/emitter_wall, by 8 ms.

8. **Gap (M2, programme gap as `gap_check` reads it).**
   - **Heard-T30 rule (the kit as it is):** `gap_check` fails on **every layout-5 scene** (s = 0.7, 0.8, 0.9 and 1;
     default and emitter_wall). The heard T30 is 2.556–2.583 s and the tail T30 2.582–2.617 s, so gaps of 2.560–2.592 s
     fall short by 8 to 57 ms. It passes on every layout-4 scene.
   - **max(heard, tail) rule:** passes by construction.

9. **Q5.** This passes on all sixteen scenes: at least 34 passing boundaries, and the ≥ 20 dB assertion holds on every
   rendered speech stimulus.
   - **Realised windows:** [0.001, 0.19] T30 on S-A and S-B\*; up to [0.001, 0.43] on layout 5; [0.013–0.024, 0.27–0.41]
     on the emitter-wall and both-wall placements.
   - **Floor:** −98.7 dB at 1 kHz on S-A (TSP's own noise through the room).

10. **Tail share at 1 kHz, against S-A's 0.046** (s < 1 scenes):

    | scene | share |
    |---|---|
    | layout4_s0.7/default (S-B\*) | 0.032 |
    | layout4_s0.7/listener_wall | 0.126 |
    | layout4_s0.7/emitter_wall | 0.464 |
    | layout5_s0.8/default | 0.485 |
    | layout4_s0.8/emitter_wall | 0.502 |
    | layout4_s0.9/emitter_wall | 0.536 |
    | layout5_s0.9/default | 0.545 |
    | layout5_s0.7/default | 0.653 |
    | layout4_s0.7/both_wall | 0.692 |
    | layout5_s0.8/emitter_wall | 0.834 |
    | layout5_s0.9/emitter_wall | 0.852 |
    | layout5_s0.7/emitter_wall | 0.887 |

    The s = 1 references are 0.579 (layout5_s1/default), 0.667 (layout4_s1/both_wall) and 0.869
    (layout5_s1/emitter_wall). ΔC80 at 1 kHz is −0.74 to −0.90 dB on the wet s < 1 scenes, against −0.52 on S-B\* and
    −0.90 on S-A.

11. **Early part and Seat 9's prints.** Every s < 1 scene has a filled early part, −1.3 to −10.3 dB broadband re direct.
    The measured D/R is above the Sabine-A diffuse expectation on every scene, by 4.0 to 21.5 dB. The smallest gaps are
    on the emitter-wall far emitter, about 4 to 7 dB; the largest is S-A's far emitter, 21.5 dB.

12. **Seat 2's C2.** C2 fails on every placement except `default`:
    - listener_wall, emitter_wall and both_wall each put a listener or emitter 0.1 m from a face;
    - emitter_wall and both_wall also have a direct-path difference of 28.4–28.65 ms, against C2's 2.5 ms.

    All default placements pass, with a difference of 0 ms and nearest faces at 1.7 m (listener) and 2.0 m (emitters).

13. **Stimulus length (K6).** Layout-5 noise stimuli are 15.2–15.3 s and speech stimuli 11.6 s, against 11.25 and 8.77 s
    on S-A. K6's typical-pace model gives 2.39–2.40 h for the full design on any layout-5 scene, against 1.94 h on S-A.
    - The model is file 32: 5 plays + 8 s per trial, a 2 min break per block, f = 2, and 3 × 5 min rests. It reproduces
      S-A's 1.94 h.
    - Layout-4 wall placements give 1.76–1.84 h; S-B\* gives 1.89 h.

## The decider's qualifying rule ("What changes the winner"), with the interrogator's flags

The rule, for an s < 1 scene:
- capped at m = 6, 7 and 8;
- peak ≤ −1 dBFS;
- item 6 clean, including form (b);
- Q5 passes;
- gap ≥ tail T30;
- s_w ≤ 2.3 %;
- 1 kHz tail share > 0.046.

The gap column reads the programme gap (`gap_check`); Table 4 has the post-N silence and the heard gaps. Two columns are
flags only and not part of the decider's rule:
- **Seat 2's C2** (Fact 12);
- **Seat 4's layout-5 condition:** layout 5 is kept out of the binaural part (item 15), or the binaural record carries the
  "isotropic tail, anisotropic room" label with per-ear tail energy printed (1-seat4 §6, V3 2 → 1). K7-builder ran omni
  only, so no per-ear tail energy exists yet for any layout-5 scene.

| s < 1 candidate | capped | peak | item 6 + (b) | Q5 | programme gap ≥ tail T30 | s_w | share > 0.046 | **qualifies (decider's rule)** | heard-gap note (Table 4) | Seat 2 C2 | Seat 4 layout-5 condition |
|---|---|---|---|---|---|---|---|---|---|---|---|
| layout4_s0.7/listener_wall | yes | −7.0 | yes | yes | yes | yes | 0.126 | **yes** | kit + D-M3b: silence after N 0.45 ms short of heard T30 (≥ tail T30); K7-builder: all ≥ heard and tail T30 | **fail** (listener 0.1 m) | n/a (layout 4) |
| layout4_s0.7/both_wall | yes | −7.6 | yes | yes | yes | yes | 0.692 | **yes** | heard gaps 22–27 ms below heard T30 under both programmes (≥ tail T30) | **fail** (0.1 m; 28.65 ms) | n/a |
| layout5_s0.8/default | yes | −5.2 | yes | yes | heard rule no; max rule yes | yes | 0.485 | **only under the max(heard, tail) gap rule** | K7-builder programme: all ≥ every tail T30 | pass | **needed** (not met yet) |
| layout5_s0.9/default | yes | −6.7 | yes | yes | heard rule no; max rule yes | yes | 0.545 | **only under the max(heard, tail) gap rule** | as above | pass | **needed** (not met yet) |
| layout5_s0.8/emitter_wall | yes | −3.8 | yes | yes | heard rule no; max rule yes | yes | 0.834 | **only under the max rule, on the programme gap** | heard gap bursts 1 → 2 is 26 ms short of the tail T30 even under the max rule | **fail** (0.1 m; 28.4 ms) | **needed** |
| layout5_s0.9/emitter_wall | yes | −4.8 | yes | yes | heard rule no; max rule yes | yes | 0.852 | **only under the max rule, on the programme gap** | as above | **fail** | **needed** |
| layout5_s0.7/default | **no** | −1.3 | yes | yes | heard no; max yes | yes | 0.653 | no (cap) | — | pass | needed |
| layout5_s0.7/emitter_wall | **no** | **+0.3** | yes | yes | heard no; max yes | yes | 0.887 | no (cap, peak) | — | fail | needed |
| layout4_s0.7/emitter_wall | **no** | −6.8 | yes | yes | yes | yes | 0.464 | no (cap) | — | fail | n/a |
| layout4_s0.8/emitter_wall | **no** | −8.4 | yes | yes | yes | yes | 0.502 | no (cap) | — | fail | n/a |
| layout4_s0.9/emitter_wall | **yes/no/no** | −9.5 | yes | yes | yes | yes | 0.536 | no (cap at 7, 8) | — | fail | n/a |
| layout4_s0.7/default (S-B\*) | yes | −6.3 | yes | yes | yes | yes | **0.032** | no (share) | — | pass | n/a |

**Summary of the rule's outcome**
- **Qualifying under the kit's gap rule:** layout4_s0.7/listener_wall and layout4_s0.7/both_wall. Both fail Seat 2's C2.
- **Qualifying only if the gap is built from max(heard, tail) T30:** layout5_s0.8/default and layout5_s0.9/default.
  Both pass C2 and both need Seat 4's layout-5 condition.
- **Qualifying on the programme gap under the max rule, with a heard gap 26 ms short of the tail T30:**
  layout5_s0.8/emitter_wall and layout5_s0.9/emitter_wall. Both fail C2 and need Seat 4's condition.
- **No candidate** qualifies under the kit's gap rule while also passing C2.
- Which gap rule and which gap quantity apply is not decided here.

**Re-checks on s = 1 scenes.** S-A, layout4_s1/both_wall, layout5_s1/default and layout5_s1/emitter_wall pass every
check above except the s < 1 condition. The exceptions:
- the two layout-5 scenes fail the heard-T30 gap rule;
- layout5_s1/emitter_wall's heard gap between bursts 1 and 2 is 26 ms short of its tail T30, even under the max rule.

## Method

Scripts are in the scratchpad and not committed. They import `tools/ci/abx_kit.py` and `tools.acoustics`:
- `/tmp/claude-0/-home-user-makroof/af6ec831-18de-58d5-a237-0b9955c5e53f/scratchpad/k7/k7.py`: one scene per run;
- `k7table.py`, `k7c1bb.py` (the broadband C1) and `k7gaps.py` (Table 4: the post-N silence, heard gaps and C2), in the same folder;
- the scene list: `scenes.txt`, in the same folder.

Results are in `build/k7/<scene>/k7.json`, `build/k7/k7_table.json`, `build/k7/k7_c1_broadband.json` and `build/k7/k7_gaps_c2.json` (git-ignored).
TSP is in `build/k7/tsp/48k.zip`, fetched by `abx_kit.fetch_tsp` and checksum-verified. It is git-ignored and never
committed.

1. **Cap.** `--w-multiplier m --diagnostics` for m = 6, 7, 8, reading `emitters[].diffuse.capHit`.
2. **Scene metrics.** `abx_kit.check_scene` with `W_CANDIDATES = ()` (cap stop lifted, as K4). It gives the heard and
   per-emitter D/R and T30, and the tail T30 from t_mix,e.
3. **Early part and ITDG.** `--images` gives the image counts and ITDG. The early part is K4's step 3: broadband
   [direct + 2.5 ms, t_mix,e − 2.5 ms) against ±2.5 ms around direct.
4. **IR pairs.** `abx_kit.ir_pair`, `ir_assertions` (recorded, not raised), `ir_band_shares` and `heard_pair_metrics`
   at g = ±0.9, ±0.5, ±3. s_w is recomputed without assertions over [t_mix,e, L).
5. **Gap.** Heard rule: gap = ⌈T30_heard · fs / P⌉ · P, then `abx_kit.gap_check`. Max rule: the same with
   max(T30_heard, tail T30_L, tail T30_R).
6. **Noise chain.** For each of the 10 stimuli:
   1. `noise_programme(T_max-rule, seed_index, 7001)`, with D-M3b applied: heard end = input end + (directS −
      alignmentShiftS)·fs per emitter. N is the first multiple of P at or after the latest heard end. N − input end zeros
      are inserted at the input end, so burst 3 and the final gap move with N.
   2. Render A, B and E with `abx_kit._render` (realtime emulation, block 512, P 512), and the offline B with
      `render_cli --in --out`.
   3. `midfade_checks` and `click_check` (form (b)), both recorded.
   4. Residual peaks from `crossfade_residual`.
   5. Nulls 10 log10(E(x − ref)/E(ref)).
7. **Speech chain.** `build_speech_chain`'s logic, with these changes:
   - pause = ⌈max-rule T · fs⌉;
   - the first boundary is at or after the heard end of sentence 1 (D-M3b);
   - the last allowed boundary is the end of speech + 0.43 T30_heard (unchanged).

   Steps: the floor from TSP's own noise; the margins at every boundary; `q5_window_record`; then 4 stimuli, each with
   its onset drawn from the kit's seeded permutation over the passing set, and mid-fade, form (b) and the E null on
   each.
8. **C1.** `bands.filter_band_with_lead` per band on each emitter's IR (output 0), and the unfiltered IR for broadband.

**Run times.** The first eleven scenes, 4 processes in parallel on 4 cores, took 5 min 53 s wall-clock. The five scenes added for file 3 took 2 min 29 s.
- Per scene: 70–97 s for layout 4 and 130–145 s for layout 5.
- The noise chain is about 75 % of each.

Files: /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md, /home/user/makroof/tools/ci/abx_kit.py,
/home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (L75–107), /home/user/makroof/src/cli/Cli.cpp (L361),
/home/user/makroof/src/sim/OfflineRender.cpp (L133–171), /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md,
/home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md.
