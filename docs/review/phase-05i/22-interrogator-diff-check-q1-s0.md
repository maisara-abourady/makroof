# 22 — Interrogator: diff check of the Q1 outcome (file 20) and the §0 rows 05h / 05i (file 21), /fix-plan step 5

Phase 05i, 2026-11-11. Document mode, limited to the passages the two plan-editor reports name, plus the later §0 wording change ("the six Linux jobs that failed at their dependency install in an Azure apt-mirror DNS outage green on attempt 4"). **Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d**. Saved verbatim by the orchestrator (the interrogator reads only).

**Checked against:** Q1: decider file 9, answer 4, "Q1 — FOR MAISARA Q1 (revised)", "Text for the plan-editor (Q1)" and its drop rule ("Drop an entry's lines if any 05i run printed OVER30S for it"). The two 05i runs of the records test: file 3 (run 43007183782, GATE lines L8–9, L206–207, L360–361; K-e12 L81, L231, L349) and file 19 (run of record 43031773338, GATE lines L97–98, L464–465, L606–607; restore-gate lines L88, L455, L597; K-e12 L122, L477, L619; agreement summaries L34, L272, L544). The §0 rows: files 1, 2 and 13. A grep of `docs/review/phase-05i/` finds no third 05i run id, so "05i's runs" means these two runs. Text read in the working tree (`docs/BUILD_PLAN.md` L27–28, L158, L504; `docs/phases/phase-05i.md` L91–97; `docs/phases/phase-05h.md` L384–387); no shell, so the diff itself was not seen. Corpus: none of these passages makes an acoustic or psychoacoustic claim (CI records and register bookkeeping), checked for fidelity to their sources.

## Outcome

| edit | passages | verdict |
|---|---|---|
| (a) Q1 | AX38 4c Linux entry; Windows entry; RG-1 sentence; phase-05i §3.3 (ii) bracket; phase-05h §5 bracket; §6 row | faithful; the drop rule applied correctly (Windows printed OVER30S on the run of record, so its closing lines were dropped); one IMPRECISE wording in the Windows record (P05I-114) |
| (b) §0 | row 05i; row 05h's appended sentence | faithful in every number; three minor IMPRECISE items: P05I-122 (where a statement comes from), P05I-125 (the unit of the warnings count), P05I-126 (SOLVE on the first run) |

**No WRONG passage. Both edits may stand.**

