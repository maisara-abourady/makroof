# 43: Builder, the L4 anchor as A-ii and the assertion 7/4/2 prints (decider file 41, interrogator file 42)

Computation only; this file makes no decision. It implements decider file 41 (L4-A = A-ii; the readings of assertions
7, 4 and 2) with interrogator file 42's corrections, as run sheet §8 now states them. Only `tools/ci/abx_kit.py` and
`tools/ci/test_abx_kit.py` changed (`tools/ci/listening_pack.py` needed no change). Nothing in `src/` was touched and
nothing was tuned (NFR-8).

**Kit commit:** `3e8f643` ("phase-07c-2b: build the L4 anchor as A-ii (B vs B+3 dB, roles 3/3) and add the
assertion 7/4/2 prints"). `build/cli/render_cli` was rebuilt from HEAD (`ninja: no work to do`; SHA-256 `9566d510…1d89`,
the same as in builder file 26).

## What changed

| item | change |
|---|---|
| `l4_trial_plan` | Each block still has 6 anchors and 16 scored trials. Every anchor is B against B with the tail stepped +3 dB (`g_db` +3), and carries `role: stepped_as_A` (A = `anchor_up`, B = `B`) or `stepped_as_B` (A = `B`, B = `anchor_up`), 3 and 3. The role list is shuffled exactly as the old ±1 list was, so the generator's draws are the same. The **seeded positions are unchanged** (primary 2, 5, 11, 16, 20, 21; rerun 1, 4, 7, 12, 17, 18). Each old "up" maps to `stepped_as_A` and each "down" to `stepped_as_B`. X is still drawn at `seal` from each block's own key, which is unchanged. |
| `l4_anchor_feasibility` | Requests **+3 dB only**. It records E_target's specular share (0.8280 max) and the deepest buildable down step (−0.82 dB) as the reason for A-ii. On the +3 dB anchor IR it asserts M1's per-band step identity (`band_step_check`, 0.05 dB) and s_w ≤ 2.3 % (`ir_assertions`, plus an explicit assert). Both are printed. |
| `L4_STIMULUS_SPECS` | A (provisional), B, and `anchor_up` (+3 dB). There is no negative step. |
| `build_l4` | No longer stops. It asserts the anchor stimulus' peak ≤ −3 dBFS and records it with the anchor checks. Familiarisation is the labelled A/B pair plus the labelled anchor pair (`pair_01_A_provisional`, `pair_01_B_exact`, `pair_02_anchor_tail_+3dB`, `pair_02_B_exact`). The manifest's anchor line and pre-registration cite decider file 41 and interrogator file 42. |
| Assertion 2 (renders) | Bit-identical before the partition boundary at or below the chord-aligned fade start (all channels). Over [boundary, fade start), max \|A − B\| ≤ −120 dB re B's peak, per sample, is asserted and labelled "Seat 3's per-sample criterion at Phase 06's −120 dB level". The first differing sample is printed. |
| Assertion 4 | Unchanged (0.05 dB). It now prints "consistency check; weak on this scene (all predicted \|A/B\| < 0.01 dB); red test: a 1.2 dB hot provisional fails it", with max \|predicted\| and max \|error\|. |
| Assertion 7 | Still asserted on the model. The realised drop is renamed `realised_schroeder_drop_db` and printed as "realised Schroeder drop [t_mix,e,max, L_f), one realisation, not asserted", per band. |
| Tests | `test_l4_build_stops_at_the_down_anchor` is replaced by `test_l4_down_step_refused_on_scene`. It checks that render_cli exits 1 with "negative diffuse energy" for −3 dB on the L4 scene, that +3 dB builds with a share between 0.80 and 0.85, that `L4_STIMULUS_SPECS` steps are exactly [+3], and that every anchor in both plans has g +3. The new `test_l4_build_end_to_end` runs `build_l4` to completion (8 trials per block, covering both roles). It spies on every render_cli call and asserts that no `--abx-step-db` is negative. It also asserts the anchor IR checks, the render null, the two print labels, the familiarisation set, and that each trial folder holds the planned files. `test_l4_trial_plan` checks the roles 3/3 and pins the anchor positions against an independent copy of the pre-A-ii draws. The seal test drops `anchor_down`. The red tests (`test_l4_ir_checks_red[tail_gain, late_A]`, `test_l4_class_line_required`, `test_l4_scoring_anchor_first_and_refusals`) are kept unchanged. |

**Tests.** `. .venv/bin/activate && cmake --build --preset cli && RENDER_CLI=build/cli/render_cli
SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci` gave **205 passed in 194.3 s** on the tree committed as `3e8f643`.
The count was 204 at `03502f4`: one test was replaced and one added.

## Measured: the full L4 pack (`build/abx-07c-2b/l4`, primary + rerun, linux x86_64, 48 kHz)

Built in 37 s. Every stimulus was rendered twice and was bit-identical. `l4-verify` gave "hashes match: the sealed L4
stimuli stand" (A, B and platform match).

