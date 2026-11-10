# Interrogator — decision mode on the board's answers to Challenge 1, Q2a and Q2b (files 43, 47)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, decision mode: the board's answers to Challenge 1, Q2a and Q2b (files 43 and 47)

Both stand. The Q2b answer in file 43 needs no corrections. File 47 (Challenge 1 = yes, Q2a (A) now, (C) scheduled) needs nine corrections, none of which changes the winner: J1 beats J2 under every reading of the cells.

Two corrections must be made before the record replaces the orchestrator's statement to Maisara (steward G1):
- **Item 6:** "realistic halls are not affected" is not supported for rooms near 100 m.
- **Item 7:** Seat 5's own arithmetic already puts the D-H1 margin past Seat 3's 20 % trigger, and that risk is not registered.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:** files 43, 47; 45-seat1…9; 48-S3c and 48-S4c; C17, C18; C14 (c); C16 (f) and (g); phase-05h §3.

### Verdicts

| record | verdict |
|---|---|
| **43, Q2b = (i), n\*_max 1 024** | **SURVIVES.** Cells match 34/37/30-S4a/35-S6b. Sum 19 against 21 (S4 1/1 against 2/2). Seat 6's preference correctly treated as no cell difference. |
| 43, Challenge 1 / Q2a "not decidable" | **Correct process.** Eight cells were missing and (B)/(C) were unrated; the 4c-2 cells were correctly not reused. |
| **47, J1: Challenge 1 yes + Q2a (A) now + (C) scheduled** | **SURVIVES WITH CORRECTIONS** (items 1–9). Items 6 and 7 must be fixed before the record goes forward; the rest can be applied by /fix-plan. |

### Checks that pass
- **Convening.** All nine seats rated R1–R3. Seat 5 restated R1.
- **Per-question cells.** Every cell in 47 §2's per-question table matches the seat's own words:
  - S1: yes 1/1 with (C) and 1/2 without; no 1/1; (A) 2/2, and 2/1 with (C); (B) 1/1; (C) 0/1; not scheduled 1/2.
  - S2: yes 1/2, 1/1 under its no-cut condition; no 1/1; (A) 1/1 (raised on C16 (g)); (B) 0/1; (C) 0/1; not scheduled 1/2.
  - S3: yes and no each 1/1 with (C), 1/2 without; (A) 1/2 as corrected; (B) 2/2; (C) 1/1; not scheduled 1/2.
  - S4: yes 0/2, 0/1 under its conditions; no 0/1; (B) 2/1; (C) 0/1; not scheduled 1/1.
  - S5: yes 1/1; no 1/2; (B) 2/3; (C) 1/1; not scheduled 1/2.
  - S6: yes 1/1 under (a), 1/2 without; no 1/1; (B) 2/2; (C) 1/1; not scheduled 1/2.
  - S7: yes 1/1; no 1/2; (B) 2/2; (C) 1/1; not scheduled 0/2.
  - S8: yes 1/1 with (C), later 2 without; no 1/1; (B) 1/2; (C) 0/1; not scheduled 1/2.
  - S9: yes 1/1 with (C), 1/2 without; no 0/1; (A) 1/2 unless (C); (B) 1/1; (C) 0/1; not scheduled 1/2.
- **The corrections Seats 3 and 9 made** to their (A) cells (1/2) are faithfully taken.
- **Veto handling.** J5 is dropped on bounds (restores 2.16–4.83 s, C14 (c)) and on Seat 5's (B) later 3. Seat 5's offline-only (B) is correctly not composed: it is unrated by Seats 1, 6 and 8, the seats that carry its cost, and it cannot lower Seat 1's real-time 2.
- **Load-bearing claims.** L1 (C14 (c)), L2 (D-H1: 29.98 s; about 30.2 s at ratio 1.05), L4 (C17: layout 4 one-end SE 0.09–0.22 dB; layout 5 fails on pilot VOV 0.13–0.46, not on SE; both-near still fails) and L6 are CORRECT.
- **Confirmations.** S3-c: Seat 3's (A) cell goes to 1/1 with (iii) 1–8. S4-c: "yes" stays 0/1, and its † can be removed.

