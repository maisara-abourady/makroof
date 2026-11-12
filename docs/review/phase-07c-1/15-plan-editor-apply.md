# 15 — Plan-editor, /fix-plan step 4 (phase 07c-1)

Saved verbatim by the orchestrator from the agent's report, 2026-11-12. Sources: files 9, 12, 13, 14.

## Plan-editor report: /fix-plan step 4 for phase 07c-1 (2026-11-12)

Nothing is committed. I did not touch `docs/PRD.md`, `src/`, `tests/`, `tools/` or goldens.

**One brief item is not done: the `docs/review/ledger.md` append.** My operating rules say never to edit `docs/review/ledger.md`, and a brief can't override that. The draft rows are at the end of this report so you (or whoever is allowed to write the ledger) can append them.

### Applied

All the decided texts are from file 12 §7–§9, using file 9 §7's AX48 text as the base, with file 13's corrections 1–13 applied and D3*‴ kept as written (file 14).

- **`docs/BUILD_PLAN.md` §0:** new row 07d (size S–M, `not started`, depends on 07c-1 `done`, premise P1). It sits after 07c-2, so 07d exists before the register cites it (correction 13).
- **`docs/BUILD_PLAN.md` §2, AX18:** the FM-1 same-scene equal-gain block is inserted before "Amended by…", with "f_w ≥ … ≥ 0.986" (correction 9) and the AMENDS line. "07c-1" is added to Breaks.
- **`docs/BUILD_PLAN.md` §2, AX38:**
  - (i): a note that the AX48 stage-1 solve is served in class (1), ahead of background solves.
  - 4c remedy: "≈ 0.15 s … 10–20× headroom" is replaced by the new condition-9 gate text, and phase-07d is recorded as created.
  - An FM-2′ amendment note with correction 5's options wording and correction 4's "isolated restore", plus the AMENDS line.
  - The macOS register entry now closes at 07d; the Windows remedy names 07d.
- **`docs/BUILD_PLAN.md` §2, AQ10:** a 2026-11-12 amendment covering the FM-2′ and FM-3′ exceptions and the gate content, with both AMENDS lines.
- **`docs/BUILD_PLAN.md` §2, AX47 (new):**
  - (b) uses correction 1's signs: step −10·log10(1+(1−f_b)·δ); ≤ +0.06 dB; ≥ −0.5 dB unless δ ≥ 9; ≥ −1 dB unless δ ≥ 19.
  - Scope adds "cross-build keyed steps are recorded" (correction 8).
  - Rationale reads NFR-1 through Q9 (unresolved), AQ9 and phase-07c-1 L40 (correction 6).
- **`docs/BUILD_PLAN.md` §2, AX48 (new):** file 9's text with file 12's changes 1–5: five-part key including Π, the keyed-load clause, gate priority, the build-id question and the Π-mismatch test.
- **`docs/BUILD_PLAN.md` §2, AX49 (new):**
  - Row text as in file 12, except D1 now reads "scenes whose matched tail energy is zero" (correction 2).
  - Rationale uses D9-L4 "at the gated geometry (t_dir 0.118 s)" (correction 3), "no isolated restore" (correction 4), and "Seat 5's cell at ≈ 147 MB unrated" for D4 (correction 12).
- **`docs/BUILD_PLAN.md` §6:** six rows dated 2026-11-12 (AX18, AX38, AQ10, AX47, AX48, AX49), each citing `docs/review/phase-07c-1/` and corpus c1b171f.
- **`docs/phases/phase-07c-1.md`:**
  - Read-first list now includes AX47–AX49.
  - L56 lead sentence has the two exceptions.
  - Condition 7: both places that said "without the solve and the synthesis" are replaced.
  - Condition 9: the new gate text and the 07d note.
  - New record (h), placed under condition 9.
  - A1: AX rows recorded.
  - A2: rewritten as file 12 directs.
  - A4: the AX47 (a)/(b) tests, the AX49 acceptance and BRAS CR3.
  - A7: state v2, five-part key.
  - A8: the other-outputMode test, tail at the first IrSet, Π mismatch is keyless.
  - New listening item L4.
  - F3/F5 cite AX47–AX49.
- **`docs/phases/phase-07c-2.md`:** read-first list updated. New scope 9:
  - the ABX runs come first;
  - the class (c) decision is bound by AX47, and admission waits for the AX47 ABX (correction 7);
  - the load fallback;
  - the W_max raise makes v2 states keyless (E_prec);
  - Seat 2's prefix check.

  Also a listening item for the two ABX runs.
