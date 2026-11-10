# Decider — round 3 for D-H3 (a)–(e) (phase 05h session 2, `/fix-plan` step 3e, the last round)

Save as `/home/user/makroof/docs/review/phase-05h/27-decider-decision-D-H3-r3.md`. Corpus revision `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d` (`/home/user/makroof/docs/corpus/SOURCE_COMMIT`). Read this round: `26-interrogator-D-H3-r2.md` (P05H-72…102, six restatements, four questions); the seats' "## Round 3: (f9) cell" sections: `17-seat1-D-H3.md` L134–145, `17-seat2-D-H3.md` L146–154, `17-seat5-D-H3.md` L212–216, `17-seat7-D-H3.md` L150–156; `17-seat9-D-H3.md` L70–80 (its (f) = (f9) cell, revised after file 18); `25-decider-decision-D-H3-r2.md` in full; `docs/BUILD_PLAN.md` AX36–AX44 (L136–144); from the code: `tests/unit/test_diffuse_agreement.cpp` L236–345, `tests/unit/test_diffuse_reports.cpp` L39–82, L275–276, `tests/unit/test_hybrid_ir.cpp` L241–277. No corpus passage is newly relied on; Vorländer Table 6.1 (L2056–2060, G's 1 dB jnd) was re-read in file 20 and is used again here.

