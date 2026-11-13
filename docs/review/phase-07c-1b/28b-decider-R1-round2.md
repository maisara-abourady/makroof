# 28b — Decider round 2: P07C1B-R1 (PR #33 run 43427854710, the macOS OVER30S and the single MACTRIGGER)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing). Saved by the orchestrator from the decider's report. File 28 falls.
Answer 1 is revised: re-list now under (a), with the text and the flag in one permitted push. Answer 2 stands (2a), with the conditions
folded in. NEEDS MAISARA: none. Challenges to settled decisions: none.

**Convening** (nine rows):
- Seat 1 not required: nothing audible; `listed` only changes a CI print label (test_diffuse_records.cpp L686–697).
- Seat 2 not required: geometry and room response untouched.
- Seat 3 convened: X-d− debt row; the synthesis mechanism.
- Seat 4 not required: chain untouched.
- Seat 5 convened: CI gates, register state, trigger, the `tests/` push.
- Seat 6 convened: 14 × worst as the user's wait (preamble, NFR-4).
- Seat 7 convened: the ≤ 3 runs per defect budget; public wording.
- Seat 8 not required: no workflow.
- Seat 9 not required: no room reference.

Seat positions: file 30.

**Knowledge:**
- K1: run facts (file 28; file 29 CORRECT).
- K2: `listed` changes the print only (code L112, L686–697).
- K3: E1 closure sample n = 3, macOS worst 24.08 s; 30.50 / 24.08 = 1.27.
- K4: a closed entry's OVER30S still reaches the step summary (ci.yml L434 greps `warnings=` regardless of `listed`), which meets C6-i.
- K5: phase-05i file 9 item 4 L24.
- K6: budget per defect (phase-07d L80; file 11 L173–174).
- K7: the scene is 2 emitters, 100 m, 96 kHz, L = 12 s.
- K8: Assemble→Commit 1 673.8 of 1 851 ms (Seat 5, macos.log L3053). Not load-bearing; the interrogator is to check it.
- K9: PR #33 open, run green, no review round yet.

**Tension map** (now/later; seats 1, 2, 4, 8, 9 at 0/0).

Q1:

| option | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| 1a keep closed | 0/1 | 1/1 | 1/1 | 1/1 | 1 | 7 |
| 1b flip at review push | 0/0 | 0/1 (2 without a review push) | 0/0 | 0/0 | 1–2 | 1–3 |
| 1c text now, flag later | 0/0 | 0/1 | 1/1 | 0/0 | 1 | 3 |
| **1b′** text + flag in one permitted push | 0/0 | 0/1 (read from conditions) | 0/0 (C6 same-push met) | 0/0 | **1** | **1** |

Q2:

| option | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| **2a** a print; a pair joins X-d− | 0/1 | 0/1 | 0/1 | 0/1 | 1 | 4 |
| 2b a pair is a separate (d) | 1/2 | 1/1 | 0/1 | 0/1 | 2 | 7 |

**Working:**
- A plain 1b flip pushed now is out: a `tests/` push that is neither a CI fix nor a review request.
- No veto.
- Worst-off: 1b′, 1a and 1c at 1 (plain 1b may be 2); 2a at 1.
- Composed: 1b′ = 1c + C6 same push + Seat 5's fallback carrier.
- Sum: 1b′ (1) < 1c (3) < 1a (7). Choice: **1b′, 2a**.

**DECISION P07C1B-R1 (revised).**
1. The macOS `cube100_lowalpha0.05_s0.3` entry is re-listed under AX38 4c (a), run 43427854710 recorded, 'closes at' phase-07d (scope 1; remedy X-d−, scope 7). The register text (T1, T4, T8), the `listed` flip and the CHANGELOG line land together in **one carrier push**: the contractor review round's push on PR #33; if the review asks for no change before merge, 07c-2's first code commit (T7). Until it lands, the PR names the pending re-list (T6). Nothing asserted changes.
2. The single MACTRIGGER is a print under FM-TRIG, filed as evidence to X-d− / 07d scope 7. A future consecutive pair joins X-d− under the folded conditions (T2).

