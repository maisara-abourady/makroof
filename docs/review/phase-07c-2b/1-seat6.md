# 1: Seat 6 (canvas designer), M3, narrow: split or unsplit α; families per option

Convened by decider file `docs/review/phase-07c-2/31-decider-abx-r4.md` ("M3: CONVENE", Seat 6 narrow). Run
2026-11-24 in the phase-07c-2b session as `seat6-canvas-designer`. Recorded verbatim from the seat's answer.

SEAT 6 POSITION: phase 07c-2b, M3, narrow (whether to split α, and how many families V1 to V4 imply)

Read: file 31 (M3 CONVENE, answer 4, V1 to V4); BUILD_PLAN AX47 (the Reversal and self-ABX design rows), AX48 (keyless load, synchronous stage-1 at the AX38 gate), AX38 (the (iv) load mark, the 10 s line); file 13, item 15; my file 10, (a).

**1. Reading.** The question is which costs the user more:
- a false "detected", which sets AX47 to 0.5 dB and so the admission cost to SE ≤ 0.25 dB, so loads get longer or a stage-1 source cannot be admitted;
- a missed real step, which is the price of splitting α.

Cues it triggers: positions that recompute heavily (S3); an automatic level step after the user stops (W4, my file-10 concern); "silence is unmeasured" (S9).

**Families implied by each option** (item 15 reruns at 08-3 "at the bound in force", so I count an 08-3 family as able to fire the reversal):
| option | families in 07c-2 | families with 08-3 | union bound on false reversal |
|---|---|---|---|
| V1 | 2 | 4 | 0.098 at 07c-2, 0.196 by 08-3 |
| V2 | 1 | 3 | 0.049, then 0.147 |
| V3 | 1 | 3 | 0.049, then 0.147 |
| V4 | 1 | 3 | 0.049, then 0.147 |

If the decider counts 08-3 differently, my ranking stays the same.

**2. Ranking.**
- **Unsplit** (each scene its own family at item 3's thresholds, union rate recorded): *prefer*.
- **Split** (noise ≥ 13 and speech ≥ 13 per scene, 0.0213): *can live with*, only under the condition below.

**3. Tension now.**
- **Unsplit: 1.** A false reversal does not make today's load worse. 07c-1's keyless load already runs the synchronous final. What it costs is the improvement a statistical stage-1 source would bring. Halving SE takes about 4× the work, since SE goes as 1/√W [Inf; sampling arithmetic]. File 4-seat8 shows the same thing: ×1 gives SE 0.47 to 0.93 dB, ×8 gives ≤ 0.25 dB. So stage-1 at 0.25 dB costs close to what the final costs, and the user's wait stays near the status quo.
- **Split: 2.** At p = 0.75, noise power falls from 0.63 to 0.405 (file 31, answer 4). That raises the chance of missing a real 0.9 dB step from 0.37 to 0.595. A missed step admits a statistical source at SE ≤ 0.5 dB. Its interim-to-final step can then be audible exactly when "settling" clears: an automatic jump after the user has stopped (W4). That breaks criterion 1 (trust before range), which I never trade.

**4. Tension later (debt).**
- **Unsplit: 1.**
  - Commits: a false-reversal risk of up to 0.147 or 0.196 that, if it fires, keeps the load slow. AX38 (iv)'s 8 × 100 m / 96 kHz load is already about 20 s against the 10 s line, and that finding stays unrepaired by this path.
  - Undo: cheap, a parameter-level change. The bound goes back to 1 dB through a board decision and one confirmatory ABX.
  - Evidence: the 07c-2 and 08-3 sessions, then load times in phase-13 beta.
- **Split: 2.**
  - Commits: a miss that ships as an audible settle step.
  - Undo: expensive. Producers have to hear it first. Then come a class (c) re-decision, new stimuli and a rerun, while trust in the first minute is already spent.
  - Evidence: the 07c-2 L1 checklist and 08-3 binaural first, the beta after that.

**5. Evidence.**
- Powers and tail probabilities: file 31, answer 4 (Binomial(16, ½); I checked 2517/65536 = 0.0384 and 697/65536 = 0.0106).
- Admission rule SE ≤ 0.5 dB, giving 0.98 dB at p95: AX47 "From 07c-2".
- Keyless load is synchronous at the AX38 gate: AX48 FM-3′.
- The 1/√W scaling: [Inf]. Its size at production W is for Seat 5 or Seat 2 to give.
- That a 0.9 dB step at settle is audible to producers on program material: [Hyp]. That is Seat 1's ruling.
- No incident in my persona covers family-wise error. My preference comes only from comparing the two costs (W4 against a forgone speed-up).

**6. Conditions of acceptance.**
- **Split, to lower it to 1/1:**
  - a pre-registered rule that a scene detecting at ≥ 12/16 noise, but below the split threshold, may not be read as "not detected". It goes to a confirmatory rerun before any statistical source is admitted;
  - my file-10 condition 2 carries over: a non-detection is recorded with its power and is never worded as inaudible.
- **Unsplit, to hold its 1:**
  - the record states the union rate for each option as in the table above;
  - a reversal that fires in exactly one family, at exactly its threshold, is flagged for a confirmatory ABX before phase 13. This is not a gate on the reversal, so power is unchanged.
  - The cost of a false reversal is measured as wall-clock time, not projected: the AX38 (iv) load and the stage-1 time at SE 0.25 against SE 0.5, on three OSes.

**7. Hand-offs.**
- Seat 5: the actual ×W cost of SE 0.25 against 0.5 at the AX38 gate.
- Seat 1: whether α is split at all, and whether a 0.9 dB settle step is audible on program.
- Seat 7: the session hours behind V1's extra family.
- Decider: whether a binaural detection at 08-3 reverses the omni bound.
- Everything else in V1 to V4 is NOT MY MATTER: scenes, layout-5 provenance, K5, labels.

**8. Premortem.** If α is split and a real 0.9 dB step goes undetected, the first producer who loads a large room hears the tail jump when "settling" clears and stops trusting the canvas. Maisara at the 07c-2 L1 or 08-3 checklist notices it first, otherwise a beta tester.
