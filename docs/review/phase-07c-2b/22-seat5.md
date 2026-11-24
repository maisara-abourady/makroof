# 22-seat5: Seat 5 on the corner findings' home (M3-H material for Maisara)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION

**1. Reading.** Where the cause ruling on the three NFR-8 placement findings sits, judged on my row only: CI gates, ordering against 07d scope 8's growth re-pin, and how 08-4's freeze is held. Cues triggered: §4.5 (what crosses between phases, and who owns the baseline at each crossing); §2 criterion 4 (every gate automated and checkable); criterion 5 (keep the seams reversible); S5/criterion 2 (determinism across platforms).

**2. Ranking**
- **H4, with conditions G1–G3 (§6): prefer.**
- **H3: can live with.**
- **H2-c: can live with, at a major later cost.**
- **H1: can live with, at a major later cost. Ranked last.**

**3. Tension now**
- **H4: 0.** One S phase. Its CI cost is one pytest in the existing `python` job. Its render takes seconds [Hyp, not timed].
- **H3: 1.** It holds 08-1 and 08-2 without any gate of mine needing that: 08-1 (the converter) and 08-2 (the early part) read no tail state.
- **H2-c: 1.** It puts a Seat 2-led scope inside a phase that has no Lead and whose remaining scopes are mine (07d L6–7). The §0 status table tracks phases, not scopes, so CLAUDE.md step 3 cannot check a gate on "07d scope X done".
- **H1: 0.**

**4. Tension later (the debt)**
- **H4 as written: 2.** Two problems.
  - **(i) Ordering against the re-pin is left unrated.** 07d scope 8 re-pins from "≥ 6 green runs on the restore path in force (manual runs after 07d's last code change …)". It pools earlier runs only if the restore path is unchanged (phase-07d L94–96). A 07e-ruled fix to AX22's realised-k test changes the ISM list and the handover, so it changes restore work. If that fix lands after the re-pin, the baselines are void. Redoing them costs at least 6 more manual runs on three OSes, a CHANGELOG reason and a §6 row, and possibly Linux going back to the board (scope 8's reversal). The skeleton hands this to 07e's loop with no rating (interrogator file 20, hidden-premise row).
  - **(ii) The gate is on the freeze, not on the measurements.** 08-4's order is benchmark → grouping → S8–S10 (update time, W1/W2, AX38 (iv) records, heaviest-mode restore gate) → freeze, with "timing recorded on the post-grouping build only" (phase-08-4 L24–26). A fix that lands after 08-4's benchmark but before its freeze voids the whole measurement half of 08-4. The gate also lives only in the Notes column and in prose. A Seat 5-led 08-4 session checks its Depends list at start (CLAUDE.md step 3), not mid-phase prose.
  - **Evidence that could overturn this:** 07e's ruling. If it is "no breach", both debts are zero.
- **H3: 1.** Same as H4 on (i), unless it carries Seat 2's own definition ("before 07d's growth re-pin"). Point (ii) is solved because it blocks all of 08. Undo cost: delete one file.
- **H2-c: 2.** The plan already orders 07d before 08-4's freeze (07d L79–80, so file 20's O1 correction stands). But gating 08-3 item 15 and 08-4 on 07d `done` ties a deterministic report to a phase whose closure rests on hosted-runner timing:
  - the macOS (d) defect, with "≤ 3 extra manual runs" (scope 7);
  - Linux possibly "returns to this phase's board loop" (scope 8);
  - the macOS entry re-listed on one runner print (P07C1B-R1, run 43427854710).
  
  Runner flutter would then hold Phase 08's freeze. If a fix is ruled, 07d's scope 8 has to wait on a child fix phase, which forces a 07d/07d-b split. The ordering against the re-pin comes out right only if scope 8 sits after the item in the file.
- **H1: 2.** A fix at 13-2 comes after 07d's re-pin, 08-4's restore gate, W1/W2 and item 8. All of them would be re-measured, plus a second re-pin round. That is a phase of re-measurement, but no real-time safety breaks, so not 3.

**5. Evidence**
- Re-pin rule: phase-07d scope 8, L94–103 (plan text).
- 08-4 internal order and the post-grouping timing rule: phase-08-4 L24–26, L60–75.
- 07d before the freeze: phase-07d L79–80.
- "AX22 fallback changes the handover, so it changes restore work": from the code, Engine.cpp L138–157 (K15). That the work change moves restore time beyond the growth bound is [Hyp]: no measurement exists.
- CI: the `python` job runs on ubuntu-24.04, macos-15 and windows-2022 with `SPATIAL_REQUIRE_RENDER_CLI=1` (from the code, ci.yml L113–127). AX5 gives bit-identity only per OS and architecture (file 20, R2). The skeleton's "bit-identically" would therefore fail on two of the three OSes on its first run.
- No incident of my own covers golden-round cost (§12). The run counts come from the plan.

**6. Conditions of acceptance** (they bring H4 to 0/1, and H3 to 1/0)
- **G1:** in §0 row 08-4, put "07e `done` and the fix phase it rules, if any" in the **Depends on** text, not in Notes, so the gate holds at 08-4's start and before its benchmark. Extra cost is about zero: 08-4 already follows 08-3, whose item 15 waits on 07e.
- **G2:** add a line to 07d scope 8: "runs only after 07e is `done` and its fix phase, if any, is `done`; if 07d reaches scope 8 first, scope 8 splits to 07d-b". Also write into the 07e skeleton (scope 5) that a fix landing after a re-pin carries the re-pin (at least 6 green runs, a CHANGELOG reason and a §6 row) in its own acceptance criteria. That must be written now, not left to 07e's loop.
- **G3:** apply R2. The pytest asserts bit-identity on the OS and architecture that produced the values (Linux x64) and AX5's cross-architecture bound on macOS and Windows.
- **H2-c, from later 2 to 1:** gate 08-3 item 15 and 08-4 on a committed ruling artifact (an interrogator SURVIVES under `docs/review/phase-07d/`), not on 07d `done`, and place the item before scope 8 in the file. That is H4 under another name.
- **H1, to 1:** only through Seat 7's deferral clause, with the cause ruled before 08-4 starts.

**7. Hand-offs**
- Seat 2: whether a likely fix (AX40 constant vs AX22 test) changes restore work or only the level. If only the level, G2's re-pin debt falls to 0.
- Seat 7: the cost of a 07d/07d-b split under G2.
- Researcher: none.

**8. Premortem.** H4 ships without G1 and G2. 07d re-pins, then 07e rules an AX22 fix that lands mid-08-4. The growth check reds on its next manual run, and 08-4's restore-gate and W1/W2 records are found to predate the fix. The first to notice is the contracted engineer reading 08-4's PR timing against the fix commit.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/17-decider-m3-r4.md
- /home/user/makroof/docs/review/phase-07c-2b/20-interrogator-on-file17.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat2.md
- /home/user/makroof/docs/review/phase-07c-2b/14-seat7.md
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md (L1–40)
- /home/user/makroof/docs/phases/phase-07d.md
- /home/user/makroof/docs/phases/phase-08-4.md
- /home/user/makroof/docs/phases/phase-08-3.md (L1–5)
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L37–43)
- /home/user/makroof/.github/workflows/ci.yml (L113–132)

To be saved by the orchestrator as /home/user/makroof/docs/review/phase-07c-2b/22-seat5.md.
