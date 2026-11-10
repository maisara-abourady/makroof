# Seat 7 — D-H3 (a), (b), (c)

SEAT 7 POSITION

**Persona assumptions that fall (as in files 5 and phase-05b2 18/23/28).** The product is a subscription at $10–20 a month, saved work renders "exactly as saved" (PRD "Business model", FR-LIC-2/3, NFR-6); the team is Maisara plus a contracted engineer; there is no customer before the Phase 13 beta. My measures here are contractor sessions, what the CI record shows a stranger, and what may be written from the latest report (AX45 (ii)). Corpus present (c1b171f); no acoustic value is at stake in these three items.

---

## D-H3 (a) — the pooled bias check

**Reading.** A pre-registered statistic whose pooled SE (0.035/√53 = 0.0048 dB, redone) is below the references' own certified residual (0.36 % = 0.0156 dB) is red while every per-case check passes by 5× and AX46 passes. Cues: "a check red by design is the opposite of a public testing record" (criterion 7, AI1/AI2); "a tolerance changed after the data" is the sentence a buyer's heuristic is built on (CLAUDE.md "never loosened to pass").

**Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) ℓ_ref in quadrature | can live with | 2 | 1→2 | Now 2 because on the decider's arithmetic (0.464 × 0.985 = 0.457 > 0.412, redone) it is a formula change *and* still red at 2 kHz: the worst of both on the record. Later 1 if RQ-H3-1 confirms E_n as the standard form and the §6 row cites AX42/AX46 as ℓ_ref's pre-data origin; 2 otherwise (a post-hoc formula on the public record). |
| (b) per class | can live with | 1 | 1 | A grouping change that mirrors AX46's own structure (Seat 2's pre-data condition), so it has a one-sentence reason; may still be red in the BRAS class (K-a3 unknown). Later: the Phase 04 class at M = 8 has limit 1.061, so the public line must say "per reference class", never "across all rooms". |
| (c) red by design, finding every run | can live with (barely) | 2 | 2 | The D-H1 W-a pattern I rated 2/2 and the board replaced with a register (file 8 L42–52). A red CHECK in the Release hidden-tag job masks the other macOS/Windows assertions in it; one founder carries a standing paragraph per PR (≈ 1 h × ≥ 3 PRs, [Inferred]); a stranger quotes "the agreement test fails" without the 0.015 dB. |
| (d) (a)+(b) | prefer, if K-a3 shows it passes | 1 | 1 | Two changes, one amendment, one row; commits small-room and 100 m classes to the same rule; undo = a test-file edit and a row re-amend (cheap). |
| (e) per reference room | prefer, equal with (d) | 1 | 1 | The honest unit for a same-sign rung error (one room = one cluster); reads best in public ("across N reference rooms beyond their own uncertainty"). Later: every new reference room adds a cluster id to the golden (small, additive). Power is Seat 1's. |
| **(f) mine: the D-H1 register pattern** | prefer, if (d)/(e) still fail on K-a3 | 0 | 1 | The rule's text stands; the CHECK runs strictly in the five bands that pass and as a **registered finding** in the three that do not: the mean deviation printed in dB and %, a growth bound (mean z not above the recorded value + 0.1 [Hyp]), a named closer (the next certified rung, or the RQ-H3-1 answer), an end date. Nothing is loosened; nothing is red everyone ignores. |

**Public wording under each.** Under every option the per-case line holds and is the one that matters: "C++ matches the reference within 0.25 dB per case and band on N certified case-bands (max 0.046 dB)". Under (a)/(d)/(e), if green: "no shared offset beyond the references' own certified resolution (< 1 %)". Under (b): the same, "per reference class" only. Under (c) or any red: the bias clause is not claimable; the report must print the mean offset (+0.36 %, 0.015 dB, 1/67 of the 1 dB jnd, Vorländer Table 6.1, corpus) beside the limit so the Phase 13 writer cannot write "no bias" and a reader of the log sees the magnitude on the same line. Forbidden everywhere: "validated method", any near-wall or both-ends-flagged claim (AX39). **Can a red pooled check be quoted against the product?** Yes, if the repo or CI log is public [Hyp]: "its own agreement test fails" is the whole post; the 0.015 dB never travels with it (AI1). Under (f) the same reader sees "registered finding: +0.36 % at the references' resolution, closer named", which is the record I want.

