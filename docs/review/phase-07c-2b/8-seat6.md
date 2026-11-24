# 8-seat6: Seat 6, R3 on M3-2

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 6 POSITION (R3 on M3-2, phase 07c-2b, narrow: α). Read-only. To be saved as /home/user/makroof/docs/review/phase-07c-2b/8-seat6.md.

I read 6-decider-m3-r2.md (M3-2 and CONVENE R3), my 4-seat6.md, and Seat 7's option in 4-seat7.md (L15). This file covers only the two items I was asked about.

**1. Reading.** There are two questions.
- (a) Does speech at ≥ 18/24 change my α cells?
- (b) Seat 7's option: if S-W (F1) detects at 0.9 dB, skip S-B\* (F2) at 0.9 dB.

The cues are the same as in R2:
- W4: the tail jumps when "settling" clears on a source admitted under class (c).
- S9: a miss, or an untested cell, gets read as approval.

**2. Ranking.**
- (a) **Speech also at ≥ 18/24: prefer, and I confirm the decider's reading of 0/1.** The 24-trial split with speech at ≥ 13/16 is close behind: can live with.
- (b) **Seat 7's skip: can live with, under conditions S1–S3 below.** Without condition S2 I rate it 2 later.

**3. Tension now.**
- **Speech also: 0.** Nothing changes at load for the user. The extra hours (about 17 to 34 min) are Seat 7's measure.
- **Skip: 0.** The reversal has already fired on F1, so the AX47 bound is 0.5 dB whether or not F2 runs at 0.9 dB. Load behaviour and the class (c) rules are the same in both cases.

**4. Tension later.**
- **Speech also: 1, confirmed.** The remaining debt is the noise chain's power loss (0.63 → 0.607), which is unchanged from R2. Speech power rises from 0.405 to 0.607, so a real step heard only in speech is missed less often. That lowers the W4 risk, but the noise chain sets my cell, so it stays at 1.
  - Debt is repaid at 08-3 and at the Phase 13 beta through the AX38 (iv) prints.
- **Skip with S1–S3: 1.** The record lacks a 0.9 dB data point for the room with early reflections (s < 1).
  - That gap matters only if AX47 or class (c) is later re-decided per room class.
  - Undoing it costs one sitting of about 1 h (Seat 7's figure).
  - The evidence would arrive at a class (c) re-decision, or at 08-3 if F4 behaves differently from F3.
- **Skip without S2: 2.** If skipping S-B\* at 0.9 dB also drops S-B\* from the 0.5 dB block, no room with early reflections is tested at the bound that now governs admission. Class (c) then admits at SE 0.5 dB with no test of the room class where the jump is least masked. That is the W4 failure, and it costs a class (c) re-decision.

**5. Evidence.**
- **False-reversal rate.** Skipping can only remove chances for F2 to give a false detection, and the reversal it would cause has already fired on F1. So the union false-reversal rate stays ≤ 0.0439 at 07c-2b, or ≤ 0.0453 with speech also [derived, from the decider's per-family figures].
- **Powers** 0.607 and 0.405, from M3-2 [derived].
- **"F2 at 0.9 dB adds nothing to the reversal"** is Seat 7's claim (`[Hyp]`, L15). I accept it for the reversal itself. I do not accept it for the per-room record.
- **The 0.5 dB block's scenes.** M3-2 says "the same design applies to the 0.5 dB block". The decision does not say whether both scenes run in that block, so I make it condition S2 [Hyp on the current text].

**6. Conditions of acceptance (skip).**
- **S1.** The skip rule is written into the pre-registration commit before the first scored trial, as a conditional branch. Adding it after any score is out. Whether such a branch is admissible is Seat 1's ground.
- **S2.** The 0.5 dB block always runs on both S-W and S-B\*. With S1 and S3 also met, this takes the later cell from 2 to 1.
- **S3.** Item 13 records "S-B\* 0.9 dB: not run (skipped after F1 detection)". It is never recorded as a null. F3 and F4 at 08-3 follow the same rule, to keep item 15's "identical to 07c-2b's".

**7. Hand-offs.**
- Seat 1: whether a branch conditioned on a detection keeps the pre-registered design valid, and how it affects the family declaration.
- Seat 7: hours under the skip. This also changes the detection branch of the Raise 2 and scope 3 texts.
- Seat 5: whether C1 needs a clause for a family that was not run.

**8. Premortem.** The failure: the skip goes ahead without S2, the 0.5 dB block runs on S-W only, and class (c) admits sources at SE 0.5 dB. A Phase 13 beta tester reopens a project in a small room with strong early reflections and hears the tail jump when "settling" clears, and that tester notices first.
