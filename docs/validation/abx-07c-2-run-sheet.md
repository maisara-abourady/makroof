# AX47 self-ABX: run sheet (phase 07c-2, D-W2)

This sheet is for the decision listener (Maisara or the listener she names) and for whoever runs the session.
The design was pre-registered by the board before any stimulus was heard. Nothing on this sheet changes it. The
source is `docs/review/phase-07c-2/13-decider-rebuttal-r4.md`, "D-W2: final", items 1–16, and its section "Q5: TSP
step placement (pre-registered)", which interrogator file 14 rated SURVIVES. Every number below is copied from
there. Where the kit had to make a choice that file 13 does not make, the choice is marked **kit choice**.
Phase 07c-2b's board loop (`docs/review/phase-07c-2b/`, decider files 2, 5, 8 and 10, interrogator files 3, 6, 11 and
13) applied the amendments file 31 held for M3 (items 9, 13, 15), re-decided the gap construction (M3-G) and brought
AX49 L4 into this kit (§8). Values the kit measures when it builds the stimuli are marked **[measured at build]**.

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
    > [Scenes with s = 1 on every face:] There E_target's specular share is 0 in every band (AX21; file 29 fact 7),
    > so this equals scaling E_b alone (file 5's wording). On an s < 1 scene (the ABX scene E,
    > `layout5_s0.9/emitter_wall`: share 0.022 / 0.001) it does not, and M1's reversal condition (file 34 item 2) is
    > live there.

    (Clause from phase-07c-2b decider file 2, D-M3f; it replaces the S-A-only clause.)

  - **What the manifest prints for it** (item 6; decider file 27, amendment 1 and "specular_share print", applied
    under file 31): per emitter and output, `window_unscaled_share` (s_w, the exact split N = (a·u − s)/(a − 1),
    a = 10^(g/20), as E(N)/E(u) over [t_mix,e, L)), per band and broadband, asserted ≤ 2.3 %; beside it, under its
    own name, render_cli's `target_specular_share` (E_target's specular share per band, a level target, not a
    waveform in the window); and, on the heard IR pair at each g, per band and broadband, the tail-window share of
    the heard energy, ΔG and ΔC80 (C80 per Vorländer Eq. 6.7, late window 80 ms to the end of the IR; file 29's
    method). These are prints; none changes a stimulus.
- **B** is the unstepped render, held throughout. **A** carries the step. **X** is either A or B (item 7).
- **Directions:** in each block, 8 trials step up and 8 step down, in random order (item 7).
- **Timing:** at least one T of programme comes before the step (T as below), and at least 2 s after it (item 7).
- **Which T30 (M2 T-a, decider files 31 and 34; construction re-decided by M3-G, phase-07c-2b decider files 8 and
  10 Part B).** Every gap, pause and the item-7 lead is built from **T = max(heard-IR T30, every tail T30) at 1 kHz**.
  Q5's ceiling stays 0.43 × the heard-IR T30 (T-a, unchanged; file 40, 2a stands). On the ABX scene
  (`layout5_s0.9/emitter_wall`) the heard-IR T30 is 2.560 s and the tail T30 2.582 / 2.600 s, so T = 2.600 s. The
  manifest labels the heard value per scene class (phase-07c-2b decider file 25, ruling (i); interrogator file 28):
  on s = 1 scenes (S-A) **"heard-IR T30, ISO fit spanning the AX21 gap, not a decay rate"** (Seat 9's text, pinned
  by M2); on s < 1 scenes, E included, **"heard-IR T30, ISO fit spanning the early part, not a decay rate"** (file 8,
  M3-S). The tail T30 is printed beside it (per emitter, from t_mix,e). Manifest fields: `scene.T30_1k_s`,
  `scene.T30_1k_s_label`, `scene.tail_T30_1k_s`. In plain words: every gap and pause, and the silence after the
  step, is at least the longer of the measured reverberation times, as heard (the lead-in silence is excluded).
- **Gap and pause construction (M3-G; it replaces the construction premise of phase-07c-2 decider file 34 item 3,
  whose gap ≥ tail T30 check fails on layout 5 under the heard rule: heard 2.557–2.575 s against tail-alone
  2.58–2.62 s, K4 fact 9).** Every quantity is taken as heard: for each emitter e, d_e is the direct delay in the
  aligned IR (samples), Δ = max d_e − min d_e (28.4 ms on the ABX scene), P the partition.
  - **Noise chain.** Each gap between bursts is ⌈(T·fs + Δ)/P⌉·P samples. N (the step) is the first partition
    boundary at or after the heard end of burst 2. Burst 3 starts at N + ⌈T·fs/P⌉·P. On the ABX scene: gap 126464
    samples, heard gap 2.606 s ≥ 2.600 s.
  - **Speech chain.** Sentence 2 starts at the input end of sentence 1 + ⌈(0.43·T_heard + T)·fs⌉ + Δ samples
    (T_heard the heard-IR T30). Onsets lie at or after the heard end of sentence 1 and no later than 0.43·T_heard
    after the end of speech (Q5). On the ABX scene this adds about 1.2 s per speech stimulus (pause 3.729 s against
    2.560 s); K6's redo carries it (about +0.08 h).
