# 33 — Interrogator on decider file 31 (M1, M2, amendments now applied)

**Interrogator on file 31: M1, M2 and the amendments now applied.** Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

Both decisions survive with corrections, and so do the item-5 sentence and the M2 debt register. Item 6's amendment and the T-a label survive as written.

| item | check | finding | outcome |
|---|---|---|---|
| M1 | convening | Seats 2 and 3 are convened; the other seven have reasons. File 28 accepted Seats 1, 4 and 9 as not required. Seat 2 handed Seat 1 a question about B's power (file 30 §7). That bears only on B, which already has max 2, so it can't change the winner. | faithful |
| M1 | map | Seat 2 (file 30) gives A 0/0 and B 1/2, "no longer uniform across all 8 bands". Seat 3 (file 26) gives A 0/0 and B 1/2, "step shrinks and stops being uniform". Sums are A 0, B 6. The register is empty, which is right because no seat rated A later ≥ 1. | faithful |
| M1 | D5-L1 | **CORRECT.** L788 combined with Engine L181–183 gives E′_diff = k·E_diff + (k−1)·E_spec, so E′_target = k·E_target. The spec = 0 branch (L776–779) gives the same. The crossfade returns {0, 1} once t ≥ t_mix + 2.5 ms (kCrossfadeHalfS = 0.0025, MixingTime.h L27). The amplitude is ∝ √E_target on both the exact and non-exact paths. The specular share is 0 at s = 1: Kuttruff §8.8, Eq. 8.59 gives I_spec/I_0 = (1−s)(1−α). | correction: cite Engine L181–183 next to L788 |
| M1 | reversal condition | **INCONSISTENT.** "An item-6 failure on any scene" has already happened: K4 fact 6 records the click-detector failures on listener_corner and both_wall. Both are s = 1 scenes with share 0, where A and B render the same stimuli, so those failures cannot tell A from B. The condition has to name what A governs, which is item 6's identity assertions. | correction |
| Item 5 | sentence | **IMPRECISE.** The refusal algebra is right: steppedRef < 0 ⇔ k < share. Three problems remain. (a) "Last clause replaced" doesn't say whether file 27's scene-specific sentence ("On layout4_s1/default that share is 0…") survives; the full sentence should be stated. (b) The list reads as exhaustive but leaves out L755–758, which refuses any scene with no diffuse level, at any g. (c) Refusal (2) needs spec ≠ 0 and g ≠ 0 (L762, L776). | correction |
| Item 6 | file 27 amendment 1 | Print-only. It depends on the kit's print fix, which has not been made yet. | SURVIVES |
| Run sheet | T-a label | Label only. The numbers in items 7 and 8 and Q5 stay at 2.009 s, and the ceiling is 0.43 × 2.009 = 0.864 s. No threshold, α, trial count or item-4 rule changes. The same holds for items 5 and 6 above. | SURVIVES |
| M2 | convening and map | S1 0/1 and 1/1, S9 1/1 and 1/1, sums 3 and 4: all as the seats wrote them (file 26). | faithful |
| M2 | debt, Seat 1 row | **IMPRECISE.** (a) Seat 1 named "K3 or the 08-3 binaural rerun" as the evidence. The row keeps only "a second scene" and drops item 15(i), the S-A binaural rerun. (b) The repaid-when test (Q5's ≥ 20 dB onset assertion) doesn't check the premise the row itself names, "gap longer than the tail's own decay". That needs the gap or heard T30 printed against the tail T30. (c) The example is weak. K4 gives no tail T30 for listener_corner, and 1.288 s is above S-A's tail T30 of 1.25–1.27 s. Layout 5 is the measured case: heard T30 2.557–2.575 s against a tail-alone T30 of 2.58–2.62 s (K4 fact 9). | correction |
| M2 | debt, Seat 9 row | Seat 9's premise "gaps ≥ 2.009 s also exceed 1.26 s" is specific to S-A, and the row doesn't carry it. It fails on layout 5 for the same reason. | correction |
| Both | PRD proxy | NFR-1 (L105) and NFR-8 (L112) say what is claimed. Every survivor is shown against them, nothing points another way, and no recorded decision is amended. | no PRD MISREAD |

**Does M1 or M2 presume an M3 outcome?**
- **M1:** only through the clause in (a). If file 27's "On layout4_s1/default…" sentence is kept, it ties the item-5 sentence to S-A. The claim that the fade-out lies inside the 0.1 dB tolerance needs s_w ≤ 2.3 %, since 10·log10(1 − 0.023) = −0.10 dB. Every K4 candidate meets that; the worst band is 1.2e−2 at s = 0.25.
- **M2:** yes. T-a's zero cells rest on heard T30 being at least the tail T30. That holds on S-A but fails on layout 5, so under V3 T-a's premise is false by 1–2.5 %. The register must tie that check to M3's scene choice, and to item 15(i).

**Questions for the decider**
1. What is the full item-5 sentence, and does it list L755–758?
2. What is M1's reversal condition, given K4 fact 6?
3. What test repays Seat 1's T-a premise, gap against tail T30, on layout 5 and on the binaural S-A rerun?

Files: /home/user/makroof/docs/review/phase-07c-2/31-decider-abx-r4.md, /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md, /home/user/makroof/src/cli/Cli.cpp, /home/user/makroof/src/sim/Engine.cpp, /home/user/makroof/src/sim/tail/MixingTime.h
