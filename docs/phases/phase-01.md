# Phase 01 — Scene contract v1 (3D Module → Simulator)

Size: **S** · Depends on: 00 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ1, AQ3, AX6, AX7), PRD "System architecture", FR-SIM-1, FR-3D-10

## Goal

Implement and test the **versioned input contract** the Simulator defines and the 3D Module
conforms to (PRD FR-SIM-1). Every later phase passes scenes as `contract::SceneDescription`.

## Assumptions in force (don't change them quietly)

- **AQ1** (contract contents), **AQ3** (material properties and ranges), **AX6** (validation limits),
  **AX7** (exactly two emitters L/R in v1). The PRD's Q1 is unresolved. This is the default.

## Contract v1 specification

JSON document. All fields are required unless marked optional.

```json
{
  "contractVersion": "1.0",
  "units": "meters",
  "room": {
    "geometry": { "kind": "shoebox", "dimensions": [8.0, 12.0, 4.0] },
    "surfaces": {
      "floor":   { "absorption": [0.02,0.02,0.03,0.03,0.04,0.05,0.05,0.06], "scattering": 0.10 },
      "ceiling": { "absorption": [...8 values...], "scattering": 0.10 },
      "xMin":    { ... }, "xMax": { ... }, "yMin": { ... }, "yMax": { ... }
    }
  },
  "listener": { "position": [4.0, 3.0, 1.7] },
  "emitters": [
    { "id": "L", "channel": 0, "position": [3.0, 9.0, 2.0], "gainDb": 0.0 },
    { "id": "R", "channel": 1, "position": [5.0, 9.0, 2.0], "gainDb": 0.0 }
  ],
  "render": {
    "outputMode": "binaural",
    "hrtfId": "generic-v1",
    "maxReflectionOrder": 20,
    "tailSeed": 12345
  },
  "extensions": {}
}
```

Semantics:

- **Axes:** right-handed, x = right, y = forward, z = up. `dimensions` = `[W, D, H]` and the room
  occupies `[0,W]×[0,D]×[0,H]`. Surfaces are named by the plane they sit on, so nothing depends on
  which way the listener faces: `xMin` (x=0), `xMax` (x=W), `yMin` (y=0), `yMax` (y=D),
  `floor` (z=0), `ceiling` (z=H). Positions are `[x, y, z]` in metres.
- **Bands:** `absorption` has exactly 8 values for octave bands centred at 63, 125, 250, 500, 1000,
  2000, 4000, 8000 Hz (`contract::kOctaveBandsHz`).
- **Ranges (AQ3):** absorption each in [0.01, 1.0]; scattering in [0, 1]; `gainDb` in [−60, +12];
  `maxReflectionOrder` integer in [0, 60]; `tailSeed` unsigned 32-bit.
- **Limits (AX6):** each room dimension in [1.5, 100] m; every emitter and the listener lie inside the
  room at least 0.1 m from every surface; every emitter is ≥ 0.3 m from the listener.
