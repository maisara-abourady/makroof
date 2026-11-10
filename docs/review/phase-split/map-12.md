# Split map — Phase 12 (Material library + starter presets)

Source: `docs/phases/phase-12.md` (size S, depends on 01, 11). Drafted per `0-drafting-brief.md`; pure
reallocation. No threshold, number, AX/AQ value, criterion wording or decision is changed.

Numbering used below (the phase file numbers only its scope): scope items **S1–S8** as numbered in the file
(sub-bullets by their bold label); automated criteria **AC1–AC7** in file order; listening items **L1–L4**;
contractor review focus **CF1–CF3** (the three clauses of its one sentence); risks **R1–R2** (the two clauses);
definition of done **DoD1–DoD3**; assumptions by id (AQ3, AX17, F3).

## 1. Sub-phase table

| id | title | lead subject matter (seat, row words) | size | depends on | what it ships | automated criteria owned |
|---|---|---|---|---|---|---|
| **12-1** | Material library | Seat 9 Room acoustician — "material-library provenance and uncertainty bounds" (row: "real rooms as references … material-library provenance and uncertainty bounds") | S | 01, 11 | `resources/materials.json` (25–40 cited materials, 8-band α, s per AX17, extrapolation rule in the header), `docs/THIRD_PARTY.md` source rows, `module3d::MaterialLibrary` feeding Phase 11's surface dropdown (replacing its placeholder list), scenes carrying numbers with the ID in `extensions` only | **AC5** (whole); **AC2, material-ID clause** (shared, see note) |
| **12-2** | Starter presets and preset browser | Seat 9 Room acoustician — "preset validation against measured rooms" (row: "real rooms as references … preset validation against measured rooms"); Seat 6's "presets and profiles" and Seat 6 (ii) rule are supporting, not lead | S | 12-1 (materials, AC2's material IDs), 01, 11; scope 7's W_max relation to 07c unchanged (see §2) | 8 shoebox presets in four categories with `extensions.preset`, `resources/presets/README.md` (character, T30 ranges), category-grouped undoable preset browser, outdoor two-branch report, U-at-default-placement check and J1 Trigger 2 handling | **AC1, AC2 (whole), AC3, AC4, AC6, AC7** |

**Note on AC2 (G2 clause split).** AC2 is a compound criterion. 12-1 owns its existing clause, worded as before with
only the subject it needs: "**No preset logic in the engine:** a CI test greps `src/sim/` for every material ID …
and finds nothing." 12-2 owns AC2 verbatim and whole ("every preset name, every material ID and the string
`preset`"), extending the same test once presets exist. No wording changed.

**Why two, not one or three.**
- Not kept whole: the phase's two halves are distinct and each carries its own risk and check. The material library
  is the phase's dominant risk ("Material data quality dominates realism", R1; contractor focus on provenance and
  extrapolation, CF1; licence/citation check) and is useful on its own (Phase 11's dropdown switches from the
  placeholder list to the cited library, phase-11.md:30). Since the file was sized S, scope 6–8 were added from
  phase 05b (AX37 (5.4) outdoor branches, AX44 U at every default placement with the J1 Trigger 2 rule and its OPEN
  placement set, AX38 (vi) D-T3), which make the preset half a full session of validation on its own.
- Not three: a separate preset-browser sub-phase (dropdown grouped by category, undoable load) would be a few lines
  of editor glue whose criteria (AC3, AC7) need the presets to exist; it is neither distinct nor risky enough to
  deserve a session, so it stays in 12-2.
- Each is buildable alone with main green: 12-1 touches `resources/`, `src/module3d/`, the Phase 11 dropdown and
  `docs/THIRD_PARTY.md`; 12-2 adds data, docs, the browser and tests on top.
- 12-1 produces no audio, so it adds no listening-pack render; all of L1–L4 need presets and stay in 12-2.

## 2. Order and rationale

12-1 → 12-2. This is the phase file's own order (scope 1–2 before 3–8): presets are built from library materials,
AC2's grep needs the material IDs, and L4 ("change one wall material") uses the library. It retires the risk the
file names first (R1, material data) first, as the unsplit phase would. Recorded dependencies are unchanged:

- **Scope 7 / 07c W_max.** Phase 12 does not depend on 07c; scope 7 says the U check is re-run under 07c's W_max once
  07c has landed, and phase-07c §6 last criterion says "if Phase 12 has run; otherwise Phase 12 runs it at 07c's
  W_max". All of scope 7 (U check, "Hall presets and J1", OPEN placement set) moves to 12-2, the sub-phase that
  builds and freezes the presets, so the trigger keeps its meaning with "Phase 12" read as 12-2 (references below).
- **Scope 8 / D-T3.** "Reaches Maisara before the presets are built": presets are built in 12-2, so the item sits at
  the start of 12-2; 12-1 builds no preset and cannot breach it.
- **Phase 13** depends on 00–12: per G3 the umbrella dependency means both 12-1 and 12-2. Unchanged.

