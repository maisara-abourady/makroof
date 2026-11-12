# 35 — Decider: G3 / D1 decision round 2 (answer to interrogator file 34): DECISION O8 stands

2026-11-12, corpus c1b171f. Measured since file 33 (8d72d7f, Linux): 30 of 40 cases with d < 0.5 within 5 % (worst
−3.53 %, cube 96 kHz seed 1 1 kHz); layout 4 out (10); worst prefix difference −55.3 dB (bound −18.27 dB).

Own correction to file 33: sums were wrong (cells right): O2 19, O3 18, O4 16, O5 18, O7 10, O8 11; ordering unchanged.

| option | S1 (28) | S2 (29) | S3 (30) | S5 (27) | S7 (26) | S9 (31) | max | sum |
|---|---|---|---|---|---|---|---|---|
| O1 | out (P07C1-G3-01) | | | | | | | |
| O2 | 2/2 | 2/2 | 1/2 | 1/2 | 1/2 | 1/1 | 2 | 19 |
| O3 | 2/1 | 1/2 | 1/2 | 1/1 | 2/1 | 2/2 | 2 | 18 |
| O4 | 1/1 | 2/2 | 1/2 | 0/1 | 1/1 | 2/2 | 2 | 16 |
| O5 | 1/1 | 2/2 | 2/1 | 1/2 | 2/2 | 1/1 | 2 | 18 |
| O6 | 2/2 | 2/2 | 2/2 | 2/1 | 2/2 | 3/3 | 3 | out (veto) |
| O7′ | not rated | 0/0 | not rated | not rated | not rated | not rated | n/a | n/a |
| O7 | 1/1 rc | 0/0 rc (C6) | 1/2 rc (no O5′) | 1/1 rc (O6 condition met; cube margin ≈ 1.5 points) | 1/1 rc (from its O4 clause "narrower but true claim; must be stated as a domain rule") | 0/1 | 2 | 10 |
| **O8** | 1/1 rc | 1/1 rc (C5; x from AX47's 1 dB) | 0/1 rc | 1/1 rc (margin 37 dB) | 1/1 rc | 1/1 rc | **1** | **11** |

Working: bounds drop O1; veto drops O6; O2–O5, O7 max 2; O8 composes O7 + O5′ (meets Seat 3's only 2) → max 1, sum 11 →
O8. If Seat 2 rated O5′ 2/2: O7 wins (max 2, sum 10).

**AX47 (b) replacement (final):** "Asserted on the A4 set (several seeds, 48 and 96 kHz): the step ≤ 1 dB per emitter in
every band, both windows; a prefix check, identity up to the AX47 (b) step gain: E(provisional − exact)/E(exact) ≤ −18.27 dB
(= 20·log10(10^(1/20) − 1), the difference a +1 dB step of the provisional gives; −1 dB gives −19.27 dB) per emitter and
band on the shipped IRs over [t_mix,e, L_f − h), h the noise generator's filter half-length plus the analysis filterbank's,
between two renders of one scene and seed (never against a measured IR); and EDT (ISO 3382-1 A.2.1, as
`tools/acoustics/metrics.py` takes it) within 5 % at 500 and 1000 Hz on the whole IR (emitter 0) against the exact IR, in
every case whose exact band IR has a direct fraction d < 0.5 (d: energy within ±5 ms of the band peak over the band's total;
d = 0.5 is Kuttruff Eq. 5.44's w_d = w_r, the mapping to the measured window a project choice fixed before any comparison).
Cases with d ≥ 0.5 lie outside EDT's domain (Kuttruff §8.4: the direct sound unduly shapes the decay curve) and print 'not
evaluated (outside EDT domain: direct-dominated, d = …)' with the exact and provisional EDT and that band's steps in both
windows; no EDT deviation from them enters the count or the worst figure. Each case also prints whether d < 0.217 (ISO
3382-2's d_min ≈ 1.9 r_c in diffuse-field terms) holds, for Phase 10. At least one case is evaluated at each of 500 Hz and
1 kHz (a non-vacuity check, not a quota). The record reads "EDT within 5 % on N cases with d < 0.5 of M"; it is a
provisional-against-exact self-comparison, not a perceptual claim."

Evidence append and §6 row: as in the decider's report (files 22, 32–35; 33 → 30 asserted; 8d72d7f figures).
Test change beyond 8d72d7f: print `d < 0.217: yes/no` per EDT case; summary wording "on N cases with d < 0.5 of M".

Future-debt register: S1/S9 — d < 0.5 instead of "r ≫ r_c" (K7 closed with no number); undo one constant (d < 0.217
asserts only 5 of 40, layout 5); evidence: the d < 0.217 subset printed every run, the 07c-2 self-ABX, Phase 10 BRAS
positions; repaid when Phase 10's loop rules the constant on the BRAS EDT position scatter. S2 — the prefix check never a
measured-vs-simulated criterion (scoped in the text); repaid when Phase 10 cites AX47 (b) without applying it to measured
IRs. S3 — guards the A4 set only; 07c-2, 08, 09 keep it green on their own sources. S5 — cube margin 1.47 points;
three-OS figures from CI; a red is a regression, never a threshold move. S7 — wording "on N cases with d < 0.5 of M",
never "EDT within jnd"; checked at the phase-13 review.

Strongest objection: Seat 9's later cell with the ISO 3382-2 point (CR3 asserted below d_min ≈ 1.9 r_c; T-only) — makes
the S1/S9 debt real, not the winner; Seat 2's O5′ cell.

Decided for Maisara: D1 — the interim-tail test checks EDT only where the reference IR is not direct-dominated (d < 0.5) and
adds a check that the interim tail's opening matches the final tail's on the shipped IR. PRD check: NFR-8, FR-SIM-2 (no
scene logic; test-side case choice on a measured property of the reference IR), AX5, NFR-1 (thresholds unchanged; d < 0.5
decides where a self-comparison applies, not a pass threshold). O2 strains NFR-1's evidence (24–98 s EDTs as passes); O3
measures another quantity; O4 strains FR-SIM-2's spirit and drops the cube; O5 unsourced threshold; O7 one check fewer; O8
passes all. Who gave most: Seats 1 and 9 (d < 0.5 instead of r ≫ r_c), repaid by the printed d < 0.217 partition and
Phase 10's ruling; Seat 2 accepts the prefix check scoped to self-comparison. Amends none of her decisions. NEEDS MAISARA:
none.
