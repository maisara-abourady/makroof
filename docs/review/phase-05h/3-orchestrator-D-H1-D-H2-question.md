# Orchestrator — questions for the decision loop, phase 05h session 2 (2026-11-10)

Run under `/fix-plan` step 3 (`.claude/commands/fix-plan.md`; `docs/board/README.md`). Session brief:
`docs/sessions/2026-11-10-phase-05h.md`, section "Session 2 of 2", objective O11. Corpus c1b171f.

## D-H1 — margin between W_max and the blocking restore gate, and its two OPEN premises

**Where the rule is written:** `docs/phases/phase-05h.md` §3 (exact text, incl. Seat 1's floor and the two OPEN
items); `docs/BUILD_PLAN.md` §2 AX38 4c, AX41 (W_max, n\*_max, the realised-work ratio), AQ10 (amended 2026-11-10);
decider files `docs/review/phase-05b2/47-*.md` §4 (i)–(iii), `51-*.md` §3–§4, `53-*.md` §1, interrogator `54-*.md`
corrections 1–2, Seat 1 `55-*.md`; ledger P05B2-J1FX-18 and -20 (carried here as the OPEN premises).

**The C++ data the rule says the decision is taken from:** `docs/review/phase-05h/1-orchestrator-cpp-costs.md`
(three OSes, CI run 42846229834; estimator commit c309589, provisional W_scene 6.10 M, n\*_max 1 024). In short:
- cost per image evaluation at the runner's pool size: 16.4 ns (Linux, pool 4), 9.6–13.7 ns (macOS, pool 3),
  11.7–11.8 ns (Windows, pool 4) at the closed cubes (the flutter scene's figure is inflated by discarded speculative
  pilot blocks; one-thread figures 44–56 ns Linux, 22–29 ns macOS, 31–38 ns Windows);
- realised work / W_scene: 0.9347 (flutter), 0.9910 (s 0.3), 0.9859 (s 1), 0.1216 (W1); prototype C16 ≤ 1.009;
- diffuse solve at the gated scenes (10 runs, median): 99–162 ms Linux, 58–96 ms macOS, 71–115 ms Windows;
- **synchronous restore today, without any diffuse solve, 96 kHz, worst of 10:** closed low-α cube 2.063–2.075 s
  (Linux), **2.328–2.591 s (macOS)**, 2.000–2.004 s (Windows); flutter 0.595 / 0.447 / 0.574 s. Budget per restore:
  30 s / 14 = 2.143 s. So 14 × (worst restore + median solve) = 30.27–30.42 s (Linux), 33.40–37.43 s (macOS),
  28.98–29.04 s (Windows) at the closed cube; 7.6–10.6 s at the flutter scene;
- run-to-run spread of the worst restore: up to 49 ms (9 %) on Windows between two runs; macOS min 1.50 s to worst
  2.59 s within one run (shared runner);
- Phase 07's full-rebuild record in the same runs (default materials, maximum room, best of 3, 96 kHz): Linux 2.03 s,
  macOS 2.17 s (BUILD_PLAN §0 row 07 recorded 1.884 s best of 3, the figure AX41's provisional W_max was sized from);
- flags and precision at the gated scenes (single runs): flutter: fallback both emitters, floor truncated, pilot floor,
  SE 0.002 / 0.001 dB, Seat 1's floor met via (a); low-α s 0.3: cap hit, SE 0.092 / 0.075 dB, pilot VOV 0.225 / 0.441,
  final VOV 0.131 / 0.155 → met only if clause (d)'s replicates pass; low-α s 1: cap hit, SE 0.360 / 0.359 dB > 0.33 dB
  → **not met**, U raised on both emitters;
- W1 diffuse share (two emitters, n\*_max 1 024, median of 10): 7.65 ms Linux, 9.03 ms macOS, 6.35 ms Windows
  (AX41: ≤ 25 ms);
- D5 hashes, n\*, N, W identical on gcc / Apple clang arm64 / MSVC at four scenes.

**What has to come out (phase-05h §3, AX41, AX38 4c), as plan text the plan-editor can apply:**
1. The gated closed low-α 100 m cube's α and s, pinned in AX38 4c (candidates computed: α 0.05, s 0.3 and s 1).
2. The definition of "any further rise" in Trigger 1's starting-state clause (e.g. relative to the scene's replicate
   spread), before the gate is implemented.
3. The realised-work ratio, pre-registered from the C++ measurements before the first CI run of the assertion and not
   changed afterwards (Seat 5 suggested about 1.05; measured ≤ 0.991 here, ≤ 1.009 in the prototype).
4. W_max re-derived once from the C++ cost at the CI runner's pool size, the worst gated cost and the worst OS
   restore build, with D-H1's margin (from the restore spread over ≥ 10 runs and the ratio) taken out of W_max, pinned
   as a cross-platform constant in image evaluations; checked against Seat 6's 3 s per emitter. The data show the
   worst OS restore **without** the diffuse solve already above the 2.143 s budget on macOS and within 0.07–0.08 s
   of it on Linux: a margin that would take more than about 20 % of W_max (here more than 100 % on macOS) returns to
   the seats, whose options are the smaller W_max or bringing (C) (phase-07c) forward, never a time cap, a narrower
   room range or a formulation seam (AX38 4c). The loop must therefore say what W_max is pinned at for this phase and
   how the blocking gate is treated (implemented and run as written, with the expected result recorded as a defect
   remedied by (C) forward; or (C) brought forward before the gate), consistent with AQ10's "a gate failure is a
   defect … remedied by bringing (C) forward" and phase-07c §3 ("brought forward on any restore-gate failure").
