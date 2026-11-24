<!-- Saved by the orchestrator from seat 2's report, 2026-11-22. -->

SEAT 2 POSITION (phase 07c-2, D-W2 ABX kit, file 24, M3). Corpus present (c1b171fe).

**Summary.** I prefer S-A: keep `layout4_s1/default`. The empty early part is AX21 behaving exactly as documented, not a defect. S-C does not fix the dryness, because it is the same scene at s = 1. S-B gives an early part only by putting another AX21 artefact into the stimulus, and its assertions are unchecked. Separately, the code contradicts the claim in files 23 Q2 and 24 that item 6 fails whenever the specular share is above 0; the decider should resolve this before ruling M1.

**1. Reading**
- The question is whether the scene's empty early part lies inside the engine's documented limits, and whether S-B or S-C would give it an early part.
- Cues it triggers: §4 cue 3 (geometry class: an absorbing floor, so concentrated absorption); cue 5 (what deviates is the early/late energy split, not the decay); §6 S6 (is a claim honest?).

**2. Ranking**
1. **S-A, prefer.** Keep the scene with file 24's corrected label, plus the NFR-8 record.
2. **S-B, can live with, only under conditions.** My concrete version (S-D): `t52_layout4_s0.4`, Table 5.2 layout 4 at s = 0.4. It is already in the listening pack and checked against the reference: C++ minus reference is +0.0084 dB at 1 kHz (phase-05h file 18).
3. **S-C, can live with only as item 9's fallback for an uncapped scene.** As a cure for dryness it does nothing.

**3. Tension now**
- **S-A: 1.**
  - The empty early part is inside the documented limits.
  - AX21 says the hybrid IR is specular-only before t_mix,e, and B11 was not promoted (05b gate B failed).
  - From the code, each image carries (1−α)(1−s) per hit. Kuttruff Eq. 8.59 gives I_spec/(I₀(1−α)) = 1 − s, so at s = 1 the specular part is exactly 0.
  - File 22 measures the tail decaying at Eyring: 1.254 / 1.274 s against 1.291 s.
  - This is the extreme case of AX21, not a typical scene. It is admissible only with that stated in the label.
- **S-B: 2.**
  - At any s < 1 the images carry energy: the first-order wall reflections are 0.99(1−s), which is −2.2 dB at s = 0.4.
  - But t_mix,e stays at 380.4 ms for layout 4 at every s (the AX22 fallback; 05b2 file 7 table).
  - The specular-only early part therefore decays as (1−s)^n̄ over about 12 hits [Inferred: mean free path 4V/S = 10.9 m, 343 · 0.38 / 10.9 ≈ 12].
  - The tail then enters at t_mix,e with an AX21 envelope jump of about 5.5 dB at s = 0.1, 15 dB at s = 0.25 and 26 dB at s = 0.4 [Inferred, an upper estimate by the same method as AX21; AX21's 0.9–8.7 dB were for t_mix = 114 ms]. A and B carry the jump identically, but the stimulus is still AX21-deficient, only in another form.
  - Two assertions are unknown (K3): whether the scene is capped at m = 6, 7 and 8, and whether the specular share of E_target stays at or below 10^(−3/10) = 0.50, which the −3 dB anchor down-step needs (Cli.cpp:788–793).
  - N_need falls with s: 490 paths at s = 0.1 against 21,984 at s = 1 (05b2 file 7), so a low s may come out uncapped.
- **S-C: 2.**
  - `layout4_s1/listener_wall` has s = 1 on every face (test_diffuse_wsweep.cpp:94), so its early part is just as empty.
  - It moves r to 20.1 m and r/r_c to about 5.2 (diffuse D/R about −14 dB), and adds a listener 0.1 m from a wall. That is one more untested variable and no gain.

**4. Tension later (the debt)**
- **S-A: 1.**
  - The verdict is obtained on an engine with no early scattered energy. Undoing it costs only a rerun.
  - Debt trigger to record: if B11 is ever promoted, the AX47 ABX stimuli are rebuilt on the promoted engine. Item 15's 08-3 binaural rerun is the next natural point.
- **S-B: 2.**
  - It amends the pre-registered scene and changes the scene hash.
  - If the AX21 jump is later held to bias the result, the cost is a full redo. It also binds item 15's rerun to the same artefact.
- **S-C: 1.** It gains nothing to carry forward.

**5. Evidence**
- Kuttruff Eq. 8.59 (§8.8) defines the specular part of a reflection as (1−s)(1−α) of the incident energy [corpus]. Kuttruff §9 (hybrids): the early part is built from specular components [corpus].
- The AX21 and B11 rows of BUILD_PLAN.
- From the code:
  - images are rendered only up to t_mix,e + 2.5 ms (Engine.h:182; crossfade in NoiseTail.h:13);
  - E_target = E_spec + E_diff (Engine.cpp:183);
  - the step sets E'_diff = k·E_diff + (k−1)·E_spec, so E'_target = k·E_target and the whole rendered tail scales by √k (Cli.cpp:742–796).
- **Challenge to file 23 Q2 and file 24's corrected item-5 sentence.**
  - In the rendered IR the window after t_mix,e + 2.5 ms contains no images, so item 6's identity holds exactly at any specular share of E_target.
  - `tests/unit/test_cli.cpp:350–358` already asserts it within 0.01 dB on `small_room`, whose specular share is about 0.74.
  - The model a = √((k−s)/(1−s)) assumes the window holds unscaled specular energy. The code renders none there; only the 2.5 ms half fade-out lands inside [t_mix,e, L), under item 6's 0.1 dB tolerance.
  - "Specular share" is used for two quantities: the share of E_target (Cli print, which decides refusal) and the kit's window share (abx_kit.py:251, inferred from the identity). Researcher or interrogator to verify; it bears on M1 and on S-B.

**6. Conditions of acceptance**
- **S-B (2 → 1)** only if all of these hold:
  - the builder shows it is capped at m = 6, 7 and 8 (AX47's Reversal sentence says "capped layout-4 scene");
  - the specular share of E_target is ≤ 0.40 in all 8 bands;
  - the AX21 jump at t_mix,e is measured and printed in the manifest;
  - it is labelled as the partial-AX21 case.
- **S-C (2 → 1)** only as item 9's uncapped-scene fallback, never as a cure for dryness.
- **S-A (to 0):** the corrected label plus the B11 debt trigger.

**7. Hand-offs**
- Seat 1: whether the empty early part leaves the tail less masked in the gap, which biases toward detection (the conservative direction for the bound) rather than non-detection [Hyp].
- Seat 3: M1, read against the Cli.cpp code fact above; the +18 % tail T30 at 8 kHz.
- Seat 9: the label, and whether a reference room is closer to a mid-size hall.
- Builder: K3 (cap flag, E_target specular share and the t_mix,e jump at s = 0.1, 0.25 and 0.4).

**8. Premortem.** If S-B is chosen without the cap check, the kit seals a scene that is either uncapped (it no longer tests a statistical source) or one whose −3 dB anchor down-step the kit refuses. The builder's first rerun notices.

Files: /home/user/makroof/src/cli/Cli.cpp (737–803), /home/user/makroof/tests/unit/test_cli.cpp (350–358), /home/user/makroof/src/sim/Engine.h (182), /home/user/makroof/src/sim/Engine.cpp (178–183), /home/user/makroof/tools/ci/abx_kit.py (228–259), /home/user/makroof/tests/unit/test_diffuse_wsweep.cpp (72–107), /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md (46–57), /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Eq. 8.59, line 3997; §9 hybrids, line 4358).
