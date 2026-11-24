SEAT 9 POSITION (round 2 of M3, phase 07c-2b; rates V6 candidates after K7, corpus c1b171fe)

The corpus was present this time. I re-read Kuttruff §5.6 (L2706–2724), §5.7 (L2727–2753) and Table 5.2 (L2782–2796). I did all the arithmetic below again myself. Measured values come from file 4.

**1. Reading**

Which s < 1, wet scene (V6), if any, should be the single 07c-2b scene? I also restate V1–V3′, confirm or correct the layout-5 Class lines, give item-9 labels and recheck the 0.43 ceiling.

Cues from my §4 that apply:
- D/R at the seat against the diffuse field.
- ITDG and early structure.
- The "decay right, room wrong" pattern (W2).
- Provenance (S8). Every candidate uses one s for all bands.

**Corpus facts that change my earlier premises**

- **Layout 5 is Kuttruff Table 5.2 case 5.** That case is a 10 × 20 × 30 m room with the long side wall (10 × 30 m) at α 1. Our xMin face is 30 × 10 m, so the geometry matches. Iteration gives 3.06 s against Eyring 2.99 s, which is **+2.3 %**: within one T30 JND (about 5 %) of the Eyring tail the engine renders.
  - My file-1 claim that the physical decay would be shorter was wrong. Correction (i) stands.
- **Layout 4 is case 4** (floor 20 × 30 m at α 1). Iteration gives 1.21 s against Eyring 1.38 s, which is **−12 %**, more than two JNDs.
  - The engine's layout-4 tail follows Eyring. On the corpus's diffuse-wall estimate it is about 14 % long [Inf; M: ratio carried over to α 0.01 plus air].
  - This affects S-A, S-B\* and every layout-4 candidate. Their labels should carry the case-4 line, as layout 5 carries case 5.
- **Real scenes from the code.** The valid fixtures in `tests/scenes/valid/` use s = 0.02–0.6. Every K7 candidate is at s ≥ 0.7, so s = 0.7 is the nearest to the fixtures and s = 0.9 the furthest.

**2. Ranking (V6 candidates first, then the earlier options)**

1. **layout5_s0.8/default: prefer.**
   - Both ends are seats (nearest faces 1.7 m and 2.0 m).
   - The early part is filled (−6.9 dB re direct).
   - The ITDG is a floor bounce at 1.6 ms, which is the realistic reflection at a seated listener.
   - The tail agrees with corpus case 5 within one JND.
2. **layout4_s0.7/both_wall: can live with.**
   - Its s is nearest the fixture range.
   - It is tail-dominated (share 0.692) and has the fullest early part (−1.3 dB).
   - Against it: the listener and one source are each 0.1 m from a wall, and the layout-4 tail is about 14 % long on case 4.
3. **layout5_s0.9/default: can live with.** Same as item 1, but its early part is 3.4 dB emptier (−10.3 dB), further from a real room.
4. **layout5_s0.8/emitter_wall and layout5_s0.9/emitter_wall: can live with.**
   - A source 0.1 m from a wall.
   - The heard gap between bursts 1 and 2 is 26 ms short of the tail T30, even under the max rule.
