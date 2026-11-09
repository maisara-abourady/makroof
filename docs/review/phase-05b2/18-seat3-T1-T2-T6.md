# Seat 3 (reverb renderer) — positions on D-T1, D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

SEAT 3 POSITION

Corpus is present (revision c1b171f). I read the option block and its addendum (files 9 and 17), phase-05b2 §0–§8, the builder evidence (7), C4 (16), the dossier (14), the D-T5/D-T4 finals (10, 13), C2, `mc2`/`step_c6`, `NoiseTail.cpp` (L53–55, L108–162, L248), `test_tail.py` (seam gate L366–414, envelope step L558–590), AX5, AX11, AX16, AX18, AX19, AX21, AQ4 and AQ10, and Vorländer Table 6.1 and §11 (the EASE paragraph and Fig. 11.38).

**What my ratings depend on:**
- D-T5.2: t_mix,e is fixed before the solve, so T1-F gathers in a known window and the AX22 jump points do not move.
- D-T4b: no cache credit. T1-F needs no cache.
- D-T4a (i): one diffuse solve per process. This interacts with N-2/N-3 near walls (see D-T1.3).

**What the prototype times are:** numba code in a container, single-threaded except C4, which used 4 threads. They are not measured on the named machine (my §12), so every time below is scale only.

---

## D-T1

**1. Reading.** The question is how the diffuse E_target is computed, how precise it must be, and what it is tested against. It triggers these §4 cues:
- **Cost:** build time and memory per instance.
- **State discontinuity:** level steps and update-rate staircases under automation.
- **Decay/level accuracy:** whether the tail level matches the room.

**2–4. Ranking and tension (now/later), with reasons.**

**D-T1.1: formulation**

- **T1-F: prefer. 1/1** with NW-3, or NW-1 under N-3 with a time-bounded N_max; **later 2 otherwise**.
  - Now:
    - Memory is under 2 MB.
    - W1 costs 1.8–2.5 ms per emitter at SE 0.083 dB, which leaves the AQ4 interval at about 32 ms.
    - Under source motion the steps between C6 points are ≤ 0.037 dB (8 000 paths, layout 4 at s = 1). They are pure gain changes on the same cached noise, faded over 30 ms, about 1/27 of the 1 dB G jnd.
    - The room-size steps (0.014–0.020 dB per 0.1 %) are identical to AX16's.
  - Later: a new estimator class whose agreement rests only on in-repo references (RQ-T1-4 is uninformed). Near walls the cost is ×100–10⁴ (D-T1.6).
- **T1-B: cannot live with. 2/3.**
  - Now: about 9 s per rebuild in the AQ10 room at an assumed 2 ns per evaluation [Hyp]. Every position update becomes a step about 9 s apart, against Table 15.1's 700 ms for the specular part.
  - Later: 1 454 s per generation at 100 m. A room-size bounce at 100 m would take days.
  - Undo cost: a rewrite of the diffuse unit.
- **T1-A: cannot live with. 3/3.**
  - Now: it needs 1.53 GB in the AQ10 fallback room and 2.53 GB in CR4, both above D-T4a's 1 GB ceiling in ordinary rooms. The numpy W1 is about 15 s, so position automation becomes a staircase of crossfades between nearly uncorrelated IRs: AX18 gives ρ < 0.414 beyond about 6 cm at 1 kHz. That breaks my criterion 1.
  - Later: it forces D-T3, a major contract bump.

**D-T1.2: seed (T1-F)**

- **S-1: prefer. 0/1.**
  - The level is a property of the scene, and tailSeed changes only the noise.
  - Later: the Monte Carlo offset is fixed per scene, so τ must budget it explicitly, because ensembles cannot average it out.
- **S-2: can live with. 1/1.**
  - Now: a seed change already decorrelates the tail (AX18, equal-power). An extra level change of about 1 SE (≤ 0.083 dB) is inaudible.
  - Later: σ₁ in AX19 gains a small level term.

**D-T1.3: N rule.** Ratings are under Tol-2; L2-F2 changes them, shown in brackets.

- **N-3: prefer. 1/1 [L2-F2: 2/2].**
  - It is the design without stopping bias (F14).
  - With N changing on position sweeps, C6 measured steps ≤ 0.018 dB, which is inaudible.
- **N-2: can live with. 1/2 [2/2].**
  - Prefix reuse stops on low means (F12), and the size of that bias is unknown.
- **N-1: can live with. 2/2 [3/3].** Every scene pays for the worst case:
  - N = 22 000 at 1.51 µs per path (W1: 12.1 ms / 8 000) gives about 33 ms per emitter, so about 66 ms for W1. That misses AQ10's 50 ms target.
  - Under L2-F2, N ≈ 726 000 gives about 1.1 s per emitter in W1 (about 9.6 s in the 100 m cube). Position updates then come more than 700 ms apart: a staircase.
  - It does not bound the SE near walls (D-T1.6).

