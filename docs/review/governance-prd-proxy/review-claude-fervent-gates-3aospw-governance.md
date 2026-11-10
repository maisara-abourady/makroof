# Review: branch claude/fervent-gates-3aospw — governance: the decider answers for Maisara from the PRD   (head 3940f96, base origin/main 808d3b0)

Branch review (no PR yet). It can end only in "Request changes" or "Not ready (no CI)". Wherever a step
needs the PR or CI: no PR: not checked. The PR description reviewed is the draft at
`scratchpad/pr2-body.md` (session scratchpad), read as the intended description.

## Verdict
**Not ready (no CI)**, and Request changes. The branch changes only process prose (10 files under
`.claude/`, `CLAUDE.md`, `docs/board/README.md`, `docs/sessions/`). The decider now answers, from
`docs/PRD.md` and her recorded decisions, the questions the decision loop used to stop to ask Maisara.
Only three cases still go to her: the PRD is silent or contradicts itself, a change to the PRD itself,
and overriding a seat's veto-grade rating. The rule is stated once (`docs/board/README.md:71-124`) and the
decider, interrogator, steward, plan-editor, `/fix-plan`, `/interrogate`, CLAUDE.md and the brief template
follow it. Generated seat files are unchanged (`build_agents.py --check` prints `ok`). The earlier rounds'
fixes (M1–M6, minors 1–15, N1–N6) hold, and I re-raise none of them. **The most important finding:** the
approved message required the decider to "show how each option serves" the PRD requirements it cites.
That requirement is not in the rule, the decider's output format or the interrogator's PRD MISREAD check
(Major 1). Fixing Major 1 and Major 2, then getting a green `ci ok` on the head, would make the branch
ready to open.

