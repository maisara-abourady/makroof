# Interrogator — decision mode, D-T1 (all parts), D-T2 and D-T6

Verbatim final output of the agent (extracted from its transcript by the orchestrator, 2026-11-10).

## Interrogator, decision mode: D-T1 (all parts), D-T2 and D-T6, rounds 1 and 2 (phase 05b session 2)

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Read:**
- the decisions (files 21 and 25) and the convenings (9 and 17);
- all 18 seat reports (18-* and 23-*);
- the computations: 7, 16, 19, 20, 22 (C12) and 24 (C13, corrected);
- `phase05b2_dt1.json` (sections c13 and c13g; I re-tabulated the C13 cases from the JSON);
- the fixtures `tests/scenes/valid/*.json`;
- BUILD_PLAN AQ10, AQ3, AX17 and AX28;
- corpus: Kuttruff §2.5 (Eqs. 2.49–2.50, L1544–1552), §4.5 (Eqs. 4.24–4.35), §5.2 (L2505) and §8.7 (L3982, Waterhouse); Vorländer Table 6.1, §11 (EASE / Fig. 11.38) and Ch. 15 intro (L3869).

### Verdicts

| id | verdict | in one line |
|---|---|---|
| D-T1.1 (T1-F\* + D1–D7) | **SURVIVES WITH CORRECTIONS** | Every cell is faithful; the corrections are a citation fix and stating that "max 1" holds only if Q1 = (a). |
| D-T1.2 (S-1) | **SURVIVES** | Every cell faithful; sums correct. |
| D-T1.3 (N-3W\*\*, W_max provisional) | **FAILS (rule text, fixable at parameter level)** | The rule does not bound the 256-history calibration block, so "pilot ≤ W_max/2" and "N ≥ pilot", which seven † cells rest on, fail in C13's own data. Seat 2's † cell is misread. N_cap is ambiguous. |
| D-T1.4 (Tol-2) | **SURVIVES WITH CORRECTIONS** | Cells faithful; D4-L2 claims too much; the register is stale against W_max. |
| D-T1.5 (CS-3 + CS-NW+) | **SURVIVES WITH CORRECTIONS** | The CS-1 row misreads S3 and S6 (the true cells are 1/3, a veto). The winner is unchanged. The case count is inconsistent. |
| D-T1.6 (NW-4C+) | **SURVIVES WITH CORRECTIONS** | The AX-row physics needs its rigid-wall condition. The S6 note reading is defensible but must be confirmed, and it collides with Seat 2's C5. The 0.70 m threshold sits exactly on `dead_booth`'s default. The register has no UI-phase row. |
| D-T2 (NEEDS MAISARA, Q1) | **SURVIVES WITH CORRECTIONS (as a Maisara packet)** | The ordering is correct and Q1 is a fair question, but both cost lines need fixing (below). |
| D-T6 (RS-2+ / B6-1F / M-2) | **UNDERCONVENED (Seat 7)**, then corrections | The decision is the basis for the "uniform rooms unchanged" claim, which is Seat 7's public-wording item. The fixed small room is a both-near scene under D-T1.6. |

### What checks out
- **Convening of D-T1 and D-T2.** All nine seats were convened, and all nine rated rounds 1 and 2.
- **Cells.** Every cell of every round-1 map matches the seat's own words: T1-A/B/F, S-1/S-2, N-1/2/3, Tol-1/2/3, CS rows (apart from the CS-1 exception below), NW-1/2/3/4, L2-F1/F2, and the RS, B6 and M rows. The round-2 cells for NW-4C+, NW-3, N-3W\* as composed, L2-F1R and the bias reading also match. I re-read each seat.
- **Sums.** All correct, except the round-2 aside "N-2 (sum 23)", which is 22.
- **Corpus re-checked:**
  - Vorländer Table 6.1: G jnd 1 dB, 500–1000 Hz.
  - Kuttruff Eq. 2.50 and L1552: in a diffuse field the phase effects reach about half a wavelength, and |p|² doubles at a rigid wall.
  - Fig. 11.38: diffuse rain scores a detector sphere of radius r_k.
- **Computations redone:**
  - 1.911 %/√2 = 1.351 %; P(|Δ| < 1 %) = 0.541; SE ≤ 0.430 % = 0.0187 dB; (1.911/0.430)² = 19.75.
  - W_max = (2.143 − 1.884)/2/42.5 ns = 3.05 M.
  - Blend cap 2/(π(d_L² + d_E²)) = 0.159 and 31.8 m⁻².
  - (1.113/0.33)² = 11.4.
  - Seat 9's Eq. 2.50 values: +2.93 / +2.71 / +1.84 / −0.64 dB.
  - The n\*_max crossing: 24.5 µs·n\* gives n\* ≈ 1 021.
