# Seat 8 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 8 POSITION (R1–R3: Challenge 1, Q2a (B), Q2a (C) as a commitment)

The corpus is present (Vorländer Table 6.1: the jnd for G and for C80 is 1 dB at 500–1000 Hz). No persona assumption fell. Maisara lifted the AQ10 and AX36 limits for these three questions (43, preamble), and I rate under that. Unchanged from earlier rounds: D-T4a = 4a-2G3C (solves queue), and my 4c-1C cell is 1/1 (`6-seat8-rerun-T5-T4.md`).

**The listener I am rating for.** A producer puts the listener in a big hall, an arena or a cathedral: a large room, an absorbing audience floor, highly diffusing walls. She opens the session with several instances, automates a move, and bounces. She needs the tail to give the size and distance she chose, the same in every instance, and a session that opens and bounces in minutes.

1. **Reading.** The question is where the large-room work limit sits, and whether load time is a hard gate. It sets how wrong a big hall's tail level may be, at random, against how long a session takes to load and bounce. Cues:
   - S3/S5: the point of view and depth come from the reverb ratio.
   - Cue 10: where the result was judged.
   - ST6: translation is checked mechanically, not by escalation.

2–4. **Ranking and tension (now / later)**

| id | option | label | now | later | reason (my measures) |
|---|---|---|---|---|---|
| R1 | **yes**: blocking gate, W_max (A) with D-H1's margin | prefer | 1 | 1 if R3 is scheduled; **2** if not | **For it:** it bounds multi-instance load mechanically. My standing premortem is an arena session that hangs or crashes at load, which CI with one instance never sees (3-seat8 item 8). Under (A) a restore is 2.14 s (C14 (c)). Eight queued instances are ≈ 17 s [Inf], inside the ≈ 16 s I accepted for Tol-3 (18-seat8). D-H1's margin (about 1.05) cuts W_max by about 5 %, so SE rises by about 2.5 % [Inf]: 1.33 → about 1.36 dB, nothing new. **Against it:** it pins the hall error of (A). Layout 4 at s = 1 is capped at SE 0.29–1.33 dB, and the low-α s = 1 cube at 0.44–0.67 dB (C16 (f); C17 preamble). Capped draws read low (C13 §2, cited in C16 (f) reading 3). Two instances in one hall therefore differ by √2·SE, 0.41–1.88 dB [Inf], which is up to about 1.9 jnd. The same hall reads drier than chosen and differs between tracks. **Later:** without (C) this is permanent. |
| R1 | no: recorded and escalated, AX38 4c | can live with | 1 | 1 | My 4c-1C cell is unchanged. On its own it buys me nothing unless (B) is chosen with it, and it leaves load guarded only by a report. |
| R2 | (B): W_max about 11× (A); needs R1 "no" | can live with | 1 | 2 | **Buys:** C17 one-end SE 0.06–0.22 dB in layouts 4 and 5 (0.09–0.22 in layout 4, against 0.29–1.33 under (A)); 100 m SE 0.05–0.12 dB. The hall's level stays within about 0.2 jnd, so its point of view holds. It does not fix both-near placements (C17 reading 3: 0.46–2.13 dB). **Now:** 2.16–4.83 s per restore (C14 (c)), so eight queued instances take ≈ 17–39 s [Inf]. **Later 2:** the work applies to every capped rebuild, not only at load. On C14's single-thread basis the diffuse part is ≈ 0.26 s per rebuild under (A) and ≈ 2.95 s under (B) (4.83 − 1.88). Over ≈ 5 600 updates per 3-minute bounce with position automation [Hyp], that adds ≈ 24 min under (A) and ≈ 4.6 h under (B); at 4 threads, roughly 6 min against 1.2 h [Inf]. A bounce 20–90× slower than real time loses the reason producers bounce offline (Izhaki App. A, my 6-seat8 note). Also, without the gate nothing caps load time again. |
| R3 | schedule (C) now | prefer | 0 | 1 | It costs my seat nothing now, because (A) holds until then. It gives a repayment date to the hall-error debt (S1 2/2, 43 §3) and lets W_max grow without touching load. **Later 1:** a tail that settles after load must behave as a slope, not a step (conditions). Cost: about one phase of Phase 07 rework (Seat 5's ground). |
| R3 | do not schedule | can live with | 1 | 2 | (A)'s hall error becomes the default for good. Phase 08's output modes and Phase 12's presets build on the synchronous restore. Undoing it later costs the Phase 07 rework plus whatever 08 and 12 have added [Inf]. Evidence arrives with the C++ W_max (phase 05h) and with Phase 12, if its presets contain s = 1 halls. |

5. **Evidence**
   - 43 §2–§4; `phases/phase-05h.md` §3 (D-H1: ratio about 1.05, 29.98 → about 30.2 s).
   - C14 (c): restores under (A) and (B).
   - C16 (f): SE and U under (A).
   - C17 table and readings 1–4.
   - Vorländer Table 6.1: the 1 dB jnd.
   - Incidents: GM1 (approved in one place, fails where it is heard) and RT11 (dead ends need time).
   - [Hyp]: the update count; how many producer presets use s = 1 with low α or an absorbing floor (Seats 9 and 6).

6. **Conditions**
   - **R1 yes, later 2 → 1:** (C) is scheduled (R3), and U's "approximate" note reaches the producer in capped halls (Seat 6). This is my standing condition from round 2.
   - **R2 (B), later 2 → 1:** a measured C++ bounce of a 3-minute song with position automation at 100 m, at no more than real time, shown to Maisara before (B) is adopted.
   - **R3 (C), later 1 → 0:**
     - (i) An offline bounce waits for the final solve, so what she bounces is what she heard once the tail settled (AX5 determinism).
     - (ii) The provisional-to-final change is an AQ4 crossfade, never a jump, and the editor shows that the tail is settling (Seat 6).
     - (iii) Seat 5 judges whether the solved result can travel in the saved state, so that a restore needs no solve at all.

7. **Hand-offs**
   - Host load watchdogs beyond pluginval, and the cost of (C): Seat 5.
   - Whether (B) meets the floor, and audibility of instance-to-instance differences of 0.4–1.9 dB: Seat 1.
   - Wording of "approximate" and "settling": Seat 6.
   - How common s = 1 halls are in presets: Seat 9.

8. **Premortem.** If the board chooses "yes" with (A) and no (C), a producer builds a cathedral or a hall with an audience floor. Its tail reads drier than she set and differs by about 1–2 dB between tracks. The "approximate" note shows, and she stacks another reverb on top. Beta support hears it first.

**Workflow requirement most affected:** speed (a session that loads and bounces within minutes), then depth carried by the direct-to-reflected balance.

Files read:
- /home/user/makroof/docs/review/phase-05b2/43-decider-board-answers-C1-Q2.md
- /home/user/makroof/docs/phases/phase-05h.md (§3)
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md ((c))
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md ((f))
- /home/user/makroof/docs/review/phase-05b2/44-orchestrator-C17.md
- /home/user/makroof/docs/review/phase-05b2/3-seat8-T5-T4.md and 6-seat8-rerun-T5-T4.md (my earlier 4c cells)
