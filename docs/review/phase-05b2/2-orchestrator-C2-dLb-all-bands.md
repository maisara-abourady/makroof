# Orchestrator computation C2 — ΔL_b (AX16 vs hybrid) in all eight bands (D-T5 (1), knowledge item D5-K2)

2026-11-09. Asked by Seat 9 (item (b)) and Seat 6 (5.1-C condition); the decider's D5-K2 marks the bands outside 500 Hz–2 kHz
as under-informed. Source: the committed Phase 05e/05f X-b data `tools/validation/data/phase05_scope6.json` (all eight bands were
computed there; `report-phase05.md` §6a prints only 500 Hz–2 kHz). ΔL_b = 10·log10(E_target(AX16)/E_target(hybrid)); the hybrid at the
05e patch sizes (`info.patch_size_m` per room). No new run.

Signed value of largest magnitude per group and band (dB):

| group | n | 63 Hz | 125 Hz | 250 Hz | 500 Hz | 1000 Hz | 2000 Hz | 4000 Hz | 8000 Hz |
|---|---|---|---|---|---|---|---|---|---|
| BRAS CR2 initial | 10 | +0.23 | +0.23 | +0.22 | +0.22 | +0.22 | +0.22 | +0.22 | +0.21 |
| BRAS CR2 initial, per-band s | 10 | +0.11 | +0.12 | +0.14 | +0.16 | +0.21 | +0.29 | +0.40 | +0.54 |
| BRAS CR3 initial | 10 | -0.99 | -1.03 | -1.01 | -1.07 | -1.13 | -1.18 | -1.17 | -1.21 |
| BRAS CR3 initial, per-band s | 10 | -0.37 | -0.46 | -0.58 | -0.80 | -1.11 | -1.47 | -1.92 | -2.41 |
| BRAS CR4 initial | 10 | -0.67 | -0.67 | -0.68 | -0.68 | -0.67 | -0.70 | -0.74 | -0.93 |
| BRAS CR4 initial, per-band s | 10 | -0.39 | -0.43 | -0.49 | -0.56 | -0.64 | -0.85 | -1.02 | -1.45 |
| Phase 04 rooms | 6 | -0.24 | -0.24 | +0.25 | +0.28 | +0.29 | +0.30 | +0.30 | +0.29 |
| Table 5.2 layout 2 | 4 | +1.13 | +1.13 | +1.13 | +1.13 | +1.13 | +1.13 | +1.13 | +1.13 |
| Table 5.2 layout 4 | 4 | +3.83 | +3.83 | +3.83 | +3.83 | +3.83 | +3.83 | +3.83 | +3.83 |
| Table 5.2 layout 5 | 4 | -1.12 | -1.12 | -1.12 | -1.12 | -1.12 | -1.12 | -1.12 | -1.12 |
| Table 5.2 layout 6 | 4 | -1.14 | -1.14 | -1.14 | -1.14 | -1.14 | -1.14 | -1.14 | -1.14 |
| uniform-a s-cases | 3 | +0.43 | +0.43 | +0.43 | +0.43 | +0.43 | +0.43 | +0.43 | +0.43 |

- Largest |ΔL_b| inside 500 Hz–2 kHz: 3.83 dB; outside (63–250 Hz, 4–8 kHz): 3.83 dB.
- Case-bands over 1 dB outside 500 Hz–2 kHz: 41 of 425; over 0.43 dB: 112.
- The hybrid-vs-tracer agreement (window check, report-phase05b §5) exists only at 500 Hz–2 kHz. In the 15 (A) cases α and s do not depend on the band,
  so the 63–250 Hz and 4–8 kHz windows differ from the checked ones only by air absorption (AX4); no tracer run exists outside 500 Hz–2 kHz.
