# 36: Seat 2 on (a)'s reference and AX44/B15 (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 2 POSITION (follow-up on M3-H: interrogator file 35, Q1 and Q2). Read-only. For saving as /home/user/makroof/docs/review/phase-07c-2b/36-seat2.md

**1. Reading.** Two questions. (1) Finding (a) has no admissible reference under my merged scope-1 text, so what should the reference be, and what does "not decidable" do to the gates? (2) Is a breach ruling for (a) compatible with AX44/B15 as Maisara accepted them, or does it amend them? Cues: §4 cue 6 (a claim of accuracy needs a reference) and cue 3 (non-diffuse geometry); situation S6 (non-circular test).

**2. Q1: the reference for (a).** My own text caused the gap. "Receiver clear of every face" turned a default setting into a rule. The tracer's 0.5 m is only the default `R_D` (tracer.py L42, "default 0.5 m, B11"). Phase 05h already ran the tracer at a 0.1 m corner listener with a smaller sphere: r_d 0.05 m at W1 (0.1, 0.1, 9.9), at 16 M particles, SE 0.27–0.32 dB (docs/review/phase-05h/14-orchestrator-M2-near-corner.md L31–39). That is AX44's own pre-registered "independent near-corner reference (Seat 2)". I withdraw "receiver clear of every face / never a reference at a near-face listener". Replacement text for 07e scope 3 and 07e-b scope 1:

> "The reference for (a) is the seeded tracer at (a)'s exact geometry, with its counting sphere wholly inside the room: r_d below the listener's clearance, at two radii (0.05 and 0.025 m), as AX44's near-corner reference (05h file 14). A band counts only where both radii are gated (k ≥ 684) and agree within their combined 3σ. Eq. 5.42 is not a reference for (a): the room is non-diffuse (Kuttruff §5.7, Table 5.2 case 4). Required prints that are never references: (i) the listener moved to ≥ 0.70 m from every face, L unchanged (both-near off; tracer at r_d 0.5 m), which separates the source-side cause (the image-source set at a corner source) from the AX44 both-near branch; (ii) the engine's E_fwd and E_rev, uncapped, w = 1 and w = 0, which separates the cap from w. The engine is never its own reference (circularity, S6). The diffuse control stays (c)'s tool only. An emitter swap tells nothing here, because GA reciprocity leaves both ends near."

Cost [Inferred]: the number of detections scales with r_d², so k ≥ 684 at r_d 0.05 m needs about 100 × N0 = 152 M particles (N0 = ceil(254 × 6000) = 1,524,000), and about 610 M at 0.025 m. That is an offline one-off under 07e's manual-job rule. If it is too expensive, 07e may relax the gate for (a) only: a 1 dB threshold against a −6.2 dB reading stays decidable while the reference's SE is ≤ 0.5 dB.

**What "not decidable" does to the gates:**

> "'Not decidable' never opens a gate. The loop first asks for the named print (the tracer at more particles, under B11's doubling rule). If (a) is still not decidable after that, whether the gates open with (a) recorded as a named B15 item is a board ruling with Seats 1, 4, 5 and 7, never a default (as scope 2's last bullet)."

**3. Q2: AX44/B15.** The answer has two parts.
- **The classification fits AX44.** AX44 concedes "both-near reads low" and makes "no accuracy claim" at both-flagged ends and at layout-4/5-type corners. It does not say these scenes render correctly, and its "requirements" list at decision time included NFR-8 (05b2 file 25 L319). Its own reversal is "the near-corner reference contradicts NW-4C by more than τ". So a breach ruling against the near-corner reference carries out a clause she accepted; it amends nothing. "Cause, never explanation" also fits: AX44 accepts the deficit as a debt and does not explain it physically.
- **Scheduling amends B15.** If the deficit is the AX44 both-near/capped branch inside C13's −0.35 to −6.72 dB envelope, a "fix before 08-4" changes B15's "none scheduled" and the debt she accepted ("flagged, not bounded"). That needs a separate FOR MAISARA answer with an `AMENDS her decision of 2026-11-10` line. I withdraw "AX44 names the receiver side only" (K16): L167's mechanism is receiver-side, but its disclaimer covers both ends.

Proposed 07e-b text:

> "The ruling quotes AX44 (L167: GA-limit paragraph, debt, reversal) and B15 (L408). A breach of (a) is recorded as the AX44 reversal firing. If print (i) shows that the deficit survives with the listener clear, or if it lies outside C13 §2's envelope, the cause is not the AX44 both-near debt: it is an ordinary breach, and the fix gate applies. Otherwise the order of the fix (B15 before 08-4, or B15 left unscheduled with U shown) goes to Maisara as a separate FOR MAISARA answer with the AMENDS line. Until she answers, the gates hold."

My seat can live with either of her answers. U fires at (a) (cap hit asserted), so the edge is stated (my §2 criterion 5).

**4. Ratings for H4+G.** Now 1. Later 1 if both texts above are adopted. Later 2 if (a) keeps no reference, or "not decidable" keeps no gate consequence: the gates would open unruled.

**5. Evidence.**
- [Observed] tracer.py L21, L42; 05h file 14.
- [Observed] BUILD_PLAN L167, L408.
- Kuttruff §5.7, as checked by the interrogator (file 35); I did not re-read it.
- Particle scaling: [Inferred]. Researcher: please confirm that the tracer's k scales with r_d².

**6. Conditions.** The H4+G later cell drops from 2 to 1 when the reference text and the gate text above are adopted.

**7. Hand-offs.**
- Seat 9: does it accept the near-corner tracer for a non-diffuse room?
- Decider: the FOR MAISARA answer.
- Seat 5: cost of the manual job.

**8. Premortem.** If (a) is left "not decidable" with no consequence, item 15's stimuli are built on a corner that reads 6 dB low. Seat 1 notices first, in the 08-3 listening.