### Corrections

1. **Fold in S3-c and S4-c.** With S3 at 1/1, **J1 = 19** and **J2 = 20**.
2. **S1's J1 cell: the decider broke its own rule.**
   - 47 §2 says to use "the seat's composite rating where it gave one".
   - Seat 1 gave a composite for exactly J1, "yes + (A) with D-H1's margin + (C) scheduled", at **1/1**. Its Q2a (A) cell under (C) is **2/1** ("the 'now' 2 stands until that phase ships").
   - The decider took the worse cell without saying the two conflict.
   - State the conflict, or ask Seat 1 in one line. If it is 1/1, J1's maximum is 1 (with S3-c), not 2. The winner is unchanged either way.
3. **S8's J1 cell is unmarked but rests on a condition.**
   - Seat 8's later 1 on "yes" requires (C) scheduled **and** "U's 'approximate' note reaches the producer in capped halls".
   - Under (A), U is silent in the capped closed 100 m cubes (SE 0.09–0.15 dB at n\*_max 1 024) and the capped absorbing-floor cube (0.09–0.10 dB), because U needs cap AND SE > 0.33 dB (C16 (f)).
   - So the condition is met only where SE > 0.33 dB. Mark the cell † and ask Seat 8. Until it answers, read later 2: **J1 = 20**.
4. **J2's S7 cell is read from conditions that J2 does not contain.** A cell read from conditions must belong to the variant rated. J2 does not include Seat 7's "no" conditions (restore record compared run to run as a finding; no W_max change without a board round). So S7 is **1/2**, and **J2 = 21**.
   - Across corrections 1–4, J1 is 19–20 and J2 is 21. J1 wins on sum and the ordering holds.
   - Without this correction, J1 at 20 and J2 at 20 would tie and fall to reversibility.
5. **L3 figures are stale.** The plan (AX41, after file 41) already uses the n\*_max 1 024 values; L3 does not:
   - layouts 4/5 at s = 1 under (A) are 0.13–1.33 dB, not 0.29–1.33 (layout 5 listener_wall 0.131 dB);
   - the low-α s = 1 cube is 0.44–0.50 dB; 0.51–0.67 is the 8 000 figure.

   Update L3 and the register's S1 row.
6. **L5 overreaches (INCONSISTENT with C16; fix before the record goes forward).**
   - "The capped class is the synthetic s = 1 long-window layouts" is false at 100 m: the closed 100 m cubes at s = 0.3 and the absorbing-floor cube are capped under (A), at SE 0.09–0.15 dB with U silent (C16 (f)).
   - C18 measured four 20 × 30 × 10 m halls only.
   - "For Maisara: realistic halls with audience floors are not affected (C18)" should read: "20 × 30 × 10 m halls with an audience floor and s ≤ 0.5 are not capped (four rooms, C18); rooms near 100 m are capped at SE ≤ 0.15 dB (C16 (f))."
7. **Risk missing from the register and the strongest objection (fix before the record goes forward).**
   - Seat 5 (R1) computes that a 3 % build spread is 0.057 s, which is 22 % of the 0.259 s diffuse budget. With the ≈ 1.05 realised-work ratio, the margin comes to ≈ 27 % of W_max.
   - That is already above Seat 3's ≈ 20 % trigger, so D-H1 is likely to return to the seats.
   - Record it: register row (S3/S5) and strongest objection.
