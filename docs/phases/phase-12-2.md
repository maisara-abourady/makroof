# Phase 12-2 — Starter presets and preset browser

Size: **S** (remainder, if needed: `12-2b`) · Depends on: 12-1, 01, 11 · Part of: [phase-12](phase-12.md) · Lead
subject matter: Seat 9 (Room acoustician), "preset validation against measured rooms" (supporting: Seat 6 (Canvas
designer), "presets and profiles", and its Seat 6 (ii) rule) · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §3 (F3),
PRD FR-3D-3, "Presets" decision, NFR-8

## Goal

Editable **starting scenes** in the PRD's four categories, built from the cited material library of
[phase-12-1](phase-12-1.md), as data only (phase-12 Goal, this sub-phase's share). The engine must have no idea
presets exist (PRD core principle, NFR-8).

## Assumptions in force

- **F3**: v1 is shoebox-only, so every preset is a shoebox approximation. The preset descriptions say so
  honestly (e.g. "Chapel (simplified box shape)").

And all of the umbrella's ([phase-12](phase-12.md#assumptions-in-force)), AQ3 and AX17 included.

## Scope

Scope 8 (Room range) is read at the start of this sub-phase, before any preset is built.

3. `resources/presets/*.json` — 8 presets (2 per category), each a full valid contract scene plus
   `extensions.preset = {name, category, description}`: (phase-12 scope 3)
   - Clubs & warehouses: `club_small`, `warehouse`.
   - Halls, chapels & churches: `chapel_box`, `concert_hall_box`.
   - Outdoor: `open_field` (ground only), `courtyard` (4 hard walls, open sky).
   - Domestic: `living_room`, `car_cabin_box` (the minimum-size room with car-like materials; note that
     real car acoustics are far from a shoebox).
4. Preset browser in the editor (dropdown grouped by category). Loading a preset replaces the scene
   (undoable) and sets parameters accordingly. The user can edit everything afterwards. (phase-12 scope 4)
   Presets never carry E_b (AX48; phase-07c-1 decision loop, 2026-11-12, decider file
   `docs/review/phase-07c-1/12-decider-decision-r3.md` §8).
5. Document each preset's expected character and expected T30 range in `resources/presets/README.md`.
   (phase-12 scope 5)
6. **Outdoor presets (AX37 (5.4), phase 05b):** each outdoor preset (`open_field`, `courtyard`) is checked
   with branch (a), the single-scatter floor integral, when all non-ground faces have α = 1, or branch
   (b), the seeded tracer within ±1 dB, otherwise; reported, not tuned. The ghost-tail criterion (the
   reference puts the energy after t_mix,e more than 60 dB below the direct sound while the rendered tail
   after t_mix,e is within 60 dB of it) firing on any outdoor preset reverses AX37 (5.4). (phase-12 scope 6)
7. **Preset placements (AX44, Seat 6 (ii)):** no preset's default placement may raise the "approximate"
   note U; if one does, the preset's placement is changed, not the predicate. This check is re-run under
   phase-07c's W_max once that phase has landed (decider files 47 §4 (iii) 8, 51 §4 item 7). (phase-12 scope 7)
   **Hall presets and J1** (decider file 53 §2, exact text). Before Phase 12 presets are frozen, every
   preset's default placement is computed at the final W_max, reporting SE, cap hit and U (Seat 9).
   (phase-12 scope 7, Hall presets and J1)
   - A preset whose default placement raises U is first fixed by changing its placement, never the
     predicate (Seat 6 (ii)).
   - If U stays raised through the capped branch (cap hit AND achieved SE > 0.33 dB) at every reasonable
     placement, because the whole window is long, the preset **reopens J1** (bring (C) forward, or
     re-size W_max), and no preset is relabelled or re-materialed to hide it.
   - Capped presets with achieved SE ≤ 0.33 dB, where U is silent (for example rooms near 100 m at
     SE ≤ 0.15 dB, C16 (f)), are **reported only**, with their SE.
   - **OPEN** (interrogator file 54; not decided here): the placement set for "every reasonable
     placement" (e.g. the preset's listener region) is stated before presets are frozen. (phase-12 scope 7, OPEN)
   - **Outdoor presets and J1 (D-H3 (b) / H3-F2, 2026-11-10; decider files 20, 25, 27; interrogator files
     22, 26, 28; AX41, AX44):** the J1 trigger's cause clause ("because the whole window is long") does
     not cover a capped U on a near-zero total that sits below the −60 dB line (an open field); such a
     preset is reported with that fact and its cause and does not reopen J1; `courtyard` (four walls, open
     sky) is tested as a room, not assumed. The CI report states, for every preset where U is raised at
     its default (the outdoor presets included), the cause (cap / both-near / VOV_union ≥ 0.1), whether a
     placement change can silence it (a one-off record) and the tail's energy after t_dir + 50 ms relative
     to the direct sound. AX44's display rule applies to the note (Phase 11 scope 8): not shown where that
     tail lies more than 60 dB below the direct sound by AX37 (5.4)'s kept check with E_target raised by
     3·SE, keyed on the measured ratio only, never on the preset category (NFR-8); U stays raised in the
     diagnostics.
8. **Room range (AX38 (vi)):** D-T3 was not needed (2026-11-10). If a D-T3 pass is ever triggered by the
   AX38 ceiling, its cost per scene class (closed reverberant box against open-face outdoor box) reaches
   Maisara before the presets are built. (phase-12 scope 8)

## Out of scope

The umbrella's out-of-scope items ([phase-12](phase-12.md#out-of-scope)), and what
[phase-12-1](phase-12-1.md) owns (`resources/materials.json`, `MaterialLibrary`, the `docs/THIRD_PARTY.md` rows).

## Acceptance criteria — automated

- [ ] Every preset validates against the contract (C++ and JSON Schema) and renders in both modes without
      NaN/Inf. (phase-12 AC1)
- [ ] **No preset logic in the engine:** a CI test greps `src/sim/` for every preset name, every material
      ID and the string `preset`, and finds nothing. (phase-12 AC2)
- [ ] **Engine independence:** a preset loaded through the UI path and the same scene JSON with
      `extensions` stripped render bit-identically. (phase-12 AC3)
- [ ] Each preset's T30 (500 Hz–1 kHz average) falls inside its documented range (e.g. living room
      0.3–0.6 s, concert hall box 1.6–2.4 s, open field < 0.1 s). (phase-12 AC4)
