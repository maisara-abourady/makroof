# Interrogator on decider file 30 (I7, round 2)

**Verdict: I7 FAILS.** The arithmetic, map, tie-break, run-sheet text and kit spec are all correct. The failure is Seat 1's condition 4, adopted verbatim: it reruns the speech chain *because of* a non-detection, which the pre-registration forbids.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:** file 30; my file 28; Seat 1's files 27 and 29; phase-07c-2 file 13, items 3 and 4; `tools/ci/abx_kit.py` L1046–1056.

## What is correct
**I7-L3′: CORRECT.**
- End of speech is 2.345 s in stimulus time.
- The onset floor is 4096 + 124800 = 128896 samples, i.e. 2.685 s.
- The first boundary at or after it is ⌈128896/512⌉·512 = 129024 samples, i.e. 2.688 s.
- So the window starts at (2.688 − 2.345)/2.560 = 0.134·T_heard.
- File 12's own lower bound reproduces under the same definition: (2.496 − 2.345)/2.560 = 0.059.

**I7-L5: CORRECT.**
- 18 boundaries fall between 2.496 and 2.677 s at 10.67 ms spacing.
- 78 − 18 = 60 remain, which is at least 34.
- Consistency check: 60 boundaries starting at 0.343 s after end of speech reach 0.972 s, which matches the ceiling of 0.973 s.

**Seat 1's inferred figures check out.**
- The earliest onset moves from 0.151 s to 0.343 s after end of speech, which is about 4.4 dB less tail at E's decay rate of 60/2.6 ≈ 23.1 dB/s.
- The mean onset moves from 0.562 s to 0.658 s. That is 0.096 s × 23.1 dB/s ≈ 2.2 dB less mean tail exposure (Seat 1's [Inferred] figure).

**I7-L6: CORRECT.** File 13 item 4: a speech non-detection never cancels a noise detection.

**Map and tie-break: faithful.**
- Seat 1 rates (1) and (3) both 1/1 (file 29), so they tie on the worst-off seat and on the sum (2 each).
- Seat 1 prefers (1) as cheaper to undo, and the reasons the decider gives are Seat 1's own.

**Conditions 1–3 are adopted faithfully.**
- Condition 1: the prints are all present, and the kit adds the onset floor and the first candidate boundary.
- Condition 2: the onset floor is pinned in the pre-registration and in `test_preregistered_numbers`, and is never adjusted after familiarisation.
- Condition 3: the record wording is verbatim.

**Run-sheet text and kit spec: correct.**
- Candidate rules (a)–(c), with (c) being lead + ⌈T·fs⌉.
- The E values quoted: floor 2.685 s, first candidate boundary 2.688 s, end of speech 2.345 s, window about [0.134, 0.380]·T_heard, about 60 passing boundaries.
- The assertions: item 7 on the first boundary and on every drawn onset, a non-empty set, at least 34 passing, and the pinned floor.

## What fails: condition 4 is INCONSISTENT with file 13 items 3 and 4
Condition 4 says: if both of E's chains give a null, record the speech null as "weakened" and apply option (3) "before the 08-3 rerun".

**It breaks two pre-registered rules.**
- File 13 item 4 (D-W2), which D1 also quotes: "A non-detection is never a reason to rerun." Condition 4 runs a new speech block precisely because of a non-detection.
- File 13 item 3: the family's error rate is FWER ≤ 0.049. If the remedy block counts in E's omni family, that family gets a second speech attempt. Its error rate becomes about 0.0384 + 2 × 0.0106 ≈ 0.060, which is above 0.049.

**It is load-bearing.** Seat 1: "Without condition 4, I rate it later 2." Without condition 4, (1) is at 1/2 against (3) at 1/1, and (3) wins. So the inconsistency touches the winner, and the decision falls on it.

**What a consistent version has to state.** This is the property required, not a choice made for the decider:
- the remedy speech run (option (3)) is its own pre-registered family at item 3's thresholds, never pooled with E's first speech result;
- it counts in AX47's union rate, giving n = 3 and a union of at most 0.147. Seats 5 and 6 rated up to 3 families, so that stays inside their ratings;
- its detection sets the bound to 0.5 dB like any family's;
- Seat 1 confirms that this form keeps its later rating at 1.

## Minor
- **Debt-row "repaid when" is IMPRECISE.** It says "Both chains detect, or (if both null) …". The debt is also repaid whenever the noise chain detects: the bound goes to 0.5 dB, and a speech null then changes nothing.
- **Seats 2–9 not required.** This stands on file 25's reasons, which file 28 did not challenge. Condition 4 does add a possible extra speech block before 08-3, which is Seat 7's hours. That is a contingent reversal path, so I do not rate it UNDERCONVENED. Seat 7 should be told when condition 4 is restated.

## Ledger
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| I7 r2 | claim I7-L3′ | floor 2.685 s; first boundary 2.688 s; 0.134·T_heard | CORRECT | abx_kit L1046, L1053; 128896 → 129024 samples | — | — |
| I7 r2 | claim I7-L5 | 18 removed, about 60 passing (≥ 34) | CORRECT | 10.67 ms spacing; ends at 0.972 s against 0.973 s | — | — |
| I7 r2 | claim | 4.4 dB at the earliest onset; 2.2 dB mean | CORRECT (arithmetic, [Inf]) | 23.1 dB/s; mean 0.562 → 0.658 s | — | — |
| I7 r2 | claim I7-L6 | speech null never cancels a noise detection | CORRECT | file 13 item 4 | — | — |
| I7 r2 | map / ordering | (1) 1/1, (3) 1/1; tie broken on cheaper undo | faithful | 29-seat1 | — | — |
| I7 r2 | conditions 1–3 | prints; pinned floor; record wording | faithful | 27-seat1, 29-seat1 | — | — |
| I7 r2 | condition 4 | speech rerun triggered by a double null | INCONSISTENT with file 13 item 4 ("A non-detection is never a reason to rerun") and item 3 (FWER ≤ 0.049; about 0.060 if pooled) | file 13 items 3, 4 | **FAILS** (load-bearing: without it Seat 1 is at later 2 and (3) wins) | restate the remedy as its own pre-registered family (n = 3, union ≤ 0.147) and have Seat 1 confirm |
| I7 r2 | run sheet / kit | candidate rules (a)–(c); asserts; prints | correct | file 30 | — | — |
| I7 r2 | debt | "repaid when: both chains detect" | IMPRECISE (a noise detection alone also repays it) | file 13 item 4 | fix | — |
| I7 r2 | convening | Seat 7 and condition 4's contingent speech block | note, not UNDERCONVENED | — | — | tell Seat 7 when condition 4 is restated |