- **Load-bearing claims confirmed against C3, C7, C12 and C13:** D1-L2, D1-L3, D1-L4, D16-L1, D16-L2, D16-L3, D16-L5, D16-L6, D13-L1, D13-L2, D5-L1, D5-L3, D6-L1, D6-L2.
- **The C13 §2 mismatch is resolved.** The corrected reading 3 now gives both comparisons, and the decider's figures (−0.35 to −6.72 dB against the long runs) come from the unchanged table.
- **Seat 9's request about W1.** B6-1 is a relation between C++ and reference, not a number fitted after seeing W1's prototype ΔL (+0.32 / +0.27 dB). The "before any number" rule holds.

### Numbered corrections

**D-T1.3 (these make it fail)**

1. **The calibration block has no work bound (INCONSISTENT with C13).** The rule samples a fixed block [0, 256) to get e_cal, then sets n\* = min(n\*_max, ⌊(W_max/2)/e_cal⌋). Once e_cal > W_max/512 (≈ 5 960 evaluations per history), the calibration block alone costs more than W_max/2. C13 shows it in three layout-4 cases:

   | case | e_cal | pilot work / W_max | final N | n\* |
   |---|---|---|---|---|
   | listener_corner | 7 049 | 0.59 | 176 | 256 |
   | emitter_corner | 7 598 | 0.64 | 145 | 256 |
   | both_corner | 8 791 | 0.74 | 90 | 256 |

   So both conditions the † cells were read on fail:
   - "pilot ≤ W_max/2": Seats 1, 2, 3, 5, 6, 7, 9;
   - "final N ≥ pilot": Seats 1, 2, 3, 5, 6, 9.

   Once e_cal > W_max/256 (≈ 11 900), the calibration block exceeds W_max itself, and the work cap that is Seat 5's restore protection no longer bounds work. The decision text also leaves undefined what happens when ⌊(W_max/2)/e_cal⌋ < 256. The † cells hold only for scenes with e_cal below ≈ 5 960.
2. **Seat 2's † cell is misread.** Two of its conditions are not met as written:
   - C1 (the pilot stops on cumulative work) is replaced by Seat 4's rule of sizing before sampling. The decider flagged this, but asked Seat 5 to confirm; it is Seat 2's condition.
   - C5 says "VOV goes to diagnostics only" and makes the cap hit and both-near flag the user-visible flags. The decision makes VOV a note trigger and hides the bare cap hit.

   Seat 2 must rate N-3W\*\* as written. The winner changes only if it rates 3.
3. **N_cap is ambiguous.** N_cap = ⌊(2·W_max − W_pilot,both)/ē_pilot⌋ divides the two-emitter remaining budget, but the text does not say whether N and N_cap are per emitter or joint. Read per emitter, the two final ranges together can use about twice the restore budget. State whether n\*, N and N_cap are joint (one history = both forward paths plus the shared listener path) or per emitter, and give the split.
4. **Q2's cost lines.**
   - (A) "six Phase 04 rooms' one-end cases have no cap hits" was measured only at C12's W_max (14.6 M), not at 3.05 M. C13 holds no such cases (JSON section c13). It is probably true, but it is [Inferred], not measured.
   - (A) gives the old method's error as "+3.87 dB"; layout 5's is −1.17 dB. State both.
   - (B) "restore about 2.6 s" depends on n\*_max:
     - at n\*_max ≈ 1 020 (the prototype value) the worst gated scene is the flutter cube at ≈ 1.884 + 2·0.42 ≈ 2.7 s;
     - at n\*_max = 8 000 (as C13 ran), N ≥ n\* makes the flutter cube use the whole cap, giving 1.884 + 11.4 × 0.259 ≈ 4.8 s.

     In both cases 14 restores exceed pluginval's 30 s (38–68 s). Say so.
   - AQ10 is misquoted. AQ10 says full rebuilds are never met "by shortening the image list or N_cap"; output changes go through AX20/AX22 and /fix-plan. It does not say "never met by changing the output". The challenge still stands on "recorded, not budgeted".
   - The decider treats the two time-sized parameters differently without saying why. n\*_max is sized to 25 ms of the AQ10 W1 *target* and also changes shipped output (W1-class final SE ≈ 0.023 dB at 8 000 histories becomes ≈ 0.064 dB at ≈ 1 020). Explain why it is not also an AQ10 challenge, or add it to Q2.