**State after this round.** D-H3 (a) / H3-F1: **revised — the decision changes from (e′) to (f9)**, on the complete map (the (f9) row now carries every convened seat's own cell) at step 5 (sum 7 < 9). D-H3 (b)–(e), H3-F2…F6: **stand, with the six restatements of file 26 applied**; no value, cell or winner changes. D-H1/D-H2: not reopened. Nothing is left contested, so no `FOR MAISARA` ruling on a contest is needed; this is the third round, the interrogator checks it once, and any verdict other than SURVIVES or SURVIVES WITH CORRECTIONS sends that item to her as NEEDS MAISARA, case (a), with both readings.

PRD digest, bounds X5–X11 and convening: unchanged from files 20 and 25 (P05H-37 SURVIVES).

---

## D-H3 (a) — AX43's pooled bias check (revised: (f9))

### Answers to the ledger

- **P05H-77 / Q1 (TENSION MISREAD).** Accepted: (f9) was Seat 9's round-1 option, so §4's "appeared after the round" branch did not apply and the ask was owed. The ask was made; the map below carries Seats 1, 2, 5, 7 and 9's own (f9) cells (Seat 3 `NOT MY MATTER`; 4, 6, 8 not required). S1 + S2 + S5 = 0 + 1 + 0 + 1 + 0 + 1 = **3 ≤ 4**, the interrogator's own falsification line: (f9) wins step 5.
- **P05H-76.** Restatement 1 applied (below, step 7 record).
- **P05H-81 / Q2.** The tree's cluster count is **25 reference rooms at 500 Hz–2 kHz and 22 elsewhere** (22 / 19 before the 88 newly certified case-bands; orchestrator, from the run); the CHECK derives every count at run time, so **the AX43 clause carries no count**; where the rationale gives one it says "at the time of writing".
- **P05H-82.** Under (f9) the "two readings of ℓ_ref in one row" sentence is withdrawn: the row now carries **one reading throughout** (Seat 2's now-0 reason). Q5's answer becomes simpler, below.

### Knowledge inventory (K-a1–K-a9 as files 20 and 25; added)

| id | what must be known | source | status |
|---|---|---|---|
| K-a10 | every convened seat's `now / later` on (f9) as a CHECK | seat1 L136 "now 0 / later 1 … can live with … level with (e′)"; seat2 L150 "0 now / 1 later; prefer over (e′) (my 1 / 1)"; seat5 L214 "now 0 / later 1"; seat7 L152 "Confirmed, 1 / 1, in my own words"; seat9 L74 "(f) additive bound: prefer, 1 / 1" | known (seat statements) |
| K-a11 | (f9) passes on the data, and its catch | seat5 L214 (from the code and file 18): band 4 \|+0.0008\| vs 0.0051 + 0.0040 dB; bands 0–2, 6, 7 \|−0.0046\| vs 0.0060 + ≈ 0.006 dB; seat7 L152 from file 18's means: 3·(0.0077/√53) + 0.0052 = 0.0084 dB vs 0.0009 (≈ 9×); 3·(0.0097/√23) + 0.0060 = 0.0121 dB vs 0.0046 (≈ 2.6×); seat2 L152 catch 0.009 dB; seat1 L141 catch ≈ 0.009 dB. **Note on seat1 L141's arithmetic:** "3 × 0.0040 + 0.0051 ≈ 0.009" multiplies the printed `3 SE_pool` (0.0040, L317) by 3 again; the seat's result (0.009) is the tree's 0.0040 + 0.0051 = 0.0091 dB, consistent with Seats 2 and 5; the slip is in the typed factor, not the value | known for file 18's set; the tree's current set (25 / 22 rooms, the H3-F6 golden move) is the pre-registered application run (below) |
| K-a12 | the cluster count in the tree | orchestrator, from the run: 25 at 500 Hz–2 kHz, 22 elsewhere; derived at run time (L327–334) | known; not pinned in plan text |
| K-a13 | Q3: whether the reports test's −85 dB is C1's quantity | from the code: `test_diffuse_reports.cpp` L69–81: late = Σ taps² from `peakAt + 0.05·fs` to the end, over `peak²` (broadband, the peak sample's squared amplitude) — the same definition as `test_hybrid_ir.cpp` L275–277 (`late < 1e-6·peak²`), the check AX37 (5.4) names "energy later than t_dir + 50 ms below −60 dB"; C1's "> 44 dB to spare" / "≤ −104 dB" (`docs/review/phase-05b2/2-orchestrator-C1-open-field.md`) is the matched tail's per-band window energy relative to the direct sound's energy: **two different quantities** | known |
| K-a14 | Q4: the standing instruments for (c)'s debt row 2 | from the code: the `[probe-denormals-detector]` line in `ci.yml` (L349–355; every OS, every Release run) and the `[pipeline]` FTZ test's per-architecture asserts (`test_diffuse_gate.cpp` L450–453) | known |

### Tension map (a), complete — `now / later`; seats 4, 6, 8 not required (0 / 0); Seat 3 `NOT MY MATTER` (0 / 0)

| option | S1 | S2 | S3 | S5 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|
| (a) ℓ_ref in quadrature per case-band | 1 / 1 | 1 / 1 | 0 / 0 | 0 / 1 | 1 / 1 | 1 / 1 | 1 | 9 |
| (b) per class, z as written | 2 / **3** | 2 / 2 | 0 / 0 | **3** / 2 | 2 / 1 | 2 / 2 | 3 | dropped |
| (c) as written, red by design | 2 / **3** | 2 / **3** | 0 / 0 | **3** / 2 | 2 / 2 | 2 / 2 | 3 | dropped |
| (d) (a) + (b) | 2 / **3** | 2 / 2 | 0 / 0 | **3** / 2 | 2 / 1 | 2 / 2 | 3 | dropped |
| (e) per reference room, z′ (base) | 1 / 1 | 1 / 1 | 0 / 0 | 1 / 1 | 1 / 1 (read from round 2, P05H-72 faithful) | 1 / 1 | 1 | 10 |
| (e′) (e) + the script's cluster key + the records printed (round-2 winner) | 1 / 1 "the print is my §6 form" | 1 / 1 "finding condition met" | 0 / 0 | 0 / 1 (condition met, K-a8) | 1 / 1 "a grouping edit, a `room` field … Not 2: the reading is written down" | 1 / 1 | 1 | 9 |
| **(f9) the additive bound as the CHECK: \|mean (C++ − ref)\| dB ≤ 3·SE_pool + mean ℓ_ref per band; the as-written, per-class and per-room z′ statistics printed as records** | **0 / 1** "costs my seat nothing it measures … a test of the estimator, which is what I asked for; later: the catch drifts with the set … repaid when the catch value is printed per band" (L138–139) | **0 / 1** "the per-case test's own reading of ℓ_ref … one reading throughout; passes; needs no cluster key; later: (i) the allowance drifts with the gated set, restated at each golden round; (ii) a one-room defect is invisible, so the per-room table stays printed" (L152–154) | 0 / 0 | **0 / 1** "one line … nothing red in the atomic push; the `room` column stays data; later: cluster-blind — swapped for (e′) at a test edit if RQ-H3-1 or a later room set shows the shared error must be grouped; the form most easily quoted as a tolerance (Seat 7's rule)" (L214–216) | **1 / 1** "a formula change on the same axis … now 1: one CHECK on a line the test already prints, the cheapest undo of the three; later 1: the §6 row must carry the reading and Phase 13 inherits the sentence" (L152); "prefer neither on cost"; (f9)'s public sentence "better … on wording alone" (L154) | **1 / 1** "prefer … passes 0.0009 against ≈ 0.008 dB; a 0.02 dB shared bias would still fail it by 2.5×" (L74) | **1** | **7** |
| (f7) Seat 7's register fallback; (x5) Seat 5's print + register | as file 25 (not needed; folded into the records) | | | | | | | |

### Working

1. **Bounds:** (f9) raises no constant, widens no τ, changes no z_FW, drops no case, reseeds nothing (X5, X6); it is a formula on the pooled clause only, on the axis (a) and (e′) share. Nothing dropped here.
2. **Veto:** (b), (c), (d) dropped (Seat 1 later 3; Seat 5 now 3; Seat 2 later 3 on (c)).
3. **Worst-off:** (a) 1, (e) 1, (e′) 1, (f9) 1. Tie.
4. **Compose:** no seat's condition lowers any (f9) cell: Seat 1's later-1 is repaid by the printed catch value (its "repaid when", which the decision adopts) but stays rated 1; Seat 2's later-1 is two debts "no new constant"; Seat 5's later-1 is structural (cluster-blind); Seats 7 and 9's 1 / 1 are the formula change itself. No composed variant. (The maximum, 1, cannot be lowered by any stated condition.)
5. **Sum:** **(f9) 7 < (a) 9 = (e′) 9 < (e) 10.** (f9) wins.
6. **Reversibility (record only, not reached):** Seat 7: (f9) "the cheapest undo of the three (one line, no residue)"; Seat 2: "the same test edit as (e′), smaller"; Seat 5: "swapped for (e′) at the cost of a test edit".
7. **Decide: (f9), as the seats rated it** (the additive bound as the CHECK; the as-written, per-class, per-case-band z′ and per-room z′ statistics printed as records; the `room` column stays data), with the two repayments the rating seats named: the catch value printed per band beside the mean deviation (Seat 1) and the two debts written into the test comment and the register (Seat 2). **Record for P05H-76 (step 7 (i), no longer the deciding step):** "(a) is 'can live with' for Seats 1, 2, 7 and 9; Seat 5 labels nothing and sits at 0/1 on (a) and (e′) alike"; on (f9), Seat 1 "can live with … level with (e′)", Seats 2 and 9 "prefer", Seat 7 "prefer neither on cost", Seat 5 "the cheapest option on the table" on its own ground.

**Pre-registered application condition (the atomic push is never red by design).** The additive line is already computed and printed every run (L311–319). Before the orchestrator moves the CHECK onto it, the Release run of the agreement test on the current tree (25 / 22 rooms; after the H3-F6 golden move) must read "within" in every band. On file 18's set it does (K-a11, margins ≈ 9× at 500 Hz–2 kHz, ≈ 2.6× elsewhere), and the H3-F6 move takes it further inside (below). If any band reads OUTSIDE on the tree, (e′) stays as the CHECK (it is in the tree), the OUTSIDE line is recorded as a finding and the clause returns to the board; it is never made green by an edit.

**H3-F6 interplay (derived, approximate; the run confirms).** Each room contributes two case-bands per band (two emitters). Moving the four small rooms to 0.625 m: dead_booth's deviation falls from +0.017 to +0.0034…+0.0057 dB and its ℓ_ref rises 0.0073 → 0.0122 dB; living_room's ℓ_ref falls 0.0239 → 0.0039, classroom's 0.0065 → 0.0013, club's 0.0060 → 0.0024 dB (P05H-80's figures). Over 53 case-bands: mean deviation changes by ≈ (0.0045 − 0.017)·2/53 ≈ −0.0005 dB (→ ≈ +0.0004 dB); mean ℓ_ref by ≈ (+0.0049 − 0.0200 − 0.0052 − 0.0036)·2/53 ≈ −0.0009 dB (→ ≈ 0.0042 dB); the bound ≈ 0.008 dB against ≈ 0.0004 dB. Direction: further inside. (With 25 rooms the shares are smaller still.)

### DECISION D-H3 (a) and `FOR MAISARA H3-F1` — AX43's pooled clause (revised wording, (f9))

**Question.** Whether AX43's pooled bias check keeps its formula, carries the reference's own uncertainty, or pools by the reference that shares the error.

**Answer (exact wording for AX43, replacing "pooled bias check per band, |mean z| ≤ 3/√M"):** "pooled bias check per band over the M gated case-bands: **|mean (C++ − ref) in dB| ≤ 3·SE_pool + mean ℓ_ref**, where SE_pool = √(mean SE² / M) is the standard error of the mean deviation and ℓ_ref in dB = 10 log10(1 + ℓ_ref) is each reference's recorded last-halving change, entered additively as a bounded systematic residual of unknown sign — the same reading of ℓ_ref as the per-case N rule (z_FW·SE ≤ τ − ℓ_ref), so one reading throughout the row (the bound treatment of a systematic term: GUM, ITTC/GCI; researcher RQ-H3-1 F1, F4–F8). The right-hand side is the catch for a shared estimator bias (≈ 0.009 dB at 500 Hz–2 kHz and ≈ 0.012 dB elsewhere on the set at the time of writing: within Seat 1's 0.02 dB and 5× inside AX46's 1 %); it is a mean of magnitudes, so it moves with the gated set; it is printed per band each run beside the mean deviation and restated in the §0 record at each golden round, never pinned as a constant; if it exceeds 0.02 dB at any band the clause returns to the board. M and the room count are derived at run time; this clause carries no count. Printed every run as records, never checked: the as-written statistic (mean z = (C++ − ref)/SE over case-bands against 3/√M), the per-class means in both forms, the pooled mean of z′ = (C++ − ref)/√(SE² + ℓ_ref²) and its mean per reference room against 3/√M_rooms (room id = the `room` column written by `tools/validation/export_phase05h_references.py` (`room_of`): each (A) case its own room; each Phase 04 room over its emitters; W1 and W2 each one room over its emitters and placements, the CS-NW+ case-bands under W1; each BRAS room over its gated pairs; never a name regex in test code). The per-room record is the watch for what the mean cannot see: a room whose |mean z′| exceeds 3 (the row's constant) is labelled, and the count of rooms with positive and negative deviation is printed; either a labelled room or every room of one sign, with the per-case checks green, reopens this clause by a board round, with the per-room form (D-H3 (a) round 2, (e′)) the pre-registered alternative. The constant 3, τ, z_FW, the test N and the case list unchanged; the `room` column is a schema addition with a CHANGELOG reason; no value regenerated. **Phase 13 quotes** the per-case line (τ, the max |C++ − ref|) and the CHECKed pooled figure as the mean signed deviation in dB and % 'inside the references' own resolution plus three standard errors', with the printed bound; never the as-written or per-room numbers as a pass/fail, never 'no bias' bare, never 'validated'."

**Rests on:** NFR-1 ("Pass thresholds come from the Expert"; rendering must match measured IRs); the verification culture (CLAUDE.md: tolerances follow from the requirement and the statistics; a golden is never regenerated to pass; a red-by-design check is a defect); AX42 (ℓ_ref inside τ) and AX43's per-case clause (τ − ℓ_ref), which already carry the reference's uncertainty additively; AX46. Her decision of 2026-11-10 on AX43.

**Reasoning (5 lines).** The pooled clause is the one place in AX43 that forgot ℓ_ref (Seat 9): with per-case SE down to 0.002 dB the as-written pool resolves the reference's own rung residual (0.1–0.4 %), so it measures the reference, not the estimator (K-a4: mean deviation +0.0009 dB; the sign is dead_booth's rung residual). A statistic that cannot pass whatever the estimator does serves NFR-1 in no way and breaks the verification culture. The additive bound is the row's own per-case reading of ℓ_ref carried into the pooled clause — one reading, no cluster key, the line the test already prints — and it keeps the catch for a true shared estimator bias at ≈ 0.009 dB (A-L14). Nothing the data made red was loosened: the constant, τ, z_FW, N and the case list are untouched; the bound is derived from the references' recorded uncertainty, not fitted. It carries the least tension of any form on the table (sum 7; no seat above 1).
- (c) keeps the words and loses the check: NFR-1 strained, the verification culture broken, two vetoes.
- (a) per-item quadrature: serves NFR-1, passes, but applies a second reading of ℓ_ref in one row and under-counts the within-room correlation (F8); sum 9.
- (b)/(d) per class: red on the data (file 18); (c) under another name.
- (e′) per reference room: serves NFR-1 in F8's grouping form, but two readings of ℓ_ref, a golden key to maintain, and a sharper catch than any seat's criterion asks for (Seat 2); sum 9; the pre-registered alternative if the per-room watch fires.
- (f9) serves NFR-1 (a check that fails on a real shared bias of ≈ 0.01 dB) and the verification culture (one reading of ℓ_ref throughout the row; nothing red; the other statistics printed, nothing hidden); sum 7.

**What would make her veto it:** the reading "a tolerance changed after the data" (CLAUDE.md), sharpened to: the pooled clause now admits a shared bias up to ≈ 0.009 dB where (e′) would catch ≈ 0.0055 dB. The answer stands on the fact that no tolerance moved (the bound is the references' recorded uncertainty plus three standard errors, the per-case clause's own form), that both catches sit far below any perceptual line (1/100 of G's 1 dB jnd, Vorländer Table 6.1), and that the catch is printed and bounded at 0.02 dB with a board return above it.

`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX43's pooled clause).`

**One reading of ℓ_ref (P05H-44 / Q5, revised).** Both clauses now read ℓ_ref the same way: a bounded systematic residual of unknown sign, added linearly (per case: τ − ℓ_ref; pooled: 3·SE_pool + mean ℓ_ref). The quadrature forms (per case-band and per room) are printed as the diagnostic that carries the cluster structure the additive mean cannot see; the Phase 13 writer quotes the CHECKed figure only.

**Also recorded, unchanged from file 25 L89 (severable; "whichever option had won"):** the dead_booth / AX36 caveat and the four small rooms' convergence, with the AX36 AMENDS line (note only). Its last clause now reads: "(f9) passes either way; at the 0.625 m references the pooled mean moves toward zero and the bound stays ≈ 0.008 dB (H3-F6 interplay above); dead_booth's z′ ≈ 0.45 is a record figure."

**Load-bearing claims.** A-L1–A-L11 as file 25 (A-L1 adds: (f9) passes both band groups, K-a11). **A-L12 (seat statements, round 3):** the (f9) cells, K-a10. **A-L13 (derived from file 18 via Seats 5 and 7; from the code L311–319):** (f9) passes every band on file 18's set: 500 Hz–2 kHz |+0.0008…+0.0009| vs 0.0084–0.0091 dB; other bands |−0.0046| vs ≈ 0.012 dB. **A-L14 (derived; corpus Vorländer Table 6.1 for the jnd):** the catch is the right-hand side, ≈ 0.009 / 0.012 dB, against (e′)'s ≈ 0.0055 dB (A-L6); all ≤ 0.02 dB (Seat 1's intent) and ≤ 1/50 of G's 1 dB jnd, so the difference is diagnostic power, not audibility. **A-L15 (product judgement, NFR-1, CLAUDE.md; AX43's text "z_FW·SE_test ≤ τ − ℓ_ref"):** the additive bound is the per-case N rule's reading of ℓ_ref, so the row has one reading. **A-L16 (from the code):** L311 `sePool = √(mean SE²/n)`, L318 the additive comparison; `pooledDev` and `pooledZ` are filled in the same branch (L247, L256), so their n agree; the CHECK is one line.

**Future-debt register (f9).**

| seat | commits later phases to | undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 | the catch drifts with the set (mean ℓ_ref up with poorly certified rooms, down as rungs certify; SE_pool down with M); the one-sign failure is not caught by the CHECK | one line (→ (e′)) | each golden round; the small-room and 100 m classes when gated | the catch value printed per band beside the mean deviation (this push), bounded at 0.02 dB; the one-sign count printed |
| 2 | (i) the allowance loosens by the share of ℓ-sensitive cases added (s = 1 layouts 0.19–0.33 %), restated at each golden round; (ii) a one-room defect is invisible to the CHECK; the per-room table stays printed; the dead_booth / AX36 finding, the 0.625 m rung (H3-F6) and the ladder-sign check stand | the same test edit, smaller | each golden round; Phase 12 presets | the two debts in the test comment and here (this push); the labelled per-room line |
| 5 | cluster-blind: swapped for (e′) at a test edit if RQ-H3-1 or a later room set shows grouping is needed; the plain-dB bound is quotable as a "tolerance" | a test edit | RQ-H3-1; 05i's room set; Phase 13 wording | Phase 13 quotes under Seat 7's sentence; the (e′) code stays as the record |
| 7 | the §6 row carries the reading; Phase 13 inherits the sentence | a row re-amend; one line | Phase 13 wording | the §6 row written (this push) |
| 9 | the catch moves at each certified rung; the signed halving sequence is printed at each rung (its hand-off) | one line | each certified rung | each golden round's §0 record |

**Strongest objection:** Seat 2's debt (ii) with Seat 5's later-1: the mean is cluster-blind, so a one-room estimator defect of the dead_booth kind (+0.017 dB, z 8) passes the CHECK unseen. It holds anyway because (i) every case-band is bounded at τ by the per-case check, so a one-room defect above τ fails there; (ii) below τ, the per-room z′ record is printed with the > 3 label and the one-sign count, read at each golden round; (iii) the one such case on file is resolved by H3-F6 (the reference moves toward the C++: +0.003…+0.006 dB at 0.625 m). It would not hold for a persistent one-room offset between ≈ 0.01 dB and τ with no further rung to sign it; then (e′) by a board round, at one line.

**Confidence:** high (every cell the seats' own; the jnd from the corpus; the statistics from researcher findings marked read; PRD ids for the product claims), **conditional** on the pre-registered application run (the printed line "within" in every band on the current tree; else (e′) stays and the clause returns). **Reversal:** a labelled room (|mean z′| > 3) or every room of one sign with the per-case checks green (→ (e′), board round); the printed catch above 0.02 dB at any band (board round); RQ-H3-1 or 05i's room set showing the shared error must be grouped (Seat 5).

**Test change (orchestrator; exact, `tests/unit/test_diffuse_agreement.cpp`):**

1. L248–250, replace the comment:
```cpp
                    // D-H3 (a) (decider file 27, H3-F1): z' = (C++ - ref) / sqrt(SE^2 + l_ref^2) carries the
                    // reference's certified uncertainty as a standard uncertainty; pooled per case-band and per
                    // reference room it is printed as a record. The CHECK is the additive bound below.
```
2. L301–306, replace the comment:
```cpp
    // AX43 pooled bias per band, as amended by D-H3 (a) (docs/review/phase-05h/27-decider-decision-D-H3-r3.md,
    // H3-F1): the CHECK is the additive bound |mean (C++ - ref) dB| <= 3 SE_pool + mean l_ref, with
    // SE_pool = sqrt(mean SE^2 / M): l_ref enters as a bounded systematic residual of unknown sign, the same
    // reading as the per-case N rule (z_FW SE <= tau - l_ref), one reading throughout AX43. The right-hand
    // side is the catch for a shared estimator bias (about 0.009 dB at 500 Hz-2 kHz on the file-18 set); it is
    // a mean of magnitudes, so it moves with the gated set and is restated at each golden round (Seat 2); it is
    // printed per band beside the mean deviation (Seat 1) and returns to the board above 0.02 dB. Printed as
    // records, never checked: the as-written statistic (mean z against 3/sqrt(M)), the pooled mean z', the
    // per-class means in both forms, and the per-room z' means (one per reference room, the `room` column
    // written by tools/validation/export_phase05h_references.py, against 3/sqrt(M_rooms)). The per-room table
    // is the watch for what the mean cannot see: a room with |mean z'| > 3 is labelled and the rooms' sign
    // count is printed; either, with the per-case checks green, reopens the clause by a board round, with the
    // per-room form ((e'), decider file 25) the pre-registered alternative.
```
3. L307–339, replace the loop body (the `classZ` loop L320–326 unchanged):
```cpp
    for (std::size_t b = 0; b < 8; ++b)
        if (pooledZ[b].n > 0)
        {
            const double limitWritten = 3.0 / std::sqrt(static_cast<double>(pooledZ[b].n));
            const double sePool = std::sqrt(pooledSe2[b].mean() / static_cast<double>(pooledSe2[b].n));
            const double catchDb = pooledLRef[b].mean() + 3.0 * sePool;
            const bool within = std::abs(pooledDev[b].mean()) <= catchDb;
            std::printf("agree-full pooled bias band %zu [CHECK, additive]: mean (C++ - ref) %+.4f dB over %d "
                        "case-bands; bound 3 SE_pool + mean l_ref = %.4f + %.4f = %.4f dB (%s)\n",
                        b, pooledDev[b].mean(), pooledZ[b].n, 3.0 * sePool, pooledLRef[b].mean(), catchDb,
                        within ? "within" : "OUTSIDE");
            CHECK(within);
            std::printf("agree-full pooled bias band %zu [record, as written]: mean z %+.3f over %d case-bands "
                        "(3/sqrt(M) %.3f); mean z' %+.3f\n",
                        b, pooledZ[b].mean(), pooledZ[b].n, limitWritten, pooledZPrime[b].mean());
            for (const auto& [cls, stats] : classZ)
                if (stats[b].n > 0)
                    std::printf("agree-full pooled bias band %zu [record, per class] %-10s: mean z %+.3f, "
                                "mean z' %+.3f over %d "
                                "(3/sqrt(M) %.3f)\n",
                                b, className(cls), stats[b].mean(), classZPrime[cls][b].mean(), stats[b].n,
                                3.0 / std::sqrt(static_cast<double>(stats[b].n)));
            Stat rooms;
            int roomsPositive = 0, roomsNegative = 0;
            for (const auto& [room, st] : roomZPrime[b])
            {
                rooms.add(st.mean());
                (st.mean() >= 0.0 ? roomsPositive : roomsNegative)++;
                std::printf("agree-full pooled bias band %zu [record, room %d]: mean z' %+.3f over %d case-bands%s\n",
                            b, room, st.mean(), st.n,
                            std::abs(st.mean()) > 3.0 ? "  |mean z'| > 3 (one-room watch)" : "");
            }
            const double limitRooms = 3.0 / std::sqrt(static_cast<double>(rooms.n));
            std::printf("agree-full pooled bias band %zu [record, per reference room, z']: mean over %d rooms "
                        "%+.3f (3/sqrt(M_rooms) %.3f); rooms +/- %d / %d\n",
                        b, rooms.n, rooms.mean(), limitRooms, roomsPositive, roomsNegative);
        }
```
The old `CHECK(std::abs(rooms.mean()) <= limit)` (L338) is removed; no golden regenerates; the `room` column stays. Apply only after the Release run shows "within" in every band (the application condition above). Plan texts: AX43 (the wording above), AX36 (caveat, as file 25), phase-05h §5 bullet 2 ("pooled bias check: the additive bound, per band; the as-written, per-class and per-room forms printed"), phase-05h §0 notes (the catch per band at the time of writing; the room count 25 / 22), Phase 13's accuracy wording inherits Seat 7's (f9) sentence.

---

## D-H3 (b) — U at the default placement of `edge_values` and `open_field` (stands; restatements 4 applied)

Decision (d), map (max 1, sum 9), working, register, claims B-L1–B-L3, B-L5–B-L9: as file 25. **Corrections:**

- **P05H-86.** In the H3-F2 answer, "the two contract-limits fixtures are named in the printed cause line" becomes: "**the two contract-limits fixtures are named by the golden's pinned U** (`phase05h_d5_hashes.json`, which fails first for any user-reachable room whose U rises); **the cause line prints the cause** (cap / both-near / VOV_union ≥ 0.1) for every fixture whose U is raised." The same wording in phase-05h §5 bullet 6.
- **P05H-87 / Q3.** They are **two different quantities** (K-a13). **B-L4 (restated):** "AX37 (5.4)'s kept check 'energy later than t_dir + 50 ms below −60 dB' is the broadband late energy from the direct peak sample + 50 ms to the end over the peak sample's squared amplitude (`test_hybrid_ir.cpp` L275–277; `test_diffuse_reports.cpp` L69–81 computes the same quantity); the reports test measures it at −85 dB at `open_field` (25 dB below the line), −30 / −16 dB at `edge_values`, +7 dB at `medium_room`. C1's '> 44 dB to spare' (≤ −104 dB re the direct sound) is the matched tail's per-band window energy relative to the direct sound's energy: a different quantity, not compared here, and **no margin has moved**." The H3-F2 display-rule sentence names the quantity it keys on: "… lies more than 60 dB below the direct sound **by AX37 (5.4)'s kept check (broadband energy after the direct peak + 50 ms over the peak's squared amplitude)** with E_target raised by 3·SE …". File 25 L116's "AX37 (5.4)'s margin now measured at 25 dB" is withdrawn in favour of "the reports test reads −85 dB on AX37 (5.4)'s own quantity, 25 dB below the line". The parenthesis "(C1 margin > 44 dB)" in AX37 (5.4) is C1's quantity and is left as it stands.

Test change: none beyond the tree. Confidence high. Reversal as file 20.

## D-H3 (c) — the AX37 (5.1) (i) denormal premise (stands; restatement 5 applied)

Decision (g) under Seat 7's condition with (f) the written fallback, map (max 1, sum 3), H3-F3, claims, strongest objection, confidence: as file 25. **P05H-92 / Q4, debt row 2 "repaid when":** "**standing — the `[probe-denormals-detector]` line in `ci.yml` (L349–355) on every OS, every Release run, and the `[pipeline]` FTZ test's per-architecture asserts (`test_diffuse_gate.cpp` L450–453), re-run on each path change**" (K-a14).

## D-H3 (d) — W1 both_corner's flags (stands)

(e5), H3-F4 wording, map, tie statement: as file 25 (P05H-95 SURVIVES). No change.

## D-H3 (e) — `reset()` on the audio thread; freeze / offline threading (stands; restatement 6 applied)

(e-x′), H3-F5, the phase-07c DECISION (conditions 10 and 11), the AX38 4c finding and the H1-F1 reading: as file 25. **P05H-98:** K-e12 and the AX38 4c finding read "≈ 4.8 s per restore; **14 such restores ≈ 67 s**" (2.664 + 2.14 = 4.80; 14 × 4.80 = 67.2), and the builder-idle citation is **`test_diffuse_records.cpp` L422** (not L385). **P05H-99 (note):** phase-05i has no §0 row or file yet; pre-existing, created when the split happens (CLAUDE.md).

## H3-F6 — the finest certified rung at the four small rooms (stands)

(A), as file 25's addendum, with its reasoning line "pooled (e′): dead_booth z′ ≈ 0.45" replaced by "pooled (f9): the move lowers the mean deviation and the bound alike (≈ +0.0004 dB against ≈ 0.008 dB at 500 Hz–2 kHz, derived above); dead_booth's z′ ≈ 0.45 is a record figure". Its AMENDS line (AX43: a record of application, no rule change) unchanged.

---

## Summary table

| id | decision (exact value / wording) | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| D-H3 (a) / H3-F1 | **(f9)**: AX43 pooled check = the additive bound \|mean (C++ − ref) dB\| ≤ 3·SE_pool + mean ℓ_ref per band (one reading of ℓ_ref throughout the row); the catch printed per band, restated each golden round, board return above 0.02 dB; as-written, per-class, pooled z′ and per-room z′ (the script's `room` column) printed as records with the > 3 label and the sign count; Phase 13 quotes the CHECKed figure in Seat 7's sentence; dead_booth / AX36 caveat; the four small rooms converge | revised (for Maisara; AMENDS AX43, AX36 note); applied after the pre-registered "within" run, else (e′) stays | Seats 7, 9 (1 / 1) | 7 ((e′) 9, (a) 9) | high, conditional on the application run | NFR-1; verification culture; AX42 / AX43 per-case form; AX46 | Vorländer Table 6.1 L2060 (jnd); researcher F1, F4–F8 (read) | a labelled room or one-sign rooms with per-case checks green (→ (e′)); catch > 0.02 dB; RQ-H3-1 / 05i's room set |
| D-H3 (b) / H3-F2 | (d), as file 25, with: fixtures named by the golden's pinned U, the cause line prints the cause; the display rule keys on AX37 (5.4)'s kept quantity (−85 dB at open_field; two quantities, no margin moved) | stands, with corrections (AMENDS AX44 (ii), AX41 J1) | Seats 7 (1 / 0), 9 (1 / 1) | 9 | high | NFR-8 / FR-SIM-2; FR-3D-3; FR-3D-5; NFR-1 | Kuttruff §4.3, §5.1; AX37 (5.4) | as file 20 |
| D-H3 (c) / H3-F3 | (g), as file 25; debt row 2 repaid by the standing `ci.yml` probe line and the `[pipeline]` FTZ asserts | stands, with corrections (reading; test DECISION) | Seats 3, 7 (1 / 0) | 3 | high (conditional on the re-probe; (f) medium) | NFR-6 / AX5; NFR-8 | none needed | as file 25 |
| D-H3 (d) / H3-F4 | (e5), as file 25 | stands (AMENDS AX44 clause) | all three (0 / 1) | 3 | medium | NFR-1; NFR-6 / AX5 | none | as file 20 |
| D-H3 (e) / H3-F5 | (e-x′), as file 25; "≈ 67 s"; L422 | stands, with corrections (AMENDS AX38 (i), AX38 4c note; DECISION phase-07c §5 conditions 10, 11) | Seat 3 (2 / 1) | 13 | medium | NFR-2 (L101); NFR-4; NFR-6 / AX5; NFR-8; L55; NFR-3 / FR-SIM-6 (automation case) | none | as file 20 |
| H3-F6 | (A), the 0.625 m references for the four small rooms, as file 25 | stands (AMENDS AX43, note only) | — | — | high | NFR-1; verification culture | — | the suite not green at 0.625 m (it is) |

## Challenges to settled decisions

None (as file 25).

## Decided for Maisara (final)

- **H3-F1 (AX43):** the pooled bias check becomes the bound the row already uses per case — the mean offset in dB must sit inside the references' own recorded resolution plus three standard errors — so the reference's uncertainty is read one way throughout the row; the old statistic, the per-room and per-class forms are printed beside it as records; the catch for a real shared bias (about 0.009 dB today, printed every run, bounded at 0.02 dB) stays far below anything audible; nothing else in the rule moved (NFR-1; CLAUDE.md verification culture; AX42/AX43 per-case form; AX46). It carried the least tension of every form heard (no seat above 1; sum 7 against 9). Seats 7 and 9 gave the most (a formula change on the public record); Seat 9 gets its own form, Seat 7 the public sentence in dB it judged better, the stated reading and the untouched constants; Seats 1 and 2 get the printed catch and the per-room watch. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX43).` Also the recorded caveat on AX36 (as file 25): `AMENDS her decision of 2026-11-09: "accepted by Maisara 2026-11-09 (no veto)" (AX36, note only).`
- **H3-F2 (AX44 (ii), AX41 J1):** as file 25, with the two corrections (fixtures named by the golden's pinned U; the display rule keys on AX37 (5.4)'s own quantity, measured −85 dB at the open field, no margin moved). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX44 Seat 6 (ii) and reversal; AX41 J1 clause).`
- **H3-F3 (AX37 (5.1) (i)):** as file 25 (no AMENDS; the standing probe and FTZ test named).
- **H3-F4 (AX44 cap-flag clause):** as file 25. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX44's "W1 both_corner asserts the cap flag").`
- **H3-F5 (AX38 (i), AX38 4c note) and DECISION D-H3 (e):** as file 25 ("≈ 67 s"). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX38 (i) class (1), correction T5T4-59 kept; AX38 4c: a recorded finding, no rule change).`
- **H3-F6 (AX43 application):** the four small rooms' references move to the finest certified rung now, with the reason recorded (NFR-1; verification culture). `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition" (AX43: note only).`

**NEEDS MAISARA:** none (no case (a), (b) or (c); no 3 overridden; nothing contested after three rounds). **Action for her or the contractor (not a decision):** the per-host trace runs (as file 25).

## Changes against file 25, keyed by P05H ids

- **P05H-77 (Q1):** the (f9) row completed from the five seats' own round-3 cells (S1 0/1, S2 0/1, S5 0/1, S7 1/1, S9 1/1; S3 NOT MY MATTER); steps 1–7 redone; **the decision changes from (e′) to (f9) at step 5 (sum 7 < 9)**; the AX43 wording, the H3-F1 answer, its options list, veto reading and AMENDS line, the register, the strongest objection, confidence and reversal restated for (f9); the test change rewritten (the additive line becomes the CHECK with the catch value printed, the per-room z′ demoted to a record with the > 3 label and the sign count); the pre-registered application run and the (e′) fallback stated; Seat 1's typed factor noted (K-a11).
- **P05H-76:** step 7 (i) restated ("four of the five; Seat 5 indifferent"), recorded though step 7 no longer decides.
- **P05H-81 (Q2):** the tree has 25 / 22 reference rooms; the AX43 clause carries no count; "at the time of writing" where a count appears.
- **P05H-82 / P05H-44:** the two-readings sentence withdrawn; one reading of ℓ_ref throughout the row.
- **P05H-86:** "named by the golden's pinned U; the cause line prints the cause".
- **P05H-87 (Q3):** two quantities named; B-L4 restated; "margin measured at 25 dB" withdrawn; the AX44 display-rule sentence names AX37 (5.4)'s kept check.
- **P05H-92 (Q4):** (c) debt row 2 "repaid when" names the `ci.yml` probe line and the `[pipeline]` FTZ asserts.
- **P05H-98:** "≈ 67 s"; `test_diffuse_records.cpp` L422.
- **P05H-99:** the phase-05i note recorded.
- H3-F6: its (e′) line becomes a record figure; (A) unchanged.

Nothing written to the tree; the orchestrator saves this as `/home/user/makroof/docs/review/phase-05h/27-decider-decision-D-H3-r3.md` and hands it to the interrogator for its one check.
