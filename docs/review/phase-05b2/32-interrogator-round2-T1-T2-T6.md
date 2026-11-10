# Interrogator — decision mode round 2, D-T1, D-T2 and D-T6 (on decider round 3)

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, decision mode, round 2 on D-T1, D-T2 and D-T6 (decider round 3, file 29)

The decider applied all 18 corrections from my round 1. Seven decisions stand, none falls, and none changes winner. What remains is text and map work that would otherwise go into the AX rows wrong:
- D-T1.6: Seat 6's own condition (i) is not yet in the text, so its 1/1 cell is not yet true.
- D-T1.6: the "Where U fires" list leaves out cases where the note fires on good estimates.
- D-T1.3: the D4 block size is still unpinned.
- Q1: one number is wrong (ℓ_ref).
- Q2: one comparison is not resolved.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:** files 29, 27 (C14), 28, 30 (Seats 2, 4 and 6), 31 (C15), 7 §3, C4, C12 and C13; the `c13` section of `phase05b2_dt1.json`; Kuttruff L1544–1552.

Following the rebuttal rule, I rate only the new or revised text.

### Verdicts

| id | verdict |
|---|---|
| D-T1.1 T1-F\* | **SURVIVES**: corrections 10 and 11 applied; S3 marked †; Q1 (b) dependence stated |
| D-T1.2 S-1 | **SURVIVES** |
| D-T1.3 N-3W\*\*\* | **SURVIVES WITH CORRECTIONS** (items 1–5) |
| D-T1.4 Tol-2 | **SURVIVES WITH CORRECTIONS** (item 6) |
| D-T1.5 CS-3 + CS-NW+ | **SURVIVES**: CS-1 shows S3 and S6 at 1/3; 70 cases / 560 case-bands, z_FW 4.290 checked |
| D-T1.6 NW-4C+ with note U | **SURVIVES WITH CORRECTIONS** (items 7–10) |
| D-T2 (Q1 packet) | **SURVIVES WITH CORRECTIONS** (items 11–12) |
| Q2 packet | **SURVIVES WITH CORRECTIONS** (item 13) |
| D-T6 RS-2+ / B6-1F / M-2 | **SURVIVES**: 9/9 convened; Seat 7's cells and conditions (i)–(iii) faithful; gate-N rule stated (72 case-bands, z_FW 3.81 checked) |

### Applied faithfully (checked)
- **Correction 1.** The pilot is bounded in work from its first block.
- **Correction 3.** Accounting is joint over W_scene = 2·W_max, and N_need is the maximum over emitters and bands.
- **Corrections 6 and 9.** The AX text says "reflecting surface, up to +3 dB at a rigid wall" (Kuttruff L1552). Phase 11 has a register row.
- **Corrections 12–14.** All applied.
- **Correction 14 arithmetic:**
  - 15 + 12 + 4 + 30 + 9 = 70 cases;
  - z for 0.01/560 two-sided = 4.290;
  - 1 − 0.999⁷⁰ = 6.8 %.
- **Correction 17.** Seat 7 rated the composite 0/1, and 0/0 under its conditions (i)–(iii). All of them, and the "same material on every surface" wording, are in the text.
- **Correction 18.** C14 (d) puts the small room at SE 0.006 dB with no cap hit, so the note stays silent there.
- **Q2's AQ10 quote** is verbatim.
- **Q1 (b) table**, recomputed:
  - 32–35×, 43–47× and 54–58× of W_max (A);
  - restores 8.6, 10.8 and 13.0 s at 1 thread;
  - W1 at 93–121, 117–154 and 140–187 ms;
  - z 3.79–3.80, SE 0.373 %, 26.3×.
- **Q2 against the computations:**
  - (A) matches C14 (b): 0 of 24 cap hits; SE ≤ 0.082 dB at n\*_max 8 000 and ≤ 0.124 dB at 1 020.
  - (A) matches C14 (c): every gated scene restores in 2.14 s.
  - (B) matches C14 (c): 2.16–4.83 s per restore, 30.2–67.6 s for 14.
  - Q2b (ii) recomputed: ≈ 16 000 × 360 × 42.5 ns ≈ 0.245 s.
- **C15 checks out.** All 16 rows pass Seat 2's pre-registered bounds (|median| ≤ 0.25 dB, p95 |error| ≤ 1 dB).

### Numbered corrections

**D-T1.3**

