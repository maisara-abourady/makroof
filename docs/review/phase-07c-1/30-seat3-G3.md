# 30 — Seat 3 (reverb renderer), G3 / D1 position (phase 07c-1 session 2)

2026-11-12. Code facts (test_interim.cpp): the level steps use the construction's own band split (unitDecays ×
bandsAmplitude), so a seed/stream mismatch (common-window step ≈ 0 dB by the √(E_p,b/f_b) normalisation) and an assembly
defect are invisible to them; only EDT looks at the shipped IR; nothing asserts the prefix identity (3.6e-5 measured only).

B3: a normalisation error ≥ 1 dB is caught by the level steps whatever the EDT option; EDT is a poor gain detector.
A stream mismatch: EDT sees it only sometimes (exact EDT varies between seeds ~6 % layout 5, ~15 % CR3, ~20 % cube 1 kHz),
never in layout 4; O3 no better.

Proposed **O5′** (alongside an EDT rule): per emitter and band over [t_mix,e, L_f) (stopping before L_f by the generator's
filter half-length, K2), assert E(provisional − exact)/E(exact) ≤ x = 20·log10(10^(1/20) − 1) = −18.27 dB (the difference a
pure 1 dB gain step produces: derived from AX47's own bound, not from results). A stream mismatch gives ≈ +3.0 dB: 21 dB gap.

Second O2 defect: layout-4 cases with 24–98 s EDTs count as evaluated. Proposed domain check: evaluate only where
EDT_exact ≤ T60_max (the longest band T60 of the tail) [Inferred: an EDC of decaying exponentials never decays slower than
the slowest; a shallower LS line comes only from fitting across the direct step, Kuttruff §8.4] — for the interrogator.

| option | now | later |
|---|---|---|
| O5′ + O2-fixed | 0 | 1 |
| O2 as drafted | 1 | 2 (07c-2 stage-1 sources and 08/09 per-output seeds bring stream-mismatch risks no check sees) |
| O3 | 1 | 2 |
| O4 | 1 | 2 (AX49 names scenes; every added scene needs /fix-plan) |
| O5 as stated | 2 | 1 |
| O6 | 2 | 2 (Eq. 5.44 diffuse assumption) |

Ranking: O5′ + O2-fixed prefer; O2-fixed; O5 (only with x as in O5′); O4; O3; O6 (rated 2).
Conditions: O2 → add O5′, the EDT_exact ≤ T60_max domain check (excluded not counted as evaluated), restate ±0.06 dB as a
conditioning probe (G3-05), print level steps (G3-08). O3/O4 → add O5′. O5 → x = −18.3 dB. O6 → only with a sourced k and
O5′. Floor: with O5′ not load-bearing; without it ≥ 1 evaluated case per band in ≥ 2 scenes after the domain check.
Premortem: an 08/09 per-output seed or a 07c-2 stage-1 source ships a provisional on the wrong stream; L4 or the self-ABX
notices before CI.
