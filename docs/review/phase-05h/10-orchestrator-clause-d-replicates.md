# Orchestrator — Seat 1's clause (d) replicates on the C++ shipping rule (2026-11-10, local Release, 4 cores)

Data only (phase-05h §3 Trigger 1, starting state; Seat 1 file 55's two conditions: the shipping rule as built, on disjoint
pre-registered streams, repeated on the C++ build). Test `records: clause (d) replicates of the shipping rule at the gated
cubes` (`tests/unit/test_diffuse_records.cpp`, `[.][benchmark][diffuse-replicates]`). Provisional W_max 3.05 M per emitter,
n\*_max 1 024. Replicate r runs the pilot + joint rule + final range as built on histories offset by r × 2^20 (pre-registered,
disjoint); the long run is 2^20 histories on [2^26, 2^26 + 2^20). Error = 10 log10(E_target,replicate / E_target,long) at 1 kHz.

| scene | emitter | long-run SE (dB) | median error (dB) | p95 \|error\| (dB) | max \|error\| (dB) | SD of error (dB) | achieved SE median (SD) (dB) | VOV_union median (SD) | clause (d) (p95 ≤ 1 dB, \|median\| ≤ 0.25) |
|---|---|---|---|---|---|---|---|---|---|
| cube100_lowalpha0.05_s0.3 | e0 | 0.006 | +0.007 | 0.250 | 0.410 | 0.137 | 0.117 (0.036) | 0.183 (0.104) | met |
| cube100_lowalpha0.05_s0.3 | e1 | 0.006 | +0.027 | 0.178 | 0.260 | 0.118 | 0.115 (0.038) | 0.200 (0.099) | met |
| cube100_lowalpha0.05_s1 | e0 | 0.021 | −0.051 | 0.701 | 0.870 | 0.351 | 0.381 (0.072) | 0.178 (0.084) | met (but SE > 0.33 dB) |
| cube100_lowalpha0.05_s1 | e1 | 0.021 | +0.011 | 0.810 | 0.850 | 0.436 | 0.384 (0.076) | 0.183 (0.090) | met (but SE > 0.33 dB) |
| cube100_flutter_fallback | e0 | 0.000 | +0.000 | 0.003 | 0.005 | 0.002 | 0.002 (0.001) | 0.122 (0.161) | met |
| cube100_flutter_fallback | e1 | 0.000 | −0.000 | 0.005 | 0.015 | 0.004 | 0.002 (0.003) | 0.157 (0.238) | met |

Readings (no decision): at s = 0.3 the C++ joint-rule replicates give p95 0.18–0.25 dB (prototype C15, per-emitter rule:
≤ 0.28 dB), so Seat 1's floor is **met** there through clause (d) with the achieved SE 0.12 dB ≤ 0.33 dB; at s = 1 clause (d)
holds (p95 0.70–0.81 dB ≤ 1 dB) but the achieved SE 0.38 dB exceeds the 0.33 dB prerequisite, so the floor is **not met**
(the starting-state finding of file 1 §2 stands). The replicate SD of the achieved SE (0.036 dB at s = 0.3, 0.072–0.076 dB at
s = 1) and of the error are the starting-state spreads a "further rise" could be read against (D-H1 R-a / R-b).
