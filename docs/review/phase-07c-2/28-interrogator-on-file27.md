# 28 — Interrogator on decider file 27

**Interrogator: file 27, the decider's round 3 (D-W2 ABX kit). Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.**

None of the three decisions survives as written.
- **M1:** UNDERCONVENED.
- **M2:** TENSION MISREAD.
- **M3:** TENSION MISREAD and UNDERINFORMED, with INCONSISTENT amendments and a minor PRD MISREAD.

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M1 | convening | Seat 2 given 0/0 | UNDERCONVENED | Seat 2's README row covers "late-tail statistics" and "the representation handed to the renderer". E_target = E_spec + E_diff (Engine.cpp L183) is that representation. Seat 2 raised M1 itself ("resolve this before ruling M1") but was never asked to rate it. A 0/0 is only for a seat that is not required or answered NOT MY MATTER, and Seat 2 was neither. | UNDERCONVENED | Will you put Seats 1, 4 and 9 down as not required, with reasons, and get M1 ratings from Seat 2? |
| M1 | ordering | summary gives "sum 1" for A | IMPRECISE | A's sum is 0. B's is 3 (1 + 2). | correction | |
| M1 | D4-L2 | the tail window holds no specular energy | CORRECT | crossfade gives {0, 1} once τ ≥ 1 (NoiseTail.cpp L278–279). Amplitude = √(E_target/ē) (Engine L531–532). E′_target = k·E_target (Cli L788). The refusal condition is g < 10·log10(share). | — | |
| M1 | item-5 sentence | "refuses a down-step when…" | IMPRECISE | It leaves out the second refusal: a band with only specular energy is refused at any g (Cli L781–786). | correction | |
| M2 | debt | T-a: Seat 1 later 1, Seat 9 later 1 | dropped | Seat 1: "Another scene could give an unstable value." K3 finding 7: the heard-IR T30 moves with the scene, and the Q5 window was not rerun. Amendment 4(ii) adds exactly such a second scene. | TENSION MISREAD | Where in the register are the T-a debts, and what heard-IR T30 does the (ii) scene give? |
| M3 | map | S-C, Seat 1 at 0/0 | faithful | Seat 1's condition was capped at m = 6–8 and wetter. K3 confirms both: capped yes/yes/yes, heard D/R 8.3 against 13.1 dB, tail −5.5 against −10.5 dB re direct. K3's own word "drier" contradicts its numbers. | — | |
| M3 | map | S-A′, Seat 1 at 1/1 c | condition unmet | Seat 1 required that "the 08-3 rerun (item 15) uses the S-D scene". Its S-D draws on layouts 4 and 5 and falls back to listener_wall. Amendment 4 drops layout 5, excludes listener_wall and allows (ii) to be omitted. The decider concedes the rule differs. The cell is 2/2. | TENSION MISREAD | |
| M3 | map | S-A′, Seat 3 at 1/1 c | condition unmet | Seat 3 required "a rerun on an s < 1 scene before 08-3". Amendment 4's filter (ΔC80 at 0.9 dB ≥ S-A's) excludes every s < 1 candidate (see the amendment-4 row). The cell is 2/2. | TENSION MISREAD | |
| M3 | map | S-A′, Seat 9 at 1/1 c | only promised | Seat 9 required that the rerun "is not done on this scene alone". Amendment 4 says "If none qualifies, (ii) is omitted". | TENSION MISREAD | |
| M3 | map | S-A′, Seat 2 at 0/0 c | partly met | Seat 2 asked for a trigger: on any B11 promotion, the stimuli are rebuilt. Amendment 4 narrows it to "before 08-3", with "marked void" as an alternative. | TENSION MISREAD | |
| M3 | map | S-A′, Seat 4 at 0/1 c | met | Amendment 4 carries conditions (a) to (d) word for word. | — | |
| M3 | map | Seat 9's "0.43 kept" at 1/1, and its condition "premise corrected on the record" | omitted | The rating is absent from both the map and the register. | TENSION MISREAD | |
| M3 | ordering | "S-A′ still wins on the sum" | not shown | On the faithful cells S-A′ has a maximum of 2 and a sum of 11–15, against S-C at 13 and S-D at 13–14. The winner is unsettled. | redo | |
| M3 | D4-L1 | S-B uncapped at s = 0.3 (all m) and s = 0.6 (m = 8) | CORRECT | K3 main table. | — | |
| M3 | D4-L1 extension | s = 0.25 and 0.4 uncapped | NOT CHECKABLE (unmeasured), load-bearing | It assumes N_need is monotone in s, which rests on two points from 05b2. An S-B at s = 0.4 under Seat 2's conditions would give S1 2/2, S2 1/1, S3 1/1, S4 0/1, S9 1/1: maximum 2, sum 10. That could win. | UNDERINFORMED | Builder: cap flag at m = 6/7/8 and peak level for s = 0.25 and s = 0.4. |
| M3 | D4-L3 | S-B's tail share is below S-A's | CORRECT | Tail share at 1 kHz, emitter L: S-A 0.089/1.090 = 0.082; S-B 0.3 0.129/3.76 = 0.034; S-B 0.6 0.098/2.075 = 0.047. These give ΔG of 0.079, 0.033 and 0.047 dB (K3 rows). | — | |
| M3 | D4-L4 | Table 5.2 case 4: Eyring 1.38 s, iteration 1.21 s, other faces α 0 | CORRECT | Kuttruff Table 5.2 and its Note. Check: 0.161·6000/(2200·−ln(1 − 600/2200)) = 1.38 s. | — | |
| M3 | label | "−10 dB at r/r_c 3.2" | IMPRECISE | Kuttruff Eq. 5.44 uses Sabine's T, i.e. A. With A ≈ 640 m²: r_c = √(640/16π) = 3.57 m, r/r_c = 3.47, D/R −10.8 dB. | correction | |
| M3 | amendment 4 | candidate pool for (ii) | INCONSISTENT | Vorländer Eq. 6.7: C80's late window runs from 80 ms to ∞. At s < 1 it holds unscaled images (the first at 59.7 ms, K3), so ΔC80 < g. On S-A, ΔC80 ≈ g because 80 ms to t_mix holds only 1.8e−7. This is the decider's own D4-L3. What is left is layout4_s1/emitter_wall (test_diffuse_wsweep L100), or nothing. So the Reversal condition and Seat 3's "repaid when" cannot be met. | FALLS (amendment) | Which s < 1 candidate could pass ΔC80 ≥ S-A's? |
| M3 | amendment 4 | "its own Bonferroni split" | changes α or leaves it undefined | Binomial, n = 16: P(≥12) = 2517/65536 = 0.0384, P(≥13) = 0.0106, total 0.049. Splitting across two scenes gives each ≤ 0.0245, so the thresholds rise to ≥13 and ≥14 and item 13's power changes. Without a split, the FWER across scenes is 0.098. Item 4 also does not say what a detection on (ii) decides. | INCONSISTENT | |
| M3 | amendments 2 and 3 | "never generalised beyond that class" while "AX47 itself is unchanged" | INCONSISTENT | AX47 "From 07c-2" admits statistical sources for every scene after the self-ABX. | INCONSISTENT | |
| M3 | amendments 1 and 3 | | faithful | Thresholds, α, trial counts and item 4 are untouched. | — | |
| M3 | convening | Seat 7 | UNDERCONVENED | File 24 left Seat 7 out because "every option costs minutes". S-A′ adds person-sessions at 08-3 (registers of Seats 1, 3 and 4). That is "schedule and complexity cost of an option", in Seat 7's row. | UNDERCONVENED | |
| M3 | strongest objection | stronger one | — | Under the filters, (ii) is emitter_wall: still empty under AX21, with an emitter 0.1 m from a face. Seat 4 rejected exactly this for the binaural rerun on S-C: the wall reflection that defines the position is "zeroed by (1−α)(1−s) = 0". | — | |
| all | PRD proxy | NFR-8 cited only as "nothing tuned" | PRD MISREAD | PRD L112 also says "Any valid scene renders correctly". That clause bears on evidence scoped to one class while the bound covers all scenes. S-A bare is never shown against NFR-1 or NFR-8. S-C and S-D are never shown against NFR-8. S-C "strains NFR-1" for being "still empty" while S-A′, equally empty, "serves" it. | PRD MISREAD | |

**On your specific points**
- **Convening.** M1 is UNDERCONVENED for Seat 2. Seats 1, 4 and 9 can be not required, but they must be recorded as such with reasons; a convened seat may not be given an invented 0/0. M2 convening is acceptable, though Seats 2–4 also need not-required rows.
- **Load-bearing claims.** The s = 0.25/0.4 inference is not a technicality, because a capped s = 0.4 could win the ordering.

**Questions for the rebuttal round**
1. Where in amendment 4 is Seat 1's S-D pool (layouts 4 and 5, listener_wall as fallback), and where is a guaranteed s < 1 rerun? If neither is there, give the S-A′ cells as 2/2.
2. Which s < 1 scene could meet ΔC80 ≥ S-A's under Vorländer Eq. 6.7?
3. Are s = 0.25 and s = 0.4 capped at m = 6–8 (a builder measurement)?
4. Does (ii) split α 0.049? If it does, what are the new c/16 thresholds and powers?
5. How is "never generalised beyond that class" reconciled with AX47's admission of statistical sources for every scene?
