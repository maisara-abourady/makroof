# 29-seat2: Seat 2 on M3-H (brief B2)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION (follow-up to 22-seat2, brief B2 of file 28; read-only. The orchestrator saves it as /home/user/makroof/docs/review/phase-07c-2b/29-seat2.md)

**1. Reading.** The brief asks four things. First, rate H2-cg, H3+G and H4+G. Second, answer Seat 5's K7 question: would a likely fix change restore work, or only the level? Third, rate G2's re-pin clause. Fourth, confirm the 07e skeleton's scope 1–3 texts or amend them. Cues from my §4: 4 (path geometry: a source or listener 0.1 m from faces), 5 (which parameter deviates), 7 (does the cost land once or twice). Situations from §6: S4 and S6 (non-circular).

**2. Ranking.** My 22-seat2 cells stand: H1 0/2, H2-c 1/2, H3 1/1, H4 1/1.
- **H4+G: prefer.**
- **H4: can live with.**
- **H2-cg: can live with.**
- **H3+G: can live with.**
- **H3: can live with.**
- **H2-c (no 08-3 gate): can live with, at a major later cost.**
- **H1: can live with, at a major later cost. Ranked last.**

**3. Tension now**
- H4+G: **1.** One S session, no change in output.
- H3+G: **1.** Same work as H4+G. Holding back 08-1 and 08-2 buys my seat nothing.
- H2-cg: **1.** Same work, but it sits in a phase with no Lead whose subject is Seat 5's.

**4. Tension later**
- **H4+G: 1.** If a fix is ruled, it costs one golden round and M3-8's rebuild of the two sealed scenes, once and before the freeze. Under every pre-freeze home that is the fix's cost, not the home's (my 22-seat2 consistency rule).
  - G1 moves the gate into *Depends on*, and G2 orders the fix against the re-pin. Together they remove the pressure to defer a fix to avoid a second re-pin.
  - Undoing it means deleting the 07e file.
  - The evidence arrives with 07e's ruling.
