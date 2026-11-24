# 5: Builder, the per-emitter tail spread (Seat 9's R2-1) and the kit's first two-scene build

Computation only, no decision. Nothing in `src/` was changed or tuned (PRD NFR-8). Binary `build/cli/render_cli`
(Release, branch `claude/trusting-hypatia-j2rt6d`; `src/` unchanged since main 86f757f). Scenes from
`tools/ci/abx_kit.py` `make_scene` (identical to K4's construction; S-A asserted equal to the pre-refactor builder).

## Seat 9's R2-1: is both_wall's tail share an engine artefact?

Seat 9 inferred from file 29 that emitter L's tail on `layout4_s1/both_wall` is about 9.4 dB stronger than
emitter R's at equal source power, which Kuttruff Eq. 5.42 does not allow (the reverberant level depends on P and A,
not on the source position). Measured on each emitter's own omni IR (output `channel·2`), 1 kHz octave
(`bands.filter_band`):

| scene | 1 kHz, from each emitter's own t_mix,e: L − R | t_mix,e L / R (s) | 1 kHz, same absolute window [0.45, 0.65) s: L − R | [0.8, 1.0) s: L − R |
|---|---|---|---|---|
| layout4_s1/default | −0.94 dB | 0.380 / 0.380 | +0.08 dB | −0.44 dB |
| layout4_s1/emitter_wall | −0.64 dB | 0.379 / 0.380 | +0.34 dB | −0.19 dB |
| layout4_s1/listener_wall | −0.91 dB | 0.380 / 0.380 | — | — |
| layout4_s1/listener_edge | — | 0.380 / 0.379 | −0.12 dB | +0.21 dB |
| layout4_s1/listener_corner | — | 0.380 / 0.384 | −0.06 dB | +0.02 dB |
| **layout4_s1/both_wall** | **+9.39 dB** | **0.165 / 0.380** | **−0.05 dB** | **−0.03 dB** |
| **layout4_s1/both_corner** | **−6.80 dB** | 0.376 / 0.379 | **−6.20 dB** | **−6.12 dB** |
| layout4_s0.7/default | −1.23 dB | 0.380 / 0.380 | — | — |

**Facts.**
1. **both_wall: no level spread.** At the same absolute time the two emitters' diffuse tails agree within 0.05 dB
   at 1 kHz. The +9.4 dB "from t_mix,e" figure is the window, not the level: emitter L's tail starts at
   t_mix,e = 0.165 s instead of the 0.380 s fallback, i.e. 0.215 s earlier, and 0.215 s of a 1.29 s decay is
   10.0 dB of energy. Seat 9's premise (equal directs plus a +9.4 dB tail) reproduces the share because the extra
   energy is real tail energy in [0.165, 0.380) s, not a level offset. So S-W's tail share 0.667 and ΔG 0.62 dB
   come from L's earlier tail onset (the t_mix,e rule at that placement), not from an estimator level error. If a
   later `src/sim` change moves L's t_mix,e back to the fallback, the share falls (Seat 9's ≈ 0.29 estimate applies
   then) and M3-8's trigger fires.
2. **both_corner: a real 6.2 dB spread.** At the same absolute windows, emitter L (at (19.9, 29.9, 9.9), 0.1 m from
   two walls and the ceiling) has a diffuse tail 6.1–6.2 dB below emitter R's at the same listener. Equal source
   power and the same room should give the same reverberant level (Kuttruff Eq. 5.42). This is an engine behaviour at
   a corner emitter, reported under NFR-8 (not tuned). both_corner is the S-W rule's fallback 3, not a chosen scene.
   Routed: Seat 2 (is it the AX40 estimator or the image-source set at a corner source?), as a follow-up outside this
   phase's scope (no `src/sim` change here).
3. The other placements (default, emitter_wall, listener_wall, listener_edge, listener_corner, s0.7) agree within
   about 1 dB from their own t_mix,e and within 0.44 dB at equal windows.

## The kit's two-scene noise build (`listening_pack.py --phase phase-07c-2b`)

