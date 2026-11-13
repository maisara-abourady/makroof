# 32 — Decider round 3: P07C1B-R1 (PR #33 run 43427854710, the macOS OVER30S and the single MACTRIGGER)

2026-11-13, corpus c1b171f (no acoustic fact load-bearing). Saved by the orchestrator from the decider's report.

## Summary of the round
- Decision (1) is revised with C-1 … C-13 of file 31 applied.
- T1 is instance-only; the standing any-run rule is struck.
- The fallback carrier is the first code commit of the next phase session, 07c-2 or 07d, whichever starts first. Its carry item lands now in both phase files.
- Decision (2) stands, with C-8 and C-10 applied.
- For Maisara is restated (8a-1 … 8a-3).
- NEEDS MAISARA: none. Challenges to settled decisions: none.
- Seat 2's convening reason now reads: "no compute or recompute time set; records only".

## PRD and her decisions
- **Preamble, quoted whole:** "Accuracy is the top priority; CPU load and latency may be high, but the plugin must stay usable in a DAW session."
- **NFR-4** lists platforms: "VST3 and AU on macOS and Windows (AU is macOS-only by nature)."
- **NFR-6** ("restores … exactly") is about exactness, not time. It decides nothing here.
- **Her 2026-11-10 decision:** "I accept the board's answer by definition."
- **Her 2026-11-12 words** (brief `docs/sessions/2026-11-12-05i-windows-listed.md` L10–12): "do we have a session for this small follow up to run whether before or after 07c-1 it won't matter?" and "do that". The vehicle was dedicated follow-up PR #31: one full CI run of about 75 minutes.

## Answers to file 31
- **Q1, instance or rule.** Instance: C-1 is applied in its instance-only form, the form the seats rated.
  - T1 re-lists only this entry under RG-1's existing sentence: "A closed entry that later prints OVER30S is named in the PR; re-listing it is a `/fix-plan` reading under (a)."
  - The H1 note is struck, so "no rule changes" is true and Seat 5 needs no re-hearing.
  - Seat 5's own 2a fingerprint clause stays in T2.
- **Q2, her 2026-11-12 decision.**
  - What she settled: the 05i flag's vehicle (PR #31), with order immaterial. She stated no rule for later owed flags.
  - The fallback here: the first code commit of the next phase session after PR #33 merges, 07c-2 or 07d, whichever starts first.
    - Both depend only on 07c-1b `done` (BUILD_PLAN L36, L37).
    - 07d is the entry's closing phase, so a 07c-2-only fallback could leave the flag false through all of 07d. That is why 07d is added.
  - Seat 5's cell is read from its conditions: "review round, or 07c-2's first code commit". 07d's first code commit is the same kind of push.
  - Against her decision:
    - It keeps her indifference to order.
    - It differs from #31 in vehicle only, and adds no CI run (it rides that phase's PR run).
    - It does not amend her decision.
    - Her veto line: a dedicated follow-up PR as #31 replaces the next-phase commit, with the same contents, at the cost of one full CI run.
  - Why 05i's failure does not repeat: the 05i carrier was written into no phase file (P05I-120). Here T7 writes it into both possible next phases now.
  - The lag:
    - (i) until PR #33's review push, if the review takes the item up;
    - (ii) otherwise from merge until the next phase session's first code commit. No calendar bound; bounded in sequence; before that phase's first CI run and before 07d takes any run.
    - CI does not run on `main`, so no run prints the stale label meanwhile. The exception is a PR opened from `main` first; on a > 30 s reading its run still prints "WARNING OVER30S on a closed register entry (… name the run in the PR)" (code L694–695).
- **Q3, a prose-only review.**
  - The carrier rides the review push only if the review takes the item up. It is then a change the review asked for (clause (2)), covered by that round's one manual CI run.
  - Otherwise (prose-only review, item not taken up, or merge first) it moves to the next phase's first code commit, and the review push starts no run.
  - The excluded plain flip was a `tests/` push now, outside both clauses.
