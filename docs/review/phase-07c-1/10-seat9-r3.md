# 10 — Seat 9, round 3 (phase 07c-1, on decider file 9 §6)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-3 questions: file 9 §6.

SEAT 9, round 3 (phase 07c-1): both points confirmed, with no correction.

1. **L_f = 0.312·T60_max: confirmed.** It meets my condition L_p ≥ 0.31·T60. The fade start sits where the decay is 18.7 dB down (a ≤ 0.0136). By Vorländer Eq. 6.4 that keeps EDT within 5 % (the jnd in Table 6.1), and I get the same arithmetic as K17. Taking T60_max per emitter is conservative for every shorter band, and the 0.1 s fade only removes energy beyond L_f, so EDT is not affected. One proviso: T60_max must be the same per-band T60 the exact tail is built with (air absorption included), not a nominal room value.

2. **K18 normalisation: confirmed.** It meets "no upward renormalisation".
   - The prefix is scaled to its expected share f_b, never to the full tail energy. The exact tail is normalised by its realised energy over the whole length (`NoiseTail.cpp`), so the prefix of the exact tail carries the same share.
   - The remaining provisional-to-exact difference is then bounded by the remainder fraction 1 − f_b ≤ 0.0136, which is ≤ 0.06 dB. That is well inside the 1 dB jnd of G and C80 (Vorländer Table 6.1).
   - E_p is measured before the fade, so the fade can only take the provisional below its share, never above it.

My D3\* rating stays at 1/1 with both conditions met. The evidence that would overturn it is the A4 test, the EDT and level comparison at 500 and 1000 Hz between the provisional and exact IRs.

File read: /home/user/makroof/docs/review/phase-07c-1/9-decider-decision-r2.md (§2 K17/K18, §6).