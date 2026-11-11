# Phase 11-3 — Surfaces panel and engine-state notes

Size: **M** (remainder, if needed: `11-3b`) · Depends on: 11-2 (and through it 11-1, 07, 09) · Part of: [phase-11](phase-11.md) · Lead subject matter: Seat 6 (Canvas designer), "which controls exist and which stay hidden; names, ranges, defaults, …" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AQ3, AX6), PRD "Overview & vision", FR-3D-1 (deferred in full), and the umbrella [phase-11](phase-11.md)

## Goal

This sub-phase's share of the umbrella goal ("A small, usable editor: … sets room size and surface materials …"): the
user sets the surface materials. It doesn't need a single acoustic term, matching the PRD's vision.

## Assumptions in force

- **AQ3**: materials are chosen from a list. The advanced view exposes per-band α and scattering.
  (phase-11 Assumptions, AQ3; shared with the umbrella)
- **AX44** (phase 05b): the "approximate" note U (`TailMatch.approximate`, per emitter) and its text rules;
  **AX38**: the diffuse-solve gate and the "settling" state; **AX39**: Seat 7's allowed and forbidden
  wording for accuracy claims. (phase-11 Assumptions, AX44, AX38, AX39; shared with the umbrella)
- And all of the umbrella's.

## Scope

Inside the umbrella's `src/plugin/ui/` (JUCE components, message thread only) (phase-11 scope 1, lead-in):
1. **Surfaces panel:** for each of the 6 surfaces, a material dropdown (list from `resources/materials.json`
   if Phase 12 is done, otherwise a placeholder list of 6 materials defined in `module3d`) and an
   "Advanced" disclosure with a per-band α table plus scattering, validated live (AQ3 ranges).
   Material edits aren't host parameters (too many). They're stored in the scene state and count as
   undoable edits (JUCE `UndoManager`). (phase-11 scope 1d)
2. **"Approximate" note** (AX44, phase 05b): shown from `TailMatch.approximate` on the **settled** scene
   only, in the info view, never mid-drag; wording by Seats 6 and 7 (within AX39's wording rules). Text
   (Seat 6 (i)): both-near branch: no ±x from the achieved SE; either the measured replicate p95 of its
   case class from the phase-05h C++ reported set, or qualitative text ("level unreliable with source and
   listener this close to surfaces; move either about 0.7 m away"); capped branch: ±x from the achieved SE
   only for classes whose reported set shows SE ≥ the replicate SD, otherwise the class p95 or
   qualitative text. When U is raised on an emitter the user did not edit, the note names the scene, not
   that emitter, as the cause. **U′** (cap hit OR both-near, Seat 6 (iii)) appears only as a labelled
   diagnostic tier in an advanced view. **U's note reaches the producer's editor, not only the
   diagnostics** (Seat 8's later 1 depends on it; decider file 51 §1, §4 item 6). (phase-11 scope 8)
   **Display rule (AX44, D-H3 (b) / H3-F2, 2026-11-10; decider files 20, 25, 27; a note rule, not the
   predicate):** the note is not shown where the tail it describes lies more than 60 dB below the direct
   sound after t_dir + 50 ms by AX37 (5.4)'s kept check (broadband energy after the direct peak + 50 ms
   over the peak's squared amplitude) with E_target raised by 3·SE; the rule keys on that measured ratio
   only, never on a preset category or a scene name (NFR-8); U stays raised in the diagnostics and the U′
   tier; if shown there: "Outdoor scene: the reverberant tail is more than 60 dB below the direct sound;
   its level is only roughly estimated" (no ±x, no both-near wording unless both-near fired). Measured
   (phase 05h reports test): `open_field` −85 dB (the rule applies), `edge_values` −30 / −16 dB (the note
   shows, with the cap wording), `medium_room` +7 dB. Seat 7's report sentence "very long, very narrow or
   near-rigid rooms can show the indicator at any placement" is the text candidate for that capped case
   (Seat 6 owns the words, within AX39's wording rules).
3. **"Settling" state** (AX38 (iii)): shown on every instance whose latest change is not yet audible (queued at
   the gate, building or crossfading; Phase 10's staleness above zero), project load included. (phase-11 scope 9)

## Out of scope

The umbrella's (phase-11 Out of scope). Also the work of the earlier sub-phases: the editor shell, output panel,
status strip and indicators (phase-11 scope 1e, 1f, 3, 4, 6, 7; in 11-1); the views, dragging, room panel,
`EditorController` and room-resize gesture (phase-11 scope 1a–1c, 2, 5; in 11-2).

## Acceptance criteria — automated

- [ ] Editing α to an out-of-range value is rejected with the validator's error message, and the scene
      stays valid. (phase-11 A2)
- [ ] Undo/redo of material edits restores identical scene JSON. (phase-11 A3)
- [ ] phase-11 A4–A7 stay green with the panel and notes added (umbrella shared rule).

## Listening / manual checklist

Hosts: as the umbrella's (phase-11 L-intro).
- [ ] Change the floor to carpet and the walls to concrete: audible change; undo returns the previous sound. (phase-11 L4)
- [ ] Save, reopen the project: same layout, same sound, same window size. (phase-11 L6)
- [ ] Write down anything confusing. This is the first time the product's *user* side is exercised. (phase-11 L7;
      shared with the umbrella)

## Contractor review focus

The umbrella's message-thread discipline (phase-11 C1b) applies; no other clause of phase-11's focus is this
sub-phase's.

## Risks

None beyond the umbrella's.

## Notes from the split

- 11-c3 (`docs/review/phase-split/1-decider-convening.md`, Map 11): NOT A DECISION within this split: (a). The gap
  (11 may reach S8/S9 before 05h's reported set and gate exist, via 09 → 08 → AX37 exception) predates the split →
  follow-up `/fix-plan` item: record 05h for 11-3. This split adds no dependency; scope 8 and 9 sit here, in the last
  sub-phase, so 11-1 and 11-2 stay free of 05h.
- L6's window-size clause is first testable after 11-1 and is covered there by phase-11 A7 (map-11 §3).

## Definition of done

- All automated criteria above green (phase-11 D1, this sub-phase's share); status row 11-3 `done` (phase-11 D2); use
  checklist in the PR (phase-11 D3).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-11-3b.md`.
