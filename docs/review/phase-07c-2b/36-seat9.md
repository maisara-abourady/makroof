# 36: Seat 9 on (a)'s reference and AX44/B15 (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 9 POSITION (M3-H follow-up on file 35 Q1/Q2; read-only, I changed no files; to be saved as /home/user/makroof/docs/review/phase-07c-2b/36-seat9.md)

**1. Reading.** Four questions: (1) Seat 2's tracer bar, (2) the reference for finding (a), (3) what "not decidable" does to the gates, and (4) whether ruling (a) a breach amends AX44. Cues that apply: S2 (the room is non-diffuse, so Eq. 5.42 is not the reference), S8 (a known bias offered as an explanation), and "late change after commitment" (AX44 is her accepted decision).

**Correction I own.** In 32-seat9 §2 I wrote that AX44's GA limit "is written for the receiver side". That is imprecise and I withdraw it. The mechanism sentence in L167 is about the receiver. The disclaimer that follows it, "No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners", covers both ends and covers (a)'s emitter.

**2. Answers**

**(1) Yes, I accept the bar.** The tracer is used only where its receiver centre is at least 0.5 m from every face (tracer.py L21, L42). A receiver sphere that crosses a face catches fewer particles than its stated volume, so the result is biased low by geometry. No 3σ gate catches that, because the 3σ gate measures scatter, not bias [Inf; H]. I would tighten it in one place: for (a) the moved listener should sit at 0.75 m, so that it is also outside AX44's 0.70 m both-near flag.

**(2) The reference for (a).** I reject the emitter swap as a reference. Both readings come from the same estimator, so it cannot show a bias they share. The key fact is that L and R are heard at one listener. In a diffuse geometric-acoustics (GA) field, whatever the listener's corner does, it does to both emitters equally. The GA-internal reference for L − R is therefore 0 dB at equal times and equal power (Eq. 5.42), even at 0.1 m from the faces. The §5.6 caveat that ᾱ = 0.28 is not small moves the absolute level and should cancel in the difference [Inf; researcher to verify].

*Text to add to 07e scope 3, as a new bullet:*
> "For (a): (a1) the diffuse control as for (c), with (a)'s exact emitter and listener positions; (a2) a moved-listener variant: the same room and emitters, the listener moved along its corner diagonal to 0.75 m from each of its three faces (outside AX44's 0.70 m both-near flag and clear of the tracer's 0.5 m receiver radius), with the seeded tracer reference gated at k ≥ 684 as for (c). Printed per band, 63 Hz–8 kHz: L − R for the engine at (a), in (a1) and in (a2), and for the tracer in (a2); for each emitter in each case, w, the both-near and capped flags, and U (S9)."

*Text to replace the "For (a)" bullet in 07e-b scope 1:*
> "For (a), the reference comes from phase-07e's (a1) and (a2). Layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4), and the tracer is barred at (a)'s listener (S2, S9). In (a1) the reference is L − R = 0 dB at equal times (Eq. 5.42, equal power, one listener). In (a2) it is the tracer's L − R. Verdicts:
> (i) if L − R in (a1) lies more than 1 dB from 0 in any band where the reference's uncertainty is under 0.5 dB, then (a) is breached and the cause is the engine's;
> (ii) if the engine's L − R in (a2) lies more than 1 dB from the tracer's, then (a2) is ruled a breach as its own placement, with its cause;
> (iii) if both are within 1 dB, then (a) is 'not decidable' (scope 1, 'not decidable' below).
> The flatness claim 'flat within ±1 dB from 125 Hz to 4 kHz → an engine effect' (29-seat9 §5) is printed as support, never as the verdict."

**(3) What "not decidable" does to the gates.** Text to add to 07e-b scope 1:
> "'Not decidable' is never 'not breached' and opens no gate by itself. The gates stay shut until the loop either:
> - asks for a named print that forms a reference; or
> - records (a) under AX44 as Maisara accepted it. That record requires all of the following: U raised at (a) and asserted in a test; the AX44 note shown there in Phase 11; no fixture or Phase 12 preset default within 0.70 m of a layout-4/5-type corner (AX44 Seat 6 (ii)); (a) entered as evidence on B15; and the 'not decidable' listed under 'Decided for Maisara' (S9)."

**(4) Ruling and AX44.**
- **The ruling itself is compatible with AX44.** AX44 makes "no accuracy claim" at (a)'s geometry and admits it "reads low, flagged, not bounded". It never says NFR-8 holds there. Calling (a) breached describes the deficit truthfully; AX44 had only declined to claim accuracy there.
- **The consequence is what can amend her decision.** If the ruled cause lies inside AX44's accepted debt (the both-near weight w or the capped branch, U raised, a deficit inside C13 §2's −0.35 to −6.72 dB), then making a fix mandatory before 08-4 schedules B15, which L408 records as "none scheduled". That amends her decision. It needs a separate FOR MAISARA answer with the `AMENDS her decision of 2026-11-10` line.
- **Causes outside that debt** (the ISM set at a corner source, the AX22 fallback, the t_mix,e rule, or any spread in (a1) or (a2) where U is silent) are ordinary NFR-8 breaches. Their fix is ordered with no amendment.
- So the 07e-b sentence "cause, never its explanation" stands for the verdict. Only the gate step needs this split by cause.

**3. Tension (H4+G).**

| Text | Now | Later |
|---|---|---|
| My texts (2)–(4) adopted | 0 | 1 |
| File 33's text as it stands, with no admissible reference for (a) | 0 | 2 |
| "Not decidable" with no gate consequence | 0 | 2 |

- **Why 1 with my texts.** (a) may end up flagged rather than fixed: a dip of about 6 JND of G that a drag can reach. U and the presets' distance from the corner contain it.
- **Why 2 without them.** The gates open with (a) unruled, and 12-2's corner presets are built on that tail.

**4. Evidence.**
- Tracer radius and gate: from the code, tracer.py L21, L28, L42.
- Layout 4 is non-diffuse: Kuttruff §5.7, Table 5.2 case 4, as checked in file 35.
- AX44 disclaimer and debt: BUILD_PLAN L167. B15: L408.
- **[Hyp], for the researcher:**
  - that Eq. 5.42 gives equal late level for the two emitters at a GA receiver 0.1 m from the faces;
  - that the §5.6 ᾱ caveat cancels in L − R.

**5. Conditions.**
- Later 2 → 1: adopt the (a1)/(a2) texts and the "not decidable" consequence.
- 1 → 0: B15 gets an owner phase before 12-2. That is a FOR MAISARA question.

**6. Hand-offs.**
- Decider: the reading of "layout-4/5-type edges and corners" (one end or both?), and the FOR MAISARA answer if the cause is w or the capped branch.
- Seat 2: whether 07e stays two S sessions with (a1) and (a2) added.
- Seat 6: the note shown at (a).
- Seat 1: audibility, if deferral is weighed.

**7. Premortem.** If (a) comes out "not decidable" and the gates open anyway, a producer drags a source into a corner and hears the tail drop by about 6 dB. Seat 1's ABX at 08-3 is the first to hear it.
