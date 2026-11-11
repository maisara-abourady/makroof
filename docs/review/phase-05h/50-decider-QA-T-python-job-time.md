# 50 — Decider: P05H-QA-T, the AX37 (5.4) board-return trigger (python-job time): option (f), an own three-OS CI job

phase-05h (session 2). Verbatim decider output (the orchestrator saved it). Seat 5 file 49; question file 47.

## Decider — P05H-QA-T (the AX37 (5.4) board-return trigger: python-job time)

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (14 files). No acoustic fact is load-bearing for the chosen option.

**PRD digest.** For whom: producers/DJs on macOS+Windows who will not learn acoustics. Outcome: a scene rendered at the highest achievable accuracy (NFR-1 top-ranked; "Accuracy first", key decisions). Hard constraints here: NFR-1 (thresholds from the Expert: τ is her accepted number, ledger P05B2-M-01); AX37 (5.4) as amended (τ alone, 3·SE ≤ τ per band, "both s values, both emitters", "in PR CI on three OSes"); AX42; NFR-8 (no scene-specific tuning: a finding is reported, never loosened); AX5 determinism; CLAUDE.md one-phase rule and CI-job rules (`needs: changes`, the `if:` gate, `ci-ok` needs; `test_ci_workflow.py` L47–56 enforce them). Her recorded decision touched: AX37, accepted 2026-11-10 ("I accept the board's answer by definition."). Verification culture: every DSP behaviour automatically checked against an independent reference (here `ground_scatter.window_target`), goldens never loosened to pass. Priorities enter through Seat 5 (CI budget) and Seat 1/NFR-1 (no loss of the check).

### Matter and options
Where the two 2^23 `open_field` renders (test_tail.py L204–250) run so that the check stays at τ, both s, both emitters, on three OSes, inside Seat 5's CI budget. Options (file 47 + Seat 5): (a) keep in the python job; (a′) composed: (a) + `timeout-minutes` 45 + `--durations=10`; (b) s 0.4 only at 2^23; (c) (b) + s 0.5 nightly; (d) concurrent renders; (e) not available; (f) own three-OS job (Seat 5's).

### Convening table
| Seat | | Reason |
|---|---|---|
| 1 | not required | nothing audible changes; τ, the form and the reference are untouched |
| 2 | not required | its matter (s-independence of the ratio, Kuttruff Eq. 4.24, file 43) is load-bearing only for (b)/(c), which are not chosen |
| 3 | not required | no rendering change |
| 4 | not required | no delivery change |
| 5 | **convened** | "CI gates"; answered, file 49 |
| 6 | not required | no user control |
| 7 | not required | no money cost: public repository, runner minutes unbilled (file 47, GitHub API 2026-11-11); schedule cost ≈ 1 h inside this session (Seat 5 §3), no founder-capacity question |
| 8 | not required | no workflow change |
| 9 | not required | as Seat 2 |

### Knowledge inventory
K1 | pair cost per OS 12.9/7.9/8.8 min; python job 22.1/16.6/16.6 | file 47 table (CI logs) | known
K2 | python job has no `timeout-minutes` | from the code, ci.yml L113–209 | known
K3 | `ci ok` wall clock 43.1 min set by `build (windows)` 42.9; `build (linux)` 27.3; python 22.1; tail-gates max 14.0 | file 47 (jobs API) | known
K4 | runners unbilled (public repo) | file 47 | known
K5 | new-job rules | from the code, test_ci_workflow.py L47–56, CLAUDE.md | known
K6 | markers registered per sub-package | conftest.py L17–27 | known
K7 | AX37 (5.4) wording incl. trigger sentence | BUILD_PLAN L138 | known
K8 | new job's duration bound: pair 12.9 + set-up < 14.0 (a tail-gates job including its renders) < 27 min < 27.3 `build (linux)` | derived from K1, K3 | known
K9 | s-independence of the ratio | file 43 (CORRECT, derived) | known, not used by (f)

