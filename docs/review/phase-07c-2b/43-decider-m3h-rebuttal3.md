# 43: Decider on M3-H, third rebuttal (answer to interrogator file 41). Phase 07c-2b

I changed no files. The orchestrator saves this as `/home/user/makroof/docs/review/phase-07c-2b/43-decider-m3h-rebuttal3.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. The PRD digest is unchanged from file 28 L10–21.

**State: REVISED. The home stays H4+G.** This is the third round (files 31, 35, 41). Whatever is still contested after the interrogator reads this file is ruled FOR MAISARA from the PRD and checked once (decider.md §6).

What changed:
- **Seat 5 rated H3+G later 1 itself** (42-seat5 §3–4). The tie at 9 now rests on the seats' own cells, and reversibility still picks H4+G.
- **The fallback clause is replaced.** A band on the SE fallback can now support only a breach. In every other case it is "not decidable" (Seats 1, 2, 9).
- **AX44's τ is now recorded separately from NFR-8.** Each emitter and each counted band gets one of three states (Seats 2, 9, 1).
- **"B11's doubling rule" is gone.** In its place, 07e has one top-up of N, stated before dispatch and triggered only by realised k (Seat 5). 07e-b runs no further particles (Seats 5, 2).
- **One new finding of mine, which I raise rather than leave for you to find.** All four (a0) runs use the same TRACER_SEED. So the two radii share particles, and an independent-errors (root-sum-square) "combined 3σ" makes the two-radius agreement test too lenient. A pre-stated print fixes this (§2.4).

---

## 0. Answers to file 41

| item | verdict in file 41 | answer | state |
|---|---|---|---|
| **Q1** S5, H3+G later | TENSION MISREAD | **Put to Seat 5, which answered in its own words:** "**Later 1**, revised from 0 … I gave 0 in 32-seat5 §4 … before the (a0) text existed (39-seat5)." The three costs that carry its 1 (a standing manual job rerun on each pin bump, the 24 h cap with its fallback, the post-end-date flip residual) "are the same under every home". And "my H4+G later 1 rests on nothing that H3+G does not also carry" (42-seat5 §3–4). The cell is now Seat 5's own rating, not a reading. H3+G sums 9, not 8. The home does not change at step 5. Step 6 decides, as before (§3). | corrected (by the seat's own rating) |
| **Q2** what a fallback band supports | FALLS (CONDITIONS VIOLATED) | **Accepted.** A band at window k 76 has 3σ = 1.49 dB per radius (2.11 dB for a two-quantity difference), and that exceeds the 1 dB threshold. Such a band supports **only "breached"**, at both radii with the same sign, when \|d\| > 1 dB + 3σ_d. Otherwise it is **"not decidable"** for that band and takes the not-decidable route, so it opens no gate. It is **never "not breached"**. "Not breached" for (a) is stated only over bands gated at k ≥ 684 at both radii. The text is fixed in 07e and 07e-b before (a0) is dispatched (§2.1; Item A1 cap clause; Item A2 verdict (iv)). Seat 1's hand-off on what a fallback band may be claimed as is answered by the text itself (42-seat9 §2). Seat 2's narrowed question (may a fallback-established breach be quoted outside the ruling?) stays with Seat 1. | revised |
| **Q3** AX44's τ | PRD MISREAD | **Accepted.** The quotes: L165, "τ = **0.25 dB** per case and band, C++ E_target against the reference (`ref_hybrid` at its finest certified rung), with the reference's ℓ_ref inside τ". L167, the reversal: "the near-corner reference contradicts NW-4C by more than τ". 07e-b now records the reversal **per emitter and per counted band, never on L − R**, in one of three states: **fired** (\|d\| > τ + 3σ_d at both radii, same sign: 0.75 dB at k 684, 1.74 dB at k 76), **not resolved at τ**, or **within τ, not testable**. "Within τ" is never read as "not fired" and never as confirming NW-4C. A fallback band never records "within τ". **Take a band with τ < \|d\| ≤ 1 dB.** NFR-8 rules it "not breached". If 0.75 < \|d\| ≤ 1 dB at k ≥ 684, the reversal is recorded as **fired**. AX44 then goes back to the board as its own decision (her reversal clause, executed). A fired reversal holds no gate and opens none, and any change to AX44 or B15 is a FOR MAISARA answer with the AMENDS line. If 0.25 < \|d\| ≤ 0.75 dB, the band records "not resolved at τ". **M3-H-R1 is re-issued (§4a):** her reversal asks for the τ check; recording it carries out her decision; acting on it is routed to her. | revised |
| **Q4** "B11's doubling rule" | FALLS (INCONSISTENT) | **Accepted.** B11's per-bin doubling (up to 16·N₀) does not apply to (a0). **Step 1 now says that 07e-b runs no further particles.** (a0)'s N is fixed in 07e by rules stated before dispatch: the pilot rule, the cap, the timeout rerun, and **one pre-stated top-up triggered by realised k only**, before any engine-to-(a0) comparison is read (S5, 42-seat5 §6). Seat 2's "completing a run that stopped short (a failed shard, or quota)" is **not adopted**. It contradicts 07e's adopted rules (S5/S7), under which a partial result is never merged, a timeout reruns once, and a quota failure counts as "over cap". | revised |
| **Q5** S9 undo cost | IMPRECISE | **Accepted.** The S9 row now uses Seat 9's restated row (42-seat9 Q5). Undoing the flag means B15, "a measured both-near fallback with p95 ≤ 1 dB" (L408), which is a `src/sim` change. It also needs one golden round, because the D5 golden pins U and the five flags of every valid fixture (L167). If the output changes, M3-8 fires and 07e's JSON is re-pinned: about one phase [Hyp, size]. "A parameter change" fits only the 0.70 m threshold, which "changes who gets flagged, not the level they hear". | corrected |
| Correction: S9 marking | IMPRECISE | The S9 cell on the decided variant is marked ᶜ, read from 42-seat9 §6 (the Q2 text gives 0/1). The S9 H3 cell cites **29-seat9 §2** ("My row cannot separate these five"). | corrected |
| Correction: (a1) row | WRONG (arithmetic) | Sum **12** (1+2+0+1+2+0+2+0+4). It is still dropped at max 2. | corrected |
| Correction: K21 | IMPRECISE | Restated (§1): "0 dB as GA's L − R expectation at a corner emitter is **not established**. Derived evidence (F3 medium, F5 low) suggests it is not." (a1) is still dropped, on Seat 9's 2/2. | corrected |
| Correction: preset clause | IMPRECISE (attribution) | Attributed to S9 (36-seat9 §2(3)) and marked **stricter than AX44 Seat 6 (ii)**, which is a U rule ("no default placement … may raise U"), not a distance rule. It binds only through the step-2 board ruling, in which Seat 6 sits. | corrected |
| Note: sharded merge | SOFTWARE | Builder note added (Item A1). From the code, tracer.py L219–233 accumulates chunk by chunk, left to right. A merge of shard totals changes the floating-point summation order. The merge must reproduce chunk-order summation: shards upload per-chunk arrays of e, e², s1, s2, room and det, and the merge accumulates them in chunk-index order from `first_chunk`. The bit-identity unit test stays as written. | adopted |

---

## 1. Knowledge inventory (changes from file 40; K1–K20 and K22–K28 stand)

| K | what must be known | source | status |
|---|---|---|---|
| K21 (restated) | 0 dB as GA's own L − R expectation at a corner emitter | dossier 37 F3 (derived, medium), F5 (derived, low) | **not established**; derived evidence suggests it is not. Not load-bearing: (a1) is dropped on 38-seat9's 2/2 |
| K29 | τ = 0.25 dB per case and band (AX42). AX44's reversal: "the near-corner reference contradicts NW-4C by more than τ". "Before the goldens (phase 05h): the independent near-corner reference (Seat 2)" | BUILD_PLAN L165, L167, re-read | known |
| K30 | σ of a tracer level is 4.34/√k dB | corpus: Vorländer §11.2.5 Eq. 11.9 (σ_k/⟨k⟩ = 1/√⟨k⟩) with Eq. 11.17 (σ_ETC = (10/ln10)·σ_E/⟨E⟩); tracer.py L27–28 | known |
| K31 | Arithmetic: k 76 gives σ 0.498 dB, 3σ 1.49 dB; for a difference of two independent quantities, 3σ = 2.11 dB. k 684 gives σ 0.166 dB, 3σ 0.498 dB, and 0.704 dB for a difference. Fallback breach lines: 1 + 1.49 = 2.49 dB per emitter; 1 + 2.11 = 3.11 dB for L − R. Reversal lines: 0.25 + 0.498 = 0.75 dB (k 684) and 0.25 + 1.49 = 1.74 dB (k 76) | computed from K30; agrees with 41 L84, 42-seat1 §1, 42-seat2 §1, 42-seat9 §5 | known |
| K32 | AX43's N rule is z_FW·SE ≤ τ − ℓ_ref. At k 684: 4.29 × 0.166 = 0.71 dB > 0.25 dB, so (a0) does not meet it. Meeting it at ℓ_ref = 0 would need SE ≤ 0.25/4.29 = 0.0583 dB, i.e. k ≥ (4.34/0.0583)² ≈ 5,550 (≈ 8.1 × the k 684 count). So "fired" is a 3σ resolution, not AX43 precision | BUILD_PLAN L166; computed; 42-seat9 §5 | known. The cost of a τ-sized run (over Seat 7's cap at the [Hyp] mid case) is not load-bearing: the three-state record is required whatever N is |
| K33 | B11: doubling "up to 16·N₀", per bin; N "(beyond the pre-stated doubling rule) … never changed after results are seen" | BUILD_PLAN L404 (as read in 41 L85); tracer.py L45 | known |
| K34 | The tracer seeds chunk j with SeedSequence([seed, j]) and accumulates chunk sums left to right. All (a0) runs use TRACER_SEED | from the code, tracer.py L30–32, L219–233, L48; 07e text "The seed is TRACER_SEED and is never changed (B11)" | known |
| K35 | (derived) The r_d 0.025 m and 0.05 m spheres are concentric at the same source and use the same particles. A path through the inner sphere passes through the outer one, so the two radii's estimates are positively correlated. Var(d) = σ₁² + σ₂² − 2cov is then below the root-sum-square value, and a "combined 3σ" agreement test computed by root-sum-square is lenient. The L and R runs share chunk streams from different source positions, so the sign of their correlation is not known | derived from K34 (geometry and the variance of a difference). Statistics, not an acoustic fact | known as a direction for the radii; unknown for L/R. Answered by a pre-stated print (§2.4), not by a value |
| K36 | Spatial-averaging bias negligible for 0.05 / 0.025 m spheres wholly inside the room | 42-seat2 §5 [Hyp]; K22 (F10) covers unbiasedness for the sphere-averaged density | under-informed in size. **Not load-bearing:** every count needs both radii to agree (Seat 2: "the Q2 text does not depend on it") |

No load-bearing gap remains. **Cells read from conditions:** S1, S2 and S9 on the merged texts (§2). **Confidence: medium.**

---

## 2. One text per point, with attribution and the condition each cell rests on

### 2.1 Fallback band (Seats 1, 2, 9)

- **Common to all three:** a fallback band supports only a breach and never "not breached". The breach test is \|d\| > 1 dB + 3σ_d at both radii. "Not breached" is stated only over bands gated at k ≥ 684 at both radii. The rule is fixed before (a0) runs.
- **Taken from each:**
  - **S2:** "with the same sign"; σ_d for L − R as √(σ_L² + σ_R²); the numeric lines 2.49 / 3.11 dB; the label "SE ≤ 0.5 dB only; two-radius check resolves only …".
  - **S9:** both radii must agree within their combined 3σ; it is written as verdict (iv); the consequent edit to the 07e cap clause; the removal of Seat 1's hand-off.
  - **S1:** a non-breach fallback band is "not decidable" and "takes the 'not decidable' route for that band … and opens no gate"; bands with radii in disagreement, or with k < 76, are print only; "No AX44 reversal is recorded as 'not fired' from a fallback band"; "never changed after the prints are seen".
- **Decider (consistency):** a band with k < 76, or with the radii in disagreement, is print only (S1). For (a)'s overall outcome it also counts as "not decidable". Otherwise a band with *less* evidence would have a weaker gate consequence than a fallback band. This is stricter in Seat 1's direction. Seat 2: "The Q2 text makes 'not decidable' likelier … That is the same debt, not a new one" (42-seat2 §4).
- **Cells:**
  - S1 0/1 ᶜ rests on 42-seat1 §5 ("later 2 to 1 if the text above replaces it in both places"). The merged text keeps every element of Seat 1's text and adds only stricter conditions for a breach.
  - S2 1/1 ᶜ rests on 42-seat2 §6. Seat 2's "never toward 'not breached'", the clause it "won't trade away", is kept verbatim.
  - S9 0/1 ᶜ rests on 42-seat9 §6 ("Adopting the Q2 text lowers my cells from 2/2 to 0/1").

### 2.2 AX44's τ (Seats 2, 9, 1)

- **S2:** per emitter, never on L − R; the "indicated, not resolved" state; the engine's achieved SE printed beside each result; "That result alone opens or holds no gate"; if the reversal fires, AX44 goes back to the board as its own decision, and "That decision's order relative to 08-4 is set by its own ruling, never by default"; "Neither the breach nor the reversal amends anything by itself".
- **S9:** recorded for every counted band, including fallback bands (1.74 dB at k 76); "within τ … never read as confirming NW-4C"; a fired reversal with (a) not breached is listed under "Decided for Maisara"; scope 2 applies if that board orders a `src/sim` change before 08-4; the AX43-precision line (42-seat9 §5).
- **S1:** "never 'not fired'", and "not testable" for \|d\| ≤ τ (42-seat1 §6).
- **Seat 2 and Seat 9 differ** only in band coverage (S2: k ≥ 684 bands; S9: every counted band). The union is taken. Recording more states raises no cell: Seat 2's later 2 was for the τ outcome going *unrecorded*.
- **Decider:**
  - "Fired" needs both radii, with the same sign, as a breach does.
  - Working: every per-emitter breach also fires the reversal (gated: \|d\| > 1, so \|d\| − 0.498 > 0.50 > τ; fallback: \|d\| > 2.49, so \|d\| − 1.49 > 1.0 > τ). A breach on L − R alone may not. So Seat 9's "Every breach also fires the reversal" is restricted to per-emitter breaches.
  - 07e's existing print of E_target against the matchTail energy is shown beside each result, because AX44's reversal is stated against NW-4C (the estimator).
- **Gates:** a fired reversal holds no gate. Seats 2 and 9 say so in their own words. Seat 9's hand-off to Seats 5 and 7 ("whether to hold gates anyway") is answered as "not by default": holding a gate would only add to their costs, and the AX44 board that follows sets any order, with Seats 5 and 7 sitting in it.
- **Cells:** S2 1/1 ᶜ (42-seat2 §6, Q3 text). S9 unchanged ("The Q3 text does not move my cell", 42-seat9 §3–4).

### 2.3 Step 1 and the top-up (Seats 2, 5)

- **Common to both:** B11's per-bin doubling does not apply to (a0); B11's "never changed after results are seen" does; 07e-b reopens nothing.
- **S5 verbatim:** the top-up paragraph in 07e, and step 1 ("No further particles are run …").
- **S2 verbatim:** "B11's per-bin doubling to 16·N₀ does not apply to (a0)"; "particles are added, never redrawn, and the seed is unchanged".
- **Not adopted:** S2's completion clause, which conflicts with 07e's timeout and quota rules (§0 Q4). Its "before any (a0) result exists" becomes "before any engine-to-(a0) comparison is read". The top-up's trigger is realised k only, and "no engine value is read before the top-up completes" (S5).
- **Cells:**
  - S5 1/1 is its own cell. The Q4 component is the replacement it rates 0/0, so the cell rests on its other common costs.
  - S2 1/1 ᶜ. Its stated objection is optional stopping, i.e. N changed after the comparison is seen (42-seat2 §4). The top-up is pre-stated, and its trigger is not the comparison.
  - If Seat 2 rejects the top-up, it is deleted. Seat 5 rated "none" 1/1, so no cell exceeds 1 and no sum changes (§5, reversal).
- Seat 7's hand-off from Seat 5 ("whether the top-up's share of the 24 h cap needs its own reserve") is not separately answered. The top-up runs only "within the 24 h cap and the 36 h ceiling", which are Seat 7's own conditions, so S7's 1/1 (39-seat7 §5) rests on the same cap.

### 2.4 Shared seed (decider; new)

**The problem.** All four (a0) runs share TRACER_SEED (K34). So "combined 3σ" computed by root-sum-square makes the two-radius test lenient (K35).

**The pre-stated fix.**
- 07e's run record prints, per band, the standard error of the two-radius difference and of L − R estimated from the paired per-chunk sums, by the delta method. The chunks are independently seeded, and the method is fixed in the script before dispatch.
- 07e-b uses:
  - **for the two-radius agreement test, that chunk-based SE**: the shared particles make it smaller than the root-sum-square, so the agreement test becomes stricter (K35);
  - **for σ_d of L − R in the breach and reversal tests, the larger of the two figures**, which never lowers a breach line.

**Cost.** The per-chunk arrays are the ones the sharded merge already keeps (§0, sharded-merge note).

**Cells.** No seat has rated this clause. It makes a breach no easier and the counted set no larger, so it cannot create a false "not breached". It is marked (decider) and is severable.

---

## 3. Tension map (now / later)

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| H1 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 0/2 | 2 | ≥18 |
| H2-c | 0/2 | 1/2 | 0/0 | 0/2 | 1/2 | 0/1 | 1/2 | 0/0 | 0/1 | 2 | ≥15 |
| H2-cg | 0/1 | 1/1 | 0/0 | 0/2 | 1/1 | 0/0 | 1/1 | 0/0 | 0/0 | 2 | ≥9 |
| H4 | 0/1 | 1/1 | 0/0 | 0/1 | 0/2 | 0/1 | 1/1 | 0/0 | 0/0 | 2 | ≥9 |
| H3 | 0/1 | 1/1 | 0/0 | 1/0 | 1/1 ʳ | 0/0 | 1/1 † | 0/0 | 0/1 ʳ | 1 | 9 |
| H3+G | 0/1 ᶜ | 1/1 ᶜ | 0/0 | 1/0 | **1/1** | 0/0 | 1/1 ʳ | 0/0 | 0/1 ᶜ | 1 | 9 |
| H4+G with (a1) as a verdict reference | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | 1/1 | 0/0 | **2/2** | 2 | **12** |
| H4+G, file 40's fallback / τ / step-1 texts | 0/**2** | 1/**2** | 0/0 | 0/1 | **2/2** | 0/0 | 1/1 | 0/0 | **2/2** | 2 | — |
| H4+G, per-bin gate for (a0) | 0/1 | 1/1 | 0/0 | 0/1 | **3/3** | 0/0 | 1/1 | 0/0 | 0/1 | 3 | — |
| H4+G, no runner cap | 0/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | **2/3** | 0/0 | 0/1 | 3 | — |
| **H4+G (decided variant)** | 0/1 ᶜ | 1/1 ᶜ | 0/0 | 0/1 | 1/1 | 0/0 | 1/1 | 0/0 | 0/1 ᶜ | **1** | **9** |

**Basis of each cell, in the seats' words:**
- **S1:**
  - H4+G and H3+G: "with the text above: 0 / 1"; later 1 is "the residual of 29-seat1 §4 … a ruled fix fires M3-8"; "My row does not separate H4+G from H3+G" (42-seat1 §3). ᶜ on the merged text (§2.1).
  - File 40's text: "0 / 2".
  - H3: 29-seat1, unchanged.
- **S2:** H4+G and H3+G 1/1: "my row does not separate them" (42-seat2 §3–4). ᶜ on the merged texts (§2.1–2.3). File 40's texts: each "later 2" (42-seat2 §4).
- **S3, S6, S8:** 29-seat3 §6, 29-seat6, 29-seat8.
- **S4:** H4+G 0/1, "Confirmed, unchanged" (34-seat4 §2). H3/H3+G 1/0 (29-seat4, as in file 40).
- **S5:**
  - H4+G 1/1 (39-seat5 §4–5; 42-seat5 §4: "rests on nothing that H3+G does not also carry").
  - H3+G 1/1, **its own rating** (42-seat5 §3–4).
  - H3 ʳ: now 1 ("under H3 I priced the hold into its now-1") and later 1 from the three costs that are "the same under every home" (42-seat5 §3–4).
  - File 40's step 1: "2 now and 2 later" (42-seat5 §6).
- **S7:**
  - H4+G "with the 24 h cap: now 1, later 1" (39-seat7 §5).
  - H3+G 1/1 (32-seat7 §3), ʳ for the cap cost common to all homes.
  - H3 † is 29-seat7, not re-rated.
  - The new texts add no runner time beyond its cap and no gate.
- **S9:**
  - H4+G and H3+G "with the Q2 text: 0 / 1" (42-seat9 §3–4), ᶜ on the merged text. File 40's text: "2 / 2".
  - H3: "My row cannot separate these five" (**29-seat9 §2**), ʳ.
  - Seat 9's (a2) condition ("verdict (ii) should also compare each emitter's late level") is adopted (Item A2 (ii)).

---

## 4. Minimum-tension working

1. **Bounds.** Out:
   - (a1) as a reference: deciding on a gap (K20, K21).
   - File 40's fallback clause: CONDITIONS VIOLATED (K31).
   - File 40's step 1: INCONSISTENT with B11 L404 (K33).
   - Seat 2's completion clause: inconsistent with 07e's adopted timeout and quota rules.
   - "Fix before 08-4 whatever the cause": it would amend B15 inside a board decision.
   - No `src/sim` change happens in 07e or 07e-b, so NFR-8 stays binding.
2. **Veto.** The per-bin gate (S5 3/3) and the uncapped job (S7 later 3) are excluded. Their seats' conditions are adopted.
3. **Worst-off seat.** Max 2 drops H1, H2-c, H2-cg, H4, H4+G with (a1), and H4+G with file 40's texts. Max 1 keeps H3, H3+G and H4+G.
4. **Compose.** No variant lowers the max.
   - S2 and S9 later 1 → 0 needs B15 owned before 12-2. That amends B15, so it is FOR MAISARA, and it is left to 07e-b's inside-debt answer.
   - The top-up and the shared-seed clause are text repairs, not compositions: neither moves a cell.
5. **Sum.** H4+G: 1+2+0+1+2+0+2+0+1 = **9**. H3+G: 1+2+0+1+2+0+2+0+1 = **9**. H3: 1+2+0+1+2+0+2+0+1 = **9**. Three-way tie, now on Seat 5's own H3+G cell.
6. **Reversibility** (unchanged from file 40 §3 step 6).
   - 07e/07e-b, (a0), (a2), the 07d/07d-b split, the JSON-pin board looks and the pin reruns are common to all three.
   - Only H3 and H3+G hold 08-1 and 08-2 from day one. Seat 7: "spent at the start and cannot be recovered" (32-seat7 §4).
   - Only H4+G has the re-hear, "only if 07e-b rules a fix" (34-seat4 §2), and item 15's wait on 07e-b if 07c-2b's ABX dates slip. The same slip also holds 08-1 and 08-2 under H3 and H3+G (34-seat4 §3).
   - Undo cost of H4+G: under 1 session (32-seat7 §4). **H4+G is cheaper to undo.**
7. **Decide: H4+G (decided variant).** Confidence medium: three cells are read from conditions (S1, S2, S9 ᶜ), and no acoustic fact decides the home.

---

## 5. DECISION M3-H (revised 3): H4+G with the 07e (measure) / 07e-b (rule) split, Lead Seat 2

Gates, split and parallel work are as in file 40 §4, with three changes: the fallback, τ and step-1 texts of §2; the top-up; the shared-seed print. The texts are in §6.

**Load-bearing claims:**
- **D-L1 to D-L4:** as in file 30 (CORRECT, file 31).
- **D-L5 [seats]:** the cells in §3. Sums 9/9/9, on Seat 5's own H3+G cell (42-seat5 §3–4).
- **D-L7 to D-L11:** as in file 40 (CORRECT or faithful, file 41).
- **D-L12 [corpus + computed]:** fallback arithmetic, K30–K31 (Vorländer §11.2.5 Eqs. 11.9, 11.17). A fallback band cannot resolve 1 dB (3σ 1.49 > 1), so it supports only a breach.
- **D-L13 [plan + computed]:** τ = 0.25 dB (L165); the reversal is stated against NW-4C (L167); the reversal lines 0.75 / 1.74 dB; (a0) does not meet AX43's N rule (0.71 > 0.25 dB), so "fired" is a 3σ resolution (K29, K31, K32).
- **D-L14 [plan]:** B11's doubling cannot size (a0), and N is never changed after results are seen (K33).
- **D-L15 [code]:** chunk-order summation and the shared seed (K34). The two-radius correlation is derived (K35).
- **D-L6 [PRD]:** the acceptance check below and FOR MAISARA M3-H-R1 (§4a).

**Future-debt register (decided variant; every later ≥ 1):**

| seat | what it commits later phases to | what undoing costs | evidence arrives | repaid when |
|---|---|---|---|---|
| 1 (L1) | A ruled fix fires M3-8: 07c-2b F1/F2 are void for their scene, and the omni rerun is needed (29-seat1 §4; "the residual … the same under every home", 42-seat1 §3) | "deleting one file" (29-seat1 §4); now the two phase files | 07e-b's ruling | 07e-b rules no fix phase, or the M3-8 rebuild is done |
| 2 (L1) | One golden round plus M3-8 before the freeze, with the JSON re-pinned. (a) may end up flagged rather than fixed; "The Q2 text makes 'not decidable' likelier, so the record path is the likelier route. That is the same debt" (42-seat2 §4) | "B15 plus a D5 golden round" (42-seat2 §4) | 07e-b's ruling; any inside-debt FOR MAISARA answer | the fix phase lands before 08-4; for the flag, B15 gets an owner phase before 12-2 (38-seat2 §5) |
| 4 (L1) | Item 15 waits on a long fix, or on 07e-b itself if 07c-2b's ABX dates slip, so 08-3 may split. Earlier checklist verdicts are provisional and are re-heard only if 07e-b rules a fix phase (34-seat4 §2–3) | not stated by Seat 4 | 07e-b's ruling; the ABX sitting dates | 07e-b rules no fix phase (label lifted, Item E), or the re-hear |
| 5 (L1) | Scope 8 held and a likely 07d/07d-b split. A board look per output-changing phase until the end date. After the end date, a discrete-field flip that "no gate stops" (34-seat5 §4). (a0) reruns on each pin bump (39-seat5 §5). The pre-stated top-up branch (42-seat5 §6) | a flip: "one board look plus possibly a fix phase"; a pin bump: one manual job | 07e-b's ruling; 07d's start; the first output-changing PR after the end date whose reason names a flip; k_pilot and realised k | re-pin on the final restore path. The flip residual is carried open: Seat 5 names no repayment |
| 7 (L1) | 07d/07d-b split; 07e-b; longer holds; board loops until the end date; (a0) up to 24 predicted runner-hours (36 h ceiling) per run, top-up included, rerun on each pin bump (39-seat7 §5) | ½ session before 07e; under 1 session after the JSON is committed (32-seat7 §4) | 07e-b's ruling; the pilot | the split closes; the end date passes; per pin bump, never (a standing cost) |
| 9 (L1) | (a) may end up flagged rather than fixed: "about 6 JND of G, reachable by a drag", contained by U, the Phase 11 note and the record path's no-preset-within-0.70 m rule (42-seat9 Q5) | **B15** ("a measured both-near fallback with p95 ≤ 1 dB", L408): a `src/sim` change, plus one golden round (the D5 golden pins U and the five flags of every valid fixture, L167, regenerated with a CHANGELOG reason), plus M3-8 and the 07e JSON re-pin if the output changes; "roughly one phase [Hyp, size]". Seat 9's "a parameter change" covers only the 0.70 m threshold ("changes who gets flagged, not the level they hear") (42-seat9 Q5) | 07e-b's ruling; the p95 that B15 measures | B15 gets an owner phase before 12-2 (FOR MAISARA), or (a) is fixed. Rises to 2 "if B15 has no owner by 12-2 and any preset default sits within 0.70 m of a layout-4/5 corner" (42-seat9 §4) |

**Strongest objection: the three ᶜ cells (S1, S2, S9) on the merged fallback/τ/step-1 texts.**
- If any of those seats reads the merge as not meeting its condition, its later cell returns to 2 under every home. The home is unaffected, because the texts are common.
- But M3-H would then carry a 2, and the text would need another round.
- Why it holds:
  - every element each seat stated is kept;
  - the additions are stricter for "breached", never looser for "not breached";
  - Seat 2's untradeable clause and Seat 1's gate consequence are kept verbatim.
- Two items are severable: the top-up (if Seat 2 rejects it, it is deleted; S5 rated "none" 1/1) and the shared-seed clause (decider-only).

**Second: the S5 H3+G cell.** It is now Seat 5's own 1. Only a seat's 2 on an H4+G-specific cost (the re-hear, or item 15's wait) would move the home.

**Third: a gated-band "not breached" at 0.5 < \|d\| ≤ 1 dB fails Seat 1's \|d\| + 3σ ≤ 1 test.** Seat 1 itself limits "not breached" to bands gated at k ≥ 684 (42-seat1 §2), and the band rule (uncertainty under 0.5 dB) is the design every seat rated. It is not reopened.

**Fourth: not asked.** Seats 4 and 7 were not asked about the stricter fallback making the record path likelier. Their 1/1 cells already count waits on 07e-b (S4) and board loops (S7).

**Reversal condition:**
- **Now:**
  - a seat rates an H4+G-specific cost at 2 → H3+G;
  - S1, S2 or S9 rejects the merged text → its own text is substituted (its rated 1), and the others are re-asked;
  - Seat 2 rejects the top-up → the top-up is deleted (no cell moves).
- **When 07e starts:** k_pilot and realised k. Fallback bands and the top-up are the rules working, not a reversal.
- **Later:**
  - 07e-b's ruling. "No fix phase" zeroes S1's and S4's conditional debts.
  - A fired AX44 reversal sends AX44 to the board as its own decision. That holds no M3-H gate unless that board orders one.

**Accepted for Maisara (PRD check):** no hard constraint is broken, and no PRD id points to another survivor.
- **NFR-8 L112** ("Any valid scene renders correctly"): all three survivors rule (a) against (a0) before 08-4. No fallback band can clear (a). Equal.
- **FR-3D-5 L75:** (a) is reachable (D-L4). Equal.
- **NFR-1 L105** ("match impulse responses measured in real spaces"): (a0) supports "agrees with GA" only. It is necessary for NFR-8 and not sufficient for NFR-1, equally under all three.
- **L49/L101** ("Accuracy first"; "Accuracy is the top priority"): H4+G and H3+G order the CPU re-pin after the acoustic fix. H3 does not.
- **L55/L174** ("no fixed deadline"): H3 and H3+G hold 08-1 and 08-2, which no id asks for.

### 4a. FOR MAISARA M3-H-R1 (re-issued): reading AX44, AX42's τ and B15 against the 07e-b rulings

- **Question:** do ruling (a) an NFR-8 breach, recording AX44's reversal against τ, and ordering a fix before 08-4 amend her accepted AX44 or AX42 (2026-11-10, ledger P05B2-M-02) or B15?
- **Governing text:**
  - **L165 (AX42):** "τ = **0.25 dB** per case and band, C++ E_target against the reference (`ref_hybrid` at its finest certified rung), with the reference's ℓ_ref inside τ."
  - **L167 (AX44), reversal:** "the near-corner reference contradicts NW-4C by more than τ."
  - **L167, disclaimer:** "No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners."
  - **L167, debt:** "both-near reads low, flagged, not bounded (repaid by a measured both-near fallback with p95 ≤ 1 dB, §5 B15)."
  - **L408 (B15):** "none scheduled".
  - **PRD:** NFR-8 L112, "Any valid scene renders correctly"; FR-3D-5 L75; NFR-1 L105; L101, "Accuracy is the top priority".
- **Answer (exact wording):**
  - "A breach ruling for (a) amends nothing.
  - 07e-b records AX44's reversal separately from NFR-8: per emitter and per counted band, at τ = 0.25 dB (AX42), as 'fired', 'not resolved at τ' or 'within τ, not testable'. 'Fired' is a 3σ resolution, not AX43 precision.
  - Recording that state amends nothing; it carries out AX44's reversal clause. A fired reversal sends AX44 back to the board as its own decision. It holds no M3-H gate and opens none, and that board sets its own order relative to 08-4.
  - Any change to AX44, and any scheduling of B15, whether from that board or from a breach whose cause lies inside AX44's accepted both-near debt (the both-near weight w or the capped branch, U raised, a deficit inside C13 §2's −0.35 to −6.72 dB), is a separate FOR MAISARA answer carrying `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`, and the 07e-b gates hold until any inside-debt answer survives the interrogator.
  - Ordering a fix before 08-4 amends nothing where the cause lies outside that debt."
- **Reasoning:**
  1. Her reversal clause names a test ("contradicts NW-4C by more than τ"), with τ fixed per case and band (L165). Running that test and recording its state carries out her decision. Leaving τ out would leave a recorded clause of hers unexecuted where the reference exists.
  2. τ (0.25 dB) and NFR-8's 1 dB are different lines. A band with τ < \|d\| ≤ 1 dB is "not breached" under NFR-8 and may still fire her reversal. The two are recorded apart, so neither hides the other.
  3. The near-corner tracer cannot resolve τ to AX43's N rule (0.71 > 0.25 dB at k 684). So her clause is applied at 3σ, and "within τ" never confirms NW-4C. That reads L165's "with the reference's ℓ_ref inside τ" honestly: this reference's uncertainty is not inside τ, and the record says so.
  4. What she accepted with a schedule is narrower: the debt, repaid by B15, "none scheduled". Only a step that changes AX44 or schedules B15 changes what she accepted. That step is routed to her.
  5. L101 ranks accuracy first, but her recorded decisions bind until a separate answer amends them (decider.md §5; README rule 1). A fired reversal therefore starts her own reversal route and does not reorder phases by default.
- **Options against the ids:**
  - **(i) Chosen:** both lines recorded, amendments routed. Serves NFR-8 L112 and FR-3D-5 L75, executes AX44's reversal, and keeps AX42/AX44/B15 intact until she is answered for.
  - **(ii) Only the 1 dB NFR-8 line** (file 40): leaves her reversal unexecuted in the τ < \|d\| ≤ 1 dB band.
  - **(iii) A fired reversal holds the 07e-b gates:** serves L101, but sets an order her AX44 does not set, and strains L55/L174 by holding on a sub-1 dB result that Seat 9 places within 1 JND of G (AX42's citation of Vorländer Table 6.1).
  - **(iv) A fired reversal amends AX44 directly:** serves L101, but amends her decision with no answer, against README rule 1.
- **What would make her veto it:** L101's "Accuracy is the top priority" read as requiring that a fired reversal hold 08-4's goldens, because the goldens freeze NW-4C. The answer: the AX44 board that the reversal convenes can order exactly that (scope 2 then applies), on the evidence. 07e-b does not pre-empt it.
- **AMENDS:** none in this answer.

---

## 6. FINAL texts for the plan-editor (one `/fix-plan`)

Notation: **(S n)** attributes a clause to Seat n; **(decider)** marks my own words.

### Item A1: new file `docs/phases/phase-07e.md`
> # Phase 07e — NFR-8 placement findings from the 07c-2b ABX scenes: measurement (report only)
>
> Size: **S** · Depends on: [07c-2b](phase-07c-2b.md) `done` (the engine its golden round leaves) · Followed by: [07e-b](phase-07e-b.md) (the ruling; planned split, Seat 2: two S sessions) · Lead subject matter: Seat 2 (Engine architect), "late-tail statistics; image-source order; … claims of physical accuracy" · Created 2026-11-24 by phase-07c-2b's M3 loop (`docs/review/phase-07c-2b/` decider files 17 §3, 28, 30, 33, 40, 43 (H4+G); all nine seats, files 29-seat1…29-seat9, 32-seat2/5/7/9, 34-seat4/5, 36-seat2/9, 38-seat2/9, 39-seat5/7, 42-seat1/2/5/9; researcher 29-researcher-RH1 and 37-researcher-a-reference; interrogator files 31, 35, 41; Maisara's hand-back) · Read first, in this order: `CLAUDE.md`; this file; `phase-07e-b.md`; `docs/review/phase-07c-2b/5-builder-tail-spread.md`, `14-seat9.md` §2, `29-seat1.md` … `29-seat9.md`, `29-researcher-RH1.md`, `32-seat2.md`, `32-seat5.md`, `32-seat7.md`, `32-seat9.md`, `36-seat2.md`, `36-seat9.md`, `37-researcher-a-reference.md`, `38-seat2.md`, `38-seat9.md`, `39-seat5.md`, `39-seat7.md`, `42-seat1.md`, `42-seat2.md`, `42-seat5.md`, `42-seat9.md`, `43-decider-m3h-rebuttal3.md`; `docs/review/phase-05h/14-orchestrator-M2-near-corner.md`; `docs/BUILD_PLAN.md` §2 AX5, AX6, AX16, AX21, AX22, AX37, AX39, AX40, AX41, AX42, AX43, AX44, AX49 and §5 B11, B15; PRD NFR-1, NFR-8, FR-3D-5.
>
> ## Raise with Maisara
> None.
>
> ## Goal
> Measure, for each finding below, everything phase-07e-b needs to rule whether NFR-8 ("Any valid scene renders correctly") is breached and why, and to record AX44's reversal against τ. This phase gives no verdict. No `src/sim` change; nothing is tuned for a scene.
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
>    - For each placement and each emitter: the equal-window level per band, 63 Hz–8 kHz, against Eq. 5.42 (printed; a reference only where the field is diffuse, phase-07e-b scope 1) (S9); E_target against the `matchTail` energy; `--tail-level ax16` against the default; k_real and the fallback flag; the both-near and capped flags, w, n\*, N, W, U and the achieved SE of E_target (S2; achieved SE: 42-seat2 Q3).
>    - Per band and placement, the reference's uncertainty as used by 07e-b scope 1's band rule: for the tracer, from its gated window or bins as stated per run; for Eq. 5.42, stated in the report with its basis (decider; makes S2's band qualifier checkable).
>    - Per sweep, the equal-window 1 kHz deficit at each distance, with any step > 1 dB between neighbouring distances flagged as a jump the user would meet while dragging a source (S1). The flag is a print, not an audibility verdict.
>    - An indicative rigid-boundary column (researcher R-H1: Waterhouse 1958 Eq. 3, image sum; derived octave averages at 0.1 m, 1 kHz about −0.5 / −1.6 / −3.8 dB for 1 / 2 / 3 faces). It is printed and is never used to explain a deficit away (S9).
>    - Per placement and emitter: the handover time (after any AX22 fallback) and the AX21 step and dip at it, per band. L_f and L_p at the AX49 gated geometry and on `ax49_l4_cube` (S3, C3-a).
>    - **For (a), the reference and two required prints, each on its own placement** (S2, S9; 38-seat2, 38-seat9):
>      - **(a0) Near-corner tracer, at (a)'s exact positions: the reference for (a).** The seeded tracer (`tools/acoustics/tracer.py`) with its counting sphere wholly inside the room, at r_d 0.05 m and r_d 0.025 m (below the listener's 0.1 m clearance), as AX44's near-corner reference (`docs/review/phase-05h/14-orchestrator-M2-near-corner.md`). A band counts at full precision only where both radii are gated (window k ≥ 684, below) and agree within their combined 3σ (computed as in "Run record" below). Eq. 5.42 is not a reference for (a): layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4). The engine is never its own reference; an emitter swap is never a reference.
>      - **(a2) Moved listener.** The same room and emitters; the listener moved along its corner diagonal to 0.75 m from each of its three faces (outside AX44's 0.70 m both-near flag and clear of the tracer's 0.5 m default radius); the seeded tracer at r_d 0.5 m, gated at k ≥ 684. It separates the source-side cause (the image-source set at a corner source) from the AX44 both-near branch; it is a print for (a) and a reference for its own placement only (S9: never a reference for (a)).
>      - **The engine's E_fwd and E_rev at (a)**, uncapped, at w = 1 and at w = 0, which separates the cap from w.
>      - Printed per band, 63 Hz–8 kHz: the late level per emitter and L − R, for the engine at (a) and in (a2), and for the tracer in (a0) at each radius and in (a2); for each emitter in each case, w, the both-near and capped flags, U and the achieved SE. The 29-seat9 §5 flatness claim is printed as support, never as the verdict. The diffuse control is (c)'s tool only (S9).
>    - **(a0) run, gate and sizing** (S5, 39-seat5 §3; cap and conditions S7, 39-seat7 §2, §4; top-up S5, 42-seat5 §6):
>      - (a0) runs as a manual CI job (`workflow_dispatch`), never on PR open, with its JSON uploaded as an artifact; that artifact is the reference. The seed is TRACER_SEED and is never changed (B11). The numpy pin is hash-locked.
>      - **Gate per window, not per bin.** For each emitter, radius and band, k = (ΣE)²/ΣE² is computed over the same late window the verdict compares, and the window counts when k ≥ 684. Per-bin k is not used for (a0). B11's per-bin doubling to 16·N₀ does not apply to (a0) (S2, S5).
>      - **Sizing.** (1) A pilot at N_pilot = 16 M (the 05h precedent) runs per emitter and radius. It records k_pilot per band and the measured µs per particle. (2) N = N_pilot × 684 / min_band k_pilot (F7), rounded up to whole 200,000-particle chunks. (3) The pilot's particles are the first chunks of N. Particles are added, never redrawn.
>      - **Sharding.** The job splits into shards of whole chunk ranges (`first_chunk`, `total_n` = N). Each shard's predicted wall time, from the pilot rate, is at most half the runner's job limit (read from GitHub's documentation at dispatch; Seat 5 holds 6 h, [Hyp]). Shards upload per-chunk arrays (e, e², s1, s2, room, det), and the merge accumulates them in chunk-index order from `first_chunk`, reproducing `tracer.py`'s left-to-right chunk summation (decider; a merge of shard totals would change the floating-point summation order, interrogator file 41). The merge is checked to be bit-identical to an unsharded run on a small N (a unit test) (S5).
>      - **Cap.** The total predicted runner time for (a0) is capped at **24 runner-hours (1,440 min)**, covering the pilot, all four runs (2 emitters × 2 radii) and the top-up, summed over shards (S7). If N for a band would exceed the cap, that band is gated for (a) only at SE ≤ 0.5 dB (window k ≥ 76), and the record says so; such a band supports only a breach, never 'not breached' (phase-07e-b scope 1, verdict (iv)) (S9, S1, S2). If it cannot reach that either, the band is not counted (S5) and is printed only (S1).
>      - **Top-up (pre-stated; (a0)'s own rule, not B11's)** (S5, 42-seat5 §6): "After the full run, for each emitter and radius whose realised window k in a band is below that band's gate (684, or 76 where the cap put the band on the SE fallback), N is raised once to N × gate / min_band k_realised, rounded up to whole 200,000-particle chunks; particles are added, never redrawn. This happens only if the total predicted runner time, the top-up included, stays within the 24 h cap and the 36 h ceiling; otherwise the cap rule applies. The trigger is realised k alone; no engine value is read before the top-up completes. There is no second top-up. Seed, windows, bins and radii never change. The run record prints both N values and both k values."
>      - **Runner and spend conditions** (S7): standard 2-core hosted runners only; a hard spend ceiling of 36 runner-hours (the cap plus one re-shard rerun), and reaching it counts as 'over cap'; (a0) is dispatched only when the remaining monthly Actions quota, as read and recorded at dispatch, is at least the cap plus one full PR CI run; the spending limit is never raised to finish (a0), and a shard that fails on quota counts as 'over cap'. The GitHub rates, quota sizes and concurrency limits in 39-seat7 §4 are [Hyp], not inputs to this rule.
>      - **On a timeout.** A shard that exceeds its limit fails the job. A partial result is never merged or used. The loop re-shards at the measured rate and reruns once. A second failure counts as 'over cap', and the cap rule applies. Compute time is not session time; 07e-c is opened only if the artifact is not back before 07e's second session ends (S5; CLAUDE.md two-session rule).
>      - **Run record** (decider; makes S5's and S7's rules checkable): per emitter, radius and band: N (and the top-up N), k_pilot, window k (and after the top-up), SE, 3σ, whether the band is gated at k ≥ 684, on the SE fallback, or not counted; shards; the measured rate; predicted and actual runner hours; the quota read at dispatch. **Shared seed** (decider): all four runs use TRACER_SEED, so the two radii share particles and are not independent. Per band, the record also prints the standard error of the two-radius difference and of L − R, estimated by the delta method from the paired per-chunk sums (chunks are independently seeded, `tracer.py` L30–32), with that method fixed in the script before dispatch, beside the root-sum-square figure. Phase-07e-b uses the chunk-based figure for the two-radius agreement test, and the larger of the two for σ_d of L − R.
>      - The (a2) and (c) tracer runs go in the same manual job, under the same sharding and timeout rule; their gates stay as written. Their predicted time is printed beside (a0)'s; if (a0) plus them would pass the 36 h ceiling, the session returns to Seats 5 and 7 before dispatch (decider).
>    - For (b): window energy from the full IR (not tail-only), to test whether L's ISM-to-tail energy is continuous across [0.165, 0.380) s against R's ISM-only energy (S2).
>    - For (c): a diffuse control (the same room with its absorption spread over all faces to the same ᾱ in every band) and an independent late-level reference at equal times from the seeded tracer, every compared bin gated at k ≥ 684 (3σ ≈ 0.5 dB), so the reference's uncertainty is under 0.5 dB; 1.2 dB is about 1 JND of G (S9). The tracer's counting sphere lies wholly inside the room: r_d is below the receiver's clearance to every face, so with the default r_d 0.5 m the receiver is at least 0.5 m from every face; a sphere that crosses a face reads low and no 3σ gate detects it (S2, S9; researcher F10). (c)'s positions are interior (listener (10, 8, 1.7) m). Printed: L − R per band for the engine, the control and the tracer. Attribution: a spread that survives in the control is the engine's; one that only the tracer reproduces is the room's; if the tracer's 3σ band overlaps both readings, (c) is 'not decidable' with that stated (S9).
>    - The restore-work counters on the AX38 4c gate scenes: images per emitter, handover time, W_pilot, n\*, N, W (for a fix's effect on 07d scope 8) (S2).
>    - Nothing is fitted to the compared level (no circularity) (S2).
> 4. **Report:** `docs/review/phase-07e/report.md` prints every scope 3 value for (a) (with (a0), (a2) and the run record), (b), (c) and the sweep, with no verdict. Verdicts belong to phase-07e-b.
>
> ## Out of scope
> Any verdict on NFR-8 or on AX44's reversal (07e-b); any `src/sim` edit; tuning for a scene; preset or canvas changes; moving the AX6 clamp; raising any spending limit; any increase of (a0)'s N beyond the pilot rule and the one pre-stated top-up; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] The sweep script and its output JSON committed; the JSON holds every scope 3 print for every placement, and the (a2) and (c) tracer references with their seed and gated counts. The output JSON records the producing platform (OS, CPU architecture, CI runner label, preset, commit); values are produced by the `cli` preset on the ubuntu-24.04 x64 CI runner (S5). The full sweep and every tracer reference run only in a manually started job or as a one-off print on that runner, never in the per-run pytest (S2, S5). A new job in `ci.yml` follows CLAUDE.md's `needs: changes` / `ci-ok` rules; a separate manual workflow is allowed; `tools/ci/test_ci_workflow.py` passes either way. A pytest in the `python` job re-runs ≥ 1 placement through `render_cli` and asserts every value bit-identically on that runner; on macOS and Windows, `ismFallback` and k_real equal, times and levels within AX5's cross-architecture bound as converted by the builder and stated in the test (AX5). A disagreement in a discrete field is a finding, never a tolerance; the pytest's failure output names each discrete field that differs from the JSON (`ismFallback`, k_real across 19, the both-near or capped flag) (S5, 34-seat5 §6). The JSON changes only through `tools/ci/update_goldens.py` (S5). Until phase-07e-b is `done` and the fix phase its ruling names, if any, is `done`: a red caused by another phase's output change (e.g. 07d's C5) is resolved in that phase's PR: it re-runs the sweep on the producing runner, updates the JSON through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, and puts the changed prints to the board for whether 07e's findings and 07e-b's ruling still hold. It is never regenerated just to pass, and the ruling is never carried over unasked (S5, 32-seat5). After that date, such a red is updated in that phase's PR through `tools/ci/update_goldens.py` with a stated reason and a BUILD_PLAN §6 row, never regenerated just to pass (end date: S7, 32-seat7 §6; wording: S5, 29-seat5 §4); the reason states whether any discrete field (`ismFallback`, k_real across 19, the both-near or capped flag) changed (decider).
> - [ ] (a0): the manual job, the sharded run, the chunk-order merge and the top-up committed; the unit test that a sharded merge is bit-identical to an unsharded run on a small N is green; the (a0) artifact's JSON holds the run record of scope 3 (both N and both k values, the chunk-based and root-sum-square SEs), and the report cites the artifact's run (S5; decider).
> - [ ] §0 row 07e updated.
>
> ## Definition of done
> Scopes 1–4 complete; the JSON, script, pytest, (a0) artifact and report committed or linked; AC green in CI on Linux, macOS and Windows. The PR lists "Decided for Maisara". CLAUDE.md rules apply. The ruling is phase-07e-b's.

### Item A2: new file `docs/phases/phase-07e-b.md`
> # Phase 07e-b — NFR-8 placement findings: cause ruling (report only)
>
> Size: **S** · Depends on: [07e](phase-07e.md) `done` · Lead subject matter: Seat 2 (Engine architect) · Created 2026-11-24 with phase-07e as its planned split (decider files 30, 33, 40, 43; 32-seat2 §2; 42-seat1/2/5/9) · Read first: `CLAUDE.md`; this file; `phase-07e.md` and its report `docs/review/phase-07e/report.md` with the (a0) artifact; the files phase-07e lists; `docs/BUILD_PLAN.md` AX42, AX43, AX44 (§2) and B11, B15 (§5).
>
> ## Raise with Maisara
> None. (A FOR MAISARA answer this phase writes under scope 1 is given for her under `docs/board/README.md`, "Who answers Maisara's questions"; it is not a Raise item.)
>
> ## Goal
> Rule, per finding (a), (b), (c), whether NFR-8 is breached and why, from phase-07e's prints, and record AX44's reversal for (a) against τ, before 08-3's item 15 stimuli are built, before 07d's growth re-pin and before Phase 08-4. No `src/sim` change in this phase; nothing is tuned for a scene.
>
> ## Gates (what waits on this phase)
> Phase-08-4 (§0 Depends on), the build of phase-08-3 item 15's stimuli and phase-07d scope 8 (the growth re-pin) wait on this phase `done` and on the fix phase it rules, if any (S2, S5). Nothing else waits: 08-1, 08-2, the rest of 08-3 and 07d scopes 1–7 run in parallel; 08-3's checklist verdicts heard before then are recorded provisional (phase-08-3 item 7) (S4).
>
> ## Scope
> 1. **Board loop** (Lead Seat 2; decider; interrogator SURVIVES):
>    - It rules, per finding and per octave band in which the reference's uncertainty is under 0.5 dB: NFR-8 breached / not breached / not decidable, with the cause; for (a), fallback bands are ruled only under verdict (iv) below (S1, S2, S9). The reference is the GA-internal level: the late level that the engine's own geometrical model predicts at equal times for each emitter at the scene's source power (Kuttruff Eq. 5.42 where the field is diffuse; elsewhere the seeded tracer with its counting sphere wholly inside the room). Breached: a spread > 1 dB from that reference. Not breached: every band within 1 dB. Not decidable: no such reference can be formed (S2; reference named as in S9). A spread produced by a feature of the engine (the AX44 weight w, the AX39/AX41 capped branch, the AX22 fallback, the t_mix,e rule, a cap) is its cause, never its explanation (S2, S9).
>    - **For (a)** (S2, S9; 38-seat2, 38-seat9; 42-seat1, 42-seat2, 42-seat9): the reference is phase-07e's (a0). Layout 4 is non-diffuse (Kuttruff §5.7, Table 5.2 case 4), so Eq. 5.42 is not a reference for (a). Let d be the engine minus (a0), per emitter's late level or for L − R; σ_d = 4.34/√k for a per-emitter level, or √(σ_L² + σ_R²) for L − R, each from that radius's window k (S2), with phase-07e's shared-seed rule for L − R and for the two-radius test (decider). Band verdicts:
>      - (i) **Gated band** (window k ≥ 684 at both radii, the radii agreeing within their combined 3σ): breached if \|d\| > 1 dB for a per-emitter late level or for L − R; not breached if every comparison is within 1 dB.
>      - (ii) **(a2), its own placement:** if the engine in (a2) differs from the tracer by more than 1 dB, in L − R or in either emitter's late level (S9, 42-seat9 §4), (a2) is ruled a breach as its own placement, with its cause.
>      - (iii) **Bands with no verdict:** a band with k < 76 at either radius, or whose two radii disagree beyond their combined 3σ, is printed only, with no verdict (S1).
>      - (iv) **Fallback band** (S1, S2, S9): a band on phase-07e's SE fallback (window k ≥ 76 but < 684 at either radius; 3σ up to 1.49 dB per radius) is labelled 'SE ≤ 0.5 dB only'. It supports only a breach, never 'not breached', whatever d is (S1, S2, S9). It rules 'breached' when, at both radii and with the same sign, \|d\| > 1 dB + 3σ_d (2.49 dB per emitter, 3.11 dB for L − R at k 76) (S1, S2, S9), and the two radii agree within their combined 3σ (S9); the ruling marks it 'SE ≤ 0.5 dB only; two-radius check resolves only 3·√(σ_0.05² + σ_0.025²) dB' (S2). Otherwise the band is 'not decidable' (S1, S9).
>      - **(a)'s outcome** (decider, from the band verdicts): if any band is breached, (a) is breached (the breach route below; the other bands' states are listed with it). Otherwise, if any band is 'not decidable' under (iv) or has no verdict under (iii), (a) is 'not decidable' for those bands and takes the not-decidable route below; it opens no gate (S1, 42-seat1 §2; (iii) bands: decider, so that a band with less evidence never carries a weaker gate consequence than a fallback band). Otherwise (a) is 'not breached', stated over the bands gated at k ≥ 684 at both radii (S9). 'Not breached' for (a) is never stated from a fallback band (S1, S2, S9).
>      - These rules are fixed before (a0) runs. They are never changed after the prints are seen (S1).
>      - The 29-seat9 §5 flatness claim ('flat within ±1 dB from 125 Hz to 4 kHz → an engine effect') is printed as support, never as the verdict. The ruling names the cause, never its explanation.
>    - **AX44's reversal, recorded separately from NFR-8** (S2, 42-seat2 Q3; S9, 42-seat9 Q3; S1, 42-seat1 §6). AX44 (BUILD_PLAN L167): 'the near-corner reference contradicts NW-4C by more than τ'. AX42 (L165): 'τ = 0.25 dB per case and band'. The test is applied per emitter's late level, never on L − R (S2), in every counted band of (a) (gated, or a fallback band) (S9). In each, the ruling records one of:
>      - 'AX44 reversal: fired', when \|d\| > τ + 3σ_d at both radii with the same sign (0.75 dB at k ≥ 684; 1.74 dB at k 76) (S2, S9; both radii: decider);
>      - 'AX44 reversal: not resolved at τ (reference 3σ = x dB)', when \|d\| > τ at either radius but the reversal is not fired (S2, S9);
>      - 'AX44 reversal: within τ, not testable (reference 3σ = x dB > τ)', when \|d\| ≤ τ at both radii, in gated bands only; it is never read as 'not fired' or as confirming NW-4C (S9, S1). On a fallback band this case is recorded as 'not resolved at τ' (S1: 'No AX44 reversal is recorded as "not fired" from a fallback band').
>      Beside each result: the engine's achieved SE (S2) and phase-07e's E_target against the `matchTail` energy (decider), and the line "'fired' is a 3σ resolution; (a0) does not meet AX43's N rule (z_FW·SE ≤ τ − ℓ_ref: 4.29 × 0.166 = 0.71 dB > 0.25 dB at k 684)" (S9). A per-emitter breach also fires the reversal; a breach on L − R alone may not (decider; working in decider file 43 §2.2). A band with τ < \|d\| ≤ 1 dB is 'not breached' under NFR-8; that result alone opens or holds no gate (S2, S9). If the reversal fired, AX44 goes back to the board as its own decision (its reversal clause), outside this phase's gates; any change to AX44, and any scheduling of B15, is a FOR MAISARA answer with `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`; that decision's order relative to 08-4 is set by its own ruling, never by default (S2); if it orders a `src/sim` change before 08-4, scope 2 applies (S9). A fired reversal is listed under 'Decided for Maisara' (S9). Neither a breach nor a fired reversal amends anything by itself (S2).
>    - **'Not decidable' is never 'not breached' and opens no gate by itself** (S1, S2, S9):
>      1. No further particles are run. (a0)'s N per emitter and radius was fixed in phase-07e by rules stated before dispatch (the pilot rule, the cap, the timeout rerun and the one pre-stated top-up), none of them triggered by an engine-to-(a0) comparison. N is never changed after the comparison has been seen (B11's clause, L404, applied to (a0)); B11's per-bin doubling to 16·N₀ does not apply to (a0) (S5, 42-seat5 §6; S2, 42-seat2 Q4).
>      2. The gates stay shut until a board ruling with Seats 1, 4, 5 and 7 (S2), and Seats 6 and 9 for the note and the preset condition (decider), records (a) (naming its not-decidable bands) under AX44 as Maisara accepted it. The record requires all of the following (S9, 36-seat9 §2(3)):
>         - U raised at (a) and asserted in a test;
>         - the AX44 note shown at (a) in Phase 11;
>         - no fixture or Phase 12 preset default within 0.70 m of a layout-4/5-type corner (S9, 36-seat9 §2(3); stricter than AX44 Seat 6 (ii), which is a U rule, 'no default placement … may raise U'; it binds only through this ruling, in which Seat 6 sits);
>         - (a) entered as evidence on B15;
>         - the 'not decidable' listed under 'Decided for Maisara'.
>    - **On a breach: the gate splits by cause** (S2, 38-seat2; S9, 36-seat9 §2(4); FOR MAISARA M3-H-R1, decider files 40 §4a and 43 §4a). The ruling quotes AX44 (BUILD_PLAN L167: the GA-limit paragraph, the debt, the reversal), AX42's τ (L165) and B15 (L408). A breach amends nothing by itself; its effect on AX44's reversal is recorded as above (S2).
>      - **Outside AX44's accepted debt.** Any one of these: verdict (ii) fires for (a2); the deficit against (a0) lies outside C13 §2's −0.35 to −6.72 dB; U is silent; or the cause is the ISM set at a corner source, the AX22 fallback or the t_mix,e rule. This is an ordinary NFR-8 breach, and the fix gate (scope 2) applies.
>      - **Inside it** (the both-near w or the capped branch, U raised, inside the envelope). Ordering a fix before 08-4, or leaving B15 unscheduled with U shown, is written as a separate FOR MAISARA answer (`docs/board/README.md`, "Who answers Maisara's questions"), with the line `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` if it schedules B15. The gates hold until that answer survives the interrogator (or, in one of the README's three cases, until Maisara answers).
>      - **Mixed causes.** The outside part takes the fix gate. Any part of a fix that changes the both-near weight w or the capped branch goes by the inside route first (decider).
>    - Before the verdicts it records, as already settled by this text, that the engine does not reproduce coherent near-boundary source radiation (R-H1; researcher F12): it is geometric, and as built its late level follows an energy target (E_target), so the reference above holds (S2, S9). AX44's GA-limit paragraph (L167) has a receiver-side mechanism sentence and a disclaimer that covers both ends ("No accuracy claim is made where both ends are flagged, nor at layout-4/5-type edges and corners") (S2, S9; 36-seat2 §3, 36-seat9 §1). Whether the mechanism sentence should also name the source side (R-H1 §7) is recorded after the per-finding verdicts, not before them and not in their place, as a separate AX44 amendment (a FOR MAISARA answer with its AMENDS line, since AX44 is her recorded decision) (S9; decider). The rigid-boundary column (phase-07e scope 3) is therefore never a ground for 'not breached' and cannot reduce a spread (S9, S2). Changing that answer is a separate board decision with a new AX checked against the corpus, outside this phase; it applies at the source to the direct, early and late parts alike, and under it a spread counts as explained only where it matches that model's per-band prediction within 1 dB and arises from that mechanism (S2).
>    - Audibility is never a ground for 'not breached' under NFR-8 (S1). If the loop considers deferring a ruled fix, Seat 1's self-ABX for (a) (29-seat1 §4) is run first; its null never makes (a) "not breached" (S1).
>    - Hand-offs it convenes: Seat 1 (audibility, if deferral is weighed; whether a breach established on a fallback band may be quoted outside the ruling (S2, 42-seat2 Q2)); Seat 6 (what the canvas or the AX44 note must say at (a); no ruling is ever answered by moving the AX6 clamp, and a change to AX6 is a separate board decision: it remaps saved automation (S6)); Seat 9 (attribution for (c); which planned 12-2 presets place a source within 0.5 m of a face (S9)); Seat 4 (whether a fix adds `both_corner` and `both_wall` to 08-3 AC6's parity cases); Seat 2 (whether a post-ruling flip of k_real across 19 is enough on its own to reopen (b), 34-seat5 §7); Seats 5 and 7 (any fix's order and cost; they sit in the AX44 board a fired reversal convenes). Already answered: K8, the drag clamp (29-seat6); R-H1, the source power near rigid faces (29-researcher-RH1); what a fallback band may be claimed as (verdict (iv); 42-seat9 §2).
> 2. **If a `src/sim` change follows:**
>    - The loop writes it as its own phase file (e.g. `phase-07f.md`), ordered before 08-4 and before 07d scope 8. It is an output change (golden round, §6 row; phase-07e's JSON re-pinned inside that round (S2)), fires phase-07c-2b M3-8 (rebuild and reseal both ABX scenes before 08-3 listening), and adds no scene- or placement-specific logic (NFR-8).
>    - The `/fix-plan` that creates the fix phase also adds its id to the Depends-on text of §0 row 08-4 and `phase-08-4.md` L3, to 08-3 item 15's stimulus sentence, and to phase-07d scope 8's order line (or 07d-b's §0 row) (S5, G1/G2).
>    - If a fix phase lands after 07d scope 8's re-pin is committed, its own automated acceptance criteria include that re-pin on the restore path it leaves: reference and baselines from ≥ 6 green manual runs after its last code change (no pooling of earlier runs), a `tests/golden/CHANGELOG.md` reason and a BUILD_PLAN §6 row, under phase-07d scope 8's rule, its Linux return-to-board clause included. It also prints record (h)'s 8-instance load on its own runs; an exceedance goes to the board (S5). A growth red after the fix goes to 07d's FM-GROWTH board loop; it never trims or reverts the acoustic fix (NFR-8, PRD L49) (S2).
>    - A fix that moves the handover, L_f or L_p carries in its own acceptance criteria: AX49's acceptance re-asserted; L_p at the gated geometry printed against 3.82 s; record (h) re-printed at the rated corner if L_f moved there; and the M3-8 rebuild, which names the L4 stimuli if `ax49_l4_cube`'s IR changes (S3, C3-a).
>    - The fix phase also prints the restore-work counters on the AX38 4c gate scenes before and after the fix; whether equal counters allow pooling under 07d scope 8 is Seat 5's ruling (S2).
>    - If the loop finds the fix cannot land before 08-4 or before item 15's build, that order is its own board ruling with Seats 4, 5 and 7, never a default.
>
> ## Out of scope
> Any `src/sim` edit; re-measuring beyond phase-07e's prints; any increase of (a0)'s N; tuning for a scene; preset or canvas changes (any consequence goes to 11-2, 11-3 or 12-2 by ruling); moving the AX6 clamp; changing AX44 or scheduling B15 except through a FOR MAISARA answer under scope 1; 07d's work.
>
> ## Acceptance criteria — automated
> - [ ] Phase-07e's pytest green on this branch, its JSON unchanged.
> - [ ] §0 rows 07e-b (and 07d, 08-3 and 08-4, if the ruling adds a fix phase) updated.
>
> ## Definition of done
> The ruling for (a), (b) and (c), with the AX44 reversal record for (a) per emitter and counted band, is committed under `docs/review/phase-07e-b/`, and the interrogator returns SURVIVES. Any FOR MAISARA answer that scope 1 requires (the inside-debt route, the AX44 source-side wording, any AX44 or B15 change after a fired reversal) has survived the interrogator and is listed under "Decided for Maisara" (or, in a README case, Maisara has answered). If a fix is ruled, the fix phase file and its §0 row exist, and its id is in the Depends texts named in scope 2. The PR lists "Decided for Maisara". CLAUDE.md rules apply.

**Reconciliation notes (for the interrogator):**
- §2.1–2.4 give each merged clause's sources.
- Seat 2's completion clause is dropped (it conflicts with 07e's timeout and quota rules).
- Seat 2's "before any (a0) result exists" becomes "before any engine-to-(a0) comparison", because of the top-up.
- Seat 9's "Every breach also fires the reversal" is restricted to per-emitter breaches (§2.2 working).
- The (a)'s-outcome sentence and the (iii) bands' route are mine (§2.1).

### Item B: BUILD_PLAN §0
- **New rows after 07d:**
  > "| 07e | [NFR-8 placement findings: measurement (report only)](phases/phase-07e.md) | S | not started | | | Depends on 07c-2b `done`. Created 2026-11-24 by phase-07c-2b's M3 loop (decider files 17 §3, 28, 30, 33, 40, 43: H4+G; all nine seats, files 29, 32, 34, 36, 38, 39, 42; researcher files 29, 37; interrogator files 31, 35, 41; Maisara's hand-back). Lead: Seat 2 (Engine architect). Planned split: this phase measures (scopes 1–3, report, the (a0) near-corner tracer by manual job: per-window k ≥ 684 gate, one pre-stated top-up, cap 24 runner-hours, SE ≤ 0.5 dB fallback that supports only a breach); 07e-b rules. No `src/sim` change. Opens no gate by itself; runs in parallel with 08-1, 08-2 and 07d scopes 1–7. |"

  > "| 07e-b | [NFR-8 placement findings: cause ruling (report only)](phases/phase-07e-b.md) | S | not started | | | Depends on 07e `done`. Created 2026-11-24 with 07e (decider files 33, 40, 43; 32-seat2; 42-seat1/2/5/9). Lead: Seat 2 (Engine architect). A fallback band never rules 'not breached'; 'not decidable' opens no gate; AX44's reversal is recorded per emitter and band at τ = 0.25 dB, apart from NFR-8, and a fired reversal sends AX44 to the board without holding a gate; a breach inside AX44's accepted both-near debt goes to a FOR MAISARA answer before any fix is ordered (B15). A fix, if ruled, is its own phase before 08-4 and 07d scope 8. Gates 08-4 (Depends on), 08-3 item 15's stimulus build and 07d scope 8. |"
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
  > "Stimuli are built only after phase-07e-b is `done` and the fix phase its ruling names, if any, is `done` (phase-07c-2b M3-H, decider files 30, 33, 40, 43; the fix phase's id is added here when its §0 row is created)."
- **Item 7, append** (S4; the change from "07e" to "07e-b" follows S2's gate condition; last sentence S4, 34-seat4 §4):
  > "If heard before phase-07e-b is `done` (and the fix phase it rules, if any), the checklist verdicts and the both-near render note are recorded 'provisional: engine before the 07e-b ruling'. A level or dryness remark on a near-face render goes to 07e/07e-b (or, once 07e-b is `done`, to the board) as an NFR-8 candidate, never to the HRTF or the headphones. The label is lifted without re-hearing if 07e-b rules no fix phase."
- **Listening checklist:** after "Record the `hrtfId` … (scope 7).", add:
  > "Verdicts heard before phase-07e-b is `done` are marked 'provisional: engine before the 07e-b ruling' (item 7)."

### Item F: `docs/validation/abx-07c-2-run-sheet.md`, C-b bullet (L130–131)
Replace "goes to the board (home pending Maisara's answer on M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`) as an NFR-8 candidate." with:
> "goes to phases 07e/07e-b, or, once 07e-b is `done`, to the board as an NFR-8 candidate (M3-H, decider files 30, 33, 40, 43; R1)."

