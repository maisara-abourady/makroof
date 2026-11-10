# Seat 8 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 8 POSITION (round 2: D-T1.6 NW-4C and NW-3 re-rated, D-T1.3 N-3W*, D-T2 L2-F1R)

The corpus is present (Vorländer Table 6.1 re-read: the jnd for G and for C80 is 1 dB at 500–1000 Hz). No persona assumption fell. My first-round assumptions still hold: D-T4a = 4a-2G3C (solves queue) and D-T4c = 4c-1C.

**The listener I am rating for.** A producer on headphones puts the listener against the back wall of a club, and the band on a stage that is itself against a wall. She expects the tail to give the distance she chose, to move without clicks when she automates the position, and to be ready within minutes.

1. **Reading.** Three questions:
   - how a near-wall placement is estimated without bias or a heavy tail (NW-4C against NW-3);
   - how N is chosen within a work cap (N-3W*);
   - whether every scene pays ≈ 19.8× for a 1 % certification (L2-F1R).

   Cues: S3 (a point of view against a wall), S5 (depth comes from the direct-to-reflected balance), S4/ST5 (a slope with no click), cue 10 (where the result was judged).

2–4. **Ranking and tension (now / later)**

| id | option | label | now | later | reason (my measures) |
|---|---|---|---|---|---|
| D-T1.6 | **NW-4C** | prefer | 1 | 1 | **One end near a surface:** unbiased, no model change. SE 0.013–0.016 dB in W1, the same as at the reference positions. Largest single-history share ≤ 0.54 % (22 §(a) reading 1). The 1 cm sweeps step ≤ 0.04 dB, and the d_E = d_L crossing ≤ 0.026 dB (22 §(b)). That is a slope with no click, about 1/25 of the jnd. Under NW-1 with N-2 the step reached 0.358 dB (19 §4). **Residual, both ends near walls:** heavy-tailed; capped SE 0.15–0.29 dB; a 0.21 dB step between 0.11 and 0.10 m; VOV fails (22 §(b) reading 4). In layouts 4 and 5 the 32 k runs sit 0.87–5.2 dB from the long runs (22 §(a)). With a heavy tail the typical draw reads dry, which is my first-round premortem. **Later 1:** this residual is flagged rather than solved. It was measured only in W1 and the synthetic layouts 4 and 5, never in the rooms producers pick. |
| D-T1.6 | NW-3 (re-rated) | can live with | 1 | 2 | **My first-round cell (0/1) changes.** Its premise ("+0.03 to +0.09 dB") fell. The clamp moves the tail +0.322 dB at layout 5's absorbing wall and +0.109 dB at layout 4's absorbing floor, and −0.11 / −0.25 dB at layout 4's wall and edge (19 §4, §6). +0.322 dB is 1.29 τ and 0.32 jnd. The bias is systematic and its sign depends on position. It makes the placement a producer chooses for a dry, close point of view (against a curtain or an absorber) read wetter than the model. **Later 2:** τ cannot budget it (21, "Why I cannot decide" 1). Either CS-NW+ fails, or near-wall cases are carved out of the gate. Seat 7's limit (no accuracy claim near walls beyond CS-NW) then becomes permanent. Undoing it later means an estimator change plus a golden round, which is NW-4C anyway. |
| D-T1.3 | N-3W* as composed | can live with only on condition | 2 | 2 | **Conflict 1.** The 8 000-history pilot costs 2.7–3.1× W_max in W2 and in the gated 100 m flutter cube, so no final range fits (22 §(d) reading 3). A gated large-venue scene then gets no diffuse estimate inside the restore bound. That is the arena or hard-hall point of view lost to a sizing rule, although the scene needs only 1–16 histories. **Conflict 2.** The final N (60–6 200) is below the discarded pilot. The final SE is 0.07–0.10 dB (above 0.083 dB in 6 of 17 cases). That is ≤ 0.1 jnd: nobody hears it, and I deliberately ignore completeness nobody will hear (§2). Steps stay small because the fixed-start range shares its prefix (22 §(b): ≤ 0.006 dB at equal N). |
| D-T1.3 | N-3W* with conditions (a) and (b) below | prefer | 1 | 1 | Speed is kept in every scene, the slope stays continuous, and a cap hit is a flag rather than a silent dry tail. Later 1 because W_max is a prototype proxy and must be re-derived from the C++ cost and from Maisara's Challenge 1. |
| D-T2 | L2-F1R | can live with only on condition | 2 | 2 | Precision bought: 0.0187 dB, about 1/53 of the 1 dB jnd. **Cost [Inf], from 21 D-T2 and 22 coupling; the update count of about 5 600 per 3-minute bounce is still my [Hyp]:** (1) AQ10 room: 72–100 ms per rebuild for two emitters (single thread), so a bounce adds ≈ 6.7–9.3 min, about 2.2–3.1× real time. (2) 100 m: ≈ 1.9 s per rebuild at 4 threads, so a bounce adds ≈ 3 h, and 8 queued instances take ≈ 15 s of diffuse solving before the last one is audible. (3) At the gated 100 m scene it needs ≈ 7× W_max. Under N-3W* it is therefore capped there anyway, at an SE of ≈ 0.05 dB [Inf]. The precision is not even reached where the cost is highest. Consistent with my L2-F2 2/2 (≈ 33×). It is not a 3 at my seat; the restore-bound breach (3.7 s against 2.14 s) is Seat 5's ground. |

