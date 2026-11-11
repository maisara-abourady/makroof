# Phase 12 — Material library + starter presets

Size: **split into 12-1…12-2** · Depends on: 01, 11 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ3) and §3 (F3), PRD FR-3D-3, "Presets" decision, NFR-8

## Goal

Editable **starting scenes** in the PRD's four categories, built from a cited **material library**, as
data only. The engine must have no idea presets exist (PRD core principle, NFR-8).

## Assumptions in force

- **AQ3**: materials are per-band α (8 bands, 63 Hz–8 kHz) + scattering.
- **AX17**: the contract (AQ1, frozen) has one broadband scattering coefficient per surface. Where a
  source gives s per octave band, the library stores the per-band values and the scene gets their
  arithmetic mean over the 500 Hz, 1 kHz and 2 kHz bands. Per-band scattering is post-v1 (BUILD_PLAN §5 B10).
- **F3**: v1 is shoebox-only, so every preset is a shoebox approximation. The preset descriptions say so
  honestly (e.g. "Chapel (simplified box shape)").

## Sub-phases

| id | title | lead seat | size | depends on | ships | owns |
|---|---|---|---|---|---|---|
| [12-1](phase-12-1.md) | Material library | Seat 9 (Room acoustician), "material-library provenance and uncertainty bounds" | S | 01, 11 | `resources/materials.json`, `docs/THIRD_PARTY.md` source rows, `module3d::MaterialLibrary` feeding Phase 11's surface dropdown | AC5 |
| [12-2](phase-12-2.md) | Starter presets and preset browser | Seat 9 (Room acoustician), "preset validation against measured rooms" (supporting: Seat 6, "presets and profiles", Seat 6 (ii)) | S | 12-1, 01, 11 | 8 shoebox presets with `extensions.preset`, `resources/presets/README.md`, the category-grouped undoable preset browser, the outdoor two-branch report, the U check at default placements and J1 handling | AC1, AC2, AC3, AC4, AC6, AC7 |

Order 12-1 → 12-2 is the phase's own (scope 1–2 before 3–8).

## Where the original items went

Labels: scope items 1–8 as numbered; automated criteria AC1–AC7 in file order; listening items L1–L4 (after the
preamble); contractor review focus CF1–CF3 (the three clauses of its sentence); risks R1–R2 (its two clauses);
definition of done DoD1–DoD3.

| original item | → |
|---|---|
| Header (size, depends on, read first) | umbrella (size now "split"; 12-1 reads AQ3, NFR-8; 12-2 reads F3, FR-3D-3, "Presets" decision, NFR-8) |
| Goal | umbrella (shared: material library → 12-1, starting scenes → 12-2) |
| Assumptions AQ3, AX17 | umbrella and 12-1 |
| Assumption F3 | umbrella and 12-2 |
| Scope 1 (incl. Licence/citation check) | 12-1 |
| Scope 2 | 12-1 |
| Scope 3, 4, 5, 6 | 12-2 |
| Scope 7 (incl. Hall presets and J1, OPEN) | 12-2 |
| Scope 8 | 12-2 (read at its start) |
| Out of scope | umbrella (governs both) |
| AC1, AC2, AC3, AC4 | 12-2 |
| AC5 | 12-1 |
| AC6, AC7 | 12-2 |
| Listening preamble, L1–L4 | 12-2 |
| CF1 (material data provenance and extrapolation) | 12-1 |
| CF2 (preset realism) | 12-2 |
| CF3 (scenes carry numbers, not references) | umbrella and 12-1 |
| R1 (material data quality) | 12-1 |
| R2 (box chapel, F3) | 12-2 |
| DoD1 (automated criteria green) | 12-1 and 12-2, each for its own criteria |
| DoD2 (status row 12 `done`) | umbrella |
| DoD3 (listening notes in the PR) | 12-2 |

## Out of scope

User preset saving/sharing (PRD excludes sharing; saving within the project already works through state),
non-shoebox presets (B2).

## Contractor review focus

That scenes carry numbers, not references (phase-12 CF3; shared with 12-1).

## Definition of done

Status row 12 `done` (phase-12 DoD2): row 12 reads `split (12-1…12-2)` and becomes `done` when both sub-phases
are; each sub-phase sets its own row.

## Notes from the split

- Final corrections list, item 2 (`5-decider-decision-r2.md`, survived in `6-interrogator-decision-r2.md`): "12: drop
  12-1's AC2 share; 12-1 owns AC5 alone; AC2 whole in 12-2."
- References elsewhere to Phase 12's presets (phase-07c §5 item 8 and §6 last criterion, phase-11 out of scope's
  "presets browser (Phase 12 adds it)", phase-08's preset validation logs) resolve to 12-2; phase-11's "if Phase 12
  is done" for the material dropdown resolves to 12-1; phase-13's dependency on "00–12" means both.

Status: the umbrella is `done` when every sub-phase is. A dependency on phase 12 means all of its sub-phases unless a
sub-phase is named.
