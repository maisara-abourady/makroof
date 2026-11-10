# Split map — Phase 11 (Minimal placement UI)

Source: `docs/phases/phase-11.md` (size **M**, depends on 07, 09). Drafted per
`docs/review/phase-split/0-drafting-brief.md`; pure reallocation, nothing changed in substance.

**Outcome: split into three sub-phases, 11-1 → 11-2 → 11-3** (a linear chain). The original row stays in
§0 as the umbrella `11`, status `split (11-1…11-3)`.

Item labels used below (the phase file numbers its scope items but not its criteria, so the rest are
numbered here in file order):
- **H** header line (size M, depends on 07, 09, read-first list); **G** goal; **OS** out of scope.
- **AS1** AX7 + AX3 (one listener, two emitters; facing arrow shown, not editable); **AS2** AQ3 (materials
  from a list; advanced per-band α and scattering); **AS3** AX44 (note U and its text rules), AX38 (gate
  and "settling" state), AX39 (Seat 7's accuracy wording).
- **S1** scope 1 lead-in ("`src/plugin/ui/` (JUCE components, message thread only)") with its bullets
  **S1a** top/side views, **S1b** dragging (gestures, `SceneModel` clamping, minimum-distance ring),
  **S1c** room panel, **S1d** surfaces panel (dropdown, placeholder list, Advanced α/s table validated
  live, material edits in scene state and undoable via `UndoManager`), **S1e** output panel, **S1f**
  status strip (latency, CPU, T60 at 500 Hz / 1 kHz via `sim::describeScene`, state-load warning badge;
  nominal Eyring T60 not shown as an open field's reverb time). **S2**–**S9** scope items 2–9.
- **A1** `EditorController` drag/clamp/gesture tests; **A2** out-of-range α rejected with the validator's
  message, scene stays valid; **A3** undo/redo of material edits restores identical scene JSON; **A4**
  snapshot test at 800×500, 1200×750, 1600×1000; **A5** thread-assertion test; **A6** pluginval strictness
  10 with editor tests on 3 OSes; **A7** state round trip still bit-identical; editor size is restored.
- **L1**–**L7** listening/use checklist items in order.
- **C1** contractor review focus, clauses **C1a** gesture handling with each host's automation modes,
  **C1b** message-thread discipline, **C1c** pixel↔metre mapping accuracy, **C1d** no UI code includes
  `src/sim` headers except via `sim::describeScene`.
- **R1** scope creep toward a 3D editor; **R2** host-specific DPI and resizing quirks on Windows.
- **D1**–**D3** definition of done (all automated criteria green; status row `done`; use checklist in
  the PR).

The phase has no "Raise with Maisara" section and no "settled" / "decisions before implementation"
section.

## 1. Sub-phase table

| id | title | lead subject matter | size | depends on | what it ships | automated criteria owned |
|---|---|---|---|---|---|---|
| 11-1 | Editor shell, output panel and status readouts | **Seat 5 Deadline keeper** — "anything on or beside the audio thread: … threading topology; host conformance (pluginval, auval, state, automation, undo, buses, latency); … platform transitions" | M | 07, 09 (the phase's recorded dependencies) | The custom editor replaces the generic one: resizable, fixed aspect, ≥ 800×500, HiDPI-correct, size remembered in state; output-mode toggle and trim; status strip (latency, CPU, T60 via `sim::describeScene`, state-load badge); "output above 0 dB" indicator; AX34 rate warning; message-thread discipline asserted | A4, A5, A6, A7 |
| 11-2 | Placement canvas: views, drags, room size | **Seat 6 Canvas designer** — "anything user-facing: … canvas metaphor and interaction; … automation and motion model; DAW workflow; time-to-first-plausible-scene" | M | 11-1 (and through it 07, 09) | `EditorController` (the only pixel↔metre converter, headless-testable); top and side views to scale with the metre grid, listener head with facing arrow, labelled L/R speakers; drags with one gesture each, `SceneModel` clamping and the minimum-distance ring; room W/D/H panel; the room-resize gesture that keeps absolute positions | A1 |
| 11-3 | Surfaces panel and engine-state notes | **Seat 6 Canvas designer** — "which controls exist and which stay hidden; names, ranges, defaults, …" | M | 11-2 (and through it 11-1, 07, 09) | Per-surface material dropdown (placeholder list in `module3d`, or `materials.json` if Phase 12 is done) with the Advanced per-band α / scattering table validated live and undoable material edits in scene state; the "approximate" note U on the settled scene (and the U′ advanced diagnostic tier); the "settling" state | A2, A3 |

Shared rules (umbrella): every sub-phase keeps A4–A7 green once 11-1 has made them pass (main stays green;
a later sub-phase that adds components renders inside the A4 snapshot and the A6 pluginval run), and every
sub-phase's UI code stays on the message thread (S1 lead-in, C1b).

### Why these cuts

- **11-1 is the host-facing shell.** Its four criteria are all host conformance and platform behaviour
  (offscreen rendering at three sizes, the thread assertion, pluginval with the editor on three OSes, state
  with editor size), and it retires R2 (Windows DPI and resizing) first. The readouts that ride with it
  (S1e, S1f, S6, S7) are displays of values Phase 07 already exposes (`stateWarning()`,
  `unsupportedRateWarning()`, reported latency, `output_mode`) plus the `describeScene` seam (C1d); they
  give the shell content for A4 ("the image isn't blank") without needing the canvas. Their wording is
  fixed in the phase file.
- **11-2 is the canvas.** One subject (the placement metaphor and its automation gestures), one criterion
  (A1) with three clauses, R1's main exposure, and C1a/C1c. S5 (room-resize gesture) belongs here because
  it rewrites the position parameters that the drags write.
- **11-3 is the remaining controls and notes.** S1d is the first non-parameter, undoable scene edit
  (`UndoManager`, scene state, live AQ3 validation; A2, A3), distinct from the host-parameter drags of
  11-2. S8 and S9 come last because they read engine state that Phase 05h's gate and estimator provide
  (see CHOICE 11-c3) and because S8's "never mid-drag" and "an emitter the user did not edit" presuppose
  11-2's drags.
- **Not split further.** A sub-phase for S8 + S9 alone would own no existing automated criterion (G2), so
  it is merged with S1d. A sub-phase for S1c + S5 alone would own no criterion either (A1 tests drags),
  so it stays in 11-2.
- **Sizes.** Each sub-phase is M, inside one session; none approaches the two-session limit (see
  CHOICE 11-c2 for the aggregate). A sub-phase that does not finish in two sessions uses `11-<n>b` (G3).

## 2. Order and rationale

Order 11-1 → 11-2 → 11-3. 11-1 must come first in any cut where scope 4 (remove the generic editor) and
scope 3 (the editor shell) are delivered once: the views of 11-2 and the panels of 11-3 need an editor to
live in, and A4/A6/A7 test that editor. 11-2 precedes 11-3 because S8's rules refer to drags and to
emitters the user did or did not edit.

- **CHOICE 11-c1 — order: shell first vs. canvas first (what ships first).**
  Options: (a) the three-way split above, shell (11-1) first: retires R2 (DPI, pluginval with the editor
  on three OSes) first; in the interval between 11-1 and 11-2 the generic editor is gone and positions are
  set only through the host's own parameter views and automation lanes (every parameter remains a host
  parameter, so nothing becomes unreachable); (b) a two-way split, canvas first: 11-1 = S1a–S1c, S2–S5
  (A1, A4, A6, A7; L), 11-2 = S1d–S1f, S6–S9 (A2, A3, A5; M): the first sub-phase ships the draggable
  placement the phase's goal leads with, but is L and mixes Seat 5's host-conformance criteria with
  Seat 6's canvas; (c) keep Phase 11 whole (M). **Recommended (a)**: each sub-phase has one lead subject
  matter and is M; the interval in (a) loses no reachable control. Because (a) changes what ships first
  (the shell before the placement canvas) and which risk is retired first (R2 before R1), it is a
  decision by G1, for the loop.
- **CHOICE 11-c2 — aggregate size.** The phase file says M (one session). Split, it becomes three M
  sub-phases (three sessions). No single sub-phase crosses the two-session limit, but the umbrella as a
  whole now spans more than two sessions. Options: (a) accept three M sub-phases; (b) the two-way split of
  11-c1 (b) (L + M); (c) keep whole. **Recommended (a)**, same reason as 11-c1; flagged because G1 counts
  a size change across the two-session limit as a decision, and this one is ambiguous (per sub-phase no,
  per umbrella yes).
- **CHOICE 11-c3 — S8/S9 and Phase 05h (dependency not recorded in the phase file).** S8 draws its text
  from "the measured replicate p95 of its case class from the phase-05h C++ reported set" and the
  `TailMatch.approximate` flag; S9 shows the wait at the AX38 diffuse-solve gate. Both are delivered by
  Phase 05h (BUILD_PLAN §0 row 05h: estimator, gate; `in progress`), but phase-11 "Depends on" lists only
  07, 09. This map moves no dependency and adds none: 11-3 carries 07, 09 through the chain, exactly as the
  phase file does. Options: (a) leave the recorded dependencies as they are (11-3 depends on 11-2; the
  executing session checks 05h at its step 3 as it would today); (b) record 05h as a dependency of 11-3
  only; (c) record 05h for the whole umbrella. **Recommended (a)** for this draft (a split adds no
  dependency); (b) would be the narrower correction if the decider finds the dependency is real. Placing
  S8 and S9 in the last sub-phase keeps 11-1 and 11-2 free of 05h under every option.

No other CHOICE. Phase 12 depends on the umbrella `11` (all sub-phases, G3); since 11-3 is last in the
chain and holds the surfaces panel that Phase 12's library feeds, narrowing that dependency to "11-3"
would be equivalent, so it is not a choice.

## 3. Coverage table

| original item | goes to |
|---|---|
| H Header: size M, depends on 07, 09, read-first list (AQ3, AX2, AX3, AX6, AX7, AX34; PRD vision, FR-3D-1/4/5/8) | umbrella; each sub-phase's own size/depends line (11-1: AX2, AX6, AX34, FR-3D-5; 11-2: AX3, AX6, AX7, FR-3D-4, FR-3D-8; 11-3: AQ3, AX6; all: PRD vision, FR-3D-1 deferred) — shared |
| G Goal | umbrella (shared; each sub-phase states its share: 11-1 output mode; 11-2 sees the room, drags, room size; 11-3 surface materials) |
| AS1 AX7, AX3 | umbrella (shared) + 11-2 |
| AS2 AQ3 | 11-3 |
| AS3 AX44, AX38, AX39 | umbrella (shared) + 11-3 (AX38's T60 hand-off clause, inside S1f, is applied in 11-1) |
| S1 lead-in "`src/plugin/ui/` (JUCE components, message thread only)" | umbrella (shared) + 11-1 |
| S1a Top and side views, metre grid, head icon with facing arrow, labelled L/R speakers | 11-2 |
| S1b Dragging: gestures (FR-3D-8), `SceneModel` clamping, minimum-distance ring | 11-2 |
| S1c Room panel W/D/H fields with sliders | 11-2 |
| S1d Surfaces panel: dropdown (materials.json if Phase 12 done, else placeholder 6 in `module3d`), Advanced α/s table validated live (AQ3), material edits in scene state, undoable (`UndoManager`) | 11-3 |
| S1e Output panel: binaural / stereo speakers toggle with its two text lines, output trim | 11-1 |
| S1f Status strip: latency, CPU, T60 at 500 Hz and 1 kHz via `sim::describeScene`, state-load warning badge; nominal Eyring T60 not shown as an open field's reverb time (AX38 4c, Seat 6) | 11-1 |
| S2 Model/view separation, `EditorController`, only pixel↔metre converter | 11-2 |
| S3 Resizable editor, fixed aspect, min 800×500, HiDPI, size in state | 11-1 |
| S4 Remove the generic editor | 11-1 |
| S5 Room-resize gesture keeping absolute positions (Phase 07 D2) | 11-2 |
| S6 "Output above 0 dB" indicator, display only (AX2; Phase 07 D4) | 11-1 |
| S7 AX34 unsupported-rate warning flag with supported rates (Phase 07 D8) | 11-1 |
| S8 "Approximate" note U (settled scene, info view, never mid-drag; Seat 6 (i) text branches; scene named as cause; U′ advanced tier; reaches the producer's editor, decider file 51) | 11-3 |
| S9 "Settling" state (AX38 (iii)), every instance at the gate, project load included | 11-3 |
| OS Out of scope (3D viewport, scene import, objects, dispersion, presets browser) | umbrella (shared; governs all three) |
| A1 `EditorController` tests (drag A→B ±1e-4 normalized in top and side views; clamping matches `SceneModel`; gestures begin and end exactly once per drag) | 11-2 |
| A2 Out-of-range α rejected with the validator's error message; scene stays valid | 11-3 |
| A3 Undo/redo of material edits restores identical scene JSON | 11-3 |
| A4 Snapshot test at 800×500, 1200×750, 1600×1000, no assertions, not blank | 11-1 (kept green by 11-2, 11-3: umbrella shared rule) |
| A5 Thread-assertion test (scene mutation off the message thread trips a debug assertion) | 11-1 (kept green by 11-2, 11-3) |
| A6 pluginval strictness 10 with editor tests, 3 OSes (Linux under `xvfb-run`) | 11-1 (kept green by 11-2, 11-3) |
| A7 State round trip still bit-identical; editor size is restored | 11-1 (kept green by 11-2, 11-3) |
| L-intro "In Logic, Ableton/Reaper (macOS) and a Windows DAW" | umbrella (shared; applies to each sub-phase's items) |
| L1 Open the editor: room, listener, two speakers visible and make sense | 11-2 |
| L2 Drag the speakers while playing: sound follows smoothly | 11-2 |
| L3 Automation write of a listener drag plays back the same movement | 11-2 |
| L4 Floor carpet, walls concrete: audible change; undo returns the previous sound | 11-3 |
| L5 Resize; HiDPI/Retina; Windows 150 % scaling | 11-1 |
| L6 Save, reopen: same layout, same sound, same window size | 11-3 (the full check needs layout and materials; the window-size clause is first testable after 11-1, covered there by A7) |
| L7 Write down anything confusing | umbrella (shared) + 11-3 |
| C1a Gesture handling with each host's automation modes | 11-2 |
| C1b Message-thread discipline | umbrella (shared) + 11-1 |
| C1c Pixel↔metre mapping accuracy | 11-2 |
| C1d No UI code includes `src/sim` headers except via `sim::describeScene` | 11-1 |
| R1 Scope creep toward a 3D editor | umbrella (shared) + 11-2 |
| R2 Host-specific DPI and resizing quirks on Windows | 11-1 |
| D1 All automated criteria green | each sub-phase for its own criteria; umbrella `done` when all are (shared) |
| D2 Status row 11 `done` | each sub-phase row `done`; umbrella row 11 `done` when 11-1…11-3 are (G3) (shared) |
| D3 Use checklist in the PR | each sub-phase PR carries its L-items (shared) |
| Raise with Maisara | none in the file |
| Settled / decisions before implementation | none in the file |

Nothing unassigned; shared items are marked.

## 4. References

Grep of the repo (excluding `docs/corpus`, `docs/review`, `docs/sessions`, `.git`, and the phase file
itself) for `Phase 11` / `phase-11` / `phase 11`, plus the Phase 11 summary and dependency lines.

| file:line | reference | → |
|---|---|---|
| `src/plugin/PluginProcessor.h:69` | "Warning flags (shown by the UI from Phase 11)": state warning, unsupported rate | 11-1 (S1f badge, S7) |
| `src/plugin/PluginProcessor.cpp:214` | "The generic editor is enough until Phase 11." | 11-1 (S4) |
| `docs/BUILD_PLAN.md:36` | §0 status row 11 | umbrella `split (11-1…11-3)` |
| `docs/BUILD_PLAN.md:134` | AX34 "the warning flag is set (shown in Phase 11)" | 11-1 (S7) |
| `docs/BUILD_PLAN.md:138` | AX38 hand-offs: "the 'settling' state and stepwise room-size automation at large rooms (Phase 10, Phase 11)"; "the nominal Eyring T60 is not shown as an open field's reverb time (Phase 11)" | settling → 11-3 (S9); room-size → 11-2 (S1c/S5); Eyring T60 → 11-1 (S1f) |
| `docs/BUILD_PLAN.md:144` | AX44 note text "Phase 11 shows it on the settled scene only …"; "U′ … in a Phase 11 advanced view" | 11-3 (S8) |
| `docs/BUILD_PLAN.md:324-331` | "### Phase 11 — Minimal placement UI · M" summary (scope, deps 07, 09, acceptance, 05b items, risks) | umbrella (items as in §3: views/drags/room fields → 11-2; materials/α table → 11-3; output mode, latency/CPU → 11-1; headless binding tests → 11-2; snapshot, pluginval, thread assertion → 11-1; 05b items → 11-3 except the Eyring T60 → 11-1) |
| `docs/BUILD_PLAN.md:337` | Phase 12 "Dependencies: 01, 11" | umbrella (all sub-phases, G3) |
| `docs/BUILD_PLAN.md:434` | §6 2026-11-08 "Follow-ups: … phase-11 scope 5–7" | scope 5 → 11-2; scope 6, 7 → 11-1 |
| `docs/BUILD_PLAN.md:438` | §6 2026-11-09 D1 row "Phase 11 tooltip note" | 11-1 (S1e output-mode text) |
| `docs/BUILD_PLAN.md:446` | §6 2026-11-10 "phase-11 (U's note reaches the producer's editor)" | 11-3 (S8) |
| `docs/phases/phase-07.md:54` | "A UI resize that keeps absolute positions is a Phase 11 gesture" | 11-2 (S5) |
| `docs/phases/phase-07.md:225` | "a visible warning flag (shown by the UI in Phase 11)" | 11-1 (S1f badge) |
| `docs/contract/README.md:249` | "A UI resize that keeps absolute positions is a Phase 11 gesture" | 11-2 (S5) |
| `docs/phases/phase-08.md:302` | "Hand-off to Phase 11 (Seat 6): … output-mode tooltip or manual, a default-experience note" | 11-1 (S1e) |
| `docs/phases/phase-09.md:75` | Risk: "Set expectations in UI text in Phase 11" (binaural height/depth on speakers) | 11-1 (S1e) |
| `docs/phases/phase-10.md:56` | "the same wait drives Phase 11's 'settling' state" | 11-3 (S9) |
| `docs/phases/phase-12.md:3` | "Depends on: 01, 11" | umbrella (all sub-phases, G3) |
| `docs/phases/phase-13.md:3` | "Depends on: 00–12" (range includes 11) | umbrella |
| `.claude/skills/review-phase-pr/references/phase-checklists.md:313-328` | "## Phase 11 — Minimal placement UI" checklist (Must contain / Verify / Traps) | umbrella; per clause: views, drag, room panel, `EditorController`, drag/clamp/gesture verify, gesture trap → 11-2; surfaces panel, α/undo verify, material-edits trap → 11-3; output panel, status strip, `describeScene`, resizable editor, generic editor removed, snapshot, thread assertion, pluginval, state verify, sim-header / DPI / off-thread traps → 11-1 |