- **`docs/phases/phase-07d.md` (new):** size S–M, laid out like 07c-2. It has the scope, the five candidates, the inputs (record (h) T60 sweep, S5/S7 ratings), the release premise P1 and the register item.
- **`docs/phases/phase-08-3.md`:** the provisional uses the same `tailSeedForOutput` and decorrelation as the exact tail; a mode switch never re-solves or waits (in scope and as a criterion).
- **`docs/phases/phase-09.md`:** the same rules for stereoSpeakers; the AX44/AX48 test is extended to stereoSpeakers (in scope and as a criterion).
- **`docs/phases/phase-10-2.md`:** record (g) feeds AX38 (v); D5-within-5 % and D6 are recorded alternatives; Seat 1 rules on automation-driven steps.
- **`docs/phases/phase-12-2.md`:** presets never carry E_b.
- **`docs/phases/phase-13-1.md`:** the 2.25 GB memory finding goes to the memory budget, never an instance cap.
- **`docs/phases/phase-13-5.md`:** the condition 11 results feed AX49's reversal. New scope 5 covers:
  - AX48's mismatch policy, including the build-id question;
  - the fingerprint-failure block;
  - a v1 build rejects v2 state;
  - wording: never "opens instantly", no cross-machine bit-identity claim.

### Held

- **`docs/review/ledger.md` append:** blocked by my rules, not by a decision. Draft below.
- **Correction 10 (AX48 "Decided" line) and correction 11 (S5/S7 cells "at T60_max ≲ 8.3 s"):** these belong in the PR's "Decided for Maisara" and the ledger, not in plan rows, so nothing was applied in the plan. Corrected Decided line for the PR: "**AX48:** the solved room level is saved with a five-part key, including the platform. A project opened on another OS or sample rate re-solves at load in about 0.1 s and builds its interim tail at the same time (about 0.5–0.65 s per instance at 96 kHz / T60 8 s; the full synthesis at T60_max ≳ 35 s), so it plays its tail at once. …" (the rest as in file 12).

### DECISIONS NEEDED

None of these hold back an edit I made. Each is a gap the decided texts leave open.

- **D1. AX47 self-ABX detection rule.**
  - Where: `docs/BUILD_PLAN.md` AX47 "Reversal", and `docs/phases/phase-07c-2.md` scope 9.
  - Question: what result counts as "detects a step below 1 dB"? AX47 gives 16 trials but no criterion, and no step sizes to test. L4 has ≥ 12/16.
  - Options:
    - (a) ≥ 12/16, the same as L4. Evidence: Blauert ch. 2 (forced-choice lateralisation method) takes 75 % agreement as the threshold, which is 12/16.
    - (b) Leave it to 07c-2's loop. Evidence: none found.
    - (c) A family-wise rule across the tested step sizes. Evidence: none found.
  - Waiting on it: nothing applied waits; 07c-2 scope 9 refers to the ABX as defined in AX47.
- **D2. Seat 3's bridge item 4 (file 14): "print the ISM latency in record (g)".**
  - Where: `docs/BUILD_PLAN.md` AX49 "T60-changing edits" / Acceptance.
  - Question: should AX49 record the ISM latency on T60 edits? File 12's D3*‴ text, which the brief says stands as written, leaves it out. File 9 had "record (g) prints the added ISM wait".
  - Options:
    - (a) Add the print to record (g) as Seat 3 conditioned its 1/1. Evidence: none found in the corpus; seat condition only.
    - (b) Leave AX49 as written. Evidence: none found.
  - Waiting on it: none (AX49 applied as written).
- **D3. Can AX49 reversal 1 ever fire?** (interrogator file 13, row P07C1-71 / Q2)
  - Where: `docs/BUILD_PLAN.md` AX49 "Reversal".
  - Question: "the gate fails at L_p ≤ 3.82 s" can fire only if a gated scene has L_p ≤ 3.82 s. The low-α cube is L_p ≥ L, and it is unknown whether the flutter scene carries a tail.
  - Options:
    - (a) Keep it as written.
    - (b) Print the flutter scene's L_p in the restore gate so the trigger can be evaluated.
    - (c) Tie the trigger to record (h)'s sweep points with L_p ≤ 3.82 s.
  - Evidence: none found (code question, `Engine.cpp` fallback path).
  - Waiting on it: none.

### Interpretations (non-acoustic choices I made)