- [ ] U is silent at every preset's default placement (scope 7, AX44); the outdoor two-branch check
      (scope 6) is reported. (phase-12 AC6)
- [ ] Loading a preset is undoable and the state round trip remains bit-identical. (phase-12 AC7)

## Listening / manual checklist (Maisara)

One familiar track through all 8 presets, on headphones (binaural) and on the Adam monitors (stereo speakers):
(phase-12 listening preamble)
- [ ] Each preset sounds plausible for its name and different from the others. (phase-12 L1)
- [ ] `open_field` is almost dry with a ground reflection; `courtyard` has slap echoes and no ceiling. (phase-12 L2)
- [ ] Note which presets sound least convincing. Chapel and car are expected to be weakest (box shape).
      This list goes to the Expert for B2. (phase-12 L3)
- [ ] Load a preset, change one wall material, and save/reopen: your edit is kept. (phase-12 L4)

## Contractor review focus

Preset realism (phase-12 CF2). The rule that scenes carry numbers, not references (phase-12 CF3) is reviewed in
[phase-12-1](phase-12-1.md) and the umbrella; AC3 above tests it for presets.

## Risks

A box chapel won't sound like a real chapel (F3) (phase-12 R2).

## Definition of done

- All automated criteria green (phase-12 DoD1, for this sub-phase's criteria).
- Status row 12-2 `done` (the umbrella's row 12 is `done` when 12-1 and 12-2 both are).
- Listening notes in the PR (phase-12 DoD3).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder
  into `phase-12-2b.md`.

## Notes from the split

- Final corrections list, item 2 (`5-decider-decision-r2.md`, survived in `6-interrogator-decision-r2.md`): "12: drop
  12-1's AC2 share; 12-1 owns AC5 alone; AC2 whole in 12-2."
- References to Phase 12's presets elsewhere read as this sub-phase: phase-07c §5 item 8 ("The Phase 12 (ii) preset
  check … is re-run under this phase's W_max") and §6 last criterion ("if Phase 12 has run; otherwise Phase 12 runs
  it at 07c's W_max"); "Before Phase 12 presets are frozen" in scope 7 above (map-12 §2, references table).
