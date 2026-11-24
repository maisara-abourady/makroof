# 8-seat9: Seat 9, R3 on M3-1 (a) tail-spread measure and the L4 label

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (round 3, M3-1 (a) and M3-L4). Read-only. The orchestrator saves this as /home/user/makroof/docs/review/phase-07c-2b/8-seat9.md.

**Short answer.** Read as worded, my condition fires on both_wall (+9.39 dB). I meant equal source power should give equal reverberant energy (Kuttruff Eq. 5.42). That measure is the energy integrated from each emitter's own onset, not the fixed late windows. Under the decider's handling as written, V1-W is now 1, later 2. With the two text changes and the print below, it is 1/1.

## 1. Reading
The question is which measure my tail-spread condition meant and whether it fires on both_wall. Cues: §17 "confusing the record's definition with the physics", and C2 "honest inputs". File 5 shows that the mechanism I assumed (a level offset) is absent, and that a different one is present (the onset).

## 2. Which measure, and does it fire?
- **What I meant.** My R2-1 wording, "each emitter's tail energy at the listener", rests on Kuttruff Eq. 5.42 (w_r = 4P/cA). That is a steady-state quantity: the reverberant energy the IR delivers, integrated, for a source of equal power. So the measure is the per-emitter energy integrated from each emitter's own t_mix,e. I agree with the interrogator here.
- **Does it fire on both_wall?** Yes, at **+9.39 dB**. The ABX programmes are noise and speech, so a listener hears integrated reverberant energy, not equal-time slices.
- **What file 5 shows.** The fixed windows [0.45, 0.65) s and [0.8, 1.0) s confirm the two decays coincide. They cannot see a spread caused by onset, and onset is the mechanism file 5 found.
- **My premise fell.** I had assumed a level offset. The real cause is the onset: L at 0.165 s (K20) against R at 0.380 s.
- **Correction to my own framing [Inf; M].** R's late onset is the larger departure from a room, not L's early one. Both per-emitter D/R values sit above the diffuse values: L by 10.8 dB (−7.7 against −18.5 dB), R by 20.2 dB (+5.2 against −15.0 dB). In a real room, reverberant energy fills in right after the direct sound. R's empty stretch of 321 ms after its direct sound costs more than L's 77.5 ms. All of this is indicative at ᾱ ≈ 0.28 (Kuttruff §5.6).
  - So the share of 0.667 is not "inflated". It depends on the engine's t_mix,e rule, which can move either way.
  - If L moves back to 0.380 s, the share falls to about 0.29 (ΔG ≈ 0.28 dB). If R moves to its K20 onset, the share rises.

## 3–4. Tension now and later, V1-W

| handling | now | later | why |
|---|---|---|---|
| Decider's, as written (equal-window print, onset stated, M3-8) | 1 | **2** | (a) The seal print for the fallbacks uses fixed windows, which miss a spread caused by onset (the interrogator's CONDITIONS VIOLATED); a fallback could be sealed with an unlabelled spread of 9 dB. (b) The label's "agree within 0.05 dB" reads as "no spread" for steady programmes. Undoing it later means relabelling and rescoping a null on the record. |
| With the conditions below | 1 | **1** | The mechanism is stated as engine behaviour, the print can see it, and M3-8 covers a rule change. |

## 5. Evidence
- File 5, table L14–22 and fact 1: code measurement.
- Kuttruff Eq. 5.42 (L2698) and the §5.6 caveat (L2724): corpus.
- The gap-energy reasoning is [Inf].
- Vorländer Table 6.1's 1 dB jnd is for G (total energy). Here I use 1 dB only as a print threshold, not as an audibility claim [Inf].

## 6. Conditions of acceptance (later 2 → 1)

**C-a. S-W label.** Replace the sentence that begins "Tail onsets t_mix,e 0.165 / 0.380 s; at equal times…" with:

> "Tail onsets t_mix,e 0.165 / 0.380 s (L / R; the engine's t_mix,e rule). The decays agree within 0.05 dB at equal times, but from its own onset L's 1 kHz tail energy is +9.4 dB over R's at equal source power, where a diffuse room gives equal reverberant levels (Kuttruff Eq. 5.42; indicative). This is engine behaviour, not room geometry; the tail share 0.667 at 1 kHz rests on it and changes with the t_mix,e rule (M3-8)."

**C-b. Seal print and SPREAD clause.** For S-W and every fallback, print L − R at 1 kHz on two measures:
- (i) integrated from each emitter's own t_mix,e to the end of the IR;
- (ii) file 5's equal windows.

The SPREAD clause fires if either measure exceeds 1 dB, and it comes in two forms:
- **Onset form:** the C-a text with the fallback's own values.
- **Level form:** my R2-2 text.

In either form, the measurement goes to Seat 2 as an NFR-8 candidate. Which onset is the departure is Seat 2's call.

**Item 13.** The record line reads:
> "tail share 0.667 at 1 kHz, resting on the engine's t_mix,e onsets 0.165 / 0.380 s (own-onset tail L − R +9.4 dB; −0.05 dB at equal times)".

## 7. L4 label
The builder's draft is close. Add the positions, the T60 above 1 kHz, the D/R reference, the fade window and the seed:

> "ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10⁶ m³, every face the same α per band, scattering 0.3. Listener (50, 30, 1.7) m; emitters (45, 70, 2) and (55, 70, 2) m, each 40.3 m from the listener. T60 8.0 ± 0.1 s from 63 Hz to 1 kHz as printed by the engine (T60_max 8 s, air absorption included), shorter above 1 kHz where α is held at its 1 kHz value; per-band T60 printed. D/R at 1 kHz {printed} dB heard, against about −6.1 dB in a diffuse field at r/r_c 2.0 (r_c ≈ 20 m from A ≈ 20,100 m² including air, Sabine; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.34 is not small, §5.6). A stress geometry for AX49's provisional tail, not a room prediction or a validated preset. A = AX49 provisional tail (Engine::assembleProvisional, validation-only flag --ax49-provisional), faded over [L_f, L_p) = [{L_f}, {L_p}) s; B = full engine tail ('exact' = full synthesis, not a measurement); one tailSeed {seed} for A and B. Fully wet: the whole rendered IR (direct, early part and tail), no dry path."

Working:
- A = 0.161 × 10⁶ / 8 = 20,125 m².
- r_c = (20,125/16π)^½ = 20.0 m. Eq. 5.44's approximate form gives 19.95 m.
- Distance to each emitter: √(25 + 1600 + 0.09) = 40.31 m.
- Diffuse D/R: 20·log10(19.95/40.31) = −6.1 dB.
- ᾱ ≤ 20,125/60,000 = 0.34. This is an upper bound, because air takes part of A.

If the fallback S is used, the same template applies with S's values. The label contains no "hall", "church", "cathedral" or "occupied". I confirm the filled text before the seal.

**L4 ratings.** L4-A stays 0/0. B′ is 0/0 on my criteria: it presents the cut, and the label is the same.

## 8. Hand-offs
- **Seat 2:** which of the two onsets (0.165 or 0.380 s) departs from the t_mix,e rule's intent. This is an NFR-8 candidate.
- **Seat 1:** whether a 9.4 dB per-emitter steady-state difference affects what the S-W null scopes.

## 9. Premortem
Suppose the fixed-window print stands. A fallback is then sealed with a spread caused by onset that nobody sees, and its null is recorded as a room-class result. The first to notice is the 08-3 rebuild after a t_mix,e change, when the scene's share moves.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/7-interrogator-on-file6.md
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md

