# 49 — Seat 5 (deadline keeper): the AX37 (5.4) validation-N check's cost on the python CI job (file 47)

phase-05h (session 2). Convened per decision P05H-QA's own clause (file 44). Verbatim seat output (the orchestrator saved it). The per-job durations of CI run 42935789745 the seat asked for are appended to file 47.

SEAT 5 POSITION

1. **Reading.** The AX37 (5.4) 2^23 check costs 12.9 min on the Linux python job (22.1 min total; 16.6 macOS/Windows), over the clause's 10 min return trigger; the question is which CI shape keeps the check at τ on three OSes inside the budget I hold. Cues: §4.4 "a test that only exercises … at one size" (inverse: a gate whose cost grows with no owner), CS-5 step 1 (CI on every push is how one person affords strictness; feedback time is the measure), criterion 4.

2. **Ranking.**
- **(f) own job, added by me: `open-field-validation`, three-OS matrix, parallel to `python`** — *prefer*. The two 2^23 cases get a registered marker (`tools/acoustics/tests/conftest.py`, next to `ensemble`/`slow`), the python job deselects it, a new job (pattern of `tail-gates`, ci.yml L213–264: `needs: changes`, the `if:` gate, `timeout-minutes`, entry in `ci-ok` `needs` L491, `test_ci_workflow.py` updated) runs `test_tail.py -m <marker>`. Both s values, both emitters, three OSes, τ alone: AX37 (5.4)'s text unchanged, no AMENDS.
- **(b) s 0.4 only at 2^23** — *can live with*.
- **(c) (b) + s 0.5 nightly** — *can live with*, below (b): nightly is Linux-only, 120 min, triggered only by PRs touching `src/sim/`/validation (nightly.yml L11–18), so s 0.5 at 2^23 leaves "three OSes" anyway; the `nightly.yml` edit buys nothing (f) does not.
- **(a) keep as is** — *can live with*, lowest.
- **(d) two concurrent render_cli** — *can live with only after measurement*; I predict ≈ 0 gain: from the code the solve already runs on a process-wide `hardware_concurrency()` pool (`src/sim/diffuse/ThreadPool.cpp` L30; `DiffuseSolveGate.cpp` L34), so two processes on 4 vCPU (3 macOS) contend for the same cores.
- **(e)** not available, agreed.

3. **Tension now.**
- (f): 1. About an hour of ci.yml/conftest/test edit; three extra runner set-ups (checkout, pip, render_cli build ≈ 3–5 min each `[Hyp]`); `ci ok` wall clock = max(python ≈ 10.5, new job ≈ 17 Linux, tail-gates ?).
- (b): 1. Python job ≈ 17 min Linux; the clause's "both s values" falls (AMENDS); the Linux python job is also the listening-pack job, so the pack waits.
- (c): 1, plus a second workflow to keep in step.
- (a): 2. +12.9 min on every PR run and every manual re-run, with **no `timeout-minutes` on the python job** (confirmed: ci.yml L113–209 has none; GitHub's default is 360 min), so a hung render_cli costs six hours of a runner before anyone sees it. The feedback loop for one person is my measure and this doubles it.
- (d): 1 (a measurement day), likely wasted.

4. **Tension later.**
- (f): 0–1. The job is the natural home for every further validation-N render (05i's references, AX46 class runs); the python job stays at its 10 min; undo = delete a job.
- (b): 1. Loses the second, independent-s run of the same ratio; if the s-independence derivation is ever questioned, the check must be re-added at 2^23 (one CI run, cheap). AMENDS carried.
- (c): 1. s 0.5 runs Linux-only and only when `src/sim/` changes; a regression in `tools/acoustics/ground_scatter.py` alone never triggers it (paths filter L13–18).
- (a): 2. Nothing in the plan prunes the python job; 05i, 08 and 12 add renders to `pytest tools`; the critical path grows a phase at a time, and the first response under schedule pressure is to skip the manual run between pushes (CLAUDE.md: pushes start nothing). Undo later = this same job split, under pressure.
- (d): 1 if it works; 2 if it is kept while mis-measured (two solves at ≤ 1 GB transient each are fine on 7 GB runners, but the pool contention makes the duration non-reproducible, and I lose the per-case `--durations` signal).

5. **Evidence.** Measurements: file 47 table `[Observed]`. Python job has no timeout; `tail-gates` 90 min, nightly 120 min, Linux-only, path-filtered: from the code (`ci.yml` L113–264, L491; `nightly.yml` L11–31). Pool on `hardware_concurrency()`: from the code (`ThreadPool.cpp` L30, `DiffuseSolveGate.cpp` L34). Markers registered per sub-package: `tools/acoustics/tests/conftest.py` L19–26, `tools/validation/tests/conftest.py` L16–17. The "≤ 10 min added wall time per OS" is AX43's CI sentence (BUILD_PLAN L144), borrowed into AX37 (5.4) (file 44 Q1); wall time of `ci ok`, not runner minutes, is the quantity I budget (criterion 4; CS-5). `[Hyp]`: the actual duration of `tail-gates` in run 42935789745; if it exceeds 22 min, (a) adds nothing to `ci ok` and its "now" rating falls to 1. **Researcher/orchestrator to verify:** read run 42935789745's per-job durations; GitHub default job timeout 360 min; whether runner minutes are billed for this repo (Seat 7 if yes). s-independence of the ratio (Kuttruff Eq. 4.24, single bounce): not my ground, see hand-offs.

6. **Conditions of acceptance.**
- (a) → 1 if (i) `timeout-minutes` (≈ 45) is added to the python job, (ii) `--durations=10` prints the two cases, and (iii) `tail-gates` is shown to be the longer job already. Without (i) I keep 2.
- (d) → accept only if a measured run on the Linux runner shows ≥ 40 % reduction of the pair's wall time with the per-case durations still printed; otherwise drop it.
- (b)/(c) → no condition needed from me; the AMENDS and the acoustic grounds are others'.

7. **Hand-offs.** Whether the ratio's s-independence (Lambert re-radiation, every other face absorbing, no second bounce) justifies dropping the s 0.5 run: Seat 2 (and Seat 9), checked by the interrogator against Kuttruff Eq. 4.24. Runner-minute cost in euros if billed: Seat 7. Whether (f)'s ci.yml edit fits the one-phase rule or is a 05i item: decider (it is the same class of edit as (c), smaller than a nightly redesign).

8. **Premortem.** If (a) is kept and fails, it fails as a 30-plus-minute `ci ok` by phase 05i, a runner hang that burns hours unseen for lack of a timeout, and an orchestrator who stops starting manual runs between pushes; the orchestrator notices first as latency, Maisara as a regression caught one PR late.
