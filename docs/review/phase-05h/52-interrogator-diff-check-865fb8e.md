# 52 — Interrogator: diff check of the plan application 865fb8e and the CI change cb7effb (P05H-QA-T) — DIFF OK (one ci.yml comment fix, applied)

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). The ci.yml comment fix and the §6 row's AMENDS words were applied in the commit that adds this file; ci.yml is fingerprinted, so CI run 10 covers the head.

**DIFF CHECK 865fb8e / cb7effb vs brief 50 — DIFF OK for the plan text; one fix in ci.yml's comment, two cosmetic notes.**

**Brief item 1 (BUILD_PLAN L138).** Replacement sentence is verbatim the addendum's "Answer (exact wording)" (marker, job, matrix, timeout 45, `--durations=10`, ci-ok needs; "≈ 10–11 min; run 42924781618: 10.5/10.7/10.1"; "12.9 / 7.9 / 8.8"; "43.1 min, set by `build (windows)`"; "across all jobs and OSes"; "never a dropped s value"). Rationale-column note verbatim per brief, and in README L100 form: `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` One line. ✓

**Brief item 2 (§6, L476).** One line; source column as specified. One departure from the brief's text: brief "the python job back to ≈ 10.5 min" → HEAD "back to ≈ 10–11 min (run 42924781618: 10.5/10.7/10.1)". That is file 51 C6 (v) and file 50's "Final plan text", which the brief told the editor to apply over its own wording; correct. Note: the row's `AMENDS her decision of 2026-11-10` (date only) is the brief's short form; README L100 and the neighbouring rows L474–475 carry her words. Optional fix: append `: "I accept the board's answer by definition."`.

**Brief item 3 (phase-05h §5 criterion 9, L328–331).** Brief: after "(PR CI, three OSes)" add " — the 2^23 cases … (decider file 50)". HEAD put the clause inside the parentheses: "(PR CI, three OSes — the 2^23 cases in the `open-field-validation` job, the smoke cases in the python job (decider file 50));". Same meaning, punctuation only; literal form would be "(PR CI, three OSes) — the 2^23 cases …, the smoke cases in the python job (decider file 50);". Acceptable as is.

**Ledger L2257 (orchestrator).** One line; 12.9/7.9/8.8, "≈ 10–11 min", "across all jobs and OSes", short AMENDS form consistent with L2254–2256. ✓

**cb7effb vs file 50 items 1–5 + C6 (i)–(iii).**
1. conftest L28–33: marker text as item 1 (ASCII "4-6.5" for "4–6.5"; "(decider file 50, P05H-QA-T)" appended). ✓
2. test_tail L207–211: `pytest.param(OPEN_FIELD_VALIDATION_HISTORIES, marks=pytest.mark.open_field_validation)` (C6 iii); s `[0.4, 0.5]`; smoke cases unmarked. ✓
3. ci.yml L273–322: name, `needs: changes`, `if` gate, include-only matrix (C6 i), `timeout-minutes: 45`, `SPATIAL_REQUIRE_RENDER_CLI`, cli build, exact pytest line. ✓
4. python job: L118 `timeout-minutes: 45`; L171 `-m "not ensemble and not nightly and not slow and not open_field_validation"` with comment L169–170. ✓
5. ci-ok L549 includes `open-field-validation`; test_ci_workflow L56 set equality passes by construction; `WORK` (C6 ii) untouched. ✓

**Fix (the one real departure):** ci.yml comment L271–272 carries the pre-C6 (iv) trigger: "so the python job keeps its ~10 min; … If it becomes the longest job of a green run on any OS, the clause returns to the board (Seat 5)." File 51 C6 (iv) named "on any OS" ambiguous; the plan now says "across all jobs and OSes". Replace with: "so the python job returns to ≈ 10–11 min; … If it becomes the longest job of a green run, across all jobs and OSes, the clause returns to the board (Seat 5)." (Comment only; note ci.yml is fingerprinted.)

**Numbers vs file 47.** 12.9/7.9/8.8 (L11–13), 43.1 (L54), 10.5/10.7/10.1 (L11–13) agree everywhere they appear (L138, L476, ci.yml L270, ledger L2257). Minor: "4–6.5 min each" (file 50 item 1, conftest, ci.yml) vs file 47's macOS 227 s = 3.8 min; file 50's own figure, not the editor's.

**Old trigger sentence.** "more than 10 min to the python job … on any OS, the clause" appears nowhere in BUILD_PLAN.md or phase-05h.md. It survives only as history in ledger.md L2254 (row P05H-QA) and in review files 42/43/47/50, which is correct.

**Rows broken across lines:** none (L138, L476, ledger L2257 each one line).