**Coupling, true of every N rule.** Near-wall solves take 0.14–2.0 s per emitter in W1 (C4 path counts × 38–47 ms per 32 000 paths) and 32 s to about 19 min in layout 4. Under D-T4a (i), one such solve holds the per-process gate, and every other instance goes stale for that long. Yet T1-F needs only 2 MB, so the gate's memory reason does not apply to it. **This is later 2 for N-2 and N-3 unless N_max is bounded in time.**

**D-T1.4: τ (with SE target τ/3)**

- **Tol-2: prefer. 0/1.** R = 0.019, below MCNP's 0.05 for point detectors (F7).
- **Tol-3: can live with. 1/2.** W1 costs 12–16 ms per emitter, so W1 lands at about 50–60 ms. That is six times the cost for 0.033 dB.
- **Tol-1: can live with. 2/2.**
  - τ is 1 dB, the G jnd, so a C++ port could drift by as much as the 1.1–1.2 dB deficits in layouts 5 and 6 that the switch exists to fix.
  - R = 0.079 fails the point-detector reliability rule.
- **Under L2-F2:** the SE target is overridden, so τ only sets the test tolerance. Tol-1 stays 2.

**D-T1.5: case set**

- **CS-2 + CS-NW: prefer. 0/1.** CS-2 covers the fixture rooms whose goldens change.
- **CS-3 (+NW): 0/1.** Its CI cost is Seat 5's to rate.
- **CS-1: 1/2.** The Phase 04 rooms' tail goldens would change on a level never agreement-tested in those rooms.
- **Without CS-NW: +1 later on any set.** No case would have a listener within 0.5 m of a surface, although placing one there is an ordinary user action.

**D-T1.6: near-listener handling**

- **NW-3: prefer. 1/1.**
  - The clamp (projection onto the inset box) is continuous in position.
  - Variance falls 4–7×.
  - E_target shifts ≤ 0.093 dB in W1.
  - The specular entries keep the true position, so the near-wall cues a listener actually hears (strong early reflections) still follow the listener.
  - F3 (derived) gives a mean near-wall gather independent of d, so the clamp mostly removes variance, not signal.
  - Later: ρ becomes a model parameter, and there is no evidence for it in concentrated-absorption rooms.
- **NW-2: can live with. 1/2.**
  - It reduces variance 2–4× at a wall but little at edges and corners.
  - If its cells sit on a fixed grid, a moving source reintroduces patch-boundary steps. The switch at r_near is a step per path.
- **NW-1: can live with, 2/2 under N-2/N-3; cannot live with, 3/3 under N-1.**
  - At 32 000 paths, single paths carry 5–73 % of the estimate, and the tail reads 1.06–3.9 dB low (C4).
  - That is a silent level error above the jnd in an ordinary position, and it breaks my criterion 2.

**5. Evidence.**
- [Observed, corpus] G jnd 1 dB, EDT 5 %, C80 1 dB: Vorländer Table 6.1.
- [Observed, corpus] Diffuse rain scores a finite detector sphere, not a point: Fig. 11.38. In EASE/CAESAR the diffuse part runs at "lower spectral and temporal resolution": Vorländer §11. Both are kin to NW-3.
- [Observed, corpus via AX18] Crossfade correlation and mid-fade dips: Vorländer Eqs. 4.14–4.16.
- [Observed, corpus via AQ10] Update intervals: Vorländer Table 15.1.
- [From the code] The tail is the same seeded unit decay scaled by √(E_target/ē_b) (`NoiseTail.cpp` L248; `makeUnitDecay(decay, seed, stream)`).
- [Measured] C4, C6 and builder §3.
- [Derived, unsourced] F3.
- [Hyp] The staleness arithmetic, T1-B's 2 ns rate, and every C++ time.

