# Seat 2 — confirmation S2-a (D-T1.3 N-3W*** and D-T1.6 note U)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 2 POSITION: confirmation S2-a (round 3; D-T1.3 N-3W*** and D-T1.6 user note)

**Summary.** I rate N-3W*** with U as *prefer*, 1 now / 1 later. I rate U′ (my literal C5) as *can live with*, 1 now / 2 later. I withdraw my literal C5 and accept U, on one condition: a replicate check of the region where U stays silent.

**1. Reading.** The question is whether N-3W*** meets my C1–C5, and which user-note predicate keeps the output honest. The cues it triggers are §4-7 (cost growth with the window) and my criterion 5: show uncertainty, never false precision, and badge validity rather than noise.

**2. Ranking.**
- **N-3W*** with U: prefer.**
- **N-3W*** with U′: can live with.**

**3–4. Tension now and later.**

| option | now | later | reason |
|---|---|---|---|
| N-3W*** + U | 1 | 1 | See "Rule checks" and "Where U fires" below. |
| N-3W*** + U′ | 1 | 2 | See "Why U′ is worse" below. |

*Rule checks on N-3W*** (from file 29, §D-T1.3).* C1 to C4 are met as file 29 states.
- **C1:** the pilot stops on cumulative joint work at W_scene/2.
- **C2:** the final range starts at 8 000, whatever N is.
- **C3:** N = max(N_need, n*).
- **C4:** W_max is a pinned constant counted in image evaluations.
- **Joint histories.** A history is two forward paths plus one listener-started path, with N_need taken as the maximum over emitters and bands. Each emitter's estimate stays unbiased (a fixed geometric w, disjoint ranges).
- **Shipping the pilot when N_cap is under one block.** That is acceptable because the pilot stops on work, not on its own SE, so F12's SE-coupled stopping bias does not apply. Only a weak work–score correlation remains [Inferred]. It is flagged.

*Where U fires and where it stays silent (C13 §2, C14 (b)/(d)).*
- **Fires:** every both-near case in C13, including the capped ones whose median reads −0.35 to −6.72 dB. That error is the one my "stated edge" exists for.
- **Silent on good estimates:**
  - the D-T6 small room (SE 0.006 dB, replicates within ±0.015 dB of a reference converged to 0.0003 %);
  - `concert_hall_box` (SE 0.054 dB, 0.05 jnd).
- **Silent but not yet checked:** capped one-end cases with VOV ≥ 0.1 and SE ≤ 0.33 dB.
  - Layout 5 one-end cases are already measured as fine: median −0.17 to +0.07 dB and p5/p95 within −0.50/+0.39 dB against the long runs; the largest single error is 0.69 dB.
  - The closed 100 m cubes at s = 0.3 (capped, SE 0.13–0.20 dB, VOV 0.31/0.37) have **no replicates**, so their median shift is unmeasured.

*What U commits later phases to.*
- W_max and n*_max get re-pinned from the C++ cost: one golden round.
- I owe the measured both-near fallback (debt register, S1 row).
- The near-corner reference is still owed.
- VOV is a random statistic, so U can flip between neighbouring placements. Seed S-1 makes it deterministic per scene, and Phase 11 evaluates U on the settled scene, so this is minor [Inferred].

*Why U′ is worse.*
- My C5 assumed that a geometric both-near criterion marks a weak estimate in any room. **C14 (d) refutes that.** The heavy tail scales with d relative to the path lengths inside the window, not with d alone (window 23 ms in the small room against 0.16 s in W1).
- In booth-class rooms almost every placement is within 0.70 m of a surface at both ends. U′ would put "approximate" on 0.006 dB estimates.
- A bare cap hit would also raise the note at 0.09–0.20 dB SE (0.1–0.2 jnd).
- A note that fires on good estimates carries no information; this is the same reason I demoted the slope flag. Users would learn to ignore it before it fires on a −6 dB both-corner tail.
- U′ also merges two different limits: the GA badge below fs, and Monte Carlo noise.

**5. Evidence.**
- [Observed] C13 §2–§4; C14 (b), (c), (d); file 29, §D-T1.3 and §D-T1.6.
- Dossier F12 and F14.
- [Inferred]: the window-relative tail and the U flip.

**6. Conditions of acceptance.**
- **U, 1/1 → 0/1:** run 30 replicates of the shipping rule in the closed 100 m cubes at s = 0.3, against the long run or the tracer.
  - Pre-register the pass: |median| ≤ τ (0.25 dB) and p95 |error| ≤ 1 dB (Seat 1's C13 form).
  - If it fails, add "cap hit AND VOV ≥ 0.1" to U for that class. That is a predicate change, not a new option.
  - Also keep the decider's CI list of U at the default placements of fixtures and presets.
- **U′, later 2 → 1:** only if a geometric criterion is shown to carry over between rooms. C14 (d) says it does not, so in practice the condition is "use U".

**7. Hand-offs.**
- **Seat 6:** the note's wording and its ±x.
- **Seat 1:** its 2/2 rests on W_max (Q2), not on U.
- **Maisara:** Q2. On n*_max, engine-wise both options are inaudible; a value ≥ 1 000 keeps the pilot's VOV meaningful (F10 needs ≥ 500 non-zero scores).
- **Orchestrator:** the 100 m replicate run above.

**8. Premortem.** If U′ ships, booth users see "approximate" on nearly every placement and learn to ignore it. A real both-corner tail reading 6 dB low then goes unnoticed, until Seat 9's corner listening in Phase 08 catches it.
