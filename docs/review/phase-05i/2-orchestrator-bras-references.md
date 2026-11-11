# Phase 05i scope 1: the BRAS pairs' outer-band references and their gating (orchestrator, 2026-11-11)

**Route.** Produced on the session machine (4 cores, 15 GB) by `tools/validation/compute_phase05i_bras_references.py`
(committed 2c11610), phase05b.step_r1's recipe applied one band column at a time; CR4 at 1.25 m through the chunked
solver (float32 kernel 5.06 GB per band). Neither the 16 GB-runner `workflow_dispatch` job nor M-d (a larger machine)
was needed: the brief's open question G5 did not arise.

**Recipe check.** `--check` recomputed CR2 and CR3 at 500 Hz, 2.5 and 1.25 m, against the committed R1 values
(`phase05b.json` r1): worst relative difference **0.0** (bit-identical).

**Order and time** (D-H2 (c): 250 Hz and 4 kHz, then 125 Hz and 8 kHz, 63 Hz last): 10:10–10:49 UTC, 30 units
(3 rooms × 2 rungs × 5 bands); CR4 at 1.25 m 213–450 s per band, every other unit ≤ 106 s.

**ℓ_ref** (the 2.5 → 1.25 m change of E_target, max over each room's 10 pairs):

| room | 63 Hz | 125 Hz | 250 Hz | 4 kHz | 8 kHz | certified |
|---|---|---|---|---|---|---|
| CR2 | 0.372 % | 0.369 % | 0.346 % | 0.343 % | 0.331 % | 50 / 50 |
| CR3 | 0.378 % | 0.374 % | 0.379 % | 0.358 % | 0.349 % | 50 / 50 |
| CR4 | 0.134 % | 0.140 % | 0.142 % | 0.116 % | 0.148 % | 50 / 50 |

(500 Hz–2 kHz from 05h, unchanged: CR2 ≤ 0.353 %, CR3 ≤ 0.367 %, CR4 ≤ 0.141 %.)

**Gating.** All 150 case-bands certify under D-H2 (a) (< 1 %) and are gated under rule G-a by the export script, with
the CHANGELOG reason (commit f604043). Diff check against main's golden: every previously gated case-band's
`ref_fine`, `ref_coarse`, `l_ref`, `gated` unchanged; the only changed fields are the 150 case-bands' five columns.
**AX43 560 of 560, AX45 72 of 72; no case-band ungated, so no owner phase is needed.** The 63 Hz column is an
agreement with ref_hybrid, never claimed as a room validation below the Schroeder frequency (CHANGELOG reason).

**Agreement suite, local Release** (`[diffuse-agree-full]`, 1 min 14 s, this machine; CI run 43007183782 is the
evidence of record): 0 failures (N_test 65 536, 0 stage-2 runs); max |C++ − ref| 0.046 dB over the gated set and
0.020 dB over the BRAS case-bands (τ 0.25 dB). AX43's additive pooled check 'within' in every band:

| band | mean (C++ − ref) dB | catch 3·SE_pool + mean ℓ_ref (dB) | case-bands |
|---|---|---|---|
| 63 Hz | −0.0008 | 0.0035 + 0.0044 = 0.0079 | 70 |
| 125 Hz | −0.0009 | 0.0035 + 0.0045 = 0.0080 | 70 |
| 250 Hz | −0.0009 | 0.0035 + 0.0045 = 0.0080 | 70 |
| 500 Hz | −0.0009 | 0.0034 + 0.0046 = 0.0080 | 70 |
| 1 kHz | −0.0011 | 0.0034 + 0.0046 = 0.0080 | 70 |
| 2 kHz | −0.0012 | 0.0034 + 0.0046 = 0.0080 | 70 |
| 4 kHz | −0.0012 | 0.0034 + 0.0046 = 0.0080 | 70 |
| 8 kHz | −0.0009 | 0.0034 + 0.0047 = 0.0081 | 70 |

The catch is now uniform at ≈ 0.008 dB in all eight bands (05h: ≈ 0.008 dB at 500 Hz–2 kHz, 0.009–0.010 dB
elsewhere over 40 case-bands), 5.3× inside AX46's 1 % = 0.043 dB; far below the 0.02 dB board-return line.

**Per-room watch** (D-H3 (a)): 26 reference rooms in every band (05h: 23 in the outer bands); rooms of both signs
(10–11 positive / 15–16 negative); mean over rooms −0.125 … −0.139 against 3/√26 = 0.588; per-room mean z′ from −2.06
to +1.32; no room labelled (|mean z′| > 3: none).

**Listening pack.** `tools/ci/listening_pack.py` derives the README's per-room label from this golden: the BRAS room
`bras_cr3_ls1_mp2` moves from "3/8 bands gated" to "8/8 bands gated" (named in the PR, phase-05i §5); the other
listening rooms' labels are unchanged.

**report-phase05.md.** `tools/validation/report.py` and `run_validation.py` do not read the agreement golden (the
report's "gated" is the AQ9 noise-margin admission, AX27), so gating these references leaves the report unchanged;
the nightly BRAS run 43007188366 regenerates it on this tree as the check.
