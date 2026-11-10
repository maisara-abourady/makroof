# Interrogator — document mode, diff check of the plan edits (3973a5c..19cabdb)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, document mode: diff check of the plan edits applying the phase 05b session 2 decisions (`git diff 3973a5c HEAD`)

The plan edits carry the accepted decisions faithfully. My final-round items 3–6 are applied word for word. One problem needs a decision before the restore gate is built: W_max is sized to the restore watchdog with no margin, but the new blocking restore gate and the allowed realised-work ratio together mean that gate can fail on timing noise alone. There are also seven smaller wording fixes the plan-editor can make. No passage contradicts a settled decision.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Checked:** the changed passages only, against the final decision texts (files 13, 15, 34, 37, 39, 40), the computations (C13–C16c and the `c16` JSON) and the corpus (Kuttruff L1544–1552 Eqs. 2.49–2.50, L2337 Eq. 4.24, L2375 Eq. 4.29, L2420 Eq. 4.35, L2505 §5.2, L1620 §2.7, L3982 §8.7; Vorländer Table 6.1).

### Verdicts per passage

| passage | verdict | note |
|---|---|---|
| CLAUDE.md, determinism exception (AX40's fixed key) | CORRECT | matches AX40 and AX5; offline bit identity is untouched |
| AQ10, amendment (Challenge 1 block; W_max and n\*_max per Q2) | CORRECT as a record of Maisara's answers; INCONSISTENT with AX41 in combination | correction 1 |
| AX5 note (D1–D7 carry cross-architecture agreement; C5 ran on one platform) | CORRECT | |
| AX16 "switched" (C16 (g) values) | CORRECT, IMPRECISE | the values are at 1 kHz; say so (correction 7) |
| AX21 cross-reference | CORRECT | |
| AX36 (c) resolved | IMPRECISE | correction 6 |
| AX37 (D-T5) | CORRECT, one IMPRECISE | the citations are as corrected (Eq. 4.24 is Lambert; the split is §5.2 / §2.7; air term §4.5); "agrees within 0.08 dB" needs its conditions (correction 5) |
| AX38 (D-T4): `reset()` in the synchronous class (59), S4 cell rated (60), Challenge 1 gate "14 × t_restore ≤ 30 s, about 2.14 s" | CORRECT; "(4b) AQ10 is unchanged" IMPRECISE | correction 8; the gate's margin is correction 1 |
| AX39 (D-T1.1) | CORRECT | corpus citations, D1–D7 with block 64, the D5 golden carrying n\* and N, the wording rules |
| AX40 (D-T1.2) and the BRAS report's MC SE (item 6) | CORRECT | also in phase-05b2 §4 |
| AX41 (D-T1.3) | rule and item 3 CORRECT, **word for word** ("Cap hit := N_need > N_cap … reported as 'floor truncated' … not as a cap hit"); integer stop test and N_cap; block 64; overrun ≤ 0.153 W_scene; realised work ≤ 1.009 W_scene; W_max 3.05 M / W_scene 6.10 M; n\*_max 1 024 with its re-derivation rule. Cost line IMPRECISE. | corrections 1 and 2 |
| AX42 (D-T1.4) and item 4 | CORRECT | 8 000: ≤ 0.082 dB at default and one-end placements, uncapped both-near up to 0.110 dB; 1 024: 0.017–0.086 dB at the defaults, 0.124 dB (C14, per-emitter) / 0.108 dB (C16, joint); Table 6.1 jnd 1 dB, δ = 0.25 jnd |
| AX43 (D-T1.5) | CORRECT | 70 / 560 / 4.290; W1 corner ℓ_ref 0.65 % = 0.028 dB, SE_test ≤ 0.052 dB; the reported set; the CI reports |
| AX44 (D-T1.6) and items 3 and 5 | CORRECT | the U predicate with the union VOV and the cap-hit definition; the final "Where U fires" list from C16b / C16c (main-text list marked superseded); the debt for W1 both_wall_0.3; GA-limit text (Eq. 2.50, §8.7, +3 dB at a rigid wall, L1552) |
| AX44, "absent at α = 1" | CORRECT (derived) | follows from Eq. 2.49's R = 1 premise (no reflected wave at R = 0); it is not stated in the corpus, so mark it as derived |
| AX45 (D-T6) | CORRECT | the room set as fixed; 72 case-bands, z_FW 3.81; the gate-N rule; Seat 7's (i)–(iii) |
| AX46 (D-T2, Q1 (a)) | CORRECT | ℓ_ref 0.65 %; 3·SE ≤ 0.35 %, SE ≈ 0.12 % ≈ 0.005 dB; (b)'s costs 20–33×, 9–13 s, 93–187 ms; "max 1 over eight rated cells" |
| §0 row 05b note | CORRECT | |
| §5 B11, B16, B17, B18 | CORRECT | |
| §5 B15 | IMPRECISE | correction 4 |
| §6 rows (D-T5/D-T4, D-T1/D-T2/D-T6, AQ10) | CORRECT | the R1 wording inherits correction 6 |
| phase-05b2 §1, §3–§5, §7–§9 | CORRECT | the acceptance list matches AX37–AX46; the blocking restore gate is listed (correction 1 applies) |
| phase-05b.md | CORRECT | |
| phase-08 (E_b parity, both-near render, item 8 per AX38 (v), per-mode records) | CORRECT | |
| phase-10 (kernel-cache AX reopens AX38 (ii) and 4b; gate wait in the staleness metric; stepwise automation) | CORRECT | |
| phase-11 (note U text per Seat 6 (i), the unmoved-emitter wording, U′ tier, "settling", no open-field Eyring T60) | CORRECT | |
| phase-12 (two-branch outdoor check, ghost-tail reversal, Seat 6 (ii) as a requirement, D-T3 packet) | CORRECT | |
| phase-13 (8-instance load time > 10 s → Maisara; multi-instance RSS incl. Bitwig; W_max / n\*_max re-check; Q2a (C) scheduled) | CORRECT | |

### Numbered corrections

1. **Must be settled before phase 05b implements the restore gate; it needs a numeric choice, so it goes through the decider, not the plan-editor alone (INCONSISTENT).**
   - **The two rules meet with no margin.** AQ10 (amended) and AX38 4c make "14 × t_restore ≤ 30 s at 100 m, 96 kHz" a CI **block**. AX41 sizes W_max to exactly that budget at the worst OS build: (2.143 − 1.884)/2 per emitter.
   - **AX41 allows overruns the block does not.** AX41 also allows realised work up to a pre-registered ratio ("about 1.05").
   - **Even today's prototype only just passes.** At the gated 100 m scenes realised work is 0.986–0.993 W_scene (C16 JSON), so the restore is ≈ 1.884 + 0.993 × 0.259 = 2.141 s, and 14 × 2.141 = 29.98 s. That is a 0.02 s margin.
   - **At the allowed ratio the block fails by design.** At 1.05: 14 × (1.884 + 1.05 × 0.259) ≈ 30.2 s.
   - **The build time is optimistic.** The 1.884 s build is a best of 3 (BUILD_PLAN §0 row 07; Seat 5, round 2).

   The W_max re-derivation rule must state the margin for the realised-work ratio and for the spread of the restore measurement. Otherwise the block flakes on timing noise.
2. **AX41 cost line mixes n\*_max values (IMPRECISE).**
   - Low-α s = 1 cube: "SE 0.44–0.50 dB" is given at the adopted 1 024.
   - Closed s = 0.3 cubes: "SE 0.13–0.20 dB" is the 8 000 figure; at 1 024 it is **0.09–0.15 dB**.
   - Absorbing-floor cube: "0.12 dB" is the 8 000 figure; at 1 024 it is **0.09–0.10 dB**.
   - Layouts 4/5: "0.17–1.33 dB" is the 8 000 figure; at 1 024 it is **0.13–1.33 dB** (layout 5 listener_wall 0.131 dB).

   State every figure at the adopted n\*_max (C16 (f)).
3. **AX38 4c / AQ10: name the restore gate's scene(s) (IMPRECISE).** "The synchronous state restore at 100 m and 96 kHz" does not say which scene. W_max is derived at the worst gated cost (the flutter / fallback cube), and every gated 100 m scene fills the budget (C14 (c), C16). Name the gated scenes; this ties to correction 1.
4. **B15 (IMPRECISE).** "Flagged by note U" holds only where U fires, i.e. both-near AND (cap hit OR VOV_union ≥ 0.1). Both-near placements such as `dead_booth` with the listener at a wall stay silent (C16 (f)). Write "flagged by U where it fires (AX44)".
5. **AX37 rationale (IMPRECISE; missing conditions).** "The propagated diffuse energy agrees within 0.08 dB" needs its conditions: 15 (A) cases, 500 Hz–2 kHz, one pair each (report-phase05b §5). The 8-band agreement (≤ 0.088 dB, C3) belongs to AX39's estimator.
6. **AX36 (c) and the §6 row (IMPRECISE).** "R1 certified at 2.5 m in CR2, CR3 and CR4" needs its conditions:
   - certified at 500 Hz–2 kHz and at the AX28 / Phase 05 positions;
   - not certified near walls in layout 4/5-type rooms (4.75 / 5.3 / 8.7 %).

   Under AX39, R1 bears only on the reference's ℓ_ref, which AX43 already records per case.
7. **AX16 switched (IMPRECISE).** Mark the C16 (g) values as 1 kHz.
8. **AX38 (4b) (IMPRECISE).** "AQ10 is unchanged" now contradicts the AQ10 amendment in the same edit. Write "AQ10's 50 ms target is unchanged".

Correction 1 must be resolved before the gate is implemented. Corrections 2–8 are wording, for the plan-editor; none changes a decision or a threshold.

### Ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-FX-01 | Item 3, cap-hit definition (AX41, AX44), word for word | CORRECT | closed |
| P05B2-FX-02 | Item 4, D-T1.4 qualifier and the 1 024 figures (AX42) | CORRECT | closed |
| P05B2-FX-03 | Item 5, final "Where U fires" list from C16b/C16c, main-text list superseded, W1 both_wall_0.3 debt (AX44) | CORRECT | closed |
| P05B2-FX-04 | Item 6, BRAS report MC SE (AX40, phase-05b2 §4) | CORRECT | closed |
| P05B2-FX-05 | Corrections 59 (`reset()`) and 60 (S4 rated) in AX38 | CORRECT | closed |
| P05B2-FX-06 | AX46 bias reading (ℓ_ref 0.65 %, SE ≈ 0.12 % ≈ 0.005 dB) | CORRECT | closed |
| P05B2-FX-07 | W_max 3.05 M / W_scene 6.10 M and n\*_max 1 024 with their re-derivation rules (AX41, AQ10, phase-05b2 §4, phase-13) | CORRECT | closed |
| P05B2-FX-08 | Blocking restore gate (14 × t_restore ≤ 30 s) against W_max sized to the same budget with zero margin and a realised-work ratio up to ≈ 1.05 (prototype 29.98 s; 30.2 s at 1.05) | INCONSISTENT: resolve before the gate is implemented (decider) | open |
| P05B2-FX-09 | AX41 cost line mixes n\*_max 8 000 and 1 024 figures | IMPRECISE | open |
| P05B2-FX-10 | Restore gate's scene(s) not named (AX38 4c, AQ10) | IMPRECISE | open |
| P05B2-FX-11 | B15 "flagged by note U" without U's conditions | IMPRECISE | open |
| P05B2-FX-12 | AX37 "within 0.08 dB" without its conditions | IMPRECISE | open |
| P05B2-FX-13 | AX36 (c) "R1 certified at 2.5 m" without band and position conditions | IMPRECISE | open |
| P05B2-FX-14 | AX16 C16 (g) values not marked 1 kHz | IMPRECISE | open |
| P05B2-FX-15 | AX38 (4b) "AQ10 is unchanged" against the AQ10 amendment | IMPRECISE | open |
| P05B2-FX-16 | Corpus claims in the changed passages (Kuttruff Eqs. 2.49–2.50, 4.24, 4.29, 4.35, §2.7, §5.2, §8.7; Vorländer Table 6.1) | CORRECT ("absent at α = 1" derived from Eq. 2.49's R = 1 premise) | closed |
| P05B2-FX-17 | No contradiction of a settled decision (AX22, phase-05b scope 0, NFR-8, Maisara's answers M-01…07) | CORRECT | closed |

Files:
- /home/user/makroof/docs/BUILD_PLAN.md (AQ10, AX38, AX41, AX36, AX37, AX16, B15)
- /home/user/makroof/docs/phases/phase-05b2.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json (section `c16`, `work_over_wscene`)
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md
