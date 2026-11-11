# 73 — Interrogator: DECISION RG-1 re-check of commits 814264c / f439039 / 3b6da2b (file 72's corrections C1, C2 and the two pointers) — SURVIVES

phase-05h (session 2). Narrow decision-mode re-check against file 72's required texts and the restored seat files. Corpus present, revision c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (not load-bearing: RG-1 carries no acoustic claim; every check below is against file 72, the seats' files, the decider files, the code and the plan texts). Note on method: this environment has no git access, so item 6 is checked by reading the current texts named in file 72 and the numbers they carry, not by diffing the commit; said so where it matters.

## Verdict: SURVIVES

C1 and C2 are applied as file 72 required, both pointers are applied, the restored seat files carry their rounds in order and every quotation spot-checked in files 64–71 matches them, the ledger row and brief are accurate, and no number, threshold or rule moved beyond file 72's texts. Two notes for the record, neither a correction (items 2 and 3).

## 1. C1 — AX38 4c "Register at the pinned W_max" (`docs/BUILD_PLAN.md:139`)

All four clauses read as file 72 required, word for word:
- Linux: "median 2 043 ms, the growth-bound baseline until RG-1 (now the in-window mean 2 068 ms, bound 1.10 × 2 068 = 2 275 ms, asserted in-window: 'Assertion form' below)" ✓; "on the final 05h run 42924781618 it read 30.18 s (median 2 092 ms, within the then-bound ≤ 2 247 ms)" ✓.
- macOS: "median 2 106 ms, min 1.84 / worst 2.67 s, the baseline until RG-1 (an out-of-window row, flutter +11 %; now the in-window mean 1 817 ms, print only)" ✓.
- Windows: "listed from that run under §5 (d), baseline 2 589 ms until RG-1 (a red run; now the in-window mean 2 028 ms)" ✓.

Arithmetic redone: 1.10 × 2 068 = 2 274.8 → 2 275 ✓ (rounded to the nearest ms); then-bound 1.10 × 2 043 = 2 247.3 → 2 247 ✓; macOS flutter on run 42909003931: 537 / 484 = 1.1095 → +11 % ✓ (file 56 L29: "(file 31: 7.52 s / 14 = 537)"; reference 484 from the three measured runs). The pins agree with the code: `tests/unit/test_diffuse_records.cpp:104-106` carry 2068.0 / 1817.0 / 2028.0, `absoluteAsserted` true / false / true, and `kGrowth = 1.10` at L86.

One baseline per entry: each entry now names the pre-RG-1 figure as history ("until RG-1") and one current baseline (2 068 asserted in-window; 1 817 print only; 2 028 asserted in-window), which is what the row's "Assertion form" block (same line: "baseline median the mean of in-window runs (Linux 2 068, Windows 2 028; macOS 1 817, print only); never a red or out-of-window run") and phase-05i scope 3 (`docs/phases/phase-05i.md:79-81`) say. The two-baselines-per-entry defect of file 72 C1 is closed.

## 2. C2 — phase-13 Raise item 5 (`docs/phases/phase-13.md:21-25`)

Current text: "Release machines bought once, no standing runner (Seat 7, file 60 round 1: larger hosted runners ≈ €100–130/month, a standing cost before any revenue, and the macOS larger runner still a shared VM; decider files 64 item 7 and 66 §7: a person's purchase); on them the strict 30 s and the 1.10 growth bound are asserted on all three OSes (AX41) and the register entries close or the absolute CHECK returns on named hardware."

