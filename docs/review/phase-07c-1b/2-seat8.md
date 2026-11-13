# 2 — Seat 8 position (D-B1, D-B2, D-B4), round 1

2026-11-13, corpus c1b171f. Saved by the orchestrator from the seat's report.

Whose ears: a producer with no acoustics training, on headphones, building one scene from several stems (FR-3D-5,
FR-3D-6, A5), judging the space with every stem playing (S9). No incident covers load time or callback overruns: every
waiting judgement is [Hyp] (Maisara's producer tests). No acoustic or numeric claim; figures from file 1, AX48/AX49, the
phase file.

## D-B1 (editing an 8-stem scene while builds run)
Reading: cue 10 "where was it judged?" (hosted runners, normal-priority thread, not a host audio thread); WM8 (a dropout is
a cliff with no geography).
Ranking: B1-b prefer; B1-d, B1-a can live with; B1-c can live with only under (c).
Now / later: B1-b 0 / 0 (record, tells Phase 13 what to look at); B1-a 1 / 2 (first real-machine evidence only at Phase 13;
a remedy there is rework at the release gate, GM1/WM4); B1-d 1 / 1 (rebuilds queue: stems sit briefly in different
versions of the room, cohesion cost ST4, MSA2; a parameter, cheap to undo; evidence from B1-b's sweep); B1-c 1 / 2 (edits
later while busy; amends cond. 12, a recorded decision; costly to back out if inversion is found).
Conditions: B1-a → 1 if it carries B1-b's re-instrumentation (host audio priority, not `sleep_for` pacing); B1-c → 1 only if
Seat 5 rules the class (1) inversion safe and a board DECISION on cond. 12; B1-d: all instances of one shared edit scheduled
together (admissibility: Seat 5 / NFR-8).
Premortem: B1-a wrong → a Windows user with 8 stems hears clicks while dragging, blames the plugin.

## D-B2 (inserting a stem into a playing session)
Reading: S2 (the space established at first exposure); GF2/GF6 (a dry stem reads in-head, an unchosen POV change).
Ranking: B2-a prefer; B2-d can live with; B2-b dry can live with only as the variant in (6); B2-b silent can live with.
Now / later: B2-a 1 / 1 (host-thread stall ≈ 145–430 ms at insertion; whether other tracks glitch is Seat 5's; a reading
plus a test, cheap to undo); B2-d 0 / 2 (every default-scene change regenerates the embedded per-platform E_b, incl. canvas,
presets, E_model bumps: a standing tax; NFR-8 for Seat 2); B2-b dry 2 / 1 (dry and close, then the room fades in: a cliff
(WM8); first judgement on the wrong sound (S2)); B2-b silent 1 / 1 (short gap then a fade from silence; familiar host
behaviour [Hyp]).
Conditions: B2-b → 1 if silent rather than dry, with an AQ4 fade from silence; B2-d → 1 if the fingerprint test regenerates or
blocks automatically on any default-scene change.
Premortem: B2-b dry → she judges the stem dry, adds her own reverb, gets a doubled room.

## D-B4 (opening an 8-stem project)
Reading: ≈ 5–9.5 s until all 8 stems are audible; S2: on play every stem in the same settled space; a space that changes by
itself after play starts is worse than a long open.
Ranking: C1 + C2 prefer; C6, C7, C5, C4, C8 can live with; C3 can live with under (b).
Now / later: C1 0 / 0–1; C2 0 / 0–1 (bit-identical; evidence the measured speedup); C4 0 / — (memory Seat 5's); C6 1 / 1
(other stems settle later, output-identical; a policy, cheap to undo); C7 1 / 1 (provided the trigger is in 07d's scope); C8
1 / 2 (runners are not her chain; release-machine confirmation makes C1/C2 late work, WM4/GM1); C5 1 / 2 (output everywhere,
golden round; Seats 2, 3 own); C3 2 / 2 (the hall shorter for the first seconds then grows, while she judges depth (WM10);
a settling step the 07c-2 AX47 or L4 ABX could expose).
Conditions: C8 → 1 if C1/C2 are measured now (K17 per-instance contention printed), C8 only for the remainder; C3 → 1 only if
Seat 9 confirms L_p ≥ 0.31·T60 holds and Seat 1 confirms the step is not heard (still below every bit-identical option); C5
deferred to Seats 1 and 9.
Premortem: C3 wrong → "the reverb gets longer a few seconds after I press play", first heard soloing a lead vocal in the
hall.

## Hand-offs
Seat 1 (audibility of overrun, insertion gap, C3 step); Seat 5 (insertion stall, inversion, C4 memory, shared-edit
scheduling group); Seat 2 (B2-d NFR-8); Seat 9 (C3, C5); Seat 6 (B2-d default-scene maintenance); Maisara (a person's
action: producer tests of the acceptable 8-stem load wait). Workflow requirement most affected (§8): "Transitions with a
chosen slope… click-free" — no stem arrives dry, no space changes by itself, no dropout while editing.
