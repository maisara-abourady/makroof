# 9 — Decider, decision round 2 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Inputs: files 5–8.

# Decider, decision round 2: phase 07c-1 (D-C1, D-C2, D-C3, D-C9), 2026-11-12

**Inputs read:**
- Review files 5, 6-seat1…9-r2, 7 and 8, plus 3-seat3, 3-seat5 and 4 (re-read).
- `docs/phases/phase-07c-1.md` in full; `docs/PRD.md` in full.
- `BUILD_PLAN.md`: AX18 (L138); AX38 4c and AQ10 (L115, L158), the H1-F2 clauses and their AMENDS lines.
- `docs/sessions/2026-11-08-interrogate-phase-07.md` (her words that accepted AX18).
- `src/sim/tail/NoiseTail.cpp` L77–155 and L198–251.
- Vorländer §6.4.1–6.4.4 and Table 6.1.

**Corpus revision:** `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`.

## 0. Outcome in brief

- **No NEEDS MAISARA.** Four FOR MAISARA answers below. Three of them amend her recorded decisions: AX18 of 2026-11-08, and H1-F2 and AQ10 (C) of 2026-11-10.
- **Every FALLS row is repaired:**
  - Keyless loads now get a synchronous stage-1 solve, so no load plays only the early part where the scene has a tail.
  - The S+E/P-mismatch clause is dropped.
  - AX47 now separates hard bounds from statistical ones.
  - L_p is fixed by Eq. 6.4 and now has a measured cost.
- **Worst-off seat is honestly 2** (Seat 3) in D-C2 and D-C9, not 1 as round 1 said. D-C1 and D-C3 have worst-off 1.
- **A cell resting on a [Hyp] cost is now contradicted by a measurement.** Seat 7 rated the restore at "8 × ~0.3 s"; file 8 implies about 0.65–0.8 s per instance at the 96 kHz / T60 ≥ 8 s corner. I ask Seats 5 and 7 to confirm their cells (§6). The decision stands until then, and only a 3 would reopen it.

## 1. PRD digest

- **For whom:** producers and DJs, any DAW, macOS and Windows, with no spatial-audio knowledge.
- **Outcome:**
  - a reopened project restores "the scene and its render exactly, on any machine" (NFR-6);
  - render state is saved (FR-LIC-1);
  - the result reaches the track by bounce (A4).
- **PRD priority:** "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a DAW session" (NFR preamble; NFR-1, NFR-2).
- **Hard bounds:**
  - NFR-8 / FR-SIM-2: no scene-specific path;
  - AX5;
  - AQ4 (30 ms);
  - AX40/AX44;
  - AX41 (A) W_max in 07c-1;
  - no `contractVersion` change;
  - the Phase 07 state rules;
  - conditions 4, 5, 6, 9, 10, 12 and A2;
  - no instance cap.
- **Her recorded decisions touched here:**
  - AX18 (accepted 2026-11-08);
  - AQ10 as amended and AX38 4c H1-F2, i.e. condition 9 and A2 (2026-11-10).
- **Verification culture:** every DSP behaviour has an automated check; independent references are preferred; goldens are never regenerated to pass.

## 2. Knowledge inventory (changes since round 1)

| K | item | source | status |
|---|---|---|---|
| K15 | Provisional synthesis cost at L_p = 0.31·T60 + 0.1 s, per emitter: 18 ms (48 kHz, T60 2 s) and 47 ms (96 kHz, T60 2 s); 121–129 ms at 48 kHz and 325–334 ms at 96 kHz for T60 ≥ 8 s. Full synthesis is 0.75–1.6 s per emitter. Per instance at 96 kHz / T60 ≥ 8 s: about 0.5–0.65 s [Inf, file 8]. | file 8, this box | **known** (this box). Three-OS figures come in the condition 9 packet. |
| K17 | L_p for EDT within 5 % | derived below from Vorländer §6.4.1 Eq. 6.4 and the EDT definition; agrees with interrogator row 25 and Seats 3 and 9 | known (derived) |
| K18 | Prefix normalisation error | derived below, using the code fact that exact bands are normalised by realised energy over the whole length (`NoiseTail.cpp` L140–151) | known (derived; the A4 test checks it) |
| K19 | What separates a P mismatch from rounding | Seat 2 r2, and interrogator row 04 from the code: P carries engine constants that are in neither S nor E | known: **not rounding-only across builds**. Within one build at an fs change it is rounding only (Seat 2, `Engine.cpp` L318–321). |
| K9/K10 | Host tolerance of the restore; offline signalling | researcher F8–F19 | under-informed. These trigger reversal; they do not change the winner (§5.4). |

**K17 working.**
- Tail energy decays as e^(−kt/T60) with k = 6 ln 10 = 13.82.
- Truncated at L, the normalised EDC (Eq. 6.4) is (e^(−x) − a)/(1 − a), with x = kt/T60 and a = e^(−kL/T60).
- EDT is 6 × the time to −10 dB (§6.4.1). For EDT ≥ 0.95·T60, the −10 dB point needs x ≥ 0.95 ln 10 = 2.187.
- Then e^(−x) ≤ 0.1122, so 0.1 + 0.9a ≤ 0.1122, so a ≤ 0.0136, so kL/T60 ≥ 4.30, so **L ≥ 0.3113·T60**, i.e. 18.7 dB of decay.
- Seat 1's own rule (fade start at the −10 dB point, T60/6 ≈ 1.33 s at 8 s) gives a = 0.10 and EDT ≈ 0.72·T60 (−28 %). It fails Seat 1's own 5 % condition, so the stricter rule is used.
- Truncation loss over the whole tail is 10·log(1 − 0.0136) = −0.06 dB, well inside Seat 1's 1 dB.

