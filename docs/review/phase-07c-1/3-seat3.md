# 3 — Seat 3 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the seat's report, 2026-11-12. Brief: file 2.

SEAT 3 POSITION (Reverb renderer). Phase 07c-1, Matters C and D, plus A3's effect on the renderer. Corpus present. The renderer facts below come from my reading of the code: `src/sim/tail/NoiseTail.{h,cpp}`, `src/sim/ism/BandRenderer.cpp`, and the Engine order given in file 1.

**Reading.** The question is what the renderer plays between a restore or an edit and the final IrSet, and how it gets from there to the final IrSet. Cues from my §4: "state discontinuity" (the step and its law), "decay accuracy" (D5's wrong T60) and "cost" (D3, A3).

**Code finding that changes D3 and D5 (load-bearing).**
- The unit decay is Gaussian noise (seeded with `tailSeed` and the emitter) put through a centred FIR band filter, then multiplied by exp(−6.91 t/T60_b), then normalised to unit energy over its whole length.
- Output sample j depends only on noise samples j to j+2h. That noise is the same PCG sequence whatever the length or the T60.
- So two tails built for the same scene with the same seed, emitter and fs carry the same band noise up to rounding. They differ only in envelope, length and normalisation gain. This covers a short prefix tail (D3), a tail with the previous T60 (D5) and the exact final tail.
- They are therefore coherent, not unrelated waveforms. The brief's D3 premise ("equal-power, unrelated waveforms") is wrong from the code.
- The interim and final IrSets for the same scene also share an identical early part.
- AX18's own split ("equal-gain for position updates, equal-power between unrelated IRs") therefore requires **equal-gain** for every same-scene interim-to-final step. With equal-power, coherent parts sum to cos45° + sin45° = 1.414, a bump of +3.0 dB for about 15 ms in the middle of the 30 ms fade.
- Equal-power stays right only for the first IrSet after load (where the fade starts from silence, so the law has no effect) and for project-to-project restores.

**Matter C (D-C1).** The size of the step is Seat 1's ruling. My rating covers the mechanics only. Under a 30 ms equal-gain fade, a level change is a smoothed gain (my S4: 5–20 ms is enough), so it causes no click at any size.
- **C1: prefer.** Now 1, later 1. One fade, recorded. It commits nothing beyond a diagnostic counter.
- **C2: can live with.** Now 1, later 2. "Cannot guarantee" means the bound must be known *before* the final level exists. That holds only for a saved E_b (0 dB) and for B2 under 07c-2 (its SE is known). For B1 (previous level) the step is unknowable, so C2 forces a hold and stacks edits up behind it in 07c-2.
- **C3: can live with.** Now 1, later 2. B2's 07c-2 SE of up to 1.33 dB (AX41) fails it. 07c-2 would need extra work.
- **C4: can live with.** Now 1, later 1. My criterion 1 is met. Criterion 2 (level within the jnd) holds only for the final level.
- **Scope point.** D1's tail joining from nothing is a step of unbounded size in dB. Every bound C1–C3 either rules D1 out where a final tail exists, or must say explicitly that it excludes it.
- **Condition on all four: same-scene steps use equal-gain.** Without it every option rises to now 2 (a +3 dB, 15 ms bump on the early part, which my criterion 1 does not trade).

**Matter D.**
- **D1: cannot live with at load where a tail existed.** Now 3, later 2.
  - It reads against condition 9 ("never silence where a tail existed"): the late field is silent for about 3.3 s.
  - The tail then arrives as one step from −∞.
  - It is acceptable only for scenes with no tail (the AX22 ISM fallback).
- **D2: cannot live with for edits.** Now 3, later 3.
  - It holds the ISM update behind the solve (81–131 ms), even for position edits whose unit decays are cached. That breaks condition 4 ("ISM update never held behind the diffuse solve").
  - For edits that change T60, the hold is about 3.3 s.
  - It also blocks Phase 10's split update (AX38 (v)).
  - For `reset()` and prepare it is the same thing as condition 10: rated 0 there.
- **D3: prefer at load.** Now 1, later 1.
  - Generator: the same `BandNoiseGenerator` (same seed and stream) at a prefix length L_p, with the existing expected-energy normalisation (`expectedUnitEnergyPer10ms`) in place of the realisation's energy.
  - Cost, [Hyp] scaled from the 3.14 s by FFT size (2^21 at 12 s/96 kHz; h is about 5–6 k samples from the Kaiser design):
    - L_p = 1 s needs a 2^17 FFT, about 0.15–0.2 s.
    - L_p = 0.5 s needs 2^16, about 0.08 s.
  - That is a short background step, not the 0.15 s synchronous budget, unless L_p is about 0.25 s.
  - The step from provisional to exact keeps the same noise and changes only the normalisation gain and the extension past L_p. The gain difference is the energy deviation of the realisation: [Hyp] up to about 1 dB at 63 Hz, much less above. The researcher or the condition 9 packet should measure it.
  - Fade the prefix out over its last 50–100 ms. A hard cut at −7.5 dB (L_p = 1 s, T60 = 8 s) gates transients.
  - Offline never uses it, and the final output is unchanged, so no golden round is needed.
- **D4 (and A3): can live with.** Now 1, later 2.
  - It adds no fidelity, only load time.
  - A stored waveform is tied to fs (a project reopened at 44.1 vs 48 kHz is invalid), to the output mode (Seat 4), to 07c-2's W_max raise and to Phase 08/09/10.
  - Its unit decays would be about 147 MB (8 bands × 1.15 M × 2 emitters × 8 B), so only the assembled 18 MB IR is practical.
  - A stored float IR from another OS is not what this OS's offline path builds (AX5 holds on the same OS only), so offline must recompute anyway.
  - Undoing it costs a further state-version bump.
- **D5: can live with.** Now 1, later 1.
  - With the previous T60 the decay slope is wrong for at most about 3.3 s, during the user's own edit. That is above my 5% jnd but transient.
  - **Condition:** the interim amplitude must be matched at t_mix to the *old* decay's ebar (sqrt(E_target/ebar_old)). Otherwise the level is off by 10·log(ebar_new/ebar_old), about 1.2 dB for a change from T60 2 s to 1.5 s (from the formula in `NoiseTail.h`).
  - The D5-to-final step is coherent, so it uses equal-gain (the existing edit law).

**Option of my own, D6 (edits that change T60).**
- Cache the band-filtered noise before the envelope.
- A T60 edit with an unchanged length (any T60_max ≥ 8 s hits the 12 s cap) then needs only the envelope and normalisation loop. That is bit-identical to `make()` if it is the same code path, and roughly ≤ 0.1 s [Hyp].
- Cost: about 74 MB per emitter at 96 kHz/12 s. Seat 5 should rate the memory.

**Progressive bit-identical synthesis: no.** It is one circular FFT of size 2^21 plus a normalisation over the whole length, so a prefix differs in rounding and in gain. It can be progressive and near-identical (D3), but not bit-identical without the recorded "cheaper generator" golden round.

**Ranking.**
- Load: A1/A2 level + D3 prefer; D4 can live with; D1 cannot live with.
- Edits: D5 (or D6) prefer; D2 cannot live with.
- `reset()`/prepare: D2 (= condition 10).

**Hand-offs.**
- Seat 1: whether a gain step of about 1 dB at 63 Hz in the provisional tail, and the size of the C-bound step, are audible.
- Seat 5: D6's memory, A3's serialisation, and running D3 off the audio thread.
- Seat 4: A3's mode dependence.

**Premortem.** If the same-scene step ships with equal-power, every reopen and every solve plays a +3 dB, 15 ms bump on the early part. Maisara's listening pack (the ir_switch and restore renders) is the first place to show it.