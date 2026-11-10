# Seat 7 — D-H3 (a), (b), (c)

(Revised after `18-orchestrator-D-H3-code-tasks.md`; item (e) appended under "## D-H3 (e)" per the decider's addendum. This supersedes my first delivery in full.)

SEAT 7 POSITION

**Persona assumptions that fall (as in files 5 and phase-05b2 18/23/28).** The product is a subscription at $10–20 a month, saved work renders "exactly as saved" (PRD "Business model", FR-LIC-2/3, NFR-6); the team is Maisara plus a contracted engineer; there is no customer before the Phase 13 beta. My measures: contractor sessions, licence euros, what the CI record shows a stranger, what may be written from the latest report (AX45 (ii)), and support exposure after the beta. Corpus present (c1b171f); no acoustic value is at stake in these items.

---

## D-H3 (a) — the pooled bias check

**Reading (corrected by file 18).** My first position, like files 11 and 16, assumed SE ≈ 0.035 dB per case-band; the real mean SE at 500 Hz–2 kHz is 0.0077 dB and the mean signed deviation is **+0.0009 dB (+0.02 %)**, not 0.015 dB. The red is a weighting artefact: the mean of z weights by 1/SE, and three contributors with SE far below their reference's ℓ_ref carry it (`dead_booth` z +8.1 at C++ − ref +0.017 dB against ℓ_ref 0.17 %; `cr4` +0.010 dB; `cr3` +0.005 dB). Per case-band everything passes τ by ≥ 5×. Cues: "a check red by design is the opposite of a public testing record" (criterion 7, AI1/AI2); "a tolerance changed after the data" is the sentence a buyer's heuristic is built on (CLAUDE.md "never loosened to pass").

**Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) ℓ_ref in quadrature | can live with | 1 | 1 | Passes every band (0.31 vs 0.412; others ≤ 0.12 vs 0.626, file 18). A formula change in test code with a one-sentence, pre-data reason (ℓ_ref already in the per-case rule, AX42, and in AX46). Later 1 only if RQ-H3-1 confirms the E_n form and the §6 row cites that origin; 2 otherwise (a post-hoc formula on the public record). |
| (b) per class, z as written | cannot recommend | 2 | 1 | Still red: BRAS 0.56–0.58 vs 0.548 at bands 3–5; reference positions 1.00–1.20 vs 0.905 at bands 3–7. A grouping change *and* a red: the worst of both. |
| (c) rule as written, red every run | can live with (barely) | 2 | 2 | The D-H1 W-a pattern I rated 2/2 and the board replaced with a register (file 8 L42–52). A red CHECK in the Release hidden-tag job masks the other assertions in it; one founder carries a standing paragraph per PR (≈ 1 h × ≥ 3 PRs [Inferred]); and the line under the red reads "+0.0009 dB", which makes the red absurd to sustain and easy to quote without that line. |
| (d) (a)+(b) | cannot recommend | 2 | 1 | Still red in the BRAS class (0.59–0.60 vs 0.548): ℓ_ref barely moves the BRAS z. Same "worst of both". |
| (e) per reference room | **prefer** | 0 | 1 | Passes in **both** forms, with z as written (|mean| ≤ 0.13 vs 0.64–0.69) and with ℓ_ref. So it is a pooling change only, no formula change: the cleanest sentence for the public record ("one measured room counts once, whatever its number of pairs"), and the honest unit for a same-sign rung error. Later 1: every new reference room adds a cluster id to the golden (additive, cheap); M_cluster is small (19–22), so power is Seat 1's to rate. |
| (f) mine, the D-H1 register pattern | fallback only | 0 | 1 | Needed only if RQ-H3-1 rejects (a) *and* Seat 1 rejects (e) on power: the rule's text stands, the CHECK runs strictly where it passes and as a registered finding with the number, a growth bound, a named closer and an end date where it does not. |

