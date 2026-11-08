# Phase-07 decider round 3 (D7 restore flag): interrogator, decision mode, round 3 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

**Outcome: SURVIVES WITH CORRECTIONS.** Answers round-2 Q1 (flag consumed on submit or skip; test (b)).

| claim | verdict | evidence |
|---|---|---|
| flag cannot outlive an identical restore | CORRECT | consumed on submit or skip; test (b) |
| L8 flag cannot outlive its restore | IMPRECISE (gap) | prepareToPlay's synchronous build and reset step 3 are decisions at generation ≥ g_R but not listed; Logic calls setStateInformation → prepareToPlay → reset; if not consumed there, the next ordinary update gets EqualPower (+3.01 dB, Vorländer Eq. 4.15) and the fresh-instance bounce can differ |
| L9 offline determinism | CORRECT if L8 fixed | — |
| skip rule; reset step 3; R3-1/R3-2 | CORRECT | — |
| merge case (d) | CORRECT | — |
| law at reset step 3 | consistent | installed at once before the first P samples; otherwise same ramp every bounce |
| −100 dB null vs analytic crossfade at plugin level | FEASIBLE under conditions | EG vs EP ramps 0.5 vs 0.707 mid-fade; Phase 06 nulls ≤ −133 dB (repo); mono preview in the reference |
| generic (NFR-8) | CORRECT | — |

Corrections: (1) name prepareToPlay's synchronous build and reset step 3 as consuming decisions (a build discarded
in reset step 1 is not a decision); (2) test (f): setStateInformation → prepareToPlay or reset → listener_y change is
EqualGain, realtime and offline; extend (e) to a fresh instance restoring before prepareToPlay, bit-identical to the
reset-instance bounce; (3) null-test conditions: trim 0 dB with the smoother snapped (gain exactly 1.0f) or the
reference applies the same gain; reference fade starts at s0 = (⌊r/P⌋+2)·P read from `fadeStartSample()` (AX31);
reference IRs built from the same scenes at the same rate (AX5).

Main session: the advocate (round 2) cleared D7 to go to /fix-plan once the interrogator confirms; corrections are
specified with no acoustic choice, so they are applied with the D7 text.
