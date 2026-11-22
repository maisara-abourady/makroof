<!-- Saved by the orchestrator from the interrogator's report, 2026-11-22. -->

Interrogator on `docs/review/phase-07c-2/13-decider-rebuttal-r4.md` (decision mode, round 4). Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

# Interrogator on file 13: FM-W3a withdrawn, D-W3 as H-2c, D-W4 deferred, D-W2 final, D-W1 waiting list

## Outcome per item

D-W3 fails on one claim, Q2, which is load-bearing: as written, the adoption rule also adopts a final during an output-trim drag. Every other check on D-W3 passes, apart from wording and debt corrections. D-W4's deferral leaves its debt with no home, and D-W2 survives as pre-registered.

| item | outcome | in one line |
|---|---|---|
| **FM-W3a** (withdrawn; condition 4 stands) | **SURVIVES** | The withdrawal answers file 12's Q1 in full. Nothing is applied, and her 2026-11-10 condition 4 binds again. |
| **D-W3 (H-2c)** | **FAILS on the Q2 claim**; otherwise survives with corrections 1–4 | Q2 says "Every other edit discards the solve, as today". That is WRONG for `output_trim_db`, so the claim that H-2c sits inside condition 4 does not hold as written. The cells, the one-variant composition, the H-3 veto drop, the ordering, the PRD table and the code references all check out. |
| **D-W4 (deferred, UNDERINFORMED)** | **SURVIVES WITH CORRECTIONS** (debt home, research question) | Deferring is legitimate. But five debt rows on H-2c are repaid "when D-W4 is resolved", and D-W4 has no phase or test in BUILD_PLAN §0/§4 or the phase files. That is INCONSISTENT under my step 3. |
| **D-W2 (final, as pre-registered)** | **SURVIVES** | Both corrections from file 12 are applied correctly, and the onset rule checks out arithmetically. |
| **D-W1 waiting list** | **SURVIVES** | Corrections 1 and 2 of file 12 are applied. U2 is now recorded in each seat's own terms. |

### D-W3: why the Q2 claim is wrong

**What file 13 says.** A final is adopted if P and S are unchanged. Only `outputMode`, `hrtfId` and `tailSeed` leave S unchanged, "Every other edit discards the solve, as today".

**What the code does.**
- `setParameter` bumps `dirty_` for every host parameter (`ScenePipeline.cpp` L315).
- `output_trim_db` is a continuous, automatable parameter, −48 to +24 dB (`ParameterMap.cpp` L65).
- It never enters `SceneDescription`: it is applied on the audio path at L977–998, and `parameterValuesFromScene` takes it separately.
- So a trim edit changes neither P nor S (`sceneKey`, L235–244).
- Today a trim drag discards a running solve (L542, L555). Under H-2c the same solve is adopted as the final in the middle of the trim drag or automation. That is a diffuse-level step during a drag.
- `output_mode` (L127: "not applied in Phase 07") also leaves the scene unchanged, but it is discrete, so it raises no mid-drag question.

**Why it matters.** Whether a step during a non-scene drag is "mid-drag" under condition 4 is a reading of her decision.
- decider.md §1a treats settling the scope of a recorded decision as a question answered as FOR MAISARA, with PRD ids.
- File 13 makes that reading implicitly, on a false premise.
- Seat 3's H-1 condition (a) ("Gain, output mode and seed edits never cancel") is a seat's position, not her decision.

### D-W3 corrections

1. **Seat 2's later 2 is unnamed.** H-2c has three later-2 cells (S1, S2, S6), not two.
   - S2's comes from the (P, S) key rather than P alone. P-only is out of bounds (Q2), so no in-bounds variant lowers it either.
   - Name it in step 3, in the strongest objection and in "Decided for Maisara", which says "Seats 1 and 6 keep a later 2".
