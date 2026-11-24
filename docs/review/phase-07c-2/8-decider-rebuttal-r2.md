<!-- Saved by the orchestrator from the decider's report, 2026-11-22. -->

# Phase 07c-2, decider rebuttal round 2: D-W1, D-W2, FM-W1a, FM-W1b

To be saved as `docs/review/phase-07c-2/8-decider-rebuttal-r2.md`. Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Bottom line:**
- **D-W1 is withdrawn.** The new local timings say no work cap satisfies both the accuracy floor (needs at least 6×) and the 700 ms ISM-hold limit (fails at 6×). My own rule sends that case back to the board, so I open a new matter, **D-W3**: the ISM update being held behind a running solve.
- **FM-W1a and FM-W1b are withdrawn.** FM-W1b is moot. FM-W1a is corrected in part (load mark, PRD ids) and deferred in part (the per-emitter reading).
- **D-W2 is revised.** The S2, S5 and S8 cells are re-read from their conditions. The S6 cell on X-5 and the S1 cell on X-3 (Seat 6's form) go to those seats, with the outcome fixed in advance. The speech source is chosen: McGill TSP v2.
- **No composed variant is built this round.** H-2 below is a minimal valid variant for a new matter, marked mine.

## 1. Verdicts accepted and the state of each item

| item | verdict | my answer | state |
|---|---|---|---|
| D-W1 | TENSION MISREAD (M-1 to M-4) plus 10 corrections | Accepted. The rule falls on Q3's evidence anyway (§2). | **withdrawn**; measurements needed (M7 on CI); new matter D-W3 convened (§5) |
| FM-W1a | PRD MISREAD | Accepted (§3) | **withdrawn**; partly restated, partly deferred |
| FM-W1b | PRD MISREAD | Accepted; moot once D-W1 falls | **withdrawn** |
| D-W2 | TENSION MISREAD plus 6 corrections | Accepted (§4) | **revised**; two cells put to seats (§6) |
| Seat 3 code claim (C-1) | correct in substance; imprecise in one detail | Accepted: an edit that arrives during the solve waits for the solve, not for `finishExact` or `makeIrSet` (L539 comes before L545 and L547) | carried into D-W3 |

**D-W1 corrections, all applied:**
1. Sums: 21, 25, 27.
2. At most one composed variant per round. Round 1 built two, which was wrong.
3. U1 alone gives m ≤ 10 at 44 ns and m ≤ 8 at 56.4 ns.
4. U3 at roughly the pool solve time; the "2× slower" factor came from the double count (H-2).
5. W-6′ is checked at the pin itself, measured, never assumed monotone.
6. Seat 1's three-OS SE and VOV print at the pin is adopted.
7. Seat 5's K-a record includes layouts 4 and 5.
8. D1-L4 restated: W-4 already fails at (A) on Linux (12.0 s) and macOS (12.8–13.3 s); it passes on Windows (9.7–9.9 s).
9. D1-L5 restated: Table 15.1 gives "time available for filter update". The text says VR user behaviour "informs" the speeds. Mapping its 3 s row onto the solve alone is by extension, not an equality.
10. The K-b veto-grade ratings go to the class (c) round, verbatim: Seat 1 "K-b unconditioned: 2 / 3"; Seat 3 "K-b: 1 now / 3 later as a general source".

**D-W2 corrections, all applied:**
1. X-1 drops at step 3 (S1 2 now), not at bounds.
2. Sums: X-1 17, X-2 18, X-4 18.
3. Step assertion, valid for down-steps as well: 10·log10(E(stepped − unstepped)/E(unstepped)) = 20·log10|10^(g/20) − 1|. The reference is the unstepped E_b IrSet's tail.
4. Zotter & Frank L1515 is cited as §4.9.8.
5. A Seat 5 debt row is added, and Seat 7's "undo" is filled (§4).
6. "With feedback" during familiarisation is Seat 1's design choice. BS.1116-3 §4.1 supports only "familiarisation mandatory".

## 2. Answers on D-W1 (Q1–Q3)

**Q3, U3. The m\* … m_max window is projected empty.**
- **m\* = 6.** From M2 (local and deterministic: AX39 D5/D7, so CI gives the same values):
  - worst non-both-near SE is 0.375 dB at ×5 and 0.323 dB at ×6;
  - both at `layout4_s1/listener_corner` e1;
  - margin at ×6: 0.007 dB.
- **U3 rests on a plan default, not only a seat condition.** AQ4's rationale says its interval "is within Vorländer Table 15.1's translational update time (700 ms for moves > 0.25 m)". AQ4 is the plan's default for PRD Q4, and PRD NFR-3 (L107) sends "this tension … to the Expert". So 700 ms is the plan's own yardstick for this tension.
- **Projection.** Per C-1, the hold is about the remainder of the running solve plus the ISM. That is up to one full pool solve. Interrogator correction 4 puts local per-scene pool cost inside CI Linux's range. Local pool(4) maximum medians over the capped reported set:
  - ×5: 590 ms;
  - ×6: 810 ms;
  - ×8: 813 ms.
- **Result.** U3 projects to hold at m ≤ 5 and fail at m\* = 6. The window [6, m_max] is projected empty on Linux. The pre-registered clause of the round-1 rule ("no m ≥ m\* meets U1–U3 → back to the board, with C-a (i)") applies. **D-W1 is withdrawn**, and I convene D-W3 (§5).
- **What could overturn the projection.** M7 measured on the three CI OSes: the true hold at m = 4, 5, 6, 8. macOS CI runs a pool of 3 threads, and its 05h single-thread cost was lower (28.7 ns). Until M7 is in, the empty window is a projection, not a fact. That is why D-W3 is convened now and not decided.
- **Monotonicity of W-6′.** Not assumed. At any candidate pin, W-6′ is measured at that m (correction 5).

**Q1, Seat 5 on W-C2.** No stated condition of Seat 5 supports reading W-C2 as 1/1. Its words were "W-6 alone" 2/2 and "used as a check beside W-5: can live with". The W-C2 cell goes to Seat 5 in the D-W1 re-decision round (§6). It is moot this round because D-W1 is withdrawn.

**Q2, the backstop. Deleted.**
- It contradicts phase-07c-2 scope 9 ("The ABX runs first … in this phase"; class (c) and the load fallback are "this phase's loop").
- It breaks Seat 2's sequencing condition ("the constant is not committed to `src/` until the keyless path is decided").
- **Revised sequencing:**
  - The constant is committed only after the class (c) round rules, inside 07c-2.
  - If the ABX or that round cannot fit, the remainder goes to `phase-07c-2b.md` under CLAUDE.md's two-session rule, still before the first release (condition 1).
- Seat 7 rated the sequencing "later 2" without its backstop, so Seat 7 is asked to rate the 07c-2b slip path (§6).
- **Debt row added:**

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 7 (sequencing) | the golden round and the class (c) round may move to 07c-2b; the listener's session stays on the critical path | one split file, and a later golden round before release | the ABX date | 07c-2 or 07c-2b lands before Phase 13's beta |

- **K-a cells.** With the backstop gone, D-W1 does not ship K-a. The class (c) round decides the keyless path, with these cells as its inputs: S2 1/2, S4 1/2, S5 1/2, S6 1/2 (2/2 at ×16), and the K-b veto-grade cells from correction 10.
- **U2 as a ratio term.** Seats 2, 5 and 7 each said the bounce does not set W. U2 is Seat 8's cap. So U2 as a term goes to Seats 2, 5 and 7, and Seat 8 re-projects without the wrong 2× factor (§6).

## 3. FM-W1a and FM-W1b (Q4, Q5)

**PRD ids, corrected.**
- The accuracy ranking and "usable" are both in the **NFR preamble, L101**: "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a DAW session."
- NFR-1 (L105) is the measured match against real IRs plus listening tests.
- NFR-2 (L106) accepts heavy CPU and latency "when they buy accuracy". It says nothing about usability.
- NFR-3 (L107) sends the smoothness tension to the Expert (Q4), whose plan default is AQ4.

**The load mark: a reading, no amendment.** AX38 (iv) defines its 10 s line on **the time until the last instance is audible at load**. Since 07c-1 that means audible at the interim level. The final-settled time is named only as a finding above 10 s.
- Under (C), W enters the time-until-audible only through a keyless stage-1 solve: K-a, or `medium_room` insertion (FM-B2).
- So the load mark binds W through the keyless path, which is the class (c) round's matter.
- It does not contradict "not kept at (A)".
- My W-4 ("final tail settled ≤ 10 s") misstated the mark. I withdraw that formulation. No amendment of her decision is needed for this part.

**Per emitter or per scene: deferred, with a case (a) risk stated.**
- No PRD passage calls for reading "Seat 6's 3 s per emitter" as per scene. The preamble names usability but gives no number. The per-scene form is Seat 6's own correction of its own criterion (05h file 5 L29), not a PRD requirement.
- The question does not bind this round. With U3 in force, U1 (per scene) is not the binding upper term at m ≤ 6: the local single-thread maximum at ×6 is 2 281 ms.
- It becomes decisive only if D-W3 removes U3.
- If it does become decisive, I will first test whether a per-scene bound satisfies the per-emitter text as a stricter limit. If that reading needs an amendment and only the preamble supports it, I will return it as **NEEDS MAISARA, case (a)**: the PRD is silent on a usability number.

**FM-W1b: withdrawn.** Under K-a, capped keyless restores grow with m (T5: the s = 1 cube 35–40 s at ×8). U1–U3 do not bound that. It is the class (c) round's usability cost against L101. The "≤ 0.164 dB at ×16" figure was wrong (0.171 dB, T3) and lay outside U1.

## 4. D-W2, revised

**Cells re-read from the seats' conditions:**
- **S2: 1/1.** Its X-1 condition, "add 0.5 dB as a second step in a fixed sequence", is met. Its 0/1 belonged to the 0.75 → 0.5 variant.
- **S5: 1/1.** The chain has a stop rule, which is the reason it gave for X-3's 1/1 ("the script refuses to unseal later sizes").
- **S8: 1/1.** Speech at 13/16 has power 0.405, so its 12/16 reason for 0/1 does not apply. Its X-2 anchor condition gives 1/1.
- **S6: put to Seat 6.** Its X-2 cell, 2/2 for "13–14/16 misses a real effect", may apply to the 13/16 speech chain.
- **S1 on X-3 in Seat 6's form** (anchor, noise then speech in one sequence, 0.75 → 0.5, 12/16 each): unrated. Seat 1 said only that a sequence across stimuli is "useless". **Put to Seat 1.**

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | sum (S6 or S1 = 1/1) |
|---|---|---|---|---|---|---|---|---|---|---|
| X-5 as decided | 0/1 | 1/1 (cond.) | 0/0 | 0/1 | 1/1 (cond.) | **?** | 1/1 | 1/1 (cond.) | 0/0 | 12 |
| X-3 (Seat 6's form) | **?** | 0/1 | 0/0 | 0/1 | 1/1 | 1/1 | 1/1 | 1/1 | 0/0 | 12 |

**Outcome fixed in advance:**
- If S6 rates X-5 ≤ 1 and S1 rates X-3 ≤ 1: the sums tie at 12. Step 6 picks X-5, which is cheaper to undo. X-5 yields speech evidence in every outcome. X-3 tests speech only after noise has detected at both sizes, so speech evidence needed later (08-3, the class (c) round) would cost a new listening session.
- If S1 rates X-3 2: X-5 wins at step 3.
- If S6 rates X-5 2 and S1 rates X-3 ≤ 1: X-3 in Seat 6's form wins.
- If both are 2: I compose one variant next round from the two seats' conditions.

**Speech source: McGill TSP v2 at 48 kHz.**
- **Why TSP (R35):** it is the only candidate documented as recorded in an anechoic room (15 cm). That meets Seat 9's condition (iv). Its licence is Simplified BSD, which meets Seat 7's licence condition.
- **Why not the others:** VCTK is hemi-anechoic and its licence conflict is unresolved (R30–R32). CMU ARCTIC was recorded in a foam booth (R34). LibriSpeech's "clean" is a recogniser-error label, not an acoustic one (R41).
- **Rules for its use:**
  - adult speakers only, so the CA and CB child recordings are excluded;
  - one speaker and file pair, fixed in the pre-registration;
  - the stimulus is two Harvard sentences with a pause of at least the scene's T30, and the step falls inside the pause;
  - our own SHA-256 of `48k.zip` and of the excerpt, computed on first fetch;
  - built locally; THIRD_PARTY row with the BSD notice;
  - the 46 dB SNR is recorded in the pre-registration.
- **Not decided:** whether the stimuli may go into the public listening-pack artifact. No consent statement exists (R35), and CC BY or BSD do not cover personality rights (R38 by analogy). **Asked of Seat 7.** Local-only is the default meanwhile.
- **FWER:** confirmed by R44 (a valid graph: Σw ≤ 1, g₁₂ = g₃₄ = 1). Strong FWER ≤ 0.0490 by the union bound, with no independence assumed. I do **not** take the α-exhaustive pass between chains (R44): it would change the pre-registered α.

**Debt rows added:**

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 5 (L1) | the stop rule is enforced in the script; stimuli pinned by hash | one session if the script is wrong | 08-3, 09 reruns | hash-pinned planned reruns |
| 7 (L1) | listener time and record wording | another listening session (about 4 sessions) | the run | the record |

The rest of D-W2 (anchor, chain, step rendering, L4, the 08-3 binaural rerun) stands as in file 5, with corrections 3 and 6 applied.

## 5. New matter D-W3: the ISM update held behind a running solve (CONVENE)

**Restatement.** Seat 3 found, and the interrogator confirmed from the code (C-1), that an edit arriving during a builder solve waits for that solve. 07c-1's condition 4 ("the ISM update is never held behind the diffuse solve") therefore holds only after a quiet spell. Under AQ4's 700 ms yardstick, this hold caps W below the accuracy floor m\* = 6.

What depends on D-W3:
- `ScenePipeline` (the builder loop and `builderAbandon_`);
- the D-W1 window;
- `[pipeline]` and TSan tests;
- AX38 (iii) "settling".

**Options:**
- **H-0: no code change.** U3 caps W. Then W is either pinned at m ≤ 5, where W-6′ fails at `layout4_s1/listener_corner` e1 (0.375 dB, U raised), or W-6′ is relaxed.
- **H-1 (Seat 3's C-a (i)): cancel-on-edit.** A newer edit cancels the in-flight builder solve at its stop points (`run.stop`), and the builder coalesces to the newest scene. Known risk: under continuous automation, every solve may be cancelled. The B1′-held diffuse level then plays until the automation stops.
- **H-2 (mine, minimal valid variant): decouple.** While a solve runs, the builder serves each edit's B1′ IrSet (the new ISM over the held E_b) without waiting. The solve runs off the builder thread, still serialised at the gate. Its result is adopted in one AQ4 step only if its scene is still the current one (the generation check). This is condition 4 read literally. It is a larger threading change.
- **H-3: relax U3.** Change the 700 ms yardstick. This touches AQ4's rationale, a plan default for an Expert-owned question (Q4, NFR-3).

**Convening table:**

| seat | status | reason | focus |
|---|---|---|---|
| 1 | convened | what the user hears: a stale diffuse level during long automation (H-1); W-6′ relaxed (H-0) | rate H-0 to H-3 |
| 2 | convened | engine: the solve as a pure function; abandonment and adoption; prefix and determinism | rate; H-2 adoption rule |
| 3 | convened | lead: time variance under automation; C-a | rate; does H-2 meet C-a? |
| 4 | convened | binaural ISM build cost at 08 under the 700 ms | rate |
| 5 | convened | threading, the gate, TSan, quiesce and cancel; real-time safety | rate; H-2 topology |
| 6 | convened | "settling" during drags and automation; the user's controls | rate |
| 7 | convened | cost: scope and schedule; whether this is 07c-2's or a 07c-1 defect routed to 07d / 10-1 | rate |
| 8 | convened | producer automation: a stale room during long moves | rate |
| 9 | convened (cheap) | probably NOT MY MATTER; confirm | rate or decline |

**Shared brief (pass on verbatim):**

> **Matter D-W3.** An edit that arrives during a builder solve waits behind it (`ScenePipeline.cpp` L315, L114, L849, L494–543; interrogator file 6 row C-1). The hold is about one pool solve: locally ×5 590 ms, ×6 810 ms, ×8 813 ms at the capped reported set. AQ4's yardstick is 700 ms (Vorländer Table 15.1, by extension). The accuracy floor needs m ≥ 6 (`2-fact-sheet-part3-m2.md`).
>
> **Options:** H-0 no change (W ≤ ×5 or W-6′ relaxed); H-1 cancel-on-edit (starvation risk under continuous automation); H-2 decouple (B1′ IrSets served during the solve; generation-checked adoption); H-3 relax U3.
>
> **Read:** files 2 (parts 1–3), 5, 6 and 8 of `docs/review/phase-07c-2/`; BUILD_PLAN AQ4, AX18, AX38 (iii), AX48 (B1′), AX49; phase-07c-1 condition 4.
>
> **Return:** for each option, now / later with a one-line reason; conditions of acceptance for any 2 or 3; future debt (07c-2, 07d, 10-1, 13).

## 6. Questions for the orchestrator to run

| to | question |
|---|---|
| Seat 5 | (a) Rate W-C2 (W-6′ selects, W-1′ caps) and W-C1′ (with U2 as a ratio term), on the corrected facts: m\* = 6; U3 projection; per-scene costs counted once. (b) Rate D-W3. |
| Seat 2 | (a) Rate U2 (Seat 8's bounce cap) as a term in W-C1′ and W-C2. You said the bounce does not set W. (b) Rate D-W3. |
| Seat 7 | (a) The same U2 question. (b) Rate the sequencing without the backstop, with slip to 07c-2b before release. (c) TSP stimuli: local-only, or the public listening pack with a BSD notice, given no consent statement? (d) Rate D-W3. |
| Seat 8 | (a) Re-project U2 at m = 5, 6 and 8 without the "local 2× slower" factor (CI ≈ local per scene). Does U2 bind? (b) Rate D-W3. |
| Seat 6 | (a) Rate X-5 as decided: speech chain at 13/16 (power 0.405), noise chain at 12/16, Bonferroni split, 3 dB anchor. (b) Rate D-W3. |
| Seat 1 | (a) Rate X-3 in Seat 6's form: anchor, then noise 0.75 → 0.5, then speech 0.75 → 0.5, one fixed sequence at 12/16 each. (b) Rate D-W3. |
| Seats 3, 4, 9 | Rate D-W3. Seat 9 also: does TSP (anechoic, 15 cm, Harvard sentences) meet your condition (iv)? |

**Measurements (orchestrator), needed before D-W3 and the D-W1 re-decision:**
- **M7 on CI, three OSes.** The ISM latency of a position edit at a random point of a running builder solve. Take m = 1, 4, 5, 6, 8; 1 instance; `layout4_s1/listener_corner` and the s = 1 cube; pool size; worst over ≥ 3 runs. This settles whether the window is empty off this local box.
- **M7b.** Under H-1's rule, the fraction of solves that complete during the AX38 (iv) automation patterns (room size stepping 1 m every 5 s; the 05i joint step; continuous automation) at m = 6 and 8. This is a starvation record.
- M1 and M3–M6, M8, M9 from file 5 stay pending for the D-W1 re-decision.

**Research:** none new is needed. Leads that are not blocking: Miller et al. (2025), an anechoic corpus with an unknown licence; and the VCTK licence read from the archive's own files.

## 7. Summary

| id | decision | state | worst-off | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-W1 | — (round-1 rule fell on its own clause) | withdrawn; measurements needed (M7) | — | — | — | L101, NFR-1, NFR-3 via AQ4, condition 3 | Vorländer Table 15.1 (by extension) | M7 on CI shows U3 holding at m ≥ 6 |
| D-W3 | — | convening (all nine) | — | — | — | L101, NFR-3 (Q4 → AQ4) | Table 15.1 via AQ4 | — |
| FM-W1a | load mark read on its AX38 (iv) definition, binding W only via the keyless path; per-emitter reading deferred | withdrawn / partly restated | — | — | medium | L101, NFR-3 | — | D-W3 removes U3 (then possibly NEEDS MAISARA, case (a)) |
| FM-W1b | — | withdrawn (moot) | — | — | — | — | — | — |
| D-W2 | X-5 (noise 0.9 → 0.5 at 12/16, speech 0.9 → 0.5 at 13/16, FWER ≤ 0.049, 3 dB anchor); speech McGill TSP v2 | revised; S6 and S1 cells put to the seats | 1 (pending S6) | 12 | medium | NFR-1 | Toole §19.1.1; Vorländer Table 6.1; Zotter & Frank §4.9.8 | S6 = 2 makes X-3 win; detection at 0.9 / 0.5 dB; 08-3 |

**Decided for Maisara:** nothing applied this round.

**NEEDS MAISARA:** none. If D-W3 removes the 700 ms limit and the per-emitter versus per-scene reading of Seat 6's 3 s then decides W, it may come back as case (a).
