# Interrogator — decision mode final round 3, D-T1, D-T2 and D-T6 (on decider round 4 + addendum)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, decision mode, final round (3) on D-T1, D-T2 and D-T6 (decider round 4 + addendum)

All 14 of my round-2 corrections are applied faithfully. Both remaining seat confirmations (S5-b and S6-b) came back at 1/1, and their conditions are folded into the text. No decision falls and no winner changes.

Two short wording fixes should be made before the packet goes to Maisara. The rest belongs to the plan-editor, but one of those is a definition the AX row must get exactly right: what counts as a cap hit. That definition decides where the note U fires.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:** files 34, 37, 35 (Seats 5 and 6), 33 (C16), 36 (C16b), 38 (C16c); the `c16` section of `phase05b2_dt1.json` (I re-tabulated `floor_truncated`, `cap_hit` and `work_over_wscene` for all 134 runs).

### Verdicts

| id | verdict |
|---|---|
| D-T1.1 T1-F\* (D1–D7, block 64) | **SURVIVES** |
| D-T1.2 S-1 | **SURVIVES** |
| D-T1.3 N-3W\*\*\* | **SURVIVES WITH CORRECTIONS**: item 3, for the plan-editor; it must be exact in the AX row |
| D-T1.4 Tol-2 | **SURVIVES WITH CORRECTIONS**: item 4, for the plan-editor |
| D-T1.5 CS-3 + CS-NW+ (70 cases / 560 case-bands, z_FW 4.290) | **SURVIVES** |
| D-T1.6 NW-4C+ with note U | **SURVIVES WITH CORRECTIONS**: items 3 and 5, for the plan-editor |
| D-T2 (Q1 packet) | **SURVIVES WITH CORRECTIONS**: item 1, before Maisara |
| Q2 packet (W_max, n\*_max) | **SURVIVES WITH CORRECTIONS**: item 2, before Maisara |
| D-T6 RS-2+ / B6-1F / M-2 | **SURVIVES** |

### Checked and faithful
- **Correction 1, D-T1.3 map:**
  - S2 0/1: Seat 2's condition is met by C15, 16/16 rows.
  - S4 1/1 at n\*_max 1 024 and 2/2 at 8 000 (30-S4a).
  - S5 1/1: rated by Seat 5 itself (S5-b). Its conditions (1)–(3) are in the addendum: integer stop test and integer N_cap; n\* and N in the D5 golden; a CI realised-work assertion at a ratio pre-registered from C++ data.
  - Sums 19 at 1 024 and 21 at 8 000 are correct. My "20" was wrong; the decider is right.
- **Correction 3, block 64.** Checked against C16 (h):
  - 8 000 = 125 blocks and 1 024 = 16 blocks.
  - Worst overrun 0.153 of W_scene, so the pilot is at most 0.653 W_scene.
  - Total work is bounded through N_cap. Realised work under the joint rule reaches at most 1.009 W_scene (layout-4 listener_wall, C16 JSON), inside the "about 2 %" stated in Q2.
- **Corrections 5 and 13.** C16 (g) is reproduced:
  - closed s = 0.3 cubes: AX16 +0.019 to +0.023 dB (long-run SE 0.006 dB);
  - low-α s = 1 cube: +0.057 / +0.101 dB;
  - absorbing-floor cube: +2.384 / +2.393 dB.

  The strongest objection and Q2 now say plainly that the switch adds random error in two classes.
- **Corrections 6–11 and 14.**
  - Seat 6's (i)–(iii) are in the text, and (ii) is now a phase-12 requirement.
  - The AX text reads "reduced next to a partially absorbing face, absent at α = 1" (Kuttruff Eq. 2.49 is derived for R = 1).
  - ℓ_ref is 0.63–0.65 %, so 3·SE ≤ 0.35 %, SE ≈ 0.117 % = 0.0051 dB.
  - The precision range is 0.0145–0.019 dB.
