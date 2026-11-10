# Phase 07c — Asynchronous diffuse solve (Q2a (C))

Size: **M** (about one phase of Phase 07 rework, decider file 47; split into `phase-07d.md` if it cannot be
finished in two sessions, CLAUDE.md) · Depends on: 05h, 07 `done` · **Must be `done` before Phase 13's
beta** (or phase-13 scope 13's versioning fallback recorded) · Read first, in this order: `CLAUDE.md`; this file in full; `docs/BUILD_PLAN.md` §2 **AQ4, AQ10
(amended 2026-11-10), AX5, AX18, AX33, AX38, AX41, AX44**; `docs/phases/phase-05h.md` (§3 D-H1, §4
scope 2, the solve seam); `docs/phases/phase-07.md` (state restore, reset sequence, offline path);
`docs/review/phase-05b2/47-decider-board-answers-C1-Q2a-final.md` §4 and
`51-decider-addendum-J1.md`; `49-interrogator-board-answers-C1-Q2.md`; ledger P05B2-C1Q2-01…14; PRD
NFR-2, NFR-3, NFR-6, FR-SIM-6.

Created on 2026-11-10 from the board's answer to Challenge 1 and Q2a (J1: Challenge 1 = yes, Q2a = (A)
now, (C) scheduled now as its own phase; decider files 47 §4 (iii) and 51 §4 item 4; interrogator file 49
SURVIVES WITH CORRECTIONS, applied).

---

## 0. Why this phase exists

Under Q2a (A) the diffuse estimator's work limit W_max is sized to the project's restore convention,
14 × t_restore ≤ 30 s (not pluginval's requirement, whose watchdog resets per restore: H1-F1, decider file
19; W_max pinned at 3.05 M per emitter by D-H1 (iv), the (A) formula giving no W_max ≥ 0 on macOS; AX41),
because the diffuse solve runs inside the synchronous state restore, prepare and `reset()`. That keeps
random level error in the capped class until this phase: SE 0.13–1.33 dB in Kuttruff Table 5.2 layouts 4/5
at s = 1 and 0.44–0.50 dB in the low-α s = 1 100 m cube (C16 (f), at n\*_max 1 024); rooms near 100 m are
capped at SE ≤ 0.15 dB in the s = 0.3 and absorbing-floor cubes (decider file 51 §2, L3/L5). This is
Seat 1's "now" 2, repaid when this phase lands with W_max re-derived from the background budget. This phase
moves the diffuse solve off the synchronous paths so W_max no longer has to fit the restore convention.

**Scope extended by D-H1 (v) / H1-F2 (2026-11-10; decider
`docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md`, interrogator `21-interrogator-D-H1-D-H2-r2.md`
SURVIVES; `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`, this phase's
scope being a board answer she accepted):** condition 9 below. The C++ measurements show that the non-diffuse
100 m / 96 kHz build alone is 3.29 s, 95.5 % of it the unit-decay synthesis in `tail::BandNoiseGenerator` at
the 12 s tail cap (`7-orchestrator-split-timer-K23.md`), so moving only the diffuse solve does not bring the
macOS restore under the convention (14 × 2.33–2.59 s = 32.6–36.3 s); the AX38 4c register's macOS entry
closes only when the synthesis leaves the synchronous restore (condition 9, or `phase-07d.md` if 07c cannot
carry it).

**Scope extended by D-H3 (e) / H3-F5 (2026-11-10; decider `docs/review/phase-05h/25-decider-decision-D-H3-r2.md`
"DECISION D-H3 (e)" and `27-decider-decision-D-H3-r3.md`, interrogator files 26 and 28 SURVIVES; AX38 (i) as
corrected):** conditions 10 and 11 below. `reset()` and `setNonRealtime` may arrive on the VST3 processing
thread (specification and the pinned JUCE 8.0.17 wrapper; AU unspecified), where the project's path waits for
the in-flight build (measured worst 2 664 ms) and may build synchronously (≈ 3.6 s): condition 10 is the
remedy and the first step of this phase; condition 11 builds the instrument that measures the freeze /
offline thread per host.

## 1. Settled — do not reopen

- AX37–AX46 and the AQ10 amendment (phase-05h §1).
- The board's J1 answer: the blocking 100 m, 96 kHz restore gate (AX38 4c, with its conditions); W_max
  (A) now; this phase scheduled before the first public release; Q2b (i), n\*_max 1 024 (decider files 43,
  47, 51).
- D-H1 as decided in phase 05h (the margin rule; AX41).

## 2. Raise with Maisara (first message and PR)

