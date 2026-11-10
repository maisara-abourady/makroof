# Phase 11-1 — Editor shell, output panel and status readouts

Size: **M** (remainder, if needed: `11-1b`) · Depends on: 07, 09 · Part of: [phase-11](phase-11.md) · Lead subject matter: Seat 5 (Deadline keeper), "anything on or beside the audio thread: … threading topology; host conformance (pluginval, auval, state, automation, undo, buses, latency); … platform transitions" · Read first: `CLAUDE.md`, `docs/BUILD_PLAN.md` §2 (AX2, AX6, AX34), PRD "Overview & vision", FR-3D-1 (deferred in full), FR-3D-5, and the umbrella [phase-11](phase-11.md)

## Goal

This sub-phase's share of the umbrella goal ("A small, usable editor: … and picks the output mode"): the custom
editor replaces the generic one, and the user picks the output mode. It doesn't need a single acoustic term, matching
the PRD's vision. It is **not** the full 3D editor (deferred, B8).

## Assumptions in force

- All of the umbrella's (phase-11 Assumptions in force). The status strip below applies AX38's 4c hand-off (the
  nominal Eyring T60 line in scope 1f).

## Scope

1. `src/plugin/ui/` (JUCE components, message thread only): (phase-11 scope 1, lead-in; shared with the umbrella)
   - **Output panel:** binaural / stereo speakers toggle with one line of explanatory text each
     ("for headphones" / "for a pair of speakers"), output trim. (phase-11 scope 1e)
     - References for the output-mode text (D-PS3 step 3, Seat 6 condition (ii); a reference, not an item):
       the phase-08 line 302 hand-off ("Hand-off to Phase 11 (Seat 6)": output-mode tooltip or manual, a
       default-experience note), the phase-09 line 75 hand-off (binaural height or depth on speakers: "Set
       expectations in UI text in Phase 11"), and the `docs/BUILD_PLAN.md` §6 row D1 (2026-11-09, "Phase 11 tooltip
       note").
   - **Status strip:** reported latency (ms), CPU estimate, the room's derived T60 at 500 Hz and 1 kHz
     (from `sim` via the contract: expose `sim::describeScene(const SceneDescription&)` returning summary
     numbers, so the UI never reaches into sim internals), and a warning badge if state failed to load (Phase 07).
     The nominal Eyring T60 is not shown as an open field's reverb time (AX38 4c hand-off, Seat 6). (phase-11 scope 1f)
2. Resizable editor with a fixed aspect ratio, minimum 800×500, HiDPI-correct. Remember the size in state.
   (phase-11 scope 3)
3. Remove the generic editor. (phase-11 scope 4)
4. **"Output above 0 dB" indicator:** display only, no auto-gain (AX2; Phase 07 D4). (phase-11 scope 6)
5. Show the **AX34 unsupported-rate warning flag** with the supported rates listed (Phase 07 D8). (phase-11 scope 7)

## Out of scope

The umbrella's (phase-11 Out of scope). Also the work of the later sub-phases: the top and side views, dragging, the
room panel, `EditorController` and the room-resize gesture (phase-11 scope 1a–1c, 2, 5; in 11-2); the surfaces panel,
the "approximate" note and the "settling" state (phase-11 scope 1d, 8, 9; in 11-3).

## Acceptance criteria — automated

- [ ] **Snapshot test:** the editor renders to an offscreen `juce::Image` at 800×500, 1200×750 and
      1600×1000 without assertions, and the image isn't blank. (Pixel-exact comparison isn't required
      because fonts differ across OSes.) (phase-11 A4)
- [ ] A thread-assertion test: any scene mutation off the message thread trips a debug assertion (test
      it with a deliberate violation in a death-test-style subprocess or a mocked assert handler). (phase-11 A5)
- [ ] pluginval strictness 10 with editor tests enabled passes on 3 OSes (Linux under `xvfb-run`). (phase-11 A6)
- [ ] State round trip still bit-identical; editor size is restored. (phase-11 A7)

## Listening / manual checklist

Hosts: as the umbrella's (phase-11 L-intro).
- [ ] Resize the window; check it on a HiDPI/Retina screen and at Windows 150% scaling. (phase-11 L5)

## Contractor review focus

Message-thread discipline (phase-11 C1b; shared with the umbrella), and that no UI code includes `src/sim` headers
except via `sim::describeScene` (phase-11 C1d).

## Risks

Host-specific DPI and resizing quirks on Windows. (phase-11 R2)

## Notes from the split

- D-PS3 (`docs/review/phase-split/3-decider-decision.md`, step 2; Seat 6 condition (i); stands in
  `5-decider-decision-r2.md`): its aspect ratio and region layout are provisional, set in 11-2 once the two scale views
  exist; 11-1 reserves the canvas region as the largest region. Scope 3's wording is unchanged.
- D-PS3 step 3 (Seat 6 condition (ii)): the output-mode references beside scope 1e above.
- Criterion ownership (`5-decider-decision-r2.md`, Q5): A4–A7 fall under Seat 5's row; scope 1e, 1f, 6 and 7 own no
  criterion and ride under the Seat 5 lead as named hand-offs, under Seat 6's condition (ii).
- Once this sub-phase makes A4–A7 pass, 11-2 and 11-3 keep them green (umbrella shared rule).

## Definition of done

- All automated criteria above green (phase-11 D1, this sub-phase's share); status row 11-1 `done` (phase-11 D2); use
  checklist in the PR (phase-11 D3).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-11-1b.md`.
