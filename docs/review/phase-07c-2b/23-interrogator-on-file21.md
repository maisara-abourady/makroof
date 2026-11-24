
## 23: Interrogator on decider file 21 (L4-COV round 2; L4-COV-P; R5)

Read-only. For the orchestrator to save as `/home/user/makroof/docs/review/phase-07c-2b/23-interrogator-on-file21.md`.

**Corpus:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Verdict in short:**
- **L4-COV (E): SURVIVES WITH CORRECTIONS.** C and E really do tie at 6, and B-second is at 7. The decisive cell, Seat 1's B-second rating, is faithfully read from its conditions. All the figures recompute. New builder file 25 does not fire any reversal condition, but it changes what the asserted (b) actually checks, and the record has to say so (C7).
- **FOR MAISARA L4-COV-P: SURVIVES WITH CORRECTIONS.** The conclusion holds, but three PRD glosses overstate their passages.
- **R5(a)/(e), option (c): SURVIVES WITH CORRECTIONS.** The cells, the conditions and the CI step all match the seats and the tree. Two statements need fixing: one figure is unsourced and NFR-4 is misquoted.
- **§6 texts:** faithful to the seats and to file 15's corrections, with one exception. The cut-window start is misdescribed, and that wording would be pre-registered verbatim.

**Files read:**
- Review files 21, 15, 13, 17 §6, 18, 25, 12-seat1, 12-seat3 (grep), 12-seat8, 16-seat5, 19-seat3, 19-seat7, 19-seat9.
- `docs/board/README.md` (convening table; "Who answers Maisara's questions"); `.claude/agents/decider.md` §1–§5; seat 5 §18.
- `docs/PRD.md` L1–112, L150–165; `docs/BUILD_PLAN.md` L117 (AQ9) and a grep for 08-3; `docs/phases/phase-08-3.md` L34–158.
- `.github/workflows/ci.yml` L386–436; `tests/unit/test_ax49_l4.cpp` (whole file); `tools/ci/ax49_l4.py` L149–186, L455–486, L697–764.
- Kuttruff §3.6 (L1972–1976), §3.7 heading (L1988), §3.8 (L2120–2122), Eqs. 4.12 and 5.24 (L2242, L2607), Table 6.1 (L2827–2834).

### Recomputed figures

| figure | working | verdict |
|---|---|---|
| (a) margin 4.17 dB | 20 − 15.83 (file 18 §1) | CORRECT |
| (b) margin 2.29 dB, strongest band 125 Hz | 20 − 17.71. K3′ matches file 15's K1+K3 to within 0.1 dB in every band (63: −49.7+34.9 = −14.8; 2k: −52.6+34.9 = −17.7). | CORRECT |
| Depths 18.72 / 23.19 / 40.14 dB | Kuttruff §3.8 Eq. 3.70 (T is the time for a 60 dB decay). 60 × 2.496 = 149.76; /8 = 18.72; /6.457 = 23.19; /3.731 = 40.14. | CORRECT |
| Air is 63 % of A at 4 kHz; T60 3.73 s | Kuttruff Eq. 5.24 (Eyring + 4mV) and Table 6.1 (6.84·10⁻³ m⁻¹ at 4 kHz, 50 % RH). 4mV = 27,360 m². Surface term 0.161·10⁶/8 − 4,320 = 15,805 m². 27,360/43,165 = 0.634, and 0.161·10⁶/43,165 = 3.730 s. Cross-check with the engine's own numbers: S·(−ln(1−0.23188)) = 15,828.5 m² gives 0.634 and 3.728 s. Back-solving 3.731 s gives m = 6.83·10⁻³, which agrees with the table. | CORRECT. Cite Eq. 5.24 beside Table 6.1. |
| 2 kHz T60 6.46 s | 4mV = 9,120 m²; 0.161·10⁶/24,925 = 6.46 s | CORRECT |
| File 25 median of (b) +1.59 dB; 3 of 16 red | Sorted margins: the 8th is 1.58 and the 9th is 1.60, so the median is 1.59. The negative ones are −3.98, −0.95 and −0.34. | CORRECT |

### Decision ledger

