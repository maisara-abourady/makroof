# 51 — Interrogator: decider file 50 (P05H-QA-T) — SURVIVES WITH CORRECTIONS (winner unchanged; C1–C6)

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). The decider's addendum answering Q1–Q4 with the FOR MAISARA block (C5) is appended to file 50.

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (14 files). No acoustic claim is load-bearing; the facts checked are code, CI and plan facts.

**Outcome: P05H-QA-T (option (f)) SURVIVES WITH CORRECTIONS.** Winner unchanged under every redo. Six restatements, two of them to the saved decision text (file 50 addendum) before the plan text is applied.

**Decision ledger**

| check | item | verdict | evidence |
|---|---|---|---|
| convening | Seat 5 convened | faithful | file 49 |
| convening | Seats 2/9 not required | faithful, but see ordering C2 | (f) rests on no acoustic claim; s-independence used only by (b)/(c), not chosen |
| convening | Seat 7 not required | acceptable | README L61 "schedule and complexity cost" touched only at ≈1 h; unbilled runners (file 47 L69); reason stated |
| map | (f) 1/1 | faithful | file 49 §3 "1", §4 "0–1"; upper end taken |
| map | (a′) 1/2 read from conditions | faithful | §6 "(a) → 1 if (i)…(iii). Without (i) I keep 2"; §4 later-2 reason (growth) not addressed by any condition; (iii) literally unmet (tail-gates 14.0 < 22.1, file 47 L61) |
| map | (a) 2/2, (b) 1/1, (c) 1/1, (d) 1/1–2 | faithful | file 49 §3–4 |
| map | confidence line "none read from conditions" | INCONSISTENT with its own map ((a′) is marked read from conditions) | file 50 L57 vs L45; C1 |
| debt | Seat 5 later 1 row | present; 05i exists (BUILD_PLAN L264); "repaid when" names the `build` job (ci.yml L266) | file 50 L72 |
| ordering | step 1 bounds | misapplied, winner unchanged | "both s values, both emitters" sits in AX37 (5.4) as amended 2026-11-11 under an AMENDS line (BUILD_PLAN L138), so it is her recorded decision (README L102–104); (b)/(c) break it and fall at step 1, not at a "PRD tie-break" (step 7 is not in decider.md §5); C2 |
| ordering | step 5 sum | misapplied | "Seats 2/9 would have to rate the dropped run, so their sums can only rise": not-required seats sit at 0/0 and nowhere else; cells invented for unconvened seats. Strike; with (b)/(c) out at bounds the sentence is unneeded; C2 |
| ordering | steps 2–4, 6 | correct | no 3; max 1 for (f); (a′) does not lower the maximum; reversibility tie |
| K1 | pair 12.9/7.9/8.8 min | CORRECT | 386+386 = 772 s = 12.87; 227+246 = 473 s = 7.88; 265+265 = 530 s = 8.83 (file 47 L11–13) |
| K2 | python job has no timeout-minutes | CORRECT | ci.yml L113–209 |
| K3 | wall clock 43.1 set by build (windows) 42.9; python 22.1; tail-gates max 14.0 | CORRECT | file 47 L54–66 |
| K5 | new-job rules | CORRECT | test_ci_workflow.py L47–56; CLAUDE.md "Every new CI job…" |
| K6 | markers registered per sub-package | CORRECT | conftest.py L17–28 |
| K7 | trigger sentence verbatim | CORRECT | BUILD_PLAN L138, word for word |
| K8 | "pair 12.9 + set-up < 14.0 … < 27 min < 27.3" | IMPRECISE (working wrong, conclusion holds) | 14.0 min is the longest tail-gates job (macOS, classroom), not a bound on 12.9 + set-up; set-up includes a render_cli build (Seat 5 §3: 3–5 min [Hyp]) so 12.9 + set-up ≈ 16–18 min, not < 14.0. The valid bound: the Linux python job (22.1 min) already contains set-up + the pair + everything else, so the new job ≤ ≈ 22 min < 27.3 build (linux); macOS/Windows ≤ 16.6 < 35.7/42.9. Run-to-run variance (ccache, runner load) is what the trigger sentence watches; C3 |
| L6 | three-OS matrix job in ci-ok's needs = "PR CI on three OSes" | CORRECT | BUILD_PLAN L138; ci.yml L491 |
| L8 | "NFR-1 ranks the full check over a reduced one" | IMPRECISE | PRD L105: match measured IRs, pass listening tests, thresholds from the Expert. It does not rank the number of s values of a synthetic integral check. The ground for (f) over (b)/(c) is her recorded decision ("both s values"), already cited as AX37 (5.4); C4 |
| PRD proxy | Decided-for-Maisara line | surviving options (a′), (d) not shown against NFR-1/AX37 (5.4) | file 50 L83 shows (a), (b)/(c), (f) only; C5 |
| PRD proxy | AMENDS of the trigger sentence | within remit, form incomplete | the recorded decision's own sentence "returns to the board (Seat 5 convened)" delegates the new form; no case (a)/(b)/(c). But decider.md L51 and §1a L115–118 require the amendment written as a `FOR MAISARA` block (question, exact wording, ids, option lines, strongest PRD reading against it); file 50 has the AMENDS line inside the DECISION only; C5 |
| CI/test change | items 1–5 | fit to apply | see C6 |

