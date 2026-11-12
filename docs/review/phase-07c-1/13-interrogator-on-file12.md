# 13 — Interrogator, final check on decider file 12 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Target: file 12.

**Interrogator, decision mode, phase 07c-1, round 3 (final check)**

Target: `/home/user/makroof/docs/review/phase-07c-1/12-decider-decision-r3.md`
Corpus revision: `c1b171fe649f07cbeb952ef1f75d89bfaa414d0d`. All 13 corpus files are present.

## Outcomes

| decision | outcome |
|---|---|
| **D-C9 → AX49 (D3\*‴)** | **TENSION MISREAD on the T60-edit path, and it changes the winner (row 59).** This goes to Maisara as NEEDS MAISARA case (a). The decider excluded D3\*″ with a Seat 3 "3" that it read from Seat 3's D2 reason. Seat 3 rated that exact edit path 2/2 in r2 and repeated "stands as given" in r3. With 2/2, D3\*″ (max 2, sum 20) beats D3\*‴ (max 2, sum 23). Everything else in AX49 is common to both options (load path, L_f rule, normalisation, handover, offline, the 07d hand-off), and it survives with corrections (rows 62–65, 68–71, 85). |
| **D-C1 → AX47 (C5‴)** | **SURVIVES WITH CORRECTIONS** (rows 64, 74, 75, 79). The map is faithful (rows 32–33 closed). The tie at 2/10 is recomputed. The tie-break on phase-07c-1 L40 is plan-grounded. |
| **D-C2 → B4-G′** | **SURVIVES WITH CORRECTIONS** (row 82, wording only). |
| **D-C3 → A1′ + Π** | **SURVIVES WITH CORRECTIONS** (row 79). Row 47 is closed. |
| **FM-1** | **SURVIVES WITH CORRECTIONS** (row 83, rounding). |
| **FM-2′** | **SURVIVES WITH CORRECTIONS** (rows 69, 73). The 07d reading of condition 9 is CORRECT (row 72). |
| **FM-3′** | **SURVIVES** (row 84). |
| **FM-4′** | **SURVIVES WITH CORRECTIONS** (rows 74, 75). |

## Decision ledger

