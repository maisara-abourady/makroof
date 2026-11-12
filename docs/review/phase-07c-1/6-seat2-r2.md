# 6 — Seat 2, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 2, ROUND 2 (phase 07c-1). This answers only the two cells asked in `docs/review/phase-07c-1/5-decider-decision-r1.md` §7.

**(a) AX48: use a saved E_b as the interim on an S+E match with a P mismatch. Now 1, later 1, can live with it, with one condition.**

- **Why it is safe if P mismatches only through rounding.** The only path from a different OS or fs into the solve is `bandsSpecularTarget`. That target is the specular energy times bandEnergy(fs), divided by bandEnergy(fs), so the difference is a few ulps. It reaches E_b only if it flips the ceiling in N_need. Without a flip, the step is at ulp level. With a flip, N changes by one or more 64-history blocks and the step is about the achieved SE: up to 0.124 dB uncapped (AX42), and up to AX41's capped SE where the cap binds. The interim lasts at most the solve time, 81–131 ms at (A) W_max (AX38 4c). [Observed in the code: `src/sim/Engine.cpp` L318–321 and `src/sim/diffuse/DiffuseEstimator.cpp` L539–540.]
- **The gap.** P also absorbs upstream engine constants that neither S nor E contains: the AX22 image cap and fallback, the mixing-time rule constants, `kCrossfadeHalfS`, `kMatchNormalisationS` and the AX4 air table. All of them move t_mix, the window or the air term. If one of them changes without a version bump, a P mismatch is no longer rounding, and the interim is a stale level that can be off by more than the SE.
- **The CI fingerprint test closes the gap only if its fixture reaches those code paths.**
- **Condition (rating stays at 1 only with it):** the fingerprint fixture set must include at least:
  - one scene that triggers the AX22 ISM fallback (`ismFallback` true);
  - one air-dominated scene (large volume, high bands).

  Then any change to those constants changes E_b, forces a version bump, and turns the case into an E mismatch.
- **Without the condition:** now 1, later 2. The evidence would arrive at the first post-release change of an upstream constant.

**(b) Seat 7's split (on an E mismatch the saved E_b stays authoritative until the user's next edit). As proposed: now 1, later 2.**

- **Now 1:** before release no user projects exist, and the format already stores both parts of the key.
- **Later 2:** an E mismatch has two causes that the split treats alike.
  - **A precision change** (for example 07c-2's W_max raise, or a change to n*_max or SE_target). The old E_b is still an unbiased estimate from the validated estimator, with its SE recorded. Keeping it is defensible.
  - **A correctness change** (an estimator bug fix, a change to D1–D7, or a model change). Keeping the old E_b keeps a level the current engine says is wrong. It plays silently in bounces and lies outside the gated AX43 set. This is my premortem from round 1.
- **Condition that lowers the split to 1/1:**
  - Split E into two parts, E_prec (`DiffuseLimits`) and E_model (the estimator-version id plus the upstream constants under (a)).
  - The saved E_b stays authoritative only on an E_prec-only mismatch. An E_model mismatch always forces the solve.
  - The saved U and diagnostic fields (SE, cap hit, VOV_union, both-near) travel with E_b, so AX44's note stays true for the old estimate.
  - The rule bumping E_model is part of the fingerprint test's contract: a change that moves E_b on the fixture with `DiffuseLimits` unchanged is E_model.
- **Without this split:** S2 is later 2. Under the decider's §7 rule, my cell alone blocks adopting the split now.

**Hand-offs**
- Whether NFR-6 wants old projects frozen on an estimator that has since been corrected: Seats 5, 7 and 8 (the PRD reading).
- Whether a step of 0.1 dB or more at load is audible: Seat 1.