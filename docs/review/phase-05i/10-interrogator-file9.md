# 10 — Interrogator, round 2: decision mode on decider file 9 (rebuttal to file 6)

Phase 05i, 2026-11-11. Target: `docs/review/phase-05i/9-decider-r2.md`, read with file 7 (code facts), file 8 (Seat 5 on Q5) and the working-tree `tests/unit/test_diffuse_records.cpp`. Saved verbatim by the orchestrator from the interrogator's report (the interrogator reads only).

**Corpus:** `docs/corpus/` present, revision **c1b171fe649f07cbeb952ef1f75d89bfaa414d0d** (`SOURCE_COMMIT`), 13 books.

**Sources read:** files 3 (Linux, plus the macOS and Windows (iv) lines), 4 (L60–84), 6, 7, 8 and 9. Phase-05h file 56 L25–50. BUILD_PLAN AQ4, AQ10 and AX38. PRD L36–165. Phase-05i §3.3. Phase-07c §§0–5 and phase-07c-1 conditions 9–10. `docs/board/README.md` (convening table; "Who answers Maisara's questions"). `.claude/agents/decider.md` §5. Seat 2 §18. From the code: `src/plugin/core/ScenePipeline.cpp` L100–243, `DiffuseSolveGate.h`, `src/sim/Engine.cpp` (generator L240, solve L331), `tests/unit/test_diffuse_gate.cpp` L663–740, and `tests/unit/test_diffuse_records.cpp` L50–139 and L370–577. Corpus: Vorländer §15.3 (Table 15.1), §9.2.1 and Table 6.1, plus greps for "Card", "Table 15.1" and "crossfade" across all files.

**Limitation:** read-only tools, no shell, so `git diff` was not run; the test file's working tree was checked against file 9's specification line by line (P05I-64). (Orchestrator: the working-tree change was committed as 52fc283; `git show 52fc283 --stat` shows only `tests/unit/test_diffuse_records.cpp`.)

## Outcomes

| item | outcome | why, in one line |
|---|---|---|
| Corrections from file 6 (disposition table) | **faithful** | Every correction marked applied is in file 9's text; the "superseded" and "answered" rows hold (P05I-42…46) |
| Q1, register exits | **SURVIVES** | §3.3 (ii) "on 05i's runs" basis; run of record named; K2 checked against all 25 values in file 56 and file 3 |
| Q2, K-e12 / Raise item 1 | **SURVIVES** | P05I-14 and P05I-15 applied as written |
| Q3, Raise item 2 (revised) | **FALLS**, also **PRD MISREAD** | Its mechanism claim is WRONG against the code: the gate is held for the whole `buildRoomIR`, not only around the ≈ 81–91 ms solve. The F-c settlement route names a timer that measures neither contention nor the gate. Reasoning step (2) says the PRD ranks a tension that NFR-3 hands to the Expert |
| Finding F-c (named in Q3) | **FALLS** | From the code it is the class-(1) wait for a holder that holds the gate for a full build; the decider's own condition for calling it a class (1) defect is already met by the code |
| Q4 | **SURVIVES** | unchanged |
| D-Q5, solve-median bound | **SURVIVES** | Convening, map, ordering, numbers, debt and PRD check all faithful; one imprecise claim is Seat 5's own and moves no cell (P05I-61) |
| Test-code change (Q1 and D-Q5) | **SURVIVES** | Matches file 9's specification item by item; the only new REQUIRE is structural (P05I-64) |

## Round-1 findings re-checked