- **Q4, the recorded value.** (a) reads **33.40 s** after re-listing.
  - 33.40 s is the register's recorded value at the pinned W_max (3.05 M, unchanged), "recorded 33.40 s on the local box". It is still `recorded14xS` at L166 (print only: L97, L684–688). It is > 29.1 s.
  - E1 read (c)'s printed 14 × worst and did not change it. 30.50 s is the triggering run; 24.08 s is the closure record.
  - Windows precedent: #31 kept 36.73 s after its 46.63 s OVER30S.
- **Q5, the seats' conditions.**
  - Seat 6 (same push): met. T1, T4 and T8 land with the flag. T2, T3, T5 and T7 say "decided / pending / lands with its flag", never "listed" (C-7 applied).
  - Seat 3 C1: met after C-8. The conditions are carried in T1, T2, T3, T4 scope 1, T5, T8, the comment, the CHANGELOG line and the Decided line; T6 carries them through its reference to T5.
- **Correction to 28b's Q4 line:** "phase-05i §3.3 (ii)'s 'otherwise' branch … Same carrier (next permitted push) (in 05i that push never came: PR #30 merged first; the flag landed in follow-up PR #31, ledger P05I-120)."

## Knowledge (additions)
- K10: recorded value 33.40 s; `recorded14xS` and `listed` are print only (L97, L112, L166, L684–695).
- K11: CI does not run on `main`.
- K12: 07c-2 and 07d both depend only on 07c-1b `done`; neither has started.
- K13: her 2026-11-12 words; #31 cost one full CI run of about 75 minutes.
- K14: the 05i review carrier never fired.

## Tension map, Q1
Seats 1, 2, 4, 8 and 9 are 0/0.

| option | S3 | S5 | S6 | S7 | max | sum |
|---|---|---|---|---|---|---|
| 1a keep closed | 0/1 | 1/1 | 1/1 | 1/1 | 1 | 7 |
| 1b flag at the review push | 0/0 | 0/1 with a review push (2 without) | 0/0 | 0/0 | 1 / 2 | 1 / 3 |
| 1c text now, flag later | 0/0 | 0/1 | 1/1 | 0/0 | 1 | 3 |
| **1b′** = 1b + fallback (next phase's first code commit) | 0/0 (read from 1b/1c) | 0/1 (read from conditions) | 0/0 (same-push met) | 0/0 (read from 1b/1c) | **1** | **1** |

- Q2 unchanged: 2a max 1, sum 4; 2b max 2, sum 7.
- Bounds (C-3): 1b (flag at the review-round push) is inside bounds. With a review push 1b and 1b′ tie (max 1, sum 1); without one, Seat 5 rates 1b at 2. 1b′ = 1b + Seat 5's fallback carrier.
- A plain flip pushed now is out of bounds. No veto-grade rating.
- Choice: **1b′; 2a.**

## DECISION P07C1B-R1 (round 3)
1. **Re-list.** The macOS `cube100_lowalpha0.05_s0.3` entry is re-listed under AX38 4c (a), by RG-1's re-listing sentence, for this one entry: recorded value 33.40 s, run 43427854710 recorded, 'closes at' phase-07d (scope 1; remedy X-d−, scope 7).
   - T1, T4, T8, the `listed` flip, its comment and the CHANGELOG line land in **one carrier commit**: PR #33's review-round push if the review takes the item up; otherwise the first code commit of the next phase session, 07c-2 or 07d, whichever starts first (T7).
   - T2, T3, T5 and T7 land now; T6 names the pending re-list. Nothing asserted changes.
2. **MACTRIGGER.** The single MACTRIGGER is a print under FM-TRIG, filed as evidence to X-d− / 07d scope 7. A later consecutive pair joins X-d− under T2's conditions.

- Confidence: medium.
- Reversal: (1) 07d's runs after the remedy close the entry again under (c); (2) a pair's excess lies outside Assemble→Commit.
- Load-bearing claims:
  - L1: `listed` and `recorded14xS` change only the print.
  - L2: RG-1's sentence.
  - L3: E1 n = 3, worst 24.08 s, 1.27×.
  - L4: the carrier rides only a review-requested change or the next phase's first code commit, written into both phase files now (T7).
  - L5: the run budget is per defect.
  - L6: OVER30S always reaches the step summary.
  - L7: the recorded value is 33.40 s.
  - L8: no CI on `main`.

## Push clause
- T2, T3, T5 and T7 are fingerprint-excluded prose (`docs/BUILD_PLAN.md`, `docs/phases/`; ci_fingerprint.py L35, L44). They follow without a run.
- T6 is the PR body, not a push.
- The carrier changes the fingerprint. It rides the review round's push only as a change the review takes up (T6 puts it before the reviewer).
- If the review asks for no change outside fingerprint-excluded prose, does not take the item up, or PR #33 merges first, the carrier moves to the first code commit of the next phase session, 07c-2 or 07d, whichever starts first (T7).
- 05i decided the same carrier (file 9 item 4); it never fired (P05I-120).

## Carrier commit
One commit; one manual CI run if it is a review push.

1. `tests/unit/test_diffuse_records.cpp` L166, the macOS low-α initializer: 8th field `listed` `false` → `true`. Every other field unchanged; `recorded14xS` stays 33.40.
2. The comment at L160–163: append after L163, wrapped by clang-format: `// Phase 07c-1b P07C1B-R1: macOS re-listed under AX38 4c (a) after closure: PR #33 run 43427854710 printed 14 x worst 30.50 s (hosted macOS runner; 100 m / 96 kHz, exact tail L = 12 s, 2 emitters; not a per-instance cost; OVER30S); recorded value 33.40 s kept; print only.`
3. `tests/golden/CHANGELOG.md`, in #31's form:
   - Heading: `## <carrier commit date> (07c-1b P07C1B-R1)`.
   - Reason: the macOS entry closed under E1 on the S2 runs, then run 43427854710 printed OVER30S, so it is re-listed under (a); print only; no golden file changed.
   - Bullet: "- `(records-test constants)`: the macOS low-alpha entry re-listed under AX38 4c (a) after closure (PR #33 run 43427854710: 14 x worst 30.50 s on the hosted macOS runner; 100 m / 96 kHz, exact tail L = 12 s, 2 emitters; OVER30S); `listed` true, recorded value 33.40 s unchanged; print only (no golden file changed)".
4. T1, T4 and T8, through `/fix-plan`.
5. Effect (C-9):
   - The macOS restore-gate line (not the GATE line) reads "LISTED defect (recorded 14 x worst 33.40 s)".
   - Above 30 s it adds "WARNING OVER30S (printed, not asserted on hosted runners)". At or below 30 s it reads "WARNING PASSES30S: this entry now passes 30 s, remove it through /fix-plan" (L690–693), which T4 reads as closing only in 07d.
   - The GATE line's `warnings=` is unchanged. No REQUIRE changes.

## Texts, final
Land now (fingerprint-excluded prose): T2, T3, T5, T7. PR body: T6. Wait for the carrier: T1, T4, T8.

### T1 (carrier)
In AX38 4c, after "…re-listing it is a `/fix-plan` reading under (a).":

"*Re-listed (phase-07c-1b, 2026-11-13, decider P07C1B-R1; an instance of the sentence above, no rule added):* under RG-1's
re-listing provision the macOS `cube100_lowalpha0.05_s0.3` entry is re-listed under (a) on run 43427854710, recorded value 33.40 s (the
register's value at the pinned W_max, local box, file 1; > 29.1 s; not changed by the E1 closure, which read (c)'s printed 14 × worst),
'closes at' phase-07d (scope 1; remedy as X-d−, scope 7). PR #33's run 43427854710 (head ac54495; hosted macOS runner; records-test scene
100 m cube, 96 kHz, exact tail L = 12 s, 2 emitters; not a per-instance cost) printed 14 × worst 30.50 s (14 × the slowest of 10
restores, 2.18 s), median 1 851 ms, ratio 4.626 (1.48 × r̄ 3.1203), flutterDev −15.8 %; RATIO, GROWTH, OVER30S and MACTRIGGER. The E1
closure sample was n = 3 S2 runs (macOS worst 24.08 s), exceeded by 1.27× (30.50 / 24.08); the E1 closure stays on record. Unlike
phase-05i decider file 9 item 4 (the Windows entry never closed: phase-05i §3.3 (ii)'s 'otherwise' branch), this entry closed under E1 and
is re-listed after closure. `listed` true, print only; nothing asserted changes; the low-α hosted-runner form stays until Phase 13."

### T2 (now)
In the X-d− paragraph, inside the parenthesis after "…no S2 run exceeds it", before its ")":

"; PR #33's run 43427854710 (head ac54495; restore path as the S2 runs; hosted macOS runner, records-test scene at 100 m / 96 kHz, L =
12 s, 2 emitters; not a per-instance cost) prints MACTRIGGER once (low-α median 1 851 ms > 1 703 ms; preceding macOS run S2 43412038058,
1 586 ms; stage hooks: Assemble→Commit 1 673.8 ms of the median): one run, a print under FM-TRIG, not a new (d) defect; evidence for
phase-07d scope 7. A second macOS pair with the same symptom joins the open defect and its closure test; it is split out only if 07d shows
a separate cause. The pair is this run and the next macOS run whose records test executes (a fingerprint-skipped run does not count),
with no change to the restore path's code in between; it joins only if that run's stage hooks also put the excess in Assemble→Commit
(otherwise the pair is a new (d) defect); X-d− keeps one budget of ≤ 3 extra manual runs, the joined pair adds none and no run is started
to test it; if 07d's split timer attributes the pair to another stage, or the 07d loop finds its synthesis share well below X-d−'s ≈ 95 %
(Seat 3), the pair splits out through `/fix-plan` as its own (d) defect with its own ≤ 3 runs; FM-TRIG condition (4) stands"

### T3 (now)
Append to phase-07d scope 7:

"Evidence added at 07c-1b (AX38 4c X-d−, P07C1B-R1): PR #33's run 43427854710 (head ac54495; restore path as the S2 runs; hosted macOS
runner; records-test scene 100 m / 96 kHz, exact tail L = 12 s, 2 emitters; not a per-instance cost): MACTRIGGER once (low-α median
1 851 ms), ratio 4.626 (1.48 × r̄), flutterDev −15.8 %, 14 × worst 30.50 s (OVER30S; the entry's re-list decided, P07C1B-R1, lands with
its flag in the carrier push, scope 1 and scope 9): a print, not a new defect. A joined pair adds no runs to this defect's ≤ 3. The
closure test re-attributes the macOS low-α restore with the split timer (a pair attributed elsewhere splits out) and checks that
restore's interim→final tail handover for clicks with the tools/acoustics click detector, on runs 07d makes."

