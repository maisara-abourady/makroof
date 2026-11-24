# 30: Decider on item 7, round 2 (corrected numbers; Seat 1 has rated)

To be saved as `docs/review/phase-07c-2b/30-decider-item7-r2.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome: I7 is decided again as option (1), with Seat 1's conditions 1–4.**
- The speech signal is unchanged.
- Onsets in E's speech chain are restricted to those with at least T of programme before them, counted from the first programme sample, with the lead-in excluded.
- The realised Q5 window becomes about [0.134, 0.380]·T_heard, with about 60 passing boundaries.
- Rulings (i) and (ii) stand (file 28).
- NEEDS MAISARA: none.

## Answers to file 28
- **I7-L3 (WRONG): corrected.**
  - End of speech is 2.345 s in stimulus time; the lead-in is already included (abx_kit L1053).
  - The onset floor is 0.085 + 2.600 = 2.685 s. The first boundary at or after it is 2.688 s.
  - The window's lower bound is (2.688 − 2.345)/2.560 = 0.134·T_heard.
  - 18 boundaries are removed (2.496 to 2.677 s), leaving about 60 passing (78 − 18). That is above the asserted minimum of 34.
  - The four places file 28 lists are corrected below: the brief, the debt row, the objection and the expected values.
- **UNDERCONVENED (Seat 1): resolved.** Seat 1 rated in files 27 and 29. Its ratings on the corrected numbers (file 29) are the ones used.

## Tension map (Seat 1 only; Seats 2–9 not required, file 25's reasons, unchallenged)
| option | S1 now/later | reason (Seat 1, file 29) |
|---|---|---|
| (1) restrict onsets, conditions 1–4 | 1/1 | "a false null on E's speech chain becomes a little more likely … carries forward to 08-3"; without condition 4, later 2 |
| (3) another MA pair | 1/1 | "reopens M3-T and repeats the measurement on all 16 scenes" |

- (2) and (4) stay out of bounds. (2) breaks item 8's "Two Harvard sentences"; (4) loosens item 7. File 28 confirmed both.

## Working
1. **Bounds:** (1) and (3) remain.
2. **Veto:** none.
3. **Worst-off seat:** a tie at 1.
4. **Sum:** a tie at 2.
5. **Cheaper to undo:**
   - undoing (1) is option (3) plus one rerun of the speech block;
   - undoing (3) means reopening M3-T and re-measuring 16 scenes.

   **(1).** Seat 1 prefers it on this ground.

## DECISION I7 (round 2)
**Run sheet, speech-chain section** (exact text):
> "**Item 7 (programme before the step).** Programme is counted from the first sample of the first programme file (sentence 1's TSP file); the kit's lead-in silence does not count. A speech onset is a candidate only if it lies (a) at or after the heard end of sentence 1 (D-M3b), (b) no later than 0.43·T_heard after the end of speech (Q5), and (c) at least lead + ⌈T·fs⌉ samples after the stimulus start (item 7), T being the construction T (M3-G). On E: onset floor 2.685 s, first candidate boundary 2.688 s, end of speech 2.345 s (stimulus time), realised window ≈ [0.134, 0.380]·T_heard, ≈ 60 passing boundaries (to be confirmed on the rebuild and fixed here before any speech stimulus is heard; never adjusted after familiarisation). **Record wording for E's speech chain:** 'speech onsets ≥ 0.134·T_heard on E (item 7); about 2 dB less mean tail exposure than an unrestricted draw.' **If E's speech and noise chains both give a non-detection,** the speech non-detection is recorded as 'weakened by the item-7 onset restriction', and option (3), a different MA pair whose first sentence gives earlier boundaries, re-measured on every pre-seal check, is the first remedy before the phase-08-3 rerun."

**⚙ Kit (`speech_layout`, `build_speech_chain`):**
- **Candidate set:** the boundaries satisfying (a), (b) and (c). Q5's ≥ 20 dB assertion and the replace-and-record rule run over this set.
- **Asserted:**
  - item 7 on the set's first boundary and on every drawn onset;
  - the set is not empty;
  - at least 34 passing boundaries;
  - the onset floor equals the value pinned in the pre-registration (a constant pinned by `test_preregistered_numbers` for E, from the rebuild).
- **Printed before the seal** (Seat 1 condition 1):
  - the tail level above the floor at every drawn onset (1 kHz band, 50 ms window, as Q5 measures it), with its minimum and median;
  - the realised window;
  - the passing count;
  - the replacement rate;
  - the onset floor and the first candidate boundary.
- **Manifest:** carries the record wording above (Seat 1 condition 3).
- **Fallbacks:** D and B apply the same rule, and their floors are pinned on use.

**Corrected expected values** (replacing file 25's):
- window ≈ [0.134, 0.380]·T_heard;
- 18 boundaries removed, about 60 passing;
- earliest onset about 0.343 s after the end of speech (was 0.151 s);
- earliest exposed tail about 4.4 dB quieter;
- mean tail exposure about 2.2 dB lower (Seat 1, [Inferred]).

**(i) and (ii):** unchanged from file 25. Both survive.

## Load-bearing claims
- **I7-L3′:** (2.688 − 2.345)/2.560 = 0.134. File 12's own lower bound reproduces under the same definition: (2.496 − 2.345)/2.560 = 0.059.
- **I7-L5:** 78 − 18 = 60, which is at least 34.
- **I7-L6 (item 4 of file 13):** a detection in either chain sets the bound to 0.5 dB, and a speech non-detection never cancels a noise detection. So a weaker speech chain cannot loosen the bound (Seat 1, file 29).

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | E's speech chain has about 2.2 dB less mean tail exposure; a false null is a little more likely, and that carries forward to 08-3 | Option (3) plus one rerun of the speech block | E's ABX result | Both chains detect, or (if both null) the speech null is recorded as "weakened" and option (3) is applied before the 08-3 rerun |
| 9 | The 0.43 ceiling (unchanged) | — | Q5 on E at the rebuild | Window recorded |

## Strongest objection
- **Seat 1's later 1.** The speech chain loses sensitivity it could not spare (power 0.41 at p = 0.75). It holds because:
  - the noise chain, Seat 1's sensitivity case, is untouched;
  - a weak speech chain can never loosen the bound;
  - condition 4 sends (3) in first if both chains give a null.
- **Option (3)** would recover about 4 dB at the earliest onset only if a new pair actually gives earlier boundaries; Seat 1 rates that as uncertain.

**Confidence:** medium (the numbers are confirmed on the rebuild).

**Reversal:** any of these:
- fewer than 34 passing boundaries on the rebuild;
- the pinned floor is not reproduced;
- both of E's chains give a null (then condition 4 applies).

## Summary
| id | decision | state | worst-off | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|---|
| I7 | (1): onsets ≥ T of programme (lead excluded); window ≈ [0.134, 0.380]·T_heard; ≈ 60 passing; Seat 1 conditions 1–4; ⚙ kit assertions and prints | revised | S1 1/1 | 2 | medium | NFR-1 | < 34 passing; floor not reproduced; double null → (3) |
| (i), (ii) | as file 25 | stand | — | — | high | NFR-1 | — |

## Decided for Maisara
- **I7.** In the speech test the step always comes after at least one full reverberation time of the room has been heard. Silence does not count toward that time. As a result, the earliest step positions are dropped, and the speech test gets slightly less sensitive (about 2 dB less reverb at the step, on average). The noise test, which carries the main weight, is unchanged.
  - If neither test hears the step, the speech result is marked as weakened, and a different sentence pair is tried before the binaural rerun.
  - NFR-1: the test is kept strict rather than relaxed.
  - The alternative, a new sentence pair now, would reopen a settled choice and redo every measurement. It serves NFR-1 no better.
  - Amends nothing of yours.

**NEEDS MAISARA:** none.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/28-interrogator-on-file25.md
- /home/user/makroof/docs/review/phase-07c-2b/29-seat1-item7-rerate.md
- /home/user/makroof/docs/review/phase-07c-2b/27-seat1-item7.md
