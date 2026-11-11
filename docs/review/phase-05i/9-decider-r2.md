# 9 — Decider, round 2: rebuttal to interrogator file 6 (Q1–Q5)

Phase 05i, 2026-11-11. Saved verbatim by the orchestrator from the decider's report (the decider reads only).

**Read for this round:** files 5, 6, 7 and 8; file 3 L1–12, L35–69, L171–205, L273–307; phase-05h file 56 L23–57, file 31 L460–470 and file 36 §2–§5; phase-05i §§0–9; BUILD_PLAN AQ4 (L109) and AX38 (L158); PRD L36–165; phase-07c §5 and its sub-phase table; `docs/board/README.md` convening table; `tests/unit/test_diffuse_records.cpp` L55–116, L262–273, L408–549 (from the code); a check, from the code, of who uses the gate (`ScenePipeline.cpp` L118–124 is the only user of `DiffuseSolveGate`) and of `cachedUnitDecays` (set nowhere in `src/` except its declaration and use in `Engine`).

**Corpus:** not present in this checkout (no `docs/corpus/*.md`, no `SOURCE_COMMIT`; `fetch_corpus.sh` fails because the private repository is not attached). No answer below rests on an acoustic or psychoacoustic fact. Table 15.1 and Card et al. appear only as AX38's own labels.

## PRD digest (unchanged from file 5, one line added)

- **For whom, outcome, constraints, culture:** as file 5 (L42, L101, NFR-1, NFR-2, NFR-6, NFR-8; AX38 (i) release rule, 4c with RG-1, (iv) with file 36 R3; phase-05i §1, §7, §8).
- **Added this round:** NFR-3 (L107: automated movement "must render smoothly despite heavy processing. This tension goes to the Expert") and FR-SIM-6 (L89: "Follow automated listener and source movement without audible artifacts"). Q4 (L159) is the Expert's question on NFR-3 and FR-SIM-6; its plan default is AQ4, which binds here. L101 ranks accuracy first and allows high latency, provided the plugin stays usable.

---

## Answers to the interrogator's five rebuttal questions

**1. Q5 baseline: yes, phase-05i §3.3 (v) governs.** "Never a red or out-of-window run as a baseline" applies to the per-OS, per-scene solve mean that k multiplies. Qualifying runs (±5 % flutter window, `kGuardPct = 5.0`, test L89; deviations from file 4 L77): Linux 43007183782 only (−3.7 %); macOS 43007183782 only (+2.4 %); Windows 42964823518 (+0.9 %) and 43007183782 (+1.3 %). The value is a PROVISIONAL print under (v) ("one run PROVISIONAL, printed not asserted"), n = 1 or 2. (iv) takes k "from the spread", which may use all three runs as evidence of spread; (v) bars only the out-of-window runs as the *baseline*. My file 5 value **falls** (P05I-30 accepted); re-decided below (D-Q5).

**2. Q5 convening: Seat 5 was required. UNDERCONVENED accepted.** A new `SOLVE` token on the CI GATE line, and its false-warning rate, is "CI gates" in Seat 5's row. Seat 5 has now been heard (file 8) and its cells are in D-Q5's map. The other eight seats are recorded not required, with reasons, in D-Q5's convening table.

**3. Q3 PRD reading: re-answered below (FOR MAISARA Q3, revised), with NFR-3 and FR-SIM-6 shown for each option.** The listener +0.5 m step in the joint record does **not** reach the output through the R + 2P path. From the code (file 7): every parameter change marks the scene dirty and the builder rebuilds the whole scene; there is no position-only path while a room-size rebuild of the same instance is pending (the position-only tail cache is Phase 10-1). So the listener move's staleness *is* the room-size rebuild's staleness. File 36 R2's "position path 31–90 ms" holds only for an isolated update at the AQ10 room (the AQ4 R + 2P record), not for this condition.

**4. Q1 premise: yes, the closure is read under §3.3 (ii) "on 05i's runs", not under an unconditional (c).** This matches 05h's practice of reading (c) against the latest run (file 31 L467–468), and explains why macOS stays listed: its two 05h passes (27.33 / 29.70 s) were followed by runs over 30 s, and it reads 43.54 s on 05i's run. The register text names the run of record: the PR's CI run, or the run its `ci ok` links if CI skips (CLAUDE.md "When CI skips"). **If the run of record, or any other 05i run of the records test, prints OVER30S for a closing entry, in window or out of it:** that entry does not close ((c) has no window clause, and I add none); it stays listed under the "otherwise" branch, with the run recorded. **The `listed` flag** then goes back to `true` in the next permitted push (the contractor's review round); it is print-only, so no assertion is affected meanwhile. **Corrections:** K2 and the Windows plan text are restated from file 56's table.

