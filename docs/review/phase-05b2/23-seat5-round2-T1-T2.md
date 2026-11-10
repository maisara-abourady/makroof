# Seat 5 — second round, D-T1.3, D-T1.6 and D-T2

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

SEAT 5 POSITION: second round on D-T1.6 (NW-4C, NW-3 re-rated), D-T1.3 (N-3W*), D-T2 (L2-F1R) and my T1-F† cell

Corpus present (c1b171f). None of the claims below is acoustic; they are clock and cost claims, sourced from C12 (`22-orchestrator-C12.md`), 19 §1/§4/§6, BUILD_PLAN §0 row 07 and dossier F19. Prototype ns per evaluation is a proxy for C++ [Inferred, O15]. I answer only what changed since `18-seat5-T1-T2-T6.md`.

**1. Reading**

This round brings four new inputs: a composed near-wall estimator, a measured clamp bias, the cap and pilot arithmetic, and a shipped-SE rule at about 20× cost.

My cues:
- §10.2: worst case first. The gated 100 m scenes and the case where both ends sit near a wall.
- §4.1: unbounded work on the host's synchronous restore thread.
- S5 / AX5: any value that decides which paths run must be identical on every platform.

**First, a correction: C12's W_max is not quite what I meant.** The structure is mine: a deterministic count of image evaluations, sized so that two emitters fit in the restore bound minus the existing build at the gated scene, taking the tightest OS. C12's Linux figure of 1.88 s is the tightest (row 07: Linux 1 883.7, macOS 1 832.1, Windows 1 509.1 ms at 96 kHz). Four of C12's inputs differ from what I meant:
- **Thread count.** I said "the pool", which is hardware_concurrency − 2 threads on the CI runner. C12 used 4 threads on a 4-core box, a pool that box would never get: it would get 2. On GitHub standard runners the pool is 1–2 threads [Hyp: runner core counts not read from our CI].
- **Cost per evaluation.** The cost must be the worst over the gated set. The flutter cube costs 10.6 / 42.5 ns at 4 / 1 threads, against the 9.02 ns used (C12 (d)). At 14.6 M evaluations and 10.6 ns, the restore is 1.884 + 2 × 0.155 = 2.19 s, above the 2.14 s bound.
- **Machine.** The solve cost and the build time must come from the same machine, which is the CI runner. Row 07's build times are best of 3, which makes the bound optimistic.
- **A fixed constant.** W_max must be a constant, identical on all platforms and never scaled by the user's core count. Otherwise the cap point, and so the estimate, differs between machines (AX5).

