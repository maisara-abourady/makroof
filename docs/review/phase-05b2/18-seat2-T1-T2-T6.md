# Seat 2 (engine architect) — positions on D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 2 POSITION (D-T1.1–1.6, D-T2, D-T6; corpus present, revision c1b171f)

My ratings depend on: D-T5.2, which fixes t_mix,e before the solve. T1-F's window premise rests on it, and it stands. D-T4a's 1 GB ceiling bears on T1-A. D-T4c, under which time is escalated rather than blocked, bears on T1-B. C3 (the outer bands) is still pending: if it shows |z| > 3 anywhere, T1-F gets re-rated.

## D-T1

**Reading.** Which estimator of the validated model ships, and how its error is bounded and tested. Cues: §4-3 and §4-4 (path geometry next to a wall); §4-7 (cost growth); W1 (a missing model piece shows up only in a blind comparison); and the S6 circularity trap.

**Is T1-F the same model? Yes, as the ℓ→0, Δt→0 limit. I checked `mc2` against `ref_hybrid` line by line.**
- **Injection.** s(1−α) of the incident weight is emitted at every hit (Eq. 4.24). The specular pre-history carries Π(1−α)(1−s) in expectation. This matches `injection`.
- **Transport.** Next-event estimation over the listener's lattice images, with the factor (1−α)(1−s) per image hit, is Gilbert/Eq. 4.35 transport.
- **Gather.** The point score cos θ/(πr²) is the integrand of `gather_kernel`'s Ω/(πA), since Ω = ∫cos θ dA/r². This is the same Eq. 4.29, without the patch average.
- **Branching.** Broadband s is unbiased with no weights only because s is band-independent (AQ3).
- **Air and window.** exp(−γr) with γ = m − rate/c reproduces the Eyring referral exactly. The triangle-inequality prune is exact.
- **Unbiased.** Yes, as next-event estimation over every image in reach.
- **The remaining differences are ref_hybrid's own:** the ℓ term (≤ 0.37 %, i.e. 0.016 dB) and its 1 ms binning (≤ 0.126 %).
- **Point vs sphere.** The point listener is the r_k→0 form of diffuse rain (Vorländer Fig. 11.38). Under AX6 the score is bounded by 1/(πd²) (F3).
  - A detector sphere with r_k > 0.1 m cuts the wall (F5), which adds bias. With r_k < d it buys nothing.
  - **So no sphere is needed.**
- **Agreement so far.** 15 cases × 3 bands at |z| ≤ 1.67, against an expected maximum of about 2.3. That is consistent with no bias.

**Two prototype defects the C++ must not copy:**
1. `nsq = sqrt(npaths)` makes each path's direction depend on N. The paths are then not a prefix of one sequence, which breaks N-2 and N-3 and makes N changes reshuffle every path.
2. The iid SE formula over stratified paths is conservative.

**(d) adjoint: the builder's "saves nothing" is wrong, in two ways.** [Inferred, GA reciprocity; Lambert and specular transport are both symmetric]
1. **The window can be applied after the solve.** The transport is linear and time-invariant, so one time-resolved listener-side solve, followed by a per-emitter window correlation, serves every emitter. That is ×(emitter count) on the solve for T1-A and T1-B.
2. **For T1-F, starting paths at the listener moves the heavy tail to the emitter end.** C4 shows that the start end costs nothing near a wall (W1 emitter at the wall: SE 0.015 dB vs 0.018 dB at the reference positions). One listener-started path set also serves all emitters. I add this as **NW-4** under D-T1.6.

**D-T1.1**

| option | rank | now | later | reason |
|---|---|---|---|---|
| T1-F | prefer | 1 | 1 | Same model; < 2 MB. Its validation chain has one more link (MC→ref→tracer), and no published bias figure exists (RQ-T1-4). Debt: per-band s (B10) needs weighted branching, which is a parameter-level change. |
| T1-B | can live with | 2 | 2 | W1 ≈ 9 s [Hyp 2 ns], 180× AQ10; 100 m takes hours. A second formulation would be forced for the edit cycle (a rewrite or a size switch with a step). Its near-wall ℓ error (4.75 %/halving at the layout-4 edge) is silent: no diagnostic flags it. |
| T1-A | can live with, last | 2 | 2 | Forces D-T3 and drops large halls, where GA is most valid (fs < 50 Hz). Undoing it means a contract bump plus a new formulation. |

**D-T1.2 (under T1-F)**
- **S-1: prefer, 0/0.** E_target becomes a pure function of the scene, as with patches. The AX19 σ1 is not mixed with MC noise.
- **S-2: can live with, 1/1.** Ensembles then combine two random sources.
- Under L2-F2 the difference between them is ≤ 0.015 dB, which is immaterial.

