# 53 — Orchestrator: the Windows strict restore-gate entry crossed 30 s on CI run 42942694523 (D-H1 (v)(d) applied)

## The record

CI run 42942694523 (cb7effb; the final tree with the `open-field-validation` job), `build (windows)` job 130268111168,
Release benchmark step, `test_diffuse_records.cpp` L393 `REQUIRE( fourteen <= 30.0 )`: `36.7347904 <= 30.0` false.
Every other job of the run green (32 of 33; `open-field validation` 10.2 / 11.8 / 14.3 min on macOS / Linux /
Windows, the python jobs 7.2 / 8.9 min); nightly 42942697249 green.

```
05h-records restore cube100_lowalpha0.05_s0.3  96 kHz with the solve, 10 runs: min 2476 median 2589 worst 2624 ms; 14 x worst 36.73 s (30 s)
05h-records restore gate cube100_lowalpha0.05_s0.3  Windows: strict (recorded 29.04 s <= 29.1 s): 14 x worst 36.73 s <= 30 s
05h-records restore cube100_flutter_fallback   96 kHz with the solve, 10 runs: min 910 median 927 worst 940 ms; 14 x worst 13.15 s (30 s)
05h-records full rebuild cube100_lowalpha0.05_s0.3   96000 Hz: min 2503 median 2555 max 2584 ms
05h-records (iv) cube100_lowalpha0.05_s0.3   96000 Hz, 8 instances: load until the last is audible 25368 ms
```

The Windows runner of this run was slower on the restore, flutter and full-rebuild records: the flutter restore
13.15 s against 10.66 s on run 42909003931 (file 31), the low-α full rebuild 2 555 ms against 1 948–2 026 ms, the
low-α restore median 2 589 ms against 2 000 / 2 056 / 1 926 ms on runs 42909003931 / 42924781618 / 42935789745
(14 × worst 29.04 / 29.50 / 28.57 s); the (iv) 8-instance load 25.4 s was inside the earlier 24.4–25.6 s. Nothing in the tree between b8b3c6d (run 42935789745) and cb7effb
touches `src/`, the tests the records run, or the build flags: the diff is `ci.yml` (a new job, a timeout and a
deselection on the python job), `tools/acoustics/tests/conftest.py` and `test_tail.py`. The likely cause is runner
speed on a shared Windows runner (to be shown at Phase 13's release-machine re-check, as the macOS entry's form
says), as review file 39 minor 3 warned ("the Windows strict entry's margin is now 0.50 s
(1.7 %) on a shared runner; by D-H1 (v)(d) a crossing is a defect").

## The rule (no decision needed: D-H1 (v)(d), accepted for Maisara, decider file 19, interrogator file 21)

Phase-05h §5, the blocking restore gate, (d): "A new failure at an unlisted OS/scene, or a listed entry breaking its
growth bound, is a defect: no re-run, no W_max cut after pinning, no room-range narrowing, no formulation seam; it
enters the register with its remedy, phase-07c forward and then phase-07c §5 condition 9 (the unit-decay synthesis
off the synchronous restore). This phase may be set `done` with the register entries recorded in §0 row 05h; the
macOS and Windows records go to Maisara in the PR (section 2 item 2)." AX38 4c's register carries the same rule and
the macOS entry's form ("or, if the runner is shown to be the cause, at Phase 13's release-machine re-check, as §0
row 06 already does for the macOS callback p99.9").

## Applied

- `tests/unit/test_diffuse_records.cpp` `kGateRegister`: the Windows low-α entry becomes a listed defect, recorded
  14 × worst 36.73 s, growth-bound baseline the run's median 2 589 ms (D-H1 (v)(b) as applied at O18 for the Linux and macOS
  entries: a one-run median; the bound 1.10 × 2 589 = 2 848 ms sits 38–48 % above the three strict-run medians, so
  it will not fire on a normal runner; Phase 13's strict re-check is the backstop), asserted as median-of-10 ≤ 1.10 × 2 589 = 2 848 ms; the flutter scene stays
  strict on every OS. `tests/golden/CHANGELOG.md` records the constants (not a golden).
- AX38 4c register (plan-editor): "`cube100_lowalpha0.05_s0.3` on **Windows** (strict 29.04 / 29.50 / 28.57 s on
  runs 42909003931 / 42924781618 / 42935789745; medians 2 000 / 2 056 / 1 926 ms; 36.73 s, median 2 589 ms, on run 42942694523, a shared runner 25–30 %
  slower on the restore, flutter and full-rebuild records; listed from that run under §5 (d), baseline 2 589 ms;
  remedy: phase-07c condition 9 (or 07d) and 10, or Phase 13's release-machine re-check if the runner is shown to
  be the cause, as the macOS entry)"; phase-05h §5 (b) and phase-05i scope 3 name the entry; a §6 row.
- No re-run of the failed run; CI run 10 on the head carries the register in its new form, as (d) says ("enters
  the register"), and its Windows line is recorded whatever it reads.
- The macOS and Windows records go to Maisara in the PR (section 2 item 2): R2's table gains the Windows line.

The remedy's premise (phase-07c conditions 9–10 take the synthesis and the solve off the synchronous restore,
≈ 0.15 s left) is unchanged; the register's purpose (D-H1 (v): the gate never red by runner speed, the defect
never hidden) is served by listing, not by re-running.

Interrogator file 54: OK with wording fixes A–D (applied above and in the test comment, the CHANGELOG entry and the
plan-editor brief); the PR attaches `git log --stat b8b3c6d..cb7effb`.
