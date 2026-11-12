# 18 — Interrogator: AX49 after Seat 3, DC fixes, code conformance (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Targets: files 13, 14, 16, 17; commits 4ea9234, ee15c56.

**Interrogator: phase 07c-1 final checks (decision mode for D-C9, document mode for the diff re-check, a code-conformance read of file 17), 2026-11-12**

Corpus revision: `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. All 13 corpus files are present.

**Limit on this check:** I have no shell, so I could not confirm that the working tree is commit ee15c56 or 4ea9234. I read the files as they are on disk.

## Verdicts

| item | verdict |
|---|---|
| **1. D-C9 → AX49 (D3\*‴)** | **SURVIVES WITH CORRECTIONS. Row 59 is CLOSED.** Seat 3 now rates D3\*″'s T60-edit path **3/3 in its own words** (file 14 L5). Its earlier 2/2 covered only holds of about 0.25 s or less (L7). That makes the decider's veto cell faithful after the fact, so D3\*″ is excluded and D3\*‴ wins on max 2, sum 23. No NEEDS MAISARA is due. Two minor corrections remain (F-02, F-05); neither changes the winner. |
| **2. Diff fixes DC-01…14 (commit 4ea9234)** | **All 10 open fixes are applied correctly where they belong.** DC-01, the one major, is closed. DC-02, DC-04, DC-13 and DC-14 were already CORRECT and are unchanged. Two minor bookkeeping slips in the ledger (F-20, F-21). |
| **3. File 17 code conformance (ee15c56)** | **The note is right in substance. None of the items it lists as "session 2" is a conflict.** I found three deviations the note does not list (F-23, F-25, F-29), all minor, all software. F-29 is a departure from the letter of the plan, which file 17 records only as "deviation in form". It needs plan text, not just a PR note. |

## Ledger

| id | decision / target | check | item | verdict | evidence | outcome / severity | question |
|---|---|---|---|---|---|---|---|
| P07C1-F-01 | D-C9 | map / ordering (row 59) | D3\*″ S3 cell = 3 | **faithful (now the seat's own rating)** | File 14 L5: "3/3. On T60-changing edits, D3\*″ holds the ISM about 3 s…". L7: the r2/r3 "2/2" "assumed a wait of 0.2–0.25 s" and does not cover this case. Seat 3 rates each option at its worst path, so the cell is 3: veto. Ordering redone: D1, D2 and D3\*″ are vetoed. D3\*‴ is max 2, sum 1/2+1/1+1/1+1/1+1/2+2/2+2/1+2/2 = 3+2+2+2+3+4+3+4 = **23**. | Row 59 closed; winner D3\*‴ | — |
| P07C1-F-02 | D-C9 | map (losing row) | File 12 row "D3\*″ + bridge only above L_p 3.82 s", S3 **2/2** | **IMPRECISE (no longer covered by the seat's words)** | File 14 L7 and L15 give 2/2 only "while max(0, t_prov − t_ISM) stays at or below about 0.25 s", or with a ≈0.25 s cap followed by the bridge. A threshold at L_p 3.82 s allows provisional waits up to ≈ 0.33 s per emitter at 96 kHz (AX49 rationale, file 8), so the S3 cell for this row is 2 or 3, not 2. Either way the row is ≥ 25 or vetoed. | minor; winner unchanged | — |
| P07C1-F-03 | D-C9 | ordering (composition) | Seat 3's own capped variant (D3\*″ with a ≈0.25 s hold cap, then the bridge) | CORRECT: it does not beat D3\*‴ | The bridge can fire in this variant. The map takes each seat's worst path, so S1 (D5 ≤ 1/2), S8 (2/1) and S9 (D5 2/2, r2) keep their D3\*‴ cells. Only S3 rises, from 1/1 to 2/2: sum 23 − 2 + 4 = **25** > 23, same max of 2. | — | — |
| P07C1-F-04 | D-C9 | map / condition | D3\*‴ S3 1/1 rests on file 14's bridge items 1–4 | faithful (all four are in plan text) | (1) AX49: "The ISM is submitted at once over the current unit decays". (2) AX48: "hold the previous E_b … The interim amplitude uses the ebar of the unit decay actually played". (3) AX18: "the AX49 D5 bridge … keeps the existing equal-gain edit law". (4) phase-07c-1 record (h), L118–120, and AX49 name the ISM-latency print. | — | — |
| P07C1-F-05 | D-C9 | claim (Seat 3's premise) | "holds the ISM about 3 s" at T60_max ≳ 35 s | IMPRECISE (not load-bearing); arithmetic on a code measurement, NOT CHECKABLE against the corpus | AX38 4c finding: constructor 0.96 s + `make` × 2 emitters 2.18 s = 3.14 s at 100 m / 96 kHz. Under AX49's parallel emitters, with one shared constructor, the wall time is ≈ 0.96 + 1.09 = **2.05 s**. "L reaches 12 s at T60_max ≥ 34.6 s" checks: (12 − 1.218)/0.312 = 34.56. Either value is far above the 0.25 s that makes it 3, so the cell stands. | minor | Is the constructor-spectra stage shared between the two parallel emitter syntheses? |
| P07C1-F-06 | AX49, phase-07c-1 | DC-01 | Bridged ISM-latency print | **fixed** | phase-07c-1 L116–122: record (h) prints "the ISM latency on T60-changing edits under the AX49 D5 bridge … taken after condition 9 lands, unlike condition 12's record (g)". AX49 names record (h) in the same words. The condition 12 record (g) (L175) is unchanged and is the staleness record, so phase-10-2 L45 ("record (g) feeds the AX38 (v) split update") stays consistent. | closed | — |
| P07C1-F-07 | AX47 | DC-02 | ≤ +0.06 dB etc. | CORRECT (unchanged) | As DC-02 (Vorländer §6.4.1 Eq. 6.4). | — | — |
| P07C1-F-08 | AX47 | DC-03 | "≥ −0.5 dB unless δ ≥ 8.97" | **fixed, CORRECT** | (10^0.05 − 1)/0.0136 = 0.12202/0.0136 = 8.97. A smaller 1 − f_b only raises the threshold, so the bound is safe. The rationale column says 8.97 too. "δ ≥ 19" for −1 dB: 0.2589/0.0136 = 19.04, safe side. | closed | — |
| P07C1-F-09 | AX49 | DC-04 | L_p ≈ 3.7 s; ≤ 334 ms per emitter | CORRECT / NOT CHECKABLE (unchanged) | As DC-04. | — | — |
| P07C1-F-10 | AX49, ledger | DC-05 | Rated corner defined; ledger label | **fixed** | AX49 reversal: "(96 kHz, T60_max ≲ 8.3 s at the gated geometry, where L_p ≤ 3.82 s; interrogator file 13 row 62)". (3.82 − 1.218)/0.312 = 8.34 s checks. The ledger D-C9 row (L2344) carries "[the S5/S7 cells hold at T60_max ≲ 8.3 s: the rated corner]". | closed | — |
| P07C1-F-11 | phase-07c-2 | DC-06 | Criterion and step sizes set before the run | **fixed** | phase-07c-2 L58–60: "This phase's loop sets the AX47 ABX's detection criterion and step sizes before the run". The family-wise note is included. Admission waits for the ABX (L64). | closed | — |
| P07C1-F-12 | phase-07c-1 | DC-07 | Gate prints each gated scene's L_p | **fixed** | phase-07c-1 L121–122, inside condition 9's block: "The restore gate also prints each gated scene's L_p". The underlying question (does the flutter scene carry a tail with L_p ≤ 3.82 s?) is still open; it is a question, not a fix. | closed | carried: file 13 Q2 |
| P07C1-F-13 | phase-07c-1 | DC-08 | Lead sentence | **fixed** | L56–58 now reads as the DC-08 restatement word for word: the stage-1 exception is attached to the solve and the AX49 exception to the synthesis. | closed | — |
| P07C1-F-14 | phase-07d | DC-09 | K23 gloss | **fixed** | phase-07d L39–40: "…for lags up to L_f, within the normalisation step (K18′) [Inf]". | closed | — |
| P07C1-F-15 | phase-07d | DC-10 | D4 seat attribution | **fixed** | phase-07d L42: "Seat 4 rated it as A3, 1; Seat 5's cell at ≈ 147 MB is unrated". This matches file 13 row 63. | closed | — |
| P07C1-F-16 | ledger | DC-11 | D-C9 convening | **fixed** | L2344: "all nine (2 NOT MY MATTER)". | closed | — |
| P07C1-F-17 | ledger | DC-12 | PE-D1…D3 status | **fixed** | L2352 now states file 16's outcomes and the fix. | closed | — |
| P07C1-F-18 | AX49 | DC-13 | ≥ 18.7 dB decay; D1 "matched tail energy is zero" | CORRECT (unchanged) | Vorländer §6.4.1 Eq. 6.4; 60 × 0.312 = 18.72 dB. | — | — |
| P07C1-F-19 | AX47 | DC-14 | G and C80 move by ≤ 1 dB | CORRECT (unchanged) | Vorländer §6.4.2 Eq. 6.5, §6.4.3 Eq. 6.7, Table 6.1. | — | — |
| P07C1-F-20 | ledger | bookkeeping | L2351: "corrections 1–13 applied (10 and 11 as report notes)" | IMPRECISE (out of date) | Correction 11 is now in plan text (AX49 reversal) and in the D-C9 row, not only a report note (F-10). | minor | — |
| P07C1-F-21 | ledger | bookkeeping | The P07C1-DC-01…14 row (L2356) | IMPRECISE (formatting) | It comes after the "Decided for Maisara" paragraph (L2354–2355), so it is outside the table and does not render as a row. | minor | — |
| P07C1-F-22 | ee15c56 vs AX38 (i) | gate scope | "Held only around the solve; the solve pool passed only while held" | **conforms** | `ScenePipeline.cpp` L132–143: `StagedBuild::plan` runs outside the gate; `Scope` + `build.solve(&gate_->pool())` inside; `assemble()` and `makeIrSet` (L226) outside. `Engine.cpp` L669–701: `solve()` restores `options.diffusePool` on every exit. `assemble()`'s implicit `solve()` is a no-op once `solveDone` is set or `needsSolve()` is false, so no solve runs outside the gate. `IrBuilderThread.cpp` L127–128 calls `decide_()` unlocked. | — | — |
| P07C1-F-23 | ee15c56 vs AX38 (i) | locking | AX38 (i): the gate is held "never while holding `stateMutex_`" | **deviation in letter, test hook only; not in file 17** | `ScenePipeline.cpp` L139: `stageHook(BuildStage::Solve)` runs inside the gate `Scope` and takes `stateMutex_` (L150) to copy the hook. That briefly makes the lock order gate → `stateMutex_`. I found no path that goes `stateMutex_` → gate (the submit, `dropForOffline` and restore critical sections never enter the gate), so there is no deadlock. Even so, `DiffuseSolveGate.h` L11–12 ("never held while a pipeline holds stateMutex_") and `ScenePipeline.h` L168 are false as written. | minor (software) | Is the gate → `stateMutex_` order allowed by AX38 (i), or must the Solve hook avoid `stateMutex_`? |
| P07C1-F-24 | ee15c56 vs AX38 (i) | class order; stage-1 solve | "AX48 stage-1 solve served in class (1)" = session 2 | **conforms; not a conflict** | `DiffuseSolveGate.h` L46–51 has the three classes. Restore and prepare enter as `Synchronous`, the offline `process()` as `Offline` (L118–120, after `builder_->quiesce()` at L494), the builder as `Builder`. The stage-1 solve does not exist yet. When it lands it enters through the same Synchronous seam. | — | — |
| P07C1-F-25 | ee15c56 vs condition 10 / AX38 (i) | reset() | Never waits, never builds; keeps the IrSet | **conforms, with one residual not in file 17** | `ScenePipeline.cpp` L319–337, L339–367 and `RealtimeEngine::resetKeepIr` → `CrossfadingConvolver::reset` (L147–170, which promotes `next_`): no wait and no build. **Residual:** when the release queue is full, `reset()` runs `delete retiring_` (L156), with the comment "not the audio thread". But AX38 (i)'s corrected premise is that `reset()` may arrive on the VST3 processing thread, and it records Apple's `AudioUnitReset` as "does not allocate or free". The path is rare but not excluded. Stale comments: `ScenePipeline.h` L73 ("non-audio thread") and `DiffuseSolveGate.h` L5 ("reset() through its step 3") contradict condition 10. | minor (software) | Can the release queue be full when a processing-thread `reset()` arrives? |
| P07C1-F-26 | ee15c56 vs AQ10 (amended 2026-11-12) | synchronous restore | Restore and prepare still build synchronously = session 2 (O6) | **not a conflict** | phase-07c-1 condition 12 L155–156 orders the work: condition 12 first, then records (b) and (g), then condition 9's synthesis move. ee15c56 sits at the step the plan names. Condition 9 (AQ10's exceptions, AX49) must still land before the phase is `done`. | — | — |
| P07C1-F-27 | ee15c56 vs AX18 (FM-1) | crossfade law | Restore → EqualPower; otherwise EqualGain | **conforms** | `ScenePipeline.cpp` L238–249. A restore of an equal scene is skipped (L241). `tailSeed` sits in `base_`, which only `restore()` replaces, so a seed change is always EqualPower. An fs change goes through `prepare()`, which drops the IRs, so the first IrSet fades from silence. There is no interim IrSet yet, so the same-scene equal-gain clause has nothing to apply to. | — | — |
| P07C1-F-28 | ee15c56 vs AX47/AX48/AX49 | scope | Not implemented = session 2 | **not a conflict** | No interim level, saved E_b, provisional tail or law change exists in the code, so no decision is pre-empted. | — | — |
| P07C1-F-29 | ee15c56 vs AX38 (i) half (2), phase-07c-1 condition 11 | host trace | Plan says "a preallocated **SPSC** ring"; the code is a multi-producer, single-consumer ring | **INCONSISTENT with the plan letter (software); the queue itself is correct** | `HostTrace.cpp` L62–100 is a correct bounded Vyukov queue: one CAS per push, drop-and-count when full, no allocation or lock on push. The deviation is justified (entry points arrive on several threads). But AX38 (i) and condition 11 still say SPSC, and file 17 records the change only as "deviation in form" for the PR. Under CLAUDE.md, plan text changes go through `/fix-plan`. | minor | — |
| P07C1-F-30 | ee15c56 vs AX5 | offline bit-identity | "`render_cli` bit-identical to b4dd092" | NOT CHECKABLE here | No shell and no CI run cited in file 17. A CI run or a local diff of `render_cli` output would settle it. | — | Which run shows the bit-identity? |

## Outcomes

- **D-C9 → AX49 (D3\*‴): SURVIVES WITH CORRECTIONS.** Row 59 is closed by Seat 3's own 3/3 (F-01). The bridge condition behind its 1/1 is fully in plan text (F-04). The ordering holds, composition included (F-03). Corrections: relabel the S3 cell of the "bridge only above 3.82 s" row as 2 or 3 (F-02). Optionally state the hold as about 2–3 s under parallel emitters (F-05). The decision follows unchanged. There is no NEEDS MAISARA.
- **Diff fixes:** DC-01, DC-03 and DC-05 to DC-12 are fixed in place. The ledger has two minor slips (F-20, F-21).
- **Code ee15c56:** conforms to the final AX38 (i), AQ10 and AX18 texts. None of the "session 2" items is a conflict. Three minor items are missing from file 17: F-23 (the Solve hook takes `stateMutex_` while the gate is held), F-25 (`delete retiring_` on a reset that may run on the processing thread, plus stale comments) and F-29 (SPSC in the plan text versus an MPSC ring in the code). F-30 is not checkable without a run.

## Questions (most consequential first)

1. **F-23.** Does AX38 (i) allow the gate → `stateMutex_` lock order that `stageHook(Solve)` creates, or must nothing under the gate take `stateMutex_`?
2. **F-25.** Can `CrossfadingConvolver::reset()` reach `delete retiring_` when the host delivers `reset()` on the processing thread?
3. **F-29.** Will AX38 (i) half (2) and condition 11 be amended through `/fix-plan` to describe the multi-producer ring?
4. **F-05.** Under AX49's parallel emitters, is the constructor-spectra stage shared, so that the full-synthesis hold is about 2.05 s rather than 3.14 s?
5. **F-30.** Which CI run shows `render_cli` output bit-identical to b4dd092 at ee15c56?

Files read:
- /home/user/makroof/docs/review/phase-07c-1/12-decider-decision-r3.md
- /home/user/makroof/docs/review/phase-07c-1/13-interrogator-on-file12.md
- /home/user/makroof/docs/review/phase-07c-1/14-seat3-final-T60-edit.md
- /home/user/makroof/docs/review/phase-07c-1/16-interrogator-diff-check.md
- /home/user/makroof/docs/review/phase-07c-1/17-orchestrator-code-conformance.md
- /home/user/makroof/docs/BUILD_PLAN.md (L36, L116, L139, L159, L168–170)
- /home/user/makroof/docs/phases/phase-07c-1.md (L50–181)
- /home/user/makroof/docs/phases/phase-07c-2.md (L50–69)
- /home/user/makroof/docs/phases/phase-07d.md (L39–42)
- /home/user/makroof/docs/phases/phase-10-2.md (L40–48)
- /home/user/makroof/docs/review/ledger.md (L2329–2356)
- /home/user/makroof/src/plugin/core/ScenePipeline.h
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp
- /home/user/makroof/src/plugin/core/DiffuseSolveGate.h
- /home/user/makroof/src/plugin/core/DiffuseSolveGate.cpp (L68–75)
- /home/user/makroof/src/plugin/core/HostTrace.h
- /home/user/makroof/src/plugin/core/HostTrace.cpp (L62–187)
- /home/user/makroof/src/plugin/core/IrBuilderThread.cpp
- /home/user/makroof/src/sim/Engine.h (L100–259)
- /home/user/makroof/src/sim/Engine.cpp (L225–424, L600–712)
- /home/user/makroof/src/sim/RealtimeEngine.cpp
- /home/user/makroof/src/sim/conv/CrossfadingConvolver.cpp (L120–179)
- /home/user/makroof/docs/corpus/SOURCE_COMMIT