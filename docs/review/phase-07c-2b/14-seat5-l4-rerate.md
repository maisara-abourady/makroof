# 14: Seat 5 re-rates L-a as decided (r1 and --provisional-handover-sample)

Asked per interrogator file 13 ("The decider's own flag": TENSION MISREAD on Seat 5's L-a cell). Seat 5 now rates r1 0/0 and the handover flag 1/1, L-a as decided 1/1, with the conditions below; L-a's maximum stays 1, so file 10's ordering stands and the misread is closed. Its conditions (r1 decided before any output file is opened; test 6 asserts no output file after r1; r5 mirrors --abx-step-sample; the handover through the RealtimeEngine IR-publication path, not a CLI-local crossfade; fade length ceil(0.030 fs); test 8 comparator; test 3 per OS; the unscored label in file name and pack index) are adopted as implementation requirements of L4-P (orchestrator note, 2026-11-24). Recorded verbatim below.

SEAT 5 POSITION (later round: L-a as decided in file 10 L4-P, with r1 and `--provisional-handover-sample`)

**What changed:** two departures from my conditions. I rate each, then L-a as a whole.

**1. r1 (refusal where L_p ≥ L) in place of my (iv) last bullet: accepted, tension 0 now / 0 later.**
- My (iv) bullet existed so that the flag could never produce something surprising on the L_p ≥ L branch. A refusal is stricter: it cannot output an "exact" file labelled as provisional. By §10 rule 5, a design where the unsafe output cannot be produced beats one where it must be checked.
- I give up nothing measured. The equivalence I wanted is already asserted below the CLI: `tests/unit/test_interim.cpp` L311 requires `bitIdentical(a.assembleProvisional(), b.assemble())`, which is Engine.h L295–297's L_p ≥ L clause, from the code.
- Conditions (small, no rating change):
  - (a) r1 is decided from `provisionalTiming()` before any output file is opened or truncated, so a refused run leaves no partial or stale WAV for the kit to pick up.
  - (b) Test 6 asserts that no output file exists after r1 on the 100 m cube.
  - (c) Exit code: AX12 has 1 for usage and 2 for an invalid scene. The scene is valid, so 1 (a flag that does not apply to this scene) is consistent; say so in the error text.

**2. `--provisional-handover-sample N`: accepted, tension 1 now / 1 later.**
- For my seat this is a gain. It drives the provisional-to-exact handover through the real-time engine's IR swap with the shipped AQ4 fade. That is S1/CS-2 exercised end to end, which no test does today outside the plugin.
- The cost: one more validation option to guard, plus test 8.
- Conditions to keep it at 1/1:
  - (i) The swap goes through the same `RealtimeEngine` IR-publication path the plugin uses (the path `--switch-scene` and `--abx-step-db` already use). It must not be a CLI-local crossfade. Otherwise test 8 proves a code path that does not ship.
  - (ii) r5 mirrors `--abx-step-sample` exactly (Cli.cpp L365–373): N is a multiple of the partition **and** of the block, N is at least one partition, N lies inside the input, and N is the output sample where the fade starts (the interrogator's correction, file 13).
  - (iii) The test 8 comparator, as the interrogator corrected it:
    - from N + fade length, bit-identical to the `--realtime-emulation` exact render with the same block and partition;
    - against the offline render, the −120 dB null only.
    - The fade length is ⌈0.030·fs⌉, not a literal 1440, or the flag refuses rates other than 48 kHz.
  - (iv) The provisional and exact IRs come from one StagedBuild plan at one level, both built synchronously before the first block. This is stated in the help text: the flag shows the DSP of the handover, not its timing. Timing remains record (h)'s job.
  - (v) The guard (test 1) and the no-golden test (test 2) name `provisionalHandoverSample` and the flag string, as file 10 already lists.
  - (vi) The listening-pack render carries its "unscored" label in the file name and in the pack index, so it can never enter a seal.

**3. L-a as decided: now 1, later 1.** It stays at prefer, provided the interrogator's test 3 correction is applied: a SHA-256 per OS, or a comparison with and without the flag on each runner. A single cross-OS pin would fail on AX5's same-platform clause and push someone to weaken the test. If test 3 ships as one cross-OS hash, later rises to 2: a red gate on a correct build gets bypassed. Undo cost: one test edit.

**Evidence.**
- From the code: Engine.h L295–298; test_interim.cpp L311; Cli.cpp L350–375 (the step-sample gating).
- BUILD_PLAN §2 AX5, AX12, AX18, AX49; file 13 rows for r5 and tests 3 and 8.
- No acoustic claim, so no corpus citation.

**Hand-offs.**
- Seat 3: whether the handover fade is inaudible in the demo render.
- Seat 6: the demo's label wording.

**Premortem.** If the handover flag is wired through a CLI-local crossfade rather than the engine's IR swap: test 8 goes green, the demo sounds clean, and the plugin's real handover stays untested. The first person to notice is a user who hears the swap at project load.
