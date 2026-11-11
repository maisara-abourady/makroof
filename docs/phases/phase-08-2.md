# Phase 08-2 — Head-relative early binaural part

Size: **M** (remainder, if needed: `08-2b`) · Depends on: 08-1; and 04, 05b, 05h, 07 (05b `done` in either outcome; with "not promoted", this phase builds on the specular-only early part, AX21). It depends on 05h, except that it may precede 05h on Seat 4's conditions per AX37 (5.3) (D-T5.3): (i) E_b and t_mix,e are read only via `TailMatch`; (ii) parity is checked within the same build; (iii) 05h re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs item 8; (iv) this phase's listening items on concentrated absorption are marked provisional · Part of: [phase-08](phase-08.md) · Lead subject matter: Seat 4 (Chain keeper), "binaural architecture" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ6, AX3, AX5, AX35) and §3 (F7, F8), PRD FR-SIM-3, FR-SIM-4, FR-3D-9, A1; the umbrella [phase-08](phase-08.md) (shared items); [phase-08-1](phase-08-1.md) (`HrtfSet`, the named onset criterion)

## Goal

This sub-phase's share of the [phase-08](phase-08.md) goal: every early reflection reaches the listener's
ears from its true direction through a measured **generic HRTF** — the early part of the 2-emitter × 2-ear
binaural room impulse response (BRIR).

## Assumptions in force

- **AX3**: the head is upright, and yaw points toward the horizontal centroid of the emitters. If the
  centroid is within 0.1 m horizontally of the listener, the previous yaw is held (initial yaw = +y).
- And all of the umbrella's ([phase-08](phase-08.md), "Assumptions in force").

## Scope

3. `[alloc]` tests on `query` and on the BRIR build. (phase-08 scope 3, clause; the BRIR-build part is owned
   here, shared with 08-3, which extends the build)
4. `src/sim/binaural/ListenerFrame.h/.cpp` — AX3 orientation; converts world-space directions of
   arrival (from Phase 03 image sources) into head-relative azimuth/elevation. (phase-08 scope 4)
5. `src/sim/binaural/BrirBuilder.h/.cpp` — for each emitter: (phase-08 scope 5, lead-in; shared with 08-3)
   - **Early part:** for each image source (from Phase 03, using its per-band amplitude, delay and
     direction), add `band-filtered(amplitudes) * HRIR(direction)` into the left and right ear buffers at
     the arrival time plus the per-ear ITD. The direct path and orders 1–3 are never grouped. (phase-08
     scope 5, Early part, first and last sentences; the grouping rule between them is in 08-4, D-PS2)
6. `sim::buildRoomIR(Kind::Binaural)` returns the 2×2 BRIR matrix: emitter L → ear L/R and emitter R →
   ear L/R. (phase-08 scope 6, sentence 1; 08-3 adds the tail to the same path)
7. `render_cli --mode binaural`, listening-pack entries (phase-08 scope 7, clauses; the listening-pack
   entries are shared with 08-3: here the anechoic renders, including `anechoic_azimuth_sweep.wav`).
   `render_cli --hrtf <file>`:
   a **validation-only** override that renders through another converted `.bin` (CLI only, never in the
   scene, no host parameter; `hrtfId` stays the schema const; the AX4 `--no-air-absorption` pattern), so
   B9 can render through BRAS's FABIAN HRIRs (CC BY-SA 4.0: validation only, as the BRAS row in
   `docs/THIRD_PARTY.md` states). (phase-08 scope 7, `--hrtf` clause) Every preset validation log (the
   Phase 12 preset listening checklist and its PR listening notes, the Phase 13 final listening pass
   through all presets, and the B9 (§5) protocol logs) records the `hrtfId` and the header's set identity
   string of the build it was listened through; this phase's checklist does the same. (phase-08 scope 7,
   last sentence; shared, umbrella)

## Out of scope

The umbrella's out-of-scope list ([phase-08](phase-08.md)) applies. The late tail, energy parity and the
plugin's `binaural` wiring are 08-3; grouping, timing records, the restore gate and the goldens are 08-4.

## Acceptance criteria — automated

