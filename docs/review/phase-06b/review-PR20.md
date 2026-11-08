# Review: PR #20 — phase-06b Phase 06 decisions and follow-ups   (head 0aef950, base claude/laughing-fermi-u9iq7f = PR #14, base SHA 67c5c4a)

Reviewed with `.claude/skills/review-phase-pr` (process-rules, phase-checklists §Phase 06,
convolution-and-movement, realtime-audio-juce, tooling-testing-licences). Review started at 8a43792;
the session pushed 9d707cf and 0aef950 during the review (crash-probe wrapper, comments, MSVC build
fix). Everything below is re-checked at **0aef950** unless marked.

## Verdict

**Not ready (CI)**. The PR records decisions 1 and 2 as decision-loop proposals (D1 (a): keep P = 512,
AQ10 reworded, reported latency 544; D2: AX31 confirmed), adds AX32 (input bound B = 2^20, zeroing), rejects
non-finite IR taps, removes Catch2's POSIX signal handler with a crash probe, and adds the summation-order
test. The code is small and correct as far as I could check. Every mutant I ran was caught (8 of 8,
table below). Locally all 164 ctest entries pass. On the head run 42410271691, TSan and ASan + UBSan are
green, but the build jobs (linux/macos/windows) are still running. The PR is a draft and its description
is missing most of the required sections. The most important finding: the scope 6 test prints its
measured error only on failure (`INFO`), so CI on NEON (macOS) and MSVC (Windows) can't show the
measurement the phase file asks for. A non-zero value under 50 ulp on one of those platforms would
pass without anyone seeing it, which is the case the D4 rule says must be reported and redesigned.

What would flip it: all CI jobs green on 0aef950 (or a later head); the scope 6 measurement visible
per platform; the PR description completed with the six sections.

## Process gate

- **Scope:** every code hunk maps to 06b scope 3–6. Plan edits to phase-07 (latency gate recorded),
  phase-08 item 8 (note on which limit applies) and phase-13 item 9 (P = 256 dropped as a remedy) follow
  from D1/D2, went through the decision loop (ledger P06B-74…76) and fall under the DoD's "plan files".
  OK. Three commit subjects start with `plan:` instead of `phase-06b:` (Minor 5).
