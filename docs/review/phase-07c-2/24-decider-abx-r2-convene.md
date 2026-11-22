# 21b: Decider round 2 on the ABX kit (files 22 and 23). Result: CONVENE

Corpus c1b171fe. I am not sealing yet. Under file 21's own outcome rule, verdict B means the seats must be convened before the stimuli are sealed. File 23 also returned file 21 UNDERCONVENED. Item 5 and 2a are given below as proposals, to be ruled on together with the seats' positions.

## Matters
- **M1. Item 5 reading.** Option A: file 13's reading, where the whole tail energy is multiplied by k. Option B: file 5's reading, E_b·k.
- **M2. Which T30 Q5 uses.** T-a: keep the T30 of the heard IR, 2.009 s (what the kit uses now). T-b: the tail's own T30, about 1.26 s.
- **M3. The scene.** S-A: keep `layout4_s1/default`, relabel it and record the bias. S-B: a scene with s < 1, so that the early part is not empty. S-C: switch to `listener_wall`. S-D: the seats propose one.

## Nine-row convening table
| Seat | Status | Reason |
|---|---|---|
| 1 | convened | Blind-test signal and onset window (M2). A dry scene biases the test toward non-detection (M3). |
| 2 | convened | AX21's empty early part is where the response's physics stops (M3). |
| 3 | convened | The diffuse/specular split in the step (M1), the 8 kHz tail T30 at +18 %, and early-reflection rendering (M3). |
| 4 | convened | Item 15 reruns this ABX binaurally at 08-3. If the early part is empty, externalisation on that chain may suffer. |
| 5 | not required | No audio-thread or host change. Every option is an offline `render_cli --realtime-emulation` run. |
| 6 | not required | No control, preset or default the user sees. Item 9 already says "not a validated preset". |
| 7 | not required | Every option costs minutes of rerun (the noise chain took 2 min 24 s in file 22). Item 13 forbids public copy. Price, tiers and wording are untouched. |
| 8 | not required | This is a validation stimulus, not a producer workflow. No point of view or translation is at stake. |
| 9 | convened | The label "occupied mid-size hall envelope" no longer fits a room about 20 dB drier. The 0.43 ceiling is Seat 9's arithmetic. |

## File 23's five questions
1. **What explains the 0.187 cutoff.** The +13.1 dB is not a print artefact: it is the D/R actually heard, the two direct sounds adding coherently (file 22). The margin starts at 32 to 35 dB (46 − 13.1 = 32.9). It holds for about 0.1 s, then falls at 46 dB/s, which is the tail's own T60 of 1.30 s. It crosses 20 dB at 0.375 s: 0.1 + 13/46 ≈ 0.38 ✓. So D2-L1 stands. "Not a malfunction" now holds conditionally on 2b, which has reported. It means the kit is not malfunctioning. The dryness itself is an AX21 property of the scene, and that is M3.
2. **Does `diff_db` pass at s > 0 under file 13's reading?** No. Take g = 0.9 dB and s = 0.5, so k = 1.2303. Then a = √((k − s)/(1 − s)) = 1.2086, and the difference energy is (a − 1)²(1 − s) = 0.02175, or −16.63 dB. The identity expects (√k − 1)² = 0.01192, or −19.24 dB. The miss is 2.6 dB against a tolerance of 0.01 (line 254). `step_db` passes, because the total energy changes by exactly k (line 255). So the kit refuses that stimulus rather than passing it. One caution: the printed `specular_share` is inferred from the identity, so at s > 0 it is only approximate.
3. **The nine-row table** is above.
4. **Contiguity.** The passing boundaries are not contiguous. The passing set is 0–33 and 35; boundary 34 misses by 0.6 dB. The manifest fields are `q5_passing_contiguous_from_first` (false), `q5_passing_boundary_indices` and `q5_realised_window_T30` = [0.0007, 0.1865]. I withdraw the line "35/81 × 0.43 = 0.186".
5. **Option lines against NFR-1** are under "Decided for Maisara" below.

Corrections accepted:
- The replacement rate is 46/36 = 1.28 replaced onsets per stimulus. The chance that the first draw is replaced is 46/81 = 0.568.
- Add "the D/R print changes" to the triggers that force a recompute before sealing.

## Corrected item 5 sentence (run sheet and PR)
"Item 5 scales the whole tail energy (diffuse and specular) by 10^(g/10). Item 6's difference identity is exact only at specular share 0. At share > 0 the kit's `diff_db` assertion fails, so the kit refuses the stimulus rather than passing a wrong one. It also refuses a down-step that would need E'_diff < 0. On layout4_s1/default the share is 0 in every band, so this equals scaling E_b alone (file 5's wording)."