## Process gate
- **Scope:** every hunk is in the brief's scope (`docs/sessions/2026-11-10-decider-prd-proxy.md:59-67`:
  O2–O6 files, `interrogate.md`, the brief). There is no PRD, BUILD_PLAN, phase-file, code, test or seat
  change, which matches the brief's "Out". This is not a phase PR, so "one phase per PR" does not apply.
  The `board:` commit prefix follows the non-phase precedent on main (`plan:`, `ci:`, PRs #18 and #22).
  The approved message named only CLAUDE.md, `/fix-plan` step 3 and the decider. The wider file set
  (interrogator, steward, plan-editor, `/interrogate`, the sessions README) follows from the approved
  "interrogator check" bullet and from consistency, and the steward accepted it (brief round 2, BRIEF OK).
- **Dependencies:** not applicable (no phase). The base 808d3b0 is the PR #25 merge, which matches the
  approved "after the phase-05b merge".
- **Status table / §6:** BUILD_PLAN is untouched (review_context: no status row or §2/§6 change). No §6
  row is needed: no assumption, threshold or golden changed.
- **Assumptions used:** none. **New or changed assumptions:** none. The rule itself is a process change,
  and her words cover it (brief:8-44).
- **Boundary and contract:** not touched. The head-tree boundary check is clean. The NFR-8 scan hit at
  `src/sim/Engine.cpp:418` is pre-existing and not in this diff.
- **Goldens / tolerances / skips:** none.
- **PR description sections:** the draft lacks the acceptance-criteria checklist mapped to evidence, the
  listening checklist, the contractor review focus and the assumption/golden changes (Major 2). It has
  "Decided for Maisara" and Follow-ups.
- **CI:** no PR, so not checked. Every changed path is fingerprint-inert:
  `ci_fingerprint.py --rev 808d3b0` equals `--rev 3940f96` (`efd55cdd…566b`). CLAUDE.md says a PR's
  markers are visible only to that PR, so a new PR will probably run CI in full rather than skip. Either
  way, `ci ok` on the head is unproven until the PR exists.
- **CLAUDE.md edits (SKILL step 4.4):** the build/test section is untouched. The changed passages are
  rule 2 (`CLAUDE.md:14-17`), Reporting 3 (`:70-76`), The board (`:113-135`) and Git and PRs
  (`:336-338`). No rule is weakened beyond what her approved message changes. Two departures from the
  message are disclosed in the PR draft (item 4): the case (a) qualifier and the failed 3-round ruling.

## Acceptance criteria audit
This is not a phase, so the criteria are the brief's objectives O1–O9 (brief:46-57).

| # | Criterion (brief) | Evidence | Reference used | Tolerance | CI evidence | Gap it would miss | Verdict |
|---|---|---|---|---|---|---|---|
| O1 | Brief checked, BRIEF OK, committed | c8920a8; brief:95 (round 2 BRIEF OK) | steward | n/a | n/a | — | proven |
| O2 | Rule stated once in the board README | `docs/board/README.md:71-124` | her 14:08 approved message (brief:23-44) | n/a | n/a | the "how each option serves them" requirement (Major 1) | proven, with Major 1 |
| O3 | Decider follows it | `decider.md:3,33-35,47-52,56-64,66-115,223-232,253-254,286-290,298-315,322-324` | README section | n/a | n/a | Major 1; Minors 1–2 | proven, with Major 1 |
| O4 | `/fix-plan` step 3 follows it | `fix-plan.md:14-17,31-55,64-68` | README section | n/a | n/a | Minor 3 (entry route) | proven |
| O5 | Steward and interrogator follow it | `steward.md:54-57,75-77,93-96,107-143,149-151`; `interrogator.md:3,20-22,140-185` | README section | n/a | n/a | Minors 2 and 7 | proven |
| O6 | CLAUDE.md consistent | `CLAUDE.md:14-17,70-76,113-135,336-338` | README section | n/a | n/a | — | proven |
| O7 | Seat files untouched | `build_agents.py --check` → `ok`; the diff names no `seat*` file | generator | n/a | n/a | — | proven |
| O8 | PR opened, CI green | none | — | — | no PR: not checked | any | not proven (pending by design) |
| O9 | No old rule left (grep, each hit classed) | my grep: `decider.md:3` still says "Maisara's settled decisions", a phrase on O9's own list; the classification is not in the repo | O9 phrase list | n/a | n/a | Minor 1 | weak |

## Findings (by severity)

### Blockers
None in the diff. The verdict is "Not ready (no CI)" only because no PR or CI run exists yet (O8).

### Major
1. **`docs/board/README.md:88-90`, `.claude/agents/decider.md:83-93` and `:105-110`,
   `.claude/agents/interrogator.md:149-163`: the approved "show how each option serves them" was dropped.**
   The message she answered with "Do it" (brief:28) says: "**Show the reasoning.** It must name the PRD
   requirements it relies on, such as NFR-2, NFR-6 or FR-SIM-6, *and show how each option serves them*."
   The branch keeps only the first half:
   - the README requires PRD ids;
   - the decider's `FOR MAISARA` format has "the PRD ids", "the reasoning, in at most 5 lines" and the
     strongest reading against it, with nothing per option;
   - the DECISION acceptance check only asserts that "no PRD goal or ranked requirement points to
     another surviving option" and cites the check's ids;
   - none of the interrogator's PRD MISREAD triggers fires when the rejected options are never set
     against the cited requirements.

   This matters because the per-option showing is what lets her veto afterwards "informed": a single
   conclusion plus ids does not show what the other options would have bought. It is also what lets the
   interrogator test "points to another surviving option" rather than take the decider's word. The PR
   draft's disclosure list (`pr2-body.md:15-17`) does not mention the omission, so the softening is silent
   (CLAUDE.md "never drop or soften an item quietly"; the steward's faithfulness check, `steward.md:78`).

   **Fix:**
   - README item 1, after "Each answer cites the PRD ids…": add "and shows, one line per option
     considered, which of those ids the option serves or strains."
   - Decider §1a step 3: add the bullet "each option considered, one line each: the cited PRD ids it
     serves or strains". Make the limit "at most 5 lines, plus one line per option".
   - Decider §1a "Accepting a DECISION for her": the "Decided for Maisara" line shows each surviving
     option against the check's PRD ids.
   - Interrogator 8a: add the trigger "an option the answer rejects (or a surviving option, for a
     DECISION's acceptance check) is not shown against the cited PRD ids".
   - Alternatively, if the omission is deliberate, add it to the PR's disclosed departures.

2. **`scratchpad/pr2-body.md:19-60`: the PR description contract is incomplete.** CLAUDE.md "Git and PRs"
   (`CLAUDE.md:336-338`) and `process-rules.md` §7 require these sections:
   - what was done;
   - an acceptance-criteria checklist with CI evidence;
   - the listening checklist;
   - the contractor review focus;
   - follow-ups;
   - assumption/golden changes;
   - "Decided for Maisara".

   The draft has no listening-checklist section, no contractor-review-focus section and no
   assumption/golden-changes section. Its "Checks" list is not mapped to the objectives O1–O9, and its CI
   line is "_to fill_". §7 says "missing sections are 'request changes' even when the code is good."

   **Fix:** add the following.
   - "Listening checklist: none (no audio output changes)".
   - "Contractor review focus: none in `src/`; process prose only. The engineer may check that
     `/review-phase-pr`'s `process-rules.md` §7 still matches CLAUDE.md (follow-up)".
   - "Assumption / golden changes: None".
   - Turn "Checks" into an O1–O9 checklist, each with its commit, file or grep evidence and, for O8, the
     `ci ok` run on the head SHA.

### Minor
1. **`.claude/agents/decider.md:3` and `.claude/agents/steward.md:55`: terminology left behind.**
   - The decider's description still bounds decisions by "the PRD's hard constraints and Maisara's settled
     decisions". The body now bounds them by her recorded decisions and the plan's AQ/AX defaults except
     the rows being decided (`decider.md:47-52`; `CLAUDE.md:113-115`). The phrase is on O9's own list.
   - The steward's BRIEF check says "her recorded words", while the defined term is "her recorded
     decisions" (README:92-94).

   **Fix:** use the defined term in both places.
2. **`.claude/agents/decider.md:30-32` and `.claude/agents/interrogator.md:169-173`: the survive criteria
   do not include the new check.**
   - The decider's "counts only if it survives" list omits "no PRD MISREAD".
   - The interrogator's SURVIVES definition does not require step 8a to pass. It also requires "nine rows
     convened", which does not fit a `FOR MAISARA` answer given outside a board round (a reading of one of
     her decisions, a Raise item).
   - The 8a closing sentence ("where the PRD truly supports two readings … goes to her as case (a)") names
     no outcome verdict.

   **Fix:** add "no PRD MISREAD" to both lists. Say "nine rows convened (board decisions only)". Name the
   outcome: "PRD MISREAD, re-answered as NEEDS MAISARA (a)".
3. **`.claude/commands/fix-plan.md:11` and `docs/board/README.md:104-107`: there is no entry route for a
   question raised outside the loop.**
   - `/fix-plan` enters the decision loop only from the plan-editor's DECISIONS NEEDED.
   - CLAUDE.md:73-74 sends "every other question" to the decider. That includes a phase file's "Raise with
     Maisara" item, a steward gap and the reading of one of her decisions.
   - Nothing says how such a question reaches decider → interrogator 8a, or where its outputs and ledger
     rows go. `steward.md:75-77` needs that evidence.
   - phase-05h §2 (Raise items 1–2) will exercise this route next.

   **Fix:** one sentence in README item 2, for example: "A question raised outside `/fix-plan` (a Raise
   item, a steward gap) runs as `/fix-plan` step 3 with the question as its DECISION NEEDED; outputs go
   under `docs/review/<target>/`, rows in the ledger."
