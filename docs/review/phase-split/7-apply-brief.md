# Apply brief for the plan-editors (phase split, 2026-11-10)

You apply verified decisions. You make **no** acoustic, numeric or product choice; if something here is ambiguous,
stop and return it as DECISIONS NEEDED with the exact passage.

Read first: `CLAUDE.md`; the session brief `docs/sessions/2026-11-10-phase-split.md` ("Reading of her words": value
rule, naming, carry-over list); your phase's draft map `docs/review/phase-split/map-<XX>.md` (sub-phase table, coverage
table, references table); the decisions `docs/review/phase-split/1-decider-convening.md` (classifications and
corrections), `3-decider-decision.md` (D-PS2 steps 1–6 stand as written there), `5-decider-decision-r2.md` (final
D-PS1, D-PS3, D-PS4, FM-1, corrections list; its Addendum and the corrections in `6-interrogator-decision-r2.md`
override earlier text). Where the map and a decision differ, **the decision wins**. Where the map raised a CHOICE that
the convening round classified NOT A DECISION, apply the resolution the convening round states.

## What to write

For phase `<XX>` with sub-phases `<XX>-1 … <XX>-n`:

1. **Sub-phase files** `docs/phases/phase-<XX>-<n>.md`, each with, in this order:
   - Title line `# Phase <XX>-<n> — <title>` and a header line:
     `Size: **S|M|L** (remainder, if needed: `<XX>-<n>b`) · Depends on: … · Part of: [phase-<XX>](phase-<XX>.md) ·
     Lead subject matter: Seat <k> (<seat name>), "<convening-table row words>" · Read first: …` (carry the original
     header's dependency and read-first items that apply, verbatim; the umbrella's full dependency line where a
     decision says so).
   - `## Raise with Maisara` if the coverage table or a decision gives this sub-phase Raise items (verbatim).
   - `## Goal` (this sub-phase's share; one or two sentences drawn from the original goal, no new claims).
   - `## Assumptions in force` (the items that bear on this sub-phase, verbatim; may say "and all of the umbrella's").
   - `## Scope`, `## Out of scope`, `## Acceptance criteria — automated`, `## Listening / manual checklist`,
     `## Contractor review focus`, `## Risks`, `## Definition of done` — each item **verbatim** from the original, with
     its original label kept in brackets, e.g. `(phase-08 scope 3)`, `(phase-08 AC5)`. A criterion split into clauses
     keeps each clause verbatim and is marked `(phase-13 C2, sentence 1; rest in 13-2)`.
   - Hand-offs and notes that the decisions add (verbatim from the decision text), under a short `## Notes from the
     split` section, citing the decision id (D-PS1 … D-PS4, FM-1, convening-round correction n).
   - Definition of done includes: "CLAUDE.md rules apply: one sub-phase per session; if it can't be finished in two
     sessions, split the remainder into `phase-<XX>-<n>b.md`."
2. **The original file `docs/phases/phase-<XX>.md` becomes the umbrella**, keeping its title, its header line (size
   becomes "split into <XX>-1…<XX>-n"; dependencies verbatim), its Goal and Assumptions in force verbatim, and any
   item the coverage table marks `umbrella` or `shared` (verbatim, with label). Then add:
   - `## Sub-phases` — table: id (linked), title, lead seat, size, depends on, ships, owns (criteria labels).
   - `## Where the original items went` — the coverage table: every original label → sub-phase (or umbrella), so
     existing references such as "phase-08 scope 3" resolve.
   - Notes from the split that the decisions put on the umbrella (verbatim).
   - A line: "Status: the umbrella is `done` when every sub-phase is. A dependency on phase <XX> means all of its
     sub-phases unless a sub-phase is named."
   Remove from the umbrella only text that now lives verbatim in a sub-phase file.
3. Do **not** edit any other file (no BUILD_PLAN, no other phase, no phase-05h). Report any reference elsewhere that
   would no longer resolve.

## Self-check before reporting
- Every label in the map's coverage table appears exactly once across the sub-phase files and umbrella (or twice where
  marked shared). Diff the original file (`git show HEAD:docs/phases/phase-<XX>.md`) against the union of the new files:
  no sentence of the original is lost or reworded, other than headings and the size line.
- No threshold, number or AX/AQ id changed.

Return to the orchestrator only: files written, the self-check result (lost or changed sentences: none / list), and any
DECISIONS NEEDED. Under 200 words.
