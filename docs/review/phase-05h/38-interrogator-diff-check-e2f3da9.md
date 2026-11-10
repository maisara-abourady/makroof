# 38 — Interrogator: diff check of the plan-editor's application (commit e2f3da9: counts, AX38 4c/(iv) records, ledger) — DIFF OK

phase-05h (session 2). Verbatim interrogator output (the orchestrator saved it). Orchestrator: note 1 (the commit hash in the ledger status cells) waived as the interrogator suggests, matching the D-H3 block's precedent; note 3 (no in-row AMENDS for (iv)) left as applied, the §6 row and the ledger carry it.

**Diff-check of commit e2f3da9 (plan-editor application of brief sections A, B, C) — DIFF OK**

Corpus present (`docs/corpus/`, 14 files); not needed for this diff-check beyond the presence rule. Read at HEAD: `/home/user/makroof/docs/BUILD_PLAN.md` (L27, L28, L139, L144, L265, L464, L470, L471), `/home/user/makroof/docs/phases/phase-05h.md` (L289–296), `/home/user/makroof/docs/phases/phase-05i.md` (L52–94), `/home/user/makroof/docs/review/ledger.md` (L2239–2246); sources: the brief, file 36 §5 + addendum, file 37, file 31 L391–426.

**A. Counts (items 1–6) — all applied verbatim; every number agrees with file 31.**
- §0 row 05h (L27): "extended in three rounds to 482 certified case-bands: AX43 410 of 560 (all 28 cases at the 1.25 m rung; the 150 reported case-bands are the BRAS pairs' outer bands), AX45 72 of 72" ✓; the catch sentence "0.0080 dB over 70 case-bands / 0.0094–0.0098 dB over 40 against |mean (C++ − ref)| 0.0009–0.0012 / 0.0051–0.0057 dB); 26 … and 23 … no room labelled (worst |mean z′| 2.06)" ✓. File 31 L406–421, L426: band 3–5 bound 0.0080 over 70, means −0.0009/−0.0011/−0.0012; bands 0–2, 6–7 bounds 0.0094/0.0095/0.0096/0.0098/0.0098 over 40, means −0.0051…−0.0057; rooms 26/23; worst z′ −2.06 ✓. Carries sentence no longer names "§2 items 2 and 3" ✓.
- §0 row 05i (L28): "the per-instance restore times in the (iv) loop if 07c condition 7 does not print them;" ✓; "evaluated on the CI records" gone ✓.
- AX43 (L144): "(the final run of the 05h golden round, 410 of 560 gated; 5.4× and 4.4× inside AX46's 1 % = 0.043 dB" ✓ — 0.043/0.0080 = 5.375 → 5.4, 0.043/0.0098 = 4.39 → 4.4 ✓; "(410 / 560 and 72 / 72 … the 150 reported case-bands are the BRAS pairs' outer bands, phase-05i; growing)" ✓.
- §6 goldens row (L464) "AX43 410 of 560 after the session's last extension (W2 both emitters, the CS-NW+ emitter-1 placements and the 0.3 m wall case, the emitter-wall case; all 28 cases at the 1.25 m rung)" ✓; split row (L470) "482 certified case-bands" ✓.
- phase-05h §5 (L292–294) ✓ verbatim; phase-05i scope 1 (L55–58) ✓ verbatim, rest of item kept.

**B/C. Raise items 2 and 3 — applied verbatim with all five file-37 corrections.**
- AX38 (iv) (L139): "*Record (2026-11-10):* Recorded (CI run 42909003931 … fires on it." identical to file 36 §5, inserted directly after "…it goes to Maisara before the first release." ✓; citation reads "decider files 33 and 36 R3" ✓ (correction 4).
- AX38 4c (L139): record line inserted after the *Escalation:* sentence ("…by extension only.") ✓; provenance "(CI run 42909003931, 2026-11-10, decider file 36 R2, revising file 33)" ✓ (correction 2); "restore alone at 100 m / 96 kHz worst 1.85–2.67 s (low-α cubes; flutter 0.64–0.76 s)" ✓ (correction 1); F-a/F-b/remedy/bounce text word-for-word file 36 ✓; followed by `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c: recorded findings F-a, F-b, no rule change.) before *Hand-offs:* ✓ (correction 3, where the brief says).
- Q2 arithmetic ("30.27 / 14 − 2.07" or its replacement) appears in no plan file ✓ (correction 5: file 36 only).
- phase-05i scope 4 (L81–87) identical to brief item 9 ✓.
- §6 row (L471): identical to brief item 11 with both lines: "`AMENDS …` (AX38 4c: recorded findings F-a, F-b, no rule change) and `AMENDS …` (AX38 (iv))" ✓; source column names 33, 36; 35; 34, 37 ✓.
- Ledger block (L2239–2246): heading as specified; intro names files 33, 36, 35, 34, 37 and the corpus revision; nine-column table; P05H-R2 (PRD L101, NFR-2, NFR-3, FR-3D-1, L42; AMENDS AX38 4c; convening "no seat"; "files 33 → 36"; "34 PRD MISREAD → 37 SURVIVES WITH CORRECTIONS (applied)") ✓; P05H-R3 (AMENDS AX38 (iv); Seat 7 on the notes clause only, file 35; cells (A) 0/1, (B) 1/2, (C) 0/1 as file 36 addendum; "34 UNDERCONVENED → 37 SURVIVES WITH CORRECTIONS (applied)") ✓.

**Table rows:** BUILD_PLAN L27, L28, L139, L144, L464, L470, L471 and ledger L2245, L2246 are each a single line (L140 opens AX39, L145 opens AX44; ledger ends at L2247) ✓.

**Not applied / notes (none blocking):**
1. Brief item 12 says ledger status "applied" *with the commit*; both rows read "applied (AX38 4c record line; §0 rows 05h and 05i; §6 row; phase-05i scope 4)" with no hash. The plan-editor was told not to commit, so it could not know e2f3da9, and the D-H3 block precedent (L2226–2237) carries no hashes either. Optional fix if you want the brief read literally: append "(commit e2f3da9)" to both status cells — but that needs another commit; I would waive it.
2. Brief-prescribed wording leaves §0 row 05h at "≈ 0.009–0.010 dB elsewhere" and AX43 at "≈ 0.010 dB elsewhere"; both round from file 31's 0.0094–0.0098 dB and were dictated by the brief, so not a departure.
3. The AX38 row itself carries the 4c AMENDS line (as the brief asked) but no in-row AMENDS line for (iv); the (iv) line lives in the §6 row and ledger only. The brief did not ask for one in the row, so not a departure; flag only if you want parity with the 4c precedent.
4. §6 L465 still says "'at the time of writing' counts 330 / 560" — a historical D-H3 log row, outside the brief; correct as a record of that application.

Verdict: **DIFF OK**. No applied text departs from its source; no source item unapplied; every number agrees with file 31 and file 36; no table row broken; the 4c AMENDS line sits after the record line and both AMENDS lines sit in the §6 row and the ledger rows as the brief directs.
