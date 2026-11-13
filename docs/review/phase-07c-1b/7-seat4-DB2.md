# 7 — Seat 4 position, D-B2 (narrow convening per P07C1B-R1-12)

2026-11-13. Saved by the orchestrator from the seat's report. Code and plan reading; corpus not re-read.

**Reading.** Insertion builds the ISM, the stage-1 (A) solve and the AX49 interim before the first IrSet. In Phase 08 binaural
and 09 stereoSpeakers that interim needs two seeded unit decays per emitter (F2, 2-seat4 L7–9; phase-08-3 scope 5, L38–42); omni
builds one. Cues: level and tone parity, the mode switch (AX49 "M"), the first IR per output.

**Ranking.** B2-a prefer; B2-d can live with; B2-b can live with from this seat (Seat 6's silent 3 is Seat 6's ground).

- **Now.** B2-a 0: first sound already the final level in every mode (AX47 (a), step 0); per-ear parity and AC6 from the first
  sample; E_b identical across modes and ears (AX44, phase-08-3 L36), the solve mode-independent. B2-d 1: same first sound; the
  key can omit `outputMode`, `hrtfId` (AX44), so SOFA import does not break it; a pinned artefact for a saving the modes do not
  grow. B2-b 1: each two-output mode gets a third first-IR state (silence then a fade from silence) that 08-3 / 09 per-ear / feed
  checks must cover.
- **Later.** B2-a 1: in binaural insertion also synthesises output-1 decays; unit-decay synthesis is 95.5 % of the non-diffuse
  restore (AX38 4c), so the binaural insertion stall could approach twice today's unit-decay share of 145–430 ms [Inferred], plus
  the HRIR early part [Inferred]; evidence at 08-4, which has no `insertMs` item (P07C1B-R1-11); undo = B2-b + one test. B2-d 2:
  saves only the stage-1 solve (ISM, interim synthesis stay synchronous, 2-seat5 L66) — in binaural the saved share shrinks while
  the unsaved part ≈ doubles [Inferred]; every E_model bump and Phase 12 default-scene change re-pins on three OSes; undo delete
  the artefact; evidence 08-4 `insertMs` per mode. B2-b 2: 08-3 / 09 must pin a fade from silence per ear and feed; real-time
  differs from offline for 0.15–0.43 s (longer under contention), so 08-3 / 09 offline/real-time parity must skip or align that
  window; an omni-like first IrSet risks the ±0.1 coherence check (08-3 AC5) for those samples; undo one test and a reading.

**Conditions.** **B2-a** (keeps later at 1): (i) insertion synthesises unit decays for every `outputIndex` the modes need (both
outputs, whatever the current mode), else the first omni→binaural switch waits for a synthesis or breaks M — if Seat 5 judges the
cost too high, the alternative goes to 07d with D-B4; (ii) phase-08-4 prints `insertMs` per mode (omni, binaural,
stereoSpeakers) and returns it to the board if binaural exceeds the host limit RQ5 finds; (iii) in binaural the first IrSet at
insertion carries the per-ear seeds and decorrelation — asserted in 08-3 beside the decider's `[pipeline]` test. **B2-d → 1/1:**
CI-generated (Seats 5, 2); key excludes mode and HRTF, includes fs and `tailSeed`; 08-4 reports the saving as a share of binaural
`insertMs`, dropped if below ≈ 10 % [Hyp threshold]. **B2-b → 1/1:** fade from silence tested per ear and feed in 08-3 / 09;
offline/real-time parity windows start after the first IrSet; Seat 6's veto stands regardless.

Evidence: F1, F2 (`src/sim/Engine.cpp` L465, L552–553; `src/sim/RealtimeEngine.cpp` L33, L67); AX44, AX49 M (phase-08-3 L36–42,
L67–70); 95.5 % (AX38 4c); what prepare builds (file 1 L68); binaural growth [Inferred] until 08-4. Hand-offs: Seat 5 (cost of
output-1 decays at insertion in omni; UI-thread limit); Seat 6 (silent veto); Seat 1 (gap audibility); decider (record
"insertion builds the unit decays for all outputs" in the D-B2 debt register beside D-B4's). Premortem: B2-a without (i) — insert
in omni, switch to binaural, the AX49 "never waits" test in 08-3 fails or the switch stalls; Seat 5's 08-3 CI notices first.
