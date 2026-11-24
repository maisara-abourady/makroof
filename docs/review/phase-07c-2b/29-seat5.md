# 29-seat5: Seat 5 on M3-H (brief B5)

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (brief B5, follow-up to 22-seat5; the orchestrator saves this as /home/user/makroof/docs/review/phase-07c-2b/29-seat5.md)

**1. Reading.** This is my follow-up on M3-H. I rate H2-cg and H4+G, give the exact texts for G1 and G2, answer how G3 names the producer platform, and say whether H4+G holds back 07d's scopes 6 and 7. The cues I apply:
- §4.5: what crosses between phases, and who owns the baseline at that crossing.
- Criterion 4: a gate must be checkable mechanically. CLAUDE.md step 3 checks §0 status rows only.
- Criterion 2 and AX5: determinism on each platform.
- Criterion 5: the seams stay reversible.

**Confirmed.** H3+G in file 28 is the same option as my "H3 with G1–G3" (22-seat5 §6). Under H3, G1 adds nothing, because H3 already blocks all of 08. G2 and G3 are what carry it. H4+G as composed in file 28 matches my G1–G3 plus R2.

**2. Ranking** (cells for H1, H2-c, H3 and H4 are unchanged from 22-seat5)
1. **H4+G: prefer.** 0/1.
2. **H3+G: can live with.** 1/0. It ties H4+G on sum, but its now-cost is certain, while H4+G's later 1 arises only if a fix is ruled.
3. **H2-cg: can live with.** 1/1.
4. **H3: can live with.** 1/1.
5. **H4 as written: can live with.** 0/2.
6. **H2-c: can live with.** 1/2.
7. **H1: can live with, ranked last.** 0/2.

**3. Tension now**
- **H4+G: 0.** It adds one pytest to the existing `python` job and one Depends-on clause.
- **H2-cg: 1.** The gate sits on a review artifact under `docs/review/phase-07d/`, not on a §0 row. Step 3 of CLAUDE.md cannot check it, so an 08-3 or 08-4 session has to look for a file by hand. A second problem: 07d's own loop will put other SURVIVES verdicts in that directory (the candidate AX row). As written, the artifact does not name the matter or the file.
- **H3+G: 1.** Unchanged.

**4. Tension later**
- **H4+G: 1.** If a fix is ruled, scope 8 waits for it and 07d may have to split into 07d/07d-b. If the fix lands after a re-pin, it carries the re-pin: at least 6 manual runs on three OSes. The evidence arrives with 07e's ruling. "No breach" brings this to 0.
- **H2-cg: 1.** Putting the item before scope 8 in the file orders the *ruling* before the re-pin, not the *fix phase*. That phase is a separate file, and nothing in H2-cg holds scope 8 for it. The gate on 08-4 also does not say it covers the fix phase. The ruling would also share 07d's two-session clock with the load and macOS loops, though it is exempt from the split-off. Undoing it costs one `/fix-plan`.
- **H3+G: 0.** Unchanged.
- **Coupling the other way (applies to every option):** suppose 07d later picks an output-changing candidate, C5 (07d scope 2). Then 07e's bit-identity pytest reds on main. The JSON must then be updated with a stated reason, never regenerated just to pass. My G3 text below covers this.

**5. Evidence**
- Re-pin rule, "runs after 07d's last code change … pooled only if … unchanged": phase-07d L94–96.
- Scopes 6 and 7: phase-07d L75–93.
- Order inside 08-4, with timing taken only on the post-grouping build: phase-08-4 L24–26.
- AX5 (BUILD_PLAN L128): bit-identity holds only on the same OS/CPU architecture. Across architectures the residual must be within −100 dBFS.
- The `python` CI job runs on ubuntu-24.04, macos-15 and windows-2022 (from the code, ci.yml L113–127, read in 22-seat5).
- [Hyp] The builder's local Linux toolchain may differ from the CI runner's. Values committed from a local build could then fail bit-identity on CI Linux, even though it is the same OS and architecture.
- [Hyp] A realised-k test that sits near its threshold could flip across architectures. That would move t_mix,e by about 0.2 s, the size of finding (b).
- No incident of mine covers what a golden round costs (§12).

