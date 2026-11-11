# Seat 4 — D-H3 (b)

`SEAT 4 POSITION — D-H3 (b)` (corpus present, c1b171f; no persona assumption fell)

**1. Reading.** Whether U raised at the default of `edge_values` / `open_field`, or a pilot that ships at `edge_values`, touches delivery: Phase 08's E_b parity (bit-identical omni/binaural/ears) and its "one both-near binaural render". Cue: *level and tone parity*. Answer to my brief: **neither is touched.** From the code: the diffuse solve is one per scene (AX39, AX44); the CI-reports test runs every fixture as `Kind::Omni` (`test_diffuse_reports.cpp` L57); `pilotShipped = nCap < blk` and `approximate` are set in `DiffuseEstimator.cpp` L382/L622 and copied into `TailMatch` by `Engine.cpp` L198/L211 before any mode branch. A pilot estimate with SE 3.98 dB (e0, −60 dB gain) / 0.76 dB (e1, +12 dB) is still one number read identically by both modes and ears; parity is bit-identity, not accuracy. `edge_values` is 1 of 10 valid fixtures with `outputMode: binaural` (from the code), so "binaural-mode fixture" is incidental; nothing about it selects it for Phase 08's both-near render (listening content; U there fires via the cap, not the both-near leg).

**2–4. Ranking, tension now / later.**

| option | label | now | later | reason / commitment / undo |
|---|---|---|---|---|
| (a) reading; list two known U cases | *prefer* | 0 | 1 | Now: no parity effect. Later: membership of the "pilot ships" list at `edge_values` is W_max-dependent (N_cap grows under phase-07c (C)), so E_b there moves at (C)'s golden round; if Phase 08 picks `edge_values` among its three binaural goldens it freezes a 3.98 dB-SE tail. Undo: a list line; one scheduled golden round. |
| (d) (a) + (ii) cause and movability printed | *prefer* | 0 | 0 | (ii) is my §14 chain-description line: it tells Phase 08 which fixtures are both-near-leg cases (usable for the render) and which are cap cases (not). (d)(i) is a note rule: Seats 1 and 6's; I do not rate it. |
| (b) change the fixture | *can live with* | 1 | 1 | Silences nothing (file 9); loses the one contract-limits scene (1.5 m slot, order 0, −60/+12 dB) that Phase 08's binaural build must also survive; touches `phase04_edge_values_omni`, the D5 hash golden, `test_hybrid_ir.cpp` L154, `test_diffuse_gate.cpp` L321 (from the code). Undo: fixture restore + golden round. |
| (c) reopen U | *can live with* | 1 | 2 | U is mode-independent, so parity survives any predicate; but Phase 08 consumes `TailMatch.approximate` per mode and selects its both-near render by U: building against a predicate still in a loop is rework of Phase 08 scope 7 and the item-8 records. Undo: a phase of Phase 08 rework. |

**5. Evidence.** One solve, shared across modes and ears: AX39, AX44, phase-08 scope 5 [plan ids]; code facts as cited above [from the code]. SE 0.76 dB ≈ 0.8 of the 1 dB jnd of G, 3.98 dB ≈ 4 jnd but at a −60 dB emitter: Vorländer Table 6.1 [corpus, L2056–2060]; audibility at that level is Seat 1's. `open_field` tail below −60 dB after t_dir + 50 ms: AX37 (5.4) [plan id]. Nothing for the researcher.

**6. Conditions.** (c) later 2 → 1: U decided and frozen before Phase 08 opens. (a) later 1 → 0: Phase 08's three binaural golden scenes exclude `edge_values` and `open_field`, or carry the SE-derived tolerance (phase-07c condition 8); the both-near render is drawn from a both-near-leg case (W1 / `club` / `living_room` at 0.1 m), never a cap case.

**7. Hand-offs.** Seat 6/1: (d)(i) note rule and what "level unreliable" means on an inaudible tail. Seat 5: blast radius of (b) on the goldens listed. Seat 2: whether n* 64 / N 0 is the AX41 rule or a defect. Seat 7: cost of (c).

**8. Premortem.** If (c) wins, Phase 08 selects its both-near binaural render and item-8 records against a predicate that then changes; the contractor reviewing Phase 08's listening pack notices first.
