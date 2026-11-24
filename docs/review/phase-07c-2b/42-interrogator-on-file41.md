# Interrogator on decider files 38 ((5) the third sitting) and 41 (L4-A = A-ii; readings of assertions 7, 4 and 2)

**Verdict: everything survives.** (5), L4-A (A-ii) and the readings of assertions 4 and 7 stand as written. The assertion-2 null definition needs one wording correction, and the debt-row arithmetic should use the measured mixing time; neither changes a conclusion.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**What I read:** files 38 and 41, the seat answers 40-seat1/2/3/5/7, builder file 15 (measured timing), `docs/phases/phase-06.md` L60–65, and Vorländer Eq. 6.4. Builder file 26 I took only through the seats' and decider's citations.

## Rulings
| item | ruling |
|---|---|
| **(5) third dated sitting** (file 38) | **SURVIVES** |
| **L4-A = A-ii** (file 41) | **SURVIVES** |
| **Assertion 7 reading** | **SURVIVES WITH CORRECTIONS** (the arithmetic input) |
| **Assertion 4 reading** | **SURVIVES** |
| **Assertion 2 reading** | **SURVIVES WITH CORRECTIONS** (attribution of the null) |

## (5) The third sitting
- It applies L4-T and file 21's worst-case rule directly.
- E's second sitting (about 74 min) plus L4's primary and rerun blocks (74 min) comes to 148 min, which is over the 2 h limit.
- L4 alone is 74 min at a typical pace and 113.6 min at a slow one, both within 120 min. Seat 7 confirms this ("about 6 min is left").
- Since it only applies an existing rule, it needs no new convening.

## Anchor map and tie-break
**Map: faithful.** Every cell matches the seats' answers:
- **A-ii:** S1 0/0, S3 0/0, S7 0/0.
- **A-i:** the same.
- **A-iii:** 1/1 for Seats 1, 2, 3, 5 and 7, sum 10.
- **A-iv:** S1 1/1, S3 2/1, S7 2/1.
- **A-v:** S1 2/1, S3 2/1, S7 1/1.
- Seat 2 was convened for A-iii only, and Seat 5 answered "NOT MY MATTER" for the other options. Both score 0/0 outside A-iii, which is correct.

**Tie-break: sound.**
- A-i and A-ii tie on the maximum (0), on the sum (0) and on reversibility. That exhausts decider §5's steps.
- The seats' own rankings are part of their reports. Seat 1 prefers A-ii and "can live with" A-i; Seat 3 ranks A-ii "prefer" and A-i "prefer, nearly as good".
- Using those rankings is not a re-rating, and the decider states the residual objection openly.
- A-i is equally valid, and either choice leaves the anchor's purpose and its chance rate unchanged.

**Chance rate: CORRECT.**
- Passing by guessing needs 5 or 6 of 6 correct: P(≥ 5/6 | ½) = (6 + 1)/64 = 7/64 = 0.109.
- Seat 1 confirms that with X drawn at random, a bias toward one label cannot raise a guesser's score, whatever the role assignment.

**Kit and plan text: faithful.**
- **A-L1:** 10·log10(0.828) = −0.82 dB. CORRECT.
- Seat 3's conditions for A-i/A-ii are all adopted: M1's step identity within 0.05 dB, s_w ≤ 2.3 %, and peak ≤ −3 dBFS on the +3 dB anchor IR.
- Seat 1's conditions are met:
  - the labelled anchor pair is in familiarisation;
  - the seeded positions and X draws are unchanged;
  - the change from "3 up, 3 down" to "+3 dB, roles 3/3" is recorded with its reasoning;
  - AX49 and item 2 are not amended.
- The exact run-sheet text is consistent with all of this.
- Its sentence "never cited as evidence about M1's step" comes from Seat 2's A-iii concern. It is harmless here.

