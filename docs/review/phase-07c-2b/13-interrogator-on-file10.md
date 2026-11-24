# Interrogator round 4 on `docs/review/phase-07c-2b/10-decider-l4.md`

Every id stands: four survive outright and eight survive with corrections. The decider's own flag on Seat 5 is a TENSION MISREAD, not UNDERCONVENED, and it does not change the winner. Until Seat 5 rates them, though, r1 and the `--provisional-handover-sample` flag should not be built.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:**
- File 10 in full, and 9-seat{1,2,3,5,6,7,9}-l4.
- Code: `src/cli/Cli.cpp` (option list L121–170, validation L340–378); `src/sim/Engine.h` (L146–160, L236–307); `ScenePipeline.cpp` L656 and L704; `tests/unit/test_interim.cpp`; `tools/ci/test_abx_kit.py` L188; `tools/ci/abx_kit.py` L730–744 and L983–984.
- `tests/scenes/valid/stone_box.json`.
- Plan: BUILD_PLAN AX49 (L172) and L365; phase-07c-1b L124; run sheet §7.
- Corpus: Kuttruff Eq. 4.12, 5.24 and 8.29, Table 6.1; Vorländer Eq. 6.3–6.4.

## Rulings

| id | ruling |
|---|---|
| L4 convening (Seats 4, 8 not required; Seat 6 added) | **sound** |
| L4 tension map | faithful, **except Seat 5's L-a cell: TENSION MISREAD** (it does not change the winner) |
| L4-P (flags, r1–r5, tests 1–8) | **SURVIVES WITH CORRECTIONS** |
| L4-W (AX49 wording) | **SURVIVES WITH CORRECTIONS** |
| L4-S (stone variant) | **SURVIVES** |
| L4-D (design, assertions) | **SURVIVES WITH CORRECTIONS** |
| L4-T (sittings) | **SURVIVES** |
| M3-S (corrected) | **SURVIVES** |
| M3-G (corrected) | **SURVIVES** |
| M3-C (corrected) | **SURVIVES** |
| M3-F (full apply list) | **SURVIVES WITH CORRECTIONS** |
| M3-T (re-decided) | **SURVIVES WITH CORRECTIONS** |

## The decider's own flag: TENSION MISREAD, not UNDERCONVENED
- **Why not UNDERCONVENED.** That outcome is for a seat whose matter was touched but which was never convened. Seat 5 was convened and answered L-a on its own ground: the CLI flag, AX5, the guard and CI.
- **Why it is a TENSION MISREAD.** Seat 5's "1/1" was given "to keep it at 1/1" under conditions (i)–(v). The decided variant differs in two ways:
  - It breaks condition (iv)'s last bullet: "on the L_p ≥ L scene, the flagged output is bit-identical to the default". The decision refuses there instead (r1), on Seats 2 and 3's conditions.
  - It adds `--provisional-handover-sample`, Seat 6's addition, which none of Seat 5's conditions covers. That is a mid-render IR swap on the real-time path.
- So the cell must be marked "read from conditions", with one condition unmet and one element unrated. It cannot be entered as Seat 5's own 1/1.
- **The two conditions really are mutually exclusive.** `Engine.h` L295–297 already makes `assembleProvisional()` "exactly assemble()" where L_p ≥ L. So Seat 5's (iv) is achievable, and choosing r1 is a choice between seats' conditions that only Seat 5 can rate.
- **Effect on the winner: none.** Seat 5 gave no 3 anywhere. Even with Seat 5 at 2/2, L-a's maximum is 2 and its sum 12 (11 with L-a1), below L-b's 14 and L-c's 18. L-a still wins.
- **Correction:**
  - mark Seat 5's cell "c (iv) unmet, handover unrated";
  - ask Seat 5 one narrow question (r1 against (iv), and the handover flag) before `--provisional-handover-sample` or r1 is implemented;
  - if Seat 5 gives a 3, that is NEEDS MAISARA case (c).