| decision | check | item | verdict | evidence | outcome | question for the decider |
|---|---|---|---|---|---|---|
| L4-COV | Q1–Q5 / file-15 corrections | the answers to Q1–Q5; restated loosening reasons (i)/(ii); R5(c) attribution; C9 header; strongest-objection sentence; Decided-for-Maisara line | faithful | Q1: a FOR MAISARA now exists and shows E and B-second against L105, L101, L17 and L55 with Seat 7's hours. Q2: Seats 7 and 9 were convened. Q3: (b) is accepted and the K5 answer withdrawn. Q4: the tie is conceded and Seat 3 was asked (19-seat3 §4, §5(2)). Q5: R5 was held until 16-seat5. §6 row 2 carries reasons (i) and (ii) as restated. The test header L1–9 now cites files 9 and 13, asserts 1e−9, and has no CLAUDE.md quotation; L156–157 record the measured values. The Decided-for-Maisara line uses Seat 9's form with the cause. | — | — |
| L4-COV | convening | Seat 5 "not required for the stimulus options" | faithful on its stated ground; incomplete in the reversal | Row 5 lists "CI gates and sanitizers". No option adds or moves a gate, and B-second adds about 30 s to an existing kit test (file 18: build 30–32 s). But under reversal condition 1 (Seat 1's B-second later cell = 0), B-second reaches 6 + Seat 5's cell, so Seat 5's cell then decides between 6 and 7. | correction: reversal condition 1 must convene Seat 5 as well as Seat 1 | Q3 |
| L4-COV | convening | Seats 2, 4, 6 not required; Seats 1, 3, 7, 8, 9 convened | faithful | Unchanged from file 15. Seats 7 and 9 were heard (19-seat7, 19-seat9). | — | — |
| L4-COV | map | Seat 1's B-second cell, 1/1 read from conditions (decisive: 7 against 6) | faithful | B-second appeared in Seat 8's round, after Seat 1's, so reading from conditions is allowed (decider.md §4). **Now 1:** Seat 1 says "a loosened criterion stays at 1", and the pad arm is loosened. Seat 3 adds that the bright arm also runs E's own (a) and (b). **Later 1:** Seat 1's E-later reason is the null-wording obligation, and that persists for the pad arm. | stands, decisive; confidence medium is correct | Q3 |
| L4-COV | map | S3, S7, S8, S9 cells for C, E and B-second | faithful | **S3:** C 0/1 and E 0/1 ("not one point above C"); B-second 0/1. **S7:** E 0/1, C 0/1; B-second 1/"0–1", resolved to 0 by K9. **S8:** C 0/1; E read from "C: no condition from me"; B-second 1/1 per its condition. **S9:** 0/1 with its wording and 1/2 without; B-second 0/1. | — | — |
| L4-COV | map | D, Seat 7 cell: "0/1 (read: the same hours as C)" | TENSION MISREAD (non-decisive) | Seat 7 never rated D and gave no condition for it. D rebuilds the chord (A half, never built). Seat 7's E-now-0 ground is that the build "cannot go red unless the code changes", and its B-second now-1 counts "one more stimulus build … seal surface". So 0 does not follow. D can only rise from 7, so the winner is unchanged. | correction: mark the cell unrated; D ≥ 7 | — |
| L4-COV | map | "Four are read from conditions" (21-L5; confidence line) | IMPRECISE | Six cells are marked: E/S1, E/S8, D/S7, D/S8, D/S9 and B-second/S1. B-second/S7 is resolved by K9 as well. | correction | — |
| L4-COV | debt | rows S1, S3, S7, S8, S9 (later 1 on E) | faithful | Every later-1 cell has a row. The phases named exist (07d, 13-5). S9's row carries "1, not 2" on the cause clause, as 19-seat9 §4 says. | — | — |
| L4-COV | claim 21-L4 / K9 | the held-chord L4 does not recur at 08-3 | CORRECT (from the plan) | `phase-08-3.md` has no AX49 held-chord item. L122's "(phase-08 L4)" is the large-hall surround item, and BUILD_PLAN's 08-3 rows contain no L4 rerun. Seat 7's stated condition is therefore met, so B-second's S7 later cell is 0. | — | — |
| L4-COV | ordering | steps 1–6 | CORRECT | No bound is broken and there is no 3. A and B are out on their 2s. Max 1 is the floor (Seat 1: "C and E, from 1 to 0: none available"). Sums: C 6 = E 6 < D 7 (≥ 7 after the correction above) = B-second 7. Step 6 is a tie (Q4). | — | — |
| L4-COV | ordering | step-7 ground: "an automated assert rather than a print … 'every behaviour has an automated check'" | IMPRECISE; weakened by new evidence | **The quotation:** CLAUDE.md says "Every DSP behaviour must have an automated check", and decider.md §1 says "every DSP behaviour automatically checked". (b) is a property of the stimulus, so the ground is an analogy. **File 25:** over 16 further tailSeeds with the same chord and S′, the asserted strongest-band form reds on 3 (min −3.98 dB). The median form holds on all 16 (min 2.74 dB), so the reds come from the reference-band draw and not from 2 kHz coverage. **What the assert checks:** the sealed file exactly. On any rebuild that redraws the tail, it is an evidenced ~3/16 chance of a stop that is not a coverage failure. **Why the ground still stands:** it is a tie-break the decider may name, no seat cell changes (Seat 3 rated E later 1 on exactly this risk), and the reversal threshold (median < 0) does not fire. | SURVIVES WITH CORRECTIONS: quote CLAUDE.md exactly, and state file 25's result beside the ground | Q1 |
| L4-COV | claim 21-L1 | (a) 4.17, (b) 2.29, 125 Hz the strongest band | CORRECT | File 18 §1; file 25 §2 (same hashes) | — | — |
| L4-COV | claim 21-L2 (K2) | the depth table, offered as a judgement input | CORRECT | Kuttruff §3.8 Eq. 3.70; working above | — | — |
| L4-COV | claim 21-L3 (K8) | air is 63 % of A at 4 kHz; 3.73 s | CORRECT (cite Eq. 5.24) | Kuttruff Table 6.1 and Eq. 5.24 (also Eq. 4.12); working above | correction (citation) | — |
| L4-COV | K10 | "σ ≈ 3.1 dB … Kuttruff §3.7 Eq. 3.47"; "a red fails safe" | IMPRECISE, not load-bearing | **Citation:** Eq. 3.47 sits in §3.6 (Steady-state sound field, L1974), not §3.7. **Conditions:** it is stated for steady-state transfer functions, not a windowed decaying tail. **"Fails safe":** a strongest-band reference is biased toward red, but luck moves the margin both ways (file 25 spans −3.98 to +3.93 dB), so a lucky draw can pass. **What actually makes K10 non-load-bearing:** the assert tests the sealed, heard file exactly. | correction | — |
| L4-COV | strongest objection | B-second loses at step 5 | holds | Recomputed above. | — | — |
| L4-COV | strongest objection (added) | E's tie-break picks the option whose seal gate fails on about 1 tail draw in 5, while C's print cannot stop the seal | stronger than the one named; does not flip | File 25 (3 of 16). Seat 3 19-seat3 §4 and §8 foresaw this as "a board round … over a margin that was always a single draw". The cells already price it (S3 E later 1 = C later 1), and the stimulus is sealed. | stands; record it | Q1 |
| L4-COV | §6 texts | band-coverage paragraph, window start: "from the chord's release sample plus round((L_f − alignmentShiftS)·fs)" | IMPRECISE (would be pre-registered) | **From the code:** `cut_window` (L708–710) starts at `m["end"]` + round(…). `chord_marks` L459 sets `end` = release_start + n_rel, i.e. the end of the 10 ms release, not its start. Read as "the release sample", the text places the window 480 samples (10 % of its length) early. | correction: "from the end of the chord's 10 ms release (sample `end`) plus round((L_f − alignmentShiftS)·fs)" | Q2 |
| L4-COV | §6 texts | §0 header, item 14, Checks-before-the-seal, Wording, AX49 fragment, §6 rows 1–2 | faithful | **Wording:** matches 19-seat9 verbatim, and `WORDING_NULL` in `ax49_l4.py` L183–186 matches too. **Row 2:** restates reasons (i) and (ii) per file 15 and keeps "the 20 dB tolerance is unchanged". **Checks:** they match 16-seat5 §6. **What remains in file 17:** the "A red is a stop, never loosened" tail of the checks bullet is outside the replaced span and survives. | — | — |
| L4-COV | §6 / record | the ensemble result is absent from the texts that will be committed | IMPRECISE (record) | Row 2 and §7 say the ensemble is "printed". The measured 3/16 reds, and the fact that the median form never reds, now exist (file 25). Seat 3 asked for the ensemble "so the reviewers can see whether 2.29 dB is typical or lucky". | correction: the record states the result, not only that a print exists | Q1 |
| L4-COV | PRD proxy (acceptance check) | E, C, D, B-second, B, A against L105, L13, L101/L49, L17, L55 | faithful in conclusion; one gloss IMPRECISE | **Each surviving option is shown.** **The gloss:** L101 reads "Accuracy is the top priority; CPU load and latency may be high…", so "rank accuracy against CPU and latency only" adds "only". **Why it does not point to B-second:** B-second's added accuracy evidence is contested in direction (K5; Seat 8 "may also make the test more lenient"), and it does not reach the excluded band (Seat 9, "4 kHz at a 40 dB depth"). | correction | — |
| L4-COV-P | PRD proxy | "L13 … The board fills that role here"; "PRD … hands their design to the Expert … therefore the board's call" | IMPRECISE | **L13** says only that such decisions "belong to the dedicated Spatial Audio Expert project". **The README** (PRD open questions) keeps Q1–Q10, including Q9 (listening-test thresholds, PRD L164), with the Expert, so the board is not the Expert. **The grounded route:** AQ9 (BUILD_PLAN L117: "the phase checklists until the Expert defines a formal MUSHRA/ABX protocol") plus the board-governed AX47/AX49 defaults, which a board DECISION changes (README item 1). | correction (restatement below) | Q4 |
| L4-COV-P | PRD proxy | "The PRD is silent between the two, so the board's ordering governs" | IMPRECISE (self-contradicting wording) | **By README item 3(a):** "PRD is silent" is the NEEDS MAISARA case. **What the answer actually shows:** no two requirements pull apart (both options serve L105 and L17; L101 and L55 are neutral), so the acceptance check passes (README, "Accepting a surviving DECISION"). That is not case (a). **It is also not "ordering alone":** it rests on L105, L17, L101 and L55. | correction | Q4 |
| L4-COV-P | PRD proxy | options against L105, L13, L101, L17, L55; veto line; amends nothing | faithful | Each passage was opened. L17 "producers and DJs" and L55 "no fixed deadline" are as quoted. No recorded decision of hers is touched. | — | — |
| R5 | convening | Seats 5 and 7 convened; Seat 3 not required because "under (c) … its hand-off does not arise" | faithful in effect; reason circular | **The hand-off:** Seat 5's hand-off to Seat 3 concerns option (a): "(a) becomes 1/1 if Seat 3 accepts having no Release evidence". **The circularity:** reasoning from the chosen option does not dispose of it. **Why it is harmless:** (a) at 1/1 would not lower the maximum below (c)'s 1, so step 4 does not require composing it, and (a) stands at Seat 5's unconditional 1/2. | correction (reason) | — |
| R5 | map | (a) 1/2, (b) 2/2, (c) S5 1/1, S7 1/0; sum 3 | faithful | 16-seat5 §3–4: "(a): 1", later "(a): 2", "(b): 2" / "2", "(c): 1" / "1". 19-seat7 §3–4: R5(e) "1" now, "0" later. | — | — |
| R5 | conditions | tag, budgets, re-entry fix, twin, seal evidence, run started by the session, sitting after green, durations and RSS, header fix | faithful | **Seat 5's conditions** (16-seat5 §6) and **Seat 7's** (19-seat7 §6) are all carried. **One change:** the decider makes a still-over-300 s result a stop to Seats 5 and 3, instead of moving to the twin automatically. That is stricter and never hides the case, as Seat 5 requires. **The tree:** `ci.yml` L409–418 has the step after "Build (release)", separate from Benchmark, with `--durations yes` under `xvfb-run` on Linux. The case is tagged exactly `"[ax49-l4]"`, and the header is fixed. | — | — |
| R5 | claim | "Release is measured at 2.5 s on Linux" | NOT CHECKABLE (unsourced) | It appears in no review file, the test header or a CI log I read. Seat 5 relayed "tens of seconds". Not load-bearing against the 60 s budget. | correction: cite the run, or drop it | Q5 |
| R5 | debt | S5 row: "repaid when all budgets are met at half the limit" | IMPRECISE | The budgets already are half the 600 s limit (16-seat5 §6). | correction: "repaid when the first Debug and ASan `--durations` readings are within the 300 s budgets" | — |
| R5 | PRD proxy | "NFR-4's three platforms are covered"; Decided-for-Maisara "runs on every PR" | IMPRECISE | **NFR-4 (L108):** "VST3 and AU on macOS and Windows". Linux is a CI platform, not an NFR-4 one. **"Every PR":** CI starts only on open/reopen/ready or by hand (CLAUDE.md "When CI runs"). | correction: "macOS and Windows (NFR-4), plus Linux in CI"; "in every CI run of a PR" | — |

### Outcomes

**L4-COV (E): SURVIVES WITH CORRECTIONS.** The winner is unchanged.
- C1: D's Seat 7 cell is marked unrated (D ≥ 7).
- C2: "four" becomes "six" read-from-conditions cells.
- C3: reversal condition 1 reads: "Seat 1 rates B-second's later cell 0: re-run steps 5–6 with Seats 1 and 5 convened (Seat 5's B-second cell then decides 6 against 7)".
- C4: K10 cites Kuttruff §3.6 Eq. 3.47 (steady-state field) and drops "luck can only make it red". It reads instead: "the assert tests the sealed file exactly; over seeds the margin moves both ways (file 25)".
- C5: K8 cites Kuttruff Eq. 5.24 with Table 6.1.
- C6: the step-7 ground quotes CLAUDE.md as "Every DSP behaviour must have an automated check" (by analogy for a stimulus property).
- C7: the ground and the §6 record (row 2 and §7) state file 25's result: "the asserted (b) reds on 3 of 16 further tailSeeds (min −3.98, median +1.59 dB); the median-referenced form holds on all 16 (min 2.74 dB); the sealed seed passes at 2.29 dB".
- C8: the cut-window start text is changed as in the ledger.
- C9: the PRD digest's L101 gloss drops "only".

**FOR MAISARA L4-COV-P: SURVIVES WITH CORRECTIONS.** Replace the last reasoning line and the L13 gloss with: "No cited requirement points to either option: both serve L105 and L17, and L101 and L55 are neutral. So the acceptance check passes and the board's ordering decides (E 6, B-second 7). Listening-test thresholds and protocol are the Expert's (L13, L105, Q9). Until then the L4 design runs on AQ9's default and the board's AX49 decisions." The "PRD is silent" and "the board fills that role" wordings are withdrawn. The answer itself is unchanged.

**R5 (c): SURVIVES WITH CORRECTIONS.** Source or drop the 2.5 s figure; correct the NFR-4 wording, "every PR", the S5 "repaid when" and the Seat 3 not-required reason.

**NEEDS MAISARA:** none is warranted. None of the three cases applies.

### Questions for the decider (most consequential first)
1. File 25 shows the asserted strongest-band (b) reds on 3 of 16 tail draws of the same chord and room, while the median form never reds. Will you restate the step-7 ground and the committed record (§6 row 2, run sheet §7, Decided for Maisara) with that result? Do you hold that an assert which a tail redraw fails about 1 time in 5 is still the better verification ground than C's print? (Your reversal threshold, median < 0, did not fire, and I do not ask you to move it.)
2. `cut_window` starts at `m["end"]`, the end of the 10 ms release (ax49_l4.py L459, L709). Will the pre-registered text say so, instead of "the chord's release sample"?
3. Under reversal condition 1, B-second's sum is 6 plus Seat 5's cell. Will the condition name Seat 5 as well as Seat 1?
4. Will L4-COV-P drop "The PRD is silent between the two" (README case (a)) and "the board fills that role" (README keeps Q1–Q10 with the Expert)? Will it rest instead on the acceptance check plus AQ9 and the board's AX49 decisions?
5. Where was `[ax49-l4]` measured at 2.5 s in Release on Linux? Give the run or log, or drop the figure.

**Files:**
- /home/user/makroof/docs/review/phase-07c-2b/21-decider-l4-coverage-r2.md
- /home/user/makroof/docs/review/phase-07c-2b/25-builder-l4-ensemble.md
- /home/user/makroof/docs/review/phase-07c-2b/15-interrogator-on-file13.md, 13-decider-l4-coverage.md, 17-decider-m3-r4.md (§6), 18-builder-l4-coverage-applied.md
- /home/user/makroof/docs/review/phase-07c-2b/12-seat1.md, 12-seat8.md, 16-seat5.md, 19-seat3.md, 19-seat7.md, 19-seat9.md
- /home/user/makroof/docs/PRD.md (L13, L17, L49, L55, L101, L105, L108, L112, L164)
- /home/user/makroof/docs/BUILD_PLAN.md (L117, AQ9)
- /home/user/makroof/docs/phases/phase-08-3.md (L38–42, L122)
- /home/user/makroof/.github/workflows/ci.yml (L406–418)
- /home/user/makroof/tests/unit/test_ax49_l4.cpp (L1–9, L156–190)
- /home/user/makroof/tools/ci/ax49_l4.py (L149–186, L459, L708–728)
- /home/user/makroof/docs/corpus/kuttruff-room-acoustics.md (L1974, L1988, L2120–2122, L2242, L2607, L2827–2834)

