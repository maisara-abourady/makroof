# Seat 4 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 4 POSITION (second round): D-T1.6, D-T1.3, D-T2 (phase 05b session 2)

The corpus is present (Roginska and Geluso, Begault). This round covers only what changed since my first round (18-seat4-T1-T2.md). Two assumptions carry over from it: D-T5.3 (the binaural tail is isotropic; Phase 08 gets E_b and t_mix,e only) and D-T4a (v) (E_b is held under head rotation).

**1. Reading.** Three things are on the table:
- NW-4C, a two-ended blend for near-wall positions.
- N-3W\*, a pilot run followed by a fresh final range, under a work cap.
- L2-F1R, the strict < 1 % reading of AX36, at about 20× Tol-2's paths.

They trigger three of my §4 cues:
- **Per-mode rebuild headroom.** AQ10 allows ≤ 50 ms for a rebuild in "every output mode from Phase 08". W1 is 20.6 ms today (BUILD_PLAN §0 row 04).
- **Level parity across modes and ears.** Phase 08 allows ±1 dB.
- **Room cues near walls.** A tail that reads low gives a wrong DRR and a dry, in-head render. Corpus: Roginska L1067, citing Begault, Wenzel and Anderson (2001): reverberation or head tracking helped mitigate internalised sound.

**2–4. Ranking and tension (now/later)**

**(a) D-T1.6, NW-4C: prefer. 0/1.**
- **Why it suits my chain:**
  - The blend is unbiased and changes no model.
  - With one end near a surface, its SE equals the SE at the reference positions: 0.013–0.016 dB in W1, 0.068–0.114 dB in layouts 4 and 5, with the largest single-history share ≤ 0.54 % (C12 (a), reading 1).
  - Listener sweeps step ≤ 0.04 dB per cm, and the emitter crossing d_E = d_L steps ≤ 0.026 dB (C12 (b)). That is about 1/25 of my ±1 dB parity budget.
  - The cost at the reference positions is a median of 1.02× forward-only (C12 (c)), so W1 headroom is unchanged.
  - E_b remains a single omni value with no dependence on head yaw (builder §2), so rotate-before-decode is intact.
- **Later 1, for the both-near case:**
  - At 32 k histories, SE is 0.22–1.27 dB and VOV is up to 0.95. The 32 k and long runs differ by up to −5.2 dB (layout 4, both_corner).
  - With a heavy tail, a capped draw typically reads low. That is a dry tail exactly where a producer has put the amp and the listener against walls. [Inferred from C12 (a) rows; how often producers build such scenes is Hyp, Seat 8.]
  - The step from 0.11 to 0.10 m is 0.21 dB (C12 (b)).

**(b) D-T1.6, NW-3 re-rated: can live with. 1/2. My first-round cell changes from "prefer, 0/1".**
- **What changed:** I rated NW-3 on "+0.03 to +0.09 dB (W1)". The measured clamp is:
  - +0.322 dB at layout 5's absorbing wall;
  - +0.109 dB at layout 4's absorbing floor;
  - −0.11 dB and −0.25 dB at layout 4's wall and edge.
  
  (Sources: 19 §6 and §4.)
- **Now 1:** the shift is systematic and identical in every mode, so parity holds. But it moves DRR by up to 0.32 dB next to absorbers, which is common in producers' room designs (booths, treated walls) [Hyp on how common].
- **Later 2:** the bias exceeds τ (0.25 dB), so the CS-NW+ agreement suite would have to exclude or fail the absorbing-face cases. My criterion 2 (measured against a reference) then has a hole at exactly the positions where the clamp acts. Undoing it costs a model change plus a golden round.
- **Why it now ranks second:** NW-4C buys the same variance gain without the bias, so NW-3 is dominated.

**(c) D-T1.3, N-3W\* as composed: can live with. 2/2.**
- My first-round condition (a final range whose start does not depend on N) is met.
- **Now 2, from W1 headroom (the pilot, not the final range):**
  - In W1 the 8 000-history pilot is 10 % of W_max, about 1.46 M image evaluations per emitter. Tol-2 needs only 607–672 histories there (C12 (d) table).
  - At the 9 ns per evaluation measured on cube100 at 4 threads, that is about 13 ms per emitter, or about 26 ms for two. At 1 thread (34 ns) it is about 100 ms.
  - So W1 per mode becomes about 47 ms or about 120 ms, against the 50 ms target, before Phase 08's HRIR early part. With a minimum final N ≥ n\* it becomes about 73 ms at 4 threads.
  - These are Inferred: the W1 cost per evaluation has not been measured, and the C++ cost is Hyp.
- **Now 2, from conflict 1 (the 8 000-history pilot exceeds W_max in W2 and the 100 m flutter cube, leaving no final range):** the composition does not say what is shipped when the final range is empty. A missing or zero tail would be veto-grade for me (a dry render). I rate the variant 2, not 3, only because the decider sent this conflict back to the seats.
- **Later 2:** whatever pilot size is chosen becomes a fixed per-scene cost inside every per-mode W1 record.