## Convening
- **L4.** Seat 4 not required (omni, diotic) and Seat 8 not required (validation stimulus) are both consistent with the README rows. Adding Seat 6 answers file 11. Sound.
- **M3-T.** Only Seat 1 is convened. The pair changes no scene, engine, chain, control or label. Seat 3's interest, the speech null, is already a pre-seal condition (M3-C 7). Seat 7's hours are measured on this pair. Sound.

## L4 tension map
I rebuilt every cell from the 9-seat files:
- **S1:** L-a 0/1, 0/0 under L-a1 (L-a1 is met by r3 for `--diagnostics`, test 2 and manifest assertion 1); L-b 1/1; L-c 1/2.
- **S2:** 1/0, 1/1, 1/2.
- **S3:** 1/1, 1/2, 1/2.
- **S6:** 0/1 held under its conditions 1–3, which are adopted; 1/1; 1/2.
- **S7:** 1/1, 1/1, 1/2.
- **S9:** 0/1, 0/0, 0/1.
- **Sums:** L-a 10 (9 with L-a1), L-b 14, L-c 18. **Correct.** The only fault is Seat 5's L-a cell, above.

**Ordering:** no seat gives a 3. L-a has a maximum of 1 against 2 for the other two. **Correct**, and it holds even under any non-veto Seat 5 rating.

## Load-bearing claims
**K27 / L4-L2: CORRECT as bounds.**
- stone_box has α 0.05 from 63 Hz to 1 kHz, then 0.06/0.07/0.08. Multiplied by 0.844 that gives 0.0422, 0.0506, 0.0591, 0.0675.
- −ln(1 − 0.0422) = 0.04312, so T = 0.161·2400/(1120·0.04312) = 8.00 s (Kuttruff Eq. 5.24 with m ≈ 0; air is negligible at 63 Hz, and the engine measures it anyway).
- S = 2(240 + 200 + 120) = 1120 m². t_dir = √(4 + 25)/343 = 15.7 ms. t_mix,e ≥ 15.7 + √2400 = 64.7 ms.
- L_f ≥ 2.561 s, L_p ≥ 2.661 s.
- L = min(1.5·8, 12) = 12 s, matching `Engine.h` L240: "1.5 T60_max from emission, capped at 12 s".

**K28 / L4-L3: CORRECT.**
- With Eyring, −S·ln(1 − ᾱ) = 0.161·10⁶/8 = 20125, so ᾱ = 1 − e^(−0.335) = 0.285.
- At 1 kHz, m = 1.08×10⁻³ m⁻¹ (Kuttruff Table 6.1, 50 % RH), so 4mV = 4320 and ᾱ = 0.232.

**K29: CONDITIONS VIOLATED, but not load-bearing.**
- Kuttruff Eq. 8.29 is the ensemble-averaged decay for white or band-noise excitation switched off. A held harmonic chord is deterministic, so its post-release decay at the partials is not the Schroeder curve.
- The citation should be Vorländer Eq. 6.4; Eq. 6.3 is the integration constant.
- It feeds only assertion 13, the ghost print, which is print-only. Label that print as "noise-excitation (Schroeder) estimate".

**K30:** the direction is [Inf] and the depth is measured. Fine.
- Seat 2's cut: e^(−13.82·2.545/8) = 0.0123, i.e. −19.1 dB.
- Seat 9's cube cut: 60·3.714/8 = 27.9 dB.

**K23, K25, K26: CORRECT (from the code).**
- `assembleProvisional` is called at ScenePipeline L656 and L704 and in `test_interim.cpp`.
- The step-flag gating is at Cli.cpp L350–375. The guard test is `test_plugin_never_reaches_the_step_flag` at L188.

**K32: CORRECT.**
- BUILD_PLAN L365: "settling" covers "building or crossfading", project load included.
- phase-07c-1b L124: "`settling()` does not include a running crossfade".

**L4-L5: CORRECT.** 13.82 × 0.312 = 4.312, and e^(−4.312) = 0.0134.

