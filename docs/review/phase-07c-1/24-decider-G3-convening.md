# 24 — Decider: G3 / D1 convening round (phase 07c-1 session 2): CONVENE

2026-11-12, corpus c1b171f. (Verbatim content of the decider's report, condensed only in layout.)

Matter: D1, how AX47 (b)'s EDT clause reads in bands where EDT is ill-conditioned or outside its domain. Not at stake:
shipped audio (provisional = exact prefix to 3.6e-5; level steps ≤ 0.072 / 0.015 dB). Hard constraints: NFR-1 (Q9
unresolved; AQ9 and Seat 1's D-C1 ruling), NFR-8 / FR-SIM-2 (a test may choose its cases; no scene logic in src/sim),
AX5, AX47's 1 dB bound and 0.5 dB reversal not reopened, AX49 "Acceptance" (changes only under O4), A4, FM-4′, CLAUDE.md
no-loosening rule (an option chosen from results must show it is a domain rule).

Options: O1 out (P07C1-G3-01 CONDITIONS VIOLATED). O2 conditioning rule (defects G3-04, G3-05, G3-06, G3-08 to fix if it
wins). O3 fixed-window slope (Kuttruff §8.4 Eqs. 8.26–8.27, §7.6). O4 restrict to layout 5 and CR3. O5 IR-difference
criterion (x unsourced). O6 (decider's variant): assert EDT ≤ 5 % where r ≥ k·r_c (Eq. 5.44) per band, decided before the
run; others printed with level steps asserted ≤ 1 dB; k open (K7/K9).

| Seat | Convened | Reason |
|---|---|---|
| 1 Perceptual gatekeeper | yes (B1) | JNDs and their conditions; acceptance tests; AX47 is Seat 1's D-C1 ruling |
| 2 Engine architect | yes (B2) | estimator domain (r vs r_c), validation metrics, circularity |
| 3 Reverb renderer | yes (B3) | the provisional tail is its rendering; decay matching |
| 4 Chain keeper | not required | omni whole-IR test; no HRTF, decoding, format or parity item |
| 5 Deadline keeper | yes (B5) | CI gate on three platforms; flake risk; rework |
| 6 Canvas designer | not required | no control, range, default, preset or workflow |
| 7 Founder | yes (B7) | schedule and complexity cost; public wording |
| 8 Storyteller | not required | nothing changes in what a producer does or hears |
| 9 Room acoustician | yes (B9) | early structure vs decay; near-field EDT in real rooms; CR3 and the absorbing-floor cube |

Knowledge inventory: K2 Table 6.1 (5 % EDT, 500–1000 Hz, conditions not stated); K3 Kuttruff §8.4 (r ≫ r_c, not
quantified); K4 Eq. 5.44; K5 the d ↔ r/r_c mapping to be re-derived; K7 ISO 3382 minimum distance → RESEARCH NEEDED R1;
K8 EDT estimator sensitivity near the source → RESEARCH NEEDED R2; K9 r, r_c per case → orchestrator M1 (file 25);
K11 the "half" floor = product matter; K13 the O2 code does not print level steps. Briefs B1–B9 and R1/R2 passed
verbatim to the seats and the researcher (files 26-…).
