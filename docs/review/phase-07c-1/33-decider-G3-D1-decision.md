# 33 — Decider: G3 / D1 decision round (phase 07c-1 session 2): DECISION O8

2026-11-12, corpus c1b171f. Inputs: files 21–32.

**Decision O8 = O7 + O5′.** AX47 (b) asserts EDT only where the exact band IR's direct fraction d < 0.5 (Kuttruff Eq. 5.44
w_d = w_r on the measured field; §8.4); d ≥ 0.5 → "not evaluated (outside EDT domain: direct-dominated, d = …)" with exact
and provisional EDT and both windows' steps, not counted; the ±0.06 dB probe and the "half" floor dropped; at least one
evaluated case at each of 500 Hz and 1 kHz (non-vacuity); added the prefix identity E(prov − exact)/E(exact) ≤ −18.27 dB
(= 20·log10(10^(1/20) − 1)) per emitter and band on the shipped IRs over [t_mix,e, L_f − h). AX49 "Acceptance" and A4
unchanged. Confidence medium.

Tension map (now/later; seats 4, 6, 8 not required): O2 max 2 sum 22; O3 2/20; O4 2/17; O5 2/20; O6 out (Seat 9 3/3);
O7 2/9 (Seat 3 later 2: no stream check); O7′ not rated by four seats (same partition as O7); **O8 max 1, sum 11** (cells
read from the seats' conditions marked rc: S1 1/1, S2 1/1 rc, S3 0/1 rc, S5 1/1 rc, S7 1/1 rc, S9 1/1 rc).

Replacement text for AX47 (b) "Asserted per band on the A4 set (several seeds, 48 and 96 kHz): both windows; EDT within 5 %
at 500 and 1000 Hz on the whole IR against the exact IR.":
> Asserted on the A4 set (several seeds, 48 and 96 kHz): the step ≤ 1 dB per emitter in every band, both windows; the prefix
> identity E(provisional − exact)/E(exact) ≤ −18.27 dB (= 20·log10(10^(1/20) − 1), the difference a pure 1 dB gain step
> gives) per emitter and band on the shipped IRs over [t_mix,e, L_f − h), h the noise generator's filter half-length plus the
> analysis filterbank's; and EDT (ISO 3382-1 A.2.1, as `tools/acoustics/metrics.py` takes it) within 5 % at 500 and 1000 Hz
> on the whole IR (emitter 0) against the exact IR, in every case whose exact band IR has a direct fraction d < 0.5 (d: energy
> within ±5 ms of the band peak over the band's total; d = 0.5 is Kuttruff Eq. 5.44's w_d = w_r applied to the measured field,
> fixed before any comparison). Cases with d ≥ 0.5 lie outside EDT's domain (Kuttruff §8.4: the direct sound unduly shapes
> the decay curve); they print 'not evaluated (outside EDT domain: direct-dominated, d = …)' with the exact and provisional
> EDT and that band's steps in both windows, are not counted as evaluated, and no EDT figure is reported from them. At least
> one case is evaluated at each of 500 Hz and 1 kHz (a non-vacuity check, not a quota). The record reads "EDT within 5 % on N
> in-domain cases of M". This is a provisional-against-exact self-comparison, not a perceptual claim.

Evidence column append: "D1 (steward G3, phase-07c-1 session 2): Kuttruff §5.6 Eqs. 5.44–5.45, §8.4; researcher file 32 F2,
F4 (no numeric EDT distance rule); files 23, 25 (d, r/r_c per case); seats files 26–31; the O2 conditioning probe (±0.06 dB)
and the 'half' floor are dropped (interrogator file 22, G3-04, -05, -06, -08)."

§6 row: as in the decider's report (EDT asserted where d < 0.5; layout 4 out; probe and floor dropped; prefix identity
added; 1 dB, 5 % and the reversal unchanged; expected 30 of 40 in domain, worst 3.53 %).

Load-bearing: D1-L1 Eq. 5.44 / 5.45 (d = 0.5 at r_c; the measured-field threshold a project choice); D1-L2 §8.4; D1-L3 layout
4 d 0.833–0.900, others ≤ 0.379: the partition is the same for any d_max in 0.38–0.83 (not fitted; the rule judges the
reference IR only; moves two cube cases into assertion and removes three degenerate passes: not a loosening); D1-L4 x
arithmetic (stream mismatch +3.01 dB); D1-L5 the level steps never see the shipped IR; D1-L6 NFR-8 / FR-SIM-2 hold.
Future debt: S1 d < 0.5 weaker than r ≫ r_c (one constant; K7 source or the 07c-2 ABX); S3 O5′ must hold for 07c-2 and
08/09; S5 cube margin ≈ 1.5 points; S7 in-domain wording only; S9 R1 may tighten to ≈ 2 r_c (phase 10).
Strongest objection: Seat 2's O5′ cell read as 1/1 (x derived from AX47's 1 dB); if 2/2, O7 alone wins (max 2 sum 9).
Reversal: an EDT-bias source against d; Seat 2 rating O5′ 2.
Decided for Maisara: D1 (EDT checked only where the reference IR is not direct-dominated; a prefix-identity check added; no
hard constraint broken; amends none of her decisions). NEEDS MAISARA: none.