- **S6-b.** C16b passes Seat 6's own test: its three named good placements go silent at 1 024 with the union VOV, and every case with SE > 0.33 dB still fires. C16c shows no change in U at 8 000. Seat 6's 1/1 at both n\*_max values is faithful.
- **Q2b table (addendum) against C16 (f):**
  - default-placement SE 0.017–0.086 dB at 1 024 and 0.007–0.054 dB at 8 000;
  - near-wall SE ≤ 0.082 dB at 8 000;
  - "≤ 0.124 dB" at 1 024 is C14's per-emitter figure; C16's joint figure is 0.108 dB, so the line is conservative.
- **D-T1.5 test N:** (0.25 − 0.028)/4.290 = 0.052 dB.
- **D-T6:** 72 case-bands, z_FW 3.81. The small room is silent under U and gated at shipping N.

### Remaining corrections

**Before the packet goes to Maisara**

1. **Q1 (a) shipped precision.** "Users get the 0.083 dB target wherever the work limit does not bind; met at n\*_max 8 000" holds only for default and one-end placements. At 8 000, uncapped both-near placements reach 0.110 dB (`living_room` both_edge_0.3, no cap, C16 (f)); at 1 024 they reach up to 0.108 dB under the joint rule. Add "at default and one-end placements". Also restore the qualifier "max 1 over eight rated cells; Seat 4 states a preference, no cell" in place of "no seat above 1".
2. **Q2a (A) table.**
   - "Layout 4 / layout 5, s = 1: SE 0.29–1.33 dB" should be **0.17–1.33 dB**: layout 5 listener_wall is 0.169 / 0.174 dB (C16 (f)).
   - Give the low-α s = 1 cube at both n\*_max values: 0.51–0.67 dB at 8 000, 0.44–0.50 dB at 1 024.
   - (B)'s restores are labelled as the per-emitter rule (C14). That labelling is correct.

**For the plan-editor (/fix-plan), exact wording required**

3. **Define "cap hit" in the D-T1.3 and D-T1.6 AX rows (INCONSISTENT between the decision text and C16).**
   - The text says "N = min(N, N_cap); a cap hit is flagged". Read literally, that flags a cap hit whenever N_cap < max(N_need, n\*).
   - C16, whose "Where U fires" list Seat 6's and Seat 2's confirmations rest on, defines cap hit as **N_need > N_cap**. It records a separate `floor_truncated` flag when the pilot overrun cuts N below n\*.
   - Floor truncation happens in **68 of 134** C16 runs, including runs flagged neither as cap hit nor as truncated in the decision's vocabulary:
     - `dead_booth` with the listener at a wall: both-near for both emitters, N 1 984 < n\* 2 112;
     - the gated flutter cube: N 256 < n\* 320;
     - `living_room` both_wall_0.1, both_edge_0.3 and the other both-near cases;
     - layout-4 corners: N = n\*/2 with cap hit.

     Under the literal text these would raise a cap hit, so U would fire on `dead_booth` with the listener at a wall (both-near AND cap). That contradicts the verified silent list and Seat 6's (ii).
   - The AX row must say:
     - cap hit := N_need > N_cap;
     - N may fall below n\* by up to the pilot overrun (≤ 0.153 W_scene of work). It is reported as "floor truncated" in the diagnostics, not as a cap hit.
     - The pre-registered CI flags follow C16.
   - Round 3's sentence "any shortfall is a flagged cap hit" (file 29 §B.1) is superseded and must not be copied.
   - No seat needs to re-rate: S2-a, S5-b and S6-b were all answered on the C16 data. Seat 5 explicitly noted that "the final range shrinks".
4. **D-T1.4.** Same qualifier as item 1: "met at n\*_max 8 000 at default and one-end placements (≤ 0.082 dB); uncapped both-near placements up to 0.110 dB".
5. **D-T1.6, which "Where U fires" list is final.**
   - The final list is the addendum's: C16b at 1 024 with the union VOV, and C16c at 8 000. Round 4's main-text list is superseded: at 1 024 it still lists W1 both_wall_0.3, `club` both_wall_0.3/0.5 and `living_room` both_edge_0.3 as firing, but they are silent under the union VOV.
   - Add to S1's debt row: at 1 024 the union VOV silences W1 both_wall_0.3, whose C13 per-emitter replicate p95 was 0.49 dB (Seat 6 thought it deserved the note). Seat 1 was not asked. Its 1/2 already covers both-near, so no cell rises.
   - Record that Seat 2's C15 replicate check ran on the per-emitter implementation (C13 rule). Joint-rule replicates in the closed cubes come with the C++ reported set.