**6. Conditions of acceptance.**
- **T1-B → 2:** only if C8's measurement beats the arithmetic by about 500× at 100 m. No condition I can name brings it to 1.
- **T1-A:** none. A range limit is a contract change, so it is Maisara's call.
- **N-2/N-3 → 1/1:**
  - N_max is set so that one solve is ≤ 3 s per emitter on the CI runner (Table 15.1's 3 s row, by extension).
  - Cap hits are escalated.
  - Alternatively, the decider exempts sub-2 MB solves from D-T4a's gate. That reopens D-T4a (i), which is for Seat 5 and the decider.
- **N-1 → 2:** only with NW-3 and Tol-2.
- **Tol-1 → 1:** add a mean signed-z bias check across cases.
- **NW-2 → 1:**
  - cells centred on the hit point;
  - a blend across r_near instead of a switch;
  - a listener sweep (below) showing steps ≤ 0.05 dB per cm [Hyp].
- **NW-1 → 1:** N-3 plus a time-bounded N_max plus CS-NW.

**7. Hand-offs.**
- **Seat 2:**
  - whether NW-3 is "the same model to a stated tolerance";
  - an adjoint Monte Carlo started from the listener would serve all emitters with one path set (about E× saving per listener move) and move the near-wall singularity to the emitters [Hyp].
- **Seat 5:** the gate coupling; CI cost.
- **Seat 6:** whether the user sees cap hits.
- **Seat 9:** real near-wall positions.
- **Orchestrator:**
  - **C6-NW:** a listener sweep from 0.5 to 0.1 m off a wall, and along a wall at 0.1 m, in 1 cm steps, under N-1, N-3, NW-2 and NW-3. C6 swept only the source.
  - Multithreaded C++ W1 under N-1 and L2-F2.
  - Whether NW-2's cells are on a grid or centred on the hit.
- **Researcher:** measured late or diffuse energy versus listener distance 0.1–0.5 m from a wall, to see whether NW-3 hides anything real.

**8. Premortem.** N-1 with NW-1 ships. A producer pushes the listener against the wall of an absorbent-floor venue preset, the tail drops 1–4 dB, and Maisara hears it first in the listening pack.

---

## D-T2

**1. Reading.** The resolution rule under T1-F. It triggers the cost cue and the "match nobody can hear" cue (my §1).

**2–4. Ranking and tension.**
- **L2-F2: can live with. 2/2.**
  - W1 costs 59–82 ms per emitter, so 118–164 ms for W1. That misses AQ10's 50 ms target and Phase 10's 100 ms staleness gate (R ≤ 39 ms, my D-T4 arithmetic [Hyp]).
  - At a W1 wall the solve takes about 8.4 s per emitter.
  - The precision bought is 0.0145 dB, about 1/70 of the G jnd.
- **L2-F1: can live with. 2/2.**
  - It costs about half of L2-F2: passing needs SE ≈ 0.47 % if the doubling difference has SD ≈ 0.71·SE [Hyp].
  - A random fail invites changing the seed, which is tuning.
- **L2-P:** I do not rate it on its own. It goes with T1-A/B, and near walls ℓ = 2.5 m is not certified (4.75 % at the layout 4 edge).

**6. Conditions of acceptance.** L2-F2 drops to 1 if multithreaded C++ W1 at L2-F2 is measured at ≤ 50 ms.

**Challenge for Maisara.** I raise this as a flag; I do not offer it as an option. The < 1 % rule bounds a discretisation bias, and T1-F has no discretisation. If she rules that D-T1.4's SE target alone governs, both cells drop to 1.

**8. Premortem.** Under L2-F2 plus N-1, W1 exceeds 1 s, and Phase 10 finds the position staircase.

---

## D-T6

**1. Reading.** The bound for uniform-α rooms, and how the seam and decay changes are reported. It triggers the decay/level and seam cues.

**2–4. Ranking and tension.**

| options | rating (now/later) | reason |
|---|---|---|
| **RS-2** | prefer, 0/1 | Includes s = 0.4, where the residual is largest (0.43 dB) |
| RS-1 | 1/1 | One room at s = 0.1 (residual +0.03 dB) never exercises the bound |
| **B6-1** | prefer, 0/1 | It is the agreement relation fixed before C11. A fail means the C++ differs from the model, which is the only defect fixable without tuning |
| B6-2 | 1/2 | 0.43 dB comes from one geometry. A fail at `stone_box` or W1 could be a property of the model, and the only "fix" would be tuning (NFR-8) |
| **M-2** | prefer, 0/1 | |
| M-1 | 1/1 | Five mixed rooms' goldens change on a model-vs-model check only |

**6. Conditions of acceptance.** B6-2 drops to 1 if an excess is reported and escalated rather than blocking, or if B6-1 is gated and B6-2 is printed as a flag.

**How the seam and decay changes should be reported (B3)**
- **(a) Paired, same tailSeed.**
  - From the code, the before and after tails are identical noise with different per-band gains. So the tail-level change is deterministic in one realisation.
  - Report ΔL_rendered,b, the band-energy ratio after t_mix,e + 2.5 ms in the AX14 central half octave, beside 10·log10(E_after/E_before) from `--diagnostics`.
  - I propose gating it as a plumbing check within 0.02 dB [Hyp tolerance] (Seat 5).
- **(b) Seam step.**
  - Use the `test_envelope_step_reported` metric (±10 ms around the handover, expected decay removed): before, after and the difference, per emitter and all 8 bands, at the same R.
  - The EDC seam gate (|step| ≤ 1 dB, R = 16) keeps running on the switched IRs. A failure is a finding, not something to tune.
- **(c) Decay.**
  - ΔEDT, ΔT30, ΔC80 and ΔG are reported as paired differences over R = 16 seeds, giving the mean and the maximum.
  - Pairing cancels most of AX19's σ₁ (EDT at 63 Hz up to 31.5 %); the paired spread should be measured once [Hyp].
  - ΔT30 should be about 0 (B12). Anything outside the paired spread flags a plumbing fault.
  - Values are stated against Table 6.1's jnds, by extension outside 500–1000 Hz.

**7. Hand-offs.**
- Seat 2: whether 0.43 dB transfers to `stone_box` and W1.
- Seat 1: audibility of the reported deltas.
- Seat 5: gating (a), and the CI cost of M-2.

**8. Premortem.** Under B6-2, W1 exceeds 0.43 + τ for a model reason, the bound gets moved after the number is seen, and the contracted engineer finds it at review.
