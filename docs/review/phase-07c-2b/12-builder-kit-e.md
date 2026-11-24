# 12: Builder, the ABX kit on scene E (M3-S, M3-G, M3-C), with E's chains measured

Computation only. This file makes no decision. Nothing in `src/` or `tests/unit` was changed or tuned (PRD NFR-8),
and no tolerance was loosened.

**Inputs:**
- decider file 8 (M3-S, M3-G, M3-C);
- interrogator file 11 ("Corrections to apply" 1–3);
- decider file 10, Part B (the ⚙ ITDG label line and the open item: B nulled on speech; relayed by the coordinator);
- decider file 5 (D-M3a, b, g);
- builder file 4 and its scratch `k7.py` (`make_scene`, `offline_conv`).

**Kit commit:** `67e151a` ("phase-07c-2b: put the ABX kit on scene E with the M3-G gaps and M3-C checks").

**Read this first:**
- **The speech chain stops on E at item 7.** The kit's speech build refuses E with TSP MA01_01: the earliest onset boundary is less than one T of programme after the file start (2.496 s against T = 2.600 s).
  - This is not caused by M3-G. The heard-T30 rule of the 07c-2 kit fails too (2.496 s < 2.560 s), and K7 recorded it on E as `pre_step_ok: false` without reporting it.
  - Every layout-5 fallback fails the same way (T ≥ 2.556 s).
  - As instructed, I recorded it and stopped that build.
  - So that the decider has the rest of the speech evidence, a **diagnostic** run changed only that one assertion into a record (details below). It is not a sealable build.
- **B on speech, nulled.** The open pre-seal item from decider file 10 Part B, B nulled within −120 dB on every speech stimulus, was measured in that diagnostic run: −130.3 dB on all 50 speech stimuli.
- **The noise chain on E passes every assertion,** on all 50 stimuli.

## What changed (all in `tools/ci/`)

**1. Scene registry (M3-S)** in `abx_kit.py`.

| scene | role |
|---|---|
| `layout5_s0.9/emitter_wall` (E) | **default** (`DEFAULT_SCENE`) |
| `layout5_s0.8/emitter_wall` (D) | fallback 1 (`FALLBACK_ORDER`) |
| `layout5_s0.8/default` (B) | fallback 2 |
| `layout4_s1/default` (S-A) | kept registered |

- `scene_layout5(s, placement)` builds layout 5 the way `k7.py`'s `make_scene` did. The JSON is byte-identical to K7's measured files, with the same SHA-256:
  - E `95d46224…a7a6`;
  - D `6724cf82…481e`;
  - B `6c730455…7f26`.
