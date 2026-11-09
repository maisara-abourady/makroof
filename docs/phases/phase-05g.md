# Phase 05g — Phase 05f follow-ups

Size: **S** · Depends on: 05f · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §0, §2 (AX30) and §5 (B12), `docs/phases/phase-05.md` scope 6, `docs/phases/phase-05f.md`, `docs/validation/bras_mapping.md` §1–§4, the PR #15 description sections "Follow-ups" and "Review" (GitHub), `docs/review/ledger.md` sections "Phase 05f session 1" and "BUILD_PLAN §5 B12, phase-05.md scope 6 — Phase 05f B12 outcome"

Created on 2026-11-07 at Maisara's request ("take care of all follow ups") for the follow-ups of
Phase 05f (PRs #15–#17), as a fresh session. This phase changes no simulator code and produces no
new results; it corrects the report generator, the reader's consistency and re-synchronisation, and
the plan text where the 05f review found gaps. **Every rule, threshold, method and condition stays in
`docs/phases/phase-05.md`** (and AX26, AX30 in `docs/BUILD_PLAN.md` §2); where this file and
phase-05.md seem to differ, phase-05.md wins and the difference goes to `/fix-plan`.

## Raise with Maisara (she does not track these herself)

The session raises each item in its **first message** and again in the **PR description**.

1. **Area tolerance of the `bras_mapping.md` §2 acceptance test (scope 4).** Only if the `/fix-plan`
   loop (interrogator → decider over the board's seats, `/fix-plan` step 3) finds that it needs her,
   as a C2-type product choice. Otherwise nothing beyond this item.

## Goal

Close the Phase 05f follow-ups without changing any simulator behaviour, any room's geometry or any
metric.

## Assumptions in force

As phase-05.md, phase-05e.md and phase-05f.md "Assumptions in force", unchanged; AX26 and AX30 as in
`docs/BUILD_PLAN.md` §2. B12 as recorded in `docs/BUILD_PLAN.md` §5 (recommendation not adopted,
Eyring stays, AQ2 unchanged; accepted by Maisara 2026-11-07).

## Start here

Phase 05f is done (PRs #15, #16). The committed results (`tools/validation/data/`,
`docs/validation/report-phase05.md`, `tests/golden/validation_baseline.json`) are the inputs; nothing
here re-runs the comparison. The follow-ups come from the PR #15 "Follow-ups" and "Review" sections and
the ledger sections listed under "Read first".

Commands: as phase-05f.md "Start here", plus

```bash
pytest tools/validation/tests/test_report_reproducible.py
pytest tools/validation/tests/test_skp_reader.py
python tools/validation/make_bras_scenes.py --check
```

## Scope

1. **Report B12 paragraph.** `tools/validation/report.py` generates an "Open plan question
   (/fix-plan)" paragraph in report §3 whenever a predictor meets the B12 arithmetic. Replace it with
   the recorded outcome (`docs/BUILD_PLAN.md` §5 B12: recommendation not adopted, accepted by Maisara
   2026-11-07). Regenerate `docs/validation/report-phase05.md` from the committed results.
   Outcome: `test_report_reproducible.py` passes; no metric changes.
2. **Report numbers from data.** `report.py` hand-types CR4's volume ratio (+0.08 %, 8 656.5 vs
   8 650 m³), the fit figures (CR2 ≤ 0.45 %, CR3 ≤ 0.23 %, CR4 ≤ 0.29 %) and the seating s (0.43 /
   0.60 / 0.85–0.87). Compute what the committed data allow (seating s from
   `tools/validation/data/bras_reduction.json`; volume ratios from the documented model V and the BRAS
   sheet volumes, kept as one cited constant) and cite the rest to `bras_mapping.md` §1.
   Outcome: a test pins these figures.
3. **Kuttruff §9.4 citation.** phase-05.md scope 6 says "a* assumes s = 1 on all walls; with low s
   the true T can fall on the other side of Eyring (Kuttruff §9.4)"; the interrogator did not find
   that statement in the §9.4 passages it read. Check it against `docs/corpus/`.
   Outcome: either the citation is confirmed (ledger row with the passage), or the citation or
   statement is corrected through `/fix-plan` (ledger row, §6 row).
4. **Area tolerance of the `bras_mapping.md` §2 acceptance test.** Currently "0.01 m², ±0.1 % allowed
   for rounding of large areas" (`extract_bras_geometry.match_materials`, `rel_tol=1e-3`). The 05f
   review found it loose against the measured ≤ 0.005 m² (a reader bug dropping ≈ 1 m² from CR4's
   1 774 m² concrete would pass). **This is a decision for this session's `/fix-plan` loop
   (the decision loop of `/fix-plan` step 3: interrogator, decider over the board's seats): whether
   to tighten it, and to what.** No value is proposed here. Outcome: the decision is recorded in the
   ledger; if it changes the tolerance, that is a plan change (`bras_mapping.md` §2, §6 row) applied
   to `tools/validation/tests/test_skp_reader.py` and `tools/validation/extract_bras_geometry.py`
   together, and CR2, CR3 and CR4 still pass.
5. **Reader definition count.** CR3 and CR4 declare 19 component definitions, but the reader finds 17
   definition records after the first geometry class (the `n_defs` cross-check was dropped in 05f by
   the root-start rule). Explain the difference from the files and restore a consistency check in
   `tools/validation/skp_reader.py`.
   Outcome: the explanation is in the reader docstring and the PR; the check is tested and the CR2,
   CR3 and CR4 parses pass it.
6. **Reader index offset in definitions.** Crossing a component-definition header,
   re-synchronisation picks the smallest index offset that survives a 60-reference trial, which can
   under-count by one (CR3 and CR4 show 'bad reference' skips a few KB after each 'definition body'
   skip). Make it exact (e.g. an extended trial before accepting an offset) without changing any
   room's geometry.
   Outcome: `test_extraction_reproduces_the_committed_geometry[CR2/CR3/CR4]` and the area and
   planarity tests pass; `reader_skips` in `bras_geometry.json` may fall (the committed file is
   updated and the PR says so).
7. **CR4's flat AX26 box as an Expert question.** Record in `bras_mapping.md` §4 "Known limits" and
   in the Expert question list the plan uses: A_floor (1 754 m², floor-assigned faces including raked
   seating) exceeds the floor's oriented-bounding-rectangle footprint (≈ 1 105 m²), giving
   H = 4.93 m vs V/footprint ≈ 7.8 m. No rule change after results (phase-05.md; AX26 is reversed
   only on independent evidence).
   Outcome: both entries committed; AX26 unchanged.
8. **Phase-06 branch.** `claude/laughing-fermi-u9iq7f` merged main before PR #16, and its nightly BRAS
   job fails on `ModuleNotFoundError: h5py` (run 42366217992). Merge current `origin/main` into it
   with a merge commit (no rebase, no force-push) and push. Touch nothing else on that branch (it
   belongs to the phase-06 session; Maisara authorised this follow-up).
   Outcome: the BRAS validation job passes on that branch.
9. **Bookkeeping.** Status row 05g `in progress`, then `done` with the PR link; PR description per
   `CLAUDE.md`; steward brief.
   Outcome: CI green on Linux, macOS and Windows; status row and brief committed.

## Out of scope

Any simulator change; anything that needs new results (comparisons, baselines, A/B pack renders).

## Acceptance criteria — automated

- [ ] Scope 1: `test_report_reproducible.py` passes on the regenerated report; no metric changes.
- [ ] Scope 2: a test pins the computed seating s and volume ratios, and the cited figures.
- [ ] Scope 5: a test of the restored definition-count consistency check passes on CR2, CR3, CR4.
- [ ] Scope 6: `test_extraction_reproduces_the_committed_geometry[CR2/CR3/CR4]` and the area and
      planarity tests pass.
- [ ] `make_bras_scenes.py --check`.
- [ ] CI green on Linux, macOS and Windows.
- [ ] The nightly BRAS validation is green on the 05g PR.

## Listening / manual checklist (Maisara)

None (no audio change).

## Contractor review focus

The reader changes of scopes 5 and 6 (generic? geometry unchanged?), whether every report number is
now computed or cited, and the scope 3 and 4 ledger rows.

## Risks

Scope 6 touches the reader's re-synchronisation; the re-extraction tests are the guard.

## Definition of done

Automated criteria green; scope 3, 4 and 7 outcomes recorded (ledger, plan files); the phase-06
branch's BRAS job green; status row 05g `done` with the PR link.
