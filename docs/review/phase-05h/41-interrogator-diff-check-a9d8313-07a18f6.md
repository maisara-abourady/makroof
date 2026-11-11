# 41 — Interrogator: diff check of the plan-editor applications a9d8313 (register medians, FTZ form, §6 row) and 07a18f6 (the Linux entry after run 42924781618) — DIFF OK

phase-05h (session 2); asked for by review file 39 minor 5. Verbatim interrogator output (the orchestrator saved it). The 'job-summary warning' wording (note 1; file 39 minor 6) goes to the final bookkeeping brief as 'job-log warning'.

**Interrogator diff-check: plan-editor commits a9d8313 (brief g6) and 07a18f6 (brief run7)**
Corpus present, revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (no corpus fact is at issue here; this is a text-against-brief-and-source check). Files read at HEAD: /home/user/makroof/docs/BUILD_PLAN.md L139 (AX38) and L471–472 (§6); /home/user/makroof/docs/phases/phase-05h.md L329–381; /home/user/makroof/docs/phases/phase-05i.md L77–84; sources /home/user/makroof/docs/review/phase-05h/31-orchestrator-local-records.md L198–200, L279–281, L341–343, L428–470; /home/user/makroof/tests/unit/test_diffuse_records.cpp L68–79, L368–393; /home/user/makroof/docs/review/phase-05h/20-decider-decision-D-H3.md L183; /home/user/makroof/tests/golden/CHANGELOG.md L137–139; /home/user/makroof/.github/workflows/ci.yml L351–355.

**Verdict: DIFF OK.** Every replacement string of both briefs is present at HEAD verbatim, composed correctly where run7 overwrote g6 fragments; no departure found.

**Brief g6 (a9d8313), items 1–5**
1. AX38 4c register (L139): "medians re-baselined from CI run 42909003931, 2026-11-10" present; Linux entry "(recorded 30.27 s on the local box, file 1; CI run 42909003931: 14 × worst 29.62 s, median 2 043 ms, the pinned growth-bound baseline; …"; macOS "(recorded 33.40 s on the local box; CI run 42909003931: 14 × worst 37.37 s, median 2 106 ms, min 1.84 / worst 2.67 s, the pinned baseline; …". Source agreement: file 31 L198 (median 2043, 14× 29.62), L279 (min 1840 / median 2106 / worst 2669 → 1.84 / 2.67 / 37.37), L341 (29.04); kGateRegister L76–77 (2043.0 / 2106.0, listed true), L78 Windows strict.
2. phase-05h §5 (b) L369–374: g6 fragments present as later amended by run7; "medians re-baselined from CI run 42909003931 (CHANGELOG entry of the baselines)" present; the CHANGELOG entry exists (L137).
3. phase-05h FTZ criterion L333–337: matches the brief word for word; agrees with decider file 20 L183 (1) (x86-64 DE | UE / DE clear; AArch64 UFC in FZ-off, IDC | UFC in FZ-on) and (3) (calibration, SKIP on failure); the two K-c4 runs 42909003931 and 42921348351 are those named in file 31 L430–434.
4. phase-05i §3 scope 3 (L77–84): g6 text present as later amended by run7.
5. §6 row L472 added (L471 names no baselines, so the brief's condition held); source column "orchestrator; CI run 42909003931".

**Brief run7 (07a18f6), items 1–5**
1. AX38 Linux: "on that run it passed 30 s and the §5 (c) job-summary warning printed; on the final 05h run 42924781618 it read 30.18 s (median 2 092 ms, growth bound ≤ 2 247 ms met), so the entry stays listed and its removal under (c) is phase-05i scope 3's call on 05i's first run; remedy:" ✓; macOS "run 42924781618: 31.23 s, median 1 849 ms, growth bound met;" ✓; "Windows (29.04 s; run 42924781618: 29.50 s, strict)" ✓. Source file 31 L461–463. Arithmetic: 1.10 × 2043 = 2247.3 → 2247 ✓; 14 × 2155 ms = 30.17 s (printed 30.18 from unrounded ms, as the source) ✓; 14 × 2231 = 31.23 ✓; 14 × 2107 = 29.50 ✓.
2. phase-05h (b) L369–371: "passed 30 s on that run, the (c) warning printed; 30.18 s, growth bound met, on the final run 42924781618, so it stays listed and (c)'s removal is phase-05i scope 3's call; closes at phase-07c)" ✓.
3. phase-05i scope 3 L79–82: replacement string verbatim ✓.
4. §6 row L472 parenthetical verbatim ✓.
5. AX38 record line F-a insertion verbatim ✓; source file 31 L464 (Linux worst 4174, others 2095/2098; macOS 2266 → 2.27; Windows 2101 → 2.10) and L468–470.

**Table rows:** AX38 (L139) and the §6 row (L472) are each one line; no row broken.

**Notes only (no fix required)**
- File 39 minor 6: the "(c) job-summary warning" is a `std::printf` to stdout (test_diffuse_records.cpp L375–384), run from the Release `[benchmark]` step (ci.yml L351/354); nothing in ci.yml tees `05h-records` output into `$GITHUB_STEP_SUMMARY` (only L61, L65, L510 write the summary). So "job-summary warning" in AX38 4c, phase-05h §5 (b)/(c), phase-05i scope 3 and the §6 row still describes a job-log print, not a step summary. Both briefs used that wording, so this is a wording debt of the plan text, not a plan-editor departure.
- phase-05h L371 runs to ~111 columns against the file's ~108 wrap; cosmetic.
- phase-05i scope 3 still gives macOS only "(37.37 s, median 2 106 ms)" without the 31.23 s of run 42924781618; run7 did not ask for it; consistent with AX38, note only.