**6. Conditions of acceptance and exact texts**

**G1**
- §0 row 08-4: replace "Depends on 08-3;" with:
  > "Depends on 08-3 and 07e `done` (and the fix phase 07e's ruling names, if any, added here by id when its §0 row is created);"
- `phase-08-4.md` L3: the same text.
- Add to 07e scope 5:
  > "The /fix-plan that creates the fix phase also adds its id to the Depends-on text of §0 row 08-4 and `phase-08-4.md` L3, and to 08-3 item 15's stimulus sentence."

  Without this, step 3 cannot see a fix phase that has no name yet.

**G2**
- `phase-07d.md` scope 8, prepend:
  > "**Order against phase-07e (phase-07c-2b M3-H):** this scope runs only after phase-07e is `done` and the fix phase its ruling names, if any, is `done` (§0). If this phase reaches scope 8 first, scope 8 splits to `phase-07d-b.md` with that dependency in its §0 row. Scopes 6 and 7 are not held."
- §0 row 07d notes, append:
  > "Scope 8 waits on 07e and its fix phase, if any (M3-H)."
- `phase-07e.md` scope 5, add:
  > "If a fix phase lands after 07d scope 8's re-pin is committed, its own automated acceptance criteria include that re-pin on the restore path it leaves: reference and baselines from ≥ 6 green manual runs after its last code change (no pooling of earlier runs), a `tests/golden/CHANGELOG.md` reason and a BUILD_PLAN §6 row, under phase-07d scope 8's rule, its Linux return-to-board clause included. It also prints record (h)'s 8-instance load on its own runs; an exceedance goes to the board."

  The record (h) sentence is my addition. It is recommended and is not needed for 0/1, because the AX38 4c restore gate is already asserted on every run.

**G3: name the producer.** "The OS/architecture that produced them" is not enough. If the producer is a developer box, the bit-identity leg can fail on CI Linux. Text:
> "The output JSON records the producing platform (OS, CPU architecture, CI runner label, preset, commit); values are produced by the `cli` preset on the ubuntu-24.04 x64 CI runner. A pytest in the `python` job re-runs ≥ 1 placement through `render_cli` and asserts every value bit-identically on that runner; on macOS and Windows, `ismFallback` and k_real equal, times and levels within AX5's cross-architecture bound as converted by the builder and stated in the test (AX5). A disagreement in a discrete field is a finding, never a tolerance. The JSON changes only through `tools/ci/update_goldens.py`."

**H2-cg, to bring now and later to 1/0:**
- Gate on a §0 row: give the item its own sub-phase row. That is H4.
- Name the artifact's file and matter id.
- Add the G2 clause for the fix phase.

**Scopes 6 and 7 under H4+G:** they are not held, and they should not be. Scope 7's closure works on macOS/Linux ratios, which a general fix moves on both OSes [Hyp]. Scope 6's record (h) is covered by the print clause above.

**7. Hand-offs**
- Seat 2 (B2): whether a likely fix changes restore work or only the level. If only the level, G2's re-pin debt is 0.
- Builder: how AX5's −100 dBFS residual converts to a dB tolerance on the metrics. I give no number.
- Seat 7: the cost of a 07d/07d-b split.

**8. Premortem.** Suppose H4+G is adopted without the G1 sentence that adds the fix phase's id. The fix phase gets written as 07f, and 08-4 starts with 07e `done` while 07f is still open. Its benchmark then predates the fix. The contracted engineer would notice first, reading 08-4's timing commits against 07f's merge.

Files read:
- /home/user/makroof/docs/review/phase-07c-2b/28-decider-m3h.md
- /home/user/makroof/docs/review/phase-07c-2b/22-seat5.md, 22-seat2.md, 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 14-seat7.md, 5-builder-tail-spread.md (L1–40)
- /home/user/makroof/docs/phases/phase-07d.md, phase-08-4.md (L1–40), phase-08-3.md (L58–87)
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L36–44, L55; AX5, AX6 L128–129)

Not re-read this round: 14-seat2.md, the PRD lines in the common list, and phase-08-3.md L3. I relied on their content as quoted in files 17, 20 and 22-seat2.
