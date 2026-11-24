# 26: Builder, the AX49 L4 chain in the ABX kit (run sheet §8): implementation and measurements

Computation only; this file makes no decision. Nothing in `src/`, `tests/unit` or `docs/` (other than this file) was
changed, and nothing was tuned (NFR-8). The AX47 chains behave as before.

**Kit commit:** `ddca7b4` ("phase-07c-2b: add the AX49 L4 chain to the ABX kit (stops at the -3 dB anchor)").
`build/cli/render_cli` was rebuilt from HEAD (`ninja: no work to do`).

## Read this first: the spec cannot be built as written, and the kit stops

**The −3 dB anchor cannot be built on the L4 scene.** L4-D defines the anchor as "B against B with the tail stepped
±3 dB (`--abx-step-db ±3 --abx-step-sample 0`), on the L4 scene and chord".

- `--abx-step-db g` scales only the diffuse part of E_target. A step down by g dB therefore needs E_target's specular
  share to be at most 10^(g/10) in every band of every emitter.
- On the L4 scene (s 0.1) render_cli prints a specular share of **0.827–0.828 in every band of both emitters**.
  - A −3 dB step needs ≤ 0.501.
  - The deepest step render_cli can make here is 10·log10(0.828) = **−0.82 dB**.
  - `render_cli ... --abx-step-db -3` exits 1 with "would need a negative diffuse energy (specular share too high)".
- The +3 dB step builds without trouble.

So the 3-down half of the anchor ("3 up, 3 down") is impossible on this scene with the named flag.

**What the kit does about it.**
- `l4_anchor_feasibility` checks this before any stimulus is rendered, and `build_l4` stops with that message.
- Nothing was substituted. Two possible substitutes were not built, because each would change the pre-registered
  anchor and that is for the decider:
  - a "down" trial presented as B against B+3 dB;
  - a broadband tail gain outside `--abx-step-db`.
- `tools/ci/test_abx_kit.py::test_l4_build_stops_at_the_down_anchor` records the finding as a red-documented stop.
  `test_speech_layout_item7_lead_on_e_with_ma01_01` is the precedent for this.

**How the numbers below were measured.** So that the decider has the remaining evidence, a **diagnostic** run
changed only that one point. It is not sealable.
- The script is in the session scratchpad, not committed.
- It runs `build_l4` unchanged except that it leaves out the −3 dB anchor stimulus, its trials and its
  familiarisation pair.
- Every number below comes from that run, at `build/abx-07c-2b/l4-diagnostic/manifest.json`.
- **Every other assertion (1–13) passes.**

## What changed (all in `tools/ci/` and CI)