Re-derived on Linux, with 0.1296 s per emitter [Inferred]:
- **1 thread:** 0.1296 s / 42.5 ns ≈ **3.05 M**.
- **2 threads:** ≈ 5.9 M, assuming about 1.95× scaling (C12's 4-thread scaling was 3.8–4.0×).

**2–4. Ratings (now / later)**

**(a) NW-4C: prefer, 1/1.**
- **Now 1:** at the gated cube100 e1, NW-4C costs 2.57× forward-only's evaluations, with a median of 1.02× (C12 (c)). That is an upper bound, because the shipping design shares the listener-started set between emitters.
- **What I gain:** this is the largest gain on my clock this round. In my first round, a listener near a wall needed about 2 s per emitter in W1 at the edge and about 80 s per restore in layout 4 (18-seat5). Under NW-4C, every one-end case runs at the reference-position SE (0.013–0.016 dB in W1, 0.068–0.114 dB in layouts 4 and 5 at 32 k), and the cap was hit in 0 of 17 cases (C12 (a), (d)).
- **What it costs my seat:** w uses only +, ×, ÷ and d, so it is deterministic. The work stays bounded by the cap. It needs no clamp and no second reference.
- **Later 1:** two RNG streams to keep under D5. The worst case moves to "both ends near a wall" (VOV up to 0.95, 364 k–377 k histories needed), which the cap bounds and flags.

**(b) NW-3: drops from prefer to can live with; 0/1 → 0/2.**
- **Now 0:** unchanged. The min/max clamp gives the same result on every platform and costs least.
- **Later 2:** at +0.322 dB (layout 5 absorbing wall, 19 §6), the clamp moves E_target by more than τ, and the shipped estimator becomes a different model from the gate's reference. That leaves my CI two outcomes, both bad:
  - a clamp-specific reference golden, regenerated whenever either model changes; or
  - absorbing-face scenes left out of every gate. The gate is then green while users' scenes are off (my §17: a clean CI with a failing beta).
- **Undo cost:** a model change plus a golden round. Evidence arrives only from user scenes.
- Whether the bias is audible or acceptable belongs to Seats 1, 2 and 9.

**(c) N-3W\* as composed: can live with, 2/2. With the conditions below: prefer, 1/1.**

- **Conflict 1, the pilot exceeds W_max.**
  - At C12's W_max the pilot is 2.7–3.1× over (W2 and the flutter cube). At the 1-thread W_max it is ≈ 13× over in the flutter cube (39.3 M evaluations) and ≈ 2.2× over even in the non-fallback cube100 (6.7 M).
  - As composed, the "cap" is either broken by its own pilot on the host's restore thread or yields no estimate.
  - I need **the pilot defined in work: n\* = min(8 000, the histories whose evaluations fit in W_max/2).** In the flutter cube that is still ≈ 310 histories at 1 thread, against a Tol-2 need of 1–16.
- **Conflict 2, the final range is smaller than the pilot.**
  - The cost of discarding the pilot is at most 2× and fits in W_max in all 17 cases (C12 (d)), so it is tolerable on my clock.
  - I need **N_final ≥ the effective pilot size, then capped by the remaining work.** Pilot ≤ W_max/2 guarantees room for it.
  - Whether the final SE may sit above 0.083 dB (6 of 17 cases) belongs to Seat 1.
- **New determinism point (D7).**
  - N decides which paths run. It is computed from the pilot SE, and the pilot's scores use libm.
  - F19 says glibc's run-time dispatch can change libm results across x86-64 hardware with the same binary.
  - So I need:
    - N computed with no libm (squared ratios of relative SE against a constant, then ceil);
    - N rounded up to whole D4 blocks;
    - per-case N recorded in the D5 golden beside the face hash.
  - A residual ulp flip at a block boundary is very improbable [Inferred]. It would show as a golden mismatch, not silently.
- **Consequence for the other seats.** Even with these conditions, the 1-thread W_max puts cube100 at its reference positions over the cap at Tol-2. The final SE would be ≈ 0.083·√(6063/1840) ≈ 0.15 dB [Inferred; upper bound because the listener set is not shared]. That is still inside Seat 1's 0.33 dB floor, and it is flagged.

**(d) L2-F1R: cannot live with, 2/3.** It has the same structure as L2-F2, which I vetoed.
- **The bound at 100 m:**
  - at C12's 4-thread figures, a restore takes ≈ 3.7 s; 14 × 3.7 ≈ 52 s against pluginval's 30 s;
  - at 1 thread, 98 M evaluations × 34 ns ≈ 3.3 s per emitter, so a restore of ≈ 8.6 s and 14× ≈ 120 s;
  - layout 4 at s = 1 takes ≈ 30 s per emitter (decider, 21).
- **Later 3:** under any cap that protects restore, the "certified" SE is false exactly where the work is expensive. The only real fix is to take the diffuse solve out of the synchronous restore and prepare, which is roughly a phase of Phase 07 rework.

**(e) T1-F†: confirmed at 1/1, on one condition.**
- The decider read it correctly from D1–D6. D1's key already carries "start end", which NW-4C needs.
- The condition is D7 above, plus W_max as a cross-platform constant. Without D7 the cell stays at 1/2, because F19's dispatch finding is now sourced.

**5. Evidence**
- C12 (a)–(d): costs, pilot/W_max ratios, cap hits, L2-F1R coupling.
- BUILD_PLAN §0 row 07: restore times per OS at 96 kHz, best of 3.
- 19 §6: +0.109 dB and +0.322 dB.
- F19 (14-researcher): libm differences and run-time dispatch.
- My arithmetic above is [Inferred], and the runner core counts are [Hyp].

**6. Conditions of acceptance**
- **N-3W\*, 2/2 → 1/1:** pilot ≤ W_max/2 in work; N_final ≥ pilot; W_max re-derived from the C++ cost at the CI runner's pool size, with the worst cost over the gated set (the flutter cube) and the worst-case build time; W_max a fixed constant; D7.
- **NW-3, later 2 → 1:** a clamp radius whose bias is measured below τ/2 in layouts 4 and 5, so that no second reference is needed.
- **L2-F1R, 2/3 → 2/2:** async restore, so the diffuse solve runs off the synchronous host calls. → 0/1 if Maisara takes the bias reading, which puts the high-N test in Release CI only.
- **NW-4C stays at 1/1 if:** one listener-started set is shared between emitters; both sets run in the same D4 blocks, so `quiesce()` still waits at most one batch; D5 hashes both sets; and the W1 both_corner case at 0.1 m replaces my first-round layout-4 corner case as the benchmark that asserts the cap flag.

**7. Hand-offs**
- **Orchestrator:** `nproc` on each CI runner; the C++ cost per evaluation; W_max re-derived with it; restore times for the layout-4-sized room.
- **Seats 1 and 2:** the minimum pilot size for a trustworthy SE; whether a final SE above target is acceptable; whether to keep the slope flag (it fires at 2.93 in W1).
- **Seats 1, 6 and 7:** cap hits at the 100 m reference positions under the corrected W_max, and their wording.
- **Maisara:** Challenge 1, and how AX36 applies to an estimator.

**8. Premortem**

W_max ships derived at 4 threads and the gated scene's lower cost. On a 4-core laptop (pool of 2), restoring a 100 m flutter-cube session takes over 2.14 s per instance, so 14 instances exceed the 30 s watchdog. CI's pluginval notices first if Challenge 1 is a gate; otherwise a beta tester does.

Files: /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md, /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/19-orchestrator-NW4-and-checks.md, /home/user/makroof/docs/review/phase-05b2/18-seat5-T1-T2-T6.md, /home/user/makroof/docs/review/phase-05b2/14-researcher-T1-T2.md, /home/user/makroof/docs/BUILD_PLAN.md
