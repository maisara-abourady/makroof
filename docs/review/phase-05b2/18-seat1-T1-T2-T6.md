# Seat 1 (perceptual gatekeeper) — positions on D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 1 POSITION

The corpus is present (c1b171f). One persona assumption no longer holds: v1 has no head tracking (AQ4, AX31) and uses one generic HRTF (AQ6), so my motion thresholds T1 and T2 do not apply here. I rated D-T4/D-T5 on the final texts (10-, 13-). None of my ratings depends on D-T4a. Yardstick: a tail-only error ΔL moves G by less than ΔL, ΔG = 10·log10(1 + f(10^(ΔL/10) − 1)), where f is the tail's share of the energy; the G jnd is 1 dB [corpus Vorländer Table 6.1, 500–1000 Hz; other bands by extension]. The bar is plausibility, because a DAW has no real reference (T3, T6).

---

## D-T1 (sub-questions 1.1–1.6)

**1. Reading.** How the shipped tail level is estimated, how precisely, and how it is tested. Cues triggered: the maker's estimator judged against its own logic (O4); the hardest signal (B2), which here means the near-wall listener; a threshold that must carry its method; level steps under automation.

**B1 answers**
- **Per-scene random error.**
  - SE 0.0145, 0.033 and 0.083 dB are ≤ 0.08 jnd. Inaudible as a level offset, even before the f reduction.
  - SE 0.33 dB is 1/3 jnd at 1 SE. But at 2–3 SE, 0.66–1.0 dB, it reaches the jnd in a minority of scene-bands. Its R of 0.079 also fails MCNP's point-detector grade (< 0.05, F7). [Inferred]
- **Automation steps** (C6): ≤ 0.037 dB per 1 cm step, ≤ 0.018 dB for N-2's batch changes. That is ≤ 0.04 jnd. In the room-size sweep, AX16 itself steps 0.014–0.020 dB. Inaudible [Observed C6; Inferred]. Not yet measured: a **listener** sweep toward a wall (see item 1 under Hand-offs).
- **S-2 level change on a tailSeed change:** ≈ 1 SE, i.e. 0.083 dB at Tol-2. Inaudible, and the change of noise texture dominates any A/B [Inferred].
- **D-T2's 1 % (0.043 dB):** a numerical convergence rule only, at 0.04 jnd. It has no perceptual basis.
- **NW-3's +0.03 to +0.09 dB and NW-2's 1–3 % (0.04–0.13 dB):** inaudible (≤ 0.13 jnd) [Observed C4; corpus Table 6.1].
- **An escalated near-wall estimate 1–4 dB low:** that is the "tail too weak" fault this phase exists to remove. In CI or validation scenes I accept escalation, on two terms: a cap-hit value never counts as an agreement pass, and the scene goes into the listening pack. In user scenes, escalation reaches nobody. I accept it there only under NW-3, with N_max at least the paths that bring C4's worst case (layout 4 edge and corner under NW-3, ≈ 1 M paths) to SE ≤ 0.33 dB with VOV < 0.1. Otherwise I rate it 2.

**Agreement-test decision rule I require** (for any stochastic option)
1. **Pre-register before any C++ number:** seed, test N per case, the case set, τ and this rule.
2. **Multiple comparisons.** CS-3 + CS-NW is 64 cases × 8 bands = 512 case-bands. At |z| > 3, a correct implementation fails somewhere with probability ≈ 0.16 (bands fully correlated) to ≈ 0.75 (independent). So the CI run uses its own N, chosen so that z_FW·SE_test ≤ τ − ℓ_ref.
   - z_FW = 4.27 (Bonferroni at a family α of 1 % over 512).
   - ℓ_ref ≈ 0.03 dB (near-wall 0.65 %).
   - Under Tol-2 this gives SE_test ≤ 0.052 dB, ≈ 2.6× the shipping N.
3. **Pooled bias check per band:** |mean signed z| ≤ 3/√M over the cases. It catches a shared bias of ≈ 0.02 dB, and a shared bias shifts every user's tail.
4. **On a fail:** no reseed, no added N for the failing case, no widened τ, no dropped case. One stage-2 rule, written before stage 1: re-run **all** cases on a disjoint, pre-registered path range at 4× N. The decision rests on stage 2 alone, under the same family rule. A stage-2 fail is a defect, investigated in the implementation, or escalated to Maisara with numbers if the reference's ℓ is the cause.
5. **N-3** makes the per-case z honest (a fresh sample). Under N-2, the test must run at a pre-registered fixed N, not through the stopping rule (F12).

**2–4. Ranking and tension (now/later)**

**D-T1.1 Formulation**

