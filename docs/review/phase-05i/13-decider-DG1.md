# 13 — Decider, round 4: D-G1 decided (the gate-scope departure G-1), with FOR MAISARA G1-C1

Phase 05i, 2026-11-11. Saved verbatim by the orchestrator from the decider's report (the decider only reads).

**Corpus:** `docs/corpus/` present, revision **c1b171fe649f07cbeb952ef1f75d89bfaa414d0d**; Vorländer §15.3 and Table 15.1 re-read (`vorlaender-auralization.md` L3952–3968).

**Read for this round:** review files 11 (D-G1 CONVENE), 12-seat1, 12-seat2, 12-seat3, 12-seat5 (lead), 12-seat6, 12-seat7, 12-seat8, 12-researcher-RQ-G1, file 3 L1–12. Code: `ScenePipeline.cpp` L95–204; `DiffuseSolveGate.h` in full; `test_diffuse_records.cpp` L700–778 (the p99.9 record) and L1005–1165 (record (d), the host-thread waits). Plan: BUILD_PLAN §0 rows 05i (L28) and 07c-1 (L34); AX38 in full (L158) and the "settling" lines (L319, L359). Phases: phase-05i in full; phase-07c-1 in full; the phase-07c umbrella headings; phase-10-2 scope 3; phase-11-3 scope 3. PRD: L76, L90, L101–109, L159, L168.

## PRD digest

- **For whom:** producers and sound designers in a DAW; multi-stem scenes from several plugin instances (FR-3D-6, FR-SIM-7).
- **Outcome:** an accurate render (NFR-1) that follows automated movement (FR-SIM-6, NFR-3) and stays usable in a DAW session (L101).
- **Hard constraints:** CLAUDE.md rule 5 with phase-05i §0 and §8 (no engine or `src/` change in 05i); AX5 (no output change) and NFR-8; D-H1 (v)(d) (no W_max cut, no range change, no formulation seam, no instance cap); her AX38 (i) (the gate "held only around the solve"; class (1) waits "at most for the one solve already running"; the release rule); AX38 (iii) and (iv) with R3; AQ4 and AQ10 as plan defaults.
- **PRD reading:** NFR-3 sends its tension to the Expert (L107), Q4/AQ4 binds; no PRD line ranks it; L101's proviso ("must stay usable in a DAW session") is the line every option is shown against.
- **Verification culture:** every behaviour has an automated check or a printed record; a claim not measured is stated as not measured; a timing record is never a CHECK on shared runners.

---

## D-G1 — decision round

**Matter (from file 11):** G-1 has to be either fixed in code or amended into her decision: who owns the change, when it lands, and whether 05i records a baseline from before the fix. **Options:** A (register entry plus a new phase-07c-1 condition); A′ (A, plus a test-side gate-wait poller in 05i); B (amend AX38 (i) to match the code); C (fix it in 05i; out by bounds); D (a new phase 05j); E (a follow-up line only).

### Knowledge inventory

