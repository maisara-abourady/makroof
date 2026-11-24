# 39: Builder, the I7 speech-chain kit, the pair search on E and E's speech chain measured

Computation only. This file makes no decision. Nothing in `src/` or `tests/unit` was changed. No tolerance was
loosened and nothing was tuned (PRD NFR-8). The L4 chain and its anchor were not touched.

**Inputs:**
- decider file 25, rulings (i) and (ii);
- decider file 30, the kit spec: candidate set (a)(b)(c), the asserts and the prints;
- decider file 34, the pair search;
- interrogator files 36 and 37: the criteria are every pre-seal assertion of §1 and §3 item 3, on the scene in use;
- Seat 1 files 27, 29 and 32 (prints before the seal);
- builder file 12 (the kit's state on E).

**Kit commit:** `03502f4`. It changes only `tools/ci/abx_kit.py` and `tools/ci/test_abx_kit.py`. `listening_pack.py`
did not need a change.

## Result first
- **A pair qualifies on E: MA02_03 + MA02_04, the 6th pair tried.** Its earliest (a)(b) boundary is 2.901 s, already
  past the onset floor of 2.685 s, so (c) holds with no restriction. All 50 stimuli pass every pre-seal assertion.
  The fallback branch (MA01_01 + MA01_02, restricted) is therefore **not in force on E**, and no onset floor is
  pinned.
- **Pinned in `abx_kit.SPEECH_PAIR` and in `test_preregistered_numbers`:**
  - MA02_03, SHA-256 `4782a1658ec8438a88e2f6147d4682f586b359da157d6946f78ae19c2210cdc1`;
  - MA02_04, SHA-256 `5ed86159c54b5e7ee83789d5b410041fd23ba8a1d667edabc8dfc166b7e49cd2`.
  - `ITEM7_ONSET_FLOOR_PINNED == {}` is pinned too: no floor is pinned, because the fallback branch was not taken.
- **For the run sheet** (not edited here, since it is not in my edit list):
  - §3 item 2's blanks are MA02_03 and MA02_04.
  - The §1 sub-bullets that give MA01_01 + MA01_02's window describe the fallback pair, which is not used. The
    chosen pair's realised window is [0.057, 0.403]·T_heard, with 84 of 90 passing.
  - The fallback record wording does not apply on E.

## What changed in the kit
1. **Candidate set (decider files 30 and 34).**
   - `speech_layout` now returns:
     - `ab_boundaries`: the boundaries under (a) and (b);
     - `onset_floor` = lead + ⌈T·fs⌉, with T the construction T;
     - `boundaries`: the candidates, meaning the (a)(b) boundaries at or after the floor;
     - `item7_unrestricted`: whether the first (a)(b) boundary already meets (c);
     - `removed_by_item7`.
   - **Asserted:**
     - (a)(b) is not empty;
     - the candidate set is not empty;
     - the M3-G heard pause and the silence after the latest candidate are each ≥ T;
     - 2 s of programme after the latest candidate;
     - item 7 on the first candidate.
   - `q5_passing` asserts ≥ `Q5_MIN_PASSING` = 34.
   - `draw_speech_onset` uses replace-and-record over the candidate set and asserts item 7 on every drawn onset.
     `build_speech_chain` asserts it again over all stimuli.
   - `item7_branch`:
     - **Unrestricted:** nothing is pinned.
     - **Restricted:** allowed only for `ITEM7_FALLBACK_PAIR` = MA01_01 + MA01_02, and only on a scene with a floor in
       `ITEM7_ONSET_FLOOR_PINNED`. The floor is asserted equal to the pinned value, and the manifest carries
       `record_wording` = "speech onsets ≥ 0.134·T_heard on E (item 7); about 2 dB less mean tail exposure than an
       unrestricted draw.".
     - Any other restricted pair is refused.
   - For the pre-registered pair, the member SHA-256s are asserted against `SPEECH_PAIR`.
   - **Printed and recorded before the seal** (`manifest.tsp.q5_drawn_onset_margin`, `manifest.item7`):
     - the tail level above the floor at every drawn onset, with its minimum and median;
     - the realised window;
     - the passing count;
     - the replacement rate, expected and realised;
     - the onset floor;
     - the first (a)(b) boundary and the first candidate boundary.
2. **`speech --search-pairs`** (`search_speech_pairs`, `tsp_pairs`).
   - **Order:** adult pairs in TSP index order, consecutive within each group (01 + 02, 03 + 04, …), MA01 then
     MA02 and so on. MA01_01 + MA01_02, the fallback pair, is skipped. CA and CB are refused.
   - **Scene:** the scene in use (`--scene-name`), with the cached zip checksum-verified by `fetch_tsp`.
   - **Per pair, cheapest step first:**
     - (c) from the dry files;
     - then one floor render and one unstepped render for Q5 over the candidate set;
     - only a pair that meets (c) unrestricted and has ≥ 34 passing gets the full `build_speech_chain` (all 50
       stimuli, every pre-seal assertion).
   - It stops at the first pair that passes. It prints one row per pair and writes `search.json`.
3. **Ruling (i).** `HEARD_T30_LABEL` is now a dict:
   - `{"s=1": "...spanning the AX21 gap...", "s<1": "...spanning the early part..."}`;
   - `scene_class_s` gives "s=1" only when every face scatters 1 in every band;
   - the manifest prints `scene.scene_class_s`, `scene.T30_1k_s_label` and `m2_gap_check.heard_T30_label`;
   - `test_preregistered_numbers` pins both texts and the class of S-A, E, D and B.
4. **Tests.**
   - **Added:**
     - `test_speech_layout_item7_restriction_on_e_with_ma01_01`: floor 128902, first candidate 129024, 18 removed,
       0.134·T_heard; red for an empty candidate set.
     - `test_item7_branch`: red for a restricted non-fallback pair, a wrong pinned floor and no pinned floor.
     - `test_draw_speech_onset_item7_and_replacement`: **red for (c) on a drawn onset**.
     - `test_q5_passing_minimum`: **red at 33 passing**.
     - `test_tsp_pairs_order`.
   - **Updated:** `test_preregistered_numbers`, `test_m2_gap_check`, `test_speech_layout_e`, and the label assert in
     the noise end-to-end test.
   - **Replaced:** builder file 12's `test_speech_layout_item7_lead_on_e_with_ma01_01`. It expected the old blanket
     stop, which decider file 30 replaces with the restriction.

## Pairs tried on E (`layout5_s0.9/emitter_wall`, SHA-256 95d46224…a7a6)

Common values:
- onset floor 2.685 s (128902 samples = 4096 + ⌈2.600120·48000⌉);
- heard pause 3.701 s on every pair (≥ T 2.600 s);
- end of speech and boundaries in stimulus time.

For the pairs that fail (c), the Q5 columns are measured over the **restricted** candidate set (a)(b)(c). They are
for the record only; those pairs were not built.

| # | pair | SHA-256 (first 8) | end of speech (s) | earliest (a)(b) boundary (s) | (c) unrestricted | (a)(b) / candidates | Q5 passing | Q5 window (T_heard) | first-draw replaced p | silence after latest (s) | full build | result |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 1 | MA01_03 + MA01_04 | 6bf43bbc / 00a485ca | 1.845 | 1.995 | no | 90 / 25 | 25 | [0.329, 0.429] | 0.000 | 2.741 | not run | (c) fails |
| 2 | MA01_05 + MA01_06 | 370b98d7 / 90db1d4f | 2.285 | 2.443 | no | 89 / 66 | 48 | [0.157, 0.353] | 0.273 | 2.757 | not run | (c) fails |
| 3 | MA01_07 + MA01_08 | 8f3e36bd / 1136b702 | 2.295 | 2.453 | no | 89 / 67 | 67 | [0.153, 0.428] | 0.000 | 2.753 | not run | (c) fails |
| 4 | MA01_09 + MA01_10 | d4896e65 / ea54d7da | 1.925 | 2.069 | no | 90 / 32 | 32 | [0.298, 0.427] | 0.000 | 2.747 | not run | (c) fails |
| 5 | MA02_01 + MA02_02 | 86b50187 / 15729840 | 2.235 | 2.411 | no | 87 / 61 | 54 | [0.177, 0.398] | 0.115 | 2.783 | not run | (c) fails |
| 6 | **MA02_03 + MA02_04** | 4782a165 / 5ed86159 | 2.755 | **2.901** | **yes** | 90 / 90 | **84** | **[0.057, 0.403]** | 0.067 | 2.750 | 50 stimuli | **qualifies** |

Row 6's full build:
- peak −20.3 dBFS;
- form (b): 0 events;
- nulls: B −130.6 dB, E −130.4 dB;
- mid-fade windows ≥ 76;
- M1 error ≤ 8.8e−4 dB.

Notes on the table:
- The search stopped at pair 6. The dry (c) check alone, run for reference on all 30 MA pairs, finds only two that
  meet (c) unrestricted: MA02_03 + MA02_04 and MA03_09 + MA03_10.
- For reference, outside the search: MA01_01 + MA01_02 (the fallback pair) has its earliest (a)(b) boundary at
  2.496 s, which fails (c) (builder file 12).

Search log: `build/abx-07c-2b/speech-search.log`. Record: `build/abx-07c-2b/speech-search/search.json`.

## E's speech chain, MA02_03 + MA02_04, measured
Command: `python tools/ci/abx_kit.py speech --out build/abx-07c-2b --speaker MA --files MA02_03 MA02_04 --cache build/k7/tsp`.
It writes `build/abx-07c-2b/speech/` (log `build/abx-07c-2b/speech.log`).
- All 50 stimulus SHA-256s are identical to the search's full build of the same pair.
- Excerpt SHA-256: `f75c3f3834a84788a249f5e0e0e498e7e98caac100c5f162721c673d60c66566`.

| quantity | measured (50 stimuli) | asserted |
|---|---|---|
| capped at m = 6 / 7 / 8 | both emitters at all three | yes |
| heard-IR T30 / tail T30 L, R (1 kHz) | 2.560 s / 2.582, 2.600 s | — |
| heard-T30 label (ruling (i)) | "heard-IR T30, ISO fit spanning the early part, not a decay rate" (class s<1) | pinned |
| construction T (M3-G) | 2.600 s | T = max(heard, tails) |
| peak (item 10) | −22.7 to −20.3 dBFS | ≤ −1 dBFS |
| M1 per-band step error, max | 8.76e−4 dB (at −3 dB); 2.2e−4 dB at +0.9 dB | ≤ 0.05 dB |
| s_w broadband / worst band | 7.31e−7 / 5.24e−5 | ≤ 2.3 % |
| target specular share, max L / R | 0.022 / 0.001 | print |
| form (b): events in the step region; residual HP peak | 0 on every stimulus; ≤ −173.4 dBFS | 0 events |
| null B vs offline, worst | −130.6 dB | ≤ −120 dB |
| null E vs offline stepped IR, worst | −130.4 dB | ≤ −120 dB |
| mid-fade (W-a windows, companions (i)–(iii)) | 76 windows per stimulus, 0 skipped, worst window ratio 1.0 | yes |
| end of speech (stimulus time) | 2.755 s | — |
| pause (input) / heard pause | 3.729 s / 3.701 s | heard ≥ T |
| heard silence after the latest candidate / after each drawn onset, min | 2.750 s / 2.814 s | ≥ T and ≥ tail T30s (`m2_gap_check`: min 2.750 s) |
| item 7: onset floor; first (a)(b) boundary; first candidate | 2.6855 s; 2.9013 s; 2.9013 s (0 removed by (c)); programme before the first candidate 2.816 s | ≥ T, on every drawn onset |
| Q5 candidates / passing | 90 / 84, contiguous from the first | ≥ 34 |
| Q5 realised window | [0.057, 0.403]·T_heard (drawn onsets 2.901–3.787 s) | recorded |
| replacement rate | first draw replaced p 0.067; expected 0.071 per stimulus; realised 2 replaced in 50 (0.04 per stimulus) | recorded |
| tail above floor at the drawn onsets | min 20.4 dB, median 29.7 dB (floor −93.5 dB, 1 kHz) | ≥ 20 dB each |
| stimulus length | 12.814 s (all 50) | — |

The gap-cue print matches builder file 12's: for example, −20.14 dB at −0.9 dB, and the largest |ΔG| is at 500 Hz.

## K6 (file 32's typical-pace model, as in builder file 12)
The model: 5 plays + 8 s per trial, a 2 min break per block, f = 2 over 12 familiarisation files per chain, and
3 × 5 min rests.

| | noise stimulus | speech stimulus | full design (2 chains × 2 blocks) |
|---|---|---|---|
| E, MA02_03 + MA02_04 (this build) | 15.294 s | 12.814 s | **2.484 h** |
| E, MA01_01 + MA01_02 (builder file 12) | 15.294 s | 12.687 s | 2.475 h |
| difference | — | +0.127 s | +0.009 h |

- Two sittings split at a block boundary come to about 1.24 h each.
- AX49 L4's time is not included; it is counted under L4-T.

## Noise chain, for G16 (from `build/abx-07c-2b/noise/manifest.json`, the build of builder file 12)
- **s_w:** 7.31e−7 broadband and 5.24e−5 in the worst band, at every g. The assertion is ≤ 2.3 %.
- **No Q5 realised window.** Q5 applies only to the speech chain, and the noise chain has no `tsp.q5_*` fields.
- **Where the noise onset sits:**
  - N is the first partition boundary at or after the heard end of burst 2;
  - N − heard end runs from 141 to 1504 samples (over both emitters' delays);
  - the onsets lie at 4.757–5.067 s;
  - the heard silence after N is 2.603 s (≥ T).
- **Stale label.** That manifest predates ruling (i), so it still carries the old label "…spanning the AX21 gap…". A
  rebuild with this kit prints "…spanning the early part…". The audio is unaffected, because the label is print only.

## Tests
`. .venv/bin/activate && cmake --build --preset cli && RENDER_CLI=build/cli/render_cli SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci`
gave **204 passed in 168.63 s**:
- on the tree of commit `03502f4`;
- `render_cli` was up to date ("no work to do");
- log: `build/abx-07c-2b/pytest-39.log`.

**Run times** (4 cores):
- search about 7 min, most of it the full build of pair 6;
- speech build about 6 min.

## Files
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/tools/ci/test_abx_kit.py
- /home/user/makroof/build/abx-07c-2b/speech-search/search.json
- /home/user/makroof/build/abx-07c-2b/speech-search.log
- /home/user/makroof/build/abx-07c-2b/speech/manifest.json
- /home/user/makroof/build/abx-07c-2b/speech.log
- /home/user/makroof/build/abx-07c-2b/noise/manifest.json