6. **Gaps in the /fix-plan list.**
   - Seat 9's "BRAS report prints the Monte Carlo SE beside the ensemble spread" (D-T1.2 debt; a condition of the bias reading) is on no phase entry. Add it to phase-05b2 §4 or the nightly report.
   - Apart from items 3–5 and this, the list (round 4 §F plus the addendum) is complete. It covers the AX rows, AX36 (c), AX16/AX21/AX5, AQ10 per Maisara, phase-05b2 §3/§4/§5, the goldens, and phases 08, 10, 11, 12, 13, §0 records, the backlog and the ledger.

### New ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-56 | Round-2 corrections 1–14 applied (map S2 0/1, S4 1/1 or 2/2; block 64; C16 as the joint re-run; AX16 resolved; D-T1.4 wording; S6 (i)–(iii); AX α text; ℓ_ref 0.65 %; precision range; /fix-plan) | faithful | closed |
| P05B2-T1T2T6-57 | S5-b: block 64 1/1, conditions (1)–(3) folded | faithful | closed |
| P05B2-T1T2T6-58 | S6-b: U 1/1 at 8 000; 1/1 at 1 024 with union VOV (C16b test met; C16c no change) | faithful | closed |
| P05B2-T1T2T6-59 | Block-64 overrun 0.153 W_scene; realised work ≤ 1.009 W_scene (joint, C16) | CORRECT | closed |
| P05B2-T1T2T6-60 | C16 (g) AX16 − long run (+0.02; +0.06/+0.10; +2.38/+2.39 dB) and the "adds random error" cost line | CORRECT | closed |
| P05B2-T1T2T6-61 | Q1 (a) "target met at 8 000" (uncapped both-near to 0.110 dB); "no seat above 1" (S4 no cell) | IMPRECISE: fix before Maisara | open |
| P05B2-T1T2T6-62 | Q2a (A) layout 4/5 SE "0.29–1.33" (is 0.17–1.33); low-α cube at both n\*_max | IMPRECISE: fix before Maisara | open |
| P05B2-T1T2T6-63 | Cap-hit definition: text "min binds → cap hit" vs C16 "N_need > N_cap" plus `floor_truncated` (68/134 runs); decides U at `dead_booth` listener-wall | INCONSISTENT: exact AX wording via /fix-plan | open |
| P05B2-T1T2T6-64 | D-T1.4 target statement qualifier | IMPRECISE (/fix-plan) | open |
| P05B2-T1T2T6-65 | Final "Where U fires" = addendum (C16b/C16c); main-text list superseded; W1 both_wall_0.3 silenced at 1 024 recorded in S1 debt | correction (/fix-plan) | open |
| P05B2-T1T2T6-66 | Seat 2's C15 check ran on the per-emitter rule; joint-rule cube replicates come with the C++ reported set | note (/fix-plan, §4) | open |
| P05B2-T1T2T6-67 | BRAS report prints MC SE (Seat 9) missing from /fix-plan | correction (/fix-plan) | open |
| P05B2-T1T2T6-68 | Final verdicts: D-T1.1, D-T1.2, D-T1.5, D-T6 SURVIVES; D-T1.3, D-T1.4, D-T1.6 SURVIVES WITH CORRECTIONS (/fix-plan); D-T2/Q1 and Q2 SURVIVES WITH CORRECTIONS (items 1–2 before Maisara) | – | open until applied |

Files:
- /home/user/makroof/docs/review/phase-05b2/34-decider-round4-final-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/37-decider-round4-addendum.md
- /home/user/makroof/docs/review/phase-05b2/33-orchestrator-C16.md
- /home/user/makroof/docs/review/phase-05b2/36-orchestrator-C16b.md
- /home/user/makroof/docs/review/phase-05b2/35-seat5-confirm-S5b.md
- /home/user/makroof/docs/review/phase-05b2/35-seat6-confirm-S6b.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json
