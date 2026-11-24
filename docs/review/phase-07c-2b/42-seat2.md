# 42: Seat 2 on the fallback band, AX44's tau and the N rule (M3-H)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

I didn't save the file because this seat is read-only: please save the text below as `/home/user/makroof/docs/review/phase-07c-2b/42-seat2.md`. I didn't open the corpus myself. Vorländer §11.2.5 is cited from the interrogator's check (file 41 L84), and I redid the arithmetic.

SEAT 2 POSITION

**1. Reading.** This round fixes three things in the 07e-b text and asks me to rate H4+G and H3+G again:
- **Q2:** what a band on the window k ≥ 76 fallback may support as evidence.
- **Q3:** what is recorded when the AX44 reversal (τ = 0.25 dB) fires below the 1 dB breach threshold.
- **Q4:** what replaces the "B11 doubling" step.

Cues it triggers: S6 (a claim of accuracy needs a reference precise enough to settle it), P3 step 2 (don't fit or extend after the result is seen), and §17 "fitting, then scoring".

**Arithmetic, redone (σ = 4.34/√k):**
- k = 76: σ 0.498 dB, 3σ 1.49 dB. The L − R difference or the two-radius check gives 3·√2·0.498 = 2.11 dB.
- k = 684: σ 0.166 dB, 3σ 0.50 dB. For L − R, 0.70 dB.

**Q2: exact text.** Replace the scope 1 fallback sentence ("For (a) only, a band on phase-07e's SE fallback … marked 'SE ≤ 0.5 dB only' in the ruling") with:

> "For (a) only, a band on phase-07e's SE fallback (window k ≥ 76 but < 684 at either radius) can establish 'breached' and nothing else. It does so only when, at both radii and with the same sign, |d| > 1 dB + 3σ_d. Here d is the engine minus (a0) for the per-emitter late level or for L − R. σ_d = 4.34/√k for a per-emitter level, or √(σ_L² + σ_R²) for L − R, each taken from that radius's window k. That is |d| > 2.49 dB per emitter, or > 3.11 dB for L − R, at k = 76. Otherwise the band does not count. It never counts toward 'not breached', and it never lifts verdict (iii): if no band of (a0) counts at k ≥ 684 and no fallback band establishes a breach, (a) is 'not decidable'. A fallback band that establishes a breach is marked 'SE ≤ 0.5 dB only; two-radius check resolves only 3·√(σ_0.05² + σ_0.025²) dB' in the ruling. For 'not breached', a band counts only when both radii are gated at k ≥ 684."

The Seat 1 hand-off on "what a band counted 'SE ≤ 0.5 dB only' may be claimed as" narrows to: whether a breach established on such a band may be quoted outside the ruling.

**Q3: exact text.** Insert after verdict (iii), and replace "A breach against (a0) is the AX44 reversal firing; it amends nothing." with:

> "**AX44's reversal is tested separately from NFR-8.** AX44 (L167): 'the near-corner reference contradicts NW-4C by more than τ'. AX42 (L165): 'τ = 0.25 dB per case and band'. The test is applied per emitter's late level in every band counted at k ≥ 684, never on L − R. In each such band the ruling records one of three results:
> - 'AX44 reversal: fired', when |d| > τ + 3σ_d (|d| > 0.75 dB at k = 684);
> - 'AX44 reversal: indicated, not resolved (reference 3σ = x dB > τ)', when τ < |d| ≤ τ + 3σ_d;
> - 'AX44 reversal: not indicated', when |d| ≤ τ.
>
> The engine's achieved SE is printed beside each result.
>
> A band with τ < |d| ≤ 1 dB is 'not breached' under NFR-8. That result alone opens or holds no gate.
>
> If the reversal fired, AX44 goes back to the board as its own decision, outside this phase's gates. Any change to AX44, and any scheduling of B15, is a FOR MAISARA answer with `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`. That decision's order relative to 08-4 is set by its own ruling, never by default.
>
> A breach (> 1 dB, resolved) also fires the reversal. Neither the breach nor the reversal amends anything by itself."

In M3-H-R1, the reasoning point that "its reversal clause asks for exactly that check" becomes: "its reversal clause asks for the τ check, which 07e-b records per emitter and band, apart from the 1 dB NFR-8 verdict."

**Q4: exact text.** Replace step 1 with:

> "1. The loop first reads (a0)'s run record. (a0)'s N per emitter and radius is fixed by phase-07e's pilot rule and cap before any (a0) result exists. It is never raised after results are seen (B11's clause, L404, applied to (a0); B11's per-bin doubling to 16·N₀ does not apply to (a0)). The only further print allowed is completing a run that stopped short of its pre-registered N (a failed shard, or quota): particles are added, never redrawn, and the seed is unchanged. This stays within phase-07e's 24 h cap and 36 h ceiling (S7)."

**2. Ranking.**
- H4+G with the three texts: *prefer*.
- H3+G with the three texts: *can live with*.
- Either option without the Q2 or Q4 text: *can live with* only under the conditions in section 6.

**3. Tension now.**
- H4+G: 1, the compute for (a0).
- H3+G: 1, the same cost.

**4. Tension later.**
- **H4+G: 1.** (a) may end up flagged rather than fixed (38-seat2 §4). The Q2 text makes "not decidable" likelier, so the record path is the likelier route. That is the same debt, not a new one. Undoing it means B15 plus a D5 golden round. Evidence arrives with 07e-b's ruling.
- **H3+G: 1, for the same reason.** 07e and 07e-b are common to both homes, so my row does not separate them.
- **Without the Q2 text: later 2.** A "not breached" verdict resting on a 1.49 dB 3σ (2.11 dB for L − R) passes a deficit of up to about 2.5 dB.
- **Without the Q3 text: later 2.** The independent near-corner reference AX44 assigned to Seat 2 would be produced, and its τ outcome would go unrecorded.
- **Keeping "B11 doubling": later 2.** Read as a licence to add particles after the result is seen, it is optional stopping.

**5. Evidence.**
- σ = 4.34/√k: tracer.py L28 [from the code]. Vorländer §11.2.5 Eq. 11.9 per file 41 L84 [interrogator's corpus check, not reread here].
- τ = 0.25 dB per case and band: AX42 L165. The reversal wording: AX44 L167. "N … never changed after results are seen": B11 L404 [plan, quoted].
- The near-corner reference is Seat 2's: AX44 L167, "Before the goldens: the independent near-corner reference (Seat 2)".
- Resolving τ at 3σ = 0.125 dB needs k ≈ 10,800, about 16× the k = 684 particles. At the interrogator's mid case of 7.8 h per run (file 41 L86) that is far over the 24 h cap. The mid case is [Hyp].
- The claim that spatial-averaging bias is negligible for spheres of 0.05 m and 0.025 m lying wholly inside the room, in the late GA field: [Hyp]. **Researcher:** please verify it. The Q2 text does not depend on it, because it requires both radii.

**6. Conditions of acceptance.**
- Each later 2 above drops to 1 when that question's text is adopted as written.
- Of the three, Q2's "never toward 'not breached'" is the one I won't trade away. It follows from my persona's rule "no claim without a measurement path".

**7. Hand-offs.**
- Seat 1: whether a fallback-established breach may be quoted outside the ruling.
- Seats 5 and 7: whether completing a run that stopped short fits the 36 h ceiling.
- The S5 H3+G later cell belongs to Seat 5. I don't read it.

**8. Premortem.** If the fallback is allowed to count toward 'not breached', a corner 2 dB low gets ruled correct. A producer dragging a source into a corner hears its reverb drop. Seat 1's item-15 listening, or a user, notices first.