5. **D7 and the realised-work overrun are faithful.** C13 shows realised work up to 1.02 × W_max (layout-4 reference positions). That is within the declared scatter, so nothing to correct.

**D-T1.6**

6. **The AX-row text needs its condition (CONDITIONS VIOLATED as written).** Eq. 2.50 is derived for a rigid wall (R = 1, Eq. 2.49). Restate: "within about half a wavelength of a *reflecting* surface the GA tail ignores the near-wall pressure rise, up to +3 dB at a rigid wall (Kuttruff Eq. 2.50, §8.7)". Next to an absorbing face (layout 4 floor, layout 5 wall) there is no such rise.
7. **The S6 note-trigger reading the decider asked me to check.**
   - Seat 6's literal trigger (23-seat6, condition 3) is "VOV ≥ 0.1".
   - The added qualifier (pilot SE > target/3, i.e. 0.028 dB) is Seat 1's escalation rule, not Seat 6's.
   - The reading fits Seat 6's premortem. It suppresses the note exactly at the flutter cube (pilot SE 0.011 / 0.0012 dB, VOV 0.512 / 0.100; JSON c13) and still raises it at cube100 (pilot SE 0.117 / 0.192 dB, VOV 0.31 / 0.37). The qualifier only suppresses where R < 0.0064, well below F11's R < 0.05 failure regime.
   - So the reading is defensible on Seat 6's stated aims. It still changes Seat 6's own predicate, so the cell is read from an amended condition: one line from Seat 6 confirms it.
   - The note design also conflicts with Seat 2's C5 (correction 2) and Seat 8's (ii) ("any cap hit … as approximate"). The decider must say which seat's condition each trigger meets and which it leaves unmet.
8. **The both-near threshold sits on a knife-edge.** `dead_booth`'s default listener is at d_L = 0.700 m exactly, and its emitters at 0.5 m (fixture). With a strict "<", whether a Phase 04 preset shows "approximate" at its default placement depends on how the host-parameter mapping rounds 0.7. The decider's strongest objection names the booth but not this. The reversal test should cover the default placement itself.
9. **Missing register row.** The UI phase is committed to the "approximate" note: settled scene only, info view, wording by Seats 6 and 7. Add a row and a /fix-plan entry; round 2 has no /fix-plan list.

**D-T1.1, D-T1.4, D-T1.5**

10. **D-T1.1 text.** "Injection s(1−α) per Kuttruff Eq. 4.24" carries the citation I corrected in D-T5.1: Eq. 4.24 is Lambert's law, and the s(1−α) / (1−s)(1−α) split is §5.2 (L2505) and §2.7. "Unbiased because s is band-independent (AQ3)" should cite AX17 (broadband s); AQ3 only sets the range.
11. **D-T1.1 "max 1" holds only under Q1 = (a).**
    - S4's T1-F cell reads "later 2 under L2-F2", and L2-F1R is the same class: Seat 4's L2-F1R reason is that it "makes the split update mandatory".
    - S6's reached 3 under NW-1 + L2-F2, and NW-4C reverts to NW-1 behaviour when both ends are near a surface.

    State that under Q1 (b) these cells reopen. T1-F stays the only survivor. Also mark S3's resolution as † (read from "NW-1 under N-3 with a time-bounded N_max"). Correct the register's "repaid when the BRAS nightly holds": an in-repo run cannot repay a debt that is about published validation.
12. **D4-L2 claims too much.** τ = 1 dB fails to catch AX16 in the cases where |ΔL| ≤ 0.43 dB: uniform-α, the Phase 04 rooms, CR2 (C2). It would catch it in layouts 4–6 (+3.83, −1.12, −1.14 dB). The veto stands on Seat 2's words, which name exactly those cases.
13. **D-T1.4 register is stale.** The row "≈ 1.5 s in layout 4 at s = 1" is superseded by W_max (A): layout 4 is capped at ≈ 0.13 s per emitter and ships SE 0.39–1.11 dB. The shipped 0.083 dB target is not reached where W_max binds; cross-reference D-T1.3 and Q2. S7's Tol-2 reason ("'uniform rooms unchanged' stays claimable" via B6-2) rests on B6-2, which D-T6 demotes to a flag. Ask Seat 7 (ties to correction 18).
14. **D-T1.5 CS-1 row (a non-winning row is misread).**
    - Seat 3 gives CS-1 1/2 plus "+1 later on any set" without CS-NW, and Seat 6 gives CS-1 1/2 plus "later rises by 1". The row is the no-NW form, as S1's 2/2 "any set without NW" shows. S3 and S6 are therefore 1/3: a veto.
    - CS-1 also has S7 0/2 and S8 2/2, and it lost anyway, so the winner is unchanged. Correct the row.
    - The case count is inconsistent: "roughly 50 cases" (the D-T2 working, and Q1's 4.9 %) against 64 (Seat 1's z_FW over 512 case-bands; "64 cases" in For Maisara). Fix the pre-registered count, since z_FW depends on it. At 64 cases, p ≥ 0.999 per case gives a 6.2 % family false-fail.

