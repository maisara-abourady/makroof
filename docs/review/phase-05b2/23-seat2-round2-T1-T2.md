# Seat 2 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 2 POSITION (round 2: D-T1.6, D-T1.3, D-T2). The corpus is present; my checkout reads e68891d, the decider cited c1b171f. No corpus line I lean on was re-read this round, so the G jnd comes via the decider's D4-L1.

**1. Reading.** I am rating four things on C12's measurements: NW-4C, NW-3 on its measured bias, N-3W* against its two conflicts, and L2-F1R against the restore bound. The cues it triggers are §4-4 (path geometry next to a wall), §4-7 (cost growth), the S6 circularity and stated-edge traps, and W3 (a missing piece shows only in the right comparison).

**(a) NW-4C: prefer, 1 now / 1 later.**

*Is it unbiased? Yes, under three checks.*
- **The model is reciprocal.** A point emitting isotropically puts cos θ/(4πr²) on a wall element, and the wall re-emits as Lambert at cos θ'/(πr'²) toward the receiver. Swap the two ends and the product is the same. The Lambert–Lambert and specular kernels are also symmetric, and air and the window depend only on total path length (19 §1) [Inferred].
- **w depends on geometry only, never on samples.** A fixed linear combination of two unbiased estimators is then unbiased. *Condition:* w must never be estimated from the run's own variances, because sample-estimated inverse-variance weights bias the blend.
- **The data agree.** 19 of 20 one-end cases match the disjoint long runs within 2 SE (C12 (a)). The exception is layout-4 emitter_edge at z ≈ −3.7. Across 20 cases the chance of one |z| ≥ 3.7 is ≈ 20 × 2.2e-4 ≈ 0.004 [Inferred]. That is not ignorable, even though VOV is 0.001.

*Why it works.* Under F3 the per-hit score is capped at 1/(πd²) at the gather end. The blend's cap is w/(πd_L²) + (1−w)/(πd_E²) = 2/(π(d_L² + d_E²)) [Inferred from F3].
- With one end at 0.1 m and the other at 2 m, the cap is 0.16 m⁻², against 31.8 for the point estimator.
- With both ends at 0.1 m it is 31.8 again, i.e. NW-1's.
- This is why one-end SE equals the reference-position SE, and why the both-near cases stay heavy-tailed (layout-4 corner: 32 k vs 256 k differ by 5.2 dB).

*Is it continuous? Yes.*
- d (distance to the nearest surface) is 1-Lipschitz, and AX6 keeps d_L² + d_E² ≥ 0.02 m², so w is continuous.
- Measured steps per cm: ≤ 0.040 dB in the listener sweeps and ≤ 0.026 dB across d_E = d_L (C12 (b)).
- A small correction to C12: the final range is a fixed-start prefix, so a change in N moves the estimate by about SE·√(ΔN/N), not by a fresh draw at √2·SE [Inferred]. The measured 0.040 dB fits that.
- The exception is both ends near walls: 0.209 dB per cm at VOV 0.29–0.32, where the SE itself is unreliable.

*What it costs.*
- **Now (1):** both-near cases are flagged, not solved.
- **Later (1):**
  - B7 directivity (AQ8 defers it) needs the emitter pattern applied in the reverse gather. That is an estimator change in both directions, not a parameter.
  - B10 needs weighted branching in both sets.
  - The layout-4/5 edge and corner disagreements with the uncertified 1.25 m reference (up to −0.376 dB, z −12.4) stay unresolved until an independent reference exists.

*Conditions to hold 1 (any one unmet → 2):*
- the both-near flag uses a geometric criterion, pre-registered from a sweep where the pilot's VOV crosses 0.1 (it is 0.056 at 0.5 m and 0.32 at 0.11 m; I give no number);
- layout-4 emitter_edge is re-run on a third disjoint range, with VOV and largest share reported. If the −0.27 dB reproduces, the reverse gather at an emitter by an edge is a defect;
- an independent near-corner reference (ref_hybrid with local patch refinement, or the tracer at r_d < 0.1 m at two radii), reported only;
- one listener-started set shared across emitters.

**(b) NW-3: cannot live with, 2 now / 3 later (was 1/2).**
- My round-1 condition (measure it in layouts 4/5, then budget τ for it) has now been tested, and it fails. The clamp reads +0.322 dB at layout 5's absorbing wall, which is more than τ = 0.25 dB, and −0.25 dB at layout 4's edge, which is all of τ (19 §4, §6).
- CS-NW+ gates near-wall cases only in W1, where the bias is ≤ 0.09 dB. So the gate cannot fail the error. That is the same reason I vetoed Tol-1.
- The bias is the field's gradient next to an absorber. With band-dependent α, the absorber's gradient varies by band, so the clamp shifts bands unequally: a tone-colour shift (the highest perceptual weight) that no diagnostic shows [Inferred].
- Undoing it after release changes saved projects' sound.
- *To reach 1/2:* a clamp whose measured bias is < τ/2 in absorbing-face cases in layouts 4/5, in all 8 bands, gated there. At the present clamp, 19 §6 says this is not met.

