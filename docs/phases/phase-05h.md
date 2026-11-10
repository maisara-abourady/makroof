# Phase 05h — Tail-level switch implementation (the B11 switch, remainder of phase 05b)

Size: **L** (the implementation that did not fit phase 05b's second session; split into `phase-05i.md` if
it cannot be finished in two sessions, CLAUDE.md) · Depends on: 05b (`done (not promoted; tail-level
switch specified in phase-05h)`, with this split), 05f, 07 `done` · Read first, in this order:
`CLAUDE.md`; this file in full; `docs/phases/phase-05b2.md` §0 (why the switch exists, what it fixes and
how much) and §3 (the decisions as posed and settled); `docs/BUILD_PLAN.md` §2 **AX37–AX46** (the settled
decisions: the text to implement), **AX16, AX21, AX22, AX36, AQ10, AX4, AX5, AX11, AX17, AX18, AX20, AX28,
AX6**, §5 **B11, B12, B15–B18**; `docs/phases/phase-05b.md` (scope 0, 4 and the AX36 notes);
`docs/validation/report-phase05b.md`; `docs/validation/report-phase05.md` §6a; `docs/review/phase-05b2/`
(decision files 13, 15, 34, 37, 39, 41 and the packet 40); `docs/review/ledger.md` blocks of phase 05b
session 2 (P05B2-…); PRD NFR-1, NFR-2, NFR-3, NFR-6, NFR-8, FR-SIM-2, FR-SIM-6, FR-3D-3, FR-3D-4.

Created on 2026-11-10 under phase-05b2 §8's split rule (the named split point: section 3's decisions and
R1 committed; the implementation did not fit phase 05b's second session). Phase 05b closes without any
`src/sim` matching change; this phase carries the implementation in phase-05b2's level of detail.

---

## 0. What this phase does (one paragraph; the full case is phase-05b2 §0)

The Phase 04 tail level is set by energy matching against image-source entries, and the AX16 scattered
entries mis-set it by up to +3.87 dB (Kuttruff Table 5.2 layout 4 at s = 1) and −1.17 dB (layout 5)
against an independent tracer, while the propagated diffuse energy (`ref_hybrid`) agrees within 0.08 dB
(15 (A) cases, 500 Hz–2 kHz, one pair each; report-phase05b §5). This phase replaces the AX16 scattered
entries in E_target by the propagated diffuse energy (AX37), computed in `src/sim` by the seeded Monte
Carlo estimator of AX39–AX44, under the build gate and memory ceiling of AX38, with the agreement,
regression and bias gates of AX42, AX43, AX45 and AX46. The early part stays specular-only (AX21).

## 1. Settled — do not reopen (cite, don't re-derive)

From phase 05b (phase-05b2 §1):
- Gate (B) fails (initial α, three BRAS rooms: EDT Δ̂ +0.816 jnd > δ = 0.25; CR4 +1.756 > 1 jnd) →
  early rendering **not promoted**; AX21 stands.
- Gate (A) per bin and the scope 5 bias trigger: "not evaluated (compute limit, AX36 (b))".
- Window check: branch (i); hybrid E_target within 0.08 dB of the tracer (phase-05b2 §0.1).
- Tracer (`tools/acoustics/tracer.py`, seed 0x05B7) and its committed statistics; self-checks
  (s = 0 passes; s = 1 diagnosis vs Table 5.2 column, ledger DB-1 open).
- ℓ ladder and its certification rule per quantity (AX36); compiled kernel
  `tools/validation/hybrid_fast.py` (= `ref_hybrid` to 1e-7; numba offline).
- B12: Eyring stays. AX22/N_cap: unchanged. Mixing-time rule: unchanged. Contract unchanged.
- Maisara 2026-11-09: build the switch (option (b)). AX36 accepted (Maisara 2026-11-09).

Decided in phase 05b session 2 (board decision loop, `docs/review/phase-05b2/`; Maisara 2026-11-10,
verbatim: "I accept the board's answer by definition."; ledger P05B2-M-01…07):
- **AX37 (D-T5):** E_target = specular entries + propagated diffuse energy in all 8 bands (5.1, with the
  RAII FTZ/DAZ guard and the outer-band tracer check); k_real and the AX22 fallback stay on the AX16
  entries (5.2); `bandsAxisShares` from specular entries only, Phase 08 gets E_b and t_mix,e only (5.3);
  `open_field` gets the generic outcome, with the finite-floor check (5.4).
