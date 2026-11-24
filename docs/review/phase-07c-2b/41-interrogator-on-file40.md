
# 41: Interrogator on file 40 (M3-H second rebuttal, H4+G with 07e/07e-b)

Save as `/home/user/makroof/docs/review/phase-07c-2b/41-interrogator-on-file40.md`. I changed no files.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

## Verdict: the decision does not survive as written

**M3-H fails on three codes: TENSION MISREAD, FALLS (two 07e-b text clauses) and PRD MISREAD.** FOR MAISARA M3-H-R1 fails on PRD MISREAD.

**What survives.** File 35's Q3, Q4 and Q5 and every correction they required were answered faithfully:
- **Seat 4:** the ABX-slip premise, the step 6 restatement, the S4 debt row, "07e-b rules no fix phase", and its optional clause in Item E with attribution.
- **Seat 5:** the post-end-date flip residual is in Seat 5's own words, the residual is carried open, and ‡ is gone. Refinement bullet 1 is adopted and attributed; bullet 2 is declined with "my 1 stands as rated".
- **Other corrections:** K14 now says "radius", and K16 is restated against the full L167 paragraph. "Names the receiver side only" is gone from every text, and K18–K19 are added.

On Q1 and Q2, these hold:
- (a0) is the reference.
- (a1) is dropped. Seat 9 itself rates keeping it 2/2 (38-seat9 §3–4).
- "Not decidable" now has a gate consequence.
- The gate is split by cause.
- Seat 2's hand-off to Seat 9 is answered (36-seat9 §2(1); 38-seat9 §2).

M3-H-R1 belongs under "Decided for Maisara", not NEEDS MAISARA. Reading her recorded decision is a rule-1 item (README L87–89). The answer changes no PRD text and overrides no `3`. It fails only on its reading of AX44 (defect 4 below).

**Four defects:**

1. **TENSION MISREAD: S5 on H3+G, later column (marked ʳ). This cell decides the winner.**
   - Seat 5's last rating of that cell in its own words is **0**: "H3+G: 0, confirmed. The prints and the clause are the same under H3+G" (32-seat5 §4).
   - Seat 5 ties H4+G's later 1 to an H4+G-specific cost: "H4+G's later 1 arises only if a fix is ruled" (29-seat5 §2).
   - 39-seat5 §5 rates H4+G only. That cell was already 1, so it does not show that the pin rerun alone is worth 1 under H3+G.
   - Reading 1 here re-rates the seat (decider.md §5, "What you never do").
   - The decider's own words: "If Seat 5 … rates H3+G later 0 under the (a0) text, H3+G sums 8 and wins."
   - The S9, S2 and S7 ʳ reads are acceptable. Each seat said in its own words that its row does not separate the homes (32-seat9 §3, 29-seat9 §2, 29-seat2, 32-seat7 §3).

2. **FALLS (CONDITIONS VIOLATED): the SE ≤ 0.5 dB fallback band counts for "not breached".**
   - Working (Vorländer §11.2.5 Eq. 11.9 in the tracer.py L28 form): at window k = 76, σ = 4.34/√76 = 0.498 dB, so 3σ = 1.49 dB. That exceeds the 1 dB verdict threshold.
   - The two-radius agreement test then resolves only 3·√2·0.498 = 2.11 dB, against 0.70 dB at k ≥ 684.
   - So a "within 1 dB" result on such a band cannot establish "not breached". The averaging-bias check (K22, F10) is also blind below about 2 dB. The text's own band rule (07e-b scope 1: uncertainty "under 0.5 dB", with 3σ as the uncertainty measure, (c)) is violated for that verdict.
   - Seat 2's "stays decidable" (36-seat2 §2) holds only when the engine-to-tracer difference is large. If the tracer also reads about −6 dB, the difference is near 0, and that is exactly where the band fails.
   - The case is realistic. Seat 7's worst case (about 78 h, 39-seat7 §3) puts the bands on the fallback.
   - K24's "not load-bearing" rests on this outcome being valid in both directions.
   - What a fallback band may be claimed as is deferred to 07e-b (the Seat 7 → Seat 1 hand-off), which means after the results are seen.

