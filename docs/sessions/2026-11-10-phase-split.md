# Session brief: split the remaining phases (07c–13) into focused sub-phases

- Branch: `claude/funny-rubin-pdkwd1` (from main 8583ba1, after PR #27)   Started: 2026-11-10
- Governing: `CLAUDE.md` ("Scope list", "Reporting: the steward", "Assumptions and decisions", "The board");
  `.claude/commands/fix-plan.md` (plan changes: plan-editor applies, interrogator checks, decider for any choice);
  `docs/BUILD_PLAN.md` §0, §6; `docs/phases/phase-07c.md`, `phase-08.md` … `phase-13.md`; `docs/board/README.md`
  (convening table: the nine subject matters); `docs/PRD.md` (for any answer given for Maisara).

## Maisara's words
> 2026-11-10 (same session, after asking how the board seats run): "Since we have opened this bramch might as well
> use it for something totally different. I want you to split each of the remaining phases 7 onwards into the
> smallest buildable sub phases that ship value while keeping the session's attention focused on one subject matter
> that deserves it"

## Reading of her words
- "remaining phases 7 onwards": every phase numbered 07 or higher that is not `done` in BUILD_PLAN §0: **07c, 08, 09,
  10, 11, 12, 13**. Phase 07 is `done` (PR #23) and is not split. 05-series phases (05h in progress, 05d not started)
  are not "7 onwards" and are out of scope.
- "smallest buildable sub-phase that ships value": each sub-phase leaves `main` building and green, and delivers
  something checkable on its own (an automated acceptance criterion it owns, and where it produces audio, a render
  in the listening pack). A sub-phase that only prepares code for a later one without its own check does not count.
- "one subject matter that deserves it": each sub-phase has one lead subject matter, named by the board seat whose
  convening-table row (`docs/board/README.md`) it falls under; a sub-phase is not split further where the result
  would no longer deserve a session (too small to carry its own check). A phase already that focused is kept whole,
  with the reason recorded.
- A split is a reallocation, not a redesign: no scope item, acceptance criterion, threshold, AX/AQ value, listening
  item, contractor focus or Raise item is added, dropped or changed in substance.
- **Value without a new criterion (G2).** A candidate sub-phase that would own no existing automated criterion is
  merged with a neighbour. A compound criterion may be split into its existing clauses, worded as before (each
  clause verbatim, plus only the subject it needs to stand alone). The interrogator's diff check tests both.
- **Which choices are decisions (G1).** A worker drafts each phase's map from the phase file (pure reallocation).
  The decider then receives all seven maps and, per map, either records it as **not a decision** with the reason
  (the cut follows the phase's own structure and changes no order of delivery, dependency or risk) or treats the
  element as a decision: an order of sub-phases that changes what ships first or which risk is retired first, a cut
  that moves an item across a dependency already recorded (e.g. AX37 (5.3), 07c's timing), or a size change that
  moves a phase across the two-session limit. Those go through the decision loop (convening, seats, decision,
  interrogator decision mode). The lead seat of each sub-phase is read from the convening table, not decided.
- **Naming (G3).** Sub-phases are `phase-<XX>-<n>.md` (`08-1`, `08-2`, …; `07c-1`, `07c-2`, …). The CLAUDE.md
  two-session remainder of a sub-phase is `<XX>-<n>b` (e.g. `08-2b`), so no name collides with the letter suffixes
  already used (07c, 13b foreseen by phase-13's size line becomes per sub-phase). The original row stays in §0 as an
  umbrella with status `split (<first>…<last>)`, set to `done` when all its sub-phases are; a dependency on the
  umbrella in any file means all of its sub-phases unless the umbrella's table names one.
- **No phase is executed (G4).** No listening checklist, listening pack or contractor review focus applies to this
  session. Every sub-phase file carries over, unchanged in substance: its "Raise with Maisara" items, a size line, its
  dependencies, the two-session limit (CLAUDE.md), and its share of goal, scope, criteria, listening checklist,
  contractor review focus, risks and definition of done.

## Objectives
| id | objective | from | done when (evidence) |
|---|---|---|---|
| O1 | **Session brief** — this brief, checked; its objectives match the opening scope list one for one (list items 1–8 = O1–O8) | CLAUDE.md Reporting 1, Scope list 1 | steward BRIEF OK, committed |
| O2 | **Split map** — 07c, 08, 09, 10, 11, 12, 13 each have a sub-phase map (or a recorded reason to stay whole); each sub-phase names its lead subject matter (seat), what it ships, its own automated check, and its dependencies | her words | `docs/review/phase-split/` map files; one per phase |
| O3 | **Coverage, nothing lost** — every scope item, automated criterion, listening item, contractor focus item and Raise item of each original phase is assigned to exactly one sub-phase (or kept in the umbrella file where it governs all of them); no threshold or AX/AQ value changed | her words ("split"), CLAUDE.md "never invent an answer quietly" | coverage table per phase in the map file; interrogator diff check finds no lost or changed criterion |
| O4 | **Sub-phase files** — a `docs/phases/phase-<XX>-<n>.md` per sub-phase, written by the plan-editor; each original phase file becomes an umbrella index (goal, sub-phase table, shared assumptions, items that span all sub-phases) so existing references (`phase-08 scope 1–3`, review skill refs, code comments) still resolve | CLAUDE.md "Assumptions and decisions" (/fix-plan route) | files in `git diff`; each umbrella has a mapping from old item numbers to sub-phases; a reference table (grep of the repo, `docs/corpus/` excluded, for `phase-<XX>` item references) in `docs/review/phase-split/references.md`, each mapped to its sub-phase |
| O5 | **BUILD_PLAN updated** — §0 has a row per sub-phase (`not started`, size, dependencies) replacing the split rows' role; §6 change-log row records the split | CLAUDE.md rule 6 | diff of BUILD_PLAN.md |
| O6 | **Choices verified** — per map, the decider's record: "not a decision" with reason, or a DECISION that SURVIVES the interrogator (decision mode) through the loop above; the interrogator checks the finished diff (coverage, no changed criterion, G2 rule); outputs saved in `docs/review/phase-split/`; ledger entry in `docs/review/ledger.md` | fix-plan steps 3, 5, 6 | decider file(s) and interrogator files in `docs/review/phase-split/`; diff verdict with no WRONG; ledger rows |
| O7 | **Tooling unaffected** — `pytest tools/ci` passes; no code, test or workflow changed | CLAUDE.md (fingerprint excludes docs/phases, BUILD_PLAN) | pytest output; `git diff --stat` touches only prose paths |
| O8 | **Committed and pushed** to `claude/funny-rubin-pdkwd1` | system instructions | `git log origin/claude/funny-rubin-pdkwd1` |

## Scope
- In: phase files 07c, 08, 09, 10, 11, 12, 13 and their new sub-phase files; BUILD_PLAN §0 and §6; review files and
  ledger for this change.
- Out (follow-ups, not this session): any code; phase 07 (done); 05h, 05d; any change to a criterion, threshold or
  assumption; opening a PR (not asked; offered at the end).

## Constraints and settled decisions
- Plan edits go through `/fix-plan`: the plan-editor applies; it makes no acoustic or numeric choice.
- Dependencies recorded in the original files (e.g. 07c depends on 05h and 07; 08 on 05h except AX37 (5.3)
  conditions; 13 on 00–12 and 07c) carry over to the right sub-phases unchanged.
- Board decisions cited in phase files (decider files, D-ids, AX/AQ rows) are not reopened.
- CLAUDE.md "If a phase can't be finished in two sessions, split the remainder into `phase-XXb.md`": the new names
  must not collide with existing files (07c exists). Phase-13's size line ("split into 13b") becomes per sub-phase
  (`13-<n>b`), a reallocation recorded in the phase-13 coverage table.

## Decided for Maisara
- D-PS1 — 08's four sub-phases carry the 05h exception verbatim; AX37 (5.3) (i) on 08-2 and 08-3, (ii)/(iv) on 08-3, (iii) on 08-4 — PRD FR-SIM-3, NFR-1 — `docs/review/phase-split/3-…`, `5-…`, `6-…` — vetoed? no
- D-PS2 — 2° grouping decided on 08-4's benchmark; if it lands, L1/L3/L4/L5 re-heard before the golden freeze — PRD NFR-1, NFR-2, FR-SIM-3 — same files — vetoed? no
- D-PS3 — Phase 11 split shell-first (11-1 editor shell → 11-2 canvas → 11-3 surfaces); 11-1's layout provisional, canvas region reserved — PRD Overview, FR-3D-5, FR-3D-8 — same files — vetoed? no
- D-PS4 — Phase 13 in five parts: 13-1 performance (Seat 3), 13-2 engine limits (Seat 2), 13-3 platforms (S9 first), 13-4 hosts, 13-5 release; K1–K3 read from 13-1; Raise items in 13-1 and 13-5 — PRD NFR-2, NFR-4, NFR-6, line 174 — same files + `5b-seat2-r2.md` — vetoed? no
- FM-1 — Phase 11 must be split rather than kept whole (her 2026-11-10 instruction settles it; PRD neutral) — PRD Overview, FR-3D-5, FR-3D-8, NFR-4, line 174 — same files — vetoed? no
- Size ruling — the two-session limit applies per sub-phase, so total sessions rise — her 2026-11-10 instruction, CLAUDE.md — `1-decider-convening.md`, `4-…` — vetoed? no
- Phase 09 kept whole; Phase 12 split in two — her 2026-11-10 instruction — `1-decider-convening.md` — vetoed? no

## Raise with Maisara
- Phase 13's four Raise items (commissioning decision F2, DELTA panel report, load time with 8 instances AX38 (iv),
  07c not landed): they are raised by the session that executes the sub-phase that holds them; this session moves
  them unchanged. Phase 07c §2 Raise items likewise.

## Steward log
| round | date | verdict | gaps opened | gaps closed |
|---|---|---|---|---|
| 0 | 2026-11-10 | BRIEF GAPS | G1, G2 (blocking); G3, G4 (non-blocking) | none |
| 1 | 2026-11-10 | BRIEF OK | none (3 wording fixes: O4 file pattern, Constraints 13b line, log row 0) | G1, G2, G3, G4 |
| 2 | 2026-11-10 | CONTINUE | G5 (O4 references.md missing, map-13 references on superseded numbering; blocking), G6 (follow-ups in the report; non-blocking) | none (O1–O3, O5–O8 MET) |
| 3 | 2026-11-10 | READY TO REPORT | none (note: THIRD_PARTY.md pointer is outside the In list; stated in the report) | G5, G6 |