**5. Q3 mechanism: not the gate. A new finding F-c, cause not established.** From the code (file 7, spot-checked): the gate is held only around the diffuse solve (≈ 81–91 ms on this run). The ISM, the unit-decay synthesis (FFT up to 2²¹ points) and the IR-set build run outside the gate, one thread per instance, concurrently across instances; no build cache in the plugin path. Record (c)'s ≈ +1.76 s excess (3 572 − 1 812 ms, Linux, one instance) is about one extra rebuild's time, so gate turn-taking (≈ 0.16–0.18 s) cannot produce it; "matches the gate's turn-taking" is struck (P05I-21 accepted). The systematic ≈ 1.5–2.6× host-thread wait is not shown to break AX38 (i) class (1) (that class promises only the gate-wait order, and the excess lies outside the gate on the code's evidence), nor to share F-a's cause (F-a was a worst-of-3 outlier with one contending pipeline). It is named separately: **F-c**, a systematic contended host-thread wait from 4 instances at 100 m / 96 kHz on every OS. Hypothesis: CPU and memory-bandwidth sharing outside the gate (file 7); not established; settled by the split timer in phase-07c condition 9's packet. **If that timer shows waiting at the gate beyond "the one solve already running", F-c becomes a class (1) defect through `/fix-plan`.** Remedy as for F-a and F-b. "R3 stands" does not depend on it (P05I-24).

---

## Q1 — FOR MAISARA Q1 (revised): register exits under §5 (c)

**State:** stands, revised; P05I-03, -06, -07, -08, -09 applied.

**Answer.** "The **Linux** and **Windows** low-α entries leave the register under AX38 4c (c), read through phase-05i §3.3 (ii): 'passes 30 s on 05i's runs'.
- **CI run 43007183782**, 05i's first run, printed 14 × worst 27.61 s (Linux) and 28.74 s (Windows): PASSES30S and in window (flutter −3.7 % / +1.3 %), growth bound asserted and met (1 892 ≤ 2 275, 1 996 ≤ 2 231 ms).
- **The closure is entered once the run of record lands**, if every 05i run of the records test prints PASSES30S for that entry. The run of record is the PR's CI run, or the run its `ci ok` links.
- **If any 05i run prints OVER30S for an entry**, in window or not, that entry stays listed, with the run recorded (the 'otherwise' branch).
- **Closed register text** keeps the recorded value, median, remedy and former closing phase as history, and appends the closure.
- **The closing phase moves to 05i by (c)'s own exit** ('its register text closes'); §4 criterion 3 ('unchanged in substance') is met: the substance fields stay, the rule's own exit changes the state.
- **macOS stays listed:** 43.54 s OVER30S is its recorded state until 07c; median 1 905 < 2 172 ms.
- **Nothing asserted changes.** The low-α scene keeps its hosted-runner form until Phase 13 (strict 30 s only on the release machines; interrogator file 69 item 2). `listed` → `false` for Linux and Windows changes only the print. The runner stays the recorded likely cause of the original listings (AX41, §3.3 (v))."

**Rests on.** AX38 4c (c) with RG-1 (her decision of 2026-11-10, accepted for her); the Linux hand-off "its removal under (c) is phase-05i scope 3's call on 05i's first run"; phase-05i §1 and §3.3 (ii); PRD NFR-1 (W_max untouched), NFR-2 and L101. The PRD is silent on CI register bookkeeping; her recorded decision settles it, so this is not case (a).

**Reasoning.** (1) §3.3 (ii) opens with the leaving branch, so "stay listed" describes its "otherwise" state; reading it as unconditional voids the branch and contradicts §1. (2) "On 05i's runs" is the stability condition, and it agrees with 05h's latest-run reading. (3) Windows falls under the same sentence ("a listed entry"), without needing Linux's hand-off. (4) Closure is print-only (P05I-05). (5) Phase 13 re-checks strictly on the release machines.

**Options.** (A) Both leave on 05i's runs; run of record named (chosen): serves NFR-1 and NFR-2; keeps her (c) operative. (B) Linux only: misreads (c), which covers "a listed entry". (C) Neither: reads "stay listed" over (c); contradicts her rule and §1. (D) Both leave and the strict 30 s is re-armed: barred by (c) and file 69 item 2; a runner-speed red would put pressure on W_max, straining NFR-1 (D-H1 (v)(d)).

**Veto reading.** Windows' values on file outside the slow-runner runs span 19.99–29.51 s, and Linux read 30.18 s in window in 05h, so closing is premature. It holds because the run of record must also pass; closure changes no assertion; an OVER30S on any 05i run keeps the entry listed; after 05i an OVER30S on a closed entry prints a WARNING and is named in the PR (debt row); Phase 13 re-checks strictly.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c register: Linux and Windows entries closed under its own (c); no rule change.)

**K2 restated (file 56 L28–49 and file 3), 14 × worst at the low-α cube:** Linux 29.62 / 30.18 / 24.31 / 41.67 (red, flutter 880 ms) / 27.81 / 25.29 / 24.75 / 27.61 s. Windows 29.04 / 29.50 / 28.57 / 36.73 (slow runner) / 25.57 / 19.99 / 29.51 / 44.83 (flutter +43.6 %) / 28.74 s. macOS 37.37 / 31.23 / 31.71 / 27.33 / 29.70 / 31.82 / 30.27 / 43.54 s. Runs in order: 42909003931, 42924781618, 42935789745, (42942694523, Windows only), 42949252041, 42954077281, 42964823518, 42975074716, 43007183782.

**Text for the plan-editor (Q1).** Apply after the run of record lands; `<ROR>` is its id. Drop an entry's lines if any 05i run printed OVER30S for it.
- **AX38 4c register, Linux entry, append:** "**Closed under (c)** in phase 05i on 05i's runs (CI run 43007183782: in-window, flutter −3.7 %, 14 × worst 27.61 s, median 1 892 ≤ 2 275 ms; run of record `<ROR>`: `<value>` s). CI values on file outside the red run 42949252041 (41.67 s, flutter 880 ms): 24.31–30.18 s. Hosted-runner assertion unchanged until Phase 13."
- **Windows entry, append:** "**Closed under (c)** in phase 05i on 05i's runs (CI run 43007183782: in-window, flutter +1.3 %, 14 × worst 28.74 s, median 1 996 ≤ 2 231 ms; run of record `<ROR>`: `<value>` s). Values on file outside the slow-runner runs 42942694523 (36.73 s) and 42975074716 (44.83 s, flutter +43.6 %): 19.99–29.51 s (19.99 s on the fast runner of 42954077281, flutter 488 ms against 737). The runner stays the recorded likely cause of the listing (AX41). Hosted-runner assertion unchanged until Phase 13."
- **RG-1 paragraph:** "The register entries (Linux 30.27 s, macOS 33.40 s, Windows 36.73 s; remedy phase-07c conditions 9–10; closing phases unchanged) stand." becomes "The macOS entry (33.40 s; remedy phase-07c conditions 9–10; closing phase unchanged) stands. The Linux and Windows entries closed under (c) on phase 05i's runs (43007183782, run of record `<ROR>`). A closed entry that later prints OVER30S is named in the PR; re-listing it is a `/fix-plan` reading under (a)."
- **phase-05i §3.3 (ii), after "stay listed with the remedy phase-07c conditions 9–10":** add "(Linux and Windows closed in 05i under (c) on 05i's runs, AX38 4c)". The same bracket on the phase-05h §5 sentence that lists the three entries, and in §0 rows 05h and 05i.
- **§6 change log row:** "2026-11-11 | 05i | AX38 4c: Linux and Windows low-α register entries closed under (c) on 05i's runs (run of record `<ROR>`); `listed` false, print only | decider files 5/9, interrogator files 6/<next>".
- **`tests/golden/CHANGELOG.md`**, in the form of the RG-1 entry: "`(records-test constants)`: the Linux and Windows low-alpha entries closed under AX38 4c (c), `listed` false, print only (no golden file changed)".

**Test-code change (Q1), `tests/unit/test_diffuse_records.cpp`:** `listed` comment: "in the AX38 4c defect register (plan text); false once closed under (c): print only". The low-α rows: Linux and Windows `listed` false, macOS true; comment "Linux (30.27 s local / file 1) and Windows (36.73 s on CI run 42942694523's slow runner, file 53) closed under AX38 4c (c) on phase 05i's runs (docs/review/phase-05i/9): print only". The 30 s suffix: on a closed entry, "; passes 30 s (register entry closed under AX38 4c (c))" or "; WARNING OVER30S on a closed register entry (printed, not asserted on hosted runners; name the run in the PR)"; on a listed entry, unchanged. The GATE line's `PASSES30S` / `OVER30S` token is unchanged, so the §0 counts keep their meaning.

---

## Q2 — FOR MAISARA Q2: stands, with P05I-14 and P05I-15 applied

The answer stands as in file 5, with two wording changes: "the worst of 10 is above the 2.143 s per-restore budget on every OS; the median is above it on Linux and Windows (2.370 / 2.377 s) and below it on macOS (1.967 s)"; and "the measured worst stays inside AX38 4c's ≈ 4.8 s arithmetic estimate (the K-e6 wait 2 664 ms plus the ≈ 2.14 s build); its [Hyp] tag attaches to pluginval's sequence (≈ 67 s)".

**Text for the plan-editor (Q2), replacing file 5's.** Append to AX38 4c's K-e12 finding: "*Record (phase 05i, CI run 43007183782):* low-α worst / median of 10: 3 276 / 2 370, 2 648 / 1 967, 3 231 / 2 377 ms (Linux / macOS / Windows; idle 1 799 / 1 803 / 1 939 ms). Worst above 2.143 s on every OS and median above it on Linux and Windows: a finding under the register's form. Above 3 s on Linux and Windows: named against the anchors. Inside the ≈ 4.8 s arithmetic estimate. Flutter 793 / 675 / 1 031 ms, within. Remedy unchanged (phase-07c conditions 9–10, re-measured by condition 7)." Add one line to the record against the anchors citing the same.

AMENDS line as in file 5.

---

## Q3 — FOR MAISARA Q3 (revised): Raise item 2 on 05i's records, with NFR-3 / FR-SIM-6

**State:** revised; P05I-25 answered; P05I-18, -19, -21, -23 applied.

**Answer.** "It stands. The records are appended, F-b is extended, and a new finding F-c is named. **NFR-3 and FR-SIM-6 are strained on this build**: at its heaviest multi-instance records, following is late, though nothing is reported to click. The strain is recorded with its owners, and nothing here relieves it now.

**The load,** 8 instances at the 100 m low-α cube, 96 kHz: 19.5 / 16.3 / 23.0 s (Linux / macOS / Windows): above 10 s, and at or below 05h's figures (AX38 (iv) recorded 20.4–25.6 s; 05h values on file 16.5–25.6 s); 7.9× / 7.5× / 9.3× the single-instance load. Windows' excess over 8× lies in instances 5–8 (restore 2.42–2.67 s against 1.93–2.04 s) and 6–8 (prepare 679 / 697 / 687 ms against 554–578 ms); cause not established. At 48 kHz: 8.3 / 8.4 / 9.9 s.

**F-b extended** (about linear in instance count): staleness when automated together at 8 × 100 m / 96 kHz, room-size step up to 16.3 / 14.6 / 16.4 s; joint step (room size and listener +0.5 m) up to 15.7 / 14.4 / 15.1 s (the listener move waits for the full rebuild: the position-only path is Phase 10-1, file 7). Staleness of real-time instances while another instance renders offline: up to 29.4 / 27.9 / 31.8 s, about 1.9–2.1× the joint staleness, about one extra rebuild's time; mechanism not established (hypothesis: CPU sharing outside the gate, file 7). The offline wait is about linear in M (7.6–7.8× at M = 8), under F20: offline has no deadline and its output is identical.

**F-c, named:** the contended synchronous host-call wait (prepare, restore, offline switch) is 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS, 1.5–2.6× the single-instance wait; ≤ 2.3 s at 48 kHz; < 1 s at the AQ10 room. Not shown to share F-a's cause; not shown to break AX38 (i) class (1) (the gate covers only the ≈ 81–91 ms solve). Settled by the split timer in phase-07c condition 9's packet; if that timer shows waiting at the gate beyond 'the one solve already running', F-c is a class (1) defect through `/fix-plan`.

**Remedy, unchanged:** phase-07c conditions 9 (or 07d) and 10; staleness shown as AX38 (iii) 'settling'; condition 7 re-measures with time-to-audible and time-to-settle; Phase 10's IR-staleness metric and position path (AQ4: 'the late tail is cached when only positions change'; AX38 (v)); phase-13 Raise item 3 applies the 10 s line to the release build.

**Never:** a W_max cut, a range change, a seam or an instance cap. No figure in the compatibility notes (Phase 13, with Seat 7). The build never reaches a producer (AX38 (i) release rule)."

**PRD ids and decisions.** L101; L49; NFR-1; NFR-2; **NFR-3 (L107), FR-SIM-6 (L89), Q4 (L159) with its plan default AQ4**; NFR-6; L42, FR-3D-6 and FR-SIM-7; L55; AX38 (i), (iii), (iv), (v) and 4c with file 36 R2/R3 (accepted for her 2026-11-10).

**Reasoning.** (1) NFR-3 and FR-SIM-6 are strained: a listener or room step at 8 × 100 m / 96 kHz is followed 14–16 s late (≈ 30 s during an offline render). The old IR keeps playing and each switch is AQ4's 30 ms crossfade, so the strain is in *following*, not in artifacts. (2) The PRD ranks the tension: L101 puts accuracy first and accepts high latency while the session stays usable; NFR-3 itself sends "this tension" to the Expert, whose plan default is AQ4, with Phase 10 and 07c as owners. So this is not case (a). (3) R3's rule depends on the load's class (above 10 s, barred from producers, cured at the cause in 07c); 05i's figures leave that class unchanged. (4) The new classes are the same build cost seen through other records. (5) No option that relieves NFR-3 now survives the PRD's ranking.

**Options.** (A) R3 stands; records appended; F-b extended; F-c named; NFR-3 / FR-SIM-6 strain recorded with its owners (chosen): serves NFR-1, NFR-2 / L101 and NFR-6; FR-SIM-6 "without audible artifacts" is served by AQ4's crossfade, its "follow" is strained on this build; NFR-3 is strained at the 8 × 100 m records, repaid through 07c conditions 9–10 / 7, AX38 (iii) and Phase 10, never shipped meanwhile. (B) A fresh answer, or NEEDS MAISARA: outside the three cases (L101 ranks accuracy first; NFR-3 routes its tension to the Expert, AQ4); serves no PRD id better than (A). (C) Cap instances or W_max to shorten staleness: serves NFR-3 / FR-SIM-6 (following); strains NFR-1, which L101 ranks top, and L42 / FR-SIM-7 / FR-3D-6; barred by D-H1 (v)(d). (D, mine) Pull the Phase 10-1 position path or 07c's moves into 05i: would serve NFR-3 for listener-only moves (not room-size steps); breaks the one-phase rule (CLAUDE.md) and phase-05i §8 ("the engine" is out of scope); out by bounds.

**Veto reading.** NFR-3 says movement "must render smoothly despite heavy processing", and a 15–30 s lag is not smooth, so a staleness bound should be set before more phases build on this path. It holds because setting that bound is the Expert's (Q4 / AQ4) and Phase 10's (the AX38 (iii) staleness metric); the build is barred from producers until 07c's remedy; 07c condition 7 and Phase 13 item 3 re-measure on the cured build. It would fall if 07c condition 7's record still showed multi-second following at the shipping build with no Phase 10 owner (the reversal condition).

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv) and 4c: 05i record lines appended; F-c named; NFR-3 / FR-SIM-6 strain recorded; no rule change.)