**Refusals r1–r5 against Cli.cpp: complete for every seat's condition.**
- They cover Seat 5 (ii), Seat 3 condition 1, Seat 1 L-a1, and the `--automation` option (L156).
- The remaining options are not refused: `--no-air-absorption`, `--w-multiplier`, `--mix-floor-ms`, `--diffuse-histories`, `--rate`, `--atmosphere`, `--images`. No seat asked for them, and test 2 keeps flagged output out of goldens and BRAS. Acceptable.
- **r5 is IMPRECISE.** The `--abx-step-sample` pattern it copies requires a multiple of the partition **and** of the block, and at least one partition (Cli.cpp L370–373). r5 should mirror that. N should also be defined as the output sample where the fade starts, the semantics of `--abx-step-sample`.

**Tests: three corrections.**
- **Test 3 is IMPRECISE.** AX5 and CLAUDE.md guarantee bit-identity only "on the same platform". A single pinned SHA-256 across three OSes would fail. It needs a hash per OS, or a with-flag/without-flag comparison on each runner.
- **Test 8 is IMPRECISE.** "From N + 1440 bit-identical to the default exact render" holds only against the **real-time-emulation** exact render with the same block and partition. Against the offline render the criterion is the −120 dB null (Phase 06), not bit-identity. Name the comparator.
- **Tests 1, 2 and 4–7 are consistent with the code.** Test 7 relies on the `[staged]` serial/parallel bit-identity (`Engine.h` L251–255).

**L4-D assertions:** consistent with Seat 3 conditions 1–9 and Seat 1's design.
- The hold is H = max(2.661, 4) = 4 s. The IR past 4 s is 60·4/8 = 30 dB down.
- The anchor, B against B ± 3 dB via `--abx-step-db` with step sample 0, passes Cli.cpp L358–362.

## L4-W
- The wording matches Seat 5's (v) and Seat 3's request. It is a board row (D-C9), not one of Maisara's recorded decisions.
- **Missing home.** Run sheet §7 is "Not in this kit" and lists "AX49 L4 (item 14)" there (L241–244). L4 now enters the kit, so the apply list needs:
  - the run sheet's §7 entry moved;
  - an L4 section: procedure, response table, anchor, family.

## Debt register and PRD (L4)
- **Debt register:** every later cell of 1 or more on L-a has a row (Seats 1, 3, 5, 6, 7, 9). Every "repaid when" names a phase that exists (07d, Phase 11). Faithful.
- **"Decided for Maisara" line: two IMPRECISE phrases.**
  - "where a cut is easiest to hear" should be "easier to hear than in the 100 m cube (about 7 dB shallower cut)". Only two scenes were compared.
  - NFR-8 is cited for "no engine change". NFR-8 governs environment-specific code paths, so NFR-1 alone carries the line.
- L-b and L-c are shown against the cited ids. **No PRD MISREAD.**

## Part B
**M3-S: SURVIVES.**
- The new ITDG line is correct. S0's floor image has a path difference of √502.3 − √488.7 = 22.412 − 22.106 = 0.306 m, i.e. 0.89 ms, notch 560 Hz. S1's floor image is 1.57 ms (318 Hz) and S0's wall image 0.583 ms (857 Hz). The specular amplitude 0.315 gives +2.4/−3.3 dB.
- The PRD lines now cover every surviving option (E, D, B, s0.9/default, both_wall, V3′, V1–V3).
- The strongest objection is restated correctly.

**M3-G: SURVIVES.**
- M3S-L4 now reads ≥ T·fs + Δ + min d ≥ T·fs.
- +1.2 s per speech stimulus (3.729 − 2.560 = 1.169 s); K6 gains about +0.08 h.
- The plain-language line is correct.

**M3-C: SURVIVES.** "Avoided" replaces "met", and the 14 % is marked as an inference.

