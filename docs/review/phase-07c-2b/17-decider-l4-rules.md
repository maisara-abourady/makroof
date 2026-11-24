# 17: Decider on the L4 pre-registration rules (D1, P1, P8)

To be saved as `docs/review/phase-07c-2b/17-decider-l4-rules.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

Interrogator file 16 was not in the repo when this was written (the glob shows files 1–14 only). The three questions are answered as the coordinator relayed them.

**Decisions:**
- **D1, a failed L4 anchor: rule (a).** The block is void and gets one rerun, whose stimuli are built and sealed in advance. The voided block's scored answers are never opened. The result is "inconclusive" only if the rerun's anchor also fails.
- **P1, wording:** "detected (≥ 12/16, family α 0.038)", where 0.038 = 2517/65536.
- **P8, voiding: yes.** The same changes that void the AX47 stimuli also void the sealed L4 stimuli. So do changes to AX49's own constants, and any mismatch between the sealed IR hashes and a fresh build.
- No seat is re-convened, because no seat's matter is newly touched (reasons below). NEEDS MAISARA: none.

## Convening
Each rule applies a design element that L4 already took over, or a condition a seat already rated, to the L4 stimuli:
- **D1:** file 13 item 14 says L4 uses the "same chain and tool, with the 6-trial anchor". AX49 says L4 "carries the AX47 self-ABX's 6-trial 3 dB anchor (pass ≥ 5/6)". Item 4's rule on failed anchors comes with that anchor. Seat 1 adopted the anchor "As AX49 fixes it" (9-seat1-l4).
- **P1:** arithmetic for a single test under item 13's existing wording.
- **P8:** the void rule of D-M3h 1 and C-b, which Seats 2, 3 and 9 rated at later 1 ("minutes to a reseal"). It is now applied to the second stimulus set.

Seat 7's hours: a rerun is already inside K6's upper bound ("every block voided once and rerun"). Seats 4, 6 and 8 are not touched.

If the interrogator holds that P8's extra triggers (AX49's constants) newly touch Seat 3, the D-C9 owner, Seat 3 is the one to convene.

## D1: a failed L4 anchor
**Options:**
- **(a)** As AX47 item 4: the block is void and gets one rerun; a voided result is discarded whatever it shows; it is never recorded as "not detected".
- **(b)** "Inconclusive", with no rerun. AX49's reversal ("the L4 ABX detects the cut") then stays unread.

**Who the seats' existing words favour:**
- **Seats 1, 6 and 7** rated an unread L4 reversal at 2 later, under L-c: "the remedy is chosen without data", "choosing by rationale", "class (c) and the W pin are decided without L4". Rule (b) recreates that state whenever an anchor fails. Rule (a) leaves it only after two failures.
- **Seat 7:** the rerun's time is inside K6's upper bound, so there is no new cost.
- **Item 4's rule** is part of the anchor L4 carries (item 14), so (a) also keeps L4 consistent with AX47.

**Decision: (a), in exact wording for the run sheet's L4 section:**
> "L4 anchor (6 trials, ±3 dB tail step, pass ≥ 5/6). If the anchor fails, the block is void: its scored trials are not unsealed or scored, and the void is recorded. One rerun follows, using a second block (its own seeded key, trial order and anchor positions) that was built and sealed with the first, before the session. A voided result is never recorded as 'not detected'. A non-detection is never a reason to rerun. If the rerun's anchor also fails, the record reads 'inconclusive (anchor failed twice)', and AX49's L4 reversal stays unread; the board treats that as an unread reversal at 07d (debt row below)."

**Kit change (builder):**
- The L4 builder makes and seals two blocks: a primary and a pre-built rerun.
- The scoring script scores the anchor trials first. It refuses to unseal a block's scored trials if that block's anchor failed.
- This matches the AX47 rule, which refuses to unseal a 0.5 dB block unless 0.9 dB was detected.

## P1: detection wording
- L4 is one test of 16 trials, scored at ≥ 12/16. Under Binomial(16, ½), P(≥ 12) = 2517/65536 = 0.0384. File 31 answer 4 gives this; Seats 1, 5 and 6 recomputed it.
- **Wording (record, run sheet, results file):**
  - Detected: "detected (≥ 12/16, family α 0.038)".
  - Not detected: "not detected in 16 trials by one listener (power 0.63 at p = 0.75); covers a cut ≥ [measured] dB below the full-IR energy in the T60_max band at T60_max 8 s" (L4-S).
  - Anchor failed twice: "inconclusive (anchor failed twice)".
  - Never "inaudible". No public copy.
- **L4 is its own family** (AX49). It is not added to the AX47 union, because it tests a different reversal (AX49's) on a different claim. The record says so beside AX47's union rate (≤ 0.098).

## P8: voiding sealed L4 stimuli
**Why.**
- L_f = t_mix,e,max + 0.312·T60_max, and the provisional IR depends on t_mix,e, the decay target and AX49's constants.
- A change that makes AX21 false, moves t_mix,e or changes the tail's decay target therefore moves L_f and L_p, and it changes A, B or both.
- The sealed stimuli would then no longer be what the plugin plays: L4 test 7, the parity test, compares only the current build.
- The reason that voids the AX47 stimuli applies here with more force, because L_f and L_p are the very quantity L4 tests.

**Decision. D-M3h 1 is extended to L4.** Sealed L4 stimuli are void for the next listening session if any of these happens:
1. any change that makes AX21's statement false or moves t_mix,e: a B11 promotion, an early-diffuse method, or a change to the AX22 rule;
2. any change to the tail's decay target, such as non-Eyring decay for non-diffuse rooms (C-b);
3. any change to AX49's provisional construction: the 0.312 fraction, the 0.1 s fade, the normalisation, or L's rule (1.5·T60_max, capped at 12 s);
4. **a hash mismatch**, as a backstop for any cause:
   - the manifest records the SHA-256 of A's IR (`--provisional-ir --ir`) and B's IR (`--ir`) on the L4 scene, with the platform;
   - before the session, the kit rebuilds both on the same platform (AX5) and compares;
   - any mismatch voids the stimuli.

**After a void:**
- The stimuli are rebuilt and must pass L4-D's assertions 1–13, tests 1–8 and Seat 9's label check before they are sealed again.
- Results already recorded stay attached to their commit and scene hash, marked "pre-change engine".
- If no L4 session follows the change before 07d decides AX49's remedy, the change's phase schedules L4 on rebuilt stimuli before that decision. This applies the timing condition Seats 1, 2, 3, 5 and 6 set on L-c.

**Homes (/fix-plan, same edit as file 10's L4-W):**
- AX49's "Listening item L4" sentence: "void rule: phase-07c-2b decider file 17, P8";
- the run sheet's new L4 section;
- the B11 homes listed under D-M3h 1 (phase-05e scope (b), the deferred B11 entry in BUILD_PLAN, the phase-05b row), extended to name the L4 stimuli.

## Load-bearing claims
- **R-L1** (arithmetic): 2517/65536 = 0.03841, which rounds to 0.038.
- **R-L2** (AX49): L_f = t_mix,e,max + 0.312·T60_max, so a change to t_mix,e or T60 moves L_f, and L_p = L_f + 0.1 s.
- **R-L3** (file 13 item 4; item 14; AX49): the L4 anchor is AX47's, and so is the failed-anchor rule.
- **R-L4** (CLAUDE.md "Determinism"; AX5): bit-identity holds only on the same platform, so the hash check runs on the sealing platform.

## Future-debt register
| seat | commits | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 1, 6, 7 | A twice-failed anchor leaves AX49's L4 reversal unread | A new L4 session, about 20 min plus setup | L4 session | Scored, or 07d decides with the unread reversal recorded as such |
| 2, 3, 9 | Engine changes void the L4 stimuli (P8, items 1–4) | Minutes to a reseal | Any B11, AX22, decay-target or AX49 change; the pre-session hash check | Rebuilt and passed, or recorded "pre-change engine" |
| 7 | A pre-built rerun block | Build minutes | Kit build | Both blocks sealed together |

## Strongest objection
Rule (b) would save one possible rerun of about 20 minutes. It does not hold: under (b), a single failed anchor leaves AX49's reversal unread, and that is the state Seats 1, 6 and 7 rated at 2 later.

The hash backstop (P8 item 4) could void stimuli after a change that is harmless to the sound, such as a compiler update on the sealing platform. It voids in the conservative direction, and the cost is minutes to a reseal.

**Confidence:** high for P1 (arithmetic); medium for D1 and P8 (seat ratings carried over from rounds on adjacent questions).

**Reversal:** Seat 1 or Seat 3 objects to extending the rule to L4 on their own ground, and is then convened.

## Summary
| id | decision | state | worst-off | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|
| D1 | rule (a): void, one pre-sealed rerun, voided result never unsealed; "inconclusive" only after a second failure | proposed | 1 (later, if it fails twice) | medium | NFR-1 | Seat 1 objects |
| P1 | "detected (≥ 12/16, family α 0.038)"; non-detection with power and cut-depth scope; own family | proposed | 0 | high | NFR-1 | — |
| P8 | L4 stimuli void on the D-M3h 1/C-b triggers, AX49 constant changes, or an IR-hash mismatch | proposed | 1 | medium | NFR-1 | Seat 3 objects |

## Decided for Maisara
- **D1.** If you fail the obvious 3 dB check trials in the reverb-cut test, that block is thrown away unread and you hear one pre-made replacement block. A failed check never counts as "you couldn't hear it". NFR-1: the test must be able to give its answer. Option (b), an inconclusive result with no rerun, strains NFR-1 by leaving AX49's reversal unread. Amends nothing.
- **P1.** A detection is reported with its own chance level, 3.8 %, because L4 is a single test. NFR-1. Amends nothing.
- **P8.** If the engine's reverb timing changes after the stimuli are sealed, they are rebuilt before you listen, so you never judge something the plugin no longer plays. NFR-1. Amends nothing.

**NEEDS MAISARA:** none.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/13-interrogator-on-file10.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat5-l4-rerate.md
- /home/user/makroof/docs/review/phase-07c-2b/16-interrogator-fixplan-diff.md: not found.