**K18 working.**
- Proposed normalisation: divide the prefix by √(E_p/f_b). E_p is the realised prefix energy before the fade. f_b = (1 − e^(−k·L_f/T60_b))/(1 − e^(−k·L/T60_b)) is the expected prefix share of the full length L.
- The ratio of the exact amplitude to the provisional is then 1 + (1 − f_b)·δ, where δ is the relative deviation of the realised remainder from its expectation.
- With 1 − f_b ≤ 0.0136 (K17) and |δ| ≤ 1, the deviation is ≤ 10·log(1.0136) = 0.06 dB.
- This is not upward renormalisation: the prefix carries its share f_b, never the full energy (Seats 1 and 9).
- With plain expected-energy normalisation the deviation would be the realisation's own energy deviation. Seat 3 put that at [Hyp] up to about 1 dB at 63 Hz.

---

## 3. D-C1: the provisional-to-final step (AX47)

**Answers to the interrogator:**
- **Row 12 / Q3.** Both kinds of bound are now stated:
  - hard and asserted for sources bounded by construction or by the deterministic A4 test;
  - statistical (p95 per band) for the 07c-2 stage-1 source, where the test asserts the gate and records the steps.
  - Seats 1 and 9 each accepted it as p95 in their own words ("1.96 × 0.5 dB = 0.98 dB ≤ 1 dB p95 per band", 6-seat1-r2; "p95 ≈ 0.98 dB", 6-seat9-r2).
- **Row 13 / Q2.** The cell is the seat's, not mine. Seat 5 r2: "C5′ (AX47): 1/1, confirmed … the admissible sources are bounds known at design time rather than a runtime check, which addresses my C2 objection."
  - Seat 5's C2 objection was against a run-time guarantee (3-seat5 L36). The revised text claims none for class (c), whose mechanics are C1/C3's (measured after, recorded), which Seat 5 rated 0/0 and 0/1.
  - Ordering if S5 were 2/2: C5″ max 2 with sum 11, C3 max 2 with sum 10, so C3 would win. At the seat's own 1/1, C5″ has max 1 and wins at step 3.
- **Row 14.** Seat 6 r2 rated C5′ 0/1 and kept its reason, so the rating stands. The disagreement goes under the strongest objection. Under B4-G′ (§4) no 07c-1 load takes an unprompted step, which meets Seat 6's condition in fact.
- **Row 17.** Corrected: Table 6.1 jnds come "from laboratory and real-room tests; paradigm not stated".
- **Row 21 / PRD.** NFR-3 and FR-SIM-6 are removed. The PRD check is FOR MAISARA FM-4.
- **Row 22.** "About 3 cycles" is withdrawn. The reason is Seat 1's: the IR is linear and deterministic, which makes it the primary statistic. Seat 1 confirmed this and asked that it be measured over the tail window, which is adopted.

**Tension map** (now/later; seats 2, 4 and 8 NOT MY MATTER = 0/0):

| opt | S1 | S3 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|
| C1 | 1/2 | 1/1 | 0/0 | 1/2 | 0/0 | 1/2 | 2 | 11 |
| C2 | 0/1 | 1/2 | 2/2 | 0/1 | 1/1 | 0/1 | 2 | 12 |
| C3 | 0/1 | 1/2 | 0/1 | 0/1 | 1/1 | 0/2 | 2 | 10 |
| C4 | 2/**3** | 1/1 | 0/1 | **3/3** | 0/1 | 2/2 | veto | — |
| **C5″** | 0/1 (r2: B4-G 0/1; AX47 reading confirmed with the tail-window correction) | 1/1 (read from conditions: equal-gain met) | 1/1 (r2 confirmed) | 0/1 (r2) | 1/1 (r2) | 0/1 (r2 B4-G 0/1; r1 C2) | **1** | **9** |

**Working:**
1. Bounds: none broken.
2. C4 out on vetoes (S1 later 3, S6 3/3).
3. Worst-off: C5″ max 1 against 2 for every other option.
4. Nothing to compose.
5. Sum 9 (not needed).

**DECISION D-C1: C5″ (AX47 text in §7).**

**Load-bearing claims:**
- **D1-L1:** Table 6.1 gives G and C80 jnd 1 dB and EDT 5 %, at 500–1000 Hz.
- **D1-L2:** a tail step x moves G (Eq. 6.5) and C80 (Eq. 6.7) by at most x (row 16 CORRECT).
- **D1-L3:** the provisional step is ≤ 0.06 dB by design (K18) and ≤ 1 dB asserted.
- **D1-L4:** for class (c), p95 = 1.96 × 0.5 = 0.98 dB per band. This assumes a zero-mean normal step with sd ≤ SE; it is arithmetic, not corpus (row 11), and 07c-2 records the realised distribution and the family-wise share.
- **D1-L5:** Seat 5's cell is in its own r2 words.

**Future-debt register:**

| seat | commits | undo cost | evidence | repaid |
|---|---|---|---|---|
| S1 1 | 1 dB with no within-stream study (R4) | AX47 → 0.5 dB | 07c-2 self-ABX (16 trials, capped layout-4 scene, noise and speech) | ABX done |
| S3 1 | refusal-path tests; ebar of the played decay | test edits | 07c-2 | tests green |
| S5 1 | measured step and counter on the builder thread | none | 07c-1 A4 | green |
| S6 1 | automation-driven steps; the 07c-2 load fallback | — | Phase 10; 07c-2 loop | Seat 1 ruling; 07c-2 decision |
| S7 1 | a refusal path to maintain; the public testing record | — | 07c-2 | — |
| S9 1 | the gate's rejection rate in the occupied class (layouts 4/5) | — | 07c-2 stage-1 times | 07c-2 packet |

**Strongest objection:** Seat 6's later 1 depends on 07c-2's load fallback. That fallback is still contested: Seat 1 says take the step; Seats 6 and 9 say never at load. It is now bound so that it can never be early-only where a tail exists.

**Confidence:** medium (one cell read from conditions; K8′ is uninformed). **Reversal:** the 07c-2 ABX detects a step below 1 dB; the bound then becomes 0.5 dB.

---

## 4. D-C2: the interim level (AX48, part B)

**Answers to the interrogator:**
- **Rows 08, 09 and 23 / Q1** (no level at a keyless load). I withdraw "a v1 state is not bound" and adopt the interrogator's reading: condition 9 binds every load of a scene that renders a tail, whatever the state version.
  - The early-only gap (K1) carries 3s: Seat 3 r2 rates B1 alone 3/1 ("At load there is no level, so no tail"); Seat 9 r2 rates D1 at load 3/3; Seat 1 r1 rated it 3/3.
  - So keyless loads take Seat 5's way (b): a **synchronous stage-1 (A) solve only where no IrSet is current and no saved E_b matches**. In 07c-1 that solve is the final, so the step is 0.
  - This amends A2 / AQ10 (C) for that path only: FOR MAISARA FM-3.
  - Undo or preset recall onto a keyless state while an IrSet is current stays fully in the background, with no synchronous solve.
- **Row 07.** Seat 9 r2: "B4-G: 0/1. It meets my round-1 condition". Its remaining condition (per emitter and per band over 500 Hz–2 kHz) is met by the all-band, per-emitter gate.
- **Row 10.** Moot: no load is left without a level.
- **Row 29.** Restated: K4 is single-solve CI timings, PROVISIONAL with n = 1–2. The synchronous wait at 4 and 8 instances includes the gate queue (about 8 × 131 ms ≈ 1 s [Hyp], Seat 5); it is printed in the new record (h).

**Keyless-load sub-matter:**

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| K1: early-only until the background solve | **3/3** (D1 at load) | — | **3**/1 (B1 alone, r2) | — | 1/1 (r2 (a)) | 2/2 (A0, r2) | — | — | **3/3** (r2) | veto | — |
| K2: synchronous stage-1 solve at keyless loads | 0/1 rfc | 0/1 rfc | **2/2** (taken from A0 r2: the same synchronous solve at load) | 0/0 rfc | 1/1 (r2 (b)) | 1/1 rfc (no load gap or step; load time handed to S5/S7) | 1/1 rfc (R3 debt as in D3) | 0/1 rfc (r2: room present from the first IrSet) | 0/1 rfc (honest inputs) | 2 | 14 |

