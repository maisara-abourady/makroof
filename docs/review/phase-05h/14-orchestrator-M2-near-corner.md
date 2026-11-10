# Orchestrator — M-2 tracer runs on the five mixed-α Phase 04 rooms and the independent near-corner reference (2026-11-10)

Reported, not gated (AX45 M-2; AX43 / AX44 "the independent near-corner reference (Seat 2)"). Script: the session scratch 
(tools/acoustics/tracer.py, seed 0x05B7-family default, 4 × 10⁶ particles per run in the Phase 04 rooms, 16 × 10⁶ at the corner; the
window of the Phase 04 plan; r_d below the listener's clearance at two radii). C++ E_target = the Python plan's specular target +
the C++ diffuse estimate in reference units (, shipping rule, provisional W_max). Values: 10 log10(E_C++ / E_tracer)
per band (63 Hz … 8 kHz), with the tracer's own SE = 4.34/√k_tr.

| room | emitter | t_mix,e (s) | r_d (m) | C++ − tracer (dB), 63 Hz … 8 kHz | tracer SE (dB) | C++ SE (dB, 1 kHz) |
|---|---|---|---|---|---|---|
| dead_booth | e0 | 0.0226 | 0.35 | +0.019 +0.020 +0.022 +0.023 +0.025 +0.026 +0.026 +0.026 | 0.006 | 0.017 |
| dead_booth | e0 | 0.0226 | 0.175 | +0.019 +0.019 +0.020 +0.020 +0.021 +0.021 +0.021 +0.021 | 0.012 | 0.017 |
| dead_booth | e1 | 0.0226 | 0.35 | +0.026 +0.026 +0.025 +0.025 +0.025 +0.026 +0.026 +0.026 | 0.006 | 0.017 |
| dead_booth | e1 | 0.0226 | 0.175 | +0.015 +0.014 +0.012 +0.011 +0.011 +0.012 +0.012 +0.012 | 0.012 | 0.017 |
| living_room | e0 | 0.0259 | 0.5 | -0.025 -0.025 -0.022 -0.017 -0.014 -0.012 -0.010 -0.010 | 0.010 | 0.021 |
| living_room | e0 | 0.0259 | 0.25 | -0.021 -0.021 -0.019 -0.015 -0.013 -0.012 -0.011 -0.011 | 0.019 | 0.021 |
| living_room | e1 | 0.0259 | 0.5 | -0.007 -0.007 -0.004 +0.001 +0.004 +0.006 +0.008 +0.008 | 0.010 | 0.022 |
| living_room | e1 | 0.0259 | 0.25 | +0.037 +0.037 +0.039 +0.042 +0.043 +0.043 +0.045 +0.045 | 0.019 | 0.022 |
| classroom | e0 | 0.0343 | 0.5 | -0.003 -0.004 -0.006 -0.007 -0.008 -0.008 -0.006 -0.005 | 0.020 | 0.031 |
| classroom | e0 | 0.0343 | 0.25 | -0.011 -0.009 -0.005 -0.002 -0.000 -0.000 -0.001 -0.002 | 0.039 | 0.031 |
| classroom | e1 | 0.0343 | 0.5 | +0.021 +0.020 +0.018 +0.017 +0.016 +0.016 +0.017 +0.018 | 0.020 | 0.032 |
| classroom | e1 | 0.0343 | 0.25 | +0.025 +0.022 +0.018 +0.014 +0.013 +0.012 +0.015 +0.017 | 0.039 | 0.032 |
| club | e0 | 0.0559 | 0.5 | +0.012 +0.012 +0.012 +0.012 +0.013 +0.013 +0.014 +0.014 | 0.027 | 0.053 |
| club | e0 | 0.0559 | 0.25 | +0.011 +0.009 +0.008 +0.006 +0.007 +0.008 +0.008 +0.009 | 0.055 | 0.053 |
| club | e1 | 0.0559 | 0.5 | -0.016 -0.015 -0.013 -0.013 -0.012 -0.012 -0.013 -0.012 | 0.027 | 0.053 |
| club | e1 | 0.0559 | 0.25 | -0.001 +0.000 +0.003 +0.004 +0.004 +0.004 +0.004 +0.004 | 0.055 | 0.053 |
| concert_hall_box | e0 | 0.1597 | 0.5 | -0.126 -0.114 -0.088 -0.068 -0.058 -0.049 -0.049 -0.055 | 0.079 | 0.049 |
| concert_hall_box | e0 | 0.1597 | 0.25 | -0.290 -0.280 -0.259 -0.242 -0.234 -0.226 -0.226 -0.232 | 0.154 | 0.049 |
| concert_hall_box | e1 | 0.1597 | 0.5 | +0.061 +0.057 +0.048 +0.041 +0.037 +0.033 +0.034 +0.037 | 0.079 | 0.067 |
| concert_hall_box | e1 | 0.1597 | 0.25 | +0.168 +0.160 +0.142 +0.127 +0.120 +0.114 +0.115 +0.120 | 0.162 | 0.067 |
| W1_listener_corner_0.1 | e0 | 0.1430 | 0.05 | +0.480 +0.480 +0.480 +0.480 +0.480 +0.479 +0.479 +0.479 | 0.318 | 0.063 |
| W1_listener_corner_0.1 | e1 | 0.1503 | 0.05 | +0.173 +0.179 +0.184 +0.188 +0.194 +0.199 +0.206 +0.213 | 0.265 | 0.064 |

Readings: the five mixed-α rooms agree with the independent tracer within ±0.3 dB in every band (the largest, concert_hall_box at
r_d 0.25 m: −0.23 to −0.29 dB against a tracer SE of 0.15 dB; at r_d 0.5 m −0.05 to −0.13 dB, SE 0.08 dB), inside the B11 window
tolerance of ±1 dB. The near-corner reference (W1, listener at (0.1, 0.1, 9.9), r_d 0.05 m) is noisy by construction (few detections
at that radius): C++ − tracer +0.48 dB (e0) and +0.17 to +0.21 dB (e1) against tracer SEs of 0.25–0.32 dB, i.e. within 1.7 SE; it
neither confirms nor contradicts NW-4C beyond τ (AX44 reversal: "the near-corner reference contradicts NW-4C by more than τ":
not met at this precision; a sharper reference needs ≈ 10× the particles).