- **Emitters (AX7):** exactly 2, ids `L` and `R`, channels 0 and 1, each used once.
- **outputMode:** `binaural` | `stereoSpeakers`. **hrtfId:** v1 accepts only `generic-v1`.
- **extensions:** free object, ignored by the v1 Simulator, preserved in round trips (room for the
  3D Module's editor-only data such as UI colours. The Simulator must never read it).
- **Versioning:** `contractVersion` is `MAJOR.MINOR`. The reader accepts the same major and any minor.
  A higher minor than known loads, ignores unknown fields, and returns a *warning*. A different major
  is an error. Unknown fields at known minor versions are an error (this catches typos).

## Scope

1. `src/contract/`:
   - `SceneDescription.h` — plain structs (`Vec3`, `SurfaceMaterial`, `Room`, `Listener`, `Emitter`,
     `RenderSettings`, `SceneDescription`), `kOctaveBandsHz`, `enum class SurfaceId { xMin, xMax, yMin, yMax, floor, ceiling }`,
     `enum class OutputMode`. Value types with `operator==`.
   - `Version.h` — `kContractVersionMajor = 1`, `kContractVersionMinor = 0`.
   - `Json.h/.cpp` — `toJson`, `fromJson` (nlohmann/json pinned via FetchContent). Floats are
     written with round-trip precision (`%.17g`-equivalent).
   - `Validate.h/.cpp` — `ValidationResult validate(const SceneDescription&)` returning a list of
     `{code, path, message}`. Codes are a stable enum (e.g. `E_ABSORPTION_RANGE`,
     `E_EMITTER_TOO_CLOSE_TO_LISTENER`, `E_VERSION_MAJOR`, `W_VERSION_MINOR_NEWER`). Parsing errors
     and semantic errors both report a JSON path (e.g. `room.surfaces.floor.absorption[3]`).
   - `Parse.h/.cpp` — `ParseResult parseScene(std::string_view json)` = parse + version check +
     validate, never throws out of the library.
2. `docs/contract/scene-v1.schema.json` — JSON Schema (draft 2020-12) expressing everything the schema
   language can express (types, ranges, counts, enums). Geometric rules such as inside-room and
   distances are C++-only. Document that in the schema's `description`.
3. `docs/contract/README.md` — human-readable spec (the section above, polished), plus a
   "Changing the contract" section (copy the rule from `CLAUDE.md`) and a version history table.
4. Fixtures in `tests/scenes/valid/` (≥ 5: `small_room`, `medium_room`, `large_hall`, `open_field`
   (5 surfaces α=1.0, floor normal), `asymmetric_materials`) and `tests/scenes/invalid/` (≥ 15, one
   rule broken each, filename = expected error code, e.g. `E_ABSORPTION_RANGE.json`).
5. Tests:
   - `tests/unit/test_contract_roundtrip.cpp` — for every valid fixture: parse → toJson → parse gives
     an equal struct. Unknown `extensions` content is preserved.
   - `tests/unit/test_contract_validation.cpp` — every invalid fixture yields exactly its expected code.
     Edge values (α=0.01, α=1.0, distance exactly 0.3 m) are valid.
   - `tests/unit/test_contract_version.cpp` — "1.0" ok; "1.7" ok with warning; "2.0" rejected; "1" or
     "x" rejected.
   - `tools/ci/test_schema_agreement.py` (pytest, uses `jsonschema` pinned in
     `tools/ci/requirements.txt`) — schema accepts all valid fixtures and rejects every invalid fixture
     whose rule the schema can express (fixtures list which are C++-only via a `_cppOnly` sidecar list).
6. `tools/ci/check_boundaries.py` — fails if any file in `src/sim/` includes from `src/module3d/` or
   `src/plugin/`, if any file in `src/module3d/` includes from `src/sim/` or `src/plugin/`, or if
   `src/contract`/`src/sim` include any `juce_` header. Add it to CI with a self-test (pytest with a temp tree).
7. Add nlohmann/json and jsonschema to `docs/THIRD_PARTY.md`.

## Out of scope

Rendering, mesh geometry, the editable scene model (Phase 07), UI.

## Acceptance criteria — automated

- [ ] All contract unit tests pass on 3 OSes.
- [ ] Schema-agreement pytest passes.
- [ ] Boundary check passes and its self-test passes.
- [ ] Round trip of each valid fixture is byte-identical on the second serialization (serialize →
      parse → serialize gives the same bytes).

## Listening / manual checklist (Maisara)

No audio in this phase. Instead:
- [ ] Read `docs/contract/README.md`. Does it describe what a scene *is* in product terms? Is anything
      missing that you expect v1 to control? (If yes, note it on the PR. It may need an AX entry.)

## Contractor review focus

Field naming and semantics (they get frozen at release); error codes; whether the v1 contract can
grow to v1.x (multi-speaker emitters, dispersion) and v2 (mesh) without contortions.

## Risks

Over-design. Resist adding fields no v1 phase uses; versioning exists so they can be added later.

## Definition of done

Automated criteria green on CI; BUILD_PLAN status row 01 `done`; PR includes the manual checklist.