**Public wording under each.** The per-case line holds under all: "C++ matches the reference within 0.25 dB per case and band on N certified case-bands (max 0.046 dB)". Under (a) or (e), green: "mean signed offset across the 53 certified case-bands at 500 Hz–2 kHz +0.0009 dB (+0.02 %), pooled per reference room / with the references' own certified uncertainty". That sentence is quotable *for* the product; it must appear in the report in dB and % beside the limit so the Phase 13 writer copies it and never writes "no bias" bare. Under (b)/(c)/(d): the bias clause is not claimable, and a reader of a public CI log [Hyp: public repo] can post "its own agreement test fails"; the +0.0009 dB never travels with it (AI1). Forbidden everywhere: "validated method", any near-wall or both-ends-flagged claim (AX39). The `dead_booth` contributor (C++ 2.3 ℓ_ref from a reference whose last halving moved 0.17 %) is a reference-resolution finding to record (Seats 2, 9), not a wording matter.

**Commits later.** (a)/(e): AX45's 72 case-bands, if ever pooled, inherit the form; undo = a test-file edit and a row re-amend. (c): every phase through 05i carries the red. (f): a closer phase in text.

**Evidence.** Figures: file 18 K-a3/K-a4 [Observed, Release re-run, same N]; file 9 [Observed]; CHECK form: `test_diffuse_agreement.cpp` L276–284 (from the code); D-H1 precedent: file 8 L42–52; E_n standard form → researcher RQ-H3-1 [Hyp until then]; public-repo exposure [Hyp]; contractor hours [Inferred]. Arithmetic redone: 3/√30 = 0.548, 3/√15 = 0.775, 3/√22 = 0.640, 3/√53 = 0.412.

**Conditions.** (a) later 1 only with RQ-H3-1 and the §6 origin sentence. (b)/(d) to 1: not reachable (they stay red on the data). (c) to 1/1: convert to (f). (e) stays 0/1 with the cluster rule written into the golden's CHANGELOG reason.

**Hand-offs.** E_n standard → researcher; power of per-room pooling → Seat 1; whether the rung residual is systematic → Seats 2, 9; `dead_booth`'s reference at 2.3 ℓ_ref → Seats 2, 9; implementability without golden regeneration → Seat 5.

**Premortem.** If (c) wins: the Release job is red in three bands from the push on, the standing paragraph goes stale by Phase 08, and the first outside reader quotes the failing CHECK without the "+0.0009 dB" beneath it; Maisara reads it in a review before I do.

---

## D-H3 (b) — U at two contract-limits fixtures