**Corrections**

C1. Confidence line: "one cell ((a′)) read from conditions, not on the chosen option".
C2. Working: move (b)/(c) to step 1 (break her recorded decision "both s values"); strike the Seats 2/9 sentence at step 5 and the "PRD tie-break" step 7. Survivors (a), (a′), (d), (f): worst-off (f) 1 alone; the decision follows without a tie-break.
C3. K8 as restated above.
C4. L8: replace NFR-1 "ranks" with: NFR-1 is served equally by every survivor that keeps τ; (b)/(c) are out by her recorded decision. Keep NFR-1 as the acceptance-check id.
C5. Add to file 50 (addendum): a `FOR MAISARA P05H-QA-T-A` block for the trigger-sentence replacement (ids AX37 (5.4), NFR-1; one line each for (a), (a′), (b), (c), (d), (f); veto reading: "the python job was never on the critical path, so the 10 min trigger could have stood"), with the AMENDS line as written.
C6. CI/test change, apply with: (i) use the python job's include-only matrix (L120–124), not tail-gates' `os:` × `room` form; (ii) test_ci_workflow.py L56 set-equality passes once `open-field-validation` is in `ci-ok` needs; `WORK` L147 unchanged is fine (the script reads whatever keys it is given); (iii) test_tail.py L208 `pytest.param(..., marks=pytest.mark.open_field_validation)` is valid; (iv) trigger wording: "the longest job of a green run on any OS" is ambiguous (longest among all jobs, or among that OS's); write "the longest job of a green run, across all jobs and OSes"; (v) "python job back to ≈ 10.5 min" is run 7's Linux figure; the per-job deltas (11.6/5.9/6.5 min) are smaller than the pair durations, so write "≈ 10–11 min (run 42924781618: 10.5/10.7/10.1)".

**Questions for the rebuttal round**
1. K8: do you accept the 22.1 min python-job bound in place of "pair + set-up < 14.0"? (falsifiable from file 47 L58.)
2. Are (b)/(c) dropped at step 1 by her recorded decision ("both s values", BUILD_PLAN L138), making the step-5 Seats 2/9 sentence and the step-7 tie-break unnecessary?
3. Will the trigger-sentence amendment be written as a `FOR MAISARA` block per decider.md §1a L87–95, with (a′) and (d) shown against the ids?
4. Trigger wording: across all jobs and OSes, or per OS?

Files: /home/user/makroof/docs/review/phase-05h/50-decider-QA-T-python-job-time.md, /home/user/makroof/docs/review/phase-05h/47-orchestrator-QA-python-job-time.md, /home/user/makroof/docs/review/phase-05h/49-seat5-QA-python-job-time.md, /home/user/makroof/.github/workflows/ci.yml, /home/user/makroof/tools/ci/test_ci_workflow.py, /home/user/makroof/tools/acoustics/tests/conftest.py, /home/user/makroof/tools/acoustics/tests/test_tail.py, /home/user/makroof/docs/BUILD_PLAN.md (L138), /home/user/makroof/docs/board/README.md, /home/user/makroof/.claude/agents/decider.md, /home/user/makroof/docs/PRD.md (L105).