- **AX38 (D-T4):** ≤ 1 GB transient per diffuse solve, one solve per process through the three-class gate
  (`reset()` in the synchronous class); ≤ 128 MB additional resident; gate wait in the staleness metric and
  "settling"; W1/W2 include the whole diffuse computation (AQ10's 50 ms target unchanged); the 100 m
  memory gate, the records and their escalation; the synchronous restore gate at the two gated 100 m,
  96 kHz builds is **blocking** (Challenge 1 = yes, AQ10 amended).
- **AX39 (D-T1.1):** the seeded Monte Carlo estimator, the ℓ → 0 form of `ref_hybrid`, with the
  determinism package D1–D7 (64-history blocks) and Seat 7's wording.
- **AX40 (D-T1.2):** fixed key; E_target does not depend on `tailSeed`.
- **AX41 (D-T1.3):** the joint path-count rule (pilot sized in work, fresh final range, integer stop test
  and N_cap, cap hit := N_need > N_cap, "floor truncated" reported separately, realised-work assertion);
  W_max provisional 3.05 M image evaluations per emitter (W_scene 6.10 M, Q2a (A)); n\*_max 1 024
  (Q2b (i)); both re-derived once from the C++ cost.
- **AX42 (D-T1.4):** τ = 0.25 dB; target SE 0.083 dB.
- **AX43 (D-T1.5):** 70 cases / 560 case-bands, z_FW 4.290, stage 2, no reseed; the reported set; CI reports.
- **AX44 (D-T1.6):** the NW-4C+ blend; both-near at 0.70 m; the note U with the union VOV; Seat 6 (i)–(iii);
  the GA-limit text.
- **AX45 (D-T6):** the fixed room set, 72 case-bands, z_FW 3.81, Seat 7 (i)–(iii), M-2.
- **AX46 (D-T2, Q1 (a)):** AX36's < 1 % rule on the estimator's bias, checked in CI per band and case class.
- **AX36 (c) resolved:** R1 certified at 2.5 m in CR2, CR3 and CR4 at 500 Hz–2 kHz at the AX28 /
  Phase 05 positions (CR4 2.5→1.25 m E_target change 0.140 %, report-phase05b §5b); R2 = D-T1.1 (AX39).
- **D-T3 not needed** (the estimator covers the whole AX6 range; holds under Q2a (A), ledger P05B2-M-07).
- **AX16 switched** (on implementation here); AX21 stands; AX5 note (cross-architecture agreement of the
  estimator rests on D1–D7).
- Q2a (C), moving the diffuse solve off the synchronous restore and prepare, is phase-13 scope 13, not here.
- Phase 08 may precede this phase on Seat 4's conditions (i)–(iv) of AX37 (5.3); if it does, this phase
  re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs phase-08 item 8 (scope 10).

## 2. Raise with Maisara (first message and PR)

1. D-H1's outcome (section 3), **only if** it changes her Q2a (A) or Challenge 1 answers (W_max sized to
   the restore watchdog; the blocking 100 m, 96 kHz restore gate). Otherwise none.
2. **The AX38 4c escalation** (conditional on the C++ records, scope 6): the full-rebuild records go to
   Maisara against the 1 / 3 / 10 s marks, labelled **UI response-time anchors (Card et al. 1991), not
   audibility limits**, with Table 15.1's conditions stated (its 3 s row covers only translational
   movement > 1 m, derived from 30–50 cm/s VR movement, has no row for room-geometry or material edits,
   and is applied to full rebuilds by extension only); any room above 3 s is named as a finding.
3. **AX38 (iv) load time** (conditional): if the 8-instance, 100 m time until the last instance is
   audible at project load exceeds 10 s, it goes to Maisara before the first release (also phase-13
   "Raise with Maisara" item 3).

## 3. Decisions before implementation

Run through the decision loop (`/fix-plan` step 3; `docs/board/README.md`) and record as an AX change
through `/fix-plan` before the restore gate is implemented. Not decided by the implementer alone, and not
after seeing the gate's result.

