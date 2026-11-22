# 22 — Builder: the ABX scene's D/R and T30 (decider file 21, point 2b)

A code fact, no seat. Nothing in `src/` was changed or tuned (PRD NFR-8). Corpus revision c1b171fe. Binary:
`build/release/render_cli` (Release, this branch). Scene: `abx_kit.scene_layout4_s1_default()`, exactly as the
kit writes it (20 × 30 × 10 m, walls and ceiling α 0.01, floor α 1, scattering 1 on every face, listener
(10, 8, 1.7), emitters L (7, 20, 2) and R (13, 20, 2), tailSeed 12345).

**Verdict: (B), a genuine property of the rendered scene, with two method artefacts in the kit's prints.**
- The rendered IR really is that dry. Each emitter's own D/R is +9.7 / +10.7 dB at 1 kHz, about 20 dB above the
  diffuse-field −10 dB at r/r_c = 3.2. The cause is that the IR is **empty between the direct sound and
  t_mix,e = 0.380 s**. This is AX21: the early part is specular-only, and with s = 1 on every face each specular
  image carries (1 − α)(1 − s) = 0. AX21 is a known, recorded deficit (BUILD_PLAN AX21, backlog B11; phase 05b did
  not promote early scattered energy). The code does what AX21 says, so this is not a new sim defect (C).
- Artefact 1 (D/R): the kit's +19.7 / +13.1 dB is the **heard** IR, L + R summed. Both emitters are at the same r,
  so their direct sounds land on the same tap and add coherently (+6 dB). The tails are uncorrelated (ρ = 0.002)
  and add in energy (+3 dB). The sum therefore reads 2.9 dB (1 kHz) to 3.0 dB (broadband) above each emitter's own
  D/R. As the heard D/R the value is correct. As "the scene's D/R at r/r_c" it is 3 dB too high.
  - Channel indexing is right: the IR's channels are `channel·2 + output`, and omni gives output 0 = output 1. So
    `ir[:,0]` is L and `ir[:,2]` is R.
  - The ±2.5 ms window sees both direct peaks, because they coincide (tap 32 in both; |L − R| = 0 over the first
    200 taps). No peak is missed.
- Artefact 2 (T30): the 2.009 s is the T30 of the heard IR's EDC: a step at the direct sound, a flat stretch out to
  t_mix, then the decay. The regression from −5 to −35 dB spans the flat stretch, so it reads long. **The tail
  itself decays at the diffuse target's Eyring T60**: tail-alone T30(1 kHz) is 1.254 / 1.274 s against 1.291 s
  (−2.9 % / −1.3 %). The speech render shows the same thing: in the Q5 pause the 1 kHz margin falls at 46.3 dB/s,
  which is T60 1.297 s. "T30 ≈ 1.56 × Eyring" is therefore not a slow room. It is the AX21 gap seen through an
  ISO 3382 decay fit.

What follows under file 21's outcome rule (for the orchestrator and the decider, not done here):
- The rule's D/R half holds: the rendered scene is about 20 dB drier than the "occupied mid-size hall envelope"
  label implies.
- The rule's T30 half does not hold as worded: the decay rate matches Eyring.
- The sim finding to report (NFR-8: report, don't tune) is AX21's empty early part, not a slow decay.
- Item 9's label correction and the CONVENE of Seats 1, 2, 3 and 9 (does the scene still serve AX47's "all
  scenes" bound) apply as file 21 states, before sealing.
- The kit's Q5 T30 (2.009 s, the heard IR's) is **unchanged** by this check. It sets the pause length and the
  0.43 · T30 ceiling. Whether Q5 should use the tail's own T30 (≈ 1.26 s) is for the decider. Changing it would
  change the stimuli.

## Method

