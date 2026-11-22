# 25: Builder, K3: the alternative ABX scenes (decider file 24, M3)

This file is computation only. It makes no decision. Nothing in `src/` was changed or tuned (PRD NFR-8). The binary
is `build/release/render_cli` (Release, this branch at 494bef5, up to date: `ninja: no work to do`). File 22's method
is reused, through `tools/ci/abx_kit.py`'s own render path and functions. The scenes were written to
`build/k3-alt-scenes/<scene>/scene.json` only, not as committed fixtures (the kit has no builder for S-B or S-C).

## Candidate scenes
Every scene is `abx_kit.scene_layout4_s1_default()` with at most one change:
- **S-A** `layout4_s1/default`, unchanged: 20 × 30 × 10 m, walls and ceiling α 0.01, floor α 1, s = 1 on every face,
  listener (10, 8, 1.7), emitters (7, 20, 2) and (13, 20, 2), tailSeed 12345.
- **S-C** `layout4_s1/listener_wall`: the listener at (10, 0.1, 1.7). This is the placement in
  `tests/unit/test_diffuse_wsweep.cpp` `layoutScenes()`, which is item 9's `listener_wall`. Both emitters are at
  r = 20.13 m.
- **S-B 0.3** and **S-B 0.6**: S-A with scattering 0.3 or 0.6 on all six faces. Nothing else changes.

## Results

### Main table (1 kHz unless stated; per-emitter values given as L / R)

