# Decider — rebuttal round 2 for D-H1 and D-H2 (phase 05h session 2, `/fix-plan` step 3e)

Save as `docs/review/phase-05h/19-decider-decision-D-H1-D-H2-r2.md`. Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`, 14 files). Answers `/home/user/makroof/docs/review/phase-05h/15-interrogator-D-H1-D-H2.md` on `8-decider-decision-D-H1-D-H2.md`. D-H3 is not touched.

Read this round: file 15 in full; `5-seat1…5-seat9-D-H1-D-H2.md` (Seat 6: `5-seat6-D-H1.md`), `5-researcher-RQ-H1-H2.md` (as cited in file 8), files 1, 7, 10; BUILD_PLAN §2 AQ3 (L88), AQ10 (L95), AX38 4c (L138), AX40, AX41, AX43, AX44 (L140–144); phase-05h §1 L42 (her 2026-11-09 words), §2 item 1 (L83–88), §3 "Starting state" (L140–143), §5 "Blocking" row (L262–265); phase-07c §5 conditions 1–8 (L72–107), §9 (L144–147); PRD L15–55 (L20 primary users; L49 "Accuracy first"; L55 "no fixed deadline"), L70–112 (L73–74 FR-3D-3/4, L89 FR-SIM-6, L101 NFR preamble, L105–112 NFR-1…8); session brief O18, O20 (L150, L152). `docs/review/phase-05h/17-seat5-D-H3.md` does not exist at the time of reading (Glob `17-seat5*` empty), so Seat 5's R-e cell is not on file: R-e is restated below and both branches are shown (P05H-04).

**State of the decisions after this round:** D-H1 (i) P-a′, (iii) Q-d, (iv), (v) W-x′: **stand, with corrections**. D-H1 (ii): **revised** (R-e restated so the starting state is a record; the cell and the working redone). D-H1 register: **revised** (rows added). H1-F1, H1-F2: **stand, with corrections**. H1-F3: **revised** (re-answered on NFR-1 and the plan text, FR-3D-3/4 dropped as support, both readings shown). D-H2 (a)–(d), H2-F1: **stand, with corrections** (sums, two register debts).

The PRD digest of `4-decider-convene-D-H1-D-H2.md` stands, with file 8's added line. One line is corrected here: *FR-3D-4 with AQ3 (s ∈ [0, 1], α ∈ [0.01, 1]) and AX6 (100 m maximum) lets a user build the α 0.05 / s = 1 cube; "no preset approaches it" is a fixture fact from the code (Seat 9), not a PRD fact.*

---

## Answers to file 15, in order of consequence

**1. P05H-04 (TENSION MISREAD, D-H1 (ii), Seat 5 × R-e).** Conceded: file 8's (ii) stored the starting-state SE and p95 "in the flags golden and never regenerated to pass", which is the mechanism Seat 5 priced at 1 (file 5-seat5 §3 L35: "Needs a frozen starting-state replicate SD per scene as a golden with a never-regenerate rule"; §4 L56: "a never-regenerate golden (SD per scene) that must survive every W_max re-derivation"). The 0 was my parenthetical, not the seat's. Seat 5 has been asked; its answer is not on file. R-e is therefore **restated** (D-H1 (ii) below) so that the starting state is a **record** (file 10's replicate table, cited in the 05h PR and the ledger, reproduced as the baseline column of the margin report), with no golden, no stored SD and no assertion; the two thresholds are constants in plan text. Seat 5's cell under the restatement is read from its R-c words, the one R option that compares a later value against the starting state with no golden: **0 / 1 (rfc)**, §3 L34 "One constant; no derived golden", §4 L55 "one constant in plan text". Steps 3–7 are redone below under both readings: (A) 0 / 1 → R-e 6 < R-d 7, R-e stands; (B) Seat 5 answers 1 / 1 → R-e 7 = R-d 7, max 1 both, no composition available (no seat at 2), reversibility in Seat 5's own words (R-d undo "—", §4 L57; R-c undo "parameter", L55) favours R-d, and R would **change to R-d** (the escalation lines are identical; only the record sentence is removed). The decision is R-e on reading (A); the reversal condition names Seat 5's answer.

**2. P05H-03 (Seat 2 × W-x).** W-x′ inherits Seat 2's **W-a cell, 0 / 1**: Seat 2's W ranking is "W-a, with my condition in §6 (the finding names the component and a remedy)" (file 5-seat2 L16); W-x′ keeps W-a's W_max and remedy and meets that condition by name (L46: the finding names `tail::BandNoiseGenerator` at 12 s × 96 kHz, states that (C) does not cure macOS, routes the remedy to 07c/07d by name). Seat 2's W-e 1 now is for one thing, L30: "Changes which OS is enforced, nothing in my measures", and W-x′ does not change which OS is enforced (all three OSes run the check; failures are listed, not exempted). Sum 17. If the interrogator reads the register form as the loosening Seat 2 left "Seat 5's loosening to judge" (L30), the cell is 1 / 1 and the sum 18; W-x′ still wins (W-a 21 next). Named as the composed variant **W-x′** (P05H-10).

**3. P05H-05, -06, -07 (register).** Rows added for every later-1 cell on P-a′ (Seats 2, 3, 5, 6, 7, 8) and R-e (Seats 5, 6, 7, 9), marked "discharged by file 10" where so; Seat 8's condition (file 5-seat8 L24) carried into (v) and row 8; the "repaid when" rows name the plan edit that creates phase-07c §5 condition 9 (07c has 1–8; no `phase-07d.md` exists; 07d conditional).

**4. P05H-24 (PRD MISREAD, H1-F3).** Re-answered below: FR-3D-3/FR-3D-4 dropped as support; "user-set" dropped; FR-3D-4 + AQ3 + AX6 stated as letting a user build the cube, with what protects that user (AX44's U; P-a′'s p95 line); both readings of "escalated once" shown; NFR-1's bearing stated. Substance kept (finding listed once; escalation at p95 > 1 dB).

**5. P05H-19, -20, -22, -23.** (v)(a) rewritten so no OS/scene is unasserted; phase-05h §5 "Blocking" row and phase-07c §5/§9 named among the amended texts; PRD L55 on the W-c line with the random-vs-systematic weighing; PRD L101 cited beside NFR-2 in H1-F1 and H1-F2.

**6. Restatements applied:** R-a 17 / R-b 13 (P05H-08); "≈ 2.5× from 48 to 96 kHz (file 7: 1 321 → 3 287 ms)" (P05H-13); "1.2–2.4 %" (P05H-16); D-H2 sums U-c 10, M-a 13, M-c live 17, B-b 12 (P05H-26); the G-a and U-a debts in rows 2 and 5 (P05H-27). Items SURVIVES without a question (P05H-01, -02, -09, -11, -12, -14, -15, -17, -18, -21, -25, -28, -29, -30): no change.

---

## D-H1 — the margin, the two OPEN premises, W_max / n\*_max, the blocking gate

### Knowledge inventory (final; changes against file 8 marked)

K1–K11, K13–K15, K17, K19, K20 unchanged (file 8). **K12** restated: no macOS runner base rate exists (researcher F12 not found); the project's own spreads govern: macOS min 1.50 / worst 2.59 s within one run; Windows cube worst **1.2–2.4 %** run to run (48.6 / 2 003.5 and 24.6 / 1 999.1 ms, file 1 header), flutter 9.3 % (49.1 / 525.2 ms). **K18** restated: the unit-decay synthesis is 3 138 of 3 287 ms (95.5 %) at 96 kHz; the full non-diffuse build is **≈ 2.5× from 48 to 96 kHz (file 7 §1: 1 321 → 3 287 ms, measured; super-linear)**; "flat in room size for T60_max ≥ 8 s" follows from `tailLengthS` = min(12 s, 1.5·T60) (from the code, Seat 2 L34). **K16** unchanged (hosts: absent; OS thresholds bound severity). New: **K21** | Seat 5's R-e cell | not on file (`17-seat5-D-H3.md` absent) | read from R-c's words (rfc), both branches shown. No load-bearing item is uninformed; K12, K16 are recorded as absent and the decision rests on neither.

### Tension map, D-H1 (now / later; each cell the seat's own words; `(rfc)` = read from conditions, the option appeared in the round)

**W.** **W-x′ (composed, P05H-10)** = Seat 5's W-x (file 5-seat5 §2 L27: W_max 3.05 M pinned; gate on all three OSes as a strict check with a plan-text defect register, growth bound median-of-10 ≤ 1.10 × recorded median, unexpected pass reported, per-OS min/median/worst and the 14× figure printed) + Seat 5's 29.1 s enforcement rule (its W-b condition, L87) + Seat 2's remedy ladder by name (L46) + Seat 6's three W-e conditions (L34) + Seat 8's bounce-record condition (L24). Every ingredient is a seat's own condition; no cell is raised by composition.

| seat | W-a | W-b | W-c | W-e | **W-x′** |
|---|---|---|---|---|---|
| 1 | 2 / 1 "my standing J1 cell … W-a brings (C) soonest" (L24) | 2 / 2 "a cut that buys nothing I measure" (L26) | 1 / 1 "the switch waits a phase" (L25) | 2 / 1 "= W-a on my measures" (L27) | **2 / 1 (rfc)** L27: "only at 3.05 M, or with '(C) next phase' written in regardless"; both hold |
| 2 | 0 / 1 "No SE cost … the plan's remedy ladder ends in a red gate unless the finding gets a remedy" (L27) | 2 / 2 "a cut 'to pass the gate' … no W_max ≥ 0 protects anything" (L28) | 1 / 1 "moves the red gate to 07c rather than curing it" (L29) | 1 / 1 "Changes which OS is enforced, nothing in my measures" (L30) | **0 / 1 (rfc)** W-a's cell with the §6 L46 condition met by name (see answer 2) |
| 3 | 1 / 1 "the solve adds 58–162 ms … commits phase-07c next" (L27) | 2 / 1 "SE ×1.21 … while macOS still fails" (L28) | 1 / 1 "stays unshipped one phase longer" (L29) | 1 / 1 "Same level cost as W-a … with (C) still brought forward" (L30) | **1 / 1 (rfc)** L30's condition holds |
| 4 | 1 / 1 "parity holds … (C) lands before Phase 08's goldens" | 2 / 1 "p95 … crossing the 1 dB jnd of G" | 1 (2 if the switch waits) / 0 | 1 / 1 "provided the Phase 08 heaviest-mode restore is still recorded on all three OSes" | **1 / 1 (rfc)** records all three OSes every run |
| 5 | 2 / 2 "A required check red by design … kills the signal" (L41, L60) | 2 / 2 "A block that flakes … turns timing noise into 'defects'" (L42) | 1 / 2 "the (C) W_max pinned before the … bounce record exists" (L43, L62) | 2 / 2 "Right pattern … wrong placement" (L44) | **1 / 1** (own, L45, L64) "the macOS result is a defect on the register, not a red; `ci ok` stays meaningful" |
| 6 | 1 / 1 "the red gate is internal and says the true thing" (L22) | 1 / 1 "What it buys the user: nothing" (L23) | 1 / 1 if split; 1 / 2 if blocked whole (L24) | 1 / 2 "enforced on the one OS no customer runs" (L25) | **1 / 1 (rfc)** its three conditions L34 written into (v) |
| 7 | 2 / 2 "a red blocking check … masks every other macOS assertion" (L24–25) | 2 / 2 "some flake rate … each flake is 'a defect'" (L26) | 2 / 2 "buys nothing on macOS" (L27) | 1 / 1 W-e′ "enforced where it passes … macOS recorded" (L17, L28) | **1 / 1 (rfc)** W-e′ at 3.05 M; W-a conditions L41 (a red masks nothing; the knot written; the macOS entry has an owner phase or end date) hold under the register |
| 8 | 1 / 1 "names that build as the finding, which is the wait she actually feels" (L15) | 1 / 1 "A precision price for nothing she can hear" (L16) | 2 / 1 "What W-c delays is the switch" (L17) | 1 / 2 "approved in one room, heard in another" (L18) | **1 / 1 (rfc)** L24: "a recorded macOS failure carries the same remedy … Phase 13 enforces it on macOS before beta"; bounce-record condition carried into (v) |
| 9 | 0 / 1 "For validation nothing changes" (L19) | 1 / 2 "Buys nothing on macOS" (L22) | 1 / 1 "the switch … waits one phase" (L21) | 0 / 1 "Same as W-a for my seat" (L20) | **0 / 1 (rfc)** as W-e at 3.05 M |
| max / sum | 2 / 21 | 2 / 29 | 2 / 21 (split; 24 whole) | 2 / 22 | **2 / 17** (18 if Seat 2 is read 1 / 1) |

**P.** P-a′ (composed, sub-choice P) = P-a + Seat 1's P-a condition (L41) + Seat 9's P-b condition (L34, carried over).

| seat | P-a | P-b | **P-a′** |
|---|---|---|---|
| 1 | 1 / 2 "my watchdog on W_max is inert while the s = 1 cube's p95 crosses 1 jnd in the reported set with no escalation path" (L18) | 1 / 1 "the escalation's attention cost, not audibility" (L17) | **1 / 1 (rfc)** L41: "P-a later 2 → 1: the s = 1 cube's SE and p95 are reported … and a p95 > 1 dB there is escalated like a gated scene" |
| 2 | 0 / 1 "validates the cost-worst realistic box … the s = 1 cube stays reported, so nothing is hidden" (L21) | 1 / 1 "a known floor failure … where any rise threshold is noisiest" | 0 / 1 |
| 3 | 0 / 1 "rests on O18's 30 replicates passing" (L32) | 1 / 1 "the floor is pre-failed" | 0 / 1 |
| 4 | 0 / 0 NMM | 0 / 0 | 0 / 0 |
| 5 | 1 / 1 "s does not enter it … the register entries name the scene" (L33, L53) | 1 / 1 "every later rise is an escalation" | 1 / 1 |
| 6 | 0 / 1 "a test box, never a preset … the Phase 12 (ii) check … decides whether a preset default ever shows U" (L15) | 1 / 1 | 0 / 1 |
| 7 | 0 / 1 "the floor rests on O18's 30 replicates" (L30) | 1 / 1 "it also picks the slower restore" | 0 / 1 |
| 8 | 0 / 1 "if a Phase 12 hall default is s = 1, Trigger 2 catches it" (L19) | 1 / 1 "an escalation about a non-room" | 0 / 1 |
| 9 | 0 / 0 "The realistic cost-worst closed room" (L13) | 1 / 1 "A bound, not a room" (L14) | 0 / 0 |
| max / sum | 2 / 10 | 1 / 16 | **1 / 9** |

**R.** R-e (Seat 1's, L20; restated as to the starting state, answer 1): R-d's lines escalate; any rise of the achieved SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB above the **recorded** starting state is printed in the margin report, not escalated; no golden.

| seat | R-a | R-b | R-c | R-d | **R-e** |
|---|---|---|---|---|---|
| 1 | 1 / 1 "A noise test" (L22) | 1 / 1 "lets the p95 cross 1 dB without firing" | 1 / 1 "escalations nobody can hear" (L21) | 0 / 1 "at P-b the SE line is already crossed" (L19) | **0 / 0** (own, L20) |
| 2 | 1 / 1 (L23) | 0 / 0 (prefer) | 1 / 1 "insensitive to a real variance regression" | 1 / 1 "collapses the clause into the floor itself" | **1 / 1 (rfc)** R-d's cell; the record adds nothing Seat 2 rated |
| 3 | 2 / 2 "a rise of a full jnd is not a rise" (L34) | 2 / 2 (L35) | 1 / 1 "escalates … on rises of 1/20 jnd" (L36) | 0 / 0 "the only ones with a perceptual meaning" (L37) | **0 / 0 (rfc)** R-d's lines, no 1/20-jnd escalation |
| 4 | 0 / 0 NMM | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 |
| 5 | 1 / 1 "a golden with a never-regenerate rule" (L35, L56) | 1 / 1 | 0 / 1 "One constant; no derived golden" / "one constant in plan text" (L34, L55) | 0 / 1 "Cheapest" / "nothing on my side" (L36, L57) | **0 / 1 (rfc, from R-c's words; K21)**; branch (B) 1 / 1 if Seat 5 so answers |
| 6 | 1 / 1 (L17) | 1 / 1 | 1 / 1 "escalates to Maisara on rises nobody can hear" | 0 / 1 "a crossing changes what the producer sees" | **0 / 1 (rfc)** L17: "every rise should be recorded; only the crossing escalates" is R-e |
| 7 | 1 / 2 "fire about one time in six" (L32) | 1 / 1 | 0 / 0 | 0 / 1 "the trigger is dead by construction" under P-b | **0 / 1 (rfc)** R-d's cost; the record is a print |
| 8 | NMM 0 / 0 (L9) | — | — | — | 0 / 0 |
| 9 | 1 / 1 (L18) | 0 / 1 (L17) | 0 / 0 (L15) | 0 / 1 "degenerates under P-b" (L16) | **0 / 1 (rfc)** |
| max / sum | 2 / **17** (8 + 9) | 2 / **13** (6 + 7) | 1 / 9 | 1 / 7 | **1 / 6** (branch (B): 1 / 7) |

**Q** and **N**: unchanged from file 8 (Q-d max 1, sum 1; N-a max 1, sum 3; N-b 2 816 carries Seat 1's 3 / 1, L29).

### Minimum-tension working (redone where it changed)

1. **Bounds.** As file 8 (X1–X3 dropped; the growth bound on the median is not X1; no option breaks NFR-8 / FR-SIM-6; the gated cube is a test scene).
2. **Veto-grade.** N-b at 2 816 dropped (Seat 1 3 / 1). No other 3.
3. **Worst-off.** W: every option max 2 (Seat 1's 2 now holds on every (A) option, L38: "only (C) landing"; W-c is 2 / 2 for Seat 7, 2 now for Seat 8). P: P-a′ max 1. R: R-c, R-d, R-e max 1 under both branches. Q-d, N-a max 1.
4. **Compose.** Sub-choice W: **W-x′** (named; answer 2). Sub-choice P: **P-a′**. One composed variant per sub-choice this round; the interrogator checks each reading. R: no seat rated R-d or R-e at 2, so no condition exists to compose from; branch (B) cannot be lowered by composition.
5. **Sum.** W-x′ 17 (18) < W-a 21 = W-c 21 < W-e 22 < W-b 29. P-a′ 9 < P-a 10 < P-b 16. R, branch (A): R-e 6 < R-d 7 < R-c 9 < R-b 13 < R-a 17. R, branch (B): R-e 7 = R-d 7 < R-c 9. Q-d 1. N-a 3.
6. **Reversibility.** W-x′: a plan edit per register entry; the pin is undone at (C)'s golden round, which every option owes. P-a′: a pin edit. R, branch (B) only: Seat 5's undo column, R-d "—" (L57) against R-c's "parameter" (L55), which the restated R-e shares (two constants and a record line to remove): **R-d**. Q-d, N-a: one constant each.
7. **Decide:** W-x′, P-a′, **R-e on branch (A)**, Q-d, N-a. If Seat 5's answer in file 17 rates R-e ≥ 1 now, (ii) changes to R-d by step 6: the escalation sentences stay, the "Recorded" sentence is struck; nothing else in D-H1 moves.

### DECISION D-H1 (plan text for the plan-editor; applied with H1-F1–H1-F3 once they survive)

**(i) AX38 4c pin of the gated closed low-α cube (P-a′).** "The gated closed low-α cube is `cube100_lowalpha0.05_s0.3` (`tools/validation/phase05b2_dt1.py` `_joint_cases()`): 100 × 100 × 100 m, α 0.05 and s 0.3 on every face, listener (50, 30, 1.7) m, emitters (45, 70, 2) and (55, 70, 2) m, 96 kHz; `ismFallback` false on both emitters, asserted. The α 0.05 / s 1 cube (`cube100_lowalpha0.05_s1`) stays in the reported set: its achieved SE, VOV and 30-replicate p95 are printed in the margin report beside the gated cube's; a replicate p95 > 1 dB there is escalated exactly as at a gated scene; any finding about it states that it is a synthetic bound that no fixture or preset approaches (no fixture has s > 0.7, from the code; Kuttruff: full Lambert reflection is 'hardly ever real', L2504) and that a user may build it (FR-3D-4, AQ3, AX6), in which case AX44's note U is raised there (cap hit AND achieved SE > 0.33 dB). Starting state (file 10, C++ shipping rule, 30 disjoint pre-registered streams, 1 kHz, local Release): gated cube p95 0.250 / 0.178 dB, achieved SE 0.117 / 0.115 dB (replicate SD 0.036 / 0.038 dB), floor **met via clause (d)**; s = 1 cube p95 0.701 / 0.810 dB, achieved SE 0.381 / 0.384 dB > 0.33 dB, floor **not met**, recorded as a starting-state finding of the reported set (H1-F3); flutter cube met via (a)."

**(ii) "Any further rise" (Trigger 1, starting-state clause; R-e restated).** "The starting state per gated scene and emitter is the **record** in `docs/review/phase-05h/10-orchestrator-clause-d-replicates.md` (cited in the 05h PR and the ledger): the fixed-key achieved SE (deterministic, AX40 / D7; the cross-OS E_target comparison of scope 9 shows whether it differs by OS) and the replicate p95 (30 disjoint pre-registered streams). It is a record, not a golden: no test asserts on it, no file is regenerated, and the margin report reproduces it as its baseline column. **Recorded** (a flagged line in the margin report of every later run that re-derives W_max or re-baselines the non-diffuse build, beside the baseline column): any rise of the achieved SE ≥ 0.05 dB or of the replicate p95 ≥ 0.10 dB above the starting state (two constants in plan text). **Escalated** (phase-05h §2 item 1, to Maisara with the SE, the VOV and the p95): the achieved SE crossing 0.33 dB, or the replicate p95 crossing 1 dB (1 jnd of G, Vorländer Table 6.1), at a gated scene, or the p95 crossing 1 dB at the reported s = 1 cube ((i) above). Nothing else escalates." (If Seat 5's R-e cell comes back ≥ 1 now, the "Recorded" sentence is struck and the rest stands: R-d.)

**(iii) Realised-work ratio (AX41, pre-registered; Q-d).** Unchanged from file 8: "realised work / W_scene ≤ **1.02** at each gated scene, pre-registered from the C++ measurements at the pinned W_max 3.05 M (measured 0.935 / 0.991 / 0.986 at flutter / s 0.3 / s 1; prototype ≤ 1.009; the count is deterministic, D7) and not changed afterwards. Beside it, W_pilot and W_final per gated scene are asserted **exactly** in the D5 golden (already recorded there); the ratio is the scene-generic guard."

**(iv) W_max and n\*_max, pinned cross-platform constants.** Unchanged from file 8 (W_max = 3.05 M per emitter, W_scene 6.10 M; formula (A) working Linux ≈ 2.4 M, Windows ≈ 5.8 M, macOS 2.1429 − 2.3277 = −0.185 s, no W_max ≥ 0; the provisional value pinned as the (A) value, not a formula result; Seat 6's 3 s met at 0.136 s per emitter; re-derived once under (C), phase-07c condition 3, with Seat 6's per-scene reading; **n\*_max = 1 024** stands, W1 diffuse share 7.65 / 9.03 (max 13.98) / 6.35 ms ≤ 25 ms; not re-derived at (C) unless the W1 measurement per output mode moves it, phase-07c §9). One addition (Seat 8 L24, Seat 5 L89): "**phase-07c pins its (C) W_max only after the AX38 4c record 'offline-bounce time of a 3-minute room-size automation at 100 m, with its ratio to real time' is in 07c's packet.**"

**(v) The blocking gate and phase-07c's ordering (W-x′; the mechanism is her recorded decision read in H1-F2).** "The AX38 4c restore gate runs on every Release run on Linux, macOS and Windows at both gated builds and, per OS and scene, prints min / median / worst of 10 restores, the worst-of-10 solve and 14 × (worst restore + worst solve). **(a) Assertion rule, no OS/scene unasserted:** where the recorded value at the pinned W_max is ≤ 29.1 s (a 3 % margin, about one observed run-to-run spread), 14 × (worst-of-10 restore + worst-of-10 solve) ≤ 30 s is asserted **strictly**; every OS/scene whose recorded value is > 29.1 s, whether or not it exceeds 30 s, is **listed in the defect register** (plan text: recorded value, median, remedy, closing phase) and asserted through (b) instead. **(b) Growth bound** on every listed entry: median-of-10 restore ≤ 1.10 × the recorded median (the median, not the worst, so the shared macOS runner's spread does not flake it; not X1). **(c)** A listed entry that passes 30 s is reported in the job summary (warning) and removed from the register through `/fix-plan` before the next phase is set `done`. **(d)** A new failure at an unlisted OS/scene, or a listed entry breaking its growth bound, is a defect: never a re-run, never a W_max cut, never a range change or a seam; it is added to the register with its remedy ((C) forward, then condition 9) through `/fix-plan`. **Register at the pinned W_max** (file 1 §4; medians re-baselined from O18's three-OS run): `cube100_lowalpha0.05_s0.3` on **Linux** (30.27 s; median 2 032.5 ms; remedy: phase-07c moves the diffuse solve, after which the non-diffuse restore gives 28.9 s; closes at 07c) and on **macOS** (33.40 s; median 1 882.0 ms, min 1.50 / worst 2.33 s on a 3-vCPU M1 VM; remedy: the finding below; closes when the unit-decay synthesis leaves the synchronous restore (07c condition 9, or 07d) or, if the runner is shown to be the cause, at Phase 13's release-machine re-check, as §0 row 06 already does for the macOS callback p99.9). Windows (29.04 s) and the flutter cube on every OS (7.6–10.6 s) are strict. **Finding (separate, named):** the non-diffuse 100 m / 96 kHz restore is the unit-decay synthesis in `tail::BandNoiseGenerator` at the 12 s tail cap (constructor spectra 0.96 s + `make` × 2 emitters 2.18 s = 3.14 of 3.29 s, 95.5 %, split timer file 7; ISM + matching + mix ≈ 0.15 s); it is flat in room size for every room with T60_max ≥ 8 s (`tailLengthS` = min(12 s, 1.5·T60), from the code) and **≈ 2.5× from 48 to 96 kHz (file 7: 1 321 → 3 287 ms, measured)**; (C) as written (phase-07c moves only the diffuse solve) does **not** cure macOS (14 × 2.33–2.59 s = 32.6–36.3 s). **Remedy, routed by name, and the plan edits it needs:** this decision adds, through `/fix-plan`, **phase-07c §5 condition 9** (07c has conditions 1–8 today; no `phase-07d.md` exists): 'the unit-decay synthesis moves off the synchronous restore, prepare and `reset()` with the same interim / settling rules as the diffuse solve (the interim tail while the synthesis is pending is decided in 07c's loop beside D-C2; never silence where a tail existed in the saved state); after both moves the restore gate measures ISM + matching + mix (≈ 0.15 s at 96 kHz) and passes a worst-of-10 rule with 10–20× headroom'; **condition 7** reads 'measures restore without the solve and the synthesis'; **§9** states that moving the synthesis is in scope and that caching its constructor spectra per (fs, length) is not the AX38 (ii) kernel cache but is an alternative recorded, not chosen; **a `phase-07d.md` of size S–M is created only if 07c's loop finds condition 9 does not fit 07c** (CLAUDE.md split rule), and the register's macOS 'closes at' then names 07d. Alternatives recorded, not chosen: a cheaper generator (output-changing; a golden round; AQ10's 'not optimised before Phase 13' to be read by the board); the constructor-spectra cache (bit-identical, ≈ 4 of 14 FFTs, [Hyp] 20–25 %, not enough alone). **Bounce record before (C)'s W_max** (Seat 8 L24, Seat 5 L89): the AX38 4c 3-minute 100 m bounce record is in 07c's packet before W_max is re-derived under (C). **Ordering:** phase-05h may be set `done` under CLAUDE.md step 6 with the register entries recorded in §0 row 05h (the automated check passes with them listed), which requires **phase-05h §5's 'Blocking' row to be rewritten in this register form** (strict ≤ 29.1 s; listed with the growth bound otherwise; a failure a defect; remedy (C) forward then condition 9); phase-07c is the **next phase after 05h**, before Phase 08's goldens (AX38 4c 'brought forward on any restore-gate failure'; phase-07c §3), its 'Depends on: 05h done' unchanged; if O18 does not fit this session, the gate and records go to phase-05i and 07c follows 05i. Phase 08's heaviest-mode gate (phase-08 scope 10) runs under the same register rule. The macOS and Windows restore records go to Maisara in the 05h PR against the 1 / 3 / 10 s anchors with the spread stated (Raise item 2), and the register is re-enforced strictly on all three OSes at Phase 13's release-machine re-check (AX41)." **Texts amended by (v):** AX38 4c (Challenge 1 paragraph), AQ10 amended (1), phase-05h §5 "Blocking" row, phase-05h §0 row notes, phase-07c §5 (conditions 7, 9) and §9, phase-08 scope 10.

**Confidence:** medium (every acoustic number corpus- or measurement-backed, every product claim with an id; seven W-x′ cells, one P-a′ cell and six R-e cells read from conditions, one of them (Seat 5 × R-e) pending the seat's answer). **Reversal conditions:** (1) Seat 5's R-e cell in file 17 is ≥ 1 now: (ii) becomes R-d (step 6); (2) O18's three-OS run shows an unlisted OS/scene over 29.1 s or a listed one under 30 s (the register changes by (c)/(d); the decision stands); (3) phase-07c's loop finds the synthesis cannot be moved without an output change (remedy becomes the cheaper generator through a golden round; W_max unaffected); (4) a seat re-rates W-x′ above its read cell (step 3 redone); (5) Phase 13's release machines show the macOS restore ≤ 2.14 s (the macOS entry closes as a runner artefact).

### Load-bearing claims, D-H1 (changes only; the rest as file 8)

- **D-H1-L4** restated (P05H-13): the unit-decay synthesis is 3 138 of 3 287 ms (95.5 %) of the non-diffuse 100 m / 96 kHz build; ISM + matching + mix 147 ms; the build is ≈ 2.5× from 48 to 96 kHz (1 321 → 3 287 ms, file 7 §1, measured). "Flat in room size for T60_max ≥ 8 s" from the code (min(12 s, 1.5·T60)).
- **D-H1-L11** restated: Seat 2's W-x′ cell is its W-a cell 0 / 1 (L16, L27, L46); Seat 5's R-e cell is read from R-c (L34, L55), pending its answer.
- **D-H1-L16** (new, product): FR-3D-4 with AQ3 and AX6 lets a user build the α 0.05 / s = 1 cube; the protection there is AX44's U (cap hit AND SE > 0.33 dB) and (i)'s p95 line, not a preset fact. "No fixture has s > 0.7" is from the code (Seat 9 L14).
- **D-H1-L17** (new, plan text): AX38 4c defines Seat 1's floor "at a gated scene … at each gated 100 m build" and the starting state "at the gated scenes (phase-05h reported set)"; phase-05h §2 item 1 says "in the starting state (the joint-rule replicates of the reported set)". Bears on H1-F3.

### Future-debt register, D-H1 (one row per later ≥ 1 on a chosen option)

| seat (option) | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (W-x′ later 1) | the (A) level debt: s = 1 cube SE 0.38 dB, layouts 4/5 0.13–1.33 dB, until (C) | nothing extra: (C)'s golden round | O18 margin report; 07c's W_max | phase-07c lands with W_max from the background budget |
| 1 (P-a′ later 1) | the s = 1 cube watched in the reported set with the p95 escalation line | a pin edit | every margin report | standing rule; closes at (C) |
| 2 (W-x′ later 1) | "the plan's remedy ladder ends in a red gate unless the finding gets a remedy" (L27): the remedy is **phase-07c §5 condition 9, created by this decision's `/fix-plan` edit** (07d only if 07c cannot carry it) | a 07c scope edit; a golden round if the cheaper generator is chosen instead | 07c's loop and its restore record | 07c `done` with condition 9 (or 07d `done`) |
| 2 (P-a′ later 1) | "the s = 1 cube stays reported, so nothing is hidden" (L21): the reported set keeps the cube | a pin edit | every margin report | standing |
| 2 (R-e later 1) | shipped precision at the gated scene guarded only by the 0.33 dB / 1 dB lines and the record (L23: "collapses the clause into the floor itself") | two constants and a record line | the first re-derivation (07c) | if a recorded rise recurs without a crossing, the board re-reads R |
| 3 (W-x′ later 1) | 07c next, before Phase 08's goldens (L27) | (C)'s golden round | O18, 07c | 07c |
| 3 (P-a′ later 1) | "rests on O18's 30 replicates passing" (L32) | — | file 10 | **discharged by file 10** (p95 0.250 / 0.178 dB, SE 0.117 / 0.115 dB: met via (d)) |
| 3 (N-a later 1) | one-end placements at up to 0.124 dB (L39) | one constant | phase-08 per-mode W1 | 07c / Phase 08 |
| 4 (W-x′ later 1) | the Phase 08 heaviest-mode gate runs under the register, after (C) | a register entry | phase-08 scope 10 | 07c (condition 9) or Phase 13 |
| 5 (W-x′ later 1) | "a register that must shrink … the growth bound re-baselined only through plan text" (L64) | a plan edit per entry | O18 per OS; RQ-H1-2 absent; Phase 13 | Linux entry at 07c; macOS entry at 07c condition 9 / 07d or Phase 13 |
| 5 (P-a′ later 1) | "nothing on my side; the register entries name the scene" (L53); evidence "O18 clause (d) replicates" | plan edit | file 10 | evidence **discharged by file 10**; the register names the scene by (v) |
| 5 (R-e later 1) | "one constant in plan text" (L55; here two) | parameter | Seat 1's replicate data | standing |
| 5 (Q-d later 1) | one pre-registered ratio, "not changed afterwards" (L58) | parameter | the D5 golden (m-3) | standing |
| 5 (N-a later 1) | "nothing new" (L66) | — | O18 W1/W2 per OS | O18 |
| 5 (all W later 1) | the multiplier 14 is the automatable-parameter count; a new id re-derives 30/N (L65) — **superseded by H1-F1**: 14 is a kept constant | — | — | closed by H1-F1 |
| 6 (W-x′ later 1) | "settling", the one-step update and the Phase 12 (ii) re-check at the final W_max come at 07c; records to Maisara in the PR (L22, L34) | a plan edit | O18 records (Raise items 2, 3) | 07c; Phase 13 re-enforcement |
| 6 (P-a′ later 1) | "the Phase 12 (ii) check, not the gated cube, is what decides whether a preset default ever shows U" (L15) | — | phase-12 preset check | Phase 12 |
| 6 (R-e later 1) | "under P-b the SE starts above 0.33 dB, so only the p95 line can fire" (L17): moot under P-a′ (SE 0.117 dB) | — | file 10 | **discharged by P-a′ + file 10** |
| 7 (W-x′ later 1) | the macOS entry listed with an end date (07c condition 9 / 07d or Phase 13); one golden round at (C) (L28, L41) | a plan edit | O18; 07c | 07c / 07d |
| 7 (P-a′ later 1) | "the floor rests on O18's 30 replicates; if they fail, Raise item 1 fires later" (L30) | — | file 10 | **discharged by file 10** |
| 7 (R-e later 1) | R-d's "under P-b the SE is already past 0.33 dB, so the trigger is dead by construction" (L32): moot under P-a′ | — | file 10 | **discharged by P-a′ + file 10** |
| 8 (W-x′ later 1) | the 2.0–2.6 s load wait outlives (C) as written until the synthesis moves (L15); **condition L24: the 3-minute bounce record is in 07c's packet before (C)'s W_max is pinned** (now in (iv)/(v)) | none; the record carries it | O18's (iv) records; RQ-H1-3 absent | 07c condition 9 / 07d; the bounce record at 07c's packet |
| 8 (P-a′ later 1) | "if a Phase 12 hall default is s = 1, Trigger 2 catches it" (L19) | — | phase-12 "Hall presets and J1" | Phase 12 |
| 9 (W-x′ later 1) | one golden round at (C); Phase 12's preset check at the final W_max with an elongated stone cathedral case (L19, L36) | — | phase-12 | 07c, Phase 12 |
| 9 (R-e later 1) | R-d "degenerates under P-b" (L16): moot under P-a′ | — | file 10 | **discharged by P-a′ + file 10** |

**Strongest objection.** As file 8 on W (Seat 1's 2 now on every (A) option; holds because W-c is 2 / 2 for Seat 7, 2 now for Seat 8, and still fails on macOS, K15). On R: the interrogator's P05H-04 remains the sharpest point: Seat 5's R-e cell is read, not given; if Seat 5 prices the record at 1 now, R-e ties R-d at 7 and R-d wins on Seat 5's own undo column. The decision stands on the restatement (no golden, no SD, no assertion: R-c's mechanism, which Seat 5 priced at 0) and names Seat 5's answer as its first reversal condition.

### FOR MAISARA H1-F1 — does the "14 × t_restore ≤ 30 s" convention stand now that it is not pluginval's requirement?

**Question.** AQ10 amended (1) and AX38 4c (her acceptance of 2026-11-10) say the restore block is "14 × t_restore ≤ 30 s under pluginval's default watchdog, about 2.14 s per restore". pluginval v1.0.4's watchdog resets after every restore (researcher F2–F4); the tool's own bound is one restore per 30 s. Does the 2.143 s per-restore bound stand, or is the gate re-based?

**Answer (exact wording).** "The block is **14 × t_restore ≤ 30 s, i.e. t_restore ≤ 2.143 s per synchronous restore at the gated builds, a project convention** on the synchronous restore (not pluginval's requirement: pluginval v1.0.4's watchdog is an inactivity timeout reset after each restore, so the tool itself tolerates one restore per 30 s; `5-researcher-RQ-H1-H2.md` F1–F6). The constant 14 is kept as written and is no longer re-derived from the automatable-parameter count. CI's pluginval run (`--timeout-ms 120000`) is not evidence for this block; the Catch2 restore test is."

**PRD ids and decisions.** PRD L101 (NFR preamble): "CPU load and latency may be high, but the plugin must stay usable in a DAW session"; NFR-2 (L106); NFR-6 (L110); NFR-1 (L105); her acceptance of 2026-11-10 ("I accept the board's answer by definition").

**Reasoning (5 lines).** The PRD names no restore bound; the convention is the one number in the plan that bounds the synchronous restore the host's UI thread blocks on (F13), and 2.14 s sits under the one OS threshold on record (Windows 5 s, F14). L101's "but" ranks usability as the bound on NFR-2's heaviness, so a 30 s synchronous restore is not licensed by NFR-2. Dropping to pluginval's real bound would let W_max under (A) grow ≈ 14× and the restore run for many seconds on the UI thread, which no seat rated. Choosing a different user-facing number (1 s, 3 s) would invent a product goal (the 1 / 3 / 10 s marks are escalation anchors, AX38 (iv), not limits). Keeping the accepted number keeps every seat's rating valid; (C) makes the (A) value transient anyway.
- *Keep the convention (chosen):* serves L101 / NFR-2 (a bounded UI-thread block), NFR-1 (W_max uncut), NFR-6; strains nothing.
- *Re-base to one restore per 30 s:* serves nothing the PRD names; strains L101 ("usable in a DAW session").
- *Re-base to a user-facing anchor (e.g. 3 s):* no PRD number; case (a) if attempted; not chosen.

**What would make her veto it.** A reading that NFR-2's "heavy CPU and latency are acceptable" outranks L101's "but … usable", licensing a longer synchronous restore so that W_max rises under (A).

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AQ10 amended (1) and AX38 4c Challenge 1: "under pluginval's default watchdog" → "a project convention; pluginval's watchdog resets per restore".)

### FOR MAISARA H1-F2 — the restore block as a strict check with a defect register, its OS scope, and the remedy beyond (C)

**Question.** AX38 4c (her acceptance) says the restore block is "a block … a gate failure is a defect … remedied by bringing (C) forward" and names no OS for it, while the memory block in the same row is "gated on Linux, recorded on macOS and Windows until Phase 13". The data say the block fails on macOS at every W_max ≥ 0 and (C) as written does not cure it. May the block run as a strict check with a plan-text defect register (W-x′), and may the remedy ladder be extended to the unit-decay synthesis?

**Answer (exact wording).** "The restore block runs on all three OSes: asserted strictly at every OS/scene whose recorded value at the pinned W_max is ≤ 29.1 s, and as a **registered defect** at every other OS/scene (each entry in plan text with its recorded value, remedy and closing phase; a growth bound, median-of-10 restore ≤ 1.10 × the recorded median; a warning on an unexpected pass; removal before the next phase is `done`); no OS/scene is unasserted. A gate failure stays a defect: never a re-run, a W_max cut after pinning, a range narrowing or a seam; its remedy is (C) forward, and where (C) as written does not cure it (the non-diffuse build alone exceeds the budget on macOS), the remedy ladder continues by name: phase-07c §5 condition 9 (or phase-07d if 07c cannot carry it) moves the unit-decay synthesis off the synchronous restore with the diffuse solve's interim rules. The register is enforced strictly on all three OSes at Phase 13's release-machine re-check. Amended texts: AX38 4c, AQ10 amended (1), phase-05h §5 'Blocking' row, phase-07c §5 (conditions 7, 9) and §9, phase-08 scope 10."

**PRD ids and decisions.** PRD L101 (NFR preamble, "usable in a DAW session"); NFR-2; NFR-1; NFR-6; NFR-8 ("no environment-specific code paths": the remedy is generic); FR-SIM-6 (no level jump at a size threshold: no range narrowing); L20 ("Primary users … on macOS and Windows"); L55 ("no fixed deadline"); her acceptance of 2026-11-10; "build the switch (option (b))", 2026-11-09 (phase-05h §1 L42).

**Reasoning (5 lines).** A block the data say is red at commit time on one OS, with no remedy in any settled text once (C) lands, protects nothing: it hides every other macOS assertion in the same job (Seat 7) and disables the fingerprint skip (D-H1-L12). The register keeps the block's content (the number, the no-re-run rule, (C) forward) and adds what the row lacks: a remedy that reaches the cause (D-H1-L4) and an end date. The plan already records-rather-than-enforces on macOS in the same row and in §0 row 06 (D-H1-L14), so this is the row's own pattern. NFR-1 is served by keeping W_max uncut; L101 / NFR-2 by the growth bound (the restore cannot grow unnoticed). Letting 05h close protects the switch's delivery, which her 2026-11-09 decision asks for.
- *W-x′ (chosen):* serves NFR-1 (no cut), L101 / NFR-2 (growth bound, remedy at the cause), NFR-8 (generic remedy).
- *W-a as written (red by design):* serves the letter of "block"; strains L101 / NFR-2 (no remedy for macOS after (C)) and CLAUDE.md's verification culture (a red everyone ignores).
- *W-b (cut W_max):* strains NFR-1 (SE ×1.21, p95 past 1 jnd at the s = 1 cube) for a pass on two OSes and none where it is worst.
- *W-c ((C) first):* **PRD L55 ("no fixed deadline") means the delay itself breaks nothing, and her 2026-11-09 words say build the switch, not when.** What W-c strains is NFR-1's own ordering: NFR-1 has two errors in play, the **systematic** AX16 error (+3.87 / −1.17 dB in layouts 4/5, +2.38 dB in the absorbing-floor cube, ≈ 4 jnd of G, removed by the switch) and the **random** (A) error (SE 0.38 dB at the s = 1 cube, 0.13–1.33 dB in layouts 4/5, removed by (C)). "Accuracy first" (L49, L101) is served by removing the larger error first; W-c ships the (C) value first and holds the ≈ 4 jnd systematic error in every golden and the listening pack for a phase (Seats 3, 9: "a 0.4 dB random error in a synthetic cube is worth less … than a 3.9 dB systematic one"), and still ends red on macOS (K15).
- *W-e (Linux-enforced):* enforces on the OS no customer runs (L20); strains L101's user.

**What would make her veto it.** The reading that "a block" means a required red on every OS until it passes, with no register, so that the pressure to shorten the 100 m build is never relieved.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX38 4c Challenge 1 and AQ10 amended (1): the register mechanism and the 29.1 s OS rule; the remedy ladder's extension to the unit-decay synthesis via phase-07c §5 condition 9 / phase-07d; phase-07c §0's scope, itself a board answer she accepted, extended by condition 9; phase-05h §5's "Blocking" row rewritten in the register form.)

### FOR MAISARA H1-F3 — phase-05h §2 "Raise with Maisara" item 1 (re-answered, P05H-24)

**Question.** Does Raise item 1 fire at the pinned W_max, given file 10: the gated s = 0.3 cube meets the floor via clause (d) (p95 0.250 / 0.178 dB ≤ 1 dB, SE 0.117 / 0.115 dB ≤ 0.33 dB), the reported s = 1 cube does not (SE 0.381 / 0.384 dB), and W_max was not cut (the negative macOS formula value resolved to (C) forward)?

**The two readings of "escalated once".** (R1) Phase-05h §2 item 1 L86–87: "A floor failure already present in the starting state (the joint-rule replicates of the reported set) is recorded as a finding and escalated once" — read with the parenthesis as the scope, any floor failure in the reported set's replicates, the s = 1 cube included, is item 1 fired once, now. (R2) AX38 4c and phase-05h §3 L140–141 define the floor "at a gated scene … at each gated 100 m build" and the starting state as "the joint-rule replicates at the gated scenes (phase-05h reported set)": the floor exists only at gated scenes; the s = 1 cube is not gated under P-a′, so its failure is a finding of the reported set, not an item-1 escalation.

**Answer (exact wording).** "Item 1 does not fire at the pinned W_max: the gated cube meets the floor via clause (d) and W_max was not cut. The s = 1 cube's starting-state floor failure (SE 0.381 / 0.384 dB, VOV 0.178 / 0.183, p95 0.701 / 0.810 dB) is **recorded once in the 05h PR, in the Raise-with-Maisara section beside item 1**, labelled 'starting-state finding of the reported set at a scene that is not gated; a synthetic bound no fixture or preset approaches; buildable by a user (FR-3D-4, AQ3, AX6), where AX44's note U is raised'; it is never a reason for a range change or a W_max cut (AX38 4c). Item 1 fires later only on (ii)'s lines: the SE crossing 0.33 dB or the p95 crossing 1 dB at the gated cube, or the p95 crossing 1 dB at the reported s = 1 cube."

**PRD ids and decisions.** NFR-1 (L105: accuracy first; "Pass thresholds come from the Expert"); L49 ("Accuracy first"); FR-3D-4 with AQ3 and AX6 (the cube is buildable; cited for what they say, not for "never approaches"); AX38 4c / AX41 (her acceptance of 2026-11-10); AX44 (U).

**Reasoning (5 lines).** NFR-1 ranks accuracy first and leaves thresholds to the Expert; it does not say where an escalation is addressed, so it supports whichever reading keeps the number in front of her without diluting the threshold, and both do: under R1 and R2 alike the finding reaches her once, in the PR, with SE, VOV and p95. R2 is the reading of her decision's own definition (AX38 4c states "at a gated scene" three times; §3's parenthesis names the reported set as where the replicates come from, not as the floor's scope). R1 taken literally would also make every reported-set case with SE > 0.33 dB in the starting state (layouts 4/5 near-wall, SE 0.13–1.33 dB) an item-1 escalation, although AX41 already records those as the accepted (A) cost (Seat 1's 2 / 2, accepted 2026-11-10); that is a consequence no seat rated and her decision did not ask for. Placing the record beside item 1 in the PR satisfies R1's "escalated once" at zero cost, so nothing is lost if she holds R1. The threshold itself is untouched (NFR-1: from the Expert, here Seat 1, whose P-a′ condition asks escalation at the s = 1 cube on the p95 line only, L41).
- *Fire now on the s = 1 finding (R1):* serves a literal reading of §2 item 1's parenthesis; strains AX41's accepted cost cell (every reported-set SE > 0.33 dB would fire) and Seats 8, 9's "an escalation about a non-room" (P-b cells).
- *Not fire; record once beside item 1 (chosen, R2):* serves NFR-1 (the number reaches her; the threshold stays the Expert's) and her 2026-11-10 decision's own definition of the floor's scope.
- *Not fire and not record:* strains NFR-1 (a known floor failure unreported); not on the table.

**What would make her veto it.** She reads §2 item 1's parenthesis literally (R1) and wants every starting-state floor failure in the reported set treated as a fired item 1, not as a finding recorded beside it.

No AMENDS line: it reads AX38 4c's scope ("at a gated scene"), it does not change it.

---

## D-H2 — which AX43 / AX45 / AX46 case-bands have a certified reference now

### Knowledge inventory
K20–K28 unchanged (file 8).

### Tension map, D-H2 (cells unchanged, file 15 P05H-26 "faithful"; sums corrected)

| seat | G-a | U-a | U-c | M-e | M-a | M-b | M-c | M-d | B-a | B-b |
|---|---|---|---|---|---|---|---|---|---|---|
| 1 | 1 / 1 | 0 / 1 | 1 / 0 | 0 / 1 | 1 / 1 | 1 / 2 | 1 / 1 | 1 / 1 | 0 / 1 | 1 / 1 |
| 2 | 1 / 1 | 0 / 0 | 1 / 0 | 0 / 1 | 0 / 1 | 1 / 1 | 1 / 2 (live) | 0 / 1 | 0 / 0 | 1 / 1 |
| 3 | 1 / 1 | 0 / 0 | 1 / 1 | 0 / 1 | 1 / 1 | 1 / 2 | 1 / 1 | 1 / 1 | 0 / 1 | 1 / 1 |
| 4 | 1 / 1 | 0 / 0 | 1 / 0 | 0 / 1 | 0 / 1 | 1 / 2 | 1 / 1 | 0 / 1 | 0 / 0 | 1 / 1 |
| 5 | 1 / 1 | 0 / 1 | 0 / 1 | 1 / 1 | 1 / 1 | 1 / 1 | 2 / 2 (live) | 1 / 1 | 1 / 1 | 0 / 1 |
| 6 | 0 / 0 not required (NOT MY MATTER, L50) | | | | | | | | | |
| 7 | 1 / 1 | 0 / 0 | 1 / 1 | 0 / 1 | 0 / 2 | 0 / 2 | 1 / 1 | 1 / 1 | 0 / 0 | 0 / 1 |
| 8 | 1 / 1 | 0 / 0 | 0 / 0 | 0 / 1 | 0 / 1 | 1 / 2 | NMM | NMM | NMM | NMM |
| 9 | 1 / 1 | 0 / 0 | 1 / 1 | 0 / 1 | 1 / 1 | 1 / 1 | 1 / 1 | 1 / 0 | 0 / 1 | 1 / 1 |
| max / sum | 1 / 16 | 1 / 2 | 1 / **10** | **1 / 9** | 2 / **13** | 2 / 20 | 2 / **17** (live) | 1 / 11 | **1 / 5** | 1 / **12** |

### Minimum-tension working
Unchanged: bounds (X4 dropped); no 3; worst-off U-a, M-e, M-d, B-a at 1; no composition needed; sums U-a 2 < U-c 10; M-e 9 < M-d 11 < M-a 13; B-a 5 < B-b 12; all additive. **Decide:** G-a with the seats' conditions, U-a, M-e (M-d and a manual artifact job as routes), B-a.

### DECISION D-H2 (plan text; the scope-now reading is H2-F1)

**(a) Gating rule (G-a).** "A case-band of AX43 / AX45 / AX46 is **gated** when the agreement golden holds for it a reference at two rungs of the ℓ ladder with the finer-rung change < 1 % (AX36, per quantity), ℓ_ref = that change recorded per case-band; the committed `phase05b.json` `ell` / `r1`, the c4 CS-NW+ values (once the session-2 1.25 m run reproduces them: `6-orchestrator-K20-certified-listing.md` cross-check) and this session's `hybrid_fast` runs all count. Everything else is **reported, not gated (reference pending)** and listed per case-band with its status (gated / single-rung uncertified / none) **in the agreement golden itself**, extended only through `update_goldens.py --extend` with a CHANGELOG reason, so that promotion is visible and the implementer can never narrow the set. z_FW stays 4.290 (AX43) and 3.81 (AX45), conservative on the subset. The report prints '<gated> of 560 gated; <n> reported (reference pending)' and '<gated> of 72 gated' in the same table (274 / 560 and 40 / 72 at the time of writing, growing this session); Phase 13's copy is written from that line. The gated set keeps at least one room with per-band α (club, living_room, classroom, dead_booth are certified) and one with mixed per-face s (the orchestrator confirms from the fixtures; else the gap is reported; PR #27 m-10). The listening-pack README states per room whether its tail level is gated, reported-only or without reference; the 05h PR's accuracy paragraph counts gated case-bands only and labels the listening line as listening content. Phase 08 goldens in rooms with ungated case-bands carry 'tail-level reference pending (D-H2)' in `tests/golden/CHANGELOG.md`. The M-2 tracer comparison is printed per band for the five mixed-α Phase 04 rooms. CI: the `build` job gets a `timeout-minutes`; the agreement suite's per-OS wall time is printed; Seat 5's budget is ≤ 10 min added wall time per OS, above which the BRAS pairs' bias check moves to the nightly (AX43's reversal clause)."

**(b) Single-rung references (U-a).** "A case-band whose reference exists at one rung only is **printed, never asserted**: |C++ − ref| in dB and z, on the same line as the fixed label `uncertified rung, no ℓ_ref, not pass/fail`, in the job summary and the phase record; never counted in a pass total or in public wording. It is a gross-error detector (a wrong face, a unit, a prune radius at per-band α); a difference > 1 dB is a flag worth a look, a small difference is not evidence of agreement to τ."

**(c) Producing the missing references (M-e, with the committed priority order).** "References are produced offline by `tools/validation/hybrid_fast.py` at two rungs (2.5 → 1.25 m) per band column, committed by script with provenance (tool commit, hash-pinned numba/numpy, rungs, ℓ_ref) and the CHANGELOG reason; never computed live in a gate. This session's 4-core background runs continue in this order, and **phase-05i gates whatever is certified by then; the rest stays reported and listed, never dropped**; every item not finished in 05i gets a named owner phase before Phase 12 freezes presets and before Phase 13 writes copy. Order (merged from Seats 1, 2, 3, 4, 8, 9: audible relevance and use first, cost deciding ties): (1) `concert_hall_box` both emitters at 1.25 m (chunked; 2.7–4.4 GB per band column) and `stone_box` both emitters at 1.25 m (cheap: ≤ 720 patches); (2) W1 e0 and e1 at 1.25 m, all 8 bands (≈ 1.2 GB; the kernel persisted to disk once); (3) the CS-NW+ emitter-1 cases and the 0.3 m wall case, 500 Hz–2 kHz first, then all bands, as gathers on the persisted W1 kernel; (4) W2 both emitters (≈ 3 GB); (5) the BRAS pairs' 250 Hz and 4 kHz, then 125 Hz and 8 kHz, 63 Hz last (15 GB class: gated when certified, never claimed as a room validation below the Schroeder frequency, Seats 1, 2, 9). Routes for the 15 GB class if this machine does not fit them: a manual, Linux-only, hash-pinned `workflow_dispatch` job on the public 16 GB standard runner (6 h limit) that uploads the small reference JSON as an artifact for a person to commit (never a live gate input; F17–F20), or a larger machine for a few days (M-d), which only Maisara can provide and is listed for her as an action, not a decision."

**(d) AX46 now (B-a).** "The bias check runs now, per band and per class, on every class with ≥ 1 certified case at the pre-registered N (3·SE ≤ 1 % − ℓ_ref): reference positions, absorbing face, small rooms, and one-end near-wall once the c4 cross-check passes. Classes without a certified case print 'not evaluated (reference pending)'. The **100 m class** names the tracer (AX39: (f) − tracer = −0.009 dB) as an independent comparison, reported at the tracer's achieved SE and labelled 'not evaluated at 1 % (compute limit)' unless a larger run certifies the tracer's SE ≪ 0.043 dB; never an AX46 pass. The result appears only as the per-class table; AX46's pooled figure is computed over the evaluated classes and labelled 'pooled over <n> of 5 classes', never as a bare 'bias ≤ 1 %'."

**Confidence:** high for (a), (b), (d); medium for (c)'s order. **Reversal condition:** phase-05i's agreement test on a newly certified case-band shows |C++ − ref| > τ (one golden round); D-H3's ruling on the pooled |mean z| failure (file 9) may change how the BRAS references enter the family rule, not the gating rule here.

### Load-bearing claims, D-H2
D-H2-L1…L7 unchanged (file 8); the tracer SE arithmetic (K26, P05H-28) is a number to record, not decided on.

### Future-debt register, D-H2 (rows 2 and 5 corrected, P05H-27)

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (G-a, U-a, M-e, B-a later 1) | 286 / 32 case-bands owed before public wording; the label text frozen; the per-class-only bias form | nil (additive) | phase-05i | 05i, or a named owner phase |
| 2 (G-a later 1; M-e later 1) | **G-a: "the listening-pack rooms are ungated at the moment the switch lands" (L61)**; M-e: the order and the persisted kernels | — | the background-run log; 05i's agreement test | 05i (Phase 04 rooms first in (c)'s order) |
| 3 (G-a, M-e, B-a later 1) | `stone_box` and W1 (AX45) certified in 05i before "nothing audible changed" is said for them | a golden round if a reference arrives > τ | 05i | 05i |
| 4 (G-a, M-e later 1) | Phase 08 goldens in ungated rooms marked "reference pending (D-H2)" | a golden round plus a re-rendered pack | 05i's agreement test | 05i before Phase 08's freeze, else the mark |
| 5 (G-a, U-a, M-e, B-a later 1) | a monotonically growing golden; the ≤ 10 min per-OS budget; the artifact-job route if used; **U-a: "a print that could be quoted as validation" (L134), met by (b)'s fixed label and the "gated only" count rule** | a nightly move for the BRAS bias check; label text | the first Release run with the suite; the public wording draft (Phase 13) | standing; Phase 13 copy from the gated line |
| 7 (G-a, M-e later 1) | an owner phase for anything 05i leaves; M-d listed as her action | nil | 05i | before Phase 12 / 13 |
| 8 (G-a, M-e later 1) | the listening README's per-room status | — | the 05h pack | 05i |
| 9 (G-a, M-e, B-a later 1) | the bass bands and the preset rooms gated in 05i | — | 05i | 05i |

**Strongest objection.** Unchanged (Seat 7's M-a / M-b later 2: answered only if the order and the "gates what is certified, rest listed" rule are plan text and the status lives in the golden).

### FOR MAISARA H2-F1 — the scope of AX43 / AX45 / AX46 now (unchanged, SURVIVES)

**Question.** AX43 ("70 cases / 560 case-bands"), AX45 ("72 case-bands") and AX46 (five classes) were accepted on 2026-11-10 on the premise that every reference existed at a certified rung. Only part of the set does. Do the gates run on the certified subset now with the rest reported and listed, with the full set gated by phase-05i or a named owner phase?

**Answer (exact wording).** "AX43, AX45 and AX46 run now on every case-band and class with a certified reference (ℓ_ref recorded); the rest are reported, not gated, listed per case-band in the agreement golden, and gated in phase-05i or a named owner phase as their references are certified in the committed priority order. No case-band is dropped, no tolerance widened, and no accuracy claim counts a reported case-band."

**PRD ids and decisions.** NFR-1 (L105: "Rendering must match impulse responses … Pass thresholds come from the Expert"); CLAUDE.md's verification culture (tolerances follow from the requirement; goldens never regenerated to pass); AX43 ("the finest certified rung, with ℓ_ref recorded"); her acceptance of 2026-11-10; "build the switch (option (b))", 2026-11-09.

**Reasoning (5 lines).** AX43's own text gates against "the finest certified rung, with ℓ_ref recorded"; a case-band without one cannot be gated without inventing a tolerance (X4), which the verification culture forbids. Gating the certified subset now lets the switch (her 2026-11-09 decision) land with its evidence instead of waiting a phase; the family rule on a subset is conservative, so nothing passes more easily. Reporting the rest in the same table keeps NFR-1's claim honest. Additive promotion costs no shipped bit.
- *Gate the certified subset now, rest listed (chosen):* serves NFR-1 and the switch's delivery; strains nothing.
- *All references first (M-b):* serves a literal "560" but delays the switch a phase and leaves the listening pack's rooms unreferenced longer (Seats 1, 4, 8: later 2).
- *Gate uncertified rungs at a widened tolerance (X4):* strains NFR-1 and the verification culture; out at bounds.

**What would make her veto it.** A reading that AX43's "560 case-bands" is a hard count that must be gated before any golden freezes, whatever it costs the switch's delivery.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AX43, AX45, AX46: "the subset with a certified reference now; the rest reported and listed; gated in phase-05i or a named owner phase" added to each row's scope.)

---

## Summary table

| id | decision (exact value / wording) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-H1 (i) P-a′ | gated cube `cube100_lowalpha0.05_s0.3`; s = 1 cube reported, p95 > 1 dB escalates; buildable by a user → U | stands (corrected) | Seat 1 (1 / 1 rfc), Seat 5 (1 / 1) | 9 | medium | NFR-8, NFR-1, FR-3D-4/AQ3/AX6 | Table 6.1; Kuttruff L2504 | replicates at a later W_max cross a line |
| D-H1 (ii) R-e | starting state = file 10 record (no golden); record rises ≥ 0.05 / 0.10 dB; escalate on 0.33 dB / 1 dB crossings | revised | Seat 2 (1 / 1 rfc); Seat 5 0 / 1 rfc pending | 6 (7 on branch (B) → R-d) | medium | NFR-1 | Table 6.1 | Seat 5's R-e cell ≥ 1 now → R-d |
| D-H1 (iii) Q-d | ratio 1.02; W_pilot/W_final exact in D5 | stands | Seat 5 (0 / 1) | 1 | high | AX41 | — | a gated scene scatters > 1.02 |
| D-H1 (iv) | W_max 3.05 M pinned; n\*_max 1 024; (C)'s W_max only after the bounce record | stands (corrected) | Seat 1 (2 / 1) | 17 / 3 | medium | NFR-1, L101/NFR-2 | Eq. (11.21) direction; Table 6.1 | 07c's re-derivation |
| D-H1 (v) W-x′ | strict ≤ 29.1 s, register + growth bound elsewhere, none unasserted; 07c next with condition 9; finding named; §5 row, 07c §5/§9 amended | stands (corrected; rests on H1-F2) | Seat 1 (2 / 1) | 17 (18) | medium | L101/NFR-2, NFR-8, FR-SIM-6 | — | O18 three-OS run; 07c's loop; Phase 13 |
| H1-F1 | 14 × t_restore ≤ 30 s stands as a project convention; 14 a constant | for Maisara (corrected) | — | — | high | L101, NFR-2, NFR-6 | — | her veto |
| H1-F2 | register + 29.1 s OS rule + remedy ladder to the synthesis | for Maisara (corrected) | — | — | medium | L101, NFR-2, NFR-1, NFR-8, L20, L55 | — | her veto |
| H1-F3 | item 1 does not fire; the s = 1 finding recorded once beside item 1 in the PR | for Maisara (revised) | — | — | high | NFR-1, L49; FR-3D-4/AQ3/AX6 (buildable) | Table 6.1 | her veto (R1 reading) |
| D-H2 (a)–(d) | gate the certified subset by listing; U-a print; M-e order; B-a per class, 100 m = tracer, labelled | stands (corrected) | Seat 5 (1 / 1) | 9 (M-e), 2 (U-a), 5 (B-a) | high / medium | NFR-1 | Table 6.1 (τ) | 05i agreement > τ; D-H3 |
| H2-F1 | AX43/45/46 scope now: certified subset; rest listed; 05i or owner phase | for Maisara (stands) | — | — | high | NFR-1 | — | her veto |

## Challenges to settled decisions
None.

## Decided for Maisara
- **D-H1 (i)–(v) accepted for her** (PRD check: no hard constraint broken — NFR-8 no scene-specific code, FR-SIM-6 no range narrowing, NFR-6/AX5 determinism kept; no PRD goal points to another surviving option: W-c would serve NFR-1's random-error part sooner but holds the ≈ 4 jnd systematic AX16 error a phase longer, L55 makes the delay cost no deadline but L49/NFR-1 "accuracy first" favours removing the larger error first, and W-c still fails on macOS; W-b strains NFR-1). Chosen: the s = 0.3 cube gated, R-e as a record (R-d if Seat 5 prices the record at 1), ratio 1.02, W_max 3.05 M and n\*_max 1 024 pinned, the gate strict where ≤ 29.1 s and a registered defect elsewhere, phase-07c next with condition 9 created. **Seat 1 gave the most** (2 now: random tail-level error 0.38 dB at the s = 1 box and 0.13–1.33 dB in the layout 4/5 class until (C)); it gets back a W_max from the background budget at phase-07c, next phase, and the p95 escalation line at the reported s = 1 cube.
- **H1-F1:** the 2.143 s per-restore bound is kept as the project's own convention (L101, NFR-2, NFR-6), no longer attributed to pluginval. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **H1-F2:** the restore block runs strictly where it passes with margin and as a registered defect where it does not, with a growth bound, an end date per entry, and the remedy extended to moving the unit-decay synthesis off the restore (L101, NFR-2, NFR-1, NFR-8). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **H1-F3:** Raise item 1 does not fire now; the s = 1 cube's floor failure is recorded once beside item 1 in the PR as a finding of the reported set, a bound no fixture or preset approaches and a user may build (NFR-1; FR-3D-4, AQ3, AX6; AX44).
- **D-H2 accepted for her** (PRD check: NFR-1 served; no option breaks a constraint; M-b serves no PRD id better). **Seat 1 gave the most** (later 1: 286 + 32 case-bands owed before public wording); it gets them back in phase-05i or a named owner phase, with the order fixed in plan text.
- **H2-F1:** AX43 / AX45 / AX46 run on the certified subset now; the rest listed and gated in phase-05i or an owner phase (NFR-1). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**NEEDS MAISARA:** none of the three cases arises. One **action** only a person can take is listed, not as a decision: M-d, a larger machine (≈ 32–64 GB, a few days, tens of euros [Hyp, Seat 7]) if the BRAS outer-band rungs and `concert_hall_box` at 1.25 m do not fit this machine or the 16 GB public runner; the plan does not depend on it.

## Changes against file 8, keyed by P05H id
- **P05H-03:** Seat 2 × W-x′ stated as the W-a cell 0 / 1 with Seat 2's words (L16, L27, L30, L46); sum 17 (18 under the other reading; winner unchanged).
- **P05H-04:** D-H1 (ii) restated: the starting state is the file 10 record (cited in the PR and ledger; baseline column of the margin report), no golden, no stored SD, no assertion; Seat 5's cell read from R-c's words 0 / 1 (rfc; K21), branch (B) 1 / 1 shown with the tie at 7 and the reversibility tie-break to R-d in Seat 5's undo column; first reversal condition = Seat 5's answer.
- **P05H-05:** register rows added for P-a′ (Seats 2, 3, 5, 6, 7, 8) and R-e (Seats 5, 6, 7, 9), "discharged by file 10" where so; Seat 5's "all W" row closed by H1-F1.
- **P05H-06:** "repaid when" rows name the `/fix-plan` edit that creates phase-07c §5 condition 9; 07d conditional on 07c's loop.
- **P05H-07:** Seat 8's bounce-record condition (L24) carried into (iv), (v) and row 8.
- **P05H-08:** R-a 17, R-b 13.
- **P05H-10:** the decided W variant named W-x′ (composed: Seat 5's W-x + 29.1 s rule + Seat 2's ladder + Seat 6's three conditions + Seat 8's bounce record); one composed variant per sub-choice.
- **P05H-13:** "linear in fs" → "≈ 2.5× from 48 to 96 kHz (file 7: 1 321 → 3 287 ms)"; D-H1-L4 restated.
- **P05H-16:** K12 "1–2.2 %" → "1.2–2.4 %".
- **P05H-19:** (v)(a) rewritten: strict ≤ 29.1 s; otherwise listed and asserted through the growth bound; no OS/scene unasserted; phase-05h §5 "Blocking" row and phase-07c §5 (conditions 7, 9) / §9 named among the amended texts, plus phase-08 scope 10.
- **P05H-20:** PRD L101 cited beside NFR-2 in H1-F1.
- **P05H-22:** PRD L55 on H1-F2's W-c line, with the random-vs-systematic weighing under L49 / NFR-1.
- **P05H-23:** H1-F2's AMENDS line names phase-07c §0's extension, phase-05h §5's row, phase-07c §5/§9; L101 cited.
- **P05H-24:** H1-F3 re-answered: FR-3D-3/FR-3D-4 dropped as support for "never approach"; "user-set" dropped; FR-3D-4 + AQ3 + AX6 stated as letting a user build the cube, with AX44's U as the protection; both readings of "escalated once" shown; NFR-1's bearing stated; the record placed beside item 1 in the PR so R1 loses nothing.
- **P05H-26:** D-H2 sums U-c 10, M-a 13, M-c live 17, B-b 12.
- **P05H-27:** D-H2 register row 2 adds Seat 2's G-a later 1 (L61); row 5 adds Seat 5's U-a later 1 (L134).

**Hand-offs to the orchestrator:** append Seat 5's R-e cell to `17-seat5-D-H3.md` when it arrives and apply reversal condition (1) if it is ≥ 1 now; re-baseline the register's medians from O18's three-OS run; print per-OS min/median/worst and the 14× figure in the job summary; put the s = 1 finding beside Raise item 1 in the PR; confirm m-10; persist the W1 and BRAS kernels; the c4 cross-check column; D-H3 untouched.
