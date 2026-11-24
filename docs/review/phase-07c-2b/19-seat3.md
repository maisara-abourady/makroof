# 19-seat3: Seat 3 on E, the cut-window time base and the 125 Hz fragility

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION

**1. Reading.** The matter is my cells for L4-COV E, C and "B as a second bright arm". It also asks whether coverage (b) is measured on the right time base, and whether a 2.29 dB margin that rests on the 125 Hz band can be an asserted gate. The §4 cues it triggers:
- Decay accuracy: the depth table K2.
- Spatial correlation and realisation: a few-partial band in a single noise-tail realisation.
- State discontinuity: the grid of the cut.

**2. Ranking.**
- E: *prefer*. It measures exposure directly in the fade window instead of through a steady-state proxy.
- C: *can live with*.
- B as a second arm: *can live with*.

**3. Tension now.**
- E: **0**. The stimulus, IRs, hashes and my checks P1–P6, S1–S7 and R1–R7 are unchanged. Assert (b) reads B in the right window (§2 below).
- C: **0**. This is unchanged from 12-seat3.
- B as a second arm: **0**. The pad arm keeps everything. The bright arm shares the IRs, so P1–P6 carry over, and S1–S7 plus its own (a) and (b) run automatically on its renders.

**4. Tension later.**
- E: **1**. Assert (b) holds a margin smaller than one realisation's spread (§5). If anything upstream changes before the seal (engine tail synthesis, tailSeed, chord) and the kit is rebuilt, (b) can red on the luck of 125 Hz alone. That would be a stop and a board round, not a false pass. Undoing it costs one print or one reference change. The evidence would come from any rebuild, or from the ensemble print in §6.
- C: **1**. My reasons in 12-seat3 still apply.
- B as a second arm: **1**. If the two arms disagree, someone has to reconcile them, and the null has to name its scope per arm. My reading of K5 (about 1 dB less sensitive, [Inferred]) is unresolved against Seat 1's.
- **My E cell is not one point above C.** The read-from-conditions 0/1 stands, so this cell does not flip the winner to C.

**5. Evidence.**

*(2) The time base is confirmed correct, from the code.*
- `cut_window` sets c0 = `m["end"] + round((L_f − alignmentShiftS)·FS)` on `y["exact"]`. That array is the render as written, with latency removed and the pre-scale undone.
- S3 nulls each render against a float64 convolution at delay 0, to −132 dB (file 18). So written-file sample n is input sample n through the aligned IR.
- At n = end + lf_tap, every contributing IR tap is ≥ L_f. B there is purely the tail past L_f, and A is inside its fade.
- The 100 ms window equals the fade [L_f, L_p) of 0.1 s.
- Numbers check: 8.0267 − 4.53 = 3.4967 s, which is 3.61353 − 0.1168 s (alignmentShiftS). That matches the direct path of 40.31 m.
- The engine-time form (+P = 512 samples = 10.67 ms) would misplace the window by about 11 % of its length. It is not used, which is correct.
- The partition grid does not enter (b) at all. (b) reads only B, which is an LTI convolution checked by S3. The grid bounds apply only to A's identity and zero asserts (S2, S4). This answers Seat 1's hand-off: computable, and grid-independent.
- Two residues are immaterial:
  - c0 sits one sample after the first fully faded output (end − 1 + lf_tap), and round() against tap()'s ceil moves it by ±1 sample, out of 4800.
  - The band filters are zero-phase (from the code, `s7_handover` docstring). B has no discontinuity at c0, so edge smear (about 23 ms at 63 Hz, [Inferred]) does not bias the window.

*(3) Fragility.*
- **Background:** the energy at one frequency in a diffuse field is exponentially distributed (Kuttruff §3.7, Eq. 3.47). The standard deviation of the level is 10/ln10 · π/√6 = **5.57 dB** (my arithmetic).
- **The window holds one draw per partial** [Inferred]. At t − end ≈ 3.5 s, the windowed transfer function decorrelates over about T60/13.8 ≈ 0.58 s.
- **Partial counts per band** (from the code, `L4_NOTES`):
  - 63 Hz (44–88 Hz): one partial, C2.
  - 125 Hz: three distinct partials (98, 130.8, 164.8 Hz).
  - 2 kHz: about 40 distinct partials.
- **Estimated spread** [Inferred]: σ ≈ 3 dB at 125 Hz and ≈ 0.9 dB at 2 kHz. The margin is a max-versus-min difference with σ ≈ 3.1 dB, so 2.29 dB is about 0.7σ.
- **Measured support:** K3 shows a 12.4 dB spread across 63 Hz–1 kHz, bands that share the same T60 and the same 18.72 dB depth. That spread is the realisation, not the room.
- **Verdict: acceptable as an asserted gate.** The stimulus is sealed and bit-reproducible (two builds, identical SHA-256s), so (b) is an exact property of the file the listener hears, not an estimate. A strongest-band reference fails safe: luck can only make it red, never pass a dull chord. It is not acceptable as a population claim, and the null wording must stay tied to this stimulus.
- **Switching the reference now would be a second post-hoc loosening** that widens the margin. Today's values, relative to each reference:

| Reference | 2 kHz margin |
|---|---|
| Strongest band (as asserted) | 2.29 dB |
| Power mean of 63–500 Hz (−4.18 dB) | 6.47 dB |
| Median of 63 Hz–1 kHz (−5.91 dB) | 8.20 dB |
| dB-mean of 63 Hz–1 kHz (−6.57 dB) | 8.86 dB |

- The power mean is still about 65 % the 125 Hz draw, so it barely cures the fragility. The median is the robust choice.

**6. Conditions of acceptance.** No cell is rated 2 or 3. I ask for two things for E, both print-only:
- Print (b) against the median of 63 Hz–1 kHz beside the asserted strongest-band form.
- Print an ensemble of (b) for the exact arm over 16 tailSeeds (render_cli `--tail-seed`, exact path), so the reviewers can see whether 2.29 dB is typical or lucky.

Separately, a recorded fallback, the decider's call: if a rebuild reds (b) only because the strongest band moved, the reference becomes the median of 63 Hz–1 kHz.

**7. Hand-offs.**
- Seat 1: whether the strongest band or the median is the perceptually right reference for "exposed". Upward masking from 125 Hz to 2 kHz is negligible, [Hyp].
- Seat 7: the bright arm's hours.
- Seat 9: the 4 kHz depth sentence in the null.

**8. Premortem.** If (b) stays strongest-referenced with no ensemble print, a pre-seal rebuild could red on the 125 Hz draw alone. The builder would notice first, and the board would lose a round arguing over a margin that was always a single draw.

Files: /home/user/makroof/tools/ci/ax49_l4.py (L703–718, L745–756, L984–995), /home/user/makroof/docs/review/phase-07c-2b/18-builder-l4-coverage-applied.md, /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (§3.7).
