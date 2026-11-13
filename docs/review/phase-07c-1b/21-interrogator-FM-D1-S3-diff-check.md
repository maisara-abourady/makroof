# 21 — Interrogator, `/fix-plan` step 5 on the FM-D1-S3 edits (commit 6ba16a5)

2026-11-13, corpus c1b171f. Saved by the orchestrator (summary; the interrogator read every passage itself, no shell).

**Verdict: step 5 complete.** Every file 20 correction in place exactly (FM-04, -06, -07, -08, -10, -11, -14, -16, -17, -19 and the
orchestrator's application: FM-11 clause dropped, Q1 specular print, FM-17 wording, FM-14 comma); nothing WRONG or INCONSISTENT;
nothing beyond files 19 and 20 except accurate bookkeeping and provenance. Numbers recomputed: −18.27 / −24.55 / −19.27 dB; N1 +2.54 /
+3.01 / +3.54 dB; |γ| ≤ 0.1218 (B = 1 dB), ≤ 0.0592 (0.5 dB); 4 × 2 × 2 × 2 = 32 builds, 28 new. Corpus: Vorländer §4.3 Eq. (4.15)
(cos cross term averages out, squares add). Plan text: AX18 "Same-scene steps" requires "the same `tailSeed`, the same emitter streams
and the same fs"; AX47 Scope "Same-scene steps are equal-gain (AX18)" — FM-08's wording cites real text.

| id | passage | verdict |
|---|---|---|
| P07C1B-FMDC-01 | phase-07c-2 scope 9 bullet | CORRECT |
| P07C1B-FMDC-02 | phase-07c-2 AC | CORRECT |
| P07C1B-FMDC-03 | phase-08-3 AC | CORRECT |
| P07C1B-FMDC-04 | 08-3 / 09 "specular energy share of E(final)" (the criteria name the reference "exact") | IMPRECISE (minor) — **applied: "of E(exact)"** |
| P07C1B-FMDC-05 | phase-09 AC | CORRECT |
| P07C1B-FMDC-06 | AX47 (b) text addition | CORRECT |
| P07C1B-FMDC-07 | AX47 evidence append | CORRECT |
| P07C1B-FMDC-08 | §6 last row | CORRECT |
| P07C1B-FMDC-09 | "D1 O8 stands (max 1, sum 12)" (O8 alone sum 11, file 40 row 82; 12 is O8 with the (i) lines) | IMPRECISE (minor) — **applied: "with the (i) lines max 1, sum 12; O8 alone sum 11"** in §6 and the ledger |
| P07C1B-FMDC-10 | §0 row 07c-1b note | CORRECT |
| P07C1B-FMDC-11 | phase-07c-1b scope 5 / AC 5 notes | CORRECT (AC box unticked before phase close; Raise item 1 kept as history) |
| P07C1B-FMDC-12 | ledger row FM-D1-S3 | CORRECT |
| P07C1B-FMDC-13 | ledger rows P07C1-G3-80 … 98 (appended, history kept) | CORRECT |
| P07C1B-FMDC-14 | ledger round files and P07C1B-FM rows | CORRECT |
| P07C1B-FMDC-15 | ledger "plan diff check complete (file 14)" predates this diff; this check unlisted | IMPRECISE (bookkeeping) — **applied: file 21 and rows P07C1B-FMDC-01 … 17 listed** |
| P07C1B-FMDC-16 | numbers | CORRECT |
| P07C1B-FMDC-17 | clause (2) equal-power handover (1 + ρ lift 0 to +3.01 dB with a shared early part, recorded not bounded) | CORRECT (consequence stated) |
