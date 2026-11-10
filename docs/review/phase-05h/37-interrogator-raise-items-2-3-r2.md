# 37 — Interrogator: decider file 36 (Raise items 2 and 3), round 2 — SURVIVES WITH CORRECTIONS

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). The corrections are applied by the plan-editor in the same application as the records (orchestrator brief in the scratchpad; diff checked in file 38).

## Round 2: `docs/review/phase-05h/36-decider-raise-items-2-3-r2.md` (with Seat 7 file 35)

Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. Only new or revised items rated; nothing rated CORRECT in file 34 is reopened.

### Ledger

| decision | check | item | verdict | evidence | outcome |
|---|---|---|---|---|---|
| R2 | Q1 answer | AX38 4c's escalation covers the contended restore; "full-rebuild records" is the phase file's paraphrase | CORRECT | BUILD_PLAN L139 *Records* "alone and contended … the (iv) records", *Escalation* "the numbers"; phase-05h L100–104 is the narrower paraphrase | — |
| R2 | R2 table, full rebuilds / AQ4 / single load | all ranges | CORRECT | file 31 L124–127, L289–292, L351–354 (AQ4); L194–195, L201–202, L275–276, L282–283, L337–338, L344–345 (rebuilds); L142, L223, L312 and L139, L220, L309 (1-instance loads 2.39–2.53 s, 1.04–1.27 s) | — |
| R2 | R2 table, "restore alone … worst 2.06–2.67 s per OS" and the AX38 4c record line | lower bound | IMPRECISE | worst-of-10 restores: Linux 2.116 / 2.057 (L198, L205), macOS 2.669 / **1.852** (L279, L286), Windows 2.075 / 2.057 (L341, L348). Over both low-α cubes the range is 1.85–2.67 s; 2.06 is right only if the macOS s = 1 cube is dropped. Restate "1.85–2.67 s (low-α cubes; flutter 0.64–0.76 s, L191, L272, L334)" in the table and in the record line | correction |
| R2 | contended restore (F-a) | gated 2.04–2.13 s; s1 Linux worst 4.079 (others 2.033 / 2.047), macOS 1.805, Windows 2.069 | CORRECT | L200, L281, L343; L207, L288, L350 | — |
| R2 | F-b loads | 4 × 100 m 4.1–11.5 s; 8 × AQ10 3.9–8.9 s; 4 × AQ10 / 96 kHz 3.0–4.0 s; 8 × 100 m / 96 kHz 20.4–25.6 s; 48 kHz 7.8–11.1 s | CORRECT | L140, L143, L221, L224, L310, L313; L135, L138, L216, L219, L305, L308; L137, L218, L307 (macOS 3.029 s is the ≥ 3 s crossing); L144, L225, L314; L141, L222, L311 | — |
| R2 | F-b staleness maxima | 1.9–2.0 s; 3.0–9.5 s; 6.2–17.8 s; 3.5–4.0 s (Linux, Windows); 16.8–17.8 s | CORRECT | L142, L223, L312; L140, L143, L221, L224, L310, L313; L141, L144, L222, L225, L311, L314; L138, L308 (macOS L219 2.32 s below 3 s, as stated) | — |
| R2 | bounce / callback | ratios 0.23–0.32× and 0.73–1.22×; macOS 1-builder p99.9 2.2 ms | CORRECT | L128–129, L293–294, L355–356; L295 | — |
| R2 | PRD proxy | L101, NFR-2, NFR-3/FR-SIM-6, FR-3D-1, L42; four options each shown; veto reading | CORRECT | PRD L101, L106, L107/L89, L71, L42 | — |
| R2 | AMENDS | "No AMENDS (… the findings are record lines)" while a record line is appended to her AX38 4c row | INCONSISTENT with the row's own precedent | BUILD_PLAN L139 already carries `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition." (AX38 4c: a recorded finding, no rule change.)` for the D-H3 (e) finding; the same act here needs the same line. A label, not a reading change | correction |
| R2 | record line provenance | "(… decider file 33 R2)" | WRONG citation | file 33 R2 named no finding; the findings are file 36 §2 (after interrogator file 34). Cite "decider file 36 R2, revising file 33" | correction |
| R3 | Q2 answer | no plan line binds 07d before the first release; phase-13 item 4 binds the diffuse half; macOS entry may close at Phase 13 | CORRECT | phase-07c L37, L140–142; phase-13 L18–20; BUILD_PLAN L139 "or, if the runner is shown to be the cause, at Phase 13's release-machine re-check" | — |
| R3 | Q2 arithmetic | "the solve itself ≈ 0.1 s: 30.27 / 14 − 2.07" | IMPRECISE | 30.27 s is O18's recorded value, 2.07 this run's restore: two runs mixed; the register's own pair gives it cleanly: (30.27 − 28.9) / 14 = 0.098 s (BUILD_PLAN L139, Linux entry). Conclusion (8 × 2.0–2.7 ≈ 16–22 s) unchanged | correction |
| R3 | Q3 answer | no seat or plan text authorises a load-time figure; clause stripped | CORRECT | phase-13 L81–89 scope 6 owns the notes; AX38 (i) sentence is stop-stall only | — |
| R3 | Q4 answer | timed loop holds only prepare / beginRestore / restore; ratios 8.8× / 8.3× / 10.1×; excess +2.0 / +0.7 / +5.4 s | CORRECT | `test_diffuse_records.cpp` L644–651 (timer t0 → load before the staleness phase at L653); 21.078/2.386 = 8.83, 20.444/2.472 = 8.27, 25.618/2.528 = 10.13; 21.078 − 19.088 = 1.99, 20.444 − 19.776 = 0.67, 25.618 − 20.224 = 5.39. "phase-05i scope 2" exists (phase-05i L68) | — |
| R3 | Q5 answer | project load carries the saved E_b (5.1); import/edit takes 5.2's fallback, never silence; FR-3D-2 is import | CORRECT | phase-07c L114–121; PRD L72 | — |
| R3 | map (addendum) | (A) 0/1, (B) 1/2, (C) 0/1, reasons and the L35 conditions | faithful, word for word | file 35 L17–19, L22–24, L35; other eight at 0/0 | — |
| R3 | ordering (addendum) | bounds none; no 3; worst-off (B) max 2 out; compose (B)+L35 = (C) (seat's words); sum 1 = 1; reversibility (A) | CORRECT | decider.md §5 steps 4–6 (L238–245); file 35 L22 "(C) undo is a plan edit (hours)", (A) writes nothing; Seat 7's "by a hair" preference recorded, not applied | — |
| R3 | registers | Seat 7 rows (file, (A) later 1), Seat 6 hand-off (L38), Seat 5 hand-off (L39), P1 row (Seats 5, 7) | CORRECT; repaid-when phases exist | 07c L125–127 (condition 7), L140–142 (07d); phase-13 L15–20, L81–89; Phase 11 L340 | — |
| R3 | corrections from file 34 | 95.5 % of the non-diffuse restore; per-OS ratios; Seat 6 row → file 12 L52 / AX38 (iii); "condition 9, or 07d" everywhere | applied | file 36 L41, L53, L67–70 | — |
| R3 | PRD proxy | L101, NFR-2, NFR-1, NFR-6, L20, L42, L49; five options; veto reading; AMENDS line with its content listed | CORRECT; within remit (README item 1 "amendment … when the PRD calls for it", item 4) | PRD L101, L105–106, L110, L20, L42, L49 | — |
| R3 | AX38 (iv) addition | figures, L645–651, "one run each", two times, P1, 07d clause | faithful; one citation | cites "decider file 33 R3" only; the applied wording is file 36 §3 and the addendum. Cite "decider files 33 and 36 R3" | correction |

### Outcomes

**R2 — SURVIVES WITH CORRECTIONS.** The re-read is faithful to AX38 4c's Records list and every figure but one checks against file 31. Three edits before the plan-editor applies the record line: (1) "restore alone … worst 2.06–2.67 s" → "1.85–2.67 s (low-α cubes; flutter 0.64–0.76 s)"; (2) provenance "decider file 33 R2" → "decider file 36 R2, revising file 33"; (3) add `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition." (AX38 4c: recorded findings F-a, F-b, no rule change.)` to R2's Decided line, matching the row's precedent. With these the answer follows unchanged.

**R3 — SURVIVES WITH CORRECTIONS.** The notes clause is settled on Seat 7's cells with the map read word for word and the ordering applied as written ((A) by reversibility after a 1/1 tie); the AMENDS is within the decider's remit and carries its line; P1 is named and registered; the five answers hold against the sources. Two edits: (1) in the Q2 working replace "30.27 / 14 − 2.07" with the register's pair "(30.27 − 28.9) / 14 ≈ 0.10 s"; (2) the AX38 (iv) addition cites "decider files 33 and 36 R3". The addition is otherwise a faithful record and fit to apply verbatim after that edit.

No NEEDS MAISARA case arises; no research gap; no question for a further round.
