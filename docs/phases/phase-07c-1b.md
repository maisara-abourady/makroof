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

1. **Condition 7, the 07c re-pin** (phase-07c-1 condition 7, "The 07c re-pin", as written there): after conditions
   9 and 12 land, re-derive the restore gate's growth-bound baselines (`kGateRegister`), the ±5 % flutter window,
   `kSolveWarn` and its `solveRefMs` baselines from ≥ 3 in-window CI runs on the post-condition-9/12 restore (the
   first PROVISIONAL, printed not asserted; never a red or out-of-window run as a baseline); re-derive the macOS
   trigger (2 172 ms); a CHANGELOG reason, a §6 row, and the AX38 4c text through `/fix-plan`.
2. **AX38 4c register entries** (macOS 33.40 s, Windows 36.73 s, low-α): on the runs of scope 1, close each under
   4c (c), or name phase-07d per condition 9's split clause. First data: run 43242209571, with the low-α restore as
   AX48/AX49 build it: 14 × worst 16.33 / 23.68 / 31.97 s (Linux / macOS / Windows); flutter cube 6.57 / 8.39 / 12.56 s.
3. **Condition 12 (c) finding:** callback p99.9 at host buffer 64 with 8 concurrent builders 1 178 / 4 245 /
   1 137 µs (Linux / macOS / Windows) against 05i's 195 / 1 674 / 404 µs (run of record 43031773338; period
   1 333 µs). The rise goes to the board loop; never an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).
4. **AX48 E_model fingerprint:** pin the per-platform hashes (Linux `22f009efe0004e82` from run 43242209571; macOS
   and Windows from CI) so the fingerprint test fails on any change.
5. **FM-D1-S3:** apply Maisara's answer (Raise item 1) through `/fix-plan`.
6. **Instance insertion (review M1).** A fresh instance's first prepare (no restore, no held or saved level) runs the
   stage-1 diffuse solve synchronously, as before 07c-1; AQ10 and AX48 name "a load" and do not name instance
   insertion. The board loop reads whether instance insertion is a load (the embedded default scene's first build)
   under AX48 FM-3′, or the code changes; until then the pipeline counts these solves separately
   (`Stats::insertSolves`, commit after f07958c); record (h) times restores only (instance prepares are outside its
   window), so its figures are not skewed; `insertSolves` is not yet printed — this phase prints it beside record (h).
7. **AX47 "Measurement" mid-fade check (review M2).** AX47 says "Wet pink-noise and speech renders check that no
   mid-fade value exceeds the louder endpoint." 07c-1 records the realised settling step on the decays played (review
   fix M2) and tests the crossfade laws (M3), but has no wet pink-noise / speech render check; this phase adds it for
   each AX47 step (equal-gain, AX18 FM-1: the settling step of a project load and an edit's interim → final) and each
   fade from silence; the load's equal-power fade over another scene's IrSet (AX18) is recorded, not asserted against
   the louder endpoint (the cross term of two correlated wet renders can exceed it, Vorländer §4.3 Eq. 4.15). The loop
   states the analysis window relative to the 30 ms AQ4 ramp (the bound holds per window only while the fade gain is
   nearly constant across it).
8. **AX49 reversal trigger fired** (record (h), run 43242209571,
   `docs/review/phase-07c-1/41-orchestrator-ci-records-43242209571.md`): an 8-instance Windows load at the rated corner (96 kHz, T60 8 s, 100 m cube, loaded in sequence) took keyless
   9 511 ms, keyed 9 448 ms (macOS 7 846 / 8 780 ms, Linux 4 995 / 5 083 ms) against AX49's 5 s. Back to the board
   with phase 07d's candidates first, per AX49 "Reversal"; the decision is taken in this phase's loop (or the loop
   moves it to 07d) — never an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5).

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

- [ ] Condition 7, the 07c re-pin: the restore gate's growth-bound baselines, the ±5 % flutter window, `kSolveWarn`
      and its `solveRefMs` baselines re-derived from ≥ 3 in-window runs (one run PROVISIONAL, printed not asserted;
      never a red or out-of-window run as a baseline), and the macOS trigger (2 172 ms) re-derived, with a
      CHANGELOG reason and a §6 row. (AX38 4c; D-Q5; phase-07c-1's condition 7 criterion)
- [ ] The AX38 4c macOS and Windows entries leave the register through `/fix-plan` under (c), or stay listed with
      'closes at' phase-07d, on the runs of scope 1, at both gated builds on three OSes. (phase-07c-1 A2, the clause
      "in AX38 4c's register form (the entries it closes removed through `/fix-plan`; entries that stay open name
      phase-07d as 'closes at')")
- [ ] Condition 12 (c): the finding is recorded with a board decision (ledger rows linked); no instance cap.
- [ ] The E_model fingerprint test asserts the pinned hash on Linux, macOS and Windows and fails on a changed E_b
      (negative check).
- [ ] FM-D1-S3: Maisara's answer recorded in BUILD_PLAN §6; if she chooses (i), the corrected lines are in
      phase-07c-2, phase-08-3 and phase-09 through `/fix-plan`.
- [ ] Instance insertion (scope 6): the reading of whether instance insertion is a load under AX48 FM-3′ recorded
      (the AX48 text through `/fix-plan` if it changes), and a test asserting the decided behaviour. (review M1)
- [ ] AX47 mid-fade check (scope 7): a test renders wet pink noise and speech through a project load and its settling
      step (and an edit's interim and final) and asserts, per analysis window (its length set in this phase's loop before the run, interrogator-checked; the loop states the analysis window relative to the 30 ms AQ4 ramp (the bound holds per window only while the fade gain is nearly constant across it)) across each AX47 step (equal-gain, AX18 FM-1: the settling step of a project load and an edit's interim → final) and each fade from silence, that the output energy
      does not exceed the louder endpoint's (the two IRs rendered alone), on three OSes; the load's equal-power fade over another scene's IrSet (AX18) is recorded, not asserted against the louder endpoint (the cross term of two correlated wet renders can exceed it, Vorländer §4.3 Eq. 4.15). (AX47 "Measurement"; review M2; DC-08, DC-09)
- [ ] AX49 reversal (scope 8): the board's decision on the AX49 reversal recorded (AX row / ledger), applied via
      `/fix-plan`; no instance cap. (AX49 "Reversal"; record (h), run 43242209571)

## Listening / manual checklist

- [ ] None new; phase-07c-1's checklist applies.

## Contractor review focus

- The re-pin's run selection (in-window, none red) and the register closures; the fingerprint pins per platform.

## Risks

A re-pinned gate that still fails at the long-T60 corner sends the entry to phase-07d (condition 9's split clause).

## Definition of done

- Section "Acceptance criteria — automated" all checked with CI evidence; §0 rows 07c-1b (and 07c-1) updated.
- PR with the "Raise with Maisara" item and its answer, the contractor focus and AX/ledger links.
- CLAUDE.md rules apply: one phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-1c.md`.

## Notes

- Split from 07c-1 on 2026-11-12 (session 2 of 2).
