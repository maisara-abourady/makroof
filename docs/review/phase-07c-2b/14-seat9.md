# 14-seat9: Seat 9 on the S-B* SPREAD clause and the L4 label figures

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (round 4: M3-1 (e), the S-B* SPREAD call; M3-L4 (iv), the L4 label figures). Read-only. To be saved as /home/user/makroof/docs/review/phase-07c-2b/14-seat9.md.

**1. Reading.** (1) Does the S-B* label (`layout4_s0.7/default`) carry a SPREAD clause, given the 1 dB print threshold? (2) Does the interrogator's C7 correct my L4 figures? Cues: §4 coefficient provenance and §17 "confusing the record's definition with the physics" (both questions); §6 S2, where all absorption sits on one surface so the field is not diffuse (question 1).

**2. Answer (1): S-B* gets a clause in a corrected level form.**
- **Why a clause is needed.** C-b fires if either measure is over 1 dB. Measure (i), integrated from each emitter's own t_mix,e, gives −1.23 dB. The two onsets are equal (0.380 / 0.380 s), so this is a level spread, not an onset spread. Leaving the clause out would hold S-B* to a weaker rule than the S-W fallbacks, and its null would rest on a spread the label never mentions. For comparison, S-A gave −0.94 dB, under the threshold.
- **Why not my R2-2 text as written.** That text says "this is the engine, not room physics". I can't claim that at 1.2 dB. This room has α 1 on the floor, 0.01 elsewhere, and scattering 0.7, so it is not diffuse (ᾱ ≈ 0.28, Kuttruff §5.6). Eq. 5.42 is only indicative here, and a real room of this kind can give reverberant levels that differ by position. The +9.4 dB on S-W is attributable because it comes from an onset rule. This spread is not.
- **Where the spread sits [Inf].** The integrated −1.23 dB is larger in magnitude than both windows (−0.21 and −0.73 dB). Most of the difference must therefore lie outside them, most likely in [0.380, 0.45) s. The equal-window spread also widens over time, which fits L's shorter tail T30 (1.254 against 1.274 s).
- **Builder request (print only, not a gate).** Add the window [0.380, 0.45) s to the S-B* seal print, so the record shows where the spread sits.
- **Exact clause.** It goes after "tail T30 1.254 / 1.274 s." and before "Not a validated preset.":

> "At equal source power the emitter tails at the listener differ at 1 kHz by −1.2 dB (L − R), integrated from their common onset t_mix,e 0.380 s; −0.2 / −0.7 dB in the equal windows [0.45, 0.65) / [0.8, 1.0) s. A diffuse room gives equal reverberant levels (Kuttruff Eq. 5.42), but with all absorption on the floor this room is not diffuse (§5.6), so the spread is not attributed to engine or room; reported under NFR-8."

- **Routing.** The measurement goes to Seat 2 as a third, lower-priority NFR-8 candidate, through whatever home the corner re-ruling settles.
- **Ratings.** Gated S-B* with this clause: 1/1, unchanged. Without any clause: 1/2, for the same reason I gave on S-W's file 6 handling (an unlabelled spread above the print threshold).
- **Gate released.** With this text adopted, my (e) answer is given and the S-B* seal may proceed.

**3. Answer (2): I accept C7.**
- **My error.** I worked out A = 0.161V/T as if the engine's T60 were Sabine's. The engine uses Eyring: from the code, `src/sim/tail/Decay.h` L6 gives T60 = 0.161V/(−S ln(1−ᾱ) + 4mV). That made my ᾱ 0.34, which is an upper bound, and I then printed it as if it were the value.
- **Redone, Kuttruff Eqs. 5.24–5.25 and 5.44, Table 6.1 (m 1.08·10⁻³ m⁻¹, 50 % RH):**
  - 4mV = 4,320 m²;
  - −S ln(1−ᾱ) = 20,125 − 4,320 = 15,805, so ᾱ = 0.232;
  - A = 60,000 × 0.232 + 4,320 = 18,215 m²;
  - r_c = (18,215/16π)^½ = 19.0 m;
  - r/r_c = 40.31/19.04 = 2.12;
  - diffuse D/R = 20·log₁₀(19.04/40.31) = −6.5 dB.
  - Spread of the inputs: T60 ± 0.1 s moves D/R by about ±0.05 dB, and 40–70 % RH also moves it by under 0.05 dB. Both are below the label's precision.
- **Fill rule.** The builder fills ᾱ from the scene's 1 kHz α and m from the engine's own air table (`bandsAirAttenuationDbPerMetre`), not from Table 6.1. If the scene's α differs from the value back-solved from the printed T60 by more than 0.005, print both (print only).
- **Final L4 label:**

> "ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10⁶ m³, every face the same α per band, scattering 0.3. Listener (50, 30, 1.7) m; emitters (45, 70, 2) and (55, 70, 2) m, each 40.3 m from the listener. T60 8.0 ± 0.1 s from 63 Hz to 1 kHz as printed by the engine (Eyring, T60_max 8 s, air absorption included), shorter above 1 kHz where α is held at its 1 kHz value; per-band T60 printed. D/R at 1 kHz {printed} dB heard, against about −6.5 dB in a diffuse field at r/r_c 2.1 (r_c ≈ 19 m from A = Σ S·α + 4mV ≈ 18,200 m² at 1 kHz, the label form; Kuttruff Eqs. 5.24–5.25, 5.44–5.45, Table 6.1; indicative only: ᾱ ≈ 0.23 at 1 kHz is not small, §5.6). A stress geometry for AX49's provisional tail, not a room prediction or a validated preset. A = AX49 provisional tail (Engine::assembleProvisional, validation-only flag --ax49-provisional), faded over [L_f, L_p) = [3.6135, 3.7135) s; B = full engine tail ('exact' = full synthesis, not a measurement); one tailSeed {seed} for A and B. Fully wet: the whole rendered IR (direct, early part and tail), no dry path."

- **Ratings.** L4-A stays 0/0. I confirm the filled text once {printed} and {seed} are in.

**4. Evidence.**
- From file 5: L23 (−1.23 dB) and the kit build log facts given in the brief (−0.21 / −0.73 dB, onsets 0.380 / 0.380 s).
- Corpus (Kuttruff): Eq. 5.42 (L2698), the §5.6 caveat (L2724), Table 6.1 (L2827–2834).
- From the code: `Decay.h` L6 and L17.
- [Inf] marks the reading of where the spread sits and the claim that it can't be attributed to engine or room.

**5. Hand-offs.**
- Seat 2: the s0.7 level spread, as an NFR-8 candidate.
- Seat 1: whether 1.2 dB per emitter changes what the S-B* null covers. This is my §8 question restated at the smaller size.

**6. Premortem.** Suppose S-B* is sealed without the clause and Seat 2 later traces the 1.2 dB to the engine. Its null would then be on record as a room-class result that rests on an artefact nobody wrote down. The first to notice would be the 08-3 rebuild, when the spread moves.