- **With the corpus.** Round-1 P05I-00 marked Table 15.1 and Card et al. NOT CHECKABLE. Table 15.1 is CORRECT as AX38 quotes it (P05I-39). Card et al. stays NOT CHECKABLE (P05I-40). No round-1 finding rested on either source, so none changes because the corpus is now present.
- **With the code.** Two round-1 findings change. P05I-21 and P05I-24 took AX38 (i)'s plan text, "held only around the solve", as the behaviour; the code holds the gate across the whole room-IR build (P05I-47). So file 5's "matches the gate's turn-taking" agreed with the code; my round-1 arithmetic (+0.16–0.18 s) described the plan, not the build. The real inconsistency is between the code and AX38 (i), which is her recorded decision (accepted 2026-11-10). P05I-50 records the revision.

## Decision ledger

| id | decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|---|
| P05I-39 | all | claim (corpus) | AX38's reading of Table 15.1: the 3 s row covers translational movement > 1 m, derived from 30–50 cm/s VR movement; no row for geometry or material edits; 35 ms head-rotation row | CORRECT | Vorländer §15.3, Table 15.1 (after Lentz et al. 2007) has four rows: source and head rotation 35 ms, translational > 0.25 m 700 ms, > 1 m 3 s. The text's 20 ms is marked "as printed; Table 15.1 gives 35 ms". Translational speed 30–50 cm/s (LaViola 2003) | none (replaces P05I-00) | — |
| P05I-40 | all | claim (corpus) | Card et al. 1991, the UI response-time anchors | NOT CHECKABLE | Not in any corpus file (grep "Card"); the cited 1991 HCI paper itself would settle it; used only as AX38's labels, not load-bearing | none | — |
| P05I-41 | all | claim (corpus) | AX38's "1 jnd of G" = 1 dB | CORRECT | Vorländer Table 6.1: G, 500–1000 Hz, jnd 1 dB; the 1 kHz replicate band lies inside that range | none | — |
| P05I-42 | Q1 | disposition P05I-03, -07, -08, -09 | basis §3.3 (ii); run of record; OVER30S on any 05i run keeps the entry listed; closing phase moves by (c)'s own exit | faithful | File 9 answer 4; Q1 bullets 2–5; reasoning (1)–(3); phase-05i L83–87 | none | — |
| P05I-43 | Q1 | disposition P05I-06; claim K2 | K2 and the Windows / Linux plan ranges | CORRECT | All 25 values and the run order match file 56 L28–49 and file 3. Linux outside red run 42949252041: 24.31–30.18 s. Windows outside 42942694523 and 42975074716: 19.99–29.51 s. Windows 19.99 s at flutter 488 ms on 42954077281 (L43) | none | — |
| P05I-44 | Q1 | inference | `listed` is set false in code that the run of record itself executes, before the plan-text closure | faithful | Answer 4 covers it; the flag is print-only: L481–490 are its only readers; the REQUIREs key on `strict30s` (L469–474) and `absoluteAsserted && inWindow` (L574–575) | none | — |
| P05I-45 | Q2 | disposition P05I-14, -15 | worst/median wording; ≈ 4.8 s as arithmetic | CORRECT | File 3 L81 (3 276 / 2 370), macOS 2 648 / 1 967, Windows 3 231 / 2 377; AX38 4c K-e12 finding | none | — |
| P05I-46 | Q3 | disposition P05I-18, -19, -23; numbers | load, staleness, offline, F-c ranges | CORRECT | Room-size max 16 304 / 14 588 / 16 421 ms; joint 15 705 / 14 376 / 15 128; during offline render 29 412 / 27 899 / 31 849 (ratios 1.87 / 1.94 / 2.11); F-c 3 607–5 043 ms, ratio to one instance 1.46 (3 616/2 485) to 2.62 (5 043/1 924) | none | — |
| P05I-47 | Q3 / F-c | claim (code), load-bearing | "The gate is held only around the diffuse solve (≈ 81–91 ms). The ISM, the unit-decay synthesis … run outside the gate" (answer 5; file 7; F-c plan text) | **WRONG** (from the code) | `ScenePipeline.cpp` L124 builds a `DiffuseSolveGate::Scope`; its destructor calls `leave()` (`DiffuseSolveGate.h` L92–96), which runs only after L132 `return sim::buildRoomIR(...)` returns. So the gate covers ISM, synthesis (`Engine.cpp` L240) and the solve (L331); only `makeIrSet` (L197) runs outside | **FALLS** | Q1 |
| P05I-48 | Q3 / F-c | inference / hidden premise | "Not shown to break (i) class (1)"; hypothesis "CPU sharing outside the gate" | **WRONG premise; the inference fails** | The holder keeps the gate for a whole build (≈ 1.9 s); a class-(1) waiter waits up to that, then builds itself: ≈ 2×, which matches 1.46–2.62×. The wait is flat from 4 to 8 instances (Linux 3 778 → 3 803 ms, Windows 3 816 → 3 870), as the class priority predicts; CPU sharing would predict growth with N. The decider's condition "waiting at the gate beyond the one solve already running" is met from the code | **FALLS** | Q1 |
| P05I-49 | Q3 | claim | Record (c): +1.76 s is "about one extra rebuild; mechanism not established (hypothesis: CPU sharing outside the gate)" | IMPRECISE (the hypothesis is contradicted) | With full-build holds, builder and offline turns take one build each, so AX38 (i)'s "about two solves" behaves as about two builds; 3 572 − 1 812 ms ≈ one 100 m / 96 kHz build | correction | Q1 |
| P05I-50 | round 1 | revision | P05I-21 (INCONSISTENT) and P05I-24 | revised | Round-1 basis was AX38 (i)'s plan text, which the code does not implement (P05I-47); the inconsistency lies between the code and AX38 (i), not in file 5's turn-taking reading | none | — |
| P05I-51 | Q3 / F-c | debt row; claim | "Settled by the split timer in phase-07c condition 9's packet"; evidence row "condition 9's split timer (F-c's cause)" | **INCONSISTENT** | Phase-07c-1 L95–97: the packet repeats `[probe-restore-split]` on one local box; that probe (`test_diffuse_gate.cpp` L667–732) runs single-threaded and uncontended, with `tailLevelAx16` (no diffuse solve) and no gate; it cannot time a gate wait or contention | **FALLS** (debt row) | Q2 |
| P05I-52 | Q3 | **PRD proxy** | Reasoning (2): "The PRD ranks the tension: L101 puts accuracy first and accepts high latency"; option A shown as serving "NFR-2 / L101" | **PRD MISREAD** (a cited id does not say what is claimed) | NFR-3 (L107): "This tension goes to the Expert", so the PRD does not rank it. L101's "latency" is NFR-2's latency, reported to the DAW for compensation (L106), not IR-update staleness. L101's own proviso, "must stay usable in a DAW session", bears on 15–30 s following and is not shown against A. The result may still follow from D-H1 (v)(d), the one-phase rule and Q4/AQ4 routing (README: Q1–Q10 stay with the Expert) | re-answer | Q3 |
| P05I-53 | Q3 | claim (corpus) | Strain "at its heaviest multi-instance records" | IMPRECISE (conditions) | AQ4's rationale cites Table 15.1's 700 ms for moves > 0.25 m (Vorländer §15.3). The joint record's listener +0.5 m waits 725 ms (48 kHz) and 1 812 ms (96 kHz) with one instance at 100 m (Linux, file 3 L42, L57); at the AQ10 room 1 319 ms with 4 instances at 96 kHz (L32), 1 221 ms with 8 at 48 kHz (L22). The table is a VR proposal, so it applies here by extension | correction | Q4 |
| P05I-54 | Q3 | claim | "FR-SIM-6 'without audible artifacts' is served by AQ4's crossfade … nothing is reported to click" | NOT CHECKABLE (audibility); IMPRECISE (wording) | Vorländer §9.2.1 describes crossfaded frames with constant power in the overlap but states nothing about audibility; no click detector ran on the (iv) records, so "not measured" fits better than "not reported" | correction | Q5 |
| P05I-55 | Q3 | claim | Clarification: "R2's position path 31–90 ms holds for an isolated update at the AQ10 room" | IMPRECISE | AQ10: Phases 04–09 time the build "without generating the unit decay, as its proxy"; today every parameter change triggers a full uncached rebuild (file 7; `cachedUnitDecays` set only by tests); 31–90 ms is therefore the Phase-10 proxy; measured full rebuilds at the AQ10 room are 156–166 ms (48 kHz) and 340–356 ms (96 kHz), Linux, 1 instance | correction | Q4 |
| P05I-56 | D-Q5 | convening | 9 rows; Seat 5 convened | faithful | README Seat 5 row: "CI gates"; Seats 2 and 3: no compute budget or work is chosen (Seat 2 §18 excludes "threading and hosts (Seat 5)"; their hand-off goes to the 07c-2 debt row); Seats 1, 4 and 6–9: nothing in their rows | none | — |
| P05I-57 | D-Q5 | map | A 0/1, B 0/1, C 1/1, D 1/1, E 2/2; the others 0/0 | faithful | File 8 §3–§4, ratings and reasons word for word | none | — |
| P05I-58 | D-Q5 | ordering | bounds → worst-off → sum → reversibility → seat ranking | correct | E breaks AX38 4c RG-1 "never a red or out-of-window run" (phase-05i §3.3 (v)); no 3s; maximum 1 for A–D; sums A 1, B 1, C 2, D 2; reversibility ties; A chosen on Seat 5's own "Prefer", without re-rating | none | — |
| P05I-59 | D-Q5 | D5-L2, L3, L4 | baselines, thresholds, 0 of 18 | CORRECT | File 4 L71–77: in-window runs Linux and macOS 43007183782 only; Windows 42964823518 (+0.9 %) and 43007183782 (+1.3 %). (90.2+90.6)/2 = 90.4, (143.8+145.0)/2 = 144.4; × 1.20 = 97.08 / 157.44 / 100.44 / 123.24 / 108.48 / 173.28; largest ratio 149.6 / 144.4 = 1.036 | none | — |
| P05I-60 | D-Q5 | D5-L5; Seat 5's B, C, E rates | t(2) and z rates | CORRECT (arithmetic; normality is [Hyp]) | macOS flutter: t = 26.47 / 14.33 = 1.85, P = ½(1 − t/√(t²+2)) = 0.103; z = 2.13, P = 0.017. B: t = 2.56, P = 0.062. C: t = 1.49, P = 0.138. E: t = 1.35, P = 0.155 | none | — |
| P05I-61 | D-Q5 | claim (Seat 5 §3, not repeated by the decider) | "The other five cells … 1.20 sits 10 or more SD above the mean; their rate is about 0" | IMPRECISE | Windows flutter: SD 3.06, (173.28 − 146.13) / 3.06 = 8.9 SD; predictive t(2) = 7.68 gives P ≈ 0.008, about 1 in 120 runs (Windows low-α 10.9 SD); no cell moves | none | — |
| P05I-62 | D-Q5 | debt | Seat 5's later-1 row; the 2/3 hand-off row | faithful | Both rows give the commitment, the undo cost, the evidence and when it is repaid; the 07c re-pin exists (AX38 4c RG-1; phase-05i §3.3 (v)), and so does phase-07c-2 | none | — |
| P05I-63 | D-Q5 | PRD proxy | acceptance check | no PRD MISREAD | A–D are shown against NFR-1 and NFR-2; no PRD goal points to B, C or D; it fills AX38 4c's own slot, so no AMENDS line is needed | none | — |
| P05I-64 | Q1, D-Q5 | test code against file 9's spec | `GateEntry`, constants, rows, prints | matches | `solveRefMs` and `solveRefRuns` at L86–89; `kSolveWarn` 1.20 at L98, separate from `kRatioWarn` (L94); rows L109–117 match the spec, including `listed` (false for Linux and Windows, true for macOS); comments L82 and L112–114 match verbatim; the 30 s suffix strings at L484–489 match verbatim; `solveWarnAt` and `solveBasis` on both GATE lines (L557, L568); flutter `warnings=` (L539, L558); low-α SOLVE (L564–565); the only new REQUIRE is `flEntry != nullptr` (L533); the closed-entry label at L481 was there before this change (file 5 K4); git diff not run | none | — |
| P05I-65 | Q4 | — | unchanged | SURVIVES | As P05I-27 | none | — |