**M3-F: SURVIVES WITH CORRECTIONS.**
- The apply list is complete for M3, and the item-15 home in run sheet §7 is right (L245).
- Add the L4 run-sheet move under item 8 (AX49 / L4-W), as above.

**M3-T: SURVIVES WITH CORRECTIONS.**
- Seat 1: "I accept", on condition that "the pre-registration states the selection grounds". The condition is adopted, so 0/0 c is a faithful reading.
- The null claim is now correct: E is nulled on speech, B on noise only (file 4 fact 5). B's speech null stays open as a pre-seal condition.
- **Correction:** the child-speaker exclusion is now at `abx_kit.py` L983–984, not L737.

## Ledger rows
| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| L4 | convening | Seats 4, 8 not required; Seat 6 added | sound | README rows; AX49 L172 | — | — |
| L4 | map | S1, S2, S3, S6, S7, S9 cells; sums 10/14/18 | faithful | 9-seat* §3–4, §6 | — | — |
| L4-P | map | S5 L-a "1/1" with (iv) unmet (r1) and handover flag unrated | TENSION MISREAD (outcome-neutral) | 9-seat5 §6 (iv); Engine.h L295–297 | SWC | ask Seat 5 before implementing r1 / handover flag |
| L4-P | ordering | L-a wins even at S5 2/2 (12 < 14) | correct | arithmetic | — | — |
| L4-P | code | r1–r4 against Cli.cpp options | consistent | Cli.cpp L121–170, L340–378 | — | — |
| L4-P | code | r5: partition only; N semantics | IMPRECISE | Cli.cpp L365–373 | SWC | — |
| L4-P | test 3 | single pinned SHA across OSes | IMPRECISE | AX5 same-platform identity | SWC | — |
| L4-P | test 8 | comparator after the fade | IMPRECISE | realtime vs offline: null, not bitwise | SWC | — |
| L4-S | claim K27 | 8.00 s, 64.7 ms, 2.561/2.661/12 s | CORRECT | Kuttruff Eq. 5.24; Engine.h L240; stone_box.json | — | — |
| L4-S | claim K28 | ᾱ 0.285 / 0.232 | CORRECT | Kuttruff Table 6.1 (1.08e−3) | — | — |
| L4-D | claim K29 | Eq. 8.29 for a chord | CONDITIONS VIOLATED (print-only) | Kuttruff §8.4 Eq. 8.29 (noise excitation); Vorländer Eq. 6.4 | SWC | — |
| L4-D | claim L5 | 0.0134 | CORRECT | arithmetic | — | — |
| L4 | claims K23/K25/K26/K32 | code and plan facts | CORRECT | ScenePipeline L656/704; test_abx_kit L188; BUILD_PLAN L365; 07c-1b L124 | — | — |
| L4-W | completeness | run sheet §7 "Not in this kit" still lists L4 | incomplete | run sheet L241–244 | SWC | — |
| L4 | PRD | "easiest"; NFR-8 for "no engine change" | IMPRECISE | PRD L112 | SWC | — |
| L4 | debt | register rows | faithful | — | — | — |
| M3-S | claim | ITDG line 0.6/0.89/1.6 ms, notches 860/560/320 Hz | CORRECT | geometry | SURVIVES | — |
| M3-S | PRD | every survivor shown | correct | file 10 Part B | SURVIVES | — |
| M3-G | claims | L4 bound; +1.2 s; +0.08 h | CORRECT | arithmetic | SURVIVES | — |
| M3-C | wording | items 8, 9 | correct | — | SURVIVES | — |
| M3-F | completeness | L4 run-sheet home | incomplete (shared with L4-W) | run sheet §7 | SWC | — |
| M3-T | convening / map | Seat 1 only; 0/0 c | sound / faithful | 9-seat1 "M3-T" | — | — |
| M3-T | claim | nulls on speech | CORRECT now | file 4 fact 5 | — | — |
| M3-T | citation | abx_kit L737 | IMPRECISE (now L983–984) | abx_kit.py | SWC | — |
