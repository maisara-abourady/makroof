# 42: Seat 9 on the fallback band, AX44's tau and its debt row (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (M3-H, follow-up on file 41 Q2, Q3, Q5. Read-only: I changed no files. The orchestrator saves this as /home/user/makroof/docs/review/phase-07c-2b/42-seat9.md.)

**1. Reading.** Three points from file 41:
- what a fallback band (window k 76) may support;
- what 07e-b records when AX44's τ fires below the 1 dB breach line;
- what it really costs to repay "(a) flagged rather than fixed".

Cues: S8 (a quantity reported without its uncertainty band) and C1 step 4 (a difference inside the reference's spread is noise).

**I own Q2.** The fallback clause is mine: in 38-seat9 §2 I wrote "(a) alone may use a 1 dB threshold while the reference SE is ≤ 0.5 dB". SE is σ, not 3σ, so the clause is wrong as I wrote it.

**2. Exact texts**

**Q2. Put this in 07e-b scope 1, the (a) block, as a new verdict (iv). Fix it before (a0) runs.**
> "(iv) A band on phase-07e's SE fallback (window k ≥ 76, 3σ up to 1.49 dB per radius) supports only a breach, never 'not breached'. It rules 'breached' when, at both radii, |engine − (a0)| > 1 dB + 3σ of that radius (about 2.5 dB at k 76), and both radii agree within their combined 3σ. Otherwise the band is 'not decidable'. 'Not breached' for (a) is stated only over bands gated at k ≥ 684, and only when every such band is within 1 dB. If no band is gated at k ≥ 684 and no fallback band rules a breach, (a) is 'not decidable' (verdict iii)."

Two consequent edits:
- **07e cap clause (Item A1).** After "and the record says so", add: "such a band supports only a breach (phase-07e-b scope 1 (iv))".
- **07e-b hand-offs.** Remove Seat 1's item "what a band counted 'SE ≤ 0.5 dB only' may be claimed as". The text above now answers it.

**Q3. Put this in 07e-b scope 1, the "On a breach" block. It replaces "A breach against (a0) is the AX44 reversal firing".**
> "AX44's reversal (L167: 'the near-corner reference contradicts NW-4C by more than τ'; τ = 0.25 dB per case and band, AX42 L165) is recorded for every counted band of (a), in one of three states:
> - 'fired': |engine − (a0)| − 3σ > τ (above about 0.75 dB at k ≥ 684; about 1.74 dB at k 76);
> - 'not resolved at τ': |d| > τ but not fired;
> - 'within τ': |d| ≤ τ, recorded with its 3σ and never read as confirming NW-4C.
>
> Every breach also fires the reversal. The reversal can also fire with every band within 1 dB.
>
> If the reversal fires and (a) is not breached, (a) is ruled 'not breached'. AX44 then goes back to the board as its own decision, which is that reversal. Any amendment it yields is a FOR MAISARA answer with the AMENDS line. On its own, a fired reversal opens no gate and holds none. If that board orders a `src/sim` change before 08-4, scope 2 applies. The fired reversal is listed under 'Decided for Maisara'."

Why it holds no gate, by my criteria: a difference of 1 dB or less is within 1 JND of G (Vorländer Table 6.1, cited in AX42). So I see no audible case for holding item 15's stimuli. Whether to hold gates anyway is Seat 5's and Seat 7's call.

M3-H-R1 reasoning 1 should therefore read "its reversal asks for that check, at τ", not "A breach … is the reversal firing".

**Q5. My restated debt row**
- **What it commits:** (a) may end up flagged rather than fixed. That is about 6 JND of G, reachable by a drag, and contained by U, by the Phase 11 note and by the record-path rule of no preset within 0.70 m.
- **What undoing costs:**
  - The fix is B15: a measured both-near fallback with p95 ≤ 1 dB (L408). That is a `src/sim` change.
  - It needs one golden round. The D5 golden pins U and the five flags of every valid fixture (L167), so it is regenerated with a CHANGELOG reason.
  - If the output changes, M3-8 fires (rebuild and reseal both ABX scenes) and 07e's JSON is re-pinned. Roughly one phase [Hyp, size].
  - My "a parameter change" fits only the 0.70 m threshold. Moving it changes who gets flagged, not the level they hear.
- **Evidence arrives:** 07e-b's ruling; the p95 that B15 measures.
- **Repaid when:** B15 gets an owner phase before 12-2 (FOR MAISARA), or (a) is fixed.

**3–4. Ratings on the adopted texts (now / later)**

| option | as adopted | with the Q2 text |
|---|---|---|
| H4+G | 2 / 2 | 0 / 1 |
| H3+G | 2 / 2 | 0 / 1 |

- **Why 2 as adopted.** A fallback band can clear (a) with a reference uncertainty of 1.49 dB, which is above one JND of G. That breaks criteria 2 and 4. Later: a false "not breached" would carry through 08-3 and 12-2. Undoing it would take an (a0) rerun at a higher N, a re-ruling and possibly M3-8.
- **The Q3 text does not move my cell:** the band in question is within 1 dB.
- **Why later stays 1 even with the larger undo cost.** The debt is already accepted under AX44, and it has a named route: the inside-debt FOR MAISARA answer. It rises to 2 if B15 has no owner by 12-2 and any preset default sits within 0.70 m of a layout-4/5 corner.
- **(a2) as a reference for its own placement.** I accept it at 0 now. Its sphere (radius 0.5 m, centred 0.75 m from each face) lies wholly inside the room, so it is the same kind of reference as (c)'s. It must never be a reference for (a).
  - Small condition: verdict (ii) should also compare each emitter's late level, as (i) does, not L − R alone.
  - One radius is enough there [Hyp].
- **My row still does not separate the two homes** (29-seat9 §2).

**5. Evidence**
- σ = 4.34/√k (tracer.py L28; Vorländer §11.2.5 Eq. 11.9, as read in file 41; I did not open the corpus this round). I redid the arithmetic:
  - at k 76: σ = 0.498 dB, 3σ = 1.49 dB; combined for two radii, 3·√2·0.498 = 2.11 dB;
  - at k 684: σ = 0.166 dB, 3σ = 0.50 dB;
  - breach line on a fallback band: 1 + 1.49 = 2.49 dB;
  - reversal lines: 0.25 + 0.50 = 0.75 dB gated, and 0.25 + 1.49 = 1.74 dB on the fallback.
- JND of G is 1 dB (AX42's citation of Vorländer Table 6.1).
- (a0) at k 684 does not meet AX43's N rule (z_FW·SE ≤ τ − ℓ_ref: 4.29·0.166 = 0.71 dB). So "fired" means a 3σ resolution, not AX43 precision. The record should say so.

**6. Conditions.** Adopting the Q2 text lowers my cells from 2/2 to 0/1. For later 1 → 0: B15 gets an owner phase before 12-2.

**7. Hand-offs.**
- Seats 5 and 7: whether a fired reversal holds any gate.
- Seats 2 and 5: Q4 (B11's doubling rule against (a0)). Not my matter.
- Seat 1: none left on the fallback.

**8. Premortem.** If a fallback band clears (a), a GA-real deficit of about 1.5 dB inside the reference's own uncertainty is shipped as "correct". The first to notice would be a producer dragging a source into a corner, or Seat 1's ABX at 08-3.
