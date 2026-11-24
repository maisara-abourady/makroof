# 21: Decider on P8 item 3 and the ordering for 07d's own remedy, with D1's corrections

To be saved as `docs/review/phase-07c-2b/21-decider-p8.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **P8 item 3 is adopted**, together with Seat 3's O5: the manifest records the constants each stimulus was built with.
- **The "After a void" clause is replaced** by a composed rule:
  - one L4 obligation per decision point, not per change (Seat 7 condition 1);
  - for 07d's own remedy: decide provisionally, run L4 on rebuilt stimuli, and reach `done` only once it is scored (Seat 3 O3, Seat 7 condition 2);
  - dated before the 08-4 freeze (Seat 7 condition 3).
- **Seat 3's O1, O2 and O4 are not decided here.** They are override flags, hash closure and a candidate order. They become 07d's own board round, and are carried as Seat 3's input.
- **D1 is corrected** on both points file 18 raised.
- NEEDS MAISARA: none.

## Convening
- **Seats 3 and 7 were convened**, as file 18 asked, and both answered (files 20 and 19).
- **No other seat is newly touched.** O1, O2 and O4 would touch Seats 1 (α across a sequence of candidates), 5 (the guard on the override flags) and 2 (L_p per candidate). Those options are deferred to 07d, not decided, so those seats are not needed now.

## Tension map (now/later, in the seats' words; c = read from the seat's stated conditions)

| option | S3 | S7 | max | sum |
|---|---|---|---|---|
| **Item 3, void trigger, with O5** | 0/1 ("minutes to a reseal and one L4 block") | 0/1 ("builder minutes per change") | 1 | 2 |
| Clause as written | 1/**2** ("cannot be met … picked by rationale") | 1/**2** ("number of sessions is open-ended") | 2 | 6 |
| **Composed: per decision point + O3 for 07d + dated before 08-4** | ≤1/1 c ("drops to 1 only with O3 alone") | 1/1 c (conditions 1–3 met) | **1** | ≤4 |
| Seat 3's O1–O5 now | 0/1 | unrated (hours per candidate; cap) | — | — |

- **Composed rule chosen.** It is the only option at a maximum of 1 that both seats rated.
- **O1–O5 cannot be ranked now.** Seat 7 has not rated them, and they need flags that do not yet exist (O1). Under Seat 3's own condition ("If the overrides are not built, … 1 only with O3 alone"), the composed rule holds Seat 3 at 1.

## DECISION P8-3: item 3 adopted
Sealed L4 stimuli are void if any part of AX49's provisional construction changes:
- the 0.312 fraction;
- the 0.1 s fade;
- the normalisation;
- L's rule (1.5·T60_max, capped at 12 s).

**⚙ Kit change (O5):** the L4 manifest prints, for each stimulus, the constants it was built with: f, fade length, normalisation, L rule. A void can then be read without diffing code. Item 4's hash check stays as the backstop.

## DECISION P8-S: the clause that replaces "After a void"
Exact wording for the AX49 L4 sentence and the run sheet's L4 section:
> "Voids under P8 items 1–4 force a rebuild and reseal only. An L4 session is owed once per decision point: before any board decision that reads AX49's L4 reversal, L4 is run on stimuli built with the constants then in force. Changes between two sessions collapse into one session on the latest constants. When the change is 07d's own remedy of AX49 (f, fade, normalisation, L rule), 07d decides the remedy provisionally, rebuilds the L4 stimuli with those constants, and runs L4 before reaching `done`; 07d may not be `done` while its L4 stimuli are void or unscored. If that L4 detects the cut, the remedy returns to the board with Seat 3 as its owner: one L4 session per board round. The 07d L4 session is dated before the Phase 08-4 freeze."

**For 07d's own board round** (not decided here; recorded in phase-07d.md beside AX49's reversal list by the same /fix-plan): Seat 3's O1, O2 and O4, quoted as its input.
- **O1:** validation-only overrides of f and the fade, under L-a's guard, so that each candidate is ABXed before the remedy decision.
- **O2:** the pinned remedy is closed by a hash check against the candidate it heard.
- **O4:** the candidate order is pre-registered by ascending L_p cost, and the cheapest candidate not detected is chosen.
- These need Seat 1's α for a candidate sequence, Seat 5's guard, Seat 2's L_p per candidate and Seat 7's cap on hours.

## D1 corrections
**1. Hours.** The rerun's time does not fall inside the existing K6 (builder file 32), which covers only the AX47 chains. It enters L4-T's K6 redo, under Seat 7's file-19 conditions:
- the redo counts the worst case: E's second sitting, plus the primary L4 block, plus the rerun block;
- the third-sitting decision is made on that worst case before the seal, and written into the brief with dates;
- if a rerun would push a sitting past 2 h, it opens the next sitting instead.

**2. Map.**

| rule | S1 | S6 | S7 | max |
|---|---|---|---|---|
| (a) void, pre-sealed rerun | ≤1 c (L-c reasons not triggered) | ≤1 c (same) | 1/1 (file 19: "at most one L4 block") | 1 |
| (b) "inconclusive", no rerun | later 2 c (L-c: "the remedy is chosen without data") | later 2 c (L-c: "choosing by rationale") | later 2 (file 19: "rated later 2 under L-c's reasons") | 2 |

The ordering is unchanged: (a).

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 3, 7 | Each change to AX49's constants means a reseal; one L4 session per decision point | Builder minutes; about 20 min of L4 per session | 07d's remedy; pre-session hash check | L4 scored before 07d is `done`, dated before the 08-4 freeze |
| 3 | O1, O2 and O4 not built now; 07d without overrides costs an extra board round if the provisional remedy is detected | One board round plus one L4 session | 07d | 07d's own round decides O1, O2 and O4 |
| 7 | The D1 rerun may need a third sitting | One sitting | L4-T K6 redo | Sitting plan dated in the brief before the seal |

## Strongest objection
Seat 3 prefers O1–O5: candidates ABXed before the decision, so that one session serves the remedy. Deferring them to 07d may cost one extra board round if the provisional remedy is detected.

That cost is accepted. O1 adds validation flags in a later phase, which needs its own guard, α and hours rulings. Deciding them now would bind 07d without the seats who own those questions. Seat 3's own condition puts the composed rule at 1.

**Confidence:** medium (the cells are read from conditions).

**Reversal:** 07d's round adopts O1–O5, or Seat 7 reports that the 08-4 freeze date cannot be met.

## Summary
| id | decision | state | worst-off | sum | PRD bound |
|---|---|---|---|---|---|
| P8-3 | void on any AX49 constant change; ⚙ manifest prints the constants (O5) | proposed | 1 | 2 | NFR-1 |
| P8-S | one L4 per decision point; 07d decides provisionally, L4 before `done`; detection goes to the board (Seat 3); dated before 08-4 | proposed | 1 | ≤4 | NFR-1 |
| O1/O2/O4 | deferred to 07d's own board round (Seat 3's input) | handed off | — | — | — |
| D1 corr. | rerun hours in L4-T's K6 redo (worst case); map rows shown | revised | 1 | — | NFR-1 |

## Decided for Maisara
- **Item 3 and the clause.** If the reverb-cut constants change, the test files are rebuilt. You listen again only when a decision actually depends on the result, not after every tweak. 07d's fix is decided provisionally and confirmed by your listening before 07d closes and before Phase 08 freezes. NFR-1.
  - The clause as written would have committed you to an open-ended number of sessions, and could not be met for 07d's own fix. That strains NFR-1 and L101.
  - Amends nothing of yours.
- **D1's hours.** The worst case of a possible rerun block is counted before the sitting plan is fixed. L101. Amends nothing.

**NEEDS MAISARA:** none. The person's action is unchanged: possibly a third short sitting, and one L4 session in 07d.