| K | what | source | status |
|---|---|---|---|
| K-g1 | The gate encloses `buildRoomIR` (ISM, synthesis and solve; `makeIrSet` outside) and is process-wide | from the code: `ScenePipeline.cpp` L124–132, L196–197; `DiffuseSolveGate.h` L59–61, L85–96 | known |
| K-g2 | One build vs one solve at 100 m (Linux): build medians 1 870 ms low-α, 664 ms flutter; solve medians 80.9 / 131.2 ms | file 3 L8–9 | known |
| K-g3 | Contended host-call waits 3.6–5.0 s from 4 instances at 100 m / 96 kHz, flat 4 → 8 | file 3; file 11 G-1 | known |
| K-g4 | Transient memory outside the solve; process peak with N concurrent builds | Seat 2, derived from the code [Inferred] / [Hyp]; not recorded | under-informed; **not load-bearing** (every surviving option narrows the gate; only *when* differs; condition 12 (f) measures it) |
| K-g5 | What narrowing buys in following and load | Seat 3 [Hyp] | uninformed; **not load-bearing** (narrowing is what her AX38 (i) already says; A′'s before/after measures it) |
| K-g6 | A `sim` change is needed to gate only the solve | from the code; Seat 2 gives the stage-split form | known |
| K-g7 | Core counts and RAM of producer machines | researcher RQ-G1: **NOT READY** (no producer source; general-PC proxies, ill-informed) | uninformed; **not load-bearing** (asked to weigh B's memory case; B falls to four veto-grade cells whatever the core count); carried as a declared unknown, replaced by the measurement in condition 12 (c) and (f) |
| K-g8 | 05h's "callback p99.9 with 1/4/8 concurrent builders" record ran builders serialised by the gate | from the code: `test_diffuse_records.cpp` L725–777 (builders rebuild through `decide` → `solveAndBuild` → the gate, `ScenePipeline.cpp` L196, L124) | known (Seat 5's finding, checked) |
| K-g9 | The poller can use existing test inspection calls without any `src/` change | from the code: `DiffuseSolveGate.h` L79–82 (`held()`, `waiting()`, `solvesCompleted()`; both take the gate mutex) | known |
| K-g10 | Record (d): only `pipes[0]` makes host calls; the others are builder-class churn; (c)'s offline pipeline is destroyed before (d) runs | from the code: L1115–1163, L1074–1114 | known |
| K-g11 | The 05i PR is not yet open; the PR's own CI run is the run of record | BUILD_PLAN §0 row 05i (no PR link); file 3 L3 | known |
| K-g12 | 07c-1 is `not started`; its conditions are 2, 4–7, 9, 10 and 11, and 10 is its first step | BUILD_PLAN L34; phase-07c-1 L54–127 | known |
| K-g13 | Table 15.1: 700 ms covers moves > 0.25 m (specular part); 3 s covers moves > 1 m (specular plus scattering); a VR proposal after Lentz et al. 2007 | corpus, Vorländer §15.3, Table 15.1 (read) | known; a yardstick by extension, not a gate |

Every load-bearing item is known. Seat 1's request (a researcher check of whether Lentz et al. derived 700 ms and 3 s from listening tests) is not load-bearing: Table 15.1 enters only as the way the records are read.

### Convening (unchanged from file 11)

Seats 1, 2, 3, 5 (lead), 6, 7 and 8 convened; every one answered. Seats 4 and 9 recorded not required (file 11's table), 0 / 0.

### Tension map (`now / later`; reasons are the seats' own words, shortened)

| Option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| A | 0/1 | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/1 | 0/1 | 0/0 | 1 | 9 |
| **A′** | 0/0 | 0/**0–1** | 0/**0–1** | 0/0 | 0/0 | 0/1 | 1/0 | 0/1 | 0/0 | **1** | **3–5** |
| B | 2/**3** | 1/2 | 1/**3** | 0/0 | 1/**3** | 2/**3** | 0/2 | 1/2 | 0/0 | 3 | — |
| D | 0/1 | 1/2 | 1/1 | 0/0 | 1/2 | 1/1 | 1/2 | 0/1 | 0/0 | 2 | 15 |
| E | 1/2 | 0/2 | 2/**3** | 0/0 | 0/**3** | 2/2 | 0/2 | 1/2 | 0/0 | 3 | — |

Seats 2 and 3 rated A′ later "0–1"; kept as written, 1 used for the maximum, the sum shown both ways (3 if both 0, 5 if both 1); not a re-rating.

**Reasons, cell by cell.** Seat 1: A 0 now ("no output change"), 1 later ("07c-1 can claim narrowing helps following without a before-remedy baseline"); A′ 0 / 0 ("the before-remedy gate-wait baseline is the 'measure the floor first' step"); B 2 now ("writes into her decision that whole-build serialisation is acceptable"), 3 later ("holds instance k's ISM update behind instance j's diffuse solve, contradicting 07c-1 condition 4"); D 0 / 1 ("benefit … unmeasured unless 05j records before and after"); E 1 now ("findable only in a PR follow-up"), 2 later ("could leave the release rule's protection … no recorded owner"). Seat 2: A 0 now ("no code"), 1 later ("commits 07c-1 to a stage split … which 07c-1 needs anyway"); A′ 0 now, 0–1 later ("as A, plus a before/after pair"); B 1 now ("a 2 s serialisation the memory rationale does not need"), 2 later ("the gate would still serialise ≈ 2 s of synthesis per instance"); D 1 now ("changes the sim API before 07c-1 restructures the same function"), 2 later ("the sim API changes twice"); E 0 now, 2 later ("no test pins the gate's scope"). Seat 3: A 1 now ("following stays strained until 07c-1"), 1 later ("07c-1 grows by one condition, the precondition of its own condition 4"); A′ 0 now ("print-only"), 0–1 later ("plus a measured before/after"); B 1 now, 3 later ("commits Phase 10 and 07c-1 condition 4 to an amendment that says the opposite"); D 1 now ("a phase of schedule"), 1 later ("two TSan rounds and tests rewritten once"); E 2 now ("a known departure … with no test"), 3 later ("can outlive 07c-1 unnoticed"). Seat 5: A 0 now, 1 later ("one new condition, the right owner"); A′ 0 now ("inside scope 2 … printed, none asserted"), 0 later ("the same poller becomes 07c-1's acceptance instrument"); B 1 now, 3 later ("writes a one-build bound for class (1) into her decision … door stays open by decision"); D 1 now ("one more phase cycle"), 2 later ("quiesce waits get worse … gate designed twice"); E 0 now, 3 later ("nothing would then hold the rule for G-1"). Seat 6: A 1 now ("any later 'following improved' rests on reasoning"), 1 later ("settling trigger has to be reworded (C1)"); A′ 0 now ("the gain … can be measured, not argued"), 1 later (as A); B 2 now ("ISM update waits behind other instances' whole builds"), 3 later ("'what they placed is what they hear' … N staggered arrivals"); D 1 now, 1 later ("settling semantics risk being reworked twice"); E 2 now ("without an owner or a register entry"), 2 later ("can reach producers with no owner"). Seat 7: A 0 now ("plan text only"), 1 later ("07c-1 grows and splits … only if needed"); A′ 1 now ("may cost one more 3-OS CI run if 05i's run has already been spent"), 0 later ("a before/after pair … 07c-1 can publish"); B 0 now, 2 later ("stall … becomes specified behaviour"); D 1 now, 2 later ("one full phase cycle … buys nothing in time to market"); E 0 now, 2 later ("first evidence would be a producer's forum post"). Seat 8: A 0 / 1 ("without the before figure"); A′ 0 now ("no producer meets this build"), 1 later ("commits 07c-1 to a new condition"); B 1 / 2 ("room-size, room or material changes still arrive one stem at a time"); D 0 / 1 ("reaches no producer sooner"); E 1 / 2 ("nothing bars release"). Seats 4 and 9: not required, 0 / 0.

### Minimum-tension working

1. **Bounds.** C is out (CLAUDE.md rule 5; phase-05i §0 and §8). B amends her decision, allowed only as a separate `FOR MAISARA` answer; not out by bounds. The 05i part of A′ is test-side only; Seat 5, the lead, rules it **inside scope 2** (it refines the required "worst host-thread wait for prepare, restore and offline" record and keeps "printed, none asserted"); a plan sentence below makes this explicit, so 05i's scope does not change silently.
2. **Veto-grade exclusion.** B out (Seats 1, 3, 5 and 6 rated it 3 later). E out (Seats 3 and 5 rated it 3 later). Survivors: A, A′, D.
3. **Worst-off seat.** A max 1, A′ max 1, D max 2: D drops; A and A′ tie at 1.
4. **Compose.** No variant brings the maximum to 0 (every narrowing option commits 07c-1 to a condition, which Seats 6 and 8 rate 1 later); none composed. The conditions adopted below are the seats' own conditions of acceptance for A and A′; none raises a seat above 1 by that seat's own statement (Seat 7 already counted 07c-1's growth in A's later 1 and A′'s later 0).
5. **Sum.** A′ 3–5, A 9: **A′ wins** under either reading of the "0–1" cells.
6. **Reversibility.** Not needed (A′'s 05i part is undone by deleting one test helper, Seat 7).
7. **Decide: A′**, with the conditions below.

### DECISION D-G1

**G-1 is a conformance defect of the code against her AX38 (i). It is fixed in code, not amended into her decision.**
1. AX38 (i) gains register entry **G-1** in the D-H3 (e) form, with its **own** release rule.
2. The remedy is a new **phase-07c-1 condition 12**: the gate narrowed to the diffuse solve, after condition 10 and before condition 9.
3. Phase 05i adds a **test-side gate-wait poller** to record (d) of scope 2, printed only: the before-remedy baseline, which 07c-1 re-runs unchanged as the after.

**Conditions of acceptance adopted:** Seat 5's items (1)–(9), all of them, in condition 12. Seat 2's stage-split form, plus the process-peak memory record (any breach to Phase 13, never an instance cap). Seat 3's one-difference-at-a-time order: 10 → 12 → 9, with records taken between 12 and 9. Seat 6's C2 (the spread across instances) in condition 12; Seat 6's C1 answered separately as `FOR MAISARA G1-C1` (it amends AX38 (iii)). Seat 1's two-row reading of Table 15.1, for reading the remedy records (specular against 700 ms, the full update with the diffuse part against 3 s; the +0.5 m step by extension); never a gate. **Not adopted:** Seat 1's click-detector run (Seat 1's condition for A, 1 → 0; Seat 1 already rates A′ 0 / 0; FR-SIM-6's "without audible artifacts" stays "not measured" until Phase 10-3, as in Q3); Seat 8's anchor-order idea (Seat 8 proposed nothing; it would weigh against NFR-8).

**Specification of the 05i poller (test-side; no `src/` change; never a CHECK).**
- **Where:** `tests/unit/test_diffuse_records.cpp`, TEST_CASE "records: AX38 (iv) per-instance restore, … host-thread waits (1, 4, 8 instances)", block (d) (L1115–1163). Both rooms, 48 and 96 kHz, 1, 4 and 8 instances; tag stays hidden `[diffuse-records-05i]`.
- **Helper:** a test-file helper `GateWaitPoller`: takes `plugin::DiffuseSolveGate::shared()` after `pipes` exist and releases it at the end of block (d). Around each of `pipes[0]`'s three host calls (prepare; `beginRestore` + `restore`; `setNonRealtime(true)` + the first offline block), a test thread loops with `sleep_for(1 ms)`; each pass reads `steady_clock`, `waiting(Class::Synchronous)`, `waiting(Class::Offline)` and `held()`. It records `solvesCompleted()` at the start and end of the call.
- **Definitions:** **queue(S)** and **queue(O)** = the sum of the poll intervals [tᵢ, tᵢ₊₁] whose starting sample had that class's waiter count ≥ 1. **remainder** = host-call time − queue(S) − queue(O). **resolution** = the observed maximum gap between polls (Seat 5: on Windows `sleep_for(1 ms)` can last about 15.6 ms [Hyp], so the gap is printed rather than assumed). In (d) only `pipes[0]` makes Synchronous or Offline entries (K-g10), so those counts are that call's.
- **Prints:** one line per (room, rate, instances, call), for the run with the worst host-call time of the 3: `05i-records (iv) gate-wait <room> <fs> Hz, <N> inst, <prepare|restore|offline switch + first block>: host call <h> ms = queue(Synchronous) <qs> ms + queue(Offline) <qo> ms + remainder <r> ms; max queue over 3 runs <qmax> ms; gate turns completed during the call <k>; polls <n>, max poll gap <g> ms (resolution); remainder includes this pipeline's own quiesce and its own build; poller locks the gate mutex about once per ms`. If no poll landed inside the call: `NOT MEASURED (no poll)`. The 1-instance line is the uncontended reference; its remainder against the 4- and 8-instance remainders is the CPU-sharing share that file 11 lists as not measured (K-q7).
- **Never:** no CHECK, REQUIRE or threshold of any kind; nothing runs off test threads; the poller thread is joined before `pipes` are destroyed; the p99.9 record is left untouched.
- **Predictions (from the code; written in the PR, not asserted):** at 100 m / 96 kHz with 4 or 8 instances, queue(S) ≤ about one foreign build (≈ 1.8–2.0 s) and remainder ≈ own quiesce plus own build; at 1 instance, queue ≈ 0; after condition 12, queue(S) ≤ one solve plus slack.
- **Timing:** it lands **before the 05i PR is opened**, so the PR's own CI run carries it (K-g11; CLAUDE.md "When to open a PR"). If the PR is already open, the 05i part is dropped (the decision becomes A), and 07c-1 takes the baseline after condition 10 and before condition 12.

### Load-bearing claims

- **D-G1-L1 (code).** The gate encloses the whole build and is process-wide (K-g1); a departure from AX38 (i)'s "held only around the solve".
- **D-G1-L2 (records, arithmetic).** Class (1)'s bound today is one build (664–1 870 ms) against one solve (80.9–131.2 ms), Linux medians, file 3 L8–9: **5–23× per scene** (flutter 664 / 131.2 = 5.1; low-α 1 870 / 80.9 = 23.1). (Seat 5's "≈ 14–23×" used a mixed pairing, 1 870 / 131.2 = 14.3.)
- **D-G1-L3 (code).** 05h's p99.9 "concurrent builders" record ran serialised builders (K-g8); its condition is restated in the plan and the record re-taken under condition 12 (c).
- **D-G1-L4 (code).** The poller needs only existing inspection calls (K-g9) and touches no `src/`.
- **D-G1-L5 (plan).** The 05i PR is not yet open (K-g11), which makes Seat 7's now-1 avoidable; the rating is kept as given.
- **D-G1-L6 (plan).** Condition 10 is 07c-1's first step and closes the D-H3 (e) entry and its release rule (phase-07c-1 L98–113); G-1 therefore needs its own rule (Seat 5 (9)).
- **D-G1-L7 (corpus).** Table 15.1's two rows as K-g13; used only to read records.
- **D-G1-L8 (seat statements of their own cost).** All cells as quoted in the map.
- **D-G1-L9 (product judgement).** No PRD goal points to D over A′; D reaches no producer sooner, because the release rule bars every build until 07c-1's entries close (Seats 7 and 8; AX38 (i) release rule).

### Future-debt register (A′; every later rating ≥ 1)

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| 2 (0–1) | 07c-1's stage split `plan → solve → assemble`, with `buildRoomIR` bit-identical | a one-line scope widening (Seat 2) | 07c-1 condition 12 (a), (f); condition 7 | A12 green; the G-1 entry removed |
| 3 (0–1) | 07c-1 grows by condition 12, the precondition of condition 4 across instances | a revert of the gate scope, about one parameter (Seat 3) | condition 12 (b), (g) records; Phase 10-3 artifacts | A12 green; Phase 10-3 |
| 6 (1) | the "settling" trigger reworded (C1), plus the spread record (C2) | a condition edit | condition 12 (g); Phase 11-3 | G1-C1 applied now; 11-3 built on it |
| 8 (1) | a new 07c-1 condition with a gate-wait test | one condition | 07c-1 gate-wait record; condition 7 re-measure | A12 green |

Seat 7's **now** 1 is not a later debt; it is avoided by landing the poller before the PR opens (D-G1-L5).

### Strongest objection

**Seat 2 / Seat 3: memory.** Once narrowed, N builders each hold about 0.3 GB outside the gate: about 2.4 GB at 8 × 100 m / 96 kHz [Hyp], unbounded in N — B's only real advantage. It holds anyway: (1) AX38 (i), her decision, bounds memory per solve and puts only the solve behind the gate; whole-build serialisation was never decided; (2) Phase 13 owns the memory budget (AX38 4a); (3) condition 12 (f) measures the process peak before anything ships, and the release rule bars producers until G-1 closes. It would not hold if condition 12 (f) shows a process peak that the Phase 13 budget cannot carry; then the open remedy is a limit on concurrently running builds, sized from the record — never an instance cap, a W_max cut or a range change (D-H1 (v)(d)) — and it comes back to the board. **Second-closest:** Seat 5's warning that narrowing puts N concurrent syntheses beside the audio threads, unmeasured; condition 12 (c) re-takes p99.9 with genuinely concurrent builders; a rise is a finding for the board.

**Confidence: medium.** No cell read from conditions; two cells are ranges ("0–1") that do not change the outcome; K-g4, K-g5 and K-g7 are unknown but not load-bearing; every acoustic statement rests on the corpus (Table 15.1, yardstick only).

**Reversal condition (07c-1, condition 12's records):** TSan `[pipeline]` finds a race in `sim` when ISM and synthesis overlap across pipelines and it cannot be fixed inside 07c-1 (narrowing waits; an interim wording returns to the board, with Seat 5's time-limited B form as the candidate); or condition 12 (f) shows a process peak beyond the Phase 13 budget (a build-concurrency limit returns to the board); or the 05i poller shows remainder ≫ one build at 4 and 8 instances, so CPU sharing rather than the gate dominates F-c (G-1's explanation of the records is revised; owner and timing stand, because conformance to AX38 (i) is required either way).

### Decided for Maisara — acceptance check (D-G1)

Checked against her AX38 (i) and NFR-1, NFR-3 / FR-SIM-6, L101, FR-SIM-7 / FR-3D-6 and NFR-8; no hard constraint broken. **A′:** restores her AX38 (i) as written; NFR-1 unchanged (no output change, AX5); serves NFR-3 / FR-SIM-6 "follow" across instances from 07c-1 on, with a measured before and after; L101: the release rule bars this build until it closes; FR-SIM-7: lag stops growing at N × one build. **A:** the same on every PRD id, but the gain cannot be checked against a before figure. **D:** the same PRD effect one phase earlier in the calendar; no producer hears it sooner (release rule); strains nothing in the PRD but costs a phase. No PRD id points to A or D over A′.

---

## FOR MAISARA G1-C1 — what "settling" means once the gate is narrowed

**Question.** AX38 (iii) says time at the gate "drives the UI 'settling' state on every instance waiting at the gate". After condition 12, an instance building its ISM or synthesis outside the gate is stale but not waiting at the gate; the same is true today of the instance that *holds* the gate. Should "settling" follow the gate wait as written, or the pending update?

**Answer (exact wording for AX38 (iii)):** "**(iii) Visibility:** time waiting at the gate counts in Phase 10's IR-staleness metric. The UI 'settling' state is shown on every instance whose latest change is not yet audible: queued at the gate, building, or in its AQ4 crossfade (Phase 10's IR staleness above zero), project load included. How it is drawn (delay, hysteresis, a scene-level aggregate) is Phase 11-3's (Seat 6)."

**Rests on:** PRD L101 ("must stay usable in a DAW session"), NFR-3 (L107), FR-SIM-6; her AX38 (iii) (ties "settling" to the staleness metric); phase-10-2 scope 3 ("IR staleness (time between the parameter change and the IR going live)"); 07c-1 A3, which already says "settling is shown while a solve is pending" (the plan text disagrees with itself today).

**Reasoning.** Her (iii) exists to make staleness visible. A gate-only trigger stays silent while an instance's audio is stale (already for the instance holding the gate, and after condition 12 for every instance building outside it). A readout that says "settled" while the user hears an old room works against L101's usability proviso. Keying it to staleness keeps her link between settling and staleness and removes the plan's internal disagreement. Implementable without locks: from the code, a pending update is the atomic `dirty_ != handled_` comparison (`ScenePipeline.cpp` L160–164).

**Options.** (a) Keep as written: strains L101 (the indicator is silent while the audio is stale) and leaves 07c-1 A3 contradicting AX38 (iii). (b) Pending-update trigger (chosen): serves L101 and FR-SIM-6's visibility of "follow"; consistent with (iii) and Phase 10's staleness. (c) Drop the readout: breaks her AX38 (iii).

**What would make her veto it:** the PRD never asks for a settling readout; a trigger on every pending update could flicker during dense automation (AQ10-room updates about 156 ms) and clutter the session, against L101 — which is why presentation (delay and hysteresis) is left to 11-3.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iii): the "settling" trigger, from gate wait to pending update; the staleness rule is unchanged.)

---

## Text for the plan-editor

These blocks replace file 11's Q3 block 2 ("Finding G-1 … Route: D-G1.") in full. In Q3 block 1, replace "G-1's route: D-G1" with "G-1: AX38 (i) register entry G-1, remedy phase-07c-1 condition 12 (D-G1)". In Q3 block 4's §6 row, replace "route D-G1" with "remedy phase-07c-1 condition 12 (D-G1)". If the interrogator's verdict on file 11 has not yet been applied, apply these blocks together with it.

**1. BUILD_PLAN AX38 (i), after the D-H3 (e) register entry and its release rule (new paragraph):** "**Register entry G-1, gate scope (phase 05i, 2026-11-11; D-G1, decider files 11 and 13; interrogator files 10 and <next>; the D-H3 (e) form).** From the code, the shipped gate is held for the whole room-IR build (`ScenePipeline::solveAndBuild`, `ScenePipeline.cpp` L124–132: image-source planning, unit-decay synthesis and the diffuse solve; only `makeIrSet` is outside). It is process-wide (`DiffuseSolveGate::shared()`), so every room-IR build in a process is serialised, whereas (i) says 'held only around the solve'. The class order holds. Class (1) waits up to one build already running (Linux medians at 100 m / 96 kHz: full rebuild 1 870 ms low-α, 664 ms flutter), not one solve (80.9 / 131.2 ms). Classes (2) and (3)'s 'about two solves' behaves as about two builds. *Recorded* (CI run 43007183782, phase 05i): contended host-call waits 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS (1.46–2.62× one instance, flat from 4 to 8; ≤ 2.3 s at 48 kHz; < 1 s at the AQ10 room); F-a (4.08 / 4.17 s) fits the same mechanism; load and staleness about linear in N (F-b, (iv)); CPU sharing not excluded. *Baseline before the remedy:* phase-05i scope 2 (d)'s gate-wait split (queue time from `waiting()` polled at about 1 ms, remainder = host call − queue, the maximum poll gap as resolution; printed, never asserted), from the 05i PR's CI run. *A record whose condition it changes:* 4c's 'callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders' ran its builders serialised by this gate (from the code, `test_diffuse_records.cpp` L725–777); it measures one build at a time beside the solve pool, not N concurrent builds, and is re-taken by the remedy. *Remedy:* phase-07c-1 condition 12 (the gate narrowed to the diffuse solve; after condition 10, before condition 9). The narrowing changes no output (AX5; each solve is a pure function of its scene, AX39/AX40). Never a W_max cut, a range change, a formulation seam or an instance cap (D-H1 (v)(d)). *Closes* when 07c-1's A12 passes in CI on three OSes, removed through `/fix-plan`. **Release rule: no build reaches a producer outside the team (beta included) while this entry is open** (the team as above). The rule is this entry's own and is **not** lifted when the D-H3 (e) entry closes under condition 10. Until this entry closes, the (iv) and 4c multi-instance records are read under G-1. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (i): register entry G-1 added, no rule change.)"

**2. BUILD_PLAN AX38 4c, *Records*:** after "callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders", insert "(builders serialised by the gate under AX38 (i) register entry G-1; re-taken with concurrent builders by phase-07c-1 condition 12)".

**3. BUILD_PLAN AX38 (iii) (FOR MAISARA G1-C1):** replace the (iii) sentence with the exact wording of G1-C1 above, followed by `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iii): the "settling" trigger.) Align: BUILD_PLAN L359: "'settling' on every instance waiting at the gate, project load included" → "'settling' on every instance whose latest change is not yet audible (queued at the gate, building or crossfading), project load included"; phase-11-3 scope 3: "shown on every instance waiting at the diffuse-solve gate, project load included" → "shown on every instance whose latest change is not yet audible (queued at the gate, building or crossfading; Phase 10's staleness above zero), project load included"; phase-10-2 scope 3: "the same wait drives Phase 11's 'settling' state" → "the staleness (gate wait included) drives Phase 11's 'settling' state"; phase-07c-1 condition 4, first bullet: "The UI shows 'settling' (AX38 (iii))" → "The UI shows 'settling' while the update is pending (AX38 (iii) as amended 2026-11-11, G1-C1)"; phase-07c-1 A3: "'settling' is shown while a solve is pending" → "'settling' is shown while an update is pending (AX38 (iii))".

**4. phase-07c-1, new condition after condition 11:** "12. **The gate narrowed to the diffuse solve** (D-G1, phase 05i, decider file 13; AX38 (i) register entry G-1; Seats 2, 3, 5 and 6). The AX38 gate encloses the diffuse solve only, as AX38 (i) states. Image-source planning, the unit-decay synthesis and the IR assembly run outside it. **Order:** after condition 10's cancel points (Seat 5), and before condition 9's synthesis move; records (b) and (g) are taken between the two, so the narrowing is judged by one difference at a time (Seat 3). **Form (Seat 2):** `sim::buildRoomIR` is split into stages (plan/ISM → diffuse solve → synthesis and assembly; names are the implementer's). `buildRoomIR` stays their composition for `render_cli`, with a test that its output is bit-identical to the composed stages on each platform (AX5). The pipeline holds `DiffuseSolveGate::Scope` around the solve stage only (RAII: `BuildCancelled` thrown inside the solve releases the gate), and the solve pool is passed only while the gate is held. Conditions 4 and 9 use the same stages. A sim API change only: no `contractVersion` change, `check_boundaries.py` unchanged, `sim` JUCE-free; not a formulation seam (D-H1 (v)(d)). Builder threads keep their default priority (AX38 (i)). **Tests and records:** (a) a `[pipeline]` test asserts that the gate is not held while image-source planning or the synthesis runs and is held during the solve (observed through a test hook; nothing on the real-time path); (b) phase 05i's gate-wait split, run unchanged, prints class (1)'s queue time at 1, 4 and 8 instances beside the 05i figures (prediction: at most one solve plus slack; printed, never a CHECK); (c) the callback p99.9 and max at host buffer 64, re-taken with 1, 4 and 8 genuinely concurrent builders and printed beside 05h's serialised record (a rise is a finding for the board, never fixed by an instance cap); (d) the worst `quiesce()` wait with N syntheses running concurrently; (e) TSan `[pipeline]` with two pipelines whose ISM and synthesis overlap while a third solves; (f) the AX38 (i) transient-memory record as the **process** peak with 4 and 8 concurrent builds at 100 m, 48 and 96 kHz (a breach goes to Phase 13's memory budget, scope 1, where a limit on concurrently running builds, sized from this record, is the open remedy; never an instance cap, a W_max cut or a range change, D-H1 (v)(d)); (g) the AX38 (iv) staleness records (room-size and joint steps; 1, 4 and 8 instances; both rooms, 48 and 96 kHz), re-taken, printing the min–max spread across instances (Seat 6 C2) beside the 05i figures, read by extension against Vorländer Table 15.1's two rows (the specular part against 700 ms for moves > 0.25 m; the full update with the diffuse part against 3 s for moves > 1 m; Seat 1) — a reading, not a gate. FR-SIM-6's 'without audible artifacts' stays not measured here (Phase 10-3). **Closes** AX38 (i)'s register entry G-1 and lifts its own release rule, through `/fix-plan`, when A12 passes. (D-G1)"

**5. phase-07c-1, acceptance criteria, new line after A11:** "- [ ] Condition 12: the `[pipeline]` test shows the gate held during the solve only; `buildRoomIR` bit-identical to its stages; TSan `[pipeline]` with overlapping ISM and synthesis green; records (b)–(d), (f) and (g) printed on three OSes, none asserted; the AX38 (i) register entry G-1 removed through `/fix-plan`. (D-G1, A12)"

**6. phase-07c-1 header and F1:** in the "Conditions (…)" heading, append "; condition 12: D-G1, phase 05i, decider file 13". F1 becomes: "Threading of the moved solve (no real-time wait, no lock on the audio thread, the AX38 gate's classes after the move; the gate's scope, solve only, and the stage split, condition 12) (phase-07c F1; D-G1)".

**7. phase-07c umbrella:** at L88, append "Condition 12 (D-G1, added 2026-11-11 by phase 05i: the gate narrowed to the solve) is in phase-07c-1." In "Where the original items went", add the row "| condition 12, A12 (added 2026-11-11 by phase 05i: D-G1) | 07c-1 |". BUILD_PLAN §0 row 07c-1, notes: append "Condition 12 (D-G1, 2026-11-11): the AX38 gate narrowed to the solve, after condition 10, before 9; closes AX38 (i) G-1."

**8. phase-05i scope 2, appended:** "**Gate-wait split (D-G1, decider file 13):** in record (d), a test thread polls `DiffuseSolveGate::shared()`'s `waiting()` and `held()` at about 1 ms during each of the host calls and prints queue(Synchronous), queue(Offline), the remainder (host call − queue; it includes the pipeline's own quiesce and build), gate turns completed and the maximum poll gap as resolution. This is the before-remedy baseline of AX38 (i) register entry G-1, re-run unchanged by phase-07c-1 condition 12. Test-side only, no `src/` change, printed, never asserted; it lands before this phase's PR is opened." In the second acceptance criterion, after "The AX38 (iv) records of scope 2", insert "(with the gate-wait split)".

**9. §6 row:** "2026-11-11 | 05i | D-G1: AX38 (i) register entry G-1 (the gate held for the whole room-IR build; its own release rule; remedy phase-07c-1 condition 12 and A12, the gate narrowed to the solve after condition 10 and before condition 9); phase-05i scope 2 gate-wait split (test-side, printed); AX38 4c p99.9 record condition restated (serialised builders). G1-C1: AX38 (iii) 'settling' keyed to a pending update; phase-10-2, phase-11-3 and phase-07c-1 aligned | decider files 11, 13; seats 12-seat1/2/3/5/6/7/8; researcher 12-researcher-RQ-G1; interrogator <next>".

---

## Summary

| id | decision (exact) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-G1 | A′: register entry G-1 in AX38 (i) with its own release rule; remedy phase-07c-1 condition 12 (gate narrowed to the solve, 10 → 12 → 9, Seat 5's (1)–(9), Seat 2's stage split and process-peak memory record, Seat 6 C2); test-side gate-wait poller in 05i scope 2 (d), printed only, before the PR opens | proposed | Seats 2, 3, 6, 7, 8 (1; S7 now, the others later) | 3–5 | medium | AX38 (i) (her decision), NFR-1, NFR-3, FR-SIM-6, FR-SIM-7, L101, CLAUDE.md rule 5, D-H1 (v)(d) | Vorländer §15.3 Table 15.1 (yardstick only) | TSan race in overlapping `sim` stages; process peak beyond the Phase 13 budget; remainder ≫ one build (G-1's account revised, owner unchanged) |
| G1-C1 | AX38 (iii): "settling" on every instance whose latest change is not yet audible (queued, building, crossfading), project load included | for Maisara | Seat 6 (debt repaid) | — | high (plan and PRD text; no acoustic claim) | L101, NFR-3, FR-SIM-6; her AX38 (iii) | none needed | 11-3 shows the trigger cannot be drawn without clutter (only presentation changes) |

## Challenges to settled decisions

None. G-1 is a defect of the code against her AX38 (i), not a challenge to her decision. G1-C1 amends AX38 (iii) as a `FOR MAISARA` answer.

## Decided for Maisara

- **D-G1:** the code holds the room-build gate longer than your AX38 (i) allows. It is fixed in code, not written into your decision: phase 07c-1 narrows the gate to the solve (condition 12), and 05i first records how long host calls wait today, so the fix can be shown to help. Until it is fixed, no build reaches a producer (a release rule of its own). Rests on your AX38 (i); NFR-1 (no output change); NFR-3, FR-SIM-6 and FR-SIM-7 (multi-stem following); L101 (usable in a session); CLAUDE.md rule 5. Who gave most: Seat 7 (one test helper in 05i, and a CI run if the PR were already open; it isn't); it gets back a measured before and after that it can publish. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (i): register entry G-1; phase-07c scope extended by condition 12.)
- **G1-C1:** the "settling" light shows whenever a change has not reached the audio yet, not only while an instance waits at the gate; otherwise it would say "settled" while you hear the old room. Rests on L101, NFR-3, FR-SIM-6, and your AX38 (iii). Who gave most: Seat 6 (takes the rewording now, keeps how it is drawn for Phase 11-3). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iii).)

**NEEDS MAISARA:** none. B, the only option that would have needed an override of veto-grade ratings (four seats), was not chosen.
