# 10 — Seat 3, round 3 (phase 07c-1, on decider file 9 §6)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-3 questions: file 9 §6.

SEAT 3, ROUND 3 (phase 07c-1). Answers on the two cells in `9-decider-decision-r2.md` §6.

**K2 cell (synchronous stage-1 solve at keyless loads): correct it to 1/1, not 2/2.**
- My A0 2/2 rated a synchronous solve at every load, and its growth when 07c-2 raises W_max.
- K2 is a narrower case on both counts:
  - It runs only at keyless loads: v1 projects, a key mismatch, another OS or another fs.
  - Stage 1 stays at the (A) budget (81–144 ms, K4), so its cost does not grow at 07c-2.
- It adds no artifact: the first IrSet carries a tail, and the step to the final level is 0 in 07c-1.
- It closes the tail gap at load, which was my D1 objection.
- The later 1 is a condition, not a cost: stage 1 must stay at the (A) budget in 07c-2. If 07c-2 makes the synchronous stage cheaper or more expensive than (A), I re-rate it then.
- With S3 at 1/1, B4-G′ no longer has me as its worst-off seat. Your §4 max of 2 for B4-G′ came from my cell.

**D3\*′ load cell 1/1: confirmed, with three precision notes for the AX49 text.**
1. **K18 is right in power terms.** The working gives the squared ratio as 1/(1 + (1 − f_b)·δ), so the step is 10·log10(1 + (1 − f_b)·δ) ≤ 0.06 dB at |δ| ≤ 1.
   - δ has no upper bound in principle, but the result is robust: at δ = 3 it is still 0.17 dB.
   - Three conditions keep it true:
     - compute f_b per band with T60_b (bands below T60_max have 1 − f_b far smaller);
     - take E_p over exactly [0, L_f), before the fade;
     - use the same seed, emitter stream and fs as the exact tail.
   - The A4 test should assert the per-band step directly, not rely on the derivation.
2. **L_f = 0.312·T60_max agrees with my derivation** (0.31; your K17).
   - Keep the 0.1 s fade after L_f, so the fade does not eat into the 18.7 dB.
   - Cap L_p at the exact length (already in your text).
3. **The handover to the exact tail is equal-gain (AX18 as amended).** In that overlap ρ ≈ 1 (K2, the code fact of one shared PCG noise stream). The exact tail's samples beyond L_p fade in from zero, where the law has no effect.

**Cost.** File 8 measures 325–334 ms per emitter at 96 kHz with T60 ≥ 8 s. That puts the per-instance restore near 0.65–0.8 s, and higher on a keyless load once the stage-1 solve is added.
- From the seat-3 side this is acceptable now that your reversal reads the restore gate rather than a 0.5 s limit per call (§5 reversal 1).
- The prefix generator builds its own constructor spectra for each L_p. The recorded constructor-spectra cache is the right first remedy, and it is bit-identical.
- Whether 8 instances fit is for Seat 5 and Seat 7.

**T60-edit cell 2/2:** stands as given, together with my bridge condition to reach 1/1.