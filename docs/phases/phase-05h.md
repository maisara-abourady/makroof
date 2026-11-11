# Phase 05h — Tail-level switch implementation (the B11 switch, remainder of phase 05b)

Size: **L** (the implementation that did not fit phase 05b's second session; split into `phase-05i.md` if
it cannot be finished in two sessions, CLAUDE.md — **split applied 2026-11-10 at the end of session 2:
the remainder is [`phase-05i.md`](phase-05i.md)**) · Depends on: 05b (`done (not promoted; tail-level
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
  96 kHz builds is **blocking** (Challenge 1 = yes, AQ10 amended; a board answer, decider files 47 and
  51, with the AX38 4c conditions).
- **AX39 (D-T1.1):** the seeded Monte Carlo estimator, the ℓ → 0 form of `ref_hybrid`, with the
  determinism package D1–D7 (64-history blocks) and Seat 7's wording.
- **AX40 (D-T1.2):** fixed key; E_target does not depend on `tailSeed`.
- **AX41 (D-T1.3):** the joint path-count rule (pilot sized in work, fresh final range, integer stop test
  and N_cap, cap hit := N_need > N_cap, "floor truncated" reported separately, realised-work assertion);
  W_max provisional 3.05 M image evaluations per emitter (W_scene 6.10 M; Q2a (A) now: the restore budget
  less D-H1's margin, pinned, re-derived once under (C)); n\*_max 1 024 (Q2b (i)); both board answers
  (decider files 43, 47, 51), both re-derived once from the C++ cost.
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
- Q2a (C), moving the diffuse solve off the synchronous restore, prepare and `reset()`, is its own phase,
  [`phase-07c.md`](phase-07c.md), before the first public release (a board answer, decider files 47 §4
  (iii) and 51), not here.
- Phase 08 may precede this phase on Seat 4's conditions (i)–(iv) of AX37 (5.3); if it does, this phase
  re-renders the binaural goldens, re-measures binaural W1/W2 and re-runs phase-08 item 8 (scope 10).

## 2. Raise with Maisara (first message and PR)

1. **Seat 1's floor at a gated scene** (section 3, decider file 53 §1), on either trigger: the re-derived
   W_max leaves a gated scene where the floor is not met (i) after D-H1's margin, or (ii) after any growth
   of the non-diffuse build. It goes to her before any range change, with the SE, the VOV and the
   replicate p95. A floor failure already present in the starting state (the joint-rule replicates of
   the reported set) is recorded as a finding and escalated once. Otherwise none (a margin above about
   20 % of W_max returns to the seats, not to her).
   **At the pinned W_max item 1 does not fire** (H1-F3, decider file 19, interrogator file 21): the gated
   cube `cube100_lowalpha0.05_s0.3` meets the floor via clause (d) (p95 0.250 / 0.178 dB, SE 0.117 /
   0.115 dB; `docs/review/phase-05h/10-orchestrator-clause-d-replicates.md`) and W_max was not cut.
   **Starting-state finding of the reported set, recorded once here beside item 1 and in the 05h PR's
   Raise-with-Maisara section:** the α 0.05 / s = 1 cube (`cube100_lowalpha0.05_s1`, a scene that is not
   gated) fails the floor in the starting state (SE 0.381 / 0.384 dB, VOV 0.178 / 0.183, p95 0.701 /
   0.810 dB); it is a synthetic bound no fixture or preset approaches, buildable by a user (FR-3D-4, AQ3,
   AX6), where AX44's note U is raised; it is never a reason for a range change or a W_max cut (AX38 4c).
   Item 1 fires later only on D-H1 (ii)'s lines: the SE crossing 0.33 dB or the p95 crossing 1 dB at the
   gated cube, or the p95 crossing 1 dB at the reported s = 1 cube.
2. **The AX38 4c escalation** (when the C++ records exist, scope 6): the full-rebuild records go to
   Maisara against the 1 / 3 / 10 s marks, labelled **UI response-time anchors (Card et al. 1991), not
   audibility limits**, with Table 15.1's conditions stated (its 3 s row covers only translational
   movement > 1 m, derived from 30–50 cm/s VR movement, has no row for room-geometry or material edits,
   and is applied to full rebuilds by extension only); any room above 3 s is named as a finding.
   If the records are not in this phase's CI run, the evaluation is carried by phase-05i (its scope 4)
   and the decider answers it for Maisara under `docs/board/README.md`.
3. **AX38 (iv) load time** (conditional): if the 8-instance, 100 m time until the last instance is
   audible at project load exceeds 10 s, it goes to Maisara before the first release (also phase-13
   "Raise with Maisara" item 3). If the (iv) record is not in this phase's CI run, phase-05i (scope 4)
   carries it the same way.

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
  - **Margin rule (board answer, decider files 47 §4 (i) and 51 §4 item 3):** the margin comes out of
    W_max, not the gate; it is set from C++ data before the gate exists, from the pre-registered
    realised-work ratio (AX41: about 1.05) and the restore spread taken from the worst of at least 10
    runs, not a best of 3; it is reported with its cost, the SE at each gated scene and in layouts 4/5.
  - **20 % trigger:** if the margin would take more than about 20 % of W_max [Hyp, Seat 3], it comes back
    to the seats with the C++ numbers; their options are to accept the smaller W_max or to bring (C)
    (phase-07c) forward, never a time cap or a narrower room range. **Expected:** the margin will
    probably exceed the trigger: a 3 % spread on the 1.884 s build is 0.057 s, 22 % of the 0.259 s
    diffuse budget, plus about 5 % for the realised-work ratio, about 27 % of W_max; a 27 % smaller W_max
    raises the capped-scene SE by about 1/√0.73, about 17 % [Inferred] (e.g. layout 4 from about 1.33 to
    1.56 dB, the low-α cube from about 0.50 to 0.58 dB) (file 51 §3).
  - **Decided (2026-11-10; D-H1 (i)–(v), decider `docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md`,
    interrogator `21-interrogator-D-H1-D-H2-r2.md` SURVIVES; H1-F1–H1-F3 answered for Maisara, open to her
    veto; recorded in AX38 4c, AQ10 and AX41):** (i) the gated closed low-α cube is
    `cube100_lowalpha0.05_s0.3` (α 0.05, s 0.3; `ismFallback` false on both emitters, asserted); the s = 1
    cube stays in the reported set with a p95 > 1 dB escalation line; (ii) "any further rise" is a record
    (below); (iii) the realised-work ratio is **1.02**, pre-registered from the C++ measurements (0.935 /
    0.991 / 0.986 at flutter / s 0.3 / s 1); (iv) W_max **3.05 M per emitter** and n\*_max **1 024** are
    pinned: the (A) formula from the C++ cost gives Linux ≈ 2.4 M, Windows ≈ 5.8 M and no W_max ≥ 0 on macOS
    (2.1429 − 2.3277 = −0.185 s), so **no margin is taken out of W_max** and the 20 % trigger above does not
    apply; the gate carries a defect register instead (v); phase-07c re-derives W_max once under (C), only
    after the AX38 4c 3-minute bounce record is in its packet; (v) the restore gate runs on all three OSes in
    the register form (section 5 "Blocking"): strict where the recorded value at the pinned W_max is
    ≤ 29.1 s; a registered defect with the growth bound (median-of-10 restore ≤ 1.10 × the recorded median
    (since RG-1: the pinned baseline median, (b))) elsewhere (Linux cube 30.27 s, closes at 07c; macOS cube
    33.40 s, closes at phase-07c condition 9 / 07d or Phase 13); the named finding (the unit-decay synthesis
    in `tail::BandNoiseGenerator`, 95.5 % of the 3.29 s non-diffuse 100 m / 96 kHz build) and its remedy,
    phase-07c §5 condition 9; phase-07c is the next phase after this one. H1-F1: 14 × t_restore ≤ 30 s is the
    project's own convention (pluginval's watchdog resets per restore), 14 a kept constant. H1-F3: section 2
    item 1.
  - **Seat 1's floor at a gated scene** (decider file 53 §1, exact text). At each gated 100 m build of
    AX38 4c, Seat 1's floor counts as **met** when the achieved SE is ≤ 0.33 dB per emitter and band and
    at least one of these holds:
    - (a) the pilot SE is ≤ target/3 (0.028 dB), so the VOV test does not apply;
    - (b) the pilot VOV is < 0.1;
    - (c) the final-range VOV is < 0.1;
    - (d) 30 replicates of the shipping rule against a long run give p95 |error| ≤ 1 dB.

    **Escalation.** If, after D-H1's margin or any growth of the non-diffuse build, the re-derived W_max
    leaves a gated scene where this floor is **not met**, the result goes to Maisara before any range
    change, with the SE, the VOV and the replicate p95. It is never fixed by a time cap, a narrower range
    or a formulation seam.

    **Starting state (D-H1 (ii), R-e; decider file 19, interrogator file 21; Seat 5 file 17 L155–158).**
    The starting state per gated scene and emitter is the **record** in
    `docs/review/phase-05h/10-orchestrator-clause-d-replicates.md` (cited in the 05h PR and the ledger):
    the fixed-key achieved SE (deterministic, AX40 / D7; the cross-OS E_target comparison of phase-05h scope 9 shows
    whether it differs by OS) and the replicate p95 (30 disjoint pre-registered streams). It is a record,
    not a golden: no test asserts on it, no file is regenerated, and the margin report reproduces it as its
    baseline column. If the floor already fails there at a gated scene, that is recorded as a finding and
    escalated once (at the pinned W_max it does not fail: H1-F3; the reported s = 1 cube's failure is a
    finding of the reported set, recorded beside phase-05h §2 item 1). **Recorded** (a flagged line in the
    margin report of every later run that re-derives W_max or re-baselines the non-diffuse build, beside
    the baseline column): any rise of the achieved SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB above the
    starting state (two constants in plan text). The starting-state values are constants in the test, per
    gated scene, with the file-10 provenance in a comment, re-pinned with a CHANGELOG reason whenever W_max
    or n\*_max is re-derived (Seat 5, file 17 L155–158). **Escalated** (phase-05h §2 item 1, to Maisara with
    the SE, the VOV and the p95): the achieved SE crossing 0.33 dB, or the replicate p95 crossing 1 dB
    (1 jnd of G, Vorländer Table 6.1), at a gated scene, or the p95 crossing 1 dB at the reported s = 1
    cube. Nothing else escalates.
  - **Clause (d) at the gated cubes** (Seat 1, `docs/review/phase-05b2/55-seat1-confirm-clause-d.md`):
    Seat 1 accepts clause (d) at the gated closed 100 m cubes at s = 0.3, on two conditions: the
    replicates run the shipping rule as built, on disjoint pre-registered streams; and the check is
    repeated on the C++ build.
  - **Closed by D-H1 (2026-11-10; decider file 19, interrogator file 21)**, the two premises interrogator
    file 54 left open:
    - the gated closed low-α 100 m cube is pinned in AX38 4c as `cube100_lowalpha0.05_s0.3` (α 0.05,
      s 0.3; D-H1 (i), P-a′); the s = 1 cube (`cube100_lowalpha0.05_s1`) stays in the reported set, its
      SE / VOV / p95 printed beside the gated cube's, a p95 > 1 dB there escalated like a gated scene;
    - "any further rise" in Trigger 1's starting-state clause is the record above (D-H1 (ii), R-e): rises of
      the achieved SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB above the file-10 starting state are
      printed, not escalated; only the 0.33 dB / 1 dB crossings escalate.

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
   blocking restore gate is implemented only after D-H1 (section 3) is recorded. **Solve seam (Seat 5,
   AX38 4c / phase-07c condition 2):** restore, prepare and `reset()` invoke the diffuse solve through one
   function, so phase-07c can move it off the synchronous path.
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
   escalation applied to them. W_max and n\*_max are pinned by D-H1 (iv) (3.05 M per emitter, 1 024; no
   margin: the (A) formula gives no W_max ≥ 0 on macOS, section 3) as cross-platform constants (AX41); the
   realised-work ratio 1.02 is pre-registered from the C++ data (D-H1 (iii)). n\*_max came out at 1 024
   (W1 diffuse share ≤ 14 ms), so the "below 1 000 → Seats 1, 3 and 4" rule did not fire.
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
    binaural W1/W2 and re-run phase-08 item 8. This also carries phase-08 scopes 9 and 10, which Phase 08
    could not meet before this phase: W1/W2 per output mode with the diffuse share and the AX38 (iv)
    records in binaural mode with the gate wait shown separately (phase-08 scope 9); the blocking restore
    gate measured in the heaviest output mode with one W_max constant for all modes (phase-08 scope 10).
    If the heaviest-mode build makes the pinned W_max fail the gate, phase-07c lands before this phase's
    re-rendered binaural goldens are frozen, or those goldens carry the SE-derived tolerance (the 08-first
    order of AQ10 / AX38 4c; in the 05h-first order the same rule applies to Phase 08's goldens).
    Capped-room binaural goldens carry the SE-derived tolerance unless phase-07c has landed before they
    are frozen (phase-07c condition 8).

## 5. Acceptance criteria — automated

- [ ] D-H1 recorded as an AX change (ledger rows linked) **before** the restore gate is implemented.
- [ ] C++ E_target = `ref_hybrid` within τ = 0.25 dB (AX42) over the 70 pre-registered cases / 560
      case-bands at z_FW 4.290, with the pooled bias check and stage 2, no reseed (AX43; Release, hidden
      tag, three OSes). **Pooled bias check (D-H3 (a), H3-F1; decider file 27, interrogator file 28):** the
      additive bound, per band: |mean (C++ − ref) in dB| ≤ 3·SE_pool + mean ℓ_ref over the M gated
      case-bands, the catch (the right-hand side) printed per band beside the mean deviation and restated
      in §0 at each golden round, never pinned (a board return above 0.02 dB); the as-written statistic
      (mean z against 3/√M), the per-class means in both forms, the pooled z′ and the per-room z′ (the
      golden's `room` column) printed as records, never checked, with the |mean z′| > 3 label and the
      rooms' sign count (a labelled room or every room of one sign, with the per-case checks green, reopens
      the clause by a board round; the per-room form (e′) is the pre-registered alternative). Applied only
      after the pre-registered application run read 'within' in every band (it did: `agree_full5.log`).
      **Scope now (D-H2 (a), H2-F1; decider file 19, interrogator file 21):** gated on the
      subset with a certified two-rung reference (ℓ_ref recorded), listed per case-band in the agreement
      golden with its status; the rest 'reported (reference pending)', never dropped; the report prints
      '<gated> of 560 gated; <n> reported (reference pending)' (560 / 560 since phase 05i, which gated the 150
      BRAS pairs' outer case-bands; 410 / 560 after the session-2 golden round, all 28 cases at the 1.25 m rung;
      the four small rooms referenced at the 0.625 m rung, H3-F6); single-rung
      references printed with the fixed label `uncertified rung, no ℓ_ref, not pass/fail`, never asserted
      (AX43 (b)); the gated set keeps one per-band-α room and one mixed-s room, or the gap is reported.
- [ ] Bias check (AX46): mean signed deviation ≤ 1 % per band and per case class, pooled and per class,
      at the pre-registered test N (3·SE_class ≤ 1 % − mean ℓ_ref, SE_class estimator-propagated, AX46);
      classes with ℓ_ref ≥ 1 % reported. **Scope now (D-H2 (d)):** every class with ≥ 1 certified case
      (reference positions, absorbing face, small rooms, one-end near-wall (the c4 cross-check recorded
      passing: `docs/review/phase-05h/6-orchestrator-K20-certified-listing.md`, 2026-11-11, |rel. diff| ≤
      3.4e-6), and BRAS pairs (500 Hz–2 kHz; the outer bands certified in phase 05i, all eight bands));
      classes without one print 'not evaluated (reference pending)'; the 100 m class is the tracer comparison, labelled 'not evaluated
      at 1 % (compute limit)', never a pass; six classes labelled; the pooled figure labelled 'pooled over
      <n> of 6 classes'.
- [ ] C++ E_target vs tracer within ±1 dB on the 15 (A) cases (deterministic test on committed data).
- [ ] Rooms where AX16 is exact per reflection order (uniform α) unchanged within D-T6's bound: the AX45
      gate, |ΔL_C++ − ΔL_ref| ≤ 0.25 dB per emitter and band over 72 case-bands at z_FW 3.81, stage 2;
      mixed-α rooms checked against the tracer (M-2) / `ref_hybrid` and reported (D-T6), not tuned.
      **Scope now (D-H2 (a)):** the certified subset ('<gated> of 72 gated', 72 / 72 since
      the session-2 golden round, unchanged in phase 05i), the rest listed as 'reported (reference pending)';
      M-2 printed per band.
- [ ] Determinism (AX39): RNG known-answer test, D5 face-sequence hashes with the per-case n\* and N
      equal on the three OSes, cross-OS E_target comparison.
- [ ] U silent at the default placement of every room and preset fixture (AX44, Seat 6 (ii) as read by
      D-H3 (b), H3-F2), asserted by the D5 golden, and U with the five AX41 flags pinned at every fixture;
      `edge_values` and `open_field` are known, correct U cases (cap; K-b3), named by the golden's pinned U,
      the cause line printing the cause (cap / both-near / VOV_union ≥ 0.1), the movability record and the
      tail's energy after t_dir + 50 ms relative to the direct sound printed for every fixture (AX37
      (5.4)'s quantity: `open_field` −85 dB, `edge_values` −30 / −16 dB, `medium_room` +7 dB).
      `layout4_s1/both_corner` asserts the cap flag; W1 both_corner asserts U with its flags (n\* 1 024,
      N 1 024, N_cap 1 088, cap hit 0, floor truncated 0) pinned as constants in the records test with the
      file-13 provenance, re-pinned with a CHANGELOG reason at each W_max / n\*_max change (D-H3 (d),
      H3-F4); the pre-registered flags at the gated scenes (AX41).
- [ ] Realised-work assertion at the gated scenes: realised work / W_scene ≤ **1.02**, the ratio
      pre-registered from C++ data before the first CI run (AX41; D-H1 (iii)); W_pilot and W_final per gated
      scene exact in the D5 golden.
- [ ] `open_field`: the AX37 (5.4) finite-floor check at the validation N 2^23 (3·SE ≤ τ asserted per band,
      |dev| ≤ τ; the shipping-N render a labelled smoke test; decider file 44 QA) and the −60 dB check (PR CI,
      three OSes — the 2^23 cases in the `open-field-validation` job, the smoke cases in the python job
      (decider file 50)); the outer-band tracer check (AX37 (5.1) (ii)) reported before any golden.
- [ ] `render_cli --diagnostics` reports the diffuse E_target per band beside the AX16 one, and the AX41
      diagnostics (test).
- [ ] Same scene + seed → bit-identical IR on the same platform; no NaN/Inf/denormals; allocation-free
      audio thread (existing tracker test) unchanged; the FTZ on/off `[pipeline]` test bit-identical per
      platform (AX37 (5.1)) — the absorbent room is the named scene: dead_booth geometry, α 0.01 at 63 Hz /
      0.999 above, s 0.5 (the near-rigid 63 Hz band's long tail against the 8.6 ms fast bands, not
      absorbency; a uniformly absorbent room reads clear); the denormal flag asserted per architecture
      (x86-64 DE | UE in the FZ-off arm and DE clear in the FZ-on arm; AArch64 UFC in the FZ-off arm and IDC |
      UFC in the FZ-on arm, the D-H3 (c) form, decided by the K-c4 runs 42909003931 and 42921348351 (file 31);
      never red by design: SKIP when the calibration of file 20 L183 (3) fails; MSVC ARM64 SKIP, phase-13
      scope 8) with the calibration step and `ThreadPool(1)`; the `[probe-denormals-detector]` probe standing
      in `ci.yml` on three OSes, re-run on each path change; every pool share under the FTZ/DAZ guard
      (`ThreadPool::runShare`, D-H3 (c) (g)), re-probed in the same CI run before the PR (D5 hashes identical,
      cross-OS E_target within 1e-7), else the caller-only form (f) with the scene named (D-H3 (c), H3-F3;
      decider files 25, 27).
- [ ] Gate (AX38): the debug assert and the real-time-beside-gate test (zero allocations, gate never
      touched), covering `reset()`; the two-order output test, one pipeline offline; TSan `[pipeline]` with
      two pipelines, one switching to offline mid-solve. **AX38 (i) register entry (D-H3 (e), H3-F5):**
      `reset()` / `setNonRealtime(true)` delivered on the processing thread waits for the in-flight build,
      measured worst 2 664 ms (closed low-α 100 m cube, 96 kHz, Linux Release; 491 ms flutter; cancel
      points only in the diffuse solve, between 64-history blocks), and in the stale case builds
      synchronously (≈ 3.6 s): up to ≈ 6.3 s; the `[diffuse-quiesce]` hidden record prints the median-of-10
      wait against 1.10 × the recorded median per OS in the job summary (a print, never a CHECK); a
      test-build counter and summary line counts Synchronous-class entries from a thread that has run the
      realtime `process()` branch (never an assert); remedy phase-07c §5 condition 10; release rule: no
      build reaches a producer outside the team (beta included) while the entry is open.
- [ ] W1/W2 (with the diffuse share) and the AX38 records recorded (AQ10). Memory block (AX38 4c): the
      peak working-set delta of the larger of the two gated 100 m, 96 kHz builds ≤ 1 GB (Linux;
      recorded on macOS and Windows), `ismFallback` stated per emitter. **K-e12 record (AX38 4c finding,
      D-H3 (e)):** a room-or-material edit in flight, then a restore, at the two gated builds, worst of 10,
      three OSes, printed once, never a CHECK (the gate's restores are measured with the builder idle); in
      this phase's AX38 (iv) records if it fits, else phase-05i (scope 2) with the PR saying which. The
      AX38 (iv) records not produced here go to phase-05i (scope 2) the same way.
- [ ] **Blocking, in the register form** (AQ10 amended, AX38 4c; D-H1 (v) W-x′ and H1-F2, decider file 19,
      interrogator file 21; RG-1, decider files 64/66/68/70, interrogator files 65/67/69/71): the synchronous
      state restore at the two gated 100 m, 96 kHz builds (the AX22-fallback (flutter) scene and
      `cube100_lowalpha0.05_s0.3`), on the Release build on Linux, macOS and Windows, at the pinned W_max 3.05
      M (no margin taken from W_max), printing per OS and scene the min / median / worst of 10 restores, the
      worst-of-10 solve and 14 × (worst restore + worst solve). (a)–(b) (RG-1, 2026-11-11): On GitHub-hosted
      runners the restore gate asserts what is runner-independent and prints what is not. **Asserted every
      run:** the exact W_pilot / W_final pins and realised work ≤ 1.02 (AX41); per gated scene the unit-decay
      length and the FFT size n (`Fft::nextPowerOfTwo(length + 2·maxHalfLength)`), exact; 14 × worst-of-10
      restore ≤ 30 s at the flutter scene on every OS; and, on Linux and Windows only, median-of-10 low-α
      restore ≤ 1.10 × the pinned baseline median when the run's flutter median is within ±5 % of its pinned
      reference, else `NOT EVALUATED (runner)`. **Printed with WARNING, never asserted on hosted runners:**
      the low-α/flutter restore ratio above 1.20 × its pinned ratio; the per-scene solve median and its ns per
      evaluation (bound: AX38 4c, set in phase 05i); 14 × worst above 30 s;
      the absolute median above 1.10 × baseline where not asserted (macOS until Phase 13); the §5 (c) 'passes
      30 s' line. On macOS two consecutive runs with the low-α median above 2 172 ms (1.15 × the mean of the
      four measured macOS medians, rounded down; re-derived at the 07c re-pin) are a defect under (d), remedy
      named, through `/fix-plan`; the 30 s warning on a listed entry is its recorded state until phase-07c,
      not a trigger; the printed growth line uses the in-window baseline 1 817 ms. The register entries (Linux
      30.27 s, macOS 33.40 s, Windows 36.73 s; remedy phase-07c conditions 9–10; closing phases unchanged)
      stand. One machine-readable line per OS/scene per run; §0 row 05h carries the latest figures and the
      counts; a WARNING run is named in the PR. Baselines: flutter reference and ratio the mean of the
      measured runs per OS (Linux 701 ms / 3.05, Windows 737 / 2.83: runs 42909003931, 42924781618,
      42935789745, 42949252041, Windows also 42942694523; macOS 484 / 3.75: runs 42924781618, 42935789745,
      42949252041); baseline median the mean of in-window runs (Linux 2 068, Windows 2 028; macOS 1 817, print
      only); never a red or out-of-window run; re-pinned only when the restore path changes, one run
      PROVISIONAL, ≥ 3 runs with a CHANGELOG reason; the ±5 % window and the solve bound re-derived from ≥ 3
      in-window runs at the 07c re-pin. A broken assertion is a defect under (d): no re-run, no W_max cut, no
      range change, no seam. `ci.yml` runs pluginval and auval `if: always()`. Phase 13 re-enforces the strict
      30 s and the 1.10 growth bound on all three OSes on the release machines (AX41); phase-07c condition 9's
      packet repeats the file 7 split timer on one named local box before sizing its interim rules. (c) A
      listed entry whose printed 14 × worst passes 30 s is a job-log warning (the PASSES30S warning printed by
      the records test; nothing writes `$GITHUB_STEP_SUMMARY`) and leaves the register through `/fix-plan`
      before the next phase is `done`; its register text closes; the low-α scene's hosted-runner assertion
      stays in this form (in-window on Linux and Windows, printed on macOS) until Phase 13; the strict 30 s
      branch applies to the flutter scene, and to the low-α scene only on the release machines. (d) A broken
      assertion, or the macOS trigger, is a defect: no re-run, no W_max cut, no range change, no seam; it
      enters the register with its remedy through `/fix-plan` — a timing entry: phase-07c conditions 9–10; a
      work-pin entry: the code change named, re-pinned only with a CHANGELOG reason. This phase may be set
      `done` with the register entries recorded in §0 row 05h; the macOS and Windows records go to Maisara in
      the PR (section 2 item 2).
- [ ] The solve seam: restore, prepare and `reset()` call the diffuse solve through one function (scope 2).
- [ ] Only if Phase 08 went first (scope 10): binaural goldens re-rendered, binaural W1/W2 per mode with
      the diffuse share and the binaural AX38 (iv) records recorded, phase-08 item 8 re-run, and the
      restore gate passed in the heaviest output mode (phase-08 scopes 9 and 10).
- [ ] Trigger 1's clause (d) replicates at the gated cubes run on the C++ shipping rule, disjoint
      pre-registered streams (section 3, D-H1; Seat 1, file 55).
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

Note (an addition, not part of AX37 (5.3)): if Phase 08 went before this phase, its listening items on
concentrated absorption, marked provisional there, are re-listened on the switched tail level.

## 7. Contractor review focus

Equivalence of the `src/sim` formulation to the validated model (not just to its numbers on a few
cases); the independence of the tracer comparison; the AX22 interaction (AX37 (5.2)); memory scaling at
100 m (AX38); determinism (the D1–D7 package, AX39); the AX38 gate (threading, three-class order,
`reset()`); the cap-hit and floor-truncated flags (AX41); D-H1's register (v); no per-scene logic.

## 8. Risks and atomicity

- The plan is recorded first: done (AX37–AX46, committed in phase 05b). D-H1 is decided (section 3,
  2026-11-10); the restore gate is implemented in its register form (section 5).
- **Atomicity:** the matching change does not land in `src/sim` (commit to the branch) without, in the
  same push, the `ref_hybrid` agreement test, the tracer test and the updated goldens, and the PR is not
  opened before a manual nightly BRAS run on that push is green (CLAUDE.md "When CI runs").
- The C++ cost puts n\*_max below 1 000 → the conflict returns to Seats 1, 3 and 4 (AX41).
- The realised-work assertion or the restore gate fails at the pinned W_max → back to D-H1, not a
  loosened gate.
- The outer-band tracer check fails in a band → D-T2 and Maisara with numbers, never back to AX16.
- A default placement of a room or preset fixture raises U → the placement changes, not the predicate
  (AX44 (ii), as read by D-H3 (b): the two contract-limits fixtures `edge_values` and `open_field` are
  known, correct U cases, not rooms).
- **Split rule (CLAUDE.md):** if this phase cannot be finished in two sessions, the remainder goes into
  `phase-05i.md` with the same atomicity rule. **Applied 2026-11-10:** [`phase-05i.md`](phase-05i.md)
  carries the remainder (its §3); this phase closes on what landed in session 2 once its CI run is green.

## 9. Out of scope

Early rendering of scattered energy (not promoted; re-run rule AX36 (e)); per-band scattering (B10);
the tail decay rate (B12); Phase 08 directions beyond AX37 (5.3) (directional late tail: §5 B18); Phase 10
caching beyond what AX39 needs (a kernel cache only through an AX, AX38); a both-near fallback (§5 B15);
moving the diffuse solve off the synchronous restore, prepare and `reset()` (Q2a (C), phase-07c); any
per-scene tuning.

## 10. Definition of done

Section 5 all checked with CI evidence; §0 row 05h `done (tail-level switch implemented)` with the
numbers; this phase's PR with the listening checklist, the contractor focus, the AX/ledger links and the
"Raise with Maisara" item if it applies.