### T4 (carrier)
- **phase-07d scope 1 (L42).** Replace "a later OVER30S is handled as AX38 4c E1 states." with:
  "a later OVER30S is handled as AX38 4c E1 states. **macOS re-listed** under (a) (P07C1B-R1): run 43427854710 (hosted macOS runner; 100 m / 96 kHz, exact tail L = 12 s, 2 emitters; not a per-instance cost) printed 14 × worst 30.50 s; recorded value 33.40 s (AX38 4c); it closes in this phase under (c) on this phase's runs after the remedy (a PASSES30S before then is a print)."
- **phase-07d scope 5** (the anchor spans the hard wrap at L69–70: "Both⏎ entries closed in phase-07c-1b (E1; scope 1)."). Replace with:
  "Both entries closed in phase-07c-1b (E1; scope 1); macOS re-listed under (a) (P07C1B-R1, run 43427854710), 'closes at' 07d."
- **BUILD_PLAN §0 row 07d.** After "closed in 07c-1b (E1, 2026-11-13)" add:
  "; macOS re-listed under (a) on run 43427854710 (P07C1B-R1)"

### T5 (now)
Append to §0 row 05h:

"PR #33 run 43427854710 (ac54495; hosted runners; records-test scenes 100 m / 96 kHz, low-α exact tail L = 12 s, 2 emitters; not
per-instance costs): low-α 14 × worst Linux / macOS / Windows 21.58 / 30.50 / 19.54 s; ratio 2.380 (print-only) / 4.626 (print-only) /
2.501 (asserted, ≤ 2.783, pass); WARNING: Linux GROWTH, PASSES30S; macOS RATIO, GROWTH, OVER30S, MACTRIGGER; Windows PASSES30S;
in-window Linux no / macOS no / Windows yes; this run adds to the counts: WARNING runs 1; in-window 0 / 0 / 1; GROWTH 1 / 1 / 0; OVER30S
0 / 1 / 0; MACTRIGGER 1 (macOS); macOS low-α re-list decided (P07C1B-R1), lands with its flag in the carrier (PR #33's review push if the
review takes it up, else the first code commit of 07c-2 or 07d, whichever starts first)."

