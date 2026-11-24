# 29-seat1: Seat 1 on M3-H (brief B1)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (brief B1, M3-H re-run; read-only; for saving as /home/user/makroof/docs/review/phase-07c-2b/29-seat1.md)

Corpus is present (c1b171f). Persona assumption that no longer holds: the PRD puts head tracking out of scope (L134), so my latency rows (T1) play no part here.

**1. Reading.** The question is where and when the cause of findings (a), (b) and (c) is ruled, measured against whether my acceptance test (08-3 item 15, F3/F4) is built and listened to before the cause is known. Cues it triggers:
- §4 "orientation cue": (a) moves an emitter's direct-to-reverberant balance, which is a distance cue.
- §4 "temporal smoothness": a drag into a corner turns (a) into a transition the user hears.
- S4 (every threshold carries its method) and criterion 1 (a null states the minimum effect it reached).

**2. Ranking**
- **H4+G: prefer.**
- **H4: prefer.** For my seat it is equal to H4+G, because G1–G3 are Seat 5's ground.
- **H2-cg: prefer, tied.** It gates item 15's stimulus build on a committed ruling, which is all my seat needs.
- **H3+G and H3: can live with.** Holding 08-1 and 08-2 costs my seat nothing.
- **H2-c: can live with, at a major later cost.**
- **H1: can live with, at a major later cost. Ranked last.**

**3. Tension now.** **0 for all seven options.** My seat spends nothing now under any home. The investigation is a session of Seat 2's.

**4. Tension later**
- **H4, H4+G, H2-cg, H3, H3+G: 1.** F3/F4 are built after the cause is known. The residual is the same under every home: a ruled fix fires M3-8, so the 07c-2b F1/F2 nulls become void for their scene and the cross-chain comparison needs an omni rerun. That is the fix's cost, not the home's. Undoing any of these means deleting one file. The evidence arrives with the ruling.
- **H2-c: 2.** 08-3 does not depend on 07d (phase-08-3 L3), so F3/F4 can be sealed and heard before the cause is ruled. If a fix then lands:
  - **The nulls are void.** The "void as evidence … until rebuilt (M3-8)" clause makes those F3/F4 nulls void. That loses 2.6–5.0 h of blind evidence (phase-08-3 L81–82).
  - **The minimum effect moves.** If (b)'s onset moves, S-W's heard step falls from +0.62 to about +0.28 dB ΔG at 0.9 dB (14-seat1 §2). A pre-fix result then tests a different minimum effect than the product has.
  - **A detection becomes ambiguous.** A pre-fix detection reverses AX47 for the recorded engine, but it does not clearly carry over to the fixed one.
  - **Strictness inflates.** Rerunning F3/F4 adds families. The union rate rises from ≤ 0.0906 to up to 6 × 0.0227 = 0.136 unless the rerun is pre-registered as a replacement. That breaks my criterion 1, stated strictness.
  - **When the evidence would arrive:** at 07d's ruling, which may come after the listening.
- **H1: 2.** Everything in H2-c applies, plus two more things:
  - **Preset tuning by ear.** Phase 12's preset listening is done on a corner tail that may be wrong. A preset author who hears a dry corner source and moves it out of the corner is tuning around an engine fault at the preset layer. That fault is the kind of finding NFR-8 exists to catch, and the tuning hides it.
  - **Late evidence.** The evidence that could overturn H1 arrives only at 13-2. Undoing it costs re-listening plus a golden round (Seats 2 and 7 estimate up to about one phase).
- It is not 3: no option makes a realism claim, and the void clause stops a void null from being cited.

**Audibility of (a) and (b): does it change any cell?**
- **(a) Audibility does not change where the cause is ruled.** NFR-8 binds whether or not the fault is audible.
- **How large (a) is at the ear [Inferred, my arithmetic].** A 6.2 dB deficit in the tail alone gives the emitter a heard change of ΔG = 10·log₁₀(1 − s·0.760), where s is the emitter's tail share at 1 kHz:
  - s = 0.29: −1.1 dB
  - s = 0.667: −3.1 dB
  - s = 0.9: −5.0 dB
