# Phase 05b session 2: decisions for Maisara to accept or veto, and four questions

2026-11-10. The board's decision loop has finished for all six subject matters (D-T5, D-T4, D-T1, D-T2, D-T6, D-T3). Every
decision survived the interrogator, in its final round, with nothing contested. Nothing is applied to the plan, and no
`src/sim` code is written, until you answer (`/fix-plan` step 3).

Final texts:
- D-T5 and D-T4: `13-decider-round4-T4a-final.md` (final summary) with `15-interrogator-T5-T4-round3.md`.
- D-T1, D-T2 and D-T6: `34-decider-round4-final-T1-T2-T6.md` plus `37-decider-round4-addendum.md`, with
  `39-interrogator-round3-final-T1-T2-T6.md`.
- Interrogator items 1 and 2 of the final round, which were to be fixed before this packet, are applied in Q1 and Q2 below.

## Part 1: decisions to accept or veto

The "worst-off" column gives the most strained seat, as tension now / later on a 0–3 scale (3 is a veto).

| id | what it decides, in one line | worst-off seat |
|---|---|---|
| D-T5.1 | The tail level comes from the propagated diffuse energy in all 8 bands (the validated model), replacing AX16's per-path entries. A tracer check runs at 125 Hz, 4 kHz and 8 kHz. | 1 |
| D-T5.2 | The image-count cap logic (AX22) is unchanged. | 1 |
| D-T5.3 | Phase 08 gets the band energies and the mixing time only. A directional tail waits behind a blind test. | 1 |
| D-T5.4 | Outdoor scenes get a generic result (ground scatter) with a −60 dB check. No preset-specific logic. | 1 |
| D-T4a | Memory ceiling: ≤ 1 GB transient per diffuse solve, one solve per process at a time, through a three-class gate (host calls first). | 1 |
| D-T4b | AQ10's W1/W2 include the whole diffuse computation. | 1 |
| D-T4c | Memory is gated at the 100 m builds. Full rebuilds, restore and bounce times are recorded, not gated. | Seat 5, 1/2 |
| D-T1.1 | The estimator is a seeded Monte Carlo of the same model, with a determinism package (identical on three OSes) and agreed public wording. | 1 (under Q1 (a)) |
| D-T1.2 | The random key is fixed, so the noise seed never moves the tail level. | 1 |
| D-T1.3 | Path count: a pilot sized in work, a fresh final range, a fixed work cap, blocks of 64 histories, integer arithmetic. The two limits' values are Q2. | Seat 1, 2/2 |
| D-T1.4 | C++ must match the reference within 0.25 dB per band. The shipped target precision is SE 0.083 dB. | 1 |
| D-T1.5 | 70 pre-registered agreement cases (560 case-bands), family error 1 %, no reseeding. | 1 |
| D-T1.6 | Near walls: blend the two ends of the path, so there is no model change. An "approximate" note shows only where an estimate is actually weak, never at a default placement. | Seat 1, 1/2 |
| D-T6 | In rooms with the same material on every surface, the change is bounded and gated against the reference. The public wording follows Seat 7's rules. | 1 |
| D-T3 | Not needed: the estimator covers the whole contract range of room sizes. | – |

**Where a seat gave the most:**
- **Seat 1 (perception)** carries a later 2 on D-T1.3 and D-T1.6. In rooms with one fully absorbing face and fully diffuse
  walls (synthetic test rooms), the tail level becomes a random estimate of about ±0.2–1.3 dB, replacing a systematic
  +3.9 / −1.2 dB.
- When the listener and a source are both against walls, the estimate can read low. It is flagged "approximate", not bounded.

## Part 2: four questions

**Challenge 1 (from D-T4c).** Should the CI check of the synchronous state restore at 100 m and 96 kHz become blocking?
- The limit is pluginval's 30 s watchdog over 14 restores, about 2.1 s per restore. Today a restore takes 1.51–1.88 s.
- "Yes" amends AQ10 ("full rebuilds recorded, not budgeted").
- "No" keeps it as recorded debt.

**Q1 (D-T2). How does your 1 % rule (AX36) apply to the new estimator?**

You accepted AX36 for patch size, where the error is systematic. The new estimator's error is random and measured.

