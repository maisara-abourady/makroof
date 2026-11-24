# 42: Seat 1 on what a fallback band may be claimed as (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 1 POSITION (save as `/home/user/makroof/docs/review/phase-07c-2b/42-seat1.md`; I changed no files)

**1. Reading.** This is the 39-seat7 §8 hand-off and interrogator 41 Q2. The question is what a counted (a) band on the SE ≤ 0.5 dB fallback (window k ≥ 76, 3σ 1.49 dB) may be claimed as, when the verdict threshold is 1 dB. The cue it triggers is §2 rank 3, honesty of the evidence: the reference cannot resolve the threshold, so a "within 1 dB" result from it cannot be shown wrong.

**Arithmetic, redone** (Vorländer §11.2.5 Eq. 11.9, in the tracer.py L28 form σ = 4.34/√k):
- At k = 76: σ = 0.498 dB, so 3σ = 1.49 dB.
- For a difference of two fallback readings (L − R, or the two-radius check): 3σ = √2 · 1.49 = 2.11 dB.
- At k = 684: 3σ = 0.498 dB.

"Not breached" needs |d| + 3σ ≤ 1 dB. That cannot happen while 3σ > 1 dB. So a fallback band can support "breached" or nothing.

**2. Exact text** (for 07e-b scope 1, to replace "also counts, marked 'SE ≤ 0.5 dB only'"; it must be fixed before (a0) is dispatched):

> **Fallback bands (S1, 42-seat1).** For (a), a band on phase-07e's SE fallback (window k ≥ 76 but < 684 at either radius) is labelled 'SE ≤ 0.5 dB only'. Let d be the engine's value minus the tracer's (per-emitter late level, or L − R). Let U₃ be 3σ of the tracer quantity compared: 3 · 4.34/√k per emitter; for L − R, the root-sum-square of the two emitters' 3σ. Such a band may be claimed only as follows:
> - **breached**, if |d| − U₃ > 1 dB at both radii;
> - **not decidable** otherwise. It is never 'not breached', whatever d is, because U₃ ≥ 1 dB. It takes the 'not decidable' route for that band (scope 1, step 2) and opens no gate.
> - **print only**, with no verdict, if the two radii disagree beyond their combined 3σ, or if k < 76 (not counted).
>
> 'Not breached' for (a) may be claimed only for bands gated at k ≥ 684 at both radii. No AX44 reversal is recorded as 'not fired' from a fallback band. This rule is fixed before (a0) runs. It is never changed after the prints are seen.

Seat 2's case of an engine about 6 dB low against a tracer that is near the GA value still rules "breached" under this text (6 − 1.49 > 1). The case it rules out is the one file 41 names: an engine-to-tracer difference near 0 being read as "not breached".

**3. Tension now / later**

| option | as in file 40 (fallback counts for "not breached") | with the text above |
|---|---|---|
| H4+G | 0 / **2** | 0 / 1 |
| H3+G | 0 / **2** | 0 / 1 |

- **Later 2 under file 40's text.** A false "not breached" opens the gates. Item 15's stimuli (my acceptance test, F3/F4) would then be built on an engine whose (a) level was never resolved. The first signal would be a heard step when a source is dragged into a corner, after 08-3 listening. Undoing it would mean a fix phase plus M3-8's rebuild and re-hear.
- **Later 1 with my text.** This is the residual of 29-seat1 §4, the same under every home: a ruled fix fires M3-8.
- The fallback text belongs to 07e/07e-b, which are common to all homes. **My row does not separate H4+G from H3+G.**

**4. Evidence**
- 3σ arithmetic: Vorländer §11.2.5 Eq. 11.9, redone above. It agrees with 41 Q2.
- Vorländer §11.2.5 (case 2) uses a 1 dB limit for G. "1 dB ≈ 1 JND of G" comes from my register: ISO 3382, static halls, medium confidence. It is not load-bearing here. This is a rule about whether the reference can resolve the threshold, not about audibility, and audibility is never a ground for "not breached" (07e-b, S1).
- Researcher: nothing needs checking.

**5. Conditions.** File 40's fallback clause goes from later 2 to 1 if the text above replaces it in both places: the Item A1 cap clause, and the Item A2 scope 1 sentence.

**6. Hand-offs**
- **Decider (PRD; file 41 Q3, AX44's τ):** τ = 0.25 dB is below 3σ at both gates (0.50 and 1.49 dB). The reversal can be claimed as fired only where |d| − U₃ > τ. Below that, "not testable" should be recorded, never "not fired".
- **Seats 5 and 7:** whether to plan more particles for bands that are not decidable, inside the 24 h cap.

**7. Premortem.** If the fallback band is allowed to count for "not breached" and that fails: the ruling says (a) is not breached on a reference that could not see 1 dB, 08-4 and item 15 go ahead, and a mixer dragging a source into a corner is the first to notice the level drop.