**D-T1.3**
- **N-3: prefer, 1/1.** The fresh disjoint range avoids F12. It needs an n* that samples near-cap scores (F10) and an N-independent stratification.
- **N-2: can live with, 1/2.** Its stopping bias runs low (F12), in the same direction as the near-wall low readings, and its size is unquantified.
- **N-1: cannot live with, 2/3.** Fixed N with diagnostics only reported ships −1.06 dB (W1 corner) to −3.9 dB (layout-4 edge) tails silently. That breaks "a stated edge".

**D-T1.4**
- **Tol-1: cannot live with, 3/3.** τ = 1 dB passes a C++ that kept AX16 in all six Phase 04 rooms, CR2 and W1 (|ΔL_b| ≤ 0.43 dB, C2). The test cannot fail the error it exists to catch.
- **Tol-2: can live with, 1/1.**
- **Tol-3: prefer. 0/0 under L2-F2; 1/1 under L2-F1.**
  - At SE 0.033 dB, 3·SE = 0.099 dB, so the whole τ is used up by noise and nothing is left for the 0.016 dB ℓ term.
  - With about 488 case-bands (CS-3), the expected false fails at 3σ are ≈ 1.3.
  - Under L2-F2: Bonferroni z ≈ 3.89 × 0.0145 + 0.016 = 0.072 dB < 0.1 dB.

**Does D-T2's choice change these?** Yes, only Tol-2 and Tol-3 move with it. Tol-3 needs L2-F2. Tol-1 stays 3 because τ, not the SE, is the threshold.

**D-T1.5**
- **CS-3 + CS-NW: prefer, 0/1.** The BRAS rooms are the only ones with measurement behind them.
- **CS-2 + CS-NW: can live with, 1/1.**
- **CS-1: 2/2.** It has a single 20×30×10 m geometry and no small room (my P3).
- **For any set: the 2.5 m reference is uncertified in small rooms.**
  - `dead_booth` (2.5×2.0×2.2 m, fs ≈ 300 Hz at an assumed T = 0.25 s) has one patch per face, and `living_room` is similar.
  - The reference ℓ must be laddered per room until it changes by < 1 %. That is cheap there.
- CS-NW is required whatever D-T1.6 is. Without it the near-wall handling is never tested.

**D-T1.6**
- **NW-1 (point): can live with, 1/2.** Unbiased. Caps will be hit in layout-4-class rooms (47 M paths at the corner for 0.083 dB), which is exactly the class the switch exists for.
- **NW-2: 2/2.**
  - h = ℓ is not the reference's gather in any useful sense. ref_hybrid averages injection and every generation over patches; NW-2 only does it on the last leg. A 2.5 m cell inside r_near = 1 m is also incoherent.
  - At h = 0.5 m, h becomes a new resolution parameter under the < 1 % rule, and it is uncertified: the 0.5→0.25 m change is 1.3 %.
  - The estimator switches at r_near, which can produce a step in the expected value that has not been measured.
- **NW-3: 1/2.** It is "the same model to a stated tolerance" only if τ includes the clamp bias. That bias was measured only in W1, at ≤ 0.093 dB, and it uses up Tol-3 at the W1 edge.
  - Physics: F3 gives a near-field expectation of 2p, independent of d. The clamp's bias is therefore the large-scale gradient of the field over 0.4 m, and that gradient is unmeasured next to an absorbing face.
  - It is not more honest physically. At 0.1 m, neither the point nor the clamp models the Waterhouse rise toward +3 dB at a rigid boundary (Kuttruff §8.7, Eq. 2.50). That rise matters where kd < 1, i.e. f < 546 Hz.
- **NW-4 (my addition): prefer [Hyp until measured], 0/1.** Generic reciprocity: start the paths at whichever endpoint is nearer a surface and gather at the other. It is unbiased and makes no model change, and one listener-started set serves all emitters. When both ends are within 0.5 m of a surface, it falls back to NW-1's cost.

**Evidence.**
- Corpus: Kuttruff Eqs. 4.24, 4.29, 4.35 and §8.7; Vorländer Fig. 11.38 and Eqs. 11.21/11.28 (F6).
- From the code: `mc2`, `gather_kernel`, `injection`.
- [Observed]: C4, C6, C2.
- Dossier: F3, F5, F10–F14.
- [Inferred]: my arithmetic above.

**Conditions of acceptance.**
- T1-A or T1-B → 1: an adjoint solve per listener, and a measured C++ W1 below 1 s.
- N-1 → 1: escalate any diagnostic failure, i.e. become N-3.
- Tol-1 → 1: τ ≤ 0.25 dB.
- CS-1 → 1: add `dead_booth`, `living_room` (with laddered references) and one BRAS room.
- NW-2 → 1: certify h by a ladder and measure the step at r_near.
- NW-3 → 1: a long-run clamp-bias measurement in layout 4/5 next to the absorbing face, and τ budgeted for it.
- NW-1 → 1: NW-4 measured and adopted.

