# 40 — Interrogator: the one check after three rounds, FM-D1-S3 (file 39)

2026-11-12, corpus c1b171f. **Outcome for FM-D1-S3: PRD MISREAD (row 83)** — option (iii) never shown against the cited
PRD id; (ii) shown against NFR-1 on an invented map cell (row 82, TENSION MISREAD: Seat 3 rates "O5′ + O2-fixed" 0/1 with no
downstream condition, so under (ii) O8 stays max 1, sum 11; (ii) is excluded only because the S3 row would have no "repaid
when"). **D1 (O8) unchanged: max 1, sum 11 under every reading.** Routing: README "Who answers Maisara's questions" item 3
(a) → NEEDS MAISARA with the decider's recommendation, the corrections and its PRD reasoning.

Holds: (i) and its NFR-1 reading (81: each line tests an existing sentence; 08-3 l.38–40 / AC l.69–70 state it without a
method; 09 l.39 no AC); arithmetic −18.27 / −19.27 / −24.55 dB (85); independent stream +3 dB (87, Vorländer Eq. 4.15);
aggregate detection (89); 05d changes (95 l.18 reading of the 2026-11-05 "no open items" §6 row — D1–D7/B items stay settled;
97 BRAS-only branch); d_dir direction (96: wording "untruncated noise").
Corrections required before any application: 80 cite "PRD NFR preamble (l.101) and NFR-1"; 86 write 10·log10(E/E) ≤ … dB;
**88 CONDITIONS VIOLATED** — 08-3/09 build the ears / speakers by a 2×2 coherence mix (L = a·n1 + b·n2, R = a·n1 − b·n2,
a = √((1+γ)/2), b = √((1−γ)/2)), so "the other output's seed" is not an independent stream: with seeds swapped the L
difference is 10·log10(2(1 − √(1 − γ²))) (≤ −18.27 dB, i.e. not red, wherever |γ_b| ≤ 0.122), R 10·log10(2(1 + √(1 − γ²)));
with the other output's signal 10·log10(2(1 − γ_b)) (not red where γ_b ≥ 0.9926) — name the construction, give the expected
value per output and band, assert red on the aggregate; 90 08-3/09 use B (the AX47 bound in force) as 07c-2 does; 91 the
07c-2 window for full-length class (c) / load-fallback interims (no L_f); 92 h includes per-mode filters (08-3 l.31 HRTF
magnitude); 93 "negative control red" per line (07c-2 has none). Observation 98: the 08-3/09 lines fall in Seat 4's row
(not convened for D1).
Ledger rows P07C1-G3-80 … 98.
