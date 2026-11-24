# 29-seat3: Seat 3 on M3-H (brief B3)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION (M3-H re-run, brief B3; for docs/review/phase-07c-2b/29-seat3.md. Read-only; the orchestrator saves it.)

**1. Reading.** Where and when the cause of the three NFR-8 placement findings is ruled. My question is whether a fix ruled by 07e that moves t_mix,e or the AX22 handover touches a rendering commitment. It does, in three places, and all three are cheap to protect. Cues: §4 "state discontinuity" (the AX22 switch point and the ISM→tail crossfade inside the IR) and "cost" (the provisional's synthesis length). It is not NOT MY MATTER, because of the code fact below. But the home choice separates my row only on H1.

**2. Ranking**
- **Prefer: H4+G and H2-cg.** They tie on my row.
- **Can live with: H4, H3+G, H3, H2-c.** On my measures they equal the two above.
- **Can live with, at a major later cost: H1.**
- None is veto-grade.

**3. Tension now.** Every option is 0. Each is report-only. None changes a crossfade, a coloration check, the AX49 provisional or the convolution cost at the time of decision.

**4. Tension later**
- **What a fix touches (from the code).**
  - `planEmitter` overwrites `plan.mixing.mixS` with t_cap,e when the AX22 test fails (Engine.cpp L147–149). L_f is computed from that same `mixS`: `t.mixMaxS = max(…, pe.mixing.mixS)` and `fadeStartS = mixMaxS + 0.312·T60_max` (Engine.cpp L645–647).
  - So a fix to the t_mix,e rule or to AX22 moves four rendering commitments:
    - (i) AX49's L_f and L_p. AX49's reversal trigger is L_p ≤ 3.82 s at the gated geometry, and L_p ≈ 3.7 s there, so the margin is about 0.1 s.
    - (ii) Where the ISM→tail crossfade inside the IR sits (the AX21 step and dip at t_mix,e).
    - (iii) Where the AX22 jump points fall in source position. Phase 10 gates the AQ4 crossfade dip across them at ≤ 1 dB (AX22 row).
    - (iv) The ax49_l4_cube IR sealed for L4.
  - Per-instance convolution cost does not move: partitioned convolution cost grows with IR length × channels, and the handover does not change IR length. The provisional's synthesis cost (≤ 334 ms per emitter at 96 kHz, AX49 K22) grows with L_f [Inferred].
- **Ratings, later:**
  - **H2-c, H2-cg, H3, H3+G, H4, H4+G: 1.**
    - Any fix lands before 08-4 and before Phase 10. So (iii) and the 08-3 per-ear provisional asserts are simply re-run, once.
    - The residue is AX49 record (h): 07d scope 6 brings the 8-instance load to ≤ 5 s on record (h). None of these options orders a fix against scope 6. G2 orders scope 8 only. A fix that moves L_f at the rated corner after scope 6 closes leaves record (h) stale.
    - Undo: a re-print of record (h) and a re-run of AX49's acceptance. A parameter-scale cost, not a phase.
    - Evidence: 07e's sweep, if it prints L_f (condition C3-a).
  - **H1: 2.**
    - Phase 10's AX22 dip gate and 10-1's tail cache (keyed on per-emitter handover state, 14-seat2 §4) would be built on the pre-fix switch points and re-run after 13-2.
    - AX49's acceptance, record (h) and the L4 record would all predate the change.
    - That is roughly one phase of re-measurement on my row. The evidence arrives only at 13-2.
    - One offset, stated so it is not hidden: Phase 13 already re-derives N_cap ("cap limits accuracy", AX22). That moves t_cap and the handover after the freeze in any case. It does not move the realised-k switch points, which is the part Phase 10 gates.

**5. Evidence**
- L_f is taken from the post-fallback handover: from the code, Engine.cpp L142–157 and L645–647.
- AX49's L_p ≈ 3.7 s against 3.82 s, and the 334 ms per emitter: BUILD_PLAN AX49, K15′/K22.
- Phase 10's ≤ 1 dB dip gate at the AX22 switch: BUILD_PLAN AX22.
- Convolution cost scales with IR length × channels: persona §5, [Observed, general].
- Whether a likely fix changes the handover at the 100 m gated geometry, where the emitters are far from faces: [Hyp]. To Seat 2.
- The corpus was not re-opened. This position rests on no new acoustic number.

**6. Conditions of acceptance**
- **C3-a: takes every pre-freeze option from 0/1 to 0/0. It also attaches to H1.**
  - In 07e scope 3, add: "per placement and emitter, print the handover time (after any AX22 fallback) and the AX21 step and dip at it, per band. Print L_f and L_p at the AX49 gated geometry and on ax49_l4_cube."
  - In scope 5, add: "a fix that moves any of these carries in its own acceptance criteria: AX49's acceptance re-asserted; L_p at the gated geometry printed against 3.82 s; record (h) re-printed at the rated corner if L_f moved there; and the M3-8 rebuild, which names the L4 stimuli if ax49_l4_cube's IR changes."
- **H1, from 2 to 1:** Seat 7's deferral clause, with the cause ruled before 08-4 and before Phase 10's AX22 dip gate is built.

**7. Hand-offs**
- **Seat 5:** whether record (h) and 07d scope 6 need ordering against a fix, as G2 orders scope 8. Its timing is yours.
- **Seat 2:** whether a likely fix (the AX40 constant, or the realised-k test) changes the handover at the 100 m gated geometry. If it does not, C3-a's L_f clause is a print only.
- **Seat 1:** whether M3-8's "void until rebuilt" covers the L4 record.
- **Seat 4:** the mode-switch interim asserted in 08-3 (07d scope 6) re-runs on any fix. That is automatic, and I make no claim on it.

**8. Premortem.** The item is homed without C3-a. A fix moves L_f at the rated corner after 07d closes scope 6, and the 8-instance load quietly goes back over 5 s with record (h) still green on paper. The contracted engineer would notice first, comparing the fix commit's date with the record (h) runs.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md (L1–40)
- /home/user/makroof/docs/review/phase-07c-2b/17-decider-m3-r4.md
- /home/user/makroof/docs/review/phase-07c-2b/20-interrogator-on-file17.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md
- /home/user/makroof/docs/phases/phase-07d.md (L70–105), phase-08-3.md (L1–90), phase-08-4.md (L18–29)
- /home/user/makroof/docs/BUILD_PLAN.md (AQ4 L112, AX6 L129, AX22 L145, AX49 L172)
- /home/user/makroof/src/sim/Engine.cpp (L125–164); grep of Engine.cpp L645–647 and Engine.h L147–159

Not read: PRD L49–L174 directly (the digest is taken from file 28); BUILD_PLAN §0 rows 07d, 08-3, 08-4 and 12-2.
