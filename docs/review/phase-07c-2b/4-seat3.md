# 4-seat3: Seat 3, M3-L4 (L4-A/L4-B, checks P1–P6, S1–S7)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 3 POSITION (M3-L4, the AX49 L4 stimulus design). For saving as docs/review/phase-07c-2b/4-seat3.md. I had read-only access, so I did not write the file.

I did not open the corpus. Acoustic figures come from the AX49 row (K17′, Vorländer §6.4.1 Eq. 6.4 as cited there), from the code, or from my own arithmetic, which is marked [Hyp].

**1. Reading**
- **The matter:** what the L4 ABX compares, and the checks every L4 stimulus must assert.
- **Cues from my §4:**
  - State discontinuity: the fade at L_f and the AQ4 handover.
  - Decay accuracy: the tail is truncated at L_p.

From the code:
- `assembleProvisionalHybrid` (Engine.cpp L654–705) makes the provisional with the same seed and stream as the exact tail, but with a generator of length lp, not L.
- Each band is scaled by c_b = 1/√(E_p,b/f_b), then given a raised-cosine fade over [lf, lp).
- So on [t_mix, L_f) the provisional is c_b × exact, per band. This holds up to FFT rounding (K2), not bit for bit.
- Past L_p it is zero.

My arithmetic at T60 8 s, k = 13.82/8 [Hyp]:
- **The cut.** The exact IR's energy past L_f is e^(−4.31) = 0.0134, which is −18.7 dB. So after a release, the provisional's decay stops within 0.1 s at about −19 dB re the steady state. That is a gated-reverb signature. I predict L4-A detects it at fully wet and monitoring level. Seat 1 owns that prediction.
- **The handover step.** At the handover, the exact state brings back the late energy (K23: both states read one input history). With d counted from the tail onset, the step is about 0.06 dB at d = 0, 0.53 dB at d = L_f − 1.25 s, 2.4 dB at L_f − 0.5 s, and about +12 dB at d = L_f.
- **A side channel during the hold.** The missing 1.34 % changes each chord partial by about 0.7 dB rms (8.686·√0.0067).

**2. Ranking**
- **L4-A: prefer.** It is the test AX49 writes ("detects the cut"), in its worst case. The handover's freedom from transients is provable without ears: companions (i)–(iii) and HF-W.
- **L4-B as written: cannot live with.** Under either reading of "≤ L_f" (from the onset or from the release), the exact state takes over before release + L_f, so the cut is never heard. AX49's reversal can then never fire.
- **L4-B′ (my addition):** the handover is seeded in (release + L_p, L). The cut is heard first, then the resurrection. I can live with it.

**3. Tension now**
- **L4-A: 1.** It needs the flag and a new chain, and it does not exercise the handover path.
- **L4-B: 2.**
  - Across the seeded d, the step ranges from 0.06 to about 12 dB, so the trials are not exchangeable.
  - It also needs a `/fix-plan` to item 14.
- **L4-B′: 1.**

**4. Tension later**
- **L4-A: 1.**
  - A detection sends AX49 back to the board with the 07d candidates, which is the registered reversal. The cost is a provisional redesign, about a phase, and that debt is AX49's, not the test's.
  - The resurrection is not tested by ear. It is printed (S7).
- **L4-B: 3.**
  - A pass leaves a cut I predict is audible unexamined in every gated load.
  - The evidence then arrives from users, after Phase 08's goldens.
  - Undoing it costs a further sitting plus the provisional redesign.
- **L4-B′: 1.**

**5. Evidence and checks to assert**

The IR level, per scene and tailSeed:
- **P1.** Assert L_p < L, and refuse otherwise. Print t_mix,e per emitter, T60_b, L_f, L_p and L.
- **P2.** The provisional IR is bit-identical to the exact one on [0, t_mix,e,min − 2.5 ms), on every emitter and output.
- **P3.** The provisional IR is exactly 0.0f from L_p onward.
- **P4.** For every band on [t_mix,e + 2.5 ms, L_f):
  - provisional = c_b·exact, with relative residual ≤ 1e−9 (via `unitDecays()`, in Catch2 or through a dump);
  - print 20·log10 c_b beside the AX47 (b) prediction;
  - assert |20·log10 c_b| ≤ the AX47 bound in force.
- **P5.** The fade gain equals 0.5(1 + cos(π(j − lf + 1)/(fadeLen + 1))) within 1e−9. It is monotone, and its first value is ≥ 1 − 1e−5, so there is no step at L_f.
- **P6.** Print the per-band energy share past L_f (predicted ≤ 0.0134). The ≥ 18.7 dB assertion that AX49 already makes stays.