Confidence medium.

**Reversal:**
- (1) the 07d remedy runs re-close the entry under (c).
- (2) the stage hooks or the 07d split timer put a pair's excess outside Assemble→Commit, so it splits out.

**Load-bearing:**
- L1: `listed` changes the print only.
- L2: the RG-1 text "A closed entry that later prints OVER30S is named in the PR; re-listing it is a `/fix-plan` reading under (a)".
- L3: E1 n = 3, worst 24.08 s; 1.27×.
- L4: the carrier push is permitted.
- L5: the budget is per defect.
- L6: OVER30S keeps printing to the step summary.

**Answers to file 29:**
- Q1: UNDERCONVENED accepted; Seat 5 heard.
- Q2: file 28's Seat 5 debt row came from no report and is struck.
- Q3: the budget stays per defect; a joined pair adds none; a split-out pair gets its own ≤ 3.
- Q4, the distinction from phase-05i file 9 item 4: there the entry was still closing on 05i's runs including the run of record (E1's 'otherwise' branch: it never closed). Here it closed on the S2 runs under E1 and is re-listed after closure, under (a)'s re-listing provision. Same carrier (next permitted push). The E1 closure stays on record; AC 2 stays met on the S2 runs.
- Q5: options against the PRD, below.
- Imprecise items:
  - R1-L4 / L4b: replaced by Q4.
  - R1-L5: restated in T1.
  - R1-L7: accepted.
  - R1-L8: push clause named below.
  - R1-L10: T5 restated.
  - H1: the pin-only rule is withdrawn. Any records-test run's OVER30S counts; a fingerprint-skipped run does not (Seat 5 (i)).

**Push clause:**
- T2, T3, T5 and T7 are fingerprint-excluded prose ("Bookkeeping that touches only fingerprint-excluded prose … may follow without a run").
- T6 is the PR body, not a push.
- The carrier (the flag in `tests/unit/`, `tests/golden/CHANGELOG.md`, T1, T4, T8) changes the CI fingerprint. It rides clause (2), review-round changes batched into one push plus one manual CI run, as a disclosed rider (05i precedent). If the contractor objects or asks for no push, it moves to 07c-2's first code commit (T7).

**Carrier push** (one commit, then one manual CI run):
1. `tests/unit/test_diffuse_records.cpp` ~L166: on the macOS low-α initializer, `listed` `false` → `true`; the other fields unchanged (33.40 stays as history).
2. The comment at ~L160–163, append: "Phase 07c-1b P07C1B-R1: macOS re-listed under AX38 4c (a) after closure: PR #33 run 43427854710 printed 14 x worst 30.50 s (OVER30S); print only."
3. `tests/golden/CHANGELOG.md`: "`(records-test constants)`: the macOS low-alpha entry re-listed under AX38 4c (a) after PR #33's run 43427854710 (14 x worst 30.50 s, OVER30S); `listed` true, print only (no golden file changed)".
4. T1, T4 and T8.
5. Expected effect: the macOS GATE label reads "LISTED defect; WARNING OVER30S". No REQUIRE changes.

**Texts.**

**T1** (AX38 4c, after "…re-listing it is a `/fix-plan` reading under (a).", carrier push):
"*Reading (phase-07c-1b, 2026-11-13, decider P07C1B-R1):* (a) reads the register's recorded value at the pinned W_max (for a closed
entry, the E1 values); a closed entry that later prints OVER30S on a CI run whose records test executes (a fingerprint-skipped run does
not count) is re-listed under (a) with the run recorded and 'closes at' its remedy phase. Unlike phase-05i decider file 9 item 4 (the
entry still closing on 05i's runs including the run of record: E1's 'otherwise' branch), this entry closed on the S2 runs under E1 and is
re-listed after closure. First instance: macOS `cube100_lowalpha0.05_s0.3` **re-listed**, 'closes at' phase-07d (scope 1; remedy as X-d−,
scope 7): PR #33's run 43427854710 (head ac54495; hosted macOS runner; records-test scene 100 m cube, 96 kHz, exact tail L = 12 s, 2
emitters; never a per-instance cost) printed 14 × worst 30.50 s, median 1 851 ms, ratio 4.626 (1.48 × r̄ 3.1203), flutterDev −15.8 %;
RATIO, GROWTH, OVER30S and MACTRIGGER. The E1 closure sample was n = 3 S2 runs (macOS worst 24.08 s), exceeded by 1.27× (30.50 / 24.08).
`listed` true, print only; nothing asserted changes; the low-α hosted-runner form stays until Phase 13."

