# Seat 3 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 3 POSITION (R1–R3: Challenge 1, Q2a (B), Q2a (C) as a commitment)

**What I read.** I read the brief (r123.md), then:
- 43 §2–§4;
- phase-05h §3 (D-H1);
- 27 C14 (c);
- 33 C16 (f) and (g);
- 44 C17;
- my own earlier positions in 3-seat3 (4c) and 23/18.

I did not re-open the corpus. Table 15.1's 700 ms and 3 s update rows are cited as in my earlier files.

**Scale of the times.** All times are from the numba prototype and are scale only (my §12). Single-thread cost is 34–42 ns per evaluation and 4-thread cost 8.6–10.6 ns (C12 (d)). W_max (A) is 3.05 M evaluations per emitter (43 §3). (B) is W_scene = 69.5 M (C17).

**1. Reading.** Whether the 100 m restore becomes a blocking gate, which fixes W_max at (A) less a margin; whether W_max grows about 11×; and whether moving the diffuse solve off the synchronous path is scheduled now. The cues these trigger:
- decay/level accuracy: a fixed per-scene random level error from the capped solve;
- cost: the full-rebuild interval under room-size and position automation at 100 m and in long-window rooms;
- state discontinuity: a level arriving late, which is a gain step.

**Correction to a † cell.** Under the new data my (A) cell is 1/2, not the 1/1† in 43 §3.
- Under (A), every layout-4 case at s = 1 is capped at SE 0.29–1.33 dB, with U firing (C16 (f)).
- In the low-α s = 1 cube the SE is 0.51/0.67 dB, where AX16 was +0.06/+0.10 dB (C16 (g)).
- Because of S-1 that error is a fixed level offset per scene. It reaches the 1 dB G jnd at about 1 SE in the worst cases. That is criterion 2, flagged but not repaired.

**2–4. Ranking and tension (now/later)**

**R1, Challenge 1**
- **"yes" (with D-H1's margin): prefer.**
  - **Rating:** 1/1 if (C) is scheduled (R3); 1/2 otherwise.
  - **Now:** it bounds the 100 m full rebuild near 2.14 s on one thread. That is under Table 15.1's 3 s row. It is the protection I preferred in round 1 (4c-2, 1/1). The margin shrinks W_max by a few per cent [Hyp], so the SE grows by about √(1/(1 − m)) ≈ 1.03–1.05×, which is negligible against 0.29–1.33 dB.
  - **Later:** it locks (A)'s long-window level error until (C) repays it.
- **"no" (AX38 4c as decided): can live with.**
  - **Rating:** 1/1 if (C) is scheduled; 1/2 otherwise.
  - **Now:** the records and escalation met my 4c conditions.
  - **Later:** nothing blocks growth of the 100 m rebuild. Its only gain over "yes" is that (B) becomes possible, which I rate below.

**R2, Q2a (B): can live with, 2/2.**
- **Now, gain:** this is the best option on criterion 2. One-end cases in layouts 4 and 5 fall from 0.29–1.33 dB to 0.06–0.22 dB (C17 readings 1–2), and the 100 m SE to 0.05–0.12 dB (43 §3).
- **Now, cost:**
  - Every capped scene's diffuse solve rises to about 2.4–2.9 s on one thread and 0.60–0.74 s on four [Inferred: 69.5 M × cost].
  - The 100 m full rebuild therefore becomes about 1.9 + 0.7 ≈ 2.6 s on four threads and about 4.8 s on one (C14 (c)). One thread is above the 3 s row.
  - In layout 4 every position step pays the cap, because every case is capped (C17). Position automation then updates more than 700 ms apart, unless the specular update is decoupled.
  - Each solve holds the per-process gate (AX38 4a (i)) for that long.
- **Not fixed:** the both-near residual remains, at 0.46–2.13 dB (C17 reading 3).
- **Later:** an 11× budget fixed into every capped scene's rebuild interval. Undo is a parameter change. The evidence arrives with the C++ rebuild records and Phase 10's staleness gate.
- **Not mine:** the restores of 30.2–67.6 s for 14 belong to Seat 5.

**R3, Q2a (C)**
- **Scheduling it now: prefer, 1/1.**
  - **Now:** one phase of Phase 07 rework is committed.
  - **Later:** it is the only route that repays both (A)'s level debt and (B)'s interval cost. W_max can then be sized by accuracy and update interval, not by the restore.
- **Not scheduling it: can live with, 1/2.**
  - (A)'s debt register says "repaid when (C) or a larger W_max". Without (C), the only repayment left is (B), with its cost.

**5. Evidence**
- [Measured] C16 (f) and (g); C17; C14 (c); D-H1 (2.141 s; 14 × 2.141 = 29.98 s; ≈ 30.2 s at a ratio of 1.05).
- [Inferred] The rebuild and solve times above, from C12 (d) costs × W_scene.
- [Hyp] The size of D-H1's margin, and whether the ISM update waits behind the diffuse solve today.

**6. Conditions of acceptance**
- **"yes" → 1/1:**
  - (C) is scheduled.
  - D-H1's margin is set from C++ data (the realised-work ratio and a percentile of the restore spread).
  - If the margin would take more than about 20 % of W_max [Hyp], it comes back to the seats, rather than shrinking W_max to absorb noise on the CI runner.
- **"no" → 1/1:** (C) is scheduled.
- **(B) → 1/1:** measured C++ rebuilds keep the 100 m full rebuild ≤ 3 s with the pool, and the specular part is updated without waiting for the diffuse solve. The diffuse level then follows as a gain faded per AQ4.
- **(C) stays at 1/1 only if:**
  1. **The restore level equals the final level.** Example: E_target is stored in the state, or the solve completes before audio. Otherwise a level step of up to 2.4 dB lands seconds after load (C16 (g), the absorbing-floor cube, as the magnitude bound [Inferred]).
  2. Any late level is a gain change faded per AQ4.
  3. Offline renders and bounces wait for the final solve (NFR-6 bit-identity).
  4. The ISM is never held behind the diffuse solve.
  5. W_max in that phase is sized to Seat 1's floor and to Table 15.1's 700 ms and 3 s rows.

**7. Hand-offs**
- **Seat 5:** the 14-restore watchdog, the gate's flakiness and the decoupling topology.
- **Seat 1:** whether (B) meets its floor (C17).
- **Seat 7:** storing E_target in state.
- **Seat 6:** what the user sees while a late level is pending.

**8. Premortem.** "yes" plus (A) is chosen and (C) is not scheduled. A producer's 20 × 30 × 10 m absorbing hall then ships with its tail level off by about 1 dB for that scene, permanently. Seat 1 or Maisara hears it first in the Phase 12 presets.
