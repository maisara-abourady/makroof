# Phase 07c-1b — Diffuse solve off the synchronous paths: remainder of 07c-1

Size: **S** · Depends on: 07c-1 `done` · Part of: [phase-07c](phase-07c.md) · Lead subject matter: Seat 5 (Deadline
keeper), "anything on or beside the audio thread: real-time safety; lock-free hand-off; threading topology; host
conformance (pluginval, auval, state, …); offline equals real-time" · Read first, in this order: `CLAUDE.md`; this
file in full; `docs/phases/phase-07c-1.md` conditions 7, 9 and 12; `docs/BUILD_PLAN.md` §2 **AX38 (4c and (iv)), AX47,
AX48, AX49**.

Created on 2026-11-12 under CLAUDE.md's split rule ("If a phase can't be finished in two sessions, split the
remainder into `phase-XXb.md`"): phase 07c-1's second session landed conditions 9, 10 and 12 and the AX47–AX49
decisions; the items below did not fit. Nothing here reopens a decision: every rule is phase-07c-1's (AX38 4c,
AX47–AX49 as decided by its loop), applied to the work that remains.

---

## Raise with Maisara (first message and PR)

1. **FM-D1-S3, NEEDS MAISARA** (`docs/review/phase-07c-1/39-decider-G3-FM-D1-S3.md`,
   `40-interrogator-G3-FM-D1-S3-check.md`): whether to write the AX47 (b)-style interim stream checks into
   [phase-07c-2](phase-07c-2.md) (conditional), [phase-08-3](phase-08-3.md) and [phase-09](phase-09.md) now
   (the decider's recommendation (i), with interrogator file 40's corrections 80, 86, 88, 90, 91, 92 and 93 applied
   first), or leave Seat 3's debt row unrepaid. D1 (O8) stands either way (interrogator file 40 row 82). The 08-3 / 09
   lines fall in Seat 4's row (binaural / loudspeaker decoding), and Seat 4 was not convened for D1 (interrogator file
   40, observation 98); if Maisara picks (i), Seat 4 is convened before the lines are applied.
2. (phase-07c §2.1, carried verbatim from phase-07c-1) **Only if** this phase would land after the first public release
   without the estimator parameters versioned in saved state: Seat 7's condition fails and the item returns to Maisara
   (decider file 47 §4, strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none. It does not apply
   now: no public release has happened.

## Goal

Finish phase 07c-1: re-pin the restore gate on the restore as AX48/AX49 build it, settle the AX38 4c register
entries on those runs, take condition 12 (c)'s finding to the board, pin the AX48 E_model fingerprints, and apply
Maisara's answer on FM-D1-S3.

## Assumptions in force

All of phase-07c-1's (AQ4, AQ10 as amended, AX5, AX18, AX33, AX38, AX41, AX44, AX47, AX48, AX49). Never a W_max cut,
a range change, a formulation seam (D-H1 (v)(d)) or an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).

## Scope

