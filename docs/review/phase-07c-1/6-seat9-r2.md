# 6 — Seat 9, round 2 (phase 07c-1, on decider file 5)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Round-2 questions: file 5 §7.

SEAT 9 POSITION, round 2 (phase 07c-1). This answers only the three items routed to Seat 9 in file 5 §7.

**Matter D, now/later (0–3)**
- **D1 at load, where the saved state had a tail: 3/3.** This is ≈ 3.3 s with no late energy. Beyond the critical distance that removes many dB of G, far more than the 1 dB jnd (Vorländer Table 6.1). It is a different room, not settling. It also breaks condition 9.
- **D1 for tailless (AX22) scenes: 0/0.** There is nothing to miss.
- **D2 on edits: 1/1.** The listener keeps hearing one real, consistent room, and the step that follows is the edit's own change. Seat 3's condition-4 conflict is theirs, not mine.
- **D4: 0/1.** It is exact, so it costs my seat nothing acoustically. It is out on Seat 4's and Seat 5's grounds, which are not mine.
- **D5 on T60 edits: 2/2.** It joins the new early part to the old decay, which is not a room that exists. For any T60 edit above 5 % the reverberance is wrong by at least the EDT jnd (5 %, Vorländer Table 6.1) until the exact tail lands. Conditions to lower it to 1: use D5 only where the old and new T60 differ by ≤ 5 % in every band from 500 to 1000 Hz, or keep it as Phase 10's room-size-automation path only, as recorded.
- **D3\*: 1/1, with two conditions:**
  1. **Minimum prefix length.** L_p ≥ 0.31 · T60 of the band, applied per band or at the longest T60. Arithmetic [Inf, H]: cut a decay where its remaining energy is x and the Schroeder curve reaches −10 dB early. EDT stays within 5 % only if (0.1 + 0.9x) ≤ 10^(−0.95), so x ≤ 0.0136, which is −18.7 dB, so L_p ≥ 18.7/60 · T60 = 0.31 · T60. The 1 dB level bound alone would need only L_p ≥ 0.115 · T60 (missing energy ≤ 20.6 %), so the EDT condition is the one that binds. At an 8 s T60 that means L_p ≥ 2.5 s, about 21 % of the 12 s tail. If cost scales with length, that is about 0.65 s of the 3.14 s synthesis [Hyp; Seat 3 owns the cost]. That would be above Seat 5's 0.5 s threshold, so reversal 1 may trigger in the long-T60 class.
  2. **No upward renormalisation.** "Normalised to expected energy" must mean the noise's unit energy, not scaling the cut decay up to the full tail energy. Scaling up would raise the early tail and C80 by up to the missing fraction (e.g. ≈ 1 dB at L_p = 0.115 · T60).

  The EDT test should be run on the whole provisional IR at 500 and 1000 Hz, against the exact IR. My cut-decay formula is a conservative tail-only stand-in for that test.

**B4-G: 0/1.** It meets my round-1 condition: SE ≤ 0.5 dB gives p95 ≈ 1.96 × 0.5 = 0.98 dB, which is ≤ 1 dB. Remaining condition: the gate must read the achieved SE per emitter and per band over 500 Hz–2 kHz, the bands where the AX16 cases and the jnd were measured. Below 500 Hz the jnd is not established, so the gate gives no audibility guarantee there [Hyp; Seat 1's ground]. The later 1 is evidence I cannot supply myself: 07c-2's stage-1 times, and whether the gate rejects most of the occupied class, layouts 4/5 at s = 1. Under 07c-2 those reach SE up to 1.33 dB (AX41), so in that class B4-G falls back to holding the previous level.

**Seat 7's split key (on an engine-part mismatch the saved E_b stays authoritative): 2/2.** It would let old projects keep a level the current build would not produce, whatever the size of the error. The AX16 history shows engine changes are not small: the AX16-to-estimator switch moved the level by +2.38 dB in the absorbing-floor cube and by +3.83 dB in layout 4 (AX16 row). Validation against BRAS and the Phase 12 presets is done on the solve, not on a stored value. My criterion 4 (honest inputs) breaks silently.
- **Condition to lower it to 1/1:** the saved E_b stays authoritative across an engine-part change only if that engine version's changelog shows |ΔE_b| ≤ 1 dB per band at 500 Hz–2 kHz on the validation set (BRAS CR2/CR3 plus the gated scenes, layouts 4/5 and the absorbing-floor cube), checked in CI against the D5 golden. Otherwise the solve runs and the saved E_b is at most the interim, under the D-C1 bound.
- **The decider's current policy ("any mismatch: saved E_b not used"): 0/1.**

**Hand-offs**
- **Seat 3:** the cost of L_p = 0.31 · T60 at 8 s.
- **Seat 1:** whether the EDT test should be on the whole IR, and the jnd below 500 Hz.
- **Seat 7:** the engine-change certification that would make the split key acceptable.

The decision file read: /home/user/makroof/docs/review/phase-07c-1/5-decider-decision-r1.md (§4, §7).