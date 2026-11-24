# 32: Seat 2 on 07e's size and the scope-4 breach sentence (M3-H follow-up)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION (follow-up on M3-H, file 30 Item A and file 31 Q1/Q4; for saving as /home/user/makroof/docs/review/phase-07c-2b/32-seat2.md; I changed no files)

**1. Reading.** Three things: whether 07e is still size S with the added prints, the exact breach sentence for scope 4, and my H4+G and H3+G cells re-rated. Cues from my §4: 5 (which parameter deviates) and 6 (a claim of accuracy). Situation S6: the test must not be circular.

**2. Q1: is 07e still size S? No, not as one session.**
- **Cheaper than it looks.** Every counter in scope 3 is already printed by `--diagnostics` (from the code, `src/cli/Cli.cpp` L597–654: ismFallback, capTimeS, handoverS, expectedMixS, nStar, n, nCap, capHit, weight, bothNear, wPilot, wFinal, wScene, targetEnergyAx16). k_real with merging is Python over `--images`. So the measurement needs no `src/sim` or CLI edit.
- **Where the size goes.** About 42 sweep placements (7 distances × 3 face counts × listener near and far), plus the α 1 corner variants and the medium_room cases, each rendered for both emitters. Then the cross-platform pytest (AC1), the report, and a nine-seat board loop with the interrogator for three findings, possibly ending in a fix-phase file.
- **The tracer reference (Seat 9) is a separate run.** It is cheap only for (c). layout4 is about 6,000 m³, so N0 = ceil(254 V) is about 1.5 M particles, and up to 16× that with doublings (`tracer.py` L44–45). That is a one-off print, not a CI test. AC1's "every scope 3 print for every placement" must exclude the tracer, or the CI job becomes infeasible.
- **The tracer cannot sit at the near-face listeners.** Its receiver is a 0.5 m sphere (`tracer.py` L21, L42). It is valid only where the receiver is at least 0.5 m from every face. It is not valid as a reference for (a)'s listener at (0.1, 0.1, 0.1) m.
- **My estimate: two S sessions [Hyp].** Seat 7 owns the session cost.
- **The split I expect, named now:**
  - 07e: scopes 1–3, AC1 and the report.
  - 07e-b: scopes 4–5 and the Definition of done (the ruling, plus any fix-phase file).
- **The split creates debt unless the gates move with it.** Every gate (08-4's Depends on, item 15, 07d scope 8, Item B's §0 row) must read "07e-b `done`". Otherwise a measurement-only 07e opens them before any ruling exists.

**3. Q2: the scope-4 sentence I require.**
> "It rules, per finding and per octave band in which the reference's uncertainty is under 0.5 dB: NFR-8 breached / not breached / not decidable, with the cause. The reference is the GA-internal equal level: the late level that the engine's own geometrical model predicts at equal times for each emitter at the scene's source power (Kuttruff Eq. 5.42 where the field is diffuse; the seeded tracer, uncertainty under 0.5 dB, receiver clear of every face, where it is not). Breached: a spread > 1 dB from that reference. Not breached: every band within 1 dB. Not decidable: no such reference can be formed. A spread produced by a feature of the engine (the AX44 weight w, the AX39/AX41 capped branch, the AX22 fallback, the t_mix,e rule, a cap) is its cause, never its explanation."

**4. How the "first rules" clause sits beside it.** It stays, and it comes before the verdicts, reworded:
> "Before the verdicts it records whether the engine is meant to reproduce coherent near-boundary source radiation (R-H1). AX44's 'GA limit' covers the receiver side only. As built, the late level follows an energy target (E_target), so the answer is no: the reference above holds, and R-H1's rigid-boundary column cannot reduce a spread. Changing that answer is a separate board decision with a new AX checked against the corpus. It applies at the source to the direct, early and late parts alike. Under it, a spread counts as explained only where it matches that model's per-band prediction within 1 dB and arises from that mechanism."
- **Why a tail-only deficit cannot be source power.** A real change in source power would lower the direct and early parts too [Inferred, R-H1 §3].
- **(a) fails that test anyway.** It shows −6.2 dB against −1.6 to −3.8 dB octave estimates, with a mismatched frequency dependence (29-seat9 §5).

**5. Q3: my cells.**

| Option | Now | Later | Change |
|---|---|---|---|
| H4+G | 1 | 1 | confirmed |
| H3+G | 1 | 1 | confirmed |

- **Why the enlarged 07e does not raise them.** The added prints are the non-circular validation my §2 never trades away. Two sessions stay inside my tolerance.
- **The one new later item.** The sweep JSON becomes a golden. A ruled fix re-pins it inside the golden round that is already counted, so the debt stays at 1.
- **Condition for both cells.** They hold only if the gates name 07e-b (section 2). If they do not, my later cell under H4+G goes to 2: the gated items could open with no ruling.
- **H3+G.** The longer 07e lengthens its hold on 08-1 and 08-2. That cost is Seat 7's, not mine.

**6. Evidence.**
- Diagnostics fields: from the code, `src/cli/Cli.cpp` L597–654.
- Tracer N0, gate and receiver sphere: from the code, `tools/acoustics/tracer.py` L21–28, L42–45.
- Kuttruff Eq. 5.42 (equal level at equal power): corpus, as checked in file 31.
- AX44 is receiver-side only: BUILD_PLAN L167, as cited in file 31.
- The session estimate is [Hyp].

**7. Hand-offs.**
- Seat 7: session cost of 07e plus 07e-b.
- Seat 5: AC1's exclusion of the tracer from CI.
- Seat 9: confirm the tracer is used only where the receiver is clear of every face.

**8. Premortem.** If "unexplained by the engine's model" stands, the w-weighted deficit in (a) is ruled "not breached" by its own cause. The first to notice is a producer whose corner source goes dry, after 08-4 has frozen.
