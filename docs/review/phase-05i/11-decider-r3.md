# 11 — Decider, round 3: answer to interrogator file 10, Q3 re-answered, and convening for D-G1 (gate scope)

Phase 05i, 2026-11-11. Saved verbatim by the orchestrator from the decider's report (the decider reads only).

**Corpus:** `docs/corpus/` present, revision **c1b171fe649f07cbeb952ef1f75d89bfaa414d0d** (`SOURCE_COMMIT`). Vorländer §15.3 and Table 15.1 read directly (`vorlaender-auralization.md` L3952–3968).

**Read for this round:** review files 7 (with its correction header), 9 and 10; file 3 L1–75, plus the joint-step lines for macOS and Windows (L148–203, L250–305). From the code: `src/plugin/core/ScenePipeline.cpp` L95–243 and `ScenePipeline.h` L204; `DiffuseSolveGate.h` in full; `src/sim/Engine.cpp` L326–332; `tests/unit/test_diffuse_records.cpp` (searched for any click or artifact detector: none; and for where the (iv) records come from: only this file); `tests/unit/test_diffuse_gate.cpp` (its uses of `held()` and `waiting()`). Plan: BUILD_PLAN §0 rows 05h, 05i, 07c and 07c-1; AQ4 (L109); AQ10 (L115); AX38 (i) (L158, the gate sentence and the class order). Phases: phase-05h §2 scope 2, §5 (the gate, the AX38 (i) register entry, RG-1 (a)–(d)) and §9; phase-05i in full; phase-07c-1 in full. PRD L36–165. `docs/board/README.md` (the convening table and "Who answers Maisara's questions").

## PRD digest

- **For whom:** producers and sound designers working in a DAW; multi-stem scenes are built from several plugin instances (L42, FR-3D-6, FR-SIM-7, A5).
- **Outcome:** an accurate room render (NFR-1) that follows automated movement (FR-SIM-6, NFR-3) and restores exactly (NFR-6).
- **Hard constraints that bear here:** NFR-8 (no scene-specific paths); the one-phase rule (CLAUDE.md rule 5; phase-05i §0 "the engine … do not change here"; §8 excludes everything 05h §9 excludes); D-H1 (v)(d) (no W_max cut, no range change, no seam, no instance cap); AX38 (i), her decision of 2026-11-10 ("held only around the solve"; class (1) "waiting at most for the one solve already running"; the release rule: no build reaches a producer while an (i) register entry is open); AX38 (iv) with R3 (accepted 2026-11-10); AQ4 and AQ10 as plan defaults.
- **PRD reading used below:** NFR-3 (L107) says "This tension goes to the Expert", and Q4 (L159) is that question; its default, AQ4, binds. L101's "latency" is NFR-2's latency, reported to the DAW for compensation (L106). L101's proviso "must stay usable in a DAW session" is a condition every option is shown against. No PRD line ranks NFR-3's tension.
- **Verification culture:** every DSP behaviour has an automated check; independent references over self-made goldens; a claim not measured is stated as not measured.

---

## Answers to the interrogator's five rebuttal questions (file 10)

**1. Gate scope. Yes: the gate is held for the whole room-IR build. P05I-47 and P05I-48 are accepted.** From the code: `ScenePipeline.cpp` L124 constructs `DiffuseSolveGate::Scope`; its destructor calls `leave()` (`DiffuseSolveGate.h` L92–96) only after `sim::buildRoomIR` returns (L132). The ISM, the unit-decay synthesis and the solve (`Engine.cpp` L331) therefore all run under the gate; only `makeIrSet` (L197) runs outside it. The gate is process-wide (`ScenePipeline.h` L204, `DiffuseSolveGate::shared()`), so **every room-IR build in the process is serialised**.

