# Scene contract v1 (3D Module → Simulator)

**Current version: 1.0.** Machine-readable schema: [`scene-v1.schema.json`](scene-v1.schema.json).
Implementation: [`src/contract/`](../../src/contract/). Example scenes: [`tests/scenes/valid/`](../../tests/scenes/valid/).

## What a scene is

A scene is everything the Simulator needs to render a track as if it were played in a space, and
nothing else. The 3D Module (the editor, presets, automation) turns whatever the user builds into
one scene. The Simulator renders from that scene alone (PRD FR-SIM-1, FR-3D-10). Whenever the user
moves something or changes a material, the 3D Module produces a new scene.

In v1 a scene describes:

| Part | What it controls | In product terms |
|---|---|---|
| **Room** | A rectangular room ("shoebox"): width, depth and height in metres. | The size of the space. Bigger rooms sound longer and later. |
| **Surfaces** | For each of the 6 surfaces (4 walls, floor, ceiling): how much sound it absorbs in each of 8 frequency bands, and how much it scatters. | What the room is made of. Concrete rings, curtains and carpet soak up highs, an open sky absorbs everything. |
| **Listener** | One position in the room. | Where the person hearing the track stands. The head is upright and faces the sources (AX3, decided by the Simulator). |
| **Emitters** | Exactly two point sources, L and R, each with a position and a level trim. The left channel of the track plays from one, the right from the other. | Where the two speakers playing the track stand. |
| **Render settings** | Headphones (binaural) or speakers output, which head model to use, how detailed the early reflections are, and a seed for the random part of the reverb. | How the result is delivered and how reproducible it is. |
| **Extensions** | A free area the Simulator never reads. | Editor-only data (camera angle, colours, notes) that must survive saving and loading. |

