# 6 — Seat 4, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

Round 2, Seat 4. Checked against docs/review/phase-07c-1/5-decider-decision-r1.md.

- **D3\*: confirmed at 1/1.** My condition R is carried as the Phase 08/09 debt at L391: the provisional tail gets the same per-mode decorrelation and coherence target as the exact tail.
- **AX48 key: confirmed.** S excludes `outputMode`, `hrtfId` and `tailSeed` (L94, L314). L330 adds the test that a v2 state restored in the other output mode uses the saved E_b bit-identically, and L331 says a change of mode, HRTF or seed never re-solves. That meets my condition K; my Matter A rating for A1 is now 0/1.

One addition: my condition M is not visible in the provisional decision. L393 covers "never re-solves", but not the D2 side, which is that a mode switch reuses the cached unit decays and never waits for a synthesis. If that is not recorded beside L393, my D2 rating stays at 1/2 instead of 1/1.