5. **Evidence**
   - The 1 dB jnd for G and C80: corpus, Vorländer Table 6.1. 0.322/1 = 0.32 jnd; 0.0187 dB = 1/53 jnd (my arithmetic).
   - NW-4C SE, shares, sweeps, both-near cases, conflicts 1 and 2, L2-F1R coupling: `22-orchestrator-C12.md` §(a), §(b), §(d), coupling section.
   - NW-3 bias: `19-orchestrator-NW4-and-checks.md` §4 and §6.
   - NW-1/N-2 step of 0.358 dB: 19 §4.
   - Incidents: GM1 (an approved result fails where it is heard) and RT11 (time to go down dead ends).
   - [Hyp]: how often producers place both ends within 0.3 m of walls (at 0.5 m both-near the need is 9 143 histories, near the cap; 22 §(b)); the bounce update count; the DRR jnd. **Researcher:** the Larsen et al. 2008 value is still outstanding unless already fetched.

6. **Conditions**
   - **NW-4C → 1/0:**
     - (i) Measure the both-near cases in `club` and `living_room` at 0.1, 0.3 and 0.5 m, not only in W1 and layouts 4 and 5.
     - (ii) The "near-wall, unreferenced" flag and any cap hit reach the producer as "approximate" (Seat 6 owns the wording and placement), not only TailMatch and the diagnostics.
   - **NW-3 → 1/1:** only if a long-run measurement shows |bias| ≤ τ/2 at absorbing faces in the six Phase 04 rooms. Otherwise NW-4C dominates it.
   - **N-3W* → 1/1:**
     - (a) **Pilot defined in work:** n* = min(8 000, the histories that fit a fixed share of W_max), so a final range always exists. Seat 1 sets the minimum pilot needed for a usable SE estimate.
     - (b) **No minimum final N required by my seat.** A floor N ≥ n* is acceptable if it stays within W_max and the restore bound. At cube100 it would take the work from ≈ 0.46 to ≈ 0.9 of W_max [Inf], so it should not be adopted before the C++ cost is measured.
     - (c) Keep the fixed-start range, so neighbouring positions share their prefix (the no-click property).
   - **L2-F1R → 0/0:** Maisara accepts the bias reading. CI certifies the estimator at high N, and the shipped SE follows Tol-2. Either way, her packet shows the bounce-to-real-time ratio (≈ 2.2–3.1× in the reference room, ≈ 3 h at 100 m).

7. **Hand-offs**
   - Audibility of 0.21 dB steps and of the tail-level jitter between rebuilds: Seat 1.
   - Whether NW-4C is "the same model", and the both-near physics: Seats 2 and 9.
   - Restore bound, C++ W_max, L2-F1R veto ground: Seat 5.
   - How a flag or cap hit is shown: Seat 6.
   - Wording near walls, and whether NW-4C meets "NW-3 or NW-2": Seat 7.
   - Challenge 1 and the AX36 reading: Maisara.

8. **Premortem.** If N-3W* ships with the history-sized pilot, a producer loads a hard 100 m hall: the gated scene gets no final range and either restores late or has no tail. If L2-F1R ships, her arena bounce runs for hours and she freezes it dry. Beta support hears both first. If the both-near flag stays in the diagnostics, her stage-against-the-wall scene reads drier than she chose and nobody tells her.

**Workflow requirement most affected:** transitions with a chosen slope and no click, and speed (a scene reached and auditioned within minutes).

Files read:
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
- /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md (§1, §4, §6)
- /home/user/makroof/docs/review/phase-05b2/18-seat8-T1-T2.md
- /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1)
