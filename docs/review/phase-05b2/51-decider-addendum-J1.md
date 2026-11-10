# Decider — addendum to file 47 (interrogator file 49; Seats 1, 3, 4, 8)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

# Decider: addendum to file 47 (interrogator file 49; Seats 1, 3, 4 and 8 confirmations)

This addendum applies interrogator file 49's corrections 1–9 and the four seat confirmations (50-seat1, 50-seat8, 48-S3c, 48-S4c). Nothing else is reopened.

**The decision is unchanged.** Challenge 1 = yes, Q2a = (A) now, and (C) is scheduled to land before the first public release. Q2b stays at (i), n\*_max = 1 024. Corrections 6 and 7, which had to be fixed before this record replaces the orchestrator's statement to Maisara, are applied below.

## 1. Corrected combined map

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| **J1** (yes + (A) + (C) scheduled) | **2/1** | 1/1† | **1/1** | **1/1** | 1/1 | 1/1† | 1/1† | **1/1** | 1/1 | 2 | **19** |
| J2 (no + (A) + (C) scheduled) | 2/1 | 1/1 | 1/1 | 1/1 | 1/2 | 1/1 | **1/2** | 1/1 | 1/1 | 2 | **21** |
| J3 / J4 (no (C)) | 2/2 | … | 1/2 | … | 1/2 | 1/2 | 1/2 | 1/2 | 1/2 | 2 | 27 |
| J5 ((B) now) | | | | | 2/**3** | | | | | 3 | – |

Changes to the cells, by correction:
- **Correction 2, S1.** Seat 1 confirms its J1 cell is 2/1 (50-seat1). Its R1 1/1 rated only the gate's own cost; J1 also contains Q2a (A), whose "now" 2 stands until (C) ships. Its later 1 needs its three R3 conditions, and file 47 §4 (iii) carries each of them:
  - (i) W_max re-derived under (C) from the background budget: (iii) 3.
  - (ii) the bounce waits for the final solve: (iii) 6.
  - (iii) "settling", a crossfaded swap, and no AX16 interim tail where AX16 is more than 1 jnd wrong: (iii) 4 and 5. 1 jnd of G = 1 dB, Vorländer Table 6.1.
- **Correction 1, S3.** Seat 3 confirms 1/1 (48-S3c): its Q2a (A) cell falls from 1/2 to 1/1 with (iii) 1–8.
- **Correction 1, S4.** Seat 4 confirms "yes" at 0/1 (48-S4c). The † is removed.
- **Correction 3, S8.** Seat 8 confirms later 1 (50-seat8). U fires where its condition is meant to apply (capped SE > 0.33 dB). The capped cubes where U is silent are at about 0.1 jnd and not skewed (C15). The cell returns to 2 only if U's note stays in the diagnostics and never reaches the producer's editor, so the phase-11 note display (AX44) carries it.
- **Correction 4, S7 in J2.** Read at 1/2. J2 does not contain Seat 7's conditions on "no".

**Working.**
- Bounds and veto drop J5.
- J1 through J4 all have max 2, from Seat 1's Q2a (A) "now".
- Sums: J1 19, J2 21, J3/J4 27. **J1 wins.** There is no tie, so reversibility is not reached.

## 2. Corrected load-bearing claims
- **L3 (C16 (f), (g); values at n\*_max 1 024, as in AX41).** Under (A):
  - layouts 4/5 at s = 1 are capped at SE 0.13–1.33 dB;
  - the low-α s = 1 100 m cube at 0.44–0.50 dB, where AX16 was only +0.06 / +0.10 dB off;
  - the closed 100 m cubes at s = 0.3 at SE 0.09–0.15 dB, and the absorbing-floor cube at 0.09–0.10 dB, with U silent in both;
  - the absorbing-floor cube's +2.4 dB AX16 error is corrected.

  This is the basis of Seat 1's 2, which stays until (C) ships.
- **L5 (C18, C16 (f)).**
  - Four 20 × 30 × 10 m halls with an absorbing audience floor (α 0.6–0.8) and s ≤ 0.5 keep the short window, are never capped under (A), stay within SE 0.083 dB, and leave U silent.
  - Rooms near 100 m are capped under (A), at SE ≤ 0.15 dB in the s = 0.3 and absorbing-floor cubes, with U silent; in the low-α s = 1 cube at 0.44–0.50 dB, with U firing.
  - The capped class is therefore the long-window synthetic s = 1 layouts **and** rooms near 100 m. Only the former, and the low-α s = 1 cube, carry errors above 0.33 dB.

## 3. Margin risk (correction 7)
**Strongest objection (added).** D-H1's margin will probably exceed Seat 3's 20 % trigger and return to the seats.
- Seat 5's own arithmetic: a 3 % spread on the 1.884 s build is 0.057 s, which is 22 % of the 0.259 s diffuse budget. Add about 5 % for the realised-work ratio of about 1.05, and the margin is about 27 % of W_max.
- A 27 % smaller W_max raises the capped-scene SE by about 1/√0.73, i.e. about 17 % [Inferred]. For example, layout 4 rises from about 1.33 to 1.56 dB, and the low-α cube from about 0.50 to 0.58 dB.
- The decision holds because the trigger sends the margin back to the seats with the C++ numbers. Their options there are to accept the smaller W_max, or to bring (C) forward. It is never resolved by a time cap or a narrower room range (§4 (i)).
- It would not hold if the C++ spread forces a margin that leaves W_max below Seat 1's floor at a gated scene. That case goes to Maisara, per Seat 6 (a).

**New debt-register row**

| seat | commits | undo | evidence | repaid when |
|---|---|---|---|---|
| S3, S5 (and S1 via SE) | D-H1's margin is probably about 27 % of W_max, above the 20 % trigger | a board round on the margin, or (C) brought forward | the C++ restore spread over ≥ 10 runs and the realised-work ratio | the margin is decided by the seats from C++ data, or (C) lands |

**S1 register row, corrected figures:** SE 0.13–1.33 dB in layouts 4/5 at s = 1, and 0.44–0.50 dB in the low-α s = 1 cube, until (C).

## 4. Plan changes (§5, completed per correction 8)
1. **AQ10 amendment and AX38 4c (Challenge 1 yes)** carry these conditions:
   - the margin is taken from W_max, computed from the worst of ≥ 10 restore runs plus the pre-registered realised-work ratio;
   - the margin's SE cost is reported at each gated scene and in layouts 4/5;
   - a margin above about 20 % of W_max returns to the seats;
   - the gate runs on the Release build;
   - a gate failure is a defect: no re-run, no W_max cut after pinning, no room-range narrowing and no formulation seam;
   - **any** gate failure is remedied by bringing (C) forward (8 (b));
   - **if the non-diffuse build alone leaves W_max below Seat 1's floor at a gated scene, the result goes to Maisara before any range change** (Seat 6 (a); 8 (a));
   - from Phase 08 on, the gate measures the heaviest output mode, and W_max stays one constant.
2. **AX41**, the W_max basis: (A) = restore budget less D-H1's margin, pinned, and re-derived once under (C) from the background budget. Q2a, Challenge 1 and Q2b are recorded as **board answers** (files 43, 47 and this addendum), replacing the orchestrator's statement. This closes steward G1.
3. **phase-05h:**
   - §3 D-H1 gets the margin rule and the 20 % trigger, with the expected margin of about 27 % noted;
   - §4 gets the single-function solve seam (Seat 5).
4. **The new (C) phase**, suggested name `phase-07c.md`, "asynchronous diffuse solve":
   - conditions (iii) 1–8;
   - before the Phase 13 beta, and ahead of Phase 08's golden freeze if the gate fails;
   - **inputs to its decision loop:**
     - Seat 1's ruling on the size of the provisional-to-final step, which Seat 6 (d) and (iii) 5 depend on (8 (d));
     - the interim-level design and saved E_b (a state-version AX if E_b is stored);
     - Seat 8's question of whether the solved result can travel in the saved state, a feasibility call for Seat 5;
   - **cross-reference:** condition (iii) 4 (atomic swap; the ISM never held behind the diffuse solve) to phase-10's split update and AX38 (v) (8 (e)).
5. **phase-08:** the gate measures the heaviest mode; W_max is one constant; capped-room goldens carry an SE-derived tolerance unless (C) has landed.
6. **phase-11:** U's note reaches the producer's editor, not only the diagnostics. Seat 8's later 1 depends on it (AX44).
7. **phase-12:** the (ii) preset check is re-run under (C)'s W_max. Hall presets are checked for capped-class membership at the final W_max (Seat 9), rooms near 100 m included (L5).
8. **phase-13:** (C) is a prerequisite for the beta; otherwise the estimator parameters are versioned in saved state.
9. **Researcher (8 (c)):**
   - how long hosts tolerate a blocked `setStateInformation` (Seat 5);
   - which hosts do not signal offline rendering reliably (Seat 5);
   - host hang dialogs and their timeouts in Logic, Live, Cubase and Bitwig (Seat 7).
10. **Ledger:** rows P05B2-C1Q2-01…14, with this addendum's answers. S1, S3, S4 and S8 confirmations recorded. Seat 5's offline-only (B) recorded as not adopted.

## 5. Bookkeeping (correction 9)
- The † on J1's S4 cell is removed.
- J1 still reads S2, S6 and S7 from conditions (†). That is three cells, each of whose conditions are in §4 (i)/(iii).
- S1, S3, S4 and S8 are confirmed by the seats.

## 6. Final summary

| id | decision | state | worst-off (cell) | sum | conf. | bound | basis | reversal |
|---|---|---|---|---|---|---|---|---|
| Q2b | (i) n\*_max 1 024 | SURVIVES (file 49) | S1 2/2 (rests on W_max, not on n\*_max) | 19 (21 for (ii)) | medium | AQ10 (lifted) | C14 (b), C16 (f) | C++ n\*_max < 1 000; an E_b refresh AX |
| Challenge 1 + Q2a | J1: blocking restore gate; W_max (A) less D-H1's margin; (C) scheduled before the first public release, with conditions (i)–(iii) | SURVIVES WITH CORRECTIONS (applied here) | S1 2/1 | 19 (J2 21) | medium (three † cells) | AQ10/AX36 (lifted); PRD NFR-2, NFR-6 | C14 (c), C16 (f)/(g), C17, C18, D-H1 | margin > 20 % back to the seats; a gate failure brings (C) forward; W_max below Seat 1's floor goes to Maisara; (C) slips past release without versioning |

## For Maisara (corrected line)
The board's answers:
- the 100 m restore gate blocks in CI;
- the big-room work limit is sized to it for now;
- a dedicated phase before the first public release moves that work off project load.

**What this means for rooms:**
- 20 × 30 × 10 m halls with an audience floor and s ≤ 0.5 are not capped (four rooms measured, C18).
- Rooms near 100 m are capped, at an error of SE ≤ 0.15 dB with no note shown (C16 (f)).
- The rooms that keep about ±0.13–1.33 dB of error until that phase are the extreme synthetic ones: an absorbing floor or wall with fully diffuse walls, and a low-absorption 100 m cube at s = 1.

**Expect this to come back:** the safety margin on the restore gate will probably exceed the seats' 20 % trigger and return to them once the C++ measurements exist. If it would push accuracy below Seat 1's floor, it comes to you.

No veto override is needed.

Files:
- /home/user/makroof/docs/review/phase-05b2/49-interrogator-board-answers-C1-Q2.md
- /home/user/makroof/docs/review/phase-05b2/50-seat1-confirm-J1.md
- /home/user/makroof/docs/review/phase-05b2/50-seat8-confirm-J1.md
- /home/user/makroof/docs/review/phase-05b2/48-seat3-confirm-S3c.md
- /home/user/makroof/docs/review/phase-05b2/48-seat4-confirm-S4c.md
- /home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md