1. **Confirmations not folded into the map.**
   - Seat 2 rated N-3W\*\*\* + U at 1/1. Its own condition (U, 1/1 → 0/1) was "30 replicates in the closed 100 m cubes… |median| ≤ 0.25 dB and p95 ≤ 1 dB", and C15 passes it, so the S2 cell is 0/1 (read from conditions, now met).
   - Seat 4 gives 1/1 with n\*_max from its condition 1, and 2/2 if n\*_max is fixed at 8 000.
   - The map still shows "?" for S2 and "(S4-a)" for S4. The maximum stays 2 (S1). The sum becomes 19, or 20 if Q2b (ii) is chosen.
2. **Seat 4's new condition is missing.** It asks that "the CI report lists any fixture or preset where the pilot estimate ships" (the fallback whose bias is of order 1/n\*). Add it to the decision text and the /fix-plan list.
3. **Seat 5's cell is unconfirmed.** The decider writes that the overrun of at most one block "needs its confirmation of the D4 block size", but Seat 5 was never asked (section C lists only S2, S4 and S6). The D4 block size is pinned nowhere. That matters:
   - **The overrun bound means nothing without it.** At layout 4's e_cal of ≈ 8 800 per emitter, a 256-history block is ≈ 37 % of W_scene, so "pilot ≤ W_scene/2" holds only up to ≈ 0.87 W_scene.
   - **Disjointness.** The final range starts at 8 000. A pilot that stops "at the first block boundary where n ≥ n\*_max" stays clear of it only if n\*_max and 8 000 are block multiples (F12/F14).

   Pin the block size, state the worst overrun as a fraction of W_scene at the worst gated cost, and ask Seat 5.
4. **Name collision.** The decider's "C15 (re-run C13/C14 under the joint rule)" is not the orchestrator's file 31, which is Seat 2's replicate check. Every Q1 and Q2 number comes from the per-emitter rule (C13/C14). The joint rule takes N_need as the maximum over emitters, so "the per-emitter figures are an upper bound on cost" is [Inferred], not shown. Rename the re-run (e.g. C16) in the decision and the /fix-plan list, and keep it before the goldens.
5. **Part of the strongest objection is NOT CHECKABLE.** "The closed 100 m cube is the one place where the switch adds error" rests on an "old error +0.09 / −0.06 dB", which is builder §3's AX16 − (f) at 8 000 paths. That estimate's own SE is 0.097 / 0.112 dB, so the AX16 error there is unresolved, not measured. The table also leaves out the low-α s = 1 cube, which ships SE 0.44–0.64 dB under (A) and has an unknown AX16 error. The same figure appears in Q2 (A) and in For Maisara ("old about 0.1 dB").

**D-T1.4**

6. **Wording inverted and over-claimed.**
   - "Where the work cap binds, the achieved SE is lower than the target allows" means the opposite of what is intended. Write "higher than the target".
   - "Target SE 0.083 dB wherever the cap does not bind" is false at the provisional n\*_max ≈ 1 020. C14 (b): `concert_hall_box` near-wall reaches 0.076–0.124 dB with no cap hit; the smaller pilot underestimates the SE. State that the target is met at n\*_max 8 000 (≤ 0.082 dB) and missed by up to 1.5× at ≈ 1 020. This links to Q2b.

**D-T1.6**

7. **Seat 6's condition (i) is not in the text, so the S6 cell (1/1) is a misread as written.**
   - Seat 6 rates U at **2/1 as written**, because of "±x from the achieved SE". In the both-near branch that SE understates the error by up to ≈ 25×: W1 both_corner has SE 0.081 dB against a replicate SD of 2.04 dB (C13 §3).
   - It is 1/1 only under (i):
     - no ±x from the achieved SE in the both-near branch;
     - in the SE > 0.33 dB branch, ±x only where SE ≥ the replicate SD for that class (layout 4 listener_wall fails: 0.68 against 0.89 dB).
   - Fold (i) into the D-T1.6 text and the phase-11 entry. It is a wording change. Until then the maximum is still 2 (S1) and the winner is unchanged, since NW-2's sum is 21.
