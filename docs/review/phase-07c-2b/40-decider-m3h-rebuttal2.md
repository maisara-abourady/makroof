# 40: Decider on M3-H, second rebuttal (answer to interrogator file 35). Phase 07c-2b

I only read files and changed none. The orchestrator saves this as `/home/user/makroof/docs/review/phase-07c-2b/40-decider-m3h-rebuttal2.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. The PRD digest is unchanged from file 28 L10–21.

**State: REVISED. The home is still H4+G. It goes back to the interrogator.**

What changed, and why the home did not:
- (a) now has a reference: the near-corner seeded tracer (a0), at r_d 0.05 m and 0.025 m, with the counting sphere wholly inside the room.
- (a1) is dropped. Seat 9 rates it 2, and the researcher marks a "0 dB" GA expectation NOT READY.
- "Not decidable" now has a gate consequence.
- The AX44/B15 gate is split by cause. Ruling a breach amends nothing. Scheduling a fix inside AX44's accepted debt is routed to a separate FOR MAISARA answer.
- New cells: S2 1/1, S5 1/1, S7 1/1, S9 0/1.
- H4+G, H3+G and H3 now all sum to 9. Reversibility still decides, for H4+G.

## 0. Answers to file 35

| item | verdict in file 35 | answer | state |
|---|---|---|---|
| **Q1** AX44/B15 | PRD MISREAD | **Accepted.** The reading of her recorded decision is answered as **FOR MAISARA M3-H-R1** (§4a), quoting L167 and L408. A breach ruling for (a) amends nothing. Ordering a fix before 08-4 for a cause inside AX44's accepted both-near debt would schedule B15, so it goes as a separate FOR MAISARA answer, written in 07e-b with the AMENDS line, and the gates hold until it survives. The split-by-cause gate is adopted from 38-seat2 §2, minus its (a1) trigger, plus one decider clause for mixed causes (§5 A2). **K16 restated** (§1). "Names the receiver side only" is removed from every text. "Decided for Maisara" is corrected (§7). | corrected |
| **Q2** (a)'s reference | FALLS (INCONSISTENT) | **Accepted.** (a)'s reference is (a0), the near-corner tracer at (a)'s exact positions (36-seat2 §2; 38-seat2; 38-seat9 §2; dossier F6, F7, F10, F11). **(a1) is resolved: dropped** as a reference and as a print. The diffuse control stays (c)'s tool only. Reasons: Seat 9 rates keeping it 2/2 (38-seat9 §3–4), and F3/F5 show 0 dB is not GA's own expectation for a corner emitter. (a2), the moved listener at 0.75 m, is a print for (a) and a reference for its own placement (38-seat2 verdict (iii); 36-seat9 (ii)). "Not decidable" opens no gate. The AX44 record path takes Seat 9's five conditions (36-seat9 §2(3)). Seat 5's (a0) run/gate text is adopted verbatim (39-seat5 §3) with Seat 7's cap of 24 runner-hours, its 36 h ceiling, standard runners and quota condition (39-seat7 §2, §4). GitHub figures are marked [Hyp] and none is load-bearing. Seat 2's hand-off to Seat 9 is answered: "Yes, I accept the bar" (36-seat9 §2(1)) and the inside-sphere tracer (38-seat9 §2). S9's cell is now its own rating. | corrected |
| **Q3** Seat 4 | TENSION MISREAD unless corrected | **Accepted.** The premise-breaker is now 07c-2b's ABX dates slipping (34-seat4 §3), in §3 step 6, the S4 register row, the second-closest objection and the reversal. "Repaid when" reads "07e-b rules no fix phase". **Seat 4's optional clause is adopted** in Item E (S4, 34-seat4 §4). | corrected |
| **Q4** Seat 5 residual | TENSION MISREAD unless corrected | **Accepted.** The S5 row carries the post-date residual in Seat 5's words: an unrouted discrete-field flip, "one board look plus possibly a fix phase", with evidence in "the first output-changing PR after the end date whose reason names a flip". "The end date passes" is removed as its repayment. S5 is cited to 34-seat5 §3–4, superseded for "now" by 39-seat5 §4. ‡ is removed. | corrected |
| **Q5** Seat 5 refinement | open | **First bullet adopted** (S5, 34-seat5 §6): the pytest failure output names the discrete fields that differ. It adds no board look, so Seat 7's §6 branch is untouched. **Second bullet (the Follow-ups routing) not adopted.** Seat 7 has not answered Seat 5's hand-off on whether a Follow-ups entry counts as a "board loop", and adopting it lowers no maximum (§3 step 4). Seat 5: "my 1 stands as rated". S7's later cell stays its own rating (39-seat7 §5) and is not read from conditions. | decided |
| K14/D-L8 | "0.5 m sphere" IMPRECISE | Now reads "receiver radius 0.5 m (default R_D)". | corrected |
| map S9 | marking | Superseded: 38-seat9 rates the adopted text 0/1 itself. | corrected |
| strongest objection | must be restated | Restated (§4). | corrected |
| inventory gap | AX44/B15/C13/cap pin missing | Added as K18–K19. | corrected |

## 1. Knowledge inventory (changes from file 33; K1–K15 and K17 stand)

| K | what must be known | source | status |
|---|---|---|---|
| K14 (restated) | Tracer receiver: counting sphere, **radius** r_d, default 0.5 m (`R_D`); gate k ≥ 684 gives 3σ ≈ 0.498 dB; N0 = ceil(254 V) = 1,524,000 for layout 4 | from the code, tracer.py L21, L27–28, L42–44 | known |
| K16 (restated) | AX44's GA-limit paragraph has **a receiver-side mechanism sentence** ("the GA tail level ignores the near-wall pressure rise") and **a disclaimer that covers both ends**: "No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners" | BUILD_PLAN L167, re-read | known |
| K18 | AX44's accepted debt is "both-near reads low, flagged, not bounded", repaid by B15. C13 §2 gives both-near capped medians of −0.35 to −6.72 dB. B15 is "none scheduled" (filed under NFR-1). AX44 cites "Accepted by Maisara 2026-11-10 (ledger P05B2-M-02)". Its reversal includes "the near-corner reference contradicts NW-4C by more than τ". `layout4_s1/both_corner` asserts the cap flag | BUILD_PLAN L167, L408; ledger L2070–2077 (her words: "I accept the board's answer by definition.") | known |
| K19 | At (a), only emitter L is both-near: listener (0.1, 0.1, 0.1), L (19.9, 29.9, 9.9), R = S1 (13, 20, 2), 2 m above the floor. (c)'s positions are interior: listener (10, 8, 1.7), emitters (7, 20, 2) and (13, 20, 2) | from the code, abx_kit.py L134–144; AX44 both-near is d < 0.70 m at both ends (L167) | known |
| K20 | Eq. 5.42 is a diffuse-field relation. Layout 4's geometry is Kuttruff's "severe deviation from diffuse conditions" (§5.7, Table 5.2 case 4). ᾱ = 0.28 | corpus: Kuttruff L2698 (Eq. 5.42), L2749 (§5.7), L2724 (§5.6 caveat); dossier F1, F2 (read) | known |
| K21 | 0 dB is **not** GA's own L − R expectation for a corner emitter, in layout 4 or in a diffuse control. The receiver factor cancels in the late tail; the source-position factor does not | dossier F3 (derived, medium), F5 (derived, low) | known as a negative: no source supports (a1)'s "0 dB". The size is uninformed, so (a1) cannot be a reference |
| K22 | A counting sphere wholly inside the room is unbiased for the sphere-averaged GA density. One that crosses a face reads low by V_in/V_sph (−1.88 dB at one face, 0.1 m clearance, r_d 0.5 m). The 3σ gate sees scatter only. The two-radius check tests the residual from spatial averaging | dossier F10 (read: Farina 1995 Eq. 1; code) | known |
| K23 | k ∝ π r_d² N, so ×100 at 0.05 m and ×400 at 0.025 m; k_eff ≈ 8/9 of hits. Pilot sizing N = N_pilot × 684 / k_pilot is valid | dossier F6 (Vorländer §11.2.2 Eq. 11.5, §11.2.5 Eq. 11.12, read), F7 (derived, high) | known |
| K24 | Layout-4 cost is in the annihilation regime: ×6.6 at 0.165 s, ×77 at 0.38 s, about ×2 near the floor. A per-bin gate needs of order 10⁹–10¹⁰ particles | dossier F9 (equations read; application derived, medium) | under-informed in magnitude. **Not load-bearing:** the adopted text sizes from a measured pilot and has a stop rule and an outcome in every case (fallback, then "does not count", then "not decidable" with gates shut) |
| K25 | 05h precedent: W1, r_d 0.05 m, 16 M particles, SE 0.25–0.32 dB, about 49 s per emitter (≈ 3.1 µs per particle) | dossier F11 (read) | known (corrected from "0.27–0.32") |
| K26 | SE fallback: 4.34/√k ≤ 0.5 dB ⇔ k ≥ (4.34/0.5)² = 75.3, so window k ≥ 76 | computed (tracer.py L28 σ form) | known |
| K27 | GitHub figures: 6 h job limit, $0.008/min, 2,000 min/month on Free, about 20 concurrent jobs, $0 on a public repo | 39-seat5 §6, 39-seat7 §4, all **[Hyp]** | uninformed. **Not load-bearing:** the texts use "the runner's job limit" and the quota "as read at dispatch", not these numbers. The 24 h cap is Seat 7's own-cost judgement |
| K28 | Sizes: 07e stays two S sessions with (a0), (a2); (a0) is compute time, not session time; 07e-c is the overflow under CLAUDE.md's two-session rule | 38-seat2 §3 [Hyp, own cost]; 39-seat5 §3 | known (seat own-cost claims) |

No load-bearing gap remains. Cells read from conditions: S2 on the adopted (a) text, and H3/H3+G cells on the new common 07e text (§2). **Confidence: medium.**

## 2. Tension map (now / later)

The variant rated is the decided H4+G plus the adopted texts. **07e and 07e-b are the same under every home** (32-seat7 §1; 32-seat5 §4; 32-seat9 §3), so every new cost (the (a0) job, the pin reruns, "(a) may end up flagged rather than fixed") is common.

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| H1 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 2 | ≥18 |
| H2-c | 0/2 | 1/2 | 0/0 | 0/2 | 1/2 | 0/1 | 1/2 | 0/0 | 0/1 | 2 | ≥15 |
| H2-cg | 0/1 | 1/1 | 0/0 | 0/2 | 1/1 | 0/0 | 1/1 | 0/0 | 0/0 | 2 | ≥9 |
| H4 | 0/1 | 1/1 | 0/0 | 0/1 | 0/2 | 0/1 | 1/1 | 0/0 | 0/0 | 2 | ≥9 |
| H3 | 0/1 | 1/1 | 0/0 | 1/0 | 1/1 ʳ | 0/0 | 1/1 † | 0/0 | 0/1 ʳ | 1 | 9 |
| H3+G | 0/1 | 1/1 ʳ | 0/0 | 1/0 | 1/1 ʳ | 0/0 | 1/1 ʳ | 0/0 | 0/1 ʳ | 1 | 9 |
| H4+G with (a1) as a verdict reference (38-seat2 merge) | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | 1/1 | 0/0 | **2/2** | 2 | 11 |
| H4+G, per-bin gate for (a0) | 0/1 | 1/1 | 0/0 | 0/1 | **3/3** | 0/0 | 1/1 | 0/0 | 0/1 | 3 | — |
| H4+G, no runner cap | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | **2/3** | 0/0 | 0/1 | 3 | — |
| **H4+G (decided variant)** | 0/1 | 1/1 ᶜ | 0/0 | 0/1 | **1/1** | 0/0 | **1/1** | 0/0 | **0/1** | **1** | **9** |

- The first four rows are dropped at max 2 on cells unrelated to the new texts. Those texts are common and add cost, so they cannot lower these rows. Their sums are lower bounds.
- ᶜ (read from conditions): Seat 2 rated its own 36 text (no (a1)) at 1/1 (36-seat2 §4) and its 38 merge (with (a1)) at 1/1 (38-seat2 §4). Its condition, later 2 → 1 "when the reference text and the gate text above are adopted" (36-seat2 §6), is met by the adopted text. That text is Seat 9's 38 merge of Seat 2's 36 text, plus the 0.75 m, the record list and the (a2) verdict that Seat 2 adopted in 38 §1–2.
- ʳ (read, not re-asked): the seat rated the new 07e text under H4+G only, and its stated reason names a cost of 07e's text, which is the same under every home:
  - S9: "H3+G … same as H4+G" (32-seat9 §3);
  - S2: "confirmed for H4+G and H3+G" (32-seat2);
  - S7: H3+G 1/1 (32-seat7 §3), and the cap cost is (a0)'s;
  - S5 later 1: "A pin bump means rerunning (a0)" (39-seat5 §5), a 07e cost. S5 now: H3+G was already 1 (the hold).
- † as in file 33: Seat 7's 29-seat7 rating, not re-rated.

**Basis of each decided-variant cell, in the seats' words:**
- **S1 0/1:** 29-seat1 §4 and §6. The audibility clause and the per-distance print are adopted. Seat 1 was not re-asked on the AX44 record path; Seat 1 sits in the board ruling that path requires (§5 A2).
- **S2 1/1 ᶜ:** now "the cost is (a0)'s compute"; later "(a) may end up flagged rather than fixed" (38-seat2 §4).
- **S3 0/0:** 29-seat3 §6, with C3-a adopted.
- **S4 0/1:** "Confirmed, unchanged" (34-seat4 §2).
- **S5 1/1:** now "a small sharded workflow and its merge test, plus runner minutes"; later, the pin rerun (39-seat5 §4–5). The 34-seat5 §4 residual stays in the register. A per-bin gate rates 3/3.
- **S6 0/0:** 29-seat6.
- **S7 1/1:** "H4+G with the 24 h cap: now 1, later 1" (39-seat7 §5). Without a cap it rates 2/3.
- **S8 0/0:** 29-seat8.
- **S9 0/1:** "Merged text: 0 … 1" (38-seat9 §3–4). Keeping (a1) rates 2/2.

## 3. Minimum-tension working (redone)

1. **Bounds.**
   - **(a1) as a verdict reference is out.** Eq. 5.42 is diffuse-only (K20), and no source gives GA's expected L − R at a corner emitter, even in a diffuse control (K21: F3, F5). Using it would be deciding on a gap (§3 rule).
   - **File 33's "fix before 08-4 whatever the cause" is out.** It would amend B15, her recorded decision, inside a board decision (decider.md §5). It is replaced by the split-by-cause gate.
   - Nothing else is dropped. No `src/sim` change happens in 07e or 07e-b, so NFR-8 stays binding.
2. **Veto.** The per-bin gate (S5 3/3) and the uncapped job (S7 later 3) are excluded. Their seats' conditions (per-window gate, cap with fallback; 24 h cap and 36 h ceiling) are adopted. Seat 6's conditional veto (clamp moved after release) stays excluded by the Out-of-scope text.
3. **Worst-off seat.**
   - Max 2, dropped: H1, H2-c, H2-cg, H4, and H4+G with (a1).
   - Max 1, kept: H3, H3+G, H4+G.
4. **Compose.** No variant lowers the max:
   - S2's and S9's later 1 → 0 needs "B15 gets an owner phase before 12-2" (38-seat2 §5; 38-seat9 §6). That would amend B15, which is a FOR MAISARA matter. It is premature before 07e-b's prints, and it would leave S1, S4, S5 and S7 at 1. It is carried, not composed. 07e-b's inside-debt FOR MAISARA answer is where it is decided.
   - Seat 5's routing bullet lowers no cell ("my 1 stands as rated") and risks S7's later cell. Not composed.
5. **Sum.**
   - H4+G = 1+2+0+1+2+0+2+0+1 = **9**.
   - H3+G = 1+2+0+1+2+0+2+0+1 = **9**.
   - H3 = 1+2+0+1+2+0+2+0+1 = **9**.
   - Three-way tie.
6. **Reversibility (restated per 34-seat4 §3).**
   - **Common to all three:** 07e/07e-b with (a0) and (a2); the 07d/07d-b split; JSON-pin board looks until the end date; the (a0) pin reruns.
   - **Only H3 and H3+G:** 08-1 and 08-2 (two M phases) wait from day one. Seat 7: "spent at the start and cannot be recovered" (32-seat7 §4).
   - **Only H4+G:**
     - the re-hear of 08-3's provisional verdicts, which happens "only if 07e-b rules a fix" (34-seat4 §2);
     - item 15 waiting on a long fix, **or on 07e-b itself if 07c-2b's ABX dates slip** by more than about 08-1 + 08-2 + most of 08-3 (34-seat4 §3).
   - The same slip under H3 or H3+G also holds 08-1 and 08-2, so "the slip separates the options in H4+G's favour" (34-seat4 §3).
   - Undo cost of H4+G: under 1 session, per 32-seat7 §4.
   - **H4+G is cheaper to undo.**
7. **Decide: H4+G (decided variant).**
   - **Confidence: medium.** No acoustic fact decides the home. Texts rest on K20–K26, all known. Read cells: S2 (conditions) and the ʳ cells.

## 4. DECISION M3-H (revised 2): H4+G with the 07e (measure) / 07e-b (rule) split, Lead Seat 2

The gates, the split and the parallel work are as in file 33 §4. In addition:
- (a)'s reference is (a0).
- "Not decidable" shuts the gates.
- The AX44/B15 gate is split by cause, with FOR MAISARA M3-H-R1 (§4a).

**Load-bearing claims:**
- **D-L1 to D-L4:** as in file 30, rated CORRECT in file 31.
- **D-L5 [seats]:** the cells in §2. Sums 9/9/9 (working in §3 step 5).
- **D-L7 [seat, own cost]:** 07e is two S sessions; (a0) is compute time; 07e-c is the overflow (38-seat2 §3; 39-seat5 §3).
- **D-L8 [code]:** the tracer receiver is a sphere of radius r_d (default 0.5 m) and is unbiased only when it lies wholly inside the room. At (a)'s 0.1 m clearance, r_d 0.05 and 0.025 m lie inside (tracer.py L21, L42; F10).
- **D-L9 [corpus + researcher]:** Eq. 5.42 does not apply at layout 4 (Kuttruff §5.7, L2749; Table 5.2 case 4), and no source gives a 0 dB GA expectation for a corner emitter (F3, F5). So (a1) cannot be a reference.
- **D-L10 [computed]:** the SE fallback threshold is window k ≥ 76 ((4.34/0.5)² = 75.3).
- **D-L11 [plan]:** AX44 L167 and B15 L408 as quoted in K16 and K18.
- **D-L6 [PRD]:** the acceptance check below, and FOR MAISARA M3-H-R1.

**Future-debt register (decided variant; every later ≥ 1):**

| seat | what it commits later phases to | what undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (L1) | A ruled fix fires M3-8: 07c-2b F1/F2 are void for their scene, and the omni rerun is needed | "deleting one file" (29-seat1 §4); now the two phase files | 07e-b's ruling | 07e-b rules no fix phase, or the M3-8 rebuild is done |
| 2 (L1) | One golden round plus M3-8's rebuild before the freeze, with the JSON re-pinned in that round; (a) may end up flagged rather than fixed under B15 (38-seat2 §4) | deleting the 07e files (29-seat2 §4) | 07e-b's ruling; any inside-debt FOR MAISARA answer | the fix phase lands before 08-4; for the flag residual, B15 gets an owner phase before 12-2 (38-seat2 §5) |
| 4 (L1) | Item 15 waits on a long fix **or, if 07c-2b's ABX dates slip, on 07e-b itself**, so 08-3 may split to 08-3b. Checklist verdicts heard before 07e-b `done` are provisional and are re-heard only if 07e-b rules a fix phase (34-seat4 §2–3) | not stated by Seat 4 | 07e-b's ruling; the ABX sitting dates | **07e-b rules no fix phase** (label lifted without re-hearing, Item E), or the re-hear |
| 5 (L1) | Scope 8 held and a likely 07d/07d-b split (not conditional on a fix). A board look per output-changing phase until the end date. **After the end date, a discrete-field flip is named in the reason and listed by the pytest, but "no gate stops it"** (34-seat5 §4). (a0) reruns on each numpy or Python pin bump (39-seat5 §5) | a flip: "one board look plus possibly a fix phase" (34-seat5 §4); a pin bump: one manual job (39-seat5 §5) | 07e-b's ruling; 07d's start; "the first output-changing PR after the end date whose reason names a flip"; the pilot's k_pilot | re-pin on the final restore path. **The flip residual is not repaid by the end date:** Seat 5 names no repayment, so it is carried open |
| 7 (L1) | 07d/07d-b split (about 1 session); 07e-b (about 1 session); longer holds on 08-4 and item 15; board loops until the end date; (a0) up to 24 predicted runner-hours (36 h ceiling) per run, rerun on each pin bump, sharing the minutes quota (39-seat7 §5) | before 07e starts: ½ session; after the JSON is committed: under 1 session (32-seat7 §4) | 07e-b's ruling; 07d's start; the pilot's k_pilot | the split closes; the end date passes; per pin bump, never (a standing cost of the reference) |
| 9 (L1) | (a) may end up flagged rather than fixed; "about 6 JND of G that a drag can reach", contained by U and the presets' distance from the corner (38-seat9 §4) | "a parameter change" (38-seat9 §4) | 07e-b's ruling | B15 gets an owner phase before 12-2 (FOR MAISARA), or (a) is fixed |

**Strongest objection: the read H3/H3+G cells (ʳ), above all S5 later.**
- They are the only cells whose other value would change the home. If Seat 5, asked, rates H3+G later **0** under the (a0) text, H3+G sums 8 and wins.
- Why it holds: Seat 5's later 1 rests on the (a0) pin rerun (39-seat5 §5), a cost of 07e's text, and Seat 5 itself says that 07e is the same under every home (32-seat5 §4). Any other S5 value for H3+G (now 2, or later 1) either drops H3+G or keeps the tie, which reversibility breaks for H4+G.
- The orchestrator may put that one question to Seat 5 before the interrogator.

**Second-closest: Seat 4's premise (34-seat4 §3).** What breaks it is **07c-2b's ABX sitting dates slipping** (07e depends on 07c-2b `done`), not the split. Item 15 then waits on 07e-b itself. Seat 4's later 1 already counts that wait, and the same slip holds 08-1 and 08-2 under H3 and H3+G.

**Third: Seats 2 and 9 later 1, "flagged rather than fixed".** Their stated repayment, B15 owned before 12-2, amends her decision. It belongs to 07e-b's inside-debt FOR MAISARA answer, made on the (a0) prints, and not to this decision.

**Reversal condition:**
- **Now:**
  - Seat 5 rates H3+G later 0 under the (a0) text → H3+G.
  - A seat rates an H4+G-specific cost (the re-hear, or item 15's wait) at 2 → H3+G.
  - A 2 on a common cost is answered in the text.
- **When 07e starts:** the pilot's k_pilot. If the predicted total exceeds 24 h, bands fall to the SE fallback; that is the cap working, not a reversal.
- **Later:** 07e-b's ruling.
  - If 07e-b rules no fix phase (and any FOR MAISARA answer it raises orders none), S4's and S1's conditional debts zero and the provisional label lifts.
  - If a fix cannot be ordered before item 15, the order goes to the board with Seats 4, 5 and 7.

**Accepted for Maisara (PRD check):** no hard constraint is broken, and no PRD id points to another survivor.
- **NFR-8 L112** ("Any valid scene renders correctly"): all three rule (a) against a non-circular reference before 08-4. A model feature is never an explanation, and the inside-debt case goes to her by separate answer. H3 leaves the re-pin order unrated.
- **FR-3D-5 L75** ("anywhere in the scene"): (a) is reachable (D-L4). Equal across the three.
- **NFR-1 L105** ("match impulse responses measured in real spaces and pass listening tests"):
  - (a0) supports only "the engine agrees with GA", not "matches a measured room" (38-seat9 §5). AX44 already calls the tail there "GA-true, not room-true", and no measured near-corner reference was found (dossier §3, R3).
  - So the reference is necessary for NFR-8, not sufficient for NFR-1. That holds equally under all three.
  - Item 15 is built on the ruled engine under all three. Under H4+G, earlier checklist verdicts are provisional and are re-heard only if a fix lands. The id does not separate the options.
- **L49/L101** (accuracy first): H4+G and H3+G order the CPU re-pin after the acoustic fix (G2). H3 does not.
- **L55/L174** (no deadline): H3 and H3+G hold 08-1 and 08-2, a cost the PRD does not ask for.

### 4a. FOR MAISARA M3-H-R1: reading AX44 and B15 against the 07e-b gates

- **Question:** does ruling finding (a) an NFR-8 breach, and ordering its fix before 08-4, amend her accepted AX44 (2026-11-10, ledger P05B2-M-02) and B15?
- **Answer (exact wording):**
  - "A breach ruling for (a) amends nothing. AX44 makes no accuracy claim at (a)'s geometry and names the near-corner reference in its own reversal.
  - Ordering a fix before 08-4 amends nothing where the cause lies outside AX44's accepted both-near debt.
  - Where the cause lies inside it (the both-near weight w or the capped branch, U raised, a deficit inside C13 §2's −0.35 to −6.72 dB), whether to fix before 08-4 or leave B15 unscheduled with U shown is a separate FOR MAISARA answer written in phase 07e-b. If that answer schedules B15, it carries `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`. The gates hold until that answer survives the interrogator."
- **Rests on:**
  - NFR-8 L112; FR-3D-5 L75; NFR-1 L105 (B15's requirement); L49/L101;
  - AX44 (BUILD_PLAN L167): disclaimer, debt clause, reversal;
  - B15 (L408); ledger L2070.
- **Reasoning:**
  1. L167 says "No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners". That withholds a claim; it does not assert NFR-8 holds there. Recording what the reference shows carries out her decision, and its reversal clause asks for exactly that check.
  2. What she accepted with a schedule is narrower. The debt is "both-near reads low, flagged, not bounded", repaid by B15, "none scheduled". Only a step that schedules that repayment changes what she accepted.
  3. NFR-8 ("Any valid scene") and FR-3D-5 ("anywhere") make (a) a valid, reachable scene that must be judged truthfully. L101 ranks accuracy first, but her recorded decision binds until a separate answer amends it (decider.md §5; README rule 1).
  4. Causes outside the debt (a one-end corner, the AX22 fallback, the t_mix,e rule, the ISM set at a corner source) were never accepted as debt. Ordering their fix amends nothing. That holds under either reading of "layout-4/5-type edges and corners" (Seat 9's hand-off), so the reading is not load-bearing.
- **Options:**
  - **(i) Chosen:** a truthful verdict with the amendment routed. Serves NFR-8 and FR-3D-5, and keeps AX44/B15 intact until she is answered for.
  - **(ii) AX44 excuses (a) as "not breached":** strains NFR-8 L112 and FR-3D-5 L75, because it calls a reachable, 6 dB-low scene correct. It also contradicts AX44's own "no accuracy claim".
  - **(iii) File 33's fix-before-08-4 whatever the cause:** serves L101 and NFR-8, but amends B15 with no answer, against README rule 1.
  - **(iv) Not judging (a) at all:** strains NFR-8 and FR-3D-5, and ignores AX44's reversal.
- **What would make her veto it:** she might read AX44's disclaimer as having placed layout-4 corners outside what is judged, so that a recorded "breach" relabels a state she accepted. And NFR-1's "measured in real spaces" makes a GA-internal verdict look beside the point. The answer to both: the verdict describes and schedules nothing, and the inside-debt schedule comes back to her as its own answer.
- **AMENDS:** none in this answer.

## 5. FINAL texts for the plan-editor (one `/fix-plan`)

Notation: **(S n)** attributes a clause to Seat n; **(decider)** marks my own words.

### Item A1: new file `docs/phases/phase-07e.md`
> # Phase 07e — NFR-8 placement findings from the 07c-2b ABX scenes: measurement (report only)
>
> Size: **S** · Depends on: [07c-2b](phase-07c-2b.md) `done` (the engine its golden round leaves) · Followed by: [07e-b](phase-07e-b.md) (the ruling; planned split, Seat 2: two S sessions) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; image-source order; … claims of physical accuracy" · Created 2026-11-24 by phase-07c-2b's M3 loop (`docs/review/phase-07c-2b/` decider files 17 §3, 28, 30, 33, 40 (H4+G); all nine seats, files 29-seat1…29-seat9, 32-seat2/5/7/9, 34-seat4/5, 36-seat2/9, 38-seat2/9, 39-seat5/7; researcher 29-researcher-RH1 and 37-researcher-a-reference; interrogator files 31, 35; Maisara's hand-back) · Read first, in this order: `CLAUDE.md`; this file; `phase-07e-b.md`; `docs/review/phase-07c-2b/5-builder-tail-spread.md`, `14-seat9.md` §2, `29-seat1.md` … `29-seat9.md`, `29-researcher-RH1.md`, `32-seat2.md`, `32-seat5.md`, `32-seat7.md`, `32-seat9.md`, `36-seat2.md`, `36-seat9.md`, `37-researcher-a-reference.md`, `38-seat2.md`, `38-seat9.md`, `39-seat5.md`, `39-seat7.md`, `40-decider-m3h-rebuttal2.md`; `docs/review/phase-05h/14-orchestrator-M2-near-corner.md`; `docs/BUILD_PLAN.md` §2 AX5, AX6, AX16, AX21, AX22, AX37, AX39, AX40, AX41, AX43, AX44, AX49 and §5 B11, B15; PRD NFR-1, NFR-8, FR-3D-5.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Measure, for each finding below, everything phase-07e-b needs to rule whether NFR-8 ("Any valid scene renders correctly") is breached and why. This phase gives no verdict. No `src/sim` change; nothing is tuned for a scene.
>
> ## Gates
> This phase opens nothing by itself. Phase-08-4, the build of phase-08-3 item 15's stimuli and phase-07d scope 8 wait on **phase-07e-b** `done` (and the fix phase it rules, if any) (Seat 2).
>
> ## Scope
> 1. **Findings** (builder file 5; 14-seat9):
>    - (a) `layout4_s1/both_corner`: emitter L (0.1 m from two walls and the ceiling) has a 1 kHz tail 6.20 / 6.12 dB below R's at equal absolute windows (−6.80 dB from each emitter's own t_mix,e). Listener at (0.1, 0.1, 0.1) m, 0.1 m from two walls and the α 1 floor; emitter L at (19.9, 29.9, 9.9) m; R at (13, 20, 2) m. Only L is within AX44's 0.70 m at both ends (both-near branch); the cap flag is asserted there (AX44) (S2).
>    - (b) `layout4_s1/both_wall`: tail onsets t_mix,e 0.165 / 0.380 s; from its own onset L's 1 kHz tail energy is +9.39 dB over R's (−0.05 / −0.03 dB at equal windows). Listener 0.1 m from the y = 0 wall, L 0.1 m from the y = 30 wall (S2).
>    - (c) lower priority: `layout4_s0.7/default`, −1.23 dB (L − R) from the common onset 0.380 s (−0.21 / −0.73 dB in the equal windows), not attributed (the room is not diffuse).
>    - The geometry of (a) is reachable from the canvas: a drag or automation lane past a face lands at exactly 0.1 m (`ParameterMap.cpp` `axisFromNormalized`; S6).
> 2. **Candidate causes:**
>    - (a): the diffuse estimator (AX39/AX41/AX44: the both-near weight w and the capped branch; AX40 fixes only its seed, whose effect is bounded near 0.083–0.33 dB); the image-source set at a corner source. The t_mix,e rule is demoted for (a): L's and R's onsets are 0.376 / 0.379 s (S2).
>    - (b): AX22's realised-k test at a source 0.1 m from a face. From the code, `planEmitter` moves the handover to t_cap,e only when the test fails, and R's 0.380 s matches the fallback time of the other layout4_s1 scenes (S2, [Inferred]). Mechanism to test [Inferred from AX22's formula, not measured]: near-coincident image pairs (about 0.58 ms apart) off a face 0.1 m away enter k_real = S²/Q as separate entries, roughly doubling k_real per such face (×4 for L with two faces against ×2 for R with one), so L can pass the k ≥ 19 test where R falls back. Measured in Python from `--images`: k_real with entries merged within 1 ms (print only). Or the t_mix,e rule (S2).
>    - Confirm with `ismFallback`, `expectedMixS` and `capTimeS` from `--diagnostics`.
> 3. **Measurement** (S2; no `src/sim` or CLI edit; every engine counter is already printed by `--diagnostics`; deterministic, AX5):
>    - A placement sweep at 0.1, 0.2, 0.5, 0.65, 0.75, 1 and 2 m from 1, 2 and 3 faces; each placement with the listener near and with it far; corners with and without the α 1 face (S2); and `medium_room` (8 × 12 × 4 m) at normalised 0 / 1 on 1, 2 and 3 axes (S6).
>    - For each placement and each emitter: the equal-window level per band, 63 Hz–8 kHz, against Eq. 5.42 (printed; a reference only where the field is diffuse, phase-07e-b scope 1) (S9); E_target against the `matchTail` energy; `--tail-level ax16` against the default; k_real and the fallback flag; the both-near and capped flags, w, n\*, N, W and U (S2).
>    - Per band and placement, the reference's uncertainty as used by 07e-b scope 1's band rule: for the tracer, from its gated window or bins as stated per run; for Eq. 5.42, stated in the report with its basis (decider; makes S2's band qualifier checkable).
>    - Per sweep, the equal-window 1 kHz deficit at each distance, with any step > 1 dB between neighbouring distances flagged as a jump the user would meet while dragging a source (S1). The flag is a print, not an audibility verdict.
>    - An indicative rigid-boundary column (researcher R-H1: Waterhouse 1958 Eq. 3, image sum; derived octave averages at 0.1 m, 1 kHz about −0.5 / −1.6 / −3.8 dB for 1 / 2 / 3 faces). It is printed and is never used to explain a deficit away (S9).
>    - Per placement and emitter: the handover time (after any AX22 fallback) and the AX21 step and dip at it, per band. L_f and L_p at the AX49 gated geometry and on `ax49_l4_cube` (S3, C3-a).
>    - **For (a), the reference and two required prints, each on its own placement** (S2, S9; 38-seat2, 38-seat9):
>      - **(a0) Near-corner tracer, at (a)'s exact positions: the reference for (a).** The seeded tracer (`tools/acoustics/tracer.py`) with its counting sphere wholly inside the room, at r_d 0.05 m and r_d 0.025 m (below the listener's 0.1 m clearance), as AX44's near-corner reference (`docs/review/phase-05h/14-orchestrator-M2-near-corner.md`). A band counts only where both radii are gated (window k ≥ 684, below) and agree within their combined 3σ. Eq. 5.42 is not a reference for (a): layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4). The engine is never its own reference; an emitter swap is never a reference.
>      - **(a2) Moved listener.** The same room and emitters; the listener moved along its corner diagonal to 0.75 m from each of its three faces (outside AX44's 0.70 m both-near flag and clear of the tracer's 0.5 m default radius); the seeded tracer at r_d 0.5 m, gated at k ≥ 684. It separates the source-side cause (the image-source set at a corner source) from the AX44 both-near branch; it is a print for (a) and a reference for its own placement only.
>      - **The engine's E_fwd and E_rev at (a)**, uncapped, at w = 1 and at w = 0, which separates the cap from w.
>      - Printed per band, 63 Hz–8 kHz: the late level per emitter and L − R, for the engine at (a) and in (a2), and for the tracer in (a0) at each radius and in (a2); for each emitter in each case, w, the both-near and capped flags, and U. The 29-seat9 §5 flatness claim is printed as support, never as the verdict. The diffuse control is (c)'s tool only (S9).
>    - **(a0) run, gate and sizing** (S5, 39-seat5 §3; cap and conditions S7, 39-seat7 §2, §4):
>      - (a0) runs as a manual CI job (`workflow_dispatch`), never on PR open, with its JSON uploaded as an artifact; that artifact is the reference. The seed is TRACER_SEED and is never changed (B11). The numpy pin is hash-locked.
>      - **Gate per window, not per bin.** For each emitter, radius and band, k = (ΣE)²/ΣE² is computed over the same late window the verdict compares, and the window counts when k ≥ 684. Per-bin k is not used for (a0).
>      - **Sizing.** (1) A pilot at N_pilot = 16 M (the 05h precedent) runs per emitter and radius. It records k_pilot per band and the measured µs per particle. (2) N = N_pilot × 684 / min_band k_pilot (F7), rounded up to whole 200,000-particle chunks. (3) The pilot's particles are the first chunks of N. Particles are added, never redrawn.
>      - **Sharding.** The job splits into shards of whole chunk ranges (`first_chunk`, `total_n` = N). Each shard's predicted wall time, from the pilot rate, is at most half the runner's job limit (read from GitHub's documentation at dispatch; Seat 5 holds 6 h, [Hyp]). Shards are merged by summing e and e². The merge is checked to be bit-identical to an unsharded run on a small N (a unit test).
>      - **Cap.** The total predicted runner time for (a0) is capped at **24 runner-hours (1,440 min)**, covering the pilot and all four runs (2 emitters × 2 radii) summed over shards (S7). If N for a band would exceed the cap, that band is gated for (a) only at SE ≤ 0.5 dB (window k ≥ 76), and the record says so. If it cannot reach that either, the band does not count (S5).
>      - **Runner and spend conditions** (S7): standard 2-core hosted runners only; a hard spend ceiling of 36 runner-hours (the cap plus one re-shard rerun), and reaching it counts as 'over cap'; (a0) is dispatched only when the remaining monthly Actions quota, as read and recorded at dispatch, is at least the cap plus one full PR CI run; the spending limit is never raised to finish (a0), and a shard that fails on quota counts as 'over cap'. The GitHub rates, quota sizes and concurrency limits in 39-seat7 §4 are [Hyp], not inputs to this rule.
>      - **On a timeout.** A shard that exceeds its limit fails the job. A partial result is never merged or used. The loop re-shards at the measured rate and reruns once. A second failure counts as 'over cap', and the cap rule applies. Compute time is not session time; 07e-c is opened only if the artifact is not back before 07e's second session ends (S5; CLAUDE.md two-session rule).
>      - The run record prints, per emitter, radius and band: N, k_pilot, window k, SE, whether the band is gated at k ≥ 684, on the SE fallback, or not counted; shards; the measured rate; predicted and actual runner hours; the quota read at dispatch (decider; makes S5's and S7's rules checkable).
>      - The (a2) and (c) tracer runs go in the same manual job, under the same sharding and timeout rule; their gates stay as written. Their predicted time is printed beside (a0)'s; if (a0) plus them would pass the 36 h ceiling, the session returns to Seats 5 and 7 before dispatch (decider).
>    - For (b): window energy from the full IR (not tail-only), to test whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s against R's ISM-only energy (S2).
>    - For (c): a diffuse control (the same room with its absorption spread over all faces to the same ᾱ in every band) and an independent late-level reference at equal times from the seeded tracer, every compared bin gated at k ≥ 684 (3σ ≈ 0.5 dB), so the reference's uncertainty is under 0.5 dB; 1.2 dB is about 1 JND of G (S9). The tracer's counting sphere lies wholly inside the room: r_d is below the receiver's clearance to every face, so with the default r_d 0.5 m the receiver is at least 0.5 m from every face; a sphere that crosses a face reads low and no 3σ gate detects it (S2, S9; researcher F10). (c)'s positions are interior (listener (10, 8, 1.7) m). Printed: L − R per band for the engine, the control and the tracer. Attribution: a spread that survives in the control is the engine's; one that only the tracer reproduces is the room's; if the tracer's 3σ band overlaps both readings, (c) is 'not decidable' with that stated (S9).
>    - The restore-work counters on the AX38 4c gate scenes: images per emitter, handover time, W_pilot, n\*, N, W (for a fix's effect on 07d scope 8) (S2).
>    - Nothing is fitted to the compared level (no circularity) (S2).
> 4. **Report:** `docs/review/phase-07e/report.md` prints every scope 3 value for (a) (with (a0), (a2) and the run record), (b), (c) and the sweep, with no verdict. Verdicts belong to phase-07e-b.
>
> ## Out of scope
> Any verdict on NFR-8 (07e-b); any `src/sim` edit; tuning for a scene; preset or canvas changes; moving the AX6 clamp; raising any spending limit; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] The sweep script and its output JSON committed; the JSON holds every scope 3 print for every placement, and the (a2) and (c) tracer references with their seed and gated counts. The output JSON records the producing platform (OS, CPU architecture, CI runner label, preset, commit); values are produced by the `cli` preset on the ubuntu-24.04 x64 CI runner (S5). The full sweep and every tracer reference run only in a manually started job or as a one-off print on that runner, never in the per-run pytest (S2, S5). A new job in `ci.yml` follows CLAUDE.md's `needs: changes` / `ci-ok` rules; a separate manual workflow is allowed; `tools/ci/test_ci_workflow.py` passes either way. A pytest in the `python` job re-runs ≥ 1 placement through `render_cli` and asserts every value bit-identically on that runner; on macOS and Windows, `ismFallback` and k_real equal, times and levels within AX5's cross-architecture bound as converted by the builder and stated in the test (AX5). A disagreement in a discrete field is a finding, never a tolerance; the pytest's failure output names each discrete field that differs from the JSON (`ismFallback`, k_real across 19, the both-near or capped flag) (S5, 34-seat5 §6). The JSON changes only through `tools/ci/update_goldens.py` (S5). Until phase-07e-b is `done` and the fix phase its ruling names, if any, is `done`: a red caused by another phase's output change (e.g. 07d's C5) is resolved in that phase's PR: it re-runs the sweep on the producing runner, updates the JSON through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, and puts the changed prints to the board for whether 07e's findings and 07e-b's ruling still hold. It is never regenerated just to pass, and the ruling is never carried over unasked (S5, 32-seat5). After that date, such a red is updated in that phase's PR through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, never regenerated just to pass (end date: S7, 32-seat7 §6; wording: S5, 29-seat5 §4); the reason states whether any discrete field (`ismFallback`, k_real across 19, the both-near or capped flag) changed (decider).
> - [ ] (a0): the manual job, the sharded run and the merge committed; the unit test that a sharded merge is bit-identical to an unsharded run on a small N is green; the (a0) artifact's JSON holds the run record of scope 3, and the report cites the artifact's run (S5).
> - [ ] §0 row 07e updated.
>
> ## Definition of done
> Scopes 1–4 complete; the JSON, script, pytest, (a0) artifact and report committed or linked; AC green in CI on Linux, macOS and Windows. The PR lists "Decided for Maisara". CLAUDE.md rules apply. The ruling is phase-07e-b's.

### Item A2: new file `docs/phases/phase-07e-b.md`
> # Phase 07e-b — NFR-8 placement findings: cause ruling (report only)
>
> Size: **S** · Depends on: [07e](phase-07e.md) `done` · Lead subject matter: Seat 2 (Engine architect) · Created 2026-11-24 with phase-07e as its planned split (decider files 30, 33, 40; 32-seat2 §2) · Read first: `CLAUDE.md`; this file; `phase-07e.md` and its report `docs/review/phase-07e/report.md` with the (a0) artifact; the files phase-07e lists; `docs/BUILD_PLAN.md` AX44 (§2) and B15 (§5).
>
> ## Raise with Maisara
> None. (A FOR MAISARA answer this phase writes under scope 1 is given for her under `docs/board/README.md`, "Who answers Maisara's questions"; it is not a Raise item.)
>
> ## Goal
> Rule, per finding (a), (b), (c), whether NFR-8 is breached and why, from phase-07e's prints, before 08-3's item 15 stimuli are built, before 07d's growth re-pin and before Phase 08-4. No `src/sim` change in this phase; nothing is tuned for a scene.
>
> ## Gates (what waits on this phase)
> Phase-08-4 (§0 Depends on), the build of phase-08-3 item 15's stimuli and phase-07d scope 8 (the growth re-pin) wait on this phase `done` and on the fix phase it rules, if any (S2, S5). Nothing else waits: 08-1, 08-2, the rest of 08-3 and 07d scopes 1–7 run in parallel; 08-3's checklist verdicts heard before then are recorded provisional (phase-08-3 item 7) (S4).
>
> ## Scope
> 1. **Board loop** (Lead Seat 2; decider; interrogator SURVIVES):
>    - It rules, per finding and per octave band in which the reference's uncertainty is under 0.5 dB: NFR-8 breached / not breached / not decidable, with the cause. For (a) only, a band on phase-07e's SE fallback (SE ≤ 0.5 dB, window k ≥ 76) also counts, marked 'SE ≤ 0.5 dB only' in the ruling (S2, S5, S9). The reference is the GA-internal level: the late level that the engine's own geometrical model predicts at equal times for each emitter at the scene's source power (Kuttruff Eq. 5.42 where the field is diffuse; elsewhere the seeded tracer with its counting sphere wholly inside the room). Breached: a spread > 1 dB from that reference. Not breached: every band within 1 dB. Not decidable: no such reference can be formed (S2; reference named as in S9). A spread produced by a feature of the engine (the AX44 weight w, the AX39/AX41 capped branch, the AX22 fallback, the t_mix,e rule, a cap) is its cause, never its explanation (S2, S9).
>    - **For (a)** (S2, S9; 38-seat2, 38-seat9): the reference is phase-07e's (a0). Layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4), so Eq. 5.42 is not a reference for (a). Verdicts:
>      - (i) if the engine at (a) differs from (a0) by more than 1 dB in a counted band (the per-emitter late level or L − R), (a) is breached;
>      - (ii) if the engine's L − R in (a2) differs from the tracer's by more than 1 dB, (a2) is ruled a breach as its own placement, with its cause;
>      - (iii) if no band of (a0) counts, (a) is 'not decidable'.
>      The 29-seat9 §5 flatness claim ('flat within ±1 dB from 125 Hz to 4 kHz → an engine effect') is printed as support, never as the verdict. The ruling names the cause, never its explanation.
>    - **'Not decidable' is never 'not breached' and opens no gate by itself** (S2, S9):
>      1. The loop first asks for the named print: (a0) at more particles, under B11's doubling rule, within phase-07e's 24 h cap and 36 h ceiling (S7).
>      2. If (a) is still not decidable, the gates stay shut until a board ruling with Seats 1, 4, 5 and 7 (S2), and Seats 6 and 9 for the note and the preset condition (decider), records (a) under AX44 as Maisara accepted it. The record requires all of the following (S9, 36-seat9 §2(3)):
>         - U raised at (a) and asserted in a test;
>         - the AX44 note shown at (a) in Phase 11;
>         - no fixture or Phase 12 preset default within 0.70 m of a layout-4/5-type corner (AX44 Seat 6 (ii));
>         - (a) entered as evidence on B15;
>         - the 'not decidable' listed under 'Decided for Maisara'.
>    - **On a breach: the gate splits by cause** (S2, 38-seat2; S9, 36-seat9 §2(4); FOR MAISARA M3-H-R1, decider file 40 §4a). The ruling quotes AX44 (BUILD_PLAN L167: the GA-limit paragraph, the debt, the reversal) and B15 (L408). A breach against (a0) is the AX44 reversal firing; it amends nothing.
>      - **Outside AX44's accepted debt.** Any one of these: verdict (ii) fires for (a2); the deficit against (a0) lies outside C13 §2's −0.35 to −6.72 dB; U is silent; or the cause is the ISM set at a corner source, the AX22 fallback or the t_mix,e rule. This is an ordinary NFR-8 breach, and the fix gate (scope 2) applies.
>      - **Inside it** (the both-near w or the capped branch, U raised, inside the envelope). Ordering a fix before 08-4, or leaving B15 unscheduled with U shown, is written as a separate FOR MAISARA answer (`docs/board/README.md`, "Who answers Maisara's questions"), with the line `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` if it schedules B15. The gates hold until that answer survives the interrogator (or, in one of the README's three cases, until Maisara answers).
>      - **Mixed causes.** The outside part takes the fix gate. Any part of a fix that changes the both-near weight w or the capped branch goes by the inside route first (decider).
>    - Before the verdicts it records, as already settled by this text, that the engine does not reproduce coherent near-boundary source radiation (R-H1; researcher F12): it is geometric, and as built its late level follows an energy target (E_target), so the reference above holds (S2, S9). AX44's GA-limit paragraph (L167) has a receiver-side mechanism sentence and a disclaimer that covers both ends ("No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners") (S2, S9; 36-seat2 §3, 36-seat9 §1). Whether the mechanism sentence should also name the source side (R-H1 §7) is recorded after the per-finding verdicts, not before them and not in their place, as a separate AX44 amendment (a FOR MAISARA answer with its AMENDS line, since AX44 is her recorded decision) (S9; decider). The rigid-boundary column (phase-07e scope 3) is therefore never a ground for 'not breached' and cannot reduce a spread (S9, S2). Changing that answer is a separate board decision with a new AX checked against the corpus, outside this phase; it applies at the source to the direct, early and late parts alike, and under it a spread counts as explained only where it matches that model's per-band prediction within 1 dB and arises from that mechanism (S2).
>    - Audibility is never a ground for 'not breached' under NFR-8 (S1). If the loop considers deferring a ruled fix, Seat 1's self-ABX for (a) (29-seat1 §4) is run first; its null never makes (a) "not breached" (S1).
>    - Hand-offs it convenes: Seat 1 (audibility, if deferral is weighed; what a band counted 'SE ≤ 0.5 dB only' may be claimed as (39-seat7 §8)); Seat 6 (what the canvas or the AX44 note must say at (a); no ruling is ever answered by moving the AX6 clamp, and a change to AX6 is a separate board decision: it remaps saved automation (S6)); Seat 9 (attribution for (c); which planned 12-2 presets place a source within 0.5 m of a face (S9)); Seat 4 (whether a fix adds `both_corner` and `both_wall` to 08-3 AC6's parity cases); Seat 2 (whether a post-ruling flip of k_real across 19 is enough on its own to reopen (b), 34-seat5 §7); Seats 5 and 7 (any fix's order and cost). Already answered: K8, the drag clamp (29-seat6), and R-H1, the source power near rigid faces (29-researcher-RH1).
> 2. **If a `src/sim` change follows:**
>    - The loop writes it as its own phase file (e.g. `phase-07f.md`), ordered before 08-4 and before 07d scope 8. It is an output change (golden round, §6 row; phase-07e's JSON re-pinned inside that round (S2)), fires phase-07c-2b M3-8 (rebuild and reseal both ABX scenes before 08-3 listening), and adds no scene- or placement-specific logic (NFR-8).
>    - The `/fix-plan` that creates the fix phase also adds its id to the Depends-on text of §0 row 08-4 and `phase-08-4.md` L3, to 08-3 item 15's stimulus sentence, and to phase-07d scope 8's order line (or 07d-b's §0 row) (S5, G1/G2).
>    - If a fix phase lands after 07d scope 8's re-pin is committed, its own automated acceptance criteria include that re-pin on the restore path it leaves: reference and baselines from ≥ 6 green manual runs after its last code change (no pooling of earlier runs), a `tests/golden/CHANGELOG.md` reason and a BUILD_PLAN §6 row, under phase-07d scope 8's rule, its Linux return-to-board clause included. It also prints record (h)'s 8-instance load on its own runs; an exceedance goes to the board (S5). A growth red after the fix goes to 07d's FM-GROWTH board loop; it never trims or reverts the acoustic fix (NFR-8, PRD L49) (S2).
>    - A fix that moves the handover, L_f or L_p carries in its own acceptance criteria: AX49's acceptance re-asserted; L_p at the gated geometry printed against 3.82 s; record (h) re-printed at the rated corner if L_f moved there; and the M3-8 rebuild, which names the L4 stimuli if `ax49_l4_cube`'s IR changes (S3, C3-a).
>    - The fix phase also prints the restore-work counters on the AX38 4c gate scenes before and after the fix; whether equal counters allow pooling under 07d scope 8 is Seat 5's ruling (S2).
>    - If the loop finds the fix cannot land before 08-4 or before item 15's build, that order is its own board ruling with Seats 4, 5 and 7, never a default.
>
> ## Out of scope
> Any `src/sim` edit; re-measuring beyond phase-07e's prints except where the loop asks for a named print; tuning for a scene; preset or canvas changes (any consequence goes to 11-2, 11-3 or 12-2 by ruling); moving the AX6 clamp; scheduling B15 except through the FOR MAISARA answer in scope 1; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] Phase-07e's pytest green on this branch, its JSON unchanged.
> - [ ] §0 rows 07e-b (and 07d, 08-3 and 08-4, if the ruling adds a fix phase) updated.
>
> ## Definition of done
> The ruling for (a), (b) and (c) is committed under `docs/review/phase-07e-b/`, and the interrogator returns SURVIVES. Any FOR MAISARA answer that scope 1 requires (the inside-debt route, the AX44 source-side wording) has survived the interrogator and is listed under "Decided for Maisara" (or, in a README case, Maisara has answered). If a fix is ruled, the fix phase file and its §0 row exist, and its id is in the Depends texts named in scope 2. The PR lists "Decided for Maisara". CLAUDE.md rules apply.

**Reconciliation notes (for the interrogator):**
- **(a)'s reference.** Seat 9's 38 merge is the base. From 38-seat2 come the (a2) verdict for its own placement (also 36-seat9 verdict (ii)), the E_fwd/E_rev print and the record board. From 39-seat5 comes "window k" for "gated". Seat 2's (a1) verdict (ii) and its "(a1)" outside-debt trigger are dropped (§0 Q2). Seat 2's "the deficit survives in (a2)" becomes "verdict (ii) fires for (a2)". Reason (decider): raw L − R in (a2) can be non-zero in GA itself, because the source-position factor does not cancel (F3). The engine-versus-tracer difference is the deficit.
- **Seat 5's window hand-off** ("confirm that the verdict's late window is the window k is gated on") is settled by the text itself ("the same late window the verdict compares").
- **"Until she answers"** (38-seat2) becomes "until that answer survives the interrogator (or, in a README case, until Maisara answers)". That is the README rule 2 form of an answer given for her.

### Item B: BUILD_PLAN §0
- **New rows after 07d:**
  > "| 07e | [NFR-8 placement findings: measurement (report only)](phases/phase-07e.md) | S | not started | | | Depends on 07c-2b `done`. Created 2026-11-24 by phase-07c-2b's M3 loop (decider files 17 §3, 28, 30, 33, 40: H4+G; all nine seats, files 29, 32, 34, 36, 38, 39; researcher files 29, 37; Maisara's hand-back). Lead: Seat 2 (Engine architect). Planned split: this phase measures (scopes 1–3, report, the (a0) near-corner tracer by manual job, cap 24 runner-hours); 07e-b rules. No `src/sim` change. Opens no gate by itself; runs in parallel with 08-1, 08-2 and 07d scopes 1–7. |"

  > "| 07e-b | [NFR-8 placement findings: cause ruling (report only)](phases/phase-07e-b.md) | S | not started | | | Depends on 07e `done`. Created 2026-11-24 with 07e (decider files 33, 40; 32-seat2). Lead: Seat 2 (Engine architect). 'Not decidable' opens no gate; a breach inside AX44's accepted both-near debt goes to a FOR MAISARA answer before any fix is ordered (B15). A fix, if ruled, is its own phase before 08-4 and 07d scope 8. Gates 08-4 (Depends on), 08-3 item 15's stimulus build and 07d scope 8. |"
- **Row 07d notes, append:**
  > "Scope 8 waits on 07e-b and its fix phase, if any (M3-H); if 07d reaches scope 8 first, it splits to 07d-b."
- **Row 08-3 notes, append:**
  > "Item 15's stimuli (AX47 binaural rerun) are built only after 07e-b `done` (and its fix phase, if any); checklist verdicts heard before then are recorded provisional, and the label is lifted without re-hearing if 07e-b rules no fix phase (item 7; M3-H)."
- **Row 08-4:** replace "Depends on 08-3;" with:
  > "Depends on 08-3 and 07e-b `done` (and the fix phase 07e-b's ruling names, if any, added here by id when its §0 row is created);"

### Item C: `docs/phases/phase-08-4.md` L3
Replace "Depends on: 08-3;" with:
> "Depends on: 08-3 and 07e-b `done` (and the fix phase 07e-b's ruling names, if any, added here by id when its §0 row is created);"

### Item D: `docs/phases/phase-07d.md` scope 8, prepend
> "**Order against phase-07e-b (phase-07c-2b M3-H):** this scope runs only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done` (§0). If this phase reaches scope 8 first, scope 8 splits to `phase-07d-b.md` with that dependency in its §0 row; 07d-b inherits 'lands before 08-4 freezes its goldens' (scope 6) and premise P1. Scopes 6 and 7 are not held."