### T6 (PR #33 description)
- **WARNING runs:** run 43427854710 with T5's figures and their conditions.
- **Pending:** "Pending: the macOS low-α register entry is re-listed under AX38 4c (a) (P07C1B-R1; recorded value 33.40 s; run 43427854710 printed 14 × worst 30.50 s on the hosted macOS runner, 100 m / 96 kHz, L = 12 s, 2 emitters). Its plan text and the `listed` flag land together in one commit: in this PR's review-round push if the review takes the item up (the test file is in the CI fingerprint, so that push needs one manual CI run); otherwise in the first code commit of the next phase session, 07c-2 or 07d, whichever starts first (a carry item in both phase files). Until then the plan says closed with the re-list pending and the flag reads false (print only; nothing asserted changes)."
- **Seat 7's sentence:** "A second macOS pair with the same symptom joins the open defect and its closure test; it is split out only if 07d shows a separate cause."
- **Decided for Maisara:** P07C1B-R1 (the line below).

### T7 (now)
Two insertions with the same body:
- (a) `docs/phases/phase-07c-2.md`: a new scope item "10. " after "   - **Seat 2's prefix check:** verify Seat 2's prefix claim (`pathCount`, `pilotStops`)." and before `## Out of scope`. The bracket reads "phase-07d scope 9".
- (b) `docs/phases/phase-07d.md`: scope item "9. " after item 8 and before `## Out of scope`. The bracket reads "phase-07c-2 scope 10".