- Citation exact: the restored `docs/review/phase-05h/60-seat7-restore-gate-runner-variance.md` round 1 (L5–32, before the `---` at L35 and "## Round 2" at L37) carries at L22: "a standing ≈ €100–130/month before any revenue … and the macOS larger runner is still a shared VM, so the variance is shifted, not removed" and "Sustainable for one founder only as the 'release machines' of AX41 used by hand at each release — a one-off purchase, no standing cost (criterion 2) — not as a standing CI runner." The three clauses the item attributes to Seat 7 (the price, "standing cost before any revenue", "still a shared VM") are Seat 7's own words. File 72's condition ("save that round into file 60 first; the citation then stands and the text may keep them") is met.
- Decider quotation matches the restored round: file 64 L31 (final-form item 7) "release machines bought once, no standing runner (Seat 7: a Phase 13 Raise item, a person's purchase)" and file 66 L24 (item 7) "release machines (bought once, Seat 7; a Phase 13 Raise item)" are faithful readings of file 60 L22 and L30 ("Buying release machines → Maisara (a person's money)"). "Files 64 item 7 and 66 §7" is the right locator for both.
- Gone: "One macOS and one Windows machine", "Linux on the dev box". Grep over `docs/phases/*.md`, `docs/BUILD_PLAN.md`, `docs/PRD.md` for "dev box", "One macOS": no hits; "€", "/month", "shared VM" occur only at `phase-13.md:22-23`, now sourced.
- Nothing beyond the decision: "strict 30 s and 1.10 growth bound asserted on all three OSes (AX41)" = file 66 item 7 / AX41 L142; "the register entries close or the absolute CHECK returns on named hardware" = file 64 L52 reversal clause, as file 72's required text had it.

Note (no action): Seat 7's round 1 derives the €100–130 from inputs it marks `[Observed]` (runner minute prices, researcher F18) and `[Hyp]` (≈ 30 min per OS build, the plan price ≈ $4/user/month, "researcher to confirm"). The Raise item reports it as Seat 7's figure in a question to Maisara, not as a plan number or threshold; that is the right status. If the plan-editor touches the item again, "≈ €100–130/month (Seat 7's estimate, inputs partly [Hyp])" would say so; not required.

## 3. The two pointers

- "recorded median" pointer, all three named places: `docs/BUILD_PLAN.md:96` (AQ10) "median-of-10 restore ≤ 1.10 × the recorded median (since RG-1: the pinned baseline median, (b))" ✓; `docs/BUILD_PLAN.md:139` AX38 "Conditions (board answer J1 …)" paragraph, same phrase ✓; `docs/phases/phase-05h.md:151-152` same phrase ✓.
- AX41 in the AMENDS parenthetical: `docs/BUILD_PLAN.md:139`, the RG-1 line at the end of the row: "`AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (AQ10 amended (1), AX38 4c and AX41: D-H1 (v)(a)–(b) as above; phase-05h §5 "Blocking"; phase-05i scope 3; phase-07c condition 9 packet; phase-13.)" ✓ (now matches file 70 L35 and the brief L223 as file 72 asked).
- The two "per OS in the job summary" instances untouched: `docs/BUILD_PLAN.md:139` AX38 (i) register entry ("prints the median-of-10 wait against 1.10 × the recorded median per OS in the job summary (a print, never a CHECK …") and `docs/phases/phase-05h.md:355` ✓. Both record the `[diffuse-quiesce]` print, whose "recorded median" is its own (the quiesce wait), not the restore gate's; correctly left alone.

Note (no action, minor): a fourth D-H1 (v) summary carries the same phrase without the pointer: `docs/phases/phase-08.md:210` "a registered defect with the growth bound (median-of-10 restore ≤ 1.10 × the recorded median) elsewhere". File 72 named only the three above and rated the phrase IMPRECISE, recommended not required; the same rating applies here. phase-08 names the governing rule first ("The gate runs under the AX38 4c register rule", L207–208), so a reader reaches (b)'s current wording. Optional pointer, same words, if phase-08 is touched again.

## 4. The restored seat files 57 / 58 / 60 / 61