## Assertion 7: correction to A-L3
- Seat 3's correction stands: assertion 8 bounds the energy past L_f counted from emission (K17′, Vorländer §6.4.1 Eq. 6.4). It does not prove a realised drop of at least 18.7 dB measured from t_mix.
- **IMPRECISE input.** A-L3 adds 0.49 dB = 60 × 0.0647/8. That 0.0647 s is K27's lower bound on t_mix,e,max, not the measured value.
- Builder file 15 measured t_mix,e,max = 0.08017 s at T60_max = 7.9955 s. That gives 60 × 0.08017/7.9955 = 0.60 dB.
- **Corrected figures:**
  - model: 10^(−(18.72 + 0.60)/10) = 0.0117;
  - realisation: 10^(−(18.47 + 0.60)/10) = 0.0124. This reproduces the measured 0.0124 exactly.
- Both stay ≤ 0.0134, so the conclusion and the reading are unchanged.
- **Correction:** restate A-L3, and the debt row, with the measured t_mix,e,max.
- **Debt row:**
  - The scatter estimate is about 0.4 dB [Inferred]: a 63 Hz octave is about 44 Hz wide, the window is about 2.5 s, giving a bandwidth–time product near 110 and a spread of 1/√110 ≈ 10 % in energy.
  - It is flagged and properly scoped, with a 16-seed ensemble to settle it before 07d's round.
  - The non-detection wording quotes the realised cut, 21.7 dB.
  - Faithful.

## Assertion 4: faithful
- The 0.05 dB tolerance is unchanged.
- The check is recorded as "weak on this scene". Its red test (a provisional 1.2 dB too hot) still fails it.
- Seat 3 rates the reading 0/0.

## Assertion 2: correction to the null's attribution
- The IR is bit-identical up to tap 3007. On the renders, bit-identity holds up to the partition boundary at 6656, and above that a null is asserted. This is Seat 3's definition, adopted faithfully.
- **IMPRECISE attribution.** The null is defined as "max |A − B| ≤ −120 dB re B's peak, per sample", and called "the Phase 06 criterion". It is not. phase-06 L60–61 defines −120 dB as a residual-to-signal **energy** ratio.
- **Correction:** call it "Seat 3's per-sample criterion at Phase 06's −120 dB level", or assert both forms.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| (5) | ordering | third dated sitting (148 > 120 min; L4 alone 74 / 113.6 min) | correct (applies L4-T and file 21) | file 38; 40-seat7 | SURVIVES | — |
| L4-A | map | A-i…A-v cells; NMM cells at 0/0 | faithful | 40-seat1/2/3/5/7 | — | — |
| L4-A | ordering | A-i vs A-ii tie broken on the seats' stated preference | sound; A-i equally valid | 40-seat1 §2; 40-seat3 §2 | SURVIVES | — |
| L4-A | claim A-L2 | P(≥ 5/6) = 7/64 = 0.109 under random X | CORRECT | binomial | — | — |
| L4-A | claim A-L1 | −3 dB refused; deepest step −0.82 dB | CORRECT | 10·log10(0.828) | — | — |
| L4-A | conditions | Seat 3 (M1 ≤ 0.05 dB, s_w, peak); Seat 1 (familiarisation, seeds, recorded change) | adopted | 40-seat1 §6; 40-seat3 §6 | — | — |
| (2) | claim A-L3 | 0.49 dB from K27's t_mix bound | IMPRECISE: measured t_mix,e,max 0.08017 s gives 0.60 dB, model 0.0117, realisation 0.0124 (= measured); still ≤ 0.0134 | builder file 15; Vorländer Eq. 6.4 | SWC | restate with the measured value |
| (2) | reading | assertion 8 measures K17′ from emission, not the drop from t_mix | CORRECT (Seat 3's correction) | AX49 K17′ | — | — |
| (2) | debt | realised 63 Hz drop 18.47 dB; scatter about 0.4 dB [Inf]; 16-seed ensemble before 07d | faithful | 40-seat3 | — | — |
| (3) | reading | assertion 4 kept, recorded as weak; red test bites | faithful | 40-seat3 | SURVIVES | — |
| (4) | reading | null "per sample re B's peak" called "the Phase 06 criterion" | IMPRECISE: Phase 06's −120 dB is an energy ratio | phase-06 L60–61 | SWC | reword the attribution |