**(a) To the method's bias, checked in CI.**
- **What users get:** the 0.083 dB target precision (0.08 of the smallest audible level change) at default and one-end
  placements wherever the work limit does not bind. That holds at n\*_max 8 000 (≤ 0.082 dB); at n\*_max 1 024 it is up to
  0.124 dB.
- **Both ends near walls, uncapped:** up to 0.110 dB at n\*_max 8 000.
- **Where the limit binds,** Q2 sets the precision.
- **CI:** a Release check verifies, per band and per class of case, that the mean deviation from the reference is ≤ 1 %.
  The test is sized so that 3·SE ≤ 1 % − ℓ_ref. The near-wall class has ℓ_ref = 0.65 %, which needs SE ≈ 0.005 dB. That
  costs CI time only.
- **Board:** no rated seat above 1 (eight seats rated; Seat 4 states a preference without a cell).

**(b) To every scene's random error.**
- About 20–33× the paths.
- 100 m restores of about 9–13 s on one thread, and 120–182 s for 14, against pluginval's 30 s.
- W1 rebuilds of 93–187 ms, against 50 ms.
- It cannot be reached at 100 m under any limit that protects the restore.
- Precision bought: 0.0145–0.019 dB, about 1/50–1/70 of an audible change.
- **It needs you to override Seat 5's veto.**

**Q2a. What sets the big-room work limit W_max?**

AQ10 says full rebuilds are "recorded, not budgeted" and "never met by shortening the image list or N_cap: that changes the
output". This limit changes the shipped tail level in order to meet a restore time, so it is yours.

**(A) Size it to pluginval's restore watchdog** (provisional 3.05 M image evaluations per emitter).
- Restores at the gated 100 m scenes come to 2.14 s, at the watchdog with no margin.
- No cap hits at any default or near-wall placement of the six Phase 04 rooms.

| rooms | old error (AX16) | new under (A) |
|---|---|---|
| layout 4 / layout 5, s = 1 (one fully absorbing face, fully diffuse) | +3.87 / −1.17 dB | random, SE 0.17–1.33 dB |
| 100 m cube with an absorbing floor | +2.38 / +2.39 dB | SE 0.12 dB |
| closed 100 m cubes, s = 0.3 | +0.02 dB | SE 0.13–0.20 dB, p95 ≤ 0.28 dB |
| closed low-α 100 m cube, s = 1 | +0.06 / +0.10 dB | SE 0.51–0.67 dB at n\*_max 8 000; 0.44–0.50 dB at 1 024; p95 ≤ 0.89 dB |

The switch corrects the first two rows and **adds** random error in the last two, where the old method was nearly exact.

**(B) About 11× more work.**
- Restores of 2.16–4.83 s per restore and 30.2–67.6 s for 14, past the watchdog in every gated scene.
- 100 m SE 0.05–0.12 dB.
- Seat 5 has not rated it, and a veto would be yours to override.

**(C) Move the diffuse solve off the synchronous restore** in a later phase, about one phase of Phase 07 rework. (A) ships
meanwhile.

**Q2b. What sets the small-room pilot limit n\*_max?**

| | (i) 1 024 | (ii) 8 000 |
|---|---|---|
| sized to | 25 ms of the 50 ms W1 rebuild target | fixed |
| precision at defaults | 0.017–0.086 dB | 0.007–0.054 dB |
| precision near walls | up to 0.124 dB | up to 0.082 dB |
| diffuse solve per W1 rebuild | ≤ 25 ms | about 0.25 s |
| Seat 4 | 1/1 | 2/2 |
| Seat 6 | 1/1 | 1/1 (its preference) |

Both are inaudible, and the "approximate" note behaves the same at both.

**Timing for Q2.** Both limits must be fixed before the first release. Until then a change costs one golden round.

## Part 3: what happens after your answers

1. `/fix-plan` applies the AX rows and plan edits from all rounds:
   - the decider's lists in files 13 and 34, plus the addendum 37;
   - the interrogator's open plan-editor items: D-T4a corrections 59 and 60; final-round items 3–6, including the exact
     "cap hit" definition and the BRAS report's Monte Carlo SE.
2. Your answers are recorded verbatim in the session brief and the ledger.
3. Then the `src/sim` implementation begins (phase-05b2 §4), or the split rule of phase-05b2 §8 applies.
