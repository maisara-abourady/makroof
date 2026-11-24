<!-- Saved by the orchestrator from seat 1's report, 2026-11-22. -->

SEAT 1 POSITION, round 2 (phase 07c-2): (a) X-3 in Seat 6's form, (b) D-W3

**Short answer:**
- **(a)** I rate X-3 in Seat 6's form **2 now / 2 later**. Under the decider's pre-fixed outcome rule (file 8 §4), that means X-5 wins at step 3.
- **(b)** I prefer **H-2**, provided it adopts the newest finished solve (0 now / 1 later). H-1 with a progress guarantee is acceptable (1 / 1). H-0 is 1 / 2 and H-3 is 2 / 2. None of the four is veto-grade.
- **One new point for Seats 2 and 5:** the code may already discard every solve during continuous automation, under H-0 too. That would make the "stale tail level" risk shared by all four options. M7b should measure H-0 as well as H-1 and H-2.

Corpus c1b171f. My round-1 positions stand except where noted. This round I read files 2 part 3 (M2), 6, 7 and 8.

---

## (a) X-3 in Seat 6's form

**The design:** the anchor first, then noise 0.75 → 0.5, then speech 0.75 → 0.5, as one fixed sequence at 12/16 per step.

**Reading.** The design keeps the strictness: the FWER is 0.0384 under the global null (researcher R43–R45). It fails on signal and on size. Cues: B2 (the hardest signal, and the signal the product actually carries) and my D-B3 condition A (07c-2's self-ABX uses recorded speech).

**Rating: can live with, 2 now / 2 later.**

**Why 2 now:**
1. **Speech is scored only after noise detects at both 0.75 and 0.5 dB.**
   - At p = 0.75 per step, the chance of reaching speech is 0.630 × 0.630 ≈ 0.40 [Inferred: independent blocks, researcher §2a powers].
   - In the likely outcomes, speech is never scored, so condition A is met in name only.
   - In the outcome where noise detects, the reversal has already fired. Speech then adds nothing to AX47's decision.
2. **0.75 dB as the first size leaves 0.75–1.0 dB untested.** Steps up to the 1 dB bound ship, so a null at 0.75 says nothing about the largest steps a producer will hear. That is my round-1 reason for 0.9 dB.

**Why 2 later:**
- Speech evidence will be needed at 08-3, where binaural changes how the tail is presented [Hyp], and in the class (c) round. Getting it costs a new listening session (Seat 7's debt row: about 4 sessions).
- If noise fails at 0.75, the 1 dB bound stands on a single noise null at a size below the bound.

**Conditions of acceptance:**
- **2 → 1:** speech gets its own initial α, so it is tested whatever noise does. That is the Bonferroni-split two-chain form, i.e. X-5.
- Changing the size to 0.9 without that leaves 2 / 2, because speech is still gated behind noise.
- The anchor-first position is fine with one rule: an anchor failure **voids** the block (one rerun) and is never recorded as "not detected".

---

## (b) D-W3: the ISM update held behind a running solve

**Reading.** What the user hears in each option comes down to three things:
- **The ISM hold.** Direct sound and early reflections are orientation cues, my category "keep, test under motion" (§4).
- **A stale diffuse level during long automation,** followed by one step when it ends.
- **The W floor.** M2 gives m\* = 6.

**A point the brief does not state.** The interrogator's C-1 says the L539 discard check runs before `finishExact`, and that an edit landing during the solve marks the scene dirty. If both hold, today's code (H-0) already throws away a solve that was overtaken by an edit. Under continuous automation, no solve result would be adopted under H-0 either. The B1′-held E_b would then play until the automation stops, and one AQ4 step would follow. AX47's Scope excludes that step ("recorded", not bounded).
- So starvation may not be specific to H-1. **For Seats 2 and 5 to confirm from the code** [Inferred].
- M7b should measure H-0 and H-2 as well as H-1.

| option | label | now / later | reason |
|---|---|---|---|
| **H-2 with recency adoption** (my condition) | **prefer** | 0 / 1 | The ISM never waits, so orientation cues update at the edit rate, and W is free to reach m\* = 6 (worst SE 0.323 dB). Later 1: the single step after the automation still exists and must be recorded. |
| H-2 as stated | can live with | 0 / 2 | "Adopted only if its scene is still current" never adopts under continuous automation. The tail level then stays stale for the whole move and lands in one step that nothing bounds. Room-size automation of 100 → 64 m is exactly the case that moves E_b most. |
| H-1 with a progress guarantee | can live with | 1 / 1 | The ISM hold falls to the cancel latency at `run.stop` points. Now 1: the hold is no longer zero. |
| H-1 unconditioned | can live with | 1 / 2 | Same starvation debt as H-2 as stated, and possibly as H-0 (see above). |
| H-0 (W ≤ ×5) | can live with | 1 / 2 | Now 1: at ×5 the worst layout SE is 0.375 dB (layout4 listener_corner e1, U = 1). 2 SE is 0.75 dB, below 1 jnd (Vorländer Table 6.1). The gated cubes and the s = 1 cube still meet the floor (0.170 dB via (c) at ×5). Later 2: W stays tied to the hold. On user machines with fewer cores (macOS CI pool 3) the same W holds the orientation cues longer, and the binaural ISM at 08 adds to the hold. |
| H-3 (relax the 700 ms) | can live with | 2 / 2 | It claims, without a test, that a longer lag of orientation cues under automation is acceptable. The 700 ms itself is a VR proposal applied "by extension" (Table 15.1, R29). My only measured motion thresholds are head-tracking latency (T1: lowest 52 ms, mean 108 ms), a different condition. No base rate exists for automation lag in a DAW [Hyp]. |

**Conditions of acceptance:**
- **H-2: later 2 → 1.**
  - A finished solve's E_b becomes the held level for later B1′ edits when it is newer than the one held, even if its scene is no longer current. That is strictly closer than the pre-automation E_b.
  - The generation check still blocks out-of-order adoption.
  - Adoption mechanics belong to Seats 2 and 3.
- **H-1: later 2 → 1.** A progress guarantee: a running solve is not cancelled when the last finished solve is older than a bound. M7b sets the bound; I give no number.
- **H-0: later 2 → 1.**
  - M7 on CI shows the hold ≤ 700 ms at the chosen m on all three OSes, macOS pool 3 included.
  - The ×5 layout result (0.375 dB, U = 1) is recorded as a reported-set finding, not a gated escalation.
- **H-3: 2 → 1.**
  - A blind test before any relaxation: self-ABX, a moving source on pulsed pink noise, ISM stepped at the relaxed interval against stepped at 700 ms, 16 trials, criterion fixed in advance.
  - It also touches Q4, which belongs to the Expert (NFR-3 → AQ4), so the decider rules on it, not this seat.

**Debt and where the evidence arrives:**
- **07c-2:** M7 and M7b, with the end-of-automation step size recorded for every H option.
- **07d:** load path. The keyless stage-1 at the chosen m is a matter for the class (c) round.
- **10-1:** an automation listening item (stepped versus smooth tail level, stale-level duration).
- **13:** beta producers automating room size.
- **Cost to undo:** H-0's pin can be raised later only with a golden round. H-2's threading change is a phase of rework if M7b shows starvation.

**Hand-offs:**
- **Seats 2 and 5:** whether L539 makes H-0 starve too, and the adoption mechanics.
- **Seat 3:** time variance at the step.
- **Seat 8:** the automation patterns M7b uses.
- **Decider:** H-3 and the Q4 ownership.

**Premortem.**
- **If X-3 wins:** noise fails at 0.75 dB, so speech is never scored. The 1 dB bound then ships steps of 0.75–1.0 dB that were never tested on voice. The first to notice is a producer on a vocal track.
- **If H-0 or H-2 as stated wins:** a long room-size automation plays a frozen tail level and lands in one step of several dB. Maisara notices first, on the Phase 10 automation item.

Files read: `/home/user/makroof/docs/review/phase-07c-2/8-decider-rebuttal-r2.md`, `/home/user/makroof/docs/review/phase-07c-2/2-fact-sheet-part3-m2.md` (L1–181), `/home/user/makroof/docs/review/phase-07c-2/6-interrogator-on-file5.md` (rows on C-1 and the Seat 1 conditions), `/home/user/makroof/docs/review/phase-07c-2/7-researcher-RQ-W2-6-7-9.md` (R43–R45).