### Item G: `docs/phases/phase-07c-2b.md`, Out of scope (L192–193)
Replace the line with:
> "- The NFR-8 placement findings (both_corner, both_wall onset, s0.7 spread): measured in phase-07e, ruled in phase-07e-b (M3-H, decider files 30, 33, 40, 43, H4+G); this phase's PR lists them under Follow-ups."

### Item H: BUILD_PLAN §0 row 07c-2b (two edits, bookkeeping)
- **Status cell:** replace "blocked (awaiting Maisara: M3-H answer, the ABX listener and sitting dates, then the ABX itself)" with:
  > "blocked (awaiting Maisara: the ABX listener and sitting dates, then the ABX itself)"
- **Notes:** in "Waiting: M3-H (case (a), file 24);", replace "M3-H (case (a), file 24)" with:
  > "nothing on M3-H (decided for Maisara, decider files 30, 33, 40, 43: H4+G, phases 07e/07e-b)"

### Item I: BUILD_PLAN §6, new row
> "| 2026-11-24 | Phase 07c-2b M3-H re-run after Maisara's hand-back (decider files 28, 30, 33, 40, 43; seats files 29-seat1…9, 32-seat2/5/7/9, 34-seat4/5, 36-seat2/9, 38-seat2/9, 39-seat5/7, 42-seat1/2/5/9; researcher 29-researcher-RH1, 37-researcher-a-reference; interrogator files 31, 35, 41; corpus c1b171f): phases 07e and 07e-b created, Lead Seat 2. 07e is report-only measurement: findings, causes, a sweep with Seats 1/2/3/6/9 prints; for (a) the near-corner seeded tracer (a0) at r_d 0.05 and 0.025 m as reference, with a per-window k ≥ 684 gate, pilot sizing, one pre-stated top-up triggered by realised k only, chunk-order sharded merge, a 24 runner-hour cap with an SE ≤ 0.5 dB fallback and a 36 h ceiling, and shared-seed SEs printed beside root-sum-square; the moved-listener (a2) print; for (c) a diffuse control and a tracer reference with the sphere wholly inside the room; the G3 producer-platform pytest on ≥ 1 placement naming any changed discrete field; Seat 5's red clause until 07e-b and any fix are `done`, then update-with-reason. 07e-b rules against the GA-internal level: an engine feature is a cause, never an explanation; a fallback band supports only a breach (\|d\| > 1 dB + 3σ_d at both radii), never 'not breached'; 'not decidable' opens no gate and runs no further particles (B11's clause applied to (a0)); AX44's reversal is recorded per emitter and counted band at τ = 0.25 dB (AX42) as fired / not resolved at τ / within τ, not testable, apart from NFR-8, and a fired reversal sends AX44 to the board without holding a gate; a breach inside AX44's accepted both-near debt goes to a separate FOR MAISARA answer (B15) before any fix is ordered, the gates holding; fix-phase ordering G1/G2, C3-a. §0 rows 07e, 07e-b (new), 07c-2b (status and notes), 07d, 08-3 and 08-4 (Depends on 07e-b, G1); phase-07d scope 8 ordered after 07e-b and its fix phase (G2; 07d-b split if reached first); phase-08-3 item 15 gate, item 7 provisional clause with its lift, checklist line; phase-08-4 L3; run sheet C-b bullet (R1); phase-07c-2b Out of scope. Decided for Maisara (FOR MAISARA M3-H-R1: a breach ruling and the τ record amend AX42/AX44/B15 nothing; any AX44 change or B15 scheduling is routed to her with the AMENDS line); amends nothing. | phase-07c-2b session (Claude), board loop; /fix-plan (plan-editor); `docs/review/phase-07c-2b/` |"