The kit, with HF-W (M3-3, Seat 5's condition D included) and the M3-4 labels, built both scenes' noise chains:
- **layout4_s1/both_wall:** capped at m = 6, 7, 8 (both emitters); heard T30 1.370 s, tail T30 1.313 / 1.274 s;
  M2: minimum gap 1.376 s ≥ 1.313 s (margin 63 ms); IR step at +0.9 dB exactly +0.9000 dB on the tail alone,
  s_w 1.4e−13, target specular share 0; heard tail share 0.667 (1 kHz), ΔG +0.621 dB, ΔC80 −0.900 dB. All 50
  stimuli (44 block trials, 6 familiarisation pairs) passed every item-6 assertion including HF-W; peaks −16.0 to
  −12.9 dBFS.
- **layout4_s0.7/default:** capped at m = 6, 7, 8; heard T30 1.831 s, tail T30 1.254 / 1.274 s; M2: minimum gap
  1.835 s ≥ 1.274 s; target specular share up to 0.032; s_w ≤ 6.1e−7. (Full stimulus results: the build log and
  `manifest.json`, cited in the brief once complete.)
- **r_c printed by the kit** is 0.057·√(V/T60_Eyring) = 3.89 m (r/r_c 7.71 / 5.18 on both_wall, 3.18 on s0.7); the
  labels use Kuttruff Eqs. 5.44–5.45 with A ≈ 640 m², r_c 3.57 m (8.39 / 5.64, 3.47). Both are printed; the labels'
  figures are the ones M3-4 decided.

Method: scratchpad script (not committed) importing `abx_kit.make_scene`, `render_cli --mode omni --ir --diagnostics`
per scene, `bands.filter_band(·, 1000)`, energies summed over the stated windows of the aligned IR.

## HF-W per scene (Seat 3's condition (a), round-2 addendum)

From each scene's `manifest.json` in `build/listening-pack/phase-07c-2b/noise/<scene>/` (local build of
`listening_pack.py --phase phase-07c-2b`, exit 0; every stimulus of both chains, 44 block trials + 6 familiarisation
pairs per scene). Worst ratio = max over stimuli, channels and frames of E_o / max(E_a, E_b); margin = 10 log10(β /
worst).

| scene | stimuli | HF-W worst ratio | β | margin (dB) | skipped frames | frames checked | peaks (dBFS) | Seat 5 (a) subset record fails |
|---|---|---|---|---|---|---|---|---|
| layout4_s0.7/default | 50 | 1.0003 | 1.1378 | 0.559 | 0 | 2100 | -7.8 to -6.0 | 0 |
| layout4_s1/both_wall | 50 | 1.0002 | 1.1378 | 0.560 | 0 | 2100 | -16.0 to -12.2 | 0 |

## HF-W commutator check (decider file 2, M3-3 "Before any seal")

Seat 3's `[Hyp]` (the 2 kHz high-pass and the 30 ms ramp commute to a negligible error) checked by full noise-chain
builds with the kit as committed (scratchpad script, `build_noise_chain(scene_name=…)`; listener_corner given a
diagnostic-only label, never sealed):

| scene | stimuli | HF-W worst ratio (β 1.1378) | margin (dB) | M2: minimum gap vs tail T30 |
|---|---|---|---|---|
| layout4_s1/default (S-A, all 50 noise stimuli) | 50 | 1.0004 | 0.559 | 2.016 s ≥ 1.274 s |
| layout4_s1/listener_corner (K5 stimulus: familiarisation pair 3, seed index 102, included) | 50 | 1.0001 | 0.561 | 1.291 s ≥ 1.273 s (18 ms margin) |
| layout4_s1/both_wall (K5 stimulus: 0.5 dB block trial 2, included) | 50 | 1.0002 | 0.560 | 1.376 s ≥ 1.313 s |
| layout4_s0.7/default | 50 | 1.0003 | 0.559 | 1.835 s ≥ 1.274 s |

So on 200 stimuli across four scenes, the worst high-passed frame energy exceeds the larger end point by at most
0.04 % (0.002 dB), against a bound of 13.8 % (0.56 dB): the commutator error is negligible on these scenes. Both K5
false positives pass HF-W. Every build stopped on nothing.
