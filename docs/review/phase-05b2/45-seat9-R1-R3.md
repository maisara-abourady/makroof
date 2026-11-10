# Seat 9 — ratings R1–R3 (Challenge 1, Q2a (B), Q2a (C))

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 9 POSITION (R1–R3: Challenge 1, Q2a (B), Q2a (C) as a commitment; 2026-11-10)

The corpus is present (c1b171f). Maisara lifted the AQ10 and AX36 limits for these questions, so none of my persona's assumptions falls here.

**What these questions decide for my seat.** They fix how much work the diffuse solve may spend per scene. That work sets the tail-level precision in one room class: a long window with one fully absorbing face, i.e. layout 4 (Kuttruff Table 5.2 case 4, absorbing floor). Kuttruff §5.7 calls that layout a crude model of most auditoria. It is my occupancy class (criterion 5; register §19, audience absorption dominates).
- This is the room where AX16 was +3.83 dB off, which is why the switch was made (BUILD_PLAN AX16).
- Under (A), C16 (f) shows the layout-4 reference positions, 1.7–2 m from any surface, capped at SE 0.43 dB with the note U raised. The one-end cases there reach 0.48–0.98 dB.
- AX44, Seat 6 (ii), says no default placement of a Phase 12 preset may raise U. Moving the placement does not help when the reference positions already raise it.
- So under (A) a hall preset of this kind either ships flagged or is changed late. That is a late palette change, the failure in my W1 incident and §4's last cue. [Inferred] whether realistic presets (audience α ≈ 0.7–0.9, s < 1) fall in this class: nobody has computed it.

**Cell corrected:** the decider read my (A) cell as 1/1†. On C16 (f) it is **1/2** unless (C) is scheduled.

**2–4. Ranking and tensions** (now / later)

| item | option | label | now | later | reason |
|---|---|---|---|---|---|
| R1 | **"no"** (recorded and escalated, AX38 4c) | prefer | 0 | 1 | It keeps (B) open, the only measured route out of the layout-4 residual. Timing is Seat 5's ground, not mine. |
| R1 | "yes" + (A) with D-H1's margin, **(C) not scheduled** | can live with | 1 | **2** | It locks W_max at the restore budget for good. D-H1's margin shrinks W_max further, and SE grows roughly as 1/√W [Inf]. The layout-4 class then stays at SE 0.43–0.98 dB, 0.4–1 jnd of G (Vorländer Table 6.1). Because the key is fixed (AX40), that error is a fixed per-scene offset that the ensembles never average out. Second risk: if the C++ ISM build alone nears 2.14 s at 100 m, the remedy that passes the gate is to cut the 100 m class. That is my round-1 4c-2 objection ("could cut the largest-error room class"). |
| R1 | "yes" + (A) + **(C) scheduled** | can live with | 1 | 1 | The debt has a scheduled repayment. |
| R2 | **(B)**, W_max ≈ 11× (A) | prefer | 1 | 1 | C17: every layout-4 one-end case and both reference positions meet Seat 1's floor, at SE 0.09–0.22 dB (0.29–1.33 dB under (A)). The 100 m cubes reach 0.05–0.12 dB (C14 (a)). What remains: in layout 5 the pilot's own VOV fails (0.13–0.46), so the lower SE is not confirmed by its own heavy-tail check. And (B) does nothing for the both-near cases (layout 5 both_corner 2.13 dB). The restore cost (2.16–4.83 s; 30.2–67.6 s for 14; C14 (c)) is Seat 5's to rate. I do not trade my cell for theirs. Later: W_max is a parameter, re-derived from the C++ cost with one golden round. |
| R2 | (A) for comparison, without (C) | can live with | 1 | 2 | As above. |
| R3 | **schedule (C) now** | prefer | 0 | 1 | It is the only option that repays the layout-4 debt without breaking the restore bound. Later 1: the interim tail level and the step when the solve lands (conditions). The one phase of Phase 07 rework is other seats' cost. |
| R3 | do not schedule | can live with | 1 | 2 under (A); 1 under (B) | Under (A) nothing repays the debt, and it surfaces at Phase 12 hall presets, after commitment. |

**Joint view (not a decision).** At 1/1 I can accept either "no" + (B), or "yes" + (A) + (C) scheduled. "Yes" + (A) with nothing scheduled is the one combination I rate 1/2.

**5. Evidence**
- C16 (f): layout-4 reference positions at SE 0.435 / 0.431 dB, capped, U raised.
- C17: the table and readings 1–4.
- C14 (c): restore times under (A) and (B).
- BUILD_PLAN AX16: +3.83 dB in layout 4. AX44: Seat 6 (ii). AX40: fixed key.
- phase-05h §3: D-H1.
- Kuttruff §5.7 and Vorländer Table 6.1 [corpus].
- 3-seat9-T5-T4.md: my 4c-2 cell.
- Whether real hall presets fall in the layout-4 class [Hyp].

**6. Conditions**
- **"yes" (later 2 → 1):** either
  - (C) is scheduled; or
  - before Phase 12 presets are frozen, every hall preset default is computed at the final W_max for SE and U, and none raises U. Plus, under either branch: a gate failure is never fixed by a room-size cut without going back to the board and Maisara.
- **(B) (now 1 → 0):** the layout-5 VOV failures are resolved by Seat 1 or Seat 2, e.g. a VOV over the union (AX44) rather than the 1 024-history pilot alone, showing the 0.06–0.15 dB estimates are not heavy-tailed.
- **(C) (later 1 → 0), two conditions:**
  - **Interim level:** until the solve lands, the tail level must not fall back to AX16 in rooms where AX16 is known to be > 1 dB off (+2.38 dB in the absorbing-floor cube; C16 (g)). Use the pilot estimate, or hold the tail until the solve lands.
  - **Offline:** offline and bounce renders wait for the full solve (AX38 offline waiters).
- **Not scheduling (later 2 → 1):** (B) is adopted, or the Phase 12 preset check above is applied.

**7. Hand-offs**
- **Seat 5:** the restore and pluginval cost of (B); the D-H1 margin.
- **Seat 1:** whether (B) meets its floor given the layout-5 VOV.
- **Seats 3 and 6:** the level step when the async solve lands under (C).
- **Seat 8 / Phase 12:** which hall presets fall in the absorbing-floor class.
- **Orchestrator:** one computation, U and SE at (A) for a 20×30×10 m room with α_floor 0.8 and s 0.5 [Hyp], to see whether realistic halls are in the class.

**8. Premortem.** If "yes" + (A) is adopted with nothing scheduled, a Phase 12 concert-hall preset with an audience floor raises U at its default placement. Then it is either relabelled or its materials are changed late. Seat 6's preset check sees it first, and a producer's A/B against a measured hall hears the remaining 0.4–1 dB scene offset after that.

Files read:
- /tmp/claude-0/-home-user-makroof/44ba3569-f338-5075-a142-3f82a248ebdb/scratchpad/r123.md
- /home/user/makroof/docs/review/phase-05b2/43-decider-board-answers-C1-Q2.md
- /home/user/makroof/docs/phases/phase-05h.md (§3)
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md (c)
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md (f)
- /home/user/makroof/docs/review/phase-05b2/44-orchestrator-C17.md
- /home/user/makroof/docs/BUILD_PLAN.md (AX16, AX44)
