# Phase 08-3 — Binaural late tail, level parity and plugin mode

Size: **M** (remainder, if needed: `08-3b`) · Depends on: 08-2; and 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Part of: [phase-08](phase-08.md) · Lead subject matter: Seat 4 (Chain keeper), "binaural architecture; … cross-format loudness and timbre parity" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the umbrella [phase-08](phase-08.md) (shared items); [phase-08-1](phase-08-1.md) (coherence target, DF-EQ), [phase-08-2](phase-08-2.md) (early part, `Kind::Binaural`)

## Goal

This sub-phase's share of the [phase-08](phase-08.md) goal: the late tail has the interaural coherence of a
diffuse field, and the result is a 2-emitter × 2-ear binaural room impulse response (BRIR) applied by the
Phase 06 convolver (headphone rendering, `outputMode = binaural`).

## Assumptions in force

- **AX5**: deterministic; tail noise per ear is seeded from `tailSeed` with the per-output offset from Phase 04.
- **AX37 (5.3)** (phase 05b): this phase receives E_b and t_mix,e per emitter through `TailMatch` and no
  tail directions; `bandsAxisShares` is a labelled specular-only diagnostic. A directional late tail is
  backlog (§5 B18), behind Seat 1's blind test. **AX39**: one diffuse solve per scene, shared across
  output modes. **AX38**: the diffuse solve runs through the process-wide gate; W1/W2 include it.
- And all of the umbrella's ([phase-08](phase-08.md), "Assumptions in force").

## Scope

3. `[alloc]` tests on `query` and on the BRIR build. (phase-08 scope 3, clause; the BRIR-build part, shared
   with 08-2)