1. `render_cli --scene <scene> --mode omni --ir ir.wav --diagnostics diag.json`, the kit's own render path. There
   are no single-emitter scenes: contract v1 rejects them (`E_EMITTER_COUNT`: exactly 2 emitters). The omni IR,
   however, holds each emitter's IR in its own channel pair, with no cross-feed. Channel `channel·2` is therefore
   the single-emitter IR.
2. Metrics: `tools.acoustics.metrics.room_metrics`, the repo's ISO 3382 / AX13 implementation. D/R is the energy in
   ±2.5 ms around the direct peak over the rest, up to the Lundeby crosspoint plus compensation. Each emitter is
   measured on its own channel, on the sum (the kit's way), and on the tail alone (the IR from t_mix,e on).
3. Energy budget at 1 kHz: `bands.filter_band`, summed over direct ±2.5 ms, [direct + 2.5 ms, t_mix − 2.5 ms) and
   [t_mix − 2.5 ms, L).
4. Critical distance: Kuttruff Eq. 5.44 (corpus `kuttruff-room-acoustics.md`, §5.6) with directivity g = 1 (Eq. 5.48
   with g = 1): r_c = (A/16π)^½ ≈ 0.1·(V/(πT))^½. The kit's 0.057·(V/T)^½ is that formula rounded (0.1/√π =
   0.0564), so the kit's r/r_c is 1 % low. Kuttruff states Eq. 5.44 with Sabine's T. Here it is evaluated with each
   T in turn. The scene's own values: V = 6000 m³, S = 2200 m², ᾱ = 0.28 (diagnostics `meanAbsorption`), and
   4mV(1 kHz) = 25.8 m². So A = −S·ln(1 − ᾱ) + 4mV = 748.5 m².
5. Diffuse-field D/R = −20·log10(r/r_c) (Kuttruff Eq. 5.43–5.45).
6. The speech Q5 numbers come from a rerun of the kit:
   `abx_kit.py speech --speaker MA --files MA01_01 MA01_02 --trials 1`, with the TSP zip checked against the kit's
   SHA-256. The manifest now carries the per-boundary margins (see "Kit change").

## Results

### Distances and r_c (both emitters at r = 12.373 m; the layout is symmetric)

