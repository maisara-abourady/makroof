# Seat 9 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 9 POSITION (second round: D-T1.6, D-T1.3, D-T2)

The corpus is present. My persona's assumptions are not contradicted here. One of my own first-round premises has fallen: for NW-3 I said "the GA mean barely depends on d, ≤ 0.09 dB". That held in W1 but is false next to an absorbing face (19 §6).

**1. Reading.** The question is how the tail level is estimated when the listener or the emitter is near a surface, how many paths are used, and under what < 1 % reading. My cues:
- the listener position and channel (C1 step 1);
- reference provenance (§4 row 8);
- an absorbing face near the seat (people and treatment, criterion 5);
- large venues near 100 m.

**2–4. Ranking and tensions** (now / later)

| item | option | label | now | later | reason (my measures) |
|---|---|---|---|---|---|
| (a) D-T1.6 | **NW-4C** | prefer | 1 | 1 | It is unbiased and changes no model, and it passes my absorbing-face checks. Against `ref_hybrid` at 1.25 m: layout 4 floor −0.006 dB, layout 5 wall +0.030 dB, i.e. ≤ 0.03 jnd of G (C12 (a); Vorländer Table 6.1). With one end near a surface, its SE equals the SE at the reference positions. The 1 cm listener sweeps step by ≤ 0.04 dB, against 0.358 dB under NW-1 with N-2 (C12 (b); 19 §4). My NW-1 condition is met: with both ends near surfaces the result is flagged "near-wall, unreferenced". What it still costs me: (i) at the layout 4/5 edges and corners it disagrees with the 1.25 m reference by −0.376 to +0.139 dB (\|z\| up to 12.4). Above τ = 0.25 dB, that leaves no certified reference at those seats (C12 (a) reading 2). (ii) One unexplained outlier, see the conditions. Debt: the weight is a formula, so undoing it is a parameter change. The evidence arrives from a finer local reference and from the BRAS nightly run. |
| (b) D-T1.6 | **NW-3**, re-rated | can live with | **2** | **2** | **My first-round cell changes from 1/1 to 2/2.** The clamp moves E_target by +0.322 dB at layout 5's absorbing wall and +0.109 dB at layout 4's absorbing floor (19 §6), and by −0.11 / −0.25 dB at layout 4's wall and edge (19 §4). Next to an absorber the gradient of the diffuse field is real, even inside GA: that face returns no diffuse energy. The clamp erases that gradient. 0.32 dB is 0.32 jnd, so it is not audible on its own and not veto-grade. But it is more than τ, so it cannot be budgeted, and a listener next to a treated wall is a common seat (S4, control rooms). My round-1 honesty argument (ρ = r_d = 0.5 m) is moot now that NW-4C is unbiased. Later: it is a model bias that no check can bound, and undoing it would take an AX change plus golden rounds. |
| (c) D-T1.3 | **N-3W\*** as composed | can live with | 2 | 2 | Conflict 1: n_cap = 0 in W2 and in the gated 100 m flutter cube (C12 (d) reading 3). The rule then publishes no defined estimate in the largest and most reverberant gated scene, which is the cathedral and arena class I protect. Conflict 2: the final SE is 0.07–0.10 dB and above target in 6 of 17 cases. That is ≤ 0.1 jnd, so not audible, but the published number is less precise than the pilot that was thrown away. |
| | **N-3W\*** with my conditions | prefer | 1 | 1 | See §6. |
| (d) D-T2 | **L2-F1R** | can live with | 1 | 2 | It fixes my round-1 objection: L2-F1 was a coin flip that invited re-seeding, and at p ≥ 0.999 per case it is repeatable. But the precision it buys (SE 0.0187 dB) is about 1/53 jnd, and below 1 JND I do not spend engine budget (§2, criterion 1). Later: at 100 m it needs ≈ 7× W_max, a restore of ≈ 3.7 s against 2.14 s (C12, coupling). If that leads to a size or range limit, or to slow restores for large-venue presets, cathedral and arena presets cannot be A/B'd within a session (C3 step 4). |