3. **FALLS (INCONSISTENT): 07e-b, "not decidable" step 1, "(a0) at more particles, under B11's doubling rule".**
   - B11 (BUILD_PLAN L404; tracer.py L45, L243–261) doubles N only "up to 16·N₀", about 24.4 M. Its trigger is per bin: fewer than 3 bins with k ≥ 684.
   - B11 also says N "(beyond the pre-stated doubling rule) … never changed after results are seen". That clause was accepted by Maisara on 2026-11-05.
   - (a0) is sized at ≥ 152 M (F8) by a per-window pilot rule, and "Per-bin k is not used for (a0)".
   - So the step invokes a rule that cannot add particles to (a0). If it is read as allowing a post-result increase, it contradicts B11's clause.
   - The text comes from Seats 2 and 9 (36-seat2, 38-seat2) and was adopted by the decider.

4. **PRD MISREAD (M3-H-R1 and the 07e-b breach text): AX44's reversal threshold τ is left out.**
   - AX44's reversal is "the near-corner reference contradicts NW-4C by more than τ" (L167). τ = 0.25 dB per case and band (AX42, L165). This is part of the row she accepted (P05B2-M-02).
   - File 40 says "A breach against (a0) is the AX44 reversal firing", and M3-H-R1 says the reversal "asks for exactly that check". But the breach threshold is 1 dB.
   - A counted band that differs by more than τ but no more than 1 dB fires her reversal clause. Under 07e-b it rules "not breached": the gates open and nothing about AX44 is recorded.
   - This is a recorded decision of hers that bears on the point and is left out.

**Round count.** By decider.md §6 (L289–293), this is the third round (31, 35, 41). Whatever stays contested after the decider's reply is ruled as `FOR MAISARA` from the PRD and checked once. If that check fails, it goes to her as NEEDS MAISARA case (a) (README item 3).

## Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| M3-H | convening | nine seats (file 28/29); follow-ups to S2, S9 (36, 38), S5, S7 (39), S4, S5 (34) | faithful | 29-seat1…9; new texts heard by the seats whose rows they touch (cost: S5, S7; reference: S2, S9) | — | — |
| M3-H | Q1 (file 35) | K16 restated; "receiver side only" removed; split by cause; M3-H-R1 written; AMENDS route for the inside-debt case | faithful | L167 re-read; 36-seat2 §3; 36-seat9 §2(4); 38-seat2 §2 | — (but see τ below) | — |
| M3-H | Q2 | (a0) reference; (a1) dropped; "not decidable" opens no gate; S9 hand-off answered | faithful | 36-seat2 §2; 38-seat9 §2–4 ("(a1) kept … 2"); 37 F3, F5, verdict NOT READY on "0 dB" | — | — |
| M3-H | Q3 | Seat 4's slip premise, step 6, S4 row, "07e-b rules no fix phase", Item E clause | faithful | 34-seat4 §2–4 | — | — |
| M3-H | Q4 | S5 residual row; ‡ removed; "end date" not its repayment | faithful | 34-seat5 §4 ("recorded but no gate stops it"; "one board look plus possibly a fix phase") | — | — |
| M3-H | Q5 | bullet 1 adopted (S5); bullet 2 declined; S7 later is its own rating | faithful | 34-seat5 §6; 39-seat7 §5 | — | — |
| M3-H | map S5, H3+G later (ʳ) | read as 1 from "a pin bump means rerunning (a0)" | **TENSION MISREAD** (an unrated cell is filled against the seat's last word) | 32-seat5 §4: H3+G later "0, confirmed", with common prints and clause; 29-seat5 §2: H4+G's later 1 "arises only if a fix is ruled"; 39-seat5 rates H4+G only | Decisive. At 0, H3+G sums 1+2+0+1+1+0+2+0+1 = 8 and wins at step 5 | Q1 |
| M3-H | map S5/S7/S2/S9 H4+G cells | 1/1, 1/1, 1/1 ᶜ, 0/1 | faithful | 39-seat5 §4–5; 39-seat7 §5; 36-seat2 §4, §6 (later 1 if "(a) keeps no reference" and "no gate consequence" are both avoided, and they are); 38-seat9 §3–4 | — | — |
| M3-H | map S9 marking | "its own rating" | IMPRECISE | 38-seat9 rated its own merge, in which the moved listener is "never references". The adopted text makes (a2) a reference "for its own placement" (verdict (ii)) and adds the mixed-cause clause and Seats 6/9. 0/1 follows from its conditions (§6: drop (a1) → 0 now; later 1 → 0 only with B15) | SURVIVES WITH CORRECTIONS: mark ᶜ | — |
| M3-H | map S9, H3 (ʳ) | cites 32-seat9 §3, which covers H3+G only | IMPRECISE (citation) | 29-seat9 §2: "My row cannot separate these five" (includes H3) | correction: cite 29-seat9 §2 | — |
| M3-H | map, (a1) row | sum 11 | WRONG (arithmetic) | 1+2+0+1+2+0+2+0+4 = 12 | none: dropped at max 2 either way | — |
| M3-H | ordering | max 1: H3, H3+G, H4+G; sums 9/9/9; reversibility for H4+G | correct as computed on the cells as written | recomputed: H4+G 1+2+0+1+2+0+2+0+1 = 9; H3+G 9; H3 9 | depends on the S5 cell (above) | Q1 |
| M3-H | debt register | six rows for every later ≥ 1 (S1, S2, S4, S5, S7, S9) | complete | 34-seat4; 34-seat5; 38-seat2 §5; 38-seat9 §4; 39-seat5 §5; 39-seat7 §5 | — | — |
| M3-H | debt S9 "a parameter change" | undo cost of "(a) flagged rather than fixed" | hidden premise, IMPRECISE | Repaying the flag is B15, "a measured both-near fallback with p95 ≤ 1 dB" (L408), and U plus the five flags of every valid fixture are pinned in the D5 golden (L167). So it is a `src/sim` change plus a golden round, not a parameter change | SURVIVES WITH CORRECTIONS: state the plan's undo cost beside Seat 9's words | Q5 |
| M3-H | D-L8 / K22 | sphere wholly inside at r_d 0.05 and 0.025 m; crossing bias −1.88 dB | CORRECT | tracer.py L21, L42; cap h = 0.4: V_cap = π·0.16·1.1/3 = 0.1843; 1 − 0.1843/0.5236 = 0.648 → −1.88 dB | — | — |
| M3-H | K23 / D-L7 | k ∝ π r_d² N; ×100, ×400; k_eff ≈ 8/9 | CORRECT | Vorländer §11.2.2 Eq. 11.5, §11.2.5 Eq. 11.12; E[ℓ]² / E[ℓ²] = (16/9) r² / 2r² = 8/9 | — | — |
| M3-H | K24 | ×6.6 at 0.165 s, ×77 at 0.38 s | CORRECT (derived; Vorländer §11.2.5 Eqs. 11.25–11.27; Kuttruff Table 5.2 case 4, T 1.21 s) | e^(13.8·0.165/1.21) = 6.57; e^(13.8·0.38/1.21) = 76.3 | "not load-bearing" depends on the fallback row below | Q2 |
| M3-H | K25, K26, D-L10 | 3.1 µs per particle; k ≥ 76 | CORRECT | 49 s / 16 M = 3.06 µs (05h file 14 L31–39); (4.34/0.5)² = 75.3 | — | — |
| M3-H | D-L9 / K20 | Eq. 5.42 is diffuse-only; layout 4 is non-diffuse; ᾱ = 0.28 | CORRECT | Kuttruff §5.6 Eq. 5.42 and the caveat after Eq. 5.48; §5.7 example "severe deviation from diffuse conditions"; Table 5.2 case 4; (600 + 1600·0.01)/2200 = 0.28 | — | — |
| M3-H | K21 | "0 dB is not GA's own L − R expectation … known" | IMPRECISE (overstated) | 37 F3 is a derivation (medium) and F5 is "derived, not established" (low). What is known is that no source supports 0 dB | SURVIVES WITH CORRECTIONS: "not established; derived evidence (F3, F5) suggests not". The drop of (a1) still follows from Seat 9's 2/2 | — |
| M3-H | 07e-b fallback clause | an "SE ≤ 0.5 dB only" band counts for every verdict, "not breached" included | **CONDITIONS VIOLATED** | Vorländer §11.2.5 Eq. 11.9: σ = 4.34/√76 = 0.498 dB, 3σ = 1.49 dB > 1 dB threshold; two-radius combined 3σ = 2.11 dB (0.70 dB at k 684). The text's own rule needs uncertainty under 0.5 dB | **FALLS** (Item A1 cap clause and Item A2 scope 1 fallback; home unaffected) | Q2 |
| M3-H | 07e-b "not decidable" step 1 | "(a0) at more particles, under B11's doubling rule" | **INCONSISTENT** | B11 L404: up to 16·N₀ (about 24.4 M), per-bin trigger, N "never changed after results are seen" beyond the pre-stated rule; tracer.py L45, L261. (a0) is ≥ 152 M (F8), per window | **FALLS** (Item A2 step 1 text; home unaffected) | Q4 |
| M3-H | 07e (a0) cap arithmetic | 24 h cap; worst case about 78 h; fallback about 8.7 h | CORRECT (seat's own cost, [Hyp] mid case) | 59 M × 154 × 3.1 µs = 7.8 h; ×4 = 31 h; 2·7.8 + 2·31 = 77.6 h; /9 = 8.6 h | — | — |
| M3-H | Item A1 sharded merge | "bit-identical to an unsharded run" | SOFTWARE (not rated) | Note for the builder: tracer.py L228–230 accumulates chunk by chunk, so a merge of shard totals changes the floating-point summation order unless it is reproduced | — | — |
| M3-H | record path (Seat 6 domain) | "no fixture or Phase 12 preset default within 0.70 m of a layout-4/5-type corner (AX44 Seat 6 (ii))" | IMPRECISE (attribution) | L167: Seat 6 (ii) says no default placement "may raise U", a U rule, not a distance rule. Seat 6 has not rated the stricter form. It binds only through a later board that includes Seat 6 | correction: attribute to S9 (36-seat9 §2(3)) and mark it stricter than AX44 Seat 6 (ii) | — |
| M3-H | anchors | L37 status and notes; L43 and phase-08-4 L3 "Depends on: 08-3;"; phase-08-3 L74–75; phase-07c-2b L192–193; run sheet L130–131 | CORRECT (all exist as quoted) | read | — | — |
| M3-H | K19 | positions | CORRECT | abx_kit.py L135–143 | — | — |
| M3-H | PRD proxy (acceptance) | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174 against H3, H3+G, H4+G | the ids say what is claimed; each survivor is shown | PRD L49, L55, L75, L101, L105, L112, L174 | — | — |
| M3-H-R1 | PRD proxy | "A breach against (a0) is the AX44 reversal firing"; "its reversal clause asks for exactly that check" | **PRD MISREAD** (a recorded decision bearing on the point is left out) | L167 reversal: "contradicts NW-4C by more than τ"; AX42 L165: τ = 0.25 dB per case and band. A band at τ < d ≤ 1 dB fires her clause while 07e-b rules "not breached" and records nothing on AX44 | PRD MISREAD: re-answer | Q3 |
| M3-H-R1 | case routing | Decided for Maisara vs NEEDS MAISARA | belongs in "Decided for Maisara" | README L87–89 (reading or amending a recorded decision is rule 1); no PRD change, no `3` overridden | — | — |
| M3-H-R1 | other readings | L167 disclaimer, debt, B15 "none scheduled", ledger L2070; four options shown against the ids | faithful | BUILD_PLAN L167, L408; ledger L2070–2077 | — | — |
| M3-H | strongest objection | the S5 H3+G read | correctly identified, but held on a read the seat never gave | above | becomes TENSION MISREAD; the fallback (defect 2) is the stronger second objection | Q1, Q2 |

## Questions for the decider (most consequential first)

1. **S5, H3+G later.** Seat 5 gave 0 (32-seat5 §4) and tied H4+G's later 1 to a ruled fix (29-seat5 §2). Will you put the H3+G later cell under the (a0) text to Seat 5, and keep the cell at its own last word until it answers? If it answers 0, H3+G sums 8: does the home then change at step 5?
2. **What a fallback band supports.** At window k 76, 3σ is 1.49 dB per radius and 2.11 dB for the two-radius check. Does a "within 1 dB" on such a band count as "not breached" for (a)? If it does not, what does it count as? That answer must be fixed in the 07e/07e-b text before (a0) runs, not left to 07e-b's Seat 1 hand-off.
3. **AX44's reversal at τ = 0.25 dB (AX42 L165).** Take a counted band where the engine at (a) and (a0) differ by more than τ but by 1 dB or less. What does 07e-b record about AX44's reversal, and how does M3-H-R1 then read her decision? Quote L165 and L167.
4. **"B11's doubling rule" in step 1.** B11 caps at 16·N₀ (about 24.4 M), triggers per bin, and bars any post-result change of N beyond its pre-stated rule (L404). (a0) is sized at ≥ 152 M per window. Which rule does step 1 actually invoke? Was it stated before (a0)'s results?
5. **Seat 9's undo cost.** Seat 9 gives "a parameter change" (38-seat9 §4). Will the S9 debt row also carry the plan's cost of repaying the flag? That cost is B15's measured fallback (L408) plus the D5 golden that pins U for every fixture (L167).

**Required corrections (not separate questions):**
- Mark S9's cell ᶜ, and cite 29-seat9 §2 for the S9 H3 cell.
- The (a1) row sums to 12, not 11.
- Restate K21 as "not established".
- Attribute the record path's preset clause to S9 and mark it stricter than AX44 Seat 6 (ii).

## Files read
- `/home/user/makroof/docs/review/phase-07c-2b/`: 40-decider-m3h-rebuttal2.md, 35-interrogator-on-file33.md, 34-seat4.md, 34-seat5.md, 36-seat2.md, 36-seat9.md, 37-researcher-a-reference.md, 38-seat2.md, 38-seat9.md, 39-seat5.md, 39-seat7.md, 32-seat5.md, 32-seat9.md, 29-seat5.md (L1–45), 29-seat* (H3 mentions), 33-decider-m3h-rebuttal.md (map rows)
- `/home/user/makroof/docs/review/phase-05h/14-orchestrator-M2-near-corner.md` L25–40
- `/home/user/makroof/docs/BUILD_PLAN.md` L37, L43 (anchors), L163–172 (AX40–AX49 heads; AX42 τ L165), L167 (AX44), L404 (B11), L408 (B15)
- `/home/user/makroof/docs/review/ledger.md` L2070–2077
- `/home/user/makroof/docs/board/README.md` L76–137; `/home/user/makroof/.claude/agents/decider.md` L215–299
- `/home/user/makroof/docs/PRD.md` L49–55, L74–76, L101–112, L174
- `/home/user/makroof/tools/acoustics/tracer.py` L1–104, L200–274; `/home/user/makroof/tools/ci/abx_kit.py` L132–147
- `/home/user/makroof/docs/phases/phase-08-3.md` L70–77, `phase-08-4.md` L1–4, `phase-07c-2b.md` L190–194, `/home/user/makroof/docs/validation/abx-07c-2-run-sheet.md` L128–132
- Corpus: `/home/user/makroof/docs/corpus/kuttruff-room-acoustics.md` (§5.6 L2694–2725; §5.7 L2727–2753; Table 5.2 L2782–2793), `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (§11.2.2 Eq. 11.5; §11.2.5 Eqs. 11.8–11.12), `/home/user/makroof/docs/corpus/SOURCE_COMMIT`