1. **Only if** this phase would land after the first public release without the estimator parameters
   versioned in saved state: Seat 7's condition fails and the item returns to Maisara (decider file 47 §4,
   strongest objection; phase-13 "Raise with Maisara" item 4). Otherwise none.

## 3. Timing

- Lands **before the first public release (the Phase 13 beta)**, with its W_max raise in one golden round.
  If it lands after release, the estimator parameters are versioned in saved state (Seats 5, 7;
  condition 1).
- **Brought ahead of Phase 08's golden freeze** if Phase 08's heaviest-mode build makes the pinned W_max
  fail the restore gate (AX38 4c; phase-08 scope 10). That gate exists only once 05h is `done`, so this
  phase comes forward only after 05h (its dependency); if Phase 08 went first, the heaviest-mode gate is
  run in phase-05h scope 10.
- **Brought forward on any restore-gate failure** (AX38 4c: a gate failure is a defect, remedied only by
  moving work off the restore path).
- **Next phase after 05h** (D-H1 (v)): 05h closes with the AX38 4c register entries recorded (Linux and
  macOS cube); this phase follows 05h directly, before Phase 08's goldens, with "Depends on: 05h `done`"
  unchanged; if 05h's gate and records are split into phase-05i, this phase follows 05i. Its (C) W_max is
  pinned only after the AX38 4c 3-minute 100 m bounce record is in this phase's packet (Seat 8; AX41).

## 4. Decisions before implementation (decision loop, `/fix-plan` step 3)

Decided through the board loop and recorded as AX rows before any code; not by the implementer alone
(decider file 51 §4 item 4):
- **D-C1, the provisional-to-final step:** Seat 1's ruling on the size of the level step from the interim
  level to the final solve, which Seat 6 (d) and condition 5 depend on.
- **D-C2, the interim level and saved E_b:** the interim-level design (condition 5); if E_b is stored in
  the project state, a state-version AX (`pluginStateVersion` bump, state fixtures, Phase 07 rules).
- **D-C3, the solved result in saved state:** Seat 8's question whether the solved result can travel in
  the saved state, a feasibility call for Seat 5.

**Researcher questions** (decider file 51 §4 item 9; asking them before D-C1–D-C3 is the plan-editor's
ordering, not the decider's):
- how long hosts tolerate a blocked `setStateInformation` (Seat 5);
- which hosts do not signal offline rendering reliably (Seat 5);
- host hang dialogs and their timeouts in Logic, Live, Cubase and Bitwig (Seat 7).

## 5. Scope — conditions 1–11 (conditions 1–8: decider file 47 §4 (iii); condition 9: D-H1 (v) / H1-F2, decider file 19; conditions 10 and 11: D-H3 (e) / H3-F5, decider files 20, 25, 27)

The diffuse solve moves off the synchronous restore, prepare and `reset()`.
1. **Timing** (section 3): before the first public release, with its W_max raise in one golden round;
   after release only with the estimator parameters versioned in saved state.
2. **Seam:** phase 05h already invokes the solve through one function from restore, prepare and `reset()`
   (Seat 5; phase-05h scope 2); this phase moves that one call off the synchronous path.
3. **W_max re-derived under (C)** from the background budget: Seat 6's 3 s per emitter, the AX38 (iv)
   load mark, and Table 15.1's 700 ms / 3 s rows (Seats 1 (i), 3 (5), 5). It is not kept at (A). It stays a
   pinned work count, the same on every platform (AX41), re-derived from the C++ cost, never a time cap;
   AX41 and the AQ10 amendment are updated through `/fix-plan`.
4. **No real-time waiting.**
   - The real-time path adopts the solved snapshot by atomic swap with an AQ4 crossfade, exactly one step
     per solve and never mid-drag. The UI shows "settling" (AX38 (iii)) (Seats 1 (iii), 3 (2), 5, 6 (c),
     8 (ii)).
   - The ISM update is never held behind the diffuse solve (Seat 3 (4)). Cross-reference: this is the
     split update that AX38 (v) names as the remedy for Table 15.1's head-rotation row (a Phase 10 AX that
     updates the specular and directional part without waiting for the diffuse solve); the two are
     designed together with phase-10's update scheduling (decider file 51 §4 item 4, 8 (e)).
5. **Interim level, in order of preference:**
   1. the E_b saved in the project state, when the scene and W_max match, so that the restore level
      equals the final level (Seats 3 (1), 4, 8 (iii); feasibility is Seat 5's, D-C3);
   2. otherwise the (A)-budget estimate or the previous level (Seat 6 (b)).

   It is never silence and never the AX16 level where AX16 is known to be more than 1 dB off (1 jnd of G,
   Vorländer Table 6.1), such as layouts 4/5 and the absorbing-floor cube (Seats 1, 4, 9). The
   provisional-to-final step stays within Seat 1's ruling (D-C1; Seat 6 (d)).
6. **Offline.** Offline renders, bounces and `render_cli` always wait for the final solve and stay
   bit-identical. Where the host's offline signal is unreliable, the render log records it (Seats 1 (ii),
   2, 4, 5, 6 (e), 8 (i), 9).
