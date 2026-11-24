
# 3: Interrogator on file 2 (decider M3, phase-07c-2b scope 2, round 1)

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. I did not read the round-2 files (`4-seat*.md`). They belong to the rebuttal round.

## Verdict in brief

**M3-1 does not survive yet.** Its corpus facts and numbers all check out. Two things stop it:
- **Seat 7's now cell (TENSION MISREAD, unconfirmed and decides the winner).** The decider reads Seat 7's condition as 1/1. Seat 7's own reason for its now column is hours, and V1-W leaves the hours unchanged. If that cell is 2, the ordering picks a different winner.
- **The acceptance check (PRD MISREAD by omission).** Two surviving options are not shown against the check's PRD ids.

**The other parts:**
- **M3-2.** Deferring α is sound, and M3-1 does not depend on how α comes out. The four-family declaration still needs the round-2 confirmation the decider has already asked for.
- **M3-3.** HF-W's arithmetic is correct. Seat 3's cell was never given by Seat 3, and the PRD lines show no options.
- **M3-4.** Survives with corrections.
- **M3-5, M3-6, M3-8.** Survive.
- **M3-7.** Partly UNDERCONVENED. Two items marked "decided now" are the same items M3-L4 asks Seats 3, 5 and 7 to rate.
- **Deferring the L4 design to M3-L4 is sound.**

## Checks

**Convening.** File 31's nine-row table applies. Seat 8 is not required ("a validation stimulus; item 13 forbids public copy"). That fits Seat 8's README row: the scene, the speech material and the labels are validation-only, not producer workflow. Convening is correct for M3-1 to M3-6 and M3-8. It is not correct for M3-7's render path and pre-seal build (row G1).

**Tension map, rebuilt from the seats' words.**
- V4 is Seat 1's own later 3: "No phase ever tests a measured, qualifying scene whose programme-level step is about 14× S-A's". The veto is faithful.
- The V1, V2, V3 and V4 cells match the seats' reports, with two exceptions:
  - Seat 6 wrote that V2, V3 and V4 "carry no α tension for my seat", but the map gives them 1/1.
  - The header says Seats 5 and 6 are rated at "the higher of the two α cells". That is wrong for Seat 6: its 13/13 split cell is 1/2, higher than unsplit at 1/1. The map actually uses unsplit plus C1, with the 13/13 split excluded.
- **Read cells for V1-W:**
  - Seat 1, 1/1: follows from "V1, to 1/1: S-W runs in 07c-2 as well, ahead of S-A". V1-W meets that.
  - Seat 2, 1/1: follows from its V2 label condition and its "Any S-B\*" condition. The both_wall label carries the 0.1 m, missing-reflection and tone-colour wording; the dip print and the partial-AX21 label are present.
  - Seat 4, 0/1: rests on condition (b). Item 15 narrows (b) from "never counted as binaural evidence for the class" to non-detections only, while F3 can still reverse AX47. Round 2 is asked to confirm this.
  - Seat 5, 1/1: follows from C1 attached under unsplit. Under the 24-trial split its split rating of 0/1 applies, so the cell stays at most 1 either way.
  - Seat 9, 1/1: follows from "no seat represented". The label says "represents no seat".
  - **Seat 7, 1/1: not established.**
    - Seat 7's now reason for V1 is "About 4.3 h gating the whole remainder of 07c-2b … the person's calendar sets the phase's end date".
    - Its condition "V1, to 1: the 07c-2b pair becomes S-W plus S-B\*, so the sensitive scene comes before the pin" answers only the later reason ("S-W's first run comes after the golden round").
    - V1-W keeps about 4 h plus L4 in 07c-2b.
    - Against that, Seat 7 wrote "V4, later to 1" with a column and "V1, to 1" without one, so both readings exist.
    - The decider chose the one that favours its winner and sends the question to round 2. The decision cannot stand before Seat 7 answers.
