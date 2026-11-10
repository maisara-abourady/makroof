# Drafting brief for the split maps (one worker per phase)

Repo /home/user/makroof. Read `CLAUDE.md`, `docs/sessions/2026-11-10-phase-split.md` (the rules: "Reading of her
words" — especially value rule, naming, what counts as a decision), the convening table in `docs/board/README.md`,
`docs/BUILD_PLAN.md` §0 (status) and your phase file in full, plus anything it cites that you need to understand a
dependency.

Maisara, 2026-11-10: "split each of the remaining phases 7 onwards into the smallest buildable sub phases that ship
value while keeping the session's attention focused on one subject matter that deserves it".

Task: draft the split map for ONE phase and write it to `docs/review/phase-split/map-<XX>.md`. Do not edit any
other file. Contents:

1. **Sub-phase table**: id (`<XX>-<n>`), title, lead subject matter (seat number + name from the convening table,
   with the row words it falls under), size (S/M/L), depends on (other sub-phases or phases, from the phase file),
   what it ships (one line), the existing automated criteria it owns (by their number/label in the phase file).
   Rules: each sub-phase is buildable on its own (main stays green), owns at least one existing automated criterion
   (otherwise merge it with a neighbour; compound criteria may be split into existing clauses, verbatim), and has one
   lead subject matter. Smallest that still deserves a session: don't create S sub-phases that are a few lines of
   work unless the subject is distinct and risky. If the phase is already focused, keep it whole and say why.
2. **Order and rationale**: why this order; flag explicitly any element that the session brief counts as a
   **decision** (order that changes what ships first / which risk is retired first; a cut that moves an item across
   a recorded dependency; size crossing the two-session limit). List them as `CHOICE <XX>-c<k>: options …,
   recommended …, why`. Do not resolve product or acoustic questions yourself.
3. **Coverage table**: every item of the original file — each scope item, each automated criterion, each
   listening/manual item, each contractor review focus item, each risk, each Raise item, definition-of-done
   items, "settled"/"decisions before implementation" items — by its original number/label → the sub-phase that
   gets it, or `umbrella` (if it governs all sub-phases, e.g. shared assumptions). Nothing may be unassigned or
   assigned twice (umbrella + one sub-phase for a shared item is fine if marked "shared").
4. **References**: grep the repo (exclude docs/corpus, docs/review, docs/sessions) for references to your phase's
   numbered items (e.g. "phase-08 scope 3", "phase-08.md §", "Phase 08 criterion") and list each with file:line →
   new sub-phase.

Change no threshold, number, AX/AQ value, wording of a criterion, or decision. Return to the orchestrator ONLY a
summary under 150 words: sub-phase ids with one-line titles and lead seat, and the CHOICE ids. The full content
lives in the file.
