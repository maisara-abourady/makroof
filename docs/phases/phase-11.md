# Phase 11 — Minimal placement UI

Size: **split into 11-1…11-3** · Depends on: 07, 09 · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ3, AX2, AX3, AX6, AX7, AX34), PRD "Overview & vision", FR-3D-1 (deferred in full), FR-3D-4, FR-3D-5, FR-3D-8

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

## Sub-phases

Status: the umbrella is `done` when every sub-phase is. A dependency on phase 11 means all of its sub-phases unless a
sub-phase is named.

| id | title | lead seat | size | depends on | ships | owns |
|---|---|---|---|---|---|---|
| [11-1](phase-11-1.md) | Editor shell, output panel and status readouts | Seat 5 (Deadline keeper) | M | 07, 09 | the custom editor replaces the generic one (resizable, fixed aspect, ≥ 800×500, HiDPI, size in state); output panel; status strip; "output above 0 dB" indicator; AX34 rate warning; message-thread discipline asserted | A4, A5, A6, A7 |
| [11-2](phase-11-2.md) | Placement canvas: views, drags, room size | Seat 6 (Canvas designer) | M | 11-1 | `EditorController`; top and side views; drags with gestures, clamping and the minimum-distance ring; room panel; room-resize gesture | A1 |
| [11-3](phase-11-3.md) | Surfaces panel and engine-state notes | Seat 6 (Canvas designer) | M | 11-2 | surfaces panel with live-validated Advanced α/scattering and undoable material edits; the "approximate" note U (and U′); the "settling" state | A2, A3 |

Order 11-1 → 11-2 → 11-3 (D-PS3, `docs/review/phase-split/3-decider-decision.md`; stands in
`5-decider-decision-r2.md`).

## Scope shared by every sub-phase

1. `src/plugin/ui/` (JUCE components, message thread only): (phase-11 scope 1, lead-in; also in 11-1; its bullets are
   in 11-1, 11-2 and 11-3, see below)

Shared rule (map-11 §1): every sub-phase keeps A4–A7 green once 11-1 has made them pass (main stays green; a later
sub-phase that adds components renders inside the A4 snapshot and the A6 pluginval run), and every sub-phase's UI code
stays on the message thread (scope 1 lead-in, C1b).

## Out of scope

3D viewport, scene import, objects inside the room, dispersion settings, presets browser (Phase 12 adds it).

## Listening / use checklist (Maisara)

In Logic, Ableton/Reaper (macOS) and a Windows DAW: (phase-11 L-intro; applies to every sub-phase's items)
- [ ] Write down anything confusing. This is the first time the product's *user* side is exercised. (phase-11 L7;
      also in 11-3)

## Contractor review focus

Message-thread discipline (phase-11 C1b; also in 11-1). The other clauses are in 11-1 (C1d) and 11-2 (C1a, C1c).

## Risks

Scope creep toward a 3D editor (phase-11 R1; also in 11-2). Host-specific DPI and resizing quirks on Windows are in
11-1 (R2).

## Definition of done

All automated criteria green; status row 11 `done`; use checklist in the PR. (phase-11 D1–D3: each sub-phase for its
own criteria, its own status row and its own checklist items; row 11 is `done` when 11-1…11-3 are.)

## Where the original items went

Labels as in `docs/review/phase-split/map-11.md`. "Scope n" is the original scope numbering (scope 1's bullets are 1a
top/side views, 1b dragging, 1c room panel, 1d surfaces panel, 1e output panel, 1f status strip); A1–A7 are the
automated criteria, L1–L7 the use checklist items, C1a–C1d the contractor-focus clauses and R1–R2 the risks, in file
order.

| original item | goes to |
|---|---|
| Header (size, depends on 07, 09, read-first list) | umbrella; each sub-phase's header carries its share (shared) |
| Goal | umbrella; each sub-phase states its share (shared) |
| Assumptions: AX7, AX3 | umbrella + 11-2 (shared) |
| Assumptions: AQ3 | umbrella + 11-3 (shared) |
| Assumptions: AX44, AX38, AX39 | umbrella + 11-3 (shared; AX38's 4c hand-off inside scope 1f is applied in 11-1) |
| scope 1 lead-in (`src/plugin/ui/`, message thread only) | umbrella + 11-1 (shared) |
| scope 1a top and side views | 11-2 |
| scope 1b dragging | 11-2 |
| scope 1c room panel | 11-2 |
| scope 1d surfaces panel | 11-3 |
| scope 1e output panel | 11-1 |
| scope 1f status strip | 11-1 |
| scope 2 model/view separation, `EditorController` | 11-2 |
| scope 3 resizable editor | 11-1 |
| scope 4 remove the generic editor | 11-1 |
| scope 5 room-resize gesture | 11-2 |
| scope 6 "output above 0 dB" indicator | 11-1 |
| scope 7 AX34 unsupported-rate warning | 11-1 |
| scope 8 "approximate" note | 11-3 |
| scope 9 "settling" state | 11-3 |
| Out of scope | umbrella (governs all three) |
| A1 `EditorController` tests | 11-2 |
| A2 out-of-range α rejected | 11-3 |
| A3 undo/redo of material edits | 11-3 |
| A4 snapshot test | 11-1 (kept green by 11-2, 11-3) |
| A5 thread-assertion test | 11-1 (kept green by 11-2, 11-3) |
| A6 pluginval strictness 10 with editor tests | 11-1 (kept green by 11-2, 11-3) |
| A7 state round trip, editor size restored | 11-1 (kept green by 11-2, 11-3) |
| L-intro (hosts) | umbrella (applies to every sub-phase's items) |
| L1 open the editor | 11-2 |
| L2 drag the speakers while playing | 11-2 |
| L3 automation write of a listener drag | 11-2 |
| L4 carpet / concrete, undo | 11-3 |
| L5 resize, HiDPI, Windows 150 % | 11-1 |
| L6 save, reopen | 11-3 |
| L7 write down anything confusing | umbrella + 11-3 (shared) |
| C1a gesture handling with automation modes | 11-2 |
| C1b message-thread discipline | umbrella + 11-1 (shared) |
| C1c pixel↔metre mapping accuracy | 11-2 |
| C1d no `src/sim` headers except `sim::describeScene` | 11-1 |
| R1 scope creep toward a 3D editor | umbrella + 11-2 (shared) |
| R2 Windows DPI and resizing quirks | 11-1 |
| D1 all automated criteria green | each sub-phase for its own; umbrella when all are (shared) |
| D2 status row 11 `done` | each sub-phase row; row 11 when 11-1…11-3 are (shared) |
| D3 use checklist in the PR | each sub-phase PR carries its items (shared) |

## Notes from the split

- FM-1 (`docs/review/phase-split/5-decider-decision-r2.md`, Decided for Maisara, open to her veto): Phase 11 owns
  criteria under two seats' rows that each deserve a session (Seat 5: A4–A7; Seat 6: A1–A3). Split shell-first under
  D-PS3, canvas region reserved, layout provisional until 11-2.
- D-PS3 (Seat 6 conditions (i) and (ii)): applied in 11-1 (provisional layout, canvas region reserved as the largest
  region; references beside scope 1e) and recorded in 11-2 (layout confirmed there).
