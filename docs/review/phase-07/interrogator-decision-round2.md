# Phase-07 decider round 2: interrogator, decision mode, round 2 (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Judged against Phase 07's ACs for D7 (advocate redirect). Round-1 corrections all applied.

| decision | outcome | what remains |
|---|---|---|
| D1 | SURVIVES WITH CORRECTIONS | tie jump "up to 0.6 m (sphere diameter); 0.52 m in example (c)" (l_x = 0.11, e_x = 0.105 on the wall normal → chord ≈ 0.6 m) |
| D2 | SURVIVES | — (optional: uniform resize scales positions only approximately, margin offset) |
| D3 | SURVIVES | — |
| D4 | SURVIVES WITH CORRECTIONS | DoD extreme scene: L and R at the same point 0.3 m from the listener (coherent +6.02 dB in the +43.9 estimate; separate points ≈ +3 dB). +24 check verified: 1 kHz −2.19 → −24.0 dB incl. direct (21.8 dB drop); 500 Hz −23.0; 4 kHz 25.6, 8 kHz 29.3 dB (Kuttruff Table 6.1) |
| D6 | SURVIVES | — |
| D7 | **FALLS (one point)** | restore flag not cleared when the restore's submit is skipped as bit-identical → next ordinary position update uses EqualPower at ρ ≈ 1 → up to +3.01 dB (Vorländer Eq. 4.15); test checks only the restore. Everything else holds: break-even √2 − 1; f_c·τ ≤ ≈ 0.170 (ρ = 0.4140) ⇔ δ ≤ ≈ 58.3 m·Hz/f_c; triangle-inequality bound; Cauchy–Schwarz bound; Omni ignores maxReflectionOrder (`Engine.cpp` 368–383); IR-identity skip consistent with reset step 3, R3-1, R3-2; offline flag determinism |
| AX18 replacement | SURVIVES WITH CORRECTIONS | cross term is Vorländer Eq. 4.15 (§4.3), not Eq. 1.37 (incoherent sum); "(k−1)·r_i" only for uniform resizes, approximately (margin offset) |
| D8 | SURVIVES WITH CORRECTIONS | "the builder is not started" → "stopped before prepare (existing rule) and not restarted" (48 → 192 kHz case) |
| D9 | SURVIVES WITH CORRECTIONS | "0 … +4.3 %" exact under Sabine (Eq. 5.26); Eyring (Eq. 5.24, AQ2) can differ slightly (−1.1 % … +4.9 % in extreme layouts); endpoint branches exact |
| Phase-10 gate | SURVIVES | consequence: at ρ = 1, P/R = ((1−g)+g√r)²/((1−g)+gr): r = 4 → −0.51 dB, r = 7 (8.5 dB) → −0.99 dB, r = 10 → −1.37 dB; band steps ≳ 8.5 dB fail the gate under any single-gain law |

Questions: (1) D7 rule making the flag apply only to the restore's own submit, with a test that the update after an
identical restore uses EqualGain; (2) D4 DoD L and R at the same point; (3) D1 accept "up to 0.6 m".
