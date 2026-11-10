# Interrogator — document mode, round 2 of the /fix-plan diff check (19cabdb..6e4e6ee)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, document mode, round 2 of the /fix-plan diff check (`git diff 19cabdb HEAD -- docs/BUILD_PLAN.md docs/phases/`)

The edits are faithful. File-41 corrections 2–8 are applied as worded. D-H1 records correction 1 faithfully. `phase-05h.md` carries phase-05b2 §4–§10 and AX37–AX46 with nothing dropped, and it keeps the atomicity rule and the "nightly BRAS green before the PR" rule.

Four small items remain, all for the plan-editor or orchestrator. The one that matters is the §0 row 05b: it is set to `done` before a PR exists and before CI has run, which CLAUDE.md does not allow.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

I checked the changed passages only.

### Verdicts per passage

| passage | verdict | note |
|---|---|---|
| File-41 correction 2 (AX41 cost line at n\*_max 1 024) | CORRECT | 0.13–1.33, 0.09–0.10, 0.09–0.15 and 0.44–0.50 dB all match C16 (f) |
| Correction 3 (restore-gate scenes named in AQ10 and AX38 4c) | CORRECT | the AX22-fallback (flutter) scene and the closed low-α cube |
| Correction 4 (B15 "flagged by U where it fires") | CORRECT | |
| Correction 5 (AX37: 0.08 dB with its conditions; 0.088 dB moved to AX39) | CORRECT | |
| Correction 6 (AX36 (c), B11, phase-05b: R1 conditions) | CORRECT | 500 Hz–2 kHz, AX28 / Phase 05 positions; not certified near walls (4.75 / 5.3 / 8.7 %); bears only on ℓ_ref |
| Correction 7 (AX16, C16 (g) marked 1 kHz) | CORRECT | |
| Correction 8 (AX38 4b "AQ10's 50 ms target is unchanged") | CORRECT | |
| AX44 "absent at α = 1", marked as derived from Eq. 2.49's R = 1 premise | CORRECT | matches Kuttruff L1542–1544 |
| D-H1 (phase-05h §3) and its pointer sentences in AQ10 (1), AX38 4c and AX41 | CORRECT | faithful to correction 1 |
| phase-05h §0 and §1 (settled list) | CORRECT | matches AX37–AX46, AX36 (c) (CR4 0.140 %, report-phase05b §5b), D-T3 not needed, Q2a (C) in phase-13 |
| phase-05h §2 item 2 | IMPRECISE | correction 2 |
| phase-05h §4 items 1–9 | CORRECT | items 2–9 of phase-05b2 §4 carried over; R1 (item 1) correctly left out as resolved |
| phase-05h §4 item 10 | CORRECT, one addition | correction 3 |
| phase-05h §5 | CORRECT | see check 1 below |
| phase-05h §6, §7, §9, §10 | CORRECT | see check 2 below |
| phase-05h §8 (atomicity) | CORRECT | the matching change lands in one push with the agreement test, the tracer test and the goldens; PR only after a green manual nightly BRAS run on that push. Split to 05i follows the CLAUDE.md two-session rule |
| §0 row 05h, the §4 entry 05h, phase-08 dependency (05h, with the AX37 (5.3) exception), phase-13 dependency, phase-11 pointer, break columns | CORRECT | matches phase-05b2 §8 and the recorded D-T5.3 exception |
| phase-05b2 header note (§4–§10 kept as record) | CORRECT | |
| §0 row 05b set to `done (not promoted; tail-level switch specified in phase-05h)` | CONDITIONS VIOLATED (CLAUDE.md "one rule", step 6) | correction 1 |
| §6 rows (plan-diff check; split) | CORRECT | both state "no value, threshold or golden changed" |

