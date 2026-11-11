# 24 — Interrogator: diff check, K-e12 run-of-record insertions (/fix-plan step 5), 2026-11-11

Corpus revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Saved verbatim by the orchestrator (the interrogator reads only).

**Checked:** the two insertions in `docs/BUILD_PLAN.md` AX38 4c (L158) described in file 23 (the "*Run of record 43031773338:* …" sentence after the K-e12 finding's 05i record; the "Run of record 43031773338: worst of 10 …" sentence after the record against the anchors), against file 19's K-e12 lines (L10, L111–132, L466–487, L608–629) and the Windows GATE line (L606). Run records, not acoustic claims; rated faithful or not against file 19.

**Result:** both insertions faithful; every number traces; the 2.143 s and 3 s statements correct on every OS (low-α worsts 3 067 / 3 241 / 5 113 ms all above 2 143 and 3 000 ms; Linux the smallest margin, named). Two minor wording points (P05I-136, -137). No WRONG items.

| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| P05I-132 | NUMBER | Low-α worst 3 067 / 3 241 / 5 113 ms | CORRECT | File 19 L122, L477, L619; per-run maxima agree (L129, L484, L626, run 6) | none | closed |
| P05I-133 | NUMBER | Builder busy 9 / 9 / 10 of 10 runs | CORRECT | File 19 L122, L477, L619; Linux run 3 "no", macOS run 2 "no", Windows all "yes"; worst over busy = overall worst | none | closed |
| P05I-134 | NUMBER | Flutter worst 833 / 751 / 1 492 ms | CORRECT | File 19 L111, L466, L608 | none | closed |
| P05I-135 | NUMBER | Windows "slow runner, flutter +48.9 %" | CORRECT | File 19 L606 `flutterDev=+48.9%`; L607 `not-evaluated(runner,flutter+48.9%)` | none | closed |
| P05I-136 | NUMBER | "Above 2.143 s on every OS" placed after the flutter worsts | IMPRECISE | True of the low-α worsts only; the flutter worsts are "within" (L111/L466/L608) | minor | **applied**: "flutter-scene worst 833 / 751 / 1 492 ms, within; low-α worst above 2.143 s on every OS …" |
| P05I-137 | NUMBER | "flutter +48.9 %" beside the flutter-scene worsts | IMPRECISE | +48.9 % is the GATE line's `flutterDev` (runner speed), a different quantity | minor | **applied**: "flutterDev +48.9 %" (both insertions) |
| P05I-138 | NUMBER | "Above 3 s on every OS (Linux 3 067 ms)" | CORRECT | Each worst above 3 000 ms; differs correctly from run 43007183782 (macOS 2 648 ms) | none | closed |
| P05I-139 | DECISION | "A finding under the register's form, remedy unchanged" | CONSEQUENCE | Matches file 19 L122/L477/L619 ("FINDING … remedy phase-07c conditions 9-10") | none | closed |
