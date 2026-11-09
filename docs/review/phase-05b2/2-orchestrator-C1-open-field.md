# C1 — `open_field` under option 5.1-A (orchestrator computation for D-T5 (4), knowledge item D5-K9)

2026-11-09. Requested by the decider's convening round (`1-decider-convene-T5-T4.md`, "Orchestrator computation").
Script: `tools/validation/phase05b2_dt1.py openfield` (data: `tools/validation/data/phase05b2_dt1.json`, section `open_field`).

**Model.** `tests/scenes/valid/open_field.json` (100 × 100 × 30 m; floor α 0.05…0.99, s = 0.4; the other five faces
α = 1, s = 0). Under 5.1-A the diffuse energy is a single generation: s(1 − α) of the direct sound's
irradiance on the floor is re-radiated per Lambert and gathered directly at the listener (Kuttruff Eqs. 4.24, 4.29);
every other route meets an α = 1 face. AX4 air on both legs. Window and referral as `matchTail`
(the AX22 fallback is active: t_mix,e = 1404.4 ms for both emitters; nominal Eyring T60 per band below).
The specular entries in the window are zero (the floor reflection arrives 1.4 ms after the direct sound,
before the window starts; every other image is zero), so E_target = the diffuse term.

**Two independent evaluations.** (i) Exact integration over the floor (polar grid around the source's foot point,
as `tools/acoustics/ground_scatter.py`, restricted to the 100 × 100 m floor, window-weighted); (ii) the D-T1 candidate (f)
prototype (MC with next-event estimation, 400 000 paths). They agree within the MC standard error.

Emitter L (R is the mirror image, identical to the printed digits):

| band (Hz) | Eyring T60 (s) | E_target,diff (integral) | E_target,diff (MC) | tail level at t_mix,e re direct, per 10 ms (dB) | whole tail energy re direct (dB) |
|---|---|---|---|---|---|
| 63 | 1.242 | 1.043e-14 | 1.043e-14 ± 7.8e-17 | -113.5 | -104.0 |
| 125 | 1.176 | 4.591e-15 | 4.593e-15 ± 3.5e-17 | -117.1 | -107.8 |
| 250 | 1.023 | 4.579e-16 | 4.581e-16 ± 3.9e-18 | -127.1 | -118.4 |
| 500 | 0.718 | 2.870e-19 | 2.874e-19 ± 3.7e-21 | -159.1 | -151.9 |
| 1000 | 0.636 | 1.240e-20 | 1.242e-20 ± 1.9e-22 | -172.7 | -166.0 |
| 2000 | 0.400 | 1.992e-27 | 2.027e-27 ± 7.5e-29 | -240.5 | -235.9 |
| 4000 | 0.251 | 5.251e-38 | 5.684e-38 ± 4.8e-39 | -345.9 | -343.3 |
| 8000 | 0.226 | 1.190e-41 | 1.288e-41 ± 1.1e-42 | -380.8 | -378.6 |

**Readings.**
- Under 5.1-A, E_b > 0 in every band, but the matched tail's whole energy is **≤ −104 dB re the direct sound** (63 Hz; −152 dB at 1 kHz).
  It starts at t_mix,e = 1.40 s. The Phase 04 consistency check (energy later than t_dir + 50 ms below −60 dB) still holds with
  > 44 dB to spare in every band.
- The rendered IR still has no early scattered energy (AX21 stands), so the physically expected ground scatter after 50 ms
  (ledger OF: −23 to −43 dB per band; `ground_scatter.py`) is not rendered: the tail does not replace it. That is the AX21
  deficit, unchanged by D-T5.
- The tail is not an artefact a listener can hear at these levels (> 100 dB below the direct sound).