- E's JSON is committed at `tools/ci/abx_scenes/layout5_s0.9_emitter_wall.json`. `write_scene` refuses it if it differs from the builder's output. The manifest carries `scene_sha256` (the committed file's hash) and `scene_file`.
- `--scene-name` (noise and speech) selects a registered scene; the default is E.
- These all take the scene's own name and label, and no longer hard-code `layout4_s1/default`:
  - `check_scene`;
  - `prepare_scene` (new);
  - `build_chain`;
  - the noise and speech chains;
  - `listening_pack.py`'s phase-07c-2 README.
- The cap-failure message names the fallback order.

**2. Labels.**
- **E:** the `label` and detail lines are copied verbatim from M3-S. The ITDG line is replaced by decider file 10 Part B's line, which includes S0's floor image at 0.89 ms (file 11's correction 1). The Class line is "Class: tail-dominated (heard −9.5 dB, tail share 0.85), partial early part".
- **D and B:** Seat 9's file-7 text at s 0.8. "As above" is written out, and each carries Seat 9's ᾱ qualifier and the "Stimulus scene" line. These labels become live only on a fallback.
- **S-A:** gains "Kuttruff Table 5.2 case 4 (floor α 1, others 0): iteration 1.21 s against Eyring 1.38 s; the engine's tail follows Eyring." (M3-C 5).
- **D-M3e:** `require_class_line` refuses any scene without a "Class: " line, in `check_scene` and in `prepare_scene`, before anything is rendered.

**3. Gap rule (M3-G).**
- `check_scene` computes `construction_T_s` = max(heard-IR T30, every tail T30) at 1 kHz, and the heard delays.
- **Noise:** `noise_programme` is fed that T. Its construction (gaps ⌈(T·fs + Δ)/P⌉·P, N at the first partition boundary at or after the heard end, burst 3 at N + ⌈T·fs/P⌉·P) and its assertions are unchanged.
- **Speech:** the new `speech_layout` puts sentence 2 at the input end of sentence 1 + ⌈(0.43·T_heard + T)·fs⌉ + Δ.
  - Onsets lie at or after the heard end of sentence 1, and at most 0.43·T_heard after the end of speech (the Q5 ceiling is unchanged).
  - It asserts: heard pause ≥ T; heard silence after the latest boundary ≥ T; the item-7 lead ≥ T; and ≥ 2 s after.
  - The silence after the onset is also asserted on each drawn onset.
- **`gap_check`:** now asserts that the construction T equals max(heard, tails), replacing "the gaps use the heard T30". It also asserts that the minimum heard gap or silence is ≥ T and ≥ every tail T30.

**4. Prints and assertions (M3-C 6, 7).**
- **M1's per-band step identity** (`band_step_check`): every emitter and band at every g; |step_db − g| ≤ 0.05 dB is asserted, and the worst error is printed.
- **Nulls in `render_trial`, on every noise and speech stimulus:**
  - B against `render_cli`'s offline render (no `--realtime-emulation`) of the same programme;
  - E against `offline_reference`, which is `k7.py`'s `offline_conv`: the programme convolved with the stepped IR from `--abx-stepped-ir`.
  - Both are asserted ≤ −120 dB, the depths are printed, and the lengths must match.
- **Gap cue** (print only): the 1 kHz level of E − B relative to B over [N, N + 100 ms) and [N, N + 300 ms), plus the band of largest |ΔG| on the heard pair at that g.
- **`manifest.summary`:** worst nulls, maximum peak, maximum residual, maximum step error and stimulus durations.

**5. Tests** (`test_abx_kit.py`).
- **Updated:** `test_m2_gap_check`, with red cases for the heard-T rule on E and for K7's 2.574 s heard gap.
- **Added:**
  - `test_scene_registry`: committed JSON = builder; SHA pinned to K7's; labels; case-4 line.
  - `test_class_line_required` (red).
  - `test_band_step_check` (red at 0.06 dB).
  - `test_offline_reference_and_null`.
  - `test_speech_layout_e`.
  - `test_speech_layout_item7_lead_on_e_with_ma01_01`, which records the finding above.
  - An E case in `test_noise_programme_as_heard` (gap 126464, heard gap 125101, silence after N 124960 samples).
- **End to end:** the trial test now runs on E (one trial per block plus the familiarisation pairs: 8 stimuli, about 80 s). It asserts the label, Class line, committed SHA, caps, M3-G T > heard T30, the gap check, the step check, a specular share > 0, a 1 kHz tail share of 0.852, nulls ≤ −120 dB and the gap-cue fields.
  - The S-A identity ΔG = 10 log10(1 + share·(a² − 1)) is no longer asserted. It holds only when the scaled and unscaled parts are disjoint (S-A has no images), and on E the ISM fade-out overlaps the tail (a 4.9e−4 dB cross term at −0.9 dB).
  - S-A's 0.046 share is no longer checked end to end. `test_zero_step_is_bit_identical` still runs on S-A.
- All the existing red tests are kept.

**6. Listening pack.** The CI `phase-07c-2` pack now builds E. The README gives the scene name, SHA-256, Class line, heard and tail T30, T, and the null and step lines.

**Not edited: the run sheet.** Another session committed its rewrite while I worked (HEAD 9163325 includes it), with E's section and S-A's case-4 line. Two differences from the kit, for whoever owns it:
- **Heard-T30 label.** Run sheet L56 says the manifest labels the heard value "…ISO fit spanning the early part…". The kit's `HEARD_T30_LABEL` (pinned by `test_preregistered_numbers`; M3-G says "the heard-T30 label stays") is "…spanning the AX21 gap…".
- **E's early-part line.** The run sheet adds "Maisara decided on 2026-11-05 …". M3-S's text, which the kit carries, does not.
- The run sheet does not yet mention `--scene-name`.

## Tests

`. .venv/bin/activate && RENDER_CLI=<render_cli @ 9163325> SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci`
→ **184 passed in 124.94 s.** The tree holds commit 67e151a's kit; the binary is built from HEAD 9163325 and is identical to `build/cli/render_cli`.

Before HEAD moved, `test_abx_kit.py` passed 29/29 on the b9d1308 binary. Against an older binary, the other session's new `test_provisional_flag.py` fails, because it needs `--provisional-ir`.

## Builds

- Noise: `python tools/ci/abx_kit.py noise --out build/abx-07c-2b`, which writes `build/abx-07c-2b/noise/`.
  - Built with render_cli from b9d1308 (src = 90e4eda, built in a clean worktree; the shared binary held another session's uncommitted src edits at the time).
  - Rebuilt on 9163325: **all 50 stimulus SHA-256s and the summary are identical.**
- Speech: `python tools/ci/abx_kit.py speech --out build/abx-07c-2b --speaker MA --files MA01_01 MA01_02 --cache build/k7/tsp`.
  - **Stops:** `AssertionError: less than one T of programme before the earliest onset` (`build/abx-07c-2b/speech.log`).
- Diagnostic speech run: `build/abx-07c-2b-diag/speech/`, script `/tmp/claude-0/-home-user-makroof/af6ec831-18de-58d5-a237-0b9955c5e53f/scratchpad/speech_diag.py`. It is the kit's own `build_speech_chain`; the only change is that `speech_layout`'s item-7 assert becomes a record. **Not sealable.**

**Run time** (both builds ran in parallel on 4 cores):
- noise 7 min 38 s (7 min 21 s alone, on the 9163325 rebuild);
- speech diagnostic 6 min 0 s;
- the speech stop comes at about 8 s.

## Measured on E (`layout5_s0.9/emitter_wall`, SHA-256 95d46224…a7a6)

| quantity | noise chain (50 stimuli) | speech chain, diagnostic (50 stimuli) |
|---|---|---|
| capped at m = 6 / 7 / 8 | both emitters at all three | same |
| heard-IR T30 / tail T30 L, R (1 kHz) | 2.560 s / 2.582, 2.600 s | same |
| construction T (M3-G) | 2.600 s | 2.600 s |
| heard delays d, Δ | 1395 / 32 samples, Δ 1363 (28.4 ms) | same |
| peak (≤ −1 dBFS) | −8.1 to −4.3 dBFS | −26.7 to −24.0 dBFS |
| M1 per-band step error, max (≤ 0.05 dB) | 8.76e−4 dB (at −3 dB); 2.2e−4 dB at +0.9 dB | same IR checks |
| s_w, broadband / worst band (≤ 2.3 %) | 7.3e−7 / 5.2e−5 | same |
| target specular share, max (L / R) | 0.022 / 0.001 | same |
| form (b): events in step region; residual HP peak | 0; ≤ −149.3 dBFS | 0; ≤ −174.6 dBFS |
| null B vs offline (≤ −120 dB), worst | −130.9 dB | **−130.3 dB** (decider file 10's open item) |
| null E vs offline stepped IR, worst | −130.6 dB | −130.3 dB |
| gap / pause (input) | 126464 samples (2.635 s) | pause 179003 samples, 3.729 s |
| min heard gap; heard silence after N or onset | gaps 2.606 s; silence after N 2.603 s (≥ T) | heard pause 3.701 s; silence after onset ≥ 2.888 s (latest boundary 2.750 s) |
| N − heard end of burst 2, min | 141 samples | — |
| `m2_gap_check` | min 2.603 s ≥ T 2.600 ≥ tails: pass | min 2.750 s: pass |
| Q5 (speech) | — | 90 boundaries, 78 pass ≥ 20 dB (contiguous from the first); window **[0.059, 0.380] T30_heard**; first draw replaced p 0.133, 0.15 per stimulus; min margin 20.7 dB; floor −93.8 dB; end of speech 2.345 s |
| item 7: programme before the earliest onset ≥ T | pass (onset − burst 1 start ≥ T) | **FAIL**: earliest boundary 2.496 s < 2.600 s (also < 2.560 s heard); 9 of the 50 drawn onsets lie < T after the file start (7 < 2.560 s) |
| stimulus duration | blocks: mean 15.294 s (15.158–15.467); familiarisation: mean 15.286 s | 12.687 s (all) |

**Gap-cue print** (1 kHz level of E − B relative to B; range over stimuli). The largest |ΔG| on the heard pair is at 500 Hz at every g:

| g (dB) | noise [N, +100 ms) | noise [N, +300 ms) | speech [N, +100 / +300 ms) | max ΔG (500 Hz) |
|---|---|---|---|---|
| −3.0 | −10.72 to −10.63 | −10.70 to −10.66 | −10.69 / −10.69 | −2.489 dB |
| −0.9 | −20.19 to −20.07 | −20.16 to −20.11 | −20.14 / −20.14 | −0.776 dB |
| −0.5 | −25.06 to −24.98 | −25.05 to −25.01 | −25.05 / −25.05 | −0.434 dB |
| +0.5 | −24.55 to −24.50 | −24.55 to −24.53 | −24.55 / −24.55 | +0.440 dB |
| +0.9 | −19.27 to −19.19 | −19.25 to −19.22 | −19.24 / −19.24 | +0.797 dB |
| +3.0 | −7.71 to −7.65 | −7.70 to −7.67 | −7.69 / −7.69 | +2.719 dB |

These match 20 log10|10^(g/20) − 1| (for example −19.3 dB at +0.9), as the tail-only step implies.

**Notes:**
- **Speech hashes.** The diagnostic speech stimuli record the member SHA-256s (MA01_01 `f004f689…b815`, MA01_02 `9da6aadb…b03b`) and the excerpt SHA-256 `452e1a32…6f26`.
- **The Q5 window start differs from K7's.** K7 gave [0.013, 0.380]; the kit gives 0.059. The kit's first boundary is placed at or after the heard end of the sentence-1 **file** (TSP's trailing silence included: file end 2.380 s + max d). K7 measured from end of speech + max d. Both are inside the D-M3b rule. The kit's rule predates this change.

## K6 hours (file 32's typical-pace model: 5 plays + 8 s per trial, 2 min break per block, f = 2, 3 × 5 min rests; it reproduces S-A's 1.94 h)

| | noise stimulus | speech stimulus | full design (2 chains × 2 blocks) |
|---|---|---|---|
| E, this kit (M3-G pause) | 15.294 s | 12.687 s | **2.475 h** |
| E, K7 (pause ⌈T⌉ = 2.600 s, file 4) | 15.22 s | 11.56 s | 2.39 h (file 4); 2.399 h with this build's noise length |
| difference from the speech pause | — | +1.129 s against K7's pause; +1.169 s against ⌈T_heard⌉ = 2.560 s (interrogator file 11's "+1.17") | **+0.077 h** (file 10's "about +0.08 h") |

Two sittings at a block boundary come to about 1.24 h each. AX49 L4's time is not included.

## For the decider (no decision taken here)

**The item-7 failure on the speech chain.**
- With MA01_01, the programme before the earliest Q5 boundary is 2.496 s, counted from the file start including the 85 ms lead-in. That is short of one T on every layout-5 scene, whatever the gap rule.
- On S-A (T 2.009 s) it passes, at 2.475 s.
- The pre-seal check fails on E, D and B alike, so the M3-S fallback order does not resolve it.
- The kit asserts item 7 over the whole boundary window and stops. Nothing was changed to make it pass.
- The other speech evidence (nulls, form (b), mid-fade, Q5, M1, M3-G silences) is green in the diagnostic run.

**Files:**
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/tools/ci/test_abx_kit.py
- /home/user/makroof/tools/ci/listening_pack.py
- /home/user/makroof/tools/ci/abx_scenes/layout5_s0.9_emitter_wall.json
- /home/user/makroof/build/abx-07c-2b/{noise,noise.log,speech.log,speech_diag.log}
- /home/user/makroof/build/abx-07c-2b-diag/speech/manifest.json
- /home/user/makroof/build/abx-07c-2b-9163325/noise/manifest.json