**T2** (X-d− paragraph, inside the parenthesis after "…no S2 run exceeds it", before its ")"; now):
"; PR #33's run 43427854710 (head ac54495; restore path as the S2 runs; hosted macOS runner, records-test scene at 100 m / 96 kHz) prints
MACTRIGGER once (low-α median 1 851 ms > 1 703 ms; preceding macOS run S2 43412038058, 1 586 ms; stage hooks: Assemble→Commit 1 673.8 ms
of the median): one run, a print under FM-TRIG, not a new (d) defect; evidence for phase-07d scope 7. A second macOS pair with the same
symptom joins the open defect and its closure test; it is split out only if 07d shows a separate cause. The pair is this run and the next
macOS run whose records test executes (a fingerprint-skipped run does not count), with no change to the restore path's code in between; it
joins only if that run's stage hooks also put the excess in Assemble→Commit; X-d− keeps one budget of ≤ 3 extra manual runs, the joined
pair adds none and no run is started to test it; if 07d's split timer attributes the pair to another stage, or the 07d loop finds its
synthesis share well below X-d−'s ≈ 95 % (Seat 3), the pair splits out through `/fix-plan` as its own (d) defect with its own ≤ 3 runs;
FM-TRIG condition (4) stands"

**T3** (phase-07d scope 7, appended; now):
"Evidence added at 07c-1b (AX38 4c X-d−, P07C1B-R1): PR #33's run 43427854710 (head ac54495; restore path as the S2 runs; hosted macOS
runner; records-test scene 100 m / 96 kHz, L = 12 s, 2 emitters): MACTRIGGER once (low-α median 1 851 ms), ratio 4.626 (1.48 × r̄),
flutterDev −15.8 %, 14 × worst 30.50 s (OVER30S; the entry re-listed, scope 1): a print, not a new defect. A joined pair adds no runs to
this defect's ≤ 3. The closure test re-attributes the macOS low-α restore with the split timer (a pair attributed elsewhere splits out) and
checks that restore's interim→final tail handover for clicks with the tools/acoustics click detector, on runs 07d makes."

**T4** (carrier push):
- phase-07d scope 1: "a later OVER30S is handled as AX38 4c E1 states." → "a later OVER30S is handled as AX38 4c E1 states. **macOS re-listed** under (a) (P07C1B-R1): run 43427854710 printed 14 × worst 30.50 s; it closes in this phase under (c) on this phase's runs after the remedy."
- phase-07d scope 5: "Both entries closed in phase-07c-1b (E1; scope 1)." → "Both entries closed in phase-07c-1b (E1; scope 1); macOS re-listed under (a) (P07C1B-R1, run 43427854710), 'closes at' 07d."
- BUILD_PLAN §0 row 07d: after "closed in 07c-1b (E1, 2026-11-13)" add "; macOS re-listed under (a) on run 43427854710 (P07C1B-R1)".

**T5** (§0 row 05h, appended; now):
"PR #33 run 43427854710 (ac54495): low-α 14 × worst Linux / macOS / Windows 21.58 / 30.50 / 19.54 s; ratio 2.380 (print-only) / 4.626
(print-only) / 2.501 (asserted, ≤ 2.783, pass); WARNING: Linux GROWTH, PASSES30S; macOS RATIO, GROWTH, OVER30S, MACTRIGGER; Windows
PASSES30S; in-window Linux no / macOS no / Windows yes; counts as the GATE lines' status fields give them (by script); a WARNING run; macOS
low-α re-list decided (P07C1B-R1), lands with its flag in the carrier push."

