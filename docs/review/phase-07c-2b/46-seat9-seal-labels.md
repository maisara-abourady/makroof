# 46: Seat 9 confirms the filled ABX labels before the seal

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (pre-seal label confirmation, phase-07c-2b ABX; read-only; for the orchestrator to save as /home/user/makroof/docs/review/phase-07c-2b/46-seat9-seal-labels.md)

**1. Reading.** The question: do the three filled labels, as the kit wrote them, match my texts, the run sheet and the manifests' own values? The trigger is my §17 rule against confusing the record's definition with the physics. I recomputed each number (Kuttruff Eqs. 5.44–5.45: D/R = 20·log₁₀(r_c/r); the 0.2 m path difference over c gives the delay).

**2. Verdicts**

**S-W (`layout4_s1/both_wall`): CONFIRMED.**
- The text is verbatim run sheet §1 (decider file 9 §6).
- Every number matches the manifest:
  - Distances 29.952 / 20.127 m.
  - D/R at 1 kHz −7.66 / +5.19 dB per emitter, −5.26 dB heard.
  - Diffuse field −18.47 / −15.02 dB at r/r_c 8.39 / 5.64, with r_c 3.57 m. A = 616 + 4mV ≈ 642 m², and ᾱ = 616/2200 = 0.28.
  - Delay 0.583 ms; first notch 1/(2τ) = 857 Hz. L's direct sound arrives 9.825/343 = 28.6 ms after R's.
  - Tail onsets t_mix,e 0.165 / 0.380 s. Equal-window L − R −0.05 / −0.03 dB; own-onset +9.39 dB.
  - Tail share 0.667. Heard-IR T30 1.370 s; tail T30 1.313 / 1.274 s.
- The manifest prints r_over_rc 7.71 / 5.18 from the kit's 0.057 form. That difference is the documented `r_c_forms` split, not an error.

**S-B\* (`layout4_s0.7/default`): CONFIRMED, with one missing clause.**
- My SPREAD clause is verbatim 14-seat9 §2.
- Every number matches the manifest:
  - D/R +1.48 / +1.30 dB per emitter, +1.72 dB heard.
  - Diffuse field −10.80 dB at r/r_c 12.373/3.57 = 3.47.
  - Spread −1.234 dB from the common onset; −0.21 / −0.73 dB in the equal windows; common onset 0.380 s.
  - Heard-IR T30 1.831 s; tail T30 1.254 / 1.274 s; Eyring T60 1.29 s.
- The [0.380, 0.45) s print I asked for reads −1.11 dB. That confirms my [Inf] that the spread sits at the onset.
- Two figures are not in the manifest, so I could not check them against it: "first image 23.6 ms" and "−3.8 dB re direct". They stand on decider file 6.
- **Missing clause.** The label says "the step at t_mix,e is printed". The print (`tmix_step_db`; positive means the tail onset is louder, from the code, abx_kit.py L369–372) reads +26.8 / +27.4 dB at 1 kHz and +30.8 / +31.3 dB broadband (L / R).
  - So the reverberant field enters 380 ms after the direct sound, about 27 dB above the specular early part just before it.
  - "Early part present" without that size misdescribes this scene's early-to-late structure.
  - **Exact replacement:** "the tail enters at t_mix,e 0.380 s about 27 dB above the specular early part just before it at 1 kHz (31 dB broadband; per band printed)".
  - This changes the label text only, not the stimuli.
  - If the decider will not reopen decided text, put the same sentence in the S-B\* record wording instead.
  - Without it I rate S-B\* 1/1. With it, 0/1.

**L4 (`ax49_l4_cube`): CONFIRMED.**
- The text is verbatim 14-seat9 §3, with {printed} = "−8.5" (−8.459 dB) and {seed} = 12345, the run's tailSeed.
- The fill figures match:
  - A 18,209 m²; r_c 19.03 m; r 40.31 m; r/r_c 2.118.
  - Diffuse D/R −6.52 dB; ᾱ 0.2319, scene and back-solved identical (difference 0 < 0.005, so a single print is correct).
  - L_f / L_p 3.61353 / 3.71353 s.
  - T60 8.0 s at 63 Hz–1 kHz; 6.457 s at 2 kHz; 3.731 s at 4 kHz.
- The `pass_rule.null` string is my 19-seat9 wording verbatim (depth 40.14 dB at 4 kHz against 18.72 dB at 63 Hz–1 kHz).
- Heard D/R is 2 dB below the diffuse figure. The label already marks the diffuse figure "indicative only", so this needs no change.

**3. Does M3-H change the S-W or S-B\* labels? No. Both stand as decided.**
- **S-B\*: "reported under NFR-8" stands.** File 43 Item A1 scope 1(c) takes this spread as finding (c), "not attributed (the room is not diffuse)". That is exactly the label's claim. The 07e/07e-b routing is in run sheet §1 (tail-spread print) and does not need to be in the label.
- **S-W: "This is engine behaviour, not room geometry … changes with the t_mix,e rule (M3-8)" stands.**
  - Both candidate causes for (b) in file 43 scope 2 are engine rules: AX22's realised-k fallback, which sets the handover, and the t_mix,e rule.
  - The equal-time decays agree within 0.05 dB, so the room-side level is equal.
  - M3-8 covers any `src/sim` change that alters the IR.

**4. Evidence**
- From the manifests: `scene.*`, `tail_spread`, `emitters[*].tmix_step_db`, heard `tail_share_of_heard`, `label_fill`.
- Kuttruff Eqs. 5.42, 5.44–5.45, 7.6, §5.6, as cited in 14-seat9 and 19-seat9. The corpus was not re-opened this round; the arithmetic above was redone by hand.

**5. Hand-offs**
- **Seat 1:** S-B\*'s heard tail share at 1 kHz is 0.032. The 3 dB anchor moves heard G by −0.07 dB and C80 by +1.40 dB. This bears on the {printed} tail share in the S-B\* record wording and on what its null covers. That call is yours, and it is still an open S-B\* seal precondition.

**6. Premortem.** If S-B\* is sealed without the step size, its null would later be cited as covering a room with a normal early part. The first to notice would be the 08-3 rebuild, or Seat 2 in 07e when it prints the AX21 step per placement.
