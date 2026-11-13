# 2 — Seat 9 position (D-B4 only), round 1

2026-11-13, corpus c1b171f. Saved by the orchestrator from the seat's report.

**Reading.** The AX49 reversal fired (8-instance load at the T60 8 s / 96 kHz record (h) scene: 6.2–10.2 s vs 5 s). Which
remedy changes the room heard? At that scene L_p 3.70 s, L 11.93 s (file 44 L292–293); the interim plays until every
instance settled (up to 12.0–12.1 s). Cues: right decay but wrong early decay (S2); a late change after commitment (§4, W1).

**Ranking.** Prefer (output-identical): C1, C2, C6, C4 (memory Seat 5's). Can live with: C7, C8. Under conditions: C5.
Cannot live with: C3 as tabled (it saves time only with a cap below t_mix + 0.312·T60_max). Added: **C3-pb**, a per-band
prefix L_p,b = t_mix,e,max + 0.312·T60_b + 0.1 s (allowed in 07c-1, "per band or at the longest T60", file 6): every band
within the EDT jnd, only short-T60 bands shortened (air absorption, high bands) — prefer, if Seats 3 and 5 find it saves time.

| option | now | later | reason / debt |
|---|---|---|---|
| C1, C2 | 0 | 0 | bit-identical |
| C4 | 0 | 0 | exact output |
| C6 | 0 | 0 | output-identical; interims longer, within the jnd by construction |
| C7 | 0 | 1 | defers to 07d, which lists C3; under schedule pressure the cheap output-changing fix is picked late (W1); evidence at 07d's loop |
| C8 | 0 | 1 | same debt, to Phase 13 under release pressure |
| C5 | 1 | 2 | changes the exact tail for good: every bounce, BRAS validation (report-phase05), later Phase 12 presets; undo = golden round + re-validation (+ preset re-validation after 12) |
| C3 (cap < 0.312·T60) | 2 | 3 | below |
| C3-pb | 0 | 1 | every band within 5 % EDT; debt: T60_b provenance must be the tail's built T60_b, air absorption included |

**Why C3 is 2 / 3 [Inf, H; arithmetic].** A cut leaves a = 10^(−D/10) of the tail energy (D = decay depth at the cut); the
Schroeder curve reaches −10 dB at a true decay of −10·log10(a + 0.1(1 − a)) dB, so EDT_cut/EDT ≈ that / 10. D = 18.7 dB
(today's rule): 0.950 = the 5 % jnd (this seat's condition, file 10 confirmed). At T60 8 s: a 2.0 s cap → D ≈ 13.5–14 dB,
EDT −14 % (≈ 3 jnd); 1.0 s → D ≈ 6.6 dB, EDT −47 % (≈ 9 jnd). Missing energy passes the 1 dB G jnd below ≈ 0.115·T60. At the
AQ4 handover the missing late energy arrives within 30 ms: the room swells by itself. Later, at 07d's corner (T60 50.5 s, L
12 s) a ≈ 3.7 s cap keeps 66 % of the 12 s tail's energy (−1.8 dB G, > 1 jnd), EDT far out; a cap adopted here sets the
precedent — veto-grade (07c-1 analogues D5 2/2, D1 3/3).

**Evidence.** jnds EDT 5 %, G 1 dB, C80 1 dB, LG 1 dB at 500–1000 Hz (Vorländer Table 6.1, checked); truncation Vorländer
§6.4.1 Eq. 6.4, K17′ (AX49), 07c-1 files 6, 10; scene figures file 44 L119–124, L278–304. C3 / C3-pb savings unknown [Hyp];
note: the prefix cost (289 ms at L_p 2.58 s, 96 kHz) may be dominated by the constructor rather than the length.

**Conditions.** C3 → 1/1: never below t_mix,e,max + 0.312·T60_b in any band (= C3-pb); otherwise acceptable only where it
leaves today's rule unchanged (0/0, saves nothing at the trigger scene); any fixed absolute cap independent of T60 stays 3.
C5 → 1/1: meets the phase-05 BRAS validation per band 125 Hz–4 kHz without getting worse; vs the current generator, exact-tail
EDT and T30 within 5 %, G, C80, LG within 1 dB on the A4 set and the gated scenes; lands before Phase 12 builds or validates
any FR-3D-3 preset. C7 / C8: the later 1 goes if the record states that 07d's C3 stays bound by the 0.312·T60_b rule.

**Hand-offs.** Seat 1 (depth; L4 detecting a capped interim; a 30 ms handover swell); Seat 3 (coloration under C5 and C3-pb;
C3-pb's cost — is the FFT size set by the longest band?); Seat 5 (cost of C1, C2, C3-pb, C4; C6 design); Seats 2, 7 (AQ10
"not optimised before Phase 13" for C5); a human (L4, any C5 listening).

**Premortem.** A fixed-cap C3: a hall or church project opens to a short dry room for 5–12 s that then swells; L4 catches it
first, producers complain; at 07d's 50 s corner a −1.8 dB, much shorter room.

Files read: file 1; BUILD_PLAN AX38, AX49; phase-07d; `docs/review/phase-07c-1/{3,6,10}-seat9*`; file 44;
`docs/corpus/vorlaender-auralization.md` (Table 6.1).