1. **Condition 7, the 07c re-pin** (phase-07c-1 condition 7, "The 07c re-pin", in AX38 4c's form as amended on
   2026-11-13 by FM-GROWTH, `docs/review/phase-07c-1b/11-decider-decision-r3.md` item 9): after conditions 9 and 12
   land, pin from ≥ 3 green S2 CI runs per OS on the post-condition-9/12 restore (out-of-window runs count; never a
   red run; the first run PROVISIONAL, printed not asserted): the flutter reference, the low-α / flutter ratio
   reference r̄ and the baseline median (`kGateRegister`), each the mean of those runs; `solveRefMs`, the mean solve
   median of those runs per OS and scene, and k per OS, the largest max / mean of those runs (PROVISIONAL
   until its dated exit; print-only on hosted runners throughout (G9); never a (d) trigger); the low-α / flutter
   ratio asserted at 1.10 × r̄ on Linux and Windows every run (an OS whose S2 ratios have max/min > 1.10 print-only, as macOS); no ±5 % gating window (in-window printed against ±5 %, AX38 4c)
   (the flutter window and the absolute leg return at the phase-07d re-pin). Re-derive the macOS trigger (2 172 ms)
   as ⌊1.15 × the mean of the green macOS low-α medians of these runs⌋, computed by script from the GATE lines
   (FM-TRIG). Print the per-stage split (ISM / solve / synthesis + assembly) on every OS on these runs and the
   value of f (AX38 4c, "Asserted every run"; if f > ×1.4 or s_L ≤ 1.10·s_F the PR states Seat 3's later 2). A
   CHANGELOG reason, a §6 row, and the AX38 4c values (the `[07c-1b re-pin: …]` placeholders) through `/fix-plan`.
2. **AX38 4c register entries** (macOS 33.40 s, Windows 36.73 s, low-α): on the runs of scope 1, close each under
   4c (c), or name phase-07d per condition 9's split clause; an entry closes only if 14 × worst ≤ 30 s on every
   S2 run (E1, AX38 4c). First data: run 43242209571, with the low-α restore as
   AX48/AX49 build it: 14 × worst 16.33 / 23.68 / 31.97 s (Linux / macOS / Windows); flutter cube 6.57 / 8.39 / 12.56 s.
3. **Condition 12 (c) finding:** callback p99.9 at host buffer 64 with 8 concurrent builders 1 178 / 4 245 /
   1 137 µs (Linux / macOS / Windows) against 05i's 195 / 1 674 / 404 µs (run of record 43031773338; period
   1 333 µs). The rise goes to the board loop; never an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).
   **Decided (D-B1 B1-b, `docs/review/phase-07c-1b/4-decider-decision-r1.md` items 1–5, item 6 as corrected in
   `8-decider-decision-r2.md`; AX38 (i) cond. 12 (c) note):** this phase re-instruments the condition 12 (c) callback
   record in `tests/unit/test_diffuse_records.cpp` (test-only; a record, never a gate; no `src/` change, no priority
   change, no instance cap). (1) Callback thread at platform audio priority: macOS `THREAD_TIME_CONSTRAINT_POLICY`
   (period = constraint = 1 333 µs in mach units), Windows MMCSS `AvSetMmThreadCharacteristicsW(L"Pro Audio")`, Linux
   SCHED_FIFO, else `priority: not available (errno)`; the priority actually obtained printed. (2) Pacing by absolute
   deadlines (`sleep_until` the next period, spin the last ≈ 100 µs; Windows a high-resolution wait); the timer
   resolution in force printed. (3) Per callback: wall and thread-CPU time of `process()` (Windows
   `QueryThreadCycleTime` with a measured cycle rate; macOS, Linux `CLOCK_THREAD_CPUTIME_ID` / `thread_info`); the
   per-callback max of `lastProcessMultiplyAdds()`. (4) Builders 0 / 1 / 2 / 4 / 8, the 0-builder floor first.
   (5) Printed per point: callback count vs expected; median, p99, p99.9 and max of wall and CPU time; overruns >
   period and > period/2; `hardware_concurrency()`; the old instrument's figures beside, labelled "old instrument
   (R16)"; `INSTRUMENT INVALID` when the count is below 0.95 × expected. (6) Residual owner as in the AX38 (i) note:
   an overrun > period at 8 builders with none at 0 is re-measured in phase-13-3 scope 4 (real macOS hardware) and on
   the R5 Windows release machine; a miss opens 13-1b (D-PS4 instruction 2) with B1-d first candidate.
4. **AX48 E_model fingerprint:** pin the per-platform hashes (Linux `22f009efe0004e82` from run 43242209571; macOS
   and Windows from CI) so the fingerprint test fails on any change.
5. **FM-D1-S3:** apply Maisara's answer (Raise item 1) through `/fix-plan`. **Answered by Maisara 2026-11-13: option (i)** ("Write the stream checks now"); the lines are in phase-07c-2
   (scope 9, acceptance), phase-08-3 and phase-09 (acceptance), AX47 (b) and BUILD_PLAN §6 (`docs/review/phase-07c-1b/`
   files 15–20).
