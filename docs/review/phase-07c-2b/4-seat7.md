# 4-seat7: Seat 7, round 2 on M3 (V1-W cell, α hours) and M3-L4

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 7 POSITION (round 2 on M3, plus M3-L4). Read-only: please save as /home/user/makroof/docs/review/phase-07c-2b/4-seat7.md.

Files read: /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md, /home/user/makroof/docs/review/phase-07c-2b/1-seat7.md, and /home/user/makroof/docs/review/phase-07c-2/32-k5-k6-clicks-session.md (K6 table, L129–168).

**R2 (a): V1-W cell. I confirm 1/1. The reason for the now cell is corrected below.**
- The decider's "about 4 h (2.6–5.6 h)" assumes the full design: 2 blocks per chain on both scenes (K6, 1.94 h per scene typical). The 0.5 dB block runs only after a 0.9 dB detection (item 4). Without a detection, K6 gives 0.99 h per scene (0.64–1.45 h).
- **The likely bill for V1-W is about 2.0 h (1.3–2.9 h), plus L4 at about 0.5 h, so about 2.5 h on the critical path.** That is about 1.2 h more than V2's likely bill. The 4.4 h branch happens only after a detection, and then the extra hours buy the most valuable finding the phase can produce. Both are inside my tolerance: now **1**.
- I admit an inconsistency in round 1. My V1 "2 now" was also priced on the full design. V1 stays at 2 on its later column, so the ranking does not change.
- Later: **1**, as before. 08-3 is about 4 h in two sittings of ≤ 2 h, and the S-W and s < 1 classes are both heard before the pin.
- Condition attached (it is a condition, not a re-rating): Raise item 2 and scope 3 must state both branches ("about 2.5 h if nothing is detected at 0.9 dB, up to about 4.5 h if something is"), with the sitting dates in the brief before the seal. If the plan text carries only "4 h", Maisara is given a worse bill than the likely one.
- Option, `[Hyp]`, for Seats 1 and 5: if S-W detects at 0.9 dB, item 4 has already set AX47 to 0.5 dB, so S-B\*'s 0.9 dB blocks add nothing to the reversal. Skipping them saves about 1 h in exactly the branch where hours run long.

**R2 (b): Seat 6's 24-trial split against unsplit + C1**
- **Hours.** The split adds 8 noise trials per block. At K6's per-trial pace on S-A-length stimuli (64.2 s typical, 38.7 s brisk, 100 s slow; both scenes are assumed to have stimuli of similar length `[Inferred]`, since ceil(T30) = 2 s on both), each block gains 8.6 min (5.2–13.3 min).
  - 07c-2b, no detection: +17 min (10–27 min).
  - 07c-2b, detection: +34 min (21–53 min).
  - 08-3 adds the same again if F3 and F4 are split.
  - A scene's full design at the typical pace becomes about 2.2 h, so a sitting splits at the chain boundary, which the decider's rule already allows.
- **What changes on my measures.**
  - Noise power falls only from 0.63 to 0.607. My round-1 objection to splitting was the drop to 0.405, and that is gone.
  - Speech power falls from 0.63 to 0.41, so a step audible only in speech is missed more often, and a customer would find it. Whether noise is the more sensitive chain is Seat 1's to say.
  - The union false-reversal rate falls from 0.098 to 0.044 at 07c-2b, and over F1–F4 from 0.196 to about 0.088 if F3 and F4 are split too.
  - At 08-3, a false reversal costs a re-pin and a golden round. 0.054 times a phase of rework (≥ 10 h, `[Hyp]`) is more than the 17–34 min the split costs.
- **Ranking:** *prefer* the 24-trial split, narrowly; *can live with* unsplit + C1.
- **Ratings:**
  - 24-trial split: now **1** (+17–34 min on a 2.5–4.5 h path), later **1** (speech power 0.41).
  - Unsplit + C1: now **0**, later **1** (the 08-3 false-reversal rate is twice as high, and a false reversal there means a re-pin).
- **F3 and F4:** treated the same way as F1 and F2, whichever is chosen. Item 15 needs trials identical to 07c-2b's for the cross-chain comparison to hold. The record states the union rate.

**M3-L4 (narrow)**
- **Hours.** 22 trials (16 scored + 6 anchors) at K6's pace. The stimulus is the chord plus ≥ L of free decay at T60 8 s, assumed to be about 11 s, which is the length of a noise stimulus (`[Inferred]`, not measured). Adding familiarisation and one break gives about **30 min (19–45 min)**. My round-1 figure of 15–30 min was low, and that assumption has fallen. A stimulus longer than about 11 s scales the time linearly, so the builder should time it the way K6 did.
- **Pre-seal build on the critical path.** As decided, the L4 flag, the T60 8 s scene with L_p < L, the seeds and the checks all have to be finished before the first scored AX47 trial. If any of them stalls (for example, the flag turns out to need a `src/sim` change, which M3-7 sends back to Seats 3 and 5), all of AX47's listening waits.
  - Rating as decided: now **1**, later **0**.
  - Condition to bring it to 0/0: the pre-registration commit freezes L4's full specification (scene, chord, level, seeds, pass rule, and the build command against the pinned engine commit). Stimuli and hashes follow in a deterministic build before L4's own first trial. Offline renders are bit-identical (CLAUDE.md, Determinism), so the hashes are fixed by the spec. Seat 1 decides whether this keeps the integrity of the pre-registration.
- **L4-A** (held chord through the provisional IR, faded, against exact):
  - *Can live with.* Now **0**: listening hours are the same, and it is the smallest build.
  - Later **1**: the handover itself, the event a user meets every time they load a long-T60 scene, is never heard in a test. If it is audible, a user finds it, as a "reverb jumps on load" thread, which is a trust withdrawal.
- **L4-B** (provisional, then an AQ4 handover to exact, against exact):
  - *Prefer.* It tests what ships, so a pass supports a claim about the product.
  - Now **1**: a handover render path is added to the pre-seal build, and a moving target may slow the listening towards the slow pace of about 45 min (`[Hyp]`).
  - Later **0**.
  - Condition to bring now to 0: build it from the existing realtime-emulation switch path (`--switch-scene` with the AQ4 fade) if Seats 3 and 5 confirm that path can carry it, and take it under the frozen-spec variant above.

**Evidence:** K6 pace and lengths, file 32 (`[Observed]` lengths, `[Hyp]` pace). Powers and union rates, files 31 and 2-decider-m3 (D-L7). Expected-cost arithmetic `[Hyp]`. My persona has no incident on validation scheduling.

**Hand-offs**
- Seat 1: speech power against noise power; the S-B\* skip after a detection; whether the frozen-spec pre-registration is equivalent.
- Seats 3 and 5: whether the switch path can carry L4-B.
- Maisara (a person's action, not a question): the sitting dates.

**Premortem:** if "4 h" goes into the plan without its branches, and L4's build stalls ahead of the AX47 seal, the listening slips on the calendar while nothing is wrong with the audio. Maisara notices first.
