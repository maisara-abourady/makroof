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

This phase moves the diffuse solve off the synchronous paths so W_max no longer has to fit the restore convention.
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

### Conditions (conditions 2, 4–7: decider file 47 §4 (iii); condition 9: D-H1 (v) / H1-F2, decider file 19; conditions 10 and 11: D-H3 (e) / H3-F5, decider files 20, 25, 27; condition 12: D-G1, phase 05i, decider file 13)

The diffuse solve moves off the synchronous restore, prepare and `reset()` (phase-07c §5 lead sentence, umbrella).

2. **Seam:** phase 05h already invokes the solve through one function from restore, prepare and `reset()`
   (Seat 5; phase-05h scope 2); this phase moves that one call off the synchronous path. (phase-07c condition 2)
4. **No real-time waiting.** (phase-07c condition 4)
   - The real-time path adopts the solved snapshot by atomic swap with an AQ4 crossfade, exactly one step
     per solve and never mid-drag. The UI shows "settling" while the update is pending (AX38 (iii) as amended
     2026-11-11, G1-C1) (Seats 1 (iii), 3 (2), 5, 6 (c), 8 (ii)).
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
7. **Gates re-scoped after the move.** The restore gate (AX38 4c) measures restore without the solve and
   the synthesis (condition 9); the solve time moves to the staleness records (AX38 (iv)) (Seat 5 (5)). E_b
   stays shared across modes and ears (Seat 4; AX39, AX44). (phase-07c condition 7)

   **The 07c re-pin** (AX38 4c; phase-05i §3.3 (v); D-Q5, decider file `docs/review/phase-05i/9-decider-r2.md`):
   after conditions 9 and 12 land (the gate then measures restore without the solve and the synthesis), the
   restore gate's growth-bound baselines, the ±5 % flutter window, the solve bound k (`kSolveWarn`) and its
   `solveRefMs` baselines are re-derived from ≥ 3 in-window runs: one run PROVISIONAL, printed not asserted;
   never a red or out-of-window run as a baseline; a CHANGELOG reason. The macOS trigger (2 172 ms) is
   re-derived at the same re-pin (AX38 4c; phase-05i §3.3 (iii)).
