<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2, decider rebuttal round 5: D-W3 (Q1) and D-W4 (Q2)

To be saved as `docs/review/phase-07c-2/15-decider-rebuttal-r5.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Bottom line:** the interrogator was right about the trim drag. I fix it by keeping today's discard rule exactly, which needs no reading of her decision. No seat rating changes. D-W4 now has a home (phase-10-3) and a researcher question. FM-W3a's withdrawal, D-W2 final and the D-W1 waiting list stand as checked.

## Q1: trim drags. The (P, S) key is withdrawn; today's discard rule is kept exactly

I accept the verdict: the Q2 claim is WRONG.
- `output_trim_db` is a continuous, automatable parameter (`ParameterMap.cpp` L65). It never enters `SceneDescription`, because it is applied on the audio path (`ScenePipeline.cpp` L977–998).
- A trim edit therefore leaves P and S unchanged, yet it bumps `dirty_` (L315).
- Under the (P, S) rule, a solve would be adopted as the final in the middle of a trim drag. Today's code discards that solve (L542, L555).

I do not claim that this is inside condition 4, and I write no FOR MAISARA reading. Instead the rule goes back to exactly what the code does today.

**H-2c, item 3 (replaced):**
> "A finished solve is adopted as the final only if `dirty_` is unchanged since the solve started (today's generation check, L555). Any parameter edit made while it runs discards it; edits that do not bump `dirty_` today do not. Adoption is one AQ4 step. The final is bit-identical to an uncancelled one-shot solve (D7)."

**H-2c, item 4 (made consistent):**
> "The per-generation cancel token stops a solve at its next stop point once `dirty_` ≠ its generation."

So every edit that discards a solve today now stops it early, and none is adopted. Condition 4's "exactly one step per solve and never mid-drag" holds literally. No reading is needed.

**Cells.**
- **S2: 1/2, unchanged.** This is now exactly Seat 2's own words: "Without rule 1 (generation check only): 1/2". That applies correction 3, which asked for the label.
- **S3: 1/1, unchanged.** Seat 3's conditions are (a) M7 under H-2 ≤ 700 ms, and (b) "a doomed solve stops at its next `run.stop` once its generation is stale". Both are now met in their own words: the generation is the stale test.
- **All other cells unchanged** (file 14 ledger): S1 0/2, S4 1/1, S5 1/1, S6 1/2, S7 1/0, S8 0/1, S9 0/0.
- **Totals:** maximum 2, sum 16. H-2 as stated sums 19, H-1 21, H-0 29, and H-3 is dropped on Seat 3's 3. **H-2c stands.**

**Corrections 1–4, applied:**
1. **Three later-2 cells, all named.**
   - Seat 1 and Seat 6: the diffuse level is starved during continuous automation, which is today's behaviour.
   - Seat 2: the generation check, where it asked for problem-key adoption.
   - On every decoupled option, all three need adoption during motion or a problem-only key. Condition 4 rules out both. On H-0, Seat 2's 2 remains in any case ("stays at 2 until the estimator is revisited").
   - The strongest objection and the "Decided for Maisara" line below now name all three seats.
2. **"No in-bounds variant lowers the maximum": reason restated.** Seat 1's and Seat 6's H-0 conditions are in bounds, but H-0 keeps Seat 2's 2. Every decoupled option needs adoption during motion, or a problem-only key, which condition 4 excludes.
3. **S2 label:** Seat 2's own "generation check only" rating, as above.
4. **Debt rows** are repaid at D-W4's home (Q2).

**Revised debt register (H-2c):**

| seat | what it commits later phases to | what undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 1 (L2) | the tail level stays frozen through continuous automation, then one end step | a rule change through D-W4; possibly a phase of rework if M7b shows starvation (Seat 1) | M7b (07c-2); D-W4 check (10-3) | D-W4 ruled in phase-10-3 (and her answer if case (a)), before Phase 13's beta |
| 2 (L2) | the generation check, not problem-key adoption | key change via D-W4 or condition 4 | 07c-2 CI; 10-3 | the same |
| 3 (L1) | the worker topology must survive 07d; Phase 10 sets the motion law | revert to the serial builder | 07d, 10-1, 10-3 | the 10-3 gate |
| 4 (L1) | a stale direct-to-reverberant ratio during automation | D-W4 | 08-4; 10-3 | D-W4 in 10-3 |
| 5 (L1) | a second actor (lifetime, TSan) | revert | TSan; 08-4; 10-1 | stress test green through 07d and 08 |
| 6 (L2) | "settling" lit throughout automation, then an automatic level step (W4) | D-W4; 11-3 drawing | M7b; 10-3; 11-3 | D-W4 in 10-3 |
| 8 (L1) | a stale diffuse level during long moves | D-W4 | M7b; 10-3 | D-W4 in 10-3 |

**Strongest objection.** Seats 1, 2 and 6 each keep a 2 later. No in-bounds option removes them: they need condition 4 changed, and only she can change it, once informed through D-W4. It holds because the cause, starvation plus generation discard, is today's behaviour on every option.

**Confidence:** medium. **Reversal:** M7 above 700 ms or not flat in m; a TSan race; D-W4's ruling.

**State: D-W3 (H-2c) revised and proposed. This should be the last rebuttal on it.**

## Q2: D-W4's home and the research question

**Home: phase-10-3, "Crossfade law and artefact gates under movement".** Its lead is Seat 3, and its subject is time variance under automation. It is added through `/fix-plan` as follows:

1. **Automated record, in its acceptance criteria.** Phase-10-3 repeats M7b on its shipped crossfade law. It records the end-of-automation step distribution under H-2c, and the same patterns with the alternative (the newest completed solve adopted as the held level, at most one per 3 s). The alternative runs only behind a validation-only flag, off by default, which never ships.
2. **Listening item, in its listening checklist (a person's action).** A blind check in Seat 1's paradigm, with its criterion fixed in advance by phase-10-3's loop:
   - one step at rest after automation, against stepwise adoption during automation;
   - pulsed pink noise and the TSP speech used in D-W2;
   - headphones, the D-W2 chain.
3. **The decision.** The 10-3 loop rules D-W4 on items 1 and 2.
   - If the PRD still supports two readings, the matter goes to Maisara as **NEEDS MAISARA, case (a)**.
   - Phrasing for her: "should the reverb level catch up in small steps during long automation (it follows the movement, but may be heard as steps) or stay frozen until the automation stops (no change while moving, then one larger step)?". Each option comes with its measured steps and the listening result.
4. **Deadline.** Before Phase 13's beta (Phase 10 precedes 13). If 10-3 slips past the beta, it is a Raise item in phase-13.

The debt rows above repay there.

**Research question (researcher, to run now so that 10-3 starts informed):**

> RQ-W4-1. Is there published evidence (peer-reviewed or standards) on the audibility or annoyance of small stepwise changes in late-reverberation level (or of IR updates of the late part) **during** source or listener movement, compared with a single level change after movement stops? Report the step size, the update interval, the crossfade length, the signal, the paradigm, the number of listeners and the movement speed. Include dynamic auralization studies, starting from the Lentz et al. (2007) basis of Vorländer Table 15.1, and time-varying reverberation or FDN modulation audibility studies. Say whether the result holds for late (diffuse) level changes rather than for early or specular updates.
>
> **What would change the outcome:** evidence that in-motion steps of 0.1–1 dB are below detection while a single end step of similar total size is detected points to recency adoption. Evidence of the reverse, or of equal detectability, points to keeping condition 4.

## Other items (survived in file 14, unchanged)

- **FM-W3a:** withdrawn. Condition 4 stands.
- **D-W2:** final, as pre-registered in file 13.
- **D-W1:** waiting on:
  - D-W3 (H-2c) implemented, with M7, M7b and TSan in;
  - the ABX and the class (c) / load-fallback round;
  - the pin-time measurements;
  - U2 as recorded in each seat's own terms.

## Summary

| id | decision | state | worst-off | sum | confidence |
|---|---|---|---|---|---|
| D-W3 | H-2c, with the generation check exactly as today (item 3 replaced, item 4 aligned) | revised; proposed | 2 (S1, S2, S6 later) | 16 | medium |
| D-W4 | home: phase-10-3 (automated record plus a listening item), before Phase 13's beta; RQ-W4-1 to the researcher | deferred, homed | — | — | — |
| D-W2 | final | stands | 1 | 12 | medium |
| D-W1 | waiting | waiting | — | — | — |

## Decided for Maisara

- **D-W3 (H-2c).** Edits now update the room's early sound at once, without waiting for the long reverb-level calculation. Any edit made while that calculation runs cancels it, exactly as the plugin already does today, so the reverb level still settles only after a drag or automation stops.
  - Rests on FR-SIM-6 and NFR-3 (AQ4).
  - Seat 5 gives most (a second actor to keep safe). It gets back its safety conditions and TSan as the acceptance test.
  - Seats 1, 2 and 6 keep a later 2 that only her answer on D-W4 can lift, after phase-10-3 has measured and listened, before the beta.
  - Amends none of her decisions.

**NEEDS MAISARA:** none now.
