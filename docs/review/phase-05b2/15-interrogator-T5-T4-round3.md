# Interrogator — decision mode, round 3 (final), D-T4a and D-T4c

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-09).

## Interrogator, round 3 of 3 (decision mode): D-T4a final (4a-2G3C) and the D-T4c additions

**Verdict: D-T4a SURVIVES WITH CORRECTIONS; D-T4c SURVIVES.** The other five decisions stand as I ruled in round 2. Nothing is contested any more. What is still open for Maisara is Challenge 1 (the AQ10 amendment for the 100 m restore gate) and her accept or veto of the seven decisions. The two D-T4a corrections below are wording only: they change no cell and no step of the ordering, so the plan-editor can apply them without another decider round. That matters because this was the last interrogation round allowed.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read this round:**
- `13-decider-round4-T4a-final.md`;
- the seat re-runs `6-seat5-rerun2-T4a.md`, `6-seat5-rerun3-T4a.md`, `6-seat3-rerun3-T4a.md`, `6-seat6-rerun4-T4a.md`, `6-seat4-rerun2-T4a.md`;
- in `ScenePipeline.cpp`: `decide` (L131–207), `resetSequence` (L209–229), `process` (L393–412);
- in `PluginProcessor.cpp`: L141–154.

### Round-2 rows: are they closed faithfully?

| row | what it asked for | status | evidence |
|---|---|---|---|
| 40 | Seat 5's cell on 4a-2G++, and Seat 3's hand-off | closed | Seat 5 rated 4a-2G++ 1/2 as written and 1/1 under the three-class rule plus its condition (b) (re-runs 2 and 3). It answered Seat 3's hand-off: an offline wait at the gate is allowed under its conditions 1–6, and all six are in (i): no gate on a real-time thread (debug assert plus a test), a bounded wait, offline never coalesces, no deadlock, a sleeping wait, and the 1 GB bound holds during a bounce. |
| 41 | conditions of Seats 1, 7 and 9 | closed | Seat 1 (1) and (2) → (iv). Seat 7 (1) → (iii). Seat 7 (2) → (iv). Seat 7 (3) → the Bitwig gap in (i). Seat 9 (a) and (b) → (vi). |
| 42 | "(position and room size)" | closed | Back in (iv). |
| 43 | S7 and S9 register rows in their own words | closed | The quotes match the re-runs. |
| 44 | the Phase 08 commitments in the /fix-plan list | closed | phase-08 now lists (iv) binaural and (v) item 8. |
| 49 | whether the closed cube actually falls back | closed | The record states `ismFallback` per emitter for both 100 m builds. If the cube falls back, the non-fallback horizon is reported as not covered. |

### Final D-T4a map against the seats' words

| seat | cell | where it comes from | faithful? |
|---|---|---|---|
| S1 | 0/1 | Rated on 4a-2G++. | Yes. Accepted carry to 4a-2G3C: Seat 1 kept its later at 1 because the (iv) records make the lag measurable, and that holds under any service order. |
| S2 | 1/1 | Carried from 4a-2G. | Yes. Ordering terms do not touch Seat 2's measures. |
| S3 | 1/1 | Read from conditions. | Yes. Re-run 3: three classes plus the offline-staleness record give "1/1"; both are in (i) and (iv). |
| S4 | 1/1 | Read from conditions in round 4. | Yes, and now rated: Seat 4's re-run 2 gives 4a-2G3C 1/1 with no new condition. |
| S5 | 1/1 | Rated (re-run 3). | Yes. All of its "earlier conditions stay part of the rule" are in (i) and (iv), including the M-parallel bound of about 2M solves. |
| S6 | 1/1 | Read from conditions. | Yes. Re-run 4 asked for offline and builder waiters to alternate, the gate wait to count as staleness and drive "settling", and a record of one instance freezing while others are automated; all are in (i), (iii) and (iv). |
| S7 | 1/1 | Rated on 4a-2G++. | Yes. Accepted carry: serving host calls first only shortens project load. |
| S8 | 1/1 | Carried from 4a-2G. | Yes, accepted. Note: alternation can roughly double a freeze while other tracks play live. A full-project bounce is not affected, because `setNonRealtime` keeps every builder quiesced (`resetSequence(false)`). This is recorded under (iv) "the offline wait". |
| S9 | 1/1 | Rated on 4a-2G++. | Yes. Ordering does not touch room range. |

- **Ordering.** The other options are unchanged; 4a-3 is vetoed, and 4a-1 and 4a-2 sit at max 2. 4a-2G3C: max 1, sum 8 + 9 = 17. The two intermediate rows match the seats: S5 1/2 on 4a-2G++ as written, and S3 and S6 1/2 on the two-class rule.
- **One composed variant per id.** The rule is met: 4a-2G3C is round 4's only variant, and the two-class version was Seat 5's own proposal.

### Is the 4a-2G3C text complete enough for the plan-editor? Two corrections