**(d) D-T2, L2-F1R: can live with. 2/2.**
- **Now 2:**
  - W1 rises by +72–100 ms for two emitters at 1 thread (decider's working, 21 §D-T2), or about 66 ms at 4 threads (C12 coupling: 0.24–0.26 × W_max per emitter).
  - W1 per mode is then about 87–120 ms against 50 ms in every output mode, so the update interval roughly doubles. That is still inside Vorländer Table 15.1's 700 ms translational row (corpus L3961–3966).
  - At 100 m the restore takes about 3.7 s against 2.14 s.
  - The precision it buys (SE 0.0187 dB, about 1/50 of the G jnd) moves nothing I measure: the error is shared across modes and ears, so parity is unaffected.
- **Later 2:**
  - It makes the split update (hold E_b, update the HRTF and specular part) mandatory before Phase 08 item 8 closes.
  - Every per-mode record carries the diffuse share.
- **Not 3:** none of the things I never trade (HRTF provenance, compensation, the rotation stage, the listening test) is touched.
- **Which reading suits my criteria:** the bias reading. The ruling is Maisara's.

**5. Evidence**
- [C12 (a)–(d)] Every SE, VOV, step, cost-ratio and W_max figure above, from 22-orchestrator-C12.md.
- [19 §4, §6] NW-3's clamp shifts.
- [BUILD_PLAN §0 row 04; AQ10] W1 is 20.6 ms; the rebuild target is 50 ms in every output mode.
- [Corpus] Roginska L1067 (reverberation or tracking reduces internalisation); Vorländer Table 15.1.
- [Inferred] The W1 per-mode times above, scaled from cube100's cost per evaluation.
- **For the researcher or orchestrator to verify:** whether a pilot smaller than 8 000 histories still raises VOV ≥ 0.1 in C12 (a)'s both-near cases.

**6. Conditions of acceptance**
- **NW-4C to 0/0:**
  - The listener-started set starts at the head centre, never at the ear positions, and one set serves both ears and every mode.
  - A test shows E_b bit-identical between `--mode omni` and `--mode binaural` and between the two ears.
  - The both-near flag ("near-wall, unreferenced") is written to TailMatch and the diagnostics.
  - The listening pack carries one both-near binaural render.
- **NW-3 to 1/1:** only if a measured clamp radius brings the layout 5 absorber bias below τ/2. Otherwise NW-4C supersedes it.
- **N-3W\* to 1/1:**
  1. Define the pilot in work, sized so that the diffuse solve (pilot plus final) takes ≤ 25 ms of the C++ W1 record for two emitters, under the conditions AQ10 is measured in. This is my round-1 condition, carried over.
  2. Start the final range at a fixed constant index, at least as large as the biggest possible pilot. Its start must then depend on neither N nor n\*. A work-defined n\* changes in integer steps as the listener moves, so a final range starting at n\* would step under automation.
  3. If the final range is empty (conflict 1), ship the fixed-size pilot estimate, flagged. Never ship a zero or missing tail. The pilot is a fixed-n estimate, so it carries no stopping bias.
  4. Compute the pilot size and the cap before sampling: from geometry, or from the pilot's mean evaluations per history. Never stop on realised work, because path cost correlates with score and a stop on work could bias the tail [Inferred; physics to Seat 2].
  5. Compute N, the pilot and the flags once per scene, shared across modes and ears.
  
  On conflict 2, I need no minimum final N. The final SE of 0.07–0.10 dB is shared across modes and ears, so it does not touch parity. If the board adopts a minimum, it counts inside condition 1.
- **L2-F1R to 1/1:** my round-1 L2-F2 conditions:
  - the diffuse solve runs once per scene, shared across modes;
  - the split-update AX is scheduled before Phase 08 item 8 closes;
  - per-mode records show the diffuse share.

**7. Hand-offs**
- **Seat 1:** whether a 0.21 dB step per cm in the tail, or a ±0.3 dB DRR error in both-near scenes, is audible.
- **Seat 2:** whether stopping on realised work biases the estimate; the clamp-radius physics.
- **Seat 5:** C++ W1 timing and the size of the work-defined pilot.
- **Seat 6:** whether the user sees the "near-wall, unreferenced" flag.
- **Seat 8:** how often producers place both the emitter and the listener against walls.
- **Maisara:** the AX36 reading.

**8. Premortem.** If N-3W\* ships with the 8 000-history pilot, W1 per mode exceeds 50 ms once Phase 08 adds the HRIR early part. In the hard-walled scenes the empty final range ships no tail, so the render goes dry. Seat 5's Phase 08 W1 record catches the first; Maisara's listening checklist catches the second, as an "inside the head" answer.
