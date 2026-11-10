# Seat 1 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 1 POSITION (second round: D-T1.6, D-T1.3, D-T2)

Corpus present. Yardstick unchanged from round 1 (18-seat1 §preamble): the G jnd is 1 dB [corpus Vorländer Table 6.1, L2056; 500–1000 Hz, other bands by extension]. A tail-only error ΔL moves G by less than ΔL. Band errors are a broadband offset, not a tilt (19 §3: correlation ≥ 0.978). No persona assumption falls beyond those named in round 1.

**1. Reading.** Three questions: which near-wall handling ships, how the path budget is set and capped, and whether the 1 % rule costs ≈ 20× paths in shipped builds. Cues triggered:
- the hardest signal, which here is the near-wall placement (B2);
- a systematic bias against a random error (O4);
- smoothness under automation (S7);
- a flag that always fires is not evidence (criterion 3).

**2–4. Ranking and tension (now / later)**

**(a) D-T1.6 NW-4C — prefer. Now 1, later 2.**
- **One end near a surface is solved.** At 32 k histories the SE equals the reference positions' SE (W1 0.013–0.016 dB; layouts 4/5 0.068–0.114 dB). The largest history share is ≤ 0.54 %, VOV ≤ 0.015. The blend is within 0.025 dB of the W1 reference and within 0.030 dB at the wall and absorbing faces (22 (a) readings 1–2).
- **Sweeps meet my round-1 C6b acceptance (≤ 0.1 dB per cm [Hyp]).** Listener sweeps step ≤ 0.040 dB. The emitter crossing d_E = d_L steps ≤ 0.026 dB (22 (b)). Under NW-1 with N-2 the step was 0.358 dB (19 §4).
- **No model change**, so my agreement-gate rule holds as written.
- **Now 1, for two residuals:**
  - layout 4's emitter edge sits at z ≈ −3.7, one case in 20, with VOV 0.001 and no explanation (22 (a) reading 1). Under a normal model, P(|z| ≥ 3.7 in some case of 20) ≈ 0.004 [Inferred];
  - layouts 4/5 edge and corner differ from the uncertified reference by up to −0.38 dB. That is ≤ 0.38 jnd as a level and is reported, not gated (D-T1.5).
- **Later 2: both ends near a surface.**
  - At 32 k histories, layout 4's both-corner case reads 5.2 dB below the 256 k run, and the long run's own SE is 1.16 dB (22 (a) row 59).
  - A capped estimate in a user scene can ship several dB low: the "tail too weak" fault this phase removes. It would arrive silently, because escalation runs only in CI and render_cli.
  - With a tail share f = 0.5, ΔL = −5 dB gives ΔG ≈ −1.8 dB, about 1.8 jnd [Inferred; f is Hyp].
  - The W1 both-near sweep steps 0.21 dB at 0.11 → 0.10 m (22 (b)), above my 0.1 dB acceptance.
  - Evidence that could overturn this: a both-near measurement in layouts 4/5 under N-3W\*, and the C++ agreement run on CS-NW+.

**(b) D-T1.6 NW-3 re-rated — can live with. Now 1, later 2. My round-1 cell changes from prefer 0/1.**
- **As a level, the measured bias is inaudible.** It runs from −0.25 dB (layout-4 edge) to +0.322 dB (layout-5 absorbing wall), i.e. ≤ 1/3 jnd, and less after f (19 §4, §6).
- **Its sign depends on the position.** It reads positive next to absorbers and negative at reflective edges, so the error is systematic, not random. Every user who puts a listener at 0.1 m from such a face gets the same offset.
- **Later 2: the bias exceeds τ = 0.25 dB.**
  - The agreement gate then has two exits: fail a correct implementation near walls, or widen τ there. My decision rule forbids widening τ (18-seat1, rule 4).
  - Either way, a near-wall implementation error of about 0.3 dB passes unseen.
  - The bias is measured at 4 points in 2 rooms. Faces with α near 1 are unmeasured [Hyp: the bias could be larger there].
- **NW-3's one advantage:** its bias is bounded where NW-4C's both-near error is not.

**(c) D-T1.3 N-3W\* as composed — can live with. Now 2, later 2. With the conditions below: prefer, 1/1.**

*Conflict 1 (the pilot does not fit W_max).* As composed, the gated flutter cube and W2 get n_cap = 0 (22 (d) reading 3). The output of a gated scene is then undefined, which no gate can accept. I also estimate that layout 4 at s = 1 has the same conflict:
- 19 §1 times NW-4 at 1.7–3.6 s per 32 k paths (4 threads), i.e. 53–112 µs per path;
- if a NW-4C history costs about two such paths [Inferred], W_max = 0.131 s allows about 600–1 200 histories, not 8 000.

What I need:
- **A pilot defined in work:** n\* = min(8 000, the histories in ≤ 50 % of W_max), so the final range always gets at least as much work as the pilot.
- **A minimum pilot of about 1 000 histories, or the cap-hit flag fires.** A small pilot under-reads the SE of a heavy-tailed variable, which sets N too low [Hyp on 1 000; the researcher could source a pilot-size rule from the MCNP tally guidance, F7–F10].
- **The pilot's VOV may fail in W2 and the flutter cube (0.31–0.68).** I accept the flag rather than iterating there, because their total SE is far below target (1–16 histories needed). The rule I ask for: VOV must be < 0.1 wherever the pilot SE is above 1/3 of the target.

