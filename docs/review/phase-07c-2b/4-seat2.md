# 4-seat2: Seat 2, round 2 on M3 (V1-W cell) and M3-L4 (scene)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION, round 2 on M3 (V1-W cell) and M3-L4 (phase 07c-2b). The corpus is present at `docs/corpus/`. This seat is read-only, so it has not saved `docs/review/phase-07c-2b/4-seat2.md`; the orchestrator saves this text verbatim.

## R2: V1-W cell, confirmed at 1/1

I checked the M3-4 label text against my round-1 conditions (`1-seat2.md` §6).

- **S-W label: met.** It has all three elements I asked for:
  - the position: "Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall";
  - the absent reflection: "those wall reflections are absent at s = 1 (AX21)";
  - the tone colour: "so the direct sound's tone colour is not room-like".
  - Item 13's example line scopes a null to that class.
- **S-B\* label: met.** It reads "Early part present but specular-only (partial AX21)". The dip print in M3-1 uses my windows exactly: [t_mix,e − 20 ms, t_mix,e − 2.5 ms) against [t_mix,e + 2.5 ms, t_mix,e + 20 ms), per band and per emitter.
- **Clause text: met.** The file-34 clause and the M3-8 trigger carry my wording. "Pass every seal gate again" is an addition I accept.
- **One condition to keep 1/1 if S-W falls back.** The fallback label must name every face whose reflection is absent. listener_corner loses three reflections and listener_edge loses two. "Follows the both_wall template" does not guarantee this unless Seat 9 checks it in the filled text.

## M3-L4

**1. Reading.** The question is which stimulus design tests AX49's truncation, and which scene gives T60 8 s with L_p < L. Cues from my persona: §4 cue 1 (V and T), cue 5 (a decay departure), §2 criterion 2 (decay where it is audible) and criterion 5 (honesty of output), and W4.

**2. Ranking**
1. **L4-A: prefer**, on the scene under (S) below.
2. **L4-B: can live with only as an extra record next to L4-A.** As the test of AX49 it is 2/2.

**3–4. Tension now / later**

**L4-A: 1 / 1.**
- The physical departure that AX49 adds is the end of the energy decay curve (EDC) at L_p. On a chord release, the provisional's decay falls to zero over the 0.1 s fade. It falls from about 19–24 dB below the tail onset [Inferred, from the AX49 L_f rule]. The exact tail goes on to L = 12 s.
- L4-A is the only design whose stimulus contains this cut. AX49's Reversal reads "the L4 ABX detects the cut", so only L4-A can trigger it.
- The steady-state difference is ≤ 0.06 dB (AX49 K17′). The cut is therefore the cue being tested.
- Later: a detection sends AX49 back to the board as designed. That costs a reopening, not a rewrite.

**L4-B: 2 / 2.**
- Under either reading of "≤ L_f", the cut is never played.
  - If time is counted from the release, the exact IR takes over before the provisional runs out.
  - If it is counted from the start of the stimulus and the chord is held longer than L_f, the release plays the exact tail.
  - Both crossfade states read one input history (K23). After the handover, the output equals the exact convolution of the whole input.
- L4-B therefore tests only the AQ4 handover, which is two near-identical IRs (same seed and stream up to L_f).
- A non-detection would be read as "the truncation is inaudible" without the truncation ever being presented. That fails criterion 5.
- Later: AX49's reversal trigger could no longer be read. Meanwhile, shipped loads can play the provisional for up to 9.51 s (Windows, 8 instances, AX49 trigger, CI run 43242209571), long enough for a release to hit the cut.

**Gap neither option covers [Inferred from K23].** In shipping, a handover that lands after a release, between L_p and L, brings the cut tail back. The output reads as a gap, then the tail swelling back in over 30 ms. This may be more audible than the cut itself. Seats 1 and 3 should judge whether it needs a third stimulus.

## (S) The scene: AX49's gated geometry, in the form the kit can build

The geometry comes from the code: record (h), `cubeT60(8.0)` in `tests/unit/test_diffuse_records.cpp` L2175–2187.

