
# 9: Decider on M3, round 3 ruling (phase-07c-2b scope 2)

Read-only. To be saved as `/home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Re-checked this round:
- Kuttruff Eq. 5.42 (L2698).
- Eq. 5.44 (L2708). It prints r_c = (A/16π)^½ ≈ 0.1·(V/πT)^½ with Sabine's T; 0.1/√π = 0.0564.
- Eq. 5.45, and the §5.6 caveat (L2724).
- §7.4 Eq. 7.6 (L3315): |G₁|² = 1 + q² + 2q·cos(2πft₀).

**Files read:**
- Review files 2, 5, 6, 7 and 8-seat1/3/5/6/7/9, plus 4-seat7.
- `docs/validation/abx-07c-2-run-sheet.md` in full.
- BUILD_PLAN §0, AX47/AX49 (L170, L172) and §5 (L388–399).
- `phases/phase-07c-2b.md` in full and `phase-13-2.md` L20–59.
- PRD L26, 49, 54, 55, 75, 101, 105, 112, 133, 174.

## PRD digest (unchanged from file 6)

- **For whom:** producers and DJs (L17). Validation stimuli are never public copy.
- **Outcome:** NFR-1 (L105): "must match impulse responses measured in real spaces and pass listening tests".
- **Hard bounds:**
  - NFR-8 (L112): "Any valid scene renders correctly; no environment-specific code paths". This is a v1 requirement.
  - FR-3D-5 (L75), placement anywhere.
  - L54 and L133, spaces are empty.
  - Her AX21 decision of 2026-11-05.
  - AX5, and the AQ/AX rows except AX47's Reversal and design, and AX49's `render_cli` sentence and L4 sentence.
- **Ranking:** L49 and L101 rank accuracy against CPU and latency only.
- **Not bounded:** hours (L55, L174: "no fixed deadline").
- **Verification:** every DSP behaviour has an automated check, nothing is loosened to pass, and a red is a stop.

---

## Answers to the interrogator's five questions (file 7)

**Q1 (Seat 9's spread condition): conceded.**
- The equal-window reading was mine, not Seat 9's. Seat 9 was convened in R3 (8-seat9). It agrees its measure is "the per-emitter energy integrated from each emitter's own t_mix,e", and that "it fires on both_wall … at +9.39 dB".
- Seat 9 rates my handling as written **1/2** and with its conditions C-a, C-b and the item-13 line **1/1**. All three are adopted (M3-1 below).
- So the SPREAD clause **fires on both_wall** in its onset form, the S-W label now says so, and the measurement goes to Seat 2 as an NFR-8 candidate (corner/onset item, §4).
- I withdraw "Vorländer Table 6.1 jnd" as the basis of the 1 dB line (CONDITIONS VIOLATED accepted). The 1 dB is Seat 9's print threshold, "not an audibility claim" (8-seat9 §5).

**Q2 (corner item (2)): conceded.** §5 is "post-v1 backlog" ("Phase files for these get written once v1 is done", L390). Item (2) is withdrawn and replaced by a pre-v1 home (§4 below).

**Q3 (B′):**
- **Sum as read:** 17, not 19.
- **Withdrawn as unrated:** the S2 and S8 B′ cells read from L4-B reasons.
- **Seat 9 has since rated B′ itself:** "B′ is 0/0 on my criteria" (8-seat9 §7).
- **Restated floor:**
  - S1 ≥ 1, its own later 1.
  - S2 ≥ 2 and S8 ≥ 2: their L4-A reasons apply to B′.
  - S3 1/1 (stated), so 2.
  - S5 1/1, its own words, so 2.
  - S7 1/0, so 1.
  - S9 0/0, so 0.
  - The floor is **≥ 10**, against L4-A's 8.
- L4-A wins at step 3 if Seat 1's read now 2 on B′ holds, otherwise at step 5. Either way the result is the same.

**Q4 (acceptance checks):**
- Each matter below shows every surviving option, including the 13/13 split, HF-W without D, S and S′, and all three timing options.
- "Offline and shipped renders unchanged" is now cited to **AX5 and AX49**. NFR-8 is cited only for "no environment-specific code path".

**Q5 (L4 label):** Seat 9's text is adopted verbatim (M3-L4 below). Seat 9 confirms the filled text before the seal.

**Other corrections from file 7, all applied:**
- **Hours:** 3.31 h is "about 3.3 h".
- **Speech-also cost:** +15 % presentations against the split (52 → 60 per scene, 104 → 120 with detection). The +36 % figure was against unsplit.
- **Timing reversal:** frozen spec at 0/0 would win at step 3, not on sum.
- **Commutator:** measured on **four scenes and 200 stimuli**, worst 1.0004, margin ≥ 0.559 dB (file 5 L79–86).
- **857 Hz:** cite Kuttruff §7.4 Eq. 7.6 (minimum at cos = −1, f = 1/(2t₀)).
- **Kit r_c:** the manifest names its form as "0.057·√(V/T60_Eyring)". The label form is Eq. 5.44 (A/16π)^½ with Sabine's A (approximate form 0.0564·√(V/T_Sabine)).
- **V2:** Seat 1's cell is 0/0 (4-seat1 R2 (b)), so V2's sum is 12.
- **Seat 2's L4 debt row:** corrected (below).

---

## Knowledge inventory (R3)

| K | what | source | status |
|---|---|---|---|
| K1 | both_wall: own-onset L − R +9.39 dB; equal windows −0.05/−0.03 dB; t_mix,e 0.165/0.380 s | file 5 table L21 (builder measurement) | known |
| K2 | both_corner: −6.80 dB own-onset; −6.20/−6.12 dB at equal windows | file 5 L22 | known |
| K3 | s0.7 own-onset L − R **−1.23 dB** (equal windows not measured) | file 5 L23 | known; bears on C-b's scope (M3-1 (d)) |
| K4 | equal power gives equal reverberant energy density | Kuttruff Eq. 5.42; indicative at ᾱ ≈ 0.28 (§5.6) | known |
| K5 | binomial: Σ C(24,k), k = 18..24 = 190051; /2²⁴ = 0.011328; P(≥ 18/24 at p = 0.75) = 0.6074 | recomputed (Σ_{k=0..6} C(24,k)·0.25^k·0.75^(24−k) = 0.6074) | known |
| K6 | every M3-2 cell in the seats' own words | 8-seat1, 8-seat5, 8-seat6, 8-seat7; 4-seat\* | known; skip-variant cells for S5 and S7 are read (marked) and not decisive |
| K7 | fixed-sequence gating: a 0.5 dB block is unsealed only after a 0.9 dB detection in that chain | run sheet L143–145 | known |
| K8 | S′ built: α per band; T60 8.0 s at 63 Hz–1 kHz; t_mix,e,max 1.1175 s; L_f 3.6135 s; L_p 3.7135 s; L 12 s | builder facts (this brief); check: 40.31/343 + √10⁶ ms = 1.1175 s; 1.1175 + 0.312·8 = 3.6135 s | known |
| K9 | offline long IR is one full-length FFT, so the L4 arms run on the partitioned path | `OfflineRender.h` L3–7 (code); Seats 3 and 5 confirm | known |
| K10 | L4 label figures: A 20,125 m², r_c 19.95–20.0 m, d 40.31 m, diffuse D/R −6.1 dB, ᾱ ≤ 0.34 | Kuttruff Eqs. 5.44–5.45; Seat 9's working, redone: 0.0564·√(10⁶/8) = 19.94; 20·log10(19.95/40.31) = −6.11 | known (indicative) |
| K11 | fatigue in 30-presentation blocks | RQ-M3-1, [Hyp] | research gap, not decisive: 3 anchors per half void a fatigued block |
| K12 | speech stimulus length ≈ noise stimulus length | Seat 7 [Inferred] | under-informed; hours only. The builder times one speech block and L4 before the dates (Seat 7's request) |

---

## (1) M3-1: the scene, final

**Tension map** (cells in each seat's own words; Seat 8 not required, 0/0):

| option | S1 | S2 | S3 | S4 | S5 | S6 | S7 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|---|
| **V1-W + C-a, C-b, item-13 line** | 0/1 | 1/1 | 1/1 | 0/1 | 0/1 | 0/1 | 1/1 | **1/1** | **1** | **12** |
| V1-W, file 6 handling | 0/1 | 1/1 | 1/1 | 0/1 | 0/1 | 0/1 | 1/1 | 1/**2** | 2 | 13 |
| V2 (conditions met) | **0/0** | 1/1 c | 2/2 | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 c | 2 | 12 |
| Gated S-B\* | 0/1 | 1/1 c | 2/2 c | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 c | 2 | 13 |
| V3-default | 1/1 c | 1/1 | 2/2 | 0/1 c | 0/1 c | 0/0 | 1/1 | 1/1 | 2 | 14 |
| V3 as written | 1/1 | 2/1 | 2/2 | 0/1 | 0/1 c | 0/0 | 1/1 | 2/1 | 2 | 16 |
| V1 | 2/2 | 1/1 | 1/1 | 0/2 | — | — | ·/2 | 1/1 | 2 | — |
| V4 | 2/**3** | … | | | | | | | veto | — |

**Seat 9's cells, in its words:**
- File 6 handling: "1 | **2** | … a fallback could be sealed with an unlabelled spread of 9 dB".
- With its conditions: "1 | **1** | The mechanism is stated as engine behaviour, the print can see it, and M3-8 covers a rule change."

**Working:**
1. **Bounds:** none of the options breaks one.
2. **Veto:** V4 is out.
3. **Worst-off seat:** V1-W with Seat 9's conditions is the only option with max 1. Every other survivor holds a 2: Seat 3 on V2, gated, V3-default and V3 as written; Seats 1, 4 and 7 on V1; Seat 9 on file 6's handling.
4. **Compose:** this option is the composition. It adds no cost to any other seat, because the prints are kit-only and the label is text.

Steps 5 and 6 are not needed.

**DECISION M3-1 (stands, revised): V1-W, as in files 2 and 6, with Seat 9's conditions replacing file 6's (a):**
- **(a′) C-b, the seal print.** For S-W and every S-W fallback, the kit prints L − R at 1 kHz on two measures:
  - (i) integrated from each emitter's own t_mix,e to the end of the IR;
  - (ii) the equal windows [0.45, 0.65) s and [0.8, 1.0) s.
  - The SPREAD clause fires if either measure exceeds 1 dB (a print threshold, not an audibility claim). It takes the **onset form** (C-a text with the scene's values) or the **level form** (Seat 9's R2-2 text).
  - In either form the measurement goes to Seat 2 as an NFR-8 candidate (§4).
  - On both_wall it fires in the onset form (+9.39 dB).
- **(b) C-a.** The S-W label carries the onset sentence (M3-4 text below).
- **(c) The item-13 line** is Seat 9's (M3-4 below).
- **(d) Kept from file 6:** fallback labels name every face whose reflection is absent; Seat 9 confirms each filled label; if a rebuilt scene fails a seal gate, item 15 returns to the board.
- **(e) Hand-off, not a decision.**
  - The kit also prints both measures on S-B\* (print only). File 5 already gives s0.7 own-onset −1.23 dB (K3).
  - Seat 9's condition names S-W and its fallbacks, so whether S-B\*'s label takes the level form is **Seat 9's call before the S-B\* seal**.
  - No S-B\* seal happens until Seat 9 has answered.

**Load-bearing:**
- **R3-L1:** K1 (file 5 measurement).
- **R3-L2:** Kuttruff Eq. 5.42, indicative (§5.6).
- **R3-L3:** Seat 9's own cells (8-seat9 §3–4).

**Future-debt register (V1-W), file 6 rows kept, except:**

| seat | commits to | undo cost | evidence | repaid when |
|---|---|---|---|---|
| 9 | S-W's share 0.667 rests on the engine's t_mix,e onsets (own-onset +9.4 dB, stated as engine behaviour); the 0.43 ceiling binds on both_wall (0.639 against 0.589 s) | relabel and rescope, rebuild under M3-8 | each seal; O4's rebuild; 08-3; the phase-13-2 board item | C-b printed at every seal; label and item 13 carry the onset |
| 2 | receives two NFR-8 candidates (corner level, both_wall onset) | a `src/sim` change is an output change | the phase-13-2 item (§4) | board ruling there |

**Strongest objection:** Seat 9's premortem. If L's onset moves, the share falls to about 0.29.
- **Why it holds anyway:** the label and item 13 now state the dependence, C-b sees it, and M3-8 rebuilds.
- **When it would not hold:** if a `src/sim` change moves the onsets before 08-3 and nobody reprints. C-b is a seal gate print, so a rebuild cannot skip it.

**Confidence:** high. Every V1-W cell is in the seat's own words.

**Reversal conditions:**
- a seal gate fails and the fallback order is exhausted;
- a clean stimulus fails HF-W;
- Seat 9 rejects a filled label.

**Acceptance check (NFR-1 L105, FR-3D-5 L75, L133/L54, AX21 decision, L55):**
- **V1-W:** serves NFR-1 (the most sensitive measured scene plus an early-part scene before the pin, the onset dependence stated). FR-3D-5 placement. L133 labels. AX21 applied. Hours unbounded (L55).
- **V2:** NFR-1 with the same S-W scene; s < 1 evidence only after the pin. No PRD id ranks it above.
- **Gated S-B\*:** as V2, with S-B\* conditional. No PRD id ranks it above.
- **V3-default:** NFR-1 with a less sensitive scene. No PRD id ranks it above.
- **V3 as written:** NFR-1 with emitter_wall, less sensitive. No PRD id ranks it above.
- **V1:** strains NFR-1 (the least sensitive scenes come before the pin).

No PRD goal or ranked requirement points away from V1-W. Amends nothing.

---

## (2) M3-2: speech criterion and the skip

**Map:**

| option | S1 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| **B: speech also ≥ 18/24, no skip** | 0/0 | 0/1 | 0/1 | 1/1 | **1** | **4** |
| A: split, speech ≥ 13/16, no skip | 1/0 | 0/1 | 0/1 | 1/1 | 1 | 5 |
| C: B + Seat 1's skip (pre-registered) | 1/1 | 0/1 c | 0/1 | 1/1 c | 1 | 6 |
| D: B + Seat 7's skip, pre-registered (K1–K4, S1, S3; 0.5 dB locked) | **2/2** | 0/1 | 0/2 | 1/1 c | 2 | — |
| E: Seat 7's skip, ad hoc | 2/2 | **2/2** | 0/2 | — | 2 | — |
| Unsplit + C1 | 1/1 | 1/1 | 1/1 | 0/1 | 1 | 7 |
| 13/13 split | — | — | 1/**2** | — | 2 | — |

**Cells, in each seat's words:**
- **S1:**
  - B: "Tension 0/0 … I prefer it" (R2). R3: "Full design, as decided (no skip) | prefer | 0 | 0".
  - C: "My option … 1 | 1".
  - Seat 7's as written: "cannot live with … 2 | 2", because skipping 0.9 "also locks out its 0.5 dB blocks".
- **S5:**
  - B: "Prefer, 0/1".
  - Ad hoc skip: "2 | 2". Pre-registered with K1–K4: "0 | 1".
  - C is marked c. Seat 1's variant also unseals the 0.5 dB blocks without a 0.9 dB detection in that chain, which K1–K4 do not address.
- **S6:**
  - B: "I confirm … 0/1".
  - Skip "with S1–S3: 1"; "Skip without S2: 2". C meets S2, because both S-B\* chains run at 0.5 dB.
- **S7:**
  - B: "Tension now: 1 … later (debt): 1".
  - The split's later reason is replaced: "cell unchanged, reason replaced".
  - For C and D the cell is marked c. Seat 7's B reasons (+17 min in the no-detection branch now, recurring at 08-3 later) are untouched by a skip that acts only after a detection, so 1/1.

**Working:**
1. **Bounds:** none.
2. **Veto:** none.
3. **Worst-off seat:** D, E and 13/13 hold a 2 and are out. B, A, C and unsplit all have max 1.
4. **Compose:** no composition lowers the maximum below 1. The 1 is Seat 7's hours, which every option carries.
5. **Sum:** B 4 < A 5 < C 6 < unsplit 7.
   - Even if Seat 7 rated C 0/0, C would tie B at 4.
   - Step 6 would then pick B: a skip removes evidence that cannot be recovered after scoring (Seat 6: "Undoing it costs one sitting of about 1 h"; Seat 1's later 1). No-skip leaves nothing to undo.

**DECISION M3-2 (final): both chains at ≥ 18/24 in all four families, and no skip.**
- **Design, per chain, per family (F1 S-W, F2 S-B\* at 07c-2b; F3, F4 at 08-3):**
  - 24 scored trials plus 6 interleaved 3 dB anchors, 30 presentations;
  - 3 anchors in each half, break after presentation 15;
  - 0.9 dB, then 0.5 dB only after a 0.9 dB detection in that chain of that family;
  - detection at ≥ 18/24; anchor pass at ≥ 5/6, otherwise void with one rerun.
- **Rates:**
  - per chain α 190051/2²⁴ = 0.011328;
  - **per family ≤ 0.022656 (0.0227)**;
  - at 07c-2b (F1, F2) **≤ 0.045312 (0.0453)**;
  - over F1–F4 **≤ 0.090624 (0.0906)**;
  - strong control, union bound;
  - **power 0.607 per chain** at p = 0.75.
- **Item 4:** a 0.9 dB detection in any chain of any family sets AX47's bound to 0.5 dB. A non-detection never cancels a detection. A 0.5 dB detection is a class (c) finding; at 08-3 it reopens that round at the board.
- **C1 (Seat 5) attaches.** Seat 6's (i) and (iv) also apply.
- **Fallback:** if the trial count is cut (only in the pre-registration commit, before any scored trial), all four families revert to file 13's unsplit thresholds (noise ≥ 12/16, speech ≥ 13/16) with C1. Never 13/13.

**Load-bearing:**
- **M2-L1:** K5 (binomial, recomputed).
- **M2-L2:** K7, the run sheet's fixed sequence. This is what makes Seat 7's skip lock out the 0.5 dB blocks.
- **M2-L3:** the seats' own cells.

**Debt (B):**

| seat | commits to | undo cost | evidence | repaid when |
|---|---|---|---|---|
| S5, 1 | a flip can land at 08-3 | a constant change under C1 | 08-3 | C1 in place |
| S6, 1 | noise power 0.63 → 0.607 | class (c) re-decision | 08-3; Phase 13 beta | AX38 (iv) prints |
| S7, 1 | +17–34 min at 07c-2b and again at 08-3 | none, before the first scored trial | each sitting | dates in the briefs |

**Strongest objection:** Seat 7's hours, about 1 h saved in the detection branch by a skip.
- **Why it holds anyway:** every skip that saves it costs Seat 1 or Seat 6 evidence on the early-part class, at 2 for Seat 7's version as written.

**Confidence:** high. B's cells are all in the seats' own words. The read cells are on the losing rows and are not decisive.

**Reversal condition:** the trial count is cut before the first scored trial (then the fallback applies).

**Acceptance check (NFR-1 L105, L55):**
- **B:** serves NFR-1 most: both chains at power 0.607, false reversal 0.0227 per family. Hours are unbounded (L55).
- **A:** NFR-1 with speech power 0.405.
- **C:** NFR-1 with F2's 0.9 dB evidence lost in the detection branch.
- **Unsplit + C1:** NFR-1 with twice the false-reversal rate.
- **D, E and 13/13 are excluded at step 3:**
  - **D:** strains NFR-1 (the 0.5 dB bound is untested on the early-part class).
  - **E:** strains NFR-1's "pass listening tests" (no reproducible record).
  - **13/13:** strains NFR-1's detection side (noise power 0.405).

No PRD id points away from B. Amends nothing.

---

## (3) M3-L4: timing, label, flag, and the B′ corrections

**Timing map:**

| option | S1 | S7 | max | sum |
|---|---|---|---|---|
| **Built and sealed before the first scored AX47 trial** | 0/0 | 1/0 | 1 | 1 |
| Frozen spec + C1–C3 | 0/1 | 0/0 c (Seat 7's frozen-spec cell; under C1 unrated) | 1 | 1 (2 if C1 raises S7) |
| Frozen spec as written | 1/1 | 0/0 | 1 | 2 |

**Seat 1's words:** "Built and sealed … prefer | 0 | 0"; "Frozen spec plus my conditions C1–C3 … 0 | 1"; "as written … 1 | 1"; "I do not rate frozen-spec-only 0/0".

**Working:**
- Steps 1 to 3: all three tie at max 1.
- Step 5: built-and-sealed ties frozen + C1–C3 at best.
- **Step 6 (reversibility):** built-and-sealed can still be downgraded to the pre-rated frozen + C1–C3 before any score is known. Frozen spec's taint ("a failed check after the scores taints L4 as designed after the data", Seat 1) cannot be undone once scores exist.
- **Decided: built and sealed.**
- **Note, not a re-rating:** Seat 7's now 1 was the stall risk. Builder facts reduce it: S′ is built, and the flag and its tests exist.

**B′ (corrected):**

| design | S1 | S2 | S3 | S5 | S7 | S8 | S9 | max | sum |
|---|---|---|---|---|---|---|---|---|---|
| **L4-A** | 0/1 | 1/1 | 1/1 | 0/0 | 0/1 | 1/1 | 0/0 | 1 | 8 |
| L4-B | vetoed (S1, S3 and S5, later 3) | | | | | | | | |
| L4-B′ (floor) | ≥ ·/1 (read now 2) | unrated, ≥ 1/1 | 1/1 | 1/1 | 1/0 | unrated, ≥ 1/1 | **0/0** (8-seat9) | ≥ 1 | **≥ 10** (17 as read in file 6) |

**Flag:**
- Seat 5: "1/1 … 1/0 with F2′". F2′ items 1–4 are adopted, so 1/0.
- Seat 3: L4-A "1/1, confirmed", with S2, S3 and S4 stated on the partition grid. Adopted verbatim.

**DECISION M3-L4 (stands, revised):** L4-A on S′, Seat 1's chord and pass rule, and Seat 3's P1–P6, S1–S7 and N-L1–N-L3. Changes from file 6:
- **(i) Seat 3's checks on the partition grid, verbatim (8-seat3 §5):**
  - S2: identity asserted before (⌊n_on/P⌋ + ⌊n_d/P⌋ + 1)·P, compared by value with ±0 equal, never memcmp.
  - S3: each real-time render nulls against `renderOffline` of its written IR, delayed by P, at ≤ −120 dB.
  - S4: exact zero from (⌈n_end/P⌉ + K_p + 1)·P, and ≤ −120 dB re the hold in the partial block.
  - Plus an assert answering Seat 3's hand-off to Seat 5: in both arms the IR is installed in the first partition, so no AQ4 fade-in falls inside the prefix (Phase 06 behaviour, §0 row 06).
- **(ii) Flag:** F1, F2 as composed, F2′ items 1–4, and F3–F6:
  - F2′ 1: refuses `--block 0`/random; requires `--realtime-emulation` whenever `--in/--out` is given.
  - F2′ 2: both arms use the same `--block` and `--partition`, printed and recorded in the manifest.
  - F2′ 3: arm A's real-time IR equals the `assembleProvisional` `--ir` output byte for byte, tested by hash.
  - F2′ 4: F5's run-to-run bit-identity covers the real-time render.
- **(iii) Timing:** built, all checks green, sealed, and hashes in the same pre-registration commit as F1 and F2, before the first scored AX47 trial.
  - If the build stalls, AX47 listening waits, and Seats 1, 3 and 7 are re-asked, with frozen spec + C1–C3 as the pre-rated candidate.
  - A red is a stop, never loosened.
- **(iv) Label:** Seat 9's text, verbatim:

> "ax49_l4_cube: synthetic 100 × 100 × 100 m, V 10⁶ m³, every face the same α per band, scattering 0.3. Listener (50, 30, 1.7) m; emitters (45, 70, 2) and (55, 70, 2) m, each 40.3 m from the listener. T60 8.0 ± 0.1 s from 63 Hz to 1 kHz as printed by the engine (T60_max 8 s, air absorption included), shorter above 1 kHz where α is held at its 1 kHz value; per-band T60 printed. D/R at 1 kHz {printed} dB heard, against about −6.1 dB in a diffuse field at r/r_c 2.0 (r_c ≈ 20 m from A ≈ 20,100 m² including air, Sabine; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.34 is not small, §5.6). A stress geometry for AX49's provisional tail, not a room prediction or a validated preset. A = AX49 provisional tail (Engine::assembleProvisional, validation-only flag --ax49-provisional), faded over [L_f, L_p) = [{L_f}, {L_p}) s; B = full engine tail ('exact' = full synthesis, not a measurement); one tailSeed {seed} for A and B. Fully wet: the whole rendered IR (direct, early part and tail), no dry path."

  The current fill is L_f 3.6135, L_p 3.7135 (K8). Seat 9 confirms the filled text before the seal. If S applies instead of S′, the same template is used with S's values.

**Debt register:** file 6's rows stand, except these two:
- **Seat 2:** commits to "a detection sends AX49 back to the board … a reopening". Undo cost: an AX49 redesign. Evidence: the L4 result. Repaid when the Reversal is applied with 07d's candidates. The gap-and-return is not a debt row; it stays under the strongest objection.
- **Seat 5:** later 0 with F2′ (the row is withdrawn).

**Strongest objection:** Seat 2's gap-and-return, which "may be more audible than the cut itself". It is answered by S7's per-band step print and by AX49's Reversal.

**Confidence:**
- high on the timing and the flag;
- medium on the design ordering, strictly by the letter (B′ cells are floors), though no reading changes the winner.

**Reversal conditions:**
- S′ fails its asserts (then S applies, scoped);
- the flag needs a `src/sim` change;
- Seat 1's prefix check or Seat 3's S2–S4 red on a clean stimulus;
- the build stalls (re-ask Seats 1, 3 and 7).

**Acceptance check (NFR-1 L105; AX5 and AX49 for unchanged renders; NFR-8 L112 only for code paths):**
- **L4-A:** serves NFR-1. It plays the cut that AX49's Reversal names.
- **L4-B:** strains NFR-1 (cannot reach the cut). Vetoed.
- **L4-B′:** NFR-1, but mixes cut and return. No PRD id ranks it above.
- **S′:** NFR-1, with the null unscoped. NFR-8: α is iterated on scene data only, with no `src/sim` path.
- **S:** NFR-1, with the null scoped to 63 Hz depth. No PRD id ranks it above.
- **Built and sealed:** NFR-1, a test not designed after its data.
- **Frozen spec + C1–C3, and frozen as written:** NFR-1 with a taint risk or open choices. No PRD id ranks them above.
- **Flag:** offline, bounce and default `render_cli` renders unchanged (AX5; AX49 "never use the provisional", plus the validation-only exception). F4 and F5 tested. The flag lives in `src/cli` and is scene-agnostic (NFR-8). Amends nothing; FM-2′ is untouched.

---

## (4) Corner routing item (2), replaced

**What it replaces:**
- Item (2) of file 6's corner routing is **withdrawn**.
- Items (1), (3) and (4) stand. That is the PR "Follow-ups" NFR-8 report, both_corner third in the S-W fallback order with SPREAD (level form), and M3-8 on any fix.

**Why this is mine alone:** it is a plan-wording choice. It sets no outcome, threshold or phase for a fix, and Seat 2 is named owner at the home.

**PRD bound:** NFR-8 L112 ("Any valid scene renders correctly") is a v1 requirement, so the home must be pre-v1.
- The chosen home is **phase-13-2** (Lead: Seat 2; pre-release; it already treats engine output changes as golden-round changes "fixed before the first release", L23–24).
- The board there may move the item earlier through `/fix-plan`.

**Text for phase-13-2, new scope item:**

> "**NFR-8 candidates from phase-07c-2b (report only; owner Seat 2)** (phase-07c-2b decider file 9 §4; builder file 5). (a) `layout4_s1/both_corner`: emitter L (0.1 m from two walls and the ceiling) has a 1 kHz diffuse tail 6.20 / 6.12 dB below emitter R's at equal absolute windows (−6.80 dB from each emitter's own t_mix,e), where Kuttruff Eq. 5.42 expects equal reverberant levels at equal power (indicative: §5.6). (b) `layout4_s1/both_wall`: tail onsets t_mix,e 0.165 / 0.380 s; from its own onset L's 1 kHz tail energy is +9.39 dB over R's (−0.05 dB at equal times); which onset departs from the t_mix,e rule's intent (Seat 9's hand-off). Done when a board loop (Seat 2 convened; decider; interrogator SURVIVES) rules on the cause (AX40 estimator, the image-source set at a corner source, or the t_mix,e rule) and on whether a `src/sim` change follows, with no scene-specific logic (NFR-8). Any change is an output change (golden round, §6 row) and fires phase-07c-2b M3-8's trigger. The board may move this item to an earlier phase through `/fix-plan`."

**Strongest objection:** a fix found at 13-2 lands after Phase 08's golden freeze and costs a second golden round. It holds because the board may pull the item forward, and M3-8 already rebuilds any sealed scene the fix touches.

---

## (5) Hours texts (speech at 18/24 chosen, no skip)

**Arithmetic** (K6 pace, [Hyp]):
- No detection: 2.0 + 0.28 (noise split) + 0.28 (speech-also) + 0.75 (L4, 16.5 s stimulus) = **3.31 h**.
- Detection: 3.88 + 0.57 + 0.57 + 0.75 = **5.77 h**.
- 08-3: 2.0 + 0.28 + 0.28 = **2.56 h**; 3.88 + 0.57 + 0.57 = **5.02 h**.

**Raise item 2 (phase-07c-2b), text:**

> "2. The ABX listening (two test rooms, noise and speech, plus the L4 held-chord test) needs you or a named listener: about 3.3 h if nothing is detected at 0.9 dB, up to about 5.8 h if something is, in sittings of at most 2 h split only at a chain boundary; the dates go in the session brief before the seal. The 08-3 binaural rerun adds about 2.6 h, up to about 5.0 h."

**Scope 3:** replace "About 2 h of listening per scene (builder file 32, K6: range 1.3 to 2.8 h by pace)" with:

> "About 3.3 h of listening if nothing is detected at 0.9 dB, up to about 5.8 h if something is, L4 included (builder file 32 K6 pace, [Hyp]; the builder times one speech block and L4 before the dates are fixed), in sittings of ≤ 2 h split only at a chain boundary."

Also in scope 3, "(file 13 item 14; run sheet §7)" becomes "(file 13 item 14 as amended by M3-L4; run sheet §7)".

---

## (6) Consolidated plan edits for one `/fix-plan`

**1. Run sheet `docs/validation/abx-07c-2-run-sheet.md`:**
- **Header:**
  - "Nothing on this sheet changes it" becomes "Nothing on this sheet changes it except the amendments in §0, each made by a board decision before any stimulus was heard."
  - **New §0, "Amendments to file 13 (phase-07c-2b M3; decider files 2, 6, 9; interrogator files 3, 7 and the check of this file)":** this is the file 13 amendments record. It lists:
    - items 2–3 (both chains 24 + 6, ≥ 18/24);
    - item 4 (applies across F1–F4);
    - item 5's clause (file 2's two-bracket text replacing "[S-A only …]", 0.874 dB);
    - item 9 (the two scenes and labels);
    - item 13 (wording);
    - item 14 (L4 design, M3-L4);
    - item 15 (now in `phase-08-3.md`);
    - M3-6 (speech pair rule);
    - M3-8 (trigger).
- **§1:**
  - "Scene" becomes the two scenes with their labels: the S-W label below, and file 6's S-B\* label.
  - The old S-A figures (T30 2.009 s, Q5 window, M2 2.016 s) are marked "S-A, history", and each sealed scene's values are printed instead (both_wall heard T30 1.370 s, tail T30 1.313/1.274 s; s0.7 1.831, 1.254/1.274 s).
  - Add the C-b tail-spread print (S-W and fallbacks; S-B\* print only, per M3-1 (e)), the S-B\* dip/step print, the Q5 heard-end kit choice, the M3-8 trigger, and the manifest r_c note ("0.057·√(V/T60_Eyring)"; labels use Eq. 5.44 (A/16π)^½).
- **§3:**
  - the speech pair MA01_01/MA01_02 with M3-6's fallback rule;
  - per-scene builds;
  - the assertion list gains "HF-W (β 1.1378) with condition D and N1–N3" in place of "no new click at the step";
  - the pre-registration commit holds both scenes' prereg records and L4's sealed hashes;
  - the builder times one speech block and L4 before the dates.
- **§4:**
  - blocks of 30 presentations (24 + 6 anchors, 3 per half, break after 15);
  - the table: every family (F1 S-W, F2 S-B\*) and chain at 0.9 dB ≥ 18/24, then 0.5 dB ≥ 18/24 only after a 0.9 dB detection in that chain of that family; anchor ≥ 5/6;
  - "Family: ≤ 0.0227 per scene (2 × 190051/2²⁴, union bound), ≤ 0.0453 at 07c-2b, ≤ 0.0906 with 08-3's F3/F4; power 0.607 per chain at p = 0.75; no α passes between chains or families";
  - the fallback sentence (M3-2);
  - item 4 across F1–F4;
  - order: S-W (noise 0.9 first, then speech), S-B\*, then L4 alone after a rest, the same day as the S-B\* sitting.
- **§5:** tables of 30 presentations (1–15 | break | 16–30), per scene and chain.
- **§6:**
  - columns become k/24 and family;
  - rows per family, chain and level;
  - wording "detected (≥ 18/24, family α 0.0227)"; "not detected in 24 trials by one listener (power 0.61 at p = 0.75) on <scene> (<record line>)"; "inconclusive" if the anchor failed;
  - item 13's sentence "A non-detection is recorded for its scene class only; the 1 dB bound elsewhere rests on D-C1, as AX47 states.";
  - the S-W record line (Seat 9): "tail share 0.667 at 1 kHz, resting on the engine's t_mix,e onsets 0.165 / 0.380 s (own-onset tail L − R +9.4 dB; −0.05 dB at equal times); listener and emitter 0.1 m from a face";
  - the record states each family's α, the union rate and which family detected at what count.
- **§7:** L4 leaves "Not in this kit" and gets its own section:
  - L4-A, S′, the label above, Seat 1's chord and pass rule (≥ 12/16, 6 anchors, ≥ 5/6);
  - Seat 3's checks on the partition grid;
  - `render_cli --ax49-provisional` with F1–F6 and F2′;
  - null wording "not detected in 16 trials by one listener (power 0.63), T60 8 s, held chord, omni diotic";
  - a detection fires AX49's Reversal, "worst case: provisional current through the whole free decay".

  The 08-3 rerun points to `phase-08-3.md`.
- **S-W label (§1 and kit), exact:**

> "layout4_s1/both_wall: 20 × 30 × 10 m, 6,000 m³, walls and ceiling α 0.01, floor α 1, scattering 1 on every face. Listener 0.1 m from the y = 0 wall, emitter L 0.1 m from the y = 30 m wall; listener–emitter 29.95 / 20.13 m (L / R). The reflections off those faces (delay about 0.58 ms; first interference notch near 0.86 kHz, Kuttruff Eq. 7.6) are absent at s = 1 (AX21; Kuttruff Eq. 8.59), so the direct sound's tone colour is not room-like and the scene represents no seat. D/R at 1 kHz −7.7 / +5.2 dB per emitter, −5.3 dB heard (emitter L's direct arrives 28.6 ms after R's and counts as reflected); diffuse field −18.5 / −15.0 dB at r/r_c 8.39 / 5.64 (r_c 3.57 m, A ≈ 640 m²; Kuttruff Eqs. 5.44–5.45; indicative only: ᾱ ≈ 0.28 is not small, Kuttruff §5.6). Tail onsets t_mix,e 0.165 / 0.380 s (L / R; the engine's t_mix,e rule). The decays agree within 0.05 dB at equal times, but from its own onset L's 1 kHz tail energy is +9.4 dB over R's at equal source power, where a diffuse room gives equal reverberant levels (Kuttruff Eq. 5.42; indicative). This is engine behaviour, not room geometry; the tail share 0.667 at 1 kHz rests on it and changes with the t_mix,e rule (M3-8). Early part empty (AX21). Heard-IR T30 1.370 s, tail T30 1.313 / 1.274 s. Not a validated preset."

  The fallback template is file 6's, with SPREAD in Seat 9's two forms (C-b).

**2. `docs/phases/phase-08-3.md`: the item-15 home** (scope, plus one manual-checklist line "AX47 binaural rerun, item 15, F3/F4"). Text:

> "15. 08-3. Before Phase 08's goldens freeze, the AX47 self-ABX is rerun on the binaural chain at the bound in force, as two pre-registered families (F3, F4) with F1 and F2's design (both chains 24 scored trials + 6 anchors, 3 per half, break after presentation 15, ≥ 18/24; per family ≤ 0.0227; union over F1–F4 ≤ 0.0906), item 4 applied within each; the record states each family's α, the union rate and which family detected at what count.
> - (i) The S-W scene sealed in 07c-2b, with tailSeed, programmes, steps and trials identical to 07c-2b's. Where its listener is < 0.70 m from a face (AX44 d_L), it is labelled 'chain comparison only; listener 0.1 m from a face, outside the free-field HRTF's validity', and it carries the 07c-2b S-W label's onset sentence. A non-detection there is never counted as binaural evidence for the class; a detection reverses AX47 per item 4.
> - (ii) The S-B\* scene sealed in 07c-2b, likewise identical.
> Neither family is cited for externalisation or plausibility, and L4/L5 are not judged on these scenes.
> Before any stimulus, per scene: binaural vs omni per-band energy within ±1 dB (AC6); per-ear, per-band energy printed (print only); item 6 (HF-W with condition D) and `[ax47-midfade]` per ear; the M2 gap and Q5 checks per ear; D/R printed per ear; `hrtfId` and the set identity string recorded; the same wired headphone model and level setting as 07c-2b, recorded in the 07c-2b and 08-3 records, and no virtualiser.
> Sittings of ≤ 2 h each (two if nothing is detected at 0.9 dB, three if something is), split only at a chain boundary, on the same or consecutive days, dates in the 08-3 brief before 08-3 starts: about 2.6 h, up to about 5.0 h (builder file 32 K6 pace). Results are worded 'static, uncompensated (B14), generic HRTF', and for (i) also 'empty early part (AX21)'. If the trigger (M3-8) fired after 07c-2b, the stimuli are rebuilt and pass every seal gate again (HF-W worst ratio, margin and skip count printed; the tail-spread print), and the cross-chain comparison is recorded void unless the omni family is rerun on the current engine. If a rebuilt scene fails a seal gate, item 15 returns to the board before any 08-3 listening."

**3. BUILD_PLAN AX47:**
- **Reversal**, replacing "If the 07c-2 self-ABX (16 trials, … recorded precedent) detects …":

  > "If the 07c-2b self-ABX (two capped layout-4 scenes, F1 S-W and F2 S-B\*, each its own family) or its 08-3 binaural rerun (F3, F4; phase-08-3 item 15) detects a step below 1 dB, the bound becomes 0.5 dB."

- **Design:** after the D-W2 sentence, add:

  > "**Amended by phase-07c-2b's loop (M3; `docs/review/phase-07c-2b/` decider files 2, 6, 9; interrogator files 3, 7 and its check of file 9):** four families, F1 `layout4_s1/both_wall` (or its sealed fallback) and F2 `layout4_s0.7/default` (fallback `layout4_s0.9/default`) omni at 07c-2b, F3/F4 the same scenes binaural at 08-3; in each family both chains 0.9 → 0.5 dB at ≥ 18/24 (24 scored trials + 6 interleaved 3 dB anchors, 3 per half; the 0.5 dB step only after a 0.9 dB detection in that chain of that family); ≤ 0.0227 per family, ≤ 0.0453 at 07c-2b, ≤ 0.0906 over F1–F4 (strong, union bound); power 0.607 per chain at p = 0.75; anchor pass ≥ 5/6; a 0.9 dB detection in any chain of any family sets the bound to 0.5 dB, and a non-detection never cancels a detection. If the trial count is cut before any scored trial, all four families revert to the unsplit thresholds above with C1, never 13/13. C1 (Seat 5): if the class (c) round admits a statistical stage-1 source, it carries SE_target as one named constant citing AX47, and 07c-2b prints the AX38 4c restore record with the 0.25 dB branch at the gated builds."

- **Sources column:** add the M3 loop and "decided for Maisara, amends nothing".

**4. BUILD_PLAN AX49:**
- **Clause**, replacing "Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6).":

  > "Offline renders, bounces in hosts that signal offline, and `render_cli` never use the provisional (AX5, condition 6), except the validation-only flag `render_cli --ax49-provisional` for listening item L4 (phase-07c-2b M3-L4: omni only; refuses unless a provisional exists; excluded with `--ensemble`, `--abx-step-db`, `--switch-scene`, `--tail-level ax16`; with `--in/--out` only under `--realtime-emulation` and a fixed `--block`, both arms on the same block and partition; never named by `src/plugin`; tested)."

- **L4 sentence:**
  - "run with the AX47 ABX in 07c-2" becomes "run with the AX47 ABX in 07c-2b".
  - Add after "free decay": "(design, phase-07c-2b M3-L4: A = the provisional faded over [L_f, L_p), B = the exact tail, one fixed tailSeed; scene `ax49_l4_cube` (100 m, T60 8.0 s at 63 Hz–1 kHz, L_p 3.71 s < L 12 s); stimuli built, checked and sealed before the first scored AX47 trial)".
- The FM-2′ text is untouched.

**5. `phase-07c-2b.md`:**
- Raise 2 and scope 3 as in §5.
- Scope 2: "Amendments held for M3" marked "applied (M3, decider file 9; run sheet §0)".

**6. `phase-13-2.md`:** the new scope item in §4.

**7. BUILD_PLAN §6:** one change-log row covering AX47 (Reversal, design), AX49 (clause, L4), the run sheet §0–§7, phase-08-3 item 15, phase-13-2's item, and the Raise/scope texts. Source: this loop, corpus c1b171f.

**Builder items (kit, not `/fix-plan`):**
- C-b's two-measure print;
- the S-W label;
- speech 24 + 6;
- F2′ items 2–4;
- Seat 3's S2–S4 on the partition grid, and the first-partition IR assert;
- the manifest r_c wording;
- the L4 label fill;
- timing one speech block and L4.

---

## Summary

| id | decision | state | worst-off (cell) | sum | conf. | PRD bound | corpus basis | reversal condition |
|---|---|---|---|---|---|---|---|---|
| M3-1 | V1-W plus Seat 9's C-a label, C-b two-measure print with onset/level SPREAD, item-13 line; S-B\* print with Seat 9's call | stands (revised) | 1 (S2, S3, S7, S9) | 12 | high | NFR-1, FR-3D-5, L133 | Kuttruff 5.42, 5.44–5.45, 7.6, 8.59 | gates exhausted; HF-W red; Seat 9 rejects a label |
| M3-2 | both chains ≥ 18/24 (24 + 6, 3 per half) in F1–F4; 0.0227/family, 0.0453, 0.0906; power 0.607; no skip; C1; fallback unsplit + C1 | proposed (final) | 1 (S7) | 4 | high | NFR-1, L55 | — (binomial) | trial count cut before scoring |
| M3-3 | HF-W + D, N1–N3; commutator on 4 scenes / 200 stimuli | stands | 1 | 4 | high | NFR-1 | — | a clean stimulus reds |
| M3-4 | labels (S-W with C-a), template with two SPREAD forms, item 13, item 15, item-5 clause | stands (revised) | — | — | high | NFR-1, L133 | Kuttruff 5.42–5.45, 7.6, 8.59 | Seat 9 rejects a filled label |
| M3-L4 | L4-A on S′; Seat 9's label; Seat 3's grid checks; flag F1–F6 + F2′; built and sealed before the first trial | stands (revised) | 1 | 8 | high (timing, flag); medium (design, letter) | NFR-1, AX5, AX49, NFR-8 (paths) | Vorländer Eq. 6.4 (AX49 K17′) | S′ fails; `src/sim` needed; a check reds; stall |
| hours | 3.3 / 5.8 h; 08-3 2.6 / 5.0 h | proposed | — | — | medium ([Hyp] pace) | L55 | — | builder timing |
| corner | (1), (3), (4) stand; (2) replaced by the phase-13-2 item (Seat 2) | revised | — | — | high | NFR-8 L112 | Kuttruff 5.42 (indicative) | the board moves it earlier |

**Challenges to settled decisions:** none.

## Decided for Maisara

- **M3-1:** the self-ABX runs on a far, wet placement and a room with early reflections. The far one's label now says its extra tail comes from how the engine starts each tail, not from the room (NFR-1, FR-3D-5, L133). Seat 7 gives about 3.3 h before the pin and gets the most sensitive test before the golden round. Amends nothing.
- **M3-2:** speech gets the same 24 trials as noise, so a step heard only on vocals is missed 39 % of the time rather than 60 %. No skipping after a detection (NFR-1; hours unbounded, L55). Seat 7 gives about 17–34 min per stage and gets fewer missed vocal steps. Amends nothing.
- **M3-3:** the click gate is a derived energy bound with built-in failing tests (NFR-1). Amends nothing.
- **M3-4:** labels say what each room is, with no "hall" and no "occupied" (L133). A null counts only for its room (NFR-1). Amends nothing.
- **M3-L4:** the held-chord test plays the worst case (the cut), is built and sealed before any AX47 answer is known, and uses a test-only command-line switch. Shipped and offline renders are unchanged (NFR-1; AX5, AX49). Seat 7 gives about 45 min plus the pre-seal build. Amends nothing (FM-2′ untouched).
- **Corner and onset findings:** reported, not tuned. Seat 2's board rules on them before release (NFR-8). Amends nothing.
- **Person's action (not a question):** the sitting dates, in the brief before the seal.

**NEEDS MAISARA:** none.

Files:
- /home/user/makroof/docs/review/phase-07c-2b/6-decider-m3-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/7-interrogator-on-file6.md
- /home/user/makroof/docs/review/phase-07c-2b/8-seat1.md, 8-seat3.md, 8-seat5.md, 8-seat6.md, 8-seat7.md, 8-seat9.md
- /home/user/makroof/docs/review/phase-07c-2b/5-builder-tail-spread.md
- /home/user/makroof/docs/review/phase-07c-2b/2-decider-m3.md
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/BUILD_PLAN.md (L170, L172, L388–399)
- /home/user/makroof/docs/phases/phase-07c-2b.md
- /home/user/makroof/docs/phases/phase-08-3.md
- /home/user/makroof/docs/phases/phase-13-2.md
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L2698–2724, L3311–3317)
- /home/user/makroof/docs/PRD.md