Not in v1 (each can be added later, see [Versioning](#versioning)): rooms that aren't shoeboxes
(mesh geometry), more than two sources or a multi-speaker layout, speaker types with their own
dispersion, sound passing through walls, user-controlled atmosphere, personalised head profiles.
These follow the defaults in [`BUILD_PLAN.md`](../BUILD_PLAN.md) §2 (AQ1, AQ3, AQ6, AQ8, AX4, AX7).

## Example

[`tests/scenes/valid/medium_room.json`](../../tests/scenes/valid/medium_room.json), shortened:

```json
{
  "contractVersion": "1.0",
  "units": "meters",
  "room": {
    "geometry": { "kind": "shoebox", "dimensions": [8.0, 12.0, 4.0] },
    "surfaces": {
      "floor":   { "absorption": [0.02, 0.02, 0.03, 0.03, 0.04, 0.05, 0.05, 0.06], "scattering": 0.10 },
      "ceiling": { "absorption": [0.20, 0.30, 0.45, 0.65, 0.80, 0.85, 0.85, 0.80], "scattering": 0.30 },
      "xMin":    { "absorption": [0.01, 0.01, 0.02, 0.02, 0.03, 0.04, 0.05, 0.05], "scattering": 0.05 },
      "xMax":    { "...": "same shape" },
      "yMin":    { "...": "same shape" },
      "yMax":    { "...": "same shape" }
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

## Specification

A scene is one JSON object. **Every field is required**; there are no optional fields in v1.

### Coordinates and units

- Lengths are in metres, levels in dB. `units` must be `"meters"`. Angles don't appear in v1.
- Axes are right-handed: **x = right, y = forward, z = up** (AQ1). Positions are `[x, y, z]`.
- `room.geometry.dimensions` is `[W, D, H]` (width along x, depth along y, height along z). The room
  occupies `[0, W] × [0, D] × [0, H]`: the origin is a floor corner.

### Fields

| Path | Type | Rule |
|---|---|---|
| `contractVersion` | string | `"MAJOR.MINOR"`, see [Versioning](#versioning). |
| `units` | string | `"meters"`. |
| `room.geometry.kind` | string | `"shoebox"` (the only kind in v1). |
| `room.geometry.dimensions` | 3 numbers | Each in **[1.5, 100] m** (AX6). |
| `room.surfaces` | object | Exactly the 6 keys `xMin`, `xMax`, `yMin`, `yMax`, `floor`, `ceiling`. |
| `room.surfaces.<s>.absorption` | 8 numbers | Absorption coefficient α per octave band, each in **[0.01, 1.0]** (AQ3). |
| `room.surfaces.<s>.scattering` | number | Broadband scattering coefficient in **[0, 1]** (AQ3). |
| `listener.position` | 3 numbers | Inside the room, at least **0.1 m** from every surface (AX6). |
| `emitters` | array | **Exactly 2** (AX7). |
| `emitters[i].id` | string | `"L"` or `"R"`, each used once. |
| `emitters[i].channel` | integer | Input channel that feeds this emitter: `0` or `1`, each used once. |
| `emitters[i].position` | 3 numbers | Inside the room, at least **0.1 m** from every surface and at least **0.3 m** from the listener (AX6). |
| `emitters[i].gainDb` | number | Level trim in **[−60, +12] dB**. |
| `render.outputMode` | string | `"binaural"` (headphones) or `"stereoSpeakers"`. |
| `render.hrtfId` | string | `"generic-v1"` (the only head model in v1, AQ6). |
| `render.maxReflectionOrder` | integer | Highest image-source reflection order, in **[0, 60]**. |
| `render.tailSeed` | integer | Unsigned 32-bit, **[0, 4294967295]**. Seeds every random process, so a scene always renders the same. |
| `extensions` | object | Anything. Preserved in round trips; ignored by the Simulator. |

Details:

- **Surfaces** are named by the plane they lie on, not by "front/back/left/right", so nothing
  depends on which way the listener faces: `xMin` is x = 0, `xMax` is x = W, `yMin` is y = 0,
  `yMax` is y = D, `floor` is z = 0, `ceiling` is z = H.
- **Bands:** the 8 absorption values are for octave bands centred at 63, 125, 250, 500, 1000, 2000,
  4000 and 8000 Hz, in that order (`contract::kOctaveBandsHz`). Reflectivity is 1 − α and isn't
  stored (PRD flag F5). An open side (sky, open field) is α = 1.0 in every band.
- **Emitters:** `id` names the emitter; `channel` says which input channel feeds it. The usual pairing
  is L = 0, R = 1. The contract also allows L = 1, R = 0 (a channel swap), because AX7 only asks for
  each id and each channel to be used once. Emitters are omnidirectional point sources (AQ8).
- **Integers:** a number with no fractional part such as `20.0` counts as an integer (as in JSON
  Schema). The writer always writes `20`.
- **Limits are inclusive.** α = 0.01 and α = 1.0, a clearance of exactly 0.1 m and a distance of
  exactly 0.3 m are all valid. Geometric limits are compared with a tolerance of 1 nm
  (`limits::kGeometryToleranceM`, BUILD_PLAN AX9), so a value written at the limit in decimal is accepted even when
  floating-point subtraction lands a hair below it (e.g. 3.3 − 3.0 = 0.2999999999999998).
- **extensions** is reserved for the 3D Module's editor-only data. The Simulator must never read
  it, so nothing in it can change the sound. It round-trips with its key order.

### Writing

`contract::toJson` writes 2-space indented JSON with keys in the order of the table above and a
trailing newline. Numbers are written with the shortest text that reads back to the identical
double (round-trip precision, equivalent to `%.17g`). So serialize → parse → serialize gives the
same bytes, and a scene saved and reopened is bit-identical.

## Versioning

`contractVersion` is `"MAJOR.MINOR"` (two decimal integers without leading zeros).

- **Minor** bump = additive change (a new field, a new enum value). Old scenes still load.
- **Major** bump = breaking change (e.g. a `mesh` geometry kind that replaces `dimensions`).

The reader (version 1.0) treats a document as follows:

| Document version | Result |
|---|---|
| `1.0` | Loads. An unknown field is an **error** (`E_UNKNOWN_FIELD`), which catches typos such as `gainDB`. |
| `1.x`, x > 0 | Loads with the **warning** `W_VERSION_MINOR_NEWER`. Unknown fields are ignored, every known rule still applies. The loaded scene is a 1.0 scene. |
| `2.0`, `0.9`, any other major | **Error** `E_VERSION_MAJOR`. |
| `"1"`, `"x"`, `"1.0.0"`, `"01.0"`, a number | **Error** `E_VERSION_FORMAT` (or `E_TYPE` for a non-string). |

## Errors and warnings

Reading a scene (`contract::parseScene`) never throws. It returns the scene, or a list of issues,
each with a stable **code**, the **JSON path** of the offending value (e.g.
`room.surfaces.floor.absorption[3]`) and a human-readable **message**. A scene with only warnings
loads. Codes are part of the API: they never change meaning and are never renumbered (list in
[`src/contract/Diagnostics.h`](../../src/contract/Diagnostics.h)).

| Code | Meaning |
|---|---|
| `E_JSON_SYNTAX` | The text is not valid JSON. |
| `E_TYPE` | A value has the wrong JSON type (e.g. a string where numbers are expected). |
| `E_MISSING_FIELD` | A required field is missing. |
| `E_UNKNOWN_FIELD` | A field isn't part of the contract at this minor version. |
| `E_ARRAY_LENGTH` | An array has the wrong number of elements (3 for positions, 8 for absorption). |
| `E_VERSION_FORMAT` | `contractVersion` isn't `"MAJOR.MINOR"`. |
| `E_VERSION_MAJOR` | `contractVersion` has a major version this build can't read. |
| `W_VERSION_MINOR_NEWER` | *Warning:* a newer minor version; unknown fields were ignored. |
| `E_UNITS` | `units` isn't `"meters"`. |
| `E_GEOMETRY_KIND` | `room.geometry.kind` isn't `"shoebox"`. |
| `E_ROOM_DIMENSION_RANGE` | A room dimension is outside [1.5, 100] m. |
| `E_ABSORPTION_RANGE` | An absorption coefficient is outside [0.01, 1.0]. |
| `E_SCATTERING_RANGE` | A scattering coefficient is outside [0, 1]. |
| `E_LISTENER_SURFACE_CLEARANCE` | The listener isn't inside the room 0.1 m clear of every surface. |
| `E_EMITTER_COUNT` | There aren't exactly two emitters. |
| `E_EMITTER_ID` | An emitter id isn't `"L"` or `"R"`, or is used twice. |
| `E_EMITTER_CHANNEL` | An emitter channel isn't 0 or 1, or is used twice. |
| `E_GAIN_RANGE` | An emitter `gainDb` is outside [−60, +12]. |
| `E_EMITTER_SURFACE_CLEARANCE` | An emitter isn't inside the room 0.1 m clear of every surface. |
| `E_EMITTER_TOO_CLOSE_TO_LISTENER` | An emitter is less than 0.3 m from the listener. |
| `E_OUTPUT_MODE` | `render.outputMode` isn't `"binaural"` or `"stereoSpeakers"`. |
| `E_HRTF_ID` | `render.hrtfId` isn't a supported head model. |
| `E_REFLECTION_ORDER_RANGE` | `render.maxReflectionOrder` is outside [0, 60]. |
| `E_TAIL_SEED_RANGE` | `render.tailSeed` isn't an unsigned 32-bit integer. |
| `E_EXTENSIONS` | In-memory scenes only: `extensionsJson` isn't the text of a JSON object. |
| `E_INTERNAL` | Unexpected internal failure (e.g. out of memory). Never caused by the document. |

One mistake gives one issue: when the room size is invalid the positions aren't checked against
it, when the emitter count is wrong the L/R and 0/1 set rules aren't checked, and the distance to
the listener is checked only when both positions are inside the room. Independent mistakes are all
reported.

### What the JSON Schema covers

[`scene-v1.schema.json`](scene-v1.schema.json) (JSON Schema draft 2020-12) expresses types,
required and unknown fields, ranges, array lengths, enums and the emitter count and uniqueness.
The **geometric rules** (inside the room with 0.1 m clearance, 0.3 m from the listener) exist only in
the C++ validator. The schema describes 1.0 documents strictly and doesn't model the
"newer minor loads with a warning" rule. `tools/ci/test_schema_agreement.py` checks in CI that
schema and C++ agree on every fixture; `tests/scenes/invalid/_cppOnly.json` lists the fixtures
whose rule only C++ can check.

## Using it from code

```cpp
#include "contract/Parse.h"     // parseScene: read + validate, never throws
#include "contract/Json.h"      // toJson, fromJson (structure only)
#include "contract/Validate.h"  // validate an in-memory scene, limits::

const contract::ParseResult result = contract::parseScene(text);
if (!result.ok())
    for (const contract::Issue& issue : result.issues)
        log(contract::toString(issue)); // "E_GAIN_RANGE at emitters[0].gainDb: gainDb must be ..."
```

The 3D Module builds a `contract::SceneDescription` in memory and calls `contract::validate` on it
before handing it over. `src/sim` and `src/module3d` never include each other; only
`contract::SceneDescription` crosses (enforced by `tools/ci/check_boundaries.py`).

## Changing the contract

A change to the contract always means: bump `contractVersion` (minor for additive changes, major for
breaking ones), update `docs/contract/scene-v1.schema.json` and `docs/contract/README.md`, add
fixtures, and add a migration test if the change breaks anything. No exceptions.

In this code base that also means: update `kContractVersionMinor`/`kContractVersionMajor` in
`src/contract/Version.h`, the reader and writer in `src/contract/Json.cpp`, the rules in
`src/contract/Validate.cpp`, and add new issue codes at the end of the list in
`src/contract/Diagnostics.h`. Don't add fields that no phase uses yet.

## Version history

| Version | Date | Change | Phase |
|---|---|---|---|
| 1.0 | 2026-11-04 | First version: shoebox room, 6 surfaces with 8-band absorption and scattering, one listener, two emitters L/R, render settings, extensions. | 01 |
