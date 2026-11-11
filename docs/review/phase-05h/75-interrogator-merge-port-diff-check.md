# Interrogator — diff check of the phase-05h plan-text port (merge of main / PR #28 into the 05h branch, head 271d378)

Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d (`docs/corpus/SOURCE_COMMIT`). Read-only check. Saved by the
orchestrator from the interrogator's hand-back (2026-11-11); corrections C1–C8 applied in the commit that adds this file.

## Outcome: **SURVIVES WITH CORRECTIONS**

Every 05h addition is in the merged tree exactly once (or in every copy the split deliberately carries), verbatim, at the place the umbrellas' "Where the original items went" tables assign; main's split text is intact; the two hand resolutions (AQ10 row, §6 order; ledger block order) are correct. No placement contradicts D-PS1–D-PS4 or 07c-c1…c3, and no lead seat changes. The corrections are pointer sentences, headings and the §6 row that the port left behind, plus one size annotation. None changes a value.

The port introduces no new acoustic FACT or NUMBER: every figure in the ported blocks was rated in files 21, 26, 28, 71 and carried verbatim. The only corpus citation inside a hand-merged row (AQ10: "1 jnd of G, Vorländer Table 6.1") is pre-existing on both sides and CORRECT [Vorländer, Table 6.1: Level, G, 500–1000 Hz, 1 dB].

## 1. Completeness (every `.ours.wdiff` hunk → merged tree)

| source hunk (`.ours`) | merged location | verbatim | count |
|---|---|---|---|
| phase-07c L20–28 (§0 ¶1, H1-F1 wording) | `docs/phases/phase-07c.md` L20–28 | yes | 1 |
| phase-07c L30–47 (two "Scope extended" ¶) | phase-07c.md L30–46 | yes | 1 each |
| phase-07c L73–76 (§3 bullet "Next phase after 05h") | phase-07c.md L73–76 | yes | 1 |
| phase-07c L95 (§5 heading) | phase-07c.md L82 | yes | 1 |
| phase-07c L125–127 (condition 7) | `phase-07c-1.md` L79–81 | yes | 1 |
| phase-07c L131–176 (conditions 9, 10, 11) | phase-07c-1.md L82–127, labelled "(phase-07c condition 9/10/11)" | yes | 1 each |
| phase-07c L183–185 (A2) | phase-07c-1.md L145–148 | yes | 1 |
| phase-07c L200–206 (A10, A11) | phase-07c-1.md L161–167, labelled | yes | 1 each |
| phase-07c L224–229 (§9) | phase-07c.md L106–112; phase-07c-1.md L131–137; phase-07c-2.md L53–59 | yes | 3 (by design: §9 "umbrella (cited in both)") |
| phase-08 L207–213, L215–216 (scope 10) | `phase-08-4.md` L58–64, L66–67 | yes | 1 |
| phase-08 L278–280 (AC13) | phase-08-4.md L82–83 | yes | 1 |
| phase-11 L59–69 (display rule) | `phase-11-3.md` L37–47 | yes | 1 |
| phase-12 L61–71 (outdoor bullet) | `phase-12-2.md` L56–66 | yes | 1 |
| phase-13 L21–25 (R5) | `phase-13-1.md` L23–27; `phase-13-5.md` L23–27 | yes | 2 (by design: D-PS4 instruction 5) |
| phase-13 L89–94 (scope 6 trace results) | phase-13-5.md L58–63 | yes | 1 |
| phase-13 L99–102 (Windows-on-ARM) | `phase-13-3.md` L30–33 | yes | 1 |
| phase-13 L128 (scope 13 sentence) | `phase-13-2.md` L23 | yes | 1 |
| phase-13 L134–141 (accuracy wording) | phase-13-2.md L29–36 | yes | 1 |

Main's split text: the 07c umbrella equals `phase-07c.theirs` except the brief's edits (§0, §3 bullet, §5 heading and pointer, §9, two table rows, the 07c-1 "owns" cell). Umbrellas 08/11/12 contain none of the ported strings (grep), i.e. no duplicate insertion. Edits beyond the brief's letter, all consistency edits forced by R5 and benign: phase-13.md L41 Labels "R0–R4" → "R0–R5 … (R5 added 2026-11-11)"; phase-13-1.md L8 "same five items"; phase-13-5.md L9 "raises all five" (main's text read "four", `phase-13.theirs` L10/L41).

## 2. Placement against the split decisions

