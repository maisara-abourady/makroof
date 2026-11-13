# 26 — Interrogator on the file 25 edits (diff 5753896..77b5c6e)

2026-11-13, corpus c1b171f. Saved by the orchestrator from the interrogator's report. No acoustic fact load-bearing; arithmetic against
files 22, 23 and PRD reading. Tree compared directly (no shell).

**Verdict: SURVIVES.** Every text matches file 25 verbatim or within the editor's four stated format interpretations; every number
recomputes; no PRD MISREAD; no contradiction left. Step 5 closes.

| item | verdict | outcome |
|---|---|---|
| Q1 4c public reason (1.0530 → 5.3 %, 1.3681 → 37 %, 1.1618 → 16 %) | CORRECT | SURVIVES |
| Q1 4c Amended summary | CORRECT | SURVIVES |
| Q1 reversal sentence (2.691 / 2.3963 = 1.1230; 1.10 × 1 282.7 = 1 411 < 1 438) | CORRECT | SURVIVES |
| Q1 phase-07d scope 8 / last AC | CORRECT | SURVIVES |
| Q1 brief FM-GROWTH line (NFR-4 L108 macOS, Windows only; preamble L101; NFR-6 L110) | CORRECT | SURVIVES; no PRD MISREAD |
| Q1 debt row S3 / S6 | not applicable (no plan or brief debt register; row lives in file 25) | SURVIVES |
| Q2 cond. 12 (c) note (thread-CPU 1 158.1 / 1 138.3 / 1 160.8 µs < 1 333 µs; wake late 6 474 µs; macOS 3 / 5 / 10; Windows 0/0) | CORRECT (Windows figure repeated: redundant, not wrong) | SURVIVES |
| Q2 brief D-B1 line (preamble, FR-3D-5, FR-3D-6, FR-SIM-7) | CORRECT | SURVIVES; no PRD MISREAD |
| Q2 routing to 08-4 | gap predating this diff: phase-08-4 scope 9 / AC print the priority but do not carry the return to the board | question 1 |
| Q3 G9 text (9cc0e32; Linux max/mean 1.006 ≤ 1.05) and CHANGELOG reason | CORRECT | SURVIVES |
| Q3 brief G9 line (preamble, NFR-6) | CORRECT | SURVIVES |
| Q4 (1.083 / 1.0219 = 1.0598; Linux 1.1230 ≥ 1.07) | CORRECT | SURVIVES |
| Q5 title, Depends, Goal, §0 row 37 | CORRECT | SURVIVES |
| RP-06, RP-16, RP-17 | CORRECT / fixed | SURVIVES |
| §6 row 528 in place | IMPRECISE (minor): Q2 recorded only as "gains the B1-b figures" | SWC (optional) 1 |
| §6 row 523 "Linux and Windows … asserted" | not a contradiction (proviso inline) | optional clarity 2 |
| 4c solve-bound label "PROVISIONAL" reads as every OS | IMPRECISE (minor, predates the editor) | optional 3 |

**Optional replacements.**
1. Row 528: "AX38 (i) cond. 12 (c) note gains the B1-b figures of these runs." → "AX38 (i) cond. 12 (c) note gains the B1-b
   figures of these runs and states Linux's residual as D-B1 item 6's, measured without real-time priority (thread-CPU max 1 158 /
   1 138 / 1 161 µs < 1 333 µs; an 08-4 residual with real-time priority obtained returns D-B1 to the board before Phase 13; decider
   file 25 Q2); 07d's growth re-pin returns Linux to the board if print-only again (decider file 25 Q1, Q5)."
2. Row 523, after "(an OS whose ratios over the current pin's runs have max/min > 1.10 is print-only)": insert "; at the S2 re-pin
   Linux and macOS print-only, Windows asserted, row 528".
3. AX38 4c: "PROVISIONAL (print-only, never a (d) trigger)" → "PROVISIONAL until its exit below (print-only, never a (d) trigger)".

**Question 1 (routing).** D-B1's reversal "earlier if 08-4 shows it", read by file 25 Q2 as "an 08-4 residual with real-time priority
obtained": should phase-08-4 scope 9 and its AC carry that return to the board?

**Orchestrator's application (no new decision):** optional 1–3 applied as written. Question 1: the return is decided text (file 25
Q2, as applied in the AX38 (i) note); it is copied into phase-08-4 scope 9 / AC so the file 08-4's session executes carries it — a
routing of decided text, not a new decision (as file 20 FM-11 / Q1).
