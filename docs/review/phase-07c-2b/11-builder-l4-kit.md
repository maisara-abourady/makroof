# 11: Builder, the AX49 L4 kit (tools/ci/ax49_l4.py) — first full build; stops on Seat 1's band-coverage assert

Saved verbatim by the orchestrator from the L4 builder's report, 2026-11-24. Note: the two new files landed in commit 1f8fb5f (the concurrent abx_kit commit), not a commit of their own.

## AX49 L4 kit (phase 07c-2b M3-L4): built; the full build stops on Seat 1's band-coverage assert (4 kHz at −22.94 dB)

The L4 kit is built, but the full build stops on one check: Seat 1's band-coverage assert fails on the clean stimulus. The exact render's steady state at 4 kHz is **−22.94 dB** below the strongest band (125 Hz). The limit is within 20 dB. Every other check passes. As instructed, I stopped and did not loosen it; it goes back to the board (Seats 1, 3 and 8).

Because of the red, nothing was packed or sealed. The build exits 2 and writes every computed value to `build/abx-07c-2b/l4/check_failed.json`.

**Commits:** I did not commit anything. Both new files are nevertheless already in HEAD: the concurrent `abx_kit` worker's commit **1f8fb5f** ("phase-07c-2b: speech chain 24+6 …") picked them up. HEAD holds my final versions and the working tree is clean. You may want to split or annotate that commit. I edited no other file and nothing under `src/`.

### Files
- `/home/user/makroof/tools/ci/ax49_l4.py` (module and CLI: `build --out`, `seal`, which calls `abx_kit.seal` unchanged, `score --key --responses [--session] [--rerun]`, and `blank`). The docstring states which checks are exact, which are measured approximations, and which need C++.
- `/home/user/makroof/tools/ci/test_ax49_l4_kit.py` (pytest).

### Why band coverage fails
| Band (Hz) | 63 | 125 | 250 | 500 | 1k | 2k | **4k** | 8k (not asserted) |
|---|---|---|---|---|---|---|---|---|
| dB re strongest | −9.8 | 0.0 | −9.3 | −11.6 | −13.3 | −15.8 | **−22.9** | −50.3 |

- **The chord itself:** the dry chord's 4 kHz band is already −14.8 dB re 125 Hz. The 1/k series to 5 kHz cuts the 2.8–5.6 kHz octave short.
- **The room:** it takes about 8.1 dB more at 4 kHz relative to 125 Hz. T60 at 4 kHz is 3.73 s against 8 s, and 125 Hz comes out about 5 dB above its neighbours after the room. That fits a reverberant transfer measured at only a few partials, with tailSeed fixed.
- **What could fix it is the board's call:** the chord spectrum (Seat 8's voicing or partial limit) or the criterion. I changed neither.

### Results of the one full build
Build time is about 26–32 s. The stimulus is 16.533 s long: 0.5 s silence, 20 ms attack, 4 s hold, 10 ms release, then 12.003 s of free decay. The chord has 220 partials. Two builds gave identical SHA-256s and identical check values.