8. **§5 plan list is incomplete.**
   - **(a)** AQ10 / AX38 4c omits Seat 6 (a)'s escalation: "if the non-diffuse build alone leaves W_max below Seat 1's floor at a gated scene, the result goes to Maisara before any range change". The decision (i) has it; §5.1 does not.
   - **(b)** "A gate failure brings (C) forward" is listed only for Phase 08. Decision (i) makes it the remedy for any gate failure.
   - **(c)** The open research questions are not routed to the researcher:
     - Seat 5: host tolerance of a blocked `setStateInformation`; hosts that do not signal offline rendering reliably;
     - Seat 7: host hang dialogs and their timeouts.
   - **(d)** Seat 1's ruling on the provisional-to-final step size, which Seat 6 (d) and (iii) 5 depend on, is not listed as an input to the (C) phase's decision loop.
   - **(e)** (iii) 4 (atomic swap, the ISM never held behind the diffuse solve) needs a cross-reference to phase-10's split update / AX38 (v).
9. **Bookkeeping.**
   - Remove the † on J1's S4 cell (S4-c confirmed it).
   - The "Confidence: four cells read from conditions" count changes with items 2–4.
   - After items 1–4, J1 still has † cells for S2, S6, S7 and, pending item 3, S8.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-C1Q2-01 | 43 Q2b = (i) n\*_max 1 024: cells, sums 19/21, preference handling | SURVIVES | closed |
| P05B2-C1Q2-02 | 43: Challenge 1 / Q2a not decidable on recorded cells; 4c-2 cells not reused | correct process | closed |
| P05B2-C1Q2-03 | R1–R3 convening (9/9) and per-question cells in 47 §2 | faithful | closed |
| P05B2-C1Q2-04 | J5 dropped (bounds, S5 later 3); offline-only (B) not composed | CORRECT | closed |
| P05B2-C1Q2-05 | S3-c (A) 1/1 and S4-c 0/1 folded: J1 19, J2 20 | correction | open |
| P05B2-C1Q2-06 | S1 J1 cell: own composite 1/1 vs (A)-with-(C) 2/1; worse taken against the stated rule | IMPRECISE (state, or ask Seat 1) | open |
| P05B2-C1Q2-07 | S8 J1 cell rests on "U reaches the producer in capped halls"; U silent in capped 100 m cubes (SE ≤ 0.15 dB) | TENSION MISREAD (unmarked †; winner unchanged) | open |
| P05B2-C1Q2-08 | J2 S7 cell read from conditions not in J2 (should be 1/2; J2 21) | TENSION MISREAD (winner unchanged; prevents a tie) | open |
| P05B2-C1Q2-09 | L1, L2, L4, L6 | CORRECT | closed |
| P05B2-C1Q2-10 | L3 stale figures (0.29–1.33 → 0.13–1.33; low-α 0.44–0.50 at 1 024) | IMPRECISE | open |
| P05B2-C1Q2-11 | L5 / For Maisara: "capped class = synthetic s = 1 layouts"; "realistic halls not affected" (100 m cubes capped, SE 0.09–0.15 dB; C18 is four 20 × 30 × 10 m rooms) | INCONSISTENT: fix before the record goes forward | open |
| P05B2-C1Q2-12 | Seat 5's margin arithmetic (≈ 22 % + 5 %) already above Seat 3's 20 % trigger; not registered | debt not registered: fix before the record goes forward | open |
| P05B2-C1Q2-13 | §5 plan list gaps (Seat 6 (a) escalation; (C) forward on any gate failure; research questions of Seats 5 and 7; Seat 1's step-size ruling; phase-10 cross-reference) | correction (/fix-plan) | open |
| P05B2-C1Q2-14 | 47 final verdict: J1 (Challenge 1 yes, Q2a (A) now, (C) scheduled before the first public release) | SURVIVES WITH CORRECTIONS (winner unchanged under every reading) | open until applied |

Files:
- /home/user/makroof/docs/review/phase-05b2/43-decider-board-answers-C1-Q2.md
- /home/user/makroof/docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md
- /home/user/makroof/docs/review/phase-05b2/45-seat1-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/45-seat5-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/45-seat7-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/45-seat8-R1-R3.md
- /home/user/makroof/docs/review/phase-05b2/48-seat3-confirm-S3c.md
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
- /home/user/makroof/docs/review/phase-05b2/46-orchestrator-C18.md