The stimulus level, per trial:
- **S1.** A and B use the same programme and the same path (realtime emulation, fixed block, the kit's P). The two outputs are identical (diotic), the peak is ≤ MAX_PEAK, and nothing is normalised.
- **S2.** A and B are bit-identical up to onset + (t_mix,e,min − 2.5 ms), floored to a partition. Otherwise print the first differing sample.
- **S3.** Each render nulls against a float64 FFT convolution of its own written IR. This catches a flag that writes a different IR from the one it renders.
- **S4.** The cut is where AX49 puts it:
  - A is exactly zero after the programme end + the provisional IR length + latency;
  - the free decay is ≥ L, asserted;
  - print B's per-band level in the 100 ms after release + L_f, relative to the hold.
- **S5.** Print the per-band A − B difference over the last 1 s of the hold, and the per-partial differences (the side channel, for Seat 1).
- **S6.** No frame detector is asserted at the cut, because no derived bound exists there. P5 and S3 cover it, and `click_record` is printed only.
- **S7.** Print the would-be handover step 10·log10(E_B/E_A) per band, in 30 ms windows, on a 100 ms grid after release.

For L4-B′ in addition:
- W-a, companions (i)–(iii) and HF-W, with a = the provisional render alone and b = the exact render alone.
- The handover at a multiple of P and of the block, as the `--abx-step-sample` precedent in Cli.cpp L365–372 requires.

Negative controls:
- **N-L1:** a hard cut at L_f; P5 must fail.
- **N-L2:** a provisional built with a different seed; P4 must fail.
- **N-L3:** a written IR that differs from the one rendered; S3 must fail.

TailSeed: vary it across trials, with A and B sharing it within a trial, so that S5's side channel is not one realisation [Hyp]. The default is the kit's fixed seed.

**6. Conditions of acceptance**
- **L4-B → 1/1:** seed the handover after release + L_p (that is L4-B′), or run L4-A as the scored family and treat L4-B as print-only.
- **L4-A (1/1):** P1–P6 and S1–S7 are in place before the seal.

**7. Hand-offs**
- **Seat 1:** the pass rule; the exchangeability of the trials; the hold side channel; pre-registering the detection prediction.
- **Seat 2:** the scene. At the 100 m gated geometry, √V = 1 s puts t_mix ≈ 1.1 s and L_p ≈ 3.7 s.
- **Seat 5:** the flag, the `src/plugin` isolation test, and the dump for P4 and P5.
- **Seat 8:** the chord voicing.
- **Seat 7:** about 16 min per block plus the build.
- **Seat 9:** the label.

**8. Premortem.** If L4-B runs and passes, the −19 dB gated cut ships in every gated load. The first to notice is a producer auditioning a long room just after loading a project, who reports it as a bug after Phase 08's goldens.

Files read:
- /home/user/makroof/src/sim/Engine.cpp (L450–705)
- /home/user/makroof/src/sim/Engine.h (L146–160, L293–309)
- /home/user/makroof/src/cli/Cli.cpp
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/docs/BUILD_PLAN.md (L172)
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md


## Addendum (interrogator file 3, question 3): HF-W rated

Saved verbatim from the seat's follow-up report.

ADDENDUM: Seat 3 on interrogator question 3 (HF-W as decided in M3-3, with Seat 5's condition D). To append to docs/review/phase-07c-2b/4-seat3.md. I had read-only access, so I have not written it to the file.

My rating of HF-W: **1 now, 1 later**, as long as condition (a) under point 6 is met.

SEAT 3 POSITION

**1. Reading.** Rate HF-W as it now stands in `abx_kit.hf_w_check` (`tools/ci/abx_kit.py` L481–520), with condition D added. The cue from my §4 is state discontinuity in the step's fade path.

**2. Ranking.** HF-W with condition D: **prefer.** It is my round-1 design, and condition D makes it stricter. A click in a near-silent frame, such as a speech pause, used to pass silently. Now it fails.

**3. Tension now: 1.**
- From the code: the bound β = (1 + n_f/L)²(1 + 1e−5) = 1.1378 is derived, not fitted to data.
- Each skipped frame now asserts E_o ≤ β·n_f·1e−9.
- N1 to N3 and the skipped-frame spike test (`tools/ci/test_abx_kit.py` L326–414) each make it fail by construction.
- The residual 1 is the evidence gap below.

**4. Tension later: 1.**
- HF-W gates every rebuild the M3-8 trigger forces, including the one O4 is expected to fire.
- If a clean stimulus ever fails, the registered reversal sends it back to Seats 3 and 5. Undoing it is a code change in the kit only, with no `src/sim` change.
- The commutator assumption (that the 2 kHz high-pass and the 30 ms ramp commute to a negligible error) stays `[Hyp]` until the confirming numbers are in the record.

**5. Evidence.**
- **What file 5 supports.** `docs/review/phase-07c-2b/5-builder-tail-spread.md` L45–50 says that all 50 both_wall stimuli passed every item-6 assertion, HF-W included.
- **What I could not find.**
  - I could not find the figures "worst ratio 1.0003, no skipped frames, 100 stimuli" in file 5.
  - For s0.7, file 5 (L51–53) defers the full results to "the build log and `manifest.json`, cited in the brief once complete".
- **What this means for β.** A worst ratio of 1.0003 against β = 1.1378 would mean the commutator error is no more than about 0.001 dB, while the margin is 0.56 dB. That is consistent with my `[Hyp]`. But for the record I hold the figure as reported by the coordinator, not as sourced.

**6. Conditions** (to keep the rating at 1/1):
- **(a)** The manifest or brief cites the per-scene worst ratio, its margin in dB and the skipped-frame count for both scenes (50 + 50 stimuli). With that cited, the commutator assumption moves from `[Hyp]` to measured, on these two scenes only.
- **(b)** Every rebuild under the M3-8 trigger prints the same three fields.

**7. Hand-offs.** The CI plumbing and condition D's threshold go to Seat 5.

**8. Premortem.** HF-W can miss a defect whose high-frequency energy stays under 0.56 dB of the larger end point in every frame. Companion (ii) catches such a defect exactly, so it would surface there first and not by ear.

Files checked:
- /home/user/makroof/tools/ci/abx_kit.py
- /home/user/makroof/tools/ci/test_abx_kit.py
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
