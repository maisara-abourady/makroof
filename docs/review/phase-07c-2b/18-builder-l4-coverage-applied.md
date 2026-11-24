# 18: Builder, decider file 13 (L4-COV E, R1–R7) and Seat 9's L4 label applied; full L4 build green

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

## AX49 L4 kit (07c-2b): the board's ruling is applied and the full build now passes every check

I applied decider file 13 (L4-COV E and R1–R7) and Seat 9's final label (file 14 §3). The full build passes every check and packs: 22 trials and 2 familiarisation pairs. Two builds give identical hashes.

I changed only `tools/ci/ax49_l4.py` and `tools/ci/test_ax49_l4_kit.py`, and committed nothing. Someone else committed a mid-edit snapshot of both files as 00c4e6b ("WIP snapshot … not final"); my final versions are the uncommitted changes on top of it.

**Flag for the board:** coverage (b) passes as worded, but with a **2.29 dB** margin, not the decider's predicted 7.6 dB.
- The decider's 12.4 dB spread came from B's per-band levels taken *relative to each band's own hold* (file 11's after-cut print).
- The assert as worded compares the absolute band energies in the cut window with the strongest band there.
- I implemented the wording. Please confirm that is the intended quantity.

### Runs
- **Full build:** `python tools/ci/ax49_l4.py build --out build/abx-07c-2b` exits 0 in about 30–32 s. The stimulus is 16.533 s long; the pack is 45 MB.
- **Pytest:** `SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci/test_ax49_l4_kit.py tools/ci/test_ax49_l4.py` gives **18 passed** in 40 s. `test_full_build` changed from xfail to pass.
- **Reproducibility:** I ran the build twice. All 8 SHA-256s are identical, and so are the scene, IR checks, stimulus checks, level, label and the whole printed log (apart from the run time):

| File | SHA-256 |
|---|---|
| scene.json | 88ff5367… |
| ir/provisional.wav | f69d295e… |
| ir/exact.wav | ffbf1743… |
| ir/anchor.wav | 755d902c… |
| chord_dry.wav | 40e18507… |
| stimuli/provisional.wav | 256c3d17… |
| stimuli/exact.wav | c3c586d3… |
| stimuli/anchor.wav | e47177e3… |

- **The chord file's hash changed** from the first round: `chord_dry.wav` now holds the chord scaled by 2^−1 (R3). The chord itself ("l4-chord-v1") is unchanged.

### 1. Coverage E
- **(a) Steady state, 63 Hz–2 kHz relative to the strongest band (125 Hz):** 63 −9.76, 250 −9.25, 500 −11.58, 1k −13.31, 2k −15.83 dB. The weakest is 2 kHz, a **margin of 4.17 dB**. Pass.
- **(b) Cut window, [8.0267, 8.1267) s:** 63 −14.73, 125 0.00, 250 −5.65, 500 −6.57, 1k −5.91, 2k −17.71 dB. The weakest is 2 kHz, a **margin of 2.29 dB**. Pass.
- **Printed bands:**

| Band | Steady state | Cut window | Depth at L_f |
|---|---|---|---|
| 4 kHz | −22.94 dB | −36.48 dB | 40.14 dB |
| 8 kHz | −50.34 dB | −77.79 dB | 104.93 dB |

- **Seat 1's original clause (63 Hz–4 kHz):** 4 kHz reads −22.94 dB relative to 125 Hz, **red**. A test pins this value.
- **Cause, as the print states it:** the chord's 1/k slope (the dry chord's 4 kHz band is −14.80 dB relative to 125 Hz) plus the room's steady-state transfer (T60 3.73 s at 4 kHz against 8.00 s). It is not the 5 kHz stop.
- **N-L4 (pytest, on float64 convolutions with the exact IR):**
  - The chord limited to partials ≤ 500 Hz fails both checks: (a) 2 kHz −105.44 dB, (b) −98.16 dB.
  - The built chord passes both: (a) −15.83 dB, (b) −17.71 dB.

### 2. Null wording
The null wording is exactly the decider's text, and a test pins it.

### 3. Seat 3's conditions R1–R7
- **R1:** P2 now prints one statement: "identical on [0, 47913); first difference at 47913". Tap 47912 is identical (True). The P2 window is [0, 47912) and its assert is unchanged.
- **R2:** every WAV the kit writes is read back and asserted bit-equal (float32) to the checked array before it is hashed.
- **R3:** I chose the **pre-scale**, and the manifest records it under `input_scaling`.
  - The chord input peaks at +3.05 dBFS. It is scaled by 2^−1 to −2.97 dBFS; that peak < 1.0 is asserted. Each render is then multiplied by 2 afterwards, and that exactness is asserted through the inverse.
  - **New finding:** the AX47 reference pink-noise input also peaks above full scale, at **+4.81 dBFS**. It is scaled by 2^−1 the same way. Its level is unchanged at −28.398 dBFS.
  - S3 is checked on the renders exactly as render_cli wrote them (from the scaled input).
- **R4:** S2 and S4 print both grid forms:
  - S2: 71168 in the written file, 71680 in engine time;
  - S4: A is zero from 390656 in the written file, 391168 in engine time;
  - S3's text reads "delay 0 in compensated output".
- **R6:** P4′ and P5′ are kept as cross-checks. The docstring now says the C++ case `[ax49-l4]` is *required* (R5) and lies outside this kit.
- **R7:** the depth margin against AX49's 18.7 dB is +0.020 dB in each band from 63 Hz to 1 kHz.

### 4. Label
- **Fill values:** the heard D/R at 1 kHz measures −8.46 dB, so {printed} is "−8.5" (U+2212 minus). {seed} is 12345.
- **Fill rule:**
  - ᾱ(1 kHz): 0.23188 from the scene; 0.23188 back-solved from T60. They do not differ by more than 0.005.
  - m (from the engine's air table): 1.0741e−3 /m.
  - Derived: A 18209 m², r_c 19.03 m, r 40.31 m, r/r_c 2.118, diffuse D/R −6.52 dB.
- **Fixed figures:** every one of the label's fixed figures is asserted consistent with the fill rule: 18,200 m², 19 m, 2.1, −6.5 dB, 0.23, 40.3 m, and [3.6135, 3.7135) s.
- **Filled text:** Seat 9's text verbatim, with "D/R at 1 kHz −8.5 dB heard" and "one tailSeed 12345 for A and B". It is in the manifest under `label`.

### Other values (unchanged from round 1)
- **Scene S′:** T60 8.000 s from 63 Hz to 1 kHz, then 6.457 / 3.731 / 1.427 s above. L_f 3.61353 s, L_p 3.71353 s, L 12 s.
- **P3–P5′:**
  - P3: zero from tap 172641;
  - P4′: c_b between −0.003 and 0.000 dB;
  - P5′: fit deviation 0.0000, energy ratio 0.3505 against 0.3504 predicted.
- **Level:** the steady state is −28.398 dBFS against the −28.398 dBFS reference (Δ −0.0000 dB).
- **S1 and S3:** peak −17.94 dBFS; S3 residual −132.2 to −132.8 dB.
- **S2 margins:** 512 samples (provisional) and 0 samples (anchor).
- **S4:** the partial block is −238.4 dB relative to the hold; free decay 12.003 s.
- **Prefix:** −34.674 dB against −18.27 dB, a margin of 16.403 dB.
- **S5 (A − B over the last 1 s of the hold):** at most ±0.017 dB per band.
- **S7 at 1 kHz:** 0.07 dB at 0 s, 2.26 dB at 3 s, 8.83 dB at 3.4 s, 17.63 dB at 3.5 s.
