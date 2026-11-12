# 6 — Seat 1, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 1, round 2 (phase 07c-1). This covers only what changed. Source: `/home/user/makroof/docs/review/phase-07c-1/5-decider-decision-r1.md`. I give one rating and three corrections below; each correction is a test detail, not a change of my position.

**B4-G (B4 plus the SE ≤ 0.5 dB admissibility gate): now 0, later 1. Prefer.**
- **Now 0:** in 07c-1 the step is 0 on every path. Stage 1 is the final solve, a matching saved E_b is bit-identical, and B1's edit step is outside D-C1's scope.
- **Later 1:** the arithmetic holds: 1.96 × 0.5 dB = 0.98 dB ≤ 1 dB p95 per band. My one remaining debt is the load fallback when stage 1 is inadmissible. I accept deferring it to 07c-2's loop, decided on measured stage-1 times, as long as the option it lands on still meets AX47 (a step of ≤ 1 dB, or one recorded equal-gain step) and conditions 5 and 9.

**D3\* (synchronous at load, background on edits): now 1, later 1. Prefer.** This holds only if the acceptance test is written as follows. The decider's text leaves two gaps open.
1. **No compensation gain for truncation.** "Normalised to expected energy" must mean only the generator's unit-variance normalisation. If the prefix is scaled up to make up for the missing late energy, the head of the tail plays too loud. A whole-IR band-level test would still pass, so it would hide the fault.
   - The 1 dB check therefore compares band energy over the common window [t_mix, L_p] of the provisional and exact tails. A second check covers the whole tail window, where the energy lost to truncation must itself stay ≤ 1 dB.
   - Per band, that means the prefix must reach at least 6.9 dB of decay: 10·log10(1 − 10^(−0.1)) = −6.87 dB. This is my arithmetic, not a corpus figure.
2. **L_p is set by a generic rule from the scene's T60s,** so NFR-8 is satisfied. The rule: per band, L_p is at least the time the exact decay reaches −10 dB, plus the 50–100 ms fade. Then EDT is computed from the same samples as the exact tail and lands within 5 % (Vorländer Table 6.1) by construction, not by tuning.
   - At an 8 s T60 this means L_p ≥ about 1.33 s plus the fade. It is that long only for long-T60 scenes; whether it fits inside the R1 0.5 s synchronous budget is Seat 3's and Seat 5's call (reversal 1).
   - A note on what remains audible: on a stop chord in an 8 s room during the roughly 3 s interim, the tail will still be heard ending early. I accept that for the interim. It is [Hyp]: no corpus figure covers how audible a truncated late tail is.

**AX47 reading: confirmed, with one correction.**
- I accept that the test asserts on IR band levels. The IR is linear in the amplitudes and deterministic, so this is the correct primary statistic, and my 50 ms windows were statistically too short at 63 Hz.
- **Correction:** the band level must be measured over the tail window (from t_mix to the end, or the common window for the provisional), not over the whole IR. AX47 bounds the tail level. A whole-IR level includes the direct and early energy, which dilutes a tail step: by the researcher's D1 arithmetic, a 1 dB tail step reads as about 0.5 dB at D/R 0 dB. The test would then accept tail steps of up to about 2 dB in dry-ish scenes.
- The wet noise and speech render stays as the overshoot check: no mid-fade value above the louder endpoint.
- My reversal is unchanged: the 07c-2 self-ABX (16 trials, the capped layout-4 scene, noise and speech). If a step under 1 dB is detected, the bound goes to 0.5 dB.