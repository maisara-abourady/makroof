
# 26: Interrogator diff check, phase 07c-2b M3 /fix-plan (plan-editor's application)

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Read-only. For the orchestrator to save as `/home/user/makroof/docs/review/phase-07c-2b/26-interrogator-diffcheck.md`.

**Method and its limit.** I have no shell here, so I could not run `git show HEAD`. I read the committed state of the four target files in full or at the edited lines: run sheet in full; `phase-08-3.md` L1–90 and L167; `phase-07c-2b.md` L28–197; BUILD_PLAN §0 L13–61, AX47 L170, AX49 L172, §6 L530–535. I compared every applied passage with its source text. I also confirmed the held items are absent: there is no `docs/phases/phase-07e*`; no `07e` appears in §0 or in any phase file except the pending pointers; the 08-3 and 08-4 §0 rows are unchanged; `phase-08-4.md` has no 07e text.

## Verdict: FAITHFUL WITH CORRECTIONS

- **Numbers:** every number in the applied texts matches its source, and every acoustic number recomputes from the corpus.
- **One correction is required.** The 08-3 gate sentence turns a held text into a commitment that the question sent to Maisara still leaves open (row D1).
- **The rest are minor:** citation-list corrections, one optional reversion to the verbatim fragment, and one software note.

## Recomputed (corpus, c1b171f)

