# 3 — Seat 6 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 6 POSITION (Matters B, C, D; a short note on A, because D4 and the load case depend on it)

**1. Reading.** The question is what the producer hears, and whether they can see why, between a load or an edit and the final IR. Three of my cues apply:
- a default that is not the real state (the first seconds after load);
- a change that recomputes heavily (S3, motion as architecture);
- an automatic helper that changes the level without being asked (W4, MIR Natural Volume).

**Key point (from my seat, [Inf]).** At project load the plugin window is usually closed. The producer reopens the project and presses play. "Settling" (AX38 (iii), project load included) is only visible to someone who opens the window, so it cannot cover anything heard at load. Load must sound right without the indicator. On edits the window is open, so settling does its job.

**Matter B (interim level)**
- **B4 – prefer.** Now 0, later 1. On edits B1 lets the user's own edit land as one step, and they attribute it to themselves. At load B2 is the only source; in 07c-1 B2 is the final solve, so there is no step. The debt: under 07c-2, B2 at load can step by itself by up to 1.33 dB in layouts 4/5 (AX41 SE). Evidence arrives in the 07c-2 run.
- **B1 – prefer on edits; it does not exist at load.** On edits: now 0, later 0.
- **B2 – can live with.** Now 0 (it equals the final). Later 2: under 07c-2, every edit gives two steps, the second one unprompted ("the room changed by itself").
- **B3 – cannot live with wherever AX16 is more than 1 dB off.** Now 2, later 2. Layout 4 is +3.83 dB off and the absorbing-floor cube +2.38 dB: a self-change of the room at load, the W4 Natural Volume incident in another form. It is also out under NFR-8 unless Seat 2 names a generic predictor of AX16's error (condition 5's bound).
- Conditions:
  - B2: acceptable at 1 if it is used only at load, never on edits, and its step obeys C2.
  - B3: no condition from me lowers it. It is admissible only with that predictor, and then it rates 1.

**Matter C (provisional-to-final step)**
- **C2 – prefer.** Now 0, later 1. It guarantees no self-caused room change above the bar.
  - Condition I add: at load, "hold the previous output" means hold nothing. C2 therefore needs a load fallback that is not silence. That fallback is the saved E_b (A2) or a provisional tail (D3).
- **C3 (≤ 0.5 dB) – can live with.** Now 0, later 1. It is stricter than I need. It pushes more cases to fallbacks; that cost falls on Seats 3 and 5, not on me.
- **C1 – can live with.** Now 1, later 2.
  - Why later 2: under 07c-2, steps above 1 dB in layouts 4/5 ship, counted but heard. Silence in the field is not approval (W3), so a counter is not a cure.
  - Condition (lowers it to 1): a step above 1 dB is allowed only within the window after a user edit while "settling" is shown. Never at load or on a restore.
- **C4 – cannot live with.** Now 3, later 3.
  - It has no bound, and "settling" is the only honesty it offers, which is invisible at load.
  - Bound: condition 5 says the step "stays within Seat 1's ruling". C4 supplies no ruling to stay within.
  - Condition: none short of adopting C1's cap.
- **Scope.** I accept "same scene, not the user's edit", with one addition. Under Phase 10 automation, every step reaches the listener as unprompted. The scope should state that automation-driven steps count as unprompted [Hyp]. Seat 1 should rule whether a step arriving later than some delay after an edit still reads as caused by it. I give no number.
- **No new control or message is needed.** A "wait / fast" toggle would leak the engine into the UI (criterion 2).

**Matter D (while the synthesis is pending)**
- **D3 – prefer for both load and edits.** Now 1, later 1.
  - The room is present at once, with the right level and T60 (if the provisional tail is built that way).
  - The equal-power swap between two unrelated noises is inaudible as a place change [Hyp]. That is for Seats 1 and 3, as are feasibility and cost.
  - It needs no golden round, because offline never uses it.
- **D4 – can live with (load only).** Now 0, later 1 from my side. Its 18 MB cost is for Seats 5 and 7. If Seat 5 rules it out, D3 covers load.
- **D5 – can live with (edits only).** Now 1, later 2.
  - On a size drag the new early part comes at once and the old-T60 tail lingers about 3.1 s at 100 m / 96 kHz. That is drop-and-settle with settling visible: honest, as with MIR's position read on release (FST21).
  - Later 2: under Phase 10 room-size automation the tail always lags the early part.
  - Condition (lowers it to 1): use D5 only for interactive edits, with D3 replacing it once D3 exists.
- **D2 – can live with on edits only.** Now 2, later 2.
  - The user's edit seems ignored for about 3.3 s, then the room jumps. That is the Altiverb switch delay Audio Ease designed away (ASFX16).
  - It also strains condition 4 (the ISM update is never held behind the diffuse solve); that half is Seat 3's.
  - Condition (lowers it to 1): hold only the tail, which is D5.
- **D1 – cannot live with at load where the saved state had a tail.** Now 3, later 3.
  - The project reopens dry, and the room arrives by itself up to about 3.3 s later (shorter at 48 kHz and in small rooms). The first result is untrue, and settling is not seen.
  - It breaks condition 9 ("never silence where a tail existed in the saved state"), read at the tail.
  - Condition: none. It is acceptable only for scenes with no tail.
  - D2 at load is D1, with the same rating.

**Matter A (note, as it bears on my matters)**
- Prefer A2: load equals the final, so there is no step.
- A1 can live with: one step at load, within C2.
- A0: the load case rests entirely on B2 + D3.
- Validity key, AX5 and the state format are for Seats 2 and 5.

**5. Evidence**
- Defaults equal reality; Indoor's perpetual convolution engine accepts new IRs click-free; Altiverb's IR switch clicks and takes an unpredictable 50–200 ms: {Obs/SRi; IndMan, ASFX16; pre}.
- Being honest about "on release": {SRi; FST21}.
- An automatic level helper surprised a user: {SRi; VSL-forum-NV} (W4).
- Silence is not approval: {Obs; FF-forum-float} (W3).
- The 1 dB jnd for G and C80 (Vorländer Table 6.1) is quoted from the brief and not re-derived by me. Whether it holds within a running stream is R4 / Seat 1.
- The plugin window being closed at load is [Inf]; there is no source in my register.

**7. Hand-offs**
- Seat 1: within-stream threshold (R4), whether a delayed step after an edit still counts as caused by it, audibility of D3's swap.
- Seat 3: D3 generator and cost; D2 against condition 4.
- Seat 5: D4/A3 size; offline after load.
- Seat 2: whether B3 has a predictor.
- Seat 11 / Phase 11: whether a scene-level settling aggregate is visible with the window closed.

**8. Premortem.** If D1 or C4 ships, a producer reopens a 100 m scene and plays at once. The first two to three seconds are dry, or the room shifts by about 1–4 dB. They report "my reverb drops out on load" as a bug, and Seat 8's beta testers notice first, before any test does.