8. **Seat 6's condition (ii) is not folded in.** Seat 6 asks that no default placement of a valid fixture or Phase 12 preset raise U: "the preset's placement is fixed, not the predicate". The decision instead has a reversal on the predicate (when SE ≤ 0.1 dB) and a phase-12 check that is only "reported". Reconcile the two, or record Seat 6's (ii) as a phase-12 requirement.
8a. Seat 6's condition (iii) (U′ as a labelled diagnostic tier) is optional. Record it or say it is declined.
9. **"Where U fires" is incomplete (INCONSISTENT with C13 §3).** It lists only layouts 4/5, the low-α s = 1 cube and W1 both_wall/corner. Applying U = both-near AND (cap OR VOV ≥ 0.1) to C13 §3's both-near cases, U also fires on placements in ordinary rooms whose estimates are good:

   | case | why U fires | measured spread |
   |---|---|---|
   | `club` both_wall_0.3 | cap hit | SE 0.071 dB, p95 0.095 dB |
   | `living_room` both_edge_0.3 | cap hit | p95 0.123 dB |
   | `living_room` both_wall_0.1 | VOV 0.28 | p95 0.148 dB |
   | `club` both_edge_0.5 | cap hit | p95 0.27 dB |
   | W1 both_wall_0.3 / 0.5 | cap hit | p95 0.49 / 0.28 dB |

   Seat 6's 3 on U′ cites `club` both_wall_0.3 as a false alarm that only U′ raises, but U raises it too. Seat 6's U cell therefore rests partly on the incomplete list. Recompute the list under the joint rule at both n\*_max values; cap-hit status depends on them. Then put the corrected list to Seat 6 in one line. Only a 3 changes anything, and U′ stays worse on Seat 6's other examples (small room, 100 m default, `dead_booth`).
10. **AX text.** "Next to an absorbing face there is no such rise" holds only for a fully absorbing face. Eq. 2.49 is derived for R = 1, and for 0 < α < 1 the rise is reduced, not absent. Write "reduced, absent at α = 1".

**D-T2 (Q1)**

11. **ℓ_ref figure is WRONG.** "ℓ_ref … up to 0.37 % in the gated set" is wrong. CS-NW+ gates the W1 corner at the 1.25 m reference, whose last halving is 0.63–0.65 % (C12 reading 2; C4), and no finer rung is computable for that room (C12). Under (a) the near-wall class then needs 3·SE ≤ 0.35–0.37 %, i.e. SE ≈ 0.12 % ≈ 0.0051 dB. That is still CI time only, but the packet must carry the right figure.
12. **Precision range.** "Precision bought 0.016–0.019 dB" leaves out L2-F2's 0.0145 dB (3·SE ≤ 1 %). Write 0.0145–0.019 dB, about 1/50–1/70 jnd. (a)'s "target 0.083 dB wherever the cap does not bind" needs item 6's n\*_max qualifier.

**Q2**

13. **Old-error comparison.** In (A), "closed 100 m cubes… old error +0.09 / −0.06 dB" and For Maisara's "old about 0.1 dB" present an unresolved difference as a measured error (item 5). Either state "AX16 − (f) not resolved at SE ≈ 0.1 dB", or have the orchestrator compute AX16 against the 1 M-history long runs C15 already holds (SE 0.005–0.022 dB), including the low-α s = 1 cube. Otherwise Q2's (A), (B) and (C) lines are correct against C14.

**/fix-plan list**

14. Add:
    - Seat 6 (i) to phase-11;
    - Seat 6 (ii) to phase-12 (as a requirement, or with the reconciled wording);
    - Seat 4's CI list of pilot-estimate ships;
    - the pinned D4 block size (D-T1.1 / D-T1.3 AX rows);
    - the renamed joint-rule re-run (item 4);
    - the AX16 − long-run computation, if item 5's claim is kept.

### For the orchestrator
- **(f)** Recompute "where U fires" under N-3W\*\*\* (joint) at n\*_max 8 000 and ≈ 1 020 on C13 §2 and §3, C14 (b) and (d), and the C14 cubes.
- **(g)** AX16 E_target against the C15 1 M-history long runs for the 100 m cubes (s = 0.3, low-α s = 1, absorbing floor).
- **(h)** The D4 block size and the worst one-block overrun as a fraction of W_scene at each gated scene.

### Questions for the decider
1. Will you fold Seat 6's (i) into U's text and the phase-11 entry, and correct "Where U fires" (item 9) before Seat 6 re-confirms?
2. What D4 block size do you pin? Is 8 000 a block multiple? What does Seat 5 rate the overrun bound?
3. Does the Q1 (a) packet carry ℓ_ref = 0.65 % (W1 corner) and the resulting near-wall CI SE?
4. Is the "+0.09 / −0.06 dB old error" at the 100 m cubes kept? If so, on what measured AX16 − (f) at SE well below 0.1 dB?

