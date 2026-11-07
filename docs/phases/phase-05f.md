# Phase 05f — CR4 geometry and three-room re-run

Size: **M** · Depends on: 05e · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ9, AX24, AX25, AX26, AX27) and §3 (F2), **`docs/phases/phase-05.md` (all of it: its rules apply here unchanged)**, `docs/phases/phase-05e.md`, `docs/validation/bras_mapping.md` §1–§3, the `tools/validation/skp_reader.py` docstring

Created on 2026-11-06 at Maisara's request ("Go for setting 5f dedicated for whatever CR4 needs"),
after the decider's CR4-handling decision of the same day (vetoable by Maisara). This phase does
everything that needs CR4; Phase 05e completes on CR2 + CR3 with the provisional two-room label.
**Every rule, threshold, method and condition stays in `docs/phases/phase-05.md`**, and the rules of
`docs/phases/phase-05e.md` apply unchanged; this file only says what is left and where to start.
Where this file and phase-05.md seem to differ, phase-05.md wins and the difference goes to
`/fix-plan`.

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**.

1. **Extraction path if the reader cannot be fixed.** If `skp_reader.py` cannot be made to extract
   CR4, Maisara decides on another extraction path (third-party code was ruled out, 2026-11-06).
2. **Deferred B12 and B11 decisions.** The B12 replacement and the B11 promotion decisions, deferred
   in 05e, become due when this phase's three-room report exists.

## Goal

Extract CR4 and complete Phase 05's evidence (phase-05.md "Goal") on three rooms.

## Assumptions in force

As phase-05.md and phase-05e.md "Assumptions in force", unchanged.

## Start here

What 05e session 1 found and committed (commit "phase-05e: three generic skp_reader fixes found while
profiling CR4"):

- Three generic `skp_reader.py` fixes: a copy-on-write object table in re-synchronisation trials
  (59 % of the profiled CR4 run, 209 of 353 s); a class-index offset correction after a re-synchronisation; incomplete face
  records dropped and logged. Also progress lines.
- The regression guard held: `tools/validation/tests/test_skp_reader.py`, CR2/CR3 extraction
  byte-identical, `make_bras_scenes.py --check`.
- CR4 now parses in ≈ 1 min but reproduces only ≈ 1 083 of 5 851 m². CR4's room uses textured faces:
  of its 1 767 `CFaceTextureCoords` records, 1 547 fit the reader's 214-byte layout (a null reference follows the 214-byte body) and the other 220 do not.
  The parse desynchronises there and stops for good at 16.46 of 17.08 MB.

CR4 stays selected; it enters only if the `bras_mapping.md` §2 acceptance test passes (every
documented material area reproduces and every loop vertex lies on its face's plane); it is never
tuned against and never dropped (`bras_mapping.md` §1).

Commands: as phase-05e.md "Start here", e.g.

```bash
python tools/validation/extract_bras_geometry.py --rooms CR4      # foreground, progress output
python tools/validation/make_bras_scenes.py --check
pytest tools/validation/tests/test_skp_reader.py
```

## Scope

All of it as specified in phase-05.md, unchanged; this list says what is left.

a. **Reader:** decode the `CFaceTextureCoords` layout variant(s), and any further record the CR4
   parse then meets, in `tools/validation/skp_reader.py`. Generic at file-format level, no per-room
   logic, under the regression guard above (`test_skp_reader.py`, CR2/CR3 extraction byte-identical,
   `make_bras_scenes.py --check`).
b. **Extract CR4** (in the foreground with progress output while the session is active) and accept
   it only by the `bras_mapping.md` §2 acceptance test.
c. **On acceptance:** append CR4's reduction results to `bras_mapping.md` §5 and the classification
   tables before any CR4 comparison; write its scenes (`make_bras_scenes.py`); extend
   `tests/golden/validation_baseline.json` through `tools/ci/update_goldens.py` (reason 'CR4 added,
   pre-committed room'); re-run the report (`docs/validation/report-phase05.md`) on three rooms,
   replacing the provisional two-room one, and the scope 6 comparisons that use room sets (B12 with
   its conditions, B11 (B) evidence, paired comparisons); then take the deferred B12 and B11
   decisions per phase-05.md's unchanged pass rules.
d. **Nightly gate:** stays green with CR4 added, and the `MAKROOF_TEST_BIAS_T60` test covers one CR4
   scene.

## Out of scope

Anything that does not need CR4.

## Acceptance criteria — automated

- [ ] The reader regression guard is green (`test_skp_reader.py`, CR2/CR3 extraction byte-identical,
      `make_bras_scenes.py --check`).
- [ ] The CR4 `bras_mapping.md` §2 acceptance test passes in
      `tools/validation/tests/test_skp_reader.py` (a CR4 case is added).
- [ ] `make_bras_scenes.py --check`.
- [ ] The report generates reproducibly on three rooms.
- [ ] The nightly gate is green with the CR4 baseline, and the `MAKROOF_TEST_BIAS_T60` test covers one
      CR4 scene and meets phase-05.md's criterion.
- [ ] AQ9 pass/fail is printed per room and per pair for CR4.

phase-05.md's paragraph below its criteria applies unchanged (failing AQ9 does not fail CI; "AQ9 met
in x/y scenes"; Maisara decides at the review via /fix-plan on B10/B11/B12/B2).

## Listening / manual checklist (Maisara)

The A/B pack gains CR4 pairs; same instructions as phase-05e.md "Listening / manual checklist".

## Contractor review focus

The reader changes (are they generic? are they validated only by the area and planarity checks?), and
whether the three-room conclusions follow from the numbers.

## Risks

The SketchUp format is undocumented; the reader may need more than one layout.

## Definition of done

Automated criteria green; three-room report committed; status row 05f `done` with an "AQ9 met in
x/y" note per room, including CR4, by α set; the deferred B12 and B11 decisions recorded.

Stop rule: if CR4 is not accepted within two sessions of this phase, the status row 05f is
`blocked (reader: CR4 not extracted)`, CR4 stays 'pending extraction (reader), not dropped', the
two-room results of 05e stand as provisional, and Maisara decides (another extraction path, or
accepting the two-room label through /fix-plan as a phase-05.md change).
