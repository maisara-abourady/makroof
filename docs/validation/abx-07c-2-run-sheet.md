# AX47 self-ABX: run sheet (phase 07c-2, D-W2)

This sheet is for the decision listener (Maisara or the listener she names) and for whoever runs the session.
The design was pre-registered by the board before any stimulus was heard. Nothing on this sheet changes it. The
source is `docs/review/phase-07c-2/13-decider-rebuttal-r4.md`, "D-W2: final", items 1–16, and its section "Q5: TSP
step placement (pre-registered)", which interrogator file 14 rated SURVIVES. Every number below is copied from
there. Where the kit had to make a choice that file 13 does not make, the choice is marked **kit choice**.

## 1. What is being tested

When the plugin replaces an interim reverb with the final one, the reverb tail changes level in one step. The
step is a 30 ms equal-gain crossfade (AQ4, AX18). The test asks whether one listener can hear such a step, in an
ABX test.

- **The step:** a change of g dB in tail energy, uniform across all 8 bands. The two IrSets come from one
  StagedBuild through `useDiffuseLevel`. The early sound is bit-identical, and only the tail changes (item 5).
  - Item 5 scales the whole tail energy (diffuse and specular) by 10^(g/10), as item 6's formula requires; on
    layout4_s1/default the specular share is 0 in every band, so this equals scaling E_b alone (file 5's wording);
    the kit refuses a down-step that would need E'_diff < 0. (Decider file 21, point 1.)
- **B** is the unstepped render, held throughout. **A** carries the step. **X** is either A or B (item 7).
- **Directions:** in each block, 8 trials step up and 8 step down, in random order (item 7).
- **Timing:** at least one T30 of programme comes before the step, and at least 2 s after it (item 7).
- **Scene:** `layout4_s1/default`, an "occupied mid-size hall envelope, not a validated preset" (item 9).
  - 20 × 30 × 10 m, with an absorbing floor and scattering 1 on every face.
  - Fixed tailSeed 12345 (**kit choice**: the value the scene template carries).
  - The kit asserts that the scene is capped at m = 6, 7 and 8, and prints r/r_c and D/R into the manifest: D/R
    per emitter (each emitter's own IR) and of the heard IR (L + R summed), which is about 3 dB higher (file 22).
- **Signals (item 8):**
  - **Noise chain:** pulsed pink noise, with gaps ≥ T30(1 kHz) and the step at the start of a gap.
  - **Speech chain:** McGill TSP v2 at 48 kHz, one adult speaker and one file pair, with a pause ≥ T30 between
    them. The onset falls in the pause, no later than 0.43 · T30(1 kHz) after the end of speech (Q5).
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
2. **Fix the speech material** in the pre-registration: one adult TSP speaker and one file pair (item 8).
   - Speaker: ______  Files: ______ and ______
   - The children CA and CB are excluded.
3. **Build the stimuli** on a machine with `render_cli` built (`cmake --preset cli && cmake --build --preset cli`).
   - Noise chain: `python tools/ci/abx_kit.py noise --out build/abx-07c-2`. The CI `listening-pack` artifact
     (`phase-07c-2/noise/`) holds the same files.
   - Speech chain, local only: `python tools/ci/abx_kit.py speech --out build/abx-07c-2 --speaker <S> --files <F1> <F2>`.
     The script downloads `48k.zip`, checks it against our SHA-256 and writes `NOTICE-TSP.txt`. Never commit or
     upload these files (item 12).
   - Each build runs every item-6 assertion on every stimulus, and stops if any fails. The assertions are: early
     parts bit-identical, the stated tail step, the `[ax47-midfade]` checks, no new click at the step, and, for
     speech, Q5's tail ≥ floor + 20 dB at the onset.
   - `manifest.json` records the measured values, every stimulus's SHA-256 and, for speech, the excerpt's SHA-256
     and every replaced onset.
4. **Seal** each chain: `python tools/ci/abx_kit.py seal --pack build/abx-07c-2/<chain> --session <session dir> --key <key file>`.
   - Keep the key file outside the session folder. The listener must not see it.
   - The session folder holds only `<level>dB/trial_NN/{A,B,X}.wav`.
   - Commit `<session dir>/prereg_hashes.json` **before the run**. It holds the key's SHA-256 and every stimulus's
     SHA-256 (item 11).
   - Never give the listener the unsealed pack (`build/abx-07c-2/<chain>/`).
5. **Date the session** in the session brief (item 16). If neither 07c-2 nor 07c-2b can hold it, it goes to
   Maisara as a person's action.

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
`python tools/ci/abx_kit.py score --key <key file> --responses responses-<chain>.csv --chain <chain>`.

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

- `score` prints k/16, the exact p and the anchor k/6. The scene hash is `scene_sha256` in `manifest.json`. The
  commit is the one the stimuli were built from.
- **Wording (item 13):**
  - "detected (≥ c/16, family α 0.049)";
  - "not detected in 16 trials by one listener (power 0.63 / 0.41 at p = 0.75)";
  - "inconclusive" if the anchor failed.
  - Never write "inaudible", and make no public copy.

## 7. Not in this kit

- **AX49 L4 (item 14):** the held-chord ABX, provisional against exact, T60 8 s. It uses the same chain and tool
  with the 6-trial anchor, but needs its own stimuli.
- **The 08-3 binaural rerun (item 15).**
- **Kit choices file 13 does not fix:**
  - the noise level (−8 dBFS RMS before the room) and the burst length (1 s);
  - the onset's seeded range;
  - the end-of-speech rule: the last 10 ms frame above TSP's noise level + 15 dB;
  - the floor segment: the noise in TSP's lead-in;
  - the trial-plan seeds;
  - rendering at the shipped W.

  They are recorded in `manifest.json` and in `tools/ci/abx_kit.py`.
