# 1: Seat 5 (deadline keeper), M3, narrow: split or unsplit α; the click_check call

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE", Seat 5 narrow) and builder
file 32 ("Follow-up for the decider"). Run 2026-11-24 in the phase-07c-2b session as `seat5-deadline-keeper`.
Recorded verbatim from the seat's answer.

SEAT 5 POSITION

**1. What the question is.** I was asked two narrow things for M3. (1) Should α be split across the ABX families or left unsplit? This matters to me because a false "detected" result changes the worker-thread budget. (2) Is the `click_check` fix needed before the seal, and in which form? The cues it triggers: §4.5 (which clock pays), §2 criterion 5 (can the decision be reversed), and §1 ("passes auval" does not count as success). From what K5 found (file 32), `click_check` currently passes S-A because A's and B's peak frames happen to fall in the same place, not because it can tell a click from noise.

**Families per option** (rule from file 13 item 15: the 08-3 rerun counts at the bound in force, so a detection there also reverses AX47; union bound ≤ 0.049·n; I redid the arithmetic, independent: 1 − 0.951ⁿ):
- **V1:** 2 at 07c-2 plus 2 at 08-3, so 4 in total. Union ≤ 0.196 (0.182 if independent).
- **V2 and V3:** 1 at 07c-2 plus 2 at 08-3, so 3 in total. Union ≤ 0.147 (0.140).
- **V4:** 1 at 07c-2 plus 2 at 08-3, so 3 in total. Union ≤ 0.147 (0.140).
- **Per seat-hour:** families run at 08-3 cost my seat more if they reverse, because by then W_max (O4) and the class (c) admission are pinned.

I have no position on anything else in V1–V4.

**2. Ranking, question (1).**
- **Unsplit, at most 3 families: prefer.**
- **Split** (noise ≥ 13 and speech ≥ 13, 0.0213 per family): can live with.
- **Unsplit with 4 families (V1):** can live with.

**3. Tension now.**
- **Unsplit:** 1. The audio callback is untouched: AX47 says the step is measured on the builder thread and never in the callback.
- **Split:** 0.

**4. Tension later (the debt).**
- **Unsplit, 3 families: 1.** A false reversal sets B = 0.5 dB, so admission needs SE ≤ 0.255 dB instead of 0.51 dB. That is about 3.9 times the stage-1 work. Either W_max has to grow inside Seat 6's 3 s per emitter, or stage 1 becomes inadmissible on capped scenes and the load falls back to a slower path. The extra pool hold also bears on M7 (≤ 700 ms edit latency). The real problem: a false reversal is never found out, because no automated test can overturn it. Only a new person-ABX could, at about 2 h plus a reseal.
- **Unsplit, 4 families (V1): 2.** The extra reversal chance lands at 08-3, after O4 and O10. Undoing it means re-deriving W_max, re-running the admission round and a golden round.
- **Split: 1.** Noise power falls from 0.63 to 0.405 at p = 0.75. A real 0.9 dB audibility that goes undetected would show up at the earliest as a listening report at the L1 checklist or the Phase 13 beta. By then W_max is pinned and the goldens are frozen, so the undo is a re-pin plus a golden round. Whether that miss matters is Seat 1's ground.

**5. Evidence.**
- Binomial tails: file 31 answer 4, redone: 2517/65536 = 0.0384; 697/65536 = 0.0106.
- SE scaling with W as 1/√W: [Hyp]. It assumes the stage-1 samples are independent. **Researcher or Seat 2:** please confirm the estimator's SE law.
- Step measured off the callback: BUILD_PLAN AX47, "Measurement".
- M7 limit: phase-07c-2b AC (M7 ≤ 700 ms).
- The pool hold projection: file 13 D3-L3, [Hyp] until M7 is measured.
- Corpus not consulted: no acoustic fact here bears weight.

**6. Conditions of acceptance.**
- **For V1 (rated 2 later), any one of these brings it to 1:**
  - its 08-3 families are run before O4 is pinned; or
  - admission is written as SE ≤ B/1.96, with W_max derived from B as a function, so that a reversal is a parameter change, not code. This applies to every option.
- **For all options:** the record states which family triggered any reversal, and the union rate.

**7. Question (2), `click_check`.**
- **Is the fix needed before the seal? Yes.** A check that passes by coincidence on 50 of 50 stimuli is not a gate. Fixing it is cheap now: a pytest and minutes of work. Fixed after the seal, it could fail a sealed stimulus, which voids the session: about 2 h of a person's time plus a reseal. The same check will also run at 08-3 and on the AX49 L4 ABX.
- **Prefer (b): A − B against the crossfade model.**
  - It is deterministic and does not depend on the median baseline.
  - It does not depend on the sign of g.
  - It reuses what companions (i)–(iii) already assert.
  - Proposed form: in each high-passed frame of the fade, HP(A − B) ≤ HP(E − B) on the same frames, times (1 + tol). A kink introduced by the ramp is exactly what that comparison exposes.
  - The detector still runs on A, B and E, print-only, for the record.
- **(a), per-frame flags against B's threshold: can live with, rated 2 now and 1 later.**
  - An up-step raises A's tail frames past B's threshold on the +3 dB anchors, so it fails builds without any click (both_wall's threshold moved 1.96 dB).
  - Down-steps hide frames instead, so the check is asymmetric.
  - It also keeps clicks.py's noise blind spot.
- **Leaving it unfixed: 2 now and 2 later.** That is not veto-grade, because this is an offline kit.
- **Test spec, required for either form:**
  - It must be shown red on a planted transient: L = 0 (a hard switch at N) and a single-sample impulse in [N, N + L). This follows the "N1 red asserted" precedent.
  - It must be shown green on S-A's 50 stimuli and on the two K5 stimuli.
  - It must be bit-reproducible (CLAUDE.md, Determinism).
  - The tolerance must be set before the seal. both_wall's existing −0.6 dB A − B gap (fade peak against the 100 ms after) is thin.

**8. Hand-offs.**
- Seat 1: the alternative p behind the power figures, and whether split is acceptable.
- Seat 3: the value of `tol`, and whether the kink at the onset of the crossfade ramp is audible.
- Seat 6: load time the user sees under B = 0.5 dB.
- Seat 2 or the researcher: the SE law.

**9. Premortem.** α is left unsplit across V1's 4 families and a chance-level run at 08-3 "detects". AX47 drops to 0.5 dB after W_max is pinned, so stage 1 stops being admissible on capped scenes. The first to notice is the M7 or load-mark CI job, or Seat 6's load-time measurement.

Files read: docs/review/phase-07c-2/31-decider-abx-r4.md, docs/review/phase-07c-2/32-k5-k6-clicks-session.md, docs/BUILD_PLAN.md (AX47, L170), docs/phases/phase-07c-2b.md, docs/review/phase-07c-2/13-decider-rebuttal-r4.md (item 15), tools/ci/abx_kit.py (`click_check` L399–409).