## M2: which T30 Q5 uses (my proposal; Seats 1 and 9 rate it)
- I propose T-a. The pre-registration says "T30", and the ISO quantity for the heard IR is 2.009 s.
- A pause of 2.009 s or more also meets "≥ T30" on the tail basis (1.26 s).
- The onset window is set by the measured ≥ 20 dB assertion (it ends at 0.375 s). That lies inside both ceilings: 0.87 s under T-a, 0.54 s under T-b. So the accepted onsets are uniform over the same 35 boundaries under either basis.
- T-b would cut N from 81 to about 51, change every seeded realisation, and shorten the pauses. It gains nothing that the assertion does not already guarantee.
- Record the tail T30 beside it in the manifest.

## M3: the scene
- Item 9's fallback to `listener_wall` is pre-registered only for the case where the pin uncaps the scene. It is not a fallback for dryness, so no pre-registered fallback applies.
- Label correction, whatever M3 decides: "20 × 30 × 10 m, Eyring T60 1.29 s at 1 kHz, early part empty under AX21 at scattering 1. D/R per emitter +10.7 / +9.7 dB at 1 kHz; heard +13.1 dB. Not a validated preset."
- NFR-8 report, with nothing tuned:
  - AX21/B11: every scene with s = 1 has an empty early part. This is a known deficit, now measured.
  - Follow-up: the 8 kHz tail T30 reads +18 % against target. Find out whether the metric or the tail causes it.

## Seat briefs
Read: files 13 (items 5–9, 15), 21, 22 and 23; BUILD_PLAN AX21, AX47 and B11; the run sheet. Rate every option you are asked about, now and later, and give your conditions.
- **Seat 1:** M3 and M2. Does a step in the tail on this scene (tail about 10 dB below the direct sound at 1 kHz, nothing before 0.38 s) still test AX47's "all scenes" bound, or does it bias the result toward non-detection beyond what item 13's wording admits? Rate T-a and T-b.
- **Seat 2:** M3. Is an empty early part at s = 1 inside the response's documented limits (AX21)? Would S-B or S-C produce an early part, and at what s?
- **Seat 3:** M1 and M3. Rate A and B. For S-B, would specular energy in the tail window make s > 0, so that item 6 refuses every stimulus? Rate the 8 kHz +18 % against the step.
- **Seat 4:** M3. Does the scene chosen here constrain the binaural rerun at 08-3 (item 15)?
- **Seat 9:** M3 and M2. Is the corrected label right? Is there a reference room closer to "mid-size hall" that the contract can express? Is the 0.43 ceiling still the right bound?

## Knowledge inventory (first pass)
- K1: per-emitter D/R and the tail-alone T30. Source: file 22. Known (code).
- K2: Kuttruff Eq. 5.43–5.45, checked in file 23. Known.
- K3: D/R and specular share for `listener_wall` and for any scene with s < 1. Uninformed. The builder should compute them with the file 22 method, alongside the seats.

## Decided for Maisara (proposed, final after the seats report)
- M1 A (file 13's reading): serves NFR-1. The kit's assertions guard the stimuli, and the kit refuses rather than distorts.
- M1 B (file 5's reading): strains NFR-1. It meets neither item 6 assertion when s > 0.
- 2a, no amendment: serves NFR-1. The thresholds from the Expert are untouched.
- 2a, amend: strains NFR-1. It changes a pre-registered test after the data came in, with nothing gained.
- 2b, check first: serves NFR-1 and NFR-8. It found a real deficit, which is reported and not tuned.
- 2b, seal now: strains NFR-1. The stimuli would be sealed under a wrong label.
- None of these amends one of her recorded decisions. There is no NEEDS MAISARA.

| id | state | worst cell | confidence |
|---|---|---|---|
| M1 | proposed A, awaiting seats | — | high |
| M2 | proposed T-a, awaiting seats | — | medium |
| M3 | convening | — | — |

Files: /home/user/makroof/docs/review/phase-07c-2/21-decider-abx-kit.md, /home/user/makroof/docs/review/phase-07c-2/22-drr-t30-check.md, /home/user/makroof/docs/review/phase-07c-2/23-interrogator-on-file21.md, /home/user/makroof/tools/ci/abx_kit.py (lines 247–256, 565–577)

**CONVENE**: Seats 1, 2, 3, 4 and 9, plus the builder for K3.
