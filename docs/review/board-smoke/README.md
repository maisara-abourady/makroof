# Board smoke runs (2026-11-09)

Runs of the nine-seat board loop made while the board agents were created (session brief
`docs/sessions/2026-11-09-board-agents.md`). The Seat 9 smoke question is a format test only. The D1
run started as a dry run; **Maisara accepted its outcome on 2026-11-09 ("accepted") and it was applied to
the plan through `/fix-plan` in the same session** (files 8–12 below; ledger section "Phase 08 generic
HRTF dataset — board decision D1" in `docs/review/ledger.md`).

Method note: when the seat agents had just been written, the Agent tool did not yet list their types, so
the first smoke run (`seat9-materials-smoke.md`) used a `general-purpose` worker given the generated
agent file (`.claude/agents/seat9-room-acoustician.md`) verbatim as its instructions; its first line says
so. The harness registered the nine types later in the same session, and every seat in the `hrtf-head/`
dry run ran as its own registered agent type (each transcript's method line says which).

| file | what |
|---|---|
| `seat9-materials-smoke.md` | O1 smoke question: Seat 9 alone on how a `materials.json` entry is stored (A nominal / B bounds + provenance / C bounds exposed as a slider) |
| `hrtf-head/` | O8 dry run of the whole loop on Phase 08 session 1 item 1 (which measured dummy-head set becomes `generic-v1`): `1-decider-convene.md` (nine-row table, briefs, K1–K16, R1–R10) → `2-seat1…9-*.md` (all nine seats, native agent types, every one a position) and `3-researcher-dossier.md` (F1–F37; run in parallel) → `4-decider-decision.md` (tension map, ordering, composed variant (a′), debt register) → `5-interrogator-round1.md` (SURVIVES WITH CORRECTIONS, nine restatements, Q1–Q5) → `6-decider-rebuttal.md` (stands, wording revised) → `7-interrogator-round2.md` (SURVIVES WITH CORRECTIONS, no questions) → **applied after acceptance:** `8-plan-diff.patch` (plan-editor) → `9-interrogator-plan-diff-check-1.md` (one major: AC 2 reference vs always-applied DF-EQ) → `10-decider-round3.md` (AC 2 sentence withdrawn and replaced) → `11-plan-diff-2.patch` → `12-interrogator-plan-diff-check-2.md` (resolved, no questions) |

**D1 outcome (accepted by Maisara 2026-11-09 and applied: phase-08, BUILD_PLAN §1/§2 AX35/§5 B14/§6, THIRD_PARTY):** `generic-v1` = SADIE II subject D1 (Neumann KU100), University of York, Apache 2.0, with a bounded (≤ ~32 MB) build-step embed, a dataset-agnostic header (set identity, Voronoi weights, weighted diffuse-field and coherence curves, source EQ state, attribution string), the converter's own solid-angle-weighted diffuse-field curve always applied with a pin-time source-state check, a new AX "data behind a released hrtfId is never replaced", the head named only in licence/THIRD_PARTY/testing record, a validation-only `render_cli --hrtf` override, and preset validation logs recording the head. The TH Köln KU100 set is excluded under phase-08's "unclear licence" stop (its paper says CC BY-SA 3.0, its Zenodo record CC BY 3.0). Two challenges to phase-08 wording: the AC 3 ITD window names no estimator (York's own plots read above it), and scope 1/3 wording on sample rate and DF-EQ. One open debt with no slot in the plan: headphone compensation (Seat 4). Two assumptions this dry run also exercised: all nine seats convened (A1); PRD hard constraints bound the options, tension decides within them (A2).