7. **Gates re-scoped after the move.** The restore gate (AX38 4c) measures restore without the solve and
   the synthesis (condition 9); the solve time moves to the staleness records (AX38 (iv)) (Seat 5 (5)). E_b
   stays shared across modes and ears (Seat 4; AX39, AX44).
8. **Follow-on checks.** The Phase 12 (ii) preset check (no preset default raises U) is re-run under this
   phase's W_max (Seat 6 (e)). Phase 08 goldens in capped rooms carry a tolerance derived from the
   achieved SE, unless this phase lands before they are frozen (Seat 4).
9. **The unit-decay synthesis moves off the synchronous restore** (D-H1 (v) / H1-F2, decider file 19,
   interrogator file 21; the register's macOS remedy): the unit-decay synthesis (`tail::BandNoiseGenerator`,
   constructor spectra 0.96 s + `make` × 2 emitters 2.18 s = 3.14 of 3.29 s at 100 m / 96 kHz, flat in room
   size for T60_max ≥ 8 s, ≈ 2.5× from 48 to 96 kHz) moves off the synchronous restore, prepare and `reset()`
   with the same interim / settling rules as the diffuse solve (the interim tail while the synthesis is
   pending is decided in this phase's loop beside D-C2; never silence where a tail existed in the saved
   state); after both moves the restore gate measures ISM + matching + mix (≈ 0.15 s at 96 kHz) and passes a
   worst-of-10 rule with 10–20× headroom. Closes the AX38 4c register entries: Linux cube (also closed by
   the diffuse move, 28.9 s) and macOS cube (33.40 s; closes here, or at 07d, or at Phase 13's
   release-machine re-check if the runner is shown to be the cause). If this phase's loop finds condition 9
   does not fit here, a `phase-07d.md` of size S–M is created (CLAUDE.md split rule) and the register's
   macOS 'closes at' names 07d. Alternatives recorded, not chosen: a cheaper generator (output-changing; a
   golden round; AQ10's "not optimised before Phase 13" to be read by the board); caching the constructor
   spectra per (fs, length) (bit-identical, ≈ 4 of 14 FFTs, [Hyp] 20–25 %, not enough alone).
10. **The `reset()` half** (D-H3 (e) / H3-F5; decider files 20 and 25 "DECISION D-H3 (e)", file 27;
    interrogator files 22, 26, 28; AX38 (i)'s register entry and remedy): **the first step of this phase,
    with its own TSan `[pipeline]` round.** Design = Seat 3's (e-k) + Seat 2's (e-e): `reset()` and
    `setNonRealtime(true)` only cancel (abandon flag, gate notify) and never wait or build; cancel points in
    image-source planning, `BandNoiseGenerator` (between the band-pair IFFTs and every 2¹⁶ samples of the
    sample and assembly loops) and the IR-set build, throwing `BuildCancelled`, output untouched — they
    also shorten every quiesce (restore, prepare, release and the destructor), which with condition 9
    bounds the AX38 4c K-e12 finding (a restore arriving mid-build); in realtime mode a reset clears the
    convolver's history, pending output and counter but **keeps the current IrSet** (promoting `next_` if a
    fade was running), so the stale → fresh switch arrives as an ordinary AQ4 / AX31 update and the output
    is never silent; the offline branch is unchanged (drop, then the next `process()` builds before the
    block: X11, NFR-6). Tests: a `[pipeline]` test asserts that `reset()` and `setNonRealtime(true)` never
    wait on the builder and never build; the two-order test; the AX38 (i) transient-memory record (an
    abandoned build's ISM/synthesis may overlap the offline build: Seat 5). Closes AX38 (i)'s register
    entry (worst quiesce wait 2 664 ms, stale build ≈ 3.6 s, up to ≈ 6.3 s) and lifts its release rule (no
    build reaches a producer outside the team, beta included, while the entry is open). Never a per-host
    code path (NFR-8).
11. **The trace build and the per-host measurement** (D-H3 (e); AX38 (i), half (2)): a CMake option
    `SPATIAL_HOST_TRACE`, default OFF, excluded from release artefacts, guarded by `pytest tools/ci`: a
    preallocated SPSC ring written from the host entry points and drained off-thread (nothing on the
    realtime path allocates, locks or logs), logging entry id, native thread id, `isNonRealtime()`,
    transport state, block size and time per call. The instrument is this phase's deliverable; **the run is
    a person's action** on real machines with host licences (Maisara or the contractor; Seat 7's estimate
    ≈ 1–2 person-days inside trial windows): Live 12, Logic (AU), Cubase (ASIO-Guard on and off), Bitwig
    (each hosting mode), REAPER (anticipative FX on/off, each render mode), FL Studio and Studio One, on
    macOS arm64 and Windows x64, in `docs/review/phase-05h/12-researcher-T5T4-61.md` §3's situations
    (a)–(e) plus bypass/unbypass, mute/unmute and plugin removal, with a 100 m scene. Results go to Phase
    13's host matrix and the compatibility notes as evidence for the notes, never a per-host code path
    (NFR-8); they do not block this phase's merge. Until measured, the compatibility notes carry AX38
    (i)'s interim sentence (no host named, no stall figure as a product promise, not in launch copy).

## 6. Acceptance criteria — automated

- [ ] D-C1–D-C3 recorded as AX rows (ledger rows linked) before the first code commit; the researcher's
      answers recorded.
- [ ] Restore, prepare and `reset()` never run the diffuse solve synchronously; the restore gate (AX38 4c)
      passes measuring restore without the solve and, under condition 9, without the unit-decay synthesis,
      on the Release build, in AX38 4c's register form (the entries it closes removed through `/fix-plan`);
      the solve time is in the staleness records.
- [ ] The real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, one step per
      solve, never mid-drag; the ISM update is never held behind the solve (tests); "settling" is shown
      while a solve is pending.
- [ ] The interim level is never silence and never the AX16 level in the cases of condition 5 (test on
      layouts 4/5 and the absorbing-floor cube); the provisional-to-final step stays within D-C1's ruling.
- [ ] Offline renders, bounces and `render_cli` wait for the final solve and are bit-identical run to run
      (AX5); an unreliable host offline signal is recorded in the render log.
- [ ] W_max re-derived under (C) from the background budget (condition 3), pinned, equal on the three OSes;
      goldens updated once through `update_goldens.py` with the reason; §6 row.
- [ ] If E_b is saved in state: the state-version AX applied, old state fixtures still load (Phase 07 rule).
- [ ] E_b bit-identical between modes and ears (AX44); allocation tracker, TSan `[conv],[pipeline]`,
      pluginval strictness 10 and auval pass.
- [ ] The Phase 12 (ii) preset check re-run under the new W_max and reported, if Phase 12 has run;
      otherwise Phase 12 runs it at 07c's W_max.
- [ ] Condition 10: the `[pipeline]` test shows `reset()` and `setNonRealtime(true)` never wait on the
      builder and never build; a realtime reset keeps the current IrSet (output never silent); the two-order
      test and the transient-memory record; TSan `[pipeline]` green; the AX38 (i) register entry removed
      through `/fix-plan`.
- [ ] Condition 11: the `SPATIAL_HOST_TRACE` option builds, is OFF by default, is absent from release
      artefacts (`pytest tools/ci` guard) and leaves the realtime path allocation-, lock- and log-free
      (tracker test); the per-host run itself is a person's action and does not gate this phase.

## 7. Listening checklist (Maisara)

- [ ] Load a project with a large room: the room is heard at once at the interim level, shows "settling",
      and moves to the final level without a click or an obvious jump.
- [ ] Drag a source in a large room: the early part follows at once; the tail level updates after the drag.
- [ ] Bounce the same project twice: the bounces are identical and match playback after settling.

## 8. Contractor review focus

Threading of the moved solve (no real-time wait, no lock on the audio thread, the AX38 gate's classes
after the move); the atomic swap and crossfade; the interim-level rule; offline determinism; the saved-state
format if E_b is stored; the W_max re-derivation from the background budget.

## 9. Out of scope

Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel cache (AX38 (ii), phase-10 AX
only); n\*_max (Q2b (i) stays at the pinned 1 024 and is not re-derived here unless the W1 measurement per
output mode moves it, AX41; D-H1 (iv)). Moving the unit-decay synthesis **is** in scope (condition 9);
caching its constructor spectra per (fs, length) is not the AX38 (ii) kernel cache but an alternative
recorded, not chosen. **W_max re-derivation (condition 3) has a prerequisite:** the (C) W_max is pinned
only after the AX38 4c record "offline-bounce time of a 3-minute room-size automation at 100 m, with its
ratio to real time" is in this phase's packet (Seat 8; D-H1 (iv), AX41).

## 10. Definition of done

Section 6 all checked with CI evidence; §0 row 07c `done` before Phase 13's beta; PR with the listening
checklist, contractor focus, AX/ledger links and the "Raise with Maisara" item if it applies.