5. `src/sim/binaural/BrirBuilder.h/.cpp` — for each emitter: (phase-08 scope 5, lead-in; shared with 08-2)
   - **Late tail:** two noise tails (left/right seeds) with the Phase 04 per-band envelopes, then mixed per
     band so the **interaural coherence** follows the diffuse-field model for a head: compute the target
     coherence per band from the HRTF set itself (diffuse-field average of the interaural cross-spectrum,
     solid-angle (Voronoi) weighted over the stored subset, done in the converter, scope 3), and apply it
     with the standard 2×2 mixing
     (`L = a·n1 + b·n2, R = a·n1 − b·n2` with a and b set from the target coherence), then apply the
     diffuse-field HRTF magnitude per ear. (phase-08 scope 5, Late tail)
   - Energy: the binaural BRIR's per-band energy (average of the two ears, diffuse-field equalized)
     equals the omni IR's per-band energy within ±1 dB. This keeps levels consistent between modes.
     (phase-08 scope 5, Energy)
   - E_b and t_mix,e are read only via `TailMatch` (AX37 (5.3)), from the one diffuse solve per scene
     (AX39); E_b is bit-identical between omni and binaural and between the ears (AX44, Seat 4).
     (phase-08 scope 5, E_b and t_mix,e)
   - **AX49 provisional tail and AX48 saved E_b** (phase-07c-1 decision loop, 2026-11-12; decider file
     `docs/review/phase-07c-1/12-decider-decision-r3.md` §8): the provisional tail uses the same
     `tailSeedForOutput` seeds and the same per-mode decorrelation as the exact tail; a v2 state restored in
     binaural uses the saved E_b bit-identically (AX48 tests); a mode switch never re-solves, never waits for a
     synthesis and reuses the cached unit decays (Seat 4 M; AX49).
   - **Phase-07c-1b loop (2026-11-13; `docs/review/phase-07c-1b/11-decider-decision-r3.md` items 6, 11):** the AX47
     mid-fade check (AX47 "Measurement", 07c-1b's `[ax47-midfade]`) runs per ear; at instance insertion (AX48, FM-B2)
     the first IrSet carries the per-ear seeds and decorrelation, asserted beside the `[pipeline]` insertion test.
6. The plugin sends `outputMode` through, so `binaural` now uses this path. `stereoSpeakers`
   keeps using omni until Phase 09. (phase-08 scope 6, sentences 2–3; sentence 1 in 08-2) No UI
   code or string table knows which head shipped: any About/credits text reads the header's attribution
   string; the main window and the mode switch never show a dataset name. (phase-08 scope 2,
   Dataset-agnostic header, last sentence; shared, umbrella; owned by 08-1)
7. listening-pack entries (including one both-near binaural render:
   listener and an emitter within 0.70 m of surfaces, AX44, Seat 4) (phase-08 scope 7, clauses; the
   listening-pack entries are shared with 08-2: here the room renders and their omni previews) Every
   preset validation log (the Phase 12 preset listening checklist and its PR listening notes, the Phase 13
   final listening pass through all presets, and the B9 (§5) protocol logs) records the `hrtfId` and the
   header's set identity string of the build it was listened through; this phase's checklist does the
   same. (phase-08 scope 7, last sentence; shared, umbrella) If heard before phase-07e-b is `done` (and the fix
   phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine
   before the 07e-b ruling'. A level or dryness remark on a near-face render goes to 07e/07e-b (or, once 07e-b is
   `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones. The label is lifted without
   re-hearing if 07e-b rules no fix phase.
15. 08-3. Before Phase 08's goldens freeze, the AX47 self-ABX is rerun on the binaural chain at the bound in force,
    as two pre-registered families (F3, F4) with F1 and F2's design (both chains 24 scored trials + 6 anchors, 3 per
    half, break after presentation 15, ≥ 18/24; per family ≤ 0.0227; union over F1–F4 ≤ 0.0906), item 4 applied within
    each; the record states each family's α, the union rate and which family detected at what count.
    - (i) The S-W scene sealed in 07c-2b, with tailSeed, programmes, steps and trials identical to 07c-2b's. Where its
      listener is < 0.70 m from a face (AX44 d_L), it is labelled 'chain comparison only; listener 0.1 m from a face,
      outside the free-field HRTF's validity', and it carries the 07c-2b S-W label's onset sentence. A non-detection
      there is never counted as binaural evidence for the class; a detection reverses AX47 per item 4. A null there is
      worded with its heard step per ear: 'not detected in 24 trials by one listener (power 0.61 at p = 0.75) on
      layout4_s1/both_wall (<record line>); heard step at 1 kHz ΔG {L} / {R} dB, ΔC80 {L} / {R} dB per ear for the
      0.9 dB tail step [0.5 dB: as printed in the manifest], at the recorded commit; void as evidence for this scene
      after a t_mix,e change until rebuilt (M3-8)', values from the manifest, never typed by hand.
    - (ii) The S-B\* scene sealed in 07c-2b, likewise identical. Its null is worded in the 07c-2b S-B\* form, with
      per-ear ΔG and ΔC80, and carries the label's SPREAD clause.

    Neither family is cited for externalisation or plausibility, and L4/L5 are not judged on these scenes.
    Stimuli are built only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done`
    (phase-07c-2b M3-H, decider files 30, 33, 40, 43; the fix phase's id is added here when its §0 row is created).
    Before any stimulus, per scene: binaural vs omni per-band energy within ±1 dB (AC6); per-ear, per-band energy
    printed (print only); item 6 (HF-W with condition D) and `[ax47-midfade]` per ear; the M2 gap and Q5 checks per
    ear; D/R printed per ear; `hrtfId` and the set identity string recorded; the same wired headphone model and level
    setting as 07c-2b, recorded in the 07c-2b and 08-3 records, and no virtualiser.
    Sittings of ≤ 2 h each (two if nothing is detected at 0.9 dB, three if something is), split only at a chain
    boundary, on the same or consecutive days, dates in the 08-3 brief before 08-3 starts: about 2.6 h, up to about
    5.0 h (builder file 32 K6 pace). Results are worded 'static, uncompensated (B14), generic HRTF', and for (i) also
    'empty early part (AX21)'. If the trigger (M3-8) fired after 07c-2b, the stimuli are rebuilt and pass every seal
    gate again (HF-W worst ratio, margin and skip count printed; the tail-spread print), and the cross-chain comparison
    is recorded void unless the omni family is rerun on the current engine. If a rebuilt scene fails a seal gate, item
    15 returns to the board before any 08-3 listening. (phase-07c-2b M3, `docs/review/phase-07c-2b/` decider files 9
    §6 item 2 and 17 §6 item 2; the run sheet `docs/validation/abx-07c-2-run-sheet.md` §0, item 15)

## Out of scope

The umbrella's out-of-scope list ([phase-08](phase-08.md)) applies. Grouping, timing records, the restore
gate and the goldens are 08-4.

## Acceptance criteria — automated

- [ ] **Tail coherence:** measured interaural coherence of the late tail per band is within ±0.1 of the
      target curve (125 Hz–4 kHz); the target is the solid-angle-weighted one (scope 3). (phase-08 AC5)
- [ ] **Energy:** binaural vs omni per-band energy within ±1 dB for all valid fixtures. (phase-08 AC6)
- [ ] T30 of each ear's BRIR within ±5% of the omni IR's T30 (250 Hz–4 kHz). (phase-08 AC8)
- [ ] **E_b parity (AX44):** E_b is bit-identical between omni and binaural and between the ears.
      (phase-08 AC11)
- [ ] **Interim tail per mode (AX48, AX49):** the binaural provisional tail uses the exact tail's
      `tailSeedForOutput` seeds and decorrelation; a mode switch never re-solves or waits for a synthesis.
- [ ] **Interim tail stream per ear (AX47 (b) prefix check; D1, FM-D1-S3):** on the A4 set (48 and 96 kHz, 2 seeds,
      more only with a reason in the PR), per emitter, ear and band, the binaural provisional IR against the exact IR,
      both as shipped (after the 2×2 coherence mix and the per-ear diffuse-field HRTF magnitude and any DF-EQ), from two
      serial builder calls of one scene and seed in one process (never from the async pipeline; never against a
      measured IR; a repeat build of each IR, N1 and N2 included, asserted bit-identical before any comparison):
      10·log10(E(provisional − exact)/E(exact)) ≤ 20·log10(10^(B/20) − 1) dB, B the AX47 bound in force
      (1 dB → −18.27 dB; 0.5 dB → −24.55 dB), over [t_mix,e, L_f − h), L_f the AX49 fade start (the same in every
      mode), h the backward reach in samples at each fs of every filter between the noise and the shipped IR (the
      generator's band filters; any band split used by the coherence mix; the per-ear DF-HRTF magnitude and DF-EQ
      filters, half-length if linear-phase with latency compensated, 0 if causal) plus the analysis filterbank's. The
      window length is printed per case and band; the window's specular energy share of E(exact) is printed per case
      and band (Seat 3, print only); an empty window, L_p ≥ L (no provisional) or zero matched tail energy (AX49 D1)
      prints 'not evaluated' with its reason and never counts as a pass; ≥ 1 evaluated case per band, ear and fs
      (non-vacuity, not a quota). Negative controls, both asserted red: **N1**, the provisional built with
      tailSeed + 1 (neither of its `tailSeedForOutput` seeds equal to either of tailSeed's, asserted as a guard on
      the seed derivation), per emitter, ear and band, expected ≈ +3.01 dB whatever γ_b (Vorländer §4.3 Eq. 4.15);
      **N2**, the provisional built with the two `tailSeedForOutput` seeds swapped, asserted on the two-ear aggregate
      per emitter and band, 10·log10((E_L,diff + E_R,diff)/(E_L + E_R)), expected ≈ +3.01 dB at equal ear energies,
      with each ear's value printed beside its unit-gain closed form, L 10·log10(2(1 − √(1 − γ_b²))),
      R 10·log10(2(1 + √(1 − γ_b²))), and the per-band ear energy ratio printed (L alone is not asserted: it is green
      where |γ_b| ≤ 0.122 at B = 1 dB (≤ 0.059 at 0.5 dB)). Direct assertion: the provisional and exact builder paths
      take the mix coefficients (a_b, b_b) and the per-ear filter coefficients from one shared function or cache, and
      the test asserts them bit-identical within one process (never across OSes). The exact IRs are those already
      built for the AX47 (b) and mid-fade fixtures (one build per scene, fs and seed); the test runs in the Release
      test job; the PR prints the added wall time per OS. (Maisara 2026-11-13; phase-07c-1b decider files 16, 19;
      Seats 4, 5, 3 files 15, 17, 18; interrogator file 20)
- [ ] **AX47 mid-fade check per ear; insertion per ear (AX47, AX48 FM-B2):** the AX47 mid-fade check passes per
      ear; the first IrSet at instance insertion carries the per-ear seeds and decorrelation (beside the `[pipeline]`
      insertion test).
- [ ] All earlier tests still pass. (phase-08 AC12, sentence 1; shared, umbrella) pluginval passes.
      (phase-08 AC12, sentence 2)

## Listening / manual checklist (Maisara, headphones)

Listening pack (`binaural/`) and the plugin in a DAW with `output_mode = binaural`. The pack never names
the head (the dataset is named only in the licence file, `docs/THIRD_PARTY.md` and the public testing
record). Fixed acceptance set, rendered for every item: an **a cappella voice, pink-noise pulses and
speech**. Every room render comes with an **anechoic direct-only render** (α = 1, direct path only) of the
same emitter and listener positions beside it, and with the omni preview. Answer in the **forced-choice
form**: location **front / back / above / inside / outside**; colour against the omni preview **none /
boxy / thin / harsh**. Record the `hrtfId` and the header's set identity string of the build you listened
through (scope 7). Verdicts heard before phase-07e-b is `done` are marked 'provisional: engine before the 07e-b
ruling' (item 7). (phase-08 L0; shared, umbrella)
- [ ] Default scene with emitters at about ±30° ahead: where is the image (front / back / above / inside /
      outside)? Expected: in front and outside your head. (Generic HRTFs are heard inside the head,
      or reversed front/back, by some people, and height on the median plane is uncertain
      (Begault Ch. 3; Vorländer §6.3.2). Note what you hear; that's what B4 is for.) (phase-08 L1)
- [ ] Move the listener close to the L emitter: the image pulls left and the room recedes. (phase-08 L3)
- [ ] Large hall: the reverb surrounds you rather than sitting between the ears like a normal stereo reverb.
      (phase-08 L4)
- [ ] Colour against the omni preview, for the room render and for its anechoic render: none / boxy / thin /
      harsh. (phase-08 L5)
- [ ] **Complaint protocol (Seat 9):** a colour complaint on a preset is checked against the anechoic
      render and the omni preview beside the preset before it is assigned to room, head or headphones.
      Head shadow is not a low-frequency effect (Rumsey §2.1.2: the head is an appreciable barrier at HF,
      not at LF), so a weak 125–250 Hz is not head shadow. A low-frequency loss can still come from the
      HRIR window (Begault Ch. 4 "Methods for Data Reduction": rectangular windowing may lose
      low-frequency information) or from the set's LF extension (SADIE II: below ~200 Hz modelled).
      "Thin" that persists in the anechoic render is therefore checked against the converter's LF
      response (the `--diagnostics` curve below 400 Hz) before it is assigned to room or headphones.
      (phase-08 L6)
- [ ] **Hand-off to Phase 11 (Seat 6):** one line in the PR for the output-mode tooltip or manual, a
      default-experience note (what a listener may hear through the generic head: inside or behind for
      some), with no head name. (phase-08 L7)
- [ ] AX47 binaural rerun, item 15, F3/F4.

## Contractor review focus

- the diffuse-coherence mixing (phase-08 CF7)
- energy normalization between modes (phase-08 CF8)

## Risks

- Generic HRTFs cause front/back confusion and weak externalization for some listeners. This is an
  expected limitation, recorded as evidence for B4. (phase-08 R1; shared, umbrella)
- Headphone compensation has no slot in the plan (§5 B14, open debt): expect colouration notes in the
  checklist that no Phase 08 step addresses. (phase-08 R7)

## Notes from the split

- AX37 (5.3) conditions binding this sub-phase (D-PS1, `docs/review/phase-split/5-decider-decision-r2.md`,
  instruction 4): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same
  build; (iv) this phase's listening items on concentrated absorption are marked provisional.
- 08-3 marks its verdicts on L1, L3, L4, L5 "provisional if 08-4 introduces grouping". (D-PS2,
  `docs/review/phase-split/3-decider-decision.md`, step 4)

## Definition of done

- All automated criteria green (phase-08 DoD1; this sub-phase's own).
- checklist in the PR with the `hrtfId` and set identity string (phase-08 DoD5; shared, umbrella).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the
  remainder into `phase-08-3b.md`.