**Commits later.** (a)/(d)/(e): AX45's 72 case-bands, if ever pooled, inherit the form. (c): every phase through 05i carries the red. (f): a closer phase must exist in text.

**Evidence.** Figures: file 9 [Observed, CI log]; CHECK form: `test_diffuse_agreement.cpp` L276–284 (from the code); D-H1 precedent: file 8 L42–52; arithmetic above redone; E_n standard form → researcher RQ-H3-1 [Hyp until then]; public-repo exposure [Hyp]; contractor hours [Inferred].

**Conditions.** (a) to 1/1: K-a3 shows it green in all three bands and RQ-H3-1 confirms the form; else compose (f). (c) to 1/1: convert to (f). (d)/(e) stay 1/1 only with the §6 row stating ℓ_ref's pre-data origin.

**Hand-offs.** K-a3 table → orchestrator; E_n standard → researcher; power loss of per-class/per-room → Seat 1; systematic vs random rung error → Seats 2, 9; implementability without golden regeneration → Seat 5.

**Premortem.** If (c) wins: the Release job is red in three bands from the push on, the standing paragraph goes stale by Phase 08, and the first outside reader (the contracted engineer at review, or a forum poster at the beta) quotes the failing CHECK without the number; Maisara reads it in a review before I do.

---

## D-H3 (b) — U at two contract-limits fixtures

