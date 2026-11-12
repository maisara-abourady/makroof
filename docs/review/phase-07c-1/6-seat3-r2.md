# 6 — Seat 3, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 3, ROUND 2 (phase 07c-1). Ratings are now/later on the 0–3 scale. Read against `5-decider-decision-r1.md`.

**Matter A.** My ratings do not trigger the "flip to A2" rule: I rate A1 and A2 the same.
- **A0: 2/2.**
  - With no saved level and B3 out, the first IrSet at load can carry a tail only after a synchronous solve of 81–144 ms (K4).
  - That solve grows with the W_max raise in 07c-2.
- **A1: 0/1.** Step 0 on the same OS; a rounding-level step across OS or fs. The later 1 is key completeness at the 07c-2 W_max raise.
- **A2: 0/1.**
  - It sounds identical to A1 on the same OS (agrees with your L2).
  - E is in the key, so a stale level cannot survive an engine change.

**Matter B.**
- **B1 alone: 3/1.** At load there is no level, so no tail. This breaks condition 5 ("never silence") together with condition 9.
- **B2 alone: 2/2.**
  - On edits it either holds the ISM behind the solve (condition 4) or needs a level from somewhere else.
  - In 07c-2 its SE reaches 1.33 dB.
- **B4: 0/1.**
- **B4-G: 0/1.**
  - Condition (renderer): the interim amplitude must use the ebar of the unit decay actually played. If the provisional tail uses the new T60s, use the new ebar.

**D3\* on T60-changing edits, with the ISM waiting for the provisional tail: 2/2 as written. With the condition below: 1/1.**

New arithmetic that sizes the prefix length L_p:
- Truncating at L_p biases the Schroeder EDC. The normalised EDC is (e^−x − a)/(1 − a), where a = e^−X is the energy left at L_p.
- For EDT within 5 % of the untruncated value, the −10 dB point must fall at x ≥ 0.95·ln10 = 2.188. That needs a ≤ 0.0136, so X ≥ 4.30 nepers.
- So the prefix must cover at least 18.7 dB of decay in the slowest band: **L_p ≥ 0.31 T60_max**, plus the fade.
- This is conservative: it treats the tail alone, and the early part lowers the bias in the hybrid IR. Seat 1 should confirm the EDT reference.

Cost [Hyp, scaled by FFT size from the 3.14 s]:

| T60_max | L_p | FFT | provisional cost | resulting time |
|---|---|---|---|---|
| 8 s, 96 kHz | about 2.5 s | 2^18 | about 0.34 s | synchronous restore about 0.5 s, at AX49's reversal threshold |
| above 8 s | — | 2^19 | about 0.7 s | — |

On edits the ISM therefore waits about max(0, t_prov − t_ISM). That is about 0.2–0.25 s at an 8 s T60, which is longer than the 81–131 ms solve wait that condition 4 was written to forbid. It keeps the letter (no diffuse solve in the way) and breaks the purpose (my condition 4).

**Condition to reach 1/1.**
- Submit the new ISM as soon as it is ready, with no waiting.
- If the provisional tail is not ready by then, carry the previous unit decay at the interim level, rescaled to the old ebar: sqrt(E_target/ebar_old). This is D5 used only as a bridge.
- The provisional or exact tail then follows as equal-gain steps (same noise, ρ high).
- The added ISM latency is printed in record (g).
- Alternative that also reaches 1/1: on edits, use D5 → exact directly and keep D3\* for loads, where no IrSet is current.

**AX18 amendment text: confirmed, with four corrections.**
1. **"The same band noise" holds only for the same `tailSeed`, emitter stream and fs, and "up to rounding".** The prefix and full generators use different FFT sizes. Add: "a `tailSeed` or fs change gives unrelated tail noise: equal-power." The per-output seeds in Phase 08/09 (`tailSeedForOutput`) must match between provisional and exact, which is Seat 4's R.
2. **Name the residual differences.** The tails differ by a normalisation gain (expected vs realised energy) and by the exact tail's extension past L_p. The extension fades in from nothing, so the law is immaterial there. Neither difference lowers ρ inside the overlap.
3. **Add the existing edit case for completeness.** A T60-changing edit uses the same noise under a different envelope. ρ is high early and falls with time, and equal-gain (the current edit law) stays right. Without this line a reader might apply equal-power to it.
4. **Arithmetic check.** Equal-power mid-fade is 10·log10(1+ρ) = +3.01 dB at ρ = 1; equal-gain is 10·log10((1+ρ)/2) = 0 dB at ρ = 1. The text is correct. Keep "the first IrSet after a restore fades from silence (law immaterial)" and "an other-scene restore and the mode switch stay equal-power".

**Researcher or packet item.** Measure the provisional synthesis time at L_p = 0.31 T60_max + fade, for T60_max = 2, 8 and 12 s at 48 and 96 kHz, before the generic L_p rule is fixed.

**Premortem.** If L_p is set from cost rather than from the EDC bias, the provisional passes the 1 dB level test and fails EDT on long rooms. If it is set from EDT, the synchronous restore at 100 m / 96 kHz lands at about 0.5 s and trips AX49's reversal. The condition 9 packet shows which comes first.