1. **The synchronous class omits `reset()`.** The text lists "prepare, restore, `setNonRealtime`". But `SpatialSceneProcessor::reset()` calls `pipeline_.reset()`, which calls `resetSequence`, which calls `decide(Source::ResetStep3)`. That call runs `buildIr` whenever the current scene differs from `builtScene_` (L146, L159–164). So a host's `reset()` can trigger a diffuse solve, and therefore a gate wait. `setNonRealtime` reaches the gate through the same path.
   - Add `reset()` (ResetStep3) to the synchronous class.
   - Cover it with the debug assert and the two-pipeline test.
   - Include it in the "worst host-thread wait" record.
   - Add `reset()` to Seat 5's open researcher question (which host threads call it). If any host calls `reset()` on its audio thread, the gate becomes reachable from a real-time thread outside `process()`.

   This is a pre-existing synchronous build (Phase 07 D7). The gate adds at most one running solve to it, so no option and no cell changes.
2. **Seat 4's cell now has its own rating.** Mark S4 "rated (re-run 2, 1/1)". The strongest objection ("S4 read from conditions, three-class order not put to Seat 4") is answered, and only S3 and S6 are now read from conditions. Confidence stays low because of K8–K10.

**Research gap, not load-bearing.** Seat 5 raised an open check [Hyp]: does any host run a freeze or offline render on a thread that also serves the real-time graph? It is listed with "no scheduled source". It does not decide between the options, because the offline path already blocks `process()` for a full synchronous rebuild today (AQ4, L400–402); the gate only multiplies that block by about 2, or about 2M. The orchestrator should still put it to the researcher, together with the `reset()` thread question, before the gate's offline path is implemented.

### D-T4c

The additions for correction 49 and the "UI response-time anchors, not audibility limits" label are faithful (Seat 1 condition (1)). Map: max 2 (S5 later), sum 17. Challenge 1 is pending with Maisara.

### Conditions the plan-editor must write into the D-T4a AX text, in addition to my round-2 list

- **Seat 5:**
  - the three-class order (host calls first; offline and builder waiters alternate one solve each; FIFO within a class);
  - (b) builder waits are cancelled on `quiesce()`;
  - the offline path takes the gate only after `quiesce()` returns;
  - a sleeping mutex-plus-condition-variable wait, no spin lock, no raised builder priority;
  - the debug assert plus the real-time-beside-gate test with zero allocations;
  - offline waiters never coalesce;
  - the two-order output test, including one pipeline offline;
  - TSan with two pipelines, one switching to offline mid-solve;
  - records: worst `quiesce()` latency, worst host-thread wait with 1, 4 and 8 pipelines, callback p99.9 during an offline render, and the M-parallel offline wait of about 2M solves;
  - `reset()` in the synchronous class (correction 1 above).
- **Seat 3:** the three-class rule; the record of real-time staleness during an offline render under room-size automation.
- **Seat 6:** alternation; the freeze-while-automating record with 4 and 8 instances.
- **Seat 4:** no new condition; (iv) binaural and (v) item 8 stay.
- **Seats 1, 7 and 9:** as written in round 4.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T5T4-51 | Row 40 (S5 cell on 4a-2G++ and Seat 3's offline hand-off) answered by Seat 5 re-runs 2 and 3 | faithful | closed |
| P05B2-T5T4-52 | Row 41 (Seats 1, 7, 9 conditions) written into (i), (iii), (iv), (vi) | faithful | closed |
| P05B2-T5T4-53 | Row 42 "(position and room size)" restored | faithful | closed |
| P05B2-T5T4-54 | Row 43 S7 and S9 register rows in the seats' words | faithful | closed |
| P05B2-T5T4-55 | Row 44 Phase 08 (iv) and (v) on the /fix-plan list | faithful | closed |
| P05B2-T5T4-56 | Row 49 `ismFallback` recorded for both 100 m builds; uncovered horizon reported | faithful | closed |
| P05B2-T5T4-57 | D-T4a final map: S3 and S6 read from conditions, S4 and S5 rated; S1, S7, S9 rated on 4a-2G++; S2 and S8 carries accepted; max 1, sum 17 | faithful | closed |
| P05B2-T5T4-58 | Two-class and 4a-2G++ intermediate rows (S5 1/2; S3 and S6 1/2) | faithful | closed |
| P05B2-T5T4-59 | D-T4a synchronous class omits `reset()` (ResetStep3 can build: `ScenePipeline.cpp` L146, L159–164, L209–229) | correction (wording; no cell change) | open (plan-editor) |
| P05B2-T5T4-60 | D-T4a S4 cell now rated by Seat 4 re-run 2 (1/1); update the mark and the strongest objection | correction (wording) | open (plan-editor) |
| P05B2-T5T4-61 | Host threading of freeze/offline and of `reset()` [Hyp] (Seat 5 open check) | NOT CHECKABLE; not load-bearing; route to the researcher before implementing the gate's offline path | open |
| P05B2-T5T4-62 | S8 carry: alternation can roughly double a live-session freeze; full-project bounce unaffected (builders quiesced); recorded in (iv) | observation | closed |
| P05B2-T5T4-63 | D-T4c additions (correction 49, UI-anchor label) | faithful | closed |
| P05B2-T5T4-64 | D-T4a final verdict | SURVIVES WITH CORRECTIONS (59, 60) | open until applied |
| P05B2-T5T4-65 | D-T4c final verdict | SURVIVES | closed |

Files:
- /home/user/makroof/docs/review/phase-05b2/13-decider-round4-T4a-final.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun2-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat5-rerun3-T4a.md
- /home/user/makroof/docs/review/phase-05b2/6-seat4-rerun2-T4a.md
- /home/user/makroof/src/plugin/core/ScenePipeline.cpp
- /home/user/makroof/src/plugin/PluginProcessor.cpp
