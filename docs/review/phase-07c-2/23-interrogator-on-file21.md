# 23 — Interrogator on decider file 21

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I reviewed /home/user/makroof/docs/review/phase-07c-2/21-decider-abx-kit.md against files 13 and 14, /home/user/makroof/tools/ci/abx_kit.py, the run sheet, docs/PRD.md and the corpus. No point survives as written, but none of the conclusions is reversed. Each needs the corrections below.

**Convening, all points: UNDERCONVENED (the rule applies by construction).** File 21 has no nine-row convening table. The matter touches three seats' rows in the README:
- Seat 1: "blind-test paradigm, … signal". The onset window is part of the stimulus design.
- Seat 9: the 0.43 figure is Seat 9's arithmetic, and the measurement has now overtaken it.
- Seat 3: the diffuse/specular split in item 5; the specular-share print is Seat 3's.

The fix is cheap: a nine-row table, with each seat convened or given its not-required reason.

**Item 5, D1-L1: IMPRECISE. Outcome SURVIVES WITH CORRECTIONS.** Worked from the kit formula the decider quotes (E'_diff = k·E_diff + (k−1)·E_spec):
- With specular share s, only the diffuse part changes. Its amplitude scales by a = √((k−s)/(1−s)), so the difference energy over the unstepped tail energy is (a−1)²(1−s).
- Item 6's identity requires (√k−1)². The two are equal only at s = 0.
- Example, g = 0.9 dB and s = 0.5: 0.0217 against 0.0119.

So file 13's reading meets the energy-step assertion (`step_db`, line 226), but neither reading meets the identity (`diff_db`, line 225) when s > 0. "Only file 13's reading is consistent" is therefore an overstatement. Two things still hold:
- On `layout4_s1/default` s = 0 in every band, so the ABX is unaffected.
- The choice of file 13's reading still follows, because file 5's reading meets neither assertion.

Required correction: drop "as item 6's formula requires" from the sentence to be added. State instead that the identity is exact at s = 0, and that at s > 0 the kit's assertion fails rather than passing a wrong stimulus.

**2a, "no amendment": SURVIVES.** File 13 (lines 132–140) pre-registers three things: a ceiling ("no later than 0.43·T30"), the measured ≥ 20 dB assertion on every stimulus, and replace-and-record. The realised window [0, 0.187·T30] lies inside that bound, and is produced by those rules. The test statistic, the 13/16 threshold, the FWER and the stated power at an assumed p are all unchanged. What was pre-registered and how it is analysed both stand. Recording the realised window before sealing is right.

The decider's reading of file 14 is faithful. File 14's Q5 row rates the 0.43 figure CORRECT (computed) and says "the measured assertion is authoritative".

**2a, D2-L1: arithmetic CORRECT, premise INCONSISTENT. The "not a malfunction" claim FALLS until 2b reports.**
- Arithmetic: (46 − 13.1 − 20)/60 = 12.9/60 = 0.215 ✓.
- Removing D/R from the tail level is sound in the stationary diffuse model (Kuttruff §5.6, Eq. 5.42–5.45; Blauert ch. 3, "stationary signal" passage).
- The input is +13.1 dB, and 2b in the same ruling suspects that number. Diffuse theory gives about −10 dB. With that value the reverberant level is about 0.4 dB below the total, and the window comes back to about 0.43·T30. The 0.187 cutoff would then be unexplained.
- Two further conditions are unstated. A sentence is not stationary speech. The 46 dB SNR (R35, not in the corpus, NOT CHECKABLE) is broadband, while the assertion is made in the 1 kHz band.

Required correction: make "not a malfunction" conditional on 2b. Add "the D/R print changes" to the recompute trigger, which currently names only the scene or T30.

**2a, "expected replacement rate (46/81)": IMPRECISE.** 46/81 = 0.568 is the chance that a stimulus's first draw is replaced. The kit draws without replacement (lines 595–603), so the expected number of replaced onsets per stimulus is 46/36 ≈ 1.28. Also, 35/81 × 0.4333 = 0.187 matches the logged 0.187 only if the passing boundaries form a contiguous early run. The kit records only their count and the latest one, so the manifest should say so.

**2b, D2-L2: CORRECT under its conditions.**
- From Kuttruff Eq. 5.43–5.45, direct/diffuse = r_c²/r², so D/R = −20·log10(r/r_c). At 3.18 that is −10.05 dB ✓.
- The kit's 0.057·√(V/T) matches Eq. 5.44 (0.1/√π = 0.0564). Note that Eq. 5.44 is stated with Sabine's T, and the kit cites "Eq. 5.40 family".
- With the measured T30 the gap grows: r_c falls by √(1.291/2.009) = 0.80, r/r_c becomes 3.97, D/R −12.0 dB, a gap of about 25 dB.
- One of the decider's two leads is weak. Summing the two emitters' IRs can raise D/R by at most about 3 dB, and only if both direct sounds coincide. If one falls outside the window, D/R goes down. It cannot explain about 23 dB.
- Toole (Fig. 4.2–4.3) notes that real reverberant level falls with distance, which also cannot reach 23 dB.

The check before sealing stands.

**Decided for Maisara: PRD MISREAD (options not shown).** The README's "Who answers" section requires one line per option against the cited ids. The section does not show:
- file 5's reading against NFR-1;
- amending against not amending, for 2a;
- sealing now against checking first, for 2b.

"No seat gives anything up" rests on a map that was never built. NFR-1 itself is read correctly: it says "pass listening tests" and "Pass thresholds come from the Expert", which supports both the reading and the 2b check. The NFR-8 use is also correct. No AMENDS line is needed.

**Questions for the decider:**
1. If 2b finds the +13.1 dB is a print artefact, what explains the 0.187·T30 cutoff, and does 2a still hold?
2. At s > 0, does the kit's `diff_db` assertion (line 225) pass under file 13's reading? Show the numbers.
3. Which seats do the nine-row table mark not required, and with what reasons?
4. Is the passing set of 35 boundaries contiguous from the first one? Give the manifest field.
5. Give one line per option against NFR-1 for item 5 and for 2a.
