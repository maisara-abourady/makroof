# Session brief: Phase 06 follow-ups (second phase-06 session)

- Branch: `claude/laughing-fermi-u9iq7f` (PR #14)   Started: 2026-11-07   Governing: `CLAUDE.md`, `docs/phases/phase-06.md`, `docs/BUILD_PLAN.md` §0, §2 (AQ4, AQ10, AX1, AX18), `.claude/commands/fix-plan.md`, the "Follow-ups" section of PR #14, the first session's brief `docs/sessions/2026-11-07-phase-06.md`

## Maisara's words
> 2026-11-07: "Take care of all the follow-ups"

> 2026-11-07 (answer to the session's question on F1, "build non-uniform partitioning now or only remove the small-buffer spikes"): "Spread only, plan later (Recommended)" — ship the spreading fix for the spikes; record non-uniform partitioning in the plan with the measured numbers, for Phase 13 or when 12 s IRs need a budget.

The follow-ups are the ones listed in PR #14 ("Follow-ups (not done here)"):
(F1) non-uniform partitioning / worst single callback above 100 % at a 64-sample host buffer with a 12 s IR during a fade; (F2) Phase 07: builder thread stopped or joined before `prepare()`/destruction; NaN/Inf host input unguarded; use `RealtimeEngine`, not the bare `CrossfadingConvolver`; (F3) AllocationTracker disables ASan's new/delete-mismatch checks; (F4) CLI null margin at P = 128 only 4.5 dB; "process before prepare()" tests would time out rather than fail; denormal guard a no-op on MSVC/ARM64; (F5) stale `review-phase-pr` reference notes on PFFFT tags; (F6) merge main again once PR #16 (h5py) lands.

## Objectives
| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | **Session brief checked** | CLAUDE.md "Reporting" | this brief committed; steward BRIEF OK |
| O2 | **Main merged in** | F6 | merge commit (with PR #16) on `origin/claude/laughing-fermi-u9iq7f`; nightly validation run on the PR head: success (run id cited) |
| O3 | **Partition work spread out** | F1 | `CrossfadingConvolver` does the k ≥ 1 partition MACs of the next block incrementally across the host callbacks of the current block (only k = 0, the FFTs and the IFFTs remain at the partition boundary); every phase-06 null / crossfade / allocation / TSan test still passes in CI on 3 OSes; (a) deterministic: a Catch2 test counts the multiply-adds each `process()` call does and asserts that no call at host buffer 64 does more than its proportional share (⌈U·64/P⌉ per state) plus the boundary's k = 0 work; (b) timing: the benchmark's 99.9th-percentile callback at host buffer 64, 12 s IR, P = 512, while crossfading is < 100 % of the 64-sample budget on each CI OS (head CI logs; the max is printed too, as information — runner preemption is not the convolver, phase-06 AC 8: don't fail on runner noise) |
| O4 | **Small-buffer benchmark** | F1 | benchmark prints mean, p99.9 and max callback % of the budget for host buffers 64 and 512, IR 3 s and 12 s (and the rest of the phase-06 grid), P = 256/512, steady and crossfading, in the head CI logs on 3 OSes; AQ10 re-confirmed: 3 s / P = 512 / buffer 512 mean ≤ 15 % on macOS |
| O5 | **NaN/Inf input guard** | F2 | non-finite input samples are replaced by 0 in `process()`; a Catch2 test feeds NaN/Inf and shows finite output that equals the clean render after the IR length |
| O6 | **ASan coverage restored** | F3 | under ASan the tracker does not replace operator new/delete; tracker-dependent assertions skip with a reason there; ASan job green |
| O7 | **Prepare tests fail fast** | F4 | the "process before prepare()" tests run the call under a watchdog and FAIL within seconds on a hang; mutation evidence in the PR (guard removed → test output FAILED and its time to failure) |
| O8 | **MSVC/ARM64 denormal guard** | F4 | **routed, not built** (changed after steward round 1, G7: no CI can compile or test it, and CLAUDE.md wants every DSP behaviour checked): recorded as a Phase 13 item through O11 |
| O9 | **P=128 null margin** | F4 | root cause measured and stated in the PR (how the residual scales with P / partition count), and either the margin at P = 128 raised to ≥ 6 dB under the unchanged −120 dB gate (CLI and C++, 3 OSes), or a justified decision to keep it with the numbers; the gate itself is not changed |
| O10 | **Skill reference corrected** | F5 | `convolution-and-movement.md` §3.2 and `phase-checklists.md` (Phase 06) agree with `tooling-testing-licences.md`: tags v1.0.0/v1.1.0/v1.2.0 exist, the project pins v1.1.0's commit (diff) |
| O11 | **Plan items routed** | F1, F2, F4 | through `/fix-plan`: `phase-07.md` gains the builder-thread-lifetime and "use `RealtimeEngine`" requirements; non-uniform partitioning (with the measured numbers) and the MSVC/ARM64 denormal guard recorded as Phase 13 items (interrogator check of the diff; ledger rows; `plan:` commit) |
| O12 | **CI, PR, status** | CLAUDE.md step 4, 6, "Git and PRs" | row 06 set back to `in progress` first, then `done` with updated notes; CI workflow green on 3 OSes for the head incl. `asan` and `tsan`, and the nightly validation green; listening pack regenerated in the head CI artifact; PR #14 description updated (what changed, AC evidence on the head run, listening checklist + artifact location, contractor review focus incl. work spreading, the new s0 = (⌊r/P⌋+2)·P, the NaN guard, the ASan tracker change; follow-ups; statement that no threshold or golden changed, so no §6 row); `/review-phase-pr` re-run (independent agent) on the new head and its blocking findings fixed; steward READY TO REPORT |

## Scope
- In: O1–O12.
- Out: implementing non-uniform partitioning (Maisara chose "spread only, plan later"); the MSVC/ARM64 denormal guard (routed to Phase 13, O8); Phase 07 plugin code (the builder thread doesn't exist yet: its requirements go into `phase-07.md`); the AQ10 latency decision (Maisara's).

## Constraints and settled decisions
- Row 06 goes back to `in progress` for this session (CLAUDE.md step 4) and returns to `done` at the end.
- Everything from the first session's brief (AQ4 30 ms, AX18 laws, AX1 latency = P + pre-roll, no AX/AQ change, no golden change).
- O3 changes pickup timing: with B's work spread over a block, a request taken at partition boundary b enters the output at the next boundary, s0 = (⌊r/P⌋ + 2)·P instead of (⌊r/P⌋ + 1)·P (one more block, 10.7 ms at P = 512 / 48 kHz). The crossfade itself (30 ms, laws) is unchanged; the test asserts the reported s0. Stated in the PR for the contractor.

## Raise with Maisara
- Still open from session 1: the latency reading (544 vs AQ10 "≤ 512").
- Non-uniform partitioning: asked and answered (spread only, plan later), see her words.

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
| 1 | 2026-11-07 | BRIEF GAPS | G1 (Maisara: F1), G2–G10 | G1 (answered: spread only, plan later), G2–G10 (objectives amended) |
| 2 | 2026-11-07 | BRIEF GAPS | G11 (brief not on origin), G12 (s0 change without a decision record), G13–G17 | G11 (6a8c027 on origin merges cdd421a), G12 (decision loop: decider D1 → interrogator SURVIVES WITH CORRECTIONS → advocate PASS → plan-editor AX31, AQ4, AC 3; diff check applied; ledger P06F-1..11), G13 (U = M·N·(K−1) per state; per-call bound in the tests), G14 (NaN test: −120 dB against the zeroed-input render over the whole output; guard in sim because the engine owns the FDL), G15 (O9 met by a code change, no keep-decision needed), G16 (phase-13 scope 1 wording kept, numbers added), G17 (code committed after the decision loop) |

## Phase re-review (not a steward round)
- `/review-phase-pr` procedure, independent agent, at 31894b6: lane bookkeeping correct, 12 of 13 non-equivalent mutants killed; Major: reset() × lanes untested (fixed: mid-block reset test, mutant now killed); stale PR description (updated); minors: renderB simplified, per-call bound for straddling blocks tested, AQ4 sample-rate wording (P06F-11), comment; big finite inputs and IrSet finiteness, the Catch2 abort hang, and pinning the summation order noted as follow-ups. Kept at `docs/review/phase-06/review-PR14-followups-at-31894b6.md`.