| T used | T (1 kHz) | r_c, Eq. 5.44 | r/r_c | diffuse-field D/R |
|---|---|---|---|---|
| Eyring T60 (diffuse target, diagnostics `t60`) | 1.291 s | 3.85 m (A form: 3.86 m; kit's 0.057: 3.89 m) | 3.22 (kit 3.18) | −10.2 dB |
| heard IR T30 (L + R, the kit's) | 2.009 s | 3.08 m | 4.01 | −12.1 dB |
| whole-IR T30, L / R | 1.919 / 1.858 s | 3.15 / 3.21 m | 3.92 / 3.86 | −11.9 / −11.7 dB |
| tail-alone T30, L / R | 1.254 / 1.274 s | 3.90 / 3.87 m | 3.17 / 3.20 | −10.0 / −10.1 dB |

### D/R (AX13), measured

| IR | broadband | 1 kHz | 2 kHz | 4 kHz | 8 kHz |
|---|---|---|---|---|---|
| emitter L alone | +16.8 dB | +10.7 dB | +11.3 dB | +13.7 dB | +23.3 dB |
| emitter R alone | +16.5 dB | +9.7 dB | +10.8 dB | +14.0 dB | +23.9 dB |
| heard, L + R (the kit's print) | +19.7 dB | +13.1 dB | +14.2 dB | — | — |

At 63 to 500 Hz the band filter cannot resolve ±2.5 ms, so AX13 reports no D/R there.

### Energy budget, 1 kHz band, per emitter

| emitter | direct (±2.5 ms) | direct + 2.5 ms to t_mix − 2.5 ms | from t_mix − 2.5 ms | D/R |
|---|---|---|---|---|
| L | 1.56e−4 | 1.8e−7 (−29.3 dB re direct) | 1.39e−5 | +10.4 dB |
| R | 1.56e−4 | 1.8e−7 (−29.3 dB re direct) | 1.74e−5 | +9.5 dB |

- t_mix,e = 0.380 s for both emitters (`ismFallback` true, image cap 1560, 175 images of which 174 are scattered).
  The AX20 expected mixing time is 0.114 s.
- Diffuse theory puts the whole reverberant energy at direct − (−10.2 dB). Of that, Eyring's decay leaves
  exp(−13.8 · 0.380/1.291) = −17.7 dB after 0.380 s. A tail that starts at t_mix therefore gives an expected
  D/R of +7.5 dB.
- The measured values are +10.4 / +9.5 dB, so the tail level sits 2.0 to 2.9 dB under that Eyring estimate. Its
  level is the propagated diffuse estimate (AX37), not Eyring.
- For orientation only: Kuttruff Table 5.2, case 4 (this room shape, absorbing floor) has the iterated T 12 % shorter
  than Eyring (1.21 against 1.38 s). That moves the same estimate to about +10.6 dB.
- So the ≈ 20 dB D/R gap is ≈ 17.7 dB from the empty early stretch (AX21) and ≈ 2 to 3 dB from the tail level.

### Diffuse target T60 against measured T30 and EDT, per emitter and band

The target is diagnostics `t60` (Eyring, with air absorption); the noise tail decays at exactly this rate
(`NoiseTail.cpp`, `kAmplitudeDecayPerT60 / T60_b`). "Whole IR" is the emitter's own channel. "Tail" is the IR from
t_mix,e = 0.380 s.

| band (Hz) | target T60 | L: T30 whole IR | L: EDT whole IR | L: T30 tail | L: EDT tail | R: T30 whole IR | R: EDT whole IR | R: T30 tail | R: EDT tail |
|---|---|---|---|---|---|---|---|---|---|
| 63 | 1.335 | 2.362 | 0.197 | 1.398 | 1.635 | 1.883 | 12.69 | 1.288 | 1.379 |
| 125 | 1.332 | 1.817 | 20.39 | 1.458 | 1.111 | 1.756 | 19.51 | 1.300 | 1.425 |
| 250 | 1.323 | 1.991 | 31.04 | 1.339 | 1.338 | 1.872 | 21.18 | 1.378 | 1.267 |
| 500 | 1.309 | 1.948 | 21.22 | 1.264 | 1.406 | 1.842 | 19.91 | 1.293 | 1.171 |
| 1000 | 1.291 | 1.919 | 56.62 | 1.254 | 1.505 | 1.858 | 33.50 | 1.274 | 1.416 |
| 2000 | 1.243 | 1.925 | 140.9 | 1.266 | 1.334 | 1.900 | 79.18 | 1.250 | 1.313 |
| 4000 | 1.089 | 1.898 | 0.002 | 1.099 | 1.135 | 1.930 | 0.002 | 1.097 | 1.167 |
| 8000 | 0.740 | 2.890 | 0.001 | 0.870 | 0.776 | 3.005 | 0.001 | 0.884 | 0.789 |
| broadband | — | 2.321 | — | 1.232 | — | 2.277 | — | 1.233 | — |

How to read the table:
- **Tail T30, 250 Hz to 4 kHz:** within −3 % to +5 % of the target.
- **Low bands:** 63 and 125 Hz are noisier (one 384-entry realisation, `capHit`).
- **8 kHz:** the tail T30 reads 0.87 / 0.88 s against 0.74 s (+18 %). This is recorded, not investigated here (it
  is outside point 2b, which is about 1 kHz). Follow-up for the orchestrator: find out whether it is the metric
  or the tail.
- **Whole-IR EDT** is meaningless on this IR, from 0.001 s to 141 s. The EDC falls 10 dB almost exactly at the
  direct sound and then stays flat out to t_mix. Whether the −10 dB point lands before or on the flat stretch
  decides between "instant" and "huge". It is reported here only to show that the IR-level decay parameters do not
  describe the room.

### Q5 (realised, for file 21 point 2a; interrogator file 23, questions 1 and 4)

- 81 partition boundaries lie in the 0.43 · T30 ceiling, and 35 pass the ≥ 20 dB margin. The passing set is
  boundaries 0–33 and 35; boundary 34 misses by 0.6 dB. It is **not strictly contiguous**.
- Realised window: [0.0007, 0.1865] · T30 after the end of speech. That is 1.3 ms to 0.375 s, with
  T30 = 2.009 s.
- Replacement: the first draw is replaced with p = 46/81 = 0.568. The expected number of replaced onsets per
  stimulus is 46/36 = 1.28 (permutation draw, failures before the first success).
- Why the cutoff falls at 0.187 · T30 (file 23, question 1):
  - The 1 kHz margin over the rendered floor is 32 to 35 dB at the end of speech. That equals 46 − 13.1 = 32.9,
    the decider's D2-L1 input, and the heard D/R is a real heard property.
  - The margin holds about level for 0.1 s, then falls at 46 dB/s (fitted over boundaries 5–60: the tail's own
    T60 of 1.30 s).
  - It crosses 20 dB at 0.375 s. In units of the tail's own decay that is 0.29 · T60.
  - D2-L1 therefore stands as a computation, and "not a malfunction" holds. The early cutoff is the tail falling
    through floor + 20 dB at its own Eyring rate.
- None of these numbers changes with this check, because the kit's Q5 T30 is unchanged. If the decider moves Q5
  onto the tail's T30 (≈ 1.26 s), they all change: the pause, the 0.43 ceiling (0.54 s) and the window in T units.

## Kit change (print and manifest only; no stimulus changes)

`tools/ci/abx_kit.py`:
- `check_scene` keeps every existing field: the heard D/R, `T30_1k_s` and `r_c_m`. Its Q5 / noise-gap T30 is
  unchanged, and so are the stimuli. It adds:
  - `DRR_basis`;
  - `r_c_m_T30`;
  - per emitter (`emitter_ir_metrics`): own D/R broadband and 1 kHz, whole-IR T30/EDT (1 kHz), t_mix, tail-alone
    T30/EDT (1 kHz), and the target T60.
  - The log line now labels the summed values "heard (L + R)".
  - The r_c comment cites Kuttruff Eq. 5.44.
- `build_speech_chain` records, through `q5_window_record`: the realised window in T30, the passing indices,
  contiguity, the first-draw replacement probability (N − K)/N, the expected replaced onsets per stimulus
  (N − K)/(K + 1), and the per-boundary margins.

`tools/ci/test_abx_kit.py` pins these:
- `test_q5_window_record`: the formulas, including a Monte Carlo of the permutation draw (46/36).
- `test_noise_trial_end_to_end`: heard D/R minus per-emitter D/R between 2 and 4 dB; the tail-alone T30 within
  10 % of the target T60; the whole-IR T30 above 1.3 × the tail T30.

The noise chain was rerun in full with the kit change (`abx_kit.py noise`, release `render_cli`). All 44 trials
(2 blocks × 22) and the 6 IR step pairs passed every item-6 assertion, exit 0, in 2 min 24 s. The stimuli are
byte-identical to the kit at d04118a on the same binary: the SHA-256 of A and B agree for trials 1–2 of both
blocks, checked with `--trials 2`. The speech chain was rerun with `--trials 1`, and its checks passed.
`pytest tools/ci` (with `SPATIAL_REQUIRE_RENDER_CLI=1`) gives 136 passed, and `check_format.sh` reports 115 files
clean.

Files: /home/user/makroof/tools/ci/abx_kit.py, /home/user/makroof/tools/ci/test_abx_kit.py,
/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md, /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md
(Eq. 5.43–5.48, Table 5.2), /home/user/makroof/docs/BUILD_PLAN.md (AX21).
