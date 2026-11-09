# Orchestrator computation C7 — reference costs (8 bands, 2.5 m) and independent checks at the 100 m cube (D-T1)

2026-11-09. Requested by the D-T1 convening round (`9-decider-convene-T1-T2-T6.md`, C7). Data: `tools/validation/data/phase05b2_dt1.json`
section `c7`; tool `tools/validation/phase05b2_dt1.py step_c7` (numpy `ref_hybrid`, single process).

## 1. `ref_hybrid` at ℓ = 2.5 m, all 8 bands (the agreement-reference cost for CS-2 / CS-3)

| room | patches | bins | kernel (GB) | kernel build (s) | solve (s) | pairs | generations |
|---|---|---|---|---|---|---|---|
| dead_booth | 6 | 28 | 0.000 | 0.1 | 0.3 | 1 | 10 |
| living_room | 24 | 31 | 0.001 | 0.1 | 0.1 | 1 | 9 |
| classroom | 52 | 39 | 0.003 | 0.2 | 0.1 | 1 | 8 |
| club | 118 | 61 | 0.027 | 1.0 | 37.5 | 1 | 9 |
| concert_hall_box | 684 | 165 | 2.470 | 40.0 | 186.2 | 1 | 12 |
| stone_box | 184 | 85 | 0.092 | 1.8 | 25.4 | 1 | 7 |
| W2 | 352 | 385 | 1.526 | 189.2 | 109.6 | 2 | 6 |
| CR2 | 52 | 38 | 0.003 | 0.3 | 0.9 | 10 | 7 |
| CR3 | 352 | 110 | 0.436 | 9.9 | 43.0 | 10 | 9 |
| CR4 | 714 | 155 | 2.529 | 62.0 | 118.1 | 10 | 8 |

(`classroom`, `club`, `concert_hall_box` are in the data file; W1 in `dense`.) Every case of CS-3 is computable on the session machine;
the largest are W2 (1.5 GB) and CR4 (2.5 GB). Exported once as a golden, the reference costs CI nothing.

## 2. Independent checks at the 100 m cube (α 0.15 band-flat, s = 0.3; emitter (45, 70, 2), listener (50, 30, 1.7); t_mix,e = 1117.5 ms)

- **Tracer** (`tools/acoustics/tracer.py`, Kuttruff §9.8, own seed, r_d = 0.5 m, N₀ = 254·V = 254,000,000 particles, 522 s):
  window k_tr ≈ 38208, SE 0.022 dB. **(f) − tracer = -0.009 dB** (500 Hz–2 kHz identical to 0.001 dB;
  (f) at 128 000 paths, SE 0.023 dB).
- **Coarse ℓ ladder of `ref_hybrid`** (air factored): 20 m → 10 m changes E_target by 0.077 %; **(f) − ladder(10 m) = -0.031 dB**.

Readings: at the contract maximum, (f) agrees with an independent tracer within its standard error and with the reference model at a
coarse but converged ℓ within 0.03 dB. This closes the "no reference at 100 m" gap for this scene (one pair, band-flat α).