**Convening.** No seat convened: a reading of her recorded rules against records; no option on the table creates a control, a range or a new design (P05I-26: faithful by precedent). Seat 6 keeps the "settling" hand-off (Phase 11). Seats 5 and 3 meet F-c at 07c condition 9's split timer.

**Text for the plan-editor (Q3, AX38 (iv), after the 2026-11-10 record).** "*Record (phase 05i, CI run 43007183782):* 8 × 100 m low-α / 96 kHz load 19.5 / 16.3 / 23.0 s (7.9× / 7.5× / 9.3× the single load; at or below 05h's figures); Windows' excess in restore (instances 5–8) and prepare (6–8), cause not established; 48 kHz 8.3 / 8.4 / 9.9 s; R3 stands. F-b extended: staleness when automated together up to 16.4 s (room size) and 15.7 s (joint; the listener move waits for the full rebuild until Phase 10-1's position path); during another instance's offline render up to 29.4 / 27.9 / 31.8 s (≈ 1.9–2.1× the joint staleness, about one extra rebuild; mechanism not established, hypothesis CPU sharing outside the gate); offline wait ≈ linear in M (F20). PRD NFR-3 / FR-SIM-6 strained on this build in following, not artifacts (AQ4 crossfade); owners: phase-07c conditions 9–10 and 7, AX38 (iii), Phase 10. Remedy unchanged."