Structure (headers, in order, nothing duplicated as read in full):
- `57-seat5-…md`: round 1 "SEAT 5 POSITION" L5–26; `---` L29; "## Round 2: Seat 5's B5 answers (i)–(vi) and re-rating (file 59)" L31; `---` L50; "## Round 3: Seat 5 on the macOS GROWTH-only trigger (interrogator file 69)…" L52. ✓
- `58-seat3-…md`: round 1 L5–38; "## Round 2" L43; "## Round 3" L66; "## Round 4" L83; "## Round 5" L90. ✓
- `60-seat7-…md`: round 1 L5–32; "## Round 2: Seat 7's cell on (x″) as corrected by interrogator file 65" L37. ✓ (File 72 L5's defect, "begin with a blank line, `---` and Round 2", is closed.)
- `61-seat6-…md`: round 1 L5–40; "## Round 2: Seat 6 on the macOS GROWTH-only trigger (interrogator file 69)…" L45. ✓

"Nothing lost" cannot be proved against git from here; the test available is whether every quotation the decider and interrogator made from these seats at the time is now found in the files. Spot-checks (two or more per seat), all found verbatim or as faithful paraphrase:
- Seat 5: file 64 L36 / L47 "a record nobody reads … mitigated by a machine-readable summary line and Phase 13", "each red masking pluginval/auval on that OS" → file 57 L18, L16 ✓; file 64 K3 "pooled CV 5.4 %; k = 1.16 … 1.20 pinned" → L37 ✓; file 66 L26 "print … do not assert" → L37 ✓; file 71 L10 "Alternative if the decider wants it armed now: bound 1.15 × … 2 172 ms: 0 of 4 rows over … Then 0 / 1 holds" → L58 ✓.
- Seat 3: file 64 L37 "(x′) now 1 / later 2 … conditions that move (x′) to 1 / 1" → file 58 L47, L53 ✓; file 64 K2 "Windows 3.08/2.64 = 1.17, Linux 3.24/2.85 = 1.14" → L15 ✓; file 66 L32 "holds at 1 / 1 … c1 + c3 … two conditions" → L70–76 ✓; file 68 L9 "(x‴) holds at 1 / 1 … no new condition" → L85 ✓; file 71 L12 "1 / 1 holds at 2 172 ms … No new condition" → L92 ✓.
- Seat 7: file 64 L40 and file 65 L17 "(f) 1 / 1 … condition: k and the band derived, not 1.10 by analogy" → file 60 L18 ✓; file 64 L43 "(a) … 2/2 from Seats 2, 3, 6, 7" → L14 "(a) 2 / 2" ✓; file 66 L11 / L35 and file 67 L11 "now 1 / later 1, unchanged … Condition: window ±5 %" → L41, L45 ✓; file 64 L31 / file 66 L24 (item 2 above) → L22, L30 ✓.
- Seat 6: file 64 L39 "(f) 0 … (x) 0" and "(x)/(e)/(f) later 1 → 0: every run prints one machine-readable line … four fields … §0 carries the figures" → file 61 L19, L30 ✓; "B6 (i) … 0 on all four" → L23 ✓; file 71 L11 "priced 'later 1, not 2' on the 1 999 ms form with ≈ 39 % exposure … 'buys nothing: the entry is already in the register with that same remedy'" → L49 ✓.

No quotation in files 64–71 points at text that is absent from the restored files.

## 5. Ledger row P05H-RG-1 (`docs/review/ledger.md:2265`) and the brief

- (d) sentence: "(d) a broken assertion or the macOS trigger is a defect: a timing entry → phase-07c conditions 9–10; a work-pin entry → the code change named, re-pinned only with a CHANGELOG reason (file 71)". This is file 71 L19's split form ("a timing entry: phase-07c conditions 9–10; a work-pin entry: the code change named, re-pinned only with a CHANGELOG reason") in summary; the "no re-run, no W_max cut, no range change, no seam" clause is carried in the row's plan-text column by AX38 L139 and phase-05h L401–404, which the row cites. Faithful; file 72 item 5 (iv)'s minor is closed.
- File 72 note: "diff check file 72 SURVIVES WITH CORRECTIONS: C1 the AX38 register paragraph's pre-RG-1 baselines, C2 phase-13 Raise item 5, applied 814264c; re-check file 73" — accurate to file 72's verdict (L7) and its two corrections (L11, L17).
- Session brief `docs/sessions/2026-11-10-phase-05h.md:147` (log row 17): names files 62/58/57/61/60, 63, 64/66/68/70, 65/67/69/71 with their outcomes, 67f13f3, e87a47f, file 72's verdict, "C1/C2 applied 814264c", "the seat files 57/58/60/61 restored from git history at f439039: their earlier rounds had been overwritten on append", and "the re-check file 73" as open. Accurate against files 65 (FALLS on one component), 67 (TENSION MISREAD on one clause), 69, 71 and 72 as read.

## 6. Nothing beyond file 72's texts (D-H1 (v)(d))

Checked by reading the current texts (no diff available here):
- The only numbers new since e87a47f are the two bounds in the C1 clauses (2 275 and the then-bound 2 247); both are derived figures (1.10 × 2 068; 1.10 × 2 043) of constants already pinned, and no test asserts on 2 275 as a literal (the code computes `kGrowth × baselineMedianMs`, L86, L104). All occurrences of 2 068 / 2 028 / 1 817 / 2 172 in `docs/BUILD_PLAN.md` and `docs/phases/*.md` (grep) agree across AX38 L139, §6 L478, phase-05h L381–390 and phase-05i L81, L89; "1 999" and "1 889" occur in no plan text.
- W_max: `docs/BUILD_PLAN.md:96` and `:142` still pin 3.05 M per emitter, n\*_max 1 024, ratio 1.02; no range change (AX6 untouched); no seam; (d) in AX38 L139 and `docs/phases/phase-05h.md:401-404` still reads "no re-run, no W_max cut, no range change, no seam", with the split remedy; `kGrowth 1.10`, `kGuardPct 5.0`, `kRatioWarn 1.20`, `kMacGrowthTriggerMs 2172.0` (`test_diffuse_records.cpp:86-93`) unchanged from file 72's record; the 30 s stays asserted at the flutter scene on every OS (L98–101 `strict30s` true) and on the release machines (AX41 L142, phase-13 item 5).
- §6 row `docs/BUILD_PLAN.md:478` is as file 72 rated it ("no threshold loosened (30 s and 1.10 kept where asserted)"); no new §6 row was needed (no assumption value, threshold or golden changed by 814264c: the edits are provenance wording in a row already amended by RG-1, a Raise item, and a cross-reference).

Nothing in the checked texts loosens, cuts or re-ranges.

## Questions for the decider

None. The decision stands as applied; the two notes above (Seat 7's `[Hyp]` inputs behind the € figure; the phase-08 L210 phrase) are optional pointers, not corrections.

Files: /home/user/makroof/docs/review/phase-05h/72-interrogator-RG-1-diff-check.md, /home/user/makroof/docs/BUILD_PLAN.md (L96, L139, L142, L478), /home/user/makroof/docs/phases/phase-13.md (L21–25), /home/user/makroof/docs/phases/phase-05h.md (L150–152, L355, L366–406), /home/user/makroof/docs/phases/phase-05i.md (L77–93), /home/user/makroof/docs/phases/phase-08.md (L207–211), /home/user/makroof/docs/review/phase-05h/57-seat5-restore-gate-runner-variance.md, 58-seat3-restore-gate-runner-variance.md, 60-seat7-restore-gate-runner-variance.md, 61-seat6-restore-gate-runner-variance.md, 64-decider-decision-RG-1.md (L31, L36–43, L47, L52), 66-decider-decision-RG-1-r2.md (L11, L24, L26, L32, L35), 68-decider-decision-RG-1-r3.md (L9), 70-decider-decision-RG-1-r4.md (L10, L12, L35), 71-interrogator-RG-1-r4.md (L10–19), 65-interrogator-RG-1-r1.md (L17), 67-interrogator-RG-1-r2.md (L11), 56-orchestrator-restore-gate-runner-variance.md (L28–30), /home/user/makroof/docs/review/ledger.md (L2265), /home/user/makroof/docs/sessions/2026-11-10-phase-05h.md (L147), /home/user/makroof/tests/unit/test_diffuse_records.cpp (L85–107).
