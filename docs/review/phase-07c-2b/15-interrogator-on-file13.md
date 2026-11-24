
## 15: Interrogator on decider file 13 (M3-L4 band-coverage red: L4-COV option E; R1–R7)

Read-only. For the orchestrator to save as `/home/user/makroof/docs/review/phase-07c-2b/15-interrogator-on-file13.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Verdict in short:**
- **L4-COV (E) does not survive.** It is UNDERCONVENED on Seat 9 and Seat 7, and it is PRD MISREAD on its acceptance check against the B-as-second-arm option. Its arithmetic also needs corrections. One stated value is wrong: the (b) margin is 2.3 dB, not 7.6 dB, and the strongest band at the cut is 125 Hz, not 1 kHz.
- **R1–R4, R6 and R7 survive.** R5 is UNDERCONVENED on Seat 5: R5(a) settles the placement question Seat 5 was convened to rate.
- **The code has moved on since the brief.** `tests/unit/test_ax49_l4.cpp` already checks monotonicity on the measured ĝ (L125–145). It asserts 1e−9 (L159, L170/L172), and N-L1/N-L2 are inside the case (L176–190). So R5(b)–(d) are met in the tree, contrary to the brief's note. Its header comment is stale (see C9).

**Files read:**
- Review files 13, 12-seat1, 12-seat3, 12-seat8, 11, 9, 14-seat9, and 4-seat1 L90–124.
- `docs/board/README.md` (convening table; "Who answers Maisara's questions"), `.claude/agents/decider.md` §1a, §4 and §5.
- The §18 sections of seats 7 and 9.
- `docs/PRD.md` L17, L49–55, L101–112; `docs/BUILD_PLAN.md` L172 and §0.
- `tools/ci/ax49_l4.py` (L127–147, L665–711, L745–756) and `tests/unit/test_ax49_l4.cpp`.
- Kuttruff §3.8 (notation L158, L2118–2120).

### The key computation: what assert (b) actually measures

K3, file 11 L59, is per band and **relative to that band's own hold**. The code shows this at `after_cut_levels`, L753–755: `hold = mean(bb[k][s0:s1]**2)` for each band k. Assert (b), by contrast, compares absolute band levels in the same window (`band_coverage` L708 → `coverage`, which takes levels relative to the strongest band, L686–693). Both use the same window (`m["end"] + lf_aligned`, L697 and L749) and the same steady-state segment (the last 1 s of the hold).

So the cut-window level relative to the strongest steady band is K1 + K3 for each band:

| Band (Hz) | K1 + K3 = level re strongest steady band (dB) |
|---|---|
| 63 | −9.8 − 39.9 = −49.7 |
| 125 | 0 − 34.9 = **−34.9** |
| 250 | −9.3 − 31.3 = −40.6 |
| 500 | −11.6 − 29.9 = −41.5 |
| 1k | −13.3 − 27.5 = −40.8 |
| 2k | −15.8 − 36.8 = **−52.6** |
| 4k | −22.94 − 48.5 = −71.4 |

Over 63 Hz–2 kHz the strongest band is 125 Hz and the weakest is 2 kHz. The spread is **17.7 dB**, so the margin is **2.3 dB**, not 12.4 / 7.6. 1 kHz sits 5.9 dB below 125 Hz. Seat 1's 12.4 dB figure (12-seat1, E row) has the same reference error, and the decider inherited it.

### Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| L4-COV | convening | Seat 9 "not required: … makes no room-acoustic claim" | UNDERCONVENED | **Item:** README row 9, "early structure vs decay". **What the wording does:** the new null wording states S′'s per-band decay ("at 4 kHz the tail is 40 dB down at L_f"), and the Decided-for-Maisara line says "the room has already taken that band 40 dB down". **Unanswered hand-off:** Seat 1 §7 hands off to Seat 9 explicitly ("whether the null wording needs the 4 kHz depth sentence"). **Seat 9's role:** it owns the L4 label (file 9 (iv)), and it gave the S-W record line in file 9. | UNDERCONVENED | Q2 |
| L4-COV | convening | Seat 7 "not required: … cannot change the winner" | UNDERCONVENED | **Item:** README row 7, "what one founder can sustain; schedule and complexity cost of an option". **The surviving option that touches it:** B-second adds about 0.75 h of her listening; the decider states this itself. **The rule:** README, "a seat is convened when the matter touches any item in its row". Being non-decisive is not a reason not to convene. **It becomes decisive:** Seat 7's cost is needed for the PRD question in row PRD-1. | UNDERCONVENED | Q2 |
| L4-COV | convening | Seats 2, 4, 6 not required | faithful | S′ is unchanged and all of Seat 2's asserts pass (file 11). The chain stays omni diotic. No control is touched. | — | — |
| L4-COV | map | A, B, C rows; Seat 1's D and E rows; Seat 3's D row | faithful | Each cell matches the seat's own words: 12-seat1 §2–4; 12-seat3 §3–4 ("C 0", "B 1", "A 2"; later "C 1", "B 1", "A 1"); 12-seat8 §3–4 ("C: 0", "A: 1", "B: 2"; later 1/1/2). The sums are recomputed: A 8, B 6, C 4, D 5, E 4. | — | — |
| L4-COV | map | E: S3 0/1 and S8 0/1, read from conditions | faithful, but decisive and incomplete | **Seat 8:** "C: no condition from me … Seat 1's call", so 0/1 follows. **Seat 3:** its C conditions (justify by the depth table; record before any scored trial) are met by E. But Seat 1's hand-off to Seat 3 is unanswered ("confirm the cut-window measure in E is computable on the partition grid"). **Why it matters:** the decider says a +1 on either cell flips the winner to C. | stands; ask | Q4 |
| L4-COV | map | D: S8 1/1, read from conditions | faithful | Seat 8's A reason applies to D's 10 kHz extension ("a little brighter than typical"), and its C later reason (the beta report) applies too. Not decisive: at S8 0/1, D would tie at 4. | — | — |
| L4-COV | debt | rows for S1, S3, S8 (each later 1 on E) | faithful | All three later-1 cells have rows. The S3 row matches "Undo cost: a print". The phases named exist: `phase-07d.md`, and beta in `phase-13-5.md`. | — | — |
| L4-COV | ordering | steps 1–5 | CORRECT | **Step 3:** A (S1/S3 at 2) and B (S8 at 2) are out; max 1 is the floor (Seat 1: "C and E, from 1 to 0: none available"). **Step 5:** C 4 = E 4 < D 5 < B-second ≥ 6; B-second's sum rests on Seat 7 being ≥ 0. | — | — |
| L4-COV | ordering | step 6: "C cannot gain a pre-registered exposure assert after scores … only by a re-sitting" | WRONG (hidden premise, from the code and the spec) | **The values exist under C too:** the per-band cut-window levels are a deterministic property of the sealed stimulus, and they are already printed in the manifest under C (Seat 1's spec, 4-seat1 L113–114; `after_cut_levels` L745–756, printed at L1039). With K1, they give (b) exactly. **Reversibility is symmetric:** before the seal, C can gain the assert as cheaply as E can drop it. So step 6 is a tie, and the winner is unchanged only as the decider's pick among tied options. | SURVIVES WITH CORRECTIONS (ordering) | Q4 |
| L4-COV | claim 13-L1 (K2) | depth at L_f = 60·(L_f − t_mix,e)/T60 | CORRECT | **Formula:** Kuttruff §3.8 (Eq. 3.70 by its notation table): T is the time for a 60 dB decay. **Working:** 2.496 s × 60 = 149.76; /8 = 18.72; /6.457 = 23.19; /3.731 = 40.14; /1.427 = 104.95 (the builder's 104.93 differs only by T60 rounding); 40.14 − 18.72 = 21.42. **Note:** 18.72 = 60 × 0.312 holds exactly by AX49's L_f rule, so R7's "+0.02 dB" is structural, not a measured margin. | — | — |
| L4-COV | claim 13-L2 (b) | "(b): spread 12.4 dB, a margin of 7.6 dB" | IMPRECISE (wrong reference) | K3 is relative to each band's own hold (L753–755). The quantity (b) asserts is K1 + K3: strongest 125 Hz (−34.9), weakest 2 kHz (−52.6), spread 17.7 dB, margin 2.3 dB. It still passes. **Restatement:** "(b): strongest band 125 Hz, weakest 2 kHz at −17.7 dB, margin 2.3 dB (file 11 K1 + K3, same windows)." | correction | Q3 |
| L4-COV | claim 13-L2 (a) | weakest band 2 kHz at −15.8 dB, margin 4.2 dB | CORRECT | File 11 L20. | — | — |
| L4-COV | strongest objection | "(b) puts a floor on the exposure at 1–2 kHz, and at the cut 1 kHz is the strongest band" | WRONG | **The levels:** at the cut, 125 Hz is the strongest band; 1 kHz is 5.9 dB below it and 2 kHz 17.7 dB below. **What (b) allows:** 1–2 kHz may sit up to 20 dB below 125 Hz, so (b) does not answer K5 (Seat 1: B gives 9–12 dB more exposure at 1–2 kHz). **What survives:** the objection is still met by the ordering alone (B is out on Seat 8's 2/2). **Restatement:** "(b) bounds 1–2 kHz to within 20 dB of 125 Hz at the cut (today 2 kHz −17.7 dB); B's exclusion is Seat 8's own 2." | correction | Q3 |
| L4-COV | claim, loosening reason (i) | "A passing stimulus existed (B)" | IMPRECISE | B was never built. Its pass is a prediction: Seat 1 "−8 to −13 dB", Seat 3 "about −9 dB", Seat 8 "about −8 dB", all [Inferred]. **Restatement:** "a stimulus predicted to pass (B; Seats 1, 3, 8, [Inferred], not built) was declined on Seat 8's 2/2." | correction | — |
| L4-COV | claim, loosening reason (ii) | "the new scope rests on K2 … not on the red's margin" | IMPRECISE (hidden premise) | **K2 alone does not set the boundary.** K2 is chord-independent, but it only ranks the bands; no depth threshold putting 2 kHz (23.19) in and 4 kHz (40.14) out was stated before the red. **What (b) actually measures** is chord × depth, which is chord-dependent. **The premise that would make the scope "follow"** is that a band about 21 dB deeper adds nothing to detection. That is Seat 1's [Hyp], which 13-L4 says is not relied on. **Restatement:** "The scope is a judgement on the depth table (Seat 3's condition), made after the red; no threshold was fixed in advance; the null claims nothing at 4 kHz." | correction | — |
| L4-COV | the loosening argument against the rules | "never loosen to pass" | holds as restated; one citation INCONSISTENT | **Where the rule actually lives:** CLAUDE.md contains no "loosen" (grep). The rule is in decider.md §5, "What you never do" ("tolerances follow from the requirement"), and in file 9's digest. CLAUDE.md's golden rule is about golden files; its procedure (intended, explained, a §6 row) is mirrored here. **Why it is not the forbidden kind:** the 20 dB tolerance is unchanged, the scope change comes from the clause's author ("my own error", 12-seat1 §1), and the null is narrowed to the asserted bands, before any scored trial. That is a recorded change after a red, not a quiet loosening. **The inconsistency:** `test_ax49_l4.cpp` L10 quotes 'CLAUDE.md "never loosen"', which is not in CLAUDE.md. | correction (citation) | — |
| L4-COV | claim 13-L4 vs Decided-for-Maisara | "4 kHz is dropped … because at the cut the room has already taken that band 40 dB down, whatever chord is played" | INCONSISTENT | **The conflict:** the line gives a causal reason for dropping 4 kHz, which is the [Hyp] that 13-L4 says is "deliberately not relied on". **The figures:** 40 dB is the decay from the tail's own onset. In absolute cut-window terms, 4 kHz sits 36.5 dB below 125 Hz under this chord. **Restatement:** "4 kHz is no longer asserted, and the null claims nothing there; by the cut, that band's tail has decayed 40 dB from its onset." | correction | — |
| L4-COV | claim K4 (A alone about −22.3 dB) | (1/2828 − 1/5000)/(1/2828 − 1/5657) | CORRECT, not load-bearing | 1.5361e−4 / 1.7684e−4 = 0.8686, which is −0.61 dB; −22.94 + 0.61 = −22.33. | — | — |
| L4-COV | PRD proxy (acceptance check) | B-second line: "NFR-1 plus brighter evidence, at more hours (L55 does not bound hours). No PRD id ranks it above E." | PRD MISREAD | **The decider's own line points to B-second.** By that line, B-second serves NFR-1 (L105, "pass listening tests") more than E and strains nothing the PRD bounds. The pad arm still runs, so L17 is kept, and L55 is "no fixed deadline". **L101 is left out:** "Accuracy is the top priority". The digest narrows this to L49 only. **The precedent:** file 9 M3-2 chose the option that "serves NFR-1 most". **What is missing:** no `FOR MAISARA` names E against B-second. The README requires one when a PRD goal points to another surviving option, or a reading showing why it does not. | PRD MISREAD | Q1 |
| L4-COV | PRD proxy | the other lines (A, B, C, D) and "Amends nothing" | faithful | A is red. B strains L17 (Seat 8). C and D: no PRD id distinguishes them from E. No recorded decision of hers is touched. | — | — |
| S3-cond | convening | R5(a) "the asserting case is non-hidden `[ax49-l4]`" and R5(e) | UNDERCONVENED | **What R5(a) does:** it rules on the matter Seat 5 was convened for, "(a) in the default set … (b) Release-only, run as the `[benchmark]` cases are" (hidden), before Seat 5 has answered. **The tree:** no 12/14-seat5 file exists, and the code already has the case non-hidden (L161–163). **Seat 7's stake:** R5(e) makes a three-platform gate a precondition of the seal, which is the stall risk behind Seat 7's file-9 now-1. | UNDERCONVENED (R5(a), (e)) | Q5 |
| S3-cond | map | R1, R2, R3, R4, R5(b), R5(d), R6, R7 | faithful | **R1–R4, R6, R7:** each matches 12-seat3 §6 (items 1, 4, 6, 7). **R3's 2⁻¹ pre-scale:** 10^(3.05/20) = 1.4207; ×0.5 = 0.710 < 1. Power-of-two scaling is exact in IEEE arithmetic barring subnormals. | SURVIVES | — |
| S3-cond | map | R5(c) "monotonicity on the measured gain ĝ" | IMPRECISE (attribution) | This is not in Seat 3's words. It is the decider's own reading of the code (a builder proposal, file 11 item 7). **Label it** "decider, from the code". It is already met at L125–145. | correction | — |
| S3-cond | code fact | `test_ax49_l4.cpp` header L4–6 and L10 | INCONSISTENT (documentation) | **L4–6** still say "asserted against the bound the measurement supports", while L159 asserts 1e−9 as R5(b) requires. **L10** cites a CLAUDE.md phrase that does not exist. | correction (builder) | — |

### Outcomes

- **L4-COV (E):** **does not survive**. It is UNDERCONVENED (Seat 9 on the null wording; Seat 7 on B-second's hours) and PRD MISREAD (no `FOR MAISARA` on E versus B-second under NFR-1 L105 and L101).
  - When it is re-run, these corrections apply whatever the winner:
    - (b)'s values (17.7 dB spread, margin 2.3 dB, strongest band 125 Hz);
    - the strongest-objection sentence;
    - loosening reasons (i) and (ii);
    - the Decided-for-Maisara line;
    - step 6 restated as a tie on reversibility.
  - Note the 2.3 dB (b) margin sits on the 125 Hz band, which Seat 3 calls fragile ("one realisation").
- **S3-cond R1–R7:**
  - **R1–R4, R6, R7:** SURVIVE.
  - **R5(b)–(d):** SURVIVE WITH CORRECTIONS (attribute R5(c) to the decider; fix the stale header L4–6, L10). The tree already meets them.
  - **R5(a) and (e):** UNDERCONVENED on Seat 5. The placement waits for Seat 5's answer.

### Questions for the rebuttal round (most consequential first)

1. Your B-second line says "NFR-1 plus brighter evidence", and it notes L55 does not bound hours. Which PRD passage makes E preferable to B-second? If there is none, write the `FOR MAISARA` that names both and shows each against L105, L101, L17 and L55, with Seat 7's hours.
2. Will you convene Seat 9 on the null wording and the 4 kHz depth sentence (Seat 1 §7's hand-off), and Seat 7 on B-second's 0.75 h and R5(e)'s seal precondition?
3. K3 is per band relative to its own hold (`ax49_l4.py` L753–755), and (b) compares absolute levels (L708). Do you accept (b) = 17.7 dB spread, weakest 2 kHz, strongest 125 Hz, margin 2.3 dB, and withdraw "at the cut 1 kHz is the strongest band"? Does your answer to K5 still hold without it?
4. Under C, the per-band cut-window levels are printed in the sealed manifest (4-seat1 L113–114; L745–756). What makes C irreversible after scores? If nothing does, step 6 is a tie: say on what ground E is named. Separately, will you ask Seat 3 for its E cell (Seat 1's partition-grid hand-off), given that a +1 flips the winner?
5. R5(a) fixes "non-hidden" before Seat 5 has rated (a) against (b). Will you hold R5(a) and (e) until Seat 5 answers?

**Files:**
- /home/user/makroof/docs/review/phase-07c-2b/13-decider-l4-coverage.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md, 12-seat3.md, 12-seat8.md, 11-builder-l4-kit.md, 9-decider-m3-r3.md, 4-seat1.md, 14-seat9.md
- /home/user/makroof/tools/ci/ax49_l4.py (L136–144, L685–711, L745–756)
- /home/user/makroof/tests/unit/test_ax49_l4.cpp (L4–10, L125–145, L159–190)
- /home/user/makroof/docs/board/README.md, /home/user/makroof/.claude/agents/decider.md (§4, §5)
- /home/user/makroof/docs/PRD.md (L17, L55, L101, L105), /home/user/makroof/docs/BUILD_PLAN.md (L172)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L158, L2118–2120)