### Item E: `docs/phases/phase-08-3.md`
- **Item 15:** replace L74–75 ("Whether item 15's stimulus build waits … `24-m3h-for-maisara.md`).") with:
  > "Stimuli are built only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done` (phase-07c-2b M3-H, decider files 30, 33, 40; the fix phase's id is added here when its §0 row is created)."
- **Item 7, append** (S4; the change from "07e" to "07e-b" follows S2's gate condition; last sentence S4, 34-seat4 §4):
  > "If heard before phase-07e-b is `done` (and the fix phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine before the 07e-b ruling'. A level or dryness remark on a near-face render goes to 07e/07e-b (or, once 07e-b is `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones. The label is lifted without re-hearing if 07e-b rules no fix phase."
- **Listening checklist:** after "Record the `hrtfId` … (scope 7).", add:
  > "Verdicts heard before phase-07e-b is `done` are marked 'provisional: engine before the 07e-b ruling' (item 7)."

### Item F: `docs/validation/abx-07c-2-run-sheet.md`, C-b bullet (L130–131)
Replace "goes to the board (home pending Maisara's answer on M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`) as an NFR-8 candidate." with:
> "goes to phases 07e/07e-b, or, once 07e-b is `done`, to the board as an NFR-8 candidate (M3-H, decider files 30, 33, 40; R1)."

### Item G: `docs/phases/phase-07c-2b.md`, Out of scope (L192–193)
Replace the line with:
> "- The NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): measured in phase-07e, ruled in phase-07e-b (M3-H, decider files 30, 33, 40, H4+G); this phase's PR lists them under Follow-ups."

### Item H: BUILD_PLAN §0 row 07c-2b (two edits, bookkeeping)
- **Status cell:** replace "blocked (awaiting Maisara: M3-H answer, the ABX listener and sitting dates, then the ABX itself)" with:
  > "blocked (awaiting Maisara: the ABX listener and sitting dates, then the ABX itself)"
- **Notes:** in "Waiting: M3-H (case (a), file 24);", replace "M3-H (case (a), file 24)" with:
  > "nothing on M3-H (decided for Maisara, decider files 30, 33, 40: H4+G, phases 07e/07e-b)"

### Item I: BUILD_PLAN §6, new row
> "| 2026-11-24 | Phase 07c-2b M3-H re-run after Maisara's hand-back (decider files 28, 30, 33, 40; seats files 29-seat1…9, 32-seat2/5/7/9, 34-seat4/5, 36-seat2/9, 38-seat2/9, 39-seat5/7; researcher 29-researcher-RH1, 37-researcher-a-reference; interrogator files 31, 35; corpus c1b171f): phases 07e and 07e-b created, Lead Seat 2. 07e is report-only measurement: findings, causes, a sweep with Seats 1/2/3/6/9 prints; for (a) the near-corner seeded tracer (a0) at r_d 0.05 and 0.025 m as reference, with a per-window k ≥ 684 gate, pilot sizing, sharding, a 24 runner-hour cap with an SE ≤ 0.5 dB fallback and a 36 h ceiling; the moved-listener (a2) print; for (c) a diffuse control and a tracer reference with the sphere wholly inside the room; the G3 producer-platform pytest on ≥ 1 placement naming any changed discrete field; Seat 5's red clause until 07e-b and any fix are `done`, then update-with-reason. 07e-b rules against the GA-internal level: an engine feature is a cause, never an explanation; 'not decidable' opens no gate; a breach inside AX44's accepted both-near debt goes to a separate FOR MAISARA answer (B15) before any fix is ordered, the gates holding; fix-phase ordering G1/G2, C3-a. §0 rows 07e, 07e-b (new), 07c-2b (status and notes), 07d, 08-3 and 08-4 (Depends on 07e-b, G1); phase-07d scope 8 ordered after 07e-b and its fix phase (G2; 07d-b split if reached first); phase-08-3 item 15 gate, item 7 provisional clause with its lift, checklist line; phase-08-4 L3; run sheet C-b bullet (R1); phase-07c-2b Out of scope. Decided for Maisara (FOR MAISARA M3-H-R1: a breach ruling amends AX44/B15 nothing; scheduling B15 is routed); amends nothing. | phase-07c-2b session (Claude), board loop; /fix-plan (plan-editor); `docs/review/phase-07c-2b/` |"

## 6. Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-H | H4+G with the 07e/07e-b split, Lead Seat 2. Gates on 07e-b `done` plus its fix phase (08-4, item 15 stimuli, 07d scope 8). (a)'s reference is (a0), the near-corner tracer at r_d 0.05/0.025 m, run under Seat 5's run/gate text with Seat 7's 24 h cap and 36 h ceiling; (a1) dropped; (a2) as a print. "Not decidable" opens no gate. The AX44/B15 gate is split by cause. Texts §5 A1–I | revised (to the interrogator) | 1 (S1, S2 ᶜ, S4, S5, S7, S9) | 9 (ties H3+G and H3 at 9; reversibility decides) | medium | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174; AX44 L167, B15 L408 | Kuttruff §5.7 (Table 5.2 case 4), Eq. 5.42 (§5.6) and its diffuse premise; Vorländer §11.2 Eqs. 11.5, 11.12 (via F6); tracer bias F10 (Farina 1995) | now: Seat 5 rates H3+G later 0 under the (a0) text, or a seat rates an H4+G-specific cost at 2 → H3+G. Pilot: k_pilot sets the fallback. Later: 07e-b's ruling ("no fix phase" zeroes S1/S4's conditional debt) |
| M3-H-R1 | FOR MAISARA: a breach ruling for (a) amends nothing; ordering a fix whose cause lies inside AX44's both-near debt is a separate FOR MAISARA answer in 07e-b, with the AMENDS line if it schedules B15; gates hold until it survives | for Maisara (to the interrogator) | — | — | high (plan text quoted) | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L101; AX44 L167; B15 L408 | none (product reading) | she vetoes; or 07e-b shows the deficit's cause is both inside and outside the debt in a way the mixed-cause clause does not cover |

**Challenges to settled decisions:** none.

## 7. Decided for Maisara
- **M3-H (revised 2).**
  - **What it does:** we find out whether a source pushed into a corner loses its reverb, and whether one source's reverb starts early by a wall. Two small report-only phases do this: 07e measures and 07e-b rules.
  - **The yardstick:** for the corner case, an independent particle simulation run at the exact spot. It runs as a one-off cloud job capped at 24 machine-hours. It costs none of your time.
  - **When:** the ruling comes before the binaural listening stimuli, 07d's CPU re-pin and Phase 08-4. If the yardstick cannot be formed, nothing opens until the board records the corner under the near-wall weakness you already accepted (AX44), with the on-screen note and no preset placed there.
  - **Rests on:** NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101 and L55/L174. H3 and H3+G serve the same ids, but they also hold 08-1 and 08-2 from day one, which no PRD id asks for.
  - **Who gave most:** Seat 2, which leads two phases and runs the near-corner job. Seats 5 and 7 carry a sharded cloud job and its minutes. They get back one golden round and one re-pin before anything freezes, a hard cap on compute, and an end date on the JSON's board checks.
  - Amends nothing.
- **FOR MAISARA M3-H-R1 (reading of AX44 and B15).**
  - Calling the corner case "broken" changes nothing you decided. On 2026-11-10 you made no accuracy claim there and accepted that it may read low.
  - A deficit is never called correct because the engine's own model produced it.
  - If the cause is that same accepted weakness, whether to fix it before 08-4 (which would schedule B15) is written as a separate answer for you, with the AMENDS line, and the gates wait for it. Other causes are fixed as ordinary NFR-8 breaches.
  - Rests on NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L101; AX44 L167; B15 L408. Amends nothing.

**NEEDS MAISARA:** none. One person-only action stays outside the loop: raising a GitHub spending limit to finish (a0). The texts forbid it, and Seat 7 advises against it (39-seat7 §4).

**Files read:**
- `/home/user/makroof/docs/review/phase-07c-2b/`: 33-decider-m3h-rebuttal.md, 35-interrogator-on-file33.md, 34-seat4.md, 34-seat5.md, 36-seat2.md, 36-seat9.md, 37-researcher-a-reference.md, 38-seat2.md, 38-seat9.md, 39-seat5.md, 39-seat7.md
- `/home/user/makroof/docs/BUILD_PLAN.md`: L37 (status and notes anchors), L43 ("Depends on 08-3;"), L167 (AX44), L408 (B15)
- `/home/user/makroof/docs/review/ledger.md` L2068–2082
- `/home/user/makroof/docs/board/README.md` L76–135
- `/home/user/makroof/docs/PRD.md` L40–56, L75, L99–112, L174
- `/home/user/makroof/tools/acoustics/tracer.py` L18–47
- `/home/user/makroof/tools/ci/abx_kit.py` L134–147
- `/home/user/makroof/docs/phases/phase-08-3.md` L74–75, `/home/user/makroof/docs/phases/phase-07c-2b.md` L193, `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` L131 (anchors)
- Corpus: `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` L2698, L2724, L2749; `/home/user/makroof/docs/corpus/SOURCE_COMMIT`