4. **`docs/board/README.md:65-68`: the role one-liners are stale.**
   - The decider is "decides (minimum tension …)", with no mention of answering for Maisara.
   - The interrogator's list omits the PRD reading.

   **Fix:** add "and answers for Maisara from the PRD (below)" and "and the PRD reading of answers given
   for her".
5. **`docs/board/README.md:110-112` and `decider.md:97-98`: case (a) has no follow-through.** The approved
   message says of case 1: "Your judgement then is the missing input, *and the fix is a PRD change*". The
   rule sends the question to her but never routes her answer into the PRD. The answer survives only as
   "her words in a brief", and the PRD stays silent for the next session.

   **Fix:** add to (a): "Her answer is recorded verbatim in the brief. The orchestrator then offers the PRD
   edit that closes the silence, for her approval (case (b))."
6. **`docs/board/README.md:89-90` and `decider.md:80-81`: Product-owned PRD questions are not covered.**
   The carve-out covers PRD open questions Q1–Q10 (owner "Expert"). It is silent on Q11, Q14 and Q15,
   which the PRD assigns to "Product" or "Product + Engineering" (`docs/PRD.md:166-170`; Q15 gates
   BUILD_PLAN B1, licensing). Answering one closes an open PRD item. It is not stated whether that is the
   decider's, case (a) (the PRD is explicitly open) or case (b).

   **Fix:** one line, for example: "A PRD open question owned by Product (Q11, Q14, Q15) is case (a)
   unless a PRD goal or requirement settles it. The answer then also closes the PRD row (case (b))."
7. **`.claude/agents/steward.md:147-148`: an old routing remains.** "If you think an objective is missing,
   raise it as a brief gap for Maisara" is not read under the new rule. The "whose call" list at `:93-96`
   gives Maisara only the three cases, actions only a person can take, and gaps that are not decisions.

   **Fix:** state that a missing objective is hers because objectives come from her words (and add it to
   the whose-call list), or route it like any other question.
