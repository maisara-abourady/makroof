# Session brief: agent personae and the steward

- Branch: claude/zealous-albattani-6pp3vm   Started: 2026-11-06   Governing: CLAUDE.md; `.claude/agents/*.md`; `.claude/commands/fix-plan.md`, `interrogate.md` (no phase: agent and tooling change, no plan or PRD edits)

## Maisara's words
> (2026-11-06, 1) I want to enrich my subagents personae: The the decider gets interrogated bu the interrogator and has to survive its scrutiny, and that is the dynamic between them. The decider shall never be under educated or under informed or mal informled or ill informed, it shall be equipped with the knowledge it requires for the particular decision and that is the researcher's job. The advocate is not supposed to be an advocate of the decider, it's the advocate of the product that makes sure both the decider and the interrogator are grounded to the product's intended goal and outcome. It can not decide, but it can certainly intervene and correct the paths of their conversation and say no. It's a screening gate and a detector. We might introduce other advicates later that wear other hats

> (2026-11-06, 2) I need to introduce an agent that you return back to that is fully aware of the objectives of the session in detail so you report back to it instead of me and it tells the orchestrator what is missing so the orchestrator takes decisions on what agent to delegate to do which

## Objectives
| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | Decider's decisions are interrogated and stand only if they survive | words 1 | decider.md and interrogator.md define the survive/fall rule and the interrogator's decision mode |
| O2 | Decider never decides uninformed / under- / mis- / ill-informed; researcher equips it per decision | words 1 | decider.md refuses to decide on gaps (RESEARCH NEEDED); researcher.md defines the per-decision dossier and checks the decider's premises |
| O3 | Advocate is the product's advocate (not the decider's), keeps decider and interrogator grounded to the product's goal and outcome; cannot decide; can intervene, redirect, say no; a screening gate and detector; room for other advocates with other hats | words 1 | advocate.md defines this, with PASS/REDIRECT/NO and drift detectors |
| O4 | The loop is actually run (subagents cannot call each other) | derived from O1–O3 | fix-plan.md orchestrates researcher → decider → interrogator → advocate |
| O5 | A new agent holds the session objectives in detail; the orchestrator reports to it instead of Maisara | words 2 | steward.md exists; a brief format gives it the objectives; CLAUDE.md requires reporting to it |
| O6 | It tells the orchestrator what is missing; the orchestrator decides delegation | words 2 | steward.md lists gaps with closing evidence and forbids naming agents |
| O7 | Changes committed and pushed to the session branch; no PR unless asked | CLAUDE.md, session instructions | commits on origin/claude/zealous-albattani-6pp3vm |

## Scope
- In: `.claude/agents/*.md`, `.claude/commands/*.md`, `CLAUDE.md`, `docs/sessions/`.
- Out: PRD, BUILD_PLAN, phase files (would need /fix-plan); the `review-phase-pr` skill.

## Constraints and settled decisions
- The advocate cannot block a WRONG / CONDITIONS VIOLATED result on cost (NFR-1 accuracy first); reported to Maisara 2026-11-06, not yet confirmed by her.
- The name `advocate` is kept for compatibility with earlier review files.

## Raise with Maisara
- none (no phase file)

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
| 1 | 2026-11-06 | BRIEF OK; CONTINUE | G1 (commit+push O5/O6 files incl. brief), G2 (steward cannot run git/CI checks), G3 (advocate only gates after the loop, not mid-exchange), G4 (advocate no-NO-on-correctness limit unconfirmed by Maisara), G5 (CLAUDE.md "step 2 above" ambiguous) | none |