*Conflict 2 (the final range is smaller than the pilot).* Perceptually minor: the final SE is 0.07–0.10 dB, ≤ 0.1 jnd. But a diagnostic that says "SE ≤ 0.083 dB" while 6 of 17 final ranges exceed it is a false statement (criterion 3). What I need:
- **A minimum final N ≥ the pilot's histories.** It costs ≤ 2× the pilot and fits W_max in all 17 cases (22 (d) reading 3).
- **The final range stays disjoint.** Pooling the pilot back in reintroduces the stopping-rule bias (F12, F14).

*Slope flag.* It fires even at the W1 reference positions (slope 2.93; 22 (e)). A flag that always fires trains people to ignore flags. Report the slope, but don't flag on it until a threshold is calibrated on the reference positions.

*My floor ("C4's worst cases reach SE ≤ 0.33 dB with VOV < 0.1"):*
- **Met** in the 17 one-end cases of CS-NW+ and the Phase 04 rooms (worst 58 k evaluations against 14.6 M; largest VOV 0.047; 22 (d)), in the listener sweeps, and in the crossing sweep (final SE ≤ 0.128 dB).
- **Not met** in the W1 both-near sweep. The final SE is 0.15–0.29 dB, but the VOV is 0.29–0.32 (22 (b) reading 4).
- **Not tested** in layouts 4/5. These are the cases C4 named. My arithmetic above puts the one-end cases at ≈ 0.36–0.52 dB under the prototype's W_max, i.e. above the floor [Inferred]. Both-near is far above it (SE 0.45–1.27 dB already at 32 k).

*Later 2.* W_max comes from a numba proxy and must be re-derived in C++ (22 (d)). The restore bound is still with Maisara. A slower C++ cost per evaluation shrinks W_max and pushes layouts 4/5 further below my floor.

**(d) D-T2 L2-F1R — can live with. Now 2, later 2.**
- **It buys nothing audible.** SE falls from 0.083 dB to 0.0187 dB, i.e. from 0.08 to 0.02 jnd. The quality curve is flat here (criterion 6, B5).
- **The cost reaches the listener as edit lag.** At the gated 100 m scene it needs ≈ 7× W_max, and the restore comes to ≈ 3.7 s against 2.14 s (22 coupling section). Edits in large rooms are heard seconds late; Vorländer, Sect. 6.2 asks interactive updates to be immediate [corpus, L3869].
- **It does not run everywhere.** It cannot run in W2 or the flutter cube (conflict 1), and it hits the cap in concert_hall_box.
- **As a gate it is not strict enough.** With p ≥ 0.999 per case over about 50 cases, a correct implementation fails about 4.9 % of the time (1 − 0.999⁵⁰). Each refactor of the random stream re-rolls that chance, and my rule forbids reseeding. A family α of 1 % needs z = 3.72 and SE ≤ 0.380 %, i.e. ≈ 25× Tol-2's paths [Inferred; arithmetic redone: (1.911/0.430)² = 19.75; (1.911/0.380)² = 25.3].
- Seat 5's veto on the restore is not mine to rate.

**5. Evidence**
- [corpus] Vorländer Table 6.1 (L2056) and L3869.
- [Observed] 22 (a), (b), (d), (e) and the coupling section; 19 §1, §3, §4, §6.
- [Inferred] ΔG with f, the per-case z probability, the family-wise arithmetic, the layout-4 history budget.
- [Hyp] f in layout 4; the 1 000-history pilot minimum; the 0.1 dB step acceptance.

**6. Conditions of acceptance**
- **NW-4C, later 2 → 1:**
  - measure both-near points (wall, edge, corner) in layouts 4/5 under N-3W\* at W_max, and show the shipped error against long runs is ≤ 1 dB at the 95th percentile;
  - otherwise, a both-near fallback with a bounded, measured bias, applied only where both endpoints are within a stated distance (Seat 2 designs it; NW-3's clamp at one end is a candidate);
  - in either case, explain or re-run the layout-4 emitter-edge outlier.
- **NW-3, later 2 → 1:** its bias is ≤ τ/2 (0.125 dB) on CS-NW+ and the absorbing-face cases, α near 1 included; or NW-3 is used only as NW-4C's both-near fallback.
- **N-3W\*, 2/2 → 1/1:**
  - a pilot defined in work (≤ 50 % of W_max, at least about 1 000 histories, flag otherwise);
  - a minimum final N ≥ the pilot's histories, in a disjoint range;
  - slope reported, not flagged;
  - my floor measured in layouts 4/5 one-end cases;
  - W_max re-derived from the C++ cost before it is frozen.
- **L2-F1R, 2/2 → 1/1:** the bias reading. That is my round-1 challenge, unchanged: in CI, at a pre-registered N with 3·SE ≤ 1 %, the pooled bias must be < 1 % per band, and shipped builds stay at Tol-2.

**7. Hand-offs**
- Model sameness and the both-near fallback design: Seat 2.
- Which of the clamp and the point estimate is closer to a real room next to an absorber: Seat 9.
- W_max, the restore bound and the C++ cost: Seat 5.
- Whether the user sees "near-wall, unreferenced": Seat 6.
- The bias reading or a veto override: Maisara.
- Pilot-size rule from the MCNP tally guidance: researcher.

**8. Premortem.** NW-4C ships with N-3W\* capped in a large reflective room. A producer puts both the mic and the source in a corner, and the tail comes out 2–5 dB weak with only a diagnostic flag. The first to notice is a beta user with a hall preset.

Files read: /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md (D-T1.3/1.6, D-T2), /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md, /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md (§1–§6), /home/user/makroof/docs/review/phase-05b2/18-seat1-T1-T2-T6.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (L2056, L3869).
