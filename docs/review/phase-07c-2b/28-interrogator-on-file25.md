# Interrogator on decider file 25 (I7, rulings (i) and (ii))

I7 fails: its arithmetic counts the 85 ms lead-in twice, so the shift in the speech onsets is bigger than the decider says, and Seat 1 should be convened. Rulings (i) and (ii) survive.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:**
- `docs/review/phase-07c-2b/25-decider-item7.md`;
- builder file 12 (`12-builder-kit-e.md`);
- `tools/ci/abx_kit.py`, `speech_layout` (L1038–1059) and `build_speech_chain` (L1094–1147);
- phase-07c-2 file 13, items 7 and 8;
- BUILD_PLAN AX21 (L144).

## Rulings
| id | ruling |
|---|---|
| **I7** | **FAILS**: I7-L3 is WRONG, and the decision is UNDERCONVENED (Seat 1). The reading of item 7 and the option exclusions are sound. |
| **(i)** heard-T30 label per scene class | **SURVIVES** |
| **(ii)** M3-S's E line is authoritative | **SURVIVES** |

### I7-L3 is WRONG: the lead-in is counted twice
The decider takes end of speech to be 2.345 s after the TSP file start, so it adds the lead: 0.085 + 2.345 = 2.430 s in stimulus time. But 2.345 s already includes the lead.

- **From the code:**
  - `speech_layout` sets `eos = lead + end_of_speech` (L1053), with `lead = LEAD_BLOCKS * PARTITION` = 4096 samples (L1046).
  - `build_speech_chain` logs `end of speech {eos / FS}` (L1144).
  - So the 2.345 s that builder file 12 reports is the stimulus-time value.
- **From the builder's own figures:**
  - The window's lower bound is (2.496 − 2.345)/2.560 = 0.059, matching file 12's "[0.059, 0.380]".
  - The decider's 2.430 s would give 0.026, which does not match.

**Corrected numbers:**
- **Onset floor:** 0.085 + 2.600 = 2.685 s. The decider has this right.
- **First boundary at or after the floor:** boundaries are 512 samples (10.67 ms) apart, and the earliest is 2.496 s (= 234 × 512 samples). The first one at or after 2.685 s is 2.688 s.
- **New window lower bound:** (2.688 − 2.345)/2.560 = **0.134·T_heard**, not "≈ 0.10". The window becomes about **[0.134, 0.380]·T_heard**.
- **Boundaries removed:** those from 2.496 s up to 2.677 s, which is **18 boundaries**, not about 10.
- **Passing boundaries left:** the 78 passing boundaries were contiguous from the first (file 12), so about **78 − 18 = 60** remain, not about 68.
- **Still above the assertion:** 60 is above the asserted minimum of 34.
- **S-A:** 2.475 − 0.085 = 2.390 s ≥ T 2.009 s, as the decider says. CORRECT.

The wrong figures also appear in four places that need correcting:
- the brief for Seat 1 ("about [0.10, 0.38]");
- the Seat 1 debt row ("about 0.06–0.10·T_heard");
- the strongest objection ("about 68");
- the expected values written for the run sheet.

### Convening: not re-convening Seat 1 is not sound (UNDERCONVENED)
The decider relies on the D1 precedent, where file 18 accepted an AX47 item carried over unchanged. That precedent does not fit here.

- **The two rules interact.** Item 7 and Q5 are both Seat 1's pre-registered rules, and each is unchanged. But applied together they produce a new distribution of speech onsets that no seat has rated:
  - the earliest **23 %** of the passing boundaries (18 of 78) are dropped;
  - the earliest onset moves from 0.151 s to 0.343 s after end of speech.
- **The tail at the onset gets quieter.** E's tail decays at about 60/2.6 ≈ 23 dB/s. Over the extra 0.19 s that is roughly **4.4 dB** less tail level at the earliest onset. This is an approximation: it treats the decay after end of speech as exponential at the tail's T30. That is the direction Seat 1's own sensitivity reasoning cares about.
- **This is Seat 1's ground.** Its row covers the blind-test signal, the paradigm, and the hardest signal; the onset distribution of the speech chain sits under all three.
- **The decider's own record agrees:**
  - it writes a debt row in Seat 1's name for a cost Seat 1 has not stated;
  - it gives "confidence: medium (Seat 1 has not rated this)";
  - option (3) remains in bounds and is ranked against (1) without any rating.
