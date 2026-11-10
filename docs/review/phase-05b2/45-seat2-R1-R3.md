# Seat 2 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 2 POSITION: R1 (Challenge 1), R2 (Q2a (B)), R3 (Q2a (C) committed now)

**Summary.**
- **R1:** I prefer "no" (1/1). I can live with "yes" (1/2, which drops to 1/1 under one condition).
- **R2:** (B) gives the best engine accuracy of the three (0/1). Whether its restore time is acceptable is Seat 5's call. I also raise my (A) cell from 0/1 to 1/1 on C16 (g).
- **R3:** I prefer scheduling (C) now (0/1). Not scheduling it is 1/2.

**1. Reading.** All three questions ask whether the diffuse precision (W_max) is set by a restore time or by accuracy.
- The cues it triggers are §4-7 (cost against the window: t_mix,e is 0.38 s in layouts 4/5 against 0.114 s in W1, C13 §2) and §4-5 (which parameter deviates: decay level in long-window rooms with an absorbing face).
- W_max is one constant for every scene, so the 100 m restore budget decides the precision in the 20 × 30 × 10 m layout-4/5 class, where the cap binds.

**R1 (Challenge 1).**

| option | ranking | now | later |
|---|---|---|---|
| "no" (recorded and escalated, AX38 4c-1C) | prefer | 1 | 1 |
| "yes" (blocking gate, W_max (A) with D-H1's margin) | can live with | 1 | 2 |

- **"no", 1/1:** these are my confirmed 4c-1C cells (file 6-seat2). My condition then was that the gated build sits in the longest time horizon, the AX22 fallback. It is met: the flutter fallback cube is one of the gated builds (C14 (c)). The diffuse precision is not tied to anything else's timing.
- **"yes", now 1:** D-H1's margin trims W_max a little. A 10 % margin raises SE by 1/√0.9, about +5 % [Inferred]: in the closed 100 m cubes 0.20 → 0.21 dB, in layout 4 0.94 → 0.99 dB. That is negligible.
- **"yes", later 2:** the margin is the restore budget minus the existing build, so the diffuse budget becomes the slack of every later phase's restore cost.
  - When Phase 08 or a later phase adds build time at 100 m, either W_max shrinks (a golden round, changed shipped tails, larger SE in the layout-4/5 class) or the gate fails.
  - The tail level would then follow unrelated code's timing.
  - "Yes" also closes (B) permanently, unless (C) is done.
- **Condition for "yes" → 1/1:** once W_max is pinned from C++, it is never lowered to make the gate pass. A gate failure caused by another phase's build growth is fixed by moving work off the restore path, i.e. (C), not by cutting W_max.

**R2 (Q2a (B)).**

| option | ranking | now | later |
|---|---|---|---|
| (B), W_max about 11× (A) | prefer (engine accuracy only) | 0 | 1 |
| (A), as rated for comparison (raised from 0/1) | can live with | 1 | 1 |

- **(B) is the best option on my criteria.**
  - Layout 4/5 one-end SE falls from 0.29–1.33 dB under (A) (C16 (f)) to 0.06–0.22 dB (C17).
  - Under (A) those layout-4 cases spread to ±1–2 dB at p5/p95 (C13 §2), about one G jnd.
  - The 100 m SE falls to 0.05–0.12 dB (C14 (a)).
- **Later 1, for two reasons:**
  - W_max is still re-derived from the C++ cost (the prototype is a proxy).
  - (B) does not remove the both-near residual, whose fallback I owe: layout 5 both_corner is still 2.13 dB (C17 reading 3).
- **The restore cost is Seat 5's ground, not mine.** That is 2.16–4.83 s per restore and 30.2–67.6 s for 14 (C14 (c)). I do not weigh it.
- **Why I raise (A) to 1/1.** C16 (g) replaces the earlier "old error +0.09/−0.06 dB" claim. In the closed 100 m cubes the old AX16 method is off by only +0.02 dB, and by +0.06/+0.10 dB in the low-α s = 1 cube. Under (A) the new method adds random SE of 0.13–0.20 dB and 0.51/0.67 dB there (p95 ≤ 0.89 dB). In those two classes the switch makes the tail worse than before. It still corrects +2.38 dB in the absorbing-floor cube and +3.87 dB in layout 4.

**R3 (Q2a (C) committed now).**

| option | ranking | now | later |
|---|---|---|---|
| schedule (C) now | prefer | 0 | 1 |
| do not schedule | can live with | 1 | 2 |

- **Scheduling now.** It decouples precision from the restore time, so W_max can be sized to Seat 1's floor instead of the watchdog. That reaches (B)'s accuracy without (B)'s restore cost.
- **Later 1** is the phase of rework, which is Seat 5's cost, plus my conditions:
  - W_max stays a pinned work count, never a time cap, so E_target remains a pure function of the scene (AX5, S-1);
  - offline renders and bounces always wait for the completed solve and stay bit-identical;
  - what plays before the solve completes is Seats 3 and 5's question.
- **Not scheduling, 1/2.** It makes (A)'s errors permanent: about 1 jnd of SE in the long-window absorbing class, and worse than AX16 in two 100 m classes (C16 (g)). Under "yes" it also leaves W_max as the slack variable.

**5. Evidence.**
- [Observed] C13 §2, C14 (a) and (c), C16 (f), (g) and (h), C17; phase-05h §3 (D-H1).
- G jnd 1 dB: Vorländer Table 6.1, via the decider's D4-L1; corpus present, not re-read this round.
- [Inferred]: the SE scaling with margin.

**6. Conditions of acceptance.**
- **"yes" → 1/1:** the one in R1, no W_max cut to pass the gate.
- **Not scheduling (C) → 1/1:** take (B) under "no" instead.
- **D-H1's margin:** it should come from the measured C++ realised/planned work ratio (prototype 0.986–0.993 at the gated scenes) and the restore spread, as phase-05h §3 says. I add nothing to that.

**7. Hand-offs.**
- **Seat 5:** the watchdog and the restore spread, and whether (B) is vetoed.
- **Seat 1:** whether C17 meets its floor.
- **Seats 3 and 5:** the interim tail under (C).
- **Seat 7:** shipped bits changing when W_max is re-derived.

**8. Premortem.** Suppose "yes" ships with no (C). Phase 08's binaural build pushes the 100 m restore past the gate, W_max is cut to pass it, and layout-4-class tails silently get noisier with every release. The first to notice is Seat 9's Phase 12 preset check, not CI.