Body:

"**Carried from 07c-1b (P07C1B-R1), only if `listed` is still `false` on the macOS `cube100_lowalpha0.05_s0.3` row of `kGateRegister` on
`main` when this phase starts:** in this phase's first code commit, in one commit: that row's `listed` `false` → `true` in
`tests/unit/test_diffuse_records.cpp` with its comment line, the `tests/golden/CHANGELOG.md` line, and texts T1, T4 and T8 (through
`/fix-plan`), exactly as written in `docs/review/phase-07c-1b/32-decider-R1-round3.md`; nothing else in the row changes (`recorded14xS`
stays 33.40). The same item stands in [phase-07c-2's Scope | phase-07d scope 9]; whichever phase starts first does it, and the other
records it as done with the commit."

### T8 (carrier)
Append a §6 row:

"| <carrier commit date> (decided 2026-11-13) | **Phase 07c-1b: AX38 4c:** macOS low-α entry re-listed under (a) after closure (run 43427854710, hosted macOS runner,
100 m / 96 kHz, L = 12 s, 2 emitters: 14 × worst 30.50 s; recorded value 33.40 s); `listed` true, print only | /fix-plan (plan-editor),
decider files 28/28b/32, interrogator files 29/31/33 |"

## Future debt

| seat | commits later phases to | undo cost | evidence arrives | repaid when |
|---|---|---|---|---|
| S5 1b′ | flag and text wait for the carrier; lag until the review push, else the next phase's first code commit (no calendar bound; no CI on `main`) | one flag + text | review round / 07c-2 or 07d first code commit | carrier lands |
| S3 2a | join rests on code identity and stage attribution; 07d click check | `/fix-plan` split | 07d split timer, closure test | X-d− closure |
| S5 2a | stage hooks decide the join | same | next executed macOS run; 07d | same |
| S6 2a | same-stage join; closure test covers the pair | same | 07d | same |
| S7 2a | one ≤ 3 budget, no added run | split gets its own ≤ 3 | 07d | same |

