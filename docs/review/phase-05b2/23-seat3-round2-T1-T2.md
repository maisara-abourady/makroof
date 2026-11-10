# Seat 3 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 3 POSITION (round 2: D-T1.6, D-T1.3, D-T2)

I read 21 (D-T1.3/1.6, D-T2), 22 (C12 in full), 19 §1/§4/§6 and my own 18. I did not re-open the corpus. The only corpus fact I lean on is the G jnd of 1 dB (Vorländer Table 6.1, as cited in 21 D4-L1). All times are from the numba prototype, not the named machine, so they show scale only (my §12).

**1. Reading.** Three questions:
- how near-wall positions are handled (NW-4C against a re-measured NW-3);
- how N is chosen (N-3W*, with C12's two conflicts);
- the strict 1 % reading (L2-F1R).

The cues they trigger:
- state discontinuity: steps per cm under motion;
- decay/level accuracy: a systematic bias against τ;
- cost: work per solve against the AQ4/AQ10 update interval and W_max.

**2–4. Ranking and tension (now/later)**

**(a) D-T1.6 NW-4C: prefer, 1/1.**
- **Now, one end near a surface:**
  - The blend's SE equals the reference-position SE: 0.013–0.016 dB in W1, 0.068–0.114 dB in layouts 4 and 5.
  - The largest history share is ≤ 0.54 % (22 (a) reading 1).
  - In W1 it is within 0.025 dB of the reference, and on walls and absorbers in layouts 4 and 5 within 0.030 dB.
  - No clamp, so the level is the model's.
- **Now, motion** (22 (b)):
  - listener sweeps ≤ 0.040 dB per cm;
  - the emitter crossing d_E = d_L ≤ 0.026 dB.
  - These are gain changes on the same cached noise, faded over AQ4's 30 ms. That is ≤ 1/25 of the G jnd, so criterion 1 holds.
  - Under NW-1/N-2 the step was 0.358 dB (19 §4).
- **Residual (why 1, not 0): both ends near a surface.**
  - At 32 k histories the SE is 0.22–1.27 dB and VOV is up to 0.95 (22 (a) reading 3).
  - Under the cap the final SE is 0.15–0.29 dB, VOV fails, and there is a 0.209 dB step between 0.11 and 0.10 m (22 (b) reading 4).
  - It is flagged, not silent.
- **Later 1:** we do not know where the both-near region starts. The pilot SE is 0.089 dB with both ends at 0.5 m and 0.56 dB at 0.11 m, and nothing was measured in between. In a booth-sized room (`dead_booth` 2.5 × 2.0 × 2.2 m) every position is within about 1.1 m of a surface.
  - Undo cost: a parameter or rule change.
  - The evidence arrives with C++ CS-NW+.
- **Open anomaly:** layout 4's emitter-edge case reads −0.273 dB, z ≈ −3.7, against the disjoint long run. It is unexplained, and VOV is 0.001. One such case in 20 is unlikely by chance `[Inferred]`.

**(b) D-T1.6 NW-3 re-rated: can live with, 2/2. My first-round 1/1 changes.**
- **The premise is gone.** I rated 1/1 on two grounds:
  - a shift of ≤ 0.093 dB in W1;
  - F3: "the clamp mostly removes variance, not signal".

  Next to an absorbing face the field has a gradient, and the clamp moves the level by +0.322 dB (layout 5) and +0.109 dB (layout 4 floor). At layout 4's edge it moves it by −0.25 dB (19 §4, §6).
- **Why 2 and not 3:**
  - The bias is systematic and larger than τ = 0.25 dB, so the agreement test cannot certify the renderer at those positions. Criterion 2 is degraded, though not broken: 0.32 dB is 0.32 of the G jnd.
- **Later 2:**
  - ρ becomes a model parameter with no evidence behind it.
  - The bias is unmeasured at absorber edges and corners `[Hyp]`.
  - Undo cost: a parameter plus a golden round.
- **Conditions:** none that I can name. NW-4C dominates it on criteria 1, 2 and 5.

**(c) D-T1.3 N-3W* as composed: can live with, 2/2. It becomes 1/1 under conditions C-1 to C-3.**
- **Conflict 1** (22 (d) reading 3):
  - The 8 000-history pilot costs 3.1× W_max in W2 and 2.7× in the gated flutter cube, so n_cap = 0.
  - The tail level of a gated scene would then rest on no final range. That is criterion 2 in a scene the product must render.
- **Conflict 2** (22 (d) continued, reading 3):
  - The final N is 60–6 200. Its SE exceeds 0.083 dB in 6 of 17 cases.
  - In W2 (pilot VOV 0.40) the final N would be 16 histories, a level read from a heavy-tailed tally.
- **What N-3W* gets right:**
  - Cap hits: 0 of 17.
  - Seat 1's floor is met in all 17.
  - My 3 s bound is met: W_max is 0.131 s per emitter at 4 threads and about 0.51 s on 1 thread.

**(d) D-T2 L2-F1R: can live with, 2/2.**
- **Arithmetic checked:**
  - 0.083 dB × 0.2303 = 1.911 %.
  - 3.29·SE/√2 ≤ 1 % gives SE ≤ 0.430 % = 0.0187 dB.
  - (1.911/0.430)² = 19.75×.
- **Now:**
  - W1 needs 36–50 ms per emitter, so 72–100 ms for two emitters. That misses AQ10's ≤ 50 ms rebuild target.
  - At 100 m it needs about 7× W_max, about 1.9 s for two emitters per position update (22, coupling section).
  - Layout 4 at s = 1 takes about 30 s (21).
  - All of that buys 0.019 dB, about 1/53 of the G jnd. It is a match nobody can hear (my §1).
- **Why 2 and not 3:** the updates still crossfade, so they arrive late but without clicks. Criterion 1 holds.
- **Later 2:**
  - It is incompatible with N-3W*'s cap at the gated scene. Either the cap hits and the 1 % certification fails, or W_max grows about 7×.
  - Undo cost: a parameter change.

**5. Evidence**
- [Measured] 22 (a), (b), (d) and the coupling section; 19 §1, §4, §6.
- [Corpus via 21] G jnd 1 dB: Vorländer Table 6.1.
- [Product] AQ4: 30 ms crossfade. AQ10: rebuild ≤ 50 ms.
- [Inferred] W1 cost under C-2 below: 179 evaluations per history (14.6 M ÷ 81 503) × 9.0 ns. 8 600 histories give ≈ 14 ms per emitter and 16 000 give ≈ 26 ms. This is an upper bound, because the prototype re-runs the listener set for each emitter.
- [Hyp] The pilot floor and the share of W_max given to the pilot in C-1.

**6. Conditions of acceptance**
- **N-3W* → 1/1, all three needed:**
  - **C-1, pilot defined in work:** n* = min(8 000, the histories that fit ½ W_max) `[Hyp share]`, with a floor of about 1 000 histories `[Hyp]`. Below the floor the cap-hit flag fires.
  - **C-2, minimum final N:** N_final ≥ n*, capped by W_max. This is C12's own suggestion and fits W_max in all 17 cases. The published SE is then ≤ the pilot's SE (0.007–0.073 dB), and no level rests on 16 histories. If the C++ W1 cost then breaks AQ10's 50 ms, lower n* so that pilot plus final stays near today's 8 000. Do not drop the floor.
  - **C-3, flags:** drop the slope flag or recalibrate it. It reads 2.93 at the W1 reference positions, so it fires almost everywhere. Keep R and VOV, and report VOV > 0.1 in gated scenes (W2 and the flutter cube).
  - W_max is re-derived from the C++ cost per evaluation (22 (d)).
- **NW-4C stays at 1/1 if:**
  - both-near is capped and flagged "near-wall, unreferenced";
  - the layout-4 emitter-edge case is re-run on a fresh disjoint range;
  - CS-NW+ reports both-near cases at 0.5 m and 0.3 m;
  - the shipped design shares one listener-started set across emitters.
- **L2-F1R → 1:**
  - Maisara takes the bias reading, which makes it 0/1 as a CI-only test; or
  - multithreaded C++ measures W1's two emitters at ≤ 50 ms and the 100 m restore within its bound.
- **Separately, under any rule:** the specular (ISM) update must not wait behind the diffuse solve. The diffuse level may lag behind a smoothed gain `[Hyp: I have not checked whether it is coupled today]`.

**7. Hand-offs**
- **Seat 2:**
  - the layout-4 emitter-edge outlier;
  - whether the reference or NW-4C is wrong at the edges and corners of layouts 4 and 5.
- **Seat 5:**
  - W_max from the C++ build;
  - the restore bound;
  - whether the ISM update and the diffuse solve are decoupled.
- **Seat 6:** whether the user sees "near-wall, unreferenced".
- **Seat 1:** whether a 0.2 dB step inside a flagged region matters.
- **Seat 9:** how common both-near placements are in real booth presets.

**8. Premortem.** N-3W* ships as composed. The 100 m flutter preset's pilot alone overruns W_max, the cap leaves no final range, and the tail level comes from a fallback or reads as missing. Maisara hears it first, in the listening pack's large-room render.