**Scene S′ (Seat 2's asserts all pass)**
- T60 per band: 8.000, 8.000, 8.000, 8.000, 8.000, 6.457, 3.731, 1.427 s. T60_max is 8 s in the 63 Hz–1 kHz bands.
- Timings: t_mix,e is 1.11753 s for both emitters; L_f 3.61353 s, L_p 3.71353 s (≤ 3.82 s), L 12 s; provisional yes.
- Depth from t_mix,e,max:

| Band (Hz) | 63–1k | 2k | 4k | 8k |
|---|---|---|---|---|
| at L_f (dB) | 18.72 | 23.19 | 40.14 | 104.93 |
| at L_p (dB) | 19.47 | 24.12 | 41.75 | 109.13 |

**IR checks**
- **P1:** L_p < L.
- **P2:** bit-identical on [0, 47912) taps on all four channels; the first differing tap is 47913.
- **P3:** zero from the L_p tap (172641); the file is exactly that long.
- **P4′:** 20·log10 c_b is between −0.003 and 0.000 dB in every band. The fade-weighted model prints between −0.014 and +0.002 dB. The provisional is the exact tail times about 1, not energy-preserving: its missing energy past L_f is AX47 (b)'s truncation loss. The bound asserted is ≤ 1 dB.
- **P5′:** fade fit maximum deviation 0.0000 against a tolerance of 0.05 (the method's own noise is 0.0001). The energy ratio over the fade is 0.3505 against a predicted 0.3504 (0.4129/0.4128 for emitter R), strictly between a hard cut (0) and no fade (c²).
- **P6 (print only):** the exact IR's share of tail energy past L_f, per band 63…8k: 0.0106, **0.0154**, 0.0138, 0.0121, 0.0122, 0.0053, 0.0006, 0.0001. At 125 and 250 Hz the realised share exceeds K17′'s 0.0134. This is noise from one realisation, and it is printed only.

**Level**
- Exact steady state −28.398 dBFS against the noise reference's −28.398 dBFS (difference −0.0000 dB).
- Chord gain −14.87 dB. **The dry input peaks at +3.05 dBFS.** It is float32 and never heard, but worth knowing.

**Stimulus checks**
- **S1:** all three arms are diotic, and the peak is −17.94 dBFS.
- **S3:** residuals −132.3 dB (provisional), −132.2 dB (exact) and −132.8 dB (anchor), margins about 12 dB.
- **S2, provisional:** n_on 24000, n_d 47913; identical before sample 71168; first difference at 71680 (margin 512).
- **S2, anchor:** identical before 71168; first difference at 71168 (margin 0, exactly on the grid bound).
- **S4:** A is exactly 0 from sample 390656 (K_p 338). The partial block [390080, 390656) is at −238.4 dB re the hold. Free decay 12.003 s ≥ 12 s.
- **Seat 1's prefix check:** **−34.674 dB** against the −18.27 dB limit, a margin of 16.40 dB. The other two readings of "release + L_f" give −34.531 and −34.682 dB (printed only).
  - The margin is much larger than the 18.7 dB figure suggests. In this 100 m room the direct sound and early part hold most of the energy, so the cut sits 27–35 dB below the hold.
  - Measured in the 100 ms after release + L_f, re the hold: B is −39.9, −34.9, −31.3, −29.9, −27.5, −36.8, −48.5, −62.4 dB; A is −53.3 … −76.3 dB.
- **S5:** per-band A − B over the hold is between −0.017 and +0.017 dB; per partial, rms 0.044 dB and max 0.340 dB.
- **S7 at 1 kHz:** the would-be handover step after the release is 0.07 dB at 0 s, 0.21 dB at 1 s, 0.36 dB at 2 s, 2.26 dB at 3 s, 8.83 dB at 3.4 s and 17.6 dB at 3.5 s.
  - It reads 176 dB at 3.6 s, where A holds only float residue below −238 dB. It is None where A is exactly 0.
  - Every band is stored in the manifest record.

### Decisions I had to interpret
1. **Output time.** render_cli removes the P-sample latency, so in the written file Seat 3's grid bounds are one partition earlier. S2 is identical before (⌊n_on/P⌋ + ⌊n_d/P⌋)·P, and S4 is zero from (⌈n_end/P⌉ + K_p)·P. Both hold exactly.
2. **The prefix window** ends at release end + (L_f − alignmentShift − 0.1 s), which is where the cut begins in the aligned output. I printed the other two readings as well; all pass.
3. **Equal lengths.** The three arms render to different lengths, so each stimulus is the render trimmed to the input length. The part trimmed off is asserted exactly 0, and the checks run on the untrimmed renders. Free decay is at least the larger of L and the IR plus 2P, which is 12 s here.
4. **Reproducible hashes.** The kit writes WAVs with scipy rather than soundfile. libsndfile's PEAK chunk carries a timestamp, which made the hashes change between runs. Worth knowing for the AX47 kit too, if it ever hashes files it writes from Python.
5. **Trial plan.** The anchor slots come from `rng.choice(22, 6)` with L4_PLAN_SEED 4902, mirroring `abx_kit`; Seat 1 asked for no per-half split for L4. Scored trials have `g_db` None and anchors −3.0.
6. **Seeds** (kit choices, pinned): chord 4901 (version "l4-chord-v1"), reference noise 4903, plan 4902. The probe gain is set so the input peaks at −20 dBFS. Then one gain step: render, measure, re-render.
7. **What is asserted exactly and what is measured:**
   - **Exact:** P1, P2, P3, S1–S4, Seat 2's asserts, coverage, prefix and level.
   - **Measured approximations, asserted:**
     - P4′: c_b from a least-squares fit on band-filtered IRs, held to |c_b| ≤ 1 dB (AX47 (b)'s bound).
     - P5′: a windowed least-squares fit against the raised cosine with a kit tolerance of 0.05, plus the energy ratio strictly between a hard cut and no fade. The L_f tap is only known to ±1 sample, so 1e−9 is out of reach from the CLI.
   - **Printed only:** P6, S5, S6 and S7.
   - **Not possible from the CLI:** P4 and P5 to 1e−9. I propose, but did not write, a Catch2 case `[ax49-l4]`. It would plan S′ with StagedBuild and compare the provisional and exact unitDecays() per emitter and band. It would assert provisional = c_b·exact on [t_mix,e + 2.5 ms, L_f) to 1e−9, and the fade gain against the formula to 1e−9, monotone, first value ≥ 1 − 1e−5. Hard-cut and other-seed variants would be the negative controls.

### Negative controls (in pytest)
- **N-L1:** a hard cut at L_f fails P5′ (deviation 1.0, energy ratio 0, not strictly between). A version with no fade at all also fails.
- **N-L2:** a provisional built with tailSeed 12346 still *passes* P2, because the early part does not depend on the seed. It fails the prefix check at −8.82 dB, against −34.67 dB for the clean pair.
- **N-L3:** S3 fails when a render is checked against the exact IR, and when the direct-sound tap is changed by 1e−4. A 1% change to one late tail tap (about −132 dB) passes, because it is below S3's −120 dB floor. That is S3's stated sensitivity, and the test documents it.

### Pytest
`SPATIAL_REQUIRE_RENDER_CLI=1 pytest -q tools/ci/test_ax49_l4_kit.py tools/ci/test_ax49_l4.py`: **15 passed, 1 xfailed in about 40 s.**

The xfail is `test_full_build`, on this band-coverage failure only. The test still requires that it is the first failure and that S1–S4, the prefix and the level passed; any other red fails the test.

It also covers:
- the pinned numbers: α = 2517/65536 = `binom_tail(12, 16)`, power 0.630, the chord, the envelope, the scene, the limits and the wordings;
- the scoring rule: detected at 12/16, not detected at 11/16, void when anchors are at 4/6, and void after the rerun;
- a pack → `abx_kit.seal` → `verify_session` → score round trip on a synthetic pack.
