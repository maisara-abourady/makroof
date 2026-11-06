# Session briefs

Each working session (a phase, a `/fix-plan`, a review, an agent or tooling change) keeps one brief
here: `docs/sessions/<YYYY-MM-DD>-<slug>.md`, where `<slug>` is the phase id or a short name. It is the
memory of the **steward** agent (`.claude/agents/steward.md`). The orchestrator (the main session) writes
the brief, has the steward check it, reports to the steward after each substantial step, and reports to
Maisara only when the steward says READY TO REPORT or NEEDS MAISARA.

The brief is committed to the session's branch so a second session on the same work, or the reviewer,
can pick it up.

## Template

```markdown
# Session brief: <title>

- Branch: <branch>   Started: <date>   Governing: <CLAUDE.md, phase file, BUILD_PLAN §…, PRD §…, command or skill>

## Maisara's words
> <each request verbatim, with its date; add every later instruction here as it arrives, never edit an earlier one>

## Objectives
| id | objective | from (her words / governing doc) | done when (evidence) |
|---|---|---|---|
| O1 | … | … | … |

## Scope
- In: …
- Out (follow-ups, not this session): …

## Constraints and settled decisions
- … (cite ids: AX…, NFR…, decider report …, accepted by Maisara on …)

## Raise with Maisara
- … (from the phase file, or "none")

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
```
