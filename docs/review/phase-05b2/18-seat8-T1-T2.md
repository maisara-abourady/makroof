# Seat 8 (storyteller) — positions on D-T1 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 8 POSITION (D-T1.1–1.6, D-T2)

The corpus is present (rev c1b171fe). Whose ears: a producer or DJ on headphones puts the listener in a club, a hall, an arena or against its back wall, and expects the tail to set the distance and size she chose. No persona assumption fell; the PRD's producers and DJs match it. My ratings assume D-T4a = 4a-2G3C (one diffuse solve per process at a time, so solves queue across instances) and D-T4c = 4c-1C (time is recorded and escalated). If either changed, my cost cells would move.

**Cost arithmetic [Inf].** Times come from the single-thread numba prototype (builder §3, C4). The 5 600 rebuilds for a 3-minute bounce are my earlier [Hyp] (one update about every 32 ms); Seat 5 to confirm. The table shows the diffuse cost added for 2 emitters.

| precision | AQ10 room: rebuild / bounce added | 100 m: rebuild / bounce added | load, 8 instances at 100 m (queued) |
|---|---|---|---|
| Tol-2 (SE 0.083 dB) | ≈ 4 ms / ≈ 22 s | ≈ 0.33 s / ≈ 30 min | ≈ 2.6 s |
| Tol-3 (SE 0.033 dB) | ≈ 28 ms / ≈ 2.6 min | ≈ 2.1 s / ≈ 3.2 h | ≈ 16.5 s |
| L2-F2 (SE 0.0145 dB) | ≈ 140 ms / ≈ 13 min (≈ 4.4× real time) | ≈ 11 s / ≈ 16.6 h (≈ 330×) | ≈ 86 s |

The 100 m bounce today already takes 56–75 min (Phase 07 full rebuild). The scatter itself does not touch the anchor, whose direct sound is unchanged. It moves depth only through the reverb ratio (Rumsey §2.2; Izhaki Ch. 24). The level jnd of G and of C80 is 1 dB (Vorländer Table 6.1), and a tail shift moves C80 by less than its own size. In a shared room, two instances differ by about √2·SE, i.e. 0.47 dB at Tol-1 and 0.12 dB at Tol-2. The corpus cites Larsen et al. 2008 (the minimum audible DRR difference) without its value. **Researcher:** fetch that value. Audibility is Seat 1's call.

=== D-T1 ===

1. **Reading.** How `src/sim` computes the diffuse tail level, how precise it must be and what it is checked against. Cues: §4 cue 10 (where it was judged), S5 (depth by the direct-to-reflected balance) and S3 (a point of view against a wall). Workflow requirement: speed.

2–4. **Ranking and tensions** (now / later)

| sub | option | label | now | later | reason |
|---|---|---|---|---|---|
| 1.1 | T1-F | prefer | 1 | 1 | Under 2 MB; ≈ 2 ms per emitter in the AQ10 room and 144–183 ms at 100 m at Tol-2, so every venue size stays reachable. Debt: an estimator class whose validation confidence is medium (no published validation, RQ-T1-4). |
| 1.1 | T1-B | cannot live with | 3 | 3 | ≈ 9 s per position-only rebuild in the AQ10 room, and hours at 100 m (C8, 2 ns [Hyp]). A designed far-to-near slope (criterion 4) lags by seconds when monitored live and cannot be bounced. In effect it is T1-A's range loss without the honesty. |
| 1.1 | T1-A | cannot live with | 3 | 3 | Forces D-T3. Under 1 GB it already fails CR4 (a real 42 m room) and the AQ10 room in fallback, the very concentrated-absorption case the switch is for. Arena, festival and outdoor points of view are lost (criterion 1). Undoing it means a contract bump plus a rewrite. |
| 1.2 | S-1 | prefer | 0 | 0 | The seed stays a texture control and is not also a depth nudge. Monitoring and bounce are identical under both seeds. |
| 1.2 | S-2 | can live with | 1 | 1 | A seed change moves the tail by about 1 SE: ≈ 0.33 dB at Tol-1, which nudges depth unasked; ≈ 0.08 dB at Tol-2. What the seed means to the user is Seat 6's call. |
| 1.3 | N-3 | prefer | 1 | 1 | No downward stopping bias (F12, F14). Cost follows the listener's position and is a delay, not a wrong level. The pilot adds a little cost. |
| 1.3 | N-2 | can live with | 1 | 1 | Its steps when N changes are ≤ 0.018 dB (C6). Prefix reuse leans low (F12): a corner reads slightly dry. |
| 1.3 | N-1 | can live with only on condition | 2 | 2 | A fixed 22 000 paths ships a W1 corner at −1.06 dB and the layout-4 edge at −3.9 dB (C4) without telling anyone. Under L2-F2 it rises to 2/3: ≈ 726 000 paths everywhere means ≈ 1 s per emitter even in ordinary rooms. |
| 1.4 | Tol-2 | prefer | 0 | 0 | The scatter is about 1/12 of the 1 dB jnd. The τ of 0.25 dB still separates a real fix from a bug in typical rooms (ΔL_b 0.1–0.7 dB in CR4). |
| 1.4 | Tol-3 | can live with | 0 | 1 | Precision nobody hears. 100 m: ≈ 16 s until the last of 8 instances is audible, and the bounce grows by ≈ 3 h. |
| 1.4 | Tol-1 | cannot live with | 2 | 2 | A τ of 1 dB passes an implementation that still carries the CR3-size error (−1.18 dB) the switch exists to remove. A bug in typical rooms hides inside the tolerance. |
| 1.5 | CS-3 + CS-NW | prefer | 0 | 0 | Real rooms plus the near-wall point of view. CI time is Seat 5's. |
| 1.5 | CS-2 + CS-NW | can live with | 0 | 1 | It covers the rooms producers pick (club, living_room), without real rooms. |
| 1.5 | CS-1 (without NW) | cannot live with | 2 | 2 | Only extreme synthetic layouts. The ordinary rooms and the listener against a wall go untested. |
| 1.6 | NW-3 | prefer | 0 | 1 | A near-wall point of view is carried by the direct sound and the exact specular early part, and both keep the true position. The tail shifts by only +0.03–0.09 dB (C4). Variance falls 4–7×, so a corner placement updates faster. Debt: a stated model change near walls (F4), owned by Seats 2 and 9. |
| 1.6 | NW-2 | can live with | 1 | 1 | Bias of 1–3 % (≤ 0.13 dB). Little help at edges and corners, which is where a "corner of the club" point of view sits. |
| 1.6 | NW-1 | can live with only on condition | 2 | 2 | At the cap it ships the listener's chosen point of view 1–4 dB too dry (C4, F11), and the escalation reaches Maisara, not the producer. |

