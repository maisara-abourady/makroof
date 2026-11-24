# 34: Decider on item 7, round 3 (final)

To be saved as `docs/review/phase-07c-2b/34-decider-item7-r3.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome: the restated remedy family flips the order, so I7 becomes a rule written into the pre-registration that settles itself before the seal:**
- **Search first.** Before E's seal, the builder tests other adult MA pairs in a fixed order, judged on measured checks only. The first pair that meets item 7 with no onset restriction and passes every pre-seal check on E becomes E's speech pair. That is option (3); M3-T is amended by this board decision.
- **If no pair qualifies,** E keeps MA01_01 + MA01_02 with the onset restriction. That is option (1), with Seat 1's conditions 1–3 and 5.
- **The remedy family never runs in either branch.** If a qualifying pair exists, it is used now rather than held back. If none exists, the remedy cannot be built.
- **So n = 2.** The union stays ≤ 0.098, and the α sentence of AX47 (D-M3i) is unchanged.
- **NEEDS MAISARA: none.**

## Why the restatement changes the order
Seat 1's restated condition 4 (file 32) makes the remedy a new pre-registered speech family, run if both of E's chains give a null.

**What that adds.**
- **Seat 7:** a cost it rated now 0 / later 1 (file 33): "If it fires, it adds about 0.5–0.6 h of Maisara's time."
- **Union:** it would raise n to 3 (≤ 0.147). That is inside Seats 5 and 6's rating, confirmed from their own words:
  - Seat 5, "Unsplit, at most 3 families: prefer", 1/1, with V2–V4 counted at 3 families and 0.147;
  - Seat 6's table, 3 families, 0.147, unsplit 1/1.

**The rule that needs no remedy, option (3), carries none of that cost.**
- File 28 accepted, and file 31 restated, that Seats 2–9 are not required for (1) against (3) (file 25's reasons). The only exception is Seat 7, for the contingent block, which exists only under (1).
- So Seat 7 scores 0/0 on (3), as not required.

## Tension map (now/later)
| option | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| (3) another adult MA pair meeting item 7 with no onset restriction (n = 2) | 1/1 ("reopens M3-T … repeats the measurement") | 1/1 (≤ 3 families) | 1/1 | 0/0 (not required) | 1 | 6 |
| (1) restriction plus the remedy family (n = 3) | 1/1 (file 32, conditions 1–5) | 1/1 (n = 3 rated) | 1/1 | 0/1 (file 33) | 1 | 7 |
| (1) restriction, no feasible remedy | 1/**2** (file 32: "later 2" if the remedy fails) | 1/1 | 1/1 | 0/0 | 2 | 7 |

## Working
1. **Bounds.** (2) and (4) stay out. (2) breaks item 8; (4) loosens item 7.
2. **Veto.** none.
3. **Worst-off seat.** (3) and (1)+remedy tie at 1.
4. **Sum.** (3) has 6, against 7 for (1)+remedy. **(3)**, if it is feasible.
   - Reversibility, Seat 1's reason for preferring (1), only breaks ties on sum, and there is none here.

**Whether (3) is feasible is unmeasured.** That is: whether any MA pair meets item 7 on E with no restriction and passes every check.

**Seat 7's condition 3 already requires that search before E's seal.** Seat 1's condition 2 uses the same selection criterion for a remedy pair. So the search outcome decides:
- **Pair found:** (3) applies, with sum 6, below (1)'s 7.
- **No pair found:** no remedy can be built. (1) is then the only feasible option, at 1/2. That is not a veto, and Seat 1's 2 is recorded as debt.

## DECISION I7 (round 3)
**Run sheet, speech-chain section** (exact text, replacing the item-7 paragraph of file 30):
> "**Item 7 (programme before the step).** Programme is counted from the first sample of the first programme file (sentence 1's TSP file); the kit's lead-in silence does not count. A speech onset is a candidate only if it lies (a) at or after the heard end of sentence 1 (D-M3b), (b) no later than 0.43·T_heard after the end of speech (Q5), and (c) at least lead + ⌈T·fs⌉ samples after the stimulus start (item 7), T being the construction T (M3-G).
> **Speech pair (pre-registered before E's seal; phase-07c-2b decider file 34).** The builder tries adult MA pairs in TSP index order (MA01_03 + MA01_04, MA01_05 + MA01_06, …, then MA02_…), recording every pair tried. The first pair that, on the scene in use, has its earliest candidate boundary under (a) and (b) already satisfying (c) (no onset restriction), at least 34 boundaries passing Q5's ≥ 20 dB assertion, form (b) green, B and E nulled within −120 dB, and the M3-G silences asserted, becomes the speech pair. It is named and its SHA-256s recorded before the seal. Selection grounds: measured assertions only, before any blind result; no pair is ever chosen by listening. If no pair qualifies, the pair stays MA01_01 + MA01_02 and condition (c) restricts the onsets: on E the onset floor is 2.685 s, the first candidate boundary 2.688 s, the realised window ≈ [0.134, 0.380]·T_heard and ≈ 60 boundaries pass (fixed here before any speech stimulus is heard; never adjusted after familiarisation). The record then states: 'speech onsets ≥ 0.134·T_heard on E (item 7); about 2 dB less mean tail exposure than an unrestricted draw.' No remedy speech family is pre-registered: a non-detection is never a reason to run another speech block (file 13 item 4)."

**⚙ Kit:**
1. A pair search, `speech --search-pairs`, printing one row per pair tried.
2. The assertions and prints of file 30, kept unchanged: the floor is pinned only in the fallback branch, and every drawn onset is checked against item 7.
3. `test_preregistered_numbers` pins the chosen pair's names and SHA-256s, and, in the fallback branch, the floor.

**AX47's α sentence (D-M3i):** unchanged. There are 2 families (E omni at 07c-2b, E binaural at 08-3), with a union ≤ 0.098. No contingent third family exists.

**Seat 7's conditions:**
- Conditions 1, 2, 4 and 5 lapse, because no remedy block exists.
- Condition 3 (the pair search and re-measure before the seal) is adopted as the search above.
- K6 is redone on whichever pair is chosen.

## Load-bearing claims
- **R3-L1 (file 13 items 3 and 4).** A rerun triggered by a null, pooled into E's family, gives FWER ≈ 0.060 > 0.049. That is why any remedy has to be its own family (file 31).
- **R3-L2 (files 1-seat5 and 1-seat6).** Both seats rated unsplit with at most 3 families (0.147) at 1/1. So n = 3 would have been inside their ratings, and n = 2 is too.
- **R3-L3 (map).** (3) sums to 6 and (1)+remedy to 7. Their maxima tie at 1.
- **R3-L4 (arithmetic, files 28 and 30).** In the fallback branch, the window ≈ [0.134, 0.380]·T_heard with about 60 boundaries passing, which is at least 34.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1 | (3) branch: M3-T is reopened, and the new pair's checks are measured only on the scene in use (E, plus D or B if used) | Re-measure on a fallback scene | Pair search before the seal | Pair named, hashed, and all checks green |
| 1 | Fallback branch: speech chain weakened (about 2.2 dB less mean tail), no remedy possible; later 2 | A new pair if TSP gains one, or the 08-3 rerun's result | E's ABX; 08-3 | E's noise or speech chain detects (the bound goes to 0.5 dB, so a speech null changes nothing); or 08-3's binaural run gives its own result |
| 9 | The 0.43 ceiling (unchanged) | — | Q5 on the chosen pair | Window recorded |

## Strongest objection
- **Seat 1 preferred (1).** It is cheaper to undo, and its pair has been measured on 16 scenes. But reversibility only breaks ties on sum, and the remedy that Seat 1's own condition requires is what costs (1) the extra point: Seat 7's later 1.
- **Seat 7 was not asked about (3).** If Seat 7 rated (3) at 1 or more, the sums would tie, and reversibility would return (1)+remedy. That is the reversal.

**Confidence:** medium (Seat 7 is not required on (3), and the search result is pending).

**Reversal:**
- Seat 7 rates (3) at 1 or more; or
- no MA pair qualifies (then the fallback branch applies automatically, with Seat 1 at later 2 recorded).

## Summary
| id | decision | state | worst-off | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|---|
| I7 r3 | pre-registered pair search: first adult MA pair meeting item 7 unrestricted plus all checks becomes E's pair (option (3), M3-T amended); else MA01_01/02 with the onset restriction (option (1)); no remedy family; n = 2, union ≤ 0.098 | revised | 1 (S1), or 2 in the fallback branch | 6 | medium | NFR-1 | Seat 7 rates (3) ≥ 1; no pair qualifies |

## Decided for Maisara
- **I7.** Before anything is sealed, the builder looks for another recording by the same speaker that gives the speech test a full reverberation time before the step with no tricks. It is chosen only by measured checks, never by listening.
  - If one exists, it is used, and the speech test keeps its full sensitivity.
  - If none exists, the current recording is used with the earliest step positions dropped, and the record says the speech test is slightly weaker.
  - Either way you hear the same number of tests, and no extra test is added after a "not heard" result.
  - NFR-1: the most sensitive valid test, with the pre-registration kept intact.
  - The rejected option, an extra speech test triggered by a null result, adds about half an hour and a third test family. It strains NFR-1's pre-registration only if it is run as a rerun.
  - Amends nothing of yours. M3-T is a board decision.

**NEEDS MAISARA:** none.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/31-interrogator-on-file30.md
- /home/user/makroof/docs/review/phase-07c-2b/32-seat1-condition4.md
- /home/user/makroof/docs/review/phase-07c-2b/33-seat7-condition4.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat5.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat6.md