- **Room:** a 100 × 100 × 100 m box, 10⁶ m³, S = 6·10⁴ m².
- **Scattering:** 0.3 on all six faces.
- **Listener:** (50, 30, 1.7).
- **Emitters:** (45, 70, 2) and (55, 70, 2). Both are 40.31 m away, so t_dir = 0.1175 s on both. This matches "t_dir 0.118 s".
- **Absorption:** uniform α = 1 − e^(−0.161·10⁶/(6·10⁴·8)) = 0.2849 in every band. This gives an Eyring T60 of 8 s without air. I recomputed it.

**Why I prefer a material variant (S′) over the verbatim box.**
- With air absorption, the verbatim box's T60_max sits at 63 Hz. The mid band is shorter. These are Eyring values, T = 0.161V/(20125 + 4mV), with m from Kuttruff Table 6.1 at 50 % RH:

  | band | T60 |
  |---|---|
  | 500 Hz | 7.11 s |
  | 1 kHz | 6.59 s |
  | 2 kHz | 5.51 s |
  | 4 kHz | 3.39 s |
  | 8 kHz | 1.37 s |

- So the guaranteed 18.7 dB depth binds only at 63 Hz, where a chord has the least energy. At 1 kHz the cut sits at about 60·2.6/6.59 ≈ 24 dB [Inferred]. The verbatim box biases L4 toward a non-detection.
- **(S′)** keeps the same geometry, scattering and positions. Only α changes per band, so that the engine's printed T60 is 8.0 s (±0.1 s) in every band from 63 Hz to 1 kHz. Above 1 kHz, α stays at the 1 kHz value, which leaves those bands shorter because of air.
  - Starting values from Table 6.1: α(1 kHz) ≈ 0.232 and α(500 Hz) ≈ 0.254. For 63–250 Hz, iterate on the engine's printed values. The AX4 humidity in the engine may differ from 50 %.
  - L_f and L_p do not change: t_mix,e,max and T60_max are the same. The scene stays inside AX49's rated corner, and the mid band is cut at about 18.7 dB.
- **Ratings:** verbatim box 1/2, rising to 1/1 if the per-band depth at L_p is printed and any null is scoped to "cut at 63 Hz depth only". (S′) is 1/1.

**Seal asserts on either scene:**
- `ProvisionalTiming.provisional == true`;
- L_p < L, with L at the 12 s cap (1.5·8);
- L_p ≤ 3.82 s;
- decay ≥ 18.7 dB from t_mix,e,max to L_f in every band.

**Prints:** T60 per band, the depth at L_f and at L_p per band, and t_mix,e,max. The release must run into ≥ L = 12 s of free decay.

**5. Evidence**
- From the code: Engine.h L146–160 and L293–298; test_diffuse_records.cpp L2175–2187.
- AX49 (BUILD_PLAN L172): K17′ and K23.
- Kuttruff Table 6.1 (air attenuation m); Eyring with 4mV [Inferred].
- The audibility of the cut, and of the gap-and-return, is [Hyp] for Seat 1.

**6. Conditions**
- **L4-B (2 → 1):** keep it only as a record next to L4-A, scoped as "handover only; cut not presented".
- **Verbatim box (later 2 → 1):** print the per-band depth and scope any null, or use (S′).

**7. Hand-offs**
- **Seat 1:** audibility, the chord's register relative to 63 Hz, and the gap-and-return stimulus.
- **Seat 3:** the gap-and-return artefact, and the normalisation difference between provisional and exact.
- **Seat 9:** the label. It must state 10⁶ m³, not a product room class, no "hall", and "not a validated preset".
- **Seat 7:** a stimulus of at least the chord plus 12 s.

**8. Premortem.** If L4-B is run, or the verbatim box is used unscoped, a null clears AX49's cut. The first to hear it is a producer who loads a large project, presses play and releases a chord before the handover.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat2.md
- /home/user/makroof/docs/BUILD_PLAN.md (L172)
- /home/user/makroof/src/sim/Engine.h
- /home/user/makroof/tests/unit/test_diffuse_records.cpp
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Table 6.1)
