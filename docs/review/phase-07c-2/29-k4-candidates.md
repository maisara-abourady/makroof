# 29: Builder, K4: candidate scenes for the ABX and item 15(ii)

This file is computation only. It makes no decision. Nothing in `src/` was changed or tuned (PRD NFR-8). It answers
the interrogator's questions 2 and 3 in file 28 (and the UNDERINFORMED row on D4-L1's extension) with measurements.
The binary is `build/release/render_cli` (Release, this branch at 66f5dec; `src/`, `tools/` and `tests/` are unchanged
since K3's 494bef5, `ninja: no work to do`). K3's method (file 25) is reused through `tools/ci/abx_kit.py`'s own render
path and functions. Scenes were written to `build/k4-alt-scenes/<scene>/scene.json` only, not as committed fixtures.

## Candidates

Every scene is built from `abx_kit.scene_layout4_s1_default()` (medium_room.json's other fields, tailSeed 12345):
20 × 30 × 10 m, every face α 0.01 except one face at α 1, listener R0 (10, 8, 1.7), emitters S0 (7, 20, 2) and
S1 (13, 20, 2).
- **(a)** layout 4 (the floor at α 1) at uniform s = 0.25, 0.4, 0.7, 0.8, 0.9 on all six faces, default placement.
- **(b)** every `layoutScenes()` placement of `tests/unit/test_diffuse_wsweep.cpp` (L75–107) at s = 1, for layout 4
  (the floor at α 1, `alpha[4]`) and layout 5 (`xMin` at α 1, `alpha[0]`; contract::SurfaceId order): `default`,
  `listener_wall` (listener (10, 0.1, 1.7)), `listener_edge` (0.1, 0.1, 1.7), `listener_corner` (0.1, 0.1, 9.9),
  `emitter_wall` (S0 at (7, 29.9, 2)), `both_wall` (both of those), `both_corner` (listener (0.1, 0.1, 0.1),
  S0 (19.9, 29.9, 9.9)). `layout4_s1/default` is **S-A**, restated here on the same method; `layout4_s1/listener_wall`
  is K3's S-C.

## Table

S-A's row reproduces K3's numbers (heard D/R 13.1 dB, heard T30 2.009 s, per-emitter D/R +10.7 / +9.7 dB).

| candidate | capped m = 6/7/8 | peak dBFS (noise chain, cap and peak checks bypassed) | per-emitter D/R 1 kHz, L / R (dB) | heard D/R 1 kHz (dB) | tail share of heard energy, 1 kHz | ΔG at g = +0.9, 1 kHz / broadband (dB) | ΔC80 at g = +0.9, 1 kHz / broadband (dB) | target specular share, max over bands, L / R | window unscaled share, broadband (max band) | item 6 | heard-IR T30 1 kHz (s) | early part empty? (images ≥ 1 non-zero L, R; early re direct, broadband) |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| layout4_s0.25/default | no/no/no | −0.9 to +1.1 | −4.8 / −4.9 | −4.7 | 0.018 | 0.018 / 0.006 | −0.076 / −0.035 | 0.410 / 0.419 | 6.5e−04 (1.2e−02) | pass | 1.398 | no (174/174, 174/174; +2.7 dB) |
| layout4_s0.4/default | no/no/no | −3.0 to −1.5 | −2.9 / −3.0 | −2.8 | 0.022 | 0.022 / 0.006 | −0.140 / −0.066 | 0.202 / 0.206 | 1.3e−04 (2.7e−03) | pass | 1.583 | no (174/174, 174/174; +0.8 dB) |
| layout4_s0.7/default | yes/yes/yes | −7.6 to −6.3 | +1.5 / +1.3 | +1.7 | 0.032 | 0.032 / 0.008 | −0.519 / −0.329 | 0.032 / 0.029 | 6.1e−07 (2.5e−05) | pass | 1.831 | no (174/174, 174/174; −3.8 dB) |
| layout4_s0.8/default | yes/yes/yes | −8.7 to −7.6 | +3.5 / +3.2 | +3.8 | 0.034 | 0.034 / 0.009 | −0.711 / −0.551 | 0.015 / 0.013 | 2.7e−08 (1.9e−06) | pass | 1.889 | no (174/174, 174/174; −6.0 dB) |
| layout4_s0.9/default | yes/yes/yes | −9.9 to −8.9 | +6.0 / +5.6 | +6.6 | 0.040 | 0.040 / 0.010 | −0.860 / −0.810 | 0.004 / 0.004 | 1.0e−10 (2.8e−08) | pass | 1.925 | no (174/174, 174/174; −9.5 dB) |
| **S-A** layout4_s1/default | yes/yes/yes | −11.7 to −10.3 | +10.7 / +9.7 | +13.1 | 0.046 | 0.045 / 0.011 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (2.4e−12) | pass | 2.009 | yes (0/174, 0/174; −76.7 dB) |
| layout4_s1/listener_wall | yes/yes/yes | −15.9 to −14.7 | +5.8 / +4.8 | +8.3 | 0.129 | 0.127 / 0.037 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (2.3e−12) | pass | 1.799 | yes (0/181, 0/181; −72.0 dB) |
| layout4_s1/listener_edge | yes/yes/yes | −18.8 to −16.4 | +6.7 / +4.8 | −1.0 | 0.208 | 0.204 / 0.066 | −0.900 / −0.900 | 0.000 / 0.000 | 4.0e−13 (2.3e−12) | pass | 1.752 | yes (0/175, 0/167; −70.2 dB) |
| layout4_s1/listener_corner | yes/yes/yes | −19.4 to −17.3 | +5.4 / +4.0 | −1.6 | 0.256 | 0.249 / 0.084 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (2.5e−12) | fails: click detector, 1 of 10 stimuli (fam 3, g +0.9); all else pass | 1.288 | yes (0/175, 0/167; −69.8 dB) |
| layout4_s1/emitter_wall | yes/yes/yes | −16.1 to −14.7 | +5.2 / +9.7 | +2.9 | 0.132 | 0.130 / 0.035 | −0.900 / −0.900 | 0.000 / 0.000 | 4.3e−13 (2.4e−12) | pass | 1.808 | yes (0/179, 0/174; −71.0 dB) |
| layout4_s1/both_wall | yes/yes/yes | −15.7 to −12.9 | −7.7 / +5.2 | −5.3 | 0.667 | 0.621 / 0.471 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (1.0e−05) | fails: click detector, 1 of 10 stimuli (0.5 2, g +3.0); all else pass | 1.370 | yes (0/39, 0/181; −67.9 dB) |
| layout4_s1/both_corner | yes/yes/yes | −21.2 to −19.3 | +8.2 / +5.3 | +1.2 | 0.199 | 0.195 / 0.065 | −0.900 / −0.900 | 0.000 / 0.000 | 4.3e−13 (5.0e−12) | pass | 1.656 | yes (0/159, 0/167; −65.6 dB) |
| layout5_s1/default | yes/yes/yes | −9.6 to −8.1 | −3.8 / −4.8 | −1.4 | 0.579 | 0.543 / 0.208 | −0.900 / −0.900 | 0.000 / 0.000 | 4.1e−13 (3.1e−12) | pass | 2.557 | yes (0/349, 0/350; −76.7 dB) |
| layout5_s1/listener_wall | no/no/no | −5.0 to −0.5 | −12.9 / −14.2 | −10.4 | 0.916 | 0.831 / 0.759 | −0.730 / −0.798 | 0.000 / 0.000 | 4.1e−13 (2.4e−06) | pass | 2.572 | yes (0/47, 0/50; −72.0 dB) |
| layout5_s1/listener_edge | yes/yes/no | −8.2 to −4.0 | −9.9 / −12.0 | −13.4 | 0.922 | 0.836 / 0.771 | −0.812 / −0.853 | 0.000 / 0.000 | 4.1e−13 (5.0e−06) | pass | 2.571 | yes (0/41, 0/51; −70.2 dB) |
| layout5_s1/listener_corner | no/no/no | −8.7 to −5.1 | −9.3 / −12.2 | −13.4 | 0.920 | 0.835 / 0.766 | −0.871 / −0.855 | 0.000 / 0.000 | 4.2e−13 (6.0e−06) | pass | 2.571 | yes (0/39, 0/51; −69.8 dB) |
| layout5_s1/emitter_wall | yes/yes/yes | −8.3 to −5.8 | −12.4 / −5.0 | −9.5 | 0.869 | 0.792 / 0.633 | −0.900 / −0.900 | 0.000 / 0.000 | 4.3e−13 (2.8e−06) | pass | 2.559 | yes (0/55, 0/350; −71.0 dB) |
| layout5_s1/both_wall | yes/yes/yes | −5.7 to −1.1 | −14.7 / −14.3 | −16.0 | 0.964 | 0.871 / 0.837 | −0.676 / −0.729 | 0.000 / 0.000 | 4.2e−13 (1.6e−06) | pass | 2.571 | yes (0/75, 0/50; −67.9 dB) |
| layout5_s1/both_corner | yes/yes/yes | −9.6 to −5.2 | −9.3 / −12.5 | −13.2 | 0.936 | 0.847 / 0.793 | −0.849 / −0.794 | 0.000 / 0.000 | 4.0e−13 (4.9e−06) | pass | 2.575 | yes (0/95, 0/51; −65.6 dB) |

Column notes. "yes/yes/no" means both emitters capped at m = 6 and 7 and at least one not at 8. All scenes are capped
at the shipped W. Item 6 "pass" means every IR-level assertion (`ir_assertions`) at g = ±0.9, ±0.5 and ±3 passed and
the kit's noise chain passed with only the cap (item 9) and peak (item 10) checks bypassed. Item 10 itself (peak ≤
−1 dBFS) can be read from the peak column.

## Facts for the decider

1. **Question 3 (s = 0.25 and 0.4).** Neither is capped at m = 6, 7 or 8 (either emitter). With K3, the layout-4
   default placement is uncapped at every m for s = 0.25, 0.3, 0.4; capped at 6 and 7 but not 8 for s = 0.6; capped at
   all three for s = 0.7, 0.8, 0.9 and 1. Peaks on the kit's noise chain: s = 0.25 reaches +1.1 dBFS (item 10's
   −1 dBFS fails, as at s = 0.3); s = 0.4 peaks at −1.5 dBFS (passes). Item 6 passes on both once the cap check is
   bypassed.