8. **`scratchpad/pr2-body.md:48-49` and brief:96: some PR claims are not yet true.**
   - "The steward cleared the session": the last steward round is round 3, CONTINUE, with G7 (review not
     run, reports unsaved) and G10 (PR and `ci ok`) open. The log does not yet show 3940f96 closing G8 and
     G9.
   - "Every finding is fixed" cannot be checked, because the two earlier review rounds' reports are not
     saved (G7). This file is the first saved review.

   CLAUDE.md "When to open a PR" needs the steward cleared and `/review-phase-pr` run with its fixes in
   before opening. **Fix:** run steward round 4 after this review's fixes and log it, then keep the claims
   in the PR. Cite this file as the review, and save or summarise the earlier rounds' finding lists.

### Questions (unverified, evidence requested)
1. **The case (c) settlement.** The 14:08 message said "one thing only you can settle is case 3". Brief
   line 44 records the orchestrator taking its own recommendation on it ("stays with you") after "Do it".
   The result is the conservative reading, it reserves more to her, and the PR discloses it (item 1). Is
   "Do it" to be read as accepting that recommendation? Her reply after the PR settles it. No change is
   requested.

## What I verified myself
- `python3 .claude/board/build_agents.py --check` printed `ok` (exit 0).
  `git diff --stat 808d3b0..HEAD` names no `.claude/agents/seat*` or `docs/board/seat-*` file.
- `review_context.py --base 808d3b0 --head 3940f96`:
  - no phase;
  - only `claude-config`, `docs/other` and `root` files;
  - no audio-thread, determinism, test-hygiene or pin hits;
  - boundary clean;
  - one pre-existing NFR-8 hit outside the diff.
- `ci_fingerprint.py --rev 808d3b0` equals `--rev 3940f96`. `is_inert()` is True for all 10 changed paths.
- `.venv/bin/pytest -q tools/ci`: 99 passed (no CI test reads the changed prose).
- I read the whole diff and every changed passage at HEAD in all 10 files, and the draft PR body.
- Repo-wide grep (CLAUDE.md, `.claude/` without seats and skill evals, `docs/board/`) for the O9 phrases
  and other routings to her:
  - `decider.md:3` keeps "Maisara's settled decisions" (Minor 1);
  - `steward.md:148` keeps a routing to her (Minor 7);
  - `researcher.md:113` ("adding them is Maisara's decision, subject to licence") concerns her private
    corpus repository and licences, so it is a person-only action and consistent with README:118-120;
  - `seat-protocol.md:79` (seat source, not editable here) still calls all §2/§6 rows "settled", which
    does not conflict: seats do not route questions.
- I checked faithfulness bullet by bullet against brief:25-42:
  - decide from the PRD: yes;
  - name the PRD requirements: yes;
  - show how each option serves them: **no** (Major 1);
  - interrogator check: yes;
  - no accept/veto stop, applied and listed, veto afterwards: yes;
  - the three cases: yes, with the two departures disclosed (case 1's "the fix is a PRD change" not
    carried through, Minor 5);
  - case 3 kept with her: yes;
  - its own session after the 05b merge: yes.
- I checked the PRD for the Q-table owners (`docs/PRD.md:150-170`) and its ranking language (`:49`,
  `:101`: accuracy first). These support decider §1a step 2's "say which one the PRD ranks higher".
- Not applicable, and not invented: the phase-specific checklist (`phase-checklists.md`) and the
  acoustics, DSP, real-time, binaural and tooling domain files. The diff touches no code, test, CI or
  dependency.
- Nothing was built: there is no code change, and CI is the evidence once a PR exists.

## For Maisara
- Listening checklist: none. This branch changes no audio and no code.
- What changes for you: the decider now answers your questions from the PRD and lists them under
  "Decided for Maisara" for your veto afterwards. Only three things still reach you: the PRD is silent or
  contradicts itself; a change to the PRD; overriding a seat's veto. Overriding a seat's veto stays with
  you, as recommended. You can hand it to the decider later.
- The decider may also read or amend one of your recorded decisions when the PRD calls for it. Each such
  answer is marked `AMENDS her decision of <date>`.
- The merge of this PR is yours ("Merge when ci is done" was about PR #25).
- Reminder from `process-rules.md` §8: CLAUDE.md and the BUILD_PLAN preamble still disagree on when a
  phase counts as done (automated criteria vs your listening checklist). This branch does not touch that.

## Contractor review focus (from the phase file), with pointers into the diff
There is no phase file and no code. If the engineer looks at the branch at all:
- the consistency of the three cases across `docs/board/README.md:108-120`, `decider.md:96-103`,
  `steward.md:107-127`, `fix-plan.md:34-38` and `CLAUDE.md:70-76,131-134`;
- the follow-up that `/review-phase-pr`'s `references/process-rules.md` §7 does not yet list "Decided for
  Maisara" (PR draft follow-ups).