Consequences, from the code and the records: class (1) keeps its priority (the contended host-call wait is flat from 4 to 8 instances: Linux 3 778 → 3 803 ms; Windows 3 816 → 3 870 ms), but its bound is one build already running (≈ 1.8–2.0 s at 100 m / 96 kHz), not one solve (≈ 81–91 ms). F-c (3.6–5.0 s, 1.46–2.62× one instance) is a class-(1) wait for a full build followed by the caller's own build. Record (c)'s +1.76 s is one more turn of full builds: AX38 (i)'s "about two solves" behaves as about two builds. F-b's growth, roughly linear in instance count, is what serialisation predicts (e.g. 8 × 100 m / 96 kHz room-size staleness 16 304 ms is 8.6× the one-instance 1 894 ms, Linux, file 3 L56, L66). F-a (4.08 / 4.17 s contended restore with one contending pipeline, against a restore alone of about 2 s) fits the same mechanism; file 9's "not shown to share F-a's cause" is withdrawn. CPU sharing is not excluded, and its share is not measured; "hypothesis: CPU sharing outside the gate" is struck everywhere.

**What the departure is:** a conformance defect of phase 05h's shipped code against AX38 (i), her recorded decision. The code holds the gate wider than (i) allows ("held only around the solve"); it therefore breaks class (1)'s bound in magnitude (one build instead of one solve) while keeping the class order. It is conservative on memory (no two builds overlap in a process) and costly on waiting. **05i cannot fix it:** phase-05i §0 and §8 put the engine out of scope, and CLAUDE.md rule 5 says work belonging to another phase is a follow-up. The fix touches `src/sim` as well, because the solve is called inside `buildRoomIR`, so narrowing the gate needs a solve hook or a seam split (`Engine.cpp` L326–331). No existing rule names this case; the nearest form is AX38 (i)'s own register entry (D-H3 (e): recorded values, remedy phase, release rule). Who owns the fix, and whether to fix the code or amend her decision to match it, is **D-G1**, convened below; not decided inside Q3, and her decision is not amended quietly.

**Q3 options:** Q3 gains option E (narrow the gate now), out by bounds in 05i; its route elsewhere is D-G1's. **F-c plan text:** file 9's F-c text was never applied (Q3 fell); withdrawn whole and folded into finding **G-1** below.

**2. Instrument. None exists today. P05I-51 is accepted.** `[probe-restore-split]` is single-threaded and uncontended, has no gate and no solve, and cannot time a gate wait; struck as F-c's instrument. **An instrument that can measure it**, from the code and with no `src/` change: during each contended host-call record of scope 2 (prepare, restore, offline switch, at 4 and 8 instances), a test thread polls `DiffuseSolveGate::shared()->waiting(Class::Synchronous)` and `held()` every 1 ms (inspection calls the gate tests already use, `test_diffuse_gate.cpp` L109, L116). It prints, per call, the **queue time** (the span during which the Synchronous waiter count is ≥ 1 after the call begins) and the **remainder** (host-call time minus queue time). Resolution about ±2 ms against waits of seconds; in these records only one instance makes a host call, so the waiter count is that call's. Predictions: from the code as it stands, queue time ≤ one build (≈ 2.0 s at 100 m / 96 kHz) and remainder ≈ one build; after a narrowing to the solve, queue time ≤ one solve plus slack. Where it runs (05i as a baseline record, or 07c-1 as the remedy's acceptance test) is part of D-G1.

**3. PRD reading. No PRD id ranks NFR-3's tension. P05I-52 is accepted.** NFR-3 (L107) sends it to the Expert. L101's "latency" is NFR-2's reported latency (L106), not IR-update staleness. Q3 is re-answered without "the PRD ranks": it rests on her recorded decisions (R3 / AX38 (iv); D-H1 (v)(d); AX38 (i)'s release rule), the bounds (CLAUDE.md rule 5; phase-05i §0 and §8), and Q4 / AQ4 routing. Each option is shown against L101's "must stay usable in a DAW session".

**4. Scope of the strain. Restated. P05I-53 and P05I-55 are accepted.** By extension, Table 15.1 is a proposal for VR after Lentz et al. 2007 (Vorländer §15.3): its 700 ms row covers "translational listener or source movement > 0.25 m" and updates the binaural processing and the specular part; the scattering part has the 3 s row (> 1 m); no row covers a room-size edit, so the yardstick applies only to the joint step's +0.5 m listener move. Worst-instance joint staleness (file 3), Linux / macOS / Windows:

| room, sample rate | instances | joint staleness, worst instance (ms) | against 700 ms |
|---|---|---|---|
| 100 m cube, 48 kHz | 1 | 725 / 834 / 883 | over on every OS |
| 100 m cube, 96 kHz | 1 | 1 812 / 1 752 / 1 919 | over on every OS |
| AQ10 room, any rate | 1 | 156–421 | within |
| AQ10 room, 48 kHz | 4 | 612 / 658 / 827 | over on Windows only |
| AQ10 room, 96 kHz | 4 | 1 319 / 1 395 / 1 647 | over on every OS |
| AQ10 room, 48 kHz | 8 | 1 221 / 1 138 / 1 637 | over on every OS |

So "at its heaviest multi-instance records" is struck: the strain starts with **one instance at 100 m**, and at the AQ10 room **from 4 instances at 96 kHz** (from 4 at 48 kHz on Windows, from 8 at 48 kHz on every OS). In today's code the specular part waits behind the whole rebuild; the plan's remedies are 07c-1 condition 4 ("the ISM update is never held behind the diffuse solve") and Phase 10. **R2:** "position path 31–90 ms" is the **Phase-10 proxy** (AQ10: Phases 04–09 time the build "without generating the unit decay, as its proxy"). Today every change is a full uncached rebuild; at the AQ10 room, one instance, Linux, that is 156–166 ms at 48 kHz and 340–356 ms at 96 kHz (file 3 L11–12, L26–27).

**5. Artifacts. Not measured.** From the code: no click or artifact detector runs in `test_diffuse_records.cpp`, the only source of the (iv) records. "Nothing is reported to click" becomes "**not measured**". FR-SIM-6's "without audible artifacts" is stated as AQ4's design intent (30 ms crossfade; Vorländer §9.2.1 describes the constant-power overlap but makes no audibility claim); Phase 10-3's artefact gates are its check.

**Corrections from file 10:** all four applied (strikes; "not measured"; onset against the 700 ms row by extension; R2 as the proxy). P05I-49 applied in record (c)'s wording.

---

## Q3 — FOR MAISARA Q3 (revised, round 3): Raise item 2 on 05i's records

**State:** revised; P05I-47…55 applied; the route of finding G-1 deferred to D-G1.