- **M2 debt check, before each seal (decider file 34, item 3, on the heard quantities of M3-G).** Asserted per
  stimulus; the build stops if any fails:
  1. N ≥ the heard end of the burst before it, for every emitter;
  2. heard silence after N (noise) or after the onset (speech) ≥ T;
  3. every heard gap or pause ≥ T;
  4. M2 (`m2_gap_check`, on heard quantities): the minimum heard gap and the heard silence after the step are each
     ≥ every tail T30;
  5. item 7: at least one T of programme before N, and at least 2 s after it.

  The manifest prints the minimum gap, the heard-IR T30 and the tail T30. With the speech chain Q5's ≥ 20 dB onset
  assertion must also pass. Before M3-G, on S-A, the noise chain's minimum gap was 2.016 s against tail T30
  1.254 / 1.274 s.
- **Scene (item 9, M3-S; phase-07c-2b decider file 8 "DECISION M3-S", ITDG line from decider file 10 Part B;
  interrogator files 11 and 13):** **`layout5_s0.9/emitter_wall`** (scene E), the only scene this kit seals.
  - 20 × 30 × 10 m; the x = 0 wall (30 × 10 m) at α 1, the other faces at α 0.01; s = 0.9 on every face in every
    band; tailSeed 12345; 48 kHz. Listener (10, 8, 1.7); S0 (7, 29.9, 2) at 22.1 m; S1 (13, 20, 2) at 12.4 m.
  - The kit asserts that the scene is capped at m = 6, 7 and 8. r/r_c is 8.46 / 4.74; diffuse-field D/R −18.6 /
    −13.5 dB (Kuttruff Eq. 5.44, Sabine A ≈ 343 m², ᾱ ≈ 0.145). The kit prints r/r_c and D/R into the manifest: per
    emitter (each emitter's own IR) and of the heard IR (L + R summed).
  - The scene JSON is committed with the kit, and its SHA-256 goes in the manifest.
  - Fallbacks, in order, if any pre-seal check fails: `layout5_s0.8/emitter_wall` (D), then `layout5_s0.8/default`
    (B), each with its own check before its seal. The kit picks the scene with `--scene-name` (default
    `layout5_s0.9/emitter_wall`; a fallback only in the order D, then B; builder file 12, decider file 25 ruling (ii)).
  - Item-9 label, quoted verbatim from the kit's M3-S text (`tools/ci/abx_kit.py` `E_LABEL`, `E_LABEL_DETAIL`), which
    is authoritative (decider file 25, ruling (ii)). `label`: **"Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall,
    specular-only early reflections (s 0.9, AX21); not a validated preset"**. `label_detail`:
    - S0 22.1 m away; direct-path difference 28.4 ms.
    - D/R −12.7 / −5.0 dB, heard −9.5 dB, against −18.6 / −13.5 dB at r/r_c 8.46 / 4.74 (Sabine A ≈ 343 m²).
      Indicative only: ᾱ ≈ 0.145 and one face at α 1; Kuttruff §5.6–5.7 says these relations are questionable when
      ᾱ is not small, and one fully absorbing face is a severe deviation from diffuse conditions.
    - ITDG 0.6 ms (S0's wall image, notch ≈ 860 Hz), 0.89 ms (S0's floor image, notch ≈ 560 Hz) and 1.6 ms (S1's
      floor image, notch ≈ 320 Hz), all inside the ±2.5 ms direct window and counted as direct; specular amplitude
      √(0.99 × 0.1) = 0.315 (+2.4 / −3.3 dB at the wall image).
    - Near-wall emitter; its LF image is under-represented (one broadband s).
    - Early part −8.6 dB re direct; the scattered early energy is absent (AX21; the fix is deferred to the B11 rule).
    - Tail share 0.852 at 1 kHz.
    - Heard-IR T30 2.560 s, labelled "ISO fit spanning the early part, not a decay rate"; tail T30 2.582 / 2.600 s;
      Eyring 2.61 s.
    - Kuttruff Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s; the engine's tail follows Eyring.
    - Gaps are built from max(heard, tail) T30.
    - Class: tail-dominated (heard −9.5 dB, tail share 0.85), partial early part
    - Stimulus scene, not a room prediction.

    Outside the quoted label: Maisara decided on 2026-11-05 that the early part should contain scattered energy; the
    plan's AX21 row defers the fix to the B11 promotion rule.
  - The Class line above is the scene's class for item 13; the kit refuses to build a manifest without a Class line
    (D-M3e).
  - On this scene the specular share of E_target is 0.022 / 0.001, so M1's reversal condition is live (file 34
    item 1's "[s = 1 scenes]" clause, D-M3f); M1's per-band step identity is asserted at ≤ 0.05 dB (M3-C 7).
  - *Superseded record, not the ABX scene:* `layout4_s1/default` (S-A), the 07c-2 kit's scene, label "Direct-dominated
    test room, early reflections absent (AX21); not a validated preset" (D-M3g), with Kuttruff Table 5.2 case 4
    (floor α 1, others 0): iteration 1.21 s against Eyring 1.38 s; the engine's tail follows Eyring (C-c, M3-C 5).
    The S-A figures quoted elsewhere on this sheet (item 5's clause, the Q5 window below) were measured on it.
- **Signals (item 8):**
  - **Noise chain:** pulsed pink noise, with heard gaps ≥ T and the step at the start of a gap (construction above).
  - **Speech chain:** McGill TSP v2 at 48 kHz, adult speaker **MA**, one file pair chosen by the pre-registered pair
    search below (§3 item 2), with a heard pause ≥ T between them (construction above). The onset falls in the
    pause, no later than 0.43 · T30(1 kHz, heard IR) after the end of speech (Q5).
    - **Pre-registered text (phase-07c-2b decider file 34, DECISION I7 round 3, with interrogator file 36's
      corrections to the pair criteria; Seat 7 file 35 rated option (3) 0/0, so the pair search stands, n = 2):**

      **Item 7 (programme before the step).** Programme is counted from the first sample of the first programme
      file (sentence 1's TSP file); the kit's lead-in silence does not count. A speech onset is a candidate only if
      it lies (a) at or after the heard end of sentence 1 (D-M3b), (b) no later than 0.43·T_heard after the end of
      speech (Q5), and (c) at least lead + ⌈T·fs⌉ samples after the stimulus start (item 7), T being the construction
      T (M3-G).

      **Speech pair (pre-registered before E's seal; phase-07c-2b decider file 34).** The builder tries adult MA
      pairs in TSP index order (MA01_03 + MA01_04, MA01_05 + MA01_06, …, then MA02_…), recording every pair tried.
      The first pair that, on the scene in use, passes every pre-seal assertion of §1 and §3 item 3, among them: its
      earliest candidate boundary under (a) and (b) already satisfying (c) (no onset restriction), at least 34
      boundaries passing Q5's ≥ 20 dB assertion, form (b) green, B and E nulled within −120 dB, the M3-G silences
      asserted, item 10's peak ≤ −1 dBFS, item 6's mid-fade companions (i)–(iii) and W-a windows, and the item-7
      assertion on every drawn onset, with Q5's realised window and replacement rate recorded, becomes the speech
      pair. The search or re-measure is repeated on a fallback scene (D or B) if one is used. The pair is named and
      its SHA-256s recorded before the seal. Selection grounds: measured assertions only, before any blind result;
      no pair is ever chosen by listening. If no pair qualifies, the pair stays MA01_01 + MA01_02 and condition (c)
      restricts the onsets: on E the onset floor is 2.685 s, the first candidate boundary 2.688 s, the realised
      window ≈ [0.134, 0.380]·T_heard and ≈ 60 boundaries pass (fixed here before any speech stimulus is heard;
      never adjusted after familiarisation). The record then states: 'speech onsets ≥ 0.134·T_heard on E (item 7);
      about 2 dB less mean tail exposure than an unrestricted draw.' No remedy speech family is pre-registered: a
      non-detection is never a reason to run another speech block (file 13 item 4).

    - **The search:** `python tools/ci/abx_kit.py speech --search-pairs` (with the speech chain's other arguments;
      see the kit's `--help`) prints one row per pair tried. `test_preregistered_numbers` pins the chosen pair's
      names and SHA-256s, and, in the fallback branch, the floor. K6 is redone on whichever pair is chosen.
    - **Families:** two, E in omni here and E binaural at 08-3 (union ≤ 0.098); no contingent third family. AX47's
      α sentence (D-M3i) is unchanged.
    - **MA01_01 + MA01_02 on the ABX scene (the fallback pair):** the kit measured the Q5 window
      [0.059, 0.380] · T_heard without the item-7 restriction (phase-07c-2b builder file 12; the first boundary at the
      heard end of the sentence-1 file, TSP's trailing silence included; builder file 4's [0.013, 0.380] used K7's
      end-of-speech definition), ≈ [0.134, 0.380] · T_heard with it (decider file 34); the kit
      recomputes and records the realised window and replacement rates for the chosen pair **[measured at build]**.
      The figures in the next two sub-bullets are S-A's (07c-2).
    - **Realised Q5 onset window, recorded before sealing** (decider file 21, 2a; measured in
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
2. **Fix the speech material** in the pre-registration: one adult TSP speaker and one file pair (item 8). M3-T
   (phase-07c-2b decider file 10 Part B) is amended by decider file 34 (I7, round 3): the pair is the result of the
   pre-registered pair search (§1, "Speech pair"); MA01_01 + MA01_02 is used only in the fallback branch, with the
   onset restriction.
   - Speaker: **MA** (an adult; TSP's documentation records it)  Files: ______ and ______ (the search result, or
     MA01_01 and MA01_02 in the fallback branch), at 48 kHz. Every pair tried is recorded.
   - Selection grounds (stated in the pre-registration; Seat 1's condition): measured assertions only (every
     pre-seal assertion of §1 and §3 item 3 on the scene in use, including item 7 with no onset restriction), before
     any blind result; no pair is ever chosen by listening.
   - Our SHA-256 of `48k.zip` and of each excerpt is recorded (item 12).
   - The children CA and CB are excluded (the kit refuses them, `tools/ci/abx_kit.py` L983–984).
   - Open before the seal, on every sealed scene (Seat 3, M3-C 7; decider file 10 M3-T): the unstepped render B
     nulled within −120 dB against the offline render on every speech stimulus (builder file 4 fact 5 nulled B on
     noise only); the stepped render E is already nulled on speech (−130.0 dB or better).
3. **Build the stimuli** on a machine with `render_cli` built (`cmake --preset cli && cmake --build --preset cli`).
   - Noise chain: `python tools/ci/abx_kit.py noise --out build/abx-07c-2`. The CI `listening-pack` artifact
     (`phase-07c-2/noise/`) holds the same files.
   - Scene: `--scene-name` (default `layout5_s0.9/emitter_wall`; fallbacks `layout5_s0.8/emitter_wall`, then
     `layout5_s0.8/default`), on both chains.
   - Speech pair search (before E's seal): `python tools/ci/abx_kit.py speech --search-pairs` (§1, "Speech pair").
   - Speech chain, local only: `python tools/ci/abx_kit.py speech --out build/abx-07c-2 --speaker <S> --files <F1> <F2>`.
     The script downloads `48k.zip`, checks it against our SHA-256 and writes `NOTICE-TSP.txt`. Never commit or
     upload these files (item 12).
   - Each build runs every item-6 assertion on every stimulus, and stops if any fails. The assertions are: early
     parts bit-identical, the stated tail step, the window's unscaled share s_w ≤ 2.3 %, the `[ax47-midfade]`
     checks, no new click at the step, and, for speech, Q5's tail ≥ floor + 20 dB at the onset. It also stops if
     the M2 debt check (§1, assertions 1–5 on heard quantities) fails.
   - **No new click at the step: `click_check` form (b)** (D-M3a, phase-07c-2b decider files 2 and 5; interrogator
     file 6 SURVIVES): no `tools.acoustics clicks` event on r = (A − B) − m over [N − 5 ms, N + L + 5 ms), with the
     model m = (j/L)(E − B) on [N, N + L) and E − B after it, L = 1440; detector unchanged (2 kHz zero-phase
     high-pass, 2 ms frames, 20 dB over the median, absolute floor −90 dBFS); on channel 0 in omni (the two outputs
     asserted identical), on each ear at 08-3. Red tests: a hard switch at N (L = 0); a −65 dBFS single-sample
     impulse inside [N, N + L); the bracket, caught at −68 dBFS and missed at −72 dBFS, mid-frame and on a frame
     boundary. Printed: `spike_floor_dbfs` and the bracket, the detector event counts on A, B and E, and the legacy
     comparison of A's events against B.
   - **Pre-seal set, on every stimulus** (M3-C 7, Seat 3): form (b) green; B and E nulled within −120 dB against
     their offline references on every noise and speech stimulus; M1's per-band step identity within 0.05 dB.
   - `manifest.json` records the measured values, every stimulus's SHA-256 and, for speech, the excerpt's SHA-256
     and every replaced onset.
4. **Seal** each chain: `python tools/ci/abx_kit.py seal --pack build/abx-07c-2/<chain> --session <session dir> --key <key file>`.
   - Keep the key file outside the session folder. The listener must not see it.
   - The session folder holds only `<level>dB/trial_NN/{A,B,X}.wav`.
   - Commit `<key file stem>-prereg.json`, written beside the key, **before the run**. It holds the key's SHA-256
     and a salted SHA-256 of every A, B and X (item 11). Each file has its own secret salt, kept in the key. Plain
     hashes would give the answers away, because X is a byte copy of A or B. `score` checks the session folder
     and the key against this record.
   - Never give the listener the unsealed pack (`build/abx-07c-2/<chain>/`).
5. **Date the session** in the session brief (item 16). If neither 07c-2 nor 07c-2b can hold it, it goes to
   Maisara as a person's action. Scene E's session (2.39 h measured, plus about 0.08 h for M3-G's longer pause; K6
   is redone on E) is split at a block boundary into two dated sittings, with a per-sitting plan in the brief
   (Seat 7, M3-C 8); AX49 L4 is scheduled as §8 states.

## 4. Procedure

- **Familiarisation, before any scored block (mandatory, BS.1116-3 §4.1; item 2).**
  - Play the labelled pairs in `familiarisation/`: the 3 dB anchor and each step size, up and down. A is
    stepped and B is not.
  - Whether feedback is given during familiarisation is Seat 1's design choice. It is **not set by this kit**.
    Record what was done: ______________________
- **Blocks (item 2).** Each block has 22 trials: 16 scored trials and 6 interleaved anchor trials (a uniform
  3 dB tail step). Take a break after trial 11. No feedback is given in scored blocks.
- **Each trial.** Listen to A, B and X, as often as you like, as whole files. Then write down whether X is A or B.
  Every trial needs an answer: guess if you are unsure.

### Trial counts and pass criteria (items 2, 3), verbatim from file 13

| chain | first test | second test (only if the first is detected) | anchor |
|---|---|---|---|
| noise | 0.9 dB at ≥ 12/16 | 0.5 dB at ≥ 12/16 | 6 per block, pass at ≥ 5/6 |
| speech | 0.9 dB at ≥ 13/16 | 0.5 dB at ≥ 13/16 | 6 per block, pass at ≥ 5/6 |

- Family: FWER ≤ 0.0490, strong (union bound; graphical procedure). No α passes between chains.
- Families across phases (AX47, D-M3i; M3-S): each sealed 07c-2b scene and each phase-08-3 rerun is its own family
  at these thresholds, unsplit. Here **n = 2** (scene E in omni now, its binaural rerun at 08-3), so the union
  false-reversal rate is ≤ 0.098. The record names the family that triggers any reversal. AX49 L4 (§8) is a
  separate family.
- Pre-registered power at p = 0.75: 0.63 (noise) and 0.405 (speech).

### Fixed-sequence stopping rule (items 3, 4, 11)

1. In each chain, run the **0.9 dB** block first.
2. Run the **0.5 dB** block of that chain **only if 0.9 dB was detected in that chain**. The scoring script
   refuses to unseal a 0.5 dB block otherwise.
3. If a block's anchor fails (fewer than 5 of 6 correct), the block is void. It gets **one rerun**, and it is
   never recorded as "not detected". A non-detection is never a reason to rerun.
4. What follows from the results:
   - A detection at 0.9 dB in **either** chain sets AX47's bound to 0.5 dB for all scenes. A speech
     non-detection never cancels a noise detection.
   - A detection at 0.5 dB is a finding for the class (c) round.

## 5. Response tables

Write X's answer (A or B) per trial. The same table as CSV:
`python tools/ci/abx_kit.py blank --chain <chain> --out responses-<chain>.csv`. Score it with
`python tools/ci/abx_kit.py score --key <key file> --session <session dir> --responses responses-<chain>.csv --chain <chain>`.

### Noise chain, 0.9 dB block

| trial | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

*(break)*

| trial | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

### Noise chain, 0.5 dB block (only after a 0.9 dB detection in the noise chain)

| trial | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

*(break)*

| trial | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

### Speech chain, 0.9 dB block

| trial | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

*(break)*

| trial | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

### Speech chain, 0.5 dB block (only after a 0.9 dB detection in the speech chain)

| trial | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

*(break)*

| trial | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

## 6. Where to record the results (item 13)

Record the results in `docs/validation/abx-07c-2-results.md` (create it at the run) and in the session brief's
dated item. Do not commit audio, and do not make a public copy of the speech stimuli.

| listener | chain | level (dB) | k/16 | exact p | anchor k/6 | scene hash | tailSeed | commit | wording |
|---|---|---|---|---|---|---|---|---|---|
| | noise | 0.9 | | | | | 12345 | | |
| | noise | 0.5 | | | | | 12345 | | |
| | speech | 0.9 | | | | | 12345 | | |
| | speech | 0.5 | | | | | 12345 | | |
| | L4 chord (§8) | provisional vs exact | | | | | 106 | | |

- `score` prints k/16, the exact p and the anchor k/6. The scene hash is `scene_sha256` in `manifest.json`. The
  commit is the one the stimuli were built from.
- **Wording (item 13):**
  - "detected (≥ c/16, family α 0.049)";
  - "not detected in 16 trials by one listener (power 0.63 / 0.41 at p = 0.75)";
  - "inconclusive" if the anchor failed.
  - Never write "inaudible", and make no public copy.
  - **Scope of a non-detection (item 13, D-M3e):** "A non-detection is recorded for its scene class only; the 1 dB
    bound elsewhere rests on D-C1, as AX47 states." The class is the Class line of the scene's item-9 label (§1).

## 7. Not in this kit

- **The 08-3 binaural rerun (item 15, M3-S):** "The AX47 self-ABX is rerun on the binaural chain at the bound in
  force, before Phase 08's goldens freeze, on the sealed 07c-2b scene and tailSeed (its omni twin), under Seat 4's
  L5 condition. It is its own family." Its rules are in `docs/phases/phase-08-3.md`.
- AX49 L4 (file 13 item 14) has moved into this kit: §8.
- **Kit choices file 13 does not fix:**
  - the noise level (−8 dBFS RMS before the room) and the burst length (1 s);
  - the onset's seeded range;
  - the end-of-speech rule: the last 10 ms frame above TSP's noise level + 15 dB;
  - the floor segment: the noise in TSP's lead-in;
  - the trial-plan seeds;
  - rendering at the shipped W.

  They are recorded in `manifest.json` and in `tools/ci/abx_kit.py`.

## 8. AX49 L4: held-chord ABX, provisional against exact tail

Source: phase-07c-2b decider file 10 Part A (L4-P, L4-S, L4-D, L4-T), interrogator file 13 (SURVIVES WITH
CORRECTIONS), Seat 5 file 14 (its conditions on the flags are implementation requirements of L4-P); the anchor,
wording, void and session rules from decider files 17 (D1, P1, P8) and 21 (P8-3, P8-S, D1 corrections), interrogator
files 18 and 22; measured timing from builder file 15. It tests whether
a listener hears the AX49 provisional tail (the one every user hears while a long-decay scene loads) against the
exact tail. L4 is its own family (AX49), not one of the AX47 families of §4 and not added to the AX47 union
(≤ 0.098): it tests a different reversal on a different claim (P1).

**Stimulus flags (validation only, `src/cli`).** `render_cli --provisional-ir` (off by default; omni only),
`--provisional-timing <json>` and `--provisional-handover-sample N`, with refusals r1–r5 and tests 1–8 of L4-P (file
10, with file 13's corrections to r5 and tests 3 and 8 and file 14's conditions). No L4 stimulus is sealed before
those tests are green in CI on Linux, macOS and Windows.

**Scene (L4-S).** `tests/scenes/valid/stone_box.json` with every band's α multiplied by one common factor k (start
0.844); the builder adjusts k until `--provisional-timing` reports T60_max = 8.0 ± 0.1 s. 20 × 12 × 10 m; listener
(10, 8, 1.7); emitters (8, 3, 1.7) and (12, 3, 1.7); s 0.1; tailSeed 106; 48 kHz. k **[measured at build]** is
recorded (builder file 15 measured k = 0.84: T60_max 7.9955 s, t_mix,e,max 0.08017 s, L_f 2.5748 s, L_p 2.6748 s); the scene JSON and its SHA-256 are committed with the kit. Asserted before the seal: provisional is true,
L_p < L; L_f, L_p, L and the per-band T60 are printed.
- `label`: **"Long-decay test room, hard stone box with uniform absorption, T60_max 8 s; provisional-vs-exact tail
  test (provisional tail, validation-only flag); not a validated preset"** (Seat 9 confirms it before the seal).
- `label_detail`:
  1. Geometry; α = k × stone_box per band; s 0.1 (early part specular only, AX21); tailSeed 106; 48 kHz; emitters
     5.39 m away.
  2. T60 per band; T60_max **[measured at build]** s in band **[measured at build]**.
  3. D/R at 1 kHz **[measured at build]** against **[measured at build]** dB at r/r_c **[measured at build]**
     (Kuttruff Eq. 5.44, Sabine A **[measured at build]** m²). ᾱ ≈ **[measured at build]** (expected 0.04–0.07) is
     small, so §5.6's ᾱ caveat does not apply.
  4. t_mix,e,max, L_f, L_p **[measured at build]** and L **[measured at build]** (11.993 s at k = 0.84).
  5. Cut depth per band: 10·log10(E_B[L_f, L)/E_B[0, L)) **[measured at build]**, printed beside the chord's band
     energy.
  6. The early reflections are identical in A and B.
  7. "Stimulus scene, not a room prediction."
- Class line: "long-decay, [Seat 9's D/R class] (heard D/R **[measured at build]** dB), cut **[measured at build]**
  dB in the T60_max band".

**Stimuli (L4-D).**
- **A** is the provisional IR (`--provisional-ir`); **B** the exact IR from the same plan. Both are rendered with
  `--realtime-emulation --block 512 --partition 512`. Both are static: the handover is not part of the scored
  stimulus.
- **Chord:** deterministic additive synthesis, versioned in the kit; open voicing C2–G2–C3–E3–G3–C4, equal-tempered;
  harmonic partials up to 8 kHz tilted −3 dB/octave; no vibrato; 50 ms onset; 10 ms raised-cosine release; band
  energies printed.
- **Timing:** hold H = max(L_p, 0.5·T60_max) (4 s at T60_max 8 s); one release per file, then at least L + 0.5 s of
  silent input; the whole exact decay fits in the file (asserted); A and B are the same length.
- **Fully wet:** the whole room IR (direct, early and tail); no dry path, no tail-only render; diotic; no
  normalisation (one fixed, recorded gain for all files); peak ≤ −3 dBFS.

**Assertions on every stimulus** (the build stops if any asserted item fails; print-only items say so):
1. the provisional flag is recorded, with "provisional tail, validation-only flag" in the manifest;
2. A and B agree before the earliest tail crossfade starts (decider file 41 (4); interrogator file 42): the IRs are
   bit-identical up to the earliest tail fade start (tap 3007 here); the renders are bit-identical before the
   partition boundary at or below the chord-aligned fade start (6656 here), and over [that boundary, fade start),
   i.e. [6656, 7103), max |A − B| ≤ −120 dB re B's peak, per sample (Seat 3's per-sample criterion at Phase 06's
   −120 dB level). Print: the first differing sample (6658);
3. prefix (AX47 (b)): 10·log10(E(A − B)/E(B)) ≤ −18.27 dB over [t_mix,e, L_f − h), per emitter and band;
4. over [t_mix,e,max + 2.5 ms, L_f), the A/B energy matches AX47 (b)'s predicted step within 0.05 dB. Print:
   "consistency check; weak on this scene (all predicted |A/B| < 0.01 dB); red test: a 1.2 dB hot provisional fails
   it" (decider file 41 (3));
5. A is zero from L_p on;
6. B is L long;
7. the decay from t_mix,e,max to L_f is at least 18.7 dB in every band, read on the model: AX49 builds 60 × 0.312
   = 18.72 dB per band (decider file 41 (2)). Print: "realised Schroeder drop [t_mix,e,max, L_f), one realisation,
   not asserted" (63 Hz: 18.47 dB);
8. B's share past L_f is at most 0.0134 per band: K17′'s bound counted from emission (the energy past L_f over the
   whole decay), not the drop from t_mix,e. With the measured t_mix,e,max 0.08017 s (60 × 0.08017/7.9955 = 0.60 dB):
   model 10^(−(18.72 + 0.60)/10) = 0.0117, realisation 10^(−(18.47 + 0.60)/10) = 0.0124 (= measured), both ≤ 0.0134
   (interrogator file 42);
9. print: the A/B level difference over the held part, per band;
10. the silence after the release is at least L;
11. peak ≤ −3 dBFS;
12. two builds are bit-identical;
13. ghost print (print only): per band, the re-onset level from B's backward-integrated curve at release + L_p +
    {0, 1, 2, 5} s, labelled "noise-excitation (Schroeder) estimate" (interrogator file 13, K29);
14. listening pack (unscored): one render, "L4 handover demo (unscored; interim then handover, as at project load)",
    on the L4 chord, releasing at t_r and handing over at the first partition boundary at or after t_r + L_p + 1 s,
    built with `--provisional-handover-sample` and added to `tools/ci/listening_pack.py` under phase-07c-2b. The word
    "unscored" is in its file name and in the pack index (Seat 5, file 14 (vi)); it is never sealed or scored.

**Procedure.**
- **Familiarisation:** includes a labelled A/B pair (A provisional, B exact) and the labelled anchor pair.
- **Block:** 22 trials, 16 scored and 6 anchor trials at seeded positions; a break after trial 11; no feedback. Each
  trial as in §4. There is no 0.5 dB block.
- **Anchor (decider file 41, DECISION L4-A, exact text; interrogator file 42):** "**Anchor (AX49; file 13 item 2: a
  uniform 3 dB tail step, pass ≥ 5/6).** 6 anchor trials per block at the block's seeded positions, built on the L4
  scene and chord from two static files: B, and B with the tail stepped +3 dB (`--abx-step-db +3 --abx-step-sample
  0`). In 3 trials the stepped file takes the stepped role and B the reference; in the other 3 the roles are swapped.
  X is drawn at random as for scored trials. On the L4 scene the specular share of E_target is 0.828, so a −3 dB step
  cannot be built (`--abx-step-db` reaches −0.82 dB); with static whole-file stimuli the two role assignments present
  the same 3 dB tail-level difference, so the anchor's purpose (chain and attention to the tail; not envelope
  sensitivity) and its chance rate (7/64) are unchanged (phase-07c-2b decider file 41). Familiarisation includes the
  labelled anchor pair. The anchor result is never cited as evidence about M1's step or any other measurement."
  Asserted on the +3 dB anchor IR: M1's per-band step identity within 0.05 dB, s_w ≤ 2.3 %, peak ≤ −3 dBFS.
- **Criteria:** detection at ≥ 12/16 (family α 0.038 ≈ 2517/65536); anchor pass at ≥ 5/6. Its own family.
- **Failed anchor (D1, rule (a); decider file 17, exact wording; its "±3 dB" predates decider file 41, under which the anchor is +3 dB with roles swapped 3/3 (A-ii)):** "L4 anchor (6 trials, ±3 dB tail step, pass
  ≥ 5/6). If the anchor fails, the block is void: its scored trials are not unsealed or scored, and the void is
  recorded. One rerun follows, using a second block (its own seeded key, trial order and anchor positions) that was
  built and sealed with the first, before the session. A voided result is never recorded as 'not detected'. A
  non-detection is never a reason to rerun. If the rerun's anchor also fails, the record reads 'inconclusive (anchor
  failed twice)', and AX49's L4 reversal stays unread; the board treats that as an unread reversal at 07d (debt row
  below)." The kit builds and seals two blocks (primary and pre-built rerun) together; the scoring script scores the
  anchor trials first and refuses to unseal a block's scored trials if that block's anchor failed (as it refuses a
  0.5 dB AX47 block without a 0.9 dB detection). The debt row is file 17's future-debt register (Seats 1, 6, 7).
- **Sittings (L4-T, Seat 7; D1 hours, decider file 21; decided by decider file 38 (5), interrogator file 42):** K6 is
  redone on the sealed L4 stimuli, counting the worst case: scene E's second sitting, plus the primary L4 block, plus
  the rerun block (the rerun is not inside the existing K6, which covers only the AX47 chains). That worst case is
  about 74 + 74 = 148 min, over 2 h, so **L4 runs in its own third dated sitting**: the primary block, plus the rerun
  block if the anchor fails (74 min at a typical pace, 113.6 min slow, within 2 h). E's two sittings are unchanged.
  The dates go into the brief before any seal. If a rerun would push a sitting past 2 h, it opens the next sitting
  instead. L4 is sealed with E, before the session (§3 item 4).

**Response table (L4).**

| trial | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

*(break)*

| trial | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| X = | | | | | | | | | | | |

**Record (§6 table, one row "L4", tailSeed 106).** Wording (Seats 9 and 6):
- detected: "detected (≥ 12/16, family α 0.038)";
- not detected: "not detected in 16 trials by one listener (power 0.63 at p = 0.75); covers a cut ≥
  **[measured at build]** dB below the full-IR energy in the T60_max band at T60_max 8 s". The cut is the label's
  detail line 5 in the T60_max band;
- anchor failed twice: "inconclusive (anchor failed twice)" (D1);
- never "inaudible", never "at T60 8 s" alone, and no public copy.
- Beside AX47's union rate (≤ 0.098) the record states that L4 is its own family, not in the AX47 union (P1).

A detection meets AX49's reversal ("the L4 ABX detects the cut"): it goes back to the board with 07d's candidates
first, and the ghost print is among 07d's inputs.

**Void rule for sealed L4 stimuli (P8, decider file 17; item 3 and the manifest print, P8-3, decider file 21).**
Sealed L4 stimuli are void for the next listening session if any of these happens:
1. any change that makes AX21's statement false or moves t_mix,e: a B11 promotion, an early-diffuse method, or a
   change to the AX22 rule;
2. any change to the tail's decay target, such as non-Eyring decay for non-diffuse rooms (C-b);
3. any change to AX49's provisional construction: the 0.312 fraction, the 0.1 s fade, the normalisation, or L's rule
   (1.5·T60_max, capped at 12 s). The L4 manifest prints, for each stimulus, the constants it was built with: f, fade
   length, normalisation, L rule (Seat 3's O5);
4. a hash mismatch, as a backstop for any cause: the manifest records the SHA-256 of A's IR (`--provisional-ir --ir`)
   and B's IR (`--ir`) on the L4 scene, with the platform; before the session the kit rebuilds both on the same
   platform (AX5) and compares; any mismatch voids the stimuli.

After a void, the stimuli are rebuilt and must pass §8's assertions 1–13, L4-P's tests 1–8 and Seat 9's label check
before they are sealed again. Results already recorded stay attached to their commit and scene hash, marked
"pre-change engine".

**When an L4 session is owed (P8-S, decider file 21, exact wording with interrogator file 22's correction to its last
sentence):** "Voids under P8 items 1–4 force a rebuild and reseal only. An L4 session is owed once per decision
point: before any board decision that reads AX49's L4 reversal, L4 is run on stimuli built with the constants then
in force. Changes between two sessions collapse into one session on the latest constants. When the change is 07d's
own remedy of AX49 (f, fade, normalisation, L rule), 07d decides the remedy provisionally, rebuilds the L4 stimuli
with those constants, and runs L4 before reaching `done`; 07d may not be `done` while its L4 stimuli are void or
unscored. If that L4 detects the cut, the remedy returns to the board with Seat 3 as its owner: one L4 session per
board round. Every 07d L4 session, including those after a detection, is dated before the Phase 08-4 freeze."