**Strongest objection:** Seat 5's "2 without a review push", together with the 05i review carrier that never fired.
- It holds: T7 writes the fallback into both next phases now (07d included, the entry's closing phase), and CI does not run on `main`.
- It would fail if a third PR from `main` ran first. That run still names the run on a > 30 s reading.

## FOR MAISARA P07C1B-R1
- **Rests on:**
  - NFR-4 (macOS listed as a target platform);
  - the preamble (quoted whole above);
  - NFR-6 (exactness, not time; decides nothing here);
  - AX38 4c (a), (c), E1, FM-TRIG, X-d− and RG-1's re-listing sentence;
  - her 2026-11-10 and 2026-11-12 words.
- **Options:**
  - 1a strains NFR-4 (closed beside 30.50 s); mild strain on the preamble; NFR-6 not touched.
  - 1b serves both only if a review push comes.
  - 1c serves both in text, with the flag lagging.
  - 1b′ serves both, text and flag in one commit. Of its fallbacks, the next phase's commit adds no run; a dedicated PR as #31 costs one run (her veto line).
  - 2a serves NFR-4 (one owner, one remedy).
  - 2b is neutral, with a duplicate owner.
- **Veto readings:**
  - (i) "n = 1 against n = 3 should not re-list a just-closed entry": it holds, because the change is print-only, E1 stays on record and 07d re-closes the entry under (c).
  - (ii) "my 2026-11-12 choice means owed flags get their own follow-up PR": then a dedicated follow-up PR as #31 replaces the next-phase commit.
- `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (the AX38 4c register state under (a)'s own provision, RG-1's re-listing sentence; no rule changes).
- Her 2026-11-12 decision is not amended: it settled the 05i instance's vehicle and stated no rule.

## Decided for Maisara
"P07C1B-R1 — the macOS 100 m low-absorption restore check went back on the defect list after one CI run's restore check read 30.50 s (14
× its slowest restore, 2.18 s; the limit is 30 s) — on a shared hosted Mac CI runner (run 43427854710), 100 m room at 96 kHz, 12 s exact tail, 2 emitters, not the load time of one
plugin. Nothing that is tested changes; the fix stays in phase 07d. The one slow macOS reading counts as evidence for the existing macOS
defect, not a new one. Rests on NFR-4 (macOS is a target platform) and the NFR preamble ("Accuracy is the top priority; CPU load and
latency may be high, but the plugin must stay usable in a DAW session."); NFR-6 not engaged. Options: keep it closed (the macOS record
misstated); flag only at the review push (fails if none comes); text now, flag later (text and code disagree); chosen: text and flag
together. Seat 5 gives most (a lag until the review push, or the first code commit of 07c-2 or 07d, whichever comes first) and gets back
an honest register and 07d's re-test. `AMENDS her decision of 2026-11-10: "I accept the board's answer by definition."` (the AX38 4c
register state under (a)'s own provision; no rule changes). Does not amend her decisions of 2026-11-12 (her request for a session for the 05i flag, "do we have a session for this small follow
up…", which became follow-up PR #31; and "do that", which put the BUILD_PLAN wording fix in #31 and left the PASSES30S readings to the
next phase, 07c-1); if she wants a dedicated vehicle here, a follow-up PR as #31 replaces the next-phase commit."

## Summary

| id | decision | state | worst-off | sum | confidence | PRD bound | reversal |
|---|---|---|---|---|---|---|---|
| P07C1B-R1 (1) | macOS low-α re-listed under (a), this entry only, recorded 33.40 s, run 43427854710; text + flag in one carrier commit (review push if taken up, else the first code commit of 07c-2 or 07d) | revised | S5 0/1 | 1 | medium | NFR-4, preamble, NFR-6 (role stated) | 07d runs re-close it under (c) |
| P07C1B-R1 (2) | one MACTRIGGER is a print; a pair joins X-d− under stage, budget and code-identity conditions | stands | 0/1 | 4 | medium | NFR-4, preamble | a pair attributed to another stage |


**Orchestrator's application (2026-11-13, no new decision; interrogator file 33):** K1 (Decided line: run id, 12 s tail, 2 emitters; her 2026-11-12 words quoted as recorded, brief L10–12), K2 (T8 dated by the carrier commit), K3 (T7(a) as scope item 10) applied above.