- **Dependencies:** phase 06 is `done` at the merge base (§0 row 06, PR #14). PR #14 itself is still open
  and this PR is stacked on it: 06b can't merge before #14.
- **Status table / §6:** row 06b is `in progress` (first commit 01ce79d). Not yet `done`, which is right
  for a draft. The §6 row for D1–D4 is present.
- **Assumptions used:** AQ4, AQ10 (reworded), AX1, AX18, AX31 (confirmed), AX32 (new). The code cites
  AX32 (`CrossfadingConvolver.h/.cpp`). The new AX32 row has its rationale, the phases it breaks
  (06b, 07, 13) and a reversal clause.
- **New/changed assumptions:** AQ10 first sentence reworded; AX32 added; AX31 note appended. All were
  put through the interrogator (ledger P06B-7…76, corpus c1b171f). The researcher dossier marked D1/D3
  "NOT READY, gaps not fillable", and the decider decided anyway (see For Maisara).
- **Boundary & contract:** `review_context.py` boundary check is clean. No contract change. The NFR-8 hit
  (`Engine.cpp:418`, `emitter.id == "L"`) is pre-existing and outside this diff.
- **Goldens/tolerances/skips:** none changed. No skips added. The `#if defined(_WIN32)` in
  `test_fail_fast.cpp:20` only selects the stdout-lock call; it doesn't remove a test.
- **PR description sections:** draft. It has "Raise with Maisara" and "Done so far". It is missing the
  AC checklist with CI evidence, the listening checklist ("None", decision 1 is (a)), contractor review
  focus, follow-ups, and assumption/golden changes (Major 2).
- **CI:** head 0aef950, run 42410271691 (`get_workflow_run`: head_sha 0aef950). Green: clang-format,
  contract tools ×3, python tools ×3, TSan (job 128516834135), ASan + UBSan (job 128516834075; log read:
  166/166 passed, including tests #16 late-first, #45 AX32, #50 non-finite tap, #166 crash probe at
  0.46 s), several tail gates. Still in progress: build (linux/macos/windows), some tail gates, BRAS
  validation. The earlier run 42409702373 on 8a43792 was cancelled (superseded). The 0aef950 commit
  message says 8a43792 didn't compile on MSVC (C3312), so Windows has no green build of the scope 5 code
  yet. Artifacts: none to check (no listening pack needed under D1 (a)).

## Acceptance criteria audit

| # | Criterion (phase file) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | Both decisions recorded: Maisara's words verbatim in the brief, ledger, §6 row | `docs/sessions/2026-11-07-phase-06b.md:8,10`; ledger section "Phase 06b decisions D1–D4"; §6 row 2026-11-07 | — | — | n/a (docs) | — | proven as worded. Whether her delegation counts as *her* decision is hers to say (For Maisara) |
| 2 | If decision 1 is (b): latency 288 … | — | — | — | — | — | N/A (decision (a)) |
| 3 | If decision 2 is a veto … | — | — | — | — | — | N/A (confirmed) |
| 4 | Scope 3: ~1e38 samples → output finite, FDL not poisoned; reference and tolerance per AX32; phase-06 nulls at their gates | `test_realtime_engine.cpp:189` "RealtimeEngine bounds input samples at 2^20 (AX32)", P ∈ {128,256,512}, seeded random blocks ≤ 512 | `renderOffline` of input with \|x\|>B zeroed (a), of burst-free input (b), per-sample references for ±B / nextafter (c) | −120 dB / −120 dB (AX32) | ASan job green; build jobs pending | a bound applied after the FFT can't exist; a bound slightly off is caught by `STATIC_REQUIRE` + (c). Mutants M2, M3, M4, M6 were all killed | proven locally + ASan; **pending** 3-OS build jobs |
| 5 | Scope 4: NaN/±Inf tap rejected (`makeIrSet` nullptr, `submitRoomIR` false), current IR kept | `test_partitioned_convolver.cpp` "IrSet geometry and validation" (3 values × 3 positions); `test_realtime_engine.cpp:268` (3 values, mid-stream refusal, −120 dB null vs current IR, `fadeCount()==0`) | `renderOffline` of the current IR | −120 dB | ASan job green; builds pending | only one bad tap per IR, in one path (taps[2]/taps[3]); a check limited to path 0 would still be caught. M5, M7 killed | proven locally + ASan; **pending** builds |
| 6 | Scope 5: SIGABRT probe → ctest reports failure well before 600 s; time quoted | ctest `fail_fast_crash_probe` → `run_crash_probe.cmake` (LIMIT 30 s) → hidden `[crash-probe]` (abort while another thread holds the stdout lock) | behaviour with the handler (M8: hang) | pass only on "Subprocess/Child aborted" or exit 3 (Windows) within 30 s | ASan 0.46 s; builds pending (Windows unproven: MSVC build broke at 8a43792) | M8 (handler back on) hangs 30.03 s → Failed: caught. At 0aef950 the wrapper no longer passes on "no test matched" (exit 2, checked) | proven on Linux; **pending** macOS/Windows |
| 7 | Scope 6: passes descending, fails ascending; threshold and measurement in PR and ledger | `test_crossfading_convolver.cpp:550` (P ∈ {128,256,512}, T = 400, x ≡ 1, 50 ulp) | exact arithmetic (analytic expected 1 + 400·2⁻²⁵) | 50 ulp / 50 ulp (D4) | ASan green (Linux x86) | M1 (`kk = k`) caught at 100 ulp. A non-zero descending error < 50 ulp on NEON/MSVC passes **silently** (Major 1) | proven on x86 Linux; measurement for NEON/MSVC **not produced** |
| 8 | TSan, ASan + UBSan green; zero allocations in `process` with the bound | existing `[alloc]` tests; TSan job runs `spatial_tests "[conv]"` | — | — | TSan 128516834135 ✅, ASan 128516834075 ✅ (the AllocationTracker skips under ASan by design, so the allocation evidence is the debug build jobs, still pending) | — | TSan/ASan proven; allocation **pending** builds |
| 9 | CI green on Linux, macOS, Windows | all | — | — | run 42410271691 in progress | — | **not proven yet** |

### Mutants run (local debug build, restored after each; `git status` clean at the end)

| # | Mutation | Result |
|---|---|---|
| M1 | `kk = k1 + 1 - k` → `kk = k` (ascending order) | killed: `test_crossfading_convolver.cpp:581` |
| M2 | AX32 bound → Phase 06 `!std::isfinite` only | killed: `test_realtime_engine.cpp:237` (finite check) and `:259` ((c) nextafter kept). **The (a) null at `:238` passed** (see Minor 1) |
| M3 | `<= kInputBound` → `< kInputBound` | killed ((c), ±B zeroed) |
| M4 | `kInputBound` = 2^21 | killed at compile time (`STATIC_REQUIRE`, `test_realtime_engine.cpp:193`) |
| M5 | finiteness check in `IrSet::create` removed | killed: `test_partitioned_convolver.cpp:160`, `test_realtime_engine.cpp:282,297,306,309` |
| M6 | bound applied to input channel 0 only | killed: `test_realtime_engine.cpp:237`, plus the phase-06 non-finite input test (`:486`) |
| M7 | `makeIrSet` catches the wrong exception type (escape) | killed: `test_realtime_engine.cpp:282,297` |
| M8 | `CATCH_CONFIG_NO_POSIX_SIGNALS OFF` (reconfigured) | killed: `fail_fast_crash_probe` "crash probe hung: no exit within 30 s", Failed 30.04 s |

## Findings (by severity)

### Blockers

None in the code. The verdict is "Not ready" only because CI isn't finished (process-rules §9: a red
or missing job makes the PR not ready).

