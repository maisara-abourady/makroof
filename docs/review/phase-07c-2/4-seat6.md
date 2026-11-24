<!-- Saved by the orchestrator from seat 6's report, 2026-11-22. -->

SEAT 6 POSITION — D-W1 and D-W2 (phase 07c-2, round 1)

Corpus present (SOURCE_COMMIT c1b171f). Read: the convening (file 1), fact sheets part 1 and part 2 (T1–T5), the researcher dossier (file 3), phase-07c-2.md, BUILD_PLAN AX38/AX44/AX47–AX49, my 05h file 5 L29, and Vorländer §15.3 Table 15.1 in the corpus.

# D-W1: W_max under (C)

**1. Reading.** This sets the per-emitter work cap. For the user it decides two things: how long "settling" shows after a load or an edit at a capped room, and what a keyless load or a plugin insertion costs while the host waits. Cues: positions that recompute heavily (S3); a settle time the user can't predict (W1); a note at a default placement (AX44 (ii)); an automatic level step after the user stops (W4).

**Facts that change my 05h reading:**
- **Table 15.1 doesn't hold as a budget.** Its rows are VR filter-update intervals for listener or source movement (> 0.25 m gives 700 ms; > 1 m gives 3 s). They are not a load or solve budget, and the table says nothing about threads (corpus Vorländer §15.3; researcher R29). My 3 s is therefore a user-facing settle anchor, applied by extension. It is not an acoustic limit.
- **The per-scene reading stands.** The gate serialises one solve per process (AX38 (i)), so the user waits for W_scene.
- **"Costliest gated scene" sets no bound.** Both gated cubes saturate: low-α at 1.26× the pin's work from ×2, flutter at 3.29× from ×4 (T1, finding 2). The bound has to be read against W_scene as realised at capped scenes, where realised work ≈ W_scene (T1: 0.91–1.03).

**W-1 value, my arithmetic** (3 s divided by the single-thread ns per scene evaluation):
- Linux: 44–56 ns on CI (05h bench, F2) and 43–63 ns in the local 07c-era sweep (T2). That gives 47.6–53 M per scene, about ×8 the pin (≈ 24 M per emitter).
- Windows: 38.4 ns, about ×13.
- macOS: 28.7 ns, about ×17.
- Measured (T1, local single thread): capped layouts at ×8 take 2.06–2.89 s; at ×16, 4.2–5.3 s.

**2–4. Ranking and tension (now / later):**

