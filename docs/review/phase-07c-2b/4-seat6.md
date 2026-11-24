# 4-seat6: Seat 6, round 2 on M3-2 (α)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 6 POSITION (round 2 on M3-2, phase 07c-2b, narrow: α read as the load time and level jumps the user sees)

I read 2-decider-m3.md (M3-2, M3-4 item 15, CONVENE R2) and my round-1 file 1-seat6.md. This answer covers only what changed since round 1. The change is V1-W: 07c-2b now has two families, F1 and F2, so the union rate under unsplit is ≤ 0.098 at admission.

**1. Reading.** Under V1-W, should F1 and F2 use my 24-trial split or stay unsplit with C1? And what should F3 and F4 use? The cues are the same as in round 1: S3 (heavy recompute at load), W4 (the level jump when "settling" clears) and S9 (a miss read as approval).

**2. Ranking (it has changed since round 1).**
1. **24-trial split, applied to F1–F4: prefer.** Per scene: noise is 24 scored trials plus 6 anchors, with a break after trial 15, pass at ≥ 18/24; speech passes at ≥ 13/16.
2. **Unsplit + C1: can live with.**
3. **13/13 split: still 1/2 (can live with).** I would not want it as a fallback.

Why the order flipped: with one 07c-2b family the split bought nothing. With two families, unsplit carries a 0.098 false-reversal rate, while the 24-trial split costs only 2.3 points of noise power: 0.63 → 0.607, so the miss rate goes from 37 % to 39.3 %. In exchange, the false-reversal rate falls by more than half, from 0.098 to 0.0438.

**3. Tension now.**
- **24-trial split: 0.** Nothing changes at load for the user. The +8 noise trials per scene cost hours, and hours are Seat 7's measure, not mine. My round-1 cell "1/1 c" becomes 0/1.
- **Unsplit + C1: 1, confirmed.** A false reversal (P ≤ 0.098 at admission) only removes a possible load-time gain on keyless loads. It never makes today's load slower.

**4. Tension later.**
- **24-trial split: 1.** The residual cost is the 2.3-point power loss in each noise family: a real sub-1 dB step is missed slightly more often. A miss can let class (c) admit a source at SE 0.5 dB, and a producer reopening a project then hears the tail jump when "settling" clears (W4). The size of that risk shows at 08-3 or with Phase 13 beta users. Undoing it means a class (c) re-decision. Under four families the union rate is ≤ 0.0876, which is below unsplit's 0.098 for 07c-2b alone.
- **Unsplit + C1: 1, confirmed.** Over F1–F4 the union rate is ≤ 0.196. A false late flip after class (c) admission forces re-admission at SE ≤ 0.25 dB. That means a re-decision, plus about 4× the samples on keyless loads, which are already over the 10 s line on 8 × 100 m rooms (AX38 (iv): 19.5 to 23.0 s). C1 keeps the cost to a constant change, so I stay at 1.

**What I want for F3 and F4:** the same 24-trial split. Item 15 already requires trials "identical to 07c-2b's", so F3 and F4 must inherit whatever F1 and F2 use. Splitting 07c-2b while leaving 08-3 unsplit would break that identity. This puts 0.0219 on each of F1–F4, 0.0438 at 07c-2b and ≤ 0.0876 overall. My condition: if Seat 1 or Seat 7 cuts the trial count after K6, the fallback is unsplit + C1 on all four families, never 13/13.

**5. Evidence.**
- Null tail P(≥ 18 of 24) = 190051/16777216 = 0.0113, plus 0.0106 for speech, gives 0.0219 per scene. Power is ≈ 0.607 at p = 0.75 [derived; decider D-L7 re-checked the null tail].
- 4 × 0.0219 = 0.0876 [arithmetic].
- The 0.63 noise power under unsplit comes from file 31 answer 4 [derived].
- The AX38 (iv) load records are a [plan record].
- The ~4× samples for half the SE is [Hyp] on the real cost. It is Seats 2 and 5 to measure.

**6. Conditions of acceptance.** Neither option is rated 2 or 3, so none are needed. The unsplit conditions (i)–(iv) as attached in M3-2 still hold if unsplit is chosen. (i) and (iv) also apply under the split.

**7. Declaration of F1–F4: confirmed,** with three conditions:
- **(a) Seat 4's "(i) chain comparison only".** I confirm it. A detection on (i) reverses AX47. A non-detection on (i) is not binaural evidence. For my seat that is acceptable: what a reversal costs me is load time, not a wrong sound.
- **(b) A 0.5 dB detection at 08-3 reopens class (c) at the board.** I confirm it. If a source has already been admitted by then, shipped load behaviour must not change silently. Any change shows in the AX38 (iv) time-to-audible print, and "settling" stays visible through every keyless load (AX38 (iii)).
- **(c) Within each family,** a speech non-detection never cancels a noise detection.

**8. Hand-offs.**
- Seat 7: the hours for +8 noise trials per scene, at 07c-2b and again at 08-3.
- Seat 1: power, the break after trial 15, and whether F3 and F4 can carry 24 trials in sittings of ≤ 2 h.
- Seat 5: whether the 0.0438 / 0.0876 rates change C1.

**9. Premortem.** If unsplit stands, F1–F4 give a false reversal at a cumulative rate up to 0.196. If one fires at 08-3 after admission, re-admission is forced at SE 0.25 dB, and a producer reopening a large-room project waits longer for sound. A beta tester notices first.

Read-only; to be saved as /home/user/makroof/docs/review/phase-07c-2b/4-seat6.md.
