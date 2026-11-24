# 38: Seat 2's merged (a) text ((a0) near-corner tracer, (a1), (a2); gate split by cause)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION (Lead merge for M3-H: 36-seat2 + 36-seat9). Read-only; I changed no files. To be saved as /home/user/makroof/docs/review/phase-07c-2b/38-seat2.md

**1. Reading.** Write one text that combines my near-corner tracer at (a)'s exact geometry with Seat 9's (a1) diffuse control and (a2) moved listener, plus the "not decidable" gate and the AX44/B15 split by cause. Cues: cue 6 (a reference has to be named), cue 3 (layout 4 is non-diffuse), S6 (no circularity).

**Reconciliation.**
- Seat 9's (a1) is admissible because it is a diffuse control scene, not layout 4. That makes Eq. 5.42 valid there, so it does not conflict with my point that Eq. 5.42 is no reference at layout 4 itself.
- I adopt 0.75 m for the moved listener, in place of my ≥ 0.70 m.
- I adopt the record list in Seat 9's (3), and keep my rule that the record is a board ruling.
- The tracer is the only reference at (a) itself. (a1) and (a2) are references for their own placements only.

**2. Merged text**

*07e scope 3 (a), new bullet:*
> "For (a), three references are required, each on its own placement:
> - **(a0) Near-corner tracer, at (a)'s exact positions.** The seeded tracer's counting sphere sits wholly inside the room at r_d 0.05 m and r_d 0.025 m (AX44's near-corner reference, 05h file 14). A band counts only where both radii are gated at k ≥ 684 and agree within their combined 3σ. If 0.025 m cannot reach the gate in the manual job, that band is gated for (a) only at SE ≤ 0.5 dB, and the run says so.
> - **(a1) Diffuse control, as for (c),** with (a)'s exact emitter and listener positions.
> - **(a2) Moved listener.** Same room and emitters; the listener is moved along its corner diagonal to 0.75 m from each of its three faces (clear of AX44's 0.70 m both-near flag and the tracer's 0.5 m radius). The seeded tracer runs at r_d 0.5 m, gated at k ≥ 684.
>
> Printed per band, 63 Hz–8 kHz:
> - the late level per emitter and L − R, for the engine in (a), (a1) and (a2), and for the tracer in (a0) and (a2);
> - for each emitter in each case: w, the both-near and capped flags, and U;
> - the engine's E_fwd and E_rev at (a), uncapped, at w = 1 and w = 0.
>
> The engine is never its own reference. An emitter swap is never a reference (S2, S9)."

*07e-b scope 1, replacing the "For (a)" bullet:*
> "For (a), the reference comes from 07e's (a0), (a1) and (a2). Layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4), so Eq. 5.42 holds only in (a1): there L − R = 0 dB at equal times and equal power. A band is used only where the reference's uncertainty is under 0.5 dB. Verdicts:
> - (i) if the engine at (a) differs from (a0) by more than 1 dB in a counted band (the per-emitter level or L − R), (a) is breached;
> - (ii) if L − R in (a1) lies more than 1 dB from 0, (a) is breached and the cause is the engine's;
> - (iii) if the engine's L − R in (a2) differs from the tracer's by more than 1 dB, (a2) is ruled a breach as its own placement, with its cause;
> - (iv) if every band of every case is within 1 dB, or no band of (a0) counts, then (a) is 'not decidable'.
>
> The 29-seat9 §5 flatness claim is printed as support, never as the verdict. The ruling names the cause, never its explanation."

*07e-b scope 1, gate text:*
> "'Not decidable' is never 'not breached' and opens no gate by itself.
> 1. The loop first asks for the named print: (a0) at more particles, under B11's doubling rule.
> 2. If (a) is still not decidable, the gates stay shut until a board ruling with Seats 1, 4, 5 and 7 records (a) under AX44 as Maisara accepted it. The record requires all of the following:
>    - U raised at (a) and asserted in a test;
>    - the AX44 note shown at (a) in Phase 11;
>    - no fixture or Phase 12 preset default within 0.70 m of a layout-4/5-type corner (AX44 Seat 6 (ii));
>    - (a) entered as evidence on B15;
>    - the 'not decidable' listed under 'Decided for Maisara'.
>
> On a breach, the ruling quotes AX44 (L167: the GA-limit paragraph, the debt, the reversal) and B15 (L408). A breach against (a0) is the AX44 reversal firing; it amends nothing. The gate step then splits by cause:
> - **Outside AX44's accepted debt.** Any one of these: the deficit survives in (a2); verdict (ii) fires; the deficit lies outside C13 §2's −0.35 to −6.72 dB; U is silent; or the cause is the ISM set at a corner source, the AX22 fallback or the t_mix,e rule. This is an ordinary NFR-8 breach, and the fix gate applies.
> - **Inside it** (the both-near w or the capped branch, U raised, inside the envelope). Ordering a fix before 08-4, or leaving B15 unscheduled with U shown, goes to Maisara as a separate FOR MAISARA answer with the line `AMENDS her decision of 2026-11-10`. The gates hold until she answers."

**3. Session size.** 07e stays at two S sessions.
- (a1) is one render. (a2) needs about 1.5 M particles (N0 = 1,524,000).
- (a0) needs about 152 M particles at 0.05 m and about 610 M at 0.025 m [Inf: k scales with r_d², researcher to confirm]. This is an offline manual job under 07e's existing rule, not session time.
- The SE ≤ 0.5 dB fallback in the text caps the cost.
- If the 0.025 m job overruns its run window, the run is split into 07e-c under the two-session rule. Seat 5 sizes the job [Hyp].

**4. H4+G ratings for the merge.**
- **Now: 1.** The cost is (a0)'s compute.
- **Later: 1.** (a) is either ruled or recorded with U, the note and the preset clearance. The remaining 1 is Seat 9's residual: (a) may end up flagged rather than fixed.

**5. Conditions.** Later 1 → 0 only if B15 gets an owner phase before 12-2. That is the FOR MAISARA question.

**6. Evidence.**
- [Observed] tracer.py L21, L42; 05h file 14 L31–39; BUILD_PLAN L167, L408.
- Kuttruff §5.7 Table 5.2 via file 35; I did not re-read it.
- [Hyp], for the researcher: that Eq. 5.42 gives equal late level at a GA receiver 0.1 m from the faces in (a1); the r_d² scaling.

**7. Hand-offs.**
- Decider: the FOR MAISARA answer if the cause falls inside the debt.
- Seat 5: (a0)'s run time.
- Seat 6: the note shown at (a).

**8. Premortem.** If (a0) is cut for cost and (a) stays "not decidable", a producer drags a source into a corner and hears the tail about 6 dB low. Seat 1's ABX at 08-3 hears it first.
