# Seat 4 — confirmation S4-a (D-T1.3 N-3W***)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 4 POSITION: confirmation S4-a, D-T1.3 N-3W\*\*\* (decider round 3, file 29)

This round answers only what changed. My round-2 position is in file 23-seat4.

**1. Reading.** N-3W\*\*\* revises the pilot rule in three ways:
- The pilot now stops on realised work, at a block boundary, at n\*_max or W_scene/2, and is then discarded.
- N and N_cap are fixed from the pilot before any final history is drawn.
- The final range is [8 000, 8 000 + N).

My §4 cues:
- **Per-mode rebuild headroom.** AQ10 targets an IR rebuild ≤ 50 ms "every output mode from Phase 08"; W1 is 20.6 ms today (BUILD_PLAN §0 row 04).
- **Level parity across modes and ears.**
- **No stopping bias towards a low (dry) tail.**

**My round-2 conditions, checked against file 29 §D-T1.3:**
- **(1) W1 diffuse share ≤ 25 ms.** Met provisionally: n\*_max is sized to it, at about 1 020 [Inferred, prototype], to be re-derived from the C++ cost.
- **(2) Fixed final-range start, independent of N and n\*.** Met: the range starts at 8 000 with n\*_max ≤ 8 000. A position-driven change in n\* or N only extends or shortens the end of a range whose start never moves.
- **(3) Never ship a missing tail.** Met: if N_cap is under one block, the pilot estimate ships, flagged.
- **(4) No stopping on realised work.** Met for everything published.
  - The final estimate is drawn on a disjoint RNG range at an N fixed beforehand, so it is unbiased given N.
  - The pilot's work-stopping affects only N and the cap, never the published value.
  - **One residual:** in the ship-the-pilot fallback, the published value is a work-stopped sample. Its bias is of order 1/n\* [Inferred]. C14 shows no gated scene where that fallback fires: the flutter cube keeps a final range (N = 313); W2 is pre-registered for the pilot floor, not this fallback (27 C14 §(a) table; 29 CI expected flags).
- **(5) Once per scene, shared across modes and ears.** Met (29 §D-T1.6: one head-centre listener-started set serves both ears and every mode).

**2. Ranking**
- **N-3W\*\*\* with n\*_max from my condition 1 (about 1 020):** prefer.
- **N-3W\*\*\* with n\*_max = 8 000 fixed:** can live with.

**3–4. Tension now / later**

**N-3W\*\*\*, n\*_max about 1 020: 1/1.**
- **Now 1:**
  - The diffuse share of W1 is ≤ 25 ms by construction. That leaves about 25 ms of the 50 ms target for Phase 08's binaural early part.
  - The achieved SE is about 0.06 dB in W1-class rooms and ≤ 0.124 dB in the Phase 04 near-wall cases (27 C14 near-wall table; 29 Q2b(i)), i.e. ≤ 0.12 of the G jnd.
  - That error is identical in every mode and in both ears, so the ±1 dB parity budget is untouched.
- **Later 1:**
  - The value is provisional until the C++ cost is measured (Q2).
  - If the C++ cost pushes n\*_max below the 1 000 floor, the floor (Seat 1's precision) has to win over my 25 ms. My now-rating would then rise to 2, by however much the diffuse share exceeds 25 ms in the per-mode W1 record.
  - Undo cost: one parameter and one golden round before release (29 debt register, S4 row).

**N-3W\*\*\*, n\*_max = 8 000 fixed: 2/2.**
- **Now 2:**
  - The diffuse solve takes about 0.25 s per W1 rebuild on the 1-thread prototype (29 §D Q2b(ii) [Inferred]). With N ≥ n\*, W1 per mode comes to about 0.27 s against the 50 ms target, about 5×, in every output mode.
  - Moved sources and listener update about every 0.3 s instead of every 50 ms. That is still within Vorländer Table 15.1's 700 ms translational row (as quoted in AQ10).
  - The precision bought (SE about 0.023 dB against 0.06 dB) moves nothing I measure: both errors are shared across modes and far below the ±1 dB parity budget.
- **Later 2:**
  - The split update (E_b held under head rotation, D-T4a (v)) becomes mandatory before Phase 08 item 8, which checks the 35 ms head-rotation row.
  - Every per-mode W1 record is a recorded miss until Phase 13.
- **Not 3:** E_b does not depend on head yaw (builder §2), so the rotation stage, HRTF provenance, compensation and the listening test are all intact.

**5. Evidence**
- [29 §D-T1.3, rule text] Pilot, final range, N_cap and fallback.
- [29 §D Q2b] Cost of n\*_max = 8 000 against about 1 020.
- [27 C14 near-wall and small-room sections] Final SE ≤ 0.082 dB at n\*_max 8 000 and ≤ 0.124 dB at 1 020; flutter cube n\* 314, N 313; the small room's final SE is 0.0062 dB at 8 000 and 0.0134 dB at 1 020.
- [BUILD_PLAN AQ10] The 50 ms target in every output mode, and the Table 15.1 700 ms row.
- [Inferred] The order-1/n\* bias in the fallback; prototype timings.
- **For Seat 2:** bound the work-stopped pilot's bias, in case the fallback ever ships.

**6. Conditions of acceptance**
- **n\*_max = 8 000, to 1/1.** Either of these:
  - the measured C++ W1 diffuse share at the CI runner's pool size is ≤ 25 ms for two emitters; or
  - an AX lets E_b refresh on its own slower interval. Table 15.1's scattering-part row (3 s for moves > 1 m) is already noted in AQ10 as a Phase 10 cache option, so the specular and HRTF part keeps the 50 ms path. Whether a held E_b during movement is acceptable is for Seats 1 and 3.
- **Both variants:**
  - The CI report lists any fixture or preset where the pilot estimate ships, so the fallback bias is visible if it ever fires.
  - The Phase 08 bit-identity test of E_b (omni against binaural, left ear against right) stays (29 §D-T1.6).

**7. Hand-offs**
- **Maisara:** Q2b, the choice between n\*_max sized to the W1 target and 8 000 fixed.
- **Seat 2:** the bias of the work-stopped pilot.
- **Seats 1 and 3:** a held E_b during movement, if that condition is pursued.
- **Seat 5:** the C++ cost per evaluation and the pool size.

**8. Premortem.** If n\*_max is fixed at 8 000 without the split update or an E_b refresh interval, every output mode rebuilds at about 0.27 s. Then Phase 08's per-mode W1 record misses 50 ms by 5×, and head rotation fails item 8's 35 ms row. Seat 5 notices first, in the Phase 08 benchmark.
