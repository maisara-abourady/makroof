<!-- Saved by the orchestrator from seat 2's report, 2026-11-22. -->

SEAT 2 POSITION (phase 07c-2, D-W2 ABX kit, M1 only: what item 5's step scales). Corpus present (c1b171fe). I checked the code myself at src/cli/Cli.cpp L737–803.

**1. Reading**
- The question: should the ABX level step scale the whole late-field level target, E_target = E_spec + E_diff (A), or only its diffuse term (B)?
- Cues it triggers:
  - §4 cue 5: which parameter deviates. Here it is the late energy, not the decay or the early part.
  - §8 P4 step 2: the per-band late-energy description is the representation I hand to Seat 3. E_target is that description (Engine.cpp L183).
  - §2 criterion 5: honesty of output. The stated step must be the rendered step.

**2. Ranking**
1. **A: prefer.**
2. **B: can live with, but only on scenes where every band's E_target specular share is 0.** There it is the same as A. Elsewhere it under-steps, so it is not an option I would choose.

**3. Tension now**
- **A: 0.**
  - The tail amplitude is √(E_target/ē), and E′_target = k·E_target (Cli L788).
  - From t_mix,e + 2.5 ms onward the window holds no images (NoiseTail.cpp L278–279). So the late field the listener hears changes by exactly g in every band.
  - That is the quantity AX47 bounds.
- **B: 1.**
  - On layout4_s1/default the share is 0 in every band. This follows from Kuttruff Eq. 8.59: the specular part is (1−s)(1−α), which is 0 at s = 1. So B renders the same stimuli as A.
  - The cost is wording only: "scales E_b" would describe the knob, not the late-field level.

**4. Tension later (the debt)**
- **A: 0.**
  - It commits nothing beyond the refusal rule: a down-step is refused when g < 10·log10(share), and so is any band with a specular-only tail (Cli L781–795). Both rules are visible and asserted.
  - One caveat: the stepped state is a stimulus manipulation, not a reachable room. E_diff no longer means "diffuse energy" in the stepped IR. That matters only if someone reuses the stepped IR as a room prediction. It is validation-only, in the AX4 style.
- **B: 2.**
  - The rendered step is 10·log10(s_t + k(1 − s_t)), where s_t is the specular share of E_target.
  - At g = 0.9 dB (k = 1.230):
    - s_t = 0.40 gives 0.56 dB. That is item 15's ceiling, so a scene that passes the 15(ii) filter still under-steps by 0.34 dB.
    - s_t = 0.74 (small_room, test_cli.cpp L350–358) gives 0.25 dB.
  - The error differs by band, so the step is no longer uniform across all 8 bands. That breaks item 5's own definition.
  - The bias points toward non-detection, which would make the bound look looser than it is.
  - Evidence arrives at 08-3, in item 15(ii) or the first s < 1 scene. Item 6's assertion would fail there and the kit would refuse to seal, so the bias would not pass silently.
  - Undoing it costs one parameter change plus a reseal and a stimulus rebuild. That is rework, not a rewrite, so 2 and not 3.

**5. Evidence**
- From the code:
  - Cli.cpp L742–796: the A formula, its two refusal branches, and the print of E_target's specular share.
  - Engine.cpp L183, L531–532: E_target and the tail amplitude.
  - NoiseTail.cpp L278–279: the crossfade reaches {0, 1}.
  - test_cli.cpp L350–358: the identity holds at share ≈ 0.74.
- Corpus:
  - Kuttruff §8.8, Eq. 8.59: the specular fraction is (1−s)(1−α).
  - Kuttruff §9 (hybrids): the late part represents the energy after the early specular part, so the level target is the whole late energy.
- B's arithmetic is mine, redone from the formula above:
  - 0.40 + 1.230·0.60 = 1.138, which is 0.56 dB;
  - 0.74 + 1.230·0.26 = 1.060, which is 0.25 dB.
- This agrees with Seat 3's 0.47 dB at s_t = 0.5: 0.5 + 0.615 = 1.115, which is 0.47 dB.

**6. Conditions of acceptance**
- **B (2 → 1 later):** restrict B by assertion to scenes where s_t = 0 in all bands, and refuse it otherwise. That turns B into A's special case, so A is simpler.
- **A (already 0), wording fixes only:**
  - the item-5 sentence names both refusals, as the interrogator noted in file 28;
  - `target_specular_share` and `window_unscaled_share` are printed under separate names, as in file 27's print fix.

**7. Hand-offs**
- Seat 1: whether a 0.34 dB under-step at the bound changes the verdict's power.
- Seat 3: smoothness and coloration of the stepped tail. It rated A 0/0 and B 1/2 in file 26, and I concur.
- Decider: put Seats 1, 4 and 9 down as not required for M1, with reasons (file 28).

**8. Premortem.** If B is adopted and item 15(ii) runs on a scene with s_t > 0, the nominal 0.9 dB step renders as roughly 0.56 dB, item 6 fails or the bound is set on a smaller step than recorded, and the builder's 08-3 rerun is the first to notice.

Files: /home/user/makroof/src/cli/Cli.cpp (737–803), /home/user/makroof/docs/review/phase-07c-2/27-decider-abx-r3.md, /home/user/makroof/docs/review/phase-07c-2/28-interrogator-on-file27.md, /home/user/makroof/docs/review/phase-07c-2/26-seat2.md, /home/user/makroof/docs/review/phase-07c-2/26-seat3.md