**AX38 4c, after F-b in the record against the anchors:** "(F-c, phase 05i, CI run 43007183782) contended synchronous host-call waits (prepare, restore, offline switch) 3.6–5.0 s from 4 instances at 100 m / 96 kHz on every OS (1.5–2.6× the single-instance wait; ≤ 2.3 s at 48 kHz; < 1 s at the AQ10 room). Not shown to share F-a's cause or to break (i) class (1): the gate is held only around the ≈ 81–91 ms solve. Settled by phase-07c condition 9's split timer; a wait at the gate beyond the one running solve is a class (1) defect through `/fix-plan`. Remedy as F-a / F-b."

---

## Q4 — stands (SURVIVES). No change.

---

## Q5 — DECISION D-Q5: the solve-median bound

**Restatement.** Picks the factor k and the baseline for a print-only `SOLVE` WARNING on the RG-1 GATE lines (phase-05i §3.3 (iv); form settled, P05I-28). Depends on it: the `test_diffuse_records.cpp` GATE block, §0 counts, PR naming of WARNING runs. Options: A k = 1.20 on the in-window baseline, PROVISIONAL; B k = 1.30, same baseline; C k = 1.15, same baseline; D no token until 07c, values printed only; E k = 1.20 on the 3-run mean (file 5).

**Convening table**

