# 19-seat7: Seat 7 on the L4 options and the R5(e) gate

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 7 POSITION (for the orchestrator to save as /home/user/makroof/docs/review/phase-07c-2b/19-seat7.md; I am read-only)

**1. Reading.** Two items. (1) What the L4 coverage options C, E and "B as a second bright arm" cost in Maisara's listening hours, builds and seal risk, now and later. (2) What R5(e), a three-platform CI gate (Seat 5's option (c)) before the L4 seal, costs in schedule and stall risk. Cues from my §4 and §11: a cheap option now that borrows from later phases; lateness costs more than early work (A7); fix before the next algorithm (R1); the founder's hour is the scarcest input. My file-9 now-1 was the risk that the seal stalls.

**2. Ranking**
- (1) **E: prefer.** **B-second: can live with.** It is close behind E, and it is the better buy if the 07d contest looks likely. **C: can live with.**
- (2) **R5(e) as Seat 5's (c): prefer**, with the conditions in §6.

**3. Tension now**
- **E: 0.** No extra sitting. The assert is built and green (file 18: (b) margin 2.29 dB). Two builds give identical hashes, so it cannot go red unless the code changes before the seal.
- **C: 0.** Same hours as E.
- **B-second: 1.** It adds about 0.75 h of her listening, one more stimulus build, and its own checks and seal surface. B has never been built (interrogator file 15, reason (i)). A first-build red on it would hold the seal `[Hyp]`. All of this is within my tolerance.
- **R5(e): 1.** It needs one manual CI run on the branch (the 2026-11-08 rule allows this without a PR). Debug and ASan time is unmeasured against Seat 5's 300 s budget. A Windows Release red at 1e−9 (MSVC FP contraction, file 16 §4) would hold the seal until Seat 3 rules. That stall is my file-9 risk, but this time it is a real finding, not friction.

**4. Tension later (debt)**
- **E: 1.** If 07d contests the 63 Hz–2 kHz scope (decider file 13, debt row S1), a re-sitting costs about 0.75 h, a rebuild and a re-seal at a later phase, after scores exist. If Seat 8's bright-pad case first shows up in a 13-5 beta report, it is a public trust withdrawal on the release path. The exposure assert makes a contest a little less likely than under C `[Inferred]`. Evidence arrives at the 07d AX49 review and at 13-5.
- **C: 1.** The same debt as E. Undo is symmetric before the seal (file 15, step 6), so C carries no extra cost of its own.
- **B-second: 0–1.** It pays the Seat 1 and Seat 8 debt rows now, while the kit, scene and sitting already exist. Doing it then is cheaper than at 07d or beta (A7). The 1 applies only if L4 is re-run at 08-3: the second family would then recur at about +0.75 h each time `[Hyp]`. The decider can settle that from the 08-3 scope.
- **R5(e): 0.** The seal evidence is bound to the fingerprint (file 16 §6), so it is not run again later. Without the gate, a P4/P5 break on the shipped Release binary would surface after the sitting. That would waste her hours or taint the seal. Undoing the gate is a one-line tag or step change.

**5. Evidence**
- Hours: about 0.75 h at the file-9 pace (file 13, Seat 7 row; file 9 §summary M3-L4), and α 0.0384 per family as given in the brief.
- Margins: (a) 4.17 dB and (b) 2.29 dB (file 18 §1). Debt rows: file 13.
- Release-only path and timeouts: file 16 §1, from the code.
- Lateness: A7 and P1 `[Observed]`. Fix before the next algorithm: R1.
- The rest is `[Hyp]`. I have no incident on the cost of a re-sitting (my §18).
- No acoustic fact is load-bearing here; the corpus is not needed.

**6. Conditions of acceptance**
- None is needed: nothing is rated 2 or 3.
- To lower B-second's later 1 to 0: state that L4 does not recur at 08-3, or that only the pad arm recurs there.
- To keep R5(e)'s now at 1 rather than 2:
  - fix the test file's stale header (file 15, C9: L4–6 and L10) before the manual run, so one run covers the sealed content;
  - the session starts the run, not Maisara;
  - her L4 sitting is scheduled only after the green run exists. A red must never cost her a sitting.
  - the builder records Debug and ASan `--durations` and peak RSS first (file 16 §6).

**7. Hand-offs**
- Whether the 2.29 dB (b) margin on 125 Hz is robust enough: Seats 1 and 3.
- Whether Debug-only coverage suffices, and whether 1e−9 holds under MSVC Release: Seat 3, on the builder's measurement.
- The null "not detected … one listener" is validation wording. Any public sound claim stays under Seat 1's Tier A rule. Nothing from it goes to a product page.
- Whether the bright material matters to producers: Seat 8.

**8. Premortem.** If E is taken without the bright arm and the bet loses, 07d or a beta tester hears the cut on a bright pad. The fix is then a re-sitting and a re-seal a phase or more later. Maisara notices first, as more hours; then a producer notices, in a public post.
