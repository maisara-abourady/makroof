# AX47 self-ABX and AX49 L4: run sheet (phase 07c-2 D-W2, as amended by phase 07c-2b M3)

This sheet is for the decision listener (Maisara or the listener she names) and for whoever runs the session.
The design was pre-registered by the board before any stimulus was heard. Nothing on this sheet changes it except the
amendments in §0, each made by a board decision before any stimulus was heard. The source is
`docs/review/phase-07c-2/13-decider-rebuttal-r4.md`, "D-W2: final", items 1–16, and its section "Q5: TSP step
placement (pre-registered)", which interrogator file 14 rated SURVIVES. Every number below is copied from
there. Where the kit had to make a choice that file 13 does not make, the choice is marked **kit choice**.

## 0. Amendments to file 13 (phase-07c-2b M3; decider files 2, 6, 9, 13, 17, 21; interrogator files 3, 7, 10, 15, 20 (its check of file 17) and 23 (its check of file 21))

- **Items 2–3:** each chain of each family has 24 scored trials + 6 interleaved 3 dB anchors (3 per half, break after
  presentation 15); 0.9 dB, then 0.5 dB only after a 0.9 dB detection in that chain of that family; detection
  ≥ 18/24; anchor ≥ 5/6 (M3-2). Fallback: §4.
- **Item 4:** applies across F1–F4 (§4).
- **Item 5's clause:** "[S-A only …]" replaced (§1).
- **Item 9:** two scenes, F1 S-W `layout4_s1/both_wall` and F2 S-B\* `layout4_s0.7/default`, with their labels and
  fallbacks (§1).
- **Item 13:** the record wording, with the heard step (§6).
- **Item 14:** L4 design (M3-L4, decider file 9), its band coverage amended by decider files 13 and 21 after the first
  build's red (4 kHz −22.94 dB), before any scored trial (§7).
- **Item 15:** the 08-3 binaural rerun, now in `docs/phases/phase-08-3.md`.
- **M3-6:** the speech pair rule (§3). **M3-8:** the rebuild trigger (§1). **C-b:** the two-measure tail-spread print
  (§1).

## 1. What is being tested

When the plugin replaces an interim reverb with the final one, the reverb tail changes level in one step. The
step is a 30 ms equal-gain crossfade (AQ4, AX18). The test asks whether one listener can hear such a step, in an
ABX test.

- **The step:** a change of g dB in tail energy, uniform across all 8 bands. The two IrSets come from one
  StagedBuild through `useDiffuseLevel`. The early sound is bit-identical, and only the tail changes (item 5).
  - **What item 5 scales** (decider file 34, item 1, verbatim; it replaces file 27's sentence and the earlier
    file 21 wording, under M1 A, file 31):

    > Item 5 scales the whole tail target E_target = E_spec + E_diff by k = 10^(g/10). Cli L788, read with Engine
    > L181–183, sets E′_diff = k·E_diff + (k−1)·E_spec, so E′_target = k·E_target. A band with E_spec = 0 is scaled
    > directly (L776–779), with the same result. The rendered window from t_mix,e + 2.5 ms onward holds no images
    > (NoiseTail L278–279; MixingTime.h L27). So the whole window waveform scales by 10^(g/20), and item 6's identity
    > is exact at any specular share of E_target (test_cli.cpp L350–358 asserts it at share ≈ 0.74). The only
    > unscaled energy in [t_mix,e, L) is the 2.5 ms ISM fade-out. It lies inside the 0.1 dB window tolerance
    > whenever its share s_w ≤ 2.3 %; s_w is printed and asserted. The kit refuses three cases:
    > - (a) a scene with no diffuse tail level, at any g (L755–758);
    > - (b) a step that would need negative diffuse energy, i.e. k < share of E_target (L788–795);
    > - (c) a band with a specular-only tail, i.e. E_spec ≠ 0 with E_diff ≤ 0 or no diffuse reference, when g ≠ 0
    >   (L762, L781–786).
    >
    > [every ABX scene with s = 1 on all faces (layout4_s1/both_wall or its sealed fallback): E_spec = 0 in every
    > band (AX21; Kuttruff Eq. 8.59), so this equals scaling E_b alone.] [layout4_s0.7/default: the target specular
    > share is up to 0.032 (max over bands and emitters, file 29), so scaling E_b alone would give 0.87 dB, not 0.9
    > (10·log10(0.032 + 1.2303 × 0.968) = 0.874 dB). Item 6's identity is asserted there, and M1's reversal condition
    > is live on this scene.]

  - **What the manifest prints for it** (item 6; decider file 27, amendment 1 and "specular_share print", applied
    under file 31): per emitter and output, `window_unscaled_share` (s_w, the exact split N = (a·u − s)/(a − 1),
    a = 10^(g/20), as E(N)/E(u) over [t_mix,e, L)), per band and broadband, asserted ≤ 2.3 %; beside it, under its
    own name, render_cli's `target_specular_share` (E_target's specular share per band, a level target, not a
    waveform in the window); and, on the heard IR pair at each g, per band and broadband, the tail-window share of
    the heard energy, ΔG and ΔC80 (C80 per Vorländer Eq. 6.7, late window 80 ms to the end of the IR; file 29's
    method). These are prints; none changes a stimulus.