- Conditions 9–11 → 07c-1: forced by the table (every condition other than 1, 3, 8 is 07c-1's) and by their subject (threading of restore/`reset()`, host entry points, a CI guard: Seat 5's row). Lead seat unchanged. Umbrella §5 pointer names 9–11 and "condition 10 is 07c-1's first step" (L88–90) ✓. A10/A11 → 07c-1 ✓ (table L156).
- Accuracy wording under 13-2 scope 1 ✓ (S13 → 13-2, D-PS4 Q1 table). R5 in 13-1 and 13-5 ✓ (instruction 5's rule applied to a fifth item; the umbrella table row L56 and the Raise sentence L10 agree). Scope 6 → 13-5 scope 3 ✓, scope 8 → 13-3 scope 3 ✓, phase-08 scope 10 → 08-4 ✓ (table L103), phase-11 scope 8 → 11-3 ✓ (table L94), phase-12 scope 7 → 12-2 ✓.
- **Size flag (not a contradiction, a stale premise).** `map-07c.md` §2 recorded 07c-1's size M as "not a decision … the sizes (M + S, the original M; neither crosses the two-session limit)" on conditions 2, 4–7 only; conditions 9–11 were not before that round. The plan already carries the overflow routes (condition 9: `phase-07d.md`; CLAUDE.md: `07c-1b`), so nothing is impossible as written, but the sub-phase table's "M" is now unexamined. Recorded as C6 (an annotation) and Q1 (for the decider).

## 3. The hand resolutions and cross-references

- **AQ10 row** (`docs/BUILD_PLAN.md` L115) = `aq10.ours` with exactly one change: "phase-13 scope 1 (13b)" → "phase-13 scope 1 (13b) [now `13-1b`, per the phase-13 umbrella]". No main-only phrase survives in it ("under pluginval's default watchdog, about 2.14 s" occurs only at L480, inside the §6 row that quotes the superseded wording — correct there).
- **§6 order**: 05h rows L471–491 in `.ours` order; main's split row at L492 (byte-identical to `BUILD_PLAN.theirs` L470) after the last 2026-11-10 row; the 2026-11-11 rows L493–498; the new row L499. Chronological ✓.
- **Ledger**: 05h blocks L2200–2265 (five blocks, as in `.ours`), then the phase-split block L2267–2295 = `ledger.theirs` L2200–2227 ✓; the amended P05B2-T5T4-61 row present once ✓.
- **Renamed cross-references** in the 05h texts: "phase-07c §5 condition 9/10/11" → umbrella §5 (L88) names them in 07c-1, each labelled there ✓; "phase-13 Raise item 5" → 13-1/13-5 item 5 labelled ✓; "phase-13 scope 13" → umbrella table S13 → 13-2 scope 1 labelled ✓; "Phase 11 scope 8" → phase-11.md L94 → 11-3 scope 2 labelled ✓; "phase-08 scope 10" → phase-08.md L103 → 08-4 scope 10 labelled ✓; "phase-13 scope 6 / 8" → 13-5 scope 3 / 13-3 scope 3 labelled ✓. **One dangling pointer**: the ledger and the §6 rows say D-H3 (e) / D-H1 applied to "phase-07c §6", but umbrella §6 (L94) still lists only A1–A9 → C1.

## 4. The new §6 row (L499)

Truthful in substance, incomplete in two places: (i) it names "07c-1 (conditions 9–11 and their criteria)" but the port also changed 07c-1's condition 7, A2 and Goal, the §9 copies in 07c-1 and 07c-2, and the umbrella's coverage table and sub-phase row; (ii) "Texts verbatim" overstates: the "(phase-07c condition n / An)" labels and the Goal's "restore watchdog → restore convention" (brief 1b) are edits to main's text. Also "D-H1 (v) / H1-F2: 07c §0" — §0 ¶1 is H1-F1's wording. → C7.

## Corrections (exact old → new)

**C1** `docs/phases/phase-07c.md` L94: "Moved verbatim: A1–A5, A7, A8 to [phase-07c-1](phase-07c-1.md); A6, A9 to [phase-07c-2](phase-07c-2.md)." → "Moved verbatim: A1–A5, A7, A8 to [phase-07c-1](phase-07c-1.md); A6, A9 to [phase-07c-2](phase-07c-2.md); A10, A11 (conditions 10 and 11, added by phase 05h session 2) are in [phase-07c-1](phase-07c-1.md)."

**C2** `docs/phases/phase-07c.md` L133: "Labels: A1–A9 are the §6 criteria in file order;" → "Labels: A1–A9 are the §6 criteria in file order (A10, A11 added 2026-11-10/11 by phase 05h session 2);"

**C3** `docs/phases/phase-07c-1.md` L54: "### Conditions (decider file 47 §4 (iii))" → "### Conditions (conditions 2, 4–7: decider file 47 §4 (iii); condition 9: D-H1 (v) / H1-F2, decider file 19; conditions 10 and 11: D-H3 (e) / H3-F5, decider files 20, 25, 27)"

**C4** `docs/phases/phase-07c-2.md` L60: "- Conditions 2, 4–7 and the decisions D-C1–D-C3: [phase-07c-1](phase-07c-1.md)." → "- Conditions 2, 4–7 and 9–11 and the decisions D-C1–D-C3: [phase-07c-1](phase-07c-1.md)."

**C5** `docs/phases/phase-07c.md` L128: "Order 07c-1 → 07c-2 (forced: under (A), W_max is sized to the restore watchdog, so it cannot be raised until the solve" → "Order 07c-1 → 07c-2 (forced: under (A), W_max is sized to the restore convention (H1-F1; 'restore watchdog' in the convening round's wording), so it cannot be raised until the solve" — the same substitution brief 1b applied to 07c-1's Goal; §0 two paragraphs above already reads "convention".

**C6** `docs/phases/phase-07c.md` L125, 07c-1 row, size cell: "M" → "M (set by the split on conditions 2, 4–7, before conditions 9–11 were added; not re-sized)". An annotation only; whether to re-size is Q1.

**C7** `docs/BUILD_PLAN.md` L499, three substrings: (a) "(D-H1 (v) / H1-F2: 07c §0, §3, condition 9," → "(D-H1 / H1-F1 and H1-F2: 07c §0, §3, condition 9,"; (b) "07c umbrella §0/§3/§5/§9 and 07c-1 (conditions 9–11 and their criteria)," → "07c umbrella §0/§3/§5/§9, its coverage table and 07c-1's sub-phase row, and 07c-1 (conditions 9–11 with A10–A11; condition 7's and A2's wording; the Goal's 'restore convention' per §0; the §9 text also in 07c-1's and 07c-2's Out of scope),"; (c) "Texts verbatim; no value changed." → "Texts verbatim apart from the '(phase-07c condition n / An)' labels and 07c-1's Goal ('restore watchdog' → 'restore convention', the §0 wording of H1-F1); no value changed."

**C8 (optional)** `docs/phases/phase-13.md` L99, `phase-13-1.md` L107, `phase-13-5.md` L111: "Raise items: all four carried by 13-1 (first message) and by 13-5 ("before the beta decision")." → same + " (five since R5, 2026-11-11)." These lines quote D-PS4 instruction 5, so leaving them as a dated quote is also defensible.

Pre-existing, not a port defect (follow-up only): `phase-13-2.md` L22 "sized to pluginval's restore watchdog less D-H1's margin" is the pre-H1-F1 wording on both sides of the merge (`.ours` kept it).

## Questions (for the decider / orchestrator)

1. Does 07c-1's size M still hold with conditions 9–11 (map-07c §2's "neither crosses the two-session limit" was stated on conditions 2, 4–7)? Falsifiable from map-07c.md and the condition texts; if the answer is "re-size", that is the board's, not the plan-editor's.
2. Condition 9 (phase-07c-1.md L91–93) and AX38 4c name "`phase-07d.md` … (CLAUDE.md split rule)" as condition 9's overflow, while the split's G3 names 07c-1's two-session remainder `07c-1b` (phase-07c.md L3, map-07c coverage row "replacing `phase-07d.md` in the size line"). Which reading is recorded: 07d a distinct phase created by D-H1 (v), or the remainder, now `07c-1b`? The text is verbatim as decided, so I did not rate it; the two names should not both point at the same mechanism.
3. Confirm the only edits beyond the brief are the three R5 consistency edits named in §1 (phase-13.md L41, phase-13-1.md L8, phase-13-5.md L9); I could not diff main's 13-1/13-5 files (only `phase-13.theirs` was provided).

## Orchestrator's answers (2026-11-11)

- C1–C8 applied in the commit that adds this file (C8 applied as a dated parenthesis after the quoted instruction).
- Q1 and Q2 are the board's, not this merge's: recorded as follow-ups for the first phase-07c-1 session (its `/fix-plan`
  step: re-size 07c-1 or confirm M with conditions 9–11; record whether condition 9's overflow is `phase-07d.md` or
  `07c-1b`). The pre-existing `phase-13-2.md` "pluginval's restore watchdog" wording goes with them.
- Q3 confirmed by `git diff origin/main -- docs/phases/phase-13-1.md docs/phases/phase-13-5.md`: only R5, the two count
  words and 13-5 scope 3's ported sentence differ from main.