### New ledger rows

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-37 | Corrections 1, 3, 6, 9–14, 17, 18 applied | faithful | closed |
| P05B2-T1T2T6-38 | 70 cases / 560 case-bands, z_FW 4.290; D-T6 72 case-bands, z_FW 3.81; Q1 (b) table; Q2 (A)/(B) against C14 | CORRECT | closed |
| P05B2-T1T2T6-39 | Seat 7 D-T6 cells and conditions (i)–(iii) | faithful | closed |
| P05B2-T1T2T6-40 | C15: 16/16 rows pass Seat 2's pre-registered bounds | CORRECT | closed |
| P05B2-T1T2T6-41 | D-T1.3 map: S2 "?" should be 0/1 (condition met by C15); S4 1/1 (2/2 if n\*_max 8 000) | correction (not folded) | open |
| P05B2-T1T2T6-42 | Seat 4's CI list of pilot-estimate ships not in text or /fix-plan | correction | open |
| P05B2-T1T2T6-43 | D4 block size unpinned; Seat 5's confirmation not sought; overrun bound and 8 000-start disjointness depend on it | open premise (Seat 5 cell unconfirmed) | open |
| P05B2-T1T2T6-44 | "C15 re-run under joint rule" collides with file 31; per-emitter figures as an upper bound on cost are [Inferred] | correction | open |
| P05B2-T1T2T6-45 | "Old error +0.09 / −0.06 dB" at 100 m cubes (builder §3, within estimator SE 0.10–0.11 dB); "the one place the switch adds error"; low-α s = 1 cube omitted | NOT CHECKABLE (unresolved) | open (compute (g)) |
| P05B2-T1T2T6-46 | D-T1.4 "achieved SE lower than the target allows" (inverted); "target met wherever cap does not bind" false at n\*_max ≈ 1 020 (0.124 dB) | IMPRECISE | open |
| P05B2-T1T2T6-47 | D-T1.6 S6 shown 1/1, but Seat 6 rates U as written 2/1; its condition (i) not in the text | TENSION MISREAD (fold-in pending; winner unchanged) | open |
| P05B2-T1T2T6-48 | Seat 6 (ii) (presets: fix placement, not predicate) against the decider's reversal and phase-12 "reported"; (iii) unrecorded | correction | open |
| P05B2-T1T2T6-49 | "Where U fires" omits both-near placements in `club`, `living_room` and W1 at 0.1–0.5 m with good estimates; Seat 6's U′ example also fires under U | INCONSISTENT (with C13 §3) | open (compute (f)) |
| P05B2-T1T2T6-50 | AX text "no such rise next to an absorbing face" | IMPRECISE (R = 1 derivation; reduced for α < 1) | open |
| P05B2-T1T2T6-51 | Q1 (a) "ℓ_ref up to 0.37 % in the gated set" (W1 corner 0.63–0.65 %, CS-NW+) | WRONG | open |
| P05B2-T1T2T6-52 | Q1 (b) precision range omits L2-F2's 0.0145 dB | IMPRECISE | open |
| P05B2-T1T2T6-53 | /fix-plan list missing Seat 6 (i)/(ii), Seat 4's CI list, D4 block size, renamed re-run | correction | open |
| P05B2-T1T2T6-54 | D-T1.1, D-T1.2, D-T1.5, D-T6 round-3 verdicts | SURVIVES | closed |
| P05B2-T1T2T6-55 | D-T1.3, D-T1.4, D-T1.6, D-T2 (Q1), Q2 round-3 verdicts | SURVIVES WITH CORRECTIONS | open until applied |

Files:
- /home/user/makroof/docs/review/phase-05b2/29-decider-round3-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/30-seat6-confirm-S6a.md
- /home/user/makroof/docs/review/phase-05b2/30-seat2-confirm-S2a.md
- /home/user/makroof/docs/review/phase-05b2/30-seat4-confirm-S4a.md
- /home/user/makroof/docs/review/phase-05b2/27-orchestrator-C14.md
- /home/user/makroof/docs/review/phase-05b2/31-orchestrator-C15.md
- /home/user/makroof/docs/review/phase-05b2/24-orchestrator-C13.md
- /home/user/makroof/docs/review/phase-05b2/7-builder-D-T1-evidence.md
