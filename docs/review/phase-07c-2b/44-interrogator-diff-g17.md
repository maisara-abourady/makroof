# Interrogator: /fix-plan step 5 for commits db1770e, c504a71, 541fc6c and the new §6 row (L539)

**Verdict: faithful.** Nothing is WRONG. Four minor fixes remain:
- the assertion-8 "(= measured)" equality, which my file 42 also stated wrongly;
- §8's L4 sitting minutes, still the pre-A-ii figures;
- the stale "Open before the seal" B-null bullet in §3 item 2;
- the column count of the last two §6 rows.

**Corpus revision:** c1b171fe649f07cbeb952ef1f75d89bfaa414d0d.

**Checked:** I have no shell, so I checked the files' current text, not the diffs:
- the run sheet §1 (L155–172), §3 items 2 and 5 (L201–256) and §8 (L436–499);
- `docs/phases/phase-07d.md` L136–140;
- BUILD_PLAN §6, L538–539.

The decisions and records I checked them against are files 34, 38, 39, 41, 42 and 43, and builder file 26 (row 8).

## db1770e (run sheet §8, phase-07d)
**Faithful:**
- **Anchor paragraph (L473–482):** decider file 41's exact L4-A text, verbatim. It is followed by Seat 3's checks on the anchor IR (M1 within 0.05 dB, s_w, peak).
- **Criteria (L483):** "family α 0.038 ≈ 2517/65536". My nit is closed.
- **Assertion 2 (L440–444):** per-sample null, attributed as "Seat 3's per-sample criterion at Phase 06's −120 dB level". My file 42 correction is applied.
- **Assertion 4 (L446–448):** the "weak on this scene" print, the red test, and the 0.05 dB tolerance unchanged. Faithful.
- **Assertion 7 (L451–453):** read on the model, with the realised drop printed. Faithful.
- **Sittings (L493–499):** the third dated sitting, faithful to file 38 (5).
- **phase-07d L136–140:** file 41's debt row (16-seed ensemble, repaid at a mean ≥ 18.7 dB within its spread). Faithful.

**Assertion 8 (L454–457): IMPRECISE. This is my error carried over from file 42.**
- L456 writes "realisation 10^(−(18.47 + 0.60)/10) = 0.0124 (= measured)".
- The 0.0124 in builder file 26 (row 8) is the per-emitter maximum at **125 Hz** (emitter 0). The heard-IR maximum is **0.01169**, also at 125 Hz, and builder file 43 reports the same heard value.
- The 18.47 dB realised drop is the **63 Hz** heard value.
- So "= measured" sets equal two quantities from different bands and different IRs. The match is a coincidence.
- **Correction:** drop "(= measured)" and add "measured maximum 0.0124 (emitter 0, 125 Hz), heard 0.01169". All of these values are ≤ 0.0134, so the assertion's conclusion is unchanged.

**Sittings: stale figures (IMPRECISE).**
- L496–497 still give "74 + 74 = 148 min" and "113.6 min slow". Those are builder file 26's figures, from before A-ii.
- Builder file 43 measured them on the final familiarisation set:
  - E's sitting 2: 74.5 min;
  - L4 primary + rerun: 72.9 min typical, 112.0 min slow;
  - total: 74.5 + 72.9 = 147.4 min.
- The conclusion is unchanged: E's second sitting plus L4 is still over 2 h, and L4 alone is still within 2 h at every pace.
- **Correction:** update to file 43's figures.

## c504a71 (run sheet §1 search result, §3 items 2 and 5)
**Faithful to builder file 39:**
- MA02_03 + MA02_04 was the 6th pair tried. Its first candidate boundary is 2.901 s, leaving 2.816 s of programme before it, which is at least T = 2.600 s.
- Q5: window [0.057, 0.403]·T_heard, 84 of 90 boundaries passing; first draw replaced with p 0.067, and 2 of 50 replaced in practice; drawn-onset margins min 20.4 dB, median 29.7 dB.
- The fallback branch is "not used on E".
- The SHA-256s for both files match.
- The list of pairs tried matches: the five earlier pairs failed rule (c).
- §3 item 5's K6 figures match (2.484 h; two sittings of about 1.24 h).

