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
| `hrtf-head/` | O8 dry run of the whole loop on Phase 08 session 1 item 1 (which measured dummy-head set becomes `generic-v1`): `1-decider-convene.md` (nine-row table, briefs, K1–K16, R1–R10) → `2-seat1…9-*.md` (all nine seats, native agent types, every one a position) and `3-researcher-dossier.md` (F1–F37; run in parallel) → `4-decider-decision.md` (tension map, ordering, composed variant (a′), debt register) → `5-interrogator-round1.md` (SURVIVES WITH CORRECTIONS, nine restatements, Q1–Q5) → `6-decider-rebuttal.md` (stands, wording revised) → `7-interrogator-round2.md` |

**Dry-run outcome (proposal only, for Maisara to accept or veto in a later `/fix-plan`):** `generic-v1` = SADIE II subject D1 (Neumann KU100), University of York, Apache 2.0, with a bounded (≤ ~32 MB) build-step embed, a dataset-agnostic header (set identity, Voronoi weights, weighted diffuse-field and coherence curves, source EQ state, attribution string), the converter's own solid-angle-weighted diffuse-field curve always applied with a pin-time source-state check, a new AX "data behind a released hrtfId is never replaced", the head named only in licence/THIRD_PARTY/testing record, a validation-only `render_cli --hrtf` override, and preset validation logs recording the head. The TH Köln KU100 set is excluded under phase-08's "unclear licence" stop (its paper says CC BY-SA 3.0, its Zenodo record CC BY 3.0). Two challenges to phase-08 wording: the AC 3 ITD window names no estimator (York's own plots read above it), and scope 1/3 wording on sample rate and DF-EQ. One open debt with no slot in the plan: headphone compensation (Seat 4). Two assumptions this dry run also exercised: all nine seats convened (A1); PRD hard constraints bound the options, tension decides within them (A2).