**D-T2 (Q1 packet)**

15. **Q1 (a).**
    - "Users get today's precision (0.083 dB)" is not accurate. There is no "today's" SE, and 0.083 dB is the Tol-2 *target*. Under Q2 (A), capped scenes ship 0.39–1.11 dB (layouts 4/5) and 0.14–0.20 dB (100 m cube).
    - The < 1 % bias test against "the converged reference" has a hidden premise: the reference is laddered only to "last halving < 1 %", and it drifts toward (f) by up to 0.58 % at 2.5 m (19 §2). The 1 % must budget ℓ_ref, as D-T1.4's τ does, or the test fails a correct estimator.
    - The bias reading's "board max 1" has eight cells. S4 states a preference but no cell.
16. **Q1 (b).**
    - It shows only L2-F1R (19.75×, p ≥ 0.999 per case). By Seat 1's arithmetic (redone) that is a 4.9 % family false-fail over 50 cases and 6.2 % over 64, with reseeding forbidden. Family α 1 % needs z ≈ 3.72–3.78 and ≈ 25–26×. L2-F2 (AX11's threshold/3, 33×), which Seat 2 called "the faithful transfer", appeared in round 1's table and has been dropped. Show all three.
    - "About 7× W_max" is relative to C12's 14.6 M. Against the provisional W_max (A) = 3.05 M, the 100 m cube needs ≈ 98 M evaluations, ≈ 32× W_max.
    - "W1 72–100 ms" is the diffuse share alone. W1 itself would be ≈ 93–121 ms (20.6 ms + diffuse).
    - The thread counts are mixed (3.7 s at 4 threads, 8.6 s at 1 thread). Label each.

**D-T6**

17. **UNDERCONVENED: Seat 7.** The README row covers "public wording and marketing claims". D-T6 sets the bound behind phase-05b2's "in uniform-α rooms nothing audible changed". Seat 7's own D-T1.4 reasons tie that claim to B6-2: under Tol-1, "'nothing audible changed in uniform rooms' cannot be said". D-T6 demotes B6-2 to a flag, so the claim then rests on the report, not on a gate. Seat 7 did not answer NOT MY MATTER ("not convened on D-T6"). One Seat 7 rating of RS-2+ / B6-1F / M-2 is needed.
18. **D-T6 conflicts with D-T1.6 (INCONSISTENT).** The fixed small room (3 × 2.5 × 2.5 m; listener (1.5, 0.667, 0.425) m, emitters at z = 0.5 m) has d_L = 0.425 m and d_E = 0.5 m. Under D-T1.6's criterion (< 0.70 m) it is a both-near scene, where the shipped error is "reported, not bounded" and the note fires. D-T6 gates it at τ = 0.25 dB. State the N at which the D-T6 gate runs: test N under D-T1.5's family rule, or shipping N. Also adopt D-T1.5's stage-2 / no-reseed rule. Seat 5 (round 1) flagged that a first-draw fail of this gate "has no legitimate fix".

### For the orchestrator to compute or fix
- **(a)** e_cal and calibration-block work (256·e_cal against W_max/2 and W_max) at D-T4c's actual gated 100 m builds. C12/C13's "cube100" has α 0.10–0.22. The closed low-α (≈ 0.05) cube is Seat 9's cost-worst box and is unmeasured. Also at one long-window worst case (100 m, absorbing floor, s = 1, AX22 fallback).
- **(b)** Rerun C12 (d) "continued" (the six Phase 04 rooms, listener then emitter at 0.1 m) at W_max = 3.05 M under the decided rule (N ≥ n\*, both n\*_max values).
- **(c)** Q2 (B) restore at the gated scenes under the decided rule, at n\*_max = 8 000 and ≈ 1 020.
- **(d)** The D-T6 small room under NW-4C / N-3W\*\*: both-near flag, cap hit, VOV, replicate error against its laddered reference.
- **(e)** The exact gated case count of CS-3 + CS-NW+ and the resulting z_FW.