- **V1′'s read veto.** Seat 1's V4 reason and its unmet V4 condition ("S-W replaces S-B\* at 08-3") both apply to V1′, so the reading is consistent. It does not matter: without the veto, V1′'s highest cell is still at least 2 (Seat 1 now 2; Seat 7 2/2 read from V1), so it drops out at step 3 anyway.

**Debt register.** Every later cell of 1 or more on V1-W is in the register: Seats 1–7 and 9, with Seat 9 on two rows. Each "repaid when" names something that exists: 08-3, O10, O4, or the AX38 (iv) records. One hidden premise: the trigger is expected to fire at O4. Item 15 then defaults to "void unless the omni family is rerun", so Seat 7's row of "about 4 h at 08-3" holds only if the void branch is taken.

**Ordering.**
- Sums recomputed: V1-W 15, V2 (conditions met) 15, V2 raw 18, V3-default 16, V3 as written 18, V1 20, gated S-B\* 15. All correct.
- With the cells as read, V1-W is the only survivor whose highest cell is 1, so it wins at step 3.
- If Seat 7's now cell is 2:
  - V1-W has max 2 and sum 16.
  - V2 (conditions met) and gated S-B\* tie at 15, or at 13 each if Seat 6's V2-family cells are 0/0 as it wrote.
  - The tie goes to reversibility. "V2 would win on sum" is therefore imprecise.
  - The FOR MAISARA the decider announced for this case does not hold as reasoned:
    - L49 and L101 rank accuracy against CPU and latency, not against listening hours.
    - NFR-8 L112 ("Any valid scene renders correctly; no environment-specific code paths") says nothing about which evidence comes before the pin.
    - V1-W and V2 both run S-W before the pin and both scene classes by 08-3. What separates them is rework risk, a cost the seats carry, not a PRD ranking.