| option | rating | now / later | reason |
|---|---|---|---|
| **W-5** = min(W-1, Seat 8's bounce term), with W-4 kept as a record and W-6 as a sufficiency check (this composition is my own) | **prefer** | 1 / 1 | Lands at about ×8. At ×8 every non-both-near layout-4/5 placement has SE ≤ 0.33 dB and U = 0. At ×4, listener_edge (0.378 dB) and listener_corner (0.426 dB) still raise U (T3). |
| **W-1** (3 s per scene, single thread, worst OS, read on W_scene) | **prefer** | 1 / 1 | Settle ≤ 3 s per edit on a busy machine. |
| **W-6** (as a rule on its own) | can live with | 1 / 1 | It doesn't stop unless both-near is excluded. Those cases keep U = 1 at every W (VOV_union 0.41–0.55 at ×16). AX44 already flags them, and the flag is true. Without both-near it gives about ×8, the same as W-1. |
| **W-2** (3 s per emitter) | can live with | **2 / 2** | About ×16: single-thread settle of 4.2–5.3 s at capped scenes, past the 3 s anchor. This is the error I corrected in 05h. |
| **W-3** (3 s at the pool size) | can live with | **2 / 2** | Assumes idle cores in a DAW session. Allows about ×32 or more, so a busy machine settles in 10–20 s [Inferred from T1/T2]. Core counts come from Steam gamers, not producers (R21). |
| **W-4** (8 instances settled ≤ 10 s) | can live with as a record only | **2 / 2** as a W term | At the pin it is already over 10 s at 96 kHz: 12.0 / 12.8–13.3 / 9.7–9.9 s on Linux / macOS / Windows (F6 (b)). That time is synthesis, which W cannot move. So it either forces (A), which is out of bounds, or binds nothing. |

**Keyless consequence beside each option:**
- **K-a** (synchronous stage-1 at the new W):
  - W-1 and W-5 at ×8: 1 / 2. The gated cubes stay under 30 s (F12: ≤ +0.37 s and ≤ +5.6 s). But a keyless restore in a capped user room grows by about +0.35–0.45 s per instance [Inferred: T1 pool at ×8 halved for CI], so 8 instances add about 3–4 s of frozen host. The s = 1 cube projects to 35–39 s against the 14× convention at ×8 (F12; it is not gated).
  - W-2: 2 / 2.
  - W-3: 2 / 2. That is my 05h premortem, a host frozen for 15–20 s.
- **Instance insertion (FM-B2) is a keyless load of `medium_room`, the plugin default, and that matters most.** At the pin it is work-stopped and floor-truncated. Once raised, its pilot runs to 1 024 histories, about 32 M evaluations (≈ ×5.2), giving about 0.3–0.8 s on the pool and 1.4–1.8 s on one thread [Inferred from F5: 3.97 M per 256 histories]. That is close to the 1 s anchor on the user's most frequent action.
- **K-b** (stage-1 at the (A) work as an interim): 1 / 2 under every option. At ×1 against ×16, the drift is 1.15 / 1.25 dB at layout-4 listener_edge and 0.42 / 0.57 dB at emitter_wall (T3). That exceeds the AX47 bound at some capped placements, so the user hears a jump during "settling" (W4).
- **K-c** (another fallback): 1 / 2 [Hyp]; it is unspecified.

**Sequencing.** I accept deciding the value now and the keyless path after the ABX, on one condition. **W must be acceptable under K-a alone**, because K-b may come out inadmissible (the ABX, or the layout-4 drift above). The value decision should carry the K-a and insertion costs measured at the chosen W. Otherwise the keyless round inherits a W it cannot cut (AX38 4c (d)), and that would be borrowing from it.

**5. Evidence.**
- From the code and the fact sheets: T1–T5, F2, F5, F6, F9, F10.
- Corpus: Vorländer §15.3, Table 15.1 (conditions differ).
- Persona incidents: W1 (ASFX16: an unpredictable switch time forced a redesign) and W4 (VSL Natural Volume: an automatic level jump).
- [Inferred]: the `medium_room` insertion cost and the CI pool times at capped scenes. **Orchestrator to measure:** the insertion and keyless restore of `medium_room` and the six Phase 04 rooms at the candidate W, on three OSes, pool and one thread.

**6. Conditions of acceptance.**
- **W-2:** read per scene, which turns it into W-1, then 1 / 1.
- **W-3:** accept only if it lands ≤ the W-1 value, then 1 / 1.
- **W-4:** demote it to an AX38 (iv) record at the chosen W. Measure it also at a capped 100 m scene (whether F6 (b)'s cube is capped is not on file) and treat a result over 10 s as a finding. Then 1 / 1.
- **K-a, for every option:**
  - plugin insertion of `medium_room` measured at ≤ 1 s at the pool size on the worst shipping OS;
  - 8 × capped-100 m keyless load recorded against the 1 / 3 / 10 s anchors.
  - If insertion exceeds 1 s, insertion is routed to the class (c) round. W is not cut.

**Companion items.**
- (b) Not my matter. The double-count correction means my 05h check ("0.136 s per emitter") should read about 0.27–0.34 s per scene at the pin on one thread (T1). It is still well inside 3 s.
- (c) Seat 5's form; no objection.
- (d) Seat 2's. User-side condition: the golden round prints ΔE_b per band at every user-reachable default, because the work-stopped `medium_room` and `asymmetric_materials` move. Any change over 1 dB is named. A benefit: any W ≥ ×4 removes the cap hit at `asymmetric_materials` (W_uncap ×2.46) and the floor truncation at the plugin default.
- (e) Keep v2, 0 / 0. A keyless load shows no warning (F10). Pre-release only.
- (f) Confirmed. Phase 12 (ii) runs at 07c-2's W. The note shows only on the settled scene (AX44), so an interim cannot raise it.
- (g) Not my matter.

**7. Hand-offs.** Seat 2: the W value and the ns basis per OS. Seat 5: the gate under K-a. Seat 8: the bounce term. Seat 7: no copy may say large rooms load or settle fast.

**8. Premortem.** If W-3 or W-2 wins, the first beta producer who inserts several instances in a large reflective room watches "settling" for more than 10 s and the host freeze at reopen. The beta tester notices first.

# D-W2: AX47 self-ABX and L4 design

**1. Reading.** The stimulus has to be the L1 moment: the project loads, the user presses play, the room plays at the interim level, then one AQ4 crossfade steps it to the final. Cues: an automatic level step (W4), and silence is not approval (W3): a "not detected" from an under-powered test is silence.

**2–4. Ranking (now / later):**

| option | rating | now / later | reason |
|---|---|---|---|
| **X-3**, with an anchor first (my variant) | **prefer** | 1 / 1 | Order: an anchor step known to be audible (e.g. 3 dB, which must be detected, otherwise the run is invalid as insensitive; BS.1116 §6, R4), then 0.75 dB, then 0.5 dB. Noise before speech, the more sensitive first. 12/16 at each step, family-wise error 0.038 (R1). |
| **X-5** built on X-3 | **prefer** | 1 / 1 | Same, plus the power statement: at 12/16, power 0.63 at p = 0.75. |
| **X-1** | can live with | 1 / **2** | Uncorrected over the two stimuli, the family-wise error is 0.075 (R1). A false 0.5 dB reversal forces K-a and longer loads. It has no anchor. |
| **X-4** | can live with | 1 / **2** | Rewrites AX47's 16 trials (needs a board DECISION) and adds listener time. |
| **X-2** | can live with | **2 / 2** | At 13–14/16 it misses a real effect 60–80 % of the time at p = 0.75 (R1). Audible steps pass as "not detected", and the user hears jumps at settle. |

**Sub-items in my mandate:**
- **The step is the shipped transition:** the AQ4 equal-gain crossfade between IrSets differing only in per-band tail level.
- **Inside ongoing program:** the step falls at a random time within a pre-registered window (e.g. 3–7 s), never at onset. A is no step; B is a step.
- **Both directions**, balanced and pre-registered, because the interim drift is signed (T3).
- **The capped layout-4 scene at its default placement** (the user's position). It stays capped up to ×8 (T3).
- **The output as a producer hears it at defaults.** Fully wet is more sensitive. That is the Seat 8 / Seat 1 call, and I accept it as the conservative case.
- **No visual cue:** "settling" is not shown.
- **L4:** place the handover where record (h) puts it after load (roughly 1–2 s for one instance), not at a fixed point.
- **Record wording:** "not detected by one listener, 16 trials". Never "seamless" in the UI or copy.

**Debt.**
- If an under-powered test admits K-b: jumps at settle show up first in the 07c-2 L1 checklist, then at 08-3 binaural on headphones (more revealing [Hyp]), then with beta testers (13). Undoing it means a class (c) re-decision and code-path removal, about part of a phase.
- A false detection tightens the bound to 0.5 dB, which forces K-a. That cost goes into D-W1's insertion condition.

**6. Conditions of acceptance.**
- **X-1:** use the fixed sequence over the two stimuli, plus the anchor, then 1 / 1.
- **X-2:** replace it with X-3; I see no lower variant.
- **X-4:** pre-register the trial count and report against 1 dB with a confidence interval, then 1 / 1.

**7. Hand-offs.**
- Seat 1: the paradigm and the sizes.
- Seat 3: the crossfade law.
- Seat 4: the chain, and a re-check at 08-3.
- Seat 7: the speech licence (LibriSpeech is CC BY 4.0, R23) and the wording.
- Seat 8: wet context.

**8. Premortem.** If X-2 wins and a 0.75 dB step goes "not detected", K-b is admitted. The first producer who reopens a large room hears the tail jump as "settling" clears, and Maisara notices first at the L1 checklist.
