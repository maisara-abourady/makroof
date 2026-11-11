# 55 — Interrogator: diff check of the plan application cad4506 (the Windows register entry) — DIFF OK; the test comment's surviving overstatement fixed

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). Applied with this file: the test comment (fingerprinted: CI run 11 covers the head), the file 31 wording, the §5 (b) baseline sentence.

Corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (not needed: CI timing records and plan readings only).

**Verdict on commit cad4506: DIFF OK** for all five edits. One survival of the struck overstatement sits outside the commit (test comment) and must still be fixed.

**Edits checked at HEAD, word for word against the brief / file 53 as corrected by file 54:**

1. `docs/BUILD_PLAN.md` L139, AX38 4c register: the Windows entry matches brief item 1 verbatim, followed by "is listed; the flutter scene stays strict on every OS (7.6–10.6 s)". Single line. Conditional form ("if the runner is shown to be the cause") kept.
2. `docs/phases/phase-05h.md` §5 (b) L379–381: "; and on Windows (recorded 36.73 s on CI run 42942694523, median 2 589 ms pinned; strict 29.04 / 29.50 / 28.57 s on the three earlier runs; listed under (d); closes with the macOS entry)" matches item 2; macOS clause keeps "if the runner is the cause".
3. `docs/phases/phase-05h.md` §5 (a) L371–372 (orchestrator fix): "the Windows cube was strict at 29.04 s until CI run 42942694523 listed it, (b)" — past tense, correct.
4. `docs/phases/phase-05i.md` §3 scope 3 L83–86: matches item 3 verbatim; "likely cause, to be shown at Phase 13" kept; "28.6–29.5 s" is a correct rounding of 28.57 / 29.50.
5. `docs/BUILD_PLAN.md` §6 L477: matches item 4 verbatim, source column "orchestrator; CI run 42942694523"; single line.

**Numbers:** 36.73 s / 2 589 ms agree with `kGateRegister` L83 {36.73, 2589.0, true} and CHANGELOG L149; 29.04 / 29.50 / 28.57 s and medians 2 000 / 2 056 / 1 926 ms agree with file 31 L341, L463, L534. Computed: 2589/2000, /2056, /1926 = +29.5 / +25.9 / +34.4 % (the "25–30 %" is file 54's accepted summary; its own figures were 23–36 %); 1.10 × 2589 = 2 848 ms, 38–48 % above the three strict medians, as file 53 states.

**"Every record" (file 54 Fix B):** absent from the four edited files, file 53 and CHANGELOG. It **survives in** `tests/unit/test_diffuse_records.cpp` L79–80: "a shared runner 25-30 % slower on every / record of that run" (line-wrapped, which is why a single-line grep misses it). File 53 L58 claims Fix B was applied "in the test comment"; it was not. Fix: replace with "slower on the restore, flutter and full-rebuild records (the (iv) 8-instance load inside its earlier range)". Also in the source `docs/review/phase-05h/31-orchestrator-local-records.md` L545: "every Windows record of that run 25–30 % slower (the flutter restore 13.15 s against 9.65–10.6 s …)" — carries both of file 54's slips (2)(i) (9.65 is file 1's local value; 10.6 not in file 31) and (2)(ii). A dated record; correct it or leave with a note, your call.

**Windows still called strict anywhere?** Only in dated 2026-11-10 texts, superseded: CHANGELOG L137 ("Windows and the flutter scene stay strict"), BUILD_PLAN §6 L472 ("Windows 29.04 s then 29.50 s strict"), and phase-05h §3 L150–153, which lists only the Linux and macOS cubes as registered (Windows omitted, D-H1 record of 2026-11-10). No fix required; note if you want §3 to mirror §5.

**Minor wording (optional):** phase-05h L381–382 "medians re-baselined from CI run 42909003931 (CHANGELOG entry of the baselines)" now follows the Windows entry, whose baseline is run 42942694523. Suggest "the Linux and macOS medians re-baselined from CI run 42909003931". Brief-prescribed placement, so not a plan-editor departure.

**Table rows broken across lines:** none (L139, L477 each one line).

Files: /home/user/makroof/docs/BUILD_PLAN.md, /home/user/makroof/docs/phases/phase-05h.md, /home/user/makroof/docs/phases/phase-05i.md, /home/user/makroof/tests/unit/test_diffuse_records.cpp, /home/user/makroof/tests/golden/CHANGELOG.md, /home/user/makroof/docs/review/phase-05h/31-orchestrator-local-records.md.