9. **The unit-decay synthesis moves off the synchronous restore** (D-H1 (v) / H1-F2, decider file 19,
   interrogator file 21; the register's macOS remedy): the unit-decay synthesis (`tail::BandNoiseGenerator`,
   constructor spectra 0.96 s + `make` × 2 emitters 2.18 s = 3.14 of 3.29 s at 100 m / 96 kHz, flat in room
   size for T60_max ≥ 8 s, ≈ 2.5× from 48 to 96 kHz) moves off the synchronous restore, prepare and `reset()`
   with the same interim / settling rules as the diffuse solve (the interim tail while the synthesis is
   pending is decided in this phase's loop beside D-C2; never silence where a tail existed in the saved
   state); after both moves the restore gate measures ISM + matching + mix (≈ 0.15 s at 96 kHz) and passes a
   worst-of-10 rule with 10–20× headroom. Closes the AX38 4c register entries: the macOS entry (33.40 s;
   closes here, or at 07d, or at Phase 13's release-machine re-check if the runner is shown to be the cause)
   and the Windows entry (36.73 s; remedy phase-07c conditions 9 (or 07d) and 10, or Phase 13's release-machine re-check; listed since run 42942694523, its OVER30S on 05i's
   run of record on a slow runner); the Linux entry already closed in phase 05i under (c). If this phase's
   loop finds condition 9 does not fit here, a `phase-07d.md` of size S–M is created (CLAUDE.md split rule)
   and the register's macOS 'closes at' names 07d. Alternatives recorded, not chosen: a cheaper generator (output-changing; a
   golden round; AQ10's "not optimised before Phase 13" to be read by the board); caching the constructor
   spectra per (fs, length) (bit-identical, ≈ 4 of 14 FFTs, [Hyp] 20–25 %, not enough alone). Its packet
   repeats the file 7 split timer (`[probe-restore-split]`, both gated scenes) on one named local box before
   sizing the interim rules (RG-1, Seat 5 (vi)). (phase-07c condition 9)
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
    code path (NFR-8). (phase-07c condition 10)
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
    (i)'s interim sentence (no host named, no stall figure as a product promise, not in launch copy). (phase-07c condition 11)
12. **The gate narrowed to the diffuse solve** (D-G1, phase 05i, decider file 13; AX38 (i) register entry G-1; Seats
    2, 3, 5 and 6). The AX38 gate encloses the diffuse solve only, as AX38 (i) states. Image-source planning, the
    unit-decay synthesis and the IR assembly run outside it. **Order:** after condition 10's cancel points (Seat 5),
    and before condition 9's synthesis move; records (b) and (g) are taken between the two, so the narrowing is
    judged by one difference at a time (Seat 3). **Form (Seat 2):** `sim::buildRoomIR` is split into stages
    (plan/ISM → diffuse solve → synthesis and assembly; names are the implementer's). `buildRoomIR` stays their
    composition for `render_cli`, with a test that its output is bit-identical to the composed stages on each
    platform (AX5). The pipeline holds `DiffuseSolveGate::Scope` around the solve stage only (RAII: `BuildCancelled`
    thrown inside the solve releases the gate), and the solve pool is passed only while the gate is held. Conditions
    4 and 9 use the same stages. A sim API change only: no `contractVersion` change, `check_boundaries.py`
    unchanged, `sim` JUCE-free; not a formulation seam (D-H1 (v)(d)). Builder threads keep their default priority
    (AX38 (i)). **Tests and records:** (a) a `[pipeline]` test asserts that the gate is not held while image-source
    planning or the synthesis runs and is held during the solve (observed through a test hook; nothing on the
    real-time path); (b) phase 05i's gate-wait split, run unchanged, prints class (1)'s queue time at 1, 4 and 8
    instances beside the 05i figures (prediction: at most one solve plus slack; printed, never a CHECK); (c) the
    callback p99.9 and max at host buffer 64, re-taken with 1, 4 and 8 genuinely concurrent builders and printed
    beside 05h's serialised record (a rise is a finding for the board, never fixed by an instance cap: PRD FR-3D-5,
    FR-3D-6, FR-SIM-7, A5); (d) the worst `quiesce()` wait with N syntheses running concurrently; (e) TSan
    `[pipeline]` with two pipelines whose ISM and synthesis overlap while a third solves; (f) the AX38 (i)
    transient-memory record as the **process** peak with 4 and 8 concurrent builds at 100 m, 48 and 96 kHz (a breach
    goes to Phase 13's memory budget, scope 1, where a limit on concurrently running builds, sized from this record,
    is the open remedy; never an instance cap (PRD FR-3D-5, FR-3D-6, FR-SIM-7, A5), a W_max cut or a range change
    (D-H1 (v)(d))); (g) the AX38 (iv) staleness records (room-size and joint steps; 1, 4 and 8 instances; both
    rooms, 48 and 96 kHz), re-taken, printing the min–max spread across instances (Seat 6 C2) beside the 05i
    figures; the joint step's +0.5 m listener move is read by extension against Vorländer Table 15.1's 700 ms row
    only (moves > 0.25 m: binaural processing plus the specular part; Seat 1); the 3 s row (translational
    move > 1 m, specular plus scattering part) applies to none of these records — a reading, not a gate.
    FR-SIM-6's 'without audible artifacts' stays not measured here (Phase 10-3). **Closes** AX38 (i)'s register
    entry G-1 and lifts its own release rule, through `/fix-plan`, when A12 passes. (D-G1)

## Out of scope

- The umbrella's §9 (phase-07c §9): Changing the estimator (AX39–AX44); a both-near fallback (§5 B15); a kernel cache
  (AX38 (ii), phase-10 AX only); n\*_max (Q2b (i) stays at the pinned 1 024 and is not re-derived here unless the W1
  measurement per output mode moves it, AX41; D-H1 (iv)). Moving the unit-decay synthesis **is** in scope (condition
  9); caching its constructor spectra per (fs, length) is not the AX38 (ii) kernel cache but an alternative recorded,
  not chosen. **W_max re-derivation (condition 3) has a prerequisite:** the (C) W_max is pinned only after the AX38 4c
  record "offline-bounce time of a 3-minute room-size automation at 100 m, with its ratio to real time" is in this
  phase's packet (Seat 8; D-H1 (iv), AX41).
- Condition 1's golden round, condition 3 (W_max re-derived under (C)) and condition 8 (follow-on checks):
  [phase-07c-2](phase-07c-2.md).

## Acceptance criteria — automated

- [ ] D-C1–D-C3 recorded as AX rows (ledger rows linked) before the first code commit; the researcher's
      answers recorded. (phase-07c A1)
- [ ] Restore, prepare and `reset()` never run the diffuse solve synchronously; the restore gate (AX38 4c)
      passes measuring restore without the solve and, under condition 9, without the unit-decay synthesis,
      on the Release build, in AX38 4c's register form (the entries it closes removed through `/fix-plan`);
      the solve time is in the staleness records. (phase-07c A2)
- [ ] The real-time path adopts each solved snapshot by atomic swap with an AQ4 crossfade, one step per
      solve, never mid-drag; the ISM update is never held behind the solve (tests); "settling" is shown
      while an update is pending (AX38 (iii)). (phase-07c A3)
- [ ] The interim level is never silence and never the AX16 level in the cases of condition 5 (test on
      layouts 4/5 and the absorbing-floor cube); the provisional-to-final step stays within D-C1's ruling.
      (phase-07c A4)
- [ ] Offline renders, bounces and `render_cli` wait for the final solve and are bit-identical run to run
      (AX5); an unreliable host offline signal is recorded in the render log. (phase-07c A5)
- [ ] If E_b is saved in state: the state-version AX applied, old state fixtures still load (Phase 07 rule).
      (phase-07c A7)
- [ ] E_b bit-identical between modes and ears (AX44); allocation tracker, TSan `[conv],[pipeline]`,
      pluginval strictness 10 and auval pass. (phase-07c A8)
- [ ] Condition 10: the `[pipeline]` test shows `reset()` and `setNonRealtime(true)` never wait on the
      builder and never build; a realtime reset keeps the current IrSet (output never silent); the two-order
      test and the transient-memory record; TSan `[pipeline]` green; the AX38 (i) register entry removed
      through `/fix-plan`. (phase-07c A10)
- [ ] Condition 11: the `SPATIAL_HOST_TRACE` option builds, is OFF by default, is absent from release
      artefacts (`pytest tools/ci` guard) and leaves the realtime path allocation-, lock- and log-free
      (tracker test); the per-host run itself is a person's action and does not gate this phase. (phase-07c A11)
- [ ] Condition 12: the `[pipeline]` test shows the gate held during the solve only; `buildRoomIR` bit-identical
      to its stages; TSan `[pipeline]` with overlapping ISM and synthesis green; records (b)–(d), (f) and (g)
      printed on three OSes, none asserted; the AX38 (i) register entry G-1 removed through `/fix-plan`. (D-G1,
      A12)
- [ ] Condition 7, the 07c re-pin: after conditions 9 and 12 land, the restore gate's growth-bound baselines,
      the ±5 % flutter window, `kSolveWarn` and its `solveRefMs` baselines re-derived from ≥ 3 in-window runs
      (one run PROVISIONAL, printed not asserted; never a red or out-of-window run as a baseline), and the
      macOS trigger (2 172 ms) re-derived, with a CHANGELOG reason. (AX38 4c; D-Q5)

## Listening / manual checklist

- [ ] Drag a source in a large room: the early part follows at once; the tail level updates after the drag.
      (phase-07c L2)
- [ ] Bounce the same project twice: the bounces are identical and match playback after settling. (phase-07c L3)

## Contractor review focus

- Threading of the moved solve (no real-time wait, no lock on the audio thread, the AX38 gate's classes
  after the move; the gate's scope, solve only, and the stage split, condition 12) (phase-07c F1; D-G1)
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