**Reading.** Two fixtures no producer builds (1.5 × 100 × 4 m; a field with one ground surface) raise U at default; the reversal is met on its words. Cues: "cost it against doing nothing" (C4); a settled rule reopened after data is a retroactive change in the record (V4).

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) reading + report line + AX41 list | can live with | 0 | 1 | One FOR MAISARA reading, one CHECK exemption by name in the reports test. Later 1: Phase 12's outdoor preset meets the same cap and the question returns unanswered. |
| (b) change the fixtures | cannot recommend | 2 | 1 | Touches contract validation (`edge_values`) and the AX37 (5.4) checks and `phase04_open_field_omni` golden (`open_field`): a golden round for a change that file 9 says silences nothing (K-b3 pending). "We moved the fixture so the flag went quiet" is the sentence the buyer's heuristic is built on. |
| (c) reopen NW-4C | can live with (not veto) | 2 | 2 | A nine-seat loop before the push (phase-05b2's D-T1 loop ran files 21–39: ≥ 1 orchestrator session [Inferred]), to change a settled predicate for two fixtures outside any room class; Phase 11's note text and Phase 12's check rewritten twice. |
| (d) (a) + forward rules | **prefer** | 1 | 0 | (ii) is one printf per fixture (cause; movable or not) and is exactly the public testing record criterion 7 asks for; (i) is a display rule and is Seats 1 and 6's (I drop it if either rates ≥ 2). Phase 12 has its rule in text now; nothing is decided at copy-writing time. |

**Compatibility-note wording (U at outdoor scenes before Phase 12).** Nothing is public before the beta; what is owed now is the report line the Phase 13 note is copied from: "In open outdoor scenes (one ground surface, nothing else reflecting) the late energy is more than 60 dB below the direct sound; the tail-level 'approximate' indicator can appear there because there is almost nothing to estimate; the scene renders as designed." Never the both-near text ("move about 0.7 m away") on a field: the cause is the cap, and AX44 says the note names the scene as the cause. For extreme rooms one honest sentence: "very long, very narrow or near-rigid rooms can show the indicator at any placement." Both are trust deposits at zero cost. Never "validated".

**Commits later.** (a)/(d): Phase 12 reports outdoor presets with the cause; Phase 11 shows or suppresses the note per Seats 1/6. (b): a golden round now and the fixtures' meaning changed. (c): a predicate change before 05h's goldens and after them in Phase 11.

**Evidence.** Flags and SEs: file 9 [Observed]; the CHECK: `test_diffuse_reports.cpp` L253–257 (from the code); fixtures (from the code); FR-3D-3/FR-3D-5; loop size [Inferred from phase-05b2]; blast radius → Seat 5.

**Conditions.** (b) to 1/1: K-b3 shows a placement that silences U at a fixture that no other test reads. (c) to 2/1: Seat 6 states in its own words that "valid fixture" meant every file under `tests/scenes/valid/`.

**Hand-offs.** Scope of "valid fixture" → Seat 6; whether producers build these → Seat 8; fixture blast radius → Seat 5; (d)(i) display rule → Seats 1, 6; the Phase 13 copy → me, from the report.

**Premortem.** If (c) wins: a session goes to reopening AX44 for two fixtures nobody builds, the field preset in Phase 12 meets the same cap anyway, and the contracted engineer notices the note text being rewritten a second time in the Phase 11 review.

---

## D-H3 (c) — the denormal premise (narrow, cost only)

**Reading.** The premise has no instance the probe can see; the guard and bit-identity test exist. Cue: the founder's hour (R1); the push waiting on a search is the cost.

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) read as satisfied | can live with | 0 | 1 | Free. Later 1: a reviewer reading "asserted to produce denormals" finds no assertion; a wording line fixes it. |
| (b) bounded search | can live with | 1 | 0 | A detector (Seat 5's: MXCSR / FPSR / `fpclassify`) ≈ half a contractor session [Inferred] plus one manual three-OS run (macOS minutes the dear class [Hyp]); bounded to one run before the push it costs a fraction of a session. Unbounded it is 2/1. |
| (c) synthetic denormal in test code | can live with | 1 | 2 | Asserts the guard against an injected value; proves nothing about the product's path; a test a stranger reads as staged. |
| (d) (a) + standing direct probe | **prefer** | 1 | 1 | Same one-off cost as (b), but the result stays on the record and re-runs only when `buildRoomIR`'s path changes; the clause rewritten to what is true. |

**Commits later.** (d): a hidden standing test on three OSes and a re-run rule; (b): nothing beyond one run; (a): a wording debt.

**Evidence.** Probe results: file 11 addendum [Observed, one box]; probe criterion: `test_diffuse_gate.cpp` L306–354 (from the code); detector availability → Seat 5 / RQ-H3-2; costs [Inferred]/[Hyp].

**Conditions.** (c) to 1/1: the test's name says "injected"; (b) to 0/0: one run, pass or fail, then (a) or (d) decided without another round.

**Hand-offs.** Detector implementability and what a negative proves → Seat 5; where a denormal could arise → Seats 2, 3.

**Premortem.** If an unbounded (b) wins: the atomic push slips a session searching for a denormal the double sums make unreachable; the steward notices the open item at its next round.

---

Files read: `docs/review/phase-05h/16-decider-convene-D-H3.md`, `11-orchestrator-D-H3-question.md` (with addendum), `9-orchestrator-agreement-results.md`, `13-orchestrator-reported-set.md`, `14-orchestrator-M2-near-corner.md`, `8-decider-decision-D-H1-D-H2.md` (W table), `5-seat7-D-H1-D-H2.md`; `docs/BUILD_PLAN.md` §2 AX37, AX39, AX41–AX46; `docs/phases/phase-05h.md` §4–§5, §8–§9; `docs/review/phase-05b2/18-seat7-T1-T2.md`, `23-seat7-round2-T1-T2.md`, `28-seat7-D-T6.md` (wording clauses); `docs/PRD.md` (FR-3D-3, FR-3D-5, FR-LIC-2/3, business model); from the code: `tests/unit/test_diffuse_agreement.cpp` L196–284, `tests/unit/test_diffuse_reports.cpp` (CHECK lines), `tests/unit/test_diffuse_gate.cpp` L300–389. Nothing written; the orchestrator saves this as `/home/user/makroof/docs/review/phase-05h/17-seat7-D-H3.md`.
