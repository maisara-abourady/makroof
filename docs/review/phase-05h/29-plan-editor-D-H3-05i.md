# Plan-editor report — D-H3 (a)–(e), H3-F1…F6 and the phase-05h split

Nothing committed. `docs/PRD.md`, `docs/review/ledger.md`, `src/`, `tests/`, `tools/`, `docs/contract/` untouched (verified with `git status`). Every value and wording below comes from decider files 25/27 and interrogator files 26/28 (with file 20 where 25 says "as file 20"); I made no acoustic or numeric choice. All anchors were replaced by exact-substring with a uniqueness assert; table rows re-checked (AX rows 4 columns, §0 rows 7, §6 rows 3; the extra `|` counts on rows 05/05e/05f/05h are pre-existing escaped `\|` in text).

## Applied

**/home/user/makroof/docs/BUILD_PLAN.md**
1. **§2 AX43** — the pooled clause "pooled bias check per band, |mean z| ≤ 3/√M" → file 27's exact (f9) wording with file 28's restatement 2 (catch "≈ 0.008 dB at 500 Hz–2 kHz and ≈ 0.010 dB elsewhere … at the time of writing (the application run; 5.5× and 4.4× inside AX46's 1 % = 0.043 dB; within Seat 1's 0.02 dB; ≤ 1/100 of G's 1 dB jnd)") and restatement 4 (the > 3 label's reach ≈ 0.023 dB at dead_booth; the +0.017 dB case printed mean z′ +2.16, visible not labelled; between ≈ 0.01 dB and the label the watch is the table and the sign count; reopen route a board round to (e′)); one reading of ℓ_ref; no count; the `room` column rule (`room_of`: W1 and W2 each one room over emitters and placements, CS-NW+ under W1); the Phase 13 quote rule. The CI-reports line gains cause / movability / tail level (file 20). Rationale: the D-H3 (a) / H3-F1 loop citation (files 16, 17-seat*, 17-researcher-RQ-H3-1/-3, 18, 20, 25, 27, 22, 26, 28; max 1, sum 7), the application evidence per restatement 1 (agree_full5: all eight bands within, 0.0046–0.0047 vs 0.0096–0.0099 dB at bands 0–2/6/7, 0.0000–0.0002 vs 0.0077–0.0078 dB at bands 3–5), the dead_booth / AX36 note with restatement 3's per-band interplay and ratio 1.50–1.63 (restatement 6), the H3-F6 application note (four small rooms at 0.625 m; dead_booth ℓ_ref 0.17 → 0.28 %; the AX36 caveat carried to that rung), AMENDS lines for H3-F1 and H3-F6; reversal gains the (f9) and H3-F6 conditions with restatement 5's "a later room set (05i, or its owner phase)". "At the time of writing" counts 274 / 560 and 40 / 72 → 330 / 560 and 72 / 72 (from the committed §6 goldens row).
2. **§2 AX36** — rationale gains the caveat (the < 1 % per-halving rule passed dead_booth's 1.25 m rung while the ladder still accelerates, ratio 1.50–1.63, applies at 0.625 m too; Seat 9's cause; the other rooms converge) and `AMENDS her decision of 2026-11-09` (note only). Rule text unchanged.
3. **§2 AX44** — after Seat 6 (ii): the H3-F2 Reading (user-reachable rooms and presets; the two contract-limits fixtures named by the golden's pinned U, the cause line prints the cause; the golden is the list; reversal not triggered; the display rule keyed on AX37 (5.4)'s kept check (broadband energy after the direct peak + 50 ms over the peak's squared amplitude) with E_target raised by 3·SE, never a name; −85 / −30 / −16 / +7 dB measured; C1's '> 44 dB' a different quantity, no margin moved; the CI report). The cap-flag clause → H3-F4's exact wording (layout4_s1/both_corner asserts the cap; W1 both_corner asserts U with flags pinned as records-test constants, file-13 provenance, re-pinned with a CHANGELOG reason; five flags per fixture in the D5 golden; Q-3 recorded once). Rationale: loop citation, both AMENDS lines (H3-F2, H3-F4); reversal reads "a user-reachable room or preset" and adds file 25's Phase 12 condition.
4. **§2 AX41** — the J1 clause (a capped near-zero total below the −60 dB line does not reopen J1; `courtyard` tested as a room); the "pilot ships" list notes `edge_values` at the time of writing, kept current in 05i; rationale: H3-F2 citation and AMENDS (AX41 J1 clause).
5. **§2 AX38 (i)** — class (1) gains a pointer to the corrected premise; the old "Open check (P05B2-T5T4-61)" sentence replaced by file 20 L274's text with file 25's two replacements (release rule "no build reaches a producer outside the team (beta included) while this entry is open"; the remedy's "(which also shorten every quiesce: restore, prepare, release and the destructor)"), cross-referenced to phase-07c conditions 10 and 11; the old "about-two-solves bound needs tightening" consequence kept as the last sentence. **AX38 4c** — the K-e12 finding inserted beside the unit-decay-synthesis finding with file 27's corrections (≈ 4.8 s per restore, 14 such ≈ 67 s; `test_diffuse_records.cpp` L422; record task 05h or 05i; remedy 07c 9 and 10; H1-F1 not widened). Rationale: D-H3 (e) citation, both AMENDS lines, reversal additions from file 25's summary; breaks column adds 05i and 07c.
6. **§0 row 05h** — session-2 note rewritten from the brief's facts (switch/gate/seam landed; D-H1/D-H2/D-H3 decided with file numbers; the golden round: 402 certified case-bands, AX43 330 of 560, AX45 72 of 72, four small rooms at 0.625 m, D5 golden bit-identical; the application run's catch figures and 25 / 22 room counts "at the time of writing"; local records: transient RSS ≤ 297 MB at 96 kHz, realised work 0.935 / 0.991, restore register baseline-pending, quiesce worst 2 664 ms with the AX38 (i) entry and counter, callback p99.9 and the 3-minute bounce 0.47× / 1.33× on a loaded box; D-H3 (c)'s FTZ facts; status stays `in progress` until CI; remainder → phase-05i).
7. **§0 row 05i** (new, after 05h): `not started`, depends on 05h, the five carries. **§4** entry for 05i (see Interpretations).
8. **§6** — six rows dated 2026-11-10: (a)/H3-F1+H3-F6; (b)/H3-F2; (c)/H3-F3; (d)/H3-F4; (e)/H3-F5; the split. Each cites the files 16, 17-seat*, 17-researcher-RQ-H3-1/-3, 18, 20, 22, 25, 26, 27, 28, corpus c1b171f, and "no golden changed by this edit".

**/home/user/makroof/docs/phases/phase-05h.md** — header notes the split; §2 items 2 and 3 note 05i (scope 4) if the records are not in 05h's CI run; §5 agreement bullet: the additive pooled check, the printed forms and the application condition, counts 330 / 560 (four small rooms at 0.625 m); AX45 bullet 72 / 72; the U bullet: asserted by the D5 golden, pinned at every fixture, the two contract-limits fixtures named by the golden's pinned U with the cause line, layout4_s1/both_corner asserts the cap, W1 both_corner's flags pinned; the FTZ bullet: the named absorbent room (dead_booth geometry, α 0.01 at 63 Hz / 0.999 above, s 0.5), flag per architecture, probe standing in `ci.yml`, pool shares under the guard, re-probe, (f) fallback; the gate bullet: the AX38 (i) register entry with K-e6's numbers, the counter, remedy 07c condition 10, the release rule; the records bullet: the K-e12 record task and the (iv) records → 05i; §8: "room or preset fixture" (file 20) and the split applied. §9 unchanged.

**/home/user/makroof/docs/phases/phase-07c.md** — §0 gains a D-H3 (e) scope-extension paragraph; §5 heading "conditions 1–11"; conditions 10 (the `reset()` half, exactly file 25's DECISION: (e-k) + (e-e), the no-wait/no-build `[pipeline]` test, first step with its own TSan round, the two-order test, the transient-memory record, closes AX38 (i)'s entry) and 11 (the `SPATIAL_HOST_TRACE` build, the per-host run a person's action, results to Phase 13); §6 gains two mirror criteria. §9 untouched (file 25 names only phase-05h §9 as unchanged).

**/home/user/makroof/docs/phases/phase-11.md** scope 8 — the display rule (file 25 wording with file 27's quantity clause), the measured levels, Seat 7's sentence as the text candidate (Seat 6 owns the words).

**/home/user/makroof/docs/phases/phase-12.md** scope 7 — the outdoor-presets / J1 bullet (the cause clause, `courtyard` as a room, the per-preset cause / movability / tail-level report, the display rule reference).

**/home/user/makroof/docs/phases/phase-13.md** — scope 6: the host matrix receives the condition-11 trace results, the interim sentence; scope 8: Windows-on-ARM runs unguarded (MSVC ARM64 guard a no-op, FTZ test SKIPs); scope 13: the accuracy-wording rule in Seat 7's (f9) sentence form (placeholders for the per-run figures, since the row says they are restated each golden round).

**/home/user/makroof/docs/phases/phase-05i.md** (new, 135 lines) — "Tail-level switch: remainder of 05h": Size M, depends on 05h; §1 settled; §2 Raise with Maisara (05h's items 2 and 3 conditional, evaluated by the decider for her; M-d as an action); §3 scope carrying exactly brief items (i)–(v); §4 acceptance; §5 no new listening items; §6–§9.

**Ledger block (not pasted):** `/tmp/claude-0/-home-user-makroof/cf3cd1bc-38f5-5108-9ecd-3edbb820be39/scratchpad/ledger-block-phase-05h-dh3.md` — header in the D-H1/D-H2 block's form (question file 11, convening 16, seats 17-seat*, researchers, decider 20/25/27, interrogator 22/26/28, corpus c1b171fe649f07cbeb952ef1f75d89bfaa414d0d, where applied) and rows P05H-D-H3-a…e, P05H-H3-F1…F6, P05H-split-05i.

## Held
- **`docs/phases/phase-07.md` L135–141** — file 20 L274 names a one-sentence correction there ("runs on the thread the host calls `reset()` on … not concurrent with `processBlock`" → "may run on the VST3 processing thread (AX38 (i), D-H3 (e)); not concurrent with `processBlock` (one processing thread, F4, F21), but not on a thread that tolerates a wait or a build"). Not applied: phase-07 is a `done` phase and not in the brief's file list. Wording only; the orchestrator can apply it verbatim or leave it.
- Code-side items named by the decisions (test comments, `ThreadPool.h` convention line, the `ci.yml` probe) are the orchestrator's, not mine.

## DECISIONS NEEDED
None. Every acoustic and numeric value was supplied by files 25/27/28.

## Interpretations (non-acoustic)
1. "phase-05h §0 notes" read as the BUILD_PLAN §0 row 05h notes column (the status table), as AX38's "Register entry (phase-05h §0; the W-x form)" uses it; written into the row-05h rewrite.
2. Phase 05i **Size M** (the brief gives none).
3. A **§4** entry for 05i added for consistency with the 05b split row ("new row and §4 entry"); the brief asked only for the §0 row.
4. "At the time of writing" counts in AX43 and phase-05h §5 updated to 330 / 560 and 72 / 72 (from the committed §6 goldens row) so they agree with the new §0 row; they are labelled as of the session-2 golden round.
5. phase-07c §6: two mirror acceptance criteria for conditions 10 and 11 (software-only; the run itself stays a person's action and does not gate).
6. The host list in AX38 (i) half (2) and phase-07c condition 11 is copied from file 20 L274 (Live 12, Logic, Cubase, Bitwig, REAPER, FL Studio, Studio One — seven names); the brief said "six hosts". I kept the decision text.
7. Phase 13 scope 13's accuracy sentence uses placeholders for the per-run figures, since AX43 says the catch is restated each golden round and never pinned.
8. phase-05h §8's "valid fixture" → "room or preset fixture" applied from file 20's plan-texts list (file 25: "Plan texts as file 20").
9. The AX38 (i) "about-two-solves bound needs tightening" consequence of the old open check was kept as the closing sentence of half (2), since the decision replaces the check's form, not that consequence.

## git diff --stat
```
 docs/BUILD_PLAN.md       | 27 ++++++++++++++----
 docs/phases/phase-05h.md | 72 +++++++++++++++++++++++++++++++++++++++---------
 docs/phases/phase-07c.md | 47 ++++++++++++++++++++++++++++++-
 docs/phases/phase-11.md  | 11 ++++++++
 docs/phases/phase-12.md  | 11 ++++++++
 docs/phases/phase-13.md  | 20 ++++++++++++--
 6 files changed, 166 insertions(+), 22 deletions(-)
```
plus untracked `docs/phases/phase-05i.md` (135 lines).
