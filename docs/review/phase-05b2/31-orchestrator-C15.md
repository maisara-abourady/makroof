# Orchestrator computation C15: replicate check of the shipping rule in the closed 100 m cubes (Seat 2, S2-a)

2026-11-10. Seat 2's condition in `30-seat2-confirm-S2a.md`. It checks the region where the user note U stays silent although
the estimate is capped.
- **Rule:** N-3W\*\* per emitter at W_max (A) = 3.05 M, n\*_max 8 000 and 1 020 (C13's implementation).
- **Replicates:** 30 independent seed pairs.
- **Long run:** 1 M NW-4C histories on the disjoint range 50 M …, 1 kHz.
- **Pass, pre-registered by Seat 2:** |median| ≤ 0.25 dB and p95 |error| ≤ 1 dB against the long run.
- **Code and data:** `tools/validation/phase05b2_dt1.py` step `c15`; JSON section `c15`.

| scene, emitter | long-run SE (dB) | n\*_max 8 000: p5 / median / p95 (dB) | p95 abs / max abs (dB) | pass | n\*_max 1 020: p5 / median / p95 (dB) | p95 abs / max abs (dB) | pass |
|---|---|---|---|---|---|---|---|
| cube100_alpha0.10-0.22_s0.3_e0 | 0.0061 | -0.220 / -0.054 / +0.188 | 0.230 / 0.419 | yes | -0.217 / -0.031 / +0.199 | 0.248 / 0.382 | yes |
| cube100_alpha0.10-0.22_s0.3_e1 | 0.0061 | -0.212 / -0.040 / +0.282 | 0.282 / 0.363 | yes | -0.188 / -0.016 / +0.179 | 0.233 / 0.314 | yes |
| cube100_lowalpha0.05_s0.3_e0 | 0.0063 | -0.227 / -0.059 / +0.198 | 0.241 / 0.453 | yes | -0.248 / -0.035 / +0.205 | 0.260 / 0.394 | yes |
| cube100_lowalpha0.05_s0.3_e1 | 0.0063 | -0.211 / -0.059 / +0.281 | 0.281 / 0.374 | yes | -0.187 / -0.012 / +0.201 | 0.213 / 0.322 | yes |
| cube100_lowalpha0.05_s1_e0 | 0.0221 | -0.766 / +0.003 / +0.525 | 0.766 / 1.252 | yes | -0.763 / -0.036 / +0.356 | 0.763 / 0.794 | yes |
| cube100_lowalpha0.05_s1_e1 | 0.0220 | -0.764 / +0.149 / +0.799 | 0.893 / 1.130 | yes | -0.446 / +0.036 / +0.565 | 0.597 / 0.665 | yes |
| cube100_absorbing_floor_s1_e0 | 0.0051 | -0.115 / -0.005 / +0.172 | 0.181 / 0.224 | yes | -0.113 / -0.016 / +0.124 | 0.145 / 0.149 | yes |
| cube100_absorbing_floor_s1_e1 | 0.0051 | -0.133 / +0.039 / +0.173 | 0.177 / 0.233 | yes | -0.096 / +0.008 / +0.117 | 0.128 / 0.144 | yes |

**Readings.**
1. **All 16 rows pass** (8 scene-emitters × 2 n\*_max values).
2. **Cubes at s = 0.3 and the absorbing-floor cube.** The median ranges from −0.06 to +0.04 dB, and the p95 |error| is
   ≤ 0.28 dB. The capped estimate shows no skew toward low values there. The pilot VOV of 0.31–0.37 (C13 §1) did not turn into
   a median shift.
3. **The low-α cube at s = 1** is the widest case:
   - median −0.04 to +0.15 dB;
   - p95 |error| 0.60–0.89 dB, inside the 1 dB bound;
   - largest single error 1.25 dB, one replicate in 30.

   This is the scene where Seat 1's floor already fails on SE (0.44–0.64 dB; C14 (a)) and where U fires on "cap hit AND SE
   > 0.33 dB".
4. **Seat 2's fallback is not needed.** Its condition said that if the check fails, "cap hit AND VOV ≥ 0.1" is added to U
   for that class. Since every row passes, U stays as written in round 3.