**Check 1 (phase-05h §5).** Every phase-05b2 §5 criterion is present except the two already met: "decisions recorded as AX rows" and R1. The additions all come from sources:
- the D-H1 item (correction 1);
- the AX41 diagnostics test (from AX41's diagnostics list);
- the blocking-gate item naming its scenes, "with D-H1's margin".

**Check 2 (phase-05h §6, §7, §9, §10).**
- §6 is identical to phase-05b2 §6.
- §7 replaces "room-range edge (D-T3)" with "memory scaling at 100 m": correct, since D-T3 is not needed. It adds D-H1.
- §9 adds B15 and Q2a (C): both consistent with §5 and phase-13.
- §10 is the 05h row.

### Corrections

1. **§0 row 05b status (bookkeeping, orchestrator).** CLAUDE.md step 6 sets `done` only when every automated acceptance criterion passes in CI, with the PR link and the date filled in. phase-05b2 §8 names the status, `done (not promoted; …)`, to be set when the 05b PR closes both sessions' work. The row now says `done` with an empty PR column and the start date (2026-11-08), and the §6 row defers "PR and date for the orchestrator". Either keep `in progress` until the 05b PR's CI passes, or fill in the PR link, CI run and done date before the session reports.

   Minor: the row's notes repeat the session-2 sentence twice ("Session 2 decisions D-T1…D-T6 accepted …" and "Session 2 (2026-11-10): decisions AX37–AX46 …"); delete one.
2. **phase-05h §2 item 2 (IMPRECISE).** "The AX38 4c escalation (conditional on the C++ records)" can be read as "only if a limit is exceeded". In AX38 4c the escalation is unconditional: "the numbers go to Maisara against 1 s, 3 s and 10 s". Only "any room above 3 s is named as a finding" is conditional. Write "when the C++ records exist".
3. **phase-05h §4 item 10 (new detail, not in the source).** "Phase 08's listening items on concentrated absorption, marked provisional there, are re-listened" goes beyond Seat 4's (iii) in AX37 (5.3), which covers re-rendering the binaural goldens, re-measuring binaural W1/W2 and re-running item 8. Condition (iv) only marks the listening items provisional. Harmless and sensible, but either mark it as the plan-editor's addition or move it to the listening checklist (§6) so it is not presented as a decided condition.
4. **Dependency note (no change needed).** 05h depends on 05b, 05f and 07. 06 is covered through 07, and 05e through 05f; that holds only if 05f's own dependency on 05e is recorded.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-FX-18 | File-41 corrections 2–8 applied as worded (AX41, AQ10/AX38 4c scenes, B15, AX37, AX36 (c)/B11/phase-05b, AX16, AX38 4b, AX44 derived note) | CORRECT | closed |
| P05B2-FX-19 | D-H1 (phase-05h §3) and its pointers in AQ10, AX38 4c, AX41 faithful to correction 1 | CORRECT | closed (P05B2-FX-08 stays open until D-H1 is decided) |
| P05B2-FX-20 | phase-05h faithful to phase-05b2 §4–§10 and AX37–AX46; atomicity and nightly-green-before-PR kept | CORRECT | closed |
| P05B2-FX-21 | Split bookkeeping: row 05h, §4 entry, phase-08/-13 dependencies with the AX37 (5.3) exception, phase-05b2 header note | CORRECT | closed |
| P05B2-FX-22 | §0 row 05b `done` set without PR link, CI evidence or done date (CLAUDE.md step 6); duplicated session-2 sentence | CONDITIONS VIOLATED (bookkeeping) | open (orchestrator) |
| P05B2-FX-23 | phase-05h §2 item 2 "conditional" escalation, against AX38 4c's unconditional escalation | IMPRECISE | open (/fix-plan) |
| P05B2-FX-24 | phase-05h §4 item 10 re-listening clause not in AX37 (5.3) | IMPRECISE (addition) | open (/fix-plan) |

Files:
- /home/user/makroof/docs/phases/phase-05h.md
- /home/user/makroof/docs/phases/phase-05b2.md
- /home/user/makroof/docs/BUILD_PLAN.md (§0 rows 05b/05h, AQ10, AX36–AX46, §4 05h entry, B11, B15, §6 rows)
- /home/user/makroof/docs/phases/phase-08.md
- /home/user/makroof/docs/phases/phase-13.md