## D-T2
- **L2-F2: prefer, 1/1.** 3·SE ≤ 1 % is the faithful transfer of the settled rule. Cost: W1 59–82 ms per emitter; the 100 m cube 4.7–6 s; the W1 wall about 9 s under NW-1.
- **L2-F1: 2/2.** The difference E_2N − E_N has SD = SE_N/√2. At SE 0.083 dB it passes with p ≈ 0.54 per case-band, so the certification is a coin flip and re-seeding after a fail would be tuning. → 1 if replaced by its expected-value form, which is L2-F2.
- **L2-P (outer bands):**
  - In the 15 (A) cases, only air absorption separates the outer bands, so I expect the ℓ change to track 500 Hz–2 kHz [Inferred]. The BRAS rooms have band-dependent α and need C9.
  - Below fs (63–250 Hz in the booth and the living room), agreement only checks the code; GA itself does not hold there. That band needs a validity badge.

## D-T1 and D-T4c: worst case for (f), and my D-T4c condition
For (f), the fallback scenes are the cheap ones (the flutter scene ≤ 0.2 ms). The worst cases are:
- the non-fallback 100 m cube (144–183 ms at 0.083 dB);
- a near-wall listener in a concentrated-absorption fallback room (layout 4, s = 1, corner).

My D-T4c condition is restated: gate the non-fallback 100 m cube, and measure the 100 m cube with a corner listener. That scene is untested.

**Evidence at 100 m: none yet.**
- I propose a ref_hybrid ladder at the same *relative* resolution as the certified one: 20→10 m in the 100 m cube, i.e. 150→600 patches, ≈ 0.09→1.5 GB per band at about 1 035 bins (my arithmetic).
- Basis: GA is self-similar except for air absorption, so also run it with `--no-air-absorption`. At 10 m, ℓ/L = 0.1 is finer than the certified 2.5 m in a 10 m-high room [Inferred].

## D-T6
**Reading.** A bound for uniform-α rooms, fixed a priori. Cue: §4-5 (which parameter deviates).

- **Room set: RS-2 preferred, 0/1; RS-1 2/2** (a single room).
  - RS-2 + (my addition): one small uniform-α validation scene. The residual depends on t_mix/T and on few reflection orders inside the window.
  - Every uniform room in RS-2 is 2 400–6 000 m³.
- **Bound: B6-1 preferred, 0/0; B6-2 2/2.**
  - 0.43 dB is an empirical maximum from one geometry: α 0.15, s ≤ 0.4, t_mix 113.5 ms. The residual grows with s (+0.03 → +0.40 dB from s = 0.1 to 0.4) and depends on shape and on the window-to-T60 ratio.
  - For `stone_box` (s = 0.1, α = 0.05) it is about 10× too loose: a C++ error of 0.4 dB would pass. For s > 0.4 it is not a bound at all.
  - My variant: B6-1 gates, and |ΔL_ref| > 0.43 dB is reported as a physics finding.
- **Mixed-α rooms: M-2 preferred, 0/0; M-1 1/2.** The tracer is the only independent referee of ref_hybrid, which has never been checked in a small room.
  - Condition: the tracer's r_d must be below the listener clearance, and it must be run at two radii (F2 practice). In the booth, r_d = 0.5 m is a quarter of the width.

## Checks for the orchestrator and researcher
1. NW-4 run on C4's listener-near-wall cases, plus forward/adjoint agreement on the 15 (A) cases.
2. The 100 m relative-ℓ ladder (C7).
3. An independent near-wall reference for layout 4: the tracer with r_d < 0.1 m at two radii, or ref_hybrid with patches refined locally around the listener.
4. Small-room reference ℓ ladders (`dead_booth`, `living_room`).
5. The NW-3 clamp bias in layout 4/5.
6. Schröder 2011 (RQ-T1-4).

## Hand-offs
- **Seat 1:** whether the clamp's 0.03–0.09 dB shift and the escalated −1 to −4 dB reads are audible; the multiple-comparison rule.
- **Seat 5:** cross-architecture determinism (libm, FMA); threads inside the gate; CI runtime of CS-3.
- **Seat 6:** whether users see a cap hit, and the validity badge.
- **Seat 9:** realism of the Waterhouse effect near walls; whether real rooms are ever uniform-α.
- **Seat 7:** what "validated" can mean without RQ-T1-4.

## Premortem
If N-1 or Tol-1 wins, a producer puts the listener in a booth corner and gets a tail 1–4 dB low with no flag. The first to notice is Seat 9's corner-position listening in Phase 08, not CI.

Files: /home/user/makroof/tools/validation/phase05b2_dt1.py (`mc2` L88–92: the N-dependent stratification), /home/user/makroof/tools/acoustics/ref_hybrid.py (`gather_kernel` L319–349), /home/user/makroof/tests/scenes/valid/dead_booth.json, /home/user/makroof/tests/scenes/valid/stone_box.json
