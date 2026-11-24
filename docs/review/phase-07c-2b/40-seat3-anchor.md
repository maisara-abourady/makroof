SEAT 3 POSITION (file 38: (1) the L4 anchor; (2)–(4) how assertions 7, 4 and 2 are read)

**1. Reading.**
- **(1)** `--abx-step-db` can only lower the tail as far as the diffuse part allows. On the L4 scene the specular share is 0.828, so the deepest down-step is 10·log10(0.828) = −0.82 dB, and the anchor's "3 down" half cannot be built.
- **(2)–(4)** concern how three of my own L4-D conditions are read.
- Cues: decay accuracy, and the state-change classes at the IR and render level.

**Correction on my own record first.** My L4-D condition 8 (file 9) asked for "B against B with the tail **+3 dB**, via --abx-step-db with step sample 0", built on the L4 scene and chord. It asked for an up-step only. The "3 up, 3 down" form arrived later. So A-i is what condition 8 asked for, and A-ii meets it too.

**2. Ranking, part (1).**
- **A-ii (roles swapped, same two files): prefer.** The stimuli are static, whole-file renders, because step sample 0 means no transition. So "up" and "down" differ only in which file is the reference. Swapping the roles 3 and 3 balances any order or label bias at no cost. Whether that balance matters is Seat 1's call.
- **A-i (up-only): prefer, nearly as good.** It is the same pair of files without the balance.
- **A-iii (a new tail-gain path): can live with.** It adds code and buys nothing that a static anchor needs.
- **A-iv (anchor on another scene): can live with, rated 2 now.** It **breaks condition 8.** The anchor's job is to check the chain and the listener's attention on this exact task: the 16.6 s chord stimulus, released into 12 s of free decay at T60 8 s. A scene where −3 dB builds needs a lower specular share, so it has a different early-to-tail balance and probably a different decay. It is not the L4 scene.
- **A-v (3 dB on the whole wet render): can live with, rated 2 now.**
  - It is outside item 2's "tail step".
  - A whole-render step is a level cue during the hold, which is far easier than any tail cue. The anchor would pass trivially and stop testing attention to the tail.

**3 and 4. Tension now / later (0–3).**

| option | now | later | reason |
|---|---|---|---|
| A-ii | 0 | 0 | no new code; meets condition 8 |
| A-i | 0 | 0 | no new code; meets condition 8; no order balance |
| A-iii | 1 | 1 | a new flag to guard (Seat 5) and keep up, for a static design that does not need it |
| A-iv | 2 | 1 | condition 8 broken; undone by going back to A-i |
| A-v | 2 | 1 | outside item 2's bound; the anchor is weakened |

**What A-iii should scale, if it is chosen.**
- It should scale **E_target, the quantity M1 settled**: the tail's amplitude √(E_target/E_unit) at assembly, specular and diffuse together, including the tail's share inside the AX18 crossfade at t_mix,e. It should not touch the image list.
- It should not be a gain on the IR taps past t_mix,e + 2.5 ms. That would leave the tail inside the crossfade unscaled, and the step would no longer be the one --abx-step-db makes.
- Acceptance test: where both paths build (for example g = +3 and g = −0.8 on this scene), the new path's IR is bit-identical to --abx-step-db's. Then nothing changes in Seat 2's M1 except the reach.

**6. Conditions of acceptance, part (1).**
- **A-i and A-ii:** the +3 dB anchor IR on the L4 scene must pass M1's checks.
  - The per-band step identity is asserted within 0.05 dB. The identity is exact at any specular share (file 34 item 1).
  - s_w ≤ 2.3 % is printed and asserted.
  - The peak is ≤ −3 dBFS; the builder measures −9.93.
- **A-iv:** to lower now to 1, it needs the same chord and the same timing, and T60_max 8 s with L_p < L. At that point A-i is simpler.
- **A-v:** none lowers it below 2 within item 2.

**Part (2)–(4): the readings.**

**(2) Assertion 7 read on the model: accept. Now 0, later 1.**
- My condition 4 copied AX49's acceptance clause, which is a statement about how the tail is built: 60·0.312 = 18.72 dB at the T60_max band.
- The realised 63 Hz Schroeder drop of 18.47 dB comes from one noise realisation in the narrowest band. The bandwidth–time product over the window is roughly 44 Hz × 2.5 s ≈ 110, so the expected scatter is about 1/√110 ≈ 10 % in energy, about 0.4 dB. A 0.25 dB shortfall sits inside that [Inferred; tag: researcher or builder may confirm with a 16-seed ensemble via --ensemble --tail-only].
- **Correction to the decider's wording.** Assertion 8 does not measure "the same quantity" as the drop from t_mix,e. It measures K17′'s bound counted from emission, energy past L_f over the whole decay (K21).
  - Arithmetic: the model gives 10^(−(18.72 + 0.49)/10) = 0.0120, where 0.49 dB = 60·0.0647/8 is the decay before t_mix. The realisation gives 10^(−(18.47 + 0.49)/10) = 0.0127.
  - Both are ≤ 0.0134, and they are consistent with the measured 0.0124.
  - So assertion 8 covers the realised side of K17′. It does not prove a realised drop of ≥ 18.7 dB from t_mix.
- **Condition:** the print reads "realised drop, one realisation, not asserted". The non-detection wording quotes the realised cut depth (the builder's "≥ 21.7 dB below the full-IR energy"), not the model's.

**(3) Assertion 4 kept and recorded as weak on this scene: accept. Now 0, later 0.**
- Here f_b ≈ ρ_b, so the predicted steps are below 0.01 dB.
- The red test (a provisional 1.2 dB too hot) still fails it, so the check bites on what it is for.
- It becomes informative on 07d's candidates at other fractions. Keep the tolerance at 0.05 dB.

**(4) Assertion 2 on the renders: accept. Now 0, later 0.**
- The exact claim lives on the IRs: bit-identical to tap 3007, which is the tail fade start.
- On the renders, partitioned FFT convolution mixes whole partitions, so a rounding difference shows up from the partition boundary (6656), not from the fade start. That is the convolver, not the provisional.
- **Condition:** the null over [6656, 7103) is defined as max |A − B| ≤ −120 dB relative to B's peak, per sample (the Phase 06 criterion). The measured first differing sample (6658) is printed.

**5. Evidence.**
- Specular share 0.828, the −0.82 dB limit, the 63 Hz drop of 18.47 dB, share 0.0124, the taps (3007, 6656/6658, 7103) and the +3 dB peak: builder file 26, from the code.
- M1 scales E_target: file 34 item 1.
- K17′ (Vorländer §6.4.1 Eq. 6.4) and the backward-integration decay (Kuttruff §8.4 Eq. 8.29); the arithmetic above is mine.
- Realisation scatter about 0.4 dB: [Inferred], not sourced in the corpus.

**7. Hand-offs.**
- Seat 1: whether order balance (A-ii over A-i) matters, and whether the chance of passing ≥ 5/6 by guessing changes. Static files should leave it at 7/64.
- Seat 2: M1's reach under A-iii.
- Seat 5: A-iii's guard and its equivalence test.
- Seat 7: hours. They do not change under A-i or A-ii.

**8. Premortem.** If A-v or A-iv is chosen and fails, it fails like this: the anchor passes on a level cue or on another room, while a listener who drifted off during the 12 s decays scores L4 at chance. The result is recorded as "not detected". Seat 1 notices first, when the anchor scores are 6/6 against an L4 score at chance.