**T6** (PR #33 description):
- Under WARNING runs: run 43427854710 with T5's figures, with Seat 3's conditions.
- "Pending: the macOS low-α register entry is re-listed under AX38 4c (a) (P07C1B-R1); its plan text and the `listed` flag land together in the review-round push, or in 07c-2's first code commit if the review asks for no change; until then the plan says closed and the flag reads false."
- Seat 7's sentence.
- P07C1B-R1 under "Decided for Maisara".

**T7** (phase-07c-2, carry item; now):
"**Carried from 07c-1b (P07C1B-R1), only if PR #33 merged before its carrier push:** in this phase's first code commit, in one commit:
`listed` true on the macOS low-α entry in tests/unit/test_diffuse_records.cpp, the tests/golden/CHANGELOG.md line, and texts T1, T4 and T8
of docs/review/phase-07c-1b/28b-decider-R1-round2.md."

**T8** (§6 row, carrier push):
"2026-11-13 | 07c-1b | AX38 4c: macOS low-α entry re-listed under (a) after closure (run 43427854710, 30.50 s); `listed` true, print only |
decider files 28/28b, interrogator 29/<next>".

**Future debt** (rating seats only):

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S5 1b′ | flag waits for a permitted push; until then plan and PR disagree with it | one flag + text | review round / 07c-2 first commit | carrier lands |
| S3 2a | join rests on code identity and stage attribution; 07d click check | `/fix-plan` split | 07d split timer, closure test | X-d− closure |
| S5 2a | stage hooks decide the join | same | next executed macOS run; 07d | same |
| S6 2a | same-stage join; closure test covers the pair | same | 07d | same |
| S7 2a | one ≤ 3 budget, no added run | split gets its own ≤ 3 | 07d | same |

**Strongest objection:**
- Seat 5's "2 without a review push": it holds because 1b′ names a second permitted carrier (07c-2's first code commit); if neither happens, the re-list stays pending and is said so.
- Clause (2) names review-requested changes: it holds on the 05i precedent and the disclosed fallback.

**FOR MAISARA P07C1B-R1.**

Rests on:
- NFR-4 ("VST3 and AU on macOS and Windows");
- the NFR preamble ("must stay usable in a DAW session");
- NFR-6 ("restores … exactly"; its role: restore time is not its subject, so it decides nothing here);
- AX38 4c (a), (c), E1, FM-TRIG, X-d−.

Options against NFR-4 / preamble / NFR-6:
- 1a: strains NFR-4 (a shipping-OS entry shows closed beside 30.50 s); mildly strains the preamble; NFR-6 not touched.
- 1b: serves both only if a review push comes.
- 1c: serves both in text, with the flag lagging.
- 1b′: serves both, with text and flag together.
- 2a: serves NFR-4 (one owner, one remedy).
- 2b: neutral, with a duplicate owner.

No PRD goal points to another surviving option.

Veto reading ("one hosted print should not re-list a just-closed entry, n = 1 against n = 3"): it holds because NFR-4 ranks macOS as shipping, the change is print-only, and the entry re-closes on 07d's runs.

**Decided for Maisara:** "P07C1B-R1 — the macOS 100 m low-absorption restore check went back on the defect list after one CI run took
30.50 s; nothing that is tested changes; the fix stays in phase 07d. The one slow macOS reading counts as evidence for the existing macOS
defect, not a new one. Rests on NFR-4 and the NFR preamble (NFR-6 not engaged). Seat 5 gives most (a short lag before the flag lands)
and gets back an honest register and 07d's re-test. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."`
(the AX38 4c register state under (a)'s own provision; no rule changes)."

**Summary:**

| id | decision | state | worst-off | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|---|
| P07C1B-R1 (1) | re-list macOS low-α under (a); text + flag in one permitted carrier push (review round, else 07c-2 first commit) | revised | S5 0/1 | 1 | medium | NFR-4, preamble, NFR-6 (role stated) | 07d runs re-close it under (c) |
| P07C1B-R1 (2) | single MACTRIGGER a print; a pair joins X-d− under stage, budget and code-identity conditions | stands | 0/1 | 4 | medium | NFR-4, preamble | pair attributed to another stage |