### Major

1. `tests/unit/test_crossfading_convolver.cpp:577-581` — the measured error goes out through `INFO`,
   which Catch2 prints only when an assertion fails, and ctest (`--output-on-failure`) hides passing
   output anyway. Phase-06b scope 6 (D4) says "the measured error (expected 0 on SSE and NEON) is
   printed for the PR" and "a non-zero descending error on any platform means the case is not exact
   there: report it and redesign the case, never re-threshold". As written, a NEON (macOS) or MSVC
   result of 1–50 ulp passes CI unseen, and the contractor focus item "pins the order rather than one
   platform's rounding" can't be checked on 2 of 3 platforms. Fix: make the non-zero case visible.
   Either add `CHECK(worst == 0.0)` (consistent with the D4 rule: non-zero is a design failure, not a
   threshold question), or keep the 50 ulp gate and add a CI step that runs the test with `-s` on all
   three OSes. Then quote the per-OS values in the PR.
2. PR description (draft): the AC checklist with CI evidence, listening checklist ("None": decision 1
   is (a)), contractor review focus, follow-ups and assumption/golden changes are missing
   (process-rules §7). The crash-probe time to failure per OS is needed for scope 5's AC ("measured
   time … quoted in the PR"). Today only the Linux value (54 ms) is quoted.

### Minor

