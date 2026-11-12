# 3 — Seat 1 position (phase 07c-1, D-C1/D-C2/D-C3/D-C9)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Brief: file 2.

SEAT 1 POSITION — phase 07c-1, matters A to D (corpus present, revision as in the brief)

**1. Reading.** The question is what the listener hears between a restore or edit and the final IR, and how large the interim-to-final step may be. It triggers three of my cues. Temporal smoothness (S7): a step inside a running stream. A threshold borrowed without its method (S4): Table 6.1 is a paired-comparison number. The worst-case signal (S5): steady noise through a fully wet send. One more fact matters: in 07c-1 the step is 0 on every path except B1's edit-latency. The ruling only starts to matter at 07c-2.

**My ruling on D-C1 (my own variant, C5 = C2 with C1 as the fallback).**
- **The bound.** For the same scene, the interim-to-final change in tail level is at most **1 dB per octave band, in all 8 bands from 63 Hz to 8 kHz**. Because the bound holds in every band, the broadband step is also at most 1 dB.
  - The step changes only the late energy, so 1 dB on the tail is at most 1 jnd of C80 and less than 1 jnd of G.
  - Applying it to all 8 bands costs nothing in 07c-1.
- **When an interim source may be used.** Only when its error is known by construction:
  - a saved E_b whose key matches gives a step of 0. Per AX18 no switch is made at all, because the IR is bit-identical;
  - the (A) estimate (07c-2) is admissible only when its reported achieved SE is at most 0.5 dB in every band. That gives about 2·SE ≤ 1 dB. The rule is generic: it uses the estimator's own diagnostics (AX41), so it is NFR-8-clean.
- **When no admissible source exists** and conditions 5 and 9 forbid waiting, the step is taken as one gain change and recorded (diagnostic plus counter). This is C1's clause, kept only as the fallback.
- **The crossfade law for this step.** A level-only step uses the same unit decays, so the correlation between the two tails is 1. AX18's mid-fade factor 1+ρ then gives a **+3.0 dB bump for 30 ms** under equal-power. Equal-gain, or a plain gain ramp, avoids it. The crossfade law is Seat 3's call. Whether a 30 ms +3 dB swell is audible is [Hyp] and goes to the researcher.

**Does Table 6.1 apply inside a running stream?** Not directly.
- Its jnds (G 1 dB, C80 1 dB, 500 to 1000 Hz) come from paired comparisons of room states (Vorländer §6, Table 6.1, after ISO 3382-1).
- Inside a stream, the two segments sit side by side. On steady noise the threshold is probably lower: level differences below 0.5 dB are audible in mono noise playback (Zotter and Frank, §4, the AllRAD/EPAD comparison).
- With music it is higher: level changes of a reflection of about ±1.5 dB are detectable (Kuttruff §7.3, Reichardt and Schmidt). My register says C80 is about 3 dB under real-time switching (secondary source, medium confidence).
- So 1 dB holds for music or speech with the dry path present. On a fully wet, steady-noise send, a trained listener in forced choice may detect it. I accept that residual because the user is not running a forced-choice test, and the step occurs at most once per solve. R4 should confirm the within-stream threshold. If it comes back below 0.5 dB on music, move to C3.

**2. Ranking and 3–4. Tension (now/later).**

Matter A (the saved E_b):
- A1, *prefer*: 0/0. The confirming solve is a free test that the key is right: any step other than 0 is a recorded key bug.
- A2, *can live with*: 0/1. It is silent if the key misses a dependency: the wrong level ships forever and nothing measures it.
- A3, *can live with*: 0/0 for perception. It is the best at load. Its cost belongs to Seats 5 and 7.
- A0, *can live with*: 1/2. At 07c-2 a load in layouts 4/5 gets the (A) estimate, whose SE reaches 1.33 dB (AX41), so p95 ≈ 2.6 dB by my arithmetic of 1.96 × 1.33.