- **D-H1 — Margin between W_max and the blocking restore gate** (interrogator plan-diff check,
  `docs/review/phase-05b2/41-interrogator-plan-diff-check.md`, correction 1; ledger P05B2-FX-08).
  - The blocking restore gate (AQ10 amended, AX38 4c: 14 × t_restore ≤ 30 s at 100 m, 96 kHz) and
    W_max sized to the same budget at the worst OS build (AX41: (2.143 − 1.884)/2 per emitter) meet with
    **no margin**.
  - Prototype: at the gated 100 m scenes realised work is 0.986–0.993 W_scene, so a restore is
    ≈ 2.141 s and 14 × 2.141 = 29.98 s. At the realised-work ratio AX41 allows (≈ 1.05): ≈ 30.2 s, so
    the block fails by design. The 1.884 s build is a best of 3 (BUILD_PLAN §0 row 07).
  - The W_max re-derivation rule must state the margin for the realised-work ratio and for the spread of
    the restore measurement; otherwise the block fails on timing noise.
  - Decided by the board loop from the C++ measurements (C++ cost per evaluation, realised against
    planned work at block 64, restore spread) before the gate is implemented. A change to W_max or to the
    gate's form goes to Maisara only if it changes her Q2a / Challenge 1 answers (section 2).

## 4. Scope

