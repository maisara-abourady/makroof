SEAT 5 POSITION

**1. Reading.** How to produce L4 stimuli (provisional tail against exact tail) without weakening AX5/AX49's rule that offline renders and `render_cli` never use the provisional, and without the plugin ever reaching a validation path. Cues triggered: S5 (offline must not differ from playback), CS-3.6/CS-5 (a gate that is checked by machine, not by convention), §9 "prefer the design where the unsafe thing cannot be expressed", and S7 (a new path reachable from shared code).

Fact from the code: `src/plugin/core/ScenePipeline.cpp` L656 and L704 already call `StagedBuild::assembleProvisional`. So "src/plugin never reaches it" can only mean the CLI option. A test that greps `src/plugin` for "provisional" would fail on legitimate code. The guard has to name the option field (e.g. `provisionalIr`) and the flag string, as `test_plugin_never_reaches_the_step_flag` does for `abxStepDb`.

**2. Ranking.**
- **L-a: prefer.** It reuses the stimulus path the kit already trusts (`render_cli` Release from the `cli` preset, `--realtime-emulation`, a fixed block), which already nulls against offline (Phase 06). The flag follows the gating pattern of `--abx-step-db` (Cli.cpp L274–282, L350–375).
- **L-b: can live with.** No wording change, but it creates a second render path for sealed stimuli.
- **L-c: can live with,** only if the date is before 07d's gate work freezes the restore path.

**3. Tension now.**
- **L-a: 1.** About 40 lines of parse and validation code, plus one guard test and one end-to-end test. The AX49 sentence widens, but only behind an explicit flag.
- **L-b: 1.** Builds on existing test patterns (`test_interim.cpp` L311–369 already calls `assembleProvisional`). But `abx_kit.py` would have to drive `spatial_tests` as well as `render_cli`, and the python CI job builds only the `cli` preset, with no tests.
- **L-c: 0.**

**4. Tension later (the debt).**
- **L-a: 1.** It commits every later flag change to keep the guard test green. Undo cost: deleting one option. Evidence that could overturn it: any default `render_cli` output changing bit-wise when the flag is present in the build. A golden hash would catch that.
- **L-b: 2.** Stimuli would come from a binary that is neither the shipped one nor the CLI. A hidden Catch2 test is not run by CI unless someone wires it in, so it rots silently. If it is built from the `debug` preset, its floats may not be bit-identical to the Release `render_cli` or plugin build: optimisation level and FP contraction can differ `[Hyp]`, which breaks AX5's same-platform bit-identity as a provenance claim for the seal hashes. Undo cost: re-sealing the stimuli. Evidence arrives at the first cross-build hash comparison.
- **L-c: 2.** AX49 ships a restore path whose reversal trigger ("the L4 ABX detects the cut") stays unread. 07d's gate closure and the record (h) work are built on that path. A late detection reopens ScenePipeline's restore threading after more code depends on it: a phase of rework, not a parameter change. Evidence arrives at L4, whenever it runs.

**5. Evidence.**
- From the code: Cli.cpp L67–75 and L350–375 (validation-only gating, mutual exclusions); Engine.h L295–298 (the comment "render_cli never call it", condition 6); ScenePipeline.cpp L656 and L704 (the plugin is a legitimate caller); `test_abx_kit.py` L188–197 (the guard pattern). Tag: `[Observed]`.
- AX5: bit-identical on the same OS and architecture (BUILD_PLAN §2). AX49: "Offline renders, bounces in hosts that signal offline, and render_cli never use the provisional."
- Debug and Release builds differing in floats: `[Hyp]`. Researcher or builder: compare the hash of `assembleProvisional` between the `debug` and `cli` builds on one runner.
- Corpus not needed. I make no acoustic claim.

**6. Conditions of acceptance.**
- **L-a** (to keep it at 1/1):
  - (i) Off by default.
  - (ii) Requires `--mode omni`. Excludes `--ensemble`, `--abx-step-db`, `--switch-scene`, `--tail-level ax16` and `--automation` (so no future host-bounce emulation can pick it up).
  - (iii) The guard test is extended: `src/plugin` never names `provisionalIr` or `--provisional-ir`, and only `src/cli/Cli.cpp` uses the field.
  - (iv) An end-to-end test with `SPATIAL_REQUIRE_RENDER_CLI=1`:
    - the default output is bit-identical with and without the flag compiled in (golden hash);
    - the flagged output is bit-identical run to run;
    - offline and `--realtime-emulation` with a fixed block null as in Phase 06;
    - on the L_p ≥ L scene, the flagged output is bit-identical to the default.
  - (v) AX49 is amended to read "…and render_cli never use the provisional, except under the validation-only `--provisional-ir` flag; host offline bounces never do". This goes through /fix-plan with a §6 change-log row.
- **L-b** (2 → 1 later): the harness is built from the `release` preset only. A CI job runs it and compares its stimulus hash with the `assembleProvisional` hash in `test_interim`. The kit records which binary and preset made each sealed file.
- **L-c** (2 → 1 later): a named date before 07d's gate-closure decision. AX49's reversal list states that L4 is unread until then. 07d may not freeze the restore path before L4 is scored.

**7. Hand-offs.**
- Seat 1: L4 design, the anchor, M3-T.
- Seat 2: the scene with T60_max 8 s and L_p < L.
- Seat 3: whether the provisional tail is faithful and the handover crossfade inaudible.
- Seat 7: hours.
- The interrogator/plan-editor: the AX49 wording change under L-a.

**8. Premortem.** If L-b is chosen and fails: stimuli are sealed from a Debug test binary whose tail differs bit-wise from what Release `render_cli` and the plugin produce. The seal hashes stop matching on the first rebuild. The builder notices first, and L4's result no longer describes the shipped provisional.