| file | change |
|---|---|
| `tools/ci/abx_scenes/stone_box_l4.json` | L4-S scene: `stone_box.json` with every band's α × 0.84 (s 0.1, tailSeed 106). SHA-256 `ac1427e4708884ca2ca5402b1b196e9d9d8d14fb9fe1edda7fe35d740af14c5d`. It equals the builder `scene_stone_box_l4()` (asserted at build) and `test_provisional_flag.l4_scene()` (test). |
| `tools/ci/abx_kit.py` | The L4 section:<br>• constants (16 + 6 trials, ≥ 12/16, α 2517/65536 = 0.038, power 0.63, −18.27 dB, 0.05 dB, 18.7 dB, 0.0134, AX49 f, fade, normalisation and L rule);<br>• `L4_SCENE` with the label and templated detail lines plus the Class line (Seat 9's D/R bands);<br>• `engine_band_firs` (a numpy copy of `sim::ism::OctaveFilterbank`, maxHalf 7849 at 48 kHz, h = 2·maxHalf, as `test_interim.cpp` uses);<br>• `l4_chord` (version 1);<br>• `l4_ir_checks` (assertions 2–8 and 13 on the IRs);<br>• `l4_anchor_feasibility`;<br>• `l4_trial_plan` (each block has its own seed);<br>• `l4_ir_hashes` and `l4_verify` (P8 item 4);<br>• `build_l4`;<br>• `l4_handover_demo`;<br>• scoring: `l4_score_anchor`, `l4_unseal_scored` (refuses after a failed anchor), `score_l4`, `l4_wording`, `read_l4_responses`;<br>• `seal` and `verify_session` take the L4 pack: `<block>/trial_NN`, one key per block (`block_seeds`), both blocks sealed together. AX47 paths are unchanged (`trial_rel`).<br>CLI: `l4 --out build/abx-07c-2b/l4`, `l4-verify --pack`; `seal`, `score --chain l4` and `blank --chain l4`. |
| `tools/ci/listening_pack.py` | `phase-07c-2b`: `L4_handover_demo_unscored.wav` plus a README index line titled "L4 handover demo (unscored; interim then handover, as at project load)". |
| `.github/workflows/ci.yml` | A Linux step builds the phase-07c-2b pack (the demo) into the `listening-pack` artifact. |
| `tools/ci/test_abx_kit.py` | 16 L4 tests (listed under Tests). |

**Design notes:**
- **A and B static.** Each is rendered with `--realtime-emulation --block 512 --partition 512`, A with
  `--provisional-ir`. The anchors are B with `--abx-step-db ±3 --abx-step-sample 0`.
- **Two builds.** Every stimulus is rendered twice and compared byte for byte (12). Both IRs are built twice with the
  P8 commands.
- **Same length.** The renders are cut to the input length after asserting that everything past it is exactly zero,
  so the whole exact decay fits and A and B are the same length.
- **Trial folders.** These are hard links to the four stimulus files. `seal` copies them into the session folder.
- **Manifest (P8-3).** For every stimulus it prints f 0.312, fade 0.1 s, the normalisation text and the L rule.
  These are checked against `--provisional-timing` at every build: (L_f − t_mix,e,max)/T60_max = 0.312,
  L_p − L_f = 0.1 s and L = min(1.5·T60_max, 12 s), each to 1e-9. A change to any of them stops the build.
- **Manifest (P8 item 4).** It records the SHA-256 of A's IR (`--provisional-ir --ir`) and B's IR (`--ir`), the
  platform and the render_cli SHA-256. `l4-verify` rebuilds both IRs, compares them, prints VOID on any mismatch
  (platform included) and exits 1.

## Measured (diagnostic run, k = 0.84, linux x86_64, 48 kHz)

**Timing and scene (L4-S)**

| quantity | value |
|---|---|
| provisional; L_p < L | true; 2.6748 < 11.9933 s |
| T60 per band, 63 Hz … 8 kHz (s) | 7.9955, 7.8811, 7.5837, 7.1441, 6.6201, 4.8436, 2.8955, 1.2438; T60_max in 63 Hz |
| t_mix,e,max, L_f, L_p, L | 0.08017 s, 2.5748 s, 2.6748 s, 11.9933 s |
| D/R at 1 kHz | per emitter −12.8 / −12.9 dB; heard (L + R) −10.4 dB → Seat 9 class **tail-dominated** |
| diffuse comparison | −14.0 dB at r/r_c 5.00 (r 5.39 m, r_c 1.08 m, Sabine A 58.4 m² from the 1 kHz T60) |
| ᾱ at 1 kHz | surfaces 0.042, inside 0.04–0.07 (asserted); A/S with air 0.052 |
| Class line | "Class: long-decay, tail-dominated (heard D/R -10.4 dB), cut -21.7 dB in the T60_max band" |

**Cut depth and chord band energy (label line 5)**

| band (Hz) | 63 | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|---|
| cut depth on B's heard IR, 10·log10(E[L_f,L)/E[0,L)) (dB) | **−21.7** | −19.3 | −21.1 | −22.1 | −24.0 | −32.8 | −52.4 | −82.5 |
| chord band energy, dB re its total | −13.8 | −10.4 | −9.6 | −7.8 | −8.3 | −7.7 | −7.3 | −10.6 |

The non-detection wording would read "covers a cut ≥ 21.7 dB below the full-IR energy in the T60_max band at
T60_max 8 s".

**Assertions**

| # | value | result |
|---|---|---|
| 1 | "provisional tail, validation-only flag" printed by render_cli, in the timing JSON and in the manifest | pass |
| 2 | IRs: first differing tap 3007 on all 4 channels = the earliest tail fade start (3007) | pass |
| 2 | renders: first differing sample 6658; chord onset 4096 + 3007 = 7103; the partition boundary below it is 6656 | see note 1 |
| 3 | prefix worst −61.1 dB (emitter 1, 63 Hz), against ≤ −18.27; window taps [3126, 107169), h 15698 | pass |
| 4 | worst \|measured − predicted\| **0.0031 dB** (tolerance 0.05); window [t_mix,e,max + 2.5 ms, L_f) | see note 2 |
| 5 | A's IR is 127667 taps, the last nonzero tap is 127666, and the L_p tap is 127667. In the stimulus, A's last nonzero sample is 2.6695 s after the release end | pass |
| 6 | B's IR is 574956 taps, which equals the L tap (11.99329 s of emission time against L 11.99328 s) | pass |
| 7 | the model decay 60·(L_f − t_mix,e,max)/T60_b is 18.72 dB (63 Hz) to 120.3 dB (8 kHz), all ≥ 18.7 | see note 3 |
| 8 | B's share past L_f: max 0.01240 (emitter 0, 125 Hz); heard IR max 0.01169 (125 Hz) | pass |
| 9 | print only: held part A/B (dB) per band, 63 Hz to 8 kHz: −0.112, +0.060, +0.023, +0.068, −0.007, −0.001, +0.000, −0.000 | print |
| 10 | silence after the release: 12.494 s (≥ L + 0.5 s) | pass |
| 11 | peaks: A −11.71, B −11.70, anchor +3 dB −9.93 dBFS (≤ −3) | pass |
| 12 | two builds bit-identical (4 IR builds, every stimulus rendered twice) | pass |
| 13 | ghost print (see below) | print |

**Note 1 (assertion 2 on the renders).** On the IRs, A and B agree bit for bit up to the earliest tail fade start,
exactly. In the partitioned convolution, the output block that contains the fade start mixes whole partitions, so
the renders can differ (by rounding) from the partition boundary at or below it. The kit asserts bit-identity of the
renders before that boundary (6656). They agree up to 6658.

**Note 2 (assertion 4, how the prediction is formed).** The prediction is AX47 (b)'s step:
- A/B = +10·log10(1 + (1 − f_b)·δ_b), which equals 10·log10(f_b/ρ_b). The provisional-to-exact step is its negative.
- f_b is AX49's formula.
- ρ_b is B's realised share of its decay over [0, L_f), measured on B's band-split IR:
  - over the window [t_mix,e,max + 2.5 ms, L_f), and over [L_f, end);
  - with [0, t_mix,e,max + 2.5 ms), which the early part hides, taken at the model's share of the window.
- Both A/B and B are gated and then split with the engine's filterbank.

| emitter | quantity | 63 Hz | 125 Hz | 250 Hz | 500 Hz | 1 kHz |
|---|---|---|---|---|---|---|
| 0 | measured (dB) | +0.0029 | +0.0044 | +0.0038 | +0.0005 | −0.0003 |
| 0 | predicted (dB) | +0.0060 | +0.0030 | +0.0028 | +0.0008 | −0.0005 |
| 0 | δ | 0.118 | 0.063 | 0.070 | 0.027 | −0.026 |
| 1 | measured (dB) | −0.0077 | +0.0027 | +0.0008 | −0.0014 | +0.0022 |
| 1 | predicted (dB) | −0.0079 | +0.0018 | +0.0009 | −0.0022 | +0.0014 |
| 1 | δ | −0.155 | 0.038 | 0.022 | −0.075 | 0.071 |

At 2–8 kHz, both values are 0.0000–0.0001 dB.

All the predicted steps are below 0.01 dB. The 0.05 dB tolerance therefore holds even with a prediction of 0 dB, so
this assertion is weak on this scene. That is reported, not changed.

**Note 3 (assertion 7, the realised drop at 63 Hz).** The kit asserts the decay as AX49 defines it, from the T60s the
tail is built with: 18.72 dB at 63 Hz (= 60 × 0.312). It also prints the realised Schroeder drop on B's heard IR
over [t_mix,e,max, L_f).

| band (Hz) | 63 | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|---|
| realised drop (dB) | **18.47** | 18.82 | 20.14 | 21.06 | 22.61 | 30.83 | 49.17 | 76.36 |

The realised value at 63 Hz is **below 18.7 dB**. Under the model reading the assertion passes; under a realised
reading it would fail at 63 Hz. Which reading item 7 means is for the decider. The kit takes AX49's construction
statement, as `tests/unit` does.

**Ghost print (13, print only)**

Labelled "noise-excitation (Schroeder) estimate". B's heard IR, dB re steady state, at release + L_p + dt:

| band (Hz) | +0 s | +1 s | +2 s | +5 s |
|---|---|---|---|---|
| 63 | −22.3 | −30.3 | −37.4 | −60.4 |
| 125 | −20.0 | −28.3 | −35.7 | −58.1 |
| 250 | −22.2 | −30.0 | −37.4 | −61.9 |
| 500 | −23.0 | −31.4 | −40.0 | −65.1 |
| 1k | −25.0 | −34.3 | −43.3 | −70.3 |
| 2k | −34.4 | −46.2 | −57.8 | −91.2 |
| 4k | −54.2 | −69.0 | −82.2 | −119.9 |
| 8k | −84.9 | −105.1 | −125.7 | −163.0 |

**IR hashes (P8 item 4, linux x86_64; render_cli SHA-256 `9566d510…1d89`)**
- A (`--provisional-ir --ir`): `bdef1bfbbc8189252a85238e8ffa6e14858a2815fa715d6f769cf66ce2d7179e`
- B (`--ir`): `5d283ed88b771ad0d82bc4899017b0385454f9d4637f38f65fba9aa73efd6f49`

**Chord (version 1).**
- Notes: MIDI 36, 43, 48, 52, 55, 60 (A4 440 Hz).
- 382 partials; the highest is 7979.6 Hz. Each partial is n^−½ against its fundamental (−3 dB/oct).
- Phases come from seed 4049.
- Envelope: a 50 ms raised-cosine onset and a 10 ms raised-cosine release.
- Level: a fixed dry peak of −12 dBFS. This is the kit's one recorded gain, chosen once for playback headroom; it is
  not a check.
- Lead-in 4096 samples. Hold H = max(L_p, 0.5·T60_max) = 3.998 s.

**Run time and lengths.**
- Each stimulus is **16.587 s** (A = B = anchors; input 796160 samples).
- The diagnostic build took **37–40 s** (Linux, 4 cores), every render done twice. The kit stops after about 12 s at
  the anchor check.
- The handover demo takes 8 s:
  - release at 4.083 s;
  - handover at 7.765 s, which is t_r + 3.682 s against t_r + L_p + 1 s = t_r + 3.675 s, rounded up to the next
    partition;
  - peak −11.7 dBFS; 28.56 s long.

## K6 on the L4 stimuli (L4-T; file 32's pace model)

The model, as in file 32:
- a trial costs plays × 16.587 s + overhead;
- a 2 min break per block;
- familiarisation is f plays of the 6 labelled files (A/B, +3 dB/B, −3 dB/B).

Audio floor (every file heard once, no overhead): **18.2 min per block**, 36.5 min for primary + rerun.

| pace | block | familiarisation | primary | **primary + rerun (worst case)** |
|---|---|---|---|---|
| brisk (3 plays, 5 s, f 1) | 22.1 min | 1.7 min | 23.7 min | **45.8 min** |
| typical (5 plays, 8 s, f 2) | 35.3 min | 3.3 min | 38.6 min | **74.0 min** |
| slow (8 plays, 10 s, f 3) | 54.3 min | 5.0 min | 59.3 min | **113.6 min** |

**Against E's second sitting.** File 12 puts each of E's two sittings at about 1.24 h (74 min) at the typical pace.
- E's sitting 2 + L4 primary + L4 rerun = 74 + 74 = **148 min (2.47 h)**. That is over 2 h, so under the D1
  worst-case rule (decider file 21) L4 needs a **third dated sitting**.
- With the primary block alone, sitting 2 would be about 113 min.
- This is computation only. The sitting decision belongs in the brief.

## Tests

The L4 tests in `tools/ci/test_abx_kit.py` (render_cli required: the last five):

| test | checks |
|---|---|
| `test_l4_preregistered_numbers` | the pre-registered numbers |
| `test_l4_scene_committed` | the committed JSON and its SHA-256, equal to the builder and to `test_provisional_flag.l4_scene()`; the label |
| `test_l4_class_line_required` | **red**: the L4 scene without its Class line is refused before rendering; an unfilled field is refused |
| `test_dr_class` | Seat 9's D/R class bands |
| `test_engine_band_firs` | the filterbank copy is complementary; maxHalf 7849 |
| `test_l4_chord` | the chord |
| `test_l4_trial_plan` | both blocks' structure; their anchor positions differ |
| `test_l4_wording` | P1's exact wording |
| `test_l4_scoring_anchor_first_and_refusals` | **red**: a failed anchor voids its block and `l4_unseal_scored` refuses; the rerun is scored; a second failure reads "inconclusive (anchor failed twice)"; a passed anchor refuses the rerun; a missing anchor answer is an error |
| `test_l4_blank_and_responses` | the blank response sheet and reading the responses |
| `test_l4_seal_two_blocks_together` | both blocks sealed with one key and their own seeds; the session verified |
| `test_l4_ir_checks_on_the_scene` | on the real IRs: provisional, L_p < L, T60_max 8 ± 0.1 s, the IR hashes reproduce (determinism), assertions 2–8 and 13 |
| `test_l4_ir_checks_red[tail_gain, late_A]` | **red**: a 1.2 dB hot provisional tail fails 3; A nonzero past L_p fails 5 |
| `test_l4_build_stops_at_the_down_anchor` | the finding above |
| `test_l4_handover_demo_unscored` | the pack holds only the demo and the index, both with "unscored"; the handover sample rule; bit-identical run to run |

A small end-to-end L4 trial cannot complete while the anchor is impossible. The end-to-end test asserts the stop, and
the IR-level and scoring paths are tested separately.

`. .venv/bin/activate && RENDER_CLI=build/cli/render_cli SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci` on
`ddca7b4`: **200 passed** (161 s).

## For the decider (no decision taken here)

1. **The −3 dB anchor (blocking).** L4-D's anchor cannot be built as written on the L4 scene: the specular share is
   0.83, and `--abx-step-db` reaches no lower than −0.82 dB. The kit stops before rendering. Nothing is sealable
   until this is decided.
2. **Assertion 7's reading.** The model decay is 18.72 dB (it passes). The realised Schroeder drop on B at 63 Hz is
   18.47 dB, which would fail a realised reading.
3. **Assertion 4 is weak here.** The predicted A/B steps are all below 0.01 dB, against a 0.05 dB tolerance.
4. **Assertion 2 on the renders** holds from the partition boundary (6656), not from the exact tail fade start
   (7103). On the IRs it holds exactly.
5. **K6.** The worst case (E's sitting 2 + primary + rerun) is 2.47 h at the typical pace, which points to a third
   sitting.
