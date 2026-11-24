SEAT 3 POSITION

**1. Reading.** The question is how to build the L4 stimuli, the blind held-chord ABX of AX49's provisional tail against the exact tail (T60 8 s). It triggers two of my cues. The first is cost: the release into free decay is where the provisional's cut is exposed. The second is state discontinuity: the plugin hands over from the provisional to the exact tail with a crossfade, and that handover is D-C9's own debt.

**What A and B are.** The ABX compares two static IRs. The live handover is not one of them.
- **A** is the provisional IR alone: `StagedBuild::plan → solve → assembleProvisional()`.
- **B** is the exact IR: `assemble()` on the same plan, at the same level and seed. Engine.h L254 makes it bit-identical to buildRoomIR.
- Both are rendered through the same real-time engine. The chord is released into at least L of free decay.

Why static, three reasons:
- AX49's reversal reads "the L4 ABX detects the cut".
- Item 14 says "provisional against exact" with release into L of free decay. That only makes sense if A plays its whole decay. Under a handover, the decay after the crossfade would be the exact tail anyway.
- Static A against B is the most sensitive test of the cut (NFR-1).

The realistic interim-then-handover render tests a different thing (see "Handover ghost" below). It gets a print now, not an ABX.

**2. Ranking.**
- **L-a: prefer.** The stimuli go through the kit's existing tool: renderRealtime (Cli.cpp L651–735), the same engine, block and partition as AX47, and the same manifest and seal. That is item 14's "same chain and tool".
- **L-b: can live with** (conditions below).
- **L-c: can live with only if dated before 07d starts.** Otherwise later 2.

**3. Tension now.**
- **L-a: 1.** A small src/cli change, plus AX49's wording. Default renders are untouched.
- **L-b: 1.** A second stimulus path outside the kit. The kit can't build A through render_cli, because render_cli has no IR-file input.
- **L-c: 1.** The provisional already plays in the plugin's load path (ScenePipeline L655–656) and has no listening evidence on its one criterion.

**4. Tension later.**
- **L-a: 1.**
  - Commits: a validation flag that calls `assembleProvisional` from render_cli.
  - Risk: condition 6 erodes, i.e. a default or offline render picks up the provisional.
  - Undo cost: delete one flag.
  - Evidence: the [pipeline] offline-bypass test, and default render_cli goldens unchanged.
- **L-b: 2.**
  - Every rerun maintains a second renderer: 07d's candidates, an 08-3 binaural rerun if any, the handover variant.
  - That renderer has its own determinism test, and its seal is not integrated with abx_kit.py.
  - Undo cost: about one session to move it into render_cli later.
- **L-c: 2.**
  - 07d's gate closure (condition 9's split clause, the long-T60 corner) is built on top of the provisional.
  - If L4 is first heard after 07d, a detection reopens 07d's work (a phase of rework).
  - Evidence: L4 itself.

**5. Evidence.**
- **Truncation.** Energy past L_f is at most e^(−13.82·0.312) = e^(−4.312) = 0.0134 (−18.7 dB) [Observed, arithmetic; K17′, Vorländer §6.4.1 Eq. 6.4].
- **Steady-state loss.** At most −0.06 dB during the held chord [K17′].
- **Decay after release.** After an interrupted steady excitation, the decay equals the backward-integrated IR [Kuttruff §8.4 Eq. 8.29; Vorländer §6.4.1 Eq. 6.3].
  - So at release + (L_f − t_dir), B is about 18.7 dB down on its late energy and still decaying.
  - A falls to silence within 0.1 s, a further 0.75 dB of B's decay (60·0.1/8).
  - I predict A is detected on a loud held chord [Hyp]. That is why the test is worth running.
- **Plugin parity.**
  - render_cli builds serially, the plugin in parallel; test [staged] shows the two are bit-identical (Engine.h L134–138).
  - The plugin builds its provisional at the solve's level: keyless load, ScenePipeline L652–656.

**Handover ghost (D-C9 debt, my class "state discontinuity").**
- K23: both crossfade states read one input history.
- Suppose a chord is released more than L_p before the handover. A has gone silent. At the handover, B's tail of that chord fades back in over 30 ms, at about −19 dB or less on the late level.
- That is an onset out of silence. AX47 (b) does not cover it, because AX47 (b) bounds only the steady step −10·log10(1+(1−f_b)·δ).
- Exposure: only on load, first restore, or an fs change, while the exact tail is pending. Record (h) shows up to 9.5 s on Windows at 8 instances.
- Status [Hyp]: please have the **researcher** check whether any literature bounds the audibility of a reverb tail re-onset at −20 dB after silence.

**6. Conditions (the item-6-like assertions for L4, on L-a; L-b must meet the same ones).**
1. **Refusals.** The flag refuses when `provisionalTiming().provisional` is false (A would equal B). It also refuses with --ensemble, --tail-level ax16 and --switch-scene, and anything other than --mode omni.
2. **One plan.** A and B come from one plan, at the solve's level.
   - Samples before the earliest tail crossfade start are asserted bit-identical.
3. **Per-band level over the window.** Over [t_mix,e,max + 2.5 ms, L_f), per emitter and band:
   - A/B energy equals AX47 (b)'s predicted step within **0.05 dB**;
   - that value is printed and asserted.
4. **Ends.**
   - A has zero energy from L_p on.
   - B's length is L.
   - L_f, L_p, L, t_mix,e,max and per-band T60 are printed.
   - Decay from t_mix,e,max to L_f is at least 18.7 dB in every band (asserted).
   - B's energy share past L_f is at most 0.0134 per band (asserted).
5. **Stimulus timing and level.**
   - At least L of silent input after each release (asserted).
   - Held-portion level difference between A and B printed per band.
   - No normalisation (item 10).
6. **Determinism (AX5).**
   - Two runs are bit-identical.
   - Default render_cli output and goldens are unchanged.
   - A test shows src/plugin never names the flag.
7. **Plugin parity.** A JUCE-free [pipeline] test shows the keyless-load interim IR is bit-identical to `--provisional-ir`'s A for the same scene, so the stimulus is what the plugin plays.
8. **Anchor.**
   - Built on the L4 scene and chord: B against B with the tail +3 dB, via --abx-step-db with step sample 0.
   - It is not borrowed from the S-A stimuli.
9. **Ghost print (print only).**
   - From B's backward-integrated curve, per band: the re-onset level at a handover time of release + L_p + {0, 1, 2, 5} s.
   - It goes into the D-C9 debt register.

To lower L-b's later rating to 1:
- the harness renders through sim::RealtimeEngine at the kit's block and partition;
- its B render nulls against render_cli's default real-time render at −120 dB.

To lower L-c's later rating to 1: the named date falls before 07d starts, and 07d's entry gate cites L4's result.

**7. Hand-offs.**
- Seat 2: the T60_max 8 s scene and its L_p and L.
- Seat 5: the flag, AX5, the "plugin never reaches it" test, CI.
- Seat 7: hours. With L = 12 s there are about 3 × (hold + 12 s) per trial, so 16 + 6 trials is about 20 min.
- Seat 1: whether the ghost needs its own ABX.
- Interrogator: the wording of the AX49 amendment, i.e. "render_cli never uses the provisional, except under a validation-only flag; default and offline paths unchanged".

**8. Premortem.** If L-c slips past 07d, and the decision fails, it fails this way: the first listener to load a long-T60 project and hit play hears the tail stop short, then come back at the handover. A user report reaches Seat 7 first, and 07d's gate work has to be reopened.
