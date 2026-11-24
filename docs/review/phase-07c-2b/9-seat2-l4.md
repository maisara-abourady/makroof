SEAT 2 POSITION

**1. Reading.** L4 needs a provisional-vs-exact stimulus pair from `StagedBuild::assembleProvisional` at T60_max ≈ 8 s with L_p < L. You asked how the stimuli are produced (L-a, L-b or L-c) and which scene to use. Cues from my §4: cue 1 (V and T give t_mix and the timing), cue 7 (what a validation instrument costs), and S6 (a claim that has not been validated, here "the provisional is inaudible").

**Scene (my answer to the seat question).** I derive it from `tests/scenes/valid/stone_box.json` (20×12×10 m, V 2,400 m³, S 1,120 m², α 0.05, listener (10, 8, 1.7), emitters (8, 3, 1.7) and (12, 3, 1.7)). Multiply every band's absorption by 0.844. That gives 0.0422 in 63 Hz–1 kHz, then 0.0506, 0.0591 and 0.0675. Keep the geometry, s 0.1 and tailSeed 106. Render with `--mode omni`.
- **Eyring check:** −ln(1−0.0422) = 0.0431. T = 0.161·2400/(1120·0.0431) = 8.0 s. Air absorption at 63 Hz is negligible, so T60_max sits in the 63 Hz band.
- **t_dir:** √(2² + 5²) = 5.385 m, so t_dir = 15.7 ms.
- **K20 bound:** t_mix,e ≥ 15.7 + max(20, √2400 = 49.0) ms = 64.7 ms.
- **Result:** L_f ≈ 0.0647 + 0.312·8.0 = **2.561 s**, L_p ≈ **2.661 s**, L = min(1.5·8, 12) = **12.0 s**. So L_p < L by 9.3 s.
- **What the builder must measure:**
  - `render_cli --scene <variant> --mode omni --diagnostics d.json`. Adjust the 63 Hz–1 kHz α until T60_max is 8.0 ± 0.1 s (inside the 5 % JND).
  - Print `provisionalTiming()` (mixMaxS, t60MaxS, fadeStartS, endS, exactS, provisional = true) for the record. The 0.0647 s above is a lower bound; the realised handover may be later.

**Why this scene and not the gated 100 m cube.** At the gated geometry (t_dir 0.118 s, √V term 1.0 s), L_f = 3.614 s, L_p = 3.714 s and L = 12 s (AX49 K15′+K20), so it also qualifies. But there the early part before t_mix holds most of the energy. After a chord's release, the provisional's cut lands at about −26 dB re steady state. In the stone variant it lands at about −19 dB: e^(−13.82·(2.561−0.016)/8) = 0.0123. That is about 7 dB more exposed, so the stone variant is the more sensitive valid test. [Inferred; Kuttruff Eq. 5.24; 60·0.312 = 18.72 dB.] The cube stays a second, optional scene tied to the rated corner. Label: "hard stone box, T60 8 s, synthetic, not a measured room". No "hall" (Seat 9).

**2. Ranking.**
- **L-a: prefer.** The provisional IR becomes a render_cli artefact. `tools.acoustics metrics` and the EDC can then score it, and the 07d reversal and future re-checks can reuse it.
- **L-b: can live with.**
- **L-c: can live with only under the condition in point 6.**

**3. Tension now.**
- **L-a: 1.** A settled clause is amended (AX49's condition 6, "render_cli never use the provisional"). There is no engine change: `assembleProvisional` exists.
- **L-b: 1.** A second WAV-writing path outside the null-tested render_cli chain (AX1 alignment, export).
- **L-c: 1.** Nothing is lost today.

**4. Tension later.**
- **L-a: 0.** Removal is one flag. Evidence: a test shows that `src/plugin` never reaches it.
- **L-b: 1.** The harness can drift from render_cli. Undoing it costs one test file.
- **L-c: 2.** The provisional plays on every project load (AX49) but has no blind result, and the "L4 detects the cut" reversal cannot fire. If a later L4 detects the cut, the fix is to raise 0.312. That raises L_p at the rated corner, where L_p ≤ 3.82 s already binds. The 07d load gate (Windows 8 instances, 9.51 s against 5 s) would then be re-measured on a moved target. Cost: a board round plus 07d rework.

**5. Evidence.**
- Eyring with air absorption: Kuttruff Eq. 4.12 / 5.24 (corpus).
- Energy past L_f ≤ 0.0134: AX49 K17′ (Vorländer Eq. 6.4).
- L = 1.5·T60_max capped at 12 s: from the code (`Engine.h` L240).
- t_mix bound: K20.
- Cut levels re steady state, and "audible after release": [Inferred] / [Hyp]. Seat 1 judges.
- T60_max = 8.0 s at α 0.0422: [Inferred]. The builder confirms it in the diagnostics.

**6. Conditions.**
- **L-c:** goes to 1 if it is dated before 07d pins its load gate or its 0.312 candidates, so that the L4 result is known before the rated corner is re-measured.
- **L-b:** goes to 0 if its exact-IR output is asserted bit-identical to `render_cli --mode omni --ir` for the same scene.
- **L-a (not required, but asked):** add a print of L_f, L_p, L and `provisional` in `--diagnostics`, and refuse the flag where `provisional` is false.

**7. Hand-offs.**
- **Seat 1:** whether a −19 dB cut after release is audible, and that a static ABX is a ceiling (in the product the provisional plays only until the crossfade).
- **Seat 3:** the handover is not in the stimulus.
- **Seat 5:** the flag's real-time and CI gate.
- **Seat 9:** the label.
- **Seat 7:** the trial length (release plus 12 s of free decay).

**8. Premortem.** L4 is deferred or run on the 100 m cube. Producers then hear a reverb on project load that stops at −19 dB in hard rooms. A user or Seat 1's panel notices first, after 07d has already pinned the load gate on 0.312.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/8-decider-scene.md
- /home/user/makroof/docs/BUILD_PLAN.md (AX49 row, L172)
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md (item 14)
- /home/user/makroof/src/sim/Engine.h
- /home/user/makroof/tests/unit/test_interim.cpp
- /home/user/makroof/tests/scenes/valid/stone_box.json
- /home/user/makroof/tests/scenes/valid/large_hall.json
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md
