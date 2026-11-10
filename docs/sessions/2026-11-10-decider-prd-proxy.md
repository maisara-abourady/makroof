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

> 2026-11-10 (after PR #26 opened, CI run 42836296191 still queued; all changed paths fingerprint-excluded prose): "Merge 26"

The orchestrator's message of 2026-11-10 14:08 UTC that she answered with "Do it" (verbatim; the approved change):

> Yes, it can reason from the PRD, and that's the authority it was missing. The PRD can now replace you as the decider's final reference. Your words are recorded in the session brief.
>
> **What changes:**
> - **Decide from the PRD.** When a question would have come to you, the decider decides it from the PRD. That covers reinterpreting one of your settled decisions, like Q1's "does the 1 % rule apply to bias or to every random error". It also covers trade-offs the earlier rules left to you, like Q2's accuracy against load time.
> - **Show the reasoning.** It must name the PRD requirements it relies on, such as NFR-2, NFR-6 or FR-SIM-6, and show how each option serves them.
> - **Interrogator check.** The interrogator checks that reasoning against the PRD as it does everything else. The decision stands only if it survives.
> - **No accept/veto stop.** The decision is applied and listed in the report. You can veto afterwards.
>
> **What I'd still bring to you, in only three cases:**
> 1. **The PRD is silent or contradicts itself on the point.** Your judgement then is the missing input, and the fix is a PRD change.
> 2. **A change to the PRD itself.** The north star shouldn't edit itself.
> 3. **Overriding a seat's veto-grade rating.** A 3 means a seat judges an option unacceptable. Overruling it should stay yours, unless you'd rather the decider may override when the PRD clearly supports it.
>
> This session shows it would work. Q1, Q2 and Challenge 1 each had a defensible answer from the PRD's requirements. The board reached those answers itself once it was allowed to.
>
> Making it the rule is a small change to CLAUDE.md, `/fix-plan` step 3 and the decider's instructions. I'll do it as its own short session after the phase-05b merge, so it doesn't mix into this PR. One thing only you can settle is case 3: should a veto still come to you, or may the decider override it when the PRD supports that? I recommend it stays with you.
>
> Meanwhile CI on [maisara-abourady/makroof#25](https://github.com/maisara-abourady/makroof/pull/25) is still running. I'll merge when it's green, as you asked.

The orchestrator's next message (14:08:57): "I'll make the governance change. On the one open point, I'm taking my recommendation: overriding a seat's veto stays with you."

## Objectives
| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | **Session brief**: this brief, checked | CLAUDE.md Reporting 1 | steward BRIEF OK, committed |
| O2 | **Rule stated once**: `docs/board/README.md` has a section "Who answers Maisara's questions" with her words, the proxy rule (the decider answers from the PRD, citing PRD ids; answers are applied and reported; she may veto afterwards) and the three cases that still go to her as approved in the 14:08 message she answered with "Do it" (PRD silent or contradictory; a change to the PRD itself; overriding a seat's veto-grade rating), plus things only a person can do. Reading or amending one of her recorded decisions when the PRD calls for it is the decider's (the approved message: "reinterpreting one of your settled decisions, like Q1's …", "trade-offs … like Q2's"), applied and reported. Plan text that routes a question to her is read under the rule, not rewritten | "north star is the prd", "Do it" | the section in the diff |
| O3 | **Decider agent follows it**: `.claude/agents/decider.md` gains a section on answering for Maisara; description, section 0, the 3-round rule, the output list and the rules no longer leave accept/veto or contested items to her outside the three cases | "i created it particulary to answer when you need his answer" | diff of decider.md |
| O4 | **/fix-plan step 3 follows it**: no accept/veto stop; surviving decisions are applied and listed for her veto afterwards; NEEDS MAISARA only in the three cases | "Do it" | diff of fix-plan.md |
| O5 | **Steward and interrogator follow it**: the steward's NEEDS MAISARA list is narrowed to the three cases plus actions only a person can take; the interrogator checks the decider's PRD reasoning (new verdict PRD MISREAD) and that a NEEDS MAISARA is a real three-case question | "Do it" | diffs of steward.md, interrogator.md |
| O6 | **CLAUDE.md consistent**: "The board" and "Reporting" state the rule by reference | "Do it" | diff of CLAUDE.md |
| O7 | **Seat files untouched**: generated seat agents still match their sources | CLAUDE.md "The board" (never hand-edit) | `python3 .claude/board/build_agents.py --check` passes |
| O8 | **PR opened, CI green**: review run on the diff and its fixes in, steward cleared, PR opened, `ci ok` green (or skipped and linked: all paths are fingerprint-excluded). The merge is hers: "Merge when ci is done" was about PR #25 only | CLAUDE.md "When to open a PR"; my stated plan ("open its own small PR") as she approved it with "Do it" | PR link, `ci ok` run |
| O9 | **No old rule left**: a grep of CLAUDE.md, `.claude/` and `docs/board/` (session briefs, reviews, corpus excluded) for "accept or veto", "Don't adopt one without her", "proposals Maisara can veto", "Maisara's settled decisions", "plans are Maisara's decision", "decision Maisara has already made", "NEEDS MAISARA" shows every hit changed or intended | steward G4 | grep output with each hit classed |

## Scope
- In: the files named in O2–O6; this brief.
- In also: `.claude/commands/interrogate.md` (its "changes to the PRD or plans are Maisara's decision").
- Out: re-deciding anything already decided; phase 05h; the review skill's stale references (PR #25 follow-up 7);
  any PRD, BUILD_PLAN or phase-file change. Plan rows that route a question to her (AQ10 / AX38 4c "goes to
  Maisara before any range change", AX38 (iv) and (vi), phase-05h §2 and its Raise items 1–2, phase-05b.md:149)
  stay as written and are read under the rule (README "Who answers Maisara's questions" item 4); they may be
  reworded the next time `/fix-plan` touches them. Where a routing is a PRD change (e.g. narrowing the contract
  room range), it stays hers under case (b).

## Constraints and settled decisions
- Seat personas and generated seat files are not edited (CLAUDE.md "The board").
- The minimum-tension ordering, veto-grade exclusion and interrogation are unchanged; only who answers the
  questions that used to stop for her changes.
- A seat's veto-grade override stays hers (my recommendation, which she approved with "Do it").
- The edits were drafted before BRIEF OK and committed with the brief in 06a1aaa (steward G5): a process slip,
  recorded here; the drafts were rechecked against the corrected O2 before the next commit.
- The final report and the PR say plainly that overriding a seat's veto stays with her and that she can
  reverse that (steward G6).
- "Raise with Maisara" items are still raised in the first message (noting that the decider answers each from the
  PRD unless one of the three cases applies) and in the PR, whose "Decided for Maisara" gives the answers (CLAUDE.md rule 2).
- Disclosed in the PR as going slightly beyond the approved 14:08 text (review of the diff): case (a)'s qualifier
  "and none of her recorded decisions settles it" (narrows what reaches her; supported by the approved
  "reinterpreting one of your settled decisions"), and a 3-round ruling that fails the interrogator's check goes to
  her as case (a) (widens what reaches her).

## Decided for Maisara
- none (this session decides no product, acoustic or numeric question)

## Raise with Maisara
- none

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
| 1 | 2026-11-10 | BRIEF GAPS | G1 (O2 adds recorded decisions, approved text has PRD only), G2 (O8 merge not from her words), G3 (plan escalations and interrogate.md:19 not addressed), G4 (no grep done-criterion), G5 (edits before BRIEF OK), G6 (veto-override note to her) | none |
| 2 | 2026-11-10 | BRIEF OK | none | G1, G2, G3, G4, G5, G6 |
| 3 | 2026-11-10 | CONTINUE | G7 (`/review-phase-pr` not run before opening; review reports unsaved), G8 (non-blocking: PR draft heading, grep scope, CI skip wording, person-only list), G9 (non-blocking: steward.md whose-call omits the non-decision 3-round gap), G10 (PR and `ci ok` pending) | none open from earlier rounds; O1–O7 and O9 MET at a97fa99 |
| 4 | 2026-11-10 | READY TO REPORT (once the PR link, a green or linked `ci ok`, and the G11 PR-body corrections are in) | G11 (non-blocking: PR body PRD guard should be (a) or (b); a97fa99 does not list findings), G12 (non-blocking: README item 3 paragraph splits the (b)/(c) bullets) | G7, G8, G9; G10 open until the PR and `ci ok` |
| 5 | 2026-11-10 | (orchestrator note) Maisara: "Merge 26". O8 closed by her instruction: PR #26 merged while CI run 42836296191 was still queued (prose-only diff, fingerprint equal to 808d3b0's) | — | G10 (merge per her words) |