2. **Question 2 (an s < 1 scene with ΔC80 ≥ S-A's).** S-A's heard ΔC80 at g = +0.9 dB is −0.900 dB at 1 kHz and
   broadband (equal to −g within 1e−8 dB: [0, 80 ms) holds only the direct sound). No s < 1 candidate reaches it.
   |ΔC80| at 1 kHz rises with s: 0.076 (s = 0.25), 0.140 (0.4), 0.519 (0.7), 0.711 (0.8), 0.860 (0.9). The early
   images (174 of 174 non-zero from the ceiling image at 59.7 ms) fall in both windows and do not scale.
3. **s = 1 candidates with ΔC80 equal to S-A's** (−0.900 dB within 1e−6 at 1 kHz and broadband): every layout-4
   placement, and layout 5 `default` and `emitter_wall`. In layout 5's `listener_*`, `both_*` placements, |ΔC80| is
   0.68 to 0.87 dB at 1 kHz. There `ismFallback` is false for both emitters and t_mix,e is 0.136 to 0.186 s, which is 77.5 ms after
   the direct sound (less than 80 ms), so part of the scaled tail lies in C80's early window.
4. **Early part.** Empty (no image of order ≥ 1 with non-zero amplitude; −65.6 to −76.7 dB broadband re direct) in
   every s = 1 scene. Filled in every s < 1 scene: +2.7 dB (s = 0.25) down to −9.5 dB (s = 0.9) broadband re direct.
5. **Tail share and ΔG.** ΔG at g = +0.9 dB tracks the tail share of the heard energy (ΔG ≈ 10 log10(1 + share
   (a² − 1)), a = 10^(g/20)). S-A: share 0.046, ΔG 0.045 dB at 1 kHz on the heard IR. On emitter L alone, S-A's
   ΔG is 0.077 dB at 1 kHz (file 28 gives 0.079 from K3's window energies). The s < 1 scenes have a smaller share
   than S-A (0.018 to 0.040). The s = 1 wall and corner placements have a larger share (0.13 to 0.67 in layout 4,
   0.58 to 0.96 in layout 5).
6. **Item 6 fails on two scenes, at the click detector only.** `layout4_s1/listener_corner` (familiarisation pair 3,
   g = +0.9, event at 3.537 s, −39.7 dBFS) and `layout4_s1/both_wall` (0.5 dB block trial 2, g = +3, event at 3.491 s,
   −33.7 dBFS). Rerun with the click assertion turned into a record (diagnostic only), every other assertion on all
   10 stimuli passed and exactly one stimulus per scene was flagged. The detector's blind spots on noise are stated
   in `click_check`'s docstring. Whether these are clicks was not examined here.
7. **Target specular share** is 0 at s = 1 (AX21) and 0.004 (s = 0.9) to 0.419 (s = 0.25) at s < 1. The down-step
   refusal limit is g < 10 log10(share): −3.8 dB at s = 0.25 (share 0.419). Every step of the design (±0.9, ±0.5,
   ±3) rendered on every candidate.
8. **Window unscaled share** ([t_mix,e, L), exact split N = (a·u − s)/(a − 1)): ≤ 4.3e−13 broadband in every s = 1
   scene, 1.0e−10 (s = 0.9) to 6.5e−4 (s = 0.25) at s < 1.
9. **Heard-IR T30 (1 kHz)** ranges from 1.288 s (layout4 listener_corner) to 2.009 s (S-A) in layout 4 and 2.557 to
   2.575 s in layout 5 (Eyring T60 2.608 s at 1 kHz against 1.291 s: the absorbing face is 300 m², not 600 m²; tail-alone T30 2.58 to
   2.62 s). The Q5 speech window was not run on any candidate.

## Method

Scripts: run from the session scratchpad (`k4.py`, `k4b.py`, `k4table.py`), not committed. They import
`tools/ci/abx_kit.py` and `tools.acoustics`. Results: `build/k4-alt-scenes/k4_results.json` and `k4b_results.json`
(git-ignored).

1. **Cap.** `render_cli --scene … --mode omni --w-multiplier m --diagnostics …` for m = 6, 7, 8, reading
   `emitters[].diffuse.capHit` (`check_scene`'s loop, with the stop turned into a record).
2. **D/R, T30.** K3 step 3: `render_cli --mode omni --ir --diagnostics`. Per emitter: channel `channel·2` through
   `abx_kit.emitter_ir_metrics` (AX13 D/R). Heard: `ir[:,0] + ir[:,2]` through `metrics.room_metrics` (D/R and T30
   at 1 kHz).
3. **Early part.** K3 step 4: `--images` (the AX20 list), images of order ≥ 1 with any non-zero band amplitude;
   broadband energy over [direct + 2.5 ms, t_mix,e − 2.5 ms) against ±2.5 ms around the direct peak (max over the two
   emitters in the table).
4. **Target specular share.** Per emitter, max over the 8 bands of `targetEnergySpecular / (targetEnergySpecular +
   targetEnergyDiffuse)` from the diagnostics.
5. **IR pair.** `render_cli --mode omni --abx-step-db g --ir u --abx-stepped-ir s` for g = ±0.9, ±0.5, ±3.
   - Item 6, IR level: `abx_kit.ir_assertions(u, s, diag, g)`.
   - Window unscaled share: N = (a·u − s)/(a − 1), a = 10^(g/20); E(N)/E(u) over [t_mix,e, L), broadband and per
     octave band (`bands.filter_band`), per emitter; the table gives the maximum over emitters and g.
   - At g = +0.9 only, on the heard pair hu = u[:,0] + u[:,2], hs = s[:,0] + s[:,2]:
     - **ΔG** = 10 log10(Σ hs² / Σ hu²) over the whole IR, broadband and in the 1 kHz octave
       (`bands.filter_band_with_lead`, so the zero-phase filter's pre-ringing is kept, as `room_metrics` does).
     - **C80** per Vorländer Eq. 6.7: 10 log10(∫₀^80ms p² / ∫_80ms^∞ p²), t = 0 at the broadband onset of hu
       (`metrics.onset_index`, ISO 3382-1's −20 dB rule; filter lead added in band), the late window to the end of the
       IR file (the synthetic IR has no noise floor, so no Lundeby truncation: `room_metrics`' C80 truncates at the
       crosspoint and was not used). **ΔC80** = C80(hs) − C80(hu).
     - **Tail share** = E(T)/E(hu) at 1 kHz, T = (hs − hu)/(a − 1), the part of the heard IR that scales.
     - The same ΔG and ΔC80 were computed on emitter L alone (quoted in fact 5 and the script output).
6. **Kit noise chain.** `abx_kit.build_noise_chain(trials=2)` with `scene_layout4_s1_default` swapped for the
   candidate, `W_CANDIDATES = ()` (cap check skipped) and `MAX_PEAK_DBFS = 20` (peak check lifted), both diagnostic
   only. Two scored-block trials per level plus the six familiarisation pairs (±3, ±0.9, ±0.5): 10 stimuli, each with
   the mid-fade W-a windows, companions (i) to (iii), the click detector and the peak recorded. The peak column is the
   range over the 10 stimuli. For the two scenes that stopped at the click detector, `k4b.py` reran the chain with the
   click assertion recording instead of raising, to get the peaks and the other assertions.

Files: /home/user/makroof/tools/ci/abx_kit.py, /home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (`layoutScenes`,
L75–107), /home/user/makroof/docs/review/phase-07c-2/25-k3-alt-scenes.md,
/home/user/makroof/docs/review/phase-07c-2/28-interrogator-on-file27.md.
