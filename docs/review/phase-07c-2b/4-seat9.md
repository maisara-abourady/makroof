# 4-seat9: Seat 9, round 2 on M3 (V1-W cell, labels, tail spread) and M3-L4 (label)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (round 2, M3 and M3-L4). Read-only. The orchestrator saves this as /home/user/makroof/docs/review/phase-07c-2b/4-seat9.md.

The corpus is present now. I checked Kuttruff §5.6 Eqs. 5.42–5.45 and the §5.6 caveat on ᾱ (docs/corpus/kuttruff-room-acoustics.md L2698–2724). Every number below is my own arithmetic from file 29's code facts.

## R2-1. My V1-W cell: 1/1 confirmed, with one new condition. If the condition is not met, later becomes 2.

My V2 condition ("the label states 'no seat represented'") is met by the both_wall label. So the reading of 1/1 holds.

**New finding [Inf; H on the arithmetic].** On both_wall, the far emitter's tail is about 9.4 dB stronger than the near emitter's at the same listener. Basis:
- Both emitters are omni at gainDb 0 (from `medium_room.json`).
- Kuttruff Eq. 5.42 gives w_r = 4P/cA. The reverberant level depends only on P and A, not on where the source stands, and D/R follows Eq. 5.45.
- **Four placements behave.** listener_wall, listener_edge, listener_corner and emitter_wall follow 1/r² within 0.7 dB, and their emitter tails agree within 1.0 dB.
- **Two placements do not:**
  - both_wall L (29.95 m) reads −7.7 dB, where emitter_wall predicts +2.6 dB. That is 10.3 dB low.
  - both_corner L (37.10 m) reads +8.2 dB, where emitter_wall predicts +0.7 dB. That is 7.5 dB high.
- **Cross-check with tail share.** Equal directs plus a +9.4 dB L tail reproduces both_wall's tail share of 0.667 and its heard D/R of −5.3 dB exactly (my model gives 0.672 and −5.33 dB). The same method reproduces the shares of listener_edge (0.21), listener_corner (0.25) and both_corner (0.20).

**Why it matters.** S-W was picked as the most sensitive scene, and part of that sensitivity comes from this tail excess. With equal tails, both_wall's share would be about 0.29, so ΔG = 10·log10(1 + 0.29 × 0.2303) ≈ 0.28 dB, against 0.62 dB now. If the estimator gets corrected, M3-8 fires and S-W loses about half its ΔG.

**Condition (keeps later at 1).**
- Before the seal, the builder prints each emitter's tail energy at the listener for the chosen S-W.
- If the two differ by more than 1 dB (the jnd for G, Vorländer Table 6.1), it is reported under NFR-8 to Seat 2. The label then carries the tail-spread clause below.
- The item-13 record names the spread.

Without this condition, later is 2.

## R2-2. Item-9 labels: exact changes

The r_c and D/R figures recompute:
- A = 600 + 16 + about 24 (air) ≈ 640 m², so r_c = (640/16π)^½ = 3.57 m.
- 29.95 m gives 8.39 and −18.5 dB; 20.13 m gives 5.64 and −15.0 dB; 12.37 m gives 3.47 and −10.8 dB.
- The ceiling-image delay is (20.46 − 12.37)/343 = 23.6 ms.
- Eyring with ᾱ = 616/2200 gives 1.29 s.

**Both labels:**
1. Change "Kuttruff Eq. 5.44" to "Kuttruff Eqs. 5.44–5.45, r_c 3.57 m". The D/R value comes from Eq. 5.45.
2. Add "indicative only: ᾱ ≈ 0.28 is not small (Kuttruff §5.6)". The decider says the labels call these values indicative, but neither text does yet.

**S-W (both_wall):**
3. Change "r/r_c 8.4 / 5.6" to "8.39 / 5.64", which matches S-B\*'s 3.47.
4. Add the distances: "listener–emitter 29.95 / 20.13 m".
5. After "−5.3 dB heard", add "(emitter L's direct arrives 28.6 ms after R's and counts as reflected)".
6. Make "those wall reflections are absent" precise: "the reflections off those faces (about 0.6 ms; first comb notch near 0.86 kHz in a real room) are absent at s = 1 (AX21; Kuttruff Eq. 8.59)". The 0.86 kHz figure is [Inf].
7. Add "tail T30 {x} s" beside the heard T30.
8. Add the tail-spread clause if R2-1 triggers it.

**S-B\* (s0.7):**
9. Add "Floor α 1: no floor reflection, unlike a real floor." Everything else in this label is correct.

**Template for the S-W fallbacks:**

"layout4_s1/{p}: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Listener ({x,y,z}) m; emitters L ({…}), R ({…}); listener–emitter {r_L} / {r_R} m. {NEAR-FACE} D/R at 1 kHz {L} / {R} dB per emitter, {H} dB heard{HEARD}; diffuse field {dL} / {dR} dB at r/r_c {qL} / {qR} (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only, ᾱ ≈ 0.28 is not small). {SPREAD} Early part empty (AX21). Heard-IR T30 {h} s, tail T30 {t} s. Not a validated preset."