## Strongest objection

- **The decider's own objection (Q3):** 15–30 s following is recorded but not relieved. That stands as written.
- **Stronger, from the code:** the strain the answer attributes to "CPU sharing outside the gate" comes, on the code's evidence, from the gate being held across the whole build. That departs from AX38 (i), "held only around the solve", which she accepted on 2026-11-10. Q3's option set treats the strain as owned by 07c and Phase 10 ("nothing here relieves it now") and never considers that the code does not meet a recorded decision of hers: a recorded decision that bears on the point and points the other way has been left out.
- **Corpus addition:** following already exceeds the 700 ms row that AQ4's own rationale relies on (Vorländer Table 15.1) with a single instance at 100 m (P05I-53).

## Questions for the decider's rebuttal (most consequential first)

1. **Gate scope.** `ScenePipeline.cpp` L124 enters the gate and it is left only when `solveAndBuild` returns after `buildRoomIR` (L132). Is the gate therefore held for the whole room-IR build (≈ 1.8–2 s at 100 m / 96 kHz)? If it is: F-c and record (c)'s +1.76 s follow from class (1) and turn-taking over full builds (the 4-to-8-instance flatness fits). Then: is the departure from AX38 (i)'s "held only around the solve" (her decision of 2026-11-10) a defect to be routed under its own rule? What happens to Q3's options and to the F-c plan text?
2. **Instrument.** Which test times the gate wait inside a contended host call? Phase-07c-1 condition 9's packet repeats `[probe-restore-split]`, which is single-threaded, uncontended and has neither gate nor solve.
3. **PRD reading (Q3, reasoning 2).** Which PRD id ranks NFR-3's tension, when NFR-3 sends it to the Expert? Does L101's "latency" include IR-update staleness, given that NFR-2 defines latency as reported for compensation? Show option A against L101's "must stay usable in a DAW session".
4. **Scope of the strain.** AQ4 cites Vorländer Table 15.1 (700 ms for moves > 0.25 m) as its yardstick. By that yardstick, is following already strained with one instance at 100 m (725 ms at 48 kHz, 1 812 ms at 96 kHz) and at the AQ10 room from 4 instances at 96 kHz (1 319 ms)? If so, should "at its heaviest multi-instance records" and the R2 clarification (the proxy, not today's full rebuild) be restated?
5. **Artifacts.** Was any click or artifact measurement taken on the (iv) automation records? If not, does "nothing is reported to click" become "not measured", with the claim about FR-SIM-6's "without audible artifacts" stated as AQ4's design intent only?

## Corrections to apply if the decider accepts them (no new decision)

- **Q3 / F-c:** strike "the gate is held only around the ≈ 81–91 ms solve" and "hypothesis: CPU sharing outside the gate" from the answer and from both plan-text blocks; they must not enter AX38 (iv) or 4c in that form.
- **Q3:** replace "nothing is reported to click" with "not measured".
- **Q3:** restate the strain's onset against Table 15.1's 700 ms row, as an application by extension.
- **Q3:** describe R2's 31–90 ms as the Phase-10 proxy (AQ10).

The code that bears on question 1 (ScenePipeline.cpp L124–132):
```cpp
    DiffuseSolveGate::Scope gate(*gate_, cls, abandon);
    ...
    return sim::buildRoomIR(scene, options);
```
