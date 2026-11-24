# 1: Seat 2 (engine architect), M3: layout-5 provenance, the AX21 jump at s = 0.7 / 0.9, the B11 trigger

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE"). Run 2026-11-24 in the
phase-07c-2b session as `seat2-engine-architect`. Recorded verbatim from the seat's answer.

SEAT 2 POSITION (phase 07c-2b, scope 2, M3: which scene the AX47 self-ABX uses). The corpus is not present in this checkout (`docs/corpus/` is missing), so every acoustic claim below is flagged, and Kuttruff is cited through the repo files that quote it.

**1. Reading**
- The question: which scene or scenes carry the AX47 self-ABX, chosen from V1–V4 (file 31 L121–126).
- Cues it triggers:
  - §4 cue 3: one absorbing face, and placements 0.1 m from a face.
  - §4 cue 4: sources and listeners near walls.
  - §4 cue 5: the early/late energy split.
  - §6 S6: does the verdict cover the claim it is used for?
- My criterion: AX47 bounds tail-level steps for every valid scene. The scene should therefore be one where a tail-level error is most exposed, and it should sit inside the engine's valid regime.

**2. Ranking (V3′ is my own variant)**
1. **V3′, prefer.** V3, but only layout5_s1/default is added, and the S-W pool is limited to default placements. S-W then picks layout5_s1/default (tail share 0.579). At 08-3: (i) the same scene and (ii) S-B\* at s = 0.7.
2. **V4, can live with.**
3. **V1, can live with**, under condition C1.
4. **V2, can live with**, under C1 and C2.
5. **V3 as written, can live with only if emitter_wall is excluded.** Otherwise S-W picks emitter_wall (0.869).

**3. Tension now**
- **V3′: 1.**
  - layout5_s1/default is in the same engine regime as S-A: capped at m = 6, 7 and 8; AX22 fallback t_mix,e; E_target specular share 0; window unscaled share 4.1e−13; ΔC80 −0.900 dB (file 29 L40).
  - It keeps S-A's default placements, so both emitters are equidistant and the step falls at a gap start for both as heard.
  - It is 12× more exposed than S-A: ΔG 0.543 against 0.045 dB at 1 kHz.
- **V4: 1.** S-A is the AX21 extreme, but valid with its label. A non-detection there covers a tail that is 4.6 % of the heard energy.
- **V1: 2, falling to 1 under C1.** S-B\*'s AX21 jump is still unmeasured. That was my file 26 condition, and K4 did not print it.
- **V2: 2.** Under K5's verdict, S-W is both_wall (0.667). That is both-near (AX44):
  - At s = 1 the coherent wall reflection, 0.6 ms after the direct sound, is zeroed. The engine is least faithful in this placement class (§6 S4).
  - The far emitter's direct burst runs through 29.3 of the fade's 30 ms (file 32 L52–62), so the step does not fall at a gap start as heard.
- **V3 as written: 2 if emitter_wall is picked.** The 0.1 m emitter's distances are 22.1 and 12.4 m [Inferred from test_diffuse_wsweep.cpp L87, L100]. That puts about 28 ms of direct burst into the fade.

**4. Tension later**
- **V3′: 1.**
  - The AX47 /fix-plan changes one word, and undoing it costs about the same. Layout 5's provenance equals layout 4's (see Seat question 1).
  - The B11 trigger applies.
- **V4: 1.** S-B\* runs at 08-3 with C1. The B11 trigger applies.
- **V1: 1.** The 08-3 S-W binaural run brings 0.1 m placements; that goes to Seat 4.
- **V2: 1.** S-B\* is guaranteed at 08-3 with C1.
- **V3 as written: 1.**

**Seat questions**

