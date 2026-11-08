# Phase-07 decider round 1: interrogator, decision mode (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

Target: decider-round1.md.

| decision | outcome | reason |
|---|---|---|
| D1 push-away (C) | SURVIVES WITH CORRECTIONS | geometry correct, tie-break well defined; test (c) value rounded; tie jump larger than stated |
| D2 resize (A) | SURVIVES WITH CORRECTIONS | "100 m³" unit; dB reference; DRR-invariance conditions |
| D3 12 s cap (a) | SURVIVES | — |
| D4 trim −48…+24 | SURVIVES WITH CORRECTIONS | covers the band mean, not the frequency-response peak (Kuttruff Eq. 3.53 ≈ +51 dB); cite Eq. 5.45 not 5.44 |
| D6 AX33 | SURVIVES | "at most rebuild + 2P" |
| D7 crossfade + no-op + AX18 amendment | **FALLS** | L4 "aligned direct dominates" fails in the default scene (r = 6.09 m vs r_c 0.67 m at 63 Hz / 1.30 m at 1 kHz; reflected energy 19 / 13 dB above direct, Kuttruff Eq. 5.44/5.45); L5 contract equality ≠ IR identity (maxReflectionOrder no effect on the hybrid IR, AX20; outputMode, hrtfId ignored in 07; extensions) → recall of an IR-identical scene gets EqualPower, +3.01 dB (Vorländer Eq. 4.15); L6 "as real tails do (Vorländer Eq. 6.14)" WRONG (Eq. 6.14 is diffuse-field coherence vs receiver displacement, min ≈ −0.217; engine ρ depends only on Δr of the nearest emitter, reaches −0.83); deferred non-realtime state submit's law unspecified |
| D8 AX34 | SURVIVES WITH CORRECTIONS | physics right; gate reset steps 3/5, builder and offline build in the AX34 state; bit-equality needs trim bypassed/unity and no AX32 guard |
| D9 log map | SURVIVES WITH CORRECTIONS | "≈ one jnd for all three axes" WRONG for single-axis travel (default room, 1 kHz, Sabine Eq. 5.26: w 0.15 %, d 0.10 %, h 4.05 % per 1 %), not load-bearing (minimax carries it); endpoint exactness comes from rounding/pow, not the clamp: test on all three platforms |

Key numbers checked: D1 example exact tie p = (0.1, 0.75 + 0.15√3 = 1.00981, 0.75), tie jumps up to 0.52 m (> A's
0.45 m); brute-force spacing 3.36 mm, lower margin not guaranteed at wedge corners. D2 52.92 m, 18.78 dB re default
(−34.5 dB re 1 m), 3.81 %. D3 11.9 dB at 63 Hz (Eyring, m = 0). D4 +28.48 direct; +43.73 reverberant; +43.86 sum;
+25.80 parameters-only; peak ≈ 7.1 dB above band mean (B ≈ 44.5 Hz, T ≈ 4.0 s, Eq. 3.53, stated for f > f_s). D6 AX31
delay in (P, 2P]. D7 ρ_b formula correct with sinc(x) = sin(πx)/(πx); Δr = 16 cm → −10.7 dB; at Vorländer §15.3 speeds
(30–50 cm/s) Δr per 32 ms ≤ 1.6 cm → ρ_1k ≈ 0.95, ρ ≥ 0.414 below ≈ 3.7 kHz. D8 544 at every rate (49.3 ms at
11.025 kHz). D9 1.0429 per 1 %; fl(100/1.5)·1.5 rounds to 100 in double.

## Questions for the decider
1. D7 no-op: which equality defines "nothing is submitted" given IR-identical scenes that differ in contract fields?
2. D7 premise/amendment: which per-band claim with numbers replaces "aligned direct sound dominates" (e.g. ρ_b at an
   assumed Δr per update)? Does EqualGain still follow? Corpus-consistent wording instead of "as real tails do"?
3. D4: band-mean or max |H(f)|?
4. D9: restated jnd basis per axis; endpoint exactness relies on pow(y, 1) = y on all platforms?
5. D8: what do reset steps 3 and 5, the builder and offline builds do in the AX34 state; trim applied; AX32 skipped?