## Ledger

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| P05I-113 | NUMBER | AX38 4c Linux entry "**Closed under (c)** … (CI run 43007183782: in-window, flutter −3.7 %, 14 × worst 27.61 s, median 1 892 ≤ 2 275 ms; run of record 43031773338: 27.40 s). CI values on file outside the red run 42949252041 (41.67 s, flutter 880 ms): 24.31–30.18 s …" | faithful (verbatim, file 9 Q1; `<ROR>` = 43031773338, `<value>` = 27.40) | File 3 L9: 27.61, median 1892, growthBound 2275; L8 −3.7 %. File 19 L87, L98: 27.40 s PASSES30S (not evaluated, flutter −13.0 %; (c) has no window clause, file 9 answer 4). K2 (file 9 L53) without 41.67: 24.31–30.18. Both 05i runs passed 30 s | none | closed |
| P05I-114 | NUMBER / DECISION text | AX38 4c Windows entry "*Phase 05i:* … stays listed under (c)'s 'otherwise' branch …" | every number faithful; IMPRECISE in one attribution | File 3 L361 (28.74, PASSES30S), L360 (+1.3 %); file 19 L607 (46.63, not-evaluated, GROWTH OVER30S), L597 (code printed "closed"); the flag return matches file 9 answer 4. AX38 4c (c) has no "otherwise" branch; the branch is phase-05i §3.3 (ii)'s ("otherwise it stays listed and the run is recorded", L94–95) | minor | **applied**: "under phase-05i §3.3 (ii)'s 'otherwise' branch" |
| P05I-115 | DECISION text | Windows "Closed under (c)" text from file 9 not applied | faithful to the drop rule | File 9 L37 and answer 4: OVER30S on any 05i run, "in window or out of it", keeps the entry listed; file 19 L607 | none | closed |
| P05I-116 | DECISION text | RG-1 sentence: macOS and Windows entries stand; Linux closed on 05i's runs; OVER30S/re-listing sentence | faithful | File 9's RG-1 text with Windows moved to the standing list by the drop rule; 33.40 / 36.73 s are the recorded register values | none | closed |
| P05I-117 | DECISION text | phase-05i §3.3 (ii) bracket | faithful | File 9's bracket with Windows dropped by the rule | none | closed |
| P05I-118 | DECISION text | phase-05h §5 bracket before "stand" | faithful | Placed where file 9 says | none | closed |
| P05I-119 | DECISION text | §6 row (L504) | faithful | File 9's row with the drop applied; `<next>` filled as file 10 | none | closed |
| P05I-120 | SOFTWARE | The `tests/golden/CHANGELOG.md` line and the Windows `listed` flag back to true in `test_diffuse_records.cpp` | correctly not applied by the plan-editor; still owed | File 19 L9, L597: the code on the run of record prints Windows as "register entry closed" while the plan lists it, until the contractor's review push | minor | open (named in the PR as a review-push item) |
| P05I-121 | SOFTWARE record | §0 row 05i, CI sentence | faithful | File 19 L3 (six Linux jobs failed resolving azure.archive.ubuntu.com before any build; attempts 2–3 the same; attempt 4 green on every job; nightly green); file 3 L3 | none | closed |
| P05I-122 | NUMBER / record | §0 05i Scope 1 incl. "recipe checks bit-identical, lean and chunked … (file 2)" | every number faithful; source of "chunked" IMPRECISE | File 2 L18–20, L29, L38–45, L50–51, L33, L26; file 19 L17–34, L272, L544. File 2 records only the lean check; the chunked CR4 1.25 m check (worst_rel_diff 0.0) is in file 18 L33 (and the provenance file) | minor | **applied**: "(file 2; the chunked recipe check in the provenance file and file 18)" |
| P05I-123 | NUMBER | §0 05i K-e12 worsts | faithful | File 3 L81, L231, L349: 3 276 / 2 648 / 3 231 ms; file 19 L122, L477, L619: 3 067 / 3 241 / 5 113 ms | none | closed |
| P05I-124 | NUMBER | §0 05i counts on 43007183782: 5 / 0 / 1, warnings 3 | faithful (recomputed) | flutter asserted on three OSes; low-α asserted on Linux and Windows, reported-only on macOS; tokens PASSES30S, OVER30S, PASSES30S | none | closed |
| P05I-125 | NUMBER | §0 05i counts on 43031773338: 3 / 2 / 1, "warnings 3" | 3 / 2 / 1 faithful; "warnings 3" IMPRECISE in its unit | File 19 L98, L465, L607: four tokens in three cells; row 05h used tokens for one run and cells for another | minor | **applied**: "warning tokens 3" (43007183782) and "warning tokens 4 in 3 cells" (43031773338) |
| P05I-126 | NUMBER | §0 05i "SOLVE 0 of 6 on both runs" | correct for the run of record; IMPRECISE for 43007183782 | Run of record: all six solve medians below their thresholds; on 43007183782 the GATE lines carry no SOLVE field (the bound did not exist) and its values are the baselines, so 0 of 6 holds by construction | minor | **applied**: "SOLVE 0 of 6 on the run of record (… the bound did not exist on 43007183782, whose values are its baselines)" |
| P05I-127 | NUMBER | §0 05i register outcome (27.61 / 27.40 s; Windows 46.63 s; flag back to true in the review push) | faithful | As P05I-113…115; macOS 43.54 s (file 3 L207) and 33.45 s (file 19 L465), both OVER30S | none | closed |
| P05I-128 | record | §0 05i Scope 5 | faithful | File 1 L27–30 | none | closed |
| P05I-129 | DECISION text | §0 05i Board sentence | faithful | File 13 L74–76, L130, L173; file 9 summary | none | closed |
| P05I-130 | record | §0 05i listening note | faithful | File 2 L54–56 | none | closed |
| P05I-131 | record | §0 row 05h appended sentence | faithful | File 2 L29; P05I-113; file 13 L74–75; silent on Windows and macOS, not a contradiction | none | closed |

## Questions (answered by the orchestrator, no decision)

1. (P05I-114) The branch is phase-05i §3.3 (ii)'s; the register record now says so.
2. (P05I-120) Yes: the PR names the mismatch under "Golden and assumption changes" and "Contractor review focus"; the Windows `listed` flag returns to true, with a CHANGELOG line, in the contractor's review push (file 9 answer 4).
3. (P05I-122) Cited: "the chunked recipe check in the provenance file and file 18".
4. (P05I-125) Unit stated as warning tokens per run (with the cell count where they differ).
5. (P05I-126) A count recomputed against the bound on the run of record only; restated.
