# Phase-07 decision loop, round 2: advocate (2026-11-08; corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d)

All round-1 conditions met (follow-ups for phase-10/11/13 in decider-round2 §4). Result: D1, D2, D3, D4, D6, D8, D9,
AX18 text, phase-10 gate PASS (with the interrogator's wording corrections); D7 REDIRECT (narrow); no NO.

- D7: make the restore flag apply only to the restore's own submit (clear it when that submit is skipped, or scope it
  to the restore's generation); offline deferred submit clears it at the same block boundary (AX5); generic (NFR-8);
  test that the first position update after an identical restore uses EqualGain (realtime and offline). If the
  interrogator confirms, D7 goes to /fix-plan without returning to the advocate. Nothing else in D7 reopened.
- Phase-10 gate: Phase 10's problem; add one sentence now: "Known limit: at ρ = 1 a band step ≳ 8.5 dB between
  consecutive IRs exceeds 1 dB under any single-gain law (Fink's equal-power-assumption law included); Phase 10
  either defines the gate's domain or proposes an energy-aware law. Each scenario reports its largest band step."
- Corrections to apply: D1 "up to 0.6 m (sphere diameter); 0.52 m in example (c)"; D4 DoD L and R at the same point
  0.3 m from the listener; AX18 cross term Eq. 4.15, "(k−1)·r_i" uniform-only, approximate; D8 builder "stopped before
  prepare (existing rule) and not restarted"; D9 "0 … +4.3 %" under Sabine (Eq. 5.26), Eyring up to ≈ +4.9 %
  (−1.1 %) in extreme layouts; D2 optional margin-offset note.
