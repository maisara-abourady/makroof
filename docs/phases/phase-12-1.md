# Phase 12-1 — Material library

Size: **S** (remainder, if needed: `12-1b`) · Depends on: 01, 11 · Part of: [phase-12](phase-12.md) · Lead subject
matter: Seat 9 (Room acoustician), "material-library provenance and uncertainty bounds" · Read first: `CLAUDE.md`,
`docs/BUILD_PLAN.md` §2 (AQ3), PRD NFR-8

## Goal

The cited **material library** that the starting scenes of [phase-12-2](phase-12-2.md) are built from, as data only
(phase-12 Goal, this sub-phase's share). The engine must have no idea presets exist (PRD core principle, NFR-8).

## Assumptions in force

- **AQ3**: materials are per-band α (8 bands, 63 Hz–8 kHz) + scattering.
- **AX17**: the contract (AQ1, frozen) has one broadband scattering coefficient per surface. Where a
  source gives s per octave band, the library stores the per-band values and the scene gets their
  arithmetic mean over the 500 Hz, 1 kHz and 2 kHz bands. Per-band scattering is post-v1 (BUILD_PLAN §5 B10).

And all of the umbrella's ([phase-12](phase-12.md#assumptions-in-force)).

## Scope

1. `resources/materials.json` — 25–40 materials, each with `id`, display name, category (hard, soft,
   wood, glass, ground, …), 8-band α, scattering (per-band where the source gives it, plus the broadband
   value derived per AX17), and a **source citation** (published absorption tables
   from standard room-acoustics textbooks or open datasets; where a source gives only 125 Hz–4 kHz,
   document the extrapolation rule for 63 Hz and 8 kHz once, in the file header). Include outdoor
   "surfaces": `open_air` (α = 1.0, s = 0), grass, soil, asphalt, snow. (phase-12 scope 1)
   - **Licence/citation check:** numeric tables of physical data are generally reusable, but record each
     source in `docs/THIRD_PARTY.md`, and don't copy any database wholesale where its terms say otherwise.
     (phase-12 scope 1, Licence/citation check)
2. `src/module3d/MaterialLibrary.h/.cpp` — loads the library; the UI dropdown uses it. A scene stores
   **numeric α/s values**, never material IDs. The contract stays self-contained, so a preset or project
   renders even if the library changes later. The material ID is kept in `extensions` for UI display only.
   (phase-12 scope 2)

## Out of scope

The umbrella's out-of-scope items ([phase-12](phase-12.md#out-of-scope)), and everything that
[phase-12-2](phase-12-2.md) owns (presets, preset browser, preset README, scope 3–8).

## Acceptance criteria — automated

- [ ] Materials file: every entry has a citation, 8 α values in [0.01, 1], s in [0, 1]. (phase-12 AC5)

## Listening / manual checklist (Maisara)

None: this sub-phase produces no audio. All of phase-12's listening items (L1–L4) are in
[phase-12-2](phase-12-2.md).

## Contractor review focus

Material data provenance and extrapolation (phase-12 CF1), and that scenes carry numbers, not references (phase-12
CF3; shared with the umbrella).

## Risks

Material data quality dominates realism (phase-12 R1).

## Definition of done

- All automated criteria green (phase-12 DoD1, for this sub-phase's criteria).
- Status row 12-1 `done` (the umbrella's row 12 is `done` when 12-1 and 12-2 both are).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder
  into `phase-12-1b.md`.

## Notes from the split

- Final corrections list, item 2 (`5-decider-decision-r2.md`, survived in `6-interrogator-decision-r2.md`): "12: drop
  12-1's AC2 share; 12-1 owns AC5 alone; AC2 whole in 12-2."