| seat | status | reason / brief |
|---|---|---|
| 1 | not required | No audibility or realism claim; a CI print about solve time. |
| 2 | not required | The response, the work and the pins are unchanged (W_pilot / W_final asserted, test L379–380). Seat 5's hand-off on `nsPerEval` across 07c goes to 07c's re-pin (debt row). |
| 3 | not required | No per-instance CPU budget is set; the token measures, it chooses no cost. The same hand-off applies. |
| 4 | not required | No delivery matter. |
| **5** | **convened (file 8)** | CI gates: a new WARNING token and its false-warning rate (P05I-37). |
| 6 | not required | No control, range or default. |
| 7 | not required | No public wording or release rule; a CI print in PR text is not a cadence or cost choice. |
| 8 | not required | No producer workflow. |
| 9 | not required | No room, material or preset. |

**Knowledge inventory (D-Q5)**

| K | what | source | status |
|---|---|---|---|
| K9′ | per-run solve medians and flutter deviations | file 4 L71–77 | known |
| K15 | in-window rule ±5 %; (v) bars out-of-window baselines; (iv) k from the ≥ 3-run spread | test L89 (from the code); phase-05i §3.3 (iv)–(v) | known |
| K16 | in-window baselines: Linux 80.9 / 131.2; macOS 83.7 / 102.7; Windows (90.2 + 90.6)/2 = 90.40, (143.8 + 145.0)/2 = 144.40 ms | K9′, K15; agrees with P05I-30 and file 8 | known |
| K17 | nothing parses the GATE lines (only the test prints them) | grep outside `docs/` (from the code) | known |
| K18 | the solve timing is `estimateDiffuse` alone on the planned problem; `nsPerEval` = median / (W_pilot + W_final) | test L408–424 (from the code) | known |
| K19 | false-warning rates are t(2) predictive, assuming normal per-run noise | Seat 5 file 8 §3 [Hyp]; arithmetic re-done below | under-informed (distribution); not load-bearing for the choice |