1. **`src/sim` implementation** of the D-T1 formulation (AX39–AX44: the seeded Monte Carlo estimator,
   the D1–D7 determinism package with 64-history blocks, the joint path-count rule with the integer
   stop test and N_cap, the near-listener blend and `TailMatch.approximate`), generic (NFR-8), in
   `src/sim/tail/` (or a new `src/sim/diffuse/` unit), no JUCE, no allocation on the audio thread (it runs
   on the builder thread only), deterministic (AX5: the noise tail keyed by `tailSeed`; the estimator's
   key is fixed and independent of `tailSeed`, AX40), no NaN/Inf/denormals, contract unchanged (no new
   scene fields: s and α already exist; anything more is a contract change and Maisara's). The AX37 (5.1)
   RAII FTZ/DAZ guard in `buildRoomIR` and its `[pipeline]` test.
2. **The AX38 diffuse-solve gate** in the JUCE-free pipeline (three classes, `reset()` in the synchronous
   class, cancellation on `quiesce()`, offline waiters never coalesce) and its tests. Before the gate's
   offline path is implemented, the researcher answers whether any host runs a freeze or offline render,
   or calls `reset()`, on a thread that also serves the real-time graph (ledger P05B2-T5T4-61). The
   blocking restore gate is implemented only after D-H1 (section 3) is recorded.
3. **Matching switch** per D-T5 (AX37) in `planEmitter`/`matchTail`; k_real and the AX22 fallback stay on
   the AX16 entries (AX37 (5.2)); `bandsAxisShares` from specular entries only, labelled (AX37 (5.3));
   diagnostics (`render_cli --diagnostics`) gain the diffuse E_target per band beside the AX16 one, and the
   AX41 diagnostics (n\*, N, achieved SE, R, VOV, slope, cap hit, floor truncated, pilot floor, both-near,
   realised work against W_scene), so the switch is observable (atomicity rule: section 8).
4. **Agreement tests** (Catch2): C++ E_target vs `ref_hybrid.target_hybrid` (exported reference values
   as a small golden, generated by a script with its reason in `tests/golden/CHANGELOG.md`) on the AX43
   suite (70 cases, 560 case-bands, z_FW 4.290, stage 2, no reseed; Release, hidden tag, three OSes;
   smoke cases in Debug, ASan and TSan) to τ = 0.25 dB (AX42); the AX46 bias check per band and case
   class; the AX45 regression gate (72 case-bands, z_FW 3.81); and C++ E_target vs the tracer's committed
   window energies (`phase05b.json` cases) within the B11 window tolerance (±1 dB), independently of the
   reference hybrid. Also, before the goldens:
   - the **reported set** (AX43: the layout 4/5 near-wall cases; W1, `club` and `living_room` both-near at
     0.1, 0.3 and 0.5 m), which also supplies the joint-rule replicates in the closed 100 m cubes (Seat 2's
     C15 check ran on the per-emitter rule) and the per-class replicate p95 the AX44 note text uses;
   - the independent **near-corner reference** (Seat 2) and W1 both_corner asserting the cap flag (Seat 5);
   - the **M-2 tracer runs** on the five mixed-α Phase 04 rooms (AX45), reported;
   - the AX37 (5.1) (ii) outer-band tracer check (125 Hz, 4 kHz, 8 kHz; layouts 4 and 5 at s = 1),
     reported before any golden is updated; a failing band goes to D-T2 and Maisara, never back to AX16;
   - the AX37 (5.4) `open_field` finite-floor check, replacing the "no tail" asserts.
   C16c (U at n\*_max 8 000 with the union VOV) is already reported (`38-orchestrator-C16c.md`: no change).
5. **Goldens and validation:** every golden whose tail level changes is updated through
   `tools/ci/update_goldens.py --reason "phase 05h: tail level from the propagated diffuse energy (AX16
   switch)"`; `phase04_open_field_omni` only after the AX37 (5.4) sentinel-margin check; new goldens, each
   created by script with its reason in the CHANGELOG: the agreement reference, ΔL_ref (AX45), the D5
   face-hash and per-case n\* / N golden, the RNG KAT vectors (AX39); the BRAS validation
   (`tools/validation/run_validation.py`, nightly) is re-run and `report-phase05.md` regenerated, printing
   the Monte Carlo SE beside the ensemble spread (Seat 9, AX40); AQ9 results are reported before/after (no
   gate change: AQ9 is reported, B11 (B) is not re-run unless the decision loop says the switch affects it).
6. **Costs:** W1/W2 (AQ10) including the diffuse share, peak memory per instance at the AQ10 room, CR4
   and the largest supported room, the AX38 4c records and the AX38 (iv) multi-instance records, the flags
   at the gated scenes and the realised work against W_scene (AX41), recorded in §0 row 05h; the AX38 4c
   escalation applied to them. **C++ re-derivation** of W_max (from the C++ cost at the CI runner's pool
   size, the worst gated cost and the worst OS restore build, with D-H1's margin) and of n\*_max (from the
   C++ W1 measurement, diffuse share ≤ 25 ms for two emitters), once, pinned as cross-platform constants
   (AX41); the realised-work ratio pre-registered from C++ data before the first CI run. If n\*_max comes
   out below 1 000, it goes back to Seats 1, 3 and 4.
7. **Plan bookkeeping** through `/fix-plan`: D-H1's AX change; AX16 "switched" confirmed with the
   implementation; the re-derived W_max and n\*_max in AX41 (and AQ10's amendment if they move); §6 rows.
8. **Listening pack:** a `phase-05h` entry: Phase 04 tail level vs switched tail level, loudness-matched
   **not** (the level difference is the point), through the six Phase 04 rooms, `open_field`, the BRAS
   scene with the largest real ΔL_b (`bras_cr3_ls1_mp2`) and three synthetic concentrated-absorption
   rooms (Table 5.2 layout 4 at s = 0.4, layout 4 at s = 1 (the largest deficit, +3.87 dB) and layout 5
   at s = 1, as scenes), clicks and pink bursts, and one both-near omni render (listener and an emitter
   within 0.70 m of surfaces, AX44). The scene choice is listening content, not a gate.
9. **CI reports** (AX43, AX41): U at the default placement of every valid fixture; every fixture or preset
   where the pilot estimate ships; the cross-OS E_target comparison; the RNG known-answer test; the D5
   hashes with n\* and N; the pre-registered flags at the gated scenes.
10. **Only if Phase 08 went first** (AX37 (5.3), Seat 4 (iii)): re-render the binaural goldens, re-measure
    binaural W1/W2 and re-run phase-08 item 8; Phase 08's listening items on concentrated absorption,
    marked provisional there, are re-listened.

## 5. Acceptance criteria — automated

- [ ] D-H1 recorded as an AX change (ledger rows linked) **before** the restore gate is implemented.
- [ ] C++ E_target = `ref_hybrid` within τ = 0.25 dB (AX42) over the 70 pre-registered cases / 560
      case-bands at z_FW 4.290, with the pooled bias check and stage 2, no reseed (AX43; Release, hidden
      tag, three OSes).
- [ ] Bias check (AX46): mean signed deviation ≤ 1 % per band and per case class, pooled and per class,
      at the pre-registered test N (3·SE ≤ 1 % − ℓ_ref); classes with ℓ_ref ≥ 1 % reported.
- [ ] C++ E_target vs tracer within ±1 dB on the 15 (A) cases (deterministic test on committed data).
- [ ] Rooms where AX16 is exact per reflection order (uniform α) unchanged within D-T6's bound: the AX45
      gate, |ΔL_C++ − ΔL_ref| ≤ 0.25 dB per emitter and band over 72 case-bands at z_FW 3.81, stage 2;
      mixed-α rooms checked against the tracer (M-2) / `ref_hybrid` and reported (D-T6), not tuned.
- [ ] Determinism (AX39): RNG known-answer test, D5 face-sequence hashes with the per-case n\* and N
      equal on the three OSes, cross-OS E_target comparison.
- [ ] U silent at the default placement of every valid fixture (AX44, Seat 6 (ii)); W1 both_corner
      asserts the cap flag; the pre-registered flags at the gated scenes (AX41).
- [ ] Realised-work assertion at the gated scenes: realised work / W_scene ≤ the ratio pre-registered
      from C++ data before the first CI run (AX41).
- [ ] `open_field`: the AX37 (5.4) finite-floor check and the −60 dB check (PR CI, three OSes); the
      outer-band tracer check (AX37 (5.1) (ii)) reported before any golden.
- [ ] `render_cli --diagnostics` reports the diffuse E_target per band beside the AX16 one, and the AX41
      diagnostics (test).
- [ ] Same scene + seed → bit-identical IR on the same platform; no NaN/Inf/denormals; allocation-free
      audio thread (existing tracker test) unchanged; the FTZ on/off `[pipeline]` test bit-identical per
      platform (AX37 (5.1)).
- [ ] Gate (AX38): the debug assert and the real-time-beside-gate test (zero allocations, gate never
      touched), covering `reset()`; the two-order output test, one pipeline offline; TSan `[pipeline]` with
      two pipelines, one switching to offline mid-solve.
- [ ] W1/W2 (with the diffuse share) and the AX38 records recorded (AQ10). Memory block (AX38 4c): the
      peak working-set delta of the larger of the two gated 100 m, 96 kHz builds ≤ 1 GB (Linux;
      recorded on macOS and Windows), `ismFallback` stated per emitter.
- [ ] **Blocking** (AQ10 amended, AX38 4c): the synchronous state restore at the two gated 100 m, 96 kHz
      builds (the AX22-fallback (flutter) scene and the closed low-α cube), 14 × t_restore ≤ 30 s, with
      D-H1's margin.
- [ ] Goldens updated only through `update_goldens.py` with the reason; nightly BRAS green; report
      regenerated.
- [ ] pluginval strictness 10 and auval still pass (rebuild cost changes the builder's timing).

## 6. Listening checklist (Maisara)

- [ ] In the concentrated-absorption scenes, the switched tail's level sounds natural against the early
      part (no "reverb pasted on top", no tail that is too weak); in uniform-α rooms nothing
      audible changed (D-T6); in the mixed-α Phase 04 rooms (e.g. club, concert_hall_box) any change
      sounds like a correction, not an artefact.
- [ ] No new seam at the handover (the level change is at t_mix,e).
- [ ] Moving a source or resizing the room under automation: no level jumps (Phase 10 will gate this;
      listen now).

## 7. Contractor review focus

Equivalence of the `src/sim` formulation to the validated model (not just to its numbers on a few
cases); the independence of the tracer comparison; the AX22 interaction (AX37 (5.2)); memory scaling at
100 m (AX38); determinism (the D1–D7 package, AX39); the AX38 gate (threading, three-class order,
`reset()`); the cap-hit and floor-truncated flags (AX41); D-H1's margin; no per-scene logic.

## 8. Risks and atomicity

- The plan is recorded first: done (AX37–AX46, committed in phase 05b). D-H1 is the one decision still
  open, and it blocks only the restore gate.
- **Atomicity:** the matching change does not land in `src/sim` (commit to the branch) without, in the
  same push, the `ref_hybrid` agreement test, the tracer test and the updated goldens, and the PR is not
  opened before a manual nightly BRAS run on that push is green (CLAUDE.md "When CI runs").
- The C++ cost puts n\*_max below 1 000 → the conflict returns to Seats 1, 3 and 4 (AX41).
- The realised-work assertion or the restore gate fails at the pinned W_max → back to D-H1, not a
  loosened gate.
- The outer-band tracer check fails in a band → D-T2 and Maisara with numbers, never back to AX16.
- A default placement of a valid fixture raises U → the placement changes, not the predicate (AX44 (ii)).
- **Split rule (CLAUDE.md):** if this phase cannot be finished in two sessions, the remainder goes into
  `phase-05i.md` with the same atomicity rule.

## 9. Out of scope

Early rendering of scattered energy (not promoted; re-run rule AX36 (e)); per-band scattering (B10);
the tail decay rate (B12); Phase 08 directions beyond AX37 (5.3) (directional late tail: §5 B18); Phase 10
caching beyond what AX39 needs (a kernel cache only through an AX, AX38); a both-near fallback (§5 B15);
moving the diffuse solve off the synchronous restore and prepare (Q2a (C), phase-13 scope 13); any
per-scene tuning.

## 10. Definition of done

Section 5 all checked with CI evidence; §0 row 05h `done (tail-level switch implemented)` with the
numbers; this phase's PR with the listening checklist, the contractor focus, the AX/ledger links and the
"Raise with Maisara" item if it applies.