1. `tests/unit/ConvTestUtil.h:53-54` (pre-existing, phase 06; the 06b tests rely on it) — `residualDb`
   returns −∞ (a perfect null) when `err` is NaN, because `!(err > 0)` is true for NaN. Under M2 the
   AX32 (a) null (`test_realtime_engine.cpp:238`) passed on NaN output. Only the separate `isfinite`
   check at `:237` and section (c) killed the mutant. The AX32 row says the (a) null "shows the FDL is
   not poisoned (fails without the bound)", but measured, it doesn't fail. Fix: return +∞ when `err` is
   NaN, and correct the AX32 row wording through `/fix-plan` (or list it as a follow-up). Every
   phase-06 null that uses this helper has the same blind spot.
2. `src/sim/RealtimeEngine.h:62` — the `makeIrSet` comment ("nullptr when the IR doesn't fit") wasn't
   updated for non-finite taps, unlike `submitRoomIR` at `:55-57`. `src/cli/Cli.cpp:519-521` reports
   any nullptr as "longer than … samples", which is misleading for a non-finite IR.
3. `src/sim/RealtimeEngine.cpp:56-65` — the `catch (const std::invalid_argument&)` swallows every
   `IrSet::create` failure (partition size, path count, length mismatch), not only the scope 4 one.
   Before this change those threw. The engine's own pre-checks make them unlikely, but a future bug
   would now look like a silent "IR refused". A non-throwing finiteness check before `create` (or a
   dedicated exception type) would keep scope 4 narrow.
4. `cmake/SpatialDependencies.cmake:79` — without Catch2's handler, a crash during a *direct* binary
   run no longer names the test. That affects the TSan job (`ci.yml:466`, `spatial_tests "[conv]"`)
   and the benchmark step (`ci.yml:335`). ctest still names it, since every test case is its own
   process (measurements M3). This is the contractor-focus question "does it still report which test
   crashed?": yes under ctest, no in those two direct invocations. Worth a sentence in the PR.