- **B** is the unstepped render, held throughout. **A** carries the step. **X** is either A or B (item 7).
- **Directions:** in each block, half the scored trials step up and half step down (12 and 12), in random order
  (item 7).
- **Timing:** at least one T30 of programme comes before the step, and at least 2 s after it (item 7).
- **Which T30 (M2 T-a, decider files 31 and 34).** The gaps, pauses and the Q5 onset window use T30(1 kHz) of the
  heard IR (S-A, history: 2.009 s on layout4_s1/default). The manifest labels it (Seat 9): **"heard-IR T30, ISO fit
  spanning the AX21 gap, not a decay rate"**, with the tail T30 beside it (S-A, history: **tail T30(1 kHz) 1.254 /
  1.274 s**, emitters L / R, from t_mix,e; the diffuse target's Eyring T60 is 1.291 s). Manifest fields:
  `scene.T30_1k_s`, `scene.T30_1k_s_label`, `scene.tail_T30_1k_s`. Each sealed scene's values are printed and used
  instead: both_wall heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s; s0.7 heard-IR T30 1.831 s, tail T30 1.254 /
  1.274 s; the Q5 window is recomputed per sealed scene.
- **M2 debt check, before each seal (decider file 34, item 3).** For each sealed scene the manifest prints the
  minimum gap, the heard-IR T30 and the tail T30, and asserts minimum gap ≥ tail T30 (`m2_gap_check`); the build
  stops if it fails. With the speech chain it must also pass Q5's ≥ 20 dB onset assertion. S-A, history: on S-A the
  noise chain's minimum gap is 2.016 s against tail T30 1.254 / 1.274 s. The check matters for any other scene M3 or
  item 15(i) seals: T-a's harmlessness rests on the gap exceeding the tail's own decay, which fails on layout 5
  (heard 2.557–2.575 s against tail-alone 2.58–2.62 s, K4 fact 9).
