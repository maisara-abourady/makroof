SEAT 4 POSITION

Corpus present (c1b171f). I re-read Kuttruff §2 (Eq. 2.50, Fig. 2.11) and §5.7, and phase-08-3.md L36 and L70 (AX44). Round 2: I answer only what K7 (file 4) changed. My conditions from 1-seat4 §6 (a) to (d) stand as adopted in D-M3h 2 and 2(c).

**1. Reading.** Rate V6 for the six candidates, re-state V1 to V3′, and rate layout 5 in item 15. Cues: missing or contradicted room cue; model violated (AX44 makes the tail isotropic with equal ear energies).

What K7 changed for my seat:
- **(K7-i) At s < 1 the early part is filled** (−1.3 to −10.3 dB re direct) and is rendered per image through the HRTF. On layout 5 it therefore carries the one-sided absorber up to t_mix,e (344 ms). The isotropic part is only the tail, but the tail is 0.485 to 0.852 of the heard energy at 1 kHz, and it is the part the ABX steps.
- **(K7-ii) The wall-behind reflection now exists** (ITDG 0.6 ms). Its specular energy factor is (1−α)(1−s) = 0.99 × 0.3 = 0.30, about −5.3 dB. This withdraws my 1-seat4 point that the near-wall cue is missing, for s < 1 only.
- **(K7-iii) Corpus support for the near-wall rise.** Kuttruff Eq. 2.50: mean-square pressure near a rigid wall is 1 + sin(2kx)/(2kx) times the far value. At x = 0.1 m that gives (my arithmetic, pure-tone values; octave noise is smoother) +2.9 dB at 125 Hz, +1.8 dB at 500 Hz and −0.6 dB at 1 kHz. Neither chain renders this rise.
  - With the wall behind, the error is the same in both ears and in omni, so the comparison between chains holds.
  - For the barred x = 0.1 placements, with ears at 0.0125 and 0.1875 m from the wall (head width `[Hyp]`), it gives an ILD of about +2.6 dB at 1 kHz in the real tail. The renderer gives 0 dB. D-M3h 2(a) now rests on the corpus, not only on my register.

**2. Ranking**

| option | label |
|---|---|
| V6 layout4_s0.7/both_wall | prefer |
| V6 layout4_s0.7/listener_wall | prefer |
| V2 | can live with |
| V6 layout5_s0.8/default (above s0.9: its early part carries more of the asymmetry, −6.9 against −10.3 dB) | can live with, only with layout 5 in item 15 under condition L5 |
| V6 layout5_s0.9/default | can live with, only with condition L5 |
| V6 layout5_s0.8/emitter_wall, layout5_s0.9/emitter_wall | can live with, only with condition L5; ranked last of the V6 set (tail 0.834 / 0.852 of heard energy) |
| V1, V3, V3′ | can live with (unchanged) |

**3. Tension now.** 0 for every option: the 07c-2b chain is omni and diotic.

**4. Tension later**

| option | rating | why |
|---|---|---|
| V6 both_wall | 1 | Wet (share 0.692), early part −1.3 dB, absorber on the floor (median plane, symmetric). 08-3 has an omni twin. Residuals: static, uncompensated, generic HRTF (B14). The head would touch the wall `[Hyp]` while the HRTF is free-field. The Eq. 2.50 rise is missing in both chains. B11 voids (D-M3h 1). |
| V6 listener_wall | 1 | As both_wall, but less wet (0.126, D/R +0.4 dB). |
| V6 layout5 default (s0.8, s0.9) | 2 → 1 under L5 | Lopsided early part, then a symmetric tail at t_mix,e: an interaural discontinuity the room does not have. Undo: one 08-3 session, about 2.4 h (K6), if an anisotropic tail is ever built. Evidence: 08-3 L4. |
| V6 layout5 emitter_wall (s0.8, s0.9) | 2 → 1 under L5 | As default, with the contradicted part at 83 to 85 % of the stimulus. |
| V1 | 2 (unchanged) | |
| V2 | 1 (unchanged) | |
| V3, V3′ | 2 (unchanged; worse than at s < 1) | K7: at s = 1 the early part is empty (−76.7 and −71.0 dB), so the asymmetry exists nowhere in the binaural IR. |

**Layout 5 in item 15:**
- **In, with label and print (condition L5): 0/1. I prefer this**, because it keeps the omni twin (26-seat4 (a)).
- **Kept out, when layout 5 is the only sealed scene (V6): 0/2.** The sealed scene never reaches binaural (my V1 reason), and the 08-3 scene stands alone.
- **Kept out, under V1 to V3′: 0/1.**

**5. Evidence**
- Eq. 2.50 and Fig. 2.11 (rise within about half a wavelength of a rigid wall): Kuttruff §2 L1546–1552. [Observed, corpus; arithmetic mine]
- One fully absorbing face gives a "severe deviation from diffuse conditions": Kuttruff §5.7 L2749. [Observed, corpus]
- How large the tail ILD is in a real room with one lateral absorber: `[Hyp]`. Researcher item (a) is still open.
- Tail level JND, binaural against diotic: researcher (c), still open.
- Tail ILD 0 by construction: phase-08-3 L36 and L70 (AX44). [Observed, plan]
- Shares, early part, ITDG, t_mix,e: file 4, Tables 1 and 3. [Observed, from the code]

**6. Conditions of acceptance**
- **L5 (layout 5 in item 15, 2 → 1):**
  - Label: "isotropic tail, anisotropic room: absorber at xMin, 10 m to the listener's left; tail ILD 0 by construction (AX44)".
  - Print per ear and per octave the energy of the early part [direct + 2.5 ms, t_mix,e) and of the tail [t_mix,e, end), with each segment's ILD. Assert the tail ILD = 0, and record the early-part ILD as the engine's own estimate of the room's asymmetry. A per-ear tail print alone would read 0.00 dB by construction and show nothing.
  - L4 and L5 are not judged on this scene. The result is never cited for lateralisation or envelopment.
  - It is voided if an anisotropic tail lands.
- **Wall-behind scenes (keeps them at 1):**
  - The label adds: "listener 0.1 m from a near-rigid wall behind; HRTF free-field; near-wall rise (Kuttruff Eq. 2.50) not rendered in either chain".
  - The early-part ILD is printed per ear (expected near 0; print only, no tolerance invented).
- **V3 and V3′:** unchanged (label, per-ear print, L4 and L5 not judged).

**7. Hand-offs**
- **Seat 2:** C2 fails on both wall scenes.
- **Seat 1:**
  - heard gaps 22 to 27 ms short of the heard T30 (both_wall);
  - both_wall's 28.65 ms lag between identical bursts (echo or comb, both chains);
  - whether a share of 0.126 meets "the hardest signal".
- **Seats 1 and 9:** the layout-5 M2 re-decision (the heard rule fails).
- **Seat 5:** the family count if 08-3 adds a scene.

**8. Premortem.** Layout5/emitter_wall is sealed and run binaurally without L5. 08-3 reports a threshold on a tail that is symmetric in a one-sided room. Maisara notices first, on L4, when the reverberation snaps to the centre after an early part that leaned right.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2b/4-k7-candidates.md
- /home/user/makroof/docs/review/phase-07c-2b/5-decider-rebuttal-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/6-interrogator-on-file5.md
- /home/user/makroof/docs/review/phase-07c-2b/1-seat4.md
- /home/user/makroof/docs/review/phase-07c-2/26-seat4.md
- /home/user/makroof/docs/phases/phase-08-3.md
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md
