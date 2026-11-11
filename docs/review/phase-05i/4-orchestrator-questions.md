# Phase 05i: questions for the decider (orchestrator, 2026-11-11)

Evidence: CI run 43007183782 (all green, three OSes; lines in file 3), phase 05h's RG-1-form runs 42964823518 and
42975074716 (`docs/review/phase-05h/31-orchestrator-local-records.md` L600–700), nightly 43007188366 (green).
Governing texts: `docs/phases/phase-05i.md` §2, §3.2, §3.3; `docs/phases/phase-05h.md` §5 (a)–(d) (L370–402);
`docs/BUILD_PLAN.md` AX38 (row at L158); PRD (NFR-1, NFR-2, NFR-6, and whatever the decider finds relevant).
Nothing here changes the engine, τ, N, the case list, W_max or a range.

## Q1 — the register under §5 (c): which listed entries leave?

phase-05h §5 (c): "A listed entry whose printed 14 × worst passes 30 s is a job-log warning … and leaves the register
through `/fix-plan` before the next phase is `done`; its register text closes; the low-α scene's hosted-runner
assertion stays in this form (in-window on Linux and Windows, printed on macOS) until Phase 13; the strict 30 s branch
applies to the flutter scene, and to the low-α scene only on the release machines." phase-05i §3.3 (ii) repeats this,
then adds: "otherwise it stays listed and the run is recorded; the Linux (30.27 s), macOS (33.40 s) and Windows
(36.73 s) entries stay listed with the remedy phase-07c conditions 9–10". phase-05h file 31 L92: "the entry's removal
is phase-05i scope 3's call".

14 × worst at the low-α cube (96 kHz), RG-1-form runs:

| OS | 42964823518 | 42975074716 | 43007183782 (05i) | status in 05i's run |
|---|---|---|---|---|
| Linux | 25.29 s PASSES30S | 24.75 s PASSES30S | **27.61 s PASSES30S** | asserted in-window (median 1 892 ≤ 2 275) |
| Windows | 29.51 s PASSES30S | 44.83 s OVER30S (slow runner, flutter +43.6 %) | **28.74 s PASSES30S** | asserted in-window (median 1 996 ≤ 2 231) |
| macOS | 31.82 s OVER30S | 30.27 s OVER30S | 43.54 s OVER30S | reported-only (median 1 905; trigger 2 172 not reached) |

Context (the K-e12 record, Q2): on the same run the low-α restore with a room edit in flight is 3.28 / 2.65 / 3.23 s
worst of 10 (Linux / macOS / Windows), above the per-restore budget 2.143 s (= 30 s / 14) on every OS; the idle
restore median of a new state is 1.80 / 1.80 / 1.94 s.

The question: does the Linux entry, the Windows entry, both or neither leave the register now (and with what text),
given that phase-05i §3.3 also says the three entries "stay listed"? If an entry leaves, does the test's
`kGateRegister` `listed` flag change (it changes only what is printed: the low-α assertion form is fixed until
Phase 13), or does only the register text close?

## Q2 — the K-e12 finding and Raise item 1

phase-05i §3.2: "a record above 2.143 s is a finding under the register's form, remedied by phase-07c conditions 9 and
10"; never a CHECK. The record is above 2.143 s on all three OSes (3.28 / 2.65 / 3.23 s; a build was in flight in every
run, checked locally after b83345c adds the per-run print). phase-05i §2 item 1 (Raise with Maisara): "the records go
to Maisara against the 1 / 3 / 10 s marks, labelled UI response-time anchors (Card et al. 1991), not audibility
limits …; any room above 3 s is named as a finding" — conditional on "if the full-rebuild records were not in phase
05h's CI run" (they were: run 42909003931; answered in 05h, decider files 33/36). The K-e12 worst is above 3 s on
Linux and Windows.

The question: does the K-e12 record above 3 s re-open Raise item 1 for Maisara, or is it the AX38 4c finding that
§3.2 names, written into AX38 4c with its remedy (phase-07c conditions 9–10) and listed in the PR? Answer for
Maisara from the PRD.

## Q3 — Raise item 2 (the AX38 (iv) load time), restated on 05i's records

8 instances, 100 m low-α cube, 96 kHz, until the last is audible: 19.5 / 16.3 / 23.0 s (05i record; the 05h record on
the same run 19.4 / 18.7 / 22.8 s; 05h's answer: decider file 36, recorded in AX38 (iv) with the remedy phase-07c
conditions 9 (or 07d) and 10, before the first release, phase-13 Raise item 3). The new records (file 3) add:
joint and room-size staleness, real-time staleness during an offline render (up to ≈ 44 s at 8 instances, 96 kHz,
100 m on the local box; CI values in file 3), the offline wait (linear in M), host-thread waits under contention. All
about linear in instance count (F-b).
The question: does 05h's answer stand unchanged for these records, or does any new record change it?

## Q4 — Raise item 3 (M-d)

Did not arise: every BRAS outer-band reference was produced on the session machine (file 2). Confirm it is recorded
as "did not arise", nothing for Maisara.

## Q5 — the solve-median bound k (phase-05h §5: "a bound proposed through `/fix-plan` once ≥ 3 runs give its spread")

Per-scene solve median (ms) on the three RG-1-form runs, with the run's flutter deviation from its reference:

| OS / scene | 42964823518 | 42975074716 | 43007183782 | mean | max / mean | min / mean |
|---|---|---|---|---|---|---|
| Linux low-α | 81.1 | 80.5 | 80.9 | 80.83 | 1.003 | 0.996 |
| Linux flutter | 130.9 | 130.6 | 131.2 | 130.90 | 1.002 | 0.998 |
| macOS low-α | 81.6 | 81.7 | 83.7 | 82.33 | 1.017 | 0.991 |
| macOS flutter | 105.1 | 82.5 | 102.7 | 96.77 | 1.086 | 0.853 |
| Windows low-α | 90.2 | 93.1 | 90.6 | 91.30 | 1.020 | 0.988 |
| Windows flutter | 143.8 | 149.6 | 145.0 | 146.13 | 1.024 | 0.984 |
| flutter deviation | L −16.8 %, M +10.1 %, W +0.9 % | L −19.6 %, M +19.4 %, W +43.6 % | L −3.7 %, M +2.4 %, W +1.3 % | | | |

The question: the form and value of k (e.g. a printed WARNING when the run's solve median exceeds k × the per-OS,
per-scene mean of these runs), whether it is printed or asserted on hosted runners (phase-05h §5 lists it under
"Printed with WARNING, never asserted"), and whether it is re-derived at the 07c re-pin (§5 says the solve bound is
re-derived from ≥ 3 in-window runs there). Note: only run 43007183782 is in-window on all three OSes; 05h's two runs
were out of window on Linux (and on Windows in 42975074716).