Fill rules:
- **NEAR-FACE, listener within 0.1 m of n faces:** "The reflections off the n faces at the listener are absent at s = 1 (AX21), so the direct sound's tone colour is not room-like and the scene represents no seat."
  - If one of those faces is the floor, add "(the floor reflection is absent at any s: α 1)".
- **NEAR-FACE, emitter only:** "…the reflections off the face at emitter L are absent at s = 1 (AX21), so its tone colour is not that of a source at a wall; the listener position is ordinary."
- **HEARD:** use it if the two direct arrivals differ by more than the AX13 direct window: " (emitter {X}'s direct arrives {Δt} ms later and counts as reflected)".
- **SPREAD:** use it if the emitter tails differ by more than 1 dB: "Emitter tails at the listener differ by {x} dB at equal source power; this is the engine, not room physics (Kuttruff Eq. 5.42); reported under NFR-8."

Prefilled values (my arithmetic, [Inf]):

| placement | faces near listener / emitter | r_L / r_R (m) | diffuse D/R (dB) | r/r_c | Δt direct (ms) | tail spread (dB) |
|---|---|---|---|---|---|---|
| listener_corner | listener: x = 0, y = 0, ceiling | 22.50 / 25.00 | −16.0 / −16.9 | 6.31 / 7.01 | 7.3 | 0.5 |
| listener_edge | listener: x = 0, y = 0 | 21.06 / 23.72 | −15.4 / −16.5 | 5.90 / 6.65 | 7.7 | 0.9 |
| both_corner | listener: x = 0, y = 0, floor; L: two walls, ceiling | 37.10 / 23.79 | −20.3 / −16.5 | 10.40 / 6.67 | 38.8 | **6.8, clause** |
| emitter_wall | L: y = 30 wall | 22.11 / 12.37 | −15.8 / −10.8 | 6.20 / 3.47 | 28.4 | 0.5 |
| listener_wall | listener: y = 0 | 20.13 / 20.13 | −15.0 / −15.0 | 5.64 / 5.64 | 0 | 1.0, print only |

My round 1 also noted that listener_corner may fail the M2 gap check (heard T30 1.288 s against a tail of about 1.27–1.30 s).

**S-B\* fallback, layout4_s0.9/default.** Use the S-B\* text with:
- s 0.9;
- D/R +6.0 / +5.6 dB per emitter, +6.6 dB heard;
- the same −10.8 dB diffuse value at 3.47;
- early part −9.5 dB re direct;
- first image (ceiling) 23.6 ms after the direct sound;
- Eyring 1.29 s;
- heard T30 1.925 s;
- the floor clause.

I confirm the filled text before the seal.

## M3-L4

**Label.** The geometry is Seat 2's. AX49's gated geometry implies a 100 m cube, V = 10⁶ m³. At T60 8 s, Eq. 5.44's approximate form gives r_c ≈ 19.9 m [Inf; depends on Seat 2's choice].

The label must contain:
- "synthetic {dims}, V {x} m³, T60_max 8 s (longest band, air absorption included), per-band T60 printed: a stress geometry, not a room prediction or a validated preset";
- what "fully wet" contains (is the direct sound in or out?);
- no "hall", "church", "cathedral" or "occupied".

**Provenance.**
- A is "AX49 provisional tail (`Engine::assembleProvisional`, validation-only flag)".
- B is "full engine tail".
- Use "exact" only with a gloss, "exact = full synthesis, not a measurement".
- Record tailSeed and the hashes. Neither A nor B is measured.

**Ratings (narrow):**
- **L4-A, *prefer*, 0/0.** It tests the cut that AX49's Reversal names ("the L4 ABX detects the cut"), and it is the worst case.
- **L4-B, *can live with*, 0/1.** It matches the product's path, but a null on it does not test the cut that AX49's Reversal names.
- Detection design belongs to Seat 1.

## Hand-offs
- **Seat 2 and the builder:** the per-emitter tail spread on both_wall and both_corner. Is it an AX40 estimator effect at near-face emitter and listener pairs? It is an NFR-8 candidate.
- **Seat 1:** S-W's ΔG of about 0.28 dB if the tails are equalised.
- **Researcher:** RQ-M3-3 is still open.

## Premortem
Suppose S-W is sealed without checking the tail spread. A later estimator fix then makes the 0.667 share fall to about 0.29. The 07c-2b null turns out to have been earned on an engine artefact, and the 08-3 rebuild is the first place that shows it.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2/29-k4-candidates.md
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md
- /home/user/makroof/tests/scenes/valid/medium_room.json
- /home/user/makroof/docs/BUILD_PLAN.md