| option | label | now/later | reason |
|---|---|---|---|
| T1-F | prefer | 1/1 | Now: at finite N, a near-wall listener reads low (W1 corner −1.06 dB, layout 4 edge −3.9 dB at 32 000 paths, C4) until 1.3 and 1.6 contain it. Later: no published validation (RQ-T1-4), so "validated" rests on the in-repo agreement and the tracer; C3 (outer bands) is pending. |
| T1-A | can live with | 1/2 | Forces D-T3. Large venues with open faces lose the correction, or a size threshold puts up to a 3.87 dB step into room-size automation. |
| T1-B | can live with | 2/2 | ≈ 9 s per rebuild in the AQ10 room at an assumed 2 ns [Hyp, C8], minutes to hours at 100 m. The monitored tail lags each edit by that long while the bounce is synchronous, so the user monitors something other than what is bounced. |

**D-T1.2 Seed**

| option | label | now/later | reason |
|---|---|---|---|
| S-1 | prefer | 0/0 | The seed changes only texture; the per-scene offset is ≤ 1 SE and inaudible. |
| S-2 | can live with | 0/1 | tailSeed becomes a hidden level control. Blind A/Bs across seeds then mix level and texture. |

**D-T1.3 Path count**

| option | label | now/later | reason |
|---|---|---|---|
| N-3 | prefer | 0/1 | Unbiased final estimate. Later: cap hits in extreme rooms. |
| N-2 | can live with | 1/1 | Stops on low means (F12), so it errs toward a quieter tail. |
| N-1 | can live with | 2/2 | Near-wall SE is unbounded. A 1–4 dB low tail ships silently, with diagnostics reported only. |

**D-T1.4 Tolerance**

| option | label | now/later | reason |
|---|---|---|---|
| Tol-2 | prefer | 0/0 | τ = 1/4 jnd; 3 SE = 0.25 dB. |
| Tol-3 | can live with | 0/1 | 6.25× the paths for no audible gain. Longer rebuilds mean larger automation steps. |
| Tol-1 | can live with | 2/2 | 1 dB of implementation slack covers the whole CR3 correction (−1.18 dB). R 0.079 fails F7. Combined with B6-2 it is 3 (see D-T6). |

**D-T1.5 Case set**

| option | label | now/later | reason |
|---|---|---|---|
| CS-3 + NW | prefer | 0/0 | Includes the BRAS rooms, where the correction is ≈ 1 jnd (CR3, the listening-pack scene), and the breaking scenario (B2). |
| CS-2 + NW | can live with | 1/1 | No realistic room with the correction near the jnd. |
| any set without NW | can live with | 2/2 | No case places the listener within 0.5 m of a surface, which is the known failure. |

**D-T1.6 Near-listener handling**

| option | label | now/later | reason |
|---|---|---|---|
| NW-3 | prefer | 0/1 | Shift ≤ 0.09 jnd in W1 and 4–7× less variance. Later: the shift in layout 4 is unmeasured. |
| NW-2 | can live with | 1/1 | Little variance cut at edges and corners, where the worst low readings were. |
| NW-1 | can live with | 2/2 | An ordinary user action gives an audible-class low reading at the cap. |

**D-T2 dependence.** Under L2-F2, S-2 drops to 0/0. The other ratings are unchanged: N-1 still cannot reach the W1 wall's 7.1 M paths.

**5. Evidence**
- [corpus] Vorländer Table 6.1; Fig. 11.38 (sphere detector).
- [Observed] C4, C5, C6; builder evidence §3.
- Dossier: F7, F11, F12, F14.
- [Inferred] The ΔG formula and the family-wise arithmetic above, redone here.

**6. Conditions**
- **T1-B 2→1:** C++ W1 ≤ 1 s measured in the AQ10 room.
- **N-1 2→1:** cap plus escalation, as in N-2.
- **Tol-1 2→1:** τ ≤ 0.5 dB.
- **Any set without NW 2→1:** add CS-NW.
- **NW-1 2→1:** N_max as stated in the B1 answers above.
- **T1-A later 2→1:** any D-T3 threshold is gated at ≤ 1 jnd of computed step.

**7. Hand-offs**
- Model sameness under NW-2 and NW-3: Seat 2.
- Physical meaning of a gather at 0.1 m: Seat 9. GA ignores the Waterhouse effect under every option [corpus Kuttruff §8, Waterhouse effect, around L3982; it describes the field near a rigid wall, +3 dB exactly at the edge].
- Time, N_max cost and CI runtime: Seat 5.
- Whether the user sees a cap hit: Seat 6.
- "Validated" wording: Seat 7.

**8. Premortem.** Under NW-1 with N-1, a producer puts the listener in a booth corner, and the tail comes out 1–4 dB weak, as in C4. Beta users with venue presets notice it first.

---

## D-T2

**1. Reading.** Does the 1 % rule need 33× the paths?

**2–4. Ranking and tension**