**Reading.** Two fixtures no producer builds raise U at default; file 18 K-b3 now **shows** (not asserts) that every moved placement of both raises U through the cap with both-near 0 (achieved SE 0.93–3.3 dB at `edge_values`, 1.6–4.1 dB at `open_field`); the pilot ships only at `edge_values`' default. Cues: "cost it against doing nothing" (C4); a settled rule reopened after data is a retroactive change in the record (V4).

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) reading + report line + AX41 list | can live with | 0 | 1 | One FOR MAISARA reading, one CHECK exemption by name in the reports test. Later 1: Phase 12's outdoor preset meets the same cap and the question returns unanswered. |
| (b) change the fixtures | cannot recommend | 2 | 1 | K-b3 shows no placement silences U, so a fixture change buys nothing and costs a golden round across contract validation, the AX37 (5.4) checks and `phase04_open_field_omni`. "We moved the fixture so the flag went quiet" is the sentence the buyer's heuristic is built on. My earlier condition for (b) is not met. |
| (c) reopen NW-4C | can live with (not veto) | 2 | 2 | A nine-seat loop before the push (phase-05b2's D-T1 loop ran files 21–39: ≥ 1 orchestrator session [Inferred]) to change a settled predicate for two fixtures outside any room class; Phase 11's note and Phase 12's check rewritten twice. |
| (d) (a) + forward rules | **prefer** | 1 | 0 | (ii) is one printf per fixture (cause; movable or not: K-b3 is exactly that table) and is the public testing record criterion 7 asks for; (i) is a display rule and Seats 1 and 6's (dropped if either rates ≥ 2). Phase 12 has its rule in text now. |

**Compatibility-note wording (U at outdoor scenes before Phase 12).** Nothing is public before the beta; what is owed now is the report line the Phase 13 note is copied from: "In open outdoor scenes (one ground surface, nothing else reflecting) the late energy is more than 60 dB below the direct sound; the tail-level 'approximate' indicator can appear there because there is almost nothing to estimate; the scene renders as designed." Never the both-near text ("move about 0.7 m away") on a field: the cause is the cap, and AX44 says the note names the scene. For extreme rooms one sentence: "very long, very narrow or near-rigid rooms can show the indicator at any placement." Trust deposits at zero cost. Never "validated".

**Commits later.** (a)/(d): Phase 12 reports outdoor presets with the cause; Phase 11 shows or suppresses the note per Seats 1/6. (b): a golden round now for nothing. (c): a predicate change before 05h's goldens and again in Phase 11.

**Evidence.** Flags and SEs at moved placements: file 18 K-b3 [Observed, `render_cli --diagnostics`]; file 9; the CHECK: `test_diffuse_reports.cpp` L253–257 (from the code); FR-3D-3/FR-3D-5; loop size [Inferred]; blast radius → Seat 5.

**Conditions.** (b): none reachable on K-b3. (c) to 2/1: Seat 6 states that "valid fixture" meant every file under `tests/scenes/valid/`.

**Hand-offs.** Scope of "valid fixture" → Seat 6; whether producers build these → Seat 8; fixture blast radius → Seat 5; (d)(i) display rule → Seats 1, 6; the Phase 13 copy → me, from the report.

**Premortem.** If (c) wins: a session goes to reopening AX44 for two fixtures nobody builds, the field preset in Phase 12 meets the same cap anyway, and the contracted engineer notices the note text being rewritten a second time in the Phase 11 review.

---

## D-H3 (c) — the denormal premise (narrow, cost only)

**Reading.** The premise has no instance the probe can see; the guard and bit-identity test exist. Cue: the founder's hour (R1); the push waiting on a search is the cost.

| option | label | now | later | reason |
|---|---|---|---|---|
| (a) read as satisfied | can live with | 0 | 1 | Free. Later 1: a reviewer reading "asserted to produce denormals" finds no assertion; a wording line fixes it. |
| (b) bounded search | can live with | 1 | 0 | A detector (Seat 5's) ≈ half a contractor session [Inferred] plus one manual three-OS run (macOS minutes the dear class [Hyp]); K-c4 says the probe's addition to the CI list is a one-line change. Unbounded it is 2/1. |
| (c) synthetic denormal in test code | can live with | 1 | 2 | Asserts the guard against an injected value; proves nothing about the product's path; a test a stranger reads as staged. |
| (d) (a) + standing direct probe | **prefer** | 1 | 1 | Same one-off cost as (b), the result stays on the record and re-runs only when `buildRoomIR`'s path changes; the clause rewritten to what is true. |

**Commits later.** (d): a hidden standing test on three OSes and a re-run rule; (b): one run; (a): a wording debt.

**Evidence.** Probe results: file 11 addendum [Observed, one box]; probe criterion: `test_diffuse_gate.cpp` L306–354 (from the code); K-c4 status: file 18; detector availability → Seat 5 / RQ-H3-2; costs [Inferred]/[Hyp].

**Conditions.** (c) to 1/1: the test's name says "injected". (b) to 0/0: one run, then (a) or (d) decided without another round.

**Hand-offs.** Detector and what a negative proves → Seat 5; where a denormal could arise → Seats 2, 3.

**Premortem.** If an unbounded (b) wins: the atomic push slips a session searching for a denormal the double sums make unreachable; the steward notices the open item at its next round.

---

## D-H3 (e) — `reset()` on the audio thread; freeze / offline threading unmeasured

**Reading.** The code's `reset()` / `setNonRealtime(true)` block in `quiesce()` and may build on the calling thread (from the code: `ScenePipeline.cpp` L102–107, L245–265, L313–327); VST3 permits that call on the processing thread and the pinned JUCE wrapper delivers it there (file 12 F1, F2, F6). Before 07c lands a transport reset in a 100 m / 96 kHz room can stall a host for 2.0–2.6 s plus the solve, if the host delivers it on the audio thread. Cues: "the hardest work is keeping it working in hosts" (R1); support is the product (R3); a stall thread on a forum is the one-shot heuristic's proof (AI1); "away from ruin before toward growth".

**(1) The six-host measurement: cost, phase, what one founder sustains.** The instrument: a validation-only logging build (thread id, `isNonRealtime()`, transport per `process()`, written to a lock-free ring and flushed off-thread, never allocating in `processBlock`) ≈ half a contractor session [Inferred]; Seat 5 designs it. The run: 6 hosts × 5 situations on macOS and Windows (Logic macOS only; Live, Cubase, Bitwig, REAPER, FL on both) ≈ 1–2 person-days at real machines [Inferred], a person's act (Maisara's or the contracted engineer's machines), not a contractor session. Licences [Hyp, list prices]: Live Standard ≈ €350 / Suite ≈ €600, Logic ≈ €230, Cubase Pro ≈ €580, Bitwig ≈ €400, REAPER ≈ €60, FL ≈ €100–500; Pro Tools is a subscription and not in the matrix (no AAX build). Done once inside trial windows (Live 90 d, Logic 90 d, Cubase 60 d, REAPER 60 d, Bitwig and FL demos with export limits to check) the licence cost is near €0 [Hyp]; done as a standing host matrix it is the licence set Phase 13 needs for beta support anyway, so the money is Phase 13's, not new. What one founder sustains: the one-off run, yes; re-running it on every host or OS update, no, which is why the remedy must be code (07c) and the measurement evidence for the notes, never a per-host code path (NFR-8). Phase: the instrument is built in 07c (its interim rules need the same build, as the decider says); the run is listed for Maisara as an action; the results land in Phase 13's host matrix and the compatibility notes. It must not block 07c's merge: 07c's conditions are code, the measurement is evidence.

**(2) Ranking and tension (now / later).**

| option | label | now | later | reason |
|---|---|---|---|---|
| (e-a) keep class (1); correct the premise; open check rewritten in two halves; gap in the notes | can live with | 0 | 1 | One FOR MAISARA reading and a note line; 05h ships; 07c is already next (D-H1 (v)) and "must be done before Phase 13", so no customer meets the stall. Later 1: the gap sits in the notes until 07c, and if 07c slips past the beta it becomes a support thread. |
| (e-b) `reset()` only cancels, never waits or builds, in 05h | can live with | 2 | 1 | Pulls 07c's `reset()` half into 05h's remaining session before the atomic push: two-order, TSan `[pipeline]` and the reset-covering gate tests to rewrite, ≈ half to one session [Inferred], against CLAUDE.md's two-session limit; a split into 05i is the likely outcome. Later 1: 07c then re-designs the interim level (its condition 5) over a reset path it inherited, so the work risks being done twice. |
| (e-c) `reset()` never builds, still cancels-and-waits | can live with | 1 | 1 | Smaller test change than (e-b), but its value rests on K-e6, unmeasured: if the 2–3 s synthesis has no cancel points the wait is the stall and (e-c) buys nothing (Seat 2's ground). |
| (e-d) (e-a) + quiesce record brought forward + thread-id debug assert + measurement as a 07c condition | **prefer, if Seat 5 says the assert fits** | 1 | 0 | The K-e6 record is already an orchestrator code task; the assert is test-build only (Seat 5 rates implementability); the measurement gets a named phase and the notes a named end date. The cost is a fraction of a session; the later debt is nil because the gap has an owner. |

**(3) Public wording until measured.** Compatibility notes are Phase 13 copy and come from the latest report (AX45 (ii) by analogy); AX39 forbids "validated" and NFR-8 forbids a per-host remedy. What the report carries now so the note can be copied: "Transport stop/start and the start of a bounce rebuild the room; in very large rooms this takes up to a few seconds, shown as 'settling'. Freeze and bounce run offline by default in Live, Logic, Bitwig, Studio One and FL Studio (their manuals, file 12 F12–F17); real-time bounce for external hardware behaves like playback. Cubase, REAPER and Pro Tools are unverified. Each host in the list is measured before release; the measured list is in the release notes." **Would I print "may stall the host for up to N s on transport reset in very large rooms"?** Not in launch copy with a planned fix: before 07c no customer reads it, after 07c it should be false, and a stall figure is the sentence a forum quotes (AI1). The rule: never print a stall figure that is not measured; never omit one that is. If 07c has not removed the `reset()` build by the beta, print it, with the measured number and the room size that triggers it, as a trust deposit rather than a surprise ticket; a subscription whose support inbox fills with "freezes my DAW on stop" is the R3 failure.

**Commits later.** (e-a)/(e-d): 07c's `reset()` half unchanged in scope; the measurement and the note line have an owner (07c instrument, Phase 13 matrix). (e-b)/(e-c): phase-05h §9 and phase-07c condition 2 rewritten by DECISION; the test list of the atomicity rule grows; undo = reverting a pipeline change plus its tests (half a session).

**Evidence.** Spec and wrapper facts: file 12 F1, F2, F6, F9 [read by the researcher, high]; code path (from the code, cited above); build and solve durations: §0 row 07, file 1 [Observed]; 07c ordering: D-H1 (v), phase-07c header ("must be done before Phase 13"); host manuals: file 12 F12–F17; licence prices and trial windows [Hyp]; contractor and person-day estimates [Inferred]. Corpus has nothing on host threading (file 12 §7).

**Conditions.** (e-b) to 1/1: 05h's status is set to split (05i) in the same decision so the two-session rule is not broken quietly, and 07c's condition 5 is read to take the 05h reset path as given. (e-c) to 0/1: K-e6 shows a cancel-observed wait ≤ 100 ms at the 100 m / 96 kHz builds on three OSes. (e-d) stays 1/0 only if Seat 5 confirms the assert never touches the allocation-free path.

**Hand-offs.** Assert implementability, measurement design, JUCE wrapper confirmation → Seat 5; cancel granularity (K-e6) → Seat 2 and the orchestrator; what the user hears and sees → Seats 1, 3, 6, 8; running the measurement on real machines with licences → Maisara (an action, not a decision); RQ-H3-3 → researcher.

**Premortem.** If (e-b) wins: 05h's second session runs out on the reset tests, the phase splits into 05i, the atomic push slips, and 07c re-designs the interim rule it just inherited; the steward notices the split. If (e-a) wins and 07c slips past the beta: a tester in Cubase with a 100 m room reports the DAW freezing on stop and the compatibility note never said so; the support inbox notices first.

---

Files read: `docs/review/phase-05h/16-decider-convene-D-H3.md` (whole, incl. "D-H3 (e)"), `18-orchestrator-D-H3-code-tasks.md`, `12-researcher-T5T4-61.md`, `11-orchestrator-D-H3-question.md` (with addendum), `9-orchestrator-agreement-results.md`, `13-orchestrator-reported-set.md`, `14-orchestrator-M2-near-corner.md`, `8-decider-decision-D-H1-D-H2.md` (W table, H1-F2), `5-seat7-D-H1-D-H2.md`; `docs/BUILD_PLAN.md` §2 AX37–AX46; `docs/phases/phase-05h.md` §4–§5, §8–§9; `docs/phases/phase-07.md` L111–160; `docs/phases/phase-07c.md` header and §5 headings; `docs/review/phase-05b2/18-seat7-T1-T2.md`, `23-seat7-round2-T1-T2.md`, `28-seat7-D-T6.md` (wording clauses); `docs/PRD.md` (FR-3D-3, FR-3D-5, FR-LIC-2/3, FR-SIM-6, NFR-2/3, business model, delivery); from the code: `tests/unit/test_diffuse_agreement.cpp` L196–284, `tests/unit/test_diffuse_reports.cpp` (CHECK lines), `tests/unit/test_diffuse_gate.cpp` L300–389, `src/plugin/core/ScenePipeline.cpp` L102–133, L245–327. Nothing written; the orchestrator saves this as `/home/user/makroof/docs/review/phase-05h/17-seat7-D-H3.md`.
