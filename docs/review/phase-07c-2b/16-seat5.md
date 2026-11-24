# 16-seat5: Seat 5 on the [ax49-l4] CI placement

Saved verbatim by the orchestrator from the seat's final report (read-only agent), 2026-11-24.

SEAT 5 POSITION (file to save as docs/review/phase-07c-2b/16-seat5.md)

**1. Reading.** Where in CI the seal-gating Catch2 case `[ax49-l4]` goes. My cues: "make the wicked task scorable", "a gate placed among records gets forgotten", and my headroom rule (worst case at no more than half the limit), applied here to the CI timeout.

Facts taken from the code:
- **ctest in CI.** It runs only the Debug preset (Linux, macOS, Windows) and ASan (Linux) (`ci.yml` L391–398, L550). The Release tests are built but never run by ctest. Release runs only `"[benchmark]"` and the denormal probe (L410–422).
- **Timeout.** The ctest preset gives each test 600 s (`CMakePresets.json` L118). `catch_discover_tests` makes `[ax49-l4]` one ctest test.
- **The case builds S′ three times.** Catch re-enters the case once for each of the two leaf SECTIONs, so S′ is built twice, and N-L2 builds a third scene.
- **What option (a) actually covers.** Debug on 3 OS plus ASan. It gives no Release evidence at all, yet Release is the binary that ships.

**2. Ranking.**
- **(c), my option: prefer.** Two parts:
  - Leave `[ax49-l4]` non-hidden in the default set, so ctest runs it in Debug on all three OS and in ASan.
  - Add one explicit gate step to the build matrix after "Build (release)", separate from the Benchmark step: `"$BIN" "[ax49-l4]" --durations yes` (under `xvfb-run -a` on Linux).
- **(a): can live with.** It reaches three OS but not Release.
- **(b): can live with, barely.** It reaches Release on three OS, but the case is hidden from local and Debug ctest.

**3. Tension now.**
- **(c): 1.** It adds one Release run of tens of seconds per OS, plus the Debug and ASan time of (a).
- **(a): 1.** Each PR pays the Debug and ASan time, which nobody has measured. Debug runs several times slower than Release, and the 600 s limit is shared with nothing else, so the margin is unknown.
- **(b): 2.** A hidden case is skipped by a plain `ctest`, so a change in `src/sim/tail` that breaks P4/P5 shows up only in a Release CI run. Tagging it `[benchmark]` would also mislabel it: it is an assertion, not a benchmark, and it would sit in a step this repo treats as "records, never gates" (L424–428).

**4. Tension later.**
- **(c): 1.**
  - The cost is the same per-PR time as (a), and undoing it is a one-line tag or step change.
  - Evidence that could overturn it arrives with the first `--durations` reading in Debug and ASan.
- **(a): 2.**
  - Every later phase that touches the tail inherits a test of minutes or more on Debug and ASan. If tail lengths or band counts grow, it drifts toward the 600 s timeout and becomes a flaky red that someone "fixes" by hiding it.
  - The ships-as-Release numerical path stays untested at 1e−9. FP contraction and vectorisation differ between Debug and Release `[Hyp]`, and P4 is an exact-scaling identity.
- **(b): 2.**
  - Hidden gates are forgotten: the seal evidence lives in one step that a later edit to the records summary or the benchmark filter can drop silently.
  - Developers' local runs never see it.

**5. Evidence.**
- CI step layout, the timeout and the SECTION re-entry are all read from the code (files and lines above).
- "Tens of seconds in Release" is the builder's local measurement relayed in the brief. The Debug and ASan multiples are `[Hyp]`, not measured.
- Memory is also `[Hyp]`, assuming double samples. One set of unit decays is 12 s × 48 kHz × 8 bands × 2 emitters × 8 B ≈ 74 MB. Exact, provisional, the N-L1 copy and the N-L2 build together come to about 300–370 MB, and more under ASan shadow memory. That fits the runners, but **the builder should report peak RSS**.
- The 0.5 × limit headroom is my Section 0 rule `[Hyp]`, carried over to CI.
- The corpus is not needed: no acoustic fact is involved.

**6. Conditions of acceptance.**
- **Tag form.** Keep `"[ax49-l4]"` exactly: no `[.]` and no `[benchmark]`. The hidden probe stays `[.]…` as R5(a) allows.
- **Time budget per run of the case** (whole case, all sections). Each limit is at most half the applicable limit.

  | build | budget | why |
  |---|---|---|
  | Release | ≤ 60 s per OS | |
  | Debug | ≤ 300 s per OS | half of the 600 s ctest limit |
  | ASan | ≤ 300 s | half of the 600 s ctest limit |

- **Before the seal**, the builder measures Debug and ASan locally with `--durations yes` and records the numbers in the PR.
- **If Debug or ASan exceeds 300 s:** first remove the re-entry so S′ is built once (run N-L1 and N-L2 inline, or cache `bt` in the case). That cuts three builds to two. Do not hide the case. Only if it is still over 300 s does the Debug and ASan run move to a `[.][ax49-l4-slow]` twin, with the Release gate step kept on all three OS. That would raise (c) to now 1, later 2.
- **With these met:** (a) becomes 1/1 if Seat 3 accepts having no Release evidence. (b) drops to 1/1 only if the hidden case gets its own named gate step (not inside Benchmark) and the local `ctest` docs in CLAUDE.md name it.
- **Seal evidence.** It must be a CI run whose fingerprint includes `tests/unit/test_ax49_l4.cpp` at its sealed content, showing the `ax49-l4:` printf line and green on all three OS. A skipped run that links to such a run counts.

**7. Hand-offs.**
- Whether Debug-only coverage (option (a)) is enough for P4/P5 at 1e−9 is Seat 3's call.
- Whether 1e−9 survives Release FP contraction on MSVC is the builder's measurement, routed to Seat 3.
- The `ci.yml` edit goes through the phase PR; `tools/ci/test_ci_workflow.py` must stay green.

**8. Premortem.** If the case goes in hidden (b), a later tail refactor breaks the fade, every local and Debug ctest stays green, and the first person to notice is the contracted engineer reading a red Release step at PR time, or nobody if the step's filter is edited.