| option | label | now/later | reason |
|---|---|---|---|
| L2-P (if T1-A/B) | can live with | 1/1 | 0.014 dB, inaudible. Not certified near walls or in the outer bands (C9). |
| L2-F2 | can live with | 2/2 | Buys 0.0145 dB (0.015 jnd). At 4.7–6 s per emitter at 100 m and ≈ 51 s in layout 4, the update interval becomes metres of automation travel: stepping and lag (AX18 dips). The quality curve is flat here (criterion 6). |
| L2-F1 | can live with | 2/2 | Pass/fail is random at a fixed seed: a gate with no stated strictness. |

**Challenge, for Maisara, not reopened here.** AX36's < 1 % rule catches a systematic, unconverged discretisation error. The Monte Carlo analogue is bias. I would apply the 1 % rule to the pooled bias against long runs, with D-T1.4's SE governing the random part.

**6. Conditions**
- **L2-F2 2→1:** the 33× cost applies only to agreement-test runs, not to shipped builds (that needs Maisara's reading of AX36).
- **L2-F1 2→1:** restated as L2-F2.

**8. Premortem.** Under L2-F2, room-size automation in large rooms steps audibly and lags by seconds, to buy precision nobody can hear.

---

## D-T6

**1. Reading.** The regression bound for uniform-α rooms. Cues: a borrowed threshold (0.43 dB measured in one geometry); "nothing audible changes" is a claim that needs evidence.

**2–4. Ranking and tension**

| option | label | now/later | reason |
|---|---|---|---|
| B6-1 | prefer | 0/1 | Checks correctness per room. Later: audibility rests on the report, not the gate. |
| B6-2 (Tol-2) | can live with | 1/2 | 0.68 dB < 1 jnd. But 0.43 dB comes from α 0.15 at 20×30×10 m. If `stone_box` exceeds it, a correct model fails and the pressure is to tune. If `stone_box` is lower, ≈ 0.6 dB of implementation error passes unseen. |
| B6-2 (Tol-1) | cannot live with | 3 | 1.43 dB lets a "nothing audible changed" room change by more than 1 jnd. |
| RS-2 | prefer | 0/0 | |
| RS-1 | can live with | 1/1 | A single room cannot support a claim about uniform rooms in general. Under B6-2, RS-2's s-cases are the bound's own data, so they are circular. |
| M-2 | prefer | 0/0 | |
| M-1 | can live with | 1/1 | Without the tracer, "sounds like a correction" (checklist §6) is judged sighted, against a model checked only against itself (O1, O4). |

**Report I require** (not gated)
- **Pairing:** before (AX16) and after the switch, same scene, emitter and tailSeed.
- **Ensemble:** R ≥ 30 paired seeds. Report the mean paired Δ, its SE and the largest per-seed Δ.
- **Metrics:** ΔG, ΔC80, ΔEDT, ΔT30, and the seam step at t_mix,e. Seat 3 defines the seam step.
- **Bands and units:** all 8 bands. Values in jnd units for 500–1000 Hz; in dB or % elsewhere, labelled "by extension". T30 uses 5 % [register, ISO 3382-1, medium confidence; not in the corpus table].
- **Flag:** any |mean| > 0.5 jnd.
- **Scope:** RS-2, the mixed rooms and the listening-pack scenes.
- **Optional self-ABX for Maisara on `stone_box`:** clicks, pink bursts and voice; 16 trials each; ≥ 12 correct counts as detected. It is evidence for the claim, not a gate.

**6. Conditions**
- **B6-2 later 2→1:** Seat 2 shows that the residual does not grow with s, size or t_mix,e for `stone_box`.
- **B6-2 (Tol-1):** acceptable only with τ ≤ 0.5 dB.

**7. Hand-offs**
- Physics of the residual: Seat 2.
- Seam measurement: Seat 3.
- Whether real rooms are uniform: Seat 9.

**8. Premortem.** Under B6-2 at Tol-1, `stone_box` moves 1.2 dB, the gate passes, and Maisara hears it at the checklist.

---

## Requests for the orchestrator and researcher
1. **C6b (orchestrator):** listener swept from 1 m to 0.1 m off a wall, an edge and a corner, in W1 and layout 4 at s = 1, under NW-1/2/3 at the chosen N rule. Report the largest neighbour step and the drift against long runs. My acceptance: steps ≤ 0.1 dB [Hyp].
2. **Orchestrator:** NW-3's shift in layout 4 near walls, against a converged run.
3. **Orchestrator:** the correlation of (f)'s per-band errors across bands. If the bands are independent, the random error becomes a tone-colour tilt in the tail (T4), not a broadband level offset.
4. **Researcher:** the smallest detectable sudden level step in reverberant broadband or octave-band noise, and at a decay seam, from a primary source. Still open from D-T5.

Files read: /home/user/makroof/docs/review/phase-05b2/9-decider-convene-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/17-decider-convene-T1-addendum.md, /home/user/makroof/docs/review/phase-05b2/16-orchestrator-C4-near-wall.md, /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md, /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md, /home/user/makroof/docs/phases/phase-05b2.md, /home/user/makroof/docs/corpus/vorlaender-auralization.md (Table 6.1), /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Waterhouse effect, around L3982).
