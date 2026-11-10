# Seat 6 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 6 POSITION: R1–R3 (Challenge 1, Q2a (B), Q2a (C) as a commitment)

I read `43-decider-board-answers-C1-Q2.md`, `phase-05h.md` §3 (D-H1), C14 (c), C16 (f) and C17. I did not re-read the corpus this round. The AQ10/AX36 limits are lifted for these questions on Maisara's authority (brief), so I rate on my own ground.

**1. Reading.** The question is how long a producer waits when a project with big-room instances loads, or after an edit in a big room. It also decides which 100 m presets can ship without the "approximate" note at their default placement, and whether a later split update is planned.

It triggers these cues:
- unpredictable settle time (W1);
- positions that recompute heavily (S3);
- a note at a default placement (my condition (ii), now a Phase 12 requirement, 34 §D-T1.6);
- an automatic level change after the user stops (W4).

One of my earlier conditions no longer applies. In round 1 I set the 4c-2 condition "the 100 m room is escalated rather than blocked" (`3-seat6-T5-T4.md`), because blocking on time could force D-T3. D-T3 is no longer needed (21 summary), and the diffuse work is now capped by W_max. A time gate is therefore met by construction, by trading SE, not room size. The one remaining exception is the non-diffuse build growing in C++ by itself.

**2–4. Ratings**

**R1, Challenge 1 "yes" (blocking gate, W_max (A) with D-H1's margin): prefer. 1/1 under condition (a); 1/2 without it.**
- **Now: 1.**
  - The gate keeps loading a project with 14 instances of a 100 m scene under 30 s, at about 2.1 s per instance (C14 (c) (A)). For the producer that is the gap between a project that opens and a host that appears to hang.
  - D-H1's margin trims W_max by about the realised-work ratio (≈ 1.05) plus the restore spread. At 100 m that raises SE by about √1.05, roughly 2.5 % [Inferred]. The set of placements where U fires should not change measurably [Inferred from C16 (f)].
- **Later: 1 with (a), 2 without.** If the C++ build alone approaches 2.14 s, the gate forces a choice. Without (a), the cheap way out would be narrowing the room-size range or adding a formulation seam (my round-1 reason, with the trigger now restricted to build growth).

**R1, "no" (recorded and escalated, AX38 4c): can live with. 1/1** (unchanged from the decider's 1/1†).
- Under (A), W_max is sized to the watchdog either way, so the producer gets the same experience today.
- The difference is drift: a slower C++ build shows up as slower project loads, caught only by the record and the escalation against 1/3/10 s (13 D-T4c).

**R2, Q2a (B) (W_max ≈ 11× (A); only with "no"): can live with. 2/2.**
- **Now: 2.**
  - At 100 m, a restore or full rebuild takes 2.16–4.83 s, against 2.14 s under (A). Loading 14 instances takes 30.2–67.6 s (C14 (c)).
  - At 4.83 s against 2.14 s, the diffuse part is about 2.95 s for two emitters on one thread. It sits at Vorländer Table 15.1's 3 s for the scattering part, which I apply to edits by extension.
  - A one-minute project load is a workflow break in a DAW session.
- **Gain: 1 (cuts the later debt).**
  - SE falls to 0.05–0.12 dB at 100 m.
  - U goes silent on the low-α s = 1 cube's default placement, which fires under (A) at SE 0.44–0.67 dB (C16 (f)).
  - In layout 4, the one-end cases fall to 0.09–0.22 dB SE and meet the floor; U would go silent on them [Inferred: SE < 0.33 dB, one end only] (C17 reading 1).
  - Under (A), requirement (ii) cannot be met in a cube of that type by moving the default placement, because the whole window is long. A Phase 12 preset of that type could not ship unchanged.
- **Later: 2.**
  - Every big-room project and every heavy edit pays (B)'s wait for good.
  - The gate is closed off, so restore time can grow unseen with the C++ cost.
  - (B) does not fix the both-near cases (C17 reading 3).

**R3, schedule (C) now (async diffuse solve in a later phase; (A) until then): prefer. 1/1 under conditions (b)–(e).**
- **Now: 1.** It commits about one phase of Phase 07 rework. That cost is Seat 5's and Seat 7's, not mine.
- **Later: 1.**
  - It is the only route that gives (B)-class SE without (B)'s wait, and it was my round-2 split-update condition.
  - It introduces one automatic level step after each load or heavy edit. That is the W4 pattern, bounded and inaudible under (d).

**R3, do not schedule: can live with. 1/2.**
- **Now: 1.** Nothing changes today.
- **Later: 2.** Long-window presets stay under (A). U fires at their defaults, so (ii) can only be met by changing the preset itself (lower s, smaller size). Seat 1's 2/2 debt has no repayment route except (B), which I rate 2/2.

**5. Evidence**
- C14 (c): restore times under (A) and (B).
- C16 (f): the low-α s = 1 cube fires U at its default placement under (A), with SE 0.508/0.667 dB at 8 000 and 0.442/0.504 dB at 1 024.
- C17 readings 1–4.
- phase-05h §3: D-H1 (29.98 s → about 30.2 s at a ratio of 1.05).
- 43 §2: the round-1 4c-2 cells.
- 13: D-T4c escalation at 1/3/10 s.
- 34 §D-T1.6: (ii).
- Corpus: Vorländer Table 15.1, 3 s for the scattering part, by extension to edits.
- My incidents: W1 (ASFX16) and W4.
- [Inferred] SE scaling with W_max as 1/√W.

**6. Conditions of acceptance**
- **(a) R1 "yes" → 1/1.** If the gate fails, the fix comes from W_max (SE) or the build, never from narrowing the room-size range or adding a formulation seam. If the non-diffuse build alone leaves W_max below Seat 1's floor at a gated scene, the gate result goes to Maisara before any range changes.
- **(B) → 1/2.** Only through (C)'s route:
  - the restore and edit use (A)'s W_max and are heard at once;
  - the (B)-class refinement lands in the background.

  Within (B) as stated, no change lowers it.
- **(b) R3, provisional level.** While the async solve runs, the plugin plays a defined provisional diffuse level: the (A) estimate, or the previous scene's level. Never silence, never no tail. The UI shows "settling" (D-T4a (iii)).
- **(c) R3, one step.** The tail level changes exactly once per solve, crossfaded click-free (AQ4: 30 ms equal-gain), and never mid-drag.
- **(d) R3, step size.** The provisional-to-final step must stay below Seat 1's ruling, which is Seat 1's to set. If the provisional is (A), the step is at most about (A)'s SE: 0.44–0.67 dB worst, in the low-α s = 1 cube (C16 (f)).
- **(e) R3, bounces and ordering.** Offline bounces and `render_cli` always wait for the final value. The Phase 12 check of (ii) is run, or re-run, under (C)'s W_max.

**7. Hand-offs**
- **Seat 5:** CI flakiness of the gate; the async solve's real-time safety; D-H1's margin.
- **Seat 1:** whether a 0.4–0.7 dB one-time step after load is acceptable (d); whether (B) meets its floor (C17).
- **Seat 7:** the cost of a phase of rework.
- **Seat 9 / Phase 12:** which long-window presets (ii) would block under (A).
- **Maisara:** (a)'s escalation, if it fires.

**8. Premortem.** If "no" + (B) is chosen and (C) is not scheduled, a producer opens a mix with a dozen festival-field instances and waits about a minute while the host appears frozen. Every big-room edit then lags about 5 s. A beta user's first big project shows it first; Maisara sees it at the Phase 10 sweep check.