**5. Evidence**
- **G jnd 1 dB:** Vorländer Table 6.1 [corpus].
- **Near-wall pressure term GA leaves out:** Kuttruff Eq. 2.50 [corpus]. Redone at 0.1 m with 1 + sin(2kx)/(2kx) for a single tone: +2.93 / +2.71 / +1.84 / −0.64 dB at 125 / 250 / 500 / 1000 Hz. This applies to every option. Within about λ/2 of a surface the tail is GA-true, not room-true.
- **Measured inputs:** NW-4C and N-3W\* figures from C12 (a)(b)(d); NW-3 bias from 19 §4 and §6 [Obs, in-repo].
- **The layout-4 emitter-edge outlier** (32 k vs long run −0.273 dB, z ≈ −3.7; long run vs reference +0.139 dB, z +5.4). My arithmetic: P(\|z\| > 3.7) ≈ 2.2·10⁻⁴ per case, about 0.4 % over 20 cases. That is unlikely to be "an outlying draw" [Inf]. A heavy tail the 32 k VOV cannot see is one candidate [Hyp].
- **Edge and corner disagreements:** they are consistent with a reference error. The independent 2 M forward runs agree with NW-4C at z ≤ 1.16, but those runs are themselves heavy-tailed, so the check is weak (C12 (a)). [Hyp] that the reference is the one at fault.

**6. Conditions**
- **NW-4C stays at 1/1 only if:**
  1. The layout-4 emitter-edge case is rerun on a third disjoint range, and the result is either explained or attributed to the reference. Until then later is 2.
  2. The 2.5 → 1.25 m change of the reference is recorded at the layout 5 edge and corner too. If it is > 1 %, those cases are "reported, not gated", as for layout 4 under D-T1.5, and carry an explicit "reference uncertified" note.
  3. The AX row states the GA validity limit near surfaces (the Kuttruff Eq. 2.50 term, about λ/2), so no reader takes the 0.1 m tail level as room-true. This is consistent with Seat 7's wording.
- **NW-3 → 1/1:** the measured clamp bias is ≤ τ/2 (0.125 dB) at both absorbing-face cases and at the layout-4 edge. At ρ = 0.5 m it is not, and I do not know a ρ at which it would be [Hyp].
- **N-3W\* → 1/1:**
  - **Conflict 1:** define the pilot by work, as n\* = min(8 000, the histories that fit a fixed share of W_max, e.g. ≤ 50 %). Floor it at a minimum number of histories that Seat 1 or Seat 2 sets for VOV to mean something; I cannot source that number. When the floor binds, raise the same flag as a cap hit.
  - **Conflict 2:** set a minimum final N ≥ n\*_eff, so the published SE ≤ the pilot SE. C12 shows this costs ≤ 2× the pilot's work and fits W_max in all 17 cases.
  - W_max must be re-derived from the C++ cost per evaluation (C12 (d)).
- **L2-F1R later → 1:** either Maisara accepts the bias reading, with a pooled high-N bias check < 1 % in every band and the BRAS report printing the Monte Carlo SE beside the ensemble spread (my D-T1.2 debt), or the restore bound is shown to hold at 100 m without a size limit.

**7. Hand-offs**
- **Seat 2:** the emitter-edge outlier; a finer local reference near edges and corners; the weight w with absorbing versus reflecting nearest faces.
- **Seat 1:** the pilot's minimum history count; whether pooling would violate F14.
- **Seat 5:** the restore cost of L2-F1R and the re-derived W_max.
- **Maisara:** the AX36 reading (bias or strict) and Challenge 1.
- **Researcher:** feasibility of a small-detector tracer (r_d ≤ 0.05 m) at the layout 5 corner [Hyp].

**8. Premortem.** Suppose NW-3 is adopted and fails. A producer puts the listener beside the absorber panel in a treated-room preset and gets a tail 0.3 dB too hot that no check flags. The first to notice is the interrogator, finding a near-absorber case left out of CS-NW+ so that it passes.

Files read:
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
- /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md
- /home/user/makroof/docs/review/phase-05b2/18-seat9-T1-T2-T6.md
