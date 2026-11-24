# Interrogator on commit c21018e (applies decider files 25 (i)/(ii), 30 and 34, with interrogator file 36's corrections)

**Verdict: faithful.** Nothing in the commit is WRONG. There is one IMPRECISE citation. Two run-sheet statements describe kit behaviour that is decided but not yet built. And a §6 row should be added, because the existing §6 entry still records the superseded pair.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Checked (current working tree; I could not view the diff itself):**
- the run sheet §1, L52–174, and §3, L193–231;
- `tools/ci/abx_kit.py`: `E_LABEL` and `E_LABEL_DETAIL` (L183–202), `HEARD_T30_LABEL` (L114), the `--scene-name` argument (L2117);
- phase-07c-2b scope 2, L116–122;
- seat file 35.

## Faithful
- **Item 7 paragraph and the "Speech pair" text (L134–154):**
  - They are file 34's exact text.
  - File 36's corrections are applied:
    - the pair must pass "every pre-seal assertion of §1 and §3 item 3", and the list now includes item 10's peak ≤ −1 dBFS, item 6's mid-fade companions and W-a windows, the item-7 assertion on every drawn onset, and Q5's window and replacement rate recorded;
    - "The search or re-measure is repeated on a fallback scene (D or B)".
  - The fallback branch matches what I checked in files 31 and 36: floor 2.685 s, first candidate boundary 2.688 s, window ≈ [0.134, 0.380]·T_heard, ≈ 60 passing boundaries, the record wording, "never adjusted after familiarisation".
  - The no-remedy sentence cites file 13 item 4.
  - "n = 2, union ≤ 0.098, AX47's α sentence unchanged" (L159–160) is correct.
- **Provenance line (L131–132):** "Seat 7 file 35 rated option (3) 0/0". That matches file 35 ("prefer, now 0 / later 0"). Seat 7's only condition is to choose the pair and redo K6 before the seal, and L158 has "K6 is redone on whichever pair is chosen".
- **"Which T30" per scene class (L56–59):** S-A keeps Seat 9's "AX21 gap" text; s < 1 scenes use "spanning the early part". This matches ruling (i).
- **E's label block (L97–114):** verbatim against `E_LABEL` and `E_LABEL_DETAIL`. All eleven detail lines match in text and order, including the Class line and "Stimulus scene, not a room prediction."
- **Reported-speech sentence (L116–117):** it sits outside the quoted label and has no quote marks. It is file 25 ruling (ii)'s sentence word for word.
- **§3 item 2 (L193–201):** "M3-T … is amended by decider file 34". The files are left blank for the search result. The selection grounds match Seat 1's condition: measured assertions only, before any blind result, never by listening.
- **`--scene-name` (L94–95, L210–211):** consistent with builder file 12 and the kit's argument.
- **phase-07c-2b scope 2 (L119–122):** "M3-T is amended by phase-07c-2b decider file 34 … MA01_01 + MA01_02 only in the fallback branch with the onset restriction". Faithful.

## Findings
- **IMPRECISE: wrong window cited for the fallback pair (L161–163).**
  - The sheet says the builder measured MA01_01 + MA01_02's unrestricted Q5 window as "[0.013, 0.380]·T30 … (builder file 4, decider file 8 K19)".
  - That is K7's figure. K7 put the first boundary at end of speech + max d.
  - The kit, which governs, puts the first boundary at the heard end of the sentence-1 file, TSP's trailing silence included. Builder file 12 measured the kit's unrestricted window as **[0.059, 0.380]**.
  - Correct the line to the kit's value (file 12), or label the 0.013 figure as K7's definition.
- **Kit behaviour described but not yet built:**
  - `HEARD_T30_LABEL` is still a single string (L114).
  - `--search-pairs` does not exist yet.
  - The run sheet presents both the per-class label and `--search-pairs` (L156, L212) as available. Both are ⚙ kit changes from decisions that survived (files 25 and 34).
  - This is not a plan defect, but the builder must land both before the run sheet is used. `test_preregistered_numbers` should pin the two label texts and the chosen pair.

## Does it need a §6 row? Yes
- The §6 row of 2026-11-24 (L534) records "speech pair MA01_01 + MA01_02, M3-T" as the fixed speech material. After this commit that statement is superseded, and §6 would contradict the run sheet and phase-07c-2b.
- The commit also changes pre-registered design elements:
  - the speech material: M3-T amended to a pre-registered pair search;
  - an onset-floor rule, pinned in the fallback branch;
  - a new pre-registered criterion of at least 34 passing boundaries;
  - the heard-T30 label wording per scene class.
- Every earlier change of the same kind got a row: M3-G (L536), and the L4 rules (L537).
- n = 2 being unchanged does not exempt it. The row records the pre-registration change, not the α.
- Suggested content, by reference only: "Phase 07c-2b loop, I7 and rulings (i)/(ii): M3-T amended (pair search before E's seal; MA01_01 + MA01_02 only in the fallback branch with the item-7 onset restriction); heard-T30 label per scene class; E's label authoritative; n = 2 unchanged; decider files 25, 30, 34; interrogator files 28, 31, 36; Seats 1, 7 files 27, 29, 32, 33, 35; decided for Maisara, amends nothing."

## Ledger
| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| c21-1 | DECISION | item-7 paragraph, pair search, criteria, scene-in-use clause | faithful | file 34; file 36 corrections; run sheet L134–154 | none | — |
| c21-2 | DECISION | fallback branch and no-remedy sentence; n = 2 | faithful | files 30, 31, 34, 36; file 13 item 4 | none | — |
| c21-3 | FACT | Seat 7 rated (3) 0/0 | CORRECT | file 35 | none | — |
| c21-4 | DECISION | heard-T30 label per scene class | faithful | file 25 (i); file 28 | none | — |
| c21-5 | FACT | E label block against `E_LABEL` / `E_LABEL_DETAIL` | verbatim | abx_kit L183–202; run sheet L97–114 | none | — |
| c21-6 | FACT | reported-speech sentence outside the label | faithful | file 25 (ii); BUILD_PLAN L144 | none | — |
| c21-7 | DECISION | §3 item 2 M3-T amended; phase-07c-2b L119–122 | faithful | file 34 | none | — |
| c21-8 | NUMBER | fallback pair's unrestricted window "[0.013, 0.380]" | IMPRECISE (that is K7's definition; the kit's value is [0.059, 0.380], builder file 12) | builder files 4, 12 | minor | open |
| c21-9 | SOFTWARE | per-class `HEARD_T30_LABEL`; `--search-pairs` | described but not yet built (⚙ from files 25, 34) | abx_kit L114; no `--search-pairs` | — | builder |
| c21-10 | DECISION | §6 row | needed: L534's "speech pair MA01_01 + MA01_02, M3-T" is superseded; pre-registered elements changed; precedent L536, L537 | BUILD_PLAN §6; CLAUDE.md | minor | open |
