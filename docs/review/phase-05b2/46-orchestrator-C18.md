# Orchestrator computation C18: are realistic halls in the capped class? (Seat 9, R1–R3 hand-off)

2026-11-10. The room is 20 × 30 × 10 m, with α 0.1 on the walls and ceiling and an absorbing audience floor (α 0.6 or 0.8).
Scattering is s = 0.3 or 0.5 on every face, with the W1 reference positions. The rule is the joint N-3W\*\*\* at W_max (A),
n\*_max 1 024. JSON section `c18`.

| floor α | s | t_mix,e (s) | n\* | N | cap hit | SE (dB, e0/e1) | U |
|---|---|---|---|---|---|---|---|
| 0.8 | 0.5 | 0.114 | 1 024 | 1 024 | no | 0.077 / 0.071 | silent |
| 0.8 | 0.3 | 0.114 | 1 024 | 1 024 | no | 0.046 / 0.045 | silent |
| 0.6 | 0.5 | 0.114 | 1 024 | 1 152 | no | 0.083 / 0.071 | silent |
| 0.6 | 0.3 | 0.114 | 1 024 | 1 024 | no | 0.053 / 0.048 | silent |

**Reading.** These halls keep the short window of W1 (t_mix,e 0.114 s), never hit the cap, and meet the 0.083 dB target.
The long window that makes layouts 4/5 expensive (0.38 s) is specific to those synthetic s = 1 layouts. A hall with an
absorbing audience floor and s ≤ 0.5 is not in the capped class under (A) [measured for these four rooms only].