**Numbers recomputed.** All correct:
- r_c = (640/16π)^½ = 3.568 m (Kuttruff Eq. 5.44).
- Distances from file 29's coordinates: 12.373, 29.952 and 20.127 m.
- Diffuse-field D/R = 20·log10(r_c/r) (Eq. 5.45): −10.80, −18.48 and −15.03 dB, at r/r_c 3.47, 8.39 and 5.64.
- A ≈ 640 m² is consistent with Eyring T = 1.291 s through Kuttruff Eq. 5.24: 0.161·6000/1.291 = 748 = 722.7 + 4mV, so 4mV ≈ 26 m², and 616 + 26 gives about 642 m².
- Ceiling image: √(9 + 144 + 16.3²) = 20.462 m, which at c = 343 m/s (Kuttruff §5.4) is 59.66 ms, or 23.58 ms after the direct sound. The nearest wall image is 20.81 m.
- 10·log10(0.032 + 10^0.09·0.968) = 10·log10(1.22290) = 0.874 dB. Seat 2's 0.873 came from rounding a² to 1.230.
- β = (1 + 96/1440)²(1 + 10⁻⁵) = 1.13779, which is 0.561 dB.
- 10·log10(1 + 0.667·0.2303) = 0.620 dB.
- Binomial tails: 2517, 697 and 137 out of 65536; 190051/2²⁴ = 0.01133; P(at least 18 of 24 at p = 0.75) = 0.6074.
- Q5 bound: 0.639 s against 0.589 s on both_wall; 0.578 s against 0.787 s on s0.7.

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-1 | convening | Seat 8 not required (file 31) | correct | README row 8 (producer workflow, POV, translation); scene, speech and labels are validation-only | — | — |
| M3-1 | map | S7 now cell for V1-W, "1 c" | TENSION MISREAD (unconfirmed; decides the winner) | 1-seat7 §3: V1 now 2 = "4.3 h gating … calendar sets the phase's end date"; §6's "so the sensitive scene comes before the pin" answers only the later reason (§4 V1); V1-W keeps about 4 h plus L4 | waits on round 2 | Does Seat 7's now column for V1-W stay at 2 for hours? If so, redo steps 3–6. |
| M3-1 | map | S1, S2, S9 V1-W cells read from conditions | faithful | 1-seat1 §6; 1-seat2 §6 plus "Any S-B\*"; 1-seat9 §6; the labels meet them | — | — |
| M3-1 | map | S4 V1-W 0/1 c via (b) | reading to confirm | 1-seat4 §6 (b): "never counted as binaural evidence for the class"; item 15 limits this to non-detections while F3 can reverse AX47 | round 2 (already asked) | — |
| M3-1 | map | S6 cells on V2, V3 and V4 rows; header "higher of the two α cells" | IMPRECISE | 1-seat6: V2, V3 and V4 "carry no α tension for my seat"; Seat 6's split cell 1/2 is higher than unsplit 1/1 | correction; the winner is unchanged (Seat 3's 2 on V2 and V3) | — |
| M3-1 | map | V4 veto (S1 later 3) | faithful | 1-seat1 §4 V4: 3, "No phase ever tests…" | — | — |
| M3-1 | map / ordering | V1′ "vetoed as a reading" | consistent reading, not needed | without the 3, V1′'s highest cell is at least 2 (S1 now 2; S7 2/2 c), so it drops out at step 3 | SURVIVES WITH CORRECTIONS: record V1′ as excluded at step 3, with S1's 3 marked as an unconfirmed reading | — |
| M3-1 | debt | eight seats with later 1 | present | register rows match each seat's later reason; O10, O4, 08-3 and the AX38 (iv) records exist | — | Does item 15 default to "void" when the trigger fires at O4, so that Seat 7's 4 h holds? |
| M3-1 | ordering | sums; step 3 | correct as read | recomputed (sums above) | — | — |
| M3-1 | ordering | contingency "V2 would win on sum" | IMPRECISE | V2 (conditions met) 15 = gated 15, so reversibility decides | correction | — |
| M3-1 | D-L1, D-L2 | file 29 and file 32 values | CORRECT (code and builder measurements) | file 29 rows layout4_s0.7, S-A, both_wall; file 32 L17–19, L60, L74–76 | — | — |
| M3-1 | D-L3 | jnd 1 dB for G and C80 at 500–1000 Hz; about 14× | CORRECT | Vorländer §6.4, Table 6.1; 0.620/0.045 = 13.8 | — | — |
| M3-1 | D-L4 | I_spec = 0 at s = 1 | CORRECT | Kuttruff §8.8, Eq. 8.59 rearranged | — | — |
| M3-1 / M3-4 | D-L5 | r_c 3.57 m; diffuse D/R −10.8 / −18.5 / −15.0 dB | CORRECT (arithmetic) | Kuttruff §5.6, Eqs. 5.44–5.45; A consistent via Eq. 5.24 | — | — |
| M3-4 | claim | labels state diffuse D/R with no qualifier; line 12 says the labels "call the diffuse D/R values indicative, as the S-A precedent does" | IMPRECISE in the labels; line 12 INCONSISTENT but not load-bearing | Kuttruff §5.6: Eq. 5.43 and related equations "become questionable if ᾱ is not small"; ᾱ = 616/2200 = 0.28. Neither label, nor file 27's S-A text, says "indicative" | SURVIVES WITH CORRECTIONS: in both labels, write "(indicative: Kuttruff §5.6, Eqs. 5.44–5.45, A ≈ 640 m², ᾱ ≈ 0.28)" | — |
| M3-1 | D-L6 | ceiling image 23.6 ms after the direct sound; walls 20.8 m or more | CORRECT | coordinates in file 29; c = 343 m/s (Kuttruff §5.4) | — | — |
| M3-2 | D-L7 | union 0.049 / 0.098 / 0.196; 0.0113; 0.0438 | CORRECT | binomial sums redone | — | — |
| M3-2 | deferral | α deferred to round 2 | sound | K10 decides the outcome (24-trial split could win on sum). M3-1 does not depend on it: under unsplit plus C1 or the 24-trial split, S5 and S6 stay at most 1; 13/13 is out on Seat 6's later 2 | — | — |
| M3-2 | map | F1–F4 can each reverse AX47 (binaural F3 and F4 reversing an omni-derived bound) | not yet rated | 1-seat5 §7 hands this to Seats 1 and 4; no seat has rated it | round 2 (already asked) | — |
| M3-3 | map | S3 cell for HF-W, "its own proposal (≤ its best)" | TENSION MISREAD (invented cell) | 1-seat3 gives no number for HF-W; its best-rated option was 1/2, so "≤ its best" does not give 1 | the winner is unchanged unless Seat 3 rates its own proposal 2 | Seat 3: HF-W now and later? |
| M3-3 | map | S5 1/1 c | faithful (conservative) | 1-seat5 §6: every "any asserted form" condition is met (N1 inside the fade, unmodified stimulus passes, SHA-256, no RNG, red is a stop) | — | — |
| M3-3 | D-L8 | β 1.1378 = 0.561 dB; the bound | CORRECT (derived) | triangle inequality over a frame in which the weight changes by n_f/L; the same form as AX47's measurement sentence; the commutator [Hyp] is gated before any seal | — | — |
| M3-1 | PRD proxy | acceptance check: survivors not shown | PRD MISREAD (omission) | gated S-B\* and V3 as written survive (max 2) but are not shown against NFR-1, NFR-8 L112, FR-3D-5 L75 or L133 | decider re-answers | — |
| M3-1 | PRD proxy | contingent FOR MAISARA for V1-W | would be PRD MISREAD as written | L49 and L101 are "Accuracy vs CPU" and "CPU load and latency may be high"; L112 does not address evidence order; L55 makes hours unbounded, not ranked | — | Which PRD id separates V1-W from V2 and from gated S-B\*? |
| M3-1 | PRD proxy | "V2 strains NFR-8 L112" | IMPRECISE | NFR-8 states a rendering requirement; the timing of s < 1 evidence is Seat 3's later cost | correction (does not change the check) | — |
| M3-3 | PRD proxy | the line shows no options; FR-SIM-6 cited | PRD MISREAD (omission); FR-SIM-6 IMPRECISE | the four options are not shown; FR-SIM-6 is about "automated listener and source movement", while the step is an IR update | decider re-answers | — |
| M3-4 | claim | 0.874 dB | CORRECT | 10·log10(1.22290) | — | — |
| M3-4 | claim | S-B\* fallback "Seats 2, 3 and 9 can live with" s0.9 | IMPRECISE | only Seat 3 says it ("0.9 as can live with"); Seats 2 and 9 picked 0.7 and did not rate 0.9 (Seat 2's "Any S-B\*" conditions cover it) | correction | — |
| M3-7 | convening | render_cli provisional flag and AX49 exception; L4 sealed before the first scored trial, "decided now" | UNDERCONVENED for those items | M3-L4 asks Seat 5 to "rate both options and the flag", Seat 3 about provisional synthesis, and Seat 7 about "the pre-seal build on the critical path"; no round-1 seat rated these. AX49 is a plan default that changes only through a board DECISION | move those items to M3-L4 | — |
| M3-7 | map | "L4 same day as sitting 2, or the next day" | IMPRECISE | 1-seat1 §5(b): "Same day: yes" | correction or rating | — |
| M3-7 | D-L10 | `assembleProvisional` exists; no CLI flag | CORRECT (from the code) | `Engine.h` L293–298; `src/cli/` has no provisional-IR flag (the only hit is `kWMaxPerEmitterProvisional`, L1030) | — | — |
| M3-1 | D-L9 | 0.639 against 0.589 s; 0.578 against 0.787 s | CORRECT (arithmetic); the 46 dB SNR is Seat 9's [Hyp], already RQ-M3-4 | L_drop = 10·log10(1 + 10^(D/R/10)): 1.12 and 3.94 dB | — | — |
| M3-5, M3-6, M3-8 | claims and PRD | no V3 `/fix-plan`; MA01_01/02 by rule; widened trigger | SURVIVES | Seat 1's rule (§5 a); Seat 2's text plus Seat 4's clause | — | — |

## Outcomes

- **M3-1:** TENSION MISREAD, pending round 2 on Seat 7's now cell, plus PRD MISREAD by omission. Its corpus basis is CORRECT. It would survive with corrections (the Seat 6 cells and header, the V1′ step-3 note, the "tie, not V2" wording, the s0.9 attribution) if both hold:
  - round 2 returns Seat 7 at 1 now and confirms the read cells, including Seat 4's narrowed (b);
  - the acceptance check shows gated S-B\* and V3 as written.
- **M3-2:** the α deferral is sound. The family declaration waits on round 2. The numbers are CORRECT.
- **M3-3:** TENSION MISREAD on Seat 3's cell (the winner is unchanged unless Seat 3 rates HF-W at 2), plus PRD MISREAD by omission. β is CORRECT.
- **M3-4:** SURVIVES WITH CORRECTIONS: the "indicative" qualifier and Eqs. 5.44–5.45 in both labels. Item 15's (i) wording waits on Seat 4 in round 2.
- **M3-5, M3-6, M3-8:** SURVIVE.
- **M3-7:**
  - Sitting order, and deferring the design to M3-L4: SURVIVE.
  - The render-path flag, the AX49 exception and the "L4 sealed before the first trial" requirement: UNDERCONVENED (Seats 3, 5 and 7, as M3-L4 itself asks).
  - "Same or next day": IMPRECISE against Seat 1.

**Can the decided parts stand without round 2?** Partly:
- M3-1's choice does not depend on α.
- It does depend on round 2 for Seat 7's now cell and for the read cells. The decider already treats those as reversal conditions.
- M3-3, M3-4's labels and item 13, M3-5, M3-6 and M3-8 do not depend on α or L4.
- M3-7's render path and pre-seal requirement cannot be decided before M3-L4 rates them.

## Questions for the decider's rebuttal round

1. Seat 7 gives its V1 now 2 for hours that V1-W keeps. Does Seat 7's round-2 answer put V1-W's now cell at 1 or at 2? If 2, which PRD id, read verbatim, separates V1-W from V2 (conditions met) and from gated S-B\*, which tie at sum 15? L49 and L101 rank accuracy against CPU and latency, not against listening hours.
2. Show gated S-B\* and V3 as written against M3-1's check ids, and M3-3's four options against its ids. Is FR-SIM-6 (movement) the right id for an IR-update step?
3. What is Seat 3's own now and later rating of HF-W?
4. Why are the render_cli flag, the AX49 exception and "L4 sealed before the first scored trial" decided now, when M3-L4 asks Seats 5, 3 and 7 to rate exactly those?
5. Does Seat 4 accept item 15's narrowing of (b) to non-detections while F3 can reverse AX47? If not, its V1-W later cell is 2, as on V2 ("a head at a wall … read as binaural evidence").

Files: /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md; /home/user/makroof/docs/review/phase-07c-2b/1-seat1.md … 1-seat9.md; /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md, 31-decider-abx-r4.md, 32-k5-k6-clicks-session.md, 40-decider-2a-2b-final.md, 41-interrogator-on-file40.md; /home/user/makroof/docs/PRD.md; /home/user/makroof/docs/BUILD_PLAN.md (L144, L170, L172); /home/user/makroof/docs/phases/phase-07c-2b.md; /home/user/makroof/src/sim/Engine.h; /home/user/makroof/src/cli/Cli.cpp; corpus /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (§5.4 Eq. 5.24, c = 343 m/s; §5.6 Eqs. 5.42–5.45; §8.8 Eq. 8.59) and /home/user/makroof/docs/corpus/vorlaender-auralization.md (§6.4, Table 6.1).
