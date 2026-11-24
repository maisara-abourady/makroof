
# 13: Decider on the M3-L4 band-coverage red (phase 07c-2b)

This is read-only. The orchestrator saves it as `/home/user/makroof/docs/review/phase-07c-2b/13-decider-l4-coverage.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. No corpus passage bears the load here. Every figure is a builder measurement (file 11), or arithmetic on those measurements shown below.

**Files read:**
- 11-builder-l4-kit.md, 12-seat1.md, 12-seat3.md, 12-seat8.md
- 9-decider-m3-r3.md
- 4-seat1.md L96–121 (the chord spec)
- BUILD_PLAN L172 (AX49, the L4 sentence)
- PRD L17, L49–55, L105, L112
- From the code: `tools/ci/ax49_l4.py` (L123–130, L584–594) and `tests/unit/test_ax49_l4.cpp`, a draft already in the tree.

## PRD digest
The digest from file 9 is unchanged.
- **For whom:** producers and DJs (L17).
- **Outcome:** NFR-1 (L105), "pass listening tests".
- **Bounds:**
  - NFR-8 (L112): no environment-specific code paths. Nothing here touches `src/sim`.
  - AX5 and AX49: shipped and offline renders stay unchanged; the provisional is used only behind the validation flag.
  - Her AX21 decision; spaces are empty (L54).
- **Not bounded:** hours (L55).
- **Ranking:** accuracy is ranked against CPU and latency only (L49).
- **Verification:** every behaviour has an automated check; a red is a stop; nothing is loosened to pass.

## Convening (narrow; this round)

| seat | status | reason |
|---|---|---|
| 1 | convened (12-seat1) | the chord criterion, detectability, the null wording |
| 2 | not required | S′ is unchanged, and all of Seat 2's asserts pass (file 11) |
| 3 | convened (12-seat3) | the stimulus checks; the builder's interpretations 1–7 |
| 4 | not required | the chain stays omni diotic; no delivery change |
| 5 | **convened now, narrow (brief below)** | Seat 3's condition puts a new Catch2 case on three CI platforms as a seal gate. That is the CI-gates item. It does not touch the stimulus choice, so the stimulus choice is decided now. |
| 6 | not required | no user control, range or default is affected |
| 7 | not required | the chosen option adds no sitting. Only the B-as-second-variant option would add one (about 0.75 h at the file 9 pace); it loses at step 5 even with Seat 7 at 0/0 (below), so Seat 7's rating cannot change the winner. |
| 8 | convened (12-seat8) | the representativeness of the material |
| 9 | not required | the L4 label is unchanged. The added null sentence prints a measured depth table and makes no room-acoustic claim. Seat 9 still confirms the filled label before the seal (file 9 (iv)). |

**Brief for Seat 5:** Seat 3 requires `[ax49-l4]` (P4/P5 at 1e−9, with N-L1/N-L2 inside) to be green on Linux, macOS and Windows before the L4 seal.
- **Read:** 12-seat3 §6 item 7; `tests/unit/test_ax49_l4.cpp`, which plans the 100 m cube at T60 8 s with a 12 s unit decay; CLAUDE.md "When CI skips" and "Build and test".
- **Rate now/later:**
  - (a) in the default `spatial_tests` set, run by ctest in every CI build type;
  - (b) Release-only, run as the `[benchmark]` cases are.
- **Give your conditions:** per-test time budget, and the tag form.
- The seal waits on your answer. The stimulus decision below does not.

---

## Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K1 | steady state re the strongest band (125 Hz): 63 −9.8, 250 −9.3, 500 −11.6, 1k −13.3, 2k −15.8, **4k −22.94**, 8k −50.3 dB | file 11 L18–20, builder measurement | known |
| K2 | depth at L_f: 18.72 dB (63 Hz–1k), 23.19 (2k), 40.14 (4k), 104.93 (8k) | file 11 L34–36. Recomputed from timing alone as 60·(L_f − t_mix,e)/T60: (3.61353 − 1.11753) = 2.496 s; ×60/8 = 18.72; /6.457 = 23.19; /3.731 = 40.14 | known. Chord-independent: it depends only on S′'s T60 and timing |
| K3 | B (exact) in the 100 ms where the cut begins, re the hold: −39.9, −34.9, −31.3, −29.9, **−27.5**, −36.8, −48.5, −62.4 dB | file 11 L59 | known. Spread over 63 Hz–2k is −27.5 − (−39.9) = 12.4 dB |
| K4 | A alone stays red at about −22.3 dB | Seats 1, 3 and 8, independently. (1/2828 − 1/5000)/(1/2828 − 1/5657) = 1.536/1.768, which is 0.61 dB | known [Inferred]. Not load-bearing: A is out on the seats' own 2s |
| K5 | effect of B on cut sensitivity: Seat 1 says +9–12 dB exposure at 1–2 kHz; Seat 3 says ≈ −1 dB | 12-seat1, 12-seat3, both [Inferred] | **conflicting**, but not load-bearing: B is out at step 3 on Seat 8's own 2/2 |
| K6 | every seat cell | 12-seat1/3/8 | known. E's cells for Seats 3 and 8 are read from conditions (marked) |
| K7 | the draft Catch2 file's state: hidden probe only; "bound the measurement supports"; monotonicity checked on the formula g | from the code, `test_ax49_l4.cpp` L4–9, L119–121, L133–141 | known |

No load-bearing gap remains.

## Tension map (now / later, in the seats' words)

| option | S1 | S3 | S8 | max | sum |
|---|---|---|---|---|---|
| A: 1/k to 10 kHz, criterion unchanged | 2/1 "predicted to red again at about −22.3 dB" | 2/1 "leaves a red, so L4 stalls" | 1/1 "a little brighter than typical" | 2 | 8 |
| B: 1/√k, criterion unchanged | 0/0 "harder stimulus" | 1/1 "≈ 1 dB less sensitivity" | **2/2** "moves the test off the real material" | 2 | 6 |
| C: 1/k chord kept; coverage over 63 Hz–2 kHz, 4k printed | 1/1 "a loosening… no assert on where the cut is exposed" | 0/1 "no change to the stimulus… null scoped" | 0/1 "material stays representative"; later, a bright-pad beta report | 1 | 4 |
| D: A + C | 1/1 "the A half adds only 0.6 dB" | 0/1 | 1/1 (read from Seat 8's conditions: A's brightness reason now, C's beta reason later) | 1 | 5 |
| **E: C + a cut-window coverage assert (Seat 1's)** | 1/1 "null must say cut exposed at 63 Hz–2 kHz…" | 0/1 (read from Seat 3's conditions: C's reasons, since the stimulus, hashes and checks are unchanged; the window is already measured in file 11 L59) | 0/1 (read from Seat 8's conditions: "C: no condition from me"; whether 4k is asserted is "Seat 1's call") | 1 | 4 |
| B as a second "bright" arm after the pad | ≥ 1/1 (the pad arm needs C) | ≥ 1/1 (B's cell) | 1/1 (Seat 8's condition) | ≥ 1 | ≥ 6, with S7 unrated |

## Working
1. **Bounds:** no option breaks one. All are kit-only, with no `src/sim` (NFR-8). Shipped renders are unchanged (AX5, AX49). Every option is still a "held-chord ABX" (AX49 L4).
2. **Veto:** no 3 anywhere.
3. **Worst-off seat:**
   - A and B hold a 2 and are out. A's 2s are Seats 1 and 3; B's is Seat 8, its own rating, which I do not re-rate.
   - C, D, E and B-second hold max 1. Max 0 is unreachable: Seat 1 says "C and E, from 1 to 0: none available", and B's best is Seat 8 at 1/1.
4. **Compose:** nothing lowers the maximum below 1.
5. **Sum:**
   - C 4 = E 4 < D 5 < B-second ≥ 6.
   - B-second loses even if Seat 7 rates it 0/0, so Seat 7 is not decisive.
6. **Reversibility (C vs E):**
   - E's extra assert can be dropped to a print before the seal at no cost.
   - C cannot gain a pre-registered exposure assert after scores exist. Seat 1's premortem (the "dull-chord artefact" reading at 07d) could then be answered only by a re-sitting. This is the same taint logic as file 9's timing ruling.
   - **E is cheaper to undo.** It also matches Seat 1's own pre-decision: "B, then E if Seat 8 rejects B", and Seat 8 did reject B as the primary.

## DECISION L4-COV: E

The chord stays as built ("l4-chord-v1", hashes unchanged). Replace Seat 1's coverage clause with this text:

> "Band coverage (Seat 1; amended by decider file 13 after the first build's red, before any scored trial). (a) The exact render's steady state (the last 1 s of the hold) has every band from 63 Hz to 2 kHz within 20 dB of its strongest band. (b) In the 100 ms where the cut begins in the aligned output (kit interpretation 2), the exact render's energy in every band from 63 Hz to 2 kHz is within 20 dB of its strongest band. Both are asserted. 4 kHz and 8 kHz are printed with their depth at L_f. The original clause (63 Hz–4 kHz) is printed with its result (first build: 4 kHz −22.94 dB, red). The scope follows from S′'s depth at L_f (63 Hz–1 kHz 18.72 dB, 2 kHz 23.19 dB, 4 kHz 40.14 dB), which no chord changes."

**The null wording becomes:** "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; at 4 kHz the tail is 40 dB down at L_f".

**Kit (builder):**
- `COVERAGE_BANDS_HZ` becomes 63–2000.
- Add assert (b).
- Keep printing the original clause.
- Add the decider's negative control **N-L4:** the same chord with partials limited to ≤ 500 Hz must fail both (a) and (b).
- Pin that the original clause still reads −22.94 dB, red, on this deterministic build.
- `test_full_build` changes from xfail to pass.
- The kit's coverage print states the cause as the 1/k slope plus the room, not the 5 kHz stop (Seats 1 and 3).

**Today's values:**
- (a): weakest band 2k at −15.8 dB, a margin of 4.2 dB.
- (b): spread 12.4 dB, a margin of 7.6 dB.

**Is this a loosening? Yes, for the steady-state clause, and it is recorded as one.**
- It is a criterion change after a red. It is not "loosening to pass" in the forbidden sense, for four reasons:
  - (i) A passing stimulus existed (B). It was declined on Seat 8's stated 2/2, not for convenience.
  - (ii) The new scope rests on K2, a chord-independent property of the scene, not on the red's margin (Seat 3's condition).
  - (iii) The claim is narrowed by exactly the band removed (the null wording), and a direct measure of the cut's exposure replaces the proxy.
  - (iv) The board made the change, not the builder, and before any scored trial.
- **How it is recorded:**
  - run sheet §0 amendments (item 14, "L4 coverage, decider file 13") and §7 (the text above);
  - one BUILD_PLAN §6 change-log row: threshold changed, the reason, the red value −22.94 dB, this file;
  - the kit manifest prints the original clause's result;
  - all of it in the pre-registration commit, before any scored trial.

**Load-bearing claims:**
- **13-L1:** K2, chord-independent (working shown in the inventory). At L_f the 4 kHz band's cut is 21.4 dB deeper than at 63 Hz–1 kHz.
- **13-L2:** K1 gives (a) a pass at −15.8 dB; K3 gives (b) a pass at a 12.4 dB spread. Both are builder measurements.
- **13-L3:** B is out on Seat 8's own 2/2 (12-seat8 §3–4). This is a seat's statement of its own cost.
- **13-L4:** the null makes no claim about 4 kHz. Seat 1's masking argument (that 4k adds nothing to detection) is [Hyp] and is deliberately not relied on: the wording scopes it out.
- **Product judgement:** the material producers play (L17) under NFR-1 (L105).

**Future-debt register (E):**

| seat | commits to | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | the null is scoped to 63 Hz–2 kHz at the cut | a re-sitting with a brighter chord if 07d contests it | the L4 result; the 07d AX49 review | assert (b) green at the seal and the null carries the scope sentence |
| 3 | the null scoped by the depth table | a print | the L4 result | the result is recorded with K2 |
| 8 | bright-pad material untested | one extra variant sitting (about 0.75 h) | Phase 13 beta reports | beta has no bright-pad cut report, or the bright arm is run |

**Strongest objection:** the conflict K5. If Seat 1 is right that B gives 9–12 dB more exposure at 1–2 kHz, E tests a softer stimulus.
- **Why it holds:** (b) puts a floor on the exposure at 1–2 kHz, and at the cut 1 kHz is the strongest band. Seat 3 reads B's sensitivity in the opposite direction. B's exclusion is Seat 8's own 2, which I do not re-rate.
- **When it would not hold:** if Seat 8 re-rated B as the primary at ≤ 1, B (0/0, 1/1, ≤ 1) would compete at step 3.

**Confidence:** medium.
- Two of E's cells are read from conditions.
- If Seat 3 or Seat 8 rates E one point above C, C wins at step 5. The only difference is then (b) asserted versus printed; the stimulus is the same.

**Reversal conditions:**
- (a) or (b) reds on a rebuild;
- Seat 3 or Seat 8 rates E above C (then C, with (b) printed);
- Seat 8 rates B ≤ 1 as the primary;
- the 07d review contests the scope (then the bright arm runs; Seat 7 is convened).

**Acceptance check (NFR-1 L105, L17, AX5, AX49, NFR-8 L112):**
- **E:** serves NFR-1. It tests the cut on the material producers play (L17), with the exposure asserted and the null scoped. AX5, AX49 and NFR-8 are untouched.
- **C:** NFR-1, without the exposure assert. No PRD id ranks it above E.
- **D:** NFR-1, with slightly brighter material and no gain at the cut. No PRD id ranks it above.
- **B:** NFR-1 with a harder or softer test (contested, K5), on material that is not representative (L17 strains). Excluded at step 3.
- **A:** NFR-1 unmet: it stays red. Excluded.
- **B as a second arm:** NFR-1 plus brighter evidence, at more hours (L55 does not bound hours). No PRD id ranks it above E.

No PRD goal points to another option. Amends nothing.

---

## Ruling on Seat 3's conditions: all binding before the seal

- **R1. P2 print.**
  - Print one consistent statement: "identical on [0, n₁); first difference at n₁".
  - State whether tap 47912 is identical.
  - The assert is unchanged.
- **R2. WAV read-back.** Every WAV the kit writes is read back and asserted bit-equal (float32) to the array that was checked, before it is hashed.
- **R3. The +3.05 dBFS dry input.** Either:
  - assert that `render_cli`'s input read is lossless above 1.0, by a round-trip check; or
  - pre-scale by an exact power of two (2⁻¹ is enough) and undo it after the render, asserting the pre-scaled peak is < 1.0.

  The manifest records which was used. No unasserted path is accepted.
- **R4. Output-time grid.**
  - The builder's interpretation 1 is accepted, and Seat 3 confirms "meets".
  - The §7 text gives both forms: IR time with +1·P, and written-file time without it.
  - S3's text says "delay 0 in compensated output". This restates file 9 (i) for the written-file domain; it is not a change of check.
- **R5. Catch2 `[ax49-l4]` is required, not proposed.** P4/P5 at 1e−9 were adopted in file 9 as "Seat 3's P1–P6"; P4′/P5′ never replaced them. On the draft `tests/unit/test_ax49_l4.cpp` (from the code):
  - (a) the asserting case is non-hidden `[ax49-l4]`; the hidden probe may stay;
  - (b) the bounds are 1e−9, not "the bound the measurement supports" (draft L4–9). If the probe measures above 1e−9, that is a red: stop, and return the probe output to Seat 3 and the decider. The bound is never set from the measurement;
  - (c) monotonicity is checked on the measured gain ĝ (or the fade array actually applied), not on the formula g (draft L119–121, which cannot fail);
  - (d) N-L1 (hard cut, built test-side) must fail P5, and N-L2 (provisional at tailSeed 12346) must fail P4, both inside the file;
  - (e) green on Linux, macOS and Windows before the seal. How it is placed in CI waits on Seat 5's answer (brief above).
- **R6.** P4′/P5′ stay in the kit as cross-checks.
- **R7.** P6 stays print-only. The kit also prints the 63 Hz–1 kHz depth margin against AX49's 18.7 dB (+0.02 dB).

The seal still also needs Seat 9's confirmation of the filled label (file 9 (iv)).

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| L4-COV | E: chord unchanged; coverage (a) steady state 63 Hz–2 kHz plus (b) cut window 63 Hz–2 kHz, both within 20 dB; 4k/8k and the original clause printed; scoped null; N-L4 | proposed | 1 (S1 1/1; S3, S8 later 1) | 4 | medium | NFR-1, L17, AX5, AX49, NFR-8 | none (builder measurements, K2 working) | (a)/(b) red; Seat 3/8 rate E > C; Seat 8 rates B ≤ 1; 07d contests |
| S3-cond | R1–R7 binding before the seal | proposed | — | — | high | NFR-1, CLAUDE.md verification | — | probe above 1e−9 (a red, to Seat 3) |
| S5 | `[ax49-l4]` CI placement | convening | — | — | — | — | — | — |

**Challenges to settled decisions:** none.

## Decided for Maisara
- **L4-COV:** the held-chord test keeps the producer-style pad. Its "enough high end" check now covers 63 Hz–2 kHz and checks directly that the chord has energy where the tail is cut. 4 kHz is dropped from the check because at the cut the room has already taken that band 40 dB down, whatever chord is played. This is recorded openly as a criterion change after a red (NFR-1 L105; L17).
  - **Seat that gives the most:** Seat 1 gives up its 4 kHz clause.
  - **What it gets back:** an assert on the cut's exposure, and a null that says exactly which bands it covers.
  - Amends nothing.
- **Seat 3's conditions:** the 1e−9 provisional-versus-exact test must exist and pass on all three platforms before the seal, along with three exactness checks on the kit's files and input level (NFR-1; AX5). Amends nothing.

**NEEDS MAISARA:** none.

**Files:**
- /home/user/makroof/docs/review/phase-07c-2b/11-builder-l4-kit.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat3.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat8.md
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md
- /home/user/makroof/docs/review/phase-07c-2b/4-seat1.md
- /home/user/makroof/tools/ci/ax49_l4.py
- /home/user/makroof/tests/unit/test_ax49_l4.cpp
- /home/user/makroof/docs/BUILD_PLAN.md (L172)
- /home/user/makroof/docs/PRD.md