### Questions for the decider's rebuttal, most consequential first
1. **D-T1.3.** What bounds the [0, 256) calibration block in work, and what is n\* when ⌊(W_max/2)/e_cal⌋ < 256? C13 rows layout-4 listener_corner, emitter_corner and both_corner show pilot work 0.59–0.74 W_max and N < n\*. Re-read the † cells against the revised rule.
2. **D-T1.3 / D-T1.6.** Which user-facing note triggers meet which seat's conditions? Seat 2's C5 (VOV diagnostics-only; cap hit user-visible), Seat 6's condition 3 (VOV ≥ 0.1, not the bare cap hit) and Seat 8's (ii) conflict. Do Seats 2 and 6 confirm their cells on the text as written?
3. **D-T6.** What does Seat 7 rate RS-2+ / B6-1F / M-2? And how does the D-T6 gate treat a small room that D-T1.6 classifies as both-near (d_L 0.425 m, d_E 0.5 m)?
4. **Q1.** Restate (a)'s shipped precision with the Q2 coupling and the ℓ_ref budget. Restate (b) with all three strict variants (19.75×, ≈ 25–26×, 33×) and with W_max in the units of the provisional value (≈ 32× at 100 m).
5. **Q2.** Give (B)'s restore at both n\*_max values with the watchdog consequence, quote AQ10 exactly, and say why n\*_max (sized to the W1 target, output-changing) is not part of the AQ10 challenge.

### Ledger rows (`docs/review/ledger.md`)

