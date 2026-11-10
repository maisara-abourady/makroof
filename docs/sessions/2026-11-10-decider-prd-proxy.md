# Session brief: the decider answers for Maisara from the PRD (governance change)

- Branch: `claude/fervent-gates-3aospw` (restarted from origin/main 808d3b0 after PR #25 merged)   Started: 2026-11-10
- Governing: `CLAUDE.md` ("Reporting: the steward", "The board", "Git and PRs"); `.claude/commands/fix-plan.md` step 3;
  `.claude/agents/decider.md`, `steward.md`, `interrogator.md`; `docs/board/README.md`; `docs/PRD.md` (the reference
  the decider reasons from).

## Maisara's words
> 2026-11-10 (asked why the decider did not answer the NEEDS MAISARA questions): "what's wrong with the decider agent?!! i created it particulary to answer when you need his answer"

> 2026-11-10 (told the board's answers): "I accept the board's answer by definition."

> 2026-11-10 (asked what the governance question in PR #25 meant): "Regarding your question, what did you mean? Also, what's the next phase to run?"

> 2026-11-10: "The decider. If it is short on capacity, tell me how can I equip it with what it needs? I can download my own mental moves and mental patterns?"

> 2026-11-10: "If it is capable of reasoning, my north star is the prd that drives my decision making"

> 2026-11-10 (told the change: the decider decides from the PRD; questions reach her only when the PRD is silent or contradictory, for PRD changes and for overriding a seat's veto; done after PR #25 merges, in its own PR): "Do it"

> 2026-11-10 (on PR #25, which the change follows): "Merge when ci is done"

## Objectives
| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | **Session brief**: this brief, checked | CLAUDE.md Reporting 1 | steward BRIEF OK, committed |
| O2 | **Rule stated once**: `docs/board/README.md` has a section "Who answers Maisara's questions" with her words, the proxy rule (the decider answers from the PRD, citing PRD ids; answers are applied and reported; she may veto afterwards) and the three cases that still go to her (PRD silent or contradictory; a change to the PRD or to one of her recorded decisions; overriding a seat's veto-grade rating), plus things only a person can do | "north star is the prd", "Do it" | the section in the diff |
| O3 | **Decider agent follows it**: `.claude/agents/decider.md` gains a section on answering for Maisara; description, section 0, the 3-round rule, the output list and the rules no longer leave accept/veto or contested items to her outside the three cases | "i created it particulary to answer when you need his answer" | diff of decider.md |
| O4 | **/fix-plan step 3 follows it**: no accept/veto stop; surviving decisions are applied and listed for her veto afterwards; NEEDS MAISARA only in the three cases | "Do it" | diff of fix-plan.md |
| O5 | **Steward and interrogator follow it**: the steward's NEEDS MAISARA list is narrowed to the three cases plus actions only a person can take; the interrogator checks the decider's PRD reasoning (new verdict PRD MISREAD) and that a NEEDS MAISARA is a real three-case question | "Do it" | diffs of steward.md, interrogator.md |
| O6 | **CLAUDE.md consistent**: "The board" and "Reporting" state the rule by reference | "Do it" | diff of CLAUDE.md |
| O7 | **Seat files untouched**: generated seat agents still match their sources | CLAUDE.md "The board" (never hand-edit) | `python3 .claude/board/build_agents.py --check` passes |
| O8 | **PR opened, CI, merged**: review run on the diff, steward cleared, PR opened, `ci ok` green (or skipped and linked: all paths are fingerprint-excluded), PR merged | CLAUDE.md "When to open a PR"; my stated plan ("its own small PR") as she approved it with "Do it" | PR link, `ci ok` run, merge SHA |

## Scope
- In: the files named in O2–O6; this brief.
- Out: re-deciding anything already decided; phase 05h; the review skill's stale references (PR #25 follow-up 7);
  any PRD, BUILD_PLAN or phase-file change (none is needed: the rule is about process, not an assumption).

## Constraints and settled decisions
- Seat personas and generated seat files are not edited (CLAUDE.md "The board").
- The minimum-tension ordering, veto-grade exclusion and interrogation are unchanged; only who answers the
  questions that used to stop for her changes.
- A seat's veto-grade override stays hers (my recommendation, which she approved with "Do it").
- "Raise with Maisara" items are still raised in the first message and the PR (CLAUDE.md rule 2), as information
  where the decider has answered them.

## Raise with Maisara
- none

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
