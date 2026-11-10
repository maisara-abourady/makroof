# Phase 11 — Minimal placement UI

Size: **M** · Depends on: 07, 09 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ3, AX2, AX3, AX6, AX7, AX34), PRD "Overview & vision", FR-3D-1 (deferred in full), FR-3D-4, FR-3D-5, FR-3D-8

## Goal

A small, usable editor: the user sees the room, drags the listener and the L/R emitters, sets room size
and surface materials, and picks the output mode. It doesn't need a single acoustic term, matching the
PRD's vision. It is **not** the full 3D editor (deferred, B8).

## Assumptions in force

- **AX7**: one listener and two emitters. **AX3**: the listener's facing direction is derived, so the UI
  shows it as an arrow but can't edit it.
- **AQ3**: materials are chosen from a list. The advanced view exposes per-band α and scattering.
- **AX44** (phase 05b): the "approximate" note U (`TailMatch.approximate`, per emitter) and its text rules;
  **AX38**: the diffuse-solve gate and the "settling" state; **AX39**: Seat 7's allowed and forbidden
  wording for accuracy claims.

## Scope

1. `src/plugin/ui/` (JUCE components, message thread only):
   - **Top view** (x/y plane) and **side view** (y/z plane) of the room, drawn to scale with a metre grid.
     The listener is a head icon with a facing arrow; L and R emitters are labelled speaker icons.
   - **Dragging** an icon writes host parameters with proper `beginChangeGesture`/`endChangeGesture`,
     so DAW automation recording works (FR-3D-8). Positions are clamped to valid space with the same rules
     as `module3d::SceneModel`. Show the minimum-distance ring around the listener while dragging.
   - **Room panel:** W/D/H numeric fields with sliders (metres).
   - **Surfaces panel:** for each of the 6 surfaces, a material dropdown (list from `resources/materials.json`
     if Phase 12 is done, otherwise a placeholder list of 6 materials defined in `module3d`) and an
     "Advanced" disclosure with a per-band α table plus scattering, validated live (AQ3 ranges).
     Material edits aren't host parameters (too many). They're stored in the scene state and count as
     undoable edits (JUCE `UndoManager`).
   - **Output panel:** binaural / stereo speakers toggle with one line of explanatory text each
     ("for headphones" / "for a pair of speakers"), output trim.
   - **Status strip:** reported latency (ms), CPU estimate, the room's derived T60 at 500 Hz and 1 kHz
     (from `sim` via the contract: expose `sim::describeScene(const SceneDescription&)` returning summary
     numbers, so the UI never reaches into sim internals), and a warning badge if state failed to load (Phase 07).
     The nominal Eyring T60 is not shown as an open field's reverb time (AX38 4c hand-off, Seat 6).
2. **Model/view separation:** the UI talks only to `module3d::SceneModel` + APVTS through a small
   `EditorController` that's testable without rendering. The controller is the only place that converts
   between pixels and metres.
3. Resizable editor with a fixed aspect ratio, minimum 800×500, HiDPI-correct. Remember the size in state.
4. Remove the generic editor.
5. **Room-resize gesture** that keeps absolute listener and emitter positions by rewriting the position
   parameters (automation of `room_*` still scales them; Phase 07 D2).
6. **"Output above 0 dB" indicator:** display only, no auto-gain (AX2; Phase 07 D4).
7. Show the **AX34 unsupported-rate warning flag** with the supported rates listed (Phase 07 D8).
8. **"Approximate" note** (AX44, phase 05b): shown from `TailMatch.approximate` on the **settled** scene
   only, in the info view, never mid-drag; wording by Seats 6 and 7 (within AX39's wording rules). Text
   (Seat 6 (i)): both-near branch: no ±x from the achieved SE; either the measured replicate p95 of its
   case class from the phase-05b C++ reported set, or qualitative text ("level unreliable with source and
   listener this close to surfaces; move either about 0.7 m away"); capped branch: ±x from the achieved SE
   only for classes whose reported set shows SE ≥ the replicate SD, otherwise the class p95 or
   qualitative text. When U is raised on an emitter the user did not edit, the note names the scene, not
   that emitter, as the cause. **U′** (cap hit OR both-near, Seat 6 (iii)) appears only as a labelled
   diagnostic tier in an advanced view.
9. **"Settling" state** (AX38 (iii)): shown on every instance waiting at the diffuse-solve gate, project
   load included.

## Out of scope

3D viewport, scene import, objects inside the room, dispersion settings, presets browser (Phase 12 adds it).

## Acceptance criteria — automated

- [ ] `EditorController` tests (headless): a simulated drag from pixel A to B sets the expected parameter
      values (±1e-4 normalized) in top and side views; clamping matches `SceneModel`; gestures begin and
      end exactly once per drag.
- [ ] Editing α to an out-of-range value is rejected with the validator's error message, and the scene
      stays valid.
- [ ] Undo/redo of material edits restores identical scene JSON.
- [ ] **Snapshot test:** the editor renders to an offscreen `juce::Image` at 800×500, 1200×750 and
      1600×1000 without assertions, and the image isn't blank. (Pixel-exact comparison isn't required
      because fonts differ across OSes.)
- [ ] A thread-assertion test: any scene mutation off the message thread trips a debug assertion (test
      it with a deliberate violation in a death-test-style subprocess or a mocked assert handler).
- [ ] pluginval strictness 10 with editor tests enabled passes on 3 OSes (Linux under `xvfb-run`).
- [ ] State round trip still bit-identical; editor size is restored.

## Listening / use checklist (Maisara)

In Logic, Ableton/Reaper (macOS) and a Windows DAW:
- [ ] Open the editor: the room, listener and two speakers are visible and make sense without explanation.
- [ ] Drag the speakers while the track plays: the sound follows smoothly.
- [ ] Arm automation write, drag the listener around, and play back: the same movement plays.
- [ ] Change the floor to carpet and the walls to concrete: audible change; undo returns the previous sound.
- [ ] Resize the window; check it on a HiDPI/Retina screen and at Windows 150% scaling.
- [ ] Save, reopen the project: same layout, same sound, same window size.
- [ ] Write down anything confusing. This is the first time the product's *user* side is exercised.

## Contractor review focus

Gesture handling with each host's automation modes, message-thread discipline, pixel↔metre mapping
accuracy, and that no UI code includes `src/sim` headers except via `sim::describeScene`.

## Risks

Scope creep toward a 3D editor; host-specific DPI and resizing quirks on Windows.

## Definition of done

All automated criteria green; status row 11 `done`; use checklist in the PR.