(rfc = read from the seat's stated conditions.)

**Whole options, each with K2 at keyless loads** (per-seat maximum of the option's r2 cells and K2):

| opt | max | sum |
|---|---|---|
| **B4-G′** (B4-G + K2) | 2 (S3) | 15 |
| B4 + K2 | 2 (S1, S3, S9) | 17 |
| B2 + K2 | 2 | ≥ 18 |
| B1 alone; B3 | out (bound and veto) | — |

**DECISION D-C2: B4-G′ (AX48 text in §7).**
- Edits, `reset()` and prepare hold the previous E_b; the specular part is recomputed from the new ISM (B1′). The interim amplitude uses the ebar of the unit decay actually played (Seat 3 r2).
- A keyless load with no IrSet current runs the synchronous stage-1 solve (K2).
- A keyless restore with an IrSet current runs everything in the background.
- From 07c-2, stage 1 at load is admissible only under AX47 (c). The inadmissible case is a 07c-2 loop item, bound to meet AX47, conditions 5 and 9, and never early-only.
- Never the AX16 level.

**Load-bearing claims:**
- **D2-L1:** no generic AX16 predictor exists (B3 is out on vetoes anyway).
- **D2-L2:** K4.
- **D2-L3:** in 07c-1 the stage-1 solve is the final, so the keyless step is 0 (AX41: W_max stays at (A)).

**Future-debt register:**

| seat | commits | undo cost | evidence | repaid |
|---|---|---|---|---|
| S3 2/2 | a synchronous solve at keyless loads | revert to background once a level source exists (07c-2 loop) | record (h); 07c-2 stage-1 times | 07c-2 decision |
| S5 1 | A2 exception, gate queue on the host thread | FM-3 reversal | record (h), condition 11 trace | Phase 13 host matrix |
| S6 1, S7 1 | load time at 8 instances | — | record (h); R3 trace | Phase 13 |
| S1, S2, S4, S8, S9 1 | gate, fallback, interim parity | — | 07c-2 | 07c-2 packet |

**Strongest objection:** Seat 3's 2/2, carried over from A0. It holds because the only alternative (K1) is vetoed, and keyless loads are team-only before release (v1 states; pre-raise v2 states). After release they are governed by AX48's dated policy.

**Confidence:** medium-low (six cells read from conditions; S3 carried from A0). **Reversal:** record (h) shows the 8-instance keyless restore past the AX38 4c rule, or a seat rates K2 3.

---

## 5. D-C3: saved E_b (AX48, part A) and D-C9: the interim tail (AX49)

### 5.1 D-C3

**Answers to the interrogator:**
- **Rows 04–05 / Q4.** Nothing makes it rounding-only across builds (K19). **The clause is dropped.** Any mismatch in a key part makes the load keyless (K2). So a reopen on another OS or at another fs now takes a synchronous stage-1 solve, with step 0 in 07c-1.
- **Seat 2's fixture condition** (one AX22-fallback scene and one air-dominated scene) is adopted anyway, because it hardens E. E is stored as two parts, E_prec and E_model (Seat 2's split): this keeps the post-release policy open without a v3.
- **Seat 7's proviso** is adopted.
- **Rows 06 and 28.** The repayment tests are now listed in the phase-file edits (§8).

| opt | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|---|
| A0 | 1/2 | 0/1 | 2/2 r2 | 1/2 | 0/1 | 2/2 r2 | 0/2 | 1/2 | 1/1 | 2 | 23 |
| **A1′** | 0/0 | 1/1 (with its r2 fixture condition) | 0/1 r2 | 0/1 r2 | 1/1 | 0/1 r2 | 1/1 r2 (proviso adopted) | 0/1 r2 | 0/1 | **1** | **11** |
| A2+cond. | 0/1 | 1/1 | 0/1 | 0/1 | 1/1 | 0/1 | 1/2 (read, r1) | 0/1 | 1/1 | 2 | 14 |
| A3 | — | — | — | 1/**3** | — | — | — | — | — | veto | — |

**DECISION D-C3: A1′.** Worst-off 1.

**Load-bearing claims:**
- **D3-L1:** `bandsDiffuse` is fs-free up to rounding (Seat 2, from the code).
- **D3-L2:** with the clause dropped, a saved E_b is used only when every part matches, and then the solve is bit-identical (step 0, no switch).
- **D3-L3:** before release there are no customer projects (phase-13-2 scope 1; file 47 §4 (iii) 1).

**Future-debt register:**

| seat | commits | undo cost | evidence | repaid |
|---|---|---|---|---|
| S2 1 | key completeness | v3 | 07c-2 W_max raise | fingerprint tests green |
| S3, S6, S8, S9 1 | E-mismatch reopen of customer projects | — | first post-release E change | board decision, due before that build |
| S4 1 | mode-independent key | v3 | Phase 09 | other-mode restore test |
| S5 1 | v2; a v1 build rejects v2 | — | release | Phase 13 compatibility notes |
| S7 1 | the proviso (build blocked until the decision exists) | — | first post-release E change | phase-13 line |

**Confidence:** medium-high. **Reversal:** the 07c-2 solve time at (C), or the post-release policy decision.

### 5.2 D-C9

**Answers to the interrogator:**
- **Row 24 / Q5 (b).** Seat 3 never rated the synchronous placement at load. That cell is now marked "read from conditions" (r1 D3 conditions plus r2 L_p and fade), 1/1. Seat 3's own 2/2 on T60 edits is entered as given.
- **Row 25.** L_p is set by K17. K15 is now measured.
- **Row 27.** PRD lines corrected (§9).
- **Row 26.** The synchronous provisional re-enters the restore gate: FOR MAISARA FM-2.
- **My round-1 reversal "≤ 0.5 s per call" misread Seat 5.**
  - Seat 5's trigger was "R1 shows a host limit ≤ 0.5 s per call" (3-seat5 L56), and R1 found no documented host limit (F9–F12).
  - Seat 5 r2 says the threshold is read "on 8 instances restored in sequence", pending R1 and R3.
  - Measured locally, the per-instance restore is about 0.65–0.8 s [Inf], so the r1 text as written would have fired. It is replaced by the triggers below.
- **Seat 3's T60-edit condition (submit the ISM at once and bridge with D5).**
  - Seat 3 rates it 1/1. Seat 9 rates D5 on T60 edits 2/2 (r2), and Seats 1, 6 and 8 rated D5 with a later or now of 2.
  - So both the bridge and the edit alternative have max 2 with higher sums.
  - My one allowed composition, D5 only for edits within 5 % (Seat 9's condition), leaves Seat 3's 2 on larger edits, so it does not lower the max.

| opt | S1 | S3 | S4 | S5 | S6 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| D1 at load | 3/3 | 3/2 | 2/2 | 1/2 | 3/3 | 2/2 | 2/2 | 3/3 | veto | — |
| D2 (edits) | — | 3/3 | — | — | — | — | — | — | veto | — |
| D4 assembled / unit decays | 0/0 | 1/2 | 1/3 / n.r. | 2/2 | 0/1 | 2/2 | 1/2 | 0/1 | veto / 2 | — / ≥ 21 with edits |
| D3\* load + D5 edits (Seat 3's alternative) | 1/2 | 1/1 | 1/1 | 1/1 | 1/2 | 0/1 | 2/1 | 2/2 | 2 | 20 |
| **D3\*′** | 1/1 r2 | **2/2** edits r2; load 1/1 rfc | 1/1 r2 (+M) | 1/1 r2 (gap closed by K2) | 1/1 r2 (+ truncation check) | 1/1 r1 (see §6) | 0/1 r2 | 1/1 r2 (conditions met) | **2** | **17** |

Seat 2 answered NOT MY MATTER: 0/0.

**DECISION D-C9: D3\*′ (AX49 text in §7).**
- **Load path:** synchronous wherever no IrSet valid at the current fs is current. A keyed load plays at the saved E_b; a keyless load at the synchronous stage-1 level.
- **Edit path:** in the background; the current IrSet plays until ISM plus provisional are ready.
- **L_p rule:** fade start L_f = 0.312·T60_max, fade 0.1 s.
- **Normalisation:** K18.
- **Handover:** equal-gain to the exact tail. Offline never uses the provisional.

**Load-bearing claims:**
- **D9-L1:** K2, the code fact: one PCG stream; output j depends on noise j…j+2h.
- **D9-L2:** K17 (Eq. 6.4 working).
- **D9-L3:** K18.
- **D9-L4:** K15, measured.
- **D9-L5:** the keyed restore at about 0.65–0.8 s per instance [Inf] stays inside the AX38 4c rule (14 × worst ≤ 30 s gives 11.2 s, about 2.7× headroom).
  - From the pre-07c split (synthesis 95.5 % of restore) and the measured ratio of provisional to full cost (0.20–0.21), the keyed restore ≈ 0.24 × the pre-07c restore. On macOS that is ≈ 0.62 s, and 14 × gives ≈ 8.7 s [Inf]. CI confirms it.

**Future-debt register:**

| seat | commits | undo cost | evidence | repaid |
|---|---|---|---|---|
| S3 2/2 | the ISM waits max(0, t_prov − t_ISM) on T60 edits (about 0.2–0.25 s at 8 s) | switch to the bridge (Seat 3) | record (g) | Phase 10 split update (AX38 (v)) |
| S1 1 | truncated late tail audible for about 3 s [Hyp] | — | L4 listening item | Maisara's L4 |
| S4 1 | per-mode coherence; M | — | Phase 08/09 | 08/09 checks |
| S5 1 | about 0.65–0.8 s per instance synchronous at the worst corner; R2 | — | condition 9 packet, record (h), condition 11 trace | Phase 13 host matrix |
| S6 1 | waits on edits; truncation | — | record (g); A4 | Phase 10 |
| S7 1 | R3 dialogs at 8 instances | — | trace | Phase 13 |
| S8 1 | realtime captures print the provisional | — | trace | Phase 13 |
| S9 1 | L_p and normalisation as stated | — | A4 | green |

**Strongest objection:** load time at 8 instances, about 5–6.5 s in sequence at 100 m / 96 kHz / T60 ≥ 8 s [Inf]. That is past Windows' 5 s not-responding criterion if a host restores sequentially on its UI thread outside startup processing (F13).
- It holds because the pre-07c figure is 20–25 s, every alternative without a veto costs as much or more, and the AQ10/H1-F1 30 s convention is met.
- It would not hold if the condition 11 trace shows such a dialog (reversal 2).

**Reversals:**
1. The restore gate fails on any OS with the provisional included. Remedy order: the constructor-spectra cache (the recorded alternative, bit-identical), then back to the board.
2. The condition 11 trace shows a host hang dialog, not-responding state or time limit reached by an ≤ 8-instance restore. Back to the board with Seats 5 and 7.
3. A common host does not signal offline by default. Re-convene Seat 5.
4. Seats 5 or 7 rate 3 on K15 (§6). Then NEEDS MAISARA case (c).

**What waits for a measurement this phase makes:**
- the three-OS restore gate, keyed and keyless (condition 9 packet, re-pin);
- record (h);
- the A4 provisional tests.

D3\*′ stands until these arrive.

**Confidence:** medium-low.

---

## 6. Round-3 confirmations (run in parallel with the interrogator; decisions stand meanwhile)

| seat | what to confirm | what a change would do |
|---|---|---|
| S5, S7 | D3\*′ on the measured K15 (about 0.65–0.8 s per instance; 8 in sequence about 5–6.5 s [Inf]) | a 3 → NEEDS MAISARA (c); a 2 leaves the winner unchanged |
| S3 | the K2 cell (taken from A0) and the D3\*′ load cell (read from conditions) | — |
| S1, S9 | L_f = 0.312·T60_max in place of Seat 1's −10 dB rule (K17); K18 normalisation as "no compensation gain" | — |
| S6 | the truncation check as worded in AX49 | — |

---

## 7. Exact rows for BUILD_PLAN §2

**AX18: append before "Amended by…":**
> **Same-scene steps (phase 07c-1 loop 2026-11-12; FOR MAISARA FM-1).**
> - An IrSet replacing an interim IrSet of the same scene, same `tailSeed`, same emitter streams and same fs is joined **equal-gain**. This covers a saved, held or stage-1 E_b to the final level, and the AX49 provisional tail to the exact tail.
> - The early parts are identical. The tails share the band noise up to rounding, because `BandNoiseGenerator::make` draws one PCG stream and output j depends on noise j…j+2h only (from the code).
> - They differ only by a normalisation gain (AX49) and by the exact tail's extension past L_p. That extension fades in from nothing, so the law is immaterial there.
> - Hence ρ = 1 for level-only steps, and ρ = √f ≥ 0.993 for the provisional (f ≥ 0.986 is the prefix share of the exact tail's energy). Both are above 0.414.
> - Equal-power would lift the mid-fade by 10·log10(1+ρ) ≈ +3.0 dB (Eq. 4.15 cross term). Equal-gain gives 10·log10((1+ρ)/2) ≈ 0 dB and never exceeds the louder endpoint.
> - A T60-changing edit (same noise, new envelope) keeps the existing equal-gain edit law.
> - A `tailSeed` or fs change gives unrelated tail noise: equal-power. Seats must match between provisional and exact per output (`tailSeedForOutput`, Phase 08/09).
> - The first IrSet after a restore fades from silence, so the law is immaterial there. A restore over a current IrSet of another scene, and the output-mode switch, stay equal-power.
> - `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`

**AX47:**
> **Interim-to-final step (D-C1; Seat 1's ruling).**
>
> **Bound.** For one scene, a step from an interim IrSet to a later one changes the tail level by at most **1 dB in each of the 8 octave bands (63 Hz–8 kHz)**. The level is measured per band over the tail window: t_mix to the end; for a provisional tail, the common window from t_mix to its fade start. G and C80 then move by at most 1 dB.
>
> **Sources and the kind of bound each carries:**
> - **(a) By construction, asserted per step:**
>   - a saved E_b whose AX48 key matches in every part (step 0, bit-identical, no switch);
>   - the synchronous stage-1 solve at a keyless load (AX48; in 07c-1 it is the final: step 0).
> - **(b) By deterministic test, asserted on the A4 set (several seeds, 48 and 96 kHz):** the AX49 provisional against its exact tail. Common-window level ≤ 1 dB per band; truncation loss over the whole tail window ≤ 1 dB; EDT within 5 % at 500 and 1000 Hz, on the whole IR against the exact IR.
> - **(c) Statistical, from 07c-2:** the stage-1 (A) estimate is admissible only when its achieved SE ≤ 0.5 dB in every band for that emitter (AX41 diagnostics; NFR-8). That is a per-band step within 1 dB at the 95 % level (1.96 × 0.5 = 0.98 dB; normal approximation, sd ≤ SE). The test asserts the gate and records every step and the share of steps above 1 dB in any band. It does not assert every step ≤ 1 dB.
>
> **Measurement.** Every step is measured on the builder thread and recorded: diagnostic plus counter, never in the callback. Wet pink-noise and speech renders check that no mid-fade value exceeds the louder endpoint.
>
> **Scope.** Excludes steps that follow a B1′ hold (edits, `reset()`, prepare; AX38 (iv) staleness records). These are recorded. Same-scene steps are equal-gain (AX18).
>
> **Deferred to 07c-2's loop.** The load source when stage 1 is inadmissible. It must meet this row, conditions 5 and 9, and never give an early-only first IrSet for a scene with a tail.
>
> **Reversal.** If the 07c-2 self-ABX (16 trials, capped layout-4 scene, noise and speech) detects a step below 1 dB, the bound becomes 0.5 dB.

Rationale column:
- Vorländer Table 6.1 (jnd G 1 dB, C80 1 dB, EDT 5 %, 500–1000 Hz; "laboratory and real-room tests", paradigm not stated); researcher R4: no within-stream study.
- Eq. 6.5 and 6.7: a tail step x gives at most x.
- Researcher D1: 0.53 dB at D/R 0 dB, 0.92 dB at −10 dB. Zotter & Frank §4: < 0.5 dB audible in mono noise. Residual accepted by Seat 1.
- FOR MAISARA FM-4; board D-C1.
- Phases: 07c-1, 07c-2, 10.

**AX48:**
> **Saved diffuse level and interim level (D-C3, D-C2).**
>
> **State.** `pluginStateVersion` 2 adds, per emitter, `bandsDiffuse`: 8 doubles in reference units, never amplitudes or E_target, stored as hex IEEE-754 bits. The key has four parts:
> - **P:** canonical hash of the `DiffuseProblem` after ISM planning;
> - **S:** canonical hash of the effective scene without `outputMode`, `hrtfId` and `tailSeed` (AX40, AX44);
> - **E_prec:** hash of `DiffuseLimits` (W_max, n\*_max, SE_target);
> - **E_model:** the estimator-version id. It is bumped with every D5-golden regeneration and whenever E_b on a fingerprint fixture changes with `DiffuseLimits` unchanged. A CI fingerprint test fails otherwise. The fixtures are the gated scenes, one scene that triggers the AX22 ISM fallback, and one air-dominated scene.
>
> **Keyed load:** P, S, E_prec and E_model all match. The saved E_b is the interim. The background solve always runs and is bit-identical (no switch; AX47 step 0).
>
> **Keyless load:** any mismatch, or a v1 state. The saved E_b is not used.
> - With no IrSet current: the stage-1 (A) solve runs **synchronously** on the restore thread inside the AX38 gate (FOR MAISARA FM-3). In 07c-1 it is the final. From 07c-2 it is admissible only under AX47 (c).
> - With an IrSet current (undo, preset recall during playback): everything runs in the background and the current IrSet plays.
>
> **Edits, `reset()`, prepare:** hold the previous E_b, with the specular part recomputed from the new ISM (B1′). The interim amplitude uses the ebar of the unit decay actually played. Never the AX16 level.
>
> **Not saved:** no tail waveform or IR.
>
> **Engine-mismatch policy.** Any mismatch is keyless until a board decision, which falls due before the first post-release build that changes E_prec or E_model.
> - After the first public release, a fingerprint failure blocks the build until that decision exists. Bumping the id alone does not clear it.
> - Inputs recorded for that decision:
>   - Seat 7: saved E_b authoritative (NFR-6, FR-LIC-3, NFR-7);
>   - Seat 2: only on an E_prec-only mismatch, with the diagnostics travelling with E_b;
>   - Seat 9: only with a CI-certified |ΔE_b| ≤ 1 dB per band at 500 Hz–2 kHz on the validation set;
>   - Seat 5: an S-keyed cache that survives edit and undo, the same rule offline, and a render-log line;
>   - Seat 6: no load gap or step.
>
> **Tests:**
> - v1 fixtures load, keyless;
> - v2 fixtures: "loads; any key-part mismatch → keyless synchronous stage-1 solve";
> - the key-match test builds its state in-process;
> - a keyless restore's first IrSet carries a tail;
> - a v2 state restored in the other `outputMode` uses the saved E_b bit-identically;
> - a change of output mode, HRTF or seed never re-solves.

Rationale column:
- Seat 2's code facts; interrogator P07C1-04 (P not rounding-only across builds).
- Minimum tension, files 3, 6 and 9 of this loop; Phase 07 state rules.
- Phases: 07c-1, 07c-2, 08, 09, 12, 13.

**AX49:**
> **Interim tail while the exact synthesis is pending (D-C9).**
>
> **What it is.** A provisional tail from the same `BandNoiseGenerator`, seed and emitter stream as the exact tail. It is cut at fade start **L_f = 0.312·T60_max** (≥ 18.7 dB of decay in every band; EDT within 5 % by Eq. 6.4), with a 0.1 s fade, so L_p = L_f + 0.1 s (never beyond the exact length).
> - Each band is normalised by √(E_p,b/f_b). E_p,b is the realised prefix energy before the fade; f_b = (1 − e^(−13.82·L_f/T60_b)) / (1 − e^(−13.82·L/T60_b)), with L the exact length.
> - The provisional is never scaled to make up the energy lost past L_p.
> - It plays at the AX48 interim level, with the amplitude from the ebar of the played decay.
>
> **Where it is built:**
> - **Synchronously**, with ISM + matching + mix, wherever no IrSet valid at the current fs is current: project load, first restore, prepare with an fs change. Every load of a scene with a tail therefore starts with a tail (condition 9).
> - **In the background** wherever an IrSet is current: undo or preset recall during playback, T60-changing edits. The current IrSet plays until ISM and provisional are ready, and record (g) prints the added ISM wait.
>
> **Unchanged:**
> - a restore of a scene equal to the current one keeps the current IrSet;
> - position-only edits keep the cached unit decays (AQ4);
> - `reset()` follows condition 10;
> - an output-mode switch reuses the cached unit decays and never waits for a synthesis (Seat 4 M).
>
> **Handover and offline:**
> - The exact tail replaces the provisional with one AQ4 equal-gain crossfade (AX18).
> - Offline renders, bounces in hosts that signal offline, and `render_cli` never use it (AX5, condition 6).
> - It runs outside the diffuse gate.
> - An interim submit never records its generation as handled. Every submit passes `decide()` under `stateMutex_` with a monotonic (generation, stage) check.
>
> **Acceptance:**
> - AX47 (b) on the A4 set plus the 100 m low-α cube, at 48 and 96 kHz;
> - truncation depth at L_f ≥ 18.7 dB in every band, asserted (Seat 6);
> - a `[pipeline]` test shows offline bypasses it;
> - its cost is printed per emitter and per instance at 1, 4 and 8 instances, in records (c), (d), (f) and (h).
>
> **D1 (early part alone)** only for tailless (AX22 fallback) scenes.
>
> **Reversal:**
> - the AX38 4c restore gate fails on any OS with the provisional included;
> - the condition 11 trace shows a hang dialog, not-responding state or time limit reached by an ≤ 8-instance restore;
> - a common host does not signal offline by default.
>
> Any of these sends it back to the board. The first remedy is the constructor-spectra cache (recorded alternative).
>
> **Recorded for Phase 10:** D5, the D5 bridge (Seat 3), and D6.

Rationale column:
- Code facts K2 and K3; K15 (review file 8); K17 (Vorländer §6.4.1 Eq. 6.4); K18.
- D1, D2 and D4 vetoed.
- FOR MAISARA FM-2.
- Phases: 07c-1, 08, 09, 10, 13.

**AX38 4c and AQ10:** apply FM-2 and FM-3 wherever the H1-F2 sentence "after both moves the restore gate measures ISM + matching + mix (≈ 0.15 s at 96 kHz) and passes a worst-of-10 rule with 10–20× headroom" appears. Use the replacement under phase-07c-1 condition 9 below, with both AMENDS lines.

## 8. Phase-file edits

**phase-07c-1:**
- **A1:** cite AX47–AX49 and the AX18 amendment.
- **A2:** "Restore, prepare and `reset()` never run the diffuse solve synchronously, except the stage-1 (A) solve at a restore with no IrSet current and no saved E_b whose AX48 key matches (FM-3). The restore gate (AX38 4c) passes measuring the keyed restore as ISM + matching + the AX49 provisional tail + mix (no solve, no exact unit-decay synthesis) and the keyless restore with the stage-1 solve added, both under the worst-of-10 rule…" The rest is unchanged.
- **Condition 9:** "after both moves the restore gate measures ISM + matching + the AX49 provisional tail + mix (keyless: plus the stage-1 solve, AX48) and passes the worst-of-10 rule; headroom as measured (AX49; review file 8)". The interim tail is AX49.
- **Condition 7's re-pin:** covers both restore forms.
- **New record (h):** keyed and keyless restores of 1, 4 and 8 instances in sequence on one thread, at 100 m, 48 and 96 kHz, on three OSes. Printed, with per-instance time until audible.
- **A4:** add the AX47 tests (tail window, common window, the classes, Seat 1 items 1–2), the AX49 acceptance and BRAS CR3 (Seat 9).
- **A7:** state v2 per AX48.
- **A8:** add the other-`outputMode` restore test, and the keyless first-IrSet-carries-a-tail test.
- **F3/F5:** cite AX47 and AX48.
- **New listening item L4:** "Reopen a saved 100 m project and play at once: the tail is there from the start; no level jump when it settles; in long rooms the tail may sound shorter for the first seconds."

**phase-07c-2:**
- AX47 (c) gate, with its family-wise record.
- Decision item: the load source when stage 1 is inadmissible, bounded as in AX47.
- The W_max raise changes E_prec, so pre-raise v2 states become keyless.
- Verify Seat 2's prefix claim (`pathCount`, `pilotStops`).
- The self-ABX: Maisara's, 16 trials, as described in AX47.

**phase-08 / phase-09:**
- The provisional gets the same per-mode decorrelation and seeds (`tailSeedForOutput`) as the exact tail.
- Extend the AX44/AX48 test to stereoSpeakers.
- A mode switch never re-solves, never waits for a synthesis and reuses the cached unit decays (Seat 4 M).

**phase-10:**
- Record (g)'s T60-edit ISM wait is an input to the AX38 (v) split update.
- D5, the D5 bridge and D6 are recorded alternatives.
- Seat 1 rules whether automation-driven steps count as unprompted under AX47.

**phase-12:** presets never carry E_b; preset validation always solves.

**phase-13-1 / 13-5:**
- The board decides AX48's engine-mismatch policy before the first post-release build that changes E.
- After release, a fingerprint failure blocks the build until that decision exists, and bumping the id alone does not clear it (Seat 7).
- The condition 11 results feed the AX49 reversal.
- Compatibility note: a v1 build rejects v2 state.
- Wording:
  - never "opens instantly";
  - "offline export waits for the final room in hosts that signal offline rendering";
  - no cross-machine bit-identity claim.
- **Memory finding (file 8 record (f), process peak delta):** 2.25 GB at 8 instances × 96 kHz → 1.11 GB at 48 kHz; it goes to Phase 13's memory budget, never an instance cap.

## 9. FOR MAISARA answers

**FM-1 (AX18 scope).**
- **Question:** does AX18's "equal-power for a state restore that changes the IR" cover the settling step after a restore?
- **Answer:** no. Same-scene interim-to-final steps are equal-gain (AX18 text in §7).
- **Rests on:** NFR-6 ("restores the scene and its render exactly"); NFR-1 (listening tests; thresholds from the Expert); her AX18 rule, which chooses the law "by IR relation".
- **Reasoning:** the two renders share their early part and their noise (ρ ≥ 0.99). Equal-power adds about +3 dB mid-fade, a value that is neither the old nor the restored render and is 3× the 1 dB jnd. Equal-gain stays between them.
- **Options:**
  - equal-power strains NFR-6 and NFR-1;
  - equal-gain serves both.
- **What would make her veto it:** the literal reading that every restore-related switch is equal-power.
- `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`

**FM-2 (H1-F2 gate content).**
- **Question:** may the restore gate include the provisional tail's synthesis, when H1-F2 says it measures ISM + matching + mix?
- **Answer:** yes. The gate measures ISM + matching + AX49 provisional + mix under the unchanged worst-of-10 / 30 s rule, and the "10–20× headroom" sentence is replaced by the measured headroom.
- **Rests on:**
  - NFR-6;
  - NFR-1, with the preamble "Accuracy is the top priority… must stay usable";
  - NFR-2;
  - H1-F2's own "never silence where a tail existed in the saved state".
- **Reasoning:**
  - H1-F2's two clauses cannot both hold. No option that survives the vetoes has a tail at load without synthesis: D1 is vetoed by Seats 1, 3, 6 and 9; D4 by Seat 4 or it costs 147 MB.
  - The PRD ranks accuracy first, provided the plugin stays usable. The keyed restore drops from about 2.4 s to about 0.65–0.8 s per instance at the worst corner, inside the 30 s convention.
- **Options:**
  - keeping the literal gate breaks NFR-6 and NFR-1 at every load;
  - the amended gate serves them and strains NFR-2 by about 0.5–0.65 s per instance at the worst corner.
- **What would make her veto it:** NFR-2's "usable" read as condition 9's 0.15 s target.
- `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**FM-3 (A2 / AQ10 (C) at keyless loads).**
- **Question:** may a load with no usable saved E_b and no current IrSet run the stage-1 solve synchronously?
- **Answer:** yes, on that path only (AX48).
- **Rests on:** NFR-6, NFR-1 / preamble, NFR-2, condition 9.
- **Reasoning:** the only alternative is an early-only room for 0.1–1 s, which carries veto-grade ratings from Seats 1, 3 and 9. The synchronous solve costs ≤ 144 ms per instance (K4, PROVISIONAL), plus the gate queue. Every keyed load, edit, `reset()` and prepare stays asynchronous.
- **Options:**
  - K1 strains NFR-6 and NFR-1 and is vetoed;
  - K2 serves them and strains NFR-2 slightly, on keyless loads only.
- **What would make her veto it:** AQ10 (C)'s "asynchronous" read as covering every restore.
- `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`

**FM-4 (D-C1 acceptance, C5″ against C3).**
- **Question:** NFR-6 favours smaller deviations. Does it point to C3 (0.5 dB)?
- **Answer:** no. AX47 at 1 dB stands.
- **Rests on:** NFR-1 ("Pass thresholds come from the Expert", which here is Table 6.1's 1 dB, Seat 1's ruling); NFR-6; NFR-2.
- **Reasoning:**
  - In 07c-1, every load source in AX47 class (a) is a 0 dB step, and the provisional is ≤ 0.06 dB by design, so C3 and C5″ give the same product.
  - They differ only in 07c-2's stage 1, where C3 rejects more estimates and so lengthens holds (NFR-2).
  - NFR-6's "exactly" is met by the settled render and by the bounce. The interim is a transient below the Expert-side threshold, and the 0.5 dB reversal is scheduled (ABX).
- **Options:**
  - C5″ serves NFR-1 and NFR-6 at the jnd;
  - C3 serves NFR-6 more tightly but strains NFR-2 in 07c-2;
  - C1 strains NFR-6 (unbounded recorded steps);
  - C4 is vetoed.
- **What would make her veto it:** NFR-6's "exactly" read as binding the interim.
- Amends nothing.

## 10. Summary

| id | decision | state | worst-off | sum | conf. | PRD bound | corpus basis | reversal |
|---|---|---|---|---|---|---|---|---|
| D-C1 | AX47 (3 classes, 1 dB in the tail window) | revised | 1 | 9 | medium | NFR-1, NFR-6 | Table 6.1; Eq. 6.4/6.5/6.7 | 07c-2 ABX → 0.5 dB |
| D-C2 | AX48 B4-G′ (synchronous stage-1 solve at keyless loads) | revised | 2 (S3) | 15 | med-low | NFR-6, NFR-8, condition 9 | — | record (h); seat 3 |
| D-C3 | AX48 A1′ (4-part key; any mismatch → keyless) | revised | 1 | 11 | med-high | NFR-6, FR-LIC-1 | — | post-release policy |
| D-C9 | AX49 D3\*′ (L_f = 0.312·T60_max; synchronous at load) | revised | 2 (S3, edits) | 17 | med-low | NFR-6, NFR-1, NFR-2 | Eq. 6.4, Table 6.1 | gate fail; condition 11 trace; R2 |
| FM-1 to FM-4 | §9 | for Maisara | — | — | medium | as cited | Eq. 4.15 | as cited |

**Challenges to settled decisions:** FM-1, FM-2 and FM-3 (§9).

### Decided for Maisara

- **AX47:** the reverb may settle by at most 1 dB per band. It is exact at every 07c-1 load, and steps that are only statistical are allowed from 07c-2 under a gate (NFR-1, NFR-6; C3 serves NFR-6 more tightly at NFR-2 cost; C1 strains NFR-6; C4 is vetoed). Seat 6 gave most: the 07c-2 load fallback is still open. In return, that fallback can never be early-only.
- **AX48:** the solved room level is saved with a four-part key. A project reopened elsewhere, or after an engine change, is solved synchronously (about 0.1 s per instance) instead of playing without its tail (NFR-6, FR-LIC-1, NFR-8; A2 is equal in 07c-1; A0 strains NFR-6 at load; A3 is vetoed). Seat 3 gave most: it carries a synchronous solve on those loads. In return, that solve is revisited at 07c-2.
- **AX49:** a reopened project has its tail from the first moment. The tail may be slightly short for the first seconds in long rooms, then settles to the exact one. Bounces in hosts that signal offline always use the exact tail (NFR-6, NFR-1, NFR-2; D1 breaks condition 9; D5 strains NFR-1 on edits). Seat 5 gave most: about 0.65–0.8 s per instance at the worst corner. In return it gets record (h) and three reversal triggers.
- **FM-1:** same-scene settling uses equal-gain. `AMENDS her decision of 2026-11-08: "accepted, merge with no ci"`.
- **FM-2:** the restore gate includes the short provisional tail. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **FM-3:** a synchronous solve runs only at loads with no usable saved level. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
- **FM-4:** AX47 stays at 1 dB rather than 0.5 dB. Amends nothing.

**NEEDS MAISARA:** none. Case (c) arises only if a round-3 seat rates 3 (§6).

Files:
- `/home/user/makroof/docs/review/phase-07c-1/5-decider-decision-r1.md`
- `/home/user/makroof/docs/review/phase-07c-1/7-interrogator-on-file5.md`
- `/home/user/makroof/docs/review/phase-07c-1/6-seat1-r2.md` … `6-seat9-r2.md`
- `/home/user/makroof/docs/review/phase-07c-1/8-orchestrator-provisional-cost.md`
- `/home/user/makroof/docs/phases/phase-07c-1.md`
- `/home/user/makroof/docs/BUILD_PLAN.md` (L115, L138, L158)
- `/home/user/makroof/src/sim/tail/NoiseTail.cpp`
- `/home/user/makroof/docs/corpus/vorlaender-auralization.md` §6.4.1–6.4.4