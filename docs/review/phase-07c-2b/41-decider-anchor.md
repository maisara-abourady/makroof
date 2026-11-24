# 41: Decider on the L4 anchor (A-ii) and on how assertions 7, 4 and 2 are read

To be saved as `docs/review/phase-07c-2b/41-decider-anchor.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **The anchor is A-ii.** It uses the same two files, B and B with the tail raised 3 dB, in 6 trials. In 3 of them the louder file takes the stepped role; in the other 3 the roles are swapped. Nothing new is built.
- **Assertion 7:** read against the model, with the realised drop printed only.
- **Assertion 4:** kept, and recorded as weak on this scene.
- **Assertion 2:** exact on the IRs. On the renders, exact up to the partition boundary below the fade start, then a −120 dB null.
- AX49 and file 13 item 2 are not amended. NEEDS MAISARA: none.

## (1) The anchor

**Tension map (now/later, in the seats' own words)**

| option | S1 | S2 | S3 | S5 | S7 | max | sum |
|---|---|---|---|---|---|---|---|
| **A-ii, roles swapped 3/3** | 0/0 ("Same two files, same task, chance rate unchanged") | NMM | 0/0 ("no new code; meets condition 8") | NMM | 0/0 | **0** | **0** |
| A-i, up-only | 0/0 | NMM | 0/0 ("no order balance") | NMM | 0/0 | 0 | 0 |
| A-iii, new tail-gain flag | 1/1 | 1/1 | 1/1 | 1/1 | 1/1 | 1 | 10 |
| A-iv, anchor on another scene | 1/1 | NMM | 2/1 (breaks condition 8) | NMM | 2/1 | 2 | — |
| A-v, 3 dB on the whole render | 2/1 | NMM | 2/1 (outside item 2) | NMM | 1/1 | 2 | — |

NMM = not my matter. Seat 2 rated only A-iii; Seat 5 called A-i, A-ii, A-iv and A-v not its matter. Both score 0/0 there.

**Working.**
- No option breaks a bound. A-v sits outside item 2's "tail step", and both seats that rated it put it at 2.
- No seat gave a 3.
- On the worst-off seat, A-i and A-ii tie at 0.
- On the sum, they tie at 0.
- On reversibility they are equal: each is a change to the trial plan.
- **A-ii is chosen.** It is the only remaining difference the seats named, and both preferred it:
  - Seat 1: it "keeps the trial plan at 3/3, so L4-D's wording changes less";
  - Seat 3: it "balances any order or label bias at no cost".
- Seat 3 corrected its own record: its condition 8 had asked for +3 dB only. So A-ii meets condition 8.

**Chance rate.** P(≥ 5/6) by guessing = 7/64 = 0.109, unchanged, because X is still drawn at random (Seat 1).

**DECISION L4-A, exact text for run sheet §8 (the anchor paragraph):**
> "**Anchor (AX49; file 13 item 2: a uniform 3 dB tail step, pass ≥ 5/6).** 6 anchor trials per block at the block's seeded positions, built on the L4 scene and chord from two static files: B, and B with the tail stepped +3 dB (`--abx-step-db +3 --abx-step-sample 0`). In 3 trials the stepped file takes the stepped role and B the reference; in the other 3 the roles are swapped. X is drawn at random as for scored trials. On the L4 scene the specular share of E_target is 0.828, so a −3 dB step cannot be built (`--abx-step-db` reaches −0.82 dB); with static whole-file stimuli the two role assignments present the same 3 dB tail-level difference, so the anchor's purpose (chain and attention to the tail; not envelope sensitivity) and its chance rate (7/64) are unchanged (phase-07c-2b decider file 41). Familiarisation includes the labelled anchor pair. The anchor result is never cited as evidence about M1's step or any other measurement."

**⚙ Kit changes:**
- `l4_trial_plan`: the anchors carry `role: stepped_as_A | stepped_as_B`, 3 and 3. The seeded positions and X draws are unchanged.
- `l4_anchor_feasibility` checks only +3 dB.
- `build_l4` no longer stops. The familiarisation files become A/B plus the labelled anchor pair.
- **Asserted on the +3 dB anchor IR** (Seat 3's condition):
  - M1's per-band step identity is within 0.05 dB;
  - s_w ≤ 2.3 % (printed and asserted);
  - peak ≤ −3 dBFS (measured at −9.93 dBFS).
- **Tests:**
  - `test_l4_build_stops_at_the_down_anchor` becomes `test_l4_down_step_refused_on_scene`. It asserts that render_cli refuses −3 dB on the L4 scene, which records why A-ii was chosen. It also asserts that the kit never asks for a negative anchor step.
  - The end-to-end L4 test now runs to completion.
- **K6:** redone on the final familiarisation set (one file fewer). The third sitting stands (file 38 (5)).

## (2)–(4) How the assertions are read (Seat 3, file 40)

**(2) Assertion 7: read against the model.** Seat 3 rates this 0/1.
- It asserts the decay as AX49 builds it: 60 × 0.312 = 18.72 dB from t_mix,e,max to L_f, per band.
- **My file-38 wording is corrected.** Assertion 8 does not measure "the same quantity". It measures K17′'s bound counted from emission: the energy past L_f over the whole decay. It covers the realised side of K17′. It does not prove a realised drop of ≥ 18.7 dB from t_mix,e.
  - Seat 3's arithmetic: model 0.0120, realisation 0.0127, measured 0.0124, all ≤ 0.0134.
- **⚙ Print:** "realised Schroeder drop [t_mix,e,max, L_f), one realisation, not asserted". At 63 Hz it is 18.47 dB.
- The non-detection wording quotes the **realised** cut depth, 21.7 dB in the T60_max band (file 26). That is already in L4-S.

**(3) Assertion 4: kept, tolerance 0.05 dB unchanged.** Seat 3 rates this 0/0.
- **⚙ Print:** "consistency check; weak on this scene (all predicted |A/B| < 0.01 dB); red test: a 1.2 dB hot provisional fails it".

**(4) Assertion 2: exact on the IRs.** Seat 3 rates this 0/0.
- **IRs:** bit-identical up to the earliest tail fade start (tap 3007 here).
- **Renders:**
  - bit-identical before the partition boundary at or below the chord-aligned fade start (6656 here);
  - over [that boundary, fade start), i.e. [6656, 7103), **max |A − B| ≤ −120 dB re B's peak, per sample** (the Phase 06 criterion, Seat 3's definition).
- **⚙ Print:** the first differing sample (6658).

## Load-bearing claims
- **A-L1** (file 26; file 34 item 1): the specular share is 0.828, giving 10·log10(0.828) = −0.82 dB, so −3 dB is refused.
- **A-L2** (arithmetic): P(≥ 5/6 | ½) = 7/64 under random X, for any role assignment.
- **A-L3** (Seat 3, arithmetic): 10^(−(18.72 + 0.49)/10) = 0.0120 and 10^(−(18.47 + 0.49)/10) = 0.0127, both ≤ 0.0134.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 3 | Assertion 7 is read against the model; the realised 63 Hz drop of 18.47 dB is put down to one-realisation scatter (about 0.4 dB [Inferred]) | A realised reading, if scatter does not explain it | A 16-seed ensemble (`--ensemble --tail-only`) of the 63 Hz drop | The ensemble mean prints ≥ 18.7 dB within its spread, before 07d's remedy round reads L4 |

## Strongest objection
A-i is equally good on every seat's rating. A-ii wins only on the two seats' stated preference for keeping the plan at 3/3. If the interrogator holds that preference cannot break a full tie, either option is valid, and the plan text would read "6 × stepped as A" instead.

**Confidence:** high for (1), (3) and (4); medium for (2), because the scatter figure is inferred.

**Reversal:** any of the following.
- The +3 dB anchor IR fails M1's checks.
- The ensemble shows a mean realised drop below 18.7 dB. Then assertion 7 goes back to Seat 3 and the 07d round.

## Summary
| id | decision | state | worst-off | sum | confidence | PRD bound |
|---|---|---|---|---|---|---|
| L4-A | A-ii: B vs B+3 dB tail, roles 3/3, ≥ 5/6, 7/64 by chance; ⚙ kit and tests | proposed | 0 | 0 | high | NFR-1 |
| (2) | assertion 7 on the model; realised drop printed; wording on assertion 8 corrected | proposed | S3 0/1 | 1 | medium | NFR-1 |
| (3) | assertion 4 kept, recorded as weak | proposed | 0 | 0 | high | NFR-1 |
| (4) | IR exact; renders exact up to the partition boundary, then a −120 dB per-sample null | proposed | 0 | 0 | high | NFR-1 |

## Decided for Maisara
- **Anchor.** In the reverb-cut test, the "can you hear an obvious 3 dB reverb change?" check trials use a louder-tail file against the normal one, presented both ways round. That is because this test room cannot make a quieter-tail version. It checks the same thing with the same odds.
  - NFR-1: the check stays valid without new code.
  - The rejected options either add a new code path that buys nothing (A-iii), or check attention on a different room or on overall loudness, which weakens the check (A-iv, A-v).
  - Amends nothing of yours.
- **Assertions.** Three internal checks are read as the engine's design states them, and the measured values are printed beside them. NFR-1. Amends nothing.

**NEEDS MAISARA:** none.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/40-seat1-anchor.md
- /home/user/makroof/docs/review/phase-07c-2b/40-seat2-anchor.md
- /home/user/makroof/docs/review/phase-07c-2b/40-seat3-anchor.md
- /home/user/makroof/docs/review/phase-07c-2b/40-seat5-anchor.md
- /home/user/makroof/docs/review/phase-07c-2b/40-seat7-anchor.md