5. n\*_max re-derived from the C++ W1 diffuse share (≤ 25 ms for two emitters): 1 024 stands unless the loop says
   otherwise (never below 1 000 without going back to Seats 1, 3 and 4).
6. Seat 1's floor: on the data it fails at s = 1 (SE 0.36 dB) and holds at s = 0.3 only through clause (d). If the
   pinned cube is the s = 1 one, "Raise with Maisara" item 1 fires (starting-state finding, escalated once). The
   decider answers for her from the PRD unless one of the three NEEDS MAISARA cases applies.

Determinism caveats for the record (PR #27 review m-3, Q-3): N depends on N_need computed from scores that contain
exp/sin, and t_mix,e comes from `MixingTime.cpp` outside the D2 flags, so equal N across OSes is highly probable, not
guaranteed by construction (equal on four scenes); C++ "work" counts images within c·t_mix + |dims| (the prototype's
lattice reached c·b + 1 m), so W_max must be re-derived on C++ counts (it is).

## D-H2 — which AX43 / AX45 / AX46 case-bands have a certified reference now

A plan premise found false this session. AX43 (70 cases, 560 case-bands), AX45 (72 case-bands) and AX46 take their
references from `ref_hybrid.target_hybrid` "at the finest certified rung, with ℓ_ref recorded" (AX36's < 1 % rung
rule). What exists in the committed data:

| case class (AX43) | reference available | rung / certification | bands |
|---|---|---|---|
| 15 (A) cases | `tools/validation/data/phase05b.json` ell.values | 1.25 m; E_target certified at 2.5 m (change 2.5→1.25 ≤ 0.33 %, AX36 (a)) | all 8 |
| 30 BRAS pairs (CR2, CR3, CR4, initial α) | `phase05b.json` r1.rooms.<room>.rungs."1.25".e_target | 1.25 m; R1 certified at 2.5 m (change 0.354 / 0.366 / 0.140 %) | 500 Hz, 1 kHz, 2 kHz only (the other 5 bands exist only at 2.25–2.5 m patches in `phase05_scope6.json`, uncertified) |
| CS-NW+: W1 listener at a wall / edge / corner at 0.1 m, emitter at a wall at 0.1 m, emitter 0 | `phase05b2_dt1.json` c4 `ref` | 2.5 and 1.25 m (change 0.65 % at the corner) | 500 Hz, 1 kHz, 2 kHz only |
| CS-NW+: W1 listener at a wall at 0.3 m; every CS-NW+ case for emitter 1 | none | — | — |
| six Phase 04 rooms × 2 emitters | `phase05_scope6.json` phase04_rooms, emitter 0 only | 2.25 m patches, one rung (uncertified) | 8 (emitter 0) / none (emitter 1) |
| W1 × 2, W2 × 2 | W1 emitter 0: `c4` W1_reference_positions | 2.5 and 1.25 m | 500 Hz–2 kHz (W1 e0); none for W1 e1, W2 e0, W2 e1 |
| AX45 room set: `stone_box` (2), W1 (2), the three (A) s-cases, the small room (2) | s-cases: as the (A) cases; stone_box e0: scope6 2.25 m; W1 e0: c4 | as above | s-cases 8; stone_box e0 8 uncertified; W1 e0 3; stone_box e1, W1 e1, small room: none |

Computing the missing references needs `tools/validation/hybrid_fast.py` (numba, offline; installed locally this
session) at two rungs (2.5 and 1.25 m) per band column per case to certify: the Phase 04 rooms, W1 and W2 have per-band
α, so 8 kernels per case per rung; the (A) ladder cost about 4 h per layout case with numpy and the 1.25 m BRAS rung
needed 15 GB (chunked). This session has 4 cores and about one day. The orchestrator can start the cheapest runs
(small Phase 04 rooms, both emitters; the small room; W1 e1 and the 0.3 m wall case at 500 Hz–2 kHz) in the
background while the C++ work proceeds, and report what finished.

**What has to come out:** the rule for this phase's agreement, bias and regression tests: (a) which case-bands are
gated now (those with a certified reference), with ℓ_ref per case-band; (b) whether a reference at one uncertified
rung (the Phase 04 rooms' 2.25 m values, the BRAS pairs' 2.5 m values outside 500 Hz–2 kHz) may be used reported-only,
gated at a widened tolerance, or not at all; (c) how and when the missing references are produced (this session's
background runs, phase-05i, a CI/nightly job), so that AX43's 560 case-bands are eventually gated without the
implementer choosing; (d) whether the AX46 bias check's pre-registered N (3·SE ≤ 1 % − ℓ_ref) runs on the gated
subset now. None of this changes τ, z_FW, the case list or the statistical rule (AX42, AX43, AX45, AX46 are settled).