- [ ] **ITD/ILD sanity** (anechoic scene: α = 1 everywhere, direct path only): an emitter at +90°
      azimuth (left; define the azimuth sign convention in the code and docs) gives ITD between **0.6 and
      0.75 ms** with the left ear leading, and ILD > 6 dB averaged over 2–8 kHz. The mirror holds at −90°.
      An emitter straight ahead gives |ITD| < 20 µs and |ILD| < 1 dB. The window 0.6–0.75 ms
      **presupposes an onset (pulse-arrival) estimator**: it is sized to the onset ITD of brief
      pulses, ≈ 650 µs at 90° (Blauert Ch. 2 §2.2.2, Fig. 2.30), and to the far-source path
      difference divided by the speed of sound, (D/2)(φ + sin φ)/c = 0.225 m / 343 m s⁻¹ = 0.656 ms
      for D = 17.5 cm (Blauert Ch. 2 §2.2.2). The estimator is therefore of the
      onset class — the converter's per-ear onset detection that yields `onset_left`/`onset_right`,
      run on the resampled HRIRs before EQ and onset removal, and the same criterion applied by the
      test to the rendered anechoic output — and its exact criterion (threshold relative to the
      ear's peak) and the sign convention are named in this AC by the decision loop **before the
      first measurement**. A low-frequency ITD (≈ 750 µs for an average human head) exceeds the
      broadband onset ITD (≈ 650 µs); the value depends on stimulus and measurement technique
      (Roginska & Geluso Ch. 1; Blauert Ch. 2 §2.2.2: the sphere model's interaural phase and group
      delay reach about 0.6–0.8 ms), so an estimator of another class would need its own window
      derived from the corpus before measuring — never this one widened. If the pinned file measures
      outside 0.6–0.75 ms with the named onset criterion, the window is challenged on that evidence
      through the interrogator, never widened to pass (decider challenge C-1: York's own ITD plots
      read ≈ 0.85 ms for D1 by an unstated method, dossier F21). Not a head reversal. (phase-08 AC3)
- [ ] **Orientation (AX3):** a unit test with emitters ahead, behind and on top of the listener gives
      the documented yaw, and the hold rule triggers at < 0.1 m. (phase-08 AC7)
- [ ] **Validation-only override:** `render_cli --hrtf <file>` renders through the given converted set;
      the option exists only in the CLI (no scene field, no host parameter; `hrtfId` stays the schema
      const), and the scene validator still rejects any other `hrtfId`. (phase-08 AC10)
- [ ] All earlier tests still pass. (phase-08 AC12, sentence 1; shared, umbrella)

## Listening / manual checklist (Maisara, headphones)

Listening pack (`binaural/`) and the plugin in a DAW with `output_mode = binaural`. The pack never names
the head (the dataset is named only in the licence file, `docs/THIRD_PARTY.md` and the public testing
record). Fixed acceptance set, rendered for every item: an **a cappella voice, pink-noise pulses and
speech**. Every room render comes with an **anechoic direct-only render** (α = 1, direct path only) of the
same emitter and listener positions beside it, and with the omni preview. Answer in the **forced-choice
form**: location **front / back / above / inside / outside**; colour against the omni preview **none /
boxy / thin / harsh**. Record the `hrtfId` and the header's set identity string of the build you listened
through (scope 7). (phase-08 L0; shared, umbrella)
- [ ] `anechoic_azimuth_sweep.wav`: a sound circling the head. It should be clearly left, right and
      front. Front/back confusion is common with generic HRTFs, so note it. (phase-08 L2)

## Contractor review focus

- coordinate and sign conventions (phase-08 CF3)
- the `--hrtf` override staying out of the scene and the plugin (phase-08 CF9)

## Risks

- Generic HRTFs cause front/back confusion and weak externalization for some listeners. This is an
  expected limitation, recorded as evidence for B4. (phase-08 R1; shared, umbrella)
- F8: the head always faces the emitters, so sources can't be put behind the listener. Report it if it
  sounds odd in practice. (phase-08 R2)
- AC 3's ITD window may fail on the SADIE heads (York's plots read ≈ 0.85 ms by an unstated method;
  a low-frequency estimator reads higher than an onset estimator). Not a head reversal: name the
  onset criterion first, then challenge the window through the interrogator on the measurement
  (C-1). (phase-08 R5)

## Notes from the split

- AX37 (5.3) condition binding this sub-phase: (i) E_b and t_mix,e read only via `TailMatch`. (D-PS1,
  `docs/review/phase-split/5-decider-decision-r2.md`, instruction 3)
- Note (Seat 4): t_mix,e (handover and image-list bound) read only from the same `planEmitter`/`TailMatch`
  result as the omni build. (D-PS1, instruction 3)
- 08-2 reads t_mix,e (the AX20 list bound and the handover) and the AX22 fallback, through the shared
  `planEmitter`/`TailMatch` path, and no E_b; its anechoic checks (AC3, AC7, AC10) read none. 05h leaves
  these unchanged (AX37 (5.2); phase-05h scope 'Mixing-time rule: unchanged'). (D-PS1, instruction 3)
- AC 3's onset criterion and sign convention are named by the decision loop at the start of 08-1, before
  the converter's first run, and written into AC 3 here (convening round, 08-c4 (a)).

## Definition of done

- All automated criteria green (phase-08 DoD1; this sub-phase's own).
- checklist in the PR with the `hrtfId` and set identity string (phase-08 DoD5; shared, umbrella).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the
  remainder into `phase-08-2b.md`.
