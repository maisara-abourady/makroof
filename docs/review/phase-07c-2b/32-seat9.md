# 32: Seat 9 on 07e's scope-3/4 sentences (M3-H follow-up)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (M3-H follow-up on file 30 §5 Item A and file 31 Q4; read-only; for `/home/user/makroof/docs/review/phase-07c-2b/32-seat9.md`)

**1. Reading.** Two places where file 30 changes my 29-seat9 conditions:
- In scope 3 (c), "under 0.5 dB" became "uncertainty stated".
- In scope 4, the verdict clause I asked for ("judged against the GA-internal equal level") was replaced by "unexplained by the engine's model", and a prior ruling on coherent radiation near a boundary was added.

Cues from my §4/§6: S8 (the rigid-boundary physics offered as an excuse) and S2 (the s0.7 room is non-diffuse, so Eq. 5.42 is not the reference).

**2. Required texts.**

*Scope 3, (c) bullet (replaces file 30 L216):*
> "For (c): a diffuse control (the same room with its absorption spread over all faces to the same ᾱ in every band) and an independent late-level reference at equal times from the seeded tracer (`tools/acoustics/tracer.py`), every compared bin gated at k ≥ 684 (3σ ≈ 0.5 dB), so the reference's uncertainty is under 0.5 dB; 1.2 dB is about 1 JND of G (Seat 9). Printed: L − R per band for the engine, the control and the tracer. Attribution: a spread that survives in the control is the engine's; one that only the tracer reproduces is the room's; if the tracer's 3σ band overlaps both readings, (c) is 'not decidable' with that stated."

*Scope 4, first bullet (replaces file 30 L220 up to "(Seat 1)"):*
> "It rules, per finding: NFR-8 breached / not breached / not decidable, with the cause. The reference is the GA-internal equal level at equal times: Kuttruff Eq. 5.42 at equal power where the field is diffuse, and the seeded tracer (scope 3) where it is not (Seat 9). Breached: a level spread > 1 dB in any octave band from 125 Hz to 4 kHz at equal times against that reference (Seat 2's test). A spread caused by an engine feature (AX39/AX41/AX44 weight w or capped branch, AX22 fallback, the t_mix,e rule) is a cause of the breach, never an explanation that clears it. The engine is geometric and does not reproduce coherent near-boundary radiation (AX44 'GA limit': GA-true, not room-true). The rigid-boundary column (scope 3) is therefore never a ground for 'not breached'. Whether AX44's GA-limit text should also name the source side (R-H1 §7) is recorded as a separate AX44 amendment after the per-finding verdicts, not before them and not in their place. For (a), the band-wise deficit is printed against the falsifiable claim 'flat within ±1 dB from 125 Hz to 4 kHz → an engine effect' (29-seat9 §5). Audibility is never a ground for 'not breached' under NFR-8 (Seat 1)."

Why: AX44's GA limit (BUILD_PLAN L167) is written for the receiver side and says no accuracy claim is made there; it is not a licence to explain a level away. The decider's "first rules whether the engine is meant to reproduce…" leaves the reference open. If the loop chose "room-true", the rigid column (−3.8 dB at 3 faces, 1 kHz octave; R-H1) would explain away about 60% of (a)'s 6.2 dB. That is the S8 failure.

**3. Ratings with the enlarged 07e** (my cells, now / later).

| Option | Scope 3 (c) and scope 4 | Now | Later |
|---|---|---|---|
| H4+G | my two texts adopted | 0 (confirmed) | 0 (confirmed) |
| H4+G | scope 3 (c) still "uncertainty stated" | 0 | **1** |
| H4+G | scope 4 still "unexplained by the engine's model" | 0 | **2** |
| H3+G | any of the above | same as H4+G | same as H4+G |

- **Why "uncertainty stated" costs 1.** The tracer could report ±1 dB. Then (c) stays unattributed when 12-2 builds non-diffuse presets: one label round.
- **Why "unexplained by the engine's model" costs 2.** A deficit caused by the weight w passes as "not breached". `car_cabin_box` is then built on the unruled corner tail, which is the same debt as H1 (29-seat9 §4).
- **H3+G.** The enlarged scope does not separate the two homes for my seat.

**4. Evidence.**
- Tracer gate k ≥ 684, 3σ ≈ 0.5 dB, σ = 4.34/√k dB: from the code, `tools/acoustics/tracer.py` L28 and L43.
- AX44 GA limit: BUILD_PLAN L167.
- Rigid-face octave averages: R-H1 and file 31 L64 (redone there to −3.6 dB, inside ±0.5 dB).
- Kuttruff §5.6 Eq. 5.42, with its caveat for ᾱ that is not small: file 31 L65.
- JND of G ≈ 1 dB: my register; Seat 1 owns this.

**5. Conditions of acceptance.**
- Later 1 → 0: restore "under 0.5 dB".
- Later 2 → 0: replace "unexplained by the engine's model" with the GA-internal reference and the clause that a model feature is a cause, not an explanation.

**6. Hand-offs.**
- Seat 2 (Lead): whether the 125 Hz–4 kHz band span of the 1 dB test is right (63 Hz and 8 kHz are excluded only for tracer variance [Inf]).
- Seat 2: whether 07e stays size S with the diffuse control.
- Researcher: none new.

**7. Premortem.** If scope 4 keeps "explained by the engine's model", 07e rules (a) "not breached, AX44 weight w", 12-2 places the car speakers at the dash, and Maisara hears the car preset's tail drop when a fix finally lands at 13-2.

Files read (under /home/user/makroof/): docs/review/phase-07c-2b/29-seat9.md, 30-decider-m3h-decision.md L180–289, 31-interrogator-on-file30.md L60–94; tools/acoustics/tracer.py (grep L28–44, L244); docs/BUILD_PLAN.md L167 (AX44).