| | S-A default | S-C listener_wall | S-B s = 0.3 | S-B s = 0.6 |
|---|---|---|---|---|
| r (m), r/r_c (Eq. 5.44, Eyring 1.291 s, r_c 3.85 m) | 12.37, 3.22 | 20.13, 5.23 | 12.37, 3.22 | 12.37, 3.22 |
| diffuse-field D/R, −20 log(r/r_c) | −10.1 dB | −14.4 dB | −10.1 dB | −10.1 dB |
| **per-emitter D/R, broadband** | +16.8 / +16.5 | +11.3 / +11.0 | −2.2 / −2.2 | +1.8 / +1.8 |
| **per-emitter D/R, 1 kHz** | +10.7 / +9.7 | +5.8 / +4.9 | −4.2 / −4.2 | −0.1 / −0.2 |
| **heard (L + R) D/R, broadband / 1 kHz** | +19.7 / +13.1 | +14.2 / +8.3 | −2.1 / −4.1 | +1.9 / +0.1 |
| t_mix,e (`ismFallback` true in all four) | 0.380 s | 0.380 s | 0.380 s | 0.380 s |
| early stretch [direct + 2.5 ms, t_mix − 2.5 ms) | 3.2 to 342 ms | 3.2 to 319 ms | 3.2 to 342 ms | 3.2 to 342 ms |
| images of order ≥ 1 with non-zero specular amplitude | 0 of 174 | 0 of 181 | 174 of 174 (first at 59.7 ms) | 174 of 174 (first at 59.7 ms) |
| **early part empty?** | **yes** | **yes** | **no** | **no** |
| **early energy re direct, 1 kHz** (broadband) | −29.3 dB (−76.7) | −29.3 / −29.2 dB (−72.0) | **+4.2 dB** (+2.1) | **−0.1 dB** (−2.0) |
| tail energy, from t_mix − 2.5 ms, re direct, 1 kHz | −10.5 / −9.5 dB | −5.5 / −4.6 dB | −8.9 / −8.0 dB | −10.1 / −9.2 dB |
| specular share of E_target per band (render_cli `--abx-step-db` print; equal in all 8 bands to 4 digits) | 0 | 0 | 0.328 / 0.334 | 0.068 / 0.067 |
| **window specular (non-scaling) share, exact, per band 63 … 8k**, emitter L | ≤ 6e−13 | ≤ 7e−13 | 7.7e−3, 4.5e−4, 2.8e−4, 3.2e−4, 3.8e−4, 3.8e−4, 3.8e−4, 5.0e−4 | 1.8e−4, 6.5e−6, 4.3e−6, 4.8e−6, 5.8e−6, 5.8e−6, 5.7e−6, 7.6e−6 |
| same, emitter R | ≤ 8e−13 | ≤ 7e−13 | 3.5e−3, 3.5e−4, 2.1e−4, 3.2e−4, 3.1e−4, 3.4e−4, 4.2e−4, 5.8e−4 | 7.6e−5, 5.0e−6, 3.1e−6, 4.7e−6, 4.7e−6, 5.1e−6, 6.3e−6, 8.7e−6 |
| same, broadband, [t_mix, L) / [t_mix + 2.5 ms, L) | 1e−13 / 0 | 1e−13 / 0 | 3.9e−4 / 0 (8e−15) | 6.0e−6 / 0 (8e−15) |
| **tail-alone T30 vs target T60** (Eyring) | 1.254 / 1.274 vs 1.291 s (−2.9 / −1.3 %) | identical | identical | identical |
| whole-IR T30, per emitter | 1.919 / 1.858 s | 1.274 / 1.281 s | 1.545 / 1.530 s | 1.771 / 1.727 s |
| heard-IR T30 (the kit's Q5 / gap T30) | 2.009 s | 1.799 s | 1.459 s | 1.770 s |
| **item 6, IR level (`ir_assertions`), g = ±0.9** | pass | pass | pass | pass |
| item 6, IR level, g = ±0.5 (and the ±3 anchor) | pass | pass | pass | pass |
| tail alone: diff_db − identity, step_db − g | 0.0000, 0.0000 dB | 0.0000, 0.0000 | 0.0000, 0.0000 | 0.0000, 0.0000 |
| [t_mix, L) window: diff_db − identity (tol 0.1) | 0.0000 dB | 0.0000 | +0.0046 / −0.0026 | +0.0008 / −0.0001 |
| **kit noise chain, all assertions** (`build_noise_chain`, trials 2 a block + the 6 familiarisation pairs: ±3, ±0.9, ±0.5) | **pass** (31 s) | **pass** (30 s) | **stops at item 9: not capped** | **stops at item 9: not capped** |
| same, cap check bypassed (diagnostic only) | — | — | item 6 passes; **item 10 headroom fails**: peaks −1.56 to +0.25 dBFS > −1 dBFS | **pass**, peaks −5.6 to −5.8 dBFS |
| stimulus peaks (familiarisation) | −10.5 to −11.7 dBFS | −15.2 to −15.9 dBFS | up to +0.25 dBFS | about −5.7 dBFS |
| **capped at m = 6 / 7 / 8** (`--w-multiplier`, capHit per emitter) | yes / yes / yes | yes / yes / yes | **no / no / no** | yes / yes / **no** |
| capHit at the shipped W | yes | yes | yes | yes |

### Tail-alone T30 per band (all four scenes: the same realisation)

| band (Hz) | 63 | 125 | 250 | 500 | 1k | 2k | 4k | 8k |
|---|---|---|---|---|---|---|---|---|
| target T60 (Eyring, diagnostics `t60`) | 1.335 | 1.332 | 1.323 | 1.309 | 1.291 | 1.243 | 1.089 | 0.740 |
| tail T30, L | 1.398 | 1.458 | 1.339 | 1.264 | 1.254 | 1.266 | 1.099 | 0.870 |
| tail T30, R | 1.288 | 1.300 | 1.378 | 1.293 | 1.274 | 1.250 | 1.097 | 0.884 |

The four scenes share the same T60 (scattering does not enter Eyring), the same t_mix,e (0.380 s, `ismFallback`) and
the same tailSeed. Their tails are therefore the same noise realisation at different levels. So the tail-alone T30 is
identical to 3 decimals in every scene, and the 8 kHz +18 % (file 22's follow-up) is present in all four.

## Findings for the decider (facts only)

1. **The early part is empty in S-A and S-C, and filled in both S-B scenes.**
   - S-C (listener_wall) keeps s = 1, so every specular image carries (1 − α)(1 − s) = 0 (AX21). Its early stretch is
     as empty as S-A's.
   - The −29.3 dB at 1 kHz in S-A and S-C is the octave filter's ringing from the direct sound. Broadband, the stretch
     is −72 to −77 dB, which is numerically empty.
   - With s < 1, every image carries energy. The first is the ceiling image at 59.7 ms. Over the early stretch the
     early energy is +4.2 dB (s = 0.3) or −0.1 dB (s = 0.6) relative to the direct sound at 1 kHz.
2. **D/R.**
   - S-C is 4.9 dB drier than S-A per emitter at 1 kHz (+5.8 / +4.9 against +10.7 / +9.7). It still sits about
     19 to 20 dB above its diffuse-field value (−14.4 dB), for the same AX21 reason.
   - S-B brings the per-emitter D/R to −4.2 dB (s = 0.3) and −0.1 / −0.2 dB (s = 0.6) at 1 kHz. Those are 5.9 and
     9.9 dB above the diffuse-field −10.1 dB.
   - The heard (L + R) D/R exceeds the per-emitter value by about 3 dB for S-A and S-C. For S-B it exceeds it by only
     0.1 to 0.3 dB. The direct sounds still add coherently (+6 dB), but at s < 1 the early images of L and R also
     arrive at matching times, so the early part partly adds coherently too.
3. **Specular share. File 24, question 2's premise does not match the code.**
   - File 24 (after file 23) models the step as scaling only the diffuse part: a = √((k − s)/(1 − s)). It predicts
     that `diff_db` misses by 2.6 dB at s = 0.5.
   - `render_cli --abx-step-db` (`src/cli/Cli.cpp`, `buildAbxStep`) sets E'_diff = k E_diff + (k − 1) E_spec. So the
     tail target E_target = E_spec + E_diff scales by exactly k.
   - The tail is a single noise waveform with amplitude √(E_target / E_unit). The whole waveform therefore scales by
     10^(g/20). That holds whatever the specular share of E_target is (0.33 or 0.07 here).
   - The "specular share" s in that sense is a share of the level target. It is not a separate waveform in the window
     that stays unscaled.
   - The only energy in item 6's window that does not scale is the early part's fade-out across t_mix ± 2.5 ms. That
     is 3.9e−4 (s = 0.3) and 6e−6 (s = 0.6) broadband, and 0 on the tail alone.
   - So item 6's identity holds on S-B: 0.0000 dB on the tail alone, and +0.005 dB at worst over [t_mix, L), against a
     tolerance of 0.1 dB.
   - File 24's corrected item-5 sentence ("At share > 0 the kit's `diff_db` assertion fails, so the kit refuses the
     stimulus") is therefore not borne out on these scenes. On M1, the decider should reread whether A and B still
     differ in what they produce.
   - The down-step refusal (E'_diff < 0) happens when k E_diff + (k − 1) E_spec < 0, that is when k is below the
     E_target specular share, or g < 10 log10(share).
     - That limit is −4.8 dB at s = 0.3 (share 0.33) and −11.7 dB at s = 0.6 (share 0.067).
     - Every step in the design (±0.9, ±0.5 and the ±3 anchor) is inside it, and all of them rendered.
4. **The kit's printed `specular_share` is a poor estimator at s > 0.** It is inferred from the identity, so it carries
   the cross term 2⟨N, T⟩. It reads 4.9e−2 at 63 Hz on S-B 0.3 emitter L, against an exact 7.7e−3, and is scattered
   (0 to 3.7e−3) in the other bands. The exact figure in the table is E(N)/E(u). The split is N = (a·u − s)/(a − 1),
   with a = 10^(g/20), u the unstepped IR and s the stepped IR (IR = N + T, stepped = N + aT). That split is exact.
   This confirms file 24's caution. A kit change is not made here.
5. **Cap (item 9).**
   - S-A and S-C are capped at m = 6, 7 and 8.
   - S-B 0.3 is capped at none of them. S-B 0.6 is capped at 6 and 7 but not at 8.
   - The kit's `check_scene` therefore stops on both S-B scenes, under item 9's rule. It reports this as "use
     listener_wall" because its message is written for S-A.
   - Every scene is capped at the shipped W.
6. **Item 10 headroom on S-B 0.3.** At the kit's fixed programme level (−8 dBFS pink noise, a kit choice), the strong
   early reflections push stimulus peaks to −1.56 … +0.25 dBFS. The kit's −1 dBFS no-normalisation check fails. This
   is not an item-6 failure. With the cap and peak checks lifted for diagnosis, every item-6 assertion passes: the IR
   level, the mid-fade W-a windows and companions (i) to (iii), and the click detector. S-B 0.6 peaks at about
   −5.7 dBFS and passes everything once the cap check is bypassed.
7. **T30 for Q5.** The heard-IR T30 moves with the early part: 2.009 s (S-A), 1.799 (S-C), 1.459 (S-B 0.3) and 1.770
   (S-B 0.6). The tail's own T30 (1.25 to 1.27 s) does not move. Any scene switch changes the Q5 pause and gap
   lengths under T-a. The Q5 speech window was not rerun on S-B or S-C here.

## Method

Script: run from the session scratchpad, not committed. It imports `tools/ci/abx_kit.py` and
`tools.acoustics`. Results: `build/k3-alt-scenes/k3_results.json` (git-ignored).

1. **Scenes.** As above, built from `abx_kit.scene_layout4_s1_default()` by editing only the listener position or
   the six `scattering` values. Written to `build/k3-alt-scenes/<tag>/scene.json`.
2. **Cap.** `render_cli --scene … --mode omni --w-multiplier m --diagnostics …` for m = 6, 7 and 8, reading
   `emitters[].diffuse.capHit`. This is `check_scene`'s loop, with the stop turned into a record.
3. **IR, D/R and T30.** These are file 22's steps 1 to 2.
   - Render: `render_cli --mode omni --ir --diagnostics`.
   - Per-emitter values: the emitter's own channel `channel·2`, through `abx_kit.emitter_ir_metrics`. That gives AX13
     D/R (broadband and 1 kHz), whole-IR T30, and tail-alone T30/EDT from t_mix,e, with
     `tools.acoustics.metrics.room_metrics`.
   - Heard values: `ir[:,0] + ir[:,2]`, the kit's basis.
   - Tail T30 per band: `room_metrics(h[t_mix:])`.
   - r_c: Kuttruff Eq. 5.44 with g = 1 and the Eyring T60 (file 22, step 4).
4. **Early part.** This is file 22's step 3.
   - Signal: the 1 kHz band (`bands.filter_band`) and the broadband IR.
   - Energy is summed over three ranges: the direct sound ±2.5 ms around the direct peak (onset plus argmax within
     2.5 ms); [direct + 2.5 ms, t_mix − 2.5 ms); and [t_mix − 2.5 ms, L).
   - Image count: `render_cli --mode omni --images` (the AX20 list). Images of order ≥ 1 whose 8-band `amplitude`
     has any non-zero entry were counted.
5. **Specular share.** Two readings:
   - (a) Of E_target, per band: render_cli's own `abx step: … specular share of E_target per band` print, which equals
     `diffuse.targetEnergySpecular / (targetEnergySpecular + targetEnergyDiffuse)` in the diagnostics.
   - (b) In item 6's window [t_mix,e, L), the energy that does not scale: from the `--abx-step-db g --ir u
     --abx-stepped-ir s` pair, N = (a·u − s)/(a − 1) with a = 10^(g/20). The share is E(N)/E(u), per octave band
     (`bands.filter_band`, then the window) and broadband. It was computed for g = ±0.9, ±0.5 and ±3. Every value is
     the same for every g, which confirms the split. The kit's own `ir_band_shares` was recorded beside it.
6. **Item 6.**
   - IR level: `abx_kit.ir_assertions` on the same pairs for g = ±0.9, ±0.5 and ±3. These are the bit-identical early
     part, tail-alone `diff_db` and `step_db` within 0.01 dB, and the window `diff_db` within 0.1 dB.
   - Full kit: `abx_kit.build_noise_chain(trials=2)`, with `scene_layout4_s1_default` swapped for the candidate
     scene. That covers every assertion: the cap check, the IR checks for all six g, and per stimulus the mid-fade
     W-a windows and (i) to (iii), the click detector, and peak ≤ −1 dBFS.
   - It ran on two scored-block trials per level plus all six familiarisation pairs, which carry ±3, ±0.9 and ±0.5.
     So both test levels were rendered and checked as stimuli.
   - For S-B, the chain was rerun with `W_CANDIDATES = ()` (the cap check skipped) to reach item 6. For S-B 0.3 it
     was run once more with the peak limit lifted. Both are diagnostic only.

Files: /home/user/makroof/tools/ci/abx_kit.py, /home/user/makroof/src/cli/Cli.cpp (`buildAbxStep`, lines 737–800),
/home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (`layoutScenes`),
/home/user/makroof/docs/review/phase-07c-2/22-drr-t30-check.md, /home/user/makroof/docs/review/phase-07c-2/24-decider-abx-r2-convene.md.
