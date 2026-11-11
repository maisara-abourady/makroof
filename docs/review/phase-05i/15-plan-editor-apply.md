# 15 — Plan-editor: verified texts applied (phase 05i, /fix-plan step 4)

Phase 05i, 2026-11-11. Applied only the texts named in the brief: decider file 9 (Q2, D-Q5), file 11 (Q3 blocks 1, 3, 4, as modified by file 13's preamble), file 13 (D-G1 blocks 1–9, G1-C1), with interrogator file 14's corrections 1–8 as resolved in the brief, and the phase-05i §3.6 bookkeeping (facts from files 2 and 3). `docs/PRD.md` not edited. §0 row 05i (status, SOLVE counts) and the AX38 4c closure of the Linux/Windows low-α entries (Q1) not applied: they wait for the PR's CI run of record.

## Edits

### docs/BUILD_PLAN.md

| # | location | old → new (gist) | source |
|---|---|---|---|
| B1 | AX38 4c, K-e12 finding (end: "…not a gate failure.") | appended the *Record (phase 05i, CI run 43007183782)* paragraph verbatim (worst / median 3 276 / 2 370, 2 648 / 1 967, 3 231 / 2 377 ms; idle; flutter; remedy unchanged) | file 9 Q2 |
| B2 | AX38 4c, record against the anchors, after F-b | inserted "(F-a and the 05i contended host-call records: see register entry G-1, AX38 (i).)" | file 11 Q3 block 3 |
| B3 | AX38 4c, record against the anchors, after "Remedy for both … (D-H1 (v)(d))." | one line: K-e12 above 3 s on Linux / Windows (3 276 / 3 231 ms; macOS 2 648 ms), CI run 43007183782, see the K-e12 finding | file 9 Q2 ("one line … citing the same") |
| B4 | AX38 4c RG-1 "Printed with WARNING" | "(a bound proposed through `/fix-plan` once ≥ 3 runs give its spread)" → the D-Q5 bound parenthesis verbatim (`kSolveWarn` 1.20 × in-window baseline; baselines; PROVISIONAL; never asserted …) | file 9 D-Q5 |
| B5 | AX38 (iv), after the 2026-11-10 record ("…phase-13 item 3 fires on it.") | appended the *Record (phase 05i, CI run 43007183782)* paragraph; "G-1's route: D-G1" → "G-1: AX38 (i) register entry G-1, remedy phase-07c-1 condition 12 (D-G1)" | file 11 Q3 block 1; file 13 preamble |
| B6 | AX38 (i) open check, after half (2) ("…the about-two-solves bound needs tightening.") | new paragraph "**Register entry G-1, gate scope** …" with its own release rule; "flat from 4 to 8" → "not growing from 4 to 8 instances (flat on Linux and Windows; lower at 8 on macOS)"; instance cap cited to PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5, D-H1 (v)(d) kept for W_max cut, range change, seam; interrogator `<next>` → 14 | file 13 block 1; file 14 corrections 2, 3 |
| B7 | AX38 4c *Records* | after "callback p99.9 at host buffer 64 with 1, 4 and 8 concurrent builders" inserted "(builders serialised by the gate under AX38 (i) register entry G-1; re-taken with concurrent builders by phase-07c-1 condition 12)" | file 13 block 2 |
| B8 | AX38 (iii) | sentence replaced by G1-C1's wording, plus file 14 correction 8's sentence (queued/building = `dirty_ != handled_`; crossfade = `CrossfadingConvolver::isFading()`; exposure and "IR going live" are phase-10-2's, scope 3), plus the AMENDS line | file 13 block 3 / G1-C1; file 14 correction 8 |
| B9 | §4 Phase 11 "From phase 05b (AX38, AX44)" (old L359) | "settling" on every instance waiting at the gate → "…whose latest change is not yet audible (queued at the gate, building or crossfading)…" | file 13 block 3 |
| B10 | §0 row 07c-1, notes | appended "Condition 12 (D-G1, 2026-11-11): the AX38 gate narrowed to the solve, after condition 10, before 9; closes AX38 (i) G-1." | file 13 block 7 |
| B11 | AX43, catch | "(≈ 0.008 dB at 500 Hz–2 kHz and ≈ 0.010 dB elsewhere … 410 of 560 gated; 5.4× and 4.4× inside …" → "(≈ 0.008 dB in all eight bands (0.0079–0.0081 dB over 70 case-bands per band; \|mean (C++ − ref)\| 0.0008–0.0012 dB), 26 reference rooms in every band, rooms of both signs, no room labelled (phase 05i, CI run 43007183782); 5.3× inside …" | brief item 5; file 2 (5.3×) |
| B12 | AX43, report counts | "(410 / 560 and 72 / 72 at the time of writing … the 150 reported case-bands are the BRAS pairs' outer bands, phase-05i; growing)" → "(560 / 560 and 72 / 72 since phase 05i, which gated the 150 BRAS pairs' outer case-bands (63, 125, 250 Hz, 4, 8 kHz); 410 / 560 after the 05h session-2 golden round)" | brief item 5 |
| B13 | AX45 | "72 / 72 at the time of writing, after the 05h session-2 golden round (40 / 72 before it)" → "72 / 72 since the 05h session-2 golden round (40 / 72 before it), unchanged in phase 05i" | brief item 5 |
| B14 | AX46 | "BRAS pairs (500 Hz–2 kHz, outer bands as 05i certifies)" → "(500 Hz–2 kHz from phase 05h; the outer bands certified in phase 05i, all eight bands)" | brief item 5 |
| B15 | §6, four rows | D-Q5 (decider 9, Seat 5 8, interrogator 10); Q3 (decider 9/11, interrogator 10/14; "route D-G1" → "remedy phase-07c-1 condition 12 (D-G1)"); D-G1 + G1-C1 (block 9; interrogator 14, corrections listed); AX43 outer bands (brief item 5 text, source file 2) | files 9, 11, 13, 14; brief |

### docs/phases/phase-05h.md

| # | location | old → new |
|---|---|---|
| H1 | §5 agreement "Scope now" | "410 / 560 at the time of writing … the 150 reported case-bands the BRAS pairs' outer bands" → "560 / 560 since phase 05i, which gated the 150 BRAS pairs' outer case-bands; 410 / 560 after the session-2 golden round …" |
| H2 | §5 bias check | "outer bands as 05i certifies" → "the outer bands certified in phase 05i, all eight bands" |
| H3 | §5 AX45 "Scope now" | "72 / 72 at the time of writing, after the session-2 golden round" → "72 / 72 since the session-2 golden round, unchanged in phase 05i" |
| H4 | §5 "Printed with WARNING" | "(a bound proposed through `/fix-plan` once ≥ 3 runs give its spread)" → "(bound: AX38 4c, set in phase 05i)" (D-Q5) |

### docs/phases/phase-05i.md

| # | location | old → new |
|---|---|---|
| I1 | §3.3 (iv) | appended "(set in 05i: AX38 4c, decider file 9)" (D-Q5) |
| I2 | §3 scope 2, end | appended the "**Gate-wait split (D-G1, decider file 13)**" paragraph; per file 14 correction 5 the poller polls `waiting()` (Synchronous and Offline) and reads `solvesCompleted()`; it does not read `held()`; code named: `measureGateWait` in `tests/unit/test_diffuse_records.cpp` (file 13 block 8) |
| I3 | §4, second criterion | "The AX38 (iv) records of scope 2" → "… of scope 2 (with the gate-wait split)" (block 8) |

### docs/phases/phase-07c-1.md

| # | location | old → new |
|---|---|---|
| C1 | "Conditions (…)" heading | appended "; condition 12: D-G1, phase 05i, decider file 13" (block 6) |
| C2 | condition 4, first bullet | `The UI shows "settling" (AX38 (iii))` → `… "settling" while the update is pending (AX38 (iii) as amended 2026-11-11, G1-C1)` (block 3) |
| C3 | new condition 12 after condition 11 | block 4 verbatim except: (c) and (f) instance-cap bar cited to PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5 (correction 3); (g) "read by extension against Table 15.1's two rows …" → the joint step's +0.5 m listener move read against the 700 ms row only (binaural processing plus the specular part); the 3 s row (translational move > 1 m, specular plus scattering part) applies to none of these records (correction 1); (b) unchanged "phase 05i's gate-wait split, run unchanged" (correction 7) |
| C4 | A3 | "while a solve is pending" → "while an update is pending (AX38 (iii))" (block 3) |
| C5 | new A12 after A11 | block 5 verbatim |
| C6 | F1 | block 6 wording |

### docs/phases/phase-07c.md (block 7 with correction 6)

§5 heading "conditions 1–11" → "1–12" plus "; condition 12: D-G1, phase 05i, decider file 13"; after the conditions paragraph (old L88–90) "Condition 12 (D-G1, added 2026-11-11 by phase 05i: the gate narrowed to the solve) is in phase-07c-1."; §6 sentence adds "and A12 (condition 12, added 2026-11-11 by phase 05i: D-G1)"; sub-phase table 07c-1 "owns" cell "conditions 9–11 (…)" → "conditions 9–12 (…, the gate narrowed to the solve)"; "Where the original items went": labels line adds "A12 added 2026-11-11 by phase 05i", and new row "| condition 12, A12 (added 2026-11-11 by phase 05i: D-G1) | 07c-1 |".

### docs/phases/phase-10-2.md (block 3; correction 8)

Scope 3: "the same wait drives Phase 11's "settling" state" → "the staleness (gate wait included) drives Phase 11's "settling" state", plus one sentence: whether "the IR going live" is the submit or the end of the AQ4 crossfade, and how the crossfade state (`CrossfadingConvolver::isFading()`, the audio thread's) is exposed to the UI, is defined here (AX38 (iii), G1-C1).

### docs/phases/phase-11-3.md (block 3)

Scope 3: "shown on every instance waiting at the diffuse-solve gate, project load included" → "shown on every instance whose latest change is not yet audible (queued at the gate, building or crossfading; Phase 10's staleness above zero), project load included".

## Not applied (by instruction)

- §0 row 05i (status; the D-Q5 SOLVE count per OS) and the AX38 4c Q1 closure of the Linux / Windows low-α entries (file 9 "Text for the plan-editor (Q1)", its §6 row): wait for the PR's CI run of record.
- §0 row 05h's counts (scope 6 lists them; the brief did not): left for the done bookkeeping.
- `tests/golden/CHANGELOG.md` and test code: out of the plan-editor's remit (already committed on the branch, f216a9c).
- File 11 Q3 block 2: replaced by file 13 block 1, as instructed.

## Interpretations (non-acoustic)

1. §6 rows written in the table's three columns (Date | Change | By): "05i" folded into the Change cell as "**Phase 05i:** …", the sources into By, as recent rows do.
2. "Finding G-1" in Q3 blocks 1 and 3 written as "register entry G-1", because file 13 block 1 records G-1 as a register entry; the decider's §6 row (block 4) keeps "finding G-1 … recorded" as written.
3. Block 1 placed after the open check's half (2) and not directly after half (1)'s release rule, so that the two halves stay together; "the team as above" still refers to the team definition above it.
4. Q2's one line in the record against the anchors was placed after the "Remedy for both … (D-H1 (v)(d))." sentence, so that "both" still means F-a and F-b. The line repeats the decider's figures only.
5. AX43 catch: AX46's ratio changed from "5.4× and 4.4×" to "5.3×", as file 2 gives it (0.043 / 0.0081 dB). The "within Seat 1's 0.02 dB; ≤ 1/100 of G's 1 dB jnd" clause is kept.
6. Correction 5: the code polls `waiting()` at about 1 ms and reads `solvesCompleted()` before and after the call, so the text says "reads `solvesCompleted()` around each call" rather than "polls" it.
7. Corrections 4 and 7 needed no text: no plan text says that narrowing "stops lag growing", and no block carries the timing fallback.
8. Wrapping: the new paragraphs were reflowed to the files' line widths. One line break was moved so that no line in a list item starts with ">" (which would render as a blockquote).

## DECISIONS NEEDED

None.
