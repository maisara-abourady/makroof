# Seat 6 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 6 POSITION: second round on D-T1.6 (NW-4C, NW-3 re-rated), D-T1.3 (N-3W\*) and D-T2 (L2-F1R)

I did not re-read the corpus this round. The two corpus facts below are cited as in my first round (`18-seat6-T1-T2.md`) and the decider's re-read (`21-…` header).

**1. Reading.** The question is what a producer gets in three situations: dragging the listener or a source toward a wall, waiting after an edit in a large room, and the tail level stepping during automation. Cues from my §4 that this triggers:
- positions that recompute heavily (S3);
- an automatic helper with a hidden trigger (W4);
- a flag that fires on ordinary placements (§6 S9 and my round-1 cap-hit condition);
- unpredictable settle time (W1).

**2–4. Ratings (now/later)**

**(a) D-T1.6 NW-4C: prefer, 1/1.**
- **Now, one end near a surface.** The listener sweeps step ≤ 0.040 dB per cm, with N almost constant (1 016–1 524) and 0 cap hits (C12 (b)). The emitter crossing d_E = d_L is continuous, ≤ 0.026 dB. With one end near a surface, the SE equals the SE at the reference positions (C12 (a) reading 1). This removes my round-1 nightmare: NW-1 with N-2 stepped 0.358 dB along a wall (19 §4).
- **Now, no model change.** Specular entries and the true positions drive everything (C12 "As implemented"), so the picture tells the truth.
- **Now, both ends near a surface.** In W1 there is a 0.21 dB step between 0.11 and 0.10 m, and the capped final SE is 0.15–0.29 dB with VOV 0.29–0.32 (C12 (b) reading 4). That is ≤ 0.21 of the 1 dB G jnd, and it is flagged. In a small room, an amp against a wall with the listener against another wall is an ordinary placement, so that flag must be worded well (conditions below).
- **Later.** Two path sets in C++; cost is 0.44–2.57× forward-only at the reference positions (median 1.02×, C12 (c)). One unexplained one-end draw remains: layout 4 emitter edge, −0.273 dB, z ≈ −3.7. Evidence that could overturn this arrives with C++ W1/W2 timing (O15) and the first CS-NW+ CI run.

**(b) D-T1.6 NW-3 re-rated: my round-1 cell changes from *prefer 1/1* to *can live with 1/2*.**
- My round-1 premise was "≤ 0.093 dB in W1". The measured clamp bias is:
  - +0.322 dB at the layout-5 absorbing wall;
  - +0.109 dB at the layout-4 absorbing floor;
  - −0.11 / −0.25 dB at the layout-4 wall and edge (19 §4, §6).