5. **layout4_s0.7/listener_wall: can live with.** It has the narrowest wet class (share 0.126, about 2.7 × S-A), and the listener 0.1 m from a wall is not a seat.
6. **Earlier options:**
   - **V1: can live with** (it was "prefer"). K7 shows S-B\* is the driest scene measured (share 0.032, below S-A's 0.046).
   - **V2, V3, V3′: can live with.**

**3–4. Tension now / later**

| option | now | later | why |
|---|---|---|---|
| L5 s0.8 default | 1 | 1 | No candidate is a measured room. Debts: M2 must take gaps from max(heard, tail) T30 (heard 2.556 s is below tail 2.617 s), and a B11 rebuild. Both cost minutes to a reseal. |
| L5 s0.9 default | 1 | 1 | As above. |
| L4 s0.7 both_wall | 1 | 1 | 0.1 m placements. If the tail target ever moves off Eyring for non-diffuse rooms, T30 shifts by up to about 12 % and the stimuli void. That costs minutes to reseal, provided the void rule (condition C-b) is in place. |
| L5 s0.8 / s0.9 emitter_wall | 1 | 1 | Only with condition C-a. Without it, later is 2: the heard gap fails M2 assertion 4. Acoustically, the leftover tail at the end of the gap is about −59.4 dB, so the issue is honesty of the rule, not audibility. |
| L4 s0.7 listener_wall | 1 | 1 | Meets my "s < 1 read before O10" condition, but only for the near-balanced class. |
| V1 | 1 | 1 | Unchanged. |
| V2 | 1 | 2 | Unchanged: O10 would be read only from a scene with an empty early part. |
| V3 | 1 | 2 | The V2 debt. K7 meets half my V3 condition: at default the max rule passes by +7 ms. My physical-decay premise fell (corpus case 5). |
| V3′ | 1 | 2 | As V3, with s = 1. |

Every V6 candidate repays the V2 debt, because O10 would be read from a scene with a filled early part. That is why each rates 1 later.

**5. Evidence**

**Diffuse-field expectations** (Eq. 5.44, which assumes Sabine's T; I recomputed both):
- Layout 4: A = 600 + 16 + 24 = 640 m², so r_c = 3.57 m and ᾱ = 616/2200 = 0.28.
- Layout 5: A = 300 + 19 + 24 = 343 m², so r_c = 2.61 m and ᾱ = 319/2200 = 0.145.
- The 24 m² air term is not checkable against the corpus. It moves results by about 0.16 dB.

**The sub-2.5 ms reflections are counted as direct** [Inf; H; geometry]. Each one falls inside the ±2.5 ms direct window, so it is counted in the direct sound, not the early part:
- Wall 0.1 m from a placement: path difference 0.2 m, arriving at 0.6 ms. First comb notch about 860 Hz.
- Layout-5 floor: path difference 0.54 m, arriving at 1.6 ms. First comb notch about 320 Hz.
- Comb depth with specular amplitude √(0.99·(1 − s)):

| s | comb peak / notch |
|---|---|
| 0.7 | +3.8 / −6.8 dB |
| 0.8 | +3.1 / −4.8 dB (floor), +3.2 / −5.2 dB (wall) |
| 0.9 | +2.3 / −3.1 dB (floor), +2.4 / −3.3 dB (wall) |

- A real flat hard surface scatters far less at low frequencies, so its comb would be deeper. This is per-band s [Hyp; researcher].

**The 0.43 ceiling** (corrected premise):
- Bound: t ≤ 0.1 + (26 − L_drop)/60 · T_tail,min.
- L_drop = 10·log10(1 + 10^(D/R/10)), using heard D/R at 1 kHz.
- Hold 0.1 s and SNR 46 dB were calibrated on S-A and are [Hyp] elsewhere.

| scene | estimate | 0.43·T30 | realised end (file 4) | what binds |
|---|---|---|---|---|
| L4 listener_wall | 0.58 s | 0.716 s | 0.449 s | the ≥ 20 dB assertion |
| L4 both_wall | 0.64 s | 0.590 s | 0.407 s | the assertion |
| L5 s0.8 default | 1.12 s | 1.099 s | 1.079 s (0.422 T) | the ceiling, roughly |
| L5 s0.9 default | 1.13 s | 1.099 s | 1.089 s (0.426 T) | the ceiling, roughly |
| L5 s0.8 emitter_wall | 1.20 s | 1.101 s | 0.960 s | the assertion |
| L5 s0.9 emitter_wall | 1.20 s | 1.101 s | 0.973 s | the assertion |

- The formula reproduces S-A (0.376 s) but overshoots by 0.12–0.24 s on every wet scene, and on S-B\* (0.561 against 0.353 s).
- So it is not a predictor. The measured ≥ 20 dB assertion governs.
- **Register correction:** the ceiling binds only on layout-5 default placements, not on both_wall. Rated 1/1 on each candidate.

**Layout-5 Class lines**

Class bands (my convention [Inf], not JNDs):
- direct-dominated: heard D/R ≥ +3 dB;
- near-balanced: between −3 and +3 dB;
- tail-dominated: ≤ −3 dB.

These are consistent with S-A (+13.1 dB), S-B\* (+1.7 dB) and S-W (−5.3 dB).

- **layout5_s1/default: CORRECT the decider's line.** Its heard D/R is −1.4 dB and its tail share 0.58, so "reverberant-dominated" overstates it. Use: "Class: near-balanced D/R (heard −1.4 dB, tail share 0.58), early part empty."
- **layout5_s1/emitter_wall: CONFIRM, with numbers added.** "Class: tail-dominated (heard −9.5 dB, tail share 0.87), early part empty."

**Item-9 labels**

Every label also carries the line "Stimulus scene, not a room prediction."

Every D/R line ends with this qualifier, with the layout's ᾱ:
> "Indicative only: ᾱ ≈ [0.28 | 0.145] and one face at α 1; Kuttruff §5.6–5.7: relations questionable when ᾱ is not small, severe deviation from diffuse conditions."

**L4 s0.7/listener_wall**
- **Label:** "Test room, specular-only early reflections (s 0.7, scattered early energy absent, AX21), listener 0.1 m from a wall; not a seat, not a validated preset"
- **Detail lines:**
  - 20 × 30 × 10 m; floor α 1, other faces 0.01; s 0.7 on every face, one value in all bands; tailSeed 12345. Listener at (10, 0.1, 1.7); emitters 20.1 m away.
  - D/R at 1 kHz −0.4 / −0.7 dB (heard +0.4 dB), against −15.0 dB at r/r_c 5.64 (Eq. 5.44, Sabine A ≈ 640 m²).
  - ITDG 0.6 ms (the wall behind the listener), counted as direct: comb with its first notch about 860 Hz, rendered at (1 − s).
  - Early part −2.1 dB re direct. Tail share 0.126.
  - Heard-IR T30 1.664 s; tail T30 1.254 / 1.274 s; Eyring 1.291 s.
  - Kuttruff Table 5.2 case 4: iteration 1.21 s against Eyring 1.38 s. The engine's tail follows Eyring.
- **Class:** near-balanced D/R (heard +0.4 dB, tail share 0.13), partial early part.

**L4 s0.7/both_wall**
- **Label:** "Tail-dominated stress placement, specular-only early reflections (s 0.7, AX21), listener and one source 0.1 m from walls; not a seat, not a validated preset"
- **Detail lines:**
  - Geometry as above. S0 at (7, 29.9, 2), 29.95 m away; S1 20.1 m away; direct-path difference 28.65 ms.
  - D/R −10.3 / −0.6 dB (heard −8.2 dB), against −18.5 / −15.0 dB at r/r_c 8.39 / 5.64.
  - ITDG 0.6 / 0.6 ms, counted as direct; combs at about 860 Hz.
  - Early part −1.3 dB. Tail share 0.692.
  - Heard T30 1.371 s; tail T30 1.313 / 1.274 s. Case-4 line as above.
- **Class:** tail-dominated (heard −8.2 dB, tail share 0.69), partial early part.

**L5 s0.8/default** (the s0.9 values follow in brackets)
- **Label:** "Test room with one absorbing side wall, specular-only early reflections (s 0.8 [0.9], AX21); not a validated preset"
- **Detail lines:**
  - x = 0 wall (30 × 10 m) α 1, others 0.01; s one value in all bands. Listener at (10, 8, 1.7); emitters 12.4 m away.
  - D/R −3.6 / −4.4 dB [−3.7 / −4.9], heard −1.4 [−1.6] dB, against −13.5 dB at r/r_c 4.74 (Sabine A ≈ 343 m²).
  - ITDG 1.6 ms (floor), counted as direct: comb with its first notch about 320 Hz, +3.1 / −4.8 dB [+2.3 / −3.1]. The ceiling follows at about 23.6 ms.
  - Early part −6.9 [−10.3] dB. Tail share 0.485 [0.545].
  - Heard-IR T30 2.556 s, below tail T30 2.617 / 2.600 s; Eyring 2.61 s.
  - Kuttruff Table 5.2 case 5: iteration 3.06 s against Eyring 2.99 s. The engine's tail follows Eyring.
  - Gaps are built from max(heard, tail) T30.
- **Class:** near-balanced D/R (heard −1.4 [−1.6] dB, tail share 0.49 [0.55]), partial early part.

**L5 s0.8/emitter_wall** (the s0.9 values follow in brackets)
- **Label:** "Tail-dominated stress placement, one absorbing side wall, source 0.1 m from a wall, specular-only early reflections (s 0.8 [0.9], AX21); not a validated preset"
- **Detail lines:**
  - S0 22.1 m away; direct-path difference 28.4 ms.
  - D/R −12.9 / −4.5 [−12.7 / −5.0] dB, heard −9.5 dB, against −18.6 / −13.5 dB at r/r_c 8.46 / 4.74.
  - ITDG 0.6 / 1.6 ms, counted as direct.
  - Early part −5.2 [−8.6] dB. Tail share 0.834 [0.852].
  - Heard T30 2.561 [2.560] s, below tail T30 2.582 / 2.600 s. Case-5 line as above.
- **Class:** tail-dominated (heard −9.5 dB, tail share 0.83 [0.85]), partial early part.

**6. Conditions**

- **C-a (emitter_wall, and both_wall's heard gaps):** build gaps as ⌈(max(heard, tail) T30·fs + Δ)/P⌉·P, so that M2 assertions 3–4 pass on heard quantities.
- **C-b (all options):** add to D-M3h 1's void list "any change to the tail's decay target (e.g. non-Eyring for non-diffuse rooms)".
- **C-c:** add the case-4 line to the S-A and S-B\* labels.
- **For V2, V3, V3′ to fall to 1 later:** unchanged from file 1. Read an s < 1 family before O10.

**7. Hand-offs**

- **Seat 1:** whether a V6 in the near-balanced class (L5 default) or the tail-dominated class (both_wall) is the harder signal. Under D-M3e, the class the V6 scene sits in decides which part of the scene space the non-detection covers.
- **Seat 2:** C2 fails on every wall placement; per-band s; C-b.
- **Seat 4:** a binaural head at 0.1 m (listener_wall, both_wall) has a head radius of about 0.09 m. D-M3h 2(a)'s bar should extend to y = 0.1.
- **Seat 7:** layout 5 takes 2.40 h against 1.76–1.84 h for the layout-4 wall placements.
- **Researcher:** ISO 17497-1 low-frequency scattering of flat hard surfaces; the band basis of the 46 dB SNR; the hold value.

**8. Premortem**

A wall placement is sealed, and its label omits that the 0.1-m reflection is only partly rendered. The non-detection is then read as covering real near-wall positions. A future per-band s model deepens the comb, and that voids the result. The builder sees it first, at the B11 or 08-3 rebuild.

Files: /home/user/makroof/docs/review/phase-07c-2b/{1-seat9,2-decider-m3,4-k7-candidates,5-decider-rebuttal-r2,6-interrogator-on-file5}.md; /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L2706–2796); /home/user/makroof/tests/scenes/valid/*.json (scattering values).
