# Phase 05i: plan-editor, steward gap G18 (K-e12 run-of-record values), 2026-11-11

/fix-plan step 4. Source of every figure: `docs/review/phase-05i/19-orchestrator-ci-run-of-record.md`
(CI run 43031773338: K-e12 lines for Linux, macOS and Windows, the GATE lines' `flutterDev`, the reading's K-e12 bullet).

## Applied

1. `docs/BUILD_PLAN.md` §2 AX38 4c, K-e12 finding: right after the "*Record (phase 05i, CI run 43007183782):* …
   Remedy unchanged (phase-07c conditions 9–10, re-measured by condition 7)." text, appended:
   "*Run of record 43031773338:* low-α worst 3 067 / 3 241 / 5 113 ms (Linux / macOS / Windows; builder busy at the
   restore in 9 / 9 / 10 of 10 runs; Windows on a slow runner, flutter +48.9 %); flutter 833 / 751 / 1 492 ms; above
   2.143 s on every OS and above 3 s on every OS (Linux 3 067 ms); a finding under the register's form, remedy unchanged."
2. `docs/BUILD_PLAN.md` §2 AX38 4c, the record against the anchors: right after "… recorded and remedied in the K-e12
   finding above.", appended: "Run of record 43031773338: worst of 10 3 067 / 3 241 / 5 113 ms on Linux / macOS /
   Windows, above 3 s on every OS (Linux 3 067 ms; Windows on a slow runner, flutter +48.9 %); recorded in the same finding."

Figures checked against file 19: low-α worsts 3067 (L122), 3241 (L477), 5113 (L619) ms; builder busy 9 / 9 / 10 of 10
(low-α lines); flutter worsts 833 (L111), 751 (L466), 1492 (L608) ms; Windows flutterDev +48.9 %. The 3 s statement
follows the brief's correction (3 067 > 3 000, so every OS).

## Held

None.

## DECISIONS NEEDED

None (record values only; no acoustic, numeric or rule choice made).

## Interpretations

- Second insertion phrased to match the anchors record's own style ("worst of 10 … on Linux / macOS / Windows") and
  names the slow-runner caveat for Windows, as the K-e12 insertion does.
- No §6 change-log row added and the existing 2026-11-11 05i row not touched: the edit records run values, changes no
  assumption, threshold or golden, and the brief forbids changing any other passage.
- Nothing committed.

## git diff --stat

 docs/BUILD_PLAN.md | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
