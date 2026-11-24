SEAT 1 POSITION (phase 07c-2b, AX49 L4 stimuli and M3-T)

**Summary.** L-a and L-b are both acceptable to my seat. I lean slightly to L-a because the stimuli then come from the same tool as AX47. L-c is acceptable only if the L4 result becomes a blocking prerequisite for 07d's AX49 remedy. I accept M3-T. I predict L4 will detect the cut, which would trigger AX49's reversal. That is a reason to run L4 soon. It is not a reason to skip it.

**1. Reading.** The question is how to produce blind stimuli that compare the provisional tail with the exact tail (AX49 L4), and whether the TSP pair under M3-T is acceptable. The cues it triggers:
- **S2 inverted.** I predict detection, so the test is cheap and decisive.
- **S5, the hardest signal.** A held chord masks the cut, and a release exposes it. This was my own request in phase-07c-1b, file 2-seat1 L76.
- **S1, salience.** A tail that stops abruptly is the signature of gated reverb, an effect producers know by name.

**2. Ranking.**
- **L-a: prefer, narrowly.** The stimuli come from the same tool, kit, manifest and seal as AX47, as item 14 requires ("same chain and tool").
- **L-b: can live with.** It is equal to L-a if the harness is tied to render_cli by the null check in condition L-b1.
- **L-c: can live with, conditionally.** Without condition L-c1, I cannot live with it.

**3. Tension now.**
- **L-a: 0.** The perceptual purpose of "render_cli never use the provisional" is that no user output and no reference render carries the cut. Both are kept if the flag is off by default, src/plugin cannot reach it, and the manifest records `provisional: true`.
- **L-b: 1.** The rendering path is not the same as AX47's by construction.
- **L-c: 1.** A cut I expect to be audible stays in the build untested for longer. Nothing ships to users before Phase 13, and offline renders never use the provisional (ScenePipeline L670–676, from the code).

**4. Tension later.**
- **L-a: 1.** There is a risk that a render made with the flag ends up in a golden or a BRAS comparison. Undoing that is one golden round. A tool that is already in place also makes the 08-3 binaural rerun and the remedy variants cheap.
- **L-b: 1.** The harness can drift from render_cli. Undoing that costs about one session.
- **L-c: 2.**
  - 07d decides the long-T60 corner and AX49's reversal candidates. If L4 has not been run by then, the remedy (a deeper cut or a longer fade, per my 07c-1 file 10 condition 2) is chosen without data, or reopened afterwards: one board round plus about 1 h of ABX.
  - The evidence that would overturn this is the L4 result itself.

**5. Evidence.**
- **What the cut is.** Every band is truncated at L_f, at least 18.7 dB below the start of the tail, then faded out over 0.1 s (AX49; K17′, Vorländer §6.4.1 Eq. 6.4).
  - Recomputed: 60·0.312 = 18.72 dB. At T60 8 s, 41.3 dB of decay is left, which is about 5.5 s at 7.5 dB/s.
- **How deep the cut lies in each band.** It is 60·(L_f − t_mix,e)/T60_b dB, so it is shallowest in the T60_max band [Inferred, arithmetic].
- **With no release, the test cannot see the cut.** A held chord with no release differs by only 10·log10(1.0134) = 0.058 dB (phase-07c-2 interrogator file 6). The release is therefore the only exposure [Observed, file 6].
- **A cut at −19 dB is within the audible range.** Reverberation matters for as long as it is audible. Begault's example range is about 50 dB, from a loudest sound of 90 dB to a noise floor of 40 dB (corpus, "Physical Aspects of Reverberation").
- **Producers know this sound by name.** Gated reverb is a known effect: the gate cuts off the release and the reverb stops abruptly (Gibson, Ch. 4, Visual 65).
- **My prediction: detection near 16/16 by an attentive listener.** This is [Hyp]. The corpus has no threshold for a truncated tail.
- **Statistics.** Chance probability P(≥12/16 | 0.5) = 0.038. Power at p = 0.75 is 0.63 (recomputed).

