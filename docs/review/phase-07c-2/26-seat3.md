<!-- Saved by the orchestrator from seat 3's report, 2026-11-22. -->

SEAT 3 POSITION

I ran as Seat 3 and read files 13, 21 to 24, BUILD_PLAN AX21, AX47 and B11, the run sheet, `tools/ci/abx_kit.py` lines 202 to 278, `src/cli/Cli.cpp` lines 737 to 833 (`buildAbxStep`), `src/sim/Engine.cpp` lines 174 to 188 and 500 to 578, and `src/sim/tail/NoiseTail.cpp` lines 273 to 281. Corpus present (c1b171fe).

**1. Reading.** Three questions: how item 5's step is applied (M1), which scene the stimuli use (M3), and what the +18 % tail T30 at 8 kHz means.
- Cues from my §4: a state change applied to the tail level (state discontinuity), decay accuracy (8 kHz), and a direct sound followed by 0.38 s of silence (my "rat-a-tat / discrete echo" cue, early-reflection design).

**Fact correction first (from the code; it changes file 24's question 2 and the corrected item-5 sentence)**
- The engine never renders specular energy in the tail window. `mixHybrid` (Engine.cpp L536–551) drops the ISM part completely after t_mix + 2.5 ms (`crossfade`, NoiseTail.cpp L278–279).
- From that point the IR is only `amplitude[b]·unit noise`, with amplitude = √(E_target,b/ē_b) (L531–532). E_target = E_spec + E_diff (L183).
- E_spec is a term in the level target. It is not a separate signal in the window.
- Under option A, E'_target = k·E_target in every band, so the whole tail scales by √k at any target specular share.
- So file 23's formula a = √((k−s)/(1−s)) and file 24's "diff_db fails at s > 0" describe a rendering this engine does not do. On the tail-alone window, `diff_db` and `step_db` hold exactly at any share.
- The only energy that does not scale is the ISM fade-out in [t_mix, t_mix + 2.5 ms). It is inside the 0.1 dB `ax47_window` assertion and shifts diff_db by 10·log10(1 − s_w). That fails only if s_w > 2.3 %.
- The kit's printed `specular_share` measures s_w. It is not the target's share; the same name is used for two different quantities.
- The kit does refuse one real case: a down-step when the target share s_t > k (Cli.cpp L788–795).
  - For −0.9 dB, k = 0.813, so s_t > 0.81 is refused.
  - For the −3 dB anchor, k = 0.501, so s_t > 0.50 is refused.
- The item-5 sentence for the run sheet and PR should be corrected to say this.

**2. Ranking**
- M1:
  - **A: prefer.** It is the AX47 quantity (the tail level over the tail window).
  - **B: can live with on S-A only.** On S-A, s_t = 0 and B is identical to A.
- M3:
  - **S-D, my proposal: prefer.** This is S-B made concrete: same layout-4 room, α and positions as S-A, only s lowered. That is a one-variable contrast with S-A.
    - s should be a value whose tail level phase-05h's agreement reference gates (0.1 or 0.3 appear there; Seat 2 to confirm which is gated at this position).
  - **S-B: prefer**, under the S-D conditions.
  - **S-A: can live with.**
  - **S-C: can live with, ranked last.** From the code, `listener_wall` is the same s = 1 room with the listener at (10, 0.1, 1.7). Its early part is still empty, and it is at a wall, where my shared-late-field rule (§9) weakens.
- The 8 kHz +18 %: not a defect of the step. It is a follow-up.

**3. Tension now**
- **A: 0.**
- **B: 1.** No difference on S-A.
- **S-B / S-D: 1.** One new scene to run through the kit; minutes of compute (file 22: 2 min 24 s).
- **S-A: 2.**
  - Every stimulus has an IR with nothing between the direct sound and 0.38 s. Speech then returns as a diffuse copy about 10 dB down, 380 ms late. My §4 flags that as an echo pattern.
  - No s < 1 scene renders like this, so the step is tested on a stimulus that is not representative of the renderer.
- **S-C: 2.** Same reason; the early part is still empty.
- **8 kHz: 0 for the ABX.**
  - Both IrSets share `useUnitDecays`, so the decay shape is identical in A and B.
  - The step is an amplitude change in each band and is exact whatever the decay error. `ir_band_shares` prints it.

**4. Tension later**
- **A: 0.**
- **B: 2.**
  - On any s_t > 0 scene, B's rendered step is 10·log10(s_t + k(1 − s_t)), for example 0.47 dB when g = 0.9 and s_t = 0.5. The step shrinks and stops being uniform across bands.
  - The 08-3 binaural rerun (item 15) would inherit that.
  - Undoing it is cheap, but the evidence would only surface as an item-6 failure.
- **S-B / S-D: 1.**
  - It must be re-asserted capped at m = 6, 7 and 8.
  - The AX21 envelope step at t_mix is present at s < 1. Upper estimates are 1.8 / 4.9 / 8.7 dB at s = 0.1 / 0.25 / 0.4. It is static and identical in A and B.
- **S-A: 2.** AX47's "all scenes" bound rests on an AX21-extreme stimulus. If B11 is ever promoted, the listening session has to be redone (a person-session, not a parameter change).
- **S-C: 2.** Same as S-A.
- **8 kHz: 1.**
  - If the error is in the tail, it is 3.6 × my strict 5 % decay JND (still under the 39 % reported upper bound). That is a decay-accuracy debt on every scene.
  - Evidence arrives from the follow-up test in §6.

**5. Evidence**
- All mechanism claims above are from the code, at the line numbers cited.
- AX21 step estimates: BUILD_PLAN AX21 (Kuttruff §5.2).
- 8 kHz numbers: file 22. Tail T30 is 0.870 / 0.884 s, tail EDT 0.776 / 0.789 s (+5 %), against a target of 0.740 s. The 4 kHz band, with T60 1.089 s, decays 26 dB/s slower than 8 kHz.
- 8 kHz cause, `[Hyp]`: a late-decay bias (T30 +18 %, EDT +5 %) fits energy leaking from the slower 4 kHz band through the 8 kHz filter skirts. The leak could be in the analysis filter or in the summed band noises of the rendered signal.
- That a 380 ms delayed onset is audible as an echo on speech is `[Hyp]`. Route it to Seat 1.

**6. Conditions of acceptance**
- **B:** apply it only where every band's s_t = 0, which is option A's result anyway.
- **S-A, which would drop to 1:**
  - label it as AX21-extreme (empty to 0.38 s);
  - record that the bound is pending a rerun on an s < 1 scene before 08-3.
- **S-B / S-D, which stay at 1:**
  - the per-band target share is printed, and is ≤ 0.50 in every band so the 3 dB anchor is not refused, or else the scene is rejected before seal;
  - the `ax47_window` s_w is ≤ 2.3 %;
  - the scene is asserted capped at m = 6, 7 and 8;
  - the AX21 step at t_mix is printed.
- **8 kHz:** the builder renders a synthetic exponential noise with T60 0.74 s through the AX13 band filter, and measures the tail's own band-7 noise unfiltered by neighbouring bands. Logged as an NFR-8 follow-up before 08's goldens freeze; nothing is tuned.

**7. Hand-offs**
- Whether S-A biases the test toward non-detection: Seat 1.
- Which s is gated, and the D/R and t_mix at it: Seat 2 and the builder (K3).
- The early part's effect on the binaural rerun: Seat 4.
- The label and the 0.43 ceiling: Seat 9.
- M2: Seats 1 and 9.
- The mislabelled "specular_share" in file 24 question 2 and in the item-5 sentence: the interrogator.

**8. Premortem.** If S-A is sealed and the result is no detection, B11 or the first s < 1 scene at 08-3 shows a tail step that is audible against a present early part. The 1 dB bound would then have been set on an empty-early stimulus, and Seat 1 would notice first at 08-3.
