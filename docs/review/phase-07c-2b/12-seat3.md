# 12-seat3: Seat 3 on the L4 band-coverage red and the builder's interpretations

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION (M3-L4, band-coverage red at the first L4 build; builder file 11). Read-only: I wrote nothing. To be saved as /home/user/makroof/docs/review/phase-07c-2b/12-seat3.md.

**1. Reading.** Seat 1's coverage assert (63 Hz–4 kHz within 20 dB of the strongest band) reads −22.94 dB at 4 kHz on the clean exact render. Every check of mine passed. The question is how to fix the stimulus or the criterion, and whether the builder's interpretations 1–7 meet my P/S checks. The cues from my §4 are decay accuracy (which bands carry the cut at L_f) and state discontinuity (the grid bounds).

**Arithmetic first** (from file 11's numbers; derivations are [Inferred], not from the corpus):
- **The 5 kHz limit is not the main cause.** A 1/k series has partial energy 1/k², so a band [a, b) holds about f0(1/a − 1/b), which halves per octave (−3 dB/octave).
  - From 125 Hz to 4 kHz is 5 octaves, so ≈ −15 dB. The builder measured −14.8 dB dry.
  - Cutting the 2828–5657 Hz octave at 5 kHz costs only 10·log10(1.768/1.536) = **0.61 dB**.
  - The room then takes the other 8.1 dB. Part of that is the steady state scaling with T60: 10·log10(3.73/8) = −3.3 dB. Part is 125 Hz sitting about 5 dB above its neighbours in one fixed-seed realisation.
- **(A) cannot turn the check green:** −22.94 + 0.61 ≈ **−22.3 dB**, still red.
- **(B) would pass:** with 1/√k the energy per octave is about flat. The dry 4 kHz band is ≈ −0.9 dB (truncation at 5 kHz: ln(5000/2828)/ln 2), so after the room it reads about −9 dB.
- **Where the cut is (file 11's depths at L_f):** 63 Hz–1 kHz 18.72 dB, 2 kHz 23.19 dB, 4 kHz **40.14 dB**, 8 kHz 104.9 dB. At the cut, the 4 kHz tail sits about 44 dB below the 125 Hz band under the present chord, and about 30 dB below it even under (B). So 4 kHz content does nothing for the test of the cut. It matters only to the hold (S5 side channel) and to timbre.

**2. Ranking**
- **(C) prefer.** Criterion 63 Hz–2 kHz, 4 kHz printed.
- **(D) can live with.** (A) adds nothing to (C): its 5–10 kHz partials land in a band 105 dB deep at L_f.
- **(B) can live with.**
- **(A) alone: not a fix.** It stays red and stalls the seal.

**3. Tension now**
- **C 0.** No change to the stimulus, the hashes or my checks.
- **D 0.** A new chord version and a rebuild of about 30 s, with every check rerun.
- **B 1.** At matched energy level, about 1 dB of the hold moves out of the T60 8 s bands (their share falls from ≈ 97.5 % to ≈ 77 %, [Inferred] from file 11's band levels) into 2–4 kHz, where the tail is 23–40 dB deep at L_f. The cut test loses about 1 dB of sensitivity.
- **A 2.** It leaves a red, so L4 stalls and the AX47 seal waits behind it (my 8-seat3 premortem).

**4. Tension later**
- **C 1.** The L4 null is scoped to content at 63 Hz–2 kHz at the cut. The label already says T60 is shorter above 1 kHz, so the wording carries this. Undo cost: a print. Evidence: the L4 result.
- **D 1.** Same as C.
- **B 1.** The null rests on a brighter, less instrument-like spectrum, and S5 is weighted toward HF.
- **A 1.**

**5. Evidence**
- Depths, T60s and band levels: file 11, builder measurement.
- Steady-state energy ∝ T60 at equal power: the relation behind Kuttruff Eq. 5.42 as cited in file 9 (I did not re-read it; indicative, §5.6).
- Series arithmetic: [Inferred], redone above.
- **Note for Seat 1:** using the strongest band as the reference is fragile here. The 125 Hz band holds few partials, and its +5 dB over its neighbours is one realisation [Inferred].

**6. Conditions**
- **(A) → 1/1:** only as part of D.
- **(C):** justify the scope by the printed depth-at-L_f table (2 kHz at 23.2 dB is in, 4 kHz at 40.1 dB is out). It is not justified by the red. Record it in the pre-registration commit, before any scored trial. Whether a criterion changed after a red counts as loosening is Seat 1's and the interrogator's call.

**Builder interpretations 1–7**
1. **Output-time grid: meets.** My +1 partition was the latency, which render_cli removes. Rechecked at P = 512: ⌊24000/512⌋ + ⌊47913/512⌋ = 46 + 93 = 139, and 139 × 512 = 71168 ✓. ⌈217440/512⌉ + ⌈172641/512⌉ = 425 + 338 = 763, and 763 × 512 = 390656 ✓. S3 passing at −132 dB with zero delay is what pins the compensation at exactly P. Keep it that way, and state in S3's text that the delay is 0 in compensated output.
   - **Anchor margin 0: meets.** X₄₆·H₉₃ puts FFT rounding across the whole of output block 139, so a first difference exactly at 71168 is expected. The assert is "identical before the bound", and the margin is print-only.
   - **Fix one print:** P2 says identical on [0, 47912) but gives the first difference as 47913. Tap 47912 is unaccounted for; print the ranges consistently.
   - **Check passes:** n_d/48000 + alignmentShift (≈ 0.1168 s) = 1.1150 s = t_mix,e − 2.5 ms.
2. **Prefix window:** Seat 1's matter. The L_f − alignmentShift arithmetic is consistent with the IR-time check under item 1.
3. **Trim: meets.** The trimmed tail is asserted 0, and B's IR ends before the input length.
4. **scipy WAVs: meets,** with one condition: assert that the arrays read back from the written WAVs equal the checked arrays.
5. **Trial plan:** Seat 1's matter.
6. **Seeds: meet.** New condition: **the dry input peaks at +3.05 dBFS.** Assert that render_cli's input read is lossless above 1.0 (round-trip equality of the input). Or pre-scale by an exact power of two and undo it after the render. A clamp on input would hit both arms, so S3 would still pass while broadband products are added to the hold.
7. **P4′/P5′ do not meet my P4/P5,** which are 1e−9 asserts ("in Catch2 or through a dump", 4-seat3). Keep P4′/P5′ as kit cross-checks.
   - **Required:** the proposed `[ax49-l4]` Catch2 case must be written, green on all three CI platforms, and in place before the seal. It is not a proposal.
   - **Negative controls inside it:** N-L1 (hard cut) must fail P5. N-L2 (another seed) must fail P4, as I specified. The CLI-level N-L2 passing P2 is expected, but it does not replace that control.
   - **P6:** the 125 Hz share of 0.0154 is above 0.0134. That is one realisation and stays print-only. Note that 63 Hz–1 kHz passes AX49's ≥ 18.7 dB by only 0.02 dB (18.72).

**7. Hand-offs**
- Seat 1: the criterion, its reference band, and whether C counts as loosening.
- Seat 8: voicing and brightness under B.
- Seat 5: running `[ax49-l4]` in CI.

**8. Premortem.** If B is chosen, the L4 null is bought with about 1 dB less sensitivity at the cut. If A alone is chosen, the rebuild reds again at about −22.3 dB and the builder sees the stall first.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/11-builder-l4-kit.md
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md
- /home/user/makroof/docs/review/phase-07c-2b/8-seat3.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat3.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md (L96–99, by grep)