| id | item | verdict | status |
|---|---|---|---|
| P05B2-T1T2T6-01 | D-T1/D-T2 convening: 9/9 convened, every seat rated both rounds | faithful | closed |
| P05B2-T1T2T6-02 | Round-1 and round-2 tension cells (all ids) against seats' words, except rows 14, 15 | faithful | closed |
| P05B2-T1T2T6-03 | D1-L2, D1-L3, D1-L4 (C3, C7, 19 §2/§6) | CORRECT | closed |
| P05B2-T1T2T6-04 | D-T1.1 "injection s(1−α) per Eq. 4.24"; "AQ3" for band-independent s | IMPRECISE (§5.2/§2.7; AX17) | open |
| P05B2-T1T2T6-05 | D-T1.1 "max 1" holds only under Q1 (a) (S4, S6 cells); S3 resolution unmarked †; register "BRAS nightly" repays a published-validation debt | IMPRECISE | open |
| P05B2-T1T2T6-06 | D-T1.2 S-1 | SURVIVES | closed |
| P05B2-T1T2T6-07 | D-T1.4 D4-L1 (Table 6.1), D4-L3 (gate B δ 0.25 jnd) | CORRECT | closed |
| P05B2-T1T2T6-08 | D-T1.4 D4-L2 "τ = 1 dB cannot detect AX16" | IMPRECISE (true only where \|ΔL\| ≤ 0.43 dB) | open |
| P05B2-T1T2T6-09 | D-T1.4 register stale against W_max (A); shipped 0.083 dB not reached where capped; S7 Tol-2 reason rests on B6-2 | IMPRECISE | open |
| P05B2-T1T2T6-10 | D-T1.5 CS-1 row S3, S6 should be 1/3 ("+1 later without NW") | TENSION MISREAD (non-winning row; winner unchanged) | open |
| P05B2-T1T2T6-11 | D-T1.5 case count 50 vs 64 (z_FW, family false-fail) | INCONSISTENT | open |
| P05B2-T1T2T6-12 | D5-L1, D5-L3 | CORRECT | closed |
| P05B2-T1T2T6-13 | D16-L1, L2, L3, L5, L6, L7 (C12, C13, 19; blend cap algebra) | CORRECT | closed |
| P05B2-T1T2T6-14 | D-T1.6 AX row "within λ/2 of a surface … pressure rise (Eq. 2.50)" | CONDITIONS VIOLATED (rigid wall, R = 1) | open |
| P05B2-T1T2T6-15 | D-T1.6 note qualifier "pilot SE > target/3" read as Seat 6's | defensible but amended condition; needs Seat 6 confirmation; conflicts with S2 C5 and S8 (ii) | open |
| P05B2-T1T2T6-16 | D-T1.6 both-near threshold 0.70 m equals `dead_booth` default d_L | open risk (knife-edge) | open |
| P05B2-T1T2T6-17 | D-T1.6 register lacks UI-phase row ("approximate" note); no /fix-plan list in round 2 | debt not registered | open |
| P05B2-T1T2T6-18 | C13 §2 table/reading mismatch | resolved (C13 corrected; decider cited the table) | closed |
| P05B2-T1T2T6-19 | D-T1.3 calibration block unbounded; pilot ≤ W_max/2 and N ≥ n\* violated in C13 layout-4 corners; cap not a bound for e_cal > W_max/256 | INCONSISTENT / CONDITIONS VIOLATED | open |
| P05B2-T1T2T6-20 | D-T1.3 S2 † cell (C1 replaced by pre-sampling rule; C5 unmet) | TENSION MISREAD | open |
| P05B2-T1T2T6-21 | D-T1.3 N_cap per-emitter vs joint accounting | INCONSISTENT (ambiguous; up to ~2× restore budget) | open |
| P05B2-T1T2T6-22 | D-T1.3 working: N-3 (round 1, sum 17) set aside as the unspecified parent of N-3W\*\* | accepted (reasoning exposed; not a §5 step) | closed |
| P05B2-T1T2T6-23 | W_max = 3.05 M arithmetic; D7 | CORRECT | closed |
| P05B2-T1T2T6-24 | Q2 (A) "six Phase 04 rooms no cap hits" at 3.05 M | NOT CHECKABLE (measured only at 14.6 M) | open (compute) |
| P05B2-T1T2T6-25 | Q2 (B) restore "≈ 2.6 s" | IMPRECISE (2.7 s at n\*_max ≈ 1 020; ≈ 4.8 s at 8 000; watchdog exceeded either way) | open |
| P05B2-T1T2T6-26 | Q2 AQ10 quotation; n\*_max not treated as an AQ10 matter | IMPRECISE / INCONSISTENT | open |
| P05B2-T1T2T6-27 | D-T2 ordering: both in-bounds options carry S5's 3; bias reading out of bounds; NEEDS MAISARA | CORRECT | closed |
| P05B2-T1T2T6-28 | D-T2 arithmetic 0.541, 0.430 %, 19.75×, 33× | CORRECT | closed |
| P05B2-T1T2T6-29 | Q1 (a) "today's precision"; hidden ℓ_ref premise in the < 1 % bias test; S4 no cell | IMPRECISE | open |
| P05B2-T1T2T6-30 | Q1 (b) omits ≈ 25–26× (family 1 %) and L2-F2 33×; "7× W_max" in old units (≈ 32× of W_max (A)); W1 figure is diffuse share only | IMPRECISE | open |
| P05B2-T1T2T6-31 | Round-1 attribution "Seats 4, 5, 6, 8 rated L2-F1 as keeping Tol-2 cost" (S4, S8 stated no cost premise) | IMPRECISE (superseded by round 2) | closed |
| P05B2-T1T2T6-32 | D-T6 convening: Seat 7 (public wording, "uniform rooms unchanged") not convened | UNDERCONVENED | open |
| P05B2-T1T2T6-33 | D-T6 small room is both-near under D-T1.6 (d_L 0.425, d_E 0.5 m) yet gated at τ | INCONSISTENT | open |
| P05B2-T1T2T6-34 | D-T6 gate N and stage-2 / no-reseed rule unstated (Seat 5 round 1) | IMPRECISE | open |
| P05B2-T1T2T6-35 | D-T6 cells, sums, D6-L1, D6-L2; W1 "before any number" (B6-1 is a relation) | CORRECT / faithful | closed |
| P05B2-T1T2T6-36 | Orchestrator computations (a)–(e) above | requested | open |

Files:
- /home/user/makroof/docs/review/phase-05b2/21-decider-decision-T1-T2-T6.md
- /home/user/makroof/docs/review/phase-05b2/25-decider-round2-T1-T2.md
- /home/user/makroof/docs/review/phase-05b2/24-orchestrator-C13.md
- /home/user/makroof/docs/review/phase-05b2/22-orchestrator-C12.md
- /home/user/makroof/docs/review/phase-05b2/23-seat2-round2-T1-T2.md
- /home/user/makroof/docs/review/phase-05b2/23-seat6-round2-T1-T2.md
- /home/user/makroof/docs/review/phase-05b2/18-seat7-T1-T2.md
- /home/user/makroof/tools/validation/data/phase05b2_dt1.json
- /home/user/makroof/tests/scenes/valid/dead_booth.json