Matter B (the interim level without a saved E_b):
- B4, *prefer*: 0/2. Its load half is B2's later debt.
- B2, *can live with*: 0/2. In 07c-1 the error is 0. At 07c-2 it is SE 0.13 to 1.33 dB in layouts 4/5, and SE 0.44 to 0.50 dB (p95 ≤ 0.89 dB) in the low-α s = 1 cube.
- B1, *can live with*: 1/1. Its step is the user's own edit, arriving late. I contest the brief's scope: that step lies outside D-C1 and is bounded by the AX38 (iv) staleness records.
- B3, *cannot live with* unless a predictor exists: 3/3. AX16 is +3.83 dB off in layout 4 and +2.38 dB in the absorbing-floor cube, about 4 jnd (AX16). Without a validated predictor it breaks condition 5.

Matter C (the step):
- C5, my variant, *prefer*: 0/1.
- C2, *prefer*: 0/1. Its only gap is that at a load with no saved E_b it may leave no admissible source.
- C3, *can live with*: 0/1. It costs (A) admissibility at 07c-2.
- C1, *can live with*: 1/2. A 2.6 dB p95 step would be taken and only recorded.
- C4, *cannot live with*: 2/3. No number means A4 can never fail. At 07c-2 an unbounded step is heard as "the room changed by itself".

Matter D (while the synthesis is pending):
- D4, *prefer*: 0/0.
- D3, *prefer*: 1/1. Condition: the provisional tail stays within 1 dB per band of the final level and 5 % of the final EDT (Table 6.1). A truncated tail fails on transients in rooms with an 8 s T60 [Hyp].
- D2, *can live with*: 1/1. It delays one change up to about 3.3 s. Whether that breaks condition 4 is Seat 3's call.
- D5, *can live with*: 1/2. The decay time is wrong until the new decays land, so one edit is heard as two changes.
- D1 at load, *cannot live with*: 3/3. **Yes, I count the tail gap as silence.** The tail component is silent for about 3.3 s. In a 100 m hall on a wet send that is a level drop many jnd deep, followed by a fade-in. If a host does not signal offline (R2), the gap is printed into the bounce, against NFR-6. D1 is acceptable for scenes with no saved tail.

**5. Evidence.**
- The jnds: Vorländer Table 6.1 [Observed, corpus].
- Noise level below 0.5 dB audible: Zotter and Frank §4 [corpus].
- ±1.5 dB with music: Kuttruff §7.3 [corpus].
- SE figures: AX41. AX16 errors: AX16.
- The mid-fade +3 dB: AX18's formula with ρ = 1 [Inferred].
- C80 about 3 dB under switching: my register, secondary [medium].
- For the researcher: R4, and how audible a 30 ms +3 dB swell is.

**6. Conditions of acceptance.**
- A0: lowered to 1/1 if A1 lands by 07c-2.
- B2 and B4: lowered to 0/1 with the SE ≤ 0.5 dB admissibility gate.
- B3: lowered to 1/2 only with a validated, scene-data-only predictor (Seats 2 and 9).
- C1: lowered to 0/1 by adding the guarantee where the source allows it, i.e. C5.
- C4: lowered to 1/2 by adding any numeric bound and a counter.
- D1: lowered to 1/1 if the load path uses D3 or D4, and offline always waits for the tail.
- D5: lowered to 1/1 if the interim tail's EDT is within 5 % of the final, or the switch is a single ramp.

**A4's acceptance test (automated).**
1. On layouts 4/5 and the absorbing-floor cube, the interim is neither silence nor the AX16 level.
2. With steady pink noise through a fully wet render (`--realtime-emulation`), measure the per-band level in 50 ms windows before and after the interim-to-final swap. Assert at most 1 dB in all 8 bands, with no mid-fade value above the louder endpoint. Do the same on speech.
3. A load with a matching key gives a step counter of 0 and no swap.
4. A forced inadmissible source is recorded.

Listening item for Maisara at 07c-2: a self-ABX of 16 trials on the capped layout-4 scene, using noise and speech.

**7. Hand-offs.**
- The crossfade law for a level-only step: Seat 3.
- The key's contents and the AX16 predictor: Seat 2.
- State size and load timing: Seat 5.
- Whether the user sees "settling" during a tail gap: Seat 6.
- Public wording about load behaviour: Seat 7.

**8. Premortem.** If C1 or C4 is chosen and 07c-2 raises W_max, layout-4-type rooms will "breathe" by 2 to 3 dB a fraction of a second after load. A mixer listening to the tail solo will report it first, as "the reverb jumps after opening".