**Also correct:** the fallback pair's window line (L167–171) now gives the kit's [0.059, 0.380] and explains K7's 0.013, which closes my earlier ledger row c21-8.

**Stale bullet (minor INCONSISTENT).** §3 item 2's "Open before the seal … the unstepped render B nulled … on every speech stimulus (builder file 4 fact 5 nulled B on noise only)" (L217–219) is no longer open.
- Builder file 12 measured B at −130.3 dB on speech with MA01_01/02.
- Builder file 39 measured B at −130.6 dB on MA02_03/04, all 50 stimuli, as part of the full build.
- c504a71 edited §3 item 2, so this bullet should have been updated in the same commit.
- **Correction:** mark it closed for E's pair (builder file 39, B −130.6 dB, E −130.4 dB), keeping it open only for a fallback scene.

## 541fc6c (note after D1's "±3 dB")
- L484: "its '±3 dB' predates decider file 41, under which the anchor is +3 dB with roles swapped 3/3 (A-ii)".
- This is correct and keeps file 17's quotation verbatim. Faithful.

## §6 row L539 (L4 anchor change)
- **Content: faithful** to files 38 and 41 and their corrections. It covers A-ii and the reason for it (0.828 → −0.82 dB), 7/64, "never cited about M1", the readings of assertions 7, 4 and 2, the third sitting, and the sources.
- **Format: INCONSISTENT.**
  - §6 is a three-column table (`| Date | Change | By |`, L417).
  - L539 has four cells: date, change, "Run sheet §8; kit (3e8f643)", sources. L538 has the same extra cell.
  - The extra cell breaks the table's columns.
  - **Correction:** merge the third and fourth cells into "By".
- **L538 is also out of date.** It still says "kit (pending)", but builder file 39 landed the kit in commit 03502f4.

## Ledger
| id | kind | item | verdict | evidence | severity | status |
|---|---|---|---|---|---|---|
| G17-1 | DECISION | §8 anchor paragraph (L473–482) | verbatim | file 41 L4-A | none | — |
| G17-2 | NUMBER | α 0.038 ≈ 2517/65536 | CORRECT | binomial | none | closed |
| G17-3 | DECISION | assertions 2, 4, 7 readings | faithful | files 41, 42 | none | — |
| G17-4 | NUMBER | assertion 8 "realisation 0.0124 (= measured)" | IMPRECISE: the measured 0.0124 is emitter 0 at 125 Hz (heard 0.01169); 18.47 dB is 63 Hz; my file 42 said the same | builder files 26 (row 8), 43 | minor | fix |
| G17-5 | NUMBER | §8 sittings 74 + 74 = 148 min; 113.6 min slow | IMPRECISE (stale; file 43 gives 74.5 + 72.9 = 147.4 and 112.0 min); conclusion unchanged | builder file 43 | minor | fix |
| G17-6 | DECISION | phase-07d assertion-7 debt row | faithful | file 41 | none | — |
| G17-7 | FACT | search result MA02_03 + MA02_04; pairs tried; Q5 figures; SHA-256s; K6 2.484 h | CORRECT | builder file 39 | none | — |
| G17-8 | FACT | fallback window [0.059, 0.380] with the K7 note | CORRECT | builder files 4, 12 | none | closed (c21-8) |
| G17-9 | FACT | §3 item 2 "Open before the seal: B nulled on speech" | INCONSISTENT (stale: B −130.6 dB on speech, builder file 39) | builder files 12, 39 | minor | fix |
| G17-10 | FACT | note on D1's "±3 dB" | faithful | files 17, 41 | none | — |
| G17-11 | DECISION | §6 L539 content | faithful | files 38, 41, 42 | none | — |
| G17-12 | SOFTWARE | §6 L538–L539 four cells in a three-column table; L538 "kit (pending)" | INCONSISTENT format; stale | BUILD_PLAN L417 | minor | fix |
