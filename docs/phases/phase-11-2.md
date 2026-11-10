# Phase 11-2 — Placement canvas: views, drags, room size

Size: **M** (remainder, if needed: `11-2b`) · Depends on: 11-1 (and through it 07, 09) · Part of: [phase-11](phase-11.md) · Lead subject matter: Seat 6 (Canvas designer), "anything user-facing: … canvas metaphor and interaction; … automation and motion model; DAW workflow; time-to-first-plausible-scene" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AX3, AX6, AX7), PRD "Overview & vision", FR-3D-1 (deferred in full), FR-3D-4, FR-3D-8, and the umbrella [phase-11](phase-11.md)

## Goal

This sub-phase's share of the umbrella goal ("A small, usable editor: the user sees the room, drags the listener and
the L/R emitters, sets room size …"): the user sees the room, drags the listener and the L/R emitters, and sets room
size. It is **not** the full 3D editor (deferred, B8).

## Assumptions in force

- **AX7**: one listener and two emitters. **AX3**: the listener's facing direction is derived, so the UI
  shows it as an arrow but can't edit it. (phase-11 Assumptions, AX7 and AX3; shared with the umbrella)
- And all of the umbrella's.

## Scope

Inside the umbrella's `src/plugin/ui/` (JUCE components, message thread only) (phase-11 scope 1, lead-in):
1. **Top view** (x/y plane) and **side view** (y/z plane) of the room, drawn to scale with a metre grid.
   The listener is a head icon with a facing arrow; L and R emitters are labelled speaker icons. (phase-11 scope 1a)
2. **Dragging** an icon writes host parameters with proper `beginChangeGesture`/`endChangeGesture`,
   so DAW automation recording works (FR-3D-8). Positions are clamped to valid space with the same rules
   as `module3d::SceneModel`. Show the minimum-distance ring around the listener while dragging. (phase-11 scope 1b)
3. **Room panel:** W/D/H numeric fields with sliders (metres). (phase-11 scope 1c)
4. **Model/view separation:** the UI talks only to `module3d::SceneModel` + APVTS through a small
   `EditorController` that's testable without rendering. The controller is the only place that converts
   between pixels and metres. (phase-11 scope 2)
5. **Room-resize gesture** that keeps absolute listener and emitter positions by rewriting the position
   parameters (automation of `room_*` still scales them; Phase 07 D2). (phase-11 scope 5)

## Out of scope

The umbrella's (phase-11 Out of scope). Also the work of the other sub-phases: the editor shell, output panel, status
strip and indicators (phase-11 scope 1e, 1f, 3, 4, 6, 7; in 11-1); the surfaces panel, the "approximate" note and the
"settling" state (phase-11 scope 1d, 8, 9; in 11-3).

## Acceptance criteria — automated

- [ ] `EditorController` tests (headless): a simulated drag from pixel A to B sets the expected parameter
      values (±1e-4 normalized) in top and side views; clamping matches `SceneModel`; gestures begin and
      end exactly once per drag. (phase-11 A1)
- [ ] phase-11 A4–A7 stay green with the views added (umbrella shared rule).

## Listening / manual checklist

Hosts: as the umbrella's (phase-11 L-intro).
- [ ] Open the editor: the room, listener and two speakers are visible and make sense without explanation. (phase-11 L1)
- [ ] Drag the speakers while the track plays: the sound follows smoothly. (phase-11 L2)
- [ ] Arm automation write, drag the listener around, and play back: the same movement plays. (phase-11 L3)

## Contractor review focus

Gesture handling with each host's automation modes (phase-11 C1a), pixel↔metre mapping accuracy (phase-11 C1c).

## Risks

Scope creep toward a 3D editor. (phase-11 R1; shared with the umbrella)

## Notes from the split

- D-PS3 (`docs/review/phase-split/3-decider-decision.md`, step 2; Seat 6 condition (i)): 11-1's aspect ratio and region
  layout are provisional, set in 11-2 once the two scale views exist; 11-1 reserves the canvas region as the largest
  region.
- D-PS3 debt register (Seat 6): layout set before the canvas exists; undo cost: a constant + re-layout; A4, A6 re-run;
  evidence: 11-2's L1; repaid when: layout confirmed in 11-2. (Seat 7: canvas ~1 session later; repaid when 11-2
  `done`.)

## Definition of done

- All automated criteria above green (phase-11 D1, this sub-phase's share); status row 11-2 `done` (phase-11 D2); use
  checklist in the PR (phase-11 D3).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-11-2b.md`.