| id | decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|---|
| P07C1-59 | D-C9 | map / ordering | D3\*″ S3 cell "3 (long-T60 edits; read from its D2 reason)" | **TENSION MISREAD (seat re-rated; winner-changing)** | 6-seat3-r2 L25 rates this edit path (ISM waits for the provisional) "2/2 as written", and 10-seat3-r3 L35 says "T60-edit cell 2/2: stands as given". decider.md §4 allows a read-from-conditions cell only for an option the seat did not rate, and §5 says "never… re-rate a seat". Seat 3's D2 3/3 rests first on the letter of condition 4 (3-seat3 L31–34), which D3\*″ does not break. With S3 at 2/2, D3\*″ = 2+4+2+2+3+4+1+2 = **20** < D3\*‴ **23**, both max 2. | TENSION MISREAD → NEEDS MAISARA (a) | — |
| P07C1-60 | D-C9 | ordering | Other rows: D1 and D2 vetoed; D3\*‴ max 2, sum 23; "bridge only above 3.82 s" ≤ 25 | CORRECT | Recomputed from the cells. | — | — |
| P07C1-61 | D-C9 | map | D3\*‴ cells: S1 1/2, S3 1/1, S4 1/1, S5 1/1 rfc, S6 1/2, S7 2/2, S8 2/1, S9 2/2 | faithful | Sources: 10-seat1-r3 (condition 1 is in L4); 6-seat3-r2 L47 (the alternative "D5 → exact on edits, D3\* for loads"); 10-seat5-r3 conditions (parallel, record (h), reversal 2) all present; 10-seat6-r3 (Seat 1 neither confirmed inaudibility nor set a deeper cut); 10-seat7-r3; 3-seat8 L33; 6-seat9-r2 L12. | — | — |
| P07C1-62 | D-C9 | map premise | S5 1/1 and S7 2/2 rest on "≈ 0.65–0.8 s per instance at T60 ≥ 8 s" | CONDITIONS VIOLATED (cost premise); debt owned | Gated geometry: t_dir = 40.3 m / 343 = 0.118 s, so L_p = 1.12 + 0.312·T + 0.1 s. That passes 3.82 s at T60_max > 8.3 s and reaches L = min(12, 1.5·T60) = 12 s at T60_max ≥ 34.6 s (AX38 4c finding). So the rated figure covers only T60_max ≲ 8.3 s. The rest is K24 (uninformed) and is registered for 07d. It is the same in D3\*″ and D3\*‴. | Winner unchanged. Label the cells "at T60_max ≲ 8.3 s". | — |
| P07C1-63 | D-C9 | map | "D4 cannot be ranked: Seat 4's cell is unrated" | IMPRECISE (wrong seat) | Seat 4 rated D4 "as A3": unit-decay form "can live with", A3 → 1 (3-seat4 L12, L14, L41). The cell that is actually unrated is Seat 5's. Its D4 2/2 rests on A3's ≈ 20 MB condition (3-seat5 L15–16, L45), not on the ≈ 147 MB unit-decay form (3-seat3 L48). The conclusion stands. | SWC | — |
| P07C1-64 | D-C1 / D-C9 | claim K18′; AX47 (b) | "Squared amplitude ratio exact/provisional = 1 + (1 − f_b)·δ; step ≥ −0.06 dB; +0.5 dB needs δ ≥ 9" | IMPRECISE (direction inverted) | δ is the relative deviation of the realised remainder (file 9 L71). Then E_full = (E_p/f_b)(1 + (1 − f_b)δ), so exact/provisional energy = **1/(1 + (1 − f_b)δ)**. The provisional-to-exact step is therefore ≤ +0.06 dB as a hard bound (δ ≥ −1), ≥ −0.5 dB unless δ ≥ 9, and ≥ −1 dB unless δ ≥ 19 (0.259 / 0.0136 = 19.0). Seat 3 r3 note 1 has this orientation. My own row 37 restatement carried the same inversion. Magnitudes and the choice are unchanged. | SWC: correct K18′ and the AX47 (b) signs before A4 encodes them | — |
| P07C1-65 | D-C9 / D-C1 | claim K17′ (D9-L2, AX47 (b)) | L_f = t_mix,e,max + 0.312·T60_max; decay ≥ 18.72 dB; tail-window loss ≤ 0.06 dB wherever L_p < L | CORRECT | Vorländer §6.4.1 Eq. 6.4: the energy fraction past L_f is (a − c)/(b − c) ≤ a/b ≤ e^(−13.8155·0.312) = 0.01343, and 10·log10(0.98657) = −0.059 dB. 60 × 0.312 = 18.72 dB. EDT is derived for the tail alone and is asserted on A4 for the hybrid IR. Rows 35, 39 and 40 are closed. | — | — |
| P07C1-66 | D-C9 | claim K22 (D9-L5) | An EDT-faithful interim at the gated cube needs the full FFT | CORRECT (with the frame fix) | L_f ≥ 1.12 + 0.212·50.5 = 11.8 s, and 11.9 s × 96 kHz = 1.14 M samples > 2^20, so n = 2^21. Correction to my row 38: without t_mix added, 10.7 s sits at the 2^20 boundary. | — | — |
| P07C1-67 | D-C9 | claim K20 | t_mix ≥ 1.0 s at 100 m; the k_eff term "does not bind" | CORRECT (bound) / IMPRECISE (aside) | `MixingTime.h` L5 and L20 state the 6.8·V^(1/3) ms figure only for t_dir → 0. Nothing rests on the aside. | — | — |
| P07C1-68 | D-C9 | claim D9-L4 | "L_p ≈ 3.6–3.7 s ≤ 3.82 s at T60 8 s / 100 m" | IMPRECISE (geometry not stated) | The bound needs t_mix,e,max ≤ 1.22 s, i.e. t_dir ≲ 0.22 s (≲ 77 m) and no AX22 shift (`Engine.cpp` L139–146). The gated geometry gives 3.71 s. A 100 m cube allows about 170 m, where L_p ≈ 4.1 s falls in the K24 band. K15′ is one box at three points. | SWC: write "at the gated geometry" | — |
| P07C1-69 | D-C9 / FM-2′ | claim D9-L6 | "No restore is longer than the pre-07c restore" | IMPRECISE (hidden premise: an isolated restore) | In a sequential 8-instance load, condition 12 runs the earlier instances' exact syntheses outside the gate, concurrently with the next synchronous restore (file 8 (f): 2.25 GB process peak at 8 × 96 kHz). The G-1-serialised pre-07c builds had no such overlap. Record (h) measures it. | SWC: restate as "an isolated restore" | — |
| P07C1-70 | D-C9 | AX49 text | "D1 … only for tailless (AX22 fallback) scenes" | INCONSISTENT (with the code) | `Engine.cpp` L135–154: the AX22 fallback moves the handover to max(t_mix,e, t_cap,e) and matches a tail there. E_b = 0 only "if the window holds no energy". Fallback scenes therefore generally have a tail, and D1 for them is the vetoed D1. | minor: write "scenes whose matched tail energy is zero" | — |
| P07C1-71 | D-C9 | reversal / gate | Reversal 1: "the gate fails at L_p ≤ 3.82 s" | open question | The gated scenes are the low-α cube (L_p ≥ L, no provisional) and the flutter scene. Unless the flutter scene carries a tail with L_p ≤ 3.82 s, reversal 1 cannot fire, and the provisional's synchronous cost is only printed. | minor | Q2 |
| P07C1-72 | FM-2′ (part 3) | PRD proxy | Condition 9's 07d clause reaches the long-T60 corner | CORRECT | phase-07c-1 L99–101: "If this phase's loop finds condition 9 does not fit here, a `phase-07d.md` of size S–M is created". L96–97: macOS "closes here, or at 07d". BUILD_PLAN L158 premise P1. The gated cube (T60_max 50.5 s) is the register's own scene. | — | — |
| P07C1-73 | FM-2′ (parts 1–2) | PRD proxy | "The literal gate breaks NFR-6 and NFR-1 at every load"; D3\*‴ is "inside the preamble's 'usable' (30 s convention, register form)" | IMPRECISE | D4 in unit-decay form (unrated) gives a tail without synthesis at keyed same-fs loads, so "every load" holds only among the rated options. At the gated corner the 30 s convention is not met; it is a registered defect (macOS 33.40 s, Windows 36.73 s), not a pass. The answer follows once restated. Row 53 (prepare declared) and row 50 (the AMENDS quote) are closed. | SWC | — |
| P07C1-74 | FM-4′ | PRD proxy | NFR-1 "Pass thresholds come from the Expert" read as Seat 1's 1 dB | IMPRECISE | PRD L13, L150–152 and Q9 (L164): "the Expert" is the Spatial Audio Expert project, and Q9 is unresolved. The plan's stand-ins are AQ9 (Table 6.1-based, accepted 2026-11-05) and phase-07c-1 L40's assignment to Seat 1. The NFR-2 reading is now correct (row 51 closed). | SWC | — |
| P07C1-75 | FM-4′ / D-C1 | hidden premise | "The ABX re-decides 0.5 against 1 dB before that source exists" | IMPRECISE (not in the plan edits) | §8's phase-07c-2 list gives no order between admitting class (c) and the AX47 ABX. The premise holds only if admission waits for the ABX result. | SWC: state the order in phase-07c-2 | — |
| P07C1-76 | D-C1 | map | S5 C5‴ 1/1; S3 1/2 (read from its C3 reason) | faithful | 6-seat5-r2 L7 ("bounds known at design time") now holds. The S3 read of 3-seat3 L21 is conservative. Rows 32 and 33 are closed. | — | — |
| P07C1-77 | D-C1 | ordering | Tie C3 = C5‴; tie-break by phase-07c-1 L40 | CORRECT | C3 sum 1+3+1+1+2+2 = 10 and C5‴ sum 1+3+2+1+2+1 = 10, both max 2. §5 has no rule after reversibility. Seat 1 ruled 1 dB with a 0.5 dB reversal (3-seat1 L9–23; 6-seat1-r2 L23). | — | — |
| P07C1-78 | D-C1 | claim | "≤ 0.06 dB, or ≤ 0.23 dB at δ ≤ 3, in 07c-1" | CORRECT (magnitudes, with row 64's direction) | 0.06 + 10·log10(1.041) = 0.06 + 0.17 dB. A step above 0.5 dB needs δ ≥ 9. Row 54 is closed. | — | — |
| P07C1-79 | AX47 / D-C3 | scope | Same-platform, cross-build keyed step is "recorded" | IMPRECISE (scope) | The step is not in class (a) or (b). AX47's Scope excludes only B1′-hold and bridge steps. List it there as recorded, not bounded (row 47 mechanism). | SWC | — |
| P07C1-80 | D-C3 | claim | Five-part key; bit-identical within AX5's scope | CORRECT | The claim is now restricted to same platform and build. Seats 3 and 5 rated r3 on "every cross-OS reopen is keyless". A1′ sum 11 unchanged. | — | — |
| P07C1-81 | D-C2 | map / ordering | K2 S3 1/1; B4-G′ max 1, sum 13; B4+K2 15; B2+K2 17 | CORRECT / faithful | 10-seat3-r3 L7; 10-seat5-r3 L16–18 (its gate-priority condition is already AX38 (i)'s class-(1) order). Row 44's sums minus 2. Row 45 is closed. | — | — |
| P07C1-82 | D-C2 | "Decided for Maisara" | "re-solves at load in about 0.1 s and plays its tail at once" | IMPRECISE | A keyless load also synthesises the AX49 tail synchronously: about 0.5–0.65 s per instance at 96 kHz / T60 8 s (file 8), and the full synthesis at T60_max ≳ 35 s. | minor | — |
| P07C1-83 | FM-1 / AX18 | claim | f_w ≥ 0.987; ρ ≥ 0.993; +3.0 dB vs ≈ 0 dB | IMPRECISE (rounding) / CORRECT | 1 − e^(−4.311) = 0.98657, so write "≥ 0.986". √0.98657 = 0.9933. Vorländer §4.3 Eq. 4.15 cross term: +2.99 dB (equal-power) vs −0.01 dB (equal-gain). Row 48 is closed. | SWC | — |
| P07C1-84 | FM-3′ | PRD proxy | NFR preamble / NFR-2 citations | CORRECT | PRD L101 and L106. | SURVIVES | — |
| P07C1-85 | D-C9 | debt | Register rows | faithful, one correction | Every later rating ≥ 1 has a row. The "07d" rows name a phase this decision creates: apply `phase-07d.md` and its BUILD_PLAN §0 row before the register cites it. | SWC | — |
| P07C1-86 | file-11 Q1–Q5 | rebuttal | The decider's answers | Q1 answered (K22, exact tail where L_p ≥ L, 07d), except its Seat 3 part, which was answered by re-rating (row 59). Q2–Q5 answered. Rows 32–36, 38–40, 42, 45, 47, 48 and 50–57 are closed. | — | — | — |

## Corrections to apply (for the parts that stand)

1. **K18′ and AX47 (b) (row 64):** "provisional-to-exact step = −10·log10(1 + (1 − f_b)·δ): ≤ +0.06 dB (δ ≥ −1); ≥ −0.5 dB unless δ ≥ 9; ≥ −1 dB unless δ ≥ 19".
2. **AX49:** "D1 only for scenes whose matched tail energy is zero" (row 70).
3. **D9-L4:** write "at the gated geometry (t_dir 0.118 s)" (row 68).
4. **D9-L6 and FM-2′:** write "an isolated restore" (row 69).
5. **FM-2′ options line:** "every rated option"; D4 noted as unrated; "registered defect", not "inside usable" (row 73).
6. **FM-4′:** NFR-1 read through Q9 unresolved, AQ9 and phase-07c-1 L40 (row 74).
7. **phase-07c-2:** class (c) admission waits for the AX47 ABX (row 75).
8. **AX47 Scope:** add "cross-build keyed steps are recorded" (row 79).
9. **AX18:** "≥ 0.986" (row 83).
10. **AX48 "Decided" line:** include the synchronous tail synthesis in the load time (row 82).
11. **S5/S7 D3\* cells:** label them "at T60_max ≲ 8.3 s" (row 62).
12. **D4 note:** "Seat 5's cell at ≈ 147 MB is unrated", not Seat 4's (row 63).
13. **07d:** create the phase file and status row before the register cites it (row 85).

## Must go to Maisara (NEEDS MAISARA, case (a): a ruling after 3 rounds that fails the check)

**One item, D-C9: what plays on T60-changing edits.** Everything else in AX49 is the same under both readings.

- **Reading A (the decider's):** Seat 3's D2 "3/3" reason ("For edits that change T60, the hold is about 3.3 s") also covers D3\*″. At T60_max ≳ 35 s, D3\*″ makes the ISM wait for the full synthesis, about 3 s. So D3\*″ is vetoed and **D3\*‴** wins: Seat 3's D5 bridge on every T60 edit, then the exact tail. Max 2, sum 23.
- **Reading B (the seats' recorded words):** Seat 3 rated this edit path "2/2 as written" (r2) and "stands as given" (r3). Then **D3\*″** wins at step 5: on T60 edits the current IrSet plays until the ISM and the provisional/exact tail are ready. Max 2, sum 20.
- **The decider's recommendation:** D3\*‴.
- **What would settle it:**
  - Seat 3's own rating of the about-3 s hold at T60_max ≳ 35 s.
  - Or a reading of her own text that neither side used: does condition 9's "with the same interim / settling rules as the diffuse solve" carry condition 4's "The ISM update is never held behind the diffuse solve" over to the synthesis?

## Questions (for the record; no further round)

1. Seat 3: at T60_max ≳ 35 s, where D3\*″ holds the ISM for the full synthesis, is your T60-edit rating 2 or 3?
2. Which AX38 4c gated scene has L_p ≤ 3.82 s, so that AX49's reversal 1 can fire? Does the flutter scene carry a tail?

Files used:
- `/home/user/makroof/docs/review/phase-07c-1/12-decider-decision-r3.md`, `11-interrogator-on-file9.md`, `9-decider-decision-r2.md`, `8-orchestrator-provisional-cost.md`, `10-seat{1,3,5,6,7,9}-r3.md`, `3-seat{1,3,4,5}.md`, `6-seat{3,9}-r2.md`
- `/home/user/makroof/docs/phases/phase-07c-1.md`; `/home/user/makroof/docs/BUILD_PLAN.md` (L114, L115, L138, L158); `/home/user/makroof/docs/PRD.md` (L13, L101–112, L150–165); `/home/user/makroof/docs/board/README.md` (L76–145); `/home/user/makroof/.claude/agents/decider.md` (§4–5)
- `/home/user/makroof/src/sim/tail/MixingTime.h`; `/home/user/makroof/src/sim/Engine.cpp` (L119–159, L218–380); `/home/user/makroof/src/sim/conv/CrossfadingConvolver.h` (L1–50)
- `/home/user/makroof/docs/corpus/vorlaender-auralization.md` (§4.3 Eq. 4.15; §6.4.1 Eq. 6.4; §6.4.2 Eq. 6.5; §6.4.3 Eq. 6.7; Table 6.1); `/home/user/makroof/docs/corpus/zotter-frank-ambisonics.md` (§4, loudness note)