**(c) N-3W*: as composed, cannot live with, 3 now / 1 later. With C1–C5: prefer, 1/1.**

As composed, a gated scene (the 100 m flutter cube) gets n_cap = 0, so there is no diffuse estimate at all. The fix is parameter-level.

- **C1, conflict 1. The pilot is defined in work.** It stops at min(8 000 histories, the cumulative evaluations reaching a fixed share of W_max). The share must be ≤ ½ so that C3 fits. The share itself is Seat 5's or 6's number.
- **C2. The final range starts at a fixed index** (8 000), whatever the pilot's actual length and whatever N. Otherwise every step in n* is a fresh draw.
- **C3, conflict 2. A floor on the final N: at least the pilot's history count.** This is required, not optional. In W2 and the flutter cube, Tol-2 needs 1–16 histories with pilot VOV 0.31–0.68. A one-path published estimate has no meaningful SE, and F14 says CLT rules fail in the non-asymptotic regime. The floor costs at most 2× the pilot and fits W_max in all 17 cases (C12). It does not bias, because the pilot is still discarded (F12).
- **C4. W_max is a pinned constant in image evaluations**, re-derived once from the C++ cost and recorded as an AX row. It must never be a time cap, so that E_target stays a pure function of the scene (S-1, AX5).
- **C5. Flags.**
  - The slope check goes to diagnostics only, or is dropped: by F10 it reads below 3 until near-cap scores are sampled, and it fires at 2.07–2.94 where the estimate is fine.
  - VOV goes to diagnostics only.
  - The user-visible flags are the cap hit and the geometric both-near flag (Seat 6).

I also ask for the cap-hit rate on a grid of ordinary positions, reported only. The crossing sweep was capped at 51 of 51 points at 28–30 m apart, where a longer t_mix,e drives the cost.

**(d) D-T2, L2-F1R: can live with, 2 now / 2 later. C12 changes my strict reading.**
- **I checked the decider's arithmetic and it holds:**
  - 1.911 %/√2 = 1.351 %;
  - P(|Δ| < 1 %) = 0.541;
  - SE ≤ 0.430 % (0.0187 dB), which is 19.75× Tol-2's paths;
  - restore 1.88 + 1.84 = 3.72 s, against 2.14 s.
- **At the gated 100 m scene it needs 6.7–7.3× W_max.** Under N-3W* it is therefore capped exactly where it is meant to certify, so its certification fails by construction, silently.
- **The precision it buys is about 1/50 of a jnd, which my §2 ignores.**
- **My round-1 L2-F2 1/1 assumed its 100 m cost (4.7–6 s) was affordable. That assumption fell** to Seat 5's veto and to C12.

I now prefer the bias reading, rated 1/1 (I add it as a rated alternative). It certifies what AX36 protects: systematic error.

*Condition for bias reading → 0/1: the bias test is powered per case class, not only pooled.* The classes are reference positions, one-end near-wall, absorbing face and small rooms, in every band. The reason is dilution: take 5 near-wall cases biased 1 % at z = 3, pooled over about 50 case-bands (bands are near-collinear, 19 §3). The pooled mean z is 0.30, under the threshold 3/√50 = 0.42, so it passes. Within the class, the threshold is 3/√5 = 1.34 and the bias is caught [Inferred].

Accepting the bias reading is Maisara's ruling.

**5. Evidence.**
- [Observed] C12 (a), (b), (d) and coupling; 19 §1, §4, §6.
- Dossier: F3 (derived), F10, F12, F14.
- From the docs: AQ8 (BUILD_PLAN).
- [Inferred]: the cap algebra, the dilution and outlier arithmetic, and the prefix-step bound.

**7. Hand-offs.**
- **Seat 1:** whether 0.21 dB per cm both-near steps are audible.
- **Seat 5:** the pilot share and the C++ W_max.
- **Seat 6:** how cap and both-near flags are shown.
- **Seat 9:** realism of both-near placements.
- **Researcher:** an independent near-corner reference.
- **Maisara:** AX36's reading.

**8. Premortem.** Suppose NW-3 ships. A producer then sets up a booth with a heavily absorbing wall, the tail at the listener's chair reads 0.3 dB high and brighter, and CI is green. The first to hear it is Seat 9's Phase 08 listening.