- **The fix is already drafted.** Convene Seat 1 with the decider's own brief, carrying the corrected numbers: window about [0.134, 0.380]·T_heard, about 60 passing boundaries, earliest onset about 0.34 s after end of speech. Ask it to rate (1) against (3), now and later.

### What stands in I7
- **Reading of item 7: CORRECT.** "Programme" counts from the first programme sample, and the lead-in is excluded. File 13 item 7 says "at least one T30 of programme before the step". Silence is not programme, and the noise chain already counts this way.
- **(2) is excluded correctly.** File 13 item 8 fixes "Two Harvard sentences"; joining two files into sentence 1 would make three.
- **(4) is excluded correctly.** Counting or lengthening the lead-in would count silence as programme, which loosens item 7.
- **(3) is correctly left in bounds.** Ranking it against (1) is the question for Seat 1.
- **Kit assertions are coherent:** item 7 on the first boundary and on every drawn onset, a non-empty set, and at least 34 passing boundaries.

### (i) and (ii)
- **(i): sound.** File 8 itself held both "the heard-T30 label stays" (M3-G) and M3-S's E wording "ISO fit spanning the early part, not a decay rate", so the two were in tension. Reading M3-G as "the label stays alongside T, worded per scene class" resolves that inside surviving decisions:
  - s = 1 scenes keep Seat 9's "AX21 gap" text;
  - s < 1 scenes (E, and fallbacks D and B) use the early-part text, since E's early part is −8.6 dB re direct (file 4).
  - Pinning both texts in `test_preregistered_numbers` is consistent.
- **(ii): consistent.**
  - It matches D-M3g as corrected in files 11 and 13: Maisara's decision appears only as reported speech, without quote marks, outside the label.
  - The context sentence ("the plan's AX21 row defers the fix to the B11 promotion rule") matches BUILD_PLAN L144.
  - The run sheet currently has that sentence inside E's early-part detail line, and (ii) moves it out correctly.
  - Documenting `--scene-name` follows builder file 12.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| I7 | claim I7-L3 | eos at 2.430 s; window floor ≈ 0.10·T_heard | WRONG: eos is 2.345 s stimulus time (lead included); floor ≈ 0.134·T_heard | abx_kit L1046, L1053, L1144; (2.496 − 2.345)/2.560 = 0.059 matches file 12 | FAILS | recompute; window ≈ [0.134, 0.380] |
| I7 | claim | about 10 boundaries removed, about 68 left | WRONG: 18 removed (2.496 to 2.677 s), about 60 left (still ≥ 34) | 512-sample spacing; file 12 Q5 row | FAILS | — |
| I7 | claim I7-L2 | earliest boundary 2.496 s; 78 contiguous passing; S-A 2.475 s | CORRECT | builder file 12 | — | — |
| I7 | convening | Seat 1 not re-convened | UNDERCONVENED (Seat 1: speech onset distribution, about 23 % of passing onsets dropped, tail about 4.4 dB lower at the earliest onset) | README Seat 1 row; file 25's own debt row and confidence | waits | convene Seat 1 with the corrected brief |
| I7 | inference | reading of item 7 (programme from the first programme sample) | CORRECT | file 13 item 7 | — | — |
| I7 | bounds | (2) out (item 8); (4) out (loosens item 7); (3) in bounds | correct | file 13 items 7, 8 | — | — |
| I7 | debt | Seat 1 row "0.06–0.10·T_heard" | INCONSISTENT with the corrected arithmetic; also written for a seat that has not rated | — | fix | — |
| (i) | consistency | heard-T30 label per scene class; M3-G sentence clarified | sound | file 8 M3-G and M3-S; file 4 early part −8.6 dB | SURVIVES | — |
| (ii) | consistency | E line authoritative; AX21 decision as reported speech outside the label | faithful | D-M3g; files 11, 13; BUILD_PLAN L144 | SURVIVES | — |