**Held-chord design (my seat's questions).**
- **Chord.** A synthesised, deterministic additive chord, versioned, with no licence:
  - an open voicing C2–G2–C3–E3–G3–C4 (65.4–261.6 Hz, equal-tempered);
  - harmonic partials up to 8 kHz with a −3 dB/octave tilt, so that all 8 bands carry energy, the T60_max band included;
  - no vibrato;
  - a 50 ms onset and a 10 ms raised-cosine release. The abrupt stop is the hardest case.
  - The kit prints the chord's energy in each band beside the cut depth in that band.
- **Hold.** H ≥ max(L_p, 0.5·T60_max), which is 4 s at T60 8 s.
  - The exact IR beyond 4 s is 30 dB down, so the decay after release differs from the decay from a true steady state by ≤ 0.004 dB (arithmetic).
- **Release.** One release per file. After it, the file runs for at least the full IR length L (about 12 s) plus 0.5 s.
  - It is asserted that the exact render is fully contained in the file.
  - A and B have equal length.
- **Fully wet.** The input is convolved with the whole room IR (direct sound, early part and tail). No dry path is added, and the tail is not used alone. After release, only the tail differs.
  - Diotic, no normalisation.
  - One common gain for every file, recorded, with peak ≤ −3 dBFS.
- **Isolation check (asserted).** The provisional flag is true, and the prefix difference passes AX47 (b)'s −18.27 dB check. That leaves the truncation as the only variable.
- **Anchor.** As AX49 fixes it: 6 trials of a uniform 3 dB tail step on the exact held-chord render (3 up, 3 down), pass at ≥ 5/6.
  - It confirms that the chain and the listener's attention work. It does not confirm sensitivity to the envelope.
- **Familiarisation.** It includes the labelled provisional/exact pair.

**M3-T: I accept.**
- MA is an adult speaker. CA and CB are the excluded children (abx_kit L737, researcher R35). The decider's condition to record this from TSP's documentation stands.
- The pair was chosen for its assertions, before any blind result, so the choice involves no selection on outcome.
- The cue lies in the pause, so the choice of speaker matters little [Inferred].
- Condition: the pre-registration states the selection grounds.

**6. Conditions of acceptance.**
- **L-a1.** render_cli refuses `--provisional-ir` together with `--diagnostics` or any golden or update_goldens path, and the manifest prints the provisional flag. Later rating: 1 → 0.
- **L-b1.** The harness's exact render nulls against render_cli's exact render of the same scene, seed and input (≤ −100 dB, asserted), and the stimuli go through abx_kit's seal and score. Now rating: 1 → 0.
- **L-c1.** A named date, and 07d cannot decide AX49's remedy or reach `done` without the L4 result. Later rating: 2 → 1.
- **Optional, for Seats 3 and 5.** Validation-only parameters for fade length and L_f fraction, so that remedy variants can be ABXed after a detection without another round of tooling.

**7. Hand-offs.**
- Seat 2: a scene with T60_max = 8 s, L_p < L, no listener 0.1 m from a wall, and L_f, L_p and L printed.
- Seat 3: the remedy space if L4 detects.
- Seat 5: the flag's isolation and AX5 determinism.
- Seat 7: hours. One block is about 22 × 3 × 16.5 s ≈ 18 min of audio before replays.
- Seat 9: the scene label.
- Researcher: any published threshold for a truncated or gated reverberation tail.

**8. Premortem.** L4 is deferred and the remedy is chosen without data. A producer then reopens a large-room project, stops a pad within about 3 s, and hears the reverb gate shut. Maisara is likely to notice first, during her own listening.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/8-decider-scene.md
- /home/user/makroof/docs/BUILD_PLAN.md (AX47, AX49)
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md (items 8, 14)
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/src/sim/Engine.h (L146–160, L293–310)
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp (L640–720)
- /home/user/makroof/docs/review/phase-07c-1/10-seat1-r3.md
- /home/user/makroof/docs/review/phase-07c-2/4-seat1.md
- /home/user/makroof/tools/ci/abx_kit.py (L12, L737)
- /home/user/makroof/docs/corpus/begault-3d-sound-vr-multimedia.md
- /home/user/makroof/docs/corpus/gibson-art-of-mixing.md
