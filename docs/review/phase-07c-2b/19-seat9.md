# 19-seat9: Seat 9 on the L4 null wording

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (L4 null wording, phase 07c-2b; read-only; to be saved as /home/user/makroof/docs/review/phase-07c-2b/19-seat9.md)

**1. Reading.** You asked whether the L4 null should carry the 4 kHz depth sentence, and in what form. You also asked for room-side ratings of C, E and "B as a second bright arm". My cues: §17 "confusing the record's definition with the physics" (a "40 dB down" with no reference point), and §4/§10 "never extrapolate a rule from one room class to another" (the 4 kHz depth is a large-volume, air-absorption property).

**Room-side finding (corpus).** The 4 kHz depth comes from the scene, and mostly from its air.
- Kuttruff Table 6.1 gives m = 6.84·10⁻³ m⁻¹ at 4 kHz, 50 % RH. So 4mV = 27,360 m².
- The surface term (α held at its 1 kHz value) is 15,805 m² (file 14).
- Eyring gives 0.161·10⁶ / 43,165 = 3.73 s, which matches the printed 3.731 s. At 2 kHz: 4mV = 9,120 m², so 0.161·10⁶ / 24,925 = 6.46 s, which matches 6.457 s.
- Air therefore makes up 63 % of A at 4 kHz.
- In a 100 m³ room, 4mV at 4 kHz is 2.7 m², which is negligible. A hard small room can have a 4 kHz T60 about equal to its mid T60, and then its 4 kHz cut is as exposed as its 1 kHz cut.
- So the null's exclusion of 4 kHz is specific to this scene and must say why.

**Is "40 dB down at L_f" right?** Yes, but only as the decay from the band's own tail onset.
- 60·(L_f − t_mix,e)/T60 = 60·2.496/3.731 = 40.14 dB (Kuttruff §3.8 definition of T).
- It is a nominal figure, computed from the engine's T60. It is not a level relative to the hold or to other bands.
- As worded, a reader would take "40 dB down" to mean below the chord or below 125 Hz. That is the §17 error.

**Should the null carry −36.5 dB re 125 Hz?** No.
- It is a chord × room level in the cut window, so it describes the stimulus, not the room.
- It is already printed in the manifest, and that is where it belongs.
- If Seat 1 wants it in the null for audibility reasons (its call), it must read "−36.5 dB re 125 Hz in the cut window under this chord".

**Second error in the wording.** "T60 8 s" is wrong over the claimed 63 Hz–2 kHz: 2 kHz is 6.46 s.

**Null wording I require:**
> "not detected in 16 trials by one listener (power 0.63); ax49_l4_cube, T60 8.0 s at 63 Hz–1 kHz and 6.5 s at 2 kHz, held chord, omni diotic; cut exposed at 63 Hz–2 kHz; no claim at 4 kHz and above, where this scene's tail (T60 3.7 s, mostly air absorption in 10⁶ m³) has by L_f decayed 40 dB from its own onset, against 19 dB at 63 Hz–1 kHz."

For the Decided-for-Maisara line, I accept the interrogator's restatement (file 15) with the cause added: "…by the cut, that band's tail has decayed 40 dB from its onset, because air absorption shortens this large scene's 4 kHz decay to 3.7 s." Drop "whatever chord is played". That is a claim about detection, which is Seat 1's [Hyp].

**2. Ranking.**
1. B-second: *prefer*, by a small margin. It covers the decay the label prints up to 4 kHz.
2. E: *can live with*.
3. C: *can live with*.

From the room side E and C are the same. Assert (b) measures the stimulus, not the room.

**3. Tension now.**
- C: 1 as worded (no reference for "40 dB down"; "T60 8 s" also covers 2 kHz). 0 with my wording.
- E: 1 as worded, 0 with my wording.
- B-second: 0.

**4. Tension later.**
- **C and E: 1.** The null risks being read as covering any room. It does not transfer to scenes where the 4 kHz T60 is close to the mid T60 (small or hard rooms, where air is negligible). Undoing it means another sitting on such a scene. The evidence would come at the 07d AX49 review, or wherever the provisional tail ships into small scenes. With no cause sentence, I rate this 2.
- **B-second: 1.** It closes the chord gap, not the scene gap: the bright arm still tests 4 kHz at a 40 dB depth in this cube. Same debt, same evidence point.

**5. Evidence.**
- Kuttruff Table 6.1 (corpus L2827–2834), the Eyring form via `src/sim/tail/Decay.h` L6 (from the code, file 14), and §3.8 for the 60 dB definition (file 15).
- File 18 for the T60s, the depths and the cut-window levels.
- My arithmetic is shown above.
- [Inf], not load-bearing: the 2.29 dB (b) margin sits on 125 Hz. At a few chord partials per octave, that level depends on one tail realisation. It is pinned by determinism, not by room physics. Seat 3 already flags it.

**6. Conditions of acceptance.**
- For C or E to go from 1/2 to 0/1: use my wording, which gives the scene's per-band T60 over the claimed bands, "decayed 40 dB from its own onset", and the air-absorption cause.
- Do not add the absolute −36.5 dB unless it is tagged "under this chord".

**7. Hand-offs.**
- Seat 1: whether −36.5 dB re 125 Hz belongs in the null for audibility reasons, and the power figure.
- Seat 7: B-second's 0.75 h.
- Seat 2: whether any shipped scene class (small, hard rooms) gets the provisional tail with a flat HF decay. That decides when the later-1 debt comes due.

**8. Premortem.** The null is sealed reading "4 kHz is 40 dB down" with no cause. 07d then cites it for a small tiled-room preset whose 4 kHz cut is as exposed as its 1 kHz cut. The first to notice is Seat 1 at the 07d AX49 review, or a beta producer hearing a bright tail truncate.
