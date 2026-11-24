SEAT 3 POSITION (narrow round: P8 item 3, and the "After a void" ordering when the change is 07d's own remedy)

**1. Reading.** Item 3 voids the sealed L4 stimuli whenever AX49's provisional construction changes: the 0.312 fraction, the 0.1 s fade, the normalisation, or L's rule. The scheduling clause then asks for L4 "before 07d decides AX49's remedy". That cannot be met when the change is the remedy itself. The cues it triggers are decay accuracy and the cut, and the AX49 reversal's remedy space, which is mine as D-C9's owner.

**2. Ranking.**
- **Item 3 as a void trigger: prefer.** It is correct: L_f = t_mix,e,max + 0.312·T60_max, and the fade and normalisation define A. Change any of them and the sealed A is no longer what the plugin plays. The parity test (L4 test 7) only checks the current build.
- **The "After a void" clause applied to 07d's own remedy, as written: cannot be met.** I am not rating it veto-grade. It is unsatisfiable, so it will be either waived or ignored. Either way the remedy is chosen without data, which is the L-c state that Seats 1, 2, 3 and 6 rated later 2.
- **My option, the ordering below: prefer.**

**3. Tension now.**
- Item 3: **0**.
- The clause as written, for 07d's remedy: **1**. Today it only adds a sentence that cannot be met.
- The ordering below: **0**.

**4. Tension later.**
- **Item 3: 1.** Each change to the constants means minutes to a reseal and one L4 block (about 20 min, Seat 7's figure). The evidence comes from 07d or any later change to AX49. The item-4 hash check catches anything item 3 misses.
- **The clause as written: 2.** At 07d, AX49's remedy is either picked by rationale and then reopened if a later L4 detects the cut (a board round plus about 1 h of ABX, per Seat 1's file 9), or 07d cannot reach `done`. Either way the remedy trades load time against cut depth blind. L_p at the rated corner already binds at 3.82 s, and Windows takes 9.51 s against the 5 s line.
- **The ordering below: 1.** The remaining debt is the ABX hours per candidate, which is Seat 7's to cap.

**Ordering I propose.** It replaces the clause only where the change is 07d's remedy of AX49. For changes made in any other phase, the clause stands.
- **O1. Candidates are ABXed before the remedy decision.**
  - Each candidate is a set of constants: fraction f, fade length, normalisation, L's rule.
  - Its stimuli are built through the L4 tool (L-a's `--provisional-ir`, extended with validation-only overrides of f and the fade; Seat 1's optional condition, file 9). They are tested against the exact tail with the same scene, chord, anchor and assertions as L4-D 1–13 and tests 1–8.
  - That candidate ABX is the L4 on rebuilt stimuli. Its result is what the remedy decision reads.
  - The overrides follow L-a's guard: off by default, never reached from src/plugin, and recorded in the manifest.
- **O2. The pinned remedy is closed by a hash check, not a second session.**
  - After 07d pins its constants, it rebuilds A and B with the shipped code, without overrides.
  - If the SHA-256 of both equals the hashes of the candidate's ABXed IRs on the same platform (AX5; P8 item 4), the candidate's result stands as the L4 result for the new constants.
  - If they differ, L4 is rerun on the rebuilt stimuli before 07d reaches `done`.
- **O3. A remedy the overrides cannot express** (a new fade shape, a different construction):
  - 07d decides it provisionally, rebuilds, and runs L4 before `done`;
  - the decision's reversal reads that L4.
  - 07d may not reach `done` while its L4 stimuli are void.
- **O4. The candidate order is pre-registered before any candidate is heard.**
  - Ascending L_p cost, because each step up in f or fade lengthens the load wait at the rated corner (Seats 2 and 6).
  - The cheapest candidate not detected is chosen.
  - The family α across the sequence of candidates is Seat 1's to set.
- **O5. The manifest records the constants each stimulus was built with** (f, fade, normalisation, L rule), so item 3's void can be read without diffing code.

**5. Evidence.**
- **Cut depth.** It is 60·f dB below the tail's start. At f = 0.312 that is 18.7 dB, so energy past L_f is at most e^(−4.312) = 0.0134 [Observed, arithmetic; AX49 K17′, Vorländer §6.4.1 Eq. 6.4].
- **Decay after release.** After the chord is released, the free decay follows the backward-integrated IR [Kuttruff §8.4 Eq. 8.29]. So any change of f or of the fade changes exactly the part of the decay that L4 hears.
- **Hashes identify the stimulus** on one platform and build [CLAUDE.md Determinism; AX5; P8 R-L4].
- That a candidate set of size ≤ 3 is enough is [Hyp]. I have no incident covering it.

**6. Conditions of acceptance.**
- The clause as written (later 2) drops to 1 if O1 to O3 replace it for 07d's own change.
- If the overrides are not built, it drops to 1 only with O3 alone: decide provisionally, then L4 before `done`. That costs one extra board round if the provisional remedy is detected.
- Item 3: no condition, apart from O5.

**7. Hand-offs.**
- Seat 7: the hours, at one L4 block per candidate plus a possible rerun, and a cap on the number of candidates.
- Seat 1: the α for the candidate sequence (O4), and whether "the cheapest not detected" is a valid stopping rule.
- Seat 5: the guard on the override flags, and the hash check in CI or the kit.
- Seat 2: L_p at the rated corner for each candidate.

**8. Premortem.** If the clause stays as written and fails, it fails like this: 07d waives it, raises f by rationale, and the larger L_p pushes the Windows load wait further past 5 s, while the cut is still audible on a stopped pad. Maisara notices first, at her Phase 11 reopen-project check.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/17-decider-l4-rules.md
- /home/user/makroof/docs/review/phase-07c-2b/18-interrogator-on-file17.md
- /home/user/makroof/docs/review/phase-07c-2b/9-seat{1,2,3,6,9}-l4.md (only the lines on the remedy and the fade)
