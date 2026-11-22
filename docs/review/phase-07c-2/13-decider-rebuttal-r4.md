<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2, decider rebuttal round 4: FM-W3a, D-W3, D-W2 final, D-W1 waiting list

To be saved as `docs/review/phase-07c-2/13-decider-rebuttal-r4.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Short version.**
- **Q1:** I choose **(ii).** Condition 4 ("exactly one step per solve and never mid-drag") stays as she accepted it. FM-W3a is withdrawn and nothing goes to her yet.
- **D-W3 is re-decided** within her standing condition, as H-2c (this round's one composed variant). The ISM update no longer waits for the solve, so Seat 5's W-C2 condition still holds, pending M7 on CI.
- **The question of letting the reverb level follow during long automation** becomes a separate item, D-W4, deferred until evidence exists. Asking her now would put an unanswerable question to her.
- **D-W2 is restated** below, final and with both corrections, in the form it will be pre-registered.

---

## Q1: FM-W3a — (ii), and why not (i)

I accept the interrogator's verdict. No PRD passage ranks FR-SIM-6's "follow" above its "without audible artifacts". NFR-3 (L107) hands that tension to the Expert. AQ4 was already in force beside condition 4 when she accepted condition 4. And the deciding premise has no evidence: that small steps in the tail level during motion are less audible than one step at the end. The interrogator marks it NOT CHECKABLE.

Sending her that choice now would ask her to rule without the one fact she would need. So:
- FM-W3a is **withdrawn**.
- **Condition 4 stands as she accepted it on 2026-11-10.**
- D-W3 is re-ordered with the item-4 exception out of bounds (below).
- The recency question becomes **D-W4**, deferred until two pieces of evidence exist:
  - M7b's end-of-automation step distribution, measured under H-2c;
  - a blind listening check in Seat 1's paradigm: steps during motion against one step at rest.
- With that evidence, if the PRD still supports two readings, D-W4 goes to her as **NEEDS MAISARA, case (a)**, with both options costed.

## Q2: problem-key adoption

H-2\* item 3 adopted a final when only the `DiffuseProblem` was unchanged. During a drag of a parameter that changes the scene key S but not P, that lands a final mid-drag. That is not reasoned inside condition 4, so it is **removed**.

H-2c adopts a final only if **neither P nor S** (the AX48 key parts) changed while it was solved. AX48 defines S as the effective scene without `outputMode`, `hrtfId` and `tailSeed`, and already rules that those three never re-solve. So an edit to one of them does not discard the solve: it does not change the scene the solve answers, it is not a scene drag, and no movement is involved (FR-SIM-6 is not engaged). Every other edit discards the solve, as today. This matches Seat 3's own H-1 condition (a): "cancel only on edits that change P or S".

## Q3: Seat 3's cell — not needed

The 3 s exception is gone. Seat 3's stated H-2 conditions now apply word for word:
- (a) M7 is re-measured under H-2, with the solve occupying the pool, and is ≤ 700 ms on the worst OS;
- (b) "a doomed solve stops at its next `run.stop` once its generation is stale".

So the cell is 1/1, read from its stated conditions without any modification. No question goes to Seat 3.

## Q4: D-W3 re-ordered, acceptance check, Seat 5's condition

### Option H-2c (this round's one composed variant): H-2 plus the stated conditions of Seats 2, 3 and 5, inside condition 4

1. **The solve moves off the builder thread.**
   - The solve runs as a task on the process-wide gate executor, not a thread per instance.
   - Its input is an immutable snapshot of the `DiffuseProblem` with E_prec and E_model. Its result comes back through a shared-ownership mailbox.
   - The builder is the only committer (comment at L582).
   - The gate is held around the solve as before (AX38 (i)).
   - The pool is `hardware_concurrency − 1` while the builder works alongside it.
   - `quiesce()` waits for or safely orphans an in-flight task (all Seat 5).
2. **The builder never waits for a solve.** Each edit gets its B1′ IrSet at once, as at L508–540.
3. **Final adoption.** A finished solve is adopted as the final only if P and S are unchanged since it started (Q2). Adoption is one AQ4 step (condition 4). The final must be bit-identical to an uncancelled one-shot solve (D7).
4. **A superseded solve stops at its next stop point.**
   - The trigger is a per-generation cancel token, separate from `builderAbandon_`.
   - Stop points are spaced by a fixed work count, never by time.
   - A cancelled solve never yields an E_b.
   - **No held-level adoption during motion** (condition 4).
5. **Offline is unchanged.** Offline renders and `render_cli` wait for the final synchronously (AX5, condition 6).
6. **Tests.**
   - TSan `[pipeline]` stress with edits at random solve points and the pipeline destroyed mid-solve.
   - Bit-identity of a final with and without cancelled predecessors.
   - Offline bit-identity.
   - `[reset-nowait]` still green.
   - A B1-b re-run with the solve duration printed.
7. **Acceptance measurements.**
   - **M7 under H-2c:** the ISM latency of an edit made mid-solve, with the solve occupying the pool. Three CI OSes, m = 1, 4, 5, 6, 8, capped scenes. Must be ≤ 700 ms on the worst OS and flat in m.
   - **M7b:** under the AX38 (iv) patterns and continuous automation, the fraction of solves completed, the time from the end of automation to the final, and the size of the end step, against H-0's `discardedMidDrag`. M7b is also D-W4's evidence.
8. **Routing.** It lands in **07c-2**, or as the **first work of 07c-2b**, before the golden round.
   - It is a defect of 07c-1's condition 4 and is recorded in the ledger as one.
   - It is added through `/fix-plan` as a phase-file scope change (correction 7), plus the BUILD_PLAN §0 note: "08-x goldens are frozen only after 07c-2 (or 07c-2b) is `done`" (Seat 7).

### Tension map (now / later)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| H-0 | 1/2 | 2/2 | 1/2 | 2/2 | 1/2 | 1/2 | 1/2 | 2/2 | 1/1 | 2 | 29 |
| H-1 (conditions of Seats 2, 3, 5; no progress rule, which is out of bounds) | 1/2 | 1/1 | 1/1 | 1/2 | 1/1 | 1/2 | 1/2 | 1/1 | 0/1 | 2 | 21 |
| H-2 as stated | 0/2 | 1/2 | 1/2 | 1/1 | 2/1 | 1/2 | 2/0 | 0/1 | 0/0 | 2 | 19 |
| H-3 | 2/2 | 1/2 | **2/3** | 2/2 | 1/2 | 1/2 | 1/2 | 2/2 | 0/0 (NOT MY MATTER) | 3 | — |
| **H-2c** | 0/2 *(from conditions: no recency)* | 1/2 *(from conditions: P,S key, not P only)* | 1/1 *(conditions (a), (b))* | 1/1 *(no stale-level bound)* | 1/1 *(all six H-2 conditions)* | 1/2 *(H-2 as written)* | 1/0 *(first work, TSan gates)* | 0/1 | 0/0 | **2** | **16** |

### Working

1. **Bounds.** Condition 4 stands. The item-4 exception and P-only adoption are out of bounds.
2. **Veto.** H-3 is dropped on Seat 3's 3.
3. **Worst-off seat.** Every remaining option has a maximum of 2. The 2s on H-2c (Seat 1 later, Seat 6 later) come from the diffuse level being starved during continuous automation. That starvation exists today under H-0 (from the code: L542 and L555 discard; it holds whenever edits arrive faster than ISM plus solve). Both seats' conditions for removing it require adopting during motion, which is outside condition 4. So **no in-bounds variant lowers them.** That is D-W4.
4. **Compose.** H-2c, this round's only variant.
5. **Sum.** H-2c 16, H-2 as stated 19, H-1 21, H-0 29.
6. **Decide: H-2c.**

### PRD acceptance (every survivor shown against FR-SIM-6 and NFR-3 / AQ4)

| option | FR-SIM-6 "follow … without audible artifacts" | NFR-3 / AQ4 (700 ms yardstick) |
|---|---|---|
| H-2c | serves it for the early part (the ISM never waits); the diffuse level follows at rest, unchanged from today | meets the yardstick if M7 confirms it; no CPU spent on solves that will be thrown away |
| H-2 as stated | same as H-2c, with doomed solves running on | same |
| H-1 | the ISM follows after the cancel latency; diffuse level the same as H-2c | meets it if the cancel latency is small (unmeasured) |
| H-0 | strained: the ISM is held for up to one solve (local projection 590 ms at ×5, more at higher W) | caps W at 5, below the accuracy floor (the preamble's accuracy priority, L101) |

No PRD goal or ranked requirement points to H-2 as stated, H-1 or H-0 over H-2c.

### Seat 5's W-C2 condition

It still holds. Seat 5's condition is that D-W3 makes the hold independent of W. Under H-2c the independence comes from the decoupling (item 2), not from the withdrawn exception, so it stands pending M7. If M7 fails, the W-C2 condition fails with it, and D-W3 returns to the board.

### Load-bearing claims

- **D3-L1 (code).** The B1′ commit is at L538–540. The solve runs inline on the one builder thread (L552–553; `IrBuilderThread.h` L5). The mid-drag discards are at L542 and L555. The single-committer comment is at L582.
- **D3-L2 (corpus, by extension).** Vorländer §15.3, Table 15.1: 700 ms for the specular part, 3 s for the specular and scattering parts. These are VR filter-update intervals.
- **D3-L3 (local Linux projection, not a fact until M7 is in).** The pool hold is 590 / 810 / 813 ms at ×5 / ×6 / ×8.

### Future-debt register (H-2c)

| seat | what it commits later phases to | what undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 1 (L2) | the tail level stays frozen through continuous automation, then one end step (as today) | D-W4: recency adoption would be a rule change, and possibly a phase of rework if M7b shows starvation (Seat 1) | M7b, D-W4 listening check | D-W4 resolved (her answer, if case (a)) |
| 2 (L2) | the (P, S) key rather than P alone | a key change, only through D-W4 or condition 4 | 07c-2 CI | D-W4 |
| 3 (L1) | the worker topology must survive 07d; Phase 10 sets the motion law | revert to the serial builder | 07d, 10-1 | 10-1 gate |
| 4 (L1) | a stale direct-to-reverberant ratio during automation | D-W4 | 08-4 | D-W4 |
| 5 (L1) | a second actor: lifetime and TSan surface | revert | TSan; 08-4, 10-1 | stress test green through 07d and 08 |
| 6 (L2) | "settling" lit throughout automation, then an automatic level step (W4) | D-W4; 11-3 drawing | M7b; 11-3 | D-W4 |
| 8 (L1) | stale diffuse level during long moves | D-W4 | M7b | D-W4 |

**Strongest objection.** Seats 1 and 6 carry a 2 later that no in-bounds option removes. It holds because the cause, starvation, predates this decision and is identical under every option. Only amending condition 4 can remove it, which is hers to decide, once informed (D-W4).

**Confidence:** medium. **Reversal:** M7 above 700 ms or not flat in m; a TSan race; D-W4's answer.

## Q5: TSP step placement (pre-registered)

The onset falls in the pause after the first sentence, **no later than 0.43 · T30(1 kHz) after the end of speech** (26/60, Seat 9's arithmetic).

**The measured criterion is asserted on every stimulus.**
- Condition: at the onset, the rendered tail level is ≥ 20 dB above the rendered floor.
- Tail level: the 1 kHz band, 50 ms window.
- Floor: the rendered level of TSP's own noise.
- The recording's SNR is about 46 dB relative to the average active speech level (R35 App. A).

A seeded onset that fails the assertion is replaced by the next seed index, and the replacement is recorded. The offset is recorded in units of T.

---

## D-W2: final, as pre-registered

**AX47 self-ABX**
1. **Listener.** One decision listener, named in the pre-registration. Any further listener is pre-registered and splits α by Bonferroni. Results hold for that listener only.
2. **Trials.**
   - 16 scored trials per test.
   - 6 interleaved anchor trials per block: a uniform 3 dB tail step; pass at ≥ 5/6.
   - Blocks of 22 trials, with a break at trial 11.
   - Familiarisation before any scored block (mandatory, BS.1116-3 §4.1). Feedback during familiarisation is Seat 1's design choice. No feedback in scored blocks.
3. **Family.**
   - Noise chain: 0.9 dB at ≥ 12/16, then, only if detected, 0.5 dB at ≥ 12/16.
   - Speech chain: 0.9 dB at ≥ 13/16, then, only if detected, 0.5 dB at ≥ 13/16.
   - FWER ≤ 0.0490, strong (union bound; graphical procedure, R43–R45). No α passes between chains.
   - Pre-registered power at p = 0.75: 0.63 (noise), 0.405 (speech).
4. **Decision.**
   - A detection at 0.9 dB in **either** chain sets AX47's bound to 0.5 dB for all scenes. A speech non-detection never cancels a noise detection.
   - A detection at 0.5 dB is a finding for the class (c) round.
   - A failed anchor voids that chain's block. It gets one rerun and is never recorded as "not detected". A non-detection is never a reason to rerun.
5. **The step.**
   - A change of g dB in tail energy, uniform across all 8 bands.
   - Two IrSets from one StagedBuild through `useDiffuseLevel`.
   - The shipped 30 ms AQ4 equal-gain fade (AX18).
   - Rendered with `render_cli --realtime-emulation`: fixed block, P = 512, onset at a seeded partition boundary.
   - The g flag is validation-only and off by default. A test shows `src/plugin` never reaches it, and at 0 dB it nulls bit-exactly against the shipped render.
6. **Assertions on every stimulus.**
   - The early parts are bit-identical.
   - 10·log10(E(stepped − unstepped)/E(unstepped)) = 20·log10|10^(g/20) − 1| over the tail window.
   - The `[ax47-midfade]` checks pass.
   - `tools.acoustics clicks` is clean.
   - The per-band wet-output change and the window's specular share are printed.
7. **Trial structure.**
   - B is the unstepped IrSet, held throughout. A carries the step. X is A or B.
   - Direction: 8 up and 8 down per block, in random order.
   - At least one T30 of programme before the step, and at least 2 s after it.
   - Fully wet.
   - Whole pre-rendered files are played, with no live switching and no visual cue.
8. **Signals.**
   - Pulsed pink noise: gaps ≥ T30(1 kHz), with the step at a gap start.
   - Speech: McGill TSP v2, 48 kHz, one adult speaker and file pair fixed in the pre-registration. Two Harvard sentences with a pause ≥ T30. Onset as in Q5.
   - The anechoic room's low-frequency cutoff is recorded as unknown.
9. **Scene.** `layout4_s1/default`, fixed tailSeed, 48 kHz, asserted capped at m = 6, 7 and 8, the candidate pins. If the pin uncaps it, use `listener_wall`. r/r_c and D/R are printed. It is named "occupied mid-size hall envelope, not a validated preset".
10. **Chain.**
    - Omni, presented diotically, on wired headphones, model recorded.
    - Fixed, recorded level, at or above monitoring level.
    - No normalisation of A, B or X.
    - 48 kHz, no resampling. No virtualisers, enhancers, ReplayGain or Bluetooth.
11. **Blinding.** The seeded key's hash and every stimulus's SHA-256 are committed before the run. A script writes and scores the answers. It refuses to unseal a 0.5 dB block unless 0.9 dB was detected in that chain.
12. **Distribution.**
    - Stimuli are built locally only.
    - Published: the build script, our own SHA-256 of `48k.zip` and of the excerpt, the seed and the sealed answers.
    - A THIRD_PARTY row carries the BSD notice.
    - Stimuli enter a public listening pack only with a written consent or redistribution statement from the corpus author.
13. **Record.**
    - Per listener and stimulus: k/16, exact p, anchor k/6, size, scene hash, tailSeed, commit, chain and level.
    - Wording: "detected (≥ c/16, family α 0.049)" or "not detected in 16 trials by one listener (power 0.63 / 0.41 at p = 0.75)"; "inconclusive" if the anchor failed.
    - Never "inaudible", and no public copy.

**AX49 L4**
14. As AX49 writes it: provisional against exact, T60 8 s, fully wet, 16 trials, ≥ 12/16, its own family. The chord is released into at least L of free decay. Same chain and tool, with the 6-trial anchor.

**Follow-on**
15. **08-3.** The AX47 self-ABX is rerun on the binaural chain at the bound in force, before Phase 08's goldens freeze.
16. **Scheduling.** The listening session is a dated item in the session brief. If neither 07c-2 nor 07c-2b can hold it, it goes to Maisara as a person's action.

D-W2's map, ordering and PRD check are unchanged from file 11: X-5 with a maximum of 1 and a sum of 12; X-3 dropped on Seat 1's 2/2.

## D-W1: waiting list, corrected

1. **D-W3 (H-2c) implemented,** with M7 (≤ 700 ms, flat in m) and M7b in, and TSan green. This is the condition behind Seat 5's W-C2 cell.
2. **The ABX and the class (c) / load-fallback round.** Carried into that round:
   - K-b: Seat 1 2/3 (unconditioned), Seat 3 1/3;
   - K-a: Seats 2, 4, 5 and 6;
   - Seat 6's `medium_room` insertion check (≤ 1 s, or insertion goes to that round);
   - Seat 2's condition that the constant is not committed to `src/` until the keyless path is decided.
3. **Pin-time measurements.**
   - M1: single-thread U1 on three OSes.
   - M3: the s = 1 cube's 30-replicate p95.
   - M4–M6: K-a restores for the s = 1 cube and every layout 4/5 placement, insertion, and 8-instance loads.
   - M8: B1-b with a capped builder scene.
   - M9: the bounce, including the layout 4 s = 1 automation bounce.
   - A three-OS SE / VOV print at the pin: if any OS reads > 0.33 dB at ×6, take ×7.
4. **U2, recorded in each seat's own terms.**
   - Seats 2 and 8: print-only. Clause 2 is never a W term; a breach goes to Seats 3 and 8.
   - Seat 5: a check at derivation time, worst of ≥ 3 runs, never an asserted CI gate.
   - Seat 7: a non-binding ceiling that may bind only above m\*. If it binds at or below m\*, the bounce ratio becomes a disclosed figure.
5. **Ordering.** "W-C2 at m = 6 (or 7) wins" is conditional on item 1. The PRD check against the NFR preamble (L101), with the M4–M6 usability costs shown, is redone at the re-decision.
6. **D-W4** is not on D-W1's path: it changes no W.

---

## State

| id | state |
|---|---|
| FM-W3a | **withdrawn**; condition 4 stands |
| D-W3 | **revised to H-2c** (max 2, sum 16); proposed for interrogation |
| D-W4 (new: should the reverb level follow during long automation, by adopting completed solves mid-motion?) | **deferred**, UNDERINFORMED; evidence: M7b plus Seat 1's blind listening check; then possibly NEEDS MAISARA (a) |
| D-W2 | **final**, both corrections applied |
| D-W1 | **waiting** (items 1–3) |

## Decided for Maisara

- **D-W3 (H-2c).** Edits now update the room's early sound at once, instead of waiting for the long reverb-level calculation. As today, the reverb level settles only after automation stops. This lands before the golden round, and Phase 08's goldens wait for it.
  - Rests on FR-SIM-6 and NFR-3 (AQ4).
  - Seat 5 gives the most: it has a second actor to keep safe, and gets back its own safety conditions and TSan as the acceptance test.
  - Seats 1 and 6 keep a later 2 that only she can lift (D-W4).
  - It amends none of her decisions.
- **D-W2.** Final listening-test design, as pre-registered above. Rests on NFR-1. Amends nothing.

**NEEDS MAISARA:** none now. Once D-W4's evidence is in, it may come to her as case (a): should the reverb level catch up in small steps during long automation (which follows the movement, but may be heard as steps) or stay frozen until the automation stops (no change while moving, but one larger step at the end)?
