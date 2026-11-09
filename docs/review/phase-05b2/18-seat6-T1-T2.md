# Seat 6 (canvas designer) — positions on D-T1 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 6 POSITION — D-T1 (1.1–1.6) and D-T2

Corpus present (rev c1b171fe). One persona assumption no longer holds, as in my D-T5 position: FR-3D-4 exposes per-surface α and s, so "hide by physics" narrows to "each control does audibly what a real room does, and automates without surprises". From the code, `tailSeed` is a scene field with a module3d setter (`SceneModel::setTailSeed`). It is not a host parameter (`ScenePipeline.h` L11), and no phase plans a UI control for it yet. Emitters are the fixed L/R pair (schema L122–124), so an emitter-index key is stable.

**1. Reading.** The question is how the tail level is computed. For my seat that comes down to three things: how long the user waits between an edit and hearing it, whether placing the listener against a wall (an ordinary first-minute action, my B6 test "walk the listener to the back") stays cheap and correct, and whether automation steps stay small. The cues it triggers: positions that recompute heavily (S3); an automatic helper with a hidden trigger (W4); unpredictable settle time (W1: Altiverb was redesigned over an unpredictable 50–200 ms IR switch); and a hidden range limit (the picture lies).

**2–4. Ratings (now / later)**

**D-T1.1 Formulation**
- **T1-F: prefer. 1/1.**
  - Now: W1 takes 1.8–2.5 ms per emitter and 100 m takes 144–183 ms at SE 0.083 dB.
  - Later: cost depends on where the listener stands (C4), which is why D-T1.6 matters. It rises to 1/2 under NW-1 and to 3 under NW-1 with L2-F2 (see D-T2).
- **T1-B: cannot live with. 3/3.**
  - Now: the AQ10 room takes about 9 s per rebuild even at the hypothetical 2 ns per evaluation, so every source or listener drag in the reference room lags 9 s. That is 180× AQ10's 50 ms target.
  - Later: at 100 m a single generation takes 1 454–7 977 s. The canvas would show a festival field while the user hears the old room for hours. That is a de facto range limit, without even the honesty of a stated one (criterion 1 trust, criterion 6 "the picture never lies").
- **T1-A: cannot live with. 3/3.**
  - Now: under 1 GB it already fails in CR4 (42×42 m), which is an ordinary club or warehouse, the PRD's first preset category (FR-3D-3).
  - Later: D-T3 has two exits. One is a size ceiling, under which outdoor presets lose their size. The other is a formulation switch at a threshold, which puts a seam in the room-size control (W4 pattern). Undoing either means a contract major bump.

**D-T1.2 Seed** (rated under T1-F)
- **S-1: prefer. 0/0.**
  - A scene has the same tail level in every instance and on every machine.
  - A future "variation" or decorrelation control (stems in one scene, FR-3D-6) would change the noise only.
- **S-2: can live with. 1/2.**
  - It makes the seed a hidden second level control: one control moving two things (W2 cue).
  - At Tol-2 the shift is about 1 SE (0.083 dB), so two re-rolled stems differ by about 0.12 dB. At Tol-1 that grows to about 0.47 dB.
  - Later: a seed control added in the UI phase would inherit this side effect.
- **Cross-machine note:** no change to my ratings. C5 shows ≤ 7.5e-8 dB. Branch flips are Seat 5's.

**D-T1.3 N rule**
- **N-3: prefer. 1/1** if combined with NW-3, **1/2** with NW-1.
  - It is unbiased (F12, F14).
  - Its build time depends on position. NW-3 bounds that spread.
- **N-2: can live with. 1/2.**
  - Same position-dependent time as N-3, plus stopping on low means (F12): near-wall tails would read low.
- **N-1: can live with. 2/2.**
  - At a fixed N of about 22 000, a listener in a corner or edge reads −1.06 dB (W1 corner) to −3.9 dB (layout 4 edge) low (C4).
  - That is a tail that drops by up to about the 1 dB G jnd when the user backs the listener into a corner.
  - Its strength is predictable settle time and no N-change steps.
- **D-T2 dependence:** under L2-F2 all three rules inherit L2-F2's cost (below).

**D-T1.4 Tolerance**
- **Tol-2: prefer. 1/1.** Costs are in the ms range except layout 4 at s = 1 (≈ 1.5 s).
- **Tol-3: can live with. 1/2.**
  - It needs about 6.3× the paths of Tol-2: 100 m at about 0.9–1.2 s per emitter, layout 4 at about 9.7 s.
  - That buys a precision I am not told anyone can hear (Seat 1).
- **Tol-1: can live with. 1/2.**
  - Under B6-2, τ = 1 dB makes D-T6's bound 1.43 dB. Uniform rooms could then change audibly and still pass. That breaks §0.4's "nothing audible changes", and Phase 12 presets built on these rooms would shift.
- **D-T2 dependence:** L2-F2 overrides all three.

**D-T1.5 Case set**
- **CS-2 + CS-NW: prefer. 0/1.**
- **CS-3 + CS-NW: prefer. 0/1.** The cost is Seat 5's.
- **CS-1: can live with. 1/2.** It covers no room shape a preset would use.
- **Any set without CS-NW:** later rises by 1. No agreement case would put the listener within 0.5 m of a surface, and that is exactly the placement users make.

**D-T1.6 Near listener**
- **NW-3: prefer. 1/1.**
  - Specular entries and t_mix,e still follow the true position, and they carry the near-wall cue (the wall reflection within about 0.6 ms).
  - The clamped diffuse level moves ≤ 0.093 dB in W1, far below 1 dB (Seat 1 confirms).
  - Variance falls 4–7×. The clamp is continuous in position and needs no UI.