6. **Instance insertion (review M1).** A fresh instance's first prepare (no restore, no held or saved level) runs the
   stage-1 diffuse solve synchronously, as before 07c-1; AQ10 and AX48 name "a load" and do not name instance
   insertion. The board loop reads whether instance insertion is a load (the embedded default scene's first build)
   under AX48 FM-3′, or the code changes; until then the pipeline counts these solves separately
   (`Stats::insertSolves`, commit after f07958c); record (h) times restores only (instance prepares are outside its
   window), so its figures are not skewed; `insertSolves` is not yet printed — this phase prints it beside record (h).
   **Decided (FM-B2, AX48 "Instance insertion", 2026-11-13):** insertion is a keyless load. Tests: "a fresh
   `ScenePipeline`, no setState, prepare at 48 kHz on `medium_room`: `insertSolves == 1`, solve done before prepare
   returns; diffuse E_b bit-identical to a stage-1 solve; first IrSet at the first boundary, `fadeCount() == 0`; also
   prepare-then-setState (both VST3 orders, R17)"; "record (h) prints prepare-first totals (interleaved; batched)
   without a settle wait, beside the setState-first total".
7. **AX47 "Measurement" mid-fade check (review M2).** AX47 said "Wet pink-noise and speech renders check that no
   mid-fade value exceeds the louder endpoint." (replaced on 2026-11-13 by the D-B3 check, AX47 "Measurement": seeded
   speech-like and pink-noise renders, 1 ms windows). 07c-1 records the realised settling step on the decays played
   (review fix M2) and tests the crossfade laws (M3), but has no wet pink-noise / seeded speech-like render check;
   this phase adds it for
   each AX47 step (equal-gain, AX18 FM-1: the settling step of a project load and an edit's interim → final) and each
   fade from silence; the load's equal-power fade over another scene's IrSet (AX18) is recorded, not asserted against
   the louder endpoint (the cross term of two correlated wet renders can exceed it, Vorländer §4.3 Eq. 4.15). **Decided
   (D-B3, AX47 "Measurement"; decider files 4, 8, 11 item 6, interrogator file 12):** signals pink noise and seeded
   speech-like (generated; seed and parameters fixed and versioned; pauses starting and ending inside a fade); per 1 ms
   window aligned to the fade start (N_w = lround(0.001·fs)), per output channel, E_out ≤ (1 + N_w/L)²·max(E_a, E_b)·
   (1 + 10⁻⁵); per sample |o| ≤ max(|a|,|b|) + 8u·(|a|+|b|); a reconstruction to 8u·(|a|+|b|); value equality with
   the endpoint outside the fade; fades from silence |o| ≤ |b|.
8. **AX49 reversal trigger fired** (record (h), run 43242209571,
   `docs/review/phase-07c-1/41-orchestrator-ci-records-43242209571.md`): an 8-instance Windows load at the rated corner (96 kHz, T60 8 s, 100 m cube, loaded in sequence) took keyless
   9 511 ms, keyed 9 448 ms (macOS 7 846 / 8 780 ms, Linux 4 995 / 5 083 ms) against AX49's 5 s. Back to the board
   with phase 07d's candidates first, per AX49 "Reversal"; the decision was moved to phase-07d by D-B4 (C7′) — never
   an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5). **Records this phase (D-B4, test-only; decider file 8):** record (h)
   prints per instance its restore time; the background builds running at its start (stage hook and `builderBusy()`,
   split Solve / Assemble, counted as instances); `hardware_concurrency()`; and the prepare-first totals (scope 6).

## Out of scope

- Everything phase-07c-1 delivered (conditions 2, 4–6, 9–12; D-C1–D-C3; AX47–AX49 as written).
- The long-T60 corner's candidates: [phase-07d](phase-07d.md). Conditions 1, 3 and 8, the AX47 / L4 ABX runs and the
  class (c) and load-fallback decisions: [phase-07c-2](phase-07c-2.md).

Follow-ups noted (review minors from 07c-1, not scope here):

- `renderLog()` is not surfaced by the PluginProcessor (A5 holds at pipeline level).
- `settling()` does not include a running crossfade (AX38 (iii) wording).
- HostTrace: `transport()` is read outside `processBlock`, and the ring's push is a CAS retry loop (diagnostic build
  only, `SPATIAL_HOST_TRACE`).