2. **The "no in-bounds variant lowers the maximum" wording.** The conclusion is CORRECT, but the stated reason is IMPRECISE.
   - Seat 1's and Seat 6's H-0 conditions are in bounds: M7 ≤ 700 ms plus the ×5 finding; naming 10-1 as the owner of the hold.
   - H-0 still keeps 2 through Seat 2: "it stays at 2 until the estimator is revisited".
   - On the decoupled variants (H-1, H-2, H-2c) both seats' conditions need adoption during motion, or a completion whose stale result condition 4 discards. That is out of bounds, as claimed.
3. **Label the S2 cell correctly.** S2 on H-2c (1/2) is Seat 2's "Without rule 1 (generation check only): 1/2". (P, S) is unrated by Seat 2, so keeping the unconditioned rating is a faithful, conservative reading. Label it that way rather than "from conditions".
4. **Debt rows repaid by D-W4.** The register rows for S1, S2, S4, S6 and S8 are repaid by "D-W4". See the D-W4 corrections below.

### D-W4 corrections

1. **Give D-W4 a home.** M7b sits in H-2c's acceptance, in 07c-2. But "a blind listening check in Seat 1's paradigm: steps during motion against one step at rest" belongs to no phase.
   - phase-10-1 has no automation listening item (grep: no match for "automation").
   - The five debt rows therefore name no existing phase or test. That has to be fixed in the plan text, or the debt is borrowed from later phases silently.
2. **State the research gap as a question for the researcher.** Is there published evidence on the audibility of small stepwise tail-level changes during source movement, compared with one step at rest? The corpus has none that I found.