| figure | working | verdict |
|---|---|---|
| S-W r_c 3.57 m, A ≈ 640 m², ᾱ ≈ 0.28 | S = 2 200 m². Floor 600 + 1 600 × 0.01 = 616 m². 4mV = 4 × 1.08·10⁻³ × 6 000 = 25.9 m². A = 642 m². r_c = (642/16π)^½ = 3.57 m (Kuttruff Eq. 5.44, Table 6.1). ᾱ = 616/2 200 = 0.28. | CORRECT |
| S-W r/r_c 8.39 / 5.64, diffuse D/R −18.5 / −15.0 dB | 29.95/3.57 and 20.13/3.57; 20·log₁₀(1/8.39) = −18.48 dB, 20·log₁₀(1/5.64) = −15.03 dB (Eq. 5.45, where w_d = w_r at r_c) | CORRECT |
| S-W notch near 0.86 kHz at a 0.58 ms delay | Eq. 7.6: the first minimum is where cos(2πft₀) = −1, so f = 1/(2t₀) = 862 Hz | CORRECT |
| S-B\* −10.8 dB at r/r_c 3.47 | 20·log₁₀(1/3.47) = −10.81 dB | CORRECT |
| S-B\* SPREAD clause, Eq. 5.42 with the §5.6 caveat | w_r = 4P/cA does not depend on position. L2724: this is questionable when ᾱ is not small. | CORRECT, verbatim to 14-seat9 §2 |
| L4 label: −6.5 dB, r/r_c 2.1, r_c ≈ 19 m, A ≈ 18 200 m², ᾱ ≈ 0.23 | 0.161 × 10⁶/8 = 20 125 m². 4mV = 4 320 m² (Table 6.1, 1 kHz, 50 %: 1.08). Eq. 5.24 gives ᾱ = 0.232, so A = 18 216 m² and r_c = 19.04 m. r = (5² + 40² + 0.3²)^½ = 40.31 m. D/R = −6.52 dB. | CORRECT, verbatim to 14-seat9 §3 |
| L4 wording: 6.5 s at 2 kHz, 3.7 s at 4 kHz, "40 dB", "19 dB" | Table 6.1 at 50 %: 2.28 and 6.84 (×10⁻³ m⁻¹). 0.161 × 10⁶/(15 805 + 9 120) = 6.46 s; /(15 805 + 27 360) = 3.73 s. Depth at L_f: 60 × 2.496/3.731 = 40.14 dB; 60 × 2.496/8 = 18.72 dB (Eq. 3.70 definition of T). | CORRECT, verbatim to 19-seat9 |
| L_f 3.6135 s, L_p 3.7135 s | t_dir = 40.31/343 = 0.1175 s. t_mix,e = t_dir + √V ms = 1.1175 s. L_f = 1.1175 + 0.312 × 8 = 3.6135 s, and L_p = L_f + 0.1 s. | CORRECT (arithmetic on AX49's own rule) |
| Item 5 clause, 0.874 dB | 10·log₁₀(0.032 + 1.2303 × 0.968) = 10·log₁₀(1.2229) = 0.874 dB | CORRECT |
| Heard step ΔG +0.62 dB | 10·log₁₀(1 + 0.667 × 0.2303) = 0.620 dB | CORRECT |
| α ≤ 0.0227 per family; 0.0453; 0.0906 | Σ_{k=18}^{24} C(24,k) = 190 051. 2 × 190 051/2²⁴ = 0.02266; ×2 = 0.0453; ×4 = 0.0906. | CORRECT |
| Power 0.607 / 0.61 | P(X ≥ 18) with X ~ Bin(24, 0.75) = 0.6074 | CORRECT |
| L4 α 0.0384, power 0.630 | Σ_{k=12}^{16} C(16,k) = 2 517; 2 517/65 536 = 0.0384. P(X ≥ 12) with X ~ Bin(16, 0.75) = 0.6302. | CORRECT |
| Hours 3.3 / 5.8 / 2.6 / 5.0 h | 2.0 + 0.28 + 0.28 + 0.75 = 3.31; 3.88 + 0.57 + 0.57 + 0.75 = 5.77; 2.56; 5.02 (file 9 §5) | CORRECT; L4 is still 0.75 h because file 21 added no arm |
| Margins 4.17 / 2.29 dB; ensemble 3/16, min −3.98, median +1.59, median form min 2.74 | file 18 §1; file 25; file 23 C7 | match their sources |

## Ledger

| id | file / place | item | verdict | evidence | severity | correction / question | status |
|---|---|---|---|---|---|---|---|
| D1 | `phase-08-3.md` L74–75 | "Stimuli are built only after the NFR-8 placement findings' cause ruling required by phase-07c-2b M3-H (home pending Maisara, file 24 …) is done." | **INCONSISTENT** with the held status | **File 20** row "§6 items 2 (3rd insertion) …": "held … They stand or fall with M3-H". **File 24** asks her "must that happen before … 08-3 item 15 … are built". Its options H1 (13-2, before release) and H2-c "as worded" (Seat 2: "1/1 if it also gates 08-3 item 15") do not gate item 15. So the sentence decides part of her open question. | major (process; not acoustic) | Replace L74–75 with: "Whether item 15's stimulus build waits on the cause ruling for the NFR-8 placement findings is pending Maisara (M3-H, `docs/review/phase-07c-2b/24-m3h-for-maisara.md`)." | open |
| D2 | run sheet §0 header; BUILD_PLAN §6 row 1 (plan-editor note a) | interrogator citation "3, 7, 10, 15 and its check of file 21": file 20 is dropped | IMPRECISE (record) | **What the editor did:** applied file 21 §6's list literally. **Why that drops file 20:** file 21 was written without file 20 to hand. File 20 is the check that rated the §1 labels, §6 wording and AX47 texts faithful, gave R1 and held M3-H. **The inconsistency:** the AX47 Sources cell in the same commit cites file 20 ("interrogator files 3, 7, 10, 20"), and AX47 Design cites "its check of file 17". | minor | In both places: "interrogator files 3, 7, 10, 15, 20 (its check of file 17) and 23 (its check of file 21)" | open |
| D3 | run sheet §7 checks (note b) | "decider file 13 R1–R7" kept | faithful | **File 15 L10:** R1–R4, R6 and R7 survive. **R5(a)/(e):** ratified in file 21 §5, which the same bullet cites. **Replacement span:** file 21 §6 replaced only the Catch2 span. | none | — | closed |
| D4 | AX49 L4 fragment (note c) | "a Release gate step on macOS and Windows (NFR-4), plus Linux in CI" | IMPRECISE (departs from verbatim; not wrong) | **Where file 23's R5 correction applied:** it targets file 21's acceptance check and Decided-for-Maisara gloss ("NFR-4's three platforms"), not the plan fragment. **The fragment:** file 21's "on Linux, macOS and Windows" was rated faithful in file 23. **What the new wording does:** "plus Linux in CI" implies that macOS and Windows are not CI runs. NFR-4 itself (PRD L108, per file 23) is quoted correctly. | minor | Restore file 21 verbatim: "… and in a Release gate step on Linux, macOS and Windows". Keeping it as applied is acceptable. | open (optional) |
| D5 | `phase-08-3.md` L58 (note d) | item "15." among items 3, 5, 6, 7 | faithful | **Source:** file 9 §6 item 2 begins "15. 08-3." verbatim. **The list:** it already carries umbrella numbers that are not consecutive (3, 5, 6, 7), so the "15." creates no new defect. | none | — | closed |
| D6 | run sheet §1 Directions (note e) | "12 and 12" | CORRECT | half of 24 scored trials (§4, M3-2) | none | — | closed |
| D7 | run sheet §4 heading, §6 "k/24" (note e) | "as amended in §0"; k/24 | faithful | file 17 §6 §4/§6 ("k/24") | none | — | closed |
| D8 | run sheet §3 item 3 (note e) | `--scene <scene>` on the noise and speech commands | SOFTWARE (not rated) | **The flag exists:** `abx_kit.py` L1155. **The collision:** output goes to `args.out / "noise"` and `"speech"` (L1181–1184), and §4 seals `--pack build/abx-07c-2/<chain>`. As written, the second scene's build uses the same path as the first. **Source:** file 17 said only "builds per scene". | — | For the builder or the orchestrator: give each scene its own `--out`, and use the matching `--pack` in item 4. | note |
| D9 | AX47 Design (note f) | full stop → semicolon before the inserted heard-step clause | faithful | **File 17 item 3:** the insertion goes before "If the trial count is cut". **Result:** the sentence reads "…never cancels a detection; a non-detection is recorded … at the recorded commit). If …" | none | — | closed |
| D10 | run sheet §0, §1 (item 5 clause, T30 history, Scenes, S-W label, S-B\* label, template, SPREAD, new bullets), §3, §4, §5, §6, §7, §8 | file 17 §6 item 1 as amended by file 21 §6, file 23 C7 and C8, and file 20 R1 | faithful | **S-W label:** = file 9 §6 verbatim. **S-B\* clause:** = 14-seat9 §2 verbatim, at the stated insertion point. **S-W null:** = 14-seat1 §6 with Seat 9's record line. **L4 label:** = 14-seat9 §3. **L4 wording:** = 19-seat9. **Band coverage:** = file 21 with C8's window start, word for word. **C7 sentence:** appended. **C-b firing:** routed to "the board (home pending … file 24)", which is R1's sense with 07e held. | none | — | closed |
| D11 | `phase-08-3.md` item 15 (i), (ii), checklist L167 | file 9 §6 item 2 plus file 17's (i) and (ii) insertions | faithful | file 17 §6 item 2; the per-ear form matches 14-seat1 §6 | none | — | closed |
| D12 | `phase-07c-2b.md` Raise 2, scope 3, scope 2 marker, Out of scope | file 9 §5 verbatim; "applied (…)"; pending pointer | faithful (marker IMPRECISE) | **The hours:** they match file 9 §5. **The marker:** it reads "decider files 9, 17, 21" where the source has "decider files 9 and 17". File 21 does not touch items 9, 13 or 15. **Out of scope:** the line is neutral ("home pending Maisara"). | minor | Optional: "(applied: M3, decider files 9 and 17; run sheet §0)" | open (optional) |
| D13 | BUILD_PLAN AX47 Reversal, Design, Sources | file 9 §6 item 3 plus file 17's changes | faithful | **Citations:** "decider files 2, 6, 9, 17; interrogator files 3, 7, 10 and its check of file 17". **Heard-step clause:** inserted. **Sources:** "decided for Maisara, amends nothing". | none | — | closed |
| D14 | BUILD_PLAN AX49 clause and L4 sentence | file 9 §6 item 4, file 17 item 4, file 21 fragment | faithful (except D4) | 07c-2 → 07c-2b; the design text; the band-coverage fragment matches file 21; FM-2′ is untouched | none | — | closed |
| D15 | BUILD_PLAN §6 rows 1–2 | file 17 item 9 as replaced by file 21 §6; 07e clauses held; C7 in row 2 | faithful (except D2) | **Row 1:** the 07e clauses are replaced by "(the placement findings' home, M3-H, is with Maisara, case (a), file 24)". **Row 2:** file 21's text plus C7, verbatim. | none | — | closed |
| D16 | held items | phase-07e file; §0 rows 07e / 08-3 / 08-4; phase-08-4 edit | absent, as required | Glob found no phase-07e file; §0 L38–43 are unchanged; no 07e text in `docs/phases` other than the pending pointers | none | — | closed |

## Questions for the orchestrator or plan-editor
1. **D1:** will `phase-08-3.md` L74–75 be restated neutrally? As committed, it settles whether 08-3 item 15 waits on the ruling, and that is part of what file 24 asks Maisara.
2. **D2:** will the run sheet §0 header and §6 row 1 cite interrogator file 20 beside file 23? The AX47 Sources cell already cites file 20.

## Files
- /home/user/makroof/docs/validation/abx-07c-2-run-sheet.md
- /home/user/makroof/docs/phases/phase-08-3.md (L58–87, L167)
- /home/user/makroof/docs/phases/phase-07c-2b.md (L31–39, L102, L129–137, L184–193)
- /home/user/makroof/docs/BUILD_PLAN.md (§0 L13–61; AX47 L170; AX49 L172; §6 L534–535)
- /home/user/makroof/docs/review/phase-07c-2b/9-decider-m3-r3.md §5–§6, 17-decider-m3-r4.md, 20-interrogator-on-file17.md, 21-decider-l4-coverage-r2.md, 23-interrogator-on-file21.md, 24-m3h-for-maisara.md, 14-seat1.md, 14-seat9.md, 19-seat9.md, 15-interrogator-on-file13.md (outcomes)
- /home/user/makroof/tools/ci/abx_kit.py (L1152–1195)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (Eq. 3.70 L2122; Eqs. 5.24–5.25 L2607–2609; §5.6 Eqs. 5.42–5.45 L2698–2710 and caveat L2724; Eq. 7.6 L3315; Eq. 8.59 L3997; Table 6.1 L2827–2834)