- **Now: 1.** These are below the jnd (Seat 1's ground). The direction matters for my seat, though: a producer who backs the listener against an absorber to deaden the sound has part of that effect undone by a hidden 0.5 m rule. The sign of the error depends on the material, which the user cannot see.
- **Later: 2.** The bias exceeds τ = 0.25 dB, so the near-wall cases (where users put listeners) cannot be gated. A near-wall regression would then pass CI unseen. NW-4C gets the same variance benefit without the bias, so NW-3 is no longer my preference.

**(c) D-T1.3 N-3W\* as composed: cannot live with, 3/3. With the conditions below: prefer, 1/1.**
- **Conflict 1.** The 8 000-history pilot costs 3.1× W_max in W2 and 2.7× in the gated 100 m flutter cube, which leaves n_cap = 0 and no final range, although those scenes need only 1–16 histories (C12 (d) reading 3).
  - A hard-walled room the user picks would get either no defined diffuse level, or a cap flag on every placement.
  - The only other way out is to overrun the restore bound.
  - Each outcome breaks one of my two criteria that are never traded: criterion 1 (what you placed is what you hear) or criterion 6 (the picture never lies). This is a defect in a definition, and it is cheap to fix.
- **Conflict 2.** The final N (60–6 200) is below the discarded pilot. The final SE is 0.07–0.10 dB, and above 0.083 dB in 6 of 17 cases (C12 (d) continued, reading 3).
  - That is ≤ 0.1 jnd, so it is not audible to my knowledge.
  - It does matter to motion. The step between neighbouring positions is bounded by about √2·SE (C12 (b) reading 1), so a smaller final SE means smaller steps when the user drags.
  - A fixed minimum N also makes settle time predictable (the W1 lesson).
- **My 3 s per emitter bound is met.** W_max is about 0.13 s per emitter at 4 threads and about 0.51 s at 1 thread on the prototype (C12 (d)). The C++ cost is unmeasured [Inferred, C12].
- **Cap hits.**
  - 0 of 17 on CS-NW+ and the Phase 04 near-wall cases.
  - All 51 points of the crossing sweep hit the cap, with a final SE of 0.081–0.128 dB. That is an ordinary placement in a 30 m room: listener 0.3 m off one wall, emitter near the far wall. Its result is fine, so a bare cap hit must not be what the user sees.
  - 38 of 91 points of the both-near sweep hit the cap.
- **Slope flag.** The slope estimate is 2.93 even at the W1 reference positions (C12 (e)). As a user-facing flag it would fire everywhere.

**(d) D-T2 L2-F1R: can live with only under conditions, 2/2.**
- **Now.**
  - At the gated 100 m scene it needs about 7× W_max: about 1.9 s for two emitters at 4 threads, so a restore of about 3.7 s against 2.14 s (C12 coupling section).
  - Single-threaded it is 2.85–3.62 s per emitter (decider's working in `21-…` D-T2), which exceeds my 3 s bound.
  - The precision it buys is 0.0187 dB, about 1/50 of the jnd. Nobody has told me that anyone can hear it.
- **Later.**
  - If W_max holds, the cap binds at the reference positions of the 100 m scene. The user-facing flag would then appear on a preset's default placement, which counts as the design failing.
  - If W_max is raised instead, the restore bound breaks, and that veto is Seat 5's.
  - Under D-T4a's gate, 8 instances × about 1.9 s ≈ 15 s, which passes the 10 s escalation mark [Inferred].
- **Not 3.** With NW-4C, round 1's 16 s per listener move along a wall no longer happens. W1 needs only 0.24–0.26 of W_max.

**5. Evidence**
- From C12 (`22-orchestrator-C12.md`):
  - (a) NW-4C table and readings 1 and 3;
  - (b) sweep table and readings 1–4;
  - (c)/(d) cost, pilot and W_max tables, readings 1–4;
  - the coupling section.
- 19 §4 (clamp bias in layout 4; the 0.358 dB step under N-2) and §6 (+0.109 dB and +0.322 dB at the absorbing faces).
- Corpus:
  - G jnd 1 dB at 500–1000 Hz, Vorländer Table 6.1; other bands by extension.
  - 3 s for the scattering part on moves > 1 m, Vorländer Table 15.1, applied to room edits by extension.
- My incidents: W1 (ASFX16: an unpredictable 50–200 ms switch made Audio Ease redesign the engine); W4 (a helper firing on unrelated edits); W3 (silence is not approval).
- [Inferred] The 8-instance figure is my arithmetic on prototype numbers.

**6. Conditions of acceptance**
- **N-3W\* → 1/1.** All of the following:
  1. **Pilot defined in work:** the pilot costs at most half of W_max, and n\* = min(8 000, the histories that fit that half).
  2. **Minimum final N:** at least the pilot's history count. Then pilot plus minimum final fits W_max in every gated scene, and the final SE is no worse than the discarded pilot's. C12 puts this within W_max in all 17 cases.
  3. **User-facing note on a quality predicate, not on the bare cap hit.** Show "tail level approximate here, ±x dB" only when:
     - both ends are near a surface; or
     - the capped final SE exceeds Seat 1's 0.33 dB floor; or
     - VOV ≥ 0.1.

     Show it only on the settled scene, never mid-drag, in the info view. The raw cap-hit, R and slope flags stay in the diagnostics and CI.
  4. **Re-derive W_max from the C++ cost** and record it against my 3 s per emitter on the single-thread CI runner.
- **NW-3 → 1/1.** Only with a per-material bias measurement inside τ/2, which 19 §6 already contradicts. I see no route.
- **L2-F1R → 1/2.** Two steps:
  - Phase 10 splits the update. The Tol-2 estimate is heard within W_max, and the strict estimate replaces it once, inside 3 s; the change is ≈ 0.083 dB SE, inaudible. Offline renders and CI always use the strict value.
  - Cap hits follow the same quality predicate as for N-3W\*.

  The later 2 stays because the level then changes once, automatically, after the user stops (the W4 pattern, although inaudible). Under Maisara's bias reading my D-T1.4 cell stays 1/1.

**7. Hand-offs**
- **Seat 1:** whether 0.21 dB steps and a capped SE of 0.29 dB in both-near cases are inaudible; whether a +0.32 dB tail offset near absorbers is.
- **Seat 2:** the unexplained −0.273 dB (z ≈ −3.7) draw at the layout-4 emitter edge.
- **Seat 5:** W_max from the C++ cost; whether a split update is real-time safe.
- **Seat 7:** public wording of the "approximate here" note.
- **Maisara:** the AX36 reading.
- **UI phase:** the settled-state indicator.

**8. Premortem.** N-3W\* ships with an 8 000-history pilot and the bare cap-hit flag. The first user who builds a concrete garage (a hard-walled room) sees "approximate" on every placement, or gets no tail at all. A beta tester, or Maisara at the Phase 10 sweep check, notices on day one.