- **H3+G: 1.** Same debt as H4+G.
- **H2-cg: 1.**
  - Same debt, plus a residual cost [Inferred]. Under CLAUDE.md ("Open a PR only when the work is finished"), a ruling committed on 07d's branch reaches `main` only when 07d merges. So the "committed artifact" gate in practice becomes "07d merged". That holds the ruling behind 07d's macOS loop and load loop (scope 7: up to 3 extra runs; scope 8: a possible return to 07d's board loop).
  - It is not rated 2, because the ruling still precedes both gated items. It is why I prefer H4+G.
- **G2's clause, "a fix landing after a re-pin carries the re-pin in its own acceptance criteria" (07e scope 5): 1.**
  - It is a backstop. G2's first sentence already holds scope 8 until 07e and its fix phase are `done`.
  - My residual cost: it ties an acoustic fix's `done` to hosted-runner timing.
  - Recommended wording, not a condition: "a growth red after the fix goes to 07d's FM-GROWTH board loop; it never trims or reverts the acoustic fix (NFR-8 L112, L49)".

**K7, Seat 5's hand-off: neither likely fix is level-only by construction, so G2's re-pin debt does not fall to 0 in advance.**
- **The AX40 seed constant is not a credible fix.**
  - AX40 only fixes the estimator's seed key (DiffuseEstimator.h L42).
  - A change of seed moves E_target by about the SE target of 0.083 dB, or U 0.33 dB in the capped branch (L51, L57). That is far below the 6.2 dB finding [Observed, code; Inferred].
- **An AX22 fix (the realised-k test at a near-face source) changes restore work by design.**
  - It flips the fallback, which changes the image count (up to N_cap 1 560), the handover and the matching (Engine.cpp L142–156).
  - It also changes the estimator's window and its image evaluations: W is counted in image evaluations, and the gathering window ends at t_mix,e (DiffuseEstimator.h L10–19, L74).
  - The AX38 4c gate set contains `cube100_flutter_fallback` (test_diffuse_bench.cpp L122), so the test is exercised on a gate scene [Observed, code].
- **An estimator fix that changes only how histories are scored is level-only.** An example is the AX44 fwd/rev weight w = d_L²/(d_L² + d_E²) (header L17–19). The path decisions and W stay the same and only E_target moves [Inferred]. Even so, it bumps kEstimatorModelId (L52–55), which affects keyed restores (Seat 5's ground).
- **This is cheap to settle empirically.** The fix phase prints the restore-work counters on the AX38 4c gate scenes before and after the fix: images per emitter, handover time, W_pilot, n\*, N, W. If they are equal, the fix is level-only on the gate set. Whether equal counters allow pooling under scope 8 ("unchanged restore path") is Seat 5's ruling.

**Skeleton (file 17 §3, Scope 1–3): confirmed, with these amendments**
- **Scope 1(a), add:**
  > "listener at (0.1, 0.1, 0.1) m, 0.1 m from two walls and the α 1 floor; emitter L at (19.9, 29.9, 9.9) m; both within AX44's 0.70 m (both-near branch)"

  Source: from the code, abx_kit.py L143, and DiffuseEstimator.h L56.
- **Scope 1(b), add:**
  > "listener 0.1 m from the y = 0 wall, L 0.1 m from the y = 30 wall"

  Source: abx_kit.py L142.
- **Scope 2(a): replace "the AX40 estimator" with:**
  > "the diffuse estimator (AX39/AX41/AX44: the both-near weight w and the capped branch; AX40 fixes only its seed, whose effect is bounded near 0.083–0.33 dB)"

  Also demote "the t_mix,e rule" for (a). L's and R's onsets are 0.376 and 0.379 s (file 5 L22), so the rule cannot produce a 6 dB spread.
- **Scope 2(b), add the mechanism [Inferred from AX22's formula, not measured]:**
  > "near-coincident image pairs (about 0.58 ms apart) off a face 0.1 m away enter k_real = S²/Q as separate entries, roughly doubling k_real per such face: ×4 for L (two faces) against ×2 for R (one), so L can pass the k ≥ 19 test where R falls back"

  Measure it in Python from `--images`: k_real with entries merged within 1 ms (print only).
- **Scope 3, add:**
  - distances of 0.65 and 0.75 m, to straddle the 0.70 m branch;
  - each placement with the listener near and with it far, to separate emitter-side from listener-side effects;
  - corners with and without the α 1 face;
  - per emitter: the both-near and capped flags, w, n\*, N and W;
  - the restore-work counters on the gate scenes (for K7);
  - R2's AX5 wording in the pytest.

**5. Evidence.**
- Code citations as given above [Observed, code].
- The near-boundary power gain at 1 kHz with a = 0.1 m: kd ≈ 1.83, so the gain is far below the low-frequency corner limit [Hyp; R-H1 to the researcher].
- Corpus not re-opened. The 1 dB jnd of G is as cited in 14-seat2.

**6. Conditions.** None needed: no cell of mine is at 2 except H2-c and H1, whose conditions are unchanged.

**7. Hand-offs.**
- Seat 5: whether equal restore-work counters let scope 8 pool runs; the kEstimatorModelId and keyed-restore effect; whether H2-cg's artifact gate needs a separate merge to reach `main`.
- Seat 1: whether a level shift from a fix to the AX44 weight is audible.
- Researcher: R-H1.

**8. Premortem.** Suppose H2-cg is chosen and the ruling waits on 07d's merge behind macOS runner flutter. Then 08-3 item 15 stalls, and the orchestrator notices first, when the gate never clears.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md, 22-seat2.md, 14-seat2.md, 22-seat5.md, 14-seat7.md, 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 5-builder-tail-spread.md (L1–40)
- /home/user/makroof/docs/phases/phase-07d.md (L1–110), phase-08-3.md (L58–87), phase-08-4.md (L20–27)
- /home/user/makroof/docs/BUILD_PLAN.md (AX22 L145, AX40 L163)
- /home/user/makroof/src/sim/Engine.cpp (L90–209), /home/user/makroof/src/sim/diffuse/DiffuseEstimator.h (L1–130)
- /home/user/makroof/tools/ci/abx_kit.py (L138–168, via search), /home/user/makroof/tests/unit/test_diffuse_bench.cpp (L122, via search)

PRD lines were not re-read: they are cited as digested in file 28.