---

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question |
|---|---|---|---|---|---|---|
| FM-W3a | PRD proxy | withdrawal; condition 4 stands | faithful | file 13 Q1; phase-05b2 file 47 L119 | SURVIVES | — |
| D-W3 | map | H-0, H-1, H-2 as stated, H-3 rows and sums 29 / 21 / 19 | faithful | 10-seat1…9; recount 12 + 17, 8 + 13, 8 + 11 | — | — |
| D-W3 | map | H-2c / S1 0/2 | faithful (condition not met) | 10-seat1: H-2 "0 / 2"; its recency condition is out of bounds | — | — |
| D-W3 | map | H-2c / S2 1/2 | faithful but mislabelled | 10-seat2 "Without rule 1 (generation check only): 1/2"; (P, S) unrated | correction 3 | — |
| D-W3 | map | H-2c / S3 1/1 | faithful | 10-seat3 §3: "(a) Re-measure M7 … (b) A doomed solve stops … With (a) and (b), H-2 meets C-a fully" | — | — |
| D-W3 | map | H-2c / S4 1/1, S5 1/1, S6 1/2, S7 1/0, S8 0/1, S9 0/0 | faithful | 10-seat4 H-2 1/1 (its 1 → 0 needs a bound); 10-seat5 six H-2 conditions; 10-seat6 H-2 "as written … 1 / 2"; 10-seat7 "H-2 → 1 now: scheduled as the first work of 07c-2b"; 10-seat8 0/1; 10-seat9 0/0 | sum 6 + 10 = 16 | — | — |
| D-W3 | ordering | one composed variant; H-3 dropped on S3's "2 / 3"; all survivors at max 2; sum picks H-2c | correct | decider.md §5 steps 2–5 | — | — |
| D-W3 | ordering | "no in-bounds variant lowers them" | CORRECT in effect; IMPRECISE as reasoned | H-0 conditions of S1 and S6 are in bounds, but S2's H-0 "stays at 2" | correction 2 | — |
| D-W3 | ordering | S2's later 2 not named | omission | H-2c row: S2 1/2 | correction 1 | — |
| D-W3 | claim Q2 | "Every other edit discards the solve, as today" | **WRONG** (load-bearing) | from the code: L315 every parameter bumps `dirty_`; `output_trim_db` is not in `SceneDescription` (`ParameterMap.cpp` L65, L131–152; `ScenePipeline.cpp` L977–998), so P and S are unchanged and a final is adopted mid-trim-drag | **FALLS** | Q1 |
| D-W3 | claim Q2 | AX48 S = effective scene without `outputMode`, `hrtfId`, `tailSeed`; these never re-solve | CORRECT | BUILD_PLAN L170; `sceneKey` L235–244 | — | — |
| D-W3 | D3-L1 | B1′ commit L538–540; inline solve L552–553; discards L542 / L555; committer comment L582; `IrBuilderThread.h` L5 | CORRECT at HEAD | read at HEAD | — | — |
| D-W3 | D3-L2 | Table 15.1 rows; AQ4 uses the 700 ms row | CORRECT (by extension) | Vorländer §15.3, Table 15.1; BUILD_PLAN L111 | — | — |
| D-W3 | D3-L3 | 590 / 810 / 813 ms | marked as a local projection, as asked | fact sheet part 3 | — | — |
| D-W3 | PRD proxy | acceptance table: H-2c, H-2 as stated, H-1, H-0 against FR-SIM-6 and NFR-3 / AQ4 | faithful; every survivor shown | PRD L89, L101, L107 | — | — |
| D-W3 | W-C2 link | Seat 5's condition met by the decoupling, pending M7 | CORRECT | 10-seat5 "D-W3 makes the ISM hold independent of W (H-1 or H-2)" | — | — |
| D-W3 | debt | seven later-≥1 rows | complete | S1 2, S2 2, S3 1, S4 1, S5 1, S6 2, S8 1 | — | — |
| D-W4 | debt | "repaid when: D-W4" (five rows) | INCONSISTENT (no phase or test) | BUILD_PLAN §0/§4; phase-10-1 has no automation item | D-W4 correction 1 | Q2 |
| D-W4 | inventory | audibility of in-motion steps against one end step | research gap, not posed to the researcher | no corpus passage found | D-W4 correction 2 | Q2 |
| D-W2 | Q5 | onset ≤ 0.43 · T30 after the end of speech | CORRECT (computed) | (46 − 20) / 60 = 0.433; the measured assertion is authoritative | — | — |
| D-W2 | claim | SNR about 46 dB re active speech level | CORRECT | R35 App. A | — | — |
| D-W2 | claim | scene capped at m = 6, 7 and 8 | CORRECT | T3: `layout4_s1/default` cap hit 1 at ×8, 0 at ×16 | — | — |
| D-W2 | statistics | FWER ≤ 0.0490; power 0.63 / 0.405; anchor ≥ 5/6 | CORRECT (rated earlier, unchanged) | file 6 rows | — | — |
| D-W1 | list | U2 in each seat's own terms; W-C2 conditional; D-W4 off D-W1's path | faithful | 10-seat2, 5, 7, 8 | — | — |

## Questions for the decider's rebuttal round

1. **Trim drags.** Under H-2c's (P, S) rule, a solve that finishes during an `output_trim_db` drag or automation is adopted as the final mid-drag, where today it is discarded. Is that inside condition 4's "never mid-drag"? If you hold that it is, where is that reading written as FOR MAISARA with PRD ids? If not, what does the adoption rule become, and do the S2 and S3 cells change?
2. **D-W4's home.** Which phase file or test will hold D-W4's blind listening check, and by when, relative to Phase 13's beta? What research question goes to the researcher on in-motion step audibility?

Files examined:
- `/home/user/makroof/docs/review/phase-07c-2/13-decider-rebuttal-r4.md`
- `/home/user/makroof/docs/review/phase-07c-2/10-seat1.md` … `10-seat9.md`
- `/home/user/makroof/docs/BUILD_PLAN.md` (L111, L170)
- `/home/user/makroof/src/plugin/core/ScenePipeline.cpp` (L225–252, L315, L486–582, L977–998)
- `/home/user/makroof/src/plugin/core/IrBuilderThread.h`
- `/home/user/makroof/src/module3d/ParameterMap.h` and `/home/user/makroof/src/module3d/ParameterMap.cpp` (L65, L127–153)
- `/home/user/makroof/docs/phases/phase-10-1.md`
- `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (Table 15.1)