**Decisions (G1).** No element of this map meets G1's tests: the order follows the phase's own structure and changes
neither what ships first nor which risk is retired first; no item crosses a recorded dependency (scope 7 and 8 stay
with the presets, AX37 (5.4), AX38 (vi), AX44 untouched); both sub-phases are S, so no size crosses the two-session
limit (each sub-phase's remainder would be `12-1b` / `12-2b`). **No CHOICE is raised.** For the decider's record
only (not a G1 decision): the alternative is to keep Phase 12 whole as one S session; the reasons against are in §1.

## 3. Coverage table

| original item (phase-12.md) | → sub-phase | note |
|---|---|---|
| Header: size S | umbrella | each sub-phase S; two-session limit per sub-phase (`12-1b`, `12-2b`) |
| Header: depends on 01, 11 | 12-1 | 12-2 depends on 12-1 (+ 01, 11 inherited) |
| Header: read first (CLAUDE.md, BUILD_PLAN §2 AQ3, §3 F3, PRD FR-3D-3, "Presets" decision, NFR-8) | umbrella (shared) | 12-1: AQ3, NFR-8; 12-2: F3, FR-3D-3, "Presets" decision, NFR-8 |
| Goal (editable starting scenes … from a cited material library, data only; engine knows no presets, NFR-8) | umbrella (shared) | "cited material library" → 12-1; "starting scenes … four categories" → 12-2 |
| Assumption AQ3 (per-band α + scattering) | umbrella (shared) + 12-1 | applied where materials are defined |
| Assumption AX17 (broadband s = mean of 500 Hz/1 kHz/2 kHz) | umbrella (shared) + 12-1 | derivation lives in the library; presets use the result |
| Assumption F3 (shoebox-only; descriptions say so) | 12-2 | |
| S1 `resources/materials.json` (25–40 materials, fields, citation, extrapolation rule, outdoor surfaces) | 12-1 | |
| S1 sub-bullet **Licence/citation check** (THIRD_PARTY rows, no wholesale copy) | 12-1 | |
| S2 `src/module3d/MaterialLibrary` (UI dropdown; scene stores numbers; ID in `extensions`) | 12-1 | |
| S3 `resources/presets/*.json` (8 presets, `extensions.preset`, the four category lists incl. car-cabin note) | 12-2 | |
| S4 Preset browser (grouped dropdown, undoable replace, parameters set, editable after) | 12-2 | |
| S5 `resources/presets/README.md` (character, expected T30 range) | 12-2 | |
| S6 Outdoor presets (AX37 (5.4) branches (a)/(b), ghost-tail criterion reverses AX37 (5.4)) | 12-2 | |
| S7 Preset placements (AX44, Seat 6 (ii); re-run under 07c's W_max) | 12-2 | |
| S7 **Hall presets and J1** (decider file 53 §2) and its three bullets | 12-2 | |
| S7 **OPEN** (interrogator file 54: placement set stated before presets are frozen) | 12-2 | the "decision before implementation" item |
| S8 Room range (AX38 (vi), D-T3 cost reaches Maisara before presets are built) | 12-2 | at the start of 12-2 |
| Out of scope (user preset saving/sharing; non-shoebox presets B2) | umbrella | governs both |
| AC1 every preset validates (C++ and Schema), renders both modes without NaN/Inf | 12-2 | |
| AC2 no preset logic in the engine (grep `src/sim/`) | 12-1 (material-ID clause) + 12-2 (whole) | shared; G2 clause split, wording verbatim |
| AC3 engine independence (UI path vs `extensions` stripped, bit-identical) | 12-2 | |
| AC4 each preset's T30 (500 Hz–1 kHz) inside its documented range | 12-2 | |
| AC5 materials file: citation, 8 α in [0.01, 1], s in [0, 1] | 12-1 | |
| AC6 U silent at every preset's default placement; outdoor two-branch check reported | 12-2 | |
| AC7 preset load undoable; state round trip bit-identical | 12-2 | |
| Listening preamble (one track, 8 presets, headphones binaural + Adam monitors) | 12-2 | |
| L1 each preset plausible and different | 12-2 | |
| L2 `open_field` almost dry with ground reflection; `courtyard` slap echoes, no ceiling | 12-2 | |
| L3 least-convincing presets noted (chapel, car expected), list to the Expert for B2 | 12-2 | |
| L4 load preset, change one wall material, save/reopen: edit kept | 12-2 | |
| CF1 material data provenance and extrapolation | 12-1 | |
| CF2 preset realism | 12-2 | |
| CF3 scenes carry numbers, not references | umbrella (shared) + 12-1 | rule set in S2 (12-1); 12-2's AC3 tests it for presets |
| R1 material data quality dominates realism | 12-1 | |
| R2 a box chapel won't sound like a real chapel (F3) | 12-2 | |
| Raise with Maisara | — | the phase file has no such section; S8's conditional D-T3 packet is in 12-2 |
| DoD1 all automated criteria green | 12-1 and 12-2, each for its own criteria | |
| DoD2 status row 12 `done` | umbrella | row 12 `split (12-1…12-2)`, `done` when both are; each sub-phase sets its own row |
| DoD3 listening notes in the PR | 12-2 | |

## 4. References

Grep of the repo (`docs/corpus`, `docs/review`, `docs/sessions`, `.git` excluded) for Phase 12 and its items. False
positives dropped: `docs/board/seat-1-…md:281`, `docs/board/seat-5-…md:668`, `.claude/agents/seat1-…md:377`,
`docs/phases/phase-05.md:490` (no Phase 12 text).

| file:line | reference | → sub-phase |
|---|---|---|
| docs/BUILD_PLAN.md:86 | AQ1 row, phases that break: "12" | umbrella |
| docs/BUILD_PLAN.md:88 | AQ3 row, phases that break: "12" | 12-1 |
| docs/BUILD_PLAN.md:114 | AX14 row (per-band levels), phases that break: "12" | 12-2 (preset T30/per-band measurement) |
| docs/BUILD_PLAN.md:117 | AX17 row, phases that break: "12" | 12-1 |
| docs/BUILD_PLAN.md:135 | AX35 row, phases that break: "12" (preset validation logs record `hrtfId`) | 12-2 |
| docs/BUILD_PLAN.md:137 | AX37 (5.4): "Phase 12 checks each outdoor preset with branch (a) … (b)"; breaks "12 (outdoor presets)" | 12-2 |
| docs/BUILD_PLAN.md:138 | AX38 (vi): D-T3 "reaches Maisara before Phase 12 builds the FR-3D-3 presets"; breaks "12 (D-T3 packet, if triggered)" | 12-2 |
| docs/BUILD_PLAN.md:141 | AQ10/AX41: "Phase 12's reopening trigger for capped presets is phase-12 'Hall presets and J1'" | 12-2 |
| docs/BUILD_PLAN.md:144 | AX44 Seat 6 (ii): "no default placement of a valid fixture or Phase 12 preset may raise U"; "(Phase 12 presets checked)"; breaks "12 (preset placements)" | 12-2 |
| docs/BUILD_PLAN.md:291 | §4 Phase 07c scope: "the Phase 12 (ii) re-run" | 12-2 |
| docs/BUILD_PLAN.md:326 | §4 Phase 11 scope: "material dropdown (from Phase 12's library once present …)" | 12-1 |
| docs/BUILD_PLAN.md:334 | §4 "### Phase 12 — Material library + starter presets · S" (block to :341) | umbrella (materials sentence → 12-1; presets, acceptance, 05b items, chapel risk → 12-2; licence risk → 12-1) |
| docs/BUILD_PLAN.md:391 | §6 log: "AX17 (… Phase 12)" | 12-1 |
| docs/BUILD_PLAN.md:446 | §6 log: "phase-12 (re-run (ii) under (C)'s W_max; hall presets checked …)" | 12-2 |
| docs/BUILD_PLAN.md:447 | §6 log: Trigger 2 "replaces phase-12's capped-class sentence"; "phase-07c §6 last criterion conditional on Phase 12 having run" | 12-2 |
| docs/phases/phase-07c.md:105 | §5 item 8: "The Phase 12 (ii) preset check … is re-run under this phase's W_max" | 12-2 |
| docs/phases/phase-07c.md:128–129 | §6 last criterion: "if Phase 12 has run; otherwise Phase 12 runs it at 07c's W_max" | 12-2 |
| docs/phases/phase-08.md:177 | "the Phase 12 preset listening checklist and its PR listening notes" | 12-2 |
| docs/phases/phase-11.md:30 | "list from `resources/materials.json` if Phase 12 is done, otherwise a placeholder list" | 12-1 |
| docs/phases/phase-11.md:64 | out of scope: "presets browser (Phase 12 adds it)" | 12-2 |
| docs/phases/phase-13.md:3 | depends on "00–12" | umbrella (both sub-phases, per G3) |
| docs/phases/phase-13.md:145 | "final listening pass through all presets" (implicit) | 12-2 (presets) |
| .claude/skills/review-phase-pr/references/phase-checklists.md:331 | "## Phase 12 — Material library + starter presets" (block to :345) | umbrella (materials.json, MaterialLibrary, THIRD_PARTY, material traps → 12-1; presets, browser, README, preset verifies → 12-2) |
| tools/validation/tests/test_phase05b2_data.py:59 | "J1 L5 / phase-12 Trigger 2" (docstring) | 12-2 |
| tools/validation/phase05b2_asrun/README.md:15 | "J1 / phase-12 Trigger 2" | 12-2 |
| tools/validation/report.py:573 | "B10 stays after phase 12" (backlog ordering string) | umbrella |
| docs/validation/report-phase05.md:590 | "B10 stays after phase 12" | umbrella |