---

## 7. Summary

| id | decision | state | worst-off seat (cell) | sum | confidence | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-H | H4+G with the 07e/07e-b split, Lead Seat 2; gates on 07e-b `done` plus its fix phase; (a0) reference with per-window gate, one pre-stated top-up, 24 h cap, fallback that supports only a breach; τ recorded apart from NFR-8; split-by-cause breach gate; texts §6 A1–I | revised (to the interrogator; third round) | 1 (S1 ᶜ, S2 ᶜ, S4, S5, S7, S9 ᶜ) | 9 (ties H3+G and H3 at 9 on S5's own cell; reversibility decides) | medium | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174; AX42 L165, AX44 L167, B11 L404, B15 L408 | Vorländer §11.2.5 Eqs. 11.9, 11.17 (fallback and τ lines); Kuttruff §5.7 Table 5.2 case 4, Eq. 5.42 premise; Vorländer §11.2.2 Eq. 11.5, Eq. 11.12 (sizing) | now: a seat rates an H4+G-specific cost 2 → H3+G; S1/S2/S9 reject the merge → its own text, the others re-asked; S2 rejects the top-up → deleted. Pilot: k sets the fallback and the top-up. Later: 07e-b's ruling; a fired reversal → the AX44 board |
| M3-H-R1 | FOR MAISARA: a breach ruling and the per-emitter τ record amend nothing; a fired reversal sends AX44 to the board, holding no gate; any AX44 change or B15 scheduling, and any inside-debt fix order, is a separate FOR MAISARA answer with the AMENDS line | for Maisara (to the interrogator) | — | — | high (plan text quoted) | NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L101, L55/L174; AX42 L165; AX44 L167; B15 L408 | none (product reading); τ arithmetic Vorländer §11.2.5 | she vetoes; or the AX44 board convened by a fired reversal orders a gate (then scope 2 applies) |

**Challenges to settled decisions:** none.

## 8. Decided for Maisara

- **M3-H (revised 3).**
  - **What we chose:** two small report-only phases. 07e measures whether a source pushed into a corner loses its reverb. 07e-b rules on it.
  - **The yardstick:** an independent particle simulation at the exact spot, capped at 24 machine-hours. Where the yardstick is too coarse to see a 1 dB error, it can only show a fault. It can never clear the corner as fine.
  - **Your earlier condition:** you accepted that the near-wall estimate would be rechecked if this yardstick disagreed by more than 0.25 dB. That check is now recorded on its own line. If it fires, the near-wall rule goes back to the board, and any change to it comes back to you.
  - **Rests on:** NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L49/L101, L55/L174. H3 and H3+G serve the same ids, but they also hold 08-1 and 08-2 from day one, which no PRD id asks for.
  - **Who gave most:** Seat 2, which leads both phases and runs the corner job. Seats 5 and 7 carry the cloud job. They get back one golden round and one re-pin before anything freezes, a hard compute cap, and an end date on the JSON's board checks.
  - Amends nothing.
- **FOR MAISARA M3-H-R1 (reading of AX42's τ, AX44 and B15).**
  - Calling the corner case "broken", and recording your 0.25 dB recheck, changes nothing you decided. It carries out the recheck you wrote into AX44.
  - If the recheck fires, the near-wall rule goes back to the board. Any change to it, or any scheduling of the near-wall fix (B15), comes to you as its own answer with the AMENDS line.
  - Rests on NFR-8 L112, FR-3D-5 L75, NFR-1 L105, L101; AX42 L165; AX44 L167; B15 L408. Amends nothing.

**NEEDS MAISARA: none.** Checked against `docs/board/README.md`'s three cases:
- **(a)** The PRD and her recorded decisions settle every point: τ and the reversal are her accepted AX42/AX44 text, and NFR-8 and L101 govern the rest.
- **(b)** No PRD requirement, constraint or out-of-scope item changes.
- **(c)** No veto-grade rating is overridden: the per-bin gate and the uncapped job are excluded, and file 40's texts are dropped at max 2.

One person-only action stays outside the loop: raising a GitHub spending limit to finish (a0). The texts forbid it.

**Files read:**
- `/home/user/makroof/docs/review/phase-07c-2b/40-decider-m3h-rebuttal2.md`, `41-interrogator-on-file40.md`, `42-seat1.md`, `42-seat2.md`, `42-seat5.md`, `42-seat9.md`
- `/home/user/makroof/docs/BUILD_PLAN.md` L163–168 (AX40–AX45; τ at L165, AX43's N rule at L166, AX44 at L167), L404 (B11, via grep), L408 (B15)
- `/home/user/makroof/docs/PRD.md` L47–56, L99–113
- `/home/user/makroof/tools/acoustics/tracer.py` L20–48, L215–238
- Corpus: `/home/user/makroof/docs/corpus/vorlaender-auralization.md` L3054–3083 (§11.2.5 Eqs. 11.7–11.18) and the notation table (L418, L715); `/home/user/makroof/docs/corpus/SOURCE_COMMIT`
---

## Errata (orchestrator, 2026-11-24): interrogator file 44's corrections C1–C8

File 44 found M3-H SURVIVES WITH CORRECTIONS. The plan texts (§6) are applied with C1 (bullet 1), C2, C3 and C4; the
corrections to this file's own reasoning are recorded here and govern over the text above:
- C1 (§2.4): "for the two-radius agreement test, that chunk-based SE" reads "for the two-radius agreement test, the
  smaller of the chunk-based SE and the root-sum-square".
- C5 (D-L12): "A fallback band's 3σ (0.50 to 1.49 dB for 76 ≤ k < 684) breaks the band rule's 'uncertainty under
  0.5 dB', and it exceeds 1 dB itself for k < 170 (Vorländer §11.2.5 Eqs. 11.9, 11.17: 13.02/√k > 1). So the band
  supports only a breach."
- C6 (§2.3): "S5 verbatim: the top-up paragraph in 07e, and step 1" reads "S5 verbatim: the top-up paragraph in 07e.
  Step 1 merges S5's and S2's texts (not verbatim)".
- C7 (§8, M3-H "Your earlier condition", and the M3-H-R1 bullet): after "That check is now recorded on its own line."
  (and after "carries out the recheck you wrote into AX44.") add "The yardstick can confirm a disagreement only above
  about 0.75 dB (1.74 dB where it is coarse). Smaller ones are recorded as unresolved, never as passing."
- C8 (M3-H-R1 option (iii)): "within 1 JND of G (AX42's citation of Vorländer Table 6.1)" reads "within 1 JND of G at
  500 to 1000 Hz (AX42's citation of Vorländer Table 6.1)".
