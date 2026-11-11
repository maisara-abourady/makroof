# Seat 5 — D-H1 and D-H2 (phase 05h session 2)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

Files read: `docs/review/phase-05h/4-decider-convene-D-H1-D-H2.md`, `3-orchestrator-D-H1-D-H2-question.md`, `1-orchestrator-cpp-costs.md`, `2-review-PR27.md` (m-2, m-3, m-10, Q-3); `docs/phases/phase-05h.md` §2–§5, §8; `docs/phases/phase-07c.md` §0, §3, §5; `docs/BUILD_PLAN.md` §2 AQ10 (amended), AX36, AX38, AX41–AX46, §0 rows 06/07/05h; `docs/review/phase-05b2/` 45-seat5-R1-R3, 35-seat5-confirm-S5b, 3-seat5-T5-T4, 4-researcher-T5-T4 (F16–F20), 47 §4, 51 §3–§4, 53 §1, 54, 55; `docs/sessions/2026-11-10-phase-05h.md` Session 2 (O11, O15, O18, Constraints); `tools/ci/run_pluginval.sh`; `.github/workflows/ci.yml`, `nightly.yml`; `tests/unit/test_diffuse_bench.cpp`; `src/plugin/core/ScenePipeline.cpp` L337–363; `tests/state/parameter_ids_v1.json`; corpus `vorlaender-auralization.md` (Table 6.1, §11.2.5 Eqs. 11.9/11.15/11.21/11.28). Corpus present (c1b171f).

---

# SEAT 5 POSITION — D-H1

## 1. Reading

Pin the constants of the diffuse estimator and decide how a blocking CI gate is run when the measurement already says it fails on one OS at every W_max ≥ 0. Cues: §10.2 (worst case before common case), §10.3 (what the host can do to me: 14 silent restores under pluginval), §4.4 (a test that only passes on one buffer size / one OS), §17 (my own blind spot: over-weighting tooling), WI-3 (Rowland: calibrate the instrument; if everything fails a test, fix the instrument, not the plugin).

