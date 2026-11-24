# 38: Seat 9 accepts the near-corner tracer; merged (a) text without (a1) (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (follow-up on 36-seat2 §2; read-only, no files changed; to be saved as /home/user/makroof/docs/review/phase-07c-2b/38-seat9.md)

**1. Reading.** The question is whether Seat 2's tracer, run at (a)'s exact geometry with r_d 0.05 m and 0.025 m, can serve as (a)'s reference, and how its text merges with my (a1)/(a2) text. Cues: S8 (a known bias offered as an explanation) and S2 (non-diffuse room).

**2. Ranking.**
- **Prefer:** Seat 2's near-corner tracer as the only reference for (a), merged as below.
- **Can live with:** Seat 2's text exactly as written in 36-seat2 §2.
- **Cannot live with:** keeping my (a1), which uses Eq. 5.42 L − R = 0 dB as a verdict reference.

**Yes, I accept the tracer, and I withdraw part of my file-36 position.** My argument against the tracer was a geometric low bias: a counting sphere that crosses a face catches fewer particles than its stated volume implies. That bias does not arise here. From the code (tracer.py L129, L150–153), r_d is a free argument and 0.5 m is only the default (L42). A sphere of 0.05 m or 0.025 m centred 0.1 m from each face lies wholly inside the room. Two residual effects remain:
- averaging over the sphere where the energy density changes with position;
- the scatter of a sparse count.

The two-radius agreement test catches the first and the k ≥ 684 gate catches the second. The 05h W1 run (file 14 L31–39) is AX44's own pre-registered near-corner reference. I also withdraw (a1) as a reference: layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4), so Eq. 5.42 at 0.1 m from the faces was my `[Hyp]`, and it is now unnecessary.

**One exact merged text (07e scope 3 and 07e-b scope 1 (a)):**

> "The reference for (a) is the seeded tracer at (a)'s exact geometry, with its counting sphere wholly inside the room: r_d 0.05 m and 0.025 m (below the listener's 0.1 m clearance), as AX44's near-corner reference (05h file 14). A band counts only where both radii are gated (k ≥ 684) and agree within their combined 3σ. If that costs too much, (a) alone may use a 1 dB threshold while the reference SE is ≤ 0.5 dB. Verdict per band, 63 Hz–8 kHz: the engine's L − R and each emitter's late level against the tracer's. A difference above 1 dB in any counted band is a breach, with its cause. Eq. 5.42 is not a reference for (a) (non-diffuse, Kuttruff §5.7, Table 5.2 case 4). The engine is never its own reference. Required prints, never references: (i) the listener moved along its corner diagonal to 0.75 m from each of its three faces (outside AX44's 0.70 m both-near flag), L and R unchanged, tracer at r_d 0.5 m, which separates the source-side cause from the AX44 both-near branch; (ii) the engine's E_fwd and E_rev, uncapped, at w = 1 and w = 0, which separates the cap from w; and for each emitter in each case, w, the both-near and capped flags, and U. The diffuse control stays (c)'s tool only; an emitter swap is not a reference. The flatness claim (29-seat9 §5) is printed as support, never as the verdict."

My file-36 text on "not decidable" and Seat 2's gate text merge as: "never opens a gate; first the named print (more particles, B11 doubling); then a board ruling, which records (a) under AX44 only with my five conditions (36-seat9 §2(3))."

**3. Tension now.**
- Merged text: **0**.
- Seat 2's text as written: **0**.
- (a1) kept as a reference: **2**. It stakes the verdict on a diffuse-field formula in a non-diffuse corner.

**4. Tension later.**
- Merged text: **1**. (a) may still end up flagged rather than fixed under B15. The dip is about 6 JND of G, contained by U and the presets' 0.70 m distance from the corner. Undoing costs a parameter change.
- Seat 2's text as written: **1**. Its 0.70 m moved-listener print sits exactly on AX44's flag boundary; 0.75 m removes the ambiguity.
- (a1) as a reference: **2**.

**5. Evidence.**
- Sphere geometry and default radius: from the code, tracer.py L21, L42, L129, L150–153.
- Gate: σ = 4.34/√684 = 0.166 dB, so 3σ ≈ 0.50 dB (tracer.py L28; arithmetic redone).
- 05h W1 run, 16 M particles: SE 0.27–0.32 dB, C++ − tracer within 1.7 SE (file 14 L31–39).
- Non-diffuse: Kuttruff, as checked in file 35.
- `[Hyp]`, for the researcher: that detections scale with r_d² (Seat 2's estimate of about 152 M and 610 M particles).
- `[Hyp]`, scope note: the tracer is geometric acoustics, so the claim it supports is "the engine agrees with GA", not "the engine matches a measured room". I name no measured corner reference.

**6. Conditions.**
- (a1) as a reference: drop it, and the rating goes from 2 to 0 now.
- Later 1 → 0: B15 gets an owner phase before 12-2. That is a FOR MAISARA question (unchanged from file 36).

**7. Hand-offs.**
- Seat 5: the cost of the 610 M-particle manual job.
- Seat 2: confirm 0.75 m in print (i).
- Decider: the FOR MAISARA answer with the AMENDS line, if the cause is w or the capped branch.

**8. Premortem.** If the merge keeps (a1) as the verdict, a diffuse-field 0 dB "pass" could hide a GA-real corner deficit. A producer then drags a source into a corner and hears the tail drop about 6 dB, and Seat 1's ABX at 08-3 is the first to hear it.