- **AX18 placement:** the FM-1 block goes literally "before 'Amended by…'", so it lands in the Rationale column. I added 07c-1 to Breaks.
- **AX48 cross-reference:** file 9's "admissible only under AX47 (c)" became "governed by AX47 and 07c-2's loop", using file 12 §4's wording, because AX47 no longer has a class (c).
- **AX47 "From 07c-2":** also says "only after the AX47 self-ABX" (correction 7's order, stated in AX47 as well as in 07c-2). The δ gloss is from interrogator row 64.
- **Rationale columns:** written from file 12's rationale lines plus corrections 3, 4, 6 and 12.
- **AX38 (i) note:** file 12 makes it conditional; interrogator row 81 says class (1) already gives the order, so I worded it as a clarification, not a rule change.
- **Record (h):** placed as a paragraph under condition 9, noting that its letter continues condition 12's records.
- **Where the phase items went:**
  - phase-08 → 08-3 (E_b parity, plugin mode);
  - phase-10 → all three items in 10-2 scope 3;
  - phase-12 → 12-2;
  - phase-13 → 13-1 (memory) and 13-5 (everything else; condition 11 into scope 3).
- **`phase-07d.md`:**
  - No lead seat named; the loop named none, so it says Seats 5 and 7 are convened.
  - Acceptance criteria are procedural only: AX row before code, register form, bit-identity or golden round. No numbers.
  - Short Risks sentence; remainder file named `07d-b`.
  - The §0 title is mine.
- **§6 rows:** the phase-file list is in the AX49 row.
- **Review file 12:** not modified (saved verbatim).

### Draft ledger rows (for `docs/review/ledger.md`, heading "phase-07c-1 (decision loop, 2026-11-12)")

Corpus revision: c1b171fe649f07cbeb952ef1f75d89bfaa414d0d. Convening: file 2, all nine seats convened; Seat 2 NOT MY MATTER on C/D at 0/0 (file 11, row 31).

| id | item | outcome |
|---|---|---|
| D-C1 | AX47 C5‴: 1 dB per band, tail window; classes (a)/(b) in 07c-1; class (c) to 07c-2 | SURVIVES WITH CORRECTIONS (file 13 rows 64, 74, 75, 79); max 2, sum 10; tie with C3 broken by phase-07c-1 L40 / NFR-1 via Q9/AQ9 |
| D-C2 | AX48 B4-G′ plus gate priority | SURVIVES WITH CORRECTIONS (row 82, wording); max 1, sum 13 |
| D-C3 | AX48 A1′ + Π (five-part key) | SURVIVES WITH CORRECTIONS (row 79); row 47 closed; max 1, sum 11 |
| D-C9 | AX49 D3*‴ | TENSION MISREAD on the T60-edit path (row 59), settled by Seat 3 (file 14: D3*″'s edit path 3/3, the same hold vetoed in D2; 1/1 only with the bridge), so D3*‴ stands, max 2, sum 23, no NEEDS MAISARA. Rest SURVIVES WITH CORRECTIONS (rows 62 [S5/S7 cells hold at T60_max ≲ 8.3 s], 63 [D4: Seat 5's cell unrated], 68, 69, 70, 85) |
| FM-1 | equal-gain for same-scene steps | SURVIVES WITH CORRECTIONS (row 83, 0.986) |
| FM-2′ | gate content; prepare; 07d clause | SURVIVES WITH CORRECTIONS (rows 69, 73); the 07d reading is CORRECT (row 72) |
| FM-3′ | keyless synchronous stage-1 | SURVIVES (row 84) |
| FM-4′ | 1 dB, not 0.5 dB | SURVIVES WITH CORRECTIONS (rows 74, 75) |
| P07C1-01…30 | file 7 on decider file 5 (round 1) | D-C1, D-C2(B) and D-C9 FALL, with TENSION and PRD MISREADs; D-C3 FALLS on one clause; AX18 SURVIVES WITH CORRECTIONS with a PRD MISREAD (no AMENDS). All answered in file 9 |
| P07C1-31…58 | file 11 on decider file 9 (round 2) | D-C9 D3*′ FALLS (row 38); D-C1 C5″ FALLS; D-C2 SURVIVES WITH CORRECTIONS; D-C3 one clause FALLS (row 47); FM-2 and FM-4 FALL; FM-3 citation fixed. All closed in file 12 / row 86 |
| P07C1-59…86 | file 13 on decider file 12 (round 3) | as the rows above; corrections 1–13 applied in the plan (10 and 11 as report/ledger notes); Q2 (reversal 1) open as D3 |

### Files changed (`git diff --stat`, including the new untracked file)

```
 docs/BUILD_PLAN.md         | 16 +++++++--
 docs/phases/phase-07c-1.md | 68 +++++++++++++++++++++++------------
 docs/phases/phase-07c-2.md | 19 ++++++++--
 docs/phases/phase-07d.md   | 88 ++++++++++++++++++++++++++++++++++++++++++++++  (new, untracked)
 docs/phases/phase-08-3.md  |  7 ++++
 docs/phases/phase-09.md    |  7 ++++
 docs/phases/phase-10-2.md  |  5 +++
 docs/phases/phase-12-2.md  |  2 ++
 docs/phases/phase-13-1.md  |  4 ++-
 docs/phases/phase-13-5.md  | 10 ++++++
 10 files changed, 198 insertions(+), 28 deletions(-)
```

Paths: /home/user/makroof/docs/BUILD_PLAN.md, /home/user/makroof/docs/phases/phase-07c-1.md, /home/user/makroof/docs/phases/phase-07c-2.md, /home/user/makroof/docs/phases/phase-07d.md, /home/user/makroof/docs/phases/phase-08-3.md, /home/user/makroof/docs/phases/phase-09.md, /home/user/makroof/docs/phases/phase-10-2.md, /home/user/makroof/docs/phases/phase-12-2.md, /home/user/makroof/docs/phases/phase-13-1.md, /home/user/makroof/docs/phases/phase-13-5.md