**One fact that frames everything (from the code and the researcher's record).** The "14" in 14 × t_restore is the count of non-bypass automatable parameters: 14 ids in `tests/state/parameter_ids_v1.json`; pluginval's "Plugin state restoration" test restores once per such parameter with no log inside the loop (researcher file 4, F18, confidence M–H), and the watchdog is an **inactivity** watchdog reset by "any log message or result update" (F17, H), default 30 000 ms (F16, H). Two consequences: (i) K4 in the decider's inventory is not "no researcher finding on record": F16–F18 exist; what is still open is narrower (see §7). (ii) Our own CI runs pluginval with `--timeout-ms 120000` (`run_pluginval.sh` L19), so a green pluginval job in CI is **not** evidence for the 30 s gate; the Catch2 restore test is the only instrument. `ScenePipeline::restore()` never short-circuits on an unchanged scene (L342–363: every call bumps `dirty_`, decides and rebuilds), so pluginval's 14 near-identical restores each build, as the bench assumes.

## 2. Ranking (per sub-choice)

| sub-choice | prefer | can live with | cannot live with |
|---|---|---|---|
| P | P-a (s = 0.3) | P-b | — |
| R | R-c (fixed ≥ 0.05 dB) | R-a, R-b, R-d | — |
| Q | Q-d (1.02) | Q-b (1.01), Q-a (1.05, my old [Hyp], retired) | — (Q-c 1.00 rated 1/2, not veto) |
| W | **W-x (mine, below)**: W_max 3.05 M pinned; the gate implemented on all three OSes as a strict defect register with a growth bound; 07c forward next; the non-diffuse 100 m build named as a separate finding | W-c; W-e only if recast as W-x | — (W-a and W-b as written rated 2/2) |
| N | N-a (1 024) | N-b only at ≤ 1 408 | — |

**W-x, my option.** Same W_max and remedy as W-a. The gate test runs on every Release run on Linux, macOS and Windows and asserts, per OS and gated scene: (a) 14 × (worst-of-10 restore + worst-of-10 solve) ≤ 30 s **unless** that OS/scene is listed in a defect register in plan text (phase-05h §5 / §0 row), each entry naming the recorded value, the remedy and the phase that closes it (07c for the solve share; the Phase 07 build finding for the rest; Phase 13 real hardware for the macOS runner question, as §0 row 06 already does for the macOS callback p99.9); (b) for every listed entry, a **growth bound**: median-of-10 restore ≤ 1.10 × the recorded median (the settled Trigger text requires detecting "any growth of the non-diffuse build"; the median, not the worst, so the shared macOS runner's 50 % tenancy spread does not flake it; this is not X1, which concerned the margin input); (c) an unexpected pass (listed OS under 30 s) is reported in the job summary and the entry must be removed (strict, or warn: decider's choice). The per-OS min/median/worst and the 14× figure are printed in the job summary on every run. Nothing here re-runs, cuts W_max, narrows ranges or adds a seam; the remedy stays "(C) forward".

## 3. Tension now

| option | rating | what it costs my seat now |
|---|---|---|
| P-a / P-b | 1 / 1 | Same non-diffuse build (s does not enter it); the 2.33 vs 2.59 s macOS worst is runner noise (medians 1.88 / 2.08). P-b makes the gate scene one whose floor already fails, so every later rise is an escalation: operational noise, not a safety cost. |
| R-c | 0 | One constant; no derived golden. |
| R-a / R-b | 1 | Needs a frozen starting-state replicate SD per scene as a golden with a never-regenerate rule. Deterministic (fixed streams), so no chance firing; ≈ 30 × 0.1 s × 2 cubes ≈ 6 s Linux / 10 s macOS per run; the long run is offline and committed. |
| R-d | 0 | Cheapest; whether it is too weak is Seat 1's. |
| Q-d 1.02 | 0 | Above every observed value (C++ ≤ 0.991, prototype ≤ 1.009) with ≈ 1 % headroom for final-range cost scatter. |
| Q-b 1.01 | 1 | 0.1 % over the prototype max; fine at the gated scenes (N 2 624–2 688, scatter small) but no headroom for a scene added later. |
| Q-a 1.05 | 1 | Loose; catches only gross accounting regressions. |
| Q-c 1.00 | 1 | Asserts a property the design does not guarantee (N_cap fixes N, not realised cost); a benign 0.5 % scatter becomes a "defect" under the no-re-run rule. |
| W-a as written | **2** | A required check red by design on macOS (32.6–37.4 s) and Linux (30.27–30.42 s). From the code (`ci.yml` L476–478, L503–516): `ci-ok` saves the pass marker only on a fully green run, so a by-design red also disables the fingerprint skip for every later PR; CLAUDE.md step 6 cannot set `done` while an automated criterion is red on any OS. A red everyone learns to ignore is the inverse of my §17 blind spot and worse: it kills the signal. |
| W-b as written | **2** | Linux "passes by construction" with ≈ 0 margin: budget left after the worst restore 0.07–0.08 s, solve at ≈ 2.1 M ≈ 0.065–0.076 s. The between-run spread of the cube's worst restore is 2.5 % (48.6 ms on 2 003 ms, Windows runs 42841138286 vs 42846229834; the 9 % figure is the flutter scene's), which alone exceeds that margin. A block that flakes under the no-re-run rule turns timing noise into "defects". Plus a golden round now and another at (C). |
| W-c | 1 | CI is clean (no gate in 05h); but 07c depends on 05h `done` and moves a seam that exists only once scope 2 lands: W-c is W-a with the gate deferred to a 05i after 07c, which the plan wording must say. |
| W-e as written | **2** | Enforces on the one OS with zero margin (Linux: red at 3.05 M; ≈ 0 margin at W-b's value); records on the one OS that passes (Windows 28.0–29.0 s). Right pattern (AX38 4c memory block; §0 row 06), wrong placement. |
| W-x | 1 | The macOS result is a defect on the register, not a red; `ci ok` stays meaningful; growth is still blocked. Costs one register entry per failing OS/scene and the summary printout. |
| N-a | 1 | W1 diffuse share worst observed 13.98 ms (macOS max) of 25 ms: 44 % headroom. |
| N-b (1 792–2 816) | **2** | Linear scaling [Hyp]: at 1 792 the macOS max → ≈ 24.5 ms (0 % headroom on the worst observed value, measured on a shared runner); at 2 816 the macOS median alone → 24.8 ms. W1 is the common-case rebuild (every drag), not the gate. |

## 4. Tension later (the debt)

| option | commits later phases to | undo cost | evidence that could overturn | rating |
|---|---|---|---|---|
| P-a | nothing on my side; the register entries name the scene | plan edit | O18 clause (d) replicates (Seat 1) | 1 |
| P-b | a gate scene permanently in escalation mode | plan edit | same | 1 |
| R-c | one constant in plan text | parameter | Seat 1's replicate data | 1 |
| R-a/b | a never-regenerate golden (SD per scene) that must survive every W_max re-derivation (07c, Phase 13) | golden bookkeeping | same | 1 |
| R-d | nothing on my side | — | — | 1 |
| Q-d / Q-b | one pre-registered constant; re-measure at the pinned W_max before the first CI run (known exactly: the count is deterministic, D7; W_pilot/W_final are already in the D5 table and should be asserted exactly there, the ratio being only the scene-generic guard) | parameter, but "not changed afterwards" | a cross-OS N mismatch (m-3) shows first in the D5 golden, not here | 1 |
| Q-c | a false "defect" the first time a new scene scatters above 1.000 | board round | any added gated scene | 2 |
| W-a | a red required check through 05i, 07c and every PR between; skip mechanism dead; 07c does not cure macOS (32.6–36.3 s without the solve), so the red outlives 07c | re-cast as W-x (a day) | RQ-H1-2 (runner tenancy); Phase 13 real hardware | **2** |
| W-b | a fragile Linux block; two golden rounds (now and at 07c); Seat 1 pays ×1.21 SE meanwhile (Vorländer Eq. 11.21, σ_L ∝ 1/√N; corpus checked, arithmetic redone: √(3.05/2.09) = 1.208) | golden round | first flaky red | **2** |
| W-c | the (C) W_max (≈ 54–68 M at one thread) pinned before the AX38 record "offline-bounce time of a 3-minute room-size automation at 100 m" exists; under room-size automation every changed block solves (≈ 94 builds per audio second at 512/48 kHz, my file-3 note [Inferred]), so that record scales with W_max; and the macOS gate still fails after (C) | golden round; phase reorder | 07c's own records | 2 |
| W-e as written | same as W-b on Linux plus a FOR MAISARA reading spent on the wrong OS | plan edit | first flaky red | 2 |
| W-x | a register that must shrink: 07c removes the solve share (Linux 28.9–29.0 s, Windows 28.0 s pass; macOS 32.6–36.3 s stays listed until the Phase 07 build shrinks or Phase 13 measures real hardware); the growth bound re-baselined only through plan text | plan edit per entry | RQ-H1-2; Phase 13 | 1 |
| all W | the gate's multiplier is the automatable-parameter count (14, frozen by the ID test; phases 08–11 add no host parameter per their files); any new automatable parameter re-derives the per-restore budget 30/N | parameter | a new parameter id | 1 |
| N-a | nothing new | — | O18 W1/W2 per OS | 1 |
| N-b | a second W1 re-measure under (C) and lower N_cap at the capped cubes (Seat 1's floor at s = 0.3 already rests on clause (d) only) | golden round | O18 | 1 |

## 5. Evidence

- 14 = parameter count: from the code (`parameter_ids_v1.json`, 14 ids incl. `output_mode`); interrogator file 8 D-T4c and decider file 5 D4-L6 derived the gate this way. [Observed]
- pluginval v1.0.4: default timeout 30 000 ms, inactivity-based, reset by log or result update; restoration test one restore per non-bypass automatable parameter, no log in the loop: researcher file 4 F16 (H), F17 (H), F18 (M–H). CI passes 120 000 ms: from the code (`run_pluginval.sh` L19). [Peer-report; Observed]
- Restore numbers, solve costs, spreads: file 1 §3–§4, runs 42846229834 / 42841138286. [Observed]
- `ci-ok` pass-marker semantics: from the code (`ci.yml` L476–478, L503–516). [Observed]
- Restore never short-circuits: from the code (`ScenePipeline.cpp` L342–363). [Observed]
- SE ∝ 1/√N: corpus Vorländer §11.2.5, Eq. (11.21) σ_L = 4.34√(A/(8πN r_d²)) (and 11.9, 11.15, 11.28); conditions: Poisson hit counts, so replicates, not the formula, are the evidence here, as the decider says. 1 dB jnd of G: corpus Table 6.1. [Observed, corpus]
- Precedent for "recorded on the shared macOS runner, proven on real hardware in Phase 13": BUILD_PLAN §0 row 06 (macOS p99.9 657 % wall / 110 % thread-CPU, handed to phase-13 item 9). [Observed]
- Linear scaling of the W1 share with n\*_max: [Hyp] (the decider's too).
- "No OS has a robust block at any W_max ≥ 0 today": [Inferred] from the numbers above (margins: macOS < 0; Linux ≈ 0 at W-b, −1 % at 3.05 M; Windows 3.3–4.3 %).
- My S5-b condition (ratio ≈ 1.05) was [Hyp] "to be set from C++ data": the data are in, it retires.

**Formula check (decider's arithmetic, redone).** 30/14 = 2.1429 s. Linux s = 1: (2.1429 − 2.0745)/2 = 0.0342 s / 16.4 ns = 2.09 M ✓; s = 0.3: (2.1429 − 2.0630)/2 = 0.0400 s / 16.4 ns = 2.44 M ✓. Windows: (2.1429 − 2.0035)/2 / 11.7 ns = 5.96 M ✓; (2.1429 − 1.9991)/2 / 11.8 ns = 6.10 M ✓. macOS: 2.1429 − 2.3277 = −0.185 s, 2.1429 − 2.5912 = −0.448 s ✓ (no W_max ≥ 0). ÷ 1.05: 1.99 / 2.32 M ✓; cuts 35 % / 24 % ✓. 14 × non-diffuse: macOS 32.59 / 36.28 s, Linux 28.88 / 29.04 s, Windows 28.05 / 27.99 s ✓. 14 × (worst + median solve) Linux 30.27 / 30.42, Windows 29.04 / 28.98 ✓. Seat 6: 3.05 M × 44.7 ns = 0.136 s ✓. SE ×1.208: 0.092 → 0.111, 0.360 → 0.435 ✓. Two refinements, not corrections: (i) for consistency with worst-of-10 restores, use the worst-of-10 solve (Linux 100.1 ms → 16.7 ns → 2.05 M rather than 2.09 M; macOS sign unchanged); (ii) the between-run spread of the cube restore's worst is 2.5 %, the 9 % belongs to the flutter scene.

## 6. Conditions of acceptance

- **W-a 2/2 → 1/1:** implement it as W-x (register + growth bound + summary printout) and bring 07c forward next; the register is plan text with remedy and closing phase per entry.
- **W-b 2/2 → 1/1:** the same W-x form (so a ≈ 0-margin Linux block is a listed entry, not a required red) **and** an enforcement rule: an OS is enforced only where 14 × (worst restore + worst solve) ≤ 29.1 s (a 3 % margin ≈ one observed between-run spread); on today's numbers only Windows qualifies at either W_max. With that, W-b buys nothing over W-a on my measures and costs a golden round; I would still prefer W-a's value.
- **W-e 2/2 → 1/1:** recast "Linux-enforced" as "enforced where the margin rule holds, listed elsewhere" (= W-x). I accept the FOR MAISARA reading of AX38 4c's OS scope in that form: the PRD is silent on where a block is measured (decider's note), and the plan already places blocks per OS (memory block; §0 row 06).
- **W-c 1/2 → 1/1:** the plan wording says 05h lands scopes 1–5, 7–9 and the records, 05i carries the gate after 07c; 07c pins its W_max only after the 100 m offline-bounce record exists.
- **Q-c 1/2 → 0/1:** replace by exact equality on W_pilot + W_final per gated scene in the D5 golden (already recorded there) plus Q-d as the generic guard.
- **N-b 2/1 → 1/1:** n\*_max ≤ 1 408 (22 blocks), keeping the worst observed macOS W1 share ≤ 19.2 ms (20 % headroom under 25 ms), re-measured in O18 before pinning.

## 7. Hand-offs

- **Researcher, RQ-H1-1 (narrowed, highest leverage):** in pluginval v1.0.4 `Source/Validator.cpp`, does `PluginsUnitTestRunner::resultsUpdated()` reset the inactivity deadline, and does `PluginStateTestRestoration::runTest` (`Source/tests/BasicTests.cpp`) call `ut.expect…` **inside** the per-parameter loop? If both, every restore resets the watchdog and the silent stretch is one restore (≈ 2.6 s), not 14 (≈ 36 s): the gate's multiplier would be 1, the margin problem dissolves, and the AQ10/AX38 4c "14 × t_restore" premise is 14× too strict. That premise came from my seat (file 3 / decider file 5 D4-L6); if confirmed I retract it in public, as my §7 incidents require. Also confirm `output_mode` counts as automatable. I rate above on the settled 14× until then.
- **Researcher, RQ-H1-2:** macOS arm64 hosted-runner cores/RAM/tenancy and documented timing variance; decides whether the macOS entry is "runner" or "plugin" and the Phase 13 wording. **RQ-H1-3:** host tolerance of a blocked `setStateInformation` (phase-07c §4).
- **Decider / interrogator:** W-x's growth bound on the median is distinct from X1 (median as margin input); say so in the record. If RQ-H1-1 overturns the 14×, that is a reading of her 2026-11-10 acceptance (AMENDS line), case for Maisara.
- **Seat 1:** P (floor), R's threshold, the SE cost of every W. **Seat 2:** the non-diffuse 100 m / 96 kHz build (2.0–2.6 s) is the cause; its reduction (Phase 07/10) is the only thing that passes the gate on macOS; whether W-b is a "cut to pass". **Seat 3:** the 20 % trigger. **Seat 4:** n\*_max. **Seat 6:** the 2.3–2.6 s user wait; 3 s per emitter met under every option. **Seat 7:** the cost of a register vs a red check in contractor time; the second golden round under W-b/W-c.
- **Orchestrator (code):** print per-OS min/median/worst and the 14× figure in the job summary; keep local numba background runs (D-H2 M-a) off any local timing measurement (CI timings are unaffected).

## 8. Premortem

If a by-design red gate ships (W-a as written), within two PRs the macOS build job is "the one that is always red"; a real macOS regression (an allocation, a pluginval crash) hides behind it, the fingerprint skip never fires, and the contracted engineer or a Mac beta user notices first.

---

# SEAT 5 POSITION — D-H2

## 1. Reading

Which case-bands the Release hidden-tag suite gates now, what reported-only prints may exist, and how missing references are produced without breaking CI time, determinism or the §8 atomic push. Cues: §2 criterion 4 (every gate automated; a release a day's work), §5 "determinism" (a reference is a committed artifact, never recomputed live), §4.4 (a test that only exercises the happy path: the gated subset must still exercise per-band α and mixed per-face s, review m-10).

## 2. Ranking

| sub-choice | prefer | can live with | cannot live with |
|---|---|---|---|
| G-a (forced) | consequence 1/1 | — | — |
| U | U-a (reported only, labelled, |C++ − ref| printed; z printed only with the "uncertified" label) | U-c | — |
| M | M-e | M-b, M-d, M-a; M-c only as an artifact-producing manual job | M-c as a live recompute (2/2, not veto) |
| B | B-a | B-b | — |

## 3. Tension now

- **G-a, 1.** CI time: the agreement test at test N (z_FW·SE ≤ τ − ℓ_ref → SE ≈ 0.05 dB, ≈ 2.7× the shipping N) is seconds per OS; the AX46 bias check at 3·SE ≤ 1 % − ℓ_ref (SE ≈ 0.005 dB) needs ≈ (0.083/0.005)² ≈ 275× the shipping N: ≈ 2 s per W1-class case at pool 4, ≈ 10 s per 100 m-class case [Inferred from file 1 §3 costs]; over ≈ 60 certified cases that is minutes on Linux, ×1.5 on macOS (pool 3). Inside the Release step. AX43's reversal clause names "Seat 5's budget" without a number: I set it at ≤ 10 min added wall time per OS in the `build` job; above that, the BRAS pairs' bias check moves to the nightly, as AX43 says. Condition: the gated set with ℓ_ref per case-band lives in the agreement golden (data, not code), extended only through `update_goldens.py --extend` (which never drops a key, from CLAUDE.md), so the implementer cannot narrow it; m-10 checked on the subset (BRAS pairs give per-band α at 500 Hz–2 kHz; mixed per-face s needs confirming in the 225).
- **U-a, 0.** No assertion, seconds of print; written to the job summary and the phase record. **U-c, 0** but loses the only check on the Phase 04 rooms' per-band α mapping until their references exist.
- **M-e, 1.** Four cores for a day in the background; each produced reference committed by script with provenance (tool commit, hash-pinned numba/numpy, rung, ℓ_ref), 05i gates what is certified then, the rest listed. **M-a 1, M-b 1, M-d 1** (cost: Seat 7). **M-c, 2 as a live job:** a reference recomputed in CI makes the gate depend on runner, numba and numpy versions (reproducibility, criterion 2); hours per case against the nightly's `timeout-minutes: 120` (from the code) and runner RAM (15 GB chunked at the 1.25 m BRAS rung; macOS runners are the smallest [Hyp], RQ-H2-1). **1** as a Linux-only `workflow_dispatch` job with hash-pinned deps that uploads the reference as an artifact for a person to commit with the CHANGELOG reason, `timeout-minutes` ≤ 360 [Hyp on the job limit, RQ-H2-1].
- **B-a, 1.** The record says "not evaluated (reference pending)" per class, never "passes" (the AX36 (b) precedent); the 100 m class's reference named; wall time printed. **B-b, 0** now, but AX46 is a §5 criterion, so deferral alone forces the split.

## 4. Tension later

| option | commits | undo | evidence | rating |
|---|---|---|---|---|
| G-a | a gated set that must grow monotonically; phase-05i; the family rule conservative on 225 | golden `--extend` | 05i | 1 |
| U-a | a print that could be quoted as validation (Seat 7/1's ground) | label text | public wording draft | 1 |
| U-c | a blind spot on per-band α until 05i | — | m-10 | 1 |
| M-e | 05i's scope and a priority order (Seats 1, 8, 9) | — | background-run log | 1 |
| M-c live | gate reproducibility tied to runner/toolchain; OOM/timeout reds under the no-re-run culture | rewrite as artifact job | first OOM | 2 |
| M-d | a person's machine and time (Seat 7) | — | — | 1 |
| B-a | a bias record per class; the 100 m class rests on the tracer or "none" (Seat 2) | — | 05i | 1 |
| B-b | AX46 unmet at 05h `done` → split | — | — | 1 |

## 5. Evidence

Nightly timeout, Release step contents: from the code (`nightly.yml` L31; `ci.yml` L338–347, no agreement step yet). `--extend` never drops: CLAUDE.md. Costs per case: file 1 §3, scaled [Inferred]. Runner RAM / job limits: [Hyp] → RQ-H2-1. No corpus claim is load-bearing here.

## 6. Conditions of acceptance

- **M-c 2/2 → 1/1:** manual, Linux-only, artifact-producing, hash-pinned, time-boxed; references committed by hand with provenance; never compared live.
- **G-a (to hold 1/1):** gated set + ℓ_ref in the golden; `--extend` only; per-OS suite wall time printed; the `build` job gets a `timeout-minutes`; m-10 confirmed on the subset or the gap reported.

## 7. Hand-offs

Priority order: Seats 1, 8, 9. Rung semantics of the 2.25 m patches and the 100 m class's reference: Seat 2. Larger machine and its cost: Seat 7 (a thing only a person can provide). Researcher: RQ-H2-1 (runner RAM, disk, per-job and per-workflow limits, larger-runner cost). Orchestrator: the per-case-band listing (K20) and per-case `hybrid_fast` cost (K23); add the `[agreement]` hidden tag to the Release step on three OSes (a step, not a job, so `test_ci_workflow.py` is unaffected).

## 8. Premortem

If M-c runs live, the first nightly OOMs at the 15 GB rung or times out at 120 min, the gated set stays at 225 through release while the report reads "agreement suite green", and Seat 9 notices when the public wording about "the same material on every surface" is drafted from a 27/72 gate.
