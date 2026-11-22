<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2, decision round 3: D-W3, D-W2 final, and what D-W1 still waits on

To be saved as `docs/review/phase-07c-2/11-decider-decision-r3.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**In short:**
- **D-W3** is decided: the solve moves off the builder thread (option H-2, as composed below). It needs one answer for Maisara (FM-W3a), because it changes her accepted "never mid-drag" rule.
- **The fix lands in 07c-2, or in 07c-2b as its first work, before the golden round.** Phase 08's goldens wait for it.
- **D-W2 is final as X-5.** Speech is McGill TSP v2, built locally only.
- **D-W1** waits on the D-W3 implementation, two measurements under it (M7, M7b), the ABX and class (c) round, and the pin-time measurements. On the current cells, W-C2 at m = 6 (or 7) would win.
- **Composed variants this round: one,** H-2\* in D-W3. None in D-W2 or D-W1.

---

## D-W3: the ISM update held behind a running solve

### Code facts (checked at HEAD)

- **The ISM waits behind the solve.** `ScenePipeline.cpp` L541–560 (the seats cite pre-shift numbers L539–543).
  - An edit's B1′ IrSet is committed first.
  - The solve then runs inline on the single builder thread (`IrBuilderThread.h` L5).
  - A solved level is thrown away if `dirty_` changed while it ran (L555–560, `discardedMidDrag`).
  - So an edit that arrives during a solve waits for that solve before its own ISM is built (interrogator C-1).
- **Today's code already starves the diffuse level.** Under continuous automation no solve is ever adopted. The held B1′ level plays until the automation stops, then one AQ4 step follows. Seats 1, 2, 3 and 5 say this from the code; I confirm it. It is not specific to H-1 or H-2.

### Tension map (now / later; the seats' words shortened)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max |
|---|---|---|---|---|---|---|---|---|---|---|
| H-0 no change | 1/2 | 2/2 | 1/2 | 2/2 | 1/2 | 1/2 | 1/2 | 2/2 | 1/1 | 2 |
| H-1 cancel-on-edit (with the conditions of Seats 2, 3 and 5) | 1/2 unconditioned (1/1 with a progress guarantee) | 1/1 | 1/1 | 1/2 | 1/1 | 1/2 | 1/2 | 1/1 | 0/1 | 2 |
| H-2 as stated (adopt only if the scene is still current) | 0/2 | 1/2 (without rule 1) | 1/2 | 1/1 | 2/1 | 1/2 | 2/0 | 0/1 | 0/0 | 2 |
| H-3 relax the 700 ms | 2/2 | 1/2 | **2/3** | 2/2 (3 if the specular part is relaxed) | 1/2 | 1/2 | 1/2 | 2/2 | — (NOT MY MATTER) | **3** |
| **H-2\* (composed, below)** | 0/1 | 1/1 | 1/1 *(from conditions)* | 1/0 | 1/1 | 1/1 | 1/0 | 0/1 | 0/0 | **1** (sum 12) |

### Working

1. **Bounds.** None broken outright. H-3 touches AQ4's rationale, the plan default for the Expert-owned Q4 (NFR-3, PRD L107).
2. **Veto.** H-3 is dropped: Seat 3 rated it 3 later ("trades a sourced yardstick for convenience").
3. **Worst-off seat.** H-0, H-1 and H-2 as stated all reach 2.
4. **Compose.** One variant, H-2\*, built from the seats' conditions:
   - Seat 5's topology for H-2 → 1/1.
   - Seat 2's rule 1, problem-key adoption → 1/1.
   - Seat 3's (a): M7 is re-measured under H-2. Seat 3's (b): a superseded solve stops at its next stop point.
   - The progress and recency rule asked for by Seats 1, 4, 6 and 8, which Seat 2 offers as its rule 2.
   - Seat 7: the fix lands before the golden round, with Seat 5's gates.

   Why H-1 plus a progress guarantee does not reach a maximum of 1: a protected solve would hold the ISM again on the single builder thread. That breaks Seat 3's C-a and Seat 5's (iii) ("≤ 700 ms at every m, flat in m"). So progress and a free ISM need the decoupling.
5. **Sum** (if needed): H-2\* = 12.
6. **Decide: H-2\*.**

**Cell read from conditions, for the interrogator to check.** I read Seat 3 on H-2\* as 1/1 from its stated conditions. Its (b), "a doomed solve stops at its next `run.stop`", is kept, with one exception: at most one superseded solve per 3 s runs on to completion. That result is used as the held level, not wasted, and it does not hold the ISM under H-2. If Seat 3 disputes this reading, the cell goes to Seat 3.

### DECISION D-W3: H-2\*

1. **The solve runs off the builder thread.**
   - It runs as a task on the process-wide gate executor, never as a thread per instance (no instance cap).
   - Input: an immutable snapshot of the `DiffuseProblem`, together with E_prec and E_model.
   - Output: returned through a shared-ownership mailbox.
   - **Only the builder commits** (the L566 single-committer invariant is kept).
   - The gate is held around the solve as before (AX38 (i)).
   - The pool is `hardware_concurrency − 1` while a builder works alongside (Seat 5). Outputs do not change, by D4.
2. **The builder never waits for a solve.** Each edit gets its B1′ IrSet at once, as at L508–540. The builder then hands the solve over and returns to serve edits.
3. **When a finished solve becomes the final.** Only if its problem key (a hash of `DiffuseProblem` plus E_prec and E_model) equals the current scene's (Seat 2 rule 1). It is adopted in one AQ4 step. It must be bit-identical to an uncancelled one-shot solve (D7).
4. **A solve whose scene has been superseded:**
   - It is stopped at its next stop point. A per-generation cancel token does this, separate from `builderAbandon_` (Seat 5 (i)). Stop points are spaced by a fixed work count, never by time (Seat 5 (ii), AX41). A cancelled solve never yields an E_b (Seat 2).
   - **The exception:** if no solve has finished on this pipeline in the last **3 s** (Table 15.1's 3 s row, by extension; the anchor of Seats 4 and 6), the superseded solve runs to the end.
   - Its E_b is then adopted **as the held level, never as a final**, if it is newer than the level playing. That is one AQ4 equal-gain step.
   - The per-band size of that step is recorded against AX47's bound, on the builder thread (Seat 6). It sits in B1′'s class: outside AX47's scope, with the step recorded.
   - This rule needs FM-W3a.
5. **Unchanged:** offline renders and `render_cli` wait for the final synchronously (AX5, condition 6). `quiesce()` waits for, or safely orphans, an in-flight task (Seat 5). "Settling" stays on until the final lands (AX38 (iii); its drawing is 11-3's).
6. **Tests:**
   - a TSan `[pipeline]` stress test with edits at random solve points, and with the pipeline destroyed mid-solve;
   - finals bit-identical with and without cancelled predecessors;
   - offline output bit-identical;
   - `[reset-nowait]` still green;
   - B1-b re-run with the solve duration printed (Seat 5).
7. **Measurements (acceptance):**
   - **M7 under H-2\*:** the ISM latency of an edit made mid-solve, with the solve occupying the pool. Three CI OSes; m = 1, 4, 5, 6, 8; capped scenes. It must be **≤ 700 ms on the worst OS and flat in m** (Seat 3 (a), Seat 5 (iii); AQ4's yardstick).
   - **M7b:** under the AX38 (iv) patterns and continuous automation, compared with H-0's `discardedMidDrag`: the fraction of solves that finish, the interval between held-level adoptions (target ≤ 3 s), and the distribution of step sizes (Seats 1, 3 (c), 4, 6, 7).
8. **Routing:**
   - This is a defect of 07c-1's condition 4, recorded in the ledger as such.
   - It lands in **07c-2**, or as the **first work of 07c-2b**, before the golden round. Seat 7 rates routing it past the golden round later 3.
   - Plan text through `/fix-plan`: BUILD_PLAN §0 records that "08-x goldens are frozen only after 07c-2 (or 07c-2b) is `done`" (Seat 7's condition).

**Load-bearing claims:**
- **D3-L1 (code).** The ISM waits behind the solve; superseded solves are discarded (L541–560; interrogator C-1).
- **D3-L2 (corpus, by extension).** Table 15.1 gives 700 ms for the specular part (moves > 0.25 m) and 3 s for the specular and scattering parts (moves > 1 m) (Vorländer §15.3, L3965–3966). These are VR filter-update intervals. AQ4's rationale uses the 700 ms row.
- **D3-L3 (local measurement).** The pool hold is 590 / 810 / 813 ms at ×5 / ×6 / ×8. This is why H-0 caps W at 5, below m\* = 6.

**PRD acceptance:**
- FR-SIM-6 ("follow … movement without audible artifacts") and NFR-3, routed through AQ4.
- H-2\* serves both: the ISM follows at once, and the diffuse level follows within about 3 s.
- H-1 serves the ISM, but the diffuse level is starved.
- H-0 strains FR-SIM-6 (a hold of up to 590 ms) and the preamble's accuracy priority (W ≤ 5).
- H-3 strains FR-SIM-6.
- No PRD goal points to another survivor.

**Future-debt register (later ≥ 1):**

| seat | commits later phases to | undoing costs | evidence | repaid when |
|---|---|---|---|---|
| 1 (L1) | a step at the end of automation still exists; held-level steps during motion | change the rule | M7b; 10-1 automation item | M7b steps within AX47 |
| 2 (L1) | the problem-key adoption and the bit-identity tests | one function | 07c-2 CI | tests green |
| 3 (L1) | the worker topology must survive 07d's synthesis moves; Phase 10 sets the motion law | a revert to the serial builder | 07d, 10-1 | 10-1 gate |
| 5 (L1) | a second actor: lifetime and TSan surface | revert | TSan, 08-4, 10-1 | stress test green across 07d / 08 |
| 6 (L1) | how "settling" is drawn during the diffuse lag | 11-3 design | 11-3 | 11-3 |
| 8 (L1) | anti-starvation shown only by M7b | change the rule | M7b | M7b ≤ 3 s |

**Strongest objection.** Seats 2, 3 and 5 prefer H-1: a smaller change, with no second actor. Seat 5 rated H-2 2 now as stated.

It holds anyway:
- H-1 without a progress rule leaves the 2-later cells of Seats 1, 4, 6 and 7.
- H-1 with one re-holds the ISM on one thread.
- Seat 5's own conditions bring H-2 to 1/1.

It fails if TSan or lifetime safety cannot be shown in 07c-2b, or if M7 under H-2\* exceeds 700 ms because the solve and the ISM compete for cores. The board then returns to H-1 with the progress question.

**Confidence:** medium. The code facts are known; M7 and M7b are pending.

**Reversal:** M7 > 700 ms or not flat in m; M7b shows adoptions more than 3 s apart, or steps above AX47's bound; a TSan race.

### FOR MAISARA FM-W3a: diffuse adoption during continuous edits

**Question.** May a finished solve for a superseded scene be adopted mid-automation, as the held level?

**Answer.** Condition 4 reads: "exactly one step per solve, never mid-drag; a solve whose scene (problem key) is still current is adopted as the final. During continuous edits or automation, a solve that finishes for a superseded scene is adopted only as the held (B1′) level, only if it is newer than the level playing, at most one such solve per 3 s, and never as a final; each step is one AQ4 crossfade, recorded against AX47."

**Rests on:**
- FR-SIM-6: "Follow automated listener and source movement without audible artifacts."
- NFR-3 (L107): "Automated movement must render smoothly … This tension goes to the Expert". Its plan default is AQ4, which rebuilds during movement and crossfades each update over 30 ms.
- Her acceptance of 2026-11-10 of decider file 47 §4 (iii) item 4.

**Reasoning.**
- From the code, "never mid-drag" together with L555 means the tail level does not follow automation at all until it stops. Then it lands in one step of the whole move's level change, which no rule bounds (Seat 1; Seat 6's W4).
- That strains FR-SIM-6's "follow".
- AQ4, the Expert-routed default, already updates the IR during movement in crossfaded steps.
- The seats that originally asked for "never mid-drag" (Seats 1, 6, 8) now ask for recency adoption. Seat 3 places the matter with Seats 1 and 6.

**Options:**
- Keep "never mid-drag": serves "no level change during motion"; strains FR-SIM-6 "follow" with one large step at rest.
- Recency adoption: serves FR-SIM-6 "follow" and AQ4's update model. It risks small audible steps during motion. Those steps are recorded, not bounded (AX47's Scope excludes B1′ steps).

**What would make her veto it:** reading "without audible artifacts" as "no tail-level change while moving". That is what the original rule protected.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (phase-07c condition 4, "never mid-drag")

---

## D-W2: final

**Map (unchanged except the two answered cells):**
- X-5: S1 0/1, S2 1/1, S3 0/0, S4 0/1, S5 1/1, **S6 1/1** (seat file 10), S7 1/1, S8 1/1, S9 0/0. Maximum 1, sum 12.
- X-3 in Seat 6's form: **S1 2/2** (seat file 10: "speech is scored only after noise detects at both 0.75 and 0.5 dB"), so its maximum is 2.
- By the outcome fixed in file 8 §4, **X-5 wins at step 3.**

**DECISION D-W2 (final).** The file 5 design, with file 8's corrections, plus these additions:
- **Seat 6's conditions:**
  - the AX47 reversal fires on a detection at 0.9 dB in either chain; a speech non-detection never cancels a noise detection;
  - a speech null is recorded with its power (0.405 at p = 0.75) and is never worded as "inaudible" on speech or program;
  - a failed anchor (< 5/6) voids that chain, and its result is never recorded as "not detected" (also Seat 1);
  - no visual cue is shown during trials.
- **Speech: McGill TSP v2 at 48 kHz.**
  - Adult speakers only.
  - Seat 9's residuals go into the pre-registration: the step falls in the first half of the pause, where the tail is at least 20 dB above the 46 dB noise floor; the step's offset from the end of speech is recorded in units of T; the anechoic room's low cutoff is recorded as unknown.
- **Distribution: local-only** (Seat 7, 0/0).
  - Published: the build script, our own SHA-256 of `48k.zip` and of the excerpt, the seed and the sealed answers.
  - Public listening-pack use only with a written consent or redistribution statement from the corpus author, recorded in THIRD_PARTY.
- **Scheduling.** The listening session is a dated item in the session brief (Seat 7). If neither 07c-2 nor 07c-2b can hold it, the scheduling goes to Maisara as a person's action, not as a decision.

**Confidence:** medium.

**Reversal:** a detection at 0.9 dB (the bound becomes 0.5 dB) or at 0.5 dB (a finding); the 08-3 binaural rerun.

**PRD check:** NFR-1 (L105). Nothing points to X-3.

---

## D-W1: what the re-decision now waits on

1. **D-W3 implemented, with M7 (≤ 700 ms, flat in m) and M7b green.** This removes U3 from the W derivation.
2. **The ABX run and the class (c) / load-fallback round.**
   - Seat 2: the constant is not committed until the keyless path is decided.
   - Seat 5: W-C1′ needs it before the pin.
   - Seat 6: `medium_room` insertion must take ≤ 1 s at pool size, or insertion moves to that round.
   - Carried to that round: the K-b cells "2 / 3" (Seat 1, unconditioned) and "1 / 3" (Seat 3, as a general source), and the K-a cells of Seats 2, 4, 5 and 6.
3. **Pin-time measurements:**
   - M1: single-thread U1 on three OSes;
   - M3: the s = 1 cube's 30-replicate p95;
   - M4–M6: K-a restores for the s = 1 cube and every layout 4/5 placement, insertion, and 8-instance loads;
   - M8: B1-b with a capped builder scene;
   - M9: the bounce, including the layout 4 s = 1 position-automation bounce (Seat 8);
   - a three-OS SE / VOV print at the pin. Seat 5 notes the AX48 fingerprints differ per OS, so cross-OS equality of the SE is not shown. If any OS reads > 0.33 dB at ×6, take ×7.
4. **State of the cells.**
   - U2 is agreed as a print-only record (Seats 2, 5, 7, 8). Clause 2 is never a W term, and a breach goes to Seats 3 and 8 (Seat 2).
   - Seat 5 now rates W-C2 1/1 (conditional) and W-C1′ 1/2. On these cells W-C2 at m = 6 (or 7) wins at step 3.
   - The PRD acceptance check, which FM-W1b got wrong, is redone at that round, with the usability costs from M4–M6 shown against the NFR preamble (L101).
   - FM-W1a's per-emitter reading only matters if W-C1′ is in contention.

---

## Summary

| id | decision | state | worst-off | sum | confidence | PRD bound | corpus | reversal |
|---|---|---|---|---|---|---|---|---|
| D-W3 | H-2\*: solve on the gate executor; builder never waits; problem-key finals; superseded solves stopped, except one per 3 s adopted as the held level; TSan, M7, M7b; lands in 07c-2 / 07c-2b before the golden round; 08 goldens wait | proposed | 1 | 12 | medium | FR-SIM-6, NFR-3 (AQ4), L101 | Vorländer Table 15.1 (by extension) | M7 > 700 ms; M7b; TSan |
| FM-W3a | condition 4: recency adoption as the held level during continuous edits | for Maisara | — | — | medium | FR-SIM-6, NFR-3 | — | her veto |
| D-W2 | X-5 final; McGill TSP v2, local-only | stands (final) | 1 | 12 | medium | NFR-1 | Toole §19.1.1; Vorländer Table 6.1 | detection; 08-3 |
| D-W1 | — | waiting (items 1–4) | — | — | — | — | — | — |

## Decided for Maisara

- **D-W3.** Edits now update the room's early sound at once while the long reverb-level calculation runs in the background. During a long automation the reverb level catches up about every 3 s instead of jumping once at the end. This is fixed before the golden round, and Phase 08's goldens wait for it.
  - Rests on FR-SIM-6 and NFR-3 (AQ4).
  - Seat 5 gives most: a second thread to keep safe. It gets back its own safety conditions and the TSan tests as acceptance.
  - FM-W3a: `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (condition 4's "never mid-drag")
- **D-W2.** The listening test's design is final. The speech is a public anechoic recording (McGill TSP), kept off public downloads until the author confirms consent.
  - Rests on NFR-1.
  - Seat 6 gives most: its noise-then-speech order. It gets back a speech test that always counts.
  - Amends none of her decisions.

**NEEDS MAISARA:** none. Booking the listening session is a person's action for her, not a decision.