- Condition 10 (interrogator note on the head-code diff check, ledger P07C1-H-DC): the offline drop
  (`setNonRealtime(true)`, an offline `reset()`) releases the dropped IRs on the calling thread, which a host may make
  the processing thread (VST3 permits it; Apple's AU `reset()` contract: 'does not allocate or free'). Moving the
  release to the builder thread is open; the realtime `reset()` (`resetKeepIr`) frees nothing.

## Acceptance criteria — automated

- [ ] Condition 7, the 07c re-pin: the flutter reference, the low-α / flutter ratio reference and the baseline
      median (`kGateRegister`), `solveRefMs` and k per OS pinned from ≥ 3 green S2 runs per OS (out-of-window runs
      count; never a red run; one run PROVISIONAL, printed not asserted; the solve bound PROVISIONAL until its dated
      exit; print-only on hosted runners throughout (G9)); the ratio asserted at 1.10 × its pin on Linux and Windows (an OS whose S2 ratios have max/min > 1.10 print-only); the
      macOS trigger (2 172 ms) re-derived by script as ⌊1.15 × the mean of the green macOS low-α medians of those runs⌋; the per-stage split
      and f printed; with a CHANGELOG reason and a §6 row. (AX38 4c as amended by FM-GROWTH and read by FM-TRIG,
      2026-11-13; D-Q5; phase-07c-1's condition 7 criterion)
- [ ] The AX38 4c macOS and Windows entries leave the register through `/fix-plan` under (c), or stay listed with
      'closes at' phase-07d, on the runs of scope 1, at both gated builds on three OSes. (phase-07c-1 A2, the clause
      "in AX38 4c's register form (the entries it closes removed through `/fix-plan`; entries that stay open name
      phase-07d as 'closes at')")
- [ ] Condition 12 (c): the finding is recorded with a board decision (ledger rows linked); no instance cap. The
      re-instrumented callback record (scope 3, D-B1 B1-b) is printed on Linux, macOS and Windows in one CI run (run
      id cited), with the priority obtained and any `INSTRUMENT INVALID` per OS; a record, never a gate; residual
      owner phase-13-3 scope 4 / the R5 machine, 13-1b with B1-d. (D-B1, decider files 4 and 8)
- [ ] The E_model fingerprint test asserts the pinned hash on Linux, macOS and Windows and fails on a changed E_b
      (negative check).
- [ ] FM-D1-S3: Maisara's answer recorded in BUILD_PLAN §6; if she chooses (i), the corrected lines are in
      phase-07c-2, phase-08-3 and phase-09 through `/fix-plan`. (Maisara answered (i) on 2026-11-13; §6 row and lines
      in, `docs/review/phase-07c-1b/` files 15–20.)
- [ ] Instance insertion (scope 6): the reading of whether instance insertion is a load under AX48 FM-3′ recorded
      (the AX48 text through `/fix-plan` if it changes), and a test asserting the decided behaviour. (review M1)
- [ ] AX47 mid-fade check (scope 7): a test renders wet pink noise and a seeded speech-like signal through a project load and its settling
      step (and an edit's interim and final) and asserts, across each AX47 step (equal-gain, AX18 FM-1: the settling step of a project load and an edit's interim → final), per 1 ms window aligned to the fade start (N_w = lround(0.001·fs)) and per output channel, E_out ≤ (1 + N_w/L)²·max(E_a, E_b)·(1 + 10⁻⁵) (E_a, E_b: the two IRs rendered alone),
      the per-sample bound |o| ≤ max(|a|,|b|) + 8u·(|a|+|b|), the reconstruction to 8u·(|a|+|b|) and value equality with the endpoint outside the fade, and for each fade from silence |o| ≤ |b|, on three OSes; the load's equal-power fade over another scene's IrSet (AX18) is recorded, not asserted against the louder endpoint (the cross term of two correlated wet renders can exceed it, Vorländer §4.3 Eq. 4.15). (AX47 "Measurement", D-B3, decider files 4, 8, 11; review M2; P07C1-S5-DC-08, -09)
- [ ] AX49 reversal (scope 8): the board's decision on the AX49 reversal recorded (AX row / ledger), applied via
      `/fix-plan`: moved to phase-07d by D-B4 (C7′), with the trigger as a 07d acceptance criterion and the records of
      record (h) printed in this phase; no instance cap. (AX49 "Reversal"; record (h), run 43242209571)

## Listening / manual checklist

- [ ] None new; phase-07c-1's checklist applies.

## Contractor review focus

- The re-pin's run selection (≥ 3 green S2 runs per OS, out-of-window runs counted, none red), the ratio reference
  and baselines taken as their mean, the solve bound k × solveRefMs PROVISIONAL and print-only with its dated exit,
  and the register closures (E1); the fingerprint pins per platform.

## Risks

A re-pinned gate that still fails at the long-T60 corner sends the entry to phase-07d (condition 9's split clause).

## Definition of done

- Section "Acceptance criteria — automated" all checked with CI evidence; §0 rows 07c-1b (and 07c-1) updated.
- PR with the "Raise with Maisara" item and its answer, the contractor focus and AX/ledger links.
- CLAUDE.md rules apply: one phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-1c.md`.

## Notes

- Split from 07c-1 on 2026-11-12 (session 2 of 2).
