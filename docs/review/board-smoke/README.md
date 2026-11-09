# Board smoke runs (2026-11-09)

Dry runs of the nine-seat board loop made while the board agents were created (session brief
`docs/sessions/2026-11-09-board-agents.md`). **Nothing here is adopted**: the decisions are proposals
recorded to show the loop works end to end; applying one goes through `/fix-plan` in a later session.

Method note: an agent type added mid-session is not registered until a new session starts, so every
seat in these runs was a `general-purpose` worker given the generated agent file
(`.claude/agents/seat<n>-*.md`) verbatim as its instructions; each transcript's first line says so.

| file | what |
|---|---|
| `seat9-materials-smoke.md` | O1 smoke question: Seat 9 alone on how a `materials.json` entry is stored (A nominal / B bounds + provenance / C bounds exposed as a slider) |
| `hrtf-head/` | O8 dry run of the whole loop on Phase 08 session 1 item 1 (which SADIE II head becomes `generic-v1`): decider CONVENE, seats, researcher, decider decision, interrogator |
