<!-- Saved by the orchestrator from seat 4's report, 2026-11-22. -->

SEAT 4 POSITION

**1. Reading.** M3 asks whether the scene chosen now for the AX47 self-ABX limits the binaural rerun at 08-3 (file 13 item 15). It does. Item 15 reruns "the AX47 self-ABX", so the 07c-2 scene carries into 08-3. If 08-3 changes scene, the comparison mixes up the chain with the scene. The matter triggers two of my cues: "missing or contradicted room cue" and "measurement doubt": a binaural result would come from an IR that is empty between the direct sound and t_mix,e = 0.380 s (file 22: −29.3 dB re direct).

**2. Ranking.**
- **S-B, prefer.** Only if K3 shows two things on the candidate scene: an early part that is not empty, and a specular share of 0 in the tail window, so that item 6 does not refuse per ear. If K3 shows share > 0, S-B cannot be run, and S-A with conditions is next.
- **S-D (my own variant), can live with.** Keep S-A now. Pre-register at 08-3 the rerun on the same scene (for comparability), plus a second scene with s < 1 if K3 qualifies one. The second scene gets its own Bonferroni split.
- **S-A, can live with.** Only with the conditions in point 6.
- **S-C, can live with, ranked last.** It is still s = 1, so the early part is still empty under AX21. On top of that the listener is 0.1 m from a wall. The wall reflection that defines that position would arrive at about 0.58 ms, and it is zeroed by (1−α)(1−s) = 0. A binaural render of that position leaves out the one cue the position exists to test.

**3. Tension now.** All four options rate 0. The 07c-2 chain is omni and diotic, so externalisation and parity across output modes are not engaged.

**4. Tension later (the debt).**
- **S-A: 2.** The 08-3 binaural stimuli would be a generic-HRTF direct sound, then 380 ms of almost nothing, then a diffuse tail. They would be static, with no head tracking and no headphone compensation (B14 is open debt, 08-3 R7). The early-reflection part of the 08-2 binaural chain (`Kind::Binaural`) would not be exercised at all. A rerun can test level detection on that scene, but nobody may read it as evidence about the binaural chain producers hear.
  - Second debt: if B11 is ever promoted (05f's deferred decision), the early part of every s = 1 scene fills in. That changes the IR under both chains and breaks the omni-to-binaural comparison. The scene is empty purely because of AX21, so S-A is the option most exposed to this.
  - Undoing it costs one more listening session at 08-3 plus minutes of kit reruns.
  - Evidence arrives at 08-3 (listening items L4 and L5, the per-ear item-6 prints) or at any B11 promotion.
- **S-B: 1.** It needs K3. The binaural rerun then carries room cues and stays on the same scene. The residual debt is AX21's envelope step at t_mix (0.9 to 8.7 dB in the AQ10 room). That step is identical in A and B.
- **S-C: 2.** Same reasons as S-A, plus a near-wall position the renderer cannot represent.
- **S-D: 1.** The cost is more of Maisara's listening time at 08-3: two blocks of 22 trials per chain, per extra scene.

**5. Evidence.**
- Reverberation almost consistently improves the externalisation of headphone 3-D sound: corpus `begault-3d-sound-vr-multimedia.md`, Ch. 3, Table 3.2 and the lines after it. [Observed, corpus]
- The early part is empty between the direct sound and 0.380 s, and per-emitter D/R is +10.7 / +9.7 dB at 1 kHz: file 22, from the code. This is AX21 and B11.
- Spatial separation of masker and target gives a BMLD of about 6 to 9 dB at 30 to 90°: corpus `blauert-ch3-multiple-sources-enclosed-spaces.md` (Fig. 3.40). So the binaural chain can change how detectable the step is compared with diotic presentation. The emitters sit about ±14° off-axis. That is my arithmetic: atan(3/12). Whether internalisation or a decorrelated tail moves the level JND of a tail step is [Hyp]. Researcher: is there data on tail-level JNDs, binaural against diotic?
- My persona has no incident on the claim that early reflections, not late ones, drive externalisation in a static binaural render. It is [Hyp]; incident 7.1 (Begault 2001) had both.

**6. Conditions of acceptance.**
- **S-A, from 2 to 1:**
  - (a) Item 15 pre-registers the same scene and tailSeed 12345 at 08-3, so the chain is the only variable.
  - (b) Before any binaural stimulus, the 08-3 per-band energy parity (±1 dB, scope 5) and item 6 are asserted per ear on this scene. D/R is printed per ear.
  - (c) The binaural result is worded "dry scene, empty early part (AX21), static, uncompensated, generic HRTF". It is never cited for externalisation or plausibility, and the 08-3 L4 and L5 checklist items are not judged on this scene.
  - (d) If B11 is promoted before 08-3, the omni ABX is rerun on the promoted IR, or the comparison across chains is marked void.
- **S-C, from 2 to 1:** only by not using it for binaural. The 0.1 m position is replaced at 08-3.

**7. Hand-offs.**
- Seat 1: whether early reflections in the onset window [0, 0.375 s] bias S-B toward non-detection through forward masking.
- Seat 3: the specular share in the tail window at s < 1.
- Seat 2: whether S-B and S-C produce an early part, and at what s.
- Seat 9: the label.
- Seat 1: whether the binaural block's α comes out of the AX47 family.

**8. Premortem.** If S-A is sealed unconditioned, 08-3 reports "not detected binaurally" on a dry, internalised render. Phase 08's goldens freeze on it. The first person to notice is Maisara, on the L4 listening item at 08-3, when the large hall still sits inside her head.