- **NW-2: can live with. 1/2.**
  - Edges and corners stay expensive, so settle time still depends on position.
  - It has two more constants, h and r_near, and τ must absorb a 1–3 % bias.
- **NW-1: can live with. 2/2.**
  - Edit-to-hear depends on position: about 0.25 s (W1 wall), about 2 s (edge), and up to minutes in layout 4 (1.4–47 M paths).
  - At N_max, it ships a tail that may read low.
  - **3 when combined with L2-F2** (below).

**D-T2**
- **L2-F1: prefer. 1/1.** It keeps Tol-2 costs. That pass/fail is itself random belongs to Seats 1 and 5.
- **L2-F2: can live with only under conditions. 2/3** with NW-1, **2/2** with NW-3.
  - Per emitter: W1 59–82 ms, 100 m 4.7–6.0 s, layout 4 about 51 s.
  - At a W1 wall: 7.1 M paths, about 8 s per emitter, so about 16 s per listener move in the AQ10 room.
  - Listener automation along a wall becomes 16 s stairs. The full IR waits on the diffuse solve (D-T4a (v)), so even the direct sound lags placement: "what you placed is not what you hear".
  - Under D-T4a's gate, 8 instances at 100 m take about 80–100 s until the last one is heard at load, which passes the 10 s escalation mark.
- **L2-P:** n/a (I cannot live with T1-A or T1-B). It is also not certified near walls (4.75 % per halving).

**5. Evidence**
- Update times: Vorländer Table 15.1 (corpus, re-read) gives 700 ms for the specular part and 3 s for the "scattering part" on moves > 1 m. It is about translation only, so applying it to room edits is an extension.
- G jnd: Vorländer Table 6.1 gives 1 dB at 500–1000 Hz; outside that range by extension.
- Measurements: builder evidence §3; C4 and NW tables (16-…); C5 and C6 (addendum); C8.
- Statistics: F3 [derived], F11, F12, F14.
- My incidents and cues: W1 (ASFX16), W2, W4.
- Times scaled to L2-F2 are my arithmetic on prototype numbers. C++ is unknown (O15) [Hyp].
- My ratings depend on D-T4a's gate (wait multiplies by instance count) and on D-T4c (time escalated, not blocked). Both survive.

**6. Conditions of acceptance**
- **L2-F2 → 1/1:** either one of two changes, plus a ruling from Seat 1.
  - (a) A Phase 10 split update in D-T4a (v)'s route. The specular part is heard within W1 timescales and the diffuse level lands later, inside Table 15.1's 3 s. Offline renders always use the final value.
  - (b) N_max, as a path count (so AX5 holds), sized so the worst gated per-update build is ≤ 3 s, with cap hits shown.
  - And: Seat 1 rules that 0.043 dB is not perceptual.
- **N-1 → 1/1:** combined with NW-3, with N fixed at the worst case of CS-x plus CS-NW.
- **N-2 / N-3 → 1/1:** N_max sized as in (b) above, and NW-3.
- **NW-1 → 1/1:** not reachable except through NW-3's variance reduction.
- **S-2 → 1/1:** the UI never exposes the seed, or names it as "variation (also nudges level ≤ x dB)".
- **Tol-1 / Tol-3 → 1:** Tol-1 only with B6-1 (per room) instead of B6-2. Tol-3 only with (a).
- **CS-1 → 1:** add CS-NW and at least the six Phase 04 rooms.
- **T1-A / T1-B:** no change within the option lowers them. T1-B drops to 2 only if C8 is measured in C++ at AQ10 ≤ 0.7 s and 100 m ≤ 10 s.

**Should the user see a cap hit?** Yes, never silently degraded (S6). But:
- only on the settled scene, never flickering during a drag (W4);
- worded in listener terms ("tail level approximate here, ±x dB");
- shown in the info view, the scene's "where the simulation stops" note (Strategy E5).

If it appears in ordinary placements, the design has failed, not the user [Hyp]. NW-3 should make it rare.

**7. Hand-offs**
- **Seat 1:** audibility of NW-3's 0.03–0.09 dB, of 0.043 dB, and of near-wall low readings.
- **Seat 2:** whether NW-3 is the same model to a stated tolerance; the NW-2 h choice.
- **Seat 5:** N_max as a path count; cap-hit escalation.
- **Seat 9:** whether a 0.5 m clamp is physically honest.
- **Seat 7:** public wording of the cap-hit note.
- **UI phase:** the settled-state indicator.

**Checks for the orchestrator**
1. **C6 extension:** a listener sweep near walls, 0.1 → 1 m off the wall, 1 m along it at 0.1 m, and into a corner, at N-1, N-2 and N-3, under NW-1, NW-2 and NW-3. Report the largest adjacent step per band. C6 swept only the source, at reference positions. With single paths carrying up to 73 %, a 10 cm listener move could step well above C6's ≤ 0.037 dB [Hyp].
2. **NW-3's E_target change** in a concentrated-absorption room: only W1 has been measured.
3. **Per-update time for both emitters** at near-wall positions, per N rule and τ.

**Check for the researcher:** any published interval between a room or material edit and hearing it (still Table 15.1 by extension only).

**8. Premortem.** If L2-F2 ships with NW-1, a producer drags the listener to the back wall of an ordinary hall and hears the old room for about 16 s, and listener automation along that wall plays as stairs. Maisara notices first at the Phase 10 sweep check, or a beta user does on their first scene.
