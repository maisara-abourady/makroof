# Phase 12 — Material library + starter presets

Size: **S** · Depends on: 01, 11 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ3) and §3 (F3), PRD FR-3D-3, "Presets" decision, NFR-8

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

## Scope

1. `resources/materials.json` — 25–40 materials, each with `id`, display name, category (hard, soft,
   wood, glass, ground, …), 8-band α, scattering (per-band where the source gives it, plus the broadband
   value derived per AX17), and a **source citation** (published absorption tables
   from standard room-acoustics textbooks or open datasets; where a source gives only 125 Hz–4 kHz,
   document the extrapolation rule for 63 Hz and 8 kHz once, in the file header). Include outdoor
   "surfaces": `open_air` (α = 1.0, s = 0), grass, soil, asphalt, snow.
   - **Licence/citation check:** numeric tables of physical data are generally reusable, but record each
     source in `docs/THIRD_PARTY.md`, and don't copy any database wholesale where its terms say otherwise.
2. `src/module3d/MaterialLibrary.h/.cpp` — loads the library; the UI dropdown uses it. A scene stores
   **numeric α/s values**, never material IDs. The contract stays self-contained, so a preset or project
   renders even if the library changes later. The material ID is kept in `extensions` for UI display only.
3. `resources/presets/*.json` — 8 presets (2 per category), each a full valid contract scene plus
   `extensions.preset = {name, category, description}`:
   - Clubs & warehouses: `club_small`, `warehouse`.
   - Halls, chapels & churches: `chapel_box`, `concert_hall_box`.
   - Outdoor: `open_field` (ground only), `courtyard` (4 hard walls, open sky).
   - Domestic: `living_room`, `car_cabin_box` (the minimum-size room with car-like materials; note that
     real car acoustics are far from a shoebox).
4. Preset browser in the editor (dropdown grouped by category). Loading a preset replaces the scene
   (undoable) and sets parameters accordingly. The user can edit everything afterwards.
5. Document each preset's expected character and expected T30 range in `resources/presets/README.md`.
6. **Outdoor presets (AX37 (5.4), phase 05b):** each outdoor preset (`open_field`, `courtyard`) is checked
   with branch (a), the single-scatter floor integral, when all non-ground faces have α = 1, or branch
   (b), the seeded tracer within ±1 dB, otherwise; reported, not tuned. The ghost-tail criterion (the
   reference puts the energy after t_mix,e more than 60 dB below the direct sound while the rendered tail
   after t_mix,e is within 60 dB of it) firing on any outdoor preset reverses AX37 (5.4).
7. **Preset placements (AX44, Seat 6 (ii)):** no preset's default placement may raise the "approximate"
   note U; if one does, the preset's placement is changed, not the predicate. This check is re-run under
   phase-07c's W_max once that phase has landed (decider files 47 §4 (iii) 8, 51 §4 item 7).
   **Capped class (Seat 9):** hall presets, rooms near 100 m included, are checked for capped-class
   membership (AX41 cap hit) at the final W_max and reported (the capped class is the long-window
   synthetic s = 1 layouts and rooms near 100 m, file 51 §2 L5; a hall preset in it reopens the board answer,
   file 47 §4, strongest objection).
8. **Room range (AX38 (vi)):** D-T3 was not needed (2026-11-10). If a D-T3 pass is ever triggered by the
   AX38 ceiling, its cost per scene class (closed reverberant box against open-face outdoor box) reaches
   Maisara before the presets are built.

## Out of scope

User preset saving/sharing (PRD excludes sharing; saving within the project already works through state),
non-shoebox presets (B2).

## Acceptance criteria — automated

- [ ] Every preset validates against the contract (C++ and JSON Schema) and renders in both modes without
      NaN/Inf.
- [ ] **No preset logic in the engine:** a CI test greps `src/sim/` for every preset name, every material
      ID and the string `preset`, and finds nothing.
- [ ] **Engine independence:** a preset loaded through the UI path and the same scene JSON with
      `extensions` stripped render bit-identically.
- [ ] Each preset's T30 (500 Hz–1 kHz average) falls inside its documented range (e.g. living room
      0.3–0.6 s, concert hall box 1.6–2.4 s, open field < 0.1 s).
- [ ] Materials file: every entry has a citation, 8 α values in [0.01, 1], s in [0, 1].
- [ ] U is silent at every preset's default placement (scope 7, AX44); the outdoor two-branch check
      (scope 6) is reported.
- [ ] Loading a preset is undoable and the state round trip remains bit-identical.

## Listening / manual checklist (Maisara)

One familiar track through all 8 presets, on headphones (binaural) and on the Adam monitors (stereo speakers):
- [ ] Each preset sounds plausible for its name and different from the others.
- [ ] `open_field` is almost dry with a ground reflection; `courtyard` has slap echoes and no ceiling.
- [ ] Note which presets sound least convincing. Chapel and car are expected to be weakest (box shape).
      This list goes to the Expert for B2.
- [ ] Load a preset, change one wall material, and save/reopen: your edit is kept.

## Contractor review focus

Material data provenance and extrapolation, preset realism, and that scenes carry numbers, not references.

## Risks

Material data quality dominates realism; a box chapel won't sound like a real chapel (F3).

## Definition of done

All automated criteria green; status row 12 `done`; listening notes in the PR.