**Dependence on D-T2.** Under L2-F2, D-T1.4 is moot, S-2's level coupling falls to 0/0, N-1 rises to 2/3, and the cost of near-wall placement under NW-1 grows (7.1 M paths at the W1 wall).

5. **Evidence**
- Vorländer Table 6.1: the 1 dB jnd for G and C80.
- Rumsey §2.2 and Izhaki Ch. 24: depth set by the reverb ratio.
- C4, C6 and C8: `16-orchestrator-C4-near-wall.md` and the addendum.
- Dossier: F3, F11, F12, F14.
- Session file: the ΔL_b values (phase-05b2 §0.1).
- Instances queue under 4a-2G3C (`13-…` L59).
- Incidents: GM1 (an approved result fails on the listener's chain), RT11 (dead-end streets need time).
- [Hyp]: the DRR jnd; the bounce update rate.

6. **Conditions**
- **T1-A:** none at my seat. Only Maisara's D-T3 can carry it.
- **T1-B:** measured C++ times of ≤ 1 s per position-only rebuild in the AQ10 room and ≤ 10 s per full rebuild at 100 m would bring it to 1/1.
- **N-1:** paired with NW-3 and a reported SE that is never escalated would bring it to 1/1.
- **NW-1:** an N_max that lets W1-class near-wall positions reach the target (≤ 1.6 M paths, ≈ 2 s), plus a cap hit shown to the user as approximate (Seat 6), would bring it to 1/1.
- **Tol-1:** none; Tol-2 is the fix.
- **CS-1:** adding the Phase 04 rooms and CS-NW (that is, CS-2 + NW) would bring it to 0/1.

=== D-T2 ===

1. **Reading.** The resolution parameter. Under T1-F this is the SE, and L2-F2 costs about 33× the paths of Tol-2.

2–4. **Ranking and tensions**
- **L2-F1:** can live with, 1/1. The test itself is a numerical matter (Seats 1 and 2). Its random pass or fail invites seed tuning.
- **L2-F2:** can live with only on condition, 2/2. It costs 4.4× real time per bounce in the reference room and ≈ 330× at 100 m (table above), and ≈ 86 s until the last instance is heard at load. It buys 0.0145 dB, about 1/70 of the jnd. I deliberately ignore "completeness nobody will hear" (§2). Phase 08's output modes share this rebuild budget. Undoing it is a parameter change.
- **L2-P:** 1/1 on its own terms, but it inherits T1-A and T1-B's 3/3. Near walls it is uncertified (C4).

6. **Condition (L2-F2).** Escalate it as a challenge for Maisara: should AX36's < 1 % certification rule bind the shipped per-scene SE, or certify the estimator in CI at high N while the runtime runs at Tol-2? Her ruling either way brings it to 1/1. Either way, the D-T1 packet shows her the bounce-to-real-time ratio.

=== Hand-offs ===
- Audibility of the scatter, the DRR jnd and the N-2 steps: Seat 1.
- Near-wall physics and whether NW-3 counts as "the same model": Seats 2 and 9.
- Update rate and CI cost: Seat 5.
- Seed meaning and showing a cap hit to the user: Seat 6.
- Public wording: Seat 7.

=== Premortem ===
If T1-B or L2-F2 ships: a producer automates a club into an arena, the bounce runs for hours, and she freezes the track dry. Beta support hears it first. If NW-1 and N-1 ship: her corner-of-the-club point of view sounds drier than she chose, and nobody is told.

Workflow requirement most affected: speed, a scene reached and auditioned within minutes; then depth by the direct-to-reflected balance.

Files read: /home/user/makroof/docs/review/phase-05b2/9-decider-convene-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/17-decider-convene-T1-addendum.md, /home/user/makroof/docs/review/phase-05b2/16-orchestrator-C4-near-wall.md, /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md, /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md, /home/user/makroof/docs/phases/phase-05b2.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1)