**Answer.** "It stands. The records are appended, F-b is extended, and F-c is withdrawn into a new finding, **G-1 (gate scope)**: the shipped code departs from AX38 (i), and D-G1 routes it.
- **On this build, following automated movement is strained** (NFR-3; FR-SIM-6's 'follow'). Measured against AQ4's own yardstick (Vorländer Table 15.1's 700 ms row for moves > 0.25 m, applied by extension), the strain starts with one instance at 100 m (725–883 ms at 48 kHz, 1 752–1 919 ms at 96 kHz) and, at the AQ10 room, from 4 instances at 96 kHz.
- **Artifacts were not measured** on these records. 'Without audible artifacts' rests on AQ4's crossfade as design intent until Phase 10-3's gates.

**The load:** 8 instances at the 100 m low-α cube, 96 kHz: 19.5 / 16.3 / 23.0 s (Linux / macOS / Windows): above 10 s, at or below 05h's figures (20.4–25.6 s recorded; 16.5–25.6 s on file); 7.9× / 7.5× / 9.3× the single-instance load, which is what process-wide serialisation of builds predicts (G-1). Windows' excess over 8× lies in restore (instances 5–8) and prepare (6–8); its cause is not established. At 48 kHz: 8.3 / 8.4 / 9.9 s. R3's class is unchanged.

**F-b extended:** staleness when automated together at 8 × 100 m / 96 kHz: room-size step up to 16.3 / 14.6 / 16.4 s; joint step up to 15.7 / 14.4 / 15.1 s (the listener move waits for the full rebuild until Phase 10-1's position path and 07c-1 condition 4); while another instance renders offline up to 29.4 / 27.9 / 31.8 s, about one more full build per turn ('about two solves' in AX38 (i) behaves as about two builds under G-1). The offline wait is about linear in M (F20).

**G-1, from the code:** the AX38 gate is held for the whole room-IR build (ISM, unit-decay synthesis, solve), not only around the solve as AX38 (i) states. Class (1) therefore waits up to one build (≈ 1.8–2.0 s at 100 m / 96 kHz), and builds are serialised across the process. Records it explains: contended host-call waits of 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS (1.46–2.62× one instance, flat from 4 to 8); F-a's 4.08 / 4.17 s fit the same mechanism; ≤ 2.3 s at 48 kHz; < 1 s at the AQ10 room. CPU sharing is not excluded, and its share is not measured; it is measured by the gate-wait record (rebuttal answer 2). Its owner and remedy: D-G1.

**Remedy, unchanged for the rest:** phase-07c conditions 9 (or 07d) and 10; staleness shown as AX38 (iii) 'settling'; condition 7 re-measures (time-to-audible, time-to-settle); 07c-1 condition 4 and Phase 10's position path and staleness metric (AX38 (v)); phase-13 Raise item 3 applies the 10 s line to the release build.

**Never:** a W_max cut, a range change, a seam or an instance cap. No figure in the compatibility notes. The build never reaches a producer (AX38 (i) release rule)."

**PRD ids and decisions.** PRD: L101; L49; NFR-1; NFR-2; NFR-3 (L107); FR-SIM-6 (L89); Q4 (L159) with its default AQ4; NFR-6; L42, FR-3D-6 and FR-SIM-7. Her decisions: AX38 (i) (gate scope, class order, release rule), (iii), (iv) with R3, (v), and 4c (accepted for her 2026-11-10); D-H1 (v)(d).

**Reasoning.** (1) Raise item 2's rule is her recorded decision R3: a load above 10 s is barred from producers and cured in 07c; 05i's figures leave its class unchanged, so the PRD is not silent and this is not case (a). (2) NFR-3 sends its tension to the Expert (L107); Q4's default, AQ4, binds; the board records the strain against AQ4's own yardstick and does not answer Q4. (3) Every option that relieves following now is out by bounds: C by D-H1 (v)(d); D and E by CLAUDE.md rule 5 and phase-05i §0 and §8. (4) G-1 is a departure from her decision; routed by a board decision (D-G1), not absorbed into a record. (5) The L101 proviso is not shown to be met at the heavy records; the AX38 (i) release rule keeps this build away from producers until it is.

**Options, against NFR-1, NFR-3, FR-SIM-6 and the L101 proviso:**
- **(A) Chosen:** records appended, R3 stands, F-b extended, F-c folded into G-1 (route D-G1), strain recorded with owners. Serves NFR-1 (no W_max change) and NFR-2. NFR-3 and FR-SIM-6 'follow' strained and recorded; FR-SIM-6 'without artifacts' not measured (AQ4 design intent). L101 proviso: not met at 100 m from 1 instance or at the AQ10 room from 4 at 96 kHz; no user meets this build (release rule); re-checked at 07c condition 7 and Phase 13 item 3.
- **(B) NEEDS MAISARA:** none of the three cases applies; R3 settles the Raise item and NFR-3 names its owner; serves no PRD id better than (A).
- **(C) Cap instances or W_max:** serves NFR-3 and the L101 proviso (shorter following); strains NFR-1, L42, FR-3D-6 and FR-SIM-7; out under D-H1 (v)(d).
- **(D) Pull 10-1 / 07c moves into 05i:** would serve NFR-3 for listener-only moves; out by CLAUDE.md rule 5 and phase-05i §8.
- **(E, new) Narrow the gate to the solve now, in 05i:** would serve AX38 (i) class (1) and plausibly multi-instance following (how much is not measured); strains nothing in the PRD visible today (memory under concurrent builds is for D-G1); out in 05i by CLAUDE.md rule 5 and phase-05i §0 and §8; its route elsewhere is D-G1.

**Veto reading:** NFR-3 says "must render smoothly", L101 says the plugin "must stay usable", and the code does not do what her own AX38 (i) says, so a record-only answer looks like tolerating a known defect. It holds because D-G1 routes G-1 with an owner and a remedy; the release rule bars producers meanwhile; 07c condition 7 and Phase 13 item 3 re-measure. It would fall if D-G1 left G-1 without an owner phase before 07c-1 is `done`.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv) and 4c: 05i record lines appended; F-c withdrawn into G-1; strain recorded; no rule change.)

**Convening (Q3):** no seat convened. Q3 reads her recorded rules against the records; the only option that creates a design change (E) goes to D-G1, where the seats are convened.

**Knowledge inventory (Q3)**

| K | what | source | status |
|---|---|---|---|
| K-q1 | the gate encloses `buildRoomIR` and is process-wide | from the code: ScenePipeline.cpp L124–132, .h L204; DiffuseSolveGate.h L92–96 | known |
| K-q2 | the (iv) records: load, staleness, offline, host-call waits | file 3 (verified by P05I-46) | known |
| K-q3 | Table 15.1 rows and conditions | Vorländer §15.3, Table 15.1 (read) | known; applied by extension (a VR proposal) |
| K-q4 | AQ4's yardstick is the 700 ms row | BUILD_PLAN L109 | known |
| K-q5 | no artifact measurement in the (iv) records | from the code (`test_diffuse_records.cpp`) | known |
| K-q6 | AQ10 proxy; full rebuild at the AQ10 room | BUILD_PLAN L115; file 3 L11–12, L26–27 | known |
| K-q7 | CPU-sharing share of F-c | none | uninformed; not load-bearing for Q3 (stated "not measured"); measured by the gate-wait record |

**Load-bearing claims (Q3).** Q3-L1 (code): the gate is held across the whole build and is process-wide (K-q1). Q3-L2 (derived): serialisation predicts load and staleness roughly linear in N: 16 304 / 1 894 = 8.6 and 15 705 / 1 812 = 8.7 at 8 instances (Linux). Q3-L3 (corpus): the 700 ms row covers moves > 0.25 m and updates the specular part; the 3 s row covers > 1 m with the scattering part; a proposal after Lentz et al. 2007. Q3-L4 (records): the onset table above. Q3-L5 (code): artifacts not measured. Q3-L6 (PRD): NFR-3 routes to the Expert; L101's latency is NFR-2's. Q3-L7 (her decisions): R3; D-H1 (v)(d); the AX38 (i) release rule.

**Text for the plan-editor (Q3). It replaces file 9's Q3 blocks entirely (they were never applied).**
1. **AX38 (iv), after the 2026-11-10 record:** "*Record (phase 05i, CI run 43007183782):* 8 × 100 m low-α / 96 kHz load 19.5 / 16.3 / 23.0 s (7.9× / 7.5× / 9.3× the single load; at or below 05h's figures; ≈ linear in N, as the process-wide serialisation of builds predicts, finding G-1, AX38 (i)); Windows' excess in restore (instances 5–8) and prepare (6–8), cause not established; 48 kHz 8.3 / 8.4 / 9.9 s; R3 stands. F-b extended: staleness when automated together up to 16.4 s (room size) and 15.7 s (joint; the listener move waits for the full rebuild until 07c-1 condition 4 and Phase 10-1's position path); during another instance's offline render up to 29.4 / 27.9 / 31.8 s (≈ one more full build per turn, G-1); offline wait ≈ linear in M (F20). Following against AQ4's yardstick (Vorländer Table 15.1, 700 ms for moves > 0.25 m, by extension; listener +0.5 m of the joint step): over from 1 instance at 100 m (725–883 ms at 48 kHz, 1 752–1 919 ms at 96 kHz) and at the AQ10 room from 4 instances at 96 kHz (1 319–1 647 ms). Artifacts not measured on these records (AQ4's crossfade is the design intent; Phase 10-3 gates it). PRD NFR-3 / FR-SIM-6 'follow' strained on this build; owners: phase-07c conditions 4, 9–10 and 7, AX38 (iii), Phase 10; G-1's route: D-G1. Remedy unchanged."
2. **AX38 (i), after its register entry:** "**Finding G-1 (phase 05i, decider file 11; interrogator file 10 P05I-47/48):** from the code, the gate is held for the whole room-IR build (`ScenePipeline::solveAndBuild`: ISM, unit-decay synthesis and solve; only the IR-set build is outside), not only around the solve as (i) states; class (1) keeps its order but waits up to one build (≈ 1.8–2.0 s at 100 m / 96 kHz), and builds are serialised per process. Records: contended host-call waits 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS (1.46–2.62× one instance, flat 4 → 8); F-a fits the same mechanism; CPU sharing not excluded, not measured. Instrument: the gate-wait record (queue time from `waiting(Synchronous)` polled at 1 ms; remainder = host call − queue). Route: D-G1."
3. **AX38 4c, in the record against the anchors after F-b:** "(F-a and the 05i contended host-call records: see finding G-1, AX38 (i).)"
4. **§6 row:** "2026-11-11 | 05i | AX38 (iv)/(i)/4c: 05i records appended; finding G-1 (gate held for the whole build) recorded, route D-G1; F-c withdrawn into G-1 | decider files 9/11, interrogator files 10/<next>".

---

## D-G1 — CONVENE: the gate-scope departure (G-1): its class, owner and timing

**Restatement:** G-1 has to be either fixed in code or amended into her decision. The choice is who owns the change and when; it also decides whether 05i records a before-remedy gate-wait baseline. What depends on it: `ScenePipeline::solveAndBuild` and a solve hook in `sim::BuildOptions` / `buildRoomIR`; class (1)'s bound (prepare, restore, `setNonRealtime`, `reset()`); multi-instance following and load (the (iv) records); process transient memory with concurrent builds (AX38 (i) 1 GB per solve, ≤ 128 MB resident); the AX38 (i) release rule; 07c-1's conditions 2, 4, 9 and 10 and its contractor focus F1.

**Options:**
- **A.** Register entry G-1 under AX38 (i), in the D-H3 (e) form (recorded values, remedy, release rule). The remedy is in **phase-07c-1**, as a new condition: the gate encloses the diffuse solve only (a solve hook or seam in `sim`; no output change, since the solve is a pure function of its scene, AX39/AX40); tests: a `[pipeline]` test that the gate is not held while the ISM or synthesis runs; the gate-wait record showing a class (1) queue ≤ one solve plus slack; the transient-memory record with N builds outside the gate; TSan `[pipeline]`. The release rule covers the entry until it closes. No code in 05i.
- **A′ (mine).** A, plus the test-side gate-wait poller added in 05i to scope 2's contended host-call records: print only, no `src/` change, a before-remedy baseline. Seats are asked whether this lies inside phase-05i scope 2.
- **B.** A FOR MAISARA amendment of AX38 (i) to match the code: "held for the room-IR build; class (1) waits at most for the one build already running". `AMENDS her decision of 2026-11-10`.
- **C.** Fix in 05i. **Out by bounds** (CLAUDE.md rule 5; phase-05i §0, §8). Listed for the record only.
- **D.** A new phase **05j** (size S) between 05i and 07c-1 that narrows the gate only, with A's tests; 07c-1 builds on it.
- **E.** A follow-up line in 05i's PR and an extended 07c-1 F1 only. No register entry and no release-rule coverage.

**Convening table**

| seat | status | reason (table item) | brief |
|---|---|---|---|
| 1 | convened | Which bar applies to update lag (Table 15.1 by extension); any audibility claim an option assumes; touches what the user hears | Brief 1 |
| 2 | convened | Simulator compute and recompute time; the representation handed over (a solve hook in `buildRoomIR`); memory per build | Brief 2 |
| 3 | convened | Time variance under automation (following); per-instance CPU when builds run concurrently; touches what the user hears | Brief 3 |
| 4 | not required | No HRTF, format, decoding or loudness-parity item; the gate scope is format-independent (the binaural records are 08-4's, under the same gate) | — |
| 5 | **convened (lead)** | Threading topology; worst-case host-call waits; offline equals real-time; TSan / CI gates; review of real-time code; touches the audio thread and hosts | Brief 5 |
| 6 | convened | Automation and motion model; DAW workflow; the "settling" readout (AX38 (iii)); touches the user's controls | Brief 6 |
| 7 | convened | Schedule and complexity cost (D adds a phase); the release rule; what one founder can sustain; touches cost | Brief 7 |
| 8 | convened | Producer workflow with several instances (FR-SIM-7, A5): whether serialised following bites | Brief 8 |
| 9 | not required | No geometry, material or preset choice; 100 m is a test scene, not a preset decision | — |

**Common brief (all convened seats; the orchestrator passes it verbatim, followed by each seat's line).**
- **Matter:** D-G1 above (restatement and options A, A′, B, C, D, E).
- **Read:** `docs/review/phase-05i/10-interrogator-file9.md` (P05I-47…55); this file's rebuttal answers 1–2 and finding G-1; `docs/review/phase-05i/3-orchestrator-ci-records.md` L1–70 (the (iv) records; the macOS and Windows sections the same); from the code: `src/plugin/core/ScenePipeline.cpp` L115–199, `ScenePipeline.h` L204, `src/plugin/core/DiffuseSolveGate.h`, `src/sim/Engine.cpp` L240 and L320–335; `docs/BUILD_PLAN.md` L158 AX38 (i) (the gate sentence, the class order, the register entry, the release rule), AQ4 (L109), AQ10 (L115); `docs/phases/phase-05i.md` §0, §3 scope 2, §8; `docs/phases/phase-05h.md` §5 (the gate criterion, the AX38 (i) register entry) and §9; `docs/phases/phase-07c-1.md` conditions 2, 4, 9, 10 and F1; PRD NFR-2, NFR-3, FR-SIM-6, FR-SIM-7, L101; Vorländer Table 15.1.
- **Rate:** every option A, A′, B, D and E, `now / later` (0–3); a one-line reason per cell, conditions of acceptance for any 2 or 3, and your ranking. In the later column, name what the option commits later phases to, what undoing it costs, and where the evidence arrives.
- **Fixed for everyone:** the code facts above. The CPU-sharing share is not measured. No option may change any output (AX5), add a per-host or per-scene path (NFR-8), cut W_max or cap instances (D-H1 (v)(d)).

**Seat-specific lines.** Brief 1: which bar the 700 ms row (by extension) should be read against for following lag, and whether any option rests on an audibility claim you would not accept (`NOT MY MATTER` if none). Brief 2: the `sim` API change needed to gate only the solve (a hook in `BuildOptions`, or splitting `buildRoomIR`) and its contract-boundary cost; the share of the 293–297 MB build transient (05h record) that lies outside the solve, from the code or a record you can cite; whether concurrent ISM and synthesis across N instances strains AX38 (i)'s memory rules; whether A's remedy belongs with 07c-1 condition 9's synthesis move. Brief 3: per-instance CPU, and following under automation when builds run concurrently instead of serialised; whether narrowing helps following on 4-core machines. Brief 5: class (1)'s bound; host-thread stalls; whether narrowing is safe before 07c-1 (abandon, quiesce, the offline path, TSan); whether A′'s poller is inside phase-05i scope 2 (a record refinement in 05i's test file) or outside it; the memory and threading risk of B; whether 07c-1 or a 05j is the right owner. Brief 6: what each option means for the "settling" readout and automation workflow (Phase 11 hand-off). Brief 7: the cost of D (a phase and CI cycles) against A; whether B's amendment changes any public-wording or release-rule exposure. Brief 8: whether multi-instance following lag (serialised builds) bites the producer workflows you represent, and which option you can live with.

**Knowledge inventory, first pass (D-G1)**

| K | what | source | status |
|---|---|---|---|
| K-g1 | gate scope and process-wide sharing | from the code (above) | known |
| K-g2 | one 100 m / 96 kHz build ≈ 1.75–2.15 s | file 3 L57 and macOS/Windows lines; 05h §0 row | known |
| K-g3 | contended host-call wait 3.6–5.0 s, flat 4 → 8 | file 3; P05I-46/48 | known |
| K-g4 | transient memory outside the solve per build; process peak with N concurrent builds | 05h: 293–297 MB whole-build delta (Linux) | under-informed (the split is not recorded); Seats 2 and 5 |
| K-g5 | what narrowing would buy in following and load | none | uninformed; depends on cores and memory bandwidth; measurable only after a narrowing |
| K-g6 | sim change needed to gate only the solve | from the code: `Engine.cpp` L326–331 inside `buildRoomIR` | known (that a hook or seam is needed); its form is Seat 2's |
| K-g7 | core and RAM base rates of music-production machines | — | uninformed → RQ-G1 |

**RESEARCH NEEDED (alongside the seats).** **RQ-G1:** the distribution of physical core counts and installed RAM among music-production computers, 2023–2026, from a published survey or vendor statistic with its method and sample stated (not a general-PC survey unless it is the only source, and then marked so). Why it matters: if most producer machines have ≤ 4 performance cores, narrowing (A / A′ / D) buys little following for N ≥ 4 and weighs mainly on class (1); B's memory argument then gains relatively. If ≥ 8 cores are typical, narrowing's benefit to NFR-3 is larger.

**CONVENE: Seats 1, 2, 3, 5 (lead), 6, 7 and 8 on D-G1, and the researcher on RQ-G1.** D-G1 is decided in the next round.

---

## Summary

| id | decision (exact) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| Q1 | Linux and Windows low-α entries close under (c) on 05i's runs; macOS stays listed | stands (SURVIVES, file 10) | none convened | 0 | high | NFR-1, NFR-2, L101 | none needed | OVER30S on any 05i run |
| Q2 | K-e12 finding into AX38 4c | stands (SURVIVES) | none | 0 | high | L101, NFR-1/2/6 | none | 07c condition 7 |
| Q3 | R3 stands; F-b extended; F-c withdrawn into G-1 (route D-G1); following strained from 1 instance at 100 m and at the AQ10 room from 4 at 96 kHz (Table 15.1 by extension); artifacts not measured | revised (FOR MAISARA) | none convened | 0 | high (records, code, Table 15.1) | NFR-1/2/3, FR-SIM-6, L101 proviso, L42 | Vorländer §15.3 Table 15.1 | D-G1 leaves G-1 without an owner; post-07c following still multi-second |
| Q4 | did not arise | stands | none | 0 | high | NFR-1 | none | none |
| D-Q5 | `kSolveWarn` 1.20 × in-window solve baseline, PROVISIONAL, print only | stands (SURVIVES) | Seat 5 (0 / 1) | 1 | medium | NFR-1, NFR-2 | none | SOLVE in window on two runs; 07c re-pin |
| D-G1 | G-1's class, owner, timing and instrument (options A, A′, B, D, E; C out) | convening | — | — | — | AX38 (i) (her decision), NFR-3, L101, CLAUDE.md rule 5 | Table 15.1 (yardstick only) | — |

## Challenges to settled decisions

None. G-1 is a conformance defect of the code against AX38 (i), not a challenge to her decision. If D-G1 chooses B, the amendment is written then as `FOR MAISARA` with an AMENDS line.

## Decided for Maisara

- **Q1, Q2, Q4, Q5:** as in file 9; they survived interrogator file 10.
- **Q3 (revised):** the 8-instance 100 m load (16–23 s) stays under her rule R3 (barred from producers, cured in 07c). Following automated movement is late on this build: against AQ4's own yardstick (700 ms for moves > 0.25 m, Vorländer Table 15.1, by extension) it is already late with one instance at 100 m, and at the default-size room from 4 instances at 96 kHz; clicks were not measured. The code holds the build gate longer than her AX38 (i) says (finding G-1), routed as a separate board decision (D-G1), not absorbed. Rests on NFR-3 (L107, sent to the Expert; AQ4 binds), FR-SIM-6, L101's usability proviso (not shown to be met; build barred), NFR-1, D-H1 (v)(d). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv), (i) and 4c record lines.)

**NEEDS MAISARA:** none.