**Tension map (Seat 5 word for word, file 8; the other eight 0 / 0, reasons above)**

| option | Seat 5 now / later | reason (now; later) |
|---|---|---|
| A 1.20, in-window | 0 / 1 | "0 of the 18 cell-runs on file are over … macOS flutter … about 1 warning in 10 runs"; "A one-run baseline (two runs on Windows) holds until the 07c re-pin … erring towards missing a regression rather than warning falsely" |
| B 1.30, in-window | 0 / 1 | "macOS flutter t = 2.56, P ≈ 0.06 (1 in 16)"; "Same debt as A; weaker on x64 if 07c's synthesis move shifts the solve" |
| C 1.15, in-window | 1 / 1 | "a reader of the GATE line can mistake a print for a (d) trigger"; "Same debt as A, plus a recurring PR line on macOS at about 1 in 7" |
| D no token | 1 / 1 | "Leaves §3.3 (iv) undone, which needs a `/fix-plan` amendment"; "each PR's §0 count has no SOLVE column until then" |
| E 1.20, 3-run mean | 2 / 2 | "Its baseline includes runs that §3.3 (v) bars"; "The creeping-baseline pattern" |

**Minimum-tension working.** (1) Bounds: E breaks phase-05i §3.3 (v) (P05I-30) and is dropped; A–D inside. (2) Veto-grade exclusion: no 3. (3) Worst-off seat: A 1, B 1, C 1, D 1, tie. (4) Compose: no 2s remain; Seat 5's conditions for A adopted as A's form. (5) Sum: A 1, B 1, C 2, D 2; A and B tie. (6) Reversibility: A and B equal (a constant plus a CHANGELOG line, overturned at the 07c re-pin). (7) Decide: the ordering does not separate A from B; A on Seat 5's own ranking ("Prefer" A; B "can live with"), without re-rating it; B's later reason states an extra weakness ("weaker on x64"); A catches a regression of +20 % rather than +30 %.

**DECISION D-Q5.** A per-scene `SOLVE` token is printed in that scene's `warnings=` field when the run's solve median exceeds **`kSolveWarn` = 1.20** × that scene's **in-window solve baseline** for the OS. Baselines (low-α / flutter, ms): Linux 80.9 / 131.2 (run 43007183782; n = 1); macOS 83.7 / 102.7 (43007183782; n = 1); Windows 90.4 / 144.4 (42964823518, 43007183782; n = 2). All **PROVISIONAL**. Thresholds: 97.1 / 157.4, 100.4 / 123.2, 108.5 / 173.3 ms. Rules: one-sided; never asserted on hosted runners; never part of (d); never a trigger; counted in §0 apart from the in-window / out-of-window status; printed regardless of the flutter window (the deviation does not predict solve time, P05I-35: no runner attribution, no NOT EVALUATED). **Calibration rule:** one cell printing SOLVE in window on two runs, with `nsPerEval`'s work and the pins unchanged, is an instrument-calibration finding, not a defect. k and the baselines are re-derived from ≥ 3 in-window runs at the 07c re-pin, and re-pinned whenever W_max or the work changes (07c-2). Seat 5's hand-off on the flutter line's `warnings=` field: it **is inside this slot** (scope 3 (i) carries "the GATE lines of every run" and (iv) the bound; nothing parses the lines, K17, so the field is additive).

**Load-bearing claims.** D5-L1 (plan text): (v) bars out-of-window baselines; (iv) takes k from the spread of ≥ 3 runs (phase-05i §3.3 (iv)–(v)). D5-L2 (from the code plus file 4): in-window membership from `kGuardPct` = 5 and the file 4 L77 deviations. D5-L3 (derived): × 1.20 gives 97.08, 157.44, 100.44, 123.24, 108.48 and 173.28 ms. D5-L4 (derived): 0 of the 18 cell-runs over; largest observed / baseline 149.6 / 144.40 = 1.036; largest max / mean over the three runs 1.086 (P05I-31). D5-L5 (Seat 5's own cost): macOS flutter predictive rate with σ estimated t(2) = (123.2 − 96.77) / (12.41 × √(4/3)) = 26.43 / 14.33 = 1.84, P = ½(1 − 1.84/√(1.84² + 2)) = ½(1 − 0.793) ≈ 0.10; with σ known z = 26.43 / 12.41 = 2.13, P ≈ 0.017; both rest on [Hyp] normal noise; not load-bearing for A over B. D5-L6 (product): print, not gate (AX38 4c's RG-1 form; PRD NFR-1, NFR-2).