- **Against the level JND.** The level JND is about 1 dB, over 500–1000 Hz (Vorländer Table 6.1, after ISO 3382-1). That figure comes from static listening in halls, so I give it medium confidence (S4). On that basis (a) is likely 1–3 JNDs, in the direction "the corner source sounds closer and drier".
- **Why the direction matters.** Direct-to-reflected level is a distance cue (Blauert ch. 3, distance paragraph, corpus L336). Seat 2's [Hyp], for the researcher (R-H1), is that a real boundary source radiates more power, not less. If that holds, (a) inverts the cue a producer expects.
- **The effect on cells:**
  - If (a) is audible, my H1 later 2 holds, and it is the preset-tuning cost above that makes it so.
  - If trained listeners cannot detect it, my H1 later falls to 1 (asymmetry rule, O2 lead). The other seats' H1 cells do not move.
  - No other cell changes.
- **(b) is late-field texture (§4).** In [0.165, 0.380) s, L's window holds diffuse tail where R's holds image-source energy, and the levels at equal times agree within 0.05 dB (file 5 L21). Audibility is probably low [Hyp]. Its cost to my seat is the heard-step shift above, which the void clause already covers.
- **The test that would settle (a)** belongs in 07e's loop (or the H2-cg ruling), and only if that loop considers deferring a ruled fix:
  - **Design:** self-ABX, 24 trials, ≥ 18/24.
  - **Stimuli:** A is both_corner as rendered. B is the same scene with emitter L's tail-only IR raised per band to R's level in the equal windows. The kit assembles B from per-emitter IRs; there is no `src/sim` change.
  - **Signals:** McGill male speech and pink-noise pulses, plus one dense mix as a control.
  - **Chain:** omni diotic, and binaural once 08-3 exists.
  - **Limit:** a null from this test is detection by one listener only. It never establishes that producers would accept the render as plausible.

**5. Evidence**
- The finding values and the void clause: file 5 L21–22; phase-08-3 L62–69 [plan].
- The 0.62, 0.34 and 0.28 dB heard steps: 14-seat1, redone in file 20.
- G JND 1 dB: Vorländer Table 6.1 (corpus L2060).
- Reverberant level does not depend on position: Kuttruff Eq. 5.42 (indicative, §5.6).
- My register entries are **leads, not facts**:
  - O1: sighted judgement.
  - O2: trained versus naive listeners.
  - R3: a cue that was cut is found by the people who hand-tune.
  - T1: per-listener results.
  - B2: the hardest signal.
- **Researcher:** R-H1, the direction of boundary power at 1 kHz.
- **Builder or Seat 2:** emitter L's tail share at both_corner. File 5 does not print it.

**6. Conditions of acceptance**
- **H2-c, 2 → 1:** gate item 15's stimulus build on the committed ruling. That makes it H2-cg. If F3/F4 are ever rerun after a void, the rerun is pre-registered as a replacement family with its own α, and nothing is pooled.
- **H1, 2 → 1:** apply Seat 7's deferral clause, so the cause is ruled before item 15's stimuli and before 12-2.
- **Every gated option, to keep it at 1:** the ruling text says "audibility is never a ground for 'not breached' under NFR-8". The 07e sweep prints the equal-window deficit at each sweep distance, so a jump of more than 1 dB between neighbouring distances shows up as a cue the user hears while dragging a source.

**7. Hand-offs**
- **Seat 2:** the deficit against distance; L's share at both_corner; whether (a) is broadband.
- **Seat 9 and the researcher:** R-H1's direction.
- **Seat 6:** whether a drag lands at exactly 0.1 m. If so, (a) is a state the user can reach and hear as a transition.
- **Seat 4:** whether item 7's both-near render waits.
- **Seat 7:** the hours of any rerun.
- **Seat 5:** G1–G3.
- **Maisara:** the listening itself.

**8. Premortem.** Suppose H2-c ships without the gate, F3/F4 are heard, and then 07d rules an AX22 fix. The nulls become void, the rerun's union rate goes unstated, and a pre-fix null is cited at AX47. The first to notice is the interrogator, or the ΔG print of the M3-8 rebuild.

Files read:
- docs/review/phase-07c-2b/: 28-decider-m3h.md, 5-builder-tail-spread.md (L1–40), 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat1.md, 14-seat2.md, 14-seat7.md, 22-seat2.md, 22-seat5.md
- docs/PRD.md (L44–180)
- docs/BUILD_PLAN.md (rows 07d, 08-3, 08-4, 12-2; AX6)
- docs/phases/phase-07d.md (L75–103), phase-08-3.md (L1–90), phase-08-4.md (L20–27)
- docs/corpus/vorlaender-auralization.md (L2054–2068)
- docs/corpus/: grep for JNDs across the corpus (Blauert ch. 3 L336, Kuttruff L3284)