1. **Layout 5's provenance as an AX47 scene.** It is equal to layout 4's.
   - It is a Kuttruff Table 5.2 one-absorbing-face case: phase-05b2.md L59, which I cannot check because the corpus is missing [Peer-report].
   - It is in the same independent tracer gate: at s = 1 the hybrid matches the tracer within −0.04 dB at 1 kHz, against +0.04 dB for layout 4 (phase-05b2.md L52–53) [Observed]. Those checks used AX28 positions, not the ABX placements, for both layouts alike.
   - It is in the same AX43 reported set (test_diffuse_records.cpp L1399) and in the 05b2 listening pack (L320).
   - "Layout-4" in AX47's Reversal records S-A's pre-registration. It is not an engine distinction.
   - One difference binds: heard T30 2.557 s against tail-alone T30 2.58–2.62 s (file 29 fact 9). File 34 item 3 already predicts that Seat 1's gap ≥ tail-T30 assertion fails on layout 5. It must be repaid (gap ≥ max of heard and tail T30, then Q5 rerun) before any seal.
   - Item-9 numbers for layout5_s1/default [Inferred; air term taken from S-A's A ≈ 640 m²]:
     - A ≈ 300 + 19 + 24 = 343 m², so r_c = 2.61 m;
     - r = 12.37 m, so r/r_c ≈ 4.7;
     - diffuse-field D/R ≈ −13.5 dB.
     - Measured per-emitter D/R is −3.8 / −4.8 dB, about 9–10 dB above that: the AX21 signature.

2. **The AX21 jump at s = 0.7 and 0.9.**
   - It is not measured. K4's "early −3.8 / −9.5 dB re direct" integrates the whole early window, which first-order images dominate.
   - Surviving images avoid the floor, so at t_mix,e = 380.4 ms (AX22 fallback) they have about 4–9 horizontal hits.
   - (0.99(1−s))^n then gives specular energy at t_mix,e about 21–47 dB (s = 0.7) and 40–90 dB (s = 0.9) below its s = 0 value [Inferred]. AX21 notes that the mean-order method overstates. My file 26 figures, with 12 hits, were upper bounds.
   - So beyond roughly 100–150 ms both are S-A's shape: a tail entering into near-silence. They differ from S-A only in the first orders.
   - **I prefer s = 0.7.** Its E_target specular share is 0.032, against 0.004 at 0.9, so it exercises M1's E′_diff formula non-trivially. Its early part is fuller. The kit's refusal limit sits at −14.9 dB, well clear of −3 dB.
   - **C1 (for S-B\* wherever it runs):** per band, the builder prints the energy in [t_mix,e − 12.5, t_mix,e − 2.5) ms against [t_mix,e + 2.5, t_mix,e + 12.5) ms, and the time the early envelope falls 60 dB below direct. The label says "partial-AX21".

3. **Trigger wording.** I accept it, with three changes:
   - (a) The trigger is "any change that makes AX21's statement false or moves t_mix,e (B11 promotion, an early-diffuse method, an AX22 rule change)", not only B11 by name.
   - (b) Rebuilt stimuli pass item 6, the cap check, the peak check, Q5, s_w ≤ 2.3 % and the M2 gap assertions before sealing. If promoted early scattered energy pushes s_w above 2.3 %, the kit refuses and the scene returns to the board.
   - (c) Earlier results stay recorded against their commit and scene hash as "pre-promotion engine". If no listening session follows the promotion before the 08-4 freeze or the beta, the promotion phase schedules item 15 on rebuilt stimuli. The trigger also needs a home outside `docs/review/`: phase-05e scope (b), the deferred B11 decision (BUILD_PLAN L264), and the phase-05b row.

**5. Evidence**
- [Observed] file 29 L28–46 and facts 3, 5, 9.
- [Observed] file 32 L44–62.
- [Observed] phase-05b2.md L52–59.
- [Peer-report] AX21 (BUILD_PLAN L144).
- [Observed] AX47 Reversal (L170).
- [Inferred] r_c and the jump estimates, arithmetic redone above.
- Researcher: verify that Kuttruff Table 5.2 lists the 10×30 m wall case, from the corpus.

**6. Conditions**
- **V1 and V4:** C1 lowers 2 to 1.
- **V2:** C1, plus C2 (a pool filter: no placement within 0.1 m of a face, and direct-path difference ≤ 2.5 ms between emitters) lowers 2 to 1, and C2 turns V2 into V4.
- **V3:** add the default placement only (that is V3′), giving 1.
- **V3′:** the layout-5 gap and T30 assertion is repaid before the seal.
- **File 34's "[S-A only]" clause:** it becomes "[s = 1 scenes]". It does not apply to S-B\*.

**7. Hand-offs**
- Seat 1: sensitivity, α split, and the gap rule on layout 5.
- Seat 3: click_check robustness, and the far-emitter burst overlapping the fade.
- Seat 4: 0.1 m placements in binaural.
- Seat 9: the layout-5 label and whether s = 0.7 is representative.
- Seat 7: hours.
- Builder: C1 and the Q5 rerun on layout5_s1/default.

**8. Premortem.** If V4 seals S-A alone and the result is a non-detection, a stage-1 source is admitted on a 4.6 % tail share. Its error is then first heard in a tail-dominated preset, and Phase 12's preset check is where it shows.

Files read: docs/review/phase-07c-2/29-k4-candidates.md, docs/review/phase-07c-2/32-k5-k6-clicks-session.md, docs/review/phase-07c-2/34-decider-m1-m2-final.md, docs/phases/phase-05b2.md (L44–68, L320), docs/BUILD_PLAN.md (L144, L170), tests/unit/test_diffuse_wsweep.cpp (L72–107).