**Future-debt register (D-Q5)**

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 5 (later 1) | a one-run baseline (two on Windows) until the 07c re-pin; macOS flutter's in-window run is the high draw (102.7 vs 82.5), so the threshold is effectively ≈ 1.27 × the 3-run mean and errs towards missing a regression | a constant plus a CHANGELOG line | every 05i / 06 / 07 PR's GATE lines | 07c re-pin from ≥ 3 in-window runs |
| 5 (hand-off to 2 / 3) | whether `nsPerEval` stays invariant across 07c's moves; from the code the timing is `estimateDiffuse` alone (K18), so the synthesis move should not shift it, but 07c-2's W_max raise changes the work | a re-pin | 07c-1 / 07c-2 CI runs | 07c-2: baselines re-pinned with the new work, k re-derived; Seats 2 / 3 convened there if `nsPerEval` moves |

**Strongest objection.** Seat 5's later 1: on macOS flutter, a high-draw one-run baseline can hide a +20–27 % solve regression until 07c. It holds because the work pins (W_pilot / W_final, FFT n) are asserted exactly, so extra or skipped work cannot hide; the restore-side GROWTH and RATIO prints sit beside it; 07c re-derives from ≥ 3 in-window runs. It would not hold if a 07c-bound change altered the solve without moving the pins; 07c's re-pin is where that shows.

**Confidence:** medium (n = 1–2 per baseline; rate depends on [Hyp] normality). **Reversal:** a cell printing SOLVE in window on two runs with the work unchanged (a calibration finding: re-derive), or the 07c re-pin's ≥ 3 in-window runs.

**Decided for Maisara (PRD check).** No hard constraint is broken: no assertion, no W_max change (NFR-1); a print only (NFR-2); RG-1 form kept. A: serves NFR-1 and NFR-2. B: serves both equally. C: serves both; the print can be confused with a trigger (no PRD id). D: serves both; leaves her RG-1 slot unfilled. No PRD goal points from A to another option. No AMENDS: this fills the slot AX38 4c opens ("a bound proposed through `/fix-plan` once ≥ 3 runs give its spread").

**Text for the plan-editor (D-Q5).**
- **AX38 4c, RG-1 paragraph:** replace "(a bound proposed through `/fix-plan` once ≥ 3 runs give its spread)" with: "(bound, phase 05i, decider file 9 / Seat 5 file 8: `SOLVE` printed in the scene's `warnings=` when the run's solve median exceeds `kSolveWarn` = 1.20 × the scene's in-window solve baseline per OS. Baselines, low-α / flutter: Linux 80.9 / 131.2 ms and macOS 83.7 / 102.7 ms (run 43007183782); Windows 90.4 / 144.4 ms (runs 42964823518, 43007183782). PROVISIONAL, n = 1–2. k from the spread of the three RG-1-form runs (largest max / mean 1.086). One-sided. Never asserted; never a (d) trigger; counted in §0 apart from the in-window status; printed whatever the flutter window. A cell printing SOLVE in window on two runs with `nsPerEval`'s work and the pins unchanged is an instrument-calibration finding, not a defect. k and the baselines are re-derived from ≥ 3 in-window runs at the 07c re-pin, and re-pinned when the work changes (07c-2))".
- **phase-05h §5, the "Printed with WARNING" list:** the same parenthesis, shortened to "(bound: AX38 4c, set in phase 05i)".
- **phase-05i §3.3 (iv):** append "(set in 05i: AX38 4c, decider file 9)".
- **§0 row 05i:** a SOLVE count per OS beside the asserted / not evaluated / WARNING counts.
- **§6 change log row:** "2026-11-11 | 05i | AX38 4c solve-median bound: `kSolveWarn` 1.20 × in-window baseline, PROVISIONAL (n = 1–2), print only | decider file 9, Seat 5 file 8, interrogator <next>".
- **`tests/golden/CHANGELOG.md`**, in the RG-1 entry's form: "`(records-test constants)`: solve-median baselines (in-window runs 42964823518 Windows, 43007183782 all OSes) and `kSolveWarn` 1.20, PROVISIONAL (no golden file changed)".

