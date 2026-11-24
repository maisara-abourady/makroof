# 4-seat4: Seat 4, round 2 on M3 (V1-W cell, F1–F4, item 15)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 4 POSITION (round 2 on M3, phase 07c-2b; for docs/review/phase-07c-2b/4-seat4.md)

I am read-only, so I have not written this file. The orchestrator saves this text.

No new acoustic fact is load-bearing in this round. Everything below is read from the plan text and the decider's file 2. I did not re-check the corpus.

**(1) My V1-W cell: confirmed at 0/1.**
- **Now is 0.** The 07c-2b chain is omni and diotic. No delivery quantity is at stake.
- **Later is 1.** Under V1-W, 08-3 meets both of my round-1 conditions:
  - (ii) is S-B\*. It is the only binaural run with a present early part, it uses the default listener position, and F2 gives it an omni baseline. This was my V1 → V1′ condition.
  - (i) is both_wall, and it now has an omni baseline (F1). This removes my V1 objection that the binaural S-W had no omni baseline. It carries condition (b)'s label verbatim, and the sentence "never counted as binaural evidence for the class".
- **What keeps it at 1 rather than 0:**
  - B14 (no headphone compensation).
  - A static, generic head.
  - The M3-8 trigger. O4 is expected to fire it before 08-3, which voids the cross-chain comparison unless the omni family is rerun.
- Each of these is covered by debt row 4, which I accept as written.
- **The fallback path keeps the label working.** The label's trigger is conditional ("< 0.70 m from a face, AX44 d_L"). So listener_corner and listener_edge get it, and emitter_wall (listener at the default position) correctly does not.

**(2) F1–F4 can each reverse AX47, including (i): confirmed.**
- The (i) label limits what a non-detection means. It does not limit what a detection means.
- A and B pass through the same HRTF pair. Their difference is the tail step filtered by the shipped binaural chain. A detection there is a detection in what the plugin outputs at a placement FR-3D-5 allows (L75). That the HRTF is invalid near a wall cannot create a difference that the shipped output does not contain.
- The one way a near-wall artefact could produce a false detection is a click or fade artefact in one ear. Item 15 closes that by running item 6 (HF-W included) and `[ax47-midfade]` per ear before any stimulus.
- So the asymmetry is right: a detection counts, and a null is chain comparison only.

**(3) Item 15 (M3-4) checked against my draft and conditions.**

| element | status |
|---|---|
| Item 6 (HF-W) and `[ax47-midfade]` per ear | met (HF-W already runs "on every output channel") |
| M2 gap and Q5 per ear | met |
| D/R per ear | met |
| `hrtfId` and set identity string | met |
| Headphone: same wired model and level, no virtualiser | met; one text fix (b) below |
| B14 wording, "static, uncompensated (B14), generic HRTF", plus "empty early part (AX21)" on (i) | met |
| Trigger: rebuild; cross-chain comparison void unless the omni family is rerun on the current engine | met; it matches my "rerun or void" wording. "Identical" then reads as identical seeds, programmes, steps and trials on a rebuilt IR, which is correct |
| AC6 line | acceptable as written; I withdraw part of my round-1 wording (c) |

Two text fixes. Neither raises my rating, but I want both:
- **(a) Restore one sentence from my draft that M3-4 dropped:** "Neither family is cited for externalisation or plausibility, and L4/L5 are not judged on these scenes."
  - The (i) clause covers only (i). S-B\* in (ii) has no equivalent.
  - A plausibility claim needs a real-loudspeaker reference (my §2 rank 2, and §1 "what I never count as success").
  - Without the sentence, my premortem path stays half-open: a binaural null on (ii) could be read as evidence for 08-3 L4 or L5.
- **(b) Say "level setting, recorded".** The 07c-2b record and the 08-3 record should each state the headphone model and the level setting. Otherwise "the same" cannot be checked afterwards.

**(c) Correction to my own round 1.**
- I asked for "per-ear parity within ±1 dB (AC6)". Phase-08-3 L68 defines AC6 as "binaural vs omni per-band energy within ±1 dB" without saying per ear.
- A per-ear, per-band ±1 dB assertion would fail at high frequencies for any lateral direct sound, through ILD, whatever the chain's correctness. That reasoning is [Hyp] and my persona has no incident for it.
- So keep item 15's AC6 line as written. If anything is added, add per-ear per-band energy as a print, not an assertion.

**Hand-offs.**
- **Seats 1 and 5:** if the trigger fires before 08-3 and the rebuilt S-W or S-B\* then fails a seal gate (for example, it is no longer capped after the W_max raise), item 15 does not say which scene 08-3 uses. The rule could be the M3-1 fallback order, rerun on the current engine.
- **Seats 1, 5, 6 and 7:** α for F3 and F4. Not mine.

**Premortem.** If (a) is not restored, the risk is this: 08-3 records "not detected, binaural, S-B\*", someone cites it at L4 as evidence that the binaural room surrounds the listener, and Maisara finds the gap only when a producer reports in-head reverb on a preset.