| quantity | value |
|---|---|
| manifest SHA-256 | `15266ae5d7436dfd12de8d72a6d775b7c28cbac8a7718f80255a911cceb786d7` |
| scene SHA-256 | `ac1427e4708884ca2ca5402b1b196e9d9d8d14fb9fe1edda7fe35d740af14c5d` (k 0.84, tailSeed 106) |
| IR hashes (P8 item 4) | A `bdef1bfb…d7179e`, B `5d283ed8…6f49` (as in file 26) |
| stimuli SHA-256 | A `27d88ec3…be5fe`, B `dfb7998d…29a6`, anchor +3 dB `ab218b5c…ad6b` |
| stimulus length | 16.587 s (all three) |
| timing | T60_max 7.9955 s (63 Hz), t_mix,e,max 0.08017 s, L_f 2.5748 s, L_p 2.6748 s, L 11.9933 s |
| Class line | "Class: long-decay, tail-dominated (heard D/R -10.4 dB), cut -21.7 dB in the T60_max band" |
| anchor positions / roles | primary: 2 B, 5 B, 11 A, 16 A, 20 A, 21 B; rerun: 1 A, 4 A, 7 A, 12 B, 17 B, 18 B (A = `stepped_as_A`, B = `stepped_as_B`) |

**Anchor IR checks (+3 dB; decider file 41, Seat 3's condition)**

| check | value | bound | result |
|---|---|---|---|
| M1 per-band step identity, worst \|step − 3\| over [t_mix,e, L) | 0.0270 dB (emitter 0, 8 kHz) | ≤ 0.05 dB | pass |
| s_w (window unscaled share, worst emitter/output) | 0.575 % (5.75e−3) | ≤ 2.3 % | pass |
| anchor stimulus peak | −9.93 dBFS | ≤ −3 dBFS | pass |
| tail-alone step (all 4 channels) | +3.0000 dB | 0.01 dB (`ir_assertions`) | pass |
| E_target specular share (max) / deepest down step | 0.8280 / −0.82 dB | (record, why A-ii) | — |

Per-band step error (dB), emitter 0: −0.024, −0.007, −0.006, −0.002, −0.010, −0.004, −0.012, −0.027. Emitter 1:
−0.007, −0.012, +0.001, +0.001, −0.012, −0.003, −0.013, −0.022 (63 Hz … 8 kHz).

**Assertions 1–13** (all asserted items pass; values as in builder file 26 unless stated)

| # | value |
|---|---|
| 1 | flag note in render_cli output, timing JSON and manifest |
| 2 | IRs: first differing tap 3007 = earliest tail fade start 3007. Renders: bit-identical before 6656 (asserted); over [6656, 7103) max \|A − B\| **−144.8 dB re B's peak** (≤ −120, "Seat 3's per-sample criterion at Phase 06's −120 dB level"); first differing sample **6658** |
| 3 | prefix worst −61.1 dB (≤ −18.27) |
| 4 | max \|measured − predicted\| 0.0031 dB (≤ 0.05); max \|predicted\| 0.0079 dB. Print: "consistency check; weak on this scene (all predicted \|A/B\| < 0.01 dB); red test: a 1.2 dB hot provisional fails it" |
| 5 | A's last nonzero tap 127666 < L_p tap 127667; in the stimulus, 2.6695 s after the release end |
| 6 | B 574956 taps = L tap |
| 7 | model (asserted ≥ 18.7): 18.72, 18.99, 19.74, 20.95, 22.61, 30.90, 51.69, 120.34 dB |
| 7 print | "realised Schroeder drop [t_mix,e,max, L_f), one realisation, not asserted": **18.47**, 18.82, 20.14, 21.06, 22.61, 30.83, 49.17, 76.36 dB |
| 8 | B's share past L_f, heard max 0.01169 (≤ 0.0134) |
| 9 | held-part A/B (dB): −0.112, +0.060, +0.023, +0.068, −0.007, −0.001, +0.000, −0.000 |
| 10 | silence after the release 12.494 s |
| 11 | peaks A −11.71, B −11.70, anchor −9.93 dBFS |
| 12 | two builds identical (4 IR builds, each stimulus rendered twice) |
| 13 | ghost print unchanged from file 26 (63 Hz: −22.3 / −30.3 / −37.4 / −60.4 dB at +0/1/2/5 s) |

## The three manifests (E's two chains, current kit)

| pack | manifest SHA-256 | key values |
|---|---|---|
| L4 `build/abx-07c-2b/l4/manifest.json` | `15266ae5…86d7` | above |
| noise `build/abx-07c-2b/noise/noise/manifest.json` (rebuilt) | `ec281533a35b00746b06b55e96669c582caa0f9cc05a933fdd98ac1aed279cab` | scene layout5_s0.9/emitter_wall, class s<1, T30(1 kHz) 2.560 s labelled **"heard-IR T30, ISO fit spanning the early part, not a decay rate"** (ruling (i)); construction T 2.600 s; minimum heard gap 2.603 s; 50 stimuli; peak max −4.33 dBFS; nulls B −130.9 / E −130.6 dB; per-band step error max 8.8e−4 dB; s_w 7.31e−7 (worst band 5.24e−5); stimulus mean 15.294 s |
| speech `build/abx-07c-2b/speech/manifest.json` (rebuilt) | `5ae271d5222c4f4628d9c3c7ac699b0ee1ca34a55e838f5572327de33539fc5b` | MA02_03 + MA02_04, branch "unrestricted"; same s<1 label; end of speech 2.755 s; pause 3.729 s (heard 3.701 s); Q5: 84 of 90 boundaries pass, window [0.057, 0.403] T30, min drawn margin 20.4 dB; 50 stimuli; peak max −20.30 dBFS; nulls B −130.6 / E −130.4 dB; stimulus 12.814 s |

**(c) The speech chain.** The kit changes in `3e8f643` touch only the L4 section. Even so, the speech chain was rebuilt
with the final kit (`abx_kit.py speech --out build/abx-07c-2b --speaker MA --files MA02_03 MA02_04 --cache build/k7/tsp`).
All 100 WAVs are **byte-identical** to builder file 39's build. The manifest's SHA-256 changed (39's was `40233d80…2ddc`),
but only in two kinds of field:
- the `render_cli` path string;
- `excerpt_sha256`.

**Finding (not fixed; outside this task).** `excerpt_sha256` is not reproducible. It hashes an in-memory WAV written
by `soundfile`, and libsndfile writes a PEAK chunk with a timestamp into float WAVs. This was checked: two writes of the
same samples one second apart hash differently. The audio and the member SHA-256s are unaffected. The fix would be to
hash the float32 samples, not the WAV bytes, or to write without the PEAK chunk. I left it for the orchestrator to
assign.

**(d) Listening packs.**
- `python tools/ci/listening_pack.py --phase phase-07c-2b` writes `build/listening-pack/phase-07c-2b/`:
  - `L4_handover_demo_unscored.wav` (`34f8458e…e213`): release 4.083 s, handover 7.765 s (t_r + 3.682 s), peak −11.7 dBFS;
  - `README.txt` (`bd9d93f5…edd7`).
- The AX47 noise chain is registered under `phase-07c-2`. `--phase phase-07c-2` writes `build/listening-pack/phase-07c-2/`:
  - `README.txt` (`46b4fa80…d2aa`);
  - `noise/` (manifest, scene JSON, 0.9dB/, 0.5dB/, familiarisation/).
  - Its manifest SHA-256 is `ec281533…9cab`, identical to the kit's noise build, and all 100 WAVs are identical.

## K6 (file 32's pace model)

**L4, the final familiarisation set.** 4 labelled files: A/B plus anchor/B. That is 3 distinct files, one fewer than the
4 distinct files of file 26's A/B, +3/B, −3/B. File 26 counted 6 labelled plays. The stimulus is 16.587 s, and 22
trials per block.

| pace | block | familiarisation | primary | **primary + rerun (worst case)** |
|---|---|---|---|---|
| brisk (3 plays, 5 s, f 1) | 22.1 min | 1.1 min | 23.2 min | **45.3 min** |
| typical (5 plays, 8 s, f 2) | 35.3 min | 2.2 min | 37.6 min | **72.9 min** |
| slow (8 plays, 10 s, f 3) | 54.3 min | 3.3 min | 57.6 min | **112.0 min** |

The audio floor is 18.2 min per block. L4's own third sitting, worst case, stays inside 2 h at every pace (slow
112.0 min, about 8 min to spare). The equivalent figures in file 26 were 74.0 and 113.6 min.

**E's two chains, this build.** Each chain has 2 blocks of 22 trials. Familiarisation is f plays of 12 files (6 pairs).
There is a 2 min break per block and 3 × 5 min rests. The noise stimulus is 15.294 s (familiarisation mean 15.286 s);
the speech stimulus is 12.814 s.

| pace | noise block / fam | speech block / fam | full design | each of the two sittings |
|---|---|---|---|---|
| brisk | 20.7 / 3.1 min | 17.9 / 2.6 min | 97.8 min (1.630 h) | 48.9 min |
| typical | 33.0 / 6.1 min | 28.4 / 5.1 min | **149.0 min (2.484 h)** | **74.5 min** |
| slow | 50.5 / 9.2 min | 43.3 / 7.7 min | 219.4 min (3.657 h) | 109.7 min |

At the typical pace this reproduces file 39's 2.484 h. E's sitting 2 plus L4's primary and rerun would come to
74.5 + 72.9 = 147.4 min, still over 2 h. So the third dated sitting (file 38 (5)) stands on these numbers.

## Files
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/tools/ci/test_abx_kit.py
- /home/user/makroof/build/abx-07c-2b/l4/manifest.json
- /home/user/makroof/build/abx-07c-2b/noise/noise/manifest.json
- /home/user/makroof/build/abx-07c-2b/speech/manifest.json
- /home/user/makroof/build/listening-pack/phase-07c-2b/
- /home/user/makroof/build/listening-pack/phase-07c-2/