### Tension map (Seat 5 only rated; all other seats 0/0 per table)
| Option | Seat 5 now/later | reason (seat's words) |
|---|---|---|
| (f) own job | 1 / 1 (seat: "0–1"; upper end taken) | "about an hour of ci.yml/conftest/test edit; three extra runner set-ups" / "natural home for every further validation-N render … undo = delete a job" |
| (b) | 1 / 1 | "python job ≈ 17 min Linux; 'both s values' falls (AMENDS); the pack waits" / "loses the second, independent-s run" |
| (c) | 1 / 1 | "a second workflow to keep in step" / "s 0.5 runs Linux-only … never triggers" on a tools-only change |
| (a) | 2 / 2 | "+12.9 min on every PR run … no `timeout-minutes` … doubles" the loop / "the critical path grows a phase at a time" |
| (a′) composed | 1 / 2 (read from conditions; condition (iii) literally unmet: tail-gates 14.0 < python 22.1) | conditions address now only |
| (d) | 1 / 1–2 | "a measurement day, likely wasted" / "2 if kept while mis-measured" |

### Working
1. Bounds: (e) unavailable; a Linux-only exemption, smaller N, τ + SE excluded by AX37 (5.4) (file 47). (b)/(c) require amending "both s values" of her recorded decision and (c) leaves "three OSes" (Seat 5 §2). All others inside.
2. Veto-grade: none.
3. Worst-off: (f), (b), (c) at 1; (a) 2; (a′) 2 (later); (d) up to 2.
4. Compose: (a′) does not lower the maximum below 1. None further.
5. Sum: (f) 2 (1 at the seat's lower end), (b) 2, (c) 2; but (b)/(c) are not fully informed (Seats 2/9 would have to rate the dropped run), so their sums can only rise.
6. Reversibility: (f) "undo = delete a job"; (b) re-add one case. Tie.
7. PRD acceptance check breaks the tie: NFR-1 points to (f), which keeps both s values, both emitters, three OSes; (b)/(c) reduce the measured evidence for a derivation.

**DECISION P05H-QA-T: option (f).** Confidence high (every claim a code, CI or plan fact; one cell taken at the upper end of the seat's range, none read from conditions). The one-phase rule: this is the housing of 05h's own acceptance check (AX37 (5.4) in PR CI), the same class of edit as 05h's test_tail.py/ci.yml changes, not a nightly redesign; it fits 05h.

**Exact CI/test change (orchestrator):**
1. `tools/acoustics/tests/conftest.py`: register `open_field_validation: AX37 (5.4) open_field check at the validation N 2^23 (two renders, 4–6.5 min each); CI runs it in the open-field-validation job on three OSes and deselects it in the python job`.
2. `test_tail.py` L208: `@pytest.mark.parametrize("histories", [None, pytest.param(OPEN_FIELD_VALIDATION_HISTORIES, marks=pytest.mark.open_field_validation)])`; s stays `[0.4, 0.5]`; the smoke cases stay in the python job.
3. `ci.yml`: new job `open-field-validation` (`name: open-field validation (${{ matrix.name }})`), copied from `tail-gates` L213–255: `needs: changes`, `if: needs.changes.outputs.run == 'true'`, `runs-on: ${{ matrix.os }}`, `timeout-minutes: 45`, matrix include ubuntu-24.04/linux, macos-15/macos, windows-2022/windows, `SPATIAL_REQUIRE_RENDER_CLI: "1"`, build `cli` preset, then `python -m pytest tools/acoustics/tests/test_tail.py -v -rP -m open_field_validation --durations=10`.
4. python job L168: `-m "not ensemble and not nightly and not slow and not open_field_validation"` with a comment line; add `timeout-minutes: 45` to the python job (Seat 5's condition (i), hygiene: K2).
5. `ci-ok` L491: add `open-field-validation`. `test_ci_workflow.py` passes by construction (set equality L56); `WORK` L147 is a fixture, unchanged.

**Exact plan text (plan-editor), AX37 (5.4):** replace "If the two 2^23 renders add more than 10 min to the python job on any OS, the clause returns to the board (Seat 5 convened; the nightly is Linux-only and does not run `test_tail.py`), never a loosened τ." with: "The 2^23 cases carry the registered marker `open_field_validation` and run in the PR CI job `open-field-validation` (three-OS matrix, `timeout-minutes` 45, `--durations=10`, in `ci-ok`'s needs); the python job deselects the marker. Record (CI run 42935789745, 2026-11-11): the pair 12.9 / 7.9 / 8.8 min on Linux / macOS / Windows; `ci ok` wall clock 43.1 min, set by `build (windows)`. If `open-field-validation` becomes the longest job of a green run on any OS, the clause returns to the board (Seat 5 convened), never a loosened τ and never a dropped s value (decider file 50, Seat 5 file 49)."
§6 row: "AX37 (5.4): the 2^23 open_field cases moved to the PR CI job `open-field-validation` (three OSes, marker `open_field_validation`); python job back to ≈ 10.5 min; trigger now 'longest job of a green run'. Orchestrator file 47, Seat 5 file 49, decider file 50."
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX37 (5.4), ledger P05B2-M-01: the board-return trigger sentence replaced by the job sentence; "both s values, both emitters", τ alone, 3·SE ≤ τ and "in PR CI on three OSes" unchanged.)

**Load-bearing claims.** L1 K1 (file 47). L2 K3: the python job is not on the critical path and the new job cannot be (K8: < 27 min < 27.3 `build (linux)`). L3 K2 (code). L4 K4 (file 47). L5 K5 (code). L6 product: a job in ci.yml on the three-OS matrix, needed by ci-ok, is "PR CI on three OSes" (AX37 (5.4), BUILD_PLAN L138). L7 Seat 5's own costs as quoted. L8 product: NFR-1 ranks the full check over a reduced one.

**Future-debt register.** Seat 5 | later 1: the job becomes the home of further validation-N renders (05i references, AX46 class runs) | undo: delete the job, move cases back | evidence: `--durations` every CI run; the trigger sentence | repaid when it stays below the longest `build` job.

**Strongest objection.** (b)'s case: by file 43's derivation the s 0.5 run is the same test, so (f) spends ≈ 6.5 min per OS on redundancy. Holds anyway: runners are free (K4), the job is off the critical path (K8), and the second run keeps the derivation checked by data each run (NFR-1); it would not hold if the repository became private and billed (Seat 7 then convened).

**Reversal condition.** `open-field-validation` the longest job of a green run on any OS (visible in every CI run from the next one), or 3·SE > τ on an OS (→ 2^24, unchanged clause).

### Summary
P05H-QA-T | (f) own three-OS job `open-field-validation`, marker `open_field_validation`, timeout 45, both s, both emitters; python job deselects | proposed | Seat 5 (1/1) | 2 | high | AX37 (5.4), NFR-1, CLAUDE.md CI rules | none needed | job becomes longest of a green run

**Challenges to settled decisions:** none.

**Decided for Maisara.** P05H-QA-T: the 2^23 open-field check keeps both s values, both emitters, three OSes and τ alone (NFR-1, AX37 (5.4)) and moves to its own CI job so the python job returns to ≈ 10.5 min; (a) strains Seat 5's budget, (b)/(c) strain NFR-1 by dropping a measured run, (f) serves both. Seat 5 gave most (one hour of CI edit, a job to watch) and gets back a timeout-bounded, parallel home for later validation renders. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX37 (5.4) trigger sentence only.)

**NEEDS MAISARA:** none.


---

## Addendum to P05H-QA-T (file 50) — answers to interrogator file 51. State: **stands, revised with C1–C6 accepted.** Winner (f) unchanged.

**Q1 (K8).** Accepted. Restated K8: the Linux python job of run 42935789745 (22.1 min, file 47 L58) already contains checkout, pip, the render_cli build, the whole `pytest tools` run and the pair; the new job runs a strict subset, so it is bounded by ≈ 22 min < 27.3 (`build (linux)`); macOS/Windows ≤ 16.6 < 35.7 / 42.9. My "pair + set-up < 14.0" is struck (14.0 was the longest tail-gates job, not a set-up bound). Run-to-run variance is what the trigger sentence watches.

**Q2.** Yes. "both s values, both emitters" entered AX37 (5.4) on 2026-11-11 under an AMENDS line (BUILD_PLAN L138), so it is her recorded decision (README L102–104). (b)/(c) break it and fall at step 1. The step-5 sentence about Seats 2/9 is struck (not-required seats sit at 0/0; nothing else), and the step-7 "PRD tie-break" is struck. Survivors (a), (a′), (d), (f); worst-off: (f) at 1 alone ((a) 2, (a′) 2 later, (d) up to 2). The decision follows without a tie-break.

**Q3.** Yes; the block is below.

**Q4.** Across all jobs and OSes. Seat 5's budgeted quantity is the `ci ok` wall clock (file 49 §5), which is set by the single longest job of the run, whichever OS it is on; a per-OS reading would fire on a Linux-only slowdown that changes no one's feedback loop.

**C1** accepted: confidence high; one cell, (a′), read from conditions, not on the chosen option. **C2** accepted as in Q2. **C3** accepted as in Q1. **C4** accepted: L8 now reads "NFR-1 is served equally by every survivor that keeps τ (PRD L105); (b)/(c) are out by her recorded decision ('both s values'), not by an NFR-1 ranking"; NFR-1 stays the acceptance-check id. **C5** accepted (block below). **C6** accepted: (i) include-only matrix (committed as cb7effb, per the orchestrator); (ii) `WORK` unchanged; (iii) `pytest.param` form; (iv) trigger wording "across all jobs and OSes"; (v) "≈ 10–11 min (run 42924781618: 10.5/10.7/10.1)".

### FOR MAISARA P05H-QA-T-A
**Question.** AX37 (5.4)'s board-return trigger ("more than 10 min to the python job on any OS") fired; what replaces it now that the 2^23 cases run in their own PR CI job?
**Answer (exact wording).** Replace that sentence with: "The 2^23 cases carry the registered marker `open_field_validation` and run in the PR CI job `open-field-validation` (three-OS matrix, `timeout-minutes` 45, `--durations=10`, in `ci-ok`'s needs); the python job deselects the marker (back to ≈ 10–11 min; run 42924781618: 10.5/10.7/10.1). Record (CI run 42935789745, 2026-11-11): the pair 12.9 / 7.9 / 8.8 min on Linux / macOS / Windows; `ci ok` wall clock 43.1 min, set by `build (windows)`. If `open-field-validation` becomes the longest job of a green run, across all jobs and OSes, the clause returns to the board (Seat 5 convened), never a loosened τ and never a dropped s value (decider file 50, Seat 5 file 49)."
**Rests on.** AX37 (5.4) as amended 2026-11-11 (τ alone, 3·SE ≤ τ, "both s values, both emitters", "in PR CI on three OSes"; its own sentence delegates the > 10 min case to the board with Seat 5); NFR-1 (PRD L105: thresholds from the Expert; τ untouched).
**Reasoning.** The recorded decision itself sends the overflow to the board, so the new form is within its remit; every survivor keeps τ and NFR-1 equally; the difference is only the CI shape, Seat 5's mandate, and (f) is the only survivor whose worst cell is 1. The trigger is re-expressed on the quantity Seat 5 budgets (the `ci ok` wall clock) instead of a job that was never on the critical path.
- (a) keep in the python job: serves AX37 (5.4) and NFR-1; strains Seat 5's budget (2/2).
- (a′) (a) + timeout + durations: same; later 2 stands (growth unaddressed).
- (b) s 0.4 only: breaks "both s values" (her recorded decision).
- (c) (b) + nightly: breaks "both s values" and "three OSes".
- (d) concurrent renders: serves the ids; unmeasured, 1/1–2.
- (f) own job: serves AX37 (5.4), NFR-1 and "PR CI on three OSes"; Seat 5 1/1.
**What would make her veto it.** "The python job was never on the critical path (file 47: `build (windows)` 42.9 min vs python 22.1), so the 10 min trigger could have stood and no job was needed." It did not stand because her own sentence made the 10 min figure the return trigger, and Seat 5 keeps (a) at 2 without a timeout and with the growth over 05i/08/12 unaddressed.
`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX37 (5.4), ledger P05B2-M-01: the board-return trigger sentence replaced by the job sentence; "both s values, both emitters", τ alone, 3·SE ≤ τ and "in PR CI on three OSes" unchanged.)

### Final plan text (plan-editor)
AX37 (5.4): the replacement sentence exactly as in the Answer above. §6 row: "AX37 (5.4): the 2^23 open_field cases moved to the PR CI job `open-field-validation` (three OSes, marker `open_field_validation`, timeout 45); python job back to ≈ 10–11 min (run 42924781618: 10.5/10.7/10.1); trigger now 'longest job of a green run, across all jobs and OSes'. Orchestrator file 47, Seat 5 file 49, decider file 50, interrogator file 51; CI change cb7effb."

**Summary.** P05H-QA-T | (f) | stands (revised per C1–C6) | Seat 5 (1/1) | sum 2 | high (one cell, (a′), read from conditions, not on the chosen option) | AX37 (5.4), NFR-1 | no corpus claim | `open-field-validation` the longest job of a green run. P05H-QA-T-A | trigger sentence as above | for Maisara | — | — | high | AX37 (5.4), NFR-1 | — | same.

**Decided for Maisara.** P05H-QA-T (f) and P05H-QA-T-A as above; Seat 5 gave the hour of CI work and gets a bounded, parallel home for later validation renders; one AMENDS line (trigger sentence only). **NEEDS MAISARA:** none.
