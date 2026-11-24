# 27: Builder, the ABX chains rebuilt from the final kit (steward round 4, G12)

Kit at the commit after 7c87e9c (final S-B* label, C-b prints, 24+6 blocks); `render_cli` build/cli (Release). Noise: `python tools/ci/listening_pack.py --phase phase-07c-2b`; speech (local only, McGill TSP v2, never committed): `python tools/ci/abx_kit.py speech --scene <scene> --speaker MA --files MA01_01 MA01_02 --out build/abx-07c-2b/<s-w|s-b>`. Every build ran every item-6 assertion (early part bit-identical, the tail step, s_w ≤ 2.3 %, the AX47 mid-fade companions, HF-W with condition D), the M1 identity (`ir_assertions` at g = ±0.9, ±0.5, ±3), the cap check at m = 6, 7, 8, the peak bound, the M2 gap check, Q5 (speech) and the C-b tail-spread gate; all exit 0.

| manifest | chain | stimuli (blocks) | capped m=6/7/8 | peaks dBFS | s_w max | IR step at +0.9 (tail alone, dB) | HF-W worst | M2 gap ≥ tail T30 (s) | Q5 min margin dB | tail spread (1 kHz, dB) | label = decided |
|---|---|---|---|---|---|---|---|---|---|---|---|
| `build/listening-pack/phase-07c-2b/noise/layout4_s0.7__default/manifest.json` | noise | 66 ({'0.9': 30, '0.5': 30}) | {'6': [True, True], '7': [True, True], '8': [True, True]} | -7.8..-5.1 | 6.1e-07 | +0.9000 | 1.0002 (0.560 dB), skipped 0 | 1.835 ≥ 1.274 | — | own-onset -1.23, windows -0.21, -0.73; clause required False, present True | True |
| `build/listening-pack/phase-07c-2b/noise/layout4_s1__both_wall/manifest.json` | noise | 66 ({'0.9': 30, '0.5': 30}) | {'6': [True, True], '7': [True, True], '8': [True, True]} | -16.0..-12.9 | 4.1e-13 | +0.9000 | 1.0002 (0.560 dB), skipped 0 | 1.376 ≥ 1.313 | — | own-onset +9.39, windows -0.05, -0.03; clause required True, present True | True |
| `build/abx-07c-2b/s-b/speech/manifest.json` | speech | 66 ({'0.9': 30, '0.5': 30}) | {'6': [True, True], '7': [True, True], '8': [True, True]} | -21.7..-21.7 | 6.1e-07 | +0.9000 | 1.0002 (0.560 dB), skipped 0 | 1.831 ≥ 1.274 | 20.2 | own-onset -1.23, windows -0.21, -0.73; clause required False, present True | True |
| `build/abx-07c-2b/s-w/speech/manifest.json` | speech | 66 ({'0.9': 30, '0.5': 30}) | {'6': [True, True], '7': [True, True], '8': [True, True]} | -31.6..-30.1 | 4.1e-13 | +0.9000 | 1.0003 (0.559 dB), skipped 172 | 1.370 ≥ 1.313 | 20.1 | own-onset +9.39, windows -0.05, -0.03; clause required True, present True | True |

L4: `build/abx-07c-2b/l4/manifest.json` (builder files 18, 25; rebuilt after the last kit change, hashes reproducible). `pytest tools/ci`: 166 passed in 100.73s (0:01:40).

Values the run sheet §1 and the labels quote (heard T30 1.370 / 1.831 s; tail T30 1.313 / 1.274 and 1.254 / 1.274 s; tail spread +9.39 / −1.23 dB own-onset) match these manifests.
