# Phase 07c-1 — Diffuse solve off the synchronous paths

Size: **M** (remainder, if needed: `07c-1b`) · Depends on: 05h, 07 `done` · Part of: [phase-07c](phase-07c.md) ·
Lead subject matter: Seat 5 (Deadline keeper), "anything on or beside the audio thread: real-time safety; lock-free
hand-off; threading topology; host conformance (pluginval, auval, state, …); offline equals real-time" · Read first,
in this order: `CLAUDE.md`; this file in full [and the umbrella, `docs/phases/phase-07c.md`]; `docs/BUILD_PLAN.md`
§2 **AQ4, AQ10 (amended 2026-11-10), AX5, AX18, AX33, AX38, AX41, AX44**; `docs/phases/phase-05h.md` (§3 D-H1, §4
scope 2, the solve seam); `docs/phases/phase-07.md` (state restore, reset sequence, offline path);
`docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 and `51-decider-addendum-J1.md`;
`49-interrogator-board-answers-C1-Q2.md`; ledger P05B2-C1Q2-01…14; PRD NFR-2, NFR-3, NFR-6, FR-SIM-6.

The umbrella is a beta prerequisite: **Must be `done` before Phase 13's beta** (or phase-13 scope 13's versioning
fallback recorded) applies to this sub-phase as part of phase 07c (umbrella header).

---

## Raise with Maisara (first message and PR)

(phase-07c §2.1)
1. **Only if** this phase would land after the first public release without the estimator parameters
   versioned in saved state: Seat 7's condition fails and the item returns to Maisara (decider file 47 §4,
   strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.

## Goal

This phase moves the diffuse solve off the synchronous paths so W_max no longer has to fit the restore watchdog.
(phase-07c §0, last sentence; the W_max raise itself is 07c-2's.)

## Assumptions in force

All of the umbrella's: §1 "Settled — do not reopen" (AX37–AX46 and the AQ10 amendment; the board's J1 answer; D-H1
as decided in phase 05h) and §3 Timing. W_max stays at its (A) value in this sub-phase (umbrella §0; AX41).

## Scope

### Decisions before implementation (decision loop, `/fix-plan` step 3)

(phase-07c §4) Decided through the board loop and recorded as AX rows before any code; not by the implementer alone
(decider file 51 §4 item 4):
- **D-C1, the provisional-to-final step:** Seat 1's ruling on the size of the level step from the interim
  level to the final solve, which Seat 6 (d) and condition 5 depend on. (phase-07c §4 D-C1)
- **D-C2, the interim level and saved E_b:** the interim-level design (condition 5); if E_b is stored in
  the project state, a state-version AX (`pluginStateVersion` bump, state fixtures, Phase 07 rules).
  (phase-07c §4 D-C2)
- **D-C3, the solved result in saved state:** Seat 8's question whether the solved result can travel in
  the saved state, a feasibility call for Seat 5. (phase-07c §4 D-C3)

**Researcher questions** (decider file 51 §4 item 9; asking them before D-C1–D-C3 is the plan-editor's
ordering, not the decider's) (phase-07c §4 note):
- how long hosts tolerate a blocked `setStateInformation` (Seat 5); (phase-07c §4 R1)
- which hosts do not signal offline rendering reliably (Seat 5); (phase-07c §4 R2)
- host hang dialogs and their timeouts in Logic, Live, Cubase and Bitwig (Seat 7). (phase-07c §4 R3)

### Conditions (decider file 47 §4 (iii))

The diffuse solve moves off the synchronous restore, prepare and `reset()` (phase-07c §5 lead sentence, umbrella).

2. **Seam:** phase 05h already invokes the solve through one function from restore, prepare and `reset()`
   (Seat 5; phase-05h scope 2); this phase moves that one call off the synchronous path. (phase-07c condition 2)
4. **No real-time waiting.** (phase-07c condition 4)
   - The real-time path adopts the solved snapshot by atomic swap with an AQ4 crossfade, exactly one step
     per solve and never mid-drag. The UI shows "settling" (AX38 (iii)) (Seats 1 (iii), 3 (2), 5, 6 (c),
     8 (ii)).
   - The ISM update is never held behind the diffuse solve (Seat 3 (4)). Cross-reference: this is the
     split update that AX38 (v) names as the remedy for Table 15.1's head-rotation row (a Phase 10 AX that
     updates the specular and directional part without waiting for the diffuse solve); the two are
     designed together with phase-10's update scheduling (decider file 51 §4 item 4, 8 (e)).
5. **Interim level, in order of preference:** (phase-07c condition 5)
   1. the E_b saved in the project state, when the scene and W_max match, so that the restore level
      equals the final level (Seats 3 (1), 4, 8 (iii); feasibility is Seat 5's, D-C3);
   2. otherwise the (A)-budget estimate or the previous level (Seat 6 (b)).

   It is never silence and never the AX16 level where AX16 is known to be more than 1 dB off (1 jnd of G,
   Vorländer Table 6.1), such as layouts 4/5 and the absorbing-floor cube (Seats 1, 4, 9). The
   provisional-to-final step stays within Seat 1's ruling (D-C1; Seat 6 (d)).
6. **Offline.** Offline renders, bounces and `render_cli` always wait for the final solve and stay
   bit-identical. Where the host's offline signal is unreliable, the render log records it (Seats 1 (ii),
   2, 4, 5, 6 (e), 8 (i), 9). (phase-07c condition 6)
7. **Gates re-scoped after the move.** The restore gate (AX38 4c) measures restore without the solve; the
   solve time moves to the staleness records (AX38 (iv)) (Seat 5 (5)). E_b stays shared across modes and
   ears (Seat 4; AX39, AX44). (phase-07c condition 7)

## Out of scope

- The umbrella's §9 (phase-07c §9): Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel
  cache (AX38 (ii), phase-10 AX only); n\*_max (Q2b (i) stays unless the C++ W1 measurement moves it, AX41).
- Condition 1's golden round, condition 3 (W_max re-derived under (C)) and condition 8 (follow-on checks):
  [phase-07c-2](phase-07c-2.md).

## Acceptance criteria — automated

- [ ] D-C1–D-C3 recorded as AX rows (ledger rows linked) before the first code commit; the researcher's
      answers recorded. (phase-07c A1)
- [ ] Restore, prepare and `reset()` never run the diffuse solve synchronously; the restore gate (AX38 4c)
      passes measuring restore without the solve, on the Release build; the solve time is in the
      staleness records. (phase-07c A2)
- [ ] The real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, one step per
      solve, never mid-drag; the ISM update is never held behind the solve (tests); "settling" is shown
      while a solve is pending. (phase-07c A3)
- [ ] The interim level is never silence and never the AX16 level in the cases of condition 5 (test on
      layouts 4/5 and the absorbing-floor cube); the provisional-to-final step stays within D-C1's ruling.
      (phase-07c A4)
- [ ] Offline renders, bounces and `render_cli` wait for the final solve and are bit-identical run to run
      (AX5); an unreliable host offline signal is recorded in the render log. (phase-07c A5)
- [ ] If E_b is saved in state: the state-version AX applied, old state fixtures still load (Phase 07 rule).
      (phase-07c A7)
- [ ] E_b bit-identical between modes and ears (AX44); allocation tracker, TSan `[conv],[pipeline]`,
      pluginval strictness 10 and auval pass. (phase-07c A8)

## Listening / manual checklist

- [ ] Drag a source in a large room: the early part follows at once; the tail level updates after the drag.
      (phase-07c L2)
- [ ] Bounce the same project twice: the bounces are identical and match playback after settling. (phase-07c L3)

## Contractor review focus

- Threading of the moved solve (no real-time wait, no lock on the audio thread, the AX38 gate's classes
  after the move) (phase-07c F1)
- the atomic swap and crossfade (phase-07c F2)
- the interim-level rule (phase-07c F3)
- offline determinism (phase-07c F4)
- the saved-state format if E_b is stored (phase-07c F5)

## Risks

The original phase file has no risks section; the umbrella's §0 gives the rationale.

## Definition of done

- Section 6 all checked with CI evidence (phase-07c §10, clause 1; here: this file's automated criteria).
- PR with the listening checklist, contractor focus, AX/ledger links and the "Raise with Maisara" item if it applies
  (phase-07c §10, clause 3; this sub-phase's share).
- CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two sessions, split the remainder into
  `phase-07c-1b.md`.

## Notes from the split

- Convening-round correction (`docs/review/phase-split/1-decider-convening.md`, Map 07c; confirmed in
  `3-decider-decision.md` and `5-decider-decision-r2.md` corrections item 1): "§2.1 Raise goes into both sub-phase
  files (the phase's first message is 07c-1's)." Each raises it in its first message.
- 07c-c3 (convening round, NOT A DECISION): "(a). D-C1–D-C3 and R1–R3 in 07c-1; A1 as written."
- 07c-c1 (convening round, NOT A DECISION): "(a). The umbrella is the beta prerequisite (G3 default; matches §3 T1)."
