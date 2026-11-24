# 38: Decider on the L4 anchor and the four other findings in builder file 26

To be saved as `docs/review/phase-07c-2b/38-decider-l4-anchor.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Outcome:**
- **(1) The −3 dB anchor: CONVENE**, Seats 1, 3, 5 and 7, plus Seat 2 narrow. This is a design question, and none of its options has been rated. I do not choose one here.
- **(2)–(4) How assertions 7, 4 and 2 are read: CONVENE Seat 3**, the author of these assertions and the owner of D-C9. Each comes with my proposed reading for it to rate.
- **(5) Sittings: decided.** L4 gets its own third dated sitting. This applies rules that already stand (L4-T; file 21's D1 worst-case rule), so it needs no convening.
- Nothing is sealable until (1) is decided. NEEDS MAISARA: none.

## (1) The −3 dB anchor: CONVENE

**The finding, from the code and file 26:**
- `--abx-step-db g` scales E_target (M1 = A). A down-step needs a specular share ≤ 10^(g/10), and the kit refuses otherwise (file 34 item 1, refusal (b)).
- On the L4 scene (s 0.1) the specular share is 0.827–0.828 in every band of both emitters. So the deepest down-step is 10·log10(0.828) = −0.82 dB, and `--abx-step-db -3` exits 1.
- The +3 dB step builds. It is uniform across bands, because E′_target = k·E_target and the window from t_mix,e + 2.5 ms on holds no images (file 34 item 1).
- So L4-D's "3 up, 3 down" anchor cannot be built as written.

**The bounds every option must stay inside:**
- AX49: L4 "carries the AX47 self-ABX's 6-trial 3 dB anchor (pass ≥ 5/6)".
- File 13 item 2: "6 interleaved anchor trials per block: a uniform 3 dB tail step; pass at ≥ 5/6".
- Neither text fixes the step's direction. That is a design detail of the kit and of L4-D.
- Seat 1 (9-seat1-l4) on the anchor's purpose: it "confirms that the chain and the listener's attention work. It does not confirm sensitivity to the envelope."

**The options to rate.** The coordinator's list was not taken as given; this is the list the seats rate. The seats may add others.
- **A-i, up-only.** 6 anchor trials, each B against B with the tail at +3 dB (`--abx-step-db +3 --abx-step-sample 0`). X is drawn at random as now.
- **A-ii, both ways with the same two files.** 3 trials where the stepped file is A and plain B is the reference, and 3 trials with the roles swapped. With static whole-file stimuli, A-i and A-ii differ only in labelling and roles. Rate whether that difference matters.
- **A-iii, a new validation path.** A broadband tail gain applied to the rendered tail past t_mix,e + 2.5 ms, both specular and diffuse, outside `--abx-step-db`, so that −3 dB can be built.
  - This is a new `src/cli` flag and needs its own guard and tests. That is Seat 5's matter.
  - It changes what "the step" scales, which M1 settled as E_target. That is Seat 2's matter.
- **A-iv, a different anchor scene for L4 only.** The anchor runs on a scene where −3 dB builds, while A/B stays on the L4 scene. The anchor would then no longer be "on the L4 scene and chord", which is Seat 3's L4-D condition 8.
- **A-v, a different anchor quantity.** For example, a 3 dB step in the whole wet render. That is outside item 2's "tail step", so it can only be rated as a bound question.

**Convening.**

| seat | status | reason |
|---|---|---|
| 1 | convened | The anchor's design and purpose (item 2; L4-D) |
| 2 | convened, narrow | Only for A-iii: what the step scales (M1, E_target) |
| 3 | convened | L4-D condition 8 (anchor on the L4 scene and chord); D-C9's owner |
| 4 | not required | Omni, diotic |
| 5 | convened, narrow | Only for A-iii: a new validation flag, its guard, AX5, CI |
| 6 | not required | A validation stimulus; the user-facing reason for L4 is unchanged |
| 7 | convened, narrow | Hours, if the trial count or familiarisation changes |
| 8 | not required | A validation stimulus |
| 9 | not required | No label changes |

**Brief, for every convened seat.** Read file 26 ("Read this first", note 1, K6), file 10 (L4-D, L4-P), AX49 (L172) and file 13 item 2. Rate A-i to A-v, now and later, with your conditions:
- **Seat 1:** does an up-only anchor, or one with roles swapped, still serve the anchor's purpose? Does it change ≥ 5/6, or the chance of passing the anchor at random (1/64 + 6/64 = 7/64 for ≥ 5/6 under guessing)?
- **Seat 3:** does A-iv break your condition 8? Under A-iii, what should the tail gain scale?
- **Seat 2 and Seat 5:** A-iii only.
- **Seat 7:** the hours under each option.

## (2)–(4) How the assertions are read: CONVENE Seat 3 (narrow)
For each finding below: the finding, then the reading proposed for Seat 3 to rate, now and later.

**(2) Assertion 7, the decay from t_mix,e,max to L_f.**
- *Finding:* the model decay at 63 Hz is 60 × 0.312 = 18.72 dB, which passes. The realised Schroeder drop on B's heard IR is 18.47 dB, which is below 18.7.
- *Proposed reading:* the model, as AX49 states it ("the decay from t_mix,e,max to L_f is ≥ 18.7 dB in every band, asserted") and as `tests/unit` takes it.
  - The realised side is covered by assertion 8. B's share past L_f is 0.0124, against 0.0134, which is AX49 K17′'s bound on the same quantity, and it passes.
  - The realised drop is printed with the label "realisation, not asserted".

**(3) Assertion 4, the A/B step over [t_mix,e,max + 2.5 ms, L_f).**
- *Finding:* every predicted step is below 0.01 dB, so the 0.05 dB tolerance would also hold with a prediction of 0.
- *Proposed reading:* keep it, and record it as "consistency check; weak on this scene (predicted < 0.01 dB)".
  - Its red test, a provisional tail 1.2 dB too hot, still fails it, so the check is not vacuous in what it is meant to catch (file 26 tests).
  - The tolerance is not changed.

**(4) Assertion 2 on the renders.**
- *Finding:* on the IRs, A and B agree bit for bit exactly up to the tail fade start (tap 3007). On the renders they agree up to sample 6658; the kit asserts up to the partition boundary 6656, while the chord-aligned fade start is 7103.
- *Proposed reading:* the IR-level assertion is the exact one. On the renders, bit-identity is asserted up to the partition boundary at or below the fade start, because partitioned convolution mixes whole partitions (Phase 06).
  - Between that boundary and 7103 the renders null within −120 dB (Phase 06's criterion). That is asserted, not left unchecked.

## (5) Sittings: decided
- **The rule.** L4-T: L4 runs in E's second sitting "if that sitting plus L4 stays within 2 h. Otherwise a third dated sitting goes into the brief before any seal". File 21's D1 correction: the worst case counts E's sitting 2 + the L4 primary + the L4 rerun.
- **The figures** (file 26, K6, typical pace): E's sitting 2 is about 74 min, and L4's primary + rerun is 74.0 min. That is 148 min (2.47 h), over 2 h.
- **Decision: a third dated sitting for L4.**
  - It holds the L4 primary block, plus the rerun block if the anchor fails.
  - That is 74 min at a typical pace, 114 min slow, so within 2 h at every pace in K6.
  - E's two sittings are unchanged.
  - The dates go into the brief before any seal.
  - K6 is redone if (1) changes the trial count or familiarisation.

## Summary
| id | decision | state | PRD bound |
|---|---|---|---|
| (1) anchor | A-i to A-v rated by Seats 1, 3 (and 2, 5 for A-iii; 7 for hours) | convening | NFR-1 |
| (2)–(4) | readings proposed: model for assertion 7 (realised printed; assertion 8 covers it); assertion 4 kept and recorded as weak; assertion 2 at partition granularity plus a −120 dB null | convening (Seat 3) | NFR-1 |
| (5) | third dated L4 sitting (primary + rerun, 74 min typical, 114 min slow) | proposed | L101 |

## Decided for Maisara
- **(5) Sittings.** The reverb-cut test (L4) gets its own short session of about 1¼ hours at most. Your two sessions for the main test are unchanged.
  - Rests on L101 (the plugin must stay usable). Listening sessions stay within the 2-hour limit the plan uses.
  - Adding L4 to your second session would make it about 2½ hours.
  - Amends nothing of yours.

**NEEDS MAISARA:** none. The third sitting is a person's action (Raise item 2).

Files:
- /home/user/makroof/docs/review/phase-07c-2b/26-builder-l4-kit.md
- /home/user/makroof/docs/review/phase-07c-2b/10-decider-l4.md
- /home/user/makroof/docs/review/phase-07c-2b/21-decider-p8.md