- **Scenes (item 9, M3-1):** F1 S-W and F2 S-B\*, labels below; fixed tailSeed 12345 (**kit choice**); each asserted
  capped at m = 6, 7, 8; D/R per emitter and heard, printed. **S-W fallback order** (by tail share; the first that
  passes every gate): listener_corner, listener_edge, both_corner, emitter_wall, listener_wall; if none with share
  ≥ 0.129 passes, M3 returns to the board. **S-B\* fallback:** `layout4_s0.9/default`. Fallback labels use the S-W
  template below with their own values, name every face whose reflection is absent, and are confirmed by Seat 9
  before the seal.
  - **S-W label** (decider file 9 §6, verbatim): "layout4_s1/both_wall: 20 × 30 × 10 m, 6,000 m³, walls and ceiling
    α 0.01, floor α 1, scattering 1 on every face. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the
    y = 30 m wall; listener–emitter 29.95 / 20.13 m (L / R). The reflections off those faces (delay about 0.58 ms;
    first interference notch near 0.86 kHz, Kuttruff Eq. 7.6) are absent at s = 1 (AX21; Kuttruff Eq. 8.59), so the
    direct sound's tone colour is not room-like and the scene represents no seat. D/R at 1 kHz −7.7 / +5.2 dB per
    emitter, −5.3 dB heard (emitter L's direct arrives 28.6 ms after R's and counts as reflected); diffuse field
    −18.5 / −15.0 dB at r/r_c 8.39 / 5.64 (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only:
    ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Tail onsets t_mix,e 0.165 / 0.380 s (L / R; the engine's t_mix,e rule).
    The decays agree within 0.05 dB at equal times, but from its own onset L's 1 kHz tail energy is +9.4 dB over R's
    at equal source power, where a diffuse room gives equal reverberant levels (Kuttruff Eq. 5.42; indicative). This
    is engine behaviour, not room geometry; the tail share 0.667 at 1 kHz rests on it and changes with the t_mix,e
    rule (M3-8). Early part empty (AX21). Heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s. Not a validated preset."
  - **S-B\* label** (decider file 6, with Seat 9's SPREAD clause, 14-seat9 §2): "layout4_s0.7/default: 20 × 30 × 10 m,
    6,000 m³, walls and ceiling α 0.01, floor α 1 (no floor reflection, unlike a real floor), scattering 0.7 on every
    face. D/R at 1 kHz +1.5 / +1.3 dB per emitter, +1.7 dB heard, against −10.8 dB in a diffuse field at r/r_c 3.47
    (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Early
    part present but specular-only (partial AX21): first image (ceiling) about 23.6 ms after the direct sound;
    broadband early energy −3.8 dB re direct; the step at t_mix,e is printed. Tail target Eyring 1.29 s at 1 kHz, a
    diffuse target, not a room prediction; heard-IR T30 1.831 s spans early part and tail; tail T30 1.254 / 1.274 s.
    At equal source power the emitter tails at the listener differ at 1 kHz by −1.2 dB (L − R), integrated from their
    common onset t_mix,e 0.380 s; −0.2 / −0.7 dB in the equal windows [0.45, 0.65) / [0.8, 1.0) s. A diffuse room
    gives equal reverberant levels (Kuttruff Eq. 5.42), but with all absorption on the floor this room is not diffuse
    (§5.6), so the spread is not attributed to engine or room; reported under NFR-8. Not a validated preset."
  - **S-W fallback template** (Seat 9, `docs/review/phase-07c-2b/4-seat9.md` R2-2; NEAR-FACE names each face, and
    "Tail onsets t_mix,e {a} / {b} s" stands before {SPREAD}, decider file 6): "layout4_s1/{p}: 20 × 30 × 10 m,
    6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Listener ({x,y,z}) m; emitters L
    ({…}), R ({…}); listener–emitter {r_L} / {r_R} m. {NEAR-FACE} D/R at 1 kHz {L} / {R} dB per emitter, {H} dB
    heard{HEARD}; diffuse field {dL} / {dR} dB at r/r_c {qL} / {qR} (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45;
    indicative only, ᾱ ≈ 0.28 is not small). Tail onsets t_mix,e {a} / {b} s. {SPREAD} Early part empty (AX21).
    Heard-IR T30 {h} s, tail T30 {t} s. Not a validated preset."
    - **NEAR-FACE, listener within 0.1 m of n faces:** "The reflections off the {faces} at the listener are absent at
      s = 1 (AX21), so the direct sound's tone colour is not room-like and the scene represents no seat." If one of
      those faces is the floor, add "(the floor reflection is absent at any s: α 1)".
    - **NEAR-FACE, emitter only:** "…the reflections off the face at emitter L are absent at s = 1 (AX21), so its tone
      colour is not that of a source at a wall; the listener position is ordinary."
    - **HEARD:** used if the two direct arrivals differ by more than the AX13 direct window: " (emitter {X}'s direct
      arrives {Δt} ms later and counts as reflected)".
    - **SPREAD** (C-b), in two forms: the **onset form**, the S-W label's onset text above (Seat 9's C-a, from "Tail
      onsets t_mix,e" to "(M3-8).") with the scene's values; the **level form**, Seat 9's R2-2 text ("Emitter tails at
      the listener differ by {x} dB at equal source power; this is the engine, not room physics (Kuttruff Eq. 5.42);
      reported under NFR-8.") or the non-attributing S-B\* form above, at Seat 9's call when it confirms the filled
      label.
- **Tail-spread print (C-b), before each seal:** L − R at 1 kHz (i) integrated from each emitter's own t_mix,e to the
  end of the IR, (ii) over [0.45, 0.65) and [0.8, 1.0) s; on S-B\* also [0.380, 0.45) s (print only). On S-W and its
  fallbacks, either measure > 1 dB (a print threshold, not an audibility claim) requires the SPREAD clause in the
  label; every firing goes to the board (home pending Maisara's answer on M3-H,
  `docs/review/phase-07c-2b/24-m3h-for-maisara.md`) as an NFR-8 candidate.
- **S-B\* step/dip print:** the AX21 step and dip at t_mix,e per band and emitter, [t_mix,e − 20, t_mix,e − 2.5) ms
  against [t_mix,e + 2.5, t_mix,e + 20) ms.
- **Q5 on both_wall (kit choice):** the onset window counts from the latest heard end of speech (input end plus the
  largest emitter direct delay).
- **Rebuild trigger (M3-8):** "On any `src/sim` change that alters a sealed scene's rendered IR (B11 promotion, the
  t_mix,e rule, estimator constants), the stimuli are rebuilt, pass every seal gate again, and their hashes are
  re-registered before the next listening session. Earlier results stand, each recorded with the engine it was
  obtained on."
- **r_c in the manifest:** the kit's "0.057·√(V/T60_Eyring)" is named as such; labels use Kuttruff Eq. 5.44
  (A/16π)^½ with A = Σ S·α + 4mV.
- **Signals (item 8):**
  - **Noise chain:** pulsed pink noise, with gaps ≥ T30(1 kHz) and the step at the start of a gap.
  - **Speech chain:** McGill TSP v2 at 48 kHz, one adult speaker and one file pair, with a pause ≥ T30 between
    them. The onset falls in the pause, no later than 0.43 · T30(1 kHz) after the end of speech (Q5).
    - **Realised Q5 onset window, recorded before sealing** (S-A, history; decider file 21, 2a; measured in
      `docs/review/phase-07c-2/22-drr-t30-check.md` on the kit's smoke pair MA01_01 / MA01_02; the kit recomputes
      and records them for whichever pair is pre-registered): accepted onsets lie in
      **[0, 0.187 · T30]** after the end of speech (0.0007 to 0.1865 · T30, i.e. 1.3 ms to 0.375 s, T30(1 kHz) of the
      heard IR = 2.009 s). 35 of the 81 boundaries in the 0.43 · T30 ceiling pass the ≥ 20 dB assertion: boundaries
      0–33 and 35 (boundary 34 misses by 0.6 dB), so the passing set is not strictly contiguous.
    - **Expected replacement rate:** a stimulus's first seeded onset is replaced with probability 46/81 = 0.568; the
      expected number of replaced onsets per stimulus is 46/36 = 1.28 (draws without replacement, interrogator
      file 23). Both are written into the speech `manifest.json` (`tsp.q5_realised_window_T30`,
      `tsp.q5_first_draw_replaced_p`, `tsp.q5_expected_replaced_per_stimulus`, `tsp.q5_passing_boundary_indices`).

## 2. Equipment and presentation (item 10)

| requirement | record here |
|---|---|
| Omni render, presented **diotically** (both ears get the same signal; the files' two channels are identical) | — |
| **Wired** headphones; write down the model | model: ______________________ |
| A fixed level, at or above monitoring level, kept the same for the whole session; write down how it was set | level / setting: ______________________ |
| **No normalisation** of A, B or X (play the files as they are) | — |
| 48 kHz, no resampling: the output device runs at 48 kHz | device and rate: ______________________ |
| No virtualisers, no enhancers, no ReplayGain, no Bluetooth | checked: ☐ |
| Whole pre-rendered files are played. No live switching and no visual cue (item 7). Use a player that plays one file at a time and shows no waveform. | player: ______________________ |

## 3. Before the session (items 1, 11, 12, 16)

1. **Name the listener** in the pre-registration. Only one decision listener takes part. A further listener
   must be pre-registered as well, and then α is split by Bonferroni. The results hold for that listener only
   (item 1).
2. **Fix the speech material** in the pre-registration: one adult TSP speaker and one file pair (item 8). Speaker
   MA, files MA01_01 and MA01_02 (M3-6). Fallback order: MA01_03 / MA01_04, then the first two files of the next adult
   speaker in the archive's alphabetical directory order (CA, CB excluded); the first pair that passes Q5 on every
   sealed scene is used in all four families.
   - The children CA and CB are excluded.
3. **Build the stimuli** on a machine with `render_cli` built (`cmake --preset cli && cmake --build --preset cli`),
   per scene, each in its own output directory (S-W and S-B\*, §1; L4: §7).
   - Noise chain: `python tools/ci/abx_kit.py noise --scene layout4_s1/both_wall --out build/abx-07c-2b/s-w` and
     `python tools/ci/abx_kit.py noise --scene layout4_s0.7/default --out build/abx-07c-2b/s-b`. The CI
     `listening-pack` artifact (`phase-07c-2/noise/`) holds the same files.
   - Speech chain, local only: `python tools/ci/abx_kit.py speech --scene layout4_s1/both_wall --out build/abx-07c-2b/s-w
     --speaker <S> --files <F1> <F2>` and `python tools/ci/abx_kit.py speech --scene layout4_s0.7/default --out
     build/abx-07c-2b/s-b --speaker <S> --files <F1> <F2>`.
     The script downloads `48k.zip`, checks it against our SHA-256 and writes `NOTICE-TSP.txt`. Never commit or
     upload these files (item 12).
   - Each build runs every item-6 assertion on every stimulus, and stops if any fails. The assertions are: early
     parts bit-identical, the stated tail step, the window's unscaled share s_w ≤ 2.3 %, the `[ax47-midfade]`
     checks, HF-W (β 1.1378) with condition D and N1–N3, and, for speech, Q5's tail ≥ floor + 20 dB at the onset. It also stops if
     the M2 gap check (minimum gap ≥ tail T30) fails.
   - `manifest.json` records the measured values, every stimulus's SHA-256 and, for speech, the excerpt's SHA-256
     and every replaced onset.
   - L4: `python tools/ci/ax49_l4.py build --out build/abx-07c-2b` (pack `build/abx-07c-2b/l4`).
4. **Seal** each chain of each scene: `python tools/ci/abx_kit.py seal --pack build/abx-07c-2b/<s-w|s-b>/<chain>
   --session <session dir> --key <key file>`.
   - Keep the key file outside the session folder. The listener must not see it.
   - The session folder holds only `<level>dB/trial_NN/{A,B,X}.wav`.
   - Commit `<key file stem>-prereg.json`, written beside the key, **before the run**. It holds the key's SHA-256
     and a salted SHA-256 of every A, B and X (item 11). Each file has its own secret salt, kept in the key. Plain
     hashes would give the answers away, because X is a byte copy of A or B. `score` checks the session folder
     and the key against this record.
   - Never give the listener the unsealed pack (`build/abx-07c-2b/<s-w|s-b>/<chain>/`).
   - The pre-registration commit holds both scenes' prereg records and L4's sealed hashes, before the first scored
     trial. **Seal preconditions:** S-W: Seat 9 confirms the filled label. S-B\*: the SPREAD clause above is in the
     label (Seat 9's (e) answer, 14-seat9) and Seat 1 has answered Seat 9's question whether the −1.2 dB spread
     changes what the S-B\* null covers. L4: §7.
5. **Date the session** in the session brief (item 16). If neither 07c-2 nor 07c-2b can hold it, it goes to
   Maisara as a person's action. The builder times one speech block and L4 before the dates are fixed.

## 4. Procedure

- **Familiarisation, before any scored block (mandatory, BS.1116-3 §4.1; item 2).**
  - Play the labelled pairs in `familiarisation/`: the 3 dB anchor and each step size, up and down. A is
    stepped and B is not.
  - Whether feedback is given during familiarisation is Seat 1's design choice. It is **not set by this kit**.
    Record what was done: ______________________
- **Blocks (item 2).** 30 presentations: 24 scored trials and 6 interleaved anchors (a uniform 3 dB tail step),
  3 anchors in each half; break after presentation 15. No feedback is given in scored blocks.
- **Each trial.** Listen to A, B and X, as often as you like, as whole files. Then write down whether X is A or B.
  Every trial needs an answer: guess if you are unsure.

### Trial counts and pass criteria (items 2, 3, as amended in §0)

| family | scene | chain | first test | second test (only after a 0.9 dB detection in that chain of that family) | anchor |
|---|---|---|---|---|---|
| F1 | S-W | noise | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
| F1 | S-W | speech | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
| F2 | S-B\* | noise | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |
| F2 | S-B\* | speech | 0.9 dB at ≥ 18/24 | 0.5 dB at ≥ 18/24 | 6 per block, ≥ 5/6 |

- Family: ≤ 0.0227 per family (2 × 190051/2²⁴, union bound), ≤ 0.0453 at 07c-2b, ≤ 0.0906 with 08-3's F3/F4; power
  0.607 per chain at p = 0.75; no α passes between chains or families. If the trial count is cut (only in the
  pre-registration commit, before any scored trial), all four families revert to file 13's unsplit thresholds (noise
  ≥ 12/16, speech ≥ 13/16) with C1; never 13/13.

### Fixed-sequence stopping rule (items 3, 4, 11)

1. In each chain, run the **0.9 dB** block first.
2. Run the **0.5 dB** block of that chain **only if 0.9 dB was detected in that chain**. The scoring script
   refuses to unseal a 0.5 dB block otherwise.
3. If a block's anchor fails (fewer than 5 of 6 correct), the block is void. It gets **one rerun**, and it is
   never recorded as "not detected". A non-detection is never a reason to rerun.
4. What follows from the results: a detection at 0.9 dB in any chain of any family (F1–F4) sets AX47's bound to
   0.5 dB for all scenes; a non-detection never cancels a detection. A detection at 0.5 dB is a class (c) finding;
   at 08-3 it reopens that round at the board.

**Order:** S-W (noise 0.9 dB first, then speech), then S-B\*, then L4 alone after a rest, the same day as the S-B\*
sitting; sittings ≤ 2 h, split only at a chain boundary.

## 5. Response tables

Write X's answer (A or B) per presentation. One table per family, chain and level, presentations 1–15 | break | 16–30
(`abx_kit.py blank` writes them; anchor positions are in the key only). 0.5 dB tables are headed 'only after a 0.9 dB
detection in this chain of this family'. The same table as CSV:
`python tools/ci/abx_kit.py blank --chain <chain> --out responses-<chain>.csv`. Score it with
`python tools/ci/abx_kit.py score --key <key file> --session <session dir> --responses responses-<chain>.csv --chain <chain>`.

### F1 (S-W), noise chain, 0.9 dB block

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F1 (S-W), noise chain, 0.5 dB block (only after a 0.9 dB detection in this chain of this family)

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F1 (S-W), speech chain, 0.9 dB block

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F1 (S-W), speech chain, 0.5 dB block (only after a 0.9 dB detection in this chain of this family)

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F2 (S-B\*), noise chain, 0.9 dB block

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F2 (S-B\*), noise chain, 0.5 dB block (only after a 0.9 dB detection in this chain of this family)

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F2 (S-B\*), speech chain, 0.9 dB block

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

### F2 (S-B\*), speech chain, 0.5 dB block (only after a 0.9 dB detection in this chain of this family)

| presentation | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

*(break)*

| presentation | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | | | | | |

## 6. Where to record the results (item 13)

Record the results in `docs/validation/abx-07c-2-results.md` (create it at the run) and in the session brief's
dated item. Do not commit audio, and do not make a public copy of the speech stimuli.

| listener | family | scene | chain | level (dB) | k/24 | exact p | anchor k/6 | heard ΔG / ΔC80 at 1 kHz (manifest) | scene hash | tailSeed | commit | wording |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| | F1 | S-W | noise | 0.9 | | | | | | 12345 | | |
| | F1 | S-W | noise | 0.5 | | | | | | 12345 | | |
| | F1 | S-W | speech | 0.9 | | | | | | 12345 | | |
| | F1 | S-W | speech | 0.5 | | | | | | 12345 | | |
| | F2 | S-B\* | noise | 0.9 | | | | | | 12345 | | |
| | F2 | S-B\* | noise | 0.5 | | | | | | 12345 | | |
| | F2 | S-B\* | speech | 0.9 | | | | | | 12345 | | |
| | F2 | S-B\* | speech | 0.5 | | | | | | 12345 | | |

- `score` prints k/24, the exact p and the anchor k/6. The scene hash is `scene_sha256` in `manifest.json`. The
  commit is the one the stimuli were built from.
- **Wording (item 13):**
  - "detected (≥ 18/24, family α 0.0227)";
  - S-W: "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on layout4_s1/both_wall (tail share
    0.667 at 1 kHz, resting on the engine's t_mix,e onsets 0.165 / 0.380 s (own-onset tail L − R +9.4 dB; −0.05 dB
    at equal times); listener and emitter 0.1 m from a face); heard step at 1 kHz ΔG +0.62 dB, ΔC80 −0.90 dB for the
    0.9 dB tail step [0.5 dB: ΔG and ΔC80 as printed in the manifest], at the recorded commit; void as evidence for
    this scene after a t_mix,e change until rebuilt (M3-8)." (Seat 1, 14-seat1 §6; Seat 9's record line);
  - S-B\* (decider's composition from Seat 1's form; Seat 1 confirms before the S-B\* seal): "not detected in 24
    trials by one listener (power 0.61 at p = 0.75) on layout4_s0.7/default (tail share {printed} at 1 kHz; tail
    onsets 0.380 / 0.380 s; tail spread L − R −1.2 dB from the common onset, not attributed; early part
    specular-only, partial AX21); heard step at 1 kHz ΔG {printed} dB, ΔC80 {printed} dB for the 0.9 dB tail step
    [0.5 dB: as printed in the manifest], at the recorded commit; void as evidence for this scene after an M3-8
    trigger until rebuilt.";
  - "inconclusive" if the anchor failed.
  - ΔG and ΔC80 are taken from the manifest, never typed by hand. "A non-detection is recorded for its scene class
    only; the 1 dB bound elsewhere rests on D-C1, as AX47 states." The record states each family's α, the union rate
    and which family detected at what count. Never write "inaudible"; no public copy.

## 7. AX49 L4: the held-chord ABX (item 14, as amended by M3-L4 and decider files 13 and 21)

- **Design (L4-A on S′):** A = AX49 provisional tail (`Engine::assembleProvisional`, `render_cli --ax49-provisional`),
  faded over [L_f, L_p) = [3.6135, 3.7135) s; B = the exact tail; one tailSeed for both; fully wet; omni diotic. Seat
  1's chord ('l4-chord-v1', 4-seat1 L96–121; kit seeds 4901/4902/4903). 16 scored trials + 6 anchors (3 dB, ≥ 5/6);
  detected at ≥ 12/16; α 2517/65536 = 0.0384, its own family; power 0.630 at p = 0.75.
- **Label (Seat 9, 14-seat9 §3, verbatim):** "ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10⁶ m³, every face the
  same α per band, scattering 0.3. Listener (50, 30, 1.7) m; emitters (45, 70, 2) and (55, 70, 2) m, each 40.3 m from
  the listener. T60 8.0 ± 0.1 s from 63 Hz to 1 kHz as printed by the engine (Eyring, T60_max 8 s, air absorption
  included), shorter above 1 kHz where α is held at its 1 kHz value; per-band T60 printed. D/R at 1 kHz {printed} dB
  heard, against about −6.5 dB in a diffuse field at r/r_c 2.1 (r_c ≈ 19 m from A = Σ S·α + 4mV ≈ 18,200 m² at 1 kHz,
  the label form; Kuttruff Eqs. 5.24–5.25, 5.44–5.45, Table 6.1; indicative only: ᾱ ≈ 0.23 at 1 kHz is not small,
  §5.6). A stress geometry for AX49's provisional tail, not a room prediction or a validated preset. A = AX49
  provisional tail (Engine::assembleProvisional, validation-only flag --ax49-provisional), faded over [L_f, L_p) =
  [3.6135, 3.7135) s; B = full engine tail ('exact' = full synthesis, not a measurement); one tailSeed {seed} for A
  and B. Fully wet: the whole rendered IR (direct, early part and tail), no dry path." Fill rule: ᾱ from the scene's
  1 kHz α and m from the engine's air table; if the back-solved α differs by > 0.005, both are printed. Seat 9
  confirms the filled text.
- **Band coverage (decider files 13 and 21, verbatim):** "Band coverage (Seat 1; amended by decider files 13 and 21
  after the first build's red, before any scored trial). (a) In the exact render's steady state (the last 1 s of the
  hold), every band from 63 Hz to 2 kHz is within 20 dB of the strongest band. (b) In the 100 ms where the cut begins
  (the fade [L_f, L_p) in written-file time: from the end of the chord's 10 ms release (sample `end`) plus
  round((L_f − alignmentShiftS)·fs); kit interpretation 2), the exact render's energy in every band from 63 Hz to
  2 kHz is within 20 dB of the strongest band in that same window (absolute band energies, not levels relative to each
  band's hold). Both are asserted. A red on either, at any build, is a stop and returns to the board; the reference
  band is not changed after a red. Printed beside them: 4 kHz and 8 kHz with their depth at L_f; the original clause
  (63 Hz–4 kHz) with its result (first build: 4 kHz −22.94 dB re 125 Hz, red); (b) against the median of
  63 Hz–1 kHz; and (b) for the exact arm over 16 further tailSeeds, run once by the builder before the seal and
  committed with the pre-registration commit (Seat 3; print only, not a CI step). The scope is a judgement on S′'s
  depth at L_f (63 Hz–1 kHz 18.72 dB, 2 kHz 23.19 dB, 4 kHz 40.14 dB; chord-independent), made after the red; no
  depth threshold was fixed in advance, and the null claims nothing at 4 kHz and above. First passing build (builder
  file 18): (a) weakest 2 kHz −15.83 dB, margin 4.17 dB; (b) strongest 125 Hz, weakest 2 kHz −17.71 dB, margin
  2.29 dB." Ensemble result (builder file 25; interrogator file 23 C7): the asserted (b) reds on 3 of 16 further
  tailSeeds (min −3.98, median +1.59 dB); the median-referenced form holds on all 16 (min 2.74 dB); the sealed seed
  passes at 2.29 dB. Negative control N-L4: the chord limited to partials ≤ 500 Hz fails (a) and (b).
- **Checks before the seal:** Seat 2's S′ asserts; Seat 3's P1–P6 and S1–S7, S2–S4 on the partition grid (IR time with
  +1·P; written-file time without it); N-L1–N-L4; in both arms the IR is installed in the first partition (no AQ4
  fade-in in the prefix); Seat 1's prefix check; F1–F6 and F2′ 1–4 of the flag; decider file 13 R1–R7; the Catch2
  `[ax49-l4]` case (P4/P5 at 1e−9, N-L1/N-L2 inside; tag exactly `[ax49-l4]`), run by ctest in Debug (Linux, macOS,
  Windows) and ASan (Linux) and by the 'AX49 L4 gate (release)' step on all three OS (Seat 5, option (c); decider
  file 21 §5); per run of the case Release ≤ 60 s, Debug ≤ 300 s, ASan ≤ 300 s, with Debug and ASan `--durations`
  and peak RSS recorded before the seal; seal evidence is a CI run, started by the session, whose fingerprint
  includes the sealed `tests/unit/test_ax49_l4.cpp`, green on all three OS with the `ax49-l4:` line; the L4 sitting
  is scheduled only after that run is green. A red is a stop, never loosened.
- **Timing:** built, all checks green, sealed, hashes in the pre-registration commit, before the first scored AX47
  trial. If the build stalls, AX47 listening waits and Seats 1, 3 and 7 are re-asked (frozen spec + C1–C3 is the
  pre-rated candidate).
- **Wording (Seat 9, 19-seat9, verbatim):** "not detected in 16 trials by one listener (power 0.63); ax49_l4_cube,
  T60 8.0 s at 63 Hz–1 kHz and 6.5 s at 2 kHz, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; no claim at
  4 kHz and above, where this scene's tail (T60 3.7 s, mostly air absorption in 10⁶ m³) has by L_f decayed 40 dB from
  its own onset, against 19 dB at 63 Hz–1 kHz." A detection fires AX49's Reversal: "worst case: provisional current
  through the whole free decay".

## 8. Not in this kit

- **The 08-3 binaural rerun (item 15):** now `docs/phases/phase-08-3.md`, item 15.
- **Kit choices file 13 does not fix:**
  - the noise level (−8 dBFS RMS before the room) and the burst length (1 s);
  - the onset's seeded range;
  - the end-of-speech rule: the last 10 ms frame above TSP's noise level + 15 dB;
  - the floor segment: the noise in TSP's lead-in;
  - the trial-plan seeds;
  - rendering at the shipped W.

  They are recorded in `manifest.json` and in `tools/ci/abx_kit.py`.