**Test-code change (D-Q5), `tests/unit/test_diffuse_records.cpp`:** `GateEntry` gains `double solveRefMs` (the scene's solve-median baseline, the mean of the in-window runs only) and `int solveRefRuns` (below 3 the bound prints PROVISIONAL); `constexpr double kSolveWarn = 1.20` after `kRatioWarn`, kept apart from it; flutter rows `131.2, 1` / `102.7, 1` / `144.4, 2`; low-α rows `80.9, 1` / `83.7, 1` / `90.4, 2`; both GATE lines print `solveWarnAt=%.1f solveBasis=%s(n=%d)`; the flutter line gains a trailing `warnings=%s` (`SOLVE ` or empty); the low-α line adds `SOLVE ` to its `warnings` when exceeded. No new REQUIRE on any timing (only the structural `REQUIRE(flEntry != nullptr)`).

---

## Corrections from file 6: disposition

| id | disposition |
|---|---|
| P05I-03, -07, -08 | applied: Q1 basis is §3.3 (ii) "on 05i's runs"; run of record named; OVER30S on any 05i run keeps the entry listed |
| P05I-06 | applied: K2 and the Windows text from file 56 (19.99–29.51 s) |
| P05I-09 | applied: the closing phase moves to 05i by (c)'s own exit |
| P05I-14, -15 | applied (Q2) |
| P05I-18, -19, -23 | applied (Q3) |
| P05I-21 | applied: struck; "about one extra rebuild; mechanism not established" |
| P05I-24 | answered: F-c named, not F-a; R3 does not depend on it |
| P05I-25 | answered: Q3 re-answered with NFR-3 / FR-SIM-6 for each option |
| P05I-30 | accepted: file 5's value falls; D-Q5 uses the in-window baseline |
| P05I-33, -34 | superseded: D-Q5's rates are Seat 5's, on the new thresholds (≈ 1 in 10; CV ≤ 2.1 %) |
| P05I-35 | applied: the attribution is struck; SOLVE prints whatever the window |
| P05I-37 | accepted: Seat 5 convened (file 8) |

## Future-debt register (all items)

| item | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| Q1 | the closure depends on the run of record; after 05i a closed entry has no re-entry rule (OVER30S is printed, named in the PR, re-listing is a `/fix-plan` reading) | a register line; `listed` back to true | the run of record; later PRs | Phase 13 strict re-check |
| Q2 / Q3 | K-e12, F-a, F-b and F-c hang on 07c conditions 9–10 (P1 open, file 36); the NFR-3 / FR-SIM-6 strain on following waits on 07c condition 7, AX38 (iii) and Phase 10's staleness metric and position path | nothing (records) | 07c condition 7; condition 9's split timer (F-c's cause); Phase 10 | 07c `done`; Phase 10; Phase 13 item 3 |
| D-Q5 | see D-Q5's register | a constant | GATE lines; 07c re-pin | 07c re-pin / 07c-2 |

**Strongest objection overall.** Q3's NFR-3 strain: 15–30 s following at 8 × 100 m / 96 kHz is recorded but not relieved. It holds under L101 and NFR-3's routing to the Expert; it falls if the post-07c record still shows multi-second following with no Phase 10 owner.

## Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| Q1 | Linux and Windows low-α entries close under (c) on 05i's runs (43007183782 plus the run of record); macOS listed; `listed` false (print only) | stands (revised) | none convened | 0 | high | NFR-1, NFR-2, L101 | none needed | OVER30S on any 05i run: that entry stays listed |
| Q2 | Item 1 not re-opened; K-e12 finding written into AX38 4c (worst above 2.143 s on every OS, median on Linux and Windows) | stands (corrected) | none | 0 | high | L101, NFR-1/2/6 | none | 07c condition 7 |
| Q3 | R3 stands; F-b extended; F-c named; NFR-3 / FR-SIM-6 strain recorded with owners | revised (FOR MAISARA) | none | 0 | high (records); medium (F-c cause) | L101, NFR-1/2/3/6, FR-SIM-6, L42 | none | split timer shows a gate wait (F-c to class (1) defect); post-07c following still multi-second |
| Q4 | Did not arise | stands | none | 0 | high | NFR-1 | none | none |
| Q5 | `kSolveWarn` 1.20 × in-window solve baseline (L 80.9/131.2, M 83.7/102.7, W 90.4/144.4 ms), PROVISIONAL, print only | proposed (DECISION) | Seat 5 (0 / 1) | 1 | medium | NFR-1, NFR-2 | none | SOLVE in window on two runs with work unchanged; 07c re-pin |

## Challenges to settled decisions

None. One clarification: file 36 R2's "the position path is 31–90 ms" holds for an isolated update at the AQ10 room, not for a listener move during a room rebuild of the same instance (file 7). Q3's plan text says so.

## Decided for Maisara

- **Q1:** the Linux and Windows restore-gate register entries close under their own rule, because both passed 30 s on 05i's runs; the closure is confirmed by the PR's run of record; macOS stays listed; no test assertion changes (NFR-1, NFR-2, L101). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c register.)
- **Q2:** a restore arriving mid-edit at the heaviest room waits up to 3.3 s; recorded as a finding, with the fix scheduled in 07c; Raise item 1 not re-opened (L101, NFR-1/2/6). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c.)
- **Q3:** the 8-instance 100 m load (16–23 s) and the new multi-instance records fall under the named findings, plus one new finding (F-c). Following automated movement is late on this heavy build (15–30 s at 8 × 100 m / 96 kHz), straining NFR-3 / FR-SIM-6; recorded. The PRD ranks accuracy first (L101) and gives this tension to the Expert (NFR-3, AQ4), so nothing is cut; the build cannot reach producers; 07c and Phase 10 re-measure. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 (iv) and 4c record lines.)
- **Q4:** the larger-machine action was not needed (NFR-1).
- **Q5:** the solve-time warning prints at 1.20 × the in-window baseline; provisional, never a CI failure, re-derived at 07c (NFR-1, NFR-2). No AMENDS.

**NEEDS MAISARA:** none.