5. Commit subjects 67034fe, b28ee25, 9206cdd use `plan:` instead of `phase-06b:` (CLAUDE.md "Git and
   PRs").
6. Resolved during the review (no action, for the record): at 8a43792 the probe wrapper passed on any
   non-zero exit. I confirmed `spatial_tests "[nonexistent]"` exits 2, so a deleted or renamed probe
   would have passed. `test_fail_fast.cpp` also cited a `WILL_FAIL` that wasn't used. Both were fixed
   in 9d707cf. I re-checked the wrapper: real probe passes ("Subprocess aborted", 53 ms), `/bin/false`
   fails. Catch2 exits with 3 only with `--warn UnmatchedTestSpec`, which the wrapper doesn't pass, so
   the Windows exit-3 rule is safe.

### Questions (unverified, evidence requested)

1. Scope 6 on NEON and MSVC: is the descending error exactly 0? (Needs Major 1's print, or a `-s` run
   in the macos/windows build jobs.)
2. Windows crash probe: does `_set_abort_behavior` plus the CRT report mode give exit code 3 promptly on
   the runner, with no WER dialog? (Needs the build (windows) job log: the `fail_fast_crash_probe` line
   and its time.)
3. Zero allocations in `process` with the bound in place (phase-06 AC 5): this needs the debug build
   jobs. The tracker skips under ASan (job 128516834075 log: test #10 "Skipped").

## What I verified myself

- `review_context.py --base origin/claude/laughing-fermi-u9iq7f --head HEAD`: phase 06b. Warnings:
  phase files touched (checked above: decisions only, ACs unchanged), and cmake touched without
  THIRD_PARTY (a Catch2 config option, not a pin change: no row needed). Boundary clean. Audio-thread
  scan: the only hit is the `throw` in `IrSet::create` (off the audio thread).
- Local debug build at 8a43792, then rebuilt at 0aef950: `xvfb-run -a ctest --preset debug -j8` gave
  164/164 passed. Scope 6 test with `-s`: worst error 0 ulp at P = 128, 256, 512 (x86-64, GCC). `[engine]`
  passed (8828 assertions).
- Mutants M1–M8 (table above). Every mutated file was restored. `git status` is clean.
- Re-derived the scope 6 arithmetic: 1/(2P) and the taps are powers of two, so every product is exact.
  The constant input gives a DC-only FDL spectrum (non-DC bins exactly 0). Descending: 400·2⁻²⁵ is
  summed exactly, then 1.0 is added, giving 1 + 100·2⁻²³, which is representable. Ascending: each
  2⁻²⁵ < ½ ulp(1) = 2⁻²⁴ rounds away, so the error is 100 ulp. The midpoint threshold of 50 is sound.
  The order code is in `advanceLane` (`CrossfadingConvolver.cpp:204-212`). Partition 0 is added last
  in `finishLane`, and it is zero in this case.
- AX32 placement: the bound is applied in the intake loop (`CrossfadingConvolver.cpp:366`), right after
  the `memcpy` and before `computeBlock()` → `fdl_.push()` (the forward FFT). No other path writes to the
  FDL. `!(fabs(x) <= B)` is true for NaN and ±Inf. The FDL-bin bound 2P·B ≤ 2³⁰ holds.
- CI: `get_check_runs`, `get_workflow_run 42410271691` (head 0aef950). Read the ASan + UBSan job log
  (grepped: 166/166, new tests and probe passed). The TSan job is green (I read only the log tail).

## For Maisara

- **Listening checklist:** none for this phase, because decision 1 is (a) (phase-06b "Listening /
  manual checklist"). I tick nothing; any listening is yours.
- **Decisions:** the phase file calls both decisions yours. The session took your reply ("I have
  created an entire workflow described in claude.md so you don't ask me these" / "Same answer") as
  delegation. The decision loop decided D1 (keep P = 512, reported latency 544 samples = 11.3 ms) and
  D2 (AX31 confirmed), and both are recorded as **vetoable proposals**, not as your acceptance. The
  phase file's "§6 row 'accepted by Maisara'" step was therefore not done, and the PR says so. Please
  either accept them explicitly or veto.
- **AX32 (new, also vetoable):** a sample above 2²⁰ (+120 dB re full scale) is silenced, not clamped.
  The researcher found no published "largest legitimate level", so B is a product choice, documented
  as such in the AX32 row.
- **Repo wording conflict (unchanged):** CLAUDE.md sets `done` when the automated criteria pass; the
  BUILD_PLAN preamble requires your listening checklist too. Here there is no checklist, so the
  conflict doesn't apply.
- This PR is stacked on PR #14, which must merge first.

## Contractor review focus (from the phase file), with pointers into the diff

- **Bound vs non-finite guard vs forward FFT:** one comparison replaces the old guard, at
  `src/sim/conv/CrossfadingConvolver.cpp:363-367`, before `computeBlock()`/`fdl_.push()`. The FDL never
  receives a non-finite spectrum (bins ≤ 2P·B). Output overflow is still possible with absurd IRs:
  Σ|h| > 1.58e29 per path, which the AX32 row documents; the accumulator is per block, so nothing
  persists.
- **Finiteness check in `IrSet::create`:** `src/sim/conv/PartitionedConvolver.cpp:54-60`, applied to
  every path in the vector overload that the `RoomIR` overload delegates to. Engine side:
  `src/sim/RealtimeEngine.cpp:56-65` (see Minor 3).
- **Fail-fast mechanism / does it still name the test:** `cmake/SpatialDependencies.cmake:74-79`,
  `tests/support/FailFast.cpp` (MSVC abort/CRT dialogs), `tests/unit/run_crash_probe.cmake`,
  `tests/unit/test_fail_fast.cpp`. ctest names the test; direct invocations don't (Minor 4).
- **Order pinned rather than one platform's rounding:** the case is exact by construction (verified
  above). Confirming it on NEON/MSVC needs Major 1.
- **Under (b), every place that assumed P = 512:** N/A. Decision (a) leaves `kDefaultPartitionSize` at
  512; the plan text in phase-07 and phase-13 was updated to match.
