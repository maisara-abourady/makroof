# Review: branch `claude/laughing-brahmagupta-vhem6q` — phase-05h Tail-level switch (session 2), round 3   (head 7e4937b, base origin/main @ merge-base 8583ba1)

Branch review (no PR yet): it cannot end in Approve, only in "Request changes" or "Not ready (no CI)".
Third pass. Pass 1 (`docs/review/phase-05h/32-…`, on d51dde0) and pass 2 (`…/39-…`, on a9d8313)
audited the AX37 switch, the agreement / tracer / regression / D5 tests and the goldens; their findings
were closed in loop files 40–46 and 56–73. This pass reads everything that changed since a9d8313
(`git diff a9d8313...7e4937b -- src tests tools .github tests/golden docs/BUILD_PLAN.md
docs/phases/phase-05h.md docs/phases/phase-05i.md`: 10 files, **none under `src/`**) and re-audits the
earlier criteria only as far as the table below needs, citing passes 1–2 where nothing changed.
The working tree carries one more local commit, 5823b89 (docs/review files 31 and 56 only), not yet on
origin; the fingerprint is unchanged by it.

## Verdict

**Request changes** (one Major, four Minors; no Blocker). The diff since pass 2 lands DECISION RG-1's
restore-gate form in `tests/unit/test_diffuse_records.cpp` (the `GateEntry` / `kGateRegister` register
with per-OS mean baselines, the asserted work pins, the flutter scene's strict 30 s, the low-α growth bound
asserted only inside a ±5 % flutter window on x64, the macOS 2 172 ms trigger printed, one GATE line per
OS and scene), its plan text (AX38 4c "Assertion form on hosted runners (RG-1)", phase-05h §5 Blocking
(a)–(d), phase-05i scope 3, §6 row, CHANGELOG record), the `open-field-validation` CI job and
`if: always()` on pluginval / auval, the FTZ test's comment fixes and the two-scene split-timer probe,
AX46's six-class / estimator-propagated form, and the open_field check at N = 2^23 with τ alone. CI run
42964823518 (workflow_dispatch on 67f13f3, whose `ci_fingerprint.py` digest equals the head's and the
local tip's: `df3845cb…d910`) is green on all 35 jobs on Linux, macOS and Windows, and nightly 42964826298
on the same SHA is green. The gate asserts exactly the "Asserted every run" list of AX38 4c and nothing
from its "Printed with WARNING" list; the baselines in the test equal the CHANGELOG's, the plan's and my
re-derivation from file 56's table. The single most important finding: the pinned "synthesis FFT size"
is re-derived in the test from the same formula the generator uses (`NoiseTail.cpp:83`) instead of being
read from the generator, so a change to how `BandNoiseGenerator` sizes its FFT is invisible to the pin;
a one-line accessor closes it. What flips the verdict: that accessor (or a `/fix-plan` narrowing of the
plan's wording to "the formula's value"), the four comment / dead-code minors, then the PR with its six
sections, the §0 row set to `done` with the GATE counts, and the PASSES30S follow-up named.

## Process gate

- **Scope:** every hunk since a9d8313 belongs to phase 05h (the restore gate is scope 6 / §5 Blocking;
  the open-field job is §5 criterion 9's CI home, decided P05H-QA-T; AX46's form is §5 criterion 3). No
  work of another phase. The phase file, phase-05i, 07c and 13 were edited through `/fix-plan` with
  decider / interrogator files cited (e87a47f, 814264c; files 64–73): a session editing its own
  acceptance criteria is the review_context warning, and here each edit carries its board record, so
  not a finding.
- **Dependencies:** unchanged since pass 1 (05b/05g `done` at the merge base).
- **Status table / §6:** §0 row 05h is still `in progress` at HEAD (correct before the PR; CLAUDE.md step
  6 sets `done` after CI). At `done` the row must carry what AX38 4c now requires: "the latest figures
  and the counts" per OS (asserted / not evaluated / WARNING runs) and the GATE lines of run 42964823518
  (Linux not-evaluated, flutter −16.8 %; macOS reported-only with GROWTH + OVER30S, median 2 069 ms
  < 2 172; Windows asserted, 2 005 ≤ 2 231 ms), plus pass 2 minor 4's AQ9 before/after. §6 rows added
  since a9d8313: eight, including "DECISION RG-1" (2026-11-11) and the two AX46 rows; each names its
  decider / interrogator files. OK.
- **Assumptions used:** AX38 4c (RG-1 form), AX41 (1.02, W pins), AX37 (5.4) (2^23, τ alone), AX46 (six
  classes, SE_prop), AQ10 amended (1). Cited in the code (`test_diffuse_records.cpp:67–96, 346, 383,
  446; test_tail.py:196–215`).
- **New / changed assumptions:** all through `/fix-plan` with §6 rows; no silent decision found. The
  constants `kGrowth 1.10`, `kGuardPct 5.0`, `kRatioWarn 1.20`, `kMacGrowthTriggerMs 2172`, the pins
  1152000 / 377517 and 2097152 / 524288 carry their provenance comments and the CHANGELOG "(RG-1)" record.
- **Boundary & contract:** review_context: 57 files scanned, no violation; contract untouched since
  pass 1. NFR-8 scan's only hit (`Engine.cpp:550`, emitter id "L"/"R" → output channel) is channel
  routing, not scene logic (unchanged since pass 1).
- **Goldens / tolerances / skips:** no golden file changed since a9d8313; the CHANGELOG gained two
  "(records-test constants)" records (not goldens, as pass 2 minor 7 asked to be said). No tolerance
  widened: the open_field check moved from τ + 3·SE to τ alone at 2^23 (tighter), the AX46 budget moved
  from 1 % − max ℓ_ref to 1 % − mean ℓ_ref with the SE redefined (a board decision, §6 row). The gate's
  30 s and 1.10 are kept where asserted; what is no longer asserted on hosted runners (the low-α 30 s,
  macOS's growth) is recorded as such in AX38 4c and §6 ("no threshold loosened"). Skips: unchanged
  (the FTZ SKIPs per platform, the ASan allocation-tracking SKIP; pass 1).
- **PR description sections:** no PR: not available. The PR must contain the six sections, the GATE
  lines and counts, the WARNING run named (macOS GROWTH on 42964823518), "Decided for Maisara" with RG-F1
  (file 70), P05H-QA-T, P05H-QA/QB/QC, and the Follow-ups below.
- **CI:** run 42964823518 (`gh run view --json jobs`): 35 jobs, all `success`, head 67f13f3, event
  workflow_dispatch; nightly 42964826298 `success` on 67f13f3 (`actions_get`). Fingerprint
  `python3 tools/ci/ci_fingerprint.py --rev {67f13f3,7e4937b,5823b89}` → identical, so the run is the
  head's evidence under the skip rule. Artifacts (`gh api …/artifacts`): `SpatialScene-{linux,macos,windows}`,
  `pluginval-{linux,macos,windows}`, `listening-pack` (236 MB, 201 files, phase-05h folder written: 12
  renders). Logs read: build-{linux,macos,windows} (saved `ci12_*.log`: ctest "100% tests passed … out
  of 223"; benchmark "All tests passed (15597 / 15595 / 15596 assertions in 13 test cases)"; pluginval
  `--strictness-level 10` "SUCCESS" on all three; auval "AU VALIDATION SUCCEEDED" on macOS),
  open-field-validation ×3 (`get_job_logs`: "2 passed, 68 deselected" in 8:17 / 6:57 / 8:54), python
  tools (linux): "571 passed, 16 skipped, 30 deselected", `test_ci_workflow.py` 21 tests passed (the new
  job is gated, in `ci-ok`'s needs).

## Acceptance criteria audit

Criteria whose evidence did not change since pass 2 cite that pass; the rows that changed are audited
in full.

| # | Criterion (phase-05h §5) | Test(s) | Reference used | Tolerance (test / phase) | CI evidence | Bug it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| 1 | D-H1 recorded as an AX change before the gate | ledger rows, AX38 4c / AX41 text | plan | — | commits e87a47f ≺ 67f13f3 | — | proven (pass 2) |
| 2 | E_target = ref_hybrid within τ over 560 / 72 case-bands; pooled AX43 CHECK | `test_diffuse_agreement.cpp` | committed Python references (two rungs) | 0.25 dB / 0.25 dB; pooled 3 SE_pool + mean ℓ_ref | run 42964823518 build logs: pooled bands 0–7 "(within)", 0.0080–0.0098 dB bound | unchanged since pass 2 | proven (pass 2) |
| 3 | AX46 bias ≤ 1 % per band and class, six classes, SE_prop | `test_diffuse_agreement.cpp:361–436` (diff since a9d8313) | same references | CHECK |mean| ≤ 1 % when 3·SE_prop ≤ 1 % − mean ℓ_ref / same (§6 row) | build logs: the AX46 lines print per class incl. `bras`; `[.]`-free, in the 223 | a class bias that is masked by SE_prop being computed from `10^(se/10) − 1` (a linearisation; fine at SE ≤ 0.2 dB) — not a plausible miss at these SEs; a heterogeneity between cases is a labelled watch, not a CHECK (by decision) | proven |
| 4 | tracer ±1 dB on 15 (A) | `test_diffuse_agreement.cpp` tracer section | committed tracer golden | 1 dB / 1 dB | pass 2 | unchanged | proven (pass 2) |
| 5 | AX45 uniform-α rooms within D-T6 | AX45 suite, 72 / 72 | golden | pass 2 | pass 2 | unchanged | proven (pass 2) |
| 6 | Determinism AX39 (KAT, D5 hashes cross-OS) | `test_diffuse_reports.cpp`, `phase05h_d5_hashes.json` | self (cross-OS) | exact | three OS logs identical W pins (3154338 / 2547436; 1696086 / 4348889) | unchanged | proven (pass 2) |
| 7 | U silent at default placements | pass 2 | — | — | pass 2 | unchanged | proven (pass 2) |
| 8 | Realised work ≤ 1.02 at the gated scenes; W_pilot / W_final pinned | `test_diffuse_records.cpp:363–379` `REQUIRE(d.realisedWorkRatio <= 1.02)`, `REQUIRE(d.wPilot == …)`, `REQUIRE(d.wFinal == …)` | constants with provenance (deterministic, D7) | exact / exact; 1.02 / 1.02 | three OS logs: 0.9347 / 0.9910, pins equal | a W change on a build where the pins were re-pinned without a CHANGELOG reason (process, not test) | proven |
| 9 | open_field AX37 (5.4) at N = 2^23: 3·SE ≤ τ per band asserted, |dev| ≤ τ alone; shipping-N smoke labelled | `test_tail.py:196–253` | `ground_scatter.window_target` (independent integral) | τ 0.25 dB / τ 0.25 dB; N rule 3·SE ≤ τ | open-field jobs ×3: 2 passed; band 7 SE 0.073–0.076 dB (3·SE 0.22–0.23 ≤ 0.25), dev −0.020…+0.005 dB; python job: smoke lines labelled, |dev| ≤ τ + 3·SE | a systematic error < 0.25 dB at 4–8 kHz is inside τ by design; an error in `window_target` itself (shared by both forms) — pass 2 re-derived it independently | proven |
| 10 | `--diagnostics` reports diffuse E_target, AX41 flags | pass 2 | — | — | pass 2 | unchanged | proven (pass 2) |
| 11 | bit-identical IR; no NaN / denormals (FTZ test); allocation-free | `test_diffuse_gate.cpp:398–500` (comments / print only changed since a9d8313; the REQUIREs unchanged) | self + FPU flags | exact | build logs: `[pipeline]` in the 223 passed on three OSes | unchanged (pass 2 minor 1 applied) | proven |
| 12 | Gate (AX38 (i)): debug assert, real-time-beside-gate | pass 2 | — | — | local ctest test #57 passed; CI 223 | unchanged | proven (pass 2) |
| 13 | W1/W2 and AX38 records; memory block ≤ 1 GB (Linux) | `test_diffuse_records.cpp:338–344` | self | 1024 MB / 1 GB | Linux log: transient RSS delta 296 MB at the gated 96 kHz builds | unchanged | proven |
| 14 | **Blocking, register form (a)–(d)** | `test_diffuse_records.cpp:97–107, 346–423, 446–471, 500–543` | per-OS means from runs on file (CHANGELOG) | see below | GATE lines of run 42964823518 (quoted in Process gate "Status table") | see Findings Major 1 and Questions 1–2 | proven as written; the FFT pin's reach is Major 1 |
| 15 | Solve seam (one function) | pass 2 | — | — | pass 2 | unchanged | proven (pass 2) |
| 16 | Only if Phase 08 went first | n/a (Phase 08 not done) | — | — | — | — | n/a |
| 17 | Trigger 1 clause (d) replicates | `[diffuse-replicates]` | long run 2^20 | pass 2 | benchmark step logs | unchanged | proven (pass 2) |
| 18 | Goldens through `update_goldens.py`; nightly green; report regenerated | CHANGELOG, nightly | — | — | nightly 42964826298 success on 67f13f3 | unchanged (no golden changed since a9d8313) | proven |
| 19 | pluginval strictness 10 and auval pass | `run_pluginval.sh`, auval step | pluginval / auval | — | build logs: SUCCESS ×3, "AU VALIDATION SUCCEEDED"; `if: always()` leaves the job red when the benchmark step fails (no `continue-on-error`; `ci-ok` requires `success`) | — | proven |

**Row 14 in detail — does the gate assert what AX38 4c says it asserts, and nothing it says it prints?**
AX38 4c "Asserted every run": (i) exact W_pilot / W_final and realised work ≤ 1.02 → `REQUIRE`s at
L365, 377, 378 ✓; (ii) per gated scene the unit-decay length and the FFT size n, exact → L398, 400 ✓
(see Major 1 on what n is read from); (iii) 14 × worst-of-10 ≤ 30 s at the flutter scene on every OS →
L459, `strict30s` true only on the three flutter entries (L99–101) ✓; (iv) Linux / Windows only, the
median-of-10 low-α restore ≤ 1.10 × baseline when the run's flutter median is within ±5 % of its
reference, else NOT EVALUATED → L541–542 guarded by `absoluteAsserted && inWindow`, `absoluteAsserted`
false on the macOS entry (L105), status string `not-evaluated(runner,flutter±x%)` ✓. "Printed with
WARNING, never asserted": the ratio above 1.20 × (L513 → "RATIO", no REQUIRE) ✓; solve median and
ns/eval (L419, print) ✓; 14 × worst above 30 s on the low-α entries (L462–469 "WARNING OVER30S", L517
"OVER30S") ✓; the absolute median above 1.10 × where not asserted (L515 "GROWTH") ✓; the (c)
PASSES30S line (L467, L520) ✓; the macOS trigger at 2 172 ms printed as `trigger=2172` and "MACTRIGGER"
(L533–540), no state kept ✓. No REQUIRE exists outside that list (the remaining ones are `entry !=
nullptr` and `fl.restore.median > 0`, structural).
**Baselines:** test L104–106 = 2068 / 1817 / 2028 ms, 3.05 / 3.75 / 2.83, 701 / 484 / 737 ms;
`kMacGrowthTriggerMs` 2172; `kGrowth` 1.10; `kRatioWarn` 1.20; `kGuardPct` 5.0 — equal to the CHANGELOG
"(RG-1)" record, AX38 4c, phase-05h §5 and phase-05i scope 3. Re-derived from file 56's table: flutter
means Linux (716+693+514+880)/4 = 700.75, Windows (757+752+626+927+622)/5 = 736.8, macOS (474+494+484)/3
= 484; ratio means 3.05 / 2.83 / 3.75; in-window medians Linux (2043+2092)/2 = 2067.5, Windows
(2000+2056)/2 = 2028, macOS (1849+1887+1715)/3 = 1817; trigger ⌊1.15 × 1889.25⌋ = 2172 ✓. Pins: 12 s ×
96 kHz = 1 152 000 (the low-α cube's T60 ≥ 8 s → the 12 s cap), 1 152 000 + 2 × 15 697 = 1 183 394 →
2^21; 377 517 + 31 394 = 408 911 → 2^19 ✓.
**Can the test go red on a correct build for runner noise?** Two paths, both named by the plan as
(d) defects, never re-runs: (a) L459, the flutter strict 30 s, on a runner ≥ 2.85 × slower than run
42964823518's Windows (10.53 s) — the register's worst runner factor on file is ×1.9 (Windows flutter
488 → 927 ms); (b) L542, when the flutter median lands inside ±5 % while the low-α median exceeds the
baseline by > 10 % (the two scenes load the memory system differently: 2^21 vs 2^19 FFTs). File 56's
in-window rows show low-α/flutter ratios 2.64–3.02 (Linux 2.85 / 3.02, Windows 2.64 / 2.73 / 2.70), i.e.
a ±6 % swing at equal flutter, so (b) is the designed sensitivity, not a flake path visible on file.
**Does it stay green on a wrong build?** A W_pilot change: no (L377, exact). A flutter worst of 2.2 s:
no (14 × 2.2 = 30.8 s > 30, L459). A low-α median of 2.2 s on Linux: yes, if the flutter median is in
window (2 200 ≤ 2 275) — by design (1.10 ×). An FFT-size change inside the generator: **yes** (Major 1).
A low-α regression on macOS, or on x64 when the runner is out of window: yes, printed — by decision.

## Findings (by severity)

### Blockers
None.

### Major
1. `tests/unit/test_diffuse_records.cpp:383–400` (and `src/sim/tail/NoiseTail.cpp:83`,
   `NoiseTail.h:68–83`) — the "synthesis FFT size" pin is not read from the synthesis. The test
   recomputes `n = Fft::nextPowerOfTwo(len + 2 * fb.maxHalfLength())` from `eyringDecay`,
   `tailLengthS`, `unitDecayLength` and the filterbank, and `BandNoiseGenerator`'s constructor sizes its
   FFT with the same expression (`fft_(Fft::nextPowerOfTwo(length + 2 * filterbank.maxHalfLength()))`).
   So the pin catches a change in the decay length, the tail cap or the filterbank, but a change to how
   the generator pads or sizes its transform (the thing Seats 2 / 3 asked to pin as the runner-independent
   proxy of the synthesis work, files 58 / 66; AX38 4c "the FFT size n … exact") is invisible to it, and
   so is a generator that stops using `fft_` at all. Why it matters here: on hosted runners this pin and
   the unit-decay length are the only assertions that stand in for the low-α restore's cost when the
   growth bound is NOT EVALUATED (which it was on Linux in the very run cited). Resolve (either): add
   `std::size_t fftSize() const noexcept { return fft_.size(); }` to `BandNoiseGenerator` (a one-line,
   JUCE-free `src/sim` change inside this phase's gate scope) and assert `BandNoiseGenerator(fb, len)
   .fftSize() == nPinned` in the records test (the probe already constructs one), keeping the formula
   line as the print; or, if the board meant the formula's value, narrow AX38 4c / phase-05h §5 and the
   test comment to say "the formula's value, not the generator's" through `/fix-plan`. The first is
   cheaper to undo and matches the decision's intent.

### Minor
1. `tests/unit/test_diffuse_records.cpp:1–5, 52–54` — stale header comments: L4 says the gated
   assertions live in `"[diffuse-gate-records]"` (no such tag anywhere in the tree; they are in
   `[diffuse-records]`), and L52–54 still says "medians to be re-baselined from the first three-OS run,
   O18" while the register now holds multi-run means (L67–75). Rewrite both to the RG-1 form.
2. `tests/unit/test_diffuse_records.cpp:446–449` — the comment says the growth bound is read "after the
   scene loop (the flutter scene runs last)", but the loop at L302–303 runs `cube100_flutter_fallback`
   first. Harmless (the GATE block at L500 runs after the whole loop either way); fix the parenthesis so
   the next reader does not look for an ordering dependency.
3. `tests/unit/test_diffuse_records.cpp:399` — `if (nPinned != 0)` is dead: both FFT-size constants are
   non-zero, so the guard only hides the intent. Drop it (or make the "0 = unpinned" convention explicit
   in the `GateEntry` comment if it is meant for the 07c re-pin).
4. `.github/workflows/ci.yml:427, 437` — `if: always()` also runs pluginval and auval when the job was
   cancelled and after a failed *build* step (the bundle is then missing, so a second, noisy failure is
   added to an already red job). The result semantics are right (the benchmark step has no
   `continue-on-error`, so its failure fails the job, and `ci-ok` requires `success`), and the plan names
   `always()` verbatim, so this is a note: `if: ${{ !cancelled() }}` is the idiom that keeps the
   host-conformance evidence without running on a cancel; change it only through `/fix-plan` since AX38
   4c and phase-05h §5 quote the expression.

### Questions (unverified, evidence requested)
1. **How often will the x64 growth bound be evaluated?** From file 56's table, the flutter median lands
   inside ±5 % of its reference in 5 of 13 x64 rows (Linux 2 of 6, Windows 3 of 7); on run 42964823518
   it was evaluated on Windows only (Linux's runner was 16.8 % *faster* than the reference, which the
   symmetric window also excludes). This is the board's chosen form (file 66, Seat 7's ±5 %; re-derived
   from ≥ 3 in-window runs at the 07c re-pin), so not a finding against the PR — but the §0 counts the
   plan now requires ("asserted / not evaluated / WARNING runs") should start with this run's 1 / 1 / 1,
   and the Expert should know the detector's duty cycle on hosted runners is under one in two. Evidence
   that would settle it: the counts after three more runs, or a one-sided window (slow runners only)
   proposed at the re-pin if the fast-runner exclusion is not wanted.
2. **Flutter strict 30 s headroom.** This run's 14 × worst are 8.31 / 10.15 / 10.53 s; the assertion at
   L459 trips at a runner ≥ 2.85 × slower than this Windows runner, against a worst observed runner
   factor of ≈ ×1.9 on file (Windows flutter 488 → 927 ms). Seat 5's "headroom ≥ 2.3 ×" holds on this
   data; a (d) defect entry, not a re-run, is the plan's answer if it ever trips. No evidence requested
   now; the §0 counts carry it.
3. **The hidden `[diffuse-records]` test was not run locally** (a Debug build on a shared 4-core box is
   neither representative nor quick for ten 100 m / 96 kHz restores). The three CI build logs (GATE
   lines, work pins, work ratios, restore lines) are the evidence used above.

## What I verified myself

- `git fetch origin claude/laughing-brahmagupta-vhem6q`; `fetch_pr.sh` → BASE=origin/main,
  HEAD=origin/claude/laughing-brahmagupta-vhem6q = 7e4937b; merge-base 8583ba1; local tree 5823b89 (one
  docs-only commit ahead, files 31 / 56). `review_context.py --base 8583ba1 --head 7e4937b`: boundary
  clean, NFR-8 hit `Engine.cpp:550` (channel id, not scene logic), no audio-thread hit in a callback,
  thread_local hits are the Debug `RealtimeMark` (pass 1 minor 6), pin scan clean.
- `git diff --stat a9d8313...7e4937b -- src` → empty: no `src/` change since pass 2 (no audio-thread,
  determinism or NFR-8 question arises from this delta).
- `python3 tools/ci/ci_fingerprint.py --rev 67f13f3 / 7e4937b / 5823b89` → all `df3845cb…d910`.
- `actions_get get_workflow_run 42964823518` / `42964826298`: both `success`, head_sha 67f13f3.
  `gh run view 42964823518 --json jobs`: 35 jobs success (three `open-field validation`, three build,
  python ×3, tail gates ×18, asan, tsan, format, contract ×3, changes, ci ok). `gh api …/artifacts`:
  7 artifacts listed above.
- Build logs (`ci12_{linux,macos,windows}.log`, grepped): GATE lines (quoted), work pins equal on three
  OSes, pluginval `--strictness-level 10` SUCCESS ×3, auval SUCCEEDED, ctest 223/223, benchmark 13 test
  cases passed. Open-field jobs: `get_job_logs` ×3, "2 passed, 68 deselected", per-band dev / SE / z
  printed (band 7: SE 0.073 / 0.076 dB → 3·SE ≤ 0.23 dB; dev −0.020 / +0.005 dB). Python job (linux):
  "571 passed, 16 skipped, 30 deselected", `test_ci_workflow.py` 21/21, smoke lines labelled
  (band 6–7 dev −1.24 / −2.85 dB at SE 2.1–2.4 dB: the capped shipping N, as pass 2 recorded).
- Re-derived in Python: the nine baselines and the trigger from file 56's table (all equal to the
  constants), the two unit-decay lengths and FFT sizes (equal to the pins), the in-window fraction (5 / 13).
- Read at HEAD: `test_diffuse_records.cpp` (L1–600 in full, L600–914 REQUIRE / TEST_CASE scan),
  `test_diffuse_gate.cpp` and `test_diffuse_agreement.cpp` diffs plus their surrounding blocks,
  `test_tail.py` / `conftest.py` diff, `ci.yml` in full (step order of the build job, action pins
  consistent across jobs: checkout v7.0.1, setup-python v7.1.0, msvc-dev-cmd v1.13.0, cache v6.1.0,
  upload-artifact v7.0.2), `NoiseTail.h/.cpp` (FFT sizing), `Engine.cpp:231–240` (the build's unit-decay
  length comes from the same `tailLengthS` / `unitDecayLength` the test uses), `Fft.h` (`size()`
  exists), AX38 4c, phase-05h §5, phase-05i scope 3, §6, CHANGELOG, files 56 and 70.
- Local build (`build/debug/_deps` existed; the tree is on the branch): `cmake --preset debug &&
  cmake --build --preset debug` → `BUILD_EXIT=0` (97 targets). `xvfb-run -a ctest --preset debug` and
  `pytest tools -m "not ensemble and not nightly and not slow and not open_field_validation"`: results
  appended below.
- Reference files: `process-rules.md`, `phase-checklists.md` (**no Phase 05h section exists; the Phase
  05 section was used**, with the phase file as the checklist — the skill's reference needs a 05h entry),
  `tooling-testing-licences.md` items 33–39 (39: "does a benchmark gate CI on timing from shared
  runners?" — the RG-1 form is exactly the answer to that item: timing is reported, work is asserted),
  `realtime-audio-juce.md` §10 (no audio-path code changed), `metrics-and-validation-data.md` §9 (the
  open_field reference is an independent integral; τ unchanged).

### Local run results
(filled in below once ctest and pytest finish)

## For Maisara

The listening checklist (phase-05h §6) is yours; nothing here ticks it. The listening pack of run
42964823518 is the `listening-pack` artifact
(https://github.com/maisara-abourady/makroof/actions/runs/42964823518/artifacts/13830673901, 236 MB),
folder `phase-05h/` (12 renders: the six Phase 04 rooms, open_field, bras_cr3_ls1_mp2, the three T52
layouts, club_both_near_0.3); plugin bundles `SpatialScene-{linux,macos,windows}` and the pluginval logs
sit beside it.
For the Expert: (1) the restore gate on shared CI machines now judges the work exactly and the restore
time only when the machine is at normal speed (RG-F1, file 70); in the final run that was one OS of
three, and macOS printed a GROWTH warning (2 069 ms against 1 999, under the 2 172 ms trigger) with
31.82 s against 30 s — recorded, not a failure; Linux and Windows printed PASSES30S (25.29 / 29.51 s), so
by §5 (c) those two listed entries leave the register through `/fix-plan` before the next phase is
`done`; (2) the open_field level at 4–8 kHz now agrees with the independent floor integral within
0.02 dB at 2^23 histories (pass 2's +0.29…+0.37 dB at 2^20 was noise, as the board read it); (3) the
CLAUDE.md step 6 / BUILD_PLAN preamble wording conflict on "done" (pass 1) still stands.

## Contractor review focus (from phase-05h §7), with pointers into the diff

- The restore gate's assertion form against the plan text: `test_diffuse_records.cpp:62–107` (register),
  `:346–423` (work pins and solve print), `:446–471` (per-scene gate lines), `:500–543` (GATE lines and
  the guarded growth REQUIRE) against AX38 4c and phase-05h §5 (a)–(d) — audited above; Major 1 is the
  one gap.
- The runner-independence claim of the pins: `NoiseTail.cpp:80–83`, `Engine.cpp:231–240`,
  `test_diffuse_gate.cpp:667–746` (the two-scene split-timer probe that produced the pins).
- The CI job split and the `always()` steps: `ci.yml:269–323`, `:425–437`, `:549–552`;
  `tools/ci/test_ci_workflow.py` (unchanged, still passes with the new job).
- AX46's six-class form: `test_diffuse_agreement.cpp:167–176, 268–275, 361–436` (SE_prop from the
  per-case SEs; `bras` printed before the 100 m tracer line).
- The validation-N open_field check: `test_tail.py:196–253`, `conftest.py:28–33` (marker registered
  under `--strict-markers`).
- No counterpart in this delta: the solve seam, the gate class order, the D5 hashes (passes 1–2).

## Follow-ups the PR should list
- §5 (c): the Linux and Windows low-α entries printed PASSES30S on run 42964823518 → `/fix-plan` removal
  before phase 05i is `done` (phase-05i scope 3 (ii)).
- §0 row 05h at `done`: the GATE counts per OS and the latest figures; the WARNING run (macOS GROWTH,
  42964823518) named in the PR; AQ9 before/after (pass 2 minor 4).
- The skill's `phase-checklists.md` has no Phase 05h section (a review never edits the skill; noted for
  the